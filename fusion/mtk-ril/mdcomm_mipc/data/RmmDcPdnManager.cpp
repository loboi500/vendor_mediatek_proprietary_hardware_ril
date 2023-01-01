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

#include <string.h>

#include "RfxStatusDefs.h"
#include "RmmDcUtility.h"
#include "RmmDcPdnManager.h"
#include "mipc_api.h"
#include "mipc_msg_host.h"

#define RFX_LOG_TAG "RmmDcPdnManager"

/*
 * RmmDcPdnManager class description:
 * The class is defined to manage the PDN table information in rild, it is slot based which
 * means each slot has such a PdnManager instance. Other class should get latest PDN info
 * from it and update the corresponding PdnInfo if it's changed.
 *
 * Not consider concurrency access currently because RILD only use one data channel and all
 * operations are executed on one thread. Should consider it if we change the thread and data
 * access model.
 */

RmmDcPdnManager::RmmDcPdnManager(int slot_id, int channel_id) :
        RfxBaseHandler(slot_id, channel_id), mPdnTableSize(0),
        m_pPdnInfo(NULL), mNumOfConnectedPdn(0) {
    initPdnTable();
    initAtCmds();
}

RmmDcPdnManager::~RmmDcPdnManager() {
    if (m_pPdnInfo != NULL) {
        free(m_pPdnInfo);
        m_pPdnInfo = NULL;
    }
    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s]: destructor.", m_slot_id, __FUNCTION__);
}

void RmmDcPdnManager::initPdnTable() {
    mPdnTableSize = getModemSupportPdnNumber();
    if (m_pPdnInfo == NULL) {
        m_pPdnInfo = (PdnInfo*) calloc(mPdnTableSize, sizeof(PdnInfo));
        RFX_ASSERT(m_pPdnInfo != NULL);
        clearAllPdnInfo();
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s]: pdnTableSize = %d, m_pPdnInfo = %p", m_slot_id,
                __FUNCTION__, mPdnTableSize, m_pPdnInfo);
    }
}

void RmmDcPdnManager::initAtCmds() {
    sp<RfxAtResponse> p_response;

    // enable ATTACH PDN URC
    p_response = atSendCommand("AT+EIAREG=1");
    if (p_response == NULL) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] fail to get IAREG=1 response", m_slot_id, __FUNCTION__);
    }
    p_response = atSendCommand("AT+ECCAUSE=1");
    if (p_response == NULL) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] fail to get ECCAUSE=1 response", m_slot_id, __FUNCTION__);
    }
}

int RmmDcPdnManager::getPdnTableSize() {
    return mPdnTableSize;
}

// Get PDN info, it is a copy of PDN info in the table.
PdnInfo RmmDcPdnManager::getPdnInfo(int aid) {
    RFX_ASSERT(validateAid(aid));
    if (DEBUG_MORE_INFO) {
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s]: aid = %d, pdnInfo = %s", m_slot_id, __FUNCTION__,
                aid, pdnInfoToString(&m_pPdnInfo[aid]).string());
    }
    return m_pPdnInfo[aid];
}

void RmmDcPdnManager::setPdnInfo(int aid, PdnInfo* pdnInfo) {
    // Use memcpy instead of assign value by attributes for better performance.
    // NOTES: No pointer member in PdnInfo, couldn't use memcpy if any pointer member in PdnInfo.
    RFX_ASSERT(pdnInfo != NULL);
    int previousPdnActiveStatus = m_pPdnInfo[aid].active;
    int newPdnActiveStatus = pdnInfo->active;
    memcpy(&m_pPdnInfo[aid], pdnInfo, sizeof(PdnInfo));

    if (previousPdnActiveStatus != newPdnActiveStatus) {
        updateAndNotifyPdnConnectStatusChanged();
    }
}

