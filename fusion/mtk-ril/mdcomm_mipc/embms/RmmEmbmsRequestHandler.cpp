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

#include "RmmEmbmsRequestHandler.h"
#include <telephony/mtk_ril.h>
#include "rfx_properties.h"

#include "hardware/ccci_intf.h"
#include "netutils/ifc.h"
#include <linux/if.h>
#include <stdint.h>
#include <time.h>
#include <string>


static const int request[] = {
    RFX_MSG_REQUEST_EMBMS_AT_CMD,
    RFX_MSG_REQUEST_EMBMS_ENABLE,
    RFX_MSG_REQUEST_EMBMS_DISABLE,
    RFX_MSG_REQUEST_EMBMS_START_SESSION,
    RFX_MSG_REQUEST_EMBMS_STOP_SESSION,
    RFX_MSG_REQUEST_EMBMS_GET_TIME,
    RFX_MSG_REQUEST_EMBMS_SET_E911,
    RFX_MSG_REQUEST_RTC_EMBMS_GET_COVERAGE_STATE,
    RFX_MSG_REQUEST_EMBMS_TRIGGER_CELL_INFO_NOTIFY,
};

static const int events[] = {
    RFX_MSG_EVENT_EMBMS_POST_NETWORK_UPDATE,
    RFX_MSG_EVENT_EMBMS_POST_HVOLTE_UPDATE,
    RFX_MSG_EVENT_EMBMS_POST_SAI_UPDATE,
    RFX_MSG_EVENT_EMBMS_POST_SESSION_UPDATE,
};

// register handler to channel
//RFX_IMPLEMENT_MIPC_HANDLER_CLASS(RmmEmbmsRequestHandler, RIL_CMD_PROXY_6);
RFX_IMPLEMENT_HANDLER_CLASS(RmmEmbmsRequestHandler, RIL_CMD_PROXY_6);

const char* RmmEmbmsRequestHandler::CCMNI_IFNAME_CCMNI = "ccmni";
int RmmEmbmsRequestHandler::embms_sock_fd;
int RmmEmbmsRequestHandler::embms_sock6_fd;

int VDBG = 1;

RmmEmbmsRequestHandler::RmmEmbmsRequestHandler(int slot_id, int channel_id) :
        RfxBaseHandler(slot_id, channel_id) {
    logD(LOG_TAG, "VDBG = %d", VDBG);

    RmmEmbmsRequestHandler::embms_sock_fd = 0;
    RmmEmbmsRequestHandler::embms_sock6_fd = 0;
    memset(&g_active_session, 0xff, sizeof(RIL_EMBMS_LocalSessionNotify));
    memset(&g_available_session, 0xff, sizeof(RIL_EMBMS_LocalSessionNotify));
    registerToHandleRequest(request, sizeof(request)/sizeof(int));
    registerToHandleEvent(events, sizeof(events)/sizeof(int));
}

RmmEmbmsRequestHandler::~RmmEmbmsRequestHandler() {
}

void RmmEmbmsRequestHandler::onHandleRequest(const sp<RfxMclMessage>& msg) {
    if (VDBG) logV(LOG_TAG, "onHandleRequest: %s", idToString(msg->getId()));
    int request = msg->getId();
    switch(request) {
        case RFX_MSG_REQUEST_EMBMS_AT_CMD:
            requestEmbmsAt(msg);
            break;
        case RFX_MSG_REQUEST_EMBMS_ENABLE:
            requestLocalEmbmsEnable(msg);
            break;
        case RFX_MSG_REQUEST_EMBMS_DISABLE:
            requestLocalEmbmsDisable(msg);
            break;
        case RFX_MSG_REQUEST_EMBMS_START_SESSION:
            requestLocalEmbmsStartSession(msg);
            break;
        case RFX_MSG_REQUEST_EMBMS_STOP_SESSION:
            requestLocalEmbmsStopSession(msg);
            break;
        case RFX_MSG_REQUEST_EMBMS_GET_TIME:
            requestLocalEmbmsGetNetworkTime(msg);
            break;
        case RFX_MSG_REQUEST_EMBMS_SET_E911:
            requestLocalEmbmsSetCoverageStatus(msg);
            break;
        case RFX_MSG_REQUEST_RTC_EMBMS_GET_COVERAGE_STATE:
            requestEmbmsGetCoverageStatus(msg);
            break;
        case RFX_MSG_REQUEST_EMBMS_TRIGGER_CELL_INFO_NOTIFY:
            requestLocalTriggerCellInfoNotify(msg);
            break;

        default:
            logE(LOG_TAG, "Should not be here");
            break;
    }
}

void RmmEmbmsRequestHandler::onHandleEvent(const sp<RfxMclMessage>& msg) {
    if (VDBG) logV(LOG_TAG, "onHandleEvent: %s", idToString(msg->getId()));
    int id = msg->getId();
    switch(id) {
        case RFX_MSG_EVENT_EMBMS_POST_NETWORK_UPDATE:
            postEpsNetworkUpdate(msg);
            break;
        case RFX_MSG_EVENT_EMBMS_POST_HVOLTE_UPDATE:
            postHvolteUpdate(msg);
            break;
        case RFX_MSG_EVENT_EMBMS_POST_SAI_UPDATE:
            postSaiListUpdate(msg);
            break;
        case RFX_MSG_EVENT_EMBMS_POST_SESSION_UPDATE:
            postSessionListUpdate(msg);
            break;
        default:
            logE(LOG_TAG, "Should not be here for %s", idToString(msg->getId()));
            break;
    }
}

void RmmEmbmsRequestHandler::postSessionListUpdate(const sp<RfxMclMessage>& msg) {
    int index = 0;
    int available_count = 0;
    int active_count = 0;
    RfxAtLine* line;
    int current_enabled;
    int num_sessions = -1;  // -1 means not set yet
    int skip;
    int err;
    char* tmp_tmgi;
    char* tmp_session_id;
    int tmp_status;

    logI(LOG_TAG, "postSessionListUpdate");
    RIL_EMBMS_LocalSessionNotify active_session;
    RIL_EMBMS_LocalSessionNotify available_session;
    sp<RfxAtResponse> p_response;
    sp<RfxMclMessage> response;
    memset(&active_session, 0, sizeof(active_session));
    memset(&available_session, 0, sizeof(available_session));

    p_response = atSendCommandMultiline("AT+EMSLU?", "+EMSLU");
    err = p_response->getError();

    if (err < 0 || p_response->getSuccess() == 0 ||
            p_response->getIntermediates()  == NULL) {
        logE(LOG_TAG, "AT+EMSLU? Fail");
        return;
    }

    // +EMSLU: <enable>
    line = p_response->getIntermediates();
    line->atTokStart(&err);
    current_enabled = line->atTokNextint(&err);
    if (err < 0) {
        goto error;
    }

    // [+EMSLUI: <num_sessions>,<x>,<tmgix>,[<session_idx>],<statusx>][...repeat num_sessions times]
    line = line->getNext();
    for (; line != NULL; line = line->getNext()) {
        line->atTokStart(&err);
        if (err < 0) goto error;
        // <num_sessions>
        if ( num_sessions == -1 ) {
            num_sessions = line->atTokNextint(&err);
            if (err < 0) goto error;
            logD(LOG_TAG, "num_sessions:%d", num_sessions);
            index = 0;
        } else {
            skip = line->atTokNextint(&err);
            if (err < 0) goto error;
        }

        if ( index < num_sessions ) {
            // <x>
            skip = line->atTokNextint(&err);
            if (err < 0) goto error;
            // x should be index+1
            if (skip != (index+1)) {
                logE(LOG_TAG, "x(%d)!=index(%d)+1", skip, index);
            }

            // <tmgix>
            if (index >= EMBMS_MAX_NUM_SESSIONINFO) {
                break;
            }
            tmp_tmgi = line->atTokNextstr(&err);
            if (err < 0) goto error;
            tmp_session_id = line->atTokNextstr(&err);
            if (err < 0) goto error;
            tmp_status = line->atTokNextint(&err);
            if (err < 0) goto error;

            if (tmp_status == 0 || tmp_status == 1) {
                strncpy(available_session.tmgix[available_count], tmp_tmgi, EMBMS_MAX_LEN_TMGI);
                strncpy(available_session.session_idx[available_count], tmp_session_id,
                    EMBMS_LEN_SESSION_IDX);
                available_count++;
                available_session.tmgi_info_count = available_count;
            }
            if (tmp_status == 1) {
                strncpy(active_session.tmgix[active_count], tmp_tmgi, EMBMS_MAX_LEN_TMGI);
                strncpy(active_session.session_idx[active_count], tmp_session_id,
                    EMBMS_LEN_SESSION_IDX);
                active_count++;
                active_session.tmgi_info_count = active_count;
            }
            index++;
        }
    }

    logI(LOG_TAG, "active_session_count=%d, available_session_count=%d",
                        active_session.tmgi_info_count, available_session.tmgi_info_count);

    if (memcmp(&g_active_session, &active_session, sizeof(RIL_EMBMS_LocalSessionNotify)) != 0) {
        response = RfxMclMessage::obtainUrc(RFX_MSG_URC_EMBMS_ACTIVE_SESSION,
            msg->getSlotId(), RfxEmbmsLocalSessionNotifyData(&active_session,
            sizeof(active_session)));
        responseToTelCore(response);
        memcpy(&g_active_session, &active_session, sizeof(RIL_EMBMS_LocalSessionNotify));
    }

    if (memcmp(&g_available_session, &available_session, sizeof(RIL_EMBMS_LocalSessionNotify)) != 0) {
        response = RfxMclMessage::obtainUrc(RFX_MSG_URC_EMBMS_AVAILABLE_SESSION,
            msg->getSlotId(), RfxEmbmsLocalSessionNotifyData(&available_session,
            sizeof(available_session)));
        responseToTelCore(response);
        memcpy(&g_available_session, &available_session, sizeof(RIL_EMBMS_LocalSessionNotify));
    }

    return;
error:
    logE(LOG_TAG, "[embms]Error during parse AT command");
}

void RmmEmbmsRequestHandler::postSaiListUpdate(const sp<RfxMclMessage>& msg) {
    int err = 0;
    sp<RfxAtResponse> p_response;
    sp<RfxMclMessage> response;

    logI(LOG_TAG, "postSaiListUpdate");

    RIL_EMBMS_LocalSaiNotify embms_sailit;
    memset(&embms_sailit, 0, sizeof(embms_sailit));

    p_response = atSendCommandMultiline("AT+EMSAIL?", "+EMSAIL");
    err = p_response->getError();

    if (err < 0 || p_response->getSuccess() == 0 ||
            p_response->getIntermediates()  == NULL) {
        return;
    }

    if (!parseSailist(p_response, &embms_sailit)) {
        return;
    }

    response = RfxMclMessage::obtainUrc(RFX_MSG_URC_EMBMS_SAI_LIST_NOTIFICATION,
        msg->getSlotId(), RfxEmbmsLocalSaiNotifyData(&embms_sailit, sizeof(embms_sailit)));
    responseToTelCore(response);
    return;
}

void RmmEmbmsRequestHandler::postHvolteUpdate(const sp<RfxMclMessage>& msg) {
    char *urc = (char *)msg->getData()->getData();
    RfxAtLine* atline = new RfxAtLine(urc, NULL);
    RfxAtLine* atline_free = atline;
    logV(LOG_TAG, "postHvolteUpdate urc=%s", urc);

    int err;
    int mode;
    int srlte_enable;
    sp<RfxAtResponse> p_response;

    atline->atTokStart(&err);
    if (err < 0) goto error;

    mode = atline->atTokNextint(&err);
    if (err < 0) goto error;
    if (VDBG) logV(LOG_TAG, "mode = %d", mode);

    if (mode == 0) {
        srlte_enable = 1;
    } else {
        srlte_enable = 0;
    }

    delete atline_free;
    atline_free = NULL;

    p_response = atSendCommand(String8::format("AT+EMEVT=2,%d", srlte_enable));
    err = p_response->getError();
    if (err != 0 || p_response->getSuccess() == 0) {
        if (VDBG) logV(LOG_TAG, "Failed to set eMBMS coverage status");
        goto error;
    }
    return;

error:
    if ( atline_free != NULL ) {
        delete atline_free;
    }
    logE(LOG_TAG, "Error during postHvolteUpdate");
}

