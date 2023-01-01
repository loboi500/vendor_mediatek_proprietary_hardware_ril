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

#include "RmcVtReqHandler.h"
#include "RmcVtDataThreadController.h"

#include "RfxVtSendMsgData.h"
#include "RmcVtMsgParser.h"

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

#define RFX_LOG_TAG "VT RIL RMC"

/*****************************************************************************
 * Class RmcVtReqHandler
 *****************************************************************************/
RFX_IMPLEMENT_HANDLER_CLASS(RmcVtReqHandler, RIL_CMD_PROXY_IMS);

static int mSimOpIdTable[MAX_SIM_COUNT] = {0};

RmcVtReqHandler::RmcVtReqHandler(int slot_id, int channel_id)
: RfxBaseHandler(slot_id, channel_id) {

    RFX_LOG_I(RFX_LOG_TAG, "[RMC VT REQ HDLR] RmcVtReqHandler create (slot_id = %d)", slot_id);

    if (!RmcVtReqHandler::isImsVideoCallon()) {
        return;
    }

    const int requestList[] = {
        RFX_MSG_REQUEST_GET_INFO,
        RFX_MSG_REQUEST_UPDATE_OPID,
    };

    registerToHandleRequest(requestList, sizeof(requestList)/sizeof(int));

    const int CommonEventList[] = {
        RFX_MSG_EVENT_CALL_STATUS_UPDATE,
        RFX_MSG_EVENT_VT_SEND_MSG,
        RFX_MSG_EVENT_VT_COMMON_DATA
    };

    registerToHandleEvent(CommonEventList, sizeof(CommonEventList) / sizeof(int));

    const int imsEventList[] = {
        RFX_MSG_EVENT_IMS_DATA,
    };

    registerToHandleEvent(RIL_IMS_Client_VILTE, imsEventList, sizeof(imsEventList) / sizeof(int));

    // create thread controller
    if (slot_id == 0) {
        mThdController = new RmcVtDataThreadController();
        mThdController->start();
        reportRildStateReady(); //report rild ready
    }
}

RmcVtReqHandler::~RmcVtReqHandler() {
}

bool RmcVtReqHandler::isImsVideoCallon(void) {
    bool isViLTESupport = RfxRilUtils::isVilteSupport();
    bool isViWiFiSupport = RfxRilUtils::isViwifiSupport();

    if (isViLTESupport || isViWiFiSupport) {
        if (isVTLogEnable()) {
            RFX_LOG_I(RFX_LOG_TAG, "[RMC VT REQ HDLR] isImsVideoCallon : True");
        }
        return true;
    } else {
        if (isVTLogEnable()) {
            RFX_LOG_I(RFX_LOG_TAG, "[RMC VT REQ HDLR] isImsVideoCallon : False");
        }
        return false;
    }
}

bool RmcVtReqHandler::isVTLogEnable(void) {
    char vt_log[100] = {0};

    rfx_property_get("persist.vendor.rilvt.log_enable", vt_log, "0");
    return (atoi(vt_log) == 1)? true: false;
}

void RmcVtReqHandler::onHandleRequest(const sp<RfxMclMessage>& msg) {

    int request = msg->getId();

    RFX_LOG_I(RFX_LOG_TAG, "[Handle REQ] request = %d", request);

    switch (request) {
        case RFX_MSG_REQUEST_GET_INFO:
            handleRequestGetInfo(msg);
            break;
        case RFX_MSG_REQUEST_UPDATE_OPID:
            handleRequestUpdateOpid(msg);
            break;
        default:
            RFX_LOG_I(RFX_LOG_TAG, "unknown request, ignore!");
            break;
    }
}

void RmcVtReqHandler::onHandleEvent(const sp<RfxMclMessage> & msg) {

    int event = msg->getId();

    RFX_LOG_I(RFX_LOG_TAG, "[Handle EVT] event = %d", event);

    switch (event) {
        case RFX_MSG_EVENT_CALL_STATUS_UPDATE:
            handleEventCallStatusUpdate(msg);
            break;
        case RFX_MSG_EVENT_VT_SEND_MSG:
            handleEventVtSendMsg(msg);
            break;
        case RFX_MSG_EVENT_IMS_DATA:
        case RFX_MSG_EVENT_VT_COMMON_DATA:
            handleEventVtReceiveMsg(msg);
            break;
        default:
            RFX_LOG_I(RFX_LOG_TAG, "[Handle EVT] unknown event, ignore!");
            break;
    }
}