void RmmDcPdnManager::setDefaultQos(int aid, const RIL_Qos* defaultQos) {
    RFX_ASSERT(validateAid(aid));
    clearDefaultQos(aid);
    m_pPdnInfo[aid].defaultQos = (RIL_Qos*)calloc(1, sizeof(RIL_Qos));
    RFX_ASSERT(m_pPdnInfo[aid].defaultQos != NULL);
    memcpy(m_pPdnInfo[aid].defaultQos, defaultQos, sizeof(RIL_Qos));
/*
    if (m_pPdnInfo[aid].accessNetwork == E_UTRAN) {
        m_pPdnInfo[aid].defaultQos = (RIL_Qos*)calloc(1, sizeof(RIL_Qos));
        //memcpy(m_pPdnInfo[aid].defaultQos->eps, defaultQos->eps, sizeof(RIL_EpsQos));
        m_pPdnInfo[aid].defaultQos->eps.qci = defaultQos->eps.qci;
        m_pPdnInfo[aid].defaultQos->eps.uplink.maxBitrateKbps
                      = defaultQos->eps.uplink.maxBitrateKbps;
        m_pPdnInfo[aid].defaultQos->eps.uplink.guaranteedBitrateKbps
                      = defaultQos->eps.uplink.guaranteedBitrateKbps;
        m_pPdnInfo[aid].defaultQos->eps.downlink.maxBitrateKbps
                      = defaultQos->eps.downlink.maxBitrateKbps;
        m_pPdnInfo[aid].defaultQos->eps.downlink.guaranteedBitrateKbps
                      = defaultQos->eps.downlink.guaranteedBitrateKbps;

    } else if (m_pPdnInfo[aid].accessNetwork == NG_RAN) {
        m_pPdnInfo[aid].defaultQos = (RIL_Qos*)calloc(1, sizeof(RIL_Qos));
        //memcpy(m_pPdnInfo[aid].defaultQos->nr, defaultQos->nr, sizeof(RIL_NrQos));
        m_pPdnInfo[aid].defaultQos->nr.fiveQi = defaultQos->nr.fiveQi;
        m_pPdnInfo[aid].defaultQos->nr.uplink.maxBitrateKbps
                      = defaultQos->nr.uplink.maxBitrateKbps;
        m_pPdnInfo[aid].defaultQos->nr.uplink.guaranteedBitrateKbps
                      = defaultQos->nr.uplink.guaranteedBitrateKbps;
        m_pPdnInfo[aid].defaultQos->nr.downlink.maxBitrateKbps
                      = defaultQos->nr.downlink.maxBitrateKbps;
        m_pPdnInfo[aid].defaultQos->nr.downlink.guaranteedBitrateKbps
                      = defaultQos->nr.downlink.guaranteedBitrateKbps;
        m_pPdnInfo[aid].defaultQos->nr.qfi = defaultQos->nr.qfi;
        m_pPdnInfo[aid].defaultQos->nr.averagingWindowMs
                      = defaultQos->nr.averagingWindowMs;
    }
*/
}

void RmmDcPdnManager::clearDefaultQos(int aid) {
    RFX_ASSERT(validateAid(aid));
    FREEIF(m_pPdnInfo[aid].defaultQos);
}

