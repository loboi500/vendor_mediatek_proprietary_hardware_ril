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

#ifndef __RMC_COMM_SIM_URC_HANDLER_H__
#define __RMC_COMM_SIM_URC_HANDLER_H__

/*****************************************************************************
 * Include
 *****************************************************************************/
#include "RmcSimBaseHandler.h"

/*****************************************************************************
 * Class RpSimController
 *****************************************************************************/

class RmcCommSimUrcHandler : public RmcSimBaseHandler {
RFX_DECLARE_HANDLER_CLASS(RmcCommSimUrcHandler);

public:
    RmcCommSimUrcHandler(int slot_id, int channel_id);
    virtual ~RmcCommSimUrcHandler();

    // Process URC here
    virtual void handleUrc(const sp<RfxMclMessage>& msg, RfxAtLine *urc);

    // Check if the handler have to process the URC or not
    virtual RmcSimBaseHandler::SIM_HANDLE_RESULT needHandle(const sp<RfxMclMessage>& msg);

    // Return the list which you want to reqister
    virtual const char** queryUrcTable(int *record_num);

private:

    static int mTrayPluginCount;

    void handleCardType(const sp<RfxMclMessage>& msg, RfxAtLine *urc);
    void handleSimStateChanged(const sp<RfxMclMessage>& msg, char* urc);
    void handleEcpin(const sp<RfxMclMessage>& msg, RfxAtLine *urc);
    void handleSimIndication(const sp<RfxMclMessage>& msg, RfxAtLine *urc);
    void handleSimSlotLockStatusChanged(RfxAtLine *urc);
    void handleSimSlotStatusChanged(RfxAtLine *urc);
    bool isEnableUiccApplicationsSupported();
    void handleUiccApplicationsEnablementChanged(const sp<RfxMclMessage>& msg, char* urc);
    void handleIccidIndication(const sp<RfxMclMessage>& msg, RfxAtLine *urc);
    void onSmlConfigureCheck();
    void handleTestSimDetected(RfxAtLine *urc);
    void handleRsuEvent(const sp<RfxMclMessage>& msg, RfxAtLine *urc);
    void handleTmoRsuEvent(const sp<RfxMclMessage>& msg, RfxAtLine *urc);
    void handleSubsidyLockEvent(const char *urc);
    void handleAttRsuSimLockEvent(const sp<RfxMclMessage>& msg, char *urc);
};
#endif /* __RMC_COMM_SIM_URC_HANDLER_H__ */

