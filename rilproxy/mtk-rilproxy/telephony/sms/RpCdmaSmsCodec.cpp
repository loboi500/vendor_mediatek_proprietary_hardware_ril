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

/*****************************************************************************
 * Include
 *****************************************************************************/
#include "RpCdmaSmsCodec.h"
#include <cutils/jstring.h>
#include <time.h>
#include <cutils/properties.h>
#include <telephony/ril_cdma_sms.h>

#define USER_DATA_ENCODING_BITS        5
#define USER_DATA_NUM_FIELDS_BITS      8
#define CDMA_SMS_SEPTETS_BITS          7
#define CDMA_SMS_OCTETS_BITS           8

/*****************************************************************************
 * Class RpCdmaSmsCodec
 *****************************************************************************/
RFX_IMPLEMENT_CLASS("RpCdmaSmsCodec", RpCdmaSmsCodec, RfxObject);

RpCdmaSmsCodec::RpCdmaSmsCodec() :
    mDebug(true) {
}

void RpCdmaSmsCodec::onInit() {
    // Required: invoke super class implementation
    RfxObject::onInit();

    log(String8("onInit"));
}

bool RpCdmaSmsCodec::decodeRilCdmaSmsMsg(Parcel *pData, RIL_CDMA_SMS_Message *rilCdmaSmsMsg) {
    logDecode(String8("decodeRilCdmaSmsMsg"));
    bool result = false;

    if (rilCdmaSmsMsg == NULL) {
        logDecode(String8("rilCdmaSmsMsg is null pointer!"));
        return false;
    }

    // FIXME
    // Parcel used data
    int32_t  t = 0;
    uint8_t ut = 0;
    status_t status;
    int32_t digitCount;
    int digitLimit;
    /**
     * decode as RIL_CDMA_SMS_Message, copied from constructCdmaSms@Ril.cpp.
     * It should be changed as cpp coding style in the future.
     */
    memset(rilCdmaSmsMsg, 0, sizeof(RIL_CDMA_SMS_Message));
    status = pData->readInt32(&t);
    rilCdmaSmsMsg->uTeleserviceID = (int) t;

    status = pData->read(&ut,sizeof(ut));
    rilCdmaSmsMsg->bIsServicePresent = (uint8_t) ut;

    status = pData->readInt32(&t);
    rilCdmaSmsMsg->uServicecategory = (int) t;

    status = pData->readInt32(&t);
    rilCdmaSmsMsg->sAddress.digit_mode = (RIL_CDMA_SMS_DigitMode) t;

    status = pData->readInt32(&t);
    rilCdmaSmsMsg->sAddress.number_mode = (RIL_CDMA_SMS_NumberMode) t;

    status = pData->readInt32(&t);
    rilCdmaSmsMsg->sAddress.number_type = (RIL_CDMA_SMS_NumberType) t;

    status = pData->readInt32(&t);
    rilCdmaSmsMsg->sAddress.number_plan = (RIL_CDMA_SMS_NumberPlan) t;

    status = pData->read(&ut,sizeof(ut));
    rilCdmaSmsMsg->sAddress.number_of_digits= (uint8_t) ut;

    digitLimit= min((rilCdmaSmsMsg->sAddress.number_of_digits), RIL_CDMA_SMS_ADDRESS_MAX);
    for(digitCount =0 ; digitCount < digitLimit; digitCount ++) {
        status = pData->read(&ut,sizeof(ut));
        rilCdmaSmsMsg->sAddress.digits[digitCount] = (uint8_t) ut;
    }

    status = pData->readInt32(&t);
    rilCdmaSmsMsg->sSubAddress.subaddressType = (RIL_CDMA_SMS_SubaddressType) t;

    status = pData->read(&ut,sizeof(ut));
    rilCdmaSmsMsg->sSubAddress.odd = (uint8_t) ut;

    status = pData->read(&ut,sizeof(ut));
    rilCdmaSmsMsg->sSubAddress.number_of_digits = (uint8_t) ut;

    digitLimit= min((rilCdmaSmsMsg->sSubAddress.number_of_digits), RIL_CDMA_SMS_SUBADDRESS_MAX);
    for(digitCount =0 ; digitCount < digitLimit; digitCount ++) {
        status = pData->read(&ut,sizeof(ut));
        rilCdmaSmsMsg->sSubAddress.digits[digitCount] = (uint8_t) ut;
    }

    status = pData->readInt32(&t);
    rilCdmaSmsMsg->uBearerDataLen = (int) t;

    digitLimit= min((rilCdmaSmsMsg->uBearerDataLen), RIL_CDMA_SMS_BEARER_DATA_MAX);
    for(digitCount =0 ; digitCount < digitLimit; digitCount ++) {
        status = pData->read(&ut, sizeof(ut));
        rilCdmaSmsMsg->aBearerData[digitCount] = (uint8_t) ut;
    }

    if (status == NO_ERROR) {
        logEncode(String8("Decode to RIL_CDMA_SMS_Message completed"));
        result = true;
    } else {
        logEncode(String8::format("Decode to RIL_CDMA_SMS_Message failed, status = %d", status));
        // return empty string as error
        result = false;
    }

    return result;
}

