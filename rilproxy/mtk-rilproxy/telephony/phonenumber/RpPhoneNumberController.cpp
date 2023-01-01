/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 *
 * MediaTek Inc. (C) 2017. All rights reserved.
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
#include "RpPhoneNumberController.h"
#include "util/RpFeatureOptionUtils.h"
#include <libmtkrilutils.h>
#include <cutils/jstring.h>
#define RFX_LOG_TAG "RpPhoneNumberController"

#define MAX_PROP_CHARS       50
#define MCC_CHAR_LEN         3
#define PLMN_CHAR_LEN        6
#define ESIMS_CAUSE_RECOVERY 14
#define MAX_ECC_NUM          16
#define MAX_ECC_BUF_SIZE     (MAX_ECC_NUM * 8 + 1)
#define MAX_PRINT_CHAR       2
#define DELAY_SET_FWK_READY_TIMER 5000 //5s

#define FREEIF(data)    \
if (data != NULL) {     \
    free(data);         \
    data = NULL;        \
}

static const char PROPERTY_NW_MCCMNC[4][40] = {
    "vendor.ril.nw.operator.mccmnc.1",
    "vendor.ril.nw.operator.mccmnc.2",
    "vendor.ril.nw.operator.mccmnc.3",
    "vendor.ril.nw.operator.mccmnc.4",
};

/*****************************************************************************
 * Class RfxController
 *****************************************************************************/

RFX_IMPLEMENT_CLASS("RpPhoneNumberController", RpPhoneNumberController, RfxController);

RpPhoneNumberController::RpPhoneNumberController():
        mGsmEcc(""),
        mC2kEcc(""),
        mIsSimInsert(false),
        mSimEccSource(NULL),
        mNetworkEccSource(NULL),
        mDefaultEccSource(NULL),
        mXmlEccSource(NULL),
        mPropertyEccSource(NULL),
        mTestEccSource(NULL),
        mIsFwkReady(false),
        mIsPendingUpdate(false),
        mTimerHandle(NULL) {
}

RpPhoneNumberController::~RpPhoneNumberController() {
    for (int i = 0; i < (int)mEccNumberSourceList.size(); i++) {
        if (mEccNumberSourceList[i] != NULL) {
            delete(mEccNumberSourceList[i]);
        }
    }
    mEccNumberSourceList.clear();
}

EmergencyCallRouting RpPhoneNumberController::getEmergencyCallRouting(String8 number) {
    if (number.isEmpty()) {
        logE(RFX_LOG_TAG, "[%s] Empty number return unknown", __FUNCTION__);
        return ECC_ROUTING_UNKNOWN;
    }

    // Only print first two characters
    char maskNumber[MAX_PRINT_CHAR + 1] = {0};
    strncpy(maskNumber, number.string(), MAX_PRINT_CHAR);
    maskNumber[MAX_PRINT_CHAR] = '\0';

    for (int i = 0; i < (int)mEccList.size(); i++) {
        if (mEccList[i].number == number) {
            // For special/fake emergency number, it should dial using normal call routing when
            // SIM ready, for other cases, it should still dial using emergency routing
            int simState = getSimState();
            if ((mEccList[i].condition == CONDITION_MMI) &&
                    (simState == RFX_SIM_STATE_READY)) {
                RFX_LOG_I(RFX_LOG_TAG, "[%s] %s* is a special ECC", __FUNCTION__, maskNumber);
                return ECC_ROUTING_NORMAL;
            } else {
                RFX_LOG_I(RFX_LOG_TAG, "[%s] %s* is a ECC, condition: %d, simState: %d",
                        __FUNCTION__, maskNumber, mEccList[i].condition, simState);
                return ECC_ROUTING_EMERGENCY;
            }
        }
    }
    RFX_LOG_I(RFX_LOG_TAG, "[%s] %s* is not a ECC", __FUNCTION__, maskNumber);
    return ECC_ROUTING_UNKNOWN;
}

bool RpPhoneNumberController::isEmergencyNumber(String8 number) {
    if (number.isEmpty()) {
        logE(RFX_LOG_TAG, "[%s] Empty number return false", __FUNCTION__);
        return false;
    }

    // Only print first two characters
    char maskNumber[MAX_PRINT_CHAR + 1] = {0};
    strncpy(maskNumber, number.string(), MAX_PRINT_CHAR);
    maskNumber[MAX_PRINT_CHAR] = '\0';

    for (int i = 0; i < (int)mEccList.size(); i++) {
        if (mEccList[i].number == number) {
            RFX_LOG_I(RFX_LOG_TAG, "[%s] %s* is a ECC with condition: %d", __FUNCTION__,
                    maskNumber, mEccList[i].condition);
            return true;
        }
    }
    RFX_LOG_I(RFX_LOG_TAG, "[%s] %s* is not a ECC", __FUNCTION__, maskNumber);
    return false;
}

