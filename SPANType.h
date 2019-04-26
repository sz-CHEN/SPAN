// Define type described in Firmware Reference Manual
#ifndef SPAN_TYPE_H
#define SPAN_TYPE_H
#ifdef _WIN32
#include <Windows.h>
#endif
#include <cstdint>
#include "MapedEnumName.hpp"
namespace SPAN {
#ifdef __GNUC__
#define ALIGN(x) __attribute__((packed, aligned(x)))
#define DO_Pragma(x) _Pragma(#x)
#define ALIGN_REGION(x) DO_Pragma(pack(x))
#define ALIGN_ENDREGION _Pragma("pack()")
#elif defined(_MSC_VER)
#define ALIGN(x)
#define ALIGN_REGION(x) __pragma(pack(x))
#define ALIGN_ENDREGION __pragma(pack())
#endif

#if (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__) || \
    (REG_DWORD == REG_DWORD_BIG_ENDIAN)
#define DEFINE_MARCO_SPAN_MESSAGE_TOGGLE(x) \
    { x.toggleEndian(); }
#else
#define DEFINE_MARCO_SPAN_MESSAGE_TOGGLE(x)
#endif

static_assert(std::numeric_limits<double>::is_iec559 &&
                  std::numeric_limits<float>::is_iec559,
              "Requires IEEE 754 floating point!");

using Char = int8_t;
using UChar = uint8_t;
using Short = int16_t;
using UShort = uint16_t;
using Long = int32_t;
using ULong = uint32_t;
using Double = double;
using Float = float;
using GPSec = Long;
using Boolean = ULong;

inline ULong StoUL(const std::string& __str, std::size_t* __idx = 0,
                   int __base = 10) {
    return std::stoul(__str, __idx, __base);
}
inline Long StoL(const std::string& __str, std::size_t* __idx = 0,
                 int __base = 10) {
    return std::stol(__str, __idx, __base);
}
inline UShort StoUS(const std::string& __str, std::size_t* __idx = 0,
                    int __base = 10) {
    return std::stoi(__str, __idx, __base);
}
inline Short StoS(const std::string& __str, std::size_t* __idx = 0,
                  int __base = 10) {
    return std::stoi(__str, __idx, __base);
}
inline Double StoD(const std::string& __str, std::size_t* __idx = 0) {
    return std::stod(__str, __idx);
}
inline Float StoF(const std::string& __str, std::size_t* __idx = 0) {
    return std::stof(__str, __idx);
}
inline UChar StoUC(const std::string& __str, std::size_t* __idx = 0,
                   int __base = 10) {
    return std::stoi(__str, __idx, __base);
}

DECLARE_ENUM_WITH_TYPE(TimeStatus, UChar,
                       // enum struct TimeStatus : UChar {
                       UNKNOWN = 20, APPROXIMATE = 60, COARSEADJUSTING = 80,
                       COARSE = 100, COARSESTEERING = 120, FREEWHEELING = 130,
                       FINEADJUSTING = 140, FINE = 160,
                       FINEBACKUPSTEERING = 170, FINESTEERING = 180,
                       SATTIME = 200
                       // };
)

DECLARE_ENUM_WITH_TYPE(
    DetailedPortIdentifier, UShort, NO_PORTS = 0x00, COM1_ALL, COM2_ALL,
    COM3_ALL, THISPORT_ALL = 0x06, FILE_ALL, ALL_PORTS, XCOM1_ALL, XCOM2_ALL,
    USB1_ALL = 0x0d, USB2_ALL, USB3_ALL, AUX_ALL, XCOM3_ALL, COM4_ALL = 0x13,
    ETH1_ALL, IMU_ALL, ICOM1_ALL = 0x17, ICOM2_ALL, ICOM3_ALL, NCOM1_ALL,
    NCOM2_ALL, NCOM3_ALL, WCOM1_ALL = 0x1e, COM1 = 0x20, COM1_1, COM1_2, COM1_3,
    COM1_4, COM1_5, COM1_6, COM1_7, COM1_8, COM1_9, COM1_10, COM1_11, COM1_12,
    COM1_13, COM1_14, COM1_15, COM1_16, COM1_17, COM1_18, COM1_19, COM1_20,
    COM1_21, COM1_22, COM1_23, COM1_24, COM1_25, COM1_26, COM1_28, COM1_29,
    COM1_30, COM1_31, COM2 = 0x40, COM2_1, COM2_2, COM2_3, COM2_4, COM2_5,
    COM2_6, COM2_7, COM2_8, COM2_9, COM2_10, COM2_11, COM2_12, COM2_13, COM2_14,
    COM2_15, COM2_16, COM2_17, COM2_18, COM2_19, COM2_20, COM2_21, COM2_22,
    COM2_23, COM2_24, COM2_25, COM2_26, COM2_28, COM2_29, COM2_30, COM2_31,
    COM3 = 0x60, COM3_1, COM3_2, COM3_3, COM3_4, COM3_5, COM3_6, COM3_7, COM3_8,
    COM3_9, COM3_10, COM3_11, COM3_12, COM3_13, COM3_14, COM3_15, COM3_16,
    COM3_17, COM3_18, COM3_19, COM3_20, COM3_21, COM3_22, COM3_23, COM3_24,
    COM3_25, COM3_26, COM3_28, COM3_29, COM3_30, COM3_31, SPECIAL = 0xa0,
    SPECIAL_1, SPECIAL_2, SPECIAL_3, SPECIAL_4, SPECIAL_5, SPECIAL_6, SPECIAL_7,
    SPECIAL_8, SPECIAL_9, SPECIAL_10, SPECIAL_11, SPECIAL_12, SPECIAL_13,
    SPECIAL_14, SPECIAL_15, SPECIAL_16, SPECIAL_17, SPECIAL_18, SPECIAL_19,
    SPECIAL_20, SPECIAL_21, SPECIAL_22, SPECIAL_23, SPECIAL_24, SPECIAL_25,
    SPECIAL_26, SPECIAL_28, SPECIAL_29, SPECIAL_30, SPECIAL_31, THISPORT = 0xc0,
    THISPORT_1, THISPORT_2, THISPORT_3, THISPORT_4, THISPORT_5, THISPORT_6,
    THISPORT_7, THISPORT_8, THISPORT_9, THISPORT_10, THISPORT_11, THISPORT_12,
    THISPORT_13, THISPORT_14, THISPORT_15, THISPORT_16, THISPORT_17,
    THISPORT_18, THISPORT_19, THISPORT_20, THISPORT_21, THISPORT_22,
    THISPORT_23, THISPORT_24, THISPORT_25, THISPORT_26, THISPORT_28,
    THISPORT_29, THISPORT_30, THISPORT_31, FILE = 0xe0, FILE_1, FILE_2, FILE_3,
    FILE_4, FILE_5, FILE_6, FILE_7, FILE_8, FILE_9, FILE_10, FILE_11, FILE_12,
    FILE_13, FILE_14, FILE_15, FILE_16, FILE_17, FILE_18, FILE_19, FILE_20,
    FILE_21, FILE_22, FILE_23, FILE_24, FILE_25, FILE_26, FILE_28, FILE_29,
    FILE_30, FILE_31, XCOM1 = 0x01a0, XCOM1_1, XCOM1_2, XCOM1_3, XCOM1_4,
    XCOM1_5, XCOM1_6, XCOM1_7, XCOM1_8, XCOM1_9, XCOM1_10, XCOM1_11, XCOM1_12,
    XCOM1_13, XCOM1_14, XCOM1_15, XCOM1_16, XCOM1_17, XCOM1_18, XCOM1_19,
    XCOM1_20, XCOM1_21, XCOM1_22, XCOM1_23, XCOM1_24, XCOM1_25, XCOM1_26,
    XCOM1_28, XCOM1_29, XCOM1_30, XCOM1_31, XCOM2 = 0x2a0, XCOM2_1, XCOM2_2,
    XCOM2_3, XCOM2_4, XCOM2_5, XCOM2_6, XCOM2_7, XCOM2_8, XCOM2_9, XCOM2_10,
    XCOM2_11, XCOM2_12, XCOM2_13, XCOM2_14, XCOM2_15, XCOM2_16, XCOM2_17,
    XCOM2_18, XCOM2_19, XCOM2_20, XCOM2_21, XCOM2_22, XCOM2_23, XCOM2_24,
    XCOM2_25, XCOM2_26, XCOM2_28, XCOM2_29, XCOM2_30, XCOM2_31, USB1 = 0x5a0,
    USB1_1, USB1_2, USB1_3, USB1_4, USB1_5, USB1_6, USB1_7, USB1_8, USB1_9,
    USB1_10, USB1_11, USB1_12, USB1_13, USB1_14, USB1_15, USB1_16, USB1_17,
    USB1_18, USB1_19, USB1_20, USB1_21, USB1_22, USB1_23, USB1_24, USB1_25,
    USB1_26, USB1_28, USB1_29, USB1_30, USB1_31, USB2 = 0x6a0, USB2_1, USB2_2,
    USB2_3, USB2_4, USB2_5, USB2_6, USB2_7, USB2_8, USB2_9, USB2_10, USB2_11,
    USB2_12, USB2_13, USB2_14, USB2_15, USB2_16, USB2_17, USB2_18, USB2_19,
    USB2_20, USB2_21, USB2_22, USB2_23, USB2_24, USB2_25, USB2_26, USB2_28,
    USB2_29, USB2_30, USB2_31, USB3 = 0x7a0, USB3_1, USB3_2, USB3_3, USB3_4,
    USB3_5, USB3_6, USB3_7, USB3_8, USB3_9, USB3_10, USB3_11, USB3_12, USB3_13,
    USB3_14, USB3_15, USB3_16, USB3_17, USB3_18, USB3_19, USB3_20, USB3_21,
    USB3_22, USB3_23, USB3_24, USB3_25, USB3_26, USB3_28, USB3_29, USB3_30,
    USB3_31, AUX = 0x8a0, AUX_1, AUX_2, AUX_3, AUX_4, AUX_5, AUX_6, AUX_7,
    AUX_8, AUX_9, AUX_10, AUX_11, AUX_12, AUX_13, AUX_14, AUX_15, AUX_16,
    AUX_17, AUX_18, AUX_19, AUX_20, AUX_21, AUX_22, AUX_23, AUX_24, AUX_25,
    AUX_26, AUX_28, AUX_29, AUX_30, AUX_31, XCOM3 = 0x9a0, XCOM3_1, XCOM3_2,
    XCOM3_3, XCOM3_4, XCOM3_5, XCOM3_6, XCOM3_7, XCOM3_8, XCOM3_9, XCOM3_10,
    XCOM3_11, XCOM3_12, XCOM3_13, XCOM3_14, XCOM3_15, XCOM3_16, XCOM3_17,
    XCOM3_18, XCOM3_19, XCOM3_20, XCOM3_21, XCOM3_22, XCOM3_23, XCOM3_24,
    XCOM3_25, XCOM3_26, XCOM3_28, XCOM3_29, XCOM3_30, XCOM3_31, COM4 = 0xba0,
    COM4_1, COM4_2, COM4_3, COM4_4, COM4_5, COM4_6, COM4_7, COM4_8, COM4_9,
    COM4_10, COM4_11, COM4_12, COM4_13, COM4_14, COM4_15, COM4_16, COM4_17,
    COM4_18, COM4_19, COM4_20, COM4_21, COM4_22, COM4_23, COM4_24, COM4_25,
    COM4_26, COM4_28, COM4_29, COM4_30, COM4_31, PORT_ADDR_ETH1 = 0xca0,
    PORT_ADDR_ETH1_1, PORT_ADDR_ETH1_2, PORT_ADDR_ETH1_3, PORT_ADDR_ETH1_4,
    PORT_ADDR_ETH1_5, PORT_ADDR_ETH1_6, PORT_ADDR_ETH1_7, PORT_ADDR_ETH1_8,
    PORT_ADDR_ETH1_9, PORT_ADDR_ETH1_10, PORT_ADDR_ETH1_11, PORT_ADDR_ETH1_12,
    PORT_ADDR_ETH1_13, PORT_ADDR_ETH1_14, PORT_ADDR_ETH1_15, PORT_ADDR_ETH1_16,
    PORT_ADDR_ETH1_17, PORT_ADDR_ETH1_18, PORT_ADDR_ETH1_19, PORT_ADDR_ETH1_20,
    PORT_ADDR_ETH1_21, PORT_ADDR_ETH1_22, PORT_ADDR_ETH1_23, PORT_ADDR_ETH1_24,
    PORT_ADDR_ETH1_25, PORT_ADDR_ETH1_26, PORT_ADDR_ETH1_28, PORT_ADDR_ETH1_29,
    PORT_ADDR_ETH1_30, PORT_ADDR_ETH1_31, PORT_ADDR_IMU = 0xda0,
    PORT_ADDR_IMU_1, PORT_ADDR_IMU_2, PORT_ADDR_IMU_3, PORT_ADDR_IMU_4,
    PORT_ADDR_IMU_5, PORT_ADDR_IMU_6, PORT_ADDR_IMU_7, PORT_ADDR_IMU_8,
    PORT_ADDR_IMU_9, PORT_ADDR_IMU_10, PORT_ADDR_IMU_11, PORT_ADDR_IMU_12,
    PORT_ADDR_IMU_13, PORT_ADDR_IMU_14, PORT_ADDR_IMU_15, PORT_ADDR_IMU_16,
    PORT_ADDR_IMU_17, PORT_ADDR_IMU_18, PORT_ADDR_IMU_19, PORT_ADDR_IMU_20,
    PORT_ADDR_IMU_21, PORT_ADDR_IMU_22, PORT_ADDR_IMU_23, PORT_ADDR_IMU_24,
    PORT_ADDR_IMU_25, PORT_ADDR_IMU_26, PORT_ADDR_IMU_28, PORT_ADDR_IMU_29,
    PORT_ADDR_IMU_30, PORT_ADDR_IMU_31, ICOM1 = 0xfa0, ICOM1_1, ICOM1_2,
    ICOM1_3, ICOM1_4, ICOM1_5, ICOM1_6, ICOM1_7, ICOM1_8, ICOM1_9, ICOM1_10,
    ICOM1_11, ICOM1_12, ICOM1_13, ICOM1_14, ICOM1_15, ICOM1_16, ICOM1_17,
    ICOM1_18, ICOM1_19, ICOM1_20, ICOM1_21, ICOM1_22, ICOM1_23, ICOM1_24,
    ICOM1_25, ICOM1_26, ICOM1_28, ICOM1_29, ICOM1_30, ICOM1_31, ICOM2 = 0x10a0,
    ICOM2_1, ICOM2_2, ICOM2_3, ICOM2_4, ICOM2_5, ICOM2_6, ICOM2_7, ICOM2_8,
    ICOM2_9, ICOM2_10, ICOM2_11, ICOM2_12, ICOM2_13, ICOM2_14, ICOM2_15,
    ICOM2_16, ICOM2_17, ICOM2_18, ICOM2_19, ICOM2_20, ICOM2_21, ICOM2_22,
    ICOM2_23, ICOM2_24, ICOM2_25, ICOM2_26, ICOM2_28, ICOM2_29, ICOM2_30,
    ICOM2_31, ICOM3 = 0x11a0, ICOM3_1, ICOM3_2, ICOM3_3, ICOM3_4, ICOM3_5,
    ICOM3_6, ICOM3_7, ICOM3_8, ICOM3_9, ICOM3_10, ICOM3_11, ICOM3_12, ICOM3_13,
    ICOM3_14, ICOM3_15, ICOM3_16, ICOM3_17, ICOM3_18, ICOM3_19, ICOM3_20,
    ICOM3_21, ICOM3_22, ICOM3_23, ICOM3_24, ICOM3_25, ICOM3_26, ICOM3_28,
    ICOM3_29, ICOM3_30, ICOM3_31, NCOM1 = 0x12a0, NCOM1_1, NCOM1_2, NCOM1_3,
    NCOM1_4, NCOM1_5, NCOM1_6, NCOM1_7, NCOM1_8, NCOM1_9, NCOM1_10, NCOM1_11,
    NCOM1_12, NCOM1_13, NCOM1_14, NCOM1_15, NCOM1_16, NCOM1_17, NCOM1_18,
    NCOM1_19, NCOM1_20, NCOM1_21, NCOM1_22, NCOM1_23, NCOM1_24, NCOM1_25,
    NCOM1_26, NCOM1_28, NCOM1_29, NCOM1_30, NCOM1_31, NCOM2 = 0x13a0, NCOM2_1,
    NCOM2_2, NCOM2_3, NCOM2_4, NCOM2_5, NCOM2_6, NCOM2_7, NCOM2_8, NCOM2_9,
    NCOM2_10, NCOM2_11, NCOM2_12, NCOM2_13, NCOM2_14, NCOM2_15, NCOM2_16,
    NCOM2_17, NCOM2_18, NCOM2_19, NCOM2_20, NCOM2_21, NCOM2_22, NCOM2_23,
    NCOM2_24, NCOM2_25, NCOM2_26, NCOM2_28, NCOM2_29, NCOM2_30, NCOM2_31,
    NCOM3 = 0x14a0, NCOM3_1, NCOM3_2, NCOM3_3, NCOM3_4, NCOM3_5, NCOM3_6,
    NCOM3_7, NCOM3_8, NCOM3_9, NCOM3_10, NCOM3_11, NCOM3_12, NCOM3_13, NCOM3_14,
    NCOM3_15, NCOM3_16, NCOM3_17, NCOM3_18, NCOM3_19, NCOM3_20, NCOM3_21,
    NCOM3_22, NCOM3_23, NCOM3_24, NCOM3_25, NCOM3_26, NCOM3_28, NCOM3_29,
    NCOM3_30, NCOM3_31, PORT_ADDR_WCOM1 = 0x16a0, PORT_ADDR_WCOM1_1,
    PORT_ADDR_WCOM1_2, PORT_ADDR_WCOM1_3, PORT_ADDR_WCOM1_4, PORT_ADDR_WCOM1_5,
    PORT_ADDR_WCOM1_6, PORT_ADDR_WCOM1_7, PORT_ADDR_WCOM1_8, PORT_ADDR_WCOM1_9,
    PORT_ADDR_WCOM1_10, PORT_ADDR_WCOM1_11, PORT_ADDR_WCOM1_12,
    PORT_ADDR_WCOM1_13, PORT_ADDR_WCOM1_14, PORT_ADDR_WCOM1_15,
    PORT_ADDR_WCOM1_16, PORT_ADDR_WCOM1_17, PORT_ADDR_WCOM1_18,
    PORT_ADDR_WCOM1_19, PORT_ADDR_WCOM1_20, PORT_ADDR_WCOM1_21,
    PORT_ADDR_WCOM1_22, PORT_ADDR_WCOM1_23, PORT_ADDR_WCOM1_24,
    PORT_ADDR_WCOM1_25, PORT_ADDR_WCOM1_26, PORT_ADDR_WCOM1_28,
    PORT_ADDR_WCOM1_29, PORT_ADDR_WCOM1_30, PORT_ADDR_WCOM1_31,
    COM5_ALL = 0x16c0, COM6_ALL, BT1_ALL, COM7_ALL, COM8_ALL, COM9_ALL,
    COM10_ALL, COM5 = 0x17a0, COM5_1, COM5_2, COM5_3, COM5_4, COM5_5, COM5_6,
    COM5_7, COM5_8, COM5_9, COM5_10, COM5_11, COM5_12, COM5_13, COM5_14,
    COM5_15, COM5_16, COM5_17, COM5_18, COM5_19, COM5_20, COM5_21, COM5_22,
    COM5_23, COM5_24, COM5_25, COM5_26, COM5_28, COM5_29, COM5_30, COM5_31,
    COM6 = 0x18a0, COM6_1, COM6_2, COM6_3, COM6_4, COM6_5, COM6_6, COM6_7,
    COM6_8, COM6_9, COM6_10, COM6_11, COM6_12, COM6_13, COM6_14, COM6_15,
    COM6_16, COM6_17, COM6_18, COM6_19, COM6_20, COM6_21, COM6_22, COM6_23,
    COM6_24, COM6_25, COM6_26, COM6_28, COM6_29, COM6_30, COM6_31, BT1 = 0x19a0,
    BT1_1, BT1_2, BT1_3, BT1_4, BT1_5, BT1_6, BT1_7, BT1_8, BT1_9, BT1_10,
    BT1_11, BT1_12, BT1_13, BT1_14, BT1_15, BT1_16, BT1_17, BT1_18, BT1_19,
    BT1_20, BT1_21, BT1_22, BT1_23, BT1_24, BT1_25, BT1_26, BT1_28, BT1_29,
    BT1_30, BT1_31, PORT_ADDR_COM7 = 0x1aa0, PORT_ADDR_COM7_1, PORT_ADDR_COM7_2,
    PORT_ADDR_COM7_3, PORT_ADDR_COM7_4, PORT_ADDR_COM7_5, PORT_ADDR_COM7_6,
    PORT_ADDR_COM7_7, PORT_ADDR_COM7_8, PORT_ADDR_COM7_9, PORT_ADDR_COM7_10,
    PORT_ADDR_COM7_11, PORT_ADDR_COM7_12, PORT_ADDR_COM7_13, PORT_ADDR_COM7_14,
    PORT_ADDR_COM7_15, PORT_ADDR_COM7_16, PORT_ADDR_COM7_17, PORT_ADDR_COM7_18,
    PORT_ADDR_COM7_19, PORT_ADDR_COM7_20, PORT_ADDR_COM7_21, PORT_ADDR_COM7_22,
    PORT_ADDR_COM7_23, PORT_ADDR_COM7_24, PORT_ADDR_COM7_25, PORT_ADDR_COM7_26,
    PORT_ADDR_COM7_28, PORT_ADDR_COM7_29, PORT_ADDR_COM7_30, PORT_ADDR_COM7_31,
    PORT_ADDR_COM8 = 0x1ba0, PORT_ADDR_COM8_1, PORT_ADDR_COM8_2,
    PORT_ADDR_COM8_3, PORT_ADDR_COM8_4, PORT_ADDR_COM8_5, PORT_ADDR_COM8_6,
    PORT_ADDR_COM8_7, PORT_ADDR_COM8_8, PORT_ADDR_COM8_9, PORT_ADDR_COM8_10,
    PORT_ADDR_COM8_11, PORT_ADDR_COM8_12, PORT_ADDR_COM8_13, PORT_ADDR_COM8_14,
    PORT_ADDR_COM8_15, PORT_ADDR_COM8_16, PORT_ADDR_COM8_17, PORT_ADDR_COM8_18,
    PORT_ADDR_COM8_19, PORT_ADDR_COM8_20, PORT_ADDR_COM8_21, PORT_ADDR_COM8_22,
    PORT_ADDR_COM8_23, PORT_ADDR_COM8_24, PORT_ADDR_COM8_25, PORT_ADDR_COM8_26,
    PORT_ADDR_COM8_28, PORT_ADDR_COM8_29, PORT_ADDR_COM8_30, PORT_ADDR_COM8_31,
    PORT_ADDR_COM9 = 0x1ca0, PORT_ADDR_COM9_1, PORT_ADDR_COM9_2,
    PORT_ADDR_COM9_3, PORT_ADDR_COM9_4, PORT_ADDR_COM9_5, PORT_ADDR_COM9_6,
    PORT_ADDR_COM9_7, PORT_ADDR_COM9_8, PORT_ADDR_COM9_9, PORT_ADDR_COM9_10,
    PORT_ADDR_COM9_11, PORT_ADDR_COM9_12, PORT_ADDR_COM9_13, PORT_ADDR_COM9_14,
    PORT_ADDR_COM9_15, PORT_ADDR_COM9_16, PORT_ADDR_COM9_17, PORT_ADDR_COM9_18,
    PORT_ADDR_COM9_19, PORT_ADDR_COM9_20, PORT_ADDR_COM9_21, PORT_ADDR_COM9_22,
    PORT_ADDR_COM9_23, PORT_ADDR_COM9_24, PORT_ADDR_COM9_25, PORT_ADDR_COM9_26,
    PORT_ADDR_COM9_28, PORT_ADDR_COM9_29, PORT_ADDR_COM9_30, PORT_ADDR_COM9_31,
    PORT_ADDR_COM10 = 0x1da0, PORT_ADDR_COM10_1, PORT_ADDR_COM10_2,
    PORT_ADDR_COM10_3, PORT_ADDR_COM10_4, PORT_ADDR_COM10_5, PORT_ADDR_COM10_6,
    PORT_ADDR_COM10_7, PORT_ADDR_COM10_8, PORT_ADDR_COM10_9, PORT_ADDR_COM10_10,
    PORT_ADDR_COM10_11, PORT_ADDR_COM10_12, PORT_ADDR_COM10_13,
    PORT_ADDR_COM10_14, PORT_ADDR_COM10_15, PORT_ADDR_COM10_16,
    PORT_ADDR_COM10_17, PORT_ADDR_COM10_18, PORT_ADDR_COM10_19,
    PORT_ADDR_COM10_20, PORT_ADDR_COM10_21, PORT_ADDR_COM10_22,
    PORT_ADDR_COM10_23, PORT_ADDR_COM10_24, PORT_ADDR_COM10_25,
    PORT_ADDR_COM10_26, PORT_ADDR_COM10_28, PORT_ADDR_COM10_29,
    PORT_ADDR_COM10_30, PORT_ADDR_COM10_31)

DECLARE_ENUM_WITH_TYPE(
    MessageID, UShort, LOGLIST = 5, RTCAOBS = 6, GPSEPHEM = 7, IONUTC = 8,
    RTCA1 = 10, RTCAREF = 11, CLOCKMODEL = 16, RAWGPSSUBFRAME = 25,
    CLOCKSTEERING = 26, VERSION = 37, RAWEPHEM = 41, BESTPOS = 42, RANGE = 43,
    PSRPOS = 47, SATVIS = 48, PORTSTATS = 72, ALMANAC = 73, RAWALM = 74,
    TRACKSTAT = 83, RXSTATUS = 93, RXSTATUSEVENT = 94, MATCHEDPOS = 96,
    BESTVEL = 99, PSRVEL = 100, TIME = 101, CMROBS = 103, CMRREF = 105,
    RTCM1 = 107, RTCM59 = 116, RTCM3 = 117, RTCM22 = 118, RXCONFIG = 128,
    RTCM16 = 129, RTCM16T = 131, RANGECMP = 140, RTKPOS = 141, DIRENT = 159,
    NAVIGATE = 161, AVEPOS = 172, PSRDOP = 174, REFSTATION = 175, MARKPOS = 181,
    VALIDMODELS = 206, RTKVEL = 216, GPALM = 217, GPGGA = 218, GPGLL = 219,
    GPGRS = 220, GPGSA = 221, GPGST = 222, GPGSV = 223, GPRMB = 224,
    GPRMC = 225, GPVTG = 226, GPZDA = 227, MARKTIME = 231, PASSCOM1 = 233,
    PASSCOM2 = 234, PASSCOM3 = 235, BESTXYZ = 241, MATCHEDXYZ = 242,
    PSRXYZ = 243, RTKXYZ = 244, GPGGARTK = 259, RTCM1819 = 260, INSATT = 263,
    INSCOV, INSPOS, INSSPD, INSVEL, RAWIMU, RTCM9 = 275, RAWGPSSBASFRAME = 287,
    RTCM15 = 307, CMRDESC = 310, INSATTS = 319, INSCOVS, INSPOSS, INSSPDS = 323,
    INSVELS, RAWIMUS, RTCAEPHEM = 347, RTCM2021 = 374, PASSXCOM1 = 405,
    PASSXCOM2 = 406, RAWGPSWORD = 407, PDPPOS = 469, PDPVEL = 470, PDPXYZ = 471,
    TIMESYNC = 492, OMNIHPPOS = 495, INSPVA = 507, INSPVAS,
    APPLICATIONSTATUS = 520, GPGGALONG = 521, PASSUSB1 = 607, PASSUSB2 = 608,
    PASSUSB3 = 609, MARK2POS = 615, MARK2TIME = 616, TIMEDWHEELDATA = 622,
    RANGEGPSL1 = 631, VEHICLEBODYROTATION = 642, WHEELSIZE = 646, RTCM23 = 665,
    RTCM24 = 667, BESTLEVERARM = 674, BSLNXYZ = 686, PASSAUX = 690,
    CMRPLUS = 717, GLOALMANAC = 718, GLOCLOCK = 719, GLORAWALM = 720,
    GLORAWFRAME = 721, GLORAWSTRING = 722, GLOEPHEMERIS = 723, BESTUTM = 726,
    LBANDINFO = 730, LBANDSTAT = 731, RAWLBANDFRAME = 732, RAWLBANDPACKET = 733,
    INSUPDATE = 757, RTCM1005 = 765, RTCM1006 = 768, RTCM1004 = 770,
    RTCM1001 = 772, RTCM1002 = 774, RTCM1003 = 776, GLORAWEPHEM = 792,
    PASSXCOM3 = 795, RTCAOBS2 = 805, CORRIMUDATA = 812, CORRIMUDATAS,
    RTCM1007 = 852, RTCM1008 = 854, GLMLA = 859, OMNIVIS = 860, RTCM31 = 864,
    RTCM32 = 873, RTCM36 = 875, RTCM36T = 877, PSRTIME = 881, CMRGLOOBS = 882,
    RTCM1009 = 885, RTCM1010 = 887, RTCM1011 = 889, RTCM1012 = 891,
    RTCM1019 = 893, RTCM1020 = 895, RTCM59GLO = 903, RTKDOP = 952,
    RTCMOMNI1 = 957, HWMONITOR = 963, HEADING = 971, RAWSBASFRAME = 973,
    SBAS0 = 976, SBAS1 = 977, SBAS10 = 978, SBAS12 = 979, SBAS17 = 980,
    SBAS18 = 981, SBAS2 = 982, SBAS24 = 983, SBAS25 = 984, SBAS26 = 985,
    SBAS27 = 986, SBAS3 = 987, SBAS32 = 988, SBAS33 = 989, SBAS34 = 990,
    SBAS35 = 991, SBAS4 = 992, SBAS45 = 993, SBAS5 = 994, SBAS6 = 995,
    SBAS7 = 996, SBAS9 = 997, SBASCORR = 998, SATVIS2 = 1043, GPHDT = 1045,
    RTCAREFEXT = 1049, MASTERPOS = 1051, ROVERPOS = 1052, RAWCNAVFRAME = 1066,
    MARK1PVA, MARK2PVA, MARK3TIME = 1075, MARK4TIME = 1076, MARK1COUNT = 1093,
    MARK2COUNT = 1094, MARK3COUNT = 1095, MARK4COUNT = 1096, RTCM1033 = 1097,
    MARK3PVA = 1118, MARK4PVA, GALALMANAC = 1120, GALCLOCK = 1121,
    GALEPHEMERIS = 1122, GALIONO = 1127, LOGFILESTATUS = 1146,
    CHANCONFIGLIST = 1148, PSRSATS = 1162, PSRDOP2 = 1163, RTKDOP2 = 1172,
    RTKSATS = 1174, MATCHEDSATS = 1176, PASHR, BESTSATS = 1194,
    OMNIHPSATS = 1197, LBANDTRACKSTAT = 1201, PASSETH1 = 1209, PDPSATS = 1234,
    SOFTLOADSTATUS = 1235, PASSICOM1 = 1250, PASSICOM2 = 1251, PASSICOM3 = 1252,
    PASSNCOM1 = 1253, PASSNCOM2 = 1254, PASSNCOM3 = 1255, BESTLEVERARM2,
    TAGGEDMARK1PVA = 1258, TAGGEDMARK2PVA, IMUTOANTOFFSETS = 1270,
    RANGECMP2 = 1273, RAIMSTATUS = 1286, ETHSTATUS = 1288, IPSTATUS = 1289,
    GALFNAVEPHEMERIS = 1301, IMURATEPVAS = 1305, GALINAVEPHEMERIS = 1309,
    ALIGNBSLNXYZ = 1314, ALIGNBSLNENU = 1315, HEADINGSATS = 1316,
    VARIABLELEVERARM = 1320, GIMBALLEDPVA, REFSTATIONINFO = 1325,
    TAGGEDMARK3PVA = 1327, TAGGEDMARK4PVA, MODELFEATURES = 1329,
    QZSSRAWEPHEM = 1330, QZSSRAWSUBFRAME = 1330, ALIGNDOP = 1332,
    HEADING2 = 1335, QZSSEPHEMERIS = 1336, RTCAOBS3 = 1340, PASSTHROUGH = 1342,
    SOURCETABLE = 1344, QZSSRAWALMANAC = 1345, QZSSALMANAC = 1346,
    QZSSIONUTC = 1347, AUTHCODES = 1348, IMURATECORRIMUS = 1362, HEAVE = 1382,
    PASSCOM4 = 1384, PROFILEINFO = 1412, GALFNAVRAWPAGE = 1413,
    GALINAVRAWWORD = 1414, SBASALMANAC = 1425, BESTGNSSPOS = 1429, BESTGNSSVEL,
    RELINSPVA = 1446, SATXYZ2 = 1451, TSS1 = 1456, INSATTX, INSVELX, INPOSX,
    RAWIMUX = 1461, RAWIMUSX, INSPVAX = 1465, PPPPOS = 1538, PPPSATS = 1541,
    PASSCOM5 = 1576, PASSCOM6 = 1577, BDSALMANAC = 1584, BDSIONO = 1590,
    BDSCLOCK = 1607, BLUETOOTHSTATUS = 1608, WIFICLISTATUS = 1613,
    WIFICLISCANRESULTS = 1616, NOVATELXOBS = 1618, NOVATELXREF = 1620,
    WIFIAPSTATUS = 1666, IPSTATS = 1669, CELLULARSTATUS = 1685,
    CELLULARINFO = 1686, BDSRAWNAVSUBFRAME = 1695, BDSEPHEMERIS = 1696,
    HEADINGRATE = 1698, PASSCOM7 = 1701, PASSCOM8 = 1702, PASSCOM9 = 1703,
    PASSCOM10 = 1704, SYNCHEAVE = 1708, DELAYEDHEAVE, LBANDBEAMTABLE = 1718,
    TERRASTARINFO = 1719, VERIPOSINFO = 1728, TERRASTARSTATUS = 1729,
    VERIPOSSTATUS = 1730, MARK3POS = 1738, MARK4POS = 1739,
    SYNCRELINSPVA = 1743, IMURATEPVA = 1778, RTKASSISTSTATUS = 2048)

DECLARE_ENUM_WITH_TYPE(ClockModelStatus, ULong,
                       // enum struct ClockModelStatus : ULong {
                       VALID = 0, CONVERGING, ITERATING, INVALID
                       // };
)
DECLARE_ENUM_WITH_TYPE(UTCStatus, ULong,
                       // enum struct UTCStatus : ULong {
                       Invalid = 0, Valid, Warning,
                       // };
)

DECLARE_ENUM_WITH_TYPE(SolutionStatus, ULong,
                       // enum struct SolutionStatus : ULong {
                       SOL_COMPUTED = 0, INSUFFICIENT_OBS, NO_CONVERGENCE,
                       SINGULARITY, COV_TRACE, TEST_DIST, COLD_START, V_H_LIMIT,
                       VARIANCE, RESIDUALS, Reserved10, Reserved11, Reserved12,
                       INTEGRITY_WARNING, Reserved14, Reserved15, Reserved16,
                       Reserved17, PENDING, INVALID_FIX, Reserved20, Reserved21,
                       INVALID_RATE
                       // };
)
DECLARE_ENUM_WITH_TYPE(
    PositionOrVelocityType, ULong,
    // enum struct PositionOrVelocityType : ULong {
    NONE = 0, FIXEDPOS, FIXEDHEIGHT, Reserved03, FLOATCONV, WIDELANE,
    NARROWLANE, Reserved07, DOPPLER_VELOCITY, Reserved09, Reserved10,
    Reserved11, Reserved12, Reserved13, Reserved14, Reserved15, SINGLE, PSRDIFF,
    WAAS, PROPOGATED, OMNISTAR, Reserved21, Reserved22, Reserved23, Reserved24,
    Reserved25, Reserved26, Reserved27, Reserved28, Reserved29, Reserved30,
    Reserved31, L1_FLOAT, IONOFREE_FLOAT, NARROW_FLOAT, Reserved35, Reserved36,
    Reserved37, Reserved38, Reserved39, Reserved40, Reserved41, Reserved42,
    Reserved43, Reserved44, Reserved45, Reserved46, Reserved47, L1_INT,
    WIDE_INT, NARROW_INT, RTK_DIRECT_INS, INS_SBAS, INS_PSRSP, INS_PSRDIFF,
    INS_RTKFLOAT, INS_RTKFIXED, INS_OMNISTAR, INS_OMNISTAR_HP, INS_OMNISTAR_XP,
    Reserved60, Reserved61, Reserved62, Reserved63, OMNISTAR_HP, OMNISTAR_XP,
    Reserved66, Reserved67, PPP_CONVERGING, PPP, Reserved70, Reserved71,
    Reserved72, INS_PPP_CONVERGING, INS_PPP
    // };
)
DECLARE_ENUM_WITH_TYPE(DatumTransfomationParams, ULong,
                       // enum struct DatumTransfomationParams : ULong {
                       ADIND = 1, ARC50, ARC60, AGD66, AGD84, BUKIT, ASTRO,
                       CHATM, CARTH, CAPE, DJAKA, EGYPT, ED50, ED79, GUNSG,
                       GEO49, GRB36, GUAM, HAWAII, KAUAI, MAUI, OAHU, HERAT,
                       HJORS, HONGK, HUTZU, INDIA, IRE65, KERTA, KANDA, LIBER,
                       LUZON, MINDA, MERCH, NAHR, NAD83, CANADA, ALASKA, NAD27,
                       CARIBB, MEXICO, CAMER, MINNA, OMAN, PUERTO, QORNO, ROME,
                       CHUA, SAM56, SAM69, CAMPO, SACOR, YACAR, TANAN, TIMBA,
                       TOKYO, TRIST, VITI, WAK60, WGS72, WGS84, ZAND, USER,
                       CSRS, ADIM, ARSM, ENW, HTN, INDB, INDI, IRL, LUZA, LUZB,
                       NAHC, NASP, OGBM, OHAA, OHAB, OHAC, OHAD, OHIA, OHIB,
                       OHIC, OHID, TIL, TOYM
                       // };
)
DECLARE_ENUM_WITH_TYPE(InertialSolutionStatus, ULong,
                       // enum struct InertialSolutionStatus : ULong {
                       INS_INACTIVE = 0, INS_ALIGNLING, INS_HIGH_VARIANCE,
                       INS_SOLUTION_GOOD, INS_SOLUTION_FREE = 6,
                       INS_ALIGNMENT_COMPLETE, DETERMINING_ORIENTATION,
                       WAITING_INITALPOS
                       // };
)

DECLARE_ENUM_WITH_TYPE(SatelliteSystem, ULong, GPS = 0, GLONASS, SBAS,
                       Galileo = 5, BeiDou, QZSS)

DECLARE_ENUM_WITH_TYPE(ObservationStatuses, ULong, GOOD = 0, BADHEALTH,
                       OLDEPHEMERIS, ELEVATIONERROR = 6, MISCLOSURE, NODIFFCORR,
                       NOEPHEMERIS, INVALIDIODE, LOCKEDOUT, LOWPOWER, OBSL2,
                       UNKNOWN = 15, NOIONOCORR, NOTUSED, OBSL1, OBSE1, OBSL5,
                       OBSE5, OBSB2, OBSB1, NOSIGNALMATCH = 25, SUPPLEMENTARY,
                       NA = 99, BAD_INTEGRITY, LOSSOFLOCK, NOAMBIGUITY)

DECLARE_ENUM_WITH_TYPE(WheelStatus, ULong, INACTIVE = 0, ACTIVE, USED, UNSYNCED,
                       BAS_MISC, HIGH_ROTATION)

DECLARE_ENUM_WITH_TYPE(HeadingUpdateValues, ULong, INACTIVE = 0, ACTIVE, USED)

// TODO: Define enum value here
// DECLARE_ENUM_WITH_TYPE(EnumType, ValueType, Value ...)

class ReceiverStatus {
   public:
    enum class BIT_ReceiverStatus : UChar {
        ErrorFlag = 0,
        TemperatureStatus,
        VoltageSupplyStatus,
        AntennaPowerStatus,
        LNAFailure,
        AntennaOpenFlag,
        AntennaShortedFlag,
        CPUOverloadFlag,
        COM1BufferOverrunFlag,
        COM2BufferOverrunFlag,
        COM3BufferOverrunFlag,
        LinkOverrunFlag,
        Reserved12,
        AuxTransmitOverrunFlag,
        AGCOutOfRange,
        Reserved15,
        INSReset,
        Reserved17,
        AlmanacFlag_UTCKnown,
        PositionSolutionFlag,
        PositionFixedFlag,
        ClockSteeringStatus,
        ClockModelFlag,
        ExternalOscillatorLockedFlag,
        SoftwareResource,
        Reserved25,
        Reserved26,
        Reserved27,
        Reserved28,
        Auxiliary3StatusEventFlag,
        Auxiliary2StatusEventFlag,
        Auxiliary1StatusEventFlag,
    };

