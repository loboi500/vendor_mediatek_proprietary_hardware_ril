/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 */
/* MediaTek Inc. (C) 2018. All rights reserved.
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

#define LOG_TAG "RadioConfig_service"

#include <android/hardware/radio/config/1.3/IRadioConfig.h>
#include <android/hardware/radio/config/1.3/IRadioConfigResponse.h>
#include <android/hardware/radio/config/1.2/IRadioConfigIndication.h>
#include <hidl/HidlTransportSupport.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>

#include <hwbinder/IPCThreadState.h>
#include <hwbinder/ProcessState.h>
#include <hidl/HidlTransportSupport.h>
#include <utils/SystemClock.h>
#include <inttypes.h>
#include <libmtkrilutils.h>
#include <mtk_log.h>
#include <mtk_properties.h>
#include <mtkconfigutils.h>
#include <radioConfig_service.h>
#include <ril_service.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <android/hardware/radio/1.6/types.h>
#include <android/hardware/radio/1.6/IRadioResponse.h>

using namespace android::hardware::radio;
using namespace android::hardware::radio::V1_0;

using namespace ::android::hardware::radio::config::V1_0;
using namespace ::android::hardware::radio::config::V1_1;
using namespace ::android::hardware::radio::config::V1_2;
using namespace ::android::hardware::radio::config::V1_3;

namespace RADIO_CONFIG_V1_0 = android::hardware::radio::config::V1_0;
namespace RADIO_CONFIG_V1_1 = android::hardware::radio::config::V1_1;
namespace RADIO_CONFIG_V1_2 = android::hardware::radio::config::V1_2;
namespace RADIO_CONFIG_V1_3 = android::hardware::radio::config::V1_3;

using ::android::hardware::configureRpcThreadpool;
using ::android::hardware::joinRpcThreadpool;
using ::android::hardware::Return;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::hidl_array;
using ::android::hardware::hidl_memory;
using ::android::hardware::Void;
using android::CommandInfo;
using android::RequestInfo;
using android::requestToString;
using android::status_t;
using android::sp;
using android::OK;

namespace AOSP_V1_6 = android::hardware::radio::V1_6;


#if defined(ANDROID_MULTI_SIM)
#define CALL_ONREQUEST(a, b, c, d, e) \
        s_radioConfigFunctions->onRequest((a), (b), (c), (d), ((RIL_SOCKET_ID)(e)))
#else
#define CALL_ONREQUEST(a, b, c, d, e) \
        s_radioConfigFunctions->onRequest((a), (b), (c), (d))
#endif


extern "C" int toRealSlot(unsigned int slotId);

RIL_RadioFunctions *s_radioConfigFunctions = NULL;
static CommandInfo *s_commands;

struct RadioConfigImpl;
sp<RadioConfigImpl> radioConfigService = NULL;
// counter used for synchronization. It is incremented every time response callbacks are updated.
volatile int32_t mCounterRadioConfig[MAX_SIM_COUNT];

extern bool isMtkFwkAddonNotExisted(unsigned int slotId);

struct RadioConfigImpl : public android::hardware::radio::config::V1_3::IRadioConfig {
    int32_t mSlotId;
    sp<RADIO_CONFIG_V1_0::IRadioConfigResponse> mRadioConfigResponse;
    sp<RADIO_CONFIG_V1_0::IRadioConfigIndication> mRadioConfigIndication;
    sp<RADIO_CONFIG_V1_1::IRadioConfigResponse> mRadioConfigResponseV1_1;
    sp<RADIO_CONFIG_V1_1::IRadioConfigIndication> mRadioConfigIndicationV1_1;
    sp<RADIO_CONFIG_V1_2::IRadioConfigResponse> mRadioConfigResponseV1_2;
    sp<RADIO_CONFIG_V1_2::IRadioConfigIndication> mRadioConfigIndicationV1_2;
    sp<RADIO_CONFIG_V1_3::IRadioConfigResponse> mRadioConfigResponseV1_3;
//    sp<RADIO_CONFIG_V1_3::IRadioConfigIndication> mRadioConfigIndicationV1_3;

    // Methods from ::android::hardware::radio::config::V1_0::IRadioConfig follow.
    Return<void> getSimSlotsStatus(int32_t serial) override;
    Return<void> setResponseFunctions(
        const sp<::android::hardware::radio::config::V1_0::IRadioConfigResponse>&
            radioConfigResponse,
        const sp<::android::hardware::radio::config::V1_0::IRadioConfigIndication>&
            radioConfigIndication) override;
    Return<void> setSimSlotsMapping(int32_t serial, const hidl_vec<uint32_t>& slotMap) override;

    // Methods from ::android::hardware::radio::config::V1_1::IRadioConfig follow.
    Return<void> getPhoneCapability(int32_t serial);
    Return<void> setPreferredDataModem(int32_t serial, uint8_t modemId);
    Return<void> setModemsConfig(int32_t serial,
        const RADIO_CONFIG_V1_1::ModemsConfig& modemsConfig);
    Return<void> getModemsConfig(int32_t serial);
//    Return<void> getPhoneCapability_1_3(int32_t serial);
    Return<void> getHalDeviceCapabilities(int32_t serial);
    void checkReturnStatus(Return<void>& ret);
};

void checkReturnStatus(int32_t slotId, Return<void>& ret) {
    if (ret.isOk() == false) {
        mtkLogE(LOG_TAG, "radioconfig checkReturnStatus: unable to call response/indication");
        // Remote process hosting the callbacks must be dead. Reset the callback objects;
        // there's no other recovery to be done here. When the client process is back up, it will
        // call setResponseFunctions()
        // Caller should already hold rdlock, release that first
        // note the current counter to avoid overwriting updates made by another thread before
        // write lock is acquired.
        int counter = mCounterRadioConfig[slotId];
        pthread_rwlock_t *radioServiceRwlockPtr = radio::getRadioServiceRwlock(slotId);
        int gotRLock = 0;
        if (radio::isTidInRLock((int) slotId, pthread_self()) != -1) {
            // had got the lock
            gotRLock = 1;
            radio::unlockRadioServiceRlock(radioServiceRwlockPtr, (int) slotId);
            mtkLogV(LOG_TAG, "radioconfig checkReturnStatus: release r lock %d", slotId);
        } else {
            mtkLogE(LOG_TAG, "radioconfig checkReturnStatus: didn't get r lock %d", slotId);
        }

        // acquire wrlock
        radio::lockRadioServiceWlock(radioServiceRwlockPtr, (int) slotId);
        mtkLogD(LOG_TAG, "radioconfig checkReturnStatus: got lock %d", slotId);
        // make sure the counter value has not changed
        if (counter == mCounterRadioConfig[slotId]) {
            mtkLogI(LOG_TAG,"radioconfig checkReturnStatus[%d]: reset response/indication", slotId);
            radioConfigService->mRadioConfigResponse = NULL;
            radioConfigService->mRadioConfigIndication = NULL;
            radioConfigService->mRadioConfigResponseV1_1 = NULL;
            radioConfigService->mRadioConfigIndicationV1_1 = NULL;
            radioConfigService->mRadioConfigResponseV1_2 = NULL;
            radioConfigService->mRadioConfigIndicationV1_2 = NULL;
            radioConfigService->mRadioConfigResponseV1_3 = NULL;
//            radioConfigService->mRadioConfigIndicationV1_3 = NULL;
            mCounterRadioConfig[slotId]++;
        } else {
            mtkLogE(LOG_TAG, "radioconfig checkReturnStatus: not resetting resFunc as they likely"
                    "got updated on another thread");
        }
        // release wrlock
        radio::unlockRadioServiceWlock(radioServiceRwlockPtr, (int) slotId);
        mtkLogV(LOG_TAG, "radioconfig checkReturnStatus: release lock %d", slotId);
        if(gotRLock == 1) {
            // Reacquire rdlock
            radio::lockRadioServiceRlock(radioServiceRwlockPtr, (int)slotId);
            mtkLogV(LOG_TAG, "radioconfig checkReturnStatus: got r lock %d", slotId);
        } else {
            mtkLogE(LOG_TAG, "checkReturnStatus: don't need to re-get r lock %d", slotId);
        }
    }
}

void populateConfigResponseInfo(RadioResponseInfo& responseInfo, int serial, int responseType,
                         RIL_Errno e) {
    responseInfo.serial = serial;
    switch (responseType) {
        case RESPONSE_SOLICITED:
            responseInfo.type = RadioResponseType::SOLICITED;
            break;
        case RESPONSE_SOLICITED_ACK_EXP:
            responseInfo.type = RadioResponseType::SOLICITED_ACK_EXP;
            break;
    }
    responseInfo.error = (RadioError) e;
}

bool dispatchConfigVoid(int serial, int slotId, int request) {
    RequestInfo *pRI = android::addRequestToList(serial, slotId, request);
    if (pRI == NULL) {
        return false;
    }
    CALL_ONREQUEST(request, NULL, 0, pRI, slotId);
    return true;
}

void RadioConfigImpl::checkReturnStatus(Return<void>& ret) {
    ::checkReturnStatus(mSlotId, ret);
}

Return<void> RadioConfigImpl::getSimSlotsStatus(int32_t serial) {
    mtkLogD(LOG_TAG, "radioConfig::getSimSlotsStatus ");
    dispatchConfigVoid(serial, mSlotId, RIL_REQUEST_GET_SLOT_STATUS);
    return Void();
}

Return<void> RadioConfigImpl::setResponseFunctions(
        const sp<RADIO_CONFIG_V1_0::IRadioConfigResponse>& radioConfigResponse,
        const sp<RADIO_CONFIG_V1_0::IRadioConfigIndication>& radioConfigIndication) {
    mtkLogD(LOG_TAG, "radioConfig::setResponseFunctions");
    pthread_rwlock_t *radioServiceRwlockPtr = radio::getRadioServiceRwlock(mSlotId);
    radio::lockRadioServiceWlock(radioServiceRwlockPtr, (int)mSlotId);
    mRadioConfigResponse = radioConfigResponse;
    mRadioConfigIndication = radioConfigIndication;
    mRadioConfigResponseV1_1 = RADIO_CONFIG_V1_1::IRadioConfigResponse::castFrom(mRadioConfigResponse).withDefault(nullptr);
    mRadioConfigIndicationV1_1 = RADIO_CONFIG_V1_1::IRadioConfigIndication::castFrom(mRadioConfigIndication).withDefault(nullptr);

    mRadioConfigResponseV1_2 = RADIO_CONFIG_V1_2::IRadioConfigResponse::castFrom(mRadioConfigResponse).withDefault(nullptr);
    mRadioConfigIndicationV1_2 = RADIO_CONFIG_V1_2::IRadioConfigIndication::castFrom(mRadioConfigIndication).withDefault(nullptr);

    mRadioConfigResponseV1_3 = RADIO_CONFIG_V1_3::IRadioConfigResponse::castFrom(mRadioConfigResponse).withDefault(nullptr);
//    mRadioConfigIndicationV1_3 = RADIO_CONFIG_V1_3::IRadioConfigIndication::castFrom(mRadioConfigIndication).withDefault(nullptr);

    mCounterRadioConfig[mSlotId]++;
    radio::unlockRadioServiceWlock(radioServiceRwlockPtr, (int)mSlotId);
    return Void();
}

Return<void> RadioConfigImpl::setSimSlotsMapping(int32_t serial,
                                             const hidl_vec<uint32_t>& slotMap) {
    mtkLogD(LOG_TAG, "radioConfig::setSimSlotsMapping ");
    RequestInfo *pRI = android::addRequestToList(serial, mSlotId,
                                                 RIL_REQUEST_SET_LOGICAL_TO_PHYSICAL_SLOT_MAPPING);
    if (pRI == NULL) {
        return Void();
    }
    int num = slotMap.size();
    int map[num];
    for (int i = 0; i < num; i++) {
        map[i] = slotMap[i];
    }

    CALL_ONREQUEST(pRI->pCI->requestNumber, map, num * sizeof(int), pRI, mSlotId);
    return Void();
}

Return<void> RadioConfigImpl::getPhoneCapability(int32_t serial) {
    mtkLogD(LOG_TAG, "radioConfig::getPhoneCapability serial=%d", serial);
    RequestInfo *pRI = android::addRequestToList(serial, mSlotId,
            RIL_REQUEST_GET_PHONE_CAPABILITY);
    if (pRI == NULL) {
        return Void();
    }
    CALL_ONREQUEST(pRI->pCI->requestNumber, NULL, 0, pRI, mSlotId);
    return Void();
}

Return<void> RadioConfigImpl::setPreferredDataModem(int32_t serial, uint8_t modemId) {
    mtkLogD(LOG_TAG, "radioConfig::setPreferredDataModem serial=%d", serial);
    mtk_property_set("vendor.ril.data.preferred_data_mode", "1");
    RequestInfo *pRI = android::addRequestToList(serial, mSlotId,
            RIL_REQUEST_SET_PREFERRED_DATA_MODEM);
    if (pRI == NULL) {
        return Void();
    }
    int mId[] = {(int)modemId};
    CALL_ONREQUEST(pRI->pCI->requestNumber, mId, sizeof(int), pRI, mSlotId);
    return Void();
}

Return<void> RadioConfigImpl::setModemsConfig(int32_t serial,
    const RADIO_CONFIG_V1_1::ModemsConfig& modemsConfig) {
    mtkLogD(LOG_TAG, "radioConfig::setModemsConfig serial=%d", serial);
    RadioResponseInfo responseInfo = {};
    RIL_Errno rilError = RIL_E_SUCCESS;
    if (modemsConfig.numOfLiveModems <= 0 ||
        modemsConfig.numOfLiveModems > 3) {
        rilError = RIL_E_INVALID_ARGUMENTS;
    } else if (isMtkFwkAddonNotExisted(mSlotId)) {
        rilError = RIL_E_REQUEST_NOT_SUPPORTED;
    }
    if (rilError != RIL_E_SUCCESS) {
        // not support
        populateConfigResponseInfo(responseInfo, serial,
                RESPONSE_SOLICITED, rilError);
        Return<void> retStatus = radioConfigService->mRadioConfigResponseV1_1->
                setModemsConfigResponse(responseInfo);
        radioConfigService->checkReturnStatus(retStatus);
    } else {
        RequestInfo *pRI = android::addRequestToList(serial, mSlotId,
                RIL_REQUEST_SET_MODEM_CONFIG);
        if (pRI == NULL) {
            return Void();
        }
        int mode[] = {(int)modemsConfig.numOfLiveModems};
        CALL_ONREQUEST(pRI->pCI->requestNumber, mode, sizeof(int), pRI, mSlotId);
    }
    return Void();
}

Return<void> RadioConfigImpl::getModemsConfig(int32_t serial) {
    if (radioConfigService != NULL && radioConfigService ->mRadioConfigResponseV1_1 != NULL) {
        RadioResponseInfo responseInfo = {};
        RADIO_CONFIG_V1_1::ModemsConfig modemConfig = {};
        modemConfig.numOfLiveModems = (uint8_t)getSimCount();
        populateConfigResponseInfo(responseInfo, serial, RESPONSE_SOLICITED, RIL_E_SUCCESS);
        Return<void> retStatus = radioConfigService->mRadioConfigResponseV1_1->
                getModemsConfigResponse(responseInfo, modemConfig);
        radioConfigService->checkReturnStatus(retStatus);
    } else {
        mtkLogE(LOG_TAG, "setPreferredDataModemResponse: mRadioConfigResponse is NULL");
    }
    return Void();
}

/*Return<void> RadioConfigImpl::getPhoneCapability_1_3(int32_t serial) {
    return Void();
}*/


