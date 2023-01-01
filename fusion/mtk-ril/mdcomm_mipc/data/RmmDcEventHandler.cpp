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
#include <linux/sockios.h>
#include <sys/socket.h>
#include <memory>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <regex>

#include "NetAgentCommon.h"
#include "NetAgentService.h"

#include "RmmDataDefs.h"
#include "RmmDcUtility.h"
#include "RfxAttachApnInfo.h"
#include "RfxRawData.h"
#include "RfxStringData.h"
#include "RfxStringsData.h"
#include "RfxVoidData.h"
#include "RfxIntsData.h"
#include "RfxDataCallResponseData.h"
#include "RfxPcoData.h"
#include "RfxPcoIaData.h"
#include "RfxPcoInfo.h"
#include "RfxQualifiedNetworkInfo.h"
#include "RfxMessageId.h"
#include "RfxMipcData.h"
#include "RfxNaCbInfoData.h"
#include "RmmDcEventHandler.h"
#include "RfxRilUtils.h"
#include "tinyxml.h"
#include <libmtkrilutils.h>
#include "RfxKeepaliveStatusData.h"
#include "RfxNetlinkIpv6InfoData.h"
#include "RfxSlicingConfigResponseData.h"
#include "RmmCapabilitySwitchUtil.h"
#include "mipc_api.h"
#include "mipc_msg_host.h"

#define RFX_LOG_TAG "RmmDcEvent"
#define MAX_AT_CMD_LENGTH 512
#define CMD_INDEX_OFFSET 100
// See AOSP define in DataConnection.java OS_ID
#define ANDROID_OS_ID "97-a4-98-e3-fc-92-5c-94-89-86-03-33-d0-6e-4e-47"

/*****************************************************************************
 * Class RmmDcEventHandler
 *****************************************************************************/
RFX_REGISTER_DATA_TO_URC_ID(RfxPcoData,                 RFX_MSG_UNSOL_PCO_DATA);
RFX_REGISTER_DATA_TO_URC_ID(RfxPcoIaData,               RFX_MSG_UNSOL_PCO_DATA_AFTER_ATTACHED);
RFX_REGISTER_DATA_TO_URC_ID(RfxIntsData,                RFX_MSG_URC_QUALIFIED_NETWORK_TYPES_CHANGED);
RFX_REGISTER_DATA_TO_URC_ID(RfxIntsData,                RFX_MSG_URC_MOBILE_DATA_USAGE);
RFX_REGISTER_DATA_TO_URC_ID(RfxKeepaliveStatusData,     RFX_MSG_URC_KEEPALIVE_STATUS);
RFX_REGISTER_DATA_TO_URC_ID(RfxIntsData,                RFX_MSG_URC_NW_LIMIT);
RFX_REGISTER_DATA_TO_URC_ID(RfxIntsData,                RFX_MSG_UNSOL_ON_DSDA_CHANGED);
RFX_REGISTER_DATA_TO_EVENT_ID(RfxNaCbInfoData,          RFX_MSG_EVENT_KERNEL_ADDRESS_UPDATED);
RFX_REGISTER_DATA_TO_EVENT_ID(RfxVoidData,              RFX_MSG_EVENT_REQ_DATA_CONTEXT_IDS);
RFX_REGISTER_DATA_TO_EVENT_ID(RfxIntsData,              RFX_MSG_EVENT_SEND_QUALIFIED_NETWORK_TYPES_CHANGED);
RFX_REGISTER_DATA_TO_EVENT_ID(RfxVoidData,              RFX_MSG_EVENT_QUERY_SELF_IA);

RIL_MtkDataProfileInfo* RmmDcEventHandler::s_LastApnTable[MAX_SIM_COUNT] = {NULL};
int RmmDcEventHandler::s_nLastReqNum[MAX_SIM_COUNT] = {0};
int* RmmDcEventHandler::s_ApnCmdIndex[MAX_SIM_COUNT] = {NULL};

int RmmDcEventHandler::s_dataSetting[MAX_SIM_COUNT][DATA_SETTING_NUMBERS] = {{0}};

RmmDcEventHandler::RmmDcEventHandler(int slot_id, int channel_id, RmmDcPdnManager* pdnManager)
: RfxBaseHandler(slot_id, channel_id), m_pPdnManager(pdnManager), m_nGprsFailureCause(PDP_FAIL_ERROR_UNSPECIFIED) {
    mIsUserBuild = RmmDcUtility::isUserBuild();
    mCurrentFdState = 1;

    const int eventList[] = {
        RFX_MSG_EVENT_DATA_ME_PDN_ACT,
        RFX_MSG_EVENT_DATA_DEACT,
        RFX_MSG_EVENT_DATA_NW_ACT,
        RFX_MSG_EVENT_DATA_MODIFY,
        RFX_MSG_EVENT_KEEPALIVE_STATUS,
        RFX_MSG_EVENT_MOBILE_DATA_USAGE_NOTIFY,
        RFX_MSG_EVENT_DATA_LINK_CAPACITY_ESTIMATE,
        RFX_MSG_EVENT_NETWORK_REJECT_CAUSE,
        RFX_MSG_EVENT_DSDA_STATE_CHANGED,
        RFX_MSG_EVENT_DATA_PDN_CHANGE,
        RFX_MSG_EVENT_SEND_QUALIFIED_NETWORK_TYPES_CHANGED,
        RFX_MSG_EVENT_QUALIFIED_NETWORK_TYPES_CHANGED,
        RFX_MSG_EVENT_DATA_NW_LIMIT_NOTIFY,
        RFX_MSG_EVENT_RADIO_CAPABILITY_UPDATED,
        RFX_MSG_EVENT_QUERY_PCO_WITH_URC,
        RFX_MSG_EVENT_QUERY_PCO_WITH_AID,
        RFX_MSG_EVENT_REQ_DATA_CONTEXT_IDS,
        RFX_MSG_EVENT_KERNEL_ADDRESS_UPDATED,
        RFX_MSG_EVENT_URSP_REEVALUATE,
        RFX_MSG_EVENT_UNSOLICITED_RESPONSE_FILTER_CHANGED,
    };
    registerToHandleEvent(eventList, sizeof(eventList) / sizeof(int));
    // For bootup, event sent is before event registered.
    onRadioCapabilityUpdated();
    // For rild reboot, set prefer data to modem.
    resendPreferData();

    // set Android OS ID for URSP registration
    // MUST set before modem radio on.
    setOsId();
}

RmmDcEventHandler::~RmmDcEventHandler() {
}

void RmmDcEventHandler::onHandleEvent(const sp<RfxMclMessage>& msg) {
    switch (msg->getId()) {
        case RFX_MSG_EVENT_DATA_ME_PDN_ACT:
            onMePdnAct(msg);
            break;
        case RFX_MSG_EVENT_DATA_DEACT:
            onDataDeact(msg);
            break;
        case RFX_MSG_EVENT_DATA_NW_ACT:
            onNwAct(msg);
            break;
        case RFX_MSG_EVENT_DATA_MODIFY:
            onDataModify(msg);
            break;
        case RFX_MSG_EVENT_KEEPALIVE_STATUS:
            updateKeepaliveStatus(msg);
            break;
        case RFX_MSG_EVENT_MOBILE_DATA_USAGE_NOTIFY:
            handleMobileDataUsageNotify(msg);
            break;
        case RFX_MSG_EVENT_DATA_LINK_CAPACITY_ESTIMATE:
            handleLinkCapacityEstimate(msg);
            break;
        case RFX_MSG_EVENT_NETWORK_REJECT_CAUSE:
            handleNetworkRejectCause(msg);
            break;
        case RFX_MSG_EVENT_DSDA_STATE_CHANGED:
            handleDsdaStateChanged(msg);
            break;
        case RFX_MSG_EVENT_DATA_PDN_CHANGE:
            onPdnChange(msg);
            break;
        case RFX_MSG_EVENT_SEND_QUALIFIED_NETWORK_TYPES_CHANGED:
            requestSendQualifiedNetworkTypesChanged(msg);
            break;
        case RFX_MSG_EVENT_QUALIFIED_NETWORK_TYPES_CHANGED:
            onQualifiedNetworkTypeChanged(msg);
            break;
        case RFX_MSG_EVENT_DATA_NW_LIMIT_NOTIFY:
            onNwLimitNotify(msg);
            break;
        case RFX_MSG_EVENT_RADIO_CAPABILITY_UPDATED:
            onRadioCapabilityUpdated();
            break;
        case RFX_MSG_EVENT_QUERY_PCO_WITH_URC:
            handleQueryPcoAfterAttach(msg);
            break;
        case RFX_MSG_EVENT_QUERY_PCO_WITH_AID:
            handlePcoInfo(msg);
            break;
        case RFX_MSG_EVENT_REQ_DATA_CONTEXT_IDS:
            requestGetDataContextIds(msg);
            break;
        case RFX_MSG_EVENT_KERNEL_ADDRESS_UPDATED:
            onKernelAddressUpdated(msg);
            break;
        case RFX_MSG_EVENT_URSP_REEVALUATE:
            handleUrspReevaluate(msg);
            break;
        case RFX_MSG_EVENT_UNSOLICITED_RESPONSE_FILTER_CHANGED:
            handleResponseFilterChanged(msg);
            break;
        default:
            RFX_LOG_E(RFX_LOG_TAG, "should not be here");
            break;
    }
}

void RmmDcEventHandler::onHandleResponse(const sp<RfxMclMessage>& msg) {
    switch (msg->getId()) {
        case RFX_MSG_EVENT_QUERY_PCO_WITH_URC:
            handleQueryPcoAfterAttachResponse(msg);
            break;
        default:
            RFX_LOG_D(RFX_LOG_TAG, "ignore response: %d", msg->getId());
            break;
    }
}

int RmmDcEventHandler::getModemSuggestedRetryTime(const char *apnName) {
    // <mode>:indicate it's query mode or reset mode. 0:query mode, 1:reset mode
    // <APN name>: APN (string type) which is use to query or reset bar timer and retry count.
    mipc_data_retry_type_const_enum suggestType = MIPC_DATA_RETRY_TYPE_RETRY_TYPE_NO_SUGGEST;
    int suggestTime = -1;
    sp<RfxMipcData> mipcReq = RfxMipcData::obtainMipcData(MIPC_DATA_RETRY_TIMER_REQ, m_slot_id);
    mipcReq->addMipcTlvUint8(MIPC_DATA_RETRY_TIMER_REQ_T_MODE, MIPC_DATA_RETRY_MODE_QUERY_TIMER);
    mipcReq->addMipcTlvStr(MIPC_DATA_RETRY_TIMER_REQ_T_APN_NAME, apnName);
    sp<RfxMipcData> mipcCnf = callToMipcMsgSync(mipcReq);
    if (mipcCnf->getResult() != MIPC_RESULT_SUCCESS) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] MIPC_DATA_ACT_CALL_REQ return error",
                m_slot_id, __FUNCTION__);
        return suggestTime;
    }

    suggestType = (mipc_data_retry_type_const_enum) mipcCnf->getMipcInt8Val(
            MIPC_DATA_RETRY_TIMER_CNF_T_RETRY_TYPE, MIPC_DATA_RETRY_TYPE_RETRY_TYPE_NO_SUGGEST);
    if (suggestType == MIPC_DATA_RETRY_TYPE_RETRY_TYPE_NO_SUGGEST) {
        RFX_LOG_I(RFX_LOG_TAG, "[%d][%s] no suggest", m_slot_id, __FUNCTION__);
        suggestTime = -1;
    } else if (suggestType == MIPC_DATA_RETRY_TYPE_RETRY_TYPE_NO_RETRY) {
        RFX_LOG_I(RFX_LOG_TAG, "[%d][%s] no retry", m_slot_id, __FUNCTION__);
        suggestTime = 0x7fffffff;
    } else if (suggestType == MIPC_DATA_RETRY_TYPE_RETRY_TYPE_WITH_SUGGEST) {
        suggestTime = mipcCnf->getMipcInt32Val(MIPC_DATA_RETRY_TIMER_CNF_T_RETRY_TIME, -1);
        RFX_LOG_I(RFX_LOG_TAG, "[%d][%s] suggest=%d", m_slot_id, __FUNCTION__, suggestTime);
        suggestTime = suggestTime * 1000;
    }

    return suggestTime;
}

void RmmDcEventHandler::requestSetupDataCall(const sp<RfxMclMessage>& msg) {
    RIL_SetupDataCallRequest *pReq = (RIL_SetupDataCallRequest*)msg->getData()->getData();
    const int nPdnInfoSize = m_pPdnManager->getPdnTableSize();
    int activatedAid = INVALID_AID;
    int rid = m_slot_id;
    int transIntfId = INVALID_TRANS_INTF_ID;
    Vector<int> vAidList;
    Vector<int>::iterator it;
    MTK_RIL_Data_Call_Response_v11* response = NULL;
    sp<RfxMclMessage> responseMsg;
    int num = 1;
    const char *pReqApn = pReq->dataProfileInfo.apn == NULL ? "" : pReq->dataProfileInfo.apn;
    // get reason
    int reason = ACT_REASON_AOSP_NORMAL;
    if (pReq->reason == 0) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] pReqData[15] = NULL, suggest to check why ril version"
                " is lower than V1.2", rid, __FUNCTION__);
    } else {
        reason = pReq->reason;
    }
    // profile
    int profileId = pReq->dataProfileInfo.profileId;
    const char *pProfileType = RmmDcUtility::getProfileType(profileId);
    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] profileId=%d, reason=%d",
            rid, __FUNCTION__, profileId, reason);

    /*                  DNN             OsAppId     ProfileId
       -------------------------------------------------------------------
       ENTERPRISE       exist or not    exist       default or unknow
       LATENCY          not exist       exist       unknow
       BANDWIDTH        not exist       exist       unknow
       -------------------------------------------------------------------

       In order to find out correct APN for ENTERPRISE request,
       we need change profile from "default" to "enterprise", then change back.
     */
    if (profileId == RIL_DATA_PROFILE_DEFAULT
            && pReq->TD.dnn != NULL && strlen(pReq->TD.dnn) > 0 && pReq->tdValid > 0
            && (pReq->TD.osAppIdLen > OS_ID_UUID_LEN + 1) && pReq->TD.osAppId != NULL
            && strncmp(DC_ENTERPRISE, (char *)&pReq->TD.osAppId[APP_ID_INDEX],
                    strlen(DC_ENTERPRISE)) == 0) {
        RFX_LOG_I(RFX_LOG_TAG,
                "[%d][%s] Enterprise request with valid DNN, change profile to enterprise temporarily",
                rid, __FUNCTION__);
        profileId = RIL_DATA_PROFILE_VENDOR_ENTERPRISE;
    }

    // get cmdIndex
    int apnIndex = -1;
    ApnTableReq apnTableReq;
    uint32_t cmdIndex = 0;
    apnTableReq.apn = const_cast<char *>(pReqApn);
    apnTableReq.username = pReq->dataProfileInfo.user;
    apnTableReq.password = pReq->dataProfileInfo.password;
    apnTableReq.apnTypeId = RmmDcUtility::getApnTypeId(profileId);
    apnTableReq.protocol = pReq->dataProfileInfo.protocol;
    apnTableReq.authtype = pReq->dataProfileInfo.authType;
    apnIndex = RmmDcEventHandler::getIndexFromApnTable(rid, &apnTableReq);
    if (profileId == RIL_DATA_PROFILE_VENDOR_ENTERPRISE) {
        // For ENTERPRISE, change profile back to default.
        profileId = RIL_DATA_PROFILE_DEFAULT;
        apnTableReq.apnTypeId = RmmDcUtility::getApnTypeId(profileId);

        // Search again if necessary
        if (apnIndex < 0) {
            apnIndex = RmmDcEventHandler::getIndexFromApnTable(rid, &apnTableReq);
        }
    }
    if (apnIndex >= 0 && apnIndex < s_nLastReqNum[m_slot_id]) {
        cmdIndex = (uint32_t) s_ApnCmdIndex[m_slot_id][apnIndex];
    } else {
        // For slice request, APN might be invalid. But should not happen for non-slice request
        RFX_LOG_I(RFX_LOG_TAG,
                "[%d][%s] No APN found from table!! apnIndex=%d, apnCount=%d",
                rid, __FUNCTION__, apnIndex, s_nLastReqNum[m_slot_id]);
    }

    char *apn = const_cast<char *>(pReqApn);
    char *urspApn = NULL;
    char *username = pReq->dataProfileInfo.user;
    char *password = pReq->dataProfileInfo.password;
    uint32_t mipcApnType = (uint32_t) RmmDcUtility::getMipcApnTypeId(profileId);
    if (mipcApnType == MIPC_APN_TYPE_UNKNOWN && pReq->tdValid > 0
            && (pReq->TD.osAppIdLen > OS_ID_UUID_LEN + 1) && pReq->TD.osAppId != NULL) {
        if (strncmp(DC_CBS, (char *)&pReq->TD.osAppId[APP_ID_INDEX], strlen(DC_CBS)) == 0) {
            // CBS without valid APN
            RFX_LOG_I(RFX_LOG_TAG,
                    "[%d][%s] CBS without valid APN",
                    rid, __FUNCTION__);
            mipcApnType = MIPC_APN_TYPE_CBS;
        } else {
            // For non-CBS slice request, modem does not have those APN type,
            // we have to set APN type as default
            RFX_LOG_I(RFX_LOG_TAG,
                    "[%d][%s] Profile is unknow, OsAppId is valid, set profile to default",
                    rid, __FUNCTION__);
            mipcApnType = MIPC_APN_TYPE_DEFAULT;
        }
    }
    uint8_t mipcProtocolType = (uint8_t) RmmDcUtility::getMipcProtocolType(
            pReq->dataProfileInfo.protocol);
    uint8_t mipcRoamingProtocolType = (uint8_t) RmmDcUtility::getMipcProtocolType(
            pReq->dataProfileInfo.roamingProtocol);
    uint8_t mipcAuthType = (uint8_t) pReq->dataProfileInfo.authType;
    uint8_t mipcIpv4v6Fallback = (uint8_t) MIPC_DATA_FALLBACK_TYPE_MAX;
    uint32_t mipcBearerBitmask = RADIO_TECH_UNKNOWN;
    uint8_t mipcReuseFlag = (uint8_t) MIPC_DATA_REUSE_TYPE_DEFAULT;

    sp<RfxMipcData> mipcCmd = RfxMipcData::obtainMipcData(MIPC_DATA_ACT_CALL_REQ, msg->getSlotId());
    sp<RfxMipcData> mipcRet = NULL;
    mipc_result_const_enum ret = mipc_result_const_NONE;

    RFX_LOG_I(RFX_LOG_TAG, "[%d][%s] apn=%s, apnIndex=%d, profile=%s, protocol=%s",
            rid, __FUNCTION__, pReqApn, apnIndex, pProfileType, pReq->dataProfileInfo.protocol);

    // Initialize data call response.
    response = (MTK_RIL_Data_Call_Response_v11*)calloc(1, sizeof(MTK_RIL_Data_Call_Response_v11));
    RFX_ASSERT(response != NULL);
    initDataCallResponse(response, num);

    if (!isDataAllowed(pReqApn)) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] isDataAllowed() return false!",
                rid, __FUNCTION__);
        response->status = m_nGprsFailureCause = PDP_FAIL_DATA_NOT_ALLOW;
        goto error;
    }

    if (isHandoverRequest(reason, profileId, &transIntfId)) {
        createDataResponse(transIntfId, IPV4V6, response);
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] %s", rid, __FUNCTION__,
                responsesToString(response, num).string());
        goto finish;
    }

    // Reserve size of AID list.
    vAidList.reserve(nPdnInfoSize);

    /*Fix timing issue of IMS/EIMS PDN*/
    //IMS/EIMS PDN was already deactivated in MD,
    //while setup data call for IMS/EIMS PDN is still ongoing in AP fwk/ril.
    //Refer to ALPS04066280 and ALPS03861864 for detail scenario.
    if ((strncmp(pProfileType, "ims", 3) == 0) &&
        (getMclStatusManager(rid)->getIntValue(RFX_STATUS_KEY_IMS_PDN_STATE) == IMS_OR_EIMS_PDN_DEACTIVATED)) {
        RFX_LOG_I(RFX_LOG_TAG, "[%d] %s pdn is already deactivated at MD, shouldn't be activated", rid, pProfileType);
        goto error;
    } else if ((strncmp(pProfileType, "emergency", 9) == 0) &&
        (getMclStatusManager(rid)->getIntValue(RFX_STATUS_KEY_EIMS_PDN_STATE) == IMS_OR_EIMS_PDN_DEACTIVATED)) {
        RFX_LOG_I(RFX_LOG_TAG, "[%d] %s pdn is already deactivated at MD, shouldn't be activated", rid, pProfileType);
        goto error;
    }
    /*Fix timing issue of IMS/EIMS PDN*/

    // URSP support for all PDN type
    if (pReq->tdValid > 0) {
        mipc_ursp_traffic_desc_struct_struct4 td;
        memset(&td, 0, sizeof(mipc_ursp_traffic_desc_struct_struct4));
        // For prot_id_next_hdr, 0 is a valid value, so set to 0xFF
        td.prot_id_next_hdr = (uint8_t)0xFF;
        // dnn
        if (pReq->TD.dnn != NULL && strlen(pReq->TD.dnn) > 0) {
            td.dnn_len = strlen(pReq->TD.dnn);
            strncpy(td.dnn, pReq->TD.dnn, MIPC_MAX_APN_LEN - 1);
        }
        // osAppId
        // 16 bytes for UUID, 1 byte for length of osAppId, and up to 255 bytes for osAppId
        if (pReq->TD.osAppIdLen > 0 && pReq->TD.osAppId != NULL) {
            if (pReq->TD.osAppIdLen > OS_ID_UUID_LEN + 1) {
                // copy OS ID
                memcpy(td.os_id, pReq->TD.osAppId, OS_ID_UUID_LEN);
                td.app_id_len = pReq->TD.osAppIdLen - OS_ID_UUID_LEN - 1;
                // copy APP ID
                memcpy(td.app_id, &pReq->TD.osAppId[APP_ID_INDEX], td.app_id_len);
                // Use apn\1Fapp_id (Use ASCII 0x1F as separator) as URSP apn context
                // 1. Modem will insert apn for URSP even AP didn't sync this APN before.
                // 2. AP/MD will use this APN to communicate when pdn not setup successfully
                // (cid is not available), like retry timer query
                char *appId = (char *)calloc(td.app_id_len + 1, sizeof(char));
                RFX_ASSERT(appId != NULL);
                strncpy(appId, (char *)td.app_id, td.app_id_len);
                char separator = (char) 31; // \1F
                if (strcmp(appId, DC_CBS) == 0) {
                    // Android T support CBS slice type and it is also valid APN for 2/3/4G
                    // Here we should still support CBS on 4G based on it will not share
                    // APN setting with other slice type.
                    asprintf(&urspApn, "%s", pReqApn);
                } else {
                    asprintf(&urspApn, "%s%c%s", pReqApn, separator, appId);
                }
                // apn will be used in query retry timer
                apn = urspApn;
                RFX_LOG_D(RFX_LOG_TAG,
                        "[%d][%s] OS APP ID: %02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x-%d-%s, urspApn:%s",
                        rid, __FUNCTION__,
                        td.os_id[0], td.os_id[1], td.os_id[2], td.os_id[3],
                        td.os_id[4], td.os_id[5], td.os_id[6], td.os_id[7],
                        td.os_id[8], td.os_id[9], td.os_id[10], td.os_id[11],
                        td.os_id[12], td.os_id[13], td.os_id[14], td.os_id[15],
                        pReq->TD.osAppId[APP_ID_LEN_INDEX],
                        (char*)(&pReq->TD.osAppId[APP_ID_INDEX]), urspApn);
                FREEIF(appId);
            } else {
                RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] Invalid OS APP ID", rid, __FUNCTION__);
                // According to TS 24.526 Section 5.2 and OsAppId defination in types.hal
                // The minimum length of the array is 18 and maximum length is 272
                // (16 bytes for OsId + 1 byte for OsAppId length up to 255 bytes for OsAppId)
                goto error;
            }
        }
        mipc_data_act_call_req_add_ursp_traffic_desc(mipcCmd->getData(),
                sizeof(mipc_ursp_traffic_desc_struct_struct4), &td);
        RFX_LOG_I(RFX_LOG_TAG, "[%d][%s] dnn_len:%d, app_id_len:%d, matchAllRuleAllowed:%d", rid,
                __FUNCTION__, td.dnn_len, pReq->TD.osAppIdLen, pReq->matchAllRuleAllowed);
    }
    mipcCmd->addMipcTlvUint32(MIPC_DATA_ACT_CALL_REQ_T_URSP_EVAL_FLAG, pReq->matchAllRuleAllowed);

    mipcBearerBitmask =
            (uint32_t) ((apnIndex >= 0 && apnIndex < s_nLastReqNum[m_slot_id]) ?
            s_LastApnTable[m_slot_id][apnIndex].bearerBitmask :
            (urspApn == NULL ? 0 : ALL_BEARER_BITMASK));

    if (mipcApnType == MIPC_APN_TYPE_IMS || mipcApnType == MIPC_APN_TYPE_EMERGENCY) {
        mipcReuseFlag = (uint8_t) MIPC_DATA_REUSE_TYPE_REUSE_ONLY;
        mipcCmd->addMipcTlvUint32(MIPC_DATA_ACT_CALL_REQ_T_APN_TYPE, mipcApnType);
        mipcCmd->addMipcTlvUint8(MIPC_DATA_ACT_CALL_REQ_T_REUSE_FLAG, mipcReuseFlag);
    } else {
        if (apnIndex >= 0 && apnIndex < s_nLastReqNum[m_slot_id]) {
            mipcCmd->addMipcTlvStr(MIPC_DATA_ACT_CALL_REQ_T_APN, pReqApn);
            mipcCmd->addMipcTlvUint32(MIPC_DATA_ACT_CALL_REQ_T_APN_INDEX, cmdIndex);
        } else if (urspApn != NULL) {
            mipcCmd->addMipcTlvStr(MIPC_DATA_ACT_CALL_REQ_T_APN, urspApn);
        } else {
            // should not be here
            RFX_LOG_W(RFX_LOG_TAG, "[%d][%s] Unknown case.", rid, __FUNCTION__);
        }
        mipcCmd->addMipcTlvUint32(MIPC_DATA_ACT_CALL_REQ_T_APN_TYPE, mipcApnType);
        mipcCmd->addMipcTlvUint8(MIPC_DATA_ACT_CALL_REQ_T_PDP_TYPE, mipcProtocolType);
        mipcCmd->addMipcTlvUint8(MIPC_DATA_ACT_CALL_REQ_T_ROAMING_TYPE, mipcRoamingProtocolType);
        mipcCmd->addMipcTlvUint8(MIPC_DATA_ACT_CALL_REQ_T_AUTH_TYPE, mipcAuthType);
        mipcCmd->addMipcTlvStr(MIPC_DATA_ACT_CALL_REQ_T_USERID, username);
        mipcCmd->addMipcTlvStr(MIPC_DATA_ACT_CALL_REQ_T_PASSWORD, password);
        mipcCmd->addMipcTlvUint8(MIPC_DATA_ACT_CALL_REQ_T_IPV4V6_FALLBACK, mipcIpv4v6Fallback);
        mipcCmd->addMipcTlvUint32(MIPC_DATA_ACT_CALL_REQ_T_BEARER_BITMASK, mipcBearerBitmask);
        mipcCmd->addMipcTlvUint8(MIPC_DATA_ACT_CALL_REQ_T_REUSE_FLAG, mipcReuseFlag);
    }

    mipcRet = callToMipcMsgSync(mipcCmd);
    ret = (mipc_result_const_enum) mipcRet->getResult();

    if (ret == MIPC_RESULT_SUCCESS
            || ret == MIPC_RESULT_PDN_EXT_LOCAL_FALLBACK_RES_SUCC_ABORT
            || ret == MIPC_RESULT_PDN_EXT_LOCAL_FALLBACK_RES_SUCC_CONT) {
        activatedAid = decodeDataCallProfile(mipcRet, ACT_CNF);
        vAidList.push_back(activatedAid);
        m_pPdnManager->updatePdnActiveStatus(activatedAid, DATA_STATE_ACTIVE);
        m_pPdnManager->setIsDedicateBearer(activatedAid, 0);
        m_pPdnManager->setProfileId(activatedAid, profileId);
        m_pPdnManager->updateApnName(activatedAid, pReqApn);
        m_pPdnManager->setAccessNetwork(activatedAid,
            RmmDcUtility::radioTechToAccessNw((RIL_RadioTechnology)getCurrentRat()));
        updateQosInformation(activatedAid);
        updateTdInfo(activatedAid);
    } else {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] MIPC_DATA_ACT_CALL_REQ return error, ret=%d",
                rid, __FUNCTION__, ret);
        updateLastFailCause((int) ret);
        if (ret == MIPC_RESULT_PDN_EXT_LOCAL_FALLBACK_RES_FAIL_CONT) {
            activatedAid = decodeDataCallProfile(mipcRet, ACT_CNF);
            if (activatedAid != INVALID_AID) {
                // wait for fallback (act ind)
                RFX_LOG_W(RFX_LOG_TAG, "[%d][%s] FAIL_CONT, wait fallback",
                        rid, __FUNCTION__);
                m_pPdnManager->setIsDedicateBearer(activatedAid, 0);
                m_pPdnManager->setProfileId(activatedAid, profileId);
                m_pPdnManager->updateApnName(activatedAid, pReqApn);
                m_mapAidReqmsg[m_pPdnManager->getPrimaryAid(activatedAid)] = msg;
                freeDataResponse(response);
                FREEIF(response);
                return;
            }
        } else {
            // FAIL_ABORT and other errors
            goto error;
        }
    }

    if (activatedAid == INVALID_AID) {
        goto error;
    }

    updateIpv6PdnInfo(activatedAid);

    // check if need wait for NetAgent callback
    if (needWaitNetAgentNotification(activatedAid)) {
        // need wait for IPV6 update, NetAgent will invoke callback function
        // save reqMessage clear ReqMessage after IP change callback.
        RFX_LOG_I(RFX_LOG_TAG, "[%d][%s] wait for NetAgent notification", rid, __FUNCTION__);
        m_mapAidReqmsg[activatedAid] = msg;
        freeDataResponse(response);
        FREEIF(response);
        return;
    }

    createDataResponse(m_pPdnManager->getTransIntfId(activatedAid), IPV4V6, response);
    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] %s", rid, __FUNCTION__, responsesToString(response, num).string());

    sendEvent(RFX_MSG_EVENT_REQ_DATA_CONTEXT_IDS, RfxVoidData(),
            RIL_CMD_PROXY_5, m_slot_id, -1, -1, 100e6);
    setPdnInfoProperty();

    goto finish;

error:

    response->status = m_nGprsFailureCause;
    response->suggestedRetryTime = getModemSuggestedRetryTime(apn);
    if ((PDP_FAIL_MISSING_UKNOWN_APN == response->status ||
                PDP_FAIL_SERVICE_OPTION_NOT_SUBSCRIBED == response->status)
            && strcasecmp(pProfileType,"mms") == 0
            && response->suggestedRetryTime != -1) {
        char simMccMnc[MAX_LENGTH_MCCMNC] = {0};
        getMccmnc(simMccMnc);
        if (0 == strcmp(simMccMnc, "42003")) {
            // Mobily(42003) has two APNs for MMS based on type of SIM card,
            // prepaid(apn="mms2") , postpaid(apn="mms1).
            // AOSP won't check SIM type(prepaid or postpaid) when select APN.
            // If wrong APN was selected, NW will return #27 and valid back-off timer.
            // AOSP has no chance to use right APN due to the back-off timer.
            // To fix it, reset back-off timer to -1(no suggest).
            RFX_LOG_I(RFX_LOG_TAG,
                    "error #27 or #33 for special oprator when set up mms");
            response->suggestedRetryTime = -1;
        }
    }
    if (PDP_FAIL_REJECTED_BY_IWLAN == response->status
            && response->suggestedRetryTime == -1
            && strcasecmp(pProfileType,"default") == 0) {
        response->suggestedRetryTime = SUGGEST_TIME_FOR_PDP_FAIL_REJECTED_BY_IWLAN;
    }

    for (it = vAidList.begin(); it != vAidList.end(); it++) {
        int aid = *it;
        //deactivateDataCall(activatedAid); //no need for MIPC
        m_pPdnManager->clearPdnInfo(aid);
    }

finish:
    responseMsg = RfxMclMessage::obtainResponse(RIL_E_SUCCESS,
            RfxDataCallResponseData(response, num), msg);
    responseToTelCore(responseMsg);

    if (response != NULL) {
        if (profileId == RIL_DATA_PROFILE_VENDOR_MMS && response->status == PDP_FAIL_NONE
                && !vAidList.empty()) {
            int data[2];
            data[0] = RmmDcUtility::getApnTypeId(profileId);
            data[1] = m_pPdnManager->getRat(*(vAidList.begin()));
            sendEvent(RFX_MSG_EVENT_SEND_QUALIFIED_NETWORK_TYPES_CHANGED, RfxIntsData(data, 2),
                    RIL_CMD_PROXY_5, m_slot_id, -1, -1, 500e6);
        }
        freeDataResponse(response);
        FREEIF(response);
    }
    FREEIF(urspApn);
    RFX_LOG_V(RFX_LOG_TAG, "[%d][%s] finish", rid, __FUNCTION__);
}

void RmmDcEventHandler::updateIpv6PdnInfo(int aid) {
    int pdnType = m_pPdnManager->getPdnType(aid);
    int interfaceId = m_pPdnManager->getInterfaceId(aid);
    if (pdnType == MIPC_APN_PDP_TYPE_IPV6 ||pdnType == MIPC_APN_PDP_TYPE_IPV4V6) {
        NetAgentService *pNetAgentService = NetAgentService::getInstance();
        if (NULL == pNetAgentService) {
            RFX_LOG_E(RFX_LOG_TAG, "[%d] NetAgentService is NULL, return error", m_slot_id);
        } else {
            InterfaceInfo *pInterfaceInfo = pNetAgentService->queryInterfaceInfo(interfaceId);
            if (pInterfaceInfo == NULL) {
                RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] error get interfaceInfo interfaceId=%d",
                        m_slot_id, __FUNCTION__, interfaceId);
                return;
            }
            int length = pInterfaceInfo->globalIpv6Count;
            RFX_LOG_V(RFX_LOG_TAG, "[%d][%s] length=%d, interfaceId=%d", m_slot_id, __FUNCTION__,
                      length, interfaceId);
            for (int i = 0; i < length && i < MAX_NUM_IPV6_ADDRESS_NUMBER; i++) {
                RFX_LOG_V(RFX_LOG_TAG, "[%d][%s] update pdn ipv6", m_slot_id, __FUNCTION__);
                m_pPdnManager->updateIpv6Info(aid, i, pInterfaceInfo->ipv6Info[i]);
            }
            if (pInterfaceInfo->mtuV6 > 0) {
                m_pPdnManager->updateMtuV6(aid, pInterfaceInfo->mtuV6);
            }
        }
    }
}

bool RmmDcEventHandler::needWaitNetAgentNotification(int aid) {
    if (aid < 0 || aid >= m_pPdnManager->getPdnTableSize()) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] illegal param", m_slot_id, __FUNCTION__);
        return false;
    }
    // check if need wait for NetAgent callback
    char* ipV4addr = m_pPdnManager->getIpv4Address(aid);
    char* ipV6addr = m_pPdnManager->getIpv6Address(aid, 0);
    int pdnType = m_pPdnManager->getPdnType(aid);
    RFX_LOG_V(RFX_LOG_TAG, "[%d][%s] pdnType(1-V4,2-V6,3-V4V6)=%d, v4addr=%s, v6addr=%s",
            m_slot_id, __FUNCTION__, pdnType,
            ipV4addr==NULL?"":ipV4addr, ipV6addr==NULL?"":ipV6addr);
    if (m_pPdnManager->getPdnActiveStatus(aid) == DATA_STATE_ACTIVE
            && ((pdnType == MIPC_APN_PDP_TYPE_IPV6 && !isIpv6Global(ipV6addr))
            ||(pdnType == MIPC_APN_PDP_TYPE_IPV4V6 && !isIpv6Global(ipV6addr)
                    && strlen(ipV4addr) == 0))) {
        return true;
    }
    return false;
}