   private:
    ULong value;

   public:
    ReceiverStatus() {}
    ReceiverStatus(const ULong& value) noexcept : value(value) {}
    ReceiverStatus(const ULong&& value) noexcept : value(value) {}
    ReceiverStatus(const ReceiverStatus&) noexcept = default;
    ReceiverStatus& operator=(const ReceiverStatus&) noexcept = default;
    ReceiverStatus(ReceiverStatus&&) noexcept = default;
    ReceiverStatus& operator=(ReceiverStatus&&) noexcept = default;
    ReceiverStatus& operator=(const ULong& value) noexcept {
        this->value = value;
        return *this;
    }
    ReceiverStatus& operator=(const ULong&& value) noexcept {
        this->value = value;
        return *this;
    }
    operator const ULong() noexcept { return this->value; }
};

class MessageType {
   public:
    enum class Mask : Char {
        MeasurementSource = 0x1F,
        Format = 0x60,
        ResponseBit = Char(0x80)
    };

    enum class Format : Char {
        Binary = 0,
        ASCII = 1 << 5,
        AbbreviatedASCII_NMEA = 1 << 6,
        Reserved = (1 << 5) | (1 << 6)
    };

    enum class ResponseBit : Char {
        OriginalMessage = 0,
        ResponseMessage = Char(1 << 7)
    };

