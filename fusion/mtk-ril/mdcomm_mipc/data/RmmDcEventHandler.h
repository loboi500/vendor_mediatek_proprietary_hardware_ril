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

#ifndef __RMM_DC_EVENT_HANDLER_H__
#define __RMM_DC_EVENT_HANDLER_H__

/*****************************************************************************
 * Include
 *****************************************************************************/
#include "RfxBaseHandler.h"
#include "RfxLinkCapacityEstimateData.h"
#include "RmmDcPdnManager.h"
#include "NetAction.h"

#include <sstream>
#include <list>
#include <map>


#define _IN6_IS_ULA(a)  \
    ((((a)->s6_addr[0] & 0xff) == 0xfc) || (((a)->s6_addr[0] & 0xff) == 0xfd))

#define DATA_SETTING_NUMBERS   5
#define SKIP_DATA_SETTINGS    -2
#define DATA_NOT_ALLOW_RETRY_TIME 500

#define MAX_PROFILEID_LENGTH 10   // max profileID length
#define MAX_LENGTH_MCCMNC 12      // max mccmnc length
#define MAX_LENGTH_PROPERTY_NAME 64    // max property name length

// max count of support qualitied network update apn
#define MAX_COUNT_QUALIFIED_NETWORK_UPDATE_APNS 3

#define RIL_E_OEM_MULTI_ALLOW_ERR RIL_E_OEM_ERROR_1

typedef enum {
    MOBILE_DATA      = 0,
    ROAMING_DATA     = 1,
    DEFAULT_DATA_SIM = 2,
    DOMESTIC_ROAMING_DATA = 3,
    INTERNATIONAL_ROAMING_DATA = 4
} DATA_SETTING_ITEM;

typedef enum {
    RETRY_TYPE_NO_SUGGEST = 0,
    RETRY_TYPE_NO_RETRY = 1,
    RETRY_TYPE_WITH_SUGGEST = 2
} MD_SUGGESTED_RETRY_TIME_TYPE;

typedef struct {
    char *apn;
    char *username;
    char *password;
    int apnTypeId;
    char *protocol;
    int authtype;
} ApnTableReq;

/// M: IWLAN AP_ASSISTED mode {@
typedef enum {
    SUPPORT_TRANSPORT_MODE_UNKNOW = 0,
    SUPPORT_TRANSPORT_MODE_CELLULAR_ONLY = 1,
    SUPPORT_TRANSPORT_MODE_WIFI_ONLY = 2,
    SUPPORT_TRANSPORT_MODE_CELLULAR_WIFI = 3
} SUPPORT_TRANSPORT_MODE;

typedef enum {
    PRIORITY_START = 0,
    PRIORITY_NULL = 1,
    PRIORITY_CELLULAR_ONLY = 2,
    PRIORITY_WIFI_ONLY = 3,
    PRIORITY_CELLULAR_PREFER = 4,
    PRIORITY_WIFI_PREFER = 5,
    PRIORITY_END = 6
} QUALIFIED_NETWORK_PRIORITY;

const int SUPPORT_QUALIFIED_NETWORK_UPDATE_APNS[MAX_COUNT_QUALIFIED_NETWORK_UPDATE_APNS] = {
    RIL_APN_TYPE_MMS,
    RIL_APN_TYPE_IMS,
    RIL_APN_TYPE_EMERGENCY
};
/// @}

/*****************************************************************************
 * Class RmmDcEventHandler
 *****************************************************************************/
class RmmDcEventHandler : public RfxBaseHandler, public NetObject {
    public:
        RmmDcEventHandler(int slot_id, int channel_id, RmmDcPdnManager* pdnManager);
        virtual ~RmmDcEventHandler();
        static int getIndexFromApnTable(unsigned int slot_id, ApnTableReq *pApnTableReq);

    protected:
        virtual void onHandleEvent(const sp<RfxMclMessage>& msg);
        virtual void onHandleResponse(const sp<RfxMclMessage>& msg);

    public:
        static RIL_MtkDataProfileInfo* s_LastApnTable[MAX_SIM_COUNT];
        static int s_nLastReqNum[MAX_SIM_COUNT];