void RmmDcPdnManager::setQosSession(int aid, RIL_QosSession* qosSession) {
    RFX_ASSERT(validateAid(aid));
    if (qosSession == NULL) {
        RFX_LOG_W(RFX_LOG_TAG, "[%d][%s] illegal param, qosSession is NULL",
                m_slot_id, __FUNCTION__);
        return;
    }
    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] aid:%d", m_slot_id, __FUNCTION__, aid);

    m_pPdnInfo[aid].qosSession = (RIL_QosSession*)calloc(1, sizeof(RIL_QosSession));
    RFX_ASSERT(m_pPdnInfo[aid].qosSession != NULL);
    m_pPdnInfo[aid].qosSession->qosSessionId = qosSession->qosSessionId;
    memcpy(&(m_pPdnInfo[aid].qosSession->qos), &(qosSession->qos), sizeof(RIL_Qos));
    m_pPdnInfo[aid].qosSession->qosFilterCount = qosSession->qosFilterCount;
    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] aid:%d, qosSession->qosFilterCount:%d.",
            m_slot_id, __FUNCTION__, aid,
            m_pPdnInfo[aid].qosSession->qosFilterCount);

    // qosFilters
    for (int j = 0; j < m_pPdnInfo[aid].qosSession->qosFilterCount; j++) {
        // local address
        int addLen = strlen(qosSession->qosFilters[j].localAddresses);
        if (addLen > 0) {
            m_pPdnInfo[aid].qosSession->qosFilters[j].localAddresses =
                    (char*) calloc(1, sizeof(char)*(addLen + 1));
            RFX_ASSERT(m_pPdnInfo[aid].qosSession->qosFilters[j].localAddresses != NULL);
            memcpy(m_pPdnInfo[aid].qosSession->qosFilters[j].localAddresses,
                    qosSession->qosFilters[j].localAddresses, addLen);
        }
        // remote address
        addLen = strlen(qosSession->qosFilters[j].remoteAddresses);
        if (addLen > 0) {
            m_pPdnInfo[aid].qosSession->qosFilters[j].remoteAddresses =
                    (char*) calloc(1, sizeof(char)*(addLen + 1));
            RFX_ASSERT(m_pPdnInfo[aid].qosSession->qosFilters[j].remoteAddresses != NULL);
            memcpy(m_pPdnInfo[aid].qosSession->qosFilters[j].remoteAddresses,
                    qosSession->qosFilters[j].remoteAddresses, addLen);
        }

        m_pPdnInfo[aid].qosSession->qosFilters[j].localPort.start
                      = qosSession->qosFilters[j].localPort.start;
        m_pPdnInfo[aid].qosSession->qosFilters[j].localPort.end
                      = qosSession->qosFilters[j].localPort.end;
        m_pPdnInfo[aid].qosSession->qosFilters[j].remotePort.start
                      = qosSession->qosFilters[j].remotePort.start;
        m_pPdnInfo[aid].qosSession->qosFilters[j].remotePort.end
                      = qosSession->qosFilters[j].remotePort.end;
        m_pPdnInfo[aid].qosSession->qosFilters[j].protocol
                      = qosSession->qosFilters[j].protocol;
        m_pPdnInfo[aid].qosSession->qosFilters[j].typeOfService
                      = qosSession->qosFilters[j].typeOfService;
        m_pPdnInfo[aid].qosSession->qosFilters[j].ipv6FlowLabel
                      = qosSession->qosFilters[j].ipv6FlowLabel;
        m_pPdnInfo[aid].qosSession->qosFilters[j].ipSecSpi
                      = qosSession->qosFilters[j].ipSecSpi;
        m_pPdnInfo[aid].qosSession->qosFilters[j].direction
                      = qosSession->qosFilters[j].direction;
        m_pPdnInfo[aid].qosSession->qosFilters[j].precedence
                      = qosSession->qosFilters[j].precedence;
    }
}

void RmmDcPdnManager::clearQosSession(int aid) {
    RFX_ASSERT(validateAid(aid));
    if (m_pPdnInfo[aid].qosSession == NULL) {
        return;
    }

    for (int j = 0; j < m_pPdnInfo[aid].qosSession->qosFilterCount; j++) {
        FREEIF(m_pPdnInfo[aid].qosSession->qosFilters[j].localAddresses);
        FREEIF(m_pPdnInfo[aid].qosSession->qosFilters[j].remoteAddresses);
    }

    FREEIF(m_pPdnInfo[aid].qosSession);
}

void RmmDcPdnManager::setSliceInfo(int aid, RIL_SliceInfo* optionalSliceInfo) {
    RFX_ASSERT(validateAid(aid));
    clearSliceInfo(aid);
    m_pPdnInfo[aid].optionalSliceInfo = (RIL_SliceInfo*)calloc(1, sizeof(RIL_SliceInfo));
    RFX_ASSERT(m_pPdnInfo[aid].optionalSliceInfo != NULL);
    memcpy(m_pPdnInfo[aid].optionalSliceInfo, optionalSliceInfo, sizeof(RIL_SliceInfo));
}

void RmmDcPdnManager::clearSliceInfo(int aid) {
    RFX_ASSERT(validateAid(aid));
    FREEIF(m_pPdnInfo[aid].optionalSliceInfo);
}

