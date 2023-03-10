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
#include <dlfcn.h>

#include "RtmCarrierConfigController.h"
#include "RfxRootController.h"
#include "nw/RtmNwDefs.h"
#include "sbp/RtmSbpController.h"

#include "RfxStatusDefs.h"
#include "rfx_properties.h"


/*****************************************************************************
 * Class RfxController
 *****************************************************************************/

#define RFX_LOG_TAG "RtmCarrier"

RFX_IMPLEMENT_CLASS("RtmCarrierConfigController", RtmCarrierConfigController, RfxController);

/* List all status manager keys which values will be changed(loaded)
   by native carrier config */
const static int CarrierConfigKeyList[] = {
    RFX_STATUS_KEY_OPERATOR,
    RFX_STATUS_KEY_RESTORE_IMS_CONFERENCE_PARTICIPANT,
    RFX_STATUS_KEY_OPERATE_IMS_CONFERENCE_PARTICIPANTS_BY_USER_ENTITY,
    RFX_STATUS_KEY_IMS_SPECIFIC_CONFERENCE_MODE,
    RFX_STATUS_KEY_HIGH_PRIORITY_CLIR_PREFIX_SUPPORTED,
    RFX_STATUS_KEY_CONFIG_DEVICE_VOLTE_AVAILABLE,
    RFX_STATUS_KEY_CONFIG_DEVICE_VT_AVAILABLE,
    RFX_STATUS_KEY_CONFIG_DEVICE_WFC_AVAILABLE,
    RFX_STATUS_KEY_CONFIG_DEVICE_VONR_AVAILABLE,
    RFX_STATUS_KEY_CONFIG_DEVICE_VINR_AVAILABLE,
    RFX_STATUS_KEY_CARRIER_ALLOW_TURN_OFF_IMS,
    RFX_STATUS_KEY_CUSTOMIZED_USER_AGENT_FORMAT,
    RFX_STATUS_KEY_CARRIER_AUTO_APPROVE_INCOMING,
    RFX_STATUS_KEY_IMS_INCOMING_CALL_RULE,
    RFX_STATUS_KEY_IMS_CONFERENCE_FIRST_PARTICIPANT_AS_HOST,
    RFX_STATUS_KEY_CARRIER_UPDATE_ADDRESS_FROM_ECPI,
    RFX_STATUS_KEY_CARRIER_UPDATE_ADDRESS_BY_PAU_FOR_MO,
    RFX_STATUS_KEY_CARRIER_UPDATE_ADDRESS_BY_SIP_FIELD,
    RFX_STATUS_KEY_CARRIER_TREAT_DUPLICATED_NUMBER_AS_ONE_PARTICIPANT,
    RFX_STATUS_KEY_CARRIER_IGNORE_SMS_FOR_EIMS,
    RFX_STATUS_KEY_CARRIER_VIWIFI_INDEPENDENT_VOWIFI,
    RFX_STATUS_KEY_IGNORE_VOLTE_VILTE_FOR_23G,
    RFX_STATUS_KEY_SBP_ID,
    RFX_STATUS_KEY_SBP_SUB_ID,
};


RtmCarrierConfigController::RtmCarrierConfigController() {
    fnGetKeyCount = NULL;
    fnGetValuesByMccMnc = NULL;
    /* Open carrier config library */
    dlHandle = dlopen("libcarrierconfig.so", RTLD_NOW);
    if (dlHandle == NULL) {
        RFX_LOG_E(RFX_LOG_TAG, "dlopen failed: %s", dlerror());
    }
}

RtmCarrierConfigController::~RtmCarrierConfigController() {
    /* Close carrier config library */
    dlclose(dlHandle);
}

void RtmCarrierConfigController::onInit() {
    // Required: invoke super class implementation
    RfxController::onInit();

    getStatusManager()->registerStatusChanged(RFX_STATUS_KEY_UICC_GSM_NUMERIC,
            RfxStatusChangeCallback(this, &RtmCarrierConfigController::onUiccGsmMccMncChanged));
    getStatusManager()->registerStatusChanged(RFX_STATUS_KEY_UICC_CDMA_NUMERIC,
            RfxStatusChangeCallback(this, &RtmCarrierConfigController::onUiccCdmaMccMncChanged));
    getStatusManager()->registerStatusChanged(RFX_STATUS_KEY_CARD_TYPE,
            RfxStatusChangeCallback(this, &RtmCarrierConfigController::onCardTypeChanged));
    getStatusManager()->registerStatusChanged(RFX_STATUS_KEY_NWS_MODE,
            RfxStatusChangeCallback(this, &RtmCarrierConfigController::onNwsModeChanged));
}

