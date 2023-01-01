/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 *
 * MediaTek Inc. (C) 2021. All rights reserved.
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
#include "RtmDataController.h"
#include "RtmDataUtils.h"
#include "ims/RtmImsController.h"
#include "power/RtmRadioController.h"
#include "RfxMainThread.h"
#include "RfxRilUtils.h"
#include "RfxSlicingConfigResponseData.h"
#include <string>
#include <stdlib.h>
#include <compiler/compiler_utils.h>

#define RFX_LOG_TAG "RtmDC"

/// FastDormancy status that sync from EM. @{
#define RTM_EM_FASTDORMANCY_SYNC  "EM_FASTDORMANCY_SYNC"
#define RTM_EM_FASTDORMANCY_TIMER_LENGTH 3
#define RTM_EM_FASTDORMANCY_TIMER_ARGUMENT_LENGTH 4
/// @}

/*****************************************************************************
 * Class RtmDataController
 *****************************************************************************/
RFX_IMPLEMENT_CLASS("RtmDataController", RtmDataController, RfxController);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxSetupDataCallData, RfxDataCallResponseData, RFX_MSG_REQUEST_SETUP_DATA_CALL);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxStringsData, RfxVoidData, RFX_MSG_REQUEST_DEACTIVATE_DATA_CALL);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxVoidData, RfxDataCallResponseData, RFX_MSG_REQUEST_DATA_CALL_LIST);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxSetDataProfileData, RfxVoidData, RFX_MSG_REQUEST_SET_DATA_PROFILE);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxIntsData, RfxVoidData, RFX_MSG_REQUEST_SYNC_DATA_SETTINGS_TO_MD);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxStringData, RfxVoidData, RFX_MSG_REQUEST_RESET_MD_DATA_RETRY_COUNT);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxIaApnData, RfxVoidData, RFX_MSG_REQUEST_SET_INITIAL_ATTACH_APN);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxFdModeData, RfxVoidData, RFX_MSG_REQUEST_SET_FD_MODE);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxLinkCapacityReportingCriteriaData, RfxVoidData, RFX_MSG_REQUEST_SET_LINK_CAPACITY_REPORTING_CRITERIA);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxVoidData, RfxVoidData, RFX_MSG_REQUEST_RESET_ALL_CONNECTIONS);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxIntsData, RfxVoidData, RFX_MSG_REQUEST_SET_PREFERRED_DATA_MODEM);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxIntsData, RfxVoidData, RFX_MSG_REQUEST_SEND_DEVICE_STATE);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxIntsData, RfxVoidData, RFX_MSG_REQUEST_UPDATE_DATA_RAT);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxKeepaliveRequestData, RfxKeepaliveStatusData, RFX_MSG_REQUEST_START_KEEPALIVE);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxIntsData, RfxVoidData, RFX_MSG_REQUEST_STOP_KEEPALIVE);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxIntsData, RfxVoidData, RFX_MSG_REQUEST_DATA_CONNECTION_ATTACH);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxIntsData, RfxVoidData, RFX_MSG_REQUEST_DATA_CONNECTION_DETACH);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxIntsData, RfxVoidData, RFX_MSG_REQUEST_ALLOW_DATA);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxIntsData, RfxVoidData, RFX_MSG_REQUEST_ENABLE_DSDA_INDICATION);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxVoidData, RfxIntsData, RFX_MSG_REQUEST_GET_DSDA_STATUS);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxVoidData, RfxSlicingConfigResponseData, RFX_MSG_REQUEST_GET_SLICING_CONFIG);

RFX_REGISTER_DATA_TO_URC_ID(RfxDataCallResponseData, RFX_MSG_URC_DATA_CALL_LIST_CHANGED);
RFX_REGISTER_DATA_TO_URC_ID(RfxVoidData, RFX_MSG_URC_MD_DATA_RETRY_COUNT_RESET);
RFX_REGISTER_DATA_TO_URC_ID(RfxPlmnMvnoData, RFX_MSG_URC_PLMN_DATA);
RFX_REGISTER_DATA_TO_URC_ID(RfxLinkCapacityEstimateData, RFX_MSG_URC_LINK_CAPACITY_ESTIMATE);

RtmDataController::RtmDataController() :
    requestTokenIdForDisableIms(INVALID_VALUE),
    transIdForDisableIms(INVALID_VALUE) {
}

RtmDataController::~RtmDataController() {
}

void RtmDataController::onInit() {
    RfxController::onInit();  // Required: invoke super class implementation
    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] enter", m_slot_id, __FUNCTION__);

    const int request_id_list[] = {
        RFX_MSG_REQUEST_SYNC_DATA_SETTINGS_TO_MD,
        RFX_MSG_REQUEST_RESET_MD_DATA_RETRY_COUNT,
        RFX_MSG_REQUEST_SETUP_DATA_CALL,
        RFX_MSG_REQUEST_DEACTIVATE_DATA_CALL,
        RFX_MSG_REQUEST_DATA_CALL_LIST,
        RFX_MSG_REQUEST_SET_DATA_PROFILE,
        RFX_MSG_REQUEST_SET_INITIAL_ATTACH_APN,
        RFX_MSG_REQUEST_SET_FD_MODE,
        RFX_MSG_REQUEST_RESET_ALL_CONNECTIONS,
        RFX_MSG_REQUEST_SET_LINK_CAPACITY_REPORTING_CRITERIA,
        RFX_MSG_REQUEST_SET_PREFERRED_DATA_MODEM,
        RFX_MSG_REQUEST_SEND_DEVICE_STATE,
        RFX_MSG_REQUEST_START_KEEPALIVE,
        RFX_MSG_REQUEST_STOP_KEEPALIVE,
        RFX_MSG_REQUEST_DATA_CONNECTION_ATTACH,
        RFX_MSG_REQUEST_DATA_CONNECTION_DETACH,
        RFX_MSG_REQUEST_ALLOW_DATA,
        RFX_MSG_REQUEST_ENABLE_DSDA_INDICATION,
        RFX_MSG_REQUEST_GET_DSDA_STATUS,
    };

    registerToHandleRequest(request_id_list,
            sizeof(request_id_list) / sizeof(const int));

    registerForStatusChange();
}

