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

#include "RmmCapabilitySwitchRequestHandler.h"
#include "RmmCapabilitySwitchUtil.h"
#include <telephony/mtk_ril.h>
#include "RfxRilUtils.h"
#include "RfxRadioCapabilityData.h"
#include "RfxVoidData.h"
#include "ratconfig.h"
#include <libmtkrilutils.h>
#include "mipc_msg_tlv_const.h"


#define RFX_LOG_TAG "RmmCapa"

#define NR_TYPE_NOT_SUPPORT (0)
#define NR_TYPE_SUB6        (1)
#define NR_TYPE_MMWAVE      (2)
#define NR_TYPE_SUB6_MMWAVE (3)

// register handler to channel
RFX_IMPLEMENT_HANDLER_CLASS(RmmCapabilitySwitchRequestHandler, RIL_CMD_PROXY_9);

RFX_REGISTER_DATA_TO_EVENT_ID(RfxIntsData, RFX_MSG_EVENT_RADIO_CAPABILITY_UPDATED);

Mutex RmmCapabilitySwitchRequestHandler::s_sim_init_state_mutex;
int RmmCapabilitySwitchRequestHandler::s_sim_init_state;

Mutex RmmCapabilitySwitchRequestHandler::s_first_instance_mutex;
bool RmmCapabilitySwitchRequestHandler::s_first_instance = true;

RmmCapabilitySwitchRequestHandler::RmmCapabilitySwitchRequestHandler(int slot_id, int channel_id) :
        RfxBaseHandler(slot_id, channel_id) {
    logD(RFX_LOG_TAG, "constructor entered");
    // setSIMInitState(0);
    const int request1[] = {
        RFX_MSG_REQUEST_SET_RADIO_CAPABILITY,
        RFX_MSG_REQUEST_GET_RADIO_CAPABILITY,
        RFX_MSG_REQUEST_CAPABILITY_SWITCH_SET_MAJOR_SIM
    };
    registerToHandleRequest(request1, sizeof(request1) / sizeof(int));

    s_first_instance_mutex.lock();
    if (s_first_instance) {
        int main_sim = queryMainProtocol();
        s_first_instance = false;
        rfx_property_set(
                "persist.vendor.radio.simswitch", String8::format("%d", main_sim).string());
        getNonSlotMclStatusManager()->setIntValue(
                RFX_STATUS_KEY_MAIN_CAPABILITY_SLOT, main_sim - 1, false, false);
        queryNoResetSupport();
        queryTplusWSupport();
        queryKeep3GMode();
        if(false == RfxRilUtils::isTplusWSupport()) {
            queryActiveMode();
        }
        queryNrType();
    }
    s_first_instance_mutex.unlock();
    queryBearer();
    sendRadioCapabilityDoneIfNeeded();
    sendEGRAT();
    sendEvent(RFX_MSG_EVENT_CAPABILITY_INIT_DONE, RfxVoidData(), m_channel_id, m_slot_id);
}

RmmCapabilitySwitchRequestHandler::~RmmCapabilitySwitchRequestHandler() {
}

void RmmCapabilitySwitchRequestHandler::onHandleRequest(const sp<RfxMclMessage> &msg) {
    //logD(RFX_LOG_TAG, "onHandleRequest: %s", idToString(msg->getId()));
    int request = msg->getId();
    switch (request) {
        case RFX_MSG_REQUEST_SET_RADIO_CAPABILITY:
            logE(RFX_LOG_TAG, "Should not receive RFX_MSG_REQUEST_SET_RADIO_CAPABILITY");
            break;
        case RFX_MSG_REQUEST_CAPABILITY_SWITCH_SET_MAJOR_SIM:
            requestSetRadioCapability(msg);
            break;
        case RFX_MSG_REQUEST_GET_RADIO_CAPABILITY:
            requestGetRadioCapability(msg);
            break;
        default:
            logE(RFX_LOG_TAG, "Should not be here");
            break;
    }
}