void RmcVtReqHandler::handleRequestGetInfo(const sp<RfxMclMessage>& msg) {

    const RIL_VT_CALL_STATUS_UPDATE *pRspData = (const RIL_VT_CALL_STATUS_UPDATE *)msg->getData()->getData();
    int call_id = pRspData->call_id;
    int call_state = pRspData->call_state;

    sp<RfxAtResponse> p_response;
    sp<RfxMclMessage> response;
    sp<RfxMclMessage> urc;
    int cause = 0;

    // send AT cmd
    /*
    p_response = atSendCommand(String8::format("AT+XXXXX=%d", call_state));

    if (p_response->isAtResponseFail()) {
                cause = p_response->atGetCmeError();
        RFX_LOG_E(RFX_LOG_TAG, "handleRequestGetInfo: response error");
        goto error;
    }
    */

    // send URC
    /*
    urc = RfxMclMessage::obtainUrc(RFX_MSG_URC_GET_INFO, m_slot_id, RfxIntsData(&allowed, 1));
    responseToTelCore(urc);
    */

    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS, RfxVoidData(), msg);
    responseToTelCore(response);

    return;
/*
error:
    RFX_LOG_E(RFX_LOG_TAG, "[GET  INFO ] ERROR cause= %d", cause);
    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_GENERIC_FAILURE, RfxIntsData(&cause, 1), msg, true);
    responseToTelCore(response);
    return;
*/
}

void RmcVtReqHandler::handleEventCallStatusUpdate(const sp<RfxMclMessage>& msg) {

    const RIL_VT_CALL_STATUS_UPDATE *pRspData = (const RIL_VT_CALL_STATUS_UPDATE *)msg->getData()->getData();
    int call_id = pRspData->call_id;
    int call_state = pRspData->call_state;

    RFX_LOG_D(RFX_LOG_TAG, "[STATUS UPD] call_id = %d, call_state = %d", call_id, call_state);

    return;
}

void RmcVtReqHandler::handleEventVtSendMsg(const sp<RfxMclMessage>& msg) {
    const RIL_VT_SERVICE_MSG *pSendMsg = (const RIL_VT_SERVICE_MSG *)msg->getData()->getData();

    RFX_LOG_D(RFX_LOG_TAG, "[VTREQ SENT] pSendMsg->size = %d, pSendMsg->data = %lu",
                pSendMsg->size, (unsigned long) pSendMsg->data);

    int msgId = (* ((int*)pSendMsg->data));
    if (msgId == MSG_ID_WRAP_IMSVT_RILD_VTSERVICE_STATUS) {

        VT_STATUS_REQ* srvStatusStruct = (VT_STATUS_REQ* )(pSendMsg->data + 8);
        if (1 == srvStatusStruct->status) {
            RFX_LOG_I(RFX_LOG_TAG, "[VTREQ SENT] RILD_IMS_CLIENT_READY");

            // Notify RIL FWK that we are ready to recv message (VTService).
            // Sometimes remote side may be ready earler than us and send message firstly
            // so we need to tell FWK when we can recv message or the earlier message will lost.
            sendUserData(RIL_IMS_Client_VILTE, RIL_IMS_CLIENT_READY, NULL, 0);
        } else {
            RFX_LOG_I(RFX_LOG_TAG, "[VTREQ SENT] RILD_IMS_CLIENT_NOT_READY");
            sendUserData(RIL_IMS_Client_VILTE, RIL_IMS_CLIENT_NOT_READY, NULL, 0);
        }

        return;
    } else if (msgId == MSG_ID_WRAP_IMSVT_RILD_GET_OP_ID_REQ) {
        VT_GET_OP_ID_REQ* srvOpIdStruct = (VT_GET_OP_ID_REQ* )(pSendMsg->data + 8);
        int sim_slot_id = srvOpIdStruct->sim_slot_id;

        RFX_LOG_I(RFX_LOG_TAG, "sim_slot_id = %d", sim_slot_id);

        if (sim_slot_id < MAX_SIM_COUNT && mSimOpIdTable[sim_slot_id] != 0) {
            //report only have valid oprator id
            reportOperatorId(sim_slot_id, mSimOpIdTable[sim_slot_id]);
        } else {
            RFX_LOG_I(RFX_LOG_TAG, "invalid operator id!!!");
        }
        return;
    }

    if (msgId == MSG_ID_WRAP_IMSVT_IMCB_GET_CAP_RSP) {

        VT_IMCB_CAP* capRspStruct = (VT_IMCB_CAP* )(pSendMsg->data + 8);

        // temp log for get cap
        if (isVTLogEnable()) {

            RFX_LOG_I(RFX_LOG_TAG, "[VTREQ SENT] accout_id = %d", capRspStruct->accout_id);
            RFX_LOG_I(RFX_LOG_TAG, "[VTREQ SENT] video_cap_num = %d", capRspStruct->video_cap_num);
            RFX_LOG_I(RFX_LOG_TAG, "[VTREQ SENT] profile_level_id = %d", capRspStruct->video_cap[0].profile_level_id);
            RFX_LOG_I(RFX_LOG_TAG, "[VTREQ SENT] max_recv_level = %d", capRspStruct->video_cap[0].max_recv_level);
            RFX_LOG_I(RFX_LOG_TAG, "[VTREQ SENT] packetization_mode = %d", capRspStruct->video_cap[0].packetization_mode);

            RFX_LOG_I(RFX_LOG_TAG, "[VTREQ SENT] bitrate_info format = %d", capRspStruct->bitrate_info[0].format);
            RFX_LOG_I(RFX_LOG_TAG, "[VTREQ SENT] bitrate_info profile = %d", capRspStruct->bitrate_info[0].profile);
            RFX_LOG_I(RFX_LOG_TAG, "[VTREQ SENT] bitrate_info level = %d", capRspStruct->bitrate_info[0].level);
            RFX_LOG_I(RFX_LOG_TAG, "[VTREQ SENT] bitrate_info minbitrate = %d", capRspStruct->bitrate_info[0].minbitrate);
            RFX_LOG_I(RFX_LOG_TAG, "[VTREQ SENT] bitrate_info bitrate = %d", capRspStruct->bitrate_info[0].bitrate);

        }
    }

    // send to RIL FWK
    sendUserData(RIL_IMS_Client_VILTE, (unsigned char* ) pSendMsg->data, pSendMsg->size);

    return;
}

