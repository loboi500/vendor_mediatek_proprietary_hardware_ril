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
#ifndef __RFX_MOBILE_WIFI_MESSAGE_ID_HEADER__
#define __RFX_MOBILE_WIFI_MESSAGE_ID_HEADER__

// Request msg id
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SET_WIFI_ENABLED)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SET_WIFI_ASSOCIATED)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SET_WFC_CONFIG)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_GET_WFC_CONFIG)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SET_WIFI_SIGNAL_LEVEL)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SET_GEO_LOCATION)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SET_WIFI_IP_ADDRESS)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SET_EMERGENCY_ADDRESS_ID)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SET_NATT_KEEP_ALIVE_STATUS)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SET_WIFI_PING_RESULT)
///M: Notify ePDG screen state
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_NOTIFY_EPDG_SCREEN_STATE)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_QUERY_SSAC_STATUS)

// URC msg id
RFX_MSG_ID_EXPN(RFX_MSG_UNSOL_MOBILE_WIFI_ROVEOUT)
RFX_MSG_ID_EXPN(RFX_MSG_UNSOL_MOBILE_WIFI_HANDOVER)
RFX_MSG_ID_EXPN(RFX_MSG_UNSOL_ACTIVE_WIFI_PDN_COUNT)
RFX_MSG_ID_EXPN(RFX_MSG_UNSOL_WIFI_RSSI_MONITORING_CONFIG)
RFX_MSG_ID_EXPN(RFX_MSG_UNSOL_WIFI_PDN_ERROR)
RFX_MSG_ID_EXPN(RFX_MSG_UNSOL_REQUEST_GEO_LOCATION)
RFX_MSG_ID_EXPN(RFX_MSG_URC_WFC_PDN_STATE)
RFX_MSG_ID_EXPN(RFX_MSG_UNSOL_NATT_KEEP_ALIVE_CHANGED)
RFX_MSG_ID_EXPN(RFX_MSG_UNSOL_WIFI_PING_REQUEST)
RFX_MSG_ID_EXPN(RFX_MSG_UNSOL_WIFI_PDN_OOS)
RFX_MSG_ID_EXPN(RFX_MSG_UNSOL_WIFI_LOCK)
RFX_MSG_ID_EXPN(RFX_MSG_UNSOL_SSAC_STATUS)
#endif