void RtmCarrierConfigController::onDeinit() {
    logD(RFX_LOG_TAG, "onDeinit");
    getStatusManager()->unRegisterStatusChanged(RFX_STATUS_KEY_UICC_GSM_NUMERIC,
        RfxStatusChangeCallback(this, &RtmCarrierConfigController::onUiccGsmMccMncChanged));
    getStatusManager()->unRegisterStatusChanged(RFX_STATUS_KEY_UICC_CDMA_NUMERIC,
        RfxStatusChangeCallback(this, &RtmCarrierConfigController::onUiccCdmaMccMncChanged));
    getStatusManager()->unRegisterStatusChanged(RFX_STATUS_KEY_CARD_TYPE,
        RfxStatusChangeCallback(this, &RtmCarrierConfigController::onCardTypeChanged));
    getStatusManager()->unRegisterStatusChanged(RFX_STATUS_KEY_NWS_MODE,
        RfxStatusChangeCallback(this, &RtmCarrierConfigController::onNwsModeChanged));
    RfxController::onDeinit();
}


bool RtmCarrierConfigController::onHandleRequest(const sp<RfxMessage>& message) {
    RFX_UNUSED(message);
    return true;
}

bool RtmCarrierConfigController::onHandleUrc(const sp<RfxMessage>& message) {
    RFX_UNUSED(message);
    return true;
}

bool RtmCarrierConfigController::onHandleResponse(const sp<RfxMessage>& message) {
    RFX_UNUSED(message);
    return true;
}

bool RtmCarrierConfigController::responseToRilj(const sp<RfxMessage>& message) {
    RFX_UNUSED(message);
    return true;
}

void RtmCarrierConfigController::onUiccGsmMccMncChanged(RfxStatusKeyEnum key __unused,
        RfxVariant old_value __unused, RfxVariant value) {
    NwsMode mode = (NwsMode) getStatusManager()->getIntValue(RFX_STATUS_KEY_NWS_MODE,
            NWS_MODE_CSFB);
    String8 mccmncStr = value.asString8();
    if (mccmncStr.isEmpty()) {
        loadConfiguration((const char*)mccmncStr.string());
    } else {
        if (NWS_MODE_CDMALTE == mode) {
            logD(RFX_LOG_TAG, "[onUiccGsmMccMncChanged] phone type is not gsm");
            return;
        }
        int mccmnc;
        mccmnc = atoi(mccmncStr.string());
        logD(RFX_LOG_TAG, "[onUiccGsmMccMncChanged]MCC/MNC: %d", mccmnc);

        /* Update status manager values when MCC/MNC changed */
        loadConfiguration((const char*)mccmncStr.string());
    }
}

void RtmCarrierConfigController::onUiccCdmaMccMncChanged(RfxStatusKeyEnum key __unused,
        RfxVariant old_value __unused, RfxVariant value) {
    NwsMode mode = (NwsMode) getStatusManager()->getIntValue(RFX_STATUS_KEY_NWS_MODE,
            NWS_MODE_CSFB);
        String8 mccmncStr = value.asString8();
    if (mccmncStr.isEmpty()) {
        loadConfiguration((const char*)mccmncStr.string());
    } else {
        if (NWS_MODE_CDMALTE != mode) {
            logD(RFX_LOG_TAG, "[onUiccCdmaMccMncChanged] phone type is not cdma");
            return;
        }
        int mccmnc;
        mccmnc = atoi(mccmncStr.string());
        logD(RFX_LOG_TAG, "[onUiccCdmaMccMncChanged]MCC/MNC: %d", mccmnc);

        /* Update status manager values when MCC/MNC changed */
        loadConfiguration((const char*)mccmncStr.string());
    }
}

void RtmCarrierConfigController::onCardTypeChanged(RfxStatusKeyEnum key,
        RfxVariant oldValue, RfxVariant newValue) {
    RFX_UNUSED(key);
    logD(RFX_LOG_TAG, "[onCardTypeChanged]oldValue: %d, newValue: %d",
        oldValue.asInt(), newValue.asInt());

    /*
      -1: init value
      0: no card
      others: sim/usim/csim/rui
    */
    int cardType = newValue.asInt();
}