// clearTds() should be invoked before invoking setTds()
void RmmDcPdnManager::setTds(int aid, int count, RIL_TrafficDescriptor* Tds) {
    RFX_ASSERT(validateAid(aid));
    m_pPdnInfo[aid].tdCount = count;
    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] aid:%d, tdCount:%d.",
                m_slot_id, __FUNCTION__, aid, m_pPdnInfo[aid].tdCount);
    if (m_pPdnInfo[aid].tdCount <= 0) {
        return;
    }
    m_pPdnInfo[aid].TDs = (RIL_TrafficDescriptor*) calloc(1,
            sizeof(RIL_TrafficDescriptor) * (m_pPdnInfo[aid].tdCount));
    RFX_ASSERT(m_pPdnInfo[aid].TDs != NULL);
    for (int i = 0; i < m_pPdnInfo[aid].tdCount; i++) {
        if (Tds[i].dnn != NULL && strlen(Tds[i].dnn) > 0) {
            int dnnLen = strlen(Tds[i].dnn);
            m_pPdnInfo[aid].TDs[i].dnn = (char*)calloc(1, sizeof(char)*(dnnLen + 1));
            RFX_ASSERT(m_pPdnInfo[aid].TDs[i].dnn != NULL);
            memcpy(m_pPdnInfo[aid].TDs[i].dnn, Tds[i].dnn, dnnLen);
        }
        m_pPdnInfo[aid].TDs[i].osAppIdLen = Tds[i].osAppIdLen;
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s][DBG] aid:%d, osAppIdLen:%d.",
                m_slot_id, __FUNCTION__, aid, m_pPdnInfo[aid].TDs[i].osAppIdLen);
        if (Tds[i].osAppIdLen > 0) {
            m_pPdnInfo[aid].TDs[i].osAppId = (uint8_t*)calloc(1,
                    sizeof(uint8_t) * Tds[i].osAppIdLen);
            RFX_ASSERT(m_pPdnInfo[aid].TDs[i].osAppId != NULL);
            memcpy(m_pPdnInfo[aid].TDs[i].osAppId, Tds[i].osAppId, Tds[i].osAppIdLen);
        }
    }
}

void RmmDcPdnManager::clearTds(int aid) {
    RFX_ASSERT(validateAid(aid));
    for (int i = 0; i < m_pPdnInfo[aid].tdCount; i++) {
        FREEIF(m_pPdnInfo[aid].TDs[i].dnn);
        FREEIF(m_pPdnInfo[aid].TDs[i].osAppId);
    }
    FREEIF(m_pPdnInfo[aid].TDs);
    m_pPdnInfo[aid].tdCount = 0;
}

/* Copy QosSession of specific AID.
 * NULL will be returned if no TD.
 * Caller is duty-bound to free memory !!!
 */
