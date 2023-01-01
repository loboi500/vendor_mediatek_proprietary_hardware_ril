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

#include "RmmOemUrcHandler.h"
#include "RfxIntsData.h"
#include "RfxStringData.h"
#include "RfxRawData.h"
#include <libmtkrilutils.h>
#include "RfxMclDispatcherThread.h"
#include "RfxMipcData.h"
#include <RfxDispatchThread.h>

#define RFX_LOG_TAG "RmmOemUrcHandler"

// RFCable status reader
static int sRFCableStatusFd = -1;
static void *rfCableStatusReaderLoop(void *param);

// register handler to channel
RFX_IMPLEMENT_HANDLER_CLASS(RmmOemUrcHandler, RIL_CMD_PROXY_URC);

RFX_REGISTER_DATA_TO_URC_ID(RfxIntsData, RFX_MSG_UNSOL_TX_POWER);
RFX_REGISTER_DATA_TO_URC_ID(RfxIntsData, RFX_MSG_UNSOL_TX_POWER_STATUS);
RFX_REGISTER_DATA_TO_URC_ID(RfxRawData, RFX_MSG_UNSOL_OEM_HOOK_RAW);

RmmOemUrcHandler::RmmOemUrcHandler(int slot_id, int channel_id) :
        RfxBaseHandler(slot_id, channel_id) {
    const char* urc[] = {
        (char *) "+EMCFRPT",
        (char *) "+EDMFAPP",
        /* For oemurc function, please replace "+XXXX" with the
         at command that you want to send to framework. */
        //(char *) "+XXXX",
    };

    registerToHandleURC(urc, sizeof(urc)/sizeof(char*));

    const int mipcUrc[] = {
        MIPC_SYS_WARNING_IND,
        MIPC_SYS_NV_SIG_ERR_IND,
        MIPC_NW_ETXPWR_IND,
        MIPC_NW_ETXPWRSTUS_IND,
        MIPC_CALL_MT_SIP_INVITE_IND,
    };
    registerToHandleMipcURC(mipcUrc, sizeof(mipcUrc) / sizeof(int));

    memset(&mRFCableStatsuReaderThread, 0, sizeof(pthread_t));
    int mainSlotId = RfxRilUtils::getMajorSim() - 1;
    if (mainSlotId == slot_id) {
        initRFCableStatusReader();
    }
    for (int i = 0; i < MTSIPINVIT_NOTIFY_BUFFER_LEN; i++) {
        mMTSipTepData[i] = NULL;
    }
}

RmmOemUrcHandler::~RmmOemUrcHandler() {
}

void RmmOemUrcHandler::onHandleUrc(const sp<RfxMclMessage>& msg) {
    if (msg->getMipcData() != NULL) {
        int mipcMsgId = msg->getMipcData()->getMipcMsgId();
        if (mipcMsgId == MIPC_SYS_WARNING_IND) {
            handleEWarning(msg->getMipcData());
        } else if (mipcMsgId == MIPC_SYS_NV_SIG_ERR_IND) {
            handleNvErr(msg->getMipcData());
        } else if (mipcMsgId == MIPC_NW_ETXPWRSTUS_IND) {
            handleTXPowerStatus(msg->getMipcData());
        } else if (mipcMsgId == MIPC_NW_ETXPWR_IND) {
            handleTXPower(msg->getMipcData());
        } else if (mipcMsgId == MIPC_CALL_MT_SIP_INVITE_IND) {
            handleRCSMTSIPInfo(msg->getMipcData());
        }
        return;
    }

    RfxAtLine *line = msg->getRawUrc();
    char *data = line->getLine();
    if (strStartsWith(data, "+EMCFRPT")
            || strStartsWith(data, "+EDMFAPP")) {
        handleOemUrc(line);
    } /* For oemurc function, please replace "+XXXX" with the
         at command that you want to send to framework.
       */
      /*
        else if (strStartsWith(data, "+XXXX")) {
        handleOemUrc(line);
    } */
    else {
        RFX_LOG_E(RFX_LOG_TAG, "we can not handle this raw urc?! %s", data);
    }
}