int RmmDcEventHandler::decodeDataCallProfile(const sp<RfxMipcData> mipcData,
        const DCProfileSource src) {
    String8 cnf("");
    int i = 0;
    char tempV6[MAX_IPV6_ADDRESS_LENGTH] = {0};
    // aid
    int aid = (int) mipcData->getMipcUint8Val(DC_T_ID(src), INVALID_AID);
    if (aid != INVALID_AID) {
        m_pPdnManager->setAid(aid, aid);
    }
    cnf.append(String8::format("aid=%d,", aid));

    // apn name
    char* apn = mipcData->getMipcStr(DC_T_APN(src));
    if (apn != NULL) {
        m_pPdnManager->updateApnName(aid, apn);
    }
    cnf.append(String8::format("apn=%s,", apn));

    // PDP type, IPV4(1), IPV6(2), IPV4V6(3), IPV4andIPV6(4)
    int pdpType = (int) mipcData->getMipcUint8Val(DC_T_PDP_TYPE(src), INVALID_VALUE);
    if (pdpType != INVALID_VALUE) {
        m_pPdnManager->setPdnType(aid, pdpType);
    }
    cnf.append(String8::format("pdpType=%d,", pdpType));

    // IPV4 addresses
    // currently MIPC response and data call response contain only 1 IPv4 address.
    // so, just get the firt IPv4 address.
    int v4Count = (int) mipcData->getMipcUint8Val(DC_T_V4_COUNT(src), INVALID_VALUE);
    if (v4Count != INVALID_VALUE) {
        char addressV4[2/*v4Count*/][MAX_IPV4_ADDRESS_LENGTH] = {{0}};
        decodeMipcV4Address(mipcData, DC_T_V4_0(src), 1/*v4Count*/, addressV4);
        m_pPdnManager->updateIpv4Address(aid, addressV4[0]);
        cnf.append(String8::format("IPV4=%s,", addressV4[0]));
    }

    // Ignore IPV6 link local address, wait global address from NA

    // DNS V4
    int dnsV4Count = (int) mipcData->getMipcUint8Val(DC_T_DNS_V4_COUNT(src),
            INVALID_VALUE);
    if (dnsV4Count != INVALID_VALUE) {
        dnsV4Count =  dnsV4Count < MAX_NUM_DNS_ADDRESS_NUMBER ? dnsV4Count
                : MAX_NUM_DNS_ADDRESS_NUMBER;
        char dnsAddressV4[MAX_NUM_DNS_ADDRESS_NUMBER][MAX_IPV4_ADDRESS_LENGTH] = {{0}};
        decodeMipcV4Address(mipcData, DC_T_DNS_V4_0(src), dnsV4Count, dnsAddressV4);
        for (i = 0; i < dnsV4Count; i++) {
            m_pPdnManager->updateIpv4Dns(aid, i, dnsAddressV4[i]);
            cnf.append(String8::format("DNSV4_%d=%s,", i, dnsAddressV4[i]));
        }
    }

    // DNS V6
    int dnsV6Count = (int) mipcData->getMipcUint8Val(DC_T_DNS_V6_COUNT(src),
            INVALID_VALUE);
    if (dnsV6Count != INVALID_VALUE) {
        dnsV6Count =  dnsV6Count < MAX_NUM_DNS_ADDRESS_NUMBER ? dnsV6Count
                : MAX_NUM_DNS_ADDRESS_NUMBER;
        char dnsAddressV6[MAX_NUM_DNS_ADDRESS_NUMBER][MAX_IPV6_ADDRESS_LENGTH] = {{0}};
        decodeMipcV6Address(mipcData, DC_T_DNS_V6_0(src), dnsV6Count, dnsAddressV6);
        for (i = 0; i < dnsV6Count; i++) {
            memset(tempV6, 0, MAX_IPV6_ADDRESS_LENGTH);
            convertIpv6Address(tempV6, dnsAddressV6[i], 0);
            m_pPdnManager->updateIpv6Dns(aid, i, tempV6);
            cnf.append(String8::format("DNSV6_%d=%s,", i, tempV6));
        }
    }

    // pcscfV4
    int pcscfV4Count = (int) mipcData->getMipcUint8Val(DC_T_PCSCF_V4_COUNT(src), 0);
    if (pcscfV4Count > 0) {
        pcscfV4Count =  pcscfV4Count < MAX_PCSCF_NUMBER ? pcscfV4Count : MAX_PCSCF_NUMBER;
        char pcscfV4[MAX_PCSCF_NUMBER][MAX_IPV4_ADDRESS_LENGTH] = {{0}};
        decodeMipcV4Address(mipcData, DC_T_PCSCF_V4_0(src), pcscfV4Count, pcscfV4);
        for (i = 0; i < pcscfV4Count; i++) {
            m_pPdnManager->updatePcscfAddress(aid, i, pcscfV4[i]);
            cnf.append(String8::format("pcscfV4_%d=%s,", i, pcscfV4[i]));
        }
        cnf.append(String8::format("pcscfV4 count:%d,", pcscfV4Count));
    }

    // pcscfV6
    int pcscfV6Count = (int) mipcData->getMipcUint8Val(DC_T_PCSCF_V6_COUNT(src), 0);
    if (pcscfV6Count > 0) {
        pcscfV6Count =  pcscfV6Count < (MAX_PCSCF_NUMBER - pcscfV4Count)
                            ? pcscfV6Count : (MAX_PCSCF_NUMBER - pcscfV4Count);
        char pcscfV6[MAX_PCSCF_NUMBER][MAX_IPV6_ADDRESS_LENGTH] = {{0}};
        decodeMipcV6Address(mipcData, DC_T_PCSCF_V6_0(src), pcscfV6Count, pcscfV6);
        for (i = 0; i < pcscfV6Count; i++) {
            memset(tempV6, 0, MAX_IPV6_ADDRESS_LENGTH);
            convertIpv6Address(tempV6, pcscfV6[i], 0);
            m_pPdnManager->updatePcscfAddress(aid, pcscfV4Count + i, tempV6);
            cnf.append(String8::format("pcscfV6_%d=%s,", i, tempV6));
        }
        cnf.append(String8::format("pcscfV6 count:%d,", pcscfV6Count));
    }

    // MTU V4
    int mtuV4 = (int) mipcData->getMipcUint32Val(DC_T_MTU_V4(src), 0);
    if (mtuV4 >= 0) {
        m_pPdnManager->updateMtuV4(aid, mtuV4);
    }
    cnf.append(String8::format("mtuV4=%d,", mtuV4));

    // MTU V6
    int mtuV6 = (int) mipcData->getMipcUint32Val(DC_T_MTU_V6(src), 0);
    if (mtuV6 >= 0) {
        m_pPdnManager->updateMtuV6(aid, mtuV6);
    }
    cnf.append(String8::format("mtuV6=%d,", mtuV6));

    // interface ID
    int interfaceId = (int) mipcData->getMipcUint32Val(
            DC_T_INTERFACE_ID(src), INVALID_ID);
    if (interfaceId != INVALID_ID) {
        m_pPdnManager->setInterfaceId(aid, interfaceId);
    }
    cnf.append(String8::format("interfaceId=%d,", interfaceId));

    // primary ID
    if (src != GET_CNF) {
        int pId = (int) mipcData->getMipcUint8Val(DC_T_P_ID(src), INVALID_ID);
        if (pId != INVALID_ID) {
            m_pPdnManager->setPrimaryAid(aid, pId);
        }
        cnf.append(String8::format("primaryId=%d,", pId));
    }

    // fallback data call ID
    if (src == ACT_CNF || src == ACT_IND) {
        int fbId = (int) mipcData->getMipcUint8Val(DC_T_FB_ID(src),
                INVALID_ID);
        cnf.append(String8::format("fbId=%d,", fbId));
    }

    // IPV4 netmask

    // IPV6 netmask

    // transInterface ID
    int transIntfId = (int) mipcData->getMipcUint32Val(
            DC_T_TRANS_ID(src), INVALID_ID);
    if (transIntfId != INVALID_ID) {
        m_pPdnManager->updateTransIntfId(aid, transIntfId);
    }
    cnf.append(String8::format(" transIntfId=%d,", transIntfId));

    // RAN Info, wifi, cellular or unknown, reference @mipc_ran_const_enum
    int ranInfo = (int) mipcData->getMipcUint8Val(DC_T_RAN_INFO(src), INVALID_VALUE);
    if (ranInfo != INVALID_VALUE) {
        if (ranInfo >= ACCESS_NW_TYPE_VODATA1 && ranInfo <= ACCESS_NW_TYPE_VODATA4) {
            // Value from 3~6 will be view as IWLAN, which is related
            // to VoData feature
            RFX_LOG_I(RFX_LOG_TAG, "[%d][%s] rat=%d change to IWLAN(2)",
                    m_slot_id, __FUNCTION__, ranInfo);
            ranInfo = ACCESS_NW_TYPE_IWLAN;
        }
        m_pPdnManager->updateRat(aid, ranInfo);
    }
    cnf.append(String8::format(" ranInfo=%d,", ranInfo));

    // bearer ID
    int bearerId = (int) mipcData->getMipcUint32Val(
            DC_T_BEARER_ID(src), INVALID_ID);
    if (bearerId != INVALID_ID) {
        m_pPdnManager->updateBearerId(aid, bearerId);
    }
    cnf.append(String8::format(" bearerId=%d,", bearerId));

    // signalling flag ID
    int signalingFlag = (int) mipcData->getMipcUint8Val(
            DC_T_IM_CN_SIGNALLING_FLAG(src), INVALID_ID);
    if (signalingFlag != INVALID_ID) {
        m_pPdnManager->setSignalingFlag(aid, signalingFlag);
    }
    cnf.append(String8::format(" signalingFlag=%d,", signalingFlag));

    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] cnf data:%s", m_slot_id, __FUNCTION__, cnf.string());

    return aid;
}

void RmmDcEventHandler::decodeMipcV4Address(const sp<RfxMipcData> mipcData, int type,
        int addrCount, char addr[][MAX_IPV4_ADDRESS_LENGTH]) {
    /* change uint8_t array to "xx.xx.x.xxx" */
    int n = 0;
    for (int i = 0; i < addrCount; i++){
        if (mipc_msg_get_val_ptr(mipcData->getData(), type+i, NULL) == NULL) {
            break;
        }
        mipc_data_v4_addr_struct4 *mipcAddr
                = (mipc_data_v4_addr_struct4*) mipc_msg_get_val_ptr(mipcData->getData(),
                type+i, NULL);
        memset(addr[i], 0, sizeof(addr[i]));
        n = snprintf(addr[i], MAX_IPV4_ADDRESS_LENGTH, "%d.%d.%d.%d",
                mipcAddr->addr[0], mipcAddr->addr[1], mipcAddr->addr[2], mipcAddr->addr[3]);
        if (n < 0) {
            RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] print IPV4 add fail.", m_slot_id, __FUNCTION__);
            continue;
        }
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] %d.%d.%d.%d",
                m_slot_id, __FUNCTION__,
                mipcAddr->addr[0], mipcAddr->addr[1], mipcAddr->addr[2], mipcAddr->addr[3]);
    }
}

void RmmDcEventHandler::decodeMipcV6Address(const sp<RfxMipcData> mipcData, int type,
        int addrCount, char addr[][MAX_IPV6_ADDRESS_LENGTH]) {
    /* change uint8_t array to "xx.xx.x.xxx.x.x.xx.x.xx.x.x.x.x.xxx.xx.xx" */
    int n = 0;
    for (int i = 0; i < addrCount; i++){
        if (mipc_msg_get_val_ptr(mipcData->getData(), type+i, NULL) == NULL) {
            break;
        }
        mipc_data_v6_addr_struct4 *mipcAddr
                = (mipc_data_v6_addr_struct4*) mipc_msg_get_val_ptr(mipcData->getData(),
                  type+i, NULL);
        memset(addr[i], 0, sizeof(addr[i]));
        n = snprintf(addr[i], MAX_IPV6_ADDRESS_LENGTH,
                "%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d",
                mipcAddr->addr[0], mipcAddr->addr[1], mipcAddr->addr[2], mipcAddr->addr[3],
                mipcAddr->addr[4], mipcAddr->addr[5], mipcAddr->addr[6], mipcAddr->addr[7],
                mipcAddr->addr[8], mipcAddr->addr[9], mipcAddr->addr[10], mipcAddr->addr[11],
                mipcAddr->addr[12], mipcAddr->addr[13], mipcAddr->addr[14], mipcAddr->addr[15]);
        if (n < 0) {
            RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] print IPV6 add fail.", m_slot_id, __FUNCTION__);
            continue;
        }
        RFX_LOG_D(RFX_LOG_TAG,
                "[%d][%s] %d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d",
                m_slot_id, __FUNCTION__,
                mipcAddr->addr[0], mipcAddr->addr[1], mipcAddr->addr[2], mipcAddr->addr[3],
                mipcAddr->addr[4], mipcAddr->addr[5], mipcAddr->addr[6], mipcAddr->addr[7],
                mipcAddr->addr[8], mipcAddr->addr[9], mipcAddr->addr[10], mipcAddr->addr[11],
                mipcAddr->addr[12], mipcAddr->addr[13], mipcAddr->addr[14], mipcAddr->addr[15]);
    }
}

// Dedicate bearer PDN activated
void RmmDcEventHandler::onNwAct(const sp<RfxMclMessage>& msg) {
    int *pEventData = (int *)msg->getData()->getData();
    int result = pEventData[0];
    int aid = pEventData[1];
    int p_id = pEventData[2];
    int fb_id = pEventData[3];

    RFX_LOG_I(RFX_LOG_TAG, "[%d][%s] result:%d, aid:%d, p_id:%d, fb_id:%d",
            m_slot_id, __FUNCTION__, result, aid, p_id, fb_id);
    if (!m_pPdnManager->validateAid(aid)
            || m_pPdnManager->getPdnActiveStatus(p_id) != DATA_STATE_ACTIVE) {
        RFX_LOG_W(RFX_LOG_TAG, "[%d][%s] invalid aid or p_id not active",
            m_slot_id, __FUNCTION__);
        return;
    }
    confirmPdnUsage(aid, true);

    m_pPdnManager->setAidAndPrimaryAid(aid, aid ,p_id);
    m_pPdnManager->setIsDedicateBearer(aid, true);
    m_pPdnManager->updatePdnActiveStatus(aid, DATA_STATE_ACTIVE);
    m_pPdnManager->updateTransIntfId(aid, m_pPdnManager->getTransIntfId(p_id));
    m_pPdnManager->setAccessNetwork(aid,
            RmmDcUtility::radioTechToAccessNw((RIL_RadioTechnology)getCurrentRat()));

    updateQosInformation(aid, true);
    requestOrSendDataCallList(msg, p_id);
}

// Default Bearer PDN activated
void RmmDcEventHandler::onMePdnAct(const sp<RfxMclMessage>& msg) {
    int *pEventData = (int *)msg->getData()->getData();
    int result = pEventData[0];
    int aid = pEventData[1];
    int p_id = pEventData[2];
    int fb_id = pEventData[3];
    int rid = m_slot_id;
    int sscMode = SSC_UNKNOWN;
    int olderAid = INVALID_AID;
    int newerAid = INVALID_AID;
    bool isFb = (fb_id != INVALID_AID ? true: false);
    // Currently, only fallback and SSC mode3
    if (isFb) {
        olderAid = p_id;
        newerAid = aid;
    } else {
        // TODO: how to distinguish SSC mode3 and reassign
        // olderAid/newerAid correspondingly
        sscMode = SSC_MODE3;
    }

    if (newerAid == INVALID_AID) {
        return;
    }

    RFX_LOG_I(RFX_LOG_TAG, "[%d][%s] aid:%d,p_id:%d, fb_id:%d, result:%d",
            rid, __FUNCTION__, aid, p_id, fb_id, result);

    m_pPdnManager->setAccessNetwork(newerAid,
            RmmDcUtility::radioTechToAccessNw((RIL_RadioTechnology)getCurrentRat()));

    // get data call profile for both success and fail case
    if (result == MIPC_RESULT_SUCCESS) {
        confirmPdnUsage(newerAid, true);
        sp<RfxMipcData> mipcReq = RfxMipcData::obtainMipcData(
                MIPC_DATA_GET_CALL_REQ, m_slot_id);
        mipcReq->addMipcTlvUint8(MIPC_DATA_GET_CALL_REQ_T_ID, (uint8_t)aid);
        sp<RfxMipcData> mipcCnf = callToMipcMsgSync(mipcReq);
        if ((mipc_result_const_enum) mipcCnf->getResult() != MIPC_RESULT_SUCCESS) {
            RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] MIPC_DATA_GET_CALL_REQ return error",
                    rid, __FUNCTION__);
            if (isFb && m_mapAidReqmsg[olderAid] != NULL) {
                createAndLaunchDataResponse(MIPC_RESULT_FAILURE, olderAid);
                m_pPdnManager->clearPdnInfo(olderAid);
                m_pPdnManager->clearPdnInfo(newerAid);
            }
            return;
        }
        decodeDataCallProfile(mipcCnf, GET_CNF);
        updateQosInformation(aid);
        updateTdInfo(aid);
    } else {
        confirmPdnUsage(newerAid, false);
    }
    if (p_id != INVALID_AID) {
        m_pPdnManager->setPrimaryAid(aid, p_id);
    }

    RFX_LOG_I(RFX_LOG_TAG, "[%d][%s] aid%d is activated and current state is %d",
            rid, __FUNCTION__, aid, m_pPdnManager->getPdnActiveStatus(aid));

    if (olderAid != INVALID_AID &&
            m_pPdnManager->getPdnActiveStatus(olderAid) == DATA_STATE_INACTIVE
            && m_pPdnManager->getPdnActiveStatus(newerAid) == DATA_STATE_ACTIVE) {
        // Update with link down state.
        m_pPdnManager->updatePdnActiveStatus(olderAid, DATA_STATE_LINKDOWN);
        m_pPdnManager->setAidAndPrimaryAid(olderAid, olderAid, olderAid);
    }

    // Procedure of different cases:
    // SSC mode3, FAIL_CONT, SUCC_CONT, normal ACT IND ...
    if (isFb && olderAid != INVALID_AID &&
            m_pPdnManager->getPdnActiveStatus(olderAid) != DATA_STATE_ACTIVE) {
        sp<RfxMclMessage> reqMsg = m_mapAidReqmsg[olderAid];
        if (reqMsg == NULL) {
            // Will tis happen?
            // 1st IND failed, 2nd IND success, and 1st already send response
            if (result == MIPC_RESULT_SUCCESS) {
                // check if need wait for NetAgent callback
                if (needWaitNetAgentNotification(newerAid)) {
                    // need wait for IPV6 update, NetAgent will invoke callback function
                    RFX_LOG_I(RFX_LOG_TAG,
                            "[%d][%s] SUCC_CONT, wait for NetAgent notification",
                            rid, __FUNCTION__);
                    return;
                }
                sendDataCallListResponse(msg);
            } else {
                m_pPdnManager->clearPdnInfo(olderAid);
                m_pPdnManager->clearPdnInfo(newerAid);
            }
        } else {
            // FAIL_CONT
            if (result == MIPC_RESULT_SUCCESS) {
                // FAIL_CONT and CONT success
                // check if need wait for NetAgent callback
                if (needWaitNetAgentNotification(newerAid)) {
                    // need wait for IPV6 update, NetAgent will invoke callback function
                    // save reqMessage clear ReqMessage after IP change callback.
                    RFX_LOG_I(RFX_LOG_TAG, "[%d][%s] wait for NetAgent notification",
                            rid, __FUNCTION__);
                    return;
                }
                createAndLaunchDataResponse(MIPC_RESULT_SUCCESS, newerAid);
            } else {
                // FAIL_CONT and CONT fail
                createAndLaunchDataResponse(MIPC_RESULT_FAILURE, newerAid);
                m_pPdnManager->clearPdnInfo(olderAid);
                m_pPdnManager->clearPdnInfo(newerAid);
            }
        }
    } else if (isFb && olderAid != INVALID_AID &&
            m_pPdnManager->getPdnActiveStatus(olderAid) == DATA_STATE_ACTIVE) {
        // SUCC_CONT
        if (result != MIPC_RESULT_SUCCESS) {
            RFX_LOG_E(RFX_LOG_TAG,
                    "[%d][%s] SUCC_CONT, CONT is not success, result:%d",
                    rid, __FUNCTION__, result);
            m_pPdnManager->clearPdnInfo(newerAid);
            return;
        }
        // check if need wait for NetAgent callback
        if (needWaitNetAgentNotification(newerAid)) {
            // need wait for IPV6 update, NetAgent will invoke callback function
            RFX_LOG_I(RFX_LOG_TAG,
                    "[%d][%s] SUCC_CONT, wait for NetAgent notification",
                    rid, __FUNCTION__);
            return;
        }
        if (m_mapAidReqmsg[olderAid] == NULL) {
            sendDataCallListResponse(msg);
        } else {
            createAndLaunchDataResponse(MIPC_RESULT_SUCCESS, newerAid);
        }
    } else {
        updateActiveStatusAndProfile(NULL, false);
        if (DATA_STATE_INACTIVE == m_pPdnManager->getPdnActiveStatus(newerAid)) {
            RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] newerAid%d is inactive",
                    rid, __FUNCTION__, newerAid);
            return;
        }

        // check if need wait for NetAgent callback
        if (needWaitNetAgentNotification(newerAid)) {
            // need wait for IPV6 update, NetAgent will invoke callback function
            RFX_LOG_I(RFX_LOG_TAG, "[%d][%s] wait for NetAgent notification",
                    rid, __FUNCTION__);
            return;
        }
        sendDataCallListResponse(msg);
    }
}

// Handle data modify ind for both Default Bearer and Dedicate Bearer
void RmmDcEventHandler::onDataModify(const sp<RfxMclMessage>& msg) {
    int *pEventData = (int *)msg->getData()->getData();
    int aid = pEventData[0];
    Vector<int> vAid;
    vAid.reserve(1);
    vAid.push_back(aid);
    int defaultAid = INVALID_AID;

    defaultAid = m_pPdnManager->getPrimaryAid(aid);
    if (!m_pPdnManager->isDedicateBearer(aid)) {
        // Default Bearer
        if (DATA_STATE_INACTIVE == isAllAidActive(&vAid)) {
            RFX_LOG_W(RFX_LOG_TAG, "[%d][%s] not all aid active", m_slot_id, __FUNCTION__);
            return;
        }
        sp<RfxMipcData> mipcReq = RfxMipcData::obtainMipcData(
                MIPC_DATA_GET_CALL_REQ, m_slot_id);
        mipcReq->addMipcTlvUint8(MIPC_DATA_GET_CALL_REQ_T_ID, (uint8_t)aid);
        sp<RfxMipcData> mipcCnf = callToMipcMsgSync(mipcReq);
        if ((mipc_result_const_enum) mipcCnf->getResult() != MIPC_RESULT_SUCCESS) {
            RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] MIPC_DATA_GET_CALL_REQ return error",
                    m_slot_id, __FUNCTION__);
            return;
        }
        decodeDataCallProfile(mipcCnf, GET_CNF);

        if (DATA_STATE_ACTIVE == m_pPdnManager->getPdnActiveStatus(aid)) {
            requestOrSendDataCallList(msg, aid);
            RFX_LOG_D(RFX_LOG_TAG,
                    "[%d][%s] udpate default bearer %d thru DataCallListChanged",
                    m_slot_id, __FUNCTION__, aid);
        } else {
            RFX_LOG_W(RFX_LOG_TAG, "[%d][%s] default bearer %d is not activated, "
                    "not to send URC for data call modification",
                    m_slot_id, __FUNCTION__, aid);
        }
    } else if (m_pPdnManager->isDedicateBearer(aid) && INVALID_AID != defaultAid) {
        // Dedicate Bearer
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] a dedicate bearer is modified [aid=%d]",
                m_slot_id, __FUNCTION__, aid);
        m_pPdnManager->updateTransIntfId(aid, m_pPdnManager->getTransIntfId(defaultAid));
        m_pPdnManager->updatePdnActiveStatus(aid,
                m_pPdnManager->getPdnActiveStatus(defaultAid));
        if (DATA_STATE_INACTIVE == isAllAidActive(&vAid)) {
            RFX_LOG_W(RFX_LOG_TAG, "[%d][%s] not all aid active", m_slot_id, __FUNCTION__);
            return;
        }

        if (DATA_STATE_ACTIVE == m_pPdnManager->getPdnActiveStatus(defaultAid)) {
            updateQosInformation(aid, true);
            requestOrSendDataCallList(msg, defaultAid);
            RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] dedicate bearer %d modified, send URC",
                    m_slot_id, __FUNCTION__, aid);
        } else {
            RFX_LOG_W(RFX_LOG_TAG, "[%d][%s] default bearer %d is not activated, "
                    "not to send URC for dedicate data call modification",
                    m_slot_id, __FUNCTION__, aid);
        }
    }
}

// Check if a dedicate bearer PDN info should be add to data call reponse.
bool RmmDcEventHandler::isValidDedicateBearer(int dftId, int ddctId) {
    if ((!m_pPdnManager->isDedicateBearer(dftId) && m_pPdnManager->isDedicateBearer(ddctId))
            && m_pPdnManager->getTransIntfId(dftId) == m_pPdnManager->getTransIntfId(ddctId)
            && (m_pPdnManager->getAccessNetwork(dftId) == E_UTRAN
                    || m_pPdnManager->getAccessNetwork(dftId) == NG_RAN)) {
        if (m_pPdnManager->getQosSession(ddctId) == NULL) {
            RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] dedicate bearer[%d] qos session is empty",
                    m_slot_id, __FUNCTION__, ddctId);
            return false;
        } else if (m_pPdnManager->getQosSession(ddctId)->qosFilterCount == 0) {
            RFX_LOG_W(RFX_LOG_TAG, "[%d][%s] dedicate bearer[%d] qos filter count is 0",
                    m_slot_id, __FUNCTION__, ddctId);
            return false;
        }
        return true;
    }
    return false;
}

// Handle data deact for both Default Bearer and Dedicate Bearer
void RmmDcEventHandler::onDataDeact(const sp<RfxMclMessage>& msg) {
    int *pEventData = (int *)msg->getData()->getData();
    int aid = pEventData[0];
    int res = pEventData[1];
    int rid = m_slot_id;
    const int nPdnInfoSize = m_pPdnManager->getPdnTableSize();

    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] aid=%d, res=%d", rid, __FUNCTION__, aid, res);

    // dedicate bearer
    if (m_pPdnManager->isDedicateBearer(aid)) {
        int p_aid = m_pPdnManager->getPrimaryAid(aid);
        RFX_LOG_I(RFX_LOG_TAG, "[%d][%s] dedicate bearer deact, aid=%d, p_aid=%d",
                rid, __FUNCTION__, aid, p_aid);
        m_pPdnManager->clearPdnInfo(aid);
        requestOrSendDataCallList(msg, p_aid);
        return;
    }

    // default bearer
    m_pPdnManager->setDeactReason(aid, convertFailCauseToRilStandard(res));
    for (int i = 0; i < nPdnInfoSize; i++) {
        if (m_pPdnManager->isDedicateBearer(i) && m_pPdnManager->getPrimaryAid(i) == aid) {
            RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] clean dedicate pdn aid%d info "
                    "due to default pdn aid%d deactivated", rid, __FUNCTION__,
                    m_pPdnManager->getAid(i), aid);
            m_pPdnManager->clearPdnInfo(i);
        }
    }

    if (createAndLaunchDataResponse(MIPC_RESULT_FAILURE, aid)) {
        m_pPdnManager->clearPdnInfo(aid);
        return;
    }

    if (notifyDeactReasonIfNeeded(aid)) {
        sendDataCallListResponse(msg, aid);
        m_pPdnManager->clearPdnInfo(aid);
        return;
    }

    m_pPdnManager->clearPdnInfo(aid);
    sendDataCallListResponse(msg);
    requestGetDataContextIds(msg);
    setPdnInfoProperty();
}

void RmmDcEventHandler::onPdnChange(const sp<RfxMclMessage>& msg) {
    int *info = (int *)msg->getData()->getData();
    int oldRat = m_pPdnManager->getRat(info[PDN_HANDOVER_INFO_CID]);

    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s]: %d,%d,%d,%d", m_slot_id, __FUNCTION__,
            info[PDN_HANDOVER_INFO_CID], info[PDN_HANDOVER_INFO_OLD_RAT],
            info[PDN_HANDOVER_INFO_NEW_RAT], oldRat);

    onMePdnPropertyChange(msg, info[PDN_HANDOVER_INFO_CID]);
    int newRat = m_pPdnManager->getRat(info[PDN_HANDOVER_INFO_CID]);
    if (newRat != info[PDN_HANDOVER_INFO_NEW_RAT]) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] different newrat:%d !!", m_slot_id, __FUNCTION__, newRat);
    }
    sendQualifiedNetworkTypesChanged(info[PDN_HANDOVER_INFO_CID], newRat);
}

void RmmDcEventHandler::onMePdnPropertyChange(const sp<RfxMclMessage>& msg, const int aid) {
    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] aid%d", m_slot_id, __FUNCTION__, aid);
    // Because this event was sent from URC channel to Data channel asynchronously, need to
    // confirm active status before do other things.
    if (PDN_SUCCESS != updateActiveStatusAndProfileById(aid)) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] updateActiveStatusAndProfileById failed for aid%d",
                m_slot_id, __FUNCTION__, aid);
        return;
    }
    sendDataCallListResponse(msg);
}

// Support IWLAN AP-ASSISTED mode
void RmmDcEventHandler::onQualifiedNetworkTypeChanged(const sp<RfxMclMessage>& msg) {
    MipcQualifiedNetworkInfo *info = (MipcQualifiedNetworkInfo *)msg->getData()->getData();
    sp<RfxMclMessage> urcMsg;
    bool isUrcForActiveApnType = false;
    int mPdnTableSize = m_pPdnManager->getPdnTableSize();
    PdnInfo pdnInfo;

    if (strncmp("setup", info->cmd, strlen("setup")) == 0) {
        const char *type = NULL;
        int matchApnType = -1;
        RFX_LOG_I(RFX_LOG_TAG, "[%d][%s] type=%s", m_slot_id, __FUNCTION__, info->type);
        for (int i = 0; i < MAX_COUNT_QUALIFIED_NETWORK_UPDATE_APNS; i++) {
            type = RmmDcUtility::getApnType(SUPPORT_QUALIFIED_NETWORK_UPDATE_APNS[i]);
            if (strncmp(info->type, type, strlen(type)) == 0){
                matchApnType = SUPPORT_QUALIFIED_NETWORK_UPDATE_APNS[i];
                RFX_LOG_I(RFX_LOG_TAG, "[%d][%s] matchApnType=%d", m_slot_id, __FUNCTION__,
                        matchApnType);
                break;
            }
        }
        if (matchApnType < 0) {
            RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] no match APN type.", m_slot_id, __FUNCTION__);
            return;
        }

        // get RAT
        int rat = ACCESS_NW_TYPE_UNKNOWN;
        int ratList[6] = {ACCESS_NW_TYPE_UNKNOWN};// [0] for mode, [1] for APN type
        int ratIndex = 2;
        int skipIwlan = false;
        for (int i = 0; i < info->ratNum; i++) {
            rat = info->ratList[i];
            // If prefer is VoData, transfer type to IWLAN
            if (rat >= ACCESS_NW_TYPE_VODATA1 && rat <= ACCESS_NW_TYPE_VODATA4) {
                rat = ACCESS_NW_TYPE_IWLAN;
            }

            if (rat == ACCESS_NW_TYPE_IWLAN) {
                if (!skipIwlan) {
                    skipIwlan = true;
                    ratList[ratIndex] = rat;
                    ratIndex++;
                }
            } else {
                ratList[ratIndex] = rat;
                ratIndex++;
            }
        }

        // check if APN type(ims or emergency or mms) of URC is active state
        for (int i = 0; i < mPdnTableSize; i++) {
            int currentAid = m_pPdnManager->getAid(i);
            if (currentAid != INVALID_AID) {
                pdnInfo = m_pPdnManager->getPdnInfo(currentAid);
                RFX_LOG_I(RFX_LOG_TAG, "[%d][%s] pdnInfo.profileId=%d, pdn_info.active=%d",
                        m_slot_id, __FUNCTION__, pdnInfo.profileId, pdnInfo.active);
                if ((matchApnType == RmmDcUtility::getApnTypeId(pdnInfo.profileId))
                        && (pdnInfo.active == DATA_STATE_ACTIVE)) {
                    isUrcForActiveApnType = true;
                    break;
                }
            }
        }

        if (isUrcForActiveApnType) {
            RFX_LOG_I(RFX_LOG_TAG, "[%d][%s] apn state is active skip to notify",
                    m_slot_id, __FUNCTION__);
        } else {
            ratList[0] = 1; //Mode
            ratList[1] = matchApnType; //APN type
            urcMsg = RfxMclMessage::obtainUrc(RFX_MSG_URC_QUALIFIED_NETWORK_TYPES_CHANGED,
                    m_slot_id, RfxIntsData(ratList, (info->ratNum + 2)));
            responseToTelCore(urcMsg);
        }
    } else {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] unknown cmd: %s", m_slot_id, __FUNCTION__, info->cmd);
    }
}

void RmmDcEventHandler::requestDeactivateDataCall(const sp<RfxMclMessage>& msg) {
    const char **pReqData = (const char **)msg->getData()->getData();
    int transIntfId = atoi(pReqData[0]);
    int reason = atoi(pReqData[1]);
    int rid = m_slot_id;
    int err = 0;
    const int nPdnInfoSize = m_pPdnManager->getPdnTableSize();
    sp<RfxMclMessage> responseMsg;

    RFX_LOG_I(RFX_LOG_TAG, "[%d][%s] transIntfId=%d, reason: %d",
            rid, __FUNCTION__, transIntfId, reason);

    if (reason != DEACT_REASON_AOSP_HANDOVER && transIntfId > INVALID_TRANS_INTF_ID) {
        for (int i = 0; i < nPdnInfoSize; i++) {
            if ((m_pPdnManager->getTransIntfId(i) == transIntfId)
                    && !m_pPdnManager->isDedicateBearer(i)) {
                // Error handling if needed.
                err = deactivateDataCall(m_pPdnManager->getAid(i), reason);

                // Reset pdn info with current aid.
                m_pPdnManager->clearPdnInfo(m_pPdnManager->getAid(i));
            }
        }
    }

    sendEvent(RFX_MSG_EVENT_REQ_DATA_CONTEXT_IDS, RfxVoidData(),
            RIL_CMD_PROXY_5, m_slot_id, -1, -1, 100e6);
    setPdnInfoProperty();

    responseMsg = RfxMclMessage::obtainResponse(RIL_E_SUCCESS, RfxVoidData(), msg);
    responseToTelCore(responseMsg);
}

int RmmDcEventHandler::deactivateDataCall(const int aid) {
    return deactivateDataCall(aid, DEACT_REASON_UNKNOWN);
}

int RmmDcEventHandler::deactivateDataCall(const int aid, const int reason) {
    int rid = m_slot_id;
    // Check if AID is out of bound.
    if (!m_pPdnManager->validateAid(aid)) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] aid=%d is out of bound",
                rid, __FUNCTION__, aid);
        return CME_ERROR_NON_CME;
    }

    sp<RfxMipcData> mipcReq = RfxMipcData::obtainMipcData(MIPC_DATA_DEACT_CALL_REQ, rid);
    mipcReq->addMipcTlvUint8(MIPC_DATA_DEACT_CALL_REQ_T_ID, (uint8_t)aid);
    mipcReq->addMipcTlvUint8(MIPC_DATA_DEACT_CALL_REQ_T_DEACT_REASON,
            (uint8_t)convertDeactCauseToMdStandard(reason));
    sp<RfxMipcData> mipcCnf = callToMipcMsgSync(mipcReq);
    mipc_result_const_enum mipcRet = (mipc_result_const_enum) mipcCnf->getResult();
    if (mipcRet != MIPC_RESULT_SUCCESS) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] MIPC_DATA_DEACT_CALL_REQ return error",
                rid, __FUNCTION__);
        return convertFailCauseToRilStandard(mipcRet);
    }

    int respAid = (int) mipcCnf->getMipcUint8Val(MIPC_DATA_DEACT_CALL_CNF_T_ID, 0);
    if (respAid != aid) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] aid%d is different from MD assigned aid%d",
                rid, __FUNCTION__, aid, respAid);
        return CME_ERROR_NON_CME;
    }

    return CME_SUCCESS;
}

bool RmmDcEventHandler::isSupportSelfSetInitialAttach() {
    int cardType = getMclStatusManager()->getIntValue(RFX_STATUS_KEY_CARD_TYPE);
    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] : cardType = %d", m_slot_id, __FUNCTION__, cardType);
    if (m_slot_id >= MAX_SIM_COUNT || cardType == 0) {
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] : cardType = %d, SIM not inserted, return",
                m_slot_id, __FUNCTION__, cardType);
        return false;
    }

    bool onlyEccApn = false;
    bool onlyImsApn = false;
    int size = RmmDcEventHandler::s_nLastReqNum[m_slot_id];
    for (int i = 0; i < size; i++) {
        RIL_MtkDataProfileInfo *profile = &RmmDcEventHandler::s_LastApnTable[m_slot_id][i];
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] : [%d] of apn, supportedTypesBitmask = %d",
                m_slot_id, __FUNCTION__, i, profile->supportedTypesBitmask);
        if (profile->supportedTypesBitmask == RIL_APN_TYPE_EMERGENCY) onlyEccApn = true;
        if (profile->supportedTypesBitmask == RIL_APN_TYPE_IMS) onlyImsApn = true;
    }

    // If only ECC or only ECC&IMS APN configured, set IA modem prefer to modem.
    // Because Java Framework will add ECC or ECC&IMS by default but not use ECC or IMS as IA.
    if ((size == 1 && onlyEccApn) || (size == 2 && onlyEccApn && onlyImsApn)) return true;
    return false;
}

void RmmDcEventHandler::handleIfVendorSelfIaNeeded() {
    if (isSupportSelfSetInitialAttach()) {
        RFX_LOG_I(RFX_LOG_TAG, "[%d][%s] : Modem auto mode.", m_slot_id, __FUNCTION__);
        sp<RfxMipcData> mipcMsg = RfxMipcData::obtainMipcData(MIPC_APN_SET_IA_MD_PREFER_REQ,
                m_slot_id);
        mipcMsg->addMipcTlvUint8(MIPC_APN_SET_IA_MD_PREFER_REQ_T_IA_MD_PREFER, 1);
        callToMipcMsgSync(mipcMsg);
    }
}

