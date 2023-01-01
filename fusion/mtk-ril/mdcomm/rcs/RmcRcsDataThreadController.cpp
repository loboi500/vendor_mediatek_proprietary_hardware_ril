/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 *
 * MediaTek Inc. (C) 2016. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
 * AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek Software")
 * have been modified by MediaTek Inc. All revisions are subject to any receiver's
 * applicable license agreements with MediaTek Inc.
 */

/*****************************************************************************
 * Include
 *****************************************************************************/
#include "RfxVoidData.h"
#include "RfxIntsData.h"

#include "RfxRcsSendMsgData.h"
#include "RmcRcsDataThreadController.h"

// for send MCL request to myself
#include "RfxMclDispatcherThread.h"
#include "RfxMclMessage.h"
#include "RfxMessageId.h"

// for socket / thread
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cutils/sockets.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define RFX_LOG_TAG "RmcRcsDataThrd"

RmcRcsSharedMemory::RmcRcsSharedMemory(void) {
    mLock = PTHREAD_MUTEX_INITIALIZER;
    mPLock = &mLock;
    mCond = PTHREAD_COND_INITIALIZER;
    mDataReadyCount = RCS_RIL_SHARE_DATA_STATUS_RECV_NONE;
    mDatalen = 0;
    mData = NULL;
}

RmcRcsSharedMemory::~RmcRcsSharedMemory() {
    if (mData != NULL) {
        free(mData);
        //ALPS05426866 to fix NE during deallocation of memory 
        mData = NULL;
    }
}

void RmcRcsSharedMemory::setState(int state) {

    RFX_LOG_I(RFX_LOG_TAG, "[MEM SET ST] state = %d\n", state);

    mDataReadyCount = state;
}

int RmcRcsSharedMemory::getState() {
    return mDataReadyCount;
}

bool RmcRcsSharedMemory::checkState(int want_state) {

    if (mDataReadyCount == want_state) {
        if (RmcRcsDataThreadController::isLogEnable()) {
            RFX_LOG_I(RFX_LOG_TAG, "[MEM  CHECK] state = %d success \n", mDataReadyCount);
        }
        return true;
    }
    return false;
}

void RmcRcsSharedMemory::setSize(int size) {
    mDatalen = size;
}

void RmcRcsSharedMemory::setData(char* data, int len) {
    mData = (char*) calloc(len, sizeof(char));
    if (mData != NULL) {
        memcpy(mData, data, len);
    }
}

int RmcRcsSharedMemory::getSize(void) {
    return mDatalen;
}

void RmcRcsSharedMemory::getData(char** data) {
    (*data) = mData;
}

void RmcRcsSharedMemory::clearData() {
    free(mData);
}

void RmcRcsSharedMemory::lock(const char* user) {

    pthread_mutex_lock(mPLock);

    if (RmcRcsDataThreadController::isLogEnable()) {
        RFX_LOG_I(RFX_LOG_TAG, "[MEM   LOCK] lock success (%s)", user);
    }
}

void RmcRcsSharedMemory::unlock(const char* user) {

    pthread_mutex_unlock(mPLock);
    if (RmcRcsDataThreadController::isLogEnable()) {
        RFX_LOG_I(RFX_LOG_TAG, "[MEM UNLOCK] unlock success (%s)", user);
    }
}

void RmcRcsSharedMemory::wait(const char* user, int stay_state) {

    while (mDataReadyCount == stay_state) {
        pthread_cond_wait(&mCond, mPLock);
    }

    if (RmcRcsDataThreadController::isLogEnable()) {
        RFX_LOG_I(RFX_LOG_TAG, "[MEM   WAIT] wait success (%s)", user);
    }
}

void RmcRcsSharedMemory::signal(const char* user) {

    pthread_cond_signal(&mCond);
    if (RmcRcsDataThreadController::isLogEnable()) {
        RFX_LOG_I(RFX_LOG_TAG, "[MEM SIGNAL] signal success (%s)", user);
    }
}