   private:
    Char value;

   public:
    MessageType() {}
    MessageType(const Char& value) noexcept : value(value) {}
    MessageType(const Char&& value) noexcept : value(value) {}
    MessageType(const MessageType&) noexcept = default;
    MessageType& operator=(const MessageType&) noexcept = default;
    MessageType(MessageType&&) noexcept = default;
    MessageType& operator=(MessageType&&) noexcept = default;
    MessageType& operator=(const Char& value) noexcept {
        this->value = value;
        return *this;
    }
    MessageType& operator=(const Char&& value) noexcept {
        this->value = value;
        return *this;
    }
    operator const Char() noexcept { return this->value; }
};

class INSExtendedSolutionStatus {
   public:
    enum class BIT_INSExtendedSolutionStatus : ULong {
        PositionUpdate = 0,
        PhaseUpdate,
        ZUPT,
        WheelSensorUpdate,
        HeadingUpdate,
        ConvergedError = 6
    };

   private:
    ULong value;

   public:
    INSExtendedSolutionStatus() {}
    INSExtendedSolutionStatus(const ULong& value) noexcept : value(value) {}
    INSExtendedSolutionStatus(const ULong&& value) noexcept : value(value) {}
    INSExtendedSolutionStatus(const INSExtendedSolutionStatus&) noexcept =
        default;
    INSExtendedSolutionStatus& operator=(
        const INSExtendedSolutionStatus&) noexcept = default;
    INSExtendedSolutionStatus(INSExtendedSolutionStatus&&) noexcept = default;
    INSExtendedSolutionStatus& operator=(INSExtendedSolutionStatus&&) noexcept =
        default;
    INSExtendedSolutionStatus& operator=(const ULong& value) noexcept {
        this->value = value;
        return *this;
    }
    INSExtendedSolutionStatus& operator=(const ULong&& value) noexcept {
        this->value = value;
        return *this;
    }
    operator const ULong() noexcept { return this->value; }
};

class ExtendedSolutionStatus {
   public:
    enum class Mask : UChar {
        Solution = 0x01,
        PseudorangeIonoCorrection = 0x0E,
        RTKASSISTActive = 0x10,
        Antenna = 0x20,
        Reserved = 0xC0
    };

