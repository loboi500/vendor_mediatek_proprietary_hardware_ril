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

// MTK fusion include
#include "RfxVoidData.h"
#include "RfxStringsData.h"

// Local include
#include "RmmWifiRelayRequestHandler.h"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>

#define RFX_LOG_TAG "RmmWr"

 // register handler to channel
RFX_IMPLEMENT_HANDLER_CLASS(RmmWifiRelayRequestHandler, RIL_CMD_PROXY_1);

// register request to RfxData
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxStringsData, RfxVoidData, RFX_MSG_REQUEST_SEND_WIFI_ENABLED);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxStringsData, RfxVoidData, RFX_MSG_REQUEST_SEND_WIFI_ASSOCIATED);
RFX_REGISTER_DATA_TO_REQUEST_ID(RfxStringsData, RfxVoidData, RFX_MSG_REQUEST_SEND_WIFI_IP_ADDRESS);

static const int requests[] = {
    RFX_MSG_REQUEST_SEND_WIFI_ENABLED,
    RFX_MSG_REQUEST_SEND_WIFI_ASSOCIATED,
    RFX_MSG_REQUEST_SEND_WIFI_IP_ADDRESS,
};

RmmWifiRelayRequestHandler::RmmWifiRelayRequestHandler(
    int slot_id, int channel_id) : RfxBaseHandler(slot_id, channel_id) {
    // register to handle request
    registerToHandleRequest(requests, sizeof(requests) / sizeof(int));
}

RmmWifiRelayRequestHandler::~RmmWifiRelayRequestHandler() {
}

void RmmWifiRelayRequestHandler::onHandleTimer() {
}

void RmmWifiRelayRequestHandler::onHandleRequest(const sp<RfxMclMessage>& msg) {
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

void RmmWifiRelayRequestHandler::onHandleResponse(const sp<RfxMclMessage>& msg) {
    int request = msg->getId();
    logD(RFX_LOG_TAG, "onHandleResponse: %d", request);
}

void RmmWifiRelayRequestHandler::handleNtfCmdResponse(const sp<RfxMclMessage>& msg) {
    logD(RFX_LOG_TAG, "handleNtfResponse, msgId:%d", msg->getId());
    sp<RfxMclMessage> response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_SUCCESS,
            RfxVoidData(), msg, false);
    responseToTelCore(response);
}

void RmmWifiRelayRequestHandler::handleErrorResponse(const sp<RfxMclMessage>& msg) {
    logD(RFX_LOG_TAG, "handleErrorResponse, msgId:%d", msg->getId());
    sp<RfxMclMessage> response = RfxMclMessage::obtainResponse(msg->getId(), RIL_E_GENERIC_FAILURE,
            RfxVoidData(), msg, false);
    responseToTelCore(response);
}

void RmmWifiRelayRequestHandler::sendWifiEnabled(const sp<RfxMclMessage>& msg) {
    /* AT+EWIFIEN=<ifname>,<enabled>
     * <ifname>: interface name, such as wlan0
     * <enabled>: 0 = disable; 1 = enable
     */
    char** params = (char**)msg->getData()->getData();
    int dataLen =  msg->getData()->getDataLength() / sizeof(char*);
    logD(RFX_LOG_TAG, "sendWifiEnabled dataLen: %d", dataLen);
    char* ifname = params[0]? params[0]: (char*)"";
    char* enabled_str = params[1]? params[1]: (char*)"0";
    if (strlen(enabled_str) != 1) {
        logE(RFX_LOG_TAG, "sendWifiEnabled: enabled len error");
        handleErrorResponse(msg);
        return;
    }
    const uint8_t enabled = (uint8_t)atoi(enabled_str);

    sp<RfxMipcData> requestData = RfxMipcData::obtainMipcData(MIPC_WFC_WIFI_INFO_NTF, msg->getSlotId());
    requestData->addMipcTlvStr(MIPC_WFC_WIFI_INFO_NTF_T_IFNAME, ifname);
    requestData->addMipcTlvUint8(MIPC_WFC_WIFI_INFO_NTF_T_ENABLE, enabled);
    //send wifi setting value NTF
    int result = callToMipcMsgNtf(requestData);
    logD(RFX_LOG_TAG, "sendWifiEnabled result: %d", result);
    handleNtfCmdResponse(msg);
}