RIL_QosSession* RmmDcPdnManager::copyQosSession(int aid) {
    RFX_ASSERT(validateAid(aid));
    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] aid:%d.", m_slot_id, __FUNCTION__, aid);
    if (m_pPdnInfo[aid].qosSession == NULL) {
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] QosSession is NULL, aid:%d.",
                m_slot_id, __FUNCTION__, aid);
        return NULL;
    }

    RIL_QosSession* tempQosSession = (RIL_QosSession*)calloc(1, sizeof(RIL_QosSession));
    RFX_ASSERT(tempQosSession != NULL);
    tempQosSession->qosSessionId = m_pPdnInfo[aid].qosSession->qosSessionId;
    memcpy(&(tempQosSession->qos), &(m_pPdnInfo[aid].qosSession->qos), sizeof(RIL_Qos));
    tempQosSession->qosFilterCount = m_pPdnInfo[aid].qosSession->qosFilterCount;
    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] aid:%d, qosSession->qosFilterCount:%d.",
            m_slot_id, __FUNCTION__, aid, tempQosSession->qosFilterCount);

    // qosFilters
    for (int j = 0; j < tempQosSession->qosFilterCount; j++) {
        // local address
        int addLen = strlen(m_pPdnInfo[aid].qosSession->qosFilters[j].localAddresses);
        if (addLen > 0) {
            tempQosSession->qosFilters[j].localAddresses =
                    (char*) calloc(1, sizeof(char)*(addLen + 1));
            RFX_ASSERT(tempQosSession->qosFilters[j].localAddresses != NULL);
            memcpy(tempQosSession->qosFilters[j].localAddresses,
                    m_pPdnInfo[aid].qosSession->qosFilters[j].localAddresses, addLen);
        }
        // remote address
        addLen = strlen(m_pPdnInfo[aid].qosSession->qosFilters[j].remoteAddresses);
        if (addLen > 0) {
            tempQosSession->qosFilters[j].remoteAddresses =
                    (char*) calloc(1, sizeof(char)*(addLen + 1));
            RFX_ASSERT(tempQosSession->qosFilters[j].remoteAddresses != NULL);
            memcpy(tempQosSession->qosFilters[j].remoteAddresses,
                    m_pPdnInfo[aid].qosSession->qosFilters[j].remoteAddresses, addLen);
        }

        tempQosSession->qosFilters[j].localPort.start
                = m_pPdnInfo[aid].qosSession->qosFilters[j].localPort.start;
        tempQosSession->qosFilters[j].localPort.end
                = m_pPdnInfo[aid].qosSession->qosFilters[j].localPort.end;
        tempQosSession->qosFilters[j].remotePort.start
                = m_pPdnInfo[aid].qosSession->qosFilters[j].remotePort.start;
        tempQosSession->qosFilters[j].remotePort.end
                = m_pPdnInfo[aid].qosSession->qosFilters[j].remotePort.end;
        tempQosSession->qosFilters[j].protocol
                = m_pPdnInfo[aid].qosSession->qosFilters[j].protocol;
        tempQosSession->qosFilters[j].typeOfService
                = m_pPdnInfo[aid].qosSession->qosFilters[j].typeOfService;
        tempQosSession->qosFilters[j].ipv6FlowLabel
                = m_pPdnInfo[aid].qosSession->qosFilters[j].ipv6FlowLabel;
        tempQosSession->qosFilters[j].ipSecSpi
                = m_pPdnInfo[aid].qosSession->qosFilters[j].ipSecSpi;
        tempQosSession->qosFilters[j].direction
                = m_pPdnInfo[aid].qosSession->qosFilters[j].direction;
        tempQosSession->qosFilters[j].precedence
                = m_pPdnInfo[aid].qosSession->qosFilters[j].precedence;
    }

    return tempQosSession;
}


/* Copy TrafficDescriptors of specific AID.
 * NULL will be returned if no TD.
 * Caller is duty-bound to free memory !!!
 */
RIL_TrafficDescriptor* RmmDcPdnManager::copyTds(int aid) {
    RFX_ASSERT(validateAid(aid));
    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s] aid:%d, tdCount:%d.",
                m_slot_id, __FUNCTION__, aid, m_pPdnInfo[aid].tdCount);
    if (m_pPdnInfo[aid].tdCount <= 0) {
        return NULL;
    }

    RIL_TrafficDescriptor* tmpTDs = (RIL_TrafficDescriptor*) calloc(1,
            sizeof(RIL_TrafficDescriptor) * (m_pPdnInfo[aid].tdCount));
    RFX_ASSERT(tmpTDs != NULL);
    for (int i = 0; i < m_pPdnInfo[aid].tdCount; i++) {
        int dnnLen = strlen(m_pPdnInfo[aid].TDs[i].dnn);
        tmpTDs[i].dnn = (char*)calloc(1, sizeof(char)*(dnnLen + 1));
        RFX_ASSERT(tmpTDs[i].dnn != NULL);
        memcpy(tmpTDs[i].dnn, m_pPdnInfo[aid].TDs[i].dnn, dnnLen);
        tmpTDs[i].osAppIdLen = m_pPdnInfo[aid].TDs[i].osAppIdLen;
        tmpTDs[i].osAppId = (uint8_t*)calloc(1, sizeof(uint8_t)*(tmpTDs[i].osAppIdLen + 1));
        RFX_ASSERT(tmpTDs[i].osAppId != NULL);
        memcpy(tmpTDs[i].osAppId, m_pPdnInfo[aid].TDs[i].osAppId, tmpTDs[i].osAppIdLen);
    }
    return tmpTDs;
}

void RmmDcPdnManager::clearPdnInfo(int aid) {
    RFX_ASSERT(validateAid(aid));
    clearPdnInfo(&m_pPdnInfo[aid]);

    updateAndNotifyPdnConnectStatusChanged();
}

