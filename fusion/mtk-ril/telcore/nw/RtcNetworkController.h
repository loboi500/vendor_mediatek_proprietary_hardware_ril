/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 *
 * MediaTek Inc. (C) 2017. All rights reserved.
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

#ifndef __RTC_NETWORK_CONTROLLER_H__
#define __RTC_NETWORK_CONTROLLER_H__

/*****************************************************************************
 * Include
 *****************************************************************************/
#include "RfxController.h"
#include <telephony/mtk_ril.h>
#include "rfx_properties.h"
#include "RfxVoidData.h"
#include "RfxNetworkScanResultData.h"
#include "nw/RtcRatSwitchController.h"
#include "RfxDataRegStateData.h"

/*****************************************************************************
 * Define
 *****************************************************************************/


/*****************************************************************************
 * Class RfxController
 *****************************************************************************/
class RtcNetworkController : public RfxController {
    RFX_DECLARE_CLASS(RtcNetworkController);

public:
    RtcNetworkController();
    virtual ~RtcNetworkController();

protected:
    virtual bool onHandleRequest(const sp<RfxMessage>& message);
    virtual bool onHandleUrc(const sp<RfxMessage>& message);
    virtual bool onHandleResponse(const sp<RfxMessage>& message);
    virtual void onInit();

    virtual bool onCheckIfRejectMessage(const sp<RfxMessage>& message,
        bool isModemPowerOff,int radioState);
    virtual bool onPreviewMessage(const sp<RfxMessage>& message);
    virtual bool onCheckIfResumeMessage(const sp<RfxMessage>& message);

    void onHandleModemReset(RfxStatusKeyEnum key, RfxVariant old_value,
        RfxVariant value);
    void onLocalAbortAvailableNetworkDone();
    bool isAPInCall();
    bool isNRSwitching();
    void onPreferredNwTypeChange(int slotId, RfxStatusKeyEnum key,
        RfxVariant old_value, RfxVariant value);
    void onHandleNrSwitchSlotChanged(RfxStatusKeyEnum key, RfxVariant old_value,
            RfxVariant value);

    void onRadioStateChanged(int slotId, RfxStatusKeyEnum key, RfxVariant old_value,
            RfxVariant value);

    void onHandleInCallEvent(RfxStatusKeyEnum key, RfxVariant old_value,
        RfxVariant value);

private:
    bool mNetworkScanOngoing;
    bool mForceStopNetworkScan;
    bool mNetworkScanPending;
    bool mCancelNetworkScanPending;
    bool mStopNetworkScan;
    bool mFakeoosSupport;//true: if non-data sim is in call, data sim's ps state will set as oos
    sp<RfxMessage> mNwScanMessage;
    int mSignalReqToken;

    // nr info
    int isDcNrRestricted;
    int isEndcAvailable;
    int isNrAvailable;

    bool inCall;
};
#endif /* __RTC_NETWORK_CONTROLLER_H__ */