int RpPhoneNumberController::getServiceCategory(String8 number) {
    // Only print first two characters
    char maskNumber[MAX_PRINT_CHAR + 1] = {0};
    strncpy(maskNumber, number.string(), MAX_PRINT_CHAR);
    maskNumber[MAX_PRINT_CHAR] = '\0';

    for (int i = 0; i < (int)mEccList.size(); i++) {
        if ((mEccList[i].number == number) &&
                (mEccList[i].categories != ECC_CATEGORY_NOT_DEFINED)) {
            RFX_LOG_I(RFX_LOG_TAG, "[%s] %s* category is %d", __FUNCTION__, maskNumber,
                    mEccList[i].categories);
            return mEccList[i].categories;
        }
    }

    RFX_LOG_I(RFX_LOG_TAG, "[%s] %s* category is 0", __FUNCTION__, maskNumber);
    return 0;
}

void RpPhoneNumberController::onInit() {
    RfxController::onInit();  // Required: invoke super class implementation

    logD(RFX_LOG_TAG, "[%s]", __FUNCTION__);

    if (RpFeatureOptionUtils::isC2kSupport()) {
        const int urc_id_list[] = {
            RIL_LOCAL_GSM_UNSOL_EF_ECC,
            RIL_LOCAL_C2K_UNSOL_EF_ECC,
            RIL_UNSOL_EMERGENCY_NUMBER_LIST
        };
        // register request & URC id list
        // NOTE. one id can ONLY be registered by one controller
        registerToHandleUrc(urc_id_list, sizeof(urc_id_list)/sizeof(const int));
        // Register callbacks for card type to clear SIM ECC when SIM plug out
        getStatusManager()->registerStatusChanged(RFX_STATUS_KEY_CARD_TYPE,
                RfxStatusChangeCallback(this, &RpPhoneNumberController::onCardTypeChanged));
    } else {
        const int urc_id_list[] = {
            RIL_LOCAL_GSM_UNSOL_EF_ECC,
            RIL_LOCAL_C2K_UNSOL_EF_ECC,
            // Handle SIM plug out to reset SIM ECC in this URC
            // Currently this URC is not used by other module
            // so we can register it for non-C2K project
            RIL_UNSOL_SIM_PLUG_OUT,
            RIL_UNSOL_EMERGENCY_NUMBER_LIST
        };
        registerToHandleUrc(urc_id_list, sizeof(urc_id_list)/sizeof(const int));
    }
    getStatusManager()->registerStatusChanged(RFX_STATUS_KEY_SIM_STATE,
            RfxStatusChangeCallback(this, &RpPhoneNumberController::onSimStateChanged));

    // register callbacks to get connection state event
    getStatusManager()->registerStatusChanged(RFX_STATUS_CONNECTION_STATE,
            RfxStatusChangeCallback(this, &RpPhoneNumberController::onConnectionStateChanged));

    initEmergencyNumberSource();
}

void RpPhoneNumberController::initEmergencyNumberSource() {
    mNetworkEccSource = new NetworkEccNumberSource(m_slot_id);
    mSimEccSource = new SimEccNumberSource(m_slot_id);
    mDefaultEccSource = new DefaultEccNumberSource(m_slot_id);

    mEccNumberSourceList.clear();
    // Add ECC source by priority
    mEccNumberSourceList.push_back(mNetworkEccSource);
    mEccNumberSourceList.push_back(mSimEccSource);
    mEccNumberSourceList.push_back(mDefaultEccSource);

    // Init property ECC if property is set
    char eccCount[PROPERTY_VALUE_MAX] = {0};
    property_get(PROPERTY_ECC_COUNT, eccCount, "0");
    if (atoi(eccCount) > 0) {
        logD(RFX_LOG_TAG, "[%s] OEM property exist, init property source", __FUNCTION__);
        mPropertyEccSource = new OemPropertyEccNumberSource(m_slot_id);
        mEccNumberSourceList.push_back(mPropertyEccSource);
    }

    // Init XML ECC if XML file is exist
    FILE* file = fopen(ECC_PATH, "r");
    // Try to find a light way to check file exist
    if (file != NULL) {
        logD(RFX_LOG_TAG, "[%s] XML file exist, init XML source", __FUNCTION__);
        mXmlEccSource = new XmlEccNumberSource(m_slot_id);
        mEccNumberSourceList.push_back(mXmlEccSource);
        if (fclose(file) != 0) {
            logE(RFX_LOG_TAG, "[%s] Close XML file fail", __FUNCTION__);
        }
    }

    mTestEccSource = new TestEccNumberSource(m_slot_id);
    mEccNumberSourceList.push_back(mTestEccSource);

    mEccList.clear();

    // For NON C2K project, onCardTypeChanged will not be invoked
    // so we need update default emergency number here.
    if (!RpFeatureOptionUtils::isC2kSupport()) {
        mDefaultEccSource->update(false);
        updateEmergencyNumber();
    }
}

