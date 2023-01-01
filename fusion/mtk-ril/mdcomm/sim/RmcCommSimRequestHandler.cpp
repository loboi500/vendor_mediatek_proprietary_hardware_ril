/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 *
 * MediaTek Inc. (C) 2016. All rights reserved.
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
#include "RfxBaseHandler.h"
#include "RfxSimIoRspData.h"
#include "RfxSimIoData.h"
#include "RfxSimAuthData.h"
#include "RfxSimGenAuthData.h"
#include "RfxSimOpenChannelData.h"
#include "RfxSimApduData.h"
#include "RfxVoidData.h"
#include "RfxStringData.h"
#include "RfxStringsData.h"
#include "RfxIntsData.h"
#include "RfxSimStatusData.h"
#include "RfxSimSlotStatusData.h"
#include "RfxRawData.h"
#include "RfxSimCarrRstData.h"
#include "RmcSimBaseHandler.h"
#include "RmcCommSimRequestHandler.h"
#include "RfxRsuRequestData.h"
#include "RfxRsuResponseData.h"
#include "RmcOpRsuSimDefs.h"
#include <compiler/compiler_utils.h>
#include <telephony/mtk_ril.h>
#include "rfx_properties.h"
#include "RfxChannel.h"
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <cstring>
#include <pthread.h>
#include "RfxMessageId.h"
#include <cutils/properties.h>
#include "RfxRilUtils.h"
#include "vsim/RmcVsimRequestHandler.h"

#ifdef __cplusplus
extern "C"
{
#endif
#include <hardware_legacy/mtk_power.h>
#include "base64.h"
#include "usim_fcp_parser.h"
#include <vendor/mediatek/proprietary/hardware/ril/platformlib/common/libmtkrilutils/proto/sap-api.pb.h>
#include "pb_decode.h"
#include "pb_encode.h"
#ifdef __cplusplus
}
#endif

using ::android::String8;
using namespace std;

// Subsidy lock feature only.
static int pinDefer[4] = {-1, -1, -1, -1};

static const int ch1ReqList[] = {
    RFX_MSG_REQUEST_ENTER_SIM_PIN,
    RFX_MSG_REQUEST_ENTER_SIM_PUK,
    RFX_MSG_REQUEST_ENTER_SIM_PIN2,
    RFX_MSG_REQUEST_ENTER_SIM_PUK2,
    RFX_MSG_REQUEST_CHANGE_SIM_PIN,
    RFX_MSG_REQUEST_CHANGE_SIM_PIN2,
    RFX_MSG_REQUEST_SIM_ENTER_NETWORK_DEPERSONALIZATION,
    RFX_MSG_REQUEST_SIM_ENTER_DEPERSONALIZATION,
    RFX_MSG_REQUEST_SIM_IO,
    RFX_MSG_REQUEST_ISIM_AUTHENTICATION,
    RFX_MSG_REQUEST_GENERAL_SIM_AUTH,
    RFX_MSG_REQUEST_SIM_OPEN_CHANNEL,
    RFX_MSG_REQUEST_SET_SIM_CARD_POWER,
    RFX_MSG_REQUEST_ENABLE_UICC_APPLICATIONS,
    RFX_MSG_REQUEST_ARE_UICC_APPLICATIONS_ENABLED,
    RFX_MSG_REQUEST_SIM_CLOSE_CHANNEL,
    RFX_MSG_REQUEST_SIM_TRANSMIT_APDU_BASIC,
    RFX_MSG_REQUEST_SIM_TRANSMIT_APDU_CHANNEL,
    RFX_MSG_REQUEST_SIM_GET_ATR,
    RFX_MSG_REQUEST_SIM_GET_ICCID,
    RFX_MSG_REQUEST_LOCAL_SIM_SAP_RESET,
    RFX_MSG_REQUEST_SIM_SAP_CONNECT,
    RFX_MSG_REQUEST_SIM_SAP_DISCONNECT,
    RFX_MSG_REQUEST_SIM_SAP_APDU,
    RFX_MSG_REQUEST_SIM_SAP_TRANSFER_ATR,
    RFX_MSG_REQUEST_SIM_SAP_POWER,
    RFX_MSG_REQUEST_SIM_SAP_RESET_SIM,
    RFX_MSG_REQUEST_SIM_SAP_SET_TRANSFER_PROTOCOL,
    RFX_MSG_REQUEST_SIM_SAP_ERROR_RESP,
    RFX_MSG_REQUEST_QUERY_FACILITY_LOCK,
    RFX_MSG_REQUEST_SET_FACILITY_LOCK,
    RFX_MSG_REQUEST_SIM_ENTER_DEVICE_NETWORK_DEPERSONALIZATION,
    RFX_MSG_REQUEST_SET_LOGICAL_TO_PHYSICAL_SLOT_MAPPING,
    RFX_MSG_REQUEST_SET_ALLOWED_CARRIERS,
    RFX_MSG_REQUEST_GET_ALLOWED_CARRIERS,
    RFX_MSG_REQUEST_ENTER_SIM_DEPERSONALIZATION,
    RFX_MSG_REQUEST_SML_RSU_REQUEST,
    RFX_MSG_REQUEST_CLIENT_RSU,
};

static const int ch3ReqList[] = {
    RFX_MSG_REQUEST_SIM_AUTHENTICATION
};

static const int ch1EventList[] = {
    RFX_MSG_EVENT_SIM_QUERY_ICCID,
    RFX_MSG_EVENT_SIM_DETECT_SIM,
    RFX_MSG_EVENT_SIM_SIM_AUTHENTICATION,
    RFX_MSG_EVENT_SIM_USIM_AUTHENTICATION,
    RFX_MSG_EVENT_GET_SLOT_STATUS,
    RFX_MSG_EVENT_SIM_RESET,
    RFX_MSG_EVENT_SIM_QUERY_EONS,
};

// Real-time
static const int ch7ReqList[] = {
    RFX_MSG_REQUEST_GET_SIM_STATUS,
    RFX_MSG_REQUEST_SET_SIM_POWER,
    RFX_MSG_REQUEST_GET_SLOT_STATUS,
    RFX_MSG_REQUEST_ACTIVATE_UICC_CARD,
    RFX_MSG_REQUEST_DEACTIVATE_UICC_CARD,
};

int RmcCommSimRequestHandler::mOldTestSimValue[MAX_SIM_COUNT] = {-1, -1, -1, -1};

RFX_REGISTER_DATA_TO_REQUEST_ID(RfxVoidData, RfxSimStatusData, RFX_MSG_REQUEST_GET_SIM_STATUS);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxSimIoData, RfxSimIoRspData, RFX_MSG_REQUEST_SIM_IO);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxStringData, RfxStringData, RFX_MSG_REQUEST_ISIM_AUTHENTICATION);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxSimAuthData, RfxSimIoRspData,
        RFX_MSG_REQUEST_SIM_AUTHENTICATION);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxSimGenAuthData, RfxSimIoRspData,
        RFX_MSG_REQUEST_GENERAL_SIM_AUTH);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxSimOpenChannelData, RfxIntsData,
        RFX_MSG_REQUEST_SIM_OPEN_CHANNEL);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxIntsData, RfxVoidData, RFX_MSG_REQUEST_SIM_CLOSE_CHANNEL);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxIntsData, RfxVoidData, RFX_MSG_REQUEST_SET_SIM_CARD_POWER);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxIntsData, RfxVoidData, RFX_MSG_REQUEST_ENABLE_UICC_APPLICATIONS);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxVoidData, RfxIntsData, RFX_MSG_REQUEST_ARE_UICC_APPLICATIONS_ENABLED);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxIntsData, RfxVoidData, RFX_MSG_REQUEST_SET_SIM_POWER);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxSimCarrRstData, RfxIntsData,
        RFX_MSG_REQUEST_SET_ALLOWED_CARRIERS);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxVoidData, RfxSimCarrRstData,
        RFX_MSG_REQUEST_GET_ALLOWED_CARRIERS);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxSimApduData, RfxSimIoRspData,
        RFX_MSG_REQUEST_SIM_TRANSMIT_APDU_BASIC);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxSimApduData, RfxSimIoRspData,
        RFX_MSG_REQUEST_SIM_TRANSMIT_APDU_CHANNEL);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxVoidData, RfxStringData, RFX_MSG_REQUEST_SIM_GET_ATR);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxVoidData, RfxStringData, RFX_MSG_REQUEST_SIM_GET_ICCID);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxStringsData, RfxIntsData, RFX_MSG_REQUEST_ENTER_SIM_PIN);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxStringsData, RfxIntsData, RFX_MSG_REQUEST_ENTER_SIM_PUK);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxStringsData, RfxIntsData, RFX_MSG_REQUEST_ENTER_SIM_PIN2);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxStringsData, RfxIntsData, RFX_MSG_REQUEST_ENTER_SIM_PUK2);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxStringsData, RfxIntsData, RFX_MSG_REQUEST_CHANGE_SIM_PIN);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxStringsData, RfxIntsData, RFX_MSG_REQUEST_CHANGE_SIM_PIN2);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxStringsData, RfxIntsData,
        RFX_MSG_REQUEST_SIM_ENTER_NETWORK_DEPERSONALIZATION);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxStringsData, RfxIntsData,
        RFX_MSG_REQUEST_SIM_ENTER_DEPERSONALIZATION);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxStringsData, RfxIntsData,
        RFX_MSG_REQUEST_ENTER_SIM_DEPERSONALIZATION);
RFX_REGISTER_DATA_TO_URC_ID(RfxVoidData, RFX_MSG_URC_RESPONSE_SIM_STATUS_CHANGED);
RFX_REGISTER_DATA_TO_URC_ID(RfxVoidData, RFX_MSG_URC_SIM_COMMON_SLOT_NO_CHANGED);
RFX_REGISTER_DATA_TO_URC_ID(RfxVoidData, RFX_MSG_URC_TRAY_PLUG_IN);
RFX_REGISTER_DATA_TO_URC_ID(RfxVoidData, RFX_MSG_URC_SIM_PLUG_OUT);
RFX_REGISTER_DATA_TO_URC_ID(RfxVoidData, RFX_MSG_URC_SIM_PLUG_IN);
RFX_REGISTER_DATA_TO_URC_ID(RfxVoidData, RFX_MSG_URC_SIM_IMSI_REFRESH_DONE);
RFX_REGISTER_DATA_TO_URC_ID(RfxIntsData, RFX_MSG_URC_SIM_SLOT_LOCK_POLICY_NOTIFY);
RFX_REGISTER_DATA_TO_URC_ID(RfxIntsData, RFX_MSG_URC_SIM_POWER_CHANGED);
RFX_REGISTER_DATA_TO_URC_ID(RfxVoidData, RFX_MSG_URC_CARD_DETECTED_IND);
RFX_REGISTER_DATA_TO_URC_ID(RfxStringsData, RFX_MSG_UNSOL_SML_RSU_EVENT);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxRawData, RfxRawData, \
        RFX_MSG_REQUEST_SIM_SAP_CONNECT);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxRawData, RfxRawData, \
        RFX_MSG_REQUEST_SIM_SAP_DISCONNECT);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxRawData, RfxRawData, \
        RFX_MSG_REQUEST_SIM_SAP_APDU);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxRawData, RfxRawData, \
        RFX_MSG_REQUEST_SIM_SAP_TRANSFER_ATR);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxRawData, RfxRawData, \
        RFX_MSG_REQUEST_SIM_SAP_POWER);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxRawData, RfxRawData, \
        RFX_MSG_REQUEST_SIM_SAP_RESET_SIM);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxRawData, RfxRawData, \
        RFX_MSG_REQUEST_SIM_SAP_SET_TRANSFER_PROTOCOL);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxVoidData, RfxRawData, \
        RFX_MSG_REQUEST_SIM_SAP_ERROR_RESP);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxStringsData, RfxIntsData,
        RFX_MSG_REQUEST_SIM_ENTER_DEVICE_NETWORK_DEPERSONALIZATION);

RFX_REGISTER_DATA_TO_EVENT_ID(RfxVoidData, RFX_MSG_EVENT_SIM_QUERY_ICCID);
RFX_REGISTER_DATA_TO_EVENT_ID(RfxStringData, RFX_MSG_EVENT_SIM_DETECT_SIM);
RFX_REGISTER_DATA_TO_EVENT_ID(RfxStringData, RFX_MSG_EVENT_SIM_SIM_AUTHENTICATION);
RFX_REGISTER_DATA_TO_EVENT_ID(RfxStringsData, RFX_MSG_EVENT_SIM_USIM_AUTHENTICATION);
RFX_REGISTER_DATA_TO_EVENT_ID(RfxStringData, RFX_MSG_EVENT_GET_SLOT_STATUS);
RFX_REGISTER_DATA_TO_EVENT_ID(RfxVoidData, RFX_MSG_EVENT_SIM_RESET);

RFX_REGISTER_DATA_TO_REQUEST_ID(RfxVoidData, RfxIntsData, \
        RFX_MSG_REQUEST_ACTIVATE_UICC_CARD);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxVoidData, RfxIntsData, \
        RFX_MSG_REQUEST_DEACTIVATE_UICC_CARD);

RFX_REGISTER_DATA_TO_URC_ID(RfxStringData, RFX_MSG_URC_ICCID_CHANGED);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxRsuRequestData, RfxRsuResponseData,
        RFX_MSG_REQUEST_SML_RSU_REQUEST);

RFX_REGISTER_DATA_TO_REQUEST_ID(RfxStringData, RfxRsuResponseData,
        RFX_MSG_REQUEST_CLIENT_RSU);
RFX_REGISTER_DATA_TO_EVENT_ID(RfxVoidData, RFX_MSG_EVENT_SIM_QUERY_EONS);
/*****************************************************************************
 * Class RfxController
 *****************************************************************************/
RmcCommSimRequestHandler::RmcCommSimRequestHandler(int slot_id, int channel_id) :
        RmcSimBaseHandler(slot_id, channel_id) {
    setTag(String8("RmcCommSimReq"));

    if (channel_id == RIL_CMD_PROXY_1) {
        // Check if SIM on/off feature is supported by modem.
        querySimOnOffActivation();
        // Query whether the SIM card supports "AT+ECGLA"
        queryEcglaCapability();
    }
}

RmcCommSimRequestHandler::~RmcCommSimRequestHandler() {
    pthread_mutex_unlock(&simStatusMutex);
    pthread_mutex_destroy(&simStatusMutex);
}

RmcSimBaseHandler::SIM_HANDLE_RESULT RmcCommSimRequestHandler::needHandle(
        const sp<RfxMclMessage>& msg) {
    int request = msg->getId();
    switch(request) {
        case RFX_MSG_REQUEST_GET_SIM_STATUS:
        case RFX_MSG_REQUEST_SIM_IO:
        case RFX_MSG_REQUEST_ISIM_AUTHENTICATION:
        case RFX_MSG_REQUEST_SIM_AUTHENTICATION:
        case RFX_MSG_REQUEST_GENERAL_SIM_AUTH:
        case RFX_MSG_EVENT_SIM_QUERY_ICCID:
        case RFX_MSG_REQUEST_SIM_OPEN_CHANNEL:
        case RFX_MSG_REQUEST_SIM_CLOSE_CHANNEL:
        case RFX_MSG_REQUEST_SIM_TRANSMIT_APDU_BASIC:
        case RFX_MSG_REQUEST_SIM_TRANSMIT_APDU_CHANNEL:
        case RFX_MSG_REQUEST_SIM_GET_ATR:
        case RFX_MSG_REQUEST_SIM_GET_ICCID:
        case RFX_MSG_REQUEST_ENTER_SIM_PIN:
        case RFX_MSG_REQUEST_ENTER_SIM_PUK:
        case RFX_MSG_REQUEST_ENTER_SIM_PIN2:
        case RFX_MSG_REQUEST_ENTER_SIM_PUK2:
        case RFX_MSG_REQUEST_CHANGE_SIM_PIN:
        case RFX_MSG_REQUEST_CHANGE_SIM_PIN2:
        case RFX_MSG_REQUEST_SIM_ENTER_NETWORK_DEPERSONALIZATION:
        case RFX_MSG_REQUEST_SIM_ENTER_DEPERSONALIZATION:
        case RFX_MSG_EVENT_SIM_DETECT_SIM:
        case RFX_MSG_EVENT_SIM_SIM_AUTHENTICATION:
        case RFX_MSG_EVENT_SIM_USIM_AUTHENTICATION:
        case RFX_MSG_REQUEST_SIM_SAP_CONNECT:
        case RFX_MSG_REQUEST_SIM_SAP_DISCONNECT:
        case RFX_MSG_REQUEST_SIM_SAP_APDU:
        case RFX_MSG_REQUEST_SIM_SAP_TRANSFER_ATR:
        case RFX_MSG_REQUEST_SIM_SAP_POWER:
        case RFX_MSG_REQUEST_SIM_SAP_RESET_SIM:
        case RFX_MSG_REQUEST_SIM_SAP_SET_TRANSFER_PROTOCOL:
        case RFX_MSG_REQUEST_SET_SIM_CARD_POWER:
        case RFX_MSG_REQUEST_ENABLE_UICC_APPLICATIONS:
        case RFX_MSG_REQUEST_ARE_UICC_APPLICATIONS_ENABLED:
        case RFX_MSG_REQUEST_SET_SIM_POWER:
        case RFX_MSG_REQUEST_SIM_ENTER_DEVICE_NETWORK_DEPERSONALIZATION:
        case RFX_MSG_REQUEST_GET_SLOT_STATUS:
        case RFX_MSG_EVENT_GET_SLOT_STATUS:
        case RFX_MSG_REQUEST_SET_LOGICAL_TO_PHYSICAL_SLOT_MAPPING:
        case RFX_MSG_REQUEST_SET_ALLOWED_CARRIERS:
        case RFX_MSG_REQUEST_GET_ALLOWED_CARRIERS:
        case RFX_MSG_REQUEST_ACTIVATE_UICC_CARD:
        case RFX_MSG_REQUEST_DEACTIVATE_UICC_CARD:
        case RFX_MSG_REQUEST_ENTER_SIM_DEPERSONALIZATION:
        case RFX_MSG_REQUEST_SML_RSU_REQUEST:
        case RFX_MSG_EVENT_SIM_RESET:
        case RFX_MSG_REQUEST_CLIENT_RSU:
        case RFX_MSG_EVENT_SIM_QUERY_EONS:
            return RmcSimBaseHandler::RESULT_NEED;
        case RFX_MSG_REQUEST_QUERY_FACILITY_LOCK:
        case RFX_MSG_REQUEST_SET_FACILITY_LOCK:
            {
                sp<RfxMclMessage> response;
                char** pStrings = (char**)(msg->getData()->getData());
                char *facility = pStrings[0];

                if (facility == NULL || strlen(facility) <= 0) {
                    logE(mTag, "needHandle => QUERY_FACILITY_LOCK, facility empty");
                        response = RfxMclMessage::obtainResponse(msg->getId(),
                                RIL_E_INVALID_ARGUMENTS, RfxIntsData(), msg, false);
                        responseToTelCore(response);
                    return RmcSimBaseHandler::RESULT_NEED;
                }
            }
            break;
        default:
            logD(mTag, "Not support the request %d!", request);
            break;
    }
    return RmcSimBaseHandler::RESULT_IGNORE;
}

void RmcCommSimRequestHandler::handleRequest(const sp<RfxMclMessage>& msg) {
    int request = msg->getId();
    switch(request) {
        case RFX_MSG_REQUEST_GET_SIM_STATUS:
            handleGetSimStatus(msg);
            break;
        case RFX_MSG_REQUEST_SIM_IO:
            handleSimIo(msg);
            break;
        case RFX_MSG_REQUEST_ISIM_AUTHENTICATION:
            handleIsimAuthentication(msg);
            break;
        case RFX_MSG_REQUEST_SIM_AUTHENTICATION:
            handleSimAuthentication(msg);
            break;
        case RFX_MSG_REQUEST_GENERAL_SIM_AUTH:
            handleGeneralSimAuthentication(msg);
            break;
        case RFX_MSG_REQUEST_SIM_OPEN_CHANNEL:
            handleSimOpenChannel(msg);
            break;
        case RFX_MSG_REQUEST_ENTER_SIM_PIN:
            handleSecurityOperation(msg,ENTER_PIN1);
            break;
        case RFX_MSG_REQUEST_ENTER_SIM_PUK:
            handleSecurityOperation(msg,ENTER_PUK1);
            break;
        case RFX_MSG_REQUEST_ENTER_SIM_PIN2:
            handleSecurityOperation(msg,ENTER_PIN2);
            break;
        case RFX_MSG_REQUEST_ENTER_SIM_PUK2:
            handleSecurityOperation(msg,ENTER_PUK2);
            break;
        case RFX_MSG_REQUEST_CHANGE_SIM_PIN:
            handleSecurityOperation(msg,CHANGE_PIN1);
            break;
        case RFX_MSG_REQUEST_CHANGE_SIM_PIN2:
            handleSecurityOperation(msg,CHANGE_PIN2);
            break;
        case RFX_MSG_REQUEST_SIM_ENTER_NETWORK_DEPERSONALIZATION:
            handleEnterNetworkDepersonalization(msg);
            break;
        case RFX_MSG_REQUEST_SIM_ENTER_DEPERSONALIZATION:
            handleEnterDepersonalization(msg);
            break;
        case RFX_MSG_REQUEST_SIM_CLOSE_CHANNEL:
            handleSimCloseChannel(msg);
            break;
        case RFX_MSG_REQUEST_SIM_TRANSMIT_APDU_BASIC:
            handleSimTransmitBasic(msg);
            break;
        case RFX_MSG_REQUEST_SIM_TRANSMIT_APDU_CHANNEL:
            handleSimTransmitChannel(msg);
            break;
        case RFX_MSG_REQUEST_SIM_GET_ATR:
            handleSimGetAtr(msg);
            break;
        case RFX_MSG_REQUEST_SIM_GET_ICCID:
            handleSimGetIccid(msg);
            break;
        case RFX_MSG_REQUEST_LOCAL_SIM_SAP_RESET:
            handleLocalBtSapReset(msg);
            break;
        case RFX_MSG_REQUEST_SIM_SAP_CONNECT:
            handleBtSapConnect(msg);
            break;
        case RFX_MSG_REQUEST_SIM_SAP_DISCONNECT:
            handleBtSapDisconnect(msg);
            break;
        case RFX_MSG_REQUEST_SIM_SAP_APDU:
            handleBtSapTransferApdu(msg);
            break;
        case RFX_MSG_REQUEST_SIM_SAP_TRANSFER_ATR:
            handleBtSapTransferAtr(msg);
            break;
        case RFX_MSG_REQUEST_SIM_SAP_POWER:
            handleBtSapPower(msg);
            break;
        case RFX_MSG_REQUEST_SIM_SAP_RESET_SIM:
            handleBtSapResetSim(msg);
            break;
        case RFX_MSG_REQUEST_SIM_SAP_SET_TRANSFER_PROTOCOL:
            handleBtSapSetTransferProtocol(msg);
            break;
        case RFX_MSG_REQUEST_SET_SIM_CARD_POWER:
            handleSetSimCardPower(msg);
            break;
        case RFX_MSG_REQUEST_ENABLE_UICC_APPLICATIONS:
            handleEnableUiccApplications(msg);
            break;
        case RFX_MSG_REQUEST_ARE_UICC_APPLICATIONS_ENABLED:
            handleAreUiccApplicationsEnabled(msg);
            break;
        case RFX_MSG_REQUEST_SET_SIM_POWER:
            handleSetSimPower(msg);
            break;
        case RFX_MSG_REQUEST_SIM_ENTER_DEVICE_NETWORK_DEPERSONALIZATION:
            handleEnterDeviceNetworkDepersonalization(msg);
            break;
        case RFX_MSG_REQUEST_GET_SLOT_STATUS:
            handleGetSlotStatus(msg);
            break;
        case RFX_MSG_REQUEST_SET_LOGICAL_TO_PHYSICAL_SLOT_MAPPING:
            handleSetSimSlotsMapping(msg);
            break;
        case RFX_MSG_REQUEST_SET_ALLOWED_CARRIERS:
            handleSetAllowedCarriers(msg);
            break;
        case RFX_MSG_REQUEST_GET_ALLOWED_CARRIERS:
            handleGetAllowedCarriers(msg);
            break;
        case RFX_MSG_REQUEST_ACTIVATE_UICC_CARD:
            handleActiveUiccCard(msg);
            break;
        case RFX_MSG_REQUEST_DEACTIVATE_UICC_CARD:
            handleDeactivateUiccCard(msg);
            break;
        case RFX_MSG_REQUEST_ENTER_SIM_DEPERSONALIZATION:
            handleEnterSimDepersonalization(msg);
            break;
        case RFX_MSG_REQUEST_SML_RSU_REQUEST:
            handleRsuRequest(msg);
            break;
        case RFX_MSG_REQUEST_CLIENT_RSU:
            handleRsuClientRequest(msg);
            break;
        default:
            logD(mTag, "Not support the request %d!", request);
            break;
    }
}

void RmcCommSimRequestHandler::handleEvent(const sp<RfxMclMessage>& msg) {
    int event = msg->getId();
    switch(event) {
        case RFX_MSG_EVENT_SIM_QUERY_ICCID:
            handleQueryIccid(msg);
            break;
        case RFX_MSG_EVENT_SIM_DETECT_SIM:
            handleDetectSim(msg);
            break;
        case RFX_MSG_EVENT_SIM_SIM_AUTHENTICATION:
            handleLocalRequestSimAuthentication(msg);
            break;
        case RFX_MSG_EVENT_SIM_USIM_AUTHENTICATION:
            handleLocalRequestUsimAuthentication(msg);
            break;
        case RFX_MSG_EVENT_GET_SLOT_STATUS:
            handleEventGetSlotStatus(msg);
            break;
        case RFX_MSG_EVENT_SIM_RESET:
            handleEventResetSim(msg);
            break;
        case RFX_MSG_EVENT_SIM_QUERY_EONS:
            handleQueryEons(msg);
            break;
        default:
            logD(mTag, "Not support the event %d!", event);
            break;
    }
}

const int* RmcCommSimRequestHandler::queryTable(int channel_id, int *record_num) {

    if (channel_id == RIL_CMD_PROXY_1) {
        *record_num = sizeof(ch1ReqList)/sizeof(int);
        return ch1ReqList;
    } else if (channel_id == RIL_CMD_PROXY_3) {
        *record_num = sizeof(ch3ReqList)/sizeof(int);
        return ch3ReqList;
    } else if (channel_id == RIL_CMD_PROXY_7) {
        *record_num = sizeof(ch7ReqList)/sizeof(int);
        return ch7ReqList;
    } else {
        // No request registered!
    }

    return NULL;
}

const int* RmcCommSimRequestHandler::queryEventTable(int channel_id, int *record_num) {
    if (channel_id == RIL_CMD_PROXY_1) {
        *record_num = sizeof(ch1EventList)/sizeof(int);
        return ch1EventList;
    }

    return NULL;
}

void RmcCommSimRequestHandler::sleepMsec(long long msec) {
    struct timespec ts;
    int err;

    ts.tv_sec = (msec / 1000);
    ts.tv_nsec = (msec % 1000) * 1000 * 1000;

    do {
        err = nanosleep(&ts, &ts);
    } while (err < 0 && errno == EINTR);
}

bool RmcCommSimRequestHandler::getSimAppInfo(int app_id, RIL_AppStatus *p_app_info,
        UICC_Status uStatus) {
    bool result = false;
    int err, intPara = -1;
    char *strPara = NULL;
    RfxAtLine *line = NULL;
    sp<RfxAtResponse> p_response = NULL;
    RmcSimPinPukCount *retry = NULL;

    if (p_app_info != NULL) {
        memset(p_app_info, 0, sizeof(RIL_AppStatus));
    } else {
        return result;
    }

    // Query SIM app info
    String8 cmd = String8::format("AT+ESIMAPP=%d,0", app_id);
    p_response = atSendCommandSingleline(cmd.string(), "+ESIMAPP:");
    p_app_info->aid_ptr = NULL;

    if (p_response != NULL && p_response->getSuccess() > 0) {
        // Success
        line = p_response->getIntermediates();

        line->atTokStart(&err);

        // application id
        intPara = line->atTokNextint(&err);

        // channel id
        intPara = line->atTokNextint(&err);

        // AID
        strPara = line->atTokNextstr(&err);
        asprintf(&p_app_info->aid_ptr, "%s", strPara);

        // App label
        strPara = NULL;
        strPara = line->atTokNextstr(&err);
        asprintf(&p_app_info->app_label_ptr, "%s", strPara);

        // Pin1 enable
        intPara = -1;
        intPara = line->atTokNextint(&err);
        if (intPara == 0) {
            p_app_info->pin1 = RIL_PINSTATE_DISABLED;
        }

        // Pin2 enable
        intPara = -1;
        intPara = line->atTokNextint(&err);
        if (intPara == 0) {
            p_app_info->pin2 = RIL_PINSTATE_DISABLED;
        }

        retry = (RmcSimPinPukCount*)calloc(1, sizeof(RmcSimPinPukCount));
        RFX_ASSERT(retry != NULL);

        // PIN1 retry count
        retry->pin1 = line->atTokNextint(&err);
        // PIN2 retry count
        retry->pin2 = line->atTokNextint(&err);
        // PUK1 retry count
        retry->puk1 = line->atTokNextint(&err);
        // PUK2 retry count
        retry->puk2 = line->atTokNextint(&err);
        // Update the system properties of PIN and PUK
        // setPinPukRetryCountProp(retry);

        // Perso state and correct pin1/pin2 enable state
        switch (uStatus) {
            case UICC_READY:
                p_app_info->app_state = RIL_APPSTATE_READY;
                p_app_info->perso_substate = RIL_PERSOSUBSTATE_READY;
                if (p_app_info->pin1 != RIL_PINSTATE_DISABLED) {
                    p_app_info->pin1 = RIL_PINSTATE_ENABLED_VERIFIED;
                }
                if (p_app_info->pin2 != RIL_PINSTATE_DISABLED) {
                    if (retry->pin2 == 0 && retry->puk2 > 0) {
                        p_app_info->pin2 = RIL_PINSTATE_ENABLED_BLOCKED;
                    } else if (retry->puk2 == 0) {
                        p_app_info->pin2 = RIL_PINSTATE_ENABLED_PERM_BLOCKED;
                    } else {
                        p_app_info->pin2 = RIL_PINSTATE_ENABLED_NOT_VERIFIED;
                    }
                }
                break;
            case UICC_PIN:
                p_app_info->app_state = RIL_APPSTATE_PIN;
                p_app_info->perso_substate = RIL_PERSOSUBSTATE_READY;
                p_app_info->pin1 = RIL_PINSTATE_ENABLED_NOT_VERIFIED;
                break;
            case UICC_PUK:
                p_app_info->app_state = RIL_APPSTATE_PUK;
                p_app_info->perso_substate = RIL_PERSOSUBSTATE_READY;
                p_app_info->pin1 = RIL_PINSTATE_ENABLED_BLOCKED;
                break;
            case UICC_NETWORK_PERSONALIZATION:
                p_app_info->app_state = RIL_APPSTATE_SUBSCRIPTION_PERSO;
                p_app_info->perso_substate = RIL_PERSOSUBSTATE_SIM_NETWORK;
                break;
            case UICC_NP:
                p_app_info->app_state = RIL_APPSTATE_SUBSCRIPTION_PERSO;
                p_app_info->perso_substate = RIL_PERSOSUBSTATE_SIM_NETWORK;
                break;
            case UICC_NSP:
                p_app_info->app_state = RIL_APPSTATE_SUBSCRIPTION_PERSO;
                p_app_info->perso_substate = RIL_PERSOSUBSTATE_SIM_NETWORK_SUBSET;
                break;
            case UICC_SP:
                p_app_info->app_state = RIL_APPSTATE_SUBSCRIPTION_PERSO;
                p_app_info->perso_substate = RIL_PERSOSUBSTATE_SIM_SERVICE_PROVIDER;
                break;
            case UICC_CP:
                p_app_info->app_state = RIL_APPSTATE_SUBSCRIPTION_PERSO;
                p_app_info->perso_substate = RIL_PERSOSUBSTATE_SIM_CORPORATE;
                break;
            case UICC_SIMP:
                p_app_info->app_state = RIL_APPSTATE_SUBSCRIPTION_PERSO;
                p_app_info->perso_substate = RIL_PERSOSUBSTATE_SIM_SIM;
                break;
            case UICC_NP_PUK:
                p_app_info->app_state = RIL_APPSTATE_SUBSCRIPTION_PERSO;
                p_app_info->perso_substate = RIL_PERSOSUBSTATE_SIM_NETWORK_PUK;
                break;
            case UICC_NSP_PUK:
                p_app_info->app_state = RIL_APPSTATE_SUBSCRIPTION_PERSO;
                p_app_info->perso_substate = RIL_PERSOSUBSTATE_SIM_NETWORK_SUBSET_PUK;
                break;
            case UICC_SP_PUK:
                p_app_info->app_state = RIL_APPSTATE_SUBSCRIPTION_PERSO;
                p_app_info->perso_substate = RIL_PERSOSUBSTATE_SIM_SERVICE_PROVIDER_PUK;
                break;
            case UICC_CP_PUK:
                p_app_info->app_state = RIL_APPSTATE_SUBSCRIPTION_PERSO;
                p_app_info->perso_substate = RIL_PERSOSUBSTATE_SIM_CORPORATE_PUK;
                break;
            case UICC_SIMP_PUK:
                p_app_info->app_state = RIL_APPSTATE_SUBSCRIPTION_PERSO;
                p_app_info->perso_substate = RIL_PERSOSUBSTATE_SIM_SIM_PUK;
                break;
            case UICC_NS_SP:
                p_app_info->app_state = RIL_APPSTATE_SUBSCRIPTION_PERSO;
                p_app_info->perso_substate = RIL_PERSOSUBSTATE_SIM_NS_SP;
                break;
            case UICC_NS_SP_PUK:
                p_app_info->app_state = RIL_APPSTATE_SUBSCRIPTION_PERSO;
                p_app_info->perso_substate = RIL_PERSOSUBSTATE_SIM_NS_SP_PUK;
                break;
            case UICC_SIM_C:
                p_app_info->app_state = RIL_APPSTATE_SUBSCRIPTION_PERSO;
                p_app_info->perso_substate = RIL_PERSOSUBSTATE_SIM_SIM_C;
                break;
            case UICC_SIM_C_PUK:
                p_app_info->app_state = RIL_APPSTATE_SUBSCRIPTION_PERSO;
                p_app_info->perso_substate = RIL_PERSOSUBSTATE_SIM_SIM_C_PUK;
                break;
            case UICC_PERM_BLOCKED:
                p_app_info->app_state = RIL_APPSTATE_PUK;
                p_app_info->perso_substate = RIL_PERSOSUBSTATE_UNKNOWN;
                p_app_info->pin1 = RIL_PINSTATE_ENABLED_PERM_BLOCKED;
                p_app_info->pin2 = RIL_PINSTATE_UNKNOWN;
                break;
            default:
                p_app_info->perso_substate = RIL_PERSOSUBSTATE_READY;
                break;
        }

        // App type
        switch (app_id) {
            case UICC_APP_SIM:
                p_app_info->app_type = RIL_APPTYPE_SIM;
                break;
            case UICC_APP_USIM:
                p_app_info->app_type = RIL_APPTYPE_USIM;
                break;
            case UICC_APP_CSIM:
                p_app_info->app_type = RIL_APPTYPE_CSIM;
                break;
            case UICC_APP_RUIM:
                p_app_info->app_type = RIL_APPTYPE_RUIM;
                break;
            case UICC_APP_ISIM:
                p_app_info->app_type = RIL_APPTYPE_ISIM;
                break;
        }
        String8 logStr;
        logStr = String8::format("app_id %d, app_type %d, app_state %d, AID %s, label %s, ",
                app_id, p_app_info->app_type, p_app_info->app_state, p_app_info->aid_ptr,
                p_app_info->app_label_ptr);
        logStr += String8::format("pin1 %d, pin2 %d, (%d, %d, %d, %d)", p_app_info->pin1,
                p_app_info->pin2, retry->pin1, retry->pin2, retry->puk1, retry->puk2);
        logD(mTag, logStr.string());
        result = true;
        free(retry);
    } else {
        logE(mTag, "Fail to get app info!");
    }

    p_response = NULL;

    // Set aid for CDMA dual activation.
    if (app_id == UICC_APP_RUIM) {
        if (p_app_info->aid_ptr != NULL) {
            free(p_app_info->aid_ptr);
        }
        asprintf(&p_app_info->aid_ptr, "%s", "A000000000RUIM");
    } else {
        // Keep as default.
    }

    return result;
}

void RmcCommSimRequestHandler::handleGetSimStatus(const sp<RfxMclMessage>& msg) {

    RIL_Errno ril_error = RIL_E_SIM_ERR;
    RIL_CardStatus_v8 *p_card_status = NULL;
    int cardType = getMclStatusManager()->getIntValue(RFX_STATUS_KEY_CARD_TYPE);
    int cdma3GNT = getMclStatusManager()->getIntValue(RFX_STATUS_KEY_CDMA3G_SWITCH_CARD);
    // MTK-START: AOSP SIM PLUG IN/OUT
    int esim_cause = getMclStatusManager()->getIntValue(RFX_STATUS_KEY_SIM_ESIMS_CAUSE);
    // MTK-END
    sp<RfxMclMessage> response;
    char tempstr[RFX_PROPERTY_VALUE_MAX] = { 0 };
    String8 prop("vendor.ril.iccid.sim");
    int ret = 0;
    bool cdma3GDM = getMclStatusManager()->getBoolValue(RFX_STATUS_KEY_CDMA3G_DUALMODE_CARD);
    bool aospEnabled = isEnableUiccApplicationsSupported();

    memset(tempstr, 0, sizeof(tempstr));
    prop.append(String8::format("%d", (m_slot_id+1)));
    //check timestampe between the request msg and the capability switch begin
    int64_t tSimSwitch = getNonSlotMclStatusManager()->getInt64Value(
            RFX_STATUS_KEY_SIM_SWITCH_RADIO_UNAVAIL_TIME);
    if (msg->getTimeStamp() <= tSimSwitch) {
        //check timestampe between the request msg and the capability switch begin
        ril_error = RIL_E_INVALID_STATE;
    } else if (cdma3GDM && (((cardType == RFX_CARD_TYPE_SIM) &&
            ((cdma3GNT == AP_TRIGGER_SWITCH_RUIM) || (cdma3GNT == GMSS_TRIGGER_SWITCH_RUIM))) ||
            ((cardType == RFX_CARD_TYPE_RUIM) &&
            ((cdma3GNT == AP_TRIGGER_SWITCH_SIM) || (cdma3GNT == GMSS_TRIGGER_SWITCH_SIM))))) {
        // check CDMA3G consistency between next card type and current card type
        ril_error = RIL_E_INVALID_STATE;
    } else if (cardType == -1) {
        // The UICC card is not ready.
        ril_error = RIL_E_SIM_ERR;
    } else if ((!aospEnabled && (getMclStatusManager()->getIntValue(RFX_STATUS_KEY_SIM_ONOFF_STATE)
            == SIM_POWER_STATE_SIM_OFF)) || (aospEnabled && (getMclStatusManager()->getIntValue(
            RFX_STATUS_KEY_AOSP_UICC_APPLICATIONS_ENABLE_STATE)
            != UICC_APPLICATIONS_ENABLE_STATE_ENABLED && getMclStatusManager()->getIntValue(
            RFX_STATUS_KEY_AOSP_UICC_APPLICATIONS_ENABLE_STATE)
            != UICC_APPLICATIONS_ENABLE_STATE_UNKNOWN))
            || (getMclStatusManager()->getIntValue(RFX_STATUS_KEY_SIM_POWER_STATE) == SIM_POWER_STATE_V16_SIM_OFF)
            || (getMclStatusManager()->getIntValue(RFX_STATUS_KEY_SIM_POWER_STATE) == SIM_POWER_STATE_PASS_THROUGH)) {
        p_card_status = (RIL_CardStatus_v8*)calloc(1, sizeof(RIL_CardStatus_v8));
        RFX_ASSERT(p_card_status != NULL);
        p_card_status->atr = (char *)calloc(1, RFX_PROPERTY_VALUE_MAX);
        RFX_ASSERT(p_card_status->atr != NULL);
        p_card_status->iccId = (char *)calloc(1, RFX_PROPERTY_VALUE_MAX);
        RFX_ASSERT(p_card_status->iccId != NULL);
        p_card_status->eid = (char *)calloc(1, RFX_PROPERTY_VALUE_MAX);
        RFX_ASSERT(p_card_status->eid != NULL);

        if (!getIccId(p_card_status->iccId)) {
            ril_error = RIL_E_SIM_ERR;
        } else {
            // The UICC card is SIM off state.
            p_card_status->card_state = RIL_CARDSTATE_PRESENT;
            p_card_status->universal_pin_state = RIL_PINSTATE_UNKNOWN;
            p_card_status->gsm_umts_subscription_app_index = -1;
            p_card_status->cdma_subscription_app_index = -1;
            p_card_status->ims_subscription_app_index = -1;
            p_card_status->num_applications = 0;
            ril_error = RIL_E_SUCCESS;
        }

        getMclStatusManager()->setIntValue(RFX_STATUS_KEY_SIM_STATE, RFX_SIM_STATE_NOT_READY);
    } else {
        bool result = false;
        int err, count = 0;
        RfxAtLine *line = NULL;
        char *cpinResult = NULL;
        sp<RfxAtResponse> p_response = NULL;

        // Get SIM status
        do {
            p_response = atSendCommandSingleline("AT+CPIN?", "+CPIN:");
            err = p_response->getError();

            if (err != 0) {
                //if (err == AT_ERROR_INVALID_THREAD) {
                //    ret = UICC_BUSY;
                //} else {
                    ret = UICC_NOT_READY;
                //}
            } else if (p_response->getSuccess() == 0) {
                switch (p_response->atGetCmeError()) {
                    case CME_SIM_BUSY:
                        ret = UICC_BUSY;
                        break;
                    case CME_SIM_NOT_INSERTED:
                        // MTK-START: AOSP SIM PLUG IN/OUT
                        if (ESIMS_CAUSE_SIM_NO_INIT == esim_cause) {
                            ret = UICC_NO_INIT;
                        } else {
                            ret = UICC_ABSENT;
                        }
                        // MTK-END
                        break;
                    case CME_SIM_FAILURE:
                        ret = UICC_ABSENT;
                        break;
                    case CME_SIM_WRONG: {
                        RmcSimPinPukCount *retry = getPinPukRetryCount();
                        if (retry != NULL && retry->pin1 == 0 && retry->puk1 == 0)
                        {
                            ret = UICC_PERM_BLOCKED; // PERM_DISABLED
                        } else {
                            ret = UICC_NOT_READY;
                        }
                        if (retry != NULL) {
                            free(retry);
                        }
                        break;
                    }
                    default:
                        ret = UICC_NOT_READY;
                        break;
                }
            } else {
                // Success
                int state = RFX_SIM_STATE_NOT_READY;

                line = p_response->getIntermediates();
                line->atTokStart(&err);
                if (err < 0) {
                    ret = UICC_NOT_READY;
                    break;
                }

                cpinResult = line->atTokNextstr(&err);
                if (err < 0) {
                    ret = UICC_NOT_READY;
                    break;
                }
                if (ret != UICC_NOT_READY) {
                    String8 cpinStr(cpinResult);
                    if (cpinStr == String8::format("SIM PIN")) {
                        ret = UICC_PIN;
                        state = RFX_SIM_STATE_PIN_REQUIRED;
                    } else if (cpinStr == String8::format("SIM PUK")) {
                        ret = UICC_PUK;
                        state = RFX_SIM_STATE_PUK_REQUIRED;
                    } else if (cpinStr == String8::format("PH-NET PIN") ||
                            cpinStr == String8::format("PH-NET PUK")) {
                        if (cpinStr == String8::format("PH-NET PIN")) {
                            ret = UICC_NP;
                        } else {
                            ret = UICC_NP_PUK;
                        }
                        state = RFX_SIM_STATE_NETWORK_LOCKED;
                    } else if (cpinStr == String8::format("PH-NETSUB PIN") ||
                            cpinStr == String8::format("PH-NETSUB PUK")) {
                        if (cpinStr == String8::format("PH-NETSUB PIN")) {
                            ret = UICC_NSP;
                        } else {
                            ret = UICC_NSP_PUK;
                        }
                        state = RFX_SIM_STATE_NETWORK_LOCKED;
                    } else if (cpinStr == String8::format("PH-SP PIN") ||
                            cpinStr == String8::format("PH-SP PUK")) {
                        if (cpinStr == String8::format("PH-SP PIN")) {
                            ret = UICC_SP;
                        } else {
                            ret = UICC_SP_PUK;
                        }
                        state = RFX_SIM_STATE_NETWORK_LOCKED;
                    } else if (cpinStr == String8::format("PH-CORP PIN") ||
                            cpinStr == String8::format("PH-CORP PUK")) {
                        if (cpinStr == String8::format("PH-CORP PIN")) {
                            ret = UICC_CP;
                        } else {
                            ret = UICC_CP_PUK;
                        }
                        state = RFX_SIM_STATE_NETWORK_LOCKED;
                    } else if (cpinStr == String8::format("PH-FSIM PIN") ||
                            cpinStr == String8::format("PH-FSIM PUK")) {
                        if (cpinStr == String8::format("PH-FSIM PIN")) {
                            ret = UICC_SIMP;
                        } else {
                            ret = UICC_SIMP_PUK;
                        }
                        state = RFX_SIM_STATE_NETWORK_LOCKED;
                    } else if (cpinStr == String8::format("PH-NSSP PIN") ||
                            cpinStr == String8::format("PH-NSSP PUK")) {
                        if (cpinStr == String8::format("PH-NSSP PIN")) {
                            ret = UICC_NS_SP;
                        } else {
                            ret = UICC_NS_SP_PUK;
                        }
                        state = RFX_SIM_STATE_NETWORK_LOCKED;
                    } else if (cpinStr == String8::format("PH-SIMC PIN") ||
                            cpinStr == String8::format("PH-SIMC PUK")) {
                        if (cpinStr == String8::format("PH-SIMC PIN")) {
                            ret = UICC_SIM_C;
                        } else {
                            ret = UICC_SIM_C_PUK;
                        }
                        state = RFX_SIM_STATE_NETWORK_LOCKED;
                    } else if (isRjioRsuSupport() && cpinStr == String8::format("SIM PIN-DEFER")) {
                        /* Subsidy lock feature only */
                        ret = UICC_NOT_READY;
                        state = RFX_SIM_STATE_NOT_READY;
                        logD(mTag, "Sim not ready and mark as SIM PIN DEFER.");
                        pinDefer[m_slot_id] = 1;
                    } else if (cpinStr == String8::format("EMPTY_EUICC")) {
                        ret = UICC_EMPTY_EUICC;
                        state = RFX_SIM_STATE_NOT_READY;
                    } else if (cpinStr == String8::format("CARD_REBOOT")) {
                        ret = UICC_CARD_REBOOT;
                        state = RFX_SIM_STATE_NOT_READY;
                    } else if (cpinStr == String8::format("CARD_RESTRICTED")) {
                        if (getMclStatusManager()->getIntValue(RFX_STATUS_KEY_CARD_TYPE)
                                == RFX_CARD_TYPE_USIM) {
                            ret = UICC_USIM_RESTRICTED;
                        } else {
                            ret = UICC_SIM_RESTRICTED;
                        }
                        state = RFX_SIM_STATE_NETWORK_LOCKED;
                    } else if (cpinStr != String8::format("READY") ||
                            RfxRilUtils::isVsimEnabledNotInserted(m_slot_id))  {
                        /* we're treating unsupported lock types as "sim absent" */
                        ret = UICC_ABSENT;
                        state = RFX_SIM_STATE_ABSENT;
                    } else {
                        ret = UICC_READY;
                        state = RFX_SIM_STATE_READY;
                    }
                }

                getMclStatusManager()->setIntValue(RFX_STATUS_KEY_SIM_STATE, state);

                p_response = NULL;
            }

            if (ret == UICC_BUSY) {
                count++;     //to avoid block; if the busy time is too long; need to check modem.
                if ((count == MAX_RETRY_COUNT) || RfxRilUtils::isVsimEnabledBySlot(m_slot_id)) {
                    ret = UICC_NOT_READY;
                    getMclStatusManager()->setIntValue(
                            RFX_STATUS_KEY_ECPIN_STATE, RFX_WAIT_FOR_ECPIN);
                } else {
                    sleepMsec(200);
                }
            } else if (ret == UICC_READY) {
                String8 testSimProp("vendor.gsm.sim.ril.testsim");
                char testStr[RFX_PROPERTY_VALUE_MAX] = { 0 };
                testSimProp.append(
                        (m_slot_id == 0) ? "" : String8::format(".%d", (m_slot_id + 1)));
                rfx_property_get(testSimProp, testStr, "0");
                // add check for ALPS05243227, query test sim timing issue
                if (strcmp("0", testStr) == 0) {
                    // Query test SIM from modem
                    p_response = atSendCommandSingleline("AT+ETESTSIM?", "+ETESTSIM:");
                    err = p_response->getError();

                    if (err < 0 || p_response->getSuccess() == 0) {
                        logE(mTag, "detect test SIM failed");
                    } else {
                        int para;

                        line = p_response->getIntermediates();

                        line->atTokStart(&err);
                        para = line->atTokNextint(&err);

                        String8 testSimStr(String8::format("%d", para));
                        if (mOldTestSimValue[m_slot_id] != para) {
                            mOldTestSimValue[m_slot_id] = para;
                            rfx_property_set(testSimProp, testSimStr.string());
                        }
                    }
                }
                p_response = NULL;
                if (isRjioRsuSupport()) {
                    // Subsidy lock feature only.
                    for (int i = 0; i < RfxRilUtils::rfxGetSimCount(); i++) {
                        if (i != m_slot_id && pinDefer[i] == 1) {
                            // setSimStatusChanged(i);
                            sp<RfxMclMessage> unsol = RfxMclMessage::obtainUrc(RFX_MSG_URC_RESPONSE_SIM_STATUS_CHANGED,
                            i, RfxVoidData());
                            responseToTelCore(unsol);
                            logD(mTag, "UICC_READY Send SIM status changed due to SIM PIN DEFER");
                            pinDefer[i] = 0;
                        }
                    }
                }
            } else if (UICC_NP == ret || UICC_PIN == ret || UICC_PUK == ret) {
                if (isRjioRsuSupport()) {
                    // Subsidy lock feature only.
                    for (int i = 0; i < RfxRilUtils::rfxGetSimCount(); i++) {
                        if (i != m_slot_id && pinDefer[i] == 1) {
                            // setSimStatusChanged(i);
                            sp<RfxMclMessage> unsol = RfxMclMessage::obtainUrc(RFX_MSG_URC_RESPONSE_SIM_STATUS_CHANGED,
                                    i, RfxVoidData());
                            responseToTelCore(unsol);
                            logD(mTag, "UICC_NP ,PIN , PUK Send SIM status changed due to SIM PIN DEFER");
                            pinDefer[i] = 0;
                        }
                    }
                }
            }
        } while (ret == UICC_BUSY);

        p_card_status = (RIL_CardStatus_v8*)calloc(1, sizeof(RIL_CardStatus_v8));
        RFX_ASSERT(p_card_status != NULL);
        p_card_status->atr = (char *)calloc(1, RFX_PROPERTY_VALUE_MAX);
        RFX_ASSERT(p_card_status->atr != NULL);
        p_card_status->iccId = (char *)calloc(1, RFX_PROPERTY_VALUE_MAX);
        RFX_ASSERT(p_card_status->iccId != NULL);
        p_card_status->eid = (char *)calloc(1, RFX_PROPERTY_VALUE_MAX);
        RFX_ASSERT(p_card_status->eid != NULL);

        getEid(p_card_status->eid);

        if (ret == UICC_NOT_READY || !getIccId(p_card_status->iccId)) {
            // Card state error
            p_card_status->card_state = RIL_CARDSTATE_ERROR;
            p_card_status->universal_pin_state = RIL_PINSTATE_UNKNOWN;
            p_card_status->gsm_umts_subscription_app_index = -1;
            p_card_status->cdma_subscription_app_index = -1;
            p_card_status->ims_subscription_app_index = -1;
            p_card_status->num_applications = 0;
            if (getMclStatusManager()->getBoolValue(RFX_STATUS_KEY_IS_EUICC_CARD, false)) {
                getAtr(p_card_status->atr);
            }
            logE(mTag, "handleGetSimStatus ret = not ready or iccId not ready.");
        } else if (ret == UICC_ABSENT) {
            // UICC absent
            p_card_status->card_state = RIL_CARDSTATE_ABSENT;
            p_card_status->universal_pin_state = RIL_PINSTATE_UNKNOWN;
            p_card_status->gsm_umts_subscription_app_index = -1;
            p_card_status->cdma_subscription_app_index = -1;
            p_card_status->ims_subscription_app_index = -1;
            p_card_status->num_applications = 0;
            resetSimPropertyAndStatusKey();
            getMclStatusManager()->setIntValue(RFX_STATUS_KEY_SIM_STATE, RFX_SIM_STATE_ABSENT);
            rfx_property_get("persist.vendor.radio.c_capability_slot", tempstr, "0");
            if (((cardType & RFX_CARD_TYPE_RUIM) || (cardType & RFX_CARD_TYPE_CSIM)) &&
                    !(cardType & RFX_CARD_TYPE_USIM) && !(cardType & RFX_CARD_TYPE_SIM) &&
                    (m_slot_id != atoi(tempstr) - 1)) {
                // For RUIM single mode card, iccid is not set in rild. If C capability is not in
                // card for C+C mode, there is no chance to update iccid in rild. Here is to update
                // iccid to N/A in such situation.
                logI(mTag, "CDMA slot: %d, %s : N/A", atoi(tempstr) - 1, prop.string());
                //rfx_property_set(prop.string(), "N/A");
                getMclStatusManager()->setString8Value(RFX_STATUS_KEY_SIM_ICCID, String8("N/A"));
                sendIccidChanged("N/A");
            }
        } else if ((ret == UICC_NO_INIT) || (ret == UICC_CARD_REBOOT)
                || (ret == UICC_EMPTY_EUICC)) {
            p_card_status->card_state = RIL_CARDSTATE_PRESENT;
            p_card_status->universal_pin_state = RIL_PINSTATE_UNKNOWN;
            p_card_status->gsm_umts_subscription_app_index = -1;
            p_card_status->cdma_subscription_app_index = -1;
            p_card_status->ims_subscription_app_index = -1;
            p_card_status->num_applications = 0;
            if (ret == UICC_EMPTY_EUICC) {
                getAtr(p_card_status->atr);
            }
        } else {
            // Get ATR.
            getAtr(p_card_status->atr);

            if (ret == UICC_PERM_BLOCKED) {
                getMclStatusManager()->setIntValue(RFX_STATUS_KEY_SIM_STATE,
                        RFX_SIM_STATE_PERM_DISABLED);
            }
            // Normal case
            if (ret == UICC_USIM_RESTRICTED || ret == UICC_SIM_RESTRICTED) {
                p_card_status->card_state = RIL_CARDSTATE_RESTRICTED;
            } else {
                p_card_status->card_state = RIL_CARDSTATE_PRESENT;
            }
            p_card_status->universal_pin_state = RIL_PINSTATE_UNKNOWN;
            p_card_status->gsm_umts_subscription_app_index = -1;
            p_card_status->cdma_subscription_app_index = -1;
            p_card_status->ims_subscription_app_index = -1;
            p_card_status->num_applications = 0;

            if (cardType & RFX_CARD_TYPE_USIM) {
                // Query USIM app info
                result = getSimAppInfo(UICC_APP_USIM,
                        &p_card_status->applications[p_card_status->num_applications],
                        (UICC_Status)ret);
            } else if (cardType & RFX_CARD_TYPE_SIM) {
                // Query SIM app info
                result = getSimAppInfo(UICC_APP_SIM,
                        &p_card_status->applications[p_card_status->num_applications],
                        (UICC_Status)ret);
            }

            if (result) {
                p_card_status->gsm_umts_subscription_app_index = p_card_status->num_applications;
                p_card_status->num_applications++;
            }

            // Query ISIM app info
            result = false;
            if (cardType & RFX_CARD_TYPE_ISIM) {
                result = getSimAppInfo(UICC_APP_ISIM,
                        &p_card_status->applications[p_card_status->num_applications],
                        (UICC_Status)ret);
            }

            if (result) {
                p_card_status->ims_subscription_app_index = p_card_status->num_applications;
                p_card_status->num_applications++;
            }

            result = false;
            if (cardType & RFX_CARD_TYPE_CSIM) {
                // Query CSIM app info
                result = getSimAppInfo(UICC_APP_CSIM,
                        &p_card_status->applications[p_card_status->num_applications],
                        (UICC_Status)ret);
            } else if (cardType & RFX_CARD_TYPE_RUIM) {
                // Query RUIM app info
                result = getSimAppInfo(UICC_APP_RUIM,
                        &p_card_status->applications[p_card_status->num_applications],
                        (UICC_Status)ret);
            }

            if (result) {
                p_card_status->cdma_subscription_app_index = p_card_status->num_applications;
                p_card_status->num_applications++;
            }

            // Correct universal pin state
            p_card_status->universal_pin_state = p_card_status->applications[0].pin1;
        }

        if (!getIccId(p_card_status->iccId) || (ret == UICC_NOT_READY
                && (count >= MAX_RETRY_COUNT))) {
            ril_error = RIL_E_SIM_ERR;
            logE(mTag, "handleGetSimStatus ril_error = RIL_E_SIM_ERR.");
        } else {
            ril_error = RIL_E_SUCCESS;
        }
    }

    // The parameter used by AOSP_V1_2::CardStatus
    if (p_card_status != NULL) {
        p_card_status->physicalSlotId = m_slot_id;
    }

    // External SIM [Start]
    // VSIM need more time to initialize, we keep SIM status as NOT_READY event if get BUSY
    // over than 2 seconds.
    if (ret == UICC_NOT_READY && RfxRilUtils::isVsimEnabledBySlot(m_slot_id)) {
        ril_error = RIL_E_SIM_ERR;
        logE(mTag, "SIM status is not ready under vsim enabled.");
    }
    // External SIM [End]

    // Send TC layer the response
    if (ril_error == RIL_E_SUCCESS) {
        response = RfxMclMessage::obtainResponse(msg->getId(), ril_error,
                RfxSimStatusData((void*)p_card_status, sizeof(RIL_CardStatus_v8)), msg, false);
    } else {
        response = RfxMclMessage::obtainResponse(msg->getId(), ril_error,
                RfxSimStatusData(NULL, 0), msg, false);
    }
    responseToTelCore(response);

    // Release memory
    if (p_card_status != NULL) {
        for (int i = 0; i < p_card_status->num_applications; i++) {
            if (p_card_status->applications[i].app_label_ptr != NULL) {
                free(p_card_status->applications[i].app_label_ptr);
            }
            if (p_card_status->applications[i].aid_ptr != NULL) {
                free(p_card_status->applications[i].aid_ptr);
            }
        }
        free(p_card_status->atr);
        free(p_card_status->iccId);
        free(p_card_status->eid);
        free(p_card_status);
    }
}

bool RmcCommSimRequestHandler::serviceActivationStatus(int fileId, int appTypeId) {
    int index = -1, err = 0, support = 0;
    bool result = true;
    String8 cmd("");
    RfxAtLine *line = NULL;
    sp<RfxAtResponse> p_response = NULL;

    switch(fileId) {
        case 28486: // 0x6F46 EF_SPN
            // SPN
            if (appTypeId == UICC_APP_USIM) {
                index = 19;
            } else if (appTypeId == UICC_APP_SIM) {
                index = 17;
            }
            break;
        case 28617: // 0x6FC9 EF_MBI
            // MBI. Check Mailbox Dialling Numbers
            if (appTypeId == UICC_APP_USIM) {
                index = 47;
            } else if (appTypeId == UICC_APP_SIM) {
                index = 53;
            }
            break;
        case 28618: // 0x6FCA EF_MWIS
            // MWIS
            if (appTypeId == UICC_APP_USIM) {
                index = 48;
            } else if (appTypeId == UICC_APP_SIM) {
                index = 54;
            }
            break;
        case 28489:  // 0x6F49 EF_SDN
            if (appTypeId == UICC_APP_USIM) {
                index = 4;
            } else if (appTypeId == UICC_APP_SIM) {
                index = 18;
            }
            break;
    }

    if (index >= 0) {
        // Use AT+ESSTQ=<app>,<service> to query service table
        // 0:  Service not supported
        // 1:  Service supported
        // 2:  Service allocated but not activated
        cmd.append(String8::format("AT+ESSTQ=%d,%d", appTypeId, index));
        p_response = atSendCommandSingleline(cmd, "+ESSTQ:");
        cmd.clear();

        err = p_response->getError();
        // The same as AOSP. 0 - Available & Disabled, 1-Available & Enabled, 2-Unavailable.
        if (err < 0 || p_response->getSuccess() == 0) {
            logE(mTag, "Fail to query service table");
        } else {
            line = p_response->getIntermediates();

            line->atTokStart(&err);
            support = line->atTokNextint(&err);
            if (err >= 0) {
                if (support != 1) {
                    result = false;
                }
            }
            logD(mTag, "serviceActivationStatus result: %d", result);
        }
        p_response = NULL;
    }

    return result;
}

void RmcCommSimRequestHandler::handleSimIo(const sp<RfxMclMessage>& msg) {
    int err = 0, intPara = 0;
    RIL_SIM_IO_v6 *pData = (RIL_SIM_IO_v6*)(msg->getData()->getData());
    String8 cmd("");
    String8 path("");
    String8 aid((pData->aidPtr != NULL)? pData->aidPtr : "");
    String8 data((pData->data != NULL)? pData->data : "");
    String8 simResponse("");
    int appTypeId = -1, channelId = 0;
    int remain = pData->p3;
    RIL_Errno result = RIL_E_SIM_ERR;
    RfxAtLine *line = NULL;
    char *tmpStr = NULL;
    sp<RfxAtResponse> p_response = NULL;
    sp<RfxMclMessage> response;
    RIL_SIM_IO_Response sr;
    int64_t tSimSwitch = 0;
    int len = 0;
    int offset = pData->p1 * (1 << 8) + pData->p2;

    memset(&sr, 0, sizeof(RIL_SIM_IO_Response));

    appTypeId = queryAppTypeId(aid);
    if (appTypeId == -1) {
        result = RIL_E_REQUEST_NOT_SUPPORTED;
        goto error;
    }

    if (!serviceActivationStatus(pData->fileid, appTypeId)) {
        result = RIL_E_REQUEST_NOT_SUPPORTED;
        goto error;
    }

    //check timestampe between the request msg and the capability switch begin
    tSimSwitch = getNonSlotMclStatusManager()->getInt64Value(
            RFX_STATUS_KEY_SIM_SWITCH_RADIO_UNAVAIL_TIME);
    if (msg->getTimeStamp() <= tSimSwitch) {
        //check timestampe between the request msg and the capability switch begin
        result = RIL_E_INVALID_STATE;
        goto error;
    }

    if (pData->pin2 != NULL && strlen(pData->pin2) > 0) {
        logD(mTag, "handleSimIo pin2 %.3s", pData->pin2);
        cmd.append(String8::format("AT+EPIN2=\"%s\"", pData->pin2));
        p_response = atSendCommand(cmd.string());
        err = p_response->getError();

        if (p_response != NULL) {
            if (p_response->getSuccess() == 0) {
                switch (p_response->atGetCmeError()) {
                    case CME_SIM_PIN2_REQUIRED:
                        result = RIL_E_SIM_PIN2;
                        break;
                    case CME_SIM_PUK2_REQUIRED:
                        result = RIL_E_SIM_PUK2;
                        break;
                    default:
                        result = RIL_E_SIM_ERR;
                        break;
                }
            } else {
                // success case
                result = RIL_E_SUCCESS;
            }
        }

        p_response = NULL;
        cmd.clear();

        if (result != RIL_E_SUCCESS) {
            logE(mTag, "Fail to check PIN2");
            goto error;
        }
    }

    // SIM access
    // 1. Remove 3F00
    if (pData->path != NULL) {
        if (strstr(pData->path, "3F00") || strstr(pData->path, "3f00")) {
            if (strlen(pData->path) > 4) {
                path.append(String8::format("%s", pData->path + 4));
            }
        } else {
            path.append(String8::format("%s", pData->path));
        }

        if ((strstr(pData->path, "7f25") || strstr(pData->path, "7F25")) &&
                ((getMclStatusManager()->getIntValue(RFX_STATUS_KEY_CDMA3G_SWITCH_CARD) ==
                AP_TRIGGER_SWITCH_SIM) ||
                (getMclStatusManager()->getIntValue(RFX_STATUS_KEY_CDMA3G_SWITCH_CARD) ==
                GMSS_TRIGGER_SWITCH_SIM))) {
            // Ignore request if the CDMA 3G card is switched into SIM.
            logE(mTag, "Ignore the sim io as CDMA 3G card is switched into sim.");

            goto error;
        }
    }

    // 2. Query channel id
    cmd.append(String8::format("AT+ESIMAPP=%d,0", appTypeId));
    p_response = atSendCommandSingleline(cmd.string(), "+ESIMAPP:");

    if (p_response != NULL && p_response->getSuccess() > 0) {
        // Success
        line = p_response->getIntermediates();
        line->atTokStart(&err);

        // application id
        intPara = line->atTokNextint(&err);

        // channel id
        channelId = line->atTokNextint(&err);
        if (channelId == 255) {
            logE(mTag, "channel id is 255!");
            result = RIL_E_SIM_BUSY;
            goto error;
        }

        p_response = NULL;
        cmd.clear();
        line = NULL;
    } else {
        logE(mTag, "Fail to get app type %d channel id!", appTypeId);
        result = RIL_E_SIM_ERR;
        goto error;
    }

    logD(mTag, "SIM_IO(%d, %d, %d, %d, %d, %d, %s)", channelId, pData->command, pData->fileid,
                pData->p1, pData->p2, pData->p3, pData->path);

    if (pData->command == 176 && ((remain >> 8) > 127)) {
        // acording spec, P1 can't greater than 128
        remain = (0x7F << 8) + (remain &0xFF);
        logE(mTag, "SIM_IO read file length error (%d, %d->%d)",
            pData->fileid, pData->p3, remain);
    }

    if (((pData->command == 192) || (pData->command == 242)) && (remain <= 0)) {
        // Set remain value same with AOSP define for get_response command.
        remain = 15;
    }

    if (!data.isEmpty() && (pData->data != NULL)) {
        int length = strlen(pData->data);
        if (length < ((2 * pData->p3) - 1)) {
            logE(mTag, "Invalid data length: %d, remain length: %d, skip to do SIM_IO",
                    length, pData->p3);
            result = RIL_E_REQUEST_NOT_SUPPORTED;
            goto error;
        }
    }

    while (remain > 0) {
        // 3. Send AT+ECRLA
        result = RIL_E_SIM_ERR;
        cmd.clear();

        if ((pData->command == 192) || (pData->command == 242)) {
            // GET RESPONSE or STATUS
            cmd.append(String8::format("AT+ECRLA=%d,%d,%d,%d,%d,%d,%d", appTypeId, channelId,
                    pData->command, pData->fileid, pData->p1, pData->p2, 0 /*P3*/));
        } else if (data.isEmpty()) {
            // READ COMMAND, P3: Max value is 256 and use 0 to represent 256
            len = ((remain < 256) ? remain : 256);
            cmd.append(String8::format("AT+ECRLA=%d,%d,%d,%d,%d,%d,%d", appTypeId, channelId,
                    pData->command, pData->fileid, (0xFF & (offset >> 8))/*P1*/,
                    (0xFF & offset)/*P2*/,
                    ((remain < 256) ? remain : 0)/*P3*/));
        } else {
            // WRITE COMMAND, P3: Max value is 255
            len = (remain > 255) ? 255 : remain;

            cmd.append(String8::format("AT+ECRLA=%d,%d,%d,%d,%d,%d,%d", appTypeId, channelId,
                    pData->command, pData->fileid, (0xFF & (offset >> 8))/*P1*/,
                    (0xFF & offset)/*P2*/,
                    len/*P3*/));
        }

        if (!data.isEmpty() && (pData->data != NULL)) {
            // Command type WRITE
            // Append <data>
            tmpStr = (char*)calloc(1, sizeof(char) * 512);
            RFX_ASSERT(tmpStr != NULL);
            strncpy(tmpStr, pData->data + 2 * (pData->p3 - remain), 2 * len);
            cmd.append(String8::format(",\"%s\"", tmpStr));
            free(tmpStr);
            tmpStr = NULL;

            offset += len;
            remain -= len;
        } else if (!path.isEmpty()) {
            // append comma only if there is path, this is for data field
            cmd.append(",");
        }

        if (!path.isEmpty()) {
            // Append <path>
            cmd.append(String8::format(",\"%s\"", path.string()));
        }

        p_response = atSendCommandSingleline(cmd.string(), "+ECRLA:");

        if (p_response != NULL && p_response->getSuccess() == 1) {
            // Success
            line = p_response->getIntermediates();

            line->atTokStart(&err);
            if (err < 0) {
                goto error;
            }

            sr.sw1 = line->atTokNextint(&err);
            if (err < 0) {
                goto error;
            }

            sr.sw2 = line->atTokNextint(&err);
            if (err < 0) {
                goto error;
            }

            if (line->atTokHasmore()) {
                char *pRes = NULL;
                pRes = line->atTokNextstr(&err);
                if (err < 0) {
                    goto error;
                }
                simResponse.append(String8::format("%s", pRes));

                if ((pData->command == 192) || (pData->command == 242)) {
                    // In the case of GET_RESPONSE, we use 0 instead of pData->p3 so we set reamin as 0
                    // directly.
                    remain = 0;
                } else if (pData->data == NULL) {
                    // Case of command type READ
                    offset += len;
                    remain -= len;
                    len = ((remain < 256) ? remain : 256);
                }

                if (remain == 0) {
                    // no more SIM acess
                    asprintf(&sr.simResponse, "%s", simResponse.string());
                }
                // Run FCP parser for USIM and CSIM when the command is GET_RESPONSE
                if ((appTypeId == UICC_APP_USIM || appTypeId == UICC_APP_CSIM ||
                        appTypeId == UICC_APP_ISIM || isSimIoFcp(sr.simResponse))
                        && pData->command == 192 /* GET_RESPONSE */) {
                    makeSimRspFromUsimFcp((unsigned char**)&sr.simResponse, pData->fileid);
                }

            } else if (pData->data == NULL) {
                // The command type is READ, but can't read data
                remain = 0;
            }
            result = RIL_E_SUCCESS;
        } else {
            // Fail to do SIM_IO
            remain = 0;
        }
    }

    if (RfxRilUtils::isEngLoad()) {
        logI(mTag, "SIM_IO(result %d, sw1 %d, sw2 %d, response %s)", result, sr.sw1, sr.sw2,
                sr.simResponse);
    }

    if ((sr.sw1 == 0x00) && (sr.sw2 == 0x00)) {
        result = RIL_E_REQUEST_NOT_SUPPORTED;
        goto error;
    } else if ((sr.sw1 == 0x69) && (sr.sw2 == 0x82)) {
        result = RIL_E_OPERATION_NOT_ALLOWED;
        goto error;
    }

    response = RfxMclMessage::obtainResponse(msg->getId(), result,
            RfxSimIoRspData((void*)&sr, sizeof(sr)), msg, false);

    responseToTelCore(response);
    p_response = NULL;

    if (sr.simResponse != NULL) {
        free(sr.simResponse);
    }
    return;
error:
    response = RfxMclMessage::obtainResponse(msg->getId(), result,
            RfxSimIoRspData((void*)&sr, sizeof(sr)), msg, false);

    responseToTelCore(response);
    p_response = NULL;

    if (sr.simResponse != NULL) {
        free(sr.simResponse);
    }

}

void RmcCommSimRequestHandler::handleIsimAuthentication(const sp<RfxMclMessage>& msg) {
    char *pData = (char*)(msg->getData()->getData());
    sp<RfxAtResponse> p_response = NULL;
    int err = 0, intPara;
    int channelId;
    String8 cmd("");
    RfxAtLine *line = NULL;
    char *auth_rsp = NULL;
    RIL_SIM_IO_Response sr;
    RIL_Errno result = RIL_E_SIM_ERR;
    int currSimInsertedState = getMclStatusManager()->getIntValue(RFX_STATUS_KEY_SIM_STATE);

    do {
        if (RFX_SIM_STATE_ABSENT == currSimInsertedState) {
            logE(mTag, "handleIsimAuthentication, sim absent");
            result = RIL_E_SIM_ABSENT;
            break;
        }
        if (pData == NULL || strlen(pData) <= 0) {
            logE(mTag, "handleIsimAuthentication, empty parameter");
            result = RIL_E_INVALID_ARGUMENTS;
            break;
        }
        // 1. Query channel id
        // TODO: Set ISIM app type id
        cmd.append(String8::format("AT+ESIMAPP=1,0"));

        p_response = atSendCommandSingleline(cmd.string(), "+ESIMAPP:");

        if (p_response != NULL && p_response->getSuccess() == 1) {
            // Success
            line = p_response->getIntermediates();
            line->atTokStart(&err);

            // application id
            intPara = line->atTokNextint(&err);

            // channel id
            channelId = line->atTokNextint(&err);
            if (channelId == 255) {
                logE(mTag, "channel id is 255!");
                result = RIL_E_SIM_BUSY;
                break;
            }

            p_response = NULL;
            cmd.clear();
            line = NULL;
        } else {
            logE(mTag, "Fail to query ISIM channel");
            break;
        }

        // 2. ISIM authentication
        cmd.append(String8::format("AT+ESIMAUTH=%d,0,\"%s\"", channelId, pData));
        p_response = atSendCommandSingleline(cmd.string(), "+ESIMAUTH:");

        if (p_response != NULL && p_response->getSuccess() == 1) {
            // Success
            line = p_response->getIntermediates();
            line->atTokStart(&err);
            if(err < 0) {
                break;
            }

            sr.sw1 = line->atTokNextint(&err);
            if(err < 0) {
                break;
            }

            sr.sw2 = line->atTokNextint(&err);
            if(err < 0) {
                break;
            }

            if(line->atTokHasmore()){
                sr.simResponse = line->atTokNextstr(&err);
                if(err < 0) {
                    break;
                }

                auth_rsp = (char*)calloc(1, sizeof(char)*MAX_AUTH_RSP);
                RFX_ASSERT(auth_rsp != NULL);
                strcpy(auth_rsp, sr.simResponse);
                logI(mTag, "requestIsimAuthentication %s, %02x, %02x", auth_rsp, sr.sw1, sr.sw2);
            } else {
                logI(mTag, "No response data");
            }
            result = RIL_E_SUCCESS;
        } else {
            logE(mTag, "Fail to do ISIM authentication!");
            break;
        }

        p_response = NULL;
    } while(0);

    sp<RfxMclMessage> response = NULL;

    if (RIL_E_SUCCESS == result) {
        response = RfxMclMessage::obtainResponse(msg->getId(), result,
                RfxStringData((void*)auth_rsp, strlen(auth_rsp)), msg, false);
    } else {
        response = RfxMclMessage::obtainResponse(msg->getId(), result,
                RfxStringData(), msg, false);
    }
    responseToTelCore(response);
    if (NULL != auth_rsp) {
        free(auth_rsp);
    }
    p_response = NULL;
}

void RmcCommSimRequestHandler::handleGeneralSimAuthentication(const sp<RfxMclMessage>& msg) {
    sp<RfxAtResponse> p_response = NULL;
    RIL_SIM_IO_Response sim_auth_response;
    RIL_SimAuthStructure *pSimAuthData = NULL;
    int err;
    String8 cmd("");
    RfxAtLine *line = NULL;
    RIL_Errno result = RIL_E_GENERIC_FAILURE;

    logD(mTag, "handleGeneralSimAuthentication");

    do {
        pSimAuthData = (RIL_SimAuthStructure*)(msg->getData()->getData());
        logI(mTag, "pSimAuthData %d, %d", pSimAuthData->mode,pSimAuthData->sessionId);
        if(pSimAuthData->mode == 0) {
            // mode 0 is represent AKA authentication mode
            if (pSimAuthData->sessionId == 0) {
                // Session id is equal to 0, for backward compability, we use old AT command
                if (pSimAuthData->param2 != NULL && strlen(pSimAuthData->param2) > 0) {
                    // There is param2 means that caller except to use USIM AUTH
                    cmd.append(String8::format("AT+EAUTH=\"%s\",\"%s\"",
                            pSimAuthData->param1, pSimAuthData->param2));
                } else {
                    // There is no param2 means that caller except to use SIM AUTH
                    cmd.append(String8::format("AT+EAUTH=\"%s\"", pSimAuthData->param1));
                }
            } else {
                // Session id is not equal to 0, means we can use new AT command
                cmd.append(String8::format("AT+ESIMAUTH=%d,%d,\"%s%s\"",
                        pSimAuthData->sessionId, pSimAuthData->mode,
                        pSimAuthData->param1, pSimAuthData->param2));
            }
        } else if (pSimAuthData->mode == 1) {
            // mode 1 is represent GBA authentication mode
            cmd.append(String8::format("AT+ESIMAUTH=%d,%d,\"%02x%s%s\"",
                    pSimAuthData->sessionId, pSimAuthData->mode, pSimAuthData->tag,
                    pSimAuthData->param1, pSimAuthData->param2));
        }

        if (pSimAuthData->mode == 0 && pSimAuthData->sessionId == 0) {
            p_response = atSendCommandSingleline(cmd.string(), "+EAUTH:");
        } else {
            p_response = atSendCommandSingleline(cmd.string(), "+ESIMAUTH:");
        }
        memset(&sim_auth_response, 0, sizeof(RIL_SIM_IO_Response));
        if (p_response != NULL) {
            err = p_response->getError();
            if (err < 0 || p_response->getSuccess() == 0) {
                logE(mTag, "requestGeneralSimAuth Fail", p_response->atGetCmeError());
                break;
            } else {
                line = p_response->getIntermediates();
                line->atTokStart(&err);
                if (err < 0) {
                    break;
                }
                sim_auth_response.sw1 = line->atTokNextint(&err);
                if (err < 0) {
                    break;
                }
                sim_auth_response.sw2 = line->atTokNextint(&err);
                if (err < 0) {
                    break;
                }

                if(line->atTokHasmore()){
                    sim_auth_response.simResponse = line->atTokNextstr(&err);
                    if(err < 0) {
                        break;
                    }
                    logI(mTag, "requestGeneralSimAuth response len = %zu %02x, %02x",
                            strlen(sim_auth_response.simResponse),
                            sim_auth_response.sw1, sim_auth_response.sw2);
                } else {
                    logI(mTag, "No response data");
                }
            }
        } else {
            break;
        }
        result = RIL_E_SUCCESS;
    } while(0);
    p_response = NULL;
    cmd.clear();
    line = NULL;

    sp<RfxMclMessage> response = NULL;

    if (result == RIL_E_SUCCESS) {
        response = RfxMclMessage::obtainResponse(msg->getId(), result,
                RfxSimIoRspData((void*)&sim_auth_response, sizeof(RIL_SIM_IO_Response)), msg, false);
    } else {
        response = RfxMclMessage::obtainResponse(msg->getId(), result,
                RfxSimIoRspData(NULL, 0), msg, false);
    }
    responseToTelCore(response);
}
void RmcCommSimRequestHandler::handleSimAuthentication(const sp<RfxMclMessage>& msg) {
    sp<RfxAtResponse> p_response = NULL;
    RIL_SIM_IO_Response *sim_auth_response = NULL;
    RIL_SimAuthentication *pSimAuthData = NULL;
    int err;
    bool closeChannelLater = false;
    int appTypeId = -1, channelId = -1, len = 0, intPara = 0;
    String8 cmd("");
    RfxAtLine *line = NULL;
    unsigned char *out_put = NULL;
    char *payload = NULL;// *pByteArray = NULL;
    char tmp[256] = {0};
    RIL_Errno result = RIL_E_SIM_ERR;

    do {
        pSimAuthData = (RIL_SimAuthentication*)(msg->getData()->getData());
        if (pSimAuthData == NULL) {
            break;
        }
        // 1. Query app type id
        appTypeId = queryAppTypeId(String8::format("%s", pSimAuthData->aid));

        // 2. Get channel id
        if (appTypeId == -1) {
            if (pSimAuthData->aid != NULL) {
                // Open channel for specific AID
                cmd.append(String8::format("AT+CCHO=\"%s\"", pSimAuthData->aid));
                p_response = atSendCommandNumeric(cmd.string());
                cmd.clear();
                if (p_response == NULL) {
                    break;
                }
                if (p_response->getSuccess() > 0) {
                    channelId = atoi(p_response->getIntermediates()->getLine());
                    if (channelId <= 0 || channelId > 19) {
                        logE(mTag, "Invalid channel id");
                        break;
                    }
                    closeChannelLater = true;
                } else {
                    logE(mTag, "Fail to open channel for AID %s", pSimAuthData->aid);
                    if (p_response != NULL) {
                        switch (p_response->atGetCmeError()) {
                            case CME_MEMORY_FULL:
                                result = RIL_E_MISSING_RESOURCE;
                                break;
                            case CME_NOT_FOUND:
                                result = RIL_E_NO_SUCH_ELEMENT;
                                break;
                            default:
                                break;
                        }
                    }
                    break;
                }

                p_response = NULL;
            } else {
                logE(mTag, "Parameter error!");
                result = RIL_E_INVALID_ARGUMENTS;
                break;
            }
        } else {
            // Query channel id according to app type id
            cmd.append(String8::format("AT+ESIMAPP=%d,0", appTypeId));

            p_response = atSendCommandSingleline(cmd.string(), "+ESIMAPP:");
            cmd.clear();

            if (p_response != NULL && p_response->getSuccess() > 0) {
                // Success
                line = p_response->getIntermediates();
                line->atTokStart(&err);

                // application id
                intPara = line->atTokNextint(&err);

                // channel id
                channelId = line->atTokNextint(&err);
                if (channelId == 255) {
                    logE(mTag, "channel id is 255!");
                    result = RIL_E_SIM_BUSY;
                    break;
                }

                line = NULL;
            } else {
                logE(mTag, "Fail to query app %d channel", appTypeId);
                break;
            }

            p_response = NULL;
        }
        if (NULL == pSimAuthData->authData) {
            logE(mTag, "authData is null!");
            result = RIL_E_INVALID_ARGUMENTS;
            break;
        }
        // 3. Decode data
        out_put = base64_decode_to_str((unsigned char *)pSimAuthData->authData,
                strlen(pSimAuthData->authData));
        logI(mTag, "[requestSimAuthentication] decode output %s", out_put);

        // 4. Send authentication APDU
        // AT+CGLA="channel id","len","CLA+INS+P1+P2+Lc+Data+Le"
        // CLA: if channel id 0~3, then CLA=0X; otherwise, if channel id 4~19, then CLA=4X
        // INS: 88 for authentication command
        // P1:00
        // P2 is decided by user's parameter, will be 8X according authentication context type
        // Lc:length of authentication context
        // Data: authentication context decided by user's parameter
        // Le: max length of data expected in response. use 00 represent unknown.
        if (out_put != NULL) {
            if ((appTypeId == UICC_APP_USIM) || (appTypeId == UICC_APP_ISIM)) {
                //TODO: The case of USIM
                cmd.append(String8::format("AT+CGLA=%d,%d,\"%02x%02x%02x%02x%02x%s00\"",
                        channelId, (unsigned int)(12 + strlen((char*)out_put)),
                        ((channelId <= 3) ? channelId : (4 * 16 + channelId - 4)), 0x88, 0,
                        pSimAuthData->authContext, (unsigned int)(strlen((char*)out_put)/2), out_put));
            } else {
                cmd.append(String8::format("AT+CGLA=%d,%d,\"%02x%02x%02x%02x%s0C\"",
                        channelId, (unsigned int)(10 + strlen((char*)out_put)), 0xA0, 0x88, 0x00,
                        0x00, out_put));
            }
            p_response = atSendCommandSingleline(cmd.string(), "+CGLA:");
            cmd.clear();
            free(out_put);
            out_put = NULL;
        }
        if (p_response != NULL && p_response->getSuccess() > 0) {
            sim_auth_response = (RIL_SIM_IO_Response*)calloc(1, sizeof(RIL_SIM_IO_Response));
            RFX_ASSERT(sim_auth_response != NULL);
            line = p_response->getIntermediates();
            line->atTokStart(&err);
            if (err < 0) {
                break;
            }

            len = line->atTokNextint(&err);
            if (err < 0) {
                break;
            }
            payload = line->atTokNextstr(&err);
            if (err < 0) {
                break;
            }
            sscanf(&(payload[len - 4]), "%02x%02x", &(sim_auth_response->sw1),
                    &(sim_auth_response->sw2));

            if (sim_auth_response->sw1 != 0x90 && sim_auth_response->sw1 != 0x91) {
                logE(mTag, "Fail to do SIM authentication");
                result = RIL_E_INVALID_ARGUMENTS;
                break;
            }

            if (len > 255) {
                len = 255;
            }

            if (len > 4) {
                len = len - 4;
                memset(tmp, 0, sizeof(char)*256);
                strncpy(tmp, payload, len);

                logI(mTag, "SIM authentication rsp %s(%zu)", tmp, sizeof(tmp));
                out_put = base64_encode_to_str((unsigned char*)tmp, strlen(tmp));
            }

            sim_auth_response->simResponse = (char*)out_put;

            logI(mTag, "SIM authentication payload = %s %02x, %02x",
                    sim_auth_response->simResponse, sim_auth_response->sw1, sim_auth_response->sw2);

            result = RIL_E_SUCCESS;
        } else {
            logE(mTag, "Fail to do SIM authentication");
            result = RIL_E_INVALID_ARGUMENTS;
            break;
        }
    } while(0);

    p_response = NULL;

    sp<RfxMclMessage> response = RfxMclMessage::obtainResponse(msg->getId(), result,
            RfxSimIoRspData((void*)sim_auth_response,
            ((sim_auth_response != NULL)? sizeof(RIL_SIM_IO_Response) : 0)), msg, false);

    responseToTelCore(response);

    if (closeChannelLater) {
        // Step3. Close channel to avoid open too much unuseless channels
        cmd.append(String8::format("AT+CCHC=%d", channelId));
        p_response = atSendCommand(cmd);
        cmd.clear();
        if (p_response != NULL) {
            err = p_response->getError();
            if (err < 0 || p_response->getSuccess() == 0) {
                logE(mTag, "[requestSimAuthentication] close channel fail");
            }
        }
        p_response = NULL;
    }

    if (out_put != NULL) {
        free(out_put);
    }

    if (sim_auth_response != NULL) {
        free(sim_auth_response);
    }

}

void RmcCommSimRequestHandler::handleQueryEons(const sp < RfxMclMessage > & msg) {
    logD(mTag, "handleQueryEons");
    sp<RfxAtResponse> p_response = NULL;
    RfxAtLine *line;
    int err;
    RIL_Errno ret = RIL_E_SIM_ERR;
    int nameValid, shotNameValid = -1;
    char *onsName = NULL;
    String8 onsKey("");
    String8 shortOnsKey("");
    RFX_UNUSED(msg);

    do {
        p_response = atSendCommandSingleline("AT+ECPHSONS?", "+ECPHSONS:");
        err = p_response->getError();
        if (err < 0) {
            logE(mTag, "Fail to query EONS");
            break;
        }

        if (p_response->getSuccess() > 0) {
            ret = RIL_E_SUCCESS;
        }

        if (ret != RIL_E_SUCCESS) {
            logE(mTag, "Query EONS, but got error!");
            break;
        }

        if (ret == RIL_E_SUCCESS) {
            line = p_response->getIntermediates();

            line->atTokStart(&err);
            if (err < 0) break;

            nameValid = line->atTokNextint(&err);
            if (err < 0) break;

            onsName = line->atTokNextstr(&err);
            if (err < 0) break;

            if (nameValid == 1) {
                onsKey.append(String8::format("%s", onsName));
                getMclStatusManager()->setString8Value(RFX_STATUS_KEY_ONS, onsKey);
            } else {
                getMclStatusManager()->setString8Value(RFX_STATUS_KEY_ONS, String8(""));
            }

            shotNameValid = line->atTokNextint(&err);
            if (err < 0) break;

            onsName = line->atTokNextstr(&err);
            if (err < 0) break;

            if (shotNameValid == 1) {
                shortOnsKey.append(String8::format("%s", onsName));
                getMclStatusManager()->setString8Value(RFX_STATUS_KEY_SHORT_ONS, shortOnsKey);
            } else {
                getMclStatusManager()->setString8Value(RFX_STATUS_KEY_SHORT_ONS, String8(""));
            }
            logD(mTag, "Query EONS, name: %d, onsName: %s, shortName %d, shortOnsName: %s ",
                    nameValid, onsKey.string(), shotNameValid, shortOnsKey.string());

        }
    } while(0);
}


void RmcCommSimRequestHandler::handleQueryIccid(const sp < RfxMclMessage > & msg) {
    sp<RfxAtResponse> p_response = NULL;
    int err;
    RfxAtLine *line;
    char *iccId = NULL;
    RIL_Errno ret = RIL_E_SIM_ERR;
    String8 prop("vendor.ril.iccid.sim");
    String8 iccidKey("");
    bool skipUpdateCardType = false;

    RFX_UNUSED(msg);
    prop.append(String8::format("%d", (m_slot_id+1)));


    do {
        p_response = atSendCommandSingleline("AT+ICCID?", "+ICCID:");
        err = p_response->getError();

        if (err < 0) {
            logE(mTag, "Fail to query iccid");
            break;
        }

        if (p_response->getSuccess() > 0) {
            ret = RIL_E_SUCCESS;
        } else {
            if (p_response->atGetCmeError() == CME_SIM_BUSY) {
                ret = RIL_E_SIM_BUSY;
                sleepMsec(200);
            } else if (p_response->atGetCmeError() == CME_SIM_NOT_INSERTED) {
                ret = RIL_E_SIM_ABSENT;
            }
        }

        if (ret != RIL_E_SUCCESS && ret != RIL_E_SIM_BUSY && ret != RIL_E_SIM_ABSENT) {
            logE(mTag, "Query iccid, but got error!");
            break;
        }

        if (ret == RIL_E_SUCCESS) {
            line = p_response->getIntermediates();
            line->atTokStart(&err);
            if (err < 0) break;

            iccId = line->atTokNextstr(&err);
            if (err < 0) break;
            // Convert all the lower case characters in iccId to upper case
            stringToUpper(iccId);
            // TODO: To print iccid using special log
            //rfx_property_set(prop.string(), iccId);
            iccidKey.append(String8::format("%s", iccId));
            getMclStatusManager()->setString8Value(RFX_STATUS_KEY_SIM_ICCID, iccidKey);
            sendIccidChanged(iccId);

            if (isAOSPPropSupport()) {
                String8 iccidPre("gsm.sim.preiccid_");
                String8 tempIccid(iccId);
                iccidPre.append(String8::format("%d", m_slot_id));
                const char *tempStr = tempIccid.string();
                if (tempStr != NULL) {
                    rfx_property_set(iccidPre, string(tempStr).substr(0, 7).c_str());
                } else {
                    logE(mTag, "Query iccid error, empty iccid");
                }
            }
        } else if (ret == RIL_E_SIM_ABSENT) {
            bool aospEnabled = isEnableUiccApplicationsSupported();
            if ((!aospEnabled && (getMclStatusManager()->getIntValue(RFX_STATUS_KEY_SIM_ONOFF_STATE)
                    != SIM_POWER_STATE_SIM_OFF))
                    || (aospEnabled && (getMclStatusManager()->getIntValue(
                    RFX_STATUS_KEY_AOSP_UICC_APPLICATIONS_ENABLE_STATE)
                    != UICC_APPLICATIONS_ENABLE_STATE_DISABLED))) {
                logD(mTag, "Query iccid, but SIM card is absent");
                //rfx_property_set(prop.string(), "N/A");
                getMclStatusManager()->setString8Value(RFX_STATUS_KEY_SIM_ICCID, String8("N/A"));
                sendIccidChanged("N/A");
            } else {
                // sim power off case, can't get iccid, shall not update cdma card type to not insert.
                skipUpdateCardType = true;
                logD(mTag, "Query iccid, but SIM card is off");
            }
        }
    } while(ret == RIL_E_SIM_BUSY);

    sp<RfxMclMessage> unsol = RfxMclMessage::obtainUrc(RFX_MSG_URC_RESPONSE_SIM_STATUS_CHANGED,
            m_slot_id, RfxVoidData());
    responseToTelCore(unsol);

    //RLOGD("queryIccId before release_wake_lock");
    mtk_release_wake_lock("sim_hot_plug");

    RmcSimPinPukCount *retry = getPinPukRetryCount();
    if (retry != NULL) {
        free(retry);
    }

    // SIM Extended APDU.
    querySimExtendedFormat();

    // Generate CDMA card type.
    if (!skipUpdateCardType) {
        handleCdmaCardType(iccId);
    }

    // Get SML retry count
    if (isSimSlotLockSupport()) {
        RmcSimSlotLockDeviceLockInfo* DeviceLockInfo = getSimSlotLockDeviceLockInfo();
        if (DeviceLockInfo != NULL) {
            free(DeviceLockInfo);
        }
    }
}

int RmcCommSimRequestHandler::openChannel(const sp < RfxMclMessage > & msg,
        RIL_SIM_IO_Response *sr, int *len) {
    sp<RfxAtResponse> p_response;
    String8 cmd("");
    int err, ril_error = RIL_E_SIM_ERR;
    RfxAtLine *line = NULL;
    char *rData = NULL;
    int cmeError = CME_SUCCESS;
    int cdmaType = getMclStatusManager()->getIntValue(RFX_STATUS_KEY_CDMA_CARD_TYPE);
    RFX_UNUSED(msg);

    if ((cdmaType == CT_UIM_SIM_CARD) || (cdmaType == CT_3G_UIM_CARD)) {
        goto error;
    }
    // AT+CGLA=<sessionid>,<length>,<command>
    // <sessionid> = 0
    // <command> = 00 70 00 00 01
    cmd.append(String8::format("AT+CGLA=%d,%d,\"%02x%02x%02x%02x%02x\"",
            0, 10, 0x00, 0x70, 0x00, 0x00, 0x01));
    p_response = atSendCommandSingleline(cmd, "+CGLA:");
    err = p_response->getError();
    if (err < 0 || p_response->getSuccess() == 0) {
        logE(mTag, "Fail to open channel");
        if (p_response->getFinalResponse() != NULL) {
            if (!strcmp(p_response->getFinalResponse()->getLine(), "+CME ERROR: MEMORY FULL")) {
                ril_error = RIL_E_MISSING_RESOURCE;
            } else if (!strcmp(p_response->getFinalResponse()->getLine(), "+CME ERROR: NOT FOUND")) {
                ril_error = RIL_E_NO_SUCH_ELEMENT;
            } else {
                cmeError = p_response->atGetCmeError();
                logE(mTag, "openChannel: cme_ERROR: %d", cmeError);
                switch(cmeError) {
                    // GSMA NFC: IO Error if SIM has no response.
                    case CME_UNKNOWN:
                        ril_error = RIL_E_OEM_ERROR_1;
                        break;
                    default:
                        break;
                }
            }
        }
        goto error;
    }

    line = p_response->getIntermediates();
    line->atTokStart(&err);
    if (err < 0) goto error;
    (*len) = line->atTokNextint(&err);
    if (err < 0) goto error;
    rData = line->atTokNextstr(&err);
    if (err < 0) goto error;

    sscanf(&(rData[(*len) - 4]), "%02x%02x", &(sr->sw1), &(sr->sw2));
    rData[(*len) - 4] = '\0';
    // Remember to free it!
    asprintf(&sr->simResponse, "%s", rData);

    p_response = NULL;

    if (sr->sw1 != 0x90 && sr->sw1 != 0x91) { // wrong sw1, sw2
        if ((sr->sw1 == 0x6A && sr->sw2 == 0x82) ||
                (sr->sw1 == 0x69 && sr->sw2 == 0x85) ||
                (sr->sw1 == 0x69 && sr->sw2 == 0x99)) {
            ril_error = RIL_E_NO_SUCH_ELEMENT;
        } else if ((sr->sw1 == 0x6A && sr->sw2 == 0x84) ||
                   (sr->sw1 == 0x6A && sr->sw2 == 0x81) ||
                   (sr->sw1 == 0x68 && sr->sw2 == 0x81)) {
            logE(mTag, "Not enough memory space in the file");
            ril_error = RIL_E_MISSING_RESOURCE;
        }
    } else {
        ril_error = RIL_E_SUCCESS;
    }

    return ril_error;

error:
    sr->sw1 = 0x6f;
    sr->sw2 = 0x00;
    sr->simResponse = NULL;

    return ril_error;
}

int RmcCommSimRequestHandler::checkRetryFCI(int sw1, int sw2) {
    int retry = 0;
    if (sw1 != 0x61 && sw1 != 0x91 && sw1 != 0x9F) {
        retry = 1;
    }

    if ((sw1 == 0x63 && sw2 == 0x10) || (sw1 == 0x92 && sw2 == 0x40)
            || (sw1 == 0x90 && sw2 == 0x00)) {
        retry = 0;
    }
    logD(mTag, "checkRetryFCI, sw1 %d sw2 %d retry %d", sw1, sw2, retry);
    return retry;
}

int RmcCommSimRequestHandler::selectAid(RIL_SIM_IO_Response *sr, int *len, int channel,
        int p2, char* pAid) {
    sp<RfxAtResponse> p_response;
    String8 cmd("");
    int err, ril_error = RIL_E_SIM_ERR;
    RfxAtLine *line = NULL;
    char *rData = NULL;
    // Parameters
    char *aid = pAid;
    int length = (10 + strlen(aid));
    int cla = ((channel > 3)? 0x40|(channel-4) : channel);
    int ins = 0xA4;
    int p1 = 0x04;
    int mP2 = p2;
    int p3 = (strlen(aid)/2);
    bool retry = false;
    int cmeError = CME_SUCCESS;

redo:
    // Reset pointer
    *len = 0;
    rData = NULL;

    // Reset the response in the sr
    if (sr->simResponse != NULL) {
        free(sr->simResponse);
        sr->simResponse = NULL;
    }

    if (aid != NULL) {
        if(ins == 0xA4 && mP2==0x04) {
            cmd.append(String8::format("AT+CGLA=%d,%d,\"%02x%02x%02x%02x%02x%s00\"",
                    channel, length+2, cla, ins, p1, mP2, p3, aid));
        } else {
            cmd.append(String8::format("AT+CGLA=%d,%d,\"%02x%02x%02x%02x%02x%s\"",
                    channel, length, cla, ins, p1, mP2, p3, aid));
        }
    } else {
        if(ins == 0xA4 && mP2==0x04) {
            cmd.append(String8::format("AT+CGLA=%d,%d,\"%02x%02x%02x%02x%02x00\"",
                    channel, length+2, cla, ins, p1, mP2, p3));
        } else {
            cmd.append(String8::format("AT+CGLA=%d,%d,\"%02x%02x%02x%02x%02x\"",
                    channel, length, cla, ins, p1, mP2, p3));
        }
    }
    logD(mTag, "selectAid, cmd: %s", cmd.string());

    p_response = atSendCommandSingleline(cmd, "+CGLA:");
    err = p_response->getError();

    if (err < 0 || p_response->getSuccess() == 0) {
        logE(mTag, "Fail to open channel");
        if (p_response->getFinalResponse() != NULL) {
            if (!strcmp(p_response->getFinalResponse()->getLine(), "+CME ERROR: MEMORY FULL")) {
                ril_error = RIL_E_MISSING_RESOURCE;
            } else if (!strcmp(p_response->getFinalResponse()->getLine(), "+CME ERROR: NOT FOUND")) {
                ril_error = RIL_E_NO_SUCH_ELEMENT;
            } else {
                cmeError = p_response->atGetCmeError();
                logE(mTag, "openChannel: cme_ERROR: %d", cmeError);
                switch(cmeError) {
                    // GSMA NFC: IO Error if SIM has no response.
                    case CME_UNKNOWN:
                        ril_error = RIL_E_OEM_ERROR_1;
                        break;
                    default:
                        break;
                }
            }
        }
        goto error;
    }

    line = p_response->getIntermediates();
    line->atTokStart(&err);
    if (err < 0) goto error;
    (*len) = line->atTokNextint(&err);
    if (err < 0) goto error;
    rData = line->atTokNextstr(&err);
    if (err < 0) goto error;

    sscanf(&(rData[(*len) - 4]), "%02x%02x", &(sr->sw1), &(sr->sw2));
    rData[(*len) - 4] = '\0';
    // Remember to free it!
    asprintf(&sr->simResponse, "%s", rData);

    p_response = NULL;
    cmd.clear();

    if(sr->sw1 == 0x61) { // GET RESPONSE setting p3 = sr.sw2
        // GET RESPONSE for selecting AID if T=0
        // AT+CGLA=<sessionid>,<length>,<command>
        // <length> = 10
        // <command> = 0X C0 00 00 sr.sw2
        // X = channel
        length = 10;
        ins = 0xC0;
        p1 = 0x00;
        mP2 = 0x00;
        p3 = sr->sw2;
        aid = NULL;
        goto redo;
    } else if(sr->sw1 == 0x6C) { // resend previous command header setting p3 = sr.sw2
        p3 = sr->sw2;
        goto redo;
    } else if (sr->sw1 != 0x90 && sr->sw1 != 0x91) { // wrong sw1, sw2
        if ((sr->sw1 == 0x6A && sr->sw2 == 0x82) ||
                (sr->sw1 == 0x6A && sr->sw2 == 0x81) ||
                (sr->sw1 == 0x69 && sr->sw2 == 0x85) ||
                (sr->sw1 == 0x69 && sr->sw2 == 0x99)) {
            ril_error = RIL_E_NO_SUCH_ELEMENT;
        } else if ((sr->sw1 == 0x6A && sr->sw2 == 0x84) ||
                   (sr->sw1 == 0x68 && sr->sw2 == 0x81)) {
            logE(mTag, "Not enough memory space in the file");
            ril_error = RIL_E_MISSING_RESOURCE;
        }
        if (ins == 0xA4 && aid != NULL && (mP2 == 0x04) && !retry) {
            // Retry only for "Select AID"
            retry = true;
            if (checkRetryFCI(sr->sw1, sr->sw2) == 1) {
                mP2 = 0;
                goto redo;
            }
        }
        // GSMA NFC test: We should treat warning code 0x62 or 0x63 as
        // success.
        if (sr->sw1 == 0x62 || sr->sw1 == 0x63) {
            logI(mTag, "0x62 || 0x63 warning code.");
            ril_error = RIL_E_SUCCESS;
        } else {
            return ril_error;
        }
    } else {
        ril_error = RIL_E_SUCCESS;
    }

    return ril_error;
error:
    sr->sw1 = 0x6f;
    sr->sw2 = 0x00;
    sr->simResponse = NULL;

    return ril_error;
}

// Hexa To Int
unsigned int RmcCommSimRequestHandler::htoi(char* szHex) {
    unsigned int hex = 0;
    int nibble;
    while (*szHex) {
        hex <<= 4;

        if (*szHex >= '0' && *szHex <= '9') {
            nibble = *szHex - '0';
        } else if (*szHex >= 'a' && *szHex <= 'f') {
            nibble = *szHex - 'a' + 10;
        } else if (*szHex >= 'A' && *szHex <= 'F') {
            nibble = *szHex - 'A' + 10;
        } else {
            nibble = 0;
        }

        hex |= nibble;

        szHex++;
    }

    return hex;
}

void RmcCommSimRequestHandler::handleSimOpenChannel(const sp < RfxMclMessage > & msg) {
    sp<RfxAtResponse> p_response;
    sp<RfxMclMessage> response;
    RIL_SIM_IO_Response sr;
    int ril_error = RIL_E_GENERIC_FAILURE, err = 0;
    int channel = 0;
    int len, i = 0;
    int *finalRsp = NULL;
    char *pAid = NULL;
    String8 cmd("");
    int cmeError = CME_SUCCESS;
    RIL_OpenChannelParams *openChannelParams = NULL;
    int p2 = 0x00;

    openChannelParams = (RIL_OpenChannelParams *)(msg->getData()->getData());
    if (openChannelParams != NULL) {
        pAid = openChannelParams->aidPtr;
        if (openChannelParams->p2 > 0) {
            p2 = openChannelParams->p2;
        }
    }

    if (NULL != openChannelParams && NULL != openChannelParams->aidPtr) {
        logD(mTag, "handleSimOpenChannel - pAid = %s, p2 = %d", pAid, p2);
    } else {
        logD(mTag, "handleSimOpenChannel - pAid null, p2 = %d", p2);
    }

    // If p2 is invalid as TS 102 221 Table 11.2 defined.
    if ((pAid == NULL) && (p2 != 0) && ((p2 & 0x80) > 0 || ((p2 & 0x40) > 0 && (p2 & 0x20) > 0)
            || ((p2 & 0x40) == 0 && (p2 & 0x20) > 0) || (p2 & 0x10) > 0 || (p2 & 0x04) == 0)) {
        logI(mTag, "handleSimOpenChannel, invalid p2");
        sr.sw1 = 0xff;
        sr.sw2 = 0xff;
        sr.simResponse = NULL;
        ril_error = RIL_E_SIM_ERR;
        goto error;
    }

    // Open channel
    ril_error = openChannel(msg, &sr, &len);

    // if sw1 == sw2 == 0xff, it means that open logical channel fail
    if(ril_error == RIL_E_SUCCESS) {
        // Support Extended Channel - 4 to 19 (0x40 ~ 0x4F)
        if (sr.simResponse != NULL) {
            channel = htoi(sr.simResponse);
        }
        logD(mTag, "handleSimOpenChannel - channel = %x", channel);
        if(channel < 1 || channel > 19) {
            sr.sw1 = 0xff;
            sr.sw2 = 0xff;
            ril_error = RIL_E_SIM_ERR;
            goto error;
        }
    } else if (ril_error == RIL_E_NO_SUCH_ELEMENT || ril_error == RIL_E_MISSING_RESOURCE
            || ril_error == RIL_E_OEM_ERROR_1) {
        goto error;
    } else {
        sr.sw1 = 0xff;
        sr.sw2 = 0xff;
        goto error;
    }

    // Select AID
    if (sr.simResponse != NULL) {
        free(sr.simResponse);
        sr.simResponse = NULL;
    }

    if (pAid != NULL) {
        memset(&sr, 0, sizeof(RIL_SIM_IO_Response));
        ril_error = selectAid(&sr, &len, channel, p2, pAid);
    } else {
        logI(mTag, "handleSimOpenChannel, empty AID");
        ril_error = RIL_E_SUCCESS;
    }

    if (ril_error != RIL_E_SUCCESS) {
        logE(mTag, "handleSimOpenChannel: fail to select AID, and then close logical channel %d",
                channel);
        goto error_select_aid;
    }

    // Open channel successfully
    if (sr.simResponse != NULL && strlen(sr.simResponse) > 0) {
        finalRsp = (int*)calloc(1, sizeof(int) * ((len / 2) + 3));
        if (NULL != finalRsp) {
            for(i = 0; i < (len / 2 - 2); i++) {
                sscanf(&(sr.simResponse[i * 2]), "%02x", &finalRsp[i + 1]);
            }
        } else {
            logE(mTag, "handleSimOpenChannel, calloc fail.");
            finalRsp = (int*)calloc(1, sizeof(int) * 3);
            RFX_ASSERT(finalRsp != NULL);
        }
    } else {
        logI(mTag, "handleSimOpenChannel, simResponse is null.");
        finalRsp = (int*)calloc(1, sizeof(int) * 3);
        RFX_ASSERT(finalRsp != NULL);
    }
    finalRsp[0] = channel;
    finalRsp[i + 1] = sr.sw1;
    finalRsp[i + 2] = sr.sw2;
    logI(mTag, "handleSimOpenChannel, channel %d sw1 %x, sw2 %x, sr.simresponse %s, i ",
        finalRsp[0], finalRsp[i + 1], finalRsp[i + 2], sr.simResponse, i);

    response = RfxMclMessage::obtainResponse(msg->getId(), (RIL_Errno)ril_error,
            RfxIntsData((void*)finalRsp, (i + 3)*sizeof(int)), msg, false);

    responseToTelCore(response);

    if (sr.simResponse != NULL) {
        free(sr.simResponse);
        sr.simResponse = NULL;
    }
    if (finalRsp != NULL) {
        free(finalRsp);
    }
    return;

error_select_aid:
    // Close logical Channel if selecting AID is failed
    // AT+CGLA=<sessionid>,<length>,<command>
    // <command> = 00 70 80 0X
    // X = channel
    logI(mTag, "handleSimOpenChannel: close logical channel %d due to fail to select AID",
            channel);
    cmd.append(String8::format("AT+CGLA=0,%d,\"%02x%02x%02x%02x\"",
                    8, 0x00, 0x70, 0x80, channel));
    p_response = atSendCommandSingleline(cmd, "+CGLA:");
    if (p_response == NULL) {
        goto error;
    }
    err = p_response->getError();
    if (err < 0 || p_response->getSuccess() == 0) {
        logE(mTag, "handleSimOpenChannel: Close logical Channel failed");
        err = RIL_E_GENERIC_FAILURE;
        cmeError = p_response->atGetCmeError();
        logE(mTag, "err select aid: cme_ERROR: %d", cmeError);
        switch(cmeError) {
            // GSMA NFC: IO Error if SIM has no response.
            case CME_UNKNOWN:
                ril_error = RIL_E_OEM_ERROR_1;
                break;
            default:
                break;
        }
    } else if (p_response->getSuccess() > 0) {
        channel = 0;
    }
    goto error;

error:
    logE(mTag, "handleSimOpenChannel, error %d, sw1 %x, sw2 %x, sr.simresponse %s",
        ril_error, sr.sw1, sr.sw2, sr.simResponse);
    if (sr.simResponse != NULL && strlen(sr.simResponse) > 0) {
        finalRsp = (int*)calloc(1, sizeof(int) * ((len / 2) + 3));
        if (NULL != finalRsp) {
            for(i = 0; i < (len / 2 - 2); i++) {
                sscanf(&(sr.simResponse[i * 2]), "%02x", &finalRsp[i + 1]);
            }
        } else {
            logE(mTag, "handleSimOpenChannel, calloc fail.");
            finalRsp = (int*)calloc(1, sizeof(int) * 3);
            RFX_ASSERT(finalRsp != NULL);
        }
    } else {
        finalRsp = (int*)calloc(1, sizeof(int) * 3);
        RFX_ASSERT(finalRsp != NULL);
    }
    finalRsp[0] = channel;
    finalRsp[i + 1] = sr.sw1;
    finalRsp[i + 2] = sr.sw2;

    response = RfxMclMessage::obtainResponse(msg->getId(), (RIL_Errno)ril_error,
            RfxIntsData((void*)finalRsp, (i + 3)*sizeof(int)), msg, false);

    responseToTelCore(response);
    if (sr.simResponse != NULL) {
        free(sr.simResponse);
        sr.simResponse = NULL;
    }
    if (finalRsp) {
        free(finalRsp);
    }
}
void RmcCommSimRequestHandler::handleSimCloseChannel(const sp < RfxMclMessage > & msg) {
    sp<RfxAtResponse> p_response;
    sp<RfxMclMessage> response;
    int err;
    String8 cmd("");
    int* channel = (int*)(msg->getData()->getData());
    int cmeError = CME_UNKNOWN;

    if (channel == NULL || *channel == 0) {
        logE(mTag, "close channel 0 is not allowed.");
        err = RIL_E_INVALID_ARGUMENTS;
        goto error;
    }
    cmd.append(String8::format("AT+CCHC=%d", (*channel)));
    p_response = atSendCommand(cmd);
    err = p_response->getError();
    if (err < 0 || p_response->getSuccess() == 0) {
        err = RIL_E_GENERIC_FAILURE;
        cmeError = p_response->atGetCmeError();
        logE(mTag, "close channel: cme_ERROR: %d", cmeError);
        switch(cmeError) {
            // GSMA NFC: IO Error if SIM has no response.
            case CME_UNKNOWN:
                err = RIL_E_OEM_ERROR_1;
                break;
            default:
                break;
        }
        goto error;
    }

    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxVoidData(), msg, false);

    responseToTelCore(response);
    return;
error:
    response = RfxMclMessage::obtainResponse(msg->getId(), (RIL_Errno)err,
            RfxVoidData(), msg, false);

    responseToTelCore(response);
}

void RmcCommSimRequestHandler::handleSimTransmitBasic(const sp < RfxMclMessage > & msg) {
    sp<RfxAtResponse> p_response;
    sp<RfxMclMessage> response;
    RIL_SIM_IO_Response sr;
    int err;
    RIL_Errno ril_error = RIL_E_SIM_ERR;
    String8 cmd("");
    RIL_SIM_APDU *p_args;
    RfxAtLine *line = NULL;
    int len;
    char sim_extended_format_prop[RFX_PROPERTY_VALUE_MAX] = {0};
    String8 prop("vendor.gsm.sim.extended.format");
    prop.append(String8::format("%d", (m_slot_id+1)));

    rfx_property_get(prop.string(), sim_extended_format_prop, "0");
    logI(mTag, "handleSimTransmitBasic sim_extended_format_prop: %d",
            atoi(sim_extended_format_prop));
    if (!strncmp(sim_extended_format_prop, "1", 1)) {
        handleSimTransmitWithExtendedAPDU(msg, true);
        return;
    }

    memset(&sr, 0, sizeof(sr));

    p_args = (RIL_SIM_APDU *)(msg->getData()->getData());

    if ((p_args->data == NULL) || (strlen(p_args->data) == 0)) {
        logD(mTag, "handleSimTransmitBasic p3 = %d", p_args->p3);

        if (p_args->p3 < 0) {
            cmd.append(String8::format("AT+CGLA=0,%d,\"%02x%02x%02x%02x\"",
                    8, p_args->cla, p_args->instruction,
                    p_args->p1, p_args->p2));
        } else {
            cmd.append(String8::format("AT+CGLA=0,%d,\"%02x%02x%02x%02x%02x\"",
                    10, p_args->cla, p_args->instruction,
                    p_args->p1, p_args->p2, p_args->p3));
        }
    } else {
        cmd.append(String8::format("AT+CGLA=0,%d,\"%02x%02x%02x%02x%02x%s\"",
                (unsigned int)(10 + strlen(p_args->data)), p_args->cla, p_args->instruction,
                p_args->p1, p_args->p2, p_args->p3,
                p_args->data));
    }
    p_response = atSendCommandSingleline(cmd, "+CGLA:");
    err = p_response->getError();

    if (err < 0 || p_response->getSuccess() == 0) {
        ril_error = RIL_E_GENERIC_FAILURE;
        goto error;
    }

    line = p_response->getIntermediates();
    line->atTokStart(&err);
    if (err < 0) goto error;

    len = line->atTokNextint(&err);
    if (err < 0) goto error;

    sr.simResponse = line->atTokNextstr(&err);
    if (err < 0) goto error;

    sscanf(&(sr.simResponse[len - 4]), "%02x%02x", &(sr.sw1), &(sr.sw2));
    sr.simResponse[len - 4] = '\0';
    logD(mTag, "handleSimTransmitBasic len = %d %02x, %02x", len, sr.sw1, sr.sw2);

    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxSimIoRspData((void*)&sr, sizeof(sr)), msg, false);

    responseToTelCore(response);
    return;

error:
    response = RfxMclMessage::obtainResponse(msg->getId(), ril_error,
            RfxSimIoRspData(NULL, 0), msg, false);

    responseToTelCore(response);
}

void RmcCommSimRequestHandler::handleDetectSim(const sp < RfxMclMessage > & msg) {
    char* urc = (char *) msg->getData()->getData();
    sp<RfxAtResponse> p_response = NULL;
    int err;
    RfxAtLine *line;
    int cardPresent = 0;
    int cmeError;
    char *cpinResult;

    logD("detectSim: entering, urc:%s", urc);

    do {
        // TODO: wait for radio manager ready
        //if (getRadioState(rid) == RADIO_STATE_UNAVAILABLE) {
        //    cardPresent = 1;
        //    break;
        //}

        p_response = atSendCommandSingleline("AT+CPIN?", "+CPIN:");
        err = p_response->getError();
        if (err != 0) {
            logE(mTag, "detectSim: err: %d", err);
            //if (err == AT_ERROR_INVALID_THREAD) {
            //    cardPresent = 1;
            //} else {
                cardPresent = 0;
            //}
            break;
        }
        if (p_response->getSuccess() == 0) {
            cmeError = p_response->atGetCmeError();
            switch (cmeError) {
                case CME_SIM_BUSY: // try to do again until more than 20 times
                cardPresent = 14; // SIM busy, framework needs to query again
                    break;
                case CME_SIM_FAILURE:
                case CME_SIM_NOT_INSERTED:
                    cardPresent = 0;
                    break;
                case CME_SIM_WRONG:
                    cardPresent = 1;
                    break;
                default:
                    cardPresent = 1; // NOT_READY
                    break;
            }
        } else {
            logD(mTag, "detectSim: success");
            line = p_response->getIntermediates();
            line->atTokStart(&err);
            if (err < 0) {
                logD(mTag, "detectSim: atTokStart: err: %d", err);
                cardPresent = 1;
                break;
            }
            cpinResult = line->atTokNextstr(&err);
            if (err < 0) {
                logD(mTag, "detectSim: atTokNextstr: err: %d", err);
                cardPresent = 1;
                break;
            }
            if (strcmp(cpinResult, "SIM PIN") && strcmp(cpinResult, "SIM PUK")
                    && strcmp(cpinResult, "PH-NET PIN") && strcmp(cpinResult, "PH-NET PUK")
                    && strcmp(cpinResult, "PH-NETSUB PIN") && strcmp(cpinResult, "PH-NETSUB PUK")
                    && strcmp(cpinResult, "PH-SP PIN") && strcmp(cpinResult, "PH-SP PUK")
                    && strcmp(cpinResult, "PH-CORP PIN") && strcmp(cpinResult, "PH-CORP PUK")
                    && strcmp(cpinResult, "PH-FSIM PIN") && strcmp(cpinResult, "PH-FSIM PUK")
                    && strcmp(cpinResult, "READY") && strcmp(cpinResult, "SIM PIN-DEFER")) {
                logD(mTag, "detectSim: out of strcmp: %s", cpinResult);
                cardPresent = 0;
            } else {
                cardPresent = 1;
            }
            break;
        }

    } while(0);
    //RLOGD("detectSim before release_wake_lock");
    mtk_release_wake_lock("sim_hot_plug");
    //RLOGD("detectSim after release_wake_lock");
    int cardType = getMclStatusManager()->getIntValue(RFX_STATUS_KEY_CARD_TYPE);

    switch (cardPresent) {
        case 1:
            /* Card inserted */
            logD(mTag, "Ready to check EUSIM (%d) in the case of event plug in", cardType);
            if (cardType & RFX_CARD_TYPE_SIM || cardType & RFX_CARD_TYPE_USIM) {
                logD(mTag, "To notify RFX_MSG_URC_SIM_PLUG_IN");
                if (strStartsWith(urc, "+ESIMS: 1,9")) {
                    //RIL_UNSOL_RESPONSE(RIL_UNSOL_VIRTUAL_SIM_ON,
                    //        &sim_inserted_status, sizeof(int), rid);
                } else if (strStartsWith(urc, "+ESIMS: 1,12")) {
                    //notifyBtSapStatusInd(
                    //        RIL_SIM_SAP_STATUS_IND_Status_RIL_SIM_STATUS_CARD_INSERTED, rid);
                } else if (strStartsWith(urc, "+ESIMS: 1,14")) {
                    //notifyBtSapStatusInd(
                    //        RIL_SIM_SAP_STATUS_IND_Status_RIL_SIM_STATUS_RECOVERED, rid);
                }

                // External SIM [Start]
                if ((isCommontSlotSupport() == true)
                        && (RmcVsimRequestHandler::getVsimPlugInOutEvent(m_slot_id) ==
                        VSIM_TRIGGER_PLUG_IN)) {
                    logD(mTag, "vsim trigger plug in on common slot project.");
                    RmcVsimRequestHandler::setVsimPlugInOutEvent(m_slot_id, VSIM_TRIGGER_RESET);
                } else if ((isCommontSlotSupport() == true) && RfxRilUtils::isVsimEnabled()) {
                    logD(mTag, "Ignore plug in event during vsim enabled on common slot project.");
                } else {
                // External SIM [End]
                    sp<RfxMclMessage> unsol = RfxMclMessage::obtainUrc(RFX_MSG_URC_SIM_PLUG_IN,
                            m_slot_id, RfxVoidData());
                    responseToTelCore(unsol);
                }
            } else if (cardType == -1 || cardType == 0) {
                // Wait for +EUSIM
                mtk_acquire_wake_lock("sim_hot_plug");
                sendEvent(RFX_MSG_EVENT_SIM_DETECT_SIM, RfxStringData(urc), RIL_CMD_PROXY_1, m_slot_id);
            }
            break;
        case 0:
        {
            sp<RfxMclMessage> unsol = NULL;
            String8 iccId(PROPERTY_ICCID_PREIFX);
            logD(mTag, "Event plug in was happened, but there is no SIM inserted actually.(%d)", cardType);
            if (cardType != 0) {
                logE(mTag, "It should not happen here. cardtype != 0.");
            }
            if (isCommontSlotSupport()) {
                logI(mTag, "notify RFX_MSG_URC_SIM_COMMON_SLOT_NO_CHANGED");
                bool aospEnabled = isEnableUiccApplicationsSupported();
                if ((!aospEnabled && (getMclStatusManager()->getIntValue(
                        RFX_STATUS_KEY_SIM_ONOFF_STATE) != SIM_POWER_STATE_SIM_OFF))
                        || (aospEnabled && (getMclStatusManager()->getIntValue(
                        RFX_STATUS_KEY_AOSP_UICC_APPLICATIONS_ENABLE_STATE)
                        == UICC_APPLICATIONS_ENABLE_STATE_ENABLED))) {
                    iccId.append(String8::format("%d", (m_slot_id + 1)));
                    //rfx_property_set(iccId.string(), "N/A");
                    getMclStatusManager()->setString8Value(RFX_STATUS_KEY_SIM_ICCID, String8("N/A"));
                    sendIccidChanged("N/A");
                }

                // External SIM [Start]
                if (RmcVsimRequestHandler::getVsimPlugInOutEvent(m_slot_id) ==
                        VSIM_TRIGGER_PLUG_IN) {
                    logD(mTag, "vsim trigger no change on common slot project.");
                    RmcVsimRequestHandler::setVsimPlugInOutEvent(m_slot_id, VSIM_TRIGGER_RESET);
                } else if (RfxRilUtils::isVsimEnabled()) {
                    logD(mTag, "Ignore no change event during vsim enabled on common slot project.");
                } else {
                // External SIM [End]
                    unsol = RfxMclMessage::obtainUrc(RFX_MSG_URC_SIM_COMMON_SLOT_NO_CHANGED,
                            m_slot_id, RfxVoidData());
                    responseToTelCore(unsol);
                }
            }
        }
            break;
        case 14:
            logD(mTag, "detect sim and sim busy so try again");
            mtk_acquire_wake_lock("sim_hot_plug");
            sendEvent(RFX_MSG_EVENT_SIM_DETECT_SIM, RfxStringData(urc), RIL_CMD_PROXY_1, m_slot_id,
                -1, -1, 200000000);
            break;
        default:
            logE(mTag, "Event plug in was happened, but CPIN? response");
            break;
    }
    return;
}

void RmcCommSimRequestHandler::handleLocalRequestUsimAuthentication(const sp < RfxMclMessage > & msg) {
    RfxBaseData *rbd = msg->getData();
    const char**  strings = (const char**)rbd->getData();
    sp<RfxAtResponse> p_response = NULL;
    sp<RfxMclMessage> response;
    int err;
    RfxAtLine *line;
    char* auth_rsp;
    String8 cmd("");
    int sw1, sw2;

    logD(mTag, "handleLocalRequestUsimAuthentication str %s %s ", strings[0], strings[1]);
    cmd.append(String8::format("AT+EAUTH=\"%s\",\"%s\"", strings[0], strings[1]));
    p_response = atSendCommandSingleline(cmd, "+EAUTH:");
    err = p_response->getError();
    if (err < 0 || p_response->getSuccess() == 0) {
        logE(mTag, "p_response = %d /n", p_response->atGetCmeError());
        goto error;
    }

    line = p_response->getIntermediates();
    line->atTokStart(&err);
    if (err < 0) {
        goto error;
    }
    sw1 = line->atTokNextint(&err);
    if (err < 0) {
        goto error;
    }
    sw2 = line->atTokNextint(&err);
    if (err < 0) {
        goto error;
    }

    if(sw1 == 0x90 && sw2 == 0x00 && line->atTokHasmore()){
        auth_rsp = line->atTokNextstr(&err);
        if(err < 0) {
            goto error;
        }
        logD(mTag, "response str %s length is %zu ", auth_rsp, strlen(auth_rsp));
    } else {
        goto error;
    }
    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxStringData((void*)auth_rsp, strlen(auth_rsp)), msg, false);

    responseToTelCore(response);
    return;

error:
    logE(mTag,"localRequestSimAuthentication Fail");
    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_GENERIC_FAILURE,
            RfxStringData(NULL, 0), msg, false);

    responseToTelCore(response);
}

void RmcCommSimRequestHandler::handleLocalRequestSimAuthentication(const sp < RfxMclMessage > & msg) {
    char* param = (char *) msg->getData()->getData();
    sp<RfxAtResponse> p_response = NULL;
    sp<RfxMclMessage> response;
    int err;
    RfxAtLine *line;
    char* auth_rsp;
    String8 cmd("");
    int sw1, sw2;

    cmd.append(String8::format("AT+EAUTH=\"%s\"",param));

    p_response = atSendCommandSingleline(cmd, "+EAUTH:");
    err = p_response->getError();

    if (err < 0 || p_response->getSuccess() == 0) {
        logE(mTag, "p_response = %d /n", p_response->atGetCmeError());
        goto error;
    }

    line = p_response->getIntermediates();
    line->atTokStart(&err);
    if (err < 0) {
        goto error;
    }
    sw1 = line->atTokNextint(&err);
    if (err < 0) {
        goto error;
    }
    sw2 = line->atTokNextint(&err);
    if (err < 0) {
        goto error;
    }

    if(sw1 == 0x90 && sw2 == 0x00 && line->atTokHasmore()){
        auth_rsp = line->atTokNextstr(&err);
        if(err < 0) {
            goto error;
        }
        logD(mTag, "response str %s length is %zu ", auth_rsp, strlen(auth_rsp));
    } else {
        goto error;
    }
    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxStringData((void*)auth_rsp, strlen(auth_rsp)), msg, false);

    responseToTelCore(response);
    return;

error:
    logE(mTag,"localRequestSimAuthentication Fail");
    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_GENERIC_FAILURE,
            RfxStringData(NULL, 0), msg, false);

    responseToTelCore(response);
}
void RmcCommSimRequestHandler::handleEnterNetworkDepersonalization(const sp<RfxMclMessage>& msg) {
    RfxBaseData *rbd = msg->getData();
    const char**  strings = (const char**)rbd->getData();
    sp<RfxAtResponse> p_response = NULL;
    int err = -1;
    String8 cmd("");
    UICC_Status sim_status = getSimStatus();
    RIL_Errno result = RIL_E_INTERNAL_ERR;
    int currSimInsertedState = getMclStatusManager()->getIntValue(RFX_STATUS_KEY_SIM_STATE);
    //[ALPS05001487] return retry count
    int retryCount = -1;
    int cat = 0;

    do {
        if (RFX_SIM_STATE_ABSENT == currSimInsertedState) {
            logE(mTag, "NetworkDepersonalization, sim absent");
            result = RIL_E_SIM_ABSENT;
            break;
        }

        if (UICC_NP == sim_status ||
            UICC_NSP == sim_status ||
            UICC_SP == sim_status ||
            UICC_CP == sim_status ||
            UICC_SIMP == sim_status ||
            UICC_NS_SP == sim_status ||
            UICC_SIM_C == sim_status) {
            cmd.append(String8::format("AT+CPIN=\"%s\"", strings[0]));
            p_response = atSendCommand(cmd.string());
            err = p_response->getError();

            cmd.clear();
            if (p_response->getSuccess() == 0) {
                switch (p_response->atGetCmeError()) {
                    case CME_NETWORK_PERSONALIZATION_PUK_REQUIRED:
                    case CME_INCORRECT_PASSWORD:
                        result = RIL_E_PASSWORD_INCORRECT;
                        break;
                    case CME_NETWORK_SUBSET_PERSONALIZATION_PUK_REQUIRED:
                        if (UICC_NP == sim_status) {
                            result = RIL_E_SUCCESS;
                        } else if (UICC_NSP == sim_status) {
                            result = RIL_E_PASSWORD_INCORRECT;
                        }
                        break;
                    case CME_SERVICE_PROVIDER_PERSONALIZATION_PUK_REQUIRED:
                        if (UICC_NP == sim_status || UICC_NSP == sim_status) {
                            result = RIL_E_SUCCESS;
                        } else if (UICC_SP == sim_status) {
                            result = RIL_E_PASSWORD_INCORRECT;
                        }
                        break;
                    case CME_CORPORATE_PERSONALIZATION_PUK_REQUIRED:
                        if (UICC_NP == sim_status ||
                            UICC_NSP == sim_status ||
                            UICC_SP == sim_status) {
                            result = RIL_E_SUCCESS;
                        } else if (UICC_CP == sim_status) {
                            result = RIL_E_PASSWORD_INCORRECT;
                        }
                        break;
                    case CME_PH_FSIM_PUK_REQUIRED:
                        if (UICC_NP == sim_status ||
                            UICC_NSP == sim_status ||
                            UICC_SP == sim_status ||
                            UICC_CP == sim_status) {
                            result = RIL_E_SUCCESS;
                        } else if (UICC_SIMP == sim_status) {
                            result = RIL_E_PASSWORD_INCORRECT;
                        }
                        break;
                    case CME_LINK_NS_SP_PIN_REQUIRED:
                        if (UICC_NP == sim_status ||
                            UICC_NSP == sim_status ||
                            UICC_SP == sim_status ||
                            UICC_CP == sim_status ||
                            UICC_SIMP == sim_status) {
                            result = RIL_E_SUCCESS;
                        } else if (UICC_NS_SP == sim_status) {
                            result = RIL_E_PASSWORD_INCORRECT;
                        }
                        break;
                    case CME_LINK_SIM_C_PIN_REQUIRED:
                        if (UICC_NP == sim_status ||
                            UICC_NSP == sim_status ||
                            UICC_SP == sim_status ||
                            UICC_CP == sim_status ||
                            UICC_SIMP == sim_status ||
                            UICC_NS_SP == sim_status) {
                            result = RIL_E_SUCCESS;
                        } else if (UICC_SIM_C == sim_status) {
                            result = RIL_E_PASSWORD_INCORRECT;
                        }
                        break;
                    case CME_OPERATION_NOT_ALLOWED_ERR:
                    case CME_OPERATION_NOT_SUPPORTED:
                    case CME_UNKNOWN:
                        logE(mTag, "Unknow error");
                        break;
                    default:
                        logE(mTag, "Not wrong password or not allowed.");
                        result = RIL_E_SUCCESS;
                        break;
                }
            } else {
                result = RIL_E_SUCCESS;
                //setRadioState(RADIO_STATE_SIM_READY,rid);
                sendSimStatusChanged();
            }
        }
        p_response = NULL;
        if (result == RIL_E_SUCCESS) {
            sendSimStatusChanged();
            /// M: ALPS02832079. Dynamic-SBP feature. @{
            //logD(mTag, "SIM NP unlocked! Setup Dynamic-SBP for RIL:%d", rid);
            // TODO: setup DSBP
            //setupDynamicSBP(rid);
            /// @}
            //  setRadioState(RADIO_STATE_SIM_READY,rid);
        }
        //[ALPS05001487] Query retry count
        if (UICC_NP == sim_status) {
            cat = 0;
        } else if (UICC_NSP == sim_status) {
            cat = 1;
        } else if (UICC_SP == sim_status) {
            cat = 2;
        } else if (UICC_CP == sim_status) {
            cat = 3;
        } else if (UICC_SIMP == sim_status) {
            cat = 4;
        }

        retryCount = getPersoRemainRetry(cat, NULL);
        logD(mTag, "handleEnterDepersonalization retryCount = %d", retryCount);
    } while(0);
    sp<RfxMclMessage> response = RfxMclMessage::obtainResponse(msg->getId(), result,
            RfxIntsData((void*)&retryCount, sizeof(retryCount)), msg, false);
    responseToTelCore(response);
}

int RmcCommSimRequestHandler::querySimExtendedFormat() {
    sp<RfxAtResponse> p_response;
    int err, temp_cap = 0;
    String8 cmd("");
    RfxAtLine *line = NULL;
    // char *capability = NULL;
    char cap[RFX_PROPERTY_VALUE_MAX] = {0};
    String8 prop("vendor.gsm.sim.extended.format");
    prop.append(String8::format("%d", (m_slot_id+1)));

    /**
     * Query if the SIM supports extended format APDU
     * AT+EXCGLA?
     * success: +EXCGLA: <support>
     *          0 : SIM does not support extended format.
     *          1 : SIM supports extended format.
     * fail: ERROR
     *
     */

    cmd.append(String8::format("AT+EXCGLA?"));
    p_response = atSendCommandSingleline(cmd, "+EXCGLA:");
    cmd.clear();

    if (p_response == NULL || p_response->getError() < 0) {
        logE(mTag, "querySimExtendedFormat fail");
         goto done;
    }

    switch (p_response->atGetCmeError()) {
        logD(mTag, "querySimExtendedFormat p_response = %d /n", p_response->atGetCmeError());
        case CME_SUCCESS:
            if (p_response->getError() < 0 || 0 == p_response->getSuccess()) {
                goto done;
            } else {
                line = p_response->getIntermediates();

                line->atTokStart(&err);
                if (err < 0) goto done;

                temp_cap = line->atTokNextint(&err);
                if (err < 0) goto done;
            }
            break;
        case CME_UNKNOWN:
            logD(mTag, "querySimExtendedFormat p_response: CME_UNKNOWN");
            break;
        default:
            logE(mTag, "querySimExtendedFormat fail");
    }

done:
    if (temp_cap == 1) {
        rfx_property_set(prop.string(), "1");
    } else {
        rfx_property_set(prop.string(), "0");
    }
    rfx_property_get(prop.string(), cap, "0");
    logI(mTag, "querySimExtendedFormat temp_cap: %d, %s: %d", temp_cap, prop.string(), atoi(cap));
    // asprintf(&capability, "%d", temp_cap);
    // setMSimProperty(m_slot_id, (char*)"vendor.gsm.sim.extended.format", capability);
    // free(capability);

    return temp_cap;
}

int RmcCommSimRequestHandler::queryEcglaCapability() {
    sp<RfxAtResponse> p_response;
    int temp_cap = 0;

    /**
     * Query whether the SIM card supports "AT+ECGLA"
     * AT+ECGLA=?
     * success: +ECGLA: <support>
     *             Support: AT< OK
     *             Not support: AT< +CME ERROR: 100
     * fail: ERROR
     */
    p_response = atSendCommand("AT+ECGLA=?");

    if (p_response == NULL || p_response->getError() < 0) {
        logE(mTag, "queryEcglaCapability fail");
         goto done;
    }

    if (p_response->atGetCmeError() == CME_SUCCESS && p_response->getSuccess() == 1
            && !strncmp(p_response->getFinalResponse()->getLine(), "OK", 2)) {
        temp_cap = 1;
        logD(mTag, "queryEcglaCapability supports AT+ECGLA");
    }

done:
    if (temp_cap == 1) {
        getMclStatusManager()->setBoolValue(RFX_STATUS_KEY_ECGLA_CAPABILITY, true);
    } else {
        getMclStatusManager()->setBoolValue(RFX_STATUS_KEY_ECGLA_CAPABILITY, false);
    }
    logD(mTag, "queryEcglaCapability: %d",
            getMclStatusManager()->getBoolValue(RFX_STATUS_KEY_ECGLA_CAPABILITY, false));

    return temp_cap;
}

void RmcCommSimRequestHandler::printReducedLog(const char* tag, char* data) {
    char dataToPrint[8];
    memset(dataToPrint, 0, sizeof(dataToPrint));
    int len = 0;
    if (data == NULL) {
        logD(mTag, "%s dataToPrint is null", tag);
    } else {
        len = strlen(data);
        if (len > 6) {
            strncpy(dataToPrint, data, 6);
        } else {
            strcpy(dataToPrint, data);
        }
    }
    logD(mTag, "%s dataToPrint=%s***, dataLength=%d", tag, dataToPrint, len);
}

#define MAX_FULL_DATA_LEN 800
#define MAX_CMD_DATA_LEN MAX_FULL_DATA_LEN - 10

void RmcCommSimRequestHandler::handleSimTransmitWithExtendedAPDU(const sp < RfxMclMessage > & msg,
        bool isBasicChannel) {
    sp<RfxAtResponse> p_response;
    sp<RfxMclMessage> response;
    RIL_SIM_IO_Response sr;
    int err;
    RIL_Errno ril_error = RIL_E_SIM_ERR;
    String8 cmd("");
    RIL_SIM_APDU *p_args = (RIL_SIM_APDU *)(msg->getData()->getData());
    RfxAtLine *line = NULL;
    int data_len = 0, remain_data_len = 0, data_offset = 0;
    int temp_data_len = 0, temp_cmd_data_len = 0;
    int rsp_offset = 0, rsp_total_len = 0, rsp_current_len = 0;
    char* temp_data = NULL;
    char* temp_rsp_data = NULL;

    logI(mTag, "handleSimTransmitWithExtendedAPDU session:%d, cla:%d, ins:%d, p1:%d, p2:%d, p3:%d",
            p_args->sessionid, p_args->cla, p_args->instruction, p_args->p1, p_args->p2,
            p_args->p3);

    memset(&sr, 0, sizeof(sr));
    if (isBasicChannel == true) {
        p_args->sessionid = 0;
    } else {
        // Set class byte according TS 102.221
        p_args->cla = setChannelToClassByte(p_args->cla, p_args->sessionid);
    }

    // +EXCGLA=<offset>,<sessionid>,<total_length>,<current_length>,<current_command_data>
    // +EXCGLA: <offset>,<total_length>,<current_length>,<current_response_data>
    if ((p_args->data == NULL) || (strlen(p_args->data) == 0)) {
        if (p_args->p3 < 0) {
            cmd.append(String8::format("AT+EXCGLA=%d,%d,%d,%d,\"%02x%02x%02x%02x\"",
                    data_offset, p_args->sessionid, 8, 8,
                    p_args->cla, p_args->instruction,
                    p_args->p1, p_args->p2));
        } else {
            cmd.append(String8::format("AT+EXCGLA=%d,%d,%d,%d,\"%02x%02x%02x%02x%02x\"",
                    data_offset, p_args->sessionid, 10, 10,
                    p_args->cla, p_args->instruction,
                    p_args->p1, p_args->p2, p_args->p3));
        }

        p_response = atSendCommandMultiline(cmd, "+EXCGLA:");
        err = p_response->getError();
        cmd.clear();
        if (err < 0 || p_response->getSuccess() == 0) {
            ril_error = RIL_E_GENERIC_FAILURE;
            goto error;
        }
    } else {
        // Send cmd with data.
        logI(mTag, "handleSimTransmitWithExtendedAPDU data = %s ", p_args->data);
        data_len = strlen(p_args->data);
        remain_data_len = data_len;

        do {
            logI(mTag, "data_offset = %d, remain_data_len = %d", data_offset, remain_data_len);
            if (data_offset == 0) {
                if (remain_data_len > MAX_CMD_DATA_LEN) {
                    temp_data_len = MAX_CMD_DATA_LEN;
                    temp_cmd_data_len = MAX_FULL_DATA_LEN;
                } else {
                    temp_data_len = remain_data_len;
                    temp_cmd_data_len = 10 + temp_data_len;
                }
            } else {
                if (remain_data_len > MAX_FULL_DATA_LEN) {
                    temp_data_len = MAX_FULL_DATA_LEN;
                    temp_cmd_data_len = MAX_FULL_DATA_LEN;
                } else {
                    temp_data_len = remain_data_len;
                    temp_cmd_data_len = temp_data_len;
                }
            }
            logI(mTag, "temp_data_len = %d, temp_cmd_data_len = %d", temp_data_len,
                    temp_cmd_data_len);

            temp_data = (char*)calloc(1, (sizeof(char)*(temp_data_len + 1)));
            if (temp_data == NULL) {
                logE(mTag, "handleSimTransmitWithExtendedAPDU calloc temp_data error!");
                goto error;
            }
            strncpy(temp_data, p_args->data + data_offset, temp_data_len);
            temp_data[temp_data_len] = '\0';
            logI(mTag, "strlen = %zu str = %s", strlen(temp_data), temp_data);

            if (data_offset == 0) {
                cmd.append(String8::format("AT+EXCGLA=%d,%d,%d,%d,\"%02x%02x%02x%02x%02x%s\"",
                        data_offset, p_args->sessionid, data_len + 10, temp_cmd_data_len,
                        p_args->cla, p_args->instruction,
                        p_args->p1, p_args->p2, p_args->p3,
                        temp_data));
            } else {
                cmd.append(String8::format("AT+EXCGLA=%d,%d,%d,%d,\"%s\"",
                        data_offset + 10, p_args->sessionid, data_len + 10, temp_cmd_data_len,
                        temp_data));
            }
            remain_data_len -= temp_data_len;
            data_offset += temp_data_len;
            logI(mTag, "data_offset = %d, remain_data_len = %d", data_offset, remain_data_len);

            if (temp_data != NULL) {
                free(temp_data);
                temp_data = NULL;
            }

             // Need to check intermediates for responses.
            if (remain_data_len <= 0) {
                p_response = atSendCommandMultiline(cmd, "+EXCGLA:");
            } else {
                p_response = atSendCommand(cmd);
            }
            err = p_response->getError();
            cmd.clear();
            if (err < 0 || p_response->getSuccess() == 0) {
                ril_error = RIL_E_GENERIC_FAILURE;
                goto error;
            }
        } while (remain_data_len > 0);
    }

    for (line = p_response->getIntermediates(); line != NULL; line = line->getNext()) {
        line->atTokStart(&err);
        if (err < 0) goto error;

        rsp_offset = line->atTokNextint(&err);
        if (err < 0) goto error;

        rsp_total_len = line->atTokNextint(&err);
        if (err < 0) goto error;

        rsp_current_len += line->atTokNextint(&err);
        if (err < 0) goto error;

        temp_data = line->atTokNextstr(&err);
        if (err < 0) goto error;

        if (NULL == temp_rsp_data) {
            temp_rsp_data = (char*)calloc(1, (sizeof(char)* (rsp_total_len + 1)));
            RFX_ASSERT(temp_rsp_data != NULL);
        }
        logI(mTag, "rsp_offset=%d rsp_total_len=%d rsp_current_len=%d", rsp_offset, rsp_total_len,
                rsp_current_len);

        if (temp_data != NULL) {
            strncpy(temp_rsp_data + rsp_offset, temp_data, strlen(temp_data));
            logI(mTag, "temp_data len=%zu, data=%s", strlen(temp_data), temp_data);
        } else {
            logE(mTag, "Null response data.");
        }

        // The last fragment of the response data.
        if (rsp_total_len == rsp_current_len) {
            temp_rsp_data[rsp_total_len] = '\0';

            sscanf(&(temp_rsp_data[rsp_total_len - 4]), "%02x%02x", &(sr.sw1), &(sr.sw2));
            asprintf(&sr.simResponse, "%s", temp_rsp_data);
            sr.simResponse[rsp_total_len - 4] = '\0';

            logI(mTag, "temp_rsp_data len = %zu, data = %s", strlen(temp_rsp_data), temp_rsp_data);
        }
    }

    free(temp_rsp_data);
    temp_rsp_data = NULL;

    logI(mTag, "handleSimTransmitWithExtendedAPDU len = %d sw1 = %02x, sw2 = %02x data = %s",
            rsp_total_len, sr.sw1, sr.sw2, sr.simResponse);
    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxSimIoRspData((void*)&sr, sizeof(sr)), msg, false);
    responseToTelCore(response);
    if (sr.simResponse != NULL) {
        free(sr.simResponse);
    }
    return;

error:
    response = RfxMclMessage::obtainResponse(msg->getId(), ril_error,
            RfxSimIoRspData(NULL, 0), msg, false);

    responseToTelCore(response);
}

void RmcCommSimRequestHandler::handleEnterDepersonalization(const sp<RfxMclMessage>& msg) {
    String8 cmd("");
    int err = -1;
    RIL_Errno ret = RIL_E_INTERNAL_ERR;
    sp<RfxMclMessage> response;
    sp<RfxAtResponse> p_response = NULL;
    UICC_Status sim_status;
    char** strings = (char**)(msg->getData()->getData());
    char* key = NULL;
    RIL_SimMeLockInfo result;
    //char *value;
    int retryCount = -1;

    memset(&result, 0, sizeof(RIL_SimMeLockInfo));

    do {
        if (strings == NULL || strings[0] == NULL ||
                strings[1] == NULL) {
             ret = RIL_E_INVALID_ARGUMENTS;
             logD(mTag, "handleEnterDepersonalization invalid arguments.");
             break;
        }

        // strings[0]: netpin
        // strings[1]: cat
        key = (strings[0] == NULL) ? (char*)"" : (char*)strings[0];
        unsigned int cat = 0;
        int perso_substate = atoi(strings[1]);
        switch (perso_substate) {
            case 5:
                cat = 3;
                break;
            case 6:
                cat = 2;
                break;
            case 3:
            case 4:
            case 7:
                cat = perso_substate - 3;
                break;
            case 8:
            case 9:
            case 10:
            case 11:
            //case 12: //hw application don't support 12
                 cat = 9;
                 break;
            default:
                 cat = perso_substate - 3 >= 0 ? (perso_substate - 3) : 0;
                 break;

        }

        sim_status = getSimStatus();
        logE(mTag, "handleEnterDepersonalization netpin : ***, cat : %s, status: %d",
                strings[1], sim_status);

        if ((UICC_NP == sim_status && (cat == 0)) ||
                (UICC_NSP == sim_status && (cat == 1))  ||
                (UICC_SP == sim_status && (cat == 2)) ||
                (UICC_CP == sim_status && (cat == 3)) ||
                (UICC_SIMP == sim_status && (cat == 4)) ||
                (cat == 9)) { //actually is UICC_NP_PUK
            if (cat == 9) {
                cmd.append(String8::format("AT+ESMLCK=9,5,\"%s\"", strings[0]));
            } else {
                cmd.append(String8::format("AT+CPIN=\"%s\"", strings[0]));
            }
            p_response = atSendCommand(cmd.string());
            err = p_response->getError();

            cmd.clear();
            if (p_response->getSuccess() == 0) {
                switch (p_response->atGetCmeError()) {
                    case CME_NETWORK_PERSONALIZATION_PUK_REQUIRED:
                    case CME_INCORRECT_PASSWORD:
                        ret = RIL_E_PASSWORD_INCORRECT;
                        break;
                    case CME_NETWORK_SUBSET_PERSONALIZATION_PUK_REQUIRED:
                        if (UICC_NP == sim_status) {
                            ret = RIL_E_SUCCESS;
                        } else if (UICC_NSP == sim_status) {
                            ret = RIL_E_PASSWORD_INCORRECT;
                        }
                        break;
                    case CME_SERVICE_PROVIDER_PERSONALIZATION_PUK_REQUIRED:
                        if (UICC_NP == sim_status || UICC_NSP == sim_status) {
                            ret = RIL_E_SUCCESS;
                        } else if (UICC_SP == sim_status) {
                            ret = RIL_E_PASSWORD_INCORRECT;
                        }
                        break;
                    case CME_CORPORATE_PERSONALIZATION_PUK_REQUIRED:
                        if (UICC_NP == sim_status ||
                            UICC_NSP == sim_status ||
                            UICC_SP == sim_status) {
                            ret = RIL_E_SUCCESS;
                        } else if (UICC_CP == sim_status) {
                            ret = RIL_E_PASSWORD_INCORRECT;
                        }
                        break;
                    case CME_PH_FSIM_PUK_REQUIRED:
                        if (UICC_SIMP == sim_status) {
                            ret = RIL_E_PASSWORD_INCORRECT;
                        } else {
                            ret = RIL_E_SUCCESS;
                        }
                        break;
                    case CME_OPERATION_NOT_ALLOWED_ERR:
                    case CME_OPERATION_NOT_SUPPORTED:
                    case CME_UNKNOWN:
                        logE(mTag, "Unknow error");
                        break;
                    default:
                        logE(mTag, "Not wrong password or not allowed.");
                        ret = RIL_E_SUCCESS;
                        break;
                }
            } else {
                ret = RIL_E_SUCCESS;
                sendSimStatusChanged();
            }
        }

        p_response = NULL;
        // Update card status in error to insure SIM ME lock puk state could be updated.
        // if (ret == RIL_E_SUCCESS) {
            sendSimStatusChanged();
        // }

        // Query retry count
        retryCount = getPersoRemainRetry(cat, &result);

        if (isAOSPPropSupport()) {
            String8 lockCount("gsm.sim");
            lockCount.append((m_slot_id == 0)? ".num.simlock" : String8::format("%d%s", m_slot_id,
                    ".num.simlock"));

            String8 value(String8::format("%d", result.catagory[0].retry_cnt));
            for (int j = 1; j < MAX_SIM_ME_LOCK_CAT_NUM; j++) {
                value.append(",");
                value.append(String8::format("%d", result.catagory[j].retry_cnt));
            }

            rfx_property_set(lockCount, value.string());
            logD(mTag, "handleEnterDepersonalization lockCount: %s, value: %s",
                    lockCount.string(), value.string());
        }

        logD(mTag, "handleEnterDepersonalization retryCount = %d", retryCount);
    } while (0);

    response = RfxMclMessage::obtainResponse(msg->getId(), ret,
            RfxIntsData((void*)&retryCount, sizeof(retryCount)), msg, false);
    responseToTelCore(response);
}

void RmcCommSimRequestHandler::handleSimTransmitChannel(const sp < RfxMclMessage > & msg) {
    sp<RfxAtResponse> p_response;
    sp<RfxMclMessage> response;
    RIL_SIM_IO_Response sr;
    int err;
    RIL_Errno ril_error = RIL_E_SIM_ERR;
    String8 cmd("");
    RIL_SIM_APDU *p_args = (RIL_SIM_APDU *)(msg->getData()->getData());

    if (p_args->instruction == 0xE2 &&
        getMclStatusManager()->getBoolValue(RFX_STATUS_KEY_ECGLA_CAPABILITY, false) &&
        getMclStatusManager()->getBoolValue(RFX_STATUS_KEY_IS_EUICC_CARD, false)) {
        handleEsimTransmitChannel(msg);
        return;
    }

    char sim_extended_format_prop[RFX_PROPERTY_VALUE_MAX] = {0};
    String8 prop("vendor.gsm.sim.extended.format");
    prop.append(String8::format("%d", (m_slot_id+1)));
    rfx_property_get(prop.string(), sim_extended_format_prop, "0");
    logI(mTag, "handleSimTransmitChannel sim_extended_format_prop: %d",
            atoi(sim_extended_format_prop));
    if (!strncmp(sim_extended_format_prop, "1", 1)) {
        handleSimTransmitWithExtendedAPDU(msg, false);
        return;
    }

    RfxAtLine *line = NULL;
    int len;
    memset(&sr, 0, sizeof(sr));
    // Set class byte according TS 102.221
    p_args->cla = setChannelToClassByte(p_args->cla, p_args->sessionid);

    logD(mTag, "handleSimTransmitChannel enter!");
    if ((p_args->data == NULL) || (strlen(p_args->data) == 0)) {
       logD(mTag, "handleSimTransmitChannel p3 = %d", p_args->p3);
       if (p_args->p3 < 0) {
           cmd.append(String8::format("AT+CGLA=%d,%d,\"%02x%02x%02x%02x\"",
                    p_args->sessionid, 8, p_args->cla, p_args->instruction,
                    p_args->p1, p_args->p2));
       } else {
           cmd.append(String8::format("AT+CGLA=%d,%d,\"%02x%02x%02x%02x%02x\"",
                    p_args->sessionid, 10, p_args->cla, p_args->instruction,
                    p_args->p1, p_args->p2, p_args->p3));
       }
    } else {
        cmd.append(String8::format("AT+CGLA=%d,%d,\"%02x%02x%02x%02x%02x%s\"",
                p_args->sessionid,
                (unsigned int)(10 + strlen(p_args->data)), p_args->cla, p_args->instruction,
                p_args->p1, p_args->p2, p_args->p3,
                p_args->data));
    }

    p_response = atSendCommandSingleline(cmd, "+CGLA:");
    err = p_response->getError();
    if (err < 0 || p_response->getSuccess() == 0) {
        ril_error = RIL_E_GENERIC_FAILURE;
        goto error;
    }

    line = p_response->getIntermediates();

    line->atTokStart(&err);
    if (err < 0) goto error;

    len = line->atTokNextint(&err);
    if (err < 0) goto error;

    sr.simResponse = line->atTokNextstr(&err);
    if (err < 0) goto error;

    sscanf(&(sr.simResponse[len - 4]), "%02x%02x", &(sr.sw1), &(sr.sw2));
    sr.simResponse[len - 4] = '\0';
    logD(mTag, "requestSIM_TransmitChannel len = %d %02x, %02x", len, sr.sw1, sr.sw2);

    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxSimIoRspData((void*)&sr, sizeof(sr)), msg, false);

    responseToTelCore(response);
    return;

error:
    response = RfxMclMessage::obtainResponse(msg->getId(), ril_error,
            RfxSimIoRspData(NULL, 0), msg, false);

    responseToTelCore(response);

}

void RmcCommSimRequestHandler::handleEsimTransmitChannel(const sp < RfxMclMessage > & msg) {
    logD(mTag, "handleEsimTransmitChannel enter!");
    sp<RfxAtResponse> p_response;
    sp<RfxMclMessage> response;
    RIL_SIM_IO_Response sr;
    int err;
    RIL_Errno ril_error = RIL_E_SIM_ERR;
    RfxAtLine *p_cur = NULL;
    String8 cmd("");
    RIL_SIM_APDU *p_args = (RIL_SIM_APDU *)(msg->getData()->getData());
    int len;
    char* sw = NULL;
    String8 responseData("");

    memset(&sr, 0, sizeof(sr));
    p_args->cla = setChannelToClassByte(p_args->cla, p_args->sessionid);

    if ((p_args->data == NULL) || (strlen(p_args->data) == 0)) {
        logD(mTag, "handleEsimTransmitChannel p3 = %d", p_args->p3);
        if (p_args->p3 < 0) {
            cmd.append(String8::format("AT+ECGLA=%d,%d,\"%02x%02x%02x%02x\"",
                    p_args->sessionid, 8, p_args->cla, p_args->instruction,
                    p_args->p1, p_args->p2));
        } else {
            cmd.append(String8::format("AT+ECGLA=%d,%d,\"%02x%02x%02x%02x%02x\"",
                    p_args->sessionid, 10, p_args->cla, p_args->instruction,
                    p_args->p1, p_args->p2, p_args->p3));
       }
    } else {
        cmd.append(String8::format("AT+ECGLA=%d,%d,\"%02x%02x%02x%02x%02x%s\"",
                    p_args->sessionid,
                    (unsigned int)(10 + strlen(p_args->data)), p_args->cla, p_args->instruction,
                    p_args->p1, p_args->p2, p_args->p3,
                    p_args->data));
    }
    p_response = atSendCommandMultiline(cmd, "+ECGLA:");
    err = p_response->getError();
    if (err < 0 || p_response->getSuccess() == 0 ||
            p_response->getIntermediates()  == NULL) {
        int cmeError = p_response->atGetCmeError();
        logE(mTag, "AT+ECGLA Fail, cmeError: %d", cmeError);
        goto error;
    }
    for (p_cur = p_response->getIntermediates(); p_cur != NULL; p_cur = p_cur->getNext()) {
        p_cur->atTokStart(&err);
        if (err < 0) goto error;

        len = p_cur->atTokNextint(&err);
        if (err < 0) goto error;

        responseData.append(String8::format("%s",p_cur->atTokNextstr(&err)));
        if (err < 0) goto error;

        if (p_cur->atTokHasmore()) {
            sw = p_cur->atTokNextstr(&err);
            if (err < 0) goto error;
            sscanf(&(sw[0]), "%02x%02x", &(sr.sw1), &(sr.sw2));
            asprintf(&sr.simResponse, "%s", responseData.string());
            logD(mTag, "handleEsimTransmitChannel sr.sw1=%02x, sr.sw2=%02x, simResonse len=%zu",
                    sr.sw1, sr.sw2, strlen(sr.simResponse));
        }
    }
    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxSimIoRspData((void*)&sr, sizeof(sr)), msg, false);
    responseToTelCore(response);
    if (sr.simResponse != NULL) {
        free(sr.simResponse);
    }
    return;
error:
    response = RfxMclMessage::obtainResponse(msg->getId(), ril_error,
            RfxSimIoRspData(NULL, 0), msg, false);
    responseToTelCore(response);
}

/**
 * Returns a copy of the given CLA byte where the channel number bits are
 * set as specified by the given channel number See GlobalPlatform Card
 * Specification 2.2.0.7: 11.1.4 Class Byte Coding.
 *
 * @param cla the CLA byte. Won't be modified
 * @param channelNumber within [0..3] (for first interindustry class byte
 *            coding) or [4..19] (for further interindustry class byte
 *            coding)
 * @return the CLA byte with set channel number bits. The seventh bit
 *         indicating the used coding (first/further interindustry class
 *         byte coding) might be modified
 */
 int RmcCommSimRequestHandler::setChannelToClassByte(int cla, int channelNumber) {
    if (channelNumber < 4) {
        // b7 = 0 indicates the first interindustry class byte coding
        cla = ((cla & 0xBC) | channelNumber);

    } else if (channelNumber < 20) {
        // b7 = 1 indicates the further interindustry class byte coding
        bool isSM = (cla & 0x0C) != 0;
        cla = ((cla & 0xB0) | 0x40 | (channelNumber - 4));
        if (isSM) {
            cla |= 0x20;
        }
    }
    return cla;
}

void RmcCommSimRequestHandler::handleSimGetAtr(const sp < RfxMclMessage > & msg) {
    sp<RfxAtResponse> p_response;
    sp<RfxMclMessage> response;
    int err;
    RIL_Errno ril_error = RIL_E_SIM_ERR;
    char *tmp;
    char *atr;
    RfxAtLine *line;

    p_response = atSendCommandSingleline("AT+ESIMINFO=0", "+ESIMINFO:");
    err = p_response->getError();

    if (err < 0 || p_response->getSuccess() == 0) {
        logE(mTag, "handleSimGetAtr Fail");
        goto error;
    }

    // +ESIMINFO:<mode>, <data> => if<mode>=0,<data>=ATR Hex String
    line = p_response->getIntermediates();
    line->atTokStart(&err);
    if (err < 0) goto error;

    tmp = line->atTokNextstr(&err);
    if(err < 0) goto error;

    atr = line->atTokNextstr(&err);
    if (err < 0) goto error;

    logD(mTag, "handleSimGetAtr strlen of response is %zu", strlen(atr));

    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
                RfxStringData((void*)atr, strlen(atr)), msg, false);

    responseToTelCore(response);
    return;

error:
    logE(mTag, "handleSimGetAtr, fail to parse respnse");
    response = RfxMclMessage::obtainResponse(msg->getId(), ril_error,
                RfxStringData(), msg, false);

    responseToTelCore(response);
}

void RmcCommSimRequestHandler::handleSimGetIccid(const sp < RfxMclMessage > & msg) {
    sp<RfxMclMessage> response;
    RIL_Errno ril_error = RIL_E_SIM_ERR;

    String8 iccid = getMclStatusManager()->getString8Value(RFX_STATUS_KEY_SIM_ICCID);
    if (!iccid.isEmpty()) {
        response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
                RfxStringData((void *)iccid.string(), iccid.length()), msg, false);
    } else {
        response = RfxMclMessage::obtainResponse(msg->getId(), ril_error, RfxStringData(), msg,
                false);
    }

    responseToTelCore(response);
}

void RmcCommSimRequestHandler::handleSecurityOperation(const sp<RfxMclMessage>& msg, UICC_Security_Operation op) {
    RfxBaseData *rbd = msg->getData();
    const char**  strings = (const char**)rbd->getData();
    size_t dataLen = rbd->getDataLength();
    String8 cmd("");
    //String8 aid("");
    int err = 0;
    sp<RfxAtResponse> p_response = NULL;
    int opRetryCount = -1;
    RIL_Errno result = RIL_E_GENERIC_FAILURE;
    RfxIntsData pRspData;
    RfxAtLine *line = NULL;
    int isSimPinEnabled = 0;
    bool bIgnoreCmd = false;
    int i = 0;
    UICC_Status sim_status;
    //int appTypeId = -1;

    do {
        switch (op) {
            case ENTER_PIN1:
            case ENTER_PUK1:
                if (dataLen == 2 * sizeof(char*) ) {
                    cmd.append(String8::format("AT+CPIN=\"%s\"", strings[0]));
                } else if (dataLen == 3 * sizeof(char*)) {
                    cmd.append(String8::format("AT+EPIN1=\"%s\",\"%s\"", strings[0], strings[1]));
                } else {
                    err = -1;
                    break;
                }
                p_response = atSendCommand(cmd.string());
                err = p_response->getError();
                break;
            case ENTER_PIN2:
            case ENTER_PUK2:
                if (dataLen == 2 * sizeof(char*) ) {
                    cmd.append(String8::format("AT+EPIN2=\"%s\"", strings[0]));
                } else if (dataLen == 3 * sizeof(char*) ) {
                    cmd.append(String8::format("AT+EPIN2=\"%s\",\"%s\"", strings[0], strings[1]));
                } else {
                    err = -1;
                    break;
                }
                p_response = atSendCommand(cmd.string());
                err = p_response->getError();
                break;
            case CHANGE_PIN1:
                /* Check if SIM pin has enabled */
                cmd.append(String8::format("AT+CLCK=\"SC\",2"));
                p_response = atSendCommandSingleline(cmd, "+CLCK:");
                //if (dataLen == 3 * sizeof(char*) && strings[2] != NULL) {
                //    aid.append(String8::format("%s", strings[2]));
                //}
                // Get app type id
                //appTypeId = queryAppTypeId(aid);
                //logD(mTag, "appTypeId=%d", appTypeId);
                //cmd.append(String8::format("AT+ECLCK=%d,\"SC\",2", appTypeId));
                //p_response = atSendCommandSingleline(cmd, "+ECLCK:");
                err = p_response->getError();

                if (err < 0) {
                    logE(mTag, "query SIM PIN lock:%d", err);
                    break;
                }

                if (p_response->getSuccess() == 0) {
                    err = -1;
                    break;
                }
                line = p_response->getIntermediates();
                line->atTokStart(&err);

                if (err < 0) {
                    logE(mTag, "query SIM PIN lock, get token error");
                    break;
                }
                isSimPinEnabled = line->atTokNextint(&err);

                if (err < 0) {
                    logE(mTag, "query SIM PIN lock, get result fail");
                    break;
                }

                logE(mTag, "query SIM PIN lock, isSimPinEnabled: %d", isSimPinEnabled);

                if (isSimPinEnabled == 0) {
                    result = RIL_E_REQUEST_NOT_SUPPORTED;
                    err = -1;
                    break;
                }
                // Fall through
                TELEPHONYWARE_FALLTHROUGH;

            case CHANGE_PIN2:
                /*  UI shall handle CHANGE PIN only operated on PIN which is enabled and nonblocking state. */
                if (dataLen == 3 * sizeof(char*)) {
                    if (CHANGE_PIN1 == op) {
                        sim_status = getSimStatus();
                        if (sim_status == UICC_PIN) {
                            op = ENTER_PIN1;
                            /* Solve CR - ALPS00260076 PIN can not be changed by using SS string when PIN is dismissed
                                          Modem does not support multiple AT commands, so input PIN1 first */
                            cmd.clear();
                            cmd.append(String8::format("AT+CPIN=\"%s\"", strings[0]));
                            bIgnoreCmd = true;
                            p_response = atSendCommand(cmd.string());
                            if (p_response->getSuccess() > 0) {
                               bIgnoreCmd = false;
                               cmd.clear();
                               cmd.append(String8::format("AT+CPWD=\"SC\",\"%s\",\"%s\"", strings[0], strings[1]));
                               /* Wait for SIM ready before changing PIN password
                                              Used the same retry scenario with getCardStatus */
                               for (i = 0; i < 30; i++) {
                                   logI(mTag, "Wait for SIM ready, try count:%d", i+1);
                                   sleepMsec(200);
                                   sim_status = getSimStatus();
                                   if (sim_status == UICC_READY) {
                                      logI(mTag, "SIM ready");
                                      break;
                                   }
                               }/* End of for */
                            }
                        } else {
                            cmd.clear();
                            cmd.append(String8::format("AT+CPWD=\"SC\",\"%s\",\"%s\"", strings[0], strings[1]));
                        }
                    } else {
                        cmd.clear();
                        cmd.append(String8::format("AT+CPWD=\"P2\",\"%s\",\"%s\"", strings[0], strings[1]));
                    }
                } else {
                    err = -1;
                    break;
                }
                if (!bIgnoreCmd) {
                    // [mtk02772] p_response should be free before use it, or it will be leakage
                    p_response = atSendCommand(cmd.string());
                    err = p_response->getError();
                }
                break;
            default:
                err = -1;
                break;
        }
        cmd.clear();
        if (err != 0) {
            /* AT runtime error */
            break;
        }

        RmcSimPinPukCount *retryCount = getPinPukRetryCount();

        if (retryCount != NULL) {
            if ((ENTER_PIN1 == op) || (CHANGE_PIN1 == op)) {
                opRetryCount = retryCount->pin1;
            } else if ((ENTER_PIN2 == op) || (CHANGE_PIN2 == op)) {
                opRetryCount = retryCount->pin2;
            } else if (ENTER_PUK1 == op) {
                opRetryCount = retryCount->puk1;
            } else if (ENTER_PUK2 == op) {
                opRetryCount = retryCount->puk2;
            }
            if (retryCount != NULL) {
                free(retryCount);
            }
        }
        logD(mTag, "handleSecurityOperation: op=%d, RetryCount=%d", op, opRetryCount);

        if (p_response->getSuccess() == 0) {
            switch (p_response->atGetCmeError()) {
                case CME_INCORRECT_PASSWORD:
                    result = RIL_E_PASSWORD_INCORRECT;
                    break;
                case CME_SIM_PIN_REQUIRED:
                case CME_SIM_PUK_REQUIRED:
                    result = RIL_E_PASSWORD_INCORRECT;
                    break;
                case CME_SIM_PIN2_REQUIRED:
                    result = RIL_E_SIM_PIN2;
                    break;
                case CME_SIM_PUK2_REQUIRED:
                    result = RIL_E_SIM_PUK2;
                    break;
                case CME_OPERATION_NOT_ALLOWED_ERR:
                    result = RIL_E_REQUEST_NOT_SUPPORTED;
                    break;
                case CME_SIM_FAILURE:
                case CME_UNKNOWN:
                    if ((ENTER_PUK1 == op) || (ENTER_PUK2 == op)) {
                        result = RIL_E_INVALID_SIM_STATE;
                    } else {
                        result = RIL_E_REQUEST_NOT_SUPPORTED;
                    }
                    break;
                default:
                    result = RIL_E_REQUEST_NOT_SUPPORTED;
                    break;
            }
        } else {
            /* Only for FTA mode */
            char property_value[RFX_PROPERTY_VALUE_MAX] = { 0 };
            rfx_property_get(PROPERTY_GSM_GCF_TEST_MODE, property_value, "0");

            if (atoi(property_value) == 2) {
                // 1. Since modem need to init after unlock SIM PIN, we try to query SIM state to check
                //  if modem has complted initialization.
                int count = 0;
                do {
                    sim_status = getSimStatus();
                    if (UICC_BUSY == sim_status) {
                        sleepMsec(200);
                        count++; //to avoid block; if the busy time is too long; need to check modem.
                        if(count == 30) {
                            break;
                        }
                    }
                } while (UICC_BUSY == sim_status);
                String8 aid("");
                if (dataLen == 2 * sizeof(char*) && strings[1] != NULL) {
                    aid.append(String8::format("%s", strings[1]));
                } else if (dataLen == 3 * sizeof(char*) && strings[2] != NULL) {
                    aid.append(String8::format("%s", strings[2]));
                }
                int appTypeId = queryAppTypeId(aid), channelId = 0, intPara = 0;
                cmd.clear();
                cmd.append(String8::format("AT+ESIMAPP=%d,0", appTypeId));

                p_response = atSendCommandSingleline(cmd.string(), "+ESIMAPP:");

                if (p_response != NULL && p_response->getSuccess() > 0) {
                    // Success
                    line = p_response->getIntermediates();
                    line->atTokStart(&err);
                    // application id
                    intPara = line->atTokNextint(&err);
                    // channel id
                    channelId = line->atTokNextint(&err);
                    if (channelId == 255) {
                        logE(mTag, "channel id is 255!");
                        result = RIL_E_SIM_BUSY;
                        break;
                    }
                    cmd.clear();
                    line = NULL;
                } else {
                    logE(mTag, "Fail to query app %d channel", appTypeId);
                    result = RIL_E_GENERIC_FAILURE;
                    break;
                }

                // 2. Check if there is techinal problem in SIM card to support lab test PTCRB 27.16
                //     Read any file to ensure there is no technical problem.
                sleepMsec(200);
                sp<RfxAtResponse> p_responseIccid = NULL;
                cmd.clear();
                cmd.append(String8::format("AT+ECRLA=%d,%d,%d,%d,%d,%d,%d", appTypeId, channelId,
                        0xb2, 0x2fe2, 1, 4, 10));
                p_responseIccid = atSendCommandSingleline(cmd.string(), "+ECRLA:");
                cmd.clear();
                if (p_responseIccid->getError() < 0 || p_responseIccid->getSuccess() == 0) {
                    logE(mTag, "Fail to read EF_ICCID");
                    if (p_responseIccid->atGetCmeError() == CME_SIM_TECHNICAL_PROBLEM) {
                        logE(mTag, "Fail to read EF_ICCID, got CME_SIM_TECHNICAL_PROBLEM.");
                        result = RIL_E_GENERIC_FAILURE;
                        break;
                    }
                } else {
                    logD(mTag, "success to read EF_ICCID");
                    result = RIL_E_SUCCESS;
                }
            } else {
                result = RIL_E_SUCCESS;
            }
        }
        /* release resource for getPINretryCount usage */

        if ((result == RIL_E_SUCCESS)&&((ENTER_PIN1 == op) || (ENTER_PUK1 == op))) {
            if (op == ENTER_PIN1) {
                logD(mTag, "ENTER_PIN1 Success!");
            } else {
                logD(mTag, "ENTER_PUK1 Success!");
            }

            sendSimStatusChanged();
            /// M: ALPS02301695. Dynamic-SBP feature. @{
            //logD(mTag, "PIN unlocked! Setup Dynamic-SBP for RIL:%d", rid);
            // TODO: setup DSBP
            //setupDynamicSBP(rid);
            /// @}
        }
    } while(0);
    cmd.clear();

    sp<RfxMclMessage> response = RfxMclMessage::obtainResponse(msg->getId(), result,
            RfxIntsData((void*)&opRetryCount, sizeof(opRetryCount)), msg, false);

    responseToTelCore(response);
}

void RmcCommSimRequestHandler::setSimInsertedStatus(int slotId, int isInserted) {
    int pivot = 1;
    int pivotSim = slotId;
    int simInsertedStatus = getMclStatusManager()->getIntValue(RFX_STATUS_KEY_SIM_INSERT_STATE);

    if(isInserted == 1) {
        pivotSim = pivot << slotId;
        simInsertedStatus = simInsertedStatus | pivotSim;
    } else {
        pivotSim = pivot << slotId;
        pivotSim = ~pivotSim;
        simInsertedStatus = (simInsertedStatus & pivotSim );
    }
    getMclStatusManager()->setIntValue(RFX_STATUS_KEY_SIM_INSERT_STATE, simInsertedStatus);
}

// BTSAP - Start
void RmcCommSimRequestHandler::decodeBtSapPayload(int msgId, const void *src,
        size_t srclen, void *dst) {
    pb_istream_t stream;
    const pb_field_t *fields = NULL;

    logD(mTag, "[BTSAP] decodeBtSapPayload start (%s), srclen:%zu", idToString(msgId), srclen);
    if (dst == NULL || src == NULL) {
        logE(mTag, "[BTSAP] decodeBtSapPayload, dst or src is NULL!!");
        return;
    }

    switch (msgId) {
        case RFX_MSG_REQUEST_SIM_SAP_CONNECT:
            fields = RIL_SIM_SAP_CONNECT_REQ_fields;
            break;
        case RFX_MSG_REQUEST_SIM_SAP_DISCONNECT:
            fields = RIL_SIM_SAP_DISCONNECT_REQ_fields;
            break;
        case RFX_MSG_REQUEST_SIM_SAP_APDU:
            fields = RIL_SIM_SAP_APDU_REQ_fields;
            break;
        case RFX_MSG_REQUEST_SIM_SAP_TRANSFER_ATR:
            fields = RIL_SIM_SAP_TRANSFER_ATR_REQ_fields;
            break;
        case RFX_MSG_REQUEST_SIM_SAP_POWER:
            fields = RIL_SIM_SAP_POWER_REQ_fields;
            break;
        case RFX_MSG_REQUEST_SIM_SAP_RESET_SIM:
            fields = RIL_SIM_SAP_RESET_SIM_REQ_fields;
            break;
        case RFX_MSG_REQUEST_SIM_SAP_SET_TRANSFER_PROTOCOL:
            fields = RIL_SIM_SAP_SET_TRANSFER_PROTOCOL_REQ_fields;
            break;
        default:
            logE(mTag, "[BTSAP] decodeBtSapPayload, MsgId is mistake!");
            return;
    }

    stream = pb_istream_from_buffer((uint8_t *)src, srclen);
    if (!pb_decode(&stream, fields, dst) ) {
        logE(mTag, "[BTSAP] decodeBtSapPayload, Error decoding protobuf buffer : %s",
                PB_GET_ERROR(&stream));
    } else {
        logD(mTag, "[BTSAP] decodeBtSapPayload, Success!");
    }
}

void RmcCommSimRequestHandler::resetBtSapContext() {
    logD(mTag, "[BTSAP] resetBtSapAtr");
    getMclStatusManager()->setIntValue(RFX_STATUS_KEY_BTSAP_STATUS, BT_SAP_INIT);
    getMclStatusManager()->setIntValue(RFX_STATUS_KEY_BTSAP_CURRENT_PROTOCOL, 0);
    getMclStatusManager()->setIntValue(RFX_STATUS_KEY_BTSAP_SUPPORT_PROTOCOL, 0);
    getMclStatusManager()->setString8Value(RFX_STATUS_KEY_BTSAP_ATR, String8(""));
}

int RmcCommSimRequestHandler::toByte(char c) {
    if (c >= '0' && c <= '9') return (c - '0');
    if (c >= 'A' && c <= 'F') return (c - 'A' + 10);
    if (c >= 'a' && c <= 'f') return (c - 'a' + 10);

    logE(mTag, "toByte Error: %c",c);
    return 0;
}

int RmcCommSimRequestHandler::hexStringToByteArrayEx(unsigned char* hexString,
        int hexStringLen, unsigned char ** byte) {
    int length = hexStringLen/2;
    unsigned char* buffer = (unsigned char*)malloc((length + 1)*sizeof(char));
    RFX_ASSERT(buffer != NULL);
    int i = 0;

    memset(buffer, 0, ((length + 1)*sizeof(char)));
    for (i = 0 ; i < hexStringLen ; i += 2)
    {
        buffer[i / 2] = (unsigned char)((toByte(hexString[i]) << 4) | toByte(hexString[i+1]));
    }

    *byte = buffer;

    return (hexStringLen/2);
}

char* RmcCommSimRequestHandler::convertBtSapIntToHexString(uint8_t *data, size_t datalen) {
    char* output = NULL, *pOut = NULL;
    unsigned int i = 0;

    if (data == NULL || datalen <= 0) {
        return output;
    }

    output = (char*)calloc(1, (sizeof(char)*datalen+1)*2);
    RFX_ASSERT(output != NULL);
    pOut = output;

    for (i = 0; i < datalen; i++) {
        pOut = &output[2*i];
        if (sprintf(pOut, "%02x", data[i]) < 0) {
            logE(mTag, "[BTSAP] convertBtSapIntToHexString, Copy string fail.");
        }
    }

    logD(mTag, "[BTSAP] convert string (%zu, %s)", datalen, output);
    return output;
}

void RmcCommSimRequestHandler::sendBtSapResponseComplete(const sp<RfxMclMessage>& msg,
        RIL_Errno ret, int msgId, void *data) {
    const pb_field_t *fields = NULL;
    size_t encoded_size = 0;
    size_t buffer_size = 0;
    pb_ostream_t ostream;
    bool success = false;
    //ssize_t written_bytes;
    sp<RfxMclMessage> response = NULL;

    logD(mTag, "[BTSAP] sendBtSapResponseComplete, start (%s)", idToString(msgId));

    switch (msgId) {
        case RFX_MSG_REQUEST_SIM_SAP_CONNECT:
            fields = RIL_SIM_SAP_CONNECT_RSP_fields;
            break;
        case RFX_MSG_REQUEST_SIM_SAP_DISCONNECT:
            fields = RIL_SIM_SAP_DISCONNECT_RSP_fields;
            break;
        case RFX_MSG_REQUEST_SIM_SAP_APDU:
            fields = RIL_SIM_SAP_APDU_RSP_fields;
            break;
        case RFX_MSG_REQUEST_SIM_SAP_TRANSFER_ATR:
            fields = RIL_SIM_SAP_TRANSFER_ATR_RSP_fields;
            break;
        case RFX_MSG_REQUEST_SIM_SAP_POWER:
            fields = RIL_SIM_SAP_POWER_RSP_fields;
            break;
        case RFX_MSG_REQUEST_SIM_SAP_RESET_SIM:
            fields = RIL_SIM_SAP_RESET_SIM_RSP_fields;
            break;
        case RFX_MSG_REQUEST_SIM_SAP_SET_TRANSFER_PROTOCOL:
            fields = RIL_SIM_SAP_SET_TRANSFER_PROTOCOL_RSP_fields;
            break;
        case RFX_MSG_REQUEST_SIM_SAP_ERROR_RESP:
            fields = RIL_SIM_SAP_ERROR_RSP_fields;
            break;
        default:
            logE(mTag, "[BTSAP] sendBtSapResponseComplete, MsgId is mistake!");
            return;
    }

    if ((success = pb_get_encoded_size(&encoded_size, fields, data)) &&
            encoded_size <= INT32_MAX) {
        //buffer_size = encoded_size + sizeof(uint32_t);
        buffer_size = encoded_size;
        uint8_t buffer[buffer_size];
        //written_size = htonl((uint32_t) encoded_size);
        ostream = pb_ostream_from_buffer(buffer, buffer_size);
        //pb_write(&ostream, (uint8_t *)&written_size, sizeof(written_size));
        success = pb_encode(&ostream, fields, data);

        if(success) {
            logD(mTag, "[BTSAP] sendBtSapResponseComplete, Size: %zu (0x%zx)", encoded_size,
                    encoded_size);
            // Send response
            //RIL_SAP_onRequestComplete(t, ret, buffer, buffer_size);
            response = RfxMclMessage::obtainSapResponse(msgId, ret,
                    RfxRawData((void*)buffer, buffer_size), msg, false);
            responseToTelCore(response);
        } else {
            logE(mTag, "[BTSAP] sendBtSapResponseComplete, Encode failed!");
        }
    } else {
        logE(mTag, "Not sending response type %d: encoded_size: %zu. encoded size result: %d",
        msgId, encoded_size, success);
    }
}

void RmcCommSimRequestHandler::handleLocalBtSapReset(const sp<RfxMclMessage>& msg) {
    RFX_UNUSED(msg);
    sendBtSapStatusInd(RIL_SIM_SAP_STATUS_IND_Status_RIL_SIM_STATUS_CARD_RESET);
}

void RmcCommSimRequestHandler::handleBtSapConnect(const sp<RfxMclMessage>& msg) {
    RIL_SIM_SAP_CONNECT_REQ *req = NULL;
    RIL_SIM_SAP_CONNECT_RSP rsp;
    sp<RfxAtResponse> p_response;
    int err, type = -1;
    int sysMaxSize = 32767;
    char *pAtr = NULL;
    RfxAtLine* line = NULL;
    RIL_Errno ret = RIL_E_GENERIC_FAILURE;
    RIL_SIM_SAP_STATUS_IND_Status unsolMsg = RIL_SIM_SAP_STATUS_IND_Status_RIL_SIM_STATUS_UNKNOWN_ERROR;
    void* data = msg->getData()->getData();
    int datalen = msg->getData()->getDataLength();

    logD(mTag, "[BTSAP] handleBtSapConnect start");
    req = (RIL_SIM_SAP_CONNECT_REQ*)calloc(1, sizeof(RIL_SIM_SAP_CONNECT_REQ));
    RFX_ASSERT(req != NULL);
    decodeBtSapPayload(RFX_MSG_REQUEST_SIM_SAP_CONNECT, data, datalen, req);

    if (req->max_message_size > sysMaxSize) {
        // Max message size from request > project setting
        rsp.response = RIL_SIM_SAP_CONNECT_RSP_Response_RIL_E_SAP_MSG_SIZE_TOO_LARGE;
        rsp.max_message_size = sysMaxSize;
        rsp.has_max_message_size = TRUE;
        sendBtSapResponseComplete(msg, ret, RFX_MSG_REQUEST_SIM_SAP_CONNECT, &rsp);
        free(req);
        return;
    }

    p_response = atSendCommandSingleline("AT+EBTSAP=0", "+EBTSAP:");
    if (p_response == NULL) {
        rsp.response = RIL_SIM_SAP_CONNECT_RSP_Response_RIL_E_SAP_CONNECT_FAILURE;
        goto format_error;
    }
    err = p_response->getError();

    if (err < 0) {
        rsp.response = RIL_SIM_SAP_CONNECT_RSP_Response_RIL_E_SAP_CONNECT_FAILURE;
        goto format_error;
    }

    if (p_response->getSuccess() == 0) {
        logE(mTag, "[BTSAP] CME ERROR = %d", p_response->atGetCmeError());
        rsp.response = RIL_SIM_SAP_CONNECT_RSP_Response_RIL_E_SAP_CONNECT_FAILURE;
        switch (p_response->atGetCmeError()) {
            case CME_BT_SAP_UNDEFINED:
                ret = RIL_E_REQUEST_NOT_SUPPORTED;
                break;
            case CME_BT_SAP_NOT_ACCESSIBLE:
                ret = RIL_E_SIM_ERR;
                unsolMsg = RIL_SIM_SAP_STATUS_IND_Status_RIL_SIM_STATUS_CARD_NOT_ACCESSIBLE;
                break;
            case CME_BT_SAP_CARD_REMOVED:
            case CME_SIM_NOT_INSERTED:
                ret = RIL_E_SIM_ABSENT;
                unsolMsg = RIL_SIM_SAP_STATUS_IND_Status_RIL_SIM_STATUS_CARD_REMOVED;
                break;
            default:
                break;
        }
        goto format_error;
    } else {
        line = p_response->getIntermediates();
        rsp.response = RIL_SIM_SAP_CONNECT_RSP_Response_RIL_E_SAP_CONNECT_FAILURE;
        if (line == NULL) {
            goto format_error;
        }

        line->atTokStart(&err);
        if (err < 0) goto format_error;

        type = line->atTokNextint(&err);
        if (err < 0) goto format_error;

        getMclStatusManager()->setIntValue(RFX_STATUS_KEY_BTSAP_CURRENT_PROTOCOL, type);

        type = line->atTokNextint(&err);
        if (err < 0) goto  format_error;

        getMclStatusManager()->setIntValue(RFX_STATUS_KEY_BTSAP_SUPPORT_PROTOCOL, type);

        pAtr = line->atTokNextstr(&err);
        if (err < 0) goto  format_error;

        int atrLen = 0;
        if (pAtr != NULL) {
            atrLen = strlen(pAtr);
            getMclStatusManager()->setString8Value(RFX_STATUS_KEY_BTSAP_ATR,
                    String8::format("%s", pAtr));
        }

        logD(mTag, "[BTSAP] requestLocalSapConnect, cur_type: %d, supp_type: %d, size: %d",
                getMclStatusManager()->getIntValue(RFX_STATUS_KEY_BTSAP_CURRENT_PROTOCOL, -1),
                getMclStatusManager()->getIntValue(RFX_STATUS_KEY_BTSAP_SUPPORT_PROTOCOL, -1),
                atrLen);

        ret = RIL_E_SUCCESS;
        // For AOSP BT SAP UT case, to set the flag has_max_message_size as true.
        //rsp.has_max_message_size = false;
        rsp.has_max_message_size = true;
        rsp.max_message_size = 0;
        if (getMclStatusManager()->getIntValue(RFX_STATUS_KEY_VOICE_CALL_COUNT, 0) > 0) {
            // There is an ongoing call so do not notify STATUS_IND now
            logI(mTag, "[BTSAP] Connection Success but there is ongoing call");
            rsp.response = RIL_SIM_SAP_CONNECT_RSP_Response_RIL_E_SAP_CONNECT_OK_CALL_ONGOING;
        } else {
            logD(mTag, "[BTSAP] Connection Success");
            rsp.response = RIL_SIM_SAP_CONNECT_RSP_Response_RIL_E_SUCCESS;
            unsolMsg = RIL_SIM_SAP_STATUS_IND_Status_RIL_SIM_STATUS_CARD_RESET;
        }

        getMclStatusManager()->setIntValue(RFX_STATUS_KEY_BTSAP_STATUS, BT_SAP_CONNECTION_SETUP);
    }

    sendBtSapResponseComplete(msg, ret, RFX_MSG_REQUEST_SIM_SAP_CONNECT, &rsp);

    if (unsolMsg != RIL_SIM_SAP_STATUS_IND_Status_RIL_SIM_STATUS_UNKNOWN_ERROR) {
        sendBtSapStatusInd(unsolMsg);
    }
    if (req != NULL) {
        free(req);
    }
    logD(mTag, "[BTSAP] requestLocalSapConnect end");
    return;
format_error:
    logE(mTag, "[BTSAP] Connection Fail");
    rsp.has_max_message_size = false;
    rsp.max_message_size = 0;
    sendBtSapResponseComplete(msg, ret, RFX_MSG_REQUEST_SIM_SAP_CONNECT, &rsp);
    if (req != NULL) {
        free(req);
    }
}

void RmcCommSimRequestHandler::handleBtSapDisconnect(const sp<RfxMclMessage>& msg) {
    RIL_SIM_SAP_DISCONNECT_REQ *req = NULL;
    RIL_SIM_SAP_DISCONNECT_RSP rsp;
    sp<RfxAtResponse> p_response;
    int err;
    RIL_Errno ret = RIL_E_GENERIC_FAILURE;
    void *data = msg->getData()->getData();
    int datalen = msg->getData()->getDataLength();

    logD(mTag, "[BTSAP] requestLocalBtSapDisconnect start");
    req = (RIL_SIM_SAP_DISCONNECT_REQ*)calloc(1, sizeof(RIL_SIM_SAP_DISCONNECT_REQ));
    RFX_ASSERT(req != NULL);
    decodeBtSapPayload(RFX_MSG_REQUEST_SIM_SAP_DISCONNECT, data, datalen, req);

    getMclStatusManager()->setIntValue(RFX_STATUS_KEY_BTSAP_STATUS, BT_SAP_DISCONNECT);
    if (getMclStatusManager()->getIntValue(RFX_STATUS_KEY_CARD_TYPE, -1) > 0) {
        p_response = atSendCommand("AT+EBTSAP=1");
        err = p_response->getError();

        if (err < 0) {
            goto format_error;
        }

        if (p_response->getSuccess() == 0) {
            logE(mTag, "[BTSAP] CME ERROR = %d", p_response->atGetCmeError());
            switch (p_response->atGetCmeError()) {
                case CME_BT_SAP_UNDEFINED:
                    ret = RIL_E_REQUEST_NOT_SUPPORTED;
                    break;
                case CME_BT_SAP_NOT_ACCESSIBLE:
                    ret = RIL_E_SIM_ERR;
                    break;
                case CME_BT_SAP_CARD_REMOVED:
                case CME_SIM_NOT_INSERTED:
                    ret = RIL_E_SIM_ABSENT;
                    break;
                default:
                    break;
            }
            goto format_error;
        } else {
            resetBtSapContext();
            ret = RIL_E_SUCCESS;
            rsp.dummy_field = 1;
        }

        sendBtSapResponseComplete(msg, ret, RFX_MSG_REQUEST_SIM_SAP_DISCONNECT, &rsp);

        logD(mTag, "[BTSAP] requestLocalBtSapDisconnect end");
    } else {
        logD(mTag, "[BTSAP] requestBtSapDisconnect but card was removed");
        rsp.dummy_field = 1;
        getMclStatusManager()->setIntValue(RFX_STATUS_KEY_BTSAP_STATUS, BT_SAP_INIT);
        ret = RIL_E_SUCCESS;
        sendBtSapResponseComplete(msg, ret, RFX_MSG_REQUEST_SIM_SAP_DISCONNECT, &rsp);
    }
    if (req != NULL) {
        free(req);
    }
    return;
format_error:
    logE(mTag, "[BTSAP] Fail to disconnect");
    getMclStatusManager()->setIntValue(RFX_STATUS_KEY_BTSAP_STATUS, BT_SAP_INIT);
    rsp.dummy_field = 0;
    sendBtSapResponseComplete(msg, ret, RFX_MSG_REQUEST_SIM_SAP_DISCONNECT, &rsp);
    if (req != NULL) {
        free(req);
    }
}

void RmcCommSimRequestHandler::handleBtSapTransferApdu(const sp<RfxMclMessage>& msg) {
    RIL_SIM_SAP_APDU_REQ *req = NULL;
    RIL_SIM_SAP_APDU_RSP rsp;
    sp<RfxAtResponse> p_response;
    int err;
    String8 cmd("");
    RfxAtLine *line = NULL;
    char *pApduResponse = NULL;
    char *hexStr = NULL;
    pb_bytes_array_t *apduResponse = NULL;
    RIL_Errno ret = RIL_E_GENERIC_FAILURE;
    void *data = msg->getData()->getData();
    int datalen = msg->getData()->getDataLength();

    req = (RIL_SIM_SAP_APDU_REQ*)calloc(1, sizeof(RIL_SIM_SAP_APDU_REQ));
    RFX_ASSERT(req != NULL);
    decodeBtSapPayload(RFX_MSG_REQUEST_SIM_SAP_APDU, data, datalen, req);
    if (getMclStatusManager()->getIntValue(RFX_STATUS_KEY_CARD_TYPE, -1) <= 0) {
        logD(mTag, "[BTSAP] requestBtSapTransferApdu but card was removed");
        rsp.response = RIL_SIM_SAP_APDU_RSP_Response_RIL_E_SIM_ABSENT;
        ret = RIL_E_SIM_ABSENT;
        sendBtSapResponseComplete(msg, ret, RFX_MSG_REQUEST_SIM_SAP_APDU, &rsp);
    } else if (getMclStatusManager()->getIntValue(RFX_STATUS_KEY_BTSAP_STATUS, 0) ==
            BT_SAP_POWER_OFF) {
        logD(mTag, "[BTSAP] requestBtSapTransferApdu but card was already power off");
        rsp.response = RIL_SIM_SAP_APDU_RSP_Response_RIL_E_SIM_ALREADY_POWERED_OFF;
        sendBtSapResponseComplete(msg, ret, RFX_MSG_REQUEST_SIM_SAP_APDU, &rsp);
    } else {
        hexStr = convertBtSapIntToHexString(req->command->bytes, req->command->size);
        logD(mTag, "[BTSAP] requestLocalBtSapTransferApdu start, (%d,%d,%s)", req->type,
                req->command->size, hexStr);
        memset(&rsp, 0, sizeof(RIL_SIM_SAP_APDU_RSP));
        cmd.append(String8::format("AT+EBTSAP=5,0,\"%s\"", hexStr));
        p_response = atSendCommandSingleline(cmd, "+EBTSAP:");
        if (p_response == NULL) {
            if (hexStr != NULL) {
                free(hexStr);
            }
            goto format_error;
        }
        if (hexStr != NULL) {
            free(hexStr);
        }
        cmd.clear();

        err = p_response->getError();
        if (err < 0) {
            rsp.response = RIL_SIM_SAP_APDU_RSP_Response_RIL_E_GENERIC_FAILURE;
            goto format_error;
        }

        if (p_response->getSuccess() == 0) {
            logE(mTag, "[BTSAP] CME ERROR = %d", p_response->atGetCmeError());
            rsp.response = RIL_SIM_SAP_APDU_RSP_Response_RIL_E_GENERIC_FAILURE;
            switch (p_response->atGetCmeError()) {
                case CME_BT_SAP_UNDEFINED:
                    ret = RIL_E_REQUEST_NOT_SUPPORTED;
                    rsp.response = RIL_SIM_SAP_APDU_RSP_Response_RIL_E_GENERIC_FAILURE;
                    break;
                case CME_BT_SAP_NOT_ACCESSIBLE:
                    ret = RIL_E_SIM_ERR;
                    rsp.response = RIL_SIM_SAP_APDU_RSP_Response_RIL_E_SIM_NOT_READY;
                    break;
                case CME_BT_SAP_CARD_REMOVED:
                case CME_SIM_NOT_INSERTED:
                    ret = RIL_E_SIM_ABSENT;
                    rsp.response = RIL_SIM_SAP_APDU_RSP_Response_RIL_E_SIM_ABSENT;
                    break;
                default:
                    break;
            }
            goto format_error;
        } else {
            char *pRes = NULL;

            line = p_response->getIntermediates();
            if (line == NULL) {
                goto format_error;
            }
            line->atTokStart(&err);
            if (err < 0) goto format_error;

            pApduResponse = line->atTokNextstr(&err);
            if (pApduResponse == NULL) {
                goto format_error;
            }
            if (err < 0) goto  format_error;

            int apduLen = strlen(pApduResponse);
            int reslen = hexStringToByteArrayEx((unsigned char *)pApduResponse, apduLen,
                    (unsigned char **)&pRes);
            RFX_ASSERT(pRes != NULL);
            apduResponse = (pb_bytes_array_t *)calloc(1,sizeof(pb_bytes_array_t) + reslen);
            RFX_ASSERT(apduResponse != NULL);
            memcpy(apduResponse->bytes, pRes, reslen);
            apduResponse->size = reslen;
            rsp.apduResponse = apduResponse;
            rsp.response = RIL_SIM_SAP_APDU_RSP_Response_RIL_E_SUCCESS;
            ret = RIL_E_SUCCESS;
            free(pRes);
        }

        sendBtSapResponseComplete(msg, ret, RFX_MSG_REQUEST_SIM_SAP_APDU, &rsp);

        if (apduResponse != NULL) {
            free(apduResponse);
        }
    }
    if (req != NULL) {
        free(req);
    }
    logD(mTag, "[BTSAP] requestLocalBtSapTransferApdu end");
    return;
format_error:
    logE(mTag, "[BTSAP] Fail to send APDU");

    sendBtSapResponseComplete(msg, ret, RFX_MSG_REQUEST_SIM_SAP_APDU, &rsp);

    if (req != NULL) {
        free(req);
    }
}

void RmcCommSimRequestHandler::handleBtSapTransferAtr(const sp<RfxMclMessage>& msg) {
    RIL_SIM_SAP_TRANSFER_ATR_REQ *req = NULL;
    RIL_SIM_SAP_TRANSFER_ATR_RSP rsp;
    RIL_Errno ret = RIL_E_GENERIC_FAILURE;
    int status = getMclStatusManager()->getIntValue(RFX_STATUS_KEY_BTSAP_STATUS, 0);
    pb_bytes_array_t *atrResponse = NULL;
    void *data = msg->getData()->getData();
    int datalen = msg->getData()->getDataLength();

    logD(mTag, "[BTSAP] requestBtSapTransferAtr start");
    req = (RIL_SIM_SAP_TRANSFER_ATR_REQ*)calloc(1, sizeof(RIL_SIM_SAP_TRANSFER_ATR_REQ));
    RFX_ASSERT(req != NULL);
    decodeBtSapPayload(RFX_MSG_REQUEST_SIM_SAP_TRANSFER_ATR, data, datalen, req);

    if (getMclStatusManager()->getIntValue(RFX_STATUS_KEY_CARD_TYPE, -1) <= 0) {
        logD(mTag, "[BTSAP] requestBtSapTransferAtr but card was removed");
        rsp.response = RIL_SIM_SAP_TRANSFER_ATR_RSP_Response_RIL_E_SIM_ABSENT;
        rsp.atr = NULL;
        ret = RIL_E_SIM_ABSENT;
    } else if (status == BT_SAP_POWER_OFF) {
        logD(mTag, "[BTSAP] requestBtSapTransferAtr but card was already power off");
        rsp.response = RIL_SIM_SAP_TRANSFER_ATR_RSP_Response_RIL_E_SIM_ALREADY_POWERED_OFF;
        rsp.atr = NULL;
    } else if (status == BT_SAP_POWER_ON ||
                status == BT_SAP_CONNECTION_SETUP ||
                status == BT_SAP_ONGOING_CONNECTION) {
        char *pRes = NULL;
        rsp.response = RIL_SIM_SAP_TRANSFER_ATR_RSP_Response_RIL_E_SUCCESS;
        String8 atr = getMclStatusManager()->getString8Value(RFX_STATUS_KEY_BTSAP_ATR);
        const char* atrStr = atr.string();
        int atrLen = strlen(atrStr);
        int reslen = hexStringToByteArrayEx((unsigned char *)atrStr, atrLen,
                (unsigned char **)&pRes);
        RFX_ASSERT(pRes != NULL);
        atrResponse = (pb_bytes_array_t *)calloc(1,sizeof(pb_bytes_array_t) + reslen);
        RFX_ASSERT(atrResponse != NULL);
        memcpy(atrResponse->bytes, pRes, reslen);
        atrResponse->size = reslen;
        rsp.atr = atrResponse;
        if (pRes != NULL) {
            free(pRes);
        }

        logD(mTag, "[BTSAP] requestBtSapTransferAtr, status: %d, size: %d", status, atrLen);

        if (status == BT_SAP_CONNECTION_SETUP) {
            getMclStatusManager()->setIntValue(RFX_STATUS_KEY_BTSAP_STATUS, BT_SAP_ONGOING_CONNECTION);
        }
    } else {
        rsp.response = RIL_SIM_SAP_TRANSFER_ATR_RSP_Response_RIL_E_GENERIC_FAILURE;
        rsp.atr = NULL;
    }
    sendBtSapResponseComplete(msg, ret, RFX_MSG_REQUEST_SIM_SAP_TRANSFER_ATR, &rsp);

    if (atrResponse != NULL) {
        free(atrResponse);
    }

    free(req);
    logD(mTag, "[BTSAP] requestBtSapTransferAtr end");
}

void RmcCommSimRequestHandler::handleBtSapPower(const sp<RfxMclMessage>& msg) {
    RIL_SIM_SAP_POWER_REQ *req = NULL;
    RIL_SIM_SAP_POWER_RSP rsp;
    RIL_Errno ret = RIL_E_GENERIC_FAILURE;
    sp<RfxAtResponse> p_response;
    int err;
    int type = 0;
    char *pAtr = NULL;
    String8 cmd("");
    RfxAtLine *line = NULL;
    int status = getMclStatusManager()->getIntValue(RFX_STATUS_KEY_BTSAP_STATUS);
    void *data = msg->getData()->getData();
    int datalen = msg->getData()->getDataLength();

    req = (RIL_SIM_SAP_POWER_REQ*)calloc(1, sizeof(RIL_SIM_SAP_POWER_REQ));
    RFX_ASSERT(req != NULL);
    decodeBtSapPayload(RFX_MSG_REQUEST_SIM_SAP_POWER, data, datalen, req);

    logD(mTag, "[BTSAP] requestBtSapPower start, (%d)", req->state);
    do {
        if (getMclStatusManager()->getIntValue(RFX_STATUS_KEY_CARD_TYPE) <= 0) {
            logD(mTag, "[BTSAP] requestBtSapPower but card was removed");
            rsp.response = RIL_SIM_SAP_POWER_RSP_Response_RIL_E_SIM_ABSENT;
            ret = RIL_E_SIM_ABSENT;
        } else if (req->state == TRUE && status == BT_SAP_POWER_ON) {
            logD(mTag, "[BTSAP] requestBtSapPower on but card was already power on");
            rsp.response = RIL_SIM_SAP_POWER_RSP_Response_RIL_E_SIM_ALREADY_POWERED_ON;
        } else if (req->state == FALSE && status == BT_SAP_POWER_OFF) {
            logD(mTag, "[BTSAP] requestBtSapPower off but card was already power off");
            rsp.response = RIL_SIM_SAP_POWER_RSP_Response_RIL_E_SIM_ALREADY_POWERED_OFF;
        } else {
            if (req->state == TRUE) {
                cmd.append(String8::format("AT+EBTSAP=2,%d", getMclStatusManager()->getIntValue(
                        RFX_STATUS_KEY_BTSAP_CURRENT_PROTOCOL)));
                p_response = atSendCommandSingleline(cmd, "+EBTSAP:");
            } else {
                p_response = atSendCommand("AT+EBTSAP=3");
            }
            if (p_response == NULL) {
                rsp.response = RIL_SIM_SAP_POWER_RSP_Response_RIL_E_GENERIC_FAILURE;
                goto format_error;
            }
            err = p_response->getError();
            if (err < 0) {
                rsp.response = RIL_SIM_SAP_POWER_RSP_Response_RIL_E_GENERIC_FAILURE;
                goto format_error;
            }

            if (p_response->getSuccess() == 0) {
                logE(mTag, "[BTSAP] CME ERROR = %d", p_response->atGetCmeError());
                rsp.response = RIL_SIM_SAP_POWER_RSP_Response_RIL_E_GENERIC_FAILURE;
                switch (p_response->atGetCmeError()) {
                    case CME_BT_SAP_CARD_REMOVED:
                    case CME_SIM_NOT_INSERTED:
                        ret = RIL_E_SIM_ABSENT;
                        rsp.response = RIL_SIM_SAP_POWER_RSP_Response_RIL_E_SIM_ABSENT;
                        break;
                    default:
                        break;
                }
                goto format_error;
            } else {
                if (req->state == TRUE) {
                    line = p_response->getIntermediates();
                    if (line == NULL) {
                        goto format_error;
                    }

                    line->atTokStart(&err);
                    if (err < 0) goto format_error;

                    type = line->atTokNextint(&err);
                    if (err < 0) goto  format_error;

                    getMclStatusManager()->setIntValue(RFX_STATUS_KEY_BTSAP_CURRENT_PROTOCOL, type);

                    pAtr = line->atTokNextstr(&err);
                    if (err < 0) goto  format_error;

                    int atrLen = 0;
                    if (pAtr != NULL) {
                        // Update ATR
                        atrLen = strlen(pAtr);
                        getMclStatusManager()->setString8Value(RFX_STATUS_KEY_BTSAP_ATR,
                                String8::format("%s", pAtr));
                    }
                    logD(mTag, "[BTSAP] requestLocalBtSapPower, cur_type: %d, size: %d",
                            getMclStatusManager()->getIntValue(
                            RFX_STATUS_KEY_BTSAP_CURRENT_PROTOCOL), atrLen);
                    getMclStatusManager()->setIntValue(RFX_STATUS_KEY_BTSAP_STATUS,
                            BT_SAP_POWER_ON);
                } else {
                    getMclStatusManager()->setIntValue(RFX_STATUS_KEY_BTSAP_STATUS,
                            BT_SAP_POWER_OFF);
                }
                logD(mTag, "[BTSAP] requestLocalBtSapPower, success! status: %d",
                        getMclStatusManager()->getIntValue(RFX_STATUS_KEY_BTSAP_STATUS));
                ret = RIL_E_SUCCESS;
                rsp.response = RIL_SIM_SAP_POWER_RSP_Response_RIL_E_SUCCESS;
            }
        }

        sendBtSapResponseComplete(msg, ret, RFX_MSG_REQUEST_SIM_SAP_POWER, &rsp);
    } while(0);

    free(req);

    logD(mTag, "[BTSAP] requestBtSapPower end");
    return;
format_error:
    logE(mTag, "[BTSAP] Fail to Set Power");
    sendBtSapResponseComplete(msg, ret, RFX_MSG_REQUEST_SIM_SAP_POWER, &rsp);
    if (req != NULL) {
        free(req);
    }

}

void RmcCommSimRequestHandler::handleBtSapResetSim(const sp<RfxMclMessage>& msg) {
    RIL_SIM_SAP_RESET_SIM_REQ *req = NULL;
    RIL_SIM_SAP_RESET_SIM_RSP rsp;
    RIL_Errno ret = RIL_E_GENERIC_FAILURE;
    int status = getMclStatusManager()->getIntValue(RFX_STATUS_KEY_BTSAP_STATUS);
    void *data = msg->getData()->getData();
    int datalen = msg->getData()->getDataLength();
    sp<RfxAtResponse> p_response;
    int err, type = 0;
    String8 cmd("");
    char *pAtr = NULL;
    RfxAtLine *line = NULL;
    //pb_bytes_array_t *atrResponse = NULL;

    logD(mTag, "[BTSAP] requestBtSapResetSim start");
    req = (RIL_SIM_SAP_RESET_SIM_REQ*)calloc(1, sizeof(RIL_SIM_SAP_RESET_SIM_REQ));
    RFX_ASSERT(req != NULL);
    decodeBtSapPayload(RFX_MSG_REQUEST_SIM_SAP_RESET_SIM, data, datalen, req);

    do {
        if (getMclStatusManager()->getIntValue(RFX_STATUS_KEY_CARD_TYPE) <= 0) {
            logD(mTag, "[BTSAP] requestBtSapResetSim but card was removed");
            rsp.response = RIL_SIM_SAP_RESET_SIM_RSP_Response_RIL_E_SIM_ABSENT;
        } else if (status == BT_SAP_POWER_OFF) {
            logD(mTag, "[BTSAP] requestBtSapResetSim off but card was already power off");
            rsp.response = RIL_SIM_SAP_RESET_SIM_RSP_Response_RIL_E_SIM_ALREADY_POWERED_OFF;
        } else {
            memset(&rsp, 0, sizeof(RIL_SIM_SAP_RESET_SIM_RSP));
            cmd.append(String8::format("AT+EBTSAP=4,%d", getMclStatusManager()->getIntValue(
                    RFX_STATUS_KEY_BTSAP_CURRENT_PROTOCOL)));
            p_response = atSendCommandSingleline(cmd, "+EBTSAP:");
            err = p_response->getError();

            if (err < 0) {
                rsp.response = RIL_SIM_SAP_RESET_SIM_RSP_Response_RIL_E_GENERIC_FAILURE;
                goto format_error;
            }

            if (p_response->getSuccess() == 0) {
                logE(mTag, "[BTSAP] CME ERROR = %d", p_response->atGetCmeError());
                rsp.response = RIL_SIM_SAP_RESET_SIM_RSP_Response_RIL_E_GENERIC_FAILURE;
                switch (p_response->atGetCmeError()) {
                    case CME_BT_SAP_CARD_REMOVED:
                    case CME_SIM_NOT_INSERTED:
                        ret = RIL_E_SIM_ABSENT;
                        rsp.response = RIL_SIM_SAP_RESET_SIM_RSP_Response_RIL_E_SIM_ABSENT;
                        break;
                    default:
                        break;
                }
                goto format_error;
            } else {
                line = p_response->getIntermediates();

                line->atTokStart(&err);
                if (err < 0) goto format_error;

                type = line->atTokNextint(&err);
                if (err < 0) goto  format_error;

                getMclStatusManager()->setIntValue(RFX_STATUS_KEY_BTSAP_CURRENT_PROTOCOL, type);

                pAtr = line->atTokNextstr(&err);
                if (err < 0) goto  format_error;

                int atrLen = 0;

                if (pAtr != NULL) {
                    // Update ATR
                    atrLen = strlen(pAtr);
                    getMclStatusManager()->setString8Value(RFX_STATUS_KEY_BTSAP_ATR,
                            String8::format("%s", pAtr));
                }

                logD(mTag, "[BTSAP] requestLocalBtSapResetSim, cur_type: %d, size: %d",
                        getMclStatusManager()->getIntValue(RFX_STATUS_KEY_BTSAP_CURRENT_PROTOCOL),
                        atrLen);
                ret = RIL_E_SUCCESS;
                rsp.response = RIL_SIM_SAP_RESET_SIM_RSP_Response_RIL_E_SUCCESS;
            }
        }

        sendBtSapResponseComplete(msg, ret, RFX_MSG_REQUEST_SIM_SAP_RESET_SIM, &rsp);
    } while(0);

    free(req);

    logD(mTag, "[BTSAP] requestBtSapResetSim end");
    return;
format_error:
    logE(mTag, "[BTSAP] Fail to Reset SIM");
    free(req);
    sendBtSapResponseComplete(msg, ret, RFX_MSG_REQUEST_SIM_SAP_RESET_SIM, &rsp);
}

void RmcCommSimRequestHandler::handleBtSapSetTransferProtocol(const sp<RfxMclMessage>& msg) {
    RIL_SIM_SAP_ERROR_RSP rsp;
    RIL_Errno ret = RIL_E_REQUEST_NOT_SUPPORTED;
    sp<RfxMclMessage> response;

    logD(mTag, "[BTSAP] requestBtSapSetTransferProtocol start");
    rsp.dummy_field = 1;

    sendBtSapResponseComplete(msg, ret, RFX_MSG_REQUEST_SIM_SAP_SET_TRANSFER_PROTOCOL, &rsp);
}
// BTSAP - End

void RmcCommSimRequestHandler::handleSetSimCardPower(const sp < RfxMclMessage > & msg) {
    sp<RfxAtResponse> p_response;
    sp<RfxMclMessage> response;
    int err = RIL_E_SUCCESS;
    String8 cmd("");
    int* mode = (int*)(msg->getData()->getData());
    cmd.append(String8::format("AT+ESIMPOWER=%d", (*mode)));
    p_response = atSendCommand(cmd);
    err = p_response->getError();
    if (err < 0 || p_response->getSuccess() == 0) {
        logE(mTag, "requestSetSimCardPower AT+ESIMPOWER=%d Fail, e= %d", *mode, err);
        err = RIL_E_REQUEST_NOT_SUPPORTED;
    } else {
        getMclStatusManager()->setIntValue(RFX_STATUS_KEY_SIM_POWER_STATE, *mode);
        if (*mode == SIM_POWER_STATE_V16_SIM_ON) {
            int count = 0;
            int status = getMclStatusManager()->getIntValue(RFX_STATUS_KEY_SIM_INIT_STATUS,
                    SIM_INIT_STATE_ABSENT);
            do {
                status = getMclStatusManager()->getIntValue(RFX_STATUS_KEY_SIM_INIT_STATUS,
                                    SIM_INIT_STATE_ABSENT);
                sleepMsec(100);
                count++;
            } while ((status == SIM_INIT_STATE_INSERT) && (count < 20));

            count = 0;
            bool delay = true;
            do {
                p_response = atSendCommandSingleline("AT+CPIN?", "+CPIN:");
                err = p_response->getError();

                if (err != 0) {
                    break;
                } else if (p_response->getSuccess() == 0) {
                    switch (p_response->atGetCmeError()) {
                        case CME_SIM_NOT_INSERTED:
                        case CME_SIM_BUSY:
                            delay = true;
                            break;
                        default:
                            delay = false;
                            break;
                    }
                } else {
                    // Success get status
                    break;
                }

                if (delay) {
                    count++;  // to avoid block; if the busy time is too long; need to check modem.
                    if (count == 15) {
                        delay = false;
                    } else {
                        sleepMsec(200);
                    }
                }
            } while (delay);
        }
    }

    logI(mTag, "requestSetSimCardPower AT+ESIMPOWER=%d rsp to tcl, e= %d", *mode, err);
    response = RfxMclMessage::obtainResponse(msg->getId(), (RIL_Errno)err,
            RfxVoidData(), msg, false);

    responseToTelCore(response);
    if (*mode == SIM_POWER_STATE_V16_SIM_OFF) {
        logI(mTag, "requestSetSimCardPower, send sim status changed.");
        sendSimStatusChanged();
    }
}

bool RmcCommSimRequestHandler::isEnableUiccApplicationsSupported() {
    if ((getMclStatusManager()->getIntValue(RFX_STATUS_KEY_AP_SIM_SWITCH_MODE)
            == SIM_SWITCH_MODE_AOSP_UICC_APPLICATIONS_ENABLE_DISABLE)
            && (getMclStatusManager()->getIntValue(RFX_STATUS_KEY_MD_SIM_SWITCH_MODE)
            == SIM_SWITCH_MODE_AOSP_UICC_APPLICATIONS_ENABLE_DISABLE)) {
        return true;
    }
    return false;
}

void RmcCommSimRequestHandler::handleEnableUiccApplications(const sp < RfxMclMessage > & msg) {
    sp<RfxAtResponse> p_response;
    sp<RfxMclMessage> response;
    RIL_Errno ril_error = RIL_E_SUCCESS;
    String8 cmd("");
    int* enable = (int*)(msg->getData()->getData());
    int mode = 10;

    // AT+ESIMPOWER=10 disable Uicc Applications
    // AT+ESIMPOWER=11 enable Uicc Applications
    if ((*enable) == 0) {
        mode = 10;
    } else {
        mode = 11;
    }
    cmd.append(String8::format("AT+ESIMPOWER=%d", mode));
    p_response = atSendCommand(cmd);

    if (p_response == NULL || p_response->getError() < 0) {
        logE(mTag, "%s() fail: Undesirable", __FUNCTION__);
        ril_error = RIL_E_OPERATION_NOT_ALLOWED;
    } else if (p_response->getSuccess() == 0) {
        switch (p_response->atGetCmeError()) {
            case CME_OPERATION_NOT_ALLOWED_ERR:
                ril_error = RIL_E_OPERATION_NOT_ALLOWED;
                break;
            case CME_SIM_NOT_INSERTED:
                ril_error = RIL_E_SIM_ABSENT;
                break;
            default:
                ril_error = RIL_E_OPERATION_NOT_ALLOWED;
                break;
        }
    }

    response = RfxMclMessage::obtainResponse(msg->getId(), ril_error, RfxVoidData(), msg, false);
    responseToTelCore(response);
}

void RmcCommSimRequestHandler::handleAreUiccApplicationsEnabled(const sp < RfxMclMessage > & msg) {
    sp<RfxAtResponse> p_response;
    sp<RfxMclMessage> response;
    RfxAtLine *line = NULL;
    int err;
    RIL_Errno ril_error = RIL_E_SUCCESS;
    int enable = 0;

    do {
        // +ESIMPOWER: 10 Uicc Applications disabled
        // +ESIMPOWER: 11 Uicc Applications enabled
        p_response = atSendCommandSingleline("AT+ESIMPOWER?", "+ESIMPOWER:");

        if (p_response == NULL || p_response->getError() < 0) {
            logE(mTag, "%s() fail: Undesirable", __FUNCTION__);
            ril_error = RIL_E_OPERATION_NOT_ALLOWED;
        } else if (p_response->getSuccess() == 0) {
            switch (p_response->atGetCmeError()) {
                case CME_SIM_NOT_INSERTED:
                    ril_error = RIL_E_SIM_ABSENT;
                    enable = 1;
                    break;
                default:
                    ril_error = RIL_E_OPERATION_NOT_ALLOWED;
                    break;
            }
        } else if (p_response->getSuccess() > 0) {
            // Success
            line = p_response->getIntermediates();
            line->atTokStart(&err);
            if (err < 0) {
                logE(mTag, "%s() fail 1: Undesirable", __FUNCTION__);
                ril_error = RIL_E_OPERATION_NOT_ALLOWED;
                break;
            }
            // Uicc Applications enable status
            enable = line->atTokNextint(&err);
            if (err < 0) {
                logE(mTag, "%s() fail 2: Undesirable", __FUNCTION__);
                ril_error = RIL_E_OPERATION_NOT_ALLOWED;
                enable = 0;
            } else {
                if (enable == 10) {
                    enable = 0;
                } else if (enable == 11) {
                    enable = 1;
                } else {
                    logE(mTag, "%s() fail 3: Undesirable", __FUNCTION__);
                    ril_error = RIL_E_OPERATION_NOT_ALLOWED;
                    enable = 0;
                }
            }
            line = NULL;
        } else {
            logE(mTag, "%s() fail 4: Undesirable", __FUNCTION__);
            ril_error = RIL_E_OPERATION_NOT_ALLOWED;
        }
    } while (0);
    response = RfxMclMessage::obtainResponse(msg->getId(), ril_error,
            RfxIntsData((void*)&enable, sizeof(int)), msg, false);
    responseToTelCore(response);
}

void RmcCommSimRequestHandler::handleSetSimPower(const sp < RfxMclMessage > & msg) {
    sp<RfxAtResponse> p_response;
    sp<RfxMclMessage> response;
    int err = RIL_E_SUCCESS;
    String8 cmd("");
    int* mode = (int*)(msg->getData()->getData());

    cmd.append(String8::format("AT+ESIMPOWER=%d", (*mode)));
    p_response = atSendCommand(cmd);

    if (p_response->getSuccess() == 0) {
        switch (p_response->atGetCmeError()) {
            case CME_OPERATION_NOT_ALLOWED_ERR:
                err = RIL_E_OPERATION_NOT_ALLOWED;
                break;
            case CME_SIM_NOT_INSERTED:
                err = RIL_E_SIM_ABSENT;
                break;
            default:
                err = RIL_E_OPERATION_NOT_ALLOWED;
                break;
        }
    }

    response = RfxMclMessage::obtainResponse(msg->getId(), (RIL_Errno)err, RfxVoidData(), msg,
            false);
    responseToTelCore(response);
}
void RmcCommSimRequestHandler::handleEnterDeviceNetworkDepersonalization(
    const sp<RfxMclMessage>& msg) {
    char** strings = (char**)(msg->getData()->getData());
    int err = -1;
    int new_state = -1;
    int op = -1;
    int op_remain_count = 0;
    RIL_Errno ret = RIL_E_GENERIC_FAILURE;
    sp<RfxAtResponse> p_response = NULL;
    String8 cmd("");

    do {
        if (strings == NULL || strings[0] == NULL) {
             ret = RIL_E_INVALID_ARGUMENTS;
             logD(mTag, "handleEnterDeviceNetworkDepersonalization invalid arguments.");
             break;
        }
        logD(mTag, "handleEnterDeviceNetworkDepersonalization lockPin : *** \n");

        op = SML_LOCK_OR_UNLOCK;
        new_state = SML_UNLOCK_DEVICE;
        cmd.append(String8::format("AT+ESLBLOB=%d,\"%s\",%d", op, strings[0], new_state));
        p_response = atSendCommand(cmd.string());
        err = p_response->getError();

        cmd.clear();
        if (err != 0) {
            /* AT runtime error */
            logE(mTag, "handleEnterDeviceNetworkDepersonalization err = %d", err);
            break;
        }

        if (p_response->getSuccess() == 0) {
            switch (p_response->atGetCmeError()) {
                case CME_INCORRECT_PASSWORD:
                    ret = RIL_E_PASSWORD_INCORRECT;
                    break;
                default:
                    ret = RIL_E_GENERIC_FAILURE;
                    break;
            }
        } else {
            ret = RIL_E_SUCCESS;
        }
        logD(mTag, "handleEnterDeviceNetworkDepersonalization ret = %d", ret);
    } while (0);

    // Get SML retry count
    RmcSimSlotLockDeviceLockInfo* retry = getSimSlotLockDeviceLockInfo();
    if (retry != NULL) {
        op_remain_count = retry->remain;
        free(retry);
    }

    sp<RfxMclMessage> response = RfxMclMessage::obtainResponse(msg->getId(), ret,
            RfxIntsData((void*)&op_remain_count, sizeof(op_remain_count)), msg, false);
    responseToTelCore(response);
}

bool RmcCommSimRequestHandler::getAtr(char* value) {
    sp<RfxAtResponse> p_response;
    int err;
    char *tmp1;
    char *tmp2;
    RfxAtLine *line;

    p_response = atSendCommandSingleline("AT+ESIMINFO=0", "+ESIMINFO:");
    err = p_response->getError();

    if (err < 0 || p_response->getSuccess() == 0) {
        logE(mTag, "getAtr Fail 0");
        return false;
    }

    // +ESIMINFO:<mode>, <data> => if<mode>=0,<data>=ATR Hex String
    line = p_response->getIntermediates();
    line->atTokStart(&err);
    if (err < 0) {
        logE(mTag, "getAtr Fail 1");
        return false;
    }
    tmp1 = line->atTokNextstr(&err);
    if (err < 0) {
        logE(mTag, "getAtr Fail 2");
        return false;
    }
    tmp2 = line->atTokNextstr(&err);
    if (err < 0) {
        logE(mTag, "getAtr Fail 3");
        return false;
    }
    if (sprintf(value, "%s", tmp2) < 0) {
        logE(mTag, "getAtr copy string fail");
        return false;
    }
    logD(mTag, "getAtr ATR =  %s ", value);
    return true;
}

bool RmcCommSimRequestHandler::getEid(char* value) {
    // RIL_SimSlotStatus *p_slot_status = NULL;
    RIL_SimSlotStatus **pp_slot_status = NULL;
    sp<RfxAtResponse> p_response = NULL;
    RfxAtLine *line = NULL;
    int slotNum = 0;
    int err = -1;
    int decodeerr = -1;

    String8 eid = getMclStatusManager()->getString8Value(RFX_STATUS_KEY_SIM_EID);
    logD(mTag, "getEid RFX_STATUS_KEY_SIM_EID =  %s ", eid.string());

    // The EID can be updated by urc "+ESLOTSINFO" and request "AT+ESLOTSINFO?".
    // So it could read key value if EID has been updated.
    if (!eid.isEmpty()) {
        // Do not set N/A for AOSP request.
        if (strcmp(eid.string(), "N/A") != 0) {
            if (sprintf(value, "%s", eid.string()) < 0) {
                return false;
            }
        }

        return true;
    } else {
        p_response = atSendCommandSingleline("AT+ESLOTSINFO?", "+ESLOTSINFO:");

        if (p_response != NULL) {
            err = p_response->getError();
        } else {
            goto error;
        }

        if (err < 0 || p_response->getSuccess() == 0) {
            goto error;
        }

        line = p_response->getIntermediates();

        pp_slot_status = decodeEslotsinfo(line, &decodeerr, &slotNum);
        if ((decodeerr != RIL_E_SUCCESS) || (pp_slot_status == NULL)) {
            goto error;
        }

        // Set EID for current slot ID.
        eid = getMclStatusManager()->getString8Value(RFX_STATUS_KEY_SIM_EID);
        logD(mTag, "getEid RFX_STATUS_KEY_SIM_EID =  %s ", eid.string());
        if (sprintf(value, "%s", eid.string()) < 0) {
            goto error;
        }

        if (pp_slot_status != NULL) {
            free(pp_slot_status[0]);
        }
        free(pp_slot_status);

        return true;
    }

error:
    logD(mTag, "getEid Failed to get Eid!, pp_slot_status = %p", pp_slot_status);

    if (pp_slot_status != NULL) {
        free(pp_slot_status[0]);
        free(pp_slot_status);
    }

    return false;
}

void RmcCommSimRequestHandler::handleSetSimSlotsMapping(const sp<RfxMclMessage>& msg) {
    logD(mTag, "handleSetSimSlotsMapping");
    RIL_Errno rilErrNo = RIL_E_SUCCESS;
    sp<RfxAtResponse> p_response = NULL;
    String8 cmd("");

    const int sim_count = RfxRilUtils::rfxGetSimCount();
    int *slotsMap = (int *)msg->getData()->getData();

    if (sim_count == 1) {
        if (((int *)slotsMap)[0] != 0) {
            logI(mTag, "handleSetSimSlotsMapping, slotsMap)[0] = %d", ((int *)slotsMap)[0]);
            ((int *)slotsMap)[0] = 0;
        }
        cmd.append(String8::format("AT+ESLOTSMAP=%d,%d", 1, ((int *)slotsMap)[0] + 1));
    } else if (sim_count == 2) {
        cmd.append(String8::format("AT+ESLOTSMAP=%d,%d,%d", 2, ((int *)slotsMap)[0] + 1,
                ((int *)slotsMap)[1] + 1));
    } else if (sim_count == 3) {
        cmd.append(String8::format("AT+ESLOTSMAP=%d,%d,%d,%d", 3, ((int *)slotsMap)[0] + 1,
                ((int *)slotsMap)[1] + 1, ((int *)slotsMap)[2] + 1));
    } else if (sim_count == 4) {
        cmd.append(String8::format("AT+ESLOTSMAP=%d,%d,%d,%d,%d", 4, ((int *)slotsMap)[0] + 1,
                ((int *)slotsMap)[1] + 1,    ((int *)slotsMap)[2] + 1, ((int *)slotsMap)[3] + 1));
    }

    p_response = atSendCommand(cmd);

    if (p_response != NULL) {
      if (p_response->getSuccess() != 1) {
          rilErrNo = RIL_E_REQUEST_NOT_SUPPORTED;
      }
      p_response = NULL;
    }
    sp<RfxMclMessage> response = RfxMclMessage::obtainResponse(msg->getId(), rilErrNo,
            RfxVoidData(), msg, false);
    responseToTelCore(response);
}

void RmcCommSimRequestHandler::querySimOnOffActivation() {
    char feature[] = "SWITCH_OFF_SIM";
    char featureOption[RFX_PROPERTY_VALUE_MAX] = { 0 };

    int support = getFeatureVersion(feature);

    // SIM ON OFF feature, 0:disable, 1:enable
    if (support == 1) {
        rfx_property_set(PROPERTY_SIM_ONOFF_SUPPORT, String8::format("%d", support).string());
        getMclStatusManager()->setBoolValue(RFX_STATUS_KEY_MODEM_SIMONOFF_SUPPORT, true);
    } else {
        rfx_property_set(PROPERTY_SIM_ONOFF_SUPPORT, String8::format("%d", 0).string());
        getMclStatusManager()->setBoolValue(RFX_STATUS_KEY_MODEM_SIMONOFF_SUPPORT, false);

        // Set SIM on/off state for modem non-supported project.
        getMclStatusManager()->setIntValue(RFX_STATUS_KEY_SIM_ONOFF_STATE, SIM_POWER_STATE_SIM_ON);
        String8 simOnOff(PROPERTY_SIM_ONOFF_STATE);
        simOnOff.append(String8::format("%d", (m_slot_id + 1)));
        rfx_property_set(simOnOff.string(), String8::format("%d", SIM_POWER_STATE_SIM_ON)
                .string());
        // Notify SIM power state.
        int simPower = SIM_POWER_STATE_SIM_ON;
        sp<RfxMclMessage> unsol = RfxMclMessage::obtainUrc(RFX_MSG_URC_SIM_POWER_CHANGED, m_slot_id,
                RfxIntsData(&simPower, 1));
        responseToTelCore(unsol);
    }

    rfx_property_get(PROPERTY_SIM_CARD_ONOFF, featureOption, "1");
    // Set SIM on/off enabled key value
    if ((atoi(featureOption) == 2) && (support == 1)) {
        getMclStatusManager()->setBoolValue(RFX_STATUS_KEY_SIM_ONOFF_ENABLED, true);
    } else {
        getMclStatusManager()->setBoolValue(RFX_STATUS_KEY_SIM_ONOFF_ENABLED, false);
    }

    // UICC Applications enable/disable feature
    if ((atoi(featureOption) != 1) && (atoi(featureOption) != 2)) {
        getMclStatusManager()->setIntValue(RFX_STATUS_KEY_AP_SIM_SWITCH_MODE,
                SIM_SWITCH_MODE_AOSP_UICC_APPLICATIONS_ENABLE_DISABLE);
    } else {
        getMclStatusManager()->setIntValue(RFX_STATUS_KEY_AP_SIM_SWITCH_MODE, atoi(featureOption));
    }
    if (support == 1) {
        getMclStatusManager()->setIntValue(RFX_STATUS_KEY_MD_SIM_SWITCH_MODE,
                SIM_SWITCH_MODE_AOSP_UICC_APPLICATIONS_ENABLE_DISABLE);
    } else {
        getMclStatusManager()->setIntValue(RFX_STATUS_KEY_MD_SIM_SWITCH_MODE,
                SIM_SWITCH_MODE_NONE);
    }
}

void RmcCommSimRequestHandler::handleEventGetSlotStatus(const sp<RfxMclMessage>& msg) {
    char* urc = (char *) msg->getData()->getData();
    logD(mTag, "handleEventGetSlotStatus urc =  %s ", urc);

    if (!strStartsWith(urc, "+ESLOTSINFO:")) {
        logE(mTag, "handleEventGetSlotStatus invalid event!");
        return;
    }

    RIL_SimSlotStatus **pp_slot_status = NULL;
    sp<RfxMclMessage> response;
    sp<RfxAtResponse> p_response = NULL;
    RfxAtLine *line = NULL;
    int slotNum = 0;
    int simCount = 0;
    int err = -1;
    int decodeerr = -1;
    sp<RfxMclMessage> unsol;

    p_response = atSendCommandSingleline("AT+ESLOTSINFO?", "+ESLOTSINFO:");

    if (p_response != NULL) {
        err = p_response->getError();
    } else {
        goto error;
    }

    if (err < 0 || p_response->getSuccess() == 0) {
        goto error;
    }

    line = p_response->getIntermediates();

    pp_slot_status = decodeEslotsinfo(line, &decodeerr, &slotNum);
    if ((decodeerr != RIL_E_SUCCESS) || (pp_slot_status == NULL)) {
        goto error;
    }

    simCount = (slotNum > RfxRilUtils::rfxGetSimCount()) ? RfxRilUtils::rfxGetSimCount() : slotNum;

    for (int i = 0; i < simCount; i++) {
        String8 iccid = getMclStatusManager(pp_slot_status[i]->logicalSlotId)->getString8Value(
                RFX_STATUS_KEY_SIM_ICCID);

        logD(mTag, "handleEventGetSlotStatus slotId:%d, iccid:%.9s, state:%d, comp:%d",
                pp_slot_status[i]->logicalSlotId, iccid.string(), pp_slot_status[i]->card_state,
                strcmp(iccid.string(), "N/A"));

        if ((pp_slot_status[i]->card_state == RIL_CARDSTATE_ABSENT)
                && (strcmp(iccid.string(), "N/A") != 0)) {
            decodeerr = RIL_E_INVALID_STATE;
            goto error;
        }
    }

    unsol = RfxMclMessage::obtainUrc(RFX_MSG_URC_ICC_SLOT_STATUS, m_slot_id,
            RfxSimSlotStatusData(pp_slot_status,  sizeof(RIL_SimSlotStatus *) * slotNum));
    responseToTelCore(unsol);

    if (pp_slot_status != NULL) {
        free(pp_slot_status[0]);
    }
    free(pp_slot_status);
    return;

error:
    logE(mTag, "handleEventGetSlotStatus decode error!, pp_slot_status = %p", pp_slot_status);
    if (pp_slot_status != NULL) {
        free(pp_slot_status[0]);
        free(pp_slot_status);
    }
}

void RmcCommSimRequestHandler::handleGetSlotStatus(const sp<RfxMclMessage>& msg) {
    logD(mTag, "handleGetSlotStatus");

    RIL_Errno ril_error = RIL_E_REQUEST_NOT_SUPPORTED;
    RIL_SimSlotStatus **pp_slot_status = NULL;
    sp<RfxMclMessage> response;
    sp<RfxAtResponse> p_response = NULL;
    RfxAtLine *line = NULL;
    int slotNum = 0;
    int count = 0;
    int err = -1;
    int decodeerr = -1;

    do {
        p_response = atSendCommandSingleline("AT+ESLOTSINFO?", "+ESLOTSINFO:");

        if (p_response != NULL) {
            err = p_response->getError();
        } else {
            goto error;
        }

        if (err < 0 || p_response->getSuccess() == 0) {
            goto error;
        }

        line = p_response->getIntermediates();

        pp_slot_status = decodeEslotsinfo(line, &decodeerr, &slotNum);
        if (decodeerr == RIL_E_SIM_BUSY) {
            count++;
            if (count == 30) {
                 ril_error = RIL_E_SIM_ERR;
                 goto error;
            } else {
                logI(mTag, "handleGetSlotStatus, %d-pp_slot_status = %p", count, pp_slot_status);
                if (pp_slot_status != NULL) {
                    free(pp_slot_status[0]);
                }
                free(pp_slot_status);
                pp_slot_status = NULL;
                sleepMsec(200);
            }
        } else if ((decodeerr != RIL_E_SUCCESS) || (pp_slot_status == NULL)) {
            ril_error = RIL_E_SIM_ERR;
            goto error;
        }
    } while (decodeerr == RIL_E_SIM_BUSY);

    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxSimSlotStatusData(pp_slot_status, sizeof(RIL_SimSlotStatus *) * slotNum), msg, false);
    responseToTelCore(response);

    if (pp_slot_status != NULL) {
        free(pp_slot_status[0]);
    }
    free(pp_slot_status);
    return;

error:
    response = RfxMclMessage::obtainResponse(msg->getId(), ril_error,
            RfxSimSlotStatusData(NULL, 0), msg, false);
    responseToTelCore(response);

    logE(mTag, "handleGetSlotStatus error!, pp_slot_status = %p", pp_slot_status);
    if (pp_slot_status != NULL) {
        free(pp_slot_status[0]);
        free(pp_slot_status);
    }
}

UICC_Status RmcCommSimRequestHandler::getSIMStatusWithRetry(void) {
    UICC_Status ret = UICC_ABSENT;
    int err, count = 0;
    RfxAtLine *line = NULL;
    char *cpinResult = NULL;
    sp<RfxAtResponse> p_response = NULL;
    int esim_cause = getMclStatusManager()->getIntValue(RFX_STATUS_KEY_SIM_ESIMS_CAUSE);

    do {
        p_response = atSendCommandSingleline("AT+CPIN?", "+CPIN:");
        err = p_response->getError();

        if (err != 0) {
            ret = UICC_NOT_READY;
        } else if (p_response->getSuccess() == 0) {
            switch (p_response->atGetCmeError()) {
                case CME_SIM_BUSY:
                    ret = UICC_BUSY;
                    break;
                case CME_SIM_NOT_INSERTED:
                    if (ESIMS_CAUSE_SIM_NO_INIT == esim_cause) {
                        ret = UICC_NO_INIT;
                    } else {
                        ret = UICC_ABSENT;
                    }
                    break;
                case CME_SIM_FAILURE:
                    ret = UICC_ABSENT;
                    break;
                case CME_SIM_WRONG: {
                    RmcSimPinPukCount *retry = getPinPukRetryCount();
                     if (retry != NULL && retry->pin1 == 0 && retry->puk1 == 0) {
                        ret = UICC_PERM_BLOCKED;  // PERM_DISABLED
                    } else {
                        ret = UICC_NOT_READY;
                    }
                    if (retry != NULL) {
                        free(retry);
                    }
                    break;
                }
                default:
                    ret = UICC_NOT_READY;
                    break;
            }
        } else {
            // Success
            line = p_response->getIntermediates();
            line->atTokStart(&err);
            if (err < 0) {
                ret = UICC_NOT_READY;
                break;
            }

            cpinResult = line->atTokNextstr(&err);
            if (err < 0) {
                ret = UICC_NOT_READY;
                break;
            }

            if (ret != UICC_NOT_READY) {
                String8 cpinStr(cpinResult);
                if (cpinStr == String8::format("SIM PIN")) {
                    ret = UICC_PIN;
                } else if (cpinStr == String8::format("SIM PUK")) {
                    ret = UICC_PUK;
                } else if (cpinStr == String8::format("PH-NET PIN") ||
                    cpinStr == String8::format("PH-NET PUK")) {
                    ret = UICC_NP;
                } else if (cpinStr == String8::format("PH-NETSUB PIN") ||
                        cpinStr == String8::format("PH-NETSUB PUK")) {
                    ret = UICC_NSP;
                } else if (cpinStr == String8::format("PH-SP PIN") ||
                        cpinStr == String8::format("PH-SP PUK")) {
                    ret = UICC_SP;
                } else if (cpinStr == String8::format("PH-CORP PIN") ||
                        cpinStr == String8::format("PH-CORP PUK")) {
                    ret = UICC_CP;
                } else if (cpinStr == String8::format("PH-FSIM PIN") ||
                        cpinStr == String8::format("PH-FSIM PUK")) {
                    ret = UICC_SIMP;
                } else if (cpinStr == String8::format("PH-NSSP PIN") ||
                        cpinStr == String8::format("PH-NSSP PUK")) {
                    ret = UICC_NS_SP;
                } else if (cpinStr == String8::format("PH-SIMC PIN") ||
                        cpinStr == String8::format("PH-SIMC PUK")) {
                    ret = UICC_SIM_C;
                } else if (cpinStr == String8::format("CARD_REBOOT")) {
                    ret = UICC_CARD_REBOOT;
                } else if (cpinStr == String8::format("CARD_RESTRICTED")) {
                    if (getMclStatusManager()->getIntValue(RFX_STATUS_KEY_CARD_TYPE) == RFX_CARD_TYPE_USIM) {
                        ret = UICC_USIM_RESTRICTED;
                    } else {
                        ret = UICC_SIM_RESTRICTED;
                    }
                } else if (cpinStr != String8::format("READY"))  {
                    /* we're treating unsupported lock types as "sim absent" */
                    ret = UICC_ABSENT;
                } else {
                    ret = UICC_READY;
                }
            }

            p_response = NULL;
        }

        if (ret == UICC_BUSY) {
            count++;  // to avoid block; if the busy time is too long; need to check modem.
            if (count == 30 || RfxRilUtils::isVsimEnabledBySlot(m_slot_id)) {
                 ret = UICC_NOT_READY;
            } else {
                 sleepMsec(200);
            }
        }
    } while (ret == UICC_BUSY);

    return ret;
}


void RmcCommSimRequestHandler::handleSetAllowedCarriers(const sp < RfxMclMessage > & msg) {
    sp<RfxAtResponse> p_response;
    sp<RfxMclMessage> response;
    int err = -1;
    String8 cmd("");
    RIL_CarrierRestrictionsWithPriority *crp = (RIL_CarrierRestrictionsWithPriority*)(
            msg->getData()->getData());
    RIL_Carrier *allowed = NULL;
    RIL_Carrier *excluded = NULL;
    int allowedCount = 0;
    int excludedCount = 0;
    UICC_Status sim_status = UICC_ABSENT;

    // 1.wait sim status
    sim_status = getSIMStatusWithRetry();

    // 2.unlock
    /* Comment as modem issue.
    p_response = atSendCommand("AT+ECRRST=0,\"12345678\"");
    err = p_response->getError();
    if (err < 0 || p_response->getSuccess() == 0) {
        logE(mTag, "handleSetAllowedCarriers AT+ECRRST=0 Fail, e= %d", err);
        err = RIL_E_GENERIC_FAILURE;
        goto error;
    } */

    // 3.Clear all
    p_response = atSendCommand("AT+ECRRST=6");
    err = p_response->getError();
    if (err < 0 || p_response->getSuccess() == 0) {
        logE(mTag, "handleSetAllowedCarriers AT+ECRRST=6 Fail, e= %d", err);
        goto error;
    }

    // 4.set multi SIM policy and prioritized.
    cmd.clear();
    logI(mTag, "handleSetAllowedCarriers MultiSimPolicy %d,  Prioritized %d",
            crp->simLockMultiSimPolicy, crp->allowedCarriersPrioritized);
    cmd.append(String8::format("AT+ECRRST=9,\"12345678\",%d,%d",
            crp->simLockMultiSimPolicy, crp->allowedCarriersPrioritized));
    p_response = atSendCommand(cmd);
    err = p_response->getError();
    if (err < 0 || p_response->getSuccess() == 0) {
        logE(mTag, "handleSetAllowedCarriers AT+ECRRST=9 Fail, e= %d", err);
        goto error;
    }

    // 5.set allowed list
    for (int i = 0; i < crp->len_allowed_carriers; i++) {
        allowed = crp->allowed_carriers + i;

        cmd.clear();
        if (strcmp(allowed->mcc, "") == 0 && strcmp(allowed->mnc, "") == 0) {
            cmd.append(String8::format("AT+ECRRST=7"));
        } else if (allowed->match_type == RIL_MATCH_ALL) {
            logI(mTag, "handleSetAllowedCarriers mcc mnc %s %s", allowed->mcc, allowed->mnc);
            cmd.append(String8::format("AT+ECRRST=2,,0,%d,\"%s%s\"",
                    allowed->match_type, allowed->mcc, allowed->mnc));
        } else {
            cmd.append(String8::format("AT+ECRRST=2,,0,%d,\"%s%s\",\"%s\"",
                    allowed->match_type, allowed->mcc, allowed->mnc, allowed->match_data));
        }
        p_response = atSendCommand(cmd);
        err = p_response->getError();
        if (err < 0 || p_response->getSuccess() == 0) {
            logE(mTag, "handleSetAllowedCarriers set white list %d Fail, e= %d", i, err);
        } else {
            allowedCount++;
        }
    }

    // 6.set excluded list
    for (int i = 0; i < crp->len_excluded_carriers; i++) {
        excluded = crp->excluded_carriers + i;

        cmd.clear();
        if (excluded->match_type == RIL_MATCH_ALL) {
            cmd.append(String8::format("AT+ECRRST=2,,1,%d,\"%s%s\"",
                    excluded->match_type, excluded->mcc, excluded->mnc));
        } else {
            cmd.append(String8::format("AT+ECRRST=2,,1,%d,\"%s%s\",\"%s\"",
                    excluded->match_type, excluded->mcc, excluded->mnc, excluded->match_data));
        }
        p_response = atSendCommand(cmd);
        err = p_response->getError();
        if (err < 0 || p_response->getSuccess() == 0) {
            logE(mTag, "handleSetAllowedCarriers set black list %d Fail, e= %d", i, err);
        } else {
            excludedCount++;
        }
    }

    /* 7.lock
    p_response = atSendCommand("AT+ECRRST=1");
    err = p_response->getError();
    if (err < 0 || p_response->getSuccess() == 0) {
        logE(mTag, "handleSetAllowedCarriers AT+ECRRST=1 Fail, e= %d", err);
        err = RIL_E_GENERIC_FAILURE;
        goto error;
    } */

    // 8.wait reboot
    sim_status = getSIMStatusWithRetry();

    // 9.Rset sim
    if ((sim_status == UICC_CARD_REBOOT) || (sim_status == UICC_USIM_RESTRICTED)
            || (sim_status == UICC_SIM_RESTRICTED)) {
        p_response = atSendCommandSingleline("AT+EBTSAP=0", "+EBTSAP:");
        err = p_response->getError();
        if (err < 0 || p_response->getSuccess() == 0) {
            logE(mTag, "handleSetAllowedCarriers AT+EBTSAP=0 Fail, e= %d", err);
            goto error;
        }

        p_response = atSendCommand("AT+EBTSAP=1");
        err = p_response->getError();
        if (err < 0 || p_response->getSuccess() == 0) {
            logE(mTag, "handleSetAllowedCarriers AT+EBTSAP=1 Fail, e= %d", err);
            goto error;
        }
    }

    // check if all sucess
    if (allowedCount < crp->len_allowed_carriers || excludedCount < crp->len_excluded_carriers) {
        goto error;
    }

    // AOSP justs request allowedCount when hidl version < 1.4.
    // totalCount = allowedCount + excludedCount;
    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxIntsData((void*)&allowedCount, sizeof(int)), msg, false);
    responseToTelCore(response);
    return;

error:
    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_REQUEST_NOT_SUPPORTED,
            RfxIntsData((void*)&allowedCount, sizeof(int)), msg, false);

    responseToTelCore(response);
}

void RmcCommSimRequestHandler::freeCarrier(RIL_Carrier *carrier, int len) {
    for(int i = 0; i < len; i++) {
        RIL_Carrier *p_cr = carrier + i;
        if (p_cr->mcc != NULL) {
            free(p_cr->mcc);
            p_cr->mcc = NULL;
        }
        if (p_cr->mnc != NULL) {
            free(p_cr->mnc);
            p_cr->mnc = NULL;
        }
        if (p_cr->match_data != NULL) {
            free(p_cr->match_data);
            p_cr->match_data = NULL;
        }
    }
    free(carrier);
}

void RmcCommSimRequestHandler::handleGetAllowedCarriers(const sp < RfxMclMessage > & msg) {
    sp<RfxMclMessage> response;
    sp<RfxAtResponse> p_response;
    int             err = -1;
    RIL_CarrierRestrictionsWithPriority *result = NULL;
    RfxAtLine *p_cur = NULL;
    int             lockstate = 0;  // 1: locked state, 2: unlocked state, 3: disable state
    int             listtype = -1;  // 0: white list, 1: black list
    int             category = -1;
    int             tmp_len = 0;
    int             allowed_tmp_len[RIL_MATCH_MAX] = {RIL_MATCH_MAX};
    int             excluded_tmp_len[RIL_MATCH_MAX] = {RIL_MATCH_MAX};
    char            *tmp;
    int             i, j;
    int             k = 0;
    int             total_allowed_len = 0;
    int             total_excluded_len = 0;
    RIL_Carrier *allowed = NULL;
    RIL_Carrier **allowed_tmp = (RIL_Carrier **)calloc(RIL_MATCH_MAX, sizeof(RIL_Carrier*));
    RFX_ASSERT(allowed_tmp != NULL);
    RIL_Carrier *excluded = NULL;
    RIL_Carrier **excluded_tmp = (RIL_Carrier **)calloc(RIL_MATCH_MAX, sizeof(RIL_Carrier*));
    RFX_ASSERT(excluded_tmp != NULL);

    logI(mTag, "handleGetAllowedCarriers IN!");
    p_response = atSendCommandMultiline("AT+ECRRST?", "+ECRRST:");
    err = p_response->getError();
    if (err < 0 || p_response->getSuccess() == 0) {
        goto error;
    }

    result = (RIL_CarrierRestrictionsWithPriority *)calloc(1, sizeof(
            RIL_CarrierRestrictionsWithPriority));
    RFX_ASSERT(result != NULL);

    p_cur = p_response->getIntermediates();
    p_cur->atTokStart(&err);
    if (err < 0) {
        goto error;
    }
    logI(mTag, "First Line Start");

    lockstate = p_cur->atTokNextint(&err);
    if (err < 0) {
        goto error;
    }
    logI(mTag, "lockstate: %d", lockstate);

    result->simLockMultiSimPolicy = p_cur->atTokNextint(&err);
    if (err < 0) {
        goto error;
    }
    logI(mTag, "simLockMultiSimPolicy: %d", result->simLockMultiSimPolicy);

    result->allowedCarriersPrioritized = p_cur->atTokNextint(&err);
    if (err < 0) {
        goto error;
    }
    logI(mTag, "allowedCarriersPrioritized: %d", result->allowedCarriersPrioritized);

    // White list
    p_cur = p_cur->getNext();
    p_cur->atTokStart(&err);
    if (err < 0) {
        goto error;
    }
    logI(mTag, "Second Line Start");

    listtype = p_cur->atTokNextint(&err);
    if (err < 0) {
        goto error;
    }
    if (listtype != 0 && listtype != 1) {
        goto error;
    }
    logI(mTag, "listtype: %d", listtype);

    // result->len_allowed_carriers = total_allowed_len;
    // allowed = calloc(total_allowed_len, sizeof(RIL_Carrier));
    for (i = 0; i < RIL_MATCH_MAX; i++) {
        category = p_cur->atTokNextint(&err);
        if (err < 0) {
            goto error;
        }
        logI(mTag, "category: %d", category);

        tmp_len = p_cur->atTokNextint(&err);
        if (err < 0) {
            goto error;
        }
        logI(mTag, "tmp_len: %d", tmp_len);

        allowed_tmp_len[i] = tmp_len;
        allowed_tmp[i] = (RIL_Carrier *)calloc(tmp_len, sizeof(RIL_Carrier));
        for (j = 0; j < tmp_len; j++) {
            RIL_Carrier *p_cr = allowed_tmp[i] + j;

            tmp = p_cur->atTokNextstr(&err);
            if (err < 0) {
                goto error;
            }
            logI(mTag, "mccmnc: %s", tmp);

            char* tmp_mcc = (char *)alloca(4);
            memset(tmp_mcc, '\0', 4);
            strncpy(tmp_mcc, tmp, 3);
            // strcat(tmp_mcc, "\0");
            logI(mTag, "tmp_mcc: %s, %zu", tmp_mcc, strlen(tmp_mcc));
            asprintf(&p_cr->mcc, "%s", tmp_mcc);
            logI(mTag, "mcc: %s", p_cr->mcc);

            char* tmp_mnc = (char *)alloca(4);
            memset(tmp_mnc, '\0', 4);
            strncpy(tmp_mnc, tmp + 3, strlen(tmp) - 3);
            logI(mTag, "tmp_mnc: %s, %zu", tmp_mcc, strlen(tmp_mcc));
            asprintf(&p_cr->mnc, "%s", tmp_mnc);
            logI(mTag, "mnc: %s", p_cr->mnc);
            p_cr->match_type = (RIL_CarrierMatchType) category;
            if (category != 0) {
                tmp = p_cur->atTokNextstr(&err);
                if (err < 0) {
                    goto error;
                }
                logI(mTag, "match_data: %s", tmp);
                asprintf(&p_cr->match_data, "%s", tmp);
            }
        }
        total_allowed_len += tmp_len;
    }

    result->len_allowed_carriers = total_allowed_len;
    result->allowed_carriers = allowed = (RIL_Carrier *)calloc(total_allowed_len,
            sizeof(RIL_Carrier));
    for (i = 0; i < RIL_MATCH_MAX; i++) {
        for (j = 0; j < allowed_tmp_len[i]; j++) {
            logI(mTag, "i:%d, j:%d", i, j);
            RIL_Carrier *p_cr = allowed_tmp[i] + j;
            logI(mTag, "*p_cur OK");
            RIL_Carrier *p_cr2 = allowed + (k++);
            logI(mTag, "*p_cur2 OK");
            asprintf(&p_cr2->mcc, "%s", p_cr->mcc);
            logI(mTag, "copy mcc OK");
            asprintf(&p_cr2->mnc, "%s", p_cr->mnc);
            logI(mTag, "copy mnc OK");
            p_cr2->match_type = p_cr->match_type;
            asprintf(&p_cr2->match_data, "%s", p_cr->match_data);
        }
    }

    if (allowed_tmp != NULL) {
        for (i = 0; i < RIL_MATCH_MAX; i++) {
           if (allowed_tmp[i] != NULL) {
               freeCarrier(allowed_tmp[i], allowed_tmp_len[i]);
               allowed_tmp[i] = NULL;
           }
        }
        free(allowed_tmp);
        allowed_tmp = NULL;
    }
    logI(mTag, "Free allowed_tmp OK");

    // Black list.
    p_cur = p_cur->getNext();
    p_cur->atTokStart(&err);
    if (err < 0) {
        goto error;
    }
    logI(mTag, "Third Line Start");

    listtype = p_cur->atTokNextint(&err);
    if (err < 0) {
        goto error;
    }
    if (listtype != 0 && listtype != 1) {
        goto error;
    }
    logI(mTag, "listtype: %d", listtype);

    // result->len_allowed_carriers = total_allowed_len;
    // allowed = calloc(total_allowed_len, sizeof(RIL_Carrier));
    for (i = 0; i < RIL_MATCH_MAX; i++) {
        category = p_cur->atTokNextint(&err);
        if (err < 0) {
            goto error;
        }
        logI(mTag, "category: %d", category);

        tmp_len = p_cur->atTokNextint(&err);
        if (err < 0) {
            goto error;
        }
        logI(mTag, "tmp_len: %d", tmp_len);

        excluded_tmp_len[i] = tmp_len;
        excluded_tmp[i] = (RIL_Carrier *)calloc(tmp_len, sizeof(RIL_Carrier));
        for (j = 0; j < tmp_len; j++) {
            RIL_Carrier *p_cr = excluded_tmp[i] + j;

            tmp = p_cur->atTokNextstr(&err);
            if (err < 0) {
                goto error;
            }
            logI(mTag, "mccmnc: %s", tmp);

            char* tmp_mcc = (char *)alloca(4);
            memset(tmp_mcc, '\0', 4);
            strncpy(tmp_mcc, tmp, 3);
            // strcat(tmp_mcc, "\0");
            logI(mTag, "tmp_mcc: %s, %zu", tmp_mcc, strlen(tmp_mcc));
            asprintf(&p_cr->mcc, "%s", tmp_mcc);
            logI(mTag, "mcc: %s", p_cr->mcc);

            char* tmp_mnc = (char *)alloca(4);
            memset(tmp_mnc, '\0', 4);
            strncpy(tmp_mnc, tmp + 3, strlen(tmp) - 3);
            // strcat(tmp_mnc, "\0");
            logI(mTag, "tmp_mnc: %s, %zu", tmp_mcc, strlen(tmp_mcc));
            asprintf(&p_cr->mnc, "%s", tmp_mnc);
            logI(mTag, "mnc: %s", p_cr->mnc);
            p_cr->match_type = (RIL_CarrierMatchType) category;
            if (category != 0) {
                tmp = p_cur->atTokNextstr(&err);
                if (err < 0) {
                    goto error;
                }
                logI(mTag, "match_data: %s", tmp);
                asprintf(&p_cr->match_data, "%s", tmp);
            }
        }
        total_excluded_len += tmp_len;
    }

    result->len_excluded_carriers = total_excluded_len;
    result->excluded_carriers = excluded = (RIL_Carrier *) calloc(total_excluded_len,
            sizeof(RIL_Carrier));
    for (i = 0; i < RIL_MATCH_MAX; i++) {
        for (j = 0; j < excluded_tmp_len[i]; j++) {
            logI(mTag, "i:%d, j:%d", i, j);
            RIL_Carrier *p_cr = excluded_tmp[i] + j;
            logI(mTag, "*p_cur OK");
            RIL_Carrier *p_cr2 = excluded + (k++);
            logI(mTag, "*p_cur2 OK");
            asprintf(&p_cr2->mcc, "%s", p_cr->mcc);
            logI(mTag, "copy mcc OK");
            asprintf(&p_cr2->mnc, "%s", p_cr->mnc);
            logI(mTag, "copy mnc OK");
            p_cr2->match_type = p_cr->match_type;
            asprintf(&p_cr2->match_data, "%s", p_cr->match_data);
        }
    }

    if (excluded_tmp != NULL) {
        for (i = 0; i < RIL_MATCH_MAX; i++) {
           if (excluded_tmp[i] != NULL) {
               freeCarrier(excluded_tmp[i], excluded_tmp_len[i]);
               excluded_tmp[i] = NULL;
           }
        }
        free(excluded_tmp);
        excluded_tmp = NULL;
    }
    logI(mTag, "Free excluded_tmp OK");
    logI(mTag, "Black list OK");

    logI(mTag, "handleGetAllowedCarriers: allowed_len %d, excluded len %d",
         result->len_allowed_carriers, result->len_excluded_carriers);
    for (int i = 0; i < result->len_allowed_carriers; i++) {
        allowed = result->allowed_carriers + i;
        logI(mTag, "allowed mcc %s, mnc %s, match_type %d, match_data %s",
                allowed->mcc, allowed->mnc, allowed->match_type, allowed->match_data);
    }
    for (int i = 0; i < result->len_excluded_carriers; i++) {
        excluded = result->excluded_carriers + i;
        logI(mTag, "excluded mcc %s, mnc %s, match_type %d, match_data %s",
                excluded->mcc, excluded->mnc, excluded->match_type, excluded->match_data);
    }

    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS, RfxSimCarrRstData(
            (void*)result, sizeof(RIL_CarrierRestrictionsWithPriority)), msg, false);
    responseToTelCore(response);

    freeCarrier(result->allowed_carriers, result->len_allowed_carriers);
    result->allowed_carriers = NULL;
    freeCarrier(result->excluded_carriers, result->len_excluded_carriers);
    result->excluded_carriers = NULL;
    free(result);
    result = NULL;
    return;

error:
    if (allowed_tmp != NULL) {
        for (i = 0; i < RIL_MATCH_MAX; i++) {
           if (allowed_tmp[i] != NULL) {
               freeCarrier(allowed_tmp[i], allowed_tmp_len[i]);
               allowed_tmp[i] = NULL;
           }
        }
        free(allowed_tmp);
        allowed_tmp = NULL;
    }
    if (excluded_tmp != NULL) {
        for (i = 0; i < RIL_MATCH_MAX; i++) {
           if (excluded_tmp[i] != NULL) {
               freeCarrier(excluded_tmp[i], excluded_tmp_len[i]);
               excluded_tmp[i] = NULL;
           }
        }
        free(excluded_tmp);
        excluded_tmp = NULL;
    }
    if (result != NULL) {
        freeCarrier(result->allowed_carriers, result->len_allowed_carriers);
        result->allowed_carriers = NULL;
        freeCarrier(result->excluded_carriers, result->len_excluded_carriers);
        result->excluded_carriers = NULL;
        free(result);
        result = NULL;
    }
    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_REQUEST_NOT_SUPPORTED,
            RfxVoidData(), msg, false);
    responseToTelCore(response);
}

bool RmcCommSimRequestHandler::isRjioRsuSupport() {
    char property_value[RFX_PROPERTY_VALUE_MAX] = {0};
    char property_value_standalone[RFX_PROPERTY_VALUE_MAX] = {0};

    rfx_property_get("vendor.gsm.sim.slot.lock.policy", property_value, "0");
    rfx_property_get("ro.vendor.mtk_subsidy_lock_support", property_value_standalone, "0");

    if ((atoi(property_value) == 10) || (atoi(property_value_standalone) == 1)) {
        return true;
    }
    return false;
}

void RmcCommSimRequestHandler::handleActiveUiccCard(const sp<RfxMclMessage>& msg) {
    sp<RfxAtResponse> p_response;
    sp<RfxMclMessage> response;
    int err = RIL_E_SUCCESS;
    int simPowerStateErrNumber = SIM_POWER_STATE_SUCCESS;
    String8 cmd("");

    if (getMclStatusManager()->getIntValue(RFX_STATUS_KEY_CARD_TYPE) == 0) {
        simPowerStateErrNumber = SIM_POWER_STATE_GENERIC_FAILURE;
        err = RIL_E_SIM_ABSENT;
    } else if (getMclStatusManager()->getIntValue(RFX_STATUS_KEY_SIM_ONOFF_STATE)
            == SIM_POWER_STATE_SIM_ON) {
       err = RIL_E_SUCCESS;
       simPowerStateErrNumber = SIM_POWER_STATE_SUCCESS;
    } else if (getMclStatusManager()->getIntValue(RFX_STATUS_KEY_SIM_ONOFF_SWITCHING_STATE)
            == SIM_POWER_STATE_SIM_SWITCHING_ON) {
        err = RIL_E_REQUEST_RATE_LIMITED;
        simPowerStateErrNumber = SIM_POWER_STATE_REQUEST_IN_PROCESS;
    } else {
        cmd.append(String8::format("AT+ESIMPOWER=%d", SIM_POWER_STATE_SIM_ON));
        p_response = atSendCommand(cmd);
        getMclStatusManager()->setIntValue(RFX_STATUS_KEY_SIM_ONOFF_SWITCHING_STATE,
                    SIM_POWER_STATE_SIM_SWITCHING_ON);

        if (p_response->getSuccess() == 0) {
            simPowerStateErrNumber = SIM_POWER_STATE_GENERIC_FAILURE;
            switch (p_response->atGetCmeError()) {
                case CME_OPERATION_NOT_ALLOWED_ERR:
                    err = RIL_E_OPERATION_NOT_ALLOWED;
                    break;
                case CME_SIM_NOT_INSERTED:
                    err = RIL_E_SIM_ABSENT;
                    break;
                default:
                    err = RIL_E_OPERATION_NOT_ALLOWED;
                    break;
            }
        }
    }

    response = RfxMclMessage::obtainResponse(msg->getId(), (RIL_Errno)err,
            RfxIntsData(&simPowerStateErrNumber, 1), msg, false);
    responseToTelCore(response);
}

void RmcCommSimRequestHandler::handleDeactivateUiccCard(const sp<RfxMclMessage>& msg) {
    sp<RfxAtResponse> p_response;
    sp<RfxMclMessage> response;
    int err = RIL_E_SUCCESS;
    int simPowerStateErrNumber = SIM_POWER_STATE_SUCCESS;
    String8 cmd("");

    if (getMclStatusManager()->getIntValue(RFX_STATUS_KEY_CARD_TYPE) == 0) {
        simPowerStateErrNumber = SIM_POWER_STATE_GENERIC_FAILURE;
        err = RIL_E_SIM_ABSENT;
    } else if (getMclStatusManager()->getIntValue(RFX_STATUS_KEY_SIM_ONOFF_STATE)
            == SIM_POWER_STATE_SIM_OFF) {
       err = RIL_E_SUCCESS;
       simPowerStateErrNumber = SIM_POWER_STATE_SUCCESS;
    } else if (getMclStatusManager()->getIntValue(RFX_STATUS_KEY_SIM_ONOFF_SWITCHING_STATE)
            == SIM_POWER_STATE_SIM_SWITCHING_OFF) {
        err = RIL_E_REQUEST_RATE_LIMITED;
        simPowerStateErrNumber = SIM_POWER_STATE_REQUEST_IN_PROCESS;
    } else {
        cmd.append(String8::format("AT+ESIMPOWER=%d", SIM_POWER_STATE_SIM_OFF));
        p_response = atSendCommand(cmd);
        getMclStatusManager()->setIntValue(RFX_STATUS_KEY_SIM_ONOFF_SWITCHING_STATE,
                    SIM_POWER_STATE_SIM_SWITCHING_OFF);

        if (p_response->getSuccess() == 0) {
            simPowerStateErrNumber = SIM_POWER_STATE_GENERIC_FAILURE;
            switch (p_response->atGetCmeError()) {
                case CME_OPERATION_NOT_ALLOWED_ERR:
                    err = RIL_E_OPERATION_NOT_ALLOWED;
                    break;
                case CME_SIM_NOT_INSERTED:
                    err = RIL_E_SIM_ABSENT;
                    break;
                default:
                    err = RIL_E_OPERATION_NOT_ALLOWED;
                    break;
            }
        }
    }

    response = RfxMclMessage::obtainResponse(msg->getId(), (RIL_Errno)err,
            RfxIntsData(&simPowerStateErrNumber, 1), msg, false);
    responseToTelCore(response);
}

/**
 * Convert the PersoSubState defined in IRadio to cat in +ESMLCK
 * perso_substate: value of PersoSubState
 * return: cat
 *         -1  -- not supported PersoSubState
 */
int RmcCommSimRequestHandler::convertPersoStateToCat(int perso_substate) {
    int cat = -1;
    switch (perso_substate) {
        case SIM_NETWORK:
        case SIM_NETWORK_PUK:
            cat = 0;
            break;
        case SIM_NETWORK_SUBSET:
        case SIM_NETWORK_SUBSET_PUK:
            cat = 1;
            break;
        case SIM_SERVICE_PROVIDER:
        case SIM_SERVICE_PROVIDER_PUK:
            cat = 2;
            break;
        case SIM_CORPORATE:
        case SIM_CORPORATE_PUK:
            cat = 3;
            break;
        case SIM_SIM:
        case SIM_SIM_PUK:
            cat = 4;
            break;
        case SIM_NS_SP:
        case SIM_NS_SP_PUK:
            cat = 5;
            break;
        case SIM_SIM_C:
        case SIM_SIM_C_PUK:
            cat = 6;
            break;
        default:
            break;

    };
    return cat;
}

/**
 * Get remaining retry count
 * @cat -- category in +ESMCLK
 * @pOutput -- if not NULL, return result of +ESMCLK.
 *
 * return: >=0 : remaining retry count
 *         -1 : unknown
 */
int RmcCommSimRequestHandler::getPersoRemainRetry(int cat, RIL_SimMeLockInfo *pOutput) {
    int retryCount = -1;
    String8 cmd("");
    int err = -1;
    sp<RfxMclMessage> response;
    sp<RfxAtResponse> p_response = NULL;
    RfxAtLine *line = NULL;
    RIL_SimMeLockInfo result;
    char *value;

    if (cat < 0 || cat >= MAX_SIM_ME_LOCK_CAT_NUM) {
        logE(mTag, "getPersoRemainRetry: invalid cat %d", cat);
        return retryCount;
    }

    memset(&result, 0, sizeof(RIL_SimMeLockInfo));
    // Query retry count
    do {
        cmd.append(String8::format("AT+ESMLCK"));
        p_response = atSendCommandSingleline(cmd, "+ESMLCK:");
        cmd.clear();
        err = p_response->getError();
        if (err < 0 || p_response->getSuccess() == 0) {
            logE(mTag, "getPersoRemainRetry AT+ESMLCK error!");
            break;
        }
        line = p_response->getIntermediates();
        line->atTokStart(&err);
        if (err < 0) {
            logE(mTag, "getPersoRemainRetry atTokStart error!");
            break;
        }

        int limit = pOutput == NULL ? cat : (MAX_SIM_ME_LOCK_CAT_NUM - 1);
        for (int i = 0; i <= limit; i++) {
            value = line->atTokChar(&err);
            if (err < 0) {
                logE(mTag, "getPersoRemainRetry parse entry %d error!", i);
                break;
            }
            result.catagory[i].catagory = line->atTokNextint(&err);
            if (err < 0) {
                logE(mTag, "getPersoRemainRetry parse entry %d error!", i);
                break;
            }
            result.catagory[i].state = line->atTokNextint(&err);
            if (err < 0) {
                logE(mTag, "getPersoRemainRetry parse entry %d error!", i);
                break;
            }
            result.catagory[i].retry_cnt = line->atTokNextint(&err);
            if (err < 0) {
                logE(mTag, "getPersoRemainRetry parse entry %d error!", i);
                break;
            }
            result.catagory[i].autolock_cnt = line->atTokNextint(&err);
            if (err < 0) {
                logE(mTag, "getPersoRemainRetry parse entry %d error!", i);
                break;
            }
            result.catagory[i].num_set = line->atTokNextint(&err);
            if (err < 0) {
                logE(mTag, "getPersoRemainRetry parse entry %d error!", i);
                break;
            }
            result.catagory[i].total_set = line->atTokNextint(&err);
            if (err < 0) {
                logE(mTag, "getPersoRemainRetry parse entry %d error!", i);
                break;
            }
            result.catagory[i].key_state = line->atTokNextint(&err);
            if (err < 0) {
                logE(mTag, "getPersoRemainRetry parse entry %d error!", i);
                break;
            }
        }

        if (err >= 0) {
            retryCount = result.catagory[cat].retry_cnt;
            logD(mTag, "getPersoRemainRetry retryCount = %d", retryCount);
        }
     } while (0);

    if (pOutput != NULL) {
        memcpy(pOutput, &result, sizeof(result));
    }

     return retryCount;
}

/*
 * AT+ESMLCK = <cat>, <op>
 * [,<key> [,<data_imsi> [,<data_gid1> [, <data_gid2>]]]]
 *
 * <cat> Integer type
 *  0: Network
 *  1: Network subset
 *  2: Service Provider
 *  3: Corporate
 *  4: SIM
 *  5: SIM NS SP
 *  6: SIM C
 * <op> Integer type
 *  0: Unlock a category
 *  1: Lock a category
 *  2: Add data for a category
 *  3: Remove data for a category
 *  4: Permanently unlock a category (Disable)
 */

void RmcCommSimRequestHandler::handleEnterSimDepersonalization(const sp<RfxMclMessage>& msg) {
    String8 cmd("");
    int err = -1;
    RIL_Errno ret = RIL_E_INTERNAL_ERR;
    sp<RfxMclMessage> response;
    sp<RfxAtResponse> p_response = NULL;
    UICC_Status sim_status;
    char** strings = (char**)(msg->getData()->getData());
    char* key = NULL;
    int retryCount = -1;
    int persoSubState = 0;
    int cat = 0;
    //[personSubState, remainingCount]
    int responseData[2];

    if (strings == NULL || strings[0] == NULL || strings[1] == NULL) {
         ret = RIL_E_INVALID_ARGUMENTS;
         logD(mTag, "handleEnterSimDepersonalization invalid arguments.");
         goto error;
    }

    // strings[0]: netpin
    // strings[1]: persoSubState
    sim_status = getSimStatus();
    logD(mTag, "handleEnterSimDepersonalization netpin : ***, persoSubState : %s, status: %d",
            strings[1], sim_status);
    key = (strings[0] == NULL) ? (char*)"" : (char*)strings[0];
    persoSubState = atoi(strings[1]);
    if (persoSubState < SIM_NETWORK || persoSubState > SIM_SIM_C_PUK) {
         ret = RIL_E_INVALID_ARGUMENTS;
         logD(mTag, "handleEnterSimDepersonalization invalid arguments.");
         goto error;
    }
    cat = convertPersoStateToCat(persoSubState);
    if (cat < 0) {
        ret = RIL_E_REQUEST_NOT_SUPPORTED;
        logE(mTag, "not support persoSubState = %d", persoSubState);
        goto error;
    }

    // Sim status will update on the current lock is depersonalized.
    if ((UICC_NP == sim_status && (persoSubState == SIM_NETWORK)) ||
            (UICC_NSP == sim_status && (persoSubState == SIM_NETWORK_SUBSET))  ||
            (UICC_SP == sim_status && (persoSubState == SIM_SERVICE_PROVIDER)) ||
            (UICC_CP == sim_status && (persoSubState == SIM_CORPORATE)) ||
            (UICC_SIMP == sim_status && (persoSubState == SIM_SIM)) ||
            (UICC_SIM_C == sim_status && (persoSubState == SIM_SIM_C)) ||
            (UICC_NS_SP == sim_status && (persoSubState == SIM_NS_SP))) {
        logI(mTag, "handleEnterSimDepersonalization: unlock current locked cat!");
    }
    /*
     * We use CPIN to unlock sim me lock. This method can only unlock the cat
     * modem selected. Unlock may fail if the spedified cat is not identical with
     * modem selected.
     */
    cmd.append(String8::format("AT+CPIN=\"%s\"", key));
    p_response = atSendCommand(cmd.string());
    cmd.clear();

    if (p_response == NULL) {
        ret = RIL_E_SYSTEM_ERR;
        logE(mTag, "p_response is NULL");
        goto error;
    }
    logD(mTag, "network lock command sent.");
    err = p_response->getError();
    if (err < 0) {
        logE(mTag, "err = %d", err);
        goto error;
    }

    if (p_response->getSuccess() == 0) {
        logE(mTag, "p_response err = %d", p_response->atGetCmeError());
        switch (p_response->atGetCmeError()) {
            case CME_NETWORK_PERSONALIZATION_PUK_REQUIRED:
            case CME_INCORRECT_PASSWORD:
                ret = RIL_E_PASSWORD_INCORRECT;
                break;

            case CME_NETWORK_SUBSET_PERSONALIZATION_PIN_REQUIRED:
            case CME_SERVICE_PROVIDER_PERSONALIZATION_PIN_REQUIRED:
            case CME_CORPORATE_PERSONALIZATION_PIN_REQUIRED:
            case CME_PH_FSIM_PIN_REQUIRED:
            case CME_LINK_NS_SP_PIN_REQUIRED:
            case CME_LINK_SIM_C_PIN_REQUIRED:
                ret = RIL_E_SUCCESS;
                break;

            case CME_NETWORK_SUBSET_PERSONALIZATION_PUK_REQUIRED:
                if (UICC_NP == sim_status) {
                    ret = RIL_E_SUCCESS;
                } else if (UICC_NSP == sim_status) {
                    ret = RIL_E_PASSWORD_INCORRECT;
                }
                break;

            case CME_SERVICE_PROVIDER_PERSONALIZATION_PUK_REQUIRED:
                if (UICC_NP == sim_status || UICC_NSP == sim_status) {
                    ret = RIL_E_SUCCESS;
                } else if (UICC_SP == sim_status) {
                    ret = RIL_E_PASSWORD_INCORRECT;
                }
                break;

            case CME_CORPORATE_PERSONALIZATION_PUK_REQUIRED:
                if (UICC_NP == sim_status ||
                    UICC_NSP == sim_status ||
                    UICC_SP == sim_status) {
                    ret = RIL_E_SUCCESS;
                } else if (UICC_CP == sim_status) {
                    ret = RIL_E_PASSWORD_INCORRECT;
                }
                break;

            case CME_PH_FSIM_PUK_REQUIRED:
                if (UICC_NP == sim_status ||
                    UICC_NSP == sim_status ||
                    UICC_SP == sim_status ||
                    UICC_CP == sim_status) {
                    ret = RIL_E_SUCCESS;
                } else if (UICC_SIMP == sim_status) {
                    ret = RIL_E_PASSWORD_INCORRECT;
                }
                break;

            case CME_LINK_NS_SP_PUK_REQUIRED:
                if (UICC_NP == sim_status ||
                    UICC_NSP == sim_status ||
                    UICC_SP == sim_status ||
                    UICC_CP == sim_status ||
                    UICC_SIMP == sim_status) {
                    ret = RIL_E_SUCCESS;
                } else if (UICC_NS_SP == sim_status) {
                    ret = RIL_E_PASSWORD_INCORRECT;
                }
                break;

            case CME_LINK_SIM_C_PUK_REQUIRED:
                if (UICC_NP == sim_status ||
                    UICC_NSP == sim_status ||
                    UICC_SP == sim_status ||
                    UICC_CP == sim_status ||
                    UICC_SIMP == sim_status ||
                    UICC_NS_SP == sim_status) {
                    ret = RIL_E_SUCCESS;
                } else if (UICC_SIM_C == sim_status) {
                    ret = RIL_E_PASSWORD_INCORRECT;
                }
                break;
            case CME_OPERATION_NOT_ALLOWED_ERR:
            case CME_OPERATION_NOT_SUPPORTED:
            case CME_UNKNOWN:
                logE(mTag, "Unknow error");
                break;
            case CME_SUCCESS:
                /* While p_response->success is 0, the CME_SUCCESS means CME ERROR:0 => it is phone failure */
                goto error;
            default:
                sendSimStatusChanged();
                goto error;
        }
    } else {
        sendSimStatusChanged();
        ret = RIL_E_SUCCESS;
    }

error:
    logE(mTag, "handleEnterSimDepersonalization return ret = %d", ret);
    retryCount = getPersoRemainRetry(cat, NULL);
    responseData[0] = persoSubState;
    responseData[1] = retryCount;
    response = RfxMclMessage::obtainResponse(msg->getId(), ret,
            RfxIntsData((void*)&responseData, sizeof(responseData)), msg, false);
    responseToTelCore(response);
}

void RmcCommSimRequestHandler::handleEventResetSim(const sp < RfxMclMessage > & msg) {
    String8 cmd("");
    int err = -1;
    sp<RfxAtResponse> p_response1 = NULL;
    sp<RfxAtResponse> p_response2 = NULL;
    logD(mTag, "handleEventResetSim...\n");

    RFX_UNUSED(msg);
    cmd.append(String8::format("AT+EBTSAP=0"));
    p_response1 = atSendCommand(cmd.string());
    err = p_response1->getError();
    if (err < 0 || p_response1->getSuccess() == 0) {
        logE(mTag, "AT+EBTSAP=0 Fail");
    }
    cmd.clear();

    cmd.append(String8::format("AT+EBTSAP=1"));
    p_response2 = atSendCommand(cmd.string());
    err = p_response2->getError();
    if (err < 0 || p_response2->getSuccess() == 0) {
        logE(mTag, "AT+EBTSAP=1 Fail");
    }
    cmd.clear();
}

/********** RSU operation *********/
void RmcCommSimRequestHandler::handleRsuRequest(const sp<RfxMclMessage>& msg) {
    RIL_RsuRequest* request = (RIL_RsuRequest*)(msg->getData()->getData());
    logD(mTag, "[RSU-SIMLOCK] handleRsuRequest opId = %d, requestId = %d",
            request->opId, request->requestId);

    switch(request->opId) {
        case RSU_OP_VZW:
            handleVzwRsuRequest(msg);
            return;
        case RSU_OP_KDDI:
            handleKDDIRsuRequest(msg);
            return;
        case RSU_OP_TMO:
            handleTmoRsuRequest(msg);
            return;
        case RSU_OP_TFN:
            handleTfnRsuRequest(msg);
            return;
        case RSU_OP_SPRINT_LEGACY:
            handleSprintRsuRequest(msg);
            return;
        case RSU_OP_COMMON:
            handleCommonRsuRequest(msg);
            return;
        default:
            break;
    }

    sp<RfxMclMessage> mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
                    RIL_E_GENERIC_FAILURE, RfxVoidData(), msg);
    responseToTelCore(mclResponse);
}

void RmcCommSimRequestHandler::handleKDDIRsuRequest(const sp<RfxMclMessage>& msg) {
    RIL_RsuRequest* request = (RIL_RsuRequest*)(msg->getData()->getData());

    switch(request->requestId) {
        case RSU_REQUEST_SET_SIM_LOCK_DATA:
            handleKDDIRsuSetSimLockData(msg);
            return;
        case RSU_REQUEST_SET_GET_ALLOWED_LOCK_DATA:
        case RSU_REQUEST_SET_GET_EXCLUDED_LOCK_DATA:
            handleKDDIRsuGetLockData(msg, request->requestId);
            return;
        default:
            break;
    }

    sp<RfxMclMessage> mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
                    RIL_E_REQUEST_NOT_SUPPORTED, RfxVoidData(), msg);
    responseToTelCore(mclResponse);
}

#define KDDI_MAX_LOCK_DATA_CHAR 400
void RmcCommSimRequestHandler::handleKDDIRsuSetSimLockData(const sp<RfxMclMessage>& msg) {
    int err = 0;
    int errCode = 0;

    String8 cmd("");
    sp<RfxAtResponse> atResponse;
    sp<RfxMclMessage> mclResponse;

    int requestId = RSU_MODEM_REQUEST_SET_LOCK_DATA_MORE;
    int offset = 0, length = 0;
    char* lock_data = NULL;
    char* cuttent_data = NULL;

    RIL_RsuRequest* request = (RIL_RsuRequest*)(msg->getData()->getData());
    RIL_RsuResponse* response = (RIL_RsuResponse*)calloc(1, sizeof(RIL_RsuResponse));

    int data_size = (request->data != NULL ? strlen(request->data) : 0);

    RFX_ASSERT(response != NULL);
    response->opId = request->opId;
    response->requestId = request->requestId;

    logD(mTag, "[RSU-SIMLOCK] handleKDDIRsuSetSimLockData opId = %d, requestId = %d, data_size = %d",
            request->opId, requestId, data_size);
    cuttent_data = request->data;
    do {
        cuttent_data = cuttent_data + length;
        if (KDDI_MAX_LOCK_DATA_CHAR <= data_size) {
            length = KDDI_MAX_LOCK_DATA_CHAR;
        } else {
            requestId = RSU_MODEM_REQUEST_SET_LOCK_DATA_DONE;
            length = data_size;
        }
        logD(mTag, "[RSU-SIMLOCK] requestId %d, length %d, offset %d", requestId, data_size, offset);
        lock_data = (char*)calloc(1, length + 1);
        RFX_ASSERT(lock_data != NULL);
        strncpy(lock_data, cuttent_data, length);

        cmd.clear();
        cmd.append(String8::format("AT+ESMLRSU=%d,%d,%d,%d,\"%s\"",
                request->opId, requestId, offset, length, lock_data));
        logD(mTag, "[RSU-SIMLOCK]AT+ESMLRSU=%d,%d,%d,%d", request->opId, requestId, offset, length);
        printReducedLog("[RSU-SIMLOCK]  AT+ESMLRSU request ", lock_data);
#ifdef SML_UT_TEST
        atResponse = smlSendAtSingleLine(cmd, "+ESMLRSU:");
#else
        atResponse = atSendCommand(cmd);
#endif
        free(lock_data);
        if (atResponse == NULL) {
            logE(mTag, "[RSU-SIMLOCK] atResponse is null");
            goto error;
        }

        err = atResponse->getError();
        if (err < 0) {
            logE(mTag, "[RSU-SIMLOCK] err = %d", err);
            goto error;
        }

        if (atResponse->getSuccess() == 0) {
            errCode = atResponse->atGetCmeError();
            logE(mTag, "[RSU-SIMLOCK] errCode = %d", errCode);
            // We get error cause 271 means the SIM Lock data is correct and save to nvram.
            if (errCode == CME_REBOOT_REQUEST) {
                break;
            } else {
                goto error;
            }
        }
        data_size = data_size - length;
        offset = offset + (length / 2);
        logD(mTag, "[RSU-SIMLOCK] data_size %d, %d", data_size, offset);
    } while (data_size > 0);

    mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
            RIL_E_SUCCESS, RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
    responseToTelCore(mclResponse);
    free(response);
    return;

error:
    free(response);
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
            RIL_E_GENERIC_FAILURE, RfxVoidData(), msg);
    responseToTelCore(mclResponse);
}

void RmcCommSimRequestHandler::handleKDDIRsuGetLockData(const sp<RfxMclMessage>& msg,
        int requestId) {
    int err = 0;
    int errCode = 0;

    String8 cmd("");
    sp<RfxAtResponse> atResponse;
    sp<RfxMclMessage> mclResponse;
    RfxAtLine *p_cur = NULL;

    int category = 0, triplet_length = 0;
    RIL_RsuRequest* request = (RIL_RsuRequest*)(msg->getData()->getData());
    RIL_RsuResponse* response = (RIL_RsuResponse*)calloc(1, sizeof(RIL_RsuResponse));
    int sim_lock_group = 1; // 1: white list, 2: black list
    char* IMSI = NULL;
    char* GID1 = NULL;
    char* GID2 = NULL;
    char* temp_data = NULL;
    char* tmp_buffer1 = NULL;
    char* tmp_buffer2 = NULL;

    RFX_ASSERT(response != NULL);
    response->opId = request->opId;
    response->requestId = request->requestId;

    if (requestId == RSU_REQUEST_SET_GET_EXCLUDED_LOCK_DATA) {
        sim_lock_group = 2;
    }

    cmd.append(String8::format("AT+ESMLRSU=%d,%d,%d",
            request->opId, RSU_MODEM_REQUEST_GET_LOCK_DATA, sim_lock_group));
    logD(mTag, "[RSU-SIMLOCK] AT+ESMLRSU=%d,%d,%d", request->opId, RSU_MODEM_REQUEST_GET_LOCK_DATA,
            sim_lock_group);
#ifdef SML_UT_TEST
    atResponse = smlSendAtSingleLine(cmd,  "+ESMLRSU:");
#else
    atResponse = atSendCommandMultiline(cmd, "+ESMLRSU:");
#endif
    if (atResponse == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleKDDIRsuGetLockData atResponse is null");
        goto error;
    }

    if (atResponse->isAtResponseFail()) {
        errCode = atResponse->atGetCmeError();
        logE(mTag, "[RSU-SIMLOCK] handleKDDIRsuGetLockData errCode = %d", errCode);
        response->errCode = errCode;
        mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
                RIL_E_GENERIC_FAILURE,
                RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
        responseToTelCore(mclResponse);
        free(response);
        return;
    }

    for (p_cur = atResponse->getIntermediates()
            ; p_cur != NULL
            ; p_cur = p_cur->getNext()) {
        p_cur->atTokStart(&err);
        if (err < 0) {
            logE(mTag, "[RSU-SIMLOCK] handleKDDIRsuGetLockData atTokStart error");
            goto error;
        }

        category = p_cur->atTokNextint(&err);
        if (err < 0) {
            logE(mTag, "[RSU-SIMLOCK] handleKDDIRsuGetLockData get category error");
            goto error;
        }
        triplet_length = p_cur->atTokNextint(&err);
        if (err < 0) {
            logE(mTag, "[RSU-SIMLOCK] handleKDDIRsuGetLockData get triplet_length error");
            goto error;
        }

        char category_str[2] = {0};
        sprintf(category_str, "%d", category);
        for (int i = 0; i < triplet_length; i++) {
            IMSI = p_cur->atTokNextstr(&err);
            if (err < 0) {
                logE(mTag, "[RSU-SIMLOCK] get IMSI error.");
                goto error;
            }
            GID1 = p_cur->atTokNextstr(&err);
            if (err < 0) {
                logE(mTag, "[RSU-SIMLOCK] get GID1 error.");
                goto error;
            }
            GID2 = p_cur->atTokNextstr(&err);
            if (err < 0) {
                logE(mTag, "[RSU-SIMLOCK] get GID2 error.");
                goto error;
            }
            //Construct IMSI:GID1:GID2,IMSI:GID1:GID2,...
            asprintf(&temp_data,"%s:%s:%s:%s", category_str, IMSI, GID1, GID2);
            if (temp_data == NULL) {
                logE(mTag, "[RSU-SIMLOCK] get temp_data error.");
                goto error;
            }
            logD(mTag, "[RSU-SIMLOCK] temp_data %s", temp_data);
            if (tmp_buffer1 == NULL) {
                tmp_buffer1 = (char*)calloc(1, (strlen(temp_data) * sizeof(char)) + 2);
                RFX_ASSERT(tmp_buffer1 != NULL);
                strncpy(tmp_buffer1, temp_data, strlen(temp_data));
            } else {
                tmp_buffer2 = (char*)calloc(1, ((strlen(tmp_buffer1) + strlen(temp_data)) * sizeof(char)) + 2);
                RFX_ASSERT(tmp_buffer2 != NULL);
                strncpy(tmp_buffer2, tmp_buffer1, strlen(tmp_buffer1));
                strncat(tmp_buffer2, ",", 1);
                strncat(tmp_buffer2, temp_data, strlen(temp_data));
                free(tmp_buffer1);
                tmp_buffer1 = tmp_buffer2;
            }
            if (temp_data != NULL) {
                free(temp_data);
                temp_data = NULL;
            }
            logD(mTag, "[RSU-SIMLOCK] handleKDDIRsuGetLockData tmp_buffer1 %s, tmp_buffer2 %s",
                    tmp_buffer1, tmp_buffer2);
        }
    }
    response->data = tmp_buffer1;
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
            RIL_E_SUCCESS, RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
    responseToTelCore(mclResponse);
    free(tmp_buffer1);
    free(response);
    return;

error:
    free(response);
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
            RIL_E_GENERIC_FAILURE, RfxVoidData(), msg);
    responseToTelCore(mclResponse);
}

void RmcCommSimRequestHandler::handleVzwRsuRequest(const sp<RfxMclMessage>& msg) {
    RIL_RsuRequest* request = (RIL_RsuRequest*)(msg->getData()->getData());

    switch(request->requestId) {
        case RSU_REQUEST_INIT_REQUEST:
            handleVzwRsuInitiate(msg);
            return;
        case RSU_REQUEST_GET_SHARED_KEY:
            handleVzwRsuGetSharedKey(msg);
            return;
        case RSU_REQUEST_UPDATE_LOCK_DATA:
            handleVzwRsuUpdateLockData(msg);
            return;
        case RSU_REQUEST_GET_LOCK_VERSION:
            handleVzwRsuGetVersion(msg);
            return;
        case RSU_REQUEST_GET_LOCK_STATUS:
            handleVzwRsuGetStatus(msg);
            return;
        case RSU_REQUEST_UNLOCK_TIMER:
            handleVzwRsuUnlockTimer(msg);
            return;
        default:
            break;
    }

    sp<RfxMclMessage> mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
                    RIL_E_GENERIC_FAILURE, RfxVoidData(), msg);
    responseToTelCore(mclResponse);
}

void RmcCommSimRequestHandler::handleVzwRsuInitiate(const sp<RfxMclMessage>& msg) {
    int err = 0;
    int errCode = 0;

    String8 cmd("");
    RfxAtLine *pLine = NULL;
    sp<RfxAtResponse> atResponse;
    sp<RfxMclMessage> mclResponse;

    int opId = -1;
    int requestId = -1;
    char* generateRequest = NULL;

    RIL_RsuRequest* request = (RIL_RsuRequest*)(msg->getData()->getData());
    RIL_RsuResponse* response = (RIL_RsuResponse*)calloc(1, sizeof(RIL_RsuResponse));
    RFX_ASSERT(response != NULL);
    response->opId = request->opId;
    response->requestId = request->requestId;

    cmd.append(String8::format("AT+ESMLRSU=%d,%d", request->opId, RSU_MODEM_REQUEST_INIT_REQUEST));
    logD(mTag, "[RSU-SIMLOCK] AT+ESMLRSU=%d,%d", request->opId, RSU_MODEM_REQUEST_INIT_REQUEST);
#ifdef SML_UT_TEST
    atResponse = smlSendAtSingleLine(cmd, "+ESMLRSU:");
#else
    atResponse = atSendCommandSingleline(cmd, "+ESMLRSU:");
#endif
    if (atResponse == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuInitiate atResponse is null");
        goto error;
    }

    if (atResponse->isAtResponseFail()) {
        errCode = atResponse->atGetCmeError();
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuInitiate errCode = %d", errCode);
        response->errCode = errCode;
        mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
                RIL_E_GENERIC_FAILURE,
                RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
        responseToTelCore(mclResponse);
        free(response);
        return;
    }

    pLine = atResponse->getIntermediates();
    if (pLine == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuInitiate pLine is null");
        goto error;
    }
    pLine->atTokStart(&err);
    if (err < 0) {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuInitiate atTokStart error");
        goto error;
    }

    opId = pLine->atTokNextint(&err);
    if (err < 0 || opId != request->opId) {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuInitiate err < 0 or opId = %d"
                " not equal ot request opId = %d", opId, request->opId);
        goto error;
    }
    requestId = pLine->atTokNextint(&err);
    if (err < 0 || requestId != RSU_MODEM_REQUEST_INIT_REQUEST) {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuInitiate err < 0 or requestId = %d"
                " not equal ot request requestId = %d", requestId, request->requestId);
        goto error;
    }

    generateRequest = pLine->atTokNextstr(&err);
    if (err < 0 || generateRequest == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuInitiate err < 0 or generateRequest is null");
        goto error;
    }
    response->data = generateRequest;
    printReducedLog("[RSU-SIMLOCK] handleVzwRsuInitiate ", response->data);

    mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
            RIL_E_SUCCESS, RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
    responseToTelCore(mclResponse);
    free(response);
    return;

error:
    free(response);
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
            RIL_E_GENERIC_FAILURE, RfxVoidData(), msg);
    responseToTelCore(mclResponse);
}

void RmcCommSimRequestHandler::handleVzwRsuGetSharedKey(const sp<RfxMclMessage>& msg) {
    int err = 0;
    int errCode = 0;

    String8 cmd("");
    RfxAtLine *pLine = NULL;
    sp<RfxAtResponse> atResponse;
    sp<RfxMclMessage> mclResponse;

    int opId = -1;
    int requestId = -1;
    char* sharedKey = NULL;

    RIL_RsuRequest* request = (RIL_RsuRequest*)(msg->getData()->getData());
    RIL_RsuResponse* response = (RIL_RsuResponse*)calloc(1, sizeof(RIL_RsuResponse));
    RFX_ASSERT(response != NULL);
    response->opId = request->opId;
    response->requestId = request->requestId;

    cmd.append(String8::format("AT+ESMLRSU=%d,%d,\"%s\"",
            request->opId, RSU_MODEM_REQUEST_GET_SHARED_KEY, request->data));
    logD(mTag, "[RSU-SIMLOCK] AT+ESMLRSU=%d,%d", request->opId, RSU_MODEM_REQUEST_GET_SHARED_KEY);
    printReducedLog("[RSU-SIMLOCK] handleVzwRsuGetSharedKey ", request->data);
#ifdef SML_UT_TEST
    atResponse = smlSendAtSingleLine(cmd, "+ESMLRSU:");
#else
    atResponse = atSendCommandSingleline(cmd, "+ESMLRSU:");
#endif
    if (atResponse == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuGetSharedKey atResponse is null");
        goto error;
    }

    if (atResponse->isAtResponseFail()) {
        errCode = atResponse->atGetCmeError();
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuGetSharedKey errCode = %d", errCode);
        response->errCode = errCode;
        mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
                RIL_E_GENERIC_FAILURE,
                RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
        responseToTelCore(mclResponse);
        free(response);
        return;
    }

    pLine = atResponse->getIntermediates();
    if (pLine == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuGetSharedKey pLine is null");
        goto error;
    }
    pLine->atTokStart(&err);
    if (err < 0) {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuGetSharedKey atTokStart error");
        goto error;
    }

    opId = pLine->atTokNextint(&err);
    if (err < 0 || opId != request->opId) {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuGetSharedKey err < 0 or opId = %d"
                " not equal ot request opId = %d", opId, request->opId);
        goto error;
    }
    requestId = pLine->atTokNextint(&err);
    if (err < 0 || requestId != RSU_MODEM_REQUEST_GET_SHARED_KEY) {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuGetSharedKey err < 0 or requestId = %d"
                " not equal ot request requestId = %d", requestId, request->requestId);
        goto error;
    }

    sharedKey = pLine->atTokNextstr(&err);
    if (err < 0 || sharedKey == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuGetSharedKey err < 0 or sharedKey is null");
        goto error;
    }
    response->data = sharedKey;
    printReducedLog("[RSU-SIMLOCK] handleVzwRsuGetSharedKey ", response->data);

    mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
            RIL_E_SUCCESS, RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
    responseToTelCore(mclResponse);
    free(response);
    return;

error:
    free(response);
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
            RIL_E_GENERIC_FAILURE, RfxVoidData(), msg);
    responseToTelCore(mclResponse);
}

void RmcCommSimRequestHandler::handleVzwRsuUpdateLockData(const sp<RfxMclMessage>& msg) {
    int err = 0;
    int errCode = 0;

    String8 cmd("");
    RfxAtLine *pLine = NULL;
    sp<RfxAtResponse> atResponse;
    sp<RfxMclMessage> mclResponse;

    int opId = -1;
    int requestId = -1;
    char* lockData = NULL;

    RIL_RsuRequest* request = (RIL_RsuRequest*)(msg->getData()->getData());
    RIL_RsuResponse* response = (RIL_RsuResponse*)calloc(1, sizeof(RIL_RsuResponse));
    RFX_ASSERT(response != NULL);
    response->opId = request->opId;
    response->requestId = request->requestId;

    cmd.append(String8::format("AT+ESMLRSU=%d,%d,\"%s\"",
            request->opId, RSU_MODEM_REQUEST_UPDATE_LOCK_DATA, request->data));
    logD(mTag, "[RSU-SIMLOCK] AT+ESMLRSU=%d,%d", request->opId, RSU_MODEM_REQUEST_UPDATE_LOCK_DATA);
    printReducedLog("[RSU-SIMLOCK] handleVzwRsuUpdateLockData ", request->data);
#ifdef SML_UT_TEST
    atResponse = smlSendAtSingleLine(cmd, "+ESMLRSU:");
#else
    atResponse = atSendCommandSingleline(cmd, "+ESMLRSU:");
#endif
    if (atResponse == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuUpdateLockData atResponse is null");
        goto error;
    }

    if (atResponse->isAtResponseFail()) {
        errCode = atResponse->atGetCmeError();
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuUpdateLockData errCode = %d", errCode);
        response->errCode = errCode;
        mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
                RIL_E_GENERIC_FAILURE,
                RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
        responseToTelCore(mclResponse);
        free(response);
        return;
    }

    pLine = atResponse->getIntermediates();
    if (pLine == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuUpdateLockData pLine is null");
        goto error;
    }
    pLine->atTokStart(&err);
    if (err < 0) {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuUpdateLockData atTokStart error");
        goto error;
    }

    opId = pLine->atTokNextint(&err);
    if (err < 0 || opId != request->opId) {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuUpdateLockData err < 0 or opId = %d"
                " not equal ot request opId = %d", opId, request->opId);
        goto error;
    }
    requestId = pLine->atTokNextint(&err);
    if (err < 0 || requestId != RSU_MODEM_REQUEST_UPDATE_LOCK_DATA) {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuUpdateLockData err < 0 or requestId = %d"
                " not equal ot request requestId = %d", requestId, request->requestId);
        goto error;
    }

    lockData = pLine->atTokNextstr(&err);
    if (err < 0 || lockData == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuUpdateLockData err < 0 or lockData is null");
        goto error;
    }
    response->data = lockData;
    printReducedLog("[RSU-SIMLOCK] handleVzwRsuUpdateLockData ", response->data);

    mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
            RIL_E_SUCCESS, RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
    responseToTelCore(mclResponse);
    free(response);
    return;

error:
    free(response);
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
            RIL_E_GENERIC_FAILURE, RfxVoidData(), msg);
    responseToTelCore(mclResponse);
}

void RmcCommSimRequestHandler::handleVzwRsuGetVersion(const sp<RfxMclMessage>& msg) {
    int err = 0;
    int errCode = 0;
    String8 cmd("");

    RfxAtLine *pLine = NULL;
    sp<RfxAtResponse> atResponse;
    sp<RfxMclMessage> mclResponse;

    int opId = -1;
    int requestId = -1;
    char* majorVersion = NULL;
    char* minorVersion = NULL;

    RIL_RsuRequest* request = (RIL_RsuRequest*)(msg->getData()->getData());
    RIL_RsuResponse* response = (RIL_RsuResponse*)calloc(1, sizeof(RIL_RsuResponse));
    RFX_ASSERT(response != NULL);
    response->opId = request->opId;
    response->requestId = request->requestId;

    cmd.append(String8::format("AT+ESMLRSU=%d,%d",
            request->opId, RSU_MODEM_REQUEST_GET_LOCK_VERSION));
    logD(mTag, "[RSU-SIMLOCK] AT+ESMLRSU=%d,%d", request->opId, RSU_MODEM_REQUEST_GET_LOCK_VERSION);
#ifdef SML_UT_TEST
    atResponse = smlSendAtSingleLine(cmd, "+ESMLRSU:");
#else
    atResponse = atSendCommandSingleline(cmd, "+ESMLRSU:");
#endif
    if (atResponse == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuGetVersion atResponse is null");
        goto error;
    }

    if (atResponse->isAtResponseFail()) {
        errCode = atResponse->atGetCmeError();
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuGetVersion errCode = %d", errCode);
        response->errCode = errCode;
        mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
                RIL_E_GENERIC_FAILURE,
                RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
        responseToTelCore(mclResponse);
        free(response);
        return;
    }

    pLine = atResponse->getIntermediates();
    if (pLine == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuGetVersion pLine is null");
        goto error;
    }
    pLine->atTokStart(&err);
    if (err < 0) {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuGetVersion atTokStart error");
        goto error;
    }

    opId = pLine->atTokNextint(&err);
    if (err < 0 || opId != request->opId) {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuGetVersion err < 0 or opId = %d"
                " not equal ot request opId = %d", opId, request->opId);
        goto error;
    }
    requestId = pLine->atTokNextint(&err);
    if (err < 0 || requestId != RSU_MODEM_REQUEST_GET_LOCK_VERSION) {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuGetVersion err < 0 or requestId = %d"
                " not equal ot request requestId = %d", requestId, request->requestId);
        goto error;
    }

    majorVersion = pLine->atTokNextstr(&err);
    if (err < 0 || majorVersion == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuGetVersion err < 0 or majorVersion is NULL");
        goto error;
    }
    if (pLine->atTokHasmore()) {
        minorVersion = pLine->atTokNextstr(&err);
        if (err < 0 || minorVersion == NULL) {
            logE(mTag, "[RSU-SIMLOCK] handleVzwRsuGetVersion err < 0 or minorVersion is NULL");
            goto error;
        }
    } else {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuGetVersion no minorVersion");
        goto error;
    }
    response->version = ((atoi(majorVersion) << 16) + atoi(minorVersion));
    logD(mTag, "[RSU-SIMLOCK] handleVzwRsuGetVersion version = %d", response->version);

    mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
            RIL_E_SUCCESS, RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
    responseToTelCore(mclResponse);
    free(response);
    return;

error:
    free(response);
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
            RIL_E_GENERIC_FAILURE, RfxVoidData(), msg);
    responseToTelCore(mclResponse);
}

void RmcCommSimRequestHandler::handleVzwRsuGetStatus(const sp<RfxMclMessage>& msg) {
    int err = 0;
    int errCode = 0;
    String8 cmd("");

    RfxAtLine *pLine = NULL;
    sp<RfxAtResponse> atResponse;
    sp<RfxMclMessage> mclResponse;

    int opId = -1;
    int requestId = -1;
    char* unlockStatus = NULL;
    char* unlockTime = NULL;

    RIL_RsuRequest* request = (RIL_RsuRequest*)(msg->getData()->getData());
    RIL_RsuResponse* response = (RIL_RsuResponse*)calloc(1, sizeof(RIL_RsuResponse));
    RFX_ASSERT(response != NULL);
    response->opId = request->opId;
    response->requestId = request->requestId;

    cmd.append(String8::format("AT+ESMLRSU=%d,%d",
            request->opId, RSU_MODEM_REQUEST_GET_LOCK_STATUS));
    logD(mTag, "[RSU-SIMLOCK] AT+ESMLRSU=%d,%d", request->opId, RSU_MODEM_REQUEST_GET_LOCK_STATUS);
#ifdef SML_UT_TEST
    atResponse = smlSendAtSingleLine(cmd, "+ESMLRSU:");
#else
    atResponse = atSendCommandSingleline(cmd, "+ESMLRSU:");
#endif
    if (atResponse == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuGetStatus atResponse is null");
        goto error;
    }

    if (atResponse->isAtResponseFail()) {
        errCode = atResponse->atGetCmeError();
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuGetStatus errCode = %d", errCode);
        response->errCode = errCode;
        mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
                RIL_E_GENERIC_FAILURE,
                RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
        responseToTelCore(mclResponse);
        free(response);
        return;
    }

    pLine = atResponse->getIntermediates();
    if (pLine == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuGetStatus pLine is null");
        goto error;
    }
    pLine->atTokStart(&err);
    if (err < 0) {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuGetStatus atTokStart error");
        goto error;
    }

    opId = pLine->atTokNextint(&err);
    if (err < 0 || opId != request->opId) {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuGetStatus err < 0 or opId = %d"
                " not equal ot request opId = %d", opId, request->opId);
        goto error;
    }
    requestId = pLine->atTokNextint(&err);
    if (err < 0 || requestId != RSU_MODEM_REQUEST_GET_LOCK_STATUS) {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuGetStatus err < 0 or requestId = %d"
                " not equal ot request requestId = %d", requestId, request->requestId);
        goto error;
    }

    unlockStatus = pLine->atTokNextstr(&err);
    if (err < 0 || unlockStatus == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuGetStatus err < 0 or unlockStatus is NULL");
        goto error;
    }
    response->status = atoi(unlockStatus);
    if (pLine->atTokHasmore()) {
        unlockTime = pLine->atTokNextstr(&err);
        if (err < 0 || unlockTime == NULL) {
            logE(mTag, "[RSU-SIMLOCK] handleVzwRsuGetStatus err < 0 or unlockTime is null");
            goto error;
        }
        response->time = atoll(unlockTime);
    } else {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuGetStatus no unlockTime");
        goto error;
    }
    logD(mTag, "[RSU-SIMLOCK] handleVzwRsuGetStatus unlockStatus = %d unlockTime = %lld",
            response->status, response->time);

    mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
            RIL_E_SUCCESS, RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
    responseToTelCore(mclResponse);
    free(response);
    return;

error:
    free(response);
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
            RIL_E_GENERIC_FAILURE, RfxVoidData(), msg);
    responseToTelCore(mclResponse);
}

void RmcCommSimRequestHandler::handleVzwRsuUnlockTimer(const sp<RfxMclMessage>& msg) {
    int err = 0;
    int errCode = 0;

    String8 cmd("");
    RfxAtLine *pLine = NULL;
    sp<RfxAtResponse> atResponse;
    sp<RfxMclMessage> mclResponse;

    int opId = -1;
    int requestId = -1;
    char* timerStatus = NULL;
    char* passedTime = NULL;

    RIL_RsuRequest* request = (RIL_RsuRequest*)(msg->getData()->getData());
    RIL_RsuResponse* response = (RIL_RsuResponse*)calloc(1, sizeof(RIL_RsuResponse));
    RFX_ASSERT(response != NULL);
    response->opId = request->opId;
    response->requestId = request->requestId;

    cmd.append(String8::format("AT+ESMLRSU=%d,%d,%d",
            request->opId, RSU_MODEM_REQUEST_UNLOCK_TIMER, (request->requestType == 2 ? 0 : 1)));
    logD(mTag, "[RSU-SIMLOCK] AT+ESMLRSU=%d,%d,%d",
            request->opId, RSU_MODEM_REQUEST_UNLOCK_TIMER, (request->requestType == 2 ? 0 : 1));
#ifdef SML_UT_TEST
    atResponse = smlSendAtSingleLine(cmd, "+ESMLRSU:");
#else
    atResponse = atSendCommandSingleline(cmd, "+ESMLRSU:");
#endif
    if (atResponse == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuUnlockTimer atResponse is null");
        goto error;
    }

    if (atResponse->isAtResponseFail()) {
        errCode = atResponse->atGetCmeError();
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuUnlockTimer errCode = %d", errCode);
        response->errCode = errCode;
        mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
                RIL_E_GENERIC_FAILURE,
                RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
        responseToTelCore(mclResponse);
        free(response);
        return;
    }

    pLine = atResponse->getIntermediates();
    if (pLine == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuUnlockTimer pLine is null");
        goto error;
    }
    pLine->atTokStart(&err);
    if (err < 0) {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuUnlockTimer atTokStart error");
        goto error;
    }

    opId = pLine->atTokNextint(&err);
    if (err < 0 || opId != request->opId) {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuUnlockTimer er < 0 or opId = %d"
                " not equal ot request opId = %d", opId, request->opId);
        goto error;
    }
    requestId = pLine->atTokNextint(&err);
    if (err < 0 || requestId != RSU_MODEM_REQUEST_UNLOCK_TIMER) {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuUnlockTimer err < 0 or requestId = %d"
                " not equal ot request requestId = %d", requestId, request->requestId);
        goto error;
    }

    timerStatus = pLine->atTokNextstr(&err);
    if (err < 0 || timerStatus == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuUnlockTimer err < 0 or timerStatus is NULL");
        goto error;
    }
    response->errCode = atoi(timerStatus);
    if (pLine->atTokHasmore()) {
        passedTime = pLine->atTokNextstr(&err);
        if (err < 0 || passedTime == NULL) {
            logE(mTag, "[RSU-SIMLOCK] handleVzwRsuUnlockTimer err < 0 or passedTime is null");
            goto error;
        }
        response->time = atoll(passedTime);
    } else {
        logE(mTag, "[RSU-SIMLOCK] handleVzwRsuUnlockTimer no passedTime");
        goto error;
    }
    logD(mTag, "[RSU-SIMLOCK] handleVzwRsuUnlockTimer timerStatus = %d passedTime = %lld",
            response->status, response->time);

    mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
            RIL_E_SUCCESS, RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
    responseToTelCore(mclResponse);
    free(response);
    return;

error:
    free(response);
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
            RIL_E_GENERIC_FAILURE, RfxVoidData(), msg);
    responseToTelCore(mclResponse);
}

void RmcCommSimRequestHandler::handleTmoRsuRequest(const sp<RfxMclMessage>& msg) {
    RIL_RsuRequest* request = (RIL_RsuRequest*)(msg->getData()->getData());
    switch (request->requestId) {
        case RSU_REQUEST_GET_SHARED_KEY:
            handleTmoRsuGetRegisterRequest(msg);
            return;
        case RSU_REQUEST_INIT_REQUEST:
            handleTmoRsuCreateUnlockRequest(msg);
            return;
        case RSU_REQUEST_UPDATE_LOCK_DATA:
            handleTmoRsuProcessMessage(msg);
            return;
        case RSU_REQUEST_GET_LOCK_VERSION:
            handleTmoRsuGetAdapterConfig(msg);
            return;
        case RSU_REQUEST_GET_LOCK_STATUS:
            handleTmoRsuGetSimlockStatus(msg);
            return;
        default:
            break;
    }
    sp<RfxMclMessage> mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
            RIL_E_GENERIC_FAILURE, RfxVoidData(), msg);
    responseToTelCore(mclResponse);
}

void RmcCommSimRequestHandler::handleTmoRsuGetRegisterRequest(const sp<RfxMclMessage>& msg) {
    int err = 0;
    String8 cmd("");
    RfxAtLine *pLine = NULL;
    sp<RfxAtResponse> atResponse;
    sp<RfxMclMessage> mclResponse;
    int opId = -1;
    int requestId = -1;
    int length = 0;
    char* sharedKey = NULL;
    RIL_RsuRequest* request = (RIL_RsuRequest*)(msg->getData()->getData());
    RIL_RsuResponse* response = (RIL_RsuResponse*)calloc(1, sizeof(RIL_RsuResponse));
    RFX_ASSERT(response != NULL);
    response->opId = request->opId;
    response->requestId = request->requestId;
    cmd.append(String8::format("AT+ESMLRSU=%d,%d,\"%s\"", request->opId,
            RSU_MODEM_REQUEST_GET_SHARED_KEY, request->data));
    logD(mTag, "[RSU-SIMLOCK] AT+ESMLRSU=%d,%d", request->opId, RSU_MODEM_REQUEST_GET_SHARED_KEY);
    printReducedLog("[RSU-SIMLOCK] handleTmoRsuSmlGetRegisterRequest ", request->data);
#ifdef SML_UT_TEST
    atResponse = smlSendAtSingleLine(cmd, "+ESMLRSU:");
#else
    atResponse = atSendCommandSingleline(cmd, "+ESMLRSU:");
#endif
    if (atResponse == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlGetRegisterRequest atResponse is null");
        goto error;
    }
    if (atResponse->isAtResponseFail()) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlGetRegisterRequest isAtResponseFail = %d",
                atResponse->isAtResponseFail());
        goto error;
    }
    pLine = atResponse->getIntermediates();
    if (pLine == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlGetRegisterRequest pLine is null");
        goto error;
    }
    pLine->atTokStart(&err);
    if (err < 0) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlGetRegisterRequest atTokStart error");
        goto error;
    }
    opId = pLine->atTokNextint(&err);
    if (err < 0 || opId != request->opId) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlGetRegisterRequest err < 0 or opId = %d"
                " not equal ot request opId = %d", opId, request->opId);
        goto error;
    }
    requestId = pLine->atTokNextint(&err);
    if (err < 0 || requestId != RSU_MODEM_REQUEST_GET_SHARED_KEY) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlGetRegisterRequest err < 0 or requestId = %d"
                " not equal ot request requestId = %d", requestId, request->requestId);
        goto error;
    }
    length = pLine->atTokNextint(&err);
    if (err < 0) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlGetRegisterRequest err < 0, length = %d", length);
        goto error;
    }
    sharedKey = pLine->atTokNextstr(&err);
    if (err < 0 || sharedKey == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlGetRegisterRequest err < 0 or sharedKey is null");
        goto error;
    }
    response->data = sharedKey;
    printReducedLog("[RSU-SIMLOCK] handleTmoRsuSmlGetRegisterRequest ", response->data);
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
    responseToTelCore(mclResponse);
    free(response);
    return;
error:
    free(response);
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_GENERIC_FAILURE,
            RfxVoidData(), msg);
    responseToTelCore(mclResponse);
}

void RmcCommSimRequestHandler::handleTmoRsuCreateUnlockRequest(const sp<RfxMclMessage>& msg) {
    int err = 0;
    String8 cmd("");
    RfxAtLine *pLine = NULL;
    sp<RfxAtResponse> atResponse;
    sp<RfxMclMessage> mclResponse;
    int opId = -1;
    int requestId = -1;
    int length = 0;
    char* generateRequest = NULL;
    RIL_RsuRequest* request = (RIL_RsuRequest*)(msg->getData()->getData());
    RIL_RsuResponse* response = (RIL_RsuResponse*)calloc(1,
            sizeof(RIL_RsuResponse));
    RFX_ASSERT(response != NULL);
    response->opId = request->opId;
    response->requestId = request->requestId;
    cmd.append(String8::format("AT+ESMLRSU=%d,%d,\"%s\"", request->opId,
            RSU_MODEM_REQUEST_INIT_REQUEST, request->data));
    logD(mTag, "[RSU-SIMLOCK] AT+ESMLRSU=%d,%d", request->opId, RSU_MODEM_REQUEST_INIT_REQUEST);
    printReducedLog("[RSU-SIMLOCK] handleTmoRsuSmlCreateUnlockRequest ", request->data);
#ifdef SML_UT_TEST
    atResponse = smlSendAtSingleLine(cmd, "+ESMLRSU:");
#else
    atResponse = atSendCommandSingleline(cmd, "+ESMLRSU:");
#endif
    if (atResponse == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlCreateUnlockRequest atResponse is null");
        goto error;
    }
    if (atResponse->isAtResponseFail()) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlCreateUnlockRequest isAtResponseFail = %d",
                atResponse->isAtResponseFail());
        goto error;
    }
    pLine = atResponse->getIntermediates();
    if (pLine == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlCreateUnlockRequest pLine is null");
        goto error;
    }
    pLine->atTokStart(&err);
    if (err < 0) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlCreateUnlockRequest atTokStart error");
        goto error;
    }
    opId = pLine->atTokNextint(&err);
    if (err < 0 || opId != request->opId) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlCreateUnlockRequest err < 0 or opId = %d"
                " not equal ot request opId = %d", opId, request->opId);
        goto error;
    }
    requestId = pLine->atTokNextint(&err);
    if (err < 0 || requestId != RSU_MODEM_REQUEST_INIT_REQUEST) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlCreateUnlockRequest err < 0 or requestId = %d"
                " not equal ot request requestId = %d", requestId, request->requestId);
        goto error;
    }
    length = pLine->atTokNextint(&err);
    if (err < 0) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlCreateUnlockRequest err<0, length = %d", length);
        goto error;
    }
    generateRequest = pLine->atTokNextstr(&err);
    if (err < 0 || generateRequest == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlCreateUnlockRequest err<0 or"
                "generateRequest is null");
        goto error;
    }
    response->data = generateRequest;
    printReducedLog("[RSU-SIMLOCK] handleTmoRsuSmlCreateUnlockRequest ", response->data);
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
    responseToTelCore(mclResponse);
    free(response);
    return;
error:
    free(response);
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_GENERIC_FAILURE,
            RfxVoidData(), msg);
    responseToTelCore(mclResponse);
}

void RmcCommSimRequestHandler::handleTmoRsuProcessMessage(const sp<RfxMclMessage>& msg) {
    int err = 0;
    String8 cmd("");
    RfxAtLine *pLine = NULL;
    sp<RfxAtResponse> atResponse;
    sp<RfxMclMessage> mclResponse;
    int opId = -1;
    int requestId = -1;
    int length = 0;
    char* lockData = NULL;
    RIL_RsuRequest* request = (RIL_RsuRequest*)(msg->getData()->getData());
    RIL_RsuResponse* response = (RIL_RsuResponse*)calloc(1,
            sizeof(RIL_RsuResponse));
    RFX_ASSERT(response != NULL);
    response->opId = request->opId;
    response->requestId = request->requestId;
    if (request->data != NULL) {
        cmd.append(String8::format("AT+ESMLRSU=%d,%d,\"%s\",%d,\"%s\"", request->opId,
                RSU_MODEM_REQUEST_UPDATE_LOCK_DATA, request->reserveString1,
                (int)strlen(request->data),
                request->data));
        logD(mTag, "[RSU-SIMLOCK] AT+ESMLRSU=%d,%d,%d", request->opId,
                RSU_MODEM_REQUEST_UPDATE_LOCK_DATA, (int)strlen(request->data));
        printReducedLog("[RSU-SIMLOCK] request->reserveString1", request->reserveString1);
        printReducedLog("[RSU-SIMLOCK] handleTmoRsuProcessMessage ", request->data);
    } else {
        cmd.append(String8::format("AT+ESMLRSU=%d,%d,\"%s\",%d,\"%s\"", request->opId,
                RSU_MODEM_REQUEST_UPDATE_LOCK_DATA, request->reserveString1, 0, ""));
    }
#ifdef SML_UT_TEST
    atResponse = smlSendAtSingleLine(cmd, "+ESMLRSU:");
#else
    atResponse = atSendCommandSingleline(cmd, "+ESMLRSU:");
#endif

    if (atResponse == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlProcessMessage atResponse is null");
        goto error;
    }
    if (atResponse->isAtResponseFail()) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlProcessMessage isAtResponseFail = %d",
                atResponse->isAtResponseFail());
        goto error;
    }
    pLine = atResponse->getIntermediates();
    if (pLine == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlProcessMessage pLine is null");
        goto error;
    }
    pLine->atTokStart(&err);
    if (err < 0) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlProcessMessage atTokStart error");
        goto error;
    }
    opId = pLine->atTokNextint(&err);
    if (err < 0 || opId != request->opId) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlProcessMessage err < 0 or opId = %d"
                " not equal ot request opId = %d", opId, request->opId);
        goto error;
    }
    requestId = pLine->atTokNextint(&err);
    if (err < 0 || requestId != RSU_MODEM_REQUEST_UPDATE_LOCK_DATA) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlProcessMessage err < 0 or requestId = %d"
                " not equal ot request requestId = %d", requestId, request->requestId);
        goto error;
    }
    length = pLine->atTokNextint(&err);
    if (err < 0) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlProcessMessage err < 0, length = %d", length);
        goto error;
    }
    lockData = pLine->atTokNextstr(&err);
    if (err < 0 || lockData == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlProcessMessage err < 0 or lockData is null");
        goto error;
    }
    response->data = lockData;
    printReducedLog("[RSU-SIMLOCK] handleTmoRsuSmlProcessMessage ", response->data);
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
    responseToTelCore(mclResponse);
    free(response);
    return;
error:
    free(response);
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_GENERIC_FAILURE,
            RfxVoidData(), msg);
    responseToTelCore(mclResponse);
}

void RmcCommSimRequestHandler::handleTmoRsuGetAdapterConfig(const sp<RfxMclMessage>& msg) {
    int err = 0;
    String8 cmd("");
    RfxAtLine *pLine = NULL;
    sp<RfxAtResponse> atResponse;
    sp<RfxMclMessage> mclResponse;
    int opId = -1;
    int requestId = -1;
    int length = 0;
    char* configData = NULL;
    RIL_RsuRequest* request = (RIL_RsuRequest*)(msg->getData()->getData());
    RIL_RsuResponse* response = (RIL_RsuResponse*)calloc(1,
            sizeof(RIL_RsuResponse));
    RFX_ASSERT(response != NULL);
    response->opId = request->opId;
    response->requestId = request->requestId;
    cmd.append(String8::format("AT+ESMLRSU=%d,%d,\"%s\"", request->opId,
            RSU_MODEM_REQUEST_GET_LOCK_VERSION, request->data));
    logD(mTag, "[RSU-SIMLOCK] AT+ESMLRSU=%d,%d", request->opId, RSU_MODEM_REQUEST_GET_LOCK_VERSION);
    printReducedLog("[RSU-SIMLOCK] handleTmoRsuSmlGetAdapterConfig ", request->data);
#ifdef SML_UT_TEST
    atResponse = smlSendAtSingleLine(cmd, "+ESMLRSU:");
#else
    atResponse = atSendCommandSingleline(cmd, "+ESMLRSU:");
#endif

    if (atResponse == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlGetAdapterConfig atResponse is null");
        goto error;
    }
    if (atResponse->isAtResponseFail()) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlGetAdapterConfig isAtResponseFail = %d",
                atResponse->isAtResponseFail());
        goto error;
    }
    pLine = atResponse->getIntermediates();
    if (pLine == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlGetAdapterConfig pLine is null");
        goto error;
    }
    pLine->atTokStart(&err);
    if (err < 0) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlGetAdapterConfig atTokStart error");
        goto error;
    }
    opId = pLine->atTokNextint(&err);
    if (err < 0 || opId != request->opId) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlGetAdapterConfig err < 0 or opId = %d"
                " not equal ot request opId = %d", opId, request->opId);
        goto error;
    }
    requestId = pLine->atTokNextint(&err);
    if (err < 0 || requestId != RSU_MODEM_REQUEST_GET_LOCK_VERSION) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlGetAdapterConfig err < 0 or requestId = %d"
                " not equal ot request requestId = %d", requestId, request->requestId);
        goto error;
    }
    length = pLine->atTokNextint(&err);
    if (err < 0) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlGetAdapterConfig err < 0, length = %d", length);
        goto error;
    }
    configData = pLine->atTokNextstr(&err);
    if (err < 0 || configData == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlGetAdapterConfig err<0 or configData is NULL");
        goto error;
    }
    response->data = configData;
    printReducedLog("[RSU-SIMLOCK] handleTmoRsuSmlGetAdapterConfig ", response->data);
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
    responseToTelCore(mclResponse);
    free(response);
    return;
error:
    free(response);
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_GENERIC_FAILURE,
            RfxVoidData(), msg);
    responseToTelCore(mclResponse);
}
void RmcCommSimRequestHandler::handleTmoRsuGetSimlockStatus(const sp<RfxMclMessage>& msg) {
    int err = 0;
    String8 cmd("");
    RfxAtLine *pLine = NULL;
    sp<RfxAtResponse> atResponse;
    sp<RfxMclMessage> mclResponse;
    int opId = -1;
    int requestId = -1;
    int length = 0;
    char* unlockStatus = NULL;
    RIL_RsuRequest* request = (RIL_RsuRequest*)(msg->getData()->getData());
    RIL_RsuResponse* response = (RIL_RsuResponse*)calloc(1,
            sizeof(RIL_RsuResponse));
    RFX_ASSERT(response != NULL);
    response->opId = request->opId;
    response->requestId = request->requestId;
    if (request->data != NULL) {
        cmd.append(String8::format("AT+ESMLRSU=%d,%d,\"%s\"", request->opId,
                RSU_MODEM_REQUEST_GET_LOCK_STATUS, request->data));
    } else {
        cmd.append(String8::format("AT+ESMLRSU=%d,%d,\"%s\"", request->opId,
                RSU_MODEM_REQUEST_GET_LOCK_STATUS, ""));
    }
    logD(mTag, "[RSU-SIMLOCK] AT+ESMLRSU=%d,%d", request->opId, RSU_MODEM_REQUEST_GET_LOCK_STATUS);
    printReducedLog("[RSU-SIMLOCK] handleTmoRsuSmlGetSimlockStatus ", request->data);
#ifdef SML_UT_TEST
    atResponse = smlSendAtSingleLine(cmd, "+ESMLRSU:");
#else
    atResponse = atSendCommandSingleline(cmd, "+ESMLRSU:");
#endif

    if (atResponse == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlGetSimlockStatus atResponse is null");
        goto error;
    }
    if (atResponse->isAtResponseFail()) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlGetSimlockStatus isAtResponseFail = %d",
                atResponse->isAtResponseFail());
        goto error;
    }
    pLine = atResponse->getIntermediates();
    if (pLine == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlGetSimlockStatus pLine is null");
        goto error;
    }
    pLine->atTokStart(&err);
    if (err < 0) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlGetSimlockStatus atTokStart error");
        goto error;
    }
    opId = pLine->atTokNextint(&err);
    if (err < 0 || opId != request->opId) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlGetSimlockStatus err < 0 or opId = %d"
                " not equal ot request opId = %d", opId, request->opId);
        goto error;
    }
    requestId = pLine->atTokNextint(&err);
    if (err < 0 || requestId != RSU_MODEM_REQUEST_GET_LOCK_STATUS) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlGetSimlockStatus err < 0 or requestId = %d"
                " not equal ot request requestId = %d", requestId, request->requestId);
        goto error;
    }
    length = pLine->atTokNextint(&err);
    if (err < 0) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlGetSimlockStatus err < 0, length = %d", length);
        goto error;
    }
    unlockStatus = pLine->atTokNextstr(&err);
    if (err < 0 || unlockStatus == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleTmoRsuSmlGetSimlockStatus err < 0 or unlockStatus is NULL");
        goto error;
    }
    response->data = unlockStatus;
    printReducedLog("[RSU-SIMLOCK] handleTmoRsuSmlGetSimlockStatus ", response->data);
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
    responseToTelCore(mclResponse);
    free(response);
    return;
error:
    free(response);
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_GENERIC_FAILURE,
            RfxVoidData(), msg);
    responseToTelCore(mclResponse);
}

//////// ATT Legacy RSU /////////////
void RmcCommSimRequestHandler::handleAttLegacyRsuRequest(const sp<RfxMclMessage>& msg,
        RIL_RsuRequest *request) {
    switch (request->requestId) {
        case RSU_REQUEST_GET_SHARED_KEY:
            logD(mTag, "[RSU-SIMLOCK] att get shared key");
            ttGetData(msg, request, "AT+EATTSK=0", "+EATTSK:");
            return;
        case RSU_REQUEST_UPDATE_LOCK_DATA:
            logD(mTag, "[RSU-SIMLOCK] att update lock data");
            ttSetData(msg, request, String8::format("AT+EATTSLB=1,%d,\"%s\"",
                    (unsigned int)((strlen(request->data) + 1)/2), request->data));
            return;
        case RSU_REQUEST_RESET_LOCK_DATA:
            logD(mTag, "[RSU-SIMLOCK] att reset lock data");
            ttSetData(msg, request, String8::format("AT+EATTSLB=2"));
            return;
        case RSU_REQUEST_GET_LOCK_STATUS:
            logD(mTag, "[RSU-SIMLOCK] att get lock status");
            ttGetData(msg, request, "AT+EATTSLB=4", "+EATTSLB:");
            return;
        case RSU_REQUEST_GET_LOCK_VERSION:
            logD(mTag, "[RSU-SIMLOCK] att get lock version");
            ttGetData(msg, request, "AT+EATTSLB=3", "+EATTSLB:");
            return;
        case RSU_REQUEST_GET_MODEM_CONFIG:
            logD(mTag, "[RSU-SIMLOCK] att get modem config");
            ttGetData(msg, request, "AT+EATTSLB=5", "+EATTSLB:");
            return;
        case RSU_REQUEST_GET_API_VERSION:
            logD(mTag, "[RSU-SIMLOCK] att get api version");
            ttGetData(msg, request, "AT+EATTSLB=6", "+EATTSLB:");
            return;
        case RSU_REQUEST_GET_SIM_SLOTS:
            logD(mTag, "[RSU-SIMLOCK] att get sim slots");
            ttGetData(msg, request, "AT+EATTSLB=7", "+EATTSLB:");
            return;
        default:
            logE(mTag, "[RSU-SIMLOCK]handleAttLegacyRsuRequest: unsupported request %d.\n",
                    request->requestId);
            break;
    }
    sp<RfxMclMessage> mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
            RIL_E_GENERIC_FAILURE, RfxVoidData(), msg);
    responseToTelCore(mclResponse);
}

//////// TMO Legacy RSU /////////////
void RmcCommSimRequestHandler::handleTmoLegacyRsuRequest(const sp<RfxMclMessage>& msg,
        RIL_RsuRequest *request) {
    switch (request->requestId) {
        case RSU_REQUEST_GET_SHARED_KEY:
            logD(mTag, "[RSU-SIMLOCK] tmo get shared key");
            ttGetData(msg, request, "AT+ETMOSK=0", "+ETMOSK:");
            return;
        case RSU_REQUEST_UPDATE_LOCK_DATA:
            logD(mTag, "[RSU-SIMLOCK] tmo update lock data");
            ttSetData(msg, request, String8::format("AT+ETMOSLB=1,%d,\"%s\"",
                    (unsigned int)((strlen(request->data) + 1)/2), request->data));
            return;
        case RSU_REQUEST_RESET_LOCK_DATA:
            logD(mTag, "[RSU-SIMLOCK] tmo reset lock data");
            ttSetData(msg, request, String8::format("AT+ETMOSLB=2"));
            return;
        case RSU_REQUEST_GET_LOCK_STATUS:
            logD(mTag, "[RSU-SIMLOCK] tmo get lock status");
            ttGetData(msg, request, "AT+ETMOSLB=4", "+ETMOSLB:");
            return;
        case RSU_REQUEST_GET_LOCK_VERSION:
            logD(mTag, "[RSU-SIMLOCK] tmo get lock version");
            ttGetData(msg, request, "AT+ETMOSLB=3", "+ETMOSLB:");
            return;
        default:
            logE(mTag, "[RSU-SIMLOCK]handleTmoLegacyRsuRequest: unsupported request %d.\n",
                    request->requestId);
            break;
    }
    sp<RfxMclMessage> mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
            RIL_E_GENERIC_FAILURE, RfxVoidData(), msg);
    responseToTelCore(mclResponse);
}

#ifdef TT_FAKE_TEST
#define FAKE_KEY "0348393939210abcd8439483"
#define FAKE_LOCK_VERSION "10"
#define FAKE_MODEM_STATUS "2030405060708090A0B0C0D0"
#define FAKE_MODEM_CONFIG "ABCDEDF23935803500"
#define FAKE_API_VERSION "10"
#define FAKE_SLOTS_NUM "2"
static unsigned char FAKE_CONFIG_DATA[] = "10230833554478F03360";
#endif

void RmcCommSimRequestHandler::ttGetData(const sp<RfxMclMessage>& msg, RIL_RsuRequest* request,
        const char *atStr, const char *responseStr) {
    RfxAtLine *line = NULL;
    int err = -1;
    RIL_Errno ret = RIL_E_GENERIC_FAILURE;
    sp<RfxAtResponse> p_response = NULL;
    int key_len;
    char *key = NULL;
    sp<RfxMclMessage> mclResponse;
    RIL_RsuResponse* response = (RIL_RsuResponse*)calloc(1, sizeof(RIL_RsuResponse));
    RFX_ASSERT(response != NULL);
    response->opId = request->opId;
    response->requestId = request->requestId;
    response->requestType = request->requestType;

    if (RfxRilUtils::isUserLoad() == 1) {
        logD(mTag, "[RSU-SIMLOCK]handleTTGetData.\n");
    } else {
        logD(mTag, "[RSU-SIMLOCK]handleTTGetData at=%s\n", atStr);
    }

    p_response = atSendCommandSingleline(atStr, responseStr);

#ifdef TT_FAKE_TEST
    const char *fakeData;
    char key_data[50];
    switch (request->requestId) {
        case RSU_REQUEST_GET_SHARED_KEY:
            fakeData = FAKE_KEY;
            break;
        case RSU_REQUEST_GET_LOCK_STATUS:
            fakeData = FAKE_MODEM_STATUS;
            break;
        case RSU_REQUEST_GET_LOCK_VERSION:
            fakeData = FAKE_LOCK_VERSION;
            break;
        case RSU_REQUEST_GET_MODEM_CONFIG:
            fakeData = FAKE_MODEM_CONFIG;
            break;
        case RSU_REQUEST_GET_API_VERSION:
            fakeData = FAKE_API_VERSION;
            break;
        case RSU_REQUEST_GET_SIM_SLOTS:
            fakeData = FAKE_SLOTS_NUM;
            break;
        default:
            logE(mTag, "[RSU-SIMLOCK]handleAttLegacyRsuRequest: unsupported request %d.\n",
                    request->requestId);
            break;
    }
    if (strlen(fakeData) >= 50) {
        logE(mTag, "test buffer too short\n");
        goto done;
    }
    strcpy(key_data, fakeData);

    response->data = key_data;
    ret = RIL_E_SUCCESS;
    logD(mTag, "test return with test data\n");
    goto done;
#endif

    err = p_response->getError();
    if (err < 0 || p_response->getSuccess() == 0) {
        logE(mTag, "[RSU-SIMLOCK]handleTTGetData p_response->getError(): %d.\n", err);
        goto done;
    }
    line = p_response->getIntermediates();
    if (RfxRilUtils::isUserLoad() != 1) {
        logD(mTag, "[RSU-SIMLOCK]handleTTGetData response: %s.\n", line->getLine());
    }
    line->atTokStart(&err);
    if(err < 0) {
        logE(mTag, "[RSU-SIMLOCK]handleTTGetData line->atTokStart: %d.\n", err);
        goto done;
    }

    //Get shared key len
    key_len = line->atTokNextint(&err);
    if (err < 0) {
        logE(mTag, "[RSU-SIMLOCK]handleTTGetData line->atTokNextint: %d.\n", err);
        goto done;
    }

    //Get shared key
    key = line->atTokNextstr(&err);
    if (err < 0) {
        logE(mTag, "[RSU-SIMLOCK]handleTTGetData line->atTokNextstr: %d.\n", err);
        goto done;
    }
    response->data = key;
    ret = RIL_E_SUCCESS;
    if (RfxRilUtils::isUserLoad() == 1) {
        logD(mTag, "[RSU-SIMLOCK]data = ***\n");
    } else {
        printReducedLog("[RSU-SIMLOCK]handleTTGetData ", response->data);
    }

done:
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(), ret,
            RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
    responseToTelCore(mclResponse);
    free(response);
    return;
}

void RmcCommSimRequestHandler::ttSetData(const sp<RfxMclMessage>& msg, RIL_RsuRequest* request,
        const String8& atStr) {
    int err = -1;
    RIL_Errno ret = RIL_E_GENERIC_FAILURE;
    sp<RfxAtResponse> p_response = NULL;
    sp<RfxMclMessage> mclResponse;
    RIL_RsuResponse* response = (RIL_RsuResponse*)calloc(1, sizeof(RIL_RsuResponse));
    RFX_ASSERT(response != NULL);
    response->opId = request->opId;
    response->requestId = request->requestId;
    response->requestType = request->requestType;

    if (RfxRilUtils::isUserLoad() == 1) {
        logD(mTag, "[RSU-SIMLOCK]ttSetData strings ***\n");
    } else {
        logD(mTag, "[RSU-SIMLOCK]ttSetData %s\n", atStr.string());
    }
    p_response = atSendCommand(atStr.string());

#ifdef TT_FAKE_TEST
    if (request->requestId == RSU_REQUEST_UPDATE_LOCK_DATA) {
        if (strcmp(request->data, (const char*)FAKE_CONFIG_DATA) == 0) {
            logD(mTag, "test return with success\n");
            ret = RIL_E_SUCCESS;
        } else {
            logE(mTag, "error config data!!!\n");
        }
    } else if (RSU_REQUEST_RESET_LOCK_DATA) {
        logD(mTag, "test return with reboot request\n");
        ret = RIL_E_REBOOT_REQUEST;
    } else {
        logD(mTag, "test not support!\n");
    }
    goto done;
#endif

    err = p_response->getError();
    if (err < 0) {
        logE(mTag, "getError() = %d", err);
        goto done;
    }

    if (p_response->getSuccess() == 0) {
        switch (p_response->atGetCmeError()) {
            logE(mTag, "p_response %d\n", p_response->atGetCmeError());
            case CME_VERIFICATION_FAILED:
                ret = RIL_E_VERIFICATION_FAILED;
                logD(mTag, "p_response CME_SIM_LOCK_BLOB_VERIFICATION_FAILED\n");
                break;
            case CME_REBOOT_REQUEST:
                ret = RIL_E_REBOOT_REQUEST;
                logD(mTag, "p_response CME_REBOOT_REQUEST\n");
                break;
            default:
                goto done;

        }
    } else {
        ret = RIL_E_SUCCESS;
        sp<RfxMclMessage> unsol = RfxMclMessage::obtainUrc(RFX_MSG_URC_RESPONSE_SIM_STATUS_CHANGED,
                m_slot_id, RfxVoidData());
        responseToTelCore(unsol);
    }

done:
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(), ret,
            RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
    responseToTelCore(mclResponse);
    free(response);
}

void RmcCommSimRequestHandler::handleRsuClientRequest(const sp<RfxMclMessage>& msg) {
    char * pdata = (char*)(msg->getData()->getData());
    char temp[3];

    if (pdata != NULL) {
        temp[0] = *pdata;
        temp[1] = *(pdata + 1);
        temp[2] = '\0';
        unsigned int opId = htoi(temp);
        temp[0] = *(pdata + 2);
        temp[1] = *(pdata + 3);
        temp[2] = '\0';
        unsigned int reqId = htoi(temp);
        RIL_RsuRequest request;
        memset(&request, 0, sizeof(request));
        request.opId = opId;
        request.requestId = reqId;
        request.data = pdata + 4;
        logD(mTag, "[RSU-SIMLOCK] handleRsuClientRequest opId = %d, requestId = %d",
                request.opId, request.requestId);
        switch(request.opId) {
            case RSU_OP_ATT_LEGACY:
                handleAttLegacyRsuRequest(msg, &request);
                return;
            case RSU_OP_TMO_LEGACY:
                handleTmoLegacyRsuRequest(msg, &request);
                return;
            default:
                break;
        }
    } else {
        logE(mTag, "[RSU-SIMLOCK] handleRsuClientRequest no command!!!");
    }


    sp<RfxMclMessage> mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
                    RIL_E_GENERIC_FAILURE, RfxVoidData(), msg);
    responseToTelCore(mclResponse);
}

//@{ add for supporting one customer's specific API
void RmcCommSimRequestHandler::handleSprintRsuRequest(const sp<RfxMclMessage>& msg) {
    RIL_RsuRequest* request = (RIL_RsuRequest*)(msg->getData()->getData());

    switch(request->requestId) {
        case RSU_REQUEST_SPRINT_GET_UNLOCK_CODE:
            handleSprintRsuGetUnlockCode(msg);
            return;

        case RSU_REQUEST_SPRINT_GET_NONCE:
            handleSprintRsuGetNonce(msg);
            return;

        case RSU_REQUEST_SPRINT_UPDATE_LOCK:
            handleSprintRsuSetUnlockCode(msg);
            return;
        default:
            break;
    }

    sp<RfxMclMessage> mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
                    RIL_E_REQUEST_NOT_SUPPORTED, RfxVoidData(), msg);
    responseToTelCore(mclResponse);
}

/**
 * Get nonceNV and signatureNV of sprint RSU
 *
 * return:
 *   (nonceNV & 0xFF) | ((signature & 0xFF)<<8)
 *
 * AT command
 *  AT+EUULK=4
 * response:
 *  +EUULK:<nonceNV>,<signatureNV>
 *  OK
 *
 *   <nonceNV>
 *       0 -- Failed to read from NVRAM
 *       1 -- Nonce is not stored
 *       2 -- Nonce is stored
 *   <signatureNV>
 *       0 -- Failed to read from NVRAM
 *       1 -- Signature is not stored
 *       2 -- Signature is stored with unlock code 0
 *       3 -- Signature is stored with unlock code 1
 *       4 -- Signature is stored with unlock code 2
 */
int RmcCommSimRequestHandler::getSprintRsuNvInfo() {
    int err = 0;
    String8 cmd("");
    sp<RfxAtResponse> atResponse;
    RfxAtLine *pLine = NULL;
    int nonceNv = 0; //failed to read
    int signatureNv = 0; //failed to read

    logD(mTag, "[RSU-SIMLOCK] getSprintRsuSetNvInfo...");
    cmd.append(String8::format("AT+EUULK=4"));
    atResponse = atSendCommandSingleline(cmd, "+EUULK:");
    if (atResponse == NULL) {
        logE(mTag, "[RSU-SIMLOCK] getSprintRsuSetNvInfo atResponse is null");
        return 0;
    }
    if (atResponse->isAtResponseFail()) {
        logE(mTag, "[RSU-SIMLOCK] getSprintRsuSetNvInfo isAtResponseFail = %d",
                atResponse->isAtResponseFail());
        return 0;
    }
    pLine = atResponse->getIntermediates();
    if (pLine == NULL) {
        logE(mTag, "[RSU-SIMLOCK] getSprintRsuSetNvInfo pLine is null");
        return 0;
    }
    pLine->atTokStart(&err);
    if (err < 0) {
        logE(mTag, "[RSU-SIMLOCK] getSprintRsuSetNvInfo atTokStart error");
        return 0;
    }
    nonceNv = pLine->atTokNextint(&err);
    if (err < 0) {
        logE(mTag, "[RSU-SIMLOCK] getSprintRsuSetNvInfo err < 0");
        return 0;
    }
    signatureNv = pLine->atTokNextint(&err);
    if (err < 0) {
        logE(mTag, "[RSU-SIMLOCK] getSprintRsuSetNvInfo err < 0");
        signatureNv = 0;
    }
    logD(mTag, "[RSU-SIMLOCK] getSprintRsuSetNvInfo nonceNv=%d, signatureNv=%d",
            nonceNv, signatureNv);
    return (nonceNv & 0xFF) | ((signatureNv & 0xFF)<<8);
}

void RmcCommSimRequestHandler::handleSprintRsuGetUnlockCode(const sp<RfxMclMessage>& msg) {
    int err = 0;
    String8 cmd("");
    RfxAtLine *pLine = NULL;
    sp<RfxAtResponse> atResponse;
    sp<RfxMclMessage> mclResponse;
    int unlockCode = -1;
    RIL_RsuRequest* request = (RIL_RsuRequest*)(msg->getData()->getData());
    RIL_RsuResponse* response = (RIL_RsuResponse*)calloc(1,
            sizeof(RIL_RsuResponse));
    RFX_ASSERT(response != NULL);
    response->opId = request->opId;
    response->requestId = request->requestId;

    logD(mTag, "[RSU-SIMLOCK] handleSprintRsuGetUnlockCode...");
    cmd.append(String8::format("AT+EUULK?"));
    atResponse = atSendCommandSingleline(cmd, "+EUULK:");

#ifdef SML_UT_TEST
    logE(mTag, "[RSU-SIMLOCK] UT fake data!!!!");

    unlockCode = 2;
    response->status = unlockCode;
    response->reserveInt1 = (2 | (1<<8));
    logD(mTag, "[RSU-SIMLOCK] handleSprintRsuGetUnlockCode unlockStatus = %d, nvinfo=%X",
            response->status, response->reserveInt1);
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
    responseToTelCore(mclResponse);
    free(response);
    return;
#endif

    if (atResponse == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleSprintRsuGetUnlockCode atResponse is null");
        goto error;
    }
    if (atResponse->isAtResponseFail()) {
        logE(mTag, "[RSU-SIMLOCK] handleSprintRsuGetUnlockCode isAtResponseFail = %d",
                atResponse->isAtResponseFail());
        goto error;
    }
    pLine = atResponse->getIntermediates();
    if (pLine == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleSprintRsuSmlGetSimlockStatus pLine is null");
        goto error;
    }
    pLine->atTokStart(&err);
    if (err < 0) {
        logE(mTag, "[RSU-SIMLOCK] handleSprintRsuGetUnlockCode atTokStart error");
        goto error;
    }
    unlockCode = pLine->atTokNextint(&err);
    if (err < 0) {
        logE(mTag, "[RSU-SIMLOCK] handleSprintRsuGetUnlockCode err < 0");
        goto error;
    }
    response->status = unlockCode;
    //get nvInfo
    response->reserveInt1 = getSprintRsuNvInfo();
    logD(mTag, "[RSU-SIMLOCK] handleSprintRsuGetUnlockCode unlockStatus=%d, nvInfo=0x%X",
            response->status, response->reserveInt1);
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
    responseToTelCore(mclResponse);
    free(response);
    return;
error:
    free(response);
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_GENERIC_FAILURE,
            RfxVoidData(), msg);
    responseToTelCore(mclResponse);
}

void RmcCommSimRequestHandler::handleSprintRsuGetNonce(const sp<RfxMclMessage>& msg) {
    int err = 0;
    String8 cmd("");
    RfxAtLine *pLine = NULL;
    sp<RfxAtResponse> atResponse;
    sp<RfxMclMessage> mclResponse;
    char *nonce = NULL;
    RIL_RsuRequest* request = (RIL_RsuRequest*)(msg->getData()->getData());
    RIL_RsuResponse* response = (RIL_RsuResponse*)calloc(1,
            sizeof(RIL_RsuResponse));
    RFX_ASSERT(response != NULL);
    response->opId = request->opId;
    response->requestId = request->requestId;

    logD(mTag, "[RSU-SIMLOCK] handleSprintRsuGetNonce...");
    cmd.append(String8::format("AT+EUULK=1,\"%s\"", request->data));
    atResponse = atSendCommandSingleline(cmd, "+EUULK:");

#ifdef SML_UT_TEST
    logE(mTag, "[RSU-SIMLOCK] UT fake data!!!!");

    char nonceStr[50];
    strcpy(nonceStr, "SSBhbSBPSw");
    nonce = nonceStr;
    response->data = nonce;
    printReducedLog("[RSU-SIMLOCK] handleSprintRsuGetNonce ", response->data);

    mclResponse = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
    responseToTelCore(mclResponse);
    free(response);
    return;
#endif

    if (atResponse == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleSprintRsuGetNonce atResponse is null");
        goto error;
    }
    if (atResponse->isAtResponseFail()) {
        logE(mTag, "[RSU-SIMLOCK] handleSprintRsuGetNonce isAtResponseFail = %d",
                atResponse->isAtResponseFail());
        goto error;
    }
    pLine = atResponse->getIntermediates();
    if (pLine == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleSprintRsuGetNonce pLine is null");
        goto error;
    }
    pLine->atTokStart(&err);
    if (err < 0) {
        logE(mTag, "[RSU-SIMLOCK] handleSprintRsuGetNonce atTokStart error");
        goto error;
    }

    nonce = pLine->atTokNextstr(&err);
    if (err < 0 || nonce == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleSprintRsuGetNonce err < 0 or nonce is NULL");
        goto error;
    }
    response->data = nonce;
    printReducedLog("[RSU-SIMLOCK] handleSprintRsuGetNonce ", response->data);

    mclResponse = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
    responseToTelCore(mclResponse);
    free(response);
    return;
error:
    free(response);
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_GENERIC_FAILURE,
            RfxVoidData(), msg);
    responseToTelCore(mclResponse);
}

void RmcCommSimRequestHandler::handleSprintRsuSetUnlockCode(const sp<RfxMclMessage>& msg) {
    int err = 0;
    String8 cmd("");
    sp<RfxAtResponse> atResponse;
    sp<RfxMclMessage> mclResponse;
    RIL_RsuRequest* request = (RIL_RsuRequest*)(msg->getData()->getData());
    RIL_RsuResponse* response = (RIL_RsuResponse*)calloc(1,
            sizeof(RIL_RsuResponse));
    RFX_ASSERT(response != NULL);
    response->opId = request->opId;
    response->requestId = request->requestId;

    logD(mTag, "[RSU-SIMLOCK] handleSprintRsuSetUnlockCode...");
    cmd.append(String8::format("AT+EUULK=2,%d,\"%s\"", request->reserveInt1, request->data));
    atResponse = atSendCommandSingleline(cmd, "+EUULK:");

#ifdef SML_UT_TEST
    printReducedLog("[RSU-SIMLOCK] handleSprintRsuSetUnlockCode ", request->data);
    for (int i=0; i<strlen(request->data); i++) {
        logD(mTag, "[RSU-SIMLOCK] request->data[%d]:%X", i, request->data[i]);
    }
    logE(mTag, "[RSU-SIMLOCK] UT fake data!!!!");
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
    responseToTelCore(mclResponse);
    free(response);
    return;
#endif

    if (atResponse == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleSprintRsuSetUnlockCode atResponse is null");
        goto error;
    }
    if (atResponse->isAtResponseFail()) {
        logE(mTag, "[RSU-SIMLOCK] handleSprintRsuSetUnlockCode isAtResponseFail = %d",
                atResponse->isAtResponseFail());
        goto error;
    }

    err = atResponse->getError();
    if (err < 0) {
        logE(mTag, "RSU-SIMLOCK] handleSprintRsuSetUnlockCode getError err = %d", err);
        goto error;
    }

    if (atResponse->getSuccess() == 0) {
        logE(mTag, "RSU-SIMLOCK] handleSprintRsuSetUnlockCode CMR err = %d",
                atResponse->atGetCmeError());
        goto error;
    }

    logD(mTag, "[RSU-SIMLOCK] handleSprintRsuSetUnlockCode success");

    mclResponse = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
    responseToTelCore(mclResponse);
    free(response);
    return;
error:
    free(response);
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_GENERIC_FAILURE,
            RfxVoidData(), msg);
    responseToTelCore(mclResponse);
}

void RmcCommSimRequestHandler::handleCommonRsuRequest(const sp<RfxMclMessage>& msg) {
    RIL_RsuRequest* request = (RIL_RsuRequest*)(msg->getData()->getData());

    switch(request->requestId) {
        case RSU_COMMON_REQUEST_GET_LOCK_INFO:
            handleCommonRsuGetLockInfo(msg);
            return;

        case RSU_COMMON_REQUEST_GET_CAT_INFO:
            handleCommonRsuGetCatInfo(msg);
            return;

        case RSU_COMMON_REQUEST_GET_LOCK_STATUS:
            handleCommonRsuGetLockStatus(msg);
            return;

        case RSU_COMMON_REQUEST_VERIFY_PIN:
            if (request->reserveInt1 == RIL_RSU_LOCK_TYPE_TF_STATUS) {
                handleTfRsuVerifyStatus(msg);
                return;
            } else {
                logE(mTag, "[RSU-SIMLOCK] RSU_COMMON_REQUEST_VERIFY_PIN: unknow lock type: %d",
                        request->reserveInt1);
            }
            break;

        default:
            logE(mTag, "[RSU-SIMLOCK] handleCommonRsuRequest: unknow requestId: %d",
                                    request->requestId);
            break;
    }

    sp<RfxMclMessage> mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
                    RIL_E_REQUEST_NOT_SUPPORTED, RfxVoidData(), msg);
    responseToTelCore(mclResponse);
}

void RmcCommSimRequestHandler::handleCommonRsuGetLockInfo(const sp<RfxMclMessage>& msg) {
    String8 cmd("");
    sp<RfxAtResponse> atResponse;
    sp<RfxMclMessage> mclResponse;
    RIL_RsuRequest* request = (RIL_RsuRequest*)(msg->getData()->getData());
    RIL_RsuResponse* response = (RIL_RsuResponse*)calloc(1,
            sizeof(RIL_RsuResponse));
    uint8_t carrierId = 0xff;
    int supportedCats = 0;
    int lockStatus = 0;
    int isLockFuse = 0;
    int isRsu = 0;
    int rule = 0;
    int subrule = 0; //currently only support SIMLOCK_SUBSCRIPTION_POLICY_INDEPENDENT

    RFX_ASSERT(response != NULL);
    response->opId = request->opId;
    response->requestId = request->requestId;

    logD(mTag, "[RSU-SIMLOCK] handleCommonRsuGetLockInfo...");
    carrierId = smlGetCarrierId();
    supportedCats = smlGetSupportedCats();
    lockStatus = smlGetLockStatus(carrierId, &isRsu, NULL);
    isLockFuse = smlIsEnabled();
    rule = smlGetLockRule();

    //compute the status value
    response->status |= supportedCats << LOCK_INFO_SUPPORTED_CATS_OFFSET;
    response->status |= (carrierId << LOCK_INFO_CARRIER_OFFSET)
            | ((lockStatus << LOCK_INFO_LOCK_STATUS_OFFSET) & LOCK_INFO_LOCK_STATUS_MASK)
            | (isLockFuse << LOCK_INFO_LOCK_FUSE_OFFSET)
            | (isRsu << LOCK_INFO_IS_RSU_OFFSET);
    response->reserveInt1 = rule | (subrule << 8);
    response->version = 0x01;
    logD(mTag, "[RSU-SIMLOCK] handleCommonRsuGetLockInfo, status=0X%X, rule=%d, version=%d",
            response->status, rule, response->version);
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
    responseToTelCore(mclResponse);
    free(response);
    return;
}

uint8_t RmcCommSimRequestHandler::smlGetCarrierId() {
    int err = 0;
    String8 cmd("");
    RfxAtLine *pLine = NULL;
    sp<RfxAtResponse> atResponse;
    uint8_t carrierId = 0xff;

    cmd.append(String8::format("AT+ESMLGEN=0"));
    atResponse = atSendCommandSingleline(cmd, "+ESMLGEN:");
    if (atResponse == NULL) {
        logE(mTag, "[RSU-SIMLOCK] smlGetCarrierId atResponse is null");
        goto error;
    }
    if (atResponse->isAtResponseFail()) {
        logE(mTag, "[RSU-SIMLOCK] smlGetCarrierId isAtResponseFail = %d",
                atResponse->isAtResponseFail());
        goto error;
    }
    pLine = atResponse->getIntermediates();
    if (pLine == NULL) {
        logE(mTag, "[RSU-SIMLOCK] smlGetCarrierId pLine is null");
        goto error;
    }
    pLine->atTokStart(&err);
    if (err < 0) {
        logE(mTag, "[RSU-SIMLOCK] smlGetCarrierId atTokStart error");
        goto error;
    }
    carrierId = (uint8_t)(pLine->atTokNextint(&err));
    if (err < 0) {
        logE(mTag, "[RSU-SIMLOCK] smlGetCarrierId err < 0");
        carrierId = 0xff;
        goto error;
    }
    return carrierId;
error:
    return carrierId;
}

int RmcCommSimRequestHandler::smlGetSupportedCats() {
    int supportedCats = 0;

    supportedCats |= (0x1 << SML_CATEGORY_3GPP_NW);
    supportedCats |= (0x1 << SML_CATEGORY_3GPP_NS);
    supportedCats |= (0x1 << SML_CATEGORY_3GPP_SP);
    supportedCats |= (0x1 << SML_CATEGORY_3GPP_CP);
    supportedCats |= (0x1 << SML_CATEGORY_3GPP_SIM);
    supportedCats |= (0x1 << SML_CATEGORY_NS_SP);
    supportedCats |= (0x1 << SML_CATEGORY_SIM_C);

    return supportedCats;
}

/**
 * Get SIM ME Lock status no matter there's sim or not.
 *   @pOrgStatus -- return original status in blob data if not null.
 *       currently, only VzW and TMO rsu are supprted.
 *
 * 0 -- unlocked
 * 1 -- locked
 */
int RmcCommSimRequestHandler::smlGetLockStatus(uint8_t carrierId, int *pIsRsu, int *pOrgStatus) {
    int lockStatus = -1;
    int isRsu = 1;

    int err = 0;
    String8 cmd("");
    RfxAtLine *pLine = NULL;
    sp<RfxAtResponse> atResponse;
    int unlockCode = -1;
    int temp;
    char *pdata = NULL;

    logD(mTag, "smlGetLockStatus carrierId %d.", carrierId);
    switch (carrierId) {
        case SML_CARRIER_NONE:
            lockStatus = 0;
            if (pIsRsu != NULL) {
                *pIsRsu = 0;
            }
            logD(mTag, "smlGetLockStatus: SML_CARRIER_NONE!");
            return lockStatus;

        case SML_CARRIER_SPRINT_RSU:
            /*
             * AT CMD:
             *     +EUULK?
             * response: +EUULK:<unlock_code>
             * unlock_code: 0/1/2, 2 -- unlocked
             */
            cmd.append(String8::format("AT+EUULK?"));
            atResponse = atSendCommandSingleline(cmd, "+EUULK:");
            if (atResponse == NULL || atResponse->isAtResponseFail())
                break;
            pLine = atResponse->getIntermediates();
            if (pLine == NULL)
                break;
            pLine->atTokStart(&err);
            if (err < 0)
                break;
            unlockCode = pLine->atTokNextint(&err);
            if (err < 0)
                break;
            lockStatus = unlockCode == 2 ? 0 : 1;
            break;

        case SML_CARRIER_ATT_RSU:
        case SML_CARRIER_TMO_TT_RSU:
            /*
             * ttGetData(msg, request, "AT+EATTSLB=4", "+EATTSLB:");
             * response: +EATTSLB:<len>,<str_data>
             * unlock_status: 4 bytes
             *      3 x MSB: reserved -- "000000"
             *      LSB: status
             *          "00" -- locked
             *          "01" -- temporarily unlocked
             *          "02" -- permanently unlocked
             *          "03" -- partial unlocked
             */
            cmd.append(String8::format("AT+EATTSLB=4"));
            atResponse = atSendCommandSingleline(cmd, "+EATTSLB:");
            if (atResponse == NULL || atResponse->isAtResponseFail())
                break;
            pLine = atResponse->getIntermediates();
            if (pLine == NULL)
                break;
            pLine->atTokStart(&err);
            if (err < 0)
                break;
            temp = pLine->atTokNextint(&err);
            if (err < 0)
                break;
            pdata = pLine->atTokNextstr(&err);
            if (err < 0)
                break;
            if (pdata != NULL && strlen(pdata) >= 2 * 4) {
                lockStatus = *(pdata + 7) == '2' ? 0 : 1;
            }
            break;

        case SML_CARRIER_TMO_MODEM_RSU:
            /*
             * AT CMD:
             *     +ESMLRSU=3,3,""
             * response: +ESMLRSU:3,3,10,"0000000000"
             *  response: +ESMLRSU:3,3,<len>,<str_data>
             *   1st byte is lock_status
             *        0 -- locked
             *        1 -- temporary unlocked
             *        2 -- permanent unlocked
             */
            cmd.append(String8::format("AT+ESMLRSU=3,3,\"\""));
            logD(mTag, "AT+ESMLRSU=3,3,\"\"");
#ifdef SML_UT_TEST
            atResponse = smlSendAtSingleLine(cmd,  "+ESMLRSU:");
#else
            atResponse = atSendCommandSingleline(cmd, "+ESMLRSU:");
#endif
            if (atResponse == NULL or atResponse->isAtResponseFail())
                break;
            pLine = atResponse->getIntermediates();
            if (pLine == NULL)
                break;
            pLine->atTokStart(&err);
            if (err < 0)
                break;
            temp = pLine->atTokNextint(&err);
            if (err < 0)
                break;
            temp = pLine->atTokNextint(&err);
            if (err < 0)
                break;
            temp = pLine->atTokNextint(&err);
            if (err < 0)
                break;
            pdata = pLine->atTokNextstr(&err);
            if (err < 0)
                break;
            if (pdata != NULL && strlen(pdata) > 2) {
                lockStatus = *(pdata + 1) == '2' ? 0 : 1;
                if (pOrgStatus != NULL) {
                    *pOrgStatus = *(pdata + 1) - '0';
                }
            }
            break;

        case SML_CARRIER_VZW_RSU:
            /*
             * AT CMD:
             *     +ESMLRSU=1,3
             *  response: +ESMLRSU:1,3,<str_unlockstatus>,<str_left_time>
             *   1st byte is lock_status
             *        0 -- locked
             *        1 -- temporary unlocked
             *        2 -- permanent unlocked
             */
            cmd.append(String8::format("AT+ESMLRSU=1,3"));
            logD(mTag, "AT+ESMLRSU=1,3,");
#ifdef SML_UT_TEST
            atResponse = smlSendAtSingleLine(cmd,  "+ESMLRSU:");
#else
            atResponse = atSendCommandSingleline(cmd, "+ESMLRSU:");
#endif
            if (atResponse == NULL or atResponse->isAtResponseFail())
                break;
            pLine = atResponse->getIntermediates();
            if (pLine == NULL)
                break;
            pLine->atTokStart(&err);
            if (err < 0)
                break;
            temp = pLine->atTokNextint(&err);
            if (err < 0)
                break;
            temp = pLine->atTokNextint(&err);
            if (err < 0)
                break;
            pdata = pLine->atTokNextstr(&err);
            if (err < 0)
                break;
            unlockCode = atoi(pdata);
            lockStatus = unlockCode == 2 ? 0 : 1;
            if (pOrgStatus != NULL) {
                *pOrgStatus = unlockCode;
            }
            break;

        default:
            isRsu = 0;
            break;
    };
    if (!isRsu) {
        RIL_SimMeLockInfo lockInfo;
        lockStatus = 0;
        getPersoRemainRetry(MAX_SIM_ME_LOCK_CAT_NUM - 1, &lockInfo);
        for (int i=0; i<MAX_SIM_ME_LOCK_CAT_NUM; i++) {
            if (lockInfo.catagory[i].state == 1) {
                lockStatus = 1;
            }
        }
    }
    if (pIsRsu != NULL) {
        *pIsRsu = isRsu;
    }
    logD(mTag, "smlGetLockStatus return lockStatus=%d, isRsu=%d.", lockStatus, isRsu);
    return lockStatus;
}

/*
 * If sim lock is enabled or configured in MD side
 *
 * return:
 *     1 -- configured
 *     0 -- not configured
 */
int RmcCommSimRequestHandler::smlIsEnabled() {
    int state = 0;
    //state: 0 -- sim lock enabled, 1 -- not enabled
    state = getNonSlotMclStatusManager()->getIntValue(RFX_STATUS_KEY_SML_SLOT_LOCK_POLICY_LOCK_STATE,
            0);
    return !state;
}

int RmcCommSimRequestHandler::smlIsRsu(int carrierId) {
    if (carrierId == SML_CARRIER_SPRINT_RSU
            || carrierId == SML_CARRIER_TMO_TT_RSU
            || carrierId == SML_CARRIER_TMO_MODEM_RSU
            || carrierId == SML_CARRIER_VZW_RSU
            || carrierId == SML_CARRIER_ATT_RSU) {
        return 1;
    }

    return 0;
}

//All SIM slots require to have a valid carrier SIM
#define SIMLOCK_SLOT_POLICY_SAME_ON_ALL_SLOTS           0
//Each SIM slot is locked to a different carrier
#define SIMLOCK_SLOT_POLICY_UNIQUE_FOR_EACH_SLOT        1
//only primary slot requres a valid carrier SIM
#define SIMLOCK_SLOT_POLICY_LOCK_ONLY_SLOT_1            2
//if primary slot has a valid carrier SIM other slots work with any SIM
#define SIMLOCK_SLOT_POLICY_VALID_CARD_MUST_ON_SLOT_1   3
//if any slot has a valid carrier SIM other slots work with any SIM
#define SIMLOCK_SLOT_POLICY_VALID_CARD_MUST_ON_A_SLOT   4

int RmcCommSimRequestHandler::smlGetLockRule() {
    int policy = SIMLOCK_SLOT_POLICY_SAME_ON_ALL_SLOTS;

    int mtkPolicy = getNonSlotMclStatusManager()->getIntValue(RFX_STATUS_KEY_SML_SLOT_LOCK_POLICY, 0);
    switch (mtkPolicy) {
        case SML_SLOT_LOCK_POLICY_ONLY_SLOT1:
        case SML_SLOT_LOCK_POLICY_ONLY_SLOT2:
            policy = SIMLOCK_SLOT_POLICY_LOCK_ONLY_SLOT_1;
            break;

        case SML_SLOT_LOCK_POLICY_ALL_SLOTS_INDIVIDUAL:
            policy = SIMLOCK_SLOT_POLICY_UNIQUE_FOR_EACH_SLOT;
            break;

        case SML_SLOT_LOCK_POLICY_LK_SLOT1:
        case SML_SLOT_LOCK_POLICY_LK_SLOT2:
            policy = SIMLOCK_SLOT_POLICY_VALID_CARD_MUST_ON_SLOT_1;
            break;

        case SML_SLOT_LOCK_POLICY_LK_SLOTA:
        case SML_SLOT_LOCK_POLICY_LK_SLOTA_RESTRICT_INVALID_ECC_FOR_VALID_NO_SERVICE:
            policy = SIMLOCK_SLOT_POLICY_VALID_CARD_MUST_ON_A_SLOT;
            break;

        case SML_SLOT_LOCK_POLICY_LK_SLOTA_RESTRICT_INVALID_CS:
            logE(mTag, "Not support MTK_LOCK_POLICY_LK_SLOTA_RESTRICT_INVALID_CS!");
            break;

        case SML_SLOT_LOCK_POLICY_LK_SLOTA_RESTRICT_REVERSE:
            logE(mTag, "Not support MTK_LOCK_POLICY_LK_SLOTA_RESTRICT_REVERSE!");
            break;

        default:
            break;
    }

    return policy;
}

void RmcCommSimRequestHandler::handleCommonRsuGetCatInfo(const sp<RfxMclMessage>& msg) {
    String8 cmd("");
    sp<RfxAtResponse> atResponse;
    sp<RfxMclMessage> mclResponse;
    RIL_RsuRequest* request = (RIL_RsuRequest*)(msg->getData()->getData());
    RIL_RsuResponse* response = (RIL_RsuResponse*)calloc(1,
            sizeof(RIL_RsuResponse));
    int cat = request->reserveInt1;
    uint8_t maxRetry = 0;
    uint8_t remainRetry = 0;
    int isLocked = 0;

    RFX_ASSERT(response != NULL);
    if (cat < 0 || cat >= MAX_SIM_ME_LOCK_CAT_NUM) {
        logE(mTag, "[RSU-SIMLOCK] handleCommonRsuGetCatInfo invalid cat(%d)", cat);
        cat = 0;
    }
    response->opId = request->opId;
    response->requestId = request->requestId;

    logD(mTag, "[RSU-SIMLOCK] handleCommonRsuGetCatInfo(%d)", cat);
    if (!smlIsRsu(smlGetCarrierId())) {
        RIL_SimMeLockInfo lockInfo;
        maxRetry = smlGetMaxRetry(cat);
        remainRetry = getPersoRemainRetry(cat, &lockInfo);
        if (lockInfo.catagory[cat].state == 1) {
            isLocked = 1;
        }
    } else {
        logD(mTag, "[RSU-SIMLOCK] handleCommonRsuGetCatInfo, RSU has no cat info");
    }

    //compute the status value
    response->status |= cat << CAT_INFO_CAT_OFFSET;
    response->status |= maxRetry << CAT_INFO_MAX_RETRY_OFFSET;
    response->status |= (remainRetry << CAT_INFO_REMAIN_RETRY_OFFSET)
            | (isLocked << CAT_INFO_IS_LOCKED_OFFSET);
    logD(mTag, "[RSU-SIMLOCK] handleCommonRsuGetCatInfo, status=0X%X", response->status);
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
    responseToTelCore(mclResponse);
    free(response);
    return;
}

uint8_t RmcCommSimRequestHandler::smlGetMaxRetry(int cat) {
    int err = 0;
    String8 cmd("");
    RfxAtLine *pLine = NULL;
    sp<RfxAtResponse> atResponse;
    uint8_t maxRetry = 0;
    int atCat = 0, atRetry = 0;

    cmd.append(String8::format("AT+ESMLGEN=1"));
    atResponse = atSendCommandSingleline(cmd, "+ESMLGEN:");
    if (atResponse == NULL) {
        logE(mTag, "[RSU-SIMLOCK] smlGetMaxRetry atResponse is null");
        goto error;
    }
    if (atResponse->isAtResponseFail()) {
        logE(mTag, "[RSU-SIMLOCK] smlGetMaxRetry isAtResponseFail = %d",
                atResponse->isAtResponseFail());
        goto error;
    }
    pLine = atResponse->getIntermediates();
    if (pLine == NULL) {
        logE(mTag, "[RSU-SIMLOCK] smlGetMaxRetry pLine is null");
        goto error;
    }
    pLine->atTokStart(&err);
    if (err < 0) {
        logE(mTag, "[RSU-SIMLOCK] smlGetMaxRetry atTokStart error");
        goto error;
    }
    do {
        atCat = pLine->atTokNextint(&err);
        if (err < 0) {
            logE(mTag, "[RSU-SIMLOCK] smlGetMaxRetry err < 0");
            goto error;
        }
        atRetry = pLine->atTokNextint(&err);
        if (err < 0) {
            logE(mTag, "[RSU-SIMLOCK] smlGetMaxRetry err < 0");
            goto error;
        }
        if (atCat == cat) {
            maxRetry = atRetry;
            break;
        }

    } while (1);
    logD(mTag, "[RSU-SIMLOCK] smlGetMaxRetry return %d", maxRetry);
    return maxRetry;
error:
    logE(mTag, "[RSU-SIMLOCK] smlGetMaxRetry return error");
    return 0;
}

/**
 * Veritfy TF Status
 *
 *  RIL_RsuRequest:
 *    data: verify key
 *    reserveInt1: lockType -- no usage
 *  RIL_RsuResponse:
 *    None
 *
 * AT command
 *  AT+ESMLGEN=<op>[,<operator_id>,<operator_op>,<key>]
 *
 *   If op is 0:
 *     +ESMLGEN: <carrier_id>
 *     OK
 *     ERROR/+CME ERROR: <err>
 *   If op is 1:
 *     +ESMLGEN: list of <cat>,<max_retry_count>
 *     OK
 *     ERROR/+CME ERROR: <err>
 *   If op is 2:
 *    and if operator_id = 0
 *    and if operator_op = 0
 *    OK
 *    ERROR/+CME ERROR: <err>
 * 1.2	Field
 * Type	Short name	Parameter/comment
 * Integer  op  0   Get carrier id
 *              1   Get max retry count
 *              2   Operator specific operation
 * Integer	operator_id	0 – Tracfone
 * Integer	operator_op	Operator specific operation
 *   0 – TFSTATUS Verify
 *       string key key
 */
void RmcCommSimRequestHandler::handleTfRsuVerifyStatus(const sp<RfxMclMessage>& msg) {
    String8 cmd("");
    sp<RfxAtResponse> atResponse;
    sp<RfxMclMessage> mclResponse;
    RIL_RsuRequest* request = (RIL_RsuRequest*)(msg->getData()->getData());
    RIL_RsuResponse* response = (RIL_RsuResponse*)calloc(1,
            sizeof(RIL_RsuResponse));

    RFX_ASSERT(response != NULL);
    if (request==NULL || request->data == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleTfRsuVerifyStatus invalid key");
        goto error;
    }
    response->opId = request->opId;
    response->requestId = request->requestId;

    logD(mTag, "[RSU-SIMLOCK] handleTfRsuVerifyStatus");
    cmd.append(String8::format("AT+ESMLGEN=2,0,0,\"%s\"", request->data));
    atResponse = atSendCommand(cmd.string());
    if (atResponse == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleTfRsuVerifyStatus atResponse is null");
        goto error;
    }
    if (atResponse->getError() < 0 || atResponse->getSuccess() == 0) {
        logE(mTag, "[RSU-SIMLOCK] handleTfRsuVerifyStatus at response error = %d",
                atResponse->getError());
        goto error;
    }
    logD(mTag, "[RSU-SIMLOCK] handleTfRsuVerifyStatus return success");
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
    responseToTelCore(mclResponse);
    free(response);
    return;
error:
    logD(mTag, "[RSU-SIMLOCK] handleTfRsuVerifyStatus return error");
    free(response);
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_GENERIC_FAILURE,
            RfxVoidData(), msg);
    responseToTelCore(mclResponse);
}

//@} add for supporting one customer's specific API

void RmcCommSimRequestHandler::handleCommonRsuGetLockStatus(const sp<RfxMclMessage>& msg) {
    String8 cmd("");
    sp<RfxAtResponse> atResponse;
    sp<RfxMclMessage> mclResponse;
    RIL_RsuRequest* request = (RIL_RsuRequest*)(msg->getData()->getData());
    RIL_RsuResponse* response = (RIL_RsuResponse*)calloc(1,
            sizeof(RIL_RsuResponse));
    uint8_t carrierId = 0xff;
    int lockStatus = -1;
    int isRsu = 0;
    int policy = 0;

    RFX_ASSERT(response != NULL);
    response->opId = request->opId;
    response->requestId = request->requestId;

    logD(mTag, "[RSU-SIMLOCK] handleCommonRsuGetLockStatus...");
    //compute carrier Id, not use smlGetCarrierId() because AT+ESMLGEN=0 is added for specific
    // customer, not supported by all chips
    policy = getNonSlotMclStatusManager()->getIntValue(RFX_STATUS_KEY_SML_SLOT_LOCK_POLICY, 0);
    if (policy == SML_SLOT_LOCK_POLICY_ALL_SLOTS_INDIVIDUAL_AND_RSU_VZW) {
        carrierId = SML_CARRIER_VZW_RSU;
    } else if (policy == SML_SLOT_LOCK_POLICY_LK_SLOTA_RSU_TMO) {
        carrierId = SML_CARRIER_TMO_MODEM_RSU;
    } else {
            char property_value[RFX_PROPERTY_VALUE_MAX] = {0};
            rfx_property_get("ro.vendor.sim_me_lock_mode", property_value, "");
            if ((strlen(property_value) > 0) && (strcmp(property_value, "1203") == 0)){
                carrierId = SML_CARRIER_VZW_RSU;
            } else if ((strlen(property_value) > 0) && (strcmp(property_value, "800") == 0)) {
                carrierId = SML_CARRIER_TMO_MODEM_RSU;
            }

    }
    smlGetLockStatus(carrierId, &isRsu, &lockStatus);

    response->status = lockStatus;
    logD(mTag, "[RSU-SIMLOCK] handleCommonRsuGetLockStatus, status=0X%X", response->status);
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
    responseToTelCore(mclResponse);
    free(response);
    return;
}

////////////TFN RSU ////////////
//AP/Modem use the same request value.
enum {
    TFN_RSU_REQUEST_GET_IMEI = 1,
    TFN_RSU_REQUEST_PROCESS_DATA,
    TFN_RSU_REQUEST_GET_LOCK_STATUS,
    TFN_RSU_REQUEST_GENERATE_REQUEST,
    TFN_RSU_REQUEST_RELOCK,
    TFN_RSU_REQUEST_GET_KEY,
};

void RmcCommSimRequestHandler::handleTfnRsuRequest(const sp<RfxMclMessage>& msg) {
    RIL_RsuRequest* request = (RIL_RsuRequest*)(msg->getData()->getData());

    switch(request->requestId) {
        case TFN_RSU_REQUEST_GET_IMEI:
            handleTfnRsuGetImei(msg);
            return;
        case TFN_RSU_REQUEST_PROCESS_DATA:
            handleTfnRsuProcessLockData(msg);
            return;
        case TFN_RSU_REQUEST_GET_LOCK_STATUS:
            handleTfnRsuGetStatus(msg);
            return;
        case TFN_RSU_REQUEST_GENERATE_REQUEST:
            handleTfnRsuGenerateRequest(msg);
            return;
        case TFN_RSU_REQUEST_RELOCK:
            handleTfnRsuRelock(msg);
            return;
        case TFN_RSU_REQUEST_GET_KEY:
            handleTfnRsuGetKey(msg);
            return;
        default:
            break;
    }

    sp<RfxMclMessage> mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
                    RIL_E_GENERIC_FAILURE, RfxVoidData(), msg);
    responseToTelCore(mclResponse);
}

/**
 * Get IMEI from modem
 *  AT+ESMLRSU=5,1
 *  +ESMLRSU:5,1,"<IMEI>"
 */
void RmcCommSimRequestHandler::handleTfnRsuGetImei(const sp<RfxMclMessage>& msg) {
    int err = 0;
    int errCode = 0;

    String8 cmd("");
    RfxAtLine *pLine = NULL;
    sp<RfxAtResponse> atResponse;
    sp<RfxMclMessage> mclResponse;

    int opId = -1;
    int requestId = -1;
    char* imei = NULL;

    RIL_RsuRequest* request = (RIL_RsuRequest*)(msg->getData()->getData());
    RIL_RsuResponse* response = (RIL_RsuResponse*)calloc(1, sizeof(RIL_RsuResponse));
    RFX_ASSERT(response != NULL);
    response->opId = request->opId;
    response->requestId = request->requestId;

    cmd.append(String8::format("AT+ESMLRSU=%d,%d", request->opId, request->requestId));
    logD(mTag, "[RSU-SIMLOCK] AT+ESMLRSU=%d,%d", request->opId, request->requestId);
#ifdef SML_UT_TEST
    atResponse = smlSendAtSingleLine(cmd, "+ESMLRSU:");
#else
    atResponse = atSendCommandSingleline(cmd, "+ESMLRSU:");
#endif
    if (atResponse == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuGetImei atResponse is null");
        goto error;
    }

    if (atResponse->isAtResponseFail()) {
        errCode = atResponse->atGetCmeError();
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuGetImei errCode = %d", errCode);
        response->errCode = errCode;
        mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
                RIL_E_GENERIC_FAILURE,
                RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
        responseToTelCore(mclResponse);
        free(response);
        return;
    }

    pLine = atResponse->getIntermediates();
    if (pLine == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuGetImei pLine is null");
        goto error;
    }
    pLine->atTokStart(&err);
    if (err < 0) {
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuGetImei atTokStart error");
        goto error;
    }

    opId = pLine->atTokNextint(&err);
    if (err < 0 || opId != request->opId) {
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuGetImei err < 0 or opId = %d"
                " not equal ot request opId = %d", opId, request->opId);
        goto error;
    }
    requestId = pLine->atTokNextint(&err);
    if (err < 0 || requestId != request->requestId) {
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuGetImei err < 0 or requestId = %d"
                " not equal ot request requestId = %d", requestId, request->requestId);
        goto error;
    }

    imei = pLine->atTokNextstr(&err);
    if (err < 0 || imei == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuGetImei err < 0 or imei is null");
        goto error;
    }
    response->data = imei;
    printReducedLog("[RSU-SIMLOCK] handleTfnRsuGetImei ", response->data);

    mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
            RIL_E_SUCCESS, RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
    responseToTelCore(mclResponse);
    free(response);
    return;

error:
    free(response);
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
            RIL_E_GENERIC_FAILURE, RfxVoidData(), msg);
    responseToTelCore(mclResponse);
}

/**
 * Input Response msg from TFN Unlock Server to modem
 *  AT+ESMLRSU=5,2,"<simlockData>"
 *  +ESMLRSU:5,2,<err_cause>
 *     No error = 0
 *     Generic error = 1
 *     Data block structure error = 2
 *     Data block version error = 3
 *     Data block signature error = 4
 *     IMEI Validation faulure = 5
 *     CK1 validation failure = 6
 *     CK2 validation failure = 7
 *     CK1+CK2 validation failure = 8
 */
void RmcCommSimRequestHandler::handleTfnRsuProcessLockData(const sp<RfxMclMessage>& msg) {
    int err = 0;
    int errCode = 0;

    String8 cmd("");
    RfxAtLine *pLine = NULL;
    sp<RfxAtResponse> atResponse;
    sp<RfxMclMessage> mclResponse;

    int opId = -1;
    int requestId = -1;

    RIL_RsuRequest* request = (RIL_RsuRequest*)(msg->getData()->getData());
    RIL_RsuResponse* response = (RIL_RsuResponse*)calloc(1, sizeof(RIL_RsuResponse));
    RFX_ASSERT(response != NULL);
    response->opId = request->opId;
    response->requestId = request->requestId;

    cmd.append(String8::format("AT+ESMLRSU=%d,%d,\"%s\"",
            request->opId, request->requestId, request->data));
    logD(mTag, "[RSU-SIMLOCK] AT+ESMLRSU=%d,%d", request->opId, request->requestId);
    printReducedLog("[RSU-SIMLOCK] handleTfnRsuProcessLockData ", request->data);
#ifdef SML_UT_TEST
    atResponse = smlSendAtSingleLine(cmd, "+ESMLRSU:");
#else
    atResponse = atSendCommandSingleline(cmd, "+ESMLRSU:");
#endif
    if (atResponse == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuProcessLockData atResponse is null");
        goto error;
    }

    if (atResponse->isAtResponseFail()) {
        errCode = atResponse->atGetCmeError();
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuProcessLockData errCode = %d", errCode);
        response->errCode = errCode;
        mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
                RIL_E_GENERIC_FAILURE,
                RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
        responseToTelCore(mclResponse);
        free(response);
        return;
    }

    pLine = atResponse->getIntermediates();
    if (pLine == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuProcessLockData pLine is null");
        goto error;
    }
    pLine->atTokStart(&err);
    if (err < 0) {
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuProcessLockData atTokStart error");
        goto error;
    }

    opId = pLine->atTokNextint(&err);
    if (err < 0 || opId != request->opId) {
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuProcessLockData err < 0 or opId = %d"
                " not equal ot request opId = %d", opId, request->opId);
        goto error;
    }
    requestId = pLine->atTokNextint(&err);
    if (err < 0 || requestId != request->requestId) {
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuProcessLockData err < 0 or requestId = %d"
                " not equal ot request requestId = %d", requestId, request->requestId);
        goto error;
    }

    response->errCode = pLine->atTokNextint(&err);
    if (err < 0) {
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuProcessLockData err < 0 when get errCause");
        goto error;
    }
    printReducedLog("[RSU-SIMLOCK] handleTfnRsuProcessLockData ", response->data);

    mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
            RIL_E_SUCCESS, RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
    responseToTelCore(mclResponse);
    free(response);
    return;

error:
    free(response);
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
            RIL_E_GENERIC_FAILURE, RfxVoidData(), msg);
    responseToTelCore(mclResponse);
}

/**
 * Get lock status
 *  AT+ESMLRSU=5,3
 *  +ESMLRSU: 5,3,<unlockStatus>
 */
void RmcCommSimRequestHandler::handleTfnRsuGetStatus(const sp<RfxMclMessage>& msg) {
    int err = 0;
    int errCode = 0;
    String8 cmd("");

    RfxAtLine *pLine = NULL;
    sp<RfxAtResponse> atResponse;
    sp<RfxMclMessage> mclResponse;

    int opId = -1;
    int requestId = -1;

    RIL_RsuRequest* request = (RIL_RsuRequest*)(msg->getData()->getData());
    RIL_RsuResponse* response = (RIL_RsuResponse*)calloc(1, sizeof(RIL_RsuResponse));
    RFX_ASSERT(response != NULL);
    response->opId = request->opId;
    response->requestId = request->requestId;

    cmd.append(String8::format("AT+ESMLRSU=%d,%d",
            request->opId, request->requestId));
    logD(mTag, "[RSU-SIMLOCK] AT+ESMLRSU=%d,%d", request->opId, request->requestId);
#ifdef SML_UT_TEST
    atResponse = smlSendAtSingleLine(cmd, "+ESMLRSU:");
#else
    atResponse = atSendCommandSingleline(cmd, "+ESMLRSU:");
#endif
    if (atResponse == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuGetStatus atResponse is null");
        goto error;
    }

    if (atResponse->isAtResponseFail()) {
        errCode = atResponse->atGetCmeError();
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuGetStatus errCode = %d", errCode);
        response->errCode = errCode;
        mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
                RIL_E_GENERIC_FAILURE,
                RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
        responseToTelCore(mclResponse);
        free(response);
        return;
    }

    pLine = atResponse->getIntermediates();
    if (pLine == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuGetStatus pLine is null");
        goto error;
    }
    pLine->atTokStart(&err);
    if (err < 0) {
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuGetStatus atTokStart error");
        goto error;
    }

    opId = pLine->atTokNextint(&err);
    if (err < 0 || opId != request->opId) {
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuGetStatus err < 0 or opId = %d"
                " not equal ot request opId = %d", opId, request->opId);
        goto error;
    }
    requestId = pLine->atTokNextint(&err);
    if (err < 0 || requestId != request->requestId) {
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuGetStatus err < 0 or requestId = %d"
                " not equal ot request requestId = %d", requestId, request->requestId);
        goto error;
    }

    response->status = pLine->atTokNextint(&err);
    if (err < 0) {
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuGetStatus err < 0 on get status");
        goto error;
    }
    logD(mTag, "[RSU-SIMLOCK] handleTfnRsuGetStatus unlockStatus = %d",
            response->status);

    mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
            RIL_E_SUCCESS, RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
    responseToTelCore(mclResponse);
    free(response);
    return;

error:
    free(response);
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
            RIL_E_GENERIC_FAILURE, RfxVoidData(), msg);
    responseToTelCore(mclResponse);
}

/**
 * Request Simlock engine to generate HMAC on the input <data>.
 *  AT+ESMLRSU=5,4,<data>
 *  +ESMLRSU: 5,4,<hmacData>
 */
void RmcCommSimRequestHandler::handleTfnRsuGenerateRequest(const sp<RfxMclMessage>& msg) {
    int err = 0;
    int errCode = 0;

    String8 cmd("");
    RfxAtLine *pLine = NULL;
    sp<RfxAtResponse> atResponse;
    sp<RfxMclMessage> mclResponse;

    int opId = -1;
    int requestId = -1;
    char* signedJwt = NULL;

    RIL_RsuRequest* request = (RIL_RsuRequest*)(msg->getData()->getData());
    RIL_RsuResponse* response = (RIL_RsuResponse*)calloc(1, sizeof(RIL_RsuResponse));
    RFX_ASSERT(response != NULL);
    response->opId = request->opId;
    response->requestId = request->requestId;

    cmd.append(String8::format("AT+ESMLRSU=%d,%d,\"%s\"",
            request->opId, request->requestId, request->data));
    logD(mTag, "[RSU-SIMLOCK] AT+ESMLRSU=%d,%d", request->opId, request->requestId);
    printReducedLog("[RSU-SIMLOCK] handleTfnRsuGenerateRequest ", request->data);
#ifdef SML_UT_TEST
    atResponse = smlSendAtSingleLine(cmd, "+ESMLRSU:");
#else
    atResponse = atSendCommandSingleline(cmd, "+ESMLRSU:");
#endif
    if (atResponse == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuGenerateRequest atResponse is null");
        goto error;
    }

    if (atResponse->isAtResponseFail()) {
        errCode = atResponse->atGetCmeError();
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuGenerateRequest errCode = %d", errCode);
        response->errCode = errCode;
        mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
                RIL_E_GENERIC_FAILURE,
                RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
        responseToTelCore(mclResponse);
        free(response);
        return;
    }

    pLine = atResponse->getIntermediates();
    if (pLine == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuGenerateRequest pLine is null");
        goto error;
    }
    pLine->atTokStart(&err);
    if (err < 0) {
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuGenerateRequest atTokStart error");
        goto error;
    }

    opId = pLine->atTokNextint(&err);
    if (err < 0 || opId != request->opId) {
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuGenerateRequest err < 0 or opId = %d"
                " not equal ot request opId = %d", opId, request->opId);
        goto error;
    }
    requestId = pLine->atTokNextint(&err);
    if (err < 0 || requestId != request->requestId) {
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuGenerateRequest err < 0 or requestId = %d"
                " not equal ot request requestId = %d", requestId, request->requestId);
        goto error;
    }

    signedJwt = pLine->atTokNextstr(&err);
    if (err < 0 || signedJwt == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuGenerateRequest err < 0 or signedJwt is null");
        goto error;
    }
    response->data = signedJwt;
    printReducedLog("[RSU-SIMLOCK] handleTfnRsuGenerateRequest ", response->data);
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
            RIL_E_SUCCESS, RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
    responseToTelCore(mclResponse);
    free(response);
    return;

error:
    free(response);
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
            RIL_E_GENERIC_FAILURE, RfxVoidData(), msg);
    responseToTelCore(mclResponse);
}

/**
 * Relock device
 *  AT+ESMLRSU=5,5
 *  +ESMLRSU=5,5,<result>
 *    result: 1 -- OK
 *            other -- error
 *  OK (or) +CME ERROR: <err_cause>
 */
void RmcCommSimRequestHandler::handleTfnRsuRelock(const sp<RfxMclMessage>& msg) {
    int err = 0;
    int errCode = 0;

    String8 cmd("");
    RfxAtLine *pLine = NULL;
    sp<RfxAtResponse> atResponse;
    sp<RfxMclMessage> mclResponse;

    int opId = -1;
    int requestId = -1;

    RIL_RsuRequest* request = (RIL_RsuRequest*)(msg->getData()->getData());
    RIL_RsuResponse* response = (RIL_RsuResponse*)calloc(1, sizeof(RIL_RsuResponse));
    RFX_ASSERT(response != NULL);
    response->opId = request->opId;
    response->requestId = request->requestId;

    cmd.append(String8::format("AT+ESMLRSU=%d,%d", request->opId, request->requestId));
    logD(mTag, "[RSU-SIMLOCK] AT+ESMLRSU=%d,%d", request->opId, request->requestId);
    printReducedLog("[RSU-SIMLOCK] handleTfnRsuRelock ", request->data);
#ifdef SML_UT_TEST
    atResponse = smlSendAtSingleLine(cmd, "+ESMLRSU:");
#else
    atResponse = atSendCommandSingleline(cmd, "+ESMLRSU:");
#endif
    if (atResponse == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuRelock atResponse is null");
        goto error;
    }

    if (atResponse->isAtResponseFail()) {
        errCode = atResponse->atGetCmeError();
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuRelock errCode = %d", errCode);
        response->errCode = errCode;
        mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
                RIL_E_GENERIC_FAILURE,
                RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
        responseToTelCore(mclResponse);
        free(response);
        return;
    }

    pLine = atResponse->getIntermediates();
    if (pLine == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuRelock pLine is null");
        goto error;
    }
    pLine->atTokStart(&err);
    if (err < 0) {
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuRelock atTokStart error");
        goto error;
    }

    opId = pLine->atTokNextint(&err);
    if (err < 0 || opId != request->opId) {
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuRelock err < 0 or opId = %d"
                " not equal ot request opId = %d", opId, request->opId);
        goto error;
    }
    requestId = pLine->atTokNextint(&err);
    if (err < 0 || requestId != request->requestId) {
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuRelock err < 0 or requestId = %d"
                " not equal ot request requestId = %d", requestId, request->requestId);
        goto error;
    }

    response->errCode = pLine->atTokNextint(&err);
    if (err < 0) {
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuRelock err < 0 on get result");
        goto error;
    }
    logD(mTag, "[RSU-SIMLOCK] handleTfnRsuRelock result = %d",
            response->errCode);
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
            RIL_E_SUCCESS, RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
    responseToTelCore(mclResponse);
    free(response);
    return;

error:
    free(response);
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
            RIL_E_GENERIC_FAILURE, RfxVoidData(), msg);
    responseToTelCore(mclResponse);
}

/**
 * Get secret key
 *  AT+ESMLRSU=5,6
 *  +ESMLRSU: 5,6,<SecretKey>
 */
void RmcCommSimRequestHandler::handleTfnRsuGetKey(const sp<RfxMclMessage>& msg) {
    int err = 0;
    int errCode = 0;

    String8 cmd("");
    RfxAtLine *pLine = NULL;
    sp<RfxAtResponse> atResponse;
    sp<RfxMclMessage> mclResponse;

    int opId = -1;
    int requestId = -1;
    char* sharedKey = NULL;

    RIL_RsuRequest* request = (RIL_RsuRequest*)(msg->getData()->getData());
    RIL_RsuResponse* response = (RIL_RsuResponse*)calloc(1, sizeof(RIL_RsuResponse));
    RFX_ASSERT(response != NULL);
    response->opId = request->opId;
    response->requestId = request->requestId;

    cmd.append(String8::format("AT+ESMLRSU=%d,%d",
            request->opId, request->requestId));
    logD(mTag, "[RSU-SIMLOCK] AT+ESMLRSU=%d,%d", request->opId, request->requestId);
    printReducedLog("[RSU-SIMLOCK] handleTfnRsuGetKey ", request->data);
#ifdef SML_UT_TEST
    atResponse = smlSendAtSingleLine(cmd, "+ESMLRSU:");
#else
    atResponse = atSendCommandSingleline(cmd, "+ESMLRSU:");
#endif
    if (atResponse == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuGetKey atResponse is null");
        goto error;
    }

    if (atResponse->isAtResponseFail()) {
        errCode = atResponse->atGetCmeError();
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuGetKey errCode = %d", errCode);
        response->errCode = errCode;
        mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
                RIL_E_GENERIC_FAILURE,
                RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
        responseToTelCore(mclResponse);
        free(response);
        return;
    }

    pLine = atResponse->getIntermediates();
    if (pLine == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuGetKey pLine is null");
        goto error;
    }
    pLine->atTokStart(&err);
    if (err < 0) {
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuGetKey atTokStart error");
        goto error;
    }

    opId = pLine->atTokNextint(&err);
    if (err < 0 || opId != request->opId) {
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuGetKey err < 0 or opId = %d"
                " not equal ot request opId = %d", opId, request->opId);
        goto error;
    }
    requestId = pLine->atTokNextint(&err);
    if (err < 0 || requestId != request->requestId) {
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuGetKey err < 0 or requestId = %d"
                " not equal ot request requestId = %d", requestId, request->requestId);
        goto error;
    }

    sharedKey = pLine->atTokNextstr(&err);
    if (err < 0 || sharedKey == NULL) {
        logE(mTag, "[RSU-SIMLOCK] handleTfnRsuGetKey err < 0 or sharedKey is null");
        goto error;
    }
    response->data = sharedKey;
    printReducedLog("[RSU-SIMLOCK] handleTfnRsuGetKey ", response->data);

    mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
            RIL_E_SUCCESS, RfxRsuResponseData(response, sizeof(RIL_RsuResponse)), msg);
    responseToTelCore(mclResponse);
    free(response);
    return;

error:
    free(response);
    mclResponse = RfxMclMessage::obtainResponse(msg->getId(),
            RIL_E_GENERIC_FAILURE, RfxVoidData(), msg);
    responseToTelCore(mclResponse);
}
////////////TFN RSU END///////////////////
sp<RfxAtResponse> RmcCommSimRequestHandler::smlSendAtSingleLine(const String8 &command,
        const char* prefix) {
    atSendCommandSingleline(command, prefix);
    RFX_UNUSED(prefix);
    char respStr[100];
    char *atResp;

    ///// TMO
    logE(mTag, "FAKE AT: %s", command.string());
    if (strStartsWith(command.string(), "AT+ESMLRSU=3,1")) { //createUnlockRequest
        strcpy(respStr, "+ESMLRSU: 3,1,27,\"0123456789ABCDEF\"");
    } else if (strStartsWith(command.string(), "AT+ESMLRSU=3,2")) { //processMessage
        strcpy(respStr, "+ESMLRSU: 3,2,20,\"ABCD0123456789ABCDEF\"");
    } else if (strStartsWith(command.string(), "AT+ESMLRSU=3,3")) {//getLockStatus
        strcpy(respStr, "+ESMLRSU: 3,3,10,\"0100278CA2\"");
    } else if (strStartsWith(command.string(), "AT+ESMLRSU=3,5")) {//getRegisterRequest
        strcpy(respStr, "+ESMLRSU: 3,5,20,\"0F001233E200\"");
    } else if (strStartsWith(command.string(), "AT+ESMLRSU=3,6")) {//getAdapterConfig
        strcpy(respStr, "+ESMLRSU: 3,6,20,\"CCCC0123456789ABCDEF\"");
    } else if (strStartsWith(command.string(), "AT+ESMLRSU=1,1")) { //VZW:  initialize
        strcpy(respStr, "+ESMLRSU: 1,1,\"0123456789ABCDEF\"");
    } else if (strStartsWith(command.string(), "AT+ESMLRSU=1,5")) { //getSharedKey
        strcpy(respStr, "+ESMLRSU: 1,5,20,\"ABCD0123456789ABCDEF\"");
    } else if (strStartsWith(command.string(), "AT+ESMLRSU=1,2")) {//updateLockData
        strcpy(respStr, "+ESMLRSU: 1,2,\"0100278CA2\"");
    } else if (strStartsWith(command.string(), "AT+ESMLRSU=1,6")) {//getLockVersion
        strcpy(respStr, "+ESMLRSU: 1,6,\"02\",\"05\"");
    } else if (strStartsWith(command.string(), "AT+ESMLRSU=1,3")) {//getLockStatus
        strcpy(respStr, "+ESMLRSU: 1,3,\"02\",\"598860253\""); //status, left time
    } else if (strStartsWith(command.string(), "AT+ESMLRSU=1,4")) {//unlockTimer
        strcpy(respStr, "+ESMLRSU: 1,4,\"5\",\"893843329\""); //timer status, passed time
    } else if (strStartsWith(command.string(), "AT+ESMLRSU=2,9")) {//KDDI: setLockData
        strcpy(respStr, "+ESMLRSU: 2,9");
    } else if (strStartsWith(command.string(), "AT+ESMLRSU=2,7,1")) {//getAllowedLockData
        strcpy(respStr, "+ESMLRSU: 1,2,\"123456789\",\"gid1\",\"gid2\",\"5678910\",\"gid11\",\"gid21\"");
    } else if (strStartsWith(command.string(), "AT+ESMLRSU=2,7,2")) {//getExcludedLockData
        strcpy(respStr, "+ESMLRSU: 2,1,\"123456789\",\"gid21\",\"gid22\"");
    } else if (strStartsWith(command.string(), "AT+ESMLRSU=5,1")) { //TFN:  getEmei
        strcpy(respStr, "+ESMLRSU: 5,1,\"123456789ABCDEF\"");
    } else if (strStartsWith(command.string(), "AT+ESMLRSU=5,2")) { //TFN:  processLockData
        strcpy(respStr, "+ESMLRSU: 5,2,8");
    } else if (strStartsWith(command.string(), "AT+ESMLRSU=5,3")) {//getLockStatus
        strcpy(respStr, "+ESMLRSU: 5,3,1");
    } else if (strStartsWith(command.string(), "AT+ESMLRSU=5,4")) {//generateRequest
        strcpy(respStr, "+ESMLRSU: 5,4,\"00223344\"");
    } else if (strStartsWith(command.string(), "AT+ESMLRSU=5,5")) {//generateRequest
        strcpy(respStr, "+ESMLRSU: 5,5,1");
    } else if (strStartsWith(command.string(), "AT+ESMLRSU=5,6")) {//getSecretKey
        strcpy(respStr, "+ESMLRSU: 5,6,\"8899AAFF\""); //getSecretKey
    } else {
        return NULL;
    }
    atResp = (char*)malloc(strlen(respStr) + 1);
    RFX_ASSERT(atResp != NULL);
    strcpy(atResp, respStr);
    RfxAtLine *atLine = new RfxAtLine();
    atLine->setLine(atResp);
    sp<RfxAtResponse> resp = new RfxAtResponse(SINGLELINE, 1, NULL, atLine, 0, NULL);
    logE(mTag, "return fake response: %s", atLine->getLine());
    return resp;
}