void RmmWifiRelayRequestHandler::sendWifiAssociated(const sp<RfxMclMessage>& msg) {
    /* AT+EWIFIASC=<ifname>,<assoc>,<ssid>,<ap_mac>,<wifi_type>,<mtu>
     * <ifname>: interface name, such as wlan0
     * <assoc>: 0 = not associated; 1 = associated
     * <ssid>: wifi ap ssid when associated, 0 if assoc = 0
     * <ap_mac>: wifi ap mac addr, 0 if assoc = 0
     * <wifi_type>: wifi type: such as 802.11b, 802.11n...
     * <mtu>: mtu size
     */
    char** params = (char**)msg->getData()->getData();
    char* ifname = params[0]? params[0]: (char*)"";

    char* assoc_str = params[1]? params[1]: (char*)"0";
    if (strlen(assoc_str) != 1) {
        logE(RFX_LOG_TAG, "sendWifiAssociated: assoc len error");
        handleErrorResponse(msg);
        return;
    }
    const uint8_t assoc = (uint8_t)atoi(assoc_str);

    char* ssid = (assoc == 0)? (char*)"0": params[2];
    if (ssid == NULL) {
        ssid = (char*)"";
        logE(RFX_LOG_TAG, "sendWifiAssociated: no ssid");
    }
    char* ap_mac = (assoc == 0)? (char*)"0": params[3];

    char* mtu = (assoc == 0)? (char*)"0": params[4];
    if (mtu == NULL) {
        mtu = (char*)"0";
        logE(RFX_LOG_TAG, "sendWifiAssociated: no mtu");
    }
    //value greater than 10000 will be ignore
    if (strlen(mtu) >= 5) {
        logE(RFX_LOG_TAG, "sendWifiAssociated: mtu len error");
        handleErrorResponse(msg);
        return;
    }
    uint16_t mtu_tlv = (uint16_t)atoi(mtu);

    char defaultWifiType[RFX_PROPERTY_VALUE_MAX] = { 0 };
    rfx_property_get("vendor.test.wifi.type", defaultWifiType, "802.11n");
    char* type = defaultWifiType;

    if (assoc == 0) {
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
                logD(RFX_LOG_TAG, "get wifi type ok: [%s]", (char*)wrq.u.data.pointer);
                type = (char*) wrq.u.data.pointer;
            } else {
                logD(RFX_LOG_TAG, "get wifi type fail: %d, len = %d", ret, wrq.u.data.length);
            }
            close(ioctl_sock);
        } else {
            logE(RFX_LOG_TAG, "sendWifiAssociated ioctl_sock = %d %s",
                    ioctl_sock, strerror(errno));
        }
    }

    // Ut Test
    if (UNIT_TEST) {
        logD(RFX_LOG_TAG, "sendWifiAssociated +EWIFIASC:%s,%d,%s,%s,%s,%d",
            ifname, assoc, ssid, ap_mac, type, mtu_tlv);
    } else {
        logD(RFX_LOG_TAG, "sendWifiAssociated assoc:%d", assoc);
    }

    uint8_t ap_mac_array[MIPC_FIX_WFC_MAC_LEN] = {0};
    convertStringMacToByteArray(ap_mac, ap_mac_array, MIPC_FIX_WFC_MAC_LEN);

    sp<RfxMipcData> requestData = RfxMipcData::obtainMipcData(MIPC_WFC_WIFI_INFO_NTF, msg->getSlotId());
    requestData->addMipcTlvStr(MIPC_WFC_WIFI_INFO_NTF_T_IFNAME, ifname);
    requestData->addMipcTlvUint8(MIPC_WFC_WIFI_INFO_NTF_T_ASSOCIATED, assoc);
    requestData->addMipcTlvStr(MIPC_WFC_WIFI_INFO_NTF_T_SSID, ssid);
    requestData->addMipcTlv(MIPC_WFC_WIFI_INFO_NTF_T_AP_MAC, MIPC_FIX_WFC_MAC_LEN, ap_mac_array);
    requestData->addMipcTlvUint8(MIPC_WFC_WIFI_INFO_NTF_T_WIFI_TYPE, MIPC_WIFI_TYPE_802_11n);
    requestData->addMipcTlvUint16(MIPC_WFC_WIFI_INFO_NTF_T_MTU, mtu_tlv);

    //send NTF notify
    int result = callToMipcMsgNtf(requestData);
    logD(RFX_LOG_TAG, "sendWifiAssociated result: %d", result);
    handleNtfCmdResponse(msg);
}