void RmmCapabilitySwitchRequestHandler::requestSetRadioCapability(const sp<RfxMclMessage> &msg) {
    /*
    sp<RfxMclMessage> resMsg;
    int *new_major_slot = (int *)msg->getData()->getData();
    int old_major_slot = getNonSlotMclStatusManager()->getIntValue(
            RFX_STATUS_KEY_MAIN_CAPABILITY_SLOT, 0);
    sp<RfxAtResponse> p_response = NULL;
    int real_channel_id = m_channel_id + RIL_PROXY_OFFSET * m_slot_id;
    bool no_reset_support = RmmCapabilitySwitchUtil::isDssNoResetSupport();
    int response_data[1];
    response_data[0] = new_major_slot[0];
    int channels_num = RfxChannelManager::getSupportChannels();

    logI(RFX_LOG_TAG, "RadioCapability old_major_slot=%d, new_major_slot=%d",
         old_major_slot, new_major_slot[0]);
    if (no_reset_support || (!isVsimEnabled() && !isPersistVsim())) {
        int sim_count = RfxRilUtils::rfxGetSimCount();
        if (!no_reset_support) {
            // DSS_NO_RESET will power off radio in RTM, not here
            for (int i = 0; i < sim_count; i++) {
                getMclStatusManager(i)->setIntValue(RFX_STATUS_KEY_RADIO_POWER_MSIM_MODE, 0);
            }
            p_response = atSendCommand(String8::format("AT+EFUN=0,%d", RFOFF_CAUSE_SIM_SWITCH));
            if (p_response != NULL && p_response->getSuccess() == 0) {
                resMsg = RfxMclMessage::obtainResponse(
                        msg->getId(), RIL_E_GENERIC_FAILURE,
                        RfxIntsData(response_data, 1), msg, true);
                responseToTelCore(resMsg);
                return;
            }
            p_response = atSendCommand("AT+EBOOT=1");
        }
        if (RfxRilUtils::getRilRunMode() != RIL_RUN_MODE_MOCK) {
            // lock sms channel (RIL_CMD_8) before other channels
            // due to sms channel may pending for long time
            for(int i = RIL_CMD_8; i < channels_num; i+=RIL_CHANNEL_OFFSET) {
                logD(RFX_LOG_TAG, "lock mutex %d!", i);
                lockRestartMutex(i);
            }

            for(int i = 0; i < channels_num; i++) {
                if (i == real_channel_id || i % RIL_CHANNEL_OFFSET == RIL_CMD_IMS ||
                        i % RIL_CHANNEL_OFFSET == RIL_URC ||
                        (no_reset_support && i % RIL_CHANNEL_OFFSET == RIL_CMD_11) ||
                        i % RIL_CHANNEL_OFFSET == RIL_CMD_8 ) {
                    continue;
                }
                if (i == 1) {
                    logI(RFX_LOG_TAG, "lock mutex %d!", i);
                } else {
                    logD(RFX_LOG_TAG, "lock mutex %d!", i);
                }
                lockRestartMutex(i);
            }
            if (no_reset_support == false) {
                for(int i = RIL_URC; i < channels_num; i += RIL_CHANNEL_OFFSET) {
                    lockRestartMutex(i);
                }
                logI(RFX_LOG_TAG, "lock mutex done!");
                // switchChannel(RIL_URC, old_major_slot, new_major_slot[0]);
            } else {
                logI(RFX_LOG_TAG, "lock mutex done!");
                getNonSlotMclStatusManager()->setBoolValue(
                        RFX_STATUS_KEY_CAPABILITY_SWITCH_URC_CHANNEL, true, false, false);
            }
        }
        String8 command;
        // re-init sim state before send ESIMMAP
        setSIMInitState(0);
        if (sim_count < 3) {
            command = String8::format("AT+ESIMMAP=%d", (1 << new_major_slot[0]));
        } else {
            command = String8::format("AT+EPSMAP=%d,%d", sim_count, new_major_slot[0] + 1);
            for (int i = 0; i < sim_count; i++) {
                if (i != new_major_slot[0]) {
                    command.appendFormat(",%d", i + 1);
                }
            }
        }
        p_response = atSendCommand(command);
        while (p_response != NULL && p_response->getSuccess() == 0) {
            logE(RFX_LOG_TAG, "at cmd returns ERROR:%d, retry", p_response->getError());
            usleep(200*1000);
            p_response = atSendCommand(command);
        }

        // wait for URC channel switch done
        while (getNonSlotMclStatusManager()->getBoolValue(
                RFX_STATUS_KEY_CAPABILITY_SWITCH_URC_CHANNEL, false)) {
            usleep(100*1000);
        }

        if (RfxRilUtils::getRilRunMode() != RIL_RUN_MODE_MOCK) {
            queryActiveMode();
            setSimSwitchProp(old_major_slot, new_major_slot[0]);
            if (no_reset_support) {
                if (false == waitSIMInitDone()) {
                    return;
                }
            }
            for(int i = 0; i < RIL_CHANNEL_OFFSET; i++) {
                if (i == RIL_CMD_IMS || i == RIL_URC || (no_reset_support && i == RIL_CMD_11)) {
                    continue;
                }
                // switchChannel(i, old_major_slot, new_major_slot[0]);
            }
            logD(RFX_LOG_TAG, "switchChannel done! old:%d,new:%d",
                 old_major_slot, new_major_slot[0]);
            for(int i = 0; i < channels_num; i++) {
                if (i % RIL_CHANNEL_OFFSET == RIL_CMD_IMS ||
                    i % RIL_CHANNEL_OFFSET == RIL_URC ||
                    i == real_channel_id ||
                    (no_reset_support && i % RIL_CHANNEL_OFFSET == RIL_CMD_11)) {
                    continue;
                }
                unlockRestartMutex(i);
            }
            if (no_reset_support == false) {
                // unlock URC channels later than sender channels
                for(int i = RIL_URC; i < channels_num; i+=RIL_CHANNEL_OFFSET) {
                    unlockRestartMutex(i);
                }
            }
            //logD(RFX_LOG_TAG, "unlock mutex done!");
        } else {
            setSimSwitchProp(old_major_slot, new_major_slot[0]);
        }
        resMsg = RfxMclMessage::obtainResponse(
                msg->getId(), RIL_E_SUCCESS, RfxIntsData(response_data, 1), msg, true);
        responseToTelCore(resMsg);

        for(int i = 0; i < sim_count; i++) {
            int event_data[1];
            event_data[0] = getMclStatusManager(i)->getIntValue(RFX_STATUS_KEY_SLOT_CAPABILITY, 0);
            sendEvent(RFX_MSG_EVENT_RADIO_CAPABILITY_UPDATED, RfxIntsData(event_data, 1),
                      RIL_CMD_PROXY_9, i);
        }
    } else {
        atSendCommand(String8::format("AT+ES3G = %d,%d", (1 << new_major_slot[0]), 3));
        setSimSwitchProp(old_major_slot, new_major_slot[0]);
        rfx_property_set("vendor.gsm.ril.eboot", "1");
        resetRadio();
    }
    */

    sp<RfxMclMessage> resMsg;
    int *new_major_slot = (int *)msg->getData()->getData();
    int old_major_slot = getNonSlotMclStatusManager()->getIntValue(
            RFX_STATUS_KEY_MAIN_CAPABILITY_SLOT, 0);
    uint32_t ps_list[4];
    int response_data[1];
    sp<RfxMipcData> mipcRet = NULL;
    mipc_result_const_enum ret = mipc_result_const_NONE;

    logI(RFX_LOG_TAG, "RadioCapability old_major_slot=%d, new_major_slot=%d",
         old_major_slot, new_major_slot[0]);

    sp<RfxMipcData> mipcMsg = RfxMipcData::obtainMipcData(MIPC_SYS_SET_MAPPING_REQ, old_major_slot);
    mipcMsg->addMipcTlvUint8(
            MIPC_SYS_SET_MAPPING_REQ_T_MAPPING_COUNT, RfxRilUtils::rfxGetSimCount());
    if (new_major_slot[0] == 0) {
        // PS1 on SIM1
        ps_list[0] = 0;
        ps_list[1] = 1;
        ps_list[2] = 2;
        ps_list[3] = 3;
    } else if (new_major_slot[0] == 1) {
        // PS1 on SIM2
        ps_list[0] = 1;
        ps_list[1] = 0;
        ps_list[2] = 2;
        ps_list[3] = 3;
    }  else if (new_major_slot[0] == 2) {
        // PS1 on SIM3
        ps_list[0] = 1;
        ps_list[1] = 2;
        ps_list[2] = 0;
        ps_list[3] = 3;
    }   else if (new_major_slot[0] == 3) {
        // PS1 on SIM3
        ps_list[0] = 1;
        ps_list[1] = 2;
        ps_list[2] = 3;
        ps_list[3] = 0;
    }

    mipcMsg->addMipcTlv(
            MIPC_SYS_SET_MAPPING_REQ_T_MAPPING_LIST,
            RfxRilUtils::rfxGetSimCount() * sizeof(uint32_t),
            ps_list);

    mipcRet = callToMipcMsgSync(mipcMsg);
    ret = (mipc_result_const_enum) mipcRet->getResult();

    logD(RFX_LOG_TAG, "sendMipcRequest: ret=%d", ret);

    setSimSwitchProp(old_major_slot, new_major_slot[0]);
    response_data[0] = new_major_slot[0];
    resMsg = RfxMclMessage::obtainResponse(
            msg->getId(), RIL_E_SUCCESS, RfxIntsData(response_data, 1), msg, true);
    responseToTelCore(resMsg);

}