String8 RpCdmaSmsCodec::encodeC2kcmgs(RIL_CDMA_SMS_Message *rilCdmaSmsMsg) {
    logEncode(String8("encodeC2kcmgs"));
    String8 hexPdu;
    String8 number;
    if (!RpCdmaSmsConverter::toHexPdu(*rilCdmaSmsMsg, hexPdu, number)) {
        return String8("");
    }

    String8 pduString8 = String8::format("AT+C2KCMGS=%d,\"%s\",\"%s\"", (int)hexPdu.length() / 2,
            hexPdu.string(),
            number.string());

    logEncode(pduString8);
    return pduString8;
}

RpCdmaSmsLocalReqRsp RpCdmaSmsCodec::decodelocalReq(const sp<RfxMessage>& message) {
    logDecode(String8("decodelocalReq"));

    int32_t numStrings;
    message->getParcel()->readInt32(&numStrings);
    String8 userDataType = String8(message->getParcel()->readString16());
    String8 rspAt = String8(message->getParcel()->readString16());
    RpCdmaSmsLocalReqRsp result;

    logDecode(String8::format("Request error: %d", message->getError()));
    logDecode(String8::format("User data type: %s", userDataType.string()));
    logDecode(String8::format("Response at commands: %s", rspAt.string()));

    if (userDataType == String8(CDMA_SMS_LOCAL_USER_DATA_MO_SMS)) {
        result.setType(CDMA_SMS_LOCAL_REQ_CMGS_RSP);
        if (message->getError() != RIL_E_SUCCESS) {
            result.setResult(false);
            result.setErrorCode(message->getError());
        } else {
            // Decode the error string
            if (rspAt.contains("+C2KCMGS:")) {
                // success
                // remove prefix
                rspAt.removeAll("+C2KCMGS:");
                // remove spaces
                rspAt.removeAll(" ");
                result.setResult(true);
                // get the message id
                result.setId(atoi(rspAt.string()));
                logDecode(String8::format("Message reference/id: %d", result.getId()));
                result.setErrorCode(RIL_E_SUCCESS);
            } else if (rspAt.contains("+C2K ERROR:")) {
                // +C2K ERROR:<error_class>, <error_cause>
                // remove prefix
                rspAt.removeAll("+C2K ERROR:");
                // remove spaces
                rspAt.removeAll(" ");
                result.setResult(false);
                // get the error code
                char *token;
                char* savePtr = NULL;
                token = strtok_r((char *)rspAt.string(), ",", &savePtr);
                result.setErrorClass(atoi(token));
                logDecode(String8::format("Error class: %d", result.getErrorClass()));
                // get the error class
                token = strtok_r(NULL, ",", &savePtr);
                result.setErrorCode(atoi(token));
                logDecode(String8::format("Error code: %d", result.getErrorCode()));
            } else {
                // No +C2KCMGS or +C2K ERROR
                result.setResult(false);
                result.setErrorCode(RIL_E_GENERIC_FAILURE);
            }
        }
    } else if (userDataType == String8(CDMA_SMS_LOCAL_USER_DATA_MT_CNMA)) {
        result.setType(CDMA_SMS_LOCAL_REQ_CNMA_RSP);
        if (message->getError() == RIL_E_SUCCESS) {
            result.setResult(true);
        } else {
            result.setResult(false);
        }
        result.setErrorCode(message->getError());
    }

    return result;
}

RpCdmaSmsMtUrc RpCdmaSmsCodec::decodeC2kcmtUrc(Parcel *pUrcData,
        RIL_CDMA_SMS_Message *rilCdmaSmsMsg) {
    logDecode(String8("decodeC2kcmtUrc"));
    String8 mtPdu = String8(pUrcData->readString16());
    RpCdmaSmsMtUrc result;
    int replyOptSeqNo = -1;
    RpCdmaSmsConverter::toMessage(rilCdmaSmsMsg, mtPdu, &replyOptSeqNo);
    result.setResult(true);
    result.setSeqId(replyOptSeqNo);
    result.setAddress(&rilCdmaSmsMsg->sAddress);

    return result;
}