int RmmEmbmsRequestHandler::convertLteRegState(int status, int eAct) {
    /*
        <eAct>:
            0x1000  L4C_LTE_SUPPORT
            0x2000  L4C_LTE_CA_SUPPORT
            0xffff  L4C_NOT_CHANGE
    */
    int result = status;
    if (result > 5) {
        // Convert stat not preferred by middleware
        result = 0;
    } else if (!(eAct >= 0x1000 && eAct <= 0x2000)) {
        // For LTE only
        result = 0;
    }
    return result;
}

void RmmEmbmsRequestHandler::postEpsNetworkUpdate(const sp<RfxMclMessage>& msg) {
    char *urc = (char *)msg->getData()->getData();
    RfxAtLine* atline = new RfxAtLine(urc, NULL);
    RfxAtLine* atline_free = atline;
    logV(LOG_TAG, "postEpsNetworkUpdate urc=%s", urc);
    int err;
    int status;

    sp<RfxAtResponse> p_response;
    char* plmn = NULL;
    RfxAtLine* line;
    int skip;
    int intdata[3];
    sp<RfxMclMessage> response;
    unsigned int cell_id = 0x0fffffff;
    char* cell_id_mask = NULL;
    int eAct;
    /*
    +EGREG: <stat>[,[<lac>],[<ci>],[<eAct>][,<existence >,<roam_indicator>]][,<cause_type>,<reject_cause>]]
    List of <stat>:
        0 : not registered, MT is not currently searching an operator to register to
        1 : registered, home network (applicable also when <eAct> indicates 1xRTT/HRPD/eHRPD)
        2 : not registered, but MT is currently trying to attach or searching an operator
        3 : registration denied
        4 : unknown
        5 : registered, roaming (applicable also when <eAct> indicates 1xRTT/HRPD/eHRPD)
        6 : registered for "SMS only", home network (not applicable)
        7 : registered for "SMS only", roaming (not applicable)
        8 : attached for emergency bearer services only (see NOTE 2)
            (applicable only when <eAct> indicates 2,4,5,6)
        9 : registered for "CSFB not preferred", home network (not applicable)
        10: registered for "CSFB not preferred", roaming (not applicable)
        101:no NW, but need to find  NW (Mapping to C2K AT Command ^mode:0, +ECGREG:0)
        102:not registered, but MT find 1X NW existence (Mapping to C2K AT command ^mode:2)
        103:not registered, but MT find Do NW existence (Mapping to C2K AT Command ^mode:4)
        104:not registered, but MT find Do&1X NW existence (Mapping to C2K AT Command ^mode:8)
    <eAct>:
        0x1000		L4C_LTE_SUPPORT
        0x2000		L4C_LTE_CA_SUPPORT
        0xffff      L4C_NOT_CHANGE
    expected:
    +CEREG:<status>
        List of <status>:
        0 : not registered
        1 : registered, home network
        2 : not registered, trying to attach or searching an operator to register
        3 : registration denied
        4 : Flight mode
        5 : registered, roaming
    */

    atline->atTokStart(&err);
    if (err < 0) goto error;

    status = atline->atTokNextint(&err);
    if (err < 0) goto error;

    if (VDBG) logV(LOG_TAG, "status = %d", status);

    // Need cell info
    if (atline->atTokHasmore()) {
        // <lac/tac>
        cell_id = atline->atTokNexthexint(&err);
        cell_id_mask = RmmEmbmsUtils::addLogMask(cell_id);
        if (err < 0) goto error;
        if (VDBG) logV(LOG_TAG, "tac: %s", cell_id_mask);
        if (cell_id_mask) {
            free(cell_id_mask);
            cell_id_mask = NULL;
        }

        // <cid>
        cell_id = atline->atTokNexthexint(&err);
        cell_id_mask = RmmEmbmsUtils::addLogMask(cell_id);
        if (VDBG) logV(LOG_TAG, "cid: %s", cell_id_mask);
        if (err < 0 || (cell_id > 0x0fffffff && cell_id != 0xffffffff)) {
            logE(LOG_TAG, "The value in the field <cid> is not valid: %s", cell_id_mask);
        }
        if (cell_id_mask) {
            free(cell_id_mask);
            cell_id_mask = NULL;
        }

        // <eAct>
        eAct = atline->atTokNextint(&err);
        if (VDBG) logV(LOG_TAG, "eAct: %04X", eAct);
        if (err < 0) eAct = 0;
        status = convertLteRegState(status, eAct);
    } else {
        logE(LOG_TAG, "No cell_id available in EGREG!");
    }

    delete atline_free;
    atline_free = NULL;

    p_response = atSendCommandSingleline("AT+EOPS?", "+EOPS:");
    err = p_response->getError();
    if (err != 0 || p_response->getSuccess() == 0 ||
            p_response->getIntermediates() == NULL) {
        goto error;
    }

    line = p_response->getIntermediates();
    line->atTokStart(&err);
    if (err < 0) goto error;

    /* <mode> */
    skip = line->atTokNextint(&err);
    if (err < 0 || skip < 0 || skip > 4) {
        logE(LOG_TAG, "The <mode> is an invalid value!!!");
        goto error;
    } else if (skip == 2) {  // deregister
        logW(LOG_TAG, "The <mode> is 2 so we ignore the follwoing fields!!!");
    } else if (line->atTokHasmore()) {
        /* <format> */
        skip = line->atTokNextint(&err);
        if (err < 0 || skip != 2) {
            logW(LOG_TAG, "The <format> is incorrect: expect 2, receive %d", skip);
            goto error;
        }
        // a "+COPS: 0, n" response is also possible
        if (!line->atTokHasmore()) {
        } else {
            /* <oper> */
            plmn = line->atTokNextstr(&err);
            if (err < 0) goto error;

            if (VDBG) logV(LOG_TAG, "Get operator code: %s", plmn);
        }
    }

    if (cell_id != 0x0fffffff && plmn != NULL && strlen(plmn) > 0) {
        intdata[0] = cell_id;
        intdata[1] = status;
        intdata[2] = (plmn == NULL)? 0:atoi(plmn);
        response = RfxMclMessage::obtainUrc(RFX_MSG_URC_EMBMS_CELL_INFO_NOTIFICATION,
            msg->getSlotId(), RfxIntsData(intdata, 3));
        responseToTelCore(response);
    } else {
        cell_id_mask = RmmEmbmsUtils::addLogMask(cell_id);
        logE(LOG_TAG, "Error due to cell_id = %s", cell_id_mask);
        if (cell_id_mask) {
            free(cell_id_mask);
            cell_id_mask = NULL;
        }
    }
    return;

error:
    if (atline_free != NULL) {
        delete atline_free;
    }
    logE(LOG_TAG, "Error during postEpsNetworkUpdate");
}

bool RmmEmbmsRequestHandler::parseSailist(sp<RfxAtResponse> p_response,
    RIL_EMBMS_LocalSaiNotify* p_embms_sailist) {
    RfxAtLine* line;
    int err = 0, count = 0, value = 0;
    int nfreq_index = 0, emsailcf_done = 0;
    int i;

    logD(LOG_TAG, "[parseSailist]");
    p_embms_sailist->nsai_total = 0;

    // Skip +EMSAIL: <enable>.
    line = p_response->getIntermediates();
    line = line->getNext();

    for (; line != NULL; line = line->getNext()) {
        line->atTokStart(&err);

        if (err < 0) return false;

        if (!emsailcf_done) {
            int cfreq_index = 0;
            // +EMSAILCF: <num_intra_freq>[,<freq_1>[,<freq_2>[...]],<num_sais>,<sai_1>[,<sai_2>[...]]]
            count = line->atTokNextint(&err);

            if (err < 0) return false;

            // read current freq first
            emsailcf_done = 1;
            if (VDBG) logV(LOG_TAG, "num_cf = %d", count);

            for (i = 0; i < count; i++) {
                value = line->atTokNextint(&err);
                if (err < 0) {
                    return false;
                }
                if (cfreq_index < EMBMS_MAX_NUM_NEIGHBOR_FREQ) {
                    if (VDBG) logV(LOG_TAG, "cfx = %d, idx = %d", value, cfreq_index);
                    p_embms_sailist->curFreqData[cfreq_index] = value;
                    cfreq_index++;
                    p_embms_sailist->cf_total = cfreq_index;
                } else {
                    logW(LOG_TAG, "Warning! curFreqData is full");
                }
            }

            if (p_embms_sailist->cf_total > 0) {
                count = line->atTokNextint(&err);
            } else {
                // If no current freq which means no sai. No more AT data to read
                count = 0;
            }

            if (err < 0) return false;

            p_embms_sailist->csai_total = count;

            if (VDBG) logV(LOG_TAG, "csai_total = %d", p_embms_sailist->csai_total);

            for (i = 0; i < count; i++) {
                value = line->atTokNextint(&err);
                if (err < 0) {
                    return false;
                }

                p_embms_sailist->curSaiData[i] = value;
                if (VDBG) logV(LOG_TAG, "s sai[%d] = %d" , i, value);
            }
        } else {
            // +EMSAILNF: <num_nf>,[<x>,<nfx>[,<num_bands_nfx>[,<band1_nfx>[,<band2_nfx>[,<...>]]]]
            //    [,<num_sais_nfx>[,<sai_1_nfx>[,<sai_2_nfx>[,<...>]]]][...]]
            //  repeat several lines.
            count = line->atTokNextint(&err);  // num_nf

            if (err < 0) return false;

            if (VDBG) logV(LOG_TAG, "num_nf = %d", count);
            if (count > 0) {
                count = line->atTokNextint(&err);  // x
                // x should be nfreq_index + 1;
                value = line->atTokNextint(&err);  // nfx
                if (err < 0) return false;
                if (VDBG) logV(LOG_TAG, "nfx = %d, idx = %d", value, nfreq_index);
                if (nfreq_index < EMBMS_MAX_NUM_NEIGHBOR_FREQ) {
                    p_embms_sailist->neiFreqData[nfreq_index] = value;
                } else {
                    logW(LOG_TAG, "Warning! neiFreqData is full");
                }

                count = line->atTokNextint(&err);  // num_bands_nfx
                if (err < 0) return false;
                if (VDBG) logV(LOG_TAG, "num_bands_nfx = %d", count);
                for (i = 0; i < count; i++) {
                    value = line->atTokNextint(&err);  // bandy_nfx
                    if (err < 0) {
                        return false;
                    }
                }

                count = line->atTokNextint(&err);  // num_sais_nfx
                if (err < 0) return false;
                if (VDBG) logV(LOG_TAG, "num_sais_nfx = %d", count);

                if (nfreq_index < EMBMS_MAX_NUM_NEIGHBOR_FREQ) {
                    p_embms_sailist->nsai_count_per_group[nfreq_index] = count;
                    // The last one use nfreq_index, increase counter;
                    nfreq_index++;
                    p_embms_sailist->nf_total = nfreq_index;
                } else {
                    logW(LOG_TAG, "Warning! nsai_count_per_group is full");
                }


                for (i = 0; i < count; i++) {
                    value = line->atTokNextint(&err);
                    if (err < 0) {
                        return false;
                    }

                    if (p_embms_sailist->nsai_total + i >= EMBMS_MAX_NUM_SAI) {
                        logW(LOG_TAG, "Error! neigData[] is full!");
                        continue;
                    }

                    p_embms_sailist->neiSaiData[p_embms_sailist->nsai_total + i] = value;
                }
            } else {
                //Force break for loop to prevent p_cur not end due to unknown reason
                break;
            }
            logD(LOG_TAG, "n sai[%d] = %d" , p_embms_sailist->nsai_total + i, value);
            p_embms_sailist->nsai_total += count;
        }
    }

    return true;
}