void RtmDataController::registerForStatusChange() {
    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] enter", m_slot_id, __FUNCTION__);
    getStatusManager()->registerStatusChanged(RFX_STATUS_KEY_WORLD_MODE_STATE,
        RfxStatusChangeCallback(this, &RtmDataController::onWorldModeStateChanged));

    getStatusManager()->registerStatusChanged(RFX_STATUS_KEY_UICC_GSM_NUMERIC,
            RfxStatusChangeCallback(this, &RtmDataController::onUiccMccMncChanged));
    getStatusManager()->registerStatusChanged(RFX_STATUS_KEY_UICC_CDMA_NUMERIC,
            RfxStatusChangeCallback(this, &RtmDataController::onUiccMccMncChanged));

    getStatusManager()->registerStatusChanged(RFX_STATUS_KEY_GSM_IMSI,
            RfxStatusChangeCallback(this, &RtmDataController::onImsiChanged));
    getStatusManager()->registerStatusChanged(RFX_STATUS_KEY_C2K_IMSI,
            RfxStatusChangeCallback(this, &RtmDataController::onImsiChanged));

    getStatusManager()->registerStatusChanged(RFX_STATUS_KEY_GSM_SPN,
            RfxStatusChangeCallback(this, &RtmDataController::onSpnChanged));
    getStatusManager()->registerStatusChanged(RFX_STATUS_KEY_CDMA_SPN,
            RfxStatusChangeCallback(this, &RtmDataController::onSpnChanged));
    getStatusManager()->registerStatusChanged(RFX_STATUS_KEY_GSM_GID1,
            RfxStatusChangeCallback(this, &RtmDataController::onGid1Changed));
    getStatusManager()->registerStatusChanged(RFX_STATUS_KEY_GSM_PNN,
            RfxStatusChangeCallback(this, &RtmDataController::onPnnChanged));
    getStatusManager()->registerStatusChanged(RFX_STATUS_KEY_GSM_IMPI,
            RfxStatusChangeCallback(this, &RtmDataController::onImpiChanged));

    getStatusManager()->registerStatusChanged(RFX_STATUS_KEY_CARD_TYPE,
            RfxStatusChangeCallback(this, &RtmDataController::onCardTypeChanged));

    getStatusManager()->registerStatusChanged(RFX_STATUS_CONNECTION_STATE,
            RfxStatusChangeCallback(this, &RtmDataController::onConnectionStateChanged));

    getStatusManager()->registerStatusChanged(RFX_STATUS_KEY_SERVICE_STATE,
            RfxStatusChangeCallback(this, &RtmDataController::onServiceStateChanged));

    getStatusManager()->registerStatusChanged(RFX_STATUS_KEY_RADIO_STATE,
        RfxStatusChangeCallback(this, &RtmDataController::onRadioStateChanged));

    /// Sync data setting from OEM @{
    // Register data setting status change from OEM hook string.
    getStatusManager()->registerStatusChanged(
                RFX_STATUS_KEY_TELEPHONY_ASSISTANT_STATUS,
                RfxStatusChangeCallback(this, &RtmDataController::onDataSettingStatusChanged));
    /// @}
}

void RtmDataController::onWorldModeStateChanged(RfxStatusKeyEnum key,
    RfxVariant old_value, RfxVariant value) {
    RFX_UNUSED(key);
    int newValue = value.asInt();
    int oldValue = old_value.asInt();
    RFX_LOG_I(RFX_LOG_TAG, "[%d][%s] old = %d, new = %d",
            m_slot_id, __FUNCTION__, oldValue, newValue);
    if (newValue == WORLD_MODE_SWITCHING) {
        sp<RfxMessage> reqToRild = RfxMessage::obtainRequest(m_slot_id,
                RFX_MSG_REQUEST_CLEAR_ALL_PDN_INFO, RfxVoidData());
        requestToMcl(reqToRild);
    }
}

void RtmDataController::onUiccMccMncChanged(RfxStatusKeyEnum key,
        RfxVariant old_value, RfxVariant value) {
    RFX_UNUSED(old_value);
    String8 strMccMnc = value.asString8();
    String8 strGsmPlmn, strCdmaPlmn;

    if (!RtmDataUtils::isValidPlmn(strMccMnc.string())) {
        RFX_LOG_E(RFX_LOG_TAG,
                "[%d][%s] new MccMnc contains non-digit character, strMccMnc = %s",
                m_slot_id, __FUNCTION__, strMccMnc.string());
        return;
    }

    RFX_LOG_D(RFX_LOG_TAG, "[%d]onUiccMccMncChanged: strMccMnc = %s",
            m_slot_id, strMccMnc.string());

    if (RFX_STATUS_KEY_UICC_GSM_NUMERIC == key) {
        strGsmPlmn = strMccMnc;
        strCdmaPlmn = getStatusManager()->getString8Value(
                RFX_STATUS_KEY_UICC_CDMA_NUMERIC, String8(""));
    } else {
        strCdmaPlmn = strMccMnc;
        strGsmPlmn = getStatusManager()->getString8Value(
                RFX_STATUS_KEY_UICC_GSM_NUMERIC, String8(""));
    }

    notifyPlmnMvnoData(strGsmPlmn, strCdmaPlmn);
}

