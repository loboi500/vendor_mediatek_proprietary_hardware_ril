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
#include "RmcDcUtility.h"
#include "RfxMclStatusManager.h"
#define RFX_LOG_TAG "RmcDcUtility"

/*****************************************************************************
 * Class RmcDcUtility
 *****************************************************************************/
static const char* VZW_MCC_MNC[] =
{
        "310004", "310005", "310006", "310010", "310012", "310013",
        "310350", "310590", "310820", "310890", "310910", "311012",
        "311110", "311270", "311271", "311272", "311273", "311274",
        "311275", "311276", "311277", "311278", "311279", "311280",
        "311281", "311282", "311283", "311284", "311285", "311286",
        "311287", "311288", "311289", "311390", "311480", "311481",
        "311482", "311483", "311484", "311485", "311486", "311487",
        "311488", "311489", "311590", "312770",
};

static const char* EXTRA_PCO_MCC_MNC[] =
{
    "20404", "310000", "310028",
};

int RmcDcUtility::isOp07Support() {
    int ret = 0;
    char optr_value[RFX_PROPERTY_VALUE_MAX] = {0};
    rfx_property_get("persist.vendor.operator.optr", optr_value, "0");
    if (strcmp(optr_value, OPERATOR_OP07) == 0) {
        ret = 1;
    }
    RFX_LOG_D(RFX_LOG_TAG, "isOp07Support = %d", ret);
    return ret;
}

int RmcDcUtility::isOp12Support() {
    int ret = 0;
    char optr_value[RFX_PROPERTY_VALUE_MAX] = {0};
    rfx_property_get("persist.vendor.operator.optr", optr_value, "0");
    if (strcmp(optr_value, OPERATOR_OP12) == 0) {
        ret = 1;
    }
    RFX_LOG_D(RFX_LOG_TAG, "isOp12Support = %d", ret);
    return ret;
}

int RmcDcUtility::isOp16Support() {
    int isOP16Support = 0;
    char optr_value[RFX_PROPERTY_VALUE_MAX] = {0};
    rfx_property_get("persist.vendor.operator.optr", optr_value, "0");
    if (strcmp(optr_value, "OP16") == 0) {
        isOP16Support = 1;
    }
    RFX_LOG_D(RFX_LOG_TAG, "isOP16Support = %d", isOP16Support);
    return isOP16Support;
}

int RmcDcUtility::isOp20Support() {
    int isOP20Support = 0;
    char optr_value[RFX_PROPERTY_VALUE_MAX] = {0};
    rfx_property_get("persist.vendor.operator.optr", optr_value, "0");
    if (strcmp(optr_value, "OP20") == 0) {
        isOP20Support = 1;
    }
    RFX_LOG_D(RFX_LOG_TAG, "isOP20Support = %d", isOP20Support);
    return isOP20Support;
}

int RmcDcUtility::isOp12MccMnc(const char *mccmnc) {
    for (unsigned int i = 0; i < sizeof(VZW_MCC_MNC)/
            sizeof(VZW_MCC_MNC[0]); i++) {
        if (0 == strcmp(mccmnc, VZW_MCC_MNC[i])) {
            RFX_LOG_V(RFX_LOG_TAG, "isOp12MccMnc: true.");
            return 1;
        }
    }
    return 0;
}

int RmcDcUtility::isPcoMccMnc(const char *mccmnc) {
    int isPco = isOp12MccMnc(mccmnc);
    if (isPco == 0) {
        int size = sizeof(EXTRA_PCO_MCC_MNC) / sizeof(EXTRA_PCO_MCC_MNC[0]);
        for (unsigned int i = 0; i < size; i++) {
            if (0 == strcmp(mccmnc, EXTRA_PCO_MCC_MNC[i])) {
                isPco = 1;
                break;
            }
        }
    }
    return isPco;
}

void RmcDcUtility::getPropertyBySlot(int slotId, const char *propertyName, char *propertyValue) {
    char prop[MTK_PROPERTY_VALUE_MAX] = {0};
    rfx_property_get(propertyName, prop, "");

    std::string propContent = std::string(prop);
    propContent.erase(std::remove_if(begin(propContent), end(propContent), ::isspace),
            end(propContent));

    int sepIdx = propContent.find(",");
    std::string prop1 = std::string(propContent);
    std::string prop2 = "";
    if (sepIdx > 0) {
        prop1 = propContent.substr(0, sepIdx);
        prop2 = propContent.substr(sepIdx+1, std::string::npos);
    }

    if (slotId == 0) {
        strncpy(propertyValue, prop1.c_str(), prop1.size());
    } else if (slotId == 1) {
        strncpy(propertyValue, prop2.c_str(), prop2.size());
    }
}

