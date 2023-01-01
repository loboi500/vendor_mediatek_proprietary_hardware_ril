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
#include "RtmImsConferenceController.h"
#include "RtmImsConferenceCallMessageHandler.h"
#include "RfxRootController.h"
#include "cc/RtmCallController.h"

#include "RfxImsCallInfo.h"
#include "RfxImsConfData.h"
#include "RfxDialogInfoData.h"
#include "RfxIntsData.h"
#include "RfxRilUtils.h"
#include "RfxStringData.h"
#include "RfxStringsData.h"
#include "RfxVoidData.h"
#include "rfx_properties.h"
#include "cc/RtmCallController.h"

/*****************************************************************************
 * Class RfxController
 *****************************************************************************/

#define RFX_LOG_TAG "RtmImsEvent"
#define MIN_IMS_CALL_MODE 20

RFX_IMPLEMENT_CLASS("RtmImsConferenceController", RtmImsConferenceController, RfxController);

// register request to RfxData
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxStringsData, RfxVoidData, RFX_MSG_REQUEST_ADD_IMS_CONFERENCE_CALL_MEMBER);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxStringsData, RfxVoidData, RFX_MSG_REQUEST_REMOVE_IMS_CONFERENCE_CALL_MEMBER);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxVoidData, RfxVoidData, RFX_MSG_REQUEST_CONFERENCE);

RFX_REGISTER_DATA_TO_URC_ID(RfxStringsData, RFX_MSG_URC_IMS_EVENT_PACKAGE_INDICATION);
RFX_REGISTER_DATA_TO_URC_ID(RfxImsConfData, RFX_MSG_UNSOL_IMS_CONFERENCE_INFO_INDICATION);
RFX_REGISTER_DATA_TO_URC_ID(RfxStringsData, RFX_MSG_UNSOL_LTE_MESSAGE_WAITING_INDICATION);
RFX_REGISTER_DATA_TO_URC_ID(RfxDialogInfoData, RFX_MSG_URC_IMS_DIALOG_INDICATION);


RtmImsConferenceController::RtmImsConferenceController() : mNormalCallsMerge(false),
        mInviteByNumber(false), mIsMerging(false), mEconfCount(0),
        mFakeDisconnectedCallProcessingCount(0) {
}

RtmImsConferenceController::~RtmImsConferenceController() {
}

void RtmImsConferenceController::onInit() {
    // Required: invoke super class implementation
    RfxController::onInit();

    mRtmImsConferenceHandler = new RtmImsConferenceHandler(getSlotId());
    mRtmImsDialogHandler = new RtmImsDialogHandler(getSlotId());

    const int request_id_list[] = {
        RFX_MSG_REQUEST_ADD_IMS_CONFERENCE_CALL_MEMBER,
        RFX_MSG_REQUEST_REMOVE_IMS_CONFERENCE_CALL_MEMBER,
        RFX_MSG_REQUEST_CONFERENCE,
    };

    const int urc_id_list[] = {
        RFX_MSG_URC_IMS_EVENT_PACKAGE_INDICATION,
        RFX_MSG_UNSOL_IMS_CONFERENCE_INFO_INDICATION,
    };

    // register request & URC id list
    // NOTE. one id can only be registered by one controller
    registerToHandleRequest(request_id_list, sizeof(request_id_list)/sizeof(const int));
    registerToHandleUrc(urc_id_list, sizeof(urc_id_list)/sizeof(const int));
}

void RtmImsConferenceController::onDeinit() {
    logD(RFX_LOG_TAG, "onDeinit");
    RfxController::onDeinit();
    delete mRtmImsConferenceHandler;
    mRtmImsConferenceHandler = NULL;
    delete mRtmImsDialogHandler;
    mRtmImsDialogHandler = NULL;
}

bool RtmImsConferenceController::onHandleRequest(const sp<RfxMessage>& message) {
    return handleMessgae(message);
}

bool RtmImsConferenceController::onHandleUrc(const sp<RfxMessage>& message) {
    return handleUrc(message);
}