void RtmDataController::onImsiChanged(RfxStatusKeyEnum key,
        RfxVariant old_value, RfxVariant value) {
    RFX_UNUSED(key);
    RFX_UNUSED(old_value);
    RFX_UNUSED(value);
    String8 strGsmPlmn, strCdmaPlmn;

    RFX_LOG_D(RFX_LOG_TAG, "[%d]onImsiChanged", m_slot_id);

    strGsmPlmn = getStatusManager()->getString8Value(
            RFX_STATUS_KEY_UICC_GSM_NUMERIC, String8(""));
    strCdmaPlmn = getStatusManager()->getString8Value(
            RFX_STATUS_KEY_UICC_CDMA_NUMERIC, String8(""));

    notifyPlmnMvnoData(strGsmPlmn, strCdmaPlmn);
}

void RtmDataController::onSpnChanged(RfxStatusKeyEnum key,
        RfxVariant old_value, RfxVariant value) {
    RFX_LOG_D(RFX_LOG_TAG, "[%d]onSpnChanged, to onImsiChanged", m_slot_id);
    onImsiChanged(key, old_value, value);
}

void RtmDataController::onGid1Changed(RfxStatusKeyEnum key,
        RfxVariant old_value, RfxVariant value) {
    RFX_LOG_D(RFX_LOG_TAG, "[%d]onGid1Changed, to onImsiChanged", m_slot_id);
    onImsiChanged(key, old_value, value);
}

void RtmDataController::onPnnChanged(RfxStatusKeyEnum key,
        RfxVariant old_value, RfxVariant value) {
    RFX_LOG_D(RFX_LOG_TAG, "[%d]onPnnChanged, to onImsiChanged", m_slot_id);
    onImsiChanged(key, old_value, value);
}

void RtmDataController::onImpiChanged(RfxStatusKeyEnum key,
        RfxVariant old_value, RfxVariant value) {
    RFX_LOG_D(RFX_LOG_TAG, "[%d]onImpiChanged, to onImsiChanged", m_slot_id);
    onImsiChanged(key, old_value, value);
}

void RtmDataController::onCardTypeChanged(RfxStatusKeyEnum key,
        RfxVariant old_value, RfxVariant value) {
    RFX_UNUSED(key);
    int oldCardType = old_value.asInt();
    int cardType = value.asInt();
    if (oldCardType != 0 && cardType == 0) {
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s]: sim plugged out, notify empty state",
                m_slot_id, __FUNCTION__);
        notifyEmptyPlmnMvnoData();
    }
}

void RtmDataController::onConnectionStateChanged(RfxStatusKeyEnum key,
        RfxVariant old_value, RfxVariant value) {
    bool oldState = false, newState = false;

    RFX_UNUSED(key);
    oldState = old_value.asBool();
    newState = value.asBool();

    RFX_LOG_D(RFX_LOG_TAG, "[%d]onConnectionStateChanged: oldState = %d, newState = %d",
            m_slot_id, oldState, newState);

    if (oldState && !newState) {
        // For the case of phone process restart, we should reset all the data connections
        sp<RfxMessage> request = RfxMessage::obtainRequest(m_slot_id,
            RFX_MSG_REQUEST_RESET_ALL_CONNECTIONS, RfxVoidData());
        requestToMcl(request);
    } else if (!oldState && newState) {
        // For the case of phone process restart, we should reset ims data connections
        sp<RfxMessage> request = RfxMessage::obtainRequest(m_slot_id,
            RFX_MSG_REQUEST_RESET_IMS_CONNECTION, RfxVoidData());
        requestToMcl(request);
    }
    if (newState) {
        String8 strGsmPlmn = getStatusManager()->getString8Value(
                RFX_STATUS_KEY_UICC_GSM_NUMERIC, String8(""));
        String8 strCdmaPlmn = getStatusManager()->getString8Value(
                RFX_STATUS_KEY_UICC_CDMA_NUMERIC, String8(""));
        if (strGsmPlmn.isEmpty() && strCdmaPlmn.isEmpty()) {
            RFX_LOG_D(RFX_LOG_TAG, "[%d]onConnectionStateChanged: plmn is empty", m_slot_id);
        } else {
            notifyPlmnMvnoData(strGsmPlmn, strCdmaPlmn);
        }
    }
}