void RmmWifiRelayRequestHandler::sendWifiIpAddress(const sp<RfxMclMessage>& msg) {
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
    // Google HIDL service changes "" in java as null in cpp
    char* ifname = params[0]? params[0]: (char*)"" ;
    char* ipv4 = (params[1] == NULL) ? (char*)"" : params[1];
    char* ipv6 = (params[2] == NULL) ? (char*)"" : params[2];
    char* ipv4PrefixLen = (params[3] == NULL) ? (char*)"0" : params[3];
    char* ipv6PrefixLen = (params[4] == NULL) ? (char*)"0" : params[4];
    char* ipv4gateway = (params[5] == NULL) ? (char*)"" : params[5];
    char* ipv6gateway = (params[6] == NULL) ? (char*)"" : params[6];
    char* dnsCount = (params[7] == NULL) ? (char*)"0" : params[7];
    int16_t dnsCount_tlv = atoi(dnsCount);
    char* dnsAddresses = (params[8] == NULL) ? (char*)"" : params[8];

    uint8_t ipv4PrefixLen_tlv = 0;
    if (strncmp(ipv4PrefixLen, "-1", 2) != 0) {
        ipv4PrefixLen_tlv = (uint8_t)atoi(ipv4PrefixLen);
    }
    uint8_t ipv6PrefixLen_tlv = 0;
    if (strncmp(ipv6PrefixLen, "-1", 2) != 0) {
        ipv6PrefixLen_tlv = (uint8_t)atoi(ipv6PrefixLen);
    }

    // Ut Test
    if (UNIT_TEST) {
        logD(RFX_LOG_TAG, "sendWifiIpAddress +EWIFIADDR:%s,%s,%s,%d,%d,%s,%s,%d,%s",
            ifname, ipv4, ipv6, ipv4PrefixLen_tlv, ipv6PrefixLen_tlv,
            ipv4gateway, ipv6gateway, dnsCount_tlv, dnsAddresses);
    } else {
        logD(RFX_LOG_TAG, "sendWifiIpAddress ipv4PrefixLen:%d, dnsCount:%d",
            ipv4PrefixLen_tlv, dnsCount_tlv);
    }

    uint8_t ipv4_array[MIPC_FIX_WFC_IPV4_LEN] = {0};
    convertStringIpv4ToByteArray(ipv4, ipv4_array, MIPC_FIX_WFC_IPV4_LEN);

    uint8_t ipv6_array[MIPC_FIX_WFC_IPV6_LEN] = {0};
    convertStringIpv6ToByteArray(ipv6, ipv6_array, MIPC_FIX_WFC_IPV6_LEN);

    uint8_t ipv4gateway_array[MIPC_FIX_WFC_IPV4_LEN] = {0};
    convertStringIpv4ToByteArray(ipv4gateway, ipv4gateway_array, MIPC_FIX_WFC_IPV4_LEN);

    uint8_t ipv6gateway_array[MIPC_FIX_WFC_IPV6_LEN] = {0};
    convertStringIpv6ToByteArray(ipv6gateway, ipv6gateway_array, MIPC_FIX_WFC_IPV6_LEN);

    sp<RfxMipcData> requestData = RfxMipcData::obtainMipcData(MIPC_WFC_WIFI_INFO_NTF, msg->getSlotId());
    requestData->addMipcTlvStr(MIPC_WFC_WIFI_INFO_NTF_T_IFNAME, ifname);
    requestData->addMipcTlv(MIPC_WFC_WIFI_INFO_NTF_T_IPV4, MIPC_FIX_WFC_IPV4_LEN, ipv4_array);
    requestData->addMipcTlv(MIPC_WFC_WIFI_INFO_NTF_T_IPV6, MIPC_FIX_WFC_IPV6_LEN, ipv6_array);
    if (ipv4PrefixLen_tlv > 0) {
        requestData->addMipcTlvUint8(MIPC_WFC_WIFI_INFO_NTF_T_IPV4_PREFIX_LEN, ipv4PrefixLen_tlv);
    }
    if (ipv6PrefixLen_tlv > 0) {
        requestData->addMipcTlvUint8(MIPC_WFC_WIFI_INFO_NTF_T_IPV6_PREFIX_LEN, ipv6PrefixLen_tlv);
    }
    requestData->addMipcTlv(MIPC_WFC_WIFI_INFO_NTF_T_IPV4_GATEWAY, MIPC_FIX_WFC_IPV4_LEN, ipv4gateway_array);
    requestData->addMipcTlv(MIPC_WFC_WIFI_INFO_NTF_T_IPV6_GATEWAY, MIPC_FIX_WFC_IPV6_LEN, ipv6gateway_array);
    requestData->addMipcTlvUint8(MIPC_WFC_WIFI_INFO_NTF_T_IP_UPDATE, MIPC_BOOLEAN_TRUE);

    //add dns array
    if (dnsCount_tlv > 0) {
        string dataSet(dnsAddresses);
        vector<string> dnsArray = splitString(dataSet, ",");
        if (dnsArray.empty() || dnsCount_tlv > dnsArray.size()) {
            logE(RFX_LOG_TAG, "setWifiIpAddress: dns count error");
            handleErrorResponse(msg);
            return;
        }

        mipc_msg_t *request = requestData->getData();
        mipc_msg_tlv_array_t *array;
        array = mipc_msg_add_tlv_array(request,
                MIPC_WFC_WIFI_INFO_NTF_T_DNS, dnsCount_tlv);
        char* tmpDns;
        uint8_t ipv4dns_array[MIPC_FIX_WFC_IPV4_LEN] = {0};
        uint8_t ipv6dns_array[MIPC_FIX_WFC_IPV6_LEN] = {0};
        for (int i = 0; i < dnsCount_tlv; i++) {
            //remove "" in string
            string dns = dnsArray[i].substr(1, dnsArray[i].length() - 2);
            tmpDns = dns.data();
            if (UNIT_TEST) {
                logD(RFX_LOG_TAG, "sendWifiIpAddress dns:%s", tmpDns);
            } else {
                logD(RFX_LOG_TAG, "sendWifiIpAddress dns:%d", i);
            }
            if (dnsArray[i].find(".") == string::npos) {
                //ipv6 dns
                memset(ipv6dns_array, 0, MIPC_FIX_WFC_IPV6_LEN);
                convertStringIpv6ToByteArray(tmpDns, ipv6dns_array, MIPC_FIX_WFC_IPV6_LEN);
            } else {
                //ipv4 dns
                memset(ipv4dns_array, 0, MIPC_FIX_WFC_IPV4_LEN);
                convertStringIpv4ToByteArray(tmpDns, ipv4dns_array, MIPC_FIX_WFC_IPV4_LEN);
                mipc_msg_add_idx(request, array, i, MIPC_FIX_WFC_IPV4_LEN, ipv4dns_array);
            }
        }
    }

    //send NTF notify
    int result = callToMipcMsgNtf(requestData);
    logD(RFX_LOG_TAG, "sendWifiIpAddress result: %d", result);
    handleNtfCmdResponse(msg);
}

