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
#include <string>
#include <vector>

#include "RtmSuppServController.h"
#include "RtmSuppServUtil.h"
#include "RfxRilUtils.h"
#include "RtmSuppServQueue.h"
#include "RfxMainThread.h"
#include <mtkconfigutils.h>
#include <libmtkrilutils.h>
#include <unistd.h>

#ifdef RFX_LOG_TAG
#undef RFX_LOG_TAG
#endif
#define RFX_LOG_TAG "RtmSuppServController"
/*****************************************************************************
 * Class RfxController
 *****************************************************************************/

RFX_IMPLEMENT_CLASS("RtmSuppServController", RtmSuppServController, RfxController);

RtmSuppServController::RtmSuppServController() {
    mQueue = RtmSuppServQueue::getInstance();

    // We send USSD URC to GSM by default
    mUssdDestination = USSD_URC_TO_GSM;
}

RtmSuppServController::~RtmSuppServController() {
    logD(RFX_LOG_TAG, "~RtmSuppServController");
}

void RtmSuppServController::onInit() {
    // Required: invoke super class implementation
    logD(RFX_LOG_TAG, "RtmSuppServController onInit!");
    RfxController::onInit();

    const int request_id_list[] = {
        RFX_MSG_REQUEST_SEND_USSD,
        RFX_MSG_REQUEST_CANCEL_USSD,
        RFX_MSG_REQUEST_SEND_USSI,
        RFX_MSG_REQUEST_CANCEL_USSI,
        RFX_MSG_REQUEST_GET_CLIR,
        RFX_MSG_REQUEST_SET_CLIR,
        RFX_MSG_REQUEST_SET_CALL_FORWARD,
        RFX_MSG_REQUEST_QUERY_CALL_FORWARD_STATUS,
        RFX_MSG_REQUEST_QUERY_CALL_FORWARD_IN_TIME_SLOT,
        RFX_MSG_REQUEST_SET_CALL_FORWARD_IN_TIME_SLOT,
        RFX_MSG_REQUEST_QUERY_CALL_WAITING,
        RFX_MSG_REQUEST_SET_CALL_WAITING,
        RFX_MSG_REQUEST_QUERY_CALL_BARRING,
        RFX_MSG_REQUEST_SET_CALL_BARRING,
        RFX_MSG_REQUEST_CHANGE_BARRING_PASSWORD,
        RFX_MSG_REQUEST_QUERY_CLIP,
        RFX_MSG_REQUEST_SET_CLIP,
        RFX_MSG_REQUEST_GET_COLR,
        RFX_MSG_REQUEST_SET_COLR,
        RFX_MSG_REQUEST_GET_COLP,
        RFX_MSG_REQUEST_SET_COLP,
        RFX_MSG_REQUEST_SEND_CNAP,
        RFX_MSG_REQUEST_SET_SUPP_SVC_NOTIFICATION,
        RFX_MSG_REQUEST_GET_XCAP_STATUS,
//        RFX_MSG_REQUEST_SET_CALL_WAITING_ATCI,
        RFX_MSG_REQUEST_RESET_SUPP_SERV,
        RFX_MSG_REQUEST_SETUP_XCAP_USER_AGENT_STRING,
        RFX_MSG_REQUEST_SET_SS_PROPERTY
//        RFX_MSG_REQUEST_USSD_DOMAIN_INFO_REQ
    };

    const int urc_id_list[] = {
        RFX_MSG_UNSOL_ON_USSD,
        RFX_MSG_UNSOL_ON_USSI
    };

    // register request & URC id list
    // NOTE. one id can only be registered by one controller
    registerToHandleRequest(request_id_list, sizeof(request_id_list)/sizeof(const int));
    registerToHandleUrc(urc_id_list, sizeof(urc_id_list)/sizeof(const int));
}

void RtmSuppServController::onDeinit() {
    logD(RFX_LOG_TAG, "onDeinit");
    mQueue->clear();
    RfxController::onDeinit();
}

