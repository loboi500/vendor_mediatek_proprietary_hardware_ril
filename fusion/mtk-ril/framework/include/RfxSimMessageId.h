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

#ifndef __RFX_SIM_MESSAGE_ID_HEADER__
#define __RFX_SIM_MESSAGE_ID_HEADER__

RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_GET_SIM_STATUS)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_ENTER_SIM_PIN)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_ENTER_SIM_PUK)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_ENTER_SIM_PIN2)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_ENTER_SIM_PUK2)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_CHANGE_SIM_PIN)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_CHANGE_SIM_PIN2)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SIM_IO)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_ISIM_AUTHENTICATION)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_GENERAL_SIM_AUTH)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SIM_OPEN_CHANNEL)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SET_SIM_CARD_POWER)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_ENABLE_UICC_APPLICATIONS)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_ARE_UICC_APPLICATIONS_ENABLED)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SIM_CLOSE_CHANNEL)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SIM_TRANSMIT_APDU_BASIC)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SIM_TRANSMIT_APDU_CHANNEL)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SIM_GET_ATR)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SIM_GET_ICCID)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SIM_AUTHENTICATION)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_GET_IMSI)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_QUERY_FACILITY_LOCK)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SET_FACILITY_LOCK)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_CDMA_SUBSCRIPTION)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_CDMA_GET_SUBSCRIPTION_SOURCE)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SIM_ENTER_NETWORK_DEPERSONALIZATION)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SIM_QUERY_SIM_NETWORK_LOCK)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SIM_SET_SIM_NETWORK_LOCK)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SIM_ENTER_DEPERSONALIZATION)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SIM_USIM_AUTHENTICATION)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SIM_OPEN_ICC_APPLICATION)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SIM_GET_ICC_APPLICATION_STATUS)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SIM_IO_EX)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SET_SIM_POWER)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_LOCAL_SIM_SAP_RESET)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SIM_SAP_CONNECT)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SIM_SAP_DISCONNECT)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SIM_SAP_APDU)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SIM_SAP_TRANSFER_ATR)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SIM_SAP_POWER)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SIM_SAP_RESET_SIM)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SIM_SAP_SET_TRANSFER_PROTOCOL)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SIM_SAP_ERROR_RESP)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SET_ALLOWED_CARRIERS)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_GET_ALLOWED_CARRIERS)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SIM_VSIM_NOTIFICATION)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SIM_VSIM_OPERATION)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_GET_SUBLOCK_MODEM_STATUS)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_UPDATE_SUBLOCK_SETTINGS)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_ENTER_SIM_DEPERSONALIZATION)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SML_RSU_REQUEST)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_GET_SUBLOCK_VERSION)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_GET_SUBLOCK_UNLOCK_TIME)
RFX_MSG_ID_EXPN(RFX_MSG_URC_RESPONSE_SIM_STATUS_CHANGED)
RFX_MSG_ID_EXPN(RFX_MSG_URC_SIM_COMMON_SLOT_NO_CHANGED)
RFX_MSG_ID_EXPN(RFX_MSG_URC_TRAY_PLUG_IN)
RFX_MSG_ID_EXPN(RFX_MSG_URC_SIM_PLUG_OUT)
RFX_MSG_ID_EXPN(RFX_MSG_URC_SIM_PLUG_IN)
RFX_MSG_ID_EXPN(RFX_MSG_URC_UICC_SUBSCRIPTION_STATUS_CHANGED)
RFX_MSG_ID_EXPN(RFX_MSG_URC_UICC_APPLICATIONS_ENABLEMENT_CHANGED)
RFX_MSG_ID_EXPN(RFX_MSG_URC_SIM_MISSING)
RFX_MSG_ID_EXPN(RFX_MSG_URC_SIM_RECOVERY)
RFX_MSG_ID_EXPN(RFX_MSG_URC_SIM_VIRTUAL_SIM_ON)
RFX_MSG_ID_EXPN(RFX_MSG_URC_SIM_VIRTUAL_SIM_OFF)
RFX_MSG_ID_EXPN(RFX_MSG_URC_SIM_IMEI_LOCK)
RFX_MSG_ID_EXPN(RFX_MSG_URC_SIM_APPLICATION_SESSION_ID_CHANGED)
RFX_MSG_ID_EXPN(RFX_MSG_URC_SIM_EUSIM_READY)
RFX_MSG_ID_EXPN(RFX_MSG_URC_SIM_VSIM_OPERATION_INDICATION)
RFX_MSG_ID_EXPN(RFX_MSG_URC_SIM_IMSI_REFRESH_DONE)
RFX_MSG_ID_EXPN(RFX_MSG_URC_SIM_SAP_STATUS)
RFX_MSG_ID_EXPN(RFX_MSG_URC_SIM_INIT_STATUS)
RFX_MSG_ID_EXPN(RFX_MSG_UNSOL_SML_RSU_EVENT)
RFX_MSG_ID_EXPN(RFX_MSG_EVENT_SIM_QUERY_ICCID)
RFX_MSG_ID_EXPN(RFX_MSG_EVENT_SIM_DETECT_SIM)
RFX_MSG_ID_EXPN(RFX_MSG_EVENT_SIM_SIM_AUTHENTICATION)
RFX_MSG_ID_EXPN(RFX_MSG_EVENT_SIM_USIM_AUTHENTICATION)
RFX_MSG_ID_EXPN(RFX_MSG_EVENT_SIM_RILD_READ_IMSI)
RFX_MSG_ID_EXPN(RFX_MSG_EVENT_SIM_VSIM_PLUG_OUT)
RFX_MSG_ID_EXPN(RFX_MSG_EVENT_SIM_VSIM_AUTH_REQUEST)
RFX_MSG_ID_EXPN(RFX_MSG_EVENT_SIM_VSIM_RELEASE_AKA_SIM)
RFX_MSG_ID_EXPN(RFX_MSG_EVENT_SIM_VSIM_SEND_ERROR_RESPONSE)
RFX_MSG_ID_EXPN(RFX_MSG_URC_SIM_SLOT_LOCK_POLICY_NOTIFY)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SIM_ENTER_DEVICE_NETWORK_DEPERSONALIZATION)
RFX_MSG_ID_EXPN(RFX_MSG_URC_SIM_POWER_CHANGED)
RFX_MSG_ID_EXPN(RFX_MSG_URC_CARD_DETECTED_IND)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_GET_SLOT_STATUS)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SET_LOGICAL_TO_PHYSICAL_SLOT_MAPPING)
RFX_MSG_ID_EXPN(RFX_MSG_URC_ICC_SLOT_STATUS)
RFX_MSG_ID_EXPN(RFX_MSG_EVENT_GET_SLOT_STATUS)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_ACTIVATE_UICC_CARD)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_DEACTIVATE_UICC_CARD)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_GET_CURRENT_UICC_CARD_PROVISIONING_STATUS)
RFX_MSG_ID_EXPN(RFX_MSG_EVENT_VSIM_RELEASE_RF)
RFX_MSG_ID_EXPN(RFX_MSG_URC_ICCID_CHANGED)
RFX_MSG_ID_EXPN(RFX_MSG_EVENT_SIM_RESET)
RFX_MSG_ID_EXPN(RFX_MSG_EVENT_SIM_QUERY_EONS)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_CLIENT_RSU)
#endif
