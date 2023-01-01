/*
 * Copyright (c) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef RIL_SERVICE_H
#define RIL_SERVICE_H

#include <telephony/mtk_ril.h>
#include <ril_internal.h>

namespace radio {
void registerService(RIL_RadioFunctions *callbacks, android::CommandInfo *commands);

int getIccCardStatusResponse(unsigned int slotId, android::ClientId clientId, int responseType,
                            int token, RIL_Errno e, void *response, size_t responselen);

int supplyIccPinForAppResponse(unsigned int slotId, android::ClientId clientId,
                              int responseType, int serial, RIL_Errno e, void *response,
                              size_t responselen);

int supplyIccPukForAppResponse(unsigned int slotId, android::ClientId clientId,
                              int responseType, int serial, RIL_Errno e, void *response,
                              size_t responselen);

int supplyIccPin2ForAppResponse(unsigned int slotId, android::ClientId clientId,
                               int responseType, int serial, RIL_Errno e, void *response,
                               size_t responselen);

int supplyIccPuk2ForAppResponse(unsigned int slotId, android::ClientId clientId,
                               int responseType, int serial, RIL_Errno e, void *response,
                               size_t responselen);

int changeIccPinForAppResponse(unsigned int slotId, android::ClientId clientId,
                              int responseType, int serial, RIL_Errno e, void *response,
                              size_t responselen);

int changeIccPin2ForAppResponse(unsigned int slotId, android::ClientId clientId,
                               int responseType, int serial, RIL_Errno e, void *response,
                               size_t responselen);

int supplyNetworkDepersonalizationResponse(unsigned int slotId, android::ClientId clientId,
                                          int responseType, int serial, RIL_Errno e,
                                          void *response, size_t responselen);

int supplySimDepersonalizationResponse(unsigned int slotId, android::ClientId clientId __unused,
                                                 int responseType, int serial, RIL_Errno e,
                                                 void *response, size_t responseLen);

int getCurrentCallsResponse(unsigned int slotId, android::ClientId clientId,
                           int responseType, int serial, RIL_Errno e, void *response,
                           size_t responselen);

int dialResponse(unsigned int slotId, android::ClientId clientId,
                int responseType, int serial, RIL_Errno e, void *response, size_t responselen);

int emergencyDialResponse(unsigned int slotId, android::ClientId clientId,
                          int responseType, int serial, RIL_Errno e,
                          void *response, size_t responselen);

int getIMSIForAppResponse(unsigned int slotId, android::ClientId clientId, int responseType,
                         int serial, RIL_Errno e, void *response, size_t responselen);

int hangupConnectionResponse(unsigned int slotId, android::ClientId clientId, int responseType,
                            int serial, RIL_Errno e, void *response, size_t responselen);

int hangupWaitingOrBackgroundResponse(unsigned int slotId, android::ClientId clientId,
                                     int responseType, int serial, RIL_Errno e, void *response,
                                     size_t responselen);

int hangupForegroundResumeBackgroundResponse(unsigned int slotId, android::ClientId clientId,
                                            int responseType, int serial, RIL_Errno e,
                                            void *response, size_t responselen);

int switchWaitingOrHoldingAndActiveResponse(unsigned int slotId, android::ClientId clientId,
                                           int responseType, int serial, RIL_Errno e,
                                           void *response, size_t responselen);

int conferenceResponse(unsigned int slotId, android::ClientId clientId, int responseType,
                      int serial, RIL_Errno e, void *response, size_t responselen);

int rejectCallResponse(unsigned int slotId, android::ClientId clientId, int responseType,
                      int serial, RIL_Errno e, void *response, size_t responselen);

int getLastCallFailCauseResponse(unsigned int slotId, android::ClientId clientId,
                                int responseType, int serial, RIL_Errno e, void *response,
                                size_t responselen);

int getSignalStrengthResponse(unsigned int slotId, android::ClientId clientId,
                              int responseType, int serial, RIL_Errno e,
                              void *response, size_t responseLen);

int getVoiceRegistrationStateResponse(unsigned int slotId, android::ClientId clientId,
                                     int responseType, int serial, RIL_Errno e, void *response,
                                     size_t responselen);

int getDataRegistrationStateResponse(unsigned int slotId, android::ClientId clientId,
                                    int responseType, int serial, RIL_Errno e, void *response,
                                    size_t responselen);

int getOperatorResponse(unsigned int slotId, android::ClientId clientId,
                       int responseType, int serial, RIL_Errno e, void *response,
                       size_t responselen);

int setRadioPowerResponse(unsigned int slotId, android::ClientId clientId,
                         int responseType, int serial, RIL_Errno e, void *response,
                         size_t responselen);

int sendDtmfResponse(unsigned int slotId, android::ClientId clientId,
                    int responseType, int serial, RIL_Errno e, void *response,
                    size_t responselen);

int sendSmsResponse(unsigned int slotId, android::ClientId clientId,
                   int responseType, int serial, RIL_Errno e, void *response,
                   size_t responselen);

int sendSMSExpectMoreResponse(unsigned int slotId, android::ClientId clientId,
                             int responseType, int serial, RIL_Errno e, void *response,
                             size_t responselen);

int setupDataCallResponse(unsigned int slotId, android::ClientId clientId,
                          int responseType, int serial, RIL_Errno e, void *response,
                          size_t responseLen);

int iccIOForAppResponse(unsigned int slotId, android::ClientId clientId,
                       int responseType, int serial, RIL_Errno e, void *response,
                       size_t responselen);

int sendUssdResponse(unsigned int slotId, android::ClientId clientId,
                    int responseType, int serial, RIL_Errno e, void *response,
                    size_t responselen);

int cancelPendingUssdResponse(unsigned int slotId, android::ClientId clientId,
                             int responseType, int serial, RIL_Errno e, void *response,
                             size_t responselen);

int getClirResponse(unsigned int slotId, android::ClientId clientId,
                   int responseType, int serial, RIL_Errno e, void *response, size_t responselen);

int setClirResponse(unsigned int slotId, android::ClientId clientId,
                   int responseType, int serial, RIL_Errno e, void *response, size_t responselen);

int getCallForwardStatusResponse(unsigned int slotId, android::ClientId clientId,
                                int responseType, int serial, RIL_Errno e, void *response,
                                size_t responselen);

int setCallForwardResponse(unsigned int slotId, android::ClientId clientId,
                          int responseType, int serial, RIL_Errno e, void *response,
                          size_t responselen);

int getCallWaitingResponse(unsigned int slotId, android::ClientId clientId,
                          int responseType, int serial, RIL_Errno e, void *response,
                          size_t responselen);

int setCallWaitingResponse(unsigned int slotId, android::ClientId clientId,
                          int responseType, int serial, RIL_Errno e, void *response,
                          size_t responselen);

int acknowledgeLastIncomingGsmSmsResponse(unsigned int slotId, android::ClientId clientId,
                                         int responseType, int serial, RIL_Errno e, void *response,
                                         size_t responselen);

int acceptCallResponse(unsigned int slotId, android::ClientId clientId,
                      int responseType, int serial, RIL_Errno e, void *response,
                      size_t responselen);

int deactivateDataCallResponse(unsigned int slotId, android::ClientId clientId,
                              int responseType, int serial, RIL_Errno e, void *response,
                              size_t responselen);

int getFacilityLockForAppResponse(unsigned int slotId, android::ClientId clientId,
                                 int responseType, int serial, RIL_Errno e, void *response,
                                 size_t responselen);

int setFacilityLockForAppResponse(unsigned int slotId, android::ClientId clientId,
                                 int responseType, int serial, RIL_Errno e, void *response,
                                 size_t responselen);

int setBarringPasswordResponse(unsigned int slotId, android::ClientId clientId,
                              int responseType, int serial, RIL_Errno e, void *response,
                              size_t responselen);

int getNetworkSelectionModeResponse(unsigned int slotId, android::ClientId clientId,
                                   int responseType, int serial, RIL_Errno e, void *response,
                                   size_t responselen);

int setNetworkSelectionModeAutomaticResponse(unsigned int slotId, android::ClientId clientId,
                                            int responseType, int serial, RIL_Errno e,
                                            void *response, size_t responselen);

int setNetworkSelectionModeManualResponse(unsigned int slotId, android::ClientId clientId,
                                         int responseType, int serial, RIL_Errno e, void *response,
                                         size_t responselen);

int getAvailableNetworksResponse(unsigned int slotId, android::ClientId clientId,
                                int responseType, int serial, RIL_Errno e, void *response,
                                size_t responselen);

int startNetworkScanResponse(unsigned int slotId, android::ClientId clientId,
                             int responseType, int serial, RIL_Errno e, void *response,
                             size_t responselen);

int stopNetworkScanResponse(unsigned int slotId, android::ClientId clientId,
                            int responseType, int serial, RIL_Errno e, void *response,
                            size_t responselen);

int startDtmfResponse(unsigned int slotId, android::ClientId clientId,
                     int responseType, int serial, RIL_Errno e, void *response,
                     size_t responselen);

int stopDtmfResponse(unsigned int slotId, android::ClientId clientId,
                    int responseType, int serial, RIL_Errno e, void *response,
                    size_t responselen);

int getBasebandVersionResponse(unsigned int slotId, android::ClientId clientId,
                              int responseType, int serial, RIL_Errno e, void *response,
                              size_t responselen);

int separateConnectionResponse(unsigned int slotId, android::ClientId clientId,
                              int responseType, int serial, RIL_Errno e, void *response,
                              size_t responselen);

int setMuteResponse(unsigned int slotId, android::ClientId clientId,
                   int responseType, int serial, RIL_Errno e, void *response,
                   size_t responselen);

int getMuteResponse(unsigned int slotId, android::ClientId clientId,
                   int responseType, int serial, RIL_Errno e, void *response,
                   size_t responselen);

int getClipResponse(unsigned int slotId, android::ClientId clientId,
                   int responseType, int serial, RIL_Errno e, void *response,
                   size_t responselen);

int getDataCallListResponse(unsigned int slotId, android::ClientId clientId,
                            int responseType, int serial, RIL_Errno e,
                            void *response, size_t responseLen);

int setSuppServiceNotificationsResponse(unsigned int slotId, android::ClientId clientId,
                                       int responseType, int serial, RIL_Errno e, void *response,
                                       size_t responselen);

int writeSmsToSimResponse(unsigned int slotId, android::ClientId clientId,
                         int responseType, int serial, RIL_Errno e, void *response,
                         size_t responselen);

int deleteSmsOnSimResponse(unsigned int slotId, android::ClientId clientId,
                          int responseType, int serial, RIL_Errno e, void *response,
                          size_t responselen);

int setBandModeResponse(unsigned int slotId, android::ClientId clientId,
                       int responseType, int serial, RIL_Errno e, void *response,
                       size_t responselen);

int getAvailableBandModesResponse(unsigned int slotId, android::ClientId clientId,
                                 int responseType, int serial, RIL_Errno e, void *response,
                                 size_t responselen);

int sendEnvelopeResponse(unsigned int slotId, android::ClientId clientId,
                        int responseType, int serial, RIL_Errno e, void *response,
                        size_t responselen);

int sendTerminalResponseToSimResponse(unsigned int slotId, android::ClientId clientId,
                                     int responseType, int serial, RIL_Errno e, void *response,
                                     size_t responselen);

int handleStkCallSetupRequestFromSimResponse(unsigned int slotId, android::ClientId clientId,
                                            int responseType, int serial, RIL_Errno e,
                                            void *response, size_t responselen);

int explicitCallTransferResponse(unsigned int slotId, android::ClientId clientId,
                                int responseType, int serial, RIL_Errno e, void *response,
                                size_t responselen);

int setPreferredNetworkTypeResponse(unsigned int slotId, android::ClientId clientId,
                                   int responseType, int serial, RIL_Errno e, void *response,
                                   size_t responselen);

int getPreferredNetworkTypeResponse(unsigned int slotId, android::ClientId clientId,
                                   int responseType, int serial, RIL_Errno e, void *response,
                                   size_t responselen);

int setAllowedNetworkTypesBitmapResponse(unsigned int slotId, android::ClientId clientId,
                                   int responseType, int serial, RIL_Errno e, void *response,
                                   size_t responselen);

int getAllowedNetworkTypesBitmapResponse(unsigned int slotId, android::ClientId clientId,
                                   int responseType, int serial, RIL_Errno e, void *response,
                                   size_t responselen);

int setNrDualConnectivityStateResponse(unsigned int slotId, android::ClientId clientId,
        int responseType, int serial, RIL_Errno e, void *response, size_t responselen);

int isNrDualConnectivityEnabledResponse(unsigned int slotId, android::ClientId clientId,
        int responseType, int serial, RIL_Errno e, void *response, size_t responselen);

int getNeighboringCidsResponse(unsigned int slotId, android::ClientId clientId,
                              int responseType, int serial, RIL_Errno e, void *response,
                              size_t responselen);

int setLocationUpdatesResponse(unsigned int slotId, android::ClientId clientId,
                              int responseType, int serial, RIL_Errno e, void *response,
                              size_t responselen);

int setCdmaSubscriptionSourceResponse(unsigned int slotId, android::ClientId clientId,
                                     int responseType, int serial, RIL_Errno e, void *response,
                                     size_t responselen);

int setCdmaRoamingPreferenceResponse(unsigned int slotId, android::ClientId clientId,
                                    int responseType, int serial, RIL_Errno e, void *response,
                                    size_t responselen);

int getCdmaRoamingPreferenceResponse(unsigned int slotId, android::ClientId clientId,
                                    int responseType, int serial, RIL_Errno e, void *response,
                                    size_t responselen);

int setTTYModeResponse(unsigned int slotId, android::ClientId clientId,
                      int responseType, int serial, RIL_Errno e, void *response,
                      size_t responselen);

int getTTYModeResponse(unsigned int slotId, android::ClientId clientId,
                      int responseType, int serial, RIL_Errno e, void *response,
                      size_t responselen);

int setPreferredVoicePrivacyResponse(unsigned int slotId, android::ClientId clientId,
                                    int responseType, int serial, RIL_Errno e, void *response,
                                    size_t responselen);

int getPreferredVoicePrivacyResponse(unsigned int slotId, android::ClientId clientId,
                                    int responseType, int serial, RIL_Errno e, void *response,
                                    size_t responselen);

int sendCDMAFeatureCodeResponse(unsigned int slotId, android::ClientId clientId,
                               int responseType, int serial, RIL_Errno e,
                               void *response, size_t responselen);

int sendBurstDtmfResponse(unsigned int slotId, android::ClientId clientId,
                         int responseType, int serial, RIL_Errno e, void *response,
                         size_t responselen);

int sendCdmaSmsResponse(unsigned int slotId, android::ClientId clientId,
                       int responseType, int serial, RIL_Errno e, void *response,
                       size_t responselen);

int sendCdmaSmsExpectMoreResponse(unsigned int slotId, android::ClientId clientId,
                                 int responseType, int serial, RIL_Errno e, void *response,
                                 size_t responselen);

int acknowledgeLastIncomingCdmaSmsResponse(unsigned int slotId, android::ClientId clientId,
                                          int responseType, int serial, RIL_Errno e, void *response,
                                          size_t responselen);

int getGsmBroadcastConfigResponse(unsigned int slotId, android::ClientId clientId,
                                 int responseType, int serial, RIL_Errno e, void *response,
                                 size_t responselen);

int setGsmBroadcastConfigResponse(unsigned int slotId, android::ClientId clientId,
                                 int responseType, int serial, RIL_Errno e, void *response,
                                 size_t responselen);

int setGsmBroadcastActivationResponse(unsigned int slotId, android::ClientId clientId,
                                     int responseType, int serial, RIL_Errno e, void *response,
                                     size_t responselen);

int getCdmaBroadcastConfigResponse(unsigned int slotId, android::ClientId clientId,
                                  int responseType, int serial, RIL_Errno e, void *response,
                                  size_t responselen);

int setCdmaBroadcastConfigResponse(unsigned int slotId, android::ClientId clientId,
                                  int responseType, int serial, RIL_Errno e, void *response,
                                  size_t responselen);

int setCdmaBroadcastActivationResponse(unsigned int slotId, android::ClientId clientId,
                                      int responseType, int serial, RIL_Errno e,
                                      void *response, size_t responselen);

int getCDMASubscriptionResponse(unsigned int slotId, android::ClientId clientId,
                               int responseType, int serial, RIL_Errno e, void *response,
                               size_t responselen);

int writeSmsToRuimResponse(unsigned int slotId, android::ClientId clientId,
                          int responseType, int serial, RIL_Errno e, void *response,
                          size_t responselen);

int deleteSmsOnRuimResponse(unsigned int slotId, android::ClientId clientId,
                           int responseType, int serial, RIL_Errno e, void *response,
                           size_t responselen);

int getDeviceIdentityResponse(unsigned int slotId, android::ClientId clientId,
                             int responseType, int serial, RIL_Errno e, void *response,
                             size_t responselen);

int exitEmergencyCallbackModeResponse(unsigned int slotId, android::ClientId clientId,
                                     int responseType, int serial, RIL_Errno e, void *response,
                                     size_t responselen);

int getSmscAddressResponse(unsigned int slotId, android::ClientId clientId,
                          int responseType, int serial, RIL_Errno e, void *response,
                          size_t responselen);

int setCdmaBroadcastActivationResponse(unsigned int slotId, android::ClientId clientId,
                                      int responseType, int serial, RIL_Errno e,
                                      void *response, size_t responselen);

int setSmscAddressResponse(unsigned int slotId, android::ClientId clientId,
                          int responseType, int serial, RIL_Errno e,
                          void *response, size_t responselen);

int reportSmsMemoryStatusResponse(unsigned int slotId, android::ClientId clientId,
                                 int responseType, int serial, RIL_Errno e,
                                 void *response, size_t responselen);

int reportStkServiceIsRunningResponse(unsigned int slotId, android::ClientId clientId,
                                      int responseType, int serial, RIL_Errno e,
                                      void *response, size_t responseLen);

int getCdmaSubscriptionSourceResponse(unsigned int slotId, android::ClientId clientId,
                                     int responseType, int serial, RIL_Errno e, void *response,
                                     size_t responselen);

int requestIsimAuthenticationResponse(unsigned int slotId, android::ClientId clientId,
                                     int responseType, int serial, RIL_Errno e, void *response,
                                     size_t responselen);

int acknowledgeIncomingGsmSmsWithPduResponse(unsigned int slotId, android::ClientId clientId,
                                            int responseType, int serial, RIL_Errno e,
                                            void *response, size_t responselen);

int sendEnvelopeWithStatusResponse(unsigned int slotId, android::ClientId clientId,
                                  int responseType, int serial, RIL_Errno e, void *response,
                                  size_t responselen);

int getVoiceRadioTechnologyResponse(unsigned int slotId, android::ClientId clientId,
                                   int responseType, int serial, RIL_Errno e,
                                   void *response, size_t responselen);

int getCellInfoListResponse(unsigned int slotId, android::ClientId clientId,
                            int responseType,
                            int serial, RIL_Errno e, void *response,
                            size_t responseLen);

int setCellInfoListRateResponse(unsigned int slotId, android::ClientId clientId,
                               int responseType, int serial, RIL_Errno e,
                               void *response, size_t responselen);

int setInitialAttachApnResponse(unsigned int slotId, android::ClientId clientId,
                               int responseType, int serial, RIL_Errno e,
                               void *response, size_t responselen);

int getImsRegistrationStateResponse(unsigned int slotId, android::ClientId clientId,
                                   int responseType, int serial, RIL_Errno e,
                                   void *response, size_t responselen);

int sendImsSmsResponse(unsigned int slotId, android::ClientId clientId, int responseType,
                      int serial, RIL_Errno e, void *response, size_t responselen);

int iccTransmitApduBasicChannelResponse(unsigned int slotId, android::ClientId clientId,
                                       int responseType, int serial, RIL_Errno e,
                                       void *response, size_t responselen);

int iccOpenLogicalChannelResponse(unsigned int slotId, android::ClientId clientId,
                                  int responseType, int serial, RIL_Errno e, void *response,
                                  size_t responselen);


int iccCloseLogicalChannelResponse(unsigned int slotId, android::ClientId clientId,
                                  int responseType, int serial, RIL_Errno e,
                                  void *response, size_t responselen);

int iccTransmitApduLogicalChannelResponse(unsigned int slotId, android::ClientId clientId,
                                         int responseType, int serial, RIL_Errno e,
                                         void *response, size_t responselen);

int nvReadItemResponse(unsigned int slotId, android::ClientId clientId,
                      int responseType, int serial, RIL_Errno e,
                      void *response, size_t responselen);


int nvWriteItemResponse(unsigned int slotId, android::ClientId clientId,
                       int responseType, int serial, RIL_Errno e,
                       void *response, size_t responselen);

int nvWriteCdmaPrlResponse(unsigned int slotId, android::ClientId clientId,
                          int responseType, int serial, RIL_Errno e,
                          void *response, size_t responselen);

int nvResetConfigResponse(unsigned int slotId, android::ClientId clientId,
                         int responseType, int serial, RIL_Errno e,
                         void *response, size_t responselen);

int setUiccSubscriptionResponse(unsigned int slotId, android::ClientId clientId,
                               int responseType, int serial, RIL_Errno e,
                               void *response, size_t responselen);

int setDataAllowedResponse(unsigned int slotId, android::ClientId clientId,
                          int responseType, int serial, RIL_Errno e,
                          void *response, size_t responselen);

int getHardwareConfigResponse(unsigned int slotId, android::ClientId clientId,
                              int responseType, int serial, RIL_Errno e,
                              void *response, size_t responseLen);

int requestIccSimAuthenticationResponse(unsigned int slotId, android::ClientId clientId,
                                       int responseType, int serial, RIL_Errno e,
                                       void *response, size_t responselen);

int setDataProfileResponse(unsigned int slotId, android::ClientId clientId,
                          int responseType, int serial, RIL_Errno e,
                          void *response, size_t responselen);

int requestShutdownResponse(unsigned int slotId, android::ClientId clientId,
                           int responseType, int serial, RIL_Errno e,
                           void *response, size_t responselen);

int getRadioCapabilityResponse(unsigned int slotId, android::ClientId clientId,
                               int responseType, int serial, RIL_Errno e,
                               void *response, size_t responseLen);

int setRadioCapabilityResponse(unsigned int slotId, android::ClientId clientId,
                               int responseType, int serial, RIL_Errno e,
                               void *response, size_t responseLen);

int startLceServiceResponse(unsigned int slotId, android::ClientId clientId,
                           int responseType, int serial, RIL_Errno e,
                           void *response, size_t responselen);

int stopLceServiceResponse(unsigned int slotId, android::ClientId clientId,
                          int responseType, int serial, RIL_Errno e,
                          void *response, size_t responselen);

int pullLceDataResponse(unsigned int slotId, android::ClientId clientId,
                        int responseType, int serial, RIL_Errno e,
                        void *response, size_t responseLen);

int getModemActivityInfoResponse(unsigned int slotId, android::ClientId clientId,
                                int responseType, int serial, RIL_Errno e,
                                void *response, size_t responselen);

int setAllowedCarriersResponse(unsigned int slotId, android::ClientId clientId,
                              int responseType, int serial, RIL_Errno e,
                              void *response, size_t responselen);

int getAllowedCarriersResponse(unsigned int slotId, android::ClientId clientId,
                              int responseType, int serial, RIL_Errno e,
                              void *response, size_t responselen);

int sendDeviceStateResponse(unsigned int slotId, android::ClientId clientId,
                              int responseType, int serial, RIL_Errno e,
                              void *response, size_t responselen);

int setIndicationFilterResponse(unsigned int slotId, android::ClientId clientId,
                              int responseType, int serial, RIL_Errno e,
                              void *response, size_t responselen);

int setSimCardPowerResponse(unsigned int slotId, android::ClientId clientId,
                              int responseType, int serial, RIL_Errno e,
                              void *response, size_t responselen);

int enableUiccApplicationsResponse(unsigned int slotId, android::ClientId clientId,
                               int responseType, int serial, RIL_Errno e, void *response,
                               size_t responselen);

int areUiccApplicationsEnabledResponse(unsigned int slotId, android::ClientId clientId,
                               int responseType, int serial, RIL_Errno e, void *response,
                               size_t responselen);

int startKeepaliveResponse(unsigned int slotId, android::ClientId clientId,
                           int responseType, int serial, RIL_Errno e,
                           void *response, size_t responselen);

int stopKeepaliveResponse(unsigned int slotId, android::ClientId clientId,
                          int responseType, int serial, RIL_Errno e,
                          void *response, size_t responselen);

int allocatePduSessionIdResponse(unsigned int slotId, android::ClientId clientId, int responseType,
        int serial, RIL_Errno e, void* response, size_t responseLen);

int releasePduSessionIdResponse(unsigned int slotId, android::ClientId clientId, int responseType,
        int serial, RIL_Errno e, void* response, size_t responseLen);

int startHandoverResponse(unsigned int slotId, android::ClientId clientId, int responseType,
        int serial, RIL_Errno e, void* response, size_t responseLen);

int cancelHandoverResponse(unsigned int slotId, android::ClientId clientId, int responseType,
        int serial, RIL_Errno e, void* response, size_t responseLen);

int setDataThrottlingResponse(unsigned int slotId, android::ClientId clientId, int responseType,
        int serial, RIL_Errno e, void* response, size_t responseLen);

int setSignalStrengthReportingCriteriaResponse(unsigned int slotId, android::ClientId clientId,
        int indicationType, int token, RIL_Errno err, void *response, size_t responseLen);

int setLinkCapacityReportingCriteriaResponse(unsigned int slotId, android::ClientId clientId,
        int indicationType, int token, RIL_Errno err, void *response, size_t responseLen);

void acknowledgeRequest(unsigned int slotId, int serial);

int radioStateChangedInd(unsigned int slotId,
                          int indicationType, int token, RIL_Errno e, void *response,
                          size_t responseLen);

int callStateChangedInd(unsigned int slotId, int indType, int token,
                        RIL_Errno e, void *response, size_t responselen);

int networkStateChangedInd(unsigned int slotId, int indType,
                                int token, RIL_Errno e, void *response, size_t responselen);

int newSmsInd(unsigned int slotId, int indicationType,
              int token, RIL_Errno e, void *response, size_t responselen);

int newSmsStatusReportInd(unsigned int slotId, int indicationType,
                          int token, RIL_Errno e, void *response, size_t responselen);

int newSmsOnSimInd(unsigned int slotId, int indicationType,
                   int token, RIL_Errno e, void *response, size_t responselen);

int onUssdInd(unsigned int slotId, int indicationType,
              int token, RIL_Errno e, void *response, size_t responselen);

int nitzTimeReceivedInd(unsigned int slotId, int indicationType,
                        int token, RIL_Errno e, void *response, size_t responselen);

int currentSignalStrengthInd(unsigned int slotId,
                             int indicationType, int token, RIL_Errno e,
                             void *response, size_t responselen);

int dataCallListChangedInd(unsigned int slotId, int indicationType,
                           int token, RIL_Errno e, void *response, size_t responselen);

int suppSvcNotifyInd(unsigned int slotId, int indicationType,
                     int token, RIL_Errno e, void *response, size_t responselen);

int stkSessionEndInd(unsigned int slotId, int indicationType,
                     int token, RIL_Errno e, void *response, size_t responselen);

int stkProactiveCommandInd(unsigned int slotId, int indicationType,
                           int token, RIL_Errno e, void *response, size_t responselen);

int stkEventNotifyInd(unsigned int slotId, int indicationType,
                      int token, RIL_Errno e, void *response, size_t responselen);

int stkCallSetupInd(unsigned int slotId, int indicationType,
                    int token, RIL_Errno e, void *response, size_t responselen);

int simSmsStorageFullInd(unsigned int slotId, int indicationType,
                         int token, RIL_Errno e, void *response, size_t responselen);

int simRefreshInd(unsigned int slotId, int indicationType,
                  int token, RIL_Errno e, void *response, size_t responselen);

int callRingInd(unsigned int slotId, int indicationType,
                int token, RIL_Errno e, void *response, size_t responselen);

int simStatusChangedInd(unsigned int slotId, int indicationType,
                        int token, RIL_Errno e, void *response, size_t responselen);

int cdmaNewSmsInd(unsigned int slotId, int indicationType,
                  int token, RIL_Errno e, void *response, size_t responselen);

int newBroadcastSmsInd(unsigned int slotId,
                       int indicationType, int token, RIL_Errno e, void *response,
                       size_t responselen);

int cdmaRuimSmsStorageFullInd(unsigned int slotId,
                              int indicationType, int token, RIL_Errno e, void *response,
                              size_t responselen);

int restrictedStateChangedInd(unsigned int slotId,
                              int indicationType, int token, RIL_Errno e, void *response,
                              size_t responselen);

int enterEmergencyCallbackModeInd(unsigned int slotId,
                                  int indicationType, int token, RIL_Errno e, void *response,
                                  size_t responselen);

int cdmaCallWaitingInd(unsigned int slotId,
                       int indicationType, int token, RIL_Errno e, void *response,
                       size_t responselen);

int cdmaOtaProvisionStatusInd(unsigned int slotId,
                              int indicationType, int token, RIL_Errno e, void *response,
                              size_t responselen);

int cdmaInfoRecInd(unsigned int slotId,
                   int indicationType, int token, RIL_Errno e, void *response,
                   size_t responselen);

int indicateRingbackToneInd(unsigned int slotId,
                            int indicationType, int token, RIL_Errno e, void *response,
                            size_t responselen);

int resendIncallMuteInd(unsigned int slotId,
                        int indicationType, int token, RIL_Errno e, void *response,
                        size_t responselen);

int cdmaSubscriptionSourceChangedInd(unsigned int slotId,
                                     int indicationType, int token, RIL_Errno e,
                                     void *response, size_t responselen);

int cdmaPrlChangedInd(unsigned int slotId,
                      int indicationType, int token, RIL_Errno e, void *response,
                      size_t responselen);

int exitEmergencyCallbackModeInd(unsigned int slotId,
                                 int indicationType, int token, RIL_Errno e, void *response,
                                 size_t responselen);

int rilConnectedInd(unsigned int slotId,
                    int indicationType, int token, RIL_Errno e, void *response,
                    size_t responselen);

int voiceRadioTechChangedInd(unsigned int slotId,
                             int indicationType, int token, RIL_Errno e, void *response,
                             size_t responselen);

int cellInfoListInd(unsigned int slotId,
                    int indicationType, int token, RIL_Errno e, void *response,
                    size_t responselen);

int imsNetworkStateChangedInd(unsigned int slotId,
                              int indicationType, int token, RIL_Errno e, void *response,
                              size_t responselen);

int subscriptionStatusChangedInd(unsigned int slotId,
                                 int indicationType, int token, RIL_Errno e, void *response,
                                 size_t responselen);

int uiccApplicationsEnablementChanged(unsigned int slotId, int indicationType, int token,
        RIL_Errno e, void *response, size_t responseLen);

int srvccStateNotifyInd(unsigned int slotId,
                        int indicationType, int token, RIL_Errno e, void *response,
                        size_t responselen);

int hardwareConfigChangedInd(unsigned int slotId,
                             int indicationType, int token, RIL_Errno e, void *response,
                             size_t responselen);

int radioCapabilityIndicationInd(unsigned int slotId,
                                 int indicationType, int token, RIL_Errno e, void *response,
                                 size_t responselen);

int onSupplementaryServiceIndicationInd(unsigned int slotId,
                                        int indicationType, int token, RIL_Errno e,
                                        void *response, size_t responselen);

int stkCallControlAlphaNotifyInd(unsigned int slotId,
                                 int indicationType, int token, RIL_Errno e, void *response,
                                 size_t responselen);

int lceDataInd(unsigned int slotId,
               int indicationType, int token, RIL_Errno e, void *response,
               size_t responselen);

int pcoDataInd(unsigned int slotId,
               int indicationType, int token, RIL_Errno e, void *response,
               size_t responselen);

int modemResetInd(unsigned int slotId,
                  int indicationType, int token, RIL_Errno e, void *response,
                  size_t responselen);

int networkScanResultInd(unsigned int slotId,
                         int indicationType, int token, RIL_Errno e, void *response,
                         size_t responselen);

int keepaliveStatusInd(unsigned int slotId,
                       int indicationType, int token, RIL_Errno e, void *response,
                       size_t responselen);

int sendRequestRawResponse(unsigned int slotId, android::ClientId clientId,
                           int responseType, int serial, RIL_Errno e,
                           void *response, size_t responseLen);

int sendRequestStringsResponse(unsigned int slotId, android::ClientId clientId,
                               int responseType, int serial, RIL_Errno e,
                               void *response, size_t responseLen);

int setCarrierInfoForImsiEncryptionResponse(unsigned int slotId, android::ClientId clientId,
                                            int responseType, int serial, RIL_Errno e,
                                            void *response, size_t responseLen);

int carrierInfoForImsiEncryption(unsigned int slotId, android::ClientId clientId,
                        int responseType, int serial, RIL_Errno e,
                        void *response, size_t responseLen);

int currentPhysicalChannelConfigs(unsigned int slotId, int indicationType,
        int token, RIL_Errno err, void *response, size_t responseLen);

int currentLinkCapacityEstimate(unsigned int slotId, int indicationType,
        int token, RIL_Errno err, void *response, size_t responseLen);

pthread_rwlock_t * getRadioServiceRwlock(int slotId);

void lockRadioServiceRlock(pthread_rwlock_t *radioServiceRwlockPtr, int slotId);
void unlockRadioServiceRlock(pthread_rwlock_t *radioServiceRwlockPtr, int slotId);
void lockRadioServiceWlock(pthread_rwlock_t *radioServiceRwlockPtr, int slotId);
void unlockRadioServiceWlock(pthread_rwlock_t *radioServiceRwlockPtr, int slotId);
int isTidInRLock(unsigned int slotId, pthread_t tid);

void setNitzTimeReceived(unsigned int slotId, int64_t timeReceived);

int emergencyNumberListInd(unsigned int slotId,
        int indicationType, int token, RIL_Errno e, void *response,
        size_t responselen);

int enableModemResponse(unsigned int slotId, android::ClientId clientId, int responseType,
        int serial, RIL_Errno err, void *response, size_t responseLen);

int getModemStackStatusResponse(unsigned int slotId, android::ClientId clientId,
        int responseType, int serial, RIL_Errno e, void *response, size_t responselen);

int setSystemSelectionChannelsResponse(unsigned int slotId, android::ClientId clientId,
                             int responseType, int serial, RIL_Errno e, void *response,
                             size_t responselen);

int getSystemSelectionChannelsResponse(unsigned int slotId, android::ClientId clientId,
                             int responseType, int serial, RIL_Errno e, void *response,
                             size_t responselen);

int getBarringInfoResponse(unsigned int slotId, android::ClientId clientId,
                                int responseType, int serial, RIL_Errno e, void *response,
                                size_t responselen);

int onBarringInfoInd(unsigned int slotId, int indicationType,
                        int token, RIL_Errno e, void *response, size_t responselen);

int onRegistrationFailedInd(unsigned int slotId, int indicationType,
                        int token, RIL_Errno e, void *response, size_t responselen);

int getSlicingConfigResponse(unsigned int slotId, android::ClientId clientId,
        int responseType, int serial, RIL_Errno e, void *response,
        size_t responselen);

int getSimPhonebookRecordsResponse(unsigned int slotId, android::ClientId clientId,
        int responseType, int serial, RIL_Errno e, void *response,
        size_t responselen);

int getSimPhonebookCapacityResponse(unsigned int slotId, android::ClientId clientId,
        int responseType, int serial, RIL_Errno e, void *response,
        size_t responselen);

int updateSimPhonebookRecordsResponse(unsigned int slotId, android::ClientId clientId,
        int responseType, int serial, RIL_Errno e, void *response,
        size_t responselen);

int simPhonebookChanged(unsigned int slotId, int indicationType,
                        int token, RIL_Errno e, void *response, size_t responselen);

int simPhonebookRecordsReceived(unsigned int slotId, int indicationType,
                        int token, RIL_Errno e, void *response, size_t responselen);

}   // namespace radio


namespace mtkRadioEx {
    int getTOEInfoResponse(unsigned int slotId, android::ClientId clientId  __unused,
                                 int responseType, int serial, RIL_Errno e,
                                 void *response, size_t responseLen);
    int disableAllCALinksResponse(unsigned int slotId, android::ClientId clientId  __unused,
                                 int responseType, int serial, RIL_Errno e,
                                 void *response, size_t responseLen);
    int getCALinkEnableStatusResponse(unsigned int slotId, android::ClientId clientId  __unused,
                                 int responseType, int serial, RIL_Errno e,
                                 void *response, size_t responseLen);
    int setCALinkEnableStatusResponse(unsigned int slotId, android::ClientId clientId  __unused,
                                 int responseType, int serial, RIL_Errno e,
                                 void *response, size_t responseLen);
    int getCALinkCapabilityListResponse(unsigned int slotId, android::ClientId clientId  __unused,
                                 int responseType, int serial, RIL_Errno e,
                                 void *response, size_t responseLen);
    int getLteDataResponse(unsigned int slotId, android::ClientId clientId  __unused,
                                 int responseType, int serial, RIL_Errno e,
                                 void *response, size_t responseLen);
    int getLteRRCStateResponse(unsigned int slotId, android::ClientId clientId  __unused,
                                 int responseType, int serial, RIL_Errno e,
                                 void *response, size_t responseLen);
    int setLteBandEnableStatusResponse(unsigned int slotId, android::ClientId clientId  __unused,
                                 int responseType, int serial, RIL_Errno e,
                                 void *response, size_t responseLen);
    int getBandPriorityListResponse(unsigned int slotId, android::ClientId clientId  __unused,
                                 int responseType, int serial, RIL_Errno e,
                                 void *response, size_t responseLen);
    int setBandPriorityListResponse(unsigned int slotId, android::ClientId clientId  __unused,
                                 int responseType, int serial, RIL_Errno e,
                                 void *response, size_t responseLen);
    int set4x4MimoEnabledResponse(unsigned int slotId, android::ClientId clientId  __unused,
                              int responseType, int serial, RIL_Errno e,
                              void *response, size_t responseLen);
    int get4x4MimoEnabledResponse(unsigned int slotId, android::ClientId clientId  __unused,
                              int responseType, int serial, RIL_Errno e,
                              void *response, size_t responseLen);
    int getLteBsrTimerResponse(unsigned int slotId, android::ClientId clientId __unused,
            int responseType, int serial, RIL_Errno e, void *response, size_t responseLen);
    int setLteBsrTimerResponse(unsigned int slotId, android::ClientId clientId __unused,
            int responseType, int serial, RIL_Errno e, void *response, size_t responseLen);
    int getLte1xRttCellListResponse(unsigned int slotId, android::ClientId clientId __unused,
            int responseType, int serial, RIL_Errno e, void *response, size_t responseLen);
    int clearLteAvailableFileResponse(unsigned int slotId, android::ClientId clientId __unused,
            int responseType, int serial, RIL_Errno e, void *response, size_t responseLen);
    int getBandModeResponse(unsigned int slotId, android::ClientId clientId __unused,
            int responseType, int serial, RIL_Errno e, void *response, size_t responseLen);
    int getAllBandModeResponse(unsigned int slotId, android::ClientId clientId __unused,
            int responseType, int serial, RIL_Errno e, void *response, size_t responseLen);
    int setNrBandModeResponse(unsigned int slotId, android::ClientId clientId __unused,
        int responseType, int serial, RIL_Errno e, void *response, size_t responseLen);
    int getCaBandModeResponse(unsigned int slotId, android::ClientId clientId __unused,
            int responseType, int serial, RIL_Errno e, void *response, size_t responseLen);
    int getCampedFemtoCellInfoResponse(unsigned int slotId,
            android::ClientId clientId __unused, int responseType, int serial, RIL_Errno e,
            void *response, size_t responseLen);
    int setQamEnabledResponse(unsigned int slotId, android::ClientId clientId, int responseType,
                    int serial, RIL_Errno e, void *response, size_t responseLen);
    int getQamEnabledResponse(unsigned int slotId, android::ClientId clientId, int responseType,
                    int serial, RIL_Errno e, void *response, size_t responseLen);
    int setTm9EnabledResponse(unsigned int slotId, android::ClientId clientId, int responseType,
                    int serial, RIL_Errno e, void *response, size_t responseLen);
    int getTm9EnabledResponse(unsigned int slotId, android::ClientId clientId, int responseType,
                    int serial, RIL_Errno e, void *response, size_t responseLen);
    int setLteScanDurationResponse(unsigned int slotId, android::ClientId clientId, int responseType,
                    int serial, RIL_Errno e, void *response, size_t responseLen);
    int getLteScanDurationResponse(unsigned int slotId, android::ClientId clientId, int responseType,
                    int serial, RIL_Errno e, void *response, size_t responseLen);

int setNetworkSelectionModeManualWithActResponse(unsigned int slotId, android::ClientId clientId,
                             int responseType, int serial, RIL_Errno e,
                             void *response, size_t responseLen);
int getAvailableNetworksWithActResponse(unsigned int slotId, android::ClientId clientId,
                              int responseType, int serial, RIL_Errno e, void *response,
                              size_t responseLen);

int cancelAvailableNetworksResponse(unsigned int slotId, android::ClientId clientId,
                             int responseType, int serial, RIL_Errno e,
                             void *response, size_t responseLen);

int cfgA2offsetResponse(unsigned int slotId, android::ClientId clientId __unused,
                             int responseType, int serial, RIL_Errno e,
                             void *response, size_t responseLen);

int cfgB1offsetResponse(unsigned int slotId, android::ClientId clientId __unused,
                             int responseType, int serial, RIL_Errno e,
                             void *response, size_t responseLen);

int enableSCGfailureResponse(unsigned int slotId, android::ClientId clientId __unused,
                             int responseType, int serial, RIL_Errno e,
                             void *response, size_t responseLen);

int setNROptionResponse(unsigned int slotId, android::ClientId clientId __unused,
                             int responseType, int serial, RIL_Errno e,
                             void *response, size_t responseLen);

int deactivateNrScgCommunicationResponse(unsigned int slotId, android::ClientId clientId __unused,
                             int responseType, int serial, RIL_Errno e,
                             void *response, size_t responseLen);

int getDeactivateNrScgCommunicationResponse(unsigned int slotId, android::ClientId clientId __unused,
                             int responseType, int serial, RIL_Errno e,
                             void *response, size_t responseLen);

int smartRatSwitchResponse(unsigned int slotId, android::ClientId clientId __unused,
        int responseType, int serial, RIL_Errno e, void *response, size_t responseLen);

int getSmartRatSwitchResponse(unsigned int slotId, android::ClientId clientId __unused,
        int responseType, int serial, RIL_Errno e, void *response, size_t responseLen);

int setSmartSceneSwitchResponse(unsigned int slotId, android::ClientId clientId __unused,
        int responseType, int serial, RIL_Errno e, void *response, size_t responseLen);

int setTxPowerResponse(unsigned int slotId, android::ClientId clientId __unused,
                             int responseType, int serial, RIL_Errno e,
                             void *response, size_t responseLen);

int setSearchStoredFreqInfoResponse(unsigned int slotId, android::ClientId clientId __unused,
                             int responseType, int serial, RIL_Errno e,
                             void *response, size_t responseLen);

int setSearchRatResponse(unsigned int slotId, android::ClientId clientId __unused,
                             int responseType, int serial, RIL_Errno e,
                             void *response, size_t responseLen);

int setBgsrchDeltaSleepTimerResponse(unsigned int slotId, android::ClientId clientId __unused,
                             int responseType, int serial, RIL_Errno e,
                             void *response, size_t responseLen);

int setClipResponse(unsigned int slotId, android::ClientId clientId, int responseType, int serial,
                    RIL_Errno e, void *response, size_t responseLen);

int getColpResponse(unsigned int slotId, android::ClientId clientId, int responseType, int serial,
                    RIL_Errno e, void *response, size_t responseLen);

int getColrResponse(unsigned int slotId, android::ClientId clientId, int responseType, int serial,
                    RIL_Errno e, void *response, size_t responseLen);

int sendCnapResponse(unsigned int slotId, android::ClientId clientId, int responseType, int serial,
                    RIL_Errno e, void *response, size_t responseLen);

int setColpResponse(unsigned int slotId, android::ClientId clientId, int responseType, int serial,
                    RIL_Errno e, void *response, size_t responseLen);

int setColrResponse(unsigned int slotId, android::ClientId clientId, int responseType, int serial,
                    RIL_Errno e, void *response, size_t responseLen);

int queryCallForwardInTimeSlotStatusResponse(unsigned int slotId, android::ClientId clientId,
                    int responseType, int serial, RIL_Errno e, void *response,
                    size_t responseLen);

int setCallForwardInTimeSlotResponse(unsigned int slotId, android::ClientId clientId,
                    int responseType, int serial, RIL_Errno e, void *response,
                    size_t responseLen);

int runGbaAuthenticationResponse(unsigned int slotId, android::ClientId clientId, int responseType,
                    int serial, RIL_Errno e, void *response, size_t responseLen);

// FastDormancy
int setFdModeResponse(unsigned int slotId, android::ClientId clientId, int responseType,
        int serial, RIL_Errno e, void *response, size_t responselen);

int hangupAllResponse(unsigned int slotId, android::ClientId clientId,
                      int responseType, int serial, RIL_Errno e,
                      void *response, size_t responselen);

int hangupWithReasonResponse(unsigned int slotId, android::ClientId clientId,
                      int responseType, int serial, RIL_Errno e,
                      void *response, size_t responselen);

int setCallIndicationResponse(unsigned int slotId, android::ClientId clientId,
                              int responseType, int serial, RIL_Errno e,
                              void *response, size_t responselen);

/// M: CC: Emergency mode for Fusion RIL
int setEccModeResponse(unsigned int slotId, android::ClientId clientId, int responseType,
                            int serial, RIL_Errno e, void *response,
                            size_t responselen);

int setEccNumResponse(unsigned int slotId, android::ClientId clientId, int responseType,
                            int serial, RIL_Errno e, void *response,
                            size_t responselen);

int getEccNumResponse(unsigned int slotId, android::ClientId clientId, int responseType,
                            int serial, RIL_Errno e, void *response,
                            size_t responselen);

int cfuStatusNotifyInd(unsigned int slotId, int indicationType,
                              int token, RIL_Errno e, void *response, size_t responseLen);

/// M: CC: CDMA call accepted indication @{
int cdmaCallAcceptedInd(unsigned int slotId, int indicationType,
                    int token, RIL_Errno e, void *response, size_t responseLen);
/// @}

int eccNumIndication(unsigned int slotId, int indicationType,
                    int token, RIL_Errno e, void *response, size_t responseLen);

/// M: CC: call control part ([IMS] common flow) @{
int incomingCallIndicationInd(unsigned int slotId, int indicationType,
                    int token, RIL_Errno e, void *response, size_t responseLen);

int cipherIndicationInd(unsigned int slotId, int indicationType,
              int token, RIL_Errno e, void *response, size_t responseLen);

int suppSvcNotifyExInd(unsigned int slotId, int indicationType,
                     int token, RIL_Errno e, void *response, size_t responselen);

int crssNotifyInd(unsigned int slotId, int indicationType,
                  int token, RIL_Errno e, void *response, size_t responseLen);

int speechCodecInfoInd(unsigned int slotId, int indicationType,
                       int token, RIL_Errno e, void *response, size_t responseLen);

int atciInd(unsigned int slotId,
            int indicationType, int token, RIL_Errno e, void *response,
            size_t responselen);

int noEmergencyCallbackModeInd(unsigned int slotId,
                                 int indicationType, int token, RIL_Errno e, void *response,
                                 size_t responselen);

// M: [VzW] Data Framework @{
int pcoDataAfterAttachedInd(unsigned int slotId,
               int indicationType, int token, RIL_Errno e, void *response,
               size_t responselen);

int networkRejectCauseInd(unsigned int slotId,
               int indicationType, int token, RIL_Errno e, void *response,
               size_t responselen);
// M: [VzW] Data Framework @}

int sendAtciResponse(unsigned int slotId, android::ClientId clientId,
                     int responseType, int serial, RIL_Errno e,
                     void *response, size_t responseLen);

/// SUBSIDYLOCK
int sendSubsidyLockResponse(unsigned int slotId, android::ClientId clientId,
                     int responseType, int serial, RIL_Errno e,
                     void *response, size_t responseLen);

/// [IMS] Response ======================================================================

int imsEmergencyDialResponse(unsigned int slotId, android::ClientId clientId,
                             int responseType, int serial, RIL_Errno e, void *response,
                             size_t responseLen);

int imsDialResponse(unsigned int slotId, android::ClientId clientId,
                    int responseType,
                    int serial, RIL_Errno e, void *response, size_t responselen);

int imsVtDialResponse(unsigned int slotId, android::ClientId clientId,
                      int responseType, int token, RIL_Errno e, void *response,
                      size_t responselen);
int videoCallAcceptResponse(unsigned int slotId, android::ClientId clientId,
                            int responseType, int token, RIL_Errno e, void *response,
                            size_t responselen);

int eccRedialApproveResponse(unsigned int slotId, android::ClientId clientId,
                            int responseType, int token, RIL_Errno e, void *response,
                            size_t responselen);

int imsEctCommandResponse(unsigned int slotId, android::ClientId clientId,
                          int responseType, int token, RIL_Errno e,
                          void *response, size_t responselen);

int controlCallResponse(unsigned int slotId, android::ClientId clientId,
                 int responseType, int token, RIL_Errno e,
                 void *response, size_t responselen);

int imsDeregNotificationResponse(unsigned int slotId, android::ClientId clientId,
                                 int responseType, int token, RIL_Errno e, void *response,
                                 size_t responselen);

int setImsEnableResponse(unsigned int slotId, android::ClientId clientId,
                         int responseType, int token, RIL_Errno e, void *response,
                         size_t responselen);

int setImscfgResponse(unsigned int slotId, android::ClientId clientId,
                      int responseType, int token, RIL_Errno e, void *response,
                      size_t responselen);

int setModemImsCfgResponse(unsigned int slotId, android::ClientId clientId,
                      int responseType, int token, RIL_Errno e, void *response,
                      size_t responselen);

int getProvisionValueResponse(unsigned int slotId, android::ClientId clientId,
                              int responseType, int token, RIL_Errno e, void *response,
                              size_t responselen);

int setProvisionValueResponse(unsigned int slotId, android::ClientId clientId,
                              int responseType, int token, RIL_Errno e, void *response,
                              size_t responselen);

// IMS Config TelephonyWare START

int setImsCfgFeatureValueResponse(unsigned int slotId, android::ClientId clientId,
                                  int responseType, int token, RIL_Errno e, void *response,
                                  size_t responselen);

int getImsCfgFeatureValueResponse(unsigned int slotId, android::ClientId clientId,
                                  int responseType, int token, RIL_Errno e, void *response,
                                  size_t responselen);

int setImsCfgProvisionValueResponse(unsigned int slotId, android::ClientId clientId,
                                    int responseType, int token, RIL_Errno e, void *response,
                                    size_t responselen);

int getImsCfgProvisionValueResponse(unsigned int slotId, android::ClientId clientId,
                                    int responseType, int token, RIL_Errno e, void *response,
                                    size_t responselen);

int getImsCfgResourceCapValueResponse(unsigned int slotId, android::ClientId clientId,
                                      int responseType, int token, RIL_Errno e, void *response,
                                      size_t responselen);
// IMS Config TelephonyWare END

int controlImsConferenceCallMemberResponse(unsigned int slotId, android::ClientId clientId,
                                int responseType, int token, RIL_Errno e, void *response,
                                size_t responselen);

int setWfcProfileResponse(unsigned int slotId, android::ClientId clientId,

                          int responseType, int token, RIL_Errno e, void *response,
                          size_t responselen);

int conferenceDialResponse(unsigned int slotId, android::ClientId clientId,
                           int responseType, int token, RIL_Errno e, void *response,
                           size_t responselen);

int vtDialWithSipUriResponse(unsigned int slotId, android::ClientId clientId,
                             int responseType, int token, RIL_Errno e, void *response,
                             size_t responselen);

int dialWithSipUriResponse(unsigned int slotId, android::ClientId clientId,
                           int responseType, int token, RIL_Errno e, void *response,
                           size_t responselen);

int sendUssiResponse(unsigned int slotId, android::ClientId clientId,
                     int responseType, int token, RIL_Errno e, void *response,
                     size_t responselen);

int cancelUssiResponse(unsigned int slotId, android::ClientId clientId,
                              int responseType, int token, RIL_Errno e, void *response,
                              size_t responselen);

int getXcapStatusResponse(unsigned int slotId, android::ClientId clientId, int responseType, int serial,
                          RIL_Errno e, void *response, size_t responseLen);

int resetSuppServResponse(unsigned int slotId, android::ClientId clientId, int responseType, int serial,
                          RIL_Errno e, void *response, size_t responseLen);

int setupXcapUserAgentStringResponse(unsigned int slotId, android::ClientId clientId, int responseType,
                          int serial, RIL_Errno e, void *response, size_t responseLen);

int forceReleaseCallResponse(unsigned int slotId, android::ClientId clientId,
                        int responseType, int token, RIL_Errno e, void *response,
                        size_t responselen);

int setImsRtpReportResponse(unsigned int slotId, android::ClientId clientId,
                            int responseType, int token, RIL_Errno e, void *response,
                            size_t responselen);

int imsBearerStateConfirmResponse(unsigned int slotId, android::ClientId clientId,
                                         int responseType, int token, RIL_Errno e,
                                         void *response, size_t responselen);

int setImsBearerNotificationResponse(unsigned int slotId, android::ClientId clientId,
                                           int responseType, int token, RIL_Errno e,
                                           void *response, size_t responselen);

int pullCallResponse(unsigned int slotId, android::ClientId clientId,
                     int responseType, int serial, RIL_Errno e,
                     void *response, size_t responselen);
int setImsRegistrationReportResponse(unsigned int slotId, android::ClientId clientId,
                                     int indicationType, int token, RIL_Errno e,
                                     void *response, size_t responseLen);

int setVendorSettingResponse(unsigned int slotId, android::ClientId clientId, int responseType, int serial,
        RIL_Errno e, void *response, size_t responseLen);

/// [IMS] Response ======================================================================
pthread_rwlock_t * getMtkRadioServiceExRwlock(int slotId);

int getSmsRuimMemoryStatusResponse(unsigned int slotId, android::ClientId clientId,
                                   int responseType, int serial, RIL_Errno e,
                                   void *response, size_t responseLen);

int toeInfoInd(unsigned int slotId, int indicationType, int token, RIL_Errno e,
                       void *response, size_t responseLen);

int sib16TimeInfoInd(unsigned int slotId, int indicationType, int token, RIL_Errno e,
                      void *response, size_t responseLen);
int nrCaBandChangeInd(unsigned int slotId, int indicationType, int token, RIL_Errno e,
                      void *response, size_t responseLen);


int currentNwCfgInfoInd(unsigned int slotId, int indicationType,
        int token, RIL_Errno err, void *response, size_t responseLen);

int currentRrcStateInd(unsigned int slotId, int indicationType,
        int token, RIL_Errno err, void *response, size_t responseLen);

int responseNetworkEventInd(unsigned int slotId,
                       int indicationType, int token, RIL_Errno e, void *response,
                       size_t responseLen);

int responsePsNetworkStateChangeInd(unsigned int slotId,
                                    int indicationType, int token, RIL_Errno e,
                                    void *response, size_t responseLen);

int networkBandInfoInd(unsigned int slotId, int indicationType, int token,
                       RIL_Errno e, void *response, size_t responseLen);

int responseModulationInfoInd(unsigned int slotId,
                       int indicationType, int token, RIL_Errno e, void *response,
                       size_t responseLen);

int responseCsNetworkStateChangeInd(unsigned int slotId,
                       int indicationType, int token, RIL_Errno e, void *response,
                       size_t responseLen);

int resetAttachApnInd(unsigned int slotId, int indicationType, int token,
                      RIL_Errno e, void *response, size_t responseLen);

int responseInvalidSimInd(unsigned int slotId,
                       int indicationType, int token, RIL_Errno e, void *response,
                       size_t responseLen);

int responseLteNetworkInfo(unsigned int slotId, int indicationType,
                       int token, RIL_Errno e, void *response, size_t responseLen);

int mdChangeApnInd(unsigned int slotId, int indicationType, int token,
                   RIL_Errno e, void *response, size_t responseLen);

// MTK-START: SIM
int getATRResponse(unsigned int slotId, android::ClientId clientId,
                 int responseType, int serial, RIL_Errno e,
                 void *response, size_t responseLen);

int getIccidResponse(unsigned int slotId, android::ClientId clientId, int responseType, int serial,
        RIL_Errno e, void *response, size_t responseLen);

int setSimPowerResponse(unsigned int slotId, android::ClientId clientId,
                 int responseType, int serial, RIL_Errno e,
                 void *response, size_t responseLen);

int onVirtualSimStatusChanged(unsigned int slotId,
        int indicationType, int token, RIL_Errno e, void *response,
        size_t responseLen);

int onImeiLock(unsigned int slotId,
        int indicationType, int token, RIL_Errno e, void *response,
        size_t responseLen);

int onImsiRefreshDone(unsigned int slotId,
        int indicationType, int token, RIL_Errno e, void *response,
        size_t responseLen);

int onCardDetectedInd(unsigned int slotId,
        int indicationType, int token, RIL_Errno e, void *response,
        size_t responseLen);
// MTK-END

/// [IMS] Indication ////////////////////////////////////////////////////////////////////
int callInfoIndicationInd(unsigned int slotId,
                          int indicationType, int token, RIL_Errno e, void *response,
                          size_t responseLen);

int econfResultIndicationInd(unsigned int slotId,
                             int indicationType, int token, RIL_Errno e,
                             void *response, size_t responseLen);

int sipCallProgressIndicatorInd(unsigned int slotId,
                                int indicationType, int token, RIL_Errno e,
                                void *response, size_t responseLen);

int callmodChangeIndicatorInd(unsigned int slotId,
                              int indicationType, int token, RIL_Errno e,
                              void *response, size_t responseLen);

int videoCapabilityIndicatorInd(unsigned int slotId,
                                int indicationType, int token, RIL_Errno e,
                                void *response, size_t responseLen);

int onUssiInd(unsigned int slotId,
              int indicationType, int token, RIL_Errno e, void *response,
             size_t responseLen);

int getProvisionDoneInd(unsigned int slotId,
                        int indicationType, int token, RIL_Errno e,
                        void *response, size_t responseLen);

int imsCfgDynamicImsSwitchCompleteInd(unsigned int slotId,
                                          int indicationType, int token, RIL_Errno e,
                                          void *response, size_t responseLen);

int imsCfgFeatureChangedInd(unsigned int slotId,
                            int indicationType, int token, RIL_Errno e,
                            void *response, size_t responseLen);

int imsCfgConfigChangedInd(unsigned int slotId,
                           int indicationType, int token, RIL_Errno e,
                           void *response, size_t responseLen);

int imsCfgConfigLoadedInd(unsigned int slotId,
                           int indicationType, int token, RIL_Errno e,
                           void *response, size_t responseLen);

int imsRtpInfoInd(unsigned int slotId,
                  int indicationType, int token, RIL_Errno e, void *response,
                  size_t responseLen);

int onXuiInd(unsigned int slotId,
             int indicationType, int token, RIL_Errno e, void *response,
             size_t responseLen);

int onVolteSubscription(unsigned int slotId, int indicationType, int token,
                        RIL_Errno e, void *response, size_t responseLen);

int imsEventPackageIndicationInd(unsigned int slotId,
                                 int indicationType, int token, RIL_Errno e,
                                 void *response, size_t responseLen);

int imsRegistrationInfoInd(unsigned int slotId,
                           int indicationType, int token, RIL_Errno e,
                           void *response, size_t responseLen);

int imsEnableDoneInd(unsigned int slotId,
                     int indicationType, int token, RIL_Errno e,
                     void *response, size_t responseLen);

int imsDisableDoneInd(unsigned int slotId,
                      int indicationType, int token, RIL_Errno e,
                      void *response, size_t responseLen);

int imsEnableStartInd(unsigned int slotId,
                      int indicationType, int token, RIL_Errno e,
                      void *response, size_t responseLen);

int imsDisableStartInd(unsigned int slotId,
                       int indicationType, int token, RIL_Errno e,
                       void *response, size_t responseLen);

int ectIndicationInd(unsigned int slotId,
                     int indicationType, int token, RIL_Errno e,
                     void *response, size_t responseLen);

int volteSettingInd(unsigned int slotId,
                    int indicationType, int token, RIL_Errno e,
                    void *response, size_t responseLen);

int imsRegFlagInd(unsigned int slotId,
                int indicationType, int token, RIL_Errno e,
                void *response, size_t responseLen);

int imsBearerStateNotifyInd(unsigned int slotId,
                           int indicationType, int token, RIL_Errno e,
                           void *response, size_t responseLen);

int imsBearerInitInd(unsigned int slotId,
                     int indicationType, int token, RIL_Errno e,
                     void *response, size_t responseLen);

int imsDataInfoNotifyInd(unsigned int slotId,
                           int indicationType, int token, RIL_Errno e,
                           void *response, size_t responseLen);

int imsDeregDoneInd(unsigned int slotId,
                    int indicationType, int token, RIL_Errno e,
                    void *response, size_t responseLen);
int incomingCallIndicationInd(unsigned int slotId, int indicationType,
                    int token, RIL_Errno e, void *response, size_t responseLen);

int callAdditionalInfoInd(unsigned int slotId, int indicationType,
                    int token, RIL_Errno e, void *response, size_t responseLen);

int cipherIndicationInd(unsigned int slotId,
                               int indicationType, int token, RIL_Errno e,
                               void *response, size_t responseLen);

int multiImsCountInd(unsigned int slotId,
          int indicationType, int token, RIL_Errno e,
          void *response, size_t responseLen);

int imsSupportEccInd(unsigned int slotId,
                     int indicationType, int token, RIL_Errno e,
                     void *response, size_t responseLen);

int redialEmergencyIndication(unsigned int slotId, int indicationType,
                      int token, RIL_Errno e, void *response, size_t responseLen);

int emergencyBearerInfoInd(unsigned int slotId, int indicationType,
                      int token, RIL_Errno e, void *response, size_t responseLen);

int imsRadioInfoChangeInd(unsigned int slotId,
                     int indicationType, int token, RIL_Errno e,
                     void *response, size_t responseLen);

int eregrtInfoInd(unsigned int slotId,
        int indicationType, int token, RIL_Errno e, void *response, size_t responseLen);

int mdInternetUsageIndication(unsigned int slotId, int indicationType,
        int token, RIL_Errno e, void *response, size_t responseLen);
/// [IMS] Indication End

// MTK-START: SIM ME LOCK
int queryNetworkLockResponse(unsigned int slotId, android::ClientId clientId,
        int responseType, int serial, RIL_Errno e,
        void *response, size_t responseLen);

int setNetworkLockResponse(unsigned int slotId, android::ClientId clientId,
        int responseType, int serial, RIL_Errno e,
        void *response, size_t responseLen);

int supplyDepersonalizationResponse(unsigned int slotId, android::ClientId clientId, int responseType,
        int serial, RIL_Errno e, void *response, size_t responselen);
// MTK-END

int confSRVCCInd(unsigned int slotId, int indicationType, int token,
                 RIL_Errno e, void *response, size_t responseLen);

// World Phone part {
int setResumeRegistrationResponse(unsigned int slotId, android::ClientId clientId,
                               int responseType, int serial, RIL_Errno e,
                               void *response, size_t responseLen);

int modifyModemTypeResponse(unsigned int slotId, android::ClientId clientId,
                               int responseType, int serial, RIL_Errno e,
                               void *response, size_t responseLen);

int plmnChangedIndication(unsigned int slotId,
                      int indicationType, int token, RIL_Errno e, void *response,
                      size_t responselen);

int registrationSuspendedIndication(unsigned int slotId,
                      int indicationType, int token, RIL_Errno e, void *response,
                      size_t responselen);

int gmssRatChangedIndication(unsigned int slotId,
                      int indicationType, int token, RIL_Errno e, void *response,
                      size_t responselen);

int worldModeChangedIndication(unsigned int slotId,
                      int indicationType, int token, RIL_Errno e, void *response,
                      size_t responselen);
// World Phone part }
int esnMeidChangeInd(unsigned int slotId,
                     int indicationType, int token, RIL_Errno e, void *response,
                     size_t responseLen);

int restartRILDResponse(unsigned int slotId, android::ClientId clientId, int responseType, int serial,
        RIL_Errno e, void *response, size_t responseLen);

// SMS-START
int getSmsParametersResponse(unsigned int slotId, android::ClientId clientId, int responseType,
        int token, RIL_Errno e, void *response, size_t responselen);
int setSmsParametersResponse(unsigned int slotId, android::ClientId clientId, int responseType,
        int token, RIL_Errno e, void *response, size_t responselen);
int getSmsMemStatusResponse(unsigned int slotId, android::ClientId clientId, int responseType,
        int serial, RIL_Errno e, void *response, size_t responseLen);
int meSmsStorageFullInd(unsigned int slotId, int indicationType,
        int token, RIL_Errno e, void *response, size_t responseLen);
int smsReadyInd(unsigned int slotId, int indicationType, int token,
        RIL_Errno e, void *response, size_t responseLen);
int smsInfoExtInd(unsigned int slotId, int indicationType, int token,
        RIL_Errno e, void *response, size_t responselen);
int setGsmBroadcastLangsResponse(unsigned int slotId, android::ClientId clientId,
        int responseType, int serial, RIL_Errno e, void *response, size_t responseLen);
int getGsmBroadcastLangsResponse(unsigned int slotId, android::ClientId clientId,
        int responseType, int serial, RIL_Errno e, void *response, size_t responseLen);
int getGsmBroadcastActivationRsp(unsigned int slotId, android::ClientId clientId,
        int responseType, int serial, RIL_Errno e, void *response, size_t responseLen);
int setEtwsResponse(unsigned int slotId, android::ClientId clientId, int responseType,
        int token, RIL_Errno e, void *response, size_t responselen);
int removeCbMsgResponse(unsigned int slotId, android::ClientId clientId, int responseType, int serial,
        RIL_Errno e, void *response, size_t responseLen);
int newEtwsInd(unsigned int slotId, int indicationType, int token, RIL_Errno e,
        void *response, size_t responselen);
int sendImsSmsExResponse(unsigned int slotId, android::ClientId clientId, int responseType,
                      int serial, RIL_Errno e, void *response, size_t responselen);
int acknowledgeLastIncomingGsmSmsExResponse(unsigned int slotId, android::ClientId clientId,
        int responseType, int serial, RIL_Errno e, void *response, size_t responseLen);
int newSmsStatusReportIndEx(unsigned int slotId,
        int indicationType, int token, RIL_Errno e, void *response, size_t responselen);
int newSmsIndEx(unsigned int slotId,
        int indicationType, int token, RIL_Errno e, void *response, size_t responselen);
int acknowledgeLastIncomingCdmaSmsExResponse(unsigned int slotId, android::ClientId clientId,
                                          int responseType, int serial, RIL_Errno e, void *response,
                                          size_t responselen);
int cdmaNewSmsIndEx(unsigned int slotId, int indicationType,
                  int token, RIL_Errno e, void *response, size_t responselen);

// SMS-END

/// M: eMBMS feature
int sendEmbmsAtCommandResponse(unsigned int slotId, android::ClientId clientId,
                            int responseType, int serial, RIL_Errno e,
                            void *response, size_t responseLen);
int embmsSessionStatusInd(unsigned int slotId, int indicationType, int token,
                      RIL_Errno e, void *response, size_t responselen);

int embmsAtInfoInd(unsigned int slotId, int indicationType, int token,
                   RIL_Errno e, void *response, size_t responselen);
/// M: eMBMS end

// / M: BIP, only to build pass {
int bipProactiveCommandInd(unsigned int slotId, int indicationType,
                           int token, RIL_Errno e, void *response, size_t responselen);
// / M: BIP }
// / M: OTASP, only to build pass {
int triggerOtaSPInd(unsigned int slotId, int indicationType,
                           int token, RIL_Errno e, void *response, size_t responselen);
// / M: OTASP }

// / M: STK, only to build pass {
int onStkMenuResetInd(unsigned int slotId, int indicationType,
                           int token, RIL_Errno e, void *response, size_t responselen);

int handleStkCallSetupRequestFromSimWithResCodeResponse(unsigned int slotId, android::ClientId clientId,
                                            int responseType, int serial, RIL_Errno e,
                                            void *response, size_t responselen);
// / M: STK }

int syncDataSettingsToMdResponse(unsigned int slotId, android::ClientId clientId,
                            int indicationType, int token, RIL_Errno e, void *response,
                            size_t responselen);

// M: Data Framework - Data Retry enhancement @{
int resetMdDataRetryCountResponse(unsigned int slotId, android::ClientId clientId,
                            int indicationType, int token, RIL_Errno e, void *response,
                            size_t responselen);

int onMdDataRetryCountReset(unsigned int slotId, int indicationType, int token,
                            RIL_Errno e, void *response, size_t responseLen);
// M: Data Framework - Data Retry enhancement @}

// M: Data Framework - CC 33 @{
int setRemoveRestrictEutranModeResponse(unsigned int slotId, android::ClientId clientId,
                            int indicationType, int token, RIL_Errno e, void *response,
                            size_t responselen);
int onRemoveRestrictEutran(unsigned int slotId, int indicationType, int token,
                            RIL_Errno e, void *response, size_t responseLen);
// M: Data Framework - CC 33 @}

// MTK-START: SIM HOT SWAP / SIM RECOVERY
int onSimPlugIn(unsigned int slotId,
        int indicationType, int token, RIL_Errno e, void *response,
        size_t responseLen);

int onSimPlugOut(unsigned int slotId,
        int indicationType, int token, RIL_Errno e, void *response,
        size_t responseLen);

int onSimMissing(unsigned int slotId,
        int indicationType, int token, RIL_Errno e, void *response,
        size_t responseLen);

int onSimRecovery(unsigned int slotId,
        int indicationType, int token, RIL_Errno e, void *response,
        size_t responseLen);
// MTK-END
// MTK-START: SIM POWER
int onSimPowerChangedInd(unsigned int slotId, int indicationType, int token,
        RIL_Errno e, void *response, size_t responseLen);
// MTK-END

// MTK-START: SIM COMMON SLOT
int onSimTrayPlugIn(unsigned int slotId,
        int indicationType, int token, RIL_Errno e, void *response,
        size_t responseLen);

int onSimCommonSlotNoChanged(unsigned int slotId,
        int indicationType, int token, RIL_Errno e, void *response,
        size_t responseLen);
// MTK-END

int getFemtocellListResponse(unsigned int slotId, android::ClientId clientId, int responseType, int serial,
                         RIL_Errno e, void *response, size_t responseLen);

int abortFemtocellListResponse(unsigned int slotId, android::ClientId clientId, int responseType,
                         int serial, RIL_Errno e, void *response, size_t responseLen);

int selectFemtocellResponse(unsigned int slotId, android::ClientId clientId, int responseType, int serial,
                         RIL_Errno e, void *response, size_t responseLen);

int queryFemtoCellSystemSelectionModeResponse(unsigned int slotId, android::ClientId clientId,
                         int responseType, int serial, RIL_Errno e, void *response,
                         size_t responseLen);

int setFemtoCellSystemSelectionModeResponse(unsigned int slotId, android::ClientId clientId,
                         int responseType, int serial, RIL_Errno e, void *response,
                         size_t responseLen);

int responseFemtocellInfo(unsigned int slotId, int responseType, int serial,
                         RIL_Errno e, void *response, size_t responseLen);

int networkInfoInd(unsigned int slotId, int indicationType, int token,
        RIL_Errno e, void *response, size_t responseLen);

int setRxTestConfigResponse(unsigned int slotId, android::ClientId clientId, int responseType, int serial,
        RIL_Errno e, void *response, size_t responseLen);
int getRxTestResultResponse(unsigned int slotId, android::ClientId clientId, int responseType, int serial,
        RIL_Errno e, void *response, size_t responseLen);

int getPOLCapabilityResponse(unsigned int slotId, android::ClientId clientId, int responseType, int serial,
                         RIL_Errno e, void *response, size_t responseLen);

int getCurrentPOLListResponse(unsigned int slotId, android::ClientId clientId, int responseType, int serial,
                         RIL_Errno e, void *response, size_t responseLen);

int setPOLEntryResponse(unsigned int slotId, android::ClientId clientId, int responseType, int serial,
                         RIL_Errno e, void *response, size_t responseLen);

// PHB START
int queryPhbStorageInfoResponse(unsigned int slotId, android::ClientId clientId,
                                int responseType, int serial, RIL_Errno e,
                                void *response, size_t responseLen);

int writePhbEntryResponse(unsigned int slotId, android::ClientId clientId,
                          int responseType, int serial, RIL_Errno e,
                          void *response, size_t responseLen);

int readPhbEntryResponse(unsigned int slotId, android::ClientId clientId,
                         int responseType, int serial, RIL_Errno e,
                         void *response, size_t responseLen);

int queryUPBCapabilityResponse(unsigned int slotId, android::ClientId clientId,
                               int responseType, int serial, RIL_Errno e,
                               void *response, size_t responseLen);

int editUPBEntryResponse(unsigned int slotId, android::ClientId clientId,
                         int responseType, int serial, RIL_Errno e,
                         void *response, size_t responseLen);

int deleteUPBEntryResponse(unsigned int slotId, android::ClientId clientId,
                           int responseType, int serial, RIL_Errno e,
                           void *response, size_t responseLen);

int readUPBGasListResponse(unsigned int slotId, android::ClientId clientId,
                           int responseType, int serial, RIL_Errno e,
                           void *response, size_t responseLen);

int readUPBGrpEntryResponse(unsigned int slotId, android::ClientId clientId,
                            int responseType, int serial, RIL_Errno e,
                            void *response, size_t responseLen);

int writeUPBGrpEntryResponse(unsigned int slotId, android::ClientId clientId,
                             int responseType, int serial, RIL_Errno e,
                             void *response, size_t responseLen);

int getPhoneBookStringsLengthResponse(unsigned int slotId, android::ClientId clientId,
                                      int responseType, int serial, RIL_Errno e,
                                      void *response, size_t responseLen);

int getPhoneBookMemStorageResponse(unsigned int slotId, android::ClientId clientId,
                                   int responseType, int serial, RIL_Errno e,
                                   void *response, size_t responseLen);

int setPhoneBookMemStorageResponse(unsigned int slotId, android::ClientId clientId,
                                    int responseType, int serial, RIL_Errno e,
                                    void *response, size_t responseLen);

int readPhoneBookEntryExtResponse(unsigned int slotId, android::ClientId clientId,
                                  int responseType, int serial, RIL_Errno e,
                                  void *response, size_t responseLen);

int writePhoneBookEntryExtResponse(unsigned int slotId, android::ClientId clientId,
                                   int responseType, int serial, RIL_Errno e,
                                   void *response, size_t responseLen);

int queryUPBAvailableResponse(unsigned int slotId, android::ClientId clientId,
                              int responseType, int serial, RIL_Errno e,
                              void *response, size_t responseLen);

int readUPBEmailEntryResponse(unsigned int slotId, android::ClientId clientId,
                              int responseType, int serial, RIL_Errno e,
                              void *response, size_t responseLen);

int readUPBSneEntryResponse(unsigned int slotId, android::ClientId clientId,
                            int responseType, int serial, RIL_Errno e,
                            void *response, size_t responseLen);

int readUPBAnrEntryResponse(unsigned int slotId, android::ClientId clientId,
                            int responseType, int serial, RIL_Errno e,
                            void *response, size_t responseLen);

int readUPBAasListResponse(unsigned int slotId, android::ClientId clientId,
                           int responseType, int serial, RIL_Errno e,
                           void *response, size_t responseLen);

int phbReadyNotificationInd(unsigned int slotId,
                            int indicationType, int token, RIL_Errno e, void *response,
                            size_t responselen);

int setPhonebookReadyResponse(unsigned int slotId, android::ClientId clientId,
                               int responseType, int serial, RIL_Errno e,
                               void *response, size_t responseLen);
// PHB END

int setTrmResponse(unsigned int slotId, android::ClientId clientId, int responseType, int serial,
        RIL_Errno e, void *response, size_t responseLen);

// APC
int setApcModeResponse(unsigned int slotId, android::ClientId clientId, int indicationType, int token,
        RIL_Errno e, void *response, size_t responseLen);

int getApcInfoResponse(unsigned int slotId, android::ClientId clientId, int indicationType, int token,
        RIL_Errno e, void *response, size_t responseLen);

int onPseudoCellInfoInd(unsigned int slotId, int indicationType, int token,
        RIL_Errno e, void *response, size_t responseLen);

int setDisable2GResponse(unsigned int slotId, android::ClientId clientId,
        int responseType, int serial, RIL_Errno e,
        void *response, size_t responseLen);

int getDisable2GResponse(unsigned int slotId, android::ClientId clientId,
        int responseType, int serial, RIL_Errno e,
        void *response, size_t responseLen);

/// M: [Network][C2K] Sprint roaming control @{
int setRoamingEnableResponse(unsigned int slotId, android::ClientId clientId, int responseType, int serial,
        RIL_Errno e, void *response, size_t responseLen);

int getRoamingEnableResponse(unsigned int slotId, android::ClientId clientId, int responseType, int serial,
        RIL_Errno e, void *response, size_t responseLen);
/// @}

int setLteReleaseVersionResponse(unsigned int slotId, android::ClientId clientId, int responseType,
        int serial, RIL_Errno e, void *response, size_t responselen);

int getLteReleaseVersionResponse(unsigned int slotId, android::ClientId clientId, int responseType,
        int serial, RIL_Errno e, void *response, size_t responselen);

int onMccMncChangedInd(unsigned int slotId, int indicationType, int token,
        RIL_Errno err, void *response, size_t responseLen);

int triggerModeSwitchByEccResponse(unsigned int slotId, android::ClientId clientId, int responseType,
        int serial, RIL_Errno e, void *response, size_t responseLen);

int setModemPowerResponse(unsigned int slotId, android::ClientId clientId, int responseType, int serial,
        RIL_Errno e, void *response, size_t responseLen);

// External SIM [Start]
int vsimNotificationResponse(unsigned int slotId, android::ClientId clientId, int responseType, int serial,
        RIL_Errno e, void *response, size_t responseLen);

int vsimOperationResponse(unsigned int slotId, android::ClientId clientId, int responseType, int serial,
        RIL_Errno e, void *response, size_t responseLen);

int onVsimEventIndication(unsigned int slotId,
        int indicationType, int token, RIL_Errno e, void *response, size_t responselen);

// External SIM [End]
int setVoiceDomainPreferenceResponse(unsigned int slotId, android::ClientId clientId,
                            int responseType, int token, RIL_Errno e, void *response,
                            size_t responselen);

int getVoiceDomainPreferenceResponse(unsigned int slotId, android::ClientId clientId,
                            int responseType, int token, RIL_Errno e, void *response,
                            size_t responselen);
/// Ims Data Framework {@
int dedicatedBearerActivationInd(unsigned int slotId, int indicationType,
        int serial, RIL_Errno e, void *response, size_t responseLen);
int dedicatedBearerModificationInd(unsigned int slotId, int indicationType,
        int serial, RIL_Errno e, void *response, size_t responseLen);
int dedicatedBearerDeactivationInd(unsigned int slotId, int indicationType,
        int serial, RIL_Errno e, void *response, size_t responseLen);
/// @}

int setWifiEnabledResponse(unsigned int slotId, android::ClientId clientId, int responseType, int serial,
        RIL_Errno err, void *response, size_t responseLen);

int setWifiAssociatedResponse(unsigned int slotId, android::ClientId clientId, int responseType, int serial,
        RIL_Errno err, void *response, size_t responseLen);

int setWfcConfigResponse(unsigned int slotId, android::ClientId clientId,
        int responseType, int serial, RIL_Errno err, void *response, size_t responseLen);

int getWfcConfigResponse(unsigned int slotId, android::ClientId clientId,
        int responseType, int serial, RIL_Errno err, void *response, size_t responseLen);

int setWifiSignalLevelResponse(unsigned int slotId, android::ClientId clientId, int responseType,
        int serial, RIL_Errno err, void *response, size_t responseLen);

int setWifiIpAddressResponse(unsigned int slotId, android::ClientId clientId, int responseType, int serial,
        RIL_Errno err, void *response, size_t responseLen);

int setLocationInfoResponse(unsigned int slotId, android::ClientId clientId, int responseType, int serial,
        RIL_Errno err, void *response, size_t responseLen);

int setEmergencyAddressIdResponse(unsigned int slotId, android::ClientId clientId, int responseType,
        int serial, RIL_Errno err, void *response, size_t responseLen);

int onWifiMonitoringThreshouldChanged(unsigned int slotId, int indicationType,
        int token, RIL_Errno err, void *response, size_t responseLen);

int onWifiPdnActivate(unsigned int slotId, int indicationType, int token,
        RIL_Errno err, void *response, size_t responseLen);

int onWfcPdnError(unsigned int slotId, int indicationType, int token,
        RIL_Errno err, void *response, size_t responseLen);

int onPdnHandover(unsigned int slotId, int indicationType, int token,
        RIL_Errno err, void *response, size_t responseLen);

int onWifiRoveout(unsigned int slotId, int indicationType, int token,
        RIL_Errno err, void *response, size_t responseLen);

int onLocationRequest(unsigned int slotId, int indicationType, int token,
        RIL_Errno err, void *response, size_t responseLen);

int onWfcPdnStateChanged(unsigned int slotId, int indicationType, int token,
        RIL_Errno err, void *response, size_t responseLen);

int setServiceStateToModemResponse(unsigned int slotId, android::ClientId clientId, int responseType,
        int serial, RIL_Errno err, void *response, size_t responseLen);

int setNattKeepAliveStatusResponse(unsigned int slotId, android::ClientId clientId, int responseType,
        int serial, RIL_Errno err, void *response, size_t responseLen);

int onNattKeepAliveChanged(unsigned int slotId, int indicationType, int token,
        RIL_Errno err, void *response, size_t responseLen);

int setWifiPingResultResponse(unsigned int slotId, android::ClientId clientId, int responseType, int serial,
        RIL_Errno err, void *response, size_t responseLen);

int onWifiPingRequest(unsigned int slotId, int indicationType, int token,
        RIL_Errno err, void *response, size_t responseLen);

int querySsacStatusResponse(unsigned int slotId, android::ClientId clientId, int responseType, int serial,
        RIL_Errno err, void *response, size_t responseLen);

int onSsacStatus(unsigned int slotId, int indicationType, int token,
        RIL_Errno err, void *response, size_t responseLen);

int onTxPowerIndication(unsigned int slotId, int indicationType, int token,
        RIL_Errno err, void *response, size_t responseLen);

int onTxPowerStatusIndication(unsigned int slotId, int indicationType,
        int token, RIL_Errno err, void *response, size_t responseLen);

int getCellInfoListResponse_1_2(unsigned int slotId, android::ClientId clientId, int indicationType,
        int token, RIL_Errno err, void *response, size_t responseLen);

int getIccCardStatusResponse_1_2(unsigned int slotId, android::ClientId clientId, int indicationType,
        int token, RIL_Errno err, void *response, size_t responseLen);

int getCurrentCallsResponse_1_2(unsigned int slotId, android::ClientId clientId, int indicationType,
        int token, RIL_Errno err, void *response, size_t responseLen);

int getSignalStrengthResponse_1_2(unsigned int slotId, android::ClientId clientId, int indicationType,
        int token, RIL_Errno err, void *response, size_t responseLen);

int getSignalStrengthWithWcdmaEcioResponse(unsigned int slotId, android::ClientId clientId,
        int indicationType, int token, RIL_Errno err, void *response, size_t responseLen);

int getVoiceRegistrationStateResponse_1_2(unsigned int slotId, android::ClientId clientId,
        int indicationType, int token, RIL_Errno err, void *response, size_t responseLen);

int getDataRegistrationStateResponse_1_2(unsigned int slotId, android::ClientId clientId,
        int indicationType, int token,RIL_Errno err, void *response, size_t responseLen);

int getIWlanRegistrationStateResponse(unsigned int slotId, android::ClientId clientId,
        int responseType, int serial, RIL_Errno e, void *response, size_t responseLen);

int iwlanRegistrationStateInd(unsigned int slotId, int indicationType, int token,
        RIL_Errno e, void *response, size_t responseLen);

int nrSysInfoInd(unsigned int slotId, int indicationType, int token,
        RIL_Errno e, void *response, size_t responseLen);

int networkScanResult_1_2(unsigned int slotId, android::ClientId clientId, int indicationType, int token,
        RIL_Errno err, void *response, size_t responseLen);

int cellInfoList_1_2(unsigned int slotId, android::ClientId clientId, int indicationType, int token,
        RIL_Errno err, void *response, size_t responseLen);

int currentSignalStrength_1_2(unsigned int slotId, android::ClientId clientId, int indicationType,
        int token, RIL_Errno err, void *response, size_t responseLen);

int currentSignalStrengthWithWcdmaEcioInd(unsigned int slotId,
        int indicationType, int token, RIL_Errno err, void *response, size_t responseLen);

int onWifiPdnOOS(unsigned int slotId, int indicationType, int token,
        RIL_Errno err, void *response, size_t responseLen);

int onWifiLock(unsigned int slotId, int indicationType,
        int token, RIL_Errno err, void *response, size_t responselen);

int onImsConferenceInfoIndication(unsigned int slotId, int indicationType,
        int token, RIL_Errno err, void *response, size_t responseLen);

int onLteMessageWaitingIndication(unsigned int slotId, int indicationType,
        int token, RIL_Errno err, void *response, size_t responseLen);

///M:Dialog Event Package Info @{
int imsDialogIndicationInd(unsigned int slotId, int indicationType, int token,
        RIL_Errno e, void *response, size_t responseLen);
///@}

int dataConnectionAttachResponse(unsigned int slotId, android::ClientId clientId, int responseType,
        int serial, RIL_Errno e, void *response, size_t responselen);

int dataConnectionDetachResponse(unsigned int slotId, android::ClientId clientId, int responseType,
        int serial, RIL_Errno e, void *response, size_t responselen);

int resetAllConnectionsResponse(unsigned int slotId, android::ClientId clientId, int responseType,
        int serial, RIL_Errno e, void *response, size_t responselen);

int setTxPowerStatusResponse(unsigned int slotId, android::ClientId clientId,
        int responseType, int serial, RIL_Errno e, void *response, size_t responseLen);

int setSuppServPropertyResponse(unsigned int slotId, android::ClientId clientId,
    int responseType, int token, RIL_Errno e, void *response, size_t responselen);

int onDsbpStateChanged(unsigned int slotId,
    int responseType, int token, RIL_Errno e, void *response, size_t responselen);

// MTK-START: SIM SLOT LOCK
int smlSlotLockInfoChangedInd(unsigned int slotId, int indicationType,
        int token, RIL_Errno e, void *response, size_t responseLen);
int supplyDeviceNetworkDepersonalizationResponse(unsigned int slotId, android::ClientId clientId,
        int responseType, int serial, RIL_Errno e, void *response, size_t responselen);
// MTK-END
// SIM RSU
int onRsuSimLockEvent(unsigned int slotId, int indicationType, int token, RIL_Errno e, void *response,
        size_t responseLen);

int getPlmnNameFromSE13TableResponse(unsigned int slotId, android::ClientId clientId,
                              int responseType, int serial, RIL_Errno e, void *response,
                              size_t responselen);

int enableCAPlusBandWidthFilterResponse(unsigned int slotId, android::ClientId clientId,
                              int responseType, int serial, RIL_Errno e, void *response,
                              size_t responselen);

///M: Notify ePDG screen state
int notifyEPDGScreenStateResponse(unsigned int slotId, android::ClientId clientId, int responseType,
        int serial, RIL_Errno err, void *response, size_t responseLen);

int oemHookRawInd(unsigned int slotId,
                  int indicationType, int token, RIL_Errno e, void *response,
                  size_t responselen);
int sendVopsIndication(unsigned int slotId, int indicationType, int token, RIL_Errno e,
        void *response, size_t responselen);
int queryVopsStatusResponse(unsigned int slotId, android::ClientId clientId,
        int responseType, int serial, RIL_Errno e, void *response, size_t responseLen);

// M: RTT @{
int setRttModeResponse(unsigned int slotId, android::ClientId clientId,
        int responseType, int serial, RIL_Errno e,
        void *response, size_t responselen);

int sendRttModifyRequestResponse(unsigned int slotId, android::ClientId clientId,
        int responseType, int serial, RIL_Errno e,
        void *response, size_t responselen);

int sendRttTextResponse(unsigned int slotId, android::ClientId clientId,
        int responseType, int serial, RIL_Errno e,
        void *response, size_t responselen);

int rttModifyRequestResponseResponse(unsigned int slotId, android::ClientId clientId,
        int responseType, int serial, RIL_Errno e,
        void *response, size_t responselen);

int toggleRttAudioIndicationResponse(unsigned int slotId, android::ClientId __unused,
        int responseType, int serial, RIL_Errno e, void *response, size_t responselen);

int rttModifyResponseInd(unsigned int slotId, int indicationType, int token, RIL_Errno e,
                         void *response, size_t responselen);

int rttTextReceiveInd(unsigned int slotId, int indicationType, int token, RIL_Errno e,
                      void *response, size_t responselen);

int rttCapabilityIndicationInd(unsigned int slotId, int indicationType, int token, RIL_Errno e,
                               void *response, size_t responselen);

int rttModifyRequestReceiveInd(unsigned int slotId, int indicationType, int token, RIL_Errno e,
                               void *response, size_t responselen);

int audioIndicationInd(unsigned int slotId, int indicationType, int token, RIL_Errno e,
                               void *response, size_t responselen);
// @}

int setSipHeaderResponse(unsigned int slotId, android::ClientId clientId,
    int responseType, int token, RIL_Errno e, void *response, size_t responselen);

int setSipHeaderReportResponse(unsigned int slotId, android::ClientId clientId,
    int responseType, int token, RIL_Errno e, void *response, size_t responselen);

int setImsCallModeResponse(unsigned int slotId, android::ClientId clientId,
    int responseType, int token, RIL_Errno e, void *response, size_t responselen);

int sipHeaderReportInd(unsigned int slotId,
    int indicationType, int token, RIL_Errno e, void *response, size_t responselen);

int callRatIndication(unsigned int slotId,
    int indicationType, int token, RIL_Errno e, void *response, size_t responselen);
// M: GWSD @{
int setGwsdModeResponse(unsigned int slotId, android::ClientId clientId __unused,
        int responseType, int serial, RIL_Errno e, void *response, size_t responseLen);
int setCallValidTimerResponse(unsigned int slotId, android::ClientId clientId __unused,
        int responseType, int serial, RIL_Errno e, void *response, size_t responseLen);
int setIgnoreSameNumberIntervalResponse(unsigned int slotId, android::ClientId clientId __unused,
        int responseType, int serial, RIL_Errno e, void *response, size_t responseLen);
int setKeepAliveByPDCPCtrlPDUResponse(unsigned int slotId, android::ClientId clientId __unused,
        int responseType, int serial, RIL_Errno e, void *response, size_t responseLen);
int setKeepAliveByIpDataResponse(unsigned int slotId, android::ClientId clientId __unused,
        int responseType, int serial, RIL_Errno e, void *response, size_t responseLen);
// @}

int qualifiedNetworkTypesChangedInd(unsigned int slotId,
        int indicationType, int token, RIL_Errno e, void *response,
        size_t responselen);
int sipRegInfoInd(unsigned int slotId, int indicationType, int token, RIL_Errno e,
        void *response, size_t responseLen);
int imsRegistrationStateInd(unsigned int slotId,
        int indicationType, int token, RIL_Errno e, void *response, size_t responseLen);
int eiregDataInd(unsigned int slotId,
        int indicationType, int token, RIL_Errno e, void *response, size_t responseLen);
int enableDsdaIndicationResponse(unsigned int slotId, android::ClientId clientId __unused,
        int responseType, int serial, RIL_Errno e, void *response, size_t responseLen);
int getDsdaStatusResponse(unsigned int slotId, android::ClientId clientId __unused,
        int responseType, int serial, RIL_Errno e, void *response, size_t responseLen);
int onDsdaChangedInd(unsigned int slotId,
    int responseType, int token, RIL_Errno e, void *response, size_t responselen);
int activateUiccCardRsp(unsigned int slotId, android::ClientId clientId, int responseType, int serial,
        RIL_Errno e, void *response, size_t responseLen);
int deactivateUiccCardRsp(unsigned int slotId, android::ClientId clientId, int responseType, int serial,
        RIL_Errno e, void *response, size_t responseLen);
int getCurrentUiccCardProvisioningStatusRsp(unsigned int slotId, android::ClientId clientId,
        int responseType, int serial, RIL_Errno e, void *response, size_t responseLen);
int radioStateChangedToImsInd(unsigned int slotId, int indicationType, int token, RIL_Errno e,
        void *response, size_t responseLen);
// MUSE WFC requirement
int registerCellQltyReportResponse(unsigned int slotId, android::ClientId clientId, int responseType, int serial,
        RIL_Errno e, void *response, size_t responselen);

// MUSE WFC requirement
int onCellularQualityChangedInd(unsigned int slotId, int indicationType, int token,
        RIL_Errno err, void *response, size_t responseLen);

int getSuggestedPlmnListResponse(unsigned int slotId, android::ClientId clientId __unused,
        int responseType, int serial, RIL_Errno e, void *response, size_t responseLen);

int routeCertificateResponse(unsigned int slotId, android::ClientId clientId __unused,
        int responseType, int serial, RIL_Errno e, void *response, size_t responseLen);
int routeAuthMessageResponse(unsigned int slotId, android::ClientId clientId __unused,
        int responseType, int serial, RIL_Errno e, void *response, size_t responseLen);
int enableCapabilityResponse(unsigned int slotId, android::ClientId clientId __unused,
        int responseType, int serial, RIL_Errno e, void *response, size_t responseLen);
int abortCertificateResponse(unsigned int slotId, android::ClientId clientId __unused,
        int responseType, int serial, RIL_Errno e, void *response, size_t responseLen);
int mobileDataUsageInd(unsigned int slotId, int indicationType, int token, RIL_Errno e,
        void *response, size_t responseLen);
int onNwLimitInd(unsigned int slotId, int indicationType, int token,
        RIL_Errno err, void *response, size_t responseLen);
int sendSarIndicatorResponse(unsigned int slotId, android::ClientId clientId __unused,
        int responseType, int serial, RIL_Errno e, void *response, size_t responseLen);
int iccidChangedInd(unsigned int slotId, int indicationType, int token,
        RIL_Errno err, void *response, size_t responseLen);
int setCallAdditionalInfoResponse(unsigned int slotId, android::ClientId clientId __unused,
        int responseType, int serial, RIL_Errno e, void *response, size_t responseLen);
int smartRatSwitchInd(unsigned int slotId,
                       int indicationType, int token, RIL_Errno e, void *response,
                       size_t responseLen);
int onPlmnDataInd(unsigned int slotId, int indicationType, int token,
        RIL_Errno err, void *response, size_t responseLen);
//RSU @{
int sendRsuRequestResponse(unsigned int slotId, android::ClientId clientId __unused,
        int responseType, int serial, RIL_Errno e, void *response, size_t responseLen);
int onRsuEvent(unsigned int slotId, int indicationType, int token, RIL_Errno e,
        void *response, size_t responseLen);
// @}
/// M: WIFI Relay @{
int sendWifiEnabledResponse(unsigned int slotId, android::ClientId clientId, int responseType, int serial,
        RIL_Errno err, void *response, size_t responseLen);

int sendWifiAssociatedResponse(unsigned int slotId, android::ClientId clientId, int responseType, int serial,
        RIL_Errno err, void *response, size_t responseLen);

int sendWifiIpAddressResponse(unsigned int slotId, android::ClientId clientId, int responseType, int serial,
        RIL_Errno err, void *response, size_t responseLen);
///@}

// [Softbank requirement]: Enable or disable call sub address feature.
int setCallSubAddressResponse(unsigned int slotId, android::ClientId clientId __unused,
        int responseType, int serial, RIL_Errno e, void *response, size_t responseLen);
int getCallSubAddressResponse(unsigned int slotId, android::ClientId clientId __unused,
        int responseType, int serial, RIL_Errno e, void *response, size_t responseLen);

///M:Video Ringtone Event indication and reponse to the request @{
int videoRingtoneEventInd(unsigned int slotId,
        int indicationType, int token, RIL_Errno e, void *response, size_t responseLen);

int videoRingtoneEventResponse(unsigned int slotId, android::ClientId clientId __unused,
        int responseType, int serial, RIL_Errno e, void *response, size_t responselen);
///@}

int getEngineeringModeInfoResponse(unsigned int slotId, android::ClientId clientId __unused,
        int responseType, int serial, RIL_Errno e, void *response, size_t responseLen);

int on5GUWInfoInd(unsigned int slotId,
            int indicationType, int token, RIL_Errno e, void *response, size_t responseLen);

}   // namespace mtkRadioEx
#endif  // RIL_SERVICE_H