void RmmEmbmsRequestHandler::requestAtGetSaiList_old(const sp<RfxMclMessage>& msg) {
    // AT%MBMSCMD="GET_SAIS_LIST" , for old middleware version only
    sp<RfxAtResponse> p_response;
    int err = 0;
    int i;
    String8 cmdline("");
    String8 response_str("");
    RIL_EMBMS_LocalSaiNotify embms_sailit;
    sp<RfxMclMessage> response;
    memset(&embms_sailit, 0, sizeof(embms_sailit));
    char *data = (char *)msg->getData()->getData();
    logI(LOG_TAG, "[requestAtGetSaiList]%s", data);

    p_response = atSendCommandMultiline("AT+EMSAIL?", "+EMSAIL");
    err = p_response->getError();

    if (err < 0 || p_response->getSuccess() == 0 ||
            p_response->getIntermediates()  == NULL) {
        goto error;
    }

    if (!parseSailist(p_response, &embms_sailit)) {
        goto error;
    }

    // cmdline = <SAI_COUNT>,[<csai1>,<csai2>,K],<SAI_COUNT>,[<nsai1>,<nsai2>,K]
    cmdline.append(String8::format("%d", embms_sailit.csai_total));

    // csai1
    for (i = 0; i < (int) embms_sailit.csai_total; i++) {
        cmdline.append(String8::format(",%d", embms_sailit.curSaiData[i]));
    }

    // n-SAI_COUNT
    cmdline.append(String8::format(",%d", embms_sailit.nsai_total));

    for (i = 0; i < (int) embms_sailit.nsai_total; i++) {
        cmdline.append(String8::format(",%d", embms_sailit.neiSaiData[i]));
    }

    // %MBMSCMD:<SAI_COUNT>,[<csai1>,<csai2>,K],<SAI_COUNT>,[<nsai1>,<nsai2>,K]
    // OK/ERROR
    response_str = String8::format("%%MBMSCMD:%s\nOK\n", cmdline.string());

    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxStringData((void *)response_str.string(), response_str.length()), msg, false);

    // response to TeleCore
    responseToTelCore(response);

    return;
error:
    response_str = String8("ERROR\n");

    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxStringData((void *)response_str.string(), response_str.length()), msg, false);

    // response to TeleCore
    responseToTelCore(response);

}

void RmmEmbmsRequestHandler::requestAtGetSaiList(const sp<RfxMclMessage>& msg) {
    // AT%MBMSCMD="CURRENT_SAI_LIST"
    sp<RfxAtResponse> p_response;
    int err = 0;
    int tail_index = 0, i, j;
    String8 cmdline("");
    String8 response_str("");
    RIL_EMBMS_LocalSaiNotify embms_sailit;
    sp<RfxMclMessage> response;
    memset(&embms_sailit, 0, sizeof(embms_sailit));
    char *data = (char *)msg->getData()->getData();
    logI(LOG_TAG, "[requestAtGetSaiList]%s", data);
    p_response = atSendCommandMultiline("AT+EMSAIL?", "+EMSAIL");
    err = p_response->getError();
    if (err < 0 || p_response->getSuccess() == 0 ||
            p_response->getIntermediates()  == NULL) {
        goto error;
    }

    if (!parseSailist(p_response, &embms_sailit)) {
        goto error;
    }

    // %MBMSCMD:<SAI_COUNT>,[<csai1>,<csai2>, <csai3>,...], <INTER_FREQUENCY_COUNT>,
    // [<Frequency_1>,<SAI_COUNT_1>,[<nsai11>, <nsai12>, <nsai13>,...]],
    // [<Frequency_n>,<SAI_COUNT_n>,[<nsain1>, <nsain2>, <nsain3>,...]]
    // OK/ERROR

    // SAI_COUNT
    cmdline.append(String8::format("%d", embms_sailit.csai_total));

    // csai1
    for (i = 0; i < (int) embms_sailit.csai_total; i++) {
        cmdline.append(String8::format(",%d", embms_sailit.curSaiData[i]));
    }

    // INTER_FREQUENCY_COUNT
    cmdline.append(String8::format(",%d", embms_sailit.nf_total));

    for (i = 0; i < (int) embms_sailit.nf_total; i++) {
        // <Frequency_1>, <SAI_COUNT_1>
        cmdline.append(String8::format(",%d,%d", embms_sailit.neiFreqData[i],
                        embms_sailit.nsai_count_per_group[i]));

        // <nsai11>
        for (j = 0; j < (int) embms_sailit.nsai_count_per_group[i]; j++) {
            cmdline.append(String8::format(",%d", embms_sailit.neiSaiData[tail_index+j]));
        }
        tail_index += embms_sailit.nsai_count_per_group[i];
    }

    // OK/ERROR
    response_str = String8::format("%%MBMSCMD:%s\nOK\n", cmdline.string());

    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxStringData((void *)response_str.string(), response_str.length()), msg, false);

    // response to TeleCore
    responseToTelCore(response);
    return;
error:
    response_str = String8("ERROR\n");
    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxStringData((void *)response_str.string(), response_str.length()), msg, false);

    // response to TeleCore
    responseToTelCore(response);
}

void RmmEmbmsRequestHandler::requestAtNetworkInfo(const sp<RfxMclMessage>& msg) {
    // AT%MBMSCMD="NETWORK INFORMATION"
    int err = 0;
    sp<RfxAtResponse> p_response;
    RfxAtLine* line;
    String8 response_str("");
    unsigned int cell_id = 0x0fffffff;
    int skip;
    char* plmn = NULL;
    char *data = (char *)msg->getData()->getData();
    sp<RfxMclMessage> response;
    logI(LOG_TAG, "[requestAtNetworkInfo]%s", data);

    p_response = atSendCommandSingleline("AT+EGREG?", "+EGREG:");
    err = p_response->getError();
    // +EGREG: <n>,<stat>[,[<lac>],[<ci>],[<eAcT>],[<rac>],
    // [<nwk_existence>],[<roam_indicator>][,<cause_type>,<reject_cause>]]
    //  <n> = 1, +EGREG: <stat>
    //  <n> = 2, +EGREG: <n>,<stat>[,[<lac>],[<ci>],[<eAcT>],[<rac>],
    //              [<nwk_existence>],[<roam_indicator>][,<cause_type>,<reject_cause>]]
    //  <n> = 3, +EGREG: <n>,<stat>[,[<lac>],[<ci>],[<eAcT>],[<rac>][,<cause_type>,<reject_cause>]]

    if (err != 0 || p_response->getSuccess() == 0 ||
            p_response->getIntermediates() == NULL) goto error;

    line = p_response->getIntermediates();
    if (!parseCellId(line, &skip, &cell_id)) {
        cell_id = 0;
    }

    // %MBMSCMD:<cell_id>
    // OK/ERROR

    p_response = atSendCommandSingleline("AT+EOPS?", "+EOPS:");
    err = p_response->getError();
    if (err != 0 || p_response->getSuccess() == 0 ||
            p_response->getIntermediates() == NULL) {
        goto error;
    }

    line = p_response->getIntermediates();
    line->atTokStart(&err);
    if (err < 0) goto error;

    /* <mode> */
    skip = line->atTokNextint(&err);
    if (err < 0 || skip < 0 || skip > 4) {
        logE(LOG_TAG, "The <mode> is an invalid value!!!");
        goto error;
    } else if (skip == 2) {  // deregister
        logW(LOG_TAG, "The <mode> is 2 so we ignore the follwoing fields!!!");
    } else if (line->atTokHasmore()) {
        /* <format> */
        skip = line->atTokNextint(&err);
        if (err < 0 || skip != 2) {
            logW(LOG_TAG, "The <format> is incorrect: expect 2, receive %d", skip);
            goto error;
        }
        // a "+COPS: 0, n" response is also possible
        if (!line->atTokHasmore()) {
        } else {
            /* <oper> */
            plmn = line->atTokNextstr(&err);
            if (err < 0) goto error;

            logD(LOG_TAG, "Get operator code: %s", plmn);
        }
    }

    if (cell_id != 0x0fffffff && plmn != NULL && strlen(plmn) > 0) {
        // On android N all use latest Middleware, for RJIL also requirement >= 1.9
        response_str = String8::format("%%MBMSCMD:%s%07X\nOK\n", plmn, cell_id);
    } else {
        goto error;
    }

    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxStringData((void *)response_str.string(), response_str.length()), msg, false);

    // response to TeleCore
    responseToTelCore(response);

    return;
error:
    response_str = String8("ERROR\n");

    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxStringData((void *)response_str.string(), response_str.length()), msg, false);

    // response to TeleCore
    responseToTelCore(response);
}

int RmmEmbmsRequestHandler::getSignalStrength(RfxAtLine *line, int* rssi) {
    int err;
    int skip;
    int act;
    int rsrp_in_qdbm;
    int rsrq_in_qdbm;


    // 93 modem <LWG, C2K, EVDO>
    // +ECSQ: <sig1>,<sig2>,<rssi_in_qdbm>,<rscp_in_qdbm>,<ecn0_in_qdbm>,<rsrq_in_qdbm>,<rsrp_in_qdbm>,<Act>,<sig3>,<serv_band>
    // +ECSQ: <sig1>,<sig2>,<rssi_in_qdbm>,<rscp_in_qdbm>,<ecn0_in_qdbm>,<rsrq_in_qdbm>,<rsrp_in_qdbm>,<256>,<sig3>,<serv_band>
    // +ECSQ: <sig1>,<sig2>,<rssi_in_qdbm>,<rscp_in_qdbm>,<ecn0_in_qdbm>,<rsrq_in_qdbm>,<rsrp_in_qdbm>,<Act_EvDo>,<sig3>,<serv_band>

    // go to start position
    line->atTokStart(&err);
    if (err < 0) return -1;
    // <sig1>
    skip = line->atTokNextint(&err);
    if (err < 0) return -1;
    // <sig2>
    skip = line->atTokNextint(&err);
    if (err < 0) return -1;
    // <rssi_in_qdbm>, 2G
    skip = line->atTokNextint(&err);
    if (err < 0) return -1;

    // 3G part <rscp_in_qdbm>
    skip = line->atTokNextint(&err);
    if (err < 0) return -1;

    skip = line->atTokNextint(&err);
    if (err < 0) return -1;

    // for LTE
    rsrq_in_qdbm = line->atTokNextint(&err);
    if (err < 0) return -1;

    rsrp_in_qdbm = line->atTokNextint(&err);
    if (err < 0) return -1;
    // <Act>
    act = line->atTokNextint(&err);
    if (err < 0) return -1;

    // 0x0004     L4C_UMTS_SUPPORT
    // 0x0008     L4C_HSDPA_SUPPORT
    if ((act == 0x1000) || (act == 0x2000)) {
        rsrq_in_qdbm = (rsrq_in_qdbm/4) * (-1);
        if (rsrq_in_qdbm > 20) {
            rsrq_in_qdbm = 20;
        } else if (rsrq_in_qdbm < 3) {
            rsrq_in_qdbm = 3;
        }

        rsrp_in_qdbm = (rsrp_in_qdbm/4) * (-1);
        if (rsrp_in_qdbm > 140) {
            rsrp_in_qdbm = 140;
        } else if (rsrp_in_qdbm < 44) {
            rsrp_in_qdbm = 44;
        }

        *rssi = rsrp_in_qdbm;
    } else {
        logD(LOG_TAG, "getSignalStrength ignore none 4G result");
        return -1;
    }

    return 0;
}

void RmmEmbmsRequestHandler::requestAtBssiSignalLevel(const sp<RfxMclMessage>& msg) {
    // AT%MBMSCMD="BSSI_SIGNAL_LEVEL"
    // reference requestSignalStrength() in RmmNetworkRequestHandler
    sp<RfxAtResponse> p_response;
    int err;
    RfxAtLine* line;
    String8 response_str("");
    sp<RfxMclMessage> response;
    int bssi = 0;
    char *data = (char *)msg->getData()->getData();
    logI(LOG_TAG, "[requestAtBssiSignalLevel]%s", data);

    p_response = atSendCommandMultiline("AT+ECSQ", "+ECSQ:");
    err = p_response->getError();
    if (err < 0 || p_response->getSuccess() == 0 ||
            p_response->getIntermediates()  == NULL) {
        goto error;
    }

    line = p_response->getIntermediates();
    err = getSignalStrength(line, &bssi);

    if (err < 0) goto error;

    // %MBMSCMD:<BSSI signal level>
    // OK/ERROR
    response_str = String8::format("%%MBMSCMD:%d\nOK\n", bssi);

    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxStringData((void *)response_str.string(), response_str.length()), msg, false);

    // response to TeleCore
    responseToTelCore(response);
    return;