bool RtmImsConferenceController::onHandleResponse(const sp<RfxMessage>& message) {
    return handleResponse(message);
}

bool RtmImsConferenceController::onCheckIfRejectMessage(
        const sp<RfxMessage>& message, bool isModemPowerOff, int radioState) {

    int isWfcSupport = RfxRilUtils::isWfcSupport();

    if (isWfcSupport == 1 && !isModemPowerOff) {
        return false;
    }

    return RfxController::onCheckIfRejectMessage(message, isModemPowerOff, radioState);
}

bool RtmImsConferenceController::handleMessgae(const sp<RfxMessage>& message) {
    int msg_id = message->getId();
    //logD(RFX_LOG_TAG, "onHandleRequest: %s", RFX_ID_TO_STR(msg_id));
    bool needSendRequestToMcl = true;

    switch (msg_id) {
        case RFX_MSG_REQUEST_ADD_IMS_CONFERENCE_CALL_MEMBER:
            //handleAddMember(message);
            break;
        case RFX_MSG_REQUEST_REMOVE_IMS_CONFERENCE_CALL_MEMBER:
            //needSendRequestToMcl = false;
            //handleRemoveMember(message);
            break;
        case RFX_MSG_REQUEST_CONFERENCE:
            handleMergeConferenece(message);
            if (mOriginalMergeMessage != NULL) {
                needSendRequestToMcl = false;
            }
            break;
        default:
            break;
    }
    if (needSendRequestToMcl) {
        requestToMcl(message);
    }
    return true;
}

bool RtmImsConferenceController::handleResponse(const sp<RfxMessage>& message) {
    int msg_id = message->getId();
    //logD(RFX_LOG_TAG, "onHandleResponse: %s", RFX_ID_TO_STR(msg_id));
    bool needSendRespone = true;
    switch (msg_id) {
        case RFX_MSG_REQUEST_ADD_IMS_CONFERENCE_CALL_MEMBER:
        case RFX_MSG_REQUEST_CONFERENCE:
            needSendRespone = handleAddMemberResponse(message);
            break;
        case RFX_MSG_REQUEST_REMOVE_IMS_CONFERENCE_CALL_MEMBER:
            handleRemoveMemberResponse(message);
            break;
        default:
            break;
    }
    if (needSendRespone) {
        responseToRilj(message);
    }
    return true;
}

bool RtmImsConferenceController::handleUrc(const sp<RfxMessage>& message) {
    int msg_id = message->getId();
    //RfxStringsData* data = (RfxStringsData*)message->getData();
    //char** params = (char**)data->getData();
    logD(RFX_LOG_TAG, "onHandleUrc: %s", RFX_ID_TO_STR(msg_id));
    bool ret = false;
    switch (msg_id) {
        case RFX_MSG_UNSOL_CALL_INFO_INDICATION:
            handleImsCallInfoUpdate(message);
            break;
        case RFX_MSG_UNSOL_ECONF_RESULT_INDICATION:
            handleEconfUpdate(message);
            break;
        case RFX_MSG_URC_IMS_EVENT_PACKAGE_INDICATION:
            handleImsEventPackageIndication(message);
            ret = true;
            break;
        case RFX_MSG_UNSOL_IMS_CONFERENCE_INFO_INDICATION:
            handleImsConfInfoIndication(message);
            ret = true;
            break;
        case RFX_MSG_UNSOL_SIP_CALL_PROGRESS_INDICATOR:
            // handleSipCallProgressIndicator(message);
            break;
        default:
            break;
    }
    return ret;
}

void RtmImsConferenceController::handleConferenceStart() {
    if (mRtmImsConferenceHandler != NULL) {
        mRtmImsConferenceHandler->startConference();
    }
}