sp<RmcRcsSharedMemory> RmcRcsDataThreadController::sShareMemory = new RmcRcsSharedMemory();
pthread_t  RmcRcsDataThreadController::sShareMemoryThd = 0;
pthread_t  RmcRcsDataThreadController::sRilServerThd = 0;
pthread_mutex_t RmcRcsDataThreadController::sMutex = PTHREAD_MUTEX_INITIALIZER;
Ril_Channel_Obj_t *RmcRcsDataThreadController::sChannelObj = NULL;
RmcRcsDataThreadController *RmcRcsDataThreadController::sInstance = NULL;

RmcRcsDataThreadController::RmcRcsDataThreadController() {
}

RmcRcsDataThreadController:: ~RmcRcsDataThreadController() {
}

sp<RmcRcsSharedMemory> RmcRcsDataThreadController::getSharedMem(void) {
    return sShareMemory;
}

void RmcRcsDataThreadController::init() {
    pthread_mutex_lock(&sMutex);
    if (sInstance == NULL) {
        RFX_LOG_I(RFX_LOG_TAG, "RmcRcsDataThreadController init, create instance");
        sInstance = new RmcRcsDataThreadController();
        startThread();
    }
    pthread_mutex_unlock(&sMutex);
}

void RmcRcsDataThreadController::startThread() {

    pthread_attr_t  attr;
    int ret;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    ret = pthread_create(&sRilServerThd, &(attr), rilServerThread, NULL);
    pthread_attr_destroy(&attr);
    if (ret < 0) {
        RFX_LOG_E(RFX_LOG_TAG, "Fail to create RCS ril thread!");
    }

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    ret = pthread_create(&sShareMemoryThd, &(attr), shareMemoryThread, NULL);
    pthread_attr_destroy(&attr);
    if (ret < 0) {
        RFX_LOG_E(RFX_LOG_TAG, "Fail to create RCS share memory thread!");
    }
}