void RtmDataController::notifyPlmnMvnoData(String8& strGsmPlmn, String8& strCdmaPlmn) {
    int cardType = getStatusManager()->getIntValue(RFX_STATUS_KEY_CARD_TYPE, 0);
    if (cardType == 0) {
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s]: absent sim, notify empty state",
                m_slot_id, __FUNCTION__);
        notifyEmptyPlmnMvnoData();
        return;
    }

    String8 strMvno("");
    RIL_PlmnMvnoData rilPlmnMvnoData = {0};
    memset(&rilPlmnMvnoData, 0, sizeof(RIL_PlmnMvnoData));

    if (!strGsmPlmn.isEmpty() && 0 == atoi(strGsmPlmn.string())) {
        strGsmPlmn = String8::format("%d", atoi(strGsmPlmn.string()));
    }
    if (!strCdmaPlmn.isEmpty() && 0 == atoi(strCdmaPlmn.string())) {
        strCdmaPlmn = String8::format("%d", atoi(strCdmaPlmn.string()));
    }

    strncpy(rilPlmnMvnoData.gsmPlmn, const_cast<char*>(strGsmPlmn.string()),
            PLMN_MVNO_DATA_PLMN_LEN - 1);
    strncpy(rilPlmnMvnoData.cdmaPlmn, const_cast<char*>(strCdmaPlmn.string()),
            PLMN_MVNO_DATA_PLMN_LEN - 1);
    strMvno = getStatusManager()->getString8Value(RFX_STATUS_KEY_GSM_SPN);
    if (!strMvno.isEmpty()) {
        strncpy(rilPlmnMvnoData.gsmSpn, const_cast<char*>(strMvno.string()),
                PLMN_MVNO_DATA_SPN_LEN -1);
    }
    strMvno = getStatusManager()->getString8Value(RFX_STATUS_KEY_CDMA_SPN);
    if (!strMvno.isEmpty()) {
        strncpy(rilPlmnMvnoData.cdmaSpn, const_cast<char*>(strMvno.string()),
                PLMN_MVNO_DATA_SPN_LEN -1);
    }
    strMvno = getStatusManager()->getString8Value(RFX_STATUS_KEY_GSM_IMSI);
    if (!strMvno.isEmpty()) {
        strncpy(rilPlmnMvnoData.gsmImsi, const_cast<char*>(strMvno.string()),
                PLMN_MVNO_DATA_IMSI_LEN -1);
    }
    strMvno = getStatusManager()->getString8Value(RFX_STATUS_KEY_C2K_IMSI);
    if (!strMvno.isEmpty()) {
        strncpy(rilPlmnMvnoData.cdmaImsi, const_cast<char*>(strMvno.string()),
                PLMN_MVNO_DATA_IMSI_LEN -1);
    }
    strMvno = getStatusManager()->getString8Value(RFX_STATUS_KEY_GSM_GID1);
    if (!strMvno.isEmpty()) {
        strncpy(rilPlmnMvnoData.gid1, const_cast<char*>(strMvno.string()),
                PLMN_MVNO_DATA_GID_LEN - 1);
    }
    strMvno = getStatusManager()->getString8Value(RFX_STATUS_KEY_GSM_PNN);
    if (!strMvno.isEmpty()) {
        strncpy(rilPlmnMvnoData.pnn, const_cast<char*>(strMvno.string()),
                PLMN_MVNO_DATA_PNN_LEN - 1);
    }
    strMvno = getStatusManager()->getString8Value(RFX_STATUS_KEY_GSM_IMPI);
    if (!strMvno.isEmpty()) {
        strncpy(rilPlmnMvnoData.impi, const_cast<char*>(strMvno.string()),
                PLMN_MVNO_DATA_IMPI_LEN -1);
    }

    /*RFX_LOG_D(RFX_LOG_TAG, "[%d][%s]: gsmPlmn = %s, cdmaPlmn = %s, gsmSpn = %s, cdmaSpn = %s,"
            " gsmImsi = %s, cdmaImsi = %s, gid1 = %s, pnn = %s, impi = %s",
            getSlotId(), __FUNCTION__, rilPlmnMvnoData.gsmPlmn, rilPlmnMvnoData.cdmaPlmn,
            rilPlmnMvnoData.gsmSpn, rilPlmnMvnoData.cdmaSpn, rilPlmnMvnoData.gsmImsi,
            rilPlmnMvnoData.cdmaImsi, rilPlmnMvnoData.gid1, rilPlmnMvnoData.pnn,
            rilPlmnMvnoData.impi);*/

    sp<RfxMessage> urc = RfxMessage::obtainUrc(getSlotId(), RFX_MSG_URC_PLMN_DATA,
            RfxPlmnMvnoData(&rilPlmnMvnoData, sizeof(RIL_PlmnMvnoData)));
    responseToRilj(urc);
}

void RtmDataController::notifyEmptyPlmnMvnoData() {
    RIL_PlmnMvnoData rilPlmnMvnoData = {0};
    memset(&rilPlmnMvnoData, 0, sizeof(RIL_PlmnMvnoData));

    sp<RfxMessage> urc = RfxMessage::obtainUrc(getSlotId(), RFX_MSG_URC_PLMN_DATA,
            RfxPlmnMvnoData(&rilPlmnMvnoData, sizeof(RIL_PlmnMvnoData)));
    responseToRilj(urc);
}

/// Sync FastDormancy state from EM. @{
void RtmDataController::onDataSettingStatusChanged(RfxStatusKeyEnum key,
        RfxVariant old_value, RfxVariant value) {
    RFX_UNUSED(key);
    RFX_UNUSED(old_value);
    String8 strStatus = value.asString8();
    RFX_LOG_D(RFX_LOG_TAG, "[%d] onDataSettingStatusChanged: value = %s",
            m_slot_id, strStatus.string());
    if (strStatus.find(String8(RTM_EM_FASTDORMANCY_SYNC)) != -1) {
        int timer[RTM_EM_FASTDORMANCY_TIMER_LENGTH] = {0};
        int status[RTM_EM_FASTDORMANCY_TIMER_ARGUMENT_LENGTH] = {0};
        char *saveptr = NULL;
        char *tempFdSetting = strtok_r((char *)strStatus.string(), ":,", &saveptr);
        int i = 0;
        while (tempFdSetting != NULL && i < RTM_EM_FASTDORMANCY_TIMER_LENGTH) {
            tempFdSetting = strtok_r(NULL, ":,", &saveptr);
            if (tempFdSetting != NULL) {
                timer[i++] = atoi(tempFdSetting);
            }
        }

        RFX_LOG_D(RFX_LOG_TAG, "[%d] onDataSettingStatusChanged: fastdormancy = %d,%d,%d",
                m_slot_id, timer[0], timer[1], timer[2]);

        // mode 2 is for fastdormancy timer
        if (timer[0] == 2) {
            status[0] = 3; // args num
            status[1] = timer[0]; // mode
            status[2] = timer[1]; // timer type
            status[3] = timer[2]; // timer value

            sp<RfxMessage> request = RfxMessage::obtainRequest(m_slot_id,
                RFX_MSG_REQUEST_SET_FD_MODE,
                RfxIntsData(status, RTM_EM_FASTDORMANCY_TIMER_ARGUMENT_LENGTH));
            requestToMcl(request);
        }
    }
}
/// @}