void RpPhoneNumberController::onCardTypeChanged(RfxStatusKeyEnum key,
        RfxVariant oldValue, RfxVariant newValue) {
    RFX_UNUSED(key);
    if (oldValue.asInt() != newValue.asInt()) {
        logV(RFX_LOG_TAG, "[%s] oldValue %d, newValue %d", __FUNCTION__,
            oldValue.asInt(), newValue.asInt());
        if (newValue.asInt() == 0) {
            logD(RFX_LOG_TAG,"[%s], reset SIM/NW ECC due to No SIM", __FUNCTION__);
            mGsmEcc = String8("");
            mC2kEcc = String8("");
            // Clear network ECC when SIM removed according to spec.
            property_set(PROPERTY_NW_ECC_LIST[m_slot_id], "");
            mIsSimInsert = false;
            mSimEccSource->update(String8(""), String8(""));
            //mDefaultEccSource->update(false);
            updateEmergencySourcesForAllSimStateChanges(hasSimInAnySlot());
            mNetworkEccSource->clear();
            mTestEccSource->update(false);
            updateEmergencyNumber();
        } else if (!isCdmaCard(newValue.asInt())) {
            // no CSIM or RUIM application, clear CDMA ecc property
            logV(RFX_LOG_TAG,"[%s], Remove C2K ECC due to No C2K SIM", __FUNCTION__);
            mC2kEcc = String8("");
            mSimEccSource->update(mGsmEcc, mC2kEcc);
            updateEmergencyNumber();
        }
    }
}

// Update special emergency number when sim state changed
// For special emergency number:
//     SIM ready: Normal call routing
//     Others: Emergency call routing
void RpPhoneNumberController::onSimStateChanged(RfxStatusKeyEnum key,
        RfxVariant oldValue, RfxVariant newValue) {
    RFX_UNUSED(key);
    if (oldValue.asInt() != newValue.asInt()) {
        logV(RFX_LOG_TAG,"[%s] update special emergency number", __FUNCTION__);
        updateSpecialEmergencyNumber();
    }
}

void RpPhoneNumberController::onConnectionStateChanged(RfxStatusKeyEnum key,
    RfxVariant oldValue, RfxVariant newValue) {
    RFX_UNUSED(oldValue);
    RFX_UNUSED(key);

    logD(RFX_LOG_TAG,"[%s] status: %d, mIsFwkReady: %d, mIsPendingUpdate: %d",
            __FUNCTION__, newValue.asBool(), mIsFwkReady, mIsPendingUpdate);

    if (mTimerHandle != NULL) {
        RfxTimer::stop(mTimerHandle);
        mTimerHandle = NULL;
    }

    if (!newValue.asBool()) {
        mIsFwkReady = false;
    } else if (!mIsFwkReady) {
        // Delay a timer to notify framework
        logD(RFX_LOG_TAG,"[%s] Delay to sent emergency list", __FUNCTION__);
        mTimerHandle = RfxTimer::start(RfxCallback0(this,
                &RpPhoneNumberController::delaySetFwkReady), ms2ns(DELAY_SET_FWK_READY_TIMER));
    }
}

void RpPhoneNumberController::delaySetFwkReady() {
    logD(RFX_LOG_TAG, "[%s] mIsFwkReady: %d, mIsPendingUpdate: %d", __FUNCTION__,
            mIsFwkReady, mIsPendingUpdate);
    mIsFwkReady = true;
    if (mIsPendingUpdate) {
        updateEmergencyNumber();
        mIsPendingUpdate = false;
    }
}