/*
void RmmCapabilitySwitchRequestHandler::resetRadio() {
    logD(RFX_LOG_TAG, "start to reset radio");
    atSendCommand("AT+EFUN=0");
    atSendCommand("AT+ECUSD=2,2");
    atSendCommand("AT+EMDT=0");
    atSendCommand("AT+EPOF");
    RfxRilUtils::triggerCCCIIoctl(CCCI_IOC_ENTER_DEEP_FLIGHT_ENHANCED);
    //power on modem
    RfxRilUtils::triggerCCCIIoctl(CCCI_IOC_LEAVE_DEEP_FLIGHT_ENHANCED);

}

bool RmmCapabilitySwitchRequestHandler::isVsimEnabledByRid(int rid) {
    bool enabled = false;
    char vsim_enabled_prop[RFX_PROPERTY_VALUE_MAX] = {0};
    char vsim_inserted_prop[RFX_PROPERTY_VALUE_MAX] = {0};

    getMSimProperty(rid, (char*)"vendor.gsm.external.sim.enabled", vsim_enabled_prop);
    getMSimProperty(rid, (char*)"vendor.gsm.external.sim.inserted", vsim_inserted_prop);

    if (atoi(vsim_enabled_prop) > 0 && atoi(vsim_inserted_prop) > 0) {
        enabled = true;
    }

    logD(RFX_LOG_TAG, "isVsimEnabled rid:%d is %d.", rid, enabled);

    return enabled;
}
bool RmmCapabilitySwitchRequestHandler::isVsimEnabled() {
    bool enabled = false;

    for (int index = 0; index < RfxRilUtils::rfxGetSimCount(); index++) {
        if (1 == isVsimEnabledByRid(index)) {
            enabled = true;
            break;
        }
    }
    logD(RFX_LOG_TAG, "isVsimEnabled=%d", enabled);
    return false;
}

bool RmmCapabilitySwitchRequestHandler::isPersistVsim() {
    bool persist = false;
    char persist_vsim_inserted_prop[RFX_PROPERTY_VALUE_MAX] = {0};

    for (int index = 0; index < RfxRilUtils::rfxGetSimCount(); index++) {
        getMSimProperty(
                index, (char*)"persist.vendor.radio.external.sim", persist_vsim_inserted_prop);
        if (atoi(persist_vsim_inserted_prop) > 0) {
            persist = true;
            break;
        }
    }
    logD(RFX_LOG_TAG, "isPersistVsim=%d", persist);
    return persist;
}
*/

void RmmCapabilitySwitchRequestHandler::queryTplusWSupport() {
    /*
    sp<RfxAtResponse> p_response = NULL;
    int TplusWsupport = 0;
    RfxAtLine *line;
    int err;

    p_response = atSendCommandSingleline("AT+ESBP=7,\"SBP_T_PLUS_W\"", "+ESBP:");
    do {
        if (p_response == NULL || p_response->getSuccess() == 0) {
            logE(RFX_LOG_TAG, "queryTplusWSupport AT+ESBP return ERROR");
            break;
        }
        line = p_response->getIntermediates();
        line->atTokStart(&err);
        if (err < 0) {
            logE(RFX_LOG_TAG, "queryTplusWSupport AT+ESBP atTokStart error:%d", err);
            break;
        }
        TplusWsupport = line->atTokNextint(&err);
        if (err < 0) {
            logE(RFX_LOG_TAG, "queryTplusWSupport AT+ESBP atTokNextint error:%d", err);
            break;
        }
    } while(0);
    logD(RFX_LOG_TAG, "queryTplusWSupport, TplusWSupport=%d", TplusWsupport);
        */
    logD(RFX_LOG_TAG, "queryTplusWSupport, Gen98 don't support TDS");
    rfx_property_set("vendor.ril.simswitch.tpluswsupport", "1");
}

void RmmCapabilitySwitchRequestHandler::queryKeep3GMode() {
    /*
    sp<RfxAtResponse> p_response = NULL;
    int keep_3g_mode = 0;
    RfxAtLine *line;
    int err;

    p_response = atSendCommandSingleline("AT+ESBP=7,\"SBP_GEMINI_LG_WG_MODE\"", "+ESBP:");
    do {
        if (p_response == NULL || p_response->getSuccess() == 0) {
            logE(RFX_LOG_TAG, "queryKeep3GMode AT+ESBP return ERROR");
            break;
        }
        line = p_response->getIntermediates();
        line->atTokStart(&err);
        if (err < 0) {
            logE(RFX_LOG_TAG, "queryKeep3GMode AT+ESBP atTokStart error:%d", err);
            break;
        }
        keep_3g_mode = line->atTokNextint(&err);
        if (err < 0) {
            logE(RFX_LOG_TAG, "queryKeep3GMode AT+ESBP atTokNextint error:%d", err);
            break;
        }
    } while(0);
    logD(RFX_LOG_TAG, "queryKeep3GMode, keep_3g_mode=%d", keep_3g_mode);
    */
    logD(RFX_LOG_TAG, "queryKeep3GMode, Gen98 don't support TDS");
    //keep_3g_mode, 0:keep TD-SCDMA, 1:keep WCDMA
    rfx_property_set("vendor.ril.nw.worldmode.keep_3g_mode", "1");
}