void RmmDcPdnManager::clearAllPdnInfo() {
    if (DEBUG_MORE_INFO) {
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s].", m_slot_id, __FUNCTION__);
        dumpAllPdnInfo();
    }

    for (int i = 0; i < mPdnTableSize; i++) {
        clearPdnInfo(&m_pPdnInfo[i]);
    }
    updateAndNotifyPdnConnectStatusChanged();
}

void RmmDcPdnManager::clearPdnInfo(PdnInfo* info) {
    // Before memset, free memory of pointers.
    FREEIF(info->defaultQos);
    if (info->qosSession != NULL) {
        FREEIF(info->qosSession->qosFilters);
    }
    FREEIF(info->qosSession);
    FREEIF(info->optionalSliceInfo);
    if (info->TDs != NULL) {
        FREEIF(info->TDs->dnn);
        FREEIF(info->TDs->osAppId);
    }
    FREEIF(info->TDs);

    memset(info, 0, sizeof(PdnInfo));
    info->transIntfId = INVALID_TRANS_INTF_ID;
    info->interfaceId = INVALID_INTERFACE_ID;
    info->primaryAid = INVALID_AID;
    info->aid = INVALID_AID;
    info->bearerId = INVALID_AID;
    info->ddcId = INVALID_AID;
    info->isDedicateBearer = 0;
    info->mtuV4= 0;  // means not be specified
    info->mtuV6 = 0;  // means not be specified
    info->reason = NO_CAUSE;
    info->deactReason = NO_REASON;
    info->rat = 1; // 1: cellular
    info->pdnType = INVALID_PDN_TYPE;
    info->profileId = -1;
    info->sscMode = SSC_UNKNOWN;
    info->accessNetwork = 0;
    for (int i = 0; i < MAX_NUM_IPV6_ADDRESS_NUMBER; i++) {
        info->addressV6Info[i].deprecationTime = -1;
        info->addressV6Info[i].expirationTime = -1;
    }
    info->qosSessionCount = 0;
    info->handoverFailureMode = -1;
    info->pduSessionId = 0;
    info->tdCount = 0;
}

void RmmDcPdnManager::updatePdnActiveStatus(int aid, int pdnActiveStatus) {
    RFX_ASSERT(validateAid(aid));
    if (!validatePdnState(pdnActiveStatus)) {
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s]: invalid input pdnState:%d.",
            m_slot_id, __FUNCTION__, pdnActiveStatus);
        return;
    }
    int prevActiveStatus = m_pPdnInfo[aid].active;
    m_pPdnInfo[aid].active = pdnActiveStatus;

    // Notify PDN active status changed, compare with previous status to reduce unnecessary call.
    if (prevActiveStatus != pdnActiveStatus) {
        updateAndNotifyPdnConnectStatusChanged();
    }
}

void RmmDcPdnManager::updateIpAddress(int aid, const char* ipv4Addr, int index,
        const char* ipv6Addr) {
    RFX_ASSERT(validateAid(aid));
    int n = 0;
    if (ipv4Addr != NULL) {
        n = snprintf(m_pPdnInfo[aid].addressV4, MAX_IPV4_ADDRESS_LENGTH, "%s", ipv4Addr);
        if (n < 0) {
            return;
        }
    }
    RFX_ASSERT(index >= 0 && index < MAX_NUM_IPV6_ADDRESS_NUMBER);
    if (ipv6Addr != NULL) {
        n = snprintf(m_pPdnInfo[aid].addressV6Info[index].addressV6,
                MAX_IPV6_ADDRESS_LENGTH, "%s", ipv6Addr);
        if (n < 0) {
            return;
        }
    }
}

void RmmDcPdnManager::updateDns(int aid, int v4DnsNumber, int v6DnsNumber,
        const char** v4Dns, const char** v6Dns) {
    RFX_ASSERT(validateAid(aid));
    int n = 0;
    for (int i = 0; i < v4DnsNumber; i++) {
        n = snprintf(m_pPdnInfo[aid].dnsV4[i], MAX_IPV4_ADDRESS_LENGTH, "%s", *(v4Dns + i));
        if (n < 0) {
            break;
        }
    }
    for (int i = 0; i < v6DnsNumber; i++) {
        n = snprintf(m_pPdnInfo[aid].dnsV6[i], MAX_IPV6_ADDRESS_LENGTH, "%s", *(v6Dns + i));
        if (n < 0) {
            break;
        }
    }
}