bool RpCdmaSmsCodec::encodeRilCdmaSmsMsg(RIL_CDMA_SMS_Message *rilCdmaSmsMsg,
        Parcel *pRilCdmaSmsMsgData) {
    logDecode(String8("encodeRilCdmaSmsMsg"));

    // FIXME
    /**
     * encode as RIL_CDMA_SMS_Message parcel data, copied from responseCdmaSms@ril.cpp/c2k-ril
     * It should be changed as cpp coding style in the future.
     */
    int digitCount;
    int digitLimit;
    uint8_t uct;

    RIL_CDMA_SMS_Message *p_cur = (RIL_CDMA_SMS_Message *) rilCdmaSmsMsg;
    pRilCdmaSmsMsgData->writeInt32(p_cur->uTeleserviceID);
    pRilCdmaSmsMsgData->write(&(p_cur->bIsServicePresent),sizeof(uct));
    pRilCdmaSmsMsgData->writeInt32(p_cur->uServicecategory);
    pRilCdmaSmsMsgData->writeInt32(p_cur->sAddress.digit_mode);
    pRilCdmaSmsMsgData->writeInt32(p_cur->sAddress.number_mode);
    pRilCdmaSmsMsgData->writeInt32(p_cur->sAddress.number_type);
    pRilCdmaSmsMsgData->writeInt32(p_cur->sAddress.number_plan);
    pRilCdmaSmsMsgData->write(&(p_cur->sAddress.number_of_digits), sizeof(uct));
    digitLimit= min((p_cur->sAddress.number_of_digits), RIL_CDMA_SMS_ADDRESS_MAX);
    for(digitCount =0 ; digitCount < digitLimit; digitCount ++) {
        pRilCdmaSmsMsgData->write(&(p_cur->sAddress.digits[digitCount]),sizeof(uct));
    }

    pRilCdmaSmsMsgData->writeInt32(p_cur->sSubAddress.subaddressType);
    pRilCdmaSmsMsgData->write(&(p_cur->sSubAddress.odd),sizeof(uct));
    pRilCdmaSmsMsgData->write(&(p_cur->sSubAddress.number_of_digits),sizeof(uct));
    digitLimit= min((p_cur->sSubAddress.number_of_digits), RIL_CDMA_SMS_SUBADDRESS_MAX);
    for(digitCount =0 ; digitCount < digitLimit; digitCount ++) {
        pRilCdmaSmsMsgData->write(&(p_cur->sSubAddress.digits[digitCount]),sizeof(uct));
    }

    digitLimit = min((p_cur->uBearerDataLen), RIL_CDMA_SMS_BEARER_DATA_MAX);
    pRilCdmaSmsMsgData->writeInt32(p_cur->uBearerDataLen);
    for(digitCount =0 ; digitCount < digitLimit; digitCount ++) {
       pRilCdmaSmsMsgData->write(&(p_cur->aBearerData[digitCount]), sizeof(uct));
    }

    return true;
}

bool RpCdmaSmsCodec::decodeRilCdmaSmsAckMsg(Parcel *pData, RIL_CDMA_SMS_Ack *rilCdmaSmsAck) {
    logDecode(String8("decodeRilCdmaSmsAckMsg"));
    bool result = false;

    // FIXME
    /**
     * decode as RIL_CDMA_SMS_Message, copied from constructCdmaSms@Ril.cpp.
     * It should be changed as cpp coding style in the future.
     */
    int32_t  t = 0;
    status_t status = NO_ERROR;

    memset(rilCdmaSmsAck, 0, sizeof(RIL_CDMA_SMS_Ack));

    status = pData->readInt32(&t);
    rilCdmaSmsAck->uErrorClass = (RIL_CDMA_SMS_ErrorClass) t;

    status = pData->readInt32(&t);
    rilCdmaSmsAck->uSMSCauseCode = (int) t;

    if (status == NO_ERROR) {
        logEncode(String8("Decode to RIL_CDMA_SMS_Ack completed"));
        result = true;
    } else {
        logEncode(String8::format("Decode to RIL_CDMA_SMS_Ack failed, status = %d", status));
        // return empty string as error
        result = false;
    }

    return result;
}

String8 RpCdmaSmsCodec::encodeRilCdmaSmsAck(RIL_CDMA_SMS_Ack *rilCdmaSmsAck, int replySeqId,
        RIL_CDMA_SMS_Address *mtAddress) {
    logEncode(String8("encodeRilCdmaSmsAck"));

    if (replySeqId == -1 || rilCdmaSmsAck == NULL || mtAddress == NULL) {
        // No need to encode
        return String8("");
    }
    logEncode(String8::format("Reply Sequence id = %d", replySeqId));

    String8 hexPdu;
    RpCdmaSmsConverter::toHexPdu(
            rilCdmaSmsAck,
            replySeqId,
            (RIL_CDMA_SMS_Address *)mtAddress,
            hexPdu);


    String8 atCmd = String8::format("AT+C2KCNMA=%d, \"%s\"",
            (int)hexPdu.length() / 2, hexPdu.string());
    logEncode(atCmd);

    return atCmd;
}

int RpCdmaSmsCodec::min(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}

void RpCdmaSmsCodec::log(String8 s) {
    if (mDebug) RFX_LOG_D("RpCdmaSmsCodec: ", "%s", s.string());
}

void RpCdmaSmsCodec::logEncode(String8 s) {
    if (mDebug) RFX_LOG_D("RpCdmaSmsCodec, <encode>: ", "%s", s.string());
}

void RpCdmaSmsCodec::logDecode(String8 s) {
    if (mDebug) RFX_LOG_D("RpCdmaSmsCodec, <decode>: ", "%s", s.string());
}


/*****************************************************************************
 * BitwiseOutputStream
 *****************************************************************************/
BitwiseOutputStream::BitwiseOutputStream(int startLen)
    :m_pos(0), m_end(startLen << 3) {
    m_buf = new unsigned char[startLen];
    memset(m_buf, 0, startLen);
}



void BitwiseOutputStream::write(int bits, uint32_t data) {
    RFX_ASSERT ((bits > 0) && (bits <= 8));
    RFX_ASSERT((m_pos + bits) < m_end);
    data &= (0xFFFFFFFFUL) >> (32 - bits);
    int index = m_pos >> 3;
    int offset = 16 - (m_pos % 8) - bits;
    data <<= offset;
    m_pos += bits;
    m_buf[index] |= data >> 8;
    if (offset < 8) {
        m_buf[index + 1] |= data & 0xFF;
    }
}