    enum class PseudorangeIonoCorrection : UChar {
        UnknownOrDefaultKlobucharModel = 0,
        KlobucharBroadcast = 1 << 1,
        SBASBroadcast = 2 << 1,
        Multi_frequencyComputed = 3 << 1,
        PSRDiffCorrection = 4 << 1,
        NovAtelBlendedIonoValue = 5 << 1
    };

   private:
    UChar value;

   public:
    ExtendedSolutionStatus() {}
    ExtendedSolutionStatus(const UChar& value) noexcept : value(value) {}
    ExtendedSolutionStatus(const UChar&& value) noexcept : value(value) {}
    ExtendedSolutionStatus(const ExtendedSolutionStatus&) noexcept = default;
    ExtendedSolutionStatus& operator=(const ExtendedSolutionStatus&) noexcept =
        default;
    ExtendedSolutionStatus(ExtendedSolutionStatus&&) noexcept = default;
    ExtendedSolutionStatus& operator=(ExtendedSolutionStatus&&) noexcept =
        default;
    ExtendedSolutionStatus& operator=(const UChar& value) noexcept {
        this->value = value;
        return *this;
    }
    ExtendedSolutionStatus& operator=(const UChar&& value) noexcept {
        this->value = value;
        return *this;
    }
    operator const UChar() noexcept { return this->value; }
};

class BESTPOSGPSAndGLONASSSignalUsedMask {
   public:
    enum class BIT_SignalUsed : UChar {
        GPSL1 = 0,
        GPSL2,
        GPSL5,
        GLONASSL1 = 4,
        GLONASSL2,
    };