void RpPhoneNumberController::onDeinit() {
    logD(RFX_LOG_TAG,"onDeinit()");

    // Unregister callbacks for card type
    getStatusManager()->unRegisterStatusChanged(RFX_STATUS_KEY_CARD_TYPE,
            RfxStatusChangeCallback(this, &RpPhoneNumberController::onCardTypeChanged));

    // Required: invoke super class implementation
    RfxController::onDeinit();
}

bool RpPhoneNumberController::onHandleUrc(const sp<RfxMessage>& message) {
    int msgId = message->getId();
    char *plmn = NULL;
    Parcel *p = NULL;

    switch (msgId) {
        case RIL_LOCAL_GSM_UNSOL_EF_ECC:
            handleGSMEFECC(message);
            break;
        case RIL_LOCAL_C2K_UNSOL_EF_ECC:
            handleC2KEFECC(message);
            break;
        case RIL_UNSOL_SIM_PLUG_OUT:
            handleSimPlugOut(message);
            responseToRilj(message);
            break;
        case RIL_UNSOL_EMERGENCY_NUMBER_LIST:
            p = message->getParcel();
            plmn = strdupReadString(p);
            handleUpdateEmergencyNumber(plmn);
            if (plmn != NULL) {
                free(plmn);
                plmn = NULL;
            }
            break;
        default:
            responseToRilj(message);
            break;
    }

    return true;
}

const char* RpPhoneNumberController::urcToString(int urcId) {
    switch (urcId) {
        case RIL_LOCAL_GSM_UNSOL_EF_ECC: return "UNSOL_GSM_EF_ECC";
        case RIL_LOCAL_C2K_UNSOL_EF_ECC: return "UNSOL_C2K_EF_ECC";
        case RIL_UNSOL_EMERGENCY_NUMBER_LIST: return "UNSOL_EMERGENCY_NUMBER_LIST";
        default:
            return "UNKNOWN_URC";
    }
}

/*
 * [MD1 EF ECC URC format]
 * + ESMECC: <m>[,<number>,<service category>[,<number>,<service category>]]
 * <m>: number of ecc entry
 * <number>: ecc number
 * <service category>: service category
 * Ex.
 * URC string:2,115,4,334,5,110,1
 *
 * Note:If it has no EF ECC, RpPhoneNumberController will receive "0"
*/
void RpPhoneNumberController::handleGSMEFECC(const sp<RfxMessage>& message){
    char *gsmEfEcc;
    Parcel *p = message->getParcel();
    gsmEfEcc = strdupReadString(p);

    logV(RFX_LOG_TAG, "[%s]", __FUNCTION__);
    // SIM ECC URC come earlier then other SIM status key
    mIsSimInsert = true;

    if (gsmEfEcc != NULL) {
        parseSimEcc(String8(gsmEfEcc), true);
        mSimEccSource->update(mGsmEcc, mC2kEcc);
        free(gsmEfEcc);
        gsmEfEcc = NULL;
    }

    // Update other source for SIM insert condition
    //mDefaultEccSource->update(true);
    //updateEmergencySourcesForPlmnChange(NULL, true);
    updateEmergencySourcesForAllSimStateChanges(true);
    updateEmergencyNumber();
}

/*
 * [MD3 EF ECC URC format]
 * +CECC:<m>[,<number [,<number >]]
 * <m>: number of ecc entry
 * <number>: ecc number
 * Ex.
 * URC string:2,115,334
 *
 * Note:If it has no EF ECC, RpPhoneNumberController will receive "0"
 *
*/
void RpPhoneNumberController::handleC2KEFECC(const sp<RfxMessage>& message){
    char *cdmaEfEcc;
    Parcel *p = message->getParcel();
    cdmaEfEcc = strdupReadString(p);
    logV(RFX_LOG_TAG, "[%s]", __FUNCTION__);
    mIsSimInsert = true;
    if (cdmaEfEcc != NULL) {
        // SIM ECC URC come earlier then other SIM status key
        parseSimEcc(String8(cdmaEfEcc), false);
        mSimEccSource->update(mGsmEcc, mC2kEcc);
        free(cdmaEfEcc);
        cdmaEfEcc = NULL;
    }

    // Update other source for SIM insert condition
    //mDefaultEccSource->update(true);
    //updateEmergencySourcesForPlmnChange(NULL, true);
    updateEmergencySourcesForAllSimStateChanges(true);
    updateEmergencyNumber();
}