void RmmOemUrcHandler::handleEWarning(RfxMipcData* data) {
       char* t_result_ptr;
       uint16_t t_system_len = 0;
       char warningMessage[254 + 1] = {0};
       t_result_ptr = (char*)data->getMipcVal(MIPC_SYS_WARNING_IND_T_INFO, &t_system_len);
       if (NULL != t_result_ptr) {
           strncpy(warningMessage, t_result_ptr, 254);
           warningMessage[254] = '\0';
       }

       char modemVersion[256] = {0};
       getMSimProperty(m_slot_id, (char*)"gsm.version.baseband", modemVersion);
       RFX_LOG_D(RFX_LOG_TAG, "handleEWarning, modem version = %s, warningMessage = %s",
               modemVersion, warningMessage);
       RfxRilUtils::handleAee(warningMessage, modemVersion);
}

/**
* Modem will send +ETXPWR after receiving AT+ERFTX
*/
void RmmOemUrcHandler::handleTXPower(RfxMipcData* data) {

    // response[0]: act (rat);
    // resposne[1]: txPower;
    int response[2] = {0, 0};
    sp<RfxMclMessage> urc;

    uint32_t act = data->getMipcUint32Val(MIPC_NW_ETXPWR_IND_T_ACT, 0);
    int32_t txPower = data->getMipcInt32Val(MIPC_NW_ETXPWR_IND_T_TX_POWER, 0);

    response[0] = static_cast<int>(act);
    response[1] = static_cast<int>(txPower);
    RFX_LOG_D(RFX_LOG_TAG, "handleTXPower: %d, %d", response[0], response[1]);
    urc = RfxMclMessage::obtainUrc(RFX_MSG_UNSOL_TX_POWER, m_slot_id, RfxIntsData(response, 2));
    responseToTelCore(urc);
    return;
}

/**
 * +ETXPWRSTUS: <event>, <sar_scenario_index>
 * <event>: Integer; Indicates the TX Power high or low
 *              0    TX power low indication
 *              1    TX power high indication
 *              FF  default value when there is no indication received from MMRF yet.
 * <sar_scenario_index>: Integer; Indicates the SAR scenario index
 *              FF ¨C If the SAR is not configured yet.
 */
void RmmOemUrcHandler::handleTXPowerStatus(RfxMipcData* data) {
    // response[0]: event (Indicates the TX Power high or low)
    // resposne[1]: sar_scenario_index(Indicates the SAR scenario index)
    int response[2] = {0, 0};
    sp<RfxMclMessage> urc;

    uint16_t event = data->getMipcUint16Val(MIPC_NW_ETXPWRSTUS_IND_T_EVENT, 0);
    int16_t sar_scenario_index = data->getMipcInt16Val(MIPC_NW_ETXPWRSTUS_IND_T_SAR_SCENARIO_INDEX, 0);

    response[0] = static_cast<int>(event);
    response[1] = static_cast<int>(sar_scenario_index);

    RFX_LOG_D(RFX_LOG_TAG, "handleTXPowerStatus: %d, %d", response[0], response[1]);
    urc = RfxMclMessage::obtainUrc(RFX_MSG_UNSOL_TX_POWER_STATUS, m_slot_id, RfxIntsData(response, 2));
    responseToTelCore(urc);
    return;
}