Return<void> RadioConfigImpl::getHalDeviceCapabilities(int32_t serial) {
    if (radioConfigService != NULL && radioConfigService->mRadioConfigResponseV1_3 != NULL) {
        AOSP_V1_6::RadioResponseInfo responseInfo = {};
        responseInfo.serial = serial;
        responseInfo.type = RadioResponseType::SOLICITED;
        responseInfo.error = (AOSP_V1_6::RadioError) RIL_E_SUCCESS;
        bool modemReducedFeatureSet1 = false;
        Return<void> retStatus = radioConfigService->mRadioConfigResponseV1_3->
                getHalDeviceCapabilitiesResponse(responseInfo, modemReducedFeatureSet1);

        radioConfigService->checkReturnStatus(retStatus);
    } else {
        mtkLogE(LOG_TAG, "getHalDeviceCapabilitiesResponse: mRadioConfigResponseV1_3 is NULL");
    }

    return Void();
}

hidl_string convertConfigCharPtrToHidlString(const char *ptr) {
    hidl_string ret;
    if (ptr != NULL) {
        ret.setToExternal(ptr, strlen(ptr));
    }
    return ret;
}

RadioIndicationType convertConfigIntToRadioIndicationType(int indicationType) {
    return indicationType == RESPONSE_UNSOLICITED ? (RadioIndicationType::UNSOLICITED) :
            (RadioIndicationType::UNSOLICITED_ACK_EXP);
}