int BitwiseOutputStream::getByteLen() const {
    int len = m_pos >> 3;
    return (m_pos & 0x7) ? (len + 1) : len;
}


/*****************************************************************************
 * BitwiseInputStream
 *****************************************************************************/
unsigned char BitwiseInputStream::read(int bits) {
    RFX_ASSERT((bits > 0) && (bits <= 8));
    RFX_ASSERT((m_pos + bits) <= m_end);
    int index = m_pos >> 3;
    int offset = 16 - (m_pos & 0x07) - bits; // &7 == % 8
    unsigned int data = (m_buf[index] & 0xFF) << 8;
    if (offset < 8) data |= m_buf[index + 1] & 0xFF;
    data >>= offset;
    data &= ((0xFFFFFFFFUL) >> (32 - bits));
    m_pos += bits;
    return (unsigned char)data;
}

void BitwiseInputStream::skip(int bits) {
    m_pos += bits;
}

/*****************************************************************************
 * CdmaSmsMessage
 *****************************************************************************/
RFX_IMPLEMENT_CLASS("CdmaSmsMessage", CdmaSmsMessage, RfxObject);

CdmaSmsMessage::CdmaSmsMessage(const int type) : m_type(type), m_error(0) {
    if (type < MESSAGE_TYPE_P2P || type > MESSAGE_TYPE_ACK) {
        m_error = -1;
    }
}


CdmaSmsMessage::CdmaSmsMessage(const char* hexPdu, int len) : m_type(-1), m_error(0){
    RFX_ASSERT(len == MESSAGE_TYPE_HEX_LEN);
    if (strncmp(hexPdu, "00", len) == 0) {
        m_type =MESSAGE_TYPE_P2P;
    } else if (strncmp(hexPdu, "01", len) == 0) {
        m_type = MESSAGE_TYPE_BC;
    } else {
        m_error = -1;
    }
}


String8 CdmaSmsMessage::toHexBody() {
     String8 body;
     for (RfxObject *i = getFirstChildObj(); i != NULL; i = i->getNextObj()) {
        RmcTlvNode *pNode = RFX_OBJ_DYNAMIC_CAST(i, RmcTlvNode);
        RFX_ASSERT(pNode != NULL);
        body.append(pNode->toHexHeader());
        body.append(pNode->toHexBody());
     }
     return body;
}




/*****************************************************************************
 * Node
 *****************************************************************************/
RFX_IMPLEMENT_CLASS("RmcTlvNode", RmcTlvNode, RfxObject);

RmcTlvNode::RmcTlvNode(int tag, int length) :
        m_tag(tag), m_length(length), m_error(0) {
}

RmcTlvNode::RmcTlvNode(const char* hexPdu, int len) : m_error(0) {
    hex2Bin(hexPdu, len);
    if (len != m_length * 2 + 4) {
        m_error = -1;
    }
}



String8 RmcTlvNode::toHexBody() {
    Vector<unsigned char>::iterator it;
    String8 hex;
    for (it = m_value.begin(); it != NULL && it != m_value.end(); it++) {
        hex.appendFormat("%02x", *it);
    }
    return hex;
}


char RmcTlvNode::char2Int(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    } else if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    } else {
        RFX_ASSERT(0);
        return 0;
    }
}


void RmcTlvNode::hex2Bin(const char *src, int len) {
    RFX_ASSERT(len % 2 == 0);
    RFX_ASSERT(len >= 6);
    for (int i = 0; i < len / 2; i++) {
        char c = char2Int(*src);
        src++;
        c = c << 4 | char2Int(*src);
        src++;
        if (i == 0) {
            m_tag = c;
        } else if (i == 1) {
            m_length = c;
        } else {
            m_value.push(c);
        }
    }
}


/*****************************************************************************
 * TeleServiceId
 *****************************************************************************/
RFX_IMPLEMENT_CLASS("TeleServiceId", TeleServiceId, RmcTlvNode);

TeleServiceId::TeleServiceId(int id) : RmcTlvNode(TELESERVICE_ID, TELESERVICE_ID_LEN) {
   m_value.push((id & 0xFFFF) >> 8);
   m_value.push(id & 0xFF);
}


TeleServiceId::TeleServiceId(const char* hexPdu, int len) :  RmcTlvNode(hexPdu, len){
    if (m_tag != TELESERVICE_ID) {
        m_error = -1;
    }
}


int TeleServiceId::getTeleServiceId() {
    if (m_error < 0) {
        return -1;
    }
    int teleServiceId = m_value[0];
    teleServiceId = teleServiceId << 8 | m_value[1];
    return teleServiceId;
}


/*****************************************************************************
 * ServiceCategory
 *****************************************************************************/
RFX_IMPLEMENT_CLASS("ServiceCategory", ServiceCategory, RmcTlvNode);

ServiceCategory::ServiceCategory(const char* hexPdu, int len) :  RmcTlvNode(hexPdu, len){
    if (m_tag != SERVICE_CATEGORY) {
        m_error = -1;
    }
}


int ServiceCategory::getServiceCategory() {
    if (m_error < 0) {
        return -1;
    }
    int serviceCategory = m_value[0];
    serviceCategory = serviceCategory << 8 | m_value[1];
    return serviceCategory;
}


