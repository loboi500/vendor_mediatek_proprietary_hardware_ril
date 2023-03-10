/* Copyright Statement:
 *
 * This software/firmware and related documentation (IMS_CONFIG_"MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 *
 * MediaTek Inc. (IMS_CONFIG_C) 2018. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS (IMS_CONFIG_"MEDIATEK SOFTWARE")
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
 * The following software/firmware and/or related documentation (IMS_CONFIG_"MediaTek Software")
 * have been modified by MediaTek Inc. All revisions are subject to any receiver's
 * applicable license agreements with MediaTek Inc.
 */

#ifndef RIL_OP07IMSCONFIGDATA_H
#define RIL_OP07IMSCONFIGDATA_H

#define CONFIG_VALUE(x,y,z) {ImsConfigItem::x,y,z},

CONFIG_VALUE(IMS_CONFIG_PUBLISH_TIMER,IMS_CONFIG_UNIT_SECONDS,"3600")
CONFIG_VALUE(IMS_CONFIG_PUBLISH_TIMER_EXTENDED,IMS_CONFIG_UNIT_SECONDS,"0")
CONFIG_VALUE(IMS_CONFIG_CAPABILITIES_CACHE_EXPIRATION,IMS_CONFIG_UNIT_SECONDS,"21600")
CONFIG_VALUE(IMS_CONFIG_AVAILABILITY_CACHE_EXPIRATION,IMS_CONFIG_UNIT_SECONDS,"60")
CONFIG_VALUE(IMS_CONFIG_CAPABILITIES_POLL_INTERVAL,IMS_CONFIG_UNIT_SECONDS,"0")
CONFIG_VALUE(IMS_CONFIG_SOURCE_THROTTLE_PUBLISH,IMS_CONFIG_UNIT_MILLISECONDS,"30000")
CONFIG_VALUE(IMS_CONFIG_MAX_NUMENTRIES_IN_RCL,IMS_CONFIG_UNIT_NONE,"100")
CONFIG_VALUE(IMS_CONFIG_CAPAB_POLL_LIST_SUB_EXP,IMS_CONFIG_UNIT_SECONDS,"30")
CONFIG_VALUE(IMS_CONFIG_CAPABILITY_DISCOVERY_ENABLED,IMS_CONFIG_UNIT_NONE,"1")


#endif //RIL_OP07IMSCONFIGDATA_H