vector<string> RmmWifiRelayRequestHandler::splitString(string str, string c) {
    string::size_type pos;
    vector<string> result;
    str += c;
    string::size_type len = str.size();
    for (string::size_type i = 0; i < len; i ++) {
        pos = str.find(c, i);
        if (pos < len) {
            string temp = str.substr(i, pos-i);
            result.push_back(temp);
            i = pos + c.size() -1;
        }
    }
    return result;
}

void RmmWifiRelayRequestHandler::convertStringMacToByteArray(
        char* mac, uint8_t macArray[], uint16_t arrayLen) {
    if (mac == NULL) {
        logE(RFX_LOG_TAG, "convertStringMacToByteArray params null");
        return;
    }
    string dataSet(mac);
    vector<string> byteArray = splitString(dataSet, ":");
    uint16_t len = byteArray.size();

    logI(RFX_LOG_TAG, "convertStringMacToByteArray len:%d, arrayLen:%d", len, arrayLen);
    if (len > arrayLen) {
        //original data too long, arrayLen is 6 byte
        return;
    }
    for (uint16_t i = 0; i < len; i++) {
        int result = sscanf(byteArray[i].data(), "%2hhx", &macArray[i]);
        if (result < 0) {
            logE(RFX_LOG_TAG, "convertStringMacToByteArray sscanf %s failed:%d",
                    byteArray[i].data(), result);
        }
    }

    if (UNIT_TEST) {
        logD(RFX_LOG_TAG, "convertStringMacToByteArray=%02x:%02x:%02x:%02x:%02x:%02x",
            macArray[0], macArray[1], macArray[2], macArray[3],
            macArray[4], macArray[5]);
    }
}