   private:
    UChar value;

   public:
    BESTPOSGPSAndGLONASSSignalUsedMask() {}
    BESTPOSGPSAndGLONASSSignalUsedMask(const UChar& value) noexcept
        : value(value) {}
    BESTPOSGPSAndGLONASSSignalUsedMask(const UChar&& value) noexcept
        : value(value) {}
    BESTPOSGPSAndGLONASSSignalUsedMask(
        const BESTPOSGPSAndGLONASSSignalUsedMask&) noexcept = default;
    BESTPOSGPSAndGLONASSSignalUsedMask& operator=(
        const BESTPOSGPSAndGLONASSSignalUsedMask&) noexcept = default;
    BESTPOSGPSAndGLONASSSignalUsedMask(
        BESTPOSGPSAndGLONASSSignalUsedMask&&) noexcept = default;
    BESTPOSGPSAndGLONASSSignalUsedMask& operator=(
        BESTPOSGPSAndGLONASSSignalUsedMask&&) noexcept = default;
    BESTPOSGPSAndGLONASSSignalUsedMask& operator=(const UChar& value) noexcept {
        this->value = value;
        return *this;
    }
    BESTPOSGPSAndGLONASSSignalUsedMask& operator=(
        const UChar&& value) noexcept {
        this->value = value;
        return *this;
    }
    operator const UChar() noexcept { return this->value; }
};

class BESTPOSGalileoAndBeiDouSignalUsedMask {
   public:
    enum class BIT_SignalUsed : UChar {
        GalileoE1 = 0,
        BeiDouB1 = 4,
        BeiDouB2,
    };