void RmmDcEventHandler::requestSyncApnTable(const sp<RfxMclMessage>& msg) {
    int n = 0;
    int cmdIndex = 1;
    sp<RfxMclMessage> resp;
    RIL_MtkDataProfileInfo **dataProfilePtrs =
                (RIL_MtkDataProfileInfo **)msg->getData()->getData();
    int nReqNum = msg->getData()->getDataLength() / sizeof(RIL_MtkDataProfileInfo*);

    if (nReqNum <= 0) {
        resp = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_GENERIC_FAILURE,
                RfxVoidData(), msg, false);
        responseToTelCore(resp);
        return;
    }

    adjustBearerBitmask(dataProfilePtrs, nReqNum);

    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] num of pararmeters = %d", m_slot_id, __FUNCTION__, nReqNum);

    // avoid syncing the same apn table, e.g. sub id ready then record loaded event
    if (s_LastApnTable[m_slot_id] != NULL) {
        bool bSameApnTable = true;
        if (s_nLastReqNum[m_slot_id] == nReqNum) {
            for (int i = 0; i < s_nLastReqNum[m_slot_id]; i++) {
                RIL_MtkDataProfileInfo *preProfile = &s_LastApnTable[m_slot_id][i];
                RIL_MtkDataProfileInfo *curProfile = dataProfilePtrs[i];
                if (preProfile->profileId != curProfile->profileId
                        || 0 != strcmp(preProfile->apn, curProfile->apn)
                        || 0 != strcmp(preProfile->protocol, curProfile->protocol)
                        || 0 != strcmp(preProfile->roamingProtocol, curProfile->roamingProtocol)
                        || preProfile->authType != curProfile->authType
                        || 0 != strcmp(preProfile->user, curProfile->user)
                        || 0 != strcmp(preProfile->password, curProfile->password)
                        || preProfile->maxConnsTime != curProfile->maxConnsTime
                        || preProfile->maxConns != curProfile->maxConns
                        || preProfile->waitTime != curProfile->waitTime
                        || preProfile->enabled != curProfile->enabled
                        || preProfile->supportedTypesBitmask != curProfile->supportedTypesBitmask
                        || preProfile->bearerBitmask != curProfile->bearerBitmask
                        || preProfile->inactiveTimer != curProfile->inactiveTimer) {
                    bSameApnTable = false;
                    break;
                }
            }
        } else {
            bSameApnTable = false;
        }
        if (bSameApnTable) {
            RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] ignore same apn table sync",
                    m_slot_id, __FUNCTION__);
            // Make IA the same as used to be.
            // Once the Set_Data_Profile triggered, send the EIAAPN even if EAPNSET is ignored.
            handleIfVendorSelfIaNeeded();
            resp = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
                    RfxVoidData(), msg, false);
            responseToTelCore(resp);
            return;
        } else {
            // reset Last APN table
            resetLastApnTable();
        }
    }

    // init s_nLastReqNum, s_ApnCmdIndex, and s_LastApnTable
    s_nLastReqNum[m_slot_id] = nReqNum;
    s_ApnCmdIndex[m_slot_id] = (int*)calloc(s_nLastReqNum[m_slot_id], sizeof(int));
    RFX_ASSERT(s_ApnCmdIndex[m_slot_id] != NULL);
    s_LastApnTable[m_slot_id] = (RIL_MtkDataProfileInfo*)calloc(s_nLastReqNum[m_slot_id],
            sizeof(RIL_MtkDataProfileInfo));
    RFX_ASSERT(s_LastApnTable[m_slot_id] != NULL);

    sp<RfxMipcData> mipcMsg = RfxMipcData::obtainMipcData(MIPC_APN_ADD_PROFILE_LIST_REQ, m_slot_id);
    mipcMsg->addMipcTlvUint8(MIPC_APN_ADD_PROFILE_LIST_REQ_T_PROFILE_COUNT, nReqNum);
    mipc_msg_tlv_array_t *apnList =
        mipc_msg_add_tlv_array(mipcMsg->getData(),
                                MIPC_APN_ADD_PROFILE_LIST_REQ_T_PROFILE_LIST,
                                nReqNum);
    for (int i = 0; i < nReqNum; i++) {
        // update Last APN table
        s_LastApnTable[m_slot_id][i].profileId = dataProfilePtrs[i]->profileId;
        asprintf(&s_LastApnTable[m_slot_id][i].apn, "%s", dataProfilePtrs[i]->apn);
        asprintf(&s_LastApnTable[m_slot_id][i].protocol, "%s", dataProfilePtrs[i]->protocol);
        asprintf(&s_LastApnTable[m_slot_id][i].roamingProtocol, "%s",
                dataProfilePtrs[i]->roamingProtocol);
        s_LastApnTable[m_slot_id][i].authType = dataProfilePtrs[i]->authType;  //backup raw data
        asprintf(&s_LastApnTable[m_slot_id][i].user, "%s", dataProfilePtrs[i]->user);
        asprintf(&s_LastApnTable[m_slot_id][i].password, "%s", dataProfilePtrs[i]->password);
        s_LastApnTable[m_slot_id][i].type = dataProfilePtrs[i]->type;
        s_LastApnTable[m_slot_id][i].maxConnsTime = dataProfilePtrs[i]->maxConnsTime;
        s_LastApnTable[m_slot_id][i].maxConns = dataProfilePtrs[i]->maxConns;
        s_LastApnTable[m_slot_id][i].waitTime = dataProfilePtrs[i]->waitTime;
        s_LastApnTable[m_slot_id][i].enabled = dataProfilePtrs[i]->enabled;
        s_LastApnTable[m_slot_id][i].supportedTypesBitmask =
                dataProfilePtrs[i]->supportedTypesBitmask;
        s_LastApnTable[m_slot_id][i].bearerBitmask = dataProfilePtrs[i]->bearerBitmask;
        s_LastApnTable[m_slot_id][i].mtu = dataProfilePtrs[i]->mtu;
        asprintf(&s_LastApnTable[m_slot_id][i].mvnoType, "%s", dataProfilePtrs[i]->mvnoType);
        asprintf(&s_LastApnTable[m_slot_id][i].mvnoMatchData, "%s",
                dataProfilePtrs[i]->mvnoMatchData);
        s_LastApnTable[m_slot_id][i].inactiveTimer = dataProfilePtrs[i]->inactiveTimer;

        cmdIndex = 0;
        for (int j = 0; j < i; j++) {
            if (0 == strcasecmp(dataProfilePtrs[i]->apn, dataProfilePtrs[j]->apn)) {
                cmdIndex += CMD_INDEX_OFFSET;
            }
        }
        s_ApnCmdIndex[m_slot_id][i] = cmdIndex;

        //add a mipc apn item.
        mipc_apn_profile_v2_struct4 apnItem;
        memset(&apnItem, 0, sizeof(mipc_apn_profile_v2_struct4));
        apnItem.id = s_LastApnTable[m_slot_id][i].profileId;
        n = snprintf(apnItem.apn, MIPC_MAX_APN_LEN, "%s", s_LastApnTable[m_slot_id][i].apn);
        if (n < 0) {
            RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] print APN fail.", m_slot_id, __FUNCTION__);
        }
        apnItem.apn_idx = cmdIndex;
        n = snprintf(apnItem.userid, MIPC_MAX_USERID_LEN, "%s", s_LastApnTable[m_slot_id][i].user);
        if (n < 0) {
            RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] print userid fail.", m_slot_id, __FUNCTION__);
        }
        n = snprintf(apnItem.password, MIPC_MAX_PASSWORD_LEN, "%s",
                s_LastApnTable[m_slot_id][i].password);
        if (n < 0) {
            RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] print password fail.", m_slot_id, __FUNCTION__);
        }
        apnItem.bearer_bitmask = s_LastApnTable[m_slot_id][i].bearerBitmask;
        apnItem.apn_type =
                RmmDcUtility::getMipcApnType(s_LastApnTable[m_slot_id][i].supportedTypesBitmask);
        apnItem.pdp_type = RmmDcUtility::getProtocolType(s_LastApnTable[m_slot_id][i].protocol);
        apnItem.roaming_type =
                RmmDcUtility::getProtocolType(s_LastApnTable[m_slot_id][i].roamingProtocol);
        apnItem.auth_type = RmmDcUtility::getAuthType(s_LastApnTable[m_slot_id][i].authType);
        apnItem.enabled = s_LastApnTable[m_slot_id][i].enabled;
        apnItem.max_conns = s_LastApnTable[m_slot_id][i].maxConns;
        apnItem.max_conn_t = s_LastApnTable[m_slot_id][i].maxConnsTime;
        apnItem.wait_time = s_LastApnTable[m_slot_id][i].waitTime;
        apnItem.inact_timer = s_LastApnTable[m_slot_id][i].inactiveTimer;
        apnItem.v4_mtu = s_LastApnTable[m_slot_id][i].mtu;
        apnItem.v6_mtu = s_LastApnTable[m_slot_id][i].mtu;
        mipc_msg_add_idx(mipcMsg->getData(), apnList, i, sizeof(mipc_apn_profile_v2_struct4),
                &apnItem);
    }

    callToMipcMsgSync(mipcMsg);
    handleIfVendorSelfIaNeeded();
    resp = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS, RfxVoidData(), msg, false);
    responseToTelCore(resp);
    return;
}

// Check whether the initial attach apn is in the apn list.
bool RmmDcEventHandler::isValidInitialAttachApn(const char* apn) {
    for (int i = 0; i < s_nLastReqNum[m_slot_id]; i++) {
        RIL_MtkDataProfileInfo *profile = &RmmDcEventHandler::s_LastApnTable[m_slot_id][i];
        if (strcmp(apn, profile->apn) == 0) {
            return true;
        }
    }

    return false;
}

void RmmDcEventHandler::requestSetInitialAttachApn(const sp<RfxMclMessage>& msg) {
    RIL_InitialAttachApn_v15 *iaData = (RIL_InitialAttachApn_v15 *)msg->getData()->getData();
    sp<RfxMclMessage> pMclResponse;

    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] %s/%s/%s/%d",m_slot_id, __FUNCTION__,
            iaData->apn, iaData->protocol, iaData->roamingProtocol, iaData->authtype);

    if (!isValidInitialAttachApn(iaData->apn)) {
        RFX_LOG_I(RFX_LOG_TAG, "[%d][%s] invalid apn %s, let modem select it",
                m_slot_id, __FUNCTION__, iaData->apn);
        sp<RfxMipcData> mipcMsg = RfxMipcData::obtainMipcData(MIPC_APN_SET_IA_MD_PREFER_REQ,
                msg->getSlotId());
        mipcMsg->addMipcTlvUint8(MIPC_APN_SET_IA_MD_PREFER_REQ_T_IA_MD_PREFER, 1);
        callToMipcMsgSync(mipcMsg);
    } else {
        sp<RfxMipcData> mipcMsg = RfxMipcData::obtainMipcData(MIPC_APN_SET_IA_REQ,
                msg->getSlotId());
        mipcMsg->addMipcTlvStr(MIPC_APN_SET_IA_REQ_T_APN, iaData->apn);
        mipcMsg->addMipcTlvUint8(MIPC_APN_SET_IA_REQ_T_PDP_TYPE,
                RmmDcUtility::getProtocolType(iaData->protocol));
        mipcMsg->addMipcTlvUint8(MIPC_APN_SET_IA_REQ_T_ROAMING_TYPE,
                RmmDcUtility::getProtocolType(iaData->roamingProtocol));
        mipcMsg->addMipcTlvUint8(MIPC_APN_SET_IA_REQ_T_AUTH_TYPE,iaData->authtype);
        mipcMsg->addMipcTlvStr(MIPC_APN_SET_IA_REQ_T_USERID, iaData->username);
        mipcMsg->addMipcTlvStr(MIPC_APN_SET_IA_REQ_T_PASSWORD, iaData->password);
        callToMipcMsgSync(mipcMsg); // don't care response, it is just ia apn.
    }

    pMclResponse = RfxMclMessage::obtainResponse(msg->getId(),
            RIL_E_SUCCESS, RfxVoidData(), msg, false);
    // response to TeleCore
    responseToTelCore(pMclResponse);
}

void RmmDcEventHandler::requestSyncDataSettingsToMd(const sp<RfxMclMessage>& msg) {
    int *pReqData = (int *)msg->getData()->getData();
    int reqDataNum = msg->getData()->getDataLength() / sizeof(int);
    sp<RfxMclMessage> resp;

    // s_dataSetting[m_slot_id][0 (MOBILE_DATA)]:      data setting on/off.
    // s_dataSetting[m_slot_id][1 (ROAMING_DATA)]:     data roaming setting on/off.
    // s_dataSetting[m_slot_id][2 (DEFAULT_DATA_SIM)]: default data SIM setting.
    // s_dataSetting[m_slot_id][3 (DOMESTIC_ROAMING_DATA)]: domestic roaming setting.
    // s_dataSetting[m_slot_id][4 (INTERNATIONAL_ROAMING_DATA)]: international roaming setting.
    for (int i = 0; i < reqDataNum; i++) {
        if (pReqData[i] != SKIP_DATA_SETTINGS) {
            s_dataSetting[m_slot_id][i] = pReqData[i];
        }
    }

    sp<RfxMipcData> mipcMsg = RfxMipcData::obtainMipcData(MIPC_DATA_SET_CONFIG_REQ, msg->getSlotId());
    if (pReqData[MOBILE_DATA] != SKIP_DATA_SETTINGS) {
        mipcMsg->addMipcTlvUint8(MIPC_DATA_SET_CONFIG_REQ_T_MOBILE_DATA, pReqData[MOBILE_DATA]);
    }
    if (!RmmDcUtility::isOp20Support()) {
        if (pReqData[ROAMING_DATA] != SKIP_DATA_SETTINGS) {
            mipcMsg->addMipcTlvUint8(MIPC_DATA_SET_CONFIG_REQ_T_DATA_ROAMING,
                        pReqData[ROAMING_DATA]);
        }
    } else {
        if (pReqData[DOMESTIC_ROAMING_DATA] != SKIP_DATA_SETTINGS) {
            mipcMsg->addMipcTlvUint8(MIPC_DATA_SET_CONFIG_REQ_T_DATA_DOMESTIC_ROAMING,
                        pReqData[DOMESTIC_ROAMING_DATA]);
        }
        if (pReqData[INTERNATIONAL_ROAMING_DATA] != SKIP_DATA_SETTINGS) {
            mipcMsg->addMipcTlvUint8(MIPC_DATA_SET_CONFIG_REQ_T_DATA_INTERNATIONAL_ROAMING,
                        pReqData[INTERNATIONAL_ROAMING_DATA]);
        }
    }

    // 0: clear
    // 1: slot 0
    // 2: slot 1
    // Modem only receive the slot ID which start from 1.
    // And 0 is treated as "UNSET" to reset.
    // TO DO, add default sim
    if (pReqData[DEFAULT_DATA_SIM] != SKIP_DATA_SETTINGS) {
        mipcMsg->addMipcTlvUint8(MIPC_DATA_SET_CONFIG_REQ_T_DEFAULT_DATA_SIM_CARD,
                    pReqData[DEFAULT_DATA_SIM] + 1);
    }

    RFX_LOG_D(RFX_LOG_TAG,
            "[%d][%s] Start, dataOn:%d, dataRoaming:%d, defaultDataSim: %d,"
            "domestic roaming: %d, international raoming: %d",
            m_slot_id,
            __FUNCTION__,
            s_dataSetting[m_slot_id][MOBILE_DATA],
            s_dataSetting[m_slot_id][ROAMING_DATA],
            s_dataSetting[m_slot_id][DEFAULT_DATA_SIM],
            s_dataSetting[m_slot_id][DOMESTIC_ROAMING_DATA],
            s_dataSetting[m_slot_id][INTERNATIONAL_ROAMING_DATA]);

    /**
     * To get IMS test mode setting and sync to modem for OP12
     *    Enable : Set Attach PDN to VZWINTERNET
     *    Disable: Set Attach PDN to VZWIMS (Default)
     */
    char value[MTK_PROPERTY_VALUE_MAX] = {0};
    rfx_property_get("persist.vendor.radio.imstestmode", value, "0");
    int imsTestMode = atoi(value);
    mipcMsg->addMipcTlvUint8(MIPC_DATA_SET_CONFIG_REQ_T_IMS_TEST_MODE, imsTestMode);

    callToMipcMsgAsync(msg, mipcMsg);
    resp = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS, RfxVoidData(), msg, false);
    responseToTelCore(resp);
}

void RmmDcEventHandler::requestResetMdDataRetryCount(const sp<RfxMclMessage>& msg) {
    sp<RfxMclMessage> response;
    const char *apnName = (const char *)msg->getData()->getData();

    // Debug only
    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] Reset MD data count for APN: %s", msg->getSlotId(),
                __FUNCTION__, apnName);
    // in ril_service will expand "" string as NULL, change back to "".
    if (apnName == NULL) {
        apnName= "";
    }
    sp<RfxMipcData> mipcMsg = RfxMipcData::obtainMipcData(MIPC_DATA_RETRY_TIMER_REQ,
                                                            msg->getSlotId());
    mipcMsg->addMipcTlvUint8(MIPC_DATA_RETRY_TIMER_REQ_T_MODE, MIPC_DATA_RETRY_MODE_RESET_TIMER);
    mipcMsg->addMipcTlvStr(MIPC_DATA_RETRY_TIMER_REQ_T_APN_NAME, apnName);
    callToMipcMsgAsync(msg, mipcMsg);
    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
                                                RfxVoidData(), msg, false);
    responseToTelCore(response);
}

RIL_DataCallFailCause RmmDcEventHandler::convertFailCauseToRilStandard(int cause) {
    int rid = m_slot_id;

    // Only handle MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE section to minus
    // MIPC_RESULT_PDN_EXT_NETWORK_ERROR_BEGIN instead of minus
    // MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_BEGIN because it's 4 bytes cause.
    // Also no need to convert causes that bigger than 0x00150000,
    // because these special causes are for MIPC only.
    if (cause > MIPC_RESULT_PDN_EXT_CME_ERROR_BEGIN
            && cause < MIPC_RESULT_PDN_EXT_CME_ERROR_END) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] CME CAUSE: %X", rid, __FUNCTION__, cause);
        cause -= MIPC_RESULT_PDN_EXT_NETWORK_ERROR_BEGIN;
        if (cause == CME_PDP_AUTHENTICATION_FAILED) {
            return PDP_FAIL_USER_AUTHENTICATION;
        } else if (cause == CME_OPERATOR_DETERMINED_BARRING) {
            return PDP_FAIL_OPERATOR_BARRED;
        } else if (cause == CME_MAXIMUM_NMUBER_PDP_CONTEXTS_REACHED) {
            return PDP_FAIL_MAX_ACTIVE_PDP_CONTEXT_REACHED;
        } else if (cause == CME_REQUESTED_APN_NOT_SUPPORTED_IN_RAT_AND_PLMN) {
            return PDP_FAIL_UNSUPPORTED_APN_IN_CURRENT_PLMN;
        } else {
            cause -= CME_CAUSE_BASE_V14;
        }
    } else if (cause > MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_BEGIN
            && cause < MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_END) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] SM CAUSE: %X",
                rid, __FUNCTION__, cause);
        cause -= MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_BEGIN;
    } else if (cause > MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_BEGIN
            && cause < MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_END) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] ESM CAUSE: %X",
                rid, __FUNCTION__, cause);
        cause -= MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_BEGIN;
    } else if (cause > MIPC_RESULT_PDN_EXT_NETWORK_PAM_CAUSE_BEGIN
            && cause < MIPC_RESULT_PDN_EXT_NETWORK_PAM_CAUSE_END) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] PAM CAUSE: %X",
                rid, __FUNCTION__, cause);
        cause -= MIPC_RESULT_PDN_EXT_NETWORK_PAM_CAUSE_BEGIN;
    } else if (cause > MIPC_RESULT_PDN_EXT_NETWORK_ERROR_BEGIN
            && cause < MIPC_RESULT_PDN_EXT_NETWORK_ERROR_END) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] NETWORK CAUSE: %X",
                rid, __FUNCTION__, cause);
        cause -= MIPC_RESULT_PDN_EXT_NETWORK_ERROR_BEGIN;
    } else {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] CAUSE: %X", rid, __FUNCTION__, cause);
    }

    switch (cause) {
        case 0: return PDP_FAIL_NONE;
        case 0x08: return PDP_FAIL_OPERATOR_BARRED;
        case 0x0E: return PDP_FAIL_NAS_SIGNALLING;
        case 0x18: return PDP_FAIL_MBMS_CAPABILITIES_INSUFFICIENT;
        case 0x19: return PDP_FAIL_LLC_SNDCP;
        case 0x1A: return PDP_FAIL_INSUFFICIENT_RESOURCES;
        case 0x1B: return PDP_FAIL_MISSING_UKNOWN_APN;
        case 0x1C: return PDP_FAIL_UNKNOWN_PDP_ADDRESS_TYPE;
        case 0x1D: return PDP_FAIL_USER_AUTHENTICATION;
        case 0x1E: return PDP_FAIL_ACTIVATION_REJECT_GGSN;
        case 0x1F: return PDP_FAIL_ACTIVATION_REJECT_UNSPECIFIED;
        case 0x20: return PDP_FAIL_SERVICE_OPTION_NOT_SUPPORTED;
        case 0x21: return PDP_FAIL_SERVICE_OPTION_NOT_SUBSCRIBED;
        case 0x22: return PDP_FAIL_SERVICE_OPTION_OUT_OF_ORDER;
        case 0x23: return PDP_FAIL_NSAPI_IN_USE;
        case 0x24: return PDP_FAIL_REGULAR_DEACTIVATION;
        case 0x25: return PDP_FAIL_QOS_NOT_ACCEPTED;
        case 0x26: return PDP_FAIL_NETWORK_FAILURE;
        case 0x27: return PDP_FAIL_UMTS_REACTIVATION_REQ;
        case 0x28: return PDP_FAIL_FEATURE_NOT_SUPP;
        case 0x29: return PDP_FAIL_TFT_SEMANTIC_ERROR;
        case 0x2A: return PDP_FAIL_TFT_SYTAX_ERROR;
        case 0x2B: return PDP_FAIL_UNKNOWN_PDP_CONTEXT;
        case 0x2C: return PDP_FAIL_FILTER_SEMANTIC_ERROR;
        case 0x2D: return PDP_FAIL_FILTER_SYTAX_ERROR;
        case 0x2E: return PDP_FAIL_PDP_WITHOUT_ACTIVE_TFT;
        case 0x2F: return PDP_FAIL_MULTICAST_GROUP_MEMBERSHIP_TIMEOUT;
        case 0x30: return PDP_FAIL_BCM_VIOLATION;
        case 0x31: return PDP_FAIL_LAST_PDN_DISC_NOT_ALLOWED;
        case 0x32: return PDP_FAIL_ONLY_IPV4_ALLOWED;
        case 0x33: return PDP_FAIL_ONLY_IPV6_ALLOWED;
        case 0x34: return PDP_FAIL_ONLY_SINGLE_BEARER_ALLOWED;
        case 0x35: return PDP_FAIL_ESM_INFO_NOT_RECEIVED;
        case 0x36: return PDP_FAIL_PDN_CONN_DOES_NOT_EXIST;
        case 0x37: return PDP_FAIL_MULTI_CONN_TO_SAME_PDN_NOT_ALLOWED;
        case 0x38: return PDP_FAIL_COLLISION_WITH_NW_INITIATED_REQUEST;
        case 0x3B: return PDP_FAIL_ESM_UNSUPPORTED_QCI_VALUE;
        case 0x3C: return PDP_FAIL_BEARER_HANDLING_NOT_SUPPORT;
        case 0x41: return PDP_FAIL_MAX_ACTIVE_PDP_CONTEXT_REACHED;
        case 0x42: return PDP_FAIL_UNSUPPORTED_APN_IN_CURRENT_PLMN;
        case 0x51: return PDP_FAIL_INVALID_TRANSACTION_ID;
        case 0x5F: return PDP_FAIL_MESSAGE_INCORRECT_SEMANTIC;
        case 0x60: return PDP_FAIL_INVALID_MANDATORY_INFO;
        case 0x61: return PDP_FAIL_MESSAGE_TYPE_UNSUPPORTED;
        case 0x62: return PDP_FAIL_MSG_TYPE_NONCOMPATIBLE_STATE;
        case 0x63: return PDP_FAIL_UNKNOWN_INFO_ELEMENT;
        case 0x64: return PDP_FAIL_CONDITIONAL_IE_ERROR;
        case 0x65: return PDP_FAIL_MSG_AND_PROTOCOL_STATE_UNCOMPATIBLE;
        case 0x6F: return PDP_FAIL_PROTOCOL_ERRORS;
        case 0x70: return PDP_FAIL_APN_TYPE_CONFLICT;
        case 0x71: return PDP_FAIL_INVALID_PCSCF_ADDR;
        case 0x72: return PDP_FAIL_INTERNAL_CALL_PREEMPT_BY_HIGH_PRIO_APN;
        case 0x73: return PDP_FAIL_EMM_ACCESS_BARRED;
        case 0x74: return PDP_FAIL_EMERGENCY_IFACE_ONLY;
        case 0x75: return PDP_FAIL_IFACE_MISMATCH;
        case 0x76: return PDP_FAIL_COMPANION_IFACE_IN_USE;
        case 0x77: return PDP_FAIL_IP_ADDRESS_MISMATCH;
        case 0x78: return PDP_FAIL_IFACE_AND_POL_FAMILY_MISMATCH;
        case 0x79: return PDP_FAIL_EMM_ACCESS_BARRED_INFINITE_RETRY;
        case 0x7A: return PDP_FAIL_AUTH_FAILURE_ON_EMERGENCY_CALL;
        case 0x0E0F: return PDP_FAIL_LOCAL_REJECT_ACT_REQ_DUE_TO_REACH_RETRY_COUNTER;
        case 0x0F47: return PDP_FAIL_TCM_ESM_TIMER_TIMEOUT;
        case 0x0F8E: return PDP_FAIL_TCM_ESM_DEACT_DUE_TO_DRB_RELEASE;
        case 0x1402: return PDP_FAIL_PAM_ATT_PDN_ACCESS_REJECT_IMS_PDN_BLOCK_TEMP;
        case 0x1671: return PDP_FAIL_DATA_NOT_ALLOW;
        case 0x16F1: return PDP_FAIL_REJECTED_BY_IWLAN;
        case 0x1A27: return PDP_FAIL_VGSM_REACTIVATION_REQUESTED;
        // mapping modem cause VGSM_PROPRIETARY_CAUSE_CORE_SYNC_PDUS_STATUS_WITH_NW
        case 0x1AC0: return PDP_FAIL_TCM_ESM_DEACT_DUE_TO_DRB_RELEASE;
        case -1: return PDP_FAIL_VOICE_REGISTRATION_FAIL;
        case -2: return PDP_FAIL_DATA_REGISTRATION_FAIL;
        case -3: return PDP_FAIL_SIGNAL_LOST;
        case -4: return PDP_FAIL_PREF_RADIO_TECH_CHANGED;
        case -5: return PDP_FAIL_RADIO_POWER_OFF;
        case -6: return PDP_FAIL_TETHERED_CALL_ACTIVE;
        default: return PDP_FAIL_ERROR_UNSPECIFIED;
    }
}

int RmmDcEventHandler::convertDeactCauseToMdStandard(int reason) {
    switch (reason) {
        case DEACT_REASON_AOSP_SHUTDOWN:
            return MIPC_DEACT_REASON_ENUM_DEACT_AOSP_SHUTDOWN;
        case DEACT_REASON_AOSP_HANDOVER:
            return MIPC_DEACT_REASON_ENUM_DEACT_AOSP_HANDOVER;
        case DEACT_REASON_APN_CHANGED:
            return MIPC_DEACT_REASON_ENUM_DEACT_APN_CHANGED;
        case DEACT_REASON_TEMP_DATA_SWITCHING:
            return MIPC_DEACT_REASON_ENUM_DEACT_TEMP_DATA_SWITCH;

        case DEACT_REASON_UNKNOWN:
        case DEACT_REASON_AOSP_NORMAL:
        case DEACT_REASON_NORMAL:
        case DEACT_REASON_RA_INITIAL_FAIL:
        case DEACT_REASON_NO_PCSCF:
        case DEACT_REASON_RA_REFRESH_FAIL:
        default:
            return MIPC_DEACT_REASON_ENUM_DEACT_NORMAL;
    }
}

void RmmDcEventHandler::updateLastFailCause(int cause) {
    m_nGprsFailureCause = convertFailCauseToRilStandard(cause);
}

int RmmDcEventHandler::getLastFailCause() {
    RFX_LOG_I(RFX_LOG_TAG, "[%d][%s] CAUSE: %X", m_slot_id, __FUNCTION__, m_nGprsFailureCause);
    return m_nGprsFailureCause;
}

int RmmDcEventHandler::isAllAidActive(Vector<int> *vAidList) {
    int rid = m_slot_id;

    updateActiveStatusAndProfile(NULL, false);

    for (Vector<int>::iterator it = vAidList->begin(); it != vAidList->end(); it++) {
        int aid = *it;
        RFX_LOG_V(RFX_LOG_TAG, "[%d][%s] pdn_info[%d], state: %d",
                rid, __FUNCTION__, aid, m_pPdnManager->getPdnActiveStatus(aid));
        if (DATA_STATE_INACTIVE == m_pPdnManager->getPdnActiveStatus(aid)) {
            RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] aid%d is inactive", rid, __FUNCTION__, aid);
            return 0;
        }
    }

    return 1;
}

void RmmDcEventHandler::requestOrSendDataCallList(const sp<RfxMclMessage>& msg) {
    int rid = m_slot_id;
    MTK_RIL_Data_Call_Response_v11* responsesOfActive = NULL;
    Vector<int> vTransIntfIdList;
    Vector<int>::iterator it;
    sp<RfxMclMessage> responseMsg;
    const int nPdnInfoSize = m_pPdnManager->getPdnTableSize();

    RFX_LOG_V(RFX_LOG_TAG, "[%d][%s] PdnTableSize=%d", rid, __FUNCTION__, nPdnInfoSize);

    // Reserve size of TransIntfId list.
    vTransIntfIdList.reserve(nPdnInfoSize);

    // Update all PDN active status.
    if (PDN_SUCCESS != updateActiveStatusAndProfile()) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] updateActiveStatusAndProfile failed",
                rid, __FUNCTION__);
        goto error;
    }

    for (int i = 0; i < nPdnInfoSize; i++) {
        if ((m_pPdnManager->getPdnActiveStatus(i) == DATA_STATE_ACTIVE) &&
                (m_pPdnManager->getTransIntfId(i) != INVALID_TRANS_INTF_ID) &&
                (std::find(vTransIntfIdList.begin(), vTransIntfIdList.end(),
                m_pPdnManager->getTransIntfId(i)) == vTransIntfIdList.end())) {
            vTransIntfIdList.push_back(m_pPdnManager->getTransIntfId(i));
        }
    }

    if (vTransIntfIdList.size() > 0) {
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] active trans-interface number is %zu",
                rid, __FUNCTION__, vTransIntfIdList.size());

        responsesOfActive = (MTK_RIL_Data_Call_Response_v11*)
                calloc(1, vTransIntfIdList.size() * sizeof(MTK_RIL_Data_Call_Response_v11));

        if (responsesOfActive == NULL) {
            RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] fail to allocate responsesOfActive!",
                    rid, __FUNCTION__);
            RFX_ASSERT(false);
        }

        initDataCallResponse(responsesOfActive, vTransIntfIdList.size());
        int index = 0;
        for (it = vTransIntfIdList.begin(); it != vTransIntfIdList.end(); it++) {
            int transIntfId = *it;
            createDataResponse(transIntfId, IPV4V6, &responsesOfActive[index]);
            ++index;
        }
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] %s", rid, __FUNCTION__,
                responsesToString(responsesOfActive, vTransIntfIdList.size()).string());

        if (msg->getType() == RFX_MESSAGE_TYPE::REQUEST) {
            responseMsg = RfxMclMessage::obtainResponse(RIL_E_SUCCESS,
                    RfxDataCallResponseData(responsesOfActive, vTransIntfIdList.size()), msg);
        } else {
            responseMsg = RfxMclMessage::obtainUrc(RFX_MSG_URC_DATA_CALL_LIST_CHANGED, rid,
                    RfxDataCallResponseData(responsesOfActive, vTransIntfIdList.size()));
        }
    } else {
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] no active response", rid, __FUNCTION__);

        if (msg->getType() == RFX_MESSAGE_TYPE::REQUEST) {
            responseMsg = RfxMclMessage::obtainResponse(RIL_E_SUCCESS, RfxVoidData(), msg);
        } else {
            responseMsg = RfxMclMessage::obtainUrc(RFX_MSG_URC_DATA_CALL_LIST_CHANGED, rid,
                    RfxVoidData());
        }
    }

    responseToTelCore(responseMsg);

    if (responsesOfActive != NULL) {
        int size = vTransIntfIdList.size();
        for (int i = 0; i < size; i++) {
            freeDataResponse(&responsesOfActive[i]);
        }
        FREEIF(responsesOfActive);
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] free responsesOfActive", rid, __FUNCTION__);
    }

    return;

error:
    if (msg->getType() == RFX_MESSAGE_TYPE::REQUEST) {
        responseMsg = RfxMclMessage::obtainResponse(RIL_E_GENERIC_FAILURE, RfxVoidData(), msg);
    } else {
        responseMsg = RfxMclMessage::obtainUrc(RFX_MSG_URC_DATA_CALL_LIST_CHANGED, rid, RfxVoidData());
    }
    responseToTelCore(responseMsg);
}

void RmmDcEventHandler::requestOrSendDataCallList(const sp<RfxMclMessage>& msg, Vector<int> *vAidList) {
    int rid = m_slot_id;
    MTK_RIL_Data_Call_Response_v11* responsesOfActive = NULL;
    Vector<int> vTransIntfIdList;
    Vector<int>::iterator it;
    sp<RfxMclMessage> responseMsg;
    const int nPdnInfoSize = m_pPdnManager->getPdnTableSize();

    RFX_LOG_V(RFX_LOG_TAG, "[%d][%s] PdnTableSize=%d", rid, __FUNCTION__, nPdnInfoSize);

    // Reserve size of TransIntfId list.
    vTransIntfIdList.reserve(nPdnInfoSize);

    if (PDN_SUCCESS != updateActiveStatusAndProfile(vAidList)) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] updateActiveStatusAndProfile failed",
                rid, __FUNCTION__);
    }

    for (int i = 0; i < nPdnInfoSize; i++) {
        if ((m_pPdnManager->getPdnActiveStatus(i) == DATA_STATE_ACTIVE) &&
                (m_pPdnManager->getTransIntfId(i) != INVALID_TRANS_INTF_ID) &&
                (std::find(vTransIntfIdList.begin(), vTransIntfIdList.end(),
                m_pPdnManager->getTransIntfId(i)) == vTransIntfIdList.end())) {
            vTransIntfIdList.push_back(m_pPdnManager->getTransIntfId(i));
        }
    }

    if (vTransIntfIdList.size() > 0) {
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] active trans-interface number is %zu",
                rid, __FUNCTION__, vTransIntfIdList.size());

        responsesOfActive = (MTK_RIL_Data_Call_Response_v11*)
                calloc(1, vTransIntfIdList.size() * sizeof(MTK_RIL_Data_Call_Response_v11));

        if (responsesOfActive == NULL) {
            RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] fail to allocate responsesOfActive!",
                    rid, __FUNCTION__);
            RFX_ASSERT(false);
        }

        initDataCallResponse(responsesOfActive, vTransIntfIdList.size());
        int index = 0;
        for (it = vTransIntfIdList.begin(); it != vTransIntfIdList.end(); it++) {
            int transIntfId = *it;
            createDataResponse(transIntfId, IPV4V6, &responsesOfActive[index]);
            ++index;
        }
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] %s", rid, __FUNCTION__,
                responsesToString(responsesOfActive, vTransIntfIdList.size()).string());

        if (msg->getType() == RFX_MESSAGE_TYPE::REQUEST) {
            responseMsg = RfxMclMessage::obtainResponse(RIL_E_SUCCESS,
                    RfxDataCallResponseData(responsesOfActive, vTransIntfIdList.size()), msg);
        } else {
            responseMsg = RfxMclMessage::obtainUrc(RFX_MSG_URC_DATA_CALL_LIST_CHANGED, rid,
                    RfxDataCallResponseData(responsesOfActive, vTransIntfIdList.size()));
        }
    } else {
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] no active response", rid, __FUNCTION__);

        if (msg->getType() == RFX_MESSAGE_TYPE::REQUEST) {
            responseMsg = RfxMclMessage::obtainResponse(RIL_E_SUCCESS, RfxVoidData(), msg);
        } else {
            responseMsg = RfxMclMessage::obtainUrc(RFX_MSG_URC_DATA_CALL_LIST_CHANGED, rid,
                    RfxVoidData());
        }
    }

    responseToTelCore(responseMsg);

    if (responsesOfActive != NULL) {
        int size = vTransIntfIdList.size();
        for (int i = 0; i < size; i++) {
            freeDataResponse(&responsesOfActive[i]);
        }
        FREEIF(responsesOfActive);
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] free responsesOfActive", rid, __FUNCTION__);
    }

    return;
}

