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

// MTK fusion include
#include "RfxVoidData.h"
#include "RfxStringData.h"
#include "RfxStringsData.h"
#include "RfxIntsData.h"

// Local include
#include "RmcWifiRelayRequestHandler.h"
#include "RmcWifiRelayInterface.h"

#include <sys/socket.h>
#include <errno.h>

#define RFX_LOG_TAG "RmcWr"

 // register handler to channel
RFX_IMPLEMENT_HANDLER_CLASS(RmcWifiRelayRequestHandler, RIL_CMD_PROXY_1);

// register request to RfxData
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxStringsData, RfxVoidData, RFX_MSG_REQUEST_SEND_WIFI_ENABLED);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxStringsData, RfxVoidData, RFX_MSG_REQUEST_SEND_WIFI_ASSOCIATED);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxStringsData, RfxVoidData, RFX_MSG_REQUEST_SEND_WIFI_IP_ADDRESS);

static const int requests[] = {
    RFX_MSG_REQUEST_SEND_WIFI_ENABLED,
    RFX_MSG_REQUEST_SEND_WIFI_ASSOCIATED,
    RFX_MSG_REQUEST_SEND_WIFI_IP_ADDRESS,
};

RmcWifiRelayRequestHandler::RmcWifiRelayRequestHandler(
    int slot_id, int channel_id) : RfxBaseHandler(slot_id, channel_id) {
    // register to handle request
    registerToHandleRequest(requests, sizeof(requests) / sizeof(int));
}

RmcWifiRelayRequestHandler::~RmcWifiRelayRequestHandler() {
}

void RmcWifiRelayRequestHandler::onHandleTimer() {
}

void RmcWifiRelayRequestHandler::onHandleRequest(const sp<RfxMclMessage>& msg) {
    int requestId = msg->getId();

    switch (requestId) {
        case RFX_MSG_REQUEST_SEND_WIFI_ENABLED:
            sendWifiEnabled(msg);
            break;
        case RFX_MSG_REQUEST_SEND_WIFI_ASSOCIATED:
            sendWifiAssociated(msg);
            break;
        case RFX_MSG_REQUEST_SEND_WIFI_IP_ADDRESS:
            sendWifiIpAddress(msg);
            break;
        default:
            break;
    }
}

void RmcWifiRelayRequestHandler::sendWifiEnabled(const sp<RfxMclMessage>& msg) {
    /* AT+EWIFIEN=<ifname>,<enabled>
     * <ifname>: interface name, such as wlan0
     * <enabled>: 0 = disable; 1 = enable
     */
    char** params = (char**)msg->getData()->getData();
    int dataLen =  msg->getData()->getDataLength() / sizeof(char*);
    logD(RFX_LOG_TAG, "setWifiEnabled dataLen: %d", dataLen);

    char* atWifiEnCmd = AT_SEND_WIFI_ENABLE;
    char* ifname = params[0];
    int enabled = atoi(params[1]);

    String8 cmd = String8::format("%s=\"%s\",%d", atWifiEnCmd, ifname, enabled);
    handleCmdWithVoidResponse(msg, cmd);
}