bool RtmSuppServController::onHandleRequest(const sp<RfxMessage>& message) {
    int msg_id = message->getId();
    int token = message->getPToken();

    // Notice :some requests, no need to add them into the queue. Directly send it to mdcomm layer

    sp<RfxMessage> responseNotSupportMsg = RfxMessage::obtainResponse(RIL_E_REQUEST_NOT_SUPPORTED,
            message, false);

    // Check if current project is a data only project by CONFIG_SS_MODE
    FeatureValue featurevalue;
    memset(featurevalue.value, 0, sizeof(featurevalue.value));
    mtkGetFeature(CONFIG_SS_MODE, &featurevalue);
    logD(RFX_LOG_TAG, "Check data only project, CONFIG_SS_MODE = %s", featurevalue.value);

    if (strcmp(featurevalue.value, "1") != 0) {
        responseToRilj(responseNotSupportMsg);
        return true;
    }

    logD(RFX_LOG_TAG, "onHandleRequest - %s", RFX_ID_TO_STR(msg_id));
    switch (msg_id) {
        case RFX_MSG_REQUEST_SEND_USSD:
            if (getStatusManager()->getBoolValue(RFX_STATUS_KEY_USSD_SESSION_ONGOING)) {
            logD(RFX_LOG_TAG, "USSD session is ongoing, rejected.");

                // Return SUCCESS first
                logD(RFX_LOG_TAG, "sendFailureReport, Return SUCCESS first by response");
                sp<RfxMessage> responseMsg = RfxMessage::obtainResponse(RIL_E_SUCCESS,
                            message, false);
                responseToRilj(responseMsg);

                // Let the UI have time to show up the "USSD code running" dialog
                usleep(300000);

                // And then report the FAILIRUE by URC
                logD(RFX_LOG_TAG, "sendFailureReport, Report the FAILIRUE by URC");
                // Generate a generic failure USSD URC
                char *genericUssdFail[2] = {(char *) "4", (char *) ""};
                sp<RfxMessage> urc = RfxMessage::obtainUrc(getSlotId(), RFX_MSG_UNSOL_ON_USSD,
                        RfxStringsData(genericUssdFail, 2));
                responseToRilj(urc);
                return true;
            } else {
                logD(RFX_LOG_TAG, "USSD session started, token = %d", token);
                getStatusManager()->setBoolValue(RFX_STATUS_KEY_USSD_SESSION_ONGOING, true);
            }
            break;
        case RFX_MSG_REQUEST_SEND_USSI:
            if (getStatusManager()->getBoolValue(RFX_STATUS_KEY_USSD_SESSION_ONGOING)) {
                logD(RFX_LOG_TAG, "USSI session is ongoing, rejected.");

                // Return SUCCESS first
                logD(RFX_LOG_TAG, "sendFailureReport, Return SUCCESS first by response");
                sp<RfxMessage> responseMsg = RfxMessage::obtainResponse(RIL_E_SUCCESS,
                            message, false);
                responseToRilj(responseMsg);

                // Let the UI have time to show up the "USSD code running" dialog
                usleep(300000);

                // And then report the FAILIRUE by URC
                logD(RFX_LOG_TAG, "sendFailureReport, Report the FAILIRUE by URC");
                // Generate a generic failure USSI URC
                char *genericUssdFail[2] = {(char *) "4", (char *) ""};
                sp<RfxMessage> urc = RfxMessage::obtainUrc(getSlotId(), RFX_MSG_UNSOL_ON_USSI,
                        RfxStringsData(genericUssdFail, 2));
                responseToRilj(urc);
                return true;
            } else {
                logD(RFX_LOG_TAG, "USSI session started, token = %d", token);
                getStatusManager()->setBoolValue(RFX_STATUS_KEY_USSD_SESSION_ONGOING, true);
            }
            break;
        case RFX_MSG_REQUEST_CANCEL_USSD:
        case RFX_MSG_REQUEST_CANCEL_USSI:
            if (getStatusManager()->getBoolValue(RFX_STATUS_KEY_USSD_SESSION_ONGOING)) {
                logD(RFX_LOG_TAG, "USSD session canceled.");
                getStatusManager()->setBoolValue(RFX_STATUS_KEY_USSD_SESSION_ONGOING, false);
            }
            break;
        case RFX_MSG_REQUEST_SET_SS_PROPERTY:
            responseToRilj(responseNotSupportMsg);
            break;
        default:
            break;
    }
    handleSSRequest(message);
    return true;
}