/*****************************************************************************
 * CdmaSmsAddress
 *****************************************************************************/
RFX_IMPLEMENT_CLASS("CdmaSmsAddress", CdmaSmsAddress, RmcTlvNode);

CdmaSmsAddress::CdmaSmsAddress(RIL_CDMA_SMS_Address &addr, bool isMo) :RmcTlvNode(-1, -1) {
    m_tag = isMo ? DEST_ADDRESS : ORIG_ADDRESS;
    BitwiseOutputStream body(40 * 8);
    body.write(1, (uint32_t)addr.digit_mode);
    body.write(1, (uint32_t)addr.number_mode);
    int size = 4;
    if (addr.digit_mode == RIL_CDMA_SMS_DIGIT_MODE_8_BIT) {
        body.write(3, (uint32_t)addr.number_type);
        if (addr.number_mode == 0) {
            body.write(4, (uint32_t)addr.number_plan);
        }
        size = 8;
    }

    body.write(8, addr.number_of_digits);
    for (int i = 0; i < addr.number_of_digits; i++) {
        body.write(size, addr.digits[i]);
        if (addr.digit_mode == RIL_CDMA_SMS_DIGIT_MODE_4_BIT) {
            addr.digits[i] = dtmf2Char(addr.digits[i]);
        }
    }
    m_number.setTo((const char* )addr.digits, addr.number_of_digits);
    m_length = body.getByteLen();
    body.write(((m_length << 3) - body.getBitLen()), 0);
    m_value.appendArray(body.getBuf(), m_length);
}


CdmaSmsAddress::CdmaSmsAddress(const char* hexPdu, int len) :  RmcTlvNode(hexPdu, len) {
    if ((m_tag != ORIG_ADDRESS) && (m_tag != DEST_ADDRESS)) {
        m_error = -1;
    }
}


bool CdmaSmsAddress::getAddress(RIL_CDMA_SMS_Address &addr) {
    if (m_error < 0) {
        return false;
    }
    BitwiseInputStream body(m_value.array(), m_value.size());
    addr.digit_mode = (RIL_CDMA_SMS_DigitMode)body.read(1);
    addr.number_mode = (RIL_CDMA_SMS_NumberMode)body.read(1);
    int size = 4;
    if (addr.digit_mode == RIL_CDMA_SMS_DIGIT_MODE_8_BIT) {
        if (addr.number_mode == RIL_CDMA_SMS_NUMBER_MODE_DATA_NETWORK) {
            addr.number_type = (RIL_CDMA_SMS_NumberType)body.read(3);
        } else {
            addr.number_type = (RIL_CDMA_SMS_NumberType)body.read(3);
            addr.number_plan = (RIL_CDMA_SMS_NumberPlan)body.read(4);
        }
        size = 8;
    }

    addr.number_of_digits = body.read(8);
    for (int i = 0; i < addr.number_of_digits; i++) {
        unsigned char digit = body.read(size);
        addr.digits[i] = digit;
    }
    return true;
}

bool CdmaSmsAddress::getAddress(String8 &addr) {
    addr.setTo(m_number);
    return true;
}


unsigned char CdmaSmsAddress::dtmf2Char(char unsigned dtmf) {
    if (dtmf >0 && dtmf <=9 ) {
        return dtmf + '0';
    } else if (dtmf == 10) {
        return '0';
    } else if (dtmf == 11) {
        return '*';
    } else if (dtmf == 12) {
        return '#';
    }
    return 0;
}


/*****************************************************************************
 * CdmaSmsSubAddress
 *****************************************************************************/
RFX_IMPLEMENT_CLASS("CdmaSmsSubAddress", CdmaSmsSubAddress, RmcTlvNode);

CdmaSmsSubAddress::CdmaSmsSubAddress(const char* hexPdu, int len) :  RmcTlvNode(hexPdu, len) {
    if ((m_tag != ORIG_SUB_ADDR) && (m_tag != DEST_SUB_ADDR)) {
        m_error = -1;
    }
}


bool CdmaSmsSubAddress::getSubAddr(RIL_CDMA_SMS_Subaddress &subAddr) {
    if (m_error < 0) {
        return false;
    }
    BitwiseInputStream body(m_value.array(), m_value.size());
    subAddr.subaddressType = (RIL_CDMA_SMS_SubaddressType)body.read(3);
    if ((subAddr.subaddressType < RIL_CDMA_SMS_SUBADDRESS_TYPE_NSAP) ||
            (subAddr.subaddressType > RIL_CDMA_SMS_SUBADDRESS_TYPE_USER_SPECIFIED)) {
        return false;
    }
    subAddr.odd = body.read(1);
    subAddr.number_of_digits = body.read(8);
    if (subAddr.number_of_digits > RIL_CDMA_SMS_SUBADDRESS_MAX) {
        return false;
    }
    for (int i = 0; i < subAddr.number_of_digits; i++) {
        subAddr.digits[i] = body.read(8);
    }
    return true;
}


/*****************************************************************************
 * BearerReplyOpt
 *****************************************************************************/
RFX_IMPLEMENT_CLASS("BearerReplyOpt", BearerReplyOpt, RmcTlvNode);