void RmmOemUrcHandler::handleRCSMTSIPInfo(RfxMipcData* data) {
    /// +ERCSMTINV: <from number>, <total count>, <index>, <MT SIP INVITE>
    int revCount=0, wholelen=0;
    char* fromNumber = data->getMipcStr(MIPC_CALL_MT_SIP_INVITE_IND_T_FROM_NUMBER);
    int total = data->getMipcUint8Val(MIPC_CALL_MT_SIP_INVITE_IND_T_TOTAL_COUNT, 0);
    int index = data->getMipcUint8Val(MIPC_CALL_MT_SIP_INVITE_IND_T_INDEX, 0);
    char* mtSipInvite = data->getMipcStr(MIPC_CALL_MT_SIP_INVITE_IND_T_MT_SIP_INVITE);
    logD(RFX_LOG_TAG, "MIPC_CALL_IMS_SIP_HEADER_IND AT< +ERCSMTINV: ***, %d, %d",total, index);


    if (index < 1 || index > 10) {
        return ;
    }

    if (mtSipInvite == NULL) {
        return;
    }

    RFX_LOG_D(RFX_LOG_TAG, "handleRCSMTSIPInfo sipInvite len: %d", strlen(mtSipInvite));
    char* tempMsg= (char*)calloc(1, sizeof(char)*(strlen(mtSipInvite) + 1));
    RFX_ASSERT(tempMsg != NULL);
    memset(tempMsg, 0x0, strlen(mtSipInvite) + 1 );
    memcpy(tempMsg, mtSipInvite, strlen(mtSipInvite));
    mMTSipTepData[index-1] = tempMsg;

    for (int i= 0; i < MTSIPINVIT_NOTIFY_BUFFER_LEN; i++) {
       if( mMTSipTepData[i] != NULL ) {
           revCount = revCount +1;
       }
    }
    if (revCount != total) {
        //do nothing
        return;
    }

    for (int i = 0; i < total; i++) {
       if( mMTSipTepData[i] != NULL ) {
           RFX_LOG_D(RFX_LOG_TAG, "handleRCSMTSIPInfo : %d ,%d", i, strlen(mMTSipTepData[i]));
           wholelen = wholelen + strlen(mMTSipTepData[i]);
       }
    }

    RFX_LOG_D(RFX_LOG_TAG, "handleRCSMTSIPInfo SIP size: %d", wholelen);
    char* atStr;
    asprintf(&atStr, "+ERCSMTINV: %s ,", fromNumber);
    wholelen = wholelen + strlen(atStr);
    sp<RfxMclMessage> urc;
    char* msg= (char*)calloc(1,sizeof(char)*(wholelen + 1));
    RFX_ASSERT(msg != NULL);
    memset(msg, 0x0, wholelen + 1);
    strncat(msg, atStr,strlen(atStr));

    for (int i = 0; i < total; i++) {
       if( mMTSipTepData[i] != NULL ) {
           strncat(msg, mMTSipTepData[i], strlen(mMTSipTepData[i]));
       }
    }

    RFX_LOG_D(RFX_LOG_TAG, "handleRCSMTSIPInfo len: %d", strlen(msg));
    urc = RfxMclMessage::obtainUrc(RFX_MSG_UNSOL_OEM_HOOK_RAW, m_slot_id,
        RfxRawData(msg, strlen(msg)));
    responseToTelCore(urc);

    free(msg);
    msg = NULL;
    free(atStr);
    atStr = NULL;
    for (int i = 0; i < total; i++) {
       free(mMTSipTepData[i]);
       mMTSipTepData[i] = NULL;
    }
}

void RmmOemUrcHandler::handleOemUrc(RfxAtLine *line) {
    char enabled[RFX_PROPERTY_VALUE_MAX] = {0};
    rfx_property_get("persist.vendor.radio.oem_urc_enable", enabled, "0");
    int err = 0;
    line->atTokStart(&err);
    RFX_LOG_D(RFX_LOG_TAG, "handleOemUrc");

    if (line->atTokHasmore()) {
        sp<RfxMclMessage> urc;
        char *s = line->getLine();
        RFX_LOG_D(RFX_LOG_TAG, "handleOemUrc, urc = %s\n", s);
        if (atoi(enabled) == 1) {
            // all urc ome indication is enabled, we skip this to prevent duplicate.
            RFX_LOG_D(RFX_LOG_TAG, "handleOemUrc skip");
        } else {
            urc = RfxMclMessage::obtainUrc(RFX_MSG_UNSOL_OEM_HOOK_RAW, m_slot_id,
                    RfxRawData(s, strlen(s)));
            responseToTelCore(urc);
        }
        if (strStartsWith(s, "+EMCFRPT: 3,1")) {
            char value[RFX_PROPERTY_VALUE_MAX] = {0};
            rfx_property_get("ro.vendor.mtk_mcf_support", value, "0");
            if(atoi(value) == 1) {
                // Critical OTA apply flow, reset modem
                RFX_LOG_E(RFX_LOG_TAG, "+EMCFRPT: 3,1, reset modem");
                sp<RfxMclMessage> mclMessage = RfxMclMessage::obtainRequest
                        (RFX_MSG_REQUEST_RESET_RADIO,
                        NULL, m_slot_id, 0, true, 0, 0, false);
                RfxMclDispatcherThread::enqueueMclMessage(mclMessage);
                return;
            }
        }
    }
}