void RmmDcEventHandler::requestOrSendDataCallList(const sp<RfxMclMessage>& msg, int aid) {
    int rid = m_slot_id;
    MTK_RIL_Data_Call_Response_v11* responsesOfActive = NULL;
    Vector<int> vTransIntfIdList;
    Vector<int>::iterator it;
    sp<RfxMclMessage> responseMsg;
    const int nPdnInfoSize = m_pPdnManager->getPdnTableSize();

    RFX_LOG_V(RFX_LOG_TAG, "[%d][%s] PdnTableSize=%d", rid, __FUNCTION__, nPdnInfoSize);

    if (PDN_SUCCESS != updateActiveStatusAndProfileById(aid)) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] updateActiveStatusAndProfileById failed for aid%d",
                rid, __FUNCTION__, aid);
        return;
    }

    // Reserve size of TransIntfId list.
    vTransIntfIdList.reserve(nPdnInfoSize);

    for (int i = 0; i < nPdnInfoSize; i++) {
        if ((m_pPdnManager->getPdnActiveStatus(i) == DATA_STATE_ACTIVE) &&
                (m_pPdnManager->getTransIntfId(i) != INVALID_TRANS_INTF_ID) &&
                (std::find(vTransIntfIdList.begin(), vTransIntfIdList.end(),
                m_pPdnManager->getTransIntfId(i)) == vTransIntfIdList.end())) {
            vTransIntfIdList.push_back(m_pPdnManager->getTransIntfId(i));
        }
    }

    if (vTransIntfIdList.size() > 0) {
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] active trans-interface number is %zu",
                rid, __FUNCTION__, vTransIntfIdList.size());

        responsesOfActive = (MTK_RIL_Data_Call_Response_v11*)
                calloc(1, vTransIntfIdList.size() * sizeof(MTK_RIL_Data_Call_Response_v11));

        if (responsesOfActive == NULL) {
            RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] fail to allocate responsesOfActive!",
                    rid, __FUNCTION__);
            RFX_ASSERT(false);
        }

        initDataCallResponse(responsesOfActive, vTransIntfIdList.size());
        int index = 0;
        for (it = vTransIntfIdList.begin(); it != vTransIntfIdList.end(); it++) {
            int transIntfId = *it;
            createDataResponse(transIntfId, IPV4V6, &responsesOfActive[index]);
            ++index;
        }
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] %s", rid, __FUNCTION__,
                responsesToString(responsesOfActive, vTransIntfIdList.size()).string());

        if (msg->getType() == RFX_MESSAGE_TYPE::REQUEST) {
            responseMsg = RfxMclMessage::obtainResponse(RIL_E_SUCCESS,
                    RfxDataCallResponseData(responsesOfActive, vTransIntfIdList.size()), msg);
        } else {
            responseMsg = RfxMclMessage::obtainUrc(RFX_MSG_URC_DATA_CALL_LIST_CHANGED, rid,
                    RfxDataCallResponseData(responsesOfActive, vTransIntfIdList.size()));
        }
    } else {
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] no active response", rid, __FUNCTION__);

        if (msg->getType() == RFX_MESSAGE_TYPE::REQUEST) {
            responseMsg = RfxMclMessage::obtainResponse(RIL_E_SUCCESS, RfxVoidData(), msg);
        } else {
            responseMsg = RfxMclMessage::obtainUrc(RFX_MSG_URC_DATA_CALL_LIST_CHANGED, rid,
                    RfxVoidData());
        }
    }

    responseToTelCore(responseMsg);

    if (responsesOfActive != NULL) {
        int size = vTransIntfIdList.size();
        for (int i = 0; i < size; i++) {
            freeDataResponse(&responsesOfActive[i]);
        }
        FREEIF(responsesOfActive);
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] free responsesOfActive", rid, __FUNCTION__);
    }
}

void RmmDcEventHandler::sendDataCallListResponse(const sp<RfxMclMessage>& msg, int deactivatedAid) {
    int rid = m_slot_id;
    MTK_RIL_Data_Call_Response_v11* responsesOfActive = NULL;
    Vector<int> vTransIntfIdList;
    Vector<int>::iterator it;
    sp<RfxMclMessage> responseMsg;
    const int nPdnInfoSize = m_pPdnManager->getPdnTableSize();

    RFX_LOG_V(RFX_LOG_TAG, "[%d][%s] PdnTableSize=%d", rid, __FUNCTION__, nPdnInfoSize);

    // Reserve size of TransIntfId list.
    vTransIntfIdList.reserve(nPdnInfoSize);

    for (int i = 0; i < nPdnInfoSize; i++) {
        if ((m_pPdnManager->getPdnActiveStatus(i) == DATA_STATE_ACTIVE) &&
                (m_pPdnManager->getTransIntfId(i) != INVALID_TRANS_INTF_ID) &&
                (std::find(vTransIntfIdList.begin(), vTransIntfIdList.end(),
                m_pPdnManager->getTransIntfId(i)) == vTransIntfIdList.end())) {
            vTransIntfIdList.push_back(m_pPdnManager->getTransIntfId(i));
        }
    }

    if (vTransIntfIdList.size() > 0) {
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] active trans-interface number is %zu",
                rid, __FUNCTION__, vTransIntfIdList.size());

        responsesOfActive = (MTK_RIL_Data_Call_Response_v11*)
                calloc(1, vTransIntfIdList.size() * sizeof(MTK_RIL_Data_Call_Response_v11));

        if (responsesOfActive == NULL) {
            RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] fail to allocate responsesOfActive!",
                    rid, __FUNCTION__);
            RFX_ASSERT(false);
        }

        initDataCallResponse(responsesOfActive, vTransIntfIdList.size());
        int index = 0;
        for (it = vTransIntfIdList.begin(); it != vTransIntfIdList.end(); it++) {
            int transIntfId = *it;
            createDataResponse(transIntfId, IPV4V6, &responsesOfActive[index]);

            if (deactivatedAid != INVALID_AID &&
                    notifyDeactReasonIfNeeded(deactivatedAid) &&
                    transIntfId == m_pPdnManager->getTransIntfId(deactivatedAid)) {
                responsesOfActive[index].active = DATA_STATE_INACTIVE;
                responsesOfActive[index].status = m_pPdnManager->getDeactReason(deactivatedAid);
            }

            ++index;
        }
        RFX_LOG_I(RFX_LOG_TAG, "[%d][%s] %s", rid, __FUNCTION__,
                responsesToString(responsesOfActive, vTransIntfIdList.size()).string());

        if (msg->getType() == RFX_MESSAGE_TYPE::REQUEST) {
            responseMsg = RfxMclMessage::obtainResponse(RIL_E_SUCCESS,
                    RfxDataCallResponseData(responsesOfActive, vTransIntfIdList.size()), msg);
        } else {
            responseMsg = RfxMclMessage::obtainUrc(RFX_MSG_URC_DATA_CALL_LIST_CHANGED, rid,
                    RfxDataCallResponseData(responsesOfActive, vTransIntfIdList.size()));
        }
    } else {
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] no active response", rid, __FUNCTION__);

        if (msg->getType() == RFX_MESSAGE_TYPE::REQUEST) {
            responseMsg = RfxMclMessage::obtainResponse(RIL_E_SUCCESS, RfxVoidData(), msg);
        } else {
            responseMsg = RfxMclMessage::obtainUrc(RFX_MSG_URC_DATA_CALL_LIST_CHANGED, rid,
                    RfxVoidData());
        }
    }

    responseToTelCore(responseMsg);

    if (responsesOfActive != NULL) {
        int size = vTransIntfIdList.size();
        for (int i = 0; i < size; i++) {
            freeDataResponse(&responsesOfActive[i]);
        }
        FREEIF(responsesOfActive);
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] free responsesOfActive", rid, __FUNCTION__);
    }
}

int RmmDcEventHandler::updateActiveStatusAndProfileById(int aid, bool bUpdateProfile) {
    if (aid < 0 || aid >= m_pPdnManager->getPdnTableSize()) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] illegal param", m_slot_id, __FUNCTION__);
        return PDN_FAILED;
    }
    Vector<int> *vAidList = new Vector<int>();
    vAidList->reserve(1);
    vAidList->push_back(aid);
    int ret = updateActiveStatusAndProfile(vAidList, bUpdateProfile);
    delete vAidList;
    vAidList = NULL;
    return ret;
}

int RmmDcEventHandler::updateActiveStatusAndProfile(Vector<int> *vAidList, bool bUpdateProfile) {
    sp<RfxAtResponse> p_response;
    int rid = m_slot_id;
    std::stringstream activeAidString;
    std::stringstream inactiveAidString;
    int pdnTableSize = m_pPdnManager->getPdnTableSize();
    int validIdSize = 0;
    uint8_t *pId = NULL;
    uint16_t t_resp_len;
    Vector<int>::iterator it;

    sp<RfxMipcData> mipcReq = RfxMipcData::obtainMipcData(
            MIPC_DATA_GET_MD_DATA_CALL_LIST_REQ, rid);
    sp<RfxMipcData> mipcCnf = callToMipcMsgSync(mipcReq);
    mipc_result_const_enum mipcRet = (mipc_result_const_enum) mipcCnf->getResult();
    if (mipcRet != MIPC_RESULT_SUCCESS) {
        RFX_LOG_E(RFX_LOG_TAG,
                "[%d][%s] MIPC_DATA_GET_MD_DATA_CALL_LIST_REQ return error",
                rid, __FUNCTION__);
        return PDN_FAILED;
    }

    void *actState = (void*) mipc_msg_get_val_ptr(mipcCnf->getData(),
            MIPC_DATA_GET_MD_DATA_CALL_LIST_CNF_T_CID_LIST, &t_resp_len);
    if (actState == NULL) {
        RFX_LOG_E(RFX_LOG_TAG,
                "[%d][%s] get MIPC_DATA_GET_MD_DATA_CALL_LIST_CNF_T_CID_LIST failed",
                rid, __FUNCTION__);
        return PDN_FAILED;
    }

    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] resp_len=%d, pdnTableSize=%d",
            rid, __FUNCTION__, t_resp_len, pdnTableSize);

    validIdSize = t_resp_len > pdnTableSize ? pdnTableSize : t_resp_len;

    pId = (uint8_t*) calloc(1, sizeof(uint8_t) * pdnTableSize);
    RFX_ASSERT(pId != NULL);
    memcpy(pId, actState, validIdSize);

    for (int i = 0; i < validIdSize; i ++) {
        if (pId[i] > 0) {
            // 0=inactive, 1=active/physical link down, 2=active/physical link up
            if (m_pPdnManager->getTransIntfId(i) == INVALID_TRANS_INTF_ID) {
                m_pPdnManager->updatePdnActiveStatus(i, DATA_STATE_LINKDOWN);
                RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] aid%d is linkdown", rid, __FUNCTION__, i);
            } else {
                m_pPdnManager->updatePdnActiveStatus(i, DATA_STATE_ACTIVE);
                RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] aid%d is active", rid, __FUNCTION__, i);
            }

            if (m_pPdnManager->getAid(i) == INVALID_AID) {
                m_pPdnManager->setAidAndPrimaryAid(i, i, i);
            }
            activeAidString << i << ":" << m_pPdnManager->getPrimaryAid(i) << ", ";

            if (!bUpdateProfile) {
                continue;
            }
            if (vAidList == NULL) {
                if (PDN_FAILED == updateDataCallProfile(i)) {
                    RFX_LOG_E(RFX_LOG_TAG,
                            "[%d][%s] case1, updateDataCallProfile failed for aid%d",
                            rid, __FUNCTION__, i);
                    continue;
                }
            } else {
                for (it = vAidList->begin(); it != vAidList->end(); it++) {
                    if (i != *it) {
                        continue;
                    }
                    if (PDN_FAILED == updateDataCallProfile(i)) {
                        RFX_LOG_E(RFX_LOG_TAG,
                                "[%d][%s] case2, updateDataCallProfile failed for aid%d",
                                rid, __FUNCTION__, i);
                        continue;
                    }
                    break;
                }
            }
        } else {
            // TODO: currently,this is original flow(before MIPC).
            // However, do we need clear pdninfo if it is inactive ?
            m_pPdnManager->updatePdnActiveStatus(i, DATA_STATE_INACTIVE);
            inactiveAidString << i << ":" << m_pPdnManager->getPrimaryAid(i) << ", ";
        }
    }

    if (activeAidString.str().length() > 0) {
        RFX_LOG_I(RFX_LOG_TAG, "[%d][%s] active list [aid:primaryAid] = [%s]",
                rid, __FUNCTION__, activeAidString.str().c_str());
    }
    if (inactiveAidString.str().length() > 0) {
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] inactive list [aid:primaryAid] = [%s]",
                rid, __FUNCTION__, inactiveAidString.str().c_str());
    }

    FREEIF(pId);
    return PDN_SUCCESS;
}

int RmmDcEventHandler::updateDataCallProfile(int aid) {
    if (!m_pPdnManager->validateAid(aid)) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] illegal param", m_slot_id, __FUNCTION__);
        return PDN_FAILED;
    }

    if (m_pPdnManager->isDedicateBearer(aid)) {
        updateQosInformation(aid, true);
    } else {
        sp<RfxMipcData> mipcReq = RfxMipcData::obtainMipcData(MIPC_DATA_GET_CALL_REQ, m_slot_id);
        mipcReq->addMipcTlvUint8(MIPC_DATA_GET_CALL_REQ_T_ID, (uint8_t) aid);
        sp<RfxMipcData> mipcCnf = callToMipcMsgSync(mipcReq);
        if ((mipc_result_const_enum) mipcCnf->getResult() != MIPC_RESULT_SUCCESS) {
            RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] MIPC_DATA_GET_CALL_REQ return error",
                    m_slot_id, __FUNCTION__);
            return PDN_FAILED;
        }
        decodeDataCallProfile(mipcCnf, GET_CNF);
        updateQosInformation(aid, false);
        updateTdInfo(aid);
    }
    return PDN_SUCCESS;
}

void RmmDcEventHandler::initDataCallResponse(MTK_RIL_Data_Call_Response_v11* responses, int length) {
    for (int i = 0; i < length; i++) {
        memset(&responses[i], 0, sizeof(MTK_RIL_Data_Call_Response_v11));
        responses[i].status = PDP_FAIL_ERROR_UNSPECIFIED;
        responses[i].active = DATA_STATE_INACTIVE;
        responses[i].cid = INVALID_AID;
        responses[i].suggestedRetryTime = -1;
    }
}

void RmmDcEventHandler::createDataResponse(int transIntfId, int protocol,
        MTK_RIL_Data_Call_Response_v11* response) {
    int rid = m_slot_id;
    char addressV4[MAX_IPV4_ADDRESS_LENGTH] = {0};
    char *addressV6[MAX_NUM_IPV6_ADDRESS_NUMBER] = {0};
    char dnsV4[MAX_NUM_DNS_ADDRESS_NUMBER][MAX_IPV4_ADDRESS_LENGTH] = {{0}};
    char dnsV6[MAX_NUM_DNS_ADDRESS_NUMBER][MAX_IPV6_ADDRESS_LENGTH] = {{0}};
    char pcscf[MAX_PCSCF_NUMBER][MAX_IPV6_ADDRESS_LENGTH] = {{0}};
    int addressV4Length = 0;
    int addressV6Length = 0;
    int nAddressLength = 0;
    int v4DnsLength = 0;
    int v6DnsLength = 0;
    int nDnsesLen = 0;
    int pcscfLength = 0;
    PdnInfo *pdnInfo = NULL;
    PdnInfo pdn_info;
    memset(&pdn_info, 0, sizeof(pdn_info));
    const int nPdnInfoSize = m_pPdnManager->getPdnTableSize();
    int ddctBearCount = 0;

    if (response == NULL) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] response is null, return!",
                rid, __FUNCTION__);
        return;
    }

    for (int i = 0; i < nPdnInfoSize; i++) {
        pdn_info = m_pPdnManager->getPdnInfo(i);
        int interfaceId = getInterfaceIdByTransIntfId(transIntfId);
        if ((interfaceId != INVALID_INTERFACE_ID) &&
                (pdn_info.transIntfId == transIntfId) &&
                !pdn_info.isDedicateBearer &&
                (pdn_info.active == DATA_STATE_ACTIVE)) {
            RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] copy pdn_info[%d] to data response for transIntfId=%d",
                    rid, __FUNCTION__, i, transIntfId);

            pdnInfo = &pdn_info;
            // There is aid bind to the interface of the response, so set to active
            response->active = pdnInfo->active;
            asprintf(&response->ifname, "ccmni%d", interfaceId);

            if (strlen(pdnInfo->addressV4) > 0
                    && strlen(pdnInfo->addressV4) < MAX_IPV4_ADDRESS_LENGTH
                    && (protocol == IPV4 || protocol == IPV4V6)) {
                strncpy(addressV4, pdnInfo->addressV4, MAX_IPV4_ADDRESS_LENGTH-1);
                addressV4Length += strlen(addressV4);
            }

            for (int j = 0; j < MAX_NUM_IPV6_ADDRESS_NUMBER; j++) {
                if (strlen(pdnInfo->addressV6Info[j].addressV6) > 0
                        && strlen(pdnInfo->addressV6Info[j].addressV6) < MAX_IPV6_ADDRESS_LENGTH
                        && (protocol == IPV6 || protocol == IPV4V6)) {
                    if (pdnInfo->addressV6Info[j].prefixLength > 0) {
                        asprintf(&addressV6[j], "%s/%d&%d&%ld&%ld",
                                pdnInfo->addressV6Info[j].addressV6,
                                pdnInfo->addressV6Info[j].prefixLength,
                                pdnInfo->addressV6Info[j].flags,
                                pdnInfo->addressV6Info[j].deprecationTime,
                                pdnInfo->addressV6Info[j].expirationTime);
                    } else {
                        asprintf(&addressV6[j], "%s&%d&%ld&%ld",
                                pdnInfo->addressV6Info[j].addressV6,
                                pdnInfo->addressV6Info[j].flags,
                                pdnInfo->addressV6Info[j].deprecationTime,
                                pdnInfo->addressV6Info[j].expirationTime);
                    }
                    if (addressV6[j] == NULL) {
                        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] fail to allocate addressV6!",
                                rid, __FUNCTION__);
                    } else {
                        addressV6Length += strlen(addressV6[j]);
                    }
                    if (j != 0 || addressV4Length != 0) {
                        ++addressV6Length;  // add one space
                    }
                }
            }

            for (int j = 0; j < MAX_NUM_DNS_ADDRESS_NUMBER; j++) {
                // If there is no IP address but with corresponding
                // DNS server, it may result in TCP/IP break down due
                // to DNS server algorithm from N, so need check if
                // have IP address when report DNS
                if (strlen(pdnInfo->dnsV4[j]) > 0
                        && strlen(pdnInfo->dnsV4[j]) < MAX_IPV4_ADDRESS_LENGTH
                        && addressV4Length > 0) {
                    strncpy(dnsV4[j], pdnInfo->dnsV4[j], MAX_IPV4_ADDRESS_LENGTH-1);
                    v4DnsLength += strlen(dnsV4[j]);
                    if (j != 0 || v6DnsLength != 0)
                        ++v4DnsLength;  // add one space
                    RFX_LOG_D(RFX_LOG_TAG,
                            "[%d][%s], pdnInfo->dnsV4[%d]=%s, dnsV4[%d]=%s",
                            rid, __FUNCTION__, j, pdnInfo->dnsV4[j], j, dnsV4[j]);
                }
                if (strlen(pdnInfo->dnsV6[j]) > 0
                        && strlen(pdnInfo->dnsV6[j]) < MAX_IPV6_ADDRESS_LENGTH
                        && addressV6Length > 0) {
                    strncpy(dnsV6[j], pdnInfo->dnsV6[j], MAX_IPV6_ADDRESS_LENGTH-1);
                    v6DnsLength += strlen(dnsV6[j]);
                    if (j != 0 || v4DnsLength != 0)
                        ++v6DnsLength;  // add one space
                    RFX_LOG_D(RFX_LOG_TAG,
                            "[%d][%s], pdnInfo->dnsV6[%d]=%s, dnsV6[%d]=%s",
                            rid, __FUNCTION__, j, pdnInfo->dnsV6[j], j, dnsV6[j]);
                }
            }

            for (int j = 0; j < MAX_PCSCF_NUMBER; j++) {
                if (strlen(pdnInfo->pcscf[j]) > 0
                        && strlen(pdnInfo->pcscf[j]) < MAX_IPV6_ADDRESS_LENGTH) {
                    strncpy(pcscf[j], pdnInfo->pcscf[j], MAX_IPV6_ADDRESS_LENGTH-1);
                    pcscfLength += strlen(pcscf[j]);
                    if (j != 0)
                        ++pcscfLength;  // add one space
                }
            }

            // mtu
            RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] mtu=%ld, mtuV6=%d, accessNetwork=%d",
                    rid, __FUNCTION__, pdnInfo->mtuV4, pdnInfo->mtuV6, pdnInfo->accessNetwork);
            response->mtu = pdnInfo->mtuV4;
            response->mtuV6 = pdnInfo->mtuV6;

            // access network
            response->accessNetwork = pdnInfo->accessNetwork;

            // default Qos
            if (pdnInfo->defaultQos != NULL && response->accessNetwork == E_UTRAN) {
                response->defaultQos = (RIL_Qos*)calloc(1, sizeof(RIL_Qos));
                RFX_ASSERT(response->defaultQos != NULL);
                response->defaultQos->eps.qci = pdnInfo->defaultQos->eps.qci;
                response->defaultQos->eps.uplink.maxBitrateKbps
                        = pdnInfo->defaultQos->eps.uplink.maxBitrateKbps;
                response->defaultQos->eps.uplink.guaranteedBitrateKbps
                        = pdnInfo->defaultQos->eps.uplink.guaranteedBitrateKbps;
                response->defaultQos->eps.downlink.maxBitrateKbps
                        = pdnInfo->defaultQos->eps.downlink.maxBitrateKbps;
                response->defaultQos->eps.downlink.guaranteedBitrateKbps
                        = pdnInfo->defaultQos->eps.downlink.guaranteedBitrateKbps;
            } else if (pdnInfo->defaultQos != NULL && response->accessNetwork == NG_RAN) {
                response->defaultQos = (RIL_Qos*)calloc(1, sizeof(RIL_Qos));
                RFX_ASSERT(response->defaultQos != NULL);
                response->defaultQos->nr.fiveQi = pdnInfo->defaultQos->nr.fiveQi;
                response->defaultQos->nr.uplink.maxBitrateKbps
                        = pdnInfo->defaultQos->nr.uplink.maxBitrateKbps;
                response->defaultQos->nr.uplink.guaranteedBitrateKbps
                        = pdnInfo->defaultQos->nr.uplink.guaranteedBitrateKbps;
                response->defaultQos->nr.downlink.maxBitrateKbps
                        = pdnInfo->defaultQos->nr.downlink.maxBitrateKbps;
                response->defaultQos->nr.downlink.guaranteedBitrateKbps
                        = pdnInfo->defaultQos->nr.downlink.guaranteedBitrateKbps;
                response->defaultQos->nr.qfi = pdnInfo->defaultQos->nr.qfi;
                response->defaultQos->nr.averagingWindowMs
                        = pdnInfo->defaultQos->nr.averagingWindowMs;
            }

            // QosSessions
            // collect dedicated bearers of this transinterface
            for (int j = 0; j < m_pPdnManager->getPdnTableSize(); j++) {
                if (isValidDedicateBearer(i, j)) {
                    ddctBearCount++;
                }
            }
            RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] dedicate bearer count:%d",
                    rid, __FUNCTION__, ddctBearCount);
            response->qosSessionCount = ddctBearCount;

            if (ddctBearCount > 0) {
                response->qosSessions = (RIL_QosSession*)calloc(1,
                        sizeof(RIL_QosSession) * ddctBearCount);
                RFX_ASSERT(response->qosSessions != NULL);
            }

            PdnInfo tmpPdnInfo;
            for (int j = 0, n = 0; j < m_pPdnManager->getPdnTableSize() && n < ddctBearCount; j++) {
                tmpPdnInfo = m_pPdnManager->getPdnInfo(j);
                if (!isValidDedicateBearer(i, j)){
                    continue;
                }
                RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] dedicate bearer, index:%d, id:%d",
                        rid, __FUNCTION__, n, j);

                response->qosSessions[n].qosSessionId = tmpPdnInfo.qosSession->qosSessionId;
                memcpy(&(response->qosSessions[n].qos),
                        &(tmpPdnInfo.qosSession->qos), sizeof(RIL_Qos));

                response->qosSessions[n].qosFilterCount = tmpPdnInfo.qosSession->qosFilterCount;
                response->qosSessions[n].qosFilters = (RIL_QosFilter*)calloc(1,
                        sizeof(RIL_QosFilter) * response->qosSessions[n].qosFilterCount);
                RFX_ASSERT(response->qosSessions[n].qosFilters != NULL);
                for (int k = 0; k < response->qosSessions[n].qosFilterCount; k++) {
                    const RIL_QosFilter* tmpFilter = &tmpPdnInfo.qosSession->qosFilters[k];
                    int addLen = 0;
                    if (tmpFilter->localAddresses != NULL) {
                        addLen = strlen(tmpFilter->localAddresses);
                        response->qosSessions[n].qosFilters[k].localAddresses =
                                (char*) calloc(1, sizeof(char)*(addLen + 1));
                        RFX_ASSERT(response->qosSessions[n].qosFilters[k].localAddresses != NULL);
                        memcpy(response->qosSessions[n].qosFilters[k].localAddresses,
                                tmpFilter->localAddresses, addLen);
                    }

                    if (tmpFilter->remoteAddresses != NULL) {
                        addLen = strlen(tmpFilter->remoteAddresses);
                        response->qosSessions[n].qosFilters[k].remoteAddresses =
                                (char*) calloc(1, sizeof(char)*(addLen + 1));
                        RFX_ASSERT(response->qosSessions[n].qosFilters[k].remoteAddresses != NULL);
                        memcpy(response->qosSessions[n].qosFilters[k].remoteAddresses,
                                tmpFilter->remoteAddresses, addLen);
                    }

                    response->qosSessions[n].qosFilters[k].localPort.start
                            = tmpFilter->localPort.start;
                    response->qosSessions[n].qosFilters[k].localPort.end
                            = tmpFilter->localPort.end;
                    response->qosSessions[n].qosFilters[k].remotePort.start
                            = tmpFilter->remotePort.start;
                    response->qosSessions[n].qosFilters[k].remotePort.end
                            = tmpFilter->remotePort.end;
                    response->qosSessions[n].qosFilters[k].protocol
                            = tmpFilter->protocol;
                    response->qosSessions[n].qosFilters[k].typeOfService
                            = tmpFilter->typeOfService;
                    response->qosSessions[n].qosFilters[k].ipv6FlowLabel
                            = tmpFilter->ipv6FlowLabel;
                    response->qosSessions[n].qosFilters[k].ipSecSpi
                            = tmpFilter->ipSecSpi;
                    response->qosSessions[n].qosFilters[k].direction
                            = tmpFilter->direction;
                    response->qosSessions[n].qosFilters[k].precedence
                            = tmpFilter->precedence;
                }
                n++;
            }

            response->handoverFailureMode = pdnInfo->handoverFailureMode;
            // Modem solution for WLAN handover so pduSessionId is no need.
            response->pduSessionId = 0;
            // slice info
            if (pdnInfo->optionalSliceInfo != NULL) {
                response->optionalSliceInfo = (RIL_SliceInfo*)calloc(1, sizeof(RIL_SliceInfo));
                RFX_ASSERT(response->optionalSliceInfo != NULL);
                memcpy(response->optionalSliceInfo, pdnInfo->optionalSliceInfo,
                        sizeof(RIL_SliceInfo));
            }

            // traffic descriptors
            response->tdCount = pdnInfo->tdCount;
            RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] tdCount=%d",
                    rid, __FUNCTION__, response->tdCount);
            if (response->tdCount > 0 && pdnInfo->TDs != NULL) {
                response->TDs = (RIL_TrafficDescriptor*)calloc(1,
                        sizeof(RIL_TrafficDescriptor) * response->tdCount);
                RFX_ASSERT(response->TDs != NULL);
            }
            for (int j = 0; j < response->tdCount; j++) {
                if (pdnInfo->TDs == NULL || response->TDs == NULL) {
                    // should not happen
                    RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] pdnInfo->TDs or response->TDs is NULL",
                            rid, __FUNCTION__);
                    break;
                }
                if (pdnInfo->TDs[j].dnn != NULL && strlen(pdnInfo->TDs[j].dnn) > 0) {
                    int len = strlen(pdnInfo->TDs[j].dnn);
                    response->TDs[j].dnn = (char*)calloc(1, sizeof(char) * (len + 1));
                    RFX_ASSERT(response->TDs[j].dnn != NULL);
                    memcpy(response->TDs[j].dnn, pdnInfo->TDs[j].dnn, len);
                }
                response->TDs[j].osAppIdLen = pdnInfo->TDs[j].osAppIdLen;
                if (response->TDs[j].osAppIdLen > 0) {
                    response->TDs[j].osAppId = (uint8_t*)calloc(1,
                            sizeof(uint8_t) * (response->TDs[j].osAppIdLen + 1));
                    RFX_ASSERT(response->TDs[j].osAppId != NULL);
                    memcpy(response->TDs[j].osAppId, pdnInfo->TDs[j].osAppId,
                            response->TDs[j].osAppIdLen);
                    RFX_LOG_D(RFX_LOG_TAG,
                        "[%d][%s] OS APP ID: %02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x-%d-%s",
                        rid, __FUNCTION__,
                        response->TDs[j].osAppId[0], response->TDs[j].osAppId[1], response->TDs[j].osAppId[2], response->TDs[j].osAppId[3],
                        response->TDs[j].osAppId[4], response->TDs[j].osAppId[5], response->TDs[j].osAppId[6], response->TDs[j].osAppId[7],
                        response->TDs[j].osAppId[8], response->TDs[j].osAppId[9], response->TDs[j].osAppId[10], response->TDs[j].osAppId[11],
                        response->TDs[j].osAppId[12], response->TDs[j].osAppId[13], response->TDs[j].osAppId[14], response->TDs[j].osAppId[15],
                        response->TDs[j].osAppId[APP_ID_LEN_INDEX],
                        (char*)(&response->TDs[j].osAppId[APP_ID_INDEX]));
                }
            }
        } else if (pdn_info.transIntfId == transIntfId) {
            RFX_LOG_I(RFX_LOG_TAG, "[%d][%s] not need to create pdn_info[%d] for transIntfId=%d"
                    " because pdn_info{isDedicateBearer=%d, active=%d} is not satisfied",
                    rid, __FUNCTION__, i, transIntfId, pdn_info.isDedicateBearer,
                    pdn_info.active);
        }
    }

    response->status = PDP_FAIL_NONE;
    response->cid = transIntfId;

    nAddressLength = addressV4Length + addressV6Length;
    response->addresses = (char*)calloc(1, (nAddressLength * sizeof(char)) + 1);
    RFX_ASSERT(response->addresses != NULL);
    response->gateways = (char*)calloc(1, (nAddressLength * sizeof(char)) + 1);
    RFX_ASSERT(response->gateways != NULL);

    if (addressV4Length > 0) {
        strncat(response->addresses + strlen(response->addresses), addressV4,
            nAddressLength - strlen(response->addresses));
        strncat(response->gateways + strlen(response->gateways), addressV4,
            nAddressLength - strlen(response->gateways));
    }
    for (int i = 0; i < MAX_NUM_IPV6_ADDRESS_NUMBER; i++) {
        if (addressV6Length > 0 && addressV6[i] != NULL && strlen(addressV6[i]) > 0) {
            int currentLength = strlen(response->addresses);
            if (currentLength > 0) {
                strncat(response->addresses + currentLength, " ", nAddressLength - currentLength);
            }
            strncat(response->addresses + strlen(response->addresses), addressV6[i],
                    nAddressLength - strlen(response->addresses));

            currentLength = strlen(response->gateways);
            if (currentLength > 0) {
                strncat(response->gateways + currentLength, " ", nAddressLength - currentLength);
            }

            strncat(response->gateways + strlen(response->gateways), UNSPECIFIED_IPV6_GATEWAY,
                    nAddressLength - strlen(response->gateways));
        }
    }

    if (addressV4Length > 0 && addressV6Length > 0) {
        asprintf(&response->type, SETUP_DATA_PROTOCOL_IPV4V6);
    } else if (addressV6Length > 0) {
        asprintf(&response->type, SETUP_DATA_PROTOCOL_IPV6);
    } else {
        asprintf(&response->type, SETUP_DATA_PROTOCOL_IP);
    }

    nDnsesLen = v4DnsLength + v6DnsLength;
    response->dnses = (char*)calloc(1, (nDnsesLen * sizeof(char)) + 1);
    RFX_ASSERT(response->dnses != NULL);

    for (int i = 0; i < MAX_NUM_DNS_ADDRESS_NUMBER; i++) {
        if (v6DnsLength > 0 && strlen(dnsV6[i]) > 0) {
            int currentLength = strlen(response->dnses);
            if (currentLength > 0) {
                strncat(response->dnses + currentLength, " ", nDnsesLen - currentLength);
            }
            strncat(response->dnses + strlen(response->dnses), dnsV6[i],
                    nDnsesLen - strlen(response->dnses));
        }
    }
    for (int i = 0; i < MAX_NUM_DNS_ADDRESS_NUMBER; i++) {
        if (v4DnsLength > 0 && strlen(dnsV4[i]) > 0) {
            int currentLength = strlen(response->dnses);
            if (currentLength > 0) {
                strncat(response->dnses + currentLength, " ", nDnsesLen - currentLength);
            }
            strncat(response->dnses + strlen(response->dnses), dnsV4[i],
                    nDnsesLen - strlen(response->dnses));
        }
    }

    response->pcscf= (char*)calloc(1, pcscfLength * sizeof(char) + 1);
    RFX_ASSERT(response->pcscf != NULL);
    for (int i = 0; i < MAX_PCSCF_NUMBER; i++) {
        if (pcscfLength > 0 && strlen(pcscf[i]) > 0) {
            int currentLength = strlen(response->pcscf);
            if (currentLength > 0) {
                strncat(response->pcscf + currentLength, " ", pcscfLength - currentLength);
                currentLength = strlen(response->pcscf);
            }
            strncat(response->pcscf + currentLength, pcscf[i], pcscfLength - currentLength);
        }
    }

    for (int i = 0; i < MAX_NUM_IPV6_ADDRESS_NUMBER; i++) {
        FREEIF(addressV6[i]);
    }
}

/*
 * return: true for sending data call response, false for not.
 */
bool RmmDcEventHandler::createAndLaunchDataResponse(int result, int aid) {
    if (aid < 0 || aid >= m_pPdnManager->getPdnTableSize()) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] invalid aid:%d",
                m_slot_id, __FUNCTION__, aid);
        return false;
    }

    int reqMsgIndex = m_pPdnManager->getPrimaryAid(aid);
    sp<RfxMclMessage> reqMsg = m_mapAidReqmsg[reqMsgIndex];
    if (reqMsg == NULL) {
        RFX_LOG_W(RFX_LOG_TAG, "[%d][%s] no reqMsg, aid:%d, p_id:%d",
                m_slot_id, __FUNCTION__, aid, reqMsgIndex);
        return false;
    }

    int num = 1;
    MTK_RIL_Data_Call_Response_v11* response =
            (MTK_RIL_Data_Call_Response_v11*)calloc(1,
            sizeof(MTK_RIL_Data_Call_Response_v11));
    RFX_ASSERT(response != NULL);
    initDataCallResponse(response, num);

    if (result == MIPC_RESULT_SUCCESS) {
        createDataResponse(m_pPdnManager->getTransIntfId(aid), IPV4V6, response);
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] %s", m_slot_id, __FUNCTION__,
                responsesToString(response, num).string());

        sendEvent(RFX_MSG_EVENT_REQ_DATA_CONTEXT_IDS, RfxVoidData(),
                RIL_CMD_PROXY_5, m_slot_id, -1, -1, 100e6);
        setPdnInfoProperty();

        sp<RfxMclMessage> responseMsg = RfxMclMessage::obtainResponse(RIL_E_SUCCESS,
                RfxDataCallResponseData(response, num), reqMsg);
        responseToTelCore(responseMsg);

        int profileId = m_pPdnManager->getProfileId(aid);
        if (profileId == RIL_DATA_PROFILE_VENDOR_MMS && response->status == PDP_FAIL_NONE) {
            int data[2];
            data[0] = RmmDcUtility::getApnTypeId(profileId);
            data[1] = m_pPdnManager->getRat(aid);
            sendEvent(RFX_MSG_EVENT_SEND_QUALIFIED_NETWORK_TYPES_CHANGED,
                    RfxIntsData(data, 2), RIL_CMD_PROXY_5, m_slot_id,
                    -1, -1, 500e6);
        }
    } else {
        char* apnName = m_pPdnManager->getApnName(aid);
        if (apnName != NULL && strlen(apnName) != 0) {
            response->suggestedRetryTime = getModemSuggestedRetryTime(apnName);
        }
        sp<RfxMclMessage> responseMsg = RfxMclMessage::obtainResponse(
                RIL_E_SUCCESS, RfxDataCallResponseData(response, num), reqMsg);
        responseToTelCore(responseMsg);
    }

    m_mapAidReqmsg.erase(reqMsgIndex);
    freeDataResponse(response);
    FREEIF(response);
    return true;
}