int RmcDcUtility::getAddressType(char* addr) {
    int type = IPV4;
    int length = strlen(addr);
    if (length >= MAX_IPV6_ADDRESS_LENGTH) {
        type = IPV4V6;
    } else if (length >= MAX_IPV4_ADDRESS_LENGTH) {
        type = IPV6;
    }
    return type;
}

const char *
RmcDcUtility::getProfileType(const int profileType) {
    switch (profileType) {
        case RIL_DATA_PROFILE_DEFAULT: return "default";
        case RIL_DATA_PROFILE_TETHERED: return "dun";
        case RIL_DATA_PROFILE_IMS: return "ims";
        case RIL_DATA_PROFILE_FOTA: return "fota";
        case RIL_DATA_PROFILE_CBS: return "cbs";
        default: return RmcDcUtility::getMtkProfileType(profileType);
    }
}

const char *
RmcDcUtility::getMtkProfileType(const int profileType) {
    switch (profileType) {
        case RIL_DATA_PROFILE_VENDOR_MMS: return "mms";
        case RIL_DATA_PROFILE_VENDOR_SUPL: return "supl";
        case RIL_DATA_PROFILE_VENDOR_HIPRI: return "hipri";
        case RIL_DATA_PROFILE_VENDOR_EMERGENCY: return "emergency";
        case RIL_DATA_PROFILE_VENDOR_XCAP: return "xcap";
        case RIL_DATA_PROFILE_VENDOR_RCS: return "rcs";
        case RIL_DATA_PROFILE_VENDOR_BIP: return "bip";
        case RIL_DATA_PROFILE_VENDOR_VSIM: return "vsim";
        case RIL_DATA_PROFILE_VENDOR_MCX: return "mcx";
        default: return "unknown";
    }
}

int RmcDcUtility::getApnTypeId(const int profileType) {
    switch (profileType) {
        case RIL_DATA_PROFILE_DEFAULT: return RIL_APN_TYPE_DEFAULT;
        case RIL_DATA_PROFILE_TETHERED: return RIL_APN_TYPE_DUN;
        case RIL_DATA_PROFILE_IMS: return RIL_APN_TYPE_IMS;
        case RIL_DATA_PROFILE_FOTA: return RIL_APN_TYPE_FOTA;
        case RIL_DATA_PROFILE_CBS: return RIL_APN_TYPE_CBS;
        default: return RmcDcUtility::getMtkApnTypeId(profileType);
    }
}

int RmcDcUtility::getMtkApnTypeId(const int profileType) {
    switch (profileType) {
        case RIL_DATA_PROFILE_VENDOR_MMS: return RIL_APN_TYPE_MMS;
        case RIL_DATA_PROFILE_VENDOR_SUPL: return RIL_APN_TYPE_SUPL;
        case RIL_DATA_PROFILE_VENDOR_HIPRI: return RIL_APN_TYPE_HIPRI;
        case RIL_DATA_PROFILE_VENDOR_EMERGENCY: return RIL_APN_TYPE_EMERGENCY;
        case RIL_DATA_PROFILE_VENDOR_XCAP: return RIL_APN_TYPE_XCAP;
        case RIL_DATA_PROFILE_VENDOR_RCS: return RIL_APN_TYPE_RCS;
        case RIL_DATA_PROFILE_VENDOR_BIP: return RIL_APN_TYPE_BIP;
        case RIL_DATA_PROFILE_VENDOR_VSIM: return RIL_APN_TYPE_VSIM;
        case RIL_DATA_PROFILE_VENDOR_MCX: return RIL_APN_TYPE_MCX;
        default: return APN_TYPE_INVALID;
    }
}

const char *
RmcDcUtility::getApnType(int apnTypeId) {
    switch (apnTypeId) {
        case RIL_APN_TYPE_DEFAULT: return "default";
        case RIL_APN_TYPE_MMS: return "mms";
        case RIL_APN_TYPE_SUPL: return "supl";
        case RIL_APN_TYPE_DUN: return "dun";
        case RIL_APN_TYPE_HIPRI: return "hipri";
        case RIL_APN_TYPE_FOTA: return "fota";
        case RIL_APN_TYPE_IMS: return "ims";
        case RIL_APN_TYPE_CBS: return "cbs";
        case RIL_APN_TYPE_IA: return "ia";
        case RIL_APN_TYPE_EMERGENCY: return "emergency";
        case RIL_APN_TYPE_MCX: return "mcx";
        case RIL_APN_TYPE_XCAP: return "xcap";
        case RIL_APN_TYPE_RCS: return checkRcsSupportPcscf();
        case RIL_APN_TYPE_BIP: return "bip";
        case RIL_APN_TYPE_VSIM: return "vsim";
        case RIL_APN_TYPE_ALL: return "default,hipri,mms,supl,dun,fota,cbs";
        case RIL_APN_TYPE_MTKALL: return "default,hipri,mms,supl,dun,fota,cbs"
                                         ",xcap,rcs,bip,vsim";
        default: return "unknown";
    }
}