void RtmDataController::onServiceStateChanged(RfxStatusKeyEnum key,
        RfxVariant old_value, RfxVariant value) {
    RFX_UNUSED(key);
    updateQualifiedNetworks(value);
    RfxNwServiceState oldSS = old_value.asServiceState();
    int oldDataRegState = oldSS.getRilDataRegState();
    int oldDataRadioTech = oldSS.getRilDataRadioTech();

    RfxNwServiceState newSS = value.asServiceState();
    int newDataRegState = newSS.getRilDataRegState();
    int newDataRadioTech = newSS.getRilDataRadioTech();

    if (!RfxNwServiceState::isInService(oldDataRegState) ||
            !RfxNwServiceState::isInService(newDataRegState)) {
        RFX_LOG_E(RFX_LOG_TAG,
                "[%d][%s] old or new data reg state is not InService",
                m_slot_id, __FUNCTION__);
        return;
    }

    // What we care about is: 4g to 5g, vice versa.
    // TODO: what about non-4g5g to 4g5g and vice versa ?
    if ((RtmDataUtils::is4GRat(oldDataRadioTech)
                && RtmDataUtils::is5GRat(newDataRadioTech))
            || (RtmDataUtils::is5GRat(oldDataRadioTech)
                    && RtmDataUtils::is4GRat(newDataRadioTech))) {
        int rat[2] = {0};
        rat[0] = oldDataRadioTech;
        rat[1] = newDataRadioTech;
        sp<RfxMessage> request = RfxMessage::obtainRequest(m_slot_id,
                RFX_MSG_REQUEST_UPDATE_DATA_RAT, RfxIntsData(rat, 2));
        requestToMcl(request);
    }
}

void RtmDataController::onRadioStateChanged(RfxStatusKeyEnum key,
        RfxVariant old_value, RfxVariant value) {
    int oldState = old_value.asInt();
    int newState = value.asInt();
    if (newState == RADIO_STATE_UNAVAILABLE || newState == RADIO_STATE_OFF) {
        bool requestPower = getStatusManager(m_slot_id)->getBoolValue(
                RFX_STATUS_KEY_REQUEST_RADIO_POWER, false);
        if (requestPower) {
            // This radio change is a URC, not from RILJ. In this case, if phone process
            // performance was poor, data FW will reset data connections to idle state(won't
            // trigger clean up due to PS keep attached), but PDNs still CONNECTED in MD.
            // So that AP is unable to active PDN any more.
            // To fix it, here we need reset all connections.
            sp<RfxMessage> request = RfxMessage::obtainRequest(m_slot_id,
                RFX_MSG_REQUEST_RESET_ALL_CONNECTIONS, RfxVoidData());
            requestToMcl(request);
        }
    }
}

void RtmDataController::onDeinit() {
    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] enter", m_slot_id, __FUNCTION__);
    RfxController::onDeinit();
}

bool RtmDataController::onHandleRequest(const sp<RfxMessage>& message) {
    int msg_id = message->getId();
    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] requestId: %s",
            m_slot_id, __FUNCTION__, idToString(msg_id));

    switch (msg_id) {
        case RFX_MSG_REQUEST_SYNC_DATA_SETTINGS_TO_MD:
            handleSyncDataSettingsToMD(message);
            break;
        case RFX_MSG_REQUEST_SETUP_DATA_CALL:
            handleSetupDataRequest(message);
            break;
        case RFX_MSG_REQUEST_DEACTIVATE_DATA_CALL:
            handleDeactivateDataRequest(message);
            break;
        case RFX_MSG_REQUEST_SET_PREFERRED_DATA_MODEM:
            handleSetPreferredDataModem(message);
            break;
        case RFX_MSG_REQUEST_SET_FD_MODE:
        case RFX_MSG_REQUEST_RESET_MD_DATA_RETRY_COUNT:
        case RFX_MSG_REQUEST_DATA_CALL_LIST:
        case RFX_MSG_REQUEST_SET_DATA_PROFILE:
        case RFX_MSG_REQUEST_SET_INITIAL_ATTACH_APN:
        case RFX_MSG_REQUEST_RESET_ALL_CONNECTIONS:
        case RFX_MSG_REQUEST_SET_LINK_CAPACITY_REPORTING_CRITERIA:
        case RFX_MSG_REQUEST_SEND_DEVICE_STATE:
        case RFX_MSG_REQUEST_UPDATE_DATA_RAT:
        case RFX_MSG_REQUEST_START_KEEPALIVE:
        case RFX_MSG_REQUEST_STOP_KEEPALIVE:
        case RFX_MSG_REQUEST_DATA_CONNECTION_ATTACH:
        case RFX_MSG_REQUEST_DATA_CONNECTION_DETACH:
        case RFX_MSG_REQUEST_ENABLE_DSDA_INDICATION:
        case RFX_MSG_REQUEST_GET_DSDA_STATUS:
            requestToMcl(message);
            break;
        case RFX_MSG_REQUEST_ALLOW_DATA: {
            // From Gen97, md has the ability to set EDALLOW=1/0 itself.
            // Do nothing and return success to framework for VTS:setdataallowed testcase.
            sp<RfxMessage> responseMsg = RfxMessage::obtainResponse(message->getSlotId(),
            RFX_MSG_REQUEST_ALLOW_DATA, RIL_E_SUCCESS, RfxVoidData(), message);
            responseToRilj(responseMsg);
            break;
        }
        default:
            RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] unknown request, ignore!", m_slot_id, __FUNCTION__);
            break;
    }
    return true;
}

