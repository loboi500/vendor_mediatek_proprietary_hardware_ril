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

#include "RfxCallFailCauseData.h"

RFX_IMPLEMENT_DATA_CLASS(RfxCallFailCauseData);

RfxCallFailCauseData::RfxCallFailCauseData(void *data, int length) : RfxBaseData(data, length)  {
    if (data == NULL) {
        m_data = NULL;
        return;
    }

    m_length = length;
    RIL_LastCallFailCauseInfo* pData = (RIL_LastCallFailCauseInfo*)data;
    RIL_LastCallFailCauseInfo* dupData;

    //Copy cause code
    dupData = (RIL_LastCallFailCauseInfo *)calloc(1, sizeof(RIL_LastCallFailCauseInfo));
    RFX_ASSERT(dupData != NULL);
    memset(dupData, 0x00, sizeof(RIL_LastCallFailCauseInfo));
    dupData->cause_code = pData->cause_code;

    //Copy vendor cause
    if (pData->vendor_cause != NULL) {
        int strLen = strlen(pData->vendor_cause);
        //Allocate and zero-initialize array
        dupData->vendor_cause = (char*)calloc(strLen + 1, sizeof(char));
        RFX_ASSERT(dupData->vendor_cause != NULL);
        strncpy(dupData->vendor_cause, pData->vendor_cause, strLen);
    }

    m_data = dupData;
 }

RfxCallFailCauseData::~RfxCallFailCauseData() {
    // free
    RIL_LastCallFailCauseInfo *tmp = (RIL_LastCallFailCauseInfo *)m_data;
    if (tmp != NULL) {
        if (tmp->vendor_cause != NULL) {
          free(tmp->vendor_cause);
        }
        free(tmp);
    }
    m_data = NULL;
}
