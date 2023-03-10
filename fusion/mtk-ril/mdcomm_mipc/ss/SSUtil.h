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

#ifndef SS_UTIL
#define SS_UTIL

#include <vector>
#include <string>
#include <telephony/ril.h>

#include "RfxDefs.h"
#include "SuppServDef.h"
#include "mipc_msg_tlv_const.h"

using namespace std;

#define UNUSED(x) ((void)(x))

const char *InfoClassToMmiBSCodeString (AtInfoClassE infoClass);
int         MmiBSCodeToInfoClassX (int serviceCode, int ssServiceClassFeature);
const char *ssStatusToOpCodeString(SsStatusE status);
char*       convertToUCS2(char* data);
const char *callBarFacToServiceCodeStrings(const char * fac);
GsmCbsDcsE  checkCbsDcs(int dcs);
const char *callForwardReasonToServiceCodeString(CallForwardReasonE cfreason);
void        setErrorMessageFromXcap(int slotId, AT_CME_Error errorCode, const char* message);
void        clearErrorMessageFromXcap(int slotId);
bool        isReallyDialable(char c);
bool        isStartsPostDial(char c);
char*       extractNetworkPortionAlt(char* phoneNumber);
char*       encryptString(char* input);
bool        startsWith(const string& target, const string& origin);
char*       replaceSetCFNumberIfNeeded(char* phoneNumber, const char* mccmnc);
char*       replaceGetCFNumberIfNeeded(char* phoneNumber, const char* mccmnc);

uint8_t ssReasonToMipcReasonCode(CallForwardReasonE cfReason);
int mipcReasonCodeToSsReason(uint8_t cfReason);
uint8_t     ssStatusToMipcOpCode(SsStatusE status);
int         callBarFacToServiceCode(const char * fac);
RIL_Errno   convertMipcResultToRil(const char *logTag, mipc_result_const_enum mipcRet);

#endif /* SS_UTIL */