void* RmcRcsDataThreadController::rilServerThread(void *arg) {

    RFX_LOG_I(RFX_LOG_TAG, "[Ril Srv Thd] rilServerThread Start");
    RFX_UNUSED(arg);
    int ret = 0, size = 0;

    //allocate memory
    sChannelObj = (Ril_Channel_Obj_t *)malloc(sizeof(Ril_Channel_Obj_t));
    if (!sChannelObj) {
        RFX_LOG_E(RFX_LOG_TAG, "[Ril Srv Thd] Can't allocate the memory");
        goto free_mem;
    }
    memset(sChannelObj, 0, sizeof(Ril_Channel_Obj_t));

    sChannelObj->channels_size = MAX_CLIENT;

    size = sizeof(Ril_Channel_Client_t) * MAX_CLIENT;
    sChannelObj->channels = (Ril_Channel_Client_t *)malloc(size);
    if (!sChannelObj->channels) {
        RFX_LOG_E(RFX_LOG_TAG, "[Ril Srv Thd] Can't allocate the memory");
        goto free_mem;
    }
    memset(sChannelObj->channels, 0, size);
    //set fd as initial value -1
    for (int i = 0; i < sChannelObj->channels_size; ++i) {
        sChannelObj->channels[i].fd = -1;
    }

    // create server FD
    sChannelObj->fd = android_get_control_socket(RCS_RIL_SOCKET_NAME);

    //do retry if init.rc didn't define socket
    if (sChannelObj->fd < 0) {
        struct sockaddr_un my_addr;
        RFX_LOG_D(RFX_LOG_TAG, "init.rc didn't define, create socket manually");
        memset(&my_addr, 0, sizeof(struct sockaddr_un));
        my_addr.sun_family = AF_UNIX;

        RFX_LOG_D(RFX_LOG_TAG, "socketName is %s", RCS_RIL_SOCKET_NAME);
        strncpy(my_addr.sun_path, RCS_RIL_SOCKET_NAME, sizeof(my_addr.sun_path));
        my_addr.sun_path[0] = 0;

        sChannelObj->fd = socket(AF_UNIX, SOCK_STREAM, 0);
        if (sChannelObj->fd < 0) {
            RFX_LOG_E(RFX_LOG_TAG, "manually listen fail, closed");
            goto free_mem;
        }

        int ret = ::bind(sChannelObj->fd, (struct sockaddr *) &my_addr,
                sizeof(struct sockaddr_un));
        if (ret < 0) {
            RFX_LOG_E(RFX_LOG_TAG, "bind fail, ret = %d, errno = %d, set state to close", ret, errno);
            close(sChannelObj->fd);
            sChannelObj->fd = -1;
        }
    }

    if (sChannelObj->fd < 0) {
        RFX_LOG_E(RFX_LOG_TAG, "[Ril Srv Thd] failed to get socket, errno: %d, %s", errno, strerror(errno));
        goto free_mem;
    }

    RFX_LOG_I(RFX_LOG_TAG, "[Ril Srv Thd] socket fd: %d", sChannelObj->fd);

    // listen client
    ret = listen(sChannelObj->fd, sChannelObj->channels_size);
    if (ret < 0) {
        RFX_LOG_E(RFX_LOG_TAG, "[Ril Srv Thd] failed to listen, errno: %d, %s", errno, strerror(errno));
        goto free_mem;
    }

    pthread_mutex_init(&(sChannelObj->mutex), 0);

    // accept client and start looper to read/write data
    while (1) {
        fd_set  iofds;
        int i = 0;
        int ret = 0;
        int max_fd = sChannelObj->fd;
        int local_errno;
        int bad_fd_handle = 0;
        Ril_Channel_Client_t *clients = sChannelObj->channels;

        FD_ZERO(&iofds);
        FD_SET(sChannelObj->fd, &iofds);

        //set client fd
        for (i = 0; i < sChannelObj->channels_size; ++i) {
            if (clients[i].fd >= 0) {
                if (clients[i].fd > max_fd) {
                    max_fd = clients[i].fd;
                }
                FD_SET(clients[i].fd, &iofds);
            }
        }

        ret = select(max_fd + 1, &iofds, 0, 0, NULL);
        local_errno = errno;

        if (ret < 0) {
            if (local_errno == EINTR) {
                continue;
            }

            RFX_LOG_E(RFX_LOG_TAG, "[Ril Srv Thd] Select fail, ret = %d, errno: %d, %s", ret, errno, strerror(errno));

            if (local_errno == 9) {
                //Bad file descriptor(9)
                for (i = 0; i < sChannelObj->channels_size; ++i) {
                    Ril_Channel_Client_t *client = &(clients[i]);
                    if (client->fd >= 0 && FD_ISSET(client->fd, &iofds)) {
                        int tmp_client_fd = client->fd;
                        RFX_LOG_E(RFX_LOG_TAG, "[Ril Srv Thd] Bad file descriptor [fd:%d, idx:%d]", client->fd, i);
                        client->fd = -1;
                        client->processing = false;
                        memset(&client->uaEvent, 0, sizeof(UaChannel_Data_t));
                        shutdown(tmp_client_fd, SHUT_RDWR);
                        close(tmp_client_fd);
                        bad_fd_handle = 1;
                        break;
                    }
                }
            }

            if (bad_fd_handle == 1) {
                continue;
            } else {
                goto free_mem;
            }
        } else if (ret == 0) {
            continue;
        }

        if (FD_ISSET(sChannelObj->fd, &iofds)) {
            int tmp_fd = 0;
            int tmp_index = -1;
            struct sockaddr_in tmp_addr;
            socklen_t tmp_addrlen = sizeof(struct sockaddr);

            tmp_fd = accept(sChannelObj->fd, (sockaddr *)&tmp_addr, (socklen_t *)&tmp_addrlen);
            if (tmp_fd < 0) {
                RFX_LOG_E(RFX_LOG_TAG, "[Ril Srv Thd] accept error, errno = %s(%d)", strerror(errno), errno);
                continue;
            }

            for (i = 0 ; i < sChannelObj->channels_size; ++i) {
                if (clients[i].fd < 0) {
                    pthread_mutex_init(&(clients[i].mutex), 0);
                    clients[i].fd = tmp_fd;
                    tmp_index = i;
                    break;
                }
            }

            if (tmp_index < 0) {
                shutdown(tmp_fd, SHUT_RDWR);
                close(tmp_fd);
                RFX_LOG_E(RFX_LOG_TAG, "[Ril Srv Thd]Connection pool is full");
            } else {
                RFX_LOG_E(RFX_LOG_TAG, "[Ril Srv Thd]Connection from %s:%d [fd:%d, idx:%d]",
                    inet_ntoa(tmp_addr.sin_addr), ntohs(tmp_addr.sin_port), tmp_fd, tmp_index);
            }
        }

        for (i = 0 ; i < sChannelObj->channels_size; ++i) {
            Ril_Channel_Client_t *client = &(clients[i]);
            UaChannel_Data_t *uaEvent = &client->uaEvent;
            char *dataBuff = client->buff;

            if (client->fd >= 0 && FD_ISSET(client->fd, &iofds)) {
                int bytesToProcess = 0;
                int leastToProcess = (client->processing) ? uaEvent->len : UA_CHANNEL_HEADER_LEN;
                int read;

                while ((read = recv(client->fd, &dataBuff[bytesToProcess], sizeof(client->buff)-bytesToProcess, 0)) > 0) {
                    bytesToProcess += read;
                    RFX_LOG_I(RFX_LOG_TAG, "[%d]client[%d] read from UA [%d]bytes, bytesToProcess[%d]", client->account, i, read, bytesToProcess);

                    while (bytesToProcess >= leastToProcess) {
                        RFX_LOG_I(RFX_LOG_TAG, "leastToProcess[%d]", leastToProcess);

                        if (!client->processing) {
                            memcpy((char *)uaEvent, dataBuff, UA_CHANNEL_HEADER_LEN);
                            dataBuff += leastToProcess;
                            bytesToProcess -= leastToProcess;
                            if (uaEvent->len > 0) {
                                uaEvent->data = (char *)calloc(uaEvent->len + 1, 1);
                                if (!uaEvent->data) {
                                    RFX_LOG_E(RFX_LOG_TAG, "[Ril Srv Thd]Can't allocate memory");
                                }
                            }
                            leastToProcess = uaEvent->len;
                            client->processing = true;
                        } else {
                            if (uaEvent->data) {
                                memcpy(uaEvent->data, dataBuff, uaEvent->len);
                            }
                            dataBuff += leastToProcess;
                            bytesToProcess -= leastToProcess;
                            processUaEvent(client);
                            client->processing = false;
                            leastToProcess = UA_CHANNEL_HEADER_LEN;
                        }
                    }
                    if (bytesToProcess > 0) {
                        memmove(client->buff, dataBuff, bytesToProcess);
                    } else if (!client->processing) {
                        break;
                    }
                    dataBuff = client->buff;
                }
                if (read <= 0 && errno != EINTR) {
                    if (uaEvent->data)
                        free(uaEvent->data);
                    int tmp_client_fd = client->fd;

                    RFX_LOG_E(RFX_LOG_TAG, "Read from UA fail, fd:[%d], ret[%d], errno[%d]", client->fd, read, errno);
                    client->fd = -1;
                    client->processing = false;
                    memset(&clients->uaEvent, 0, sizeof(UaChannel_Data_t));
                    shutdown(tmp_client_fd, SHUT_RDWR);
                    close(tmp_client_fd);
                }
            }
        }
    }

    RFX_LOG_E(RFX_LOG_TAG, "rilServerThread quit");

    //close server fd
    close(sChannelObj->fd);
    sChannelObj->fd = -1;

free_mem :
    if (sChannelObj && sChannelObj->channels)
        free(sChannelObj->channels);
    if (sChannelObj) {
        if (sChannelObj->fd >= 0)
            close(sChannelObj->fd);
        free(sChannelObj);
    }
    RFX_LOG_E(RFX_LOG_TAG, "[Ril Srv Thd] end of server thread, should not happen");

    return 0;
}