        void requestSetupDataCall(const sp<RfxMclMessage>& msg);
        void requestDeactivateDataCall(const sp<RfxMclMessage>& msg);
        void onNwAct(const sp<RfxMclMessage>& msg);
        void onDataModify(const sp<RfxMclMessage>& msg);
        void onMePdnAct(const sp<RfxMclMessage>& msg);
        void onDataDeact(const sp<RfxMclMessage>& msg);
        void onPdnChange(const sp<RfxMclMessage>& msg);
        void onMePdnPropertyChange(const sp<RfxMclMessage>& msg, const int aid);
        void onQualifiedNetworkTypeChanged(const sp<RfxMclMessage>& msg);
        void requestSyncApnTable(const sp<RfxMclMessage>& msg);
        void requestSetInitialAttachApn(const sp<RfxMclMessage>& msg);
        void requestSyncDataSettingsToMd(const sp<RfxMclMessage>& msg);
        void requestResetMdDataRetryCount(const sp<RfxMclMessage>& msg);
        void requestOrSendDataCallList(const sp<RfxMclMessage>& msg);
        void requestOrSendDataCallList(const sp<RfxMclMessage>& msg, Vector<int> *vAidList);
        void requestOrSendDataCallList(const sp<RfxMclMessage>& msg, int aid);
        void requestClearAllPdnInfo(const sp<RfxMclMessage>& msg);
        void onRegisterUrcDone() {};
        void notifyPcoValue(int value, char* apn);
        void handlePcoInfo(const sp<RfxMclMessage>& msg);
        void handleQueryPcoAfterAttach(const sp<RfxMclMessage>& msg);
        void handleQueryPcoAfterAttachResponse(const sp<RfxMclMessage>& msg);
        // Cleanup all connections
        void handleResetAllConnections(const sp<RfxMclMessage>& msg);
        void resendPreferData();
        void requestSetPreferredDataModem(const sp<RfxMclMessage>& msg);
        void requestGetDataContextIds(const sp<RfxMclMessage>& msg);
        void requestSendQualifiedNetworkTypesChanged(const sp<RfxMclMessage>& msg);
        void handleMobileDataUsageNotify(const sp<RfxMclMessage>& msg);
        void requestStartKeepalive(const sp<RfxMclMessage>& msg);
        void requestStopKeepalive(const sp<RfxMclMessage>& msg);
        void updateKeepaliveStatus(const sp<RfxMclMessage>& msg);
        void onNwLimitNotify(const sp<RfxMclMessage>& msg);
        void onKernelAddressUpdated(const sp<RfxMclMessage>& msg);

        void onRadioCapabilityUpdated();
        void requestSetFdMode(const sp<RfxMclMessage>& msg);
        void requestSetLinkCapacityReportingCriteria(const sp<RfxMclMessage>& msg);
        void handleLinkCapacityEstimate(const sp<RfxMclMessage>& msg);
        void handleNetworkRejectCause(const sp<RfxMclMessage>& msg);
        void handleSendDeviceStateRequest(const sp<RfxMclMessage>& msg);
        void handleResponseFilterChanged(const sp<RfxMclMessage>& msg);

        // For Multi-SIM
        void handleDcAttachDetachRequest(const sp<RfxMclMessage>& msg, int type);