void RmmCapabilitySwitchRequestHandler::queryNrType() {
    // Modem don't support mmWave before Gen98, only support SUB6m_slot_id
    sp<RfxMipcData> mipcReq, mipcRsp;
    void* p = NULL;
    uint16_t len =0;
    mipc_sys_nr_band_struct4* pNrBand = NULL;

    if (RatConfig_isNrSupported() == 0) {
        rfx_property_set("vendor.ril.nr.type",
                    String8::format("%d", NR_TYPE_NOT_SUPPORT).string());
        return;
    }

    mipcReq = RfxMipcData::obtainMipcData(MIPC_NW_GET_BAND_MODE_REQ, m_slot_id);
    mipcReq->addMipcTlvUint8(MIPC_NW_GET_BAND_MODE_REQ_T_OPTION,
            MIPC_NW_BAND_OPTION_SYSTEM_SUPPORT);
    mipcRsp = callToMipcMsgSync(mipcReq);
    if (mipcRsp != NULL) {
        // nr band
        p = mipcRsp->getMipcVal(MIPC_NW_GET_BAND_MODE_CNF_T_NR_BAND, &len);
    }

    // default nr type is sub6
    if ((mipcRsp->getResult() != MIPC_RESULT_SUCCESS) || (p == NULL)) {
        rfx_property_set("vendor.ril.nr.type",
                String8::format("%d", NR_TYPE_SUB6).string());
        return;
    }

    pNrBand = (mipc_sys_nr_band_struct4 *) p;
    // bit 256 ~ 262 is for mmWave
    if (pNrBand->nr_band_class[8] & 126 != 0) {
        rfx_property_set("vendor.ril.nr.type",
                String8::format("%d", NR_TYPE_SUB6_MMWAVE).string());
    } else {
        rfx_property_set("vendor.ril.nr.type",
                String8::format("%d", NR_TYPE_SUB6).string());
    }
}

void RmmCapabilitySwitchRequestHandler::queryNoResetSupport() {
    /*
    char feature[] = "DSS_NO_RESET";
    int support = getFeatureVersion(feature);
    //no reset support, 0:disable, 1:enable
    logD(RFX_LOG_TAG, "queryNoResetSupport, %s=%d",feature, support);
    if (support == 1) {
        rfx_property_set("vendor.ril.simswitch.no_reset_support",
                String8::format("%d", support).string());
    } else {
        rfx_property_set("vendor.ril.simswitch.no_reset_support",
                String8::format("%d", 0).string());
    }
    */
    logD(RFX_LOG_TAG, "queryNoResetSupport, Gen98 always support");
    rfx_property_set("vendor.ril.simswitch.no_reset_support", "1");
}

void RmmCapabilitySwitchRequestHandler::queryActiveMode() {
    /*
    sp<RfxAtResponse> p_response = NULL;
    int csraaResponse[3] = {0};
    RfxAtLine *line;
    int err;

    p_response = atSendCommandMultiline("AT+CSRA?", "+CSRAA:");

    do {
        if (p_response == NULL || p_response->getSuccess() == 0) {
            logE(RFX_LOG_TAG, "AT+CSRAA return ERROR");
            break;
        }
        line = p_response->getIntermediates();
        line->atTokStart(&err);
        if (err < 0) {
            break;
        }
        csraaResponse[0] = line->atTokNextint(&err);
        if (err < 0) {
            break;
        }
        csraaResponse[1] = line->atTokNextint(&err);
        if (err < 0) {
            break;
        }
        //logD(RFX_LOG_TAG, "+CSRAA:<UTRANFDD> = %d", csraaResponse[1]);
        csraaResponse[2] = line->atTokNextint(&err);
        if (err < 0) {
            break;
        }
        //logD(RFX_LOG_TAG, "+CSRAA:<UTRAN-TDD-LCR> = %d", csraaResponse[2]);
        if ((csraaResponse[1] == 1) && (csraaResponse[2] == 0)) {
            //FDD mode
            rfx_property_set("vendor.ril.nw.worldmode.activemode",
                    String8::format("%d", 1).string());
        }
        else if ((csraaResponse[1] == 0) && (csraaResponse[2] == 1)) {
            //TDD mode
            rfx_property_set("vendor.ril.nw.worldmode.activemode",
                    String8::format("%d", 2).string());
        }
    } while (0);
    */
    // Gen 98 is always on FDD mode
    rfx_property_set("vendor.ril.nw.worldmode.activemode", "1");
}

int RmmCapabilitySwitchRequestHandler::getActiveMode() {
    char world_mode_prop[RFX_PROPERTY_VALUE_MAX] = {0};
    int world_mode = 0;

    rfx_property_get("vendor.ril.nw.worldmode.activemode", world_mode_prop, "1");
    world_mode = atoi(world_mode_prop);
    return world_mode;
}