int RmcDcUtility::getProfileID(int apnTypeId) {
    switch (apnTypeId) {
        case RIL_APN_TYPE_DEFAULT: return RIL_DATA_PROFILE_DEFAULT;
        case RIL_APN_TYPE_DUN: return RIL_DATA_PROFILE_TETHERED;
        case RIL_APN_TYPE_FOTA: return RIL_DATA_PROFILE_FOTA;
        case RIL_APN_TYPE_IMS: return RIL_DATA_PROFILE_IMS;
        case RIL_APN_TYPE_CBS: return RIL_DATA_PROFILE_CBS;
        case RIL_APN_TYPE_MMS: return RIL_DATA_PROFILE_VENDOR_MMS;
        case RIL_APN_TYPE_SUPL: return RIL_DATA_PROFILE_VENDOR_SUPL;
        case RIL_APN_TYPE_XCAP: return RIL_DATA_PROFILE_VENDOR_XCAP;
        case RIL_APN_TYPE_BIP: return RIL_DATA_PROFILE_VENDOR_BIP;
        case RIL_APN_TYPE_HIPRI: return RIL_DATA_PROFILE_VENDOR_HIPRI;
        case RIL_APN_TYPE_EMERGENCY: return RIL_DATA_PROFILE_VENDOR_EMERGENCY;
        case RIL_APN_TYPE_RCS: return RIL_DATA_PROFILE_VENDOR_RCS;
        case RIL_APN_TYPE_VSIM: return RIL_DATA_PROFILE_VENDOR_VSIM;
        case RIL_APN_TYPE_MCX: return RIL_DATA_PROFILE_VENDOR_MCX;
        default: return RIL_DATA_PROFILE_DEFAULT;
    }
}

int RmcDcUtility::getProtocolType(const char* protocol) {
    int type = IPV4;

    if (protocol == NULL) {
        return type;
    }

    if (!strcmp(protocol, SETUP_DATA_PROTOCOL_IP)) {
        type = IPV4;
    } else if (!strcmp(protocol, SETUP_DATA_PROTOCOL_IPV6)) {
        type = IPV6;
    } else if (!strcmp(protocol, SETUP_DATA_PROTOCOL_IPV4V6)) {
        type = IPV4V6;
    }

    RFX_LOG_D(RFX_LOG_TAG, "The protocol type is %d", type);
    return type;
}

const char* RmcDcUtility::getProtocolName(int protocol) {
    const char* name = NULL;
    switch (protocol) {
        case IPV4:
            name = SETUP_DATA_PROTOCOL_IP;
            break;
        case IPV6:
            name = SETUP_DATA_PROTOCOL_IPV6;
            break;
        case IPV4V6:
            name = SETUP_DATA_PROTOCOL_IPV4V6;
            break;
        default:
            name = SETUP_DATA_PROTOCOL_IP;
            break;
    }

    RFX_LOG_D(RFX_LOG_TAG, "The protocol name is %s", name);
    return name;
}

int RmcDcUtility::getProtocolClassBitmap(int protocol) {
    switch (protocol) {
        case IPV4:
            return NETAGENT_ADDR_TYPE_IPV4;
        case IPV6:
            return NETAGENT_ADDR_TYPE_IPV6;
        case IPV4V6:
            return NETAGENT_ADDR_TYPE_ANY;
        default:
            return NETAGENT_ADDR_TYPE_UNKNOWN;
    }
}

int RmcDcUtility::getAuthType(int authType) {
    // TODO: Move the logic of transfer AUTHTYPE_PAP_CHAP to AUTHTYPE_CHAP to DDM.
    // Sync AuthType value(AT+CGAUTH uses) to DDM. Treat AUTHTYPE_PAP_CHAP as
    // AUTHTYPE_CHAP as modem's suggestion, other values just bypass to modem.
    if (authType == AUTHTYPE_PAP_CHAP) {
        return AUTHTYPE_CHAP;
    }

    return authType;
}