void RmmWifiRelayRequestHandler::convertStringIpv4ToByteArray(
        char* ipv4, uint8_t ipv4Array[], uint16_t arrayLen) {
    if (ipv4 == NULL) {
        logE(RFX_LOG_TAG, "convertStringIpv4ToByteArray params null");
        return;
    }
    string dataSet(ipv4);
    vector<string> byteArray = splitString(dataSet, ".");
    uint16_t len = byteArray.size();

    logD(RFX_LOG_TAG, "convertStringIpv4ToByteArray len:%d, arrayLen:%d", len, arrayLen);
    if (len > arrayLen) {
        //original data too long, arrayLen is 4 byte
        return;
    }
    for (uint16_t i = 0; i < len; i++) {
        ipv4Array[i] = (uint8_t)atoi(byteArray[i].data());
    }

    if (UNIT_TEST) {
        logD(RFX_LOG_TAG, "convertStringIpv4ToByteArray:%d.%d.%d.%d",
            ipv4Array[0], ipv4Array[1], ipv4Array[2], ipv4Array[3]);
    }
}

int RmmWifiRelayRequestHandler::convertStringIpv6ToByteArray(
        char* ipv6, uint8_t Ipv6Array[], uint16_t arrayLen) {
    /**
    adjust the format of IP address to be consistent and comparable
    EX 2001:2001:0:0:1::11 -> 2001:0000:0000:0001:0000:0000:0000:0011
    */
    int ret = 1;
    struct in6_addr v6Address;
    memset(&v6Address, 0, sizeof(v6Address));
    // ret: -1, error occurs, ret: 0, invalid address, ret: 1, success;
    ret = inet_pton(AF_INET6, ipv6, &v6Address);
    if (ret >= 0) {
        memcpy(Ipv6Array, &v6Address, arrayLen);
        if (UNIT_TEST) {
            logD(RFX_LOG_TAG, "convertStringIpv6ToByteArray ipv6_array=%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X",
                    Ipv6Array[0], Ipv6Array[1], Ipv6Array[2], Ipv6Array[3],
                    Ipv6Array[4], Ipv6Array[5], Ipv6Array[6], Ipv6Array[7],
                    Ipv6Array[8], Ipv6Array[9], Ipv6Array[10], Ipv6Array[11],
                    Ipv6Array[12], Ipv6Array[13], Ipv6Array[14], Ipv6Array[15]);
        } else {
            logD(RFX_LOG_TAG, "convertStringIpv6ToByteArray success:%d", ret);
        }
        return 0;
    }
    logE(RFX_LOG_TAG, "convertStringIpv6ToByteArray failed");
    return -1;
}