String8 RmmDcEventHandler::responsesToString(MTK_RIL_Data_Call_Response_v11* responses, int num) {
    int rid = m_slot_id;
    String8 cmd("");

    if (num == 0 || responses == NULL) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] the number of data call responses is %d "
                "(if number is not 0, that means data call responses is null)",
                rid, __FUNCTION__, num);
        return String8::format("");
    }

    cmd.append(String8::format("DataCallResponse <-"));

    for (int i = 0; i < num; i++) {
        cmd.append(String8::format(" {status=%d, suggestedRetryTime=%d, transIntfId=%d, active=%d,"
                " type=%s, ifname=%s, addresses=%s, dnses=%s, gateways=%s, pcscf=%s, mtu=%d}",
                (&responses[i])->status,
                (&responses[i])->suggestedRetryTime,
                (&responses[i])->cid,
                (&responses[i])->active,
                (&responses[i])->type,
                (&responses[i])->ifname,
                mIsUserBuild ? "xxx" : (&responses[i])->addresses,
                mIsUserBuild ? "xxx" : (&responses[i])->dnses,
                mIsUserBuild ? "xxx" : (&responses[i])->gateways,
                mIsUserBuild ? "xxx" : (&responses[i])->pcscf,
                (&responses[i])->mtu));
    }
    return cmd;
}

void RmmDcEventHandler::freeDataResponse(MTK_RIL_Data_Call_Response_v11* response) {
    if (response->ifname != NULL) {
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] type=%s, ifname=%s, addresses=%s, dnses=%s, gateways=%s, pcscf=%s",
                m_slot_id,
                __FUNCTION__,
                response->type,
                response->ifname,
                mIsUserBuild ? "xxx" : response->addresses,
                mIsUserBuild ? "xxx" : response->dnses,
                mIsUserBuild ? "xxx" : response->gateways,
                response->pcscf);
    }

    FREEIF(response->type);
    FREEIF(response->ifname);
    FREEIF(response->addresses);
    FREEIF(response->gateways);
    FREEIF(response->dnses);
    FREEIF(response->pcscf);
    FREEIF(response->defaultQos);
    FREEIF(response->optionalSliceInfo);

    if (response->qosSessionCount > 0) {
        for (int i = 0; i < response->qosSessionCount; i++) {
            if (response->qosSessions[i].qosFilterCount > 0) {
                FREEIF(response->qosSessions[i].qosFilters);
            }
        }
        FREEIF(response->qosSessions);
    }

    if (response->tdCount > 0) {
        for (int i = 0; i < response->tdCount; i++) {
            FREEIF(response->TDs[i].dnn);
            FREEIF(response->TDs[i].osAppId);
        }
        FREEIF(response->TDs);
    }
}

int RmmDcEventHandler::convertIpv6Address(char* output, char* input, int isLinkLocal) {
    // input : 32.1.13.184.0.0.0.3.61.48.97.182.50.254.113.251
    // output : 2001:0DB8:0000:0003:3D30:61B6:32FE:71FB
    int rid = m_slot_id;
    char *p = NULL;
    char *address = NULL;
    int value = 0;
    int len = 0;
    int count = 8;
    char tmpOutput[MAX_IPV6_ADDRESS_LENGTH] = {0};
    int n = 0;
    char *saveptr = NULL;

    if (output == NULL || input == NULL || strlen(input) == 0) {
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] output or input is NULL", rid, __FUNCTION__);
        return -1;
    }

    if (isLinkLocal == 1) {
        strncpy(output, IPV6_PREFIX, MAX_IPV6_ADDRESS_LENGTH - 1);
    } else {
        strncpy(output, NULL_ADDR, MAX_IPV6_ADDRESS_LENGTH - 1);
    }

    address = strsep(&input, "/");
    p = strtok_r(address, ".", &saveptr);

    //Skip the 64 bit of this PDP address if this pdp adress is a local link address
    if (isLinkLocal == 1) {
        while (count && p) {
            p = strtok_r(NULL, ".", &saveptr);
            count--;
        }
    }

    while (p) {
        memset(tmpOutput, 0, MAX_IPV6_ADDRESS_LENGTH);
        value = atoi(p);
        n = snprintf(tmpOutput, MAX_IPV6_ADDRESS_LENGTH, "%02X", value);
        if (n < 0) {
            RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] snprintf errorl", rid, __FUNCTION__);
            return -1;
        }
        strncat(output + strlen(output), tmpOutput, MAX_IPV6_ADDRESS_LENGTH-strlen(output)-1);
        p = strtok_r(NULL, ".", &saveptr);
        if (p == NULL) {
            RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] The format of IP address is illegal", rid, __FUNCTION__);
            return -1;
        }
        memset(tmpOutput, 0, MAX_IPV6_ADDRESS_LENGTH);
        value = atoi(p);
        n = snprintf(tmpOutput, MAX_IPV6_ADDRESS_LENGTH, "%02X:", value);
        if (n < 0) {
            RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] snprintf errorl", rid, __FUNCTION__);
            return -1;
        }
        strncat(output + strlen(output), tmpOutput, MAX_IPV6_ADDRESS_LENGTH-strlen(output)-1);
        p = strtok_r(NULL, ".", &saveptr);
    }

    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] before convertIpv6Address: %s", rid, __FUNCTION__,
            mIsUserBuild ? "xxx" : output);
    len = strlen(output);
    if (len >= 1) output[len - 1] = '\0';

    if (input != NULL) {
        memset(tmpOutput, 0, MAX_IPV6_ADDRESS_LENGTH);
        n = snprintf(tmpOutput, MAX_IPV6_ADDRESS_LENGTH, "/%s", input);
        if (n < 0) {
            RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] snprintf errorl", rid, __FUNCTION__);
            return -1;
        }
        strncat(output + strlen(output), tmpOutput, MAX_IPV6_ADDRESS_LENGTH-strlen(output)-1);
    }

    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] convertIpv6Address: %s", rid, __FUNCTION__,
            mIsUserBuild ? "xxx" : output);

    return 0;
}

bool RmmDcEventHandler::isIpv6Global(char *ipv6Addr) {
    if (ipv6Addr == NULL) {
        return false;
    }
    int rid = m_slot_id;
    char *address = NULL;
    String8 cmd("");

    address = strsep(&ipv6Addr, "/");
    cmd.append(String8::format("{IPv6 address:%s, IPv6 prefix length:%s}", address, ipv6Addr));

    if (address != NULL) {
        struct sockaddr_in6 sa;
        int ret = 0;

        if (strncasecmp("FE80", address, strlen("FE80")) == 0) {
            RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] not global -> %s", rid, __FUNCTION__, cmd.string());
            return false;
        }

        // ret: -1, error occurs, ret: 0, invalid address, ret: 1, success;
        ret = inet_pton(AF_INET6, address, &(sa.sin6_addr));
        if (ret <= 0) {
            RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] inet_pton ret: %d -> %s",
                    rid, __FUNCTION__, ret, cmd.string());
            return false;
        }

        if (IN6_IS_ADDR_MULTICAST(&sa.sin6_addr)) {
            if (IN6_IS_ADDR_MC_GLOBAL(&sa.sin6_addr)) {
                RFX_LOG_V(RFX_LOG_TAG, "[%d][%s] global -> %s", rid, __FUNCTION__, cmd.string());
                return true;
            } else {
                RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] not global -> %s", rid, __FUNCTION__, cmd.string());
            }
        } else {
            if (IN6_IS_ADDR_LINKLOCAL(&sa.sin6_addr)) {
                RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] link-local -> %s", rid, __FUNCTION__, cmd.string());
            } else if (IN6_IS_ADDR_SITELOCAL(&sa.sin6_addr)) {
                RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] site-local -> %s", rid, __FUNCTION__, cmd.string());
            } else if (IN6_IS_ADDR_V4MAPPED(&sa.sin6_addr)) {
                RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] v4mapped -> %s", rid, __FUNCTION__, cmd.string());
            } else if (IN6_IS_ADDR_V4COMPAT(&sa.sin6_addr)) {
                RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] v4compat -> %s", rid, __FUNCTION__, cmd.string());
            } else if (IN6_IS_ADDR_LOOPBACK(&sa.sin6_addr)) {
                RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] host -> %s", rid, __FUNCTION__, cmd.string());
            } else if (IN6_IS_ADDR_UNSPECIFIED(&sa.sin6_addr)) {
                RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] unspecified -> %s", rid, __FUNCTION__, cmd.string());
            } else if (_IN6_IS_ULA(&sa.sin6_addr)) {
                RFX_LOG_V(RFX_LOG_TAG, "[%d][%s] take uni-local as global -> %s",
                        rid, __FUNCTION__, cmd.string());
                return true;
            } else {
                RFX_LOG_V(RFX_LOG_TAG, "[%d][%s] global -> %s", rid, __FUNCTION__,
                        mIsUserBuild ? "xxx" : cmd.string());
                return true;
            }
        }
    } else {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] input ipv6 address is null!!", rid, __FUNCTION__);
    }
    return false;
}

bool RmmDcEventHandler::isDataAllowed(const char* pReqApn) {
    int bearer_bitmask = 0;
    bool bSupportWifiBearer = false;
    // 0 - Not registered
    // 1 - Registered
    int nWfcState = getMclStatusManager(m_slot_id)->getIntValue(RFX_STATUS_KEY_WFC_STATE, 0);
    // 0 - Not registered
    // 1 - Registered, home network
    // 2 - Not registered, but MT is currently searching a new operator to register
    // 3 - Registration denied
    // 4 - Unknown
    // 5 - Registered, roaming
    int nPsState = getMclStatusManager(m_slot_id)->getIntValue(RFX_STATUS_KEY_CELLULAR_PS_STATE, 0);
    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] nWfcState = %d, nPsState = %d, roaming data = %d",
            m_slot_id, __FUNCTION__, nWfcState, nPsState, s_dataSetting[m_slot_id][ROAMING_DATA]);

    if (1 == nWfcState) {
        for (int i = 0; i < s_nLastReqNum[m_slot_id]; i++) {
            if (0 == strcmp(pReqApn, s_LastApnTable[m_slot_id][i].apn)) {
                bearer_bitmask = s_LastApnTable[m_slot_id][i].bearerBitmask;
                RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] bearer_bitmask = %d",
                        m_slot_id, __FUNCTION__, bearer_bitmask);
                if (0 == bearer_bitmask
                        ||((bearer_bitmask & (1 << (RADIO_TECH_IWLAN - 1))) != 0)) {
                    bSupportWifiBearer = true;
                }
                break;
            }
        }
        if (!bSupportWifiBearer && 5 == nPsState && 0 == s_dataSetting[m_slot_id][ROAMING_DATA]) {
            RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] the PS state is roaming but data roaming is off",
                    m_slot_id, __FUNCTION__);
            return false;
        }
    }
    return true;
}

int RmmDcEventHandler::getInterfaceIdByTransIntfId(int transIntfId) {
    if (0 <= transIntfId) {
        return transIntfId % TRANSACTION_ID_OFFSET;
    }
    return INVALID_INTERFACE_ID;
}

void RmmDcEventHandler::requestClearAllPdnInfo(const sp<RfxMclMessage>& msg) {
    RFX_UNUSED(msg);
    RFX_LOG_I(RFX_LOG_TAG, "[%d][%s]", m_slot_id, __FUNCTION__);
    RFX_ASSERT(m_pPdnManager != NULL);
    m_pPdnManager->clearAllPdnInfo();
}

void RmmDcEventHandler::notifyPcoValue(int value, char* apn) {
    if (!isPcoStateUrcCustomized()) return;

    char *pcoData = NULL;
    asprintf(&pcoData, "[PCOVALUE]%d,%s", value, apn);
    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] pcovalue : %s", m_slot_id, __FUNCTION__, pcoData);
    sp<RfxMclMessage> urc = RfxMclMessage::obtainUrc(RFX_MSG_UNSOL_OEM_HOOK_RAW, m_slot_id,
            RfxRawData(pcoData, strlen(pcoData)));
    responseToTelCore(urc);
    FREEIF(pcoData);
}

void RmmDcEventHandler::handlePcoInfo(const sp<RfxMclMessage>& msg) {
    char simMccMnc[MAX_LENGTH_MCCMNC] = {0};
    getMccmnc(simMccMnc);
    if (!RmmDcUtility::isPcoMccMnc(simMccMnc)) {
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] query PCO return: [%s] not OP12 SIM",
                m_slot_id, __FUNCTION__, simMccMnc);
        return;
    }

    MipcPcoInfo *pcoInfo = (MipcPcoInfo *)msg->getData()->getData();
    for (int i = 0; i < pcoInfo->pcoCount; i++) {
        sp<RfxMclMessage> urcMsg = NULL;
        std::string pcoContent(pcoInfo->pcoList[i].content[0] ? pcoInfo->pcoList[i].content : "");
        if (pcoContent.size() <= 0) {
            RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] query PCO return: content's length is 0",
                    m_slot_id, __FUNCTION__);
            continue;
        }

        int nPcoValue = -1;
        char strApnName[MAX_APN_NAME_LENGTH] = {0};
        std::string pcoValue;
        int delimiter = pcoContent.find(":");
        if (delimiter < 0) {
            pcoValue = pcoContent;
        } else {
            pcoValue = pcoContent.substr(delimiter+1, std::string::npos);
        }
        nPcoValue = atoi(pcoValue.c_str());

        // ia apn pco
        if (pcoInfo->apn[0] != 0) {
            RIL_PCO_Data_attached pcoDataIa;
            pcoDataIa.cid = m_pPdnManager->getTransIntfId(pcoInfo->cid);
            pcoDataIa.apn_name = pcoInfo->apn;
            pcoDataIa.bearer_proto = (char *)RmmDcUtility::getProtocolName(pcoInfo->pdpType);
            pcoDataIa.pco_id = std::stoi(std::string(pcoInfo->pcoList[i].ie), NULL, 16);
            pcoDataIa.contents_length = 1;
            pcoDataIa.contents = (char *)pcoValue.c_str();
            RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] PCO cid %d, apn %s, proto %s, pco_id %d, contents %s",
                    m_slot_id, __FUNCTION__, pcoDataIa.cid, pcoDataIa.apn_name,
                    pcoDataIa.bearer_proto, pcoDataIa.pco_id, pcoDataIa.contents);

            if (pcoDataIa.apn_name != NULL) {
                strncpy(strApnName, pcoDataIa.apn_name, MAX_APN_NAME_LENGTH - 1);
            }
            urcMsg = RfxMclMessage::obtainUrc(RFX_MSG_UNSOL_PCO_DATA_AFTER_ATTACHED,
                    m_slot_id, RfxPcoIaData(&pcoDataIa, sizeof(pcoDataIa)));
        } else {
            RIL_PCO_Data pcoData;
            pcoData.cid = m_pPdnManager->getTransIntfId(pcoInfo->cid);
            int protoBitMask = 0; // 1:v4, 2:v6, 4:v4v6
            for (int i = 0; i < m_pPdnManager->getPdnTableSize(); i++) {
                if (pcoData.cid == m_pPdnManager->getTransIntfId(i)) {
                    std::string ipv4 = std::string(m_pPdnManager->getIpv4Address(i));
                    std::string ipv6 = std::string(m_pPdnManager->getIpv6Address(i, 0));
                    ipv4.erase(std::remove_if(begin(ipv4), end(ipv4), ::isspace), end(ipv4));
                    ipv6.erase(std::remove_if(begin(ipv6), end(ipv6), ::isspace), end(ipv6));
                    protoBitMask |= (ipv4.size() > 0 && ipv6.size() == 0) ? 1<<IPV4:
                            (ipv4.size() == 0 && ipv6.size() > 0) ? 1<<IPV6:
                            (ipv4.size() > 0 && ipv6.size() > 0) ? 1<<IPV4V6 : 1<<IPV4;
                    strncpy(strApnName, m_pPdnManager->getApnName(i), MAX_APN_NAME_LENGTH - 1);
                }
            }

            std::string proto;
            switch (protoBitMask) {
                case 1<<IPV4:
                    proto = SETUP_DATA_PROTOCOL_IP;
                    break;
                case 1<<IPV6:
                    proto = SETUP_DATA_PROTOCOL_IPV6;
                    break;
                case (1<<IPV4 | 1<<IPV6):
                case 1<<IPV4V6:
                    proto = SETUP_DATA_PROTOCOL_IPV4V6;
                    break;
                default:
                    proto = SETUP_DATA_PROTOCOL_IP;
                    break;
            }
            pcoData.bearer_proto = (char*) proto.c_str();
            pcoData.pco_id = std::stoi(std::string(pcoInfo->pcoList[i].ie), NULL, 16);
            pcoData.contents_length = 1;
            pcoData.contents = (char *)pcoValue.c_str();
            RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] PCO cid %d, proto %s, pcoid %d, contents %s, apn %s",
                    m_slot_id, __FUNCTION__,
                    pcoData.cid, pcoData.bearer_proto, pcoData.pco_id, pcoData.contents,
                    strApnName);
            urcMsg = RfxMclMessage::obtainUrc(RFX_MSG_UNSOL_PCO_DATA, m_slot_id,
                    RfxPcoData(&pcoData, sizeof(pcoData)));
        }
        if (urcMsg == NULL) {
            RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] fail to obtainUrc!", m_slot_id, __FUNCTION__);
            continue;
        }
        String8 pcoStatusKey = String8(pcoInfo->pcoList[i].ie);
        pcoStatusKey.append(":");
        pcoStatusKey.append(pcoValue.c_str());
        getMclStatusManager()->setString8Value(RFX_STATUS_KEY_PCO_STATUS, pcoStatusKey);
        responseToTelCore(urcMsg);

        if (nPcoValue > -1) notifyPcoValue(nPcoValue, strApnName);
    }
}

void RmmDcEventHandler::handleQueryPcoAfterAttach(const sp<RfxMclMessage>& msg) {
    MipcAttachApnInfo *iaApnInfo = (MipcAttachApnInfo *)msg->getData()->getData();
    sp<RfxMipcData> mipcMsg = RfxMipcData::obtainMipcData(MIPC_DATA_GET_PCO_REQ, msg->getSlotId());
    mipcMsg->addMipcTlvStr(MIPC_DATA_GET_PCO_REQ_T_APN, iaApnInfo->apn);
    mipcMsg->addMipcTlvUint32(MIPC_DATA_GET_PCO_REQ_T_APN_INDEX, iaApnInfo->apnIndex);
    callToMipcMsgAsync(msg, mipcMsg);
}

void RmmDcEventHandler::handleQueryPcoAfterAttachResponse(const sp<RfxMclMessage>& msg) {
    MipcAttachApnInfo *iaApnInfo = (MipcAttachApnInfo *)msg->getData()->getData();
    MipcPcoInfo pcoInfo;
    memset(&pcoInfo, 0, sizeof(pcoInfo));
    pcoInfo.pcoCount = (int)msg->getMipcData()->getMipcUint8Val(
            MIPC_DATA_GET_PCO_CNF_T_PCO_COUNT, 0);
    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s]: pco count: %d", m_slot_id, __FUNCTION__, pcoInfo.pcoCount);
    if (pcoInfo.pcoCount > 0) {
        mipc_data_pco_ie_struct4 *mipcPcoItem = (mipc_data_pco_ie_struct4 *)mipc_msg_get_val_ptr(
                msg->getMipcData()->getData(), MIPC_DATA_GET_PCO_CNF_T_PCO_LIST, NULL);
        if (mipcPcoItem == NULL) {
            RFX_LOG_E(RFX_LOG_TAG, "[%d][%s]: no pco item!", m_slot_id, __FUNCTION__);
            return;
        }
        pcoInfo.pcoList = (MipcPcoItem *)calloc(pcoInfo.pcoCount, sizeof(MipcPcoItem));
        if (pcoInfo.pcoList == NULL) {
            RFX_LOG_E(RFX_LOG_TAG, "[%d][%s]: no memory!!!", m_slot_id, __FUNCTION__);
            return;
        }
        for (int i = 0; i < pcoInfo.pcoCount; i++) {
            strncpy(pcoInfo.pcoList[i].ie, mipcPcoItem[i].ie, MIPC_MAX_PCO_IE_LEN - 1);
            strncpy(pcoInfo.pcoList[i].content, mipcPcoItem[i].content,
                    MIPC_MAX_PCO_CONTENT_LEN - 1);
            RFX_LOG_D(RFX_LOG_TAG, "[%d][%s]: pco ie: %s, content: %s", m_slot_id, __FUNCTION__,
                    pcoInfo.pcoList[i].ie, pcoInfo.pcoList[i].content);
        }
        pcoInfo.cid = (int)msg->getMipcData()->getMipcUint8Val(MIPC_DATA_GET_PCO_CNF_T_ID, 0);
        // ia apn pco extra parameters
        strncpy(pcoInfo.apn, iaApnInfo->apn, MIPC_MAX_APN_LEN - 1);
        pcoInfo.pdpType = iaApnInfo->pdpType;
        sendEvent(RFX_MSG_EVENT_QUERY_PCO_WITH_AID,
                RfxPcoInfo(&pcoInfo, sizeof(pcoInfo)), RIL_CMD_PROXY_5, m_slot_id);
        free(pcoInfo.pcoList);
    }
}

int RmmDcEventHandler::confirmPdnUsage(const int aid, const bool bUsed) {
    String8 cmd("");
    sp<RfxAtResponse> p_response;

    // Check if AID is out of bound.
    if (!m_pPdnManager->validateAid(aid)) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] aid=%d is out of bound",
                m_slot_id, __FUNCTION__, aid);
        return -1;
    }

    sp<RfxMipcData> mipcNtf = RfxMipcData::obtainMipcData(MIPC_DATA_ACT_CALL_NTF, m_slot_id);
    mipcNtf->addMipcTlvUint8(MIPC_DATA_ACT_CALL_NTF_T_ID, (uint8_t)aid);
    mipcNtf->addMipcTlvUint8(MIPC_DATA_ACT_CALL_NTF_T_RESPONSE,
            (uint8_t)(bUsed ? MIPC_ACT_CALL_NTF_ENUM_USE_FB_DATA_CALL
                    : MIPC_ACT_CALL_NTF_ENUM_UNUSE_FB_DATA_CALL));
    int result = callToMipcMsgNtf(mipcNtf);
    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] MIPC_DATA_ACT_CALL_NTF for aid %d return %d",
            m_slot_id, __FUNCTION__, aid, result);

    return 0;
}

bool RmmDcEventHandler::isFallbackPdn(const int aid) {
    int rid = m_slot_id;
    int pdnsOfActive = 0;
    PdnInfo pdn_info;
    memset(&pdn_info, 0, sizeof(pdn_info));
    const int nPdnInfoSize = m_pPdnManager->getPdnTableSize();

    // Check if AID is out of bound.
    if (!m_pPdnManager->validateAid(aid)) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] aid=%d is out of bound",
                rid, __FUNCTION__, aid);
        return false;
    }

    for (int i = 0; i < nPdnInfoSize; i++) {
        pdn_info = m_pPdnManager->getPdnInfo(i);
        if ((pdn_info.active == DATA_STATE_ACTIVE) && pdn_info.aid != aid
                && (m_pPdnManager->getTransIntfId(pdn_info.aid)
                        == m_pPdnManager->getTransIntfId(aid))) {
            pdnsOfActive++;
        }
    }

    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] aid=%d transIntfId=%d has %d fallback aids",
            rid, __FUNCTION__, aid, m_pPdnManager->getTransIntfId(aid), pdnsOfActive);
    return (pdnsOfActive > 0) ? true : false;
}

bool RmmDcEventHandler::notifyDeactReasonIfNeeded(const int deactivatedAid) {
    int rid = m_slot_id;

    // Check if AID is out of bound.
    if (!m_pPdnManager->validateAid(deactivatedAid)) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] deactivatedAid=%d is out of bound",
                rid, __FUNCTION__, deactivatedAid);
        return false;
    }

    // Update the reason of why pdn was deactivated to FWK for checking if needs to do pdn retrying
    // except that there has no existed reason or another of fallback pdn of the same apn is still alive.
    if (m_pPdnManager->getDeactReason(deactivatedAid) != NO_REASON
            && !isFallbackPdn(deactivatedAid)) {
        RFX_LOG_I(RFX_LOG_TAG, "[%d][%s] notify deact reason %d for {deactAid=%d, transIntfId=%d}",
                rid, __FUNCTION__, m_pPdnManager->getDeactReason(deactivatedAid), deactivatedAid,
                m_pPdnManager->getTransIntfId(deactivatedAid));
        return true;
    }
    return false;
}

bool RmmDcEventHandler::isSupportWifiBearer(int bearerBitmask) {
    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] bearerBitmask = %d", m_slot_id,
            __FUNCTION__, bearerBitmask);
    return ((bearerBitmask & (1 << (RADIO_TECH_IWLAN - 1))) != 0);
}

int RmmDcEventHandler::getIndexFromApnTable(unsigned int slot_id, ApnTableReq *pApnTableReq) {
    int index = -1;

    RFX_LOG_V(RFX_LOG_TAG, "[%d][%s] pApnTableReq apn=%s, user=%s, pwd=%s, apnTypeId=%d, protocol=%s, authtype=%d",
            slot_id, __FUNCTION__, pApnTableReq->apn, pApnTableReq->username, pApnTableReq->password,
            pApnTableReq->apnTypeId, pApnTableReq->protocol, pApnTableReq->authtype);

    // apn;user;password;type(default,mms,...);protocol;roaming_protocol;
    // authtype;carrier_enabled;max_conns;max_conns_time;wait_time;bearer_bitmask;inactive_timer;cmd_index
    for (int i = 0; i < s_nLastReqNum[slot_id]; i++) {

        RFX_LOG_V(RFX_LOG_TAG, "[%d][%s] s_nLastReqNum[%d][%d] apn=%s, user=%s, pwd=%s, supportedTypesBitmask=%d, protocol=%s, authtype=%d",
                slot_id, __FUNCTION__, slot_id, i, s_LastApnTable[slot_id][i].apn, s_LastApnTable[slot_id][i].user,
                s_LastApnTable[slot_id][i].password, s_LastApnTable[slot_id][i].supportedTypesBitmask,
                s_LastApnTable[slot_id][i].protocol, s_LastApnTable[slot_id][i].authType);

        if (pApnTableReq->apn && 0 != strcasecmp(pApnTableReq->apn, s_LastApnTable[slot_id][i].apn)) {
            RFX_LOG_V(RFX_LOG_TAG, "[%d][%s] apn is not the same: %s",
                    slot_id, __FUNCTION__, s_LastApnTable[slot_id][i].apn);
            continue;
        }

        if (pApnTableReq->username && 0 != strcasecmp(pApnTableReq->username, s_LastApnTable[slot_id][i].user)) {
            RFX_LOG_V(RFX_LOG_TAG, "[%d][%s] user is not the same: %s",
                    slot_id, __FUNCTION__, s_LastApnTable[slot_id][i].user);
            continue;
        }

        if (pApnTableReq->password && 0 != strcasecmp(pApnTableReq->password, s_LastApnTable[slot_id][i].password)) {
            RFX_LOG_V(RFX_LOG_TAG, "[%d][%s] pwd is not the same: %s",
                    slot_id, __FUNCTION__, s_LastApnTable[slot_id][i].password);
            continue;
        }

        if (pApnTableReq->apnTypeId != APN_TYPE_INVALID) {
            if ((s_LastApnTable[slot_id][i].supportedTypesBitmask & pApnTableReq->apnTypeId) != pApnTableReq->apnTypeId) {
                RFX_LOG_V(RFX_LOG_TAG, "[%d][%s] supportedTypesBitmask is not supported: %d",
                        slot_id, __FUNCTION__, s_LastApnTable[slot_id][i].supportedTypesBitmask);
                continue;
            }
        }

        if (pApnTableReq->protocol&& 0 != strcasecmp(pApnTableReq->protocol, s_LastApnTable[slot_id][i].protocol)) {
            RFX_LOG_V(RFX_LOG_TAG, "[%d][%s] protocol is not the same: %s",
                    slot_id, __FUNCTION__, s_LastApnTable[slot_id][i].protocol);
            continue;
        }
        if (pApnTableReq->authtype != s_LastApnTable[slot_id][i].authType) {
            RFX_LOG_V(RFX_LOG_TAG, "[%d][%s] authtype is not the same: %d",
                    slot_id, __FUNCTION__, s_LastApnTable[slot_id][i].authType);
            continue;
        }

        index = i;
        break;
    }

    return index;
}

// Support requirements to cleanup all data connections.
// This function is used for sync data connections status between Java Framework
// and RILD when phone process reinitiate.
void RmmDcEventHandler::handleResetAllConnections(const sp<RfxMclMessage>& msg) {
    RFX_LOG_D(RFX_LOG_TAG, "[%s]", __FUNCTION__);
    sp<RfxMclMessage> responseMsg;
    const int nPdnInfoSize = m_pPdnManager->getPdnTableSize();

    for (int i = 0; i < nPdnInfoSize; i++) {
        int aid = m_pPdnManager->getAid(i);
        if (aid != INVALID_AID && !m_pPdnManager->isDedicateBearer(i)) {
            deactivateDataCall(aid);
            m_pPdnManager->clearPdnInfo(aid);
        }
    }

    responseMsg = RfxMclMessage::obtainResponse(RIL_E_SUCCESS, RfxVoidData(), msg);
    responseToTelCore(responseMsg);
}

/*
 * The usage of resend prefer data in the case of RILD-reconnect.
 */
void RmmDcEventHandler::resendPreferData() {
    char preferDataSlot[RFX_PROPERTY_VALUE_MAX] = {0};
    rfx_property_get(PREFER_DATA_SLOT_PROPERTY, preferDataSlot, "-1");
    int preferSlot = atoi(preferDataSlot);
    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] prefer slot = %d", m_slot_id, __FUNCTION__, preferSlot);

    if (preferSlot >= RFX_SLOT_ID_0 && preferSlot < MAX_RFX_SLOT_ID
                && preferSlot == m_slot_id) {
        getNonSlotMclStatusManager()->setIntValue(RFX_STATUS_KEY_PREFERRED_DATA_SIM,
                preferSlot, true);
        sp<RfxMipcData> mipcReq = RfxMipcData::obtainMipcData(
                MIPC_DATA_SET_DATA_ALLOW_REQ, m_slot_id);
        mipc_msg_async(mipcReq->getData(), NULL, NULL);
    }
}

void RmmDcEventHandler::requestSetPreferredDataModem(const sp<RfxMclMessage>& msg) {
    int *pReqData = (int *)msg->getData()->getData();
    // 0: slot 0
    // 1: slot 1
    int preferredMd = pReqData[0];
    int rid = m_slot_id;
    RIL_Errno ret = RIL_E_SUCCESS;
    sp<RfxAtResponse> p_response;
    sp<RfxMclMessage> responseMsg;

    RFX_LOG_I(RFX_LOG_TAG, "[%d][%s] requestSetPreferredDataModem, preferredMd=%d",
            rid, __FUNCTION__, preferredMd);

    if (preferredMd >= RFX_SLOT_ID_0 && preferredMd < MAX_RFX_SLOT_ID
            && preferredMd == rid) {
        sp<RfxMipcData> mipcReq = RfxMipcData::obtainMipcData(MIPC_DATA_SET_DATA_ALLOW_REQ, rid);
        sp<RfxMipcData> mipcCnf = callToMipcMsgSync(mipcReq);
        if ((mipc_result_const_enum) mipcCnf->getResult() != MIPC_RESULT_SUCCESS) {
            RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] MIPC_DATA_SET_DATA_ALLOW_REQ return error",
                    rid, __FUNCTION__);
            ret = RIL_E_INTERNAL_ERR;
        }
    }

    responseMsg = RfxMclMessage::obtainResponse(ret, RfxVoidData(), msg);
    responseToTelCore(responseMsg);
}

bool RmmDcEventHandler::getMccmnc(char* mccmnc) {
    char key[MAX_LENGTH_PROPERTY_NAME] = {0};
    int n = 0;
    if (m_slot_id == 0) {
        n = snprintf(key, MAX_LENGTH_PROPERTY_NAME - 1, "%s", PROPERTY_MCC_MNC);
    } else {
        n = snprintf(key, MAX_LENGTH_PROPERTY_NAME - 1, "%s%s%d", PROPERTY_MCC_MNC, ".", m_slot_id);
    }
    if (n < 0) {
        return false;
    }
    rfx_property_get(key, mccmnc, "0");
    if (strlen(mccmnc) > 3) {
        return true;
    }

    memset(mccmnc, 0, MAX_LENGTH_MCCMNC);
    memset(key, 0, MAX_LENGTH_PROPERTY_NAME);
    if (m_slot_id == 0) {
        n = snprintf(key, MAX_LENGTH_PROPERTY_NAME - 1, "%s", PROPERTY_MCC_MNC_CDMA);
    } else {
        n = snprintf(key, MAX_LENGTH_PROPERTY_NAME - 1, "%s%s%d",
                PROPERTY_MCC_MNC_CDMA, ".", m_slot_id);
    }
    if (n < 0) {
        return false;
    }
    rfx_property_get(key, mccmnc, "0");
    if (strlen(mccmnc) > 3) {
        return true;
    }

    return false;
}

void RmmDcEventHandler::requestGetDataContextIds(const sp<RfxMclMessage>& msg) {
    RFX_UNUSED(msg);
    Vector<int> vTransIntfIdList;
    const int nPdnInfoSize = m_pPdnManager->getPdnTableSize();

    vTransIntfIdList.reserve(nPdnInfoSize);

    for (int i = 0; i < nPdnInfoSize; i++) {
        if ((m_pPdnManager->getPdnActiveStatus(i) == DATA_STATE_ACTIVE) &&
                (m_pPdnManager->getTransIntfId(i) != INVALID_TRANS_INTF_ID) &&
                (std::find(vTransIntfIdList.begin(), vTransIntfIdList.end(),
                m_pPdnManager->getTransIntfId(i)) == vTransIntfIdList.end())) {
            vTransIntfIdList.push_back(m_pPdnManager->getTransIntfId(i));
        }
    }

    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] the number of context ids = %d",
            m_slot_id, __FUNCTION__, (int)vTransIntfIdList.size());

    sendEvent(RFX_MSG_EVENT_RSP_DATA_CONTEXT_IDS,
            RfxIntsData((int*)vTransIntfIdList.array(), vTransIntfIdList.size()),
            RIL_CMD_PROXY_3, m_slot_id);
}

bool RmmDcEventHandler::isHandoverRequest(int reason, int profileId, int *pTransIntfId) {
    if (reason != ACT_REASON_AOSP_HANDOVER) {
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] profileId %d reason %d is not for handover",
                m_slot_id, __FUNCTION__, profileId, reason);
        return false;
    }

    const int nPdnInfoSize = m_pPdnManager->getPdnTableSize();
    PdnInfo pdn_info;

    for (int i = 0; i < nPdnInfoSize; i++) {
        pdn_info = m_pPdnManager->getPdnInfo(i);
        if (pdn_info.profileId == profileId && !pdn_info.isDedicateBearer &&
                pdn_info.active == DATA_STATE_ACTIVE) {
            *pTransIntfId = pdn_info.transIntfId;
            return true;
        }
    }
    return false;
}

void RmmDcEventHandler::requestSendQualifiedNetworkTypesChanged(const sp<RfxMclMessage>& msg) {
    int *pReqData = (int *)msg->getData()->getData();
    int apnType = pReqData[0];
    int rat = pReqData[1];
    int data[3] = {0};
    sp<RfxMclMessage> urcMsg;

    data[0] = 1; // this element is 'mode' to indicate the parsing rule of the remain array elements.
    data[1] = apnType;
    data[2] = rat;

    urcMsg = RfxMclMessage::obtainUrc(RFX_MSG_URC_QUALIFIED_NETWORK_TYPES_CHANGED,
            m_slot_id, RfxIntsData(data, 3));
    responseToTelCore(urcMsg);

    RFX_LOG_I(RFX_LOG_TAG, "[%d][%s] mode=%d, apnType=%d, rat=%d",
            m_slot_id, __FUNCTION__, data[0], data[1], data[2]);
}

void RmmDcEventHandler::sendQualifiedNetworkTypesChanged(int aid, int newRat) {
    PdnInfo pdn_info;
    int data[3] = {0};
    sp<RfxMclMessage> urcMsg;

    pdn_info = m_pPdnManager->getPdnInfo(aid);
    if (!pdn_info.isDedicateBearer && pdn_info.active == DATA_STATE_ACTIVE) {
        data[0] = 1; // 'mode' to indicate the parsing rule of the remain array elements.
        data[1] = RmmDcUtility::getApnTypeId(pdn_info.profileId);

        // Value from 3~6 will be view as IWLAN, which is related to VoData feature
        if (newRat >= ACCESS_NW_TYPE_VODATA1 && newRat <= ACCESS_NW_TYPE_VODATA4) {
            RFX_LOG_I(RFX_LOG_TAG, "[%d][%s] rat=%d change to IWLAN(2)", m_slot_id, __FUNCTION__,
                    newRat);
            newRat = ACCESS_NW_TYPE_IWLAN;
        }
        data[2] = newRat;

        urcMsg = RfxMclMessage::obtainUrc(RFX_MSG_URC_QUALIFIED_NETWORK_TYPES_CHANGED,
                m_slot_id, RfxIntsData(data, 3));
        responseToTelCore(urcMsg);
        RFX_LOG_I(RFX_LOG_TAG, "[%d][%s] mode=%d, apnType=%d, rat=%d", m_slot_id,
                __FUNCTION__, data[0], data[1], data[2]);
    }
}