void RmcWifiRelayRequestHandler::sendWifiAssociated(const sp<RfxMclMessage>& msg) {
    /* AT+EWIFIASC=<ifname>,<assoc>,<ssid>,<ap_mac>,<wifi_type>,<mtu>
     * <ifname>: interface name, such as wlan0
     * <assoc>: 0 = not associated; 1 = associated
     * <ssid>: wifi ap ssid when associated, 0 if assoc = 0
     * <ap_mac>: wifi ap mac addr, 0 if assoc = 0
     * <wifi_type>: wifi type: such as 802.11b, 802.11n...
     * <mtu>: mtu size
     */
    char** params = (char**)msg->getData()->getData();

    char* atCmd = AT_SEND_WIFI_ASSOCIATED;
    char* ifname = params[0]? params[0]: (char*)"" ;
    const char* assoc = params[1]? params[1]: (char*)"0" ;
    char* ssid = (atoi(assoc) == 0)? (char*)"0": params[2];
    char* ap_mac = (atoi(assoc) == 0)? (char*)"0": params[3];
    char* mtu = (atoi(assoc) == 0)? (char*)"0": params[4];
    char defaultWifiType[RFX_PROPERTY_VALUE_MAX] = { 0 };
    rfx_property_get("vendor.test.wifi.type", defaultWifiType, "802.11n");
    char* type = defaultWifiType;

    // TODO: Need to check modem generation before sync to trunk
    if (atoi(assoc) == 0) {
        type = (char*) "";
    } else {
        int ioctl_sock = socket(AF_INET, SOCK_DGRAM, 0);
        if (ioctl_sock >= 0) {
            struct iwreq wrq;
            struct priv_driver_cmd_t priv_cmd;
            int ret;

            memset(&priv_cmd,0x00,sizeof(priv_cmd));
            priv_cmd.used_len = strlen(priv_cmd.buf);
            priv_cmd.total_len = PRIV_CMD_SIZE;

            strncpy(wrq.ifr_name, "wlan0", (IFNAMSIZ - 1));
            wrq.u.data.pointer = &priv_cmd;
            wrq.u.data.length = strlen(priv_cmd.buf);
            wrq.u.data.flags = PRIV_CMD_GET_WIFI_TYPE;

            ret = ioctl(ioctl_sock, IOCTL_SET_STRUCT_FOR_EM, &wrq);
            if ((ret == 0) && (wrq.u.data.length > 1)) {
                //ALOGI("get wifi type ok: [%s]", wrq.u.data.pointer);
                logD(RFX_LOG_TAG, "get wifi type ok: [%s]", (char*)wrq.u.data.pointer);
                type = (char*) wrq.u.data.pointer;
            } else {
                //ALOGI("get wifi type fail: %d\n", ret);
                logD(RFX_LOG_TAG, "get wifi type fail: %d, len = %d", ret, wrq.u.data.length);
            }
            close(ioctl_sock);
        } else {
            logE(RFX_LOG_TAG, "setWifiAssociatedWithMtu() ioctl_sock = %d %s",
                    ioctl_sock, strerror(errno));
        }
    }

    String8 cmd = String8::format("%s=\"%s\",%s,\"%s\",\"%s\",\"%s\",%s",
                                   atCmd, ifname, assoc, ssid, ap_mac, type, mtu);
    handleCmdWithVoidResponse(msg, cmd);
}

void RmcWifiRelayRequestHandler::sendWifiIpAddress(const sp<RfxMclMessage>& msg) {
    /* AT+EWIFIADDR=<ifname>,<ipv4>,<ipv6>,<ipv4PrefixLen>,<ipv6PrefixLen>,
     *         <ipv4gateway>,<ipv6gateway>,<dns_count>, <dns_1>, <dns_2>,..., <dns_n>
     * <ifname>: interface name, such as wlan0
     * <ipv4>: IPV4 address
     * <ipv6>: IPV6 address
     * <ipv4PrefixLen>: IPV4 address prefix length
     * <ipv6PrefixLen>: IPV6 address prefix length
     * <ipv4gateway>: IPV4 gateway address
     * <ipv6gateway>: IPV6 gateway address
     * <dns_count>: dns server count
     * <dns_1>, <dns_2>,... <dns_n>: dns server addresses
     */
    char** params = (char**)msg->getData()->getData();

    char* atCmd = AT_SEND_WIFI_IP_ADDRESS;

    // Google HIDL service changes "" in java as null in cpp
    char* ifname = params[0]? params[0]: (char*)"" ;
    char* ipv4 = (params[1] == NULL) ? (char*)"" : params[1];
    char* ipv6 = (params[2] == NULL) ? (char*)"" : params[2];
    char* ipv4PrefixLen = (params[3] == NULL) ? (char*)"-1" : params[3];
    if (strncmp(ipv4PrefixLen,"-1", 2) == 0) ipv4PrefixLen = (char*)"";
    char* ipv6PrefixLen = (params[4] == NULL) ? (char*)"-1" : params[4];
    if (strncmp(ipv6PrefixLen,"-1", 2) == 0) ipv6PrefixLen = (char*)"";
    char* ipv4gateway = (params[5] == NULL) ? (char*)"" : params[5];
    char* ipv6gateway = (params[6] == NULL) ? (char*)"" : params[6];
    char* dnsCount = (params[7] == NULL) ? (char*)"0" : params[7];
    char* dnsAddresses = (params[8] == NULL) ? (char*)"" : params[8];

    String8 cmd = String8::format("%s=\"%s\",\"%s\",\"%s\",%s,%s,\"%s\",\"%s\",%s,%s",
            atCmd, ifname, ipv4, ipv6,
            ipv4PrefixLen, ipv6PrefixLen,
            ipv4gateway, ipv6gateway,
            dnsCount, dnsAddresses);
    handleCmdWithVoidResponse(msg, cmd);
}