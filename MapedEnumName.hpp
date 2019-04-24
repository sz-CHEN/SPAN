#ifndef __MAPED_ENUM_NAME_HPP
#define __MAPED_ENUM_NAME_HPP
#include <algorithm>
#include <cctype>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#define STRING_REMOVE_CHAR(str, ch) \
    str.erase(std::remove(str.begin(), str.end(), ch), str.end())

inline std::vector<std::string> splitString(std::string str, char sep = ',') {
    std::vector<std::string> vecString;
    std::string item;
    std::stringstream stringStream(str);
    while (std::getline(stringStream, item, sep)) {
        vecString.push_back(item);
    }
    return vecString;
}

#define DECLARE_ENUM_WITH_TYPE(E, T, ...)                                  \
    enum class E : T { __VA_ARGS__ };                                      \
    static std::map<std::string, T> E##MapName(                            \
        generateNameMapEnum<T>(#__VA_ARGS__));                             \
    static std::map<T, std::string> NameMap##E(                            \
        generateEnumMapName<T>(#__VA_ARGS__));                             \
    inline E E##FromName(std::string name) { return (E)E##MapName[name]; } \
    inline std::string NameFrom##E(E e) { return NameMap##E[(T)e]; }       \
    inline bool valid##E(std::string value) {                              \
        return (E##MapName.find(value) != E##MapName.end());               \
    }

#define DECLARE_ENUM(E, ...) DECLARE_ENUM_WITH_TYPE(E, int32_t, __VA_ARGS__)
template <typename T>
inline std::map<std::string, T> generateNameMapEnum(std::string strMap) {
    STRING_REMOVE_CHAR(strMap, ' ');
    STRING_REMOVE_CHAR(strMap, '(');

    std::vector<std::string> enumTokens(splitString(strMap));
    std::map<std::string, T> retMap;
    T inxMap;

    inxMap = 0;
    for (auto iter = enumTokens.begin(); iter != enumTokens.end(); ++iter) {
        // Token: [EnumName | EnumName=EnumValue]
        std::string enumName;
        // T enumValue;
        if (iter->find('=') == std::string::npos) {
            enumName = *iter;
        } else {
            std::vector<std::string> enumNameValue(splitString(*iter, '='));
            enumName = enumNameValue[0];
            // inxMap = static_cast<T>(enumNameValue[1]);
            if (std::is_unsigned<T>::value) {
                inxMap = static_cast<T>(std::stoull(enumNameValue[1], 0, 0));
            } else {
                inxMap = static_cast<T>(std::stoll(enumNameValue[1], 0, 0));
            }
        }
        retMap[enumName] = inxMap++;
    }
    return retMap;
}

template <typename T>
inline std::map<T, std::string> generateEnumMapName(std::string strMap) {
    STRING_REMOVE_CHAR(strMap, ' ');
    STRING_REMOVE_CHAR(strMap, '(');

    std::vector<std::string> enumTokens(splitString(strMap));
    std::map<T, std::string> retMap;
    T inxMap;

    inxMap = 0;
    for (auto iter = enumTokens.begin(); iter != enumTokens.end(); ++iter) {
        // Token: [EnumName | EnumName=EnumValue]
        std::string enumName;
        // T enumValue;
        if (iter->find('=') == std::string::npos) {
            enumName = *iter;
        } else {
            std::vector<std::string> enumNameValue(splitString(*iter, '='));
            enumName = enumNameValue[0];
            // inxMap = static_cast<T>(enumNameValue[1]);
            if (std::is_unsigned<T>::value) {
                inxMap = static_cast<T>(std::stoull(enumNameValue[1], 0, 0));
            } else {
                inxMap = static_cast<T>(std::stoll(enumNameValue[1], 0, 0));
            }
        }
        retMap[inxMap++] = enumName;
    }
    return retMap;
}
#endif