int radioConfig::getSimSlotsStatusResponse(unsigned int slotId, android::ClientId clientId __unused,
                                           int responseType, int serial, RIL_Errno e,
                                           const void *response, size_t responseLen ) {
    mtkLogD(LOG_TAG, "getSimSlotsStatusResponse: response");
    if (radioConfigService != NULL && radioConfigService ->mRadioConfigResponseV1_2 != NULL) {
        mtkLogD(LOG_TAG, "radioConfigService ->mRadioConfigResponseV1_2 != NULL");
        RadioResponseInfo responseInfo = {};
        populateConfigResponseInfo(responseInfo, serial, responseType, e);
        hidl_vec<RADIO_CONFIG_V1_2::SimSlotStatus> slotStatus = {};
        if (response == NULL || responseLen % sizeof(RIL_SimSlotStatus *) != 0) {
            mtkLogE(LOG_TAG, "getSimSlotsStatusResponse: Invalid response");
            if (e == RIL_E_SUCCESS) responseInfo.error = RadioError::INVALID_RESPONSE;
        } else {
            int num = responseLen / sizeof(RIL_SimSlotStatus *);
            slotStatus.resize(num);
            for (int i = 0; i < num; i++) {
                RIL_SimSlotStatus *p_cur = ((RIL_SimSlotStatus **)response)[i];
                slotStatus[i].base.cardState = (CardState) p_cur->card_state;
                slotStatus[i].base.slotState = (SlotState) p_cur->slotState;
                slotStatus[i].base.atr = convertConfigCharPtrToHidlString(p_cur->atr);
                slotStatus[i].base.logicalSlotId = p_cur->logicalSlotId;
                slotStatus[i].base.iccid = convertConfigCharPtrToHidlString(p_cur->iccId);
                // For radio_config 1.2
                slotStatus[i].eid = convertConfigCharPtrToHidlString(p_cur->eid);
            }
        }
        Return<void> retStatus = radioConfigService->mRadioConfigResponseV1_2->
                    getSimSlotsStatusResponse_1_2(responseInfo, slotStatus);
        radioConfigService->checkReturnStatus(retStatus);
    } else if (radioConfigService != NULL && radioConfigService ->mRadioConfigResponse != NULL) {
        mtkLogD(LOG_TAG, "radioConfigService ->mRadioConfigResponse != NULL");
        RadioResponseInfo responseInfo = {};
        populateConfigResponseInfo(responseInfo, serial, responseType, e);
        hidl_vec<RADIO_CONFIG_V1_0::SimSlotStatus> slotStatus = {};
        if (response == NULL || responseLen % sizeof(RIL_SimSlotStatus *) != 0) {
            mtkLogE(LOG_TAG, "getSimSlotsStatusResponse: Invalid response");
            if (e == RIL_E_SUCCESS) responseInfo.error = RadioError::INVALID_RESPONSE;
        } else {
            int num = responseLen / sizeof(RIL_SimSlotStatus *);
            slotStatus.resize(num);
            for (int i = 0; i < num; i++) {
                RIL_SimSlotStatus *p_cur = ((RIL_SimSlotStatus **)response)[i];
                slotStatus[i].cardState = (CardState) p_cur->card_state;
                slotStatus[i].slotState = (SlotState) p_cur->slotState;
                slotStatus[i].atr = convertConfigCharPtrToHidlString(p_cur->atr);
                slotStatus[i].logicalSlotId = p_cur->logicalSlotId;
                slotStatus[i].iccid = convertConfigCharPtrToHidlString(p_cur->iccId);
            }
        }
        Return<void> retStatus = radioConfigService->mRadioConfigResponse->
                    getSimSlotsStatusResponse(responseInfo, slotStatus);
        radioConfigService->checkReturnStatus(retStatus);
    } else {
        mtkLogE(LOG_TAG, "getSimSlotsStatusResponse: mRadioConfigResponse is NULL");
    }
    return 0;
}