void RmcRcsDataThreadController::processUaEvent(Ril_Channel_Client_t *client) {
    UaChannel_Data_t *chnlData = &client->uaEvent;

    RFX_LOG_I(RFX_LOG_TAG, "[%d]processUaEvent -> type[%d], len[%d], flag[%d], account[%d]",
            client->account, chnlData->type, chnlData->len, chnlData->flag, chnlData->account);

    if (chnlData->type == VOLTE_REQ_SIPTX_CREATE) {
        VoLTE_Stack_Channel_Info_t *info = (VoLTE_Stack_Channel_Info_t *)chnlData->data;
        if (info->type == (VoLTE_Stack_UA_RCS_Proxy | VoLTE_UA_MAGIC_NUMBER)) {
            client->type = VoLTE_Stack_UA_RCS_Proxy;
        } else if (info->type == (VoLTE_Stack_UA_RCS_Proxy_Sip | VoLTE_UA_MAGIC_NUMBER)) {
            client->type = VoLTE_Stack_UA_RCS_Proxy_Sip;
        } else {
            RFX_LOG_E(RFX_LOG_TAG, "wrong type(%d) for VOLTE_REQ_SIPTX_CREATE", info->type);
            return;
        }
    }
    if (chnlData->type == VOLTE_REQ_SIPTX_CREATE
            || chnlData->type == VOLTE_REQ_SIPTX_REG_ADD_BIND) {
        client->account = chnlData->account;
    }

    // dispatch to md
    int dataSize = chnlData->len + MD_CHANNEL_HEADER_LEN;
    char* mdData = (char *)calloc(dataSize, 1);
    if (!mdData) {
        RFX_LOG_E(RFX_LOG_TAG, "processUaEvent -> can't allocate memory");
        return;
    }
    ((int *)mdData)[0] = chnlData->type;
    ((int *)mdData)[1] = chnlData->len;
    ((int *)mdData)[2] = chnlData->flag;
    ((int *)mdData)[3] = client->account;
    ((int *)mdData)[4] = client->type;

    if (chnlData->len > 0) {
        memcpy(&mdData[MD_CHANNEL_HEADER_LEN], chnlData->data, chnlData->len);
        free(chnlData->data);
    }

    memset(&client->uaEvent, 0, sizeof(client->uaEvent));

    sp<RfxMclMessage> rcsmsg = RfxMclMessage::obtainEvent(RFX_MSG_EVENT_RCS_SEND_MSG,
            RfxRcsSendMsgData(mdData, dataSize), RIL_CMD_PROXY_2, 0);
    RfxMclDispatcherThread::enqueueMclMessage(rcsmsg);
    free(mdData);
}

