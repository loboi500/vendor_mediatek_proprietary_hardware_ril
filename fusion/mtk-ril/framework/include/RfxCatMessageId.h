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

#ifndef __RFX_CAT_MESSAGE_ID_HEADER__
#define __RFX_CAT_MESSAGE_ID_HEADER__

RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_STK_SEND_ENVELOPE_COMMAND)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_STK_SEND_TERMINAL_RESPONSE)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_STK_HANDLE_CALL_SETUP_REQUESTED_FROM_SIM)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_STK_HANDLE_CALL_SETUP_REQUESTED_FROM_SIM_WITH_RESULT_CODE)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_REPORT_STK_SERVICE_IS_RUNNING)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_STK_SEND_ENVELOPE_WITH_STATUS)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_STK_SEND_RESPONSE_BY_CMDTYPE)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_STK_EVENT_NOTIFY)
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_STK_QUERY_CPIN_STATE)

RFX_MSG_ID_EXPN(RFX_MSG_URC_STK_SESSION_END)
RFX_MSG_ID_EXPN(RFX_MSG_URC_STK_PROACTIVE_COMMAND)
RFX_MSG_ID_EXPN(RFX_MSG_URC_STK_EVENT_NOTIFY)
RFX_MSG_ID_EXPN(RFX_MSG_URC_STK_CALL_SETUP)
RFX_MSG_ID_EXPN(RFX_MSG_URC_SIM_REFRESH)
RFX_MSG_ID_EXPN(RFX_MSG_URC_STK_CC_ALPHA_NOTIFY)
RFX_MSG_ID_EXPN(RFX_MSG_URC_STK_SETUP_MENU_RESET)
RFX_MSG_ID_EXPN(RFX_MSG_URC_STK_CALL_CTRL)
RFX_MSG_ID_EXPN(RFX_MSG_URC_STK_TRIGGER_OTASP)
RFX_MSG_ID_EXPN(RFX_MSG_URC_STK_CPIN_STATE)

RFX_MSG_ID_EXPN(RFX_MSG_EVENT_STK_IS_RUNNING)
RFX_MSG_ID_EXPN(RFX_MSG_EVENT_STK_NOTIFY)
RFX_MSG_ID_EXPN(RFX_MSG_EVENT_STK_QUERY_CPIN_STATE)
// BIP @{
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_BIP_SEND_CONFIRM_INFO)
// BIP @}
// BTSAP @{
RFX_MSG_ID_EXPN(RFX_MSG_REQUEST_SIM_SAP_TRANSFER_CARD_READER_STATUS)
// BTSAP @}
#endif

