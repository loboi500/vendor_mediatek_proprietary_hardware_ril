/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 *
 * MediaTek Inc. (C) 2010. All rights reserved.
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
#include "RfxPreciseCallState.h"

/*****************************************************************************
 * Class RfxPreciseCallState
 *****************************************************************************/

RfxPreciseCallState::RfxPreciseCallState() :
        mSlot(-1),
        mCallId(-1),
        mCallType(CALL_TYPE_NONE),
        mCallRat(CALL_RAT_NONE),
        mCallDir(CALL_DIR_NONE),
        mCallNumber(""),
        mOrigState(ORIG_NONE) {
}

RfxPreciseCallState::~RfxPreciseCallState() {
}

OrigState RfxPreciseCallState::RILStateToOrigState(RIL_CallState state) {
    switch (state) {
        case RIL_CALL_ACTIVE: return ORIG_ACTIVE;
        case RIL_CALL_HOLDING: return ORIG_HOLDING;
        case RIL_CALL_DIALING: return ORIG_DIALING;
        case RIL_CALL_ALERTING: return ORIG_ALERTING;
        case RIL_CALL_INCOMING: return ORIG_INCOMING;
        case RIL_CALL_WAITING: return ORIG_WAITING;
        default: return ORIG_NONE;
    }
}

bool RfxPreciseCallState::isValid() {
    return (mSlot > -1 &&
            mCallId > 0 &&
            mCallType != CALL_TYPE_NONE &&
            mCallRat != CALL_RAT_NONE &&
            mCallDir != CALL_DIR_NONE &&
            mOrigState != ORIG_NONE);
}

void RfxPreciseCallState::dump() {
    RLOGD("[PreciseCallState] slot:%d, id:%d, type:%d, rat:%d, dir:%d, number:%s, orig:%d",
            mSlot, mCallId, mCallType, mCallRat, mCallDir,
            String8(mCallNumber).string(), mOrigState);
}