BearerReplyOpt::BearerReplyOpt() : RmcTlvNode(BEARER_REPLY_OPT, BEARER_REPLY_OPT_LEN) {
   m_value.push(0x00);
}


BearerReplyOpt::BearerReplyOpt(const char* hexPdu, int len) :  RmcTlvNode(hexPdu, len) {
    if (m_tag != BEARER_REPLY_OPT) {
        m_error = -1;
    }
}


int BearerReplyOpt::getReplySeq() {
   if (m_error < 0) {
       return -1;
   }
   return (m_value[0] >> 2) & 0x3F;
}


/*****************************************************************************
 * CauseCode
 *****************************************************************************/
RFX_IMPLEMENT_CLASS("CauseCode", CauseCode, RmcTlvNode);

CauseCode::CauseCode(RIL_CDMA_SMS_Ack &ack, int replySeqNo) : RmcTlvNode(CAUSE_CODE, -1) {
    int errClass;
    if (ack.uErrorClass == RIL_CDMA_SMS_NO_ERROR) {
        m_length = CAUSE_CODE_NO_ERR_LEN;
        errClass = NO_ERR;
    } else if (RIL_CDMA_SMS_ERROR == ack.uErrorClass){
        m_length = CAUSE_CODE_ERR_LEN;
        errClass = PERMANENT_ERR;
    } else if (RIL_CDMA_SMS_TEMP_ERROR == (int)ack.uErrorClass) {
        m_length = CAUSE_CODE_ERR_LEN;
        errClass = TEMPORARY_ERR;
    } else {
        RFX_ASSERT(0);
    }
    m_value.push((unsigned char) ((replySeqNo << 2) | (errClass & 0x03)));
    if (errClass != NO_ERR) {
        m_value.push((unsigned char) ack.uSMSCauseCode);
    }
}

CauseCode::CauseCode(const char* hexPdu, int len) :  RmcTlvNode(hexPdu, len) {
    if (m_tag != CAUSE_CODE) {
        m_error = -1;
    }
}

/*****************************************************************************
 * BearerData
 *****************************************************************************/
RFX_IMPLEMENT_CLASS("BearerData", BearerData, RmcTlvNode);

BearerData::BearerData(unsigned char *data, int len) : RmcTlvNode(BEARER_DATA, len),
        m_messageId(-1), m_messageType(-1), m_needStatusReport(false) {
    len = removeZero(data, len);
    m_length = len;
    m_value.appendArray(data, len);
}


BearerData::BearerData(const char* hexPdu, int len) :  RmcTlvNode(hexPdu, len),
        m_messageId(-1), m_messageType(-1), m_needStatusReport(false) {
    if (m_tag != BEARER_DATA) {
        m_error = -1;
        return;
    }
}


bool BearerData::getBearerData(bool isCtWap, unsigned char *bearerData, int *len) {
    if (m_error < 0) {
        return false;
    }
    if (isCtWap) {
        *len = specialProcessForCtWapPush(bearerData);
    } else {
        memcpy(bearerData, m_value.array(), m_value.size());
        *len = m_length;
    }
    return true;
}

void BearerData::decodeMessageId() {
    BitwiseInputStream inStream(m_value.array(), m_value.size());
    while (inStream.available() > 0) {
        int subparamId = inStream.read(8);
        if (subparamId == SUBPARAM_MESSAGE_IDENTIFIER) {
            const int EXPECTED_PARAM_SIZE = 3 * 8;
            int paramBits = inStream.read(8) * 8;
            if (paramBits >= EXPECTED_PARAM_SIZE) {
                m_messageType = inStream.read(4);
                m_messageId = inStream.read(8) << 8;
                m_messageId |= inStream.read(8);
            }
            break;
        } else {
            int subparamLen = inStream.read(8); // SUBPARAM_LEN
            int paramBits = subparamLen * 8;
            if (paramBits <= inStream.available()) {
                inStream.skip(paramBits);
            }
        }
    }
}

void BearerData::decodeReplyOpt() {
    BitwiseInputStream inStream(m_value.array(), m_value.size());
    while (inStream.available() > 0) {
        int subparamId = inStream.read(8);
        if (subparamId == SUBPARAM_REPLY_OPTION) {
            const int EXPECTED_PARAM_SIZE = 8;
            int paramBits = inStream.read(8) * 8;
            if (paramBits >= EXPECTED_PARAM_SIZE) {
                unsigned char userAckReq = inStream.read(1);
                unsigned char deliveryAckReq = inStream.read(1);
                m_needStatusReport = (deliveryAckReq==1);
            }
            break;
        } else {
            int subparamLen = inStream.read(8); // SUBPARAM_LEN
            int paramBits = subparamLen * 8;
            if (paramBits <= inStream.available()) {
                inStream.skip(paramBits);
            }
        }
    }
}