int radioConfig::setSimSlotsMappingResponse(unsigned int slotId, android::ClientId clientId __unused,
                                            int responseType, int serial, RIL_Errno e,
                                            const void *response, size_t responseLen ) {
    if (radioConfigService != NULL && radioConfigService ->mRadioConfigResponse != NULL) {
        RadioResponseInfo responseInfo = {};
        populateConfigResponseInfo(responseInfo, serial, responseType, e);
        Return<void> retStatus = radioConfigService->mRadioConfigResponse->
                setSimSlotsMappingResponse(responseInfo);
        radioConfigService->checkReturnStatus(retStatus);
    } else {
        mtkLogE(LOG_TAG, "setSimSlotsMappingResponse: mRadioConfigResponse is NULL");
    }
    return 0;
}

int radioConfig::setPreferredDataModemResponse(unsigned int slotId, android::ClientId clientId,
        int responseType, int serial, RIL_Errno e, const void *response, size_t responseLen ) {
    if (radioConfigService != NULL && radioConfigService ->mRadioConfigResponseV1_1 != NULL) {
        RadioResponseInfo responseInfo = {};
        populateConfigResponseInfo(responseInfo, serial, responseType, e);
        Return<void> retStatus = radioConfigService->mRadioConfigResponseV1_1->
                setPreferredDataModemResponse(responseInfo);
        radioConfigService->checkReturnStatus(retStatus);
    } else {
        mtkLogE(LOG_TAG, "setPreferredDataModemResponse: mRadioConfigResponse is NULL");
    }
    return 0;
}