int RmcDcUtility::stringToBinaryBase(char *str, int base, int *err) {
    int out;
    unsigned long ul;
    *err = 0;

    if (str == NULL) {
        *err = -1;
        return 0;
    }

    ul = strtoul(str, NULL, base);
    if (ul == ULONG_MAX) {
        RFX_LOG_E(RFX_LOG_TAG, "[%s] error on strtoul", __FUNCTION__);
        *err = -2;
        return 0;
    }
    out = (int)ul;

    return out;
}

int RmcDcUtility::isImsSupport() {
    int isImsSupport = 0;
    char prop_value[RFX_PROPERTY_VALUE_MAX] = {0};
    rfx_property_get("persist.vendor.ims_support", prop_value, "0");
    isImsSupport = atoi(prop_value);
    RFX_LOG_D(RFX_LOG_TAG, "isImsSupport = %d", isImsSupport);
    return isImsSupport;
}

const char *RmcDcUtility::addrTypeToString(ADDRESS_TYPE addrType) {
    switch (addrType) {
        case ADDRESS_NULL: return "NULL";
        case ADDRESS_IPV4: return "IPV4";
        case ADDRESS_IPV6_UNIQUE_LOCAL: return "IPV6 UNIQUE LOCAL";
        case ADDRESS_IPV6_SITE_LOCAL: return "IPV6 SITE LOCAL";
        case ADDRESS_IPV6_LINK_LOCAL: return "IPV6 LINK LOCAL";
        case ADDRESS_IPV6_GLOBAL: return "IPV6 GLOBAL";
        default: return "UNKNOWN";
    }
}

const char *RmcDcUtility::pdnTypeToString(int pdnType) {
    switch (pdnType) {
        case IPV4: return "IPV4";
        case IPV6: return "IPV6";
        case IPV4V6: return "IPV4V6";
        default: return "INVALID PDN TYPE";
    }
}

bool RmcDcUtility::isRcsUaSupport() {
    char property_value[RFX_PROPERTY_VALUE_MAX] = {0};
    rfx_property_get("persist.vendor.mtk_rcs_ua_support", property_value, "0");
    return strcmp(property_value, "1") == 0 ? true : false;
}

const char *RmcDcUtility::checkRcsSupportPcscf() {
    int isRcsSupport = 0;
    int op08 = 0;
    char prop_value[RFX_PROPERTY_VALUE_MAX] = {0};

    rfx_property_get("persist.vendor.mtk_rcs_ua_support", prop_value, "0");
    isRcsSupport = (!strcmp(prop_value, "1")) ? 1 : 0;
    rfx_property_get("persist.vendor.operator.optr", prop_value, "0");
    op08 = (!strcmp(prop_value, OPERATOR_OP08)) ? 1 : 0;

    RFX_LOG_D(RFX_LOG_TAG, "checkRcsSupportPcscf = %d:%d", isRcsSupport, op08);

    if (isRcsSupport && op08) {
        return "rcs,rcs_pcscf";
    }
    return "rcs";
}

bool RmcDcUtility::isUserBuild() {
    char property_value[RFX_PROPERTY_VALUE_MAX] = {0};
    rfx_property_get("ro.build.type", property_value, "");
    if (strcmp(property_value, "user") == 0) {
        return true;
    }
    return false;
}

// Override modem default apn for emergency apn protocol.
bool RmcDcUtility::isSupportOverrideModemDefaultApn() {
    char support_value[RFX_PROPERTY_VALUE_MAX] = {0};
    rfx_property_get("persist.vendor.radio.override_md_apn", support_value, "0");
    int value = atoi(support_value);
    return value == 1;
}

bool RmcDcUtility::isSupportDefaultImsApnSettings() {
    int isDefaultImsApnSupport = 0;
    char support_value[RFX_PROPERTY_VALUE_MAX] = {0};
    rfx_property_get("persist.vendor.radio.ims.default_apn", support_value, "0");
    isDefaultImsApnSupport = atoi(support_value);
    RFX_LOG_D(RFX_LOG_TAG, "isSupportDefaultImsApnSettings = %d", isDefaultImsApnSupport);
    return isDefaultImsApnSupport == 1;
}

// Check XFRM interface support or not, only support on non-5G and GKI platform.
bool RmcDcUtility::isXfrmSupport() {
    char xfrmSupport[RFX_PROPERTY_VALUE_MAX] = {0};
    rfx_property_get("persist.vendor.xfrm_support", xfrmSupport, "0");
    return (atoi(xfrmSupport) == 1);
}

