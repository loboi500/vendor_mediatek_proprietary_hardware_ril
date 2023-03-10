/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 *
 * MediaTek Inc. (C) 2019. All rights reserved.
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

#ifndef __RTC_NR_SWITCH_CONTROLLER_H__
#define __RTC_NR_SWITCH_CONTROLLER_H__

/*****************************************************************************
 * Include
 *****************************************************************************/
#include "RfxController.h"
#include <telephony/mtk_ril.h>
#include "rfx_properties.h"
#include "RfxIntsData.h"
#include "nw/RtcRatSwitchController.h"
#include "capabilityswitch/RtcCapabilitySwitchChecker.h"

/*****************************************************************************
 * Define
 *****************************************************************************/

#define SIM_OFF      (10)
#define SIM_ON       (11)

/*****************************************************************************
 * Class RfxController
 *****************************************************************************/
class RtcNrSwitchController : public RfxController {
    RFX_DECLARE_CLASS(RtcNrSwitchController);

public:
    RtcNrSwitchController();
    virtual ~RtcNrSwitchController();

protected:
    virtual bool onHandleResponse(const sp<RfxMessage>& message);
    virtual void onInit();

    void responseNrSwitch(const sp<RfxMessage>& response);
    int getNrSlot();
    void switchNrSlot();
    void switchNrSlot(int nrSlot);

    void onDefaultDataChanged(RfxStatusKeyEnum key, RfxVariant old_value,
            RfxVariant value);
    void onCapabilitySwitchStatusChanged(RfxStatusKeyEnum key, RfxVariant old_value,
            RfxVariant value);
    void onApVoiceCallCountChanged(int slotId, RfxStatusKeyEnum key,
        RfxVariant old_value, RfxVariant value);
    void onNrSwitchRetry(RfxStatusKeyEnum key, RfxVariant old_value,
            RfxVariant value);

    void onLocalAbortAvailableNetworkDone();
    int isNetworkScanOngoing();
    bool isNRSwitching();

    bool simStateReady();
    int getSimOnOffState(int slot_id);

protected:
    RtcCapabilitySwitchChecker* mCheckerController;
    int mNrSlot;
    int mPreferredDataSlot;
    bool mTriggerRetry;
    int mCapaNoNeed;
};
#endif /* __RTC_NR_SWITCH_CONTROLLER_H__ */