/**
* Modem will send +ENVSIGERR when NVRAM verified failed.
*/
void RmmOemUrcHandler::handleNvErr(RfxMipcData* data) {
    uint8_t error_code = data->getMipcUint8Val(MIPC_SYS_NV_SIG_ERR_IND_T_ERROR_CODE, 0);

    RFX_LOG_D(RFX_LOG_TAG, "handleNvErr: %d", error_code);
    // enable recovery mode
    if (error_code == 1) {
        rfx_property_set("sys.powerctl", "reboot,recovery");
    }
    return;
}

void RmmOemUrcHandler::initRFCableStatusReader() {
    logD(RFX_LOG_TAG, "initRFCableStatusReader");
    mRFCableStatsuReaderThread = 0;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    int result = pthread_create(&mRFCableStatsuReaderThread, &attr, rfCableStatusReaderLoop, NULL);
    if (result != 0) {
        logE("initRFCableStatusReader: Failed to create dispatch thread: %s", strerror(result));
        return;
    }
}


void *RmmOemUrcHandler::rfCableStatusReaderLoop(void* params __unused) {
    int count = -1;
    RfxRilUtils::printLog(INFO, String8::format("%s", RFX_LOG_TAG),
            String8::format("rfCableStatusReaderLoop - RFCable status working thread"), RFX_SLOT_ID_0);
    sRFCableStatusFd = open("/dev/ccci_pin_sta", O_RDWR);
    RfxRilUtils::printLog(INFO, String8::format("%s", RFX_LOG_TAG),
            String8::format(
            "[RmmOemUrcHandler] rfCableStatusReaderLoop: fd = %d", sRFCableStatusFd),
            RFX_SLOT_ID_0);

    if (sRFCableStatusFd < 0) {
        RfxRilUtils::printLog(ERROR, String8::format("%s", RFX_LOG_TAG),
                String8::format("ccci_pin_sta port is not available, error code: %d (%s)", errno, strerror(errno)),
                RFX_SLOT_ID_0);
        return NULL;
    }

    PinStatusEvent *buffer = (PinStatusEvent *) calloc(1, sizeof(PinStatusEvent));
    if (buffer == NULL) {
        RfxRilUtils::printLog(ERROR, String8::format("%s", RFX_LOG_TAG),
                String8::format("OOM"), RFX_SLOT_ID_0);
        close(sRFCableStatusFd);
        return NULL;
    }

    do {
        count = read(sRFCableStatusFd, buffer, sizeof(PinStatusEvent));
        if (count > 0) {
            RfxRilUtils::printLog(INFO, String8::format("%s", RFX_LOG_TAG),
                    String8::format(
                    "rfCableStatusReaderLoop: count: %d pin_value %d, pin_name: %s",
                    count, buffer->pin_value, buffer->pin_name), RFX_SLOT_ID_0);
            sendUrcToTelCor(buffer);
        } else {
            RFX_LOG_E(RFX_LOG_TAG, "rfCableStatusReaderLoop: count:%d < 0", count);
        }
    } while (count > 0 || (count < 0 && errno == EINTR));

    RfxRilUtils::printLog(ERROR, String8::format("%s", RFX_LOG_TAG),
            String8::format("read /dev/ccci_pin_sta error: %s (%d)", strerror(errno), errno), RFX_SLOT_ID_0);
    free(buffer);
    close(sRFCableStatusFd);
    return NULL;
}


void RmmOemUrcHandler::sendUrcToTelCor(PinStatusEvent* buffer) {
    sp<RfxMclMessage> urc;
    char* responseRaw = NULL;
    if (asprintf(&responseRaw, "+RF CABLE: %d,%s", buffer->pin_value, buffer->pin_name) < 0) {
        RFX_LOG_E(RFX_LOG_TAG, "sendUrcToTelCor asprintf fail!");
        return;
    }

    for (int i = 0; i < getSimCount(); i++) {
        RfxRilUtils::printLog(DEBUG, String8::format("%s", RFX_LOG_TAG),
                String8::format(
                "[RmmOemUrcHandler] send RFCable event"), i);
        urc = RfxMclMessage::obtainUrc(
                RFX_MSG_UNSOL_OEM_HOOK_RAW, i,
                RfxStringData((void*)responseRaw, strlen(responseRaw)));
        RfxDispatchThread::enqueueUrcMessage(urc);
    }
    free(responseRaw);
}