int RmmCapabilitySwitchRequestHandler::queryMainProtocol() {
    int main_sim = RfxRilUtils::getMajorSim();
    sp<RfxMipcData> mipcRet = NULL;
    mipc_result_const_enum ret = mipc_result_const_NONE;
    int count = 0;
    uint32_t *ps_list;
    uint16_t length = 0;

    sp<RfxMipcData> mipcMsg = RfxMipcData::obtainMipcData(MIPC_SYS_GET_MAPPING_REQ, main_sim - 1);
    mipcRet = callToMipcMsgSync(mipcMsg);

    ret = (mipc_result_const_enum) mipcRet->getResult();
    if (ret != MIPC_RESULT_SUCCESS) {
        logI(RFX_LOG_TAG, "queryMainProtocol failed, return %d", main_sim);
        return main_sim;
    }

    count = mipcRet->getMipcUint8Val(MIPC_SYS_GET_MAPPING_CNF_T_MAPPING_COUNT, 0);
    ps_list = (uint32_t*)mipcRet->getMipcVal(MIPC_SYS_GET_MAPPING_CNF_T_MAPPING_LIST, &length);
    logI(RFX_LOG_TAG, "queryMainProtocol, main_sim:%d, count:%d, len:%d",
            main_sim, count, length);

    if (length >= RfxRilUtils::rfxGetSimCount()) {
        for (int i = 0; i < RfxRilUtils::rfxGetSimCount(); i++) {
            if (ps_list[i] == 0) {
                return (i + 1);
            }
        }
    }
    return main_sim;
}

void RmmCapabilitySwitchRequestHandler::queryBearer() {
    sp<RfxAtResponse> p_response = NULL;
    int err;
    RfxAtLine *line;
    int ret = 0;
    int ap_max_rat = RAF_GPRS;
    int radio_capability;
    int main_slot = RmmCapabilitySwitchUtil::getMajorSim() - 1;
    char tempstr[RFX_PROPERTY_VALUE_MAX] = { 0 };

    logD(RFX_LOG_TAG, "queryBearer");

    if (main_slot == m_slot_id) {
        rfx_property_get(rat_properties[0], tempstr, "G");
    } else if (main_slot > m_slot_id) {
        rfx_property_get(rat_properties[m_slot_id + 1], tempstr, "G");
    } else {
        rfx_property_get(rat_properties[m_slot_id], tempstr, "G");
    }

    // query project config capability
    if (strchr(tempstr, 'G') != NULL && RatConfig_isGsmSupported()) {
        ap_max_rat |= RAF_GSM;
    }
    if (strchr(tempstr, 'W') != NULL && RatConfig_isWcdmaSupported()) {
        ap_max_rat |= RAF_UMTS;
    }
    if (strchr(tempstr, 'T') != NULL && RatConfig_isTdscdmaSupported()) {
        ap_max_rat |= RAF_TD_SCDMA;
    }
    if (strchr(tempstr, 'L') != NULL &&
        (RatConfig_isLteFddSupported() || RatConfig_isLteTddSupported())) {
        ap_max_rat |= RAF_LTE;
    }
    if (strchr(tempstr, 'N') != NULL && RatConfig_isNrSupported()) {
        ap_max_rat |= RAF_NR;
    }

    int major_slot = RfxRilUtils::getMajorSim() - 1;
    if (major_slot == m_slot_id) {
        // use RAF_GPRS as the main protocol flag
        // for 3 SIMs project, if the rat value is same for two protocols
        // AOSP logic cannot find out the main protocol
        ap_max_rat |= RAF_GPRS;
    } else {
        ap_max_rat &= (~RAF_GPRS);
    }
    radio_capability = ap_max_rat;
    getMclStatusManager(m_slot_id)->setIntValue(
            RFX_STATUS_KEY_SLOT_FIXED_CAPABILITY, radio_capability, false, false);

    if (major_slot != m_slot_id && getActiveMode() == 2 &&
        RfxRilUtils::isTplusWSupport() == false &&
        RfxRilUtils::getKeep3GMode() == 0) {
        // Remove 3G raf for non major SIMs in TDD mode
        radio_capability &= ~RAF_UMTS;
    }
    if(RmmCapabilitySwitchUtil::isDisableC2kCapability() == false &&
            RatConfig_isC2kSupported()) {
        memset(tempstr, 0, sizeof(tempstr));
        rfx_property_get("persist.vendor.radio.c_capability_slot", tempstr, "1");
        int cslot = atoi(tempstr) - 1;
        logI(RFX_LOG_TAG, "queryBearer, cslot=%d", cslot);
        if (cslot == m_slot_id || (cslot < 0 && m_slot_id == 0)) {
            radio_capability |= (RAF_CDMA_GROUP | RAF_EVDO_GROUP);
        }
    }
    logD(RFX_LOG_TAG, "radio_capability=%d", radio_capability);
    getMclStatusManager(m_slot_id)->setIntValue(
            RFX_STATUS_KEY_SLOT_CAPABILITY, radio_capability, false, false);
}

void RmmCapabilitySwitchRequestHandler::sendRadioCapabilityDoneIfNeeded() {
    int radio_capability = getMclStatusManager(m_slot_id)->getIntValue(
            RFX_STATUS_KEY_SLOT_CAPABILITY, 0);
    int event_data[1];

    if(RmmCapabilitySwitchUtil::isDisableC2kCapability() == false &&
            RatConfig_isC2kSupported()) {
        // always send CDMA capability from Android Q
        radio_capability |= (RAF_CDMA_GROUP | RAF_EVDO_GROUP);
    }

    event_data[0] = radio_capability;
    sendEvent(RFX_MSG_EVENT_RADIO_CAPABILITY_UPDATED, RfxIntsData(event_data, 1),
              m_channel_id, m_slot_id);
}

void RmmCapabilitySwitchRequestHandler::requestGetRadioCapability(const sp<RfxMclMessage> &msg) {
    int radio_capability;
    int session_id = -1;
    RIL_RadioCapability rc;
    memset(&rc, 0, sizeof(RIL_RadioCapability));
    rc.version = RIL_RADIO_CAPABILITY_VERSION;
    rc.session = session_id;
    rc.phase = RC_PHASE_UNSOL_RSP;
    rc.status = RC_STATUS_SUCCESS;
    radio_capability = getMclStatusManager(m_slot_id)->getIntValue(
            RFX_STATUS_KEY_SLOT_CAPABILITY, 0);
    if(RmmCapabilitySwitchUtil::isDisableC2kCapability() == false &&
            RatConfig_isC2kSupported()) {
        // always send CDMA capability from Android Q
        radio_capability |= (RAF_CDMA_GROUP | RAF_EVDO_GROUP);
    }

    logD(RFX_LOG_TAG, "requestGetRadioCapability, cap[%d] = %d, sizeof(RIL_RadioCapability)=%d",
         m_slot_id, radio_capability, (int)sizeof(RIL_RadioCapability));
    rc.rat = radio_capability;
    RfxRilUtils::getLogicalModemId(rc.logicalModemUuid, MAX_UUID_LENGTH, m_slot_id);
    sp<RfxMclMessage> response = RfxMclMessage::obtainResponse(
            RIL_E_SUCCESS, RfxRadioCapabilityData(&rc, sizeof(RIL_RadioCapability)), msg);
    responseToTelCore(response);
}