void RtmImsConferenceController::handleOneKeyConference(const sp<RfxMessage>& message) {
    RfxStringsData* data = (RfxStringsData*)message->getData();
    char** params = (char**)data->getData();
    int numOfMembers = atoi(params[1]);
    // get number sequence
    int offSet = 2;
    vector<string> members;
    for (int i = 0; i < numOfMembers; ++i) {
        char* addr = params[i + offSet];
        if (addr != NULL) {
            string memberNum(addr);
            members.push_back(memberNum);
        }
    }
    if (mRtmImsConferenceHandler != NULL) {
        mRtmImsConferenceHandler->tryOneKeyAddLocalList(members);
        mRtmImsConferenceHandler->startConference();
    }
}

void RtmImsConferenceController::handleOneKeyConferenceFail(const sp<RfxMessage>& message) {
    RFX_UNUSED(message);

    if (mRtmImsConferenceHandler != NULL) {
        mRtmImsConferenceHandler->closeConference();
    }
    while (!mCachedCEPMessageQueue.empty()) {
        mCachedCEPMessageQueue.pop();
    }
}

void RtmImsConferenceController::handleAddMember(const sp<RfxMessage>& message) {
    //int msg_id = message->getId();
    RfxStringsData* data = (RfxStringsData*)message->getData();
    char** params = (char**)data->getData();
    char* address = params[1];
    int callId = atoi(params[2]);
    Vector<RfxImsCallInfo*> calls =
            getStatusManager(m_slot_id)->getImsCallInfosValue(RFX_STATUS_KEY_IMS_CALL_LIST);
    logD(RFX_LOG_TAG, "handleAddMember: %d", callId);

    if (callId == -1) {  // One-key add member
        mInviteByNumber = true;
        if (mRtmImsConferenceHandler != NULL && address != NULL) {
            mRtmImsConferenceHandler->tryOneKeyAddParticipant(address);
        }
    } else {  // normal add member by merge
        mIsMerging = true;
        mIsAddingMember = true;
        for (int i = 0; i < (int)calls.size(); i++) {
            if (calls[i]->getCallId() == callId && calls[i]->isConference() == false) {
                if (mRtmImsConferenceHandler != NULL && address != NULL) {
                    mRtmImsConferenceHandler->tryAddParticipant(address);
                }
            }
        }
    }
}

void RtmImsConferenceController::handleRemoveMember(const sp<RfxMessage>& message) {
    int msg_id = message->getId();
    RfxStringsData* data = (RfxStringsData*)message->getData();
    char** params = (char**)data->getData();
    //char* address = params[1];
    char **newData = (char **) calloc(3, sizeof(char *));
    //string newAddressStr;
    //string retryAddressStr;
    if (newData == NULL) {
        logE(RFX_LOG_TAG, "handleRemoveMember, newData calloc fail!");
        sp<RfxMessage> responseMsg = RfxMessage::obtainResponse(RIL_E_NO_MEMORY, message, false);
        responseToRilj(responseMsg);
        return;
    }

    //if (mRtmImsConferenceHandler != NULL && address != NULL) {
        //mRtmImsConferenceHandler->tryRemoveParticipant(address);
        //newAddressStr = mRtmImsConferenceHandler->getConfParticipantUri(address, false);
        //retryAddressStr = mRtmImsConferenceHandler->getConfParticipantUri(address, true);
    //}
    newData[0] = strdup(params[0]);
    newData[1] = strdup(params[1]);
    newData[2] = strdup(params[2]);
    //newData[3] = strdup(retryAddressStr.c_str());

    //mIsRemovingMember = true;
    sp<RfxMessage> request = RfxMessage::obtainRequest(msg_id,
            RfxStringsData(newData, 3), message, false);
    requestToMcl(request);
    for (int i = 0; i < 3; i++) {
        if (newData[i] != NULL) {
            free(newData[i]);
        }
    }
    free(newData);
}