error:
    response_str = String8("ERROR\n");

    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxStringData((void *)response_str.string(), response_str.length()), msg, false);

    // response to TeleCore
    responseToTelCore(response);
}

void RmmEmbmsRequestHandler::dummyOkResponse(const sp<RfxMclMessage>& msg) {
    String8 response_str("OK\n");
    sp<RfxMclMessage> response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxStringData((void *)response_str.string(), response_str.length()), msg, false);

    // response to TeleCore
    responseToTelCore(response);
}

void RmmEmbmsRequestHandler::requestAtModemStatus(const sp<RfxMclMessage>& msg) {
    // AT+CFUN?
    sp<RfxAtResponse> p_response;
    String8 response_str("");
    sp<RfxMclMessage> response;
    char *data = (char *)msg->getData()->getData();
    logI(LOG_TAG, "[requestAtModemStatus]%s", data);
    RIL_Errno rilErrNo = RIL_E_SUCCESS;
    char atcmd[] = "AT+CFUN?";

    sp<RfxMipcData> initMipc = RfxMipcData::obtainMipcData(MIPC_SYS_AT_REQ, m_slot_id);
    initMipc->addMipcTlvStr(MIPC_SYS_AT_REQ_T_ATCMD, atcmd);
    sp<RfxMipcData> rsp_data = callToMipcMsgSync(initMipc);

    logD(LOG_TAG, "Modem Status, AT+CFUN? ,result: %d",rsp_data->getResult());
    uint16_t val_len = 0;
    const char *temp_value = nullptr;

    if (MIPC_RESULT_SUCCESS != rsp_data->getResult()) {
        rilErrNo = RIL_E_GENERIC_FAILURE;
        goto error;
    }

    temp_value = (char*) rsp_data->getMipcVal(MIPC_SYS_AT_REQ_T_ATCMD, &val_len);
    response_str = String8(temp_value);

    // AT+CFUN?
    // OK/ERROR
    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxStringData((void *)response_str.string(), response_str.length()), msg, false);

    // response to TeleCore
    responseToTelCore(response);
    return;

error:
    response_str = String8("ERROR\n");

    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxStringData((void *)response_str.string(), response_str.length()), msg, false);

    // response to TeleCore
    responseToTelCore(response);
}

void RmmEmbmsRequestHandler::requestAtEnableUrcEvents(const sp<RfxMclMessage>& msg) {
    // AT%MBMSEV=[0,1]

    int input_err = 0;
    int enable = 0;
    sp<RfxAtResponse> p_response;
    String8 response_str("");
    sp<RfxMclMessage> response;
    char *data = (char *)msg->getData()->getData();
    logI(LOG_TAG, "[requestAtEnableUrcEvents]%s", data);


   //for mipc
   RIL_Errno rilErrNo = RIL_E_SUCCESS;
   String8 val =  String8::format("AT+EMSRV=%d", enable);
   char atcmd[strlen(val) + 1];  // Make sure there's enough space
   strcpy(atcmd, val);
    uint16_t val_len = 0;
    const char *temp_value = nullptr;

    RfxAtLine* atline = new RfxAtLine(data, NULL);
    RfxAtLine* atline_free = atline;

    sp<RfxMipcData> initMipc = RfxMipcData::obtainMipcData(MIPC_SYS_AT_REQ, m_slot_id);
    initMipc->addMipcTlvStr(MIPC_SYS_AT_REQ_T_ATCMD, atcmd);
    sp<RfxMipcData> rsp_data = callToMipcMsgSync(initMipc);
    // skip to next '='
    atline->atTokEqual(&input_err);
    if (input_err < 0) {
        goto input_error;
    }

    enable = atline->atTokNextint(&input_err);
    if (input_err < 0) {
        goto input_error;
    }
    delete atline_free;
    atline_free = NULL;
    logD(LOG_TAG, "EnableUrcEvents Status, AT+EMSRV ,result: %d",rsp_data->getResult());

    if (MIPC_RESULT_SUCCESS != rsp_data->getResult()) {
        rilErrNo = RIL_E_GENERIC_FAILURE;
        goto error;
    }

    val =  String8::format("AT+EMSLU=%d", enable);
    strcpy(atcmd, val);
    initMipc = RfxMipcData::obtainMipcData(MIPC_SYS_AT_REQ, m_slot_id);
    initMipc->addMipcTlvStr(MIPC_SYS_AT_REQ_T_ATCMD, atcmd);
    rsp_data = callToMipcMsgSync(initMipc);
    logD(LOG_TAG, "EnableUrcEvents, AT+EMSLU ,result: %d",rsp_data->getResult());
    if (MIPC_RESULT_SUCCESS != rsp_data->getResult()) {
        rilErrNo = RIL_E_GENERIC_FAILURE;
        goto error;
    }

    val = String8::format("AT+EMSAIL=%d", enable);
    strcpy(atcmd, val);
    initMipc = RfxMipcData::obtainMipcData(MIPC_SYS_AT_REQ, m_slot_id);
    initMipc->addMipcTlvStr(MIPC_SYS_AT_REQ_T_ATCMD, atcmd);
    rsp_data = callToMipcMsgSync(initMipc);

    logD(LOG_TAG, "EnableUrcEvents Status,AT+EMSAIL ,result: %d",rsp_data->getResult());
        if (MIPC_RESULT_SUCCESS != rsp_data->getResult()) {
            rilErrNo = RIL_E_GENERIC_FAILURE;
            goto error;
        }

    temp_value = (char*) rsp_data->getMipcVal(MIPC_SYS_AT_REQ_T_ATCMD, &val_len);
    response_str = temp_value;

    response_str = String8("OK\n");

    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxStringData((void *)response_str.string(), response_str.length()), msg, false);

    // response to TeleCore
    responseToTelCore(response);
    return;

input_error:
    logE(LOG_TAG, "Input parameter error!!");
error:
    if (atline_free != NULL) {
        delete atline_free;
    }
    response_str = String8("ERROR\n");

    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxStringData((void *)response_str.string(), response_str.length()), msg, false);

    // response to TeleCore
    responseToTelCore(response);
}

void RmmEmbmsRequestHandler::requestAtAvailService(const sp<RfxMclMessage>& msg) {
    // AT%MBMSCMD?
    sp<RfxAtResponse> p_response;
    RfxAtLine* line;
    int skip;
    int num_sessions = -1;
    char current_session_tmgis[EMBMS_MAX_NUM_SESSIONINFO][EMBMS_MAX_LEN_TMGI + 1];
    char current_session_ids[EMBMS_MAX_NUM_SESSIONINFO][EMBMS_LEN_SESSION_IDX + 1];
    int index = 0;
    String8 cmdline("");
    String8 response_str("");
    char* tmpBuffer;
    sp<RfxMclMessage> response;
    int err = 0;
    char *data = (char *)msg->getData()->getData();
    logI(LOG_TAG, "[requestAtAvailService]%s", data);
    memset(current_session_tmgis, 0, sizeof(current_session_tmgis));
    memset(current_session_ids, 0, sizeof(current_session_ids));

    RIL_Errno rilErrNo = RIL_E_SUCCESS;
    char atcmd[] = "AT+EMSLU?";
    sp<RfxMipcData> initMipc = RfxMipcData::obtainMipcData(MIPC_EMBMS_EMSLU_REQ, m_slot_id);
    initMipc->addMipcTlvStr(mipc_embms_emslu_req_tlv_NONE, atcmd);
    sp<RfxMipcData> rsp_data = callToMipcMsgSync(initMipc);

    uint16_t val_len;
    mipc_embms_session_info_struct4 *session_info;
    uint8_t *enable_status;
    uint16_t *session_count;

    logD(LOG_TAG, "ession Info Status, AT+EMEVT? ,result: %d",rsp_data->getResult());
    if (MIPC_RESULT_SUCCESS != rsp_data->getResult()) {
        rilErrNo = RIL_E_GENERIC_FAILURE;
        goto error;
    }
    val_len = 0;
    session_info = (mipc_embms_session_info_struct4*) rsp_data->getMipcVal(MIPC_EMBMS_EMSLU_CNF_T_SESSION_LIST, &val_len);
    enable_status = (uint8_t*) rsp_data->getMipcVal(MIPC_EMBMS_EMSLU_CNF_T_IS_ENABLED, &val_len);
    session_count = (uint16_t*) rsp_data->getMipcVal(MIPC_EMBMS_EMSLU_CNF_T_SESSION_COUNT, &val_len);

    // <num_sessions>
    num_sessions = *session_count;
    logD(LOG_TAG, "num_sessions:%d", num_sessions);

    if (num_sessions > EMBMS_MAX_NUM_SESSIONINFO) {
        logE(LOG_TAG, "Over session size limitation");
        num_sessions = EMBMS_MAX_NUM_SESSIONINFO;
   }
   index = 0;


        // handle from <x>
        if (index < num_sessions && index < EMBMS_MAX_NUM_SESSIONINFO) {
            //  <x>
            skip = session_info->index;

            // x should be index+1
            if (skip != (index + 1)) {
                logE(LOG_TAG, "x(%d)!=index(%d)+1", skip, index);
            }

            // <tmgix>
            tmpBuffer = session_info->tmgi;


            if (VDBG) logV(LOG_TAG, "tmgi = %s", tmpBuffer);
            strlcpy(current_session_tmgis[index], tmpBuffer, EMBMS_MAX_LEN_TMGI);

            // <sessionId>
            tmpBuffer = session_info->tmgi;

            if (VDBG) logV(LOG_TAG, "sessionId = %s", tmpBuffer);
            strlcpy(current_session_ids[index], tmpBuffer, EMBMS_LEN_SESSION_IDX);

            // skip status, both active and available are counted as available

            index++;
          }


    // %MBMSCMD: <TMGI>[,<SessionID>]
    // OK/ERROR
    for (int i = 0; i < num_sessions; i++) {
        tmpBuffer = current_session_tmgis[i];

        if (!isTmgiEmpty(tmpBuffer)) {
            int session_ids_len = 0;
            session_ids_len = strlen(current_session_ids[i]);
            if (session_ids_len == 0) {
                cmdline.append(String8::format("%%MBMSCMD: %s\n", tmpBuffer));
            } else {
                char *endptr = NULL;
                int sessionId = (int) strtol(current_session_ids[i], &endptr, 16);
                cmdline.append(String8::format("%%MBMSCMD: %s,%d\n", tmpBuffer, sessionId));
            }
        }
    }
    response_str = String8::format("%sOK\n", cmdline.string());
    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxStringData((void *)response_str.string(), response_str.length()), msg, false);

    // response to TeleCore
    responseToTelCore(response);
    return;
error:
    response_str = String8("ERROR\n");
    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxStringData((void *)response_str.string(), response_str.length()), msg, false);

    // response to TeleCore
    responseToTelCore(response);
}

void RmmEmbmsRequestHandler::requestAtDeviceInfo(const sp<RfxMclMessage>& msg) {
    int fd;
    struct ifreq ifr;
    unsigned char *mac;
    String8 response_str("");
    sp<RfxMclMessage> response;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd >= 0) {
        int ret = 0;
        ifr.ifr_addr.sa_family = AF_INET;
        int result = sprintf(ifr.ifr_name, "%s%d", CCMNI_IFNAME_CCMNI, EMBMS_IFACE_ID - 1);
        if (result < 0) {
            logE(LOG_TAG, "sprintf fail for ifr.ifr_name");
        }
        ret = ioctl(fd, SIOCGIFHWADDR, &ifr);
        close(fd);
        mac = (unsigned char *)ifr.ifr_hwaddr.sa_data;
        if(ret < 0 ){
           response_str = String8("ERROR\n");
        }else{
          response_str = String8::format("%%MBMSCMD:%.2X:%.2X:%.2X:%.2X:%.2X:%.2X\nOK\n",
            mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        }

        logD(LOG_TAG, "mac address:%s", response_str.string());

        response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
                RfxStringData((void *)response_str.string(), response_str.length()), msg, false);

        // response to TeleCore
        responseToTelCore(response);
    } else {
        response_str = String8("ERROR\n");
        response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
                RfxStringData((void *)response_str.string(), response_str.length()), msg, false);

        // response to TeleCore
        responseToTelCore(response);
    }
}