// Update status key to notify PDN status, request by AGPS.
void RmmDcPdnManager::updateAndNotifyPdnConnectStatusChanged() {
    int numOfConnectedPdn = 0;
    for (int i = 0; i < mPdnTableSize; i++) {
        if (m_pPdnInfo[i].active == DATA_STATE_ACTIVE) {
            numOfConnectedPdn++;
        }
    }

    RFX_LOG_D(RFX_LOG_TAG, "[%d][%s]: mNumOfConnectedPdn = %d, numOfConnectedPdn = %d.",
            m_slot_id, __FUNCTION__, mNumOfConnectedPdn, numOfConnectedPdn);
    if (mNumOfConnectedPdn != numOfConnectedPdn) {
        if (numOfConnectedPdn > 0) {
            getMclStatusManager()->setIntValue(RFX_STATUS_KEY_DATA_CONNECTION,
                    DATA_STATE_CONNECTED);
        } else {
            getMclStatusManager()->setIntValue(RFX_STATUS_KEY_DATA_CONNECTION,
                    DATA_STATE_DISCONNECTED);
        }
    }
    mNumOfConnectedPdn = numOfConnectedPdn;
}

void RmmDcPdnManager::dumpAllPdnInfo() {
    for (int i = 0; i < mPdnTableSize; i++) {
        RFX_LOG_D(RFX_LOG_TAG, "[%d][%s]: %s", m_slot_id,
                __FUNCTION__, pdnInfoToString(&m_pPdnInfo[i]).string());
    }
}

String8 RmmDcPdnManager::pdnInfoToString(PdnInfo* pdnInfo) {
    String8 cmd("");

    cmd.append(String8::format("PdnInfo{transIntfId=%d, primaryAid=%d, aid=%d, apnName=%s, "
            "active=%d, addrV4=%s, ",
            pdnInfo->transIntfId,
            pdnInfo->primaryAid,
            pdnInfo->aid,
            pdnInfo->apn,
            pdnInfo->active,
            pdnInfo->addressV4));

    cmd.append(String8::format("addrV6="));
    for (int i = 0; i < MAX_NUM_IPV6_ADDRESS_NUMBER; i++) {
        if (i != 0) {
            cmd.append(String8::format("%s", ", "));
        }
        cmd.append(String8::format("%s", pdnInfo->addressV6Info[i].addressV6));
    }

    cmd.append(String8::format(", mtuV4=%d, mtuV6=%d, rat=%d, reason=%d, deactReason=%d, pdnType=%d, profileId=%d, sscMode=%d}",
            pdnInfo->mtuV4,
            pdnInfo->mtuV6,
            pdnInfo->rat,
            pdnInfo->reason,
            pdnInfo->deactReason,
            pdnInfo->pdnType,
            pdnInfo->profileId,
            pdnInfo->sscMode));

    return cmd;
}

// Get modem support PDN number, MD response the AID range by AT+CGDCONT=?.
// It is used to decide the size of PDN table.
int RmmDcPdnManager::getModemSupportPdnNumber() {
    sp<RfxMipcData> mipcReq = RfxMipcData::obtainMipcData(MIPC_DATA_GET_PDP_CID_REQ, m_slot_id);
    sp<RfxMipcData> mipcCnf = callToMipcMsgSync(mipcReq);
    if ((mipc_result_const_enum) mipcCnf->getResult() != MIPC_RESULT_SUCCESS) {
        RFX_LOG_E(RFX_LOG_TAG, "[%d][%s] MIPC_DATA_KEEPALIVE_REQ return error",
                m_slot_id, __FUNCTION__);
        return DEFAULT_PDN_TABLE_SIZE;
    }
    int min = (int) mipcCnf->getMipcUint8Val(MIPC_DATA_GET_PDP_CID_CNF_T_MIN_CID, 0);
    int max = (int) mipcCnf->getMipcUint8Val(MIPC_DATA_GET_PDP_CID_CNF_T_MAX_CID,
            DEFAULT_PDN_TABLE_SIZE);
    RFX_LOG_I(RFX_LOG_TAG, "[%d][%s] min_cid:%d, max_id:%d",
            m_slot_id, __FUNCTION__, min, max);
    return (max - min) + 1;

}