void RtmImsConferenceController::handleMergeConferenece(const sp<RfxMessage>& message) {
    mIsMerging = true;
    Vector<RfxImsCallInfo*> calls =
            getStatusManager(m_slot_id)->getImsCallInfosValue(RFX_STATUS_KEY_IMS_CALL_LIST);

    int confCallId = 0;
    Vector<string> numbers;
    Vector<string> callIds;

    for (int i = 0; i < (int)calls.size(); i++) {
        if (calls[i]->isConferenceHost() == true) {
            confCallId = calls[i]->getCallId();
        }
        if (calls[i]->isConference() == false) {
            const char* number = calls[i]->getNumber().string();
            if (number != NULL) {
                numbers.push_back(number);
                callIds.push_back(to_string(calls[i]->getCallId()));
            }
        }
    }

    // Handle Confernece call & Normal call merge.
    if (confCallId > 0 && callIds.size() > 0) {
        char **newData = (char **) calloc(3, sizeof(char *));
        if (newData == NULL) {
            logE(RFX_LOG_TAG, "handleMergeConferenece, newData calloc fail!");
            sp<RfxMessage> responseMsg = RfxMessage::obtainResponse(RIL_E_NO_MEMORY, message, false);
            responseToRilj(responseMsg);
            return;
        }
        newData[0] = strdup(to_string(confCallId).c_str());
        newData[1] = strdup(numbers[0].c_str());
        newData[2] = strdup(callIds[0].c_str());
        sp<RfxMessage> request = RfxMessage::obtainRequest(
                RFX_MSG_REQUEST_ADD_IMS_CONFERENCE_CALL_MEMBER,
                RfxStringsData(newData, 3), message, false);
        //handleAddMember(request);
        mOriginalMergeMessage = RfxMessage::obtainRequest(
                m_slot_id, RFX_MSG_REQUEST_CONFERENCE, message);
        requestToMcl(request);

        for (int i = 0; i < 3; i++) {
            if (newData[i] != NULL) {
                free(newData[i]);
            }
        }
        free(newData);
        return;
    } else {
        // Handle Normal call & Normal call merge.
        mNormalCallsMerge = true;
        mEconfCount = 0;
        Vector<string> numbers;
        for (int i = 0; i < (int)calls.size(); i++) {
            RfxImsCallInfo* call = calls[i];
            if (call->isConference() == false) {
                const char* number = call->getNumber().string();
                if (number != NULL) {
                    numbers.push_back(number);
                }
            }
            if (call->getCallState() == RfxImsCallInfo::STATE_ESTABLISHED) {
                mActiveCallIdBeforeMerge = call->getCallId();
            }
        }
        if (mRtmImsConferenceHandler != NULL && numbers.size() >= 2) {
            mRtmImsConferenceHandler->firstMerge(callIds[0], callIds[1], numbers[0], numbers[1]);
        }
    }
}

void RtmImsConferenceController::handleImsConfInfoIndication(const sp<RfxMessage>& message) {
    int dataLen = message->getData()->getDataLength();
    int count = dataLen / sizeof(RIL_Conference_Participants);
    logD(RFX_LOG_TAG, "count of participants is %d", count);
    if (count == 0) return;

    RIL_Conference_Participants* participants =
            (RIL_Conference_Participants *) message->getData()->getData();
    if (participants == NULL) {
        logE(RFX_LOG_TAG, "participants is null");
        return;
    }

    sp<RfxMessage> msg = RfxMessage::obtainUrc(getSlotId(),
            RFX_MSG_UNSOL_IMS_CONFERENCE_INFO_INDICATION,
            RfxImsConfData((void*)participants, sizeof(RIL_Conference_Participants) * count));
    responseToRilj(msg);
}