        RIL_DataCallFailCause convertFailCauseToRilStandard(int cause);
        int convertDeactCauseToMdStandard(int reason);
        void updateLastFailCause(int cause);
        int getLastFailCause();
        int isAllAidActive(Vector<int> *vAidList);
        int updateActiveStatusAndProfile(Vector<int> *vAidList = NULL, bool bUpdateProfile = true);
        int updateActiveStatusAndProfileById(int aid, bool bUpdateProfile = true);
        int updateDataCallProfile(int aid);
        void initDataCallResponse(MTK_RIL_Data_Call_Response_v11* responses, int length);
        void createDataResponse(int transIntfId, int protocol,
                MTK_RIL_Data_Call_Response_v11* response);
        bool createAndLaunchDataResponse(int result, int aid);
        String8 responsesToString(MTK_RIL_Data_Call_Response_v11* responses, int num);
        void freeDataResponse(MTK_RIL_Data_Call_Response_v11* response);
        int convertIpv6Address(char* output, char* input, int isLinkLocal);
        bool isIpv6Global(char *ipv6Addr);
        void sendDataCallListResponse(const sp<RfxMclMessage>& msg, int deactivatedAid = INVALID_AID);
        int deactivateDataCall(const int aid);
        int deactivateDataCall(const int aid, const int reason);
        int getInterfaceIdByTransIntfId(int transIntfId);
        int confirmPdnUsage(const int aid, const bool bUsed);
        bool isFallbackPdn(const int aid);
        bool notifyDeactReasonIfNeeded(const int deactivatedAid);
        bool isDataAllowed(const char* pReqApn);
        bool isSupportWifiBearer(int bearerBitmask);
        bool getMccmnc(char* mccmnc);
        bool isHandoverRequest(int reason, int profileId, int *pTransIntfId);
        void sendQualifiedNetworkTypesChanged(int aid, int newRat);
        void setPdnInfoProperty();
        void adjustBearerBitmask(RIL_MtkDataProfileInfo **dataProfilePtrs, int count);
        bool isSupportWifiType(int typesBitmask);
        void resetLastApnTable();
        int decodeDataCallProfile(const sp<RfxMipcData> mipcRet, const DCProfileSource src);
        void decodeMipcV4Address(const sp<RfxMipcData> mipcData, int type, int addrCount,
                char addr[][MAX_IPV4_ADDRESS_LENGTH]);
        void decodeMipcV6Address(const sp<RfxMipcData> mipcData, int type, int addrCount,
                char addr[][MAX_IPV6_ADDRESS_LENGTH]);
        void updatePdnInfoByInterfaceInfo(int aid, CallbackInfo *pCbInfo);
        void handleResetMdDataRetryCountResponse(const sp<RfxMclMessage>& msg);
        void handleDsdaStateChanged(const sp<RfxMclMessage>& msg);
        void handleEnableDsdaIndication(const sp<RfxMclMessage>& msg);
        void handleGetDsdaStatus(const sp<RfxMclMessage>& msg);
        void handleDsdaStatusResponse(const sp<RfxMclMessage>& msg);
        void handleUpdateDataRatRequest(const sp<RfxMclMessage>& msg);
        void handleGetSlicingConfig(const sp<RfxMclMessage>& msg);
        void handleGetSlicingConfigResponse(const sp<RfxMclMessage>& msg);
        void handleUrspReevaluate(const sp<RfxMclMessage>& msg);

    private:
        void initializeFastDormancy();
        void disableLegacyFastDormancy();
        bool isValidInitialAttachApn(const char* apn);
        bool isSupportSelfSetInitialAttach();
        void handleIfVendorSelfIaNeeded();
        void updateIpv6PdnInfo(int aid);
        bool needWaitNetAgentNotification(int aid);
        int getModemSuggestedRetryTime(const char *apnName);
        int handleFastdormancyCommand(int mode, int param1, int param2);
        int getCurrentRat();
        bool updateEpsQos(int aid);
        bool updateNrQos(int aid);
        bool updateQosFilters(int aid);
        int convertAddrAndSubnetMask(char* output, const char* input);
        int calculateSubnetMaskNumber(char* input);
        bool updateQosInformation(int aid, bool isDedicateBearer = false);
        void updateTdInfo(int aid);
        void getSliceInfo(RIL_SlicingConfig &sc, String8 plmn);
        void dumpSliceConfig(RIL_SlicingConfig sc);
        void setOsId();
        int getOsIdArray(uint8_t *osId);
        bool isValidDedicateBearer(int dftId, int ddctId);

    protected:
        RmmDcPdnManager* m_pPdnManager;
        int m_nGprsFailureCause;

    private:
        static int s_dataSetting[MAX_SIM_COUNT][DATA_SETTING_NUMBERS];
        static int* s_ApnCmdIndex[MAX_SIM_COUNT];
        bool mIsUserBuild;
        std::map<int, sp<RfxMclMessage>> m_mapAidReqmsg; // <aid, ReqMessage>
        int mCurrentFdState;
};

#endif /* __RMM_DC_EVENT_HANDLER_H__ */
