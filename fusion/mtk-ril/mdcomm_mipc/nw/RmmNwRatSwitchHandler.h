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

#ifndef __RMM_NW_RAT_SWITCH_HANDLER_H__
#define __RMM_NW_RAT_SWITCH_HANDLER_H__

#include "RmmNwHandler.h"
#include "libmtkrilutils.h"

typedef enum {
    RAT_GSM =  (1 <<  0),
    RAT_UMTS = (1 << 1),
    RAT_LTE = (1 << 2),
    RAT_NR = (1 << 3),
    RAT_C2K = (1 << 4)
} MIPC_RAT;

#define RAT_GSM_BIT_GROUP (RAT_GSM | RAT_UMTS | RAT_LTE | RAT_NR)
#define RAT_CDMA_BIT_GROUP (RAT_C2K)

/* Define the network selecting mode. */
typedef enum {
    NWS_MODE_UNKNOWN    = -1, // for CSFB (GSM) network selecting mode
    NWS_MODE_CDMALTE    = 0,  // for CDMALTE (CDMA) network selecting mode
    NWS_MODE_CSFB       = 1,  // for CSFB (GSM) network selecting mode
} NwsMode;

typedef enum {
    SWITCH_RAT,
    GMSS_RAT
} PHONE_CHANGE_SOURCE;

/* Define the network selecting mode for NR extend. */
typedef enum {
    EXTEND_GMSS_RAT_INVALID  = 0,     // Invalid  RAT
    EXTEND_GMSS_RAT_GSM      = 1 << 0,    // GERAN (GSM)
    EXTEND_GMSS_RAT_WCDMA    = 1 << 1,    // UTRAN (WCDMA)
    EXTEND_GMSS_RAT_LTE      = 1 << 2,    // EUTRAN (LTE)
    EXTEND_GMSS_RAT_C2K1X    = 1 << 5,    // CDMA2000 1x
    EXTEND_GMSS_RAT_C2KHRPD  = 1 << 6,    // CDMA2000 HRPD
    EXTEND_GMSS_RAT_NR       = 1 << 7     // NR
} ExtendedGmssRat;

/* Define the GMSS status. */
typedef enum {
    GMSS_STATUS_SELECT,   // GMSS select.
    GMSS_STATUS_ATTACHED, // GMSS attached.
    GMSS_STATUS_ECC       // GMSS ECC.
} GmssStatus;

/*  <MSPL_set> integer type;
 *  The set(no priority) of Multimode System Selection (MMSS) System Priority List.
 *  Enum specified as:
 *  RAT_NONE              = 0,
 *  RAT_GSM               = 1,
 *  RAT_UMTS              = 2,
 *  RAT_GSM_UMTS          = RAT_GSM | RAT_UMTS,                    // 3
 *  RAT_LTE               = 4,
 *  RAT_GSM_LTE           = RAT_GSM | RAT_LTE,                     // 5
 *  RAT_UMTS_LTE          = RAT_UMTS | RAT_LTE,                    // 6
 *  RAT_GSM_UMTS_LTE      = RAT_GSM | RAT_UMTS | RAT_LTE,          // 7
 *  RAT_COM_GSM           = 8,
 *  RAT_C2K               = 16,
 *  RAT_GSM_C2K           = RAT_GSM | RAT_C2K,                     // 17
 *  RAT_UMTS_C2K          = RAT_UMTS | RAT_C2K,                    // 18
 *  RAT_GSM_UMTS_C2K      = RAT_GSM | RAT_UMTS | RAT_C2K,          // 19
 *  RAT_LTE_C2K           = RAT_LTE | RAT_C2K,                     // 20
 *  RAT_GSM_LTE_C2K       = RAT_GSM | RAT_LTE | RAT_C2K,           // 21
 *  RAT_UMTS_LTE_C2K      = RAT_UMTS | RAT_LTE | RAT_C2K,          // 22
 *  RAT_GSM_UMTS_LTE_C2K  = RAT_GSM | RAT_UMTS | RAT_LTE | RAT_C2K // 23
 *  RAT_1xRTT             = 32,
 *  RAT_HRPD              = 64,
 *  RAT_1xRTT_HRPD        = RAT_1xRTT | RAT_HRPD                   // 96
 */

typedef enum {
    MSPL_RAT_NONE     = 0,
    MSPL_RAT_GSM      = 1 << 0,  // 1
    MSPL_RAT_UMTS     = 1 << 1,  // 2
    MSPL_RAT_LTE      = 1 << 2,  // 4
    MSPL_RAT_COM_GSM  = 1 << 3,  // 8
    MSPL_RAT_C2K      = 1 << 4,  // 16
    MSPL_RAT_1xRTT    = 1 << 5,  // 32
    MSPL_RAT_HRPD     = 1 << 6,  // 64
    MSPL_RAT_NR       = 1 << 7   // 128
} MSPL;

typedef struct {
    int32_t rat;
    int32_t mcc;
    int32_t status;
    int32_t mspl;
    int32_t ishome;
} GmssInfo;

class RmmNwRatSwitchHandler : public RmmNwHandler {
    RFX_DECLARE_HANDLER_CLASS(RmmNwRatSwitchHandler);

    public:
        RmmNwRatSwitchHandler(int slot_id, int channel_id);
        virtual ~RmmNwRatSwitchHandler();

    protected:
        virtual void onHandleRequest(const sp<RfxMclMessage>& msg);
        virtual void onHandleResponse(const sp<RfxMclMessage>& msg);
        virtual void onHandleUrc(const sp<RfxMclMessage>& msg) {RFX_UNUSED(msg);}
        virtual void onHandleEvent(const sp<RfxMclMessage>& msg);

    private:
        void handleSetPreferredNetworkTypeRequest(const sp<RfxMclMessage>& msg);

        void handleGetPreferredNetworkTypeRequest(const sp<RfxMclMessage>& msg);
        void handleGetPreferredNetworkTypeResponse(const sp<RfxMclMessage>& msg);

        void handleStopNetworkScan(const sp<RfxMclMessage>& msg);
        void handleAbortQueryAvailableNetworks(const sp<RfxMclMessage>& msg);

        void handleVoiceRadioTechRequest(const sp<RfxMclMessage>& msg);

        void handleGetGmssRatModeRequest(const sp<RfxMclMessage>& msg);
        void handleGetGmssRatModeResponse(const sp<RfxMclMessage>& msg);

        void handleUpdatePhoneModeRequest(const sp<RfxMclMessage>& msg);

        void handleCurrentRatChangedEvent(const sp<RfxMclMessage>& msg);
        void handleEgmssInfoChangedEvent(const sp<RfxMclMessage>& msg);

        bool isRatPreferred();
        void updateGmssRatMode();
        void handleGmssRat(GmssInfo gmssInfo);
        void updatePhoneMode(PHONE_CHANGE_SOURCE source);
        bool isCurrentRatContainGsm();
        bool isCurrentRatContainCdma();
        bool isCdmaDualModeSimCard();
        bool isGsmOnlySim();
        bool isCT4GCard();
        void setNwsMode(NwsMode mode);
        void setIntSysProp(char *propName, int val);
        int getIntSysProp(char *propName, int defaultVal);
        int convertNetworkType(int nt_type, int prefer_type);
        int isGcfTestMode();
        int isTestSim(int slotId);
        int disable2GOption(int reqType);


    protected:
        int m_slot_id;
        int m_channel_id;

    private:
        int mCurRatBit;
        int mCurPreferedNetWorkType;
        int mPhoneMode;
        NwsMode mNwsMode;
        bool mDisable2GWithRat;

};

#endif