bool RtmDataController::onHandleResponse(const sp<RfxMessage>& message) {
    int msg_id = message->getId();
    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] responseId: %s",
            m_slot_id, __FUNCTION__ , idToString(msg_id));

    switch (msg_id) {
        case RFX_MSG_REQUEST_SETUP_DATA_CALL:
            handleSetupDataResponse(message);
            break;
        case RFX_MSG_REQUEST_SYNC_DATA_SETTINGS_TO_MD:
        case RFX_MSG_REQUEST_SET_FD_MODE:
        case RFX_MSG_REQUEST_DEACTIVATE_DATA_CALL:
        case RFX_MSG_REQUEST_SET_PREFERRED_DATA_MODEM:
        case RFX_MSG_REQUEST_RESET_MD_DATA_RETRY_COUNT:
        case RFX_MSG_REQUEST_DATA_CALL_LIST:
        case RFX_MSG_REQUEST_SET_DATA_PROFILE:
        case RFX_MSG_REQUEST_SET_INITIAL_ATTACH_APN:
        case RFX_MSG_REQUEST_RESET_ALL_CONNECTIONS:
        case RFX_MSG_REQUEST_SET_LINK_CAPACITY_REPORTING_CRITERIA:
        case RFX_MSG_REQUEST_SEND_DEVICE_STATE:
        case RFX_MSG_REQUEST_START_KEEPALIVE:
        case RFX_MSG_REQUEST_STOP_KEEPALIVE:
        case RFX_MSG_REQUEST_DATA_CONNECTION_ATTACH:
        case RFX_MSG_REQUEST_DATA_CONNECTION_DETACH:
        case RFX_MSG_REQUEST_ENABLE_DSDA_INDICATION:
        case RFX_MSG_REQUEST_GET_DSDA_STATUS:
            responseToRilj(message);
            break;
        case RFX_MSG_REQUEST_UPDATE_DATA_RAT:
        case RFX_MSG_REQUEST_RESET_IMS_CONNECTION:
            RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] nothing to do.", m_slot_id, __FUNCTION__);
            break;
        default:
            RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] unknown response, ignore!", m_slot_id, __FUNCTION__);
            break;
    }
    return true;
}

bool RtmDataController::onHandleUrc(const sp<RfxMessage>& message) {
    int msg_id = message->getId();
    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] urcId: %s", m_slot_id, __FUNCTION__, idToString(msg_id));
    return true;
}

void RtmDataController::handleSyncDataSettingsToMD(const sp<RfxMessage>& message) {
    // For sync the data settings.
    int *pReqData = (int *) message->getData()->getData();

    if (pReqData[DEFAULT_DATA_SIM] != SKIP_DATA_SETTINGS) {
        getNonSlotScopeStatusManager()->setIntValue(RFX_STATUS_KEY_DEFAULT_DATA_SIM,
                pReqData[DEFAULT_DATA_SIM]);
    }

    requestToMcl(message);
}

void RtmDataController::preCheckIfNeedDisableIms(const sp<RfxMessage>& message) {
    RIL_SetupDataCallRequest *pReq = (RIL_SetupDataCallRequest*)message->getData()->getData();
    int nProfileId = pReq->dataProfileInfo.profileId;

    int slot_id = m_slot_id;
    RfxNwServiceState defaultServiceState (0, 0, 0 ,0);
    RfxNwServiceState serviceState = getStatusManager()
            ->getServiceStateValue(RFX_STATUS_KEY_SERVICE_STATE, defaultServiceState);
    int dataRadioTech = serviceState.getRilDataRadioTech();

    RFX_LOG_D(RFX_LOG_TAG, "preCheckIfNeedDisableIms: apntype=%s, slot id=%d, datastate=%d ",
            nProfileId, slot_id, dataRadioTech);

    //Check if apn type is MMS
    if (nProfileId != RIL_DATA_PROFILE_VENDOR_MMS) {
        return;
    }
    //RFX_LOG_D(RFX_LOG_TAG, "preCheckIfNeedDisableIms: apn type is mms");

    //Check if MMS is sent by secondary SIM, get slot id
    if (slot_id == INVALID_VALUE) {
        return;
    }
    slot_id = ((m_slot_id == 0) ? 1 : 0);
    //RFX_LOG_D(RFX_LOG_TAG, "preCheckIfNeedDisableIms: slot is secondary");

    //Check if he RAT is under 2G/3G/C2K
    switch (dataRadioTech) {
        case RADIO_TECH_LTE:
            return;
        case RADIO_TECH_LTE_CA:
            return;
        default:
            break;
    }
    requestTokenIdForDisableIms = message->getToken();

    //ImsPreCheck
    RtmImsController *imsController;
    sp<RfxAction> action;
    logD(RFX_LOG_TAG, "Disable IMS , slotId=%d", slot_id);
    imsController = (RtmImsController *) findController(slot_id,
            RFX_OBJ_CLASS_INFO(RtmImsController));
    action = new RfxAction1<const sp<RfxMessage>>(this,
            &RtmDataController::onImsConfirmed, message);
    imsController->requestImsDisable(slot_id, action);
    //RFX_LOG_D(RFX_LOG_TAG, "requestImsDisable finished");
}