void RmmEmbmsRequestHandler::requestAtSetPreference(const sp<RfxMclMessage>& msg) {
    //  AT%MBMSCMD="MBMS_PREFERENCE",[0,1]

    int input_err = 0;
    int enable = 0;
    String8 response_str("");
    sp<RfxAtResponse> p_response;
    sp<RfxMclMessage> response;
    char *data = (char *)msg->getData()->getData();
    RIL_Errno rilErrNo = RIL_E_SUCCESS;
    String8 val = String8::format("AT+EMPRI=%d", enable);
    char arr[strlen(val) + 1];  // Make sure there's enough space
    strcpy(arr, val);
    sp<RfxMipcData> initMipc = RfxMipcData::obtainMipcData(MIPC_SYS_AT_REQ, m_slot_id);
    initMipc->addMipcTlvStr(MIPC_SYS_AT_REQ_T_ATCMD, arr);
    sp<RfxMipcData> rsp_data = callToMipcMsgSync(initMipc);

    logI(LOG_TAG, "[requestAtSetPreference]%s", data);
    RfxAtLine* atline = new RfxAtLine(data, NULL);
    RfxAtLine* atline_free = atline;
    //  skip to next ','
    atline->atTokNextstr(&input_err);
    if (input_err < 0) {
        goto input_error;
    }

    enable = atline->atTokNextint(&input_err);
    if (input_err < 0) {
        goto input_error;
    }
    delete atline_free;
    atline_free = NULL;
    //  priority

    logD(LOG_TAG, "At Set Preference status, AT+EMPRI = %d ,result: %d",enable,rsp_data->getResult());
    if (MIPC_RESULT_SUCCESS != rsp_data->getResult()) {
        rilErrNo = RIL_E_GENERIC_FAILURE;
        goto error;
    }

    response_str = String8("OK\n");
    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxStringData((void *)response_str.string(), response_str.length()), msg, false);

    // response to TeleCore
    responseToTelCore(response);
    return;

input_error:
    logE(LOG_TAG, "Input parameter error!!");
error:
    if (atline_free != NULL) {
        delete atline_free;
    }
    response_str = String8("ERROR\n");
    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxStringData((void *)response_str.string(), response_str.length()), msg, false);

    // response to TeleCore
    responseToTelCore(response);
}

// AT+CEREG=?
// +CEREG: (3) / +CEREG: (0-3) / +CEREG: (1,3)
// OK
void RmmEmbmsRequestHandler::requestAtNetworkRegSupport(const sp<RfxMclMessage>& msg) {
    sp<RfxAtResponse> p_response;


    String8 response_str("");
    sp<RfxMclMessage> response;
    char *data = (char *)msg->getData()->getData();
    logI(LOG_TAG, "[requestAtNetworkRegSupport]%s", data);
    RIL_Errno rilErrNo = RIL_E_SUCCESS;
    char atcmd[] = "AT+EGREG=?";
    sp<RfxMipcData> initMipc = RfxMipcData::obtainMipcData(MIPC_SYS_AT_REQ, m_slot_id);
    initMipc->addMipcTlvStr(MIPC_SYS_AT_REQ_T_ATCMD, atcmd);
    sp<RfxMipcData> rsp_data = callToMipcMsgSync(initMipc);
    uint16_t val_len = 0;
    const char *temp_value;
    logD(LOG_TAG, "AtNetworkRegSupport status ,result: %d",rsp_data->getResult());
    if (MIPC_RESULT_SUCCESS != rsp_data->getResult()) {
        rilErrNo = RIL_E_GENERIC_FAILURE;
        goto error;
    }

    temp_value = (char*) rsp_data->getMipcVal(MIPC_SYS_AT_REQ_T_ATCMD, &val_len);
    response_str = String8(temp_value);

    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxStringData((void *)response_str.string(), response_str.length()), msg, false);

    // response to TeleCore
    responseToTelCore(response);
    return;

error:
    response_str = String8("ERROR\n");

    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxStringData((void *)response_str.string(), response_str.length()), msg, false);

    // response to TeleCore
    responseToTelCore(response);
}

// AT+CEREG?
// +CEREG: <n>,<stat>[,[<tac>],[<ci>],[<AcT>[,<cause_type>,<reject_cause>]]]
void RmmEmbmsRequestHandler::requestAtNetworkRegStatus(const sp<RfxMclMessage>& msg) {
    sp<RfxAtResponse> p_response;


    String8 response_str("");
    sp<RfxMclMessage> response;
    char *data = (char *)msg->getData()->getData();
    logI(LOG_TAG, "[requestAtNetworkRegStatus]%s", data);
    RIL_Errno rilErrNo = RIL_E_SUCCESS;
    char atcmd[] = "AT+EGREG=?";
    sp<RfxMipcData> initMipc = RfxMipcData::obtainMipcData(MIPC_SYS_AT_REQ, m_slot_id);
    initMipc->addMipcTlvStr(MIPC_SYS_AT_REQ_T_ATCMD, atcmd);
    sp<RfxMipcData> rsp_data = callToMipcMsgSync(initMipc);
    uint16_t val_len = 0;
    const char *temp_value;
    logD(LOG_TAG, "AtNetworkReg status ,result: %d",rsp_data->getResult());
    if (MIPC_RESULT_SUCCESS != rsp_data->getResult()) {
        rilErrNo = RIL_E_GENERIC_FAILURE;
        goto error;
    }

    temp_value = (char*) rsp_data->getMipcVal(MIPC_SYS_AT_REQ_T_ATCMD, &val_len);
    response_str = String8(temp_value);

    // AT+CFUN?
    // OK/ERROR
    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxStringData((void *)response_str.string(), response_str.length()), msg, false);

    // response to TeleCore
    responseToTelCore(response);
    return;

error:
    response_str = String8("ERROR\n");

    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxStringData((void *)response_str.string(), response_str.length()), msg, false);

    // response to TeleCore
    responseToTelCore(response);
}

void RmmEmbmsRequestHandler::requestEmbmsAt(const sp<RfxMclMessage>& msg) {
    char *data = (char *)msg->getData()->getData();
    logI(LOG_TAG, "requestEmbmsAt:%s", (char*)data);

    if (data == NULL) {
        logE(LOG_TAG, "Error!! requestEmbmsAt: get null!!");
    // for RJIL old middleware version, and this only occur from v1.8
    } else if (strStartsWith(data, "AT%MBMSCMD=\"CURRENT_SAI_LIST\"")) {
        if (isRjilSupport()) {
            requestAtGetSaiList_old(msg);
        } else {
            requestAtGetSaiList(msg);
        }
    } else if (strStartsWith(data, "AT%MBMSCMD=\"NETWORK INFORMATION\"")) {
        requestAtNetworkInfo(msg);
    } else if (strStartsWith(data, "AT%MBMSCMD=\"BSSI_SIGNAL_LEVEL\"")) {
        requestAtBssiSignalLevel(msg);
    } else if (strStartsWith(data, "AT+CMEE=")) {
        dummyOkResponse(msg);
    } else if (strStartsWith(data, "AT+CFUN?")) {
        requestAtModemStatus(msg);
    } else if (strStartsWith(data, "AT%MBMSEV=")) {
        requestAtEnableUrcEvents(msg);
    } else if (strStartsWith(data, "AT%MBMSCMD?")) {
        requestAtAvailService(msg);
    } else if (strStartsWith(data, "AT%MBMSCMD=?")) {
        dummyOkResponse(msg);
    } else if (strStartsWith(data, "AT%MBMSCMD=\"DEVICE INFO\"")) {
        requestAtDeviceInfo(msg);
    } else if (strStartsWith(data, "ATE1")) {
        dummyOkResponse(msg);
    } else if (strStartsWith(data, "AT%MBMSCMD=\"MBMS_PREFERENCE\"")) {
        requestAtSetPreference(msg);
    } else if (strStartsWith(data, "AT+CEREG=?")) {
        requestAtNetworkRegSupport(msg);
    } else if (strStartsWith(data, "AT+CEREG?")) {
        requestAtNetworkRegStatus(msg);
    } else if (strStartsWith(data, "AT+CEREG=")) {
        dummyOkResponse(msg);
    } else if (strStartsWith(data, "AT") && strlen(data) == 2) {
        dummyOkResponse(msg);
    } else {
        logE(LOG_TAG, "Unknown command.");
    }
}

bool RmmEmbmsRequestHandler::parseCellId(RfxAtLine* p_response, int* status,
                                        unsigned int* cell_id) {
    RfxAtLine* line;
    int skip;
    int err;
    int eAct;
    char* cell_id_mask = NULL;
    line = p_response;

    if (cell_id == NULL || status == NULL) {
        logE(LOG_TAG, "ptr is NULL!!");
        return false;
    }
    *cell_id = 0;
    line->atTokStart(&err);

    if (err < 0) return false;

    /* <n> */
    skip = line->atTokNextint(&err);

    if (err < 0) return false;

    /* <stat> */
    *status = line->atTokNextint(&err);

    if (err < 0) return false;

    if (line->atTokHasmore()) {
        /* <lac/tac> */
        skip = line->atTokNexthexint(&err);

        if (err < 0) return false;

        /* <cid> */
        *(int*)cell_id = line->atTokNexthexint(&err);
        cell_id_mask = RmmEmbmsUtils::addLogMask(*cell_id);
        logD(LOG_TAG, "cid: %s", cell_id_mask);

        if (err < 0 || (*cell_id > 0x0fffffff && *cell_id != 0xffffffff)) {
            logE(LOG_TAG, "The value in the field <cid> is not valid: %s", cell_id_mask);
            if (cell_id_mask) {
                free(cell_id_mask);
                cell_id_mask = NULL;
            }
            return false;
        }

        if (cell_id_mask) {
            free(cell_id_mask);
            cell_id_mask = NULL;
        }
        // <eAct>
        eAct = line->atTokNextint(&err);
        if (VDBG) logV(LOG_TAG, "eAct: %04X", eAct);
        if (err < 0) eAct = 0;
        *status = convertLteRegState(*status, eAct);
    } else {
        *cell_id = 0;
    }
    return true;
}

// for RJIL old middleware version with spec v1.8
bool RmmEmbmsRequestHandler::isRjilSupport() {
    // On android N all use latest Middleware, for RJIL also support requirement >= 1.9
    return false;
}

bool RmmEmbmsRequestHandler::isAtCmdEnableSupport() {
    bool ret = false;
    char prop[RFX_PROPERTY_VALUE_MAX] = {0};

    // for RJIL old middleware version
    if (isRjilSupport()) {
        return false;
    }

    rfx_property_get("persist.vendor.radio.embms.atenable", prop, "1");

    if (!strcmp(prop, "1")) {
        return true;
    } else if (!strcmp(prop, "0")) {
        return false;
    }

    return ret;
}