void RmmCapabilitySwitchRequestHandler::setSimSwitchProp(int old_major_slot, int new_major_slot) {
    switchCapability(old_major_slot, new_major_slot);
    rfx_property_set("persist.vendor.radio.simswitch",
                     String8::format("%d", new_major_slot + 1).string());
    getNonSlotMclStatusManager()->setIntValue(
            RFX_STATUS_KEY_MAIN_CAPABILITY_SLOT, new_major_slot, false, false);
}

/*
void RmmCapabilitySwitchRequestHandler::lockRestartMutex(int channel_id) {
    RfxChannel *p_channel;
    RfxChannelContext *p_channel_context;

    p_channel = RfxChannelManager::getChannel(channel_id);
    p_channel_context = p_channel->getContext();
    p_channel_context->setNeedWaitRestartCondition(true);
    p_channel_context->m_restartMutex.lock();
    p_channel_context->m_readerMutex.lock();
}

void RmmCapabilitySwitchRequestHandler::unlockRestartMutex(int channel_id) {
    RfxChannel *p_channel;
    RfxChannelContext *p_channel_context;

    p_channel = RfxChannelManager::getChannel(channel_id);
    p_channel_context = p_channel->getContext();
    p_channel_context->setNeedWaitRestartCondition(false);
    p_channel_context->m_readerMutex.unlock();
    p_channel_context->m_restartCondition.signal();
    p_channel_context->m_restartMutex.unlock();
}


void RmmCapabilitySwitchRequestHandler::switchChannelByRealId(int channel_id1, int channel_id2) {
    RfxChannel *channel1, *channel2;
    RfxReader *reader1, *reader2;
    RfxSender *sender1, *sender2;
    RfxChannelContext *tmp_context;
    int tmp_fd;
    if (channel_id1 == channel_id2) {
        return;
    }
    //RFX_LOG_D(RFX_LOG_TAG, "switchChannel:%d <-> %d", channel_id1, channel_id2);
    channel1 = RfxChannelManager::getChannel(channel_id1);
    channel2 = RfxChannelManager::getChannel(channel_id2);
    reader1 = channel1->getReader();
    reader2 = channel2->getReader();
    sender1 = channel1->getSender();
    sender2 = channel2->getSender();

    tmp_context = reader1->getChannelContext();
    reader1->setChannelContext(reader2->getChannelContext());
    reader2->setChannelContext(tmp_context);

    reader1->setChannelId(channel_id2);
    reader2->setChannelId(channel_id1);

    channel1->setReader(reader2);
    channel2->setReader(reader1);
    tmp_fd = sender1->getFd();
    sender1->setFd(sender2->getFd());
    sender2->setFd(tmp_fd);
}


void RmmCapabilitySwitchRequestHandler::switchChannel(int channel, int old_major_slot,
                                                      int new_major_slot) {
    if (old_major_slot == new_major_slot) {
        return;
    }
    if (RfxRilUtils::rfxGetSimCount() < 3) {
        //Switch main protocol channel from old main slot to slot 0
        switchChannelByRealId(channel, channel + old_major_slot * RIL_CHANNEL_OFFSET);
        //Switch main protocol channel from 0 to new main slot id
        switchChannelByRealId(channel, channel + new_major_slot * RIL_CHANNEL_OFFSET);
    } else {
        int step = (new_major_slot > old_major_slot) ? 1 : -1;
        for (int i = old_major_slot; i != new_major_slot; i += step) {
            switchChannelByRealId(
                    channel + i * RIL_CHANNEL_OFFSET, channel + (i + step) * RIL_CHANNEL_OFFSET);
        }
    }
}
*/


//shift capability for the new EPSMAP mapping logic
void RmmCapabilitySwitchRequestHandler::shiftCapability(int old_major_slot, int new_major_slot) {
    if (old_major_slot == new_major_slot) {
        RFX_LOG_D(RFX_LOG_TAG, "shiftCapability:old=new=%d", old_major_slot);
        return;
    }
    int step = (new_major_slot > old_major_slot) ? 1 : -1;
    for (int i = old_major_slot; i != new_major_slot; i += step) {
        switchFixedCapability(i, i + step);
        setCapabilityByConfig(i, false);
    }
    setCapabilityByConfig(new_major_slot, true);
}

void RmmCapabilitySwitchRequestHandler::switchFixedCapability(int slot_a, int slot_b) {
    int tmp_capability = getMclStatusManager(slot_a)->getIntValue(
            RFX_STATUS_KEY_SLOT_FIXED_CAPABILITY, 0);
    getMclStatusManager(slot_a)->setIntValue(
            RFX_STATUS_KEY_SLOT_FIXED_CAPABILITY, getMclStatusManager(slot_b)->getIntValue(
                    RFX_STATUS_KEY_SLOT_FIXED_CAPABILITY, 0), false, false);
    getMclStatusManager(slot_b)->setIntValue(
            RFX_STATUS_KEY_SLOT_FIXED_CAPABILITY, tmp_capability, false, false);
}