void RtmDataController::handleSetupDataRequest(const sp<RfxMessage>& message) {
    // Convert profileId to a valid one based on supportedTypesBitmask
    // if profileId is using default value.
    RIL_SetupDataCallRequest *pReq = (RIL_SetupDataCallRequest*)message->getData()->getData();
    int nProfileId = pReq->dataProfileInfo.profileId;
    if (nProfileId <= 0) {
        int supportedTypesBitmask = pReq->dataProfileInfo.supportedTypesBitmask;
        for (int i = 0; i < RIL_APN_TYPE_COUNT; i++) {
            if (supportedTypesBitmask & (1 << i)) {
                if ((1 << i) == RIL_APN_TYPE_DEFAULT) {
                    int preferSim = getNonSlotScopeStatusManager()->getIntValue(
                            RFX_STATUS_KEY_PREFERRED_DATA_SIM);
                    if (preferSim != m_slot_id) {
                        RFX_LOG_I(RFX_LOG_TAG, "[%d][%s] non preferred data sim, skip default apn",
                            m_slot_id, __FUNCTION__);
                        continue;
                    }
                }
                nProfileId = getProfileID(1 << i);
                pReq->dataProfileInfo.profileId = nProfileId;
                break;
            }
        }
    }

    if(RtmDataUtils::isSupportTemporaryDisableIms() && (RfxRilUtils::rfxGetSimCount() == 2)) {
        preCheckIfNeedDisableIms(message);
    }
    requestToMcl(message);
}

void RtmDataController::handleSetupDataResponse(const sp<RfxMessage>& response) {
    //Remember the transferID of MMS pdn
    if (RtmDataUtils::isSupportTemporaryDisableIms() && RfxRilUtils::rfxGetSimCount() == 2
            && response->getToken() == requestTokenIdForDisableIms) {
        if (response->getError() != RIL_E_SUCCESS) {
            logD(RFX_LOG_TAG, "setupdata response fail!");
            requestResumeIms(response);
            responseToRilj(response);
            return;
        }
        const int *pRspData = (int *) response->getData()->getData();
        RFX_LOG_D(RFX_LOG_TAG, "handleSetupDataResponse: cid=%d", pRspData[2]);
        transIdForDisableIms = pRspData[2];
        requestTokenIdForDisableIms = INVALID_VALUE;
    }
    responseToRilj(response);
}

void RtmDataController::handleDeactivateDataRequest(const sp<RfxMessage>& message) {
    const char **pReqData = (const char **) message->getData()->getData();

    RFX_LOG_D(RFX_LOG_TAG, "handleDeactivateDataRequest: cid=%s", pReqData[0]);

    //If the cid is same, resume ims
    if (RtmDataUtils::isSupportTemporaryDisableIms() && RfxRilUtils::rfxGetSimCount() == 2
            && transIdForDisableIms == atoi(pReqData[0]) && atoi(pReqData[0]) >= 0) {
        requestResumeIms(message);
    }
    requestToMcl(message);
}

void RtmDataController::handleSetPreferredDataModem(const sp<RfxMessage>& message) {
    const int *pReqData = (const int *)message->getData()->getData();
    int preferredMdId = pReqData[0]; // 0 for slot0, 1 for slot1.
    RFX_LOG_D(RFX_LOG_TAG,
            "handleSetPreferredDataModem: preferred Modem=%d", preferredMdId);

    if (preferredMdId < 0 || preferredMdId >= RFX_SLOT_COUNT) {
        sp<RfxMessage> responseMsg = RfxMessage::obtainResponse(message->getSlotId(),
                RFX_MSG_REQUEST_SET_PREFERRED_DATA_MODEM, RIL_E_INVALID_ARGUMENTS,
                RfxVoidData(), message);
        responseToRilj(responseMsg);
        return;
    }

    getNonSlotScopeStatusManager()->setIntValue(RFX_STATUS_KEY_PREFERRED_DATA_SIM,
            preferredMdId, true);
    RtmDataUtils::setPreferDataSlotToProperty(preferredMdId);
    message->setSlotId(preferredMdId);
    requestToMcl(message);
}

bool RtmDataController::onCheckIfRejectMessage(const sp<RfxMessage>& message,
        bool isModemPowerOff, int radioState) {
    int msgId = message->getId();
    if((radioState == (int)RADIO_STATE_OFF) &&
            (msgId == RFX_MSG_REQUEST_SYNC_DATA_SETTINGS_TO_MD ||
             msgId == RFX_MSG_REQUEST_SET_DATA_PROFILE ||
             msgId == RFX_MSG_REQUEST_SET_PREFERRED_DATA_MODEM ||
             msgId == RFX_MSG_REQUEST_SET_INITIAL_ATTACH_APN ||
             msgId == RFX_MSG_REQUEST_ENABLE_DSDA_INDICATION ||
             msgId == RFX_MSG_REQUEST_GET_DSDA_STATUS ||
            (RfxRilUtils::isWfcSupport() &&
             msgId == RFX_MSG_REQUEST_SETUP_DATA_CALL) ||
            (RfxRilUtils::isWfcSupport() &&
             msgId == RFX_MSG_REQUEST_DEACTIVATE_DATA_CALL) ||
             msgId == RFX_MSG_REQUEST_SET_LINK_CAPACITY_REPORTING_CRITERIA ||
             msgId == RFX_MSG_REQUEST_SEND_DEVICE_STATE ||
             msgId == RFX_MSG_REQUEST_SET_FD_MODE ||
             msgId == RFX_MSG_REQUEST_ALLOW_DATA)) {
        return false;
    } else if ((radioState == (int)RADIO_STATE_UNAVAILABLE) &&
            (msgId == RFX_MSG_REQUEST_SYNC_DATA_SETTINGS_TO_MD ||
             msgId == RFX_MSG_REQUEST_SET_DATA_PROFILE ||
             msgId == RFX_MSG_REQUEST_SET_PREFERRED_DATA_MODEM ||
            (RfxRilUtils::isWfcSupport() &&
             msgId == RFX_MSG_REQUEST_SETUP_DATA_CALL) ||
            (RfxRilUtils::isWfcSupport() &&
             msgId == RFX_MSG_REQUEST_DEACTIVATE_DATA_CALL) ||
             msgId == RFX_MSG_REQUEST_ALLOW_DATA)) {
        return false;
    }
    return RfxController::onCheckIfRejectMessage(message, isModemPowerOff, radioState);
}

