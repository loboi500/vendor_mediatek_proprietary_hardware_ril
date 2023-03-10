/* Copyright Statement:
 *
 * This software/firmware and related documentation (IMS_CONFIG_"MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 *
 * MediaTek Inc. (IMS_CONFIG_C) 2018. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS (IMS_CONFIG_"MEDIATEK SOFTWARE")
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
 * The following software/firmware and/or related documentation (IMS_CONFIG_"MediaTek Software")
 * have been modified by MediaTek Inc. All revisions are subject to any receiver's
 * applicable license agreements with MediaTek Inc.
 */

#ifndef RIL_IMSCONFIGITEMS_H
#define RIL_IMSCONFIGITEMS_H
#define CONFIG_DATA(x,y,z) {ImsConfigItem::x,{ImsConfigItem::x,ImsCfgMimeType::y,z}},


CONFIG_DATA(IMS_CONFIG_VOCODER_AMRMODESET,STRING,"")
CONFIG_DATA(IMS_CONFIG_VOCODER_AMRWBMODESET,STRING,"")
CONFIG_DATA(IMS_CONFIG_SIP_SESSION_TIMER,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_MIN_SE,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_CANCELLATION_TIMER,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_TDELAY,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_SILENT_REDIAL_ENABLE,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_SIP_T1_TIMER,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_SIP_T2_TIMER,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_SIP_TF_TIMER,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_VLT_SETTING_ENABLED,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_LVC_SETTING_ENABLED,INTEGER,"video_over_ps_support")
CONFIG_DATA(IMS_CONFIG_DOMAIN_NAME,STRING,"")
CONFIG_DATA(IMS_CONFIG_SMS_FORMAT,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_SMS_OVER_IP,INTEGER,"sms_over_ip")
CONFIG_DATA(IMS_CONFIG_PUBLISH_TIMER,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_CAPABILITY_DISCOVERY_ENABLED,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_PUBLISH_TIMER_EXTENDED,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_CAPABILITIES_CACHE_EXPIRATION,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_AVAILABILITY_CACHE_EXPIRATION,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_CAPABILITIES_POLL_INTERVAL,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_SOURCE_THROTTLE_PUBLISH,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_MAX_NUMENTRIES_IN_RCL,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_CAPAB_POLL_LIST_SUB_EXP,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_GZIP_FLAG,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_EAB_SETTING_ENABLED,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_VOICE_OVER_WIFI_ROAMING,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_VOICE_OVER_WIFI_MODE,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_MOBILE_DATA_ENABLED,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_VOLTE_USER_OPT_IN_STATUS,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_LBO_PCSCF_ADDRESS,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_KEEP_ALIVE_ENABLED,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_REGISTRATION_RETRY_BASE_TIME_SEC,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_REGISTRATION_RETRY_MAX_TIME_SEC,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_SPEECH_START_PORT,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_SPEECH_END_PORT,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_SIP_INVITE_REQ_RETX_INTERVAL_MSEC,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_SIP_INVITE_RSP_WAIT_TIME_MSEC,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_SIP_INVITE_RSP_RETX_WAIT_TIME_MSEC,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_SIP_NON_INVITE_REQ_RETX_INTERVAL_MSEC,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_SIP_NON_INVITE_TXN_TIMEOUT_TIMER_MSEC,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_SIP_INVITE_RSP_RETX_INTERVAL_MSEC,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_SIP_ACK_RECEIPT_WAIT_TIME_MSEC,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_SIP_ACK_RETX_WAIT_TIME_MSEC,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_SIP_NON_INVITE_REQ_RETX_WAIT_TIME_MSEC,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_SIP_NON_INVITE_RSP_RETX_WAIT_TIME_MSEC,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_AMR_WB_OCTET_ALIGNED_PT,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_AMR_WB_BANDWIDTH_EFFICIENT_PT,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_AMR_OCTET_ALIGNED_PT,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_AMR_BANDWIDTH_EFFICIENT_PT,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_DTMF_WB_PT,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_DTMF_NB_PT,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_AMR_DEFAULT_MODE,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_SMS_PSI,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_VIDEO_QUALITY,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_VOICE_OVER_WIFI_SETTING_ENABLED,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_TH_LTE1,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_TH_LTE2,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_TH_LTE3,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_TH_1x,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_VOWT_A,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_VOWT_B,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_T_EPDG_LTE,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_T_EPDG_WIFI,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_T_EPDG_1X,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_VICE_SETTING_ENABLED,INTEGER,"call_pull_service")
CONFIG_DATA(IMS_CONFIG_RTT_SETTING_ENABLED,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_EPDG_ADDRESS,STRING,"epdg_identifier")
CONFIG_DATA(IMS_CONFIG_PUBLISH_ERROR_RETRY_TIMER,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_VOICE_OVER_WIFI_MDN,STRING,"")
CONFIG_DATA(IMS_CONFIG_VOICE_DOMAIN_PREFERENCE,INTEGER,"")
CONFIG_DATA(IMS_CONFIG_VONR_SETTING_ENABLED,INTEGER,"")

#endif //RIL_IMSCONFIGITEMS_H