int radioConfig::getPhoneCapabilityResponse(unsigned int slotId, android::ClientId clientId,
        int responseType, int serial, RIL_Errno e, const void *response, size_t responselen) {
    if (radioConfigService != NULL && radioConfigService ->mRadioConfigResponseV1_1 != NULL) {
        RadioResponseInfo responseInfo = {};
        RADIO_CONFIG_V1_1::PhoneCapability phoneCapability = {};
        populateConfigResponseInfo(responseInfo, serial, responseType, e);

        if (response == NULL) {
            mtkLogE(LOG_TAG, "getPhoneCapabilityResponse: Invalid response");
        } else {
            unsigned int mdMaxSimCount = getMdMaxSimCount();
            RIL_PhoneCapability *pPhoneCapability = ((RIL_PhoneCapability *) response);
            phoneCapability.maxActiveData = pPhoneCapability->maxActiveData;
            phoneCapability.maxActiveInternetData = pPhoneCapability->maxActiveInternetData;
            phoneCapability.isInternetLingeringSupported
                    = pPhoneCapability->isInternetLingeringSupported;
            phoneCapability.logicalModemList.resize(mdMaxSimCount);
            for (unsigned int i = 0; i < mdMaxSimCount; i++) {
                phoneCapability.logicalModemList[i].modemId
                        = pPhoneCapability->logicalModemList[i].modemId;
            }
        }
        Return<void> retStatus = radioConfigService->mRadioConfigResponseV1_1->
                getPhoneCapabilityResponse(responseInfo, phoneCapability);
        radioConfigService->checkReturnStatus(retStatus);
    } else {
        mtkLogE(LOG_TAG, "getPhoneCapabilityResponse: mRadioConfigResponse is NULL");
    }
    return 0;
}

