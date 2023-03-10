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

#ifndef __RMM_CALL_CONTROL_URC_HANDLER_H__
#define __RMM_CALL_CONTROL_URC_HANDLER_H__

#include "RmmCallControlBaseHandler.h"

class RmmCallControlUrcHandler : public RmmCallControlBaseHandler {
    RFX_DECLARE_HANDLER_CLASS(RmmCallControlUrcHandler);

    public:
        RmmCallControlUrcHandler(int slot_id, int channel_id);
        virtual ~RmmCallControlUrcHandler();

        static int getSpeechCodec();
        static void resetSpeechCodec();

    protected:
        virtual void onHandleUrc(const sp<RfxMclMessage>& msg);

    private:
        void handleCallProgressIndicationMessage(const sp<RfxMclMessage>& msg);
        void handleCallEventIndicationMessage(const sp<RfxMclMessage>& msg);
        void handleRingMessage(const sp<RfxMclMessage>& msg);
        void handleEspeechMessage(const sp<RfxMclMessage>& msg);
        void handleCipherIndicationMessage(const sp<RfxMclMessage>& msg);
        void handleSpeechCodecInfo(const sp<RfxMclMessage>& msg);
        void handleCrssNotification(const sp<RfxMclMessage>& msg);
        void handleSuppSvcNotification(const sp<RfxMclMessage>& msg);
        void sendRingbackToneNotification(int isStart);
        void handleECPI(int callId, int msgType, int isIbt);
        bool shoudNotifyCallInfo(int msgType);
        bool shouldNotifyCallStateChanged(int msgType);
        void handleRedirectNumber(const sp<RfxMclMessage>& msg);

        /// C2K specific start
        void handleNoCarrierMessage();
        void handleCdmaCallingPartyNumberInfoMessage(char *number,
                int numberType, int numberPresentation);
        void handleCdmaRedirectingNumberInfoMessage(const sp<RfxMclMessage>& msg);
        void handleLineControlInfoMessage(const sp<RfxMclMessage>& msg);
        void handleExtendedDisplayInfoMessage(const sp<RfxMclMessage>& msg);
        void handleDisplayAndSignalsInfoMessage(const sp<RfxMclMessage>& msg);
        void handleSignalsInfoMessage(const sp<RfxMclMessage>& msg);
        void handleEmergencyCallbackModeMessage(const sp<RfxMclMessage>& msg);
        void handleCdmaCallWaitingMessage(char *number, int numberType);
        void handleWpsTrafficChannelAssigned();
        /// C2K specific end

        /// IMS specific start
        void handleConfSrvcc(const sp<RfxMclMessage>& msg);
        void handleSipMsgIndication(const sp<RfxMclMessage>& msg);
        void handleConfModifiedResult(const sp<RfxMclMessage>& msg);
        void handleCallModeChanged(const sp<RfxMclMessage>& msg);
        void handleECT(const sp<RfxMclMessage>& msg);
        void handleImsEventPackage(const sp<RfxMclMessage>& msg);
        void handleImsConfInfoUpdate(const sp<RfxMclMessage>& msg);
        void handleSrvccStateChange(const sp<RfxMclMessage>& msg);
        void notifySrvccState(int state);
        void handleCallRatChange(const sp<RfxMclMessage>& msg);
        void handleRedialEmergencyIndication(const sp<RfxMclMessage>& msg);
        void handleImsHeaderInfo(const sp<RfxMclMessage>& msg);
        void handleCallAdditionalInfo(const sp<RfxMclMessage>& msg);
        void handleMDInternetUsage(const sp<RfxMclMessage>&msg);
        /// IMS specific end

        char atLog[MAX_AT_RESPONSE] = { 0 };

        enum {
            STOP_RING_BACK_TONE = 0,
            START_RING_BACK_TONE,
        };

        enum {
            CRSS_CALL_WAITING,
            CRSS_CALLED_LINE_ID_PREST,
            CRSS_CALLING_LINE_ID_PREST,
            CRSS_CONNECTED_LINE_ID_PREST
        };

        enum {
            SUPP_SVC_CSSI,
            SUPP_SVC_CSSU
        };

        typedef enum {
            VOICE = 0,
            VT = 10,
            VOLTE = 20,
            VILTE = 21,
            VOLTE_CONF = 22,
        } Call_Mode;

        /// C2K specific start
        enum {
           IDLE,
           CONNECTED,
           DIALING,
           INCOMING,
           WAITING,
        };

        int mCallState = IDLE;
        const int DISPLAY_TAG_CALLING_PARTY_NAME = 0x8D;
        const int DISPLAY_TAG_ORIG_CALLED_NAME = 0x8F;

        int mCachedSignal = 0;
        String8 mCachedWaitingCallNumber;
        const int SIGNAL_TONES_OFF = 0x3F;
        /// @}

        int mIsRingBackTonePlaying = 0;

        /**
         *   MtkSpeechCodecTypes
         *     NONE(0),
         *     QCELP13K(0x0001),
         *     EVRC(0x0002),
         *     EVRC_B(0x0003),
         *     EVRC_WB(0x0004),
         *     EVRC_NW(0x0005),
         *     AMR_NB(0x0006),
         *     AMR_WB(0x0007),
         *     GSM_EFR(0x0008),
         *     GSM_FR(0x0009),
         *     GSM_HR(0x000A);
         */
        static int mSpeechCodec;
};
#endif
