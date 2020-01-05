#ifndef SPAN_Header_H
#define SPAN_Header_H
#include "SPANType.h"

namespace SPAN {
// 28
struct Header {
    Char sync[3];
    // sync[0] = (Char)0xAA;
    // sync[1] = (Char)0x44;
    // sync[2] = (Char)0x12;
    UChar header_length;
    MessageID message_ID;
    MessageType message_type;
    UChar port_address;
    UShort message_length;  // used as port_address when ascii mode
    UShort sequence;
    UChar idel_time;
    TimeStatus time_status;
    UShort week;
    GPSec ms;
    ReceiverStatus receiver_status;
    UShort reserved;
    UShort receiver_S_W_version;

    static bool fromBin(const std::string& str, Header& __t) {
        if (str.size() < sizeof(__t)) return false;
        memcpy(&__t, str.data(), sizeof(__t));
        DEFINE_MARCO_SPAN_MESSAGE_TOGGLE(__t);
        return true;
    }

    static bool fromAscii(const std::vector<std::string>& str, Header& __t) {
        if (str.size() < 10) {
            return false;
        }
        try {
            __t.message_ID = MessageIDFromName(str[0]);
            __t.message_length = (UShort)DetailedPortIdentifierFromName(str[1]);
            __t.port_address = (UChar)(__t.message_length & 0xFF);
            __t.sequence = stoUS(str[2]);
            __t.idel_time = stoF(str[3]) * 2;
            __t.time_status = TimeStatusFromName(str[4]);
            __t.week = stoUS(str[5]);
            __t.ms = DtoL(stoD(str[6]) * 1000);
            __t.receiver_status = stoUL(str[7], 0, 16);
            __t.reserved = stoUS(str[8], 0, 16);
            __t.receiver_S_W_version = stoUS(str[9]);
            return true;
        } catch (...) {
            return false;
        }
    }

    void toggleEndian() {
        TOGGLE_SPAN_ENDIAN(message_ID);
        TOGGLE_SPAN_ENDIAN(message_length);
        TOGGLE_SPAN_ENDIAN(sequence);
        TOGGLE_SPAN_ENDIAN(week);
        TOGGLE_SPAN_ENDIAN(ms);
        TOGGLE_SPAN_ENDIAN(receiver_status);
        TOGGLE_SPAN_ENDIAN(reserved);
        TOGGLE_SPAN_ENDIAN(receiver_S_W_version);
        // return *msg;
    }
};

// 12
struct ShortHeader {
    Char sync[3];
    // sync[0] = (Char)0xAA;
    // sync[1] = (Char)0x44;
    // sync[2] = (Char)0x13;
    UChar message_length;
    MessageID message_ID;
    UShort week_number;
    ULong milliseconds;

    static bool fromBin(const std::string& str, ShortHeader& __t) {
        if (str.size() < sizeof(__t)) return false;
        memcpy(&__t, str.data(), sizeof(__t));
        DEFINE_MARCO_SPAN_MESSAGE_TOGGLE(__t);
        return true;
    }

    static bool fromAscii(const std::vector<std::string>& str,
                          ShortHeader& __t) {
        if (str.size() < 3) {
            return false;
        }
        try {
            __t.message_ID = MessageIDFromName(str[0]);
            __t.week_number = stoUS(str[1]);
            __t.milliseconds = DtoUL((stoD(str[2]) * 1000));
            return true;
        } catch (...) {
            return false;
        }
    }

    void toggleEndian() {
        TOGGLE_SPAN_ENDIAN(message_ID);
        TOGGLE_SPAN_ENDIAN(week_number);
        TOGGLE_SPAN_ENDIAN(milliseconds);
    }
};

}  // namespace SPAN
#endif