void RpPhoneNumberController::parseSimEcc(String8 line, bool isGsm) {
    String8 writeEcc = String8("");
    int parameterCount = 0;

    logV(RFX_LOG_TAG, "[%s] line: %s", __FUNCTION__, line.string());

    char *tempEcc = strtok((char*)line.string(), ",");

    while (tempEcc != NULL) {
        parameterCount++;
        //Just ignore the 1st parameter: it is the total number of emergency numbers.
        if(parameterCount >= 2){
            if(writeEcc.length() > 0) {
                if (isGsm) {
                    if ((parameterCount % 2) == 0) {
                        writeEcc += String8(";");
                    } else {
                        writeEcc += String8(",");
                    }
                } else {
                    writeEcc += String8(",");
                }
            }
            writeEcc += String8(tempEcc);
        }
        tempEcc = strtok(NULL, ",");
    }

    if (isGsm) {
        mGsmEcc = writeEcc;
        logD(RFX_LOG_TAG,"[%s] mGsmEcc: %s", __FUNCTION__, mGsmEcc.string());
    } else {
        mC2kEcc = writeEcc;
        logD(RFX_LOG_TAG,"[%s] mC2kEcc: %s", __FUNCTION__, mC2kEcc.string());
    }
}

// For non-C2K project to handle SIM plugout to reset SIM ECC only.
// for C2K project use RFX_STATUS_KEY_CARD_TYPE.
void RpPhoneNumberController::handleSimPlugOut(const sp<RfxMessage>& message){
    RFX_UNUSED(message);
    logD(RFX_LOG_TAG,"handleSimPlugOut, reset property due to No SIM");
    mGsmEcc = String8("");
    mC2kEcc = String8("");
    // Clear network ECC when SIM removed according to spec.
    property_set(PROPERTY_NW_ECC_LIST[m_slot_id], "");
    mIsSimInsert = false;
    mSimEccSource->update(mGsmEcc, mC2kEcc);
    mDefaultEccSource->update(false);
    mNetworkEccSource->clear();
    updateEmergencyNumber();
}

bool RpPhoneNumberController::isCdmaCard(int cardType) {
     if ((cardType & RFX_CARD_TYPE_RUIM) > 0 ||
         (cardType & RFX_CARD_TYPE_CSIM) > 0) {
         return true;
     }
     return false;
}

void RpPhoneNumberController::handleUpdateEmergencyNumber(char *plmn){
    logV(RFX_LOG_TAG, "[%s] plmn: %s", __FUNCTION__, plmn);
    bool isChange = false;
    if (mNetworkEccSource->update()) {
        isChange = true;
    }

    if (updateEmergencySourcesForPlmnChange(plmn, mIsSimInsert) || isChange) {
        updateEmergencyNumber();
    }
}

void RpPhoneNumberController::createEmergencyNumberListResponse(RIL_EmergencyNumber *data) {
    for (int i = 0; i < (int)mEccList.size(); i++) {
        asprintf(&(data[i].number), "%s", mEccList[i].number.string());
        // AOSP expect mcc/mnc not NULL
        char currentMcc[MCC_CHAR_LEN + 1] = {0};
        char currentMnc[MCC_CHAR_LEN + 1] = {0};
        String8 plmn = getPlmn(m_slot_id);
        if (plmn.length() > MCC_CHAR_LEN) {
            strncpy(currentMcc, plmn.string(), MCC_CHAR_LEN);
            currentMcc[MCC_CHAR_LEN] = '\0';
            strncpy(currentMnc, plmn.string() + MCC_CHAR_LEN, MCC_CHAR_LEN);
            currentMnc[MCC_CHAR_LEN] = '\0';
        }
        logD(RFX_LOG_TAG, "[%s] plmn:%s,mcc:%s,mnc:%s", __FUNCTION__, plmn.string(),
                currentMcc, currentMnc);
        asprintf(&(data[i].mcc), "%s", currentMcc);
        asprintf(&(data[i].mnc), "%s", currentMnc);
        if (mEccList[i].categories == ECC_CATEGORY_NOT_DEFINED) {
            data[i].categories = 0;
        } else {
            data[i].categories = mEccList[i].categories;
        }
        data[i].urns = NULL; // not used yet
        // Map EmergencyNumberSource to RIL_EmergencyNumberSource (AOSP value)
        // Convert all extended source type to MODEM_CONFIG
        data[i].sources = (mEccList[i].sources & 0x0F) |
                (((mEccList[i].sources & 0xF0) > 0) ? MODEM_CONFIG : 0);
    }
}

void RpPhoneNumberController::freeEmergencyNumberListResponse(RIL_EmergencyNumber *data) {
    for (int i = 0; i < (int)mEccList.size(); i++) {
        FREEIF(data[i].number);
        FREEIF(data[i].mcc);
        FREEIF(data[i].mnc);
    }
    FREEIF(data);
}

