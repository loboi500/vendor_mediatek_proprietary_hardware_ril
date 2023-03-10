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

#ifndef __RMC_IMS_CONTROL_REQUEST_HANDLER_H__
#define __RMC_IMS_CONTROL_REQUEST_HANDLER_H__

#include "RfxBaseHandler.h"
#include "RfxIntsData.h"
#include "RfxVoidData.h"
#include "RfxStringData.h"
#include "RfxStringsData.h"
#include "RfxMessageId.h"

#define RFX_LOG_TAG "RmcImsCtlReqHdl"

#define MAX_MD_CFGTYPE_NUM 3
#define MAX_MD_CFG_KEY_LEN 63
#define MAX_MD_CFG_VAL_LEN 255

typedef enum {
    ECFGSET = 0,
    EWOCFGSET = 1,
    EIWLCFGSET = 2
} MD_CFGTYPE;
static const char* cfgAtCmd[] = {"AT+ECFGSET", "AT+EWOCFGSET", "AT+EIWLCFGSET"};

class RmcImsControlRequestHandler : public RfxBaseHandler {
    RFX_DECLARE_HANDLER_CLASS(RmcImsControlRequestHandler);
    private:
        String8 userAgentformat;

    public:
        RmcImsControlRequestHandler(int slot_id, int channel_id);
        virtual ~RmcImsControlRequestHandler();

    protected:
        virtual void onHandleRequest(const sp<RfxMclMessage>& msg);

    private:
        //void requestSetVolteEnabled(const sp<RfxMclMessage>& msg);
        //void requestSetWfcEnabled(const sp<RfxMclMessage>& msg);
        //void requestSetVilteEnabled(const sp<RfxMclMessage>& msg);
        //void requestSetViwifiEnabled(const sp<RfxMclMessage>& msg);
        void requestSetImsCfg(const sp<RfxMclMessage>& msg);
        void requestSetModemImsCfg(const sp<RfxMclMessage>& msg);
        void requestSendWfcProfile(const sp<RfxMclMessage>& msg);
        void enableImsRegistrationReport(const sp<RfxMclMessage>& msg);
        void requestImsRegistrationState(const sp<RfxMclMessage>& msg);
        void requestSetImsEnabled(const sp<RfxMclMessage>& msg);
        void requestImsDereg(const sp<RfxMclMessage>& msg);
        void enableImsEccSupportReport();
        void requestSetImsRtpReport(const sp<RfxMclMessage>& msg);
        void requestMultiImsSupportCount();
        void enableImsRcsStateFeature();
        void enableVoPSUrc();
        void enableSipRegInfoInd();
        void requestSetSipUserAgent();
        bool isCurrentSlotSupportIms();
        void queryVopsStatus(const sp<RfxMclMessage>& msg);
        void enableVopsStatusReport();
};

#endif