//return client channel obj
int RmcRcsDataThreadController::getClientIndex(int account, int uaType) {
    if (!sChannelObj) {
        return -1;
    }
    if (!sChannelObj->channels) {
        return -1;
    }

    for (int i = 0; i < sChannelObj->channels_size; ++i) {
        Ril_Channel_Client_t *client = &sChannelObj->channels[i];
        if (client->fd >= 0
            && client->type == uaType
            && (client->account == account || client->account < 0)) {
                return i;
        }
    }

    return -1;
}

void * RmcRcsDataThreadController::shareMemoryThread(void *arg) {

    RFX_LOG_I(RFX_LOG_TAG, "[Share Mem Thd] Start");

    RFX_UNUSED(arg);

    while(1) {

        //if (sIsVtConnected == 0) {
            //RFX_LOG_D(RFX_LOG_TAG, "[RIL IMCB THD] sIsVtConnected : %d", sIsVtConnected);
            //usleep(500 * 1000);
            //continue;
        //}

        sShareMemory->lock("ril-md thread");

        sShareMemory->wait("ril-md thread", RCS_RIL_SHARE_DATA_STATUS_RECV_NONE);

        char *pRecvMsg;
        int size;
        UaChannel_Data_t recvData;
        int uaType; /* VoLTE_Stack_UA_Type_e */

        sShareMemory->getData(&pRecvMsg);
        size = sShareMemory->getSize();

        memset(&recvData, 0, sizeof(recvData));
        recvData.type = ((int *)pRecvMsg)[0];
        recvData.len = ((int *)pRecvMsg)[1];
        recvData.flag = ((int *)pRecvMsg)[2];
        recvData.account = ((int *)pRecvMsg)[3];
        uaType = ((int *)pRecvMsg)[4];
        RFX_LOG_I(RFX_LOG_TAG, "Received msgId[%d] from MD length[%d], uaType[%d] account[%d]",
                recvData.type, size, uaType, recvData.account);

        if (size != (recvData.len + (int)(MD_CHANNEL_HEADER_LEN))) {
            RFX_LOG_E(RFX_LOG_TAG, "Received from MD data length wrong");

            sShareMemory->clearData();
            sShareMemory->setState(RCS_RIL_SHARE_DATA_STATUS_RECV_NONE);
            sShareMemory->unlock("ril-md thread");
            continue;
        }

        if (recvData.len > 0) {
            recvData.data = (char* )calloc(recvData.len, sizeof(char));
            if (!recvData.data) {
                RFX_LOG_E(RFX_LOG_TAG, "[Share Mem Thd] Can't allocate the memory");

                sShareMemory->clearData();
                sShareMemory->setState(RCS_RIL_SHARE_DATA_STATUS_RECV_NONE);
                sShareMemory->unlock("ril-md thread");
                continue;
            }
            memcpy(recvData.data, pRecvMsg + MD_CHANNEL_HEADER_LEN, recvData.len);
        }

        sendDataToUA(&recvData, recvData.account, uaType);

        if (recvData.data) {
            free(recvData.data);
        }

        sShareMemory->clearData();

        sShareMemory->setState(RCS_RIL_SHARE_DATA_STATUS_RECV_NONE);

        sShareMemory->unlock("ril-md thread");

    }
    RFX_LOG_E(RFX_LOG_TAG, "[Share Mem Thd]end of readerLooper, should not happen");

    return 0;
}

