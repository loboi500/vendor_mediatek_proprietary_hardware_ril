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
#include "RmmDcUtility.h"
#include "RfxMclStatusManager.h"
#include "mipc_api.h"
#include "mipc_data.h"

#define RFX_LOG_TAG "RmmDcUtility"

/*****************************************************************************
 * Class RmmDcUtility
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

int RmmDcUtility::isOp07Support() {
    int ret = 0;
    char optr_value[RFX_PROPERTY_VALUE_MAX] = {0};
    rfx_property_get("persist.vendor.operator.optr", optr_value, "0");
    if (strcmp(optr_value, OPERATOR_OP07) == 0) {
        ret = 1;
    }
    RFX_LOG_D(RFX_LOG_TAG, "isOp07Support = %d", ret);
    return ret;
}

int RmmDcUtility::isOp12Support() {
    int ret = 0;
    char optr_value[RFX_PROPERTY_VALUE_MAX] = {0};
    rfx_property_get("persist.vendor.operator.optr", optr_value, "0");
    if (strcmp(optr_value, OPERATOR_OP12) == 0) {
        ret = 1;
    }
    RFX_LOG_D(RFX_LOG_TAG, "isOp12Support = %d", ret);
    return ret;
}

int RmmDcUtility::isOp16Support() {
    int isOP16Support = 0;
    char optr_value[RFX_PROPERTY_VALUE_MAX] = {0};
    rfx_property_get("persist.vendor.operator.optr", optr_value, "0");
    if (strcmp(optr_value, "OP16") == 0) {
        isOP16Support = 1;
    }
    RFX_LOG_D(RFX_LOG_TAG, "isOP16Support = %d", isOP16Support);
    return isOP16Support;
}

int RmmDcUtility::isOp20Support() {
    int isOP20Support = 0;
    char optr_value[RFX_PROPERTY_VALUE_MAX] = {0};
    rfx_property_get("persist.vendor.operator.optr", optr_value, "0");
    if (strcmp(optr_value, "OP20") == 0) {
        isOP20Support = 1;
    }
    RFX_LOG_D(RFX_LOG_TAG, "isOP20Support = %d", isOP20Support);
    return isOP20Support;
}

int RmmDcUtility::isOp12MccMnc(const char *mccmnc) {
    for (unsigned int i = 0; i < sizeof(VZW_MCC_MNC)/
            sizeof(VZW_MCC_MNC[0]); i++) {
        if (0 == strcmp(mccmnc, VZW_MCC_MNC[i])) {
            RFX_LOG_V(RFX_LOG_TAG, "isOp12MccMnc: true.");
            return 1;
        }
    }
    return 0;
}

int RmmDcUtility::isPcoMccMnc(const char *mccmnc) {
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

void RmmDcUtility::getPropertyBySlot(int slotId, const char *propertyName, char *propertyValue) {
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

int RmmDcUtility::getAddressType(char* addr) {
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
RmmDcUtility::getProfileType(const int profileType) {
    switch (profileType) {
        case RIL_DATA_PROFILE_DEFAULT: return "default";
        case RIL_DATA_PROFILE_TETHERED: return "dun";
        case RIL_DATA_PROFILE_IMS: return "ims";
        case RIL_DATA_PROFILE_FOTA: return "fota";
        case RIL_DATA_PROFILE_CBS: return "cbs";
        default: return RmmDcUtility::getMtkProfileType(profileType);
    }
}

const char *
RmmDcUtility::getMtkProfileType(const int profileType) {
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

int RmmDcUtility::getApnTypeId(const int profileType) {
    switch (profileType) {
        case RIL_DATA_PROFILE_DEFAULT: return RIL_APN_TYPE_DEFAULT;
        case RIL_DATA_PROFILE_TETHERED: return RIL_APN_TYPE_DUN;
        case RIL_DATA_PROFILE_IMS: return RIL_APN_TYPE_IMS;
        case RIL_DATA_PROFILE_FOTA: return RIL_APN_TYPE_FOTA;
        case RIL_DATA_PROFILE_CBS: return RIL_APN_TYPE_CBS;
        default: return RmmDcUtility::getMtkApnTypeId(profileType);
    }
}

int RmmDcUtility::getMtkApnTypeId(const int profileType) {
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
        case RIL_DATA_PROFILE_VENDOR_ENTERPRISE: RIL_APN_TYPE_ENTERPRISE;
        default: return APN_TYPE_INVALID;
    }
}

int RmmDcUtility::getMipcApnTypeId(const int profileType) {
    switch (profileType) {
        case RIL_DATA_PROFILE_DEFAULT:          return MIPC_APN_TYPE_DEFAULT;
        case RIL_DATA_PROFILE_TETHERED:         return MIPC_APN_TYPE_DUN;
        case RIL_DATA_PROFILE_IMS:              return MIPC_APN_TYPE_IMS;
        case RIL_DATA_PROFILE_FOTA:             return MIPC_APN_TYPE_FOTA;
        case RIL_DATA_PROFILE_CBS:              return MIPC_APN_TYPE_CBS;
        case RIL_DATA_PROFILE_VENDOR_MMS:       return MIPC_APN_TYPE_MMS;
        case RIL_DATA_PROFILE_VENDOR_SUPL:      return MIPC_APN_TYPE_SUPL;
        case RIL_DATA_PROFILE_VENDOR_HIPRI:     return MIPC_APN_TYPE_HIPRI;
        case RIL_DATA_PROFILE_VENDOR_EMERGENCY: return MIPC_APN_TYPE_EMERGENCY;
        case RIL_DATA_PROFILE_VENDOR_XCAP:      return MIPC_APN_TYPE_XCAP;
        case RIL_DATA_PROFILE_VENDOR_RCS:       return MIPC_APN_TYPE_RCS;
        case RIL_DATA_PROFILE_VENDOR_BIP:       return MIPC_APN_TYPE_BIP;
        case RIL_DATA_PROFILE_VENDOR_VSIM:      return MIPC_APN_TYPE_VSIM;
        // TODO: For MCS, use MIPC defined value after MIPC adding defination
        case RIL_DATA_PROFILE_VENDOR_MCX:       return RIL_APN_TYPE_MCX;
        default: return MIPC_APN_TYPE_UNKNOWN;
    }
}

const char *
RmmDcUtility::getApnType(int apnTypeId) {
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
        case RIL_APN_TYPE_RCS: return "rcs";
        case RIL_APN_TYPE_BIP: return "bip";
        case RIL_APN_TYPE_VSIM: return "vsim";
        case RIL_APN_TYPE_ALL: return "default,hipri,mms,supl,dun,fota,cbs";
        case RIL_APN_TYPE_MTKALL: return "default,hipri,mms,supl,dun,fota,cbs"
                                         ",xcap,rcs,bip,vsim";
        default: return "unknown";
    }
}

int RmmDcUtility::getProfileID(int apnTypeId) {
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

int RmmDcUtility::getProtocolType(const char* protocol) {
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

const char* RmmDcUtility::getProtocolName(int protocol) {
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

int RmmDcUtility::getProtocolClassBitmap(int protocol) {
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

int RmmDcUtility::getMipcProtocolType(const char* protocol) {
    int type = MIPC_APN_PDP_TYPE_IPV4;

    if (protocol == NULL) {
        return type;
    }

    if (!strcmp(protocol, SETUP_DATA_PROTOCOL_IP)) {
        type = MIPC_APN_PDP_TYPE_IPV4;
    } else if (!strcmp(protocol, SETUP_DATA_PROTOCOL_IPV6)) {
        type = MIPC_APN_PDP_TYPE_IPV6;
    } else if (!strcmp(protocol, SETUP_DATA_PROTOCOL_IPV4V6)) {
        type = MIPC_APN_PDP_TYPE_IPV4V6;
    }

    RFX_LOG_D(RFX_LOG_TAG, "The protocol type is %d", type);
    return type;
}

int RmmDcUtility::getAuthType(int authType) {
    // TODO: Move the logic of transfer AUTHTYPE_PAP_CHAP to AUTHTYPE_CHAP to DDM.
    // Sync AuthType value(AT+CGAUTH uses) to DDM. Treat AUTHTYPE_PAP_CHAP as
    // AUTHTYPE_CHAP as modem's suggestion, other values just bypass to modem.
    if (authType == AUTHTYPE_PAP_CHAP) {
        return AUTHTYPE_CHAP;
    }

    return authType;
}

int RmmDcUtility::stringToBinaryBase(char *str, int base, int *err) {
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

int RmmDcUtility::isImsSupport() {
    int isImsSupport = 0;
    char prop_value[RFX_PROPERTY_VALUE_MAX] = {0};
    rfx_property_get("persist.vendor.ims_support", prop_value, "0");
    isImsSupport = atoi(prop_value);
    RFX_LOG_D(RFX_LOG_TAG, "isImsSupport = %d", isImsSupport);
    return isImsSupport;
}

const char *RmmDcUtility::addrTypeToString(ADDRESS_TYPE addrType) {
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

const char *RmmDcUtility::pdnTypeToString(int pdnType) {
    switch (pdnType) {
        case IPV4: return "IPV4";
        case IPV6: return "IPV6";
        case IPV4V6: return "IPV4V6";
        default: return "INVALID PDN TYPE";
    }
}

bool RmmDcUtility::isRcsSupportPcscf() {
    int isRcsSupport = 0;
    int op08 = 0;
    char prop_value[RFX_PROPERTY_VALUE_MAX] = {0};

    rfx_property_get("persist.vendor.mtk_rcs_ua_support", prop_value, "0");
    isRcsSupport = (!strcmp(prop_value, "1")) ? 1 : 0;
    rfx_property_get("persist.vendor.operator.optr", prop_value, "0");
    op08 = (!strcmp(prop_value, OPERATOR_OP08)) ? 1 : 0;

    RFX_LOG_D(RFX_LOG_TAG, "isRcsSupportPcscf = %d:%d", isRcsSupport, op08);

    if (isRcsSupport && op08) {
        return true;
    }
    return false;
}

bool RmmDcUtility::isUserBuild() {
    char property_value[RFX_PROPERTY_VALUE_MAX] = {0};
    rfx_property_get("ro.build.type", property_value, "");
    if (strcmp(property_value, "user") == 0) {
        return true;
    }
    return false;
}

int RmmDcUtility::isFastDormancySupport() {
    int isFdSupport = 0;
    char propertyValue[RFX_PROPERTY_VALUE_MAX] = { 0 };
    rfx_property_get(PROPERTY_MTK_FD_SUPPORT, propertyValue, "0");
    isFdSupport = atoi(propertyValue);
    return isFdSupport ? 1 : 0;
}

int RmmDcUtility::getMipcApnType(int rilApnType) {
    int mipcApnType = 0;
    if (rilApnType & RIL_APN_TYPE_DEFAULT) {
        mipcApnType |= MIPC_APN_TYPE_DEFAULT;
    }
    if (rilApnType & RIL_APN_TYPE_MMS) {
        mipcApnType |= MIPC_APN_TYPE_MMS;
    }
    if (rilApnType & RIL_APN_TYPE_SUPL) {
        mipcApnType |= MIPC_APN_TYPE_SUPL;
    }
    if (rilApnType & RIL_APN_TYPE_DUN) {
        mipcApnType |= MIPC_APN_TYPE_DUN;
    }
    if (rilApnType & RIL_APN_TYPE_HIPRI) {
        mipcApnType |= MIPC_APN_TYPE_HIPRI;
    }
    if (rilApnType & RIL_APN_TYPE_FOTA) {
        mipcApnType |= MIPC_APN_TYPE_FOTA;
    }
    if (rilApnType & RIL_APN_TYPE_IMS) {
        mipcApnType |= MIPC_APN_TYPE_IMS;
    }
    if (rilApnType & RIL_APN_TYPE_CBS) {
        mipcApnType |= MIPC_APN_TYPE_CBS;
    }
    if (rilApnType & RIL_APN_TYPE_IA) {
        mipcApnType |= MIPC_APN_TYPE_IA;
    }
    if (rilApnType & RIL_APN_TYPE_EMERGENCY) {
        mipcApnType |= MIPC_APN_TYPE_EMERGENCY;
    }
    /* not support yet.
    if (rilApnType & RIL_APN_TYPE_MCX) {
        mipcApnType |= MIPC_APN_TYPE_MCX;
    }*/
    if (rilApnType & RIL_APN_TYPE_XCAP) {
        mipcApnType |= MIPC_APN_TYPE_XCAP;
    }
    if (rilApnType & RIL_APN_TYPE_RCS) {
        mipcApnType |= MIPC_APN_TYPE_RCS;
        if (RmmDcUtility::isRcsSupportPcscf()) {
            mipcApnType |= MIPC_APN_TYPE_RCS_PCSCF;
        }
    }
    if (rilApnType & RIL_APN_TYPE_BIP) {
        mipcApnType |= MIPC_APN_TYPE_BIP;
    }
    if (rilApnType & RIL_APN_TYPE_VSIM) {
        mipcApnType |= MIPC_APN_TYPE_VSIM;
    }
    // No enterprise defination in modem, change to default.
    if (rilApnType & RIL_APN_TYPE_ENTERPRISE) {
        mipcApnType |= MIPC_APN_TYPE_DEFAULT;
    }

    return mipcApnType;
}

int RmmDcUtility::radioTechToAccessNw(RIL_RadioTechnology radioTech) {
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

RIL_SliceServiceType RmmDcUtility::convertIntToSliceServiceType(int sst) {
    if (sst > 0 && sst <= 3) {
        return (RIL_SliceServiceType)sst;
    } else {
        return NONE_TYPE;
    }
}


int RmmDcUtility::charToInt(char aChar) {
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

long RmmDcUtility::hexStrToDec(const char* hexStr) {
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