void RmmDcEventHandler::setPdnInfoProperty() {
    Vector<int> vTransIntfIdList;
    const int nPdnInfoSize = m_pPdnManager->getPdnTableSize();
    String8 keyPdnInfo("");
    String8 valuePdnInfo("");

    keyPdnInfo.append(String8::format("vendor.ril.data.pdn_info%d", m_slot_id));

    vTransIntfIdList.reserve(nPdnInfoSize);
    for (int i = 0; i < nPdnInfoSize; i++) {
        if ((m_pPdnManager->getPdnActiveStatus(i) == DATA_STATE_ACTIVE) &&
                (m_pPdnManager->getTransIntfId(i) != INVALID_TRANS_INTF_ID) &&
                (std::find(vTransIntfIdList.begin(), vTransIntfIdList.end(),
                m_pPdnManager->getTransIntfId(i)) == vTransIntfIdList.end())) {
            PdnInfo pdn_info = m_pPdnManager->getPdnInfo(i);
            if (pdn_info.profileId != RIL_DATA_PROFILE_IMS
                    && pdn_info.profileId != RIL_DATA_PROFILE_VENDOR_EMERGENCY) {
                valuePdnInfo.append(String8::format("%s_%d,",
                        RmmDcUtility::getProfileType(pdn_info.profileId),
                        m_pPdnManager->getInterfaceId(i)));
                vTransIntfIdList.push_back(m_pPdnManager->getTransIntfId(i));
            }
        }
    }

    rfx_property_set(keyPdnInfo, valuePdnInfo.string());

    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] %s = %s",
            m_slot_id, __FUNCTION__, keyPdnInfo.string(), valuePdnInfo.string());
}

void RmmDcEventHandler::handleMobileDataUsageNotify(const sp<RfxMclMessage>& msg) {
    // <tx_bytes>,<tx_packets>,<rx_bytes>,<rx_packets>
    int* data = (int*)msg->getData()->getData();
    if (data == NULL) return;

    int response[COUNT_MOBILE_DATA_USAGE] = {0};
    memcpy(response, data, COUNT_MOBILE_DATA_USAGE * sizeof(int));

    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] %d,%d,%d,%d",
            m_slot_id, __FUNCTION__, response[0], response[1], response[2], response[3]);
    sp<RfxMclMessage> urcMsg = RfxMclMessage::obtainUrc(RFX_MSG_URC_MOBILE_DATA_USAGE,
            m_slot_id, RfxIntsData(response, COUNT_MOBILE_DATA_USAGE));
    responseToTelCore(urcMsg);
}

// Handle apns that support ims/mms/xcap/emergency/cbs, but have no bearerbitmask configured.
// e.g. There is an apn(A) support mms type and has no bearerbitmask configured,
// If there is another apn also has mms type but the BearerBitmask is 18(wifi only),
// then configure apn A with bearerbitmask cellular only, else configure apn A
// cellular and WiFi.
void RmmDcEventHandler::adjustBearerBitmask(RIL_MtkDataProfileInfo **dataProfilePtrs,
        int count) {
    if (isWifiApnExplicitlyConfigured()) {
        for (int i = 0; i < count; i++) {
            if (dataProfilePtrs[i]->bearerBitmask == 0) {
                dataProfilePtrs[i]->bearerBitmask = ALL_BEARER_EXCLUDE_IWLAN_BITMASK;
            }
        }
        return;
    }

    for (int i = 0; i < count; i++) {
        if (dataProfilePtrs[i]->bearerBitmask == 0) {
            if (isSupportWifiType(dataProfilePtrs[i]->supportedTypesBitmask)) {
                bool find = false;
                for (int j = 0; j < count; j++) {
                    if (isSupportWifiType(dataProfilePtrs[i]->supportedTypesBitmask
                            & dataProfilePtrs[j]->supportedTypesBitmask)
                            && dataProfilePtrs[j]->bearerBitmask == (1 << (RADIO_TECH_IWLAN - 1))) {
                        find = true;
                        break;
                    }
                }

                RFX_LOG_I(RFX_LOG_TAG, "[%d][%s] %s find %d apn that support wifi only",
                        m_slot_id, __FUNCTION__, dataProfilePtrs[i]->apn, find);

                if (find) {
                    dataProfilePtrs[i]->bearerBitmask = ALL_BEARER_EXCLUDE_IWLAN_BITMASK;
                } else {
                    dataProfilePtrs[i]->bearerBitmask = ALL_BEARER_BITMASK;
                }
            } else {
                dataProfilePtrs[i]->bearerBitmask = ALL_BEARER_EXCLUDE_IWLAN_BITMASK;
            }
        }
    }
}

bool RmmDcEventHandler::isSupportWifiType(int typesBitmask) {
    if (typesBitmask & RIL_APN_TYPE_IMS
            || typesBitmask & RIL_APN_TYPE_MMS
            || typesBitmask & RIL_APN_TYPE_XCAP
            || typesBitmask & RIL_APN_TYPE_EMERGENCY
            || typesBitmask & RIL_APN_TYPE_CBS) {
        return true;
    }
    return false;
}

void RmmDcEventHandler::requestStartKeepalive(const sp<RfxMclMessage>& msg) {
    String8 cmd("");
    sp<RfxAtResponse> p_response;
    sp<RfxMclMessage> responseMsg;
    char sourceAddress[MAX_IPV6_ADDRESS_LENGTH] = {0};
    char destinationAddress[MAX_IPV6_ADDRESS_LENGTH] = {0};
    char srcPort[6] = {0}, dstPort[6] = {0};
    int type = IPV4_UDP;
    RIL_Errno status = RIL_E_INVALID_ARGUMENTS;
    RIL_KeepaliveStatus keepaliveStatus = {0, KEEPALIVE_INACTIVE};
    int n = 0;
    sp<RfxMipcData> mipcReq = NULL;
    sp<RfxMipcData> mipcCnf = NULL;
    mipc_data_start_keepalive_request_struct4 *kaStruct = NULL;

    RIL_KeepaliveRequest *pReq = (RIL_KeepaliveRequest*)msg->getData()->getData();

    if (pReq->type == NATT_IPV4) {
        n = snprintf(sourceAddress, MAX_IPV4_ADDRESS_LENGTH, "%d.%d.%d.%d",
                pReq->sourceAddress[0] & 0xff, pReq->sourceAddress[1] & 0xff,
                pReq->sourceAddress[2] & 0xff, pReq->sourceAddress[3] & 0xff);
        if (n < 0) {
            RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] fail to snprintf", m_slot_id, __FUNCTION__);
            goto finish;
        }
        n = snprintf(destinationAddress, MAX_IPV4_ADDRESS_LENGTH, "%d.%d.%d.%d",
                pReq->destinationAddress[0] & 0xff, pReq->destinationAddress[1] & 0xff,
                pReq->destinationAddress[2] & 0xff, pReq->destinationAddress[3] & 0xff);
        if (n < 0) {
            RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] fail to snprintf", m_slot_id, __FUNCTION__);
            goto finish;
        }
    } else {
        n = snprintf(sourceAddress, MAX_IPV6_ADDRESS_LENGTH, "%02X%02X:%02X%02X:"
                "%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X",
                pReq->sourceAddress[0] & 0xff, pReq->sourceAddress[1] & 0xff,
                pReq->sourceAddress[2] & 0xff, pReq->sourceAddress[3] & 0xff,
                pReq->sourceAddress[4] & 0xff, pReq->sourceAddress[5] & 0xff,
                pReq->sourceAddress[6] & 0xff, pReq->sourceAddress[7] & 0xff,
                pReq->sourceAddress[8] & 0xff, pReq->sourceAddress[9] & 0xff,
                pReq->sourceAddress[10] & 0xff, pReq->sourceAddress[11] & 0xff,
                pReq->sourceAddress[12] & 0xff, pReq->sourceAddress[13] & 0xff,
                pReq->sourceAddress[14] & 0xff, pReq->sourceAddress[15] & 0xff);
        if (n < 0) {
            RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] fail to snprintf", m_slot_id, __FUNCTION__);
            goto finish;
        }
        n = snprintf(destinationAddress, MAX_IPV6_ADDRESS_LENGTH, "%02X%02X:%02X%02X:"
                "%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X",
                pReq->destinationAddress[0] & 0xff, pReq->destinationAddress[1] & 0xff,
                pReq->destinationAddress[2] & 0xff, pReq->destinationAddress[3] & 0xff,
                pReq->destinationAddress[4] & 0xff, pReq->destinationAddress[5] & 0xff,
                pReq->destinationAddress[6] & 0xff, pReq->destinationAddress[7] & 0xff,
                pReq->destinationAddress[8] & 0xff, pReq->destinationAddress[9] & 0xff,
                pReq->destinationAddress[10] & 0xff, pReq->destinationAddress[11] & 0xff,
                pReq->destinationAddress[12] & 0xff, pReq->destinationAddress[13] & 0xff,
                pReq->destinationAddress[14] & 0xff, pReq->destinationAddress[15] & 0xff);
        if (n < 0) {
            RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] fail to snprintf", m_slot_id, __FUNCTION__);
            goto finish;
        }
        type = IPV6_UDP;
    }

    n = snprintf(srcPort, sizeof(srcPort), "%d", pReq->sourcePort);
    if (n < 0) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] fail to snprintf", m_slot_id, __FUNCTION__);
        goto finish;
    }
    n = snprintf(dstPort, sizeof(dstPort), "%d", pReq->destinationPort);
    if (n < 0) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] fail to snprintf", m_slot_id, __FUNCTION__);
        goto finish;
    }

    kaStruct = (mipc_data_start_keepalive_request_struct4*)calloc(1,
                    sizeof(mipc_data_start_keepalive_request_struct4));
    RFX_ASSERT(kaStruct != NULL);
    kaStruct->type = pReq->type;
    kaStruct->sourcePort = pReq->sourcePort;
    kaStruct->maxKeepaliveIntervalMillis = pReq->maxKeepaliveIntervalMillis;
    kaStruct->cid = pReq->cid;
    // mipc defined address len is: 68
    n = snprintf(kaStruct->sourceAddress, MAX_INADDR_LEN, "%s", pReq->sourceAddress);
    if (n < 0) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] fail to snprintf sourceAddress",
                m_slot_id, __FUNCTION__);
        goto finish;
    }
    n = snprintf(kaStruct->destinationAddress, MAX_INADDR_LEN, "%s", pReq->destinationAddress);
    if (n < 0) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] fail to snprintf destinationAddress",
                m_slot_id, __FUNCTION__);
        goto finish;
    }

    mipcReq = RfxMipcData::obtainMipcData(MIPC_DATA_KEEPALIVE_REQ, m_slot_id);
    mipcReq->addMipcTlv(MIPC_DATA_KEEPALIVE_REQ_T_START_KEEPALIVE,
            sizeof(mipc_data_start_keepalive_request_struct4), kaStruct);
    mipcCnf = callToMipcMsgSync(mipcReq);
    if ((mipc_result_const_enum) mipcCnf->getResult() != MIPC_RESULT_SUCCESS) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] MIPC_DATA_KEEPALIVE_REQ return error",
                m_slot_id, __FUNCTION__);
        goto finish;
    }

    keepaliveStatus.sessionHandle = mipcCnf->getMipcUint32Val(
            MIPC_DATA_KEEPALIVE_CNF_T_SESSION_HANDLE, 0);
    keepaliveStatus.code = (RIL_KeepaliveStatusCode) mipcCnf->getMipcUint8Val(
            MIPC_DATA_KEEPALIVE_CNF_T_STATUS_CODE, 0);
    status = RIL_E_SUCCESS;

finish:
    FREEIF(kaStruct);
    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] sessionHandle=%d, code=%d", m_slot_id, __FUNCTION__,
            keepaliveStatus.sessionHandle, keepaliveStatus.code);
    responseMsg = RfxMclMessage::obtainResponse(status,
            RfxKeepaliveStatusData(&keepaliveStatus, sizeof(keepaliveStatus)), msg);
    responseToTelCore(responseMsg);
}

void RmmDcEventHandler::requestStopKeepalive(const sp<RfxMclMessage>& msg) {
    sp<RfxMclMessage> responseMsg;

    int* param = (int*)(msg->getData()->getData());
    int conn_id = param[0];

    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] conn_id=%d", m_slot_id, __FUNCTION__, conn_id);

    sp<RfxMipcData> mipcReq = RfxMipcData::obtainMipcData(MIPC_DATA_KEEPALIVE_REQ, m_slot_id);
    mipcReq->addMipcTlvUint32(MIPC_DATA_KEEPALIVE_REQ_T_STOP_KEEPALIVE, conn_id);
    sp<RfxMipcData> mipcCnf = callToMipcMsgSync(mipcReq);
    mipc_result_const_enum mipcRet = (mipc_result_const_enum) mipcCnf->getResult();
    if (mipcRet != MIPC_RESULT_SUCCESS) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] MIPC_DATA_KEEPALIVE_REQ return error",
                m_slot_id, __FUNCTION__);
        responseMsg = RfxMclMessage::obtainResponse(RIL_E_INVALID_ARGUMENTS, RfxVoidData(), msg);
    } else {
        responseMsg = RfxMclMessage::obtainResponse(RIL_E_SUCCESS, RfxVoidData(), msg);
    }
    responseToTelCore(responseMsg);
}

void RmmDcEventHandler::updateKeepaliveStatus(const sp<RfxMclMessage>& msg) {
    int *pInt = (int *)msg->getData()->getData(); // [0]: session handle, [1]:status code
    if (pInt == NULL) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] Data is NULL", m_slot_id, __FUNCTION__);
        return;
    }
    RIL_KeepaliveStatus keepaliveStatus = {0, KEEPALIVE_INACTIVE};
    keepaliveStatus.sessionHandle = (uint32_t)pInt[0];
    keepaliveStatus.code = (RIL_KeepaliveStatusCode)pInt[1];
    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] sessionHandle=%d, code=%d", m_slot_id, __FUNCTION__,
            keepaliveStatus.sessionHandle, keepaliveStatus.code);
    sp<RfxMclMessage> urcMsg = RfxMclMessage::obtainUrc(RFX_MSG_URC_KEEPALIVE_STATUS,
            m_slot_id,
            RfxKeepaliveStatusData(&keepaliveStatus, sizeof(keepaliveStatus)));
    responseToTelCore(urcMsg);
}

void RmmDcEventHandler::onNwLimitNotify(const sp<RfxMclMessage>& msg) {
    sp<RfxMclMessage> urcMsg;
    int response[1] = {0};
    response[0] = ((int *)msg->getData()->getData())[0];
    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] limit = %d", m_slot_id, __FUNCTION__, response[0]);
    urcMsg = RfxMclMessage::obtainUrc(RFX_MSG_URC_NW_LIMIT, m_slot_id, RfxIntsData(response, 1));
    responseToTelCore(urcMsg);
}

void RmmDcEventHandler::onKernelAddressUpdated(const sp<RfxMclMessage>& msg) {
    CallbackInfo *pCbInfo = (CallbackInfo*)msg->getData()->getData();
    String8 info("");
    if (!mIsUserBuild) {
        int globalIpv6Count = pCbInfo->interfaceInfo->globalIpv6Count;
        info.append(String8::format("reason=%d, interfaceId=%d, addressV4=%s, "
                "mtuV4=%d, mtuv6=%d, globalIpv6Count=%d, ",
                pCbInfo->reason, pCbInfo->interfaceInfo->interfaceId,
                pCbInfo->interfaceInfo->addressV4, pCbInfo->interfaceInfo->mtuV4,
                pCbInfo->interfaceInfo->mtuV6, pCbInfo->interfaceInfo->globalIpv6Count));
        for (int i = 0; i < globalIpv6Count; i++) {
            info.append(String8::format(
                    "Ipv6Info[%d]:{addressV6=%s, prefixLength=%d, flags=%d, "
                    "deprecationTime=%ld, expirationTime=%ld}, ",
                    i,
                    pCbInfo->interfaceInfo->ipv6Info[i].addressV6,
                    pCbInfo->interfaceInfo->ipv6Info[i].prefixLength,
                    pCbInfo->interfaceInfo->ipv6Info[i].flags,
                    pCbInfo->interfaceInfo->ipv6Info[i].deprecationTime,
                    pCbInfo->interfaceInfo->ipv6Info[i].expirationTime));
        }
    }

    int aid = INVALID_AID;
    const int nPdnInfoSize = m_pPdnManager->getPdnTableSize();

    for (int i = 0; i < nPdnInfoSize; i++) {
        if ((m_pPdnManager->getPdnActiveStatus(i) == DATA_STATE_ACTIVE) &&
                (m_pPdnManager->getInterfaceId(i) == pCbInfo->interfaceInfo->interfaceId)) {
            aid = i;
            break;
        }
    }

    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] aid:%d, data:%s", m_slot_id, __FUNCTION__,
            aid, info.string());
    if (aid == INVALID_AID) return;

    // 1. update pdnInfo table according to aid
    // 2. check if m_mapAidReqmsg[aid] is NULL
    //   2.1 If ReqMsg exist, trigger send data call response.
    //   2.2 else, sendDataCallListResponse(msg, SSC_UNKNOWN, true);
    updatePdnInfoByInterfaceInfo(aid, pCbInfo);
    sp<RfxMclMessage> reqMsg = m_mapAidReqmsg[m_pPdnManager->getPrimaryAid(aid)];
    if (reqMsg != NULL) {
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] reqMsg exist.", m_slot_id, __FUNCTION__);
        updateActiveStatusAndProfileById(aid, false);
        bool isActive = m_pPdnManager->getPdnActiveStatus(aid) == DATA_STATE_ACTIVE;
        createAndLaunchDataResponse(isActive ? MIPC_RESULT_SUCCESS : MIPC_RESULT_FAILURE, aid);
    } else {
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] no reqMsg.", m_slot_id, __FUNCTION__);
        sendDataCallListResponse(msg);
    }
}

void RmmDcEventHandler::updatePdnInfoByInterfaceInfo(int aid, CallbackInfo *pCbInfo) {
    if (pCbInfo == NULL || pCbInfo->interfaceInfo == NULL || aid == INVALID_AID) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] illegal param.", m_slot_id, __FUNCTION__);
        return;
    }
    if (m_pPdnManager->getInterfaceId(aid) != pCbInfo->interfaceInfo->interfaceId) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] interfaceId not equal.", m_slot_id, __FUNCTION__);
        return;
    }
    if ((pCbInfo->reason & CALLBACK_REASON_IPV4_CHANGE) != 0) {
        m_pPdnManager->updateIpv4Address(aid, pCbInfo->interfaceInfo->addressV4);
    }
    if ((pCbInfo->reason & CALLBACK_REASON_IPV6_CHANGE) != 0) {
        char emptyV6[MAX_IPV6_ADDRESS_LENGTH] = {0};
        for (int i = 0; i < MAX_IPV6_ADDRESS_COUNT; i++) {
            m_pPdnManager->updateIpv6Address(aid, i, emptyV6);
            if (i < pCbInfo->interfaceInfo->globalIpv6Count) {
                m_pPdnManager->updateIpv6Info(aid, i, pCbInfo->interfaceInfo->ipv6Info[i]);
            }
        }
    }
    if ((pCbInfo->reason & CALLBACK_REASON_MTUV4_CHANGE) != 0) {
        m_pPdnManager->updateMtuV4(aid, pCbInfo->interfaceInfo->mtuV4);
    }
    if ((pCbInfo->reason & CALLBACK_REASON_MTUV6_CHANGE) != 0) {
        m_pPdnManager->updateMtuV6(aid, pCbInfo->interfaceInfo->mtuV6);
    }
}

void RmmDcEventHandler::resetLastApnTable() {
    if (s_LastApnTable[m_slot_id] != NULL) {
        for (int i = 0; i < s_nLastReqNum[m_slot_id]; i++) {
            FREEIF(s_LastApnTable[m_slot_id][i].apn);
            FREEIF(s_LastApnTable[m_slot_id][i].protocol);
            FREEIF(s_LastApnTable[m_slot_id][i].roamingProtocol);
            FREEIF(s_LastApnTable[m_slot_id][i].user);
            FREEIF(s_LastApnTable[m_slot_id][i].password);
            FREEIF(s_LastApnTable[m_slot_id][i].mvnoType);
            FREEIF(s_LastApnTable[m_slot_id][i].mvnoMatchData);
        }
        FREEIF(s_LastApnTable[m_slot_id]);
    }
    FREEIF(s_ApnCmdIndex[m_slot_id]);
    s_nLastReqNum[m_slot_id] = 0;
}

void RmmDcEventHandler::onRadioCapabilityUpdated() {
    if (RmmDcUtility::isFastDormancySupport() == 1) {
        initializeFastDormancy();
    } else {
        RFX_LOG_I(RFX_LOG_TAG, "Fast dormancy is configured disabled");
        handleFastdormancyCommand(MIPC_NW_FAST_DORMANCY_DISABLE, -1, -1);
    }
}

int RmmDcEventHandler::handleFastdormancyCommand(int mode, int param1, int param2) {
    sp<RfxMipcData> mipcMsg = RfxMipcData::obtainMipcData(MIPC_NW_SET_IDLE_HINT_REQ, m_slot_id);
    if (mode == -1) {
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] invalid mode", m_slot_id, __FUNCTION__);
        return 0;
    }

    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] mode=%d param1=%d param2=%d",
            m_slot_id, __FUNCTION__, mode, param1, param2);
    // mode: 0/1 for enable/disable fastdormancy
    // mode: 2 for set timer value
    // mode: 3 for screen status
    mipcMsg->addMipcTlvUint8(MIPC_NW_SET_IDLE_HINT_REQ_T_STATUS, mode);
    if (param1 != -1) {
        mipcMsg->addMipcTlvUint32(MIPC_NW_SET_IDLE_HINT_REQ_T_PARAM_1, param1);
    }
    if (param2 != -1) {
        mipcMsg->addMipcTlvUint32(MIPC_NW_SET_IDLE_HINT_REQ_T_PARAM_2, param2);
    }

    mipc_msg_async(mipcMsg->getData(), NULL, NULL);
    return 1;
}

int RmmDcEventHandler::getCurrentRat() {
    RfxNwServiceState defaultServiceState (0, 0, 0 ,0);
    RfxNwServiceState ss = getMclStatusManager(m_slot_id)
            ->getServiceStateValue(RFX_STATUS_KEY_SERVICE_STATE, defaultServiceState);
    int dataRadioTech = ss.getRilDataRadioTech();
    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] data radiotech:%d",
            m_slot_id, __FUNCTION__, dataRadioTech);
    return dataRadioTech;
}

bool RmmDcEventHandler::updateEpsQos(int aid) {
    if (aid < 0 || aid >= m_pPdnManager->getPdnTableSize()) {
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] invalid param aid:%d",
            m_slot_id, __FUNCTION__, aid);
        return false;
    }

    sp<RfxMipcData> mipcReq = RfxMipcData::obtainMipcData(MIPC_DATA_GET_QOS_REQ, m_slot_id);
    mipcReq->addMipcTlvUint8(MIPC_DATA_GET_QOS_REQ_T_CID, aid);
    sp<RfxMipcData> mipcCnf = callToMipcMsgSync(mipcReq);
    if ((mipc_result_const_enum) mipcCnf->getResult() != MIPC_RESULT_SUCCESS) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] MIPC_DATA_GET_QOS_REQ return error",
                m_slot_id, __FUNCTION__);
        return false;
    }

    uint16_t rspLen; // should be 1 since we quary with aid.
    rspLen = mipc_msg_get_tlv_num(mipcCnf->getData(), MIPC_DATA_GET_QOS_CNF_T_QOS_LIST);
    if (rspLen <= 0) {
        RFX_LOG_W(RFX_LOG_TAG, "[%d][%s] EPS Qos num <= 0, num:%d",
                m_slot_id, __FUNCTION__, rspLen);
        return false;
    }

    mipc_data_qos_info_struct4 *qosInfo
            = (mipc_data_qos_info_struct4*) mipc_data_get_qos_cnf_get_qos_list(
            mipcCnf->getData(), NULL, 0);
    if (qosInfo == NULL) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] EPS Qos struct is null, len:%d index:0",
                m_slot_id, __FUNCTION__, rspLen);
        return false;
    }

    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] qos list len:%d, cid:%d, qci:%d, "
           "DL_GBR:%d, DL_MBR:%d, DL_AMBR:%d, UL_GBR:%d, UL_MBR:%d, UL_AMBR:%d",
            m_slot_id, __FUNCTION__, rspLen, qosInfo->cid, qosInfo->QCI,
            qosInfo->DL_GBR, qosInfo->DL_MBR, qosInfo->DL_AMBR,
            qosInfo->UL_GBR, qosInfo->UL_MBR, qosInfo->UL_AMBR);

    if (!m_pPdnManager->isDedicateBearer(aid)) {
        RIL_Qos defaultQos;
        defaultQos.eps.qci = (int) qosInfo->QCI;
        defaultQos.eps.downlink.guaranteedBitrateKbps = (int) qosInfo->DL_GBR;
        defaultQos.eps.downlink.maxBitrateKbps = (int) qosInfo->DL_MBR;
        defaultQos.eps.uplink.guaranteedBitrateKbps = (int) qosInfo->UL_GBR;
        defaultQos.eps.uplink.maxBitrateKbps  = (int) qosInfo->UL_MBR;
        m_pPdnManager->setDefaultQos(aid, &defaultQos);
        return true;
    } else {
        RIL_QosSession *pQosSession = m_pPdnManager->getQosSession(aid);
        RIL_QosSession tmpQosSession;
        RIL_QosSession *pTmpQosSession = pQosSession != NULL ? pQosSession : &tmpQosSession;

        pTmpQosSession->qos.eps.qci = (int) qosInfo->QCI;
        pTmpQosSession->qos.eps.downlink.guaranteedBitrateKbps = (int) qosInfo->DL_GBR;
        pTmpQosSession->qos.eps.downlink.maxBitrateKbps = (int) qosInfo->DL_MBR;
        pTmpQosSession->qos.eps.uplink.guaranteedBitrateKbps = (int) qosInfo->UL_GBR;
        pTmpQosSession->qos.eps.uplink.maxBitrateKbps = (int) qosInfo->UL_MBR;

        if (pQosSession == NULL) {
            m_pPdnManager->setQosSession(aid, pTmpQosSession);
        }
        return true;
    }
}

bool RmmDcEventHandler::updateNrQos(int aid) {
    if (aid < 0 || aid >= m_pPdnManager->getPdnTableSize()) {
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] invalid param aid:%d",
            m_slot_id, __FUNCTION__, aid);
        return false;
    }

    sp<RfxMipcData> mipcReq = RfxMipcData::obtainMipcData(MIPC_DATA_GET_5GQOS_REQ, m_slot_id);
    mipcReq->addMipcTlvUint8(MIPC_DATA_GET_5GQOS_REQ_T_CID, aid);
    sp<RfxMipcData> mipcCnf = callToMipcMsgSync(mipcReq);
    if ((mipc_result_const_enum) mipcCnf->getResult() != MIPC_RESULT_SUCCESS) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] MIPC_DATA_GET_5GQOS_REQ return error",
                m_slot_id, __FUNCTION__);
        return false;
    }

    uint16_t rspLen; // should be 1 since we quary with aid.
    rspLen = mipc_msg_get_tlv_num(mipcCnf->getData(), MIPC_DATA_GET_5GQOS_CNF_T_QOS_LIST);
    if (rspLen <= 0) {
        RFX_LOG_W(RFX_LOG_TAG, "[%d][%s] 5G Qos num <= 0, num:%d",
                m_slot_id, __FUNCTION__, rspLen);
        return false;
    }

    mipc_data_5gqos_info_struct4 *fiveGQosInfo
            = (mipc_data_5gqos_info_struct4*) mipc_data_get_5gqos_cnf_get_qos_list(
            mipcCnf->getData(), NULL, 0);
    if (fiveGQosInfo == NULL) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] 5G Qos struct is null, len:%d, index:0",
                m_slot_id, __FUNCTION__, rspLen);
        return false;
    }

    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] 5GQos list len:%d, cid:%d, VQI:%d, "
           "DL_GFBR:%d, DL_MFBR:%d, DL_SAMBR:%d, UL_GFBR:%d, UL_MFBR:%d, UL_SAMBR:%d, "
           "averaging_window:%d",
            m_slot_id, __FUNCTION__, rspLen, fiveGQosInfo->cid, fiveGQosInfo->VQI,
            fiveGQosInfo->DL_GFBR, fiveGQosInfo->DL_MFBR, fiveGQosInfo->DL_SAMBR,
            fiveGQosInfo->UL_GFBR, fiveGQosInfo->UL_MFBR, fiveGQosInfo->UL_SAMBR,
            fiveGQosInfo->Averaging_window);

    if (!m_pPdnManager->isDedicateBearer(aid)) {
        // For default bearer, get qfi by MIPC_DATA_GET_CALL_REQ
        sp<RfxMipcData> qfiReq = RfxMipcData::obtainMipcData(MIPC_DATA_GET_CALL_REQ, m_slot_id);
        qfiReq->addMipcTlvUint8(MIPC_DATA_GET_CALL_REQ_T_ID, aid);
        sp<RfxMipcData> qfiCnf = callToMipcMsgSync(qfiReq);
        if ((mipc_result_const_enum) qfiCnf->getResult() != MIPC_RESULT_SUCCESS) {
            RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] MIPC_DATA_GET_CALL_REQ return error",
                    m_slot_id, __FUNCTION__);
            return false;
        }

        int qfi = (int) qfiCnf->getMipcUint8Val(MIPC_DATA_GET_CALL_CNF_T_QFI, INVALID_VALUE);
        if (qfi == INVALID_VALUE) {
             RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] default bearer, qfi is invalid",
                    m_slot_id, __FUNCTION__);
            return false;
        }

        // update qos for default bearer
        RIL_Qos *pDefaultQos = m_pPdnManager->getDefaultQos(aid);
        RIL_Qos tmpDefaultQos;
        RIL_Qos *pTmpDefaultQos = pDefaultQos != NULL ? pDefaultQos : &tmpDefaultQos;

        pTmpDefaultQos->nr.fiveQi = fiveGQosInfo->VQI;
        pTmpDefaultQos->nr.averagingWindowMs = fiveGQosInfo->Averaging_window;
        pTmpDefaultQos->nr.downlink.guaranteedBitrateKbps = fiveGQosInfo->DL_GFBR;
        pTmpDefaultQos->nr.downlink.maxBitrateKbps = fiveGQosInfo->DL_MFBR;
        pTmpDefaultQos->nr.uplink.guaranteedBitrateKbps = fiveGQosInfo->UL_GFBR;
        pTmpDefaultQos->nr.uplink.maxBitrateKbps = fiveGQosInfo->UL_MFBR;
        pTmpDefaultQos->nr.qfi = qfi;

        if (pDefaultQos == NULL) {
            m_pPdnManager->setDefaultQos(aid, pTmpDefaultQos);
        }
        return true;
    } else {
        // For dedicate bearer, get qfi by MIPC_DATA_GET_DEDICATE_BEARER_INFO_REQ
        sp<RfxMipcData> qfiReq = RfxMipcData::obtainMipcData(
                MIPC_DATA_GET_DEDICATE_BEARER_INFO_REQ, m_slot_id);
        qfiReq->addMipcTlvUint8(MIPC_DATA_GET_DEDICATE_BEARER_INFO_REQ_T_CID, aid);
        sp<RfxMipcData> qfiCnf = callToMipcMsgSync(qfiReq);
        if ((mipc_result_const_enum) qfiCnf->getResult() != MIPC_RESULT_SUCCESS) {
            RFX_LOG_E(RFX_LOG_TAG,
                    "[%d][%s] MIPC_DATA_GET_DEDICATE_BEARER_INFO_REQ return error",
                    m_slot_id, __FUNCTION__);
            return false;
        }

        uint16_t sec_pdp_contx_info_len; // should be 1 since we quary with aid.
        sec_pdp_contx_info_len = mipc_msg_get_tlv_num(qfiCnf->getData(),
                MIPC_DATA_GET_DEDICATE_BEARER_INFO_CNF_T_CONTEXT_LIST);
        if (sec_pdp_contx_info_len <= 0) {
            RFX_LOG_W(RFX_LOG_TAG, "[%d][%s] sec_pdp_contx_info_len <= 0, len:%d",
                    m_slot_id, __FUNCTION__, sec_pdp_contx_info_len);
            return false;
        }
        mipc_data_secondary_pdp_context_info_struct4 *secPdpContxInfo =
                (mipc_data_secondary_pdp_context_info_struct4*) mipc_data_get_dedicate_bearer_info_cnf_get_context_list(
                qfiCnf->getData(), NULL, 0);
        if (secPdpContxInfo == NULL) {
            RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] secPdpContxInfo is NULL, len:%d, index:0",
                    m_slot_id, __FUNCTION__, sec_pdp_contx_info_len);
            return false;
        }

        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] 2nd pdp context info len:%d, cid:%d, qfi:%d",
                m_slot_id, __FUNCTION__, sec_pdp_contx_info_len,
                secPdpContxInfo->cid, secPdpContxInfo->QFI);

        // update qos for dedicate bearer
        RIL_QosSession *pQosSession = m_pPdnManager->getQosSession(aid);
        RIL_QosSession tmpQosSession;
        RIL_QosSession *pTmpQosSession = pQosSession != NULL ? pQosSession : &tmpQosSession;
        pTmpQosSession->qos.nr.fiveQi = fiveGQosInfo->VQI;
        pTmpQosSession->qos.nr.averagingWindowMs = fiveGQosInfo->Averaging_window;
        pTmpQosSession->qos.nr.downlink.guaranteedBitrateKbps = fiveGQosInfo->DL_GFBR;
        pTmpQosSession->qos.nr.downlink.maxBitrateKbps = fiveGQosInfo->DL_MFBR;
        pTmpQosSession->qos.nr.uplink.guaranteedBitrateKbps = fiveGQosInfo->UL_GFBR;
        pTmpQosSession->qos.nr.uplink.maxBitrateKbps = fiveGQosInfo->UL_MFBR;
        pTmpQosSession->qos.nr.qfi= secPdpContxInfo->QFI;
        pTmpQosSession->qosSessionId= secPdpContxInfo->QFI;

        if (pQosSession == NULL) {
            m_pPdnManager->setQosSession(aid, pTmpQosSession);
        }
        return true;
    }
}