int BearerData::specialProcessForCtWapPush(unsigned char* targetArray) {
    unsigned char paramId, paramLen, index = 0;
    unsigned short pos = 0;
    while (index < m_value.size()) {
        paramId = m_value[index++];
        paramLen = m_value[index++];
        // Skip user data 8*8+5 bits: For CT's WAP Push Message, need to skip
        if (paramId == SUBPARAM_USER_DATA) {
            targetArray[pos++] = paramId;
            targetArray[pos++] = paramLen - 8;
            unsigned short endUserDataPos = index + paramLen;
            index += 8;
            while (index < endUserDataPos) {
                targetArray[pos] = 0;
                targetArray[pos] = (m_value[index] << 5) | (m_value[index+1] >> 3);
                index++;
                pos++;
            }
        } else {
            memcpy(targetArray + pos, m_value.array() + index - 2, paramLen + 2);
            pos += (paramLen + 2);
            index += paramLen;
        }
    }
    return pos;
}


int BearerData::removeZero(unsigned char* bytePdu, unsigned short len) {
    unsigned char paramId;
    unsigned char paramLen;
    unsigned char index = 0;
    int userDataPos = -1;
    int userDataLen = -1;
    int pos = -1;
    while (index < len) {
        paramId = bytePdu[index++];
        paramLen = bytePdu[index++];
        if (paramId == 0) {
            // check if having header in user data
            if (((bytePdu[index + paramLen - 1]) & 0x08) == 0x08) {
                userDataPos = -1;
                break;
            }
        } else if (paramId == 1) {
            userDataPos = index;
            userDataLen = paramLen;
        }
        index += paramLen;
    }
    if (userDataPos != -1) {
        // 7bit ASCII encoding and last byte is zero
        if (((bytePdu[userDataPos] & 0xF8) == 0x10) &&
                (bytePdu[userDataPos + userDataLen - 1] == 0)) {
            unsigned char numFields = ((bytePdu[userDataPos] & 0x07) << USER_DATA_ENCODING_BITS) |
                    (bytePdu[userDataPos + 1] >> 3);
            // User data length: [encoding(5)][num_fields(8)][CHARi(x)][reserved(0-7)]
            unsigned char reservedBits = userDataLen * CDMA_SMS_OCTETS_BITS -
                    (numFields * CDMA_SMS_SEPTETS_BITS +
                    USER_DATA_ENCODING_BITS + USER_DATA_NUM_FIELDS_BITS);
            LOGI("removeZero, numFields: %d, reservedBits: %d, userDataLen: %d",
                    numFields, reservedBits, userDataLen);
            if (reservedBits < CDMA_SMS_OCTETS_BITS) {
                // no need remove reserved zero bits (Reserved bits length should be 0-7)
                return len;
            }
            pos =  userDataPos + userDataLen - 1;
            bytePdu[userDataPos - 1] = bytePdu[userDataPos - 1] - 1;
            if (pos + 1 < len) {
                memmove(&bytePdu[pos], &bytePdu[pos + 1], len - (pos + 1));
            }
            len--;
            LOGD("zero removed");
        }
    }
    return len;
}

/*****************************************************************************
 * Class RpCdmaSmsConverter
 *****************************************************************************/
bool RpCdmaSmsConverter::toHexPdu(
        RIL_CDMA_SMS_Message &message, String8 &hexPdu, String8 &address,
        bool needBearerReplyOpt) {
    if (message.sAddress.number_of_digits > RIL_CDMA_SMS_ADDRESS_MAX ||
            message.sSubAddress.number_of_digits > RIL_CDMA_SMS_SUBADDRESS_MAX ||
            message.uBearerDataLen > RIL_CDMA_SMS_BEARER_DATA_MAX)
    {
        return false;
    }

    CdmaSmsMessage *pMsg;
    RFX_OBJ_CREATE_EX(pMsg, CdmaSmsMessage, NULL, (CdmaSmsMessage::MESSAGE_TYPE_P2P));
    RFX_ASSERT(pMsg != NULL);

    TeleServiceId *pTId;
    RFX_OBJ_CREATE_EX(pTId, TeleServiceId, pMsg, (message.uTeleserviceID));
    RFX_ASSERT(pTId != NULL);

    CdmaSmsAddress *pAddr;
    RFX_OBJ_CREATE_EX(pAddr, CdmaSmsAddress, pMsg, (message.sAddress, true));
    RFX_ASSERT(pAddr != NULL);

    if (needBearerReplyOpt) {
        BearerReplyOpt *pOpt;
        RFX_OBJ_CREATE(pOpt, BearerReplyOpt, pMsg);
        RFX_ASSERT(pOpt != NULL);
    }

    BearerData *pBearer;
    RFX_OBJ_CREATE_EX(pBearer, BearerData, pMsg,
     (message.aBearerData, message.uBearerDataLen));
    RFX_ASSERT(pBearer != NULL);

    pAddr->getAddress(address);
    hexPdu = pMsg->toHexHeader() + pMsg->toHexBody();
    RFX_OBJ_CLOSE(pMsg);
    return true;
}


bool RpCdmaSmsConverter::toHexPdu(RIL_CDMA_SMS_Ack* pAck, int replySeqNo,
     RIL_CDMA_SMS_Address* pAddress, String8 &hexPdu) {
    if (pAck == NULL || pAddress == NULL) {
        return false;
    }
    CdmaSmsMessage *pMsg;
    RFX_OBJ_CREATE_EX(pMsg, CdmaSmsMessage, NULL, (CdmaSmsMessage::MESSAGE_TYPE_ACK));
    RFX_ASSERT(pMsg != NULL);

    CdmaSmsAddress *pAddr;
    RFX_OBJ_CREATE_EX(pAddr, CdmaSmsAddress, pMsg, (*pAddress, true));
    RFX_ASSERT(pAddr != NULL);

    CauseCode* pCause;
    RFX_OBJ_CREATE_EX(pCause, CauseCode, pMsg, (*pAck, replySeqNo));
    RFX_ASSERT(pCause != NULL);

    hexPdu = pMsg->toHexHeader() + pMsg->toHexBody();
    RFX_OBJ_CLOSE(pMsg);
    return true;
}


