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

#ifndef __RTM_IMS_SMS_CONTROLLER_H__
#define __RTM_IMS_SMS_CONTROLLER_H__

/*****************************************************************************
 * Include
 *****************************************************************************/
#include "RfxController.h"
#include "RtmGsmSmsController.h"
#include "RtmCdmaSmsController.h"
#include "RtmConcatSms.h"
#include "RtmSmsMessage.h"
#include "utils/Vector.h"

/*****************************************************************************
 * Class RpSimController
 *****************************************************************************/

class RtmImsSmsController : public RfxController {
RFX_DECLARE_CLASS(RtmImsSmsController);

public:
    RtmImsSmsController();
    virtual ~RtmImsSmsController();

public:
    bool removeReferenceIdCached(int ref);
    void addReferenceId(int ref);
    int getCacheSize();
    RtmConCatSmsRoot *getConCatSmsRoot() {
        return mConCatSmsRoot;
    }
    void sendCdmaSms(RtmCdmaSmsMessage *msg);
    void sendGsmSms(RtmGsmSmsMessage *msg);
    void sendCdmaSmsAck(const sp<RfxMessage>& message);
    void sendGsmSmsAck(int success, int cause, const sp<RfxMessage>& message);
    bool isSupportSmsFormatConvert();

// Override
protected:
    virtual void onInit();
    virtual bool onHandleRequest(const sp<RfxMessage>& message);
    virtual bool onCheckIfRejectMessage(
            const sp<RfxMessage>& message, bool isModemPowerOff, int radioState);
    virtual bool onPreviewMessage(const sp<RfxMessage>& message);
    virtual bool onCheckIfResumeMessage(const sp<RfxMessage>& message);

private:
    void setTag(String8 tag) {mTag = tag;}
    bool hasImsCall();
    bool isCdmaRat();
    bool isInCall();
    bool isInCdmaCall();

private:
    String8 mTag;
    RtmGsmSmsController *mGsmCtrl;
    RtmCdmaSmsController *mCdmaCtrl;
    RtmConCatSmsRoot *mConCatSmsRoot;
    Vector<int> mImsSmsRefIdVector; //only store ims sms reference id

};
#endif /* __RTM_IMS_SMS_CONTROLLER_H__ */