bool RmmDcEventHandler::updateQosFilters(int aid) {
    if (aid < 0 || aid >= m_pPdnManager->getPdnTableSize()) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] invalid aid%d", m_slot_id, __FUNCTION__, aid);
        return false;
    }
    if (!m_pPdnManager->isDedicateBearer(aid)) {
        RFX_LOG_E(RFX_LOG_TAG,
            "[%d][%s] donot update QosFilters for non-dedicatebearer, aid:%d",
            m_slot_id, __FUNCTION__, aid);
        return false;
    }

    sp<RfxMipcData> mipcReq = RfxMipcData::obtainMipcData(MIPC_DATA_GET_TFT_REQ, m_slot_id);
    mipcReq->addMipcTlvUint8(MIPC_DATA_GET_TFT_REQ_T_CID, aid);
    sp<RfxMipcData> mipcCnf = callToMipcMsgSync(mipcReq);
    if ((mipc_result_const_enum) mipcCnf->getResult() != MIPC_RESULT_SUCCESS) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] MIPC_DATA_GET_TFT_REQ return error",
                m_slot_id, __FUNCTION__);
        return false;
    }

    int i = 0;
    int n = 0;
    RIL_QosFilter * qf = NULL;
    char v4Mask[MAX_IPV4_ADDRESS_LENGTH] = { 0 };
    char v6Mask[MAX_IPV6_ADDRESS_LENGTH] = { 0 };
    char* tmpAddr = NULL;
    int addrLen = 0;
    int maskLen = 0;
    int tmpLen = 0;
    uint16_t t_resp_len;

    t_resp_len = mipc_msg_get_tlv_num(mipcCnf->getData(), MIPC_DATA_GET_TFT_CNF_T_TFT_LIST);
    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] TFT num:%d, aid:%d", m_slot_id, __FUNCTION__, t_resp_len, aid);
    if (t_resp_len <= 0) {
        return false;
    }

    mipc_data_tft_info_struct4 *tftInfo = NULL;

    // if no QOS session, create it
    if (m_pPdnManager->getQosSession(aid) == NULL) {
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] Qos session of aid%d is null, create it.",
                m_slot_id, __FUNCTION__, aid);
        RIL_QosSession * pQosSession = (RIL_QosSession *) calloc(1, sizeof(RIL_QosSession));
        RFX_ASSERT(pQosSession != NULL);
        m_pPdnManager->setQosSession(aid, pQosSession);
        FREEIF(pQosSession);
    }
    // clear original info if neccesary
    if (m_pPdnManager->getQosSession(aid)->qosFilterCount != 0) {
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] clear original Qos session info for aid%d.",
                m_slot_id, __FUNCTION__, aid);
        for (i = 0; i < m_pPdnManager->getQosSession(aid)->qosFilterCount; i++) {
            qf = &(m_pPdnManager->getQosSession(aid)->qosFilters[i]);
            FREEIF(qf->localAddresses);
            FREEIF(qf->remoteAddresses);
        }
        FREEIF(m_pPdnManager->getQosSession(aid)->qosFilters);
    }
    m_pPdnManager->getQosSession(aid)->qosFilterCount = t_resp_len;
    m_pPdnManager->getQosSession(aid)->qosFilters = (RIL_QosFilter*) calloc(1,
            sizeof(RIL_QosFilter) * t_resp_len);
    RFX_ASSERT(m_pPdnManager->getQosSession(aid)->qosFilters != NULL);
    qf = m_pPdnManager->getQosSession(aid)->qosFilters;
    for (i = 0; i < t_resp_len; i++) {
        tftInfo = (mipc_data_tft_info_struct4*) mipc_data_get_tft_cnf_get_tft_list(
                mipcCnf->getData(), NULL, i);
        if (tftInfo == NULL) {
            RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] tftInfo is NULL, len:%d, index:%d, aid:%d",
                m_slot_id, __FUNCTION__, t_resp_len, i, aid);
            m_pPdnManager->clearQosSession(aid);
            return false;
        }
        // local address
        addrLen = 0;
        if (tftInfo->local_v4_addr_present) {
            addrLen += MAX_IPV4_ADDR_AND_MASK_LENGTH;
        }
        if (tftInfo->local_v6_addr_present) {
            addrLen += MAX_IPV6_ADDR_AND_MASK_LENGTH;
        }
        if (addrLen != 0) {
            qf[i].localAddresses = (char*) calloc(1, sizeof(char)* addrLen);
            RFX_ASSERT(qf[i].localAddresses != NULL);
        }
        if (tftInfo->local_v4_addr_present) {
            tmpAddr = (char*) calloc(1, sizeof(char)* MAX_IPV4_ADDRESS_LENGTH*2);
            RFX_ASSERT(tmpAddr != NULL);
            n = snprintf(tmpAddr, MAX_IPV4_ADDRESS_LENGTH*2, "%d.%d.%d.%d.%d.%d.%d.%d",
                tftInfo->local_v4_addr[0], tftInfo->local_v4_addr[1],
                tftInfo->local_v4_addr[2], tftInfo->local_v4_addr[3],
                tftInfo->local_v4_subnet_mask[0],
                tftInfo->local_v4_subnet_mask[1],
                tftInfo->local_v4_subnet_mask[2],
                tftInfo->local_v4_subnet_mask[3]);
            if (n < 0) {
                RFX_LOG_E(RFX_LOG_TAG,
                        "[%d][%s] fail to snprintf v4 localAddresses and subnet mask",
                        m_slot_id, __FUNCTION__);
            }
            convertAddrAndSubnetMask(qf[i].localAddresses, tmpAddr);
            RFX_LOG_D(RFX_LOG_TAG,
                    "[%d][%s] Local V4 Addr And SubnetMask, before:%s, after:%s",
                    m_slot_id, __FUNCTION__, tmpAddr, qf[i].localAddresses);
            FREEIF(tmpAddr);
        }
        if (tftInfo->local_v6_addr_present) {
            tmpLen = strlen(qf[i].localAddresses);
            if (tmpLen > 0) {
                n = snprintf(qf[i].localAddresses + tmpLen, addrLen - tmpLen, " ");
                if (n < 0) {
                    RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] fail to snprintf v6 qf[i].localAddresses",
                            m_slot_id, __FUNCTION__);
                }
            }
            tmpLen = strlen(qf[i].localAddresses);

            tmpAddr = (char*) calloc(1, sizeof(char)* MAX_IPV6_ADDRESS_LENGTH*2);
            RFX_ASSERT(tmpAddr != NULL);
            n = snprintf(tmpAddr, MAX_IPV6_ADDRESS_LENGTH*2,
                "%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d",
                tftInfo->local_v6_addr[0], tftInfo->local_v6_addr[1],
                tftInfo->local_v6_addr[2], tftInfo->local_v6_addr[3],
                tftInfo->local_v6_addr[4], tftInfo->local_v6_addr[5],
                tftInfo->local_v6_addr[6], tftInfo->local_v6_addr[7],
                tftInfo->local_v6_addr[8], tftInfo->local_v6_addr[9],
                tftInfo->local_v6_addr[10], tftInfo->local_v6_addr[11],
                tftInfo->local_v6_addr[12], tftInfo->local_v6_addr[13],
                tftInfo->local_v6_addr[14], tftInfo->local_v6_addr[15],
                tftInfo->local_v6_subnet_mask[0],
                tftInfo->local_v6_subnet_mask[1],
                tftInfo->local_v6_subnet_mask[2],
                tftInfo->local_v6_subnet_mask[3],
                tftInfo->local_v6_subnet_mask[4],
                tftInfo->local_v6_subnet_mask[5],
                tftInfo->local_v6_subnet_mask[6],
                tftInfo->local_v6_subnet_mask[7],
                tftInfo->local_v6_subnet_mask[8],
                tftInfo->local_v6_subnet_mask[9],
                tftInfo->local_v6_subnet_mask[10],
                tftInfo->local_v6_subnet_mask[11],
                tftInfo->local_v6_subnet_mask[12],
                tftInfo->local_v6_subnet_mask[13],
                tftInfo->local_v6_subnet_mask[14],
                tftInfo->local_v6_subnet_mask[15]);
            if (n < 0) {
                RFX_LOG_E(RFX_LOG_TAG,
                        "[%d][%s] fail to snprintf v6 localAddresses and subnet mask",
                        m_slot_id, __FUNCTION__);
            }

            char* tmpV6Addr = (char*) calloc(1, sizeof(char)* MAX_IPV6_ADDR_AND_MASK_LENGTH);
            RFX_ASSERT(tmpV6Addr != NULL);
            convertAddrAndSubnetMask(tmpV6Addr, tmpAddr);
            RFX_LOG_D(RFX_LOG_TAG,
                    "[%d][%s] Local V6 Addr And SubnetMask, before:%s, after:%s",
                    m_slot_id, __FUNCTION__, tmpAddr, tmpV6Addr);
            int lenV6Addr = strlen(tmpV6Addr);
            n = snprintf(qf[i].localAddresses + tmpLen, addrLen - tmpLen, "%s", tmpV6Addr);
            if (n < 0) {
                RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] fail to snprintf v6 qf[i].localAddresses",
                        m_slot_id, __FUNCTION__);
            }
            FREEIF(tmpV6Addr);
            FREEIF(tmpAddr);
        }

        // remote address
        addrLen = 0;
        if (tftInfo->remote_v4_addr_present) {
            addrLen += MAX_IPV4_ADDR_AND_MASK_LENGTH;
        }
        if (tftInfo->remote_v6_addr_present) {
            addrLen += MAX_IPV6_ADDR_AND_MASK_LENGTH;
        }
        if (addrLen != 0) {
            qf[i].remoteAddresses = (char*) calloc(1, sizeof(char)* addrLen);
            RFX_ASSERT(qf[i].remoteAddresses != NULL);
        }
        if (tftInfo->remote_v4_addr_present) {
            tmpAddr = (char*) calloc(1, sizeof(char)* MAX_IPV4_ADDRESS_LENGTH*2);
            RFX_ASSERT(tmpAddr != NULL);
            n = snprintf(tmpAddr, MAX_IPV4_ADDRESS_LENGTH*2, "%d.%d.%d.%d.%d.%d.%d.%d",
                tftInfo->remote_v4_addr[0], tftInfo->remote_v4_addr[1],
                tftInfo->remote_v4_addr[2], tftInfo->remote_v4_addr[3],
                tftInfo->remote_v4_subnet_mask[0],
                tftInfo->remote_v4_subnet_mask[1],
                tftInfo->remote_v4_subnet_mask[2],
                tftInfo->remote_v4_subnet_mask[3]);
            if (n < 0) {
                RFX_LOG_E(RFX_LOG_TAG,
                        "[%d][%s] fail to snprintf v4 localAddresses and subnet mask",
                        m_slot_id, __FUNCTION__);
            }
            convertAddrAndSubnetMask(qf[i].localAddresses, tmpAddr);
            RFX_LOG_D(RFX_LOG_TAG,
                    "[%d][%s] Remote V4 Addr And SubnetMask, before:%s, after:%s",
                    m_slot_id, __FUNCTION__, tmpAddr, qf[i].localAddresses);
            FREEIF(tmpAddr);
        }
        if (tftInfo->remote_v6_addr_present) {
            tmpLen = strlen(qf[i].remoteAddresses);
            if (tmpLen > 0) {
                n = snprintf(qf[i].remoteAddresses + tmpLen, addrLen - tmpLen, " ");
                if (n < 0) {
                    RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] fail to snprintf v6 qf[i].remoteAddresses",
                            m_slot_id, __FUNCTION__);
                }
            }
            tmpLen = strlen(qf[i].remoteAddresses);

            tmpAddr = (char*) calloc(1, sizeof(char)* MAX_IPV6_ADDRESS_LENGTH*2);
            RFX_ASSERT(tmpAddr != NULL);
            n = snprintf(tmpAddr, MAX_IPV6_ADDRESS_LENGTH*2,
                "%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d",
                tftInfo->remote_v6_addr[0], tftInfo->remote_v6_addr[1],
                tftInfo->remote_v6_addr[2], tftInfo->remote_v6_addr[3],
                tftInfo->remote_v6_addr[4], tftInfo->remote_v6_addr[5],
                tftInfo->remote_v6_addr[6], tftInfo->remote_v6_addr[7],
                tftInfo->remote_v6_addr[8], tftInfo->remote_v6_addr[9],
                tftInfo->remote_v6_addr[10], tftInfo->remote_v6_addr[11],
                tftInfo->remote_v6_addr[12], tftInfo->remote_v6_addr[13],
                tftInfo->remote_v6_addr[14], tftInfo->remote_v6_addr[15],
                tftInfo->remote_v6_subnet_mask[0],
                tftInfo->remote_v6_subnet_mask[1],
                tftInfo->remote_v6_subnet_mask[2],
                tftInfo->remote_v6_subnet_mask[3],
                tftInfo->remote_v6_subnet_mask[4],
                tftInfo->remote_v6_subnet_mask[5],
                tftInfo->remote_v6_subnet_mask[6],
                tftInfo->remote_v6_subnet_mask[7],
                tftInfo->remote_v6_subnet_mask[8],
                tftInfo->remote_v6_subnet_mask[9],
                tftInfo->remote_v6_subnet_mask[10],
                tftInfo->remote_v6_subnet_mask[11],
                tftInfo->remote_v6_subnet_mask[12],
                tftInfo->remote_v6_subnet_mask[13],
                tftInfo->remote_v6_subnet_mask[14],
                tftInfo->remote_v6_subnet_mask[15]);
            if (n < 0) {
                RFX_LOG_E(RFX_LOG_TAG,
                        "[%d][%s] fail to snprintf v6 remoteAddresses and subnet mask",
                        m_slot_id, __FUNCTION__);
            }

            char* tmpV6Addr = (char*) calloc(1, sizeof(char)* MAX_IPV6_ADDR_AND_MASK_LENGTH);
            RFX_ASSERT(tmpV6Addr != NULL);
            convertAddrAndSubnetMask(tmpV6Addr, tmpAddr);
            RFX_LOG_D(RFX_LOG_TAG,
                    "[%d][%s] Remote V6 Addr And SubnetMask, before:%s, after:%s",
                    m_slot_id, __FUNCTION__, tmpAddr, tmpV6Addr);
            int lenV6Addr = strlen(tmpV6Addr);
            n = snprintf(qf[i].remoteAddresses + tmpLen, addrLen - tmpLen, "%s", tmpV6Addr);
            if (n < 0) {
                RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] fail to snprintf v6 qf[i].remoteAddresses",
                        m_slot_id, __FUNCTION__);
            }
            FREEIF(tmpV6Addr);
            FREEIF(tmpAddr);
        }

        // local port
        qf[i].localPort.start = tftInfo->local_port_low;
        qf[i].localPort.end = tftInfo->local_port_high;

        // remote port
        qf[i].remotePort.start = tftInfo->remote_port_low;
        qf[i].remotePort.end = tftInfo->remote_port_high;

        // Qos protocol
        qf[i].protocol = (RIL_QosProtocol) tftInfo->protocol_number_next_header;

        // type of service
        qf[i].typeOfService = tftInfo->tos_mask;

        // ipv6 flow label
        qf[i].ipv6FlowLabel = tftInfo->flow_label;

        // security parameter index
        qf[i].ipSecSpi = tftInfo->ipsec_spi;

        // derection, downlink-0, uplink-1, bidirectional-2
        qf[i].direction = (RIL_QosFilterDirection) tftInfo->direction;

        // precedence
        qf[i].precedence = tftInfo->evaluation_precedence_index;
    }

    // print log
    for (i = 0; i < t_resp_len; i++) {
        tftInfo = (mipc_data_tft_info_struct4*) mipc_data_get_tft_cnf_get_tft_list(
                mipcCnf->getData(), NULL, i);
        if (tftInfo == NULL) {
            RFX_LOG_E(RFX_LOG_TAG,
                "[%d][%s] print log, tftInfo is NULL, len:%d, index:%d, aid:%d",
                m_slot_id, __FUNCTION__, t_resp_len, i, aid);
            m_pPdnManager->clearQosSession(aid);
            continue;
        }
        String8 cnf("");
        cnf.append(String8::format("tftInfo list len:%d,", t_resp_len));
        cnf.append(String8::format("cid:%d,", tftInfo->cid));
        cnf.append(String8::format("packet_filter_id:%d,",
                         tftInfo->packet_filter_identifier));
        cnf.append(String8::format("evaluation_precedence_index:%d,",
                         tftInfo->evaluation_precedence_index));
        cnf.append(String8::format("remote_v4_addr_present:%d,",
                         tftInfo->remote_v4_addr_present));
        cnf.append(String8::format("remote_v6_addr_present:%d,",
                         tftInfo->remote_v6_addr_present));
        cnf.append(String8::format("protocol_number_next_header:%d,",
                         tftInfo->protocol_number_next_header));
        cnf.append(String8::format("tos_traffic_class:%d,",
                         tftInfo->tos_traffic_class));
        cnf.append(String8::format("tos_mask:%d,", tftInfo->tos_mask));
        cnf.append(String8::format("direction:%d,", tftInfo->direction));
        cnf.append(String8::format("NW_packet_filter_id:%d,",
                         tftInfo->NW_packet_filter_identifier));
        cnf.append(String8::format("local_v4_addr_present:%d,",
                         tftInfo->local_v4_addr_present));
        cnf.append(String8::format("local_v6_addr_present:%d,",
                         tftInfo->local_v6_addr_present));
        cnf.append(String8::format("local_port_low:%d,", tftInfo->local_port_low));
        cnf.append(String8::format("local_port_high:%d,", tftInfo->local_port_high));
        cnf.append(String8::format("remote_port_low:%d,", tftInfo->remote_port_low));
        cnf.append(String8::format("remote_port_high:%d,", tftInfo->remote_port_high));
        cnf.append(String8::format("ipsec_spi:%d,", tftInfo->ipsec_spi));
        cnf.append(String8::format("flow_label:%d,", tftInfo->flow_label));
        cnf.append(String8::format("QRI:%d,", tftInfo->QRI));

        if (mIsUserBuild) {
            cnf.append(String8::format("remote_v4_addr:omit for user load, "));
            cnf.append(String8::format("remote_v4_subnet_mask:omit for user load, "));
            cnf.append(String8::format("remote_v6_addr:omit for user load, "));
            cnf.append(String8::format("remote_v6_subnet_mask:omit for user load, "));
            cnf.append(String8::format("local_v4_addr:omit for user load, "));
            cnf.append(String8::format("local_v4_subnet_mask:omit for user load, "));
            cnf.append(String8::format("local_v6_addr:omit for user load, "));
            cnf.append(String8::format("local_v6_subnet_mask:omit for user load, "));
        } else {
            cnf.append(String8::format("remote_v4_addr:%d.%d.%d.%d,",
                    tftInfo->remote_v4_addr[0], tftInfo->remote_v4_addr[1],
                    tftInfo->remote_v4_addr[2], tftInfo->remote_v4_addr[3]));
            cnf.append(String8::format("remote_v4_subnet_mask:%d.%d.%d.%d,",
                    tftInfo->remote_v4_subnet_mask[0], tftInfo->remote_v4_subnet_mask[1],
                    tftInfo->remote_v4_subnet_mask[2], tftInfo->remote_v4_subnet_mask[3]));
            cnf.append(String8::format(
                    "remote_v6_addr:%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d, ",
                    tftInfo->remote_v6_addr[0], tftInfo->remote_v6_addr[1],
                    tftInfo->remote_v6_addr[2], tftInfo->remote_v6_addr[3],
                    tftInfo->remote_v6_addr[4], tftInfo->remote_v6_addr[5],
                    tftInfo->remote_v6_addr[6], tftInfo->remote_v6_addr[7],
                    tftInfo->remote_v6_addr[8], tftInfo->remote_v6_addr[9],
                    tftInfo->remote_v6_addr[10], tftInfo->remote_v6_addr[11],
                    tftInfo->remote_v6_addr[12], tftInfo->remote_v6_addr[13],
                    tftInfo->remote_v6_addr[14], tftInfo->remote_v6_addr[15]));
            cnf.append(String8::format(
                    "remote_v6_subnet_mask:%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d, ",
                    tftInfo->remote_v6_subnet_mask[0], tftInfo->remote_v6_subnet_mask[1],
                    tftInfo->remote_v6_subnet_mask[2], tftInfo->remote_v6_subnet_mask[3],
                    tftInfo->remote_v6_subnet_mask[4], tftInfo->remote_v6_subnet_mask[5],
                    tftInfo->remote_v6_subnet_mask[6], tftInfo->remote_v6_subnet_mask[7],
                    tftInfo->remote_v6_subnet_mask[8], tftInfo->remote_v6_subnet_mask[9],
                    tftInfo->remote_v6_subnet_mask[10], tftInfo->remote_v6_subnet_mask[11],
                    tftInfo->remote_v6_subnet_mask[12], tftInfo->remote_v6_subnet_mask[13],
                    tftInfo->remote_v6_subnet_mask[14], tftInfo->remote_v6_subnet_mask[15]));
            cnf.append(String8::format("local_v4_addr:%d.%d.%d.%d,",
                    tftInfo->local_v4_addr[0], tftInfo->local_v4_addr[1],
                    tftInfo->local_v4_addr[2], tftInfo->local_v4_addr[3]));
            cnf.append(String8::format("local_v4_subnet_mask:%d.%d.%d.%d,",
                    tftInfo->local_v4_subnet_mask[0], tftInfo->local_v4_subnet_mask[1],
                    tftInfo->local_v4_subnet_mask[2], tftInfo->local_v4_subnet_mask[3]));
            cnf.append(String8::format(
                    "local_v6_addr:%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d, ",
                    tftInfo->local_v6_addr[0], tftInfo->local_v6_addr[1],
                    tftInfo->local_v6_addr[2], tftInfo->local_v6_addr[3],
                    tftInfo->local_v6_addr[4], tftInfo->local_v6_addr[5],
                    tftInfo->local_v6_addr[6], tftInfo->local_v6_addr[7],
                    tftInfo->local_v6_addr[8], tftInfo->local_v6_addr[9],
                    tftInfo->local_v6_addr[10], tftInfo->local_v6_addr[11],
                    tftInfo->local_v6_addr[12], tftInfo->local_v6_addr[13],
                    tftInfo->local_v6_addr[14], tftInfo->local_v6_addr[15]));
            cnf.append(String8::format(
                    "local_v6_subnet_mask:%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d, ",
                    tftInfo->local_v6_subnet_mask[0], tftInfo->local_v6_subnet_mask[1],
                    tftInfo->local_v6_subnet_mask[2], tftInfo->local_v6_subnet_mask[3],
                    tftInfo->local_v6_subnet_mask[4], tftInfo->local_v6_subnet_mask[5],
                    tftInfo->local_v6_subnet_mask[6], tftInfo->local_v6_subnet_mask[7],
                    tftInfo->local_v6_subnet_mask[8], tftInfo->local_v6_subnet_mask[9],
                    tftInfo->local_v6_subnet_mask[10], tftInfo->local_v6_subnet_mask[11],
                    tftInfo->local_v6_subnet_mask[12], tftInfo->local_v6_subnet_mask[13],
                    tftInfo->local_v6_subnet_mask[14], tftInfo->local_v6_subnet_mask[15]));
        }
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] tftInfo:%s", m_slot_id, __FUNCTION__, cnf.string());
    }
    return true;
}

int RmmDcEventHandler::convertAddrAndSubnetMask(char* output, const char* input) {
    /* Input(:
           "a1.a2.a3.a4.m1.m2.m3.m4" for IPv4
           or
           "a1.a2.a3.a4.a5.a6.a7.a8.a9.a10.a11.a12.a13.a14.a15.a16.m1.m2.m3.m4.m5.m6.m7
           .m8.m9.m10.m11.m12.m13.m14.m15.m16", for IPv6.
       Output:
           192.0.1.11/16
           2001:db8::1/64
       note: ax and mx are 0-255 numeric, defined in 27.007
    */
    if (output == NULL || input == NULL) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] output or input is NULL", m_slot_id, __FUNCTION__);
        return -1;
    }
    int i = 0;
    int n = 0;
    int inputLen = strlen(input);
    int delimCount = 0;
    int midDelimPos = 0;
    int IpType = -1;
    int addrPartLen = 0;
    int subnetMaskCount = 0;
    char *tempIn = (char*) calloc(1, sizeof(char) * (inputLen+1));
    RFX_ASSERT(tempIn != NULL);
    memcpy(tempIn, input, inputLen);
    char *subNetMask = NULL;
    char *addrV6 = NULL;
    const char dotDelim = '.';
    for (i = 0; tempIn[i] != '\0'; i++) {
        if (dotDelim == tempIn[i]) {
            delimCount++;
        }
    }
    IpType = delimCount == 7 ? IPV4 : (delimCount == 31 ? IPV6 : -1);
    if (IpType == -1) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] illegal format, delimCount:%d",
                m_slot_id, __FUNCTION__, delimCount);
        FREEIF(tempIn);
        return -1;
    }

    midDelimPos = (delimCount +1)/2;
    delimCount = 0;
    for (i = 0; tempIn[i] != '\0'; i++) {
        if (dotDelim == tempIn[i] && ++delimCount == midDelimPos) {
            break;
        }
        addrPartLen++;
    }
    subNetMask = (char*) calloc(1, sizeof(char) * (inputLen-addrPartLen) + 1);
    RFX_ASSERT(subNetMask != NULL);
    memcpy(subNetMask, input+addrPartLen+1, inputLen-addrPartLen-1);

    subnetMaskCount = calculateSubnetMaskNumber(subNetMask);

    memset(tempIn+addrPartLen, 0, inputLen-addrPartLen);
    if (IpType == IPV6) {
        addrV6 = (char*) calloc(1, sizeof(char) * MAX_IPV6_ADDRESS_LENGTH);
        RFX_ASSERT(addrV6 != NULL);
        int isLocal = strncasecmp("254.128", tempIn, strlen("254.128")) == 0 ? 1 : 0;
        convertIpv6Address(addrV6, tempIn, isLocal);
        FREEIF(tempIn);
        tempIn = addrV6;
    }
    if (subnetMaskCount != -1) {
        n = snprintf(output,
                IpType == IPV4 ? MAX_IPV4_ADDR_AND_MASK_LENGTH : MAX_IPV6_ADDR_AND_MASK_LENGTH,
                "%s%s%d", tempIn, "/", subnetMaskCount);
        if (n < 0) {
            RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] fail to snprintf", m_slot_id, __FUNCTION__);
        }
    } else {
        n = snprintf(output,
                IpType == IPV4 ? MAX_IPV4_ADDR_AND_MASK_LENGTH : MAX_IPV6_ADDR_AND_MASK_LENGTH,
                "%s", tempIn);
        if (n < 0) {
            RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] fail to snprintf", m_slot_id, __FUNCTION__);
        }
    }

    FREEIF(tempIn);
    FREEIF(subNetMask);
    return 0;
}

int RmmDcEventHandler::calculateSubnetMaskNumber(char* input) {
    if (input == NULL || strlen(input) == 0) {
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] illegal param", m_slot_id, __FUNCTION__);
        return -1;
    }
    int inputLen = strlen(input);
    char* tmpInput = (char*) calloc(1, sizeof(char) * (inputLen + 1));
    RFX_ASSERT(tmpInput != NULL);
    memcpy(tmpInput, input, inputLen);
    int count = 0;
    int i = 0;
    int bitNum = 7;
    int ipDec = 0;
    long maxValue = 255;
    char* ipStr = NULL;
    char* saveptr = NULL;
    const char* delim = ".";
    ipStr = strtok_r(tmpInput, delim, &saveptr);
    while(ipStr != NULL && strlen(ipStr) > 0){
        ipDec = atoi(ipStr);
        if (ipDec > maxValue) {
            FREEIF(tmpInput);
            return -1;
        }
        for (i = bitNum; i >= 0 && ipDec/(1 << i) >= 1; ipDec -= (1<<i), count++, i--) {}
        ipStr = strtok_r(NULL, delim, &saveptr);
    }
    FREEIF(tmpInput);
    return (count > 0) ? count : -1;
}

/*
 * For default bearer, update Qos based on RAT
 * For dedicate bearer, update Qos Session
 */
bool RmmDcEventHandler::updateQosInformation(int aid, bool isDedicateBearer) {
    if (aid < 0 || aid >= m_pPdnManager->getPdnTableSize()) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] invalid aid%d", m_slot_id, __FUNCTION__, aid);
        return false;
    }

    int rat = getCurrentRat();
    // update Qos
    if (rat == RADIO_TECH_LTE || rat == RADIO_TECH_LTE_CA) {
        if (!updateEpsQos(aid)) {
            RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] updateEpsQos failed, aid%d",
                    m_slot_id, __FUNCTION__, aid);
            return false;
        }
    } else if (rat == RADIO_TECH_NR) {
        if (!updateNrQos(aid)) {
            RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] updateNrQos failed, aid%d",
                    m_slot_id, __FUNCTION__, aid);
            return false;
        }
    } else {
        RFX_LOG_W(RFX_LOG_TAG,
               "[%d][%s] Rat is neither 4G nor 5G, donot set QosInfo",
               m_slot_id, __FUNCTION__);
        return false;
    }

    // update dedicate bearer QosFilters
    // From perspective of 3GPP spec, Qos Session(qosSessionId,Qos, Qos Filter)
    // is exist for 2G/3G/4G/5G. But, currently AOSP only design Qos struct for
    // 4G and 5G, so we only need update Qos session info for 4G and 5G.
    if (isDedicateBearer && (rat == RADIO_TECH_LTE || rat == RADIO_TECH_LTE_CA
            || rat == RADIO_TECH_NR)) {
        return updateQosFilters(aid);
    }
    return false;
}

void RmmDcEventHandler::requestSetFdMode(const sp<RfxMclMessage>& msg) {
    int* pReqInt = (int*)msg->getData()->getData();
    sp<RfxMclMessage> response;

    if (pReqInt == NULL) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] Weird, request msg null", m_slot_id, __FUNCTION__);
        response = RfxMclMessage::obtainResponse(
                msg->getId(), RIL_E_SUCCESS, RfxVoidData(), msg, false);
        responseToTelCore(response);
        return;
    }

    int result = 0;
    int argsNum = pReqInt[0];
    if (argsNum == 1) mCurrentFdState = pReqInt[1];

    char propertyValue[RFX_PROPERTY_VALUE_MAX] = {0};
    rfx_property_get(PROPERTY_RIL_FD_MODE, propertyValue, "0");
    if (atoi(propertyValue) == 0) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] initialize not finish", m_slot_id, __FUNCTION__);
        response = RfxMclMessage::obtainResponse(
                msg->getId(), RIL_E_SUCCESS, RfxVoidData(), msg, false);
        responseToTelCore(response);
        return;
    }

    if (argsNum == 1) {
        result = handleFastdormancyCommand(pReqInt[1], -1, -1);
    } else if (argsNum == 2) {
        result = handleFastdormancyCommand(pReqInt[1], pReqInt[2], -1);
    } else if (argsNum == 3) {
        rfx_property_set(PROPERTY_FD_TIMER[pReqInt[2]], String8::format("%d", pReqInt[3]).string());
        result = handleFastdormancyCommand(pReqInt[1], pReqInt[2], pReqInt[3]);
    } else {
        RFX_LOG_E(RFX_LOG_TAG, "Should never be here!");
    }

    response = RfxMclMessage::obtainResponse(
            msg->getId(), result == 1 ? RIL_E_SUCCESS : RIL_E_MODEM_ERR, RfxVoidData(), msg, false);

    responseToTelCore(response);
}

void RmmDcEventHandler::requestSetLinkCapacityReportingCriteria(const sp<RfxMclMessage>& msg) {
    RIL_LinkCapacityReportingCriteria* data = NULL;
    int numOfDlThreshold = 0;
    int numOfUlThreshold = 0;

    sp<RfxMclMessage> pMclResponse;
    sp<RfxMipcData> mipcMsg;
    int* thresholdDlKbpsNumber = NULL;
    int* thresholdUlKbpsNumber = NULL;

    data = (RIL_LinkCapacityReportingCriteria*)msg->getData()->getData();
    if (data == NULL) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] data is null, return!", m_slot_id, __FUNCTION__);
        pMclResponse = RfxMclMessage::obtainResponse(RIL_E_NO_SUCH_ENTRY, RfxVoidData(), msg);
        responseToTelCore(pMclResponse);
        return;
    }

    // <mode>[,<histerisis_millis>,<dl_hysterisis_kbps>,<ul_hysterisis_kbps>,
    // <num_of_dl_threshold>[,<dl_threshold1>,<dl_threshold2>,<dl_threshold3>,...],
    // <num_of_ul_threshold>[,<ul_threshold1>,<ul_threshold2>,<ul_threshold3>,...],<RAT>]
    mipcMsg = RfxMipcData::obtainMipcData(
            MIPC_DATA_SET_LINK_CAPACITY_REPORTING_CRITERIA_REQ, m_slot_id);
    mipcMsg->addMipcTlvUint8(
            MIPC_DATA_SET_LINK_CAPACITY_REPORTING_CRITERIA_REQ_T_MODE, MIPC_DATA_LCE_MODE_SET);
    mipcMsg->addMipcTlvUint32(
            MIPC_DATA_SET_LINK_CAPACITY_REPORTING_CRITERIA_REQ_T_HYSTERESIS_MS, data->hysteresisMs);
    mipcMsg->addMipcTlvUint32(
            MIPC_DATA_SET_LINK_CAPACITY_REPORTING_CRITERIA_REQ_T_HYSTERESIS_DL_KBPS,
            data->hysteresisDlKbps);
    mipcMsg->addMipcTlvUint32(
            MIPC_DATA_SET_LINK_CAPACITY_REPORTING_CRITERIA_REQ_T_HYSTERESIS_UL_KBPS,
            data->hysteresisUlKbps);

    numOfDlThreshold = data->thresholdDlKbpsNumber > MAX_LCE_THRESHOLD_NUMBER
            ? MAX_LCE_THRESHOLD_NUMBER
            : data->thresholdDlKbpsNumber;
    thresholdDlKbpsNumber = (int*)calloc(numOfDlThreshold, sizeof(int));
    if (thresholdDlKbpsNumber == NULL) return;
    memcpy(thresholdDlKbpsNumber, data->thresholdDlKbpsList, numOfDlThreshold * sizeof(int));

    mipcMsg->addMipcTlvUint8(
            MIPC_DATA_SET_LINK_CAPACITY_REPORTING_CRITERIA_REQ_T_THRESHOLD_DL_KBPS_NUM,
            numOfDlThreshold);
    mipcMsg->addMipcTlv(
            MIPC_DATA_SET_LINK_CAPACITY_REPORTING_CRITERIA_REQ_T_THRESHOLD_DL_KBPS_LIST,
            sizeof(int) * numOfDlThreshold, thresholdDlKbpsNumber);

    numOfUlThreshold = data->thresholdUlKbpsNumber > MAX_LCE_THRESHOLD_NUMBER
            ? MAX_LCE_THRESHOLD_NUMBER
            : data->thresholdUlKbpsNumber;
    thresholdUlKbpsNumber = (int*)calloc(numOfUlThreshold, sizeof(int));
    if (thresholdUlKbpsNumber == NULL) {
        FREEIF(thresholdDlKbpsNumber);
        return;
    }
    memcpy(thresholdUlKbpsNumber, data->thresholdUlKbpsList, numOfUlThreshold * sizeof(int));

    mipcMsg->addMipcTlvUint8(
            MIPC_DATA_SET_LINK_CAPACITY_REPORTING_CRITERIA_REQ_T_THRESHOLD_UL_KBPS_NUM,
            numOfUlThreshold);
    mipcMsg->addMipcTlv(
            MIPC_DATA_SET_LINK_CAPACITY_REPORTING_CRITERIA_REQ_T_THRESHOLD_UL_KBPS_LIST,
            sizeof(int) * numOfUlThreshold, thresholdUlKbpsNumber);

    mipcMsg->addMipcTlvUint32(
            MIPC_DATA_SET_LINK_CAPACITY_REPORTING_CRITERIA_REQ_T_ACCESS_NETWORK,
            data->accessNetwork);

    callToMipcMsgAsync(msg, mipcMsg);

    pMclResponse = RfxMclMessage::obtainResponse(RIL_E_SUCCESS, RfxVoidData(), msg);
    responseToTelCore(pMclResponse);

    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] finish", m_slot_id, __FUNCTION__);
    FREEIF(thresholdDlKbpsNumber);
    FREEIF(thresholdUlKbpsNumber);
}

void RmmDcEventHandler::handleLinkCapacityEstimate(const sp<RfxMclMessage>& msg) {
    int* data = (int*)msg->getData()->getData();
    if (data == NULL) return;

    RIL_LinkCapacityEstimate* response = (RIL_LinkCapacityEstimate*)calloc(1,
            sizeof(RIL_LinkCapacityEstimate));
    if (response == NULL) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] calloc response fail", m_slot_id, __FUNCTION__);
        return;
    }

    response->downlinkCapacityKbps = data[0];
    response->uplinkCapacityKbps = data[1];
    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] downlinkCapacityKbps=%d uplinkCapacityKbps=%d", m_slot_id,
            __FUNCTION__, response->downlinkCapacityKbps, response->uplinkCapacityKbps);

    sp<RfxMclMessage> urcMsg = RfxMclMessage::obtainUrc(RFX_MSG_URC_LINK_CAPACITY_ESTIMATE,
            m_slot_id, RfxLinkCapacityEstimateData(response, sizeof(RIL_LinkCapacityEstimate)));
    responseToTelCore(urcMsg);
    FREEIF(response);
}

void RmmDcEventHandler::handleNetworkRejectCause(const sp<RfxMclMessage>& msg) {
    int* data = (int*)msg->getData()->getData();
    if (data == NULL) return;

    int response[COUNT_NETWORK_REJECT_CAUSE] = {0};
    memcpy(response, data, COUNT_NETWORK_REJECT_CAUSE * sizeof(int));

    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] %d,%d,%d",
            m_slot_id, __FUNCTION__, response[0], response[1], response[2]);
    sp<RfxMclMessage> urcMsg = RfxMclMessage::obtainUrc(RFX_MSG_URC_NETWORK_REJECT_CAUSE, m_slot_id,
            RfxIntsData(response, COUNT_NETWORK_REJECT_CAUSE));
    responseToTelCore(urcMsg);
}

void RmmDcEventHandler::handleSendDeviceStateRequest(const sp<RfxMclMessage>& msg) {
    int *pReqInt = (int *)msg->getData()->getData();

    // Only handle LOW_DATA_EXPECTED
    if (pReqInt[0] == FASTDORMANCY_LOW_DATA_EXPECTED) {
        int settings[FASTDORMANCY_PARAMETER_LENGTH] = {0};
        settings[0] = 1;          // args Num
        settings[1] = pReqInt[1]; // state
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] state: %d", m_slot_id, __FUNCTION__, settings[1]);

        RfxIntsData data(settings, FASTDORMANCY_PARAMETER_LENGTH);
        sp<RfxMclMessage> request = RfxMclMessage::obtainRequest(msg->getId(),
                &data, msg->getSlotId(), msg->getToken(),
                msg->getSendToMainProtocol(), msg->getRilToken(),
                msg->getTimeStamp(), msg->getAddAtFront());
        requestSetFdMode(request);
    } else {
        sp<RfxMclMessage> response = RfxMclMessage::obtainResponse(msg->getId(),
                RIL_E_REQUEST_NOT_SUPPORTED, RfxVoidData(), msg, false);
        responseToTelCore(response);
    }
}

void RmmDcEventHandler::handleResponseFilterChanged(const sp<RfxMclMessage>& msg) {
    int *data = (int *)msg->getData()->getData();
    if (data == NULL) return;

    sp<RfxMipcData> mipcMsg = RfxMipcData::obtainMipcData(
            MIPC_DATA_SET_LINK_CAPACITY_REPORTING_CRITERIA_REQ, m_slot_id);

    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] filter: %d", m_slot_id, __FUNCTION__, data[0]);
    if ((data[0] & LINK_CAPACITY_ESTIMATE) == LINK_CAPACITY_ESTIMATE) {
        mipcMsg->addMipcTlvUint8(
                MIPC_DATA_SET_LINK_CAPACITY_REPORTING_CRITERIA_REQ_T_MODE,
                MIPC_DATA_LCE_MODE_ENABLE);
    } else {
        mipcMsg->addMipcTlvUint8(
                MIPC_DATA_SET_LINK_CAPACITY_REPORTING_CRITERIA_REQ_T_MODE,
                MIPC_DATA_LCE_MODE_DISABLE);
    }

    callToMipcMsgAsync(msg, mipcMsg);
}