   private:
    UChar value;

   public:
    BESTPOSGalileoAndBeiDouSignalUsedMask() {}
    BESTPOSGalileoAndBeiDouSignalUsedMask(const UChar& value) noexcept
        : value(value) {}
    BESTPOSGalileoAndBeiDouSignalUsedMask(const UChar&& value) noexcept
        : value(value) {}
    BESTPOSGalileoAndBeiDouSignalUsedMask(
        const BESTPOSGalileoAndBeiDouSignalUsedMask&) noexcept = default;
    BESTPOSGalileoAndBeiDouSignalUsedMask& operator=(
        const BESTPOSGalileoAndBeiDouSignalUsedMask&) noexcept = default;
    BESTPOSGalileoAndBeiDouSignalUsedMask(
        BESTPOSGalileoAndBeiDouSignalUsedMask&&) noexcept = default;
    BESTPOSGalileoAndBeiDouSignalUsedMask& operator=(
        BESTPOSGalileoAndBeiDouSignalUsedMask&&) noexcept = default;
    BESTPOSGalileoAndBeiDouSignalUsedMask& operator=(
        const UChar& value) noexcept {
        this->value = value;
        return *this;
    }
    BESTPOSGalileoAndBeiDouSignalUsedMask& operator=(
        const UChar&& value) noexcept {
        this->value = value;
        return *this;
    }
    operator const UChar() noexcept { return this->value; }
};

class BESTSATSSignalMask {
   public:
    enum class BIT_GPS : UChar { GPSL1 = 0, GPSL2, GPSL5 };