bool RtmSuppServController::onHandleUrc(const sp<RfxMessage>& message) {
    int msg_id = message->getId();
    int token = message->getPToken();
    switch(msg_id) {
        case RFX_MSG_UNSOL_ON_USSD:  // fall through
        case RFX_MSG_UNSOL_ON_USSI: {
            char** params = (char**) message->getData()->getData();
            int ussdMode = atoi(params[0]);
            int newId = (getUssdDestination() == USSD_URC_TO_GSM) ? RFX_MSG_UNSOL_ON_USSD
                    : RFX_MSG_UNSOL_ON_USSI;

            // Do not display any MMI dialog when +CUSD:3 and no session ongoing.
            // If there is a session ongoing, +CUSD:3 should be sent to UI and
            // the ression should be reset.
            if (ussdMode == 3 &&
                    !getStatusManager()->getBoolValue(RFX_STATUS_KEY_USSD_SESSION_ONGOING)) {
                return true;
            }

            // Change to comply with AOSP
            if (ussdMode == 2 || ussdMode == 3) {
                strncpy(params[0], "0", strlen(params[0]));
            }

            sp<RfxMessage> urcToRilj = RfxMessage::obtainUrc(m_slot_id, newId, message, true);

            // If USSD mode equals to 1, it means further user action is required.
            // Keep the UssdDestination the same. Otherwise, change mUssdDestination to
            // default value. Because the session come to an end.
            if (ussdMode == 1) {
                setUssdDestination(getUssdDestination());
            } else {
                setUssdDestination(USSD_URC_TO_GSM);
            }

            if (getStatusManager()->getBoolValue(RFX_STATUS_KEY_USSD_SESSION_ONGOING)) {
                logD(RFX_LOG_TAG, "USSD session completed, token = %d", token);
                getStatusManager()->setBoolValue(RFX_STATUS_KEY_USSD_SESSION_ONGOING, false);
            }

            responseToRilj(urcToRilj);
            break;
        }
        default:
            responseToRilj(message);
            break;
    }
    return true;
}

bool RtmSuppServController::onHandleResponse(const sp<RfxMessage>& message) {
    int msg_id = message->getId();
    int token = message->getPToken();
    logD(RFX_LOG_TAG, "onHandleResponse - %s", RFX_ID_TO_STR(msg_id));
    switch (msg_id) {
        case RFX_MSG_REQUEST_SEND_USSD:
            if(message->getError() != RIL_E_SUCCESS) {
                logD(RFX_LOG_TAG, "USSD session failed, end session, token = %d", token);
                getStatusManager()->setBoolValue(RFX_STATUS_KEY_USSD_SESSION_ONGOING, false);
            }
            break;
        case RFX_MSG_REQUEST_SEND_USSI:
            if(message->getError() != RIL_E_SUCCESS) {
                logD(RFX_LOG_TAG, "USSI session failed, end session, token = %d", token);
                getStatusManager()->setBoolValue(RFX_STATUS_KEY_USSD_SESSION_ONGOING, false);
            }
            break;
        default:
            break;
    }
    handleSSResponse(message);
    return true;
}

bool RtmSuppServController::onCheckIfRejectMessage(const sp<RfxMessage>& message,
        bool isModemPowerOff, int radioState) {
    RFX_UNUSED(message);
    int wfcState = getStatusManager()->getIntValue(RFX_STATUS_KEY_WFC_STATE, -1);
    logD(RFX_LOG_TAG, "onCheckIfRejectMessage isModemPowerOff %d, radioState: %d, wfcState: %d",
            (isModemPowerOff == false) ? 0 : 1, radioState, wfcState);

    /* If WFC is enabled, bypass all SS requests. */
    if (wfcState == 1) {
        return false;
    }

    int msgId = message->getId();
    if (msgId == RFX_MSG_REQUEST_SETUP_XCAP_USER_AGENT_STRING ||
        msgId == RFX_MSG_REQUEST_SET_SS_PROPERTY) {
        return false;
    }

    /* If WFC is not enabled and radio is off. reject the request in request_id_list*/
    if (radioState == (int)RADIO_STATE_UNAVAILABLE ||
            radioState == (int)RADIO_STATE_OFF ||
            isModemPowerOff == true) {
        return true;
    }

    /* If WFC is not enabled and radio is not off. Bypass all SS request */
    return false;
}