void RmmCapabilitySwitchRequestHandler::setCapabilityByConfig(int slot, bool is_major_slot) {
    int cslot = -1;
    char tempstr[RFX_PROPERTY_VALUE_MAX] = { 0 };
    if (RmmCapabilitySwitchUtil::isDisableC2kCapability() == false && RatConfig_isC2kSupported()) {
        memset(tempstr, 0, sizeof(tempstr));
        rfx_property_get("persist.vendor.radio.c_capability_slot", tempstr, "1");
        cslot = atoi(tempstr) - 1;
    }
    int tmp_capability = getMclStatusManager(slot)->getIntValue(
        RFX_STATUS_KEY_SLOT_FIXED_CAPABILITY, 0);
    if (!is_major_slot && getActiveMode() == 2 && RfxRilUtils::isTplusWSupport() == false &&
        RfxRilUtils::getKeep3GMode() == 0) {
        // Remove 3G raf for non major SIMs in TDD mode
        tmp_capability &= ~RAF_UMTS;
    }
    if (cslot == slot) {
        tmp_capability |= (RAF_CDMA_GROUP | RAF_EVDO_GROUP);
    }
    logD(RFX_LOG_TAG, "setCapabilityByConfig, cslot=%d,capa=%d", cslot, tmp_capability);
    getMclStatusManager(slot)->setIntValue(
            RFX_STATUS_KEY_SLOT_CAPABILITY, tmp_capability, false, false);
}

void RmmCapabilitySwitchRequestHandler::switchCapability(int old_major_slot, int new_major_slot) {
    int tmp_capability;
    int cslot = -1;
    char tempstr[RFX_PROPERTY_VALUE_MAX] = { 0 };

    if (RfxRilUtils::rfxGetSimCount() > 2) {
        return shiftCapability(old_major_slot, new_major_slot);
    }
    if (old_major_slot != 0) {
        tmp_capability = getMclStatusManager(old_major_slot)->getIntValue(
                RFX_STATUS_KEY_SLOT_FIXED_CAPABILITY, 0);
        getMclStatusManager(old_major_slot)->setIntValue(
                RFX_STATUS_KEY_SLOT_FIXED_CAPABILITY, getMclStatusManager(0)->getIntValue(
                        RFX_STATUS_KEY_SLOT_FIXED_CAPABILITY, 0), false, false);
        getMclStatusManager(0)->setIntValue(
                RFX_STATUS_KEY_SLOT_FIXED_CAPABILITY, tmp_capability, false, false);
    }
    if (new_major_slot != 0) {
        tmp_capability = getMclStatusManager(new_major_slot)->getIntValue(
                RFX_STATUS_KEY_SLOT_FIXED_CAPABILITY, 0);
        getMclStatusManager(new_major_slot)->setIntValue(
                RFX_STATUS_KEY_SLOT_FIXED_CAPABILITY, getMclStatusManager(0)->getIntValue(
                        RFX_STATUS_KEY_SLOT_FIXED_CAPABILITY, 0), false, false);
        getMclStatusManager(0)->setIntValue(
                RFX_STATUS_KEY_SLOT_FIXED_CAPABILITY, tmp_capability, false, false);
    }
    if (RmmCapabilitySwitchUtil::isDisableC2kCapability() == false && RatConfig_isC2kSupported()) {
        memset(tempstr, 0, sizeof(tempstr));
        rfx_property_get("persist.vendor.radio.c_capability_slot", tempstr, "1");
        cslot = atoi(tempstr) - 1;
        logI(RFX_LOG_TAG, "switchCapability, cslot=%d", cslot);
    }
    if (old_major_slot != 0 && new_major_slot != 0) {
        tmp_capability = getMclStatusManager(0)->getIntValue(
                RFX_STATUS_KEY_SLOT_FIXED_CAPABILITY, 0);
        if (getActiveMode() == 2 && RfxRilUtils::isTplusWSupport() == false &&
            RfxRilUtils::getKeep3GMode() == 0) {
            // Remove 3G raf for non major SIMs in TDD mode
            tmp_capability &= ~RAF_UMTS;
        }
        if (cslot == 0) {
            tmp_capability |= (RAF_CDMA_GROUP | RAF_EVDO_GROUP);
        }
        getMclStatusManager(0)->setIntValue(
                RFX_STATUS_KEY_SLOT_CAPABILITY, tmp_capability, false, false);
    }

    tmp_capability = getMclStatusManager(old_major_slot)->getIntValue(
            RFX_STATUS_KEY_SLOT_FIXED_CAPABILITY, 0);
    if (getActiveMode() == 2 && RfxRilUtils::isTplusWSupport() == false &&
        RfxRilUtils::getKeep3GMode() == 0) {
        // Remove 3G raf for non major SIMs in TDD mode
        tmp_capability &= ~RAF_UMTS;
    }
    if (cslot == old_major_slot) {
        tmp_capability |= (RAF_CDMA_GROUP | RAF_EVDO_GROUP);
    }
    getMclStatusManager(old_major_slot)->setIntValue(
            RFX_STATUS_KEY_SLOT_CAPABILITY, tmp_capability, false, false);

    tmp_capability = getMclStatusManager(new_major_slot)->getIntValue(
            RFX_STATUS_KEY_SLOT_FIXED_CAPABILITY, 0);
    if (cslot == new_major_slot) {
        tmp_capability |= (RAF_CDMA_GROUP | RAF_EVDO_GROUP);
    }
    getMclStatusManager(new_major_slot)->setIntValue(
            RFX_STATUS_KEY_SLOT_CAPABILITY, tmp_capability, false, false);
}