// Version 1 is for Gen97 or later generation modem.
// Version 2 is for non-5G and GKI platform.
bool RmcDcUtility::isMdrsraSupport(int mdrsraVersion) {
    char mdrsraV2Support[RFX_PROPERTY_VALUE_MAX] = {0};
    rfx_property_get("persist.vendor.mdrsra_v2_support", mdrsraV2Support, "0");
    return (mdrsraVersion == 1 || (mdrsraVersion == 2 && atoi(mdrsraV2Support) == 1));
}

int RmcDcUtility::charToInt(char aChar) {
    if(isdigit(aChar)) {
        return aChar - 48;
    }
    if( aChar < 'A' || (aChar > 'F' && aChar < 'a') || aChar > 'z' ) {
        return -1;
    }
    if(isalpha(aChar)) {
        return isupper(aChar) ? aChar - 55 : aChar - 87;
    }
    return -1;
}

long RmcDcUtility::hexStrToDec(const char* hexStr) {
    if (hexStr == NULL || strlen(hexStr) == 0) {
        return -1;
    }
    int len = strlen(hexStr);
    int num = 0;
    int i = 0;
    int temp = 0;
    int bits = 0;

    for (; i < len; i++, temp = 0) {
        temp = charToInt(*(hexStr + i));
        bits = (len - i - 1) * 4;
        temp = temp << bits;
        num = num | temp;
    }
    return num;
}

int RmcDcUtility::radioTechToAccessNw(RIL_RadioTechnology radioTech) {
    /* AOSP_V1_5::RadioAccessNetworks to 3gpp 27.007 Sec 7.3
       RadioAccessNetworks 0: UNKNOWN
       RadioAccessNetworks 1: GERAN (0 GSM)
       RadioAccessNetworks 2: UTRAN (2 UTRAN)
       RadioAccessNetworks 3: EUTRAN(7 E-UTRAN)
       RadioAccessNetworks 4: NGRAN (12 NG-RAN)
    */
    switch(radioTech) {
        case RADIO_TECH_GSM:
        case RADIO_TECH_GPRS:
        case RADIO_TECH_EDGE:
        case RADIO_TECH_UMTS:
        case RADIO_TECH_IS95A:
        case RADIO_TECH_IS95B:
        case RADIO_TECH_1xRTT:
            return 1;
        case RADIO_TECH_EVDO_0:
        case RADIO_TECH_EVDO_A:
        case RADIO_TECH_HSDPA:
        case RADIO_TECH_HSUPA:
        case RADIO_TECH_HSPA:
        case RADIO_TECH_EVDO_B:
        case RADIO_TECH_EHRPD:
        case RADIO_TECH_HSPAP:
        case RADIO_TECH_TD_SCDMA:
            return 2;
        case RADIO_TECH_LTE:
        case RADIO_TECH_LTE_CA:
            return 3;
        case RADIO_TECH_NR:
            return 4;
        case RADIO_TECH_UNKNOWN:
        case RADIO_TECH_IWLAN:
        default:
            return 0;
    }
}

void RmcDcUtility::convertHexOsIdToIntArray(uint8_t *appId, char *hexStr) {
    // Convert HEX OS ID to uint array
    // os_id=\97\a4\98\e3\fc\92\5c\94\89\86\03\33\d0\6e\4e\47
    int index = 0;
    long ch = 0;
    for (char *pCur = strsep(&hexStr, "\\"); pCur != NULL; pCur = strsep(&hexStr, "\\")) {
        ch = hexStrToDec(pCur);
        RFX_LOG_D(RFX_LOG_TAG, "[%s] ch: %d", __FUNCTION__, ch);
        if (ch > 0) {
            appId[index++] = ch;
        }
        if (hexStr == NULL || index >= OS_ID_UUID_LEN) {
            break;
        }
    }
}