void RmcVtReqHandler::handleEventVtReceiveMsg(const sp<RfxMclMessage>& msg) {
    const char *pRecvMsg = (const char *)msg->getData()->getData();
    int length = msg->getData()->getDataLength();

    RFX_LOG_I(RFX_LOG_TAG, "[VTREQ RECV] data length = %d, slot = %d\n", length, m_slot_id);

    //Add operator id for MSG_ID_WRAP_IMSVT_IMCB_GET_CAP_IND
    int msgId = (* ((int*)pRecvMsg));
    if (msgId == MSG_ID_WRAP_IMSVT_IMCB_GET_CAP_IND) {

        VT_IMCB_CAPIND* capIndStruct = (VT_IMCB_CAPIND* )(pRecvMsg + 8);
        int sim_slot_id = capIndStruct->sim_slot_id;

        // Here is only for MD 93, we need to add operator id when receiving cap indication here.
        // Before MD 92, it will use legancy rild and not enter here.
        // After MD 95, MD will send cap indication with operator id.
        if (capIndStruct->operator_code == 0) {
            // operator id as
            // 0: SIM not ready
            // 8: Default id -> Not found in mapping table, SIM card not detected
            // > 0: Correct opid
            if (mSimOpIdTable[sim_slot_id] == 0) {
                mPendingCapReqBySim[sim_slot_id]++;
                RFX_LOG_I(RFX_LOG_TAG, "sim card %d opid not ready, pending request: %d\n", sim_slot_id, mPendingCapReqBySim[sim_slot_id]);
                return;

            } else {
                if (isVTLogEnable()) {
                    RFX_LOG_I(RFX_LOG_TAG, "update CAP indication message[%d] as operator_code = %d\n", sim_slot_id, mSimOpIdTable[sim_slot_id]);
                }
                capIndStruct->operator_code = mSimOpIdTable[sim_slot_id];
            }
        }
    }

    sendMsgToVTS((char*)pRecvMsg, length, "handleRequestVtReceiveMsg");

    return;
}

