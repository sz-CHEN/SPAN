#include "SPANParser.h"
#include <algorithm>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>
#include "SPANHeader.h"
#include "SPANMessage.h"
namespace SPAN {
const ULong CRC32_POLYNOMIAL = 0xEDB88320;
/* --------------------------------------------------------------------------
Calculate a CRC value to be used by CRC calculation functions.
-------------------------------------------------------------------------- */
ULong CRC32Value(int i) {
    int j;
    ULong ulCRC;
    ulCRC = i;
    for (j = 8; j > 0; j--) {
        if (ulCRC & 1)
            ulCRC = (ulCRC >> 1) ^ CRC32_POLYNOMIAL;
        else
            ulCRC >>= 1;
    }
    return ulCRC;
}
/* --------------------------------------------------------------------------
Calculates the CRC-32 of a block of data all at once
-------------------------------------------------------------------------- */
ULong CalculateBlockCRC32(
    unsigned long ulCount,   /* Number of bytes in the data block */
    unsigned char *ucBuffer) /* Data block */
{
    ULong ulTemp1;
    ULong ulTemp2;
    ULong ulCRC = 0;
    while (ulCount-- != 0) {
        ulTemp1 = (ulCRC >> 8) & 0x00FFFFFF;
        ulTemp2 = CRC32Value(((int)ulCRC ^ *ucBuffer++) & 0xff);
        ulCRC = ulTemp1 ^ ulTemp2;
    }
    return (ulCRC);
}

Parser::Parser() { parseState = ParseState::IDLE; }

Parser::~Parser() {
    for (auto iter = callbacksType.begin(); iter != callbacksType.end();
         iter++) {
        if (releaseCallbacks[iter->first] != nullptr) {
            (*(std::function<void()> *)releaseCallbacks[iter->first])();
            delete (std::function<void()> *)releaseCallbacks[iter->first];
            releaseCallbacks[iter->first] = nullptr;
        }
    }
}

void Parser::push(std::string buf) {
    if (buf.empty()) {
        return;
    }
    bool loop = false;
    msg.append(buf);
    do {
        loop = false;
        switch (parseState) {
            case ParseState::IDLE: {
                dataType = DataType::Unknown;
                size_t index = 0;
                for (size_t i = 0; i < msg.size(); ++i) {
                    auto &&c = msg[i];
                    if (c == char(0xAA)) {
                        dataType = DataType::Binary;
                        index = i;
                        break;
                    } else if (c == '%') {
                        dataType = DataType::ShortASCII;
                        index = i;
                        break;
                    } else if (c == '#') {
                        dataType = DataType::ASCII;
                        index = i;
                        break;
                    } else if (c == '<') {
                        dataType = DataType::Abbreviated;
                        index = i;
                        break;
                    }
                }
                switch (dataType) {
                    case DataType::Binary: {
                        msg.erase(0, index);
                        if (msg.size() > 1) {
                            if (msg[1] == char(0x44)) {
                                if (msg.size() > 2) {
                                    if (msg[2] == char(0x12)) {
                                        parseState = ParseState::BinaryHeader;
                                        loop = true;
                                    } else if (msg[2] == char(0x13)) {
                                        dataType = DataType::ShortBinary;
                                        parseState =
                                            ParseState::ShortBinaryHeader;
                                        loop = true;
                                    } else {
                                        msg.erase(0, 2);
                                        loop = true;
                                    }
                                }
                            } else {
                                msg.erase(0, 1);
                                loop = true;
                            }
                        }
                    } break;
                    case DataType::ASCII: {
                        parseState = ParseState::ASCIIHeader;
                        msg.erase(0, index);
                        loop = true;
                    } break;
                    case DataType::ShortASCII: {
                        parseState = ParseState::ShortASCIIHeader;
                        msg.erase(0, index);
                        loop = true;
                    } break;
                    case DataType::Unknown:
                    default:
                        msg.clear();
                        break;
                }
            } break;
            case ParseState::Abbreviated: {
                auto index = msg.find_first_of('\n');
                if (index != msg.npos) {
                    std::string abbr(msg.begin(), msg.begin() + index + 1);
                    if (abbr.end() ==
                        std::find_if(abbr.begin(), abbr.end(), [](int ch) {
                            return !(std::isprint(ch) || std::isspace(ch));
                        })) {
                        if (abbreviatedCallback) abbreviatedCallback(abbr);
                        msg.erase(0, index + 1);
                    } else {
                        msg.erase(0, 1);
                    }
                    parseState = ParseState::IDLE;
                    loop = true;
                } else {
                    if (msg.end() !=
                        std::find_if(msg.begin(), msg.end(), [](int ch) {
                            return !(std::isprint(ch) || std::isspace(ch));
                        })) {
                        parseState = ParseState::IDLE;
                        msg.erase(0, 1);
                        loop = true;
                    }
                }
            } break;
            case ParseState::ASCIIHeader:
            case ParseState::ShortASCIIHeader: {
                auto index = msg.find_first_of(';');
                if (index != msg.npos) {
                    parseState = ParseState::ASCIIData;
                    if (msg.size() > index + 1) {
                        loop = true;
                    }
                } else {
                    if (msg.end() !=
                        std::find_if(msg.begin(), msg.end(), [](int ch) {
                            return !(std::isprint(ch) || std::isspace(ch));
                        })) {
                        parseState = ParseState::IDLE;
                        msg.erase(0, 1);
                        loop = true;
                    }
                }
            } break;
            case ParseState::ASCIIData: {
                auto index = msg.find_first_of('*');
                if (index != msg.npos) {
                    parseState = ParseState::ASCIICRC;
                    if (msg.size() > index + 1) {
                        loop = true;
                    }
                } else {
                    if (msg.end() !=
                        std::find_if(msg.begin(), msg.end(), [](int ch) {
                            return !(std::isprint(ch) || std::isspace(ch));
                        })) {
                        parseState = ParseState::IDLE;
                        msg.erase(0, 1);
                        loop = true;
                    }
                }
            } break;
            case ParseState::ASCIICRC: {
                auto index = msg.find_first_of('*');
                if (msg.size() >= index + 9) {
                    std::string crcStr(msg.begin() + index + 1,
                                       msg.begin() + index + 9);
                    ULong crc = std::stoul(crcStr, 0, 16);
                    ULong calcrc = CalculateBlockCRC32(
                        index - 1, (unsigned char *)&msg[1]);
                    if (calcrc == crc) {
                        auto headerend = msg.find_first_of(';');
                        std::string headerstr(msg.begin() + 1,
                                              msg.begin() + headerend);
                        headerstr.push_back(',');
                        std::istringstream headerstream(headerstr);
                        std::string s;
                        std::vector<std::string> strs;
                        while (getline(headerstream, s, ',')) {
                            strs.push_back(s);
                        }
                        if (strs[0].size() > 1) {
                            strs[0].erase(strs[0].end() - 1, strs[0].end());
                        }
                        Header header;
                        ShortHeader sheader;
                        bool isSucceed = true;
                        switch (dataType) {
                            case DataType::ASCII: {
                                if (!Header::fromAscii(strs, header)) {
                                    isSucceed = false;
                                }
                            } break;
                            case DataType::ShortASCII: {
                                if (!ShortHeader::fromAscii(strs, sheader)) {
                                    isSucceed = false;
                                }
                            } break;
                            default:
                                isSucceed = false;
                                break;
                        }
                        if (isSucceed) {
                            std::string datastr(msg.begin() + headerend + 1,
                                                msg.begin() + index);
                            datastr.push_back(',');
                            std::istringstream datastream(datastr);
                            strs.clear();
                            while (getline(datastream, s, ',')) {
                                strs.push_back(s);
                            }
                            switch (dataType) {
                                case DataType::ASCII: {
                                    auto *va = callbacksType[header.message_ID];
                                    if (va != nullptr) {
                                        memmove(va, &header, sizeof(header));
                                        if (ConstructASCIIWithoutHeader(
                                                header.message_ID, strs, va)) {
                                            std::function<void(void *)> *func =
                                                (std::function<void(void *)> *)
                                                    callbacks[header
                                                                  .message_ID];
                                            if (func != nullptr) {
                                                (*func)(va);
                                            }
                                        }
                                    }
                                    break;
                                }
                                case DataType::ShortASCII: {
                                    auto *va =
                                        callbacksType[sheader.message_ID];
                                    if (va != nullptr) {
                                        memmove(va, &sheader, sizeof(sheader));
                                        if (ConstructASCIIWithoutHeader(
                                                sheader.message_ID, strs, va)) {
                                            std::function<void(void *)> *func =
                                                (std::function<void(void *)> *)
                                                    callbacks[sheader
                                                                  .message_ID];
                                            if (func != nullptr) {
                                                (*func)(va);
                                            }
                                        }
                                    }
                                    break;
                                }
                                default:
                                    break;
                            }
                        }
                    }
                    msg.erase(0, index + 9);
                    parseState = ParseState::IDLE;
                    if (!msg.empty()) {
                        loop = true;
                    }
                }
            } break;
            case ParseState::BinaryHeader: {
                if (msg.size() >= sizeof(Header)) {
                    Header header;
                    if (Header::fromBin(msg, header) &&
                        header.header_length == sizeof(Header)) {
                        messageLength =
                            header.message_length + header.header_length;
                        parseState = ParseState::BinaryData;
                        if (msg.size() > header.header_length) {
                            loop = true;
                        }
                    } else {
                        msg.erase(0, 3);
                        parseState = ParseState::IDLE;
                    }
                }
            } break;
            case ParseState::ShortBinaryHeader: {
                if (msg.size() >= sizeof(ShortHeader)) {
                    ShortHeader header;
                    if (ShortHeader::fromBin(msg, header)) {
                        messageLength =
                            header.message_length + sizeof(ShortHeader);
                        parseState = ParseState::BinaryData;
                        if (msg.size() > sizeof(ShortHeader)) {
                            loop = true;
                        }
                    } else {
                        msg.erase(0, 3);
                        parseState = ParseState::IDLE;
                    }
                }
            } break;
            case ParseState::BinaryData: {
                if (msg.size() >= messageLength) {
                    parseState = ParseState::BinaryCRC;
                    if (msg.size() > messageLength) {
                        loop = true;
                    }
                }
            } break;
            case ParseState::BinaryCRC: {
                if (msg.size() >= messageLength + 4) {
                    ULong crc = *(ULong *)&msg[messageLength];
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
                    toggleEndian(&crc);
#endif
                    ULong calCRC = CalculateBlockCRC32(
                        messageLength, (unsigned char *)&msg[0]);
                    if (crc == calCRC) {
                        MessageID messageID;
                        switch (dataType) {
                            case DataType::Binary: {
                                Header header;
                                if (Header::fromBin(msg, header)) {
                                    messageID = header.message_ID;
                                    auto va = callbacksType[messageID];
                                    if (va != nullptr) {
                                        memmove(va, &header, sizeof(header));
                                        if (ConstructBINWithoutHeader(
                                                messageID,
                                                std::string(msg.begin() +
                                                                sizeof(header),
                                                            msg.end()),
                                                va)) {
                                            std::function<void(void *)> *func =
                                                (std::function<void(void *)> *)
                                                    callbacks[messageID];
                                            if (func != nullptr) {
                                                (*func)(va);
                                            }
                                        }
                                    }
                                }
                                break;
                            }
                            case DataType::ShortBinary: {
                                ShortHeader header;
                                if (ShortHeader::fromBin(msg, header)) {
                                    messageID = header.message_ID;
                                    auto va = callbacksType[messageID];
                                    if (va != nullptr) {
                                        memmove(va, &header,
                                                sizeof(ShortHeader));
                                        if (ConstructBINWithoutHeader(
                                                messageID,
                                                std::string(
                                                    msg.begin() +
                                                        sizeof(ShortHeader),
                                                    msg.end()),
                                                va)) {
                                            std::function<void(void *)> *func =
                                                (std::function<void(void *)> *)
                                                    callbacks[messageID];
                                            if (func != nullptr) {
                                                (*func)(va);
                                            }
                                        }
                                    }
                                }
                                break;
                            }
                            default:
                                break;
                        }
                    }
                    msg.erase(0, messageLength + 4);
                    parseState = ParseState::IDLE;
                    if (!msg.empty()) {
                        loop = true;
                    }
                }
            } break;
        }
    } while (loop);
}

void Parser::RegisterAbbreviatedCallback(
    std::function<void(std::string)> abbreviatedCallback) {
    this->abbreviatedCallback = abbreviatedCallback;
}

}  // namespace SPAN