void RtmDataController::onImsConfirmed(const sp<RfxMessage> message) {
    int defaultDataSim = getNonSlotScopeStatusManager()
            ->getIntValue(RFX_STATUS_KEY_DEFAULT_DATA_SIM); // get default data sim slot id.
    logD(RFX_LOG_TAG, "onImsConfirmed Slot: %d, ims preCheck Done", defaultDataSim);
}

void RtmDataController::requestResumeIms(const sp<RfxMessage> message) {
    RtmImsController *imsController;
    sp<RfxAction> action;
    int slot_id = m_slot_id;
    slot_id = ((m_slot_id == 0) ? 1 : 0);
    logD(RFX_LOG_TAG, "Resume IMS precheck, slotId=%d", slot_id);
    imsController = (RtmImsController *) findController(slot_id,
            RFX_OBJ_CLASS_INFO(RtmImsController));
    action = new RfxAction1<const sp<RfxMessage>>(this,
            &RtmDataController::onImsConfirmed, message);
    imsController->requestImsResume(slot_id, action);
    //RFX_LOG_D(RFX_LOG_TAG, "requestImsResume finished");
    requestTokenIdForDisableIms = INVALID_VALUE;
}

int RtmDataController::getProfileID(int apnTypeId) {
    switch (apnTypeId) {
        case RIL_APN_TYPE_DEFAULT: return RIL_DATA_PROFILE_DEFAULT;
        case RIL_APN_TYPE_DUN: return RIL_DATA_PROFILE_TETHERED;
        case RIL_APN_TYPE_FOTA: return RIL_DATA_PROFILE_FOTA;
        case RIL_APN_TYPE_IMS: return RIL_DATA_PROFILE_IMS;
        case RIL_APN_TYPE_CBS: return RIL_DATA_PROFILE_CBS;
        case RIL_APN_TYPE_MMS: return RIL_DATA_PROFILE_VENDOR_MMS;
        case RIL_APN_TYPE_SUPL: return RIL_DATA_PROFILE_VENDOR_SUPL;
        case RIL_APN_TYPE_XCAP: return RIL_DATA_PROFILE_VENDOR_XCAP;
        case RIL_APN_TYPE_BIP: return RIL_DATA_PROFILE_VENDOR_BIP;
        case RIL_APN_TYPE_HIPRI: return RIL_DATA_PROFILE_VENDOR_HIPRI;
        case RIL_APN_TYPE_EMERGENCY: return RIL_DATA_PROFILE_VENDOR_EMERGENCY;
        case RIL_APN_TYPE_RCS: return RIL_DATA_PROFILE_VENDOR_RCS;
        case RIL_APN_TYPE_VSIM: return RIL_DATA_PROFILE_VENDOR_VSIM;
        case RIL_APN_TYPE_MCX: return RIL_DATA_PROFILE_VENDOR_MCX;
        default: return RIL_DATA_PROFILE_DEFAULT;
    }
}

void RtmDataController::updateQualifiedNetworks(RfxVariant& new_value) {
    RfxNwServiceState newSS = new_value.asServiceState();
    int state = newSS.getIwlanRegState();
    int data[3];
    data[0] = 1; // mode, always 1 currently.
    data[1] = RIL_APN_TYPE_MMS | RIL_APN_TYPE_XCAP | RIL_APN_TYPE_CBS;
    /** M: notice about this preference policy
     *  Here we make mms/xcap/cbs preferred iwlan when there is,
     *  but maybe some operators always require that mms/xcap/cbs should be on cellular.
     *  when this case really needed, can add customize code here to break the urc report,
     *  then android framework default and always preferred cellular.
     *
     *  For most cases, this maybe not a problem even here reported iwlan preferred,
     *  because if an apn not configured network_type_bitmask, framework will take it as
     *  support wifi, but our modem take it as not support wifi,
     *  so if framework can select the apn by iwlan side, our modem can still use cellular
     *  to setup.
     *  But for a sepcial case of the following, it will block:
     *  the apn has type "default,mms,XXX", and configured with network_type_bitmask without
     *  support wifi(18) for some reason, normally because of some types have extra apns.
     *
     *  For this case, if registered on wifi,and we reported wifi preferred for mms,
     *  then framework will try iwlan path to setup pdn, which will be blocked because of
     *  no wifi apn available. When this scenario happened, then you really need add code
     *  here to stop the urc report iwlan preference.
     *  You can check RFX_STATUS_KEY_UICC_GSM_NUMERIC/RFX_STATUS_KEY_UICC_CDMA_NUMERIC, and
     *  skip the urc report to make mms/xcap/cbs can always go cellular path.
     */
    if (state == 1) { // VoWiFi registered, mms/xcap/cbs preferred VoWiFi first.
        data[2] = ACCESS_NW_TYPE_IWLAN;
    } else { // VoWiFi not registered, mms/xcap/cbs back to cellular.
        data[2] = ACCESS_NW_TYPE_CELLULAR;
    }
    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] WFC:%d, prefer: %d", m_slot_id, __FUNCTION__, state, data[2]);
    sp<RfxMessage> message = RfxMessage::obtainUrc(m_slot_id,
            RFX_MSG_URC_QUALIFIED_NETWORK_TYPES_CHANGED, RfxIntsData(data, 3));
    responseToRilj(message);
}