void RpPhoneNumberController::emergencyNumberListToParcel(const sp<RfxMessage>& msg,
        RIL_EmergencyNumber *response, int responselen) {
    Parcel *p = msg->getParcel();

    int num = responselen / sizeof(RIL_EmergencyNumber);
    p->writeInt32(num);

    RIL_EmergencyNumber *p_cur = (RIL_EmergencyNumber *) response;
    for (int i = 0; i < num; i++) {
        writeStringToParcel(p, p_cur[i].number);
        writeStringToParcel(p, p_cur[i].mcc);
        writeStringToParcel(p, p_cur[i].mnc);
        p->writeInt32(p_cur[i].categories);
        // urns not used, skip
        p->writeInt32(p_cur[i].sources);
    }
}

void RpPhoneNumberController::updateEmergencyNumber() {
    mEccList.clear();
    for (int i = 0; i < (int)mEccNumberSourceList.size(); i++) {
        mEccNumberSourceList[i]->addToEccList(mEccList);
    }

    // Remove non emergency numbers with condition NEVER after add all
    // emergency numbers with different source.
    removeNonEmergencyNumbers();

    String8 eccList = String8("");
    for (int i = 0; i < (int)mEccList.size(); i++) {
        // Skip duplicate emergency number
        if (!isEccMatchInList(mEccList[i].number, eccList)) {
            if (eccList == String8("")) {
                eccList += mEccList[i].number;
            } else {
                eccList += String8(",") + mEccList[i].number;
            }
        }
    }

    logI(RFX_LOG_TAG, "[%s] mIsFwkReady: %d, mIsPendingUpdate: %d, ecc list: %s", __FUNCTION__,
            mIsFwkReady, mIsPendingUpdate, (char*)eccList.string());

    // Set ril.ecclist property (For backward compatible)
    property_set(PROPERTY_ECC_LIST[m_slot_id], eccList.string());

    // Save special ECC list to property
    updateSpecialEmergencyNumber();

    // Send URC to framework (Q AOSP)
    if (mIsFwkReady) {
        int length = mEccList.size() * sizeof(RIL_EmergencyNumber);
        RIL_EmergencyNumber *pResponse = (RIL_EmergencyNumber *)calloc(1, length);
        if (pResponse != NULL) {
            createEmergencyNumberListResponse(pResponse);
            sp<RfxMessage> urc = RfxMessage::obtainUrc(m_slot_id, RIL_UNSOL_EMERGENCY_NUMBER_LIST);
            emergencyNumberListToParcel(urc, pResponse, length);
            responseToRilj(urc);
            freeEmergencyNumberListResponse(pResponse);
        }
    } else {
        mIsPendingUpdate = true;
    }

    dumpEccList();
}

void RpPhoneNumberController::updateSpecialEmergencyNumber() {
    String8 specialEccList = String8("");
    int simState = getSimState();
    if (simState == RFX_SIM_STATE_READY) {
        for (int i = 0; i < (int)mEccList.size(); i++) {
            if (mEccList[i].condition == CONDITION_MMI) {
                if (specialEccList == String8("")) {
                    specialEccList += mEccList[i].number;
                } else {
                    specialEccList += String8(",") + mEccList[i].number;
                }
            }
        }
    }
    property_set(PROPERTY_SPECIAL_ECC_LIST[m_slot_id], specialEccList.string());
    logV(RFX_LOG_TAG, "[%s] special ecc list: %s", __FUNCTION__, (char*)specialEccList.string());
}

String8 RpPhoneNumberController::convertPlmnForRoaming(String8 plmn) {
    // Convert for CT roaming PLMN
    if (plmn == String8("20404") && isCtCard()) {
        return String8("46011");
    }
    return plmn;
}