    enum class BIT_GLONASS : UChar {
        GLONASSL1 = 0,
        GLONASSL2,
    };

    enum class BIT_Galileo : UChar { GalileoE1 = 0 };

    enum class BIT_BeiDou : UChar {
        BeiDouB1 = 0,
        BeiDouB2,
    };

   private:
    ULong value;

   public:
    BESTSATSSignalMask() {}
    BESTSATSSignalMask(const ULong& value) noexcept : value(value) {}
    BESTSATSSignalMask(const ULong&& value) noexcept : value(value) {}
    BESTSATSSignalMask(const BESTSATSSignalMask&) noexcept = default;
    BESTSATSSignalMask& operator=(const BESTSATSSignalMask&) noexcept = default;
    BESTSATSSignalMask(BESTSATSSignalMask&&) noexcept = default;
    BESTSATSSignalMask& operator=(BESTSATSSignalMask&&) noexcept = default;
    BESTSATSSignalMask& operator=(const ULong& value) noexcept {
        this->value = value;
        return *this;
    }
    BESTSATSSignalMask& operator=(const ULong&& value) noexcept {
        this->value = value;
        return *this;
    }
    operator const ULong() noexcept { return this->value; }
};

class IMUStatus {
   public:
    enum class BIT_iIMUFSAS : ULong {
        GyroWarmUp = 4,
        GyroSelfTestActive,
        GyroStatusBitSet,
        GyroTimeOutCommandInterface,
        PowerUpBuiltInTest,
        Interrupt = 10,
        WarmUp = 12,
        InitiatedBuiltInTest = 15,
        Accelerometer = 18,
        AccelerometerTimeOut,
        GyroInitiatedBIT = 21,
        GyroSelfTest,
        GyroTimeOut,
        AnalogToDigital,
        TestMode,
        Software,
        RAM_ROM,
        Operational = 29,
        Interface,
        InterfaceTimeOut
    };

    enum class BIT_LitefLCI1 : ULong {
        IBITErrorFlag = 0,
        CBITErrorFlag,
        CalibrationStatusFlag,
        ModeReadFlag = 4,
        IMUModeIndication1,
        IMUModeIndication2,
        IMUModeIndication3,
        MasterNoGo,
        IMUNoGo,
        AccelerometerZNoGo,
        AccelerometerYNoGo,
        AccelerometerXNoGo,
        GyroscopeZNoGo,
        GyroscopeYNoGo,
        GyroscopeXNoGo,
        MasterWarning,
        IMUWarning,
        AccelerometerZWarning,
        AccelerometerYWarning,
        AccelerometerXWarning,
        GyroscopeZWarning,
        GyroscopeYWarning,
        GyroscopeXWarning
    };

    enum class Mask_LitefLCI1 : ULong { ModeIndication = 0x0F };

    enum class OffsetBit_LitefLCI1 : Char { ModeIndication = 4 };

    enum class ModeIndication : UChar {
        PowerOnBIT = 0,
        StandbyMode = 0x01,
        InitiatedBIT = 0x06,
        IBITReady = 0x07,
        OperationalMode = 0x0D
    };

