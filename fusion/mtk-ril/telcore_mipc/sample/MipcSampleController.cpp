/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 *
 * MediaTek Inc. (C) 2010. All rights reserved.
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
#include "RfxRilUtils.h"
#include "RfxLog.h"
#include "RfxAction.h"
#include "RfxMainThread.h"
#include "MipcSampleController.h"

#define MIPC_SAMPLE_LOG_TAG "MipcSampleController"


/*****************************************************************************
 * Class RfxController
 *****************************************************************************/
RFX_IMPLEMENT_CLASS("MipcSampleController", MipcSampleController, RfxController);

RFX_REGISTER_DATA_TO_REQUEST_ID(RfxIntsData, RfxVoidData, RFX_MSG_REQUEST_MIPC_SAMPLE_START);

RFX_REGISTER_DATA_TO_URC_ID(RfxVoidData, RFX_MSG_URC_MIPC_SAMPLE_END);

MipcSampleController::MipcSampleController() {

}

MipcSampleController::~MipcSampleController() {
}

void::MipcSampleController::onDeinit() {
}

void MipcSampleController::onInit() {
    // Required: invoke super class implementation
    RfxController::onInit();

    const int request_id_list[] = {
        RFX_MSG_REQUEST_MIPC_SAMPLE_START,
    };

    const int urc_id_list[] = {
        RFX_MSG_URC_MIPC_SAMPLE_END,
    };

    // register request & URC id list
    // NOTE. one id can only be registered by one controller
    registerToHandleRequest(request_id_list, sizeof(request_id_list)/sizeof(const int));
    registerToHandleUrc(urc_id_list, sizeof(urc_id_list)/sizeof(const int));
    getStatusManager()->registerStatusChangedEx(RFX_STATUS_KEY_TELEPHONY_ASSISTANT_STATUS,
            RfxStatusChangeCallbackEx(this, &MipcSampleController::onTelephonyAssistantStatusChanged));

    // register callbacks to get required information
    logD(MIPC_SAMPLE_LOG_TAG, "[mipcSample]MipcSampleController::onInit");
}

bool MipcSampleController::onPreviewMessage(const sp<RfxMessage>& message) {
    int msgId = message->getId();
    logD(MIPC_SAMPLE_LOG_TAG, "onPreviewMessage, handle %s", RFX_ID_TO_STR(msgId));
    return true;
}

bool MipcSampleController::onCheckIfResumeMessage(const sp<RfxMessage>& message) {
    int msgId = message->getId();
    logD(MIPC_SAMPLE_LOG_TAG, "onCheckIfResumeMessage, handle %s", RFX_ID_TO_STR(msgId));
    return true;
}


bool MipcSampleController::onHandleRequest(const sp<RfxMessage>& message) {
    int msgId = message->getId();
    logD(MIPC_SAMPLE_LOG_TAG, "onHandleRequest, handle %s", RFX_ID_TO_STR(msgId));
    requestToMcl(message);
    return true;
}

bool MipcSampleController::onHandleUrc(const sp<RfxMessage>& message) {
    int msgId = message->getId();
    int slotId = message->getSlotId();
    logD(MIPC_SAMPLE_LOG_TAG, "onHandleUrc, %s, %d", RFX_ID_TO_STR(msgId), slotId);
    if (msgId != RFX_MSG_URC_MIPC_SAMPLE_END) {
        logD(MIPC_SAMPLE_LOG_TAG, "onHandleUrc not expect, %s, %d", RFX_ID_TO_STR(msgId), slotId);
    }
    return true;
}

bool MipcSampleController::onHandleResponse(const sp<RfxMessage>& message) {
    int msgId = message->getId();
    int slotId = message->getSlotId();
    logD(MIPC_SAMPLE_LOG_TAG, "onHandleResponse, handle %s, %d", RFX_ID_TO_STR(msgId), slotId);
    switch (msgId) {
      case RFX_MSG_REQUEST_MIPC_SAMPLE_START:
          responseToRilj(message);
          break;
      default:
          logD(MIPC_SAMPLE_LOG_TAG, "unknow response ignore!");
          break;
    }
    return true;
}

bool MipcSampleController::onCheckIfRejectMessage(const sp<RfxMessage>& message,
            bool isModemPowerOff, int radioState) {
    int msgId = message->getId();
    int slotId = message->getSlotId();
    logD(MIPC_SAMPLE_LOG_TAG, "onCheckIfRejectMessage, isMDPowerOff=%d, radioState=%d, msgId=%d, slotId=%d",
            isModemPowerOff, radioState, msgId, slotId);
    return false;
}


void MipcSampleController::onTelephonyAssistantStatusChanged(int slotId, RfxStatusKeyEnum key,
        RfxVariant old_value, RfxVariant value) {
    RFX_UNUSED(key);
    RFX_UNUSED(old_value);
    const char* newValue = value.asString8().string();
    logD(MIPC_SAMPLE_LOG_TAG, "AssistantStatusChanged str = %s, %d", newValue, slotId);
}