String8 RpPhoneNumberController::getPlmn(int slot) {
    // Get from network MCC/MNC
    char mccmnc[PROPERTY_VALUE_MAX] = {0};
    property_get((char *)PROPERTY_NW_MCCMNC[slot], mccmnc, "");
    logV(RFX_LOG_TAG, "[%s] networkPlmn: %s", __FUNCTION__, (char *)mccmnc);
    if (strlen(mccmnc) > MCC_CHAR_LEN &&
            // Don't return invalid network PLMN here, instead we
            // should try to get from SIM/UICC MCC/MNC
            strcmp(mccmnc, "000000") != 0 && strcmp(mccmnc, "FFFFFF") != 0) {
        return String8(mccmnc);
    }

    // Try to get from GSM SIM
    String8 gsmProp(PROPERTY_MCC_MNC);
    gsmProp.append((slot == 0) ? "" : String8::format(".%d", slot));
    property_get((const char *)gsmProp.string(), mccmnc, "");
    logV(RFX_LOG_TAG, "[%s] %s is: %s", __FUNCTION__, gsmProp.string(), mccmnc);
    if (strlen(mccmnc) > MCC_CHAR_LEN) {
        return convertPlmnForRoaming(String8(mccmnc));
    }

    // Try to get from CDMA SIM
    String8 cdmaProp(PROPERTY_MCC_MNC_CDMA);
    cdmaProp.append((slot == 0) ? "" : String8::format(".%d", slot));
    property_get((const char *)cdmaProp.string(), mccmnc, "");
    logV(RFX_LOG_TAG, "[%s] %s is: %s", __FUNCTION__, cdmaProp.string(), mccmnc);
    if (strlen(mccmnc) > MCC_CHAR_LEN) {
        return String8(mccmnc);
    }

    // No PLMN detect, return ""
    logV(RFX_LOG_TAG, "[%s] No PLMN detected!", __FUNCTION__);
    return String8("");
}

bool RpPhoneNumberController::isEccMatchInList(String8 number, String8 eccList) {
    // Add match boundary char ',' for easy match
    String8 searchEccList = String8(",") + eccList + String8(",");
    if (searchEccList.find(String8(",") + number + String8(",")) != -1) {
        return true;
    }

    return false;
}

String8 RpPhoneNumberController::getSourcesString(int sources) {
    String8 sourcesString = String8("");
    if (sources & SOURCE_NETWORK) {
        sourcesString += String8("|") + String8("Network");
    }
    if (sources & SOURCE_SIM) {
        sourcesString += String8("|") + String8("SIM");
    }
    if (sources & SOURCE_CONFIG) {
        sourcesString += String8("|") + String8("Config");
    }
    if (sources & SOURCE_DEFAULT) {
        sourcesString += String8("|") + String8("Default");
    }
    if (sources & SOURCE_OEM_PROPERTY) {
        sourcesString += String8("|") + String8("Property");
    }
    if (sources & SOURCE_FRAMEWORK) {
        sourcesString += String8("|") + String8("Framework");
    }
    if (sources & SOURCE_TEST) {
        sourcesString += String8("|") + String8("TEST");
    }
    return sourcesString;
}

void RpPhoneNumberController::dumpEccList() {
    if (ECC_DEBUG == 1) {
        for (int i = 0; i < (int)mEccList.size(); i++) {
            logD(RFX_LOG_TAG, "[%s] ECC [%d][%s,%s,%s,%d,%d,%s]",
                    __FUNCTION__, i,
                    mEccList[i].number.string(),
                    mEccList[i].mcc.string(),
                    mEccList[i].mnc.string(),
                    mEccList[i].categories,
                    mEccList[i].condition,
                    getSourcesString(mEccList[i].sources).string());
        }
    }
}

// The API will help to allocate memory so remember to free
// it while you don't use the buffer anymore
char* RpPhoneNumberController::strdupReadString(Parcel *p) {
    size_t stringlen;
    const char16_t *s16;

    s16 = p->readString16Inplace(&stringlen);

    return strndup16to8(s16, stringlen);
}

bool RpPhoneNumberController::isCtCard() {
    bool ret = false;
    int type = getStatusManager()->getIntValue(RFX_STATUS_KEY_CDMA_CARD_TYPE);
    if (type == CT_4G_UICC_CARD ||
            type == CT_UIM_SIM_CARD ||
            type == CT_3G_UIM_CARD) {
        ret = true;
    }
    return ret;
}