void RmmEmbmsRequestHandler::requestLocalEmbmsEnable(const sp<RfxMclMessage>& msg) {
    const int enable = 1;
    int err = 0;
    String8 cmd("");
    sp<RfxAtResponse> p_response;
    RIL_EMBMS_LocalEnableResp enable_response;
    int type;
    sp<RfxMclMessage> response;
    sp<RfxMclMessage> urc_response;

    unsigned int cell_id = 0x0fffffff;
    RfxAtLine* line;
    int skip;
    int status;
    char* plmn = NULL;
    int intdata[3];

    int *data = (int *)msg->getData()->getData();
    // initial
    enable_response.trans_id = data[0];
    enable_response.response = EMBMS_GENERAL_FAIL;  // default fail
    type = data[1];
    logI(LOG_TAG, "[requestLocalEmbmsEnable]:%d, r_trans_id:%d", type, enable_response.trans_id);

    sendEvent(RFX_MSG_EVENT_EMBMS_INITIAL_VARIABLE, RfxVoidData(), RIL_CMD_PROXY_URC,
        msg->getSlotId());

    memset(&g_active_session, 0xff, sizeof(RIL_EMBMS_LocalSessionNotify));
    memset(&g_available_session, 0xff, sizeof(RIL_EMBMS_LocalSessionNotify));

    // setNetworkInterface to ccmni7
    configureEmbmsNetworkInterface(EMBMS_IFACE_ID - 1, enable);

    enable_response.interface_index_valid = 0;  // interface_index_valid

    // get interface index

    int result = sprintf(enable_response.interface_name, "%s%d", CCMNI_IFNAME_CCMNI, EMBMS_IFACE_ID - 1);
    if (result < 0) {
        logE(LOG_TAG, "sprintf fail for enable_response.interface_name");
    }
    logI(LOG_TAG, "response.interface_name:%s", enable_response.interface_name);
    int if_index;
    ifc_init();
    if (ifc_get_ifindex(enable_response.interface_name, &if_index)) {
        logE(LOG_TAG, "cannot obtain interface index");
        if_index = -1;
    }
    ifc_close();

    if (if_index != -1) {
        enable_response.interface_index_valid = 1;
        enable_response.interface_index = if_index;
        logD(LOG_TAG, "if_index:%d", if_index);
    } else {
        goto error;
    }

    // Prevent duplicated bind, force unbind if already binded
    p_response = atSendCommand(String8::format("AT+EMBIND=0,\"M-LHIF\",%d", EMBMS_IFACE_ID));
    err = p_response->getError();

    // Real bind
    p_response = atSendCommand(String8::format("AT+EMBIND=%d,\"M-LHIF\",%d",
        enable, EMBMS_IFACE_ID));
    err = p_response->getError();
    if (err != 0 || p_response->getSuccess() == 0) {
        logE(LOG_TAG, "AT+EMBIND=%d Fail", enable);
        goto error;
    }


    // enable eMBMS Service
    p_response = atSendCommand(String8::format("AT+EMSEN=%d", enable));
    err = p_response->getError();
    if (err != 0 || p_response->getSuccess() == 0) {
        logE(LOG_TAG, "AT+EMSEN=%d Fail", enable);
        goto error;
    }

    // priority
    if(type == EMBMS_COMMAND_RIL || !isAtCmdEnableSupport()) {
        p_response = atSendCommand("AT+EMPRI=1");
        err = p_response->getError();
        if (err != 0 || p_response->getSuccess() == 0) {
            logE(LOG_TAG, "AT+EMPRI=%d Fail", enable);
            goto error;
        }
    }

    // Set tmgi serch timer to 8s
    // +EMSESSCFG=<index>,<para_1>
    // index: 1: TMGI search timer
    // <para_1>: TMGI search time (second)
    atSendCommand("AT+EMSESSCFG=1,8");

    // Enable unsolicited indication.
    if (type == EMBMS_COMMAND_RIL) {
        atSendCommand("AT+EMSRV=1");
        // Enable session list update unsolicited event
        atSendCommand("AT+EMSLU=1");
        // Enable SAI list unsolicited event
        atSendCommand("AT+EMSAIL=1");
    }

    p_response = atSendCommandSingleline("AT+EGREG?", "+EGREG:");
    err = p_response->getError();
    // +EGREG: <n>,<stat>[,[<lac>],[<ci>],[<eAcT>],[<rac>],
    // [<nwk_existence>],[<roam_indicator>][,<cause_type>,<reject_cause>]]
    //  <n> = 1, +EGREG: <stat>
    //  <n> = 2, +EGREG: <n>,<stat>[,[<lac>],[<ci>],[<eAcT>],[<rac>],
    //              [<nwk_existence>],[<roam_indicator>][,<cause_type>,<reject_cause>]]
    //  <n> = 3, +EGREG: <n>,<stat>[,[<lac>],[<ci>],[<eAcT>],[<rac>][,<cause_type>,<reject_cause>]]

    if (err != 0 || p_response->getSuccess() == 0 ||
            p_response->getIntermediates() == NULL) goto error;

    line = p_response->getIntermediates();
    if (!parseCellId(line, &status, &cell_id)) {
        cell_id = 0;
    }

    p_response = atSendCommandSingleline("AT+EOPS?", "+EOPS:");
    err = p_response->getError();
    if (err != 0 || p_response->getSuccess() == 0 ||
            p_response->getIntermediates() == NULL) {
        goto error;
    }

    line = p_response->getIntermediates();
    line->atTokStart(&err);
    if (err < 0) goto error;

    /* <mode> */
    skip = line->atTokNextint(&err);
    if (err < 0 || skip < 0 || skip > 4) {
        logE(LOG_TAG, "The <mode> is an invalid value!!!");
        goto error;
    } else if (skip == 2) {  // deregister
        logW(LOG_TAG, "The <mode> is 2 so we ignore the follwoing fields!!!");
    } else if (line->atTokHasmore()) {
        /* <format> */
        skip = line->atTokNextint(&err);
        if (err < 0 || skip != 2) {
            logW(LOG_TAG, "The <format> is incorrect: expect 2, receive %d", skip);
            goto error;
        }
        // a "+COPS: 0, n" response is also possible
        if (line->atTokHasmore()) {
            /* <oper> */
            plmn = line->atTokNextstr(&err);
            if (err < 0) goto error;

            logD(LOG_TAG, "Get operator code: %s", plmn);
        }
    }
    if (cell_id != 0x0fffffff && plmn != NULL && strlen(plmn) > 0) {
        intdata[0] = cell_id;
        intdata[1] = status;
        intdata[2] = (plmn == NULL)? 0:atoi(plmn);
        urc_response = RfxMclMessage::obtainUrc(RFX_MSG_URC_EMBMS_CELL_INFO_NOTIFICATION,
            msg->getSlotId(), RfxIntsData(intdata, 3));
        responseToTelCore(urc_response);
    }

    // OK / ERROR
    enable_response.response = EMBMS_GENERAL_SUCCESS;

    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxEmbmsLocalEnableRespData(&enable_response, sizeof(enable_response)), msg, false);

    // response to TeleCore
    responseToTelCore(response);
    return;

error:
    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxEmbmsLocalEnableRespData(&enable_response, sizeof(enable_response)), msg, false);

    // response to TeleCore
    responseToTelCore(response);
}

/* For setting IFF_UP: ril_data_setflags(s, &ifr, IFF_UP, 0) */
/* For setting IFF_DOWN: ril_data_setflags(s, &ifr, 0, IFF_UP) */
void RmmEmbmsRequestHandler::ril_data_setflags(int s, struct ifreq *ifr, int set, int clr)
{
    int ret = 0;
    char *flag = NULL;

    ret = ioctl(s, SIOCGIFFLAGS, ifr);
    asprintf(&flag, "SIOCGIFFLAGS");
    if (ret < 0) {
        goto terminate;
    } else {
        free(flag);
    }

    ifr->ifr_flags = (ifr->ifr_flags & (~clr)) | set;
    ret = ioctl(s, SIOCSIFFLAGS, ifr);
    asprintf(&flag, "SIOCSIFFLAGS");
    if (ret < 0) {
        goto terminate;
    } else {
        free(flag);
    }

    return;
terminate:
    logE(LOG_TAG, "ril_data_setflags: error in set %s:%d - %d:%s", flag, ret, errno, strerror(errno));
    free(flag);
    return;
}

void RmmEmbmsRequestHandler::ril_embms_ioctl_init() {
    if (RmmEmbmsRequestHandler::embms_sock_fd > 0)
        close(RmmEmbmsRequestHandler::embms_sock_fd);

    RmmEmbmsRequestHandler::embms_sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

    if (RmmEmbmsRequestHandler::embms_sock_fd < 0)
        logE(LOG_TAG, "Couldn't create IP socket: errno=%d", errno);
    else
        logD(LOG_TAG, "Allocate embms_sock_fd=%d", RmmEmbmsRequestHandler::embms_sock_fd);

    if (RmmEmbmsRequestHandler::embms_sock6_fd > 0)
        close(RmmEmbmsRequestHandler::embms_sock6_fd);

    RmmEmbmsRequestHandler::embms_sock6_fd = socket(AF_INET6, SOCK_DGRAM, 0);

    if (RmmEmbmsRequestHandler::embms_sock6_fd < 0) {
        RmmEmbmsRequestHandler::embms_sock6_fd = -errno;    /* save errno for later */
        logE(LOG_TAG, "Couldn't create IPv6 socket: errno=%d", errno);
    } else {
        logD(LOG_TAG, "Allocate embms_sock6_fd=%d", RmmEmbmsRequestHandler::embms_sock6_fd);
    }
}

void RmmEmbmsRequestHandler::setNwIntfDown(const char * pzIfName) {
    logV(LOG_TAG, "setNwIntfDown %s", pzIfName);
    ifc_reset_connections(pzIfName, RESET_ALL_ADDRESSES);
    ifc_remove_default_route(pzIfName);
    ifc_disable(pzIfName);
}

void RmmEmbmsRequestHandler::configureEmbmsNetworkInterface(int interfaceId, int isUp) {
    struct ifreq ifr;

    logI(LOG_TAG, "configureNetworkInterface interface %d to %s", interfaceId, isUp ? "UP" : "DOWN");
    memset(&ifr, 0, sizeof(struct ifreq));
    int result = sprintf(ifr.ifr_name, "%s%d", CCMNI_IFNAME_CCMNI, EMBMS_IFACE_ID - 1);
    if (result < 0) {
        logE(LOG_TAG, "sprintf fail for ifr.ifr_name");
    }

    if (isUp) {
        logV(LOG_TAG, "set network interface down before up");
        setNwIntfDown(ifr.ifr_name);
    }

    ril_embms_ioctl_init();

    if (isUp) {
        ril_data_setflags(RmmEmbmsRequestHandler::embms_sock_fd, &ifr, IFF_UP, 0);
        ril_data_setflags(RmmEmbmsRequestHandler::embms_sock6_fd, &ifr, IFF_UP, 0);
    } else {
        setNwIntfDown(ifr.ifr_name);
    }

    close(RmmEmbmsRequestHandler::embms_sock_fd);
    close(RmmEmbmsRequestHandler::embms_sock6_fd);
    RmmEmbmsRequestHandler::embms_sock_fd = 0;
    RmmEmbmsRequestHandler::embms_sock6_fd = 0;
}

void RmmEmbmsRequestHandler::requestLocalEmbmsDisable(const sp<RfxMclMessage>& msg) {
    const int enable = 0;

    String8 cmd("");
    sp<RfxAtResponse> p_response;
    RIL_EMBMS_DisableResp disable_response;
    int type;
    sp<RfxMclMessage> response;

    int *data = (int *)msg->getData()->getData();
    // initial
    disable_response.trans_id = data[0];
    disable_response.response = EMBMS_GENERAL_FAIL;  // default fail
    type = data[1];
    logI(LOG_TAG, "[requestLocalEmbmsDisable]:%d, r_trans_id:%d", type, disable_response.trans_id);

    sendEvent(RFX_MSG_EVENT_EMBMS_INITIAL_VARIABLE, RfxVoidData(), RIL_CMD_PROXY_URC,
        msg->getSlotId());

    memset(&g_active_session, 0xff, sizeof(RIL_EMBMS_LocalSessionNotify));
    memset(&g_available_session, 0xff, sizeof(RIL_EMBMS_LocalSessionNotify));

    // setNetworkInterface to ccmni7
    configureEmbmsNetworkInterface(EMBMS_IFACE_ID -1 , enable);

    RIL_Errno rilErrNo = RIL_E_SUCCESS;
    String8 val = String8::format("AT+EMBIND=%d,\"M-LHIF\",%d", enable, EMBMS_IFACE_ID);
    char arr_embind[strlen(val) + 1];  // Make sure there's enough space
    strcpy(arr_embind, val);

    val = String8::format("AT+EMSEN=%d", enable);
    char arr_emsen[strlen(val) + 1];  // Make sure there's enough space
    strcpy(arr_emsen, val);

    val = String8::format("AT+EMPRI=%d", enable);
    char arr_empri[strlen(val) + 1];  // Make sure there's enough space
    strcpy(arr_empri, val);


    sp<RfxMipcData> initMipc = RfxMipcData::obtainMipcData(MIPC_SYS_AT_REQ, m_slot_id);
    initMipc->addMipcTlvStr(MIPC_SYS_AT_REQ_T_ATCMD, arr_embind);
    sp<RfxMipcData> rsp_data = callToMipcMsgSync(initMipc);

    logD(LOG_TAG, "Status, AT+EMBIND ,result: %d",rsp_data->getResult());
    if (MIPC_RESULT_SUCCESS != rsp_data->getResult()){
        rilErrNo = RIL_E_GENERIC_FAILURE;
        goto error;
    }

    // enable eMbms Service
    initMipc = RfxMipcData::obtainMipcData(MIPC_SYS_AT_REQ, m_slot_id);
    initMipc->addMipcTlvStr(MIPC_SYS_AT_REQ_T_ATCMD, arr_emsen);
    rsp_data = callToMipcMsgSync(initMipc);
    logD(LOG_TAG, "Status,AT+EMSEN ,result: %d",rsp_data->getResult());
    if(MIPC_RESULT_SUCCESS != rsp_data->getResult()){
        rilErrNo = RIL_E_GENERIC_FAILURE;
        goto error;
    }

    // priority
    initMipc = RfxMipcData::obtainMipcData(MIPC_SYS_AT_REQ, m_slot_id);
    initMipc->addMipcTlvStr(MIPC_SYS_AT_REQ_T_ATCMD, arr_empri);
    rsp_data = callToMipcMsgSync(initMipc);
    logD(LOG_TAG, "Status, AT+EMPRI ,result: %d",rsp_data->getResult());
    if(MIPC_RESULT_SUCCESS != rsp_data->getResult()){
        rilErrNo = RIL_E_GENERIC_FAILURE;
        goto error;
    }
    // Ignore all URC since service already disabled

    // OK / ERROR
    disable_response.response = EMBMS_GENERAL_SUCCESS;
    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxEmbmsDisableRespData(&disable_response, sizeof(disable_response)), msg, false);

    // response to TeleCore
    responseToTelCore(response);
    return;

