/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  Copyright (c) [2020], MediaTek Inc. All rights reserved.
*  This software/firmware and related documentation ("MediaTek Software") are
*  protected under relevant copyright laws.
*
*  The information contained herein is confidential and proprietary to
*  MediaTek Inc. and/or its licensors. Except as otherwise provided in the
*  applicable licensing terms with MediaTek Inc. and/or its licensors, any
*  reproduction, modification, use or disclosure of MediaTek Software, and
*  information contained herein, in whole or in part, shall be strictly
*  prohibited.
*****************************************************************************/

#ifndef __MIPC_MSG_TLV_CONST_H__
#define __MIPC_MSG_TLV_CONST_H__

#include "platform.h"

enum MIPC_MSG_enum {
    MIPC_MSG_NONE = 0,
    MIPC_REQ_BEGIN                                          = 0,

    MIPC_SYS_REQ_BEGIN                                      = MIPC_REQ_BEGIN + 0,
    /* get modem information */
    MIPC_SYS_GET_INFO_REQ                                   = MIPC_SYS_REQ_BEGIN + 1,
    /* the result for GET_INFO_REQ */
    MIPC_SYS_GET_INFO_CNF                                   = MIPC_SYS_REQ_BEGIN + 2,
    /* send AT command */
    MIPC_SYS_AT_REQ                                         = MIPC_SYS_REQ_BEGIN + 3,
    /* the result for AT_REQ */
    MIPC_SYS_AT_CNF                                         = MIPC_SYS_REQ_BEGIN + 4,
    /* reboot the whole device */
    MIPC_SYS_REBOOT_REQ                                     = MIPC_SYS_REQ_BEGIN + 5,
    /* the result for REBOOT_REQ */
    MIPC_SYS_REBOOT_CNF                                     = MIPC_SYS_REQ_BEGIN + 6,
    MIPC_SYS_GET_MAPPING_REQ                                = MIPC_SYS_REQ_BEGIN + 7,
    /* the result for GET_MAPPING_REQ */
    MIPC_SYS_GET_MAPPING_CNF                                = MIPC_SYS_REQ_BEGIN + 8,
    /* set SIM mapping */
    MIPC_SYS_SET_MAPPING_REQ                                = MIPC_SYS_REQ_BEGIN + 9,
    /* the result for SET_MAPPING_REQ */
    MIPC_SYS_SET_MAPPING_CNF                                = MIPC_SYS_REQ_BEGIN + 10,
    /* get thermal sensor num */
    MIPC_SYS_GET_THERMAL_SENSOR_NUM_REQ                     = MIPC_SYS_REQ_BEGIN + 15,
    /* the result for GET_THERMAL_SENSOR_NUM_REQ */
    MIPC_SYS_GET_THERMAL_SENSOR_NUM_CNF                     = MIPC_SYS_REQ_BEGIN + 16,
    /* get a thermal sensor info */
    MIPC_SYS_GET_THERMAL_SENSOR_INFO_REQ                    = MIPC_SYS_REQ_BEGIN + 17,
    /* the result for GET_THERMAL_SENSOR_INFO_REQ */
    MIPC_SYS_GET_THERMAL_SENSOR_INFO_CNF                    = MIPC_SYS_REQ_BEGIN + 18,
    /* set thermal alarm */
    MIPC_SYS_SET_THERMAL_SENSOR_REQ                         = MIPC_SYS_REQ_BEGIN + 19,
    /* the result for SET_THERMAL_SENSOR_REQ */
    MIPC_SYS_SET_THERMAL_SENSOR_CNF                         = MIPC_SYS_REQ_BEGIN + 20,
    /* get thermal sensor current state */
    MIPC_SYS_GET_THERMAL_SENSOR_REQ                         = MIPC_SYS_REQ_BEGIN + 21,
    /* the result for GET_THERMAL_SENSOR_REQ */
    MIPC_SYS_GET_THERMAL_SENSOR_CNF                         = MIPC_SYS_REQ_BEGIN + 22,
    /* get thermal actuator num */
    MIPC_SYS_GET_THERMAL_ACTUATOR_NUM_REQ                   = MIPC_SYS_REQ_BEGIN + 23,
    /* the result for GET_THERMAL_ACTUATOR_NUM_REQ */
    MIPC_SYS_GET_THERMAL_ACTUATOR_NUM_CNF                   = MIPC_SYS_REQ_BEGIN + 24,
    /* set thermal actuator */
    MIPC_SYS_SET_THERMAL_ACTUATOR_REQ                       = MIPC_SYS_REQ_BEGIN + 25,
    /* the result for SET_THERMAL_ACTUATOR_REQ */
    MIPC_SYS_SET_THERMAL_ACTUATOR_CNF                       = MIPC_SYS_REQ_BEGIN + 26,
    /* get thermal actuator */
    MIPC_SYS_GET_THERMAL_ACTUATOR_INFO_REQ                  = MIPC_SYS_REQ_BEGIN + 27,
    /* the result for GET_THERMAL_ACTUATOR_INFO_REQ */
    MIPC_SYS_GET_THERMAL_ACTUATOR_INFO_CNF                  = MIPC_SYS_REQ_BEGIN + 28,
    /* set modem configuration request */
    MIPC_SYS_SET_CONFIG_REQ                                 = MIPC_SYS_REQ_BEGIN + 29,
    /* set modem configuration response */
    MIPC_SYS_SET_CONFIG_CNF                                 = MIPC_SYS_REQ_BEGIN + 30,
    /* get modem configuration request */
    MIPC_SYS_GET_CONFIG_REQ                                 = MIPC_SYS_REQ_BEGIN + 31,
    /* get modem configuration response */
    MIPC_SYS_GET_CONFIG_CNF                                 = MIPC_SYS_REQ_BEGIN + 32,
    /* register configuration indication */
    MIPC_SYS_REG_CONFIG_REQ                                 = MIPC_SYS_REQ_BEGIN + 33,
    /* register configuration indication response */
    MIPC_SYS_REG_CONFIG_CNF                                 = MIPC_SYS_REQ_BEGIN + 34,
    /* enable or disable ADPCLK report */
    MIPC_SYS_SET_ADPCLK_REQ                                 = MIPC_SYS_REQ_BEGIN + 35,
    /*  */
    MIPC_SYS_SET_ADPCLK_CNF                                 = MIPC_SYS_REQ_BEGIN + 36,
    /* get current ADPCLK report */
    MIPC_SYS_GET_ADPCLK_REQ                                 = MIPC_SYS_REQ_BEGIN + 37,
    /*  */
    MIPC_SYS_GET_ADPCLK_CNF                                 = MIPC_SYS_REQ_BEGIN + 38,
    /*  */
    MIPC_SYS_SET_MD_LOG_MODE_REQ                            = MIPC_SYS_REQ_BEGIN + 39,
    /*  */
    MIPC_SYS_SET_MD_LOG_MODE_CNF                            = MIPC_SYS_REQ_BEGIN + 40,
    /*  */
    MIPC_SYS_GET_MD_LOG_MODE_REQ                            = MIPC_SYS_REQ_BEGIN + 41,
    /*  */
    MIPC_SYS_GET_MD_LOG_MODE_CNF                            = MIPC_SYS_REQ_BEGIN + 42,
    /*  */
    MIPC_SYS_SET_MD_LOG_LEVEL_REQ                           = MIPC_SYS_REQ_BEGIN + 43,
    /*  */
    MIPC_SYS_SET_MD_LOG_LEVEL_CNF                           = MIPC_SYS_REQ_BEGIN + 44,
    /*  */
    MIPC_SYS_GET_MD_LOG_LEVEL_REQ                           = MIPC_SYS_REQ_BEGIN + 45,
    /*  */
    MIPC_SYS_GET_MD_LOG_LEVEL_CNF                           = MIPC_SYS_REQ_BEGIN + 46,
    /*  */
    MIPC_SYS_SET_MD_LOG_LOCATION_REQ                        = MIPC_SYS_REQ_BEGIN + 47,
    /*  */
    MIPC_SYS_SET_MD_LOG_LOCATION_CNF                        = MIPC_SYS_REQ_BEGIN + 48,
    /*  */
    MIPC_SYS_GET_MD_LOG_LOCATION_REQ                        = MIPC_SYS_REQ_BEGIN + 49,
    /*  */
    MIPC_SYS_GET_MD_LOG_LOCATION_CNF                        = MIPC_SYS_REQ_BEGIN + 50,
    /*  */
    MIPC_SYS_WRITE_NVRAM_REQ                                = MIPC_SYS_REQ_BEGIN + 51,
    /*  */
    MIPC_SYS_WRITE_NVRAM_CNF                                = MIPC_SYS_REQ_BEGIN + 52,
    /*  */
    MIPC_SYS_READ_NVRAM_REQ                                 = MIPC_SYS_REQ_BEGIN + 53,
    /*  */
    MIPC_SYS_READ_NVRAM_CNF                                 = MIPC_SYS_REQ_BEGIN + 54,
    /*  */
    MIPC_SYS_AUTH_REQ                                       = MIPC_SYS_REQ_BEGIN + 55,
    /*  */
    MIPC_SYS_AUTH_CNF                                       = MIPC_SYS_REQ_BEGIN + 56,
    /*  */
    MIPC_SYS_SET_DAT_REQ                                    = MIPC_SYS_REQ_BEGIN + 57,
    /*  */
    MIPC_SYS_SET_DAT_CNF                                    = MIPC_SYS_REQ_BEGIN + 58,
    /*  */
    MIPC_SYS_GET_DAT_REQ                                    = MIPC_SYS_REQ_BEGIN + 59,
    /*  */
    MIPC_SYS_GET_DAT_CNF                                    = MIPC_SYS_REQ_BEGIN + 60,
    /*  */
    MIPC_SYS_MCF_REQ                                        = MIPC_SYS_REQ_BEGIN + 61,
    /*  */
    MIPC_SYS_MCF_CNF                                        = MIPC_SYS_REQ_BEGIN + 62,
    /* set FCC lock mode (need to auth first) */
    MIPC_SYS_SET_FCC_LOCK_REQ                               = MIPC_SYS_REQ_BEGIN + 63,
    /* the result for SET_FCC_LOCK_REQ */
    MIPC_SYS_SET_FCC_LOCK_CNF                               = MIPC_SYS_REQ_BEGIN + 64,
    /* set system time, the time given MUST be UTC time. */
    MIPC_SYS_SET_TIME_REQ                                   = MIPC_SYS_REQ_BEGIN + 65,
    /* the result for SET_TIME_REQ */
    MIPC_SYS_SET_TIME_CNF                                   = MIPC_SYS_REQ_BEGIN + 66,
    /* get system time expressed in UTC */
    MIPC_SYS_GET_TIME_REQ                                   = MIPC_SYS_REQ_BEGIN + 67,
    /* the result for GET_TIME_REQ */
    MIPC_SYS_GET_TIME_CNF                                   = MIPC_SYS_REQ_BEGIN + 68,
    /*  */
    MIPC_SYS_SET_SAR_REQ                                    = MIPC_SYS_REQ_BEGIN + 69,
    /*  */
    MIPC_SYS_SET_SAR_CNF                                    = MIPC_SYS_REQ_BEGIN + 70,
    /*  */
    MIPC_SYS_GET_SAR_REQ                                    = MIPC_SYS_REQ_BEGIN + 71,
    /*  */
    MIPC_SYS_GET_SAR_CNF                                    = MIPC_SYS_REQ_BEGIN + 72,
    /* set power saving mode */
    MIPC_SYS_SET_POWER_SAVING_REQ                           = MIPC_SYS_REQ_BEGIN + 73,
    /* the result for SET_POWER_SAVING_REQ */
    MIPC_SYS_SET_POWER_SAVING_CNF                           = MIPC_SYS_REQ_BEGIN + 74,
    /* <trigger DEVICE to start or stop the statistics of some connection parameters> or  <read DEVICE statitic info>; cant carry START&STOP in one MIPC_REQ; execute priority: STOP > READ > PERIOD > START; */
    MIPC_SYS_CONNECTIVITY_STATISTICS_REQ                    = MIPC_SYS_REQ_BEGIN + 75,
    /* rsp of CONNECTIVITY_STATISTICS_REQ */
    MIPC_SYS_CONNECTIVITY_STATISTICS_CNF                    = MIPC_SYS_REQ_BEGIN + 76,
    /* query device sbp info */
    MIPC_SYS_QUERY_SBP_REQ                                  = MIPC_SYS_REQ_BEGIN + 77,
    /* rsp of QUERY_SBP_REQ */
    MIPC_SYS_QUERY_SBP_CNF                                  = MIPC_SYS_REQ_BEGIN + 78,
    /* set Location Info */
    MIPC_SYS_SET_GEO_LOCATION_REQ                           = MIPC_SYS_REQ_BEGIN + 81,
    /* response of SET_GEO_LOCATION_REQ */
    MIPC_SYS_SET_GEO_LOCATION_CNF                           = MIPC_SYS_REQ_BEGIN + 82,
    /* command is used to configure and query DSBP information */
    MIPC_SYS_SET_DSBP_REQ                                   = MIPC_SYS_REQ_BEGIN + 83,
    /* response of SET_DSBP_REQ */
    MIPC_SYS_SET_DSBP_CNF                                   = MIPC_SYS_REQ_BEGIN + 84,
    /* command is used to send sar ind */
    MIPC_SYS_SEND_SAR_IND_REQ                               = MIPC_SYS_REQ_BEGIN + 85,
    /* response of SEND_SAR_IND_REQ */
    MIPC_SYS_SEND_SAR_IND_CNF                               = MIPC_SYS_REQ_BEGIN + 86,
    /* This command is used to infrom modem the reboot mode */
    MIPC_SYS_SILENT_REBOOT_REQ                              = MIPC_SYS_REQ_BEGIN + 87,
    /* response of SILENT_REBOOT_REQ */
    MIPC_SYS_SILENT_REBOOT_CNF                              = MIPC_SYS_REQ_BEGIN + 88,
    /* This command is used to infrom modem current project setting is single sim or dual sim,and need set before power on to flight mode */
    MIPC_SYS_MULTI_SIM_CONFIG_REQ                           = MIPC_SYS_REQ_BEGIN + 89,
    /* This command is used to infrom modem current project setting is single sim or dual sim,and need set before power on to flight mode */
    MIPC_SYS_MULTI_SIM_CONFIG_CNF                           = MIPC_SYS_REQ_BEGIN + 90,
    /* This command is used to infrom modem the reboot mode */
    MIPC_SYS_REBOOT_SET_REQ                                 = MIPC_SYS_REQ_BEGIN + 91,
    /* response of REBOOT_SET_REQ */
    MIPC_SYS_REBOOT_SET_CNF                                 = MIPC_SYS_REQ_BEGIN + 92,
    /*  */
    MIPC_SYS_GET_THERMAL_ACTUATOR_REQ                       = MIPC_SYS_REQ_BEGIN + 93,
    /*  */
    MIPC_SYS_GET_THERMAL_ACTUATOR_CNF                       = MIPC_SYS_REQ_BEGIN + 94,
    /* get_thermal_sensor_runtime_req */
    MIPC_SYS_GET_THERMAL_SENSOR_RUNTIME_REQ                 = MIPC_SYS_REQ_BEGIN + 95,
    /* get_thermal_sensor_runtime_cnf */
    MIPC_SYS_GET_THERMAL_SENSOR_RUNTIME_CNF                 = MIPC_SYS_REQ_BEGIN + 96,
    /* reset_nv>set_auto>set_trip>wb_nv */
    MIPC_SYS_SET_THERMAL_RUNTIME_REQ                        = MIPC_SYS_REQ_BEGIN + 97,
    /*  */
    MIPC_SYS_SET_THERMAL_RUNTIME_CNF                        = MIPC_SYS_REQ_BEGIN + 98,
    /* set or get SBP infomation, including SBP ID, SBP feature configuration and SBP feature data and param */
    MIPC_SYS_SET_OR_GET_SBP_INFO_REQ                        = MIPC_SYS_REQ_BEGIN + 99,
    /* response of SET_OR_GET_SBP_INFO_REQ */
    MIPC_SYS_SET_OR_GET_SBP_INFO_CNF                        = MIPC_SYS_REQ_BEGIN + 100,
    /*  */
    MIPC_SYS_GET_ALL_THERMAL_INFO_REQ                       = MIPC_SYS_REQ_BEGIN + 101,
    /*  */
    MIPC_SYS_GET_ALL_THERMAL_INFO_CNF                       = MIPC_SYS_REQ_BEGIN + 102,
    MIPC_SYS_REQ_END                                        = MIPC_SYS_REQ_BEGIN + 0xFF,

    MIPC_APN_REQ_BEGIN                                      = MIPC_REQ_BEGIN + 0x100,
    /* set LTE initial attach APN profile */
    MIPC_APN_SET_IA_REQ                                     = MIPC_APN_REQ_BEGIN + 1,
    /* the result for SET_IA_REQ */
    MIPC_APN_SET_IA_CNF                                     = MIPC_APN_REQ_BEGIN + 2,
    /* get LTE initial attach profile */
    MIPC_APN_GET_IA_REQ                                     = MIPC_APN_REQ_BEGIN + 3,
    /* the result for GET_IA_REQ */
    MIPC_APN_GET_IA_CNF                                     = MIPC_APN_REQ_BEGIN + 4,
    /* add an APN profile */
    MIPC_APN_ADD_PROFILE_REQ                                = MIPC_APN_REQ_BEGIN + 5,
    /* the result for ADD_PROFILE_REQ */
    MIPC_APN_ADD_PROFILE_CNF                                = MIPC_APN_REQ_BEGIN + 6,
    /* list current APN profiles */
    MIPC_APN_LIST_PROFILE_REQ                               = MIPC_APN_REQ_BEGIN + 7,
    /* the result for LIST_PROFILE_REQ */
    MIPC_APN_LIST_PROFILE_CNF                               = MIPC_APN_REQ_BEGIN + 8,
    /* delete an APN profile */
    MIPC_APN_DEL_PROFILE_REQ                                = MIPC_APN_REQ_BEGIN + 9,
    /* the result for DEL_PROFILE_REQ */
    MIPC_APN_DEL_PROFILE_CNF                                = MIPC_APN_REQ_BEGIN + 10,
    /* indicate host/ap will set apn profile or not */
    MIPC_APN_SET_PROFILE_STATUS_REQ                         = MIPC_APN_REQ_BEGIN + 11,
    /* the response of SET_PROFILE_STATUS_REQ */
    MIPC_APN_SET_PROFILE_STATUS_CNF                         = MIPC_APN_REQ_BEGIN + 12,
    /* list modem APN profiles and state */
    MIPC_APN_LIST_MD_PROFILE_REQ                            = MIPC_APN_REQ_BEGIN + 13,
    /* the result for LIST_PROFILE_REQ */
    MIPC_APN_LIST_MD_PROFILE_CNF                            = MIPC_APN_REQ_BEGIN + 14,
    /* to SET Verizon specific APN, it is different APN profile with MIPC_APN_ADD_PROFILE_REQ */
    MIPC_APN_SET_VZW_APN_REQ                                = MIPC_APN_REQ_BEGIN + 15,
    /* the response of SET_VZW_APN_REQ */
    MIPC_APN_SET_VZW_APN_CNF                                = MIPC_APN_REQ_BEGIN + 16,
    /* to SET Verizon specific APN timer, it is different APN profile with MIPC_APN_ADD_PROFILE_REQ */
    MIPC_APN_SET_VZW_APN_TIMER_REQ                          = MIPC_APN_REQ_BEGIN + 17,
    /* the response of SET_VZW_APN_REQ */
    MIPC_APN_SET_VZW_APN_TIMER_CNF                          = MIPC_APN_REQ_BEGIN + 18,
    /* add a profile list for modem, modem will replace old list with new list totally */
    MIPC_APN_ADD_PROFILE_LIST_REQ                           = MIPC_APN_REQ_BEGIN + 19,
    /* the response of ADD_PROFILE_LIST_REQ */
    MIPC_APN_ADD_PROFILE_LIST_CNF                           = MIPC_APN_REQ_BEGIN + 20,
    /* to set md prefer IA APN, modem will select initial APN for LTE or not */
    MIPC_APN_SET_IA_MD_PREFER_REQ                           = MIPC_APN_REQ_BEGIN + 21,
    /* response of SET_IA_MD_PREFER_REQ */
    MIPC_APN_SET_IA_MD_PREFER_CNF                           = MIPC_APN_REQ_BEGIN + 22,
    MIPC_APN_REQ_END                                        = MIPC_APN_REQ_BEGIN + 0xFF,

    MIPC_DATA_REQ_BEGIN                                     = MIPC_REQ_BEGIN + 0x200,
    /* activate a data call */
    MIPC_DATA_ACT_CALL_REQ                                  = MIPC_DATA_REQ_BEGIN + 1,
    /* the result for ACT_CALL_REQ */
    MIPC_DATA_ACT_CALL_CNF                                  = MIPC_DATA_REQ_BEGIN + 2,
    /* de-activate the data call */
    MIPC_DATA_DEACT_CALL_REQ                                = MIPC_DATA_REQ_BEGIN + 3,
    /* the result for DEACT_CALL_REQ */
    MIPC_DATA_DEACT_CALL_CNF                                = MIPC_DATA_REQ_BEGIN + 4,
    /* get the data call information */
    MIPC_DATA_GET_CALL_REQ                                  = MIPC_DATA_REQ_BEGIN + 5,
    /* the result for GET_CALL_REQ */
    MIPC_DATA_GET_CALL_CNF                                  = MIPC_DATA_REQ_BEGIN + 6,
    /* set packet filter white list (not matched packets will be dropped) */
    MIPC_DATA_SET_PACKET_FILTER_REQ                         = MIPC_DATA_REQ_BEGIN + 7,
    /* the result for SET_PACKET_FILTER_REQ */
    MIPC_DATA_SET_PACKET_FILTER_CNF                         = MIPC_DATA_REQ_BEGIN + 8,
    /* get current packet filter setting */
    MIPC_DATA_GET_PACKET_FILTER_REQ                         = MIPC_DATA_REQ_BEGIN + 9,
    /* the result for GET_PACKET_FILTER_REQ */
    MIPC_DATA_GET_PACKET_FILTER_CNF                         = MIPC_DATA_REQ_BEGIN + 10,
    /* get operator-specific PCO, at least one of ID or APN+index must be included */
    MIPC_DATA_GET_PCO_REQ                                   = MIPC_DATA_REQ_BEGIN + 11,
    /* the result for GET_PCO_REQ */
    MIPC_DATA_GET_PCO_CNF                                   = MIPC_DATA_REQ_BEGIN + 12,
    /* set specific sim slot data allow */
    MIPC_DATA_SET_DATA_ALLOW_REQ                            = MIPC_DATA_REQ_BEGIN + 13,
    /* the response of SET_DATA_ALLOW_REQ */
    MIPC_DATA_SET_DATA_ALLOW_CNF                            = MIPC_DATA_REQ_BEGIN + 14,
    /* get data call list in modem */
    MIPC_DATA_GET_MD_DATA_CALL_LIST_REQ                     = MIPC_DATA_REQ_BEGIN + 15,
    /* response of get data call list in modem */
    MIPC_DATA_GET_MD_DATA_CALL_LIST_CNF                     = MIPC_DATA_REQ_BEGIN + 16,
    /* set data config, including mobile data, data roaming, VoLTE, ims_test_mode, data_domestic_roaming, data_international_roaming */
    MIPC_DATA_SET_CONFIG_REQ                                = MIPC_DATA_REQ_BEGIN + 17,
    /* the response of SET_CONFIG_REQ */
    MIPC_DATA_SET_CONFIG_CNF                                = MIPC_DATA_REQ_BEGIN + 18,
    /* to get data config, including mobile data, data roaming, VoLTE, ims_test_mode, data_domestic_roaming, data_international_roaming */
    MIPC_DATA_GET_CONFIG_REQ                                = MIPC_DATA_REQ_BEGIN + 19,
    /* the response of get data config, including mobile data, data roaming, VoLTE, ims_test_mode, data_domestic_roaming, data_international_roaming */
    MIPC_DATA_GET_CONFIG_CNF                                = MIPC_DATA_REQ_BEGIN + 20,
    /* abort the data call before get the response of ACT CALL REQ */
    MIPC_DATA_ABORT_CALL_REQ                                = MIPC_DATA_REQ_BEGIN + 21,
    /* the response of ABORT_CALL_REQ */
    MIPC_DATA_ABORT_CALL_CNF                                = MIPC_DATA_REQ_BEGIN + 22,
    /* get related info of data call connection, such as established time, end time, reject cause, this MIPC REQ must include at least one of APN or ID, if call is connected, ID is suggested, if call is not connected, APN is suggested */
    MIPC_DATA_GET_CALL_INFO_REQ                             = MIPC_DATA_REQ_BEGIN + 23,
    /* the response of GET_CALL_INFO_REQ */
    MIPC_DATA_GET_CALL_INFO_CNF                             = MIPC_DATA_REQ_BEGIN + 24,
    /* get range of supported pdp cid */
    MIPC_DATA_GET_PDP_CID_REQ                               = MIPC_DATA_REQ_BEGIN + 25,
    /* response of GET_PDP_CID_REQ */
    MIPC_DATA_GET_PDP_CID_CNF                               = MIPC_DATA_REQ_BEGIN + 26,
    /* commond is used to query or set retry timer */
    MIPC_DATA_RETRY_TIMER_REQ                               = MIPC_DATA_REQ_BEGIN + 27,
    /* response of RETRY_TIMER_CNF */
    MIPC_DATA_RETRY_TIMER_CNF                               = MIPC_DATA_REQ_BEGIN + 28,
    /* commond is used to enable and to set the extended link capacity estimation reporting criteria */
    MIPC_DATA_SET_LINK_CAPACITY_REPORTING_CRITERIA_REQ      = MIPC_DATA_REQ_BEGIN + 29,
    /* response of SET_LINK_CAPACITY_REPORTING_CRITERIA_REQ */
    MIPC_DATA_SET_LINK_CAPACITY_REPORTING_CRITERIA_CNF      = MIPC_DATA_REQ_BEGIN + 30,
    /* commond is used to read Secondary PDP context dynamic parameters */
    MIPC_DATA_GET_DEDICATE_BEARER_INFO_REQ                  = MIPC_DATA_REQ_BEGIN + 31,
    /* response of GET_DEDICATE_BEARER_INFO_REQ */
    MIPC_DATA_GET_DEDICATE_BEARER_INFO_CNF                  = MIPC_DATA_REQ_BEGIN + 32,
    /* commond is used to get the quality of service parameters of the established PDP context */
    MIPC_DATA_GET_QOS_REQ                                   = MIPC_DATA_REQ_BEGIN + 33,
    /* response of GET_QOS_REQ */
    MIPC_DATA_GET_QOS_CNF                                   = MIPC_DATA_REQ_BEGIN + 34,
    /* commond is used to get the relevant information about Traffic Flow Template */
    MIPC_DATA_GET_TFT_REQ                                   = MIPC_DATA_REQ_BEGIN + 35,
    /* response of GET_TFT_REQ */
    MIPC_DATA_GET_TFT_CNF                                   = MIPC_DATA_REQ_BEGIN + 36,
    /* commond used to defined parameters which should be set before initiating a PDN connection */
    MIPC_DATA_SET_LGDCONT_REQ                               = MIPC_DATA_REQ_BEGIN + 37,
    /* response of SET_LGDCONT_REQ */
    MIPC_DATA_SET_LGDCONT_CNF                               = MIPC_DATA_REQ_BEGIN + 38,
    /* send the s-nssai value to modem when handover */
    MIPC_DATA_SET_NSSAI_REQ                                 = MIPC_DATA_REQ_BEGIN + 39,
    /* response of SET_NSSAI_REQ */
    MIPC_DATA_SET_NSSAI_CNF                                 = MIPC_DATA_REQ_BEGIN + 40,
    /* commond is used to start or stop keep alive */
    MIPC_DATA_KEEPALIVE_REQ                                 = MIPC_DATA_REQ_BEGIN + 41,
    /* response of KEEPALIVE_REQ */
    MIPC_DATA_KEEPALIVE_CNF                                 = MIPC_DATA_REQ_BEGIN + 42,
    /* commond is used to get DSDA state */
    MIPC_DATA_GET_DSDA_STATE_REQ                            = MIPC_DATA_REQ_BEGIN + 43,
    /* the response of get DSDA state */
    MIPC_DATA_GET_DSDA_STATE_CNF                            = MIPC_DATA_REQ_BEGIN + 44,
    /* commond is used to get the quality of service parameters of the established PDU session */
    MIPC_DATA_GET_5GQOS_REQ                                 = MIPC_DATA_REQ_BEGIN + 45,
    /* response of GET_5GQOS_REQ */
    MIPC_DATA_GET_5GQOS_CNF                                 = MIPC_DATA_REQ_BEGIN + 46,
    /* commond is used to handle PDU session ID,only for specific modem branch */
    MIPC_DATA_SET_PSI_REQ                                   = MIPC_DATA_REQ_BEGIN + 47,
    /* response of handle PDU session ID */
    MIPC_DATA_SET_PSI_CNF                                   = MIPC_DATA_REQ_BEGIN + 48,
    /* to GET UE NSSAI */
    MIPC_DATA_GET_NSSAI_REQ                                 = MIPC_DATA_REQ_BEGIN + 49,
    /* resposne of GET_NSSAI_REQ */
    MIPC_DATA_GET_NSSAI_CNF                                 = MIPC_DATA_REQ_BEGIN + 50,
    /* to get URSP route profile */
    MIPC_DATA_GET_URSP_ROUTE_PROFILE_REQ                    = MIPC_DATA_REQ_BEGIN + 51,
    /* response of get URSP route profile */
    MIPC_DATA_GET_URSP_ROUTE_PROFILE_CNF                    = MIPC_DATA_REQ_BEGIN + 52,
    /* to SET URSP UE policy */
    MIPC_DATA_SET_URSP_PRECONF_UE_POLICY_REQ                = MIPC_DATA_REQ_BEGIN + 53,
    /* reponse of SET URSP UE policy */
    MIPC_DATA_SET_URSP_PRECONF_UE_POLICY_CNF                = MIPC_DATA_REQ_BEGIN + 54,
    /* to GET URSP UE policy */
    MIPC_DATA_GET_URSP_UE_POLICY_REQ                        = MIPC_DATA_REQ_BEGIN + 55,
    /*  reponse of GET URSP UE policy */
    MIPC_DATA_GET_URSP_UE_POLICY_CNF                        = MIPC_DATA_REQ_BEGIN + 56,
    MIPC_DATA_REQ_END                                       = MIPC_DATA_REQ_BEGIN + 0xFF,

    MIPC_INTERNAL_REQ_BEGIN                                 = MIPC_REQ_BEGIN + 0x300,
    /*  */
    MIPC_INTERNAL_OPEN_REQ                                  = MIPC_INTERNAL_REQ_BEGIN + 1,
    /*  */
    MIPC_INTERNAL_OPEN_CNF                                  = MIPC_INTERNAL_REQ_BEGIN + 2,
    /*  */
    MIPC_INTERNAL_CLOSE_REQ                                 = MIPC_INTERNAL_REQ_BEGIN + 3,
    /*  */
    MIPC_INTERNAL_CLOSE_CNF                                 = MIPC_INTERNAL_REQ_BEGIN + 4,
    /*  */
    MIPC_INTERNAL_TEST_REQ                                  = MIPC_INTERNAL_REQ_BEGIN + 5,
    /*  */
    MIPC_INTERNAL_TEST_CNF                                  = MIPC_INTERNAL_REQ_BEGIN + 6,
    /*  */
    MIPC_INTERNAL_REGISTER_IND_REQ                          = MIPC_INTERNAL_REQ_BEGIN + 7,
    /*  */
    MIPC_INTERNAL_REGISTER_IND_CNF                          = MIPC_INTERNAL_REQ_BEGIN + 8,
    /*  */
    MIPC_INTERNAL_UNREGISTER_IND_REQ                        = MIPC_INTERNAL_REQ_BEGIN + 9,
    /*  */
    MIPC_INTERNAL_UNREGISTER_IND_CNF                        = MIPC_INTERNAL_REQ_BEGIN + 10,
    /*  */
    MIPC_INTERNAL_REGISTER_CMD_REQ                          = MIPC_INTERNAL_REQ_BEGIN + 11,
    /*  */
    MIPC_INTERNAL_REGISTER_CMD_CNF                          = MIPC_INTERNAL_REQ_BEGIN + 12,
    /*  */
    MIPC_INTERNAL_UNREGISTER_CMD_REQ                        = MIPC_INTERNAL_REQ_BEGIN + 13,
    /*  */
    MIPC_INTERNAL_UNREGISTER_CMD_CNF                        = MIPC_INTERNAL_REQ_BEGIN + 14,
    /*  */
    MIPC_INTERNAL_SET_FILTER_REQ                            = MIPC_INTERNAL_REQ_BEGIN + 15,
    /*  */
    MIPC_INTERNAL_SET_FILTER_CNF                            = MIPC_INTERNAL_REQ_BEGIN + 16,
    /*  */
    MIPC_INTERNAL_RESET_FILTER_REQ                          = MIPC_INTERNAL_REQ_BEGIN + 17,
    /*  */
    MIPC_INTERNAL_RESET_FILTER_CNF                          = MIPC_INTERNAL_REQ_BEGIN + 18,
    /*  */
    MIPC_INTERNAL_EIF_REQ                                   = MIPC_INTERNAL_REQ_BEGIN + 19,
    /*  */
    MIPC_INTERNAL_EIF_CNF                                   = MIPC_INTERNAL_REQ_BEGIN + 20,
    MIPC_INTERNAL_REQ_END                                   = MIPC_INTERNAL_REQ_BEGIN + 0xFF,

    MIPC_NW_REQ_BEGIN                                       = MIPC_REQ_BEGIN + 0x400,
    /* get radio on/off status */
    MIPC_NW_GET_RADIO_STATE_REQ                             = MIPC_NW_REQ_BEGIN + 1,
    /* the result for GET_RADIO_STATE_REQ */
    MIPC_NW_GET_RADIO_STATE_CNF                             = MIPC_NW_REQ_BEGIN + 2,
    /* turn SW radio on or off */
    MIPC_NW_SET_RADIO_STATE_REQ                             = MIPC_NW_REQ_BEGIN + 3,
    /* the result for SET_RADIO_STATE_REQ */
    MIPC_NW_SET_RADIO_STATE_CNF                             = MIPC_NW_REQ_BEGIN + 4,
    /* set registration mode */
    MIPC_NW_SET_REGISTER_STATE_REQ                          = MIPC_NW_REQ_BEGIN + 5,
    /* the result for SET_REGISTER_STATE_REQ */
    MIPC_NW_SET_REGISTER_STATE_CNF                          = MIPC_NW_REQ_BEGIN + 6,
    /* get current network registration status. */
    MIPC_NW_GET_REGISTER_STATE_REQ                          = MIPC_NW_REQ_BEGIN + 7,
    /* the result for GET_REGISTER_STATE_REQ */
    MIPC_NW_GET_REGISTER_STATE_CNF                          = MIPC_NW_REQ_BEGIN + 8,
    /* Get all the available operators in the network. */
    MIPC_NW_GET_PLMN_LIST_REQ                               = MIPC_NW_REQ_BEGIN + 9,
    /* The result for GET_PLMN_LIST_REQ */
    MIPC_NW_GET_PLMN_LIST_CNF                               = MIPC_NW_REQ_BEGIN + 10,
    /* do PS attach of detach */
    MIPC_NW_SET_PS_REQ                                      = MIPC_NW_REQ_BEGIN + 11,
    /* the result for SET_PS_REQ */
    MIPC_NW_SET_PS_CNF                                      = MIPC_NW_REQ_BEGIN + 12,
    /* get current PS attach status */
    MIPC_NW_GET_PS_REQ                                      = MIPC_NW_REQ_BEGIN + 13,
    /* the result for GET_PS_REQ */
    MIPC_NW_GET_PS_CNF                                      = MIPC_NW_REQ_BEGIN + 14,
    /* set singal report interval/threshold */
    MIPC_NW_SET_SIGNAL_REQ                                  = MIPC_NW_REQ_BEGIN + 15,
    /* the result for SET_SIGNAL_REQ */
    MIPC_NW_SET_SIGNAL_CNF                                  = MIPC_NW_REQ_BEGIN + 16,
    /* get current signal status */
    MIPC_NW_GET_SIGNAL_REQ                                  = MIPC_NW_REQ_BEGIN + 17,
    /* the result for GET_SIGNAL_REQ */
    MIPC_NW_GET_SIGNAL_CNF                                  = MIPC_NW_REQ_BEGIN + 18,
    /* get preferred PLMN list */
    MIPC_NW_GET_PREFERRED_PROVIDER_REQ                      = MIPC_NW_REQ_BEGIN + 19,
    /* the result for GET_PREFERRED_PROVIDER_REQ */
    MIPC_NW_GET_PREFERRED_PROVIDER_CNF                      = MIPC_NW_REQ_BEGIN + 20,
    /* set preferred PLMN list */
    MIPC_NW_SET_PREFERRED_PROVIDER_REQ                      = MIPC_NW_REQ_BEGIN + 21,
    /* the result for SET_PREFERRED_PROVIDER_REQ */
    MIPC_NW_SET_PREFERRED_PROVIDER_CNF                      = MIPC_NW_REQ_BEGIN + 22,
    /* set home PLMN */
    MIPC_NW_SET_HOME_PROVIDER_REQ                           = MIPC_NW_REQ_BEGIN + 23,
    /* the result for SET_HOME_PROVIDER_REQ */
    MIPC_NW_SET_HOME_PROVIDER_CNF                           = MIPC_NW_REQ_BEGIN + 24,
    /* get current home PLMN */
    MIPC_NW_GET_HOME_PROVIDER_REQ                           = MIPC_NW_REQ_BEGIN + 25,
    /* the result for GET_HOME_PROVIDER_REQ */
    MIPC_NW_GET_HOME_PROVIDER_CNF                           = MIPC_NW_REQ_BEGIN + 26,
    /* get current LTE initial attach status */
    MIPC_NW_GET_IA_STATUS_REQ                               = MIPC_NW_REQ_BEGIN + 27,
    /* the result for GET_IA_STATUS_REQ */
    MIPC_NW_GET_IA_STATUS_CNF                               = MIPC_NW_REQ_BEGIN + 28,
    /* get NITZ information(UTC time and timezone). */
    MIPC_NW_GET_NITZ_REQ                                    = MIPC_NW_REQ_BEGIN + 29,
    /* the result for GET_NITZ_REQ */
    MIPC_NW_GET_NITZ_CNF                                    = MIPC_NW_REQ_BEGIN + 30,
    /* enable/disable fast dormancy */
    MIPC_NW_SET_IDLE_HINT_REQ                               = MIPC_NW_REQ_BEGIN + 31,
    /* the result for SET_IDLE_HINT_REQ */
    MIPC_NW_SET_IDLE_HINT_CNF                               = MIPC_NW_REQ_BEGIN + 32,
    /* get current fast dormancy status */
    MIPC_NW_GET_IDLE_HINT_REQ                               = MIPC_NW_REQ_BEGIN + 33,
    /* the result for GET_IDLE_HINT_REQ */
    MIPC_NW_GET_IDLE_HINT_CNF                               = MIPC_NW_REQ_BEGIN + 34,
    /* get current base station information */
    MIPC_NW_GET_BASE_STATIONS_REQ                           = MIPC_NW_REQ_BEGIN + 35,
    /* the result for GET_BASE_STATIONS_REQ */
    MIPC_NW_GET_BASE_STATIONS_CNF                           = MIPC_NW_REQ_BEGIN + 36,
    /* get location information */
    MIPC_NW_GET_LOCATION_INFO_REQ                           = MIPC_NW_REQ_BEGIN + 37,
    /* the result for GET_LOCATION_INFO_REQ */
    MIPC_NW_GET_LOCATION_INFO_CNF                           = MIPC_NW_REQ_BEGIN + 38,
    /* set RAT mode(0: GSM; 1: UMTS; 2: GSM+UMTS; 3: LTE; 4: GSM+LTE; 5: UMTS+LTE; 6: GSM+UMTS+LTE; 7: C2K; 8: GSM+C2K; 9: UMTS+C2K; 10: GSM+UMTS+C2K; ......) */
    MIPC_NW_SET_RAT_REQ                                     = MIPC_NW_REQ_BEGIN + 39,
    /* the result for SET_RAT_REQ */
    MIPC_NW_SET_RAT_CNF                                     = MIPC_NW_REQ_BEGIN + 40,
    /* tranlsate plmn id to network name */
    MIPC_NW_GET_PROVIDER_NAME_REQ                           = MIPC_NW_REQ_BEGIN + 41,
    /* the result for GET_PROVIDER_NAME_REQ */
    MIPC_NW_GET_PROVIDER_NAME_CNF                           = MIPC_NW_REQ_BEGIN + 42,
    /* Get modem current rat info. */
    MIPC_NW_GET_RAT_REQ                                     = MIPC_NW_REQ_BEGIN + 43,
    /* Get modem current rat info. */
    MIPC_NW_GET_RAT_CNF                                     = MIPC_NW_REQ_BEGIN + 44,
    /* Enable or disable 5G. */
    MIPC_NW_SET_NR_REQ                                      = MIPC_NW_REQ_BEGIN + 45,
    /* Enable or disable 5G result. */
    MIPC_NW_SET_NR_CNF                                      = MIPC_NW_REQ_BEGIN + 46,
    /* get current CS attach status */
    MIPC_NW_GET_CS_REQ                                      = MIPC_NW_REQ_BEGIN + 47,
    /* get current CS attach status */
    MIPC_NW_GET_CS_CNF                                      = MIPC_NW_REQ_BEGIN + 48,
    /* Get available band mode. */
    MIPC_NW_GET_BAND_MODE_REQ                               = MIPC_NW_REQ_BEGIN + 49,
    /* Get available band mode information. */
    MIPC_NW_GET_BAND_MODE_CNF                               = MIPC_NW_REQ_BEGIN + 50,
    /* Set band mode information. */
    MIPC_NW_SET_BAND_MODE_REQ                               = MIPC_NW_REQ_BEGIN + 51,
    /* Set band mode information result. */
    MIPC_NW_SET_BAND_MODE_CNF                               = MIPC_NW_REQ_BEGIN + 52,
    /* Set channel lock parameters. */
    MIPC_NW_SET_CHANNEL_LOCK_REQ                            = MIPC_NW_REQ_BEGIN + 53,
    /* Set channel lock parameters result. */
    MIPC_NW_SET_CHANNEL_LOCK_CNF                            = MIPC_NW_REQ_BEGIN + 54,
    /* Read channel lock parameters. */
    MIPC_NW_GET_CHANNEL_LOCK_REQ                            = MIPC_NW_REQ_BEGIN + 55,
    /* Read channel lock parameters result. */
    MIPC_NW_GET_CHANNEL_LOCK_CNF                            = MIPC_NW_REQ_BEGIN + 56,
    /* Abort PLMN List search. */
    MIPC_NW_SET_ABORT_PLMN_LIST_SEARCH_REQ                  = MIPC_NW_REQ_BEGIN + 57,
    /* Abort PLMN List search result. */
    MIPC_NW_SET_ABORT_PLMN_LIST_SEARCH_CNF                  = MIPC_NW_REQ_BEGIN + 58,
    /* Get the capability for preferred list of networks. */
    MIPC_NW_GET_POL_CAPABILITY_REQ                          = MIPC_NW_REQ_BEGIN + 59,
    /* Get the capability for preferred list of networks response. */
    MIPC_NW_GET_POL_CAPABILITY_CNF                          = MIPC_NW_REQ_BEGIN + 60,
    /* Set the order of prefer RAT modes for network selection. */
    MIPC_NW_SET_PREFER_RAT_REQ                              = MIPC_NW_REQ_BEGIN + 61,
    /* The result for setting prefer rat. */
    MIPC_NW_SET_PREFER_RAT_CNF                              = MIPC_NW_REQ_BEGIN + 62,
    /* enable/disable lte carrier aggregation switch. */
    MIPC_NW_SET_LTE_CARRIER_AGGREGATION_SWITCH_REQ          = MIPC_NW_REQ_BEGIN + 67,
    /* Set lte carrier aggregation switch mode information result. */
    MIPC_NW_SET_LTE_CARRIER_AGGREGATION_SWITCH_CNF          = MIPC_NW_REQ_BEGIN + 68,
    /* Set the PS/CS registration state and roaming type for modem. */
    MIPC_NW_SET_PS_CS_REGISTRATION_STATE_ROAMING_TYPE_REQ   = MIPC_NW_REQ_BEGIN + 69,
    /* Set the PS/CS registration state and roaming type for modem result. */
    MIPC_NW_SET_PS_CS_REGISTRATION_STATE_ROAMING_TYPE_CNF   = MIPC_NW_REQ_BEGIN + 70,
    /* Get lte carrier aggregation switch. */
    MIPC_NW_GET_LTE_CARRIER_AGGREGATION_SWITCH_REQ          = MIPC_NW_REQ_BEGIN + 71,
    /* Get lte carrier aggregation switch response. */
    MIPC_NW_GET_LTE_CARRIER_AGGREGATION_SWITCH_CNF          = MIPC_NW_REQ_BEGIN + 72,
    /* Trigger the cell measurement. */
    MIPC_NW_CELL_MEASUREMENT_REQ                            = MIPC_NW_REQ_BEGIN + 75,
    /* The result for cell measurement. */
    MIPC_NW_CELL_MEASUREMENT_CNF                            = MIPC_NW_REQ_BEGIN + 76,
    /* Update the cell and band white list. */
    MIPC_NW_CELL_BAND_WHITE_LIST_LOCK_REQ                   = MIPC_NW_REQ_BEGIN + 77,
    /* Update the cell and band white list. */
    MIPC_NW_CELL_BAND_WHITE_LIST_LOCK_CNF                   = MIPC_NW_REQ_BEGIN + 78,
    /* Get LTE/NR ca info include cell index, cell state,band, bandwidth cw0_cqi and cw1_cqi. */
    MIPC_NW_GET_CELL_BAND_BANDWIDTH_REQ                     = MIPC_NW_REQ_BEGIN + 79,
    /* The band and bandwidth for LTE/NR */
    MIPC_NW_GET_CELL_BAND_BANDWIDTH_CNF                     = MIPC_NW_REQ_BEGIN + 80,
    /* Get 5G option configuration. */
    MIPC_NW_GET_NR_REQ                                      = MIPC_NW_REQ_BEGIN + 81,
    /* Get 5G option configuration. */
    MIPC_NW_GET_NR_CNF                                      = MIPC_NW_REQ_BEGIN + 82,
    /* Get srxlev information. */
    MIPC_NW_GET_SRXLEV_REQ                                  = MIPC_NW_REQ_BEGIN + 83,
    /* Get srxlev information. */
    MIPC_NW_GET_SRXLEV_CNF                                  = MIPC_NW_REQ_BEGIN + 84,
    /* set roaming mode configuartion. */
    MIPC_NW_SET_ROAMING_MODE_REQ                            = MIPC_NW_REQ_BEGIN + 85,
    /* result of set roaming mode cnf. */
    MIPC_NW_SET_ROAMING_MODE_CNF                            = MIPC_NW_REQ_BEGIN + 86,
    /* set roaming mode configuartion. */
    MIPC_NW_GET_ROAMING_MODE_REQ                            = MIPC_NW_REQ_BEGIN + 87,
    /* result of set roaming mode cnf. */
    MIPC_NW_GET_ROAMING_MODE_CNF                            = MIPC_NW_REQ_BEGIN + 88,
    /* Enable/disable of urc of the defined ind type . */
    MIPC_NW_SET_URC_ENABLE_REQ                              = MIPC_NW_REQ_BEGIN + 89,
    /* result of set ind enable cnf. */
    MIPC_NW_SET_URC_ENABLE_CNF                              = MIPC_NW_REQ_BEGIN + 90,
    /* Get plmn list with PLMNs arranged based on Signal Strength in the particular rat. */
    MIPC_NW_GET_SUGGESTED_PLMN_LIST_REQ                     = MIPC_NW_REQ_BEGIN + 91,
    /* The result for get suggested plmn list. */
    MIPC_NW_GET_SUGGESTED_PLMN_LIST_CNF                     = MIPC_NW_REQ_BEGIN + 92,
    /* set specified RAT`s PLMN for searching. */
    MIPC_NW_SET_SEARCH_STORE_FREQUENCY_INFO_REQ             = MIPC_NW_REQ_BEGIN + 93,
    /* set specified RAT`s PLMN for searching. */
    MIPC_NW_SET_SEARCH_STORE_FREQUENCY_INFO_CNF             = MIPC_NW_REQ_BEGIN + 94,
    /* Manual CSG selection. */
    MIPC_NW_SET_SELECT_FEMTOCELL_REQ                        = MIPC_NW_REQ_BEGIN + 95,
    /* Manual CSG selection. */
    MIPC_NW_SET_SELECT_FEMTOCELL_CNF                        = MIPC_NW_REQ_BEGIN + 96,
    /* config a2 offset. */
    MIPC_NW_SET_CONFIG_A2_OFFSET_REQ                        = MIPC_NW_REQ_BEGIN + 97,
    /* config a2 offset. */
    MIPC_NW_SET_CONFIG_A2_OFFSET_CNF                        = MIPC_NW_REQ_BEGIN + 98,
    /* config b1 offset. */
    MIPC_NW_SET_CONFIG_B1_OFFSET_REQ                        = MIPC_NW_REQ_BEGIN + 99,
    /* config b1 offset. */
    MIPC_NW_SET_CONFIG_B1_OFFSET_CNF                        = MIPC_NW_REQ_BEGIN + 100,
    /* report anbr. */
    MIPC_NW_SET_REPORT_ANBR_REQ                             = MIPC_NW_REQ_BEGIN + 101,
    /* report anbr. */
    MIPC_NW_SET_REPORT_ANBR_CNF                             = MIPC_NW_REQ_BEGIN + 102,
    /* report network registration status. */
    MIPC_NW_SET_NETWORK_EVENT_REQ                           = MIPC_NW_REQ_BEGIN + 103,
    /* report network registration status. */
    MIPC_NW_SET_NETWORK_EVENT_CNF                           = MIPC_NW_REQ_BEGIN + 104,
    /* enable ca plus filter. */
    MIPC_NW_SET_ENABLE_CA_PLUS_FILTER_REQ                   = MIPC_NW_REQ_BEGIN + 105,
    /* enable ca plus filter. */
    MIPC_NW_SET_ENABLE_CA_PLUS_FILTER_CNF                   = MIPC_NW_REQ_BEGIN + 106,
    /* Abort femtocell list. */
    MIPC_NW_ABORT_FEMTOCELL_LIST_REQ                        = MIPC_NW_REQ_BEGIN + 107,
    /* The result for ABORT_FEMTOCELL_LIST_REQ. */
    MIPC_NW_ABORT_FEMTOCELL_LIST_CNF                        = MIPC_NW_REQ_BEGIN + 108,
    /* Get femtocell list. */
    MIPC_NW_GET_FEMTOCELL_LIST_REQ                          = MIPC_NW_REQ_BEGIN + 109,
    /* The result for GET_FEMTOCELL_LIST_REQ. */
    MIPC_NW_GET_FEMTOCELL_LIST_CNF                          = MIPC_NW_REQ_BEGIN + 110,
    /* SET_PSEUDO_CELL_MODE_REQ. */
    MIPC_NW_SET_PSEUDO_CELL_MODE_REQ                        = MIPC_NW_REQ_BEGIN + 111,
    /* The result for SET_PSEUDO_CELL_MODE_REQ. */
    MIPC_NW_SET_PSEUDO_CELL_MODE_CNF                        = MIPC_NW_REQ_BEGIN + 112,
    /* GET_PSEUDO_CELL_INFO REQ. */
    MIPC_NW_GET_PSEUDO_CELL_INFO_REQ                        = MIPC_NW_REQ_BEGIN + 113,
    /* The result for GET_PSEUDO_CELL_INFO_REQ. */
    MIPC_NW_GET_PSEUDO_CELL_INFO_CNF                        = MIPC_NW_REQ_BEGIN + 114,
    /* SET_ROAMING_ENABLE_REQ. */
    MIPC_NW_SET_ROAMING_ENABLE_REQ                          = MIPC_NW_REQ_BEGIN + 115,
    /* The result for SET_ROAMING_ENABLE_REQ. */
    MIPC_NW_SET_ROAMING_ENABLE_CNF                          = MIPC_NW_REQ_BEGIN + 116,
    /* GET_ROAMING_ENABLE_REQ. */
    MIPC_NW_GET_ROAMING_ENABLE_REQ                          = MIPC_NW_REQ_BEGIN + 117,
    /* The result for GET_ROAMING_ENABLE_REQ. */
    MIPC_NW_GET_ROAMING_ENABLE_CNF                          = MIPC_NW_REQ_BEGIN + 118,
    /* SET_ROAMING_ENABLE_REQ. */
    MIPC_NW_SET_FEMTOCELL_SYSTEM_SELECTION_MODE_REQ         = MIPC_NW_REQ_BEGIN + 119,
    /* The result for SET_FEMTOCELL_SYSTEM_SELECTION_MODE_REQ. */
    MIPC_NW_SET_FEMTOCELL_SYSTEM_SELECTION_MODE_CNF         = MIPC_NW_REQ_BEGIN + 120,
    /* GET_FEMTOCELL_SYSTEM_SELECTION_MODE_REQ. */
    MIPC_NW_QUERY_FEMTOCELL_SYSTEM_SELECTION_MODE_REQ       = MIPC_NW_REQ_BEGIN + 121,
    /* The result for GET_FEMTOCELL_SYSTEM_SELECTION_MODE_REQ. */
    MIPC_NW_QUERY_FEMTOCELL_SYSTEM_SELECTION_MODE_CNF       = MIPC_NW_REQ_BEGIN + 122,
    /* Set network report status level. */
    MIPC_NW_SET_NW_IND_REPORT_LEVEL_REQ                     = MIPC_NW_REQ_BEGIN + 123,
    /* Set network state report level. */
    MIPC_NW_SET_NW_IND_REPORT_LEVEL_CNF                     = MIPC_NW_REQ_BEGIN + 124,
    /* Set disable 2g capability. This request is operator specificed, for the common use, please use the project config. */
    MIPC_NW_SET_DISABLE_2G_REQ                              = MIPC_NW_REQ_BEGIN + 125,
    /* Set disable 2G result. */
    MIPC_NW_SET_DISABLE_2G_CNF                              = MIPC_NW_REQ_BEGIN + 126,
    /* Get disable 2G config. */
    MIPC_NW_GET_DISABLE_2G_REQ                              = MIPC_NW_REQ_BEGIN + 127,
    /* Get disable 2g config. This request is operator specificed */
    MIPC_NW_GET_DISABLE_2G_CNF                              = MIPC_NW_REQ_BEGIN + 128,
    /* Set RAT switch for 4G/5G */
    MIPC_NW_SET_SMART_RAT_SWITCH_REQ                        = MIPC_NW_REQ_BEGIN + 129,
    /* Set RAT switch for 4G/5G result. */
    MIPC_NW_SET_SMART_RAT_SWITCH_CNF                        = MIPC_NW_REQ_BEGIN + 130,
    /* Get RAT switch for 4G/5G */
    MIPC_NW_GET_SMART_RAT_SWITCH_REQ                        = MIPC_NW_REQ_BEGIN + 131,
    /* Get RAT switch for 4G/5G state. */
    MIPC_NW_GET_SMART_RAT_SWITCH_CNF                        = MIPC_NW_REQ_BEGIN + 132,
    /* This interface allows users to perform RF test of control TX power. */
    MIPC_NW_VSS_ANTENNA_CONF_REQ                            = MIPC_NW_REQ_BEGIN + 133,
    /* This interface allows users to perform RF test of control TX power. */
    MIPC_NW_VSS_ANTENNA_CONF_CNF                            = MIPC_NW_REQ_BEGIN + 134,
    /* This interface allows users to perform RF test of control TX power. */
    MIPC_NW_VSS_ANTENNA_INFO_REQ                            = MIPC_NW_REQ_BEGIN + 135,
    /* This interface allows users to perform RF test of control TX power. */
    MIPC_NW_VSS_ANTENNA_INFO_CNF                            = MIPC_NW_REQ_BEGIN + 136,
    /* This interface is used to notify modem the radio capability of host. */
    MIPC_NW_SET_RADIO_CAPABILITY_REQ                        = MIPC_NW_REQ_BEGIN + 137,
    /* This interface is used to notify modem the radio capability of host. */
    MIPC_NW_SET_RADIO_CAPABILITY_CNF                        = MIPC_NW_REQ_BEGIN + 138,
    /* set cdma roaming preference. */
    MIPC_NW_SET_CDMA_ROAMING_PREFERENCE_REQ                 = MIPC_NW_REQ_BEGIN + 139,
    /* set cdma roaming preference. */
    MIPC_NW_SET_CDMA_ROAMING_PREFERENCE_CNF                 = MIPC_NW_REQ_BEGIN + 140,
    /* query cdma roaming preference. */
    MIPC_NW_GET_CDMA_ROAMING_PREFERENCE_REQ                 = MIPC_NW_REQ_BEGIN + 141,
    /* query cdma roaming preference. */
    MIPC_NW_GET_CDMA_ROAMING_PREFERENCE_CNF                 = MIPC_NW_REQ_BEGIN + 142,
    /* query barring info. */
    MIPC_NW_GET_BARRING_INFO_REQ                            = MIPC_NW_REQ_BEGIN + 143,
    /* query barring info. */
    MIPC_NW_GET_BARRING_INFO_CNF                            = MIPC_NW_REQ_BEGIN + 144,
    /* query ehrpd info. */
    MIPC_NW_GET_EHRPD_INFO_REQ                              = MIPC_NW_REQ_BEGIN + 145,
    /* query ehrpd info. */
    MIPC_NW_GET_EHRPD_INFO_CNF                              = MIPC_NW_REQ_BEGIN + 146,
    /* query egmss info. */
    MIPC_NW_GET_EGMSS_REQ                                   = MIPC_NW_REQ_BEGIN + 147,
    /* query egmss info. */
    MIPC_NW_GET_EGMSS_CNF                                   = MIPC_NW_REQ_BEGIN + 148,
    /* set cache endc connect mode. */
    MIPC_NW_SET_CACHE_ENDC_CONNECT_MODE_REQ                 = MIPC_NW_REQ_BEGIN + 149,
    /* result of cache endc mode config. */
    MIPC_NW_SET_CACHE_ENDC_CONNECT_MODE_CNF                 = MIPC_NW_REQ_BEGIN + 150,
    /* In some test, there maybe two cases that need exclusive behavior of the same handset, so need a mode to make sure work well. */
    MIPC_NW_SET_PS_TEST_MODE_REQ                            = MIPC_NW_REQ_BEGIN + 151,
    /* result of setting ps test mode. */
    MIPC_NW_SET_PS_TEST_MODE_CNF                            = MIPC_NW_REQ_BEGIN + 152,
    /* Get ps test mode. */
    MIPC_NW_GET_PS_TEST_MODE_REQ                            = MIPC_NW_REQ_BEGIN + 153,
    /* Result for getting ps test mode. */
    MIPC_NW_GET_PS_TEST_MODE_CNF                            = MIPC_NW_REQ_BEGIN + 154,
    /* set signal strength report criteria. */
    MIPC_NW_SET_SIGNAL_REPORT_CRITERIA_REQ                  = MIPC_NW_REQ_BEGIN + 155,
    /* Result of set signal report criteria. */
    MIPC_NW_SET_SIGNAL_REPORT_CRITERIA_CNF                  = MIPC_NW_REQ_BEGIN + 156,
    /* get the infomation of the CA. */
    MIPC_NW_GET_ECAINFO_REQ                                 = MIPC_NW_REQ_BEGIN + 157,
    /* the response result of get the ECAINFO. */
    MIPC_NW_GET_ECAINFO_CNF                                 = MIPC_NW_REQ_BEGIN + 158,
    /* query Activity info. */
    MIPC_NW_GET_ACTIVITY_INFO_REQ                           = MIPC_NW_REQ_BEGIN + 159,
    /* query Activity info. */
    MIPC_NW_GET_ACTIVITY_INFO_CNF                           = MIPC_NW_REQ_BEGIN + 160,
    /* This command is used to turn on/off CA. */
    MIPC_NW_SET_CA_REQ                                      = MIPC_NW_REQ_BEGIN + 163,
    /* The result of set ca req. */
    MIPC_NW_SET_CA_CNF                                      = MIPC_NW_REQ_BEGIN + 164,
    /* query lte RRC state. */
    MIPC_NW_GET_LTE_RRC_STATE_REQ                           = MIPC_NW_REQ_BEGIN + 165,
    /* LTE RRC state info. */
    MIPC_NW_GET_LTE_RRC_STATE_CNF                           = MIPC_NW_REQ_BEGIN + 166,
    /* This command is used to retrieve LTE available/unavailable 1xRTT cell list. */
    MIPC_NW_GET_LTE_1XRTT_CELL_LIST_REQ                     = MIPC_NW_REQ_BEGIN + 167,
    /* 1xRTT cell list info */
    MIPC_NW_GET_LTE_1XRTT_CELL_LIST_CNF                     = MIPC_NW_REQ_BEGIN + 168,
    /* clear lte available file. */
    MIPC_NW_CLEAR_LTE_AVAILABLE_FILE_REQ                    = MIPC_NW_REQ_BEGIN + 169,
    /* the result of clear lte available file. */
    MIPC_NW_CLEAR_LTE_AVAILABLE_FILE_CNF                    = MIPC_NW_REQ_BEGIN + 170,
    /* This command is used to get CA capability. */
    MIPC_NW_GET_CA_LINK_CAPABILITY_REQ                      = MIPC_NW_REQ_BEGIN + 171,
    /* CA link capability info */
    MIPC_NW_GET_CA_LINK_CAPABILITY_CNF                      = MIPC_NW_REQ_BEGIN + 172,
    /* This command is used to get CA capability. */
    MIPC_NW_GET_CA_LINK_ENABLE_STATUS_REQ                   = MIPC_NW_REQ_BEGIN + 173,
    /* This command is used to get CA capability. */
    MIPC_NW_GET_CA_LINK_ENABLE_STATUS_CNF                   = MIPC_NW_REQ_BEGIN + 174,
    /* This command is used to get TM9 enable status. */
    MIPC_NW_GET_TM9_ENABLE_STATUS_REQ                       = MIPC_NW_REQ_BEGIN + 175,
    /* TM9 enable status */
    MIPC_NW_GET_TM9_ENABLE_STATUS_CNF                       = MIPC_NW_REQ_BEGIN + 176,
    /* TM9 enable status */
    MIPC_NW_SET_TM9_ENABLE_STATUS_REQ                       = MIPC_NW_REQ_BEGIN + 177,
    /* The result of setting TM9 enable */
    MIPC_NW_SET_TM9_ENABLE_STATUS_CNF                       = MIPC_NW_REQ_BEGIN + 178,
    /* This command is used to query the configuration of MOA-DM/OTA-DM. */
    MIPC_NW_GET_OMADM_CONF_REQ                              = MIPC_NW_REQ_BEGIN + 179,
    /* The result of query the configuration of OMA-DM/OTA-DM */
    MIPC_NW_GET_OMADM_CONF_CNF                              = MIPC_NW_REQ_BEGIN + 180,
    /* This command is used to configure the modem settings for MOA-DM/OTA-DM. */
    MIPC_NW_SET_OMADM_CONF_REQ                              = MIPC_NW_REQ_BEGIN + 181,
    /* The result of configure OMA-DM */
    MIPC_NW_SET_OMADM_CONF_CNF                              = MIPC_NW_REQ_BEGIN + 182,
    /* This command is used to get ca band mode. */
    MIPC_NW_GET_CA_BAND_MODE_REQ                            = MIPC_NW_REQ_BEGIN + 183,
    /* The result of ca band mode. */
    MIPC_NW_GET_CA_BAND_MODE_CNF                            = MIPC_NW_REQ_BEGIN + 184,
    /* This command is used to set the CA combination band list. */
    MIPC_NW_SET_CA_LINK_ENABLE_STATUS_REQ                   = MIPC_NW_REQ_BEGIN + 185,
    /* The result of set the CA combination band list. */
    MIPC_NW_SET_CA_LINK_ENABLE_STATUS_CNF                   = MIPC_NW_REQ_BEGIN + 186,
    /* This command is used to get the LTE related data. */
    MIPC_NW_GET_LTE_DATA_REQ                                = MIPC_NW_REQ_BEGIN + 187,
    /* The result of getting the LTE related data. */
    MIPC_NW_GET_LTE_DATA_CNF                                = MIPC_NW_REQ_BEGIN + 188,
    /* This command is used to set TUW timer length */
    MIPC_NW_SET_TUW_TIMER_LENGTH_REQ                        = MIPC_NW_REQ_BEGIN + 189,
    /* The result of set tuw timer */
    MIPC_NW_SET_TUW_TIMER_LENGTH_CNF                        = MIPC_NW_REQ_BEGIN + 190,
    /* This command is used to get TUW timer length. */
    MIPC_NW_GET_TUW_TIMER_LENGTH_REQ                        = MIPC_NW_REQ_BEGIN + 191,
    /* The TUW timer length. */
    MIPC_NW_GET_TUW_TIMER_LENGTH_CNF                        = MIPC_NW_REQ_BEGIN + 192,
    /* This command is used to get 5GUW info. */
    MIPC_NW_GET_5GUW_INFO_REQ                               = MIPC_NW_REQ_BEGIN + 193,
    /* The 5GUW info. */
    MIPC_NW_GET_5GUW_INFO_CNF                               = MIPC_NW_REQ_BEGIN + 194,
    /* This command is used to get nr ca band. */
    MIPC_NW_GET_NR_CA_BAND_REQ                              = MIPC_NW_REQ_BEGIN + 195,
    /* nr ca band */
    MIPC_NW_GET_NR_CA_BAND_CNF                              = MIPC_NW_REQ_BEGIN + 196,
    /* This command is used to get nr5g subcarrier spacing in khz. */
    MIPC_NW_GET_NR_SCS_REQ                                  = MIPC_NW_REQ_BEGIN + 197,
    /* nr5g subcarrier spacing in khz */
    MIPC_NW_GET_NR_SCS_CNF                                  = MIPC_NW_REQ_BEGIN + 198,
    /* This command is used to get physical channel configs info. */
    MIPC_NW_GET_PHYSICAL_CHANNEL_CONFIGS_REQ                = MIPC_NW_REQ_BEGIN + 199,
    /* physical channel configs info */
    MIPC_NW_GET_PHYSICAL_CHANNEL_CONFIGS_CNF                = MIPC_NW_REQ_BEGIN + 200,
    /* The request of set or update the OS_ID. */
    MIPC_NW_OS_ID_UPDATE_REQ                                = MIPC_NW_REQ_BEGIN + 201,
    /* The result of the os_id update or set. */
    MIPC_NW_OS_ID_UPDATE_CNF                                = MIPC_NW_REQ_BEGIN + 202,
    /* Start network scan */
    MIPC_NW_START_NETWORK_SCAN_REQ                          = MIPC_NW_REQ_BEGIN + 203,
    /* The result to start network scan */
    MIPC_NW_START_NETWORK_SCAN_CNF                          = MIPC_NW_REQ_BEGIN + 204,
    /* This command is used to abort network scan */
    MIPC_NW_STOP_NETWORK_SCAN_REQ                           = MIPC_NW_REQ_BEGIN + 205,
    /* The result to abort network scan */
    MIPC_NW_STOP_NETWORK_SCAN_CNF                           = MIPC_NW_REQ_BEGIN + 206,
    /* This command is used to get whether it is supported to do network scan through MIPC_NW_START_NETWORK_SCAN_REQ. */
    MIPC_NW_GET_NETWORK_SCAN_SUPPORT_STATUS_REQ             = MIPC_NW_REQ_BEGIN + 207,
    /* If result is SUCCESS, network scan through MIPC_NW_START_NETWORK_SCAN_REQ is supported. Otherwise, it is not supported */
    MIPC_NW_GET_NETWORK_SCAN_SUPPORT_STATUS_CNF             = MIPC_NW_REQ_BEGIN + 208,
    /* the request of the default,allowed and prefered nssai get */
    MIPC_NW_GET_NSSAI_REQ                                   = MIPC_NW_REQ_BEGIN + 213,
    /* the response of the GET_NSSAI_REQ */
    MIPC_NW_GET_NSSAI_CNF                                   = MIPC_NW_REQ_BEGIN + 214,
    /* Set 5GUC timer length and band bitmap */
    MIPC_NW_SET_5GUC_REQ                                    = MIPC_NW_REQ_BEGIN + 215,
    /* Set 5GUC cnf */
    MIPC_NW_SET_5GUC_CNF                                    = MIPC_NW_REQ_BEGIN + 216,
    /* Get 5GUC current setting */
    MIPC_NW_GET_5GUC_SETTING_REQ                            = MIPC_NW_REQ_BEGIN + 217,
    /* 5GUC current setting */
    MIPC_NW_GET_5GUC_SETTING_CNF                            = MIPC_NW_REQ_BEGIN + 218,
    /* Get 5GUC info */
    MIPC_NW_GET_5GUC_INFO_REQ                               = MIPC_NW_REQ_BEGIN + 219,
    /* 5GUC current setting */
    MIPC_NW_GET_5GUC_INFO_CNF                               = MIPC_NW_REQ_BEGIN + 220,
    /* This command is used to get first plmn. */
    MIPC_NW_GET_FIRST_PLMN_REQ                              = MIPC_NW_REQ_BEGIN + 221,
    /* The result to get first plmn */
    MIPC_NW_GET_FIRST_PLMN_CNF                              = MIPC_NW_REQ_BEGIN + 222,
    MIPC_NW_REQ_END                                         = MIPC_NW_REQ_BEGIN + 0xFF,

    MIPC_SIM_REQ_BEGIN                                      = MIPC_REQ_BEGIN + 0x500,
    /* enable/disable PIN */
    MIPC_SIM_PIN_PROTECT_REQ                                = MIPC_SIM_REQ_BEGIN + 1,
    /* the result for PIN_PROTECT_REQ */
    MIPC_SIM_PIN_PROTECT_CNF                                = MIPC_SIM_REQ_BEGIN + 2,
    /* change PIN */
    MIPC_SIM_CHANGE_PIN_REQ                                 = MIPC_SIM_REQ_BEGIN + 3,
    /* the result for CHANGE_PIN_REQ */
    MIPC_SIM_CHANGE_PIN_CNF                                 = MIPC_SIM_REQ_BEGIN + 4,
    /* verify PIN */
    MIPC_SIM_VERIFY_PIN_REQ                                 = MIPC_SIM_REQ_BEGIN + 5,
    /* the result for VERIFY_PIN_REQ */
    MIPC_SIM_VERIFY_PIN_CNF                                 = MIPC_SIM_REQ_BEGIN + 6,
    /* unblock PIN */
    MIPC_SIM_UNBLOCK_PIN_REQ                                = MIPC_SIM_REQ_BEGIN + 7,
    /* the result for UNBLOCK_PIN_REQ */
    MIPC_SIM_UNBLOCK_PIN_CNF                                = MIPC_SIM_REQ_BEGIN + 8,
    /* request to get the pin info statusof sim card */
    MIPC_SIM_GET_PIN_INFO_REQ                               = MIPC_SIM_REQ_BEGIN + 9,
    /* the result for GET_PIN_INFO_REQ */
    MIPC_SIM_GET_PIN_INFO_CNF                               = MIPC_SIM_REQ_BEGIN + 10,
    /* request to get all the pin that MD supported  */
    MIPC_SIM_GET_PIN_LIST_REQ                               = MIPC_SIM_REQ_BEGIN + 11,
    /* the result for GET_PIN_LIST_REQ */
    MIPC_SIM_GET_PIN_LIST_CNF                               = MIPC_SIM_REQ_BEGIN + 12,
    /* request to get sim STATE */
    MIPC_SIM_STATE_REQ                                      = MIPC_SIM_REQ_BEGIN + 13,
    /* the result for STATE_REQ */
    MIPC_SIM_STATE_CNF                                      = MIPC_SIM_REQ_BEGIN + 14,
    MIPC_SIM_STATUS_REQ                                     = MIPC_SIM_REQ_BEGIN + 15,
    /* the result for STATUS_REQ */
    MIPC_SIM_STATUS_CNF                                     = MIPC_SIM_REQ_BEGIN + 16,
    /* request to get the iccid of sim card */
    MIPC_SIM_ICCID_REQ                                      = MIPC_SIM_REQ_BEGIN + 17,
    /* the result for ICCID_REQ */
    MIPC_SIM_ICCID_CNF                                      = MIPC_SIM_REQ_BEGIN + 18,
    MIPC_SIM_IMSI_REQ                                       = MIPC_SIM_REQ_BEGIN + 19,
    /* the result for IMSI_REQ */
    MIPC_SIM_IMSI_CNF                                       = MIPC_SIM_REQ_BEGIN + 20,
    /* request the msisdn in sim card */
    MIPC_SIM_MSISDN_REQ                                     = MIPC_SIM_REQ_BEGIN + 21,
    /* the result for MSISDN_REQ */
    MIPC_SIM_MSISDN_CNF                                     = MIPC_SIM_REQ_BEGIN + 22,
    /* request to get the atr of sim card */
    MIPC_SIM_GET_ATR_INFO_REQ                               = MIPC_SIM_REQ_BEGIN + 23,
    /* the result for GET_ATR_INFO_REQ */
    MIPC_SIM_GET_ATR_INFO_CNF                               = MIPC_SIM_REQ_BEGIN + 24,
    /* open a logical channel */
    MIPC_SIM_OPEN_CHANNEL_REQ                               = MIPC_SIM_REQ_BEGIN + 25,
    /* the result for OPEN_CHANNEL_REQ */
    MIPC_SIM_OPEN_CHANNEL_CNF                               = MIPC_SIM_REQ_BEGIN + 26,
    /* close the logical channel */
    MIPC_SIM_CLOSE_CHANNEL_REQ                              = MIPC_SIM_REQ_BEGIN + 27,
    /* the result for CLOSE_CHANNEL_REQ */
    MIPC_SIM_CLOSE_CHANNEL_CNF                              = MIPC_SIM_REQ_BEGIN + 28,
    /* do restricted access */
    MIPC_SIM_CHANNEL_RESTRICTED_ACCESS_REQ                  = MIPC_SIM_REQ_BEGIN + 29,
    /* the result for CHANNEL_RESTRICTED_ACCESS_REQ */
    MIPC_SIM_CHANNEL_RESTRICTED_ACCESS_CNF                  = MIPC_SIM_REQ_BEGIN + 30,
    /* do generic access */
    MIPC_SIM_CHANNEL_GENERIC_ACCESS_REQ                     = MIPC_SIM_REQ_BEGIN + 31,
    /* the result for GENERIC_ACCESS_REQ */
    MIPC_SIM_CHANNEL_GENERIC_ACCESS_CNF                     = MIPC_SIM_REQ_BEGIN + 32,
    /* do long APDU access to sim card */
    MIPC_SIM_LONG_APDU_ACCESS_REQ                           = MIPC_SIM_REQ_BEGIN + 33,
    /* the result for LONG_APDU_ACCESS_REQ */
    MIPC_SIM_LONG_APDU_ACCESS_CNF                           = MIPC_SIM_REQ_BEGIN + 34,
    /* list app  */
    MIPC_SIM_APP_LIST_REQ                                   = MIPC_SIM_REQ_BEGIN + 35,
    /* the result for APP_LIST_REQ */
    MIPC_SIM_APP_LIST_CNF                                   = MIPC_SIM_REQ_BEGIN + 36,
    /* get file status */
    MIPC_SIM_FILE_STATUS_REQ                                = MIPC_SIM_REQ_BEGIN + 37,
    /* the result for FILE_STATUS_REQ */
    MIPC_SIM_FILE_STATUS_CNF                                = MIPC_SIM_REQ_BEGIN + 38,
    /* get sim passthrough mode's status or sim application/power's status */
    MIPC_SIM_GET_RESET_REQ                                  = MIPC_SIM_REQ_BEGIN + 39,
    /* mode 0 means query passthrough mode's status, mode 1 means query sim application/power's status */
    MIPC_SIM_GET_RESET_CNF                                  = MIPC_SIM_REQ_BEGIN + 40,
    /* reset SIM */
    MIPC_SIM_SET_RESET_REQ                                  = MIPC_SIM_REQ_BEGIN + 41,
    /* the result for SET_RESET_REQ */
    MIPC_SIM_SET_RESET_CNF                                  = MIPC_SIM_REQ_BEGIN + 42,
    /* get saved terminal capability */
    MIPC_SIM_GET_TERMINAL_CAPABILITY_REQ                    = MIPC_SIM_REQ_BEGIN + 43,
    /* the result for GET_TERMINAL_CAPABILITY_REQ */
    MIPC_SIM_GET_TERMINAL_CAPABILITY_CNF                    = MIPC_SIM_REQ_BEGIN + 44,
    /* set terminial capability */
    MIPC_SIM_SET_TERMINAL_CAPABILITY_REQ                    = MIPC_SIM_REQ_BEGIN + 45,
    /* the result for SET_TERMINAL_CAPABILITY_REQ */
    MIPC_SIM_SET_TERMINAL_CAPABILITY_CNF                    = MIPC_SIM_REQ_BEGIN + 46,
    /* verify PIN by application */
    MIPC_SIM_SET_PIN_EX_REQ                                 = MIPC_SIM_REQ_BEGIN + 47,
    /* the result for SET_PIN_EX_REQ */
    MIPC_SIM_SET_PIN_EX_CNF                                 = MIPC_SIM_REQ_BEGIN + 48,
    /* get PIN information by application */
    MIPC_SIM_GET_PIN_EX_REQ                                 = MIPC_SIM_REQ_BEGIN + 49,
    /* the result for GET_PIN_EX_REQ */
    MIPC_SIM_GET_PIN_EX_CNF                                 = MIPC_SIM_REQ_BEGIN + 50,
    /* get response of run gsm authentication */
    MIPC_SIM_GET_GSM_AUTH_REQ                               = MIPC_SIM_REQ_BEGIN + 51,
    /* the response of run gsm authentication */
    MIPC_SIM_GET_GSM_AUTH_CNF                               = MIPC_SIM_REQ_BEGIN + 52,
    /* get response of run extention authentication */
    MIPC_SIM_GET_EXT_AUTH_REQ                               = MIPC_SIM_REQ_BEGIN + 53,
    /* response of run extention authentication */
    MIPC_SIM_GET_EXT_AUTH_CNF                               = MIPC_SIM_REQ_BEGIN + 54,
    /* query sim facility */
    MIPC_SIM_GET_FACILITY_REQ                               = MIPC_SIM_REQ_BEGIN + 55,
    /* result of get sim facility status */
    MIPC_SIM_GET_FACILITY_CNF                               = MIPC_SIM_REQ_BEGIN + 56,
    /*  */
    MIPC_SIM_SET_FACILITY_REQ                               = MIPC_SIM_REQ_BEGIN + 57,
    /*  */
    MIPC_SIM_SET_FACILITY_CNF                               = MIPC_SIM_REQ_BEGIN + 58,
    /* get euicc slots status */
    MIPC_SIM_GET_EUICC_SLOTS_STATUS_REQ                     = MIPC_SIM_REQ_BEGIN + 59,
    /* the result of get euicc slots status */
    MIPC_SIM_GET_EUICC_SLOTS_STATUS_CNF                     = MIPC_SIM_REQ_BEGIN + 60,
    /* this command is used to SAP connect request */
    MIPC_SIM_ACCESS_PROFILE_CONNECT_REQ                     = MIPC_SIM_REQ_BEGIN + 61,
    /* the result of SAP connect request */
    MIPC_SIM_ACCESS_PROFILE_CONNECT_CNF                     = MIPC_SIM_REQ_BEGIN + 62,
    /* this command is used to SAP disconnect request */
    MIPC_SIM_ACCESS_PROFILE_DISCONNECT_REQ                  = MIPC_SIM_REQ_BEGIN + 63,
    /* the result of SAP disconnect request */
    MIPC_SIM_ACCESS_PROFILE_DISCONNECT_CNF                  = MIPC_SIM_REQ_BEGIN + 64,
    /* this command is used to SAP power on request */
    MIPC_SIM_ACCESS_PROFILE_POWER_ON_REQ                    = MIPC_SIM_REQ_BEGIN + 65,
    /* result of SAP power on request */
    MIPC_SIM_ACCESS_PROFILE_POWER_ON_CNF                    = MIPC_SIM_REQ_BEGIN + 66,
    /* this command is used to SAP power off request */
    MIPC_SIM_ACCESS_PROFILE_POWER_OFF_REQ                   = MIPC_SIM_REQ_BEGIN + 67,
    /* result of SAP power off request */
    MIPC_SIM_ACCESS_PROFILE_POWER_OFF_CNF                   = MIPC_SIM_REQ_BEGIN + 68,
    /* this command is used to SAP reset sim request */
    MIPC_SIM_ACCESS_PROFILE_RESET_REQ                       = MIPC_SIM_REQ_BEGIN + 69,
    /* result of SAP reset sim request */
    MIPC_SIM_ACCESS_PROFILE_RESET_CNF                       = MIPC_SIM_REQ_BEGIN + 70,
    /* this command is used to SAP APDU request */
    MIPC_SIM_ACCESS_PROFILE_APDU_REQ                        = MIPC_SIM_REQ_BEGIN + 71,
    /* result of SAP APDU request */
    MIPC_SIM_ACCESS_PROFILE_APDU_CNF                        = MIPC_SIM_REQ_BEGIN + 72,
    /* request to set sim power */
    MIPC_SIM_SET_SIM_POWER_REQ                              = MIPC_SIM_REQ_BEGIN + 73,
    /* result of set sim power request */
    MIPC_SIM_SET_SIM_POWER_CNF                              = MIPC_SIM_REQ_BEGIN + 74,
    /* request to set sim slots mapping */
    MIPC_SIM_SET_PHYSICAL_SLOTS_MAPPING_REQ                 = MIPC_SIM_REQ_BEGIN + 75,
    /* result of set sim slots mapping */
    MIPC_SIM_SET_PHYSICAL_SLOTS_MAPPING_CNF                 = MIPC_SIM_REQ_BEGIN + 76,
    /* do extended generic access */
    MIPC_SIM_EXTENDED_CHANNEL_GENERIC_ACCESS_REQ            = MIPC_SIM_REQ_BEGIN + 77,
    /* the result for EXTENDED_CHANNEL_GENERIC_ACCESS_REQ */
    MIPC_SIM_EXTENDED_CHANNEL_GENERIC_ACCESS_CNF            = MIPC_SIM_REQ_BEGIN + 78,
    /* do sim uicc file access_ record */
    MIPC_SIM_UICC_FILE_ACCESS_RECORD_REQ                    = MIPC_SIM_REQ_BEGIN + 79,
    /* the result for UICC_FILE_ACCESS_RECORD_REQ */
    MIPC_SIM_UICC_FILE_ACCESS_RECORD_CNF                    = MIPC_SIM_REQ_BEGIN + 80,
    /* do sim uicc file access binary */
    MIPC_SIM_UICC_FILE_ACCESS_BINARY_REQ                    = MIPC_SIM_REQ_BEGIN + 81,
    /* the result for UICC_FILE_ACCESS_BINARY_REQ */
    MIPC_SIM_UICC_FILE_ACCESS_BINARY_CNF                    = MIPC_SIM_REQ_BEGIN + 82,
    /* request to get sim slots mapping */
    MIPC_SIM_GET_PHYSICAL_SLOTS_MAPPING_REQ                 = MIPC_SIM_REQ_BEGIN + 83,
    /* result of get sim slots mapping */
    MIPC_SIM_GET_PHYSICAL_SLOTS_MAPPING_CNF                 = MIPC_SIM_REQ_BEGIN + 84,
    /* get response of run extention authentication */
    MIPC_SIM_GET_SIM_AUTH_REQ                               = MIPC_SIM_REQ_BEGIN + 85,
    /* response of run extention authentication */
    MIPC_SIM_GET_SIM_AUTH_CNF                               = MIPC_SIM_REQ_BEGIN + 86,
    /* request to get google carriers lock info */
    MIPC_SIM_SML_GET_ALLOWED_CARRIERS_REQ                   = MIPC_SIM_REQ_BEGIN + 87,
    /* result of google carriers lock info */
    MIPC_SIM_SML_GET_ALLOWED_CARRIERS_CNF                   = MIPC_SIM_REQ_BEGIN + 88,
    /* request to set google carriers lock */
    MIPC_SIM_SML_SET_ALLOWED_CARRIERS_REQ                   = MIPC_SIM_REQ_BEGIN + 89,
    /* result of set allowed carriers, allowed_count(excluded_count) means num of set allowed(excluded) carriers success */
    MIPC_SIM_SML_SET_ALLOWED_CARRIERS_CNF                   = MIPC_SIM_REQ_BEGIN + 90,
    /* depersonalization specific sml lock */
    MIPC_SIM_SML_ENTER_SIM_DEPERSONALIZATION_REQ            = MIPC_SIM_REQ_BEGIN + 91,
    /* result of depersonalization */
    MIPC_SIM_SML_ENTER_SIM_DEPERSONALIZATION_CNF            = MIPC_SIM_REQ_BEGIN + 92,
    /* query sml lock info */
    MIPC_SIM_SML_GET_LOCK_REQ                               = MIPC_SIM_REQ_BEGIN + 93,
    /* specific category sml lock info */
    MIPC_SIM_SML_GET_LOCK_CNF                               = MIPC_SIM_REQ_BEGIN + 94,
    /* operation sim me lock */
    MIPC_SIM_SML_SET_LOCK_REQ                               = MIPC_SIM_REQ_BEGIN + 95,
    /* result of set sml lock */
    MIPC_SIM_SML_SET_LOCK_CNF                               = MIPC_SIM_REQ_BEGIN + 96,
    /* update device lock state */
    MIPC_SIM_SML_ENTER_DEVICE_DEPERSONALIZATION_REQ         = MIPC_SIM_REQ_BEGIN + 97,
    MIPC_SIM_SML_ENTER_DEVICE_DEPERSONALIZATION_CNF         = MIPC_SIM_REQ_BEGIN + 98,
    /* query device lock state */
    MIPC_SIM_SML_GET_DEV_LOCK_REQ                           = MIPC_SIM_REQ_BEGIN + 99,
    /* device lock state */
    MIPC_SIM_SML_GET_DEV_LOCK_CNF                           = MIPC_SIM_REQ_BEGIN + 100,
    /* remote sim unlock for different operator */
    MIPC_SIM_SML_RSU_REQ                                    = MIPC_SIM_REQ_BEGIN + 101,
    /* result of RSU */
    MIPC_SIM_SML_RSU_CNF                                    = MIPC_SIM_REQ_BEGIN + 102,
    /* request to set aka sim */
    MIPC_SIM_VSIM_SET_AKA_REQ                               = MIPC_SIM_REQ_BEGIN + 103,
    /* result of set aka sim */
    MIPC_SIM_VSIM_SET_AKA_CNF                               = MIPC_SIM_REQ_BEGIN + 104,
    /* request to enable Vsim */
    MIPC_SIM_VSIM_ENABLE_REQ                                = MIPC_SIM_REQ_BEGIN + 105,
    /* result of enable Vsim */
    MIPC_SIM_VSIM_ENABLE_CNF                                = MIPC_SIM_REQ_BEGIN + 106,
    /* request to disable Vsim */
    MIPC_SIM_VSIM_DISABLE_REQ                               = MIPC_SIM_REQ_BEGIN + 107,
    /* result of disable Vsim */
    MIPC_SIM_VSIM_DISABLE_CNF                               = MIPC_SIM_REQ_BEGIN + 108,
    /* request to plug in/out vsim */
    MIPC_SIM_VSIM_PLUG_REQ                                  = MIPC_SIM_REQ_BEGIN + 109,
    /* result of plug in/out vsim */
    MIPC_SIM_VSIM_PLUG_CNF                                  = MIPC_SIM_REQ_BEGIN + 110,
    /* request to set vsim timer */
    MIPC_SIM_VSIM_SET_TIMER_REQ                             = MIPC_SIM_REQ_BEGIN + 111,
    /* result of set vsim timer */
    MIPC_SIM_VSIM_SET_TIMER_CNF                             = MIPC_SIM_REQ_BEGIN + 112,
    /* request to reset vsim  */
    MIPC_SIM_VSIM_RESET_REQ                                 = MIPC_SIM_REQ_BEGIN + 113,
    /* result of reset vsim */
    MIPC_SIM_VSIM_RESET_CNF                                 = MIPC_SIM_REQ_BEGIN + 114,
    /* request to send APDU  */
    MIPC_SIM_VSIM_APDU_REQ                                  = MIPC_SIM_REQ_BEGIN + 115,
    /* result of send APDU */
    MIPC_SIM_VSIM_APDU_CNF                                  = MIPC_SIM_REQ_BEGIN + 116,
    /* request to auth */
    MIPC_SIM_VSIM_AUTH_REQ                                  = MIPC_SIM_REQ_BEGIN + 117,
    /* result of auth */
    MIPC_SIM_VSIM_AUTH_CNF                                  = MIPC_SIM_REQ_BEGIN + 118,
    /* request CDMA subscription */
    MIPC_SIM_CDMA_SUBSCRIPTION_REQ                          = MIPC_SIM_REQ_BEGIN + 119,
    /* result of CDMA subscription */
    MIPC_SIM_CDMA_SUBSCRIPTION_CNF                          = MIPC_SIM_REQ_BEGIN + 120,
    /* request CDMA subscription source */
    MIPC_SIM_CDMA_GET_SUBSCRIPTION_SOURCE_REQ               = MIPC_SIM_REQ_BEGIN + 121,
    /* result of CDMA subscription source */
    MIPC_SIM_CDMA_GET_SUBSCRIPTION_SOURCE_CNF               = MIPC_SIM_REQ_BEGIN + 122,
    /* request query pin count */
    MIPC_SIM_PIN_COUNT_QUERY_REQ                            = MIPC_SIM_REQ_BEGIN + 123,
    /* result of query pin count */
    MIPC_SIM_PIN_COUNT_QUERY_CNF                            = MIPC_SIM_REQ_BEGIN + 124,
    MIPC_SIM_SML_GET_NETWORK_LOCK_REQ                       = MIPC_SIM_REQ_BEGIN + 125,
    /* result of network lock info */
    MIPC_SIM_SML_GET_NETWORK_LOCK_CNF                       = MIPC_SIM_REQ_BEGIN + 126,
    MIPC_SIM_REQ_END                                        = MIPC_SIM_REQ_BEGIN + 0xFF,

    MIPC_SMS_REQ_BEGIN                                      = MIPC_REQ_BEGIN + 0x600,
    /* set or get SMS configuration */
    MIPC_SMS_CFG_REQ                                        = MIPC_SMS_REQ_BEGIN + 1,
    /* the result for CFG_REQ */
    MIPC_SMS_CFG_CNF                                        = MIPC_SMS_REQ_BEGIN + 2,
    /* send SMS */
    MIPC_SMS_SEND_REQ                                       = MIPC_SMS_REQ_BEGIN + 5,
    /* the result for SEND_REQ */
    MIPC_SMS_SEND_CNF                                       = MIPC_SMS_REQ_BEGIN + 6,
    /* read SMS */
    MIPC_SMS_READ_REQ                                       = MIPC_SMS_REQ_BEGIN + 7,
    /* the result for READ_REQ */
    MIPC_SMS_READ_CNF                                       = MIPC_SMS_REQ_BEGIN + 8,
    /* delete SMS */
    MIPC_SMS_DELETE_REQ                                     = MIPC_SMS_REQ_BEGIN + 9,
    /* the result for DELETE_REQ */
    MIPC_SMS_DELETE_CNF                                     = MIPC_SMS_REQ_BEGIN + 10,
    /* get SMS storage status */
    MIPC_SMS_GET_STORE_STATUS_REQ                           = MIPC_SMS_REQ_BEGIN + 11,
    /* the result for GET_STORE_STATUS_REQ */
    MIPC_SMS_GET_STORE_STATUS_CNF                           = MIPC_SMS_REQ_BEGIN + 12,
    /* write SMS to device(storage is the W_R_D_STORAGE in CFG_REQ) */
    MIPC_SMS_WRITE_REQ                                      = MIPC_SMS_REQ_BEGIN + 13,
    /* the result for WRITE_REQ */
    MIPC_SMS_WRITE_CNF                                      = MIPC_SMS_REQ_BEGIN + 14,
    /* the configuration of cbm, cfg_type must exist when corresponding option carried, default is all allow, msg_id&dcs&type all match open list(etws primary just match OPEN_CBM_TYPE&ETWS_PRIMARY_CFG),then the cbm would indicate USER */
    MIPC_SMS_CBM_CFG_REQ                                    = MIPC_SMS_REQ_BEGIN + 15,
    /* the result for CBM_CFG_REQ, if the CFG_TYPE is query, would carry the detail info */
    MIPC_SMS_CBM_CFG_CNF                                    = MIPC_SMS_REQ_BEGIN + 16,
    /* the req of SCBM related feature */
    MIPC_SMS_SCBM_REQ                                       = MIPC_SMS_REQ_BEGIN + 17,
    /* the result for SCBM_REQ */
    MIPC_SMS_SCBM_CNF                                       = MIPC_SMS_REQ_BEGIN + 18,
    MIPC_SMS_REQ_END                                        = MIPC_SMS_REQ_BEGIN + 0xFF,

    MIPC_SS_REQ_BEGIN                                       = MIPC_REQ_BEGIN + 0x700,
    /* the request command of send USSD */
    MIPC_SS_SEND_USSD_REQ                                   = MIPC_SS_REQ_BEGIN + 1,
    /* the result for MICP_SS_SEND_USSD_REQ */
    MIPC_SS_SEND_USSD_CNF                                   = MIPC_SS_REQ_BEGIN + 2,
    /* the request command of cancel USSD */
    MIPC_SS_CANCEL_USSD_REQ                                 = MIPC_SS_REQ_BEGIN + 3,
    /* the result for MICP_SS_CANCEL_USSD_REQ */
    MIPC_SS_CANCEL_USSD_CNF                                 = MIPC_SS_REQ_BEGIN + 4,
    /* the request command to set CLIR */
    MIPC_SS_SET_CLIR_REQ                                    = MIPC_SS_REQ_BEGIN + 5,
    /* the response of SET CLIR */
    MIPC_SS_SET_CLIR_CNF                                    = MIPC_SS_REQ_BEGIN + 6,
    /* the request command to get CLIR */
    MIPC_SS_GET_CLIR_REQ                                    = MIPC_SS_REQ_BEGIN + 7,
    /* the response of get CLIR */
    MIPC_SS_GET_CLIR_CNF                                    = MIPC_SS_REQ_BEGIN + 8,
    /* the request command to set call waiting */
    MIPC_SS_SET_CALL_WAITING_REQ                            = MIPC_SS_REQ_BEGIN + 9,
    /* the response of set call waiting */
    MIPC_SS_SET_CALL_WAITING_CNF                            = MIPC_SS_REQ_BEGIN + 10,
    /* the request to query call waiting */
    MIPC_SS_QUERY_CALL_WAITING_REQ                          = MIPC_SS_REQ_BEGIN + 11,
    /* response of query call waiting */
    MIPC_SS_QUERY_CALL_WAITING_CNF                          = MIPC_SS_REQ_BEGIN + 12,
    /* the request command to set call forward */
    MIPC_SS_SET_CALL_FORWARD_REQ                            = MIPC_SS_REQ_BEGIN + 13,
    /* response of set call forward */
    MIPC_SS_SET_CALL_FORWARD_CNF                            = MIPC_SS_REQ_BEGIN + 14,
    /* the request command to query call forward */
    MIPC_SS_QUERY_CALL_FORWARD_REQ                          = MIPC_SS_REQ_BEGIN + 15,
    /* the response of query call forward */
    MIPC_SS_QUERY_CALL_FORWARD_CNF                          = MIPC_SS_REQ_BEGIN + 16,
    /* the request command to lock/unlock for call barring */
    MIPC_SS_SET_CALL_BARRING_REQ                            = MIPC_SS_REQ_BEGIN + 17,
    /* the response to lock/unlock call barring */
    MIPC_SS_SET_CALL_BARRING_CNF                            = MIPC_SS_REQ_BEGIN + 18,
    /* the request command to query call barring */
    MIPC_SS_QUERY_CALL_BARRING_REQ                          = MIPC_SS_REQ_BEGIN + 19,
    /* the response to query call barring */
    MIPC_SS_QUERY_CALL_BARRING_CNF                          = MIPC_SS_REQ_BEGIN + 20,
    /* sets a new password for the facility lock function definded by Facility Lock +CLCK */
    MIPC_SS_CHANGE_BARRING_PASSWORD_REQ                     = MIPC_SS_REQ_BEGIN + 21,
    /* response of CHANGE_BARRING_PASSWORD_REQ */
    MIPC_SS_CHANGE_BARRING_PASSWORD_CNF                     = MIPC_SS_REQ_BEGIN + 22,
    /* enables/disables the presentation of notification result codes from TA to TE */
    MIPC_SS_SET_SUPP_SVC_NOTIFICATION_REQ                   = MIPC_SS_REQ_BEGIN + 23,
    /* response of SET_SUPP_SVC_NOTIFICATION_REQ */
    MIPC_SS_SET_SUPP_SVC_NOTIFICATION_CNF                   = MIPC_SS_REQ_BEGIN + 24,
    /* query calling line identification presentation */
    MIPC_SS_QUERY_CLIP_REQ                                  = MIPC_SS_REQ_BEGIN + 25,
    /* response of QUERY_CLIP_REQ */
    MIPC_SS_QUERY_CLIP_CNF                                  = MIPC_SS_REQ_BEGIN + 26,
    /* set calling line identification at the TE enabled or disabled  */
    MIPC_SS_SET_CLIP_REQ                                    = MIPC_SS_REQ_BEGIN + 27,
    /* response of SET_CLIP_REQ */
    MIPC_SS_SET_CLIP_CNF                                    = MIPC_SS_REQ_BEGIN + 28,
    /* run Gba Authentication */
    MIPC_SS_RUN_GBA_REQ                                     = MIPC_SS_REQ_BEGIN + 29,
    /* response of RUN_GBA_REQ */
    MIPC_SS_RUN_GBA_CNF                                     = MIPC_SS_REQ_BEGIN + 30,
    /* the request command to get COLP */
    MIPC_SS_GET_COLP_REQ                                    = MIPC_SS_REQ_BEGIN + 31,
    /* the response of get COLP */
    MIPC_SS_GET_COLP_CNF                                    = MIPC_SS_REQ_BEGIN + 32,
    /* the request command to set COLP */
    MIPC_SS_SET_COLP_REQ                                    = MIPC_SS_REQ_BEGIN + 33,
    /* the response of set COLP */
    MIPC_SS_SET_COLP_CNF                                    = MIPC_SS_REQ_BEGIN + 34,
    /* the request command to get COLR */
    MIPC_SS_GET_COLR_REQ                                    = MIPC_SS_REQ_BEGIN + 35,
    /* the response of get COLR */
    MIPC_SS_GET_COLR_CNF                                    = MIPC_SS_REQ_BEGIN + 36,
    /* the request command to send Call Name identification Presentation */
    MIPC_SS_SEND_CNAP_REQ                                   = MIPC_SS_REQ_BEGIN + 37,
    /* the response of send CNAP */
    MIPC_SS_SEND_CNAP_CNF                                   = MIPC_SS_REQ_BEGIN + 38,
    /* the request command to set COLR */
    MIPC_SS_SET_COLR_REQ                                    = MIPC_SS_REQ_BEGIN + 39,
    /* the response of set COLR */
    MIPC_SS_SET_COLR_CNF                                    = MIPC_SS_REQ_BEGIN + 40,
    /* the request command to setup XCAP USER AGENT */
    MIPC_SS_SETUP_XCAP_USER_AGENT_REQ                       = MIPC_SS_REQ_BEGIN + 41,
    /* the response of setup XCAP USER AGENT */
    MIPC_SS_SETUP_XCAP_USER_AGENT_CNF                       = MIPC_SS_REQ_BEGIN + 42,
    /* the request command to set XCAP CONFIG */
    MIPC_SS_SET_XCAP_CFG_REQ                                = MIPC_SS_REQ_BEGIN + 43,
    /* the response of set XCAP CONFIG */
    MIPC_SS_SET_XCAP_CFG_CNF                                = MIPC_SS_REQ_BEGIN + 44,
    MIPC_SS_REQ_END                                         = MIPC_SS_REQ_BEGIN + 0xFF,

    MIPC_STK_REQ_BEGIN                                      = MIPC_REQ_BEGIN + 0x800,
    /* the request command to set PAC info */
    MIPC_STK_SET_PAC_REQ                                    = MIPC_STK_REQ_BEGIN + 1,
    /* the response of set PAC */
    MIPC_STK_SET_PAC_CNF                                    = MIPC_STK_REQ_BEGIN + 2,
    /* get proactive command handle info which indicate proactive command will be handled by ME or TE */
    MIPC_STK_GET_PAC_REQ                                    = MIPC_STK_REQ_BEGIN + 3,
    /* the response of GET_PAC_REQ */
    MIPC_STK_GET_PAC_CNF                                    = MIPC_STK_REQ_BEGIN + 4,
    /* send terminal response to UICC */
    MIPC_STK_SEND_TERMINAL_RESPONSE_REQ                     = MIPC_STK_REQ_BEGIN + 5,
    /* the result of sSEND_TERMINAL_RESPONSE_REQ */
    MIPC_STK_SEND_TERMINAL_RESPONSE_CNF                     = MIPC_STK_REQ_BEGIN + 6,
    /* send envelope to UICC */
    MIPC_STK_SEND_ENVELOPE_REQ                              = MIPC_STK_REQ_BEGIN + 7,
    /* the result of SEND_ENVELOPE_REQ */
    MIPC_STK_SEND_ENVELOPE_CNF                              = MIPC_STK_REQ_BEGIN + 8,
    /* the request command to get envelope info */
    MIPC_STK_GET_ENVELOPE_INFO_REQ                          = MIPC_STK_REQ_BEGIN + 9,
    /* the result of GET_ENVELOPE_INFO_REQ */
    MIPC_STK_GET_ENVELOPE_INFO_CNF                          = MIPC_STK_REQ_BEGIN + 10,
    /* set the result of AP confirm for BIP open channel commond which includes non-null alpha ID */
    MIPC_STK_HANDLE_CALL_SETUP_FROM_SIM_REQ                 = MIPC_STK_REQ_BEGIN + 11,
    /* response of HANDLE_CALL_SETUP_FROM_SIM_REQ */
    MIPC_STK_HANDLE_CALL_SETUP_FROM_SIM_CNF                 = MIPC_STK_REQ_BEGIN + 12,
    /* set result of AP confirm for BIP open channel command */
    MIPC_STK_SEND_BIPCONF_REQ                               = MIPC_STK_REQ_BEGIN + 13,
    /* the result of SEND_BIPCONF_CNF */
    MIPC_STK_SEND_BIPCONF_CNF                               = MIPC_STK_REQ_BEGIN + 14,
    MIPC_STK_REQ_END                                        = MIPC_STK_REQ_BEGIN + 0xFF,

    MIPC_CALL_REQ_BEGIN                                     = MIPC_REQ_BEGIN + 0x900,
    /* this command is used to dial a call */
    MIPC_CALL_DIAL_REQ                                      = MIPC_CALL_REQ_BEGIN + 1,
    /* the result for CALL_DIAL_REQ */
    MIPC_CALL_DIAL_CNF                                      = MIPC_CALL_REQ_BEGIN + 2,
    /* requests call-related supplementary services */
    MIPC_CALL_SS_REQ                                        = MIPC_CALL_REQ_BEGIN + 3,
    /* the result for CALL_SS_REQ. For assured and consulative ECT type final success or fail status of the transfer is indicated as MIPC_CALL_ECT_IND */
    MIPC_CALL_SS_CNF                                        = MIPC_CALL_REQ_BEGIN + 4,
    /* this command is used to release call */
    MIPC_CALL_HANGUP_REQ                                    = MIPC_CALL_REQ_BEGIN + 5,
    /* the result for CALL_HANGUP_REQ */
    MIPC_CALL_HANGUP_CNF                                    = MIPC_CALL_REQ_BEGIN + 6,
    /* answers and initiates a connection to an incoming call */
    MIPC_CALL_ANSWER_REQ                                    = MIPC_CALL_REQ_BEGIN + 7,
    /* the result for CALL_ANSWER_REQ */
    MIPC_CALL_ANSWER_CNF                                    = MIPC_CALL_REQ_BEGIN + 8,
    /* get the call status */
    MIPC_CALL_GET_CALL_STATUS_REQ                           = MIPC_CALL_REQ_BEGIN + 9,
    /* the result for CALL_GET_CALL_STATUS_CNF */
    MIPC_CALL_GET_CALL_STATUS_CNF                           = MIPC_CALL_REQ_BEGIN + 10,
    /* conference call operation */
    MIPC_CALL_CONFERENCE_REQ                                = MIPC_CALL_REQ_BEGIN + 11,
    /* the result for CALL_CONFERENCE_REQ */
    MIPC_CALL_CONFERENCE_CNF                                = MIPC_CALL_REQ_BEGIN + 12,
    /* get the ims conference call information, get cs conference infomation please use GET_CALL_STATUS_REQ */
    MIPC_CALL_GET_CONFERENCE_INFO_REQ                       = MIPC_CALL_REQ_BEGIN + 13,
    /* the result for CALL_GET_CONFERENCE_CALL_INFO_REQ */
    MIPC_CALL_GET_CONFERENCE_INFO_CNF                       = MIPC_CALL_REQ_BEGIN + 14,
    /* get the reason for : (1) the failure in the last unsuccessful call setup or in-call modification  (2) the last call release */
    MIPC_CALL_GET_FINISH_REASON_REQ                         = MIPC_CALL_REQ_BEGIN + 15,
    /* the result for CALL_GET_FINISH_REASON_REQ */
    MIPC_CALL_GET_FINISH_REASON_CNF                         = MIPC_CALL_REQ_BEGIN + 16,
    /* this command is intended to be send START_DTMF and STOP_DTMF message to NW separately */
    MIPC_CALL_DTMF_REQ                                      = MIPC_CALL_REQ_BEGIN + 17,
    /* the result for CALL_DTMF_REQ */
    MIPC_CALL_DTMF_CNF                                      = MIPC_CALL_REQ_BEGIN + 18,
    /* get the ECC list */
    MIPC_CALL_GET_ECC_LIST_REQ                              = MIPC_CALL_REQ_BEGIN + 19,
    /* the result for CALL_GET_ECC_LIST_REQ */
    MIPC_CALL_GET_ECC_LIST_CNF                              = MIPC_CALL_REQ_BEGIN + 20,
    /* set the ECC list to modem */
    MIPC_CALL_SET_ECC_LIST_REQ                              = MIPC_CALL_REQ_BEGIN + 21,
    /* the result for CALL_SET_ECC_LIST_REQ */
    MIPC_CALL_SET_ECC_LIST_CNF                              = MIPC_CALL_REQ_BEGIN + 22,
    /* set the flight mode ecc session */
    MIPC_CALL_SET_FLIGHT_MODE_ECC_SESSION_REQ               = MIPC_CALL_REQ_BEGIN + 23,
    /* result of set the flight mode ecc session */
    MIPC_CALL_SET_FLIGHT_MODE_ECC_SESSION_CNF               = MIPC_CALL_REQ_BEGIN + 24,
    /* request to exit ecbm mode */
    MIPC_CALL_SET_EXIT_ECBM_MODE_REQ                        = MIPC_CALL_REQ_BEGIN + 25,
    /* result of exit ecbm mode */
    MIPC_CALL_SET_EXIT_ECBM_MODE_CNF                        = MIPC_CALL_REQ_BEGIN + 26,
    /* trigger an ecall */
    MIPC_CALL_IVS_ONEKEY_ECALL_REQ                          = MIPC_CALL_REQ_BEGIN + 27,
    /* the result for IVS_ONEKEY_ECALL_REQ */
    MIPC_CALL_IVS_ONEKEY_ECALL_CNF                          = MIPC_CALL_REQ_BEGIN + 28,
    /* add user-definded SIP headers */
    MIPC_CALL_SET_SIP_HEADER_REQ                            = MIPC_CALL_REQ_BEGIN + 29,
    /* result of set sip header req */
    MIPC_CALL_SET_SIP_HEADER_CNF                            = MIPC_CALL_REQ_BEGIN + 30,
    /* Query IMS SIP Header by Call Id and the result will be sent via MIPC_CALL_IMS_HEADER_IND */
    MIPC_CALL_ENABLE_IMS_SIP_HEADER_REPORT_REQ              = MIPC_CALL_REQ_BEGIN + 31,
    /* result of enable ims sip header report req */
    MIPC_CALL_ENABLE_IMS_SIP_HEADER_REPORT_CNF              = MIPC_CALL_REQ_BEGIN + 32,
    /* Set IMS call additional information */
    MIPC_CALL_SET_CALL_ADDITIONAL_INFO_REQ                  = MIPC_CALL_REQ_BEGIN + 33,
    /* result of set call additinal info req */
    MIPC_CALL_SET_CALL_ADDITIONAL_INFO_CNF                  = MIPC_CALL_REQ_BEGIN + 34,
    MIPC_CALL_PEER_RTT_MODIFY_REQ                           = MIPC_CALL_REQ_BEGIN + 35,
    /* result of peer rtt modify req */
    MIPC_CALL_PEER_RTT_MODIFY_CNF                           = MIPC_CALL_REQ_BEGIN + 36,
    MIPC_CALL_LOCAL_RTT_MODIFY_REQ                          = MIPC_CALL_REQ_BEGIN + 37,
    /* result of local rtt modify req */
    MIPC_CALL_LOCAL_RTT_MODIFY_CNF                          = MIPC_CALL_REQ_BEGIN + 38,
    MIPC_CALL_RTT_TEXT_REQ                                  = MIPC_CALL_REQ_BEGIN + 39,
    /* result of rtt text req */
    MIPC_CALL_RTT_TEXT_CNF                                  = MIPC_CALL_REQ_BEGIN + 40,
    MIPC_CALL_RTT_MODE_REQ                                  = MIPC_CALL_REQ_BEGIN + 41,
    /* result of rtt mode req */
    MIPC_CALL_RTT_MODE_CNF                                  = MIPC_CALL_REQ_BEGIN + 42,
    MIPC_CALL_RTT_AUDIO_REQ                                 = MIPC_CALL_REQ_BEGIN + 43,
    /* result of rtt audio req */
    MIPC_CALL_RTT_AUDIO_CNF                                 = MIPC_CALL_REQ_BEGIN + 44,
    MIPC_CALL_SET_RCS_STATE_AND_FEATURE_REQ                 = MIPC_CALL_REQ_BEGIN + 45,
    /* result of set RCS state and feature req */
    MIPC_CALL_SET_RCS_STATE_AND_FEATURE_CNF                 = MIPC_CALL_REQ_BEGIN + 46,
    MIPC_CALL_UPDATE_RCS_SESSION_INFO_REQ                   = MIPC_CALL_REQ_BEGIN + 47,
    /* result of update RCS session info req */
    MIPC_CALL_UPDATE_RCS_SESSION_INFO_CNF                   = MIPC_CALL_REQ_BEGIN + 48,
    /* get the voice domain preference of the UE. */
    MIPC_CALL_GET_VOICE_DOMAIN_PREFERENCE_REQ               = MIPC_CALL_REQ_BEGIN + 53,
    /* result of get voice domain preference req */
    MIPC_CALL_GET_VOICE_DOMAIN_PREFERENCE_CNF               = MIPC_CALL_REQ_BEGIN + 54,
    /* pull call */
    MIPC_CALL_PULL_REQ                                      = MIPC_CALL_REQ_BEGIN + 55,
    /* result of call pull req */
    MIPC_CALL_PULL_CNF                                      = MIPC_CALL_REQ_BEGIN + 56,
    MIPC_CALL_GET_TTY_MODE_REQ                              = MIPC_CALL_REQ_BEGIN + 57,
    /* result of call get TTY mode req */
    MIPC_CALL_GET_TTY_MODE_CNF                              = MIPC_CALL_REQ_BEGIN + 58,
    /* set IMS call mode to difficiate client API mode and original IMS mode */
    MIPC_CALL_SET_IMS_CALL_MODE_REQ                         = MIPC_CALL_REQ_BEGIN + 59,
    /* result of call set IMS call mode req */
    MIPC_CALL_SET_IMS_CALL_MODE_CNF                         = MIPC_CALL_REQ_BEGIN + 60,
    MIPC_CALL_SET_TTY_MODE_REQ                              = MIPC_CALL_REQ_BEGIN + 61,
    /* result of call set TTY mode req */
    MIPC_CALL_SET_TTY_MODE_CNF                              = MIPC_CALL_REQ_BEGIN + 62,
    /* set the MT to operate according to the specified voice domain preference for E-UTRAN */
    MIPC_CALL_SET_VOICE_DOMAIN_PREFERENCE_REQ               = MIPC_CALL_REQ_BEGIN + 63,
    /* result of set voice domain preference req */
    MIPC_CALL_SET_VOICE_DOMAIN_PREFERENCE_CNF               = MIPC_CALL_REQ_BEGIN + 64,
    /* this command is used to dial a conference call */
    MIPC_CALL_CONFERENCE_DIAL_REQ                           = MIPC_CALL_REQ_BEGIN + 65,
    /* the result for CONFERENCE_DIAL_REQ */
    MIPC_CALL_CONFERENCE_DIAL_CNF                           = MIPC_CALL_REQ_BEGIN + 66,
    /* this command is used to set GWSD mode */
    MIPC_CALL_SET_GWSD_MODE_REQ                             = MIPC_CALL_REQ_BEGIN + 67,
    /* the result for set_GWSD_MODE_REQ */
    MIPC_CALL_SET_GWSD_MODE_CNF                             = MIPC_CALL_REQ_BEGIN + 68,
    /* this command is used to set GWSD mode */
    MIPC_CALL_APPROVE_CSFB_REQ                              = MIPC_CALL_REQ_BEGIN + 69,
    /* the result for APPROVE_CSFB_REQ */
    MIPC_CALL_APPROVE_CSFB_CNF                              = MIPC_CALL_REQ_BEGIN + 70,
    /* this command is used to set GWSD call valid timer */
    MIPC_CALL_SET_GWSD_CALL_VALID_REQ                       = MIPC_CALL_REQ_BEGIN + 71,
    /* the result for SET_GWSD_CALL_VALID_REQ */
    MIPC_CALL_SET_GWSD_CALL_VALID_CNF                       = MIPC_CALL_REQ_BEGIN + 72,
    /* this command is used to set GWSD ignore call interval */
    MIPC_CALL_SET_GWSD_IGNORE_CALL_INTERVAL_REQ             = MIPC_CALL_REQ_BEGIN + 73,
    /* the result for SET_GWSD_IGNORE_CALL_INTERVAL_REQ */
    MIPC_CALL_SET_GWSD_IGNORE_CALL_INTERVAL_CNF             = MIPC_CALL_REQ_BEGIN + 74,
    /* this command is used to set GWSD keep alive PDCP */
    MIPC_CALL_SET_GWSD_KA_PDCP_REQ                          = MIPC_CALL_REQ_BEGIN + 75,
    /* the result for SET_GWSD_KA_PDCP_REQ */
    MIPC_CALL_SET_GWSD_KA_PDCP_CNF                          = MIPC_CALL_REQ_BEGIN + 76,
    /* this command is used to set GWSD keep alive IPDATA */
    MIPC_CALL_SET_GWSD_KA_IPDATA_REQ                        = MIPC_CALL_REQ_BEGIN + 77,
    /* the result for SET_GWSD_KA_IPDATA_REQ */
    MIPC_CALL_SET_GWSD_KA_IPDATA_CNF                        = MIPC_CALL_REQ_BEGIN + 78,
    /* This command is used to provide User Interactive Service information accompanying with a specific ongoing Call */
    MIPC_CALL_UIS_INFO_REQ                                  = MIPC_CALL_REQ_BEGIN + 83,
    /* get the result of UIS_INFO_REQ */
    MIPC_CALL_UIS_INFO_CNF                                  = MIPC_CALL_REQ_BEGIN + 84,
    /* This command is used to enable auto answer, default value is 1 */
    MIPC_CALL_AUTO_ANSWER_REQ                               = MIPC_CALL_REQ_BEGIN + 85,
    /* get the result of AUTO_ANSWER_REQ */
    MIPC_CALL_AUTO_ANSWER_CNF                               = MIPC_CALL_REQ_BEGIN + 86,
    /* This command is used to set call/data prefer setting */
    MIPC_CALL_DATA_PREFER_SET_REQ                           = MIPC_CALL_REQ_BEGIN + 87,
    /* get the result of DATA_PREFER_SET_REQ */
    MIPC_CALL_DATA_PREFER_SET_CNF                           = MIPC_CALL_REQ_BEGIN + 88,
    /* request to approve this call or not */
    MIPC_CALL_ECC_REDIAL_APPROVE_REQ                        = MIPC_CALL_REQ_BEGIN + 91,
    /* result of ecc redial approve command */
    MIPC_CALL_ECC_REDIAL_APPROVE_CNF                        = MIPC_CALL_REQ_BEGIN + 92,
    MIPC_CALL_REQ_END                                       = MIPC_CALL_REQ_BEGIN + 0xFF,

    MIPC_IMS_REQ_BEGIN                                      = MIPC_REQ_BEGIN + 0xA00,
    /* set ims config */
    MIPC_IMS_SET_CONFIG_REQ                                 = MIPC_IMS_REQ_BEGIN + 0,
    /* set modem configuration response */
    MIPC_IMS_SET_CONFIG_CNF                                 = MIPC_IMS_REQ_BEGIN + 1,
    /* get modem configuration request */
    MIPC_IMS_GET_CONFIG_REQ                                 = MIPC_IMS_REQ_BEGIN + 2,
    /* get modem configuration response */
    MIPC_IMS_GET_CONFIG_CNF                                 = MIPC_IMS_REQ_BEGIN + 3,
    /* get modem ims state request */
    MIPC_IMS_GET_STATE_REQ                                  = MIPC_IMS_REQ_BEGIN + 4,
    /* response of get modem ims state  */
    MIPC_IMS_GET_STATE_CNF                                  = MIPC_IMS_REQ_BEGIN + 5,
    /* to set imspdis */
    MIPC_IMS_SET_PDIS_REQ                                   = MIPC_IMS_REQ_BEGIN + 6,
    /* the response of set imspdis */
    MIPC_IMS_SET_PDIS_CNF                                   = MIPC_IMS_REQ_BEGIN + 7,
    /* to set NAPTR */
    MIPC_IMS_SET_NAPTR_REQ                                  = MIPC_IMS_REQ_BEGIN + 8,
    /* the response of set NAPTR */
    MIPC_IMS_SET_NAPTR_CNF                                  = MIPC_IMS_REQ_BEGIN + 9,
    /* to get network reporting status, e.g. CIREP */
    MIPC_IMS_GET_NW_RPT_REQ                                 = MIPC_IMS_REQ_BEGIN + 10,
    /* response of get network reporting status, e.g. CIREP */
    MIPC_IMS_GET_NW_RPT_CNF                                 = MIPC_IMS_REQ_BEGIN + 11,
    /* to set ims test mode */
    MIPC_IMS_SET_TEST_MODE_REQ                              = MIPC_IMS_REQ_BEGIN + 12,
    /* the response of set ims test mode */
    MIPC_IMS_SET_TEST_MODE_CNF                              = MIPC_IMS_REQ_BEGIN + 13,
    /* set ims registiation status request */
    MIPC_IMS_SET_EIREG_REQ                                  = MIPC_IMS_REQ_BEGIN + 14,
    /* set ims registiation status response */
    MIPC_IMS_SET_EIREG_CNF                                  = MIPC_IMS_REQ_BEGIN + 15,
    /* to set Smart Congestion Mitigation, only for specific modem branch */
    MIPC_IMS_SET_SCM_REQ                                    = MIPC_IMS_REQ_BEGIN + 16,
    /* response of set Smart Congestion Mitigation */
    MIPC_IMS_SET_SCM_CNF                                    = MIPC_IMS_REQ_BEGIN + 17,
    /* to set IMS service session status,only for specific modem branch */
    MIPC_IMS_SET_SERVICE_SESSION_REQ                        = MIPC_IMS_REQ_BEGIN + 18,
    /* response of IMS service session status */
    MIPC_IMS_SET_SERVICE_SESSION_CNF                        = MIPC_IMS_REQ_BEGIN + 19,
    /* to set IMS UAC status,only for specific modem branch */
    MIPC_IMS_SET_UAC_REQ                                    = MIPC_IMS_REQ_BEGIN + 20,
    /* response of SET IMS UAC */
    MIPC_IMS_SET_UAC_CNF                                    = MIPC_IMS_REQ_BEGIN + 21,
    MIPC_IMS_REQ_END                                        = MIPC_IMS_REQ_BEGIN + 0xFF,

    MIPC_WFC_REQ_BEGIN                                      = MIPC_REQ_BEGIN + 0xB00,
    /* register cell signal ind(CELL_SIGNAL_IND), diffirent SIGNAL_TYPE has different parameters */
    MIPC_WFC_REGISTER_CELL_SIGNAL_IND_REQ                   = MIPC_WFC_REQ_BEGIN + 0,
    /* result of REGISTER_CELL_SIGNAL_IND_REQ */
    MIPC_WFC_REGISTER_CELL_SIGNAL_IND_CNF                   = MIPC_WFC_REQ_BEGIN + 1,
    /* Service specific access control restriction status query */
    MIPC_WFC_CSSAC_REQ                                      = MIPC_WFC_REQ_BEGIN + 2,
    /* result of CSSAC_REQ */
    MIPC_WFC_CSSAC_CNF                                      = MIPC_WFC_REQ_BEGIN + 3,
    /* used for PEI (P-Emergency-Info) Header in all emergency call as part of SIP Invite; Support for IMS AT&T project. Refer to <CDR-WiFi-1310> PEI Header;This command is suggested to be sent before emergency call is made; This ai for WiFi calling. */
    MIPC_WFC_SET_EMC_AID_REQ                                = MIPC_WFC_REQ_BEGIN + 4,
    /* result of SET_EMC_AID_REQ */
    MIPC_WFC_SET_EMC_AID_CNF                                = MIPC_WFC_REQ_BEGIN + 5,
    /* cfg relate operation */
    MIPC_WFC_CFG_REQ                                        = MIPC_WFC_REQ_BEGIN + 6,
    /* result of CFG_REQ */
    MIPC_WFC_CFG_CNF                                        = MIPC_WFC_REQ_BEGIN + 7,
    MIPC_WFC_REQ_END                                        = MIPC_WFC_REQ_BEGIN + 0xFF,

    MIPC_PHB_REQ_BEGIN                                      = MIPC_REQ_BEGIN + 0xC00,
    /* edit or delete upb entry */
    MIPC_PHB_SET_UPB_ENTRY_REQ                              = MIPC_PHB_REQ_BEGIN + 0,
    /* set upb entry result */
    MIPC_PHB_SET_UPB_ENTRY_CNF                              = MIPC_PHB_REQ_BEGIN + 1,
    /* read upb entry */
    MIPC_PHB_GET_UPB_ANR_EMAIL_SNE_ENTRY_REQ                = MIPC_PHB_REQ_BEGIN + 2,
    /* read upb entry cnf */
    MIPC_PHB_GET_UPB_ANR_EMAIL_SNE_ENTRY_CNF                = MIPC_PHB_REQ_BEGIN + 3,
    /* read upb entry */
    MIPC_PHB_GET_UPB_AAS_GAS_GRP_LIST_ENTRY_REQ             = MIPC_PHB_REQ_BEGIN + 4,
    /* read upb entry cnf */
    MIPC_PHB_GET_UPB_AAS_GAS_GRP_LIST_ENTRY_CNF             = MIPC_PHB_REQ_BEGIN + 5,
    /* get phb memory storage info */
    MIPC_PHB_GET_PHB_STORAGE_INFO_REQ                       = MIPC_PHB_REQ_BEGIN + 6,
    /* get phb storage info cnf */
    MIPC_PHB_GET_PHB_STORAGE_INFO_CNF                       = MIPC_PHB_REQ_BEGIN + 7,
    /* get phb memory storage info */
    MIPC_PHB_SET_PHB_MEM_STORAGE_REQ                        = MIPC_PHB_REQ_BEGIN + 8,
    /* set phb memory storage cnf */
    MIPC_PHB_SET_PHB_MEM_STORAGE_CNF                        = MIPC_PHB_REQ_BEGIN + 9,
    /* get phb entry from bindex to eindex */
    MIPC_PHB_GET_PHB_ENTRY_REQ                              = MIPC_PHB_REQ_BEGIN + 10,
    /* the result for get phb entry req */
    MIPC_PHB_GET_PHB_ENTRY_CNF                              = MIPC_PHB_REQ_BEGIN + 11,
    /* set phb entry */
    MIPC_PHB_SET_PHB_ENTRY_REQ                              = MIPC_PHB_REQ_BEGIN + 12,
    /* get phb entry cnf */
    MIPC_PHB_SET_PHB_ENTRY_CNF                              = MIPC_PHB_REQ_BEGIN + 13,
    /* get phb string length req */
    MIPC_PHB_GET_PHB_STRINGSLENGTH_REQ                      = MIPC_PHB_REQ_BEGIN + 14,
    /* the result for phb string length req */
    MIPC_PHB_GET_PHB_STRINGSLENGTH_CNF                      = MIPC_PHB_REQ_BEGIN + 15,
    /* get upb capability req */
    MIPC_PHB_GET_UPB_CAPABILITY_REQ                         = MIPC_PHB_REQ_BEGIN + 16,
    /* the result upb capability req */
    MIPC_PHB_GET_UPB_CAPABILITY_CNF                         = MIPC_PHB_REQ_BEGIN + 17,
    /* get phb string length req */
    MIPC_PHB_GET_PHB_AVAILABLE_REQ                          = MIPC_PHB_REQ_BEGIN + 18,
    /* the result for phb string length req */
    MIPC_PHB_GET_PHB_AVAILABLE_CNF                          = MIPC_PHB_REQ_BEGIN + 19,
    MIPC_PHB_REQ_END                                        = MIPC_PHB_REQ_BEGIN + 0xFF,

    MIPC_EMBMS_REQ_BEGIN                                    = MIPC_REQ_BEGIN + 0xD00,
    /* get the latest information regarding the MBMS sessions available in the current MBSFN req. */
    MIPC_EMBMS_EMSLU_REQ                                    = MIPC_EMBMS_REQ_BEGIN + 0,
    /* the result for EMSLU_REQ */
    MIPC_EMBMS_EMSLU_CNF                                    = MIPC_EMBMS_REQ_BEGIN + 1,
    /* get the latest SAI list req. */
    MIPC_EMBMS_GET_SAI_LIST_REQ                             = MIPC_EMBMS_REQ_BEGIN + 2,
    /* the result for GET_SAI_LIST_REQ */
    MIPC_EMBMS_GET_SAI_LIST_CNF                             = MIPC_EMBMS_REQ_BEGIN + 3,
    /* Notify MBMSAL the beginning or the end of the hVoLTE scenarios req. */
    MIPC_EMBMS_NOTIFY_HVOLTE_STATUS_REQ                     = MIPC_EMBMS_REQ_BEGIN + 4,
    /* the result for NOTIFY_HVOLTE_STATUS_REQ */
    MIPC_EMBMS_NOTIFY_HVOLTE_STATUS_CNF                     = MIPC_EMBMS_REQ_BEGIN + 5,
    MIPC_EMBMS_REQ_END                                      = MIPC_EMBMS_REQ_BEGIN + 0xFF,


    MIPC_IND_BEGIN                                          = 0x4000,

    MIPC_SYS_IND_BEGIN                                      = MIPC_IND_BEGIN + 0,
    /* unsolicited AT command indication */
    MIPC_SYS_AT_IND                                         = MIPC_SYS_IND_BEGIN + 1,
    /* thermal alarm indication */
    MIPC_SYS_THERMAL_SENSOR_IND                             = MIPC_SYS_IND_BEGIN + 2,
    /* the configuartion change indication */
    MIPC_SYS_CONFIG_IND                                     = MIPC_SYS_IND_BEGIN + 3,
    /*  */
    MIPC_SYS_ADPCLK_IND                                     = MIPC_SYS_IND_BEGIN + 4,
    /*  */
    MIPC_SYS_MCF_IND                                        = MIPC_SYS_IND_BEGIN + 5,
    /*  */
    MIPC_SYS_SBP_IND                                        = MIPC_SYS_IND_BEGIN + 6,
    /* location info indicate */
    MIPC_SYS_GEO_LOCATION_IND                               = MIPC_SYS_IND_BEGIN + 17,
    /* modem initial indication */
    MIPC_SYS_MD_INIT_IND                                    = MIPC_SYS_IND_BEGIN + 18,
    /* modem EE waring indication */
    MIPC_SYS_WARNING_IND                                    = MIPC_SYS_IND_BEGIN + 19,
    /* nvram verified failed indication */
    MIPC_SYS_NV_SIG_ERR_IND                                 = MIPC_SYS_IND_BEGIN + 20,
    /* report the statistics info of VODATA */
    MIPC_SYS_VODATA_STATISTICS_IND                          = MIPC_SYS_IND_BEGIN + 21,
    /*  */
    MIPC_SYS_THERMAL_ACTUATOR_IND                           = MIPC_SYS_IND_BEGIN + 22,
    MIPC_SYS_IND_END                                        = MIPC_SYS_IND_BEGIN + 0xFF,

    MIPC_APN_IND_BEGIN                                      = MIPC_IND_BEGIN + 0x100,
    /* LTE initial attach profile changed indication */
    MIPC_APN_IA_CFG_IND                                     = MIPC_APN_IND_BEGIN + 1,
    /* APN profile changed indication */
    MIPC_APN_PROFILE_CFG_IND                                = MIPC_APN_IND_BEGIN + 2,
    /* VZW APN profile changed indication */
    MIPC_APN_VZW_CHG_IND                                    = MIPC_APN_IND_BEGIN + 3,
    MIPC_APN_IND_END                                        = MIPC_APN_IND_BEGIN + 0xFF,

    MIPC_DATA_IND_BEGIN                                     = MIPC_IND_BEGIN + 0x200,
    /* NW activate a data call indication, or fallback data call indication */
    MIPC_DATA_ACT_CALL_IND                                  = MIPC_DATA_IND_BEGIN + 1,
    /* NW de-activate a data call indication */
    MIPC_DATA_DEACT_CALL_IND                                = MIPC_DATA_IND_BEGIN + 2,
    /* NW modifiy a data call indication */
    MIPC_DATA_MOD_CALL_IND                                  = MIPC_DATA_IND_BEGIN + 3,
    /* NW modifiy PCO indication */
    MIPC_DATA_MOD_PCO_IND                                   = MIPC_DATA_IND_BEGIN + 4,
    /* host activate a data call indication */
    MIPC_DATA_WWAN_ACT_CALL_IND                             = MIPC_DATA_IND_BEGIN + 5,
    /* host de-activate a data call indication */
    MIPC_DATA_WWAN_DEACT_CALL_IND                           = MIPC_DATA_IND_BEGIN + 6,
    /* register call act ind */
    MIPC_DATA_CALL_ACT_REG_IND                              = MIPC_DATA_IND_BEGIN + 7,
    /* register decall act ind */
    MIPC_DATA_CALL_DEACT_REG_IND                            = MIPC_DATA_IND_BEGIN + 8,
    /* register mod call act ind */
    MIPC_DATA_CALL_MOD_REG_IND                              = MIPC_DATA_IND_BEGIN + 9,
    /* user in modem act a data call */
    MIPC_DATA_MD_ACT_CALL_IND                               = MIPC_DATA_IND_BEGIN + 10,
    /* user in modem deact a data call */
    MIPC_DATA_MD_DEACT_CALL_IND                             = MIPC_DATA_IND_BEGIN + 11,
    /* iwlan priority list indication */
    MIPC_DATA_IWLAN_PRIORITY_LIST_IND                       = MIPC_DATA_IND_BEGIN + 12,
    /* the commond is to report uplink  and downlink link capacity estimation */
    MIPC_DATA_LINK_CAPACITY_ESTIMATE_IND                    = MIPC_DATA_IND_BEGIN + 13,
    /* the commond is to report Network Limit State */
    MIPC_DATA_NW_LIMIT_IND                                  = MIPC_DATA_IND_BEGIN + 14,
    /* the commond is to report data timer */
    MIPC_DATA_TIMER_IND                                     = MIPC_DATA_IND_BEGIN + 15,
    /* the commond is to report keep alive info */
    MIPC_DATA_KEEPALIVE_STATUS_IND                          = MIPC_DATA_IND_BEGIN + 16,
    /* the commond is to report mobile data usage */
    MIPC_DATA_MOBILE_DATA_USAGE_IND                         = MIPC_DATA_IND_BEGIN + 17,
    /* the commond is to report netowrk reject cause */
    MIPC_DATA_NETWORK_REJECT_CAUSE_IND                      = MIPC_DATA_IND_BEGIN + 18,
    /* the commond is to report DSDA(dual sim dual active) state */
    MIPC_DATA_DSDA_STATE_IND                                = MIPC_DATA_IND_BEGIN + 19,
    /* the commond is to indicate UMTS PS domain state, only for specific modem branch */
    MIPC_DATA_UMTS_PS_STATE_IND                             = MIPC_DATA_IND_BEGIN + 20,
    /* the commond is to indicate which apn timer has been reset */
    MIPC_DATA_RETRY_TIMER_IND                               = MIPC_DATA_IND_BEGIN + 21,
    /* the commond is to indicate URSP re-evaluation */
    MIPC_DATA_URSP_REEVAL_IND                               = MIPC_DATA_IND_BEGIN + 22,
    /* the commond is to indicate UE policy change */
    MIPC_DATA_URSP_UE_POLICY_CHG_IND                        = MIPC_DATA_IND_BEGIN + 23,
    MIPC_DATA_IND_END                                       = MIPC_DATA_IND_BEGIN + 0xFF,

    MIPC_INTERNAL_IND_BEGIN                                 = MIPC_IND_BEGIN + 0x300,
    /* for test only */
    MIPC_INTERNAL_TEST_IND                                  = MIPC_INTERNAL_IND_BEGIN + 1,
    /* unsolicited network interface control indication */
    MIPC_INTERNAL_EIF_IND                                   = MIPC_INTERNAL_IND_BEGIN + 2,
    /* PDN handover indication (ex. L->W or W->L) */
    MIPC_INTERNAL_HO_IND                                    = MIPC_INTERNAL_IND_BEGIN + 3,
    MIPC_INTERNAL_IND_END                                   = MIPC_INTERNAL_IND_BEGIN + 0xFF,

    MIPC_NW_IND_BEGIN                                       = MIPC_IND_BEGIN + 0x400,
    /* registration state changed indication */
    MIPC_NW_REGISTER_IND                                    = MIPC_NW_IND_BEGIN + 1,
    /* singal changed indication */
    MIPC_NW_SIGNAL_IND                                      = MIPC_NW_IND_BEGIN + 2,
    /* PS attach state changed indication */
    MIPC_NW_PS_IND                                          = MIPC_NW_IND_BEGIN + 3,
    /* radio status changed indication */
    MIPC_NW_RADIO_IND                                       = MIPC_NW_IND_BEGIN + 4,
    /* IA status changed indication */
    MIPC_NW_IA_IND                                          = MIPC_NW_IND_BEGIN + 5,
    /* NITZ changed indication */
    MIPC_NW_NITZ_IND                                        = MIPC_NW_IND_BEGIN + 6,
    /* location changed indication */
    MIPC_NW_LOCATION_INFO_IND                               = MIPC_NW_IND_BEGIN + 7,
    /* CS state change indication. */
    MIPC_NW_CS_IND                                          = MIPC_NW_IND_BEGIN + 8,
    /* Signalling connection state change indication. */
    MIPC_NW_CSCON_IND                                       = MIPC_NW_IND_BEGIN + 9,
    /* Preferred provider list changed by network flow. */
    MIPC_NW_PREFERRED_PROVIDER_IND                          = MIPC_NW_IND_BEGIN + 10,
    /* dl and ul ca info of lte and nr. */
    MIPC_NW_CAINFO_IND                                      = MIPC_NW_IND_BEGIN + 11,
    /* eons state change indication. */
    MIPC_NW_EONS_IND                                        = MIPC_NW_IND_BEGIN + 12,
    /* ciev state change indication. */
    MIPC_NW_CIEV_IND                                        = MIPC_NW_IND_BEGIN + 13,
    /* Inform the information of system selection, according to RAT, location and attach status. */
    MIPC_NW_EGMSS_IND                                       = MIPC_NW_IND_BEGIN + 14,
    /* packet switching data service capability ind. */
    MIPC_NW_PSBEARER_IND                                    = MIPC_NW_IND_BEGIN + 15,
    /* Preferred provider list changed by network flow. */
    MIPC_NW_ECELL_IND                                       = MIPC_NW_IND_BEGIN + 16,
    /* anbr changed indication */
    MIPC_NW_ANBR_IND                                        = MIPC_NW_IND_BEGIN + 17,
    /* irat changed indication */
    MIPC_NW_IRAT_IND                                        = MIPC_NW_IND_BEGIN + 18,
    /* Report network registration status. */
    MIPC_NW_EREGINFO_IND                                    = MIPC_NW_IND_BEGIN + 19,
    /* indicates the modulation scheme of the active RAT. */
    MIPC_NW_EMODCFG_IND                                     = MIPC_NW_IND_BEGIN + 20,
    /* on lte network info. */
    MIPC_NW_EPCELLINFO_IND                                  = MIPC_NW_IND_BEGIN + 21,
    /* Pseudo_cell info urc. */
    MIPC_NW_PSEUDO_CELL_IND                                 = MIPC_NW_IND_BEGIN + 22,
    /* Pseudo_cell info urc. */
    MIPC_NW_NETWORK_INFO_IND                                = MIPC_NW_IND_BEGIN + 23,
    /* Plmn id changed. */
    MIPC_NW_MCCMNC_IND                                      = MIPC_NW_IND_BEGIN + 24,
    /* Physical channel config changed indication. */
    MIPC_NW_PHYSICAL_CHANNEL_CONFIGS_IND                    = MIPC_NW_IND_BEGIN + 25,
    /* the status of the OTASP. */
    MIPC_NW_OTACMSG_IND                                     = MIPC_NW_IND_BEGIN + 26,
    /* the status of the OTASP. */
    MIPC_NW_BARRING_INFO_IND                                = MIPC_NW_IND_BEGIN + 27,
    /* This interface is used to report radio capability to host. */
    MIPC_NW_RADIO_CAPABILITY_IND                            = MIPC_NW_IND_BEGIN + 28,
    /* This interface is used to report current rat to host. */
    MIPC_NW_CURRENT_RAT_IND                                 = MIPC_NW_IND_BEGIN + 29,
    /* Report the camping on cell status. */
    MIPC_NW_CAMP_STATE_IND                                  = MIPC_NW_IND_BEGIN + 30,
    /* This interface is used to report the sim which has nr capability to host. */
    MIPC_NW_NR_SWITCH_IND                                   = MIPC_NW_IND_BEGIN + 31,
    /* This interface is used to report the femtocell info. */
    MIPC_NW_FEMTOCELL_INFO_IND                              = MIPC_NW_IND_BEGIN + 32,
    /* onNotifyTXPower URC. */
    MIPC_NW_ETXPWR_IND                                      = MIPC_NW_IND_BEGIN + 33,
    /* handleTXPowerStatus URC. */
    MIPC_NW_ETXPWRSTUS_IND                                  = MIPC_NW_IND_BEGIN + 34,
    /* Indicates the status about IWLAN. */
    MIPC_NW_IWLAN_IND                                       = MIPC_NW_IND_BEGIN + 35,
    /* handle ECHINFO URC */
    MIPC_NW_CH_INFO_IND                                     = MIPC_NW_IND_BEGIN + 36,
    /* handle E5GUW URC */
    MIPC_NW_NRUW_INFO_IND                                   = MIPC_NW_IND_BEGIN + 37,
    /* NR ca bands */
    MIPC_NW_NR_CA_BAND_IND                                  = MIPC_NW_IND_BEGIN + 38,
    /* nr5g subcarrier spacing in khz */
    MIPC_NW_NR_SCS_IND                                      = MIPC_NW_IND_BEGIN + 39,
    /* Network scan result */
    MIPC_NW_NETWORK_SCAN_IND                                = MIPC_NW_IND_BEGIN + 40,
    /* CA info */
    MIPC_NW_CA_INFO_IND                                     = MIPC_NW_IND_BEGIN + 41,
    /* 5GUC info */
    MIPC_NW_NRUC_INFO_IND                                   = MIPC_NW_IND_BEGIN + 42,
    /* The first plmn */
    MIPC_NW_FIRST_PLMN_IND                                  = MIPC_NW_IND_BEGIN + 43,
    MIPC_NW_IND_END                                         = MIPC_NW_IND_BEGIN + 0xFF,

    MIPC_SIM_IND_BEGIN                                      = MIPC_IND_BEGIN + 0x500,
    /* SIM state changed indication */
    MIPC_SIM_STATE_IND                                      = MIPC_SIM_IND_BEGIN + 1,
    /* SIM status changed indication */
    MIPC_SIM_STATUS_IND                                     = MIPC_SIM_IND_BEGIN + 2,
    /*  */
    MIPC_SIM_EUICC_SLOTS_STATUS_IND                         = MIPC_SIM_IND_BEGIN + 3,
    /*  */
    MIPC_SIM_ICCID_IND                                      = MIPC_SIM_IND_BEGIN + 4,
    /* SIM status changed indication with cause */
    MIPC_SIM_STATUS_CHANGE_WITH_CAUSE_IND                   = MIPC_SIM_IND_BEGIN + 5,
    /* SIM physical slots mapping set req command done indication  */
    MIPC_SIM_PHYSICAL_SLOTS_MAPPING_DONE_IND                = MIPC_SIM_IND_BEGIN + 6,
    /* csim imsi changed indication */
    MIPC_SIM_CSIM_IMSI_CHANGE_IND                           = MIPC_SIM_IND_BEGIN + 7,
    /* report sim me lock rules and device lock status */
    MIPC_SIM_SML_STATUS_IND                                 = MIPC_SIM_IND_BEGIN + 8,
    /* report rsu event id and event string */
    MIPC_SIM_SML_RSU_IND                                    = MIPC_SIM_IND_BEGIN + 9,
    /* vsim reset indication  */
    MIPC_SIM_VSIM_RESET_IND                                 = MIPC_SIM_IND_BEGIN + 12,
    /* vsim APDU indication  */
    MIPC_SIM_VSIM_APDU_IND                                  = MIPC_SIM_IND_BEGIN + 13,
    /* vsim APDU indication  */
    MIPC_SIM_VSIM_EVENT_IND                                 = MIPC_SIM_IND_BEGIN + 14,
    /* sim APP indication  */
    MIPC_SIM_SIMAPP_IND                                     = MIPC_SIM_IND_BEGIN + 15,
    /* test sim indication  */
    MIPC_SIM_TEST_SIM_IND                                   = MIPC_SIM_IND_BEGIN + 16,
    /* CT3G indication  */
    MIPC_SIM_CT3G_IND                                       = MIPC_SIM_IND_BEGIN + 17,
    /* CARD type indication  */
    MIPC_SIM_CARD_TYPE_IND                                  = MIPC_SIM_IND_BEGIN + 18,
    /* sim indication  */
    MIPC_SIM_SIMIND_IND                                     = MIPC_SIM_IND_BEGIN + 19,
    /* sim status changed, host or ap can query new sim status */
    MIPC_SIM_STATUS_CHANGED_IND                             = MIPC_SIM_IND_BEGIN + 20,
    MIPC_SIM_IND_END                                        = MIPC_SIM_IND_BEGIN + 0xFF,

    MIPC_SMS_IND_BEGIN                                      = MIPC_IND_BEGIN + 0x600,
    /* SMS configuration changed indication(sim plug out and plug in would trigger this indication) */
    MIPC_SMS_CFG_IND                                        = MIPC_SMS_IND_BEGIN + 1,
    /* new sms indication when user prefer_no_ack&save_in_TE */
    MIPC_SMS_NEW_SMS_IND                                    = MIPC_SMS_IND_BEGIN + 2,
    /* SMS storage status changed indication, new sms saved in DEVICE would trigger this indication */
    MIPC_SMS_STORE_STATUS_IND                               = MIPC_SMS_IND_BEGIN + 3,
    /* new status report indication when user prefer_no_ack */
    MIPC_SMS_NEW_STATUS_REPORT_IND                          = MIPC_SMS_IND_BEGIN + 6,
    /* CBM indication contains ETWS primary/ETWS secondary/CMAS/other cbm msgs */
    MIPC_SMS_NEW_CBM_IND                                    = MIPC_SMS_IND_BEGIN + 7,
    /* new indication about SCBM feature */
    MIPC_SMS_SCBM_IND                                       = MIPC_SMS_IND_BEGIN + 8,
    /* other information about SMS to indication */
    MIPC_SMS_EXT_INFO_IND                                   = MIPC_SMS_IND_BEGIN + 9,
    MIPC_SMS_IND_END                                        = MIPC_SMS_IND_BEGIN + 0xFF,

    MIPC_SS_IND_BEGIN                                       = MIPC_IND_BEGIN + 0x700,
    /* USSD received indication */
    MIPC_SS_USSD_IND                                        = MIPC_SS_IND_BEGIN + 1,
    /* the unsol supp svc notification ind */
    MIPC_SS_ECMCCSS_IND                                     = MIPC_SS_IND_BEGIN + 2,
    /* Call Forward UNSOL ind */
    MIPC_SS_CFU_IND                                         = MIPC_SS_IND_BEGIN + 3,
    /* XCAP RCN ind */
    MIPC_SS_XCAP_RCN_IND                                    = MIPC_SS_IND_BEGIN + 4,
    /* IMS XUI ind */
    MIPC_SS_IMS_XUI_IND                                     = MIPC_SS_IND_BEGIN + 5,
    MIPC_SS_IND_END                                         = MIPC_SS_IND_BEGIN + 0xFF,

    MIPC_STK_IND_BEGIN                                      = MIPC_IND_BEGIN + 0x800,
    /* receive proactive command from UICC */
    MIPC_STK_PAC_IND                                        = MIPC_STK_IND_BEGIN + 1,
    /* SIM Refresh ind */
    MIPC_STK_SIM_REFRESH_IND                                = MIPC_STK_IND_BEGIN + 2,
    /* bip event notify */
    MIPC_STK_BIP_EVENT_NOTIFY_IND                           = MIPC_STK_IND_BEGIN + 3,
    MIPC_STK_IND_END                                        = MIPC_STK_IND_BEGIN + 0xFF,

    MIPC_CALL_IND_BEGIN                                     = MIPC_IND_BEGIN + 0x900,
    /* call status changed indication */
    MIPC_CALL_STATUS_IND                                    = MIPC_CALL_IND_BEGIN + 1,
    /* call event indication */
    MIPC_CALL_EVENT_IND                                     = MIPC_CALL_IND_BEGIN + 2,
    /* this message is used to inform host that the call mode change */
    MIPC_CALL_MODE_IND                                      = MIPC_CALL_IND_BEGIN + 3,
    /* this message is used to inofrm host response code from NW which UA received */
    MIPC_CALL_SIP_IND                                       = MIPC_CALL_IND_BEGIN + 4,
    /* this message is used to indicate host to XML event package */
    MIPC_CALL_CONFERENCE_IND                                = MIPC_CALL_IND_BEGIN + 5,
    /* this message is used to indicate host to XML event package */
    MIPC_CALL_IMS_EVENT_PACKAGE_IND                         = MIPC_CALL_IND_BEGIN + 6,
    /* ecc list changed indication */
    MIPC_CALL_ECC_LIST_CHANGE_IND                           = MIPC_CALL_IND_BEGIN + 7,
    /* supplementary service indication */
    MIPC_CALL_SS_IND                                        = MIPC_CALL_IND_BEGIN + 8,
    /* this message is used to indicate ecc call back mode change */
    MIPC_CALL_ECBM_CHANGE_IND                               = MIPC_CALL_IND_BEGIN + 9,
    /* this message is used to indicate CRSS  */
    MIPC_CALL_CRSS_IND                                      = MIPC_CALL_IND_BEGIN + 10,
    MIPC_CALL_ECT_IND                                       = MIPC_CALL_IND_BEGIN + 11,
    MIPC_CALL_CIPHER_IND                                    = MIPC_CALL_IND_BEGIN + 12,
    MIPC_CALL_RTT_AUDIO_IND                                 = MIPC_CALL_IND_BEGIN + 13,
    MIPC_CALL_RTT_CAPABILITY_IND                            = MIPC_CALL_IND_BEGIN + 14,
    MIPC_CALL_LOCAL_RTT_MODIFY_RESULT_IND                   = MIPC_CALL_IND_BEGIN + 15,
    MIPC_CALL_PEER_RTT_MODIFY_RESULT_IND                    = MIPC_CALL_IND_BEGIN + 16,
    MIPC_CALL_RTT_TEXT_RECEIVE_IND                          = MIPC_CALL_IND_BEGIN + 17,
    MIPC_CALL_RCS_DIGITS_LINE_IND                           = MIPC_CALL_IND_BEGIN + 18,
    MIPC_CALL_DISPLAY_AND_SIGNALS_INFO_IND                  = MIPC_CALL_IND_BEGIN + 19,
    MIPC_CALL_EXTENDED_DISPLAY_INFO_IND                     = MIPC_CALL_IND_BEGIN + 20,
    MIPC_CALL_LINE_CONTROL_INFO_IND                         = MIPC_CALL_IND_BEGIN + 21,
    MIPC_CALL_REDIRECTING_NUMBER_INFO_IND                   = MIPC_CALL_IND_BEGIN + 22,
    /* gwsd event indication */
    MIPC_CALL_GWSD_EVENT_IND                                = MIPC_CALL_IND_BEGIN + 23,
    /* econf urc indication */
    MIPC_CALL_ECONF_IND                                     = MIPC_CALL_IND_BEGIN + 24,
    /* this message is used to report IMS sip header */
    MIPC_CALL_IMS_SIP_HEADER_IND                            = MIPC_CALL_IND_BEGIN + 25,
    /* this message is used to indicate ecc redial */
    MIPC_CALL_ECC_REDIAL_IND                                = MIPC_CALL_IND_BEGIN + 27,
    /* This message is used to indicate emergency bearer services support */
    MIPC_CALL_EMERGENCY_BEARER_SUPPORT_IND                  = MIPC_CALL_IND_BEGIN + 28,
    /* This command is used to provide User Interactive Service information accompanying with a specific ongoing Call */
    MIPC_CALL_UIS_INFO_IND                                  = MIPC_CALL_IND_BEGIN + 29,
    /* Set IMS call additional information */
    MIPC_CALL_CALL_ADDITIONAL_INFO_IND                      = MIPC_CALL_IND_BEGIN + 30,
    /* this message is used to indicate the INVITE SIP message of MT CALL */
    MIPC_CALL_MT_SIP_INVITE_IND                             = MIPC_CALL_IND_BEGIN + 31,
    MIPC_CALL_IND_END                                       = MIPC_CALL_IND_BEGIN + 0xFF,

    MIPC_IMS_IND_BEGIN                                      = MIPC_IND_BEGIN + 0xA00,
    /* IMS configuration changed indication */
    MIPC_IMS_CONFIG_IND                                     = MIPC_IMS_IND_BEGIN + 0,
    /* IMS state changed indication */
    MIPC_IMS_STATE_IND                                      = MIPC_IMS_IND_BEGIN + 1,
    /* to notify AP the emergency service support status in the current cell */
    MIPC_IMS_SUPPORT_ECC_IND                                = MIPC_IMS_IND_BEGIN + 2,
    /* IMS/emergency PDN status indication */
    MIPC_IMS_PDN_IND                                        = MIPC_IMS_IND_BEGIN + 3,
    /* to notify AP the NAPTR infomation */
    MIPC_IMS_NAPTR_IND                                      = MIPC_IMS_IND_BEGIN + 4,
    /* IMS eireg info indication */
    MIPC_IMS_REG_IND                                        = MIPC_IMS_IND_BEGIN + 5,
    /* IMS sip reg info indication */
    MIPC_IMS_SIP_REG_INFO_IND                               = MIPC_IMS_IND_BEGIN + 6,
    /* IMS cirepi indication */
    MIPC_IMS_VOPS_IND                                       = MIPC_IMS_IND_BEGIN + 7,
    /* IMS register remain time indication */
    MIPC_IMS_REG_REMAIN_TIME_IND                            = MIPC_IMS_IND_BEGIN + 8,
    /* IMS eimsui indication */
    MIPC_IMS_UI_IND                                         = MIPC_IMS_IND_BEGIN + 9,
    MIPC_IMS_IND_END                                        = MIPC_IMS_IND_BEGIN + 0xFF,

    MIPC_WFC_IND_BEGIN                                      = MIPC_IND_BEGIN + 0xB00,
    /* cell quality indication(configured by REGISTER_CELL_SIGNAL_IND_REQ) */
    MIPC_WFC_CELL_SIGNAL_IND                                = MIPC_WFC_IND_BEGIN + 0,
    /* notify AP current active PDN count on WiFi */
    MIPC_WFC_WIFI_PDN_COUNT_IND                             = MIPC_WFC_IND_BEGIN + 1,
    /* inform AP about handover progress */
    MIPC_WFC_PDN_HO_IND                                     = MIPC_WFC_IND_BEGIN + 2,
    /* notify AP that UE is going to rove out WiFi coverage when WFC in call */
    MIPC_WFC_ROVE_OUT_IND                                   = MIPC_WFC_IND_BEGIN + 3,
    /* Service specific access control restriction status ind */
    MIPC_WFC_SSAC_IND                                       = MIPC_WFC_IND_BEGIN + 4,
    /* wifi pdn error from modem */
    MIPC_WFC_WIFI_PDN_ERR_IND                               = MIPC_WFC_IND_BEGIN + 5,
    /*  IMS pdn out of service from modem */
    MIPC_WFC_WIFI_PDN_OOS_IND                               = MIPC_WFC_IND_BEGIN + 6,
    /* some information about WFC */
    MIPC_WFC_WFC_IND                                        = MIPC_WFC_IND_BEGIN + 7,
    MIPC_WFC_IND_END                                        = MIPC_WFC_IND_BEGIN + 0xFF,

    MIPC_PHB_IND_BEGIN                                      = MIPC_IND_BEGIN + 0xC00,
    /* PHB ready state indication */
    MIPC_PHB_READY_STATE_IND                                = MIPC_PHB_IND_BEGIN + 0,
    MIPC_PHB_IND_END                                        = MIPC_PHB_IND_BEGIN + 0xFF,

    MIPC_EMBMS_IND_BEGIN                                    = MIPC_IND_BEGIN + 0xD00,
    /* This interface is used to report any changes in eMBMS service coverage status to host. */
    MIPC_EMBMS_EMSRV_IND                                    = MIPC_EMBMS_IND_BEGIN + 0,
    /* This interface is used to report MBMS sessions list update information to host. */
    MIPC_EMBMS_EMSLUI_IND                                   = MIPC_EMBMS_IND_BEGIN + 1,
    /* This interface is used to report neighbouring frequency with bands list and MBMS SAI list to host. */
    MIPC_EMBMS_EMSAILNF_IND                                 = MIPC_EMBMS_IND_BEGIN + 2,
    /* This interface is used to report the status of session to host,during session activation and deactivation. */
    MIPC_EMBMS_EMSESS_IND                                   = MIPC_EMBMS_IND_BEGIN + 3,
    /* This interface is used to report the hVoLTE mode to host. */
    MIPC_EMBMS_EHVOLTE_IND                                  = MIPC_EMBMS_IND_BEGIN + 4,
    MIPC_EMBMS_IND_END                                      = MIPC_EMBMS_IND_BEGIN + 0xFF,


    MIPC_CMD_BEGIN                                          = 0x8000,

    MIPC_SYS_CMD_BEGIN                                      = MIPC_CMD_BEGIN + 0,
    /* send REBOOT command to AP */
    MIPC_SYS_REBOOT_CMD                                     = MIPC_SYS_CMD_BEGIN + 1,
    /* the result for REBOOT_CMD */
    MIPC_SYS_REBOOT_RSP                                     = MIPC_SYS_CMD_BEGIN + 2,
    /* set host configuration request */
    MIPC_SYS_SET_CONFIG_DIPC_CMD                            = MIPC_SYS_CMD_BEGIN + 3,
    /* set host configuration response */
    MIPC_SYS_SET_CONFIG_DIPC_RSP                            = MIPC_SYS_CMD_BEGIN + 4,
    /* request to update the configuration */
    MIPC_SYS_CONFIG_NEEDED_TO_UPDATE_CMD                    = MIPC_SYS_CMD_BEGIN + 5,
    /* request to update the configuration */
    MIPC_SYS_CONFIG_NEEDED_TO_UPDATE_RSP                    = MIPC_SYS_CMD_BEGIN + 6,
    /* get host configuration request */
    MIPC_SYS_GET_CONFIG_DIPC_CMD                            = MIPC_SYS_CMD_BEGIN + 7,
    /* get host configuration response */
    MIPC_SYS_GET_CONFIG_DIPC_RSP                            = MIPC_SYS_CMD_BEGIN + 8,
    /* set sAP time */
    MIPC_SYS_SET_TIME_CMD                                   = MIPC_SYS_CMD_BEGIN + 9,
    /* the result for TIME_CMD */
    MIPC_SYS_SET_TIME_RSP                                   = MIPC_SYS_CMD_BEGIN + 10,
    MIPC_SYS_CMD_END                                        = MIPC_SYS_CMD_BEGIN + 0xFF,

    MIPC_APN_CMD_BEGIN                                      = MIPC_CMD_BEGIN + 0x100,
    MIPC_APN_CMD_END                                        = MIPC_APN_CMD_BEGIN + 0xFF,

    MIPC_DATA_CMD_BEGIN                                     = MIPC_CMD_BEGIN + 0x200,
    MIPC_DATA_CMD_END                                       = MIPC_DATA_CMD_BEGIN + 0xFF,

    MIPC_INTERNAL_CMD_BEGIN                                 = MIPC_CMD_BEGIN + 0x300,
    /*  */
    MIPC_INTERNAL_TEST_CMD                                  = MIPC_INTERNAL_CMD_BEGIN + 1,
    /*  */
    MIPC_INTERNAL_TEST_RSP                                  = MIPC_INTERNAL_CMD_BEGIN + 2,
    /*  */
    MIPC_INTERNAL_EIPPORT_CMD                               = MIPC_INTERNAL_CMD_BEGIN + 3,
    /*  */
    MIPC_INTERNAL_EIPPORT_RSP                               = MIPC_INTERNAL_CMD_BEGIN + 4,
    /*  */
    MIPC_INTERNAL_EIPSPI_CMD                                = MIPC_INTERNAL_CMD_BEGIN + 5,
    /*  */
    MIPC_INTERNAL_EIPSPI_RSP                                = MIPC_INTERNAL_CMD_BEGIN + 6,
    /* free multi ip spi */
    MIPC_INTERNAL_MULTI_EIPSPI_FREE_CMD                     = MIPC_INTERNAL_CMD_BEGIN + 7,
    /* response of free multi ip spi */
    MIPC_INTERNAL_MULTI_EIPSPI_FREE_RSP                     = MIPC_INTERNAL_CMD_BEGIN + 8,
    MIPC_INTERNAL_CMD_END                                   = MIPC_INTERNAL_CMD_BEGIN + 0xFF,

    MIPC_NW_CMD_BEGIN                                       = MIPC_CMD_BEGIN + 0x400,
    MIPC_NW_CMD_END                                         = MIPC_NW_CMD_BEGIN + 0xFF,

    MIPC_SIM_CMD_BEGIN                                      = MIPC_CMD_BEGIN + 0x500,
    MIPC_SIM_CMD_END                                        = MIPC_SIM_CMD_BEGIN + 0xFF,

    MIPC_SMS_CMD_BEGIN                                      = MIPC_CMD_BEGIN + 0x600,
    /* new sms indication when user prefer_ack&save_in_TE */
    MIPC_SMS_NEW_SMS_CMD                                    = MIPC_SMS_CMD_BEGIN + 1,
    /* to ack for the NEW_SMS_CMD */
    MIPC_SMS_NEW_SMS_RSP                                    = MIPC_SMS_CMD_BEGIN + 2,
    /* [3GPP] new status report indication when user prefer_ack */
    MIPC_SMS_NEW_STATUS_REPORT_CMD                          = MIPC_SMS_CMD_BEGIN + 3,
    /* [3GPP]to ack for the NEW_STATUS_REPORT_CMD */
    MIPC_SMS_NEW_STATUS_REPORT_RSP                          = MIPC_SMS_CMD_BEGIN + 4,
    MIPC_SMS_CMD_END                                        = MIPC_SMS_CMD_BEGIN + 0xFF,

    MIPC_SS_CMD_BEGIN                                       = MIPC_CMD_BEGIN + 0x700,
    MIPC_SS_CMD_END                                         = MIPC_SS_CMD_BEGIN + 0xFF,

    MIPC_STK_CMD_BEGIN                                      = MIPC_CMD_BEGIN + 0x800,
    MIPC_STK_CMD_END                                        = MIPC_STK_CMD_BEGIN + 0xFF,

    MIPC_CALL_CMD_BEGIN                                     = MIPC_CMD_BEGIN + 0x900,
    /* This command requests users to approve an incoming call in Call Present stage */
    MIPC_CALL_APPROVE_INCOMING_CMD                          = MIPC_CALL_CMD_BEGIN + 1,
    /* This command allows users to approve an incoming call in Call Present stage */
    MIPC_CALL_APPROVE_INCOMING_RSP                          = MIPC_CALL_CMD_BEGIN + 2,
    MIPC_CALL_CMD_END                                       = MIPC_CALL_CMD_BEGIN + 0xFF,

    MIPC_IMS_CMD_BEGIN                                      = MIPC_CMD_BEGIN + 0xA00,
    /* to notify AP the p-cscf address discovery */
    MIPC_IMS_PDIS_CMD                                       = MIPC_IMS_CMD_BEGIN + 0,
    /* response of p-cscf address discovery */
    MIPC_IMS_PDIS_RSP                                       = MIPC_IMS_CMD_BEGIN + 1,
    MIPC_IMS_CMD_END                                        = MIPC_IMS_CMD_BEGIN + 0xFF,

    MIPC_WFC_CMD_BEGIN                                      = MIPC_CMD_BEGIN + 0xB00,
    /* request HOST to Ping NW and response with result */
    MIPC_WFC_PING_CMD                                       = MIPC_WFC_CMD_BEGIN + 0,
    /* to ack for the PING_CMD */
    MIPC_WFC_PING_RSP                                       = MIPC_WFC_CMD_BEGIN + 1,
    /* Modem request ARP/NDP query */
    MIPC_WFC_GET_MAC_CMD                                    = MIPC_WFC_CMD_BEGIN + 2,
    /* Modem request ARP/NDP query */
    MIPC_WFC_GET_MAC_RSP                                    = MIPC_WFC_CMD_BEGIN + 3,
    /* request AP that WO need keep alive service */
    MIPC_WFC_NATT_KEEP_ALIVE_CMD                            = MIPC_WFC_CMD_BEGIN + 4,
    /* notify the MD that wifi driver support the NATT or not */
    MIPC_WFC_NATT_KEEP_ALIVE_RSP                            = MIPC_WFC_CMD_BEGIN + 5,
    /* MD use this CMD to register the WIFI_SIGNAL_NTF */
    MIPC_WFC_REGISTER_WIFI_SIGNAL_NTF_CMD                   = MIPC_WFC_CMD_BEGIN + 6,
    /* RSP for REGISTER_WIFI_SIGNAL_NTF_CMD */
    MIPC_WFC_REGISTER_WIFI_SIGNAL_NTF_RSP                   = MIPC_WFC_CMD_BEGIN + 7,
    MIPC_WFC_CMD_END                                        = MIPC_WFC_CMD_BEGIN + 0xFF,


    MIPC_NTF_BEGIN                                          = 0xC000,

    MIPC_SYS_NTF_BEGIN                                      = MIPC_NTF_BEGIN + 0,
    MIPC_SYS_NTF_END                                        = MIPC_SYS_NTF_BEGIN + 0xFF,

    MIPC_APN_NTF_BEGIN                                      = MIPC_NTF_BEGIN + 0x100,
    MIPC_APN_NTF_END                                        = MIPC_APN_NTF_BEGIN + 0xFF,

    MIPC_DATA_NTF_BEGIN                                     = MIPC_NTF_BEGIN + 0x200,
    /* notify use or unuse fallback cid */
    MIPC_DATA_ACT_CALL_NTF                                  = MIPC_DATA_NTF_BEGIN + 0,
    MIPC_DATA_NTF_END                                       = MIPC_DATA_NTF_BEGIN + 0xFF,

    MIPC_INTERNAL_NTF_BEGIN                                 = MIPC_NTF_BEGIN + 0x300,
    /* for test only */
    MIPC_INTERNAL_TEST_NTF                                  = MIPC_INTERNAL_NTF_BEGIN + 1,
    /* inject tst string */
    MIPC_INTERNAL_INJECT_TST_NTF                            = MIPC_INTERNAL_NTF_BEGIN + 2,
    MIPC_INTERNAL_NTF_END                                   = MIPC_INTERNAL_NTF_BEGIN + 0xFF,

    MIPC_NW_NTF_BEGIN                                       = MIPC_NTF_BEGIN + 0x400,
    MIPC_NW_NTF_END                                         = MIPC_NW_NTF_BEGIN + 0xFF,

    MIPC_SIM_NTF_BEGIN                                      = MIPC_NTF_BEGIN + 0x500,
    MIPC_SIM_NTF_END                                        = MIPC_SIM_NTF_BEGIN + 0xFF,

    MIPC_SMS_NTF_BEGIN                                      = MIPC_NTF_BEGIN + 0x600,
    MIPC_SMS_NTF_END                                        = MIPC_SMS_NTF_BEGIN + 0xFF,

    MIPC_SS_NTF_BEGIN                                       = MIPC_NTF_BEGIN + 0x700,
    MIPC_SS_NTF_END                                         = MIPC_SS_NTF_BEGIN + 0xFF,

    MIPC_STK_NTF_BEGIN                                      = MIPC_NTF_BEGIN + 0x800,
    MIPC_STK_NTF_END                                        = MIPC_STK_NTF_BEGIN + 0xFF,

    MIPC_WFC_NTF_BEGIN                                      = MIPC_NTF_BEGIN + 0xB00,
    /* update WiFi signal value to the modem */
    MIPC_WFC_WIFI_SIGNAL_NTF                                = MIPC_WFC_NTF_BEGIN + 0,
    /* Notify ePDG screen state */
    MIPC_WFC_EPDG_SCREEN_STATE_NTF                          = MIPC_WFC_NTF_BEGIN + 1,
    /* provide the wifi information to modem module */
    MIPC_WFC_WIFI_INFO_NTF                                  = MIPC_WFC_NTF_BEGIN + 2,
    MIPC_WFC_NTF_END                                        = MIPC_WFC_NTF_BEGIN + 0xFF,


};

    /* MIPC_MSG.SYS_GET_INFO_REQ */
enum mipc_sys_get_info_req_tlv_enum {
    mipc_sys_get_info_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SYS_GET_INFO_CNF */
enum mipc_sys_get_info_cnf_tlv_enum {
    mipc_sys_get_info_cnf_tlv_NONE = 0,
    /* phase out, please use SYS_CELLULAR_CLASS_V1. A bitmask that represents what cellular technology are supported */
    /* type = bitmap, refer to SYS_CAP_CELLULAR_CLASS */
    MIPC_SYS_GET_INFO_CNF_T_SYS_CELLULAR_CLASS              = 0x100,
    /* The presence of circuit voice service, and how such service interacts with data service */
    /* type = uint8_t, refer to SYS_VOICE_CLASS */
    MIPC_SYS_GET_INFO_CNF_T_VOICE_CLASS                     = 0x101,
    /* A bitmap that represents which SIM type are supported */
    /* type = uint8_t, refer to SYS_SIM_CLASS */
    MIPC_SYS_GET_INFO_CNF_T_SIM_CLASS                       = 0x102,
    /* A bitmap that represents which radio technologies are supported by the function */
    /* type = bitmap, refer to SYS_CAP_DATA */
    MIPC_SYS_GET_INFO_CNF_T_DATA_CLASS                      = 0x103,
    /* A bitmap that represents which GSM bands are supported */
    /* type = bitmap, refer to SYS_CAP_GSM_BAND */
    MIPC_SYS_GET_INFO_CNF_T_GSM_BAND_CLASS                  = 0x104,
    /* A bitmap that represents which UMTS bands are supported */
    /* type = bitmap, refer to SYS_CAP_UMTS_BAND */
    MIPC_SYS_GET_INFO_CNF_T_UMTS_BAND_CLASS                 = 0x105,
    /* A bitmap that represents which TDS bands are supported */
    /* type = bitmap, refer to SYS_CAP_TDS_BAND */
    MIPC_SYS_GET_INFO_CNF_T_TDS_BAND_CLASS                  = 0x106,
    /* A bitmap that represents which CDMA bands are supported */
    /* type = bitmap, refer to SYS_CAP_CDMA_BAND */
    MIPC_SYS_GET_INFO_CNF_T_C2K_BAND_CLASS                  = 0x107,
    /* A bitmap that represents which LTE bands are supported */
    /* type = struct, refer to sys_lte_band */
    MIPC_SYS_GET_INFO_CNF_T_LTE_BAND_CLASS                  = 0x108,
    /* A bitmap that represents which NR bands are supported */
    /* type = struct, refer to sys_nr_band */
    MIPC_SYS_GET_INFO_CNF_T_NR_BAND_CLASS                   = 0x109,
    /* A bitmap that represents the type of SMS messages and directional flow are supported */
    /* type = bitmap, refer to SYS_CAP_SMS */
    MIPC_SYS_GET_INFO_CNF_T_SMS_CAPS                        = 0x10A,
    /* A bitmap that represents the control capabilities that the device supports */
    /* type = bitmap, refer to SYS_CAP_CTRL */
    MIPC_SYS_GET_INFO_CNF_T_CTRL_CAPS                       = 0x10B,
    /* A bitmap that represents which AUTH algorithm are supported */
    /* type = uint8_t, refer to SYS_AUTH_ALGO */
    MIPC_SYS_GET_INFO_CNF_T_AUTH_ALGO_CAPS                  = 0x10C,
    /* a bitmap that represents the service capabilities that the device supports */
    /* type = bitmap, refer to SYS_CAP_SERVICE */
    MIPC_SYS_GET_INFO_CNF_T_SERVICE_CAPS                    = 0x10D,
    /* A structure the contains how many SIM and protocol are supported */
    /* type = struct, refer to sys_modem */
    MIPC_SYS_GET_INFO_CNF_T_MULTI_MD                        = 0x10E,
    /* device id (IMEI) */
    /* type = string */
    MIPC_SYS_GET_INFO_CNF_T_DEVICE_ID                       = 0x10F,
    /* manufactuer */
    /* type = string */
    MIPC_SYS_GET_INFO_CNF_T_MANUFCTR                        = 0x110,
    /* firmware version */
    /* type = string */
    MIPC_SYS_GET_INFO_CNF_T_FIRMWARE                        = 0x111,
    /* hardware version */
    /* type = string */
    MIPC_SYS_GET_INFO_CNF_T_HARDWARE                        = 0x112,
    /* maximum concurrent data sessions */
    /* type = uint16_t */
    MIPC_SYS_GET_INFO_CNF_T_MAX_ACTIVE_CTXT                 = 0x113,
    /* current protocol id */
    /* type = uint16_t */
    MIPC_SYS_GET_INFO_CNF_T_EXECUTOR_IDX                    = 0x114,
    /* custom data class name */
    /* type = string */
    MIPC_SYS_GET_INFO_CNF_T_CUSTOM_CLASS_NAME               = 0x115,
    /* product type */
    /* type = uint8_t, refer to SYS_PRODUCT_TYPE */
    MIPC_SYS_GET_INFO_CNF_T_PRODUCT_TYPE                    = 0x116,
    /* phase out, please use ESN_V1. Electronic Serial Num. Hex string type,fixed len */
    /* type = string */
    MIPC_SYS_GET_INFO_CNF_T_ESN                             = 0x8117,
    /* International Mobile Equipment Identity software version. string type, fixed len */
    /* type = string */
    MIPC_SYS_GET_INFO_CNF_T_IMEISV                          = 0x8118,
    /* phase out, please use MEID_V1. Mobile Equipment Identifier. Hex string type,fixed len */
    /* type = string */
    MIPC_SYS_GET_INFO_CNF_T_MEID                            = 0x8119,
    /* custom firmware version */
    /* type = string */
    MIPC_SYS_GET_INFO_CNF_T_FIRMWARE_CUSTOM                 = 0x11A,
    /* hardware chip id */
    /* type = byte_array */
    MIPC_SYS_GET_INFO_CNF_T_HARDWARE_ID                     = 0x11B,
    /* type = string */
    MIPC_SYS_GET_INFO_CNF_T_SERIAL_NUMBER                   = 0x11C,
    /* type = string */
    MIPC_SYS_GET_INFO_CNF_T_PROJECT_NAME                    = 0x11D,
    /* type = string */
    MIPC_SYS_GET_INFO_CNF_T_FLAVOR_NAME                     = 0x11E,
    /* Electronic Serial Num. */
    /* type = string */
    MIPC_SYS_GET_INFO_CNF_T_ESN_V1                          = 0x811F,
    /* Mobile Equipment Identifier. */
    /* type = string */
    MIPC_SYS_GET_INFO_CNF_T_MEID_V1                         = 0x8120,
    /* A bitmask that represents what cellular technology are supported */
    /* type = bitmap, refer to SYS_CAP_CELLULAR_CLASS */
    MIPC_SYS_GET_INFO_CNF_T_SYS_CELLULAR_CLASS_V1           = 0x121,
};

    /* MIPC_MSG.SYS_AT_REQ */
enum mipc_sys_at_req_tlv_enum {
    mipc_sys_at_req_tlv_NONE = 0,
    /* AT command string to execute */
    /* type = string */
    MIPC_SYS_AT_REQ_T_ATCMD                                 = 0x8100,
};

    /* MIPC_MSG.SYS_AT_CNF */
enum mipc_sys_at_cnf_tlv_enum {
    mipc_sys_at_cnf_tlv_NONE = 0,
    /* the AT command execution result */
    /* type = string */
    MIPC_SYS_AT_CNF_T_ATCMD                                 = 0x8100,
};

    /* MIPC_MSG.SYS_REBOOT_REQ */
enum mipc_sys_reboot_req_tlv_enum {
    mipc_sys_reboot_req_tlv_NONE = 0,
    /* specify the reboot mode */
    /* type = uint8_t, refer to SYS_REBOOT_MODE */
    MIPC_SYS_REBOOT_REQ_T_MODE                              = 0x100,
    /* Download Timeout (Unit: second, Only valid when MODE is DOWNLOAD or SETTIMEOUT) */
    /* type = uint32_t */
    MIPC_SYS_REBOOT_REQ_T_TIMEOUT                           = 0x101,
};

    /* MIPC_MSG.SYS_REBOOT_CNF */
enum mipc_sys_reboot_cnf_tlv_enum {
    mipc_sys_reboot_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SYS_GET_MAPPING_REQ */
enum mipc_sys_get_mapping_req_tlv_enum {
    mipc_sys_get_mapping_req_tlv_NONE = 0,
    /* type = uint8_t, refer to SYS_SIM_PS */
    MIPC_SYS_GET_MAPPING_REQ_T_MSG                          = 0x100,
};

    /* MIPC_MSG.SYS_GET_MAPPING_CNF */
enum mipc_sys_get_mapping_cnf_tlv_enum {
    mipc_sys_get_mapping_cnf_tlv_NONE = 0,
    /* the number of list element */
    /* type = uint8_t */
    MIPC_SYS_GET_MAPPING_CNF_T_MAPPING_COUNT                = 0x100,
    /* mapping list elements. each element represents a sim to ps mapping */
    /* type = struct_array, refer to sys_mapping */
    MIPC_SYS_GET_MAPPING_CNF_T_MAPPING_LIST                 = 0x101,
};

    /* MIPC_MSG.SYS_SET_MAPPING_REQ */
enum mipc_sys_set_mapping_req_tlv_enum {
    mipc_sys_set_mapping_req_tlv_NONE = 0,
    /* the number of list element */
    /* type = uint8_t */
    MIPC_SYS_SET_MAPPING_REQ_T_MAPPING_COUNT                = 0x100,
    /* mapping list elements. each element represents a sim to ps mapping */
    /* type = struct_array, refer to sys_mapping */
    MIPC_SYS_SET_MAPPING_REQ_T_MAPPING_LIST                 = 0x101,
};

    /* MIPC_MSG.SYS_SET_MAPPING_CNF */
enum mipc_sys_set_mapping_cnf_tlv_enum {
    mipc_sys_set_mapping_cnf_tlv_NONE = 0,
    /* the number of list element */
    /* type = uint8_t */
    MIPC_SYS_SET_MAPPING_CNF_T_MAPPING_COUNT                = 0x100,
    /* mapping list elements. each element represents a sim to ps mapping */
    /* type = struct_array, refer to sys_mapping */
    MIPC_SYS_SET_MAPPING_CNF_T_MAPPING_LIST                 = 0x101,
};

    /* MIPC_MSG.SYS_GET_THERMAL_SENSOR_NUM_REQ */
enum mipc_sys_get_thermal_sensor_num_req_tlv_enum {
    mipc_sys_get_thermal_sensor_num_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SYS_GET_THERMAL_SENSOR_NUM_CNF */
enum mipc_sys_get_thermal_sensor_num_cnf_tlv_enum {
    mipc_sys_get_thermal_sensor_num_cnf_tlv_NONE = 0,
    /* the number of thermal sensors */
    /* type = uint32_t */
    MIPC_SYS_GET_THERMAL_SENSOR_NUM_CNF_T_NUM               = 0x100,
};

    /* MIPC_MSG.SYS_GET_THERMAL_SENSOR_INFO_REQ */
enum mipc_sys_get_thermal_sensor_info_req_tlv_enum {
    mipc_sys_get_thermal_sensor_info_req_tlv_NONE = 0,
    /* thermal sensor ID */
    /* type = uint32_t */
    MIPC_SYS_GET_THERMAL_SENSOR_INFO_REQ_T_ID               = 0x100,
};

    /* MIPC_MSG.SYS_GET_THERMAL_SENSOR_INFO_CNF */
enum mipc_sys_get_thermal_sensor_info_cnf_tlv_enum {
    mipc_sys_get_thermal_sensor_info_cnf_tlv_NONE = 0,
    /* thermal sensor ID */
    /* type = uint32_t */
    MIPC_SYS_GET_THERMAL_SENSOR_INFO_CNF_T_ID               = 0x100,
    /* thermal sensor name */
    /* type = string */
    MIPC_SYS_GET_THERMAL_SENSOR_INFO_CNF_T_NAME             = 0x101,
    /*  */
    /* type = uint8_t */
    MIPC_SYS_GET_THERMAL_SENSOR_INFO_CNF_T_TYPE             = 0x102,
    /*  */
    /* type = uint8_t */
    MIPC_SYS_GET_THERMAL_SENSOR_INFO_CNF_T_MEAS_TYPE        = 0x103,
    /*  */
    /* type = int32_t */
    MIPC_SYS_GET_THERMAL_SENSOR_INFO_CNF_T_MIN_TEMPATURE    = 0x104,
    /*  */
    /* type = uint32_t */
    MIPC_SYS_GET_THERMAL_SENSOR_INFO_CNF_T_MAX_TEMPATURE    = 0x105,
    /*  */
    /* type = uint32_t */
    MIPC_SYS_GET_THERMAL_SENSOR_INFO_CNF_T_ACCURACY         = 0x106,
    /*  */
    /* type = uint32_t */
    MIPC_SYS_GET_THERMAL_SENSOR_INFO_CNF_T_RESOLUTION       = 0x107,
    /*  */
    /* type = int32_t */
    MIPC_SYS_GET_THERMAL_SENSOR_INFO_CNF_T_WARN_TEMPATURE   = 0x108,
    /*  */
    /* type = int32_t */
    MIPC_SYS_GET_THERMAL_SENSOR_INFO_CNF_T_HW_SHUTDOWN_TEMPERATURE = 0x109,
    /*  */
    /* type = uint32_t */
    MIPC_SYS_GET_THERMAL_SENSOR_INFO_CNF_T_MIN_SAMPLING_PERIOD = 0x10A,
};

    /* MIPC_MSG.SYS_SET_THERMAL_SENSOR_REQ */
enum mipc_sys_set_thermal_sensor_req_tlv_enum {
    mipc_sys_set_thermal_sensor_req_tlv_NONE = 0,
    /* type = uint8_t */
    MIPC_SYS_SET_THERMAL_SENSOR_REQ_T_CONFIG_COUNT          = 0x100,
    /* type = struct_array, refer to sys_thermal_sensor_config */
    MIPC_SYS_SET_THERMAL_SENSOR_REQ_T_CONFIG_LIST           = 0x101,
    /* type = struct, refer to sys_thermal_sensor_config_e */
    MIPC_SYS_SET_THERMAL_SENSOR_REQ_T_CONFIG_E              = 0x102,
};

    /* MIPC_MSG.SYS_SET_THERMAL_SENSOR_CNF */
enum mipc_sys_set_thermal_sensor_cnf_tlv_enum {
    mipc_sys_set_thermal_sensor_cnf_tlv_NONE = 0,
    /* type = uint8_t */
    MIPC_SYS_SET_THERMAL_SENSOR_CNF_T_CONFIG_COUNT          = 0x100,
    /* type = struct_array, refer to sys_thermal_sensor_config */
    MIPC_SYS_SET_THERMAL_SENSOR_CNF_T_CONFIG_LIST           = 0x101,
    /* type = struct, refer to sys_thermal_sensor_config_e */
    MIPC_SYS_SET_THERMAL_SENSOR_CNF_T_CONFIG_E              = 0x102,
};

    /* MIPC_MSG.SYS_GET_THERMAL_SENSOR_REQ */
enum mipc_sys_get_thermal_sensor_req_tlv_enum {
    mipc_sys_get_thermal_sensor_req_tlv_NONE = 0,
    /* thermal sensor ID */
    /* type = uint32_t */
    MIPC_SYS_GET_THERMAL_SENSOR_REQ_T_ID                    = 0x100,
};

    /* MIPC_MSG.SYS_GET_THERMAL_SENSOR_CNF */
enum mipc_sys_get_thermal_sensor_cnf_tlv_enum {
    mipc_sys_get_thermal_sensor_cnf_tlv_NONE = 0,
    /* type = int32_t */
    MIPC_SYS_GET_THERMAL_SENSOR_CNF_T_TEMPERATURE           = 0x100,
};

    /* MIPC_MSG.SYS_GET_THERMAL_ACTUATOR_NUM_REQ */
enum mipc_sys_get_thermal_actuator_num_req_tlv_enum {
    mipc_sys_get_thermal_actuator_num_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SYS_GET_THERMAL_ACTUATOR_NUM_CNF */
enum mipc_sys_get_thermal_actuator_num_cnf_tlv_enum {
    mipc_sys_get_thermal_actuator_num_cnf_tlv_NONE = 0,
    /* the number of thermal actuators */
    /* type = uint32_t */
    MIPC_SYS_GET_THERMAL_ACTUATOR_NUM_CNF_T_NUM             = 0x100,
};

    /* MIPC_MSG.SYS_SET_THERMAL_ACTUATOR_REQ */
enum mipc_sys_set_thermal_actuator_req_tlv_enum {
    mipc_sys_set_thermal_actuator_req_tlv_NONE = 0,
    /* the actuator ID */
    /* type = uint32_t, refer to SYS_THERMAL_ACTUATOR_ID */
    MIPC_SYS_SET_THERMAL_ACTUATOR_REQ_T_ID                  = 0x100,
    /* throttle level */
    /* type = uint32_t */
    MIPC_SYS_SET_THERMAL_ACTUATOR_REQ_T_LEVEL               = 0x101,
    /*  */
    /* type = uint32_t */
    MIPC_SYS_SET_THERMAL_ACTUATOR_REQ_T_STATE               = 0x102,
};

    /* MIPC_MSG.SYS_SET_THERMAL_ACTUATOR_CNF */
enum mipc_sys_set_thermal_actuator_cnf_tlv_enum {
    mipc_sys_set_thermal_actuator_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SYS_GET_THERMAL_ACTUATOR_INFO_REQ */
enum mipc_sys_get_thermal_actuator_info_req_tlv_enum {
    mipc_sys_get_thermal_actuator_info_req_tlv_NONE = 0,
    /* the actuator ID */
    /* type = uint32_t, refer to SYS_THERMAL_ACTUATOR_ID */
    MIPC_SYS_GET_THERMAL_ACTUATOR_INFO_REQ_T_ID             = 0x100,
};

    /* MIPC_MSG.SYS_GET_THERMAL_ACTUATOR_INFO_CNF */
enum mipc_sys_get_thermal_actuator_info_cnf_tlv_enum {
    mipc_sys_get_thermal_actuator_info_cnf_tlv_NONE = 0,
    /* the actuator ID */
    /* type = uint32_t, refer to SYS_THERMAL_ACTUATOR_ID */
    MIPC_SYS_GET_THERMAL_ACTUATOR_INFO_CNF_T_ID             = 0x100,
    /* thermal sensor name */
    /* type = string */
    MIPC_SYS_GET_THERMAL_ACTUATOR_INFO_CNF_T_NAME           = 0x101,
    /*  */
    /* type = uint32_t */
    MIPC_SYS_GET_THERMAL_ACTUATOR_INFO_CNF_T_TOTAL_LEVEL    = 0x102,
    /*  */
    /* type = uint32_t */
    MIPC_SYS_GET_THERMAL_ACTUATOR_INFO_CNF_T_CURRENT_LEVEL  = 0x103,
    /*  */
    /* type = uint32_t */
    MIPC_SYS_GET_THERMAL_ACTUATOR_INFO_CNF_T_USER_IMPACT    = 0x104,
    /*  */
    /* type = uint32_t */
    MIPC_SYS_GET_THERMAL_ACTUATOR_INFO_CNF_T_EFFICIENCY     = 0x105,
};

    /* MIPC_MSG.SYS_SET_CONFIG_REQ */
enum mipc_sys_set_config_req_tlv_enum {
    mipc_sys_set_config_req_tlv_NONE = 0,
    /* the configuration class */
    /* type = uint32_t, refer to SYS_CONFIG_CLASS */
    MIPC_SYS_SET_CONFIG_REQ_T_CLASS                         = 0x100,
    /* the string of configuration type */
    /* type = string */
    MIPC_SYS_SET_CONFIG_REQ_T_TYPE                          = 0x101,
    /* the configuration data */
    /* type = byte_array */
    MIPC_SYS_SET_CONFIG_REQ_T_DATA                          = 0x8102,
};

    /* MIPC_MSG.SYS_SET_CONFIG_CNF */
enum mipc_sys_set_config_cnf_tlv_enum {
    mipc_sys_set_config_cnf_tlv_NONE = 0,
    /* the response data */
    /* type = byte_array */
    MIPC_SYS_SET_CONFIG_CNF_T_DATA                          = 0x8100,
};

    /* MIPC_MSG.SYS_GET_CONFIG_REQ */
enum mipc_sys_get_config_req_tlv_enum {
    mipc_sys_get_config_req_tlv_NONE = 0,
    /* the configuration class */
    /* type = uint32_t, refer to SYS_CONFIG_CLASS */
    MIPC_SYS_GET_CONFIG_REQ_T_CLASS                         = 0x100,
    /* the string of configuration type */
    /* type = string */
    MIPC_SYS_GET_CONFIG_REQ_T_TYPE                          = 0x101,
};

    /* MIPC_MSG.SYS_GET_CONFIG_CNF */
enum mipc_sys_get_config_cnf_tlv_enum {
    mipc_sys_get_config_cnf_tlv_NONE = 0,
    /* the response data */
    /* type = byte_array */
    MIPC_SYS_GET_CONFIG_CNF_T_DATA                          = 0x8100,
};

    /* MIPC_MSG.SYS_REG_CONFIG_REQ */
enum mipc_sys_reg_config_req_tlv_enum {
    mipc_sys_reg_config_req_tlv_NONE = 0,
    /* the configuration class */
    /* type = uint32_t, refer to SYS_CONFIG_CLASS */
    MIPC_SYS_REG_CONFIG_REQ_T_CLASS                         = 0x100,
    /* the string of configuration type */
    /* type = string */
    MIPC_SYS_REG_CONFIG_REQ_T_TYPE                          = 0x101,
};

    /* MIPC_MSG.SYS_REG_CONFIG_CNF */
enum mipc_sys_reg_config_cnf_tlv_enum {
    mipc_sys_reg_config_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SYS_SET_ADPCLK_REQ */
enum mipc_sys_set_adpclk_req_tlv_enum {
    mipc_sys_set_adpclk_req_tlv_NONE = 0,
    /* enable or disable */
    /* type = uint8_t, refer to SYS_ADPCLK_STATE */
    MIPC_SYS_SET_ADPCLK_REQ_T_STATE                         = 0x100,
};

    /* MIPC_MSG.SYS_SET_ADPCLK_CNF */
enum mipc_sys_set_adpclk_cnf_tlv_enum {
    mipc_sys_set_adpclk_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SYS_GET_ADPCLK_REQ */
enum mipc_sys_get_adpclk_req_tlv_enum {
    mipc_sys_get_adpclk_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SYS_GET_ADPCLK_CNF */
enum mipc_sys_get_adpclk_cnf_tlv_enum {
    mipc_sys_get_adpclk_cnf_tlv_NONE = 0,
    /* type = uint8_t */
    MIPC_SYS_GET_ADPCLK_CNF_T_FREQ_INFO_COUNT               = 0x100,
    /* type = struct_array, refer to sys_adpclk_freq_info */
    MIPC_SYS_GET_ADPCLK_CNF_T_FREQ_INFO_LIST                = 0x101,
};

    /* MIPC_MSG.SYS_SET_MD_LOG_MODE_REQ */
enum mipc_sys_set_md_log_mode_req_tlv_enum {
    mipc_sys_set_md_log_mode_req_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_SYS_SET_MD_LOG_MODE_REQ_T_MODE                     = 0x100,
};

    /* MIPC_MSG.SYS_SET_MD_LOG_MODE_CNF */
enum mipc_sys_set_md_log_mode_cnf_tlv_enum {
    mipc_sys_set_md_log_mode_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SYS_GET_MD_LOG_MODE_REQ */
enum mipc_sys_get_md_log_mode_req_tlv_enum {
    mipc_sys_get_md_log_mode_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SYS_GET_MD_LOG_MODE_CNF */
enum mipc_sys_get_md_log_mode_cnf_tlv_enum {
    mipc_sys_get_md_log_mode_cnf_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_SYS_GET_MD_LOG_MODE_CNF_T_MODE                     = 0x100,
};

    /* MIPC_MSG.SYS_SET_MD_LOG_LEVEL_REQ */
enum mipc_sys_set_md_log_level_req_tlv_enum {
    mipc_sys_set_md_log_level_req_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_SYS_SET_MD_LOG_LEVEL_REQ_T_LEVEL                   = 0x100,
};

    /* MIPC_MSG.SYS_SET_MD_LOG_LEVEL_CNF */
enum mipc_sys_set_md_log_level_cnf_tlv_enum {
    mipc_sys_set_md_log_level_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SYS_GET_MD_LOG_LEVEL_REQ */
enum mipc_sys_get_md_log_level_req_tlv_enum {
    mipc_sys_get_md_log_level_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SYS_GET_MD_LOG_LEVEL_CNF */
enum mipc_sys_get_md_log_level_cnf_tlv_enum {
    mipc_sys_get_md_log_level_cnf_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_SYS_GET_MD_LOG_LEVEL_CNF_T_LEVEL                   = 0x100,
};

    /* MIPC_MSG.SYS_SET_MD_LOG_LOCATION_REQ */
enum mipc_sys_set_md_log_location_req_tlv_enum {
    mipc_sys_set_md_log_location_req_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_SYS_SET_MD_LOG_LOCATION_REQ_T_ENABLE               = 0x100,
};

    /* MIPC_MSG.SYS_SET_MD_LOG_LOCATION_CNF */
enum mipc_sys_set_md_log_location_cnf_tlv_enum {
    mipc_sys_set_md_log_location_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SYS_GET_MD_LOG_LOCATION_REQ */
enum mipc_sys_get_md_log_location_req_tlv_enum {
    mipc_sys_get_md_log_location_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SYS_GET_MD_LOG_LOCATION_CNF */
enum mipc_sys_get_md_log_location_cnf_tlv_enum {
    mipc_sys_get_md_log_location_cnf_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_SYS_GET_MD_LOG_LOCATION_CNF_T_ENABLE               = 0x100,
};

    /* MIPC_MSG.SYS_WRITE_NVRAM_REQ */
enum mipc_sys_write_nvram_req_tlv_enum {
    mipc_sys_write_nvram_req_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_SYS_WRITE_NVRAM_REQ_T_FILE_IDX                     = 0x100,
    /* type = uint32_t */
    MIPC_SYS_WRITE_NVRAM_REQ_T_RECORD_IDX                   = 0x101,
    /* type = byte_array */
    MIPC_SYS_WRITE_NVRAM_REQ_T_DATA                         = 0x8102,
};

    /* MIPC_MSG.SYS_WRITE_NVRAM_CNF */
enum mipc_sys_write_nvram_cnf_tlv_enum {
    mipc_sys_write_nvram_cnf_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_SYS_WRITE_NVRAM_CNF_T_DATA_LEN                     = 0x100,
};

    /* MIPC_MSG.SYS_READ_NVRAM_REQ */
enum mipc_sys_read_nvram_req_tlv_enum {
    mipc_sys_read_nvram_req_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_SYS_READ_NVRAM_REQ_T_FILE_IDX                      = 0x100,
    /* type = uint32_t */
    MIPC_SYS_READ_NVRAM_REQ_T_RECORD_IDX                    = 0x101,
};

    /* MIPC_MSG.SYS_READ_NVRAM_CNF */
enum mipc_sys_read_nvram_cnf_tlv_enum {
    mipc_sys_read_nvram_cnf_tlv_NONE = 0,
    /* type = byte_array */
    MIPC_SYS_READ_NVRAM_CNF_T_DATA                          = 0x8100,
};

    /* MIPC_MSG.SYS_AUTH_REQ */
enum mipc_sys_auth_req_tlv_enum {
    mipc_sys_auth_req_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_SYS_AUTH_REQ_T_OP                                  = 0x100,
    /* type = byte_array */
    MIPC_SYS_AUTH_REQ_T_ENCDATA                             = 0x8101,
};

    /* MIPC_MSG.SYS_AUTH_CNF */
enum mipc_sys_auth_cnf_tlv_enum {
    mipc_sys_auth_cnf_tlv_NONE = 0,
    /* type = byte_array */
    MIPC_SYS_AUTH_CNF_T_RAND                                = 0x8100,
};

    /* MIPC_MSG.SYS_SET_DAT_REQ */
enum mipc_sys_set_dat_req_tlv_enum {
    mipc_sys_set_dat_req_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_SYS_SET_DAT_REQ_T_INDEX                            = 0x100,
};

    /* MIPC_MSG.SYS_SET_DAT_CNF */
enum mipc_sys_set_dat_cnf_tlv_enum {
    mipc_sys_set_dat_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SYS_GET_DAT_REQ */
enum mipc_sys_get_dat_req_tlv_enum {
    mipc_sys_get_dat_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SYS_GET_DAT_CNF */
enum mipc_sys_get_dat_cnf_tlv_enum {
    mipc_sys_get_dat_cnf_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_SYS_GET_DAT_CNF_T_INDEX                            = 0x100,
};

    /* MIPC_MSG.SYS_MCF_REQ */
enum mipc_sys_mcf_req_tlv_enum {
    mipc_sys_mcf_req_tlv_NONE = 0,
    /* type = uint8_t, refer to SYS_MCF_OP */
    MIPC_SYS_MCF_REQ_T_OP                                   = 0x10A,
    /* type = uint8_t */
    MIPC_SYS_MCF_REQ_T_CONFIG_TYPE                          = 0x10B,
    /* type = string */
    MIPC_SYS_MCF_REQ_T_DUMP_LIDS                            = 0x10C,
    /* type = uint8_t */
    MIPC_SYS_MCF_REQ_T_PATH_TYPE                            = 0x10D,
    /* type = uint8_t */
    MIPC_SYS_MCF_REQ_T_TRIGGER_DSBP                         = 0x10E,
    /* type = uint8_t */
    MIPC_SYS_MCF_REQ_T_ACTION                               = 0x10F,
    /* type = uint8_t */
    MIPC_SYS_MCF_REQ_T_FORMAT                               = 0x110,
    /* type = uint32_t */
    MIPC_SYS_MCF_REQ_T_NUM                                  = 0x111,
    /* type = uint8_t */
    MIPC_SYS_MCF_REQ_T_LEN                                  = 0x112,
    /* type = uint16_t */
    MIPC_SYS_MCF_REQ_T_REC_ID                               = 0x113,
    /* type = byte_array */
    MIPC_SYS_MCF_REQ_T_VALUE                                = 0x114,
    /* type = string */
    MIPC_SYS_MCF_REQ_T_CONFIG1                              = 0x115,
    /* type = string */
    MIPC_SYS_MCF_REQ_T_CONFIG                               = 0x116,
    /* type = uint8_t */
    MIPC_SYS_MCF_REQ_T_IS_RESET                             = 0x117,
};

    /* MIPC_MSG.SYS_MCF_CNF */
enum mipc_sys_mcf_cnf_tlv_enum {
    mipc_sys_mcf_cnf_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_SYS_MCF_CNF_T_MCF_RESULT                           = 0x100,
    /* type = uint32_t */
    MIPC_SYS_MCF_CNF_T_DSBP_RESULT                          = 0x101,
    /* type = uint8_t, refer to SYS_MCF_OP */
    MIPC_SYS_MCF_CNF_T_OP                                   = 0x10A,
    /* type = uint8_t */
    MIPC_SYS_MCF_CNF_T_CONFIG_TYPE                          = 0x10B,
    /* type = uint8_t */
    MIPC_SYS_MCF_CNF_T_PATH_TYPE                            = 0x10D,
    /* type = uint8_t */
    MIPC_SYS_MCF_CNF_T_ACTION                               = 0x10F,
    /* type = uint8_t */
    MIPC_SYS_MCF_CNF_T_FORMAT                               = 0x110,
    /* type = uint8_t */
    MIPC_SYS_MCF_CNF_T_LEN                                  = 0x112,
    /* type = byte_array */
    MIPC_SYS_MCF_CNF_T_VALUE                                = 0x114,
    /* type = string */
    MIPC_SYS_MCF_CNF_T_CONFIG1                              = 0x115,
};

    /* MIPC_MSG.SYS_SET_FCC_LOCK_REQ */
enum mipc_sys_set_fcc_lock_req_tlv_enum {
    mipc_sys_set_fcc_lock_req_tlv_NONE = 0,
    /* type = uint8_t */
    MIPC_SYS_SET_FCC_LOCK_REQ_T_MODE                        = 0x100,
};

    /* MIPC_MSG.SYS_SET_FCC_LOCK_CNF */
enum mipc_sys_set_fcc_lock_cnf_tlv_enum {
    mipc_sys_set_fcc_lock_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SYS_SET_TIME_REQ */
enum mipc_sys_set_time_req_tlv_enum {
    mipc_sys_set_time_req_tlv_NONE = 0,
    /* year */
    /* type = uint32_t */
    MIPC_SYS_SET_TIME_REQ_T_YEAR                            = 0x100,
    /* month */
    /* type = uint32_t */
    MIPC_SYS_SET_TIME_REQ_T_MONTH                           = 0x101,
    /* day */
    /* type = uint32_t */
    MIPC_SYS_SET_TIME_REQ_T_DAY                             = 0x102,
    /* hour */
    /* type = uint32_t */
    MIPC_SYS_SET_TIME_REQ_T_HOUR                            = 0x103,
    /* minute */
    /* type = uint32_t */
    MIPC_SYS_SET_TIME_REQ_T_MINUTE                          = 0x104,
    /* second */
    /* type = uint32_t */
    MIPC_SYS_SET_TIME_REQ_T_SECOND                          = 0x105,
};

    /* MIPC_MSG.SYS_SET_TIME_CNF */
enum mipc_sys_set_time_cnf_tlv_enum {
    mipc_sys_set_time_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SYS_GET_TIME_REQ */
enum mipc_sys_get_time_req_tlv_enum {
    mipc_sys_get_time_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SYS_GET_TIME_CNF */
enum mipc_sys_get_time_cnf_tlv_enum {
    mipc_sys_get_time_cnf_tlv_NONE = 0,
    /* year */
    /* type = uint32_t */
    MIPC_SYS_GET_TIME_CNF_T_YEAR                            = 0x100,
    /* month */
    /* type = uint32_t */
    MIPC_SYS_GET_TIME_CNF_T_MONTH                           = 0x101,
    /* day */
    /* type = uint32_t */
    MIPC_SYS_GET_TIME_CNF_T_DAY                             = 0x102,
    /* hour */
    /* type = uint32_t */
    MIPC_SYS_GET_TIME_CNF_T_HOUR                            = 0x103,
    /* minute */
    /* type = uint32_t */
    MIPC_SYS_GET_TIME_CNF_T_MINUTE                          = 0x104,
    /* second */
    /* type = uint32_t */
    MIPC_SYS_GET_TIME_CNF_T_SECOND                          = 0x105,
    /* timestamp (FRC) */
    /* type = uint32_t */
    MIPC_SYS_GET_TIME_CNF_T_TIMESTAMP                       = 0x106,
};

    /* MIPC_MSG.SYS_SET_SAR_REQ */
enum mipc_sys_set_sar_req_tlv_enum {
    mipc_sys_set_sar_req_tlv_NONE = 0,
    /* type = uint8_t, refer to SYS_SAR_MODE */
    MIPC_SYS_SET_SAR_REQ_T_MODE                             = 0x100,
    /* type = uint32_t */
    MIPC_SYS_SET_SAR_REQ_T_INDEX                            = 0x101,
};

    /* MIPC_MSG.SYS_SET_SAR_CNF */
enum mipc_sys_set_sar_cnf_tlv_enum {
    mipc_sys_set_sar_cnf_tlv_NONE = 0,
    /* type = uint8_t, refer to SYS_SAR_MODE */
    MIPC_SYS_SET_SAR_CNF_T_MODE                             = 0x100,
    /* type = uint32_t */
    MIPC_SYS_SET_SAR_CNF_T_INDEX                            = 0x101,
};

    /* MIPC_MSG.SYS_GET_SAR_REQ */
enum mipc_sys_get_sar_req_tlv_enum {
    mipc_sys_get_sar_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SYS_GET_SAR_CNF */
enum mipc_sys_get_sar_cnf_tlv_enum {
    mipc_sys_get_sar_cnf_tlv_NONE = 0,
    /* type = uint8_t, refer to SYS_SAR_MODE */
    MIPC_SYS_GET_SAR_CNF_T_MODE                             = 0x100,
    /* type = uint32_t */
    MIPC_SYS_GET_SAR_CNF_T_INDEX                            = 0x101,
};

    /* MIPC_MSG.SYS_SET_POWER_SAVING_REQ */
enum mipc_sys_set_power_saving_req_tlv_enum {
    mipc_sys_set_power_saving_req_tlv_NONE = 0,
    /* 0: disable, 1: enable */
    /* type = uint8_t */
    MIPC_SYS_SET_POWER_SAVING_REQ_T_MODE                    = 0x100,
};

    /* MIPC_MSG.SYS_SET_POWER_SAVING_CNF */
enum mipc_sys_set_power_saving_cnf_tlv_enum {
    mipc_sys_set_power_saving_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SYS_CONNECTIVITY_STATISTICS_REQ */
enum mipc_sys_connectivity_statistics_req_tlv_enum {
    mipc_sys_connectivity_statistics_req_tlv_NONE = 0,
    /* once HOST carry this TLV(no matter what value), means HOST need read statistic info & period(s), DEVICE would carry the info in CNF */
    /* type = uint8_t */
    MIPC_SYS_CONNECTIVITY_STATISTICS_REQ_T_READ_FLAG        = 0x100,
    /* once HOST carry this TLV(no matter what value), means HOST need trigger reset statistic counters, then start statistic, DEVICE would stop statistic until period expired(none 0) or receive STOP from HOST */
    /* type = uint8_t */
    MIPC_SYS_CONNECTIVITY_STATISTICS_REQ_T_START            = 0x101,
    /* once HOST carry this TLV(no matter what value), means DEVICE should stop statistic now, but dont reset the counters */
    /* type = uint8_t */
    MIPC_SYS_CONNECTIVITY_STATISTICS_REQ_T_STOP             = 0x102,
    /* once HOST carry this TLV, means DEVICE should set the PERIOD(uint:second; max value is 86400) */
    /* type = uint32_t */
    MIPC_SYS_CONNECTIVITY_STATISTICS_REQ_T_PERIOD_VALUE     = 0x103,
};

    /* MIPC_MSG.SYS_CONNECTIVITY_STATISTICS_CNF */
enum mipc_sys_connectivity_statistics_cnf_tlv_enum {
    mipc_sys_connectivity_statistics_cnf_tlv_NONE = 0,
    /* indicate the total number of SMS successfully transmitted during the collection period */
    /* type = uint32_t */
    MIPC_SYS_CONNECTIVITY_STATISTICS_CNF_T_SMS_TX_COUNTER   = 0x100,
    /* indicate the total number of SMS successfully received during the collection period */
    /* type = uint32_t */
    MIPC_SYS_CONNECTIVITY_STATISTICS_CNF_T_SMS_RX_COUNTER   = 0x101,
    /* Indicate the total amount of data (IP / non-IP) transmitted during the collection period expressed in kilobytes */
    /* type = uint32_t */
    MIPC_SYS_CONNECTIVITY_STATISTICS_CNF_T_TX_DATA          = 0x102,
    /* Indicate the total amount of data (IP / non-IP) received during the collection period expressed in kilobytes */
    /* type = uint32_t */
    MIPC_SYS_CONNECTIVITY_STATISTICS_CNF_T_RX_DATA          = 0x103,
    /* The maximum IP message size that is used during the collection period(uint: B) */
    /* type = uint32_t */
    MIPC_SYS_CONNECTIVITY_STATISTICS_CNF_T_MAX_MESSAGE_SIZE = 0x104,
    /* The average IP message size that is used during the collection period(uint: B) */
    /* type = uint32_t */
    MIPC_SYS_CONNECTIVITY_STATISTICS_CNF_T_AVERAGE_MESSAGE_SIZE = 0x105,
    /* the period that set before, uint:second */
    /* type = uint32_t */
    MIPC_SYS_CONNECTIVITY_STATISTICS_CNF_T_PERIOD_VALUE     = 0x106,
};

    /* MIPC_MSG.SYS_QUERY_SBP_REQ */
enum mipc_sys_query_sbp_req_tlv_enum {
    mipc_sys_query_sbp_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SYS_QUERY_SBP_CNF */
enum mipc_sys_query_sbp_cnf_tlv_enum {
    mipc_sys_query_sbp_cnf_tlv_NONE = 0,
    /* device sbp id */
    /* type = uint32_t */
    MIPC_SYS_QUERY_SBP_CNF_T_SBP_ID                         = 0x100,
    /* type = uint32_t */
    MIPC_SYS_QUERY_SBP_CNF_T_SIM_SBP_ID                     = 0x101,
    /* type = string */
    MIPC_SYS_QUERY_SBP_CNF_T_SBP_FEATURE_BYTE               = 0x102,
    /* type = string */
    MIPC_SYS_QUERY_SBP_CNF_T_SBP_DATA_BYTE                  = 0x103,
};

    /* MIPC_MSG.SYS_SET_GEO_LOCATION_REQ */
enum mipc_sys_set_geo_location_req_tlv_enum {
    mipc_sys_set_geo_location_req_tlv_NONE = 0,
    /* request id, 0 ~ 7 */
    /* type = uint8_t, refer to SYS_ACCOUNT_ID */
    MIPC_SYS_SET_GEO_LOCATION_REQ_T_ACCOUNT_ID              = 0x100,
    /* 0: Do not broadcast this information to all IMS accounts. 1: Broadcast this information to all IMS accounts */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_SYS_SET_GEO_LOCATION_REQ_T_BROADCAST_FLAG          = 0x101,
    /* latitude from GPS, 0 as failed */
    /* type = string */
    MIPC_SYS_SET_GEO_LOCATION_REQ_T_LATITUDE                = 0x102,
    /* longitude from GPS, 0 as failed */
    /* type = string */
    MIPC_SYS_SET_GEO_LOCATION_REQ_T_LONGITUDE               = 0x103,
    /* accurate from GPS, 0 as failed */
    /* type = string */
    MIPC_SYS_SET_GEO_LOCATION_REQ_T_ACCURACY                = 0x104,
    /* Positioning method */
    /* type = string */
    MIPC_SYS_SET_GEO_LOCATION_REQ_T_METHOD                  = 0x105,
    /* type = string */
    MIPC_SYS_SET_GEO_LOCATION_REQ_T_CITY                    = 0x106,
    /* type = string */
    MIPC_SYS_SET_GEO_LOCATION_REQ_T_STATE                   = 0x107,
    /* Zip code */
    /* type = string */
    MIPC_SYS_SET_GEO_LOCATION_REQ_T_ZIP                     = 0x108,
    /* Two-letter country code defined by ISO 3166-1 */
    /* type = string */
    MIPC_SYS_SET_GEO_LOCATION_REQ_T_COUNTRY_CODE            = 0x109,
    /* UE Wi-Fi interface mac address */
    /* type = string */
    MIPC_SYS_SET_GEO_LOCATION_REQ_T_UE_WLAN_MAC             = 0x10A,
    /* confidence */
    /* type = uint32_t */
    MIPC_SYS_SET_GEO_LOCATION_REQ_T_CONFIDENCE              = 0x10B,
    /* altitude */
    /* type = string */
    MIPC_SYS_SET_GEO_LOCATION_REQ_T_ALTITUDE                = 0x10C,
    /* accuracy semi Major Axis */
    /* type = string */
    MIPC_SYS_SET_GEO_LOCATION_REQ_T_ACCURACY_SEMI_MAJOR_AXIS = 0x10D,
    /* accuracy semi Minor Axis */
    /* type = string */
    MIPC_SYS_SET_GEO_LOCATION_REQ_T_ACCURACY_SEMI_MINOR_AXIS = 0x10E,
    /* accuracy vertical Axis */
    /* type = string */
    MIPC_SYS_SET_GEO_LOCATION_REQ_T_ACCURACY_VERTICAL_AXIS  = 0x10F,
};

    /* MIPC_MSG.SYS_SET_GEO_LOCATION_CNF */
enum mipc_sys_set_geo_location_cnf_tlv_enum {
    mipc_sys_set_geo_location_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SYS_SET_DSBP_REQ */
enum mipc_sys_set_dsbp_req_tlv_enum {
    mipc_sys_set_dsbp_req_tlv_NONE = 0,
    /* dynamic sbp mode */
    /* type = uint8_t, refer to SYS_DSBP_MODE */
    MIPC_SYS_SET_DSBP_REQ_T_MODE                            = 0x100,
};

    /* MIPC_MSG.SYS_SET_DSBP_CNF */
enum mipc_sys_set_dsbp_cnf_tlv_enum {
    mipc_sys_set_dsbp_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SYS_SEND_SAR_IND_REQ */
enum mipc_sys_send_sar_ind_req_tlv_enum {
    mipc_sys_send_sar_ind_req_tlv_NONE = 0,
    /* sar commond type, 0 or 1 */
    /* type = uint8_t */
    MIPC_SYS_SEND_SAR_IND_REQ_T_CMD_TYPE                    = 0x100,
    /* commond parameter */
    /* type = string */
    MIPC_SYS_SEND_SAR_IND_REQ_T_CMD_PARAM                   = 0x101,
};

    /* MIPC_MSG.SYS_SEND_SAR_IND_CNF */
enum mipc_sys_send_sar_ind_cnf_tlv_enum {
    mipc_sys_send_sar_ind_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SYS_SILENT_REBOOT_REQ */
enum mipc_sys_silent_reboot_req_tlv_enum {
    mipc_sys_silent_reboot_req_tlv_NONE = 0,
    /* 0 means normal mode(default mode), 1 means silent reboot. when silent reboot, MD will use the verified sim pin to auto verify sim pin */
    /* type = uint8_t */
    MIPC_SYS_SILENT_REBOOT_REQ_T_MODE                       = 0x100,
};

    /* MIPC_MSG.SYS_SILENT_REBOOT_CNF */
enum mipc_sys_silent_reboot_cnf_tlv_enum {
    mipc_sys_silent_reboot_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SYS_MULTI_SIM_CONFIG_REQ */
enum mipc_sys_multi_sim_config_req_tlv_enum {
    mipc_sys_multi_sim_config_req_tlv_NONE = 0,
    /* 1 means single sim mode,2 dual sim mode */
    /* type = uint8_t */
    MIPC_SYS_MULTI_SIM_CONFIG_REQ_T_MODE                    = 0x101,
};

    /* MIPC_MSG.SYS_MULTI_SIM_CONFIG_CNF */
enum mipc_sys_multi_sim_config_cnf_tlv_enum {
    mipc_sys_multi_sim_config_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SYS_REBOOT_SET_REQ */
enum mipc_sys_reboot_set_req_tlv_enum {
    mipc_sys_reboot_set_req_tlv_NONE = 0,
    /* 0 means normal mode, 1means silent reboot, default is 0 */
    /* type = uint8_t */
    MIPC_SYS_REBOOT_SET_REQ_T_MODE                          = 0x100,
};

    /* MIPC_MSG.SYS_REBOOT_SET_CNF */
enum mipc_sys_reboot_set_cnf_tlv_enum {
    mipc_sys_reboot_set_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SYS_GET_THERMAL_ACTUATOR_REQ */
enum mipc_sys_get_thermal_actuator_req_tlv_enum {
    mipc_sys_get_thermal_actuator_req_tlv_NONE = 0,
    /*  */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_SYS_GET_THERMAL_ACTUATOR_REQ_T_GET_ACTUATOR_NUM    = 0x100,
    /* actuator_id_to_get_actuator_info */
    /* type = uint32_t, refer to SYS_THERMAL_ACTUATOR_ID */
    MIPC_SYS_GET_THERMAL_ACTUATOR_REQ_T_ACTUATOR_ID         = 0x101,
};

    /* MIPC_MSG.SYS_GET_THERMAL_ACTUATOR_CNF */
enum mipc_sys_get_thermal_actuator_cnf_tlv_enum {
    mipc_sys_get_thermal_actuator_cnf_tlv_NONE = 0,
    /* actuator_num */
    /* type = uint32_t */
    MIPC_SYS_GET_THERMAL_ACTUATOR_CNF_T_ACTUATOR_NUM        = 0x100,
    /* actuator_state_info */
    /* type = struct, refer to sys_thermal_actuator_state_info */
    MIPC_SYS_GET_THERMAL_ACTUATOR_CNF_T_ACTUATOR_STATE_INFO = 0x101,
};

    /* MIPC_MSG.SYS_GET_THERMAL_SENSOR_RUNTIME_REQ */
enum mipc_sys_get_thermal_sensor_runtime_req_tlv_enum {
    mipc_sys_get_thermal_sensor_runtime_req_tlv_NONE = 0,
    /*  */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_SYS_GET_THERMAL_SENSOR_RUNTIME_REQ_T_GET_MD_AUTO_ENABLE = 0x100,
    /* sensor_id_to_get_trip_point */
    /* type = uint32_t */
    MIPC_SYS_GET_THERMAL_SENSOR_RUNTIME_REQ_T_SENSOR_ID     = 0x101,
};

    /* MIPC_MSG.SYS_GET_THERMAL_SENSOR_RUNTIME_CNF */
enum mipc_sys_get_thermal_sensor_runtime_cnf_tlv_enum {
    mipc_sys_get_thermal_sensor_runtime_cnf_tlv_NONE = 0,
    /*  */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_SYS_GET_THERMAL_SENSOR_RUNTIME_CNF_T_MD_AUTO_ENABLE = 0x100,
    /* trip maps */
    /* type = struct, refer to sys_thermal_trip_map */
    MIPC_SYS_GET_THERMAL_SENSOR_RUNTIME_CNF_T_TRIP          = 0x101,
};

    /* MIPC_MSG.SYS_SET_THERMAL_RUNTIME_REQ */
enum mipc_sys_set_thermal_runtime_req_tlv_enum {
    mipc_sys_set_thermal_runtime_req_tlv_NONE = 0,
    /*  */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_SYS_SET_THERMAL_RUNTIME_REQ_T_RESET_CFG_FROM_NV    = 0x100,
    /*  */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_SYS_SET_THERMAL_RUNTIME_REQ_T_MD_AUTO_ENABLE       = 0x101,
    /*  */
    /* type = struct, refer to sys_thermal_trip_change */
    MIPC_SYS_SET_THERMAL_RUNTIME_REQ_T_TRIP_CHANGE          = 0x102,
    /*  */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_SYS_SET_THERMAL_RUNTIME_REQ_T_SAVE_CFG_TO_NV       = 0x103,
};

    /* MIPC_MSG.SYS_SET_THERMAL_RUNTIME_CNF */
enum mipc_sys_set_thermal_runtime_cnf_tlv_enum {
    mipc_sys_set_thermal_runtime_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SYS_SET_OR_GET_SBP_INFO_REQ */
enum mipc_sys_set_or_get_sbp_info_req_tlv_enum {
    mipc_sys_set_or_get_sbp_info_req_tlv_NONE = 0,
    /* mode of SBP */
    /* type = uint8_t, refer to SYS_SBP_MODE */
    MIPC_SYS_SET_OR_GET_SBP_INFO_REQ_T_MODE                 = 0x100,
    /* <feature> is identified by integer value */
    /* type = uint32_t */
    MIPC_SYS_SET_OR_GET_SBP_INFO_REQ_T_FEATURE_INT          = 0x101,
    /* <feature> is identified by name string */
    /* type = string */
    MIPC_SYS_SET_OR_GET_SBP_INFO_REQ_T_FEATURE_STR          = 0x102,
    /* SBP feature data or config. Interger between 0 ~ 255 */
    /* type = uint8_t */
    MIPC_SYS_SET_OR_GET_SBP_INFO_REQ_T_DATA                 = 0x103,
    /* param will only get/set for current protocal stack. Without special param, the get/set feature/data will be applied for all protocol stack. */
    /* type = uint8_t */
    MIPC_SYS_SET_OR_GET_SBP_INFO_REQ_T_PARAM                = 0x104,
};

    /* MIPC_MSG.SYS_SET_OR_GET_SBP_INFO_CNF */
enum mipc_sys_set_or_get_sbp_info_cnf_tlv_enum {
    mipc_sys_set_or_get_sbp_info_cnf_tlv_NONE = 0,
    /* Interger between 0 ~ 255 */
    /* type = uint8_t */
    MIPC_SYS_SET_OR_GET_SBP_INFO_CNF_T_DATA                 = 0x100,
};

    /* MIPC_MSG.SYS_GET_ALL_THERMAL_INFO_REQ */
enum mipc_sys_get_all_thermal_info_req_tlv_enum {
    mipc_sys_get_all_thermal_info_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SYS_GET_ALL_THERMAL_INFO_CNF */
enum mipc_sys_get_all_thermal_info_cnf_tlv_enum {
    mipc_sys_get_all_thermal_info_cnf_tlv_NONE = 0,
    /*  */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_SYS_GET_ALL_THERMAL_INFO_CNF_T_AUTO_FLAG           = 0x101,
    /* information of thermal sensor */
    /* type = struct, refer to sys_thermal_sensor_info_e */
    MIPC_SYS_GET_ALL_THERMAL_INFO_CNF_T_THERMAL_TEMP_INFO   = 0x102,
    /* information of thermal actuator */
    /* type = struct, refer to sys_thermal_actuator_state_info */
    MIPC_SYS_GET_ALL_THERMAL_INFO_CNF_T_ACTUATOR_STATE_INFO = 0x103,
};

    /* MIPC_MSG.APN_SET_IA_REQ */
enum mipc_apn_set_ia_req_tlv_enum {
    mipc_apn_set_ia_req_tlv_NONE = 0,
    /* APN name */
    /* type = string */
    MIPC_APN_SET_IA_REQ_T_APN                               = 0x101,
    /* pdp type */
    /* type = uint8_t, refer to APN_PDP_TYPE */
    MIPC_APN_SET_IA_REQ_T_PDP_TYPE                          = 0x102,
    /* roaming type */
    /* type = uint8_t, refer to APN_PDP_TYPE */
    MIPC_APN_SET_IA_REQ_T_ROAMING_TYPE                      = 0x103,
    /* auth type */
    /* type = uint8_t, refer to APN_AUTH_TYPE */
    MIPC_APN_SET_IA_REQ_T_AUTH_TYPE                         = 0x104,
    /* user name */
    /* type = string */
    MIPC_APN_SET_IA_REQ_T_USERID                            = 0x8105,
    /* password */
    /* type = string */
    MIPC_APN_SET_IA_REQ_T_PASSWORD                          = 0x8106,
    /* bearer bit mask */
    /* type = uint32_t */
    MIPC_APN_SET_IA_REQ_T_BEARER_BITMASK                    = 0x107,
    /* compression config */
    /* type = uint8_t, refer to APN_COMPRESSION */
    MIPC_APN_SET_IA_REQ_T_COMPRESSION                       = 0x108,
};

    /* MIPC_MSG.APN_SET_IA_CNF */
enum mipc_apn_set_ia_cnf_tlv_enum {
    mipc_apn_set_ia_cnf_tlv_NONE = 0,
    /* the number of IA APN */
    /* type = uint8_t */
    MIPC_APN_SET_IA_CNF_T_IA_COUNT                          = 0x100,
    /* the list of IA APN */
    /* type = struct_array, refer to apn_ia */
    MIPC_APN_SET_IA_CNF_T_IA_LIST                           = 0x8101,
};

    /* MIPC_MSG.APN_GET_IA_REQ */
enum mipc_apn_get_ia_req_tlv_enum {
    mipc_apn_get_ia_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.APN_GET_IA_CNF */
enum mipc_apn_get_ia_cnf_tlv_enum {
    mipc_apn_get_ia_cnf_tlv_NONE = 0,
    /* the number of IA APN */
    /* type = uint8_t */
    MIPC_APN_GET_IA_CNF_T_IA_COUNT                          = 0x100,
    /* the list of IA APN */
    /* type = struct_array, refer to apn_ia */
    MIPC_APN_GET_IA_CNF_T_IA_LIST                           = 0x8101,
};

    /* MIPC_MSG.APN_ADD_PROFILE_REQ */
enum mipc_apn_add_profile_req_tlv_enum {
    mipc_apn_add_profile_req_tlv_NONE = 0,
    /* the ID of APN profile */
    /* type = uint32_t */
    MIPC_APN_ADD_PROFILE_REQ_T_ID                           = 0x101,
    /* plmn of operator NW */
    /* type = string */
    MIPC_APN_ADD_PROFILE_REQ_T_PLMN_ID                      = 0x102,
    /* apn name */
    /* type = string */
    MIPC_APN_ADD_PROFILE_REQ_T_APN                          = 0x103,
    /* apn type */
    /* type = uint32_t, refer to APN_TYPE */
    MIPC_APN_ADD_PROFILE_REQ_T_APN_TYPE                     = 0x104,
    /* pdp type */
    /* type = uint8_t, refer to APN_PDP_TYPE */
    MIPC_APN_ADD_PROFILE_REQ_T_PDP_TYPE                     = 0x105,
    /* roaming type */
    /* type = uint8_t, refer to APN_PDP_TYPE */
    MIPC_APN_ADD_PROFILE_REQ_T_ROAMING_TYPE                 = 0x106,
    /* auth type */
    /* type = uint8_t, refer to APN_AUTH_TYPE */
    MIPC_APN_ADD_PROFILE_REQ_T_AUTH_TYPE                    = 0x107,
    /* user name */
    /* type = string */
    MIPC_APN_ADD_PROFILE_REQ_T_USERID                       = 0x8108,
    /* password */
    /* type = string */
    MIPC_APN_ADD_PROFILE_REQ_T_PASSWORD                     = 0x8109,
    /* bearer bitmask */
    /* type = uint32_t */
    MIPC_APN_ADD_PROFILE_REQ_T_BEARER_BITMASK               = 0x10A,
    /* compression */
    /* type = uint8_t, refer to APN_COMPRESSION */
    MIPC_APN_ADD_PROFILE_REQ_T_COMPRESSION                  = 0x10B,
    /* apn is enabled or not, MAX is not set */
    /* type = uint8_t, refer to APN_ENABLED_TYPE */
    MIPC_APN_ADD_PROFILE_REQ_T_ENABLED                      = 0x10C,
};

    /* MIPC_MSG.APN_ADD_PROFILE_CNF */
enum mipc_apn_add_profile_cnf_tlv_enum {
    mipc_apn_add_profile_cnf_tlv_NONE = 0,
    /* number of APN profile in list */
    /* type = uint8_t */
    MIPC_APN_ADD_PROFILE_CNF_T_APN_COUNT                    = 0x100,
    /* the list of APN profile */
    /* type = struct_array, refer to apn_profile */
    MIPC_APN_ADD_PROFILE_CNF_T_APN_LIST                     = 0x8101,
};

    /* MIPC_MSG.APN_LIST_PROFILE_REQ */
enum mipc_apn_list_profile_req_tlv_enum {
    mipc_apn_list_profile_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.APN_LIST_PROFILE_CNF */
enum mipc_apn_list_profile_cnf_tlv_enum {
    mipc_apn_list_profile_cnf_tlv_NONE = 0,
    /* number of APN profile in list */
    /* type = uint8_t */
    MIPC_APN_LIST_PROFILE_CNF_T_APN_COUNT                   = 0x100,
    /* the list of APN profile */
    /* type = struct_array, refer to apn_profile */
    MIPC_APN_LIST_PROFILE_CNF_T_APN_LIST                    = 0x8101,
};

    /* MIPC_MSG.APN_DEL_PROFILE_REQ */
enum mipc_apn_del_profile_req_tlv_enum {
    mipc_apn_del_profile_req_tlv_NONE = 0,
    /* profile ID to delete */
    /* type = uint32_t */
    MIPC_APN_DEL_PROFILE_REQ_T_ID                           = 0x101,
};

    /* MIPC_MSG.APN_DEL_PROFILE_CNF */
enum mipc_apn_del_profile_cnf_tlv_enum {
    mipc_apn_del_profile_cnf_tlv_NONE = 0,
    /* profile number in list */
    /* type = uint8_t */
    MIPC_APN_DEL_PROFILE_CNF_T_APN_COUNT                    = 0x100,
    /* profile list */
    /* type = struct_array, refer to apn_profile */
    MIPC_APN_DEL_PROFILE_CNF_T_APN_LIST                     = 0x8101,
};

    /* MIPC_MSG.APN_SET_PROFILE_STATUS_REQ */
enum mipc_apn_set_profile_status_req_tlv_enum {
    mipc_apn_set_profile_status_req_tlv_NONE = 0,
    /* indicate host/ap will set APN profile or not */
    /* type = uint8_t, refer to APN_PROFILE_MODE */
    MIPC_APN_SET_PROFILE_STATUS_REQ_T_MODE                  = 0x101,
};

    /* MIPC_MSG.APN_SET_PROFILE_STATUS_CNF */
enum mipc_apn_set_profile_status_cnf_tlv_enum {
    mipc_apn_set_profile_status_cnf_tlv_NONE = 0,
};

    /* MIPC_MSG.APN_LIST_MD_PROFILE_REQ */
enum mipc_apn_list_md_profile_req_tlv_enum {
    mipc_apn_list_md_profile_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.APN_LIST_MD_PROFILE_CNF */
enum mipc_apn_list_md_profile_cnf_tlv_enum {
    mipc_apn_list_md_profile_cnf_tlv_NONE = 0,
    /* number of APN profile in list */
    /* type = uint8_t */
    MIPC_APN_LIST_MD_PROFILE_CNF_T_APN_COUNT                = 0x100,
    /* the list of APN profile */
    /* type = struct_array, refer to md_apn_profile */
    MIPC_APN_LIST_MD_PROFILE_CNF_T_APN_LIST                 = 0x8101,
};

    /* MIPC_MSG.APN_SET_VZW_APN_REQ */
enum mipc_apn_set_vzw_apn_req_tlv_enum {
    mipc_apn_set_vzw_apn_req_tlv_NONE = 0,
    /* indicate which APN identity to edit */
    /* type = uint8_t */
    MIPC_APN_SET_VZW_APN_REQ_T_APN_ID                       = 0x100,
    /* indicate the APN class */
    /* type = uint8_t */
    MIPC_APN_SET_VZW_APN_REQ_T_CLASS                        = 0x101,
    /* the network identifier, such as IMS,VZWADMIN,etc */
    /* type = string */
    MIPC_APN_SET_VZW_APN_REQ_T_NETWORK_IDENTIFIER           = 0x102,
    /* pdp type,such as IP,IPv6,IPv4v6 */
    /* type = uint8_t, refer to APN_PDP_TYPE */
    MIPC_APN_SET_VZW_APN_REQ_T_PDP_TYPE                     = 0x103,
    /* apn bearer, such as, LTE */
    /* type = string */
    MIPC_APN_SET_VZW_APN_REQ_T_APN_BEARER                   = 0x104,
    /* apn is enabled or not, MAX is not set */
    /* type = uint8_t, refer to APN_ENABLED_TYPE */
    MIPC_APN_SET_VZW_APN_REQ_T_ENABLED                      = 0x105,
    /* APN inactivity timer */
    /* type = uint32_t */
    MIPC_APN_SET_VZW_APN_REQ_T_APN_TIMER                    = 0x106,
};

    /* MIPC_MSG.APN_SET_VZW_APN_CNF */
enum mipc_apn_set_vzw_apn_cnf_tlv_enum {
    mipc_apn_set_vzw_apn_cnf_tlv_NONE = 0,
};

    /* MIPC_MSG.APN_SET_VZW_APN_TIMER_REQ */
enum mipc_apn_set_vzw_apn_timer_req_tlv_enum {
    mipc_apn_set_vzw_apn_timer_req_tlv_NONE = 0,
    /* indicate which APN identity to edit */
    /* type = uint8_t */
    MIPC_APN_SET_VZW_APN_TIMER_REQ_T_APN_ID                 = 0x100,
    /* max connection count */
    /* type = uint8_t */
    MIPC_APN_SET_VZW_APN_TIMER_REQ_T_MAX_CONN               = 0x101,
    /* max connection  */
    /* type = uint8_t */
    MIPC_APN_SET_VZW_APN_TIMER_REQ_T_MAX_CONN_T             = 0x102,
    /* wait time by seconds */
    /* type = uint32_t */
    MIPC_APN_SET_VZW_APN_TIMER_REQ_T_WAIT_TIME              = 0x103,
    /* throttle timer by seconds */
    /* type = uint32_t */
    MIPC_APN_SET_VZW_APN_TIMER_REQ_T_THROTTLE_TIME          = 0x104,
};

    /* MIPC_MSG.APN_SET_VZW_APN_TIMER_CNF */
enum mipc_apn_set_vzw_apn_timer_cnf_tlv_enum {
    mipc_apn_set_vzw_apn_timer_cnf_tlv_NONE = 0,
};

    /* MIPC_MSG.APN_ADD_PROFILE_LIST_REQ */
enum mipc_apn_add_profile_list_req_tlv_enum {
    mipc_apn_add_profile_list_req_tlv_NONE = 0,
    /* indicate how many profiles in list,profile count should be <= 10 */
    /* type = uint8_t */
    MIPC_APN_ADD_PROFILE_LIST_REQ_T_PROFILE_COUNT           = 0x100,
    /* the profile list to add */
    /* type = struct_array, refer to apn_profile_v2 */
    MIPC_APN_ADD_PROFILE_LIST_REQ_T_PROFILE_LIST            = 0x8101,
};

    /* MIPC_MSG.APN_ADD_PROFILE_LIST_CNF */
enum mipc_apn_add_profile_list_cnf_tlv_enum {
    mipc_apn_add_profile_list_cnf_tlv_NONE = 0,
    /* indicate how many profiles in list */
    /* type = uint8_t */
    MIPC_APN_ADD_PROFILE_LIST_CNF_T_PROFILE_COUNT           = 0x100,
    /* the profile list to add */
    /* type = struct_array, refer to apn_profile_v2 */
    MIPC_APN_ADD_PROFILE_LIST_CNF_T_PROFILE_LIST            = 0x8101,
};

    /* MIPC_MSG.APN_SET_IA_MD_PREFER_REQ */
enum mipc_apn_set_ia_md_prefer_req_tlv_enum {
    mipc_apn_set_ia_md_prefer_req_tlv_NONE = 0,
    /* modem will select initial APN for LTE or not */
    /* type = uint8_t, refer to IA_MD_PREFER_TYPE */
    MIPC_APN_SET_IA_MD_PREFER_REQ_T_IA_MD_PREFER            = 0x100,
};

    /* MIPC_MSG.APN_SET_IA_MD_PREFER_CNF */
enum mipc_apn_set_ia_md_prefer_cnf_tlv_enum {
    mipc_apn_set_ia_md_prefer_cnf_tlv_NONE = 0,
};

    /* MIPC_MSG.DATA_ACT_CALL_REQ */
enum mipc_data_act_call_req_tlv_enum {
    mipc_data_act_call_req_tlv_NONE = 0,
    /* APN name */
    /* type = string */
    MIPC_DATA_ACT_CALL_REQ_T_APN                            = 0x101,
    /* APN type */
    /* type = uint32_t, refer to APN_TYPE */
    MIPC_DATA_ACT_CALL_REQ_T_APN_TYPE                       = 0x102,
    /* PDP type */
    /* type = uint8_t, refer to APN_PDP_TYPE */
    MIPC_DATA_ACT_CALL_REQ_T_PDP_TYPE                       = 0x103,
    /* ROAMING type */
    /* type = uint8_t, refer to APN_PDP_TYPE */
    MIPC_DATA_ACT_CALL_REQ_T_ROAMING_TYPE                   = 0x104,
    /* AUTH type */
    /* type = uint8_t, refer to APN_AUTH_TYPE */
    MIPC_DATA_ACT_CALL_REQ_T_AUTH_TYPE                      = 0x105,
    /* username */
    /* type = string */
    MIPC_DATA_ACT_CALL_REQ_T_USERID                         = 0x8106,
    /* password */
    /* type = string */
    MIPC_DATA_ACT_CALL_REQ_T_PASSWORD                       = 0x8107,
    /* v4v6 fallback mode */
    /* type = uint8_t, refer to DATA_FALLBACK_TYPE */
    MIPC_DATA_ACT_CALL_REQ_T_IPV4V6_FALLBACK                = 0x108,
    /* specifiy allowed bearer type */
    /* type = uint32_t */
    MIPC_DATA_ACT_CALL_REQ_T_BEARER_BITMASK                 = 0x109,
    /* how to reuse modem already activated pdn */
    /* type = uint8_t, refer to DATA_REUSE_TYPE */
    MIPC_DATA_ACT_CALL_REQ_T_REUSE_FLAG                     = 0x10A,
    /* to indicate different APNs which have same apn */
    /* type = uint32_t */
    MIPC_DATA_ACT_CALL_REQ_T_APN_INDEX                      = 0x10C,
    /* to indicate URSP traffic description */
    /* type = struct, refer to ursp_traffic_desc_struct */
    MIPC_DATA_ACT_CALL_REQ_T_URSP_TRAFFIC_DESC              = 0x10D,
    /* to indicate URSP ue local configuartion */
    /* type = struct, refer to ursp_ue_local_conf_struct */
    MIPC_DATA_ACT_CALL_REQ_T_URSP_UE_LOCAL_CONF             = 0x10E,
    /* URSP EVAL MATCH ALL DISALLOWED */
    /* type = uint32_t */
    MIPC_DATA_ACT_CALL_REQ_T_URSP_EVAL_FLAG                 = 0x10F,
};

    /* MIPC_MSG.DATA_ACT_CALL_CNF */
enum mipc_data_act_call_cnf_tlv_enum {
    mipc_data_act_call_cnf_tlv_NONE = 0,
    /* data call id */
    /* type = uint8_t */
    MIPC_DATA_ACT_CALL_CNF_T_ID                             = 0x100,
    /* apn name */
    /* type = string */
    MIPC_DATA_ACT_CALL_CNF_T_APN                            = 0x101,
    /* pdp type */
    /* type = uint8_t, refer to APN_PDP_TYPE */
    MIPC_DATA_ACT_CALL_CNF_T_PDP_TYPE                       = 0x102,
    /* v4 address count */
    /* type = uint8_t */
    MIPC_DATA_ACT_CALL_CNF_T_V4_COUNT                       = 0x103,
    /* first v4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_ACT_CALL_CNF_T_V4_0                           = 0x8104,
    /* second v4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_ACT_CALL_CNF_T_V4_1                           = 0x8105,
    /* third v4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_ACT_CALL_CNF_T_V4_2                           = 0x8106,
    /* fourth v4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_ACT_CALL_CNF_T_V4_3                           = 0x8107,
    /* v6 address count */
    /* type = uint8_t */
    MIPC_DATA_ACT_CALL_CNF_T_V6_COUNT                       = 0x108,
    /* first v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_ACT_CALL_CNF_T_V6_0                           = 0x8109,
    /* second v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_ACT_CALL_CNF_T_V6_1                           = 0x810A,
    /* third v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_ACT_CALL_CNF_T_V6_2                           = 0x810B,
    /* fourth v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_ACT_CALL_CNF_T_V6_3                           = 0x810C,
    /* DNS v4 address count */
    /* type = uint8_t */
    MIPC_DATA_ACT_CALL_CNF_T_DNS_V4_COUNT                   = 0x10D,
    /* first DNS v4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_ACT_CALL_CNF_T_DNS_V4_0                       = 0x810E,
    /* second DNS v4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_ACT_CALL_CNF_T_DNS_V4_1                       = 0x810F,
    /* third DNS v4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_ACT_CALL_CNF_T_DNS_V4_2                       = 0x8110,
    /* fourth DNS v4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_ACT_CALL_CNF_T_DNS_V4_3                       = 0x8111,
    /* DNS v6 address count */
    /* type = uint8_t */
    MIPC_DATA_ACT_CALL_CNF_T_DNS_V6_COUNT                   = 0x112,
    /* first DNS v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_ACT_CALL_CNF_T_DNS_V6_0                       = 0x8113,
    /* second DNS v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_ACT_CALL_CNF_T_DNS_V6_1                       = 0x8114,
    /* third DNS v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_ACT_CALL_CNF_T_DNS_V6_2                       = 0x8115,
    /* fourth DNS v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_ACT_CALL_CNF_T_DNS_V6_3                       = 0x8116,
    /* PCSCF v4 address count */
    /* type = uint8_t */
    MIPC_DATA_ACT_CALL_CNF_T_PCSCF_V4_COUNT                 = 0x117,
    /* first PCSCF v4 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_ACT_CALL_CNF_T_PCSCF_V4_0                     = 0x8118,
    /* second PCSCF v4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_ACT_CALL_CNF_T_PCSCF_V4_1                     = 0x8119,
    /* third PCSCF v4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_ACT_CALL_CNF_T_PCSCF_V4_2                     = 0x811A,
    /* fourth PCSCF v4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_ACT_CALL_CNF_T_PCSCF_V4_3                     = 0x811B,
    /* PCSCF v6 address count */
    /* type = uint8_t */
    MIPC_DATA_ACT_CALL_CNF_T_PCSCF_V6_COUNT                 = 0x11C,
    /* first PCSCF v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_ACT_CALL_CNF_T_PCSCF_V6_0                     = 0x811D,
    /* second PCSCF v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_ACT_CALL_CNF_T_PCSCF_V6_1                     = 0x811E,
    /* third PCSCF v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_ACT_CALL_CNF_T_PCSCF_V6_2                     = 0x811F,
    /* fourth PCSCF v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_ACT_CALL_CNF_T_PCSCF_V6_3                     = 0x8120,
    /* gateway v4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_ACT_CALL_CNF_T_GW_V4                          = 0x8121,
    /* gateway v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_ACT_CALL_CNF_T_GW_V6                          = 0x8122,
    /* v4 MTU */
    /* type = uint32_t */
    MIPC_DATA_ACT_CALL_CNF_T_MTU_V4                         = 0x123,
    /* v6 MTU */
    /* type = uint32_t */
    MIPC_DATA_ACT_CALL_CNF_T_MTU_V6                         = 0x124,
    /* network interface id */
    /* type = uint32_t */
    MIPC_DATA_ACT_CALL_CNF_T_INTERFACE_ID                   = 0x125,
    /* data call primary id */
    /* type = uint8_t */
    MIPC_DATA_ACT_CALL_CNF_T_P_ID                           = 0x126,
    /*  fall back data call id */
    /* type = uint8_t */
    MIPC_DATA_ACT_CALL_CNF_T_FB_ID                          = 0x127,
    /*  IPv4 net mask */
    /* type = uint32_t */
    MIPC_DATA_ACT_CALL_CNF_T_IPv4_NETMASK                   = 0x128,
    /*  IPv6 net mask */
    /* type = uint32_t */
    MIPC_DATA_ACT_CALL_CNF_T_IPv6_NETMASK                   = 0x129,
    /*  network transmition id */
    /* type = uint32_t */
    MIPC_DATA_ACT_CALL_CNF_T_TRANS_ID                       = 0x12A,
    /* RAN info, wifi, cellular or unknown */
    /* type = uint8_t, refer to RAN */
    MIPC_DATA_ACT_CALL_CNF_T_RAN_INFO                       = 0x12B,
    /*  network ESM/5GSM bearer id */
    /* type = uint32_t */
    MIPC_DATA_ACT_CALL_CNF_T_BEARER_ID                      = 0x12C,
    /* im cn signalling flag from network */
    /* type = uint8_t */
    MIPC_DATA_ACT_CALL_CNF_T_IM_CN_SIGNALLING_FLAG          = 0x12D,
};

    /* MIPC_MSG.DATA_DEACT_CALL_REQ */
enum mipc_data_deact_call_req_tlv_enum {
    mipc_data_deact_call_req_tlv_NONE = 0,
    /* data call id */
    /* type = uint8_t */
    MIPC_DATA_DEACT_CALL_REQ_T_ID                           = 0x101,
    /* deact reason */
    /* type = uint8_t, refer to DEACT_REASON_ENUM */
    MIPC_DATA_DEACT_CALL_REQ_T_DEACT_REASON                 = 0x102,
};

    /* MIPC_MSG.DATA_DEACT_CALL_CNF */
enum mipc_data_deact_call_cnf_tlv_enum {
    mipc_data_deact_call_cnf_tlv_NONE = 0,
    /* data call id */
    /* type = uint8_t */
    MIPC_DATA_DEACT_CALL_CNF_T_ID                           = 0x100,
};

    /* MIPC_MSG.DATA_GET_CALL_REQ */
enum mipc_data_get_call_req_tlv_enum {
    mipc_data_get_call_req_tlv_NONE = 0,
    /* data call id */
    /* type = uint8_t */
    MIPC_DATA_GET_CALL_REQ_T_ID                             = 0x101,
};

    /* MIPC_MSG.DATA_GET_CALL_CNF */
enum mipc_data_get_call_cnf_tlv_enum {
    mipc_data_get_call_cnf_tlv_NONE = 0,
    /* data call id */
    /* type = uint8_t */
    MIPC_DATA_GET_CALL_CNF_T_ID                             = 0x100,
    /* APN name */
    /* type = string */
    MIPC_DATA_GET_CALL_CNF_T_APN                            = 0x101,
    /* PDP type */
    /* type = uint8_t, refer to APN_PDP_TYPE */
    MIPC_DATA_GET_CALL_CNF_T_PDP_TYPE                       = 0x102,
    /* v4 address count */
    /* type = uint8_t */
    MIPC_DATA_GET_CALL_CNF_T_V4_COUNT                       = 0x103,
    /* first v4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_GET_CALL_CNF_T_V4_0                           = 0x8104,
    /* second v4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_GET_CALL_CNF_T_V4_1                           = 0x8105,
    /* third v4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_GET_CALL_CNF_T_V4_2                           = 0x8106,
    /* fourth v4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_GET_CALL_CNF_T_V4_3                           = 0x8107,
    /* v6 address count */
    /* type = uint8_t */
    MIPC_DATA_GET_CALL_CNF_T_V6_COUNT                       = 0x108,
    /* first v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_GET_CALL_CNF_T_V6_0                           = 0x8109,
    /* second v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_GET_CALL_CNF_T_V6_1                           = 0x810A,
    /* third v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_GET_CALL_CNF_T_V6_2                           = 0x810B,
    /* fourth v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_GET_CALL_CNF_T_V6_3                           = 0x810C,
    /* DNS v4 address count */
    /* type = uint8_t */
    MIPC_DATA_GET_CALL_CNF_T_DNS_V4_COUNT                   = 0x10D,
    /* first DNS v4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_GET_CALL_CNF_T_DNS_V4_0                       = 0x810E,
    /* second DNS v4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_GET_CALL_CNF_T_DNS_V4_1                       = 0x810F,
    /* third DNS v4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_GET_CALL_CNF_T_DNS_V4_2                       = 0x8110,
    /* fourth DNS v4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_GET_CALL_CNF_T_DNS_V4_3                       = 0x8111,
    /* DNS v6 address count */
    /* type = uint8_t */
    MIPC_DATA_GET_CALL_CNF_T_DNS_V6_COUNT                   = 0x112,
    /* first DNS v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_GET_CALL_CNF_T_DNS_V6_0                       = 0x8113,
    /* second DNS v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_GET_CALL_CNF_T_DNS_V6_1                       = 0x8114,
    /* third DNS v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_GET_CALL_CNF_T_DNS_V6_2                       = 0x8115,
    /* fourth DNS v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_GET_CALL_CNF_T_DNS_V6_3                       = 0x8116,
    /* PCSCF v4 address count */
    /* type = uint8_t */
    MIPC_DATA_GET_CALL_CNF_T_PCSCF_V4_COUNT                 = 0x117,
    /* first PCSCF v4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_GET_CALL_CNF_T_PCSCF_V4_0                     = 0x8118,
    /* second PCSCF v4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_GET_CALL_CNF_T_PCSCF_V4_1                     = 0x8119,
    /* third PCSCF v4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_GET_CALL_CNF_T_PCSCF_V4_2                     = 0x811A,
    /* fourth PCSCF v4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_GET_CALL_CNF_T_PCSCF_V4_3                     = 0x811B,
    /* PCSCF v6 address count */
    /* type = uint8_t */
    MIPC_DATA_GET_CALL_CNF_T_PCSCF_V6_COUNT                 = 0x11C,
    /* first PCSCF v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_GET_CALL_CNF_T_PCSCF_V6_0                     = 0x811D,
    /* second PCSCF v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_GET_CALL_CNF_T_PCSCF_V6_1                     = 0x811E,
    /* third PCSCF v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_GET_CALL_CNF_T_PCSCF_V6_2                     = 0x811F,
    /* fourth PCSCF v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_GET_CALL_CNF_T_PCSCF_V6_3                     = 0x8120,
    /* gateway v4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_GET_CALL_CNF_T_GW_V4                          = 0x8121,
    /* gateway v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_GET_CALL_CNF_T_GW_V6                          = 0x8122,
    /* v4 MTU */
    /* type = uint32_t */
    MIPC_DATA_GET_CALL_CNF_T_MTU_V4                         = 0x123,
    /* v6 MTU */
    /* type = uint32_t */
    MIPC_DATA_GET_CALL_CNF_T_MTU_V6                         = 0x124,
    /* network interface id */
    /* type = uint32_t */
    MIPC_DATA_GET_CALL_CNF_T_INTERFACE_ID                   = 0x125,
    /*  IPv4 net mask */
    /* type = uint32_t */
    MIPC_DATA_GET_CALL_CNF_T_IPv4_NETMASK                   = 0x126,
    /*  IPv6 net mask */
    /* type = uint32_t */
    MIPC_DATA_GET_CALL_CNF_T_IPv6_NETMASK                   = 0x127,
    /* APN type */
    /* type = uint32_t, refer to APN_TYPE */
    MIPC_DATA_GET_CALL_CNF_T_APN_TYPE                       = 0x128,
    /* network transmition id */
    /* type = uint32_t */
    MIPC_DATA_GET_CALL_CNF_T_TRANS_ID                       = 0x129,
    /* RAN info, wifi, cellular or unknown */
    /* type = uint8_t, refer to RAN */
    MIPC_DATA_GET_CALL_CNF_T_RAN_INFO                       = 0x12A,
    /*  network ESM/5GSM bearer id */
    /* type = uint32_t */
    MIPC_DATA_GET_CALL_CNF_T_BEARER_ID                      = 0x12B,
    /* im cn signalling flag from network */
    /* type = uint8_t */
    MIPC_DATA_GET_CALL_CNF_T_IM_CN_SIGNALLING_FLAG          = 0x12C,
    /* identifies the QoS flow */
    /* type = uint8_t */
    MIPC_DATA_GET_CALL_CNF_T_QFI                            = 0x12D,
};

    /* MIPC_MSG.DATA_SET_PACKET_FILTER_REQ */
enum mipc_data_set_packet_filter_req_tlv_enum {
    mipc_data_set_packet_filter_req_tlv_NONE = 0,
    /* data call id (apply to which data call) */
    /* type = uint8_t */
    MIPC_DATA_SET_PACKET_FILTER_REQ_T_ID                    = 0x101,
    /* filter count */
    /* type = uint8_t */
    MIPC_DATA_SET_PACKET_FILTER_REQ_T_FILTER_COUNT          = 0x102,
    /* filter content */
    /* type = struct_array, refer to data_packet_filter */
    MIPC_DATA_SET_PACKET_FILTER_REQ_T_FILTER_LIST           = 0x103,
};

    /* MIPC_MSG.DATA_SET_PACKET_FILTER_CNF */
enum mipc_data_set_packet_filter_cnf_tlv_enum {
    mipc_data_set_packet_filter_cnf_tlv_NONE = 0,
    /* data call id */
    /* type = uint8_t */
    MIPC_DATA_SET_PACKET_FILTER_CNF_T_ID                    = 0x100,
    /* filter count */
    /* type = uint8_t */
    MIPC_DATA_SET_PACKET_FILTER_CNF_T_FILTER_COUNT          = 0x101,
    /* filter content */
    /* type = struct_array, refer to data_packet_filter */
    MIPC_DATA_SET_PACKET_FILTER_CNF_T_FILTER_LIST           = 0x102,
};

    /* MIPC_MSG.DATA_GET_PACKET_FILTER_REQ */
enum mipc_data_get_packet_filter_req_tlv_enum {
    mipc_data_get_packet_filter_req_tlv_NONE = 0,
    /* data call id */
    /* type = uint8_t */
    MIPC_DATA_GET_PACKET_FILTER_REQ_T_ID                    = 0x101,
};

    /* MIPC_MSG.DATA_GET_PACKET_FILTER_CNF */
enum mipc_data_get_packet_filter_cnf_tlv_enum {
    mipc_data_get_packet_filter_cnf_tlv_NONE = 0,
    /* data call id */
    /* type = uint8_t */
    MIPC_DATA_GET_PACKET_FILTER_CNF_T_ID                    = 0x100,
    /* filter count */
    /* type = uint8_t */
    MIPC_DATA_GET_PACKET_FILTER_CNF_T_FILTER_COUNT          = 0x101,
    /* filter content */
    /* type = struct_array, refer to data_packet_filter */
    MIPC_DATA_GET_PACKET_FILTER_CNF_T_FILTER_LIST           = 0x102,
};

    /* MIPC_MSG.DATA_GET_PCO_REQ */
enum mipc_data_get_pco_req_tlv_enum {
    mipc_data_get_pco_req_tlv_NONE = 0,
    /* data call id */
    /* type = uint8_t */
    MIPC_DATA_GET_PCO_REQ_T_ID                              = 0x101,
    /* apn name */
    /* type = string */
    MIPC_DATA_GET_PCO_REQ_T_APN                             = 0x102,
    /* apn index */
    /* type = uint32_t */
    MIPC_DATA_GET_PCO_REQ_T_APN_INDEX                       = 0x103,
    /* pco ie to query */
    /* type = string */
    MIPC_DATA_GET_PCO_REQ_T_PCO_IE                          = 0x104,
};

    /* MIPC_MSG.DATA_GET_PCO_CNF */
enum mipc_data_get_pco_cnf_tlv_enum {
    mipc_data_get_pco_cnf_tlv_NONE = 0,
    /* data call id */
    /* type = uint8_t */
    MIPC_DATA_GET_PCO_CNF_T_ID                              = 0x100,
    /* PCO count */
    /* type = uint8_t */
    MIPC_DATA_GET_PCO_CNF_T_PCO_COUNT                       = 0x101,
    /* PCO content */
    /* type = struct, refer to data_pco_ie */
    MIPC_DATA_GET_PCO_CNF_T_PCO_LIST                        = 0x102,
};

    /* MIPC_MSG.DATA_SET_DATA_ALLOW_REQ */
enum mipc_data_set_data_allow_req_tlv_enum {
    mipc_data_set_data_allow_req_tlv_NONE = 0,
    /* to indicate clear or not, if this TLV is not NULL, data allow configuration will be cleared */
    /* type = uint8_t */
    MIPC_DATA_SET_DATA_ALLOW_REQ_T_CLEAR                    = 0x100,
};

    /* MIPC_MSG.DATA_SET_DATA_ALLOW_CNF */
enum mipc_data_set_data_allow_cnf_tlv_enum {
    mipc_data_set_data_allow_cnf_tlv_NONE = 0,
};

    /* MIPC_MSG.DATA_GET_MD_DATA_CALL_LIST_REQ */
enum mipc_data_get_md_data_call_list_req_tlv_enum {
    mipc_data_get_md_data_call_list_req_tlv_NONE = 0,
};

    /* MIPC_MSG.DATA_GET_MD_DATA_CALL_LIST_CNF */
enum mipc_data_get_md_data_call_list_cnf_tlv_enum {
    mipc_data_get_md_data_call_list_cnf_tlv_NONE = 0,
    /* data call id list and indicate which is actived */
    /* type = byte_array, refer to MIPC_CID_ACT_STATE */
    MIPC_DATA_GET_MD_DATA_CALL_LIST_CNF_T_CID_LIST          = 0x100,
};

    /* MIPC_MSG.DATA_SET_CONFIG_REQ */
enum mipc_data_set_config_req_tlv_enum {
    mipc_data_set_config_req_tlv_NONE = 0,
    /* mobile data, enable, disable or no change */
    /* type = uint8_t, refer to DATA_CONFIG_TYPE */
    MIPC_DATA_SET_CONFIG_REQ_T_MOBILE_DATA                  = 0x100,
    /* data roaming config, enable, disable or no change */
    /* type = uint8_t, refer to DATA_CONFIG_TYPE */
    MIPC_DATA_SET_CONFIG_REQ_T_DATA_ROAMING                 = 0x101,
    /* VOLTE config, enable, disable or no change */
    /* type = uint8_t, refer to DATA_CONFIG_TYPE */
    MIPC_DATA_SET_CONFIG_REQ_T_VOLTE                        = 0x102,
    /* ims test mode config, enable, disable or no change */
    /* type = uint8_t, refer to DATA_CONFIG_TYPE */
    MIPC_DATA_SET_CONFIG_REQ_T_IMS_TEST_MODE                = 0x103,
    /* data domestic roaming config, enable, disable or no change */
    /* type = uint8_t, refer to DATA_CONFIG_TYPE */
    MIPC_DATA_SET_CONFIG_REQ_T_DATA_DOMESTIC_ROAMING        = 0x104,
    /* data international roaming config, enable, disable or no change */
    /* type = uint8_t, refer to DATA_CONFIG_TYPE */
    MIPC_DATA_SET_CONFIG_REQ_T_DATA_INTERNATIONAL_ROAMING   = 0x105,
    /* default sim card */
    /* type = uint8_t */
    MIPC_DATA_SET_CONFIG_REQ_T_DEFAULT_DATA_SIM_CARD        = 0x106,
};

    /* MIPC_MSG.DATA_SET_CONFIG_CNF */
enum mipc_data_set_config_cnf_tlv_enum {
    mipc_data_set_config_cnf_tlv_NONE = 0,
};

    /* MIPC_MSG.DATA_GET_CONFIG_REQ */
enum mipc_data_get_config_req_tlv_enum {
    mipc_data_get_config_req_tlv_NONE = 0,
};

    /* MIPC_MSG.DATA_GET_CONFIG_CNF */
enum mipc_data_get_config_cnf_tlv_enum {
    mipc_data_get_config_cnf_tlv_NONE = 0,
    /* mobile data, enable, disable or no change */
    /* type = uint8_t, refer to DATA_CONFIG_TYPE */
    MIPC_DATA_GET_CONFIG_CNF_T_MOBILE_DATA                  = 0x100,
    /* data roaming config, enable, disable or no change */
    /* type = uint8_t, refer to DATA_CONFIG_TYPE */
    MIPC_DATA_GET_CONFIG_CNF_T_DATA_ROAMING                 = 0x101,
    /* VOLTE config, enable, disable or no change */
    /* type = uint8_t, refer to DATA_CONFIG_TYPE */
    MIPC_DATA_GET_CONFIG_CNF_T_VOLTE                        = 0x102,
    /* ims test mode config, enable, disable or no change */
    /* type = uint8_t, refer to DATA_CONFIG_TYPE */
    MIPC_DATA_GET_CONFIG_CNF_T_IMS_TEST_MODE                = 0x103,
    /* data domestic roaming config, enable, disable or no change */
    /* type = uint8_t, refer to DATA_CONFIG_TYPE */
    MIPC_DATA_GET_CONFIG_CNF_T_DATA_DOMESTIC_ROAMING        = 0x104,
    /* data international roaming config, enable, disable or no change */
    /* type = uint8_t, refer to DATA_CONFIG_TYPE */
    MIPC_DATA_GET_CONFIG_CNF_T_DATA_INTERNATIONAL_ROAMING   = 0x105,
};

    /* MIPC_MSG.DATA_ABORT_CALL_REQ */
enum mipc_data_abort_call_req_tlv_enum {
    mipc_data_abort_call_req_tlv_NONE = 0,
    /* apn name */
    /* type = string */
    MIPC_DATA_ABORT_CALL_REQ_T_APN                          = 0x100,
};

    /* MIPC_MSG.DATA_ABORT_CALL_CNF */
enum mipc_data_abort_call_cnf_tlv_enum {
    mipc_data_abort_call_cnf_tlv_NONE = 0,
};

    /* MIPC_MSG.DATA_GET_CALL_INFO_REQ */
enum mipc_data_get_call_info_req_tlv_enum {
    mipc_data_get_call_info_req_tlv_NONE = 0,
    /* apn name */
    /* type = string */
    MIPC_DATA_GET_CALL_INFO_REQ_T_APN                       = 0x100,
    /* data call id */
    /* type = uint8_t */
    MIPC_DATA_GET_CALL_INFO_REQ_T_ID                        = 0x101,
};

    /* MIPC_MSG.DATA_GET_CALL_INFO_CNF */
enum mipc_data_get_call_info_cnf_tlv_enum {
    mipc_data_get_call_info_cnf_tlv_NONE = 0,
    /* apn name */
    /* type = string */
    MIPC_DATA_GET_CALL_INFO_CNF_T_APN                       = 0x100,
    /* data call id */
    /* type = uint8_t */
    MIPC_DATA_GET_CALL_INFO_CNF_T_ID                        = 0x101,
    /* the utc time of call established */
    /* type = struct, refer to data_nitz_info */
    MIPC_DATA_GET_CALL_INFO_CNF_T_ESTBLISHED_TIME           = 0x102,
    /* the utc time of call disconnected */
    /* type = struct, refer to data_nitz_info */
    MIPC_DATA_GET_CALL_INFO_CNF_T_END_TIME                  = 0x103,
    /* if PDN is rejected, indicate reject cause from netowrk, 0 means success */
    /* type = uint32_t */
    MIPC_DATA_GET_CALL_INFO_CNF_T_REJECT_CAUSE              = 0x104,
};

    /* MIPC_MSG.DATA_GET_PDP_CID_REQ */
enum mipc_data_get_pdp_cid_req_tlv_enum {
    mipc_data_get_pdp_cid_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.DATA_GET_PDP_CID_CNF */
enum mipc_data_get_pdp_cid_cnf_tlv_enum {
    mipc_data_get_pdp_cid_cnf_tlv_NONE = 0,
    /* minimum pdp cid */
    /* type = uint8_t */
    MIPC_DATA_GET_PDP_CID_CNF_T_MIN_CID                     = 0x100,
    /* max pdp cid */
    /* type = uint8_t */
    MIPC_DATA_GET_PDP_CID_CNF_T_MAX_CID                     = 0x101,
};

    /* MIPC_MSG.DATA_RETRY_TIMER_REQ */
enum mipc_data_retry_timer_req_tlv_enum {
    mipc_data_retry_timer_req_tlv_NONE = 0,
    /* 0: query modem suggested retry time. 1: reset data retry count. 2: retry after a given time period */
    /* type = uint8_t, refer to DATA_RETRY_MODE */
    MIPC_DATA_RETRY_TIMER_REQ_T_MODE                        = 0x100,
    /* apn name */
    /* type = string */
    MIPC_DATA_RETRY_TIMER_REQ_T_APN_NAME                    = 0x101,
};

    /* MIPC_MSG.DATA_RETRY_TIMER_CNF */
enum mipc_data_retry_timer_cnf_tlv_enum {
    mipc_data_retry_timer_cnf_tlv_NONE = 0,
    /* suggest retry type from modem */
    /* type = uint8_t, refer to DATA_RETRY_TYPE */
    MIPC_DATA_RETRY_TIMER_CNF_T_RETRY_TYPE                  = 0x100,
    /* suggest retry time from modem is second */
    /* type = uint32_t */
    MIPC_DATA_RETRY_TIMER_CNF_T_RETRY_TIME                  = 0x101,
};

    /* MIPC_MSG.DATA_SET_LINK_CAPACITY_REPORTING_CRITERIA_REQ */
enum mipc_data_set_link_capacity_reporting_criteria_req_tlv_enum {
    mipc_data_set_link_capacity_reporting_criteria_req_tlv_NONE = 0,
    /* 0: disable. 1: enable. 2: set LCE reporting criteria */
    /* type = uint8_t, refer to DATA_LCE_MODE */
    MIPC_DATA_SET_LINK_CAPACITY_REPORTING_CRITERIA_REQ_T_MODE = 0x100,
    /* Minimum time interval between two URC reports */
    /* type = uint32_t */
    MIPC_DATA_SET_LINK_CAPACITY_REPORTING_CRITERIA_REQ_T_HYSTERESIS_MS = 0x101,
    /* Minumum dl throughput change between two URC reports */
    /* type = uint32_t */
    MIPC_DATA_SET_LINK_CAPACITY_REPORTING_CRITERIA_REQ_T_HYSTERESIS_DL_KBPS = 0x102,
    /* Minimum ul throughput change between two URC reports */
    /* type = uint32_t */
    MIPC_DATA_SET_LINK_CAPACITY_REPORTING_CRITERIA_REQ_T_HYSTERESIS_UL_KBPS = 0x103,
    /* number of threshold DL Kbps List len */
    /* type = uint8_t */
    MIPC_DATA_SET_LINK_CAPACITY_REPORTING_CRITERIA_REQ_T_THRESHOLD_DL_KBPS_NUM = 0x104,
    /* threshold DL Kbps List, int array */
    /* type = byte_array */
    MIPC_DATA_SET_LINK_CAPACITY_REPORTING_CRITERIA_REQ_T_THRESHOLD_DL_KBPS_LIST = 0x105,
    /* number of threshold UL Kbps List len */
    /* type = uint8_t */
    MIPC_DATA_SET_LINK_CAPACITY_REPORTING_CRITERIA_REQ_T_THRESHOLD_UL_KBPS_NUM = 0x106,
    /* threshold UL Kbps List, int array */
    /* type = byte_array */
    MIPC_DATA_SET_LINK_CAPACITY_REPORTING_CRITERIA_REQ_T_THRESHOLD_UL_KBPS_LIST = 0x107,
    /* Rat for which the Link capacity reporting criteria is applicable */
    /* type = uint32_t */
    MIPC_DATA_SET_LINK_CAPACITY_REPORTING_CRITERIA_REQ_T_ACCESS_NETWORK = 0x108,
};

    /* MIPC_MSG.DATA_SET_LINK_CAPACITY_REPORTING_CRITERIA_CNF */
enum mipc_data_set_link_capacity_reporting_criteria_cnf_tlv_enum {
    mipc_data_set_link_capacity_reporting_criteria_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.DATA_GET_DEDICATE_BEARER_INFO_REQ */
enum mipc_data_get_dedicate_bearer_info_req_tlv_enum {
    mipc_data_get_dedicate_bearer_info_req_tlv_NONE = 0,
    /* context identifier */
    /* type = uint8_t */
    MIPC_DATA_GET_DEDICATE_BEARER_INFO_REQ_T_CID            = 0x100,
};

    /* MIPC_MSG.DATA_GET_DEDICATE_BEARER_INFO_CNF */
enum mipc_data_get_dedicate_bearer_info_cnf_tlv_enum {
    mipc_data_get_dedicate_bearer_info_cnf_tlv_NONE = 0,
    /* PDP contexts, struct array */
    /* type = struct, refer to data_secondary_pdp_context_info */
    MIPC_DATA_GET_DEDICATE_BEARER_INFO_CNF_T_CONTEXT_LIST   = 0x100,
};

    /* MIPC_MSG.DATA_GET_QOS_REQ */
enum mipc_data_get_qos_req_tlv_enum {
    mipc_data_get_qos_req_tlv_NONE = 0,
    /* context identifier */
    /* type = uint8_t */
    MIPC_DATA_GET_QOS_REQ_T_CID                             = 0x100,
};

    /* MIPC_MSG.DATA_GET_QOS_CNF */
enum mipc_data_get_qos_cnf_tlv_enum {
    mipc_data_get_qos_cnf_tlv_NONE = 0,
    /* qos info, struct array */
    /* type = struct, refer to data_qos_info */
    MIPC_DATA_GET_QOS_CNF_T_QOS_LIST                        = 0x100,
};

    /* MIPC_MSG.DATA_GET_TFT_REQ */
enum mipc_data_get_tft_req_tlv_enum {
    mipc_data_get_tft_req_tlv_NONE = 0,
    /* context identifier */
    /* type = uint8_t */
    MIPC_DATA_GET_TFT_REQ_T_CID                             = 0x100,
};

    /* MIPC_MSG.DATA_GET_TFT_CNF */
enum mipc_data_get_tft_cnf_tlv_enum {
    mipc_data_get_tft_cnf_tlv_NONE = 0,
    /* tft info, struct array */
    /* type = struct, refer to data_tft_info */
    MIPC_DATA_GET_TFT_CNF_T_TFT_LIST                        = 0x100,
};

    /* MIPC_MSG.DATA_SET_LGDCONT_REQ */
enum mipc_data_set_lgdcont_req_tlv_enum {
    mipc_data_set_lgdcont_req_tlv_NONE = 0,
    /* APN name */
    /* type = string */
    MIPC_DATA_SET_LGDCONT_REQ_T_APN                         = 0x100,
    /* apn index */
    /* type = uint32_t */
    MIPC_DATA_SET_LGDCONT_REQ_T_APN_INDEX                   = 0x101,
    /* indicates the type of PDP context activation request for the PDP context */
    /* type = uint8_t, refer to DATA_LGDCONT_REQ_TYPE */
    MIPC_DATA_SET_LGDCONT_REQ_T_REQUEST_TYPE                = 0x102,
    /* the target RAT of this PDN connection */
    /* type = uint8_t, refer to DATA_LGDCONT_RAT_TYPE */
    MIPC_DATA_SET_LGDCONT_REQ_T_RAT_TYPE                    = 0x103,
};

    /* MIPC_MSG.DATA_SET_LGDCONT_CNF */
enum mipc_data_set_lgdcont_cnf_tlv_enum {
    mipc_data_set_lgdcont_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.DATA_SET_NSSAI_REQ */
enum mipc_data_set_nssai_req_tlv_enum {
    mipc_data_set_nssai_req_tlv_NONE = 0,
    /* APN name */
    /* type = string */
    MIPC_DATA_SET_NSSAI_REQ_T_APN                           = 0x100,
    /* apn index */
    /* type = uint32_t */
    MIPC_DATA_SET_NSSAI_REQ_T_APN_INDEX                     = 0x101,
    /* s-nssai value string */
    /* type = string */
    MIPC_DATA_SET_NSSAI_REQ_T_SNSSAI                        = 0x102,
};

    /* MIPC_MSG.DATA_SET_NSSAI_CNF */
enum mipc_data_set_nssai_cnf_tlv_enum {
    mipc_data_set_nssai_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.DATA_KEEPALIVE_REQ */
enum mipc_data_keepalive_req_tlv_enum {
    mipc_data_keepalive_req_tlv_NONE = 0,
    /* session handle of stop keep alive */
    /* type = uint32_t */
    MIPC_DATA_KEEPALIVE_REQ_T_STOP_KEEPALIVE                = 0x100,
    /* info of start keep alive */
    /* type = struct, refer to data_start_keepalive_request */
    MIPC_DATA_KEEPALIVE_REQ_T_START_KEEPALIVE               = 0x101,
};

    /* MIPC_MSG.DATA_KEEPALIVE_CNF */
enum mipc_data_keepalive_cnf_tlv_enum {
    mipc_data_keepalive_cnf_tlv_NONE = 0,
    /* connection id */
    /* type = uint32_t */
    MIPC_DATA_KEEPALIVE_CNF_T_SESSION_HANDLE                = 0x100,
    /* keep alive status code */
    /* type = uint8_t, refer to DATA_KEEPALIVE_STATUS_CODE */
    MIPC_DATA_KEEPALIVE_CNF_T_STATUS_CODE                   = 0x101,
};

    /* MIPC_MSG.DATA_GET_DSDA_STATE_REQ */
enum mipc_data_get_dsda_state_req_tlv_enum {
    mipc_data_get_dsda_state_req_tlv_NONE = 0,
};

    /* MIPC_MSG.DATA_GET_DSDA_STATE_CNF */
enum mipc_data_get_dsda_state_cnf_tlv_enum {
    mipc_data_get_dsda_state_cnf_tlv_NONE = 0,
    /* type = uint8_t, refer to DSDA_ALLOWED_TYPE */
    MIPC_DATA_GET_DSDA_STATE_CNF_T_DSDA_ALLOWED             = 0x100,
    /* type = uint8_t, refer to DSDA_STATE_TYPE */
    MIPC_DATA_GET_DSDA_STATE_CNF_T_DSDA_STATE               = 0x101,
};

    /* MIPC_MSG.DATA_GET_5GQOS_REQ */
enum mipc_data_get_5gqos_req_tlv_enum {
    mipc_data_get_5gqos_req_tlv_NONE = 0,
    /* context identifier */
    /* type = uint8_t */
    MIPC_DATA_GET_5GQOS_REQ_T_CID                           = 0x100,
};

    /* MIPC_MSG.DATA_GET_5GQOS_CNF */
enum mipc_data_get_5gqos_cnf_tlv_enum {
    mipc_data_get_5gqos_cnf_tlv_NONE = 0,
    /* 5g qos info, struct array */
    /* type = struct, refer to data_5gqos_info */
    MIPC_DATA_GET_5GQOS_CNF_T_QOS_LIST                      = 0x100,
};

    /* MIPC_MSG.DATA_SET_PSI_REQ */
enum mipc_data_set_psi_req_tlv_enum {
    mipc_data_set_psi_req_tlv_NONE = 0,
    /* PSI handle type */
    /* type = uint8_t, refer to PSI_ACTION_ENUM */
    MIPC_DATA_SET_PSI_REQ_T_ACTION                          = 0x100,
    /* PDU session ID */
    /* type = uint8_t */
    MIPC_DATA_SET_PSI_REQ_T_PSI                             = 0x101,
    /* apn name */
    /* type = string */
    MIPC_DATA_SET_PSI_REQ_T_APN                             = 0x102,
    /* to indicate different APNs which have same apn */
    /* type = uint32_t */
    MIPC_DATA_SET_PSI_REQ_T_APN_INDEX                       = 0x103,
};

    /* MIPC_MSG.DATA_SET_PSI_CNF */
enum mipc_data_set_psi_cnf_tlv_enum {
    mipc_data_set_psi_cnf_tlv_NONE = 0,
    /* PDU session ID */
    /* type = uint8_t */
    MIPC_DATA_SET_PSI_CNF_T_PSI                             = 0x100,
};

    /* MIPC_MSG.DATA_GET_NSSAI_REQ */
enum mipc_data_get_nssai_req_tlv_enum {
    mipc_data_get_nssai_req_tlv_NONE = 0,
    /* indicate NSSAI TYPE to get */
    /* type = uint8_t, refer to NSSAI_TYPE_ENUM */
    MIPC_DATA_GET_NSSAI_REQ_T_NSSAI_TYPE                    = 0x100,
    /* plmn id, mcc1, mcc2, mcc3, mnc1, mnc2, mnc3 */
    /* type = byte_array */
    MIPC_DATA_GET_NSSAI_REQ_T_PLMN_ID                       = 0x101,
};

    /* MIPC_MSG.DATA_GET_NSSAI_CNF */
enum mipc_data_get_nssai_cnf_tlv_enum {
    mipc_data_get_nssai_cnf_tlv_NONE = 0,
    /* indicate the s_nssai count in s_nssai list */
    /* type = uint8_t */
    MIPC_DATA_GET_NSSAI_CNF_T_DEFAULT_CONFIGURED_NSSAI_NUM  = 0x100,
    /* s_nssai list */
    /* type = struct_array, refer to s_nssai_struct */
    MIPC_DATA_GET_NSSAI_CNF_T_DEFAULT_CONFIGURED_NSSAI_LIST = 0x101,
    /* indicate the s_nssai count in s_nssai list */
    /* type = uint8_t */
    MIPC_DATA_GET_NSSAI_CNF_T_REJECTED_NSSAI_3GPP_NUM       = 0x102,
    /* rejected s_nssai list */
    /* type = struct_array, refer to rejected_s_nssai_struct */
    MIPC_DATA_GET_NSSAI_CNF_T_REJECTED_NSSAI_3GPP_LIST      = 0x103,
    /* indicate the s_nssai count in s_nssai list */
    /* type = uint8_t */
    MIPC_DATA_GET_NSSAI_CNF_T_REJECTED_NSSAI_NON3GPP_NUM    = 0x104,
    /* rejected s_nssai list */
    /* type = struct_array, refer to rejected_s_nssai_struct */
    MIPC_DATA_GET_NSSAI_CNF_T_REJECTED_NSSAI_NON3GPP_LIST   = 0x105,
    /* indicate the s_nssai count in s_nssai list */
    /* type = uint8_t */
    MIPC_DATA_GET_NSSAI_CNF_T_CONFIGURED_NSSAI_NUM          = 0x106,
    /* s_nssai list */
    /* type = struct_array, refer to plmn_specific_s_nssai_struct */
    MIPC_DATA_GET_NSSAI_CNF_T_CONFIGURED_NSSAI_LIST         = 0x107,
    /* indicate the s_nssai count in s_nssai list */
    /* type = uint8_t */
    MIPC_DATA_GET_NSSAI_CNF_T_ALLOWED_NSSAI_3GPP_NUM        = 0x108,
    /* s_nssai list */
    /* type = struct_array, refer to plmn_specific_s_nssai_struct */
    MIPC_DATA_GET_NSSAI_CNF_T_ALLOWED_NSSAI_3GPP_LIST       = 0x109,
    /* indicate the s_nssai count in s_nssai list */
    /* type = uint8_t */
    MIPC_DATA_GET_NSSAI_CNF_T_ALLOWED_NSSAI_NON3GPP_NUM     = 0x10A,
    /* s_nssai list */
    /* type = struct_array, refer to plmn_specific_s_nssai_struct */
    MIPC_DATA_GET_NSSAI_CNF_T_ALLOWED_NSSAI_NON3GPP_LIST    = 0x10B,
    /* indicate the preferrd s_nssai count in s_nssai list */
    /* type = uint8_t */
    MIPC_DATA_GET_NSSAI_CNF_T_PREFERRED_NSSAI_3GPP_NUM      = 0x10C,
    /* preferred s_nssai list */
    /* type = struct_array, refer to s_nssai_struct */
    MIPC_DATA_GET_NSSAI_CNF_T_PREFERRED_NSSAI_3GPP_LIST     = 0x10D,
    /* indicate the preferrd non 3gpp s_nssai count in s_nssai list */
    /* type = uint8_t */
    MIPC_DATA_GET_NSSAI_CNF_T_PREFERRED_NSSAI_NON3GPP_NUM   = 0x10E,
    /* preferred non 3gpp s_nssai list */
    /* type = struct_array, refer to s_nssai_struct */
    MIPC_DATA_GET_NSSAI_CNF_T_PREFERRED_NSSAI_NON3GPP_LIST  = 0x10F,
};

    /* MIPC_MSG.DATA_GET_URSP_ROUTE_PROFILE_REQ */
enum mipc_data_get_ursp_route_profile_req_tlv_enum {
    mipc_data_get_ursp_route_profile_req_tlv_NONE = 0,
    /* data call id */
    /* type = uint32_t */
    MIPC_DATA_GET_URSP_ROUTE_PROFILE_REQ_T_ID               = 0x100,
};

    /* MIPC_MSG.DATA_GET_URSP_ROUTE_PROFILE_CNF */
enum mipc_data_get_ursp_route_profile_cnf_tlv_enum {
    mipc_data_get_ursp_route_profile_cnf_tlv_NONE = 0,
    /* data call id */
    /* type = uint32_t */
    MIPC_DATA_GET_URSP_ROUTE_PROFILE_CNF_T_ID               = 0x100,
    /* the establishment request info send to  */
    /* type = struct, refer to ursp_ue_local_conf_struct */
    MIPC_DATA_GET_URSP_ROUTE_PROFILE_CNF_T_EST_REQ_PARAM    = 0x101,
    /* establish attribute */
    /* type = uint32_t */
    MIPC_DATA_GET_URSP_ROUTE_PROFILE_CNF_T_ATTR             = 0x102,
    /* route supp profile list count */
    /* type = uint32_t */
    MIPC_DATA_GET_URSP_ROUTE_PROFILE_CNF_T_ROUTE_SUPP_PROFILE_LIST_NUM = 0x103,
    /* route supp profile list, struct array */
    /* type = struct_array, refer to ursp_get_route_supp_profile_ind_struct */
    MIPC_DATA_GET_URSP_ROUTE_PROFILE_CNF_T_ROUTE_SUPP_PROFILE_LIST = 0x104,
};

    /* MIPC_MSG.DATA_SET_URSP_PRECONF_UE_POLICY_REQ */
enum mipc_data_set_ursp_preconf_ue_policy_req_tlv_enum {
    mipc_data_set_ursp_preconf_ue_policy_req_tlv_NONE = 0,
    /* plmn id, mcc1, mcc2, mcc3, mnc1, mnc2, mnc3 */
    /* type = byte_array */
    MIPC_DATA_SET_URSP_PRECONF_UE_POLICY_REQ_T_PLMN_ID      = 0x100,
    /* the number of rule in rule list */
    /* type = uint8_t */
    MIPC_DATA_SET_URSP_PRECONF_UE_POLICY_REQ_T_RULE_NUM     = 0x101,
    /* rule list */
    /* type = struct_array, refer to ursp_rule_struct */
    MIPC_DATA_SET_URSP_PRECONF_UE_POLICY_REQ_T_RULE_LIST    = 0x102,
};

    /* MIPC_MSG.DATA_SET_URSP_PRECONF_UE_POLICY_CNF */
enum mipc_data_set_ursp_preconf_ue_policy_cnf_tlv_enum {
    mipc_data_set_ursp_preconf_ue_policy_cnf_tlv_NONE = 0,
};

    /* MIPC_MSG.DATA_GET_URSP_UE_POLICY_REQ */
enum mipc_data_get_ursp_ue_policy_req_tlv_enum {
    mipc_data_get_ursp_ue_policy_req_tlv_NONE = 0,
    /* plmn id, mcc1, mcc2, mcc3, mnc1, mnc2, mnc3 */
    /* type = byte_array */
    MIPC_DATA_GET_URSP_UE_POLICY_REQ_T_PLMN_ID              = 0x100,
};

    /* MIPC_MSG.DATA_GET_URSP_UE_POLICY_CNF */
enum mipc_data_get_ursp_ue_policy_cnf_tlv_enum {
    mipc_data_get_ursp_ue_policy_cnf_tlv_NONE = 0,
    /* plmn id, mcc1, mcc2, mcc3, mnc1, mnc2, mnc3 */
    /* type = byte_array */
    MIPC_DATA_GET_URSP_UE_POLICY_CNF_T_PLMN_ID              = 0x100,
    /* the number of rule in rule list */
    /* type = uint8_t */
    MIPC_DATA_GET_URSP_UE_POLICY_CNF_T_RULE_NUM             = 0x101,
    /* rule list */
    /* type = struct_array, refer to ursp_rule_struct */
    MIPC_DATA_GET_URSP_UE_POLICY_CNF_T_RULE_LIST            = 0x102,
};

    /* MIPC_MSG.INTERNAL_OPEN_REQ */
enum mipc_internal_open_req_tlv_enum {
    mipc_internal_open_req_tlv_NONE = 0,
    /*  */
    /* type = uint32_t */
    MIPC_INTERNAL_OPEN_REQ_T_VERSION                        = 0x100,
    /*  */
    /* type = string */
    MIPC_INTERNAL_OPEN_REQ_T_CLIENT_NAME                    = 0x101,
    /* indicate whether the host support USIR feature */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_INTERNAL_OPEN_REQ_T_USIR_SUPPORT                   = 0x102,
};

    /* MIPC_MSG.INTERNAL_OPEN_CNF */
enum mipc_internal_open_cnf_tlv_enum {
    mipc_internal_open_cnf_tlv_NONE = 0,
    /*  */
    /* type = uint32_t */
    MIPC_INTERNAL_OPEN_CNF_T_VERSION                        = 0x100,
    /* default timeout value configured by modem */
    /* type = uint32_t */
    MIPC_INTERNAL_OPEN_CNF_T_TIMEOUT                        = 0x101,
};

    /* MIPC_MSG.INTERNAL_CLOSE_REQ */
enum mipc_internal_close_req_tlv_enum {
    mipc_internal_close_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.INTERNAL_CLOSE_CNF */
enum mipc_internal_close_cnf_tlv_enum {
    mipc_internal_close_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.INTERNAL_TEST_REQ */
enum mipc_internal_test_req_tlv_enum {
    mipc_internal_test_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.INTERNAL_TEST_CNF */
enum mipc_internal_test_cnf_tlv_enum {
    mipc_internal_test_cnf_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_INTERNAL_TEST_CNF_T_TEST                           = 0x100,
};

    /* MIPC_MSG.INTERNAL_REGISTER_IND_REQ */
enum mipc_internal_register_ind_req_tlv_enum {
    mipc_internal_register_ind_req_tlv_NONE = 0,
    /* MIPC message id */
    /* type = uint16_t */
    MIPC_INTERNAL_REGISTER_IND_REQ_T_MSG_ID                 = 0x100,
};

    /* MIPC_MSG.INTERNAL_REGISTER_IND_CNF */
enum mipc_internal_register_ind_cnf_tlv_enum {
    mipc_internal_register_ind_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.INTERNAL_UNREGISTER_IND_REQ */
enum mipc_internal_unregister_ind_req_tlv_enum {
    mipc_internal_unregister_ind_req_tlv_NONE = 0,
    /* MIPC message id */
    /* type = uint16_t */
    MIPC_INTERNAL_UNREGISTER_IND_REQ_T_MSG_ID               = 0x100,
};

    /* MIPC_MSG.INTERNAL_UNREGISTER_IND_CNF */
enum mipc_internal_unregister_ind_cnf_tlv_enum {
    mipc_internal_unregister_ind_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.INTERNAL_REGISTER_CMD_REQ */
enum mipc_internal_register_cmd_req_tlv_enum {
    mipc_internal_register_cmd_req_tlv_NONE = 0,
    /* MIPC message id */
    /* type = uint16_t */
    MIPC_INTERNAL_REGISTER_CMD_REQ_T_MSG_ID                 = 0x100,
};

    /* MIPC_MSG.INTERNAL_REGISTER_CMD_CNF */
enum mipc_internal_register_cmd_cnf_tlv_enum {
    mipc_internal_register_cmd_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.INTERNAL_UNREGISTER_CMD_REQ */
enum mipc_internal_unregister_cmd_req_tlv_enum {
    mipc_internal_unregister_cmd_req_tlv_NONE = 0,
    /* MIPC message id */
    /* type = uint16_t */
    MIPC_INTERNAL_UNREGISTER_CMD_REQ_T_MSG_ID               = 0x100,
};

    /* MIPC_MSG.INTERNAL_UNREGISTER_CMD_CNF */
enum mipc_internal_unregister_cmd_cnf_tlv_enum {
    mipc_internal_unregister_cmd_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.INTERNAL_SET_FILTER_REQ */
enum mipc_internal_set_filter_req_tlv_enum {
    mipc_internal_set_filter_req_tlv_NONE = 0,
    /*  */
    /* type = struct, refer to internal_set_filter_req */
    MIPC_INTERNAL_SET_FILTER_REQ_T_STRUCT                   = 0x100,
};

    /* MIPC_MSG.INTERNAL_SET_FILTER_CNF */
enum mipc_internal_set_filter_cnf_tlv_enum {
    mipc_internal_set_filter_cnf_tlv_NONE = 0,
    /*  */
    /* type = struct, refer to internal_set_filter_cnf */
    MIPC_INTERNAL_SET_FILTER_CNF_T_STRUCT                   = 0x100,
};

    /* MIPC_MSG.INTERNAL_RESET_FILTER_REQ */
enum mipc_internal_reset_filter_req_tlv_enum {
    mipc_internal_reset_filter_req_tlv_NONE = 0,
    /*  */
    /* type = struct, refer to internal_reset_filter_req */
    MIPC_INTERNAL_RESET_FILTER_REQ_T_STRUCT                 = 0x100,
};

    /* MIPC_MSG.INTERNAL_RESET_FILTER_CNF */
enum mipc_internal_reset_filter_cnf_tlv_enum {
    mipc_internal_reset_filter_cnf_tlv_NONE = 0,
    /*  */
    /* type = struct, refer to internal_reset_filter_cnf */
    MIPC_INTERNAL_RESET_FILTER_CNF_T_STRUCT                 = 0x100,
};

    /* MIPC_MSG.INTERNAL_EIF_REQ */
enum mipc_internal_eif_req_tlv_enum {
    mipc_internal_eif_req_tlv_NONE = 0,
    /*  */
    /* type = uint32_t */
    MIPC_INTERNAL_EIF_REQ_T_TRANSID                         = 0x100,
    /*  */
    /* type = uint8_t, refer to INTERNAL_EIF_REQ_CMD */
    MIPC_INTERNAL_EIF_REQ_T_CMD                             = 0x101,
    /*  */
    /* type = struct, refer to full_addr */
    MIPC_INTERNAL_EIF_REQ_T_NEW_ADDR                        = 0x8102,
    /*  */
    /* type = struct, refer to full_addr */
    MIPC_INTERNAL_EIF_REQ_T_OLD_ADDR                        = 0x8103,
    /* pdp type for interface up */
    /* type = uint8_t, refer to EIF_ADDRESS_TYPE */
    MIPC_INTERNAL_EIF_REQ_T_ADDRESS_TYPE                    = 0x104,
};

    /* MIPC_MSG.INTERNAL_EIF_CNF */
enum mipc_internal_eif_cnf_tlv_enum {
    mipc_internal_eif_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_RADIO_STATE_REQ */
enum mipc_nw_get_radio_state_req_tlv_enum {
    mipc_nw_get_radio_state_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_RADIO_STATE_CNF */
enum mipc_nw_get_radio_state_cnf_tlv_enum {
    mipc_nw_get_radio_state_cnf_tlv_NONE = 0,
    /* SW radio state */
    /* type = uint8_t, refer to NW_RADIO_STATE */
    MIPC_NW_GET_RADIO_STATE_CNF_T_SW_STATE                  = 0x100,
    /* HW radio state */
    /* type = uint8_t, refer to NW_RADIO_STATE */
    MIPC_NW_GET_RADIO_STATE_CNF_T_HW_STATE                  = 0x101,
};

    /* MIPC_MSG.NW_SET_RADIO_STATE_REQ */
enum mipc_nw_set_radio_state_req_tlv_enum {
    mipc_nw_set_radio_state_req_tlv_NONE = 0,
    /* SW radio state */
    /* type = uint8_t, refer to NW_RADIO_STATE */
    MIPC_NW_SET_RADIO_STATE_REQ_T_SW_STATE                  = 0x100,
    /* reason to turn radio on/off */
    /* type = uint8_t, refer to NW_RADIO_STATE_CAUSE */
    MIPC_NW_SET_RADIO_STATE_REQ_T_CAUSE                     = 0x101,
    /* HW radio state (only can be set by intenal AP) */
    /* type = uint8_t, refer to NW_RADIO_STATE */
    MIPC_NW_SET_RADIO_STATE_REQ_T_HW_STATE                  = 0x102,
};

    /* MIPC_MSG.NW_SET_RADIO_STATE_CNF */
enum mipc_nw_set_radio_state_cnf_tlv_enum {
    mipc_nw_set_radio_state_cnf_tlv_NONE = 0,
    /* SW radio state */
    /* type = uint8_t, refer to NW_RADIO_STATE */
    MIPC_NW_SET_RADIO_STATE_CNF_T_SW_STATE                  = 0x100,
    /* HW radio state */
    /* type = uint8_t, refer to NW_RADIO_STATE */
    MIPC_NW_SET_RADIO_STATE_CNF_T_HW_STATE                  = 0x101,
};

    /* MIPC_MSG.NW_SET_REGISTER_STATE_REQ */
enum mipc_nw_set_register_state_req_tlv_enum {
    mipc_nw_set_register_state_req_tlv_NONE = 0,
    /* auto or manual */
    /* type = uint8_t, refer to NW_REGISTER_MODE */
    MIPC_NW_SET_REGISTER_STATE_REQ_T_MODE                   = 0x100,
    /* the format for operator name, not used in current stage, if register as manual mode, must give the format. */
    /* type = uint8_t */
    MIPC_NW_SET_REGISTER_STATE_REQ_T_FORMAT                 = 0x101,
    /* PLMN id, if register network in manual mode, must provide the PLMN id, for example 46001 */
    /* type = string */
    MIPC_NW_SET_REGISTER_STATE_REQ_T_OPER                   = 0x8102,
    /* Radio access technology, recommend use RAT_MODE. */
    /* type = uint8_t, refer to NW_ACT_TYPE */
    MIPC_NW_SET_REGISTER_STATE_REQ_T_ACT                    = 0x103,
    /* Used for EOPS, interger type range 0~0xFFFFFFFF */
    /* type = uint32_t */
    MIPC_NW_SET_REGISTER_STATE_REQ_T_ARFCN                  = 0x104,
    /* RAT mode, refer to AT+ERAT */
    /* type = uint8_t */
    MIPC_NW_SET_REGISTER_STATE_REQ_T_RAT_MODE               = 0x105,
    /* REQ handling mode: 0 - non block, the response will return once send the cmd; 1 - block, the response will return until the register action finished. */
    /* type = uint8_t */
    MIPC_NW_SET_REGISTER_STATE_REQ_T_BLOCK                  = 0x106,
    /* 0: default is COPS; 1: EOPS. NOTE: if this not appear, MD will according to the mode and so on to decide which at_mode used. */
    /* type = uint8_t */
    MIPC_NW_SET_REGISTER_STATE_REQ_T_CTRL_MODE              = 0x107,
};

    /* MIPC_MSG.NW_SET_REGISTER_STATE_CNF */
enum mipc_nw_set_register_state_cnf_tlv_enum {
    mipc_nw_set_register_state_cnf_tlv_NONE = 0,
    /* packet service register state */
    /* type = struct, refer to nw_reg_state */
    MIPC_NW_SET_REGISTER_STATE_CNF_T_STATE                  = 0x100,
    /* network error enum, refer to 3GPP 24.008 */
    /* type = uint16_t */
    MIPC_NW_SET_REGISTER_STATE_CNF_T_NW_ERR                 = 0x101,
    /* Currently network register mode: auto or manual */
    /* type = uint8_t, refer to NW_REGISTER_MODE */
    MIPC_NW_SET_REGISTER_STATE_CNF_T_MODE                   = 0x102,
    /* This represents the data speed for current radio technologies can support */
    /* type = uint32_t, refer to NW_DATA_SPEED */
    MIPC_NW_SET_REGISTER_STATE_CNF_T_DATA_SPEED             = 0x103,
    /* provider short name */
    /* type = string */
    MIPC_NW_SET_REGISTER_STATE_CNF_T_NW_NAME                = 0x104,
    /* A string to indicate the roaming. */
    /* type = string */
    MIPC_NW_SET_REGISTER_STATE_CNF_T_ROAMING_TEXT           = 0x105,
    /* the operation error, refer to the NW Error */
    /* type = uint16_t */
    MIPC_NW_SET_REGISTER_STATE_CNF_T_FAIL_CAUSE             = 0x106,
    /* provider long name */
    /* type = string */
    MIPC_NW_SET_REGISTER_STATE_CNF_T_NW_LONG_NAME           = 0x107,
};

    /* MIPC_MSG.NW_GET_REGISTER_STATE_REQ */
enum mipc_nw_get_register_state_req_tlv_enum {
    mipc_nw_get_register_state_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_REGISTER_STATE_CNF */
enum mipc_nw_get_register_state_cnf_tlv_enum {
    mipc_nw_get_register_state_cnf_tlv_NONE = 0,
    /* packet service register state */
    /* type = struct, refer to nw_reg_state */
    MIPC_NW_GET_REGISTER_STATE_CNF_T_STATE                  = 0x100,
    /* network error enum, refer to 3GPP 24.008 */
    /* type = uint16_t */
    MIPC_NW_GET_REGISTER_STATE_CNF_T_NW_ERR                 = 0x101,
    /* auto or manual */
    /* type = uint8_t, refer to NW_REGISTER_MODE */
    MIPC_NW_GET_REGISTER_STATE_CNF_T_MODE                   = 0x102,
    /* This represents the data speed for current radio technologies can support */
    /* type = uint32_t, refer to NW_DATA_SPEED */
    MIPC_NW_GET_REGISTER_STATE_CNF_T_DATA_SPEED             = 0x103,
    /* provider short name */
    /* type = string */
    MIPC_NW_GET_REGISTER_STATE_CNF_T_NW_NAME                = 0x104,
    /* A string to indicate the roaming. */
    /* type = string */
    MIPC_NW_GET_REGISTER_STATE_CNF_T_ROAMING_TEXT           = 0x105,
    /* the operation is fail, refer to the network error for details */
    /* type = uint16_t */
    MIPC_NW_GET_REGISTER_STATE_CNF_T_FAIL_CAUSE             = 0x106,
    /* plmn id, for example, 46001 */
    /* type = string */
    MIPC_NW_GET_REGISTER_STATE_CNF_T_PLMN_ID                = 0x107,
    /* provider long name */
    /* type = string */
    MIPC_NW_GET_REGISTER_STATE_CNF_T_NW_LONG_NAME           = 0x108,
};

    /* MIPC_MSG.NW_GET_PLMN_LIST_REQ */
enum mipc_nw_get_plmn_list_req_tlv_enum {
    mipc_nw_get_plmn_list_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_PLMN_LIST_CNF */
enum mipc_nw_get_plmn_list_cnf_tlv_enum {
    mipc_nw_get_plmn_list_cnf_tlv_NONE = 0,
    /* the number of plmn list */
    /* type = uint8_t */
    MIPC_NW_GET_PLMN_LIST_CNF_T_INFO_COUNT                  = 0x100,
    /* PLMN list element */
    /* type = struct_array, refer to nw_provider */
    MIPC_NW_GET_PLMN_LIST_CNF_T_INFO_LIST                   = 0x101,
    /* The fail cause for this operation. */
    /* type = uint16_t */
    MIPC_NW_GET_PLMN_LIST_CNF_T_FAIL_CAUSE                  = 0x102,
    /* extend plmn list element */
    /* type = struct_array, refer to nw_extend_provider */
    MIPC_NW_GET_PLMN_LIST_CNF_T_EXTEND_INFO_LIST            = 0x103,
};

    /* MIPC_MSG.NW_SET_PS_REQ */
enum mipc_nw_set_ps_req_tlv_enum {
    mipc_nw_set_ps_req_tlv_NONE = 0,
    /* attach or detach */
    /* type = uint8_t, refer to NW_PS */
    MIPC_NW_SET_PS_REQ_T_ACTION                             = 0x100,
    /* Control which used to do the ps attach/detach. The default behavior is CGATT. */
    /* type = uint8_t, refer to NW_PS_CTRL_MODE */
    MIPC_NW_SET_PS_REQ_T_CTRL_MODE                          = 0x101,
};

    /* MIPC_MSG.NW_SET_PS_CNF */
enum mipc_nw_set_ps_cnf_tlv_enum {
    mipc_nw_set_ps_cnf_tlv_NONE = 0,
    /*  */
    /* type = uint8_t, refer to NW_PS */
    MIPC_NW_SET_PS_CNF_T_TACH                               = 0x100,
    /* This represents the data speed for current radio technologies can support. */
    /* type = uint32_t, refer to NW_DATA_SPEED */
    MIPC_NW_SET_PS_CNF_T_DATA_SPEED                         = 0x101,
    /* For 5G only: sub6 or mmwave */
    /* type = uint8_t */
    MIPC_NW_SET_PS_CNF_T_NW_FREQUENCY                       = 0x102,
    /* The fail cause for this operation. */
    /* type = uint16_t */
    MIPC_NW_SET_PS_CNF_T_FAIL_CAUSE                         = 0x103,
};

    /* MIPC_MSG.NW_GET_PS_REQ */
enum mipc_nw_get_ps_req_tlv_enum {
    mipc_nw_get_ps_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_PS_CNF */
enum mipc_nw_get_ps_cnf_tlv_enum {
    mipc_nw_get_ps_cnf_tlv_NONE = 0,
    /*  */
    /* type = uint8_t, refer to NW_PS */
    MIPC_NW_GET_PS_CNF_T_TACH                               = 0x100,
    /* This represents the data speed for current radio technologies can support. */
    /* type = uint32_t, refer to NW_DATA_SPEED */
    MIPC_NW_GET_PS_CNF_T_DATA_SPEED                         = 0x101,
    /* For 5G only: sub6 or mmwave */
    /* type = uint8_t */
    MIPC_NW_GET_PS_CNF_T_NW_FREQUENCY                       = 0x102,
    /* The fail cause for this operation. */
    /* type = uint16_t */
    MIPC_NW_GET_PS_CNF_T_FAIL_CAUSE                         = 0x103,
    /* The ps data registration state. */
    /* type = struct, refer to nw_ps_reg_info */
    MIPC_NW_GET_PS_CNF_T_REG_INFO                           = 0x104,
    /* The cell type. */
    /* type = uint8_t, refer to NW_CELL_TYPE */
    MIPC_NW_GET_PS_CNF_T_CELL_TYPE                          = 0x105,
    /* The cell info: mipc_nw_gsm_cell_struct4 and so on. NOTE: WHEN CELL TYPE IS CELL_TYPE_NSA_EXT, CELL INFO IS THE LTE CELL */
    /* type = struct, refer to nw_gsm_cell */
    MIPC_NW_GET_PS_CNF_T_CELL_INFO                          = 0x8106,
    /* The nr cell info: mipc_nw_nr_cell_struct4. NOTE: JUST VALID WHEN CELL_TYPE IS CELL_TYPE_NSA_EXT, AND CELL_INFO IS LTE CELL. */
    /* type = struct, refer to nw_nr_cell */
    MIPC_NW_GET_PS_CNF_T_NSA_EXT_CELL_INFO                  = 0x8107,
};

    /* MIPC_MSG.NW_SET_SIGNAL_REQ */
enum mipc_nw_set_signal_req_tlv_enum {
    mipc_nw_set_signal_req_tlv_NONE = 0,
    /* The signal report interval, the default value is 5 seconds. */
    /* type = uint32_t */
    MIPC_NW_SET_SIGNAL_REQ_T_SIGNAL_STRENGTH_INTERVAL       = 0x100,
    /* The threshold for rssi, the default value is 5. */
    /* type = uint32_t */
    MIPC_NW_SET_SIGNAL_REQ_T_RSSI_THRESHOLD                 = 0x101,
    /* The threshold for err rate, the default value is 0. */
    /* type = uint32_t */
    MIPC_NW_SET_SIGNAL_REQ_T_ERR_RATE_THRESHOLD             = 0x102,
    /* The threshold for rsrp, the default value is 2 db. */
    /* type = uint32_t */
    MIPC_NW_SET_SIGNAL_REQ_T_RSRP_THRESHOLD                 = 0x103,
    /* The threshold for snr, the default value is 0 db. */
    /* type = uint32_t */
    MIPC_NW_SET_SIGNAL_REQ_T_SNR_THRESHOLD                  = 0x104,
    /* The value 1 indicates the threshold is used for RAW signal info, this means the rsrp in qdbm unit and snr in qdb unit. The default value is 0, use the dbm and db unit. */
    /* type = uint8_t, refer to NW_SIGNAL_THRESHOLD_MODE */
    MIPC_NW_SET_SIGNAL_REQ_T_THRESHOLD_MODE                 = 0x105,
};

    /* MIPC_MSG.NW_SET_SIGNAL_CNF */
enum mipc_nw_set_signal_cnf_tlv_enum {
    mipc_nw_set_signal_cnf_tlv_NONE = 0,
    /* Current setting for signal report interval, the default value is 5 seconds. */
    /* type = uint32_t */
    MIPC_NW_SET_SIGNAL_CNF_T_SIGNAL_STRENGTH_INTERVAL       = 0x104,
    /* Current setting for rssi threshold, the default value is 5. */
    /* type = uint32_t */
    MIPC_NW_SET_SIGNAL_CNF_T_RSSI_THRESHOLD                 = 0x105,
    /* Current setting for err rate threshold, the default value is 0. */
    /* type = uint32_t */
    MIPC_NW_SET_SIGNAL_CNF_T_ERR_RATE_THRESHOLD             = 0x106,
    /* Current setting for rsrp threshold, the default value is 2 db. */
    /* type = uint32_t */
    MIPC_NW_SET_SIGNAL_CNF_T_RSRP_THRESHOLD                 = 0x107,
    /* Current setting for snr threshold, the default value is 0 db. */
    /* type = uint32_t */
    MIPC_NW_SET_SIGNAL_CNF_T_SNR_THRESHOLD                  = 0x108,
    /* The fail cause for this operation. */
    /* type = uint16_t */
    MIPC_NW_SET_SIGNAL_CNF_T_FAIL_CAUSE                     = 0x109,
    /* Signal type, GSM/UMTS/LTE/NR/NSA. Note: When the type is NSA, maybe contains LTE and(or) NR signal info. */
    /* type = uint8_t, refer to NW_SIGNAL_TYPE */
    MIPC_NW_SET_SIGNAL_CNF_T_SIGNAL_TYPE                    = 0x10A,
    /* GSM signal strength. */
    /* type = struct, refer to nw_gsm_signal_strength */
    MIPC_NW_SET_SIGNAL_CNF_T_GSM_SIGNAL                     = 0x10B,
    /* UMTS signal strength. */
    /* type = struct, refer to nw_umts_signal_strength */
    MIPC_NW_SET_SIGNAL_CNF_T_UMTS_SIGNAL                    = 0x10C,
    /* LTE signal strength. */
    /* type = struct, refer to nw_lte_signal_strength */
    MIPC_NW_SET_SIGNAL_CNF_T_LTE_SIGNAL                     = 0x10D,
    /* NR signal strength. */
    /* type = struct, refer to nw_nr_signal_strength */
    MIPC_NW_SET_SIGNAL_CNF_T_NR_SIGNAL                      = 0x10E,
    /* The raw signal data, parse from +ECSQ. */
    /* type = struct_array, refer to nw_raw_signal_info */
    MIPC_NW_SET_SIGNAL_CNF_T_RAW_SIGNAL_INFO_LIST           = 0x10F,
    /* The raw signal info count: when in NSA, the count is 2, and others is 1 */
    /* type = uint8_t */
    MIPC_NW_SET_SIGNAL_CNF_T_RAW_SIGNAL_INFO_COUNT          = 0x110,
    /* CDMA signal strength. */
    /* type = struct, refer to nw_cdma_signal_strength */
    MIPC_NW_SET_SIGNAL_CNF_T_CDMA_SIGNAL                    = 0x111,
};

    /* MIPC_MSG.NW_GET_SIGNAL_REQ */
enum mipc_nw_get_signal_req_tlv_enum {
    mipc_nw_get_signal_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_SIGNAL_CNF */
enum mipc_nw_get_signal_cnf_tlv_enum {
    mipc_nw_get_signal_cnf_tlv_NONE = 0,
    /* Current setting for signal reporting interva, the default value is 5 seconds. */
    /* type = uint32_t */
    MIPC_NW_GET_SIGNAL_CNF_T_SIGNAL_STRENGTH_INTERVAL       = 0x104,
    /* Current rssi threshold setting for signal reporting, the default value is 5. */
    /* type = uint32_t */
    MIPC_NW_GET_SIGNAL_CNF_T_RSSI_THRESHOLD                 = 0x105,
    /* Current err rate threshold setting for signal reporting, the default value is 0. */
    /* type = uint32_t */
    MIPC_NW_GET_SIGNAL_CNF_T_ERR_RATE_THRESHOLD             = 0x106,
    /* Current rsrp threshold setting for signal reporting, the default value is 2 db. */
    /* type = uint32_t */
    MIPC_NW_GET_SIGNAL_CNF_T_RSRP_THRESHOLD                 = 0x107,
    /* Current snr threshold setting for signal reporting, the default value is 0 db. */
    /* type = uint32_t */
    MIPC_NW_GET_SIGNAL_CNF_T_SNR_THRESHOLD                  = 0x108,
    /* The fail cause for operation. */
    /* type = uint16_t */
    MIPC_NW_GET_SIGNAL_CNF_T_FAIL_CAUSE                     = 0x109,
    /* Signal type, GSM/UMTS/LTE/NR/NSA. Note: When the type is NSA, maybe contains LTE and(or) NR signal info. */
    /* type = uint8_t, refer to NW_SIGNAL_TYPE */
    MIPC_NW_GET_SIGNAL_CNF_T_SIGNAL_TYPE                    = 0x10A,
    /* GSM signal strength. */
    /* type = struct, refer to nw_gsm_signal_strength */
    MIPC_NW_GET_SIGNAL_CNF_T_GSM_SIGNAL                     = 0x10B,
    /* UMTS signal strength. */
    /* type = struct, refer to nw_umts_signal_strength */
    MIPC_NW_GET_SIGNAL_CNF_T_UMTS_SIGNAL                    = 0x10C,
    /* LTE signal strength. */
    /* type = struct, refer to nw_lte_signal_strength */
    MIPC_NW_GET_SIGNAL_CNF_T_LTE_SIGNAL                     = 0x10D,
    /* NR signal strength. */
    /* type = struct, refer to nw_nr_signal_strength */
    MIPC_NW_GET_SIGNAL_CNF_T_NR_SIGNAL                      = 0x10E,
    /* The raw signal data, parse from +ECSQ. */
    /* type = struct_array, refer to nw_raw_signal_info */
    MIPC_NW_GET_SIGNAL_CNF_T_RAW_SIGNAL_INFO_LIST           = 0x10F,
    /* The raw signal info count: when in NSA, the count is 2, and others is 1 */
    /* type = uint8_t */
    MIPC_NW_GET_SIGNAL_CNF_T_RAW_SIGNAL_INFO_COUNT          = 0x110,
    /* CDMA signal strength. */
    /* type = struct, refer to nw_cdma_signal_strength */
    MIPC_NW_GET_SIGNAL_CNF_T_CDMA_SIGNAL                    = 0x111,
};

    /* MIPC_MSG.NW_GET_PREFERRED_PROVIDER_REQ */
enum mipc_nw_get_preferred_provider_req_tlv_enum {
    mipc_nw_get_preferred_provider_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_PREFERRED_PROVIDER_CNF */
enum mipc_nw_get_preferred_provider_cnf_tlv_enum {
    mipc_nw_get_preferred_provider_cnf_tlv_NONE = 0,
    /* The provider list length. */
    /* type = uint8_t */
    MIPC_NW_GET_PREFERRED_PROVIDER_CNF_T_COUNT              = 0x100,
    /*  */
    /* type = struct_array, refer to nw_provider */
    MIPC_NW_GET_PREFERRED_PROVIDER_CNF_T_LIST               = 0x101,
    /* The fail cause for current operation. */
    /* type = uint16_t */
    MIPC_NW_GET_PREFERRED_PROVIDER_CNF_T_FAIL_CAUSE         = 0x102,
};

    /* MIPC_MSG.NW_SET_PREFERRED_PROVIDER_REQ */
enum mipc_nw_set_preferred_provider_req_tlv_enum {
    mipc_nw_set_preferred_provider_req_tlv_NONE = 0,
    /* The provider list length. */
    /* type = uint8_t */
    MIPC_NW_SET_PREFERRED_PROVIDER_REQ_T_COUNT              = 0x100,
    /*  */
    /* type = struct_array, refer to nw_provider */
    MIPC_NW_SET_PREFERRED_PROVIDER_REQ_T_LIST               = 0x101,
};

    /* MIPC_MSG.NW_SET_PREFERRED_PROVIDER_CNF */
enum mipc_nw_set_preferred_provider_cnf_tlv_enum {
    mipc_nw_set_preferred_provider_cnf_tlv_NONE = 0,
    /* The provider list length. */
    /* type = uint8_t */
    MIPC_NW_SET_PREFERRED_PROVIDER_CNF_T_COUNT              = 0x100,
    /*  */
    /* type = struct_array, refer to nw_provider */
    MIPC_NW_SET_PREFERRED_PROVIDER_CNF_T_LIST               = 0x101,
    /* The fail cause for current operation. */
    /* type = uint16_t */
    MIPC_NW_SET_PREFERRED_PROVIDER_CNF_T_FAIL_CAUSE         = 0x102,
};

    /* MIPC_MSG.NW_SET_HOME_PROVIDER_REQ */
enum mipc_nw_set_home_provider_req_tlv_enum {
    mipc_nw_set_home_provider_req_tlv_NONE = 0,
    /*  */
    /* type = struct, refer to nw_provider */
    MIPC_NW_SET_HOME_PROVIDER_REQ_T_PROVIDER                = 0x100,
};

    /* MIPC_MSG.NW_SET_HOME_PROVIDER_CNF */
enum mipc_nw_set_home_provider_cnf_tlv_enum {
    mipc_nw_set_home_provider_cnf_tlv_NONE = 0,
    /*  */
    /* type = struct, refer to nw_provider */
    MIPC_NW_SET_HOME_PROVIDER_CNF_T_PROVIDER                = 0x8100,
    /* The fail cause for current operation. */
    /* type = uint16_t */
    MIPC_NW_SET_HOME_PROVIDER_CNF_T_FAIL_CAUSE              = 0x101,
};

    /* MIPC_MSG.NW_GET_HOME_PROVIDER_REQ */
enum mipc_nw_get_home_provider_req_tlv_enum {
    mipc_nw_get_home_provider_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_HOME_PROVIDER_CNF */
enum mipc_nw_get_home_provider_cnf_tlv_enum {
    mipc_nw_get_home_provider_cnf_tlv_NONE = 0,
    /*  */
    /* type = struct, refer to nw_provider */
    MIPC_NW_GET_HOME_PROVIDER_CNF_T_PROVIDER                = 0x8100,
    /* The fail cause for current operation. */
    /* type = uint16_t */
    MIPC_NW_GET_HOME_PROVIDER_CNF_T_FAIL_CAUSE              = 0x101,
};

    /* MIPC_MSG.NW_GET_IA_STATUS_REQ */
enum mipc_nw_get_ia_status_req_tlv_enum {
    mipc_nw_get_ia_status_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_IA_STATUS_CNF */
enum mipc_nw_get_ia_status_cnf_tlv_enum {
    mipc_nw_get_ia_status_cnf_tlv_NONE = 0,
    /* APN name */
    /* type = string */
    MIPC_NW_GET_IA_STATUS_CNF_T_APN                         = 0x100,
    /* The RAT info. */
    /* type = uint8_t */
    MIPC_NW_GET_IA_STATUS_CNF_T_RAT                         = 0x101,
    /*  */
    /* type = uint8_t, refer to APN_PDP_TYPE */
    MIPC_NW_GET_IA_STATUS_CNF_T_PDP_TYPE                    = 0x102,
    /*  */
    /* type = uint8_t, refer to APN_AUTH_TYPE */
    MIPC_NW_GET_IA_STATUS_CNF_T_AUTH_TYPE                   = 0x103,
    /* User id. */
    /* type = string */
    MIPC_NW_GET_IA_STATUS_CNF_T_USERID                      = 0x8104,
    /* Password for the user id. */
    /* type = string */
    MIPC_NW_GET_IA_STATUS_CNF_T_PASSWORD                    = 0x8105,
};

    /* MIPC_MSG.NW_GET_NITZ_REQ */
enum mipc_nw_get_nitz_req_tlv_enum {
    mipc_nw_get_nitz_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_NITZ_CNF */
enum mipc_nw_get_nitz_cnf_tlv_enum {
    mipc_nw_get_nitz_cnf_tlv_NONE = 0,
    /*  */
    /* type = struct, refer to nw_nitz_info */
    MIPC_NW_GET_NITZ_CNF_T_INFO                             = 0x100,
};

    /* MIPC_MSG.NW_SET_IDLE_HINT_REQ */
enum mipc_nw_set_idle_hint_req_tlv_enum {
    mipc_nw_set_idle_hint_req_tlv_NONE = 0,
    /* Control the set operation. */
    /* type = uint8_t, refer to NW_FAST_DORMANCY */
    MIPC_NW_SET_IDLE_HINT_REQ_T_STATUS                      = 0x100,
    /* ID(0~255) of the timer to be set when STATUS is SET_TIMER; Indicate screen is on(1) or off(0) when STATUS is SCREEN_STATUS. */
    /* type = uint32_t */
    MIPC_NW_SET_IDLE_HINT_REQ_T_PARAM_1                     = 0x101,
    /* Just used when STATUS is SET_TIMER, it represents the value(0~65535) of timer to be set in unit 0.1 second. */
    /* type = uint32_t */
    MIPC_NW_SET_IDLE_HINT_REQ_T_PARAM_2                     = 0x102,
};

    /* MIPC_MSG.NW_SET_IDLE_HINT_CNF */
enum mipc_nw_set_idle_hint_cnf_tlv_enum {
    mipc_nw_set_idle_hint_cnf_tlv_NONE = 0,
    /*  */
    /* type = uint8_t, refer to NW_FAST_DORMANCY */
    MIPC_NW_SET_IDLE_HINT_CNF_T_STATUS                      = 0x100,
    /* The fail cause for current operation. */
    /* type = uint16_t */
    MIPC_NW_SET_IDLE_HINT_CNF_T_FAIL_CAUSE                  = 0x101,
};

    /* MIPC_MSG.NW_GET_IDLE_HINT_REQ */
enum mipc_nw_get_idle_hint_req_tlv_enum {
    mipc_nw_get_idle_hint_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_IDLE_HINT_CNF */
enum mipc_nw_get_idle_hint_cnf_tlv_enum {
    mipc_nw_get_idle_hint_cnf_tlv_NONE = 0,
    /*  */
    /* type = uint8_t, refer to NW_FAST_DORMANCY */
    MIPC_NW_GET_IDLE_HINT_CNF_T_STATUS                      = 0x100,
    /* The fail cause for current operation. */
    /* type = uint16_t */
    MIPC_NW_GET_IDLE_HINT_CNF_T_FAIL_CAUSE                  = 0x101,
    /* 0: current network doesn't support R8 Dormancy; 1: current network supports R8 Fast Dormancy. */
    /* type = uint8_t */
    MIPC_NW_GET_IDLE_HINT_CNF_T_R8_FD_STATUS                = 0x102,
};

    /* MIPC_MSG.NW_GET_BASE_STATIONS_REQ */
enum mipc_nw_get_base_stations_req_tlv_enum {
    mipc_nw_get_base_stations_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_BASE_STATIONS_CNF */
enum mipc_nw_get_base_stations_cnf_tlv_enum {
    mipc_nw_get_base_stations_cnf_tlv_NONE = 0,
    /* The gsm cell list length. */
    /* type = uint32_t */
    MIPC_NW_GET_BASE_STATIONS_CNF_T_GSM_CELL_COUNT          = 0x100,
    /*  */
    /* type = struct_array, refer to nw_gsm_cell */
    MIPC_NW_GET_BASE_STATIONS_CNF_T_GSM_CELL_LIST           = 0x8101,
    /* The umts cell list length. */
    /* type = uint32_t */
    MIPC_NW_GET_BASE_STATIONS_CNF_T_UMTS_CELL_COUNT         = 0x102,
    /*  */
    /* type = struct_array, refer to nw_umts_cell */
    MIPC_NW_GET_BASE_STATIONS_CNF_T_UMTS_CELL_LIST          = 0x8103,
    /* The tdscdma cell list length. */
    /* type = uint32_t */
    MIPC_NW_GET_BASE_STATIONS_CNF_T_TDSCDMA_CELL_COUNT      = 0x104,
    /*  */
    /* type = struct_array, refer to nw_tdscdma_cell */
    MIPC_NW_GET_BASE_STATIONS_CNF_T_TDSCDMA_CELL_LIST       = 0x8105,
    /* The lte cell list length. */
    /* type = uint32_t */
    MIPC_NW_GET_BASE_STATIONS_CNF_T_LTE_CELL_COUNT          = 0x106,
    /*  */
    /* type = struct_array, refer to nw_lte_cell */
    MIPC_NW_GET_BASE_STATIONS_CNF_T_LTE_CELL_LIST           = 0x8107,
    /* The cdma cell list length. */
    /* type = uint32_t */
    MIPC_NW_GET_BASE_STATIONS_CNF_T_CDMA_CELL_COUNT         = 0x108,
    /*  */
    /* type = struct_array, refer to nw_cdma_cell */
    MIPC_NW_GET_BASE_STATIONS_CNF_T_CDMA_CELL_LIST          = 0x8109,
    /* The nr cell list length. */
    /* type = uint32_t */
    MIPC_NW_GET_BASE_STATIONS_CNF_T_NR_CELL_COUNT           = 0x10A,
    /*  */
    /* type = struct_array, refer to nw_nr_cell */
    MIPC_NW_GET_BASE_STATIONS_CNF_T_NR_CELL_LIST            = 0x810B,
    /* The fail cause for current operation. */
    /* type = uint16_t */
    MIPC_NW_GET_BASE_STATIONS_CNF_T_FAIL_CAUSE              = 0x10C,
};

    /* MIPC_MSG.NW_GET_LOCATION_INFO_REQ */
enum mipc_nw_get_location_info_req_tlv_enum {
    mipc_nw_get_location_info_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_LOCATION_INFO_CNF */
enum mipc_nw_get_location_info_cnf_tlv_enum {
    mipc_nw_get_location_info_cnf_tlv_NONE = 0,
    /*  */
    /* type = struct, refer to nw_location_info */
    MIPC_NW_GET_LOCATION_INFO_CNF_T_INFO                    = 0x8100,
    /* The fail cause for current operation. */
    /* type = uint16_t */
    MIPC_NW_GET_LOCATION_INFO_CNF_T_FAIL_CAUSE              = 0x101,
};

    /* MIPC_MSG.NW_SET_RAT_REQ */
enum mipc_nw_set_rat_req_tlv_enum {
    mipc_nw_set_rat_req_tlv_NONE = 0,
    /* The rat info. This parameter is for compability with previous version. Please use the BIT_RAT first */
    /* type = uint8_t */
    MIPC_NW_SET_RAT_REQ_T_RAT                               = 0x100,
    /* The perfer rat info. */
    /* type = uint8_t */
    MIPC_NW_SET_RAT_REQ_T_PREFER_RAT                        = 0x101,
    /* The rat info by bit. bit0: GSM, bit1: UMTS, bit2: LTE, bit3: NR, bit4: C2K. */
    /* type = uint32_t, refer to NW_BIT_RAT */
    MIPC_NW_SET_RAT_REQ_T_BIT_RAT                           = 0x102,
};

    /* MIPC_MSG.NW_SET_RAT_CNF */
enum mipc_nw_set_rat_cnf_tlv_enum {
    mipc_nw_set_rat_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_PROVIDER_NAME_REQ */
enum mipc_nw_get_provider_name_req_tlv_enum {
    mipc_nw_get_provider_name_req_tlv_NONE = 0,
    /* plmn of operator NW */
    /* type = string */
    MIPC_NW_GET_PROVIDER_NAME_REQ_T_PLMN_ID                 = 0x100,
    /* lac */
    /* type = uint32_t */
    MIPC_NW_GET_PROVIDER_NAME_REQ_T_LAC                     = 0x101,
    /* The default value is 0 which means just return the NW_NAME and NW_LONG_NAME; when set to 1, it will try to return all the names info(EONS/NITZ/TS25) if it exist. */
    /* type = uint8_t */
    MIPC_NW_GET_PROVIDER_NAME_REQ_T_OPTION                  = 0x102,
};

    /* MIPC_MSG.NW_GET_PROVIDER_NAME_CNF */
enum mipc_nw_get_provider_name_cnf_tlv_enum {
    mipc_nw_get_provider_name_cnf_tlv_NONE = 0,
    /* plmn of operator NW */
    /* type = string */
    MIPC_NW_GET_PROVIDER_NAME_CNF_T_PLMN_ID                 = 0x8100,
    /* lac */
    /* type = uint32_t */
    MIPC_NW_GET_PROVIDER_NAME_CNF_T_LAC                     = 0x8101,
    /* provider name, The short name is return according to following priority: EONS > NITZ > TS25 */
    /* type = string */
    MIPC_NW_GET_PROVIDER_NAME_CNF_T_NW_NAME                 = 0x8102,
    /* provider name, The long name is return according to following priority: EONS > NITZ > TS25 */
    /* type = string */
    MIPC_NW_GET_PROVIDER_NAME_CNF_T_NW_NAME_LONG            = 0x8103,
    /* The EONS name for the plmn. */
    /* type = struct, refer to nw_name_pair */
    MIPC_NW_GET_PROVIDER_NAME_CNF_T_EONS_NAME               = 0x8104,
    /* The NITZ name for the plmn. */
    /* type = struct, refer to nw_name_pair */
    MIPC_NW_GET_PROVIDER_NAME_CNF_T_NITZ_NAME               = 0x8105,
    /* The TS25 short name for the plmn. */
    /* type = struct, refer to nw_name_pair */
    MIPC_NW_GET_PROVIDER_NAME_CNF_T_TS25_NAME               = 0x8106,
};

    /* MIPC_MSG.NW_GET_RAT_REQ */
enum mipc_nw_get_rat_req_tlv_enum {
    mipc_nw_get_rat_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_RAT_CNF */
enum mipc_nw_get_rat_cnf_tlv_enum {
    mipc_nw_get_rat_cnf_tlv_NONE = 0,
    /* Access technology of current register PLMN. */
    /* type = uint8_t */
    MIPC_NW_GET_RAT_CNF_T_ACT                               = 0x100,
    /* Indicates GPRS status: 0: GPRS; 1: EDGE. */
    /* type = uint8_t */
    MIPC_NW_GET_RAT_CNF_T_GPRS_STATUS                       = 0x101,
    /* RAT mode setting of MS. */
    /* type = uint8_t */
    MIPC_NW_GET_RAT_CNF_T_RAT_MODE                          = 0x102,
    /* Discarded, please use AT+EPRATL to set prefer RAT list. */
    /* type = uint8_t */
    MIPC_NW_GET_RAT_CNF_T_PREFER_RAT                        = 0x103,
    /* 0: unlock ERAT; 1: lock ERAT, i.e. cannot set RAT */
    /* type = uint8_t */
    MIPC_NW_GET_RAT_CNF_T_LOCK                              = 0x104,
    /* RAT mode setting of MS. bit0: GSM, bit1: UMTS, bit2: LTE, bit3: NR, bit4: C2K */
    /* type = uint32_t, refer to NW_BIT_RAT */
    MIPC_NW_GET_RAT_CNF_T_BIT_RAT                           = 0x105,
    /* the capability of current protocol. bit0: GSM, bit1: UMTS, bit2: LTE, bit3: NR, bit4: C2K */
    /* type = uint32_t */
    MIPC_NW_GET_RAT_CNF_T_RADIO_CAPABILITY                  = 0x106,
};

    /* MIPC_MSG.NW_SET_NR_REQ */
enum mipc_nw_set_nr_req_tlv_enum {
    mipc_nw_set_nr_req_tlv_NONE = 0,
    /* 1: LTE ONLY(disable NSA+SA); 3: SA ONLY; 5: NSA ONLY; 7: NSA+SA. */
    /* type = uint8_t */
    MIPC_NW_SET_NR_REQ_T_NR_OPT                             = 0x100,
    /* Control if need to do the local release. */
    /* type = uint8_t, refer to NW_VG_OPTION_OPERATION */
    MIPC_NW_SET_NR_REQ_T_ACT_OPERATION                      = 0x101,
};

    /* MIPC_MSG.NW_SET_NR_CNF */
enum mipc_nw_set_nr_cnf_tlv_enum {
    mipc_nw_set_nr_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_CS_REQ */
enum mipc_nw_get_cs_req_tlv_enum {
    mipc_nw_get_cs_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_CS_CNF */
enum mipc_nw_get_cs_cnf_tlv_enum {
    mipc_nw_get_cs_cnf_tlv_NONE = 0,
    /* CS registration info. */
    /* type = struct, refer to nw_cs_reg_info */
    MIPC_NW_GET_CS_CNF_T_REG_INFO                           = 0x8100,
    /* The cell type. */
    /* type = uint8_t, refer to NW_CELL_TYPE */
    MIPC_NW_GET_CS_CNF_T_CELL_TYPE                          = 0x101,
    /* The cell info: mipc_nw_gsm_cell_struct4 and so on. */
    /* type = struct, refer to nw_gsm_cell */
    MIPC_NW_GET_CS_CNF_T_CELL_INFO                          = 0x8102,
};

    /* MIPC_MSG.NW_GET_BAND_MODE_REQ */
enum mipc_nw_get_band_mode_req_tlv_enum {
    mipc_nw_get_band_mode_req_tlv_NONE = 0,
    /* NW_BAND_OPTION_CURRENT_SETTING indicates to get current setting bands info; NW_BAND_OPTION_SYSTEM_SUPPORT indicates to return all system supports bands. If without this OPTION, the default option is NW_BAND_OPTION_CURRENT_SETTING */
    /* type = uint8_t, refer to NW_BAND_OPTION */
    MIPC_NW_GET_BAND_MODE_REQ_T_OPTION                      = 0x100,
};

    /* MIPC_MSG.NW_GET_BAND_MODE_CNF */
enum mipc_nw_get_band_mode_cnf_tlv_enum {
    mipc_nw_get_band_mode_cnf_tlv_NONE = 0,
    /* uint32_t, A bitmap that represents which GSM bands are supported */
    /* type = bitmap, refer to SYS_CAP_GSM_BAND */
    MIPC_NW_GET_BAND_MODE_CNF_T_GSM_BAND                    = 0x100,
    /* uint32_t, A bitmap that represents which UMTS bands are supported */
    /* type = bitmap, refer to SYS_CAP_UMTS_BAND */
    MIPC_NW_GET_BAND_MODE_CNF_T_UMTS_BAND                   = 0x101,
    /* A bitmap that represents which LTE bands are supported */
    /* type = struct, refer to sys_lte_band */
    MIPC_NW_GET_BAND_MODE_CNF_T_LTE_BAND                    = 0x102,
    /* A bitmap that represents which NR bands are supported */
    /* type = struct, refer to sys_nr_band */
    MIPC_NW_GET_BAND_MODE_CNF_T_NR_BAND                     = 0x103,
    /* A bitmap that represents which NR NSA bands are supported. If nr_sa_band equals to nr_nsa_band, nr_nsa_band_won't present. */
    /* type = struct, refer to sys_nr_band */
    MIPC_NW_GET_BAND_MODE_CNF_T_NR_NSA_BAND                 = 0x104,
};

    /* MIPC_MSG.NW_SET_BAND_MODE_REQ */
enum mipc_nw_set_band_mode_req_tlv_enum {
    mipc_nw_set_band_mode_req_tlv_NONE = 0,
    /* uint32_t, A bitmap that represents which GSM bands are supported */
    /* type = bitmap, refer to SYS_CAP_GSM_BAND */
    MIPC_NW_SET_BAND_MODE_REQ_T_GSM_BAND                    = 0x100,
    /* uint32_t, A bitmap that represents which UMTS bands are supported */
    /* type = bitmap, refer to SYS_CAP_UMTS_BAND */
    MIPC_NW_SET_BAND_MODE_REQ_T_UMTS_BAND                   = 0x101,
    /* A bitmap that represents which LTE bands are supported */
    /* type = struct, refer to sys_lte_band */
    MIPC_NW_SET_BAND_MODE_REQ_T_LTE_BAND                    = 0x102,
    /* A bitmap that represents which NR bands are supported */
    /* type = struct, refer to sys_nr_band */
    MIPC_NW_SET_BAND_MODE_REQ_T_NR_BAND                     = 0x103,
    /* A bitmap that represents which NR NSA bands are supported. If nr_nsa_band not present, set both nr_sa_band and nr_nsa_band to nr_band. */
    /* type = struct, refer to sys_nr_band */
    MIPC_NW_SET_BAND_MODE_REQ_T_NR_NSA_BAND                 = 0x104,
};

    /* MIPC_MSG.NW_SET_BAND_MODE_CNF */
enum mipc_nw_set_band_mode_cnf_tlv_enum {
    mipc_nw_set_band_mode_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_SET_CHANNEL_LOCK_REQ */
enum mipc_nw_set_channel_lock_req_tlv_enum {
    mipc_nw_set_channel_lock_req_tlv_NONE = 0,
    /* The list length for info list. */
    /* type = uint16_t */
    MIPC_NW_SET_CHANNEL_LOCK_REQ_T_CH_LOCK_INFO_LIST_COUNT  = 0x100,
    /* Lock channel information. */
    /* type = struct_array, refer to nw_channel_lock_info */
    MIPC_NW_SET_CHANNEL_LOCK_REQ_T_CH_LOCK_INFO_LIST        = 0x101,
    /* Lock channel information. */
    /* type = struct, refer to nw_channel_lock_info_v1 */
    MIPC_NW_SET_CHANNEL_LOCK_REQ_T_CH_LOCK_INFO_LIST_V1     = 0x102,
};

    /* MIPC_MSG.NW_SET_CHANNEL_LOCK_CNF */
enum mipc_nw_set_channel_lock_cnf_tlv_enum {
    mipc_nw_set_channel_lock_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_CHANNEL_LOCK_REQ */
enum mipc_nw_get_channel_lock_req_tlv_enum {
    mipc_nw_get_channel_lock_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_CHANNEL_LOCK_CNF */
enum mipc_nw_get_channel_lock_cnf_tlv_enum {
    mipc_nw_get_channel_lock_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_SET_ABORT_PLMN_LIST_SEARCH_REQ */
enum mipc_nw_set_abort_plmn_list_search_req_tlv_enum {
    mipc_nw_set_abort_plmn_list_search_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_SET_ABORT_PLMN_LIST_SEARCH_CNF */
enum mipc_nw_set_abort_plmn_list_search_cnf_tlv_enum {
    mipc_nw_set_abort_plmn_list_search_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_POL_CAPABILITY_REQ */
enum mipc_nw_get_pol_capability_req_tlv_enum {
    mipc_nw_get_pol_capability_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_POL_CAPABILITY_CNF */
enum mipc_nw_get_pol_capability_cnf_tlv_enum {
    mipc_nw_get_pol_capability_cnf_tlv_NONE = 0,
    /* type = struct, refer to nw_pol_info */
    MIPC_NW_GET_POL_CAPABILITY_CNF_T_POL_INFO               = 0x100,
};

    /* MIPC_MSG.NW_SET_PREFER_RAT_REQ */
enum mipc_nw_set_prefer_rat_req_tlv_enum {
    mipc_nw_set_prefer_rat_req_tlv_NONE = 0,
    /* The length for RAT_LIST, the max len is 4 */
    /* type = uint8_t */
    MIPC_NW_SET_PREFER_RAT_REQ_T_RAT_NUM                    = 0x100,
    /* The RAT selection list with priority: rat_list[0] > rat_list[1] > rat_list[2] > rat_list[3], the value can refer to NW_PREFER_RAT_TYPE. */
    /* type = byte_array, refer to NW_PREFER_RAT_TYPE */
    MIPC_NW_SET_PREFER_RAT_REQ_T_RAT_LIST                   = 0x101,
};

    /* MIPC_MSG.NW_SET_PREFER_RAT_CNF */
enum mipc_nw_set_prefer_rat_cnf_tlv_enum {
    mipc_nw_set_prefer_rat_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_SET_LTE_CARRIER_AGGREGATION_SWITCH_REQ */
enum mipc_nw_set_lte_carrier_aggregation_switch_req_tlv_enum {
    mipc_nw_set_lte_carrier_aggregation_switch_req_tlv_NONE = 0,
    /* enable/disable lte carrier aggregation switch */
    /* type = uint8_t, refer to NW_LTE_CARRIER_ARRREGATION_SWITCH */
    MIPC_NW_SET_LTE_CARRIER_AGGREGATION_SWITCH_REQ_T_STATUS = 0x100,
};

    /* MIPC_MSG.NW_SET_LTE_CARRIER_AGGREGATION_SWITCH_CNF */
enum mipc_nw_set_lte_carrier_aggregation_switch_cnf_tlv_enum {
    mipc_nw_set_lte_carrier_aggregation_switch_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_SET_PS_CS_REGISTRATION_STATE_ROAMING_TYPE_REQ */
enum mipc_nw_set_ps_cs_registration_state_roaming_type_req_tlv_enum {
    mipc_nw_set_ps_cs_registration_state_roaming_type_req_tlv_NONE = 0,
    /* type = struct, refer to nw_ps_cs_reg_roaming_info */
    MIPC_NW_SET_PS_CS_REGISTRATION_STATE_ROAMING_TYPE_REQ_T_PS_CS_REG_ROAMING_INFO = 0x100,
};

    /* MIPC_MSG.NW_SET_PS_CS_REGISTRATION_STATE_ROAMING_TYPE_CNF */
enum mipc_nw_set_ps_cs_registration_state_roaming_type_cnf_tlv_enum {
    mipc_nw_set_ps_cs_registration_state_roaming_type_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_LTE_CARRIER_AGGREGATION_SWITCH_REQ */
enum mipc_nw_get_lte_carrier_aggregation_switch_req_tlv_enum {
    mipc_nw_get_lte_carrier_aggregation_switch_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_LTE_CARRIER_AGGREGATION_SWITCH_CNF */
enum mipc_nw_get_lte_carrier_aggregation_switch_cnf_tlv_enum {
    mipc_nw_get_lte_carrier_aggregation_switch_cnf_tlv_NONE = 0,
    /*  */
    /* type = uint8_t, refer to NW_LTE_CARRIER_ARRREGATION_SWITCH */
    MIPC_NW_GET_LTE_CARRIER_AGGREGATION_SWITCH_CNF_T_STATUS = 0x100,
};

    /* MIPC_MSG.NW_CELL_MEASUREMENT_REQ */
enum mipc_nw_cell_measurement_req_tlv_enum {
    mipc_nw_cell_measurement_req_tlv_NONE = 0,
    /* 1: start cell measurement; 0: abort cell measurement */
    /* type = uint8_t */
    MIPC_NW_CELL_MEASUREMENT_REQ_T_ACTION                   = 0x100,
    /* A bitmap that represents which LTE bands are measurement. */
    /* type = struct, refer to sys_lte_band */
    MIPC_NW_CELL_MEASUREMENT_REQ_T_LTE_BAND                 = 0x101,
    /* A bitmap that represents which NR bands are measurement. */
    /* type = struct, refer to sys_nr_band */
    MIPC_NW_CELL_MEASUREMENT_REQ_T_NR_BAND                  = 0x102,
    /* Scan type for cell measurement. */
    /* type = uint8_t, refer to NW_CELLMEASUREMENT_SCAN_TYPE */
    MIPC_NW_CELL_MEASUREMENT_REQ_T_SCAN_TYPE                = 0x103,
};

    /* MIPC_MSG.NW_CELL_MEASUREMENT_CNF */
enum mipc_nw_cell_measurement_cnf_tlv_enum {
    mipc_nw_cell_measurement_cnf_tlv_NONE = 0,
    /* The cell count for the cell measurement. */
    /* type = uint8_t */
    MIPC_NW_CELL_MEASUREMENT_CNF_T_LTE_CELL_LIST_COUNT      = 0x103,
    /* The cell count for the cell measurement. */
    /* type = struct_array, refer to nw_cellmeasurement_info */
    MIPC_NW_CELL_MEASUREMENT_CNF_T_LTE_CELL_LIST            = 0x8104,
    /* The PLMN infos for all cells, this is array(the list for cell_plmn) */
    /* type = struct_array, refer to cell_plmn */
    MIPC_NW_CELL_MEASUREMENT_CNF_T_LTE_PLMN_ARRAY           = 0x8105,
    /* The cell count for the cell measurement. */
    /* type = uint8_t */
    MIPC_NW_CELL_MEASUREMENT_CNF_T_NR_CELL_LIST_COUNT       = 0x106,
    /* The cell count for the cell measurement. */
    /* type = struct_array, refer to nw_cellmeasurement_info */
    MIPC_NW_CELL_MEASUREMENT_CNF_T_NR_CELL_LIST             = 0x8107,
    /* The PLMN infos for NR cells, this is array(the list for cell_plmn) */
    /* type = struct_array, refer to cell_plmn */
    MIPC_NW_CELL_MEASUREMENT_CNF_T_NR_PLMN_ARRAY            = 0x8108,
};

    /* MIPC_MSG.NW_CELL_BAND_WHITE_LIST_LOCK_REQ */
enum mipc_nw_cell_band_white_list_lock_req_tlv_enum {
    mipc_nw_cell_band_white_list_lock_req_tlv_NONE = 0,
    /* A bitmap that represents which LTE bands are measurement. */
    /* type = struct, refer to sys_lte_band */
    MIPC_NW_CELL_BAND_WHITE_LIST_LOCK_REQ_T_LTE_BAND        = 0x100,
    /* A bitmap that represents which NR bands are measurement. */
    /* type = struct, refer to sys_nr_band */
    MIPC_NW_CELL_BAND_WHITE_LIST_LOCK_REQ_T_NR_BAND         = 0x101,
    /* lte white cell list count */
    /* type = uint8_t */
    MIPC_NW_CELL_BAND_WHITE_LIST_LOCK_REQ_T_LTE_CELL_COUNT  = 0x102,
    /* lte white cell list, please just fill the earfcn and physical_cell_id of nw_lte_cell */
    /* type = struct_array, refer to nw_lte_cell */
    MIPC_NW_CELL_BAND_WHITE_LIST_LOCK_REQ_T_LTE_CELL_LIST   = 0x103,
    /* nr white cell list count */
    /* type = uint8_t */
    MIPC_NW_CELL_BAND_WHITE_LIST_LOCK_REQ_T_NR_CELL_COUNT   = 0x104,
    /* nr white cell list, please just fill the nr_arfcn and physical_cell_id of nw_nr_cell */
    /* type = struct_array, refer to nw_nr_cell */
    MIPC_NW_CELL_BAND_WHITE_LIST_LOCK_REQ_T_NR_CELL_LIST    = 0x105,
};

    /* MIPC_MSG.NW_CELL_BAND_WHITE_LIST_LOCK_CNF */
enum mipc_nw_cell_band_white_list_lock_cnf_tlv_enum {
    mipc_nw_cell_band_white_list_lock_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_CELL_BAND_BANDWIDTH_REQ */
enum mipc_nw_get_cell_band_bandwidth_req_tlv_enum {
    mipc_nw_get_cell_band_bandwidth_req_tlv_NONE = 0,
    /*  support both rat lte and nr currently, this is not mandatory. */
    /* type = uint8_t */
    MIPC_NW_GET_CELL_BAND_BANDWIDTH_REQ_T_RAT               = 0x100,
};

    /* MIPC_MSG.NW_GET_CELL_BAND_BANDWIDTH_CNF */
enum mipc_nw_get_cell_band_bandwidth_cnf_tlv_enum {
    mipc_nw_get_cell_band_bandwidth_cnf_tlv_NONE = 0,
    /* this parameter will be removed,the value is invalid */
    /* type = uint8_t */
    MIPC_NW_GET_CELL_BAND_BANDWIDTH_CNF_T_NUM_SERVING_CELL  = 0x100,
    /* this parameter will be removed,the value is invalid */
    /* type = struct_array, refer to nw_cell_band_bandwidth */
    MIPC_NW_GET_CELL_BAND_BANDWIDTH_CNF_T_LTE_SERVING_CELL_LIST = 0x8101,
    /* this parameter will be removed,the value is invalid */
    /* type = struct_array, refer to nw_cell_band_bandwidth */
    MIPC_NW_GET_CELL_BAND_BANDWIDTH_CNF_T_NR_SERVING_CELL_LIST = 0x8102,
    /* num of dl lte serving cell, the max of it is 32 */
    /* type = uint8_t */
    MIPC_NW_GET_CELL_BAND_BANDWIDTH_CNF_T_LTE_DL_SERVING_CELL_COUNT = 0x103,
    /* num of ul lte serving cell, the max of it is 32 */
    /* type = uint8_t */
    MIPC_NW_GET_CELL_BAND_BANDWIDTH_CNF_T_LTE_UL_SERVING_CELL_COUNT = 0x104,
    /* num of dl nr serving cell, the max of it is 32 */
    /* type = uint8_t */
    MIPC_NW_GET_CELL_BAND_BANDWIDTH_CNF_T_NR_DL_SERVING_CELL_COUNT = 0x105,
    /* num of ul nr serving cell, the max of it is 32 */
    /* type = uint8_t */
    MIPC_NW_GET_CELL_BAND_BANDWIDTH_CNF_T_NR_UL_SERVING_CELL_COUNT = 0x106,
    /* DL LTE serving cell list */
    /* type = struct_array, refer to nw_lte_nr_ca_info */
    MIPC_NW_GET_CELL_BAND_BANDWIDTH_CNF_T_LTE_DL_SERVING_CELL_LIST = 0x107,
    /* UL LTE serving cell list */
    /* type = struct_array, refer to nw_lte_nr_ca_info */
    MIPC_NW_GET_CELL_BAND_BANDWIDTH_CNF_T_LTE_UL_SERVING_CELL_LIST = 0x108,
    /* DL NR serving cell list */
    /* type = struct_array, refer to nw_lte_nr_ca_info */
    MIPC_NW_GET_CELL_BAND_BANDWIDTH_CNF_T_NR_DL_SERVING_CELL_LIST = 0x109,
    /* UL NR serving cell list */
    /* type = struct_array, refer to nw_lte_nr_ca_info */
    MIPC_NW_GET_CELL_BAND_BANDWIDTH_CNF_T_NR_UL_SERVING_CELL_LIST = 0x10A,
};

    /* MIPC_MSG.NW_GET_NR_REQ */
enum mipc_nw_get_nr_req_tlv_enum {
    mipc_nw_get_nr_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_NR_CNF */
enum mipc_nw_get_nr_cnf_tlv_enum {
    mipc_nw_get_nr_cnf_tlv_NONE = 0,
    /* 1: LTE ONLY(disable NSA+SA); 3: SA ONLY; 5: NSA ONLY; 7: NSA+SA. */
    /* type = uint8_t */
    MIPC_NW_GET_NR_CNF_T_NR_OPT                             = 0x100,
};

    /* MIPC_MSG.NW_GET_SRXLEV_REQ */
enum mipc_nw_get_srxlev_req_tlv_enum {
    mipc_nw_get_srxlev_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_SRXLEV_CNF */
enum mipc_nw_get_srxlev_cnf_tlv_enum {
    mipc_nw_get_srxlev_cnf_tlv_NONE = 0,
    /* LTE SRXLEV INFO. */
    /* type = struct, refer to nw_srxlev_info */
    MIPC_NW_GET_SRXLEV_CNF_T_LTE_SRXLEV_INFO                = 0x100,
    /* NR SRXLEV INFO. */
    /* type = struct, refer to nw_srxlev_info */
    MIPC_NW_GET_SRXLEV_CNF_T_NR_SRXLEV_INFO                 = 0x101,
};

    /* MIPC_MSG.NW_SET_ROAMING_MODE_REQ */
enum mipc_nw_set_roaming_mode_req_tlv_enum {
    mipc_nw_set_roaming_mode_req_tlv_NONE = 0,
    /*  A bitmap that represents which roaming mode to disable */
    /* type = bitmap, refer to NW_ROAMING_MODE */
    MIPC_NW_SET_ROAMING_MODE_REQ_T_ROAMING_MODE             = 0x100,
};

    /* MIPC_MSG.NW_SET_ROAMING_MODE_CNF */
enum mipc_nw_set_roaming_mode_cnf_tlv_enum {
    mipc_nw_set_roaming_mode_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_ROAMING_MODE_REQ */
enum mipc_nw_get_roaming_mode_req_tlv_enum {
    mipc_nw_get_roaming_mode_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_ROAMING_MODE_CNF */
enum mipc_nw_get_roaming_mode_cnf_tlv_enum {
    mipc_nw_get_roaming_mode_cnf_tlv_NONE = 0,
    /*  A bitmap that represents which roaming mode to disable */
    /* type = bitmap, refer to NW_ROAMING_MODE */
    MIPC_NW_GET_ROAMING_MODE_CNF_T_ROAMING_MODE             = 0x100,
};

    /* MIPC_MSG.NW_SET_URC_ENABLE_REQ */
enum mipc_nw_set_urc_enable_req_tlv_enum {
    mipc_nw_set_urc_enable_req_tlv_NONE = 0,
    /*  ind type of to set */
    /* type = uint8_t, refer to NW_IND_TYPE */
    MIPC_NW_SET_URC_ENABLE_REQ_T_TYPE                       = 0x100,
    /*  1 means to enable and 0 means disable the given ind. */
    /* type = uint8_t */
    MIPC_NW_SET_URC_ENABLE_REQ_T_ENABLE                     = 0x101,
};

    /* MIPC_MSG.NW_SET_URC_ENABLE_CNF */
enum mipc_nw_set_urc_enable_cnf_tlv_enum {
    mipc_nw_set_urc_enable_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_SUGGESTED_PLMN_LIST_REQ */
enum mipc_nw_get_suggested_plmn_list_req_tlv_enum {
    mipc_nw_get_suggested_plmn_list_req_tlv_NONE = 0,
    /* 0:GMSS, 1:UMTS, 3:LTE. */
    /* type = uint8_t */
    MIPC_NW_GET_SUGGESTED_PLMN_LIST_REQ_T_RAT               = 0x100,
    /* number of PLMN that needs to be listed. */
    /* type = uint8_t */
    MIPC_NW_GET_SUGGESTED_PLMN_LIST_REQ_T_NUM               = 0x101,
    /* guard timer for PLMN list procedure. */
    /* type = uint8_t */
    MIPC_NW_GET_SUGGESTED_PLMN_LIST_REQ_T_TIMER             = 0x102,
};

    /* MIPC_MSG.NW_GET_SUGGESTED_PLMN_LIST_CNF */
enum mipc_nw_get_suggested_plmn_list_cnf_tlv_enum {
    mipc_nw_get_suggested_plmn_list_cnf_tlv_NONE = 0,
    /* the number of suggested plmn list. */
    /* type = uint8_t */
    MIPC_NW_GET_SUGGESTED_PLMN_LIST_CNF_T_COUNT             = 0x100,
    /* suggested PLMN list */
    /* type = struct_array, refer to nw_suggested */
    MIPC_NW_GET_SUGGESTED_PLMN_LIST_CNF_T_LIST              = 0x101,
    /* The fail cause for current operation. */
    /* type = uint16_t */
    MIPC_NW_GET_SUGGESTED_PLMN_LIST_CNF_T_FAIL_CAUSE        = 0x102,
};

    /* MIPC_MSG.NW_SET_SEARCH_STORE_FREQUENCY_INFO_REQ */
enum mipc_nw_set_search_store_frequency_info_req_tlv_enum {
    mipc_nw_set_search_store_frequency_info_req_tlv_NONE = 0,
    /* 0:Clear all the setting of this command. 1: Add new ARFCN of the specified RAT`s PLMN for searching. */
    /* type = uint8_t */
    MIPC_NW_SET_SEARCH_STORE_FREQUENCY_INFO_REQ_T_OPER      = 0x100,
    /* only support LTE 4 and NR 128. */
    /* type = uint8_t */
    MIPC_NW_SET_SEARCH_STORE_FREQUENCY_INFO_REQ_T_RAT       = 0x101,
    /* plmn id. */
    /* type = string */
    MIPC_NW_SET_SEARCH_STORE_FREQUENCY_INFO_REQ_T_PLMN      = 0x102,
    /* number of ARFCN to be added,current max number is 10. */
    /* type = uint8_t */
    MIPC_NW_SET_SEARCH_STORE_FREQUENCY_INFO_REQ_T_COUNT     = 0x103,
    /* ARFCN. */
    /* type = struct_array, refer to nw_arfcn */
    MIPC_NW_SET_SEARCH_STORE_FREQUENCY_INFO_REQ_T_ARFCN     = 0x104,
};

    /* MIPC_MSG.NW_SET_SEARCH_STORE_FREQUENCY_INFO_CNF */
enum mipc_nw_set_search_store_frequency_info_cnf_tlv_enum {
    mipc_nw_set_search_store_frequency_info_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_SET_SELECT_FEMTOCELL_REQ */
enum mipc_nw_set_select_femtocell_req_tlv_enum {
    mipc_nw_set_select_femtocell_req_tlv_NONE = 0,
    /* plmn id. */
    /* type = string */
    MIPC_NW_SET_SELECT_FEMTOCELL_REQ_T_PLMN                 = 0x100,
    /* 0:GSM, 2:UMTS, 7:LTE. */
    /* type = uint8_t */
    MIPC_NW_SET_SELECT_FEMTOCELL_REQ_T_ACT                  = 0x101,
    /* csg id. */
    /* type = string */
    MIPC_NW_SET_SELECT_FEMTOCELL_REQ_T_CSG_ID               = 0x102,
};

    /* MIPC_MSG.NW_SET_SELECT_FEMTOCELL_CNF */
enum mipc_nw_set_select_femtocell_cnf_tlv_enum {
    mipc_nw_set_select_femtocell_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_SET_CONFIG_A2_OFFSET_REQ */
enum mipc_nw_set_config_a2_offset_req_tlv_enum {
    mipc_nw_set_config_a2_offset_req_tlv_NONE = 0,
    /* offset. */
    /* type = uint8_t */
    MIPC_NW_SET_CONFIG_A2_OFFSET_REQ_T_OFFSET               = 0x100,
    /* thresh_bound. */
    /* type = uint8_t */
    MIPC_NW_SET_CONFIG_A2_OFFSET_REQ_T_THRESH_BOUND         = 0x101,
};

    /* MIPC_MSG.NW_SET_CONFIG_A2_OFFSET_CNF */
enum mipc_nw_set_config_a2_offset_cnf_tlv_enum {
    mipc_nw_set_config_a2_offset_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_SET_CONFIG_B1_OFFSET_REQ */
enum mipc_nw_set_config_b1_offset_req_tlv_enum {
    mipc_nw_set_config_b1_offset_req_tlv_NONE = 0,
    /* offset. */
    /* type = uint8_t */
    MIPC_NW_SET_CONFIG_B1_OFFSET_REQ_T_OFFSET               = 0x100,
    /* thresh_bound. */
    /* type = uint8_t */
    MIPC_NW_SET_CONFIG_B1_OFFSET_REQ_T_THRESH_BOUND         = 0x101,
};

    /* MIPC_MSG.NW_SET_CONFIG_B1_OFFSET_CNF */
enum mipc_nw_set_config_b1_offset_cnf_tlv_enum {
    mipc_nw_set_config_b1_offset_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_SET_REPORT_ANBR_REQ */
enum mipc_nw_set_report_anbr_req_tlv_enum {
    mipc_nw_set_report_anbr_req_tlv_NONE = 0,
    /* 0:disable ENABR URC, 1:enable EANBR URC, 2:send phone`s ANBR valuse to NW. */
    /* type = uint8_t */
    MIPC_NW_SET_REPORT_ANBR_REQ_T_MODE                      = 0x100,
    /* ebi value,5-15. */
    /* type = uint8_t */
    MIPC_NW_SET_REPORT_ANBR_REQ_T_EBI                       = 0x101,
    /* 0:downlink, 1:uplink. */
    /* type = uint8_t */
    MIPC_NW_SET_REPORT_ANBR_REQ_T_IS_UL                     = 0x102,
    /* valid rang 1-63. */
    /* type = uint8_t */
    MIPC_NW_SET_REPORT_ANBR_REQ_T_BEARE_ID                  = 0x104,
    /* Bitrate value 0-8000, 0xffff means invalid value. */
    /* type = uint16_t */
    MIPC_NW_SET_REPORT_ANBR_REQ_T_BITRATE                   = 0x103,
    /* valid rang 1-15. */
    /* type = uint8_t */
    MIPC_NW_SET_REPORT_ANBR_REQ_T_PDU_SESSION_ID            = 0x105,
    /* ext_param. */
    /* type = uint8_t */
    MIPC_NW_SET_REPORT_ANBR_REQ_T_EXT_PARAM                 = 0x106,
};

    /* MIPC_MSG.NW_SET_REPORT_ANBR_CNF */
enum mipc_nw_set_report_anbr_cnf_tlv_enum {
    mipc_nw_set_report_anbr_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_SET_NETWORK_EVENT_REQ */
enum mipc_nw_set_network_event_req_tlv_enum {
    mipc_nw_set_network_event_req_tlv_NONE = 0,
    /* 0:disable EREGINFO URC, 1:enable EREGINFO URC. */
    /* type = uint8_t */
    MIPC_NW_SET_NETWORK_EVENT_REQ_T_MODE                    = 0x100,
};

    /* MIPC_MSG.NW_SET_NETWORK_EVENT_CNF */
enum mipc_nw_set_network_event_cnf_tlv_enum {
    mipc_nw_set_network_event_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_SET_ENABLE_CA_PLUS_FILTER_REQ */
enum mipc_nw_set_enable_ca_plus_filter_req_tlv_enum {
    mipc_nw_set_enable_ca_plus_filter_req_tlv_NONE = 0,
    /* 0:disable, 1:enable. */
    /* type = uint8_t */
    MIPC_NW_SET_ENABLE_CA_PLUS_FILTER_REQ_T_ENABLE          = 0x100,
};

    /* MIPC_MSG.NW_SET_ENABLE_CA_PLUS_FILTER_CNF */
enum mipc_nw_set_enable_ca_plus_filter_cnf_tlv_enum {
    mipc_nw_set_enable_ca_plus_filter_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_ABORT_FEMTOCELL_LIST_REQ */
enum mipc_nw_abort_femtocell_list_req_tlv_enum {
    mipc_nw_abort_femtocell_list_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_ABORT_FEMTOCELL_LIST_CNF */
enum mipc_nw_abort_femtocell_list_cnf_tlv_enum {
    mipc_nw_abort_femtocell_list_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_FEMTOCELL_LIST_REQ */
enum mipc_nw_get_femtocell_list_req_tlv_enum {
    mipc_nw_get_femtocell_list_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_FEMTOCELL_LIST_CNF */
enum mipc_nw_get_femtocell_list_cnf_tlv_enum {
    mipc_nw_get_femtocell_list_cnf_tlv_NONE = 0,
    /* Count of LTE femtocell LIST. */
    /* type = uint8_t */
    MIPC_NW_GET_FEMTOCELL_LIST_CNF_T_CELL_COUNT             = 0x100,
    /* The list of FEMTOCELL. */
    /* type = struct_array, refer to nw_femtocell_info */
    MIPC_NW_GET_FEMTOCELL_LIST_CNF_T_FEMTOCELL_LIST         = 0x101,
    /* The fail cause for current operation . */
    /* type = uint16_t */
    MIPC_NW_GET_FEMTOCELL_LIST_CNF_T_FAIL_CAUSE             = 0x102,
};

    /* MIPC_MSG.NW_SET_PSEUDO_CELL_MODE_REQ */
enum mipc_nw_set_pseudo_cell_mode_req_tlv_enum {
    mipc_nw_set_pseudo_cell_mode_req_tlv_NONE = 0,
    /* the mode of the apc. */
    /* type = uint8_t */
    MIPC_NW_SET_PSEUDO_CELL_MODE_REQ_T_APC_MODE             = 0x100,
    /* urc_enable value. */
    /* type = uint8_t */
    MIPC_NW_SET_PSEUDO_CELL_MODE_REQ_T_URC_ENABLE           = 0x101,
    /* timer value. */
    /* type = uint16_t */
    MIPC_NW_SET_PSEUDO_CELL_MODE_REQ_T_TIMER                = 0x102,
};

    /* MIPC_MSG.NW_SET_PSEUDO_CELL_MODE_CNF */
enum mipc_nw_set_pseudo_cell_mode_cnf_tlv_enum {
    mipc_nw_set_pseudo_cell_mode_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_PSEUDO_CELL_INFO_REQ */
enum mipc_nw_get_pseudo_cell_info_req_tlv_enum {
    mipc_nw_get_pseudo_cell_info_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_PSEUDO_CELL_INFO_CNF */
enum mipc_nw_get_pseudo_cell_info_cnf_tlv_enum {
    mipc_nw_get_pseudo_cell_info_cnf_tlv_NONE = 0,
    /* The mode of the pseudo cell apc */
    /* type = uint8_t */
    MIPC_NW_GET_PSEUDO_CELL_INFO_CNF_T_APC_MODE             = 0x100,
    /* the enable state of the URC  */
    /* type = uint8_t */
    MIPC_NW_GET_PSEUDO_CELL_INFO_CNF_T_URC_ENABLE           = 0x101,
    /* the interval of the periods */
    /* type = uint16_t */
    MIPC_NW_GET_PSEUDO_CELL_INFO_CNF_T_TIMER                = 0x102,
    /* the count of the pseudocell list */
    /* type = uint8_t */
    MIPC_NW_GET_PSEUDO_CELL_INFO_CNF_T_CELL_COUNT           = 0x103,
    /* The list of FEMTOCELL. */
    /* type = struct_array, refer to nw_pseudocell_info */
    MIPC_NW_GET_PSEUDO_CELL_INFO_CNF_T_PSEUDOCELL_LIST      = 0x104,
    /* The fail cause for current operation . */
    /* type = uint16_t */
    MIPC_NW_GET_PSEUDO_CELL_INFO_CNF_T_FAIL_CAUSE           = 0x105,
};

    /* MIPC_MSG.NW_SET_ROAMING_ENABLE_REQ */
enum mipc_nw_set_roaming_enable_req_tlv_enum {
    mipc_nw_set_roaming_enable_req_tlv_NONE = 0,
    /* the protocal index of the roaming enable. */
    /* type = uint8_t */
    MIPC_NW_SET_ROAMING_ENABLE_REQ_T_PROTOCOL_INDEX         = 0x100,
    /* Bar dom voice roaming enabled. */
    /* type = uint8_t */
    MIPC_NW_SET_ROAMING_ENABLE_REQ_T_DOM_VOICE              = 0x101,
    /* Bar dom data roaming enabled. */
    /* type = uint8_t */
    MIPC_NW_SET_ROAMING_ENABLE_REQ_T_DOM_DATA               = 0x102,
    /* Bar int voice roaming enabled. */
    /* type = uint8_t */
    MIPC_NW_SET_ROAMING_ENABLE_REQ_T_INT_VOICE              = 0x103,
    /* Bar int data roaming enabled. */
    /* type = uint8_t */
    MIPC_NW_SET_ROAMING_ENABLE_REQ_T_INT_DATA               = 0x104,
    /* Bar LTE data roaming enabled. */
    /* type = uint8_t */
    MIPC_NW_SET_ROAMING_ENABLE_REQ_T_LTE_DATA               = 0x105,
};

    /* MIPC_MSG.NW_SET_ROAMING_ENABLE_CNF */
enum mipc_nw_set_roaming_enable_cnf_tlv_enum {
    mipc_nw_set_roaming_enable_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_ROAMING_ENABLE_REQ */
enum mipc_nw_get_roaming_enable_req_tlv_enum {
    mipc_nw_get_roaming_enable_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_ROAMING_ENABLE_CNF */
enum mipc_nw_get_roaming_enable_cnf_tlv_enum {
    mipc_nw_get_roaming_enable_cnf_tlv_NONE = 0,
    /* the protocal index of the roaming enable. */
    /* type = uint8_t */
    MIPC_NW_GET_ROAMING_ENABLE_CNF_T_PROTOCOL_INDEX         = 0x100,
    /* Bar dom voice roaming enabled. */
    /* type = uint8_t */
    MIPC_NW_GET_ROAMING_ENABLE_CNF_T_DOM_VOICE              = 0x101,
    /* Bar dom data roaming enabled. */
    /* type = uint8_t */
    MIPC_NW_GET_ROAMING_ENABLE_CNF_T_DOM_DATA               = 0x102,
    /* Bar int voice roaming enabled. */
    /* type = uint8_t */
    MIPC_NW_GET_ROAMING_ENABLE_CNF_T_INT_VOICE              = 0x103,
    /* Bar int data roaming enabled. */
    /* type = uint8_t */
    MIPC_NW_GET_ROAMING_ENABLE_CNF_T_INT_DATA               = 0x104,
    /* Bar LTE data roaming enabled. */
    /* type = uint8_t */
    MIPC_NW_GET_ROAMING_ENABLE_CNF_T_LTE_DATA               = 0x105,
    /* The fail cause for current operation . */
    /* type = uint16_t */
    MIPC_NW_GET_ROAMING_ENABLE_CNF_T_FAIL_CAUSE             = 0x106,
};

    /* MIPC_MSG.NW_SET_FEMTOCELL_SYSTEM_SELECTION_MODE_REQ */
enum mipc_nw_set_femtocell_system_selection_mode_req_tlv_enum {
    mipc_nw_set_femtocell_system_selection_mode_req_tlv_NONE = 0,
    /* The mode of the femtocell system selection . */
    /* type = uint8_t */
    MIPC_NW_SET_FEMTOCELL_SYSTEM_SELECTION_MODE_REQ_T_MODE  = 0x100,
};

    /* MIPC_MSG.NW_SET_FEMTOCELL_SYSTEM_SELECTION_MODE_CNF */
enum mipc_nw_set_femtocell_system_selection_mode_cnf_tlv_enum {
    mipc_nw_set_femtocell_system_selection_mode_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_QUERY_FEMTOCELL_SYSTEM_SELECTION_MODE_REQ */
enum mipc_nw_query_femtocell_system_selection_mode_req_tlv_enum {
    mipc_nw_query_femtocell_system_selection_mode_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_QUERY_FEMTOCELL_SYSTEM_SELECTION_MODE_CNF */
enum mipc_nw_query_femtocell_system_selection_mode_cnf_tlv_enum {
    mipc_nw_query_femtocell_system_selection_mode_cnf_tlv_NONE = 0,
    /* The mode of the femtocell system selection . */
    /* type = uint8_t */
    MIPC_NW_QUERY_FEMTOCELL_SYSTEM_SELECTION_MODE_CNF_T_MODE = 0x100,
    /* The fail cause for current operation . */
    /* type = uint16_t */
    MIPC_NW_QUERY_FEMTOCELL_SYSTEM_SELECTION_MODE_CNF_T_FAIL_CAUSE = 0x101,
};

    /* MIPC_MSG.NW_SET_NW_IND_REPORT_LEVEL_REQ */
enum mipc_nw_set_nw_ind_report_level_req_tlv_enum {
    mipc_nw_set_nw_ind_report_level_req_tlv_NONE = 0,
    /* Indicate PS state report LEVEL. 3: enable EGERG URC with full information.  5: enable EGREG URC when <stat> or <eAct> changes. 0: do not change ps state report level. */
    /* type = uint8_t */
    MIPC_NW_SET_NW_IND_REPORT_LEVEL_REQ_T_PS_STATE_LEVEL    = 0x100,
    /* Indicate CS state report LEVEL. 3: enable EREG URC with full information.  5: enable EREG URC when <stat> or <eAct> changes. 0: do not change cs state report level. */
    /* type = uint8_t */
    MIPC_NW_SET_NW_IND_REPORT_LEVEL_REQ_T_CS_STATE_LEVEL    = 0x101,
};

    /* MIPC_MSG.NW_SET_NW_IND_REPORT_LEVEL_CNF */
enum mipc_nw_set_nw_ind_report_level_cnf_tlv_enum {
    mipc_nw_set_nw_ind_report_level_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_SET_DISABLE_2G_REQ */
enum mipc_nw_set_disable_2g_req_tlv_enum {
    mipc_nw_set_disable_2g_req_tlv_NONE = 0,
    /* Indicaates which rat is disable: 0 => no RAT are disable; 1 => disable 2G. */
    /* type = uint8_t */
    MIPC_NW_SET_DISABLE_2G_REQ_T_MODE                       = 0x100,
};

    /* MIPC_MSG.NW_SET_DISABLE_2G_CNF */
enum mipc_nw_set_disable_2g_cnf_tlv_enum {
    mipc_nw_set_disable_2g_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_DISABLE_2G_REQ */
enum mipc_nw_get_disable_2g_req_tlv_enum {
    mipc_nw_get_disable_2g_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_DISABLE_2G_CNF */
enum mipc_nw_get_disable_2g_cnf_tlv_enum {
    mipc_nw_get_disable_2g_cnf_tlv_NONE = 0,
    /* Indicaates which rat is disable: 0 => no RAT are disable; 1 => disable 2G. */
    /* type = uint8_t */
    MIPC_NW_GET_DISABLE_2G_CNF_T_MODE                       = 0x100,
};

    /* MIPC_MSG.NW_SET_SMART_RAT_SWITCH_REQ */
enum mipc_nw_set_smart_rat_switch_req_tlv_enum {
    mipc_nw_set_smart_rat_switch_req_tlv_NONE = 0,
    /* The expected mode for switch control. */
    /* type = uint8_t, refer to NW_RAT_SWITCH_MODE */
    MIPC_NW_SET_SMART_RAT_SWITCH_REQ_T_MODE                 = 0x100,
    /* Indicates which RAT will be used, just support two RAT for this REQ: 0: 4G; 1: 5G. */
    /* type = uint8_t */
    MIPC_NW_SET_SMART_RAT_SWITCH_REQ_T_RAT                  = 0x101,
};

    /* MIPC_MSG.NW_SET_SMART_RAT_SWITCH_CNF */
enum mipc_nw_set_smart_rat_switch_cnf_tlv_enum {
    mipc_nw_set_smart_rat_switch_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_SMART_RAT_SWITCH_REQ */
enum mipc_nw_get_smart_rat_switch_req_tlv_enum {
    mipc_nw_get_smart_rat_switch_req_tlv_NONE = 0,
    /* The mode for switch control. */
    /* type = uint8_t, refer to NW_RAT_SWITCH_MODE */
    MIPC_NW_GET_SMART_RAT_SWITCH_REQ_T_MODE                 = 0x100,
};

    /* MIPC_MSG.NW_GET_SMART_RAT_SWITCH_CNF */
enum mipc_nw_get_smart_rat_switch_cnf_tlv_enum {
    mipc_nw_get_smart_rat_switch_cnf_tlv_NONE = 0,
    /* RAT switch state. */
    /* type = uint8_t */
    MIPC_NW_GET_SMART_RAT_SWITCH_CNF_T_STATE                = 0x100,
};

    /* MIPC_MSG.NW_VSS_ANTENNA_CONF_REQ */
enum mipc_nw_vss_antenna_conf_req_tlv_enum {
    mipc_nw_vss_antenna_conf_req_tlv_NONE = 0,
    /* 0: signal information is not available on all Rx chains.  1: Rx diversity bitmask for chain 0.  2: Rx diversity bitmask for chain 1 is available.  3: Signal information on both Rx chains is available. */
    /* type = uint8_t */
    MIPC_NW_VSS_ANTENNA_CONF_REQ_T_ANTENNA_TYPE             = 0x100,
};

    /* MIPC_MSG.NW_VSS_ANTENNA_CONF_CNF */
enum mipc_nw_vss_antenna_conf_cnf_tlv_enum {
    mipc_nw_vss_antenna_conf_cnf_tlv_NONE = 0,
    /* 0: signal information is not available on all Rx chains.  1: Rx diversity bitmask for chain 0.  2: Rx diversity bitmask for chain 1 is available.  3: Signal information on both Rx chains is available. */
    /* type = uint8_t */
    MIPC_NW_VSS_ANTENNA_CONF_CNF_T_ANTENNA_TYPE             = 0x100,
};

    /* MIPC_MSG.NW_VSS_ANTENNA_INFO_REQ */
enum mipc_nw_vss_antenna_info_req_tlv_enum {
    mipc_nw_vss_antenna_info_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_VSS_ANTENNA_INFO_CNF */
enum mipc_nw_vss_antenna_info_cnf_tlv_enum {
    mipc_nw_vss_antenna_info_cnf_tlv_NONE = 0,
    /* primary antenna RSSI */
    /* type = int32_t */
    MIPC_NW_VSS_ANTENNA_INFO_CNF_T_PRIMARY_ANTENNA_RSSI     = 0x100,
    /* relative phase */
    /* type = int32_t */
    MIPC_NW_VSS_ANTENNA_INFO_CNF_T_RELATIVE_PHASE           = 0x101,
    /* secondary antenna RSSI */
    /* type = int32_t */
    MIPC_NW_VSS_ANTENNA_INFO_CNF_T_SECONDARY_ANTENNA_RSSI   = 0x102,
    /* phase1 */
    /* type = int32_t */
    MIPC_NW_VSS_ANTENNA_INFO_CNF_T_PHASE1                   = 0x103,
    /* rx0 state, 0: not valid, 1: valid */
    /* type = int32_t */
    MIPC_NW_VSS_ANTENNA_INFO_CNF_T_RX_STATE_0               = 0x104,
    /* rx1 state, 0: not valid, 1: valid */
    /* type = int32_t */
    MIPC_NW_VSS_ANTENNA_INFO_CNF_T_RX_STATE_1               = 0x105,
};

    /* MIPC_MSG.NW_SET_RADIO_CAPABILITY_REQ */
enum mipc_nw_set_radio_capability_req_tlv_enum {
    mipc_nw_set_radio_capability_req_tlv_NONE = 0,
    /* bit0: GSM, bit1: UMTS, bit2: LTE, bit3: NR, bit4: C2K */
    /* type = uint32_t */
    MIPC_NW_SET_RADIO_CAPABILITY_REQ_T_RADIO_CAPABILITY     = 0x100,
};

    /* MIPC_MSG.NW_SET_RADIO_CAPABILITY_CNF */
enum mipc_nw_set_radio_capability_cnf_tlv_enum {
    mipc_nw_set_radio_capability_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_SET_CDMA_ROAMING_PREFERENCE_REQ */
enum mipc_nw_set_cdma_roaming_preference_req_tlv_enum {
    mipc_nw_set_cdma_roaming_preference_req_tlv_NONE = 0,
    /* 0: for Home Networks only, 2: for Roaming on Any Network. */
    /* type = uint8_t */
    MIPC_NW_SET_CDMA_ROAMING_PREFERENCE_REQ_T_ROAMING_TYPE  = 0x100,
};

    /* MIPC_MSG.NW_SET_CDMA_ROAMING_PREFERENCE_CNF */
enum mipc_nw_set_cdma_roaming_preference_cnf_tlv_enum {
    mipc_nw_set_cdma_roaming_preference_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_CDMA_ROAMING_PREFERENCE_REQ */
enum mipc_nw_get_cdma_roaming_preference_req_tlv_enum {
    mipc_nw_get_cdma_roaming_preference_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_CDMA_ROAMING_PREFERENCE_CNF */
enum mipc_nw_get_cdma_roaming_preference_cnf_tlv_enum {
    mipc_nw_get_cdma_roaming_preference_cnf_tlv_NONE = 0,
    /* 0: for Home Networks only, 2: for Roaming on Any Network. */
    /* type = uint8_t */
    MIPC_NW_GET_CDMA_ROAMING_PREFERENCE_CNF_T_ROAMING_TYPE  = 0x100,
};

    /* MIPC_MSG.NW_GET_BARRING_INFO_REQ */
enum mipc_nw_get_barring_info_req_tlv_enum {
    mipc_nw_get_barring_info_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_BARRING_INFO_CNF */
enum mipc_nw_get_barring_info_cnf_tlv_enum {
    mipc_nw_get_barring_info_cnf_tlv_NONE = 0,
    /* 0: disable unsolicited result code , 1: enable unsolicited result code. */
    /* type = uint8_t */
    MIPC_NW_GET_BARRING_INFO_CNF_T_MODE                     = 0x100,
    /* number of current camping on network barring. */
    /* type = uint8_t */
    MIPC_NW_GET_BARRING_INFO_CNF_T_COUNT                    = 0x101,
    /* The current camping on network barring info LIST of the barring service. */
    /* type = struct_array, refer to nw_barring_info */
    MIPC_NW_GET_BARRING_INFO_CNF_T_BARRING_LIST             = 0x102,
    /* current camping on network rat 2:UMTS 4:LTE 128:NR. */
    /* type = uint8_t */
    MIPC_NW_GET_BARRING_INFO_CNF_T_RAT                      = 0x103,
    /* number of UMTS barring. */
    /* type = uint8_t */
    MIPC_NW_GET_BARRING_INFO_CNF_T_COUNT_UMTS               = 0x104,
    /* The UMTS barring info LIST of the barring service. */
    /* type = struct_array, refer to nw_barring_info */
    MIPC_NW_GET_BARRING_INFO_CNF_T_BARRING_LIST_UMTS        = 0x105,
    /* number of LTE barring. */
    /* type = uint8_t */
    MIPC_NW_GET_BARRING_INFO_CNF_T_COUNT_LTE                = 0x106,
    /* The LTE barring info LIST of the barring service. */
    /* type = struct_array, refer to nw_barring_info */
    MIPC_NW_GET_BARRING_INFO_CNF_T_BARRING_LIST_LTE         = 0x107,
    /* number of NR barring. */
    /* type = uint8_t */
    MIPC_NW_GET_BARRING_INFO_CNF_T_COUNT_NR                 = 0x108,
    /* The NR barring info LIST of the barring service. */
    /* type = struct_array, refer to nw_barring_info */
    MIPC_NW_GET_BARRING_INFO_CNF_T_BARRING_LIST_NR          = 0x109,
};

    /* MIPC_MSG.NW_GET_EHRPD_INFO_REQ */
enum mipc_nw_get_ehrpd_info_req_tlv_enum {
    mipc_nw_get_ehrpd_info_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_EHRPD_INFO_CNF */
enum mipc_nw_get_ehrpd_info_cnf_tlv_enum {
    mipc_nw_get_ehrpd_info_cnf_tlv_NONE = 0,
    /* protocol revision in use, 0-10. */
    /* type = uint8_t */
    MIPC_NW_GET_EHRPD_INFO_CNF_T_REV                        = 0x100,
    /* mobile country code. */
    /* type = uint16_t */
    MIPC_NW_GET_EHRPD_INFO_CNF_T_MCC                        = 0x101,
    /* mobile network code. */
    /* type = uint16_t */
    MIPC_NW_GET_EHRPD_INFO_CNF_T_MNC                        = 0x102,
    /* network identification. */
    /* type = uint16_t */
    MIPC_NW_GET_EHRPD_INFO_CNF_T_NID                        = 0x103,
    /* system identification. */
    /* type = uint16_t */
    MIPC_NW_GET_EHRPD_INFO_CNF_T_SID                        = 0x104,
    /* base station identification. */
    /* type = uint16_t */
    MIPC_NW_GET_EHRPD_INFO_CNF_T_BS_ID                      = 0x105,
    /* latitude of the current base station, in units of 0.25 seconds. */
    /* type = uint32_t */
    MIPC_NW_GET_EHRPD_INFO_CNF_T_BS_LAT                     = 0x106,
    /* longitude of the current base station, in units of 0.25 seconds. */
    /* type = uint32_t */
    MIPC_NW_GET_EHRPD_INFO_CNF_T_BS_LONG                    = 0x107,
    /* EVDO sector id. */
    /* type = string */
    MIPC_NW_GET_EHRPD_INFO_CNF_T_SECTOR_ID                  = 0x108,
    /* EVDO subnet mask. */
    /* type = string */
    MIPC_NW_GET_EHRPD_INFO_CNF_T_SUBNET_MASK                = 0x109,
};

    /* MIPC_MSG.NW_GET_EGMSS_REQ */
enum mipc_nw_get_egmss_req_tlv_enum {
    mipc_nw_get_egmss_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_EGMSS_CNF */
enum mipc_nw_get_egmss_cnf_tlv_enum {
    mipc_nw_get_egmss_cnf_tlv_NONE = 0,
    /* rat. */
    /* type = uint32_t */
    MIPC_NW_GET_EGMSS_CNF_T_RAT                             = 0x100,
    /* mcc */
    /* type = uint32_t */
    MIPC_NW_GET_EGMSS_CNF_T_MCC                             = 0x101,
    /* attach status: 1 attached to the network on the rat; 0 have selected the rat and is going to perform PLMN search. */
    /* type = uint32_t */
    MIPC_NW_GET_EGMSS_CNF_T_STATUS                          = 0x102,
    /* current reported rat */
    /* type = uint32_t */
    MIPC_NW_GET_EGMSS_CNF_T_CUR_REPORTED_RAT                = 0x103,
    /* is home country or not, 0: not home contury, 1: home country */
    /* type = uint32_t */
    MIPC_NW_GET_EGMSS_CNF_T_IS_HOME_COUNTRY                 = 0x104,
};

    /* MIPC_MSG.NW_SET_CACHE_ENDC_CONNECT_MODE_REQ */
enum mipc_nw_set_cache_endc_connect_mode_req_tlv_enum {
    mipc_nw_set_cache_endc_connect_mode_req_tlv_NONE = 0,
    /* 0: no cache , 1: d cache mode,it means we will cache endc when the cell is used to be endc 2: jp mode, we will cache endc for a while of timer1 when idle to connected to LTE cell and cache endc for a while of timer2 when scg connect is break out. */
    /* type = uint8_t */
    MIPC_NW_SET_CACHE_ENDC_CONNECT_MODE_REQ_T_MODE          = 0x100,
    /* the value of timer1, uint:seconds */
    /* type = uint8_t */
    MIPC_NW_SET_CACHE_ENDC_CONNECT_MODE_REQ_T_TIMER1        = 0x101,
    /* the value of timer2,uint:seconds */
    /* type = uint8_t */
    MIPC_NW_SET_CACHE_ENDC_CONNECT_MODE_REQ_T_TIMER2        = 0x102,
};

    /* MIPC_MSG.NW_SET_CACHE_ENDC_CONNECT_MODE_CNF */
enum mipc_nw_set_cache_endc_connect_mode_cnf_tlv_enum {
    mipc_nw_set_cache_endc_connect_mode_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_SET_PS_TEST_MODE_REQ */
enum mipc_nw_set_ps_test_mode_req_tlv_enum {
    mipc_nw_set_ps_test_mode_req_tlv_NONE = 0,
    /* The test mode. */
    /* type = uint8_t, refer to NW_PS_TEST_MODE */
    MIPC_NW_SET_PS_TEST_MODE_REQ_T_MODE                     = 0x100,
    /* Specific test profile under the test mode. */
    /* type = uint32_t */
    MIPC_NW_SET_PS_TEST_MODE_REQ_T_PROFILE                  = 0x101,
};

    /* MIPC_MSG.NW_SET_PS_TEST_MODE_CNF */
enum mipc_nw_set_ps_test_mode_cnf_tlv_enum {
    mipc_nw_set_ps_test_mode_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_PS_TEST_MODE_REQ */
enum mipc_nw_get_ps_test_mode_req_tlv_enum {
    mipc_nw_get_ps_test_mode_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_PS_TEST_MODE_CNF */
enum mipc_nw_get_ps_test_mode_cnf_tlv_enum {
    mipc_nw_get_ps_test_mode_cnf_tlv_NONE = 0,
    /* The test mode. */
    /* type = uint8_t, refer to NW_PS_TEST_MODE */
    MIPC_NW_GET_PS_TEST_MODE_CNF_T_MODE                     = 0x100,
    /* Specific test profile under the test mode. */
    /* type = uint32_t */
    MIPC_NW_GET_PS_TEST_MODE_CNF_T_PROFILE                  = 0x101,
};

    /* MIPC_MSG.NW_SET_SIGNAL_REPORT_CRITERIA_REQ */
enum mipc_nw_set_signal_report_criteria_req_tlv_enum {
    mipc_nw_set_signal_report_criteria_req_tlv_NONE = 0,
    /* 0: disable, 1: enable */
    /* type = uint8_t */
    MIPC_NW_SET_SIGNAL_REPORT_CRITERIA_REQ_T_MODE           = 0x100,
    /* The rat of whose signal you want to set. 1-GSM, 2-UMTS, 3-LTE, 4-C2K, 5-NR */
    /* type = uint8_t, refer to NW_SIGNAL_RAT */
    MIPC_NW_SET_SIGNAL_REPORT_CRITERIA_REQ_T_RAT            = 0x101,
    /* The signal measurement type */
    /* type = uint8_t, refer to NW_SIGNAL_MEASUREMENT_TYPE */
    MIPC_NW_SET_SIGNAL_REPORT_CRITERIA_REQ_T_SIGNAL_MEASUREMENT = 0x102,
    /* A hysteresis time in milliseconds. A value of 0 disables hysteresis. */
    /* type = uint32_t */
    MIPC_NW_SET_SIGNAL_REPORT_CRITERIA_REQ_T_HYSTERESIS_MS  = 0x103,
    /* An interval in dB defining the required magnitude change between reports. Its value must be smaller than the smallest threshold delta. An interval value of 0 disables hysteresis. */
    /* type = uint32_t */
    MIPC_NW_SET_SIGNAL_REPORT_CRITERIA_REQ_T_HYSTERESIS_DB  = 0x104,
    /* An array of trigger thresholds in dBm. */
    /* type = struct, refer to nw_threshold_array */
    MIPC_NW_SET_SIGNAL_REPORT_CRITERIA_REQ_T_THRESHOLD      = 0x105,
};

    /* MIPC_MSG.NW_SET_SIGNAL_REPORT_CRITERIA_CNF */
enum mipc_nw_set_signal_report_criteria_cnf_tlv_enum {
    mipc_nw_set_signal_report_criteria_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_ECAINFO_REQ */
enum mipc_nw_get_ecainfo_req_tlv_enum {
    mipc_nw_get_ecainfo_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_ECAINFO_CNF */
enum mipc_nw_get_ecainfo_cnf_tlv_enum {
    mipc_nw_get_ecainfo_cnf_tlv_NONE = 0,
    /* the cainfo of the response. */
    /* type = struct, refer to nw_ecainfo */
    MIPC_NW_GET_ECAINFO_CNF_T_ECAINFO                       = 0x100,
};

    /* MIPC_MSG.NW_GET_ACTIVITY_INFO_REQ */
enum mipc_nw_get_activity_info_req_tlv_enum {
    mipc_nw_get_activity_info_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_ACTIVITY_INFO_CNF */
enum mipc_nw_get_activity_info_cnf_tlv_enum {
    mipc_nw_get_activity_info_cnf_tlv_NONE = 0,
    /* period(in ms) for which Tx power level n is active. */
    /* type = struct, refer to nw_tx */
    MIPC_NW_GET_ACTIVITY_INFO_CNF_T_TX                      = 0x100,
    /* period(in ms) for which Rx is active. */
    /* type = uint32_t */
    MIPC_NW_GET_ACTIVITY_INFO_CNF_T_RX                      = 0x101,
    /* period(in ms) when modem is power collapsed. */
    /* type = uint32_t */
    MIPC_NW_GET_ACTIVITY_INFO_CNF_T_SLEEP_TIME              = 0x102,
    /* period(in ms) when modem is awake and in idle mode. */
    /* type = uint32_t */
    MIPC_NW_GET_ACTIVITY_INFO_CNF_T_IDLE_TIME               = 0x103,
    /* number of tx power levels, power levels is a series of contiguous (but not necessarily equally-sized) ranges of transmit power level. */
    /* type = uint8_t */
    MIPC_NW_GET_ACTIVITY_INFO_CNF_T_NUM_TX_LEVELS           = 0x104,
};

    /* MIPC_MSG.NW_SET_CA_REQ */
enum mipc_nw_set_ca_req_tlv_enum {
    mipc_nw_set_ca_req_tlv_NONE = 0,
    /* Now just support set LTE CA */
    /* type = uint8_t, refer to NW_SET_CA_RAT */
    MIPC_NW_SET_CA_REQ_T_RAT                                = 0x100,
    /* 0: turn off LTE Carrier Aggregation, 1: turn on LTE Carrier Aggregation. */
    /* type = uint8_t, refer to NW_CA_MODE */
    MIPC_NW_SET_CA_REQ_T_MODE                               = 0x101,
};

    /* MIPC_MSG.NW_SET_CA_CNF */
enum mipc_nw_set_ca_cnf_tlv_enum {
    mipc_nw_set_ca_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_LTE_RRC_STATE_REQ */
enum mipc_nw_get_lte_rrc_state_req_tlv_enum {
    mipc_nw_get_lte_rrc_state_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_LTE_RRC_STATE_CNF */
enum mipc_nw_get_lte_rrc_state_cnf_tlv_enum {
    mipc_nw_get_lte_rrc_state_cnf_tlv_NONE = 0,
    /*  */
    /* type = uint8_t */
    MIPC_NW_GET_LTE_RRC_STATE_CNF_T_MODE                    = 0x100,
    /* LTE RRC state */
    /* type = uint8_t, refer to LTE_RRC_STATE */
    MIPC_NW_GET_LTE_RRC_STATE_CNF_T_STATE                   = 0x101,
};

    /* MIPC_MSG.NW_GET_LTE_1XRTT_CELL_LIST_REQ */
enum mipc_nw_get_lte_1xrtt_cell_list_req_tlv_enum {
    mipc_nw_get_lte_1xrtt_cell_list_req_tlv_NONE = 0,
    /* 0: LTE available 1xRTT cell lists, 1: LTE unavailable 1xRTT cell lists. */
    /* type = uint8_t, refer to CELL_LIST_TYPE */
    MIPC_NW_GET_LTE_1XRTT_CELL_LIST_REQ_T_TYPE              = 0x100,
};

    /* MIPC_MSG.NW_GET_LTE_1XRTT_CELL_LIST_CNF */
enum mipc_nw_get_lte_1xrtt_cell_list_cnf_tlv_enum {
    mipc_nw_get_lte_1xrtt_cell_list_cnf_tlv_NONE = 0,
    /* number of LTE available/unavailable 1xRTT cell lists. */
    /* type = uint8_t */
    MIPC_NW_GET_LTE_1XRTT_CELL_LIST_CNF_T_COUNT             = 0x100,
    /* The cell LIST info of LTE available/unavailable 1xRTT cell lists. */
    /* type = struct_array, refer to 1xrtt_cell_info */
    MIPC_NW_GET_LTE_1XRTT_CELL_LIST_CNF_T_CELL_LIST         = 0x101,
};

    /* MIPC_MSG.NW_CLEAR_LTE_AVAILABLE_FILE_REQ */
enum mipc_nw_clear_lte_available_file_req_tlv_enum {
    mipc_nw_clear_lte_available_file_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_CLEAR_LTE_AVAILABLE_FILE_CNF */
enum mipc_nw_clear_lte_available_file_cnf_tlv_enum {
    mipc_nw_clear_lte_available_file_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_CA_LINK_CAPABILITY_REQ */
enum mipc_nw_get_ca_link_capability_req_tlv_enum {
    mipc_nw_get_ca_link_capability_req_tlv_NONE = 0,
    /* 0: Get CA downlink capability, 1: Get CA downlink and uplink capability. */
    /* type = uint8_t, refer to CA_LINK_MODE */
    MIPC_NW_GET_CA_LINK_CAPABILITY_REQ_T_MODE               = 0x100,
};

    /* MIPC_MSG.NW_GET_CA_LINK_CAPABILITY_CNF */
enum mipc_nw_get_ca_link_capability_cnf_tlv_enum {
    mipc_nw_get_ca_link_capability_cnf_tlv_NONE = 0,
    /* number of band combo */
    /* type = uint8_t */
    MIPC_NW_GET_CA_LINK_CAPABILITY_CNF_T_COUNT              = 0x100,
    /* CA link capability. */
    /* type = struct_array, refer to band_combo_info */
    MIPC_NW_GET_CA_LINK_CAPABILITY_CNF_T_BAND_COMBO         = 0x101,
};

    /* MIPC_MSG.NW_GET_CA_LINK_ENABLE_STATUS_REQ */
enum mipc_nw_get_ca_link_enable_status_req_tlv_enum {
    mipc_nw_get_ca_link_enable_status_req_tlv_NONE = 0,
    /* Get UL/DL CA enable status for the specified band_combo */
    /* type = uint8_t, refer to CA_LINK_ENABLE_MODE */
    MIPC_NW_GET_CA_LINK_ENABLE_STATUS_REQ_T_MODE            = 0x100,
    /* specific band combo */
    /* type = string */
    MIPC_NW_GET_CA_LINK_ENABLE_STATUS_REQ_T_BAND_COMBO      = 0x101,
};

    /* MIPC_MSG.NW_GET_CA_LINK_ENABLE_STATUS_CNF */
enum mipc_nw_get_ca_link_enable_status_cnf_tlv_enum {
    mipc_nw_get_ca_link_enable_status_cnf_tlv_NONE = 0,
    /* UL/DL CA enable status of specific band combo. */
    /* type = uint8_t, refer to BAND_COMBO_ENABLE_STATUS */
    MIPC_NW_GET_CA_LINK_ENABLE_STATUS_CNF_T_STATUS          = 0x100,
};

    /* MIPC_MSG.NW_GET_TM9_ENABLE_STATUS_REQ */
enum mipc_nw_get_tm9_enable_status_req_tlv_enum {
    mipc_nw_get_tm9_enable_status_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_TM9_ENABLE_STATUS_CNF */
enum mipc_nw_get_tm9_enable_status_cnf_tlv_enum {
    mipc_nw_get_tm9_enable_status_cnf_tlv_NONE = 0,
    /* FDD TM9 enable status */
    /* type = uint8_t, refer to TM9_ENABLE_STATUS */
    MIPC_NW_GET_TM9_ENABLE_STATUS_CNF_T_TM9_FDD_SETTING     = 0x100,
    /* TDD TM9 enable status */
    /* type = uint8_t, refer to TM9_ENABLE_STATUS */
    MIPC_NW_GET_TM9_ENABLE_STATUS_CNF_T_TM9_TDD_SETTING     = 0x101,
};

    /* MIPC_MSG.NW_SET_TM9_ENABLE_STATUS_REQ */
enum mipc_nw_set_tm9_enable_status_req_tlv_enum {
    mipc_nw_set_tm9_enable_status_req_tlv_NONE = 0,
    /* 0: Set FDD TM9, 1: Set TDD TM9 */
    /* type = uint8_t, refer to TM9_SETTING_TYPE */
    MIPC_NW_SET_TM9_ENABLE_STATUS_REQ_T_TYPE                = 0x100,
    /* TDD TM9 enable status */
    /* type = uint8_t, refer to TM9_ENABLE_STATUS */
    MIPC_NW_SET_TM9_ENABLE_STATUS_REQ_T_STATUS              = 0x101,
};

    /* MIPC_MSG.NW_SET_TM9_ENABLE_STATUS_CNF */
enum mipc_nw_set_tm9_enable_status_cnf_tlv_enum {
    mipc_nw_set_tm9_enable_status_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_OMADM_CONF_REQ */
enum mipc_nw_get_omadm_conf_req_tlv_enum {
    mipc_nw_get_omadm_conf_req_tlv_NONE = 0,
    /* OMA-DM node type */
    /* type = uint8_t, refer to OMADM_NODE_TYPE */
    MIPC_NW_GET_OMADM_CONF_REQ_T_TYPE                       = 0x100,
};

    /* MIPC_MSG.NW_GET_OMADM_CONF_CNF */
enum mipc_nw_get_omadm_conf_cnf_tlv_enum {
    mipc_nw_get_omadm_conf_cnf_tlv_NONE = 0,
    /* OMA-DM configured value */
    /* type = string */
    MIPC_NW_GET_OMADM_CONF_CNF_T_NODE_VALUE                 = 0x100,
};

    /* MIPC_MSG.NW_SET_OMADM_CONF_REQ */
enum mipc_nw_set_omadm_conf_req_tlv_enum {
    mipc_nw_set_omadm_conf_req_tlv_NONE = 0,
    /* OMA-DM node type */
    /* type = uint8_t, refer to OMADM_NODE_TYPE */
    MIPC_NW_SET_OMADM_CONF_REQ_T_TYPE                       = 0x100,
    /* OMA-DM configured value */
    /* type = string */
    MIPC_NW_SET_OMADM_CONF_REQ_T_NODE_VALUE                 = 0x101,
};

    /* MIPC_MSG.NW_SET_OMADM_CONF_CNF */
enum mipc_nw_set_omadm_conf_cnf_tlv_enum {
    mipc_nw_set_omadm_conf_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_CA_BAND_MODE_REQ */
enum mipc_nw_get_ca_band_mode_req_tlv_enum {
    mipc_nw_get_ca_band_mode_req_tlv_NONE = 0,
    /* Primary band for which CA bitmap needs to be provided */
    /* type = int32_t */
    MIPC_NW_GET_CA_BAND_MODE_REQ_T_PRIMARY_ID               = 0x100,
};

    /* MIPC_MSG.NW_GET_CA_BAND_MODE_CNF */
enum mipc_nw_get_ca_band_mode_cnf_tlv_enum {
    mipc_nw_get_ca_band_mode_cnf_tlv_NONE = 0,
    /* bitmap band info */
    /* type = struct, refer to nw_ca_band */
    MIPC_NW_GET_CA_BAND_MODE_CNF_T_BAND                     = 0x100,
};

    /* MIPC_MSG.NW_SET_CA_LINK_ENABLE_STATUS_REQ */
enum mipc_nw_set_ca_link_enable_status_req_tlv_enum {
    mipc_nw_set_ca_link_enable_status_req_tlv_NONE = 0,
    /* The list type of CA combination band list */
    /* type = uint8_t, refer to CA_COMB_LIST_TYPE */
    MIPC_NW_SET_CA_LINK_ENABLE_STATUS_REQ_T_LIST_TYPE       = 0x100,
    /* CA combination band list */
    /* type = string */
    MIPC_NW_SET_CA_LINK_ENABLE_STATUS_REQ_T_CA_COMB_LIST    = 0x101,
    /* UL/DL, just for future expansion, now this parameter is invalid */
    /* type = uint8_t */
    MIPC_NW_SET_CA_LINK_ENABLE_STATUS_REQ_T_LINK_TYPE       = 0x102,
};

    /* MIPC_MSG.NW_SET_CA_LINK_ENABLE_STATUS_CNF */
enum mipc_nw_set_ca_link_enable_status_cnf_tlv_enum {
    mipc_nw_set_ca_link_enable_status_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_LTE_DATA_REQ */
enum mipc_nw_get_lte_data_req_tlv_enum {
    mipc_nw_get_lte_data_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_LTE_DATA_CNF */
enum mipc_nw_get_lte_data_cnf_tlv_enum {
    mipc_nw_get_lte_data_cnf_tlv_NONE = 0,
    /* The registration state of LTE. */
    /* type = uint32_t */
    MIPC_NW_GET_LTE_DATA_CNF_T_REG_STATE                    = 0x100,
    /* MCC */
    /* type = uint32_t */
    MIPC_NW_GET_LTE_DATA_CNF_T_MCC                          = 0x101,
    /* MNC */
    /* type = uint32_t */
    MIPC_NW_GET_LTE_DATA_CNF_T_MNC                          = 0x102,
    /* cell id */
    /* type = uint32_t */
    MIPC_NW_GET_LTE_DATA_CNF_T_CELL_ID                      = 0x103,
    /* The band of LTE. */
    /* type = uint32_t */
    MIPC_NW_GET_LTE_DATA_CNF_T_BAND                         = 0x104,
    /* The bandwidth of LTE. */
    /* type = uint32_t */
    MIPC_NW_GET_LTE_DATA_CNF_T_BANDWIDTH                    = 0x105,
    /* ul channel */
    /* type = uint32_t */
    MIPC_NW_GET_LTE_DATA_CNF_T_UL_CHANNEL                   = 0x106,
    /* dl channel */
    /* type = uint32_t */
    MIPC_NW_GET_LTE_DATA_CNF_T_DL_CHANNEL                   = 0x107,
    /* The rssi of LTE. */
    /* type = uint32_t */
    MIPC_NW_GET_LTE_DATA_CNF_T_RSSI                         = 0x108,
    /* The rsrp of LTE. */
    /* type = uint32_t */
    MIPC_NW_GET_LTE_DATA_CNF_T_RSRP                         = 0x109,
    /* The rsrq of LTE. */
    /* type = uint32_t */
    MIPC_NW_GET_LTE_DATA_CNF_T_RSRQ                         = 0x10A,
    /* The tx power of LTE. */
    /* type = uint32_t */
    MIPC_NW_GET_LTE_DATA_CNF_T_TX_POWER                     = 0x10B,
};

    /* MIPC_MSG.NW_SET_TUW_TIMER_LENGTH_REQ */
enum mipc_nw_set_tuw_timer_length_req_tlv_enum {
    mipc_nw_set_tuw_timer_length_req_tlv_NONE = 0,
    /* Number of updated tuw, 1~3 */
    /* type = uint8_t */
    MIPC_NW_SET_TUW_TIMER_LENGTH_REQ_T_TUW_NUM              = 0x100,
    /* The tuw id and tuw length */
    /* type = struct_array, refer to nw_tuw_info */
    MIPC_NW_SET_TUW_TIMER_LENGTH_REQ_T_TUW                  = 0x101,
};

    /* MIPC_MSG.NW_SET_TUW_TIMER_LENGTH_CNF */
enum mipc_nw_set_tuw_timer_length_cnf_tlv_enum {
    mipc_nw_set_tuw_timer_length_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_TUW_TIMER_LENGTH_REQ */
enum mipc_nw_get_tuw_timer_length_req_tlv_enum {
    mipc_nw_get_tuw_timer_length_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_TUW_TIMER_LENGTH_CNF */
enum mipc_nw_get_tuw_timer_length_cnf_tlv_enum {
    mipc_nw_get_tuw_timer_length_cnf_tlv_NONE = 0,
    /* TUW1 length */
    /* type = uint32_t */
    MIPC_NW_GET_TUW_TIMER_LENGTH_CNF_T_TUW1                 = 0x100,
    /* TUW2 length */
    /* type = uint32_t */
    MIPC_NW_GET_TUW_TIMER_LENGTH_CNF_T_TUW2                 = 0x101,
    /* TUW3 length */
    /* type = uint32_t */
    MIPC_NW_GET_TUW_TIMER_LENGTH_CNF_T_TUW3                 = 0x102,
};

    /* MIPC_MSG.NW_GET_5GUW_INFO_REQ */
enum mipc_nw_get_5guw_info_req_tlv_enum {
    mipc_nw_get_5guw_info_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_5GUW_INFO_CNF */
enum mipc_nw_get_5guw_info_cnf_tlv_enum {
    mipc_nw_get_5guw_info_cnf_tlv_NONE = 0,
    /* 0: don't display 5G UW, 1: display 5G UW. */
    /* type = uint8_t */
    MIPC_NW_GET_5GUW_INFO_CNF_T_DISPLAY_5GUW                = 0x100,
    /* 0: not on n77 band, 1: on n77 band */
    /* type = uint8_t */
    MIPC_NW_GET_5GUW_INFO_CNF_T_ON_N77_BAND                 = 0x101,
    /* 0: not on fr2 band, 1: on fr2 band */
    /* type = uint8_t */
    MIPC_NW_GET_5GUW_INFO_CNF_T_ON_FR2_BAND                 = 0x102,
    /* 0: not allowed, 1: allowed */
    /* type = uint8_t */
    MIPC_NW_GET_5GUW_INFO_CNF_T_5GUW_ALLOWED                = 0x103,
};

    /* MIPC_MSG.NW_GET_NR_CA_BAND_REQ */
enum mipc_nw_get_nr_ca_band_req_tlv_enum {
    mipc_nw_get_nr_ca_band_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_NR_CA_BAND_CNF */
enum mipc_nw_get_nr_ca_band_cnf_tlv_enum {
    mipc_nw_get_nr_ca_band_cnf_tlv_NONE = 0,
    /*  */
    /* type = int32_t */
    MIPC_NW_GET_NR_CA_BAND_CNF_T_IS_ENDC                    = 0x100,
    /* The num of nr ca band */
    /* type = uint8_t */
    MIPC_NW_GET_NR_CA_BAND_CNF_T_BAND_NUM                   = 0x101,
    /* The nr ca band */
    /* type = struct, refer to nr_ca_band */
    MIPC_NW_GET_NR_CA_BAND_CNF_T_BAND                       = 0x102,
};

    /* MIPC_MSG.NW_GET_NR_SCS_REQ */
enum mipc_nw_get_nr_scs_req_tlv_enum {
    mipc_nw_get_nr_scs_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_NR_SCS_CNF */
enum mipc_nw_get_nr_scs_cnf_tlv_enum {
    mipc_nw_get_nr_scs_cnf_tlv_NONE = 0,
    /* nr5g subcarrier spacing in khz */
    /* type = int32_t */
    MIPC_NW_GET_NR_SCS_CNF_T_SCS                            = 0x100,
};

    /* MIPC_MSG.NW_GET_PHYSICAL_CHANNEL_CONFIGS_REQ */
enum mipc_nw_get_physical_channel_configs_req_tlv_enum {
    mipc_nw_get_physical_channel_configs_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_PHYSICAL_CHANNEL_CONFIGS_CNF */
enum mipc_nw_get_physical_channel_configs_cnf_tlv_enum {
    mipc_nw_get_physical_channel_configs_cnf_tlv_NONE = 0,
    /* physical channel configs information. */
    /* type = struct, refer to physical_channel_info_v1 */
    MIPC_NW_GET_PHYSICAL_CHANNEL_CONFIGS_CNF_T_PHYSICAL_CHANNEL_CONFIGS_LIST_V1 = 0x100,
};

    /* MIPC_MSG.NW_OS_ID_UPDATE_REQ */
enum mipc_nw_os_id_update_req_tlv_enum {
    mipc_nw_os_id_update_req_tlv_NONE = 0,
    /* The number of the os_id,the number value of:0~15 */
    /* type = uint8_t */
    MIPC_NW_OS_ID_UPDATE_REQ_T_OS_ID_NUM                    = 0x100,
    /* The set of the os_id. */
    /* type = struct_array, refer to os_id_info */
    MIPC_NW_OS_ID_UPDATE_REQ_T_OS_ID_LIST                   = 0x101,
};

    /* MIPC_MSG.NW_OS_ID_UPDATE_CNF */
enum mipc_nw_os_id_update_cnf_tlv_enum {
    mipc_nw_os_id_update_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_START_NETWORK_SCAN_REQ */
enum mipc_nw_start_network_scan_req_tlv_enum {
    mipc_nw_start_network_scan_req_tlv_NONE = 0,
    /* 0: one_shot, 1: periodic */
    /* type = uint32_t, refer to NW_SCAN_TYPE */
    MIPC_NW_START_NETWORK_SCAN_REQ_T_SCAN_TYPE              = 0x100,
    /* periodic interval, 5~300 sec */
    /* type = uint32_t */
    MIPC_NW_START_NETWORK_SCAN_REQ_T_INTERVAL               = 0x101,
    /* Its value must smaller than 3600 sec */
    /* type = uint32_t */
    MIPC_NW_START_NETWORK_SCAN_REQ_T_MAX_SEARCH_TIME        = 0x102,
    /* 0: disable(one final result), 1: enable(multiple partial result) */
    /* type = uint32_t, refer to NW_INCREMENTAL_RESULTS */
    MIPC_NW_START_NETWORK_SCAN_REQ_T_INCREMENTAL_RESULTS    = 0x103,
    /* 1~10 sec, 0: default modem value, send whenever updated */
    /* type = uint32_t */
    MIPC_NW_START_NETWORK_SCAN_REQ_T_INCREMENTAL_RESULT_PERIODICITY = 0x104,
    /* The list of rat info. 1 RAT 1 record, the max num of record is 8. */
    /* type = struct, refer to nw_record_info */
    MIPC_NW_START_NETWORK_SCAN_REQ_T_RECORD_LIST            = 0x105,
    /* PLMN id, the max num of plmn is 20 */
    /* type = struct, refer to nw_plmn_info */
    MIPC_NW_START_NETWORK_SCAN_REQ_T_PLMN_LIST              = 0x106,
};

    /* MIPC_MSG.NW_START_NETWORK_SCAN_CNF */
enum mipc_nw_start_network_scan_cnf_tlv_enum {
    mipc_nw_start_network_scan_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_STOP_NETWORK_SCAN_REQ */
enum mipc_nw_stop_network_scan_req_tlv_enum {
    mipc_nw_stop_network_scan_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_STOP_NETWORK_SCAN_CNF */
enum mipc_nw_stop_network_scan_cnf_tlv_enum {
    mipc_nw_stop_network_scan_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_NETWORK_SCAN_SUPPORT_STATUS_REQ */
enum mipc_nw_get_network_scan_support_status_req_tlv_enum {
    mipc_nw_get_network_scan_support_status_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_NETWORK_SCAN_SUPPORT_STATUS_CNF */
enum mipc_nw_get_network_scan_support_status_cnf_tlv_enum {
    mipc_nw_get_network_scan_support_status_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_SET_5GUC_REQ */
enum mipc_nw_set_5guc_req_tlv_enum {
    mipc_nw_set_5guc_req_tlv_NONE = 0,
    /* 0~240 seconds, default setting of 30 seconds, omit means no change */
    /* type = uint32_t */
    MIPC_NW_SET_5GUC_REQ_T_REFRESH_TIMER_LENGTH             = 0x100,
    /* A bitmap of nsa band, omit means no change. n41,n258,n260,n261,n262 default enable */
    /* type = struct, refer to sys_nr_band */
    MIPC_NW_SET_5GUC_REQ_T_NSA_BAND                         = 0x101,
    /* A bitmap of sa band, omit means no change. n41,n258,n260,n261,n262 default enable */
    /* type = struct, refer to sys_nr_band */
    MIPC_NW_SET_5GUC_REQ_T_SA_BAND                          = 0x102,
    /* 0: disable bandwidth check, 1: enable bandwidth check, omit means no change */
    /* type = uint32_t, refer to NW_BW_CHECK */
    MIPC_NW_SET_5GUC_REQ_T_BW_CHECK_ENABLE                  = 0x103,
    /* 0~240 MHz, default setting of 60 MHz, omit means no change */
    /* type = uint32_t */
    MIPC_NW_SET_5GUC_REQ_T_BW_CHECK_THRESHOLD               = 0x104,
};

    /* MIPC_MSG.NW_SET_5GUC_CNF */
enum mipc_nw_set_5guc_cnf_tlv_enum {
    mipc_nw_set_5guc_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_5GUC_SETTING_REQ */
enum mipc_nw_get_5guc_setting_req_tlv_enum {
    mipc_nw_get_5guc_setting_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_5GUC_SETTING_CNF */
enum mipc_nw_get_5guc_setting_cnf_tlv_enum {
    mipc_nw_get_5guc_setting_cnf_tlv_NONE = 0,
    /* 0~240 seconds, default setting of 30 seconds */
    /* type = uint32_t */
    MIPC_NW_GET_5GUC_SETTING_CNF_T_REFRESH_TIMER_LENGTH     = 0x100,
    /* A bitmap of nsa band. n41,n258,n260,n261,n262 default enable */
    /* type = struct, refer to sys_nr_band */
    MIPC_NW_GET_5GUC_SETTING_CNF_T_NSA_BAND                 = 0x101,
    /* A bitmap of sa band. n41,n258,n260,n261,n262 default enable */
    /* type = struct, refer to sys_nr_band */
    MIPC_NW_GET_5GUC_SETTING_CNF_T_SA_BAND                  = 0x102,
    /* 0: disable bandwidth check, 1: enable bandwidth check */
    /* type = uint32_t, refer to NW_BW_CHECK */
    MIPC_NW_GET_5GUC_SETTING_CNF_T_BW_CHECK_ENABLE          = 0x103,
    /* 0~240 MHz */
    /* type = uint32_t */
    MIPC_NW_GET_5GUC_SETTING_CNF_T_BW_CHECK_THRESHOLD       = 0x104,
};

    /* MIPC_MSG.NW_GET_5GUC_INFO_REQ */
enum mipc_nw_get_5guc_info_req_tlv_enum {
    mipc_nw_get_5guc_info_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_5GUC_INFO_CNF */
enum mipc_nw_get_5guc_info_cnf_tlv_enum {
    mipc_nw_get_5guc_info_cnf_tlv_NONE = 0,
    /* 0: not display 5G UC, 1: display 5G UC */
    /* type = uint32_t, refer to NW_5GUC_STATE */
    MIPC_NW_GET_5GUC_INFO_CNF_T_DISPLAY_5GUC                = 0x100,
    /* 0: not on UC band(ex: n41), 1: on UC band(ex: n41) */
    /* type = uint32_t, refer to NW_UC_BAND */
    MIPC_NW_GET_5GUC_INFO_CNF_T_ON_UC_BAND                  = 0x101,
    /* 0~300 MHz */
    /* type = uint32_t */
    MIPC_NW_GET_5GUC_INFO_CNF_T_AGG_BW                      = 0x102,
};

    /* MIPC_MSG.NW_GET_FIRST_PLMN_REQ */
enum mipc_nw_get_first_plmn_req_tlv_enum {
    mipc_nw_get_first_plmn_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.NW_GET_FIRST_PLMN_CNF */
enum mipc_nw_get_first_plmn_cnf_tlv_enum {
    mipc_nw_get_first_plmn_cnf_tlv_NONE = 0,
    /* mcc */
    /* type = string */
    MIPC_NW_GET_FIRST_PLMN_CNF_T_MCC                        = 0x100,
    /* mnc */
    /* type = string */
    MIPC_NW_GET_FIRST_PLMN_CNF_T_MNC                        = 0x101,
};

    /* MIPC_MSG.NW_GET_NSSAI_REQ */
enum mipc_nw_get_nssai_req_tlv_enum {
    mipc_nw_get_nssai_req_tlv_NONE = 0,
    /* indicate NSSAI TYPE to get */
    /* type = uint8_t, refer to NSSAI_TYPE_ENUM */
    MIPC_NW_GET_NSSAI_REQ_T_NSSAI_TYPE                      = 0x100,
    /* plmn id, mcc1, mcc2, mcc3, mnc1, mnc2, mnc3 */
    /* type = byte_array */
    MIPC_NW_GET_NSSAI_REQ_T_PLMN_ID                         = 0x101,
};

    /* MIPC_MSG.NW_GET_NSSAI_CNF */
enum mipc_nw_get_nssai_cnf_tlv_enum {
    mipc_nw_get_nssai_cnf_tlv_NONE = 0,
    /* s_nssai list */
    /* type = struct, refer to s_nssai_struct */
    MIPC_NW_GET_NSSAI_CNF_T_DEFAULT_CONFIGURED_NSSAI_LIST   = 0x100,
    /* rejected s_nssai list */
    /* type = struct, refer to rejected_s_nssai_struct */
    MIPC_NW_GET_NSSAI_CNF_T_REJECTED_NSSAI_3GPP_LIST        = 0x101,
    /* rejected s_nssai list */
    /* type = struct, refer to rejected_s_nssai_struct */
    MIPC_NW_GET_NSSAI_CNF_T_REJECTED_NSSAI_NON3GPP_LIST     = 0x102,
    /* s_nssai list */
    /* type = struct, refer to plmn_specific_s_nssai_struct */
    MIPC_NW_GET_NSSAI_CNF_T_CONFIGURED_NSSAI_LIST           = 0x103,
    /* s_nssai list */
    /* type = struct, refer to plmn_specific_s_nssai_struct */
    MIPC_NW_GET_NSSAI_CNF_T_ALLOWED_NSSAI_3GPP_LIST         = 0x104,
    /* s_nssai list */
    /* type = struct, refer to plmn_specific_s_nssai_struct */
    MIPC_NW_GET_NSSAI_CNF_T_ALLOWED_NSSAI_NON3GPP_LIST      = 0x105,
    /* preferred s_nssai list */
    /* type = struct, refer to s_nssai_struct */
    MIPC_NW_GET_NSSAI_CNF_T_PREFERRED_NSSAI_3GPP_LIST       = 0x106,
    /* preferred non 3gpp s_nssai list */
    /* type = struct, refer to s_nssai_struct */
    MIPC_NW_GET_NSSAI_CNF_T_PREFERRED_NSSAI_NON3GPP_LIST    = 0x107,
};

    /* MIPC_MSG.SIM_PIN_PROTECT_REQ */
enum mipc_sim_pin_protect_req_tlv_enum {
    mipc_sim_pin_protect_req_tlv_NONE = 0,
    /* pin type */
    /* type = uint8_t, refer to SIM_PIN_TYPE */
    MIPC_SIM_PIN_PROTECT_REQ_T_PIN_TYPE                     = 0x100,
    /* pin operation */
    /* type = uint8_t, refer to SIM_PIN_PROTECTION */
    MIPC_SIM_PIN_PROTECT_REQ_T_PIN_OP                       = 0x101,
    /* pin code */
    /* type = string */
    MIPC_SIM_PIN_PROTECT_REQ_T_PIN_CODE                     = 0x8102,
};

    /* MIPC_MSG.SIM_PIN_PROTECT_CNF */
enum mipc_sim_pin_protect_cnf_tlv_enum {
    mipc_sim_pin_protect_cnf_tlv_NONE = 0,
    /* pin type */
    /* type = uint8_t, refer to SIM_PIN_TYPE */
    MIPC_SIM_PIN_PROTECT_CNF_T_PIN_TYPE                     = 0x100,
    /* pin state */
    /* type = uint8_t, refer to SIM_PIN_STATE */
    MIPC_SIM_PIN_PROTECT_CNF_T_PIN_STATE                    = 0x101,
    /* remaining attempts */
    /* type = uint32_t */
    MIPC_SIM_PIN_PROTECT_CNF_T_REMAINING_ATTEMPTS           = 0x102,
};

    /* MIPC_MSG.SIM_CHANGE_PIN_REQ */
enum mipc_sim_change_pin_req_tlv_enum {
    mipc_sim_change_pin_req_tlv_NONE = 0,
    /* pin type */
    /* type = uint8_t, refer to SIM_PIN_TYPE */
    MIPC_SIM_CHANGE_PIN_REQ_T_PIN_TYPE                      = 0x100,
    /* old pin code */
    /* type = string */
    MIPC_SIM_CHANGE_PIN_REQ_T_OLD_PIN                       = 0x8101,
    /* new pin code */
    /* type = string */
    MIPC_SIM_CHANGE_PIN_REQ_T_NEW_PIN                       = 0x8102,
};

    /* MIPC_MSG.SIM_CHANGE_PIN_CNF */
enum mipc_sim_change_pin_cnf_tlv_enum {
    mipc_sim_change_pin_cnf_tlv_NONE = 0,
    /* pin type */
    /* type = uint8_t, refer to SIM_PIN_TYPE */
    MIPC_SIM_CHANGE_PIN_CNF_T_PIN_TYPE                      = 0x100,
    /* pin state */
    /* type = uint8_t, refer to SIM_PIN_STATE */
    MIPC_SIM_CHANGE_PIN_CNF_T_PIN_STATE                     = 0x101,
    /* remaining attempts */
    /* type = uint32_t */
    MIPC_SIM_CHANGE_PIN_CNF_T_REMAINING_ATTEMPTS            = 0x102,
};

    /* MIPC_MSG.SIM_VERIFY_PIN_REQ */
enum mipc_sim_verify_pin_req_tlv_enum {
    mipc_sim_verify_pin_req_tlv_NONE = 0,
    /* pin type */
    /* type = uint8_t, refer to SIM_PIN_TYPE */
    MIPC_SIM_VERIFY_PIN_REQ_T_PIN_TYPE                      = 0x100,
    /* pin code */
    /* type = string */
    MIPC_SIM_VERIFY_PIN_REQ_T_PIN_CODE                      = 0x8101,
};

    /* MIPC_MSG.SIM_VERIFY_PIN_CNF */
enum mipc_sim_verify_pin_cnf_tlv_enum {
    mipc_sim_verify_pin_cnf_tlv_NONE = 0,
    /* pin type */
    /* type = uint8_t, refer to SIM_PIN_TYPE */
    MIPC_SIM_VERIFY_PIN_CNF_T_PIN_TYPE                      = 0x100,
    /* pin state */
    /* type = uint8_t, refer to SIM_PIN_STATE */
    MIPC_SIM_VERIFY_PIN_CNF_T_PIN_STATE                     = 0x101,
    /* remaining attempts */
    /* type = uint32_t */
    MIPC_SIM_VERIFY_PIN_CNF_T_REMAINING_ATTEMPTS            = 0x102,
};

    /* MIPC_MSG.SIM_UNBLOCK_PIN_REQ */
enum mipc_sim_unblock_pin_req_tlv_enum {
    mipc_sim_unblock_pin_req_tlv_NONE = 0,
    /* pin type */
    /* type = uint8_t, refer to SIM_PIN_TYPE */
    MIPC_SIM_UNBLOCK_PIN_REQ_T_PIN_TYPE                     = 0x100,
    /* puk code */
    /* type = string */
    MIPC_SIM_UNBLOCK_PIN_REQ_T_PUK_CODE                     = 0x8101,
    /* pin code */
    /* type = string */
    MIPC_SIM_UNBLOCK_PIN_REQ_T_PIN_CODE                     = 0x8102,
};

    /* MIPC_MSG.SIM_UNBLOCK_PIN_CNF */
enum mipc_sim_unblock_pin_cnf_tlv_enum {
    mipc_sim_unblock_pin_cnf_tlv_NONE = 0,
    /* pin type */
    /* type = uint8_t, refer to SIM_PIN_TYPE */
    MIPC_SIM_UNBLOCK_PIN_CNF_T_PIN_TYPE                     = 0x100,
    /* pin state */
    /* type = uint8_t, refer to SIM_PIN_STATE */
    MIPC_SIM_UNBLOCK_PIN_CNF_T_PIN_STATE                    = 0x101,
    /* remaining attempts */
    /* type = uint32_t */
    MIPC_SIM_UNBLOCK_PIN_CNF_T_REMAINING_ATTEMPTS           = 0x102,
};

    /* MIPC_MSG.SIM_GET_PIN_INFO_REQ */
enum mipc_sim_get_pin_info_req_tlv_enum {
    mipc_sim_get_pin_info_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SIM_GET_PIN_INFO_CNF */
enum mipc_sim_get_pin_info_cnf_tlv_enum {
    mipc_sim_get_pin_info_cnf_tlv_NONE = 0,
    /* pin type */
    /* type = uint8_t, refer to SIM_PIN_TYPE */
    MIPC_SIM_GET_PIN_INFO_CNF_T_PIN_TYPE                    = 0x100,
    /* pin state */
    /* type = uint8_t, refer to SIM_PIN_STATE */
    MIPC_SIM_GET_PIN_INFO_CNF_T_PIN_STATE                   = 0x101,
    /* remaining attempts */
    /* type = uint32_t */
    MIPC_SIM_GET_PIN_INFO_CNF_T_REMAINING_ATTEMPTS          = 0x102,
};

    /* MIPC_MSG.SIM_GET_PIN_LIST_REQ */
enum mipc_sim_get_pin_list_req_tlv_enum {
    mipc_sim_get_pin_list_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SIM_GET_PIN_LIST_CNF */
enum mipc_sim_get_pin_list_cnf_tlv_enum {
    mipc_sim_get_pin_list_cnf_tlv_NONE = 0,
    /* pin21 */
    /* type = struct, refer to sim_pin_desc */
    MIPC_SIM_GET_PIN_LIST_CNF_T_PIN1                        = 0x100,
    /* pin2 */
    /* type = struct, refer to sim_pin_desc */
    MIPC_SIM_GET_PIN_LIST_CNF_T_PIN2                        = 0x101,
    /* NW PIN definded in 3GPP 22.022 */
    /* type = struct, refer to sim_pin_desc */
    MIPC_SIM_GET_PIN_LIST_CNF_T_NW_PIN                      = 0x102,
    /* SUB_NW PIN definded in 3GPP 22.022 */
    /* type = struct, refer to sim_pin_desc */
    MIPC_SIM_GET_PIN_LIST_CNF_T_SUB_NW_PIN                  = 0x103,
    /* SP PIN definded in 3GPP 22.022 */
    /* type = struct, refer to sim_pin_desc */
    MIPC_SIM_GET_PIN_LIST_CNF_T_SP_PIN                      = 0x104,
    /* CORP PIN definded in 3GPP 22.022 */
    /* type = struct, refer to sim_pin_desc */
    MIPC_SIM_GET_PIN_LIST_CNF_T_CORP_PIN                    = 0x105,
    /* SIM PIN definded in 3GPP 22.022 */
    /* type = struct, refer to sim_pin_desc */
    MIPC_SIM_GET_PIN_LIST_CNF_T_SIM_PIN                     = 0x106,
};

    /* MIPC_MSG.SIM_STATE_REQ */
enum mipc_sim_state_req_tlv_enum {
    mipc_sim_state_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SIM_STATE_CNF */
enum mipc_sim_state_cnf_tlv_enum {
    mipc_sim_state_cnf_tlv_NONE = 0,
    /* sim slot state */
    /* type = uint8_t, refer to SIM_STATE */
    MIPC_SIM_STATE_CNF_T_STATE                              = 0x100,
    /* sim slot id */
    /* type = uint32_t */
    MIPC_SIM_STATE_CNF_T_SIM_ID                             = 0x101,
    /* sim protocol id */
    /* type = uint32_t */
    MIPC_SIM_STATE_CNF_T_PS_ID                              = 0x102,
};

    /* MIPC_MSG.SIM_STATUS_REQ */
enum mipc_sim_status_req_tlv_enum {
    mipc_sim_status_req_tlv_NONE = 0,
    /* 0 means mbim mode, only retrun STATUS, SIM_ID and PS_ID, 1 means full mode, return all the TLVs defined in STATUS_CNF  */
    /* type = uint8_t */
    MIPC_SIM_STATUS_REQ_T_MODE                              = 0x100,
};

    /* MIPC_MSG.SIM_STATUS_CNF */
enum mipc_sim_status_cnf_tlv_enum {
    mipc_sim_status_cnf_tlv_NONE = 0,
    /* sim status */
    /* type = uint8_t, refer to SIM_STATUS */
    MIPC_SIM_STATUS_CNF_T_STATUS                            = 0x100,
    /* sim slot id,0-based, the value may be 0,1,2,3 */
    /* type = uint8_t */
    MIPC_SIM_STATUS_CNF_T_SIM_ID                            = 0x101,
    /* sim protocol id,0-based, the value may be 0,1,2,3 */
    /* type = uint8_t */
    MIPC_SIM_STATUS_CNF_T_PS_ID                             = 0x102,
    /* card present state for android */
    /* type = uint8_t, refer to SIM_CARD_PRESENT_STATE */
    MIPC_SIM_STATUS_CNF_T_CARD_PRESENT_STATE                = 0x103,
    /* always 0, not support now */
    /* type = uint8_t, refer to SIM_ENABLED */
    MIPC_SIM_STATUS_CNF_T_UPIN_STATUS                       = 0x104,
    /* is testsim or not */
    /* type = uint8_t */
    MIPC_SIM_STATUS_CNF_T_TEST_SIM                          = 0x105,
    /* 0xff means invalid */
    /* type = uint8_t */
    MIPC_SIM_STATUS_CNF_T_GSM_APP_IDX                       = 0x106,
    /* 0xff means invalid */
    /* type = uint8_t */
    MIPC_SIM_STATUS_CNF_T_CDMA_APP_IDX                      = 0x107,
    /* 0xff means invalid */
    /* type = uint8_t */
    MIPC_SIM_STATUS_CNF_T_ISIM_APP_IDX                      = 0x108,
    /* number of application */
    /* type = uint8_t */
    MIPC_SIM_STATUS_CNF_T_APP_COUNT                         = 0x109,
    /* application description */
    /* type = struct_array, refer to app_status_desc */
    MIPC_SIM_STATUS_CNF_T_APP_LIST                          = 0x810A,
    /* eid */
    /* type = string */
    MIPC_SIM_STATUS_CNF_T_EID                               = 0x810B,
    /* iccid string */
    /* type = string */
    MIPC_SIM_STATUS_CNF_T_ICCID                             = 0x810C,
    /* ATR string */
    /* type = string */
    MIPC_SIM_STATUS_CNF_T_ATR                               = 0x810D,
    /* msisdn ready */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_SIM_STATUS_CNF_T_MSISDN_READY                      = 0x10E,
    /* type = uint8_t */
    MIPC_SIM_STATUS_CNF_T_PIN1                              = 0x10F,
    /* type = uint8_t */
    MIPC_SIM_STATUS_CNF_T_PIN2                              = 0x110,
    /* type = uint8_t */
    MIPC_SIM_STATUS_CNF_T_PUK1                              = 0x111,
    /* type = uint8_t */
    MIPC_SIM_STATUS_CNF_T_PUK2                              = 0x112,
};

    /* MIPC_MSG.SIM_ICCID_REQ */
enum mipc_sim_iccid_req_tlv_enum {
    mipc_sim_iccid_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SIM_ICCID_CNF */
enum mipc_sim_iccid_cnf_tlv_enum {
    mipc_sim_iccid_cnf_tlv_NONE = 0,
    /* iccid string */
    /* type = string */
    MIPC_SIM_ICCID_CNF_T_ICCID                              = 0x8100,
};

    /* MIPC_MSG.SIM_IMSI_REQ */
enum mipc_sim_imsi_req_tlv_enum {
    mipc_sim_imsi_req_tlv_NONE = 0,
    /* 0 for GSM, 1 for C2K */
    /* type = uint8_t */
    MIPC_SIM_IMSI_REQ_T_MODE                                = 0x100,
    /* only work for C2K mode, will use at+ecimi=app_id to query imsi if app_id is exist */
    /* type = uint8_t, refer to SIM_APP_TYPE_EX */
    MIPC_SIM_IMSI_REQ_T_APP_ID                              = 0x101,
};

    /* MIPC_MSG.SIM_IMSI_CNF */
enum mipc_sim_imsi_cnf_tlv_enum {
    mipc_sim_imsi_cnf_tlv_NONE = 0,
    /* imsi string */
    /* type = string */
    MIPC_SIM_IMSI_CNF_T_IMSI                                = 0x8100,
    /* MNC length */
    /* type = uint8_t */
    MIPC_SIM_IMSI_CNF_T_MNC_LEN                             = 0x101,
};

    /* MIPC_MSG.SIM_MSISDN_REQ */
enum mipc_sim_msisdn_req_tlv_enum {
    mipc_sim_msisdn_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SIM_MSISDN_CNF */
enum mipc_sim_msisdn_cnf_tlv_enum {
    mipc_sim_msisdn_cnf_tlv_NONE = 0,
    /* msisdn count */
    /* type = uint8_t */
    MIPC_SIM_MSISDN_CNF_T_MSISDN_COUNT                      = 0x100,
    /* msisdn list, the msisdn may not exist in the sim card */
    /* type = struct_array, refer to sim_msisdn */
    MIPC_SIM_MSISDN_CNF_T_MSISDN_LIST                       = 0x8101,
};

    /* MIPC_MSG.SIM_GET_ATR_INFO_REQ */
enum mipc_sim_get_atr_info_req_tlv_enum {
    mipc_sim_get_atr_info_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SIM_GET_ATR_INFO_CNF */
enum mipc_sim_get_atr_info_cnf_tlv_enum {
    mipc_sim_get_atr_info_cnf_tlv_NONE = 0,
    /* length of atr */
    /* type = uint32_t */
    MIPC_SIM_GET_ATR_INFO_CNF_T_ATR_LEN                     = 0x100,
    /* atr string */
    /* type = string */
    MIPC_SIM_GET_ATR_INFO_CNF_T_ATR                         = 0x8101,
};

    /* MIPC_MSG.SIM_OPEN_CHANNEL_REQ */
enum mipc_sim_open_channel_req_tlv_enum {
    mipc_sim_open_channel_req_tlv_NONE = 0,
    /* length of applicaiton id */
    /* type = uint8_t */
    MIPC_SIM_OPEN_CHANNEL_REQ_T_APP_ID_LEN                  = 0x100,
    /* applicaiton id, this app_id is used to select aid after open channel,if APP_ID_LEN =0, only open channel operation is executed, no select aid operation */
    /* type = string */
    MIPC_SIM_OPEN_CHANNEL_REQ_T_APP_ID                      = 0x101,
    /* P2 defined in SIM SPEC(102.221), this prameter is used in select aid cmd after open channel */
    /* type = uint8_t */
    MIPC_SIM_OPEN_CHANNEL_REQ_T_P2                          = 0x102,
    /* channel group of the channel id, this group is optional */
    /* type = uint8_t */
    MIPC_SIM_OPEN_CHANNEL_REQ_T_CHANNEL_GROUP               = 0x103,
};

    /* MIPC_MSG.SIM_OPEN_CHANNEL_CNF */
enum mipc_sim_open_channel_cnf_tlv_enum {
    mipc_sim_open_channel_cnf_tlv_NONE = 0,
    /* status word response from UICC */
    /* type = uint16_t */
    MIPC_SIM_OPEN_CHANNEL_CNF_T_SW                          = 0x100,
    /* channel id */
    /* type = uint8_t */
    MIPC_SIM_OPEN_CHANNEL_CNF_T_CHANNEL                     = 0x101,
    /* response of open channel */
    /* type = byte_array */
    MIPC_SIM_OPEN_CHANNEL_CNF_T_RESP                        = 0x102,
};

    /* MIPC_MSG.SIM_CLOSE_CHANNEL_REQ */
enum mipc_sim_close_channel_req_tlv_enum {
    mipc_sim_close_channel_req_tlv_NONE = 0,
    /* channel id */
    /* type = uint8_t */
    MIPC_SIM_CLOSE_CHANNEL_REQ_T_CHANNEL_ID                 = 0x100,
    /* close a group of channel, if channel id is not 0, close channel id only, if channel id is 0 and channel group is not 0,all the channels belongs to the group will be closed */
    /* type = uint8_t */
    MIPC_SIM_CLOSE_CHANNEL_REQ_T_CHANNEL_GROUP              = 0x101,
};

    /* MIPC_MSG.SIM_CLOSE_CHANNEL_CNF */
enum mipc_sim_close_channel_cnf_tlv_enum {
    mipc_sim_close_channel_cnf_tlv_NONE = 0,
    /* status word returned from sim card */
    /* type = uint16_t */
    MIPC_SIM_CLOSE_CHANNEL_CNF_T_SW                         = 0x100,
};

    /* MIPC_MSG.SIM_CHANNEL_RESTRICTED_ACCESS_REQ */
enum mipc_sim_channel_restricted_access_req_tlv_enum {
    mipc_sim_channel_restricted_access_req_tlv_NONE = 0,
    /* application id */
    /* type = uint8_t, refer to SIM_APP_TYPE */
    MIPC_SIM_CHANNEL_RESTRICTED_ACCESS_REQ_T_APP_ID         = 0x100,
    /* channel id the the application */
    /* type = uint8_t */
    MIPC_SIM_CHANNEL_RESTRICTED_ACCESS_REQ_T_SESSION_ID     = 0x101,
    /* command */
    /* type = uint8_t, refer to SIM_ACCESS_COMMAND */
    MIPC_SIM_CHANNEL_RESTRICTED_ACCESS_REQ_T_CMD            = 0x102,
    /* file id */
    /* type = uint16_t */
    MIPC_SIM_CHANNEL_RESTRICTED_ACCESS_REQ_T_FILE_ID        = 0x103,
    /* P1 of APDU */
    /* type = uint8_t */
    MIPC_SIM_CHANNEL_RESTRICTED_ACCESS_REQ_T_P1             = 0x104,
    /* P2 of APDU */
    /* type = uint8_t */
    MIPC_SIM_CHANNEL_RESTRICTED_ACCESS_REQ_T_P2             = 0x105,
    /* P3 of APDU */
    /* type = uint8_t */
    MIPC_SIM_CHANNEL_RESTRICTED_ACCESS_REQ_T_P3             = 0x106,
    /* data length in DATA */
    /* type = uint16_t */
    MIPC_SIM_CHANNEL_RESTRICTED_ACCESS_REQ_T_DATA_LEN       = 0x107,
    /* command data */
    /* type = byte_array */
    MIPC_SIM_CHANNEL_RESTRICTED_ACCESS_REQ_T_DATA           = 0x8108,
    /* file path */
    /* type = string */
    MIPC_SIM_CHANNEL_RESTRICTED_ACCESS_REQ_T_PATH           = 0x109,
    /* P3 of APDU, can support more than 256 bytes */
    /* type = uint16_t */
    MIPC_SIM_CHANNEL_RESTRICTED_ACCESS_REQ_T_P3_EX          = 0x10A,
};

    /* MIPC_MSG.SIM_CHANNEL_RESTRICTED_ACCESS_CNF */
enum mipc_sim_channel_restricted_access_cnf_tlv_enum {
    mipc_sim_channel_restricted_access_cnf_tlv_NONE = 0,
    /* status word */
    /* type = uint16_t */
    MIPC_SIM_CHANNEL_RESTRICTED_ACCESS_CNF_T_SW             = 0x100,
    /* response length of apdu */
    /* type = uint16_t */
    MIPC_SIM_CHANNEL_RESTRICTED_ACCESS_CNF_T_RESP_LEN       = 0x101,
    /* response apdu */
    /* type = byte_array */
    MIPC_SIM_CHANNEL_RESTRICTED_ACCESS_CNF_T_RESP_APDU      = 0x8102,
};

    /* MIPC_MSG.SIM_CHANNEL_GENERIC_ACCESS_REQ */
enum mipc_sim_channel_generic_access_req_tlv_enum {
    mipc_sim_channel_generic_access_req_tlv_NONE = 0,
    /* application id */
    /* type = uint8_t, refer to SIM_APP_TYPE */
    MIPC_SIM_CHANNEL_GENERIC_ACCESS_REQ_T_APP_ID            = 0x100,
    /* channel id */
    /* type = uint8_t */
    MIPC_SIM_CHANNEL_GENERIC_ACCESS_REQ_T_CHANNEL_ID        = 0x101,
    /* APDU length */
    /* type = uint16_t */
    MIPC_SIM_CHANNEL_GENERIC_ACCESS_REQ_T_APDU_LEN          = 0x102,
    /* apdu send to sim card */
    /* type = byte_array */
    MIPC_SIM_CHANNEL_GENERIC_ACCESS_REQ_T_APDU              = 0x8103,
};

    /* MIPC_MSG.SIM_CHANNEL_GENERIC_ACCESS_CNF */
enum mipc_sim_channel_generic_access_cnf_tlv_enum {
    mipc_sim_channel_generic_access_cnf_tlv_NONE = 0,
    /* status word */
    /* type = uint16_t */
    MIPC_SIM_CHANNEL_GENERIC_ACCESS_CNF_T_SW                = 0x100,
    /* response apdu length */
    /* type = uint16_t */
    MIPC_SIM_CHANNEL_GENERIC_ACCESS_CNF_T_RESP_LEN          = 0x101,
    /* response apdu returned by sim card */
    /* type = byte_array */
    MIPC_SIM_CHANNEL_GENERIC_ACCESS_CNF_T_RESP_APDU         = 0x8102,
};

    /* MIPC_MSG.SIM_LONG_APDU_ACCESS_REQ */
enum mipc_sim_long_apdu_access_req_tlv_enum {
    mipc_sim_long_apdu_access_req_tlv_NONE = 0,
    /* always 1 */
    /* type = uint8_t */
    MIPC_SIM_LONG_APDU_ACCESS_REQ_T_VERSION                 = 0x100,
    /* application id length */
    /* type = uint8_t */
    MIPC_SIM_LONG_APDU_ACCESS_REQ_T_APP_ID_LEN              = 0x101,
    /* application id */
    /* type = byte_array */
    MIPC_SIM_LONG_APDU_ACCESS_REQ_T_APP_ID                  = 0x102,
    /* file path */
    /* type = string */
    MIPC_SIM_LONG_APDU_ACCESS_REQ_T_PATH_ID                 = 0x103,
    /* file id */
    /* type = uint16_t */
    MIPC_SIM_LONG_APDU_ACCESS_REQ_T_FILE_ID                 = 0x104,
    /* file offset */
    /* type = uint16_t */
    MIPC_SIM_LONG_APDU_ACCESS_REQ_T_FILE_OFFSET             = 0x105,
    /* number of bytes that will returned by sim card  */
    /* type = uint16_t */
    MIPC_SIM_LONG_APDU_ACCESS_REQ_T_NUMBER_OF_BYTES         = 0x106,
    /* pin2 */
    /* type = string */
    MIPC_SIM_LONG_APDU_ACCESS_REQ_T_LOCAL_PIN               = 0x107,
    /* length of binary data that will send to sim card */
    /* type = uint16_t */
    MIPC_SIM_LONG_APDU_ACCESS_REQ_T_BINARY_DATA_LEN         = 0x108,
    /* binary data that will send to sim card */
    /* type = byte_array */
    MIPC_SIM_LONG_APDU_ACCESS_REQ_T_BINARY_DATA             = 0x8109,
};

    /* MIPC_MSG.SIM_LONG_APDU_ACCESS_CNF */
enum mipc_sim_long_apdu_access_cnf_tlv_enum {
    mipc_sim_long_apdu_access_cnf_tlv_NONE = 0,
    /* always 1 */
    /* type = uint8_t */
    MIPC_SIM_LONG_APDU_ACCESS_CNF_T_VERSION                 = 0x100,
    /* status word */
    /* type = uint16_t */
    MIPC_SIM_LONG_APDU_ACCESS_CNF_T_SW                      = 0x101,
    /* reponse data length */
    /* type = uint16_t */
    MIPC_SIM_LONG_APDU_ACCESS_CNF_T_DATA_LEN                = 0x102,
    /* response data from sim card */
    /* type = byte_array */
    MIPC_SIM_LONG_APDU_ACCESS_CNF_T_DATA                    = 0x8103,
};

    /* MIPC_MSG.SIM_APP_LIST_REQ */
enum mipc_sim_app_list_req_tlv_enum {
    mipc_sim_app_list_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SIM_APP_LIST_CNF */
enum mipc_sim_app_list_cnf_tlv_enum {
    mipc_sim_app_list_cnf_tlv_NONE = 0,
    /* always 1 */
    /* type = uint8_t */
    MIPC_SIM_APP_LIST_CNF_T_VERSION                         = 0x100,
    /* application count */
    /* type = uint8_t */
    MIPC_SIM_APP_LIST_CNF_T_APP_COUNT                       = 0x101,
    /* active application idx in app list */
    /* type = uint8_t */
    MIPC_SIM_APP_LIST_CNF_T_ACTIVE_APP_idx                  = 0x102,
    /* application list */
    /* type = struct_array, refer to sim_app_info */
    MIPC_SIM_APP_LIST_CNF_T_APP_LIST                        = 0x103,
};

    /* MIPC_MSG.SIM_FILE_STATUS_REQ */
enum mipc_sim_file_status_req_tlv_enum {
    mipc_sim_file_status_req_tlv_NONE = 0,
    /* always 1 */
    /* type = uint8_t */
    MIPC_SIM_FILE_STATUS_REQ_T_VERSION                      = 0x100,
    /* aid length */
    /* type = uint8_t */
    MIPC_SIM_FILE_STATUS_REQ_T_AID_LEN                      = 0x101,
    /* aid */
    /* type = byte_array */
    MIPC_SIM_FILE_STATUS_REQ_T_AID                          = 0x102,
    /* length of file path */
    /* type = uint8_t */
    MIPC_SIM_FILE_STATUS_REQ_T_FILE_PATH_LEN                = 0x103,
    /* file path */
    /* type = string */
    MIPC_SIM_FILE_STATUS_REQ_T_FILE_PATH                    = 0x104,
};

    /* MIPC_MSG.SIM_FILE_STATUS_CNF */
enum mipc_sim_file_status_cnf_tlv_enum {
    mipc_sim_file_status_cnf_tlv_NONE = 0,
    /* always 1 */
    /* type = uint8_t */
    MIPC_SIM_FILE_STATUS_CNF_T_VERSION                      = 0x101,
    /* status word */
    /* type = uint16_t */
    MIPC_SIM_FILE_STATUS_CNF_T_SW                           = 0x102,
    /* types of file accessibility */
    /* type = uint8_t, refer to SIM_FILE_ACCESSIBILITY */
    MIPC_SIM_FILE_STATUS_CNF_T_FILE_ACCESSIBILITY           = 0x103,
    /* file type */
    /* type = uint8_t, refer to SIM_FILE_TYPE */
    MIPC_SIM_FILE_STATUS_CNF_T_FILE_TYPE                    = 0x104,
    /* file structure */
    /* type = uint8_t, refer to SIM_FILE_STRUCTURE */
    MIPC_SIM_FILE_STATUS_CNF_T_FILE                         = 0x105,
    /* The number of items in the UICC file. For transparent and TLV files, this is set to 1 */
    /* type = uint8_t */
    MIPC_SIM_FILE_STATUS_CNF_T_ITEM_COUNT                   = 0x106,
    /* The size of each item, in bytes. For transparent or TLV files, this is the size of the entire EF. For record-based files, this represents the total number of records */
    /* type = uint8_t */
    MIPC_SIM_FILE_STATUS_CNF_T_SIZE                         = 0x107,
    /*  An array of type mipc_sim_pin_type_enum that describes the access condition for each operation (READ, UPDATE, ACTIVATE, and DEACTIVATE in that order) on that file */
    /* type = byte_array, refer to SIM_PIN_TYPE */
    MIPC_SIM_FILE_STATUS_CNF_T_LOCK_STATUS                  = 0x108,
};

    /* MIPC_MSG.SIM_GET_RESET_REQ */
enum mipc_sim_get_reset_req_tlv_enum {
    mipc_sim_get_reset_req_tlv_NONE = 0,
    /* 0 means query passthrough mode status, 1 means query sim application/power status */
    /* type = uint8_t */
    MIPC_SIM_GET_RESET_REQ_T_TYPE                           = 0x100,
};

    /* MIPC_MSG.SIM_GET_RESET_CNF */
enum mipc_sim_get_reset_cnf_tlv_enum {
    mipc_sim_get_reset_cnf_tlv_NONE = 0,
    /* return sim power mode or passthrough status */
    /* type = uint8_t */
    MIPC_SIM_GET_RESET_CNF_T_MODE                           = 0x100,
};

    /* MIPC_MSG.SIM_SET_RESET_REQ */
enum mipc_sim_set_reset_req_tlv_enum {
    mipc_sim_set_reset_req_tlv_NONE = 0,
    /* reset mode */
    /* type = uint8_t, refer to SIM_PASS_THROUGH_MODE */
    MIPC_SIM_SET_RESET_REQ_T_MODE                           = 0x100,
};

    /* MIPC_MSG.SIM_SET_RESET_CNF */
enum mipc_sim_set_reset_cnf_tlv_enum {
    mipc_sim_set_reset_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SIM_GET_TERMINAL_CAPABILITY_REQ */
enum mipc_sim_get_terminal_capability_req_tlv_enum {
    mipc_sim_get_terminal_capability_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SIM_GET_TERMINAL_CAPABILITY_CNF */
enum mipc_sim_get_terminal_capability_cnf_tlv_enum {
    mipc_sim_get_terminal_capability_cnf_tlv_NONE = 0,
    /* terminal capability object count */
    /* type = uint8_t */
    MIPC_SIM_GET_TERMINAL_CAPABILITY_CNF_T_COUNT            = 0x100,
    /* data length of terminal capability */
    /* type = uint16_t */
    MIPC_SIM_GET_TERMINAL_CAPABILITY_CNF_T_TC_LEN           = 0x101,
    /* terminal capability */
    /* type = byte_array */
    MIPC_SIM_GET_TERMINAL_CAPABILITY_CNF_T_TC               = 0x102,
};

    /* MIPC_MSG.SIM_SET_TERMINAL_CAPABILITY_REQ */
enum mipc_sim_set_terminal_capability_req_tlv_enum {
    mipc_sim_set_terminal_capability_req_tlv_NONE = 0,
    /* terminal capability object count */
    /* type = uint8_t */
    MIPC_SIM_SET_TERMINAL_CAPABILITY_REQ_T_COUNT            = 0x100,
    /* length of terminal capability data */
    /* type = uint16_t */
    MIPC_SIM_SET_TERMINAL_CAPABILITY_REQ_T_TC_LEN           = 0x101,
    /* terminal capability */
    /* type = byte_array */
    MIPC_SIM_SET_TERMINAL_CAPABILITY_REQ_T_TC               = 0x102,
};

    /* MIPC_MSG.SIM_SET_TERMINAL_CAPABILITY_CNF */
enum mipc_sim_set_terminal_capability_cnf_tlv_enum {
    mipc_sim_set_terminal_capability_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SIM_SET_PIN_EX_REQ */
enum mipc_sim_set_pin_ex_req_tlv_enum {
    mipc_sim_set_pin_ex_req_tlv_NONE = 0,
    /* pin type */
    /* type = uint8_t, refer to SIM_PIN_TYPE */
    MIPC_SIM_SET_PIN_EX_REQ_T_PIN_TYPE                      = 0x100,
    /* pin operation */
    /* type = uint8_t, refer to SIM_PIN_OPERATION */
    MIPC_SIM_SET_PIN_EX_REQ_T_OP                            = 0x101,
    /* pin code when verify enable and disable pin ,or old pin when change pin,or puk code when operation is unblock pin */
    /* type = string */
    MIPC_SIM_SET_PIN_EX_REQ_T_PIN_CODE                      = 0x8102,
    /* new pin code when unblock or change pin */
    /* type = string */
    MIPC_SIM_SET_PIN_EX_REQ_T_NEW_PIN_CODE                  = 0x8103,
    /* aid length */
    /* type = uint8_t */
    MIPC_SIM_SET_PIN_EX_REQ_T_AID_LEN                       = 0x104,
    /* aid */
    /* type = byte_array */
    MIPC_SIM_SET_PIN_EX_REQ_T_AID                           = 0x105,
};

    /* MIPC_MSG.SIM_SET_PIN_EX_CNF */
enum mipc_sim_set_pin_ex_cnf_tlv_enum {
    mipc_sim_set_pin_ex_cnf_tlv_NONE = 0,
    /* pin type */
    /* type = uint8_t, refer to SIM_PIN_TYPE */
    MIPC_SIM_SET_PIN_EX_CNF_T_PIN_TYPE                      = 0x100,
    /* pin state */
    /* type = uint8_t, refer to SIM_PIN_STATE */
    MIPC_SIM_SET_PIN_EX_CNF_T_PIN_STATE                     = 0x101,
    /* remaining attempts */
    /* type = uint32_t */
    MIPC_SIM_SET_PIN_EX_CNF_T_REMAINING_ATTEMPTS            = 0x102,
};

    /* MIPC_MSG.SIM_GET_PIN_EX_REQ */
enum mipc_sim_get_pin_ex_req_tlv_enum {
    mipc_sim_get_pin_ex_req_tlv_NONE = 0,
    /* always 1 */
    /* type = uint8_t */
    MIPC_SIM_GET_PIN_EX_REQ_T_VERSION                       = 0x100,
    /* aid length */
    /* type = uint8_t */
    MIPC_SIM_GET_PIN_EX_REQ_T_AID_LEN                       = 0x101,
    /* aid data */
    /* type = byte_array */
    MIPC_SIM_GET_PIN_EX_REQ_T_AID                           = 0x102,
};

    /* MIPC_MSG.SIM_GET_PIN_EX_CNF */
enum mipc_sim_get_pin_ex_cnf_tlv_enum {
    mipc_sim_get_pin_ex_cnf_tlv_NONE = 0,
    /* pin type */
    /* type = uint8_t, refer to SIM_PIN_TYPE */
    MIPC_SIM_GET_PIN_EX_CNF_T_PIN_TYPE                      = 0x100,
    /* pin state */
    /* type = uint8_t, refer to SIM_PIN_STATE */
    MIPC_SIM_GET_PIN_EX_CNF_T_PIN_STATE                     = 0x101,
    /* remain attempts */
    /* type = uint32_t */
    MIPC_SIM_GET_PIN_EX_CNF_T_REMAINING_ATTEMPTS            = 0x102,
};

    /* MIPC_MSG.SIM_GET_GSM_AUTH_REQ */
enum mipc_sim_get_gsm_auth_req_tlv_enum {
    mipc_sim_get_gsm_auth_req_tlv_NONE = 0,
    /* fixed length: 16 bytes */
    /* type = byte_array */
    MIPC_SIM_GET_GSM_AUTH_REQ_T_RAND1                       = 0x8100,
    /* fixed length: 16 bytes,if RAND2 exist SIM CARD will run gsm algorithm 2 times */
    /* type = byte_array */
    MIPC_SIM_GET_GSM_AUTH_REQ_T_RAND2                       = 0x8101,
    /* fixed length: 16 bytes,if RAND2 and RAND3 exist SIM CARD will run gsm algorithm 3 times */
    /* type = byte_array */
    MIPC_SIM_GET_GSM_AUTH_REQ_T_RAND3                       = 0x8102,
};

    /* MIPC_MSG.SIM_GET_GSM_AUTH_CNF */
enum mipc_sim_get_gsm_auth_cnf_tlv_enum {
    mipc_sim_get_gsm_auth_cnf_tlv_NONE = 0,
    /* status word */
    /* type = uint16_t */
    MIPC_SIM_GET_GSM_AUTH_CNF_T_SW                          = 0x100,
    /* fixed length: 4 bytes */
    /* type = byte_array */
    MIPC_SIM_GET_GSM_AUTH_CNF_T_SRES1                       = 0x101,
    /* fixed length: 8 bytes */
    /* type = byte_array */
    MIPC_SIM_GET_GSM_AUTH_CNF_T_KC1                         = 0x102,
    /* fixed length: 4 bytes, exist only when rand2 is send */
    /* type = byte_array */
    MIPC_SIM_GET_GSM_AUTH_CNF_T_SRES2                       = 0x103,
    /* fixed length: 8 bytes, exist only when rand2 is send */
    /* type = byte_array */
    MIPC_SIM_GET_GSM_AUTH_CNF_T_KC2                         = 0x104,
    /* fixed length: 4 bytes, exist only when rand3 is send */
    /* type = byte_array */
    MIPC_SIM_GET_GSM_AUTH_CNF_T_SRES3                       = 0x105,
    /* fixed length: 8 bytes, exist only when rand3 is send */
    /* type = byte_array */
    MIPC_SIM_GET_GSM_AUTH_CNF_T_KC3                         = 0x106,
};

    /* MIPC_MSG.SIM_GET_EXT_AUTH_REQ */
enum mipc_sim_get_ext_auth_req_tlv_enum {
    mipc_sim_get_ext_auth_req_tlv_NONE = 0,
    /* channel id.It is suggested that either CH or APP_ID should be carried.If neither CH nor APP_ID is carried, defualt channel will be used. If both parameters are carried, CH will be used. */
    /* type = uint8_t */
    MIPC_SIM_GET_EXT_AUTH_REQ_T_CH                          = 0x100,
    /* mode defined in 31.102 section 7.1.2 */
    /* type = uint8_t */
    MIPC_SIM_GET_EXT_AUTH_REQ_T_MODE                        = 0x101,
    /* data length of CMD_DATA */
    /* type = uint16_t */
    MIPC_SIM_GET_EXT_AUTH_REQ_T_CMD_LEN                     = 0x102,
    /* authentication data defined in 31.102 section 7.1.2 */
    /* type = byte_array */
    MIPC_SIM_GET_EXT_AUTH_REQ_T_CMD_DATA                    = 0x8103,
    /* application id. It is suggested that either CH or APP_ID should be carried.If neither CH nor APP_ID is carried, defualt channel will be used. If both parameters are carried, CH will be used. */
    /* type = uint8_t, refer to SIM_APP_TYPE */
    MIPC_SIM_GET_EXT_AUTH_REQ_T_APP_ID                      = 0x104,
};

    /* MIPC_MSG.SIM_GET_EXT_AUTH_CNF */
enum mipc_sim_get_ext_auth_cnf_tlv_enum {
    mipc_sim_get_ext_auth_cnf_tlv_NONE = 0,
    /* status word */
    /* type = uint16_t */
    MIPC_SIM_GET_EXT_AUTH_CNF_T_SW                          = 0x100,
    /* response length */
    /* type = uint16_t */
    MIPC_SIM_GET_EXT_AUTH_CNF_T_RSP_LEN                     = 0x101,
    /* response return from sim card */
    /* type = byte_array */
    MIPC_SIM_GET_EXT_AUTH_CNF_T_RSP_DATA                    = 0x8102,
};

    /* MIPC_MSG.SIM_GET_FACILITY_REQ */
enum mipc_sim_get_facility_req_tlv_enum {
    mipc_sim_get_facility_req_tlv_NONE = 0,
    /* application id */
    /* type = uint8_t, refer to SIM_APP_TYPE */
    MIPC_SIM_GET_FACILITY_REQ_T_APP_ID                      = 0x100,
    /* support FD, SC, AO, OI, OX, AI, IR */
    /* type = string */
    MIPC_SIM_GET_FACILITY_REQ_T_FACILITY                    = 0x101,
};

    /* MIPC_MSG.SIM_GET_FACILITY_CNF */
enum mipc_sim_get_facility_cnf_tlv_enum {
    mipc_sim_get_facility_cnf_tlv_NONE = 0,
    /* 0 means not active, 1 means active */
    /* type = uint8_t */
    MIPC_SIM_GET_FACILITY_CNF_T_STATUS                      = 0x100,
};

    /* MIPC_MSG.SIM_SET_FACILITY_REQ */
enum mipc_sim_set_facility_req_tlv_enum {
    mipc_sim_set_facility_req_tlv_NONE = 0,
    /*  */
    /* type = uint8_t, refer to SIM_APP_TYPE */
    MIPC_SIM_SET_FACILITY_REQ_T_APP_ID                      = 0x100,
    /* support FD SC, AO, OI, OX, AI, IR */
    /* type = string */
    MIPC_SIM_SET_FACILITY_REQ_T_FACILITY                    = 0x101,
    /* pin1 or pin2 code */
    /* type = string */
    MIPC_SIM_SET_FACILITY_REQ_T_PASS_WORD                   = 0x8102,
    /* 0 disable and 1 enable */
    /* type = uint8_t */
    MIPC_SIM_SET_FACILITY_REQ_T_MODE                        = 0x103,
};

    /* MIPC_MSG.SIM_SET_FACILITY_CNF */
enum mipc_sim_set_facility_cnf_tlv_enum {
    mipc_sim_set_facility_cnf_tlv_NONE = 0,
    /* remaining attempts */
    /* type = uint8_t */
    MIPC_SIM_SET_FACILITY_CNF_T_RETRY_COUNT                 = 0x100,
};

    /* MIPC_MSG.SIM_GET_EUICC_SLOTS_STATUS_REQ */
enum mipc_sim_get_euicc_slots_status_req_tlv_enum {
    mipc_sim_get_euicc_slots_status_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SIM_GET_EUICC_SLOTS_STATUS_CNF */
enum mipc_sim_get_euicc_slots_status_cnf_tlv_enum {
    mipc_sim_get_euicc_slots_status_cnf_tlv_NONE = 0,
    /*  physical slots number */
    /* type = uint8_t */
    MIPC_SIM_GET_EUICC_SLOTS_STATUS_CNF_T_SLOTS_INFO_COUNT  = 0x100,
    /* slot info for all slots */
    /* type = struct_array, refer to sim_slots_info */
    MIPC_SIM_GET_EUICC_SLOTS_STATUS_CNF_T_SLOTS_INFO_LIST   = 0x8101,
    /* type = uint8_t, refer to SIM_CARD_PRESENT_STATE */
    MIPC_SIM_GET_EUICC_SLOTS_STATUS_CNF_T_CARD_STATE        = 0x8102,
    /* type = uint8_t */
    MIPC_SIM_GET_EUICC_SLOTS_STATUS_CNF_T_SLOTS_STATE       = 0x8103,
    /* type = uint8_t */
    MIPC_SIM_GET_EUICC_SLOTS_STATUS_CNF_T_LOGICAL_IDX       = 0x8104,
    /* type = string */
    MIPC_SIM_GET_EUICC_SLOTS_STATUS_CNF_T_ATR               = 0x8105,
    /* type = string */
    MIPC_SIM_GET_EUICC_SLOTS_STATUS_CNF_T_EID               = 0x8106,
    /* type = string */
    MIPC_SIM_GET_EUICC_SLOTS_STATUS_CNF_T_ICCID             = 0x8107,
};

    /* MIPC_MSG.SIM_ACCESS_PROFILE_CONNECT_REQ */
enum mipc_sim_access_profile_connect_req_tlv_enum {
    mipc_sim_access_profile_connect_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SIM_ACCESS_PROFILE_CONNECT_CNF */
enum mipc_sim_access_profile_connect_cnf_tlv_enum {
    mipc_sim_access_profile_connect_cnf_tlv_NONE = 0,
    /* Indicate which transport protocol is used, 0x00 : T=0,0x01 : T=1 */
    /* type = uint8_t */
    MIPC_SIM_ACCESS_PROFILE_CONNECT_CNF_T_CUR_TYPE          = 0x100,
    /* Indicate what's the capability in transport protocol in the SIM card,0x00 : T=0, 0x01 : T=1, 0x02 : Both T=0 and T=1 supported */
    /* type = uint8_t */
    MIPC_SIM_ACCESS_PROFILE_CONNECT_CNF_T_SUPPORT_TYPE      = 0x101,
    /* the ATR response from SIM card */
    /* type = string */
    MIPC_SIM_ACCESS_PROFILE_CONNECT_CNF_T_ATR               = 0x102,
};

    /* MIPC_MSG.SIM_ACCESS_PROFILE_DISCONNECT_REQ */
enum mipc_sim_access_profile_disconnect_req_tlv_enum {
    mipc_sim_access_profile_disconnect_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SIM_ACCESS_PROFILE_DISCONNECT_CNF */
enum mipc_sim_access_profile_disconnect_cnf_tlv_enum {
    mipc_sim_access_profile_disconnect_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SIM_ACCESS_PROFILE_POWER_ON_REQ */
enum mipc_sim_access_profile_power_on_req_tlv_enum {
    mipc_sim_access_profile_power_on_req_tlv_NONE = 0,
    /* Indicate which transport protocol is used, 0x00 : T=0,0x01 : T=1 */
    /* type = uint8_t */
    MIPC_SIM_ACCESS_PROFILE_POWER_ON_REQ_T_TYPE             = 0x100,
};

    /* MIPC_MSG.SIM_ACCESS_PROFILE_POWER_ON_CNF */
enum mipc_sim_access_profile_power_on_cnf_tlv_enum {
    mipc_sim_access_profile_power_on_cnf_tlv_NONE = 0,
    /* Indicate what's the capability in transport protocol in the SIM card, 0x00 : T=0, 0x01 : T=1, 0x02 : Both T=0 and T=1 supported */
    /* type = uint8_t */
    MIPC_SIM_ACCESS_PROFILE_POWER_ON_CNF_T_CUR_TYPE         = 0x101,
    /* the ATR response from SIM card */
    /* type = string */
    MIPC_SIM_ACCESS_PROFILE_POWER_ON_CNF_T_ATR              = 0x102,
};

    /* MIPC_MSG.SIM_ACCESS_PROFILE_POWER_OFF_REQ */
enum mipc_sim_access_profile_power_off_req_tlv_enum {
    mipc_sim_access_profile_power_off_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SIM_ACCESS_PROFILE_POWER_OFF_CNF */
enum mipc_sim_access_profile_power_off_cnf_tlv_enum {
    mipc_sim_access_profile_power_off_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SIM_ACCESS_PROFILE_RESET_REQ */
enum mipc_sim_access_profile_reset_req_tlv_enum {
    mipc_sim_access_profile_reset_req_tlv_NONE = 0,
    /* Indicate which transport protocol is used, 0x00 : T=0,0x01 : T=1 */
    /* type = uint8_t */
    MIPC_SIM_ACCESS_PROFILE_RESET_REQ_T_TYPE                = 0x100,
};

    /* MIPC_MSG.SIM_ACCESS_PROFILE_RESET_CNF */
enum mipc_sim_access_profile_reset_cnf_tlv_enum {
    mipc_sim_access_profile_reset_cnf_tlv_NONE = 0,
    /* Indicate what's the capability in transport protocol in the SIM card, 0x00 : T=0, 0x01 : T=1, 0x02 : Both T=0 and T=1 supported */
    /* type = uint8_t */
    MIPC_SIM_ACCESS_PROFILE_RESET_CNF_T_CUR_TYPE            = 0x101,
    /* the ATR response from SIM card */
    /* type = string */
    MIPC_SIM_ACCESS_PROFILE_RESET_CNF_T_ATR                 = 0x102,
};

    /* MIPC_MSG.SIM_ACCESS_PROFILE_APDU_REQ */
enum mipc_sim_access_profile_apdu_req_tlv_enum {
    mipc_sim_access_profile_apdu_req_tlv_NONE = 0,
    /* Indicate what's the capability in transport protocol in the SIM card, 0x00 : T=0, 0x01 : T=1, 0x02 : Both T=0 and T=1 supported */
    /* type = uint8_t */
    MIPC_SIM_ACCESS_PROFILE_APDU_REQ_T_TYPE                 = 0x100,
    /* the APDU send to sim card */
    /* type = string */
    MIPC_SIM_ACCESS_PROFILE_APDU_REQ_T_APDU                 = 0x101,
};

    /* MIPC_MSG.SIM_ACCESS_PROFILE_APDU_CNF */
enum mipc_sim_access_profile_apdu_cnf_tlv_enum {
    mipc_sim_access_profile_apdu_cnf_tlv_NONE = 0,
    /* the APDU return from sim card */
    /* type = string */
    MIPC_SIM_ACCESS_PROFILE_APDU_CNF_T_APDU                 = 0x100,
};

    /* MIPC_MSG.SIM_SET_SIM_POWER_REQ */
enum mipc_sim_set_sim_power_req_tlv_enum {
    mipc_sim_set_sim_power_req_tlv_NONE = 0,
    /* mode 0 means rf operation only, mode 1 means operation for both sim and rf, mode 2 means power down/up without esims urc until plug out/in sim card */
    /* type = uint8_t */
    MIPC_SIM_SET_SIM_POWER_REQ_T_MODE                       = 0x100,
    /*  */
    /* type = uint8_t */
    MIPC_SIM_SET_SIM_POWER_REQ_T_SIM_POWER                  = 0x101,
};

    /* MIPC_MSG.SIM_SET_SIM_POWER_CNF */
enum mipc_sim_set_sim_power_cnf_tlv_enum {
    mipc_sim_set_sim_power_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SIM_SET_PHYSICAL_SLOTS_MAPPING_REQ */
enum mipc_sim_set_physical_slots_mapping_req_tlv_enum {
    mipc_sim_set_physical_slots_mapping_req_tlv_NONE = 0,
    /* slots number */
    /* type = uint8_t */
    MIPC_SIM_SET_PHYSICAL_SLOTS_MAPPING_REQ_T_SLOTS_NUM     = 0x100,
    /* 0-based,slots_mapping_list = {1,0} means sim slot0->physical slot1, sim slot1->pysical slot0 */
    /* type = byte_array */
    MIPC_SIM_SET_PHYSICAL_SLOTS_MAPPING_REQ_T_SLOTS_MAPPING_LIST = 0x101,
};

    /* MIPC_MSG.SIM_SET_PHYSICAL_SLOTS_MAPPING_CNF */
enum mipc_sim_set_physical_slots_mapping_cnf_tlv_enum {
    mipc_sim_set_physical_slots_mapping_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SIM_EXTENDED_CHANNEL_GENERIC_ACCESS_REQ */
enum mipc_sim_extended_channel_generic_access_req_tlv_enum {
    mipc_sim_extended_channel_generic_access_req_tlv_NONE = 0,
    /* channel id  */
    /* type = uint8_t */
    MIPC_SIM_EXTENDED_CHANNEL_GENERIC_ACCESS_REQ_T_SESSION_ID = 0x100,
    /* CLA byte of APDU, that will send to sim card */
    /* type = uint8_t */
    MIPC_SIM_EXTENDED_CHANNEL_GENERIC_ACCESS_REQ_T_CLA      = 0x101,
    /* INS byte of APDU, that will send to sim card */
    /* type = uint8_t */
    MIPC_SIM_EXTENDED_CHANNEL_GENERIC_ACCESS_REQ_T_INS      = 0x102,
    /* P1 byte of APDU, that will send to sim card */
    /* type = uint8_t */
    MIPC_SIM_EXTENDED_CHANNEL_GENERIC_ACCESS_REQ_T_P1       = 0x103,
    /* P2 byte of APDU, that will send to sim card */
    /* type = uint8_t */
    MIPC_SIM_EXTENDED_CHANNEL_GENERIC_ACCESS_REQ_T_P2       = 0x104,
    /* P3 byte of APDU, that will send to sim card */
    /* type = uint8_t */
    MIPC_SIM_EXTENDED_CHANNEL_GENERIC_ACCESS_REQ_T_P3       = 0x105,
    /* data length in DATA. If card support extended Lc and Le fileds but INS is not 0XE2, the max len is 65535,else the max data length is 255 */
    /* type = uint16_t */
    MIPC_SIM_EXTENDED_CHANNEL_GENERIC_ACCESS_REQ_T_DATA_LEN = 0x106,
    /* command data in APDU */
    /* type = byte_array */
    MIPC_SIM_EXTENDED_CHANNEL_GENERIC_ACCESS_REQ_T_DATA     = 0x8107,
};

    /* MIPC_MSG.SIM_EXTENDED_CHANNEL_GENERIC_ACCESS_CNF */
enum mipc_sim_extended_channel_generic_access_cnf_tlv_enum {
    mipc_sim_extended_channel_generic_access_cnf_tlv_NONE = 0,
    /* status word */
    /* type = uint16_t */
    MIPC_SIM_EXTENDED_CHANNEL_GENERIC_ACCESS_CNF_T_SW       = 0x100,
    /* response length of apdu */
    /* type = uint16_t */
    MIPC_SIM_EXTENDED_CHANNEL_GENERIC_ACCESS_CNF_T_RESP_LEN = 0x101,
    /* response apdu */
    /* type = byte_array */
    MIPC_SIM_EXTENDED_CHANNEL_GENERIC_ACCESS_CNF_T_RESP_APDU = 0x8102,
};

    /* MIPC_MSG.SIM_UICC_FILE_ACCESS_RECORD_REQ */
enum mipc_sim_uicc_file_access_record_req_tlv_enum {
    mipc_sim_uicc_file_access_record_req_tlv_NONE = 0,
    /* applicaiton id */
    /* type = byte_array */
    MIPC_SIM_UICC_FILE_ACCESS_RECORD_REQ_T_APP_ID           = 0x100,
    /* length of app_id */
    /* type = uint8_t */
    MIPC_SIM_UICC_FILE_ACCESS_RECORD_REQ_T_APP_ID_LEN       = 0x101,
    /* file id */
    /* type = uint16_t */
    MIPC_SIM_UICC_FILE_ACCESS_RECORD_REQ_T_FILE_ID          = 0x102,
    /* record number */
    /* type = uint8_t */
    MIPC_SIM_UICC_FILE_ACCESS_RECORD_REQ_T_RECORD_NUM       = 0x103,
    /* length of data */
    /* type = uint16_t */
    MIPC_SIM_UICC_FILE_ACCESS_RECORD_REQ_T_DATA_LEN         = 0x104,
    /* command data */
    /* type = byte_array */
    MIPC_SIM_UICC_FILE_ACCESS_RECORD_REQ_T_DATA             = 0x105,
    /* path */
    /* type = string */
    MIPC_SIM_UICC_FILE_ACCESS_RECORD_REQ_T_PATH             = 0x106,
    /* local pin code */
    /* type = string */
    MIPC_SIM_UICC_FILE_ACCESS_RECORD_REQ_T_PIN2             = 0x107,
};

    /* MIPC_MSG.SIM_UICC_FILE_ACCESS_RECORD_CNF */
enum mipc_sim_uicc_file_access_record_cnf_tlv_enum {
    mipc_sim_uicc_file_access_record_cnf_tlv_NONE = 0,
    /* status word */
    /* type = uint16_t */
    MIPC_SIM_UICC_FILE_ACCESS_RECORD_CNF_T_SW               = 0x100,
    /* response length of apdu */
    /* type = uint16_t */
    MIPC_SIM_UICC_FILE_ACCESS_RECORD_CNF_T_RESP_LEN         = 0x101,
    /* response apdu */
    /* type = byte_array */
    MIPC_SIM_UICC_FILE_ACCESS_RECORD_CNF_T_RESP_APDU        = 0x102,
};

    /* MIPC_MSG.SIM_UICC_FILE_ACCESS_BINARY_REQ */
enum mipc_sim_uicc_file_access_binary_req_tlv_enum {
    mipc_sim_uicc_file_access_binary_req_tlv_NONE = 0,
    /* applicaiton id */
    /* type = byte_array */
    MIPC_SIM_UICC_FILE_ACCESS_BINARY_REQ_T_APP_ID           = 0x100,
    /* length of app_id */
    /* type = uint8_t */
    MIPC_SIM_UICC_FILE_ACCESS_BINARY_REQ_T_APP_ID_LEN       = 0x101,
    /* file id */
    /* type = uint16_t */
    MIPC_SIM_UICC_FILE_ACCESS_BINARY_REQ_T_FILE_ID          = 0x102,
    /* offset */
    /* type = uint16_t */
    MIPC_SIM_UICC_FILE_ACCESS_BINARY_REQ_T_OFFSET           = 0x103,
    /* length of data */
    /* type = uint16_t */
    MIPC_SIM_UICC_FILE_ACCESS_BINARY_REQ_T_DATA_LEN         = 0x104,
    /* command data */
    /* type = byte_array */
    MIPC_SIM_UICC_FILE_ACCESS_BINARY_REQ_T_DATA             = 0x105,
    /* path */
    /* type = string */
    MIPC_SIM_UICC_FILE_ACCESS_BINARY_REQ_T_PATH             = 0x106,
    /* local pin code */
    /* type = string */
    MIPC_SIM_UICC_FILE_ACCESS_BINARY_REQ_T_PIN2             = 0x107,
};

    /* MIPC_MSG.SIM_UICC_FILE_ACCESS_BINARY_CNF */
enum mipc_sim_uicc_file_access_binary_cnf_tlv_enum {
    mipc_sim_uicc_file_access_binary_cnf_tlv_NONE = 0,
    /* status word */
    /* type = uint16_t */
    MIPC_SIM_UICC_FILE_ACCESS_BINARY_CNF_T_SW               = 0x100,
    /* response length of apdu */
    /* type = uint16_t */
    MIPC_SIM_UICC_FILE_ACCESS_BINARY_CNF_T_RESP_LEN         = 0x101,
    /* response apdu */
    /* type = byte_array */
    MIPC_SIM_UICC_FILE_ACCESS_BINARY_CNF_T_RESP_APDU        = 0x102,
};

    /* MIPC_MSG.SIM_GET_PHYSICAL_SLOTS_MAPPING_REQ */
enum mipc_sim_get_physical_slots_mapping_req_tlv_enum {
    mipc_sim_get_physical_slots_mapping_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SIM_GET_PHYSICAL_SLOTS_MAPPING_CNF */
enum mipc_sim_get_physical_slots_mapping_cnf_tlv_enum {
    mipc_sim_get_physical_slots_mapping_cnf_tlv_NONE = 0,
    /* 0-based, physical slot id */
    /* type = uint8_t */
    MIPC_SIM_GET_PHYSICAL_SLOTS_MAPPING_CNF_T_ACTIVE_PHYSICAL_SLOT_ID = 0x101,
};

    /* MIPC_MSG.SIM_GET_SIM_AUTH_REQ */
enum mipc_sim_get_sim_auth_req_tlv_enum {
    mipc_sim_get_sim_auth_req_tlv_NONE = 0,
    /* P2 value of authentication command,defualt is 0 */
    /* type = uint8_t */
    MIPC_SIM_GET_SIM_AUTH_REQ_T_P2                          = 0x100,
    /* AID Valuse,see ESTI 102.221 8.1 and 102.220,default is null */
    /* type = string */
    MIPC_SIM_GET_SIM_AUTH_REQ_T_AID                         = 0x101,
    /* data length of CMD_DATA */
    /* type = uint16_t */
    MIPC_SIM_GET_SIM_AUTH_REQ_T_CMD_LEN                     = 0x102,
    /* authentication data defined in 31.102 section 7.1.2 */
    /* type = byte_array */
    MIPC_SIM_GET_SIM_AUTH_REQ_T_CMD_DATA                    = 0x8103,
};

    /* MIPC_MSG.SIM_GET_SIM_AUTH_CNF */
enum mipc_sim_get_sim_auth_cnf_tlv_enum {
    mipc_sim_get_sim_auth_cnf_tlv_NONE = 0,
    /* status word */
    /* type = uint16_t */
    MIPC_SIM_GET_SIM_AUTH_CNF_T_SW                          = 0x100,
    /* response length */
    /* type = uint16_t */
    MIPC_SIM_GET_SIM_AUTH_CNF_T_RSP_LEN                     = 0x101,
    /* response return from sim card */
    /* type = byte_array */
    MIPC_SIM_GET_SIM_AUTH_CNF_T_RSP_DATA                    = 0x8102,
};

    /* MIPC_MSG.SIM_SML_GET_ALLOWED_CARRIERS_REQ */
enum mipc_sim_sml_get_allowed_carriers_req_tlv_enum {
    mipc_sim_sml_get_allowed_carriers_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SIM_SML_GET_ALLOWED_CARRIERS_CNF */
enum mipc_sim_sml_get_allowed_carriers_cnf_tlv_enum {
    mipc_sim_sml_get_allowed_carriers_cnf_tlv_NONE = 0,
    /* google carriers lock status */
    /* type = uint8_t, refer to SIM_CRRST_STATE */
    MIPC_SIM_SML_GET_ALLOWED_CARRIERS_CNF_T_STATE           = 0x100,
    /* multi sim policy */
    /* type = uint8_t */
    MIPC_SIM_SML_GET_ALLOWED_CARRIERS_CNF_T_MULTI_SIM_POLICY = 0x101,
    /* True means that only carriers included in the allowed list and not in the excluded list are permitted.False means that all carriers are allowed except those included in the excluded list and not in the allowed list */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_SIM_SML_GET_ALLOWED_CARRIERS_CNF_T_ALLOWED_CARRIERS_PRIORITIZED = 0x102,
    /* num of allowed carriers */
    /* type = uint8_t */
    MIPC_SIM_SML_GET_ALLOWED_CARRIERS_CNF_T_ALLOWED_CARRIERS_NUM = 0x103,
    /* allowed carriers list */
    /* type = struct_array, refer to sim_carrier_struct */
    MIPC_SIM_SML_GET_ALLOWED_CARRIERS_CNF_T_ALLOWED_CARRIERS = 0x104,
    /* num of excluded carriers */
    /* type = uint8_t */
    MIPC_SIM_SML_GET_ALLOWED_CARRIERS_CNF_T_EXCLUDED_CARRIERS_NUM = 0x105,
    /* excluded carriers list */
    /* type = struct_array, refer to sim_carrier_struct */
    MIPC_SIM_SML_GET_ALLOWED_CARRIERS_CNF_T_EXCLUDED_CARRIERS = 0x106,
};

    /* MIPC_MSG.SIM_SML_SET_ALLOWED_CARRIERS_REQ */
enum mipc_sim_sml_set_allowed_carriers_req_tlv_enum {
    mipc_sim_sml_set_allowed_carriers_req_tlv_NONE = 0,
    /* multi sim policy */
    /* type = uint8_t */
    MIPC_SIM_SML_SET_ALLOWED_CARRIERS_REQ_T_MULTI_SIM_POLICY = 0x100,
    /* True means that only carriers included in the allowed list and not in the excluded list are permitted.False means that all carriers are allowed except those included in the excluded list and not in the allowed list */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_SIM_SML_SET_ALLOWED_CARRIERS_REQ_T_ALLOWED_CARRIERS_PRIORITIZED = 0x101,
    /* num of allowed carriers */
    /* type = uint8_t */
    MIPC_SIM_SML_SET_ALLOWED_CARRIERS_REQ_T_ALLOWED_CARRIERS_NUM = 0x102,
    /* allowed carriers list */
    /* type = struct_array, refer to sim_carrier_struct */
    MIPC_SIM_SML_SET_ALLOWED_CARRIERS_REQ_T_ALLOWED_CARRIERS = 0x103,
    /* num of excluded carriers */
    /* type = uint8_t */
    MIPC_SIM_SML_SET_ALLOWED_CARRIERS_REQ_T_EXCLUDED_CARRIERS_NUM = 0x104,
    /* excluded carriers list */
    /* type = struct_array, refer to sim_carrier_struct */
    MIPC_SIM_SML_SET_ALLOWED_CARRIERS_REQ_T_EXCLUDED_CARRIERS = 0x105,
};

    /* MIPC_MSG.SIM_SML_SET_ALLOWED_CARRIERS_CNF */
enum mipc_sim_sml_set_allowed_carriers_cnf_tlv_enum {
    mipc_sim_sml_set_allowed_carriers_cnf_tlv_NONE = 0,
    /* num of set allowed carriers success */
    /* type = uint8_t */
    MIPC_SIM_SML_SET_ALLOWED_CARRIERS_CNF_T_ALLOWED_COUNT   = 0x100,
    /* num of set excluded carriers success */
    /* type = uint8_t */
    MIPC_SIM_SML_SET_ALLOWED_CARRIERS_CNF_T_EXCLUDED_COUNT  = 0x101,
};

    /* MIPC_MSG.SIM_SML_ENTER_SIM_DEPERSONALIZATION_REQ */
enum mipc_sim_sml_enter_sim_depersonalization_req_tlv_enum {
    mipc_sim_sml_enter_sim_depersonalization_req_tlv_NONE = 0,
    /* sim me lock category */
    /* type = uint8_t, refer to SIM_SML_CATEGORY */
    MIPC_SIM_SML_ENTER_SIM_DEPERSONALIZATION_REQ_T_CATEGORY = 0x100,
    /* password for depersonalization */
    /* type = string */
    MIPC_SIM_SML_ENTER_SIM_DEPERSONALIZATION_REQ_T_PIN_CODE = 0x8101,
};

    /* MIPC_MSG.SIM_SML_ENTER_SIM_DEPERSONALIZATION_CNF */
enum mipc_sim_sml_enter_sim_depersonalization_cnf_tlv_enum {
    mipc_sim_sml_enter_sim_depersonalization_cnf_tlv_NONE = 0,
    /* sim me lock category */
    /* type = uint8_t, refer to SIM_SML_CATEGORY */
    MIPC_SIM_SML_ENTER_SIM_DEPERSONALIZATION_CNF_T_CATEGORY = 0x100,
    /* times left that user can try on */
    /* type = uint8_t */
    MIPC_SIM_SML_ENTER_SIM_DEPERSONALIZATION_CNF_T_REMAIN_COUNT = 0x101,
    /* all category remain retry count */
    /* type = byte_array */
    MIPC_SIM_SML_ENTER_SIM_DEPERSONALIZATION_CNF_T_REMAIN_COUNT_LIST = 0x102,
};

    /* MIPC_MSG.SIM_SML_GET_LOCK_REQ */
enum mipc_sim_sml_get_lock_req_tlv_enum {
    mipc_sim_sml_get_lock_req_tlv_NONE = 0,
    /* sim me lock category */
    /* type = uint8_t, refer to SIM_SML_CATEGORY */
    MIPC_SIM_SML_GET_LOCK_REQ_T_CATEGORY                    = 0x100,
};

    /* MIPC_MSG.SIM_SML_GET_LOCK_CNF */
enum mipc_sim_sml_get_lock_cnf_tlv_enum {
    mipc_sim_sml_get_lock_cnf_tlv_NONE = 0,
    /* sim me lock category */
    /* type = uint8_t, refer to SIM_SML_CATEGORY */
    MIPC_SIM_SML_GET_LOCK_CNF_T_CATEGORY                    = 0x100,
    /* category lock state, 1-lock, 2-unlock, 3-autolock, 4-disable */
    /* type = uint8_t */
    MIPC_SIM_SML_GET_LOCK_CNF_T_STATE                       = 0x101,
    /* times left that user can try on */
    /* type = uint8_t */
    MIPC_SIM_SML_GET_LOCK_CNF_T_RETRY_CNT                   = 0x102,
    /* times left that MD will write SIM card code in category list */
    /* type = uint8_t */
    MIPC_SIM_SML_GET_LOCK_CNF_T_AUTOLOCK_CNT                = 0x103,
    /* numbers of sets that is in the category list */
    /* type = uint8_t */
    MIPC_SIM_SML_GET_LOCK_CNF_T_NUM_SET                     = 0x104,
    /* total numbers of sets that the category can set */
    /* type = uint8_t */
    MIPC_SIM_SML_GET_LOCK_CNF_T_TOTAL_SET                   = 0x105,
    /* current state of key, 0-key is not set, 1-key is well set */
    /* type = uint8_t */
    MIPC_SIM_SML_GET_LOCK_CNF_T_KEY_STATE                   = 0x106,
    /* max times that user can try on */
    /* type = uint8_t */
    MIPC_SIM_SML_GET_LOCK_CNF_T_MAX_CNT                     = 0x107,
    /* unlock authentication by local or remote, 1 means unlock by remote server, 0 means by local */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_SIM_SML_GET_LOCK_CNF_T_RSU_ENABLE                  = 0x108,
};

    /* MIPC_MSG.SIM_SML_SET_LOCK_REQ */
enum mipc_sim_sml_set_lock_req_tlv_enum {
    mipc_sim_sml_set_lock_req_tlv_NONE = 0,
    /* sim me lock category */
    /* type = uint8_t, refer to SIM_SML_CATEGORY */
    MIPC_SIM_SML_SET_LOCK_REQ_T_CATEGORY                    = 0x100,
    /* operation for sim me lock */
    /* type = uint8_t, refer to SIM_SML_OPERATION */
    MIPC_SIM_SML_SET_LOCK_REQ_T_OP                          = 0x101,
    /* string of category key */
    /* type = string */
    MIPC_SIM_SML_SET_LOCK_REQ_T_KEY                         = 0x8102,
    /* string of imsi */
    /* type = string */
    MIPC_SIM_SML_SET_LOCK_REQ_T_DATA_IMSI                   = 0x103,
    /* string of gid1 */
    /* type = string */
    MIPC_SIM_SML_SET_LOCK_REQ_T_GID1                        = 0x104,
    /* string of gid2 */
    /* type = string */
    MIPC_SIM_SML_SET_LOCK_REQ_T_GID2                        = 0x105,
};

    /* MIPC_MSG.SIM_SML_SET_LOCK_CNF */
enum mipc_sim_sml_set_lock_cnf_tlv_enum {
    mipc_sim_sml_set_lock_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SIM_SML_ENTER_DEVICE_DEPERSONALIZATION_REQ */
enum mipc_sim_sml_enter_device_depersonalization_req_tlv_enum {
    mipc_sim_sml_enter_device_depersonalization_req_tlv_NONE = 0,
    /* string of device key, for device lock verification */
    /* type = string */
    MIPC_SIM_SML_ENTER_DEVICE_DEPERSONALIZATION_REQ_T_KEY   = 0x8100,
};

    /* MIPC_MSG.SIM_SML_ENTER_DEVICE_DEPERSONALIZATION_CNF */
enum mipc_sim_sml_enter_device_depersonalization_cnf_tlv_enum {
    mipc_sim_sml_enter_device_depersonalization_cnf_tlv_NONE = 0,
    /* times left for user to retry on */
    /* type = uint8_t */
    MIPC_SIM_SML_ENTER_DEVICE_DEPERSONALIZATION_CNF_T_REMAIN_COUNT = 0x100,
};

    /* MIPC_MSG.SIM_SML_GET_DEV_LOCK_REQ */
enum mipc_sim_sml_get_dev_lock_req_tlv_enum {
    mipc_sim_sml_get_dev_lock_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SIM_SML_GET_DEV_LOCK_CNF */
enum mipc_sim_sml_get_dev_lock_cnf_tlv_enum {
    mipc_sim_sml_get_dev_lock_cnf_tlv_NONE = 0,
    /* device lock state, 0-locked, 1-unlocked */
    /* type = uint8_t */
    MIPC_SIM_SML_GET_DEV_LOCK_CNF_T_LOCK_STATE              = 0x100,
    /* protection algorithm used by the device lock, 0 means plaintext, 1 means PBKDF2-HMAC-SHA256 */
    /* type = uint8_t */
    MIPC_SIM_SML_GET_DEV_LOCK_CNF_T_ALGO                    = 0x101,
    /* max retry count for user can try on for device lock verification */
    /* type = uint8_t */
    MIPC_SIM_SML_GET_DEV_LOCK_CNF_T_MAX_CNT                 = 0x102,
    /* remain retry count for user can try on for device lock verification */
    /* type = uint8_t */
    MIPC_SIM_SML_GET_DEV_LOCK_CNF_T_REMAIN_CNT              = 0x103,
};

    /* MIPC_MSG.SIM_SML_RSU_REQ */
enum mipc_sim_sml_rsu_req_tlv_enum {
    mipc_sim_sml_rsu_req_tlv_NONE = 0,
    /* operator id */
    /* type = uint32_t */
    MIPC_SIM_SML_RSU_REQ_T_OPERATOR_ID                      = 0x100,
    /* request function id */
    /* type = uint32_t, refer to SIM_SML_RSU_OPERATION */
    MIPC_SIM_SML_RSU_REQ_T_REQUEST_ID                       = 0x101,
    /* unlock timer operation id */
    /* type = uint32_t */
    MIPC_SIM_SML_RSU_REQ_T_REQUEST_TYPE                     = 0x102,
    /* data */
    /* type = string */
    MIPC_SIM_SML_RSU_REQ_T_DATA                             = 0x8103,
    /* reserve int 1 */
    /* type = uint32_t */
    MIPC_SIM_SML_RSU_REQ_T_RSV1                             = 0x104,
    /* reserve int 2 */
    /* type = uint32_t */
    MIPC_SIM_SML_RSU_REQ_T_RSV2                             = 0x105,
    /* RFU data string */
    /* type = string */
    MIPC_SIM_SML_RSU_REQ_T_RSV_STRING                       = 0x8106,
};

    /* MIPC_MSG.SIM_SML_RSU_CNF */
enum mipc_sim_sml_rsu_cnf_tlv_enum {
    mipc_sim_sml_rsu_cnf_tlv_NONE = 0,
    /* operator id */
    /* type = uint32_t */
    MIPC_SIM_SML_RSU_CNF_T_OPERATOR_ID                      = 0x100,
    /* request function id */
    /* type = uint32_t */
    MIPC_SIM_SML_RSU_CNF_T_REQUEST_ID                       = 0x101,
    /* unlock timer operation id */
    /* type = uint32_t */
    MIPC_SIM_SML_RSU_CNF_T_REQUEST_TYPE                     = 0x102,
    /* cme error code */
    /* type = uint32_t */
    MIPC_SIM_SML_RSU_CNF_T_ERROR_CODE                       = 0x103,
    /* data */
    /* type = string */
    MIPC_SIM_SML_RSU_CNF_T_DATA                             = 0x8104,
    /* temporary unlock time remaining seconds */
    /* type = byte_array */
    MIPC_SIM_SML_RSU_CNF_T_TIME                             = 0x105,
    /* 2 x MSB for major version and 2 x LSB for minor version */
    /* type = uint32_t */
    MIPC_SIM_SML_RSU_CNF_T_VERSION                          = 0x106,
    /* lock status */
    /* type = uint32_t */
    MIPC_SIM_SML_RSU_CNF_T_STATUS                           = 0x107,
    /* reserve int 1 */
    /* type = uint32_t */
    MIPC_SIM_SML_RSU_CNF_T_RSV1                             = 0x108,
    /* reserve int 2 */
    /* type = uint32_t */
    MIPC_SIM_SML_RSU_CNF_T_RSV2                             = 0x109,
    /* RFU data string */
    /* type = string */
    MIPC_SIM_SML_RSU_CNF_T_RSV_STRING                       = 0x810A,
};

    /* MIPC_MSG.SIM_VSIM_SET_AKA_REQ */
enum mipc_sim_vsim_set_aka_req_tlv_enum {
    mipc_sim_vsim_set_aka_req_tlv_NONE = 0,
    /* 0-non-AKA, 1-AKA */
    /* type = uint8_t */
    MIPC_SIM_VSIM_SET_AKA_REQ_T_MODE                        = 0x100,
};

    /* MIPC_MSG.SIM_VSIM_SET_AKA_CNF */
enum mipc_sim_vsim_set_aka_cnf_tlv_enum {
    mipc_sim_vsim_set_aka_cnf_tlv_NONE = 0,
    /* result of set aka sim */
    /* type = uint32_t */
    MIPC_SIM_VSIM_SET_AKA_CNF_T_RESULT                      = 0x100,
};

    /* MIPC_MSG.SIM_VSIM_ENABLE_REQ */
enum mipc_sim_vsim_enable_req_tlv_enum {
    mipc_sim_vsim_enable_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SIM_VSIM_ENABLE_CNF */
enum mipc_sim_vsim_enable_cnf_tlv_enum {
    mipc_sim_vsim_enable_cnf_tlv_NONE = 0,
    /* result of enable Vsim */
    /* type = uint32_t */
    MIPC_SIM_VSIM_ENABLE_CNF_T_RESULT                       = 0x100,
};

    /* MIPC_MSG.SIM_VSIM_DISABLE_REQ */
enum mipc_sim_vsim_disable_req_tlv_enum {
    mipc_sim_vsim_disable_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SIM_VSIM_DISABLE_CNF */
enum mipc_sim_vsim_disable_cnf_tlv_enum {
    mipc_sim_vsim_disable_cnf_tlv_NONE = 0,
    /* result of enable Vsim */
    /* type = uint32_t */
    MIPC_SIM_VSIM_DISABLE_CNF_T_RESULT                      = 0x100,
};

    /* MIPC_MSG.SIM_VSIM_PLUG_REQ */
enum mipc_sim_vsim_plug_req_tlv_enum {
    mipc_sim_vsim_plug_req_tlv_NONE = 0,
    /* 0-in, 1-out */
    /* type = uint8_t */
    MIPC_SIM_VSIM_PLUG_REQ_T_MODE                           = 0x100,
    /* 0-LOCAL_SIM, 1-REMOTE_SIM */
    /* type = uint8_t, refer to SIM_VSIM_TYPE */
    MIPC_SIM_VSIM_PLUG_REQ_T_SIM_TYPE                       = 0x101,
};

    /* MIPC_MSG.SIM_VSIM_PLUG_CNF */
enum mipc_sim_vsim_plug_cnf_tlv_enum {
    mipc_sim_vsim_plug_cnf_tlv_NONE = 0,
    /* result of plug in/out vsim */
    /* type = uint32_t */
    MIPC_SIM_VSIM_PLUG_CNF_T_RESULT                         = 0x100,
};

    /* MIPC_MSG.SIM_VSIM_SET_TIMER_REQ */
enum mipc_sim_vsim_set_timer_req_tlv_enum {
    mipc_sim_vsim_set_timer_req_tlv_NONE = 0,
    /* vsim timer */
    /* type = uint32_t */
    MIPC_SIM_VSIM_SET_TIMER_REQ_T_TIMER                     = 0x8100,
};

    /* MIPC_MSG.SIM_VSIM_SET_TIMER_CNF */
enum mipc_sim_vsim_set_timer_cnf_tlv_enum {
    mipc_sim_vsim_set_timer_cnf_tlv_NONE = 0,
    /* result of set vsim timer */
    /* type = uint32_t */
    MIPC_SIM_VSIM_SET_TIMER_CNF_T_RESULT                    = 0x100,
};

    /* MIPC_MSG.SIM_VSIM_RESET_REQ */
enum mipc_sim_vsim_reset_req_tlv_enum {
    mipc_sim_vsim_reset_req_tlv_NONE = 0,
    /* reset result */
    /* type = uint32_t */
    MIPC_SIM_VSIM_RESET_REQ_T_RESULT                        = 0x100,
    /* data length */
    /* type = uint32_t */
    MIPC_SIM_VSIM_RESET_REQ_T_LENGTH                        = 0x101,
    /* reset data */
    /* type = string */
    MIPC_SIM_VSIM_RESET_REQ_T_DATA                          = 0x102,
};

    /* MIPC_MSG.SIM_VSIM_RESET_CNF */
enum mipc_sim_vsim_reset_cnf_tlv_enum {
    mipc_sim_vsim_reset_cnf_tlv_NONE = 0,
    /* result of reset vsim */
    /* type = uint32_t */
    MIPC_SIM_VSIM_RESET_CNF_T_RESULT                        = 0x100,
};

    /* MIPC_MSG.SIM_VSIM_APDU_REQ */
enum mipc_sim_vsim_apdu_req_tlv_enum {
    mipc_sim_vsim_apdu_req_tlv_NONE = 0,
    /* data length */
    /* type = uint32_t */
    MIPC_SIM_VSIM_APDU_REQ_T_LENGTH                         = 0x100,
    /* APDU data */
    /* type = string */
    MIPC_SIM_VSIM_APDU_REQ_T_DATA                           = 0x8101,
};

    /* MIPC_MSG.SIM_VSIM_APDU_CNF */
enum mipc_sim_vsim_apdu_cnf_tlv_enum {
    mipc_sim_vsim_apdu_cnf_tlv_NONE = 0,
    /* result of send APDU */
    /* type = uint32_t */
    MIPC_SIM_VSIM_APDU_CNF_T_RESULT                         = 0x100,
};

    /* MIPC_MSG.SIM_VSIM_AUTH_REQ */
enum mipc_sim_vsim_auth_req_tlv_enum {
    mipc_sim_vsim_auth_req_tlv_NONE = 0,
    /* 1-occuping RF, 0-releasing RF */
    /* type = uint8_t, refer to SIM_VSIM_AUTH_MODE */
    MIPC_SIM_VSIM_AUTH_REQ_T_MODE                           = 0x100,
};

    /* MIPC_MSG.SIM_VSIM_AUTH_CNF */
enum mipc_sim_vsim_auth_cnf_tlv_enum {
    mipc_sim_vsim_auth_cnf_tlv_NONE = 0,
    /* result of auth */
    /* type = uint32_t */
    MIPC_SIM_VSIM_AUTH_CNF_T_RESULT                         = 0x100,
};

    /* MIPC_MSG.SIM_CDMA_SUBSCRIPTION_REQ */
enum mipc_sim_cdma_subscription_req_tlv_enum {
    mipc_sim_cdma_subscription_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SIM_CDMA_SUBSCRIPTION_CNF */
enum mipc_sim_cdma_subscription_cnf_tlv_enum {
    mipc_sim_cdma_subscription_cnf_tlv_NONE = 0,
    /* result  */
    /* type = uint32_t */
    MIPC_SIM_CDMA_SUBSCRIPTION_CNF_T_RESULT                 = 0x100,
    /* type = string */
    MIPC_SIM_CDMA_SUBSCRIPTION_CNF_T_MSISDN                 = 0x101,
    /* CDMA home SID/NID count, max 20 */
    /* type = uint8_t */
    MIPC_SIM_CDMA_SUBSCRIPTION_CNF_T_SID_NID_COUNT          = 0x102,
    /* type = struct_array, refer to sid_nid_list */
    MIPC_SIM_CDMA_SUBSCRIPTION_CNF_T_SID_NID_LIST           = 0x103,
    /* type = string */
    MIPC_SIM_CDMA_SUBSCRIPTION_CNF_T_VMIN                   = 0x104,
    /* type = string */
    MIPC_SIM_CDMA_SUBSCRIPTION_CNF_T_VPRLID                 = 0x105,
};

    /* MIPC_MSG.SIM_CDMA_GET_SUBSCRIPTION_SOURCE_REQ */
enum mipc_sim_cdma_get_subscription_source_req_tlv_enum {
    mipc_sim_cdma_get_subscription_source_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SIM_CDMA_GET_SUBSCRIPTION_SOURCE_CNF */
enum mipc_sim_cdma_get_subscription_source_cnf_tlv_enum {
    mipc_sim_cdma_get_subscription_source_cnf_tlv_NONE = 0,
    /* result of auth */
    /* type = uint32_t */
    MIPC_SIM_CDMA_GET_SUBSCRIPTION_SOURCE_CNF_T_RESULT      = 0x100,
    /* UIM state, 0- UIM disable, 1- UIM enable */
    /* type = uint8_t */
    MIPC_SIM_CDMA_GET_SUBSCRIPTION_SOURCE_CNF_T_UIM_STATE   = 0x101,
};

    /* MIPC_MSG.SIM_PIN_COUNT_QUERY_REQ */
enum mipc_sim_pin_count_query_req_tlv_enum {
    mipc_sim_pin_count_query_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SIM_PIN_COUNT_QUERY_CNF */
enum mipc_sim_pin_count_query_cnf_tlv_enum {
    mipc_sim_pin_count_query_cnf_tlv_NONE = 0,
    /* result of pin count query */
    /* type = uint32_t */
    MIPC_SIM_PIN_COUNT_QUERY_CNF_T_RESULT                   = 0x100,
    /* pin1 remaining attempts */
    /* type = uint8_t */
    MIPC_SIM_PIN_COUNT_QUERY_CNF_T_PIN1                     = 0x101,
    /* pin2 remaining attempts */
    /* type = uint8_t */
    MIPC_SIM_PIN_COUNT_QUERY_CNF_T_PIN2                     = 0x102,
    /* puk1 remaining attempts */
    /* type = uint8_t */
    MIPC_SIM_PIN_COUNT_QUERY_CNF_T_PUK1                     = 0x103,
    /* puk2 remaining attempts */
    /* type = uint8_t */
    MIPC_SIM_PIN_COUNT_QUERY_CNF_T_PUK2                     = 0x104,
};

    /* MIPC_MSG.SIM_SML_GET_NETWORK_LOCK_REQ */
enum mipc_sim_sml_get_network_lock_req_tlv_enum {
    mipc_sim_sml_get_network_lock_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SIM_SML_GET_NETWORK_LOCK_CNF */
enum mipc_sim_sml_get_network_lock_cnf_tlv_enum {
    mipc_sim_sml_get_network_lock_cnf_tlv_NONE = 0,
    /* carrier id */
    /* type = uint32_t */
    MIPC_SIM_SML_GET_NETWORK_LOCK_CNF_T_CARRIER_ID          = 0x100,
    /* supported sml lock cats, every bit maps to a sml lock cats, if bit value is 1 means this cat is supported. 3GPP_NW(bit0)/3GPP_NS(bit1)/3GPP_SP(bit2)/3GPP_CP(bit3)/3GPP_SIM(bit4)/NS_NP(bit5)/SIM_C(bit6) */
    /* type = uint32_t */
    MIPC_SIM_SML_GET_NETWORK_LOCK_CNF_T_SUPPORTED_CATS      = 0x101,
    /* now fixed 0x01 */
    /* type = uint32_t */
    MIPC_SIM_SML_GET_NETWORK_LOCK_CNF_T_VERSION             = 0x102,
    /* network lock status, 0 means unlocked, 1 means locked */
    /* type = uint8_t */
    MIPC_SIM_SML_GET_NETWORK_LOCK_CNF_T_LOCK_STATUS         = 0x103,
    /* sim lock is enable or configured in modem side, 1 means md configured, 0 means not configured */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_SIM_SML_GET_NETWORK_LOCK_CNF_T_LOCK_FUSE           = 0x104,
    /* unlock by local or remote, 1 means unlock by remote server, 0 means by local */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_SIM_SML_GET_NETWORK_LOCK_CNF_T_RSU_ENABLE          = 0x105,
    /* reserve to save sim me lock rules */
    /* type = uint16_t */
    MIPC_SIM_SML_GET_NETWORK_LOCK_CNF_T_RULE                = 0x106,
    /* reserve to save sim me lock subrules */
    /* type = uint16_t */
    MIPC_SIM_SML_GET_NETWORK_LOCK_CNF_T_SUBRULE             = 0x107,
};

    /* MIPC_MSG.SMS_CFG_REQ */
enum mipc_sms_cfg_req_tlv_enum {
    mipc_sms_cfg_req_tlv_NONE = 0,
    /* set or get DEVICE SMS format setting */
    /* type = uint8_t, refer to SMS_FORMAT */
    MIPC_SMS_CFG_REQ_T_FORMAT                               = 0x100,
    /* [3GPP] set the SCA(sms center address) */
    /* type = string */
    MIPC_SMS_CFG_REQ_T_SET_SCA                              = 0x8101,
    /* [3GPP] if need get the sca: 0->no_need, other->need */
    /* type = uint8_t */
    MIPC_SMS_CFG_REQ_T_GET_SCA                              = 0x102,
    /* [PHASE OUT] no need set, DEVICE always return SMS state now */
    /* type = uint8_t */
    MIPC_SMS_CFG_REQ_T_GET_SMS_STATE                        = 0x103,
    /* [PHASE OUT] */
    /* type = uint8_t */
    MIPC_SMS_CFG_REQ_T_GET_STORE_STATUS                     = 0x104,
    /* set or get prefer_ack; [3GPP]prefer_ack means if USER want to ack for the new sms to TE(save in SIM would not need ack from USER); [3GPP2]only if prefer_save_c2k_in_te & prefer_ack & mt_pdu_contain_bearer_reply_option, then need ack from HOST */
    /* type = uint8_t, refer to SMS_ACK */
    MIPC_SMS_CFG_REQ_T_PREFER_ACK                           = 0x105,
    /* set or get prefer_storage. prefer_storage means that which storage USER want to save mt sms. if not TE: always UIM for 3gpp2 format, use this tlv for 3gpp format */
    /* type = uint8_t, refer to SMS_STORAGE */
    MIPC_SMS_CFG_REQ_T_PREFER_STORAGE                       = 0x106,
    /* [PHASE OUT]indicate if need get all the setting: 0->no_need, other->need. not recommend */
    /* type = uint8_t */
    MIPC_SMS_CFG_REQ_T_GET_ALL_CAN_GET                      = 0x107,
    /* HOST notify DEVICE that HOST's SMS storage is valid(true) or invalid(false), so DEVICE may ack err quick to NW when recv sms. refer to AT+EMEMS in MTK_AT. MD will ignore this cfg when prefer save not TE */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_SMS_CFG_REQ_T_SET_HOST_MEM_AVAILABLE               = 0x108,
    /* [3GPP] mipc not support Text mode, but can set text mode parameter as AT+CSMP */
    /* type = uint8_t, refer to SMS_TEXT_MODE_PARAM_ACTION */
    MIPC_SMS_CFG_REQ_T_TEXT_MODE_PARAM_ACTION               = 0x109,
    /* [3GPP] refer TS27.005 3.3.2 <fo> */
    /* type = uint8_t */
    MIPC_SMS_CFG_REQ_T_TEXT_MODE_FO                         = 0x10A,
    /* [3GPP] refer TS27.005 3.3.2 <vp> */
    /* type = uint8_t */
    MIPC_SMS_CFG_REQ_T_TEXT_MODE_VP                         = 0x10B,
    /* [3GPP] refer TS27.005 3.3.2 <pid> */
    /* type = uint8_t */
    MIPC_SMS_CFG_REQ_T_TEXT_MODE_PID                        = 0x10C,
    /* [3GPP] refer TS27.005 3.3.2 <dcs> */
    /* type = uint8_t */
    MIPC_SMS_CFG_REQ_T_TEXT_MODE_DCS                        = 0x10D,
    /* [PHASE OUT] */
    /* type = uint8_t, refer to SMS_STORAGE */
    MIPC_SMS_CFG_REQ_T_PREFER_STORAGE_C2K                   = 0x10E,
    /* where to do read/write/delete operation for 3gpp format sms? [3GPP]default setting is MT. If PREFER_STORAGE is TE, this tlv could be configured; If PREFER_STORAGE is not TE, W_R_D_STORAGE would be same as PREFER_STORAGE. No W_R_D_STORAGE for 3GPP2 because 3gpp2 always UIM and couldn't be changed */
    /* type = uint8_t, refer to SMS_STORAGE */
    MIPC_SMS_CFG_REQ_T_W_R_D_STORAGE                        = 0x10F,
    /* save the settings to non-volatile memory, refer CSAS, currently only support save setting of SCA */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_SMS_CFG_REQ_T_SAVE_SETTING                         = 0x110,
};

    /* MIPC_MSG.SMS_CFG_CNF */
enum mipc_sms_cfg_cnf_tlv_enum {
    mipc_sms_cfg_cnf_tlv_NONE = 0,
    /* indicate the format that configured for this protocal */
    /* type = uint8_t, refer to SMS_FORMAT */
    MIPC_SMS_CFG_CNF_T_FORMAT                               = 0x100,
    /* [3GPP] indicate the SCA(sms center address) that configured for this protocal */
    /* type = string */
    MIPC_SMS_CFG_CNF_T_SCA                                  = 0x8101,
    /* indicate if the sms module is initialized */
    /* type = uint8_t, refer to SMS_STATE */
    MIPC_SMS_CFG_CNF_T_SMS_STATE                            = 0x102,
    /* [3GPP] indicate the max messages that can be saved in this protocal */
    /* type = uint16_t */
    MIPC_SMS_CFG_CNF_T_MAX_MESSAGE                          = 0x103,
    /* indicate if user want to ack for the new sms to TE(save in SIM would not need ack from user) */
    /* type = uint8_t, refer to SMS_ACK */
    MIPC_SMS_CFG_CNF_T_PREFER_ACK                           = 0x104,
    /* indicate which storage user want to save mt sms. TE: new MT msg would indicated with NEW_SMS_IND(PREFER_ACK=FALSE) or NEW_SMS_CMD(PREFER_ACK=TRUE); <not TE>: new MT msg would indicated with STORE_STATUS_IND. This cfg option is just PREFER(CBM & STATUS_REPORT can not support save in sim now) */
    /* type = uint8_t, refer to SMS_STORAGE */
    MIPC_SMS_CFG_CNF_T_PREFER_STORAGE                       = 0x105,
    /* [3GPP] indicate the used messages number saved in this protocal */
    /* type = uint16_t */
    MIPC_SMS_CFG_CNF_T_USED_MESSAGE                         = 0x106,
    /* [3GPP] indicate the total messages number that can be saved in this protocal */
    /* type = uint16_t */
    MIPC_SMS_CFG_CNF_T_TOTAL_MESSAGE                        = 0x107,
    /* [3GPP] refer TS27.005 3.3.2 <fo> */
    /* type = uint8_t */
    MIPC_SMS_CFG_CNF_T_TEXT_MODE_FO                         = 0x10A,
    /* [3GPP] refer TS27.005 3.3.2 <vp> */
    /* type = uint8_t */
    MIPC_SMS_CFG_CNF_T_TEXT_MODE_VP                         = 0x10B,
    /* [3GPP] refer TS27.005 3.3.2 <pid> */
    /* type = uint8_t */
    MIPC_SMS_CFG_CNF_T_TEXT_MODE_PID                        = 0x10C,
    /* [3GPP] refer TS27.005 3.3.2 <dcs> */
    /* type = uint8_t */
    MIPC_SMS_CFG_CNF_T_TEXT_MODE_DCS                        = 0x10D,
    /* [PHASE OUT] */
    /* type = uint8_t, refer to SMS_STORAGE */
    MIPC_SMS_CFG_CNF_T_PREFER_STORAGE_C2K                   = 0x10E,
    /* [PHASE OUT] */
    /* type = uint16_t */
    MIPC_SMS_CFG_CNF_T_USED_MESSAGE_C2K                     = 0x10F,
    /* [PHASE OUT] */
    /* type = uint16_t */
    MIPC_SMS_CFG_CNF_T_MAX_MESSAGE_C2K                      = 0x110,
    /* where to do read/write/delete operation for 3gpp format sms? [3GPP]default setting is MT. If PREFER_STORAGE is TE, this tlv could be configured; If PREFER_STORAGE is not TE, W_R_D_STORAGE would be same as PREFER_STORAGE. No W_R_D_STORAGE for 3GPP2 because 3gpp2 always UIM and couldn't be changed */
    /* type = uint8_t, refer to SMS_STORAGE */
    MIPC_SMS_CFG_CNF_T_W_R_D_STORAGE                        = 0x111,
};

    /* MIPC_MSG.SMS_SEND_REQ */
enum mipc_sms_send_req_tlv_enum {
    mipc_sms_send_req_tlv_NONE = 0,
    /* indicate the format of that msg to be sent, support PDU_3GPP & PDU_3GPP2 now */
    /* type = uint8_t, refer to SMS_FORMAT */
    MIPC_SMS_SEND_REQ_T_FORMAT                              = 0x100,
    /* [PDU_3GPP] pdu contains sca, can refer the pdu parameter in CMGS */
    /* type = byte_array */
    MIPC_SMS_SEND_REQ_T_PDU                                 = 0x8101,
    /* [PHASE OUT]PDU could cover this tlv, so no need anymore */
    /* type = uint8_t */
    MIPC_SMS_SEND_REQ_T_PDU_LEN                             = 0x102,
    /* [PDU_3GPP] save the sent msg to DEVICE or SIM , default no_save, not support save with CDMA format now */
    /* type = uint8_t, refer to SMS_SEND_SAVE */
    MIPC_SMS_SEND_REQ_T_SAVE                                = 0x103,
    /* [PDU_3GPP] expect_more option, indicate if there is more sms to send, enable to keep link opened. default NULL */
    /* type = uint8_t, refer to SMS_MORE_MSG_TO_SEND */
    MIPC_SMS_SEND_REQ_T_MORE_MSG_TO_SEND                    = 0x104,
    /* [PDU_3GPP2] refer to the 2nd parmameter of EC2KCMGS */
    /* type = byte_array */
    MIPC_SMS_SEND_REQ_T_PDU_C2K                             = 0x8105,
    /* [PDU_3GPP2]  CDMA dest_address in decimal number string(length contains the /0), refer to the 3rd parmameter of EC2KCMGS */
    /* type = string */
    MIPC_SMS_SEND_REQ_T_NUM_C2K                             = 0x8106,
};

    /* MIPC_MSG.SMS_SEND_CNF */
enum mipc_sms_send_cnf_tlv_enum {
    mipc_sms_send_cnf_tlv_NONE = 0,
    /* [PDU_3GPP] message reference of sent message */
    /* type = uint8_t */
    MIPC_SMS_SEND_CNF_T_MR                                  = 0x103,
    /* [PDU_3GPP] if need to save in SEND_REQ, this IE would carry the valid message index in storage */
    /* type = uint16_t */
    MIPC_SMS_SEND_CNF_T_MESSAGE_INDEX                       = 0x104,
    /* [PDU_3GPP2] error class of C2K operation */
    /* type = uint8_t, refer to SMS_C2K_ERR_CLASS */
    MIPC_SMS_SEND_CNF_T_ERR_CLASS_C2K                       = 0x105,
    /* indicate the format sent */
    /* type = uint8_t, refer to SMS_FORMAT */
    MIPC_SMS_SEND_CNF_T_FORMAT                              = 0x106,
    /* [PDU_3GPP2] C2K error code */
    /* type = uint16_t, refer to SMS_C2K_ERR_CODE */
    MIPC_SMS_SEND_CNF_T_ERR_CODE_C2K                        = 0x107,
    /* [PDU_3GPP][ztbd] can refer the <ackpdu> in CMGS */
    /* type = byte_array */
    MIPC_SMS_SEND_CNF_T_ACK_PDU                             = 0x8108,
    /* [PDU_3GPP2] message id(refer CS0015 4.5.1 MESSAGE_ID) of sent message */
    /* type = uint16_t */
    MIPC_SMS_SEND_CNF_T_MSGID_C2K                           = 0x109,
};

    /* MIPC_MSG.SMS_READ_REQ */
enum mipc_sms_read_req_tlv_enum {
    mipc_sms_read_req_tlv_NONE = 0,
    /* the format to be read. default: PDU_3GPP, currently only support PDU_3GPP */
    /* type = uint8_t, refer to SMS_FORMAT */
    MIPC_SMS_READ_REQ_T_FORMAT                              = 0x100,
    /* which type of sms to be read */
    /* type = uint8_t, refer to SMS_FLAG */
    MIPC_SMS_READ_REQ_T_FLAG                                = 0x101,
    /* which sms should to be read, only valid when flag is INDEX. If flag is INDEX and carry this IE, this IE should be 0 */
    /* type = uint16_t */
    MIPC_SMS_READ_REQ_T_MESSAGE_INDEX                       = 0x102,
};

    /* MIPC_MSG.SMS_READ_CNF */
enum mipc_sms_read_cnf_tlv_enum {
    mipc_sms_read_cnf_tlv_NONE = 0,
    /* the format readed */
    /* type = uint8_t, refer to SMS_FORMAT */
    MIPC_SMS_READ_CNF_T_FORMAT                              = 0x100,
    /* [PDU_3GPP] the count of readed sms */
    /* type = uint16_t */
    MIPC_SMS_READ_CNF_T_PDU_COUNT                           = 0x103,
    /* [PDU_3GPP] list of read sms */
    /* type = struct_array, refer to sms_pdu */
    MIPC_SMS_READ_CNF_T_PDU_LIST                            = 0x8104,
    /* [PDU_3GPP2] read sms */
    /* type = byte_array */
    MIPC_SMS_READ_CNF_T_PDU_C2K                             = 0x8105,
};

    /* MIPC_MSG.SMS_DELETE_REQ */
enum mipc_sms_delete_req_tlv_enum {
    mipc_sms_delete_req_tlv_NONE = 0,
    /* which type of sms to be delete */
    /* type = uint8_t, refer to SMS_FLAG */
    MIPC_SMS_DELETE_REQ_T_FLAG                              = 0x100,
    /* which sms should to be delete. Only valid when flag is INDEX. If flag is INDEX and carry this IE, this IE's value should be 0 */
    /* type = uint16_t */
    MIPC_SMS_DELETE_REQ_T_MESSAGE_INDEX                     = 0x101,
    /* the format to delete, default PDU_3GPP */
    /* type = uint8_t, refer to SMS_FORMAT */
    MIPC_SMS_DELETE_REQ_T_FORMAT                            = 0x102,
};

    /* MIPC_MSG.SMS_DELETE_CNF */
enum mipc_sms_delete_cnf_tlv_enum {
    mipc_sms_delete_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SMS_GET_STORE_STATUS_REQ */
enum mipc_sms_get_store_status_req_tlv_enum {
    mipc_sms_get_store_status_req_tlv_NONE = 0,
    /* [PHASE OUT] */
    /* type = uint8_t, refer to SMS_STORAGE */
    MIPC_SMS_GET_STORE_STATUS_REQ_T_STORAGE                 = 0x100,
    /* PDU_3GPP -> get status of W_R_D_STORAGE; PDU_3GPP2 -> get status of UIM */
    /* type = uint8_t, refer to SMS_FORMAT */
    MIPC_SMS_GET_STORE_STATUS_REQ_T_FORMAT                  = 0x101,
};

    /* MIPC_MSG.SMS_GET_STORE_STATUS_CNF */
enum mipc_sms_get_store_status_cnf_tlv_enum {
    mipc_sms_get_store_status_cnf_tlv_NONE = 0,
    /* indicate if <the storage full> or <new sms in DEVICE received> */
    /* type = bitmap, refer to SMS_STORE_FLAG */
    MIPC_SMS_GET_STORE_STATUS_CNF_T_FLAG                    = 0x100,
    /* if the falg indicated there is new message, this shows the message_index */
    /* type = uint16_t */
    MIPC_SMS_GET_STORE_STATUS_CNF_T_MESSAGE_INDEX           = 0x101,
    /* indicate the max messages that can be saved in this protocal */
    /* type = uint16_t */
    MIPC_SMS_GET_STORE_STATUS_CNF_T_MAX_MESSAGE             = 0x102,
    /* indicate the used messages number saved in this protocal */
    /* type = uint16_t */
    MIPC_SMS_GET_STORE_STATUS_CNF_T_USED_MESSAGE            = 0x103,
    /* [PHASE OUT] */
    /* type = uint8_t, refer to SMS_STORAGE */
    MIPC_SMS_GET_STORE_STATUS_CNF_T_STORAGE                 = 0x104,
};

    /* MIPC_MSG.SMS_WRITE_REQ */
enum mipc_sms_write_req_tlv_enum {
    mipc_sms_write_req_tlv_NONE = 0,
    /* PDU_3GPP or PDU_3GPP2, defaut PDU_3GPP */
    /* type = uint8_t, refer to SMS_FORMAT */
    MIPC_SMS_WRITE_REQ_T_FORMAT                             = 0x100,
    /* [3GPP]pdu contains sca(if no sca, just 0x00 prefix); [3GPP2]the second parameter of EC2KCMGW */
    /* type = byte_array */
    MIPC_SMS_WRITE_REQ_T_PDU                                = 0x8101,
    /* [PHASE OUT] */
    /* type = uint8_t */
    MIPC_SMS_WRITE_REQ_T_PDU_LEN                            = 0x102,
    /* [PHASE OUT] */
    /* type = uint8_t, refer to SMS_STORAGE */
    MIPC_SMS_WRITE_REQ_T_STORAGE                            = 0x103,
    /* message status */
    /* type = uint8_t, refer to SMS_STATUS */
    MIPC_SMS_WRITE_REQ_T_STATUS                             = 0x104,
    /* [PHASE OUT] */
    /* type = byte_array */
    MIPC_SMS_WRITE_REQ_T_PDU_C2K                            = 0x8105,
};

    /* MIPC_MSG.SMS_WRITE_CNF */
enum mipc_sms_write_cnf_tlv_enum {
    mipc_sms_write_cnf_tlv_NONE = 0,
    /* the message index of write location */
    /* type = uint16_t */
    MIPC_SMS_WRITE_CNF_T_MESSAGE_INDEX                      = 0x100,
};

    /* MIPC_MSG.SMS_CBM_CFG_REQ */
enum mipc_sms_cbm_cfg_req_tlv_enum {
    mipc_sms_cbm_cfg_req_tlv_NONE = 0,
    /* [3GPP]indicate which type of cbm msg that USER needed */
    /* type = bitmap, refer to SMS_CBM_TYPE */
    MIPC_SMS_CBM_CFG_REQ_T_OPEN_CBM_TYPE                    = 0x100,
    /* [3GPP]message identifier in TS23.041; [3GPP2]service category in CS.0015 */
    /* type = uint8_t, refer to SMS_CBM_CFG_TYPE */
    MIPC_SMS_CBM_CFG_REQ_T_MSG_ID_CFG_TYPE                  = 0x101,
    /* allow or ban msg_id range config, most significant 16 bit means least msg_id in this range, least significant 16 bit means highest msg_id in this range, range contains begining and ending msg_id */
    /* type = uint32_t */
    MIPC_SMS_CBM_CFG_REQ_T_MSG_ID_RANGE                     = 0x102,
    /* allow or ban msg_id config */
    /* type = uint16_t */
    MIPC_SMS_CBM_CFG_REQ_T_MSG_ID_SINGLE                    = 0x103,
    /* [3GPP]data coding scheme in TS23.041; [3GPP2]language indicator in CS.0015 */
    /* type = uint8_t, refer to SMS_CBM_CFG_TYPE */
    MIPC_SMS_CBM_CFG_REQ_T_DCS_CFG_TYPE                     = 0x104,
    /* allow or ban dcs range config(can be arrary format, most 30 elements),most significant 8 bit means least dcs in this range, least significant 8 bit means highest dcs in this range, range contains begining and ending dcs */
    /* type = uint16_t */
    MIPC_SMS_CBM_CFG_REQ_T_DCS_RANGE                        = 0x105,
    /* allow or ban dcs range config(can be arrary format, most 60 elements),similar to MSG_ID_SINGLE */
    /* type = uint8_t */
    MIPC_SMS_CBM_CFG_REQ_T_DCS_SINGLE                       = 0x106,
    /* [3GPP]in order to be compatible with AT+ETWS, default 0xff */
    /* type = bitmap, refer to SMS_ETWS_PRIMARY_TYPE */
    MIPC_SMS_CBM_CFG_REQ_T_ETWS_PRIMARY_CFG                 = 0x107,
    /* the format for cfg req, only pdu_3gpp or pdu_3gpp2, default as pdu_3gpp */
    /* type = uint8_t, refer to SMS_FORMAT */
    MIPC_SMS_CBM_CFG_REQ_T_FORMAT                           = 0x108,
    /* [3GPP2] for compatible with AT+ECSCB, default is on */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_SMS_CBM_CFG_REQ_T_C2K_CBM_ENABLE                   = 0x109,
    /* [3GPP] for 3gpp cbm, enable/disable the PDU_3GPP_SEG in NEW_CBM_IND follow the format of +CBM URC */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_SMS_CBM_CFG_REQ_T_PDU_3GPP_SEG_ENABLE              = 0x10A,
};

    /* MIPC_MSG.SMS_CBM_CFG_CNF */
enum mipc_sms_cbm_cfg_cnf_tlv_enum {
    mipc_sms_cbm_cfg_cnf_tlv_NONE = 0,
    /* [3GPP]indicate <which type of cbm msg that USER needed> configured in DEVICE */
    /* type = bitmap, refer to SMS_CBM_TYPE */
    MIPC_SMS_CBM_CFG_CNF_T_OPEN_CBM_TYPE                    = 0x100,
    /* indicate <MSG_ID_CFG_TYPE> saved in DEVICE, present when REQ's MSG_ID_CFG_TYPE exist */
    /* type = uint8_t, refer to SMS_CBM_CFG_TYPE */
    MIPC_SMS_CBM_CFG_CNF_T_MSG_ID_CFG_TYPE                  = 0x101,
    /* indicate <MSG_ID_RANGE> saved in DEVICE, maybe present when REQ's MSG_ID_CFG_TYPE exist */
    /* type = uint32_t */
    MIPC_SMS_CBM_CFG_CNF_T_MSG_ID_RANGE                     = 0x102,
    /* indicate <MSG_ID_SINGLE> saved in DEVICE, maybe present when REQ's MSG_ID_CFG_TYPE exist */
    /* type = uint16_t */
    MIPC_SMS_CBM_CFG_CNF_T_MSG_ID_SINGLE                    = 0x103,
    /* indicate <DCS_CFG_TYPE> saved in DEVICE, present when REQ's DCS_CFG_TYPE exist */
    /* type = uint8_t, refer to SMS_CBM_CFG_TYPE */
    MIPC_SMS_CBM_CFG_CNF_T_DCS_CFG_TYPE                     = 0x104,
    /* indicate <DCS_RANGE> saved in DEVICE, maybe present when REQ's DCS_CFG_TYPE exist */
    /* type = uint16_t */
    MIPC_SMS_CBM_CFG_CNF_T_DCS_RANGE                        = 0x105,
    /* indicate <DCS_SINGLE> saved in DEVICE, maybe present when REQ's DCS_CFG_TYPE exist */
    /* type = uint8_t */
    MIPC_SMS_CBM_CFG_CNF_T_DCS_SINGLE                       = 0x106,
    /* [3GPP]indicate language cfg for dcs saved in DEVICE, maybe present when REQ's DCS_CFG_TYPE exist. ban or allow follow dcs cfg */
    /* type = uint8_t */
    MIPC_SMS_CBM_CFG_CNF_T_LANGUAGE_SINGLE                  = 0x107,
    /* the format for cfg cnf, only pdu_3gpp or pdu_3gpp2 */
    /* type = uint8_t, refer to SMS_FORMAT */
    MIPC_SMS_CBM_CFG_CNF_T_FORMAT                           = 0x108,
    /* [3GPP2] for compatible with AT+ECSCB, when FORMAT=3gpp2, would carry this option */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_SMS_CBM_CFG_CNF_T_C2K_CBM_ENABLE                   = 0x109,
};

    /* MIPC_MSG.SMS_SCBM_REQ */
enum mipc_sms_scbm_req_tlv_enum {
    mipc_sms_scbm_req_tlv_NONE = 0,
    /* DEVICE would indicate HOST when entered SCBM mode using SCBM_IND, HOST use this value to decide quit now(or DEVICE would quit in 5min later auto) */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_SMS_SCBM_REQ_T_QUIT_SCBM_MODE                      = 0x100,
};

    /* MIPC_MSG.SMS_SCBM_CNF */
enum mipc_sms_scbm_cnf_tlv_enum {
    mipc_sms_scbm_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SS_SEND_USSD_REQ */
enum mipc_ss_send_ussd_req_tlv_enum {
    mipc_ss_send_ussd_req_tlv_NONE = 0,
    /* data coding scheme */
    /* type = uint32_t */
    MIPC_SS_SEND_USSD_REQ_T_DCS                             = 0x101,
    /* length of ussd payload */
    /* type = uint8_t */
    MIPC_SS_SEND_USSD_REQ_T_PAYLOAD_LEN                     = 0x102,
    /* byte array of ussd payload */
    /* type = byte_array */
    MIPC_SS_SEND_USSD_REQ_T_PAYLOAD                         = 0x8103,
    /* lang of send ussd req */
    /* type = string */
    MIPC_SS_SEND_USSD_REQ_T_LANG                            = 0x104,
};

    /* MIPC_MSG.SS_SEND_USSD_CNF */
enum mipc_ss_send_ussd_cnf_tlv_enum {
    mipc_ss_send_ussd_cnf_tlv_NONE = 0,
    /* ussd response */
    /* type = uint8_t, refer to SS_USSD */
    MIPC_SS_SEND_USSD_CNF_T_USSD_RESPONSE                   = 0x100,
    /*  ussd session state */
    /* type = uint8_t, refer to SS_SESSION */
    MIPC_SS_SEND_USSD_CNF_T_USSD_SESSION_STATE              = 0x101,
    /* data coding scheme */
    /* type = uint32_t */
    MIPC_SS_SEND_USSD_CNF_T_DCS                             = 0x102,
    /* length of ussd payload */
    /* type = uint8_t */
    MIPC_SS_SEND_USSD_CNF_T_PAYLOAD_LEN                     = 0x103,
    /* pointer to ussd payload */
    /* type = byte_array */
    MIPC_SS_SEND_USSD_CNF_T_PAYLOAD                         = 0x8104,
};

    /* MIPC_MSG.SS_CANCEL_USSD_REQ */
enum mipc_ss_cancel_ussd_req_tlv_enum {
    mipc_ss_cancel_ussd_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SS_CANCEL_USSD_CNF */
enum mipc_ss_cancel_ussd_cnf_tlv_enum {
    mipc_ss_cancel_ussd_cnf_tlv_NONE = 0,
    /* ussd response */
    /* type = uint8_t, refer to SS_USSD */
    MIPC_SS_CANCEL_USSD_CNF_T_USSD_RESPONSE                 = 0x100,
    /* ussd session state */
    /* type = uint8_t, refer to SS_SESSION */
    MIPC_SS_CANCEL_USSD_CNF_T_USSD_SESSION_STATE            = 0x101,
    /* data coding scheme */
    /* type = uint32_t */
    MIPC_SS_CANCEL_USSD_CNF_T_DCS                           = 0x102,
    /* payload length */
    /* type = uint8_t */
    MIPC_SS_CANCEL_USSD_CNF_T_PAYLOAD_LEN                   = 0x103,
    /* pointer to payload */
    /* type = byte_array */
    MIPC_SS_CANCEL_USSD_CNF_T_PAYLOAD                       = 0x8104,
};

    /* MIPC_MSG.SS_SET_CLIR_REQ */
enum mipc_ss_set_clir_req_tlv_enum {
    mipc_ss_set_clir_req_tlv_NONE = 0,
    /* the value to set CLIR */
    /* type = uint8_t */
    MIPC_SS_SET_CLIR_REQ_T_N_VALUE                          = 0x100,
};

    /* MIPC_MSG.SS_SET_CLIR_CNF */
enum mipc_ss_set_clir_cnf_tlv_enum {
    mipc_ss_set_clir_cnf_tlv_NONE = 0,
    /* err message of set CLIR */
    /* type = string */
    MIPC_SS_SET_CLIR_CNF_T_ERRMESSAGE                       = 0x100,
};

    /* MIPC_MSG.SS_GET_CLIR_REQ */
enum mipc_ss_get_clir_req_tlv_enum {
    mipc_ss_get_clir_req_tlv_NONE = 0,
};

    /* MIPC_MSG.SS_GET_CLIR_CNF */
enum mipc_ss_get_clir_cnf_tlv_enum {
    mipc_ss_get_clir_cnf_tlv_NONE = 0,
    /* n value of CLIR */
    /* type = uint8_t */
    MIPC_SS_GET_CLIR_CNF_T_CLIR_N                           = 0x100,
    /* m value of CLIR */
    /* type = uint8_t */
    MIPC_SS_GET_CLIR_CNF_T_CLIR_M                           = 0x101,
    /* err message of get CLIR */
    /* type = string */
    MIPC_SS_GET_CLIR_CNF_T_ERRMESSAGE                       = 0x102,
};

    /* MIPC_MSG.SS_SET_CALL_WAITING_REQ */
enum mipc_ss_set_call_waiting_req_tlv_enum {
    mipc_ss_set_call_waiting_req_tlv_NONE = 0,
    /* to enable or disable call waiting */
    /* type = uint8_t, refer to SS_CALL_WAITING */
    MIPC_SS_SET_CALL_WAITING_REQ_T_CW_ENABLE_DISABLE        = 0x100,
    /* service class */
    /* type = uint16_t, refer to SS_SERVICE_CLASS */
    MIPC_SS_SET_CALL_WAITING_REQ_T_SERVICE_CLASS            = 0x101,
};

    /* MIPC_MSG.SS_SET_CALL_WAITING_CNF */
enum mipc_ss_set_call_waiting_cnf_tlv_enum {
    mipc_ss_set_call_waiting_cnf_tlv_NONE = 0,
    /* err message of Set Call Waiting */
    /* type = string */
    MIPC_SS_SET_CALL_WAITING_CNF_T_ERRMESSAGE               = 0x100,
};

    /* MIPC_MSG.SS_QUERY_CALL_WAITING_REQ */
enum mipc_ss_query_call_waiting_req_tlv_enum {
    mipc_ss_query_call_waiting_req_tlv_NONE = 0,
    /* service class */
    /* type = uint16_t, refer to SS_SERVICE_CLASS */
    MIPC_SS_QUERY_CALL_WAITING_REQ_T_SERVICE_CLASS          = 0x100,
};

    /* MIPC_MSG.SS_QUERY_CALL_WAITING_CNF */
enum mipc_ss_query_call_waiting_cnf_tlv_enum {
    mipc_ss_query_call_waiting_cnf_tlv_NONE = 0,
    /* active or not active of call waiting */
    /* type = uint8_t, refer to SS_ACTIVE_STATUS */
    MIPC_SS_QUERY_CALL_WAITING_CNF_T_CALL_WAITING_STATUS    = 0x100,
    /* service class */
    /* type = uint16_t, refer to SS_SERVICE_CLASS */
    MIPC_SS_QUERY_CALL_WAITING_CNF_T_SERVICE_CLASS          = 0x101,
    /* number of call waiting */
    /* type = uint8_t */
    MIPC_SS_QUERY_CALL_WAITING_CNF_T_CW_COUNT               = 0x102,
    /* list of call waiting */
    /* type = struct_array, refer to ss_call_waiting */
    MIPC_SS_QUERY_CALL_WAITING_CNF_T_CW_LIST                = 0x103,
    /* err message of Query Call Waiting */
    /* type = string */
    MIPC_SS_QUERY_CALL_WAITING_CNF_T_ERRMESSAGE             = 0x104,
};

    /* MIPC_MSG.SS_SET_CALL_FORWARD_REQ */
enum mipc_ss_set_call_forward_req_tlv_enum {
    mipc_ss_set_call_forward_req_tlv_NONE = 0,
    /* ss operation type */
    /* type = uint8_t, refer to SS_SET_CALL_FORWARD_OPERATION_CODE */
    MIPC_SS_SET_CALL_FORWARD_REQ_T_SS_OPERATION             = 0x100,
    /* call forward reason */
    /* type = uint8_t, refer to SS_CALL_FORWARD_REASON */
    MIPC_SS_SET_CALL_FORWARD_REQ_T_CALL_FORWARD_REASON      = 0x101,
    /* call forward dial number */
    /* type = string */
    MIPC_SS_SET_CALL_FORWARD_REQ_T_DIAL_NUMBER              = 0x8102,
    /* service class */
    /* type = uint16_t, refer to SS_SERVICE_CLASS */
    MIPC_SS_SET_CALL_FORWARD_REQ_T_SERVICE_CLASS            = 0x103,
    /* type of address */
    /* type = uint16_t */
    MIPC_SS_SET_CALL_FORWARD_REQ_T_TOA                      = 0x104,
    /* call forward timer no reply */
    /* type = uint8_t */
    MIPC_SS_SET_CALL_FORWARD_REQ_T_TIMER_SECONDS            = 0x105,
    /* time slot begin of call forward */
    /* type = string */
    MIPC_SS_SET_CALL_FORWARD_REQ_T_TIME_SLOT_BEGIN          = 0x106,
    /* time slot end of call forward */
    /* type = string */
    MIPC_SS_SET_CALL_FORWARD_REQ_T_TIME_SLOT_END            = 0x107,
};

    /* MIPC_MSG.SS_SET_CALL_FORWARD_CNF */
enum mipc_ss_set_call_forward_cnf_tlv_enum {
    mipc_ss_set_call_forward_cnf_tlv_NONE = 0,
    /* err message of Set Call Forward */
    /* type = string */
    MIPC_SS_SET_CALL_FORWARD_CNF_T_ERRMESSAGE               = 0x100,
};

    /* MIPC_MSG.SS_QUERY_CALL_FORWARD_REQ */
enum mipc_ss_query_call_forward_req_tlv_enum {
    mipc_ss_query_call_forward_req_tlv_NONE = 0,
    /* query service class */
    /* type = uint16_t, refer to SS_SERVICE_CLASS */
    MIPC_SS_QUERY_CALL_FORWARD_REQ_T_SERVICE_CLASS          = 0x100,
    /* call forward reason to query */
    /* type = uint8_t, refer to SS_CALL_FORWARD_REASON */
    MIPC_SS_QUERY_CALL_FORWARD_REQ_T_CALL_FORWARD_REASON    = 0x101,
};

    /* MIPC_MSG.SS_QUERY_CALL_FORWARD_CNF */
enum mipc_ss_query_call_forward_cnf_tlv_enum {
    mipc_ss_query_call_forward_cnf_tlv_NONE = 0,
    /* number of call forward */
    /* type = uint8_t */
    MIPC_SS_QUERY_CALL_FORWARD_CNF_T_CALL_FORWARD_COUNT     = 0x100,
    /* list of call forward, in cf cnf struct timer range is 1 - 30, and 0 means invalid */
    /* type = struct_array, refer to ss_call_forward */
    MIPC_SS_QUERY_CALL_FORWARD_CNF_T_CALL_FORWARD_LIST      = 0x8101,
    /* err message of Query Call Forward */
    /* type = string */
    MIPC_SS_QUERY_CALL_FORWARD_CNF_T_ERRMESSAGE             = 0x102,
};

    /* MIPC_MSG.SS_SET_CALL_BARRING_REQ */
enum mipc_ss_set_call_barring_req_tlv_enum {
    mipc_ss_set_call_barring_req_tlv_NONE = 0,
    /* Lock,unlock call barring */
    /* type = uint8_t, refer to SS_CALL_BARRING_LOCK */
    MIPC_SS_SET_CALL_BARRING_REQ_T_LOCK                     = 0x100,
    /* facility for call barring */
    /* type = uint8_t, refer to SS_CALL_BARRING_FAC */
    MIPC_SS_SET_CALL_BARRING_REQ_T_FACILITY                 = 0x101,
    /* the call barring password */
    /* type = string */
    MIPC_SS_SET_CALL_BARRING_REQ_T_PASSWORD                 = 0x8102,
    /* set call barring service class */
    /* type = uint16_t, refer to SS_SERVICE_CLASS */
    MIPC_SS_SET_CALL_BARRING_REQ_T_SERVICE_CLASS            = 0x103,
};

    /* MIPC_MSG.SS_SET_CALL_BARRING_CNF */
enum mipc_ss_set_call_barring_cnf_tlv_enum {
    mipc_ss_set_call_barring_cnf_tlv_NONE = 0,
    /* err message of Set Call Barring */
    /* type = string */
    MIPC_SS_SET_CALL_BARRING_CNF_T_ERRMESSAGE               = 0x100,
};

    /* MIPC_MSG.SS_QUERY_CALL_BARRING_REQ */
enum mipc_ss_query_call_barring_req_tlv_enum {
    mipc_ss_query_call_barring_req_tlv_NONE = 0,
    /* facility for query call barring */
    /* type = uint8_t, refer to SS_CALL_BARRING_FAC */
    MIPC_SS_QUERY_CALL_BARRING_REQ_T_FACILITY               = 0x100,
    /* query service class */
    /* type = uint16_t, refer to SS_SERVICE_CLASS */
    MIPC_SS_QUERY_CALL_BARRING_REQ_T_SERVICE_CLASS          = 0x101,
};

    /* MIPC_MSG.SS_QUERY_CALL_BARRING_CNF */
enum mipc_ss_query_call_barring_cnf_tlv_enum {
    mipc_ss_query_call_barring_cnf_tlv_NONE = 0,
    /* call barring status, active, not active, or service class indication */
    /* type = uint16_t */
    MIPC_SS_QUERY_CALL_BARRING_CNF_T_CALL_BARRING_STATUS    = 0x100,
    /* err message of Query Call Barring */
    /* type = string */
    MIPC_SS_QUERY_CALL_BARRING_CNF_T_ERRMESSAGE             = 0x101,
};

    /* MIPC_MSG.SS_CHANGE_BARRING_PASSWORD_REQ */
enum mipc_ss_change_barring_password_req_tlv_enum {
    mipc_ss_change_barring_password_req_tlv_NONE = 0,
    /* facility for call barring */
    /* type = uint8_t, refer to SS_CALL_BARRING_FAC */
    MIPC_SS_CHANGE_BARRING_PASSWORD_REQ_T_FACILITY          = 0x8100,
    /* old password */
    /* type = string */
    MIPC_SS_CHANGE_BARRING_PASSWORD_REQ_T_OLD_PWD           = 0x8101,
    /* new password */
    /* type = string */
    MIPC_SS_CHANGE_BARRING_PASSWORD_REQ_T_NEW_PWD           = 0x8102,
    /* new password confirmed */
    /* type = string */
    MIPC_SS_CHANGE_BARRING_PASSWORD_REQ_T_NEW_PWD_CONFIRM   = 0x8103,
};

    /* MIPC_MSG.SS_CHANGE_BARRING_PASSWORD_CNF */
enum mipc_ss_change_barring_password_cnf_tlv_enum {
    mipc_ss_change_barring_password_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SS_SET_SUPP_SVC_NOTIFICATION_REQ */
enum mipc_ss_set_supp_svc_notification_req_tlv_enum {
    mipc_ss_set_supp_svc_notification_req_tlv_NONE = 0,
    /* set the +CSSI intermediate result code presentation status to TE. 0 disable, 1 enable */
    /* type = uint8_t */
    MIPC_SS_SET_SUPP_SVC_NOTIFICATION_REQ_T_STATUS_I        = 0x100,
    /* set the +CSSU unsolicited result code presentation status to TE. 0 disable, 1 enable */
    /* type = uint8_t */
    MIPC_SS_SET_SUPP_SVC_NOTIFICATION_REQ_T_STATUS_U        = 0x101,
};

    /* MIPC_MSG.SS_SET_SUPP_SVC_NOTIFICATION_CNF */
enum mipc_ss_set_supp_svc_notification_cnf_tlv_enum {
    mipc_ss_set_supp_svc_notification_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SS_QUERY_CLIP_REQ */
enum mipc_ss_query_clip_req_tlv_enum {
    mipc_ss_query_clip_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SS_QUERY_CLIP_CNF */
enum mipc_ss_query_clip_cnf_tlv_enum {
    mipc_ss_query_clip_cnf_tlv_NONE = 0,
    /* shows the result code presentation status to the TE. 0 disable, 1 enable */
    /* type = uint8_t */
    MIPC_SS_QUERY_CLIP_CNF_T_CODE_STATUS                    = 0x100,
    /* shows the subscriber CLIP service status in the netowrk */
    /* type = uint8_t */
    MIPC_SS_QUERY_CLIP_CNF_T_NW_STATUS                      = 0x101,
    /* err message of query CLIP */
    /* type = string */
    MIPC_SS_QUERY_CLIP_CNF_T_ERRMESSAGE                     = 0x102,
};

    /* MIPC_MSG.SS_SET_CLIP_REQ */
enum mipc_ss_set_clip_req_tlv_enum {
    mipc_ss_set_clip_req_tlv_NONE = 0,
    /* integer type. 0 disable, 1 enable */
    /* type = uint8_t */
    MIPC_SS_SET_CLIP_REQ_T_STATUS                           = 0x100,
};

    /* MIPC_MSG.SS_SET_CLIP_CNF */
enum mipc_ss_set_clip_cnf_tlv_enum {
    mipc_ss_set_clip_cnf_tlv_NONE = 0,
    /* err message of set CLIP */
    /* type = string */
    MIPC_SS_SET_CLIP_CNF_T_ERRMESSAGE                       = 0x100,
};

    /* MIPC_MSG.SS_RUN_GBA_REQ */
enum mipc_ss_run_gba_req_tlv_enum {
    mipc_ss_run_gba_req_tlv_NONE = 0,
    /* a string to indicate GBA key */
    /* type = string */
    MIPC_SS_RUN_GBA_REQ_T_NAF_FQDN                          = 0x100,
    /* a string for GBA protocol */
    /* type = string */
    MIPC_SS_RUN_GBA_REQ_T_NAF_SECURE_PROTOCOL_ID            = 0x101,
    /* to indicate force run GBA or using cache. 0: no need. 1: force run */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_SS_RUN_GBA_REQ_T_FORCE_RUN                         = 0x102,
    /* to indicate network access */
    /* type = uint32_t */
    MIPC_SS_RUN_GBA_REQ_T_NET_ID                            = 0x103,
};

    /* MIPC_MSG.SS_RUN_GBA_CNF */
enum mipc_ss_run_gba_cnf_tlv_enum {
    mipc_ss_run_gba_cnf_tlv_NONE = 0,
    /* GBA key */
    /* type = string */
    MIPC_SS_RUN_GBA_CNF_T_KEY                               = 0x100,
    /* key length */
    /* type = uint8_t */
    MIPC_SS_RUN_GBA_CNF_T_KEY_LEN                           = 0x101,
    /* bit id */
    /* type = string */
    MIPC_SS_RUN_GBA_CNF_T_BIT_ID                            = 0x102,
    /* the lifetime of key */
    /* type = string */
    MIPC_SS_RUN_GBA_CNF_T_KEY_LIFETIME                      = 0x103,
};

    /* MIPC_MSG.SS_GET_COLP_REQ */
enum mipc_ss_get_colp_req_tlv_enum {
    mipc_ss_get_colp_req_tlv_NONE = 0,
};

    /* MIPC_MSG.SS_GET_COLP_CNF */
enum mipc_ss_get_colp_cnf_tlv_enum {
    mipc_ss_get_colp_cnf_tlv_NONE = 0,
    /* disable or enable of COLP */
    /* type = uint8_t */
    MIPC_SS_GET_COLP_CNF_T_COLP_N                           = 0x100,
    /* service status in the network for COLP */
    /* type = uint8_t */
    MIPC_SS_GET_COLP_CNF_T_COLP_M                           = 0x101,
    /* err message of get COLP */
    /* type = string */
    MIPC_SS_GET_COLP_CNF_T_ERRMESSAGE                       = 0x102,
};

    /* MIPC_MSG.SS_SET_COLP_REQ */
enum mipc_ss_set_colp_req_tlv_enum {
    mipc_ss_set_colp_req_tlv_NONE = 0,
    /* disable or enable to set COLP */
    /* type = uint8_t */
    MIPC_SS_SET_COLP_REQ_T_N_VALUE                          = 0x100,
};

    /* MIPC_MSG.SS_SET_COLP_CNF */
enum mipc_ss_set_colp_cnf_tlv_enum {
    mipc_ss_set_colp_cnf_tlv_NONE = 0,
    /* err message of set COLP */
    /* type = string */
    MIPC_SS_SET_COLP_CNF_T_ERRMESSAGE                       = 0x100,
};

    /* MIPC_MSG.SS_GET_COLR_REQ */
enum mipc_ss_get_colr_req_tlv_enum {
    mipc_ss_get_colr_req_tlv_NONE = 0,
};

    /* MIPC_MSG.SS_GET_COLR_CNF */
enum mipc_ss_get_colr_cnf_tlv_enum {
    mipc_ss_get_colr_cnf_tlv_NONE = 0,
    /* status value of COLR */
    /* type = uint8_t */
    MIPC_SS_GET_COLR_CNF_T_STATUS                           = 0x100,
    /* err message of get COLR */
    /* type = string */
    MIPC_SS_GET_COLR_CNF_T_ERRMESSAGE                       = 0x101,
};

    /* MIPC_MSG.SS_SEND_CNAP_REQ */
enum mipc_ss_send_cnap_req_tlv_enum {
    mipc_ss_send_cnap_req_tlv_NONE = 0,
};

    /* MIPC_MSG.SS_SEND_CNAP_CNF */
enum mipc_ss_send_cnap_cnf_tlv_enum {
    mipc_ss_send_cnap_cnf_tlv_NONE = 0,
    /* enable or disable of CNAP status to the TE */
    /* type = uint8_t, refer to SS_CNAP_STATE */
    MIPC_SS_SEND_CNAP_CNF_T_CNAP_N                          = 0x100,
    /* CNAP service status in the network */
    /* type = uint8_t */
    MIPC_SS_SEND_CNAP_CNF_T_CNAP_M                          = 0x101,
};

    /* MIPC_MSG.SS_SET_COLR_REQ */
enum mipc_ss_set_colr_req_tlv_enum {
    mipc_ss_set_colr_req_tlv_NONE = 0,
    /* the value to set COLR */
    /* type = uint8_t */
    MIPC_SS_SET_COLR_REQ_T_N_VALUE                          = 0x100,
};

    /* MIPC_MSG.SS_SET_COLR_CNF */
enum mipc_ss_set_colr_cnf_tlv_enum {
    mipc_ss_set_colr_cnf_tlv_NONE = 0,
    /* err message of get COLP */
    /* type = string */
    MIPC_SS_SET_COLR_CNF_T_ERRMESSAGE                       = 0x100,
};

    /* MIPC_MSG.SS_SETUP_XCAP_USER_AGENT_REQ */
enum mipc_ss_setup_xcap_user_agent_req_tlv_enum {
    mipc_ss_setup_xcap_user_agent_req_tlv_NONE = 0,
    /* the string to setup XCAP USER AGENT */
    /* type = string */
    MIPC_SS_SETUP_XCAP_USER_AGENT_REQ_T_STR                 = 0x100,
};

    /* MIPC_MSG.SS_SETUP_XCAP_USER_AGENT_CNF */
enum mipc_ss_setup_xcap_user_agent_cnf_tlv_enum {
    mipc_ss_setup_xcap_user_agent_cnf_tlv_NONE = 0,
};

    /* MIPC_MSG.SS_SET_XCAP_CFG_REQ */
enum mipc_ss_set_xcap_cfg_req_tlv_enum {
    mipc_ss_set_xcap_cfg_req_tlv_NONE = 0,
    /* the config name of XCAP */
    /* type = string */
    MIPC_SS_SET_XCAP_CFG_REQ_T_CFG_NAME                     = 0x100,
    /* the config value of XCAP */
    /* type = string */
    MIPC_SS_SET_XCAP_CFG_REQ_T_VALUE                        = 0x101,
};

    /* MIPC_MSG.SS_SET_XCAP_CFG_CNF */
enum mipc_ss_set_xcap_cfg_cnf_tlv_enum {
    mipc_ss_set_xcap_cfg_cnf_tlv_NONE = 0,
};

    /* MIPC_MSG.STK_SET_PAC_REQ */
enum mipc_stk_set_pac_req_tlv_enum {
    mipc_stk_set_pac_req_tlv_NONE = 0,
    /* the bitmask, each bit indicates if the host likes to handle/receive a notification for a specific proactive command or not. (size is 32 bytes = 256 bits */
    /* type = byte_array */
    MIPC_STK_SET_PAC_REQ_T_PAC_BITMASK_PTR                  = 0x101,
};

    /* MIPC_MSG.STK_SET_PAC_CNF */
enum mipc_stk_set_pac_cnf_tlv_enum {
    mipc_stk_set_pac_cnf_tlv_NONE = 0,
    /* each byte identifies the current support for a specific proactive command */
    /* type = byte_array */
    MIPC_STK_SET_PAC_CNF_T_PAC_PROFILE                      = 0x100,
};

    /* MIPC_MSG.STK_GET_PAC_REQ */
enum mipc_stk_get_pac_req_tlv_enum {
    mipc_stk_get_pac_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.STK_GET_PAC_CNF */
enum mipc_stk_get_pac_cnf_tlv_enum {
    mipc_stk_get_pac_cnf_tlv_NONE = 0,
    /* each byte identifies the current support for a specific proactive command */
    /* type = byte_array */
    MIPC_STK_GET_PAC_CNF_T_PAC_PROFILE                      = 0x100,
};

    /* MIPC_MSG.STK_SEND_TERMINAL_RESPONSE_REQ */
enum mipc_stk_send_terminal_response_req_tlv_enum {
    mipc_stk_send_terminal_response_req_tlv_NONE = 0,
    /*  length of terminal response */
    /* type = uint32_t */
    MIPC_STK_SEND_TERMINAL_RESPONSE_REQ_T_TR_LEN            = 0x101,
    /* pointer to terminal response */
    /* type = byte_array */
    MIPC_STK_SEND_TERMINAL_RESPONSE_REQ_T_TR_PTR            = 0x102,
};

    /* MIPC_MSG.STK_SEND_TERMINAL_RESPONSE_CNF */
enum mipc_stk_send_terminal_response_cnf_tlv_enum {
    mipc_stk_send_terminal_response_cnf_tlv_NONE = 0,
    /* status words */
    /* type = uint16_t */
    MIPC_STK_SEND_TERMINAL_RESPONSE_CNF_T_STATUS_WORDS      = 0x100,
    /* length of terminal response */
    /* type = uint32_t */
    MIPC_STK_SEND_TERMINAL_RESPONSE_CNF_T_TR_LEN            = 0x101,
    /* pointer to terminal response */
    /* type = byte_array */
    MIPC_STK_SEND_TERMINAL_RESPONSE_CNF_T_TR_PTR            = 0x102,
};

    /* MIPC_MSG.STK_SEND_ENVELOPE_REQ */
enum mipc_stk_send_envelope_req_tlv_enum {
    mipc_stk_send_envelope_req_tlv_NONE = 0,
    /* length of envelop */
    /* type = uint32_t */
    MIPC_STK_SEND_ENVELOPE_REQ_T_ENVELOPE_LEN               = 0x101,
    /* pointer to envelop */
    /* type = byte_array */
    MIPC_STK_SEND_ENVELOPE_REQ_T_ENVELOPE_PTR               = 0x102,
};

    /* MIPC_MSG.STK_SEND_ENVELOPE_CNF */
enum mipc_stk_send_envelope_cnf_tlv_enum {
    mipc_stk_send_envelope_cnf_tlv_NONE = 0,
    /* Its value is (sw1 << 8) | sw2. You can get sw1 and sw2 from it */
    /* type = uint16_t */
    MIPC_STK_SEND_ENVELOPE_CNF_T_STATUS_WORDS               = 0x100,
    /* hex string of the whole envelope response(BER-TLV) given by UICC */
    /* type = string */
    MIPC_STK_SEND_ENVELOPE_CNF_T_ENVELOPE_RESPONSE          = 0x101,
};

    /* MIPC_MSG.STK_GET_ENVELOPE_INFO_REQ */
enum mipc_stk_get_envelope_info_req_tlv_enum {
    mipc_stk_get_envelope_info_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.STK_GET_ENVELOPE_INFO_CNF */
enum mipc_stk_get_envelope_info_cnf_tlv_enum {
    mipc_stk_get_envelope_info_cnf_tlv_NONE = 0,
    /* the bit mask of envelope value */
    /* type = byte_array */
    MIPC_STK_GET_ENVELOPE_INFO_CNF_T_ENVELOPE_BITMASK       = 0x100,
};

    /* MIPC_MSG.STK_HANDLE_CALL_SETUP_FROM_SIM_REQ */
enum mipc_stk_handle_call_setup_from_sim_req_tlv_enum {
    mipc_stk_handle_call_setup_from_sim_req_tlv_NONE = 0,
    /* integer, example: 0, 1, 32, 33 */
    /* type = uint8_t */
    MIPC_STK_HANDLE_CALL_SETUP_FROM_SIM_REQ_T_DATA          = 0x100,
};

    /* MIPC_MSG.STK_HANDLE_CALL_SETUP_FROM_SIM_CNF */
enum mipc_stk_handle_call_setup_from_sim_cnf_tlv_enum {
    mipc_stk_handle_call_setup_from_sim_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.STK_SEND_BIPCONF_REQ */
enum mipc_stk_send_bipconf_req_tlv_enum {
    mipc_stk_send_bipconf_req_tlv_NONE = 0,
    /* send bipconf req cmd number */
    /* type = uint32_t */
    MIPC_STK_SEND_BIPCONF_REQ_T_CMD_NUM                     = 0x100,
    /* send bipconf result */
    /* type = uint32_t */
    MIPC_STK_SEND_BIPCONF_REQ_T_RESULT                      = 0x101,
};

    /* MIPC_MSG.STK_SEND_BIPCONF_CNF */
enum mipc_stk_send_bipconf_cnf_tlv_enum {
    mipc_stk_send_bipconf_cnf_tlv_NONE = 0,
};

    /* MIPC_MSG.CALL_DIAL_REQ */
enum mipc_call_dial_req_tlv_enum {
    mipc_call_dial_req_tlv_NONE = 0,
    /* this field is digits number when DIAL_ADDRESS_TYPE=MIPC_CALL_DIAL_ADDRESS_TYPE_NONE or MIPC_CALL_DIAL_ADDRESS_TYPE_NUMBER;this field is URI when DIAL_ADDRESS_TYPE=MIPC_CALL_DIAL_ADDRESS_TYPE_SIP_URI */
    /* type = string */
    MIPC_CALL_DIAL_REQ_T_DIAL_ADDRESS                       = 0x8100,
    /* the type of DIAL_ADDRESS */
    /* type = uint32_t, refer to CALL_DIAL_ADDRESS_TYPE */
    MIPC_CALL_DIAL_REQ_T_DIAL_ADDRESS_TYPE                  = 0x101,
    /* the call type. MIPC_CALL_DIAL_TYPE_RTT don't support currently */
    /* type = uint32_t, refer to CALL_DIAL_TYPE */
    MIPC_CALL_DIAL_REQ_T_TYPE                               = 0x102,
    /* the call domain */
    /* type = uint32_t, refer to CALL_DIAL_DOMAIN */
    MIPC_CALL_DIAL_REQ_T_DOMAIN                             = 0x103,
    /* only support AUTO, CS_ONLY, 3GPP2_ONLY */
    /* type = uint32_t, refer to CALL_DIAL_DOMAIN */
    MIPC_CALL_DIAL_REQ_T_ECC_RETRY_DOMAIN                   = 0x104,
    /* A bitmap indicating the Emergency Service Category Value according to 3GPP TS 24.008 */
    /* type = uint16_t */
    MIPC_CALL_DIAL_REQ_T_ECC_CATEGORY                       = 0x105,
    /* Requests calling line identification restriction (once) */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_CALL_DIAL_REQ_T_CLIR                               = 0x106,
    /* when set ecc test mode, it's necessary */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_CALL_DIAL_REQ_T_IS_ECC_TESTING                     = 0x107,
};

    /* MIPC_MSG.CALL_DIAL_CNF */
enum mipc_call_dial_cnf_tlv_enum {
    mipc_call_dial_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.CALL_SS_REQ */
enum mipc_call_ss_req_tlv_enum {
    mipc_call_ss_req_tlv_NONE = 0,
    /* the action of call-related supplementary services */
    /* type = uint32_t, refer to CALL_SS_ACTION */
    MIPC_CALL_SS_REQ_T_ACTION                               = 0x100,
    /* this field is only necessary when action=MIPC_CALL_SS_ACTION_HOLD_CALL or MIPC_CALL_SS_ACTION_RESUME_CALL */
    /* type = uint32_t */
    MIPC_CALL_SS_REQ_T_CALLID                               = 0x101,
    /* this field is only necessary when action=MIPC_CONST.CALL_SS_ACTION_EXPLICIT_CALL_AND_TRANSFER */
    /* type = uint8_t, refer to CALL_ECT_TYPE */
    MIPC_CALL_SS_REQ_T_ECT_TYPE                             = 0x102,
    /* this field is only necessary when action=MIPC_CONST.CALL_SS_ACTION_EXPLICIT_CALL_AND_TRANSFER */
    /* type = string */
    MIPC_CALL_SS_REQ_T_ECT_NUMBER                           = 0x8103,
};

    /* MIPC_MSG.CALL_SS_CNF */
enum mipc_call_ss_cnf_tlv_enum {
    mipc_call_ss_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.CALL_HANGUP_REQ */
enum mipc_call_hangup_req_tlv_enum {
    mipc_call_hangup_req_tlv_NONE = 0,
    /* the mode of hangup call */
    /* type = uint32_t, refer to CALL_HANGUP_MODE */
    MIPC_CALL_HANGUP_REQ_T_MODE                             = 0x100,
    /* this field is only necessary when mode=MIPC_CALL_HANGUP_MODE_HANGUP or MIPC_CALL_HANGUP_MODE_FORCE_HANGUP */
    /* type = uint32_t */
    MIPC_CALL_HANGUP_REQ_T_CALLID                           = 0x101,
    /* this field is only necessary when mode=MIPC_CALL_HANGUP_MODE_HANGUP */
    /* type = uint32_t, refer to CALL_HANGUP_CAUSE */
    MIPC_CALL_HANGUP_REQ_T_CAUSE                            = 0x102,
};

    /* MIPC_MSG.CALL_HANGUP_CNF */
enum mipc_call_hangup_cnf_tlv_enum {
    mipc_call_hangup_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.CALL_ANSWER_REQ */
enum mipc_call_answer_req_tlv_enum {
    mipc_call_answer_req_tlv_NONE = 0,
    /* the mode of answer call */
    /* type = uint32_t, refer to CALL_ANSWER_MODE */
    MIPC_CALL_ANSWER_REQ_T_MODE                             = 0x100,
    /* this field is only necessary when mode=MIPC_CALL_ANSWER_MODE_AUDIO_CALL, MIPC_CALL_ANSWER_MODE_Rx_VIDEO_CALL or MIPC_CALL_ANSWER_MODE_Tx_VIDEO_CALL */
    /* type = uint32_t */
    MIPC_CALL_ANSWER_REQ_T_CALLID                           = 0x101,
};

    /* MIPC_MSG.CALL_ANSWER_CNF */
enum mipc_call_answer_cnf_tlv_enum {
    mipc_call_answer_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.CALL_GET_CALL_STATUS_REQ */
enum mipc_call_get_call_status_req_tlv_enum {
    mipc_call_get_call_status_req_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_CALL_GET_CALL_STATUS_REQ_T_CALLID                  = 0x100,
};

    /* MIPC_MSG.CALL_GET_CALL_STATUS_CNF */
enum mipc_call_get_call_status_cnf_tlv_enum {
    mipc_call_get_call_status_cnf_tlv_NONE = 0,
    /* the total number of current protocol call */
    /* type = uint32_t */
    MIPC_CALL_GET_CALL_STATUS_CNF_T_COUNT                   = 0x100,
    /* the call id of current protocol call */
    /* type = uint32_t */
    MIPC_CALL_GET_CALL_STATUS_CNF_T_CALLID                  = 0x10B,
    /* the direction of current protocol call */
    /* type = uint32_t, refer to CALL_DIRECTION */
    MIPC_CALL_GET_CALL_STATUS_CNF_T_DIRECTION               = 0x10C,
    /* the mode of current protocol call */
    /* type = uint32_t, refer to CALL_MODE */
    MIPC_CALL_GET_CALL_STATUS_CNF_T_MODE                    = 0x10D,
    /* the call clcc state of current protocol call */
    /* type = uint32_t, refer to CALL_CLCC_STATE */
    MIPC_CALL_GET_CALL_STATUS_CNF_T_CALL_CLCC_STATE         = 0x10E,
    /* the number type of current protocol call */
    /* type = uint32_t, refer to CALL_DIAL_ADDRESS_TYPE */
    MIPC_CALL_GET_CALL_STATUS_CNF_T_NUMBER_TYPE             = 0x10F,
    /* type of address (refer TS 24.008 [8] subclause 10.5.4.7) */
    /* type = uint32_t */
    MIPC_CALL_GET_CALL_STATUS_CNF_T_TON                     = 0x110,
    /* the number of current protocol call */
    /* type = string */
    MIPC_CALL_GET_CALL_STATUS_CNF_T_NUMBER                  = 0x8111,
    /* the rat of current protocol call */
    /* type = uint32_t, refer to CALL_RAT */
    MIPC_CALL_GET_CALL_STATUS_CNF_T_RAT                     = 0x112,
    /* the type of current protocol call */
    /* type = bitmap, refer to CALL_TYPE */
    MIPC_CALL_GET_CALL_STATUS_CNF_T_TYPE                    = 0x113,
    /* the detail info of current protocol call */
    /* type = struct, refer to call_detail_info */
    MIPC_CALL_GET_CALL_STATUS_CNF_T_DETAIL_INFO             = 0x8114,
    /* the video capability of current protocol call */
    /* type = struct, refer to call_video_cap */
    MIPC_CALL_GET_CALL_STATUS_CNF_T_VIDEO_CAP               = 0x115,
};

    /* MIPC_MSG.CALL_CONFERENCE_REQ */
enum mipc_call_conference_req_tlv_enum {
    mipc_call_conference_req_tlv_NONE = 0,
    /* the conference call id. this file is only used when ACTION=MIPC_CALL_CONF_ACTION_ADD_PARTICIPANT or MIPC_CALL_CONF_ACTION_REMOVE_PARTICIPANT */
    /* type = uint32_t */
    MIPC_CALL_CONFERENCE_REQ_T_CONF_CALLID                  = 0x100,
    /* the conference action */
    /* type = uint32_t, refer to CALL_CONF_ACTION */
    MIPC_CALL_CONFERENCE_REQ_T_ACTION                       = 0x101,
    /* the participant number.this file is only used when ACTION=MIPC_CALL_CONF_ACTION_ADD_PARTICIPANT, MIPC_CALL_CONF_ACTION_REMOVE_PARTICIPANT or MIPC_CALL_CONF_ACTION_CDMA_FLASH */
    /* type = string */
    MIPC_CALL_CONFERENCE_REQ_T_NUMBER                       = 0x8102,
    /* the target call id for action.this file is only used when ACTION=MIPC_CALL_CONF_ACTION_ADD_PARTICIPANT or MIPC_CALL_CONF_ACTION_SPLIT */
    /* type = uint32_t */
    MIPC_CALL_CONFERENCE_REQ_T_TARGET_CALLID                = 0x103,
};

    /* MIPC_MSG.CALL_CONFERENCE_CNF */
enum mipc_call_conference_cnf_tlv_enum {
    mipc_call_conference_cnf_tlv_NONE = 0,
    /* error cause */
    /* type = uint16_t, refer to CALL_REJECT_CAUSE */
    MIPC_CALL_CONFERENCE_CNF_T_CAUSE                        = 0x100,
};

    /* MIPC_MSG.CALL_GET_CONFERENCE_INFO_REQ */
enum mipc_call_get_conference_info_req_tlv_enum {
    mipc_call_get_conference_info_req_tlv_NONE = 0,
    /* the conference call id */
    /* type = uint32_t */
    MIPC_CALL_GET_CONFERENCE_INFO_REQ_T_CONF_CALLID         = 0x100,
};

    /* MIPC_MSG.CALL_GET_CONFERENCE_INFO_CNF */
enum mipc_call_get_conference_info_cnf_tlv_enum {
    mipc_call_get_conference_info_cnf_tlv_NONE = 0,
    /* the number of conference participant */
    /* type = uint32_t */
    MIPC_CALL_GET_CONFERENCE_INFO_CNF_T_COUNT               = 0x100,
    /* the direction of conference participant */
    /* type = uint32_t, refer to CALL_DIRECTION */
    MIPC_CALL_GET_CONFERENCE_INFO_CNF_T_DIRECTION           = 0x10B,
    /* call number */
    /* type = string */
    MIPC_CALL_GET_CONFERENCE_INFO_CNF_T_PARTICIPANT_NUMBER  = 0x810C,
    /* the name of conference participant */
    /* type = string */
    MIPC_CALL_GET_CONFERENCE_INFO_CNF_T_PARTICIPANT_NAME    = 0x810D,
    /* the status of conference participant */
    /* type = uint32_t, refer to CONF_PARTICIPANT_STATUS */
    MIPC_CALL_GET_CONFERENCE_INFO_CNF_T_PARTICIPANT_STATUS  = 0x10E,
    /* call user entity string */
    /* type = string */
    MIPC_CALL_GET_CONFERENCE_INFO_CNF_T_PARTICIPANT_USER_ENTITY = 0x10F,
    /* call endpoint entity string */
    /* type = string */
    MIPC_CALL_GET_CONFERENCE_INFO_CNF_T_PARTICIPANT_ENDPOINT_ENTITY = 0x110,
};

    /* MIPC_MSG.CALL_GET_FINISH_REASON_REQ */
enum mipc_call_get_finish_reason_req_tlv_enum {
    mipc_call_get_finish_reason_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.CALL_GET_FINISH_REASON_CNF */
enum mipc_call_get_finish_reason_cnf_tlv_enum {
    mipc_call_get_finish_reason_cnf_tlv_NONE = 0,
    /* the value listed in GSM 04.08 annex H */
    /* type = uint32_t */
    MIPC_CALL_GET_FINISH_REASON_CNF_T_REASON                = 0x100,
    /* the describes reason value */
    /* type = string */
    MIPC_CALL_GET_FINISH_REASON_CNF_T_REASON_STR            = 0x101,
};

    /* MIPC_MSG.CALL_DTMF_REQ */
enum mipc_call_dtmf_req_tlv_enum {
    mipc_call_dtmf_req_tlv_NONE = 0,
    /* DTMF START or STOP */
    /* type = uint32_t, refer to DTMF_MODE */
    MIPC_CALL_DTMF_REQ_T_MODE                               = 0x100,
    /* this field is only necessary when mode=START or SINGLE_TONE or BURST_TONE */
    /* type = string */
    MIPC_CALL_DTMF_REQ_T_DIGIT                              = 0x8101,
};

    /* MIPC_MSG.CALL_DTMF_CNF */
enum mipc_call_dtmf_cnf_tlv_enum {
    mipc_call_dtmf_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.CALL_GET_ECC_LIST_REQ */
enum mipc_call_get_ecc_list_req_tlv_enum {
    mipc_call_get_ecc_list_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.CALL_GET_ECC_LIST_CNF */
enum mipc_call_get_ecc_list_cnf_tlv_enum {
    mipc_call_get_ecc_list_cnf_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_CALL_GET_ECC_LIST_CNF_T_INFO_COUNT                 = 0x100,
    /* type = struct_array, refer to ecc_info */
    MIPC_CALL_GET_ECC_LIST_CNF_T_INFO_LIST                  = 0x101,
};

    /* MIPC_MSG.CALL_SET_ECC_LIST_REQ */
enum mipc_call_set_ecc_list_req_tlv_enum {
    mipc_call_set_ecc_list_req_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_CALL_SET_ECC_LIST_REQ_T_INFO_COUNT                 = 0x100,
    /* when set ecc list, MAX_CALL_ECC_LIST_RECORD_NUM is 16 */
    /* type = struct_array, refer to ecc_info */
    MIPC_CALL_SET_ECC_LIST_REQ_T_INFO_LIST                  = 0x101,
};

    /* MIPC_MSG.CALL_SET_ECC_LIST_CNF */
enum mipc_call_set_ecc_list_cnf_tlv_enum {
    mipc_call_set_ecc_list_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.CALL_SET_FLIGHT_MODE_ECC_SESSION_REQ */
enum mipc_call_set_flight_mode_ecc_session_req_tlv_enum {
    mipc_call_set_flight_mode_ecc_session_req_tlv_NONE = 0,
    /* 0 means normal mode, 1 means flight mode */
    /* type = uint8_t */
    MIPC_CALL_SET_FLIGHT_MODE_ECC_SESSION_REQ_T_IS_FLIGHT_MODE = 0x100,
};

    /* MIPC_MSG.CALL_SET_FLIGHT_MODE_ECC_SESSION_CNF */
enum mipc_call_set_flight_mode_ecc_session_cnf_tlv_enum {
    mipc_call_set_flight_mode_ecc_session_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.CALL_SET_EXIT_ECBM_MODE_REQ */
enum mipc_call_set_exit_ecbm_mode_req_tlv_enum {
    mipc_call_set_exit_ecbm_mode_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.CALL_SET_EXIT_ECBM_MODE_CNF */
enum mipc_call_set_exit_ecbm_mode_cnf_tlv_enum {
    mipc_call_set_exit_ecbm_mode_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.CALL_IVS_ONEKEY_ECALL_REQ */
enum mipc_call_ivs_onekey_ecall_req_tlv_enum {
    mipc_call_ivs_onekey_ecall_req_tlv_NONE = 0,
    /* type = uint8_t, refer to ECALL_TYPE */
    MIPC_CALL_IVS_ONEKEY_ECALL_REQ_T_TYPE                   = 0x100,
    /* only support binary now */
    /* type = uint8_t, refer to ECALL_MSD_FORMAT */
    MIPC_CALL_IVS_ONEKEY_ECALL_REQ_T_MSD_FORMAT             = 0x101,
    /* type = byte_array */
    MIPC_CALL_IVS_ONEKEY_ECALL_REQ_T_MSD                    = 0x102,
};

    /* MIPC_MSG.CALL_IVS_ONEKEY_ECALL_CNF */
enum mipc_call_ivs_onekey_ecall_cnf_tlv_enum {
    mipc_call_ivs_onekey_ecall_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.CALL_SET_SIP_HEADER_REQ */
enum mipc_call_set_sip_header_req_tlv_enum {
    mipc_call_set_sip_header_req_tlv_NONE = 0,
    /* total number of additinal info */
    /* type = uint32_t */
    MIPC_CALL_SET_SIP_HEADER_REQ_T_TOTAL                    = 0x100,
    /* index of current additional info */
    /* type = uint32_t */
    MIPC_CALL_SET_SIP_HEADER_REQ_T_INDEX                    = 0x101,
    /* number of key or key/value pair  */
    /* type = uint32_t */
    MIPC_CALL_SET_SIP_HEADER_REQ_T_COUNT                    = 0x102,
    /* when the strlen of SIP headers more than MAX_CALL_SIP_HEADER_VALUE_PAIR_LEN, please use index slice */
    /* type = string */
    MIPC_CALL_SET_SIP_HEADER_REQ_T_VALUE_PAIR               = 0x8103,
};

    /* MIPC_MSG.CALL_SET_SIP_HEADER_CNF */
enum mipc_call_set_sip_header_cnf_tlv_enum {
    mipc_call_set_sip_header_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.CALL_ENABLE_IMS_SIP_HEADER_REPORT_REQ */
enum mipc_call_enable_ims_sip_header_report_req_tlv_enum {
    mipc_call_enable_ims_sip_header_report_req_tlv_NONE = 0,
    /* the call id of query ims sip header */
    /* type = uint32_t */
    MIPC_CALL_ENABLE_IMS_SIP_HEADER_REPORT_REQ_T_CALL_ID    = 0x100,
    /* wanted type of header,ex.13: CALL-ID header */
    /* type = uint32_t */
    MIPC_CALL_ENABLE_IMS_SIP_HEADER_REPORT_REQ_T_HEADER_TYPE = 0x101,
};

    /* MIPC_MSG.CALL_ENABLE_IMS_SIP_HEADER_REPORT_CNF */
enum mipc_call_enable_ims_sip_header_report_cnf_tlv_enum {
    mipc_call_enable_ims_sip_header_report_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.CALL_SET_CALL_ADDITIONAL_INFO_REQ */
enum mipc_call_set_call_additional_info_req_tlv_enum {
    mipc_call_set_call_additional_info_req_tlv_NONE = 0,
    /* The call mode will be applied till next command to change call_mode. */
    /* type = uint8_t, refer to CALL_ADDITIONAL_INFO_MODE */
    MIPC_CALL_SET_CALL_ADDITIONAL_INFO_REQ_T_MODE           = 0x100,
    /* the type of IMS call additional information */
    /* type = uint8_t, refer to CALL_ADDITIONAL_INFO_TYPE */
    MIPC_CALL_SET_CALL_ADDITIONAL_INFO_REQ_T_TYPE           = 0x101,
    /* total number of additinal info */
    /* type = uint32_t */
    MIPC_CALL_SET_CALL_ADDITIONAL_INFO_REQ_T_TOTAL          = 0x102,
    /* index of current additional info */
    /* type = uint32_t */
    MIPC_CALL_SET_CALL_ADDITIONAL_INFO_REQ_T_INDEX          = 0x103,
    /* number of key or key/value pair in additional info */
    /* type = uint32_t */
    MIPC_CALL_SET_CALL_ADDITIONAL_INFO_REQ_T_COUNT          = 0x104,
    /* IMS call additional information */
    /* type = string */
    MIPC_CALL_SET_CALL_ADDITIONAL_INFO_REQ_T_ADDITIONAL_INFO = 0x8105,
};

    /* MIPC_MSG.CALL_SET_CALL_ADDITIONAL_INFO_CNF */
enum mipc_call_set_call_additional_info_cnf_tlv_enum {
    mipc_call_set_call_additional_info_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.CALL_PEER_RTT_MODIFY_REQ */
enum mipc_call_peer_rtt_modify_req_tlv_enum {
    mipc_call_peer_rtt_modify_req_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_CALL_PEER_RTT_MODIFY_REQ_T_CALL_ID                 = 0x100,
    /* type = uint8_t, refer to CALL_PEER_RTT_MODIFY_RESULT */
    MIPC_CALL_PEER_RTT_MODIFY_REQ_T_RESULT                  = 0x101,
};

    /* MIPC_MSG.CALL_PEER_RTT_MODIFY_CNF */
enum mipc_call_peer_rtt_modify_cnf_tlv_enum {
    mipc_call_peer_rtt_modify_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.CALL_LOCAL_RTT_MODIFY_REQ */
enum mipc_call_local_rtt_modify_req_tlv_enum {
    mipc_call_local_rtt_modify_req_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_CALL_LOCAL_RTT_MODIFY_REQ_T_CALL_ID                = 0x100,
    /* type = uint8_t, refer to CALL_LOCAL_RTT_MODIFY_OP */
    MIPC_CALL_LOCAL_RTT_MODIFY_REQ_T_OP                     = 0x101,
};

    /* MIPC_MSG.CALL_LOCAL_RTT_MODIFY_CNF */
enum mipc_call_local_rtt_modify_cnf_tlv_enum {
    mipc_call_local_rtt_modify_cnf_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_CALL_LOCAL_RTT_MODIFY_CNF_T_CALL_ID = 0x100,
    /* type = uint8_t */
    MIPC_CALL_LOCAL_RTT_MODIFY_CNF_T_RESULT = 0x101,
};

    /* MIPC_MSG.CALL_RTT_TEXT_REQ */
enum mipc_call_rtt_text_req_tlv_enum {
    mipc_call_rtt_text_req_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_CALL_RTT_TEXT_REQ_T_CALL_ID                        = 0x100,
    /* type = uint32_t */
    MIPC_CALL_RTT_TEXT_REQ_T_LEN                            = 0x101,
    /* type = string */
    MIPC_CALL_RTT_TEXT_REQ_T_TEXT                           = 0x102,
};

    /* MIPC_MSG.CALL_RTT_TEXT_CNF */
enum mipc_call_rtt_text_cnf_tlv_enum {
    mipc_call_rtt_text_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.CALL_RTT_MODE_REQ */
enum mipc_call_rtt_mode_req_tlv_enum {
    mipc_call_rtt_mode_req_tlv_NONE = 0,
    /* type = uint8_t, refer to CALL_RTT_MODE_OP */
    MIPC_CALL_RTT_MODE_REQ_T_OP                             = 0x100,
};

    /* MIPC_MSG.CALL_RTT_MODE_CNF */
enum mipc_call_rtt_mode_cnf_tlv_enum {
    mipc_call_rtt_mode_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.CALL_RTT_AUDIO_REQ */
enum mipc_call_rtt_audio_req_tlv_enum {
    mipc_call_rtt_audio_req_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_CALL_RTT_AUDIO_REQ_T_CALL_ID                       = 0x100,
    /* 0: disable audio indication; 1:enable audio indication */
    /* type = uint8_t */
    MIPC_CALL_RTT_AUDIO_REQ_T_ENABLE                        = 0x101,
};

    /* MIPC_MSG.CALL_RTT_AUDIO_CNF */
enum mipc_call_rtt_audio_cnf_tlv_enum {
    mipc_call_rtt_audio_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.CALL_SET_RCS_STATE_AND_FEATURE_REQ */
enum mipc_call_set_rcs_state_and_feature_req_tlv_enum {
    mipc_call_set_rcs_state_and_feature_req_tlv_NONE = 0,
    /* type = uint32_t, refer to CALL_RCS_STATE */
    MIPC_CALL_SET_RCS_STATE_AND_FEATURE_REQ_T_STATE         = 0x100,
    /* A bit mask indicate the corresponding RCS feature supported or not. */
    /* type = uint32_t, refer to CALL_RCS_FEATURE */
    MIPC_CALL_SET_RCS_STATE_AND_FEATURE_REQ_T_FEATURE       = 0x101,
};

    /* MIPC_MSG.CALL_SET_RCS_STATE_AND_FEATURE_CNF */
enum mipc_call_set_rcs_state_and_feature_cnf_tlv_enum {
    mipc_call_set_rcs_state_and_feature_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.CALL_UPDATE_RCS_SESSION_INFO_REQ */
enum mipc_call_update_rcs_session_info_req_tlv_enum {
    mipc_call_update_rcs_session_info_req_tlv_NONE = 0,
    /* 0:disable;1:enable. */
    /* type = uint8_t */
    MIPC_CALL_UPDATE_RCS_SESSION_INFO_REQ_T_STATUS          = 0x100,
};

    /* MIPC_MSG.CALL_UPDATE_RCS_SESSION_INFO_CNF */
enum mipc_call_update_rcs_session_info_cnf_tlv_enum {
    mipc_call_update_rcs_session_info_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.CALL_GET_VOICE_DOMAIN_PREFERENCE_REQ */
enum mipc_call_get_voice_domain_preference_req_tlv_enum {
    mipc_call_get_voice_domain_preference_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.CALL_GET_VOICE_DOMAIN_PREFERENCE_CNF */
enum mipc_call_get_voice_domain_preference_cnf_tlv_enum {
    mipc_call_get_voice_domain_preference_cnf_tlv_NONE = 0,
    /* indicates the voice domain preference of the UE. */
    /* type = uint32_t, refer to CALL_VOICE_DOMAIN */
    MIPC_CALL_GET_VOICE_DOMAIN_PREFERENCE_CNF_T_SETTING     = 0x100,
};

    /* MIPC_MSG.CALL_PULL_REQ */
enum mipc_call_pull_req_tlv_enum {
    mipc_call_pull_req_tlv_NONE = 0,
    /* target URI */
    /* type = string */
    MIPC_CALL_PULL_REQ_T_URI                                = 0x8100,
    /* the call mode of pull */
    /* type = uint8_t, refer to CALL_PULL_TYPE */
    MIPC_CALL_PULL_REQ_T_TYPE                               = 0x101,
};

    /* MIPC_MSG.CALL_PULL_CNF */
enum mipc_call_pull_cnf_tlv_enum {
    mipc_call_pull_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.CALL_GET_TTY_MODE_REQ */
enum mipc_call_get_tty_mode_req_tlv_enum {
    mipc_call_get_tty_mode_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.CALL_GET_TTY_MODE_CNF */
enum mipc_call_get_tty_mode_cnf_tlv_enum {
    mipc_call_get_tty_mode_cnf_tlv_NONE = 0,
    /* type = uint8_t, refer to CALL_TTY_MODE */
    MIPC_CALL_GET_TTY_MODE_CNF_T_MODE                       = 0x100,
};

    /* MIPC_MSG.CALL_SET_IMS_CALL_MODE_REQ */
enum mipc_call_set_ims_call_mode_req_tlv_enum {
    mipc_call_set_ims_call_mode_req_tlv_NONE = 0,
    /* Call related Client API mode or original IMS mode */
    /* type = uint8_t, refer to CALL_IMS_CALL_MODE */
    MIPC_CALL_SET_IMS_CALL_MODE_REQ_T_OP                    = 0x100,
};

    /* MIPC_MSG.CALL_SET_IMS_CALL_MODE_CNF */
enum mipc_call_set_ims_call_mode_cnf_tlv_enum {
    mipc_call_set_ims_call_mode_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.CALL_SET_TTY_MODE_REQ */
enum mipc_call_set_tty_mode_req_tlv_enum {
    mipc_call_set_tty_mode_req_tlv_NONE = 0,
    /* type = uint8_t, refer to CALL_TTY_MODE */
    MIPC_CALL_SET_TTY_MODE_REQ_T_MODE                       = 0x100,
};

    /* MIPC_MSG.CALL_SET_TTY_MODE_CNF */
enum mipc_call_set_tty_mode_cnf_tlv_enum {
    mipc_call_set_tty_mode_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.CALL_SET_VOICE_DOMAIN_PREFERENCE_REQ */
enum mipc_call_set_voice_domain_preference_req_tlv_enum {
    mipc_call_set_voice_domain_preference_req_tlv_NONE = 0,
    /* the voice domain preference of the UE. The default value is manufacturer specific. */
    /* type = uint32_t, refer to CALL_VOICE_DOMAIN */
    MIPC_CALL_SET_VOICE_DOMAIN_PREFERENCE_REQ_T_SETTING     = 0x100,
};

    /* MIPC_MSG.CALL_SET_VOICE_DOMAIN_PREFERENCE_CNF */
enum mipc_call_set_voice_domain_preference_cnf_tlv_enum {
    mipc_call_set_voice_domain_preference_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.CALL_CONFERENCE_DIAL_REQ */
enum mipc_call_conference_dial_req_tlv_enum {
    mipc_call_conference_dial_req_tlv_NONE = 0,
    /* the type of conference call */
    /* type = uint32_t, refer to CALL_CONFERENCE_DIAL_TYPE */
    MIPC_CALL_CONFERENCE_DIAL_REQ_T_TYPE                    = 0x100,
    /* Requests calling line identification restriction (once) */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_CALL_CONFERENCE_DIAL_REQ_T_CLIR                    = 0x101,
    /* the count of dial_address */
    /* type = uint32_t */
    MIPC_CALL_CONFERENCE_DIAL_REQ_T_COUNT                   = 0x102,
    /* telephone number or SIP URI */
    /* type = string */
    MIPC_CALL_CONFERENCE_DIAL_REQ_T_DIAL_ADDRESS            = 0x8103,
};

    /* MIPC_MSG.CALL_CONFERENCE_DIAL_CNF */
enum mipc_call_conference_dial_cnf_tlv_enum {
    mipc_call_conference_dial_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.CALL_SET_GWSD_MODE_REQ */
enum mipc_call_set_gwsd_mode_req_tlv_enum {
    mipc_call_set_gwsd_mode_req_tlv_NONE = 0,
    /* type = uint32_t, refer to SET_GWSD_MODE_ACTION */
    MIPC_CALL_SET_GWSD_MODE_REQ_T_ACTION                    = 0x101,
    /* the mode of GWSD */
    /* type = uint32_t */
    MIPC_CALL_SET_GWSD_MODE_REQ_T_MODE                      = 0x102,
    /* the keepalive mode */
    /* type = uint32_t */
    MIPC_CALL_SET_GWSD_MODE_REQ_T_KA_MODE                   = 0x103,
    /* the keepalive cycle */
    /* type = string */
    MIPC_CALL_SET_GWSD_MODE_REQ_T_KA_CYCLE                  = 0x104,
};

    /* MIPC_MSG.CALL_SET_GWSD_MODE_CNF */
enum mipc_call_set_gwsd_mode_cnf_tlv_enum {
    mipc_call_set_gwsd_mode_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.CALL_APPROVE_CSFB_REQ */
enum mipc_call_approve_csfb_req_tlv_enum {
    mipc_call_approve_csfb_req_tlv_NONE = 0,
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_CALL_APPROVE_CSFB_REQ_T_IS_APPROVE                 = 0x100,
};

    /* MIPC_MSG.CALL_APPROVE_CSFB_CNF */
enum mipc_call_approve_csfb_cnf_tlv_enum {
    mipc_call_approve_csfb_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.CALL_SET_GWSD_CALL_VALID_REQ */
enum mipc_call_set_gwsd_call_valid_req_tlv_enum {
    mipc_call_set_gwsd_call_valid_req_tlv_NONE = 0,
    /* the call valid timer */
    /* type = uint32_t */
    MIPC_CALL_SET_GWSD_CALL_VALID_REQ_T_TIMER               = 0x101,
};

    /* MIPC_MSG.CALL_SET_GWSD_CALL_VALID_CNF */
enum mipc_call_set_gwsd_call_valid_cnf_tlv_enum {
    mipc_call_set_gwsd_call_valid_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.CALL_SET_GWSD_IGNORE_CALL_INTERVAL_REQ */
enum mipc_call_set_gwsd_ignore_call_interval_req_tlv_enum {
    mipc_call_set_gwsd_ignore_call_interval_req_tlv_NONE = 0,
    /* the ignore call interval */
    /* type = uint32_t */
    MIPC_CALL_SET_GWSD_IGNORE_CALL_INTERVAL_REQ_T_INTERVAL  = 0x101,
};

    /* MIPC_MSG.CALL_SET_GWSD_IGNORE_CALL_INTERVAL_CNF */
enum mipc_call_set_gwsd_ignore_call_interval_cnf_tlv_enum {
    mipc_call_set_gwsd_ignore_call_interval_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.CALL_SET_GWSD_KA_PDCP_REQ */
enum mipc_call_set_gwsd_ka_pdcp_req_tlv_enum {
    mipc_call_set_gwsd_ka_pdcp_req_tlv_NONE = 0,
    /* the keep alive PDCP */
    /* type = string */
    MIPC_CALL_SET_GWSD_KA_PDCP_REQ_T_PDATA                  = 0x101,
};

    /* MIPC_MSG.CALL_SET_GWSD_KA_PDCP_CNF */
enum mipc_call_set_gwsd_ka_pdcp_cnf_tlv_enum {
    mipc_call_set_gwsd_ka_pdcp_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.CALL_SET_GWSD_KA_IPDATA_REQ */
enum mipc_call_set_gwsd_ka_ipdata_req_tlv_enum {
    mipc_call_set_gwsd_ka_ipdata_req_tlv_NONE = 0,
    /* the keep alive IPDATA */
    /* type = string */
    MIPC_CALL_SET_GWSD_KA_IPDATA_REQ_T_PDATA                = 0x101,
};

    /* MIPC_MSG.CALL_SET_GWSD_KA_IPDATA_CNF */
enum mipc_call_set_gwsd_ka_ipdata_cnf_tlv_enum {
    mipc_call_set_gwsd_ka_ipdata_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.CALL_UIS_INFO_REQ */
enum mipc_call_uis_info_req_tlv_enum {
    mipc_call_uis_info_req_tlv_NONE = 0,
    /* call ID */
    /* type = uint32_t */
    MIPC_CALL_UIS_INFO_REQ_T_CALLID                         = 0x100,
    /* Indicates the type of the UIS Info */
    /* type = uint8_t, refer to CALL_UIS_INFO_TYPE */
    MIPC_CALL_UIS_INFO_REQ_T_TYPE                           = 0x101,
    /* Indicates the detailed UIS Info in string format */
    /* type = string */
    MIPC_CALL_UIS_INFO_REQ_T_DATA                           = 0x102,
};

    /* MIPC_MSG.CALL_UIS_INFO_CNF */
enum mipc_call_uis_info_cnf_tlv_enum {
    mipc_call_uis_info_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.CALL_AUTO_ANSWER_REQ */
enum mipc_call_auto_answer_req_tlv_enum {
    mipc_call_auto_answer_req_tlv_NONE = 0,
    /* enable auto answer */
    /* type = uint8_t */
    MIPC_CALL_AUTO_ANSWER_REQ_T_ENABLE                      = 0x100,
};

    /* MIPC_MSG.CALL_AUTO_ANSWER_CNF */
enum mipc_call_auto_answer_cnf_tlv_enum {
    mipc_call_auto_answer_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.CALL_DATA_PREFER_SET_REQ */
enum mipc_call_data_prefer_set_req_tlv_enum {
    mipc_call_data_prefer_set_req_tlv_NONE = 0,
    /* indicates the state of GPRS transfer preference, <state> of AT+EGTP */
    /* type = uint8_t, refer to CALL_PREFER_SET_STATE */
    MIPC_CALL_DATA_PREFER_SET_REQ_T_STATE                   = 0x100,
    /* indicates the setting of Monitor Peer PCH, <mode> of AT+EMPPCH */
    /* type = uint8_t, refer to CALL_PREFER_SET_MONITOR_MODE */
    MIPC_CALL_DATA_PREFER_SET_REQ_T_MODE                    = 0x101,
};

    /* MIPC_MSG.CALL_DATA_PREFER_SET_CNF */
enum mipc_call_data_prefer_set_cnf_tlv_enum {
    mipc_call_data_prefer_set_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.CALL_ECC_REDIAL_APPROVE_REQ */
enum mipc_call_ecc_redial_approve_req_tlv_enum {
    mipc_call_ecc_redial_approve_req_tlv_NONE = 0,
    /*  0 means disapprove this call, 1 means approve */
    /* type = uint8_t */
    MIPC_CALL_ECC_REDIAL_APPROVE_REQ_T_APPROVE              = 0x100,
    /*  call id */
    /* type = uint32_t */
    MIPC_CALL_ECC_REDIAL_APPROVE_REQ_T_CALL_ID              = 0x101,
};

    /* MIPC_MSG.CALL_ECC_REDIAL_APPROVE_CNF */
enum mipc_call_ecc_redial_approve_cnf_tlv_enum {
    mipc_call_ecc_redial_approve_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.IMS_SET_CONFIG_REQ */
enum mipc_ims_set_config_req_tlv_enum {
    mipc_ims_set_config_req_tlv_NONE = 0,
    /* the configuration class, CLASS_IMS_FEATURE mapping AT+EIMSCFG, CLASS_IMS_CONFIG mapping AT+ECFGSET, IMS_PROVISION mapping AT+EPVSSET, IMS_CAPABILITY is used to set ims capability */
    /* type = uint32_t, refer to IMS_CONFIG_CLASS */
    MIPC_IMS_SET_CONFIG_REQ_T_CLASS                         = 0x100,
    /* the string of configuration type, for example, this string will be send to lowlayer with AT+ECFGSET = type,data */
    /* type = string */
    MIPC_IMS_SET_CONFIG_REQ_T_TYPE                          = 0x101,
    /* the configuration data,for example, this string will be send to lowlayer with AT+ECFGSET = type,data */
    /* type = byte_array */
    MIPC_IMS_SET_CONFIG_REQ_T_DATA                          = 0x102,
};

    /* MIPC_MSG.IMS_SET_CONFIG_CNF */
enum mipc_ims_set_config_cnf_tlv_enum {
    mipc_ims_set_config_cnf_tlv_NONE = 0,
    /* the response data */
    /* type = byte_array */
    MIPC_IMS_SET_CONFIG_CNF_T_DATA                          = 0x100,
};

    /* MIPC_MSG.IMS_GET_CONFIG_REQ */
enum mipc_ims_get_config_req_tlv_enum {
    mipc_ims_get_config_req_tlv_NONE = 0,
    /* the configuration class */
    /* type = uint32_t, refer to IMS_CONFIG_CLASS */
    MIPC_IMS_GET_CONFIG_REQ_T_CLASS                         = 0x100,
    /* the string of configuration type */
    /* type = string */
    MIPC_IMS_GET_CONFIG_REQ_T_TYPE                          = 0x101,
};

    /* MIPC_MSG.IMS_GET_CONFIG_CNF */
enum mipc_ims_get_config_cnf_tlv_enum {
    mipc_ims_get_config_cnf_tlv_NONE = 0,
    /* the response data */
    /* type = byte_array */
    MIPC_IMS_GET_CONFIG_CNF_T_DATA                          = 0x100,
};

    /* MIPC_MSG.IMS_GET_STATE_REQ */
enum mipc_ims_get_state_req_tlv_enum {
    mipc_ims_get_state_req_tlv_NONE = 0,
    /* the event of ims state */
    /* type = uint8_t, refer to IMS_STATE_IND_EVENT */
    MIPC_IMS_GET_STATE_REQ_T_EVENT                          = 0x100,
};

    /* MIPC_MSG.IMS_GET_STATE_CNF */
enum mipc_ims_get_state_cnf_tlv_enum {
    mipc_ims_get_state_cnf_tlv_NONE = 0,
    /* the event of ims state */
    /* type = uint8_t, refer to IMS_STATE_IND_EVENT */
    MIPC_IMS_GET_STATE_CNF_T_EVENT                          = 0x100,
    /* the ims registration state */
    /* type = uint8_t, refer to IMS_STATE */
    MIPC_IMS_GET_STATE_CNF_T_REG_STATE                      = 0x101,
    /* the ims registration ext info */
    /* type = uint32_t */
    MIPC_IMS_GET_STATE_CNF_T_EXT_INFO                       = 0x102,
    /* the ims wfc state */
    /* type = uint8_t */
    MIPC_IMS_GET_STATE_CNF_T_WFC                            = 0x103,
    /* the ims account id */
    /* type = uint32_t */
    MIPC_IMS_GET_STATE_CNF_T_ACCOUNT_ID                     = 0x104,
    /* the ims account id */
    /* type = byte_array */
    MIPC_IMS_GET_STATE_CNF_T_URI                            = 0x8105,
    /* expire time */
    /* type = uint32_t */
    MIPC_IMS_GET_STATE_CNF_T_EXPIRE_TIME                    = 0x106,
    /* error code */
    /* type = uint32_t */
    MIPC_IMS_GET_STATE_CNF_T_ERROR_CODE                     = 0x107,
    /* error message */
    /* type = string */
    MIPC_IMS_GET_STATE_CNF_T_ERROR_MESSAGE                  = 0x108,
};

    /* MIPC_MSG.IMS_SET_PDIS_REQ */
enum mipc_ims_set_pdis_req_tlv_enum {
    mipc_ims_set_pdis_req_tlv_NONE = 0,
    /* transaction id, 1~255 */
    /* type = uint8_t */
    MIPC_IMS_SET_PDIS_REQ_T_TRANSACTION_ID                  = 0x100,
    /* pcscf method */
    /* type = uint8_t, refer to PDIS_METHOD_TYPE */
    MIPC_IMS_SET_PDIS_REQ_T_METHOD                          = 0x101,
    /* to indicate pdis success or not */
    /* type = uint8_t */
    MIPC_IMS_SET_PDIS_REQ_T_IS_SUCCESS                      = 0x102,
};

    /* MIPC_MSG.IMS_SET_PDIS_CNF */
enum mipc_ims_set_pdis_cnf_tlv_enum {
    mipc_ims_set_pdis_cnf_tlv_NONE = 0,
};

    /* MIPC_MSG.IMS_SET_NAPTR_REQ */
enum mipc_ims_set_naptr_req_tlv_enum {
    mipc_ims_set_naptr_req_tlv_NONE = 0,
    /* transaction id, 1~255 */
    /* type = uint8_t */
    MIPC_IMS_SET_NAPTR_REQ_T_TRANSACTION_ID                 = 0x100,
    /* mod id */
    /* type = string */
    MIPC_IMS_SET_NAPTR_REQ_T_MOD_ID                         = 0x101,
    /* to indicate pdis success or not */
    /* type = uint8_t */
    MIPC_IMS_SET_NAPTR_REQ_T_RESULT                         = 0x102,
    /* order */
    /* type = uint8_t */
    MIPC_IMS_SET_NAPTR_REQ_T_ORDER                          = 0x103,
    /* pref */
    /* type = uint8_t */
    MIPC_IMS_SET_NAPTR_REQ_T_PREF                           = 0x104,
    /* flags */
    /* type = string */
    MIPC_IMS_SET_NAPTR_REQ_T_FLAGS                          = 0x105,
    /* service */
    /* type = string */
    MIPC_IMS_SET_NAPTR_REQ_T_SERVICE                        = 0x106,
    /* pref */
    /* type = string */
    MIPC_IMS_SET_NAPTR_REQ_T_REGEXP                         = 0x107,
    /* FQDN */
    /* type = string */
    MIPC_IMS_SET_NAPTR_REQ_T_FQDN                           = 0x108,
};

    /* MIPC_MSG.IMS_SET_NAPTR_CNF */
enum mipc_ims_set_naptr_cnf_tlv_enum {
    mipc_ims_set_naptr_cnf_tlv_NONE = 0,
};

    /* MIPC_MSG.IMS_GET_NW_RPT_REQ */
enum mipc_ims_get_nw_rpt_req_tlv_enum {
    mipc_ims_get_nw_rpt_req_tlv_NONE = 0,
};

    /* MIPC_MSG.IMS_GET_NW_RPT_CNF */
enum mipc_ims_get_nw_rpt_cnf_tlv_enum {
    mipc_ims_get_nw_rpt_cnf_tlv_NONE = 0,
    /* the reporting status */
    /* type = uint8_t, refer to IMS_REPORT_STATUS */
    MIPC_IMS_GET_NW_RPT_CNF_T_REPORT_STATUS                 = 0x100,
    /* IMS VOPS supported indication from the network */
    /* type = uint8_t, refer to NW_IMS_VOPS_STATUS */
    MIPC_IMS_GET_NW_RPT_CNF_T_NW_IMS_VOPS                   = 0x101,
};

    /* MIPC_MSG.IMS_SET_TEST_MODE_REQ */
enum mipc_ims_set_test_mode_req_tlv_enum {
    mipc_ims_set_test_mode_req_tlv_NONE = 0,
    /* ims test mode */
    /* type = uint8_t */
    MIPC_IMS_SET_TEST_MODE_REQ_T_TEST_MODE                  = 0x100,
};

    /* MIPC_MSG.IMS_SET_TEST_MODE_CNF */
enum mipc_ims_set_test_mode_cnf_tlv_enum {
    mipc_ims_set_test_mode_cnf_tlv_NONE = 0,
};

    /* MIPC_MSG.IMS_SET_EIREG_REQ */
enum mipc_ims_set_eireg_req_tlv_enum {
    mipc_ims_set_eireg_req_tlv_NONE = 0,
    /* the ims registration state */
    /* type = uint8_t */
    MIPC_IMS_SET_EIREG_REQ_T_REG_STATE                      = 0x100,
    /* the ims registration type */
    /* type = uint8_t */
    MIPC_IMS_SET_EIREG_REQ_T_REG_TYPE                       = 0x101,
    /* the ims registration ext info */
    /* type = uint32_t */
    MIPC_IMS_SET_EIREG_REQ_T_EXT_INFO                       = 0x102,
    /* the ims dereg cause */
    /* type = uint8_t */
    MIPC_IMS_SET_EIREG_REQ_T_DEREG_CAUSE                    = 0x103,
    /* the ims rat */
    /* type = uint8_t */
    MIPC_IMS_SET_EIREG_REQ_T_IMS_RAT                        = 0x104,
    /* the ims sip uri type */
    /* type = uint8_t */
    MIPC_IMS_SET_EIREG_REQ_T_SIP_URI_TYPE                   = 0x105,
    /* the ims detail state */
    /* type = uint8_t */
    MIPC_IMS_SET_EIREG_REQ_T_DETAIL_IMS_STATE               = 0x106,
    /* the ims reason */
    /* type = uint8_t */
    MIPC_IMS_SET_EIREG_REQ_T_REASON                         = 0x107,
};

    /* MIPC_MSG.IMS_SET_EIREG_CNF */
enum mipc_ims_set_eireg_cnf_tlv_enum {
    mipc_ims_set_eireg_cnf_tlv_NONE = 0,
};

    /* MIPC_MSG.IMS_SET_SCM_REQ */
enum mipc_ims_set_scm_req_tlv_enum {
    mipc_ims_set_scm_req_tlv_NONE = 0,
    /* Smart Congestion Mitigation application */
    /* type = uint8_t, refer to SCM_APPLICATION_ENUM */
    MIPC_IMS_SET_SCM_REQ_T_APPLICATION                      = 0x100,
    /* start or end */
    /* type = uint8_t, refer to SCM_INDICATION_ENUM */
    MIPC_IMS_SET_SCM_REQ_T_INDICATION                       = 0x101,
};

    /* MIPC_MSG.IMS_SET_SCM_CNF */
enum mipc_ims_set_scm_cnf_tlv_enum {
    mipc_ims_set_scm_cnf_tlv_NONE = 0,
};

    /* MIPC_MSG.IMS_SET_SERVICE_SESSION_REQ */
enum mipc_ims_set_service_session_req_tlv_enum {
    mipc_ims_set_service_session_req_tlv_NONE = 0,
    /* IMS service session status */
    /* type = uint8_t, refer to IMS_SERVICE_TYPE_ENUM */
    MIPC_IMS_SET_SERVICE_SESSION_REQ_T_SERVICE_TYPE         = 0x100,
    /* start or end */
    /* type = uint8_t, refer to IMS_SERVICE_STATUS_ENUM */
    MIPC_IMS_SET_SERVICE_SESSION_REQ_T_SERVICE_STATUS       = 0x101,
};

    /* MIPC_MSG.IMS_SET_SERVICE_SESSION_CNF */
enum mipc_ims_set_service_session_cnf_tlv_enum {
    mipc_ims_set_service_session_cnf_tlv_NONE = 0,
};

    /* MIPC_MSG.IMS_SET_UAC_REQ */
enum mipc_ims_set_uac_req_tlv_enum {
    mipc_ims_set_uac_req_tlv_NONE = 0,
    /* IMS service session status */
    /* type = uint8_t, refer to IMS_SERVICE_TYPE_ENUM */
    MIPC_IMS_SET_UAC_REQ_T_SERVICE_TYPE                     = 0x100,
    /* start or end */
    /* type = uint8_t, refer to IMS_SERVICE_STATUS_ENUM */
    MIPC_IMS_SET_UAC_REQ_T_SERVICE_STATUS                   = 0x101,
};

    /* MIPC_MSG.IMS_SET_UAC_CNF */
enum mipc_ims_set_uac_cnf_tlv_enum {
    mipc_ims_set_uac_cnf_tlv_NONE = 0,
};

    /* MIPC_MSG.WFC_REGISTER_CELL_SIGNAL_IND_REQ */
enum mipc_wfc_register_cell_signal_ind_req_tlv_enum {
    mipc_wfc_register_cell_signal_ind_req_tlv_NONE = 0,
    /* witch SIGNAL_TYPE this req is set for */
    /* type = uint8_t, refer to WFC_SIGNAL_TYPE */
    MIPC_WFC_REGISTER_CELL_SIGNAL_IND_REQ_T_SIGNAL_TYPE     = 0x100,
    /* enable IND? */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_WFC_REGISTER_CELL_SIGNAL_IND_REQ_T_ENABLE_RPT      = 0x101,
    /* default value(if not carry this TLV):500; unit:ms; */
    /* type = uint32_t */
    MIPC_WFC_REGISTER_CELL_SIGNAL_IND_REQ_T_TIME            = 0x102,
    /* unit:dbm */
    /* type = int16_t */
    MIPC_WFC_REGISTER_CELL_SIGNAL_IND_REQ_T_THRESHOLD_IN    = 0x103,
    /* unit:dbm */
    /* type = int16_t */
    MIPC_WFC_REGISTER_CELL_SIGNAL_IND_REQ_T_THRESHOLD_OUT   = 0x104,
    /* threshold value for extension; unit:dbm */
    /* type = int16_t */
    MIPC_WFC_REGISTER_CELL_SIGNAL_IND_REQ_T_THRESHOLD_EXT   = 0x105,
};

    /* MIPC_MSG.WFC_REGISTER_CELL_SIGNAL_IND_CNF */
enum mipc_wfc_register_cell_signal_ind_cnf_tlv_enum {
    mipc_wfc_register_cell_signal_ind_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.WFC_CSSAC_REQ */
enum mipc_wfc_cssac_req_tlv_enum {
    mipc_wfc_cssac_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.WFC_CSSAC_CNF */
enum mipc_wfc_cssac_cnf_tlv_enum {
    mipc_wfc_cssac_cnf_tlv_NONE = 0,
    /* parameter shows the barring factor for MMTEL voice, refer to TS27.007 +CSSAC */
    /* type = uint16_t */
    MIPC_WFC_CSSAC_CNF_T_BF_VOICE                           = 0x100,
    /* parameter shows the barring factor for MMTEL video, refer to TS27.007 +CSSAC */
    /* type = uint16_t */
    MIPC_WFC_CSSAC_CNF_T_BF_VIDEO                           = 0x101,
    /* parameter shows the barring timer for MMTEL voice, refer to TS27.007 +CSSAC */
    /* type = uint16_t */
    MIPC_WFC_CSSAC_CNF_T_BT_VOICE                           = 0x102,
    /* parameter shows the barring timer for MMTEL video, refer to TS27.007 +CSSAC */
    /* type = uint16_t */
    MIPC_WFC_CSSAC_CNF_T_BT_VIDEO                           = 0x103,
};

    /* MIPC_MSG.WFC_SET_EMC_AID_REQ */
enum mipc_wfc_set_emc_aid_req_tlv_enum {
    mipc_wfc_set_emc_aid_req_tlv_NONE = 0,
    /* aid=xxxx-yyyy-wwww-zzzz (64 bit hex values) */
    /* type = string */
    MIPC_WFC_SET_EMC_AID_REQ_T_AID                          = 0x100,
};

    /* MIPC_MSG.WFC_SET_EMC_AID_CNF */
enum mipc_wfc_set_emc_aid_cnf_tlv_enum {
    mipc_wfc_set_emc_aid_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.WFC_CFG_REQ */
enum mipc_wfc_cfg_req_tlv_enum {
    mipc_wfc_cfg_req_tlv_NONE = 0,
    /* location enable */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_WFC_CFG_REQ_T_LOCATION_ENABLE                      = 0x100,
    /* set WiFi Calling Profile by AP */
    /* type = uint8_t, refer to WFC_PREFER */
    MIPC_WFC_CFG_REQ_T_WFC_PREFER                           = 0x101,
};

    /* MIPC_MSG.WFC_CFG_CNF */
enum mipc_wfc_cfg_cnf_tlv_enum {
    mipc_wfc_cfg_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.PHB_SET_UPB_ENTRY_REQ */
enum mipc_phb_set_upb_entry_req_tlv_enum {
    mipc_phb_set_upb_entry_req_tlv_NONE = 0,
    /* operation: 2 means edit,3 means delete */
    /* type = uint32_t */
    MIPC_PHB_SET_UPB_ENTRY_REQ_T_OP                         = 0x100,
    /* the type of USIM phonebook related EF files.  */
    /* type = uint32_t, refer to PHB_EF_FILE_TYPE */
    MIPC_PHB_SET_UPB_ENTRY_REQ_T_TYPE                       = 0x101,
    /* the index of ADN entry to be accessed. */
    /* type = uint32_t */
    MIPC_PHB_SET_UPB_ENTRY_REQ_T_ADN_INDEX                  = 0x102,
    /* the index of EF entry to be accessed. */
    /* type = uint32_t */
    MIPC_PHB_SET_UPB_ENTRY_REQ_T_EF_ENTRY_INDEX             = 0x103,
    /* the type of number, valid value:129(normal) 145(international). */
    /* type = uint32_t */
    MIPC_PHB_SET_UPB_ENTRY_REQ_T_TON                        = 0x104,
    /* the associated EF_AAS entry index. */
    /* type = uint32_t */
    MIPC_PHB_SET_UPB_ENTRY_REQ_T_AAS_ID                     = 0x105,
    /* group id list count,max is 10. */
    /* type = uint32_t */
    MIPC_PHB_SET_UPB_ENTRY_REQ_T_GRP_COUNT                  = 0x106,
    /* group id list,valid value 0-255. */
    /* type = uint32_t */
    MIPC_PHB_SET_UPB_ENTRY_REQ_T_GRP_ID_LIST                = 0x107,
    /* number/email/alphaID string. */
    /* type = string */
    MIPC_PHB_SET_UPB_ENTRY_REQ_T_LINE                       = 0x8108,
    /* number/email/alphaID string encode method. */
    /* type = uint32_t, refer to PHB_ENCODE_METHOD */
    MIPC_PHB_SET_UPB_ENTRY_REQ_T_ENCODE_METHOD              = 0x109,
};

    /* MIPC_MSG.PHB_SET_UPB_ENTRY_CNF */
enum mipc_phb_set_upb_entry_cnf_tlv_enum {
    mipc_phb_set_upb_entry_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.PHB_GET_UPB_ANR_EMAIL_SNE_ENTRY_REQ */
enum mipc_phb_get_upb_anr_email_sne_entry_req_tlv_enum {
    mipc_phb_get_upb_anr_email_sne_entry_req_tlv_NONE = 0,
    /* the type of USIM phonebook related EF files. 0:EF_ANR 1:EF_EMAIL 2:EF_SNE */
    /* type = uint32_t, refer to PHB_EF_FILE_TYPE */
    MIPC_PHB_GET_UPB_ANR_EMAIL_SNE_ENTRY_REQ_T_TYPE         = 0x100,
    /* the index of ADN entry to be accessed. */
    /* type = uint32_t */
    MIPC_PHB_GET_UPB_ANR_EMAIL_SNE_ENTRY_REQ_T_ADN_INDEX    = 0x101,
    /* the index of EF entry to be accessed. */
    /* type = uint32_t */
    MIPC_PHB_GET_UPB_ANR_EMAIL_SNE_ENTRY_REQ_T_EF_ENTRY_INDEX = 0x8102,
};

    /* MIPC_MSG.PHB_GET_UPB_ANR_EMAIL_SNE_ENTRY_CNF */
enum mipc_phb_get_upb_anr_email_sne_entry_cnf_tlv_enum {
    mipc_phb_get_upb_anr_email_sne_entry_cnf_tlv_NONE = 0,
    /* phb anr entry */
    /* type = struct, refer to phb_anr_entry */
    MIPC_PHB_GET_UPB_ANR_EMAIL_SNE_ENTRY_CNF_T_PHB_ENTRY    = 0x8100,
    /* email str */
    /* type = struct, refer to phb_email_str */
    MIPC_PHB_GET_UPB_ANR_EMAIL_SNE_ENTRY_CNF_T_EMAIL        = 0x8101,
    /* sne str. */
    /* type = struct, refer to phb_name_str */
    MIPC_PHB_GET_UPB_ANR_EMAIL_SNE_ENTRY_CNF_T_SNESTR       = 0x8102,
};

    /* MIPC_MSG.PHB_GET_UPB_AAS_GAS_GRP_LIST_ENTRY_REQ */
enum mipc_phb_get_upb_aas_gas_grp_list_entry_req_tlv_enum {
    mipc_phb_get_upb_aas_gas_grp_list_entry_req_tlv_NONE = 0,
    /* the type of USIM phonebook related EF files. 3:EF_AAS 4:EF_GAS 5:EF_GRP */
    /* type = uint32_t, refer to PHB_EF_FILE_TYPE */
    MIPC_PHB_GET_UPB_AAS_GAS_GRP_LIST_ENTRY_REQ_T_TYPE      = 0x100,
    /* the begining index of ADN entry to be accessed. */
    /* type = uint32_t */
    MIPC_PHB_GET_UPB_AAS_GAS_GRP_LIST_ENTRY_REQ_T_BINDEX    = 0x101,
    /* the ending index of ADN entry to be accessed. */
    /* type = uint32_t */
    MIPC_PHB_GET_UPB_AAS_GAS_GRP_LIST_ENTRY_REQ_T_EINDEX    = 0x102,
};

    /* MIPC_MSG.PHB_GET_UPB_AAS_GAS_GRP_LIST_ENTRY_CNF */
enum mipc_phb_get_upb_aas_gas_grp_list_entry_cnf_tlv_enum {
    mipc_phb_get_upb_aas_gas_grp_list_entry_cnf_tlv_NONE = 0,
    /* aas entry count. */
    /* type = uint32_t */
    MIPC_PHB_GET_UPB_AAS_GAS_GRP_LIST_ENTRY_CNF_T_AAS_COUNT = 0x100,
    /* aas str array. */
    /* type = struct_array, refer to phb_name_str */
    MIPC_PHB_GET_UPB_AAS_GAS_GRP_LIST_ENTRY_CNF_T_AAS_LIST  = 0x8101,
    /* gas entry count. */
    /* type = uint32_t */
    MIPC_PHB_GET_UPB_AAS_GAS_GRP_LIST_ENTRY_CNF_T_GAS_COUNT = 0x102,
    /* gas str array. */
    /* type = struct_array, refer to phb_name_str */
    MIPC_PHB_GET_UPB_AAS_GAS_GRP_LIST_ENTRY_CNF_T_GAS_LIST  = 0x8103,
    /* grp id list count. */
    /* type = uint32_t */
    MIPC_PHB_GET_UPB_AAS_GAS_GRP_LIST_ENTRY_CNF_T_GRP_COUNT = 0x104,
    /* group id list,valid value 0-255. */
    /* type = uint32_t */
    MIPC_PHB_GET_UPB_AAS_GAS_GRP_LIST_ENTRY_CNF_T_GRP_ID_LIST = 0x105,
};

    /* MIPC_MSG.PHB_GET_PHB_STORAGE_INFO_REQ */
enum mipc_phb_get_phb_storage_info_req_tlv_enum {
    mipc_phb_get_phb_storage_info_req_tlv_NONE = 0,
    /* the storage type of query, null means to get current shorage type info */
    /* type = uint32_t, refer to PHB_STROAGE_TYPE */
    MIPC_PHB_GET_PHB_STORAGE_INFO_REQ_T_STORAGE_TYPE        = 0x100,
};

    /* MIPC_MSG.PHB_GET_PHB_STORAGE_INFO_CNF */
enum mipc_phb_get_phb_storage_info_cnf_tlv_enum {
    mipc_phb_get_phb_storage_info_cnf_tlv_NONE = 0,
    /* the used memory. */
    /* type = uint32_t */
    MIPC_PHB_GET_PHB_STORAGE_INFO_CNF_T_USED                = 0x100,
    /* the total memory. */
    /* type = uint32_t */
    MIPC_PHB_GET_PHB_STORAGE_INFO_CNF_T_TOTAL               = 0x101,
    /* the max length of number. */
    /* type = uint32_t */
    MIPC_PHB_GET_PHB_STORAGE_INFO_CNF_T_NLENGTH             = 0x102,
    /* the max length of text. */
    /* type = uint32_t */
    MIPC_PHB_GET_PHB_STORAGE_INFO_CNF_T_TLENGTH             = 0x103,
    /* the storage type of query. */
    /* type = uint32_t, refer to PHB_STROAGE_TYPE */
    MIPC_PHB_GET_PHB_STORAGE_INFO_CNF_T_STORAGE_TYPE        = 0x104,
};

    /* MIPC_MSG.PHB_SET_PHB_MEM_STORAGE_REQ */
enum mipc_phb_set_phb_mem_storage_req_tlv_enum {
    mipc_phb_set_phb_mem_storage_req_tlv_NONE = 0,
    /* the storage type. */
    /* type = uint32_t, refer to PHB_STROAGE_TYPE */
    MIPC_PHB_SET_PHB_MEM_STORAGE_REQ_T_STORAGE_TYPE         = 0x100,
    /* the password str. */
    /* type = string */
    MIPC_PHB_SET_PHB_MEM_STORAGE_REQ_T_PASSWORD             = 0x8101,
};

    /* MIPC_MSG.PHB_SET_PHB_MEM_STORAGE_CNF */
enum mipc_phb_set_phb_mem_storage_cnf_tlv_enum {
    mipc_phb_set_phb_mem_storage_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.PHB_GET_PHB_ENTRY_REQ */
enum mipc_phb_get_phb_entry_req_tlv_enum {
    mipc_phb_get_phb_entry_req_tlv_NONE = 0,
    /* the index of beginning entry. */
    /* type = uint32_t */
    MIPC_PHB_GET_PHB_ENTRY_REQ_T_BINDEX                     = 0x100,
    /* the index of ending entry. */
    /* type = uint32_t */
    MIPC_PHB_GET_PHB_ENTRY_REQ_T_EINDEX                     = 0x101,
    /* storage type. when extended is 1,storage should be SM type */
    /* type = uint32_t, refer to PHB_STROAGE_TYPE */
    MIPC_PHB_GET_PHB_ENTRY_REQ_T_STORAGE_TYPE               = 0x102,
    /* the extended type or not, 1 means extended. */
    /* type = uint8_t */
    MIPC_PHB_GET_PHB_ENTRY_REQ_T_EXT                        = 0x103,
};

    /* MIPC_MSG.PHB_GET_PHB_ENTRY_CNF */
enum mipc_phb_get_phb_entry_cnf_tlv_enum {
    mipc_phb_get_phb_entry_cnf_tlv_NONE = 0,
    /* the number of entry count */
    /* type = uint32_t */
    MIPC_PHB_GET_PHB_ENTRY_CNF_T_ENTRY_COUNT                = 0x100,
    /* entry list */
    /* type = struct_array, refer to phb_entry */
    MIPC_PHB_GET_PHB_ENTRY_CNF_T_ENTRY_LIST                 = 0x8101,
};

    /* MIPC_MSG.PHB_SET_PHB_ENTRY_REQ */
enum mipc_phb_set_phb_entry_req_tlv_enum {
    mipc_phb_set_phb_entry_req_tlv_NONE = 0,
    /* storage type,when extended is 1,storage should be SM type. */
    /* type = uint32_t, refer to PHB_STROAGE_TYPE */
    MIPC_PHB_SET_PHB_ENTRY_REQ_T_TYPE                       = 0x100,
    /* the extended type or not, 1 means extended. */
    /* type = uint8_t */
    MIPC_PHB_SET_PHB_ENTRY_REQ_T_EXT                        = 0x101,
    /* the entry to write */
    /* type = struct, refer to phb_entry */
    MIPC_PHB_SET_PHB_ENTRY_REQ_T_ENTRY                      = 0x8102,
};

    /* MIPC_MSG.PHB_SET_PHB_ENTRY_CNF */
enum mipc_phb_set_phb_entry_cnf_tlv_enum {
    mipc_phb_set_phb_entry_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.PHB_GET_PHB_STRINGSLENGTH_REQ */
enum mipc_phb_get_phb_stringslength_req_tlv_enum {
    mipc_phb_get_phb_stringslength_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.PHB_GET_PHB_STRINGSLENGTH_CNF */
enum mipc_phb_get_phb_stringslength_cnf_tlv_enum {
    mipc_phb_get_phb_stringslength_cnf_tlv_NONE = 0,
    /* the max number length. */
    /* type = uint32_t */
    MIPC_PHB_GET_PHB_STRINGSLENGTH_CNF_T_MAX_NUM_LEN        = 0x100,
    /* the max alpha string length. */
    /* type = uint32_t */
    MIPC_PHB_GET_PHB_STRINGSLENGTH_CNF_T_MAX_ALPHA_LEN      = 0x101,
    /* the max additional number alpha string length */
    /* type = uint32_t */
    MIPC_PHB_GET_PHB_STRINGSLENGTH_CNF_T_MAX_AAS_LEN        = 0x102,
    /* the max group info alpha string length */
    /* type = uint32_t */
    MIPC_PHB_GET_PHB_STRINGSLENGTH_CNF_T_MAX_GAS_LEN        = 0x103,
    /* the max second name string length. */
    /* type = uint32_t */
    MIPC_PHB_GET_PHB_STRINGSLENGTH_CNF_T_MAX_SNE_LEN        = 0x104,
    /* the max email string length. */
    /* type = uint32_t */
    MIPC_PHB_GET_PHB_STRINGSLENGTH_CNF_T_MAX_EMAIL_LEN      = 0x105,
};

    /* MIPC_MSG.PHB_GET_UPB_CAPABILITY_REQ */
enum mipc_phb_get_upb_capability_req_tlv_enum {
    mipc_phb_get_upb_capability_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.PHB_GET_UPB_CAPABILITY_CNF */
enum mipc_phb_get_upb_capability_cnf_tlv_enum {
    mipc_phb_get_upb_capability_cnf_tlv_NONE = 0,
    /* the number supported ANR for a ADN entry. */
    /* type = uint32_t */
    MIPC_PHB_GET_UPB_CAPABILITY_CNF_T_NUM_ANR               = 0x100,
    /* the number supported EMAIL for a ADN entry. */
    /* type = uint32_t */
    MIPC_PHB_GET_UPB_CAPABILITY_CNF_T_NUM_EMAIL             = 0x101,
    /* the number supported SNE for a ADN entry. */
    /* type = uint32_t */
    MIPC_PHB_GET_UPB_CAPABILITY_CNF_T_NUM_SNE               = 0x102,
    /* maximum number of AAS entries. */
    /* type = uint32_t */
    MIPC_PHB_GET_UPB_CAPABILITY_CNF_T_NUM_AAS               = 0x103,
    /* maximum length of the AAS in the entries. */
    /* type = uint32_t */
    MIPC_PHB_GET_UPB_CAPABILITY_CNF_T_LEN_AAS               = 0x104,
    /* maximum number of GAS entries. */
    /* type = uint32_t */
    MIPC_PHB_GET_UPB_CAPABILITY_CNF_T_NUM_GAS               = 0x105,
    /* maximum length of the GAS in the entries. */
    /* type = uint32_t */
    MIPC_PHB_GET_UPB_CAPABILITY_CNF_T_LEN_GAS               = 0x106,
    /* maximum number of GRP entries. */
    /* type = uint32_t */
    MIPC_PHB_GET_UPB_CAPABILITY_CNF_T_NUM_GRP               = 0x107,
};

    /* MIPC_MSG.PHB_GET_PHB_AVAILABLE_REQ */
enum mipc_phb_get_phb_available_req_tlv_enum {
    mipc_phb_get_phb_available_req_tlv_NONE = 0,
    /* the type of phonebook related EF files. */
    /* type = uint32_t, refer to PHB_EF_FILE_TYPE */
    MIPC_PHB_GET_PHB_AVAILABLE_REQ_T_TYPE                   = 0x100,
    /* the index of EF file associated with an entry */
    /* type = uint32_t */
    MIPC_PHB_GET_PHB_AVAILABLE_REQ_T_INDEX                  = 0x101,
};

    /* MIPC_MSG.PHB_GET_PHB_AVAILABLE_CNF */
enum mipc_phb_get_phb_available_cnf_tlv_enum {
    mipc_phb_get_phb_available_cnf_tlv_NONE = 0,
    /* max number of entries in the queried EF files. */
    /* type = uint32_t */
    MIPC_PHB_GET_PHB_AVAILABLE_CNF_T_MAX_NUM                = 0x100,
    /* max number of available entries in the queried EF files. */
    /* type = uint32_t */
    MIPC_PHB_GET_PHB_AVAILABLE_CNF_T_AVAILABLE_NUM          = 0x101,
    /* the max string length of queried EF files, such as alpha string length of an EF_GAS entry. */
    /* type = uint32_t */
    MIPC_PHB_GET_PHB_AVAILABLE_CNF_T_MAX_LEN                = 0x102,
};

    /* MIPC_MSG.EMBMS_EMSLU_REQ */
enum mipc_embms_emslu_req_tlv_enum {
    mipc_embms_emslu_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.EMBMS_EMSLU_CNF */
enum mipc_embms_emslu_cnf_tlv_enum {
    mipc_embms_emslu_cnf_tlv_NONE = 0,
    /* 0: disable eMBMS Session List uptate information, 1: enable eMBMS Session List uptate information. */
    /* type = uint8_t */
    MIPC_EMBMS_EMSLU_CNF_T_IS_ENABLED                       = 0x100,
    /* number of MBMS sessions in the list. */
    /* type = uint16_t */
    MIPC_EMBMS_EMSLU_CNF_T_SESSION_COUNT                    = 0x101,
    /* sessions list element. */
    /* type = struct_array, refer to embms_session_info */
    MIPC_EMBMS_EMSLU_CNF_T_SESSION_LIST                     = 0x102,
};

    /* MIPC_MSG.EMBMS_GET_SAI_LIST_REQ */
enum mipc_embms_get_sai_list_req_tlv_enum {
    mipc_embms_get_sai_list_req_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.EMBMS_GET_SAI_LIST_CNF */
enum mipc_embms_get_sai_list_cnf_tlv_enum {
    mipc_embms_get_sai_list_cnf_tlv_NONE = 0,
    /* 0: disable eMBMS Session List uptate information, 1: enable eMBMS Session List uptate information. */
    /* type = uint8_t */
    MIPC_EMBMS_GET_SAI_LIST_CNF_T_IS_ENABLED                = 0x100,
    /* The MBMS SAI info of the current intra frequencies */
    /* type = struct, refer to embms_sai_cf_info */
    MIPC_EMBMS_GET_SAI_LIST_CNF_T_SAI_CF_INFO               = 0x101,
    /* The number of neighboring frequencies. Range is from 0 to 8. */
    /* type = uint8_t */
    MIPC_EMBMS_GET_SAI_LIST_CNF_T_SAI_NF_COUNT              = 0x102,
    /* List of neighbouring frequencies and their bands,if any, with their SAI list. */
    /* type = struct_array, refer to embms_sai_nf_info */
    MIPC_EMBMS_GET_SAI_LIST_CNF_T_SAI_NF_LIST               = 0x103,
};

    /* MIPC_MSG.EMBMS_NOTIFY_HVOLTE_STATUS_REQ */
enum mipc_embms_notify_hvolte_status_req_tlv_enum {
    mipc_embms_notify_hvolte_status_req_tlv_NONE = 0,
    /* the status of the hVoLTE scenarios. 0: the end of the scenario, 1: The beginning of the scenario. */
    /* type = uint8_t */
    MIPC_EMBMS_NOTIFY_HVOLTE_STATUS_REQ_T_STATUS            = 0x100,
};

    /* MIPC_MSG.EMBMS_NOTIFY_HVOLTE_STATUS_CNF */
enum mipc_embms_notify_hvolte_status_cnf_tlv_enum {
    mipc_embms_notify_hvolte_status_cnf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SYS_AT_IND */
enum mipc_sys_at_ind_tlv_enum {
    mipc_sys_at_ind_tlv_NONE = 0,
    /* type = string */
    MIPC_SYS_AT_IND_T_ATCMD                                 = 0x8100,
};

    /* MIPC_MSG.SYS_THERMAL_SENSOR_IND */
enum mipc_sys_thermal_sensor_ind_tlv_enum {
    mipc_sys_thermal_sensor_ind_tlv_NONE = 0,
    /* type = int32_t */
    MIPC_SYS_THERMAL_SENSOR_IND_T_TEMPERATURE               = 0x100,
    /* type = struct, refer to sys_thermal_sensor_config */
    MIPC_SYS_THERMAL_SENSOR_IND_T_THRESHOLD                 = 0x101,
    /* type = uint8_t */
    MIPC_SYS_THERMAL_SENSOR_IND_T_INFO_COUNT                = 0x102,
    /* type = struct, refer to sys_thermal_sensor_info */
    MIPC_SYS_THERMAL_SENSOR_IND_T_INFO                      = 0x103,
    /* type = struct, refer to sys_thermal_sensor_config_e */
    MIPC_SYS_THERMAL_SENSOR_IND_T_CONFIG_E                  = 0x104,
    /* type = struct, refer to sys_thermal_sensor_info_e */
    MIPC_SYS_THERMAL_SENSOR_IND_T_INFO_E                    = 0x105,
};

    /* MIPC_MSG.SYS_CONFIG_IND */
enum mipc_sys_config_ind_tlv_enum {
    mipc_sys_config_ind_tlv_NONE = 0,
    /* the reason of configuration change */
    /* type = uint32_t, refer to SYS_CONFIG_CHANGE_REASON */
    MIPC_SYS_CONFIG_IND_T_REASON                            = 0x100,
    /* the configuration class */
    /* type = uint32_t, refer to SYS_CONFIG_CLASS */
    MIPC_SYS_CONFIG_IND_T_CLASS                             = 0x101,
};

    /* MIPC_MSG.SYS_ADPCLK_IND */
enum mipc_sys_adpclk_ind_tlv_enum {
    mipc_sys_adpclk_ind_tlv_NONE = 0,
    /* type = uint8_t */
    MIPC_SYS_ADPCLK_IND_T_FREQ_INFO_COUNT                   = 0x100,
    /* type = struct_array, refer to sys_adpclk_freq_info */
    MIPC_SYS_ADPCLK_IND_T_FREQ_INFO_LIST                    = 0x101,
};

    /* MIPC_MSG.SYS_MCF_IND */
enum mipc_sys_mcf_ind_tlv_enum {
    mipc_sys_mcf_ind_tlv_NONE = 0,
    /* type = uint8_t */
    MIPC_SYS_MCF_IND_T_TYPE                                 = 0x10A,
    /* type = uint8_t */
    MIPC_SYS_MCF_IND_T_RESULT                               = 0x10B,
};

    /* MIPC_MSG.SYS_SBP_IND */
enum mipc_sys_sbp_ind_tlv_enum {
    mipc_sys_sbp_ind_tlv_NONE = 0,
    /* the sys sbp id */
    /* type = uint32_t */
    MIPC_SYS_SBP_IND_T_SBP_ID                               = 0x100,
    /* the sim sys sbp id */
    /* type = uint32_t */
    MIPC_SYS_SBP_IND_T_SIM_SBP_ID                           = 0x8101,
};

    /* MIPC_MSG.SYS_GEO_LOCATION_IND */
enum mipc_sys_geo_location_ind_tlv_enum {
    mipc_sys_geo_location_ind_tlv_NONE = 0,
    /* request id, 0 ~ 7 */
    /* type = uint8_t, refer to SYS_ACCOUNT_ID */
    MIPC_SYS_GEO_LOCATION_IND_T_ACCOUNT_ID                  = 0x100,
    /* 0: Do not broadcast this information to all IMS accounts. 1: Broadcast this information to all IMS accounts */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_SYS_GEO_LOCATION_IND_T_BROADCAST_FLAG              = 0x101,
    /* latitude from GPS, 0 as failed */
    /* type = string */
    MIPC_SYS_GEO_LOCATION_IND_T_LATITUDE                    = 0x102,
    /* longitude from GPS, 0 as failed */
    /* type = string */
    MIPC_SYS_GEO_LOCATION_IND_T_LONGITUDE                   = 0x103,
    /* accurate from GPS, 0 as failed */
    /* type = string */
    MIPC_SYS_GEO_LOCATION_IND_T_ACCURACY                    = 0x104,
    /* Positioning method */
    /* type = string */
    MIPC_SYS_GEO_LOCATION_IND_T_METHOD                      = 0x105,
    /* type = string */
    MIPC_SYS_GEO_LOCATION_IND_T_CITY                        = 0x106,
    /* type = string */
    MIPC_SYS_GEO_LOCATION_IND_T_STATE                       = 0x107,
    /* Zip code */
    /* type = string */
    MIPC_SYS_GEO_LOCATION_IND_T_ZIP                         = 0x108,
    /* Two-letter country code defined by ISO 3166-1 */
    /* type = string */
    MIPC_SYS_GEO_LOCATION_IND_T_COUNTRY_CODE                = 0x109,
    /* UE Wi-Fi interface mac address */
    /* type = string */
    MIPC_SYS_GEO_LOCATION_IND_T_UE_WLAN_MAC                 = 0x10A,
    /* confidence */
    /* type = uint32_t */
    MIPC_SYS_GEO_LOCATION_IND_T_CONFIDENCE                  = 0x10B,
};

    /* MIPC_MSG.SYS_MD_INIT_IND */
enum mipc_sys_md_init_ind_tlv_enum {
    mipc_sys_md_init_ind_tlv_NONE = 0,
    /* type = uint8_t, refer to MD_INIT_ID */
    MIPC_SYS_MD_INIT_IND_T_INIT_ID                          = 0x100,
};

    /* MIPC_MSG.SYS_WARNING_IND */
enum mipc_sys_warning_ind_tlv_enum {
    mipc_sys_warning_ind_tlv_NONE = 0,
    /* detailed warning info */
    /* type = string */
    MIPC_SYS_WARNING_IND_T_INFO                             = 0x100,
};

    /* MIPC_MSG.SYS_NV_SIG_ERR_IND */
enum mipc_sys_nv_sig_err_ind_tlv_enum {
    mipc_sys_nv_sig_err_ind_tlv_NONE = 0,
    /* type = uint8_t */
    MIPC_SYS_NV_SIG_ERR_IND_T_ERROR_CODE                    = 0x100,
};

    /* MIPC_MSG.SYS_VODATA_STATISTICS_IND */
enum mipc_sys_vodata_statistics_ind_tlv_enum {
    mipc_sys_vodata_statistics_ind_tlv_NONE = 0,
    /* sim slot id, 0 based */
    /* type = uint8_t */
    MIPC_SYS_VODATA_STATISTICS_IND_T_SIM_ID                 = 0x100,
    /* Total tx bytes on internet interface for SIM (bytes) since interface up */
    /* type = uint32_t */
    MIPC_SYS_VODATA_STATISTICS_IND_T_TX_BYTES               = 0x101,
    /* Total rx bytes on internet interface for SIM (bytes) since interface up */
    /* type = uint32_t */
    MIPC_SYS_VODATA_STATISTICS_IND_T_RX_BYTES               = 0x102,
    /* Total tx pkts on internet interface for SIM since interface up */
    /* type = uint32_t */
    MIPC_SYS_VODATA_STATISTICS_IND_T_TX_PKT                 = 0x103,
    /* Total rx pkts on internet interface for SIM since interface up */
    /* type = uint32_t */
    MIPC_SYS_VODATA_STATISTICS_IND_T_RX_PKT                 = 0x104,
};

    /* MIPC_MSG.SYS_THERMAL_ACTUATOR_IND */
enum mipc_sys_thermal_actuator_ind_tlv_enum {
    mipc_sys_thermal_actuator_ind_tlv_NONE = 0,
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_SYS_THERMAL_ACTUATOR_IND_T_IMS_ONLY_IND            = 0x100,
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_SYS_THERMAL_ACTUATOR_IND_T_FLIGHT_MODE_IND         = 0x101,
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_SYS_THERMAL_ACTUATOR_IND_T_CHARGE_IND              = 0x102,
};

    /* MIPC_MSG.APN_IA_CFG_IND */
enum mipc_apn_ia_cfg_ind_tlv_enum {
    mipc_apn_ia_cfg_ind_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.APN_PROFILE_CFG_IND */
enum mipc_apn_profile_cfg_ind_tlv_enum {
    mipc_apn_profile_cfg_ind_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.APN_VZW_CHG_IND */
enum mipc_apn_vzw_chg_ind_tlv_enum {
    mipc_apn_vzw_chg_ind_tlv_NONE = 0,
    /* apn profile count */
    /* type = uint8_t */
    MIPC_APN_VZW_CHG_IND_T_APN_COUNT                        = 0x100,
    /* the list of APN profile */
    /* type = struct_array, refer to vzw_apn_profile */
    MIPC_APN_VZW_CHG_IND_T_APN_LIST                         = 0x101,
};

    /* MIPC_MSG.DATA_ACT_CALL_IND */
enum mipc_data_act_call_ind_tlv_enum {
    mipc_data_act_call_ind_tlv_NONE = 0,
    /* data call id */
    /* type = uint8_t */
    MIPC_DATA_ACT_CALL_IND_T_ID                             = 0x100,
    /* apn name */
    /* type = string */
    MIPC_DATA_ACT_CALL_IND_T_APN                            = 0x101,
    /* pdp type */
    /* type = uint8_t, refer to APN_PDP_TYPE */
    MIPC_DATA_ACT_CALL_IND_T_PDP_TYPE                       = 0x102,
    /* v4 address count */
    /* type = uint8_t */
    MIPC_DATA_ACT_CALL_IND_T_V4_COUNT                       = 0x103,
    /* first v4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_ACT_CALL_IND_T_V4_0                           = 0x8104,
    /* second v4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_ACT_CALL_IND_T_V4_1                           = 0x8105,
    /* third v4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_ACT_CALL_IND_T_V4_2                           = 0x8106,
    /* fourth v4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_ACT_CALL_IND_T_V4_3                           = 0x8107,
    /* v6 address count */
    /* type = uint8_t */
    MIPC_DATA_ACT_CALL_IND_T_V6_COUNT                       = 0x108,
    /* first v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_ACT_CALL_IND_T_V6_0                           = 0x8109,
    /* second v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_ACT_CALL_IND_T_V6_1                           = 0x810A,
    /* third v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_ACT_CALL_IND_T_V6_2                           = 0x810B,
    /* fourth v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_ACT_CALL_IND_T_V6_3                           = 0x810C,
    /* DNS v4 address count */
    /* type = uint8_t */
    MIPC_DATA_ACT_CALL_IND_T_DNS_V4_COUNT                   = 0x10D,
    /* first DNS v4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_ACT_CALL_IND_T_DNS_V4_0                       = 0x810E,
    /* second DNS v4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_ACT_CALL_IND_T_DNS_V4_1                       = 0x810F,
    /* third DNS v4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_ACT_CALL_IND_T_DNS_V4_2                       = 0x8110,
    /* fourth DNS v4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_ACT_CALL_IND_T_DNS_V4_3                       = 0x8111,
    /* DNS v6 address count */
    /* type = uint8_t */
    MIPC_DATA_ACT_CALL_IND_T_DNS_V6_COUNT                   = 0x112,
    /* first DNS v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_ACT_CALL_IND_T_DNS_V6_0                       = 0x8113,
    /* second DNS v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_ACT_CALL_IND_T_DNS_V6_1                       = 0x8114,
    /* third DNS v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_ACT_CALL_IND_T_DNS_V6_2                       = 0x8115,
    /* fourth DNS v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_ACT_CALL_IND_T_DNS_V6_3                       = 0x8116,
    /* PCSCF v4 address count */
    /* type = uint8_t */
    MIPC_DATA_ACT_CALL_IND_T_PCSCF_V4_COUNT                 = 0x117,
    /* first PCSCF v4 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_ACT_CALL_IND_T_PCSCF_V4_0                     = 0x8118,
    /* second PCSCF v4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_ACT_CALL_IND_T_PCSCF_V4_1                     = 0x8119,
    /* third PCSCF v4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_ACT_CALL_IND_T_PCSCF_V4_2                     = 0x811A,
    /* fourth PCSCF v4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_ACT_CALL_IND_T_PCSCF_V4_3                     = 0x811B,
    /* PCSCF v6 address count */
    /* type = uint8_t */
    MIPC_DATA_ACT_CALL_IND_T_PCSCF_V6_COUNT                 = 0x11C,
    /* first PCSCF v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_ACT_CALL_IND_T_PCSCF_V6_0                     = 0x811D,
    /* second PCSCF v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_ACT_CALL_IND_T_PCSCF_V6_1                     = 0x811E,
    /* third PCSCF v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_ACT_CALL_IND_T_PCSCF_V6_2                     = 0x811F,
    /* fourth PCSCF v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_ACT_CALL_IND_T_PCSCF_V6_3                     = 0x8120,
    /* gateway v4 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_ACT_CALL_IND_T_GW_V4                          = 0x8121,
    /* gateway v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_ACT_CALL_IND_T_GW_V6                          = 0x8122,
    /* v4 MTU */
    /* type = uint32_t */
    MIPC_DATA_ACT_CALL_IND_T_MTU_V4                         = 0x123,
    /* v6 MTU */
    /* type = uint32_t */
    MIPC_DATA_ACT_CALL_IND_T_MTU_V6                         = 0x124,
    /* network interface id */
    /* type = uint32_t */
    MIPC_DATA_ACT_CALL_IND_T_INTERFACE_ID                   = 0x125,
    /* data call id */
    /* type = uint8_t */
    MIPC_DATA_ACT_CALL_IND_T_P_ID                           = 0x126,
    /*  fall back data call id */
    /* type = uint8_t */
    MIPC_DATA_ACT_CALL_IND_T_FB_ID                          = 0x127,
    /* network transmition id */
    /* type = uint32_t */
    MIPC_DATA_ACT_CALL_IND_T_TRANS_ID                       = 0x128,
    /*  IPv4 net mask */
    /* type = uint32_t */
    MIPC_DATA_ACT_CALL_IND_T_IPv4_NETMASK                   = 0x129,
    /* RAN info, wifi, cellular or unknown */
    /* type = uint8_t, refer to RAN */
    MIPC_DATA_ACT_CALL_IND_T_RAN_INFO                       = 0x12A,
    /*  network ESM/5GSM bearer id */
    /* type = uint32_t */
    MIPC_DATA_ACT_CALL_IND_T_BEARER_ID                      = 0x12B,
    /* im cn signalling flag from network */
    /* type = uint8_t */
    MIPC_DATA_ACT_CALL_IND_T_IM_CN_SIGNALLING_FLAG          = 0x12C,
};

    /* MIPC_MSG.DATA_DEACT_CALL_IND */
enum mipc_data_deact_call_ind_tlv_enum {
    mipc_data_deact_call_ind_tlv_NONE = 0,
    /* data call id */
    /* type = uint8_t */
    MIPC_DATA_DEACT_CALL_IND_T_ID                           = 0x100,
    /* network error enum, refer to 3GPP 24.008 */
    /* type = uint8_t */
    MIPC_DATA_DEACT_CALL_IND_T_RES                          = 0x101,
    /* network error enum, refer to 3GPP 24.008 */
    /* type = uint32_t */
    MIPC_DATA_DEACT_CALL_IND_T_NEW_RES                      = 0x102,
};

    /* MIPC_MSG.DATA_MOD_CALL_IND */
enum mipc_data_mod_call_ind_tlv_enum {
    mipc_data_mod_call_ind_tlv_NONE = 0,
    /* data call id */
    /* type = uint8_t */
    MIPC_DATA_MOD_CALL_IND_T_ID                             = 0x100,
    /* apn */
    /* type = string */
    MIPC_DATA_MOD_CALL_IND_T_APN                            = 0x101,
    /* pdp type */
    /* type = uint8_t, refer to APN_PDP_TYPE */
    MIPC_DATA_MOD_CALL_IND_T_PDP_TYPE                       = 0x102,
    /* the count of ipv4 address */
    /* type = uint8_t */
    MIPC_DATA_MOD_CALL_IND_T_V4_COUNT                       = 0x103,
    /* first ipv4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_MOD_CALL_IND_T_V4_0                           = 0x8104,
    /* second ipv4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_MOD_CALL_IND_T_V4_1                           = 0x8105,
    /* third ipv4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_MOD_CALL_IND_T_V4_2                           = 0x8106,
    /* forth ipv4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_MOD_CALL_IND_T_V4_3                           = 0x8107,
    /* count of ipv6 address */
    /* type = uint8_t */
    MIPC_DATA_MOD_CALL_IND_T_V6_COUNT                       = 0x108,
    /* first ipv6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_MOD_CALL_IND_T_V6_0                           = 0x8109,
    /* second ipv6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_MOD_CALL_IND_T_V6_1                           = 0x810A,
    /* third ipv6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_MOD_CALL_IND_T_V6_2                           = 0x810B,
    /* forth ipv6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_MOD_CALL_IND_T_V6_3                           = 0x810C,
    /* count of DNS  address */
    /* type = uint8_t */
    MIPC_DATA_MOD_CALL_IND_T_DNS_V4_COUNT                   = 0x10D,
    /* first ipv4 DNS address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_MOD_CALL_IND_T_DNS_V4_0                       = 0x810E,
    /* second ipv4 DNS address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_MOD_CALL_IND_T_DNS_V4_1                       = 0x810F,
    /* third ipv4 DNS address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_MOD_CALL_IND_T_DNS_V4_2                       = 0x8110,
    /* forth ipv4 DNS address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_MOD_CALL_IND_T_DNS_V4_3                       = 0x8111,
    /* count of ipv6 DNS address */
    /* type = uint8_t */
    MIPC_DATA_MOD_CALL_IND_T_DNS_V6_COUNT                   = 0x112,
    /* first ipv6 DNS address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_MOD_CALL_IND_T_DNS_V6_0                       = 0x8113,
    /* second ipv6 DNS address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_MOD_CALL_IND_T_DNS_V6_1                       = 0x8114,
    /* third ipv6 DNS address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_MOD_CALL_IND_T_DNS_V6_2                       = 0x8115,
    /* forth ipv6 DNS address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_MOD_CALL_IND_T_DNS_V6_3                       = 0x8116,
    /*  count of P-CSCF */
    /* type = uint8_t */
    MIPC_DATA_MOD_CALL_IND_T_PCSCF_V4_COUNT                 = 0x117,
    /* first address of P-CSCF */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_MOD_CALL_IND_T_PCSCF_V4_0                     = 0x8118,
    /* second address of P-CSCF */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_MOD_CALL_IND_T_PCSCF_V4_1                     = 0x8119,
    /* third address of P-CSCF */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_MOD_CALL_IND_T_PCSCF_V4_2                     = 0x811A,
    /* forth address of P-CSCF */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_MOD_CALL_IND_T_PCSCF_V4_3                     = 0x811B,
    /* count of ipv6 P-CSCF */
    /* type = uint8_t */
    MIPC_DATA_MOD_CALL_IND_T_PCSCF_V6_COUNT                 = 0x11C,
    /* first address of ipv6 P-CSCF */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_MOD_CALL_IND_T_PCSCF_V6_0                     = 0x811D,
    /* second address of ipv6 P-CSCF */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_MOD_CALL_IND_T_PCSCF_V6_1                     = 0x811E,
    /* third address of ipv6 P-CSCF */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_MOD_CALL_IND_T_PCSCF_V6_2                     = 0x811F,
    /* forth address of ipv6 P-CSCF */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_MOD_CALL_IND_T_PCSCF_V6_3                     = 0x8120,
    /* ipv4 gateway address */
    /* type = struct, refer to data_v4_addr */
    MIPC_DATA_MOD_CALL_IND_T_GW_V4                          = 0x8121,
    /* ipv6 gateway address */
    /* type = struct, refer to data_v6_addr */
    MIPC_DATA_MOD_CALL_IND_T_GW_V6                          = 0x8122,
    /* mtu of ipv4 */
    /* type = uint32_t */
    MIPC_DATA_MOD_CALL_IND_T_MTU_V4                         = 0x123,
    /* mtu of ipv6 */
    /* type = uint32_t */
    MIPC_DATA_MOD_CALL_IND_T_MTU_V6                         = 0x124,
    /* interface ID */
    /* type = uint32_t */
    MIPC_DATA_MOD_CALL_IND_T_INTERFACE_ID                   = 0x125,
    /* network transmition id */
    /* type = uint32_t */
    MIPC_DATA_MOD_CALL_IND_T_TRANS_ID                       = 0x126,
    /* RAN info, wifi, cellular or unknown */
    /* type = uint8_t, refer to RAN */
    MIPC_DATA_MOD_CALL_IND_T_RAN_INFO                       = 0x127,
    /*  network ESM/5GSM bearer id */
    /* type = uint32_t */
    MIPC_DATA_MOD_CALL_IND_T_BEARER_ID                      = 0x128,
    /* im cn signalling flag from network */
    /* type = uint8_t */
    MIPC_DATA_MOD_CALL_IND_T_IM_CN_SIGNALLING_FLAG          = 0x129,
    /* primary data call id */
    /* type = uint8_t */
    MIPC_DATA_MOD_CALL_IND_T_P_ID                           = 0x12A,
    /* a bitmap that indicates what kind of change occurred, Bit1 TFT changed, Bit 2 Qos changed, Bit 3 WLAN Offload changed, Bit 4 Relocation of PDU session anchor requested, Bit 5 PDP address or PDP type changed, Bit 6 ATSSS parameters changed, Bit 7 P-CSCF restoration requested */
    /* type = uint32_t */
    MIPC_DATA_MOD_CALL_IND_T_CHANGE_REASON                  = 0x12C,
    /* indicates whether this is an informational event or whether the TE has to acknowledge it. 0 Informational event, 1 Information request: Acknowledgement required. */
    /* type = uint8_t, refer to DATA_MOD_EVENT_TYPE */
    MIPC_DATA_MOD_CALL_IND_T_EVENT_TYPE                     = 0x12D,
};

    /* MIPC_MSG.DATA_MOD_PCO_IND */
enum mipc_data_mod_pco_ind_tlv_enum {
    mipc_data_mod_pco_ind_tlv_NONE = 0,
    /* data call ID */
    /* type = uint8_t */
    MIPC_DATA_MOD_PCO_IND_T_ID                              = 0x100,
    /* pco count */
    /* type = uint8_t */
    MIPC_DATA_MOD_PCO_IND_T_PCO_COUNT                       = 0x101,
    /* pco struct list */
    /* type = struct_array, refer to data_pco_ie */
    MIPC_DATA_MOD_PCO_IND_T_PCO_LIST                        = 0x102,
};

    /* MIPC_MSG.DATA_WWAN_ACT_CALL_IND */
enum mipc_data_wwan_act_call_ind_tlv_enum {
    mipc_data_wwan_act_call_ind_tlv_NONE = 0,
    /* interface ID */
    /* type = uint32_t */
    MIPC_DATA_WWAN_ACT_CALL_IND_T_INTERFACE_ID              = 0x100,
    /* data call ID */
    /* type = uint32_t */
    MIPC_DATA_WWAN_ACT_CALL_IND_T_CID                       = 0x101,
    /* APN name */
    /* type = string */
    MIPC_DATA_WWAN_ACT_CALL_IND_T_APN                       = 0x102,
    /* APN type */
    /* type = uint32_t, refer to APN_TYPE */
    MIPC_DATA_WWAN_ACT_CALL_IND_T_APN_TYPE                  = 0x103,
    /* PDP type */
    /* type = uint8_t, refer to APN_PDP_TYPE */
    MIPC_DATA_WWAN_ACT_CALL_IND_T_PDP_TYPE                  = 0x104,
    /* mtu of ipv4 */
    /* type = uint32_t */
    MIPC_DATA_WWAN_ACT_CALL_IND_T_V4_MTU                    = 0x105,
    /* mtu of ipv6 */
    /* type = uint32_t */
    MIPC_DATA_WWAN_ACT_CALL_IND_T_V6_MTU                    = 0x106,
    /* ipv4 address count */
    /* type = uint8_t */
    MIPC_DATA_WWAN_ACT_CALL_IND_T_V4_ADDR_COUNT             = 0x107,
    /* ipv4 address struct list */
    /* type = struct_array, refer to addr */
    MIPC_DATA_WWAN_ACT_CALL_IND_T_V4_ADDR_LIST              = 0x8108,
    /* ipv6 address count */
    /* type = uint8_t */
    MIPC_DATA_WWAN_ACT_CALL_IND_T_V6_ADDR_COUNT             = 0x109,
    /* ipv6 address struct list */
    /* type = struct_array, refer to addr */
    MIPC_DATA_WWAN_ACT_CALL_IND_T_V6_ADDR_LIST              = 0x810A,
    /* ipv4 DNS address count */
    /* type = uint8_t */
    MIPC_DATA_WWAN_ACT_CALL_IND_T_DNS_V4_ADDR_COUNT         = 0x10B,
    /* ipv4 DNS address struct list */
    /* type = struct_array, refer to addr */
    MIPC_DATA_WWAN_ACT_CALL_IND_T_DNS_V4_ADDR_LIST          = 0x810C,
    /* ipv6 DNS address count */
    /* type = uint8_t */
    MIPC_DATA_WWAN_ACT_CALL_IND_T_DNS_V6_ADDR_COUNT         = 0x10D,
    /* ipv6 DNS address struct list */
    /* type = struct_array, refer to addr */
    MIPC_DATA_WWAN_ACT_CALL_IND_T_DNS_V6_ADDR_LIST          = 0x810E,
};

    /* MIPC_MSG.DATA_WWAN_DEACT_CALL_IND */
enum mipc_data_wwan_deact_call_ind_tlv_enum {
    mipc_data_wwan_deact_call_ind_tlv_NONE = 0,
    /* interface ID */
    /* type = uint32_t */
    MIPC_DATA_WWAN_DEACT_CALL_IND_T_INTERFACE_ID            = 0x100,
    /* data call ID */
    /* type = uint32_t */
    MIPC_DATA_WWAN_DEACT_CALL_IND_T_CID                     = 0x101,
    /* apn name */
    /* type = string */
    MIPC_DATA_WWAN_DEACT_CALL_IND_T_APN                     = 0x102,
    /* apn type */
    /* type = uint32_t, refer to APN_TYPE */
    MIPC_DATA_WWAN_DEACT_CALL_IND_T_APN_TYPE                = 0x103,
};

    /* MIPC_MSG.DATA_CALL_ACT_REG_IND */
enum mipc_data_call_act_reg_ind_tlv_enum {
    mipc_data_call_act_reg_ind_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.DATA_CALL_DEACT_REG_IND */
enum mipc_data_call_deact_reg_ind_tlv_enum {
    mipc_data_call_deact_reg_ind_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.DATA_CALL_MOD_REG_IND */
enum mipc_data_call_mod_reg_ind_tlv_enum {
    mipc_data_call_mod_reg_ind_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.DATA_MD_ACT_CALL_IND */
enum mipc_data_md_act_call_ind_tlv_enum {
    mipc_data_md_act_call_ind_tlv_NONE = 0,
    /* data call ID */
    /* type = uint32_t */
    MIPC_DATA_MD_ACT_CALL_IND_T_CID                         = 0x100,
    /* apn name */
    /* type = string */
    MIPC_DATA_MD_ACT_CALL_IND_T_APN                         = 0x101,
    /* apn index to indicate same apn profile */
    /* type = uint32_t */
    MIPC_DATA_MD_ACT_CALL_IND_T_APN_IDX                     = 0x102,
};

    /* MIPC_MSG.DATA_MD_DEACT_CALL_IND */
enum mipc_data_md_deact_call_ind_tlv_enum {
    mipc_data_md_deact_call_ind_tlv_NONE = 0,
    /* data call ID */
    /* type = uint32_t */
    MIPC_DATA_MD_DEACT_CALL_IND_T_CID                       = 0x100,
};

    /* MIPC_MSG.DATA_IWLAN_PRIORITY_LIST_IND */
enum mipc_data_iwlan_priority_list_ind_tlv_enum {
    mipc_data_iwlan_priority_list_ind_tlv_NONE = 0,
    /* notification */
    /* type = string */
    MIPC_DATA_IWLAN_PRIORITY_LIST_IND_T_CMD                 = 0x100,
    /* pdn type */
    /* type = string */
    MIPC_DATA_IWLAN_PRIORITY_LIST_IND_T_TYPE                = 0x101,
    /* setup priority */
    /* type = uint8_t, refer to MIPC_EIWLPL_PRIORITY_TYPE */
    MIPC_DATA_IWLAN_PRIORITY_LIST_IND_T_SETUP_PRIORITY      = 0x102,
    /* cellular priority */
    /* type = uint8_t, refer to MIPC_EIWLPL_PRIORITY_TYPE */
    MIPC_DATA_IWLAN_PRIORITY_LIST_IND_T_CELLULAR_PRIORITY   = 0x103,
    /* cellular priority */
    /* type = uint8_t, refer to MIPC_EIWLPL_PRIORITY_TYPE */
    MIPC_DATA_IWLAN_PRIORITY_LIST_IND_T_WIFI_PRIORITY       = 0x104,
    /* description for long print */
    /* type = string */
    MIPC_DATA_IWLAN_PRIORITY_LIST_IND_T_DESCRIPTION         = 0x105,
    /* cellular priority */
    /* type = uint8_t */
    MIPC_DATA_IWLAN_PRIORITY_LIST_IND_T_RAT_NUM             = 0x106,
    /* cellular priority */
    /* type = byte_array */
    MIPC_DATA_IWLAN_PRIORITY_LIST_IND_T_RAT_LIST            = 0x107,
};

    /* MIPC_MSG.DATA_LINK_CAPACITY_ESTIMATE_IND */
enum mipc_data_link_capacity_estimate_ind_tlv_enum {
    mipc_data_link_capacity_estimate_ind_tlv_NONE = 0,
    /* Downlink capacity in kbps */
    /* type = uint32_t */
    MIPC_DATA_LINK_CAPACITY_ESTIMATE_IND_T_DL_KBPS          = 0x100,
    /* Uplink capacity in kbps */
    /* type = uint32_t */
    MIPC_DATA_LINK_CAPACITY_ESTIMATE_IND_T_UL_KBPS          = 0x101,
    /* Estimated downlink capacity of secondary carrier in a dual connected NR mode in kbps */
    /* type = uint32_t */
    MIPC_DATA_LINK_CAPACITY_ESTIMATE_IND_T_SECOND_DL_KBPS   = 0x102,
    /* Estimated uplink capacity secondary carrier in a dual connected NR mode in kbps. */
    /* type = uint32_t */
    MIPC_DATA_LINK_CAPACITY_ESTIMATE_IND_T_SECOND_UL_KBPS   = 0x103,
};

    /* MIPC_MSG.DATA_NW_LIMIT_IND */
enum mipc_data_nw_limit_ind_tlv_enum {
    mipc_data_nw_limit_ind_tlv_NONE = 0,
    /* the network limit state */
    /* type = uint32_t */
    MIPC_DATA_NW_LIMIT_IND_T_STATE                          = 0x100,
};

    /* MIPC_MSG.DATA_TIMER_IND */
enum mipc_data_timer_ind_tlv_enum {
    mipc_data_timer_ind_tlv_NONE = 0,
    /* t3396 or back-off */
    /* type = string */
    MIPC_DATA_TIMER_IND_T_SRC_ID                            = 0x100,
    /* apn name */
    /* type = string */
    MIPC_DATA_TIMER_IND_T_APN                               = 0x101,
    /* cause */
    /* type = uint32_t */
    MIPC_DATA_TIMER_IND_T_CAUSE                             = 0x102,
    /* 0:start, 1:stop, 2:expired */
    /* type = uint32_t */
    MIPC_DATA_TIMER_IND_T_TIMER_STATE                       = 0x103,
    /* time in ms */
    /* type = uint32_t */
    MIPC_DATA_TIMER_IND_T_EXPIRE_TIME                       = 0x104,
};

    /* MIPC_MSG.DATA_KEEPALIVE_STATUS_IND */
enum mipc_data_keepalive_status_ind_tlv_enum {
    mipc_data_keepalive_status_ind_tlv_NONE = 0,
    /* connection id */
    /* type = uint32_t */
    MIPC_DATA_KEEPALIVE_STATUS_IND_T_SESSION_HANDLE         = 0x100,
    /* keep alive status code */
    /* type = uint8_t, refer to DATA_KEEPALIVE_STATUS_CODE */
    MIPC_DATA_KEEPALIVE_STATUS_IND_T_STATUS_CODE            = 0x101,
};

    /* MIPC_MSG.DATA_MOBILE_DATA_USAGE_IND */
enum mipc_data_mobile_data_usage_ind_tlv_enum {
    mipc_data_mobile_data_usage_ind_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_DATA_MOBILE_DATA_USAGE_IND_T_TX_BYTES              = 0x100,
    /* type = uint32_t */
    MIPC_DATA_MOBILE_DATA_USAGE_IND_T_TX_PACKETS            = 0x101,
    /* type = uint32_t */
    MIPC_DATA_MOBILE_DATA_USAGE_IND_T_RX_BYTES              = 0x102,
    /* type = uint32_t */
    MIPC_DATA_MOBILE_DATA_USAGE_IND_T_RX_PACKETS            = 0x103,
};

    /* MIPC_MSG.DATA_NETWORK_REJECT_CAUSE_IND */
enum mipc_data_network_reject_cause_ind_tlv_enum {
    mipc_data_network_reject_cause_ind_tlv_NONE = 0,
    /* type = uint16_t */
    MIPC_DATA_NETWORK_REJECT_CAUSE_IND_T_EMM_CAUSE          = 0x100,
    /* type = uint16_t */
    MIPC_DATA_NETWORK_REJECT_CAUSE_IND_T_ESM_CAUSE          = 0x101,
    /* emm cause source */
    /* type = uint16_t */
    MIPC_DATA_NETWORK_REJECT_CAUSE_IND_T_EVENT              = 0x102,
};

    /* MIPC_MSG.DATA_DSDA_STATE_IND */
enum mipc_data_dsda_state_ind_tlv_enum {
    mipc_data_dsda_state_ind_tlv_NONE = 0,
    /* type = uint8_t, refer to DSDA_ALLOWED_TYPE */
    MIPC_DATA_DSDA_STATE_IND_T_DSDA_ALLOWED                 = 0x100,
    /* type = uint8_t, refer to DSDA_STATE_TYPE */
    MIPC_DATA_DSDA_STATE_IND_T_DSDA_STATE                   = 0x101,
    /* type = uint8_t, refer to DR_DSDA_TYPE */
    MIPC_DATA_DSDA_STATE_IND_T_IS_DR_DSDA                   = 0x102,
    /* type = uint8_t, refer to DR_DSDS_TYPE */
    MIPC_DATA_DSDA_STATE_IND_T_IS_DR_DSDS                   = 0x103,
};

    /* MIPC_MSG.DATA_UMTS_PS_STATE_IND */
enum mipc_data_umts_ps_state_ind_tlv_enum {
    mipc_data_umts_ps_state_ind_tlv_NONE = 0,
    /* type = uint8_t */
    MIPC_DATA_UMTS_PS_STATE_IND_T_CONN_STATUS               = 0x100,
};

    /* MIPC_MSG.DATA_RETRY_TIMER_IND */
enum mipc_data_retry_timer_ind_tlv_enum {
    mipc_data_retry_timer_ind_tlv_NONE = 0,
    /* apn name */
    /* type = string */
    MIPC_DATA_RETRY_TIMER_IND_T_APN_NAME                    = 0x100,
};

    /* MIPC_MSG.DATA_URSP_REEVAL_IND */
enum mipc_data_ursp_reeval_ind_tlv_enum {
    mipc_data_ursp_reeval_ind_tlv_NONE = 0,
    /* data call ID list length */
    /* type = uint8_t */
    MIPC_DATA_URSP_REEVAL_IND_T_ID_LIST_LEN                 = 0x100,
    /* data call ID list length */
    /* type = byte_array */
    MIPC_DATA_URSP_REEVAL_IND_T_ID_LIST                     = 0x101,
    /* REEVAL event */
    /* type = uint32_t, refer to URSP_REEVAL_TYPE_ENUM */
    MIPC_DATA_URSP_REEVAL_IND_T_EVENT                       = 0x102,
};

    /* MIPC_MSG.DATA_URSP_UE_POLICY_CHG_IND */
enum mipc_data_ursp_ue_policy_chg_ind_tlv_enum {
    mipc_data_ursp_ue_policy_chg_ind_tlv_NONE = 0,
    /* plmn id, mcc1, mcc2, mcc3, mnc1, mnc2, mnc3 */
    /* type = byte_array */
    MIPC_DATA_URSP_UE_POLICY_CHG_IND_T_PLMN_ID              = 0x100,
    /* ue policy change event */
    /* type = uint32_t, refer to URSP_REEVAL_TYPE_ENUM */
    MIPC_DATA_URSP_UE_POLICY_CHG_IND_T_EVENT                = 0x101,
};

    /* MIPC_MSG.INTERNAL_TEST_IND */
enum mipc_internal_test_ind_tlv_enum {
    mipc_internal_test_ind_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.INTERNAL_EIF_IND */
enum mipc_internal_eif_ind_tlv_enum {
    mipc_internal_eif_ind_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_INTERNAL_EIF_IND_T_TRANSID                         = 0x100,
    /* type = uint8_t, refer to INTERNAL_EIF_IND_CMD */
    MIPC_INTERNAL_EIF_IND_T_CMD                             = 0x101,
    /* type = uint32_t */
    MIPC_INTERNAL_EIF_IND_T_CAUSE                           = 0x102,
    /* type = uint32_t */
    MIPC_INTERNAL_EIF_IND_T_MTU                             = 0x103,
    /* type = uint8_t */
    MIPC_INTERNAL_EIF_IND_T_NET_V4_ADDR_COUNT               = 0x104,
    /* type = struct_array, refer to v4_full_addr */
    MIPC_INTERNAL_EIF_IND_T_NET_V4_ADDR_LIST                = 0x8105,
    /* type = uint8_t */
    MIPC_INTERNAL_EIF_IND_T_NET_V6_ADDR_COUNT               = 0x106,
    /* type = struct_array, refer to v6_full_addr */
    MIPC_INTERNAL_EIF_IND_T_NET_V6_ADDR_LIST                = 0x8107,
};

    /* MIPC_MSG.INTERNAL_HO_IND */
enum mipc_internal_ho_ind_tlv_enum {
    mipc_internal_ho_ind_tlv_NONE = 0,
    /* data call id */
    /* type = uint8_t */
    MIPC_INTERNAL_HO_IND_T_ID                               = 0x100,
    /* HO current progress */
    /* type = uint8_t, refer to INTERNAL_HO_PROGRESS */
    MIPC_INTERNAL_HO_IND_T_PROGRESS                         = 0x102,
    /* source RAN */
    /* type = uint8_t, refer to RAN */
    MIPC_INTERNAL_HO_IND_T_SRC_RAN                          = 0x103,
    /* target RAN */
    /* type = uint8_t, refer to RAN */
    MIPC_INTERNAL_HO_IND_T_DST_RAN                          = 0x104,
    /* HO success ot not */
    /* type = uint8_t */
    MIPC_INTERNAL_HO_IND_T_IS_SUCC                          = 0x105,
    /* v4 address */
    /* type = struct, refer to data_v4_addr */
    MIPC_INTERNAL_HO_IND_T_V4_ADDR                          = 0x8106,
    /* v6 address */
    /* type = struct, refer to data_v6_addr */
    MIPC_INTERNAL_HO_IND_T_V6_ADDR                          = 0x8107,
    /*  network transmition id */
    /* type = uint32_t */
    MIPC_INTERNAL_HO_IND_T_TRANS_ID                         = 0x108,
};

    /* MIPC_MSG.NW_REGISTER_IND */
enum mipc_nw_register_ind_tlv_enum {
    mipc_nw_register_ind_tlv_NONE = 0,
    /* type = struct, refer to nw_reg_state */
    MIPC_NW_REGISTER_IND_T_STATE                            = 0x100,
    /* network error enum, refer to 3GPP 24.008 */
    /* type = uint16_t */
    MIPC_NW_REGISTER_IND_T_NW_ERR                           = 0x101,
    /* type = uint8_t, refer to NW_REGISTER_MODE */
    MIPC_NW_REGISTER_IND_T_MODE                             = 0x102,
    /* This represents the data speed for current radio technologies can support */
    /* type = uint32_t, refer to NW_DATA_SPEED */
    MIPC_NW_REGISTER_IND_T_DATA_SPEED                       = 0x103,
    /* provider short name */
    /* type = string */
    MIPC_NW_REGISTER_IND_T_NW_NAME                          = 0x104,
    /* Raoming text info. */
    /* type = string */
    MIPC_NW_REGISTER_IND_T_ROAMING_TEXT                     = 0x105,
    /* Not valid for indication. */
    /* type = uint16_t */
    MIPC_NW_REGISTER_IND_T_FAIL_CAUSE                       = 0x106,
    /* provider long name */
    /* type = string */
    MIPC_NW_REGISTER_IND_T_NW_LONG_NAME                     = 0x107,
};

    /* MIPC_MSG.NW_SIGNAL_IND */
enum mipc_nw_signal_ind_tlv_enum {
    mipc_nw_signal_ind_tlv_NONE = 0,
    /* Current interval setting for signal reporting, the default value is 5 seconds. */
    /* type = uint32_t */
    MIPC_NW_SIGNAL_IND_T_SIGNAL_STRENGTH_INTERVAL           = 0x104,
    /* Current rssi threshold setting for signal reporting, the default value is 5. */
    /* type = uint32_t */
    MIPC_NW_SIGNAL_IND_T_RSSI_THRESHOLD                     = 0x105,
    /* Current err rate threshold setting for signal reporting, the default value is 0. */
    /* type = uint32_t */
    MIPC_NW_SIGNAL_IND_T_ERR_RATE_THRESHOLD                 = 0x106,
    /* Current rsrp threshold setting for signal reporting, the default value is 2 db. */
    /* type = uint32_t */
    MIPC_NW_SIGNAL_IND_T_RSRP_THRESHOLD                     = 0x107,
    /* Current snr threshold setting for signal reporting, the default value is 0 db. */
    /* type = uint32_t */
    MIPC_NW_SIGNAL_IND_T_SNR_THRESHOLD                      = 0x108,
    /* Signal type, GSM/UMTS/LTE/NR/NSA. Note: When the type is NSA, maybe contains LTE and(or) NR signal info. */
    /* type = uint8_t, refer to NW_SIGNAL_TYPE */
    MIPC_NW_SIGNAL_IND_T_SIGNAL_TYPE                        = 0x109,
    /* GSM signal strength. */
    /* type = struct, refer to nw_gsm_signal_strength */
    MIPC_NW_SIGNAL_IND_T_GSM_SIGNAL                         = 0x10A,
    /* UMTS signal strength. */
    /* type = struct, refer to nw_umts_signal_strength */
    MIPC_NW_SIGNAL_IND_T_UMTS_SIGNAL                        = 0x10B,
    /* LTE signal strength. */
    /* type = struct, refer to nw_lte_signal_strength */
    MIPC_NW_SIGNAL_IND_T_LTE_SIGNAL                         = 0x10C,
    /* NR signal strength. */
    /* type = struct, refer to nw_nr_signal_strength */
    MIPC_NW_SIGNAL_IND_T_NR_SIGNAL                          = 0x10D,
    /* The raw signal data, parse from +ECSQ. */
    /* type = struct_array, refer to nw_raw_signal_info */
    MIPC_NW_SIGNAL_IND_T_RAW_SIGNAL_INFO_LIST               = 0x10E,
    /* The raw signal info count: when in NSA, the count is 2, and others is 1 */
    /* type = uint8_t */
    MIPC_NW_SIGNAL_IND_T_RAW_SIGNAL_INFO_COUNT              = 0x10F,
    /* CDMA signal strength. */
    /* type = struct, refer to nw_cdma_signal_strength */
    MIPC_NW_SIGNAL_IND_T_CDMA_SIGNAL                        = 0x110,
};

    /* MIPC_MSG.NW_PS_IND */
enum mipc_nw_ps_ind_tlv_enum {
    mipc_nw_ps_ind_tlv_NONE = 0,
    /* PS attach state. */
    /* type = uint8_t */
    MIPC_NW_PS_IND_T_TACH                                   = 0x100,
    /* This represents the data speed for current radio technologies can support */
    /* type = uint32_t, refer to NW_DATA_SPEED */
    MIPC_NW_PS_IND_T_DATA_SPEED                             = 0x101,
    /* Just valid for 5G. */
    /* type = uint8_t */
    MIPC_NW_PS_IND_T_NW_FREQUENCY                           = 0x102,
    /* The ps data registration state. */
    /* type = struct, refer to nw_ps_reg_info */
    MIPC_NW_PS_IND_T_REG_INFO                               = 0x103,
    /* The cell type. */
    /* type = uint8_t, refer to NW_CELL_TYPE */
    MIPC_NW_PS_IND_T_CELL_TYPE                              = 0x104,
    /* The cell info: mipc_nw_gsm_cell_struct4 and so on. NOTE: according to the cell type to get the cell info. */
    /* type = struct, refer to nw_gsm_cell */
    MIPC_NW_PS_IND_T_CELL_INFO                              = 0x8105,
};

    /* MIPC_MSG.NW_RADIO_IND */
enum mipc_nw_radio_ind_tlv_enum {
    mipc_nw_radio_ind_tlv_NONE = 0,
    /* sw radio status. */
    /* type = uint8_t */
    MIPC_NW_RADIO_IND_T_SW_STATE                            = 0x100,
    /* hw radio status. */
    /* type = uint8_t */
    MIPC_NW_RADIO_IND_T_HW_STATE                            = 0x101,
};

    /* MIPC_MSG.NW_IA_IND */
enum mipc_nw_ia_ind_tlv_enum {
    mipc_nw_ia_ind_tlv_NONE = 0,
    /* APN name. */
    /* type = string */
    MIPC_NW_IA_IND_T_APN                                    = 0x100,
    /* RAT info. */
    /* type = uint8_t */
    MIPC_NW_IA_IND_T_RAT                                    = 0x101,
    /* type = uint8_t, refer to APN_PDP_TYPE */
    MIPC_NW_IA_IND_T_PDP_TYPE                               = 0x102,
    /* type = uint8_t, refer to APN_AUTH_TYPE */
    MIPC_NW_IA_IND_T_AUTH_TYPE                              = 0x103,
    /* User id. */
    /* type = string */
    MIPC_NW_IA_IND_T_USERID                                 = 0x8104,
    /* Password for user id. */
    /* type = string */
    MIPC_NW_IA_IND_T_PASSWORD                               = 0x8105,
    /* to indicate different APNs which have same apn */
    /* type = uint32_t */
    MIPC_NW_IA_IND_T_APN_INDEX                              = 0x106,
};

    /* MIPC_MSG.NW_NITZ_IND */
enum mipc_nw_nitz_ind_tlv_enum {
    mipc_nw_nitz_ind_tlv_NONE = 0,
    /* type = struct, refer to nw_nitz_info */
    MIPC_NW_NITZ_IND_T_INFO                                 = 0x100,
    /* The type of nitz info. */
    /* type = uint8_t, refer to NITZ_IND_TYPE */
    MIPC_NW_NITZ_IND_T_TYPE                                 = 0x101,
};

    /* MIPC_MSG.NW_LOCATION_INFO_IND */
enum mipc_nw_location_info_ind_tlv_enum {
    mipc_nw_location_info_ind_tlv_NONE = 0,
    /* type = struct, refer to nw_location_info */
    MIPC_NW_LOCATION_INFO_IND_T_INFO                        = 0x8100,
};

    /* MIPC_MSG.NW_CS_IND */
enum mipc_nw_cs_ind_tlv_enum {
    mipc_nw_cs_ind_tlv_NONE = 0,
    /* type = struct, refer to nw_reg_change_info */
    MIPC_NW_CS_IND_T_INFO                                   = 0x8100,
    /* The cell type. */
    /* type = uint8_t, refer to NW_CELL_TYPE */
    MIPC_NW_CS_IND_T_CELL_TYPE                              = 0x101,
    /* The cell info: mipc_nw_gsm_cell_struct4 and so on. NOTE: according to the cell type to get the cell info. */
    /* type = struct, refer to nw_gsm_cell */
    MIPC_NW_CS_IND_T_CELL_INFO                              = 0x8102,
};

    /* MIPC_MSG.NW_CSCON_IND */
enum mipc_nw_cscon_ind_tlv_enum {
    mipc_nw_cscon_ind_tlv_NONE = 0,
    /* type = struct, refer to nw_cscon_status */
    MIPC_NW_CSCON_IND_T_STATUS                              = 0x100,
};

    /* MIPC_MSG.NW_PREFERRED_PROVIDER_IND */
enum mipc_nw_preferred_provider_ind_tlv_enum {
    mipc_nw_preferred_provider_ind_tlv_NONE = 0,
    /* The provider list length. */
    /* type = uint8_t */
    MIPC_NW_PREFERRED_PROVIDER_IND_T_PROVIDER_COUNT         = 0x100,
    /*  */
    /* type = struct_array, refer to nw_provider */
    MIPC_NW_PREFERRED_PROVIDER_IND_T_PROVIDER_LIST          = 0x101,
};

    /* MIPC_MSG.NW_CAINFO_IND */
enum mipc_nw_cainfo_ind_tlv_enum {
    mipc_nw_cainfo_ind_tlv_NONE = 0,
    /* num of dl lte serving cell, the max of it is 32 */
    /* type = uint8_t */
    MIPC_NW_CAINFO_IND_T_LTE_DL_SERVING_CELL_COUNT          = 0x100,
    /* num of ul lte serving cell, the max of it is 32 */
    /* type = uint8_t */
    MIPC_NW_CAINFO_IND_T_LTE_UL_SERVING_CELL_COUNT          = 0x101,
    /* num of dl nr serving cell, the max of it is 32 */
    /* type = uint8_t */
    MIPC_NW_CAINFO_IND_T_NR_DL_SERVING_CELL_COUNT           = 0x102,
    /* num of ul nr serving cell, the max of it is 32 */
    /* type = uint8_t */
    MIPC_NW_CAINFO_IND_T_NR_UL_SERVING_CELL_COUNT           = 0x103,
    /* DL LTE serving cell list */
    /* type = struct_array, refer to nw_lte_nr_ca_info */
    MIPC_NW_CAINFO_IND_T_LTE_DL_SERVING_CELL_LIST           = 0x104,
    /* UL LTE serving cell list */
    /* type = struct_array, refer to nw_lte_nr_ca_info */
    MIPC_NW_CAINFO_IND_T_LTE_UL_SERVING_CELL_LIST           = 0x105,
    /* DL NR serving cell list */
    /* type = struct_array, refer to nw_lte_nr_ca_info */
    MIPC_NW_CAINFO_IND_T_NR_DL_SERVING_CELL_LIST            = 0x106,
    /* UL NR serving cell list */
    /* type = struct_array, refer to nw_lte_nr_ca_info */
    MIPC_NW_CAINFO_IND_T_NR_UL_SERVING_CELL_LIST            = 0x107,
};

    /* MIPC_MSG.NW_EONS_IND */
enum mipc_nw_eons_ind_tlv_enum {
    mipc_nw_eons_ind_tlv_NONE = 0,
    /* pnn. */
    /* type = uint32_t */
    MIPC_NW_EONS_IND_T_PNN                                  = 0x100,
    /* opl */
    /* type = uint32_t */
    MIPC_NW_EONS_IND_T_OPL                                  = 0x101,
};

    /* MIPC_MSG.NW_CIEV_IND */
enum mipc_nw_ciev_ind_tlv_enum {
    mipc_nw_ciev_ind_tlv_NONE = 0,
    /* ciev urc type. */
    /* type = uint32_t */
    MIPC_NW_CIEV_IND_T_CIEV_TYPE                            = 0x100,
    /* the ecbm status value of ciev 102 */
    /* type = uint32_t */
    MIPC_NW_CIEV_IND_T_ECBM_STATUS                          = 0x101,
    /* plmn of operator NW of ciev 10 */
    /* type = string */
    MIPC_NW_CIEV_IND_T_PLMN_ID                              = 0x102,
    /* provider name long of ciev 10 */
    /* type = string */
    MIPC_NW_CIEV_IND_T_NW_NAME_LONG                         = 0x103,
    /* provider name short of ciev 10 */
    /* type = string */
    MIPC_NW_CIEV_IND_T_NW_NAME_SHORT                        = 0x104,
    /* PRL ID of ciev 131 */
    /* type = uint32_t */
    MIPC_NW_CIEV_IND_T_PRL_ID                               = 0x105,
};

    /* MIPC_MSG.NW_EGMSS_IND */
enum mipc_nw_egmss_ind_tlv_enum {
    mipc_nw_egmss_ind_tlv_NONE = 0,
    /* rat. */
    /* type = uint32_t */
    MIPC_NW_EGMSS_IND_T_RAT                                 = 0x100,
    /* mcc */
    /* type = uint32_t */
    MIPC_NW_EGMSS_IND_T_MCC                                 = 0x101,
    /* attach status: 1 attached to the network on the rat; 0 have selected the rat and is going to perform PLMN search. */
    /* type = uint32_t */
    MIPC_NW_EGMSS_IND_T_STATUS                              = 0x102,
    /* current reported rat */
    /* type = uint32_t */
    MIPC_NW_EGMSS_IND_T_CUR_REPORTED_RAT                    = 0x103,
    /* is home country or not, 0: not home contury, 1: home country */
    /* type = uint32_t */
    MIPC_NW_EGMSS_IND_T_IS_HOME_COUNTRY                     = 0x104,
};

    /* MIPC_MSG.NW_PSBEARER_IND */
enum mipc_nw_psbearer_ind_tlv_enum {
    mipc_nw_psbearer_ind_tlv_NONE = 0,
    /* cell data speed support  */
    /* type = uint32_t */
    MIPC_NW_PSBEARER_IND_T_CELL_DATA_SPEED_SUPPORT          = 0x100,
    /* max data bearer capability */
    /* type = uint32_t */
    MIPC_NW_PSBEARER_IND_T_MAX_DATA_BEARER_CAPABILITY       = 0x101,
    /* The number of secondary cells used for down link. */
    /* type = uint32_t */
    MIPC_NW_PSBEARER_IND_T_SEC_CELL_NUM_IN_DL               = 0x102,
    /* The number of secondary cells used for upper link. */
    /* type = uint32_t */
    MIPC_NW_PSBEARER_IND_T_SEC_CELL_NUM_IN_UL               = 0x103,
};

    /* MIPC_MSG.NW_ECELL_IND */
enum mipc_nw_ecell_ind_tlv_enum {
    mipc_nw_ecell_ind_tlv_NONE = 0,
    /* The gsm cell list length. */
    /* type = uint32_t */
    MIPC_NW_ECELL_IND_T_GSM_CELL_COUNT                      = 0x100,
    /*  */
    /* type = struct_array, refer to nw_gsm_cell */
    MIPC_NW_ECELL_IND_T_GSM_CELL_LIST                       = 0x101,
    /* The umts cell list length. */
    /* type = uint32_t */
    MIPC_NW_ECELL_IND_T_UMTS_CELL_COUNT                     = 0x102,
    /*  */
    /* type = struct_array, refer to nw_umts_cell */
    MIPC_NW_ECELL_IND_T_UMTS_CELL_LIST                      = 0x103,
    /* The tdscdma cell list length. */
    /* type = uint32_t */
    MIPC_NW_ECELL_IND_T_TDSCDMA_CELL_COUNT                  = 0x104,
    /*  */
    /* type = struct_array, refer to nw_tdscdma_cell */
    MIPC_NW_ECELL_IND_T_TDSCDMA_CELL_LIST                   = 0x105,
    /* The lte cell list length. */
    /* type = uint32_t */
    MIPC_NW_ECELL_IND_T_LTE_CELL_COUNT                      = 0x106,
    /*  */
    /* type = struct_array, refer to nw_lte_cell */
    MIPC_NW_ECELL_IND_T_LTE_CELL_LIST                       = 0x107,
    /* The cdma cell list length. */
    /* type = uint32_t */
    MIPC_NW_ECELL_IND_T_CDMA_CELL_COUNT                     = 0x108,
    /*  */
    /* type = struct_array, refer to nw_cdma_cell */
    MIPC_NW_ECELL_IND_T_CDMA_CELL_LIST                      = 0x109,
    /* The nr cell list length. */
    /* type = uint32_t */
    MIPC_NW_ECELL_IND_T_NR_CELL_COUNT                       = 0x10A,
    /*  */
    /* type = struct_array, refer to nw_nr_cell */
    MIPC_NW_ECELL_IND_T_NR_CELL_LIST                        = 0x10B,
    /* The fail cause for current operation. */
    /* type = uint16_t */
    MIPC_NW_ECELL_IND_T_FAIL_CAUSE                          = 0x10C,
};

    /* MIPC_MSG.NW_ANBR_IND */
enum mipc_nw_anbr_ind_tlv_enum {
    mipc_nw_anbr_ind_tlv_NONE = 0,
    /* type = struct, refer to nw_anbr_info */
    MIPC_NW_ANBR_IND_T_INFO                                 = 0x100,
};

    /* MIPC_MSG.NW_IRAT_IND */
enum mipc_nw_irat_ind_tlv_enum {
    mipc_nw_irat_ind_tlv_NONE = 0,
    /* type = struct, refer to nw_irat_info */
    MIPC_NW_IRAT_IND_T_INFO                                 = 0x100,
};

    /* MIPC_MSG.NW_EREGINFO_IND */
enum mipc_nw_ereginfo_ind_tlv_enum {
    mipc_nw_ereginfo_ind_tlv_NONE = 0,
    /* 0:GSM, 2:UTRAN, 7:LTE. */
    /* type = uint8_t */
    MIPC_NW_EREGINFO_IND_T_ACT                              = 0x100,
    /* 0:successful completion of Routing Area Update procedure. 1:successful completion of Tracking Area Update procedure */
    /* type = uint8_t */
    MIPC_NW_EREGINFO_IND_T_EVENT_TYPE                       = 0x101,
};

    /* MIPC_MSG.NW_EMODCFG_IND */
enum mipc_nw_emodcfg_ind_tlv_enum {
    mipc_nw_emodcfg_ind_tlv_NONE = 0,
    /* indicate the modulation scheme. */
    /* type = uint8_t */
    MIPC_NW_EMODCFG_IND_T_MODULATION                        = 0x100,
};

    /* MIPC_MSG.NW_EPCELLINFO_IND */
enum mipc_nw_epcellinfo_ind_tlv_enum {
    mipc_nw_epcellinfo_ind_tlv_NONE = 0,
    /* on lte network info, value 1-44. */
    /* type = uint8_t */
    MIPC_NW_EPCELLINFO_IND_T_LTE_BAND                       = 0x100,
};

    /* MIPC_MSG.NW_PSEUDO_CELL_IND */
enum mipc_nw_pseudo_cell_ind_tlv_enum {
    mipc_nw_pseudo_cell_ind_tlv_NONE = 0,
    /* num of pseudo cell num,the value is 1 or 2 */
    /* type = uint8_t */
    MIPC_NW_PSEUDO_CELL_IND_T_CELL_COUNT                    = 0x100,
    /* pseudo cell list of urc */
    /* type = struct_array, refer to nw_pseudocell_info */
    MIPC_NW_PSEUDO_CELL_IND_T_PSEUDOCELL_LIST               = 0x101,
};

    /* MIPC_MSG.NW_NETWORK_INFO_IND */
enum mipc_nw_network_info_ind_tlv_enum {
    mipc_nw_network_info_ind_tlv_NONE = 0,
    /* Type of network info */
    /* type = uint16_t */
    MIPC_NW_NETWORK_INFO_IND_T_TYPE                         = 0x100,
    /* network info of the urc */
    /* type = string */
    MIPC_NW_NETWORK_INFO_IND_T_NW_INFO                      = 0x101,
};

    /* MIPC_MSG.NW_MCCMNC_IND */
enum mipc_nw_mccmnc_ind_tlv_enum {
    mipc_nw_mccmnc_ind_tlv_NONE = 0,
    /* plmn of operator NW */
    /* type = string */
    MIPC_NW_MCCMNC_IND_T_PLMN_ID                            = 0x100,
};

    /* MIPC_MSG.NW_PHYSICAL_CHANNEL_CONFIGS_IND */
enum mipc_nw_physical_channel_configs_ind_tlv_enum {
    mipc_nw_physical_channel_configs_ind_tlv_NONE = 0,
    /* The count for physical ch info list. */
    /* type = uint8_t */
    MIPC_NW_PHYSICAL_CHANNEL_CONFIGS_IND_T_PHYSICAL_CH_INFO_LIST_COUNT = 0x100,
    /* The physical ch info list. */
    /* type = struct_array, refer to physical_channel_info */
    MIPC_NW_PHYSICAL_CHANNEL_CONFIGS_IND_T_PHYSICAL_CH_INFO_LIST = 0x101,
    /* The physical channel configs info list. */
    /* type = struct, refer to physical_channel_info_v1 */
    MIPC_NW_PHYSICAL_CHANNEL_CONFIGS_IND_T_PHYSICAL_CH_INFO_LIST_V1 = 0x102,
};

    /* MIPC_MSG.NW_OTACMSG_IND */
enum mipc_nw_otacmsg_ind_tlv_enum {
    mipc_nw_otacmsg_ind_tlv_NONE = 0,
    /* value 1-14. */
    /* type = uint8_t */
    MIPC_NW_OTACMSG_IND_T_OTA_STATE                         = 0x100,
};

    /* MIPC_MSG.NW_BARRING_INFO_IND */
enum mipc_nw_barring_info_ind_tlv_enum {
    mipc_nw_barring_info_ind_tlv_NONE = 0,
    /* number of barring. */
    /* type = uint8_t */
    MIPC_NW_BARRING_INFO_IND_T_COUNT                        = 0x100,
    /* The barring info LIST of the barring service. */
    /* type = struct_array, refer to nw_barring_info */
    MIPC_NW_BARRING_INFO_IND_T_BARRING_LIST                 = 0x101,
    /* rat, 1:GSM 2:UMTS 4:LTE 128:NR */
    /* type = uint8_t */
    MIPC_NW_BARRING_INFO_IND_T_RAT                          = 0x102,
};

    /* MIPC_MSG.NW_RADIO_CAPABILITY_IND */
enum mipc_nw_radio_capability_ind_tlv_enum {
    mipc_nw_radio_capability_ind_tlv_NONE = 0,
    /* bit0: GSM, bit1: UMTS, bit2: LTE, bit3: NR, bit4: C2K */
    /* type = uint32_t */
    MIPC_NW_RADIO_CAPABILITY_IND_T_RADIO_CAPABILITY         = 0x100,
};

    /* MIPC_MSG.NW_CURRENT_RAT_IND */
enum mipc_nw_current_rat_ind_tlv_enum {
    mipc_nw_current_rat_ind_tlv_NONE = 0,
    /* the rat info by bit, bit0: GSM, bit1: UMTS, bit2: LTE, bit3: NR, bit4: C2K */
    /* type = uint32_t, refer to NW_BIT_RAT */
    MIPC_NW_CURRENT_RAT_IND_T_CURRENT_BIT_RAT               = 0x100,
    /* rat info by the value in AT cmd. 0: GSM; 1: UMTS; 2: GSM+UMTS; 3: LTE; 4: GSM+LTE; 5: UMTS+LTE; 6: GSM+UMTS+LTE; 7: C2K; 8: GSM+C2K; 9: UMTS+C2K; 10: GSM+UMTS+C2K; ...... */
    /* type = uint8_t */
    MIPC_NW_CURRENT_RAT_IND_T_CURRENT_RAT                   = 0x101,
    /* the prefer rat, its invalid value is 255 */
    /* type = uint8_t */
    MIPC_NW_CURRENT_RAT_IND_T_PREFER_RAT                    = 0x102,
};

    /* MIPC_MSG.NW_CAMP_STATE_IND */
enum mipc_nw_camp_state_ind_tlv_enum {
    mipc_nw_camp_state_ind_tlv_NONE = 0,
    /* The ps data registration state. */
    /* type = struct, refer to nw_ps_reg_info */
    MIPC_NW_CAMP_STATE_IND_T_REG_INFO                       = 0x100,
    /* plmn id, for example, 46001 */
    /* type = string */
    MIPC_NW_CAMP_STATE_IND_T_PLMN_ID                        = 0x101,
    /* provider short name */
    /* type = string */
    MIPC_NW_CAMP_STATE_IND_T_NW_NAME                        = 0x102,
};

    /* MIPC_MSG.NW_NR_SWITCH_IND */
enum mipc_nw_nr_switch_ind_tlv_enum {
    mipc_nw_nr_switch_ind_tlv_NONE = 0,
    /* The sim that has nr capability */
    /* type = uint8_t */
    MIPC_NW_NR_SWITCH_IND_T_NR_SIM                          = 0x100,
};

    /* MIPC_MSG.NW_FEMTOCELL_INFO_IND */
enum mipc_nw_femtocell_info_ind_tlv_enum {
    mipc_nw_femtocell_info_ind_tlv_NONE = 0,
    /* femtocell type,1: csg type, 2: cdma type, 3: lte type */
    /* type = uint8_t */
    MIPC_NW_FEMTOCELL_INFO_IND_T_TYPE                       = 0x100,
    /* 1XRTT type */
    /* type = uint8_t */
    MIPC_NW_FEMTOCELL_INFO_IND_T_IS_1X_FEMTOCELL            = 0x101,
    /* evdo type */
    /* type = uint8_t */
    MIPC_NW_FEMTOCELL_INFO_IND_T_IS_EVDO_FEMTOCELL          = 0x102,
    /* This is valid when TYPE is 3, 2 means lte femtocell and 0 means not. */
    /* type = uint8_t */
    MIPC_NW_FEMTOCELL_INFO_IND_T_IS_FEMTOCELL               = 0x103,
    /* 0:CS, 1:PS. */
    /* type = uint8_t */
    MIPC_NW_FEMTOCELL_INFO_IND_T_DOMAIN                     = 0x104,
    /* Network register status. */
    /* type = uint8_t */
    MIPC_NW_FEMTOCELL_INFO_IND_T_STATE                      = 0x105,
    /* Radio access technology */
    /* type = uint8_t */
    MIPC_NW_FEMTOCELL_INFO_IND_T_ACT                        = 0x106,
    /* 0:current cell is not csg cell,1:current cell is csg cell. */
    /* type = uint8_t */
    MIPC_NW_FEMTOCELL_INFO_IND_T_IS_CSG_CELL                = 0x107,
    /* csg id. */
    /* type = uint32_t */
    MIPC_NW_FEMTOCELL_INFO_IND_T_CSG_ID                     = 0x108,
    /* 0:not allowed, 1:allowed, 2:operator, 3:unauth operator, 0xff:invalid. */
    /* type = uint16_t */
    MIPC_NW_FEMTOCELL_INFO_IND_T_CSG_ICON_TYPE              = 0x109,
    /* cause. */
    /* type = uint16_t */
    MIPC_NW_FEMTOCELL_INFO_IND_T_CAUSE                      = 0x10A,
    /* plmn id. */
    /* type = string */
    MIPC_NW_FEMTOCELL_INFO_IND_T_PLMN_ID                    = 0x10B,
    /* operator name. */
    /* type = string */
    MIPC_NW_FEMTOCELL_INFO_IND_T_OPER_NAME                  = 0x10C,
    /* hnb name, Hex decimal format */
    /* type = string */
    MIPC_NW_FEMTOCELL_INFO_IND_T_HNBNAME                    = 0x10D,
};

    /* MIPC_MSG.NW_ETXPWR_IND */
enum mipc_nw_etxpwr_ind_tlv_enum {
    mipc_nw_etxpwr_ind_tlv_NONE = 0,
    /* 2: UTRAN, 7:E-UTRAN. */
    /* type = uint32_t */
    MIPC_NW_ETXPWR_IND_T_ACT                                = 0x100,
    /* indicate TX power value in 1/8 dBm. */
    /* type = int32_t */
    MIPC_NW_ETXPWR_IND_T_TX_POWER                           = 0x101,
};

    /* MIPC_MSG.NW_ETXPWRSTUS_IND */
enum mipc_nw_etxpwrstus_ind_tlv_enum {
    mipc_nw_etxpwrstus_ind_tlv_NONE = 0,
    /* indicates the TX power Event, 0: TX power low indication, 1:TX power high indication, 0xff:default value. */
    /* type = uint16_t */
    MIPC_NW_ETXPWRSTUS_IND_T_EVENT                          = 0x100,
    /* Indicates the SAR scenario index */
    /* type = int16_t */
    MIPC_NW_ETXPWRSTUS_IND_T_SAR_SCENARIO_INDEX             = 0x101,
};

    /* MIPC_MSG.NW_IWLAN_IND */
enum mipc_nw_iwlan_ind_tlv_enum {
    mipc_nw_iwlan_ind_tlv_NONE = 0,
    /* IWLAN Status. */
    /* type = uint32_t, refer to NW_IWLAN_STATUS */
    MIPC_NW_IWLAN_IND_T_STATUS                              = 0x100,
};

    /* MIPC_MSG.NW_CH_INFO_IND */
enum mipc_nw_ch_info_ind_tlv_enum {
    mipc_nw_ch_info_ind_tlv_NONE = 0,
    /* rat value */
    /* type = int32_t, refer to NW_CH_INFO_RAT */
    MIPC_NW_CH_INFO_IND_T_RAT                               = 0x100,
    /* current camped band */
    /* type = int32_t */
    MIPC_NW_CH_INFO_IND_T_BAND                              = 0x101,
    /* current camped channel */
    /* type = int32_t */
    MIPC_NW_CH_INFO_IND_T_CHANNEL                           = 0x102,
    /*  */
    /* type = int32_t */
    MIPC_NW_CH_INFO_IND_T_IS_ENDC                           = 0x103,
};

    /* MIPC_MSG.NW_NRUW_INFO_IND */
enum mipc_nw_nruw_info_ind_tlv_enum {
    mipc_nw_nruw_info_ind_tlv_NONE = 0,
    /* 0: don't display 5G UW, 1: display 5G UW. */
    /* type = uint8_t */
    MIPC_NW_NRUW_INFO_IND_T_DISPLAY_5GUW                    = 0x100,
    /* 0: not on n77 band, 1: on n77 band */
    /* type = uint8_t */
    MIPC_NW_NRUW_INFO_IND_T_ON_N77_BAND                     = 0x101,
    /* 0: not on fr2 band, 1: on fr2 band */
    /* type = uint8_t */
    MIPC_NW_NRUW_INFO_IND_T_ON_FR2_BAND                     = 0x102,
    /* 0: not allowed, 1: allowed */
    /* type = uint8_t */
    MIPC_NW_NRUW_INFO_IND_T_5GUW_ALLOWED                    = 0x103,
};

    /* MIPC_MSG.NW_NR_CA_BAND_IND */
enum mipc_nw_nr_ca_band_ind_tlv_enum {
    mipc_nw_nr_ca_band_ind_tlv_NONE = 0,
    /*  */
    /* type = int32_t */
    MIPC_NW_NR_CA_BAND_IND_T_IS_ENDC                        = 0x100,
    /* The num of nr ca band */
    /* type = uint8_t */
    MIPC_NW_NR_CA_BAND_IND_T_BAND_NUM                       = 0x101,
    /* The nr ca band */
    /* type = struct, refer to nr_ca_band */
    MIPC_NW_NR_CA_BAND_IND_T_BAND                           = 0x102,
};

    /* MIPC_MSG.NW_NR_SCS_IND */
enum mipc_nw_nr_scs_ind_tlv_enum {
    mipc_nw_nr_scs_ind_tlv_NONE = 0,
    /* nr5g subcarrier spacing in khz */
    /* type = int32_t */
    MIPC_NW_NR_SCS_IND_T_SCS                                = 0x100,
};

    /* MIPC_MSG.NW_NETWORK_SCAN_IND */
enum mipc_nw_network_scan_ind_tlv_enum {
    mipc_nw_network_scan_ind_tlv_NONE = 0,
    /* 0: partial, 1: complete */
    /* type = uint32_t, refer to NW_SCAN_STATUS */
    MIPC_NW_NETWORK_SCAN_IND_T_SCAN_STATUS                  = 0x100,
    /* network info */
    /* type = struct, refer to nw_scan_info */
    MIPC_NW_NETWORK_SCAN_IND_T_RECORD_LIST                  = 0x101,
};

    /* MIPC_MSG.NW_CA_INFO_IND */
enum mipc_nw_ca_info_ind_tlv_enum {
    mipc_nw_ca_info_ind_tlv_NONE = 0,
    /* CA info */
    /* type = struct, refer to nw_ecainfo */
    MIPC_NW_CA_INFO_IND_T_CAINFO                            = 0x100,
};

    /* MIPC_MSG.NW_NRUC_INFO_IND */
enum mipc_nw_nruc_info_ind_tlv_enum {
    mipc_nw_nruc_info_ind_tlv_NONE = 0,
    /* 0: not display 5G UC, 1: display 5G UC */
    /* type = uint32_t, refer to NW_5GUC_STATE */
    MIPC_NW_NRUC_INFO_IND_T_DISPLAY_5GUC                    = 0x100,
    /* 0: not on UC band(ex: n41), 1: on UC band(ex: n41) */
    /* type = uint32_t, refer to NW_UC_BAND */
    MIPC_NW_NRUC_INFO_IND_T_ON_UC_BAND                      = 0x101,
    /* 0~300 MHz */
    /* type = uint32_t */
    MIPC_NW_NRUC_INFO_IND_T_AGG_BW                          = 0x102,
};

    /* MIPC_MSG.NW_FIRST_PLMN_IND */
enum mipc_nw_first_plmn_ind_tlv_enum {
    mipc_nw_first_plmn_ind_tlv_NONE = 0,
    /* mcc */
    /* type = string */
    MIPC_NW_FIRST_PLMN_IND_T_MCC                            = 0x100,
    /* mnc */
    /* type = string */
    MIPC_NW_FIRST_PLMN_IND_T_MNC                            = 0x101,
};

    /* MIPC_MSG.SIM_STATE_IND */
enum mipc_sim_state_ind_tlv_enum {
    mipc_sim_state_ind_tlv_NONE = 0,
    /* mapping  to mbim sim state */
    /* type = uint8_t, refer to SIM_STATE */
    MIPC_SIM_STATE_IND_T_STATE                              = 0x100,
    /* sim slot id */
    /* type = uint32_t */
    MIPC_SIM_STATE_IND_T_SIM_ID                             = 0x101,
    /* sim protocol id */
    /* type = uint32_t */
    MIPC_SIM_STATE_IND_T_PS_ID                              = 0x102,
    /* is present or not */
    /* type = uint32_t */
    MIPC_SIM_STATE_IND_T_IS_PRESENT                         = 0x103,
    /* sub state of sim card */
    /* type = uint8_t, refer to SIM_SUB_STATE */
    MIPC_SIM_STATE_IND_T_SUB_STATE                          = 0x104,
};

    /* MIPC_MSG.SIM_STATUS_IND */
enum mipc_sim_status_ind_tlv_enum {
    mipc_sim_status_ind_tlv_NONE = 0,
    /* sim status */
    /* type = uint8_t, refer to SIM_STATUS */
    MIPC_SIM_STATUS_IND_T_STATUS                            = 0x100,
    /* sim slot id */
    /* type = uint32_t */
    MIPC_SIM_STATUS_IND_T_SIM_ID                            = 0x101,
    /* sim protocol id */
    /* type = uint32_t */
    MIPC_SIM_STATUS_IND_T_PS_ID                             = 0x102,
};

    /* MIPC_MSG.SIM_EUICC_SLOTS_STATUS_IND */
enum mipc_sim_euicc_slots_status_ind_tlv_enum {
    mipc_sim_euicc_slots_status_ind_tlv_NONE = 0,
    /* physical slots number */
    /* type = uint8_t */
    MIPC_SIM_EUICC_SLOTS_STATUS_IND_T_SLOTS_INFO_COUNT      = 0x100,
    /* slots info */
    /* type = struct_array, refer to sim_slots_info */
    MIPC_SIM_EUICC_SLOTS_STATUS_IND_T_SLOTS_INFO_LIST       = 0x8101,
    /* type = uint8_t, refer to SIM_CARD_PRESENT_STATE */
    MIPC_SIM_EUICC_SLOTS_STATUS_IND_T_CARD_STATE            = 0x8102,
    /* type = uint8_t */
    MIPC_SIM_EUICC_SLOTS_STATUS_IND_T_SLOTS_STATE           = 0x8103,
    /* type = uint8_t */
    MIPC_SIM_EUICC_SLOTS_STATUS_IND_T_LOGICAL_IDX           = 0x8104,
    /* type = string */
    MIPC_SIM_EUICC_SLOTS_STATUS_IND_T_ATR                   = 0x8105,
    /* type = string */
    MIPC_SIM_EUICC_SLOTS_STATUS_IND_T_EID                   = 0x8106,
    /* type = string */
    MIPC_SIM_EUICC_SLOTS_STATUS_IND_T_ICCID                 = 0x8107,
};

    /* MIPC_MSG.SIM_ICCID_IND */
enum mipc_sim_iccid_ind_tlv_enum {
    mipc_sim_iccid_ind_tlv_NONE = 0,
    /* iccid string */
    /* type = string */
    MIPC_SIM_ICCID_IND_T_ICCID                              = 0x8100,
};

    /* MIPC_MSG.SIM_STATUS_CHANGE_WITH_CAUSE_IND */
enum mipc_sim_status_change_with_cause_ind_tlv_enum {
    mipc_sim_status_change_with_cause_ind_tlv_NONE = 0,
    /* is sim inserted */
    /* type = uint8_t */
    MIPC_SIM_STATUS_CHANGE_WITH_CAUSE_IND_T_IS_SIM_INSERTED = 0x100,
    /* sim change cause */
    /* type = uint8_t, refer to SIM_CAUSE */
    MIPC_SIM_STATUS_CHANGE_WITH_CAUSE_IND_T_CAUSE           = 0x101,
    /* sim change additional cause, currently only refresh  report additional cause */
    /* type = uint8_t, refer to SIM_ADDITIONAL_CAUSE */
    MIPC_SIM_STATUS_CHANGE_WITH_CAUSE_IND_T_ADDITIONAL_CAUSE = 0x102,
};

    /* MIPC_MSG.SIM_PHYSICAL_SLOTS_MAPPING_DONE_IND */
enum mipc_sim_physical_slots_mapping_done_ind_tlv_enum {
    mipc_sim_physical_slots_mapping_done_ind_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SIM_CSIM_IMSI_CHANGE_IND */
enum mipc_sim_csim_imsi_change_ind_tlv_enum {
    mipc_sim_csim_imsi_change_ind_tlv_NONE = 0,
    /* 0 means csim ismi_m not programmed, 1 means csim imsi_m programmed */
    /* type = uint8_t */
    MIPC_SIM_CSIM_IMSI_CHANGE_IND_T_STATUS                  = 0x100,
};

    /* MIPC_MSG.SIM_SML_STATUS_IND */
enum mipc_sim_sml_status_ind_tlv_enum {
    mipc_sim_sml_status_ind_tlv_NONE = 0,
    /* lock rule */
    /* type = uint8_t */
    MIPC_SIM_SML_STATUS_IND_T_LOCK_RULE                     = 0x100,
    /* lock sub rule */
    /* type = uint16_t */
    MIPC_SIM_SML_STATUS_IND_T_LOCK_SUB_RULE                 = 0x101,
    /* device lock state */
    /* type = uint8_t */
    MIPC_SIM_SML_STATUS_IND_T_DEVICE_LOCK_STATE             = 0x102,
    /* max possible capability of current protocol */
    /* type = uint8_t */
    MIPC_SIM_SML_STATUS_IND_T_RULE_POLICY                   = 0x103,
    /* sim card valid state under current rule setting */
    /* type = uint8_t */
    MIPC_SIM_SML_STATUS_IND_T_SIM_VALIDITY                  = 0x104,
    /* remaining times left for user can retry on device lock verification */
    /* type = uint8_t */
    MIPC_SIM_SML_STATUS_IND_T_DEVICE_LOCK_REMAIN_CNT        = 0x105,
};

    /* MIPC_MSG.SIM_SML_RSU_IND */
enum mipc_sim_sml_rsu_ind_tlv_enum {
    mipc_sim_sml_rsu_ind_tlv_NONE = 0,
    /* type = uint8_t */
    MIPC_SIM_SML_RSU_IND_T_OPERATOR_ID                      = 0x100,
    /* type = uint16_t */
    MIPC_SIM_SML_RSU_IND_T_EVENT_ID                         = 0x101,
    /* type = string */
    MIPC_SIM_SML_RSU_IND_T_EVENT_STRING                     = 0x102,
};

    /* MIPC_MSG.SIM_VSIM_RESET_IND */
enum mipc_sim_vsim_reset_ind_tlv_enum {
    mipc_sim_vsim_reset_ind_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SIM_VSIM_APDU_IND */
enum mipc_sim_vsim_apdu_ind_tlv_enum {
    mipc_sim_vsim_apdu_ind_tlv_NONE = 0,
    /* APDU data */
    /* type = string */
    MIPC_SIM_VSIM_APDU_IND_T_DATA                           = 0x8100,
};

    /* MIPC_MSG.SIM_VSIM_EVENT_IND */
enum mipc_sim_vsim_event_ind_tlv_enum {
    mipc_sim_vsim_event_ind_tlv_NONE = 0,
    /* event */
    /* type = uint8_t */
    MIPC_SIM_VSIM_EVENT_IND_T_EVENT                         = 0x100,
    /* APDU data */
    /* type = string */
    MIPC_SIM_VSIM_EVENT_IND_T_DATA                          = 0x8101,
};

    /* MIPC_MSG.SIM_SIMAPP_IND */
enum mipc_sim_simapp_ind_tlv_enum {
    mipc_sim_simapp_ind_tlv_NONE = 0,
    /* app id */
    /* type = uint8_t, refer to SIM_APP_TYPE_EX */
    MIPC_SIM_SIMAPP_IND_T_APP_ID                            = 0x100,
    /* channel id */
    /* type = uint8_t */
    MIPC_SIM_SIMAPP_IND_T_CH_ID                             = 0x101,
    /* MCC */
    /* type = string */
    MIPC_SIM_SIMAPP_IND_T_MCC                               = 0x102,
    /* MNC */
    /* type = string */
    MIPC_SIM_SIMAPP_IND_T_MNC                               = 0x103,
};

    /* MIPC_MSG.SIM_TEST_SIM_IND */
enum mipc_sim_test_sim_ind_tlv_enum {
    mipc_sim_test_sim_ind_tlv_NONE = 0,
    /* is testsim or not */
    /* type = uint8_t */
    MIPC_SIM_TEST_SIM_IND_T_TEST_SIM                        = 0x100,
};

    /* MIPC_MSG.SIM_CT3G_IND */
enum mipc_sim_ct3g_ind_tlv_enum {
    mipc_sim_ct3g_ind_tlv_NONE = 0,
    /* is CT3G or not */
    /* type = uint8_t */
    MIPC_SIM_CT3G_IND_T_TYPE                                = 0x100,
};

    /* MIPC_MSG.SIM_CARD_TYPE_IND */
enum mipc_sim_card_type_ind_tlv_enum {
    mipc_sim_card_type_ind_tlv_NONE = 0,
    /* SIM/USIM state */
    /* type = uint8_t */
    MIPC_SIM_CARD_TYPE_IND_T_USIM_STATE                     = 0x100,
    /* UIM/CSIM state */
    /* type = uint8_t */
    MIPC_SIM_CARD_TYPE_IND_T_CSIM_STATE                     = 0x101,
    /* ISIM state */
    /* type = uint8_t */
    MIPC_SIM_CARD_TYPE_IND_T_ISIM_STATE                     = 0x102,
};

    /* MIPC_MSG.SIM_SIMIND_IND */
enum mipc_sim_simind_ind_tlv_enum {
    mipc_sim_simind_ind_tlv_NONE = 0,
    /* event type */
    /* type = uint8_t */
    MIPC_SIM_SIMIND_IND_T_EVENT                             = 0x100,
    /*  app id */
    /* type = uint8_t */
    MIPC_SIM_SIMIND_IND_T_APP_ID                            = 0x101,
    /* SPN string */
    /* type = string */
    MIPC_SIM_SIMIND_IND_T_SPN                               = 0x102,
    /* imsi string */
    /* type = string */
    MIPC_SIM_SIMIND_IND_T_IMSI                              = 0x8103,
    /* GID1 string */
    /* type = string */
    MIPC_SIM_SIMIND_IND_T_GID1                              = 0x104,
    /* PNN full name string */
    /* type = string */
    MIPC_SIM_SIMIND_IND_T_PNN_FULL_NAME                     = 0x105,
    /* IMPI string */
    /* type = string */
    MIPC_SIM_SIMIND_IND_T_IMPI                              = 0x106,
    /* file number, max 10 */
    /* type = uint8_t */
    MIPC_SIM_SIMIND_IND_T_FILE_NUM                          = 0x107,
    /* file list */
    /* type = struct_array, refer to file_list */
    MIPC_SIM_SIMIND_IND_T_FILE_LIST                         = 0x8108,
};

    /* MIPC_MSG.SIM_STATUS_CHANGED_IND */
enum mipc_sim_status_changed_ind_tlv_enum {
    mipc_sim_status_changed_ind_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SMS_CFG_IND */
enum mipc_sms_cfg_ind_tlv_enum {
    mipc_sms_cfg_ind_tlv_NONE = 0,
    /* indicate the format that configured for this protocal. PDU or TEXT */
    /* type = uint8_t, refer to SMS_FORMAT */
    MIPC_SMS_CFG_IND_T_FORMAT                               = 0x100,
    /* [3GPP] indicate the SCA(sms center address) that configured for this protocal */
    /* type = string */
    MIPC_SMS_CFG_IND_T_SCA                                  = 0x8101,
    /* indicate if the sms module is initialized */
    /* type = uint8_t, refer to SMS_STATE */
    MIPC_SMS_CFG_IND_T_SMS_STATE                            = 0x102,
    /* [3GPP] indicate the max messages that can be saved in this protocal */
    /* type = uint16_t */
    MIPC_SMS_CFG_IND_T_MAX_MESSAGE                          = 0x103,
    /* indicate if user want to ack for the new sms to TE, save in SIM would not need ack from user */
    /* type = uint8_t, refer to SMS_ACK */
    MIPC_SMS_CFG_IND_T_PREFER_ACK                           = 0x104,
    /* indicate which storage user want to save mt sms */
    /* type = uint8_t, refer to SMS_STORAGE */
    MIPC_SMS_CFG_IND_T_PREFER_STORAGE                       = 0x105,
    /* [3GPP]indicate the used messages number saved in this protocal */
    /* type = uint16_t */
    MIPC_SMS_CFG_IND_T_USED_MESSAGE                         = 0x106,
    /* [PHASE OUT] */
    /* type = uint8_t, refer to SMS_STORAGE */
    MIPC_SMS_CFG_IND_T_PREFER_STORAGE_C2K                   = 0x107,
    /* [PHASE OUT] */
    /* type = uint16_t */
    MIPC_SMS_CFG_IND_T_USED_MESSAGE_C2K                     = 0x108,
    /* [PHASE OUT] */
    /* type = uint16_t */
    MIPC_SMS_CFG_IND_T_MAX_MESSAGE_C2K                      = 0x109,
    /* [3GPP]where to do read/write/delete operation for 3gpp format sms? No W_R_D_STORAGE for 3GPP2 because 3gpp2 always UIM and couldn't be changed */
    /* type = uint8_t, refer to SMS_STORAGE */
    MIPC_SMS_CFG_IND_T_W_R_D_STORAGE                        = 0x10A,
};

    /* MIPC_MSG.SMS_NEW_SMS_IND */
enum mipc_sms_new_sms_ind_tlv_enum {
    mipc_sms_new_sms_ind_tlv_NONE = 0,
    /* the format of this sms. PDU_3GPP or PDU_3GPP2 */
    /* type = uint8_t, refer to SMS_FORMAT */
    MIPC_SMS_NEW_SMS_IND_T_FORMAT                           = 0x100,
    /* [PDU_3GPP] should be 1 in this case */
    /* type = uint16_t */
    MIPC_SMS_NEW_SMS_IND_T_PDU_COUNT                        = 0x103,
    /* [PDU_3GPP] */
    /* type = struct_array, refer to sms_pdu */
    MIPC_SMS_NEW_SMS_IND_T_PDU_LIST                         = 0x8104,
    /* [PDU_3GPP2]valid when 3gpp2 format */
    /* type = byte_array */
    MIPC_SMS_NEW_SMS_IND_T_PDU_C2K                          = 0x8105,
};

    /* MIPC_MSG.SMS_STORE_STATUS_IND */
enum mipc_sms_store_status_ind_tlv_enum {
    mipc_sms_store_status_ind_tlv_NONE = 0,
    /* indicate if <the storage full> or <new sms in DEVICE received> */
    /* type = bitmap, refer to SMS_STORE_FLAG */
    MIPC_SMS_STORE_STATUS_IND_T_FLAG                        = 0x100,
    /* if the falg indicated there is new message, this shows the message_index */
    /* type = uint16_t */
    MIPC_SMS_STORE_STATUS_IND_T_MESSAGE_INDEX               = 0x101,
};

    /* MIPC_MSG.SMS_NEW_STATUS_REPORT_IND */
enum mipc_sms_new_status_report_ind_tlv_enum {
    mipc_sms_new_status_report_ind_tlv_NONE = 0,
    /* [PDU_3GPP]pdu detail info, lenght is controled by PDU_LEN */
    /* type = byte_array */
    MIPC_SMS_NEW_STATUS_REPORT_IND_T_PDU                    = 0x8100,
};

    /* MIPC_MSG.SMS_NEW_CBM_IND */
enum mipc_sms_new_cbm_ind_tlv_enum {
    mipc_sms_new_cbm_ind_tlv_NONE = 0,
    /* [3GPP]cbm type indication,show the type of cbm message in this indication */
    /* type = bitmap, refer to SMS_CBM_TYPE */
    MIPC_SMS_NEW_CBM_IND_T_CBM_TYPE                         = 0x100,
    /* [3GPP][ETWS_PRIMARY only]refer TS23.041 9.3.24 for more information */
    /* type = uint16_t */
    MIPC_SMS_NEW_CBM_IND_T_WARNING_TYPE                     = 0x101,
    /* [3GPP]refer TS23.041 9.4.1.2.2 for more information; [3GPP2]service category */
    /* type = uint16_t */
    MIPC_SMS_NEW_CBM_IND_T_MESSAGE_ID                       = 0x102,
    /* [3GPP]refer TS23.041 9.4.1.2.1 for more information */
    /* type = uint16_t */
    MIPC_SMS_NEW_CBM_IND_T_SERIAL_NUMBER                    = 0x103,
    /* [3GPP]refer TS23.041 9.4.2.2.4 for more information, invalid when CBM_TYPE=ETWS_PRIMARY; [3GPP2]language indicator */
    /* type = uint8_t */
    MIPC_SMS_NEW_CBM_IND_T_DCS                              = 0x104,
    /* [3GPP]refer TS23.041 9.4.2.2.5 for more information, invalid when CBM_TYPE=ETWS_PRIMARY */
    /* type = byte_array */
    MIPC_SMS_NEW_CBM_IND_T_DATA                             = 0x8105,
    /* [3GPP]refer TS23.041 9.4.1.3.6 for more information, only valid in CBM_TYPE=ETWS_PRIMARY */
    /* type = byte_array */
    MIPC_SMS_NEW_CBM_IND_T_SECUR_INFO                       = 0x106,
    /* only pdu_3gpp or pdu_3gpp2 */
    /* type = uint8_t, refer to SMS_FORMAT */
    MIPC_SMS_NEW_CBM_IND_T_FORMAT                           = 0x107,
    /* [3GPP2]refer CS0015 table 3.4.2.2-1 with 0x01 prefix */
    /* type = byte_array */
    MIPC_SMS_NEW_CBM_IND_T_PDU_C2K                          = 0x108,
    /* [3GPP]refer +CBM for more info, exist when PDU_3GPP_SEG_ENABLE set before */
    /* type = byte_array */
    MIPC_SMS_NEW_CBM_IND_T_PDU_3GPP_SEG                     = 0x109,
    /* Warning Area Coordinates info, refer ATIS-0700041 */
    /* type = byte_array */
    MIPC_SMS_NEW_CBM_IND_T_WAC_INFO                         = 0x10A
};

    /* MIPC_MSG.SMS_SCBM_IND */
enum mipc_sms_scbm_ind_tlv_enum {
    mipc_sms_scbm_ind_tlv_NONE = 0,
    /* indicate the SCBM status in DEVICE */
    /* type = uint8_t, refer to SMS_SCBM_STATUS */
    MIPC_SMS_SCBM_IND_T_STATUS_UPDATE                       = 0x100,
};

    /* MIPC_MSG.SMS_EXT_INFO_IND */
enum mipc_sms_ext_info_ind_tlv_enum {
    mipc_sms_ext_info_ind_tlv_NONE = 0,
    /* [wtcfm] more info to comment, log shows that ims recv with this URC, show a sip:xxx */
    /* type = string */
    MIPC_SMS_EXT_INFO_IND_T_EPSI                            = 0x100,
    /* Electronic Serial Num. 8 byte */
    /* type = byte_array */
    MIPC_SMS_EXT_INFO_IND_T_ESN_OLD                         = 0x101,
    /* Electronic Serial Num. 8 byte */
    /* type = byte_array */
    MIPC_SMS_EXT_INFO_IND_T_ESN_NEW                         = 0x102,
};

    /* MIPC_MSG.SS_USSD_IND */
enum mipc_ss_ussd_ind_tlv_enum {
    mipc_ss_ussd_ind_tlv_NONE = 0,
    /* ussd response */
    /* type = uint8_t, refer to SS_USSD */
    MIPC_SS_USSD_IND_T_USSD_RESPONSE                        = 0x100,
    /* ussd session state */
    /* type = uint8_t, refer to SS_SESSION */
    MIPC_SS_USSD_IND_T_USSD_SESSION_STATE                   = 0x101,
    /* data coding scheme */
    /* type = uint32_t */
    MIPC_SS_USSD_IND_T_DCS                                  = 0x102,
    /* length of payload */
    /* type = uint8_t */
    MIPC_SS_USSD_IND_T_PAYLOAD_LEN                          = 0x103,
    /* payload pointer */
    /* type = byte_array */
    MIPC_SS_USSD_IND_T_PAYLOAD                              = 0x104,
};

    /* MIPC_MSG.SS_ECMCCSS_IND */
enum mipc_ss_ecmccss_ind_tlv_enum {
    mipc_ss_ecmccss_ind_tlv_NONE = 0,
    /* the id of current call */
    /* type = uint32_t */
    MIPC_SS_ECMCCSS_IND_T_CALL_ID                           = 0x100,
    /* urc type */
    /* type = uint32_t */
    MIPC_SS_ECMCCSS_IND_T_SERVICE                           = 0x101,
    /* the raw string of ecmccss */
    /* type = string */
    MIPC_SS_ECMCCSS_IND_T_RAW_STRING                        = 0x102,
};

    /* MIPC_MSG.SS_CFU_IND */
enum mipc_ss_cfu_ind_tlv_enum {
    mipc_ss_cfu_ind_tlv_NONE = 0,
    /* the status of cfu icon */
    /* type = uint8_t, refer to SS_ECFU_ICON_STATUS */
    MIPC_SS_CFU_IND_T_STATUS                                = 0x100,
    /* the line info */
    /* type = uint8_t */
    MIPC_SS_CFU_IND_T_LINE                                  = 0x101,
};

    /* MIPC_MSG.SS_XCAP_RCN_IND */
enum mipc_ss_xcap_rcn_ind_tlv_enum {
    mipc_ss_xcap_rcn_ind_tlv_NONE = 0,
    /* the xcap response code */
    /* type = uint32_t */
    MIPC_SS_XCAP_RCN_IND_T_CODE                             = 0x100,
    /* change code to response */
    /* type = uint8_t */
    MIPC_SS_XCAP_RCN_IND_T_RESPONSE                         = 0x101,
};

    /* MIPC_MSG.SS_IMS_XUI_IND */
enum mipc_ss_ims_xui_ind_tlv_enum {
    mipc_ss_ims_xui_ind_tlv_NONE = 0,
    /* the account number */
    /* type = uint8_t */
    MIPC_SS_IMS_XUI_IND_T_ACCOUNT_ID                        = 0x100,
    /* broadcast flag */
    /* type = uint8_t */
    MIPC_SS_IMS_XUI_IND_T_BROADCAST_FLAG                    = 0x101,
    /* Xui information */
    /* type = string */
    MIPC_SS_IMS_XUI_IND_T_XUI_INFO                          = 0x8102,
};

    /* MIPC_MSG.STK_PAC_IND */
enum mipc_stk_pac_ind_tlv_enum {
    mipc_stk_pac_ind_tlv_NONE = 0,
    /* proactive command type from UICC */
    /* type = uint8_t, refer to STK_PAC_TYPE */
    MIPC_STK_PAC_IND_T_PAC_TYPE                             = 0x100,
    /* length of proactive command */
    /* type = uint16_t */
    MIPC_STK_PAC_IND_T_PAC_LEN                              = 0x101,
    /* pointer to proactive command payload */
    /* type = byte_array */
    MIPC_STK_PAC_IND_T_PAC                                  = 0x8102,
};

    /* MIPC_MSG.STK_SIM_REFRESH_IND */
enum mipc_stk_sim_refresh_ind_tlv_enum {
    mipc_stk_sim_refresh_ind_tlv_NONE = 0,
    /* the result of sim refresh */
    /* type = uint8_t, refer to SIM_REFRESH_RESULT_TYPE */
    MIPC_STK_SIM_REFRESH_IND_T_SIM_REFRESH_RESULT           = 0x100,
    /* ef id of the updated file */
    /* type = uint32_t */
    MIPC_STK_SIM_REFRESH_IND_T_EF_ID                        = 0x101,
    /* aid of application caused refresh */
    /* type = string */
    MIPC_STK_SIM_REFRESH_IND_T_AID                          = 0x102,
};

    /* MIPC_MSG.STK_BIP_EVENT_NOTIFY_IND */
enum mipc_stk_bip_event_notify_ind_tlv_enum {
    mipc_stk_bip_event_notify_ind_tlv_NONE = 0,
    /* bip command */
    /* type = string */
    MIPC_STK_BIP_EVENT_NOTIFY_IND_T_CMD_DATA                = 0x100,
};

    /* MIPC_MSG.CALL_STATUS_IND */
enum mipc_call_status_ind_tlv_enum {
    mipc_call_status_ind_tlv_NONE = 0,
    /* call ID */
    /* type = uint32_t */
    MIPC_CALL_STATUS_IND_T_CALLID                           = 0x100,
    /* type = uint32_t, refer to CALL_DIRECTION */
    MIPC_CALL_STATUS_IND_T_DIRECTION                        = 0x101,
    /* type = uint32_t, refer to CALL_MODE */
    MIPC_CALL_STATUS_IND_T_MODE                             = 0x102,
    /* type of address (refer TS 24.008 [8] subclause 10.5.4.7) */
    /* type = uint32_t */
    MIPC_CALL_STATUS_IND_T_TON                              = 0x103,
    /* type = string */
    MIPC_CALL_STATUS_IND_T_NUMBER                           = 0x8104,
    /* type = bitmap, refer to CALL_TYPE */
    MIPC_CALL_STATUS_IND_T_TYPE                             = 0x105,
    /* type = struct, refer to call_detail_info */
    MIPC_CALL_STATUS_IND_T_DETAIL_INFO                      = 0x8106,
    /* type = struct, refer to call_video_cap */
    MIPC_CALL_STATUS_IND_T_VIDEO_CAP                        = 0x107,
    /* the message type */
    /* type = uint32_t, refer to CALL_MSG_TYPE */
    MIPC_CALL_STATUS_IND_T_MSG_TYPE                         = 0x109,
    /* This information is only provided for MSG_TYPE=DISCONNECT, which is sent when modem receive RELEASE ir RELEAS COMPLETE CC nessage from the network. It is defined in SPEC 24.008 Annex H. */
    /* type = uint32_t */
    MIPC_CALL_STATUS_IND_T_DISC_CAUSE                       = 0x10A,
    /* type = string */
    MIPC_CALL_STATUS_IND_T_PAU                              = 0x810B,
};

    /* MIPC_MSG.CALL_EVENT_IND */
enum mipc_call_event_ind_tlv_enum {
    mipc_call_event_ind_tlv_NONE = 0,
    /* call event */
    /* type = uint32_t, refer to CALL_EVENT */
    MIPC_CALL_EVENT_IND_T_EVENT                             = 0x100,
    /* the reason of call reject (when EVENT=MT_REJECT) */
    /* type = uint32_t, refer to CALL_REJECT_REASON */
    MIPC_CALL_EVENT_IND_T_REJECT_REASON                     = 0x10B,
    /* the handover information (when EVENT=SRVCC) */
    /* type = uint32_t */
    MIPC_CALL_EVENT_IND_T_SRVCCH                            = 0x115,
    /* the handover information (when EVENT=MT_REDIRECT) */
    /* type = string */
    MIPC_CALL_EVENT_IND_T_REDIRECT_NUMBER                   = 0x811F,
    /* the current voice codec (when EVENT=AUDIO_CODEC_CHANGE) */
    /* type = uint16_t, refer to CALL_AUDIO_CODEC */
    MIPC_CALL_EVENT_IND_T_AUDIO_CODEC                       = 0x129,
    /* the current voice codec (when EVENT=SPEECH_ATTACH) */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_CALL_EVENT_IND_T_SPEECH_ON                         = 0x133,
    /* the current voice codec (when EVENT=SPEECH_ATTACH) */
    /* type = uint32_t, refer to SPEECH_RAT */
    MIPC_CALL_EVENT_IND_T_SPEECH_RAT                        = 0x134,
    /* the current voice codec (when EVENT=SPEECH_ATTACH) */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_CALL_EVENT_IND_T_SPEECH_IRHO_ON                    = 0x135,
    /* the current call rat (when EVENT=RAT) */
    /* type = uint8_t, refer to CALL_RAT */
    MIPC_CALL_EVENT_IND_T_RAT                               = 0x13C,
    /* the call num (when EVENT=ECONFSRVCC) */
    /* type = uint32_t */
    MIPC_CALL_EVENT_IND_T_COUNT                             = 0x15B,
    /* the call id (when EVENT=ECONFSRVCC) */
    /* type = uint32_t */
    MIPC_CALL_EVENT_IND_T_CALL_ID                           = 0x15C,
};

    /* MIPC_MSG.CALL_MODE_IND */
enum mipc_call_mode_ind_tlv_enum {
    mipc_call_mode_ind_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_CALL_MODE_IND_T_CALLID                             = 0x100,
    /* type = uint32_t, refer to CALL_MODE */
    MIPC_CALL_MODE_IND_T_MODE                               = 0x101,
    /* type = uint32_t, refer to SDP_DIRECTION */
    MIPC_CALL_MODE_IND_T_SDP_CAMERA_DIRECTION               = 0x102,
    /* type = uint32_t, refer to SDP_DIRECTION */
    MIPC_CALL_MODE_IND_T_SDP_AUDIO_DIRECTION                = 0x103,
    /* type = uint32_t, refer to SDP_AUDIO_CODEC */
    MIPC_CALL_MODE_IND_T_SDP_AUDIO_CODEC                    = 0x104,
};

    /* MIPC_MSG.CALL_SIP_IND */
enum mipc_call_sip_ind_tlv_enum {
    mipc_call_sip_ind_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_CALL_SIP_IND_T_CALLID                              = 0x100,
    /* type = uint32_t, refer to SIP_DIRECTION */
    MIPC_CALL_SIP_IND_T_DIRECTION                           = 0x101,
    /* type = uint32_t, refer to SIP_MSG_TYPE */
    MIPC_CALL_SIP_IND_T_MSG_TYPE                            = 0x102,
    /* only used when MSG_TYPE=REQUEST */
    /* type = uint32_t, refer to SIP_METHOD */
    MIPC_CALL_SIP_IND_T_METHOD                              = 0x103,
    /* only used when MSG_TYPE=RESPONSE */
    /* type = uint32_t */
    MIPC_CALL_SIP_IND_T_RESPONSE_CODE                       = 0x104,
    /* reason header field in SIP message */
    /* type = string */
    MIPC_CALL_SIP_IND_T_REASON_TEXT                         = 0x105,
};

    /* MIPC_MSG.CALL_CONFERENCE_IND */
enum mipc_call_conference_ind_tlv_enum {
    mipc_call_conference_ind_tlv_NONE = 0,
    /* the conference cal id */
    /* type = uint32_t */
    MIPC_CALL_CONFERENCE_IND_T_CONF_CALLID                  = 0x100,
    /* type = uint32_t */
    MIPC_CALL_CONFERENCE_IND_T_COUNT                        = 0x101,
    /* type = uint32_t, refer to CALL_DIRECTION */
    MIPC_CALL_CONFERENCE_IND_T_DIRECTION                    = 0x10B,
    /* call number */
    /* type = string */
    MIPC_CALL_CONFERENCE_IND_T_PARTICIPANT_NUMBER           = 0x810C,
    /* type = string */
    MIPC_CALL_CONFERENCE_IND_T_PARTICIPANT_NAME             = 0x810D,
    /* type = uint32_t, refer to CONF_PARTICIPANT_STATUS */
    MIPC_CALL_CONFERENCE_IND_T_PARTICIPANT_STATUS           = 0x10E,
    /* call user entity string */
    /* type = string */
    MIPC_CALL_CONFERENCE_IND_T_PARTICIPANT_USER_ENTITY      = 0x10F,
    /* call endpoint entity string */
    /* type = string */
    MIPC_CALL_CONFERENCE_IND_T_PARTICIPANT_ENDPOINT_ENTITY  = 0x110,
};

    /* MIPC_MSG.CALL_IMS_EVENT_PACKAGE_IND */
enum mipc_call_ims_event_package_ind_tlv_enum {
    mipc_call_ims_event_package_ind_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_CALL_IMS_EVENT_PACKAGE_IND_T_CALLID                = 0x100,
    /* type = uint32_t, refer to IMS_EVENT_PACKAGE_TYPE */
    MIPC_CALL_IMS_EVENT_PACKAGE_IND_T_TYPE                  = 0x101,
    /* type = string */
    MIPC_CALL_IMS_EVENT_PACKAGE_IND_T_DATA                  = 0x8102,
};

    /* MIPC_MSG.CALL_ECC_LIST_CHANGE_IND */
enum mipc_call_ecc_list_change_ind_tlv_enum {
    mipc_call_ecc_list_change_ind_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.CALL_SS_IND */
enum mipc_call_ss_ind_tlv_enum {
    mipc_call_ss_ind_tlv_NONE = 0,
    /* it is manufacturer specific, which of these codes are supported */
    /* type = uint32_t, refer to CALL_SS_CODE1 */
    MIPC_CALL_SS_IND_T_CODE1                                = 0x100,
    /* it is manufacturer specific, which of these codes are supported */
    /* type = uint32_t, refer to CALL_SS_CODE2 */
    MIPC_CALL_SS_IND_T_CODE2                                = 0x101,
    /* it is manufacturer specific, which of these codes are supported */
    /* type = uint32_t */
    MIPC_CALL_SS_IND_T_INDEX                                = 0x102,
    /* type = string */
    MIPC_CALL_SS_IND_T_NUMBER                               = 0x8103,
    /* type of address (refer TS 24.008 [8] subclause 10.5.4.7) */
    /* type = uint32_t */
    MIPC_CALL_SS_IND_T_TOA                                  = 0x104,
    /* string type subaddress of format specified by SATYPE */
    /* type = string */
    MIPC_CALL_SS_IND_T_SUBADDR                              = 0x105,
    /* type of subaddress octet in integer format (refer TS 24.008 [8] subclause 10.5.4.8) */
    /* type = uint32_t */
    MIPC_CALL_SS_IND_T_SATYPE                               = 0x106,
    /* Supplementary service notification, URC: +ECMCCSS */
    /* type = string */
    MIPC_CALL_SS_IND_T_RAW_STRING                           = 0x8107,
};

    /* MIPC_MSG.CALL_ECBM_CHANGE_IND */
enum mipc_call_ecbm_change_ind_tlv_enum {
    mipc_call_ecbm_change_ind_tlv_NONE = 0,
    /* type = uint8_t, refer to CALL_ECBM_MODE */
    MIPC_CALL_ECBM_CHANGE_IND_T_MODE                        = 0x100,
};

    /* MIPC_MSG.CALL_CRSS_IND */
enum mipc_call_crss_ind_tlv_enum {
    mipc_call_crss_ind_tlv_NONE = 0,
    /* type of CRSS IND */
    /* type = uint8_t, refer to CRSS_TYPE */
    MIPC_CALL_CRSS_IND_T_CRSS_TYPE                          = 0x100,
    /* string type phone number of format specified by <type> */
    /* type = string */
    MIPC_CALL_CRSS_IND_T_NUMBER                             = 0x8101,
    /* type of address octet in integer format (refer TS 24.008 [8] subclause 10.5.4.7) */
    /* type = uint8_t, refer to NUMBER_TYPE */
    MIPC_CALL_CRSS_IND_T_CALL_NUMBER_TYPE                   = 0x102,
    /* indicates number presentation */
    /* type = uint8_t, refer to NUMBER_PRESENTATION */
    MIPC_CALL_CRSS_IND_T_NUMBER_PRESENTATION                = 0x103,
    /* string type subaddress of format specified by <satype> */
    /* type = string */
    MIPC_CALL_CRSS_IND_T_SUB_ADDRESS                        = 0x8104,
    /* type of subaddress octet in integer format (refer TS 24.008 [8] subclause 10.5.4.8) */
    /* type = uint8_t */
    MIPC_CALL_CRSS_IND_T_SA_TYPE                            = 0x105,
    /* type = string */
    MIPC_CALL_CRSS_IND_T_ALPHAID                            = 0x8106,
    /* string type caller name */
    /* type = string */
    MIPC_CALL_CRSS_IND_T_NAME                               = 0x8107,
};

    /* MIPC_MSG.CALL_ECT_IND */
enum mipc_call_ect_ind_tlv_enum {
    mipc_call_ect_ind_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_CALL_ECT_IND_T_CALL_ID                             = 0x100,
    /* FALSE: fail; TRUE: success */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_CALL_ECT_IND_T_ECT_RESULT                          = 0x101,
    /* type = uint32_t */
    MIPC_CALL_ECT_IND_T_CAUSE                               = 0x102,
};

    /* MIPC_MSG.CALL_CIPHER_IND */
enum mipc_call_cipher_ind_tlv_enum {
    mipc_call_cipher_ind_tlv_NONE = 0,
    /* FALSE: do not show cipher indication; TRUE:show cipher indication */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_CALL_CIPHER_IND_T_SIM_CIPHER_IND                   = 0x100,
    /* FALSE: no connection; TRUE:has connection */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_CALL_CIPHER_IND_T_MM_CONNECTION                    = 0x101,
    /* type = uint8_t, refer to CALL_CIPHER_ON_STATUS */
    MIPC_CALL_CIPHER_IND_T_CS_CIPHER_ON                     = 0x102,
    /* type = uint8_t, refer to CALL_CIPHER_ON_STATUS */
    MIPC_CALL_CIPHER_IND_T_PS_CIPHER_ON                     = 0x103,
};

    /* MIPC_MSG.CALL_RTT_AUDIO_IND */
enum mipc_call_rtt_audio_ind_tlv_enum {
    mipc_call_rtt_audio_ind_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_CALL_RTT_AUDIO_IND_T_CALL_ID                       = 0x100,
    /* type = uint8_t, refer to CALL_RTT_AUDIO_TYPE */
    MIPC_CALL_RTT_AUDIO_IND_T_TYPE                          = 0x101,
};

    /* MIPC_MSG.CALL_RTT_CAPABILITY_IND */
enum mipc_call_rtt_capability_ind_tlv_enum {
    mipc_call_rtt_capability_ind_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_CALL_RTT_CAPABILITY_IND_T_CALL_ID                  = 0x100,
    /* type = uint8_t */
    MIPC_CALL_RTT_CAPABILITY_IND_T_LOCAL_TEXT_CAPABILITY    = 0x101,
    /* type = uint8_t */
    MIPC_CALL_RTT_CAPABILITY_IND_T_REMOTE_TEXT_CAPABILITY   = 0x102,
    /* type = uint8_t */
    MIPC_CALL_RTT_CAPABILITY_IND_T_LOCAL_TEXT_STATUS        = 0x103,
    /* type = uint8_t */
    MIPC_CALL_RTT_CAPABILITY_IND_T_REAL_REMOTE_TEXT_CAPABILITY = 0x104,
};

    /* MIPC_MSG.CALL_LOCAL_RTT_MODIFY_RESULT_IND */
enum mipc_call_local_rtt_modify_result_ind_tlv_enum {
    mipc_call_local_rtt_modify_result_ind_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_CALL_LOCAL_RTT_MODIFY_RESULT_IND_T_CALL_ID         = 0x100,
    /* type = uint8_t */
    MIPC_CALL_LOCAL_RTT_MODIFY_RESULT_IND_T_RESULT          = 0x101,
};

    /* MIPC_MSG.CALL_PEER_RTT_MODIFY_RESULT_IND */
enum mipc_call_peer_rtt_modify_result_ind_tlv_enum {
    mipc_call_peer_rtt_modify_result_ind_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_CALL_PEER_RTT_MODIFY_RESULT_IND_T_CALL_ID          = 0x100,
    /* type = uint8_t, refer to CALL_LOCAL_RTT_MODIFY_OP */
    MIPC_CALL_PEER_RTT_MODIFY_RESULT_IND_T_OP               = 0x101,
};

    /* MIPC_MSG.CALL_RTT_TEXT_RECEIVE_IND */
enum mipc_call_rtt_text_receive_ind_tlv_enum {
    mipc_call_rtt_text_receive_ind_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_CALL_RTT_TEXT_RECEIVE_IND_T_CALL_ID                = 0x100,
    /* type = uint32_t */
    MIPC_CALL_RTT_TEXT_RECEIVE_IND_T_LEN                    = 0x101,
    /* type = string */
    MIPC_CALL_RTT_TEXT_RECEIVE_IND_T_TEXT                   = 0x102,
};

    /* MIPC_MSG.CALL_RCS_DIGITS_LINE_IND */
enum mipc_call_rcs_digits_line_ind_tlv_enum {
    mipc_call_rcs_digits_line_ind_tlv_NONE = 0,
    /* type = string */
    MIPC_CALL_RCS_DIGITS_LINE_IND_T_DIGITS_LINE             = 0x100,
};

    /* MIPC_MSG.CALL_DISPLAY_AND_SIGNALS_INFO_IND */
enum mipc_call_display_and_signals_info_ind_tlv_enum {
    mipc_call_display_and_signals_info_ind_tlv_NONE = 0,
    /* type = string */
    MIPC_CALL_DISPLAY_AND_SIGNALS_INFO_IND_T_DISPLAY        = 0x8100,
    /* type = uint32_t */
    MIPC_CALL_DISPLAY_AND_SIGNALS_INFO_IND_T_SIGNAL_TYPE    = 0x101,
    /* type = uint32_t */
    MIPC_CALL_DISPLAY_AND_SIGNALS_INFO_IND_T_ALERT_PITCH    = 0x102,
    /* type = uint32_t */
    MIPC_CALL_DISPLAY_AND_SIGNALS_INFO_IND_T_SIGNAL         = 0x103,
};

    /* MIPC_MSG.CALL_EXTENDED_DISPLAY_INFO_IND */
enum mipc_call_extended_display_info_ind_tlv_enum {
    mipc_call_extended_display_info_ind_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_CALL_EXTENDED_DISPLAY_INFO_IND_T_DISPLAY_TAG       = 0x100,
    /* type = string */
    MIPC_CALL_EXTENDED_DISPLAY_INFO_IND_T_INFO              = 0x8101,
};

    /* MIPC_MSG.CALL_LINE_CONTROL_INFO_IND */
enum mipc_call_line_control_info_ind_tlv_enum {
    mipc_call_line_control_info_ind_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_CALL_LINE_CONTROL_INFO_IND_T_POLARITY_INCLUDED     = 0x100,
    /* type = uint32_t */
    MIPC_CALL_LINE_CONTROL_INFO_IND_T_TOGGLE_MODE           = 0x101,
    /* type = uint32_t */
    MIPC_CALL_LINE_CONTROL_INFO_IND_T_REVERSE_POLARITY      = 0x102,
    /* type = uint32_t */
    MIPC_CALL_LINE_CONTROL_INFO_IND_T_POWER_DENIAL_TIME     = 0x103,
};

    /* MIPC_MSG.CALL_REDIRECTING_NUMBER_INFO_IND */
enum mipc_call_redirecting_number_info_ind_tlv_enum {
    mipc_call_redirecting_number_info_ind_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_CALL_REDIRECTING_NUMBER_INFO_IND_T_EXT_BIT_1       = 0x100,
    /* type = uint32_t */
    MIPC_CALL_REDIRECTING_NUMBER_INFO_IND_T_NUMBER_TYPE     = 0x101,
    /* type = uint32_t */
    MIPC_CALL_REDIRECTING_NUMBER_INFO_IND_T_NUMBER_PLAN     = 0x102,
    /* type = uint32_t */
    MIPC_CALL_REDIRECTING_NUMBER_INFO_IND_T_EXT_BIT_2       = 0x103,
    /* type = uint32_t */
    MIPC_CALL_REDIRECTING_NUMBER_INFO_IND_T_PI              = 0x104,
    /* type = uint32_t */
    MIPC_CALL_REDIRECTING_NUMBER_INFO_IND_T_SI              = 0x105,
    /* type = uint32_t */
    MIPC_CALL_REDIRECTING_NUMBER_INFO_IND_T_EXT_BIT_3       = 0x106,
    /* type = uint32_t */
    MIPC_CALL_REDIRECTING_NUMBER_INFO_IND_T_REDIRECTION_REASON = 0x107,
    /* type = string */
    MIPC_CALL_REDIRECTING_NUMBER_INFO_IND_T_NUMBER          = 0x8108,
};

    /* MIPC_MSG.CALL_GWSD_EVENT_IND */
enum mipc_call_gwsd_event_ind_tlv_enum {
    mipc_call_gwsd_event_ind_tlv_NONE = 0,
    /* gwsd event */
    /* type = uint32_t, refer to GWSD_EVENT */
    MIPC_CALL_GWSD_EVENT_IND_T_EVENT                        = 0x100,
    /* the call id (when EVENT=ECRFCPY) */
    /* type = uint32_t */
    MIPC_CALL_GWSD_EVENT_IND_T_CALL_ID                      = 0x10B,
    /* the update status (when EVENT=ECRFCPY) */
    /* type = uint32_t */
    MIPC_CALL_GWSD_EVENT_IND_T_UPDATE_STATUS                = 0x10C,
    /* the ton (when EVENT=EICPGU) */
    /* type = uint32_t */
    MIPC_CALL_GWSD_EVENT_IND_T_TON                          = 0x115,
    /* the number (when EVENT=EICPGU) */
    /* type = string */
    MIPC_CALL_GWSD_EVENT_IND_T_NUMBER                       = 0x8116,
    /* the result (when EVENT=EICPGRES) */
    /* type = uint32_t */
    MIPC_CALL_GWSD_EVENT_IND_T_RESULT                       = 0x11F,
};

    /* MIPC_MSG.CALL_ECONF_IND */
enum mipc_call_econf_ind_tlv_enum {
    mipc_call_econf_ind_tlv_NONE = 0,
    /* the conference call id (when EVENT=ECONF) */
    /* type = uint32_t */
    MIPC_CALL_ECONF_IND_T_CONF_CALL_ID                      = 0x100,
    /* the operation: 0=add, 1=remove (when EVENT=ECONF) */
    /* type = uint32_t */
    MIPC_CALL_ECONF_IND_T_OPERATION                         = 0x101,
    /* the number (when EVENT=ECONF) */
    /* type = string */
    MIPC_CALL_ECONF_IND_T_NUMBER                            = 0x8102,
    /* the econf result (when EVENT=ECONF) */
    /* type = uint32_t */
    MIPC_CALL_ECONF_IND_T_RESULT                            = 0x103,
    /* the econf failed cause (when EVENT=ECONF) */
    /* type = uint32_t */
    MIPC_CALL_ECONF_IND_T_CAUSE                             = 0x104,
    /* the joined call id (when EVENT=ECONF) */
    /* type = uint32_t */
    MIPC_CALL_ECONF_IND_T_JOINED_CALL_ID                    = 0x105,
};

    /* MIPC_MSG.CALL_IMS_SIP_HEADER_IND */
enum mipc_call_ims_sip_header_ind_tlv_enum {
    mipc_call_ims_sip_header_ind_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_CALL_IMS_SIP_HEADER_IND_T_CALL_ID                  = 0x100,
    /* type = uint32_t */
    MIPC_CALL_IMS_SIP_HEADER_IND_T_HEADER_TYPE              = 0x101,
    /* type = uint32_t */
    MIPC_CALL_IMS_SIP_HEADER_IND_T_TOTAL_COUNT              = 0x102,
    /* type = uint32_t */
    MIPC_CALL_IMS_SIP_HEADER_IND_T_INDEX                    = 0x103,
    /* type = string */
    MIPC_CALL_IMS_SIP_HEADER_IND_T_VALUE                    = 0x8104,
};

    /* MIPC_MSG.CALL_ECC_REDIAL_IND */
enum mipc_call_ecc_redial_ind_tlv_enum {
    mipc_call_ecc_redial_ind_tlv_NONE = 0,
    /* 0 means request AP to leave flight mode and 30 means NW request to dial CS normal call, others means call id */
    /* type = uint8_t */
    MIPC_CALL_ECC_REDIAL_IND_T_CALL_ID                      = 0x100,
};

    /* MIPC_MSG.CALL_EMERGENCY_BEARER_SUPPORT_IND */
enum mipc_call_emergency_bearer_support_ind_tlv_enum {
    mipc_call_emergency_bearer_support_ind_tlv_NONE = 0,
    /* Emergency bearer services support indicator for Iu mode */
    /* type = uint8_t, refer to EMERGENCY_CALL_S1_SUPPORT */
    MIPC_CALL_EMERGENCY_BEARER_SUPPORT_IND_T_S1_SUPPORT     = 0x100,
    /* notify AP the emergency service support status in the current cell  */
    /* type = uint8_t, refer to EMERGENCY_CALL_RAT */
    MIPC_CALL_EMERGENCY_BEARER_SUPPORT_IND_T_RAT            = 0x101,
    /* notify AP the emergency service support status in the current cell */
    /* type = uint8_t, refer to EMERGENCY_CALL_SUPPORT_EMC */
    MIPC_CALL_EMERGENCY_BEARER_SUPPORT_IND_T_SUPPORT_EMC    = 0x102,
    /* notify AP the emergency bearer services support indicator for Iu mode  */
    /* type = uint8_t, refer to EMERGENCY_CALL_EMB_IU_SUPP */
    MIPC_CALL_EMERGENCY_BEARER_SUPPORT_IND_T_EMB_IU_SUPP    = 0x103,
    /* notify AP the emergency services support in 5GS for 3GPP access */
    /* type = uint8_t, refer to EMERGENCY_CALL_EMS_5G_SUPP */
    MIPC_CALL_EMERGENCY_BEARER_SUPPORT_IND_T_EMS_5G_SUPP    = 0x104,
    /* notify AP the emergency services support in 5GS for 3GPP access */
    /* type = uint8_t, refer to EMERGENCY_CALL_EMF_5G_SUPP */
    MIPC_CALL_EMERGENCY_BEARER_SUPPORT_IND_T_EMF_5G_SUPP    = 0x105,
};

    /* MIPC_MSG.CALL_UIS_INFO_IND */
enum mipc_call_uis_info_ind_tlv_enum {
    mipc_call_uis_info_ind_tlv_NONE = 0,
    /* call ID */
    /* type = uint32_t */
    MIPC_CALL_UIS_INFO_IND_T_CALLID                         = 0x100,
    /* Indicates the type of the UIS Info */
    /* type = uint8_t, refer to CALL_UIS_INFO_TYPE */
    MIPC_CALL_UIS_INFO_IND_T_TYPE                           = 0x101,
    /* Indicates the detailed UIS Info in string format */
    /* type = string */
    MIPC_CALL_UIS_INFO_IND_T_DATA                           = 0x102,
    /* Only used by URC, indicates the final result of the AT command */
    /* type = uint8_t, refer to CALL_UIS_INFO_RESULT */
    MIPC_CALL_UIS_INFO_IND_T_RESULT                         = 0x103,
    /* Only used by URC, indicates the detailed cause */
    /* type = uint32_t, refer to CALL_UIS_INFO_CAUSE */
    MIPC_CALL_UIS_INFO_IND_T_CAUSE                          = 0x104,
};

    /* MIPC_MSG.CALL_CALL_ADDITIONAL_INFO_IND */
enum mipc_call_call_additional_info_ind_tlv_enum {
    mipc_call_call_additional_info_ind_tlv_NONE = 0,
    /* call ID */
    /* type = uint32_t */
    MIPC_CALL_CALL_ADDITIONAL_INFO_IND_T_CALLID             = 0x100,
    /* The call mode will be applied till next command to change call_mode. */
    /* type = uint8_t, refer to CALL_ADDITIONAL_INFO_MODE */
    MIPC_CALL_CALL_ADDITIONAL_INFO_IND_T_MODE               = 0x101,
    /* type = uint8_t, refer to CALL_ADDITIONAL_INFO_TYPE */
    MIPC_CALL_CALL_ADDITIONAL_INFO_IND_T_TYPE               = 0x102,
    /* total number of additinal info */
    /* type = uint32_t */
    MIPC_CALL_CALL_ADDITIONAL_INFO_IND_T_TOTAL              = 0x103,
    /* index of current additional info */
    /* type = uint32_t */
    MIPC_CALL_CALL_ADDITIONAL_INFO_IND_T_INDEX              = 0x104,
    /* number of key or key/value pair in additional info */
    /* type = uint32_t */
    MIPC_CALL_CALL_ADDITIONAL_INFO_IND_T_COUNT              = 0x105,
    /* type = string */
    MIPC_CALL_CALL_ADDITIONAL_INFO_IND_T_ADDITIONAL_INFO    = 0x8106,
};

    /* MIPC_MSG.CALL_MT_SIP_INVITE_IND */
enum mipc_call_mt_sip_invite_ind_tlv_enum {
    mipc_call_mt_sip_invite_ind_tlv_NONE = 0,
    /* remote MT's phone number */
    /* type = string */
    MIPC_CALL_MT_SIP_INVITE_IND_T_FROM_NUMBER               = 0x8100,
    /* total count of this MT SIP INVITE will be reported */
    /* type = uint8_t */
    MIPC_CALL_MT_SIP_INVITE_IND_T_TOTAL_COUNT               = 0x101,
    /* nth part of the all MT SIP INVITE */
    /* type = uint8_t */
    MIPC_CALL_MT_SIP_INVITE_IND_T_INDEX                     = 0x102,
    /* MT SIP INVITE message */
    /* type = string */
    MIPC_CALL_MT_SIP_INVITE_IND_T_MT_SIP_INVITE             = 0x8103,
};

    /* MIPC_MSG.IMS_CONFIG_IND */
enum mipc_ims_config_ind_tlv_enum {
    mipc_ims_config_ind_tlv_NONE = 0,
    /* the reason of ims configuration changed indication */
    /* type = uint8_t, refer to IMS_CONFIG_IND_REASON */
    MIPC_IMS_CONFIG_IND_T_REASON                            = 0x100,
    /* the reason of ims configuration changed indication */
    /* type = byte_array */
    MIPC_IMS_CONFIG_IND_T_CONFIG_DATA                       = 0x101,
};

    /* MIPC_MSG.IMS_STATE_IND */
enum mipc_ims_state_ind_tlv_enum {
    mipc_ims_state_ind_tlv_NONE = 0,
    /* the event of ims state changed indication */
    /* type = uint8_t, refer to IMS_STATE_IND_EVENT */
    MIPC_IMS_STATE_IND_T_EVENT                              = 0x100,
    /* the ims registration state */
    /* type = uint8_t */
    MIPC_IMS_STATE_IND_T_REG_STATE                          = 0x101,
    /* the ims registration ext info */
    /* type = uint32_t */
    MIPC_IMS_STATE_IND_T_EXT_INFO                           = 0x102,
    /* the ims wfc state */
    /* type = uint8_t */
    MIPC_IMS_STATE_IND_T_WFC                                = 0x103,
    /* the ims account id */
    /* type = uint32_t */
    MIPC_IMS_STATE_IND_T_ACCOUNT_ID                         = 0x104,
    /* the ims account id */
    /* type = byte_array */
    MIPC_IMS_STATE_IND_T_URI                                = 0x8105,
    /* expire time */
    /* type = uint32_t */
    MIPC_IMS_STATE_IND_T_EXPIRE_TIME                        = 0x106,
    /* error code */
    /* type = uint32_t */
    MIPC_IMS_STATE_IND_T_ERROR_CODE                         = 0x107,
    /* error message */
    /* type = string */
    MIPC_IMS_STATE_IND_T_ERROR_MESSAGE                      = 0x108,
};

    /* MIPC_MSG.IMS_SUPPORT_ECC_IND */
enum mipc_ims_support_ecc_ind_tlv_enum {
    mipc_ims_support_ecc_ind_tlv_NONE = 0,
    /* current cell rat */
    /* type = uint8_t, refer to IMS_ECC_IND_RAT */
    MIPC_IMS_SUPPORT_ECC_IND_T_RAT                          = 0x100,
    /* emergency service support status. 0: doesn't support, 1: support */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_IMS_SUPPORT_ECC_IND_T_SUPPORT_EMC                  = 0x101,
};

    /* MIPC_MSG.IMS_PDN_IND */
enum mipc_ims_pdn_ind_tlv_enum {
    mipc_ims_pdn_ind_tlv_NONE = 0,
    /* the type of indication, currently it is always notify */
    /* type = uint8_t, refer to IMS_IND_TYPE */
    MIPC_IMS_PDN_IND_T_IND_TYPE                             = 0x100,
    /* ims/emergency PDN id */
    /* type = uint32_t */
    MIPC_IMS_PDN_IND_T_ID                                   = 0x101,
    /* ims/emergency PDN state, activated or deactivated */
    /* type = uint8_t, refer to MIPC_CID_ACT_STATE */
    MIPC_IMS_PDN_IND_T_PDN_STATE                            = 0x102,
    /* APN type, it should be ims or emergency */
    /* type = uint32_t, refer to APN_TYPE */
    MIPC_IMS_PDN_IND_T_APN_TYPE                             = 0x103,
    /* network interface id */
    /* type = uint32_t */
    MIPC_IMS_PDN_IND_T_INTERFACE_ID                         = 0x104,
    /* ipv4 dns address count */
    /* type = uint8_t */
    MIPC_IMS_PDN_IND_T_V4_DNS_ADDR_COUNT                    = 0x105,
    /* ipv4 dns address struct list */
    /* type = struct_array, refer to data_v4_addr */
    MIPC_IMS_PDN_IND_T_V4_DNS_ADDR_LIST                     = 0x8106,
    /* ipv6 dns address count */
    /* type = uint8_t */
    MIPC_IMS_PDN_IND_T_V6_DNS_ADDR_COUNT                    = 0x107,
    /* ipv6 dns address struct list */
    /* type = struct_array, refer to data_v6_addr */
    MIPC_IMS_PDN_IND_T_V6_DNS_ADDR_LIST                     = 0x8108,
};

    /* MIPC_MSG.IMS_NAPTR_IND */
enum mipc_ims_naptr_ind_tlv_enum {
    mipc_ims_naptr_ind_tlv_NONE = 0,
    /* transaction id, 1~255 */
    /* type = uint8_t */
    MIPC_IMS_NAPTR_IND_T_TRANSACTION_ID                     = 0x100,
    /* mod id */
    /* type = string */
    MIPC_IMS_NAPTR_IND_T_MOD_ID                             = 0x101,
    /* FQDN */
    /* type = string */
    MIPC_IMS_NAPTR_IND_T_FQDN                               = 0x102,
};

    /* MIPC_MSG.IMS_REG_IND */
enum mipc_ims_reg_ind_tlv_enum {
    mipc_ims_reg_ind_tlv_NONE = 0,
    /* the ims registration state */
    /* type = uint8_t */
    MIPC_IMS_REG_IND_T_REG_STATE                            = 0x100,
    /* the ims registration type */
    /* type = uint8_t */
    MIPC_IMS_REG_IND_T_REG_TYPE                             = 0x101,
    /* the ims registration ext info */
    /* type = uint32_t */
    MIPC_IMS_REG_IND_T_EXT_INFO                             = 0x102,
    /* the ims dereg cause */
    /* type = uint8_t */
    MIPC_IMS_REG_IND_T_DEREG_CAUSE                          = 0x103,
    /* the ims retry */
    /* type = uint8_t */
    MIPC_IMS_REG_IND_T_IMS_RETRY                            = 0x104,
    /* the ims rat */
    /* type = uint8_t */
    MIPC_IMS_REG_IND_T_RAT                                  = 0x105,
    /* the ims sip uri type */
    /* type = uint8_t */
    MIPC_IMS_REG_IND_T_SIP_URI_TYPE                         = 0x106,
    /* the ims reg sub state */
    /* type = uint8_t, refer to IMS_STATE */
    MIPC_IMS_REG_IND_T_REG_SUB_STATE                        = 0x107,
};

    /* MIPC_MSG.IMS_SIP_REG_INFO_IND */
enum mipc_ims_sip_reg_info_ind_tlv_enum {
    mipc_ims_sip_reg_info_ind_tlv_NONE = 0,
    /* the ims esipreginfo account id */
    /* type = uint32_t */
    MIPC_IMS_SIP_REG_INFO_IND_T_ACCOUNT_ID                  = 0x100,
    /* the ims esipreginfo direction */
    /* type = string */
    MIPC_IMS_SIP_REG_INFO_IND_T_DIRECTION                   = 0x101,
    /* the ims esipreginfo sip msg type */
    /* type = string */
    MIPC_IMS_SIP_REG_INFO_IND_T_SIP_MSG_TYPE                = 0x102,
    /* the ims esipreginfo method */
    /* type = string */
    MIPC_IMS_SIP_REG_INFO_IND_T_METHOD                      = 0x103,
    /* the ims esipreginfo response code */
    /* type = uint32_t */
    MIPC_IMS_SIP_REG_INFO_IND_T_RESPONSE_CODE               = 0x104,
    /* the ims esipreginfo reason phrase */
    /* type = string */
    MIPC_IMS_SIP_REG_INFO_IND_T_REASON_PHRASE               = 0x105,
    /* the ims esipreginfo warn text */
    /* type = string */
    MIPC_IMS_SIP_REG_INFO_IND_T_WARN_TEXT                   = 0x106,
};

    /* MIPC_MSG.IMS_VOPS_IND */
enum mipc_ims_vops_ind_tlv_enum {
    mipc_ims_vops_ind_tlv_NONE = 0,
    /* the ims vops supported indication from the network */
    /* type = uint8_t */
    MIPC_IMS_VOPS_IND_T_NWIMSVOPS                           = 0x100,
};

    /* MIPC_MSG.IMS_REG_REMAIN_TIME_IND */
enum mipc_ims_reg_remain_time_ind_tlv_enum {
    mipc_ims_reg_remain_time_ind_tlv_NONE = 0,
    /* the ims register remain time */
    /* type = uint32_t */
    MIPC_IMS_REG_REMAIN_TIME_IND_T_REG_REMAIN_TIME          = 0x100,
    /* the sub remain time */
    /* type = uint32_t */
    MIPC_IMS_REG_REMAIN_TIME_IND_T_SUB_REMAIN_TIME          = 0x101,
};

    /* MIPC_MSG.IMS_UI_IND */
enum mipc_ims_ui_ind_tlv_enum {
    mipc_ims_ui_ind_tlv_NONE = 0,
    /* the ims icon advance display flag */
    /* type = uint8_t */
    MIPC_IMS_UI_IND_T_ICONFLAG                              = 0x100,
};

    /* MIPC_MSG.WFC_CELL_SIGNAL_IND */
enum mipc_wfc_cell_signal_ind_tlv_enum {
    mipc_wfc_cell_signal_ind_tlv_NONE = 0,
    /* witch SIGNAL_TYPE this indication is for */
    /* type = uint8_t, refer to WFC_SIGNAL_TYPE */
    MIPC_WFC_CELL_SIGNAL_IND_T_SIGNAL_TYPE                  = 0x100,
    /* unit:dbm */
    /* type = int16_t */
    MIPC_WFC_CELL_SIGNAL_IND_T_VALUE                        = 0x101,
};

    /* MIPC_MSG.WFC_WIFI_PDN_COUNT_IND */
enum mipc_wfc_wifi_pdn_count_ind_tlv_enum {
    mipc_wfc_wifi_pdn_count_ind_tlv_NONE = 0,
    /* count */
    /* type = uint8_t */
    MIPC_WFC_WIFI_PDN_COUNT_IND_T_COUNT                     = 0x100,
};

    /* MIPC_MSG.WFC_PDN_HO_IND */
enum mipc_wfc_pdn_ho_ind_tlv_enum {
    mipc_wfc_pdn_ho_ind_tlv_NONE = 0,
    /* pdn type */
    /* type = uint8_t, refer to WFC_PDN_TYPE */
    MIPC_WFC_PDN_HO_IND_T_PDN_TYPE                          = 0x100,
    /* status */
    /* type = uint8_t, refer to WFC_PDN_HO_STATUS */
    MIPC_WFC_PDN_HO_IND_T_STATUS                            = 0x101,
    /* src_rat */
    /* type = uint8_t, refer to WFC_RAT */
    MIPC_WFC_PDN_HO_IND_T_SRC_RAT                           = 0x102,
    /* dst_rat */
    /* type = uint8_t, refer to WFC_RAT */
    MIPC_WFC_PDN_HO_IND_T_DST_RAT                           = 0x103,
};

    /* MIPC_MSG.WFC_ROVE_OUT_IND */
enum mipc_wfc_rove_out_ind_tlv_enum {
    mipc_wfc_rove_out_ind_tlv_NONE = 0,
    /* WiFi interface name, len contains /0 */
    /* type = string */
    MIPC_WFC_ROVE_OUT_IND_T_IFNAME                          = 0x100,
    /* TRUE: Wifi roveout, no LTE for H.O.; FALSE: Wifi RSSI acceptable */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_WFC_ROVE_OUT_IND_T_RVOUT                           = 0x101,
    /* TRUE: trigger mobike; FALSE: not trigger mobike */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_WFC_ROVE_OUT_IND_T_MOBIKE_IND                      = 0x102,
};

    /* MIPC_MSG.WFC_SSAC_IND */
enum mipc_wfc_ssac_ind_tlv_enum {
    mipc_wfc_ssac_ind_tlv_NONE = 0,
    /* parameter shows the barring factor for MMTEL voice, refer to TS27.007 +CSSAC */
    /* type = uint16_t */
    MIPC_WFC_SSAC_IND_T_BF_VOICE                            = 0x100,
    /* parameter shows the barring factor for MMTEL video, refer to TS27.007 +CSSAC */
    /* type = uint16_t */
    MIPC_WFC_SSAC_IND_T_BF_VIDEO                            = 0x101,
    /* parameter shows the barring timer for MMTEL voice, refer to TS27.007 +CSSAC */
    /* type = uint16_t */
    MIPC_WFC_SSAC_IND_T_BT_VOICE                            = 0x102,
    /* parameter shows the barring timer for MMTEL video, refer to TS27.007 +CSSAC */
    /* type = uint16_t */
    MIPC_WFC_SSAC_IND_T_BT_VIDEO                            = 0x103,
};

    /* MIPC_MSG.WFC_WIFI_PDN_ERR_IND */
enum mipc_wfc_wifi_pdn_err_ind_tlv_enum {
    mipc_wfc_wifi_pdn_err_ind_tlv_NONE = 0,
    /* n3epc_public_defs.h -> n3epc_pdn_rejct_enum */
    /* type = int32_t */
    MIPC_WFC_WIFI_PDN_ERR_IND_T_CAUSE                       = 0x100,
    /* refer n3epc_public_defs.h -> n3epc_ike_error_notify_enum */
    /* type = int32_t */
    MIPC_WFC_WIFI_PDN_ERR_IND_T_SUB_CAUSE                   = 0x101,
};

    /* MIPC_MSG.WFC_WIFI_PDN_OOS_IND */
enum mipc_wfc_wifi_pdn_oos_ind_tlv_enum {
    mipc_wfc_wifi_pdn_oos_ind_tlv_NONE = 0,
    /* apn name */
    /* type = string */
    MIPC_WFC_WIFI_PDN_OOS_IND_T_APN                         = 0x100,
    /* context identifier */
    /* type = uint8_t */
    MIPC_WFC_WIFI_PDN_OOS_IND_T_CID                         = 0x101,
    /* oos state */
    /* type = uint8_t, refer to WFC_PDN_OOS_STATE */
    MIPC_WFC_WIFI_PDN_OOS_IND_T_OOS_STATE                   = 0x102,
};

    /* MIPC_MSG.WFC_WFC_IND */
enum mipc_wfc_wfc_ind_tlv_enum {
    mipc_wfc_wfc_ind_tlv_NONE = 0,
    /* [PHASE OUT]indicate the wifi ims pdn state, please use WIFI_IMS_PDN_STATE instead of this tlv(to avoid misunderstanding of naming) */
    /* type = uint8_t, refer to WFC_WIFI_PDN_STATE */
    MIPC_WFC_WFC_IND_T_WIFI_PDN_STATE                       = 0x100,
    /* VoData and data sim. <value> is the second parameter in URC +EWFC: 3, <value> */
    /* type = uint8_t */
    MIPC_WFC_WFC_IND_T_DATA_SIM                             = 0x101,
    /* WiFi interface name for LOCK action, len contains /0 */
    /* type = string */
    MIPC_WFC_WFC_IND_T_IFNAME                               = 0x102,
    /* TRUE:enable lock status; FALSE:disable lock status */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_WFC_WFC_IND_T_LOCK                                 = 0x103,
    /* indicate the wifi ims pdn state */
    /* type = uint8_t, refer to WFC_WIFI_PDN_STATE */
    MIPC_WFC_WFC_IND_T_WIFI_IMS_PDN_STATE                   = 0x104,
};

    /* MIPC_MSG.PHB_READY_STATE_IND */
enum mipc_phb_ready_state_ind_tlv_enum {
    mipc_phb_ready_state_ind_tlv_NONE = 0,
    /* phb ready indication, 1:ready  0:not ready */
    /* type = uint8_t */
    MIPC_PHB_READY_STATE_IND_T_READY                        = 0x100,
};

    /* MIPC_MSG.EMBMS_EMSRV_IND */
enum mipc_embms_emsrv_ind_tlv_enum {
    mipc_embms_emsrv_ind_tlv_NONE = 0,
    /* The eMBMS service status, 0:No LTE service, 1:Only Unicast available(LTE coverage), 2:In eMBMS supporting area, 3:E911 call is on-going, 4:In SRLTE mode, 5:In flight mode */
    /* type = uint8_t */
    MIPC_EMBMS_EMSRV_IND_T_STATUS                           = 0x100,
    /* The MBSFN area ID info. */
    /* type = struct, refer to embms_area_id_info */
    MIPC_EMBMS_EMSRV_IND_T_AREA_ID_INFO                     = 0x101,
};

    /* MIPC_MSG.EMBMS_EMSLUI_IND */
enum mipc_embms_emslui_ind_tlv_enum {
    mipc_embms_emslui_ind_tlv_NONE = 0,
    /* The number of MBMS sessions in the list. */
    /* type = uint16_t */
    MIPC_EMBMS_EMSLUI_IND_T_NUM_SESSIONS                    = 0x100,
    /* The MBMS session info. */
    /* type = struct, refer to embms_session_info */
    MIPC_EMBMS_EMSLUI_IND_T_SESSIONS_INFO                   = 0x101,
};

    /* MIPC_MSG.EMBMS_EMSAILNF_IND */
enum mipc_embms_emsailnf_ind_tlv_enum {
    mipc_embms_emsailnf_ind_tlv_NONE = 0,
    /* The neighbouring frequency with bands list and MBMS SAI list. */
    /* type = struct, refer to embms_nb_req_info */
    MIPC_EMBMS_EMSAILNF_IND_T_MBMS_NB_FREQ_INFO             = 0x100,
};

    /* MIPC_MSG.EMBMS_EMSESS_IND */
enum mipc_embms_emsess_ind_tlv_enum {
    mipc_embms_emsess_ind_tlv_NONE = 0,
    /* The number of MBMS sessions in the list. */
    /* type = uint16_t */
    MIPC_EMBMS_EMSESS_IND_T_NUM_SESSIONS                    = 0x100,
    /* The MBMS session info. */
    /* type = struct, refer to embms_session_info */
    MIPC_EMBMS_EMSESS_IND_T_MBMS_SESSION_INFO               = 0x101,
    /* The cause for session deactivation. */
    /* type = uint8_t */
    MIPC_EMBMS_EMSESS_IND_T_CAUSE                           = 0x102,
    /* The sub-cause for activating session failed when <cause> is 1. */
    /* type = uint8_t */
    MIPC_EMBMS_EMSESS_IND_T_SUB_CAUSE                       = 0x103,
};

    /* MIPC_MSG.EMBMS_EHVOLTE_IND */
enum mipc_embms_ehvolte_ind_tlv_enum {
    mipc_embms_ehvolte_ind_tlv_NONE = 0,
    /* The hVolte mode. */
    /* type = uint8_t */
    MIPC_EMBMS_EHVOLTE_IND_T_MODE                           = 0x100,
};

    /* MIPC_MSG.SYS_REBOOT_CMD */
enum mipc_sys_reboot_cmd_tlv_enum {
    mipc_sys_reboot_cmd_tlv_NONE = 0,
    /* specify the reboot mode */
    /* type = uint8_t, refer to SYS_REBOOT_MODE */
    MIPC_SYS_REBOOT_CMD_T_MODE                              = 0x100,
    /* Download Timeout (Unit: second, Only valid when MODE is DOWNLOAD or SETTIMEOUT) */
    /* type = uint32_t */
    MIPC_SYS_REBOOT_CMD_T_TIMEOUT                           = 0x101,
};

    /* MIPC_MSG.SYS_REBOOT_RSP */
enum mipc_sys_reboot_rsp_tlv_enum {
    mipc_sys_reboot_rsp_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SYS_SET_CONFIG_DIPC_CMD */
enum mipc_sys_set_config_dipc_cmd_tlv_enum {
    mipc_sys_set_config_dipc_cmd_tlv_NONE = 0,
    /* the configuration class */
    /* type = uint32_t, refer to SYS_CONFIG_CLASS */
    MIPC_SYS_SET_CONFIG_DIPC_CMD_T_CLASS                    = 0x100,
    /* the string of configuration type */
    /* type = string */
    MIPC_SYS_SET_CONFIG_DIPC_CMD_T_TYPE                     = 0x101,
    /* the configuration data */
    /* type = byte_array */
    MIPC_SYS_SET_CONFIG_DIPC_CMD_T_DATA                     = 0x102,
};

    /* MIPC_MSG.SYS_SET_CONFIG_DIPC_RSP */
enum mipc_sys_set_config_dipc_rsp_tlv_enum {
    mipc_sys_set_config_dipc_rsp_tlv_NONE = 0,
    /* the response data */
    /* type = byte_array */
    MIPC_SYS_SET_CONFIG_DIPC_RSP_T_DATA                     = 0x100,
};

    /* MIPC_MSG.SYS_CONFIG_NEEDED_TO_UPDATE_CMD */
enum mipc_sys_config_needed_to_update_cmd_tlv_enum {
    mipc_sys_config_needed_to_update_cmd_tlv_NONE = 0,
    /* the configuration class */
    /* type = uint32_t, refer to SYS_CONFIG_CLASS */
    MIPC_SYS_CONFIG_NEEDED_TO_UPDATE_CMD_T_CLASS            = 0x100,
    /* the string of configuration type */
    /* type = string */
    MIPC_SYS_CONFIG_NEEDED_TO_UPDATE_CMD_T_TYPE             = 0x101,
};

    /* MIPC_MSG.SYS_CONFIG_NEEDED_TO_UPDATE_RSP */
enum mipc_sys_config_needed_to_update_rsp_tlv_enum {
    mipc_sys_config_needed_to_update_rsp_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.SYS_GET_CONFIG_DIPC_CMD */
enum mipc_sys_get_config_dipc_cmd_tlv_enum {
    mipc_sys_get_config_dipc_cmd_tlv_NONE = 0,
    /* the configuration class */
    /* type = uint32_t, refer to SYS_CONFIG_CLASS */
    MIPC_SYS_GET_CONFIG_DIPC_CMD_T_CLASS                    = 0x100,
    /* the string of configuration type */
    /* type = string */
    MIPC_SYS_GET_CONFIG_DIPC_CMD_T_TYPE                     = 0x101,
};

    /* MIPC_MSG.SYS_GET_CONFIG_DIPC_RSP */
enum mipc_sys_get_config_dipc_rsp_tlv_enum {
    mipc_sys_get_config_dipc_rsp_tlv_NONE = 0,
    /* the response data */
    /* type = byte_array */
    MIPC_SYS_GET_CONFIG_DIPC_RSP_T_DATA                     = 0x100,
};

    /* MIPC_MSG.SYS_SET_TIME_CMD */
enum mipc_sys_set_time_cmd_tlv_enum {
    mipc_sys_set_time_cmd_tlv_NONE = 0,
    /* type = struct, refer to nw_nitz_info */
    MIPC_SYS_SET_TIME_CMD_T_INFO                            = 0x100,
};

    /* MIPC_MSG.SYS_SET_TIME_RSP */
enum mipc_sys_set_time_rsp_tlv_enum {
    mipc_sys_set_time_rsp_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.INTERNAL_TEST_CMD */
enum mipc_internal_test_cmd_tlv_enum {
    mipc_internal_test_cmd_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.INTERNAL_TEST_RSP */
enum mipc_internal_test_rsp_tlv_enum {
    mipc_internal_test_rsp_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.INTERNAL_EIPPORT_CMD */
enum mipc_internal_eipport_cmd_tlv_enum {
    mipc_internal_eipport_cmd_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_INTERNAL_EIPPORT_CMD_T_TRANSID                     = 0x100,
    /* type = uint8_t, refer to INTERNAL_EIPPORT_ACTION */
    MIPC_INTERNAL_EIPPORT_CMD_T_ACTION                      = 0x101,
    /* type = uint8_t */
    MIPC_INTERNAL_EIPPORT_CMD_T_IFID                        = 0x102,
    /* type = struct, refer to addr */
    MIPC_INTERNAL_EIPPORT_CMD_T_ADDR                        = 0x8103,
    /* type = uint8_t */
    MIPC_INTERNAL_EIPPORT_CMD_T_PROTO                       = 0x104,
    /* type = uint16_t */
    MIPC_INTERNAL_EIPPORT_CMD_T_PORT                        = 0x105,
};

    /* MIPC_MSG.INTERNAL_EIPPORT_RSP */
enum mipc_internal_eipport_rsp_tlv_enum {
    mipc_internal_eipport_rsp_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_INTERNAL_EIPPORT_RSP_T_TRANSID                     = 0x100,
    /* type = uint8_t, refer to INTERNAL_EIPPORT_ACTION */
    MIPC_INTERNAL_EIPPORT_RSP_T_ACTION                      = 0x101,
    /* type = uint8_t, refer to INTERNAL_EIPPORT_RESULT */
    MIPC_INTERNAL_EIPPORT_RSP_T_RESULT                      = 0x102,
};

    /* MIPC_MSG.INTERNAL_EIPSPI_CMD */
enum mipc_internal_eipspi_cmd_tlv_enum {
    mipc_internal_eipspi_cmd_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_INTERNAL_EIPSPI_CMD_T_TRANSID                      = 0x100,
    /* type = uint8_t, refer to INTERNAL_EIPSPI_ACTION */
    MIPC_INTERNAL_EIPSPI_CMD_T_ACTION                       = 0x101,
    /* type = struct, refer to addr */
    MIPC_INTERNAL_EIPSPI_CMD_T_SRC_ADDR                     = 0x8102,
    /* type = struct, refer to addr */
    MIPC_INTERNAL_EIPSPI_CMD_T_DST_ADDR                     = 0x8103,
    /* type = uint8_t, refer to IPSEC_PROTO_ENUM */
    MIPC_INTERNAL_EIPSPI_CMD_T_PROTO                        = 0x104,
    /* type = uint8_t, refer to IPSEC_MODE_ENUM */
    MIPC_INTERNAL_EIPSPI_CMD_T_MODE                         = 0x105,
    /* type = uint32_t */
    MIPC_INTERNAL_EIPSPI_CMD_T_MIN_SPI                      = 0x106,
    /* type = uint32_t */
    MIPC_INTERNAL_EIPSPI_CMD_T_MAX_SPI                      = 0x107,
    /* type = uint32_t */
    MIPC_INTERNAL_EIPSPI_CMD_T_SPI                          = 0x8108,
};

    /* MIPC_MSG.INTERNAL_EIPSPI_RSP */
enum mipc_internal_eipspi_rsp_tlv_enum {
    mipc_internal_eipspi_rsp_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_INTERNAL_EIPSPI_RSP_T_TRANSID                      = 0x100,
    /* type = uint8_t */
    MIPC_INTERNAL_EIPSPI_RSP_T_ACTION                       = 0x101,
    /* type = uint32_t */
    MIPC_INTERNAL_EIPSPI_RSP_T_SPI                          = 0x8102,
};

    /* MIPC_MSG.INTERNAL_MULTI_EIPSPI_FREE_CMD */
enum mipc_internal_multi_eipspi_free_cmd_tlv_enum {
    mipc_internal_multi_eipspi_free_cmd_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_INTERNAL_MULTI_EIPSPI_FREE_CMD_T_TRANSID           = 0x100,
    /* type = uint32_t */
    MIPC_INTERNAL_MULTI_EIPSPI_FREE_CMD_T_MULTI_FREE_COUNT  = 0x8101,
    /* type = struct_array, refer to addr */
    MIPC_INTERNAL_MULTI_EIPSPI_FREE_CMD_T_SRC_ADDR_LIST     = 0x8102,
    /* type = struct_array, refer to addr */
    MIPC_INTERNAL_MULTI_EIPSPI_FREE_CMD_T_DST_ADDR_LIST     = 0x8103,
    /* type = byte_array, refer to IPSEC_PROTO_ENUM */
    MIPC_INTERNAL_MULTI_EIPSPI_FREE_CMD_T_PROTO_LIST        = 0x104,
    /* it should be a uint32 list */
    /* type = byte_array */
    MIPC_INTERNAL_MULTI_EIPSPI_FREE_CMD_T_SPI_LIST          = 0x8105,
};

    /* MIPC_MSG.INTERNAL_MULTI_EIPSPI_FREE_RSP */
enum mipc_internal_multi_eipspi_free_rsp_tlv_enum {
    mipc_internal_multi_eipspi_free_rsp_tlv_NONE = 0,
    /* type = uint32_t */
    MIPC_INTERNAL_MULTI_EIPSPI_FREE_RSP_T_TRANSID           = 0x100,
    /* type = uint32_t */
    MIPC_INTERNAL_MULTI_EIPSPI_FREE_RSP_T_MULTI_FREE_COUNT  = 0x8101,
    /* it should be a uint32 list */
    /* type = byte_array */
    MIPC_INTERNAL_MULTI_EIPSPI_FREE_RSP_T_SPI_LIST          = 0x8102,
    /* type = byte_array, refer to SPI_STATUS_ENUM */
    MIPC_INTERNAL_MULTI_EIPSPI_FREE_RSP_T_STATUS_LIST       = 0x8103,
};

    /* MIPC_MSG.SMS_NEW_SMS_CMD */
enum mipc_sms_new_sms_cmd_tlv_enum {
    mipc_sms_new_sms_cmd_tlv_NONE = 0,
    /* the format of this sms */
    /* type = uint8_t, refer to SMS_FORMAT */
    MIPC_SMS_NEW_SMS_CMD_T_FORMAT                           = 0x100,
    /* [PDU_3GPP] should be 1 in this case */
    /* type = uint16_t */
    MIPC_SMS_NEW_SMS_CMD_T_PDU_COUNT                        = 0x103,
    /* [PDU_3GPP] valid when */
    /* type = struct_array, refer to sms_pdu */
    MIPC_SMS_NEW_SMS_CMD_T_PDU_LIST                         = 0x8104,
    /* [PDU_3GPP2] valid when CDMA */
    /* type = byte_array */
    MIPC_SMS_NEW_SMS_CMD_T_PDU_C2K                          = 0x8105,
};

    /* MIPC_MSG.SMS_NEW_SMS_RSP */
enum mipc_sms_new_sms_rsp_tlv_enum {
    mipc_sms_new_sms_rsp_tlv_NONE = 0,
    /* [PDU_3GPP] ack for the NEW_SMS_CMD,RP_ACK or RP_ERROR */
    /* type = uint8_t, refer to NEW_SMS_ACK */
    MIPC_SMS_NEW_SMS_RSP_T_NEW_SMS_ACK                      = 0x100,
    /* [PDU_3GPP] cause in TS23.040 9.2.3.22 */
    /* type = uint8_t */
    MIPC_SMS_NEW_SMS_RSP_T_CAUSE                            = 0x101,
    /* the format of this sms */
    /* type = uint8_t, refer to SMS_FORMAT */
    MIPC_SMS_NEW_SMS_RSP_T_FORMAT                           = 0x102,
    /* [PDU_3GPP2] error class of C2K operation, if not carry, would be 0x00 */
    /* type = uint8_t, refer to SMS_C2K_ERR_CLASS */
    MIPC_SMS_NEW_SMS_RSP_T_ERR_CLASS_C2K                    = 0x103,
    /* [PDU_3GPP2] C2K error code */
    /* type = uint16_t, refer to SMS_C2K_ERR_CODE */
    MIPC_SMS_NEW_SMS_RSP_T_ERR_CODE_C2K                     = 0x104,
    /* [PDU_3GPP] refer to <ackpdu> in AT+CNMA; if carry this, CAUSE would be ignored */
    /* type = byte_array */
    MIPC_SMS_NEW_SMS_RSP_T_ACK_PDU                          = 0x8105,
};

    /* MIPC_MSG.SMS_NEW_STATUS_REPORT_CMD */
enum mipc_sms_new_status_report_cmd_tlv_enum {
    mipc_sms_new_status_report_cmd_tlv_NONE = 0,
    /* pdu detail info */
    /* type = byte_array */
    MIPC_SMS_NEW_STATUS_REPORT_CMD_T_PDU                    = 0x8100,
};

    /* MIPC_MSG.SMS_NEW_STATUS_REPORT_RSP */
enum mipc_sms_new_status_report_rsp_tlv_enum {
    mipc_sms_new_status_report_rsp_tlv_NONE = 0,
    /* ack for the NEW_STATUS_REPORT_CMD,RP_ACK or RP_ERROR */
    /* type = uint8_t, refer to NEW_SMS_ACK */
    MIPC_SMS_NEW_STATUS_REPORT_RSP_T_ACK_TYPE               = 0x100,
    /* cause in TS23.040 9.2.3.22 */
    /* type = uint8_t */
    MIPC_SMS_NEW_STATUS_REPORT_RSP_T_CAUSE                  = 0x101,
    /* [PDU_3GPP] refer to <ackpdu> in AT+CNMA; if carry this, CAUSE would be ignored */
    /* type = byte_array */
    MIPC_SMS_NEW_STATUS_REPORT_RSP_T_ACK_PDU                = 0x8102,
};

    /* MIPC_MSG.CALL_APPROVE_INCOMING_CMD */
enum mipc_call_approve_incoming_cmd_tlv_enum {
    mipc_call_approve_incoming_cmd_tlv_NONE = 0,
    /* call ID */
    /* type = uint32_t */
    MIPC_CALL_APPROVE_INCOMING_CMD_T_CALLID                 = 0x100,
    /* type = string */
    MIPC_CALL_APPROVE_INCOMING_CMD_T_NUMBER                 = 0x8101,
    /* type of address (refer TS 24.008 [8] subclause 10.5.4.7) */
    /* type = uint32_t */
    MIPC_CALL_APPROVE_INCOMING_CMD_T_TOA                    = 0x102,
    /* sequence number which is piggybacked from the incoming call */
    /* type = uint32_t */
    MIPC_CALL_APPROVE_INCOMING_CMD_T_SEQ_NO                 = 0x103,
    /* type = uint32_t, refer to CALL_MODE */
    MIPC_CALL_APPROVE_INCOMING_CMD_T_MODE                   = 0x104,
    /* type = uint8_t */
    MIPC_CALL_APPROVE_INCOMING_CMD_T_EVOLTESI_FLOW          = 0x105,
};

    /* MIPC_MSG.CALL_APPROVE_INCOMING_RSP */
enum mipc_call_approve_incoming_rsp_tlv_enum {
    mipc_call_approve_incoming_rsp_tlv_NONE = 0,
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_CALL_APPROVE_INCOMING_RSP_T_IS_APPROVE             = 0x100,
    /* type = uint32_t */
    MIPC_CALL_APPROVE_INCOMING_RSP_T_CAUSE                  = 0x101,
    /* call ID */
    /* type = uint32_t */
    MIPC_CALL_APPROVE_INCOMING_RSP_T_CALLID                 = 0x102,
    /* sequence number which is piggybacked from the incoming call */
    /* type = uint32_t */
    MIPC_CALL_APPROVE_INCOMING_RSP_T_SEQ_NO                 = 0x103,
};

    /* MIPC_MSG.IMS_PDIS_CMD */
enum mipc_ims_pdis_cmd_tlv_enum {
    mipc_ims_pdis_cmd_tlv_NONE = 0,
    /* transaction id, 1~255 */
    /* type = uint8_t */
    MIPC_IMS_PDIS_CMD_T_TRANSACTION_ID                      = 0x100,
    /* emergency indication */
    /* type = uint8_t, refer to EM_ID_TYPE */
    MIPC_IMS_PDIS_CMD_T_EM_ID                               = 0x101,
    /* pcscf method */
    /* type = uint8_t, refer to PDIS_METHOD_TYPE */
    MIPC_IMS_PDIS_CMD_T_METHOD                              = 0x102,
    /* interface name , such as ccmni0 */
    /* type = string */
    MIPC_IMS_PDIS_CMD_T_NW_INTERFACE_NAME                   = 0x103,
};

    /* MIPC_MSG.IMS_PDIS_RSP */
enum mipc_ims_pdis_rsp_tlv_enum {
    mipc_ims_pdis_rsp_tlv_NONE = 0,
    /* transaction id, 1~255 */
    /* type = uint8_t */
    MIPC_IMS_PDIS_RSP_T_TRANSACTION_ID                      = 0x100,
    /* pcscf method */
    /* type = uint8_t, refer to PDIS_METHOD_TYPE */
    MIPC_IMS_PDIS_RSP_T_METHOD                              = 0x101,
    /* success or not */
    /* type = uint8_t */
    MIPC_IMS_PDIS_RSP_T_IS_SUCCESS                          = 0x102,
};

    /* MIPC_MSG.WFC_PING_CMD */
enum mipc_wfc_ping_cmd_tlv_enum {
    mipc_wfc_ping_cmd_tlv_NONE = 0,
    /* the rat to ping */
    /* type = uint8_t, refer to WFC_RAT */
    MIPC_WFC_PING_CMD_T_RAT                                 = 0x100,
};

    /* MIPC_MSG.WFC_PING_RSP */
enum mipc_wfc_ping_rsp_tlv_enum {
    mipc_wfc_ping_rsp_tlv_NONE = 0,
    /* the rat ping */
    /* type = uint8_t, refer to WFC_RAT */
    MIPC_WFC_PING_RSP_T_RAT                                 = 0x100,
    /* unit:ms */
    /* type = uint16_t */
    MIPC_WFC_PING_RSP_T_AVE_LATENCY                         = 0x101,
    /* loss_rate */
    /* type = uint8_t */
    MIPC_WFC_PING_RSP_T_LOSS_RATE                           = 0x102,
};

    /* MIPC_MSG.WFC_GET_MAC_CMD */
enum mipc_wfc_get_mac_cmd_tlv_enum {
    mipc_wfc_get_mac_cmd_tlv_NONE = 0,
    /* WiFi interface name, len contains /0 */
    /* type = string */
    MIPC_WFC_GET_MAC_CMD_T_IFNAME                           = 0x100,
    /* ip, len=4->IPv4;len=16->IPv6 */
    /* type = byte_array */
    MIPC_WFC_GET_MAC_CMD_T_IP                               = 0x101,
};

    /* MIPC_MSG.WFC_GET_MAC_RSP */
enum mipc_wfc_get_mac_rsp_tlv_enum {
    mipc_wfc_get_mac_rsp_tlv_NONE = 0,
    /* 0-success */
    /* type = int32_t */
    MIPC_WFC_GET_MAC_RSP_T_GET_RESULT                       = 0x100,
    /* WiFi interface name, len contains /0 */
    /* type = string */
    MIPC_WFC_GET_MAC_RSP_T_IFNAME                           = 0x101,
    /* ip, len=4->IPv4;len=16->IPv6 */
    /* type = byte_array */
    MIPC_WFC_GET_MAC_RSP_T_IP                               = 0x102,
    /* mac address */
    /* type = byte_array */
    MIPC_WFC_GET_MAC_RSP_T_MAC                              = 0x103,
};

    /* MIPC_MSG.WFC_NATT_KEEP_ALIVE_CMD */
enum mipc_wfc_natt_keep_alive_cmd_tlv_enum {
    mipc_wfc_natt_keep_alive_cmd_tlv_NONE = 0,
    /* enable? */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_WFC_NATT_KEEP_ALIVE_CMD_T_ENABLE                   = 0x100,
    /* unit:s,if interval < 20s, wifi NATT keep alive will not start */
    /* type = uint16_t */
    MIPC_WFC_NATT_KEEP_ALIVE_CMD_T_INTERVAL                 = 0x101,
    /* ip, len=4->IPv4; len=16->IPv6 */
    /* type = byte_array */
    MIPC_WFC_NATT_KEEP_ALIVE_CMD_T_SRC_IP                   = 0x102,
    /* src_port */
    /* type = uint16_t */
    MIPC_WFC_NATT_KEEP_ALIVE_CMD_T_SRC_PORT                 = 0x103,
    /* ip, len=4->IPv4; len=16->IPv6 */
    /* type = byte_array */
    MIPC_WFC_NATT_KEEP_ALIVE_CMD_T_DST_IP                   = 0x104,
    /* dst_port */
    /* type = uint16_t, refer to BOOLEAN */
    MIPC_WFC_NATT_KEEP_ALIVE_CMD_T_DST_PORT                 = 0x105,
};

    /* MIPC_MSG.WFC_NATT_KEEP_ALIVE_RSP */
enum mipc_wfc_natt_keep_alive_rsp_tlv_enum {
    mipc_wfc_natt_keep_alive_rsp_tlv_NONE = 0,
    /* WiFi interface name, len contains /0 */
    /* type = string */
    MIPC_WFC_NATT_KEEP_ALIVE_RSP_T_IFNAME                   = 0x100,
    /* natt enable? */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_WFC_NATT_KEEP_ALIVE_RSP_T_ENABLE                   = 0x101,
    /* ip, len=4->IPv4; len=16->IPv6 */
    /* type = byte_array */
    MIPC_WFC_NATT_KEEP_ALIVE_RSP_T_SRC_IP                   = 0x102,
    /* src_port */
    /* type = uint16_t */
    MIPC_WFC_NATT_KEEP_ALIVE_RSP_T_SRC_PORT                 = 0x103,
    /* ip, len=4->IPv4; len=16->IPv6 */
    /* type = byte_array */
    MIPC_WFC_NATT_KEEP_ALIVE_RSP_T_DST_IP                   = 0x104,
    /* dst_port */
    /* type = uint16_t */
    MIPC_WFC_NATT_KEEP_ALIVE_RSP_T_DST_PORT                 = 0x105,
};

    /* MIPC_MSG.WFC_REGISTER_WIFI_SIGNAL_NTF_CMD */
enum mipc_wfc_register_wifi_signal_ntf_cmd_tlv_enum {
    mipc_wfc_register_wifi_signal_ntf_cmd_tlv_NONE = 0,
    /* enable NTF(WIFI_SIGNAL_NTF)? */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_WFC_REGISTER_WIFI_SIGNAL_NTF_CMD_T_ENABLE_NTF      = 0x100,
    /* [wtcfm]uint:dbm? */
    /* type = int16_t */
    MIPC_WFC_REGISTER_WIFI_SIGNAL_NTF_CMD_T_RSSI_THRESHOLD  = 0x101,
};

    /* MIPC_MSG.WFC_REGISTER_WIFI_SIGNAL_NTF_RSP */
enum mipc_wfc_register_wifi_signal_ntf_rsp_tlv_enum {
    mipc_wfc_register_wifi_signal_ntf_rsp_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.DATA_ACT_CALL_NTF */
enum mipc_data_act_call_ntf_tlv_enum {
    mipc_data_act_call_ntf_tlv_NONE = 0,
    /* indicate the cid */
    /* type = uint8_t */
    MIPC_DATA_ACT_CALL_NTF_T_ID                             = 0x100,
    /* indicate use or not */
    /* type = uint8_t, refer to ACT_CALL_NTF_ENUM */
    MIPC_DATA_ACT_CALL_NTF_T_RESPONSE                       = 0x101,
};

    /* MIPC_MSG.INTERNAL_TEST_NTF */
enum mipc_internal_test_ntf_tlv_enum {
    mipc_internal_test_ntf_tlv_NONE = 0,
    /* no proprietary TLV */
};

    /* MIPC_MSG.INTERNAL_INJECT_TST_NTF */
enum mipc_internal_inject_tst_ntf_tlv_enum {
    mipc_internal_inject_tst_ntf_tlv_NONE = 0,
    /* type = string */
    MIPC_INTERNAL_INJECT_TST_NTF_T_MODULE                   = 0x100,
    /* type = uint8_t */
    MIPC_INTERNAL_INJECT_TST_NTF_T_INDEX                    = 0x101,
    /* type = string */
    MIPC_INTERNAL_INJECT_TST_NTF_T_INJECT_STRING            = 0x102,
};

    /* MIPC_MSG.WFC_WIFI_SIGNAL_NTF */
enum mipc_wfc_wifi_signal_ntf_tlv_enum {
    mipc_wfc_wifi_signal_ntf_tlv_NONE = 0,
    /* WiFi interface name, len contains /0 */
    /* type = string */
    MIPC_WFC_WIFI_SIGNAL_NTF_T_IFNAME                       = 0x100,
    /* uint:dbm */
    /* type = int16_t */
    MIPC_WFC_WIFI_SIGNAL_NTF_T_RSSI                         = 0x101,
    /* unit: dB */
    /* type = int16_t */
    MIPC_WFC_WIFI_SIGNAL_NTF_T_SNR                          = 0x102,
};

    /* MIPC_MSG.WFC_EPDG_SCREEN_STATE_NTF */
enum mipc_wfc_epdg_screen_state_ntf_tlv_enum {
    mipc_wfc_epdg_screen_state_ntf_tlv_NONE = 0,
    /* screen state */
    /* type = uint8_t, refer to EPDG_SCREEN_STATE */
    MIPC_WFC_EPDG_SCREEN_STATE_NTF_T_STATE                  = 0x100,
};

    /* MIPC_MSG.WFC_WIFI_INFO_NTF */
enum mipc_wfc_wifi_info_ntf_tlv_enum {
    mipc_wfc_wifi_info_ntf_tlv_NONE = 0,
    /* WiFi interface name, len contains /0 */
    /* type = string */
    MIPC_WFC_WIFI_INFO_NTF_T_IFNAME                         = 0x100,
    /* enable? */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_WFC_WIFI_INFO_NTF_T_ENABLE                         = 0x101,
    /* cause of enable or disable; now only 1=flight_mode, expand to enum? */
    /* type = uint8_t */
    MIPC_WFC_WIFI_INFO_NTF_T_CAUSE                          = 0x102,
    /* associated? */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_WFC_WIFI_INFO_NTF_T_ASSOCIATED                     = 0x103,
    /* ssid, len contains /0 */
    /* type = string */
    MIPC_WFC_WIFI_INFO_NTF_T_SSID                           = 0x104,
    /* ap mac address */
    /* type = byte_array */
    MIPC_WFC_WIFI_INFO_NTF_T_AP_MAC                         = 0x105,
    /* wifi type */
    /* type = uint8_t, refer to WIFI_TYPE */
    MIPC_WFC_WIFI_INFO_NTF_T_WIFI_TYPE                      = 0x106,
    /* mtu size */
    /* type = uint16_t */
    MIPC_WFC_WIFI_INFO_NTF_T_MTU                            = 0x107,
    /* ue mac address */
    /* type = byte_array */
    MIPC_WFC_WIFI_INFO_NTF_T_UE_MAC                         = 0x108,
    /* ipv4 address */
    /* type = byte_array */
    MIPC_WFC_WIFI_INFO_NTF_T_IPV4                           = 0x109,
    /* ipv4 prefix len */
    /* type = uint8_t */
    MIPC_WFC_WIFI_INFO_NTF_T_IPV4_PREFIX_LEN                = 0x10A,
    /* ipv4 gateway */
    /* type = byte_array */
    MIPC_WFC_WIFI_INFO_NTF_T_IPV4_GATEWAY                   = 0x10B,
    /* ipv6 address */
    /* type = byte_array */
    MIPC_WFC_WIFI_INFO_NTF_T_IPV6                           = 0x10C,
    /* ipv6 prefix len */
    /* type = uint8_t */
    MIPC_WFC_WIFI_INFO_NTF_T_IPV6_PREFIX_LEN                = 0x10D,
    /* ipv6 gateway */
    /* type = byte_array */
    MIPC_WFC_WIFI_INFO_NTF_T_IPV6_GATEWAY                   = 0x10E,
    /* dns */
    /* type = byte_array */
    MIPC_WFC_WIFI_INFO_NTF_T_DNS                            = 0x10F,
    /* indicate if the IP&DNS info need update */
    /* type = uint8_t, refer to BOOLEAN */
    MIPC_WFC_WIFI_INFO_NTF_T_IP_UPDATE                      = 0x110,
    /* same as WIFI_TYPE, this use string format for backward compatible */
    /* type = string */
    MIPC_WFC_WIFI_INFO_NTF_T_WIFI_TYPE_STR                  = 0x111,
    /* meaning has wifi transport capability and net capability validated */
    /* type = uint8_t, refer to WIFI_EXTEND_STATE */
    MIPC_WFC_WIFI_INFO_NTF_T_WIFI_EXTEND_STATE              = 0x112,
};

enum MIPC_COMMON_TLV_enum {
    MIPC_COMMON_TLV_NONE = 0,
    /*  */
    MIPC_T_RESULT                                           = 0,
};

enum mipc_boolean_const_enum {
    mipc_boolean_const_NONE = 0,
    /* BOOLEAN */
    MIPC_BOOLEAN_FALSE                                      = 0,
    MIPC_BOOLEAN_TRUE                                       = 1,
};
typedef enum mipc_boolean_const_enum mipc_boolean_const_enum;

enum mipc_sys_sim_ps_const_enum {
    mipc_sys_sim_ps_const_NONE = 0,
    /* SYS_SIM_PS */
    MIPC_SYS_SIM_PS_SIM0                                    = 0x01,
    MIPC_SYS_SIM_PS_SIM1                                    = 0x02,
    MIPC_SYS_SIM_PS_SIM2                                    = 0x04,
    MIPC_SYS_SIM_PS_SIM3                                    = 0x08,
    MIPC_SYS_SIM_PS_PS0                                     = 0x10,
    MIPC_SYS_SIM_PS_PS1                                     = 0x20,
    MIPC_SYS_SIM_PS_PS2                                     = 0x40,
    MIPC_SYS_SIM_PS_PS3                                     = 0x80,
    MIPC_SYS_SIM_PS_ALL                                     = 0xFF,
};
typedef enum mipc_sys_sim_ps_const_enum mipc_sys_sim_ps_const_enum;

enum mipc_sys_reboot_mode_const_enum {
    mipc_sys_reboot_mode_const_NONE = 0,
    /* SYS_REBOOT_MODE */
    /* normal reboot mode */
    MIPC_SYS_REBOOT_MODE_NORMAL                             = 0,
    MIPC_SYS_REBOOT_MODE_DOWNLOAD                           = 1,
    MIPC_SYS_REBOOT_MODE_POWEROFF                           = 2,
    MIPC_SYS_REBOOT_MODE_PRESHUTDOWN                        = 3,
    MIPC_SYS_REBOOT_MODE_DOWNLOAD_NONRST                    = 4,
};
typedef enum mipc_sys_reboot_mode_const_enum mipc_sys_reboot_mode_const_enum;

enum mipc_sys_cap_cellular_class_const_enum {
    mipc_sys_cap_cellular_class_const_NONE = 0,
    /* SYS_CAP_CELLULAR_CLASS */
    MIPC_SYS_CAP_CELLULAR_CLASS_GSM                         = 0x00000001,
    MIPC_SYS_CAP_CELLULAR_CLASS_CDMA                        = 0x00000002,
};
typedef enum mipc_sys_cap_cellular_class_const_enum mipc_sys_cap_cellular_class_const_enum;

enum mipc_sys_voice_class_const_enum {
    mipc_sys_voice_class_const_NONE = 0,
    /* SYS_VOICE_CLASS */
    MIPC_SYS_VOICE_CLASS_UNKNOWN                            = 0,
    MIPC_SYS_VOICE_CLASS_NO_VOICE                           = 1,
    MIPC_SYS_VOICE_CLASS_SEPARATE_VOICE_DATA                = 2,
    MIPC_SYS_VOICE_CLASS_SIMULTANEOUS_VOICE_DATA            = 3,
};
typedef enum mipc_sys_voice_class_const_enum mipc_sys_voice_class_const_enum;

enum mipc_sys_sim_class_const_enum {
    mipc_sys_sim_class_const_NONE = 0,
    /* SYS_SIM_CLASS */
    MIPC_SYS_SIM_CLASS_UNKNOWN                              = 0,
    MIPC_SYS_SIM_CLASS_LOGICAL                              = 1,
    MIPC_SYS_SIM_CLASS_REMOVABLE                            = 2,
};
typedef enum mipc_sys_sim_class_const_enum mipc_sys_sim_class_const_enum;

enum mipc_sys_cap_data_const_enum {
    mipc_sys_cap_data_const_NONE = 0,
    /* SYS_CAP_DATA */
    MIPC_SYS_CAP_DATA_NONE                                  = 0x00000000,
    MIPC_SYS_CAP_DATA_GPRS                                  = 0x00000001,
    MIPC_SYS_CAP_DATA_EDGE                                  = 0x00000002,
    MIPC_SYS_CAP_DATA_UMTS                                  = 0x00000004,
    MIPC_SYS_CAP_DATA_HSDPA                                 = 0x00000008,
    MIPC_SYS_CAP_DATA_HSUPA                                 = 0x00000010,
    MIPC_SYS_CAP_DATA_LTE                                   = 0x00000020,
    MIPC_SYS_CAP_DATA_5G_NSA                                = 0x00000040,
    MIPC_SYS_CAP_DATA_5G_SA                                 = 0x00000080,
    MIPC_SYS_CAP_DATA_1XRTT                                 = 0x00010000,
    MIPC_SYS_CAP_DATA_1XEVDO                                = 0x00020000,
    MIPC_SYS_CAP_DATA_1XEVDO_REVA                           = 0x00040000,
    MIPC_SYS_CAP_DATA_1XEVDV                                = 0x00080000,
    MIPC_SYS_CAP_DATA_3XRTT                                 = 0x00100000,
    MIPC_SYS_CAP_DATA_1XEVDO_REVB                           = 0x00200000,
    MIPC_SYS_CAP_DATA_UMB                                   = 0x00400000,
    MIPC_SYS_CAP_DATA_HSPA_PLUS                             = 0x40000000,
    MIPC_SYS_CAP_DATA_CUSTOM                                = 0x80000000,
};
typedef enum mipc_sys_cap_data_const_enum mipc_sys_cap_data_const_enum;

enum mipc_sys_cap_sms_const_enum {
    mipc_sys_cap_sms_const_NONE = 0,
    /* SYS_CAP_SMS */
    MIPC_SYS_CAP_SMS_NONE                                   = 0x00000000,
    MIPC_SYS_CAP_SMS_PDU_RECEIVE                            = 0x00000001,
    MIPC_SYS_CAP_SMS_PDU_SEND                               = 0x00000002,
    MIPC_SYS_CAP_SMS_TEXT_RECEIVE                           = 0x00000004,
    MIPC_SYS_CAP_SMS_TEXT_SEND                              = 0x00000008,
};
typedef enum mipc_sys_cap_sms_const_enum mipc_sys_cap_sms_const_enum;

enum mipc_sys_cap_ctrl_const_enum {
    mipc_sys_cap_ctrl_const_NONE = 0,
    /* SYS_CAP_CTRL */
    MIPC_SYS_CAP_CTRL_NONE                                  = 0x00000000,
    MIPC_SYS_CAP_CTRL_REG_MANUAL                            = 0x00000001,
    MIPC_SYS_CAP_CTRL_HW_RADIO_SWITCH                       = 0x00000002,
    MIPC_SYS_CAP_CTRL_CDMA_MOBILE_IP                        = 0x00000004,
    MIPC_SYS_CAP_CTRL_CDMA_SIMPLE_IP                        = 0x00000008,
    MIPC_SYS_CAP_CTRL_MULTI_CARRIER                         = 0x00000010,
    MIPC_SYS_CAP_CTRL_ESIM                                  = 0x00000020,
    MIPC_SYS_CAP_CTRL_UE_POLICY_ROUTE_SELECTION             = 0x00000040,
    MIPC_SYS_CAP_CTRL_SIM_HOT_SWAP_CAPABLE                  = 0x00000080,
};
typedef enum mipc_sys_cap_ctrl_const_enum mipc_sys_cap_ctrl_const_enum;

enum mipc_sys_auth_algo_const_enum {
    mipc_sys_auth_algo_const_NONE = 0,
    /* SYS_AUTH_ALGO */
    MIPC_SYS_AUTH_ALGO_NONE                                 = 0,
    MIPC_SYS_AUTH_ALGO_SIM                                  = 1,
    MIPC_SYS_AUTH_ALGO_AKA                                  = 2,
    MIPC_SYS_AUTH_ALGO_AKAP                                 = 3,
};
typedef enum mipc_sys_auth_algo_const_enum mipc_sys_auth_algo_const_enum;

enum mipc_sys_cap_service_const_enum {
    mipc_sys_cap_service_const_NONE = 0,
    /* SYS_CAP_SERVICE */
    MIPC_SYS_CAP_SERVICE_NONE                               = 0x00000000,
    MIPC_SYS_CAP_SERVICE_LTE_ATTACH                         = 0x00000001,
    MIPC_SYS_CAP_SERVICE_CONTEXT_MGMT                       = 0x00000002,
    MIPC_SYS_CAP_SERVICE_MULTI_SIM                          = 0x00000004,
    MIPC_SYS_CAP_SERVICE_EX_SAR                             = 0x00000008,
    MIPC_SYS_CAP_SERVICE_NETWORK_BLACKLIST                  = 0x00000010,
    MIPC_SYS_CAP_SERVICE_5G_NSA                             = 0x00000020,
};
typedef enum mipc_sys_cap_service_const_enum mipc_sys_cap_service_const_enum;

enum mipc_sys_cap_gsm_band_const_enum {
    mipc_sys_cap_gsm_band_const_NONE = 0,
    /* SYS_CAP_GSM_BAND */
    MIPC_SYS_CAP_GSM_BAND_900                               = 0x00000002,
    MIPC_SYS_CAP_GSM_BAND_DCS_1800                          = 0x00000008,
    MIPC_SYS_CAP_GSM_BAND_PCS_1900                          = 0x00000010,
    MIPC_SYS_CAP_GSM_BAND_PCS_850                           = 0x00000080,
};
typedef enum mipc_sys_cap_gsm_band_const_enum mipc_sys_cap_gsm_band_const_enum;

enum mipc_sys_cap_umts_band_const_enum {
    mipc_sys_cap_umts_band_const_NONE = 0,
    /* SYS_CAP_UMTS_BAND */
    MIPC_SYS_CAP_UMTS_BAND_I                                = 0x00000001,
    MIPC_SYS_CAP_UMTS_BAND_II                               = 0x00000002,
    MIPC_SYS_CAP_UMTS_BAND_III                              = 0x00000004,
    MIPC_SYS_CAP_UMTS_BAND_IV                               = 0x00000008,
    MIPC_SYS_CAP_UMTS_BAND_V                                = 0x00000010,
    MIPC_SYS_CAP_UMTS_BAND_VI                               = 0x00000020,
    MIPC_SYS_CAP_UMTS_BAND_VII                              = 0x00000040,
    MIPC_SYS_CAP_UMTS_BAND_VIII                             = 0x00000080,
    MIPC_SYS_CAP_UMTS_BAND_IX                               = 0x00000100,
    MIPC_SYS_CAP_UMTS_BAND_X                                = 0x00000200,
};
typedef enum mipc_sys_cap_umts_band_const_enum mipc_sys_cap_umts_band_const_enum;

enum mipc_sys_cap_cdma_band_const_enum {
    mipc_sys_cap_cdma_band_const_NONE = 0,
    /* SYS_CAP_CDMA_BAND */
    MIPC_SYS_CAP_CDMA_BAND_0                                = 0x00000001,
    MIPC_SYS_CAP_CDMA_BAND_1                                = 0x00000002,
    MIPC_SYS_CAP_CDMA_BAND_2                                = 0x00000004,
    MIPC_SYS_CAP_CDMA_BAND_3                                = 0x00000008,
    MIPC_SYS_CAP_CDMA_BAND_4                                = 0x00000010,
    MIPC_SYS_CAP_CDMA_BAND_5                                = 0x00000020,
    MIPC_SYS_CAP_CDMA_BAND_6                                = 0x00000040,
    MIPC_SYS_CAP_CDMA_BAND_7                                = 0x00000080,
    MIPC_SYS_CAP_CDMA_BAND_8                                = 0x00000100,
    MIPC_SYS_CAP_CDMA_BAND_9                                = 0x00000200,
    MIPC_SYS_CAP_CDMA_BAND_10                               = 0x00000400,
    MIPC_SYS_CAP_CDMA_BAND_11                               = 0x00000800,
    MIPC_SYS_CAP_CDMA_BAND_12                               = 0x00001000,
    MIPC_SYS_CAP_CDMA_BAND_13                               = 0x00002000,
    MIPC_SYS_CAP_CDMA_BAND_14                               = 0x00004000,
    MIPC_SYS_CAP_CDMA_BAND_15                               = 0x00008000,
    MIPC_SYS_CAP_CDMA_BAND_16                               = 0x00010000,
    MIPC_SYS_CAP_CDMA_BAND_17                               = 0x00020000,
    MIPC_SYS_CAP_CDMA_BAND_18                               = 0x00040000,
    MIPC_SYS_CAP_CDMA_BAND_19                               = 0x00080000,
    MIPC_SYS_CAP_CDMA_BAND_20                               = 0x00100000,
};
typedef enum mipc_sys_cap_cdma_band_const_enum mipc_sys_cap_cdma_band_const_enum;

enum mipc_sys_cap_tds_band_const_enum {
    mipc_sys_cap_tds_band_const_NONE = 0,
    /* SYS_CAP_TDS_BAND */
    MIPC_SYS_CAP_TDS_BAND_A                                 = 0x00000001,
    MIPC_SYS_CAP_TDS_BAND_B                                 = 0x00000002,
    MIPC_SYS_CAP_TDS_BAND_C                                 = 0x00000004,
    MIPC_SYS_CAP_TDS_BAND_D                                 = 0x00000008,
    MIPC_SYS_CAP_TDS_BAND_E                                 = 0x00000010,
    MIPC_SYS_CAP_TDS_BAND_F                                 = 0x00000020,
};
typedef enum mipc_sys_cap_tds_band_const_enum mipc_sys_cap_tds_band_const_enum;

enum mipc_sys_product_type_const_enum {
    mipc_sys_product_type_const_NONE = 0,
    /* SYS_PRODUCT_TYPE */
    MIPC_SYS_PRODUCT_TYPE_SMARTPHONE                        = 0x00,
    MIPC_SYS_PRODUCT_TYPE_DATACARD                          = 0x01,
};
typedef enum mipc_sys_product_type_const_enum mipc_sys_product_type_const_enum;

enum mipc_sys_config_class_const_enum {
    mipc_sys_config_class_const_NONE = 0,
    /* SYS_CONFIG_CLASS */
    /*  */
    MIPC_SYS_CONFIG_CLASS_GENERAL_MD_CONFIG                 = 0,
    /* for AT+EGMC support */
    MIPC_SYS_CONFIG_CLASS_LEGACY_MD_CONFIG                  = 1,
    /*  */
    MIPC_SYS_CONFIG_CLASS_HOST_RELAY_DIPC_CONFIG            = 2,
    /* for AT+EWOCFGSET support */
    MIPC_SYS_CONFIG_CLASS_N3X_CONFIG                        = 3,
    /* for AT+EIWLCFGSET support */
    MIPC_SYS_CONFIG_CLASS_IWLAN_CONFIG                      = 4,
};
typedef enum mipc_sys_config_class_const_enum mipc_sys_config_class_const_enum;

enum mipc_ims_config_class_const_enum {
    mipc_ims_config_class_const_NONE = 0,
    /* IMS_CONFIG_CLASS */
    /* for AT+EIMSCFG support */
    MIPC_IMS_CONFIG_CLASS_IMS_FEATURE                       = 0,
    /* for AT+ECFGSET support */
    MIPC_IMS_CONFIG_CLASS_IMS_CONFIG                        = 1,
    /* for AT+EPVSSET support */
    MIPC_IMS_CONFIG_CLASS_IMS_PROVISION                     = 2,
    /*  */
    MIPC_IMS_CONFIG_CLASS_IMS_CAPABILITY                    = 3,
};
typedef enum mipc_ims_config_class_const_enum mipc_ims_config_class_const_enum;

enum mipc_ims_config_ind_reason_const_enum {
    mipc_ims_config_ind_reason_const_NONE = 0,
    /* IMS_CONFIG_IND_REASON */
    MIPC_IMS_CONFIG_IND_REASON_IMS_READY                    = 0,
    MIPC_IMS_CONFIG_IND_REASON_USER_CHANGE                  = 1,
};
typedef enum mipc_ims_config_ind_reason_const_enum mipc_ims_config_ind_reason_const_enum;

enum mipc_ims_ind_type_const_enum {
    mipc_ims_ind_type_const_NONE = 0,
    /* IMS_IND_TYPE */
    MIPC_IMS_IND_TYPE_NOTIFY                                = 0,
    MIPC_IMS_IND_TYPE_INIT                                  = 1,
    MIPC_IMS_IND_TYPE_REJECT                                = 2,
    MIPC_IMS_IND_TYPE_MAX                                   = 0x7F,
};
typedef enum mipc_ims_ind_type_const_enum mipc_ims_ind_type_const_enum;

enum mipc_ims_state_ind_event_const_enum {
    mipc_ims_state_ind_event_const_NONE = 0,
    /* IMS_STATE_IND_EVENT */
    MIPC_IMS_STATE_IND_EVENT_REG_STATE                      = 0,
    MIPC_IMS_STATE_IND_EVENT_WFC                            = 1,
    MIPC_IMS_STATE_IND_EVENT_REG_URI                        = 2,
    MIPC_IMS_STATE_IND_EVENT_REG_RESP                       = 3,
};
typedef enum mipc_ims_state_ind_event_const_enum mipc_ims_state_ind_event_const_enum;

enum mipc_ims_state_const_enum {
    mipc_ims_state_const_NONE = 0,
    /* IMS_STATE */
    MIPC_IMS_STATE_UNREGISTERED                             = 0,
    MIPC_IMS_STATE_REGISTERED                               = 1,
    MIPC_IMS_STATE_UNREGISTERING                            = 2,
    MIPC_IMS_STATE_REGISTERING                              = 3,
    MIPC_IMS_STATE_REREGISTERING                            = 4,
};
typedef enum mipc_ims_state_const_enum mipc_ims_state_const_enum;

enum mipc_ims_ecc_ind_rat_const_enum {
    mipc_ims_ecc_ind_rat_const_NONE = 0,
    /* IMS_ECC_IND_RAT */
    MIPC_IMS_ECC_IND_RAT_GSM                                = 0,
    MIPC_IMS_ECC_IND_RAT_WCDMA                              = 1,
    MIPC_IMS_ECC_IND_RAT_TD_SCDMA                           = 2,
    MIPC_IMS_ECC_IND_RAT_FDD_LTE                            = 3,
    MIPC_IMS_ECC_IND_RAT_TDD_LTE                            = 4,
};
typedef enum mipc_ims_ecc_ind_rat_const_enum mipc_ims_ecc_ind_rat_const_enum;

enum mipc_ims_report_status_const_enum {
    mipc_ims_report_status_const_NONE = 0,
    /* IMS_REPORT_STATUS */
    MIPC_IMS_REPORT_STATUS_DISABLE_STATUS                   = 0,
    MIPC_IMS_REPORT_STATUS_ENABLE_STATUS                    = 1,
    MIPC_IMS_REPORT_STATUS_MAX                              = 2,
};
typedef enum mipc_ims_report_status_const_enum mipc_ims_report_status_const_enum;

enum mipc_nw_ims_vops_status_const_enum {
    mipc_nw_ims_vops_status_const_NONE = 0,
    /* NW_IMS_VOPS_STATUS */
    MIPC_NW_IMS_VOPS_STATUS_NOT_REV_FROM_NW                 = 0,
    MIPC_NW_IMS_VOPS_STATUS_REV_FROM_NW                     = 1,
    MIPC_NW_IMS_VOPS_STATUS_MAX                             = 2,
};
typedef enum mipc_nw_ims_vops_status_const_enum mipc_nw_ims_vops_status_const_enum;

enum mipc_sys_config_change_reason_const_enum {
    mipc_sys_config_change_reason_const_NONE = 0,
    /* SYS_CONFIG_CHANGE_REASON */
    MIPC_SYS_CONFIG_CHANGE_REASON_SIM_READY                 = 0,
    MIPC_SYS_CONFIG_CHANGE_REASON_USER_CHANGE               = 1,
};
typedef enum mipc_sys_config_change_reason_const_enum mipc_sys_config_change_reason_const_enum;

enum mipc_sys_adpclk_state_const_enum {
    mipc_sys_adpclk_state_const_NONE = 0,
    /* SYS_ADPCLK_STATE */
    /*  */
    MIPC_SYS_ADPCLK_STATE_DISABLE                           = 0,
    /*  */
    MIPC_SYS_ADPCLK_STATE_ENABLE                            = 1,
};
typedef enum mipc_sys_adpclk_state_const_enum mipc_sys_adpclk_state_const_enum;

enum mipc_sys_mcf_op_const_enum {
    mipc_sys_mcf_op_const_NONE = 0,
    /* SYS_MCF_OP */
    MIPC_SYS_MCF_OP_SET_OTA_AND_OPOTA_FILE_PATH             = 0,
    MIPC_SYS_MCF_OP_SET_OTA_FILE_PATH                       = 1,
    MIPC_SYS_MCF_OP_SET_OPOTA_FILE_PATH                     = 2,
    MIPC_SYS_MCF_OP_SET_FILE_PATH_IN_MCF_DSBP_ACTIVE_MODE   = 3,
    MIPC_SYS_MCF_OP_GET_APPLIED_FILE_PATH                   = 4,
    MIPC_SYS_MCF_OP_DUMP_LID_DATA                           = 5,
    MIPC_SYS_MCF_OP_SET_FILE_PATH_AND_AUTO_SELECT_BIN       = 6,
    MIPC_SYS_MCF_OP_UPDATE_OPOTA_FILE                       = 7,
    MIPC_SYS_MCF_OP_INI_OPERATION                           = 8,
    MIPC_SYS_MCF_OP_LID_VARIABLE_OPERATION                  = 9,
    MIPC_SYS_MCF_OP_QUERY_VARIABLE_VALUE                    = 10,
    MIPC_SYS_MCF_OP_ASSIGN_COMBINED_PATH                    = 11,
};
typedef enum mipc_sys_mcf_op_const_enum mipc_sys_mcf_op_const_enum;

enum mipc_sys_sar_mode_const_enum {
    mipc_sys_sar_mode_const_NONE = 0,
    /* SYS_SAR_MODE */
    MIPC_SYS_SAR_MODE_BY_DEVICE                             = 0x00,
    MIPC_SYS_SAR_MODE_BY_HOST                               = 0x01,
};
typedef enum mipc_sys_sar_mode_const_enum mipc_sys_sar_mode_const_enum;

enum mipc_sys_account_id_const_enum {
    mipc_sys_account_id_const_NONE = 0,
    /* SYS_ACCOUNT_ID */
    MIPC_SYS_ACCOUNT_ID_SIM1_NORMAL                         = 0,
    MIPC_SYS_ACCOUNT_ID_SIM1_EMERGENCY                      = 1,
    MIPC_SYS_ACCOUNT_ID_SIM2_NORMAL                         = 2,
    MIPC_SYS_ACCOUNT_ID_SIM2_EMERGENCY                      = 3,
};
typedef enum mipc_sys_account_id_const_enum mipc_sys_account_id_const_enum;

enum mipc_md_init_id_const_enum {
    mipc_md_init_id_const_NONE = 0,
    /* MD_INIT_ID */
    MIPC_MD_INIT_ID_SMS_READY                               = 1,
    MIPC_MD_INIT_ID_PHB_READY                               = 2,
    MIPC_MD_INIT_ID_CHANGE_EONS_FILE                        = 8,
    MIPC_MD_INIT_ID_INVALID_SIM                             = 16,
    MIPC_MD_INIT_ID_PHB_NOT_READY                           = 32,
    MIPC_MD_INIT_ID_TCM_READY                               = 64,
};
typedef enum mipc_md_init_id_const_enum mipc_md_init_id_const_enum;

enum mipc_sys_dsbp_mode_const_enum {
    mipc_sys_dsbp_mode_const_NONE = 0,
    /* SYS_DSBP_MODE */
    MIPC_SYS_DSBP_MODE_DISABLE                              = 0,
    MIPC_SYS_DSBP_MODE_ENABLE_IMS                           = 1,
    MIPC_SYS_DSBP_MODE_ENABLE_ALL                           = 2,
};
typedef enum mipc_sys_dsbp_mode_const_enum mipc_sys_dsbp_mode_const_enum;

enum mipc_sys_sbp_mode_const_enum {
    mipc_sys_sbp_mode_const_NONE = 0,
    /* SYS_SBP_MODE */
    MIPC_SYS_SBP_MODE_SET_SBP_ID                            = 0,
    MIPC_SYS_SBP_MODE_SET_CONFIG_WITH_FEATURE_INT           = 1,
    MIPC_SYS_SBP_MODE_SET_DATA_WITH_FEATURE_INT             = 2,
    MIPC_SYS_SBP_MODE_GET_CONFIG_WITH_FEATURE_INT           = 3,
    MIPC_SYS_SBP_MODE_GET_DATA_WITH_FEATURE_INT             = 4,
    MIPC_SYS_SBP_MODE_SET_CONFIG_WITH_FEATURE_STR           = 5,
    MIPC_SYS_SBP_MODE_SET_DATA_WITH_FEATURE_STR             = 6,
    MIPC_SYS_SBP_MODE_GET_CONFIG_WITH_FEATURE_STR           = 7,
    MIPC_SYS_SBP_MODE_GET_DATA_WITH_FEATURE_STR             = 8,
};
typedef enum mipc_sys_sbp_mode_const_enum mipc_sys_sbp_mode_const_enum;

enum mipc_apn_pdp_type_const_enum {
    mipc_apn_pdp_type_const_NONE = 0,
    /* APN_PDP_TYPE */
    MIPC_APN_PDP_TYPE_DEFAULT                               = 0,
    MIPC_APN_PDP_TYPE_IPV4                                  = 1,
    MIPC_APN_PDP_TYPE_IPV6                                  = 2,
    MIPC_APN_PDP_TYPE_IPV4V6                                = 3,
    MIPC_APN_PDP_TYPE_IPV4_AND_IPV6                         = 4,
};
typedef enum mipc_apn_pdp_type_const_enum mipc_apn_pdp_type_const_enum;

enum mipc_deact_reason_enum_const_enum {
    mipc_deact_reason_enum_const_NONE = 0,
    /* DEACT_REASON_ENUM */
    MIPC_DEACT_REASON_ENUM_DONT_CARE                        = 0,
    MIPC_DEACT_REASON_ENUM_DEACT_NORMAL                     = 1,
    MIPC_DEACT_REASON_ENUM_DEACT_NO_PCSCF                   = 3,
    MIPC_DEACT_REASON_ENUM_DEACT_FORCE_TO_LOCAL_RELEASE     = 6,
    MIPC_DEACT_REASON_ENUM_DEACT_AOSP_SHUTDOWN              = 7,
    MIPC_DEACT_REASON_ENUM_DEACT_AOSP_HANDOVER              = 8,
    MIPC_DEACT_REASON_ENUM_DEACT_APN_CHANGED                = 9,
    MIPC_DEACT_REASON_ENUM_DEACT_IMS_HANDOVER               = 10,
    MIPC_DEACT_REASON_ENUM_DEACT_TEMP_DATA_SWITCH           = 11,
    MIPC_DEACT_REASON_ENUM_DEACT_IPCA                       = 20,
    MIPC_DEACT_REASON_ENUM_MAX                              = 0x7F,
};
typedef enum mipc_deact_reason_enum_const_enum mipc_deact_reason_enum_const_enum;

enum mipc_apn_enabled_type_const_enum {
    mipc_apn_enabled_type_const_NONE = 0,
    /* APN_ENABLED_TYPE */
    MIPC_APN_ENABLED_TYPE_DISABLED                          = 0,
    MIPC_APN_ENABLED_TYPE_ENABLED                           = 1,
    MIPC_APN_ENABLED_TYPE_MAX                               = 2,
};
typedef enum mipc_apn_enabled_type_const_enum mipc_apn_enabled_type_const_enum;

enum mipc_ia_md_prefer_type_const_enum {
    mipc_ia_md_prefer_type_const_NONE = 0,
    /* IA_MD_PREFER_TYPE */
    MIPC_IA_MD_PREFER_TYPE_DISABLE_MD_PREFER                = 0,
    MIPC_IA_MD_PREFER_TYPE_ENABLE__MD_PREFER                = 1,
    MIPC_IA_MD_PREFER_TYPE_MAX                              = 2,
};
typedef enum mipc_ia_md_prefer_type_const_enum mipc_ia_md_prefer_type_const_enum;

enum mipc_eif_address_type_const_enum {
    mipc_eif_address_type_const_NONE = 0,
    /* EIF_ADDRESS_TYPE */
    MIPC_EIF_ADDRESS_TYPE_DEFAULT                           = 0,
    MIPC_EIF_ADDRESS_TYPE_IPV4                              = 1,
    MIPC_EIF_ADDRESS_TYPE_IPV6                              = 2,
    MIPC_EIF_ADDRESS_TYPE_IPV4V6                            = 3,
};
typedef enum mipc_eif_address_type_const_enum mipc_eif_address_type_const_enum;

enum mipc_apn_auth_type_const_enum {
    mipc_apn_auth_type_const_NONE = 0,
    /* APN_AUTH_TYPE */
    MIPC_APN_AUTH_TYPE_NONE                                 = 0,
    MIPC_APN_AUTH_TYPE_PAP                                  = 1,
    MIPC_APN_AUTH_TYPE_CHAP                                 = 2,
    MIPC_APN_AUTH_TYPE_PAP_OR_CHAP                          = 3,
};
typedef enum mipc_apn_auth_type_const_enum mipc_apn_auth_type_const_enum;

enum mipc_apn_type_const_enum {
    mipc_apn_type_const_NONE = 0,
    /* APN_TYPE */
    MIPC_APN_TYPE_UNKNOWN                                   = 0x00000000,
    MIPC_APN_TYPE_DEFAULT                                   = 0x00000001,
    MIPC_APN_TYPE_IMS                                       = 0x00000002,
    MIPC_APN_TYPE_MMS                                       = 0x00000004,
    MIPC_APN_TYPE_SUPL                                      = 0x00000008,
    MIPC_APN_TYPE_DUN                                       = 0x00000010,
    MIPC_APN_TYPE_HIPRI                                     = 0x00000020,
    MIPC_APN_TYPE_FOTA                                      = 0x00000040,
    MIPC_APN_TYPE_CBS                                       = 0x00000080,
    MIPC_APN_TYPE_EMERGENCY                                 = 0x00000100,
    MIPC_APN_TYPE_IA                                        = 0x00000200,
    MIPC_APN_TYPE_DM                                        = 0x00000400,
    MIPC_APN_TYPE_WAP                                       = 0x00000800,
    MIPC_APN_TYPE_NET                                       = 0x00001000,
    MIPC_APN_TYPE_CMMAIL                                    = 0x00002000,
    MIPC_APN_TYPE_TETHERING                                 = 0x00004000,
    MIPC_APN_TYPE_RCSE                                      = 0x00008000,
    MIPC_APN_TYPE_XCAP                                      = 0x00010000,
    MIPC_APN_TYPE_RCS                                       = 0x00020000,
    MIPC_APN_TYPE_RCS_PCSCF                                 = 0x00040000,
    MIPC_APN_TYPE_VSIM                                      = 0x00080000,
    MIPC_APN_TYPE_BIP                                       = 0x00100000,
    MIPC_APN_TYPE_NW_ASSIGNED                               = 0x80000000,
};
typedef enum mipc_apn_type_const_enum mipc_apn_type_const_enum;

enum mipc_apn_compression_const_enum {
    mipc_apn_compression_const_NONE = 0,
    /* APN_COMPRESSION */
    MIPC_APN_COMPRESSION_NONE                               = 0,
    MIPC_APN_COMPRESSION_ENABLE                             = 1,
};
typedef enum mipc_apn_compression_const_enum mipc_apn_compression_const_enum;

enum mipc_apn_profile_mode_const_enum {
    mipc_apn_profile_mode_const_NONE = 0,
    /* APN_PROFILE_MODE */
    MIPC_APN_PROFILE_MODE_HOST_NOT_SET_APN_PROFILE          = 0,
    MIPC_APN_PROFILE_MODE_HOST_SET_APN_PROFILE              = 1,
};
typedef enum mipc_apn_profile_mode_const_enum mipc_apn_profile_mode_const_enum;

enum mipc_data_fallback_type_const_enum {
    mipc_data_fallback_type_const_NONE = 0,
    /* DATA_FALLBACK_TYPE */
    MIPC_DATA_FALLBACK_TYPE_DISABLE                         = 0,
    MIPC_DATA_FALLBACK_TYPE_IPV4_FIRST                      = 1,
    MIPC_DATA_FALLBACK_TYPE_IPV6_FIRST                      = 2,
    MIPC_DATA_FALLBACK_TYPE_MAX                             = 0x7F,
};
typedef enum mipc_data_fallback_type_const_enum mipc_data_fallback_type_const_enum;

enum mipc_mipc_cid_act_state_const_enum {
    mipc_mipc_cid_act_state_const_NONE = 0,
    /* MIPC_CID_ACT_STATE */
    MIPC_MIPC_CID_ACT_STATE_DEACTIVATED                     = 0,
    MIPC_MIPC_CID_ACT_STATE_ACTIVATED                       = 1,
};
typedef enum mipc_mipc_cid_act_state_const_enum mipc_mipc_cid_act_state_const_enum;

enum mipc_data_reuse_type_const_enum {
    mipc_data_reuse_type_const_NONE = 0,
    /* DATA_REUSE_TYPE */
    MIPC_DATA_REUSE_TYPE_DEFAULT                            = 0,
    MIPC_DATA_REUSE_TYPE_USER_SETTING_FIRST                 = 1,
    MIPC_DATA_REUSE_TYPE_NOT_REUSE                          = 2,
    MIPC_DATA_REUSE_TYPE_REUSE_ONLY                         = 3,
};
typedef enum mipc_data_reuse_type_const_enum mipc_data_reuse_type_const_enum;

enum mipc_data_config_type_const_enum {
    mipc_data_config_type_const_NONE = 0,
    /* DATA_CONFIG_TYPE */
    MIPC_DATA_CONFIG_TYPE_DISABLE                           = 0,
    MIPC_DATA_CONFIG_TYPE_ENABLE                            = 1,
    MIPC_DATA_CONFIG_TYPE_NO_CHANGE                         = 2,
};
typedef enum mipc_data_config_type_const_enum mipc_data_config_type_const_enum;

enum mipc_data_retry_mode_const_enum {
    mipc_data_retry_mode_const_NONE = 0,
    /* DATA_RETRY_MODE */
    MIPC_DATA_RETRY_MODE_QUERY_TIMER                        = 0,
    MIPC_DATA_RETRY_MODE_RESET_TIMER                        = 1,
    MIPC_DATA_RETRY_MODE_RETRY_AFTER_TIMER                  = 2,
};
typedef enum mipc_data_retry_mode_const_enum mipc_data_retry_mode_const_enum;

enum mipc_data_retry_type_const_enum {
    mipc_data_retry_type_const_NONE = 0,
    /* DATA_RETRY_TYPE */
    MIPC_DATA_RETRY_TYPE_RETRY_TYPE_NO_SUGGEST              = 0,
    MIPC_DATA_RETRY_TYPE_RETRY_TYPE_NO_RETRY                = 1,
    MIPC_DATA_RETRY_TYPE_RETRY_TYPE_WITH_SUGGEST            = 2,
};
typedef enum mipc_data_retry_type_const_enum mipc_data_retry_type_const_enum;

enum mipc_data_lce_mode_const_enum {
    mipc_data_lce_mode_const_NONE = 0,
    /* DATA_LCE_MODE */
    MIPC_DATA_LCE_MODE_DISABLE                              = 0,
    MIPC_DATA_LCE_MODE_ENABLE                               = 1,
    MIPC_DATA_LCE_MODE_SET                                  = 2,
};
typedef enum mipc_data_lce_mode_const_enum mipc_data_lce_mode_const_enum;

enum mipc_data_keepalive_status_code_const_enum {
    mipc_data_keepalive_status_code_const_NONE = 0,
    /* DATA_KEEPALIVE_STATUS_CODE */
    MIPC_DATA_KEEPALIVE_STATUS_CODE_ACTIVE                  = 0,
    MIPC_DATA_KEEPALIVE_STATUS_CODE_INACTIVE                = 1,
    MIPC_DATA_KEEPALIVE_STATUS_CODE_PENDING                 = 2,
};
typedef enum mipc_data_keepalive_status_code_const_enum mipc_data_keepalive_status_code_const_enum;

enum mipc_data_keepalive_type_const_enum {
    mipc_data_keepalive_type_const_NONE = 0,
    /* DATA_KEEPALIVE_TYPE */
    MIPC_DATA_KEEPALIVE_TYPE_NATT_IPV4                      = 0,
    MIPC_DATA_KEEPALIVE_TYPE_NATT_IPV6                      = 1,
};
typedef enum mipc_data_keepalive_type_const_enum mipc_data_keepalive_type_const_enum;

enum mipc_data_lgdcont_req_type_const_enum {
    mipc_data_lgdcont_req_type_const_NONE = 0,
    /* DATA_LGDCONT_REQ_TYPE */
    MIPC_DATA_LGDCONT_REQ_TYPE_NEW_PDP_OR_HANDOVER          = 0,
    MIPC_DATA_LGDCONT_REQ_TYPE_EMERGENCY_PDP                = 1,
    MIPC_DATA_LGDCONT_REQ_TYPE_NEW_PDP                      = 2,
    MIPC_DATA_LGDCONT_REQ_TYPE_HANDOVER                     = 3,
    MIPC_DATA_LGDCONT_REQ_TYPE_EMERGENCY_HANDOVER           = 4,
};
typedef enum mipc_data_lgdcont_req_type_const_enum mipc_data_lgdcont_req_type_const_enum;

enum mipc_data_lgdcont_rat_type_const_enum {
    mipc_data_lgdcont_rat_type_const_NONE = 0,
    /* DATA_LGDCONT_RAT_TYPE */
    MIPC_DATA_LGDCONT_RAT_TYPE_All_RAT                      = 0,
    MIPC_DATA_LGDCONT_RAT_TYPE_RAT_23G                      = 1,
    MIPC_DATA_LGDCONT_RAT_TYPE_RAT_4G                       = 2,
};
typedef enum mipc_data_lgdcont_rat_type_const_enum mipc_data_lgdcont_rat_type_const_enum;

enum mipc_data_mod_event_type_const_enum {
    mipc_data_mod_event_type_const_NONE = 0,
    /* DATA_MOD_EVENT_TYPE */
    MIPC_DATA_MOD_EVENT_TYPE_INFORMATIONAL_EVENT            = 0,
    MIPC_DATA_MOD_EVENT_TYPE_ACKNOWLEDGEMENT_REQUIRED       = 1,
};
typedef enum mipc_data_mod_event_type_const_enum mipc_data_mod_event_type_const_enum;

enum mipc_mipc_eiwlpl_priority_type_const_enum {
    mipc_mipc_eiwlpl_priority_type_const_NONE = 0,
    /* MIPC_EIWLPL_PRIORITY_TYPE */
    MIPC_MIPC_EIWLPL_PRIORITY_TYPE_START                    = 0,
    MIPC_MIPC_EIWLPL_PRIORITY_TYPE_NULL                     = 1,
    MIPC_MIPC_EIWLPL_PRIORITY_TYPE_CELLULAR                 = 2,
    MIPC_MIPC_EIWLPL_PRIORITY_TYPE_WIFI                     = 3,
    MIPC_MIPC_EIWLPL_PRIORITY_TYPE_CELLULAR_GREATER_THAN_WIFI = 4,
    MIPC_MIPC_EIWLPL_PRIORITY_TYPE_WIFI_GREATER_THAN_CELLULAR = 5,
    MIPC_MIPC_EIWLPL_PRIORITY_TYPE_END                      = 6,
};
typedef enum mipc_mipc_eiwlpl_priority_type_const_enum mipc_mipc_eiwlpl_priority_type_const_enum;

enum mipc_internal_eif_req_cmd_const_enum {
    mipc_internal_eif_req_cmd_const_NONE = 0,
    /* INTERNAL_EIF_REQ_CMD */
    MIPC_INTERNAL_EIF_REQ_CMD_IFUP                          = 0,
    MIPC_INTERNAL_EIF_REQ_CMD_IFDOWN                        = 1,
    MIPC_INTERNAL_EIF_REQ_CMD_IPUPDATE                      = 2,
    MIPC_INTERNAL_EIF_REQ_CMD_IFQUERY                       = 3,
    MIPC_INTERNAL_EIF_REQ_CMD_NO_RA_INITIAL                 = 4,
    MIPC_INTERNAL_EIF_REQ_CMD_NO_RA_REFRESH                 = 5,
    MIPC_INTERNAL_EIF_REQ_CMD_IPADD                         = 6,
    MIPC_INTERNAL_EIF_REQ_CMD_IPDEL                         = 7,
    MIPC_INTERNAL_EIF_REQ_CMD_IPCHG                         = 8,
};
typedef enum mipc_internal_eif_req_cmd_const_enum mipc_internal_eif_req_cmd_const_enum;

enum mipc_internal_eif_ind_cmd_const_enum {
    mipc_internal_eif_ind_cmd_const_NONE = 0,
    /* INTERNAL_EIF_IND_CMD */
    MIPC_INTERNAL_EIF_IND_CMD_IFUP                          = 0,
    MIPC_INTERNAL_EIF_IND_CMD_IFDOWN                        = 1,
    MIPC_INTERNAL_EIF_IND_CMD_IPCHG                         = 4,
    MIPC_INTERNAL_EIF_IND_CMD_IFCHANGE                      = 5,
    MIPC_INTERNAL_EIF_IND_CMD_MTU                           = 6,
};
typedef enum mipc_internal_eif_ind_cmd_const_enum mipc_internal_eif_ind_cmd_const_enum;

enum mipc_internal_eipport_action_const_enum {
    mipc_internal_eipport_action_const_NONE = 0,
    /* INTERNAL_EIPPORT_ACTION */
    MIPC_INTERNAL_EIPPORT_ACTION_ALLOC                      = 0,
    MIPC_INTERNAL_EIPPORT_ACTION_FREE                       = 1,
};
typedef enum mipc_internal_eipport_action_const_enum mipc_internal_eipport_action_const_enum;

enum mipc_internal_eipport_result_const_enum {
    mipc_internal_eipport_result_const_NONE = 0,
    /* INTERNAL_EIPPORT_RESULT */
    MIPC_INTERNAL_EIPPORT_RESULT_FAILURE                    = 0,
    MIPC_INTERNAL_EIPPORT_RESULT_SUCCESS                    = 1,
};
typedef enum mipc_internal_eipport_result_const_enum mipc_internal_eipport_result_const_enum;

enum mipc_internal_eipspi_action_const_enum {
    mipc_internal_eipspi_action_const_NONE = 0,
    /* INTERNAL_EIPSPI_ACTION */
    MIPC_INTERNAL_EIPSPI_ACTION_ALLOC                       = 0,
    MIPC_INTERNAL_EIPSPI_ACTION_FREE                        = 1,
};
typedef enum mipc_internal_eipspi_action_const_enum mipc_internal_eipspi_action_const_enum;

enum mipc_internal_ho_progress_const_enum {
    mipc_internal_ho_progress_const_NONE = 0,
    /* INTERNAL_HO_PROGRESS */
    MIPC_INTERNAL_HO_PROGRESS_START                         = 0,
    MIPC_INTERNAL_HO_PROGRESS_END                           = 1,
    MIPC_INTERNAL_HO_PROGRESS_IP_READY                      = 2,
    MIPC_INTERNAL_HO_PROGRESS_MAX                           = 0x7F,
};
typedef enum mipc_internal_ho_progress_const_enum mipc_internal_ho_progress_const_enum;

enum mipc_dsda_allowed_type_const_enum {
    mipc_dsda_allowed_type_const_NONE = 0,
    /* DSDA_ALLOWED_TYPE */
    MIPC_DSDA_ALLOWED_TYPE_NOT_ALLOWED                      = 0,
    MIPC_DSDA_ALLOWED_TYPE_ALLOWED                          = 1,
    MIPC_DSDA_ALLOWED_TYPE_MAX                              = 0x7F,
};
typedef enum mipc_dsda_allowed_type_const_enum mipc_dsda_allowed_type_const_enum;

enum mipc_dsda_state_type_const_enum {
    mipc_dsda_state_type_const_NONE = 0,
    /* DSDA_STATE_TYPE */
    MIPC_DSDA_STATE_TYPE_ACTIVE                             = 0,
    MIPC_DSDA_STATE_TYPE_POSSIBLE                           = 1,
    MIPC_DSDA_STATE_TYPE_NOT_POSSIBLE                       = 2,
    MIPC_DSDA_STATE_TYPE_MAX                                = 0x7F,
};
typedef enum mipc_dsda_state_type_const_enum mipc_dsda_state_type_const_enum;

enum mipc_psi_action_enum_const_enum {
    mipc_psi_action_enum_const_NONE = 0,
    /* PSI_ACTION_ENUM */
    MIPC_PSI_ACTION_ENUM_RELEASE                            = 0,
    MIPC_PSI_ACTION_ENUM_OCCUPY                             = 1,
    MIPC_PSI_ACTION_ENUM_QUERY                              = 2,
    MIPC_PSI_ACTION_ENUM_INJECT                             = 3,
    MIPC_PSI_ACTION_ENUM_REQUIRE                            = 4,
    MIPC_PSI_ACTION_ENUM_MAX                                = 0x7F,
};
typedef enum mipc_psi_action_enum_const_enum mipc_psi_action_enum_const_enum;

enum mipc_ursp_route_supp_profile_type_enum_const_enum {
    mipc_ursp_route_supp_profile_type_enum_const_NONE = 0,
    /* URSP_ROUTE_SUPP_PROFILE_TYPE_ENUM */
    MIPC_URSP_ROUTE_SUPP_PROFILE_TYPE_ENUM_REQ              = 1,
    MIPC_URSP_ROUTE_SUPP_PROFILE_TYPE_ENUM_MAX              = 0x7FFFFFFF,
};
typedef enum mipc_ursp_route_supp_profile_type_enum_const_enum mipc_ursp_route_supp_profile_type_enum_const_enum;

enum mipc_ursp_reeval_type_enum_const_enum {
    mipc_ursp_reeval_type_enum_const_NONE = 0,
    /* URSP_REEVAL_TYPE_ENUM */
    MIPC_URSP_REEVAL_TYPE_ENUM_PERIODIC                     = 1,
    MIPC_URSP_REEVAL_TYPE_ENUM_PDU_REL                      = 2,
    MIPC_URSP_REEVAL_TYPE_ENUM_PCF_UPDATE                   = 3,
    MIPC_URSP_REEVAL_TYPE_ENUM_INTER_SYS                    = 4,
    MIPC_URSP_REEVAL_TYPE_ENUM_REG                          = 5,
    MIPC_URSP_REEVAL_TYPE_ENUM_WLAN_EST                     = 6,
    MIPC_URSP_REEVAL_TYPE_ENUM_WLAN_REL                     = 7,
    MIPC_URSP_REEVAL_TYPE_ENUM_ALLOWED_NSSAI                = 8,
    MIPC_URSP_REEVAL_TYPE_ENUM_LADN                         = 9,
    MIPC_URSP_REEVAL_TYPE_ENUM_MAX                          = 0x7FFFFFFF,
};
typedef enum mipc_ursp_reeval_type_enum_const_enum mipc_ursp_reeval_type_enum_const_enum;

enum mipc_nssai_type_enum_const_enum {
    mipc_nssai_type_enum_const_NONE = 0,
    /* NSSAI_TYPE_ENUM */
    MIPC_NSSAI_TYPE_ENUM_DEFAULT_CONFIGURED_NSSAI           = 0,
    MIPC_NSSAI_TYPE_ENUM_DEFAULT_CONFIGURED_AND_REJECT_NSSAI = 1,
    MIPC_NSSAI_TYPE_ENUM_DEFAULT_CONFIGURED_AND_REJECT_AND_CONFIGURED_NSSAI = 2,
    MIPC_NSSAI_TYPE_ENUM_DEFAULT_CONFIGURED_AND_REJECT_AND_CONFIGURED_AND_ALLOWED_NSSAI = 3,
    MIPC_NSSAI_TYPE_ENUM_MAX                                = 0x7F,
};
typedef enum mipc_nssai_type_enum_const_enum mipc_nssai_type_enum_const_enum;

enum mipc_nw_radio_state_const_enum {
    mipc_nw_radio_state_const_NONE = 0,
    /* NW_RADIO_STATE */
    MIPC_NW_RADIO_STATE_OFF                                 = 0,
    MIPC_NW_RADIO_STATE_ON                                  = 1,
};
typedef enum mipc_nw_radio_state_const_enum mipc_nw_radio_state_const_enum;

enum mipc_nw_radio_state_cause_const_enum {
    mipc_nw_radio_state_cause_const_NONE = 0,
    /* NW_RADIO_STATE_CAUSE */
    MIPC_NW_RADIO_STATE_CAUSE_UNSPECIFIED                   = 0,
    MIPC_NW_RADIO_STATE_CAUSE_DUPLEX_MODE_CHANGE            = 1,
    MIPC_NW_RADIO_STATE_CAUSE_POWER_OFF                     = 2,
    MIPC_NW_RADIO_STATE_CAUSE_SIM_SWITCH                    = 3,
};
typedef enum mipc_nw_radio_state_cause_const_enum mipc_nw_radio_state_cause_const_enum;

enum mipc_nw_provider_state_const_enum {
    mipc_nw_provider_state_const_NONE = 0,
    /* NW_PROVIDER_STATE */
    /*  */
    MIPC_NW_PROVIDER_STATE_UNKNOWN                          = 0,
    /*  */
    MIPC_NW_PROVIDER_STATE_AVAILABLE                        = 1,
    /*  */
    MIPC_NW_PROVIDER_STATE_CURRENT                          = 2,
    /*  */
    MIPC_NW_PROVIDER_STATE_FORBIDDEN                        = 3,
};
typedef enum mipc_nw_provider_state_const_enum mipc_nw_provider_state_const_enum;

enum mipc_nw_register_mode_const_enum {
    mipc_nw_register_mode_const_NONE = 0,
    /* NW_REGISTER_MODE */
    MIPC_NW_REGISTER_MODE_AUTOMATIC                         = 0,
    MIPC_NW_REGISTER_MODE_MANUAL                            = 1,
    MIPC_NW_REGISTER_MODE_MANUAL_EXT                        = 4,
    MIPC_NW_REGISTER_MODE_SEMI_AUTO                         = 5,
};
typedef enum mipc_nw_register_mode_const_enum mipc_nw_register_mode_const_enum;

enum mipc_nw_register_state_const_enum {
    mipc_nw_register_state_const_NONE = 0,
    /* NW_REGISTER_STATE */
    MIPC_NW_REGISTER_STATE_NOT_REGISTERED                   = 0,
    MIPC_NW_REGISTER_STATE_HOME                             = 1,
    MIPC_NW_REGISTER_STATE_SEARCHING                        = 2,
    MIPC_NW_REGISTER_STATE_DENIED                           = 3,
    MIPC_NW_REGISTER_STATE_UNKNOWN                          = 4,
    MIPC_NW_REGISTER_STATE_ROAMING                          = 5,
    MIPC_NW_REGISTER_STATE_HOME_SMS_ONLY                    = 6,
    MIPC_NW_REGISTER_STATE_ROAMING_SMS_ONLY                 = 7,
    MIPC_NW_REGISTER_STATE_ATTACHED_ECC_ONLY                = 8,
    MIPC_NW_REGISTER_STATE_HOME_CSFB_NOT_PREF               = 9,
    MIPC_NW_REGISTER_STATE_ROAMING_CSFB_NOT_PREF            = 10,
};
typedef enum mipc_nw_register_state_const_enum mipc_nw_register_state_const_enum;

enum mipc_nw_ps_const_enum {
    mipc_nw_ps_const_NONE = 0,
    /* NW_PS */
    MIPC_NW_PS_DETACH                                       = 0,
    MIPC_NW_PS_ATTACH                                       = 1,
};
typedef enum mipc_nw_ps_const_enum mipc_nw_ps_const_enum;

enum mipc_nw_ia_const_enum {
    mipc_nw_ia_const_NONE = 0,
    /* NW_IA */
    MIPC_NW_IA_DETACH                                       = 0,
    MIPC_NW_IA_ATTACH                                       = 1,
};
typedef enum mipc_nw_ia_const_enum mipc_nw_ia_const_enum;

enum mipc_nw_fast_dormancy_const_enum {
    mipc_nw_fast_dormancy_const_NONE = 0,
    /* NW_FAST_DORMANCY */
    MIPC_NW_FAST_DORMANCY_DISABLE                           = 0,
    MIPC_NW_FAST_DORMANCY_ENABLE                            = 1,
    MIPC_NW_FAST_DORMANCY_SET_TIMER                         = 2,
    MIPC_NW_FAST_DORMANCY_SCREEN_STATUS                     = 3,
};
typedef enum mipc_nw_fast_dormancy_const_enum mipc_nw_fast_dormancy_const_enum;

enum mipc_nw_blacklist_type_const_enum {
    mipc_nw_blacklist_type_const_NONE = 0,
    /* NW_BLACKLIST_TYPE */
    MIPC_NW_BLACKLIST_TYPE_SIM                              = 0,
    MIPC_NW_BLACKLIST_TYPE_NETWORK                          = 1,
};
typedef enum mipc_nw_blacklist_type_const_enum mipc_nw_blacklist_type_const_enum;

enum mipc_nw_cell_type_const_enum {
    mipc_nw_cell_type_const_NONE = 0,
    /* NW_CELL_TYPE */
    MIPC_NW_CELL_TYPE_NONE                                  = 0,
    MIPC_NW_CELL_TYPE_GSM                                   = 1,
    MIPC_NW_CELL_TYPE_CDMA                                  = 2,
    MIPC_NW_CELL_TYPE_LTE                                   = 3,
    MIPC_NW_CELL_TYPE_UMTS                                  = 4,
    MIPC_NW_CELL_TYPE_TD_SCDMA                              = 5,
    MIPC_NW_CELL_TYPE_NR                                    = 6,
    /* Just valid when in NSA case, this means the cell info has LTE and NR. */
    MIPC_NW_CELL_TYPE_NSA_EXT                               = 7,
};
typedef enum mipc_nw_cell_type_const_enum mipc_nw_cell_type_const_enum;

enum mipc_nw_ch_lock_const_enum {
    mipc_nw_ch_lock_const_NONE = 0,
    /* NW_CH_LOCK */
    MIPC_NW_CH_LOCK_CANCEL                                  = 0,
    MIPC_NW_CH_LOCK_ENABLE_CH_LK_EM                         = 1,
    MIPC_NW_CH_LOCK_ENABLE_CH_LK_CBRS                       = 2,
    MIPC_NW_CH_LOCK_CONFIG_CH_LK_CBRS                       = 3,
};
typedef enum mipc_nw_ch_lock_const_enum mipc_nw_ch_lock_const_enum;

enum mipc_nw_ch_lock_mode_const_enum {
    mipc_nw_ch_lock_mode_const_NONE = 0,
    /* NW_CH_LOCK_MODE */
    MIPC_NW_CH_LOCK_MODE_IDLE_MODE_ONLY                     = 0,
    MIPC_NW_CH_LOCK_MODE_IDLE_MR                            = 1,
    MIPC_NW_CH_LOCK_MODE_IDLE_HOCCO                         = 2,
    MIPC_NW_CH_LOCK_MODE_IDLE_AND_CONNECTED                 = 3,
    MIPC_NW_CH_LOCK_MODE_UNCHANGED                          = 255,
};
typedef enum mipc_nw_ch_lock_mode_const_enum mipc_nw_ch_lock_mode_const_enum;

enum mipc_nw_data_speed_const_enum {
    mipc_nw_data_speed_const_NONE = 0,
    /* NW_DATA_SPEED */
    MIPC_NW_DATA_SPEED_NONE_SPECIFIED                       = 0x0000,
    MIPC_NW_DATA_SPEED_GPRS                                 = 0x0001,
    MIPC_NW_DATA_SPEED_EDGE                                 = 0x0002,
    MIPC_NW_DATA_SPEED_UMTS                                 = 0x0004,
    MIPC_NW_DATA_SPEED_HSDPA                                = 0x0008,
    MIPC_NW_DATA_SPEED_HSUPA                                = 0x0010,
    MIPC_NW_DATA_SPEED_HSDPA_UPA                            = 0x0018,
    MIPC_NW_DATA_SPEED_HSDPAP                               = 0x0020,
    MIPC_NW_DATA_SPEED_HSDPAP_UPA                           = 0x0030,
    MIPC_NW_DATA_SPEED_HSUPAP                               = 0x0040,
    MIPC_NW_DATA_SPEED_HSUPAP_DPA                           = 0x0048,
    MIPC_NW_DATA_SPEED_HSPAP                                = 0x0060,
    MIPC_NW_DATA_SPEED_DC_DPA                               = 0x0088,
    MIPC_NW_DATA_SPEED_DC_DPA_UPA                           = 0x0098,
    MIPC_NW_DATA_SPEED_DC_HSDPAP                            = 0x00a0,
    MIPC_NW_DATA_SPEED_DC_HSDPAP_UPA                        = 0x00b0,
    MIPC_NW_DATA_SPEED_DC_HSUPAP_DPA                        = 0x00c8,
    MIPC_NW_DATA_SPEED_DC_HSPAP                             = 0x00e0,
    MIPC_NW_DATA_SPEED_1XRTT                                = 0x0100,
    MIPC_NW_DATA_SPEED_HRPD                                 = 0x0200,
    MIPC_NW_DATA_SPEED_EHRPD                                = 0x0400,
    MIPC_NW_DATA_SPEED_LTE                                  = 0x1000,
    MIPC_NW_DATA_SPEED_LTE_CA                               = 0x2000,
    MIPC_NW_DATA_SPEED_ENDC                                 = 0x4000,
    MIPC_NW_DATA_SPEED_NR                                   = 0x8000,
    MIPC_NW_DATA_SPEED_NOT_CHANGE                           = 0xffff,
};
typedef enum mipc_nw_data_speed_const_enum mipc_nw_data_speed_const_enum;

enum mipc_nw_signal_type_const_enum {
    mipc_nw_signal_type_const_NONE = 0,
    /* NW_SIGNAL_TYPE */
    MIPC_NW_SIGNAL_TYPE_GSM                                 = 0,
    MIPC_NW_SIGNAL_TYPE_UMTS                                = 1,
    MIPC_NW_SIGNAL_TYPE_LTE                                 = 2,
    MIPC_NW_SIGNAL_TYPE_NR                                  = 3,
    MIPC_NW_SIGNAL_TYPE_NR_NSA                              = 4,
    MIPC_NW_SIGNAL_TYPE_CDMA                                = 5,
};
typedef enum mipc_nw_signal_type_const_enum mipc_nw_signal_type_const_enum;

enum mipc_nw_cscon_mode_const_enum {
    mipc_nw_cscon_mode_const_NONE = 0,
    /* NW_CSCON_MODE */
    MIPC_NW_CSCON_MODE_IDLE                                 = 0,
    MIPC_NW_CSCON_MODE_CONNECTED                            = 1,
    MIPC_NW_CSCON_MODE_UNKNOWN                              = 255,
};
typedef enum mipc_nw_cscon_mode_const_enum mipc_nw_cscon_mode_const_enum;

enum mipc_nw_cscon_state_const_enum {
    mipc_nw_cscon_state_const_NONE = 0,
    /* NW_CSCON_STATE */
    MIPC_NW_CSCON_STATE_UTRAN_URA_PCH                       = 0,
    MIPC_NW_CSCON_STATE_UTRAN_CELL_PCH                      = 1,
    MIPC_NW_CSCON_STATE_UTRAN_CELL_FACH                     = 2,
    MIPC_NW_CSCON_STATE_UTRAN_CELL_DCH                      = 3,
    MIPC_NW_CSCON_STATE_GERAN_CS_CONNECTED                  = 4,
    MIPC_NW_CSCON_STATE_GERAN_PS_CONNECTED                  = 5,
    MIPC_NW_CSCON_STATE_GERAN_CS_PS_CONNECTED               = 6,
    MIPC_NW_CSCON_STATE_EUTRAN_CONNECTED                    = 7,
    MIPC_NW_CSCON_STATE_NR_RAN_CONNECTED                    = 8,
    MIPC_NW_CSCON_STATE_NR_RAN_INACTIVE                     = 8,
    MIPC_NW_CSCON_STATE_UNKNOWN                             = 255,
};
typedef enum mipc_nw_cscon_state_const_enum mipc_nw_cscon_state_const_enum;

enum mipc_nw_cscon_access_const_enum {
    mipc_nw_cscon_access_const_NONE = 0,
    /* NW_CSCON_ACCESS */
    MIPC_NW_CSCON_ACCESS_GERAN                              = 0,
    MIPC_NW_CSCON_ACCESS_UTRAN_TDD                          = 1,
    MIPC_NW_CSCON_ACCESS_UTRAN_FDD                          = 2,
    MIPC_NW_CSCON_ACCESS_EUTRAN_TDD                         = 3,
    MIPC_NW_CSCON_ACCESS_EUTRAN_FDD                         = 4,
    MIPC_NW_CSCON_ACCESS_NR                                 = 5,
    MIPC_NW_CSCON_ACCESS_UNKNOWN                            = 255,
};
typedef enum mipc_nw_cscon_access_const_enum mipc_nw_cscon_access_const_enum;

enum mipc_nw_cscon_core_network_const_enum {
    mipc_nw_cscon_core_network_const_NONE = 0,
    /* NW_CSCON_CORE_NETWORK */
    MIPC_NW_CSCON_CORE_NETWORK_EPC                          = 0,
    MIPC_NW_CSCON_CORE_NETWORK_5GCN                         = 1,
    MIPC_NW_CSCON_CORE_NETWORK_UNKNOWN                      = 255,
};
typedef enum mipc_nw_cscon_core_network_const_enum mipc_nw_cscon_core_network_const_enum;

enum mipc_nw_prefer_rat_type_const_enum {
    mipc_nw_prefer_rat_type_const_NONE = 0,
    /* NW_PREFER_RAT_TYPE */
    MIPC_NW_PREFER_RAT_TYPE_GSM                             = 1,
    MIPC_NW_PREFER_RAT_TYPE_UMTS                            = 2,
    MIPC_NW_PREFER_RAT_TYPE_LTE                             = 4,
    MIPC_NW_PREFER_RAT_TYPE_NR                              = 128,
};
typedef enum mipc_nw_prefer_rat_type_const_enum mipc_nw_prefer_rat_type_const_enum;

enum mipc_nw_lte_carrier_arrregation_switch_const_enum {
    mipc_nw_lte_carrier_arrregation_switch_const_NONE = 0,
    /* NW_LTE_CARRIER_ARRREGATION_SWITCH */
    MIPC_NW_LTE_CARRIER_ARRREGATION_SWITCH_TURNOFF          = 0,
    MIPC_NW_LTE_CARRIER_ARRREGATION_SWITCH_TURNON           = 1,
};
typedef enum mipc_nw_lte_carrier_arrregation_switch_const_enum mipc_nw_lte_carrier_arrregation_switch_const_enum;

enum mipc_nw_ps_cs_reg_state_const_enum {
    mipc_nw_ps_cs_reg_state_const_NONE = 0,
    /* NW_PS_CS_REG_STATE */
    MIPC_NW_PS_CS_REG_STATE_IN_SERVICE                      = 0,
    MIPC_NW_PS_CS_REG_STATE_OUT_OF_SERVICE                  = 1,
    MIPC_NW_PS_CS_REG_STATE_EMERGENCY_ONLY                  = 2,
    MIPC_NW_PS_CS_REG_STATE_POWER_OFF                       = 3,
};
typedef enum mipc_nw_ps_cs_reg_state_const_enum mipc_nw_ps_cs_reg_state_const_enum;

enum mipc_nw_ps_cs_roaming_type_const_enum {
    mipc_nw_ps_cs_roaming_type_const_NONE = 0,
    /* NW_PS_CS_ROAMING_TYPE */
    MIPC_NW_PS_CS_ROAMING_TYPE_NOT_ROAMING                  = 0,
    MIPC_NW_PS_CS_ROAMING_TYPE_UNKNOWN                      = 1,
    MIPC_NW_PS_CS_ROAMING_TYPE_DOMESTIC                     = 2,
    MIPC_NW_PS_CS_ROAMING_TYPE_INTERNATIONAL                = 3,
};
typedef enum mipc_nw_ps_cs_roaming_type_const_enum mipc_nw_ps_cs_roaming_type_const_enum;

enum mipc_nw_ril_ps_cs_reg_state_const_enum {
    mipc_nw_ril_ps_cs_reg_state_const_NONE = 0,
    /* NW_RIL_PS_CS_REG_STATE */
    MIPC_NW_RIL_PS_CS_REG_STATE_NOT_REGISTERED_AND_NOT_SEARCHING = 0,
    MIPC_NW_RIL_PS_CS_REG_STATE_HOME_NETWORK                = 1,
    MIPC_NW_RIL_PS_CS_REG_STATE_NOT_REGISTERED_AND_SEARCHING = 2,
    MIPC_NW_RIL_PS_CS_REG_STATE_REG_DENIED                  = 3,
    MIPC_NW_RIL_PS_CS_REG_STATE_UNKNOWN                     = 4,
    MIPC_NW_RIL_PS_CS_REG_STATE_ROAMING                     = 5,
    MIPC_NW_RIL_PS_CS_REG_STATE_GOOGLE_UNDEFINED1           = 6,
    MIPC_NW_RIL_PS_CS_REG_STATE_GOOGLE_UNDEFINED2           = 7,
    MIPC_NW_RIL_PS_CS_REG_STATE_GOOGLE_UNDEFINED3           = 8,
    MIPC_NW_RIL_PS_CS_REG_STATE_GOOGLE_UNDEFINED4           = 9,
    MIPC_NW_RIL_PS_CS_REG_STATE_NOT_REGISTERED_AND_NOT_SEARCHING_EMERGENCY_CALL_ENABLED = 10,
    MIPC_NW_RIL_PS_CS_REG_STATE_GOOGLE_UNDEFINED5           = 11,
    MIPC_NW_RIL_PS_CS_REG_STATE_NOT_REGISTERED_AND_SEARCHING_EMERGENCY_CALL_ENABLED = 12,
    MIPC_NW_RIL_PS_CS_REG_STATE_REG_DENIED_EMERGENCY_CALL_ENABLED = 13,
    MIPC_NW_RIL_PS_CS_REG_STATE_UNKNOWN_EMERGENCY_CALL_ENABLED = 14,
    MIPC_NW_RIL_PS_CS_REG_STATE_GOOGLE_UNDEFINED6           = 15,
};
typedef enum mipc_nw_ril_ps_cs_reg_state_const_enum mipc_nw_ril_ps_cs_reg_state_const_enum;

enum mipc_nw_cellmeasurement_scan_type_const_enum {
    mipc_nw_cellmeasurement_scan_type_const_NONE = 0,
    /* NW_CELLMEASUREMENT_SCAN_TYPE */
    MIPC_NW_CELLMEASUREMENT_SCAN_TYPE_ONLINE_CUS_DEP        = 0,
    MIPC_NW_CELLMEASUREMENT_SCAN_TYPE_OFFLINE               = 1,
    MIPC_NW_CELLMEASUREMENT_SCAN_TYPE_ONLINE_NETWORK_DEP    = 2,
};
typedef enum mipc_nw_cellmeasurement_scan_type_const_enum mipc_nw_cellmeasurement_scan_type_const_enum;

enum mipc_nw_band_option_const_enum {
    mipc_nw_band_option_const_NONE = 0,
    /* NW_BAND_OPTION */
    /* Current setting bands. */
    MIPC_NW_BAND_OPTION_CURRENT_SETTING                     = 0,
    /* Which bands md system supports. */
    MIPC_NW_BAND_OPTION_SYSTEM_SUPPORT                      = 1,
};
typedef enum mipc_nw_band_option_const_enum mipc_nw_band_option_const_enum;

enum mipc_nw_signal_threshold_mode_const_enum {
    mipc_nw_signal_threshold_mode_const_NONE = 0,
    /* NW_SIGNAL_THRESHOLD_MODE */
    MIPC_NW_SIGNAL_THRESHOLD_MODE_MAP_VALUE                 = 0,
    MIPC_NW_SIGNAL_THRESHOLD_MODE_RAW                       = 1,
};
typedef enum mipc_nw_signal_threshold_mode_const_enum mipc_nw_signal_threshold_mode_const_enum;

enum mipc_nw_roaming_mode_const_enum {
    mipc_nw_roaming_mode_const_NONE = 0,
    /* NW_ROAMING_MODE */
    MIPC_NW_ROAMING_MODE_DIS_NONE                           = 0x0,
    MIPC_NW_ROAMING_MODE_DIS_INTERNATIONAL                  = 0x1,
    MIPC_NW_ROAMING_MODE_DIS_NATIONAL                       = 0x2,
    MIPC_NW_ROAMING_MODE_DIS_H_P_PLMN_SEARCH                = 0x4,
};
typedef enum mipc_nw_roaming_mode_const_enum mipc_nw_roaming_mode_const_enum;

enum mipc_nw_antenna_platform_const_enum {
    mipc_nw_antenna_platform_const_NONE = 0,
    /* NW_ANTENNA_PLATFORM */
    MIPC_NW_ANTENNA_PLATFORM_VZ_6290                        = 0,
    MIPC_NW_ANTENNA_PLATFORM_VZ_6292                        = 1,
    MIPC_NW_ANTENNA_PLATFORM_VZ_6294                        = 2,
};
typedef enum mipc_nw_antenna_platform_const_enum mipc_nw_antenna_platform_const_enum;

enum mipc_nw_cell_connection_state_const_enum {
    mipc_nw_cell_connection_state_const_NONE = 0,
    /* NW_CELL_CONNECTION_STATE */
    MIPC_NW_CELL_CONNECTION_STATE_NONE_SERVING              = 0,
    MIPC_NW_CELL_CONNECTION_STATE_PRIMARY_SERVING           = 1,
    MIPC_NW_CELL_CONNECTION_STATE_SECONDARY_SERVING         = 2,
};
typedef enum mipc_nw_cell_connection_state_const_enum mipc_nw_cell_connection_state_const_enum;

enum mipc_nw_rat_switch_mode_const_enum {
    mipc_nw_rat_switch_mode_const_NONE = 0,
    /* NW_RAT_SWITCH_MODE */
    MIPC_NW_RAT_SWITCH_MODE_NONE                            = 0,
    MIPC_NW_RAT_SWITCH_MODE_NSA_SCG                         = 1,
    MIPC_NW_RAT_SWITCH_MODE_NSA_SCG_ALLOW                   = 2,
    MIPC_NW_RAT_SWITCH_MODE_NSA_TAU                         = 3,
    MIPC_NW_RAT_SWITCH_MODE_SA_ONLY                         = 4,
    MIPC_NW_RAT_SWITCH_MODE_SA_TAU                          = 5,
    MIPC_NW_RAT_SWITCH_MODE_BOTH                            = 6,
    MIPC_NW_RAT_SWITCH_MODE_BOTH_TAU                        = 7,
    MIPC_NW_RAT_SWITCH_MODE_ALL                             = 8,
    MIPC_NW_RAT_SWITCH_MODE_RRC_STATE                       = 9,
};
typedef enum mipc_nw_rat_switch_mode_const_enum mipc_nw_rat_switch_mode_const_enum;

enum mipc_nw_ind_type_const_enum {
    mipc_nw_ind_type_const_NONE = 0,
    /* NW_IND_TYPE */
    MIPC_NW_IND_TYPE_ECELL                                  = 1,
};
typedef enum mipc_nw_ind_type_const_enum mipc_nw_ind_type_const_enum;

enum mipc_nw_ps_ctrl_mode_const_enum {
    mipc_nw_ps_ctrl_mode_const_NONE = 0,
    /* NW_PS_CTRL_MODE */
    MIPC_NW_PS_CTRL_MODE_CGATT                              = 0,
    MIPC_NW_PS_CTRL_MODE_EGTYPE                             = 1,
};
typedef enum mipc_nw_ps_ctrl_mode_const_enum mipc_nw_ps_ctrl_mode_const_enum;

enum mipc_nw_act_type_const_enum {
    mipc_nw_act_type_const_NONE = 0,
    /* NW_ACT_TYPE */
    MIPC_NW_ACT_TYPE_GSM                                    = 0,
    MIPC_NW_ACT_TYPE_UMTS                                   = 2,
    MIPC_NW_ACT_TYPE_EGPRS                                  = 3,
    MIPC_NW_ACT_TYPE_HSDPA                                  = 4,
    MIPC_NW_ACT_TYPE_HSUPA                                  = 5,
    MIPC_NW_ACT_TYPE_HSDPA_HSPUPA                           = 6,
    MIPC_NW_ACT_TYPE_LTE                                    = 7,
    MIPC_NW_ACT_TYPE_NR                                     = 11,
    MIPC_NW_ACT_TYPE_NG_RAN                                 = 12,
    MIPC_NW_ACT_TYPE_ENDC                                   = 13,
};
typedef enum mipc_nw_act_type_const_enum mipc_nw_act_type_const_enum;

enum mipc_nw_ps_test_mode_const_enum {
    mipc_nw_ps_test_mode_const_NONE = 0,
    /* NW_PS_TEST_MODE */
    MIPC_NW_PS_TEST_MODE_NONE                               = 0,
    MIPC_NW_PS_TEST_MODE_CTA                                = 1,
    MIPC_NW_PS_TEST_MODE_FTA                                = 2,
    MIPC_NW_PS_TEST_MODE_IOT                                = 3,
    MIPC_NW_PS_TEST_MODE_OPERATOR                           = 4,
    MIPC_NW_PS_TEST_MODE_FACTORY                            = 5,
};
typedef enum mipc_nw_ps_test_mode_const_enum mipc_nw_ps_test_mode_const_enum;

enum mipc_nw_signal_measurement_type_const_enum {
    mipc_nw_signal_measurement_type_const_NONE = 0,
    /* NW_SIGNAL_MEASUREMENT_TYPE */
    /* received signal strength indication. Used RAT: GSM, C2K */
    MIPC_NW_SIGNAL_MEASUREMENT_TYPE_RSSI                    = 1,
    /* received signal code power.  Used RAT: UMTS */
    MIPC_NW_SIGNAL_MEASUREMENT_TYPE_RSCP                    = 2,
    /* reference signal received power.  Used RAT: LTE */
    MIPC_NW_SIGNAL_MEASUREMENT_TYPE_RSRP                    = 3,
    /* reference signal received quality.  Used RAT: LTE */
    MIPC_NW_SIGNAL_MEASUREMENT_TYPE_RSRQ                    = 4,
    /* Reference Signal signal to noise ratio.  Used RAT: LTE */
    MIPC_NW_SIGNAL_MEASUREMENT_TYPE_RSSNR                   = 5,
    /* 5G SS reference signal received power.  Used RAT: NR */
    MIPC_NW_SIGNAL_MEASUREMENT_TYPE_SSRSRP                  = 6,
    /* 5G SS reference signal received qulity.  Used RAT: NR */
    MIPC_NW_SIGNAL_MEASUREMENT_TYPE_SSRSRQ                  = 7,
    /* 5G SS signal_to_noise and interference ratio.  Used RAT: NR */
    MIPC_NW_SIGNAL_MEASUREMENT_TYPE_SSSINR                  = 8,
};
typedef enum mipc_nw_signal_measurement_type_const_enum mipc_nw_signal_measurement_type_const_enum;

enum mipc_nw_signal_rat_const_enum {
    mipc_nw_signal_rat_const_NONE = 0,
    /* NW_SIGNAL_RAT */
    MIPC_NW_SIGNAL_RAT_GSM                                  = 1,
    MIPC_NW_SIGNAL_RAT_UMTS                                 = 2,
    MIPC_NW_SIGNAL_RAT_LTE                                  = 3,
    MIPC_NW_SIGNAL_RAT_C2K                                  = 4,
    MIPC_NW_SIGNAL_RAT_NR                                   = 5,
};
typedef enum mipc_nw_signal_rat_const_enum mipc_nw_signal_rat_const_enum;

enum mipc_nw_bit_rat_const_enum {
    mipc_nw_bit_rat_const_NONE = 0,
    /* NW_BIT_RAT */
    MIPC_NW_BIT_RAT_GSM_BIT                                 = 1,
    MIPC_NW_BIT_RAT_UMTS_BIT                                = 2,
    MIPC_NW_BIT_RAT_LTE_BIT                                 = 4,
    MIPC_NW_BIT_RAT_NR_BIT                                  = 8,
    MIPC_NW_BIT_RAT_C2K_BIT                                 = 16,
};
typedef enum mipc_nw_bit_rat_const_enum mipc_nw_bit_rat_const_enum;

enum mipc_nw_bit_act_const_enum {
    mipc_nw_bit_act_const_NONE = 0,
    /* NW_BIT_ACT */
    /* Bit0.  This bit represents GSM access technology,  0: access technology not selected, 1: access technology selected */
    MIPC_NW_BIT_ACT_GSM_ACTN_BIT                            = 1,
    /* Bit1.  This bit represents GSM compact access technology,  0: access technology not selected, 1: access technology selected */
    MIPC_NW_BIT_ACT_GSM_COMPACT_ACTN_BIT                    = 2,
    /* Bit2.  This bit represents UTRAN access technology,  0: access technology not selected, 1: access technology selected */
    MIPC_NW_BIT_ACT_UTRAN_ACTN_BIT                          = 4,
    /* Bit3.  This bit represents E-UTRAN access technology,  0: access technology not selected, 1: access technology selected */
    MIPC_NW_BIT_ACT_E_UTRAN_ACTN_BIT                        = 8,
    /* Bit4.  This bit represents NG-RAN access technology,  0: access technology not selected, 1: access technology selected */
    MIPC_NW_BIT_ACT_NG_RAN_ACTN_BIT                         = 16,
};
typedef enum mipc_nw_bit_act_const_enum mipc_nw_bit_act_const_enum;

enum mipc_nw_iwlan_status_const_enum {
    mipc_nw_iwlan_status_const_NONE = 0,
    /* NW_IWLAN_STATUS */
    MIPC_NW_IWLAN_STATUS_NOT_READY                          = 0,
    MIPC_NW_IWLAN_STATUS_READY                              = 1,
};
typedef enum mipc_nw_iwlan_status_const_enum mipc_nw_iwlan_status_const_enum;

enum mipc_nw_ca_mode_const_enum {
    mipc_nw_ca_mode_const_NONE = 0,
    /* NW_CA_MODE */
    MIPC_NW_CA_MODE_TURN_OFF                                = 0,
    MIPC_NW_CA_MODE_TURN_ON                                 = 1,
};
typedef enum mipc_nw_ca_mode_const_enum mipc_nw_ca_mode_const_enum;

enum mipc_lte_rrc_state_const_enum {
    mipc_lte_rrc_state_const_NONE = 0,
    /* LTE_RRC_STATE */
    MIPC_LTE_RRC_STATE_NULL                                 = 0,
    MIPC_LTE_RRC_STATE_IDLE                                 = 1,
    MIPC_LTE_RRC_STATE_ATMPT_CONNECTION                     = 2,
    MIPC_LTE_RRC_STATE_CONNECTED                            = 3,
    MIPC_LTE_RRC_STATE_ENDING                               = 4,
};
typedef enum mipc_lte_rrc_state_const_enum mipc_lte_rrc_state_const_enum;

enum mipc_cell_list_type_const_enum {
    mipc_cell_list_type_const_NONE = 0,
    /* CELL_LIST_TYPE */
    /* Get LTE available 1xRTT cell lists */
    MIPC_CELL_LIST_TYPE_AVAILABLE                           = 0,
    /* Get LTE unavailable 1xRTT cell lists */
    MIPC_CELL_LIST_TYPE_UNAVAILABLE                         = 1,
};
typedef enum mipc_cell_list_type_const_enum mipc_cell_list_type_const_enum;

enum mipc_ca_link_mode_const_enum {
    mipc_ca_link_mode_const_NONE = 0,
    /* CA_LINK_MODE */
    /* Get CA downlink capability */
    MIPC_CA_LINK_MODE_DOWNLINK                              = 0,
    /* Get CA downlink and uplink capability */
    MIPC_CA_LINK_MODE_DOWNLIINK_AND_UPLINK                  = 1,
};
typedef enum mipc_ca_link_mode_const_enum mipc_ca_link_mode_const_enum;

enum mipc_ca_link_enable_mode_const_enum {
    mipc_ca_link_enable_mode_const_NONE = 0,
    /* CA_LINK_ENABLE_MODE */
    /* Get DL CA enable status for specified band_combo. */
    MIPC_CA_LINK_ENABLE_MODE_DOWNLINK                       = 2,
    /* Get UL CA enable status for specified band_combo. */
    MIPC_CA_LINK_ENABLE_MODE_UPLINK                         = 3,
};
typedef enum mipc_ca_link_enable_mode_const_enum mipc_ca_link_enable_mode_const_enum;

enum mipc_band_combo_enable_status_const_enum {
    mipc_band_combo_enable_status_const_NONE = 0,
    /* BAND_COMBO_ENABLE_STATUS */
    /* The band_combo is disable. */
    MIPC_BAND_COMBO_ENABLE_STATUS_DISABLE                   = 0,
    /* The band_combo is enable. */
    MIPC_BAND_COMBO_ENABLE_STATUS_ENABLE                    = 1,
};
typedef enum mipc_band_combo_enable_status_const_enum mipc_band_combo_enable_status_const_enum;

enum mipc_tm9_enable_status_const_enum {
    mipc_tm9_enable_status_const_NONE = 0,
    /* TM9_ENABLE_STATUS */
    /* The TM9 is disable. */
    MIPC_TM9_ENABLE_STATUS_DISABLE                          = 0,
    /* The TM9 is enable. */
    MIPC_TM9_ENABLE_STATUS_ENABLE                           = 1,
};
typedef enum mipc_tm9_enable_status_const_enum mipc_tm9_enable_status_const_enum;

enum mipc_tm9_setting_type_const_enum {
    mipc_tm9_setting_type_const_NONE = 0,
    /* TM9_SETTING_TYPE */
    /* The FDD TM9. */
    MIPC_TM9_SETTING_TYPE_FDD                               = 0,
    /* The TDD TM9. */
    MIPC_TM9_SETTING_TYPE_TDD                               = 1,
};
typedef enum mipc_tm9_setting_type_const_enum mipc_tm9_setting_type_const_enum;

enum mipc_omadm_node_type_const_enum {
    mipc_omadm_node_type_const_NONE = 0,
    /* OMADM_NODE_TYPE */
    /* Autonomous gap */
    MIPC_OMADM_NODE_TYPE_AUTONOMOUS_GAP                     = 0,
    /* MPSR duration */
    MIPC_OMADM_NODE_TYPE_MPSR_DURATION                      = 1,
    /* SCAN duration */
    MIPC_OMADM_NODE_TYPE_SCAN_DURATION                      = 2,
    /* Sleep duration */
    MIPC_OMADM_NODE_TYPE_SLEEP_DURATION                     = 3,
    /* MPSR max duration */
    MIPC_OMADM_NODE_TYPE_MPSR_MAX_DURATION                  = 4,
    /* MPSR max duration */
    MIPC_OMADM_NODE_TYPE_LONG_MPSR_DURATION                 = 5,
    /* TPLMN barring timer */
    MIPC_OMADM_NODE_TYPE_TPLMN_BARRING_TIMER                = 6,
    /* LTE HPUE */
    MIPC_OMADM_NODE_TYPE_LTE_HPUE                           = 7,
};
typedef enum mipc_omadm_node_type_const_enum mipc_omadm_node_type_const_enum;

enum mipc_ca_comb_list_type_const_enum {
    mipc_ca_comb_list_type_const_NONE = 0,
    /* CA_COMB_LIST_TYPE */
    /* White list. */
    MIPC_CA_COMB_LIST_TYPE_WHITE                            = 0,
    /* Black list. */
    MIPC_CA_COMB_LIST_TYPE_BLACK                            = 1,
};
typedef enum mipc_ca_comb_list_type_const_enum mipc_ca_comb_list_type_const_enum;

enum mipc_nw_set_ca_rat_const_enum {
    mipc_nw_set_ca_rat_const_NONE = 0,
    /* NW_SET_CA_RAT */
    /* The CA of all rat */
    MIPC_NW_SET_CA_RAT_ALL                                  = 0,
    /* The LTE CA */
    MIPC_NW_SET_CA_RAT_LTE                                  = 1,
};
typedef enum mipc_nw_set_ca_rat_const_enum mipc_nw_set_ca_rat_const_enum;

enum mipc_nitz_ind_type_const_enum {
    mipc_nitz_ind_type_const_NONE = 0,
    /* NITZ_IND_TYPE */
    /* Sib16 time, AT+CIEV: 11, */
    MIPC_NITZ_IND_TYPE_CIEV                                 = 0,
    /* Time zone reporting, AT+CTZEU */
    MIPC_NITZ_IND_TYPE_CTZEU                                = 1,
};
typedef enum mipc_nitz_ind_type_const_enum mipc_nitz_ind_type_const_enum;

enum mipc_nw_tuw_id_const_enum {
    mipc_nw_tuw_id_const_NONE = 0,
    /* NW_TUW_ID */
    MIPC_NW_TUW_ID_TUW1                                     = 1,
    MIPC_NW_TUW_ID_TUW2                                     = 2,
    MIPC_NW_TUW_ID_TUW3                                     = 3,
};
typedef enum mipc_nw_tuw_id_const_enum mipc_nw_tuw_id_const_enum;

enum mipc_nw_ch_info_rat_const_enum {
    mipc_nw_ch_info_rat_const_NONE = 0,
    /* NW_CH_INFO_RAT */
    MIPC_NW_CH_INFO_RAT_GSM                                 = 1,
    MIPC_NW_CH_INFO_RAT_UMTS                                = 2,
    MIPC_NW_CH_INFO_RAT_LTE                                 = 4,
    MIPC_NW_CH_INFO_RAT_NR                                  = 128,
};
typedef enum mipc_nw_ch_info_rat_const_enum mipc_nw_ch_info_rat_const_enum;

enum mipc_nw_vg_option_operation_const_enum {
    mipc_nw_vg_option_operation_const_NONE = 0,
    /* NW_VG_OPTION_OPERATION */
    MIPC_NW_VG_OPTION_OPERATION_VG_OPTION_OPERATION_NONE    = 0,
    MIPC_NW_VG_OPTION_OPERATION_VG_OPTION_OPERATION_LOCAL_RELEASE = 1,
    MIPC_NW_VG_OPTION_OPERATION_VG_OPTION_OPERATION_LOCAL_RELEASE_NR_SEARCH = 2,
};
typedef enum mipc_nw_vg_option_operation_const_enum mipc_nw_vg_option_operation_const_enum;

enum mipc_nw_scan_rat_const_enum {
    mipc_nw_scan_rat_const_NONE = 0,
    /* NW_SCAN_RAT */
    MIPC_NW_SCAN_RAT_GSM                                    = 1,
    MIPC_NW_SCAN_RAT_UMTS                                   = 2,
    MIPC_NW_SCAN_RAT_LTE                                    = 4,
    MIPC_NW_SCAN_RAT_NR                                     = 128,
};
typedef enum mipc_nw_scan_rat_const_enum mipc_nw_scan_rat_const_enum;

enum mipc_nw_scan_type_const_enum {
    mipc_nw_scan_type_const_NONE = 0,
    /* NW_SCAN_TYPE */
    MIPC_NW_SCAN_TYPE_ONE_SHOT                              = 0,
    MIPC_NW_SCAN_TYPE_PERIODIC                              = 1,
};
typedef enum mipc_nw_scan_type_const_enum mipc_nw_scan_type_const_enum;

enum mipc_nw_incremental_results_const_enum {
    mipc_nw_incremental_results_const_NONE = 0,
    /* NW_INCREMENTAL_RESULTS */
    /* disable (one final result) */
    MIPC_NW_INCREMENTAL_RESULTS_DISABLE                     = 0,
    /* enable (multiple partial result) */
    MIPC_NW_INCREMENTAL_RESULTS_ENABLE                      = 1,
};
typedef enum mipc_nw_incremental_results_const_enum mipc_nw_incremental_results_const_enum;

enum mipc_nw_scan_status_const_enum {
    mipc_nw_scan_status_const_NONE = 0,
    /* NW_SCAN_STATUS */
    MIPC_NW_SCAN_STATUS_PARTIAL                             = 0,
    MIPC_NW_SCAN_STATUS_COMPLETE                            = 1,
};
typedef enum mipc_nw_scan_status_const_enum mipc_nw_scan_status_const_enum;

enum mipc_nw_plmn_status_const_enum {
    mipc_nw_plmn_status_const_NONE = 0,
    /* NW_PLMN_STATUS */
    MIPC_NW_PLMN_STATUS_INVALID                             = 0,
    MIPC_NW_PLMN_STATUS_AVAILABLE                           = 1,
    MIPC_NW_PLMN_STATUS_CURRENT                             = 2,
    MIPC_NW_PLMN_STATUS_FORBIDDEN                           = 3,
};
typedef enum mipc_nw_plmn_status_const_enum mipc_nw_plmn_status_const_enum;

enum mipc_nw_register_status_const_enum {
    mipc_nw_register_status_const_NONE = 0,
    /* NW_REGISTER_STATUS */
    MIPC_NW_REGISTER_STATUS_NOT_REGISTERED                  = 0,
    MIPC_NW_REGISTER_STATUS_REGISTERED                      = 1,
};
typedef enum mipc_nw_register_status_const_enum mipc_nw_register_status_const_enum;

enum mipc_nw_srv_cell_status_const_enum {
    mipc_nw_srv_cell_status_const_NONE = 0,
    /* NW_SRV_CELL_STATUS */
    /*  */
    MIPC_NW_SRV_CELL_STATUS_NONE                            = 0,
    /* primary serving cell */
    MIPC_NW_SRV_CELL_STATUS_PRIMARY                         = 1,
    /* secondary serving cell */
    MIPC_NW_SRV_CELL_STATUS_SECONDARY                       = 2,
};
typedef enum mipc_nw_srv_cell_status_const_enum mipc_nw_srv_cell_status_const_enum;

enum mipc_nw_bw_check_const_enum {
    mipc_nw_bw_check_const_NONE = 0,
    /* NW_BW_CHECK */
    /* disable bandwidth check */
    MIPC_NW_BW_CHECK_DISABLE                                = 0,
    /* enable bandwidth check */
    MIPC_NW_BW_CHECK_ENABLE                                 = 1,
};
typedef enum mipc_nw_bw_check_const_enum mipc_nw_bw_check_const_enum;

enum mipc_nw_5guc_state_const_enum {
    mipc_nw_5guc_state_const_NONE = 0,
    /* NW_5GUC_STATE */
    /* don't display 5G UC */
    MIPC_NW_5GUC_STATE_NOT_DISPLAY                          = 0,
    /* display 5G UC */
    MIPC_NW_5GUC_STATE_DISPLAY                              = 1,
};
typedef enum mipc_nw_5guc_state_const_enum mipc_nw_5guc_state_const_enum;

enum mipc_nw_uc_band_const_enum {
    mipc_nw_uc_band_const_NONE = 0,
    /* NW_UC_BAND */
    /* not on UC band */
    MIPC_NW_UC_BAND_NOT_ON                                  = 0,
    /* on UC band */
    MIPC_NW_UC_BAND_ON                                      = 1,
};
typedef enum mipc_nw_uc_band_const_enum mipc_nw_uc_band_const_enum;

enum mipc_sim_status_const_enum {
    mipc_sim_status_const_NONE = 0,
    /* SIM_STATUS */
    /* sim not inserted */
    MIPC_SIM_STATUS_NOT_INSERT                              = 0,
    /* CPIN response BUSY */
    MIPC_SIM_STATUS_BUSY                                    = 1,
    /* CPIN response READY */
    MIPC_SIM_STATUS_READY                                   = 2,
    /* MT is waiting SIM PIN to be given  */
    MIPC_SIM_STATUS_SIM_PIN                                 = 3,
    /* MT is waiting SIM PUK to be given  */
    MIPC_SIM_STATUS_SIM_PUK                                 = 4,
    /* MT is waiting phone to SIM card password to be givenn  */
    MIPC_SIM_STATUS_PH_SIM_PIN                              = 5,
    /* MT is waiting phone-to-very first SIM card password to be given  */
    MIPC_SIM_STATUS_PH_FSIM_PIN                             = 6,
    /* MT is waiting phone-to-very first SIM card unblocking password to be given  */
    MIPC_SIM_STATUS_PH_FSIM_PUK                             = 7,
    /* MT is waiting SIM PIN2 to be given  */
    MIPC_SIM_STATUS_SIM_PIN2                                = 8,
    /* MT is waiting SIM PUK2 to be given n  */
    MIPC_SIM_STATUS_SIM_PUK2                                = 9,
    /* MT is waiting network personalization password to be given */
    MIPC_SIM_STATUS_PH_NET_PIN                              = 10,
    /* MT is waiting network personalization unblocking password to be given */
    MIPC_SIM_STATUS_PH_NET_PUK                              = 11,
    /* MT is waiting network subset personalization password to be given  */
    MIPC_SIM_STATUS_PH_NETSUB_PIN                           = 12,
    /* MT is waiting network subset personalization unblocking password to be given  */
    MIPC_SIM_STATUS_PH_NETSUB_PUK                           = 13,
    /* MT is waiting service provider personalization password to be given  */
    MIPC_SIM_STATUS_PH_SP_PIN                               = 14,
    /* MT is waiting service provider personalization unblocking password to be given  */
    MIPC_SIM_STATUS_PH_SP_PUK                               = 15,
    /* MT is waiting corporate personalization password to be given */
    MIPC_SIM_STATUS_PH_CORP_PIN                             = 16,
    /* MT is waiting corporate personalization unblocking password to be given */
    MIPC_SIM_STATUS_PH_CORP_PUK                             = 17,
    /* CARD Reboot */
    MIPC_SIM_STATUS_CARD_REBOOT                             = 18,
    /* CARD restricted  */
    MIPC_SIM_STATUS_CARD_RESTRICTED                         = 19,
    /* eUICC but no profile  */
    MIPC_SIM_STATUS_EMPT_EUICC                              = 20,
    /* SIM initialization done after CPIN ready  */
    MIPC_SIM_STATUS_COMPLETE_READY                          = 21,
};
typedef enum mipc_sim_status_const_enum mipc_sim_status_const_enum;

enum mipc_sim_state_const_enum {
    mipc_sim_state_const_NONE = 0,
    /* SIM_STATE */
    MIPC_SIM_STATE_UNKNOWN                                  = 0,
    MIPC_SIM_STATE_OFFEMPTY                                 = 1,
    MIPC_SIM_STATE_OFF                                      = 2,
    MIPC_SIM_STATE_EMPTY                                    = 3,
    MIPC_SIM_STATE_NOTREADY                                 = 4,
    MIPC_SIM_STATE_ACTIVE                                   = 5,
    MIPC_SIM_STATE_ERROR                                    = 6,
    MIPC_SIM_STATE_ACTIVE_ESIM                              = 7,
    MIPC_SIM_STATE_ACTIVE_ESIM_NOPROFILE                    = 8,
};
typedef enum mipc_sim_state_const_enum mipc_sim_state_const_enum;

enum mipc_sim_card_present_state_const_enum {
    mipc_sim_card_present_state_const_NONE = 0,
    /* SIM_CARD_PRESENT_STATE */
    MIPC_SIM_CARD_PRESENT_STATE_ABSENT                      = 0,
    MIPC_SIM_CARD_PRESENT_STATE_PRESENT                     = 1,
    MIPC_SIM_CARD_PRESENT_STATE_ERROR                       = 2,
    MIPC_SIM_CARD_PRESENT_STATE_RESTRICTED                  = 3,
};
typedef enum mipc_sim_card_present_state_const_enum mipc_sim_card_present_state_const_enum;

enum mipc_sim_sub_state_const_enum {
    mipc_sim_sub_state_const_NONE = 0,
    /* SIM_SUB_STATE */
    MIPC_SIM_SUB_STATE_UNKNOWN                              = 0,
    MIPC_SIM_SUB_STATE_PLUG_IN                              = 1,
    MIPC_SIM_SUB_STATE_PLUG_OUT                             = 2,
    MIPC_SIM_SUB_STATE_RECOVERY_START                       = 3,
    MIPC_SIM_SUB_STATE_RECOVERY_EN                          = 4,
};
typedef enum mipc_sim_sub_state_const_enum mipc_sim_sub_state_const_enum;

enum mipc_sim_pin_type_const_enum {
    mipc_sim_pin_type_const_NONE = 0,
    /* SIM_PIN_TYPE */
    MIPC_SIM_PIN_TYPE_NONE                                  = 0,
    MIPC_SIM_PIN_TYPE_PIN1                                  = 1,
    MIPC_SIM_PIN_TYPE_PIN2                                  = 2,
    MIPC_SIM_PIN_TYPE_PUK1                                  = 3,
    MIPC_SIM_PIN_TYPE_PUK2                                  = 4,
    MIPC_SIM_PIN_TYPE_NW                                    = 5,
    MIPC_SIM_PIN_TYPE_SUB_NW                                = 6,
    MIPC_SIM_PIN_TYPE_SP                                    = 7,
    MIPC_SIM_PIN_TYPE_CORP                                  = 8,
    MIPC_SIM_PIN_TYPE_SIM                                   = 9,
    MIPC_SIM_PIN_TYPE_NS_SP                                 = 10,
    MIPC_SIM_PIN_TYPE_SIM_C                                 = 11,
    MIPC_SIM_PIN_TYPE_PUK_N                                 = 12,
    MIPC_SIM_PIN_TYPE_PUK_NS                                = 13,
    MIPC_SIM_PIN_TYPE_PUK_SP                                = 14,
    MIPC_SIM_PIN_TYPE_PUK_C                                 = 15,
    MIPC_SIM_PIN_TYPE_PUK_SIM                               = 16,
    MIPC_SIM_PIN_TYPE_PUK_NS_SP                             = 17,
    MIPC_SIM_PIN_TYPE_PUK_SIM_C                             = 18,
};
typedef enum mipc_sim_pin_type_const_enum mipc_sim_pin_type_const_enum;

enum mipc_sim_pin_protection_const_enum {
    mipc_sim_pin_protection_const_NONE = 0,
    /* SIM_PIN_PROTECTION */
    MIPC_SIM_PIN_PROTECTION_DISABLE                         = 0,
    MIPC_SIM_PIN_PROTECTION_ENABLE                          = 1,
};
typedef enum mipc_sim_pin_protection_const_enum mipc_sim_pin_protection_const_enum;

enum mipc_sim_pin_mode_const_enum {
    mipc_sim_pin_mode_const_NONE = 0,
    /* SIM_PIN_MODE */
    MIPC_SIM_PIN_MODE_NOT_SUPPORT                           = 0,
    MIPC_SIM_PIN_MODE_ENABLE                                = 1,
    MIPC_SIM_PIN_MODE_DISABLE                               = 2,
};
typedef enum mipc_sim_pin_mode_const_enum mipc_sim_pin_mode_const_enum;

enum mipc_sim_pin_format_const_enum {
    mipc_sim_pin_format_const_NONE = 0,
    /* SIM_PIN_FORMAT */
    MIPC_SIM_PIN_FORMAT_UNKNOWN                             = 0,
    MIPC_SIM_PIN_FORMAT_NUMERIC                             = 1,
    MIPC_SIM_PIN_FORMAT_ALPHA_NUMERIC                       = 2,
};
typedef enum mipc_sim_pin_format_const_enum mipc_sim_pin_format_const_enum;

enum mipc_sim_pin_state_const_enum {
    mipc_sim_pin_state_const_NONE = 0,
    /* SIM_PIN_STATE */
    MIPC_SIM_PIN_STATE_UNLOCKED                             = 0,
    MIPC_SIM_PIN_STATE_LOCKED                               = 1,
};
typedef enum mipc_sim_pin_state_const_enum mipc_sim_pin_state_const_enum;

enum mipc_sim_pin_operation_const_enum {
    mipc_sim_pin_operation_const_NONE = 0,
    /* SIM_PIN_OPERATION */
    MIPC_SIM_PIN_OPERATION_ENTER                            = 0,
    MIPC_SIM_PIN_OPERATION_ENABLE                           = 1,
    MIPC_SIM_PIN_OPERATION_DISABLE                          = 2,
    MIPC_SIM_PIN_OPERATION_CHANGE                           = 3,
};
typedef enum mipc_sim_pin_operation_const_enum mipc_sim_pin_operation_const_enum;

enum mipc_sim_pass_through_mode_const_enum {
    mipc_sim_pass_through_mode_const_NONE = 0,
    /* SIM_PASS_THROUGH_MODE */
    MIPC_SIM_PASS_THROUGH_MODE_DISABLE                      = 0,
    MIPC_SIM_PASS_THROUGH_MODE_ENABLE                       = 1,
};
typedef enum mipc_sim_pass_through_mode_const_enum mipc_sim_pass_through_mode_const_enum;

enum mipc_sim_app_type_const_enum {
    mipc_sim_app_type_const_NONE = 0,
    /* SIM_APP_TYPE */
    /* unknown type */
    MIPC_SIM_APP_TYPE_UNKNOWN                               = 0,
    /* legacy SIM directories rooted at the MF */
    MIPC_SIM_APP_TYPE_MF                                    = 1,
    /* legacy SIM directories rooted at the DF_GSM */
    MIPC_SIM_APP_TYPE_MFSIM                                 = 2,
    /* legacy SIM directories rooted at the DF_CDMA */
    MIPC_SIM_APP_TYPE_MFRUIM                                = 3,
    /* USIM application */
    MIPC_SIM_APP_TYPE_USIM                                  = 4,
    /* CSIM application */
    MIPC_SIM_APP_TYPE_CSIM                                  = 5,
    /* ISIM application */
    MIPC_SIM_APP_TYPE_ISIM                                  = 6,
};
typedef enum mipc_sim_app_type_const_enum mipc_sim_app_type_const_enum;

enum mipc_sim_app_type_ex_const_enum {
    mipc_sim_app_type_ex_const_NONE = 0,
    /* SIM_APP_TYPE_EX */
    /* ISIM application */
    MIPC_SIM_APP_TYPE_EX_ISIM                               = 0,
    /* USIM application */
    MIPC_SIM_APP_TYPE_EX_USIM                               = 1,
    /* CSIM application */
    MIPC_SIM_APP_TYPE_EX_CSIM                               = 2,
    /* SIM application */
    MIPC_SIM_APP_TYPE_EX_SIM                                = 3,
    /* UIM application */
    MIPC_SIM_APP_TYPE_EX_UIM                                = 4,
    /* unknown type */
    MIPC_SIM_APP_TYPE_EX_UNKNOWN                            = 255,
};
typedef enum mipc_sim_app_type_ex_const_enum mipc_sim_app_type_ex_const_enum;

enum mipc_sim_access_command_const_enum {
    mipc_sim_access_command_const_NONE = 0,
    /* SIM_ACCESS_COMMAND */
    MIPC_SIM_ACCESS_COMMAND_READ_BINARY                     = 176,
    MIPC_SIM_ACCESS_COMMAND_READ_RECORD                     = 178,
    MIPC_SIM_ACCESS_COMMAND_GET_RESPONSE                    = 192,
    MIPC_SIM_ACCESS_COMMAND_UPDATE_BINARY                   = 214,
    MIPC_SIM_ACCESS_COMMAND_UPDATE_RECORD                   = 220,
    MIPC_SIM_ACCESS_COMMAND_STATUS                          = 242,
    MIPC_SIM_ACCESS_COMMAND_RETRIEVE_DATA                   = 203,
    MIPC_SIM_ACCESS_COMMAND_SET_DATA                        = 219,
};
typedef enum mipc_sim_access_command_const_enum mipc_sim_access_command_const_enum;

enum mipc_sim_file_accessibility_const_enum {
    mipc_sim_file_accessibility_const_NONE = 0,
    /* SIM_FILE_ACCESSIBILITY */
    MIPC_SIM_FILE_ACCESSIBILITY_UNKNOWN                     = 0,
    MIPC_SIM_FILE_ACCESSIBILITY_NOTSHAREABLE                = 1,
    MIPC_SIM_FILE_ACCESSIBILITY_SHAREABLE                   = 2,
};
typedef enum mipc_sim_file_accessibility_const_enum mipc_sim_file_accessibility_const_enum;

enum mipc_sim_file_type_const_enum {
    mipc_sim_file_type_const_NONE = 0,
    /* SIM_FILE_TYPE */
    MIPC_SIM_FILE_TYPE_UNKNOWN                              = 0,
    MIPC_SIM_FILE_TYPE_WORKING_EF                           = 1,
    MIPC_SIM_FILE_TYPE_INTERNAL_EF                          = 2,
    MIPC_SIM_FILE_TYPE_DF_OR_ADF                            = 3,
};
typedef enum mipc_sim_file_type_const_enum mipc_sim_file_type_const_enum;

enum mipc_sim_file_structure_const_enum {
    mipc_sim_file_structure_const_NONE = 0,
    /* SIM_FILE_STRUCTURE */
    MIPC_SIM_FILE_STRUCTURE_UNKNOWN                         = 0,
    MIPC_SIM_FILE_STRUCTURE_TRANSPARENT                     = 1,
    MIPC_SIM_FILE_STRUCTURE_CYCLIC                          = 2,
    MIPC_SIM_FILE_STRUCTURE_LINEAR                          = 3,
    MIPC_SIM_FILE_STRUCTURE_BERTLV                          = 4,
};
typedef enum mipc_sim_file_structure_const_enum mipc_sim_file_structure_const_enum;

enum mipc_sim_enabled_const_enum {
    mipc_sim_enabled_const_NONE = 0,
    /* SIM_ENABLED */
    MIPC_SIM_ENABLED_UNKNOWN                                = 0,
    MIPC_SIM_ENABLED_ENABLED_NOT_VERIFIED                   = 1,
    MIPC_SIM_ENABLED_ENABLED_VERIFIED                       = 2,
    MIPC_SIM_ENABLED_DISABLED                               = 3,
    MIPC_SIM_ENABLED_ENABLED_BLOCKED                        = 4,
    MIPC_SIM_ENABLED_ENABLED_PERM_BLOCKED                   = 5,
};
typedef enum mipc_sim_enabled_const_enum mipc_sim_enabled_const_enum;

enum mipc_sim_app_state_const_enum {
    mipc_sim_app_state_const_NONE = 0,
    /* SIM_APP_STATE */
    MIPC_SIM_APP_STATE_UNKNOWN                              = 0,
    MIPC_SIM_APP_STATE_DETECTED                             = 1,
    MIPC_SIM_APP_STATE_PIN                                  = 2,
    MIPC_SIM_APP_STATE_PUK                                  = 3,
    MIPC_SIM_APP_STATE_SUBSTATE                             = 4,
    MIPC_SIM_APP_STATE_READY                                = 5,
};
typedef enum mipc_sim_app_state_const_enum mipc_sim_app_state_const_enum;

enum mipc_sim_app_sub_status_const_enum {
    mipc_sim_app_sub_status_const_NONE = 0,
    /* SIM_APP_SUB_STATUS */
    MIPC_SIM_APP_SUB_STATUS_UNKNOWN                         = 0,
    MIPC_SIM_APP_SUB_STATUS_IN_PROGRESS                     = 1,
    MIPC_SIM_APP_SUB_STATUS_READY                           = 2,
    MIPC_SIM_APP_SUB_STATUS_NW                              = 3,
    MIPC_SIM_APP_SUB_STATUS_NW_PUK                          = 4,
    MIPC_SIM_APP_SUB_STATUS_SUB_NW                          = 5,
    MIPC_SIM_APP_SUB_STATUS_SUB_NW_PUK                      = 6,
    MIPC_SIM_APP_SUB_STATUS_CORP                            = 7,
    MIPC_SIM_APP_SUB_STATUS_CORP_PUK                        = 8,
    MIPC_SIM_APP_SUB_STATUS_SP                              = 9,
    MIPC_SIM_APP_SUB_STATUS_SP_PUK                          = 10,
    MIPC_SIM_APP_SUB_STATUS_IMSI                            = 11,
    MIPC_SIM_APP_SUB_STATUS_IMSI_PUK                        = 12,
    MIPC_SIM_APP_SUB_STATUS_LINK_NS_SP                      = 13,
    MIPC_SIM_APP_SUB_STATUS_LINK_NS_SP_PUK                  = 14,
    MIPC_SIM_APP_SUB_STATUS_LINK_SIM_C                      = 15,
    MIPC_SIM_APP_SUB_STATUS_LINK_SIM_C_PUK                  = 16,
};
typedef enum mipc_sim_app_sub_status_const_enum mipc_sim_app_sub_status_const_enum;

enum mipc_sim_cause_const_enum {
    mipc_sim_cause_const_NONE = 0,
    /* SIM_CAUSE */
    MIPC_SIM_CAUSE_CARD_REMOVED                             = 0,
    MIPC_SIM_CAUSE_ACCESS_ERROR                             = 1,
    MIPC_SIM_CAUSE_SIM_REFRESH                              = 2,
    MIPC_SIM_CAUSE_SIM_REFRESH_POWER_OFF                    = 3,
    MIPC_SIM_CAUSE_SIM_PUK1                                 = 4,
    MIPC_SIM_CAUSE_SIM_ACCESS_PROFILE_ON                    = 5,
    MIPC_SIM_CAUSE_SIM_ACCESS_PROFILE_OFF                   = 6,
    MIPC_SIM_CAUSE_DUAIL_DISCONNECTED                       = 7,
    MIPC_SIM_CAUSE_DUAIL_CONNECTED                          = 8,
    MIPC_SIM_CAUSE_SIM_VSIM_ON                              = 9,
    MIPC_SIM_CAUSE_SIM_VSIM_OFF                             = 10,
    MIPC_SIM_CAUSE_SIM_PLUG_OUT                             = 11,
    MIPC_SIM_CAUSE_SIM_PLUG_IN                              = 12,
    MIPC_SIM_CAUSE_SIM_RECOVERY_START                       = 13,
    MIPC_SIM_CAUSE_SIM_RECOVERY_END                         = 14,
    MIPC_SIM_CAUSE_SIM_IMEI_LOCK_FAIL                       = 15,
    MIPC_SIM_CAUSE_SIM_OP09_LOCK_FAIL                       = 16,
    MIPC_SIM_CAUSE_SIM_CARD_TECHNICAL_PROBLEM               = 17,
    MIPC_SIM_CAUSE_SIM_POWER_OFF_BY_L4                      = 18,
    MIPC_SIM_CAUSE_SIM_OP20_IMEI_LOCK                       = 19,
    MIPC_SIM_CAUSE_SIM_PLUG_IN_REPLACED                     = 20,
    MIPC_SIM_CAUSE_SIM_OP01_LOCK                            = 21,
    MIPC_SIM_CAUSE_SIM_OP01_UNLOCK                          = 22,
    MIPC_SIM_CAUSE_SIM_FAST_RECOVERY_START                  = 23,
    MIPC_SIM_CAUSE_SIM_FAST_RECOVERY_SUCCESS                = 24,
    MIPC_SIM_CAUSE_SIM_TRAY_PLUG_OUT                        = 25,
    MIPC_SIM_CAUSE_SIM_PLUG_IN_NO_INIT                      = 26,
    MIPC_SIM_CAUSE_SIM_PRESENCE_DETECTION_FAIL              = 27,
    MIPC_SIM_CAUSE_SIM_STATE_DISABLE                        = 28,
    MIPC_SIM_CAUSE_SIM_STATE_ENABLE                         = 29,
};
typedef enum mipc_sim_cause_const_enum mipc_sim_cause_const_enum;

enum mipc_sim_additional_cause_const_enum {
    mipc_sim_additional_cause_const_NONE = 0,
    /* SIM_ADDITIONAL_CAUSE */
    MIPC_SIM_ADDITIONAL_CAUSE_SIM_REFRESH_TYPE_NAA_INIT_AND_FULL_FCN = 0,
    MIPC_SIM_ADDITIONAL_CAUSE_SIM_REFRESH_TYPE_FCN          = 1,
    MIPC_SIM_ADDITIONAL_CAUSE_SIM_REFRESH_TYPE_NAA_INIT_AND_FCN = 2,
    MIPC_SIM_ADDITIONAL_CAUSE_SIM_REFRESH_TYPE_NAA_INIT     = 3,
    MIPC_SIM_ADDITIONAL_CAUSE_SIM_REFRESH_TYPE_SIM_RESET    = 4,
    MIPC_SIM_ADDITIONAL_CAUSE_SIM_REFRESH_TYPE_NAA_APP_RESET = 5,
    MIPC_SIM_ADDITIONAL_CAUSE_SIM_REFRESH_TYPE_NAA_SESSION_RESET = 6,
    MIPC_SIM_ADDITIONAL_CAUSE_SIM_REFRESH_TYPE_STEERING_OF_ROAMING = 7,
    MIPC_SIM_ADDITIONAL_CAUSE_SIM_REFRESH_TYPE_STEERING_OF_ROAMING_FOR_IWLAN = 8,
    MIPC_SIM_ADDITIONAL_CAUSE_SIM_REFRESH_TYPE_EUICC_PROFILE = 9,
    MIPC_SIM_ADDITIONAL_CAUSE_SIM_REFRESH_END               = 255,
};
typedef enum mipc_sim_additional_cause_const_enum mipc_sim_additional_cause_const_enum;

enum mipc_sim_vsim_type_const_enum {
    mipc_sim_vsim_type_const_NONE = 0,
    /* SIM_VSIM_TYPE */
    MIPC_SIM_VSIM_TYPE_SIM_TYPE_LOCAL_SIM                   = 0,
    MIPC_SIM_VSIM_TYPE_SIM_TYPE_REMOTE_SIM                  = 1,
};
typedef enum mipc_sim_vsim_type_const_enum mipc_sim_vsim_type_const_enum;

enum mipc_sim_vsim_auth_mode_const_enum {
    mipc_sim_vsim_auth_mode_const_NONE = 0,
    /* SIM_VSIM_AUTH_MODE */
    MIPC_SIM_VSIM_AUTH_MODE_RELEASING_RF                    = 0,
    MIPC_SIM_VSIM_AUTH_MODE_OCCUPING_RF                     = 1,
};
typedef enum mipc_sim_vsim_auth_mode_const_enum mipc_sim_vsim_auth_mode_const_enum;

enum mipc_sim_crrst_state_const_enum {
    mipc_sim_crrst_state_const_NONE = 0,
    /* SIM_CRRST_STATE */
    MIPC_SIM_CRRST_STATE_SIM_CRRST_STATE_NULL               = 0,
    MIPC_SIM_CRRST_STATE_SIM_CRRST_STATE_LOCKED             = 1,
    MIPC_SIM_CRRST_STATE_SIM_CRRST_STATE_UNLOCKED           = 2,
    MIPC_SIM_CRRST_STATE_SIM_CRRST_STATE_DISABLED           = 3,
};
typedef enum mipc_sim_crrst_state_const_enum mipc_sim_crrst_state_const_enum;

enum mipc_sim_sml_category_const_enum {
    mipc_sim_sml_category_const_NONE = 0,
    /* SIM_SML_CATEGORY */
    MIPC_SIM_SML_CATEGORY_CAT_N                             = 0,
    MIPC_SIM_SML_CATEGORY_CAT_NS                            = 1,
    MIPC_SIM_SML_CATEGORY_CAT_SP                            = 2,
    MIPC_SIM_SML_CATEGORY_CAT_CORP                          = 3,
    MIPC_SIM_SML_CATEGORY_CAT_SIM                           = 4,
    MIPC_SIM_SML_CATEGORY_CAT_NS_SP                         = 5,
    MIPC_SIM_SML_CATEGORY_CAT_SIM_CORP                      = 6,
    MIPC_SIM_SML_CATEGORY_CAT_SIZE                          = 7,
    MIPC_SIM_SML_CATEGORY_CAT_DUAL_SIM_LOCK_CONTROL         = 8,
    MIPC_SIM_SML_CATEGORY_CAT_MASTER_KEY                    = 9,
    MIPC_SIM_SML_CATEGORY_CAT_UNKNOWN                       = 255,
};
typedef enum mipc_sim_sml_category_const_enum mipc_sim_sml_category_const_enum;

enum mipc_sim_sml_operation_const_enum {
    mipc_sim_sml_operation_const_NONE = 0,
    /* SIM_SML_OPERATION */
    MIPC_SIM_SML_OPERATION_UNLOCK                           = 0,
    MIPC_SIM_SML_OPERATION_LOCK                             = 1,
    MIPC_SIM_SML_OPERATION_ADD                              = 2,
    MIPC_SIM_SML_OPERATION_REMOVE                           = 3,
    MIPC_SIM_SML_OPERATION_DISABLE                          = 4,
    MIPC_SIM_SML_OPERATION_UPDATE_AUTOLOCK_COUNT            = 5,
};
typedef enum mipc_sim_sml_operation_const_enum mipc_sim_sml_operation_const_enum;

enum mipc_sim_sml_rsu_operation_const_enum {
    mipc_sim_sml_rsu_operation_const_NONE = 0,
    /* SIM_SML_RSU_OPERATION */
    MIPC_SIM_SML_RSU_OPERATION_INIT                         = 1,
    MIPC_SIM_SML_RSU_OPERATION_UPDATE_LOCK_DATA             = 2,
    MIPC_SIM_SML_RSU_OPERATION_GET_LOCK_STATUS              = 3,
    MIPC_SIM_SML_RSU_OPERATION_UNLOCK_TIMER                 = 4,
    MIPC_SIM_SML_RSU_OPERATION_GET_SHARED_KEY               = 5,
    MIPC_SIM_SML_RSU_OPERATION_GET_LOCK_VERSION             = 6,
    MIPC_SIM_SML_RSU_OPERATION_GET_LOCK_DATA                = 7,
    MIPC_SIM_SML_RSU_OPERATION_GET_ALLOWED_LOCK_DATA        = 8,
    MIPC_SIM_SML_RSU_OPERATION_GET_EXCLUDED_LOCK_DATA       = 9,
    MIPC_SIM_SML_RSU_OPERATION_GET_MD_CONFIG                = 10,
    MIPC_SIM_SML_RSU_OPERATION_GET_API_VERSION              = 11,
    MIPC_SIM_SML_RSU_OPERATION_GET_SIM_SLOTS                = 12,
    MIPC_SIM_SML_RSU_OPERATION_RESET_LOCK_DATA              = 13,
    MIPC_SIM_SML_RSU_OPERATION_VERIFY_TF_STATUS             = 14,
};
typedef enum mipc_sim_sml_rsu_operation_const_enum mipc_sim_sml_rsu_operation_const_enum;

enum mipc_sms_state_const_enum {
    mipc_sms_state_const_NONE = 0,
    /* SMS_STATE */
    /* some SMS related operation would be baned because of not initialized */
    MIPC_SMS_STATE_NOT_INITIALIZED                          = 0,
    /* SIM_OK & SMS_MODULE_INITIALIZED, sms operation permit now */
    MIPC_SMS_STATE_INITIALIZED                              = 1,
};
typedef enum mipc_sms_state_const_enum mipc_sms_state_const_enum;

enum mipc_sms_format_const_enum {
    mipc_sms_format_const_NONE = 0,
    /* SMS_FORMAT */
    /* only for cfg using */
    MIPC_SMS_FORMAT_PDU                                     = 0,
    /* only for cfg using; MIPC dont support TEXT mode now */
    MIPC_SMS_FORMAT_TEXT                                    = 1,
    /* [PHASE OUT] */
    MIPC_SMS_FORMAT_CDMA                                    = 2,
    /* for other mipc than cfg */
    MIPC_SMS_FORMAT_PDU_3GPP                                = 3,
    /* for other mipc than cfg */
    MIPC_SMS_FORMAT_PDU_3GPP2                               = 4,
    /* query the cfg */
    MIPC_SMS_FORMAT_QUERY                                   = 0xFD,
    /* same as not carry this tlv */
    MIPC_SMS_FORMAT_NULL                                    = 0xFE,
    /* invalid value */
    MIPC_SMS_FORMAT_INVALID                                 = 0xFF,
};
typedef enum mipc_sms_format_const_enum mipc_sms_format_const_enum;

enum mipc_sms_cbm_type_const_enum {
    mipc_sms_cbm_type_const_NONE = 0,
    /* SMS_CBM_TYPE */
    /* etws primary. if open this in cbm_cfg, no matter dcs&msg_id setting, etws_primary would indicate */
    MIPC_SMS_CBM_TYPE_ETWS_PRIMARY                          = 0x00000001,
    /* cbm with msg_id in 4352-4356 */
    MIPC_SMS_CBM_TYPE_ETWS_SECONDARY                        = 0x00000002,
    /* cbm with msg_id in 4370-4400 */
    MIPC_SMS_CBM_TYPE_CMAS                                  = 0x00000004,
    /* for other mipc than cfg */
    MIPC_SMS_CBM_TYPE_OTHERS                                = 0x80000000,
};
typedef enum mipc_sms_cbm_type_const_enum mipc_sms_cbm_type_const_enum;

enum mipc_sms_etws_primary_type_const_enum {
    mipc_sms_etws_primary_type_const_NONE = 0,
    /* SMS_ETWS_PRIMARY_TYPE */
    /* normal etws primary would indication */
    MIPC_SMS_ETWS_PRIMARY_TYPE_ETWS_PRIMARY                 = 0x01,
    /* etws primary with security check would indication */
    MIPC_SMS_ETWS_PRIMARY_TYPE_ETWS_PRIMARY_WITH_SECURITY_CHECK = 0x02,
    /* etws primary with msg_id = 4355 would indication */
    MIPC_SMS_ETWS_PRIMARY_TYPE_ETWS_PRIMARY_FOR_TEST        = 0x04,
};
typedef enum mipc_sms_etws_primary_type_const_enum mipc_sms_etws_primary_type_const_enum;

enum mipc_sms_flag_const_enum {
    mipc_sms_flag_const_NONE = 0,
    /* SMS_FLAG */
    MIPC_SMS_FLAG_ALL                                       = 0,
    MIPC_SMS_FLAG_NEW                                       = 1,
    MIPC_SMS_FLAG_OLD                                       = 2,
    MIPC_SMS_FLAG_SENT                                      = 3,
    MIPC_SMS_FLAG_DRAFT                                     = 4,
    MIPC_SMS_FLAG_INDEX                                     = 5,
    MIPC_SMS_FLAG_INVALID                                   = 0xFF,
};
typedef enum mipc_sms_flag_const_enum mipc_sms_flag_const_enum;

enum mipc_sms_status_const_enum {
    mipc_sms_status_const_NONE = 0,
    /* SMS_STATUS */
    MIPC_SMS_STATUS_REC_UNREAD                              = 0,
    MIPC_SMS_STATUS_REC_READ                                = 1,
    MIPC_SMS_STATUS_STO_UNSENT                              = 2,
    MIPC_SMS_STATUS_STO_SENT                                = 3,
    MIPC_SMS_STATUS_INVALID                                 = 0xFF,
};
typedef enum mipc_sms_status_const_enum mipc_sms_status_const_enum;

enum mipc_sms_class_const_enum {
    mipc_sms_class_const_NONE = 0,
    /* SMS_CLASS */
    MIPC_SMS_CLASS_0                                        = 0,
    MIPC_SMS_CLASS_1                                        = 1,
    MIPC_SMS_CLASS_2                                        = 2,
    MIPC_SMS_CLASS_3                                        = 3,
    MIPC_SMS_CLASS_NONE                                     = 0xFE,
    MIPC_SMS_CLASS_INVALID                                  = 0xFF,
};
typedef enum mipc_sms_class_const_enum mipc_sms_class_const_enum;

enum mipc_sms_store_flag_const_enum {
    mipc_sms_store_flag_const_NONE = 0,
    /* SMS_STORE_FLAG */
    MIPC_SMS_STORE_FLAG_NONE                                = 0x00000000,
    /* [3GPP]storage full */
    MIPC_SMS_STORE_FLAG_STORE_FULL                          = 0x00000001,
    /* [3GPP]new sms ind */
    MIPC_SMS_STORE_FLAG_NEW_MESSAGE                         = 0x00000002,
    /* [3GPP]sim storage full */
    MIPC_SMS_STORE_FLAG_STORE_FULL_SIM                      = 0x00000004,
    /* [3GPP]me storage full */
    MIPC_SMS_STORE_FLAG_STORE_FULL_ME                       = 0x00000008,
    /* [3GPP2]uim storage full */
    MIPC_SMS_STORE_FLAG_STORE_FULL_UIM                      = 0x00000010,
    /* [3GPP2]new c2k_sms ind */
    MIPC_SMS_STORE_FLAG_NEW_SMS_C2K                         = 0x00000020,
};
typedef enum mipc_sms_store_flag_const_enum mipc_sms_store_flag_const_enum;

enum mipc_sms_storage_const_enum {
    mipc_sms_storage_const_NONE = 0,
    /* SMS_STORAGE */
    /* SIM */
    MIPC_SMS_STORAGE_SIM                                    = 0,
    /* NVRAM */
    MIPC_SMS_STORAGE_ME                                     = 1,
    /* only used in cfg->PREFER_STORAGE(not save in SIM/UIM/NVRAM, just relay to HOST/sAP) */
    MIPC_SMS_STORAGE_TE                                     = 2,
    /* UIM */
    MIPC_SMS_STORAGE_UIM                                    = 3,
    /* SIM first, then NVRAM */
    MIPC_SMS_STORAGE_MT                                     = 4,
    MIPC_SMS_STORAGE_QUERY                                  = 0xFD,
    MIPC_SMS_STORAGE_NULL                                   = 0xFE,
    MIPC_SMS_STORAGE_INVALID                                = 0xFF,
};
typedef enum mipc_sms_storage_const_enum mipc_sms_storage_const_enum;

enum mipc_sms_ack_const_enum {
    mipc_sms_ack_const_NONE = 0,
    /* SMS_ACK */
    MIPC_SMS_ACK_NONEED                                     = 0,
    MIPC_SMS_ACK_NEEDED                                     = 1,
    MIPC_SMS_ACK_QUERY                                      = 0xFD,
    MIPC_SMS_ACK_NULL                                       = 0xFE,
    MIPC_SMS_ACK_INVALID                                    = 0xFF,
};
typedef enum mipc_sms_ack_const_enum mipc_sms_ack_const_enum;

enum mipc_new_sms_ack_const_enum {
    mipc_new_sms_ack_const_NONE = 0,
    /* NEW_SMS_ACK */
    MIPC_NEW_SMS_ACK_RP_ACK                                 = 0,
    MIPC_NEW_SMS_ACK_RP_ERROR                               = 1,
    MIPC_NEW_SMS_ACK_INVALID                                = 0xFF,
};
typedef enum mipc_new_sms_ack_const_enum mipc_new_sms_ack_const_enum;

enum mipc_sms_send_save_const_enum {
    mipc_sms_send_save_const_NONE = 0,
    /* SMS_SEND_SAVE */
    MIPC_SMS_SEND_SAVE_NO_SAVE                              = 0,
    MIPC_SMS_SEND_SAVE_SAVE_IN_SIM                          = 1,
    MIPC_SMS_SEND_SAVE_INVALID                              = 0xFF,
};
typedef enum mipc_sms_send_save_const_enum mipc_sms_send_save_const_enum;

enum mipc_sms_more_msg_to_send_const_enum {
    mipc_sms_more_msg_to_send_const_NONE = 0,
    /* SMS_MORE_MSG_TO_SEND */
    /*  */
    MIPC_SMS_MORE_MSG_TO_SEND_DISABLE                       = 0,
    /* after a while MD would return to disable, refer AT+CMMS=1 */
    MIPC_SMS_MORE_MSG_TO_SEND_ENABLE_ONCE                   = 1,
    /* MD would not return to disable automatically, refer AT+CMMS=2 */
    MIPC_SMS_MORE_MSG_TO_SEND_ENABLE_ALWAYS                 = 2,
    /* NULL value, nothing todo */
    MIPC_SMS_MORE_MSG_TO_SEND_NULL                          = 0xFE,
    /* INVALID value */
    MIPC_SMS_MORE_MSG_TO_SEND_INVALID                       = 0xFF,
};
typedef enum mipc_sms_more_msg_to_send_const_enum mipc_sms_more_msg_to_send_const_enum;

enum mipc_sms_cbm_cfg_type_const_enum {
    mipc_sms_cbm_cfg_type_const_NONE = 0,
    /* SMS_CBM_CFG_TYPE */
    /* list in corresponding cfg IE would indicate to USER */
    MIPC_SMS_CBM_CFG_TYPE_ALLOW                             = 1,
    /* list in corresponding cfg IE would not indicate to USER */
    MIPC_SMS_CBM_CFG_TYPE_BAN                               = 2,
    /* query DEVICE's value of corresponding cfg */
    MIPC_SMS_CBM_CFG_TYPE_QUERY                             = 0xFD,
};
typedef enum mipc_sms_cbm_cfg_type_const_enum mipc_sms_cbm_cfg_type_const_enum;

enum mipc_sms_scbm_status_const_enum {
    mipc_sms_scbm_status_const_NONE = 0,
    /* SMS_SCBM_STATUS */
    MIPC_SMS_SCBM_STATUS_EXIT                               = 0,
    MIPC_SMS_SCBM_STATUS_ENTERED                            = 1,
    MIPC_SMS_SCBM_STATUS_DISABLED                           = 2,
    MIPC_SMS_SCBM_STATUS_REINITED                           = 3,
};
typedef enum mipc_sms_scbm_status_const_enum mipc_sms_scbm_status_const_enum;

enum mipc_sms_c2k_err_class_const_enum {
    mipc_sms_c2k_err_class_const_NONE = 0,
    /* SMS_C2K_ERR_CLASS */
    MIPC_SMS_C2K_ERR_CLASS_NO_ERR                           = 0,
    MIPC_SMS_C2K_ERR_CLASS_TEMP                             = 2,
    MIPC_SMS_C2K_ERR_CLASS_PERMANENT                        = 3,
    MIPC_SMS_C2K_ERR_CLASS_INVALID                          = 0xFF,
};
typedef enum mipc_sms_c2k_err_class_const_enum mipc_sms_c2k_err_class_const_enum;

enum mipc_sms_text_mode_param_action_const_enum {
    mipc_sms_text_mode_param_action_const_NONE = 0,
    /* SMS_TEXT_MODE_PARAM_ACTION */
    MIPC_SMS_TEXT_MODE_PARAM_ACTION_SET                     = 1,
    MIPC_SMS_TEXT_MODE_PARAM_ACTION_QUERY                   = 0xFD,
    MIPC_SMS_TEXT_MODE_PARAM_ACTION_NULL                    = 0xFE,
    MIPC_SMS_TEXT_MODE_PARAM_ACTION_INVALID                 = 0xFF,
};
typedef enum mipc_sms_text_mode_param_action_const_enum mipc_sms_text_mode_param_action_const_enum;

enum mipc_sms_c2k_err_code_const_enum {
    mipc_sms_c2k_err_code_const_NONE = 0,
    /* SMS_C2K_ERR_CODE */
    MIPC_SMS_C2K_ERR_CODE_FDN_CHECK                         = 0x0E,
    MIPC_SMS_C2K_ERR_CODE_RUIM_ABSENT                       = 0x6B,
};
typedef enum mipc_sms_c2k_err_code_const_enum mipc_sms_c2k_err_code_const_enum;

enum mipc_em_id_type_const_enum {
    mipc_em_id_type_const_NONE = 0,
    /* EM_ID_TYPE */
    MIPC_EM_ID_TYPE_UNKNOWN_SERVICE                         = 0,
    MIPC_EM_ID_TYPE_NOT_EMERGENCY_SERVICE                   = 1,
    MIPC_EM_ID_TYPE_EMERGENCY_SERVICE                       = 2,
    MIPC_EM_ID_TYPE_MAX                                     = 3,
};
typedef enum mipc_em_id_type_const_enum mipc_em_id_type_const_enum;

enum mipc_pdis_method_type_const_enum {
    mipc_pdis_method_type_const_NONE = 0,
    /* PDIS_METHOD_TYPE */
    MIPC_PDIS_METHOD_TYPE_NONE                              = 0,
    MIPC_PDIS_METHOD_TYPE_SIM                               = 1,
    MIPC_PDIS_METHOD_TYPE_MO                                = 2,
    MIPC_PDIS_METHOD_TYPE_PCO                               = 3,
    MIPC_PDIS_METHOD_TYPE_DHCPV4                            = 4,
    MIPC_PDIS_METHOD_TYPE_DHCPV6                            = 5,
    MIPC_PDIS_METHOD_TYPE_MANUL                             = 6,
};
typedef enum mipc_pdis_method_type_const_enum mipc_pdis_method_type_const_enum;

enum mipc_scm_application_enum_const_enum {
    mipc_scm_application_enum_const_NONE = 0,
    /* SCM_APPLICATION_ENUM */
    MIPC_SCM_APPLICATION_ENUM_MMTEL_VOICE                   = 0,
    MIPC_SCM_APPLICATION_ENUM_MMTEL_VIDEO                   = 1,
    MIPC_SCM_APPLICATION_ENUM_SMS_OVER_IP                   = 2,
    MIPC_SCM_APPLICATION_ENUM_MAX                           = 0x7F,
};
typedef enum mipc_scm_application_enum_const_enum mipc_scm_application_enum_const_enum;

enum mipc_scm_indication_enum_const_enum {
    mipc_scm_indication_enum_const_NONE = 0,
    /* SCM_INDICATION_ENUM */
    MIPC_SCM_INDICATION_ENUM_START_INDICATION               = 1,
    MIPC_SCM_INDICATION_ENUM_END_INDICATION                 = 2,
    MIPC_SCM_INDICATION_ENUM_MAX                            = 0x7F,
};
typedef enum mipc_scm_indication_enum_const_enum mipc_scm_indication_enum_const_enum;

enum mipc_ims_service_type_enum_const_enum {
    mipc_ims_service_type_enum_const_NONE = 0,
    /* IMS_SERVICE_TYPE_ENUM */
    MIPC_IMS_SERVICE_TYPE_ENUM_NORMAL_VOICE_CALL            = 1,
    MIPC_IMS_SERVICE_TYPE_ENUM_NORMAL_VIDEO_CALL            = 2,
    MIPC_IMS_SERVICE_TYPE_ENUM_SMS                          = 4,
    MIPC_IMS_SERVICE_TYPE_ENUM_REG_SIG                      = 8,
    MIPC_IMS_SERVICE_TYPE_ENUM_MAX                          = 0x7F,
};
typedef enum mipc_ims_service_type_enum_const_enum mipc_ims_service_type_enum_const_enum;

enum mipc_ims_service_status_enum_const_enum {
    mipc_ims_service_status_enum_const_NONE = 0,
    /* IMS_SERVICE_STATUS_ENUM */
    MIPC_IMS_SERVICE_STATUS_ENUM_START_INDICATION           = 0,
    MIPC_IMS_SERVICE_STATUS_ENUM_STOP_INDICATION            = 1,
    MIPC_IMS_SERVICE_STATUS_ENUM_MAX                        = 0x7F,
};
typedef enum mipc_ims_service_status_enum_const_enum mipc_ims_service_status_enum_const_enum;

enum mipc_act_call_ntf_enum_const_enum {
    mipc_act_call_ntf_enum_const_NONE = 0,
    /* ACT_CALL_NTF_ENUM */
    MIPC_ACT_CALL_NTF_ENUM_USE_FB_DATA_CALL                 = 0,
    MIPC_ACT_CALL_NTF_ENUM_UNUSE_FB_DATA_CALL               = 1,
    MIPC_ACT_CALL_NTF_ENUM_MAX                              = 0x7F,
};
typedef enum mipc_act_call_ntf_enum_const_enum mipc_act_call_ntf_enum_const_enum;

enum mipc_wfc_signal_type_const_enum {
    mipc_wfc_signal_type_const_NONE = 0,
    /* WFC_SIGNAL_TYPE */
    MIPC_WFC_SIGNAL_TYPE_LTE_RSRP                           = 0,
    MIPC_WFC_SIGNAL_TYPE_LTE_RS_SNR                         = 1,
    MIPC_WFC_SIGNAL_TYPE_UMTS_RSCP                          = 2,
    MIPC_WFC_SIGNAL_TYPE_UMTS_ECNO                          = 3,
    MIPC_WFC_SIGNAL_TYPE_LTE_RSRQ                           = 4,
    MIPC_WFC_SIGNAL_TYPE_NR_SS_RSRP                         = 5,
    MIPC_WFC_SIGNAL_TYPE_INVALID                            = 0xFF,
};
typedef enum mipc_wfc_signal_type_const_enum mipc_wfc_signal_type_const_enum;

enum mipc_epdg_screen_state_const_enum {
    mipc_epdg_screen_state_const_NONE = 0,
    /* EPDG_SCREEN_STATE */
    MIPC_EPDG_SCREEN_STATE_UNLOCK                           = 0,
    MIPC_EPDG_SCREEN_STATE_LOCK                             = 1,
    MIPC_EPDG_SCREEN_STATE_OPEN_KEYGUARD_ON                 = 2,
    MIPC_EPDG_SCREEN_STATE_INVALID                          = 0xFF,
};
typedef enum mipc_epdg_screen_state_const_enum mipc_epdg_screen_state_const_enum;

enum mipc_wifi_type_const_enum {
    mipc_wifi_type_const_NONE = 0,
    /* WIFI_TYPE */
    MIPC_WIFI_TYPE_802_11                                   = 0,
    MIPC_WIFI_TYPE_802_11a                                  = 1,
    MIPC_WIFI_TYPE_802_11b                                  = 2,
    MIPC_WIFI_TYPE_802_11g                                  = 3,
    MIPC_WIFI_TYPE_802_11n                                  = 4,
    MIPC_WIFI_TYPE_802_11ac                                 = 5,
    MIPC_WIFI_TYPE_INVALID                                  = 0xFF,
};
typedef enum mipc_wifi_type_const_enum mipc_wifi_type_const_enum;

enum mipc_wfc_prefer_const_enum {
    mipc_wfc_prefer_const_NONE = 0,
    /* WFC_PREFER */
    MIPC_WFC_PREFER_CELL_ONLY                               = 0,
    MIPC_WFC_PREFER_WIFI_PREFER                             = 1,
    MIPC_WFC_PREFER_CELL_PREFER                             = 2,
    MIPC_WFC_PREFER_WIFI_ONLY                               = 3,
    MIPC_WFC_PREFER_INVALID                                 = 0xFF,
};
typedef enum mipc_wfc_prefer_const_enum mipc_wfc_prefer_const_enum;

enum mipc_wfc_rat_const_enum {
    mipc_wfc_rat_const_NONE = 0,
    /* WFC_RAT */
    MIPC_WFC_RAT_3GPP                                       = 1,
    MIPC_WFC_RAT_WIFI                                       = 2,
    MIPC_WFC_RAT_INVALID                                    = 0xFF,
};
typedef enum mipc_wfc_rat_const_enum mipc_wfc_rat_const_enum;

enum mipc_wfc_pdn_type_const_enum {
    mipc_wfc_pdn_type_const_NONE = 0,
    /* WFC_PDN_TYPE */
    MIPC_WFC_PDN_TYPE_IMS                                   = 0,
    MIPC_WFC_PDN_TYPE_SMS                                   = 1,
    MIPC_WFC_PDN_TYPE_MMS                                   = 2,
    MIPC_WFC_PDN_TYPE_INVALID                               = 0xFF,
};
typedef enum mipc_wfc_pdn_type_const_enum mipc_wfc_pdn_type_const_enum;

enum mipc_wfc_pdn_ho_status_const_enum {
    mipc_wfc_pdn_ho_status_const_NONE = 0,
    /* WFC_PDN_HO_STATUS */
    MIPC_WFC_PDN_HO_STATUS_START                            = 0,
    MIPC_WFC_PDN_HO_STATUS_SUCCESS                          = 1,
    MIPC_WFC_PDN_HO_STATUS_FAIL                             = 0xFF,
};
typedef enum mipc_wfc_pdn_ho_status_const_enum mipc_wfc_pdn_ho_status_const_enum;

enum mipc_wfc_pdn_oos_state_const_enum {
    mipc_wfc_pdn_oos_state_const_NONE = 0,
    /* WFC_PDN_OOS_STATE */
    MIPC_WFC_PDN_OOS_STATE_OOS_END_PDN_DIS                  = 0,
    MIPC_WFC_PDN_OOS_STATE_OOS_START                        = 1,
    MIPC_WFC_PDN_OOS_STATE_OOS_END_PDN_RESUME               = 2,
    MIPC_WFC_PDN_OOS_STATE_FAIL                             = 0xFF,
};
typedef enum mipc_wfc_pdn_oos_state_const_enum mipc_wfc_pdn_oos_state_const_enum;

enum mipc_wfc_wifi_pdn_state_const_enum {
    mipc_wfc_wifi_pdn_state_const_NONE = 0,
    /* WFC_WIFI_PDN_STATE */
    MIPC_WFC_WIFI_PDN_STATE_NOT_REGISTERED                  = 0,
    MIPC_WFC_WIFI_PDN_STATE_REGISTERED                      = 1,
    MIPC_WFC_WIFI_PDN_STATE_NOT_REGISTERED_WITH_LOCK        = 2,
    MIPC_WFC_WIFI_PDN_STATE_INVALID                         = 0xFF,
};
typedef enum mipc_wfc_wifi_pdn_state_const_enum mipc_wfc_wifi_pdn_state_const_enum;

enum mipc_ss_ussd_const_enum {
    mipc_ss_ussd_const_NONE = 0,
    /* SS_USSD */
    MIPC_SS_USSD_NO_ACTION_REQUIRED                         = 0,
    MIPC_SS_USSD_ACTION_REQUIRED                            = 1,
    MIPC_SS_USSD_TERMINATED_BY_NW                           = 2,
    MIPC_SS_USSD_OTHER_LOCAL_CLIENT                         = 3,
    MIPC_SS_USSD_OPERATION_NOT_SUPPORTED                    = 4,
    MIPC_SS_USSD_NW_TIME_OUT                                = 5,
};
typedef enum mipc_ss_ussd_const_enum mipc_ss_ussd_const_enum;

enum mipc_ss_session_const_enum {
    mipc_ss_session_const_NONE = 0,
    /* SS_SESSION */
    MIPC_SS_SESSION_NEW                                     = 0,
    MIPC_SS_SESSION_EXISTING                                = 1,
};
typedef enum mipc_ss_session_const_enum mipc_ss_session_const_enum;

enum mipc_ss_call_waiting_const_enum {
    mipc_ss_call_waiting_const_NONE = 0,
    /* SS_CALL_WAITING */
    MIPC_SS_CALL_WAITING_DISABLE                            = 0,
    MIPC_SS_CALL_WAITING_ENABLE                             = 1,
};
typedef enum mipc_ss_call_waiting_const_enum mipc_ss_call_waiting_const_enum;

enum mipc_ss_set_call_forward_operation_code_const_enum {
    mipc_ss_set_call_forward_operation_code_const_NONE = 0,
    /* SS_SET_CALL_FORWARD_OPERATION_CODE */
    MIPC_SS_SET_CALL_FORWARD_OPERATION_CODE_SS_ACTIVATE     = 0,
    MIPC_SS_SET_CALL_FORWARD_OPERATION_CODE_SS_DEACTIVATE   = 1,
    MIPC_SS_SET_CALL_FORWARD_OPERATION_CODE_SS_REGISTRATION = 3,
    MIPC_SS_SET_CALL_FORWARD_OPERATION_CODE_SS_ERASURE      = 4,
};
typedef enum mipc_ss_set_call_forward_operation_code_const_enum mipc_ss_set_call_forward_operation_code_const_enum;

enum mipc_ss_call_forward_reason_const_enum {
    mipc_ss_call_forward_reason_const_NONE = 0,
    /* SS_CALL_FORWARD_REASON */
    MIPC_SS_CALL_FORWARD_REASON_CALL_FORWARD_UNCONDITIONAL  = 21,
    MIPC_SS_CALL_FORWARD_REASON_CALL_FORWARD_BUSY           = 67,
    MIPC_SS_CALL_FORWARD_REASON_CALL_FORWARD_NO_REPLY       = 61,
    MIPC_SS_CALL_FORWARD_REASON_CALL_FORWARD_NOT_REACHABLE  = 62,
    MIPC_SS_CALL_FORWARD_REASON_CALL_FORWARD_ALL            = 2,
    MIPC_SS_CALL_FORWARD_REASON_CALL_FORWARD_ALL_CONDITIONAL = 4,
    MIPC_SS_CALL_FORWARD_REASON_CALL_FORWARD_NOT_REGISTER   = 68,
};
typedef enum mipc_ss_call_forward_reason_const_enum mipc_ss_call_forward_reason_const_enum;

enum mipc_ss_active_status_const_enum {
    mipc_ss_active_status_const_NONE = 0,
    /* SS_ACTIVE_STATUS */
    MIPC_SS_ACTIVE_STATUS_NOT_ACTIVE                        = 0,
    MIPC_SS_ACTIVE_STATUS_ACTIVE                            = 1,
};
typedef enum mipc_ss_active_status_const_enum mipc_ss_active_status_const_enum;

enum mipc_ss_type_of_address_const_enum {
    mipc_ss_type_of_address_const_NONE = 0,
    /* SS_TYPE_OF_ADDRESS */
    MIPC_SS_TYPE_OF_ADDRESS_NORMAL                          = 0,
    MIPC_SS_TYPE_OF_ADDRESS_INTERNATIONAL                   = 1,
};
typedef enum mipc_ss_type_of_address_const_enum mipc_ss_type_of_address_const_enum;

enum mipc_ss_service_class_const_enum {
    mipc_ss_service_class_const_NONE = 0,
    /* SS_SERVICE_CLASS */
    MIPC_SS_SERVICE_CLASS_NONE                              = 0,
    MIPC_SS_SERVICE_CLASS_VOICE                             = 1,
    MIPC_SS_SERVICE_CLASS_DATA                              = 2,
    MIPC_SS_SERVICE_CLASS_FAX                               = 4,
    MIPC_SS_SERVICE_CLASS_SMS                               = 8,
    MIPC_SS_SERVICE_CLASS_DATA_CIRCUIT_SYNC                 = 16,
    MIPC_SS_SERVICE_CLASS_DATA_CIRCUIT_ASYNC                = 32,
    MIPC_SS_SERVICE_CLASS_DEDICATED_PACKET_ACCESS           = 64,
    MIPC_SS_SERVICE_CLASS_DEDICATED_PAD_ACCESS              = 128,
    MIPC_SS_SERVICE_CLASS_MTK_LINE2                         = 256,
    MIPC_SS_SERVICE_CLASS_MTK_VIDEO                         = 512,
};
typedef enum mipc_ss_service_class_const_enum mipc_ss_service_class_const_enum;

enum mipc_ss_call_barring_lock_const_enum {
    mipc_ss_call_barring_lock_const_NONE = 0,
    /* SS_CALL_BARRING_LOCK */
    MIPC_SS_CALL_BARRING_LOCK_UNLOCK                        = 0,
    MIPC_SS_CALL_BARRING_LOCK_LOCK                          = 1,
};
typedef enum mipc_ss_call_barring_lock_const_enum mipc_ss_call_barring_lock_const_enum;

enum mipc_ss_call_barring_fac_const_enum {
    mipc_ss_call_barring_fac_const_NONE = 0,
    /* SS_CALL_BARRING_FAC */
    MIPC_SS_CALL_BARRING_FAC_AO                             = 0,
    MIPC_SS_CALL_BARRING_FAC_OI                             = 1,
    MIPC_SS_CALL_BARRING_FAC_OX                             = 2,
    MIPC_SS_CALL_BARRING_FAC_AI                             = 3,
    MIPC_SS_CALL_BARRING_FAC_IR                             = 4,
    MIPC_SS_CALL_BARRING_FAC_AB                             = 5,
    MIPC_SS_CALL_BARRING_FAC_AG                             = 6,
    MIPC_SS_CALL_BARRING_FAC_AC                             = 7,
    MIPC_SS_CALL_BARRING_FAC_ACR                            = 8,
};
typedef enum mipc_ss_call_barring_fac_const_enum mipc_ss_call_barring_fac_const_enum;

enum mipc_ss_cnap_state_const_enum {
    mipc_ss_cnap_state_const_NONE = 0,
    /* SS_CNAP_STATE */
    MIPC_SS_CNAP_STATE_DISABLE                              = 0,
    MIPC_SS_CNAP_STATE_ENABLE                               = 1,
};
typedef enum mipc_ss_cnap_state_const_enum mipc_ss_cnap_state_const_enum;

enum mipc_ss_ecfu_icon_status_const_enum {
    mipc_ss_ecfu_icon_status_const_NONE = 0,
    /* SS_ECFU_ICON_STATUS */
    MIPC_SS_ECFU_ICON_STATUS_HIDE_CFU_ICON                  = 0,
    MIPC_SS_ECFU_ICON_STATUS_SHOW_CFU_ICON                  = 1,
};
typedef enum mipc_ss_ecfu_icon_status_const_enum mipc_ss_ecfu_icon_status_const_enum;

enum mipc_spi_status_enum_const_enum {
    mipc_spi_status_enum_const_NONE = 0,
    /* SPI_STATUS_ENUM */
    MIPC_SPI_STATUS_ENUM_SUCCESS                            = 0,
    MIPC_SPI_STATUS_ENUM_FAILURE                            = 1,
    MIPC_SPI_STATUS_ENUM_ENCAP_NO_RULE                      = 2,
    MIPC_SPI_STATUS_ENUM_DECAP_NO_RULE                      = 2,
    MIPC_SPI_STATUS_ENUM_DECAP_PACKET_SA_UNMATCH            = 3,
    MIPC_SPI_STATUS_ENUM_SPI_FREE_FAIL_SA_EXISTANT          = 4,
    MIPC_SPI_STATUS_ENUM_ENCAP_SA_SUSPEND                   = 5,
    MIPC_SPI_STATUS_ENUM_MAX                                = 6,
};
typedef enum mipc_spi_status_enum_const_enum mipc_spi_status_enum_const_enum;

enum mipc_ipsec_proto_enum_const_enum {
    mipc_ipsec_proto_enum_const_NONE = 0,
    /* IPSEC_PROTO_ENUM */
    MIPC_IPSEC_PROTO_ENUM_ESP                               = 50,
    MIPC_IPSEC_PROTO_ENUM_AH                                = 51,
    MIPC_IPSEC_PROTO_ENUM_MAX                               = 0x7F,
};
typedef enum mipc_ipsec_proto_enum_const_enum mipc_ipsec_proto_enum_const_enum;

enum mipc_ipsec_mode_enum_const_enum {
    mipc_ipsec_mode_enum_const_NONE = 0,
    /* IPSEC_MODE_ENUM */
    MIPC_IPSEC_MODE_ENUM_transport                          = 0,
    MIPC_IPSEC_MODE_ENUM_tunnel                             = 1,
    MIPC_IPSEC_MODE_ENUM_MAX                                = 0x7F,
};
typedef enum mipc_ipsec_mode_enum_const_enum mipc_ipsec_mode_enum_const_enum;

enum mipc_stk_not_handled_const_enum {
    mipc_stk_not_handled_const_NONE = 0,
    /* STK_NOT_HANDLED */
    MIPC_STK_NOT_HANDLED_BY_FUNCTION_CANNOT_BE_HANDLED_BY_HOST = 0,
    MIPC_STK_NOT_HANDLED_By_FUNCTION_MAY_BE_HANDLED_BY_HOST = 1,
};
typedef enum mipc_stk_not_handled_const_enum mipc_stk_not_handled_const_enum;

enum mipc_stk_handled_const_enum {
    mipc_stk_handled_const_NONE = 0,
    /* STK_HANDLED */
    MIPC_STK_HANDLED_BY_FUNCTION_ONLY_TRANSPARENT_TO_HOST   = 2,
    MIPC_STK_HANDLED_BY_FUNCTION_NOTIFICATION_TO_HOST_POSSIBLE = 3,
    MIPC_STK_HANDLED_BY_FUNCTION_NOTIFICATIONS_TO_HOST_ENABLE = 4,
    MIPC_STK_HANDLED_BY_FUNCTION_CAN_BE_OVERRIDDEN_BY_HOST  = 5,
    MIPC_STK_HANDLED_BY_HOST_FUNCTION_NOT_ABLE_TO_HANDLE    = 6,
    MIPC_STK_HANDLED_BY_HOST_FUNCTION_ABLE_TO_HANDLE        = 7,
};
typedef enum mipc_stk_handled_const_enum mipc_stk_handled_const_enum;

enum mipc_stk_pac_type_const_enum {
    mipc_stk_pac_type_const_NONE = 0,
    /* STK_PAC_TYPE */
    MIPC_STK_PAC_TYPE_PROACTIVE_COMMAND                     = 0,
    MIPC_STK_PAC_TYPE_NOTIFICATION                          = 1,
    MIPC_STK_PAC_TYPE_SESSION_END                           = 2,
};
typedef enum mipc_stk_pac_type_const_enum mipc_stk_pac_type_const_enum;

enum mipc_sim_refresh_result_type_const_enum {
    mipc_sim_refresh_result_type_const_NONE = 0,
    /* SIM_REFRESH_RESULT_TYPE */
    MIPC_SIM_REFRESH_RESULT_TYPE_SIM_FILE_UPDATE            = 0,
    MIPC_SIM_REFRESH_RESULT_TYPE_SIM_INIT                   = 1,
    MIPC_SIM_REFRESH_RESULT_TYPE_SIM_RESET                  = 2,
    MIPC_SIM_REFRESH_RESULT_TYPE_APP_INIT                   = 3,
    MIPC_SIM_REFRESH_RESULT_TYPE_SIM_INIT_FULL_FILE_CHANGE  = 4,
    MIPC_SIM_REFRESH_RESULT_TYPE_SIM_INIT_FILE_CHANGE       = 5,
    MIPC_SIM_REFRESH_RESULT_TYPE_SESSION_RESET              = 6,
};
typedef enum mipc_sim_refresh_result_type_const_enum mipc_sim_refresh_result_type_const_enum;

enum mipc_ran_const_enum {
    mipc_ran_const_NONE = 0,
    /* RAN */
    MIPC_RAN_UNKNOWN                                        = 0,
    MIPC_RAN_CELL                                           = 1,
    MIPC_RAN_WIFI                                           = 2,
    MIPC_RAN_3GPP2                                          = 3,
    MIPC_RAN_DATA1                                          = 4,
    MIPC_RAN_DATA2                                          = 5,
    MIPC_RAN_DATA3                                          = 6,
    MIPC_RAN_DATA4                                          = 7,
};
typedef enum mipc_ran_const_enum mipc_ran_const_enum;

enum mipc_call_clcc_state_const_enum {
    mipc_call_clcc_state_const_NONE = 0,
    /* CALL_CLCC_STATE */
    MIPC_CALL_CLCC_STATE_ACTIVE                             = 0,
    MIPC_CALL_CLCC_STATE_HELD                               = 1,
    MIPC_CALL_CLCC_STATE_DIALING                            = 2,
    MIPC_CALL_CLCC_STATE_ALERTING                           = 3,
    MIPC_CALL_CLCC_STATE_INCOMING                           = 4,
    MIPC_CALL_CLCC_STATE_WAITING                            = 5,
};
typedef enum mipc_call_clcc_state_const_enum mipc_call_clcc_state_const_enum;

enum mipc_call_direction_const_enum {
    mipc_call_direction_const_NONE = 0,
    /* CALL_DIRECTION */
    MIPC_CALL_DIRECTION_MO_CALL                             = 0,
    MIPC_CALL_DIRECTION_MT_CALL                             = 1,
};
typedef enum mipc_call_direction_const_enum mipc_call_direction_const_enum;

enum mipc_sdp_direction_const_enum {
    mipc_sdp_direction_const_NONE = 0,
    /* SDP_DIRECTION */
    MIPC_SDP_DIRECTION_INACTIVE                             = 0,
    MIPC_SDP_DIRECTION_SEND_ONLY                            = 1,
    MIPC_SDP_DIRECTION_RECV_ONLY                            = 2,
    MIPC_SDP_DIRECTION_SEND_RECV                            = 3,
};
typedef enum mipc_sdp_direction_const_enum mipc_sdp_direction_const_enum;

enum mipc_speech_rat_const_enum {
    mipc_speech_rat_const_NONE = 0,
    /* SPEECH_RAT */
    MIPC_SPEECH_RAT_GSM                                     = 1,
    MIPC_SPEECH_RAT_UTMS                                    = 2,
    MIPC_SPEECH_RAT_IMS                                     = 4,
};
typedef enum mipc_speech_rat_const_enum mipc_speech_rat_const_enum;

enum mipc_call_rat_const_enum {
    mipc_call_rat_const_NONE = 0,
    /* CALL_RAT */
    MIPC_CALL_RAT_UNKNOWN                                   = 0,
    MIPC_CALL_RAT_CS                                        = 1,
    MIPC_CALL_RAT_VoLTE                                     = 2,
    MIPC_CALL_RAT_WFC                                       = 3,
    MIPC_CALL_RAT_VoNR                                      = 4,
};
typedef enum mipc_call_rat_const_enum mipc_call_rat_const_enum;

enum mipc_call_type_const_enum {
    mipc_call_type_const_NONE = 0,
    /* CALL_TYPE */
    /*  */
    MIPC_CALL_TYPE_MPTY                                     = 0x00000001,
    /*  */
    MIPC_CALL_TYPE_EMERGENCY                                = 0x00000010,
    /*  */
    MIPC_CALL_TYPE_VIDEO                                    = 0x00000100,
    /*  */
    MIPC_CALL_TYPE_RTT                                      = 0x00001000,
    /*  */
    MIPC_CALL_TYPE_IN_BAND_TONE                             = 0x00010000,
    /*  */
    MIPC_CALL_TYPE_IN_BAND_TONE_VIDEO                       = 0x00020000,
    /*  */
    MIPC_CALL_TYPE_IN_BAND_TONE_VIDEO_VOICE                 = 0x00030000,
    /*  */
    MIPC_CALL_TYPE_TCH                                      = 0x00100000,
};
typedef enum mipc_call_type_const_enum mipc_call_type_const_enum;

enum mipc_call_mode_const_enum {
    mipc_call_mode_const_NONE = 0,
    /* CALL_MODE */
    MIPC_CALL_MODE_VOICE                                    = 0,
    MIPC_CALL_MODE_DATA                                     = 1,
    MIPC_CALL_MODE_VFD_VOICE                                = 3,
    MIPC_CALL_MODE_AVD_VOICE                                = 4,
    MIPC_CALL_MODE_AVF_VOICE                                = 5,
    MIPC_CALL_MODE_VFD_DATA                                 = 6,
    MIPC_CALL_MODE_AVD_DATA                                 = 7,
    MIPC_CALL_MODE_UNKNOWN                                  = 9,
    MIPC_CALL_MODE_IMS_VOICE_CALL                           = 20,
    MIPC_CALL_MODE_IMS_VIDEO_CALL                           = 21,
    MIPC_CALL_MODE_IMS_VOICE_CONFERENCE                     = 22,
    MIPC_CALL_MODE_IMS_VIDEO_CONFERENCE                     = 23,
    MIPC_CALL_MODE_IMS_VOICE_CONFERENCE_PARTICIPANT         = 24,
    MIPC_CALL_MODE_IMS_VIDEO_CONFERENCE_PARTICIPANT         = 25,
    MIPC_CALL_MODE_C2K_VOICE_CALL                           = 40,
    MIPC_CALL_MODE_C2K_OTASP_CALL_STD                       = 41,
    MIPC_CALL_MODE_C2K_OTASP_CALL_NO_STD                    = 42,
    MIPC_CALL_MODE_C2K_ECC_CALL                             = 43,
};
typedef enum mipc_call_mode_const_enum mipc_call_mode_const_enum;

enum mipc_call_dial_address_type_const_enum {
    mipc_call_dial_address_type_const_NONE = 0,
    /* CALL_DIAL_ADDRESS_TYPE */
    MIPC_CALL_DIAL_ADDRESS_TYPE_NONE                        = 0,
    MIPC_CALL_DIAL_ADDRESS_TYPE_SIP_URI                     = 1,
    MIPC_CALL_DIAL_ADDRESS_TYPE_NUMBER                      = 2,
};
typedef enum mipc_call_dial_address_type_const_enum mipc_call_dial_address_type_const_enum;

enum mipc_call_audio_codec_const_enum {
    mipc_call_audio_codec_const_NONE = 0,
    /* CALL_AUDIO_CODEC */
    MIPC_CALL_AUDIO_CODEC_NONE                              = 0x0000,
    MIPC_CALL_AUDIO_CODEC_QCELP13K                          = 0x0001,
    MIPC_CALL_AUDIO_CODEC_EVRC                              = 0x0002,
    MIPC_CALL_AUDIO_CODEC_EVRC_B                            = 0x0003,
    MIPC_CALL_AUDIO_CODEC_EVRC_WB                           = 0x0004,
    MIPC_CALL_AUDIO_CODEC_EVRC_NW                           = 0x0005,
    MIPC_CALL_AUDIO_CODEC_AMR_NB                            = 0x0006,
    MIPC_CALL_AUDIO_CODEC_AMR_WB                            = 0x0007,
    MIPC_CALL_AUDIO_CODEC_GSM_EFR                           = 0x0008,
    MIPC_CALL_AUDIO_CODEC_GSM_FR                            = 0x0009,
    MIPC_CALL_AUDIO_CODEC_GSM_HR                            = 0x000a,
    MIPC_CALL_AUDIO_CODEC_EVS_NB                            = 0x0017,
    MIPC_CALL_AUDIO_CODEC_EVS_WB                            = 0x0018,
    MIPC_CALL_AUDIO_CODEC_EVS_SW                            = 0x0019,
    MIPC_CALL_AUDIO_CODEC_EVS_FB                            = 0x0020,
    MIPC_CALL_AUDIO_CODEC_EVS_AWB                           = 0x0021,
};
typedef enum mipc_call_audio_codec_const_enum mipc_call_audio_codec_const_enum;

enum mipc_sdp_audio_codec_const_enum {
    mipc_sdp_audio_codec_const_NONE = 0,
    /* SDP_AUDIO_CODEC */
    MIPC_SDP_AUDIO_CODEC_AMR                                = 1,
    MIPC_SDP_AUDIO_CODEC_AMR_WB                             = 2,
    MIPC_SDP_AUDIO_CODEC_EVS                                = 17,
};
typedef enum mipc_sdp_audio_codec_const_enum mipc_sdp_audio_codec_const_enum;

enum mipc_call_event_const_enum {
    mipc_call_event_const_NONE = 0,
    /* CALL_EVENT */
    /*  */
    MIPC_CALL_EVENT_MT_REJECTED                             = 1,
    /*  */
    MIPC_CALL_EVENT_MT_REDIRECT                             = 2,
    /*  */
    MIPC_CALL_EVENT_SRVCC                                   = 3,
    /*  */
    MIPC_CALL_EVENT_AUDIO_CODEC_CHANGE                      = 4,
    /*  */
    MIPC_CALL_EVENT_SPEECH_ATTACH                           = 5,
    /*  */
    MIPC_CALL_EVENT_CRING                                   = 6,
    /*  */
    MIPC_CALL_EVENT_RAT                                     = 7,
    /*  */
    MIPC_CALL_EVENT_NO_CARRIER                              = 8,
    /*  */
    MIPC_CALL_EVENT_ECONFSRVCC                              = 9,
};
typedef enum mipc_call_event_const_enum mipc_call_event_const_enum;

enum mipc_gwsd_event_const_enum {
    mipc_gwsd_event_const_NONE = 0,
    /* GWSD_EVENT */
    /*  */
    MIPC_GWSD_EVENT_ECRFCPY                                 = 1,
    /*  */
    MIPC_GWSD_EVENT_EICPGU                                  = 2,
    /*  */
    MIPC_GWSD_EVENT_EICPGRES                                = 3,
};
typedef enum mipc_gwsd_event_const_enum mipc_gwsd_event_const_enum;

enum mipc_call_msg_type_const_enum {
    mipc_call_msg_type_const_NONE = 0,
    /* CALL_MSG_TYPE */
    MIPC_CALL_MSG_TYPE_MT_CALL                              = 0,
    MIPC_CALL_MSG_TYPE_DISCONNECT                           = 1,
    MIPC_CALL_MSG_TYPE_ALERT                                = 2,
    MIPC_CALL_MSG_TYPE_CALL_PROCESS                         = 3,
    MIPC_CALL_MSG_TYPE_SYNC                                 = 4,
    MIPC_CALL_MSG_TYPE_PROGRESS                             = 5,
    MIPC_CALL_MSG_TYPE_CONNECTED                            = 6,
    MIPC_CALL_MSG_TYPE_ALL_CALLS_DISC                       = 129,
    MIPC_CALL_MSG_TYPE_CALL_ID_ASSIGN                       = 130,
    MIPC_CALL_MSG_TYPE_STATE_CHANGE_HELD                    = 131,
    MIPC_CALL_MSG_TYPE_STATE_CHANGE_ACTIVE                  = 132,
    MIPC_CALL_MSG_TYPE_STATE_CHANGE_DISCONNECTED            = 133,
    MIPC_CALL_MSG_TYPE_STATE_CHANGE_MO_DISCONNECTING        = 134,
    MIPC_CALL_MSG_TYPE_STATE_HELD_BY_REMOTE                 = 135,
    MIPC_CALL_MSG_TYPE_STATE_ACTIVE_BY_REMOTE               = 136,
};
typedef enum mipc_call_msg_type_const_enum mipc_call_msg_type_const_enum;

enum mipc_call_reject_reason_const_enum {
    mipc_call_reject_reason_const_NONE = 0,
    /* CALL_REJECT_REASON */
    MIPC_CALL_REJECT_REASON_UNDEFINED                       = 0,
};
typedef enum mipc_call_reject_reason_const_enum mipc_call_reject_reason_const_enum;

enum mipc_call_dial_type_const_enum {
    mipc_call_dial_type_const_NONE = 0,
    /* CALL_DIAL_TYPE */
    MIPC_CALL_DIAL_TYPE_VOICE                               = 1,
    MIPC_CALL_DIAL_TYPE_VIDEO                               = 2,
    MIPC_CALL_DIAL_TYPE_EMERGENCY                           = 3,
    MIPC_CALL_DIAL_TYPE_RTT                                 = 4,
};
typedef enum mipc_call_dial_type_const_enum mipc_call_dial_type_const_enum;

enum mipc_call_conference_dial_type_const_enum {
    mipc_call_conference_dial_type_const_NONE = 0,
    /* CALL_CONFERENCE_DIAL_TYPE */
    MIPC_CALL_CONFERENCE_DIAL_TYPE_VOICE                    = 1,
    MIPC_CALL_CONFERENCE_DIAL_TYPE_VIDEO                    = 2,
};
typedef enum mipc_call_conference_dial_type_const_enum mipc_call_conference_dial_type_const_enum;

enum mipc_call_dial_domain_const_enum {
    mipc_call_dial_domain_const_NONE = 0,
    /* CALL_DIAL_DOMAIN */
    /* Automatic - LTE(IMS), WG(CS), 1x(C2K) */
    MIPC_CALL_DIAL_DOMAIN_AUTO                              = 0,
    /* CS only - WG(CS) */
    MIPC_CALL_DIAL_DOMAIN_CS_ONLY                           = 1,
    /* 3GPP only - LTE(IMS), WG(CS) */
    MIPC_CALL_DIAL_DOMAIN_3GPP_ONLY                         = 2,
    /* 3GPP2 only - 1x(C2K) */
    MIPC_CALL_DIAL_DOMAIN_3GPP2_ONLY                        = 3,
    /* IMS and 3GPP2 only - NR(IMS), LTE(IMS), 1x(C2K) */
    MIPC_CALL_DIAL_DOMAIN_IMS_AND_3GPP2_ONLY                = 4,
    /* 3GPP CS and 3GPP2 only - WG(CS), 1x(C2K) */
    MIPC_CALL_DIAL_DOMAIN_3GPP_CS_AND_3GPP2_ONLY            = 5,
};
typedef enum mipc_call_dial_domain_const_enum mipc_call_dial_domain_const_enum;

enum mipc_call_ss_action_const_enum {
    mipc_call_ss_action_const_NONE = 0,
    /* CALL_SS_ACTION */
    /* release all held calls, or set User-Determined User Busy for a waiting call */
    MIPC_CALL_SS_ACTION_RELEASE_ALL_HELD_OR_WAITING_CALL    = 0,
    /* release all active calls and accept the other(waiting or held) call */
    MIPC_CALL_SS_ACTION_RELEASE_ALL_ACTIVE_AND_ACCEPT_CALL  = 1,
    /* places all active call on hold and accept the other(held or waiting) call */
    MIPC_CALL_SS_ACTION_PLACE_ALL_ACTIVE_CALL_ON_HOLD_AND_ACCEPT_CALL = 2,
    /* Connects two calls and siconnects the subscriber from both calls */
    MIPC_CALL_SS_ACTION_EXPLICIT_CALL_AND_TRANSFER          = 4,
    /* Activate the Completion of Calls to Busy Subscriber Request. (CCBS) */
    MIPC_CALL_SS_ACTION_COMPLETION_CALL_BUSY_SUBSCRIBER     = 5,
    /* change a specific call to on-hold (only the IMS call support this feature) */
    MIPC_CALL_SS_ACTION_HOLD_CALL                           = 131,
    /* change a specific call to active (only the IMS call support this feature) */
    MIPC_CALL_SS_ACTION_RESUME_CALL                         = 132,
};
typedef enum mipc_call_ss_action_const_enum mipc_call_ss_action_const_enum;

enum mipc_call_conf_action_const_enum {
    mipc_call_conf_action_const_NONE = 0,
    /* CALL_CONF_ACTION */
    /* merges the call to the conversation */
    MIPC_CALL_CONF_ACTION_MERGE                             = 0,
    /* adds a call to the conversation */
    MIPC_CALL_CONF_ACTION_ADD_PARTICIPANT                   = 1,
    /* remove a call from the conversation */
    MIPC_CALL_CONF_ACTION_REMOVE_PARTICIPANT                = 2,
    /* split a party from the CS MTPY(conference), for cs only */
    MIPC_CALL_CONF_ACTION_SPLIT                             = 3,
    /* manage 3-way calls, for cdma only */
    MIPC_CALL_CONF_ACTION_CDMA_FLASH                        = 4,
};
typedef enum mipc_call_conf_action_const_enum mipc_call_conf_action_const_enum;

enum mipc_set_gwsd_mode_action_const_enum {
    mipc_set_gwsd_mode_action_const_NONE = 0,
    /* SET_GWSD_MODE_ACTION */
    /* set DSDA-like mode */
    MIPC_SET_GWSD_MODE_ACTION_SET_DSDA_LIKE_MODE            = 1,
    /* set single card GWSD mode(CSFB) */
    MIPC_SET_GWSD_MODE_ACTION_SET_SINGLE_CARD_GWSD_MODE     = 2,
};
typedef enum mipc_set_gwsd_mode_action_const_enum mipc_set_gwsd_mode_action_const_enum;

enum mipc_call_hangup_mode_const_enum {
    mipc_call_hangup_mode_const_NONE = 0,
    /* CALL_HANGUP_MODE */
    /*  */
    MIPC_CALL_HANGUP_MODE_HANGUP                            = 0,
    /*  */
    MIPC_CALL_HANGUP_MODE_HANGUP_ALL                        = 1,
    /*  */
    MIPC_CALL_HANGUP_MODE_FORCE_HANGUP                      = 2,
};
typedef enum mipc_call_hangup_mode_const_enum mipc_call_hangup_mode_const_enum;

enum mipc_call_hangup_cause_const_enum {
    mipc_call_hangup_cause_const_NONE = 0,
    /* CALL_HANGUP_CAUSE */
    MIPC_CALL_HANGUP_CAUSE_USER_HANGUP                      = 0,
    MIPC_CALL_HANGUP_CAUSE_IMS_NO_COVERAGE                  = 1,
    MIPC_CALL_HANGUP_CAUSE_IS_LOW_BATTERY                   = 2,
    MIPC_CALL_HANGUP_CAUSE_IMS_FORWARD                      = 3,
    MIPC_CALL_HANGUP_CAUSE_IMS_SPECIAL_HUNGUP               = 4,
    MIPC_CALL_HANGUP_CAUSE_IMS_607_UNWANTED                 = 5,
    MIPC_CALL_HANGUP_CAUSE_CS_INCOMING_REJECTED_NO_FORWARD  = 6,
};
typedef enum mipc_call_hangup_cause_const_enum mipc_call_hangup_cause_const_enum;

enum mipc_call_answer_mode_const_enum {
    mipc_call_answer_mode_const_NONE = 0,
    /* CALL_ANSWER_MODE */
    /*  */
    MIPC_CALL_ANSWER_MODE_DEFAULT                           = 0,
    /* accepts as audio call */
    MIPC_CALL_ANSWER_MODE_AUDIO_CALL                        = 1,
    /* accepts as one way only video call (Rx) */
    MIPC_CALL_ANSWER_MODE_Rx_VIDEO_CALL                     = 2,
    /* accepts as one way only video call (Tx) */
    MIPC_CALL_ANSWER_MODE_Tx_VIDEO_CALL                     = 3,
};
typedef enum mipc_call_answer_mode_const_enum mipc_call_answer_mode_const_enum;

enum mipc_call_ss_code1_const_enum {
    mipc_call_ss_code1_const_NONE = 0,
    /* CALL_SS_CODE1 */
    /* unconditional call forwarding is active */
    MIPC_CALL_SS_CODE1_UCF_ACTIVE                           = 0,
    /* some of the conditional call forwardings are active */
    MIPC_CALL_SS_CODE1_CCF_ACTIVE                           = 1,
    /* call has been forwarded */
    MIPC_CALL_SS_CODE1_FORWARDED_CALL                       = 2,
    /* call is waiting */
    MIPC_CALL_SS_CODE1_WAITING_CALL                         = 3,
    /* this is a CUG call (also <index> present) */
    MIPC_CALL_SS_CODE1_CUG_CALL                             = 4,
    /* outgoing calls are barred */
    MIPC_CALL_SS_CODE1_OUTGOING_CALLS_ARE_BARRED            = 5,
    /* incoming calls are barred */
    MIPC_CALL_SS_CODE1_INCOMING_CALLS_ARE_BARRED            = 6,
    /* CLIR suppression rejected */
    MIPC_CALL_SS_CODE1_CLIR_SUPPRESSION_REJECTED            = 7,
    /* call has been deflected */
    MIPC_CALL_SS_CODE1_DEFLECTED_CALL                       = 8,
    /* called party is idle for video ringtone */
    MIPC_CALL_SS_CODE1_CALLED_PARTY_IS_IDLE_FOR_VIDEO_RINGTONE = 9,
};
typedef enum mipc_call_ss_code1_const_enum mipc_call_ss_code1_const_enum;

enum mipc_call_ss_code2_const_enum {
    mipc_call_ss_code2_const_NONE = 0,
    /* CALL_SS_CODE2 */
    /* this is a forwarded call (MT call setup) */
    MIPC_CALL_SS_CODE2_FORWARDED_CALL                       = 0,
    /* this is a CUG call (also <index> present) (MT call setup) */
    MIPC_CALL_SS_CODE2_CUG_CALL                             = 1,
    /* call has been put on hold (during a voice call) */
    MIPC_CALL_SS_CODE2_HOLD_CALL                            = 2,
    /* call has been retrieved (during a voice call) */
    MIPC_CALL_SS_CODE2_RETRIEVED_CALL                       = 3,
    /* multiparty call entered (during a voice call) */
    MIPC_CALL_SS_CODE2_MULTIPARTY_CALL                      = 4,
    /* call on hold has been released (this is not a SS notification) (during a voice call) */
    MIPC_CALL_SS_CODE2_HOLD_CALL_HAS_BEEN_RELEASEED         = 5,
    /* forward check SS message received (can be received whenever) */
    MIPC_CALL_SS_CODE2_FORWARD_CHECK_SS_MSG_RECEIVED        = 6,
    /* all is being connected (alerting) with the remote party in alerting state in explicit call transfer operation (during a voice call) */
    MIPC_CALL_SS_CODE2_CONNECTED_CALL_WITH_REMOTE_PARTY_IN_ALERTING = 7,
    /* call has been connected with the other remote party in explicit call transfer operation (also number and subaddress parameters may be present) (during a voice call or MT call setup) */
    MIPC_CALL_SS_CODE2_CONNECTED_CALL_WITH_REMOTE_PARTY_IN_EXPLICIT_CALL_TRANSFER = 8,
    /* this is a deflected call (MT call setup) */
    MIPC_CALL_SS_CODE2_DEFLECTED_CALL                       = 9,
    /* additional incoming call forwarded */
    MIPC_CALL_SS_CODE2_ADDITIONAL_INCOMING_CALL_FORWARDED   = 10,
    /* Call Forwarded */
    MIPC_CALL_SS_CODE2_CALL_FORWARDED                       = 11,
    /* Call Forwarded Unconditional */
    MIPC_CALL_SS_CODE2_CALL_FORWARDED_UNCONDITIONAL         = 12,
    /* Call Forwarded Conditional */
    MIPC_CALL_SS_CODE2_CALL_FORWARDED_CONDITIONAL           = 13,
    /* Call Busy Forwarded */
    MIPC_CALL_SS_CODE2_CALL_BUSY_FORWARDED                  = 14,
    /* Call Forwarded on No Reply */
    MIPC_CALL_SS_CODE2_CALL_FORWARDED_ON_NO_REPLY           = 15,
    /* Call Forwarded on Not Reachable */
    MIPC_CALL_SS_CODE2_CALL_FORWARDED_ON_NOT_REACHABLE      = 16,
};
typedef enum mipc_call_ss_code2_const_enum mipc_call_ss_code2_const_enum;

enum mipc_supplementary_service_type_const_enum {
    mipc_supplementary_service_type_const_NONE = 0,
    /* SUPPLEMENTARY_SERVICE_TYPE */
    MIPC_SUPPLEMENTARY_SERVICE_TYPE_CALL_FORWARDING         = 13,
    MIPC_SUPPLEMENTARY_SERVICE_TYPE_CALLED_PARTY_IS_IDLE_FOR_VIDEO_RINGTONE = 110,
    MIPC_SUPPLEMENTARY_SERVICE_TYPE_OUTGOING_CALL_BARRING   = 256,
    MIPC_SUPPLEMENTARY_SERVICE_TYPE_CALL_FORWARDING_NOT_SHOW_FORWARDTOAST = 257,
    MIPC_SUPPLEMENTARY_SERVICE_TYPE_CALL_WAITING            = 259,
};
typedef enum mipc_supplementary_service_type_const_enum mipc_supplementary_service_type_const_enum;

enum mipc_emergency_call_s1_support_const_enum {
    mipc_emergency_call_s1_support_const_NONE = 0,
    /* EMERGENCY_CALL_S1_SUPPORT */
    MIPC_EMERGENCY_CALL_S1_SUPPORT_S1_MODE_NOT_SUPPORT      = 0,
    MIPC_EMERGENCY_CALL_S1_SUPPORT_S1_MODE_SUPPORT          = 1,
};
typedef enum mipc_emergency_call_s1_support_const_enum mipc_emergency_call_s1_support_const_enum;

enum mipc_emergency_call_rat_const_enum {
    mipc_emergency_call_rat_const_NONE = 0,
    /* EMERGENCY_CALL_RAT */
    MIPC_EMERGENCY_CALL_RAT_GSM                             = 0,
    MIPC_EMERGENCY_CALL_RAT_WCDMA                           = 1,
    MIPC_EMERGENCY_CALL_RAT_TD_SCDMA                        = 2,
    MIPC_EMERGENCY_CALL_RAT_FDD_LTE                         = 3,
    MIPC_EMERGENCY_CALL_RAT_TDD_LTE                         = 4,
};
typedef enum mipc_emergency_call_rat_const_enum mipc_emergency_call_rat_const_enum;

enum mipc_emergency_call_support_emc_const_enum {
    mipc_emergency_call_support_emc_const_NONE = 0,
    /* EMERGENCY_CALL_SUPPORT_EMC */
    /* Current cell does not support emergency service */
    MIPC_EMERGENCY_CALL_SUPPORT_EMC_NOT_SUPPORT             = 0,
    /* Current cell support emergency servicee */
    MIPC_EMERGENCY_CALL_SUPPORT_EMC_SUPPORT                 = 1,
};
typedef enum mipc_emergency_call_support_emc_const_enum mipc_emergency_call_support_emc_const_enum;

enum mipc_emergency_call_emb_iu_supp_const_enum {
    mipc_emergency_call_emb_iu_supp_const_NONE = 0,
    /* EMERGENCY_CALL_EMB_IU_SUPP */
    MIPC_EMERGENCY_CALL_EMB_IU_SUPP_NOT_SUPPORT_LU_MODE_AND_A_GB_MODE = 0,
    MIPC_EMERGENCY_CALL_EMB_IU_SUPP_ONLY_SUPPORT_LU_MODE    = 1,
};
typedef enum mipc_emergency_call_emb_iu_supp_const_enum mipc_emergency_call_emb_iu_supp_const_enum;

enum mipc_emergency_call_ems_5g_supp_const_enum {
    mipc_emergency_call_ems_5g_supp_const_NONE = 0,
    /* EMERGENCY_CALL_EMS_5G_SUPP */
    MIPC_EMERGENCY_CALL_EMS_5G_SUPP_EMC_NOT_SUPPORT         = 0,
    MIPC_EMERGENCY_CALL_EMS_5G_SUPP_EMC_SUPPORT_NR_5GCN_ONLY = 1,
    MIPC_EMERGENCY_CALL_EMS_5G_SUPP_EMC_SUPPORT_EUTRA_5GCN_ONLY  = 2,
    MIPC_EMERGENCY_CALL_EMS_5G_SUPP_EMC_SUPPORT_NR_5GCN_EUTRA_5GCN = 3,
};
typedef enum mipc_emergency_call_ems_5g_supp_const_enum mipc_emergency_call_ems_5g_supp_const_enum;

enum mipc_emergency_call_emf_5g_supp_const_enum {
    mipc_emergency_call_emf_5g_supp_const_NONE = 0,
    /* EMERGENCY_CALL_EMF_5G_SUPP */
    MIPC_EMERGENCY_CALL_EMF_5G_SUPP_EMC_FALLBACK_NOT_SUPPORT = 0,
    MIPC_EMERGENCY_CALL_EMF_5G_SUPP_EMC_FALLBACK_SUPPORT_NR_5GCN_ONLY = 1,
    MIPC_EMERGENCY_CALL_EMF_5G_SUPP_EMC_FALLBACK_SUPPORT_EUTRA_5GCN_ONLY  = 2,
    MIPC_EMERGENCY_CALL_EMF_5G_SUPP_EMC_FALLBACK_SUPPORT_NR_5GCN_EUTRA_5GCN = 3,
};
typedef enum mipc_emergency_call_emf_5g_supp_const_enum mipc_emergency_call_emf_5g_supp_const_enum;

enum mipc_call_uis_info_type_const_enum {
    mipc_call_uis_info_type_const_NONE = 0,
    /* CALL_UIS_INFO_TYPE */
    MIPC_CALL_UIS_INFO_TYPE_BOTTON_CLICKING                 = 1,
};
typedef enum mipc_call_uis_info_type_const_enum mipc_call_uis_info_type_const_enum;

enum mipc_call_uis_info_result_const_enum {
    mipc_call_uis_info_result_const_NONE = 0,
    /* CALL_UIS_INFO_RESULT */
    MIPC_CALL_UIS_INFO_RESULT_SUCCESS                       = 0,
    MIPC_CALL_UIS_INFO_RESULT_FAILURE                       = 1,
};
typedef enum mipc_call_uis_info_result_const_enum mipc_call_uis_info_result_const_enum;

enum mipc_call_uis_info_cause_const_enum {
    mipc_call_uis_info_cause_const_NONE = 0,
    /* CALL_UIS_INFO_CAUSE */
    MIPC_CALL_UIS_INFO_CAUSE_NONE                           = 0,
    MIPC_CALL_UIS_INFO_CAUSE_CALL_NOT_EXIST                 = 1,
    MIPC_CALL_UIS_INFO_CAUSE_DATA_IS_NULL                   = 2,
    MIPC_CALL_UIS_INFO_CAUSE_LACL_OF_MEMORY                 = 3,
    MIPC_CALL_UIS_INFO_CAUSE_SIP_ERROR                      = 4,
};
typedef enum mipc_call_uis_info_cause_const_enum mipc_call_uis_info_cause_const_enum;

enum mipc_call_prefer_set_state_const_enum {
    mipc_call_prefer_set_state_const_NONE = 0,
    /* CALL_PREFER_SET_STATE */
    MIPC_CALL_PREFER_SET_STATE_DATA_PREFER                  = 0,
    MIPC_CALL_PREFER_SET_STATE_CALL_PREFER                  = 1,
};
typedef enum mipc_call_prefer_set_state_const_enum mipc_call_prefer_set_state_const_enum;

enum mipc_call_prefer_set_monitor_mode_const_enum {
    mipc_call_prefer_set_monitor_mode_const_NONE = 0,
    /* CALL_PREFER_SET_MONITOR_MODE */
    /* DO NOT monitor PCH of other SIM when this SIM is in data transfer */
    MIPC_CALL_PREFER_SET_MONITOR_MODE_NOT_MONITOR           = 0,
    /* monitor PCH of other SIM when this SIM in data transfer */
    MIPC_CALL_PREFER_SET_MONITOR_MODE_MONITOR               = 1,
};
typedef enum mipc_call_prefer_set_monitor_mode_const_enum mipc_call_prefer_set_monitor_mode_const_enum;

enum mipc_call_reject_cause_const_enum {
    mipc_call_reject_cause_const_NONE = 0,
    /* CALL_REJECT_CAUSE */
    MIPC_CALL_REJECT_CAUSE_NORMAL                           = 0,
    MIPC_CALL_REJECT_CAUSE_ABNORMAL                         = 1,
    MIPC_CALL_REJECT_CAUSE_NONUMBER                         = 2,
    MIPC_CALL_REJECT_CAUSE_UNREGISTERED                     = 3,
    MIPC_CALL_REJECT_CAUSE_DISCONNECT                       = 4,
    MIPC_CALL_REJECT_CAUSE_BECANCEL                         = 5,
    MIPC_CALL_REJECT_CAUSE_BEREJECT                         = 6,
    MIPC_CALL_REJECT_CAUSE_BEREJECT_380                     = 7,
    MIPC_CALL_REJECT_CAUSE_BEREJECT_380_EMERGENCY_TO_CS     = 8,
    MIPC_CALL_REJECT_CAUSE_BEREJECT_380_EMERGENCY_REREG     = 9,
    MIPC_CALL_REJECT_CAUSE_BEREJECT_480                     = 10,
    MIPC_CALL_REJECT_CAUSE_BEREJECT_503                     = 11,
    MIPC_CALL_REJECT_CAUSE_TX_TIMEOUT                       = 12,
    MIPC_CALL_REJECT_CAUSE_NO_PRIVACY                       = 13,
    MIPC_CALL_REJECT_CAUSE_PRECONDFAIL                      = 14,
    MIPC_CALL_REJECT_CAUSE_SECONDCALL                       = 15,
    MIPC_CALL_REJECT_CAUSE_NOMEDIACONTENT                   = 16,
    MIPC_CALL_REJECT_CAUSE_INVALIDMSG                       = 17,
    MIPC_CALL_REJECT_CAUSE_INVALIDCMD                       = 18,
    MIPC_CALL_REJECT_CAUSE_INVALIDIDX                       = 19,
    MIPC_CALL_REJECT_CAUSE_SRVCC                            = 20,
    MIPC_CALL_REJECT_CAUSE_FACILITY_REJECTED                = 21,
    MIPC_CALL_REJECT_CAUSE_DEDICATED_BEARER_TIMEOUT         = 22,
    MIPC_CALL_REJECT_CAUSE_UA_MAX                           = 23,
    MIPC_CALL_REJECT_CAUSE_UNAVAILABLE_OF_CALLS             = 24,
    MIPC_CALL_REJECT_CAUSE_IMS_CC_CAUSE_MAX                 = 25,
    MIPC_CALL_REJECT_CAUSE_UNKNOWN                          = 65535,
};
typedef enum mipc_call_reject_cause_const_enum mipc_call_reject_cause_const_enum;

enum mipc_sys_thermal_actuator_id_const_enum {
    mipc_sys_thermal_actuator_id_const_NONE = 0,
    /* SYS_THERMAL_ACTUATOR_ID */
    MIPC_SYS_THERMAL_ACTUATOR_ID_UL_THROTTLING              = 1,
    MIPC_SYS_THERMAL_ACTUATOR_ID_TX_POWER                   = 2,
    MIPC_SYS_THERMAL_ACTUATOR_ID_CC_CTRL                    = 3,
    MIPC_SYS_THERMAL_ACTUATOR_ID_HEADSWITCH                 = 4,
    MIPC_SYS_THERMAL_ACTUATOR_ID_RAS                        = 5,
    MIPC_SYS_THERMAL_ACTUATOR_ID_FR2_OFF                    = 6,
    MIPC_SYS_THERMAL_ACTUATOR_ID_FLIGHT_MODE                = 7,
    MIPC_SYS_THERMAL_ACTUATOR_ID_CHARGER                    = 8,
};
typedef enum mipc_sys_thermal_actuator_id_const_enum mipc_sys_thermal_actuator_id_const_enum;

enum mipc_conf_participant_status_const_enum {
    mipc_conf_participant_status_const_NONE = 0,
    /* CONF_PARTICIPANT_STATUS */
    MIPC_CONF_PARTICIPANT_STATUS_PENDING                    = 0,
    MIPC_CONF_PARTICIPANT_STATUS_DIALING_OUT                = 1,
    MIPC_CONF_PARTICIPANT_STATUS_DIALING_IN                 = 2,
    MIPC_CONF_PARTICIPANT_STATUS_ALERTING                   = 3,
    MIPC_CONF_PARTICIPANT_STATUS_ON_HOLD                    = 4,
    MIPC_CONF_PARTICIPANT_STATUS_CONNECTED                  = 5,
    MIPC_CONF_PARTICIPANT_STATUS_DISCONNECTING              = 6,
    MIPC_CONF_PARTICIPANT_STATUS_DISCONNECTED               = 7,
    MIPC_CONF_PARTICIPANT_STATUS_MUTED_VIA_FOCUS            = 8,
    MIPC_CONF_PARTICIPANT_STATUS_CONNECT_FAIL               = 9,
};
typedef enum mipc_conf_participant_status_const_enum mipc_conf_participant_status_const_enum;

enum mipc_sip_direction_const_enum {
    mipc_sip_direction_const_NONE = 0,
    /* SIP_DIRECTION */
    MIPC_SIP_DIRECTION_SEND                                 = 0,
    MIPC_SIP_DIRECTION_RECEIVE                              = 1,
};
typedef enum mipc_sip_direction_const_enum mipc_sip_direction_const_enum;

enum mipc_sip_msg_type_const_enum {
    mipc_sip_msg_type_const_NONE = 0,
    /* SIP_MSG_TYPE */
    MIPC_SIP_MSG_TYPE_REQUEST                               = 0,
    MIPC_SIP_MSG_TYPE_RESPONSE                              = 1,
};
typedef enum mipc_sip_msg_type_const_enum mipc_sip_msg_type_const_enum;

enum mipc_sip_method_const_enum {
    mipc_sip_method_const_NONE = 0,
    /* SIP_METHOD */
    MIPC_SIP_METHOD_INVITE                                  = 1,
    MIPC_SIP_METHOD_REFER                                   = 2,
    MIPC_SIP_METHOD_UPDATE                                  = 3,
    MIPC_SIP_METHOD_CANCEL                                  = 4,
    MIPC_SIP_METHOD_MESSAGE                                 = 5,
    MIPC_SIP_METHOD_ACK                                     = 6,
    MIPC_SIP_METHOD_BYE                                     = 7,
    MIPC_SIP_METHOD_OPTIONS                                 = 8,
    MIPC_SIP_METHOD_SUBSCRIBE                               = 9,
    MIPC_SIP_METHOD_NOTIFY                                  = 10,
    MIPC_SIP_METHOD_PUBLISH                                 = 11,
    MIPC_SIP_METHOD_INFO                                    = 12,
    MIPC_SIP_METHOD_PRACK                                   = 13,
};
typedef enum mipc_sip_method_const_enum mipc_sip_method_const_enum;

enum mipc_ims_event_package_type_const_enum {
    mipc_ims_event_package_type_const_NONE = 0,
    /* IMS_EVENT_PACKAGE_TYPE */
    MIPC_IMS_EVENT_PACKAGE_TYPE_CONFERENCE                  = 1,
    MIPC_IMS_EVENT_PACKAGE_TYPE_DIALOG                      = 2,
    MIPC_IMS_EVENT_PACKAGE_TYPE_MWI                         = 3,
    MIPC_IMS_EVENT_PACKAGE_TYPE_DTMF_GEN                    = 100,
};
typedef enum mipc_ims_event_package_type_const_enum mipc_ims_event_package_type_const_enum;

enum mipc_ecc_info_type_const_enum {
    mipc_ecc_info_type_const_NONE = 0,
    /* ECC_INFO_TYPE */
    MIPC_ECC_INFO_TYPE_HOST                                 = 0,
    MIPC_ECC_INFO_TYPE_SIM                                  = 1,
    MIPC_ECC_INFO_TYPE_MCF                                  = 2,
    MIPC_ECC_INFO_TYPE_NW                                   = 3,
    MIPC_ECC_INFO_TYPE_SPEC                                 = 4,
};
typedef enum mipc_ecc_info_type_const_enum mipc_ecc_info_type_const_enum;

enum mipc_dtmf_mode_const_enum {
    mipc_dtmf_mode_const_NONE = 0,
    /* DTMF_MODE */
    /*  */
    MIPC_DTMF_MODE_START                                    = 0,
    /*  */
    MIPC_DTMF_MODE_STOP                                     = 1,
    /*  */
    MIPC_DTMF_MODE_SINGLE_TONE                              = 2,
    /* this mode is only used in CDMA call */
    MIPC_DTMF_MODE_BURST_TONE                               = 3,
};
typedef enum mipc_dtmf_mode_const_enum mipc_dtmf_mode_const_enum;

enum mipc_call_ecbm_mode_const_enum {
    mipc_call_ecbm_mode_const_NONE = 0,
    /* CALL_ECBM_MODE */
    /* ecbm mode off */
    MIPC_CALL_ECBM_MODE_ECBM_OFF                            = 0,
    /* ecbm mode on */
    MIPC_CALL_ECBM_MODE_ECBM_ON                             = 1,
    /* no ecbm mode */
    MIPC_CALL_ECBM_MODE_NO_ECBM                             = 2,
};
typedef enum mipc_call_ecbm_mode_const_enum mipc_call_ecbm_mode_const_enum;

enum mipc_call_cli_validity_const_enum {
    mipc_call_cli_validity_const_NONE = 0,
    /* CALL_CLI_VALIDITY */
    /* CLI VALID */
    MIPC_CALL_CLI_VALIDITY_CLI_VALID                        = 0,
    /* CLI has been with held by the originator */
    MIPC_CALL_CLI_VALIDITY_CLI_WITHHELD                     = 1,
    /* CLI is not valid due to interworking problems or limitations of originating network */
    MIPC_CALL_CLI_VALIDITY_CLI_INTERWORK                    = 2,
    /* CLI is not valid due to calling party being of type payphone */
    MIPC_CALL_CLI_VALIDITY_CLI_PAYPHONE                     = 3,
    /* CLI is not valid due to other reasons */
    MIPC_CALL_CLI_VALIDITY_CLI_OTHERS                       = 4,
};
typedef enum mipc_call_cli_validity_const_enum mipc_call_cli_validity_const_enum;

enum mipc_call_cni_validity_const_enum {
    mipc_call_cni_validity_const_NONE = 0,
    /* CALL_CNI_VALIDITY */
    /* CNI VALID */
    MIPC_CALL_CNI_VALIDITY_CNI_VALID                        = 0,
    /* CNI has been with held by the originator */
    MIPC_CALL_CNI_VALIDITY_CNI_WITHHELD                     = 1,
    /* CNI is not valid due to interworking problems or limitations of originating network */
    MIPC_CALL_CNI_VALIDITY_CNI_INTERWORK                    = 2,
    /* CNI is not valid due to calling party being of type payphone */
    MIPC_CALL_CNI_VALIDITY_CNI_PAYPHONE                     = 3,
    /* CNI is not valid due to other reasons */
    MIPC_CALL_CNI_VALIDITY_CNI_OTHERS                       = 4,
};
typedef enum mipc_call_cni_validity_const_enum mipc_call_cni_validity_const_enum;

enum mipc_ecall_type_const_enum {
    mipc_ecall_type_const_NONE = 0,
    /* ECALL_TYPE */
    MIPC_ECALL_TYPE_TEST                                    = 0,
    MIPC_ECALL_TYPE_RECOFIG                                 = 1,
    MIPC_ECALL_TYPE_MANUAL                                  = 2,
    MIPC_ECALL_TYPE_AUTO                                    = 3,
};
typedef enum mipc_ecall_type_const_enum mipc_ecall_type_const_enum;

enum mipc_ecall_msd_format_const_enum {
    mipc_ecall_msd_format_const_NONE = 0,
    /* ECALL_MSD_FORMAT */
    MIPC_ECALL_MSD_FORMAT_BINARY                            = 1,
};
typedef enum mipc_ecall_msd_format_const_enum mipc_ecall_msd_format_const_enum;

enum mipc_crss_type_const_enum {
    mipc_crss_type_const_NONE = 0,
    /* CRSS_TYPE */
    /* 3GPP Call Waiting  */
    MIPC_CRSS_TYPE_CRSS_CALL_WAITING                        = 0,
    /* 3GPP Calling line dentification presentation */
    MIPC_CRSS_TYPE_CRSS_CALLING_LINE_ID_PRESET              = 1,
    /* 3GPP Called line identification presentation */
    MIPC_CRSS_TYPE_CRSS_CALLED_LINE_ID_PRESET               = 2,
    /* 3GPP connected line dentification presentation */
    MIPC_CRSS_TYPE_CRSS_CONNECTED_LINE_ID_PRESET            = 3,
    /* 3GPP2 Call Waiting  */
    MIPC_CRSS_TYPE_CDMA_CALL_WAITING                        = 4,
    /* 3GPP2 Calling line dentification presentation */
    MIPC_CRSS_TYPE_CDMA_CALLING_LINE_ID_PRESET              = 5,
};
typedef enum mipc_crss_type_const_enum mipc_crss_type_const_enum;

enum mipc_number_presentation_const_enum {
    mipc_number_presentation_const_NONE = 0,
    /* NUMBER_PRESENTATION */
    /* alowed */
    MIPC_NUMBER_PRESENTATION_ALLOWED                        = 0,
    /* restricted */
    MIPC_NUMBER_PRESENTATION_RESTRICTED                     = 1,
    /* unknown or not specified */
    MIPC_NUMBER_PRESENTATION_UNKNOWN                        = 2,
};
typedef enum mipc_number_presentation_const_enum mipc_number_presentation_const_enum;

enum mipc_number_type_const_enum {
    mipc_number_type_const_NONE = 0,
    /* NUMBER_TYPE */
    /* unknown */
    MIPC_NUMBER_TYPE_UNKNOWN                                = 0,
    /* international call */
    MIPC_NUMBER_TYPE_INTERNATIONAL                          = 1,
    /* national call */
    MIPC_NUMBER_TYPE_NATIONAL                               = 2,
};
typedef enum mipc_number_type_const_enum mipc_number_type_const_enum;

enum mipc_call_ect_type_const_enum {
    mipc_call_ect_type_const_NONE = 0,
    /* CALL_ECT_TYPE */
    /* NVRAM default configuration is used, maybe IMS_BLIND_ECT or IMS_ASSURED_ECT */
    MIPC_CALL_ECT_TYPE_IMS_DEFAULT                          = 0,
    /* triggers IMS explicit call transfer with ECT type blind */
    MIPC_CALL_ECT_TYPE_IMS_BLIND_ECT                        = 1,
    /* triggers IMS explicit call transfer with ECT type assured */
    MIPC_CALL_ECT_TYPE_IMS_ASSURED_ECT                      = 2,
    /* Connects two calls and dsiconnects the subscriber from both calls */
    MIPC_CALL_ECT_TYPE_CONSULTATIVE_ECT                     = 3,
};
typedef enum mipc_call_ect_type_const_enum mipc_call_ect_type_const_enum;

enum mipc_call_cipher_on_status_const_enum {
    mipc_call_cipher_on_status_const_NONE = 0,
    /* CALL_CIPHER_ON_STATUS */
    MIPC_CALL_CIPHER_ON_STATUS_NO_CIPHER                    = 0,
    MIPC_CALL_CIPHER_ON_STATUS_CIPHER                       = 1,
    MIPC_CALL_CIPHER_ON_STATUS_UNKNOWN                      = 255,
};
typedef enum mipc_call_cipher_on_status_const_enum mipc_call_cipher_on_status_const_enum;

enum mipc_call_additional_info_mode_const_enum {
    mipc_call_additional_info_mode_const_NONE = 0,
    /* CALL_ADDITIONAL_INFO_MODE */
    MIPC_CALL_ADDITIONAL_INFO_MODE_ORIGINAL_IMS_CALL        = 1,
    MIPC_CALL_ADDITIONAL_INFO_MODE_CLIENT_API               = 2,
    MIPC_CALL_ADDITIONAL_INFO_MODE_ENRICHED_CALLING         = 3,
};
typedef enum mipc_call_additional_info_mode_const_enum mipc_call_additional_info_mode_const_enum;

enum mipc_call_additional_info_type_const_enum {
    mipc_call_additional_info_type_const_NONE = 0,
    /* CALL_ADDITIONAL_INFO_TYPE */
    MIPC_CALL_ADDITIONAL_INFO_TYPE_HEADER                   = 1,
    MIPC_CALL_ADDITIONAL_INFO_TYPE_LOCATION                 = 2,
};
typedef enum mipc_call_additional_info_type_const_enum mipc_call_additional_info_type_const_enum;

enum mipc_call_peer_rtt_modify_result_const_enum {
    mipc_call_peer_rtt_modify_result_const_NONE = 0,
    /* CALL_PEER_RTT_MODIFY_RESULT */
    MIPC_CALL_PEER_RTT_MODIFY_RESULT_ACCEPT                 = 0,
    MIPC_CALL_PEER_RTT_MODIFY_RESULT_REJECT                 = 1,
};
typedef enum mipc_call_peer_rtt_modify_result_const_enum mipc_call_peer_rtt_modify_result_const_enum;

enum mipc_call_local_rtt_modify_op_const_enum {
    mipc_call_local_rtt_modify_op_const_NONE = 0,
    /* CALL_LOCAL_RTT_MODIFY_OP */
    MIPC_CALL_LOCAL_RTT_MODIFY_OP_DOWNGRADE                 = 0,
    MIPC_CALL_LOCAL_RTT_MODIFY_OP_UPGRADE                   = 1,
};
typedef enum mipc_call_local_rtt_modify_op_const_enum mipc_call_local_rtt_modify_op_const_enum;

enum mipc_call_rtt_mode_op_const_enum {
    mipc_call_rtt_mode_op_const_NONE = 0,
    /* CALL_RTT_MODE_OP */
    /* disable IMS RTT capability */
    MIPC_CALL_RTT_MODE_OP_DISABLE                           = 0,
    /* enable IMS RTT capability with Automatic RTT Operation Mode.  */
    MIPC_CALL_RTT_MODE_OP_AUTOMATIC                         = 1,
    /* enable IMS RTT capability with Upon Request RTT Operation Mode */
    MIPC_CALL_RTT_MODE_OP_UPON_REQUEST                      = 2,
};
typedef enum mipc_call_rtt_mode_op_const_enum mipc_call_rtt_mode_op_const_enum;

enum mipc_call_rtt_audio_type_const_enum {
    mipc_call_rtt_audio_type_const_NONE = 0,
    /* CALL_RTT_AUDIO_TYPE */
    MIPC_CALL_RTT_AUDIO_TYPE_SILENCE                        = 0,
    MIPC_CALL_RTT_AUDIO_TYPE_SPEECH                         = 1,
};
typedef enum mipc_call_rtt_audio_type_const_enum mipc_call_rtt_audio_type_const_enum;

enum mipc_call_rcs_state_const_enum {
    mipc_call_rcs_state_const_NONE = 0,
    /* CALL_RCS_STATE */
    MIPC_CALL_RCS_STATE_DISABLE                             = 0,
    MIPC_CALL_RCS_STATE_ENABLE                              = 1,
    /* RCS needs IMS doing re-registration without RCS feature tag or with temporary RCS feature tag */
    MIPC_CALL_RCS_STATE_RE_REGISTRATION                     = 2,
};
typedef enum mipc_call_rcs_state_const_enum mipc_call_rcs_state_const_enum;

enum mipc_call_rcs_feature_const_enum {
    mipc_call_rcs_feature_const_NONE = 0,
    /* CALL_RCS_FEATURE */
    MIPC_CALL_RCS_FEATURE_NONE                              = 0,
    MIPC_CALL_RCS_FEATURE_SESSION                           = 0x01,
    MIPC_CALL_RCS_FEATURE_FILETRANSFER                      = 0x02,
    MIPC_CALL_RCS_FEATURE_MSG                               = 0x04,
    MIPC_CALL_RCS_FEATURE_LARGEMSG                          = 0x08,
    MIPC_CALL_RCS_FEATURE_GEOPUSH                           = 0x10,
    MIPC_CALL_RCS_FEATURE_GEOPULL                           = 0x20,
    MIPC_CALL_RCS_FEATURE_GEOPULLFT                         = 0x40,
    MIPC_CALL_RCS_FEATURE_IMDN_AGGREGATION                  = 0x80,
    MIPC_CALL_RCS_FEATURE_GEOSMS                            = 0x100,
    MIPC_CALL_RCS_FEATURE_FTHTTP                            = 0x200,
    MIPC_CALL_RCS_FEATURE_CALLCOMPOSER                      = 0x400,
    MIPC_CALL_RCS_FEATURE_CHATBOT                           = 0x800,
    MIPC_CALL_RCS_FEATURE_CHATBOT_SA                        = 0x1000,
    MIPC_CALL_RCS_FEATURE_CHATBOT_VERSION                   = 0x2000,
};
typedef enum mipc_call_rcs_feature_const_enum mipc_call_rcs_feature_const_enum;

enum mipc_call_voice_domain_const_enum {
    mipc_call_voice_domain_const_NONE = 0,
    /* CALL_VOICE_DOMAIN */
    /* CS Voice only */
    MIPC_CALL_VOICE_DOMAIN_CS_ONLY                          = 1,
    /* CS Voice preferred, IMS PS Voice as secondary */
    MIPC_CALL_VOICE_DOMAIN_CS_PREFERRED                     = 2,
    /* IMS PS Voice preferred, CS Voice as secondary */
    MIPC_CALL_VOICE_DOMAIN_PS_PREFERRED                     = 3,
    /* IMS PS Voice only */
    MIPC_CALL_VOICE_DOMAIN_PS_ONLY                          = 4,
};
typedef enum mipc_call_voice_domain_const_enum mipc_call_voice_domain_const_enum;

enum mipc_call_pull_type_const_enum {
    mipc_call_pull_type_const_NONE = 0,
    /* CALL_PULL_TYPE */
    MIPC_CALL_PULL_TYPE_VOICE                               = 0,
    MIPC_CALL_PULL_TYPE_VIDEO                               = 1,
};
typedef enum mipc_call_pull_type_const_enum mipc_call_pull_type_const_enum;

enum mipc_call_tty_mode_const_enum {
    mipc_call_tty_mode_const_NONE = 0,
    /* CALL_TTY_MODE */
    /* Disable TTY call  */
    MIPC_CALL_TTY_MODE_OFF                                  = 0,
    /* Enable TTY call */
    MIPC_CALL_TTY_MODE_FULL                                 = 1,
    /* Enable TTY call with HCO (Hearing Carry-Over) */
    MIPC_CALL_TTY_MODE_HCO                                  = 2,
    /* Enable TTY call with VCO (Voice Carry-Over) */
    MIPC_CALL_TTY_MODE_VCO                                  = 3,
};
typedef enum mipc_call_tty_mode_const_enum mipc_call_tty_mode_const_enum;

enum mipc_call_ims_call_mode_const_enum {
    mipc_call_ims_call_mode_const_NONE = 0,
    /* CALL_IMS_CALL_MODE */
    /* original IMS call mode  */
    MIPC_CALL_IMS_CALL_MODE_ORIGINAL_IMS                    = 1,
    /* Client API call mode */
    MIPC_CALL_IMS_CALL_MODE_CLIENT_API                      = 2,
};
typedef enum mipc_call_ims_call_mode_const_enum mipc_call_ims_call_mode_const_enum;

enum mipc_phb_ef_file_type_const_enum {
    mipc_phb_ef_file_type_const_NONE = 0,
    /* PHB_EF_FILE_TYPE */
    /* EF_ANR */
    MIPC_PHB_EF_FILE_TYPE_EF_ANR                            = 0,
    /* CNI has been with held by the originator */
    MIPC_PHB_EF_FILE_TYPE_EF_EMAIL                          = 1,
    /* EF_EMAIL */
    MIPC_PHB_EF_FILE_TYPE_EF_SNE                            = 2,
    /* EF_AAS */
    MIPC_PHB_EF_FILE_TYPE_EF_AAS                            = 3,
    /* EF_GAS */
    MIPC_PHB_EF_FILE_TYPE_EF_GAS                            = 4,
    /* EF_GRP */
    MIPC_PHB_EF_FILE_TYPE_EF_GRP                            = 5,
};
typedef enum mipc_phb_ef_file_type_const_enum mipc_phb_ef_file_type_const_enum;

enum mipc_phb_encode_method_const_enum {
    mipc_phb_encode_method_const_NONE = 0,
    /* PHB_ENCODE_METHOD */
    MIPC_PHB_ENCODE_METHOD_ENCODE_IRA                       = 0,
    MIPC_PHB_ENCODE_METHOD_ENCODE_UCS2                      = 1,
    MIPC_PHB_ENCODE_METHOD_ENCODE_UCS2_81                   = 2,
    MIPC_PHB_ENCODE_METHOD_ENCODE_UCS2_82                   = 3,
    MIPC_PHB_ENCODE_METHOD_ENCODE_UCS2_GSM7BIT              = 4,
    MIPC_PHB_ENCODE_METHOD_ENCODE_UNKNOWN                   = 5,
};
typedef enum mipc_phb_encode_method_const_enum mipc_phb_encode_method_const_enum;

enum mipc_phb_stroage_type_const_enum {
    mipc_phb_stroage_type_const_NONE = 0,
    /* PHB_STROAGE_TYPE */
    /* MT phonebook */
    MIPC_PHB_STROAGE_TYPE_ME                                = 0,
    /* SIM/UICC phonebook */
    MIPC_PHB_STROAGE_TYPE_SM                                = 1,
    /* last-dialling phonebook */
    MIPC_PHB_STROAGE_TYPE_LD                                = 2,
    /* MT missed calls list */
    MIPC_PHB_STROAGE_TYPE_MC                                = 3,
    /* MT received calls list */
    MIPC_PHB_STROAGE_TYPE_RC                                = 4,
    /* MT dialled call list */
    MIPC_PHB_STROAGE_TYPE_DC                                = 5,
    /* SIM/UICC fixdialling-phonebook */
    MIPC_PHB_STROAGE_TYPE_FD                                = 6,
    /* SIMown numbers list. */
    MIPC_PHB_STROAGE_TYPE_ON                                = 7,
};
typedef enum mipc_phb_stroage_type_const_enum mipc_phb_stroage_type_const_enum;

enum mipc_result_const_enum {
    mipc_result_const_NONE = 0,
    /* RESULT */
    /* The operation succeeded */
    MIPC_RESULT_SUCCESS                                     = 0,
    /* The operation failed because the device is busy. In the absence of any explicit information from the function to clear this condition, the host can use subsequent actions by the function (e.g., notifications or command completions) as a hint to retry the failed operation. */
    MIPC_RESULT_BUSY                                        = 1,
    /* The operation failed (a generic failure). */
    MIPC_RESULT_FAILURE                                     = 2,
    /* The operation failed because the SIM card was not fully inserted in to the device. */
    MIPC_RESULT_SIM_NOT_INSERTED                            = 3,
    /* The operation failed because the SIM card is bad and cannot be used any further. */
    MIPC_RESULT_BAD_SIM                                     = 4,
    /* The operation failed because a PIN must be entered to proceed. */
    MIPC_RESULT_PIN_REQUIRED                                = 5,
    /* The operation failed because the PIN is disabled. */
    MIPC_RESULT_PIN_DISABLED                                = 6,
    /* The operation failed because the device is not registered with any network. */
    MIPC_RESULT_NOT_REGISTERED                              = 7,
    /* The operation failed because no network providers could be found. */
    MIPC_RESULT_PROVIDERS_NOT_FOUND                         = 8,
    /* The operation failed because the device does not support the operation. */
    MIPC_RESULT_NO_DEVICE_SUPPORT                           = 9,
    /* The operation failed because the service provider is not currently visible. */
    MIPC_RESULT_PROVIDER_NOT_VISIBLE                        = 10,
    /* The operation failed because the requested data-class was not available. */
    MIPC_RESULT_DATA_CLASS_NOT_AVAILABLE                    = 11,
    /* The operation failed because the packet service is detached. */
    MIPC_RESULT_PACKET_SERVICE_DETACHED                     = 12,
    /* The operation failed because the maximum number of activated contexts has been reached. */
    MIPC_RESULT_MAX_ACTIVATED_CONTEXTS                      = 13,
    /* The operation failed because the device is in the process of initializing. Retry the operation after the ReadyState of the device changes to MBIMSubscriberReadyStateInitialized. */
    MIPC_RESULT_NOT_INITIALIZED                             = 14,
    /* The operation failed because a voice call is in progress. */
    MIPC_RESULT_VOICE_CALL_IN_PROGRESS                      = 15,
    /* The operation failed because the context is not activated. */
    MIPC_RESULT_CONTEXT_NOT_ACTIVATED                       = 16,
    /* The operation failed because service is not activated. */
    MIPC_RESULT_SERVICE_NOT_ACTIVATED                       = 17,
    /* The operation failed because the access string is invalid. */
    MIPC_RESULT_INVALID_ACCESS_STRING                       = 18,
    /* The operation failed because the username and/or password supplied are invalid. */
    MIPC_RESULT_INVALID_USERID_PASSWORD                     = 19,
    /* The operation failed because the radio is currently powered off. */
    MIPC_RESULT_RADIO_POWER_OFF                             = 20,
    /* The operation failed because of invalid parameters. */
    MIPC_RESULT_INVALID_PARAMETERS                          = 21,
    /* The operation failed because of a read failure. */
    MIPC_RESULT_READ_FAILURE                                = 22,
    /* The operation failed because of a write failure. */
    MIPC_RESULT_WRITE_FAILURE                               = 23,
    /* Reserved. */
    MIPC_RESULT_Reserved_24                                 = 24,
    /* The phonebook operation failed because there is no phone book. */
    MIPC_RESULT_NO_PHONEBOOK                                = 25,
    /* A parameter with dynamic size is larger than the function can handle */
    MIPC_RESULT_PARAMETER_TOO_LONG                          = 26,
    /* The SIM Toolkit application on the SIM card is busy and the command could not be processed */
    MIPC_RESULT_STK_BUSY                                    = 27,
    /* The operation failed because the operation is not allowed. */
    MIPC_RESULT_OPERATION_NOT_ALLOWED                       = 28,
    /* The phonebook or sms operation failed because the because of device or SIM memory failure. */
    MIPC_RESULT_MEMORY_FAILURE                              = 29,
    /* The phonebook or sms operation failed because of an invalid memory index. */
    MIPC_RESULT_INVALID_MEMORY_INDEX                        = 30,
    /* The phonebook or sms operation failed because the device or SIM memory is full. */
    MIPC_RESULT_MEMORY_FULL                                 = 31,
    /* The phonebook or sms operation failed because the filter type is not supported. */
    MIPC_RESULT_FILTER_NOT_SUPPORTED                        = 32,
    /* Attempt to open a device service failed because the number of opened streams has reached the device service instance limit for this service. */
    MIPC_RESULT_DSS_INSTANCE_LIMIT                          = 33,
    /* The device service operation attempted is invalid. */
    MIPC_RESULT_INVALID_DEVICE_SERVICE_OPERATION            = 34,
    /* The device sets this error on an AKA or AKAPrime challenge response when the AKA or AKAPrime challenge sent has incorrect AUTN. */
    MIPC_RESULT_AUTH_INCORRECT_AUTN                         = 35,
    /* The device sets this error on a an AKA or AKAPrime challenge response when the AKA or AKAPrime challenge sent has synchronization failure. When this error code is returned the AUTS field would be set. */
    MIPC_RESULT_AUTH_SYNC_FAILURE                           = 36,
    /* The device sets this error on an AKAPrime challenge response when the AKAPrime challenge sent does not have the AMF bit set to 1. */
    MIPC_RESULT_AUTH_AMF_NOT_SET                            = 37,
    /* The operation failed because it could not support the type of context identified by ContextType. */
    MIPC_RESULT_CONTEXT_NOT_SUPPORTED                       = 38,
    /* The operation failed because sim is missing resource(ex. not enough memory space) . */
    MIPC_RESULT_MISSING_RESOURCE                            = 39,
    /* The operation failed because not found . */
    MIPC_RESULT_NOT_FOUND                                   = 40,
    /* The operation failed because PHB FDN is blocked. */
    MIPC_RESULT_FDN_BLOCKED                                 = 41,
    /* The SMS operation failed because the service center address is either invalid or unknown. */
    MIPC_RESULT_SMS_UNKNOWN_SMSC_ADDRESS                    = 100,
    /* The SMS operation failed because of a network timeout. */
    MIPC_RESULT_SMS_NETWORK_TIMEOUT                         = 101,
    /* The SMS operation failed because the SMS language is not supported.This applies to CDMA based devices only. */
    MIPC_RESULT_SMS_LANG_NOT_SUPPORTED                      = 102,
    /* The SMS operation failed because the SMS encoding is not supported. This applies to CDMA based device only. */
    MIPC_RESULT_SMS_ENCODING_NOT_SUPPORTED                  = 103,
    /* The SMS operation failed because the SMS format is not supported. */
    MIPC_RESULT_SMS_FORMAT_NOT_SUPPORTED                    = 104,
    /* The  operation failed because the operation is not supported. */
    MIPC_RESULT_OPERATION_NOT_SUPPORTED                     = 105,
    /* The  operation failed because of not found. */
    MIPC_RESULT_ERROR_NOT_FOUND                             = 106,
    /* The  operation failed and no reason given. */
    MIPC_RESULT_ERROR_UNKOWN                                = 107,
    /*  */
    MIPC_RESULT_COMMON_END                                  = 0x3FFFF,
    /* CAT module extension result begin */
    MIPC_RESULT_CAT_EXT_BEGIN                               = 0x00080000,
    /* CAT module extension result end */
    MIPC_RESULT_CAT_EXT_END                                 = 0x000BFFFF,
    /* CC module extension result begin */
    MIPC_RESULT_CC_EXT_BEGIN                                = 0x000C0000,
    /* this call id is force hangup before */
    MIPC_RESULT_CC_CALL_FORCE_RELEASED_BEFORE               = 0x000C0001,
    /* CC module extension result end */
    MIPC_RESULT_CC_EXT_END                                  = 0x000FFFFF,
    /* NW module extension result begin */
    MIPC_RESULT_NW_EXT_BEGIN                                = 0x00100000,
    /* NW module extension result end */
    MIPC_RESULT_NW_EXT_END                                  = 0x0013FFFF,
    /* PDN module extension result begin */
    MIPC_RESULT_PDN_EXT_BEGIN                               = 0x00140000,
    /* PDN module network error begin */
    MIPC_RESULT_PDN_EXT_NETWORK_ERROR_BEGIN                 = 0x00140000,
    /* PDN module cme error begin */
    MIPC_RESULT_PDN_EXT_CME_ERROR_BEGIN                     = 0x00140064,
    /* PDN module cme error end */
    MIPC_RESULT_PDN_EXT_CME_ERROR_END                       = 0x001400C8,
    /* PDN module network SM error cause begin */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_BEGIN              = 0x00140C00,
    /* there is no such cause in SM spec, just for default */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_EMPTY              = 0x00140C01,
    /* OPERATOR DETERMINED BARRING as spec */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_OPERATOR_DETERMINED_BARRING = 0x00140C08,
    /* LLC_SND_FAILURE */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_LLC_SND_FAILURE    = 0x00140C19,
    /* INSUFF_RESOURCE */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_INSUFF_RESOURCE    = 0x00140C1A,
    /* UNKNOWN_APN */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_UNKNOWN_APN        = 0x00140C1B,
    /* UNKNOWN_PDP_ADDR_OR_TYPE */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_UNKNOWN_PDP_ADDR_OR_TYPE = 0x00140C1C,
    /* AUTHENTICATION_FAILURE */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_AUTHENTICATION_FAILURE = 0x00140C1D,
    /* ACTIVATION_REJ_GGSN */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_ACTIVATION_REJ_GGSN = 0x00140C1E,
    /* ACTIVATION_REJ_UNSPECIFIED */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_ACTIVATION_REJ_UNSPECIFIED = 0x00140C1F,
    /* UNSUPPORTED_SERVICE_OPTION */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_UNSUPPORTED_SERVICE_OPTION = 0x00140C20,
    /* UNSUBSCRIBED_SERVICE_OPTION */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_UNSUBSCRIBED_SERVICE_OPTION = 0x00140C21,
    /* SERVICE_OPTION_TEMPORARILY_OUT_OF_ORDER */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_SERVICE_OPTION_TEMPORARILY_OUT_OF_ORDER = 0x00140C22,
    /* PTI_ALREADY_USED */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_PTI_ALREADY_USED   = 0x00140C23,
    /* REGULAR_DEACTIVATION */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_REGULAR_DEACTIVATION = 0x00140C24,
    /* QOS_NOT_ACCEPTED */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_QOS_NOT_ACCEPTED   = 0x00140C25,
    /* NETWORK_FAIL */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_NETWORK_FAIL       = 0x00140C26,
    /* REACTIVATION_REQD */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_REACTIVATION_REQD  = 0x00140C27,
    /* UNSUPPORTED_NW_CONTEXT_ACTIVATION */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_UNSUPPORTED_NW_CONTEXT_ACTIVATION = 0x00140C28,
    /* SEMANTIC_ERROR_IN_TFT_OP */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_SEMANTIC_ERROR_IN_TFT_OP = 0x00140C29,
    /* SYNTACTICAL_ERROR_IN_TFT_OP */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_SYNTACTICAL_ERROR_IN_TFT_OP = 0x00140C2A,
    /* UNKNOWN_PDP_CONTEXT */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_UNKNOWN_PDP_CONTEXT = 0x00140C2B,
    /* SEMANTIC_ERROR_IN_PACKET_FILTER */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_SEMANTIC_ERROR_IN_PACKET_FILTER = 0x00140C2C,
    /* SYNTAX_ERROR_IN_PACKET_FILTER */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_SYNTAX_ERROR_IN_PACKET_FILTER = 0x00140C2D,
    /* PDP_CONTEXT_WO_TFT_ALREADY_ACT */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_PDP_CONTEXT_WO_TFT_ALREADY_ACT = 0x00140C2E,
    /* PTI_MISMATCH */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_PTI_MISMATCH       = 0x00140C2F,
    /* ACTIVATION_REJ_BCM_VIOLATION */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_ACTIVATION_REJ_BCM_VIOLATION = 0x00140C30,
    /* LAST_PDN_DISC_NOT_ALLOWED */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_LAST_PDN_DISC_NOT_ALLOWED = 0x00140C31,
    /* PDP_TYPE_IPV4_ONLY_ALLOWED */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_PDP_TYPE_IPV4_ONLY_ALLOWED = 0x00140C32,
    /* PDP_TYPE_IPV6_ONLY_ALLOWED */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_PDP_TYPE_IPV6_ONLY_ALLOWED = 0x00140C33,
    /* SINGLE_ADDR_BEARERS_ONLY_ALLOWED */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_SINGLE_ADDR_BEARERS_ONLY_ALLOWED = 0x00140C34,
    /* ESM_INFORMATION_NOT_RECEIVED */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_ESM_INFORMATION_NOT_RECEIVED = 0x00140C35,
    /* PDN_CONNENCTION_NOT_EXIST */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_PDN_CONNENCTION_NOT_EXIST = 0x00140C36,
    /* MULTIPLE_PDN_APN_NOT_ALLOWED */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_MULTIPLE_PDN_APN_NOT_ALLOWED = 0x00140C37,
    /* COLLISION_WITH_NW_INITIATED_REQ */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_COLLISION_WITH_NW_INITIATED_REQ = 0x00140C38,
    /* UNSUPPORTED_QCI_VALUE */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_UNSUPPORTED_QCI_VALUE = 0x00140C3B,
    /* MAXIMUM_NUM_OF_PDP_CONTEXTS_REACHED */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_MAXIMUM_NUM_OF_PDP_CONTEXTS_REACHED = 0x00140C41,
    /* REQUESTED_APN_NOT_SUPPORTED_IN_CURRENT_RAT_AND_PLMN_COMBINATION */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_REQUESTED_APN_NOT_SUPPORTED_IN_CURRENT_RAT_AND_PLMN_COMBINATION = 0x00140C42,
    /* INVALID_TI */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_INVALID_TI         = 0x00140C51,
    /* SM_SEMANTICALLY_INCORRECT_MSG */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_SM_SEMANTICALLY_INCORRECT_MSG = 0x00140C5F,
    /* INVALID_MAND_INFO */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_INVALID_MAND_INFO  = 0x00140C60,
    /* SM_MSG_TYPE_NON_EXISTENT_OR_NOT_IMPLEMENTED */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_SM_MSG_TYPE_NON_EXISTENT_OR_NOT_IMPLEMENTED = 0x00140C61,
    /* SM_MSG_TYPE_NOT_COMPATIBLE_WITH_PROTOCOL_STATE */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_SM_MSG_TYPE_NOT_COMPATIBLE_WITH_PROTOCOL_STATE = 0x00140C62,
    /* IE_NON_EXISTENCE_OR_NOT_IMPLEMENTED */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_IE_NON_EXISTENCE_OR_NOT_IMPLEMENTED = 0x00140C63,
    /* CONDITIONAL_IE_ERROR */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_CONDITIONAL_IE_ERROR = 0x00140C64,
    /* SM_MSG_NOT_COMPATIBLE_WITH_PROTOCOL_STATE */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_SM_MSG_NOT_COMPATIBLE_WITH_PROTOCOL_STATE = 0x00140C65,
    /* SM_PROTOCOL_ERROR_UNSPECIFIED */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_SM_PROTOCOL_ERROR_UNSPECIFIED = 0x00140C6F,
    /* APN_RESTRICTION_VALUE_INCOMPATIBLE_WITH_ACTIVE_PDP_CTX */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_APN_RESTRICTION_VALUE_INCOMPATIBLE_WITH_ACTIVE_PDP_CTX = 0x00140C70,
    /* PDN module network SM error cause end */
    MIPC_RESULT_PDN_EXT_NETWORK_SM_CAUSE_END                = 0x00140C71,
    /* PDN module network ESM error cause begin */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_BEGIN             = 0x00140D00,
    /* there is no spec,default value */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_NO_CAUSE          = 0x00140D01,
    /* ESM_OPERATOR_DETERMINED_BARRING */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_OPERATOR_DETERMINED_BARRING = 0x00140D08,
    /* ESM_INSUFFICIENT_RESOURCES */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_INSUFFICIENT_RESOURCES = 0x00140D1A,
    /* ESM_UNKNOWN_OR_MISSING_APN */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_UNKNOWN_OR_MISSING_APN = 0x00140D1B,
    /* ESM_UNKNOWN_PDN_TYPE */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_UNKNOWN_PDN_TYPE  = 0x00140D1C,
    /* USER_AUTH_FAILED */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_USER_AUTH_FAILED  = 0x00140D1D,
    /* REQUEST_REJECTED_BY_SGW_OR_PDNGW */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_REQUEST_REJECTED_BY_SGW_OR_PDNGW  = 0x00140D1E,
    /* REQUEST_REJECTED_UNSPECIFIED */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_REQUEST_REJECTED_UNSPECIFIED = 0x00140D1F,
    /* SERVICE_OPT_NOT_SUPPORTED */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_SERVICE_OPT_NOT_SUPPORTED = 0x00140D20,
    /* REQ_SERVICE_NOT_SUBSCRIBED */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_REQ_SERVICE_NOT_SUBSCRIBED = 0x00140D21,
    /* ESM_SERVICE_TEMP_OUT_OF_ORDER */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_SERVICE_TEMP_OUT_OF_ORDER = 0x00140D22,
    /* PTI_ALREADY_USED */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_PTI_ALREADY_USED  = 0x00140D23,
    /* REGULAR_DEACTIVATION */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_REGULAR_DEACTIVATION = 0x00140D24,
    /* EPS_QOS_NOT_ACCEPTED */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_EPS_QOS_NOT_ACCEPTED = 0x00140D25,
    /* NETWORK_FAILURE */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_NETWORK_FAILURE   = 0x00140D26,
    /* REACTIVATION_REQUESTED */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_REACTIVATION_REQUESTED = 0x00140D27,
    /* SEMANTIC_ERROR_IN_TFT */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_SEMANTIC_ERROR_IN_TFT = 0x00140D29,
    /* SYNTACTIC_ERROR_IN_TFT  */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_SYNTACTIC_ERROR_IN_TFT = 0x00140D2A,
    /* INVALID_EPS_BEARER_IDENTITY  */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_INVALID_EPS_BEARER_IDENTITY = 0x00140D2B,
    /* SEMANTIC_ERROR_IN_PACKET_FILTERS  */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_SEMANTIC_ERROR_IN_PACKET_FILTERS = 0x00140D2C,
    /* SYNTACTIC_ERROR_IN_PACKET_FILTERS  */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_SYNTACTIC_ERROR_IN_PACKET_FILTERS = 0x00140D2D,
    /* EPSB_CTXT_WITHOUT_TFT_ACTIVATED  */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_EPSB_CTXT_WITHOUT_TFT_ACTIVATED = 0x00140D2E,
    /* PTI_MISMATCH */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_PTI_MISMATCH      = 0x00140D2F,
    /* LAST_PDN_DISC_NOT_ALLOWED */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_LAST_PDN_DISC_NOT_ALLOWED = 0x00140D31,
    /* PDN_TYPE_IPV4_ONLY_ALLOWED */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_PDN_TYPE_IPV4_ONLY_ALLOWED = 0x00140D32,
    /* PDN_TYPE_IPV6_ONLY_ALLOWED */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_PDN_TYPE_IPV6_ONLY_ALLOWED = 0x00140D33,
    /* SINGLE_ADDRESS_ONLY_ALLOWED */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_SINGLE_ADDRESS_ONLY_ALLOWED = 0x00140D34,
    /* ESM_INFORMATION_NOT_RECEIVED */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_ESM_INFORMATION_NOT_RECEIVED = 0x00140D35,
    /* PDN_CONNENCTION_NOT_EXIST */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_PDN_CONNENCTION_NOT_EXIST = 0x00140D36,
    /* MULTIPLE_PDN_APN_NOT_ALLOWED */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_MULTIPLE_PDN_APN_NOT_ALLOWED = 0x00140D37,
    /* COLLISION_WITH_NW_INIT_REQUEST */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_COLLISION_WITH_NW_INIT_REQUESTD = 0x00140D38,
    /* UNSUPPORTED_QCI_VALUE */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_UNSUPPORTED_QCI_VALUE = 0x00140D3B,
    /* MAXIMUM_NUM_OF_EPS_BEARERS_REACHED */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_MAXIMUM_NUM_OF_EPS_BEARERS_REACHED = 0x00140D41,
    /* ESM_REQUESTED_APN_NOT_SUPPORTED_IN_CURRENT_RAT_AND_PLMN_COMBINATION */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_ESM_REQUESTED_APN_NOT_SUPPORTED_IN_CURRENT_RAT_AND_PLMN_COMBINATION = 0x00140D42,
    /* INVALID_PTI_VALUE */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_INVALID_PTI_VALUE = 0x00140D51,
    /* SEMANTIC_INCORRECT_MSG */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_SEMANTIC_INCORRECT_MSG = 0x00140D5F,
    /* INVALID_MANDATORY_IE */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_INVALID_MANDATORY_IE = 0x00140D60,
    /* MSG_TYPE_NON_EXISTENT */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_MSG_TYPE_NON_EXISTENT = 0x00140D61,
    /* MSG_TYPE_NOT_COMPATIBLE_STATE */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_MSG_TYPE_NOT_COMPATIBLE_STATE = 0x00140D62,
    /* IE_NON_EXISTENT_NOT_IMPLEMENTED */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_IE_NON_EXISTENT_NOT_IMPLEMENTED = 0x00140D63,
    /* CONDITIONAL_IE_ERROR */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_CONDITIONAL_IE_ERROR = 0x00140D64,
    /* MSG_NOT_COMPATIBLE_STATE */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_MSG_NOT_COMPATIBLE_STATE = 0x00140D65,
    /* PROTOCOL_ERROR_UNSPECIFIED */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_PROTOCOL_ERROR_UNSPECIFIED = 0x00140D6F,
    /* APN_RESTRICT_VALUE_INCOMPATIBLE  */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_APN_RESTRICT_VALUE_INCOMPATIBLE  = 0x00140D70,
    /* PDN module network ESM error cause begin */
    MIPC_RESULT_PDN_EXT_NETWORK_ESM_CAUSE_END               = 0x00140D71,
    /* PDN module network PAM error cause begin */
    MIPC_RESULT_PDN_EXT_NETWORK_PAM_CAUSE_BEGIN             = 0x00141200,
    /* PDN module network PAM error cause end */
    MIPC_RESULT_PDN_EXT_NETWORK_PAM_CAUSE_END               = 0x001412FF,
    /* PDN module network 5GSM error cause begin */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_BEGIN            = 0x00141A00,
    /* default value, there is no spec */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_NO_CAUSE         = 0x00141A01,
    /* OPERATOR_DETERMINED_BARRING */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_OPERATOR_DETERMINED_BARRING = 0x00141A08,
    /* INSUFFICIENT_RESOURCES */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_INSUFFICIENT_RESOURCES = 0x00141A1A,
    /* MISSING_OR_UNKNOWN_DNN */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_MISSING_OR_UNKNOWN_DNN = 0x00141A1B,
    /* UNKNOWN_PDU_SESSION_TYPE */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_UNKNOWN_PDU_SESSION_TYPE = 0x00141A1C,
    /* USER_AUTH_FAILED */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_USER_AUTH_FAILED = 0x00141A1D,
    /* REQUEST_REJECTED_BY_SGW_OR_PDNGW */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_REQUEST_REJECTED_BY_SGW_OR_PDNGW = 0x00141A1E,
    /* REQUEST_REJECTED_UNSPECIFIED */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_REQUEST_REJECTED_UNSPECIFIED = 0x00141A1F,
    /* SERVICE_OPT_NOT_SUPPORTED */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_SERVICE_OPT_NOT_SUPPORTED = 0x00141A20,
    /* REQ_SERVICE_NOT_SUBSCRIBED */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_REQ_SERVICE_NOT_SUBSCRIBED = 0x00141A21,
    /* SERVICE_OPT_TEMP_OUT_OF_ORDER */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_SERVICE_OPT_TEMP_OUT_OF_ORDER = 0x00141A22,
    /* PTI_ALREADY_USED */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_PTI_ALREADY_USED = 0x00141A23,
    /* REGULAR_DEACTIVATION */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_REGULAR_DEACTIVATION = 0x00141A24,
    /* EPS_QOS_NOT_ACCEPTED */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_EPS_QOS_NOT_ACCEPTED = 0x00141A25,
    /* NETWORK_FAILURE */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_NETWORK_FAILURE  = 0x00141A26,
    /* REACTIVATION_REQUESTED */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_REACTIVATION_REQUESTED = 0x00141A27,
    /* SEMANTIC_ERROR_IN_TFT */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_SEMANTIC_ERROR_IN_TFT = 0x00141A29,
    /* SYNTACTIC_ERROR_IN_TFT */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_SYNTACTIC_ERROR_IN_TFT = 0x00141A2A,
    /* INVALID_PDU_SESSION_IDENTITY */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_INVALID_PDU_SESSION_IDENTITY = 0x00141A2B,
    /* SEMANTIC_ERROR_IN_PACKET_FILTERS */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_SEMANTIC_ERROR_IN_PACKET_FILTERS = 0x00141A2C,
    /* SYNTACTIC_ERROR_IN_PACKET_FILTERS */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_SYNTACTIC_ERROR_IN_PACKET_FILTERS = 0x00141A2D,
    /* OUT_OF_LADN_SERVICE_AREA */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_OUT_OF_LADN_SERVICE_AREA = 0x00141A2E,
    /* PTI_MISMATCH */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_PTI_MISMATCH     = 0x00141A2F,
    /* LAST_PDN_DISC_NOT_ALLOWED */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_LAST_PDN_DISC_NOT_ALLOWED = 0x00141A31,
    /* PDU_SESSION_TYPE_IPV4_ONLY_ALLOWED */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_PDU_SESSION_TYPE_IPV4_ONLY_ALLOWED = 0x00141A32,
    /* PDU_SESSION_TYPE_IPV4_ONLY_ALLOWED */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_PDU_SESSION_TYPE_IPV6_ONLY_ALLOWED = 0x00141A33,
    /* SINGLE_ADDRESS_ONLY_ALLOWED */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_SINGLE_ADDRESS_ONLY_ALLOWED = 0x00141A34,
    /* PDU_SESSION_NOT_EXIST */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_PDU_SESSION_NOT_EXIST = 0x00141A36,
    /* MULTIPLE_PDN_APN_NOT_ALLOWED */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_MULTIPLE_PDN_APN_NOT_ALLOWED = 0x00141A37,
    /* COLLISION_WITH_NW_INIT_REQUEST */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_COLLISION_WITH_NW_INIT_REQUEST = 0x00141A38,
    /* UNSUPPORTED_QCI_VALUE */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_UNSUPPORTED_QCI_VALUE = 0x00141A3B,
    /* MAXIMUM_NUM_OF_EPS_BEARERS_REACHED */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_MAXIMUM_NUM_OF_EPS_BEARERS_REACHED = 0x00141A41,
    /* REQUESTED_APN_NOT_SUPPORTED_IN_CURRENT_RAT_AND_PLMN_COMBINATION */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_REQUESTED_APN_NOT_SUPPORTED_IN_CURRENT_RAT_AND_PLMN_COMBINATION = 0x00141A42,
    /* INSUFFICIENT_RESOURCES_FOR_SPECIFIC_SLICE_AND_DNN */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_INSUFFICIENT_RESOURCES_FOR_SPECIFIC_SLICE_AND_DNN = 0x00141A43,
    /* NOT_SUPPORTED_SSC_MODE */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_NOT_SUPPORTED_SSC_MODE = 0x00141A44,
    /* NOT_SUPPORTED_SSC_MODE */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_INSUFFICIENT_RESOURCES_FOR_SPECIFIC_SLICE = 0x00141A45,
    /* MISSING_OR_UNKNOWN_DNN_IN_A_SLICE */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_MISSING_OR_UNKNOWN_DNN_IN_A_SLICE = 0x00141A46,
    /* INVALID_PTI_VALUE */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_INVALID_PTI_VALUE = 0x00141A51,
    /* MAX_DATA_RATE_PER_UE_FOR_UPLANE_INTEGRITY_PROTECTION_IS_TOO_LOW */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_MAX_DATA_RATE_PER_UE_FOR_UPLANE_INTEGRITY_PROTECTION_IS_TOO_LOW = 0x00141A52,
    /* SEMANTIC_ERROR_IN_QOS_OPERATION */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_SEMANTIC_ERROR_IN_QOS_OPERATION = 0x00141A53,
    /* SYNTACTIC_ERROR_IN_QOS_OPERATION */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_SYNTACTIC_ERROR_IN_QOS_OPERATION = 0x00141A54,
    /* INVALID_MAPPED_EPS_BEARER_IDENTITY */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_INVALID_MAPPED_EPS_BEARER_IDENTITY = 0x00141A55,
    /* SEMANTICLLY_INCORRECT_MSG */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_SEMANTICLLY_INCORRECT_MSG = 0x00141A5F,
    /* INVALID_MANDATORY_IE */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_INVALID_MANDATORY_IE = 0x00141A60,
    /* MSG_TYPE_NON_EXISTENT_OR_NOT_IMPLEMENT */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_MSG_TYPE_NON_EXISTENT_OR_NOT_IMPLEMENT = 0x00141A61,
    /* MSG_TYPE_NOT_COMPATIBLE_STATE */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_MSG_TYPE_NOT_COMPATIBLE_STATE = 0x00141A62,
    /* IE_NON_EXISTENT_NOT_IMPLEMENTED */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_IE_NON_EXISTENT_NOT_IMPLEMENTED = 0x00141A63,
    /* CONDITIONAL_IE_ERROR */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_CONDITIONAL_IE_ERROR = 0x00141A64,
    /* MSG_NOT_COMPATIBLE_STATE */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_MSG_NOT_COMPATIBLE_STATE = 0x00141A65,
    /* PROTOCOL_ERROR_UNSPECIFIED */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_PROTOCOL_ERROR_UNSPECIFIED = 0x00141A6F,
    /* PDN module network 5GSM error cause end */
    MIPC_RESULT_PDN_EXT_NETWORK_5GSM_CAUSE_END              = 0x00141AFF,
    /* PDN module network error end */
    MIPC_RESULT_PDN_EXT_NETWORK_ERROR_END                   = 0x0014FFFF,
    /* PDN mipc messages error begin */
    MIPC_RESULT_PDN_EXT_LOCAL_MIPC_ERROR_BEGIN              = 0x00150000,
    /* There is no enough information in MIPC message */
    MIPC_RESULT_PDN_EXT_LOCAL_MIPC_ERROR_NO_ENOUGH_INFO     = 0x00150001,
    /* PDN mipc messages error end */
    MIPC_RESULT_PDN_EXT_LOCAL_MIPC_ERROR_END                = 0x001500FF,
    /* PDN module parameters error begin */
    MIPC_RESULT_PDN_EXT_LOCAL_PARA_ERROR_BEGIN              = 0x00150100,
    /* parameters for PDN is invalid */
    MIPC_RESULT_PDN_EXT_LOCAL_PARA_ERROR_INVALID_PARA       = 0x00150101,
    /* APN is not found to activate */
    MIPC_RESULT_PDN_EXT_LOCAL_PARA_ERROR_NOT_FIND_APN_TO_ACT = 0x00150102,
    /* APN is already activated or no apn info to abort */
    MIPC_RESULT_PDN_EXT_LOCAL_PARA_ERROR_NO_APN_INFO_TO_ABORT = 0x00150103,
    /* APN is disbaled by host */
    MIPC_RESULT_PDN_EXT_LOCAL_PARA_ERROR_APN_PROFILE_IS_DISABLED = 0x00150104,
    /* APN call info is not found */
    MIPC_RESULT_PDN_EXT_LOCAL_PARA_ERROR_NOT_FIND_CALL_INFO = 0x00150105,
    /* PDN module parameters error end */
    MIPC_RESULT_PDN_EXT_LOCAL_PARA_ERROR_END                = 0x001501FF,
    /* PDN IP FALLBACK RESPONSE start */
    MIPC_RESULT_PDN_EXT_LOCAL_FALLBACK_RES_START            = 0x00150200,
    /* PDN IP FALLBACK RESPONSE fail abort */
    MIPC_RESULT_PDN_EXT_LOCAL_FALLBACK_RES_FAIL_ABORT       = 0x00150201,
    /* PDN IP FALLBACK RESPONSE success abort */
    MIPC_RESULT_PDN_EXT_LOCAL_FALLBACK_RES_SUCC_ABORT       = 0x00150202,
    /* PDN IP FALLBACK RESPONSE fail continue */
    MIPC_RESULT_PDN_EXT_LOCAL_FALLBACK_RES_FAIL_CONT        = 0x00150203,
    /* PDN IP FALLBACK RESPONSE success continue */
    MIPC_RESULT_PDN_EXT_LOCAL_FALLBACK_RES_SUCC_CONT        = 0x00150204,
    /* PDN IP FALLBACK RESPONSE end */
    MIPC_RESULT_PDN_EXT_LOCAL_FALLBACK_RES_END              = 0x0015020F,
    /* PDN module extension result end */
    MIPC_RESULT_PDN_EXT_END                                 = 0x0017FFFF,
    /* RF module extension result begin */
    MIPC_RESULT_RF_EXT_BEGIN                                = 0x00180000,
    /* RF module extension result end */
    MIPC_RESULT_RF_EXT_END                                  = 0x001BFFFF,
    /* SIM module extension result begin */
    MIPC_RESULT_SIM_EXT_BEGIN                               = 0x001C0000,
    /* MT is waiting  PUK1 code */
    MIPC_RESULT_SIM_EXT_PUK1_REQUIRED                       = 0x001C0001,
    /* MT is waiting  PIN2 code */
    MIPC_RESULT_SIM_EXT_PIN2_REQUIRED                       = 0x001C0002,
    /* MT is waiting  PUK2 code */
    MIPC_RESULT_SIM_EXT_PUK2_REQUIRED                       = 0x001C0003,
    /* SIM failure  */
    MIPC_RESULT_SIM_EXT_SIM_FAILURE                         = 0x001C0004,
    /* Incoorect password returned from UICC  */
    MIPC_RESULT_SIM_EXT_INCORRECT_PASS_WORD                 = 0x001C0005,
    /* Network personalization PIN required.Related 3GPP SPEC:22.022.  */
    MIPC_RESULT_SIM_EXT_NW_PERSON_PIN_REQUIRED              = 0x001C0006,
    /* Network personalization PUK required.  */
    MIPC_RESULT_SIM_EXT_NW_PERSON_PUK_REQUIRED              = 0x001C0007,
    /* Network subset personalization PIN required. Related 3GPP SPEC:22.022.  */
    MIPC_RESULT_SIM_EXT_NW_SUB_PERSON_PIN_REQUIRED          = 0x001C0008,
    /* Network subset personalization PUK required.  */
    MIPC_RESULT_SIM_EXT_NW_SUB_PERSON_PUK_REQUIRED          = 0x001C0009,
    /* Service Provider personalization PIN required. Related 3GPP SPEC:22.022. */
    MIPC_RESULT_SIM_EXT_SP_PERSON_PIN_REQUIRED              = 0x001C000A,
    /* Service Provider personalization PUK required. */
    MIPC_RESULT_SIM_EXT_SP_PERSON_PUK_REQUIRED              = 0x001C000B,
    /* Corporate personalization PIN required.Related 3GPP SPEC:22.022. */
    MIPC_RESULT_SIM_EXT_CORP_PERSON_PIN_REQUIRED            = 0x001C000C,
    /* Corporate personalization PUK required. */
    MIPC_RESULT_SIM_EXT_CORP_PERSON_PUK_REQUIRED            = 0x001C000D,
    /* IMSI personalization PIN required.Related 3GPP SPEC:22.022. */
    MIPC_RESULT_SIM_EXT_IMSI_PERSON_PIN_REQUIRED            = 0x001C000E,
    /* IMSI personalization PUK required. */
    MIPC_RESULT_SIM_EXT_IMSI_PERSON_PUK_REQUIRED            = 0x001C000F,
    /* Link network and service provider personalization pin required. */
    MIPC_RESULT_SIM_EXT_LINK_NS_SP_PERSON_PIN_REQUIRED      = 0x001C0010,
    /* Link network and service provider personalization puk required. */
    MIPC_RESULT_SIM_EXT_LINK_NS_SP_PERSON_PUK_REQUIRED      = 0x001C0011,
    /* Link SIM and corporate personalization pin required. */
    MIPC_RESULT_SIM_EXT_LINK_SIM_C_PERSON_PIN_REQUIRED      = 0x001C0012,
    /* Link SIM and corporate personalization puk required. */
    MIPC_RESULT_SIM_EXT_LINK_SIM_C_PERSON_PUK_REQUIRED      = 0x001C0013,
    /* BT SAP related error. */
    MIPC_RESULT_SIM_EXT_BT_SAP_UNDEFINED                    = 0x001C0014,
    /* BT SAP not accessible. */
    MIPC_RESULT_SIM_EXT_BT_SAP_NOT_ACCESSIBLE               = 0x001C0015,
    /* BT SAP error card removed. */
    MIPC_RESULT_SIM_EXT_BT_SAP_CARD_REMOVED                 = 0x001C0016,
    /* BT SAP error card already powered off. */
    MIPC_RESULT_SIM_EXT_BT_SAP_CARD_ALREADY_POWERED_OFF     = 0x001C0017,
    /* BT SAP error card already powered on. */
    MIPC_RESULT_SIM_EXT_BT_SAP_CARD_ALREADY_POWERED_ON      = 0x001C0018,
    /* Operation failed because of sim technical problem. */
    MIPC_RESULT_SIM_EXT_TECHNICAL_PROBLEM                   = 0x001C0019,
    /* TMO rsu verifycation result */
    MIPC_RESULT_SIM_EXT_VERIFYCATION_FAILED                 = 0x001C001A,
    /* TMO rsu verifycation result */
    MIPC_RESULT_SIM_EXT_REBOOT_REQUIRED                     = 0x001C001B,
    /* sim state is off */
    MIPC_RESULT_SIM_EXT_SIM_OFF                             = 0x001C001C,
    /* SIM module extension result end */
    MIPC_RESULT_SIM_EXT_END                                 = 0x001FFFFF,
    /* SMS module extension result begin */
    MIPC_RESULT_SMS_EXT_BEGIN                               = 0x00200000,
    /*  */
    MIPC_RESULT_SMS_EXT_CBM_CFG_WRONG_MSG_ID_RANGE_FORMAT   = 0x00200001,
    /*  */
    MIPC_RESULT_SMS_EXT_CBM_CFG_WRONG_MSG_ID_SINGLE_FORMAT  = 0x00200002,
    /*  */
    MIPC_RESULT_SMS_EXT_CBM_CFG_WRONG_DCS_RANGE_FORMAT      = 0x00200003,
    /*  */
    MIPC_RESULT_SMS_EXT_CBM_CFG_WRONG_DCS_SINGLE_FORMAT     = 0x00200004,
    /*  */
    MIPC_RESULT_SMS_EXT_CBM_CFG_TOO_MORE_RANGES_OR_SINGLES  = 0x00200005,
    /*  */
    MIPC_RESULT_SMS_EXT_CBM_CFG_MSG_ID_LOGIC_ERROR          = 0x00200006,
    /*  */
    MIPC_RESULT_SMS_EXT_CBM_CFG_DCS_LOGIC_ERROR             = 0x00200007,
    /* Something wrong with storage parameter, like unsync/uninit... */
    MIPC_RESULT_SMS_EXT_NEED_SET_PREFER_STORAGE_AGAIN       = 0x00200008,
    /* Something wrong with c2k operation */
    MIPC_RESULT_SMS_EXT_C2K_ERROR                           = 0x00200009,
    /* bellow should be old AT error, could use offset to judge AT error cause */
    MIPC_RESULT_SMS_EXT_AT_ERROR_BEGIN                      = 0x00210000,
    /* at error cause 226 would transfer this */
    MIPC_RESULT_SMS_EXT_CM_SMS_CONNECTION_BROKEN            = 0x002100E2,
    /* at error cause 2601 would transfer this */
    MIPC_RESULT_SMS_EXT_MTK_FDN_CHECK_FAILURE               = 0x00210A29,
    /* at error cause 6145 would transfer this */
    MIPC_RESULT_SMS_EXT_MTK_REQ_RETRY                       = 0x00211801,
    /* upper should be old AT error, could use offset to judge AT error cause */
    MIPC_RESULT_SMS_EXT_AT_ERROR_END                        = 0x0021FFFF,
    /* SMS module extension result end */
    MIPC_RESULT_SMS_EXT_END                                 = 0x0023FFFF,
    /* SS module extension result begin */
    MIPC_RESULT_SS_EXT_BEGIN                                = 0x00240000,
    /* cat module extension result end */
    MIPC_RESULT_SS_EXT_END                                  = 0x0027FFFF,
    /* SWITCH module extension result begin */
    MIPC_RESULT_SWITCH_EXT_BEGIN                            = 0x00280000,
    /* SWITCH module extension result end */
    MIPC_RESULT_SWITCH_EXT_END                              = 0x002BFFFF,
    /* SYS module extension result begin */
    MIPC_RESULT_SYS_EXT_BEGIN                               = 0x002C0000,
    /* SYS module extension result end */
    MIPC_RESULT_SYS_EXT_END                                 = 0x002FFFFF,
    /* IMS module extension result begin */
    MIPC_RESULT_IMS_EXT_BEGIN                               = 0x00300000,
    /* IMS module extension result end */
    MIPC_RESULT_IMS_EXT_END                                 = 0x0033FFFF,
    /* PHB module extension result begin */
    MIPC_RESULT_PHB_EXT_BEGIN                               = 0x00340000,
    /* PHB module PIN2 is required */
    MIPC_RESULT_PHB_EXT_PIN2_REQUIRED                       = 0x00340001,
    /* PHB module PUK2 is required */
    MIPC_RESULT_PHB_EXT_PUK2_REQUIRED                       = 0x00340002,
    /* PHB module text string is too long */
    MIPC_RESULT_PHB_EXT_TEXT_STRING_TOO_LONG                = 0x00340003,
    /* PHB module dial string is too long */
    MIPC_RESULT_PHB_EXT_DIAL_STRING_TOO_LONG                = 0x00340004,
    /* PHB module extension result end */
    MIPC_RESULT_PHB_EXT_END                                 = 0x0034FFFF,
    /*  */
    MIPC_RESULT_AUTH_REQUIRED                               = 0xFFFFFFFE,
    /*  */
    MIPC_RESULT_TIMEOUT                                     = 0xFFFFFFFF,
};
typedef enum mipc_result_const_enum mipc_result_const_enum;



#define MIPC_MAX_AT_URC_LEN                                (128) /* Maximum AT URC, should be 4*X */
#define MIPC_MAX_AT_CMD_LEN                                (128) /* Maximum AT command length, should be 4*X */
#define MIPC_MAX_AT_CMD_RSP_LEN                            (1024) /* Maximum AT command response length, should be 4*X */
#define MIPC_MAX_APN_LEN                                   (100) /* Maximum APN Name length, should be 4*X */
#define MIPC_MAX_DEL_SPI_NUM                               (50) /* Maximum SPI delete count, SPI is uint32 */
#define MIPC_MAX_APN_BEARER_LEN                            (10) /* Maximum APN bearer length */
#define MIPC_MAX_CID_LIST_LEN                              (200) /* cid is 0~199 */
#define MIPC_MAX_RULE_LIST_LEN                             (8) /*  */
#define MIPC_MAX_USERID_LEN                                (64) /* Maximum User Name length, should be 4*X */
#define MIPC_MAX_PASSWORD_LEN                              (64) /* Maximum Password length, should be 4*X */
#define MIPC_MAX_EIWLAN_CMD_LEN                            (8) /* Maximum IWLAN PRIORITY command length, should be 4*X */
#define MIPC_MAX_EIWLAN_TYPE_LEN                           (16) /* Maximum IWLAN PRIORITY type length, should be 4*X */
#define MIPC_MAX_EIWLAN_DESCRIPTION_LEN                    (32) /* Maximum IWLAN PRIORITY description length, should be 4*X */
#define MIPC_FIX_CALL_BARRING_PASSWORD_LEN                 (4) /* Maximum Call barring Password length, should be 4*X */
#define MIPC_MAX_OPER_LEN                                  (16) /* Maximum operator name length */
#define MIPC_MAX_USSD_LEN                                  (160) /* Maximum USSD length */
#define MIPC_MAX_PAC_IND_LEN                               (512) /* Maximum pac ind length */
#define MIPC_MAX_TERMINAL_RESPONSE_LEN                     (261) /* Maximum terminal response length */
#define MIPC_MAX_AID_LEN                                   (256) /* Maximum aid length in refresh */
#define MIPC_MAX_ENVELOP_LEN                               (261) /* Maximum envelop length */
#define MIPC_MAX_BIP_LEN                                   (32) /* Maximum stk bip command length */
#define MIPC_MAX_S_NSSAI_NUM                               (64) /* Maximum s-nssai count in s-nssai list */
#define MIPC_MAX_CLIENT_NAME_LEN                           (160) /* Maximum client name length */
#define MIPC_SIM_FIX_ICCID_LEN                             (20) /* Maximum ICCID length */
#define MIPC_MAX_IMSI_LEN                                  (20) /* Maximum IMSI length */
#define MIPC_MAX_ATR_LEN                                   (80) /* Maximum ATR string length */
#define MIPC_MAX_DEVICEID_LEN                              (16) /*  */
#define MIPC_MAX_MANUFACTURER_LEN                          (32) /*  */
#define MIPC_MAX_FIRMWARE_INFO_LEN                         (64) /*  */
#define MIPC_MAX_HARDWAREWARE_INFO_LEN                     (30) /*  */
#define MIPC_FIX_ESN_LEN                                   (8) /* Fixed length for ESN */
#define MIPC_FIX_IMEISV_LEN                                (2) /* Fixed length for IMEISV */
#define MIPC_FIX_MEID_LEN                                  (14) /* Fixed length for MEID */
#define MIPC_FIX_HARDWARE_ID_LEN                           (16) /* Fixed length for harware id */
#define MIPC_MAX_DUMP_LIDS_LEN                             (1024) /* max length for mcf dump lids */
#define MIPC_MAX_MCF_VALUE_LEN                             (512) /* max length for mcf value */
#define MIPC_MAX_MCF_CFG_LEN                               (1024) /* max length for mcf config */
#define MIPC_MAX_NETWORK_NAME_LEN                          (60) /*  */
#define MIPC_MAX_ROAMING_TEXT_LEN                          (64) /*  */
#define MIPC_FIX_GSM_AUTH_RAND_LEN                         (16) /* Fixed length for RAND */
#define MIPC_FIX_GSM_AUTH_RSP_KC_LEN                       (8) /* Fixed length for KC */
#define MIPC_FIX_GSM_AUTH_RSP_SRES_LEN                     (4) /* Fixed length for SRES */
#define MIPC_MAX_EXT_AUTH_CMD_DATA_LEN                     (256) /* Maximum command data length of extention authenticate command */
#define MIPC_MAX_EXT_AUTH_RSP_DATA_LEN                     (256) /* Maximum command response length of extention authenticate command */
#define MIPC_MAX_TERMINAL_CAPABILITY_DATA_LEN              (256) /* Maximum data length of terminal capability */
#define MIPC_MAX_SIM_APP_LABEL_LEN                         (32) /* Maximum data length of application label */
#define MIPC_MAX_SIM_AID_BYTE_LEN                          (20) /* Maximum data length of application id */
#define MIPC_MAX_SIM_AID_STR_LEN                           (40) /* Maximum string length of application id */
#define MIPC_MAX_SMS_PDU_LEN                               (256) /* Maximum length of SMS PDU(include the sca) */
#define MIPC_MAX_CBM_PDU_LEN                               (1246) /* Maximum length of CBM PDU((82+1)*15+1) */
#define MIPC_MAX_SMS_SCA_LEN                               (32) /* Maximum length of SMS SCA(include the NULL-ending) */
#define MIPC_FIX_SMS_ETWS_SECUR_INFO_LEN                   (50) /* fixed length of ETWS security info */
#define MIPC_MAX_SMS_NUM_LEN                               (32) /* Maximum length of SMS number */
#define MIPC_MAX_SMS_CBM_MSGID_RANGE_NUM                   (30) /*  */
#define MIPC_MAX_SMS_CBM_MSGID_SINGLE_NUM                  (60) /*  */
#define MIPC_MAX_SMS_CBM_DCS_RANGE_NUM                     (30) /*  */
#define MIPC_MAX_SMS_CBM_DCS_SINGLE_NUM                    (60) /*  */
#define MIPC_MAX_SMS_CBM_LANGUAGE_SINGLE_NUM               (60) /*  */
#define MIPC_MAX_SMS_EPSI_LEN                              (256) /*  */
#define MIPC_MAX_SMS_SEG_NUM                               (15) /*  */
#define MIPC_MAX_WFC_IFNAME_LEN                            (128) /* max length of WFC ifname(like wlan0) */
#define MIPC_MAX_WFC_THRESHOLD_NUM                         (16) /* max length of WFC threshold */
#define MIPC_MAX_WFC_IP_LEN                                (16) /* 16 for IPV6, 4 for IPv4 */
#define MIPC_FIX_WFC_EMC_AID_LEN                           (20) /* fixed length of WFC emergency address id */
#define MIPC_MAX_WFC_SSID_LEN                              (33) /* max length of WFC ssid */
#define MIPC_FIX_WFC_MAC_LEN                               (6) /* fix length of WFC mac */
#define MIPC_FIX_WFC_IPV4_LEN                              (4) /* fix length of WFC ipv4 */
#define MIPC_FIX_WFC_IPV6_LEN                              (16) /* fix length of WFC ipv6 */
#define MIPC_MAX_WFC_DNS_NUM                               (10) /* max wfc dns num */
#define MIPC_MAX_WFC_WIFI_TYPE_LEN                         (32) /* max length of WFC wifi type */
#define MIPC_MAX_SS_DIAL_NUMBER_LEN                        (182) /* Maximum dail number in ss service */
#define MIPC_MAX_SS_DIAL_NUMBER_FOR_ALIGN_LEN              (183) /* Maximum dail number in ss service for align */
#define MIPC_MAX_DIAL_ADDRESS_LEN                          (180) /* Maximum dail address length */
#define MIPC_MAX_CALL_NUMBER_LEN                           (128) /* Maximum call number length */
#define MIPC_MAX_CALL_PAU_LEN                              (512) /* Maximum call pau length */
#define MIPC_MAX_CALL_ECC_NUMBER_LEN                       (10) /* Maximum ecc call number length */
#define MIPC_MAX_CALL_CONFERENCE_PARTICIPANT_NUM           (40) /* Maximum conference call paticipant number */
#define MIPC_MAX_CALL_NAME_LEN                             (80) /* Maximum call name length */
#define MIPC_MAX_CALL_EIMSEVTPKG_URI_LEN                   (180) /* Maximum call +eimsevtpkg uri length */
#define MIPC_MAX_CALL_DISPLAY_NAME_LEN                     (64) /* Maximum call display name length */
#define MIPC_MAX_CALL_VERSTAT_LEN                          (64) /* Maximum call verstat length */
#define MIPC_MAX_CALL_PRIVACY_LEN                          (64) /* Maximum call privacy length */
#define MIPC_MAX_CALL_SS_SUBADDR_LEN                       (64) /*  */
#define MIPC_MAX_SIM_PATH_BYTE_LEN                         (12) /* Maximum byte length of sim path for byte_array type */
#define MIPC_MAX_SIM_PATH_STR_LEN                          (24) /* Maximum string length of sim path */
#define MIPC_MAX_SIM_APDU_BYTE_LEN                         (261) /* Maximum length of APDU byte */
#define MIPC_MAX_SIM_APDU_STRING_LEN                       (522) /* Maximum length of APDU string */
#define MIPC_MAX_SIM_LONG_BIN_DATA_LEN                     (65535) /* Maximum length of command or response data for LONG APDU operation */
#define MIPC_MAX_SIM_PIN_CODE_LEN                          (16) /* Maximum pin code length for sim card */
#define MIPC_MAX_SIM_PUK_CODE_LEN                          (16) /* Maximum puk code length for sim card */
#define MIPC_MAX_SIM_CMD_DATA_STR_LEN                      (510) /* Maximum command data string length of APDU */
#define MIPC_MAX_SIM_RSP_DATA_STR_LEN                      (510) /* Maximum response data string length of APDU */
#define MIPC_MAX_SIM_CMD_DATA_BYTE_LEN                     (255) /* Maximum command data byte length of APDU */
#define MIPC_MAX_SIM_CMD_EXTENDED_DATA_BYTE_LEN            (65535) /* Maximum command data byte length of extended APDU */
#define MIPC_MAX_SIM_RSP_DATA_BYTE_LEN                     (255) /* Maximum response data  byte length of APDU */
#define MIPC_MAX_SIM_NUM                                   (2) /*  */
#define MIPC_MAX_SIM_EID_LEN                               (32) /* Maximum eid string length of euicc */
#define MIPC_MAX_SIM_FACILITY_LEN                          (2) /* maximum string length of SIM facility string */
#define MIPC_MAX_SIM_SML_HCK_STR_LEN                       (128) /* maximum string length of SIM sml key string */
#define MIPC_MAX_CALL_FINISH_REASON_LEN                    (128) /*  */
#define MIPC_MAX_DTMF_DIGIT_LEN                            (128) /* Maximum call dtmf digit length. when DTMF_MODE is SINGLE_TONE, MAX_DTMF_DIGIT_LEN is 2 */
#define MIPC_MAX_CALL_ECC_LIST_RECORD_NUM                  (64) /* Maximum record of ecc list record  */
#define MIPC_MAX_CALL_SIP_HEADER_VALUE_PAIR_LEN            (232) /*  */
#define MIPC_MAX_CALL_SIP_HEADER_VALUE_LEN                 (1950) /* Maximum call sip header value length */
#define MIPC_MAX_CALL_ADDITIONAL_INFO_LEN                  (1950) /* Maximum call additinal info length */
#define MIPC_MAX_CALL_MT_SIP_INVITE_LEN                    (1950) /* Maximum MT SIP INVITE length */
#define MIPC_MAX_CALL_RCS_DIGITS_LINE_LEN                  (128) /* Maximum call rcs digits line info string length */
#define MIPC_MAX_CALL_RTT_TEXT_LEN                         (1024) /* Maximum call send Rtt Text length */
#define MIPC_MAX_CALL_PULL_URI_LEN                         (128) /* Maximum call pull uri length */
#define MIPC_MAX_CALL_DISPLAY_AND_SIGNALS_INFO_DISPLAY_LEN (64) /*  */
#define MIPC_MAX_CALL_EXTENDED_DISPLAY_INFO_LEN            (64) /*  */
#define MIPC_MAX_ECALL_MSD_DATA_LEN                        (140) /* Maximum number of bytes of eCall MSD */
#define MIPC_MAX_SIP_REASON_TEXT_LEN                       (120) /*  */
#define MIPC_IMS_MAX_URI_LEN                               (256) /*  */
#define MIPC_IMS_MAX_ERROR_MESSAGE_LEN                     (256) /*  */
#define MIPC_MAX_IMS_EVENT_PACKAGE_DATA_LEN                (64000) /*  */
#define MIPC_MAX_CALL_NUM                                  (7) /* Maximum call count */
#define MIPC_MAX_SBP_STR_LEN                               (256) /* Maximum length of sbp string */
#define MIPC_MAX_PLMN_ID_LEN                               (7) /* Maximum length of plmn id(mcc + mnc) */
#define MIPC_MAX_BAND_COMBO_LEN                            (16) /* Each band Combo max length */
#define MIPC_OMADM_VALUE_LEN                               (64) /* Maximum OMA-DM configured value length */
#define MIPC_MAX_SYS_THERMAL_SENSOR_NUM                    (8) /* max_sys_thermal_sensor_num */
#define MIPC_MAX_SYS_THERMAL_TRIP_POINT_NUM_IN_ONE_SENSOR  (16) /* max_sys_thermal_trip_point_num_in_one_sensor */
#define MIPC_MAX_ALPHAID_LEN                               (128) /* Maximum length of alphaid */
#define MIPC_MAX_SUB_ADDRESS_LEN                           (128) /* Maximum length of subaddress */
#define MIPC_MAX_CHANGE_BARRING_PWD_LEN                    (9) /* Maximum length of password in change barring request */
#define MIPC_MAX_SYS_STR_LEN                               (256) /* Maximum length of string in run GBA request */
#define MIPC_MAX_LCE_THRESHOLD_NUMBER                      (15) /* Maximum number of LCE threshold */
#define MIPC_MAX_TIME_LEN                                  (16) /* Maximum length of string in data TIME_IND */
#define MIPC_MAX_SET_LOCATION_LEN                          (128) /* Maximum length of string in set location info */
#define MIPC_MAX_DATA_SNSSAI_LEN                           (16) /*  */
#define MIPC_MAX_SPN_LEN                                   (71) /* Maximum length of SPN */
#define MIPC_MAX_GID1_NUM                                  (41) /* Maximum gid1 num */
#define MIPC_MAX_IMPI_LEN                                  (149) /* Maximum length of  IMPI */
#define MIPC_MAX_SS_ECMCCSS_RAW_LEN                        (256) /* Maximum length of ss ecmccss raw string */
#define MIPC_MAX_XCAP_USER_AGENT_STR_LEN                   (128) /* Maximum length of setup xcap user agent string */
#define MIPC_MAX_SS_XUI_INFO_LEN                           (512) /* Maximum length of ss xui info */
#define MIPC_MAX_SS_COMM_INFO_LEN                          (128) /* Maximum length of ss comm info */
#define MIPC_MAX_SS_USSD_LANG_LEN                          (32) /* Maximum length of ss ussd lang */
#define MIPC_MAX_IMS_STRING_INFO_LEN                       (128) /* Maximum length of ims string info */
#define MIPC_MAX_GRP_ID_NUM                                (10) /* Maximum number of grp list. */
#define MIPC_MAX_CHANNEL_LOCK_NUM                          (32) /* Maximum number of grp list. */
#define MIPC_MAX_SYS_THERMAL_ACTUATOR_NUM                  (32) /* max_sys_thermal_actuator_num */
#define MIPC_MAX_PHYSICAL_CHANNEL_CONFIGS_NUM              (15) /* Maximum number of physical channel configs list. */
#define MIPC_MAX_CELL_ID_LEN                               (32) /* Max cell id len */
#define MIPC_MAX_NWSCN_RECORD_NUM                          (8) /* Max network scan record num */
#define MIPC_MAX_NWSCN_PLMN_NUM                            (20) /* Max network scan plmn num */
#define MIPC_MAX_NWSCN_RESULT_NUM                          (20) /* Max network scan result num */
#define MIPC_MAX_MCCMNC_LEN                                (4) /* Max mcc/mnc length */
#define MIPC_UE_OS_ID_LEN                                  (16) /* According to RFC 4122,OS_ID is defined as UUID(Universally Unique IDentifier)with length 128bits(16bytes) */
#define MIPC_MAX_UE_OS_ID_NUM                              (15) /* According to 24.501 D.6.6,UE could carry maxinum 15 OS ID to NW */

#pragma pack (push)
#pragma pack (1)

typedef struct mipc_v4_full_addr_struct4 {
    uint32_t                                           mtu; /* 0 means not present */
    uint8_t                                            addr[4]; /* N/A */
    uint8_t                                            mask[4]; /* N/A */
} mipc_v4_full_addr_struct4 ;

typedef struct mipc_v6_full_addr_struct4 {
    uint32_t                                           mtu; /* 0 means not present */
    uint8_t                                            addr[16]; /* N/A */
    uint32_t                                           prefix; /* N/A */
} mipc_v6_full_addr_struct4 ;

typedef struct mipc_addr_struct4 {
    uint32_t                                           addr_len; /* N/A */
    uint8_t                                            addr[16]; /* N/A */
} mipc_addr_struct4 ;

typedef struct mipc_full_addr_struct4 {
    uint32_t                                           addr_len; /* N/A */
    uint8_t                                            addr[16]; /* N/A */
    uint32_t                                           mtu; /* 0 means not present */
    uint8_t                                            mask[4]; /* N/A */
    uint32_t                                           prefix; /* N/A */
} mipc_full_addr_struct4 ;

typedef struct mipc_apn_ia_struct4 {
    char                                               apn[MIPC_MAX_APN_LEN]; /* apn name */
    uint32_t                                           apn_idx; /* N/A */
    char                                               userid[MIPC_MAX_USERID_LEN]; /* user id */
    char                                               password[MIPC_MAX_PASSWORD_LEN]; /* password */
    uint32_t                                           bearer_bitmask; /* N/A */
    uint8_t                                            pdp_type; /* pdp type (v4, v6, v4v6 at home) */
    uint8_t                                            roaming_type; /* roamingtype (v4, v6, v4v6 at roaming) */
    uint8_t                                            auth_type; /* auth potocol */
    uint8_t                                            compression; /* compression */
} mipc_apn_ia_struct4 ;

typedef struct mipc_apn_profile_struct4 {
    uint32_t                                           id; /* apn profile id */
    uint8_t                                            plmn_id[MIPC_MAX_PLMN_ID_LEN]; /* provider id in sim card */
    uint8_t                                            padding; /* padding */
    char                                               apn[MIPC_MAX_APN_LEN]; /* apn name */
    uint32_t                                           apn_idx; /* N/A */
    char                                               userid[MIPC_MAX_USERID_LEN]; /* user id */
    char                                               password[MIPC_MAX_PASSWORD_LEN]; /* password */
    uint32_t                                           bearer_bitmask; /* N/A */
    uint32_t                                           apn_type; /* apn type */
    uint8_t                                            pdp_type; /* pdp type (v4, v6, v4v6 at home) */
    uint8_t                                            roaming_type; /* roamingtype (v4, v6, v4v6 at roaming) */
    uint8_t                                            auth_type; /* auth potocol */
    uint8_t                                            compression; /* compression */
    uint8_t                                            reserve1; /* reserve for implementing field */
    uint8_t                                            reserve2; /* reserve for implementing field */
    uint8_t                                            reserve3; /* reserve for implementing field */
    uint8_t                                            enabled; /* apn is enabled or not, MAX is not set */
} mipc_apn_profile_struct4 ;

typedef struct mipc_apn_profile_v2_struct4 {
    uint32_t                                           id; /* apn profile id, 0x7FFFFFFF is the invalid value to indicate that host don't need profile ID */
    uint8_t                                            plmn_id[MIPC_MAX_PLMN_ID_LEN]; /* provider id in sim card */
    uint8_t                                            padding; /* padding */
    char                                               apn[MIPC_MAX_APN_LEN]; /* apn name */
    uint32_t                                           apn_idx; /* to indicate different APNs which have same apn, 0x7FFFFFFF is the invalid value to indicate that apn index is maintained by modem not host */
    char                                               userid[MIPC_MAX_USERID_LEN]; /* user id */
    char                                               password[MIPC_MAX_PASSWORD_LEN]; /* password */
    uint32_t                                           bearer_bitmask; /* N/A */
    uint32_t                                           apn_type; /* apn type */
    uint8_t                                            pdp_type; /* pdp type (v4, v6, v4v6 at home) */
    uint8_t                                            roaming_type; /* roamingtype (v4, v6, v4v6 at roaming) */
    uint8_t                                            auth_type; /* auth potocol */
    uint8_t                                            compression; /* compression */
    uint8_t                                            enabled; /* apn is enabled or not, MAX is not set */
    uint8_t                                            padding2[3]; /* N/A */
    uint32_t                                           max_conns; /* to indicate max_conns for vzw apn */
    uint32_t                                           max_conn_t; /* to indicate max_conn_t for vzw apn */
    uint32_t                                           wait_time; /* to indicate wait_time for vzw apn */
    uint32_t                                           inact_timer; /* to indicate inact_timer for sprint apn */
    uint32_t                                           v4_mtu; /* ipv4 mtu, 0x7FFFFFFF is the invalid value to indicate that host don't need to set mtu */
    uint32_t                                           v6_mtu; /* ipv6 mtu, 0x7FFFFFFF is the invalid value to indicate that host don't need to set mtu */
} mipc_apn_profile_v2_struct4 ;

typedef struct mipc_md_apn_profile_struct4 {
    uint32_t                                           id; /* apn profile id */
    uint8_t                                            plmn_id[MIPC_MAX_PLMN_ID_LEN]; /* provider id in sim card */
    uint8_t                                            act_state; /* APN activated state */
    char                                               apn[MIPC_MAX_APN_LEN]; /* apn name */
    uint32_t                                           apn_idx; /* N/A */
    char                                               userid[MIPC_MAX_USERID_LEN]; /* user id */
    char                                               password[MIPC_MAX_PASSWORD_LEN]; /* password */
    uint32_t                                           bearer_bitmask; /* N/A */
    uint32_t                                           apn_type; /* apn type */
    uint8_t                                            pdp_type; /* pdp type (v4, v6, v4v6 at home) */
    uint8_t                                            roaming_type; /* roamingtype (v4, v6, v4v6 at roaming) */
    uint8_t                                            auth_type; /* auth potocol */
    uint8_t                                            reserve; /* reserve */
} mipc_md_apn_profile_struct4 ;

typedef struct mipc_vzw_apn_profile_struct4 {
    char                                               apn[MIPC_MAX_APN_LEN]; /* apn name */
    char                                               apnb[MIPC_MAX_APN_BEARER_LEN]; /* apn bearer */
    uint8_t                                            pdp_type; /* pdp type (v4, v6, v4v6 at home) */
    uint8_t                                            id; /* ID */
    uint8_t                                            apnclass; /* APN class */
    uint8_t                                            enabled; /* apn is enabled or not, MAX is not set */
    uint8_t                                            max_conn; /* max connection count */
    uint8_t                                            max_conn_t; /* max connection  */
    uint32_t                                           wait_time; /* wait time by seconds */
    uint8_t                                            act_state; /* APN activated state */
    uint8_t                                            reserve1; /* reserve */
    uint8_t                                            reserve2; /* reserve */
    uint8_t                                            reserve3; /* reserve */
} mipc_vzw_apn_profile_struct4 ;

typedef struct mipc_data_nitz_info_struct4 {
    uint32_t                                           year; /* the year as an integer. */
    uint32_t                                           month; /* N/A */
    uint32_t                                           day; /* N/A */
    uint32_t                                           hour; /* N/A */
    uint32_t                                           minute; /* N/A */
    uint32_t                                           second; /* N/A */
} mipc_data_nitz_info_struct4 ;

typedef struct mipc_data_v4_addr_struct4 {
    uint8_t                                            addr[4]; /* N/A */
} mipc_data_v4_addr_struct4 ;

typedef struct mipc_data_v6_addr_struct4 {
    uint8_t                                            addr[16]; /* N/A */
} mipc_data_v6_addr_struct4 ;

typedef struct mipc_data_pco_ie_struct4 {
    char                                               ie[5]; /* N/A */
    uint8_t                                            padding[3]; /* N/A */
    char                                               content[80]; /* N/A */
} mipc_data_pco_ie_struct4 ;

typedef struct mipc_data_packet_filter_struct4 {
    uint8_t                                            len; /* N/A */
    uint8_t                                            padding[3]; /* N/A */
    uint8_t                                            pattern[192]; /* N/A */
    uint8_t                                            mask[192]; /* N/A */
} mipc_data_packet_filter_struct4 ;

typedef struct mipc_data_secondary_pdp_context_info_struct4 {
    uint8_t                                            cid; /* N/A */
    uint8_t                                            p_cid; /* N/A */
    uint8_t                                            bearer_id; /* N/A */
    uint8_t                                            IM_CN_Signalling_Flag; /* N/A */
    uint8_t                                            WLAN_Offload; /* N/A */
    uint8_t                                            PDU_session_id; /* N/A */
    uint16_t                                           QFI; /* QOS flow id for NR */
} mipc_data_secondary_pdp_context_info_struct4 ;

typedef struct mipc_data_qos_info_struct4 {
    uint16_t                                           cid; /* N/A */
    uint16_t                                           QCI; /* N/A */
    uint32_t                                           DL_GBR; /* N/A */
    uint32_t                                           UL_GBR; /* N/A */
    uint32_t                                           DL_MBR; /* N/A */
    uint32_t                                           UL_MBR; /* N/A */
    uint32_t                                           DL_AMBR; /* N/A */
    uint32_t                                           UL_AMBR; /* N/A */
} mipc_data_qos_info_struct4 ;

typedef struct mipc_data_5gqos_info_struct4 {
    uint16_t                                           cid; /* N/A */
    uint16_t                                           VQI; /* N/A */
    uint64_t                                           DL_GFBR; /* N/A */
    uint64_t                                           UL_GFBR; /* N/A */
    uint64_t                                           DL_MFBR; /* N/A */
    uint64_t                                           UL_MFBR; /* N/A */
    uint64_t                                           DL_SAMBR; /* N/A */
    uint64_t                                           UL_SAMBR; /* N/A */
    uint32_t                                           Averaging_window; /* N/A */
} mipc_data_5gqos_info_struct4 ;

typedef struct mipc_data_tft_info_struct4 {
    uint8_t                                            cid; /* N/A */
    uint8_t                                            packet_filter_identifier; /* N/A */
    uint8_t                                            evaluation_precedence_index; /* N/A */
    uint8_t                                            remote_v4_addr_present; /* N/A */
    uint8_t                                            remote_v6_addr_present; /* N/A */
    uint8_t                                            protocol_number_next_header; /* N/A */
    uint8_t                                            tos_traffic_class; /* N/A */
    uint8_t                                            tos_mask; /* N/A */
    uint8_t                                            direction; /* N/A */
    uint8_t                                            NW_packet_filter_identifier; /* N/A */
    uint8_t                                            local_v4_addr_present; /* N/A */
    uint8_t                                            local_v6_addr_present; /* N/A */
    uint8_t                                            remote_v4_addr[4]; /* N/A */
    uint8_t                                            remote_v4_subnet_mask[4]; /* N/A */
    uint8_t                                            remote_v6_addr[16]; /* N/A */
    uint8_t                                            remote_v6_subnet_mask[16]; /* N/A */
    uint16_t                                           local_port_low; /* N/A */
    uint16_t                                           local_port_high; /* N/A */
    uint16_t                                           remote_port_low; /* N/A */
    uint16_t                                           remote_port_high; /* N/A */
    uint32_t                                           ipsec_spi; /* N/A */
    uint32_t                                           flow_label; /* N/A */
    uint8_t                                            local_v4_addr[4]; /* N/A */
    uint8_t                                            local_v4_subnet_mask[4]; /* N/A */
    uint8_t                                            local_v6_addr[16]; /* N/A */
    uint8_t                                            local_v6_subnet_mask[16]; /* N/A */
    uint32_t                                           QRI; /* N/A */
} mipc_data_tft_info_struct4 ;

typedef struct mipc_data_start_keepalive_request_struct4 {
    uint32_t                                           type; /* Type of keepalive packet, refer to DATA_KEEPALIVE_TYPE */
    uint32_t                                           sourcePort; /* Source port if applicable or 0x7FFFFFFF; the maximum value is 65535 */
    uint32_t                                           destinationPort; /* Destination port if applicable or 0x7FFFFFFF; the maximum value is 65535 */
    uint32_t                                           maxKeepaliveIntervalMillis; /* Maximum milliseconds between two packets */
    uint32_t                                           cid; /* Context ID, uniquely identifies this call */
    char                                               sourceAddress[68]; /* Source address in network-byte order */
    char                                               destinationAddress[68]; /* Destination address in network-byte order */
} mipc_data_start_keepalive_request_struct4 ;

typedef struct mipc_s_nssai_struct_struct4 {
    uint8_t                                            sst_present; /* N/A */
    uint8_t                                            sst; /* N/A */
    uint8_t                                            sd_present; /* N/A */
    uint8_t                                            padding; /* N/A */
    uint32_t                                           sd; /* N/A */
    uint8_t                                            mapped_sst_present; /* N/A */
    uint8_t                                            mapped_sst; /* N/A */
    uint8_t                                            mapped_sd_present; /* N/A */
    uint8_t                                            padding2; /* N/A */
    uint32_t                                           mapped_sd; /* N/A */
} mipc_s_nssai_struct_struct4 ;

typedef struct mipc_ursp_route_sel_desc_struct_struct4 {
    uint8_t                                            p_val; /* N/A */
    uint8_t                                            ssc_mode; /* N/A */
    uint8_t                                            dnn_len; /* N/A */
    uint8_t                                            s_nssai_present; /* N/A */
    mipc_s_nssai_struct_struct4                        s_nssai; /* N/A */
    char                                               dnn[MIPC_MAX_APN_LEN]; /* dnn name, MAX length 100 */
    uint8_t                                            pdu_session_type; /* N/A */
    uint8_t                                            pref_access_type; /* N/A */
    uint8_t                                            padding2[2]; /* N/A */
} mipc_ursp_route_sel_desc_struct_struct4 ;

typedef struct mipc_ursp_traffic_desc_struct_struct4 {
    uint8_t                                            is_match_all; /* traffic match all or not, 1 means match all, 0 means not */
    uint8_t                                            dnn_len; /* the length of dnn */
    uint8_t                                            padding[2]; /* N/A */
    char                                               dnn[MIPC_MAX_APN_LEN]; /* dnn name, MAX length 100 */
    uint8_t                                            os_id[16]; /* UUID */
    uint8_t                                            app_id_len; /* the length of app id */
    uint8_t                                            padding2[3]; /* N/A */
    uint8_t                                            app_id[255]; /* app id */
    uint8_t                                            padding3; /* N/A */
    uint8_t                                            ipv4_addr[4]; /* ipv4 address */
    uint8_t                                            ipv4_mask[4]; /* ipv4 address mask */
    uint8_t                                            ipv6_addr[16]; /* ipv6 address */
    uint8_t                                            ipv6_prefix_len; /* N/A */
    uint8_t                                            padding4[3]; /* N/A */
    uint16_t                                           port_num; /* N/A */
    uint16_t                                           min_port_num; /* N/A */
    uint16_t                                           max_port_num; /* N/A */
    uint8_t                                            prot_id_next_hdr; /* N/A */
    uint8_t                                            dst_fqdn_len; /* N/A */
    uint8_t                                            dst_fqdn[255]; /* N/A */
    uint8_t                                            padding5; /* N/A */
} mipc_ursp_traffic_desc_struct_struct4 ;

typedef struct mipc_ursp_ue_local_conf_struct_struct4 {
    uint8_t                                            ssc_mode; /* N/A */
    uint8_t                                            dnn_len; /* N/A */
    uint8_t                                            padding; /* N/A */
    uint8_t                                            s_nssai_present; /* N/A */
    mipc_s_nssai_struct_struct4                        s_nssai; /* N/A */
    char                                               dnn[MIPC_MAX_APN_LEN]; /* dnn name, MAX length 100 */
    uint8_t                                            pdu_session_type; /* N/A */
    uint8_t                                            pref_access_type; /* N/A */
    uint8_t                                            padding3[2]; /* N/A */
} mipc_ursp_ue_local_conf_struct_struct4 ;

typedef struct mipc_ursp_get_route_supp_profile_ind_struct_struct4 {
    uint32_t                                           cid; /* N/A */
    uint32_t                                           supp_profile_type; /* N/A */
    mipc_ursp_traffic_desc_struct_struct4              traffic_desc; /* N/A */
    mipc_ursp_ue_local_conf_struct_struct4             ue_local_conf; /* N/A */
    uint8_t                                            is_match_all_disallowed; /* N/A */
    uint8_t                                            padding[3]; /* N/A */
} mipc_ursp_get_route_supp_profile_ind_struct_struct4 ;

typedef struct mipc_ursp_rule_struct_struct4 {
    uint8_t                                            p_val; /* N/A */
    uint8_t                                            padding[3]; /* N/A */
    mipc_ursp_traffic_desc_struct_struct4              traffic_desc; /* N/A */
    uint8_t                                            num_of_rsd; /* N/A */
    uint8_t                                            padding2[3]; /* N/A */
    mipc_ursp_route_sel_desc_struct_struct4            route_sel_desc_list[8]; /* N/A */
} mipc_ursp_rule_struct_struct4 ;

typedef struct mipc_plmn_specific_s_nssai_struct_struct4 {
    uint8_t                                            plmn_id[8]; /* only the first 6 length are used for mcc and mnc, the last 2 is padding */
    uint8_t                                            sst_present; /* N/A */
    uint8_t                                            sst; /* N/A */
    uint8_t                                            sd_present; /* N/A */
    uint8_t                                            padding; /* N/A */
    uint32_t                                           sd; /* N/A */
    uint8_t                                            mapped_sst_present; /* N/A */
    uint8_t                                            mapped_sst; /* N/A */
    uint8_t                                            mapped_sd_present; /* N/A */
    uint8_t                                            padding2; /* N/A */
    uint32_t                                           mapped_sd; /* N/A */
} mipc_plmn_specific_s_nssai_struct_struct4 ;

typedef struct mipc_rejected_s_nssai_struct_struct4 {
    uint8_t                                            cause_value; /* N/A */
    uint8_t                                            sst_present; /* N/A */
    uint8_t                                            sst; /* N/A */
    uint8_t                                            sd_present; /* N/A */
    uint32_t                                           sd; /* N/A */
} mipc_rejected_s_nssai_struct_struct4 ;

typedef struct mipc_nw_provider_struct4 {
    uint32_t                                           index; /* Network index in the SIM Preferred network list. */
    char                                               plmn_id[MIPC_MAX_PLMN_ID_LEN]; /* PLMN id, format: ASCII (Number: 0-9) */
    uint8_t                                            padding[1]; /* N/A */
    char                                               network_name[60]; /* Network Name, format: ASCII */
    char                                               network_short_name[60]; /* Network short Name, format: ASCII */
    uint32_t                                           act; /* if get/set prefer provider, please refer to NW_BIT_ACT
            if not get/set prefer provider, please refer to NW_ACT_TYPE
 */
    uint32_t                                           act_supported; /* bitmap for which access technology were selected, 1 byte bitmap. */
    uint8_t                                            state; /* 0x0:unknown, 0x1:home, 0x2:forbidden, 0x4:preferred, 0x8:visible, 0x10: registered */
    uint8_t                                            rssi; /* RSSI: range 0-31 and 99 for invalid */
    uint8_t                                            error_rate; /* ErrorRate: range 0-7 and 99 for invalid */
    uint8_t                                            padding2[1]; /* N/A */
} mipc_nw_provider_struct4 ;

typedef struct mipc_nw_nitz_info_struct4 {
    uint32_t                                           year; /* the year as an integer. */
    uint32_t                                           month; /* N/A */
    uint32_t                                           day; /* N/A */
    uint32_t                                           hour; /* N/A */
    uint32_t                                           minute; /* N/A */
    uint32_t                                           second; /* N/A */
    int32_t                                            time_zone_offset_minutes; /* this value includes any adjustment for the current state of daylight saving time. */
    int32_t                                            daylight_saving_offset_minutes; /* this value indicates whether time zone includes daylight savings adjustment, for example, 0 means no adjustment for Daylight saving time.. */
} mipc_nw_nitz_info_struct4 ;

typedef struct mipc_nw_anbr_info_struct4 {
    uint8_t                                            anbrq_config; /* N/A */
    uint8_t                                            ebi; /* N/A */
    uint8_t                                            is_ul; /* N/A */
    uint8_t                                            beare_id; /* qos flow identifier. */
    uint16_t                                           bitrate; /* bitrate value. */
    uint8_t                                            pdu_session_id; /* pdu session id. */
    uint8_t                                            ext_param; /* reserved for future usage. */
} mipc_nw_anbr_info_struct4 ;

typedef struct mipc_nw_irat_info_struct4 {
    uint8_t                                            irat_status; /* N/A */
    uint8_t                                            is_successful; /* present only when irat_status is 0. 0:inter_rat procedure failed , 1:inter_rat procedure is successful, 255: invalid value */
} mipc_nw_irat_info_struct4 ;

typedef struct mipc_nw_reg_state_struct4 {
    uint8_t                                            ps_state; /* Indicate packet service register state.
            0 detached
            1 attached, home network
            2 not registered, but MT is currently trying to attach or searching an operator to register to
            3 registration denied
            4 detached
            5 attached, roaming  network
 */
    uint8_t                                            cs_state; /* Indicate circuit service register state. */
    char                                               plmn[MIPC_MAX_PLMN_ID_LEN]; /* N/A */
    uint8_t                                            padding[1]; /* N/A */
    char                                               cs_plmn[MIPC_MAX_PLMN_ID_LEN]; /* N/A */
    uint8_t                                            padding2[1]; /* N/A */
    uint32_t                                           lac; /* N/A */
    uint32_t                                           cs_lac; /* N/A */
    uint32_t                                           ci; /* N/A */
    uint32_t                                           cs_ci; /* N/A */
    uint8_t                                            is_roaming; /* N/A */
    uint8_t                                            cs_is_roaming; /* N/A */
    uint8_t                                            padding3[2]; /* N/A */
} mipc_nw_reg_state_struct4 ;

typedef struct mipc_nw_blacklist_struct4 {
    char                                               plmn[MIPC_MAX_PLMN_ID_LEN]; /* N/A */
    uint8_t                                            blacklist_type; /* N/A */
} mipc_nw_blacklist_struct4 ;

typedef struct mipc_nw_location_info_struct4 {
    uint32_t                                           location_area_code; /* GSM/UMTS area code of the current location. */
    uint32_t                                           tracking_area_code; /* LTE tracking area code of the current location. */
    uint32_t                                           cell_id; /* ID of the cellular tower. */
} mipc_nw_location_info_struct4 ;

typedef struct mipc_nw_gsm_cell_struct4 {
    uint8_t                                            state; /* 1: serving; 0: neighboring */
    char                                               provider_id[MIPC_MAX_PLMN_ID_LEN]; /* N/A */
    uint32_t                                           lac; /* Location area code. */
    uint32_t                                           cid; /* Cell Identity. */
    uint32_t                                           ta; /* timing advance. */
    uint32_t                                           arfcn; /* The Absolute Radio Frequency Channel Number of the cell. Use 0xFFFFFFFF when this information is not available. */
    uint32_t                                           base_station_id; /* The Base Station id for the cell. */
    uint32_t                                           rx_level; /* The received signal strength of the cell. */
    uint32_t                                           bitErrorRate; /* Transport Channel BER as defined in TS 25.225 5.2.5 Valid values are (0-7, 99) as defined in TS 27.007 8.5. */
    uint32_t                                           registered; /* The registered state of the cell. */
    char                                               long_name[MIPC_MAX_NETWORK_NAME_LEN]; /* long provider name. */
    char                                               short_name[MIPC_MAX_NETWORK_NAME_LEN]; /* short provider name. */
} mipc_nw_gsm_cell_struct4 ;

typedef struct mipc_nw_umts_cell_struct4 {
    uint8_t                                            state; /* 1: serving; 0: neighboring */
    char                                               provider_id[MIPC_MAX_PLMN_ID_LEN]; /* N/A */
    uint32_t                                           lac; /* Location area code. */
    uint32_t                                           cid; /* Cell Identity. */
    uint32_t                                           uarfcn; /* The UTRA Absolute Radio Frequency Channel Number of the cell. Use 0xFFFFFFFF when this information is not available. */
    uint32_t                                           psc; /* The Primary Scrambling Code of the cell. */
    int32_t                                            rscp; /* The received signal code power of the cell. */
    int32_t                                            ecno; /* The signal to noise ratio of the cell. */
    uint32_t                                           registered; /* The registered state of the cell. */
    char                                               long_name[MIPC_MAX_NETWORK_NAME_LEN]; /* long provider name. */
    char                                               short_name[MIPC_MAX_NETWORK_NAME_LEN]; /* short provider name. */
} mipc_nw_umts_cell_struct4 ;

typedef struct mipc_nw_lte_cell_struct4 {
    uint8_t                                            state; /* 1: serving; 0: neighboring */
    char                                               provider_id[MIPC_MAX_PLMN_ID_LEN]; /* N/A */
    uint32_t                                           cid; /* Cell Identity. */
    uint32_t                                           earfcn; /* The Radio Frequency Channel Number of the cell. Use 0xFFFFFFFF when this information is not available. */
    uint32_t                                           physical_cell_id; /* The Physical Cell ID. Use 0xFFFFFFFF when this information is not available. */
    uint32_t                                           tac; /* The Tracking Area Code. */
    int32_t                                            rsrp; /* The Average Reference signal Received Power. */
    int32_t                                            rsrq; /* Average Reference signal Received Quality. */
    uint32_t                                           ta; /* timing advance. */
    int32_t                                            rsrp_in_qdbm; /* The Average Reference signal Received Power in qdbm. */
    int32_t                                            rsrq_in_qdbm; /* Average Reference signal Received Quality in qdbm. */
    int32_t                                            rssnr; /* The current reference signal signal-to-noise ratio in 0.1 dB units.Range: -200 to +300 (-200 = -20.0 dB, +300 = 30dB).INT_MAX : 0x7FFFFFFF denotes invalid value. */
    uint32_t                                           cqi; /* The current Channel Quality Indicator.Range: 0 to 15,INT_MAX : 0x7FFFFFFF denotes invalid value. */
    uint32_t                                           dl_freq_band; /* downlink freq band used by the cell. */
    uint32_t                                           registered; /* The registered state of the cell. */
    char                                               long_name[MIPC_MAX_NETWORK_NAME_LEN]; /* long provider name. */
    char                                               short_name[MIPC_MAX_NETWORK_NAME_LEN]; /* short provider name. */
} mipc_nw_lte_cell_struct4 ;

typedef struct mipc_nw_nr_cell_struct4 {
    uint8_t                                            state; /* 1: serving; 0: neighboring */
    char                                               provider_id[MIPC_MAX_PLMN_ID_LEN]; /* N/A */
    uint64_t                                           cid; /* Cell Identity. */
    uint32_t                                           physical_cell_id; /* The Physical Cell ID. */
    uint32_t                                           nr_arfcn; /* Absolute RF channel number of the serving cell. */
    uint32_t                                           tac; /* The Tracking Area Code. */
    int32_t                                            rsrp; /* The Average Reference signal Received Power. */
    int32_t                                            rsrq; /* Average Reference signal Received Quality. */
    int32_t                                            sinr; /* SS signal-to-noise and interference ratio. */
    uint32_t                                           ta; /* timing advance. */
    uint32_t                                           csirsrp; /* CSI reference signal received power. */
    uint32_t                                           csirsrq; /* CSI reference signal received quality. */
    uint32_t                                           csisinr; /* CSI signal-to-noise and interference ratio. */
    uint32_t                                           dl_freq_band; /* downlink freq band used by the cell. */
    uint32_t                                           registered; /* The registered state of the cell. */
    char                                               long_name[MIPC_MAX_NETWORK_NAME_LEN]; /* long provider name. */
    char                                               short_name[MIPC_MAX_NETWORK_NAME_LEN]; /* short provider name. */
} mipc_nw_nr_cell_struct4 ;

typedef struct mipc_nw_cdma_cell_struct4 {
    uint32_t                                           networkId; /* Network Id 0..65535, 0xffffffff means invalid */
    uint32_t                                           systemId; /* CDMA System Id 0..32767, 0xffffffff means invalid. */
    uint32_t                                           basestationId; /* Base Station Id 0..65535, 0xffffffff means invalid */
    uint32_t                                           longitude; /* Longitude is a decimal number as specified in 3GPP2 C.S0005-A v6.0.It is represented in units of 0.25 seconds and ranges from -2592000 to 2592000, both values inclusive (corresponding to a range of -180 to +180 degrees). 0xffffffff 0xffffffff means invalid . */
    uint32_t                                           latitude; /* Latitude is a decimal number as specified in 3GPP2 C.S0005-A v6.0.It is represented in units of 0.25 seconds and ranges from -1296000 to 1296000, both values inclusive (corresponding to a range of -90 to +90 degrees). 0xffffffff 0xffffffff means invalid . */
    uint32_t                                           dbm_cdma; /* This value is the actual RSSI value. */
    uint32_t                                           ecio_cdma; /* This value is the actual Ec/Io. */
    uint32_t                                           dbm_evdo; /* This value is the actual RSSI value. */
    uint32_t                                           ecio_evdo; /* This value is the actual Ec/Io. */
    uint32_t                                           snr_evdo; /* signal to noise ratio. */
    uint8_t                                            state; /* 1: serving; 0: neighboring */
    uint8_t                                            registered; /* The registered state of the cell. */
} mipc_nw_cdma_cell_struct4 ;

typedef struct mipc_nw_tdscdma_cell_struct4 {
    int32_t                                            TBD; /* N/A */
} mipc_nw_tdscdma_cell_struct4 ;

typedef struct mipc_nw_reg_change_info_struct4 {
    uint8_t                                            stat; /* Network register status. */
    uint32_t                                           lac_tac; /* Location area code. */
    uint64_t                                           cell_id; /* Cell id, 32 bit for non-5G and 36 bit for 5G. */
    uint16_t                                           eact; /* Radio access technology. */
    uint8_t                                            rac; /* Routing area code. */
    uint8_t                                            nw_existence; /* Indicate if nw exist, only valid when eact belongs to C2K. */
    uint8_t                                            roam_indicator; /* Roam indicator, only valid when eact belongs to C2K. */
    uint8_t                                            cause_type; /* Indicates the type of reject_cause. */
    uint16_t                                           reject_cause; /* The cause of the failed registration. */
    uint8_t                                            dcnr_restricted; /* Indicate if dcnr is restricted. */
    uint8_t                                            endc_sib_status; /* Indicates endc sib status. */
    uint8_t                                            endc_available; /* Indicate if endc is available. */
} mipc_nw_reg_change_info_struct4 ;

typedef struct mipc_nw_cs_reg_info_struct4 {
    uint8_t                                            stat; /* Network register status. */
    uint16_t                                           rat; /* The radio technology, please refer to eAct of EREG. */
    uint8_t                                            css; /* Network register status, 0: Concurrent service not support; 1: Concurrent service support. */
    uint8_t                                            roaming_ind; /* If register on CDMA or EVDO. */
    int8_t                                             is_in_prl; /* indicates whether the current system is in the PRL if registered on a CDMA or EVDO system or -1 if not. 0=not in the PRL, 1=in the PRL. */
    int16_t                                            def_roaming_ind; /* default Roaming Indicator from the PRL, if registered on a CDMA or EVDO system or -1 if not. Valid values are 0-255. */
    uint16_t                                           reason_for_denial; /* Registeration denied reason. See 3GPP TS 24.008. */
} mipc_nw_cs_reg_info_struct4 ;

typedef struct mipc_nw_ps_reg_info_struct4 {
    uint8_t                                            stat; /* Network register status. */
    uint16_t                                           rat; /* The radio technology, please refer to eAct of EREG. */
    uint16_t                                           reason_for_denial; /* Registeration denied reason. See 3GPP TS 24.008. */
    uint16_t                                           max_data_calls; /* The maximum number of simultaneous data calls. This maybe removed in future because it always be 0 in ril */
    int32_t                                            is_vops_supported; /* Indicates if camped network support VoLTE services. */
    int32_t                                            is_emc_bearer_supported; /* Indicates if camped network support VoLTE emergency bearers. */
    uint8_t                                            is_endc_available; /* Indicates if E-UTRA-NR Dual Connectivity(EN-DC) is supported by the primary serving cell. */
    uint8_t                                            is_dcnr_restricted; /* Indicates if dual connectivity with NR is restricted. */
    uint8_t                                            is_nr_available; /* Indicates if the nr available. */
    uint8_t                                            roaming_ind; /* If register on CDMA or EVDO. */
    int8_t                                             is_in_prl; /* indicates whether the current system is in the PRL if registered on a CDMA or EVDO system or -1 if not. 0=not in the PRL, 1=in the PRL. */
    int16_t                                            def_roaming_ind; /* default Roaming Indicator from the PRL, if registered on a CDMA or EVDO system or -1 if not. Valid values are 0-255. */
    uint64_t                                           cell_id; /* Cell id. */
    uint8_t                                            cache_endc_connect; /* cache endc connect for a specified period of time(the timer is configed by api). */
    uint32_t                                           lac_tac; /* Location area code. */
} mipc_nw_ps_reg_info_struct4 ;

typedef struct mipc_nw_channel_lock_info_struct4 {
    uint8_t                                            opt; /* Lock Operation for this info. */
    uint8_t                                            act; /* 0:GSM; 2:UTRAN; 7:LTE; 11:NR */
    uint32_t                                           band_info[4]; /* Bitmap for band info: GSM and UMTS use band_info[0]; LTE uses band_info[0..7]; NR uses band_info[0..31] */
    uint8_t                                            channel_num; /* The real length for arfcn_list. */
    uint32_t                                           arfcn_list[32]; /* The list that expected to lock. */
    uint32_t                                           cell_id; /* The cell want to lock. Once set the id, the channel_num will be considered as 1. */
    uint8_t                                            lock_mode; /* Lock channel mode. */
} mipc_nw_channel_lock_info_struct4 ;

typedef struct mipc_nw_channel_lock_info_v1_struct4 {
    uint32_t                                           opt; /* Lock Operation for this info. */
    uint32_t                                           act; /* 0:GSM; 2:UTRAN; 7:LTE; 11:NR */
    uint32_t                                           band_info[32]; /* Bitmap for band info: GSM and UMTS use band_info[0]; LTE uses band_info[0..7]; NR uses band_info[0..31] */
    uint32_t                                           channel_num; /* The real length for arfcn_list. */
    uint32_t                                           arfcn_list[32]; /* The list that expected to lock. */
    uint32_t                                           cell_id; /* The cell want to lock. Once set the id, the channel_num will be considered as 1. */
    uint32_t                                           lock_mode; /* Lock channel mode. */
} mipc_nw_channel_lock_info_v1_struct4 ;

typedef struct mipc_nw_gsm_signal_strength_struct4 {
    int32_t                                            signal_strength; /* Valid values are (0-31, 99) as defined in TS27.007 8.5. */
    int32_t                                            bit_error_rate; /* Valid values are (0-7, 99) as defined in TS27.007 8.5. */
    int32_t                                            timing_advance; /* Timing Advance in bit periods. 1 bit period = 48/13 us. */
} mipc_nw_gsm_signal_strength_struct4 ;

typedef struct mipc_nw_umts_signal_strength_struct4 {
    int32_t                                            signal_strength; /* Valid values are (0-31, 99) as defined in TS27.007 8.5. */
    int32_t                                            bit_error_rate; /* Valid values are (0-7, 99) as defined in TS27.007 8.5. */
    int32_t                                            rscp; /* CPICH RSCP as defined in TS 25.215 5.1.1, valid value are (0-96, 255). */
    int32_t                                            ecno; /* Ec/No value as defined in TS 25.215 5.1.5. Valid values are (0-49, 255). */
} mipc_nw_umts_signal_strength_struct4 ;

typedef struct mipc_nw_lte_signal_strength_struct4 {
    int32_t                                            signal_strength; /* Valid values are (0-31, 99) as defined in TS27.007 8.5. */
    int32_t                                            rsrp; /* The current Reference Signal Receive Power in dBm multipled by -1. Range: 44-140 dBm. */
    int32_t                                            rsrq; /* The current Reference Signal Receive Quality in dB multiplied by -1. (20 - 3 dB). */
    int32_t                                            rssnr; /* The current reference signal signal-to-noise ratio in 0.1 dB units. Range: -200 to + 300 */
    int32_t                                            cqi; /* The current Channel Quality Indicator, range(0-15). */
    int32_t                                            timing_advance; /* Timing advance in micro seconds for a one way trip from cell to device. Range(0 - 0x7ffffffe) */
} mipc_nw_lte_signal_strength_struct4 ;

typedef struct mipc_nw_nr_signal_strength_struct4 {
    int32_t                                            signal_strength; /* Valid values are (0-31, 99) as defined in TS27.007 8.5. */
    int32_t                                            ss_rsrp; /* SS reference signal received power, multipled by -1, Range[44, 140]. */
    int32_t                                            ss_rsrq; /* SS reference signal received quality, multipled by -1, Range[3, 20]. */
    int32_t                                            ss_sinr; /* SS signal-to-noise and interference ratio. Range[-23, 40]. */
    int32_t                                            csi_rsrp; /* CSI reference signal received power, multipled by -1. Range[44, 140] */
    int32_t                                            csi_rsrq; /* CSI reference signal received quality, multipled by -1. Range[3, 20] */
    int32_t                                            csi_sinr; /* CSI signal-to-noise and interference ratio. Range[-23, 40] */
} mipc_nw_nr_signal_strength_struct4 ;

typedef struct mipc_nw_cdma_signal_strength_struct4 {
    int32_t                                            dbm; /* cdma actual RSSI value. */
    int32_t                                            ecio; /* cdma actual Ec/Io value. */
    int32_t                                            snr; /* cdma signal noise ratio. */
} mipc_nw_cdma_signal_strength_struct4 ;

typedef struct mipc_nw_cscon_status_struct4 {
    uint8_t                                            mode; /* Indicates the signalling connection status. */
    uint8_t                                            state; /* Indicates the RRC state information if the MT is in connected mode while in UTRAN. */
    uint8_t                                            access; /* Indicates the access technology. */
    uint8_t                                            core_network; /* Indicates the core network. */
} mipc_nw_cscon_status_struct4 ;

typedef struct mipc_nw_pol_info_struct4 {
    uint32_t                                           start_index; /* Indicates the start index for preferred network list. */
    uint32_t                                           end_index; /* Indicates the end index for preferred network list. */
    uint8_t                                            format_first; /* Indicates the start format code for network name. */
    uint8_t                                            format_last; /* Indicates the stop format code for network name. */
} mipc_nw_pol_info_struct4 ;

typedef struct mipc_nw_ps_cs_reg_roaming_info_struct4 {
    uint8_t                                            m_voice_reg_state; /* CS state:0 1 2 3 */
    uint8_t                                            m_data_reg_state; /* PS state:0 1 2 3 */
    uint8_t                                            m_voice_roaming_type; /* CS roaming type:0 1 2 3 */
    uint8_t                                            m_data_roaming_type; /* PS roaming type:0 1 2 3 */
    uint8_t                                            m_ril_voice_reg_state; /* CS registration state for GSM,UMTS and CDMA 0~15 */
    uint8_t                                            m_ril_data_reg_state; /* PS registration state for GSM,UMTS and CDMA 0~15 */
} mipc_nw_ps_cs_reg_roaming_info_struct4 ;

typedef struct mipc_nw_cellmeasurement_info_struct4 {
    uint8_t                                            rat; /* cell rat info: 7: LTE; 13 : NG-RAN */
    uint32_t                                           arfcn; /* the arfcn info for this cell. */
    uint32_t                                           pci; /* the physical cell id for this cell. */
    uint32_t                                           rsrp; /* the signal info in qdbm for this cell */
    uint32_t                                           rsrq; /* the signal info in qdbm for this cell. */
    uint32_t                                           snr; /* the signal info for this cell in qdb. */
    uint64_t                                           cid; /* the cell id for this cell. */
} mipc_nw_cellmeasurement_info_struct4 ;

typedef struct mipc_nw_cell_band_bandwidth_struct4 {
    uint16_t                                           cell_band; /* cell band: 1~1024 */
    uint32_t                                           cell_bandwidth; /* cell bandwidth: 0~400000,kHz */
} mipc_nw_cell_band_bandwidth_struct4 ;

typedef struct mipc_nw_lte_nr_ca_info_struct4 {
    uint32_t                                           cell_index; /* ServCell index. */
    uint8_t                                            cell_state; /* 1:SCELL_STATUS_NOACTIVE; 2:SCELL_STATUS_ACTIVE */
    uint8_t                                            cc_cw0_cqi; /* cc_cw0_cqi:0~15 */
    uint8_t                                            cc_cw1_cqi; /* cc_cw1_cqi:0~15 */
    uint8_t                                            cell_bandwidth; /* cell bandwidth: for lte 0:1.4MHz 1:3MHz 2:5MHz 3:10MHz 4:15MHz 5:20MHz; for nr 0:5MHz 1:10MHz 2:15MHz 3:20MHz 4:25MHz 5:30MHz 6:40MHz 7:50MHz 8:60MHz 9:80MHz 10:90MHz 11:100MHz 12:200MHz 13:400MHz */
    uint16_t                                           cell_band; /* cell band: 1~1024 */
    uint16_t                                           cc_pci; /* cc_pci:0~1024 */
    uint32_t                                           cc_arfcn; /* channel info: EARFCN for LTE and NR-ARFCN for NR5G */
    char                                               cell_bandwidth_str[8]; /* cell bandwidth str unit: MHz */
} mipc_nw_lte_nr_ca_info_struct4 ;

typedef struct mipc_cell_plmn_struct4 {
    char                                               plmn_id[MIPC_MAX_PLMN_ID_LEN]; /* N/A */
    char                                               plmn_name[32]; /* N/A */
} mipc_cell_plmn_struct4 ;

typedef struct mipc_nw_raw_signal_info_struct4 {
    int32_t                                            sig1; /* 0 ~ 63: this field is the same as <rscp> in +CESQ when camp on GSM service;
 0 ~ 96: this field is the same as <rscp> in +CESQ when camp on UMTS service;
 0 ~ 34: this field the same as rsrq in +CESQ when camp on LTE network.
 255 means invalid value */
    int32_t                                            sig2; /* 0 ~ 7: ber when camp on GSM; 0~ 49: ecno when camp on UMTS; 0 ~ 97: rsrp when camp on LTE. */
    int32_t                                            rssi_in_qdbm; /* Negative integer. Received signal strength raw data in quarter dbm. 1 meams inivalid. */
    int32_t                                            rscp_in_qdbm; /* Negative integer. RSCP in quarter dbm, only avaliable when camp on UMTS network. 1 means invalid. */
    int32_t                                            ecn0_in_qdbm; /* Negative integer. EcN0 in quarter dbm. Only avaliable when camp on UMTS network, 1 means invalid. */
    int32_t                                            rsrq_in_qdbm; /* Negative integer.
 GSM/UMTS/LTE/C2K: RSRQ in quarter dB. Only avaliable when camp on LTE network, 1 means invalid;
 NR: SS-RSRQ in qdb. 0x7FFF means invalid. */
    int32_t                                            rsrp_in_qdbm; /* Negative integer.
 GSM/UMTS/LTE/C2K: RSRP in quarter dbm. Only avaliable when camp on LTE network, 1 means invalid;
 NR: SS-RSRP in qdbm. 0x7FFF means invalid. */
    int32_t                                            eact; /*  */
    int32_t                                            sig3; /* GSM/UMTS/LTE/C2K: RSSNR in quarter dB. RSSNR is signal-to-noise ration for reference signal. It is available only when camping on a LTE network, 0x7FFF means invalid.
 NR: SS-SINR in qdb, 0x7FFF means invalid. */
    int32_t                                            serv_band; /* Serving LTE band. */
    int32_t                                            second_rsrq_in_qdbm; /* CSI-RSRQ in qdb. Only avaliable when camp on NR network, 0x7FFF means invalid. Now invalid value is reported by default. */
    int32_t                                            second_rsrp_in_qdbm; /* CSI-RSRP in qdbm. Only avaliable when camp on NR network, 0x7FFF means invalid. Now invalid value is reported by default. */
    int32_t                                            second_sig3; /* CSI-SINR in qdb. Only avaliable when camp on NR network, 0x7FFF means invalid. Now invalid value is reported by default. */
    uint8_t                                            signal_type; /* N/A */
} mipc_nw_raw_signal_info_struct4 ;

typedef struct mipc_physical_channel_info_struct4 {
    uint32_t                                           rat; /* RAT info. */
    uint8_t                                            status; /* UE and CELL connection status. */
    int32_t                                            cell_bandwidth_downlink; /* Downlink bandwidth for cell. */
    int32_t                                            channel_number; /*  */
    int32_t                                            num_cids; /*  */
    uint32_t                                           physical_cell_id; /*  */
} mipc_physical_channel_info_struct4 ;

typedef struct mipc_physical_channel_info_v1_struct4 {
    uint32_t                                           rat; /* RAT info. */
    uint8_t                                            status; /* UE and CELL connection status. */
    int32_t                                            cell_bandwidth_downlink; /* Downlink bandwidth for cell. */
    int32_t                                            cell_bandwidth_uplink; /* Uplink bandwidth for cell. */
    int32_t                                            downlink_channel_number; /* downlink channel number */
    int32_t                                            uplink_channel_number; /* uplink channel number */
    int32_t                                            num_cids; /*  */
    uint32_t                                           physical_cell_id; /*  */
    uint32_t                                           band; /*  */
    uint32_t                                           frequency_range; /*  */
} mipc_physical_channel_info_v1_struct4 ;

typedef struct mipc_nw_name_pair_struct4 {
    char                                               short_name[MIPC_MAX_NETWORK_NAME_LEN]; /* N/A */
    char                                               long_name[MIPC_MAX_NETWORK_NAME_LEN]; /* N/A */
} mipc_nw_name_pair_struct4 ;

typedef struct mipc_nw_suggested_struct4 {
    uint8_t                                            state; /* 0: unknown, 1: available, 2: current, 3: forbidden */
    char                                               network_long_name[60]; /* Network long Name, format: ASCII */
    char                                               network_short_name[60]; /* Network short Name, format: ASCII */
    char                                               plmn_id[MIPC_MAX_PLMN_ID_LEN]; /* PLMN id, format: ASCII (Number: 0-9) */
    char                                               lac[10]; /* Location area code. */
    uint32_t                                           act; /* Bit 0: GSM_AcTn; 0, not selected; 1 selected;
            Bit 1: GSM_Compact_AcTn; 0, not selected; 1 selected;
            Bit 2: UTRAN_AcTn; 0, not selected; 1 selected;
            Bit 3: E-UTRAN_AcTn; 0, not selected; 1 selected;
            0 GSM
            1 GSM Compact
            2 UTRAN
            3 GSM w/EGPRS (see NOTE 1)
            4 UTRAN w/HSDPA (see NOTE 2)
            5 UTRAN w/HSUPA (see NOTE 2)
            6 UTRAN w/HSDPA and HSUPA (see NOTE 2)
            7 E-UTRAN
            8 EC-GSM-IoT (A/Gb mode) (see NOTE 3)
            9 E-UTRAN (NB-S1 mode) (see NOTE 4)
            10 E-UTRA connected to a 5GCN (see NOTE 5)
            11 NR connected to a 5GCN (see NOTE 5)
            12 NG-RAN
            13 E-UTRA-NR dual connectivity
 */
} mipc_nw_suggested_struct4 ;

typedef struct mipc_nw_arfcn_struct4 {
    uint32_t                                           arfcn[10]; /* N/A */
} mipc_nw_arfcn_struct4 ;

typedef struct mipc_nw_femtocell_info_struct4 {
    char                                               plmn_id[MIPC_MAX_PLMN_ID_LEN]; /* id of the plmn */
    char                                               oper_long_name[MIPC_MAX_NETWORK_NAME_LEN]; /* oper_long_name of the femtocell */
    char                                               oper_short_name[MIPC_MAX_NETWORK_NAME_LEN]; /* oper_short_name of the femtocell */
    uint8_t                                            act; /* the act of the femtocell;value is 0(GSM)/2(UMTS)/7(LTE). */
    uint8_t                                            num_csg; /* the num_csg of the femtocell. */
    uint32_t                                           csg_id; /* the csg id of the femtocell. */
    uint8_t                                            csg_type; /* the csg type of the femtocell. */
    char                                               hnb_name[50]; /* the hnb_name of the femtocell. */
    char                                               sig[7]; /* the sig of the femtocell */
} mipc_nw_femtocell_info_struct4 ;

typedef struct mipc_nw_pseudocell_info_struct4 {
    uint8_t                                            type; /* the type of the pseudocell. */
    char                                               plmn[MIPC_MAX_PLMN_ID_LEN]; /* the plmn id of the pseudocell. */
    char                                               long_name[MIPC_MAX_NETWORK_NAME_LEN]; /* the plmn long name of the pseudocell. */
    char                                               short_name[MIPC_MAX_NETWORK_NAME_LEN]; /* the plmn short name of the pseudocell. */
    uint32_t                                           lac; /* the lac of the pseudocell. */
    uint64_t                                           cell_id; /* the cell id of the pseudocell. */
    uint16_t                                           arfcn; /* the arfcn of the pseudocell. */
    uint8_t                                            bsic; /* the bsic of the pseudocell. */
    char                                               si3_raw_data[50]; /* the si3_raw_data of the pseudocell. */
} mipc_nw_pseudocell_info_struct4 ;

typedef struct mipc_nw_barring_info_struct4 {
    uint16_t                                           service_type; /* indicates the service type of the barring service. */
    uint8_t                                            barring_type; /* indicates the type of barring applied to the service. 0: NONE, 1: CONDITIONAL, 2: UNCONDITIONAL. */
    uint8_t                                            factor; /* indicates the barring factor as a percentage 0-100. */
    uint16_t                                           time_seconds; /* indicates the number of seconds between re-evaluations of barring. */
    uint8_t                                            is_barred; /* indicates whether barring is currently being applied. */
} mipc_nw_barring_info_struct4 ;

typedef struct mipc_nw_threshold_array_struct4 {
    uint8_t                                            num_of_threshold; /* The num of threshold. Maximum 10. A value of 0 disables the use of thresholds for reporting. */
    int32_t                                            threshold_dbm[10]; /* An array of trigger thresholds in dBm. */
} mipc_nw_threshold_array_struct4 ;

typedef struct mipc_nw_extend_provider_struct4 {
    uint32_t                                           index; /* Network index in the SIM Preferred network list. */
    uint32_t                                           stat; /* 0: unknown, 1: available, 2: current, 3: forbidden */
    char                                               oper_long_name[60]; /* oper long name, format: ASCII */
    char                                               oper_short_name[60]; /* oper short name, format: ASCII */
    char                                               oper_numeric_name[MIPC_MAX_PLMN_ID_LEN]; /* oper numeric name, format: ASCII */
    uint8_t                                            padding[1]; /* N/A */
    char                                               lac[20]; /* location info, format: ASCII */
    uint32_t                                           act; /* please refer to NW_ACT_TYPE */
    uint32_t                                           csq_rssi; /* coded value. */
    uint32_t                                           register_state; /* register state */
    uint32_t                                           timestamp_type; /* timestamp type */
    int32_t                                            timestamp; /* timestamp */
    uint32_t                                           connection_stat; /* connection state */
    char                                               cell_id[20]; /* cell id */
    uint32_t                                           freq; /* freq */
    int32_t                                            bsic_psc_cpid_pci; /* BSIC/PSC/CPID/PCI */
    int32_t                                            sig2; /* sig2 */
    int32_t                                            sig3; /* sig3 */
    int32_t                                            sig4; /* sig4 */
    int32_t                                            sig5; /* sig5 */
    uint32_t                                           bit_error_rat; /* bit error rat */
    uint32_t                                           timing_advance; /* timing advance */
    uint32_t                                           cqi; /* CQI */
} mipc_nw_extend_provider_struct4 ;

typedef struct mipc_nw_ecainfo_struct4 {
    uint32_t                                           ca_info; /* indicate the CA state. 0: CA CONFIGURED, 1: CA NOT CONFIGURED, 2: CA ACTIVE, 3: CA DEACTIVATED */
    uint32_t                                           pcell_bw; /* indicate pcell bandwidth */
    uint32_t                                           scell_bw1; /* indicate first scell bandwidth */
    uint32_t                                           scell_bw2; /* indicate second scell bandwidth */
    uint32_t                                           scell_bw3; /* indicate third scell bandwidth */
    uint32_t                                           scell_bw4; /* indicate fourth scell bandwidth */
} mipc_nw_ecainfo_struct4 ;

typedef struct mipc_1xrtt_cell_info_struct4 {
    int32_t                                            sid; /*  */
    int32_t                                            nid; /*  */
    int32_t                                            bsid; /*  */
} mipc_1xrtt_cell_info_struct4 ;

typedef struct mipc_band_combo_info_struct4 {
    char                                               band_combo[MIPC_MAX_BAND_COMBO_LEN]; /* band combo */
} mipc_band_combo_info_struct4 ;

typedef struct mipc_nw_ca_band_struct4 {
    uint32_t                                           ca_band_class[8]; /* CA band: bitmask, ca_band_class[0]'s bit0~bit31 indicating band1~band32, ca_band_class[1]'s bit0~bit31 band33~band64 and so on */
} mipc_nw_ca_band_struct4 ;

typedef struct mipc_nw_tuw_info_struct4 {
    uint8_t                                            tuw_id; /* 1: TUW1, 2: TUW2, 3: TUW3 */
    uint32_t                                           tuw_length; /* TUW1: 0~30 seconds, default setting of 3 seconds.  TUW2: 0~120 seconds, default setting of 60 seconds.  TUW3: 0~30 seconds, default setting of 2 seconds. */
} mipc_nw_tuw_info_struct4 ;

typedef struct mipc_nr_ca_band_struct4 {
    int32_t                                            band[10]; /* the nr ca band. Pcell always at band[0] if 2 or more bands present. */
} mipc_nr_ca_band_struct4 ;

typedef struct mipc_nw_record_info_struct4 {
    uint32_t                                           rat; /* 1: GSM, 2: UMTS, 4: LTE, 128: NR, refer to NW_SCAN_RAT */
    uint32_t                                           num_band; /* 0~8, 0 means search all supported bands */
    uint32_t                                           band[8]; /* band, 0~1024 */
    uint32_t                                           num_channel; /* 0~32, 0 means search all channels */
    uint32_t                                           channel[32]; /* arfcn, 0~3279165 */
} mipc_nw_record_info_struct4 ;

typedef struct mipc_nw_plmn_info_struct4 {
    char                                               plmn_id[MIPC_MAX_PLMN_ID_LEN]; /* plmn id */
} mipc_nw_plmn_info_struct4 ;

typedef struct mipc_nw_scan_info_struct4 {
    uint32_t                                           rat; /* 1: GSM, 2: UMTS, 4: LTE, 128: NR, refer to NW_SCAN_RAT */
    int32_t                                            xarfcn; /* arfcn for GSM, uarfcn for UMTS, earfcn for LTE, nrarfcn for NR */
    int32_t                                            pcid; /* BSIC for GSM, PSC(Primary scrambling code) for UMTS, PCI(Physical cell ID) for LTE and NR */
    char                                               plmn_id[MIPC_MAX_PLMN_ID_LEN]; /* plmn id */
    char                                               cell_id[MIPC_MAX_CELL_ID_LEN]; /*  cell ID */
    char                                               lac_or_tac[20]; /* LAC for GSM and UMTS, TAC for LTE and NR */
    int32_t                                            plmn_status; /* 0: invalid, 1: available, 2: current, 3: forbidden, refer to NW_PLMN_STATUS */
    int32_t                                            registered; /* 0: not registered, 1: registered, refer to NW_REGISTER_STATUS */
    int32_t                                            srv_cell_status; /* 0: none, 1: primary serving cell, 2: secondary serving cell, refer to NW_SRV_CELL_STATUS */
    int32_t                                            sig1; /* GSM: rxlev, WCDMA: rxlev, TDSCDMA : rssi in dbm, LTE: rxlev, NR: ss-rsrp in rxlev */
    int32_t                                            sig2; /* GSM: rssi in qdbm, UMTS: rssi in qdbm, LTE: rssi in qdbm, NR: ss-rsrq in rxlev */
    int32_t                                            sig3; /* GSM: N/A, WCDMA: rscp, TDSCDMA: N/A, LTE: rsrp in qdbm, NR: ss-rsrp in qdbm */
    int32_t                                            sig4; /* GSM: N/A, WCDMA: ecno, TDSCDMA: N/A, LTE: rsrq in qdbm, NR: ss-rsrq in qdbm */
    int32_t                                            sig5; /* GSM: N/A, UMTS: N/A, LTE: snr in qdbm, NR: ss-snr in qdbm */
} mipc_nw_scan_info_struct4 ;

typedef struct mipc_os_id_info_struct4 {
    uint8_t                                            os_id[MIPC_UE_OS_ID_LEN]; /* the os_id info of the update or set. */
} mipc_os_id_info_struct4 ;

typedef struct mipc_sim_msisdn_struct4 {
    uint8_t                                            msisdn[24]; /* N/A */
} mipc_sim_msisdn_struct4 ;

typedef struct mipc_sim_pin_desc_struct4 {
    uint8_t                                            pin_mode; /* pin mode */
    uint8_t                                            pin_format; /* pin format */
    uint8_t                                            pin_len_min; /* minimum pin length */
    uint8_t                                            pin_len_max; /* maximum pin length */
} mipc_sim_pin_desc_struct4 ;

typedef struct mipc_sim_app_info_struct4 {
    uint8_t                                            app_type; /* The type of the UICC application. */
    uint8_t                                            app_id_len; /* The length of the UICC application id. */
    uint8_t                                            sim_app_id[MIPC_MAX_SIM_AID_BYTE_LEN]; /* The UICC application id. */
    uint8_t                                            name_len; /* The  length of application name. */
    uint8_t                                            name[32]; /* Application name. */
    uint8_t                                            num_of_pins; /* num of pins,only support PIN1, not support UPIN,max num is 8. */
    uint8_t                                            pin_ref[8]; /* pin ref, not support different application keys for different applications,maxnum is 8. */
} mipc_sim_app_info_struct4 ;

typedef struct mipc_sim_slots_info_struct4 {
    char                                               card_state[20]; /* AT+CPIN? response */
    uint8_t                                            slots_state; /* slots state of physical slots: 0 means inactive, 1 means active */
    uint8_t                                            logical_idx; /* logical slots index of physical slot */
    uint8_t                                            padding[2]; /* N/A */
    char                                               atr[MIPC_MAX_ATR_LEN]; /* the atr of the card  */
    char                                               eid[MIPC_MAX_SIM_EID_LEN]; /* the eid of the card  */
    char                                               iccid[MIPC_SIM_FIX_ICCID_LEN]; /* sim iccid of the iccid */
} mipc_sim_slots_info_struct4 ;

typedef struct mipc_app_status_desc_struct4 {
    uint8_t                                            app_type; /* application type */
    uint8_t                                            app_state; /* application state */
    uint8_t                                            pin_status; /* same to cpin state */
    uint8_t                                            sub_status; /* application sub status */
    uint8_t                                            pin1_replaced; /* pin1 applied to all applications */
    uint8_t                                            pin1_state; /* pin1 state */
    uint8_t                                            pin2_state; /* pin2 state */
    uint8_t                                            padding; /* N/A */
    char                                               aid[41]; /* aid (MAX_SIM_AID_STR_LEN+1) */
    uint8_t                                            padding2[3]; /* N/A */
    char                                               app_label[33]; /* application label (MAX_SIM_APP_LABEL_LEN+1) */
    uint8_t                                            padding3[3]; /* N/A */
} mipc_app_status_desc_struct4 ;

typedef struct mipc_file_list_struct4 {
    char                                               path[9]; /* path id + file id */
    char                                               data[50]; /* SW1SW2+ data string */
} mipc_file_list_struct4 ;

typedef struct mipc_sid_nid_list_struct4 {
    char                                               sid[6]; /* sid */
    uint8_t                                            padding[2]; /* N/A */
    char                                               nid[6]; /* nid */
} mipc_sid_nid_list_struct4 ;

typedef struct mipc_sim_carrier_struct_struct4 {
    char                                               mcc[4]; /* mcc */
    char                                               mnc[4]; /* mnc */
    uint8_t                                            match_cat; /* carrier match type */
    char                                               match_data[21]; /* SPN/IMSI Prefix/GID1/GID2 data. For match cat 0, data is null */
} mipc_sim_carrier_struct_struct4 ;

typedef struct mipc_sms_pdu_struct4 {
    uint16_t                                           message_index; /* message index */
    uint8_t                                            pdu_len; /* the length of TPDU(without sca) */
    uint8_t                                            status; /* message status */
    uint8_t                                            sms_class; /* message class */
    uint8_t                                            padding[3]; /* N/A */
    uint8_t                                            pdu[256]; /* pdu contains sca and tpdu */
} mipc_sms_pdu_struct4 ;

typedef struct mipc_ss_call_forward_struct4 {
    uint8_t                                            call_forward_status; /* call forward status, active or not active */
    char                                               dial_number[MIPC_MAX_SS_DIAL_NUMBER_FOR_ALIGN_LEN]; /* dial number */
    uint16_t                                           service_class; /* service class */
    uint16_t                                           type_of_address; /* type of address, normal or international */
    uint8_t                                            padding[3]; /* padding for align */
    uint8_t                                            timer; /* timer, 1-30 */
    uint8_t                                            reason; /* call forward reason to query from req */
    uint8_t                                            padding1[3]; /* padding for align */
    char                                               time_slot_begin[MIPC_MAX_SS_COMM_INFO_LEN]; /* time slot begin of call forward */
    char                                               time_slot_end[MIPC_MAX_SS_COMM_INFO_LEN]; /* time slot end of call forward */
} mipc_ss_call_forward_struct4 ;

typedef struct mipc_ss_call_waiting_struct4 {
    uint8_t                                            call_waiting_status; /* call waiting status, active or not active */
    uint8_t                                            padding; /* padding for align */
    uint16_t                                           service_class; /* call waiting service class */
} mipc_ss_call_waiting_struct4 ;

typedef struct mipc_sys_mapping_struct4 {
    uint32_t                                           ps_id; /* N/A */
} mipc_sys_mapping_struct4 ;

typedef struct mipc_sys_lte_band_struct4 {
    uint32_t                                           lte_band_class[8]; /* LTE band: bitmask, lte_band_class[0]'s bit0~bit31 indicating band1~band32, lte_band_class[1]'s bit0~bit31 band33~band64, and so on. */
} mipc_sys_lte_band_struct4 ;

typedef struct mipc_sys_nr_band_struct4 {
    uint32_t                                           nr_band_class[32]; /* Bands for NR: bitmask, nr_band_class[0]'s bit0~bit31 indicating band1~band32, nr_band_class[1]'s bit0~bit31 band33~band64 and so on */
} mipc_sys_nr_band_struct4 ;

typedef struct mipc_sys_thermal_sensor_config_struct4 {
    uint32_t                                           enable; /*  */
    uint32_t                                           sensor_id; /*  */
    uint32_t                                           alarm_id; /*  */
    int32_t                                            threshold; /*  */
    uint32_t                                           hysteresis; /*  */
    uint32_t                                           interval; /*  */
    uint32_t                                           alarm_type; /*  */
} mipc_sys_thermal_sensor_config_struct4 ;

typedef struct mipc_sys_thermal_sensor_config_e_struct4 {
    uint32_t                                           enable; /*  */
    uint32_t                                           sensor_id; /*  */
    uint32_t                                           alarm_id; /*  */
    int32_t                                            threshold; /*  */
    uint32_t                                           hysteresis; /*  */
    uint32_t                                           interval; /*  */
    uint32_t                                           alarm_type; /*  */
} mipc_sys_thermal_sensor_config_e_struct4 ;

typedef struct mipc_sys_thermal_actuator_state_info_struct4 {
    uint32_t                                           actuator_id; /* actuator_id */
    uint32_t                                           num_throttling_state; /* num_throttling_state */
    uint32_t                                           current_throttling_state; /* current_throttling_state */
} mipc_sys_thermal_actuator_state_info_struct4 ;

typedef struct mipc_sys_thermal_sensor_info_struct4 {
    uint32_t                                           sensor_id; /* sensor id */
    int32_t                                            temperature; /* current temperature */
} mipc_sys_thermal_sensor_info_struct4 ;

typedef struct mipc_sys_thermal_sensor_info_e_struct4 {
    uint32_t                                           sensor_id; /* sensor id */
    int32_t                                            temperature; /* current temperature */
} mipc_sys_thermal_sensor_info_e_struct4 ;

typedef struct mipc_sys_thermal_trip_map_struct4 {
    uint32_t                                           val_trip_map; /* N/A */
    int32_t                                            threshold_value; /* N/A */
    uint32_t                                           hysteresis_value; /* N/A */
    uint32_t                                           sampling_period; /* N/A */
    uint32_t                                           sensor_alarm_type; /* N/A */
    uint32_t                                           throttle_level; /* N/A */
} mipc_sys_thermal_trip_map_struct4 ;

typedef struct mipc_sys_thermal_trip_change_struct4 {
    uint32_t                                           sensor_id; /* N/A */
    int32_t                                            before_trip_temp; /* N/A */
    int32_t                                            after_trip_temp; /* N/A */
    uint32_t                                           save_cfg_to_nv; /* 0->no, others->yes */
} mipc_sys_thermal_trip_change_struct4 ;

typedef struct mipc_call_detail_info_struct4 {
    uint8_t                                            number_present; /* This parameter can provide details why <number> does not contain a calling party BCD number (refer 3GPP TS 24.008 [8] subclause 10.5.4.30). */
    uint8_t                                            padding[3]; /* Reserved */
    char                                               number[MIPC_MAX_CALL_NUMBER_LEN]; /* call number */
    uint8_t                                            name_present; /* this field don't support MIPC_CALL_CNI_VALIDITY_CNI_PAYPHONE and MPIC_CALL_CNI_VALIDITY_CNI_OTHERS */
    uint8_t                                            padding2[3]; /* Reserved */
    char                                               name[MIPC_MAX_CALL_NAME_LEN]; /* call name */
    char                                               display_name[MIPC_MAX_CALL_DISPLAY_NAME_LEN]; /* display name */
    char                                               verstat[MIPC_MAX_CALL_VERSTAT_LEN]; /* verstat */
    char                                               privacy[MIPC_MAX_CALL_PRIVACY_LEN]; /* privacy */
} mipc_call_detail_info_struct4 ;

typedef struct mipc_call_video_cap_struct4 {
    uint8_t                                            local_video_cap_present; /* This field will be always TRUE currently */
    uint8_t                                            local_video_cap; /* local video capability */
    uint8_t                                            remote_video_cap_present; /* this field will be TRUE after IMS call connected  */
    uint8_t                                            remote_video_cap; /* 1 for remote UE video-capable, 0 for remote UE no video-capble. If video feature tag is included in received SIP messages, then this value is set to 1 */
} mipc_call_video_cap_struct4 ;

typedef struct mipc_ecc_info_struct4 {
    uint8_t                                            is_fake_ecc; /*  */
    uint8_t                                            padding[3]; /*  */
    uint16_t                                           category; /* A bitmap indicating the Emergency Service Category Value according to 3GPP TS 24.008 */
    uint16_t                                           type; /*  */
    char                                               number[MIPC_MAX_CALL_ECC_NUMBER_LEN]; /*  */
    uint8_t                                            padding2[2]; /*  */
} mipc_ecc_info_struct4 ;

typedef struct mipc_nw_srxlev_info_struct4 {
    uint16_t                                           srxlev_in_qdb; /* srxlev in qdb value */
    uint16_t                                           squal_in_qdb; /* squal in qdb value */
} mipc_nw_srxlev_info_struct4 ;

typedef struct mipc_phb_name_str_struct4 {
    char                                               name_str[168]; /* phb name string. */
    uint32_t                                           encode_method; /* phb name string encode method. */
} mipc_phb_name_str_struct4 ;

typedef struct mipc_phb_email_str_struct4 {
    char                                               name_str[248]; /* phb name string. */
    uint32_t                                           encode_method; /* phb name string encode method. */
} mipc_phb_email_str_struct4 ;

typedef struct mipc_phb_anr_entry_struct4 {
    uint32_t                                           type; /* type of the entry,refer to storage type. */
    uint32_t                                           index; /* the stored index of the entry */
    uint32_t                                           ton; /* type of the number. */
    char                                               number[40]; /* number string. */
} mipc_phb_anr_entry_struct4 ;

typedef struct mipc_phb_entry_struct4 {
    uint32_t                                           index; /* the stored index of the entry */
    uint32_t                                           ton; /* type of the number. */
    char                                               number[40]; /* number string. */
    char                                               alphaID[168]; /* alphaID string. */
    char                                               adnumber[40]; /* additional number string. */
    uint32_t                                           adtype; /* additional number type. */
    char                                               email[248]; /* email string. */
    uint32_t                                           encode_method; /* encode method type. */
} mipc_phb_entry_struct4 ;

typedef struct mipc_embms_area_id_info_struct4 {
    uint8_t                                            num_area_ids; /* The number of MBSFN area IDs available. Range is from 1 to 8. */
    uint8_t                                            padding1[3]; /* padding. */
    uint8_t                                            area_id[8]; /* MBSFN area ID. Range is from 0 to 255. */
} mipc_embms_area_id_info_struct4 ;

typedef struct mipc_embms_session_info_struct4 {
    uint16_t                                           index; /* The index of MBMS session. */
    uint8_t                                            padding1[2]; /* padding. */
    char                                               tmgi[13]; /* TMGI(Temporary Mobile Group Identity)in position x in the list. It is represented in the form of a string of 11 or 12 hex digits. */
    uint8_t                                            padding2[3]; /* padding. */
    char                                               session_id[3]; /* Session ID in position x in the list. It is represented in the form of a string of 2 hex digits. */
    uint8_t                                            status; /* Status of the MBMS session. 0:MBMS session available(TMGI/Session ID present in MCCH), 1:MBMS session activated(modem receiving MTCH data). */
} mipc_embms_session_info_struct4 ;

typedef struct mipc_embms_nb_req_info_struct4 {
    uint8_t                                            num_nf; /* The number of neighboring frequencies. Range is from 0 to 8. */
    uint8_t                                            index; /* The index of neighboring frequency. Range is from 1 to 8. */
    uint8_t                                            padding1[2]; /* padding. */
    uint32_t                                           nf; /* The neighboring frequency. */
    uint8_t                                            num_bands_nf; /* The number of neighboring frequency band in the list. Range is from 0 to 8. */
    uint8_t                                            padding2[3]; /* padding. */
    uint16_t                                           band_nf[8]; /* The neighboring frequency band. Range is from 0 to 256. */
    uint8_t                                            num_sais_nf; /* The number of SAIs in the list for neighbor frequency. Range is from 0 to 64? */
    uint8_t                                            padding3[3]; /* padding. */
    uint16_t                                           sai_nf[64]; /* The SAIs in SAI list for neighbor frequency. Range is from 0 to 65535. */
} mipc_embms_nb_req_info_struct4 ;

typedef struct mipc_embms_sai_cf_info_struct4 {
    uint8_t                                            num_intra_freq; /* The number of intra frequencies. Range is from 0 to 2. */
    uint8_t                                            padding1[3]; /* padding. */
    uint32_t                                           intra_freq[2]; /* Intra frequencys. Range is from 0 to 262143. */
    uint8_t                                            num_sais; /* The number of SAIs in the list. Range is from 1 to 64. */
    uint8_t                                            padding2[3]; /* padding. */
    uint16_t                                           sais[64]; /* The SAIs in SAI list. Range is from 0 to 65535. */
} mipc_embms_sai_cf_info_struct4 ;

typedef struct mipc_embms_sai_nf_info_struct4 {
    uint8_t                                            index; /* The index of neighboring. Range is from 1 to 8. */
    uint8_t                                            padding1[3]; /* padding. */
    uint32_t                                           nf; /* The neighboring frequency . Range is from 0 to 262143. */
    uint8_t                                            num_bands_nf; /* The number of neighboring frequency band in the list. Range is from 0 to 8. */
    uint8_t                                            padding2[3]; /* padding. */
    uint16_t                                           band_nf[8]; /* The SAIs in SAI list. Range is from 0 to 256. */
    uint8_t                                            num_sais_nf; /* The number of SAIs in the list. Range is from 0 to 64. */
    uint8_t                                            padding3[3]; /* padding. */
    uint16_t                                           sai_nf[64]; /* The SAIs in the SAI list. Range is from 0 to 65535. */
} mipc_embms_sai_nf_info_struct4 ;

typedef struct mipc_internal_set_filter_req_struct4 {
    uint8_t                                            nccmni_net_if; /* N/A */
    uint8_t                                            reserve1; /* N/A */
    uint16_t                                           nccmni_seq; /* N/A */
    uint32_t                                           valid_field; /* mandatory, a bitmap, refer to IPC_FILTER_BY_XXX */
    uint8_t                                            ip_type; /* IPC_IP_TYPE_IPV4 or IPC_IP_TYPE_IPV6 */
    uint8_t                                            ctrl_protocol; /* IPC_HDR_PROT_XXX */
    uint16_t                                           src_port; /* N/A */
    uint16_t                                           dst_port; /* N/A */
    uint16_t                                           tcp_flags; /* IPC_HDR_TCP_FLAG_XXX */
    uint32_t                                           spi; /* N/A */
    uint8_t                                            src_v4_addr[4]; /* Source IPv4 address to filter. */
    uint8_t                                            dst_v4_addr[4]; /* Destination IPv4 address to filter. */
    uint8_t                                            src_v6_addr[16]; /* Source IPv6 address to filter. */
    uint8_t                                            dst_v6_addr[16]; /* Destination IPv6 address to filter. */
    uint8_t                                            icmpv4_type; /* Type field of ICMPv4 header to filter. */
    uint8_t                                            icmpv6_type; /* Type field of ICMPv6 header to filter. */
    uint16_t                                           reserve; /* N/A */
    uint32_t                                           features; /* N/A */
} mipc_internal_set_filter_req_struct4 ;

typedef struct mipc_internal_set_filter_cnf_struct4 {
    uint8_t                                            nccmni_net_if; /* N/A */
    uint8_t                                            reserve1; /* N/A */
    uint16_t                                           nccmni_seq; /* N/A */
    int32_t                                            filter_id; /* >=0: filter id, <0: set failed. */
} mipc_internal_set_filter_cnf_struct4 ;

typedef struct mipc_internal_reset_filter_req_struct4 {
    uint8_t                                            nccmni_net_if; /* N/A */
    uint8_t                                            reserve1; /* N/A */
    uint16_t                                           nccmni_seq; /* N/A */
    int32_t                                            is_deregister_all_filter; /* 0: deregister the filter id only, 1: deregister all filter */
    int32_t                                            filter_id; /* filter id to deregister */
} mipc_internal_reset_filter_req_struct4 ;

typedef struct mipc_internal_reset_filter_cnf_struct4 {
    uint8_t                                            nccmni_net_if; /* N/A */
    uint8_t                                            reserve1; /* N/A */
    uint16_t                                           nccmni_seq; /* N/A */
    int32_t                                            is_success; /* 1: success */
} mipc_internal_reset_filter_cnf_struct4 ;

typedef struct mipc_nw_tx_struct4 {
    uint32_t                                           tx[5]; /* N/A */
} mipc_nw_tx_struct4 ;

typedef struct mipc_sys_modem_struct8 {
    uint64_t                                           modem_id; /* modem_id:64bit,constant across reboots or device removal and insertion */
    uint32_t                                           executor_number; /* executor number */
    uint32_t                                           sim_number; /* sim number */
    uint32_t                                           concurrency; /* dual standby:1, dual active:2  */
    uint8_t                                            padding[4]; /* N/A */
} mipc_sys_modem_struct8 ;

typedef struct mipc_sys_adpclk_freq_info_struct8 {
    uint64_t                                           center_frequency; /*  */
    uint32_t                                           frequency_spread; /*  */
    uint32_t                                           noise_power; /*  */
    uint32_t                                           relative_signal_strength; /*  */
    uint32_t                                           connect_status; /*  */
} mipc_sys_adpclk_freq_info_struct8 ;

#pragma pack (pop)


#endif /* __MIPC_MSG_TLV_CONST_H__ */
