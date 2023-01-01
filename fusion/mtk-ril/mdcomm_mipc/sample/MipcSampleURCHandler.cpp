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

#include "MipcSampleURCHandler.h"
#include <telephony/mtk_ril.h>
#include "RfxMipcData.h"
#include "mipc_msg_tlv_api.h"
#include "mipc_msg_tlv_const.h"

#define RFX_LOG_TAG "MipcSampleURCHandler"

RFX_IMPLEMENT_HANDLER_CLASS(MipcSampleURCHandler, RIL_CMD_PROXY_5);


MipcSampleURCHandler::MipcSampleURCHandler(int slot_id, int channel_id) :
        RfxBaseHandler(slot_id, channel_id) {
    const int urc[] = {
        MIPC_SYS_AT_IND,
    };
    logI(RFX_LOG_TAG, "MipcSampleURCHandler init slotid %d, ch id %d", slot_id, channel_id);
    registerToHandleMipcURC(urc, sizeof(urc)/sizeof(int));

    const char *urcString[] = {
        "+EDSBP:",
    };
    registerToHandleURC(urcString, sizeof(urcString)/sizeof(char*));
}

MipcSampleURCHandler::~MipcSampleURCHandler() {
}

void MipcSampleURCHandler::onHandleUrc(const sp<RfxMclMessage>& msg) {
    char* atcmd_ptr = NULL;
    uint16_t atcommand_len = 0;
    if (msg->getMipcData() != NULL && msg->getMipcData()->getMipcMsgId() == MIPC_SYS_AT_IND) {
        logI(RFX_LOG_TAG, "mipc msg id: %d", msg->getMipcData()->getMipcMsgId());
        logI(RFX_LOG_TAG, "mipc slot id %d", msg->getMipcData()->getMipcSlotId());
        atcmd_ptr = (char*)(msg->getMipcData()->getMipcVal(MIPC_SYS_AT_IND_T_ATCMD, &atcommand_len));
        logI(RFX_LOG_TAG, "mipc URC string len %d, str %s", atcommand_len, atcmd_ptr);
        sp<RfxMclMessage> urc = RfxMclMessage::obtainUrc(RFX_MSG_URC_MIPC_SAMPLE_END,
                m_slot_id, RfxVoidData());
        responseToTelCore(urc);
    }

    if (msg->getRawUrc() != NULL) {
        char* urc = (char*)msg->getRawUrc()->getLine();
        logI(RFX_LOG_TAG, "URC string str:%s", urc);
        if (strStartsWith(urc, "+EDSBP:")) {
            sp<RfxMclMessage> urc = RfxMclMessage::obtainUrc(
                    RFX_MSG_URC_MIPC_SAMPLE_END, m_slot_id, RfxVoidData());
            responseToTelCore(urc);
        }
    }
}