error:
    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxEmbmsDisableRespData(&disable_response, sizeof(disable_response)), msg, false);

    // response to TeleCore
    responseToTelCore(response);
}

void RmmEmbmsRequestHandler::requestLocalEmbmsStartSession(const sp<RfxMclMessage>& msg) {
    String8 cmd("");
    String8 cmdline("");
    sp<RfxAtResponse> p_response;


    uint32_t i;
    sp<RfxMclMessage> response;

    logI(LOG_TAG, "[requestLocalEmbmsStartSession]");
    RIL_EMBMS_LocalStartSessionReq* request = (RIL_EMBMS_LocalStartSessionReq*)
                                                msg->getData()->getData();

    RIL_EMBMS_LocalStartSessionResp response_data;

    // initial
    memset(&response_data, 0, sizeof(response_data));
    response_data.trans_id = request->trans_id;
    logD(LOG_TAG, "trans_id:%d, tmgi:%s", response_data.trans_id, request->tmgi);
    response_data.response = EMBMS_SESSION_UNKNOWN_ERROR;

    // AT+EMSESS=<act>,<tmgi>[,[<session_id>][,[<area_id>][,<num_sais>,[sai_1>[,<sai_2>[K]]]
    //  [,<num_freq>,<freq_1>[,<freq_2>[K]]]]]]

    //  session_id
    if (request->saiList_count > 0 || request->earfcnlist_count > 0 || request->session_id > 0) {
        cmdline.append(String8(","));

    }
    if (request->session_id > 0) {  // !=INVALID_EMBMS_SESSION_ID
        cmdline.append(String8::format("\"%02X\"", request->session_id));
    }

    if (request->saiList_count > 0 || request->earfcnlist_count > 0) {
        // area_id, not support
        cmdline.append(String8(","));

        // num_sais
        if (request->saiList_count > EMBMS_MAX_NUM_SAI) {
            request->saiList_count = EMBMS_MAX_NUM_SAI;
        }
        cmdline.append(String8::format(",%d", request->saiList_count));

        // sai_y
        for (i = 0; i < request->saiList_count; i++) {
            cmdline.append(String8::format(",%d", request->saiList[i]));
        }

        // num_freq
        if (request->earfcnlist_count > EMBMS_MAX_NUM_FREQ) {
            request->earfcnlist_count = EMBMS_MAX_NUM_FREQ;
        }
        cmdline.append(String8::format(",%d", request->earfcnlist_count));

        for (i = 0; i < request->earfcnlist_count; i++) {
            cmdline.append(String8::format(",%d", request->earfcnlist[i]));
        }
    }

    String8 val = String8::format("AT+EMSESS=1,\"%s\"%s", request->tmgi, cmdline.string());
    char arr_emsess[strlen(val) + 1];  // Make sure there's enough space
    strcpy(arr_emsess, val);
    RIL_Errno rilErrNo = RIL_E_SUCCESS;

    sp<RfxMipcData> initMipc = RfxMipcData::obtainMipcData(MIPC_SYS_AT_REQ, m_slot_id);
    initMipc->addMipcTlvStr(MIPC_SYS_AT_REQ_T_ATCMD, arr_emsess);
    sp<RfxMipcData> rsp_data = callToMipcMsgSync(initMipc);
    logD(LOG_TAG, "Local Embms Session Start Status, AT+EMSESS ,result: %d",rsp_data->getResult());
    if(MIPC_RESULT_SUCCESS != rsp_data->getResult()){
        rilErrNo = RIL_E_GENERIC_FAILURE;
        goto error;
    }
    response_data.response = EMBMS_SESSION_SUCCESS;
    response_data.tmgi_info_valid = 1;
    strncpy(response_data.tmgi, request->tmgi, EMBMS_MAX_LEN_TMGI);

    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxEmbmsLocalStartSessionRespData(&response_data,
                sizeof(response_data)), msg, false);

    // response to TeleCore
    responseToTelCore(response);
    return;

error:
    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxEmbmsLocalStartSessionRespData(&response_data,
                sizeof(response_data)), msg, false);

    // response to TeleCore
    responseToTelCore(response);
}

int RmmEmbmsRequestHandler::isTmgiEmpty(char * tmgi) {
    if (tmgi == NULL) {
        return true;
    }
    return(strlen(tmgi) == 0);
}

void RmmEmbmsRequestHandler::requestLocalEmbmsStopSession(const sp<RfxMclMessage>& msg) {
    sp<RfxAtResponse> p_response;
    int err = 0;
    String8 cmd("");
    String8 cmdline("");
    char* tmpBuffer;
    sp<RfxMclMessage> response;

    logI(LOG_TAG, "[requestLocalEmbmsStopSession]");

    RIL_EMBMS_LocalStopSessionReq* request = (RIL_EMBMS_LocalStopSessionReq*)
                                                msg->getData()->getData();
    RIL_EMBMS_LocalStartSessionResp response_data;

    // initial
    memset(&response_data, 0, sizeof(response_data));
    response_data.trans_id = request->trans_id;
    logD(LOG_TAG, "trans_id:%d, tmgi:%s", response_data.trans_id, request->tmgi);
    response_data.response = EMBMS_SESSION_UNKNOWN_ERROR;
    int active_num_sessions = 0;
    char* tmgi;
    char current_session_tmgis[EMBMS_MAX_NUM_EMSLUI][EMBMS_MAX_LEN_TMGI + 1];
  sp<RfxMipcData> initMipc;
  sp<RfxMipcData> rsp_data;
    // AT+EMSESS=<act>,<tmgi>[,[<session_id>][,[<area_id>][,<num_sais>,[sai_1>[,<sai_2>[K]]]
    // [,<num_freq>,<freq_1>[,<freq_2>[K]]]]]]
    if (request->stop_type == EMBMS_DEACTIVE_ALL_SESSION) {
        int current_enabled = 0;
        int num_sessions = -1;
        int skip, i = 0;
        uint16_t index = 0;
        char* session_id;
        uint8_t status;
        RfxAtLine* line;
        memset(current_session_tmgis, 0, sizeof(current_session_tmgis));


    RIL_Errno rilErrNo = RIL_E_SUCCESS;
    char atcmd[] = "AT+EMSLU?";
    initMipc = RfxMipcData::obtainMipcData(MIPC_EMBMS_EMSLU_REQ, m_slot_id);
    initMipc->addMipcTlvStr(mipc_embms_emslu_req_tlv_NONE, atcmd);
    rsp_data = callToMipcMsgSync(initMipc);
    logD(LOG_TAG, "ession Info Status, AT+EMEVT? ,result: %d",rsp_data->getResult());
    if(MIPC_RESULT_SUCCESS != rsp_data->getResult()){
        rilErrNo = RIL_E_GENERIC_FAILURE;
        goto error;
    }
    uint16_t val_len = 0;
    mipc_embms_session_info_struct4 *session_info =
        (mipc_embms_session_info_struct4*) rsp_data->getMipcVal(MIPC_EMBMS_EMSLU_CNF_T_SESSION_LIST, &val_len);
    uint8_t *enable_status = (uint8_t*) rsp_data->getMipcVal(MIPC_EMBMS_EMSLU_CNF_T_IS_ENABLED, &val_len);
    uint16_t *session_count = (uint16_t*) rsp_data->getMipcVal(MIPC_EMBMS_EMSLU_CNF_T_SESSION_COUNT, &val_len);

if(num_sessions == -1){
num_sessions = *session_count;
index = 0;
}
   if (index < num_sessions) {
                //  <x>
                skip = session_info->index;
                //  x should be index+1
                if (skip != (index + 1)) {
                    logE(LOG_TAG, "Error! x(%d)!=index(%d)+1.", skip, index);
                    goto error;
                }
                //  <tmgix>
                tmpBuffer = session_info->tmgi;
                //  session_id
                session_id = session_info->session_id;
                //  status
                status = session_info->status;


                logV(LOG_TAG, "tmpBuffer = %s, status =%d", tmpBuffer, status);
                if (status) {
                    strlcpy(current_session_tmgis[active_num_sessions], tmpBuffer, EMBMS_MAX_LEN_TMGI);
                    active_num_sessions++;
                }
                index++;
            }
    for (int i = 0; i < active_num_sessions; i++) {
         tmgi = current_session_tmgis[i];

    if (!isTmgiEmpty(tmgi)) {
        RIL_Errno rilErrNo = RIL_E_SUCCESS;
        String8 val = String8::format("AT+EMSESS=0,\"%s\"", tmgi);
        char arr_emsess[strlen(val) + 1];  // Make sure there's enough space
        strcpy(arr_emsess, val);
        initMipc = RfxMipcData::obtainMipcData(MIPC_SYS_AT_REQ, m_slot_id);
        initMipc->addMipcTlvStr(MIPC_SYS_AT_REQ_T_ATCMD, arr_emsess);
        rsp_data = callToMipcMsgSync(initMipc);
        logD(LOG_TAG, "Session Disable status,AT+EMSESS ,result: %d",
        rsp_data->getResult());
        if(MIPC_RESULT_SUCCESS != rsp_data->getResult()){
            rilErrNo = RIL_E_GENERIC_FAILURE;
            goto error;
        }
    }
}

        response_data.response = EMBMS_SESSION_SUCCESS;
        response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
                RfxEmbmsLocalStartSessionRespData(&response_data,
                    sizeof(response_data)), msg, false);

        // response to TeleCore
        responseToTelCore(response);
        return;

    } else {  // EMBMS_DEACTIVE_SESSION
        if (request->session_id > 0) {  // !=INVALID_EMBMS_SESSION_ID
            cmdline.append(String8(","));
            cmdline.append(String8::format("\"%02X\"", request->session_id));
        }
        cmd = String8::format("AT+EMSESS=0,\"%s\"%s", request->tmgi, cmdline.string());
        p_response = atSendCommand(cmd);
        err = p_response->getError();
        if (err < 0 || p_response->getSuccess() == 0) {
            goto error;
        }

        response_data.response = EMBMS_SESSION_SUCCESS;
        response_data.tmgi_info_valid = 1;
        strncpy(response_data.tmgi, request->tmgi, EMBMS_MAX_LEN_TMGI);

        response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
                RfxEmbmsLocalStartSessionRespData(&response_data,
                    sizeof(response_data)), msg, false);

        // response to TeleCore
        responseToTelCore(response);
        return;
    }

error:
        response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
                RfxEmbmsLocalStartSessionRespData(&response_data,
                    sizeof(response_data)), msg, false);

        // response to TeleCore
        responseToTelCore(response);
}