    enum class BIT_HG1700 : ULong {
        IMUStatus4 = 4,
        IMUStatus5,
        IMUStatus6,
        IMUStatus7,
        IMUStatus27 = 27,
        IMUStatus28,
        IMUStatus29,
        IMUStatus30,
        IMUStatus31,
    };

    enum class BIT_LN200 : ULong {
        IMUStatus0 = 0,
        IMUStatus1,
        IMUStatus2,
        IMUStatus3,
        IMUStatus4,
        IMUStatus5,
        IMUStatus6,
        IMUStatus7,
        IMUStatus8,
        IMUStatus9,
        IMUStatus10,
        IMUStatus11,
        IMUStatus12,
        IMUStatus13,
        IMUStatus14,
        IMUStatus24 = 24,
        IMUStatus25,
        IMUStatus26,
        IMUStatus27,
        IMUStatus28,
        IMUStatus30 = 30,
    };

    enum class BIT_ISA100 : ULong {
        MaintenanceIndication = 0,
        AccelerometersInvalid,
        AccelerometerXWarning,
        AccelerometerYWarning,
        AccelerometerZWarning,
        AccelerometerXNOGO,
        AccelerometerYNOGO,
        AccelerometerZNOGO,
        ResetOccurred,
        GyroscopesInvalid,
        GyroscopeXWarning,
        GyroscopeYWarning,
        GyroscopeZWarning,
        GyroscopeXNOGO,
        GyroscopeYNOGO,
        GyroscopeZNOGO,
    };

    enum class Mask_ISA100_100C : ULong { Temperature = 0x0003 };

    enum class OffsetBit_ISA100_100C : ULong { Temperature = 16 };

    constexpr static double ISA100_100CTemperatureScaleRatio = 3.90625e-3;

    enum class CPT : ULong {
        GyroXStatus = 0,
        GyroYStatus,
        GyroZStatus,
        AccelerometerXStatus = 4,
        AccelerometerYStatus,
        AccelerometerZStatus,
    };

    enum class Mask_CPT : ULong { DataSequenceCounter = 0x03 };

    enum class OffsetBit_CPT : ULong { DataSequenceCounter = 8 };

    enum class BIT_KVH1750_1725 : ULong {
        GyroXStatus = 0,
        GyroYStatus,
        GyroZStatus,
        AccelerometerXStatus = 4,
        AccelerometerYStatus,
        AccelerometerZStatus,
    };

    enum class Mask_KVH1750_1725 : ULong {
        DataSequenceCounter = 0x3,
        Temperature = 0x0003
    };

    enum class OffsetBit_KVH1750_1725 : ULong {
        DataSequenceCounter = 8,
        Temperature = 16
    };

    enum class BIT_HG1900_1930 : ULong {
        IMUStatus4 = 4,
        IMUStatus5,
        IMUStatus6,
        IMUStatus7,
        IMUStatus24 = 24,
        IMUStatus26 = 26,
        IMUStatus27,
        IMUStatus28,
        IMUStatus29,
        IMUStatus30,
    };

    enum class BIT_ADIS16488_IGMA1 : ULong {
        AlarmStatusFlag = 0,
        SPICommunicationError = 3,
        SensorOverRange,
        InitialSelfTestFailure,
        FlashMemoryFailure,
        ProcessingOverrun,
        SelfTestFailure_XAxisGyro,
        SelfTestFailure_YAxisGyro,
        SelfTestFailure_ZAxisGyro,
        SelfTestFailure_XAxisAccelerometer,
        SelfTestFailure_YAxisAccelerometer,
        SelfTestFailure_ZAxisAccelerometer
    };

    enum class Mask_ADIS16488_IGMA1 : ULong { Temperature = 0x0003 };

    enum class OffsetBit_ADIS16488_IGMA1 : ULong { Temperature = 16 };

    constexpr static double ADIS16488_IGMA1TemperatureScaleRatio = 0.00565;
    constexpr static double ADIS16488_IGMA1TemperatureOffset = 25;

    enum class Mask_STIM300_IGMS1 : ULong {
        GyroStatus = 0xFF,
        Temperature = 0x00030000,
        AccelerometerStatus = 0xFF00
    };
    enum class OffsetBit_STIM300_IGMS1 : ULong {
        GyroStatus = 0,
        AccelerometerStatus = 8,
        Temperature = 16
    };

    enum class BIT_STIM300_Status : ULong {
        XChannel = 0,
        YChannel,
        ZChannel,
        ErrorInMeasurementChannel,
        Overload,
        OutsideOperatingConditions,
        Startup,
        SystemIntegrityError
    };

    constexpr static double STIM300_IGMS1TemperatureScaleRatio =
        1 / (double)(2UL << 8);

    enum class BIT_uIMU : ULong {
        ResetAcknowledged = 0,
        GyrosNotInitialized,
        GyroXWarning,
        GyroYWarning,
        GyroZWarning,
        GyroXNOGO,
        GyroYNOGO,
        GyroZNOGO,
        AccelsNotInitialized = 9,
        AccelXWarning,
        AccelYWarning,
        AccelZWarning,
        AccelXNOGO,
        AccelYNOGO,
        AccelZNOGO,
    };

    enum class Mask_uIMU : ULong { Temperature = 0x0003 };

    enum class OffsetBit_uIMU : ULong { Temperature = 16 };

    constexpr static double uIMUTemperatureScaleRatio = 3.90625e-3;

   private:
    ULong value;

   public:
    IMUStatus() {}
    IMUStatus(const ULong& value) noexcept : value(value) {}
    IMUStatus(const ULong&& value) noexcept : value(value) {}
    IMUStatus(const IMUStatus&) noexcept = default;
    IMUStatus& operator=(const IMUStatus&) noexcept = default;
    IMUStatus(IMUStatus&&) noexcept = default;
    IMUStatus& operator=(IMUStatus&&) noexcept = default;
    IMUStatus& operator=(const ULong& value) noexcept {
        this->value = value;
        return *this;
    }
    IMUStatus& operator=(const ULong&& value) noexcept {
        this->value = value;
        return *this;
    }
    operator const ULong() noexcept { return this->value; }
};

DECLARE_ENUM_WITH_TYPE(IMUError, UChar, Okay = 0x00, Error)

DECLARE_ENUM_WITH_TYPE(IMUType, UChar, IMU_UNKNOWN = 0, IMU_HG1700_AG11,
                       IMU_HG1700_AG17 = 4, IMU_HG1900_CA29, IMU_LN200 = 8,
                       IMU_HG1700_AG58 = 11, IMU_HG1700_AG62, IMU_IMAR_FSAS,
                       IMU_KVH_COTS = 16, IMU_LITEF_LCI1 = 19, IMU_HG1930_AA99,
                       IMU_ISA100C = 26, IMU_HG1900_CA50, IMU_HG1930_CA50,
                       IMU_ADIS16488 = 31, IMU_STIM300, IMU_KVH_1750,
                       IMU_ISA100, IMU_ISA100_400HZ = 38, IMU_ISA100C_400HZ,
                       IMU_KVH_1725 = 45, IMU_LITEF_MICROIMU = 52)

template <typename T>
inline void toggleEndian(const T* msg) {
    auto&& len = sizeof(T);
    for (int i = 0; i < (len >> 1); ++i) {
        std::swap(*(((char*)msg) + i), *(((char*)msg) + len - i - 1));
    }
}

#define TOGGLE_SPAN_ENDIAN(x)    \
    {                            \
        auto tx = x;       \
        SPAN::toggleEndian(&tx); \
        x = tx;            \
    }
}  // namespace SPAN
#endif