int radioConfig::simSlotStatusChangedInd(unsigned int slotId,
        int indicationType, int token, RIL_Errno e, const void *response, size_t responseLen) {
    if (radioConfigService != NULL && radioConfigService ->mRadioConfigIndicationV1_2!= NULL) {
        mtkLogD(LOG_TAG, "radioConfigService ->mRadioConfigIndicationV1_2 != NULL");
        if (response == NULL || responseLen % sizeof(RIL_SimSlotStatus *) != 0) {
            mtkLogE(LOG_TAG, "simSlotStatusChangedInd: Invalid response");
            return 0;
        }
        hidl_vec<RADIO_CONFIG_V1_2::SimSlotStatus> slotStatus;
        int num = responseLen / sizeof(RIL_SimSlotStatus *);
        slotStatus.resize(num);
        for (int i = 0; i < num; i++) {
            RIL_SimSlotStatus *p_cur = ((RIL_SimSlotStatus **)response)[i];
            slotStatus[i].base.cardState = (CardState) p_cur->card_state;
            slotStatus[i].base.slotState = (SlotState) p_cur->slotState;
            slotStatus[i].base.atr = convertConfigCharPtrToHidlString(p_cur->atr);
            slotStatus[i].base.logicalSlotId = p_cur->logicalSlotId;
            slotStatus[i].base.iccid = convertConfigCharPtrToHidlString(p_cur->iccId);
            // For radio config 1.2
            slotStatus[i].eid = convertConfigCharPtrToHidlString(p_cur->eid);
        }
        Return<void> retStatus = radioConfigService->mRadioConfigIndicationV1_2
                ->simSlotsStatusChanged_1_2(convertConfigIntToRadioIndicationType(indicationType),
                slotStatus);
        radioConfigService->checkReturnStatus(retStatus);
    } else if (radioConfigService != NULL && radioConfigService ->mRadioConfigIndication != NULL) {
        if (response == NULL || responseLen % sizeof(RIL_SimSlotStatus *) != 0) {
            mtkLogE(LOG_TAG, "simSlotStatusChangedInd: Invalid response");
            return 0;
        }
        hidl_vec<RADIO_CONFIG_V1_0::SimSlotStatus> slotStatus;
        int num = responseLen / sizeof(RIL_SimSlotStatus *);
        slotStatus.resize(num);
        for (int i = 0; i < num; i++) {
            RIL_SimSlotStatus *p_cur = ((RIL_SimSlotStatus **)response)[i];
            slotStatus[i].cardState = (CardState) p_cur->card_state;
            slotStatus[i].slotState = (SlotState) p_cur->slotState;
            slotStatus[i].atr = convertConfigCharPtrToHidlString(p_cur->atr);
            slotStatus[i].logicalSlotId = p_cur->logicalSlotId;
            slotStatus[i].iccid = convertConfigCharPtrToHidlString(p_cur->iccId);
        }

        mtkLogD(LOG_TAG, "radioConfigService ->mRadioConfigIndication != NULL");
        Return<void> retStatus = radioConfigService->mRadioConfigIndication
                ->simSlotsStatusChanged(convertConfigIntToRadioIndicationType(indicationType),
                slotStatus);
        radioConfigService->checkReturnStatus(retStatus);
    } else {
        mtkLogE(LOG_TAG, "radioConfigService[%d] or mRadioConfigIndication is NULL",
                slotId);
    }
    return 0;
}