bool RpCdmaSmsConverter::toMessage(
        RIL_CDMA_SMS_Message *pMessage, String8 &hexPdu, int *pReplySeqNo) {
    const char *p = hexPdu.string();
    const char *q = p;
    int size = hexPdu.size();
    if (size % 2 != 0 || size < 2) {
        return false;
    }
    RFX_ASSERT(pMessage != NULL);
    RFX_ASSERT(pReplySeqNo != NULL);
    *pReplySeqNo = -1;
    bool ret = false;
    CdmaSmsMessage *pMsg;
    RFX_OBJ_CREATE_EX(pMsg, CdmaSmsMessage, NULL, (p, 2));
    p +=2;
    bool isCtWapPush = false;
    memset(pMessage, 0, sizeof(RIL_CDMA_SMS_Message));
    while ((p + 4 - q) < size) {
        String8 slen(p + 2, 2);
        int len = strtol(slen.string(), NULL, 16);
        len = len * 2 + 4;
        if (strncmp(p, "00", 2) == 0) {
            TeleServiceId *pId;
            RFX_OBJ_CREATE_EX(pId, TeleServiceId, pMsg, (p, len));
            isCtWapPush = pId->isCtWapPush();
            pMessage->uTeleserviceID = isCtWapPush ? 0x1004 : pId->getTeleServiceId();
        } else if (strncmp(p, "01", 2) == 0) {
            ServiceCategory *pSc;
            RFX_OBJ_CREATE_EX(pSc, ServiceCategory, pMsg, (p, len));
            pMessage->bIsServicePresent = 1;
            pMessage->uServicecategory = pSc->getServiceCategory();
        } else if (strncmp(p, "02", 2) == 0) {
            CdmaSmsAddress *pAddr;
            RFX_OBJ_CREATE_EX(pAddr, CdmaSmsAddress, pMsg, (p, len));
            pAddr->getAddress(pMessage->sAddress);
        } else if (strncmp(p, "03", 2) == 0) {
            CdmaSmsSubAddress *pSubAddr;
            RFX_OBJ_CREATE_EX(pSubAddr, CdmaSmsSubAddress, pMsg, (p, len));
            pSubAddr->getSubAddr(pMessage->sSubAddress);
        } else if (strncmp(p, "04", 2) == 0) {
            CdmaSmsAddress *pAddr;
            RFX_OBJ_CREATE_EX(pAddr, CdmaSmsAddress, pMsg, (p, len));
        } else if (strncmp(p, "05", 2) == 0) {
            CdmaSmsSubAddress *pSubAddr;
            RFX_OBJ_CREATE_EX(pSubAddr, CdmaSmsSubAddress, pMsg, (p, len));
        } else if (strncmp(p, "06", 2) == 0) {
            BearerReplyOpt *pOpt;
            RFX_OBJ_CREATE_EX(pOpt, BearerReplyOpt, pMsg, (p, len));
            *pReplySeqNo = pOpt->getReplySeq();
        } else if (strncmp(p, "07", 2) == 0) {
            CauseCode *pCause;
            RFX_OBJ_CREATE_EX(pCause, CauseCode, pMsg, (p, len));
        } else if (strncmp(p, "08", 2) == 0) {
            BearerData *pBearer;
            RFX_OBJ_CREATE_EX(pBearer, BearerData, pMsg, (p, len));
            pBearer->getBearerData(isCtWapPush,
                    pMessage->aBearerData, &pMessage->uBearerDataLen);
        } else {
          break;
        }
        p += len;
    }
    RFX_OBJ_CLOSE(pMsg);
    return ret;
}

bool RpCdmaSmsConverter::isStatusReport(RIL_CDMA_SMS_Message *pMessage, int *pMessageId) {
    BearerData *pBearer;
    RFX_OBJ_CREATE_EX(pBearer, BearerData, NULL,
     (pMessage->aBearerData, pMessage->uBearerDataLen));
    RFX_ASSERT(pBearer != NULL);
    pBearer->decodeMessageId();
    *pMessageId = pBearer->getMessageId();
    bool ret = pBearer->isStatusReport();
    RFX_OBJ_CLOSE(pBearer);
    return ret;
}

bool RpCdmaSmsConverter::isNeedStatusReport(RIL_CDMA_SMS_Message * pMessage) {
    BearerData *pBearer;
    RFX_OBJ_CREATE_EX(pBearer, BearerData, NULL,
     (pMessage->aBearerData, pMessage->uBearerDataLen));
    RFX_ASSERT(pBearer != NULL);
    pBearer->decodeReplyOpt();
    bool ret = pBearer->isNeedStatusReport();
    RFX_OBJ_CLOSE(pBearer);
    return ret;
}