bool RpPhoneNumberController::updateEmergencySourcesForPlmnChange(char *plmn, bool isSimInsert) {
    logV(RFX_LOG_TAG, "[%s] plmn: %s, isSimInsert: %d", __FUNCTION__, plmn, isSimInsert);
    bool isChange = false;
    String8 newPlmn;
    if (plmn != NULL && strlen(plmn) > MCC_CHAR_LEN) {
        newPlmn = String8(plmn);
    } else {
        newPlmn = getPlmn(m_slot_id);
    }

    // reload XML ECC
    if (mXmlEccSource != NULL &&
            mXmlEccSource->update(newPlmn, isSimInsert)) {
        isChange = true;
    }

    // reload property ECC
    if (mPropertyEccSource != NULL &&
            mPropertyEccSource->update(newPlmn, isSimInsert)) {
        isChange = true;
    }

    // Update peer slot emergency numbers if possible
    int simCount = getSimCount();
    for (int i = 0; i < simCount; i++) {
        if (i != m_slot_id) {
            RpPhoneNumberController* eccController = (RpPhoneNumberController *)findController(
                    i, RFX_OBJ_CLASS_INFO(RpPhoneNumberController));
            if (eccController != NULL) {
                logD(RFX_LOG_TAG, "[%s] update ECC for peer slot %d", __FUNCTION__, i);
                if (eccController->updateEmergencySourcesFromPeer(getPlmn(m_slot_id))) {
                    eccController->updateEmergencyNumber();
                }
            }
        }
    }

    return isChange;
}

int RpPhoneNumberController::getSimState() {
    int simState = 0;
    if (RpFeatureOptionUtils::isC2kSupport()) {
        simState = getStatusManager()->getIntValue(RFX_STATUS_KEY_SIM_STATE);
    } else {
        // Legacy RIL without C2K don't support RFX_STATUS_KEY_SIM_STATE
        // Return ready if SIM insert without considering PIN state
        simState = mIsSimInsert ? 1 : 0;
    }
    return simState;
}

bool RpPhoneNumberController::isSimInserted() {
    return mIsSimInsert;
}

bool RpPhoneNumberController::hasSimInAnySlot() {
    if (mIsSimInsert) {
        return true;
    }
    int simCount = getSimCount();
    for (int i = 0; i < simCount; i++) {
        RpPhoneNumberController* eccNumberController = (RpPhoneNumberController *)findController(
                i, RFX_OBJ_CLASS_INFO(RpPhoneNumberController));
        if (eccNumberController != NULL && eccNumberController->isSimInserted()) {
            return true;
        }
    }
    return false;
}

void RpPhoneNumberController::updateForSimStateChanges(bool isSimInserted) {
    logD(RFX_LOG_TAG, "[%s] isSimInserted: %d", __FUNCTION__, isSimInserted);
    mDefaultEccSource->update(isSimInserted);
    updateEmergencySourcesForPlmnChange(NULL, isSimInserted);
}

void RpPhoneNumberController::updateEmergencySourcesForAllSimStateChanges(bool isSimInserted) {
    int simCount = getSimCount();
    for (int i = 0; i < simCount; i++) {
        RpPhoneNumberController* eccNumberController = (RpPhoneNumberController *)findController(
                i, RFX_OBJ_CLASS_INFO(RpPhoneNumberController));
        if (eccNumberController != NULL) {
            eccNumberController->updateForSimStateChanges(isSimInserted);
            eccNumberController->updateEmergencyNumber();
        }
    }
}

// Update emergency number when PLMN changes from peer slot
// For example: SIM1 have SIM and SIM2 no SIM, SIM2 emergency number will not update
// for PLMN because it can't get valid PLMN. In this case, we can update SIM2 emergency
// numbers if SIM1 got PLMN.
bool RpPhoneNumberController::updateEmergencySourcesFromPeer(String8 plmn) {
    if (getPlmn(m_slot_id).length() > MCC_CHAR_LEN || plmn.length() < MCC_CHAR_LEN
            || mIsSimInsert) {
        logD(RFX_LOG_TAG, "[%s] No need mIsSimInsert: %d", __FUNCTION__, mIsSimInsert);
        return false;
    }

    logD(RFX_LOG_TAG, "[%s] Update for PLMN: %s", __FUNCTION__, plmn.string());

    bool isChange = false;
    // reload XML ECC
    if (mXmlEccSource != NULL &&
            mXmlEccSource->update(plmn, mIsSimInsert)) {
        isChange = true;
    }

    // reload property ECC
    if (mPropertyEccSource != NULL &&
            mPropertyEccSource->update(plmn, mIsSimInsert)) {
        isChange = true;
    }

    return isChange;
}

void RpPhoneNumberController::removeNonEmergencyNumbers() {
    for (Vector<EmergencyNumber>::iterator iter = mEccList.begin(); iter != mEccList.end();) {
        if (iter != NULL) {
            if ((*iter).condition == (int)CONDITION_NEVER) {
                logD(RFX_LOG_TAG, "[%s] Remove %s", __FUNCTION__, (*iter).number.string());
                iter = mEccList.erase(iter);
            } else {
                ++iter;
            }
        }
    }
}