void RmcVtReqHandler::handleRequestUpdateOpid(const sp<RfxMclMessage>& msg) {
    int *data = (int *)msg->getData()->getData();
    int slot_id = ((int *)data)[0];
    int operator_id = ((int *)data)[1];
    mSimOpIdTable[slot_id] = operator_id;
    RFX_LOG_I(RFX_LOG_TAG, "set mSimOpIdTable[%d] = %d\n", slot_id, operator_id);

    // Resend cap indication when pending request
    if (mSimOpIdTable[slot_id] != 0) {

        while(mPendingCapReqBySim[slot_id] > 0) {

            if (isVTLogEnable()) {
                RFX_LOG_I(RFX_LOG_TAG, "Handle SIM%d pending request: %d\n", slot_id, mPendingCapReqBySim[slot_id]);
            }

            // Prepare VT_IMCB_CAPIND structure
            char* outBuffer = NULL;
            int msgType = MSG_ID_WRAP_IMSVT_IMCB_GET_CAP_IND;
            int capIndLength = sizeof(VT_IMCB_CAPIND);
            int length = capIndLength + 1 + 8;

            outBuffer = (char* ) calloc(length, sizeof(char));
            if (outBuffer == NULL) {
                RFX_LOG_I(RFX_LOG_TAG, "fail to calloc outBufferf");
                return;
            }

            (* ((int*)outBuffer))       = msgType;
            (* ((int*)outBuffer + 1))   = capIndLength;

            VT_IMCB_CAPIND CapInd;
            memset(&CapInd, 0, capIndLength);
            CapInd.sim_slot_id = slot_id;
            CapInd.operator_code = mSimOpIdTable[slot_id];

            memcpy(outBuffer + 8, &CapInd, capIndLength);

            sendMsgToVTS(outBuffer, length, "handleRequestUpdateOpid");
            free(outBuffer);

            mPendingCapReqBySim[slot_id]--;
        }
    }

    sp<RfxMclMessage> response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS, RfxVoidData(), msg);
    responseToTelCore(response);
}

void RmcVtReqHandler::reportRildStateReady() {

    if (isVTLogEnable()) {
        RFX_LOG_I(RFX_LOG_TAG, "reportRildStateReady");
    }

    char* outBuffer = NULL;
    int msgType = MSG_ID_WRAP_IMSVT_RILD_RILD_STATUS;
    int RildIndLength = sizeof(VT_RIL_STATUS_IND);
    int length = RildIndLength + 1 + 8;

    outBuffer = (char* ) calloc(length, sizeof(char));
    if (outBuffer == NULL) {
        RFX_LOG_I(RFX_LOG_TAG, "fail to calloc outBufferf");
        return;
    }

    (* ((int*)outBuffer))       = msgType;
    (* ((int*)outBuffer + 1))   = RildIndLength;

    VT_RIL_STATUS_IND RildStatusInd;
    memset(&RildStatusInd, 0, RildIndLength);

    RildStatusInd.sim_slot_id = 0;
    RildStatusInd.status = 1;  // 1:Ready, 0:Not readay

    memcpy(outBuffer + 8, &RildStatusInd, RildIndLength);

    sendMsgToVTS(outBuffer, length, "ReportVTRildStatus");
    free(outBuffer);

}

void RmcVtReqHandler::reportOperatorId(int slot_id, int op_id) {

    RFX_LOG_I(RFX_LOG_TAG, "reportOperatorId");

    char* outBuffer = NULL;
    int msgType = MSG_ID_WRAP_IMSVT_RILD_GET_OP_ID_RSP;
    int OpIdRspLength = sizeof(VT_GET_OP_ID_RSP);
    int length = OpIdRspLength + 1 + 8;

    outBuffer = (char* ) calloc(length, sizeof(char));
    if (outBuffer == NULL) {
        RFX_LOG_I(RFX_LOG_TAG, "fail to calloc outBufferf");
        return;
    }

    (* ((int*)outBuffer))       = msgType;
    (* ((int*)outBuffer + 1))   = OpIdRspLength;

    VT_GET_OP_ID_RSP OpIdRsp;
    memset(&OpIdRsp, 0, OpIdRspLength);

    OpIdRsp.sim_slot_id = slot_id;
    OpIdRsp.op_id = op_id;

    memcpy(outBuffer + 8, &OpIdRsp, OpIdRspLength);

    sendMsgToVTS(outBuffer, length, "reportOperatorId");
    free(outBuffer);
}


void RmcVtReqHandler::sendMsgToVTS(char* outBuffer, int length, const char* user) {
    sp<RmcVtSharedMemory> Mem  = RmcVtDataThreadController::getSharedMem();

    while (1) {
        if (!Mem->checkState(VT_RIL_SHARE_DATA_STATUS_RECV_NONE)) {
            // wait VT RIL thread finish sending data to vt service
            usleep(200);

        } else {
            Mem->lock(user);
            break;
        }
    }

    Mem->setSlotId(m_slot_id);
    Mem->setSize(length);
    Mem->setData(outBuffer, length);

    Mem->setState(VT_RIL_SHARE_DATA_STATUS_RECV_DATA);

    Mem->signal(user);

    Mem->unlock(user);

}