//  Parse SAIs list
bool RmmEmbmsRequestHandler::parseSIB16Time(sp<RfxAtResponse> p_response,
    RIL_EMBMS_GetTimeResp* time_response) {
    RfxAtLine* line;
    uint64_t utc_time;
    int err = 0;
    int tmp = 0;

    line = p_response->getIntermediates();
    line->atTokStart(&err);
    if (err < 0) goto error;

    // <dst>
    time_response->day_light_saving = 0;
    tmp = line->atTokNextint(&err);
    if (err < 0) goto error;
    // notice day_light_saving is uint8 can't save minus number. tmp is int.
    if (tmp >= 0) {
        time_response->day_light_saving_valid = 1;
        time_response->day_light_saving = tmp;
    }

    // <ls>
    tmp = line->atTokNextint(&err);
    time_response->leap_seconds = tmp;
    if (err < 0) goto error;
    time_response->leap_seconds_valid = 1;

    // <lto>
    tmp = line->atTokNextint(&err);
    time_response->local_time_offset = tmp;
    time_response->local_time_offset_valid = 1;
    if (err < 0) goto error;

    // <ut>
    utc_time = line->atTokNextlonglong(&err);
    if (err < 0) goto error;

    // Integer value represented as number 10ms units
    // since 00:00:00 on Gregorian calendar date 1 January 1900
    logD(LOG_TAG, "utc time before modify:%lu", utc_time);
    utc_time = utc_time * 10;  // Convert to milliseconds
    time_response->milli_sec = utc_time;
    logV(LOG_TAG, "parseSIB16Time success.");
    return true;
error:
    logE(LOG_TAG, "parseSIB16Time error!!");
    return false;
}

//  Parse NITZ list
bool RmmEmbmsRequestHandler::parseNitzTime(sp<RfxAtResponse> p_response,
    RIL_EMBMS_GetTimeResp* time_response) {
    // +EMTSI: 2[,[<dst>],<lto>,<year>,<month>,<day>,<hour>,<min>,<sec>]
    RfxAtLine* line;
    int err = 0;
    int type = 0;
    int tmp = 0;
    struct tm m_time;
    memset(&m_time, 0, sizeof(m_time));

    line = p_response->getIntermediates();
    line->atTokStart(&err);
    if (err < 0) goto error;

    // type
    type = line->atTokNextint(&err);
    if (err < 0) goto error;
    if (type != 2) goto error;

    // <dst>
    time_response->day_light_saving = 0;
    tmp = line->atTokNextint(&err);
    if (err < 0) goto error;
    if (tmp >= 0) {
        time_response->day_light_saving_valid = 1;
        time_response->day_light_saving = tmp;
    }

    // <lto>
    tmp = line->atTokNextint(&err);
    time_response->local_time_offset = tmp;
    if (err < 0) goto error;
    time_response->local_time_offset = time_response->local_time_offset / 4;
    time_response->local_time_offset_valid = 1;

    // <year> 2000-2999
    tmp = line->atTokNextint(&err);
    if (err < 0) goto error;
    // Since 1900
    m_time.tm_year = tmp - 1900;

    // <month> 1-12
    tmp = line->atTokNextint(&err);
    if (err < 0) goto error;
    // 0-11
    m_time.tm_mon = tmp - 1;

    // <day> 1-31
    tmp = line->atTokNextint(&err);
    if (err < 0) goto error;
    // 1-31
    m_time.tm_mday = tmp;

    // <hour> 0-23
    tmp = line->atTokNextint(&err);
    if (err < 0) goto error;
    // 0-23
    m_time.tm_hour = tmp;

    // <min> 0-59
    tmp = line->atTokNextint(&err);
    if (err < 0) goto error;
    // 0-59
    m_time.tm_min = tmp;

    // <sec> 0-59
    tmp = line->atTokNextint(&err);
    if (err < 0) goto error;
    // 0-59
    m_time.tm_sec = tmp;

    // negative if the information is not available
    m_time.tm_isdst = -1;

    // Convert to UTC second since Epoch, then convert to milli second
    time_response->milli_sec = timegm(&m_time) * 1000LL;
    logD(LOG_TAG, "Nitz time:%lu", time_response->milli_sec);
    logV(LOG_TAG, "parseNitzTime success.");
    return true;
error:
    logE(LOG_TAG, "parseNitzTime error!!");
    return false;
}

void RmmEmbmsRequestHandler::requestLocalEmbmsGetNetworkTime(const sp<RfxMclMessage>& msg) {
    sp<RfxAtResponse> p_response;
    int err = 0;
    RIL_EMBMS_GetTimeResp time_response;
    sp<RfxMclMessage> response;
    int *data = (int *)msg->getData()->getData();

    logI(LOG_TAG, "[requestLocalEmbmsGetNetworkTime]");

    // initial
    memset(&time_response, 0, sizeof(time_response));
    time_response.trans_id = data[0];
    logV(LOG_TAG, "trans_id:%d", time_response.trans_id);
    time_response.response = EMBMS_GET_TIME_ERROR;
    time_response.day_light_saving = 0;

    p_response = atSendCommandSingleline("AT+EMTSI", "+EMTSI:");
    err = p_response->getError();
    // +EMTSI: <dst>,<ls>,<lto>,<ut>
    if (err < 0 || p_response->getSuccess() == 0 ||
            p_response->getIntermediates()  == NULL) {
        time_response.response = EMBMS_GET_TIME_ERROR;
    } else if (parseSIB16Time(p_response, &time_response)) {
        time_response.response = EMBMS_GET_TIME_SIB16;
    } else {
        time_response.response = EMBMS_GET_TIME_ERROR;
    }

    // If Get SIB16 Fail then try to get Nitz
    if (time_response.response == EMBMS_GET_TIME_ERROR) {
        memset(&time_response, 0, sizeof(time_response));
        // Try to get NITZ time
        p_response = atSendCommandSingleline("AT+EMTSI=2", "+EMTSI:");
        err = p_response->getError();
        if (err < 0 || p_response->getSuccess() == 0 ||
                p_response->getIntermediates()  == NULL) {
            time_response.response = EMBMS_GET_TIME_ERROR;
        } else if (parseNitzTime(p_response, &time_response)) {
            time_response.response = EMBMS_GET_TIME_NITZ;
        } else {
            time_response.response = EMBMS_GET_TIME_ERROR;
        }
    }

    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxEmbmsGetTimeRespData(&time_response, sizeof(time_response)), msg, false);

    // response to TeleCore
    responseToTelCore(response);
    return;
}

void RmmEmbmsRequestHandler::requestLocalEmbmsSetCoverageStatus(const sp<RfxMclMessage>& msg) {
    sp<RfxAtResponse> p_response;
    int err = 0;
    int *data = (int *)msg->getData()->getData();
    int scenario = data[0];
    int status = data[1];
    sp<RfxMclMessage> response;

    logI(LOG_TAG, "requestEmbmsSetCoverageStatus:<%d,%d>", scenario, status);
    // AT+EMEVT=<scenario>, <status>
    // <scenario> 1: E911,2: hVoLTE
    // <status> 1: The beginning of the scenario, 0: The end of the scenario

    RIL_Errno rilErrNo = RIL_E_SUCCESS;

    String8 val = String8::format("AT+EMEVT=%d,%d", scenario, status);
    char atcmd[strlen(val) + 1];  // Make sure there's enough space
    strcpy(atcmd, val);
    sp<RfxMipcData> initMipc = RfxMipcData::obtainMipcData(MIPC_SYS_AT_REQ, m_slot_id);
    initMipc->addMipcTlvStr(MIPC_SYS_AT_REQ_T_ATCMD, atcmd);
    sp<RfxMipcData> rsp_data = callToMipcMsgSync(initMipc);

    logD(LOG_TAG, "Set Coverage Status, AT+EMEVT? ,result: %d",
            rsp_data->getResult());
    if(MIPC_RESULT_SUCCESS != rsp_data->getResult()){
        rilErrNo = RIL_E_GENERIC_FAILURE;
        goto error;
    }

    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxVoidData(), msg, false);
    // response to TeleCore
    responseToTelCore(response);
    return;
error:
    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_GENERIC_FAILURE,
            RfxVoidData(), msg, false);
    // response to TeleCore
    responseToTelCore(response);
}

void RmmEmbmsRequestHandler::requestEmbmsGetCoverageStatus(const sp<RfxMclMessage>& msg) {
    int err = 0;
    sp<RfxAtResponse> p_response;
    RIL_EMBMS_GetCoverageResp coverage_response;
    RfxAtLine* line;
    int is_enabled, srv_status;
    sp<RfxMclMessage> response;

    logI(LOG_TAG, "[requestEmbmsGetCoverageStatus]:");

    int *data = (int *)msg->getData()->getData();

    // initial
    coverage_response.trans_id = data[0];
    logV(LOG_TAG, "trans_id:%d", coverage_response.trans_id);
    coverage_response.response = EMBMS_GENERAL_FAIL;  // default fail
    coverage_response.coverage_state_valid = 0;

    p_response = atSendCommandSingleline("AT+EMSRV?", "+EMSRV:");
    err = p_response->getError();
    if (err != 0 || p_response->getSuccess() == 0) {
        logE(LOG_TAG, "AT+EMSRV? Fail");
        goto error;
    }

    line = p_response->getIntermediates();
    // +EMSRV: <enable>,<srv>,<num_area_ids>,<area_id1>[,area_id2>[...]]
    // OK
    line->atTokStart(&err);
    if (err < 0) goto error;

    // <enable>
    is_enabled = line->atTokNextint(&err);
    if (err < 0) goto error;

    // <srv>
    // 0: No service, 1:only unicast available,
    // 2: in eMBMS supporting area 3:e911 4:hVolte 5:flight mode
    srv_status = line->atTokNextint(&err);
    if (err < 0) goto error;

    // send OK response
    coverage_response.response = EMBMS_GENERAL_SUCCESS;
    coverage_response.coverage_state_valid = 1;
    // Let ril-proxy do the value transform
    coverage_response.coverage_state = srv_status;
    // 0: No service, 1:only unicast available, 2:in eMBMS supporting area 3:e911 4:hVolte 5:flight mode

    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxEmbmsGetCoverageRespData(&coverage_response, sizeof(coverage_response)), msg, false);

    // response to TeleCore
    responseToTelCore(response);
    return;
error:
    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxEmbmsGetCoverageRespData(&coverage_response, sizeof(coverage_response)), msg, false);

    // response to TeleCore
    responseToTelCore(response);
}

void RmmEmbmsRequestHandler::requestLocalTriggerCellInfoNotify(const sp<RfxMclMessage>& msg) {
    int err = 0;
    sp<RfxAtResponse> p_response;
    sp<RfxMclMessage> response;
    sp<RfxMclMessage> urc_response;
    unsigned int cell_id = 0x0fffffff;
    RfxAtLine* line;

    int status = 0;


    String8 responseStr("");

    logI(LOG_TAG, "[requestLocalTriggerCellInfoNotify]");

    // Trigger a CEREG urc for default sim switch scenario under L+L.
    p_response = atSendCommandSingleline("AT+EGREG?", "+EGREG:");
    err = p_response->getError();

    if (err != 0 || p_response->getSuccess() == 0 ||
            p_response->getIntermediates() == NULL) goto error;

    line = p_response->getIntermediates();
    if (!parseCellId(line, &status, &cell_id)) {
        cell_id = 0;
    }

    responseStr = String8::format("+CEREG:%d\n", status);
    urc_response = RfxMclMessage::obtainUrc(RFX_MSG_URC_EMBMS_AT_INFO,
        msg->getSlotId(), RfxStringData((void *)responseStr.string(), responseStr.length()));
    responseToTelCore(urc_response);

    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxVoidData(), msg, false);

    // response to TeleCore
    responseToTelCore(response);
    return;

error:
    response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxVoidData(), msg, false);

    // response to TeleCore
    responseToTelCore(response);
}

// Debug usage
void RmmEmbmsRequestHandler::forceEnableMdEmbms(const sp<RfxMclMessage>& msg) {
    sp<RfxAtResponse> p_response;

    RFX_UNUSED(msg);
    atSendCommand(String8("AT+ESBP=5,\"SBP_LTE_MBMS\",1"));
    atSendCommand(String8("AT+ESBP=5,\"SBP_LTE_MBMS_COUNTING\",1"));
    atSendCommand(String8("AT+ESBP=5,\"SBP_LTE_MBMS_SERVICE_CONTINUITY\",1"));
    atSendCommand(String8("AT+ESBP=5,\"SBP_LTE_MBMS_SCELL\",1"));
}