void RtmCarrierConfigController::onNwsModeChanged(RfxStatusKeyEnum key __unused,
        RfxVariant oldValue, RfxVariant newValue) {
    logD(RFX_LOG_TAG, "[onNwsModeChanged] oldValue: %d, newValue: %d",
        oldValue.asInt(), newValue.asInt());
    NwsMode nwsMode = (NwsMode) newValue.asInt();
    String8 mccmnc = getStatusManager()->getString8Value(RFX_STATUS_KEY_UICC_GSM_NUMERIC,
            String8("0"));
    // use current phone type to get mccmnc
    if (NWS_MODE_CDMALTE == nwsMode) {
        mccmnc = getStatusManager()->getString8Value(RFX_STATUS_KEY_UICC_CDMA_NUMERIC,
            String8("0"));
    }

    if (mccmnc.isEmpty()) {
        logD(RFX_LOG_TAG, "[onNwsModeChanged] mccmnc is empty");
        return;
    }
    logD(RFX_LOG_TAG, "[onNwsModeChanged] mccmnc: %s", mccmnc.string());
    loadConfiguration((const char*)mccmnc.string());
}

void RtmCarrierConfigController::loadConfiguration(const char *mccmnc) {
    int count = 0;
    RfxStatusKeyEnum key;
    String8 defaultValue;

    /* getKeyCount function pointer */
    fnGetKeyCount = (unsigned int (*)(const char*)) dlsym(dlHandle, "getKeyCount");
    if (fnGetKeyCount == NULL) {
        RFX_LOG_E(RFX_LOG_TAG, "getKeyCount function in libcarrierconfig is not defined!");
    } else {
        /* Get the count of carrier config value for specific mcc/mnc */
        count = fnGetKeyCount(mccmnc);
        RFX_LOG_D(RFX_LOG_TAG, "getKeyCount for %s = %d", mccmnc, count);
    }

    if (count > 0) {
        /* Load carrier config value */
        fnGetValuesByMccMnc = (int (*)(const char*, CarrierConfigValue*))
                dlsym(dlHandle, "getValuesByMccMnc");
        if (fnGetValuesByMccMnc == NULL) {
            RFX_LOG_D(RFX_LOG_TAG, "getValueByKey function in libcarrierconfig is not defined!");
        } else {
            CarrierConfigValue *data = (CarrierConfigValue*)calloc(count, sizeof(CarrierConfigValue));
            if (data != NULL) {
                int returnCount = fnGetValuesByMccMnc(mccmnc, data);
                for (int i = 0; i < returnCount; i++) {
                    key = (RfxStatusKeyEnum)data[i].key;
                    getStatusManager()->setString8Value(key, String8(data[i].value));
                    defaultValue = getStatusManager()->getDefaultValue(key).asString8();
                    RFX_LOG_D(RFX_LOG_TAG, "key = %s, default value = %s, new value = %s",
                            RfxStatusManager::getKeyString(key), defaultValue.string(),
                            getStatusManager()->getString8Value(key).string());
                }
                freeCarrierConfigValue(data, returnCount);
            }
        }/* end of fnGetValuesByMccMnc == NULL */
    }else  {
        /* Reset carrier config data to default value */
        int keyCount = sizeof(CarrierConfigKeyList) / sizeof(int);
        int i;
        RFX_LOG_D(RFX_LOG_TAG, "reset to default values, keyCount=%d", keyCount);
        for (i = 0; i < keyCount; i++) {
            key = (RfxStatusKeyEnum)CarrierConfigKeyList[i];
            defaultValue = getStatusManager()->getDefaultValue(key).asString8();
            getStatusManager()->setString8Value(key, defaultValue);
        }
    }/* end of count > 0 */

    getStatusManager()->setString8Value(RFX_STATUS_KEY_CARRIER_CONFIG_CHANGED, String8(mccmnc));
    RtmSbpController* sbp_controller = (RtmSbpController *)findController(
            RFX_OBJ_CLASS_INFO(RtmSbpController));
    if (sbp_controller) {
        RFX_LOG_I(RFX_LOG_TAG, "Notify sbp controller directly!");
        sbp_controller->onSbpIdChanged(m_slot_id, RFX_STATUS_KEY_SBP_ID,
                RfxVariant(""), RfxVariant(""));
    }
}

void RtmCarrierConfigController::freeCarrierConfigValue(CarrierConfigValue *data, int count) {
    for (int i = 0; i < count; i++) {
        if (data[i].value != NULL) {
            free(data[i].value);
        }
    }
    free(data);
}