int radioConfig::setModemsConfigResponse(unsigned int slotId, android::ClientId clientId,
        int responseType, int serial, RIL_Errno e, const void *response, size_t responseLen ) {
    if (radioConfigService != NULL && radioConfigService ->mRadioConfigResponseV1_1 != NULL) {
        RadioResponseInfo responseInfo = {};
        populateConfigResponseInfo(responseInfo, serial, responseType, e);
        Return<void> retStatus = radioConfigService->mRadioConfigResponseV1_1->
                setModemsConfigResponse(responseInfo);
        radioConfigService->checkReturnStatus(retStatus);
        if (e == RIL_E_SUCCESS) {
            // create local request to reset modem
            mtkLogI(LOG_TAG, "setModemsConfig successfully, reset modem/TRM");
            mtk_property_set("vendor.ril.disable.eboot", "1");
            RequestInfo *pRI = android::addRequestToList(0, slotId, RIL_REQUEST_RESTART_RILD);
            if (pRI == NULL) {
                mtkLogE(LOG_TAG, "setModemsConfigResponse: pRI is NULL");
                return 0;
            }
            pRI->local = 1;

            CALL_ONREQUEST(RIL_REQUEST_RESTART_RILD, NULL, 0, pRI, slotId);
        }
    } else {
        mtkLogE(LOG_TAG, "setModemsConfigResponse: mRadioConfigResponse is NULL");
    }
    return 0;
}

void radioConfig::registerService(RIL_RadioFunctions *callbacks, CommandInfo *commands) {
    using namespace android::hardware;

    s_radioConfigFunctions = callbacks;
    s_commands = commands;
    configureRpcThreadpool(1, true);

    radioConfigService = new RadioConfigImpl;
    radioConfigService->mSlotId = 0;
    status_t status = radioConfigService->registerAsService();
    mtkLogD(LOG_TAG, "radioConfig::registerService status: %d", status);

}