//write data to client UA
int RmcRcsDataThreadController::sendDataToUA(UaChannel_Data_t *data, int account, int uaType) {
    Ril_Channel_Client_t *client = 0;
    int ret = 0;
    int id = 0;

    int index = getClientIndex(account, uaType);
    if (index < 0) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d]Client not found for ua type[%d]", account, uaType);
        return -1;
    }
    client = &sChannelObj->channels[index];
    RFX_LOG_I(RFX_LOG_TAG, "[%d]send msgId[%d] to UA client[%d] with datalen[%d]",
            client->account, data->type, index, data->len);

    pthread_mutex_lock(&(client->mutex));
    id = client->fd;
    if (id < 0) {
        RFX_LOG_E(RFX_LOG_TAG, "channel fd (%d) < 0, channel = %p", id, client);
        pthread_mutex_unlock(&(client->mutex));
        return -1;
    }

    do {
        ret = fsend(id, (char *)data, UA_CHANNEL_HEADER_LEN);
        if (ret != UA_CHANNEL_HEADER_LEN) {
            ret = -1;
            break;
        }

        if (data->len && data->data) {
            ret = fsend(id, (char *)data->data, data->len);
            if (ret != data->len) {
                ret = -1;
                break;
            }
        } else if (data->len || data->data) {
            RFX_LOG_E(RFX_LOG_TAG, "Channel send fail, length or data is null");
            ret = -1;
            break;
        }
        ret = 0;
    } while (0);

    pthread_mutex_unlock(&(client->mutex));

    return ret;
}

int RmcRcsDataThreadController::fsend(int fd, char *data, int len) {
    int size = 0, ret = 0;
    int write_size = 0;
    int local_errno;

    if (fd <= 0) {
        return -1;
    }

    while (size < len) {
        write_size = len - size;

        ret = send(fd, data + size, write_size, 0);
        local_errno = errno;

        if (ret > 0) {
            size += ret;
        } else {
            if (errno == EINTR) {
                continue;
            }
            else if (errno == EPIPE) {
                ;
            }
            RFX_LOG_E(RFX_LOG_TAG, "Can't write the data to channel, error = (%d), fd = (%d)", local_errno, fd);
            break;
        }
    }
    return size;
}

void RmcRcsDataThreadController::sendMsgToShareMemory(char* outBuffer, int length, const char* user) {
    sp<RmcRcsSharedMemory> Mem  = getSharedMem();

    while (1) {
        if (!Mem->checkState(RCS_RIL_SHARE_DATA_STATUS_RECV_NONE)) {
            // wait finish sending data to UA
            usleep(200);

        } else {
            Mem->lock(user);
            break;
        }
    }

    Mem->setSize(length);
    Mem->setData(outBuffer, length);

    Mem->setState(RCS_RIL_SHARE_DATA_STATUS_RECV_DATA);

    Mem->signal(user);

    Mem->unlock(user);

}

bool RmcRcsDataThreadController::isLogEnable() {
    char enableLog[100] = {0};

    rfx_property_get("persist.vendor.rilrcs.log_enable", enableLog, "0");
    return (atoi(enableLog) == 1)? true: false;
}