void RtmImsConferenceController::handleImsEventPackageIndication(const sp<RfxMessage>& message) {
    /*
     * +EIMSEVTPKG: <call_id>,<type>,<urc_index>,<total_urc_count>,<data>
     * <call_id>:  0~255
     * <type>: 1 = Conference Event Package; 2 = Dialog Event Package; 3 = Message Waiting Event Package
     * <urc_index>: 1~255, the index of URC part
     * <total_urc_count>: 1~255
     * <data>: xml raw data, max length = 1950
     */

    RfxStringsData* data = (RfxStringsData*)message->getData();
    char** params = (char**)data->getData();
    int msgType = atoi(params[1]);

    if (msgType == 1) {
        // For multiple Urc case, only cache the last.
        if ((mIsAddingMember || mIsRemovingMember)) {
            logD(RFX_LOG_TAG, "handleImsEventPackageIndication: cache CEP");
            mCachedCEPMessageQueue.push(message);
        } else {
            mRtmImsConferenceHandler->handleImsConfCallMessage(message);
        }
        return;
    } else if (msgType == 2) {
        mRtmImsDialogHandler->handleImsDialogMessage(message);
        return;
    } else if (msgType == 3) {
        sp<RfxMessage> msg = RfxMessage::obtainUrc(message->getSlotId(),
                RFX_MSG_UNSOL_LTE_MESSAGE_WAITING_INDICATION, message, true);
        responseToRilj(msg);
    } else if (msgType == 100) {  //ims video ringtone event
        const int maxLen = 5;
        char **urcData = (char **) calloc(maxLen, sizeof(char *));
        RFX_ASSERT(urcData != NULL);

        urcData[0] = strdup(params[0]); //call id
        urcData[1] = strdup(params[1]); //type
        urcData[2] = strdup(params[4]); //event info, parsed by L5

        sp<RfxMessage> msg = RfxMessage::obtainUrc(m_slot_id, RFX_MSG_UNSOL_VIDEO_RINGTONE_EVENT_IND,
                RfxStringsData(urcData, maxLen));
        responseToRilj(msg);

        for (int i = 0; i < maxLen; i++) {
            if (urcData[i] != NULL) {
                free(urcData[i]);
            }
        }
        free(urcData);
    }
}

void RtmImsConferenceController::handleImsCallInfoUpdate(const sp<RfxMessage>& message) {
    /* +ECPI: <call_id>, <msg_type>, <is_ibt>,
    *        <is_tch>, <dir>, <call_mode>, <number>, <type>, "<pau>", [<cause>] */
    RfxStringsData* data = (RfxStringsData*)message->getData();
    char** params = (char**)data->getData();
    int callId = atoi(params[0]);
    //char* number = params[6];
    int msgType = atoi(params[1]);
    if (msgType == 133) {
        Vector<RfxImsCallInfo*> calls = getStatusManager(m_slot_id)->getImsCallInfosValue(
                RFX_STATUS_KEY_IMS_CALL_LIST);
        int count = (int)calls.size();
        for (int i = 0; i < count; i++) {
            if (calls[i]->getCallId() == callId && calls[i]->isConferenceHost() == true) {
                while (!mCachedCEPMessageQueue.empty()) {
                    mCachedCEPMessageQueue.pop();
                }
                mIsAddingMember = false;
                mIsRemovingMember = false;
                if (mRtmImsConferenceHandler != NULL) {
                    mRtmImsConferenceHandler->closeConference();
                    mFakeDisconnectedCallProcessingCount = 0;
                    mFakeDisconnectedCallIdList.clear();
                    return;
                }
            }
        }
        if (count == 0 || (count == 1 && calls[0]->getCallId() == callId)) {
            while (!mCachedCEPMessageQueue.empty()) {
                mCachedCEPMessageQueue.pop();
            }
            mIsAddingMember = false;
            mIsRemovingMember = false;
            if (mRtmImsConferenceHandler != NULL) {
                mRtmImsConferenceHandler->closeConference();
                mFakeDisconnectedCallProcessingCount = 0;
                mFakeDisconnectedCallIdList.clear();
            }
        }
    }
}