void RtmSuppServController::handleSSRequest(const sp<RfxMessage>& message) {
    int msg_id = message->getId();

    if (mQueue->getSSLock() == SS_LOCKED) {
        logD(RFX_LOG_TAG, "[%d]%s, a SS request is in process, add it into queue",
                message->getPToken(), RFX_ID_TO_STR(message->getId()));
        mQueue->add(RtmSSEntry(message));
    } else {
        logD(RFX_LOG_TAG, "[%d]%s, No SS request in process, directly execute it",
                message->getPToken(), RFX_ID_TO_STR(message->getId()));
        mQueue->setSSLock(SS_LOCKED);

        switch(msg_id) {
            case RFX_MSG_REQUEST_SEND_USSD:
                setUssdDestination(USSD_URC_TO_GSM);
                requestToMcl(message);
                break;
            case RFX_MSG_REQUEST_SEND_USSI:
                setUssdDestination(USSD_URC_TO_IMS);
                requestToMcl(message);
                break;
            case RFX_MSG_REQUEST_CANCEL_USSD:
                setUssdDestination(USSD_URC_TO_GSM);
                requestToMcl(message);
                break;
            case RFX_MSG_REQUEST_CANCEL_USSI:
                setUssdDestination(USSD_URC_TO_GSM);
                requestToMcl(message);
                break;
            default:
                requestToMcl(message);
                break;
        }
    }
}

void RtmSuppServController::handleSSResponse(const sp<RfxMessage>& message) {
    const RtmSSEntry *msgEntry;
    int msg_id = message->getId();
    logD(RFX_LOG_TAG, "[%d]%s, SS request's response", message->getPToken(),
            RFX_ID_TO_STR(message->getId()));
    if (!mQueue->isEmpty()) {
        msgEntry = &(mQueue->itemAt(0));
        logD(RFX_LOG_TAG, "the queue is not empty, pick [%d]%s to process",
                msgEntry->message->getPToken(), RFX_ID_TO_STR(msgEntry->message->getId()));

        requestToMcl(msgEntry->message);
        mQueue->removeFront();
    } else {
        // Release the lock if there is no message in the suspended queue
        logD(RFX_LOG_TAG, "No more SS request, release SS lock");
        mQueue->setSSLock(SS_UNLOCKED);
    }
    if (msg_id == RFX_MSG_REQUEST_QUERY_CALL_BARRING) {
        logD(RFX_LOG_TAG, "Direct to QUERY_CALL_BARRING to RtmCommSimController");
        msg_id = RFX_MSG_REQUEST_QUERY_FACILITY_LOCK;
        // Re-enqueue the message into main thread, RtmCommSimController will handle the response
        sp<RfxMessage> newMsg = RfxMessage::obtainResponse(msg_id, message);
        RfxMainThread::enqueueMessage(newMsg);
        return;
    } else if (msg_id == RFX_MSG_REQUEST_SET_CALL_BARRING) {
        logD(RFX_LOG_TAG, "Direct to SET_CALL_BARRING to RtmCommSimController");
        msg_id = RFX_MSG_REQUEST_SET_FACILITY_LOCK;
        // Re-enqueue the message into main thread, RtmCommSimController will handle the response
        sp<RfxMessage> newMsg = RfxMessage::obtainResponse(msg_id, message);
        RfxMainThread::enqueueMessage(newMsg);
        return;
    }

    responseToRilj(message);
}

UssdDestination RtmSuppServController::getUssdDestination() {
    logD(RFX_LOG_TAG, "getUssdDestination(): mUssdDestination = %s",
            ussdDestinationToString(mUssdDestination));
    return mUssdDestination;
}

void RtmSuppServController::setUssdDestination(UssdDestination destination) {
    logD(RFX_LOG_TAG, "setUssdDestination(): %s -> %s", ussdDestinationToString(mUssdDestination),
            ussdDestinationToString(destination));
    if (mUssdDestination == destination) {
        return;
    }
    mUssdDestination = destination;
}

const char *RtmSuppServController::ussdDestinationToString(UssdDestination destination) {
    switch (destination) {
        case USSD_URC_TO_GSM:
            return "USSD_URC_TO_GSM";
        case USSD_URC_TO_IMS:
            return "USSD_URC_TO_IMS";
        default:
            // not possible here!
            return NULL;
    }
}
