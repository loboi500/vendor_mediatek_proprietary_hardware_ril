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

#ifndef __RMM_RADIO_REQUEST_HANDLER_H__
#define __RMM_RADIO_REQUEST_HANDLER_H__

#include "RfxBaseHandler.h"
#include "platform.h"

class RmmRadioRequestHandler : public RfxBaseHandler {
    RFX_DECLARE_HANDLER_CLASS(RmmRadioRequestHandler);

    public:
        RmmRadioRequestHandler(int slotId, int channelId);
        virtual ~RmmRadioRequestHandler();

    protected:
        virtual void onHandleRequest(const sp<RfxMclMessage>& msg);

        virtual void onHandleTimer();

        virtual void onHandleEvent(const sp<RfxMclMessage>& msg);

    private:
        void requestRadioPower(const sp<RfxMclMessage> &msg);

        void bootupSetRadioPower(const sp<RfxMclMessage> &msg);

        bool isUnderCryptKeeper();

        void initMdStatusReader();
        static void getResetLock();
        static void releaseResetLock();
        static void* mdStatusReaderLoop(void* params);
        static void mdStatusEventCb(void *priv_ptr, struct md_status_event_t *event_ptr);
        static void sendUrcToTelCor(char* buffer);

        mipc_result_const_enum sendMipcRequest(int slot, int onOff, int caller);

    private:
        pthread_t mMdStatsuReaderThread;
        static int sMdStatusEventType;

        /// M: CC: ECC related handling @{
        void handleEccIndication(int slot, int onOff, int forEcc, int preEcc);
        void setEccPowerOnStatus(bool isOnForEcc);
        bool getEccPowerOnStatus();
        void updateEccPhone(int slotId, int preEcc);
        /// @}
};
#endif