void RtmImsConferenceController::handleEconfUpdate(const sp<RfxMessage>& message) {
    // +ECONF:<conf_call_id>,<op>,<num>,<result>,<cause>[,<joined_call_id>]
    RfxStringsData* data = (RfxStringsData*)message->getData();
    char** params = (char**)data->getData();
    int result = atoi(params[3]);
    char* joined_call_id = params[5];

    logD(RFX_LOG_TAG, "handleEconfUpdate: mNormalCallsMerge:%d", mNormalCallsMerge);
    if (mNormalCallsMerge) {
        mEconfCount++;
        //if (result == 0 && mRtmImsConferenceHandler != NULL && joined_call_id != NULL) {
            //mRtmImsConferenceHandler->addFirstMergeParticipant(joined_call_id);
        //}
        if (mEconfCount == 2) {
            if (mRtmImsConferenceHandler != NULL) {
                if (result == 0) {
                    handleSpecificConferenceMode();
                    //modifyParticipantComplete();
                } else {
                    mRtmImsConferenceHandler->modifyParticipantFailed();
                }
            }
            mEconfCount = 0;
            mNormalCallsMerge = false;
            mIsMerging = false;
        }
    } else {
        mIsMerging = false;
        if (mRtmImsConferenceHandler != NULL) {
            if (result == 0) {
                //modifyParticipantComplete();
            } else {
                mRtmImsConferenceHandler->modifyParticipantFailed();
            }
        }
        //tryhandleCachedCEP();
    }
}

void RtmImsConferenceController::handleSipCallProgressIndicator(const sp<RfxMessage>& message) {
    if (mRtmImsConferenceHandler != NULL) {
        mRtmImsConferenceHandler->handleOneKeyInviteNotifyResult(message);
    }
}

bool RtmImsConferenceController::handleAddMemberResponse(const sp<RfxMessage>& response) {
    RtmCallController *ctrl = (RtmCallController *) findController(m_slot_id,
                    RFX_OBJ_CLASS_INFO(RtmCallController));
    bool needSendRespone = true;

    if (response->getError() != RIL_E_SUCCESS) {
        //tryhandleCachedCEP();
        mInviteByNumber = false;
        mIsMerging = false;
        if (mRtmImsConferenceHandler != NULL) {
            mRtmImsConferenceHandler->modifyParticipantFailed();
        }
        needSendRespone = tryhandleAddMemberByMerge(response);
        if (mNormalCallsMerge) {
            //ctrl->retrieveMergeFail(mActiveCallIdBeforeMerge);
            mNormalCallsMerge = false;
            mActiveCallIdBeforeMerge = 0;
        }
        return needSendRespone;
    }
    if (mInviteByNumber) {
        mInviteByNumber = false;
        // modifyParticipantComplete();
    } else {
        ctrl->onMergeStart();
    }
    needSendRespone = tryhandleAddMemberByMerge(response);
    return needSendRespone;
}

void RtmImsConferenceController::handleRemoveMemberResponse(const sp<RfxMessage>& response) {
    if (response->getError() != RIL_E_SUCCESS) {
        //tryhandleCachedCEP();
        mIsMerging = false;
        if (mRtmImsConferenceHandler != NULL) {
            mRtmImsConferenceHandler->modifyParticipantFailed();
        }
        return;
    }

    if (mRtmImsConferenceHandler != NULL) {
        //modifyParticipantComplete();
    }
    //tryhandleCachedCEP();
}

void RtmImsConferenceController::modifyParticipantComplete() {
    bool ret = mRtmImsConferenceHandler->modifyParticipantComplete();
    if (ret) {
        onParticipantsUpdate(false);
    }
    logD(RFX_LOG_TAG, "start  Timer");
    mTimeoutHandle = RfxTimer::start(RfxCallback0(this,
            &RtmImsConferenceController::onTimeout), ms2ns(5000));
}

void RtmImsConferenceController::onTimeout() {
    logD(RFX_LOG_TAG, "onTimeout");

    // check if need special handling for conference
    RfxStatusKeyEnum key = RFX_STATUS_KEY_IMS_SPECIFIC_CONFERENCE_MODE;
    if (getStatusManager(m_slot_id)->getString8Value(key) == "1") {
        logD(RFX_LOG_TAG, "onTimeout, KDDI case and no need update paticipant to hide manage menu");
        return;
    }

    if(mRtmImsConferenceHandler != NULL) {
        mRtmImsConferenceHandler->updateConferenceStateWithLocalCache();
    }
}

