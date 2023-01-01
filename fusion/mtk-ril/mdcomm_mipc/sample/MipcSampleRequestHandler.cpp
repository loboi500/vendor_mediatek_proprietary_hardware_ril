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

#include "MipcSampleRequestHandler.h"
#include <telephony/mtk_ril.h>
#include "RfxMipcData.h"
#include "RfxIntsData.h"
#include "RfxStringsData.h"
#include "RfxVoidData.h"
#include "RfxStringData.h"
#include "mipc_msg_tlv_api.h"
#include "mipc_msg_tlv_const.h"

#define RFX_LOG_TAG "MipcSampleRequestHandler"

// register handler to channel
RFX_IMPLEMENT_HANDLER_CLASS(MipcSampleRequestHandler, RIL_CMD_PROXY_1);

MipcSampleRequestHandler::MipcSampleRequestHandler(int slot_id, int channel_id) :
        RfxBaseHandler(slot_id, channel_id) {
    const int request[] = {
        RFX_MSG_REQUEST_MIPC_SAMPLE_START,
    };
    logI(RFX_LOG_TAG, "MipcSampleRequestHandler init slotId %d, channel_id %d", slot_id, channel_id);
    registerToHandleRequest(request, sizeof(request)/sizeof(int));

    const int cmd[] = {
        MIPC_CALL_APPROVE_INCOMING_CMD,
    };

    registerToHandleMipcCmd(cmd, sizeof(cmd)/sizeof(int));
    logI(RFX_LOG_TAG, " registerToHandleMipcCmd ");

    char atcmd[] = "AT+ES3G?";
    sp<RfxMipcData> initMipc = RfxMipcData::obtainMipcData(MIPC_SYS_AT_REQ, slot_id);
    initMipc->addMipcTlv(MIPC_SYS_AT_REQ_T_ATCMD, strlen(atcmd) + 1, atcmd);
    sp<RfxMipcData> cnfMipc = callToMipcMsgSync(initMipc);
    uint16_t atcmdnlen = 0;
    char *atcmdcnf = (char*)(cnfMipc->getMipcVal(MIPC_SYS_AT_CNF_T_ATCMD, &atcmdnlen));

    int err = 0;
    sp<RfxAtResponse> p_response = NULL;
    p_response = atSendCommand("AT+CMMS=1");
    err = p_response->getError();
    if (err < 0 || p_response->getSuccess() == 0) {
        logE(RFX_LOG_TAG, "MipcSampleRequestHandler fail while executing AT+CMMS=1");
    } else {
       logE(RFX_LOG_TAG, "MipcSampleRequestHandler success while executing AT+CMMS=1");
    }
    p_response = NULL;

    logE(RFX_LOG_TAG, "sample init:%s", atcmdcnf);
}

MipcSampleRequestHandler::~MipcSampleRequestHandler() {
}

void MipcSampleRequestHandler::onHandleRequest(const sp<RfxMclMessage>& msg) {
    logD(RFX_LOG_TAG, "onHandleRequest: %d", msg->getId());
    int request = msg->getId();
    switch(request) {
        case RFX_MSG_REQUEST_MIPC_SAMPLE_START: {
            char atcmd[] = "AT+EFUN=0";
            sp<RfxMipcData> initMipc = RfxMipcData::obtainMipcData(MIPC_SYS_AT_REQ, msg->getSlotId());
            initMipc->addMipcTlv(MIPC_SYS_AT_REQ_T_ATCMD, strlen(atcmd) + 1, atcmd);
            callToMipcMsgAsync(msg, initMipc);
            }
            break;
        default:
            logE(RFX_LOG_TAG, "Should not be here");
            break;
    }
}

void MipcSampleRequestHandler::onHandleCmd(const sp<RfxMclMessage>& msg) {
    RfxMipcData* mipcData = msg->getMipcData();
    logI(RFX_LOG_TAG, "onHandleCmd slodId:%d, MipcMsgId:%d, MipcslotId:%d",
            msg->getSlotId(), mipcData->getMipcMsgId(), mipcData->getMipcSlotId());

    // sp<RfxMipcData> cmdRsp = RfxMipcData::obtainMipcData(MIPC_SYS_AT_REQ, msg->getSlotId(), msgTxId);
    // add tlv to cmdRsp
    // int ret = callToMipcMsgCmdResponse(cmdRsp);
}

void MipcSampleRequestHandler::onHandleResponse(const sp<RfxMclMessage>& msg) {
    RfxMipcData* mipcData = msg->getMipcData();
    logI(RFX_LOG_TAG, "onHandleResponse msgId:%d, slotId:%d", msg->getId(), msg->getSlotId());
    logI(RFX_LOG_TAG, "onHandleResponse MipcMsgId:%d, MipcSlotId:%d",
            mipcData->getMipcMsgId(), mipcData->getMipcSlotId());
    switch(msg->getId()) {
        case RFX_MSG_REQUEST_MIPC_SAMPLE_START: {
            uint16_t atcmdnlen = 0;
            char *atcmdcnf = (char*)(mipcData->getMipcVal(MIPC_SYS_AT_CNF_T_ATCMD, &atcmdnlen));
            logE(RFX_LOG_TAG, "SAMPLE_START cmd:%s", atcmdcnf);
            sp<RfxMclMessage> response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
                    RfxVoidData(), msg, false);
            responseToTelCore(response);

            logE(RFX_LOG_TAG, "SAMPLE send:AT+CIMI");
            atSendCommandNumeric("AT+CIMI");

            logE(RFX_LOG_TAG, "SAMPLE send:AT+CGMR");
            atSendCommandRaw("AT+CGMR");

            logE(RFX_LOG_TAG, "SAMPLE send:AT+EMDVER?");
            sp<RfxAtResponse> pResponse = atSendCommandMultiline(String8::format("AT+EMDVER?"),
                    (char *) "+EMDVER:");
            if (pResponse->getError() < 0 || pResponse->getSuccess() == 0) {
                logE(RFX_LOG_TAG, "AT+EMDVER? fail");
                return;
            }
            int err = 0;
            char *feature = NULL;
            int version = 0;
            RfxAtLine *line = pResponse->getIntermediates();
            while (1) {
                line->atTokStart(&err);
                feature = line->atTokNextstr(&err);
                version = line->atTokNextint(&err);
                logE(RFX_LOG_TAG, "SAMPLE EMDVER:%s,%d", feature, version);
                if (NULL == line->getNext()) {
                    break;
                }
                line = line->getNext();
            }
            }
            break;
        default:
            logE(RFX_LOG_TAG, "should not be here");
            break;
    }
}