bool RmcDcUtility::parseTdFromString(RIL_TrafficDescriptor* td, char* tdStr) {
    if (td == NULL || tdStr == NULL || strlen(tdStr) <= 0) {
        RFX_LOG_E(RFX_LOG_TAG, "[%s] NULL parameter, tdStr:%s", __FUNCTION__, tdStr);
        return false;
    }
    if (strstr(tdStr, DNN_TAG) == NULL && strstr(tdStr, TD_APPID_TAG) == NULL) {
        // Since current android version only care about DNN and OS APP ID of a TD,
        // if a TD has no DNN and OS APP ID, ignore it.
        RFX_LOG_W(RFX_LOG_TAG, "[%s] ignore TD that has no DNN and APP ID, tdStr:%s",
                __FUNCTION__, tdStr);
        return false;
    }

    uint8_t osId[OS_ID_UUID_LEN] = {0};
    bool osIdValid = false;
    uint8_t *pAppId = NULL;
    int appIdLen = 0;
    for (char *pCur = strsep(&tdStr, "/"); pCur != NULL; pCur = strsep(&tdStr, "/")) {
        if (strstr(pCur, DNN_TAG) != NULL) {
            FREEIF(td->dnn);
            td->dnn = (char*)calloc((strlen(pCur) - strlen(DNN_TAG) + 1), sizeof(char));
            RFX_ASSERT(td->dnn != NULL);
            // dnn=xxx
            strncpy(td->dnn, pCur + strlen(DNN_TAG),
                    (strlen(pCur) - strlen(DNN_TAG)));
        } else if (strstr(pCur, TD_OSID_TAG) != NULL) {
            // os_id=yyy
            convertHexOsIdToIntArray(osId, pCur + strlen(TD_OSID_TAG));
            osIdValid = true;
        } else if (strstr(pCur, TD_APPID_TAG) != NULL) {
            // app_id=yyy
            appIdLen = strlen(pCur) - strlen(TD_APPID_TAG);
            pAppId = (uint8_t*)calloc(appIdLen, sizeof(uint8_t));
            RFX_ASSERT(pAppId != NULL);
            memcpy(pAppId, pCur + strlen(TD_APPID_TAG), appIdLen);
        }

        if (osIdValid && appIdLen > 0) {
            td->osAppIdLen = OS_ID_UUID_LEN + 1 + appIdLen;
            FREEIF(td->osAppId);
            td->osAppId = (uint8_t*)calloc(td->osAppIdLen, sizeof(uint8_t));
            RFX_ASSERT(td->osAppId != NULL);
            memcpy(td->osAppId, osId, OS_ID_UUID_LEN);
            td->osAppId[APP_ID_LEN_INDEX] = (uint8_t)appIdLen;
            memcpy(&td->osAppId[APP_ID_INDEX], pAppId, appIdLen);
        }

        if (tdStr == NULL) {
            break;
        }
    }
    RFX_LOG_D(RFX_LOG_TAG, "[%s] td:{%s,%d}", __FUNCTION__,
                    td->dnn, td->osAppIdLen);
    FREEIF(pAppId);
    return true;
}

void RmcDcUtility::parseRsdFromString(RIL_RouteSelectionDescriptor* rsd, char* rsdStr) {
    if (rsd == NULL || rsdStr == NULL || strlen(rsdStr) <= 0) {
        return;
    }
    char *pCur = NULL;
    for (pCur = strsep(&rsdStr, "/"); pCur != NULL; pCur = strsep(&rsdStr, "/")) {
        RFX_LOG_D(RFX_LOG_TAG, "[%s] pCur: %s, rsdStr: %s", __FUNCTION__, pCur, rsdStr);
        if (strstr(pCur, DNN_TAG) != NULL) {
            // dnn=aaa,bbb
            int dnnCount = 0;
            pCur += strlen(DNN_TAG);
            char *pDnnTemp = (char*)calloc(strlen(pCur) + 1, sizeof(char));
            char *pDnnOrg = pDnnTemp;
            RFX_ASSERT(pDnnTemp != NULL);
            strncpy(pDnnTemp, pCur, strlen(pCur));
            char *pDnn = strsep(&pDnnTemp, ",");
            for (; pDnn != NULL; pDnn = strsep(&pDnnTemp, ",")) {
                strncpy(rsd->dnn[dnnCount], pDnn, RIL_MAX_DNN_CHAR_COUNT);
                RFX_LOG_D(RFX_LOG_TAG, "[%s] RSD dnn[%d]: %s", __FUNCTION__,
                        dnnCount, rsd->dnn[dnnCount]);
                dnnCount++;
                if (pDnnTemp == NULL || dnnCount > RIL_MAX_DNN_COUNT) {
                    break;
                }
            }
            rsd->dnnCount = dnnCount;
            free(pDnnOrg);
        } else if (strstr(pCur, RSD_SSC_MOD_TAG) != NULL) {
            // AOSP ssc_mode=1/2/3
            int sscMode = atoi(pCur + strlen(RSD_SSC_MOD_TAG));
            if (sscMode >= 0 && sscMode <= 2) {
                rsd->sscMode = (RIL_SscMode)(sscMode + 1); // AT SSC mode value: 0/1/2
            } else {
                // Default value
                rsd->sscMode = SSC_MODE_1;
            }
        } else if (strstr(pCur, RSD_SNSSAI_TAG) != NULL) {
            // s-nssai=(sst/sst;mapped_sst/sst.sd/sst.sd;mapped_sst/sst.sd; mapped_sst. mapped_sd)
            RIL_SliceInfo nssais[MAX_NSSAIS];
            memset(nssais, 0, sizeof(RIL_SliceInfo) * MAX_NSSAIS);
            int count = 0;
            parseNssaiFromString(nssais, &count, SLICE_ALLOWED, pCur + strlen(RSD_SNSSAI_TAG));
            RFX_LOG_D(RFX_LOG_TAG, "[%s] RSD s-nssai: %s, count %d", __FUNCTION__,
                    pCur + strlen(RSD_SNSSAI_TAG), count);
            for (int i = 0; i < count; i++) {
                RFX_LOG_D(RFX_LOG_TAG, "[%s] nssai[%d]={%d,%d,%d,%d,%d}",
                        __FUNCTION__, i, nssais[i].sst, nssais[i].sliceDifferentiator,
                        nssais[i].mappedHplmnSst, nssais[i].mappedHplmnSD, nssais[i].status);
            }
            if (count > 0) {
                rsd->sliceCount = count;
                rsd->sliceInfo = (RIL_SliceInfo*)calloc(count, sizeof(RIL_SliceInfo));
                RFX_ASSERT(rsd->sliceInfo != NULL);
                memcpy(rsd->sliceInfo, nssais, count * sizeof(RIL_SliceInfo));
            }
        } else if (strstr(pCur, RSD_SESSION_TYPE_TAG) != NULL) {
            // pdu_session_type=IP/IPV6/IPV4V6
            rsd->sessionType = (char*)calloc((strlen(pCur) - strlen(RSD_SESSION_TYPE_TAG)),
                    sizeof(char));
            RFX_ASSERT(rsd->sessionType != NULL);
            strncpy(rsd->sessionType, pCur + strlen(RSD_SESSION_TYPE_TAG),
                    (strlen(pCur) - strlen(RSD_SESSION_TYPE_TAG)));
        }

        if (rsdStr == NULL) {
            break;
        }
    }
    RFX_LOG_D(RFX_LOG_TAG, "[%s] RSD {%d,%s,%d,%d,%d}", __FUNCTION__,
            rsd->precedence, rsd->sessionType, rsd->sscMode,
            rsd->sliceCount, rsd->dnnCount);
}