void RtmImsConferenceController::tryhandleCachedCEP() {
    logD(RFX_LOG_TAG, "tryhandleCachedCEP adding:%d, removing:%d",
            mIsAddingMember, mIsRemovingMember);
    if (mIsAddingMember || mIsRemovingMember) {
        if (mIsRemovingMember) {
            mIsRemovingMember = false;
        }
        if (mIsAddingMember) {
            mIsAddingMember = false;
        }
        logD(RFX_LOG_TAG, "mCachedCEPMessageQueue size:%d", (int)mCachedCEPMessageQueue.size());
        while (!mCachedCEPMessageQueue.empty()) {
            if (mRtmImsConferenceHandler != NULL) {
                mRtmImsConferenceHandler->handleImsConfCallMessage(mCachedCEPMessageQueue.front());
            }
            mCachedCEPMessageQueue.pop();
        }
    }
}

bool RtmImsConferenceController::tryhandleAddMemberByMerge(const sp<RfxMessage>& response) {
    if (mOriginalMergeMessage != NULL) {
        sp<RfxMessage> newResponse = RfxMessage::obtainResponse(response->getError(),
                mOriginalMergeMessage, false);
        responseToRilj(newResponse);
        mOriginalMergeMessage = NULL;
        return false;
    }
    return true;
}

void RtmImsConferenceController::onParticipantsUpdate(bool autoTerminate) {
    vector<sp<ConferenceCallUser>> users =
            mRtmImsConferenceHandler->getConfParticipantsInfo();
    RtmCallController *ctrl =
            (RtmCallController *) findController(m_slot_id,
                    RFX_OBJ_CLASS_INFO(RtmCallController));
    ctrl->onParticipantsUpdate(users, autoTerminate);

    int count = (int)users.size();
    logD(RFX_LOG_TAG, "count %d, autoTerminate %d", count, autoTerminate);

    if (autoTerminate || count == 0) return;

    RIL_Conference_Participants* participants = (RIL_Conference_Participants*)
            calloc(1, sizeof(RIL_Conference_Participants) * count);
    if (participants == NULL) {
        logE(RFX_LOG_TAG, "participants calloc fail!");
        return;
    }

    for(int i = 0; i < count; i++) {
        sp<ConferenceCallUser> user = users[i];
        int len = strlen(user->mDisplayText.c_str());
        participants[i].display_text = (char*) calloc(1, len + 1);
        strncpy(participants[i].display_text, user->mDisplayText.c_str(), len);
        len = strlen(user->mEndPoint.c_str());
        participants[i].end_point    = (char*) calloc(1, len + 1);
        strncpy(participants[i].end_point, user->mEndPoint.c_str(), len);
        len = strlen(user->mEntity.c_str());
        participants[i].entity       = (char*) calloc(1, len + 1);
        strncpy(participants[i].entity, user->mEntity.c_str(), len);
        len = strlen(user->mStatus.c_str());
        participants[i].status       = (char*) calloc(1, len + 1);
        strncpy(participants[i].status, user->mStatus.c_str(), len);
        len = strlen(user->mUserAddr.c_str());
        participants[i].useraddr     = (char*) calloc(1, len + 1);
        strncpy(participants[i].useraddr, user->mUserAddr.c_str(), len);
    }
    sp<RfxMessage> msg = RfxMessage::obtainUrc(getSlotId(),
            RFX_MSG_UNSOL_IMS_CONFERENCE_INFO_INDICATION,
            RfxImsConfData((void*)participants, sizeof(RIL_Conference_Participants) * count));
    if (participants != NULL) {
        for (int i = 0; i < count; i++) {
            free(participants[i].useraddr);
            free(participants[i].end_point);
            free(participants[i].display_text);
            free(participants[i].status);
            free(participants[i].entity);
        }
        free(participants);
    }

    responseToRilj(msg);
}

