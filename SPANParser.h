// The parser with callback
#ifndef SPAN_PARSER_H
#define SPAN_PARSER_H
#include <functional>
#include <map>
#include <string>
#include <vector>
#include "SPANHeader.h"
#include "SPANMessage.h"
namespace SPAN {
struct BESTSATS;
class Parser {
    // Finite-state machine
    enum struct ParseState {
        IDLE,
        Abbreviated,
        ASCIIHeader,
        ShortASCIIHeader,
        ASCIIData,
        ASCIICRC,
        BinaryHeader,
        ShortBinaryHeader,
        BinaryData,
        BinaryCRC
    };
    // The allowed data types.
    // Short*** supported after OEM6
    enum struct DataType {
        Unknown,
        Abbreviated,
        ASCII,
        ShortASCII,
        Binary,
        ShortBinary
    };

   public:
    Parser();
    ~Parser();

    // Register callbacks. Callbacks will be called blocking when the message is
    // parsed.
#pragma region

    template <typename T>
    void RegisterCallback(std::function<void(const T*)> callback,
                          MessageID messageID);

    void RegisterAbbreviatedCallback(
        std::function<void(std::string)> abbreviatedCallback);

#pragma endregion

    // get the message buf
    void push(std::string buf);

   private:
    DataType dataType;
    ParseState parseState;
    std::map<MessageID, void*> callbacksType;
    std::map<MessageID, void*> callbacks;
    std::map<MessageID, void*> releaseCallbacks;
    std::function<void(std::string)> abbreviatedCallback;
    std::string msg;
    uint32_t messageLength;
};

template <typename T>
void Parser::RegisterCallback(std::function<void(const T*)> callback,
                              MessageID messageID) {
    if (callbacks[messageID] != nullptr) {
        delete (std::function<void(const T*)>*)callbacks[messageID];
    }
    auto* newCallback = new std::function<void(const T*)>(
        [callback](const T* msg) -> void { callback(msg); });
    callbacks[messageID] = newCallback;
    // std::swap(callback,callbacks[messageID]);
    if (callbacksType[messageID] == nullptr) {
        callbacksType[messageID] = new T();
    }
    if (releaseCallbacks[messageID] == nullptr) {
        releaseCallbacks[messageID] =
            new std::function<void()>([&, messageID]() -> void {
                if (callbacksType[messageID] != nullptr) {
                    delete (T*)callbacksType[messageID];
                }
                if (callbacks[messageID] != nullptr) {
                    delete (std::function<void(const T*)>*)callbacks[messageID];
                }
            });
    }
};

}  // namespace SPAN
#endif