void RmmDcEventHandler::initializeFastDormancy() {
    // Fast Dormancy is only available on 3G protocol set, so when maxRadio is 2G, disable it.
    int radioCapability =
            getMclStatusManager(m_slot_id)->getIntValue(RFX_STATUS_KEY_SLOT_CAPABILITY, 0);
    int maxCapability = RmmCapabilitySwitchUtil::getMaxRadioGeneration(radioCapability);

    if (maxCapability == RADIO_GENERATION_2G) {
        rfx_property_set(PROPERTY_RIL_FD_MODE, "0");
        return;
    }

    char propertyValue[RFX_PROPERTY_VALUE_MAX] = {0};

    sp<RfxMipcData> mipcMsg = RfxMipcData::obtainMipcData(MIPC_NW_GET_IDLE_HINT_REQ, m_slot_id);
    sp<RfxMipcData> mipcCnf = callToMipcMsgSync(mipcMsg);
    if (mipcCnf->getResult() != MIPC_RESULT_SUCCESS) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] MIPC_NW_GET_IDLE_HINT_REQ error", m_slot_id, __FUNCTION__);
        return;
    }

    // Set PROPERTY_RIL_FD_MODE. Framework can query this to know if AP side is necessary to
    // execute FD or not.
    rfx_property_set(PROPERTY_RIL_FD_MODE, "1");

    // timerId=0: Screen Off + Legacy FD
    memset(propertyValue, 0, sizeof(propertyValue));
    rfx_property_get(PROPERTY_FD_SCREEN_OFF_TIMER, propertyValue, DEFAULT_FD_SCREEN_OFF_TIMER);
    handleFastdormancyCommand(MIPC_NW_FAST_DORMANCY_SET_TIMER, 0, (int)(atof(propertyValue)));

    // timerId=2: Screen Off + R8 FD
    memset(propertyValue, 0, sizeof(propertyValue));
    rfx_property_get(
            PROPERTY_FD_SCREEN_OFF_R8_TIMER, propertyValue, DEFAULT_FD_SCREEN_OFF_R8_TIMER);
    handleFastdormancyCommand(MIPC_NW_FAST_DORMANCY_SET_TIMER, 2, (int)(atof(propertyValue)));

    // timerId=1: Screen On + Legacy FD
    memset(propertyValue, 0, sizeof(propertyValue));
    rfx_property_get(PROPERTY_FD_SCREEN_ON_TIMER, propertyValue, DEFAULT_FD_SCREEN_ON_TIMER);
    handleFastdormancyCommand(MIPC_NW_FAST_DORMANCY_SET_TIMER, 1, (int)(atof(propertyValue)));

    // timerId=3: Screen On + R8 FD
    memset(propertyValue, 0, sizeof(propertyValue));
    rfx_property_get(
            PROPERTY_FD_SCREEN_ON_R8_TIMER, propertyValue, DEFAULT_FD_SCREEN_ON_R8_TIMER);
    handleFastdormancyCommand(MIPC_NW_FAST_DORMANCY_SET_TIMER, 3, (int)(atof(propertyValue)));

    memset(propertyValue, 0, sizeof(propertyValue));
    rfx_property_get(PROPERTY_FD_ON_ONLY_R8_NETWORK, propertyValue, "0");
    if (atoi(propertyValue) == 1) {
        disableLegacyFastDormancy();
    }

    handleFastdormancyCommand(mCurrentFdState, -1, -1);
}

void RmmDcEventHandler::disableLegacyFastDormancy() {
    int mode = 0;
    int parameter = 0;

    sp<RfxMipcData> mipcMsg = RfxMipcData::obtainMipcData(MIPC_NW_GET_PS_TEST_MODE_REQ, m_slot_id);
    sp<RfxMipcData> mipcCnf = callToMipcMsgSync(mipcMsg);
    if (mipcCnf->getResult() != MIPC_RESULT_SUCCESS) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] MIPC_NW_GET_PS_TEST_MODE_REQ error", m_slot_id,
                __FUNCTION__);
        return;
    }

    mode = mipcCnf->getMipcUint8Val(MIPC_NW_GET_PS_TEST_MODE_CNF_T_MODE, 0);
    parameter = mipcCnf->getMipcUint32Val(MIPC_NW_GET_PS_TEST_MODE_CNF_T_PROFILE, 0);

    sp<RfxMipcData> mipcMsgDisable =
            RfxMipcData::obtainMipcData(MIPC_NW_SET_PS_TEST_MODE_REQ, m_slot_id);
    mipcMsgDisable->addMipcTlvUint8(MIPC_NW_SET_PS_TEST_MODE_REQ_T_MODE, mode);
    mipcMsgDisable->addMipcTlvUint32(MIPC_NW_SET_PS_TEST_MODE_REQ_T_PROFILE,
            (parameter & FASTDORMANCY_ON) | FASTDORMANCY_LEGACY_OFF);

    mipc_msg_async(mipcMsgDisable->getData(), NULL, NULL);
}

/// Multi-SIM Start

// Support requirements to do ps attach or ps&cs attach base on the parameter.
// This function is used only for Java Framework to trigger data-stall mechanism.
// Detach request and attach request will be always executed successively, Attach
// request is always after detach request.
void RmmDcEventHandler::handleDcAttachDetachRequest(const sp<RfxMclMessage>& msg, int type) {
    sp<RfxMclMessage> response;
    sp<RfxMipcData> mipcMsg;
    int* pReqInt = (int*)msg->getData()->getData();
    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] command=%d type=%d",
            m_slot_id, __FUNCTION__, pReqInt[0], type);

    if (pReqInt[0] == 0) {
        mipcMsg = RfxMipcData::obtainMipcData(MIPC_NW_SET_PS_REQ, m_slot_id);
        mipcMsg->addMipcTlvUint8(MIPC_NW_SET_PS_REQ_T_CTRL_MODE, MIPC_NW_PS_CTRL_MODE_EGTYPE);
        mipcMsg->addMipcTlvUint8(MIPC_NW_SET_PS_REQ_T_ACTION,
                type == DATA_CONNECTION_ATTACH ? MIPC_NW_PS_ATTACH : MIPC_NW_PS_DETACH);
        callToMipcMsgSync(mipcMsg);
    } else {
        mipcMsg = RfxMipcData::obtainMipcData(MIPC_NW_SET_RADIO_STATE_REQ, m_slot_id);
        mipcMsg->addMipcTlvUint8(MIPC_NW_SET_RADIO_STATE_REQ_T_SW_STATE,
                type == DATA_CONNECTION_ATTACH ? MIPC_NW_RADIO_STATE_ON : MIPC_NW_RADIO_STATE_OFF);
        mipcMsg->addMipcTlvUint8(
                MIPC_NW_SET_RADIO_STATE_REQ_T_CAUSE, MIPC_NW_RADIO_STATE_CAUSE_UNSPECIFIED);
        callToMipcMsgSync(mipcMsg);
    }

    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS, RfxVoidData(), msg);
    responseToTelCore(response);
}
/// Multi-SIM end @}

void RmmDcEventHandler::handleResetMdDataRetryCountResponse(const sp<RfxMclMessage>& msg) {
    RfxMipcData* mipcData = msg->getMipcData();
    RFX_LOG_D(RFX_LOG_TAG, "[%s] msgId:%d, slot:%d", __FUNCTION__, msg->getId(), msg->getSlotId());
    if (mipcData == NULL) {
        RFX_LOG_E(RFX_LOG_TAG, "[%s] mipc data is null!", __FUNCTION__);
        return;
    }
    RFX_LOG_D(RFX_LOG_TAG, "[%s] MipcMsgId:%d, MipcSlotId:%d", __FUNCTION__,
            mipcData->getMipcMsgId(), mipcData->getMipcSlotId());
    if (mipcData->getResult() != MIPC_RESULT_SUCCESS) {
        RFX_LOG_E(RFX_LOG_TAG, "[%s] failed!! err code:%d", __FUNCTION__, mipcData->getResult());
    }
}

void RmmDcEventHandler::handleDsdaStateChanged(const sp<RfxMclMessage>& msg) {
    int* data = (int*)msg->getData()->getData();
    if (data == NULL) return;
    char feature[] = "GEMINI_DR_DSDA";

    int dsdaMode = 0;
    if (data[1] == MIPC_DSDA_STATE_TYPE_ACTIVE || data[1] == MIPC_DSDA_STATE_TYPE_POSSIBLE) {
        dsdaMode = 1;
    }

    int drDsdaMode = (getFeatureVersion(feature) >= 1) ? data[2] : DRDSDA_STATUS_NOT_SUPPORT;
    int response = (data[1] + DSDA_BASE_NEW_VERSION) * 100 + drDsdaMode * 10 + data[3];

    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] response=%d", m_slot_id, __FUNCTION__, response);
    getNonSlotMclStatusManager()->setIntValue(RFX_STATUS_DSDA_MODE, response);
    sp<RfxMclMessage> urc = RfxMclMessage::obtainUrc(RFX_MSG_UNSOL_ON_DSDA_CHANGED,
            m_slot_id, RfxIntsData(&response, 1));
    responseToTelCore(urc);
}

void RmmDcEventHandler::handleEnableDsdaIndication(const sp<RfxMclMessage>& msg) {
    int* data = (int*)msg->getData()->getData();
    if (data == NULL) return;

    const int dsdaInd[] = {
        MIPC_DATA_DSDA_STATE_IND
    };

    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] enable=%d", m_slot_id, __FUNCTION__, data[0]);
    if (data[0] == 0) {
        unregisterToHandleMipcURC(dsdaInd, 1);
    } else {
        registerToHandleMipcURC(dsdaInd, 1);
    }

    sp<RfxMclMessage> response = RfxMclMessage::obtainResponse(msg->getId(),
            RIL_E_SUCCESS, RfxVoidData(), msg, false);
    responseToTelCore(response);
}

void RmmDcEventHandler::handleGetDsdaStatus(const sp<RfxMclMessage>& msg) {
    sp<RfxMipcData> mipcMsg = RfxMipcData::obtainMipcData(MIPC_DATA_GET_DSDA_STATE_REQ, m_slot_id);
    callToMipcMsgAsync(msg, mipcMsg);
}

void RmmDcEventHandler::handleDsdaStatusResponse(const sp<RfxMclMessage>& msg) {
    char feature[] = "GEMINI_DR_DSDA";

    int dsdaMode = 0;
    int dsdaState = (int)msg->getMipcData()->getMipcUint8Val(
            MIPC_DATA_GET_DSDA_STATE_CNF_T_DSDA_STATE, 0);
    if (dsdaState == MIPC_DSDA_STATE_TYPE_ACTIVE || dsdaState == MIPC_DSDA_STATE_TYPE_POSSIBLE) {
        dsdaMode = 1;
    }

    int drDsda = (int)msg->getMipcData()->getMipcUint8Val(
            MIPC_DATA_DSDA_STATE_IND_T_IS_DR_DSDA, 0);
    int drDsdsState = (int)msg->getMipcData()->getMipcUint8Val(
            MIPC_DATA_DSDA_STATE_IND_T_IS_DR_DSDS, 0);
    int drDsdaState = (getFeatureVersion(feature) >= 1) ? drDsda : DRDSDA_STATUS_NOT_SUPPORT;
    int response = (dsdaState + DSDA_BASE_NEW_VERSION) * 100 + drDsdaState * 10 + drDsdsState;

    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] response=%d", m_slot_id, __FUNCTION__, response);
    getNonSlotMclStatusManager()->setIntValue(RFX_STATUS_DSDA_MODE, response);
    sp<RfxMclMessage> mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
            RIL_E_SUCCESS, RfxIntsData(&response, 1), msg, false);
    responseToTelCore(mclResponse);
}

void RmmDcEventHandler::handleUpdateDataRatRequest(const sp<RfxMclMessage>& msg) {
    int* param = (int*)(msg->getData()->getData());
    int oldRat = param[0];
    int newRat = param[1];
    int needUpdateQos = 0;

    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] oldRat=%d, newRat=%d",
            m_slot_id, __FUNCTION__, oldRat, newRat);
    // rat changed between 4G and 5G, update Qos
    if (((oldRat == RADIO_TECH_LTE || oldRat == RADIO_TECH_LTE_CA) && newRat == RADIO_TECH_NR)
            || (oldRat == RADIO_TECH_NR
                    && (newRat == RADIO_TECH_LTE || newRat == RADIO_TECH_LTE_CA))) {
        needUpdateQos = 1;
    }

    int tableSize = m_pPdnManager->getPdnTableSize();
    for (int i = 0; i < tableSize; i++) {
        if (m_pPdnManager->getPdnActiveStatus(i) != DATA_STATE_ACTIVE) continue;
        m_pPdnManager->setAccessNetwork(m_pPdnManager->getAid(i),
                RmmDcUtility::radioTechToAccessNw((RIL_RadioTechnology)getCurrentRat()));
        if (needUpdateQos == 1) {
            updateQosInformation(i, m_pPdnManager->isDedicateBearer(i));
        }
    }

    if (needUpdateQos == 1) {
        // Here we need a non-request message, so that we can response data call list
        // as a urc
        sp<RfxMclMessage> urcMsg = RfxMclMessage::obtainUrc(
                RFX_MSG_URC_DATA_CALL_LIST_CHANGED, m_slot_id, RfxVoidData());
        requestOrSendDataCallList(urcMsg);
    }

    sp<RfxMclMessage> responseMsg = RfxMclMessage::obtainResponse(RIL_E_SUCCESS,
            RfxVoidData(), msg);
    responseToTelCore(responseMsg);
}

void RmmDcEventHandler::updateTdInfo(int aid) {
    if (getCurrentRat() != RADIO_TECH_NR) {
        return;
    }
    if (aid < 0 || aid >= m_pPdnManager->getPdnTableSize()) {
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] invalid param aid:%d",
            m_slot_id, __FUNCTION__, aid);
        return;
    }

    sp<RfxMipcData> mipcReq = RfxMipcData::obtainMipcData(MIPC_DATA_GET_URSP_ROUTE_PROFILE_REQ,
            m_slot_id);
    mipcReq->addMipcTlvUint32(MIPC_DATA_GET_URSP_ROUTE_PROFILE_REQ_T_ID, aid);
    sp<RfxMipcData> mipcCnf = callToMipcMsgSync(mipcReq);
    if ((mipc_result_const_enum) mipcCnf->getResult() != MIPC_RESULT_SUCCESS) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] MIPC_DATA_GET_URSP_ROUTE_PROFILE_REQ return error",
                m_slot_id, __FUNCTION__);
        return;
    }

    int receivedTdCount = mipc_data_get_ursp_route_profile_cnf_get_route_supp_profile_list_num(
            mipcCnf->getData(), 0);
    if (receivedTdCount <= 0) {
        RFX_LOG_W(RFX_LOG_TAG, "[%d][%s] received TD count is %d, return.",
                m_slot_id, __FUNCTION__, receivedTdCount);
        return;
    }

    RIL_TrafficDescriptor *tds = (RIL_TrafficDescriptor*)calloc(receivedTdCount,
            sizeof(RIL_TrafficDescriptor));
    RFX_ASSERT(tds != NULL);
    uint16_t retLen = 0;
    int validTdCount = 0;
    for (int i = 0; i < receivedTdCount; i++) {
        mipc_ursp_get_route_supp_profile_ind_struct_struct4 *retRP =
                mipc_data_get_ursp_route_profile_cnf_get_route_supp_profile_list(
                mipcCnf->getData(), &retLen, i);
        if (retRP != NULL && retLen > 0) {
            if (retRP->traffic_desc.dnn_len <= 0 && retRP->traffic_desc.app_id_len <= 0) {
                // Adjust td count.
                // Since current android version only care about DNN and OS APP ID of a TD,
                // if a TD has no DNN and OS APP ID, ignore it.
                RFX_LOG_W(RFX_LOG_TAG, "[%d][%s] ignore TD that has no DNN and APP ID.",
                        m_slot_id, __FUNCTION__);
                continue;
            }
            // dnn
            if (retRP->traffic_desc.dnn_len > 0) {
                asprintf(&(tds[validTdCount].dnn), "%s", retRP->traffic_desc.dnn);
            }
            // osAppId
            if (retRP->traffic_desc.app_id_len > 0) {
                tds[validTdCount].osAppIdLen = OS_ID_UUID_LEN + 1 + retRP->traffic_desc.app_id_len;
                tds[validTdCount].osAppId =
                        (uint8_t*)calloc(tds[validTdCount].osAppIdLen, sizeof(uint8_t));
                RFX_ASSERT(tds[validTdCount].osAppId != NULL);
                memcpy(tds[validTdCount].osAppId, retRP->traffic_desc.os_id, OS_ID_UUID_LEN);
                tds[validTdCount].osAppId[APP_ID_LEN_INDEX] = retRP->traffic_desc.app_id_len;
                memcpy(&tds[validTdCount].osAppId[APP_ID_INDEX], retRP->traffic_desc.app_id,
                        retRP->traffic_desc.app_id_len);
                RFX_LOG_D(RFX_LOG_TAG,
                        "[%d][%s] OS APP ID: %02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x-%d-%s",
                        m_slot_id, __FUNCTION__,
                        tds[validTdCount].osAppId[0], tds[validTdCount].osAppId[1], tds[validTdCount].osAppId[2], tds[validTdCount].osAppId[3],
                        tds[validTdCount].osAppId[4], tds[validTdCount].osAppId[5], tds[validTdCount].osAppId[6], tds[validTdCount].osAppId[7],
                        tds[validTdCount].osAppId[8], tds[validTdCount].osAppId[9], tds[validTdCount].osAppId[10], tds[validTdCount].osAppId[11],
                        tds[validTdCount].osAppId[12], tds[validTdCount].osAppId[13], tds[validTdCount].osAppId[14], tds[validTdCount].osAppId[15],
                        tds[validTdCount].osAppId[APP_ID_LEN_INDEX],
                        (char*)(&tds[validTdCount].osAppId[APP_ID_INDEX]));
            }
            validTdCount++;
        }
    }
    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] received TD count is %d, valide TD counst is %d.",
            m_slot_id, __FUNCTION__, receivedTdCount, validTdCount);
    m_pPdnManager->clearTds(aid);
    m_pPdnManager->setTds(aid, validTdCount, tds);
    for (int i = 0; i < receivedTdCount; i++) {
        FREEIF(tds[i].dnn);
        FREEIF(tds[i].osAppId);
    }
    FREEIF(tds);
}

void RmmDcEventHandler::handleUrspReevaluate(const sp<RfxMclMessage>& msg) {
    int *pData = (int *)msg->getData()->getData();
    if (pData != NULL && pData[0] > 0) {
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] cid list length: %d", m_slot_id, __FUNCTION__,
                pData[0]);
        for (int i = 1; i < pData[0]; i++) {
            updateTdInfo(i);
        }
        requestOrSendDataCallList(msg);
    }
}

void RmmDcEventHandler::handleGetSlicingConfig(const sp<RfxMclMessage>& msg) {
    // Get PLMN from registered network
    String8 plmn = getMclStatusManager()->
            getString8Value(RFX_STATUS_KEY_OPERATOR, String8("0"));
    if (plmn.length() < MIN_PLMN_LENTH) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s]: Invalid PLMN: %s", m_slot_id, __FUNCTION__,
                plmn.string());
        return;
    }
    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] plmn: %s", m_slot_id, __FUNCTION__, plmn.string());
    // Get URSP rules using async way
    sp<RfxMipcData> mipcMsg = RfxMipcData::obtainMipcData(MIPC_DATA_GET_URSP_UE_POLICY_REQ,
            m_slot_id);
    mipc_data_get_ursp_ue_policy_req_add_plmn_id(mipcMsg->getData(), plmn.length(),
            (uint8_t*)plmn.string());
    callToMipcMsgAsync(msg, mipcMsg);
}

void RmmDcEventHandler::handleGetSlicingConfigResponse(const sp<RfxMclMessage>& msg) {
    RIL_SlicingConfig sc;
    memset(&sc, 0, sizeof(sc));

    // Get PLMN from SIM card
    String8 plmn = getMclStatusManager()->
            getString8Value(RFX_STATUS_KEY_UICC_GSM_NUMERIC, String8("0"));
    if (plmn.length() < MIN_PLMN_LENTH) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s]: Invalid PLMN: %s", m_slot_id, __FUNCTION__,
                plmn.string());
        sp<RfxMclMessage> response = RfxMclMessage::obtainResponse(msg->getId(),
            RIL_E_SUCCESS, RfxSlicingConfigResponseData(&sc, sizeof(RIL_SlicingConfig)),
            msg, false);
        responseToTelCore(response);
        return;
    }

    // URSP rule response
    int ruleNum = (int)mipc_data_get_ursp_ue_policy_cnf_get_rule_num(
            msg->getMipcData()->getData(), 0);
    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] URSP rule number: %d", m_slot_id, __FUNCTION__, ruleNum);
    if (ruleNum > 0) {
        sc.ruleCount = ruleNum;
        sc.urspRules = (RIL_UrspRule*)calloc(ruleNum, sizeof(RIL_UrspRule));
        RFX_ASSERT(sc.urspRules != NULL);
        uint16_t dataLen = 0;
        mipc_ursp_rule_struct_struct4 *pMipcRule = NULL;
        for (int i = 0; i < ruleNum; i++) {
            pMipcRule = mipc_data_get_ursp_ue_policy_cnf_get_rule_list(
                    msg->getMipcData()->getData(), &dataLen, i);
            if (pMipcRule != NULL && dataLen > 0) {
                // precedence
                sc.urspRules[i].precedence = pMipcRule->p_val;
                // TD
                if (pMipcRule->traffic_desc.dnn_len > 0 || pMipcRule->traffic_desc.app_id_len > 0) {
                    sc.urspRules[i].tdCount = 1;
                    sc.urspRules[i].trafficDescriptors = (RIL_TrafficDescriptor*)calloc(1,
                            sizeof(RIL_TrafficDescriptor));
                    RFX_ASSERT(sc.urspRules[i].trafficDescriptors != NULL);
                    // dnn
                    if (pMipcRule->traffic_desc.dnn_len > 0) {
                        asprintf(&(sc.urspRules[i].trafficDescriptors->dnn), "%s",
                                pMipcRule->traffic_desc.dnn);
                    }
                    // app id
                    if (pMipcRule->traffic_desc.app_id_len > 0) {
                        sc.urspRules[i].trafficDescriptors->osAppIdLen =
                                pMipcRule->traffic_desc.app_id_len;
                        sc.urspRules[i].trafficDescriptors->osAppId = (uint8_t*)calloc(
                                pMipcRule->traffic_desc.app_id_len, sizeof(uint8_t));
                        RFX_ASSERT(sc.urspRules[i].trafficDescriptors->osAppId != NULL);
                        memcpy(sc.urspRules[i].trafficDescriptors->osAppId,
                                pMipcRule->traffic_desc.app_id, pMipcRule->traffic_desc.app_id_len);
                    }
                }

                // RSD
                RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] RSD count: %d",
                        m_slot_id, __FUNCTION__, (int)pMipcRule->num_of_rsd);
                sc.urspRules[i].rsdCount = pMipcRule->num_of_rsd;
                if (pMipcRule->num_of_rsd > 0) {
                    sc.urspRules[i].routeSelectionDescriptor = (RIL_RouteSelectionDescriptor*)
                            calloc(pMipcRule->num_of_rsd, sizeof(RIL_RouteSelectionDescriptor));
                    RFX_ASSERT(sc.urspRules[i].routeSelectionDescriptor != NULL);
                    for (int j = 0; j < pMipcRule->num_of_rsd; j++) {
                        // precedence
                        sc.urspRules[i].routeSelectionDescriptor[j].precedence =
                                pMipcRule->route_sel_desc_list[j].p_val;
                        // sessionType
                        asprintf(&(sc.urspRules[i].routeSelectionDescriptor[j].sessionType), "%s",
                                (char*)RmmDcUtility::getProtocolName(
                                pMipcRule->route_sel_desc_list[j].pdu_session_type));
                        // ssc mode
                        int sscMode = pMipcRule->route_sel_desc_list[j].ssc_mode;
                        if (sscMode > 0) {
                            sc.urspRules[i].routeSelectionDescriptor[j].sscMode =
                                    (RIL_SscMode)sscMode;
                        } else {
                            // Default value
                            sc.urspRules[i].routeSelectionDescriptor[j].sscMode = SSC_MODE_1;
                        }
                        // dnn
                        if (pMipcRule->route_sel_desc_list[j].dnn_len > 0) {
                            // can only 1 dnn according to 3GPP 24.256
                            sc.urspRules[i].routeSelectionDescriptor[j].dnnCount = 1;
                            strncpy(sc.urspRules[i].routeSelectionDescriptor[j].dnn[0],
                                    pMipcRule->route_sel_desc_list[j].dnn,
                                    RIL_MAX_DNN_CHAR_COUNT);
                        }
                        // slice info
                        if (pMipcRule->route_sel_desc_list[j].s_nssai_present > 0) {
                            sc.urspRules[i].routeSelectionDescriptor[j].sliceInfo =
                                    (RIL_SliceInfo*)calloc(1, sizeof(RIL_SliceInfo));
                            RFX_ASSERT(sc.urspRules[i].routeSelectionDescriptor[j].sliceInfo != NULL);
                            mipc_s_nssai_struct_struct4 *pMipcNssai = &pMipcRule->route_sel_desc_list[j].s_nssai;
                            sc.urspRules[i].routeSelectionDescriptor[j].sliceInfo->sst =
                                    RmmDcUtility::convertIntToSliceServiceType(
                                    pMipcNssai->sst_present ? pMipcNssai->sst : 0);
                            sc.urspRules[i].routeSelectionDescriptor[j].sliceInfo->sliceDifferentiator =
                                    pMipcNssai->sd_present ? pMipcNssai->sd : 0;
                            sc.urspRules[i].routeSelectionDescriptor[j].sliceInfo->mappedHplmnSst =
                                    RmmDcUtility::convertIntToSliceServiceType(
                                    pMipcNssai->mapped_sst_present ? pMipcNssai->mapped_sst : 0);
                            sc.urspRules[i].routeSelectionDescriptor[j].sliceInfo->mappedHplmnSD =
                                    pMipcNssai->mapped_sd_present ? pMipcNssai->mapped_sd : 0;
                            sc.urspRules[i].routeSelectionDescriptor[j].sliceInfo->status =
                                    SLICE_ALLOWED;
                            sc.urspRules[i].routeSelectionDescriptor[j].sliceCount = 1;
                        }
                    }
                }
            }
        }
    }

    getSliceInfo(sc, plmn);

    dumpSliceConfig(sc);

    // Response
    sp<RfxMclMessage> response = RfxMclMessage::obtainResponse(msg->getId(),
            RIL_E_SUCCESS, RfxSlicingConfigResponseData(&sc, sizeof(RIL_SlicingConfig)),
            msg, false);
    responseToTelCore(response);

    // Free
    for (int i = 0; i < sc.ruleCount; i++) {
        // Free dnn and os APP id
        for (int j = 0; j < sc.urspRules[i].tdCount; j++) {
            FREEIF(sc.urspRules[i].trafficDescriptors[j].dnn);
            if (sc.urspRules[i].trafficDescriptors[j].osAppIdLen > 0) {
                FREEIF(sc.urspRules[i].trafficDescriptors[j].osAppId);
            }
        }
        // Free TD info
        FREEIF(sc.urspRules[i].trafficDescriptors);

        // Free sessionType and sliceInfo
        for (int j = 0; j < sc.urspRules[i].rsdCount; j++) {
            FREEIF(sc.urspRules[i].routeSelectionDescriptor[j].sessionType);
            FREEIF(sc.urspRules[i].routeSelectionDescriptor[j].sliceInfo);
        }
        // Free RSD info
        FREEIF(sc.urspRules[i].routeSelectionDescriptor);
    }
    FREEIF(sc.urspRules);
    FREEIF(sc.sliceInfo);
}

void RmmDcEventHandler::getSliceInfo(RIL_SlicingConfig &sc, String8 plmn) {
    // Get slice info using sync way
    sp<RfxMipcData> mipcMsg = RfxMipcData::obtainMipcData(MIPC_NW_GET_NSSAI_REQ,
            m_slot_id);
    mipc_nw_get_nssai_req_add_nssai_type(mipcMsg->getData(),
            MIPC_NSSAI_TYPE_ENUM_DEFAULT_CONFIGURED_AND_REJECT_AND_CONFIGURED_AND_ALLOWED_NSSAI);
    mipc_nw_get_nssai_req_add_plmn_id(mipcMsg->getData(), plmn.length(),
            (uint8_t*)plmn.string());
    sp<RfxMipcData> mipcCnf = callToMipcMsgSync(mipcMsg);
    if ((mipc_result_const_enum) mipcCnf->getResult() != MIPC_RESULT_SUCCESS) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] MIPC_NW_GET_NSSAI_REQ return error",
                m_slot_id, __FUNCTION__);
        return;
    }

    unsigned int sliceIndex = 0;
    int sliceNum = 0;
    uint16_t dataLen = 0;
    mipc_s_nssai_struct_struct4 *pMipcNssai = NULL;
    mipc_plmn_specific_s_nssai_struct_struct4 *pPlmnNssai = NULL;
    RIL_SliceInfo nssais[MAX_NSSAIS * MAX_NSSAI_TYPE];
    memset(nssais, 0, sizeof(RIL_SliceInfo) * MAX_NSSAIS * MAX_NSSAI_TYPE);

    // default config nssai
    sliceNum = (int)mipc_msg_get_tlv_num(mipcCnf->getData(),
            MIPC_NW_GET_NSSAI_CNF_T_DEFAULT_CONFIGURED_NSSAI_LIST);
    for (int i = 0; i < sliceNum; i++) {
        pMipcNssai = mipc_nw_get_nssai_cnf_get_default_configured_nssai_list(mipcCnf->getData(),
                &dataLen, i);
        nssais[sliceIndex].sst = RmmDcUtility::convertIntToSliceServiceType(
                pMipcNssai->sst_present ? pMipcNssai->sst : 0);
        nssais[sliceIndex].sliceDifferentiator =
                pMipcNssai->sd_present ? pMipcNssai->sd : 0;
        nssais[sliceIndex].mappedHplmnSst = RmmDcUtility::convertIntToSliceServiceType(
                pMipcNssai->mapped_sst_present ? pMipcNssai->mapped_sst : 0);
        nssais[sliceIndex].mappedHplmnSD =
                pMipcNssai->mapped_sd_present ? pMipcNssai->mapped_sd : 0;
        nssais[sliceIndex].status = SLICE_DEFAULT_CONFIGURED;
        sliceIndex++;
    }

    // reject nssai
    sliceNum = (int)mipc_msg_get_tlv_num(mipcCnf->getData(),
            MIPC_NW_GET_NSSAI_CNF_T_REJECTED_NSSAI_3GPP_LIST);
    mipc_rejected_s_nssai_struct_struct4 *pMipcRejectNssai = NULL;
    for (int i = 0; i < sliceNum; i++) {
        pMipcRejectNssai = mipc_nw_get_nssai_cnf_get_rejected_nssai_3gpp_list(mipcCnf->getData(),
                &dataLen, i);
        nssais[sliceIndex].sst = RmmDcUtility::convertIntToSliceServiceType(
                pMipcRejectNssai->sst_present ? pMipcRejectNssai->sst : 0);
        nssais[sliceIndex].sliceDifferentiator =
                pMipcRejectNssai->sd_present ? pMipcRejectNssai->sd : 0;
        if (pMipcRejectNssai->cause_value > 0) {
            nssais[sliceIndex].status = SLICE_REJECTED_NOT_AVAILABLE_IN_REG_AREA;
        } else {
            nssais[sliceIndex].status = SLICE_REJECTED_NOT_AVAILABLE_IN_PLMN;
        }
        sliceIndex++;
    }

    // configure nssai
    sliceNum = (int)mipc_msg_get_tlv_num(mipcCnf->getData(),
            MIPC_NW_GET_NSSAI_CNF_T_CONFIGURED_NSSAI_LIST);
    for (int i = 0; i < sliceNum; i++) {
        pPlmnNssai = mipc_nw_get_nssai_cnf_get_configured_nssai_list(mipcCnf->getData(),
                &dataLen, i);
        nssais[sliceIndex].sst = RmmDcUtility::convertIntToSliceServiceType(
                pPlmnNssai->sst_present ? pPlmnNssai->sst : 0);
        nssais[sliceIndex].sliceDifferentiator =
                pPlmnNssai->sd_present ? pPlmnNssai->sd : 0;
        nssais[sliceIndex].mappedHplmnSst = RmmDcUtility::convertIntToSliceServiceType(
                pPlmnNssai->mapped_sst_present ? pPlmnNssai->mapped_sst : 0);
        nssais[sliceIndex].mappedHplmnSD =
                pPlmnNssai->mapped_sd_present ? pPlmnNssai->mapped_sd : 0;
        nssais[sliceIndex].status = SLICE_CONFIGURED;
        sliceIndex++;
    }

    // allowed nssai
    sliceNum = (int)mipc_msg_get_tlv_num(mipcCnf->getData(),
            MIPC_NW_GET_NSSAI_CNF_T_ALLOWED_NSSAI_3GPP_LIST);
    for (int i = 0; i < sliceNum; i++) {
        pPlmnNssai = mipc_nw_get_nssai_cnf_get_allowed_nssai_3gpp_list(mipcCnf->getData(),
                &dataLen, i);
        nssais[sliceIndex].sst = RmmDcUtility::convertIntToSliceServiceType(
                pPlmnNssai->sst_present ? pPlmnNssai->sst : 0);
        nssais[sliceIndex].sliceDifferentiator =
                pPlmnNssai->sd_present ? pPlmnNssai->sd : 0;
        nssais[sliceIndex].mappedHplmnSst = RmmDcUtility::convertIntToSliceServiceType(
                pPlmnNssai->mapped_sst_present ? pPlmnNssai->mapped_sst : 0);
        nssais[sliceIndex].mappedHplmnSD =
                pPlmnNssai->mapped_sd_present ? pPlmnNssai->mapped_sd : 0;
        nssais[sliceIndex].status = SLICE_ALLOWED;
        sliceIndex++;
    }

    sc.sliceCount = sliceIndex;
    sc.sliceInfo = (RIL_SliceInfo*)calloc(sliceIndex, sizeof(RIL_SliceInfo));
    RFX_ASSERT(sc.sliceInfo != NULL);
    memcpy(sc.sliceInfo, nssais, sliceIndex * sizeof(RIL_SliceInfo));
}

void RmmDcEventHandler::dumpSliceConfig(RIL_SlicingConfig sc) {
    RFX_LOG_D(RFX_LOG_TAG,"[%d][%s] rule number: %d", m_slot_id, __FUNCTION__, sc.ruleCount);
    for (int i = 0; i < sc.ruleCount; i++) {
        RFX_LOG_D(RFX_LOG_TAG,"[%d][%s] rules[%d],precedence:%d,tdCount:%d,rsdCount:%d",
                m_slot_id, __FUNCTION__, i, sc.urspRules[i].precedence,
                sc.urspRules[i].tdCount, sc.urspRules[i].rsdCount);
        for (int j = 0; j < sc.urspRules[i].tdCount; j++) {
            RFX_LOG_D(RFX_LOG_TAG,"[%d][%s] TD[%d]:{%s,%d}", m_slot_id, __FUNCTION__, j,
                    sc.urspRules[i].trafficDescriptors[j].dnn,
                    sc.urspRules[i].trafficDescriptors[j].osAppIdLen);
        }
        for (int j = 0; j < sc.urspRules[i].rsdCount; j++) {
            RFX_LOG_D(RFX_LOG_TAG,"[%d][%s] RSD[%d]:{%d,%s,%d,%d,%d}", m_slot_id, __FUNCTION__, j,
                    sc.urspRules[i].routeSelectionDescriptor[j].precedence,
                    sc.urspRules[i].routeSelectionDescriptor[j].sessionType,
                    sc.urspRules[i].routeSelectionDescriptor[j].sscMode,
                    sc.urspRules[i].routeSelectionDescriptor[j].sliceCount,
                    sc.urspRules[i].routeSelectionDescriptor[j].dnnCount);
        }
    }
    for (int i = 0; i < sc.sliceCount; i++) {
        RFX_LOG_D(RFX_LOG_TAG, "[%s] Slice info count: %d, [%d]{%d,%d,%d,%d,%d}", __FUNCTION__,
                sc.sliceCount, i,
                sc.sliceInfo[i].sst,
                sc.sliceInfo[i].sliceDifferentiator,
                sc.sliceInfo[i].mappedHplmnSst,
                sc.sliceInfo[i].mappedHplmnSD,
                sc.sliceInfo[i].status);
    }
}

int RmmDcEventHandler::getOsIdArray(uint8_t *osId) {
    int i = 0;
    int len = strlen(ANDROID_OS_ID);
    char *pOsId = (char*)calloc(1, len + 1);
    if (pOsId == NULL) {
        RFX_LOG_D(RFX_LOG_TAG, "[%s] allocate memory fail for osid", __FUNCTION__);
        return 0;
    }
    strncpy(pOsId, ANDROID_OS_ID, len);
    RFX_LOG_D(RFX_LOG_TAG, "[%s] pOsId %s", __FUNCTION__, pOsId);
    char *tmpOsId = pOsId;
    for (char *pCur = strsep(&tmpOsId, "-"); pCur != NULL;) {
        osId[i] = (uint8_t)RmmDcUtility::hexStrToDec(pCur);
        pCur = strsep(&tmpOsId, "-");
        RFX_LOG_V(RFX_LOG_TAG, "[%s] osId[%d] %x", __FUNCTION__, i, osId[i]);
        i++;
        if (i >= MIPC_UE_OS_ID_LEN) {
            break;
        }
    }
    free(pOsId);
    return 1;
}

void RmmDcEventHandler::setOsId() {
    sp<RfxMipcData> mipcReq = RfxMipcData::obtainMipcData(
            MIPC_NW_OS_ID_UPDATE_REQ, m_slot_id);
    mipc_nw_os_id_update_req_add_os_id_num(mipcReq->getData(), 1);
    mipc_os_id_info_struct4 osId;
    if (!getOsIdArray(osId.os_id)) {
        return;
    }
    mipc_msg_tlv_array_t *osIdList = mipc_msg_add_tlv_array(
            mipcReq->getData(), MIPC_NW_OS_ID_UPDATE_REQ_T_OS_ID_LIST, 1);
    mipc_msg_add_idx(mipcReq->getData(), osIdList, 0, sizeof(mipc_os_id_info_struct4), &osId);
    mipc_msg_async(mipcReq->getData(), NULL, NULL);
}