void RtmImsConferenceController::handleSpecificConferenceMode() {
    // check if need special handling for conference
    RfxStatusKeyEnum key = RFX_STATUS_KEY_IMS_SPECIFIC_CONFERENCE_MODE;

    if (getStatusManager(m_slot_id)->getString8Value(key) == "1") {
        logD(RFX_LOG_TAG, "handleEconfUpdate(), special conference mode with mode = 1");

        // KDDI conference handling:
        //   KDDI conference won't terminate the participant after merge complete.
        //   Because user cannot see or do anything for these calls,
        //   AP will just view as terminated and skip the following event for them

        RfxStatusKeyEnum key2 = RFX_STATUS_KEY_IMS_CALL_LIST;
        Vector<RfxImsCallInfo*> calls = getStatusManager(m_slot_id)->getImsCallInfosValue(key2);

        int count = (int)calls.size();

        for (int i = 0; i < count; i++) {
            // +ECPI:<call_id>, <msg_type>, <is_ibt>, <is_tch>, <dir>, <call_mode>[, <number>, <toa>], "",<cause>

            if (calls[i]->isConference() == false) {
                int maxLen = 10;
                char *params[maxLen];
                int callId = calls[i]->getCallId();
                String8 callNumber = calls[i]->getNumber();
                int ret = 0;

                logD(RFX_LOG_TAG, "handleSpecificConferenceMode(), fake disconnect for call id = %d, number = %s",
                        callId, RfxRilUtils::pii(RFX_LOG_TAG, callNumber.string()));

                params[0] = (char *) alloca(3);
                ret = sprintf(params[0], "%d", callId);
                if (ret < 0) return;

                params[1] = (char *) alloca(4);
                ret = sprintf(params[1], "%d", 133);
                if (ret < 0) return;

                // for 133 case, these param is no need
                for (int j=2; j < 5; j++) {
                    params[j] = (char *) alloca(2);
                    ret = sprintf(params[j], "%d", 0);
                    if (ret < 0) return;
                }

                // if KDDI support ViLTE, need to chang this
                params[5] = (char *) alloca(3);
                ret = sprintf(params[5], "%d", 20);
                if (ret < 0) return;

                params[6] = (char *) alloca(strlen(callNumber.string()) + 1);
                ret = sprintf(params[6], "%s", callNumber.string());
                if (ret < 0) return;

                // for 133 case, these param is no need
                for (int j=7; j < 10; j++) {
                    params[j] = (char *) alloca(1);
                    ret = sprintf(params[j], "");
                    if (ret < 0) return;
                }

                mFakeDisconnectedCallProcessingCount++;
                mFakeDisconnectedCallIdList.push_back(callId);

                RfxStringsData data(params, maxLen);
                sp<RfxMessage> urcToRilj = RfxMessage::obtainUrc(
                                            m_slot_id,
                                            RFX_MSG_UNSOL_CALL_INFO_INDICATION,
                                            data);

                RtmCallController *imsCallCtrl = (RtmCallController *) findController(
                        m_slot_id, RFX_OBJ_CLASS_INFO(RtmCallController));

                imsCallCtrl->notifyCallInfoUpdate(urcToRilj);
            }
        }
    }
}

bool RtmImsConferenceController::needProcessFakeDisconnect() {
    logD(RFX_LOG_TAG, "needProcessFakeDisconnect(),  mFakeDisconnectedCallProcessingCount = %d",
            mFakeDisconnectedCallProcessingCount);

    return (mFakeDisconnectedCallProcessingCount > 0);
}

void RtmImsConferenceController::processFakeDisconnectDone() {
    logD(RFX_LOG_TAG, "processFakeDisconnectDone(),  mFakeDisconnectedCallProcessingCount = %d",
            mFakeDisconnectedCallProcessingCount);

    mFakeDisconnectedCallProcessingCount--;
}

bool RtmImsConferenceController::needSkipDueToFakeDisconnect(int callid) {
    logD(RFX_LOG_TAG, "needSkipDueToFakeDisconnect(),  callid = %d", callid);

    int listSize = mFakeDisconnectedCallIdList.size();
    for (int i = 0; i < listSize; i++) {

        int item = mFakeDisconnectedCallIdList.itemAt(i);
        if (item == callid) {
            logD(RFX_LOG_TAG, "needSkipDueToFakeDisconnect(), Need to skip");
            return true;
        }
    }
    logD(RFX_LOG_TAG, "needSkipDueToFakeDisconnect(), No Need to skip");
    return false;
}
/* IMS Call End */