void RmmCapabilitySwitchRequestHandler::sendEGRAT() {
    int raf = getMclStatusManager(m_slot_id)->getIntValue(RFX_STATUS_KEY_SLOT_FIXED_CAPABILITY, 0);
    int rat;
    sp<RfxMipcData> mipcRet = NULL;
    mipc_result_const_enum ret = mipc_result_const_NONE;
    uint32_t nw_type = 0;

    if(RmmCapabilitySwitchUtil::isDisableC2kCapability() == false &&
            RatConfig_isC2kSupported()) {
        raf |= RAF_CDMA_GROUP;
    } else {
        raf &= ~RAF_CDMA_GROUP;
    }
    if(!RatConfig_isGsmSupported()) {
        raf &= ~RAF_GSM_GROUP;
    }
    raf = RmmCapabilitySwitchUtil::getAdjustedRaf(raf);
    switch (raf) {
        case RAF_GSM_GROUP:
            rat = 0;
            break;
        case RAF_WCDMA_GROUP:
            rat = 1;
            break;
        case RAF_GSM_GROUP | RAF_WCDMA_GROUP:
            rat = 2;
            break;
        case RAF_LTE:
            rat = 3;
            break;
        case RAF_GSM_GROUP | RAF_LTE:
            rat = 4;
            break;
        case RAF_WCDMA_GROUP | RAF_LTE:
            rat = 5;
            break;
        case RAF_GSM_GROUP | RAF_WCDMA_GROUP | RAF_LTE:
            rat = 6;
            break;
        case RAF_CDMA_GROUP:
            rat = 7;
            break;
        case RAF_GSM_GROUP | RAF_CDMA_GROUP:
            rat = 8;
            break;
        case RAF_GSM_GROUP | RAF_WCDMA_GROUP | RAF_CDMA_GROUP:
            rat = 10;
            break;
        case RAF_LTE | RAF_CDMA_GROUP:
            rat = 11;
            break;
        case RAF_GSM_GROUP | RAF_LTE | RAF_CDMA_GROUP:
            rat = 12;
            break;
        case RAF_GSM_GROUP | RAF_WCDMA_GROUP | RAF_LTE | RAF_CDMA_GROUP:
            rat = 14;
            break;
        case RAF_NR:
            rat = 15;
            break;
        case RAF_NR | RAF_GSM_GROUP:
            rat = 16;
            break;
        case RAF_NR | RAF_WCDMA_GROUP:
            rat = 17;
            break;
        case RAF_NR | RAF_GSM_GROUP | RAF_WCDMA_GROUP:
            rat = 18;
            break;
        case RAF_NR | RAF_LTE:
            rat = 19;
            break;
        case RAF_NR | RAF_LTE | RAF_GSM_GROUP:
            rat = 20;
            break;
        case RAF_NR | RAF_LTE | RAF_WCDMA_GROUP:
            rat = 21;
            break;
        case RAF_NR | RAF_LTE | RAF_WCDMA_GROUP | RAF_GSM_GROUP:
            rat = 22;
            break;
        case RAF_NR | RAF_CDMA_GROUP:
            rat = 23;
            break;
        case RAF_NR | RAF_GSM_GROUP | RAF_CDMA_GROUP:
            rat = 24;
            break;
        case RAF_NR | RAF_WCDMA_GROUP | RAF_CDMA_GROUP:
            rat = 25;
            break;
        case RAF_NR | RAF_LTE | RAF_CDMA_GROUP:
            rat = 26;
            break;
        case RAF_NR | RAF_GSM_GROUP | RAF_WCDMA_GROUP | RAF_CDMA_GROUP:
            rat = 27;
            break;
        case RAF_NR | RAF_LTE | RAF_GSM_GROUP | RAF_CDMA_GROUP:
            rat = 28;
            break;
        case RAF_NR | RAF_LTE | RAF_WCDMA_GROUP | RAF_CDMA_GROUP:
            rat = 29;
            break;
        case RAF_NR | RAF_LTE | RAF_CDMA_GROUP | RAF_GSM_GROUP | RAF_WCDMA_GROUP:
            rat = 30;
            break;
        default:
            rat = 14;
            break;
    }

    // bit0: GSM, bit1: UMTS, bit2: LTE, bit3: NR, bit4: C2K
    if ((raf & RAF_GSM_GROUP) == RAF_GSM_GROUP) {
        nw_type |= 1;
    }
    if ((raf & RAF_WCDMA_GROUP) == RAF_WCDMA_GROUP) {
        nw_type |= 2;
    }
    if ((raf & RAF_LTE) == RAF_LTE) {
        nw_type |= 4;
    }
    if ((raf & RAF_NR) == RAF_NR) {
        nw_type |= 8;
    }
    if ((raf & RAF_CDMA_GROUP) == RAF_CDMA_GROUP) {
        nw_type |= 16;
    }

    sp<RfxMipcData> mipcMsg = RfxMipcData::obtainMipcData(
            MIPC_NW_SET_RADIO_CAPABILITY_REQ, m_slot_id);
    mipcMsg->addMipcTlvUint8(MIPC_NW_SET_RADIO_CAPABILITY_REQ_T_RADIO_CAPABILITY, nw_type);

    logI(RFX_LOG_TAG, "sendEGRAT: raf=%d, rat=%d, nw_type=%d", raf, rat, nw_type);

    mipcRet = callToMipcMsgSync(mipcMsg);
    ret = (mipc_result_const_enum) mipcRet->getResult();

    logD(RFX_LOG_TAG, "sendEGRAT: ret=%d", ret);
}

void RmmCapabilitySwitchRequestHandler::notifySIMInitDone(int slot_id) {
    RFX_UNUSED(slot_id);
    /*
    RFX_LOG_I(RFX_LOG_TAG, "notifySIMInitDone, slot:%d, sim_init_state:0x%x",
              slot_id, s_sim_init_state);
    s_sim_init_state_mutex.lock();
    s_sim_init_state |= (1 << slot_id);
    s_sim_init_state_mutex.unlock();
    */
}
/*
int RmmCapabilitySwitchRequestHandler::getSIMInitState() {
    int ret;
    s_sim_init_state_mutex.lock();
    ret = s_sim_init_state;
    s_sim_init_state_mutex.unlock();
    return ret;
}

void RmmCapabilitySwitchRequestHandler::setSIMInitState(int val) {
    s_sim_init_state_mutex.lock();
    s_sim_init_state = val;
    s_sim_init_state_mutex.unlock();
}

bool RmmCapabilitySwitchRequestHandler::waitSIMInitDone() {
    for (int i = 0; i < RfxRilUtils::rfxGetSimCount(); i++) {
        int retry_count = 0;
        while ((getSIMInitState() & (1 << i)) == 0) {
            usleep(100*1000);
            retry_count++;
            //logD(RFX_LOG_TAG, "wait SIM[%d] init done, retry:%d", i, retry_count);
            if (retry_count > 100) {
                rfx_property_set("vendor.gsm.ril.eboot", "1");
                // resetRadio();
                return false;
            }
        }
    }
    return true;
}
*/
