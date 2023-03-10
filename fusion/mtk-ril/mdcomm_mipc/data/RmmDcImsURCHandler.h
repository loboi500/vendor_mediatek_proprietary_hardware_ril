/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 *
 * MediaTek Inc. (C) 2018. All rights reserved.
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

#ifndef __RMM_DC_IMS_URC_HANDLER_H__
#define __RMM_DC_IMS_URC_HANDLER_H__

/*****************************************************************************
 * Include
 *****************************************************************************/
#include "RfxBaseHandler.h"
#include "RfxController.h"
#include "RfxStatusDefs.h"
#include "rfx_properties.h"

/*****************************************************************************
 * Class RmmDcImsURCHandler
 *****************************************************************************/
class RmmDcImsURCHandler : public RfxBaseHandler {
    RFX_DECLARE_HANDLER_CLASS(RmmDcImsURCHandler);

    public:
        RmmDcImsURCHandler(int slot_id, int channel_id);
        virtual ~RmmDcImsURCHandler();

    protected:
        virtual void onHandleRequest(const sp<RfxMclMessage>& msg);
        virtual void setLinkMaster(int action, int interfaceId, char *type);
        virtual void onHandleUrc(const sp<RfxMclMessage>& msg);
        // URC +EIMSPDN "notify" URC
        virtual void handleImsBearerNotify(const sp<RfxMclMessage>& msg);
        // Set flag to control "+EIMSPDN " notification to ap
        virtual void handleImsBearerNotification(const sp<RfxMclMessage>& msg);
        // Callback function when RmmDcUrcHandler URC registration ready
        virtual void setImsNotifySwitch();
        virtual void notifyImsBearerRequest(int requestId, RIL_IMS_BearerNotification* notification, bool isUpdateState);

        // handle unsynchronized scenario after phone process/ims service has been kill
        virtual void notifyUnsyncImsBearerRequest();
        // handle unsynchronized scenario after phone/ims service has been kill deu to phone decrypt
        virtual void checkImsServiceRestartAfterSystemCrash();
        // reset ims connection
        virtual void handleResetImsConnection(const sp<RfxMclMessage>& msg);
    private:
        int isEnableBearerNotification = 1;
};
#endif /* __RMM_DC_IMS_URC_HANDLER_H__ */