RIL_SliceServiceType RmcDcUtility::convertIntToSliceServiceType(int sst) {
    if (sst > 0 && sst <= 3) {
        return (RIL_SliceServiceType)sst;
    } else {
        return NONE_TYPE;
    }
}

void RmcDcUtility::parseNssaiFromString(RIL_SliceInfo *nssai, int *count, RIL_SliceStatus status,
        char* nssaiStr) {
    RFX_LOG_D(RFX_LOG_TAG, "[%s] nssaiStr: %s", __FUNCTION__, nssaiStr);
    if (nssaiStr == NULL || strlen(nssaiStr) <= 0) {
        return;
    }

    int index = 0;
    char sst[MAX_SST_CHAR + 1] = {0};
    char sd[MAX_SD_CHAR + 1] = {0};
    char cause[MAX_CAUSE_CHAR + 1] = {0};

    // sst1.sd1#cause;mapped_sst1.mapped_sd1:sst2.sd2#cause;mapped_sst2.mapped_sd2:sst3.sd3;mapped_sst3
    // Cause value (octet 3)
    // 3GPP TS 24.501 [161] table 9.11.3.46.1.
    // Bits
    // 0000 S-NSSAI not available in the current PLMN or SNPN
    // 0001 S-NSSAI not available in the current registration area
    // 0010 S-NSSAI not available due to the failed or revoked
    //      network slice-specific authentication and authorization
    for (char *pCur = strsep(&nssaiStr, ":"); pCur != NULL; pCur = strsep(&nssaiStr, ":"), index++) {
        /* 3GPP TS 27.007 10.1.1
           The <S-NSSAI> has one of the forms:
            sst                           only slice/service type (SST) is present
            sst;mapped_sst                SST and mapped configured SST are present
            sst.sd                        SST and slice differentiator (SD) are present
            sst.sd;mapped_sst             SST, SD and mapped configured SST are present
            sst.sd;mapped_sst.mapped_sd   SST, SD, mapped configured SST and mapped
                                          configured SD are present

           The rejected S-NSSAI has one of the forms:
            sst#cause                     only slice/service type (SST) and reject cause are present
            sst.sd#cause                  SST and slice differentiator (SD) and reject cause are present
        */

        RFX_LOG_D(RFX_LOG_TAG, "[%s] S-NSSAI[%d]:%s", __FUNCTION__, index, pCur);
        char* pSstSd[2] = { NULL };
        pSstSd[1] = (char*)calloc(strlen(pCur) + 1, sizeof(char));
        RFX_ASSERT(pSstSd[1] != NULL);
        strncpy(pSstSd[1], pCur, strlen(pCur));
        pSstSd[1][strlen(pCur)] = '\0';
        pSstSd[0] = strsep(&pSstSd[1], ";");

        // status
        nssai[index].status = status;

        for (int i = 0; i < 2; i++) {
            if (pSstSd[i] == NULL || strlen(pSstSd[i]) == 0) {
                continue;
            }

            int sdIndex = -1;
            int causeIndex = -1;
            int j = -1;
            while (pSstSd[i][++j] != '\0') {
                if (pSstSd[i][j] == '.') {
                    sdIndex = j;
                } else if (pSstSd[i][j] == '#') {
                    causeIndex = j;
                }
            }
            memset(sst, 0, MAX_SST_CHAR + 1);
            memset(sd, 0, MAX_SD_CHAR + 1);
            memset(cause, 0, MAX_CAUSE_CHAR + 1);
            if (sdIndex > 0 && causeIndex > 0) {
                // sst.sd#cause, must be non-mapped
                memcpy(sst, pSstSd[i], sdIndex);
                nssai[index].sst = convertIntToSliceServiceType(atoi(sst));
                memcpy(sd, pSstSd[i] + sdIndex + 1, causeIndex - sdIndex -1);
                nssai[index].sliceDifferentiator = atoi(sd);
                memcpy(cause, pSstSd[i] + causeIndex + 1, MAX_CAUSE_CHAR);
                RFX_LOG_D(RFX_LOG_TAG, "[%s] cause: %s, pSstSd[%d] cause string:%s", __FUNCTION__,
                        cause, i, pSstSd[i] + causeIndex + 1);
                if (atoi(cause) > 0) {
                    nssai[index].status = SLICE_REJECTED_NOT_AVAILABLE_IN_REG_AREA;
                }
            } else if (sdIndex > 0 && causeIndex < 0) {
                // sst.sd or mapped_sst.mapped_sd
                memcpy(sst, pSstSd[i], sdIndex);
                if (i == 0) {
                    nssai[index].sst = convertIntToSliceServiceType(atoi(sst));
                } else {
                    nssai[index].mappedHplmnSst = convertIntToSliceServiceType(atoi(sst));
                }
                memcpy(sd, pSstSd[i] + sdIndex + 1, strlen(pSstSd[i]) - sdIndex);
                if (i == 0) {
                    nssai[index].sliceDifferentiator = atoi(sd);
                } else {
                    nssai[index].mappedHplmnSD = atoi(sd);
                }
            } else if (sdIndex < 0 && causeIndex > 0) {
                // sst#cause, must be non-mapped
                memcpy(sst, pSstSd[i], causeIndex);
                nssai[index].sst = convertIntToSliceServiceType(atoi(sst));
                memcpy(cause, pSstSd[i] + causeIndex + 1, MAX_CAUSE_CHAR);
                if (atoi(cause) > 0) {
                    nssai[index].status = SLICE_REJECTED_NOT_AVAILABLE_IN_REG_AREA;
                }
            } else if (sdIndex < 0 && causeIndex < 0) {
                // sst or mapped_sst
                if (1 == 0) {
                    nssai[index].sst = convertIntToSliceServiceType(atoi(pSstSd[i]));
                } else {
                    nssai[index].mappedHplmnSst = convertIntToSliceServiceType(atoi(pSstSd[i]));
                }
            } else {
                // Should not be here
                RFX_LOG_E(RFX_LOG_TAG, "[%s] Parse sst/sd/cause error, pCur1: %s",
                        __FUNCTION__, pSstSd[i]);
            }
        }

        FREEIF(pSstSd[0]);
        FREEIF(pSstSd[1]);
        if (nssaiStr == NULL) {
            break;
        }
    }

    *count = index;
    RFX_LOG_D(RFX_LOG_TAG, "[%s] type:%d, count:%d, ", __FUNCTION__, status, index);
    for (int i = 0; i < index; i++) {
        RFX_LOG_D(RFX_LOG_TAG, "[%s] nssai[%d]={%d,%d,%d,%d,%d}",
                __FUNCTION__, i, nssai[i].sst, nssai[i].sliceDifferentiator,
                nssai[i].mappedHplmnSst, nssai[i].mappedHplmnSD, nssai[i].status);
    }
}

