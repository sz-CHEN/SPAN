#ifndef SPAN_OEM6_Message_H
#define SPAN_OEM6_Message_H
#include <cmath>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>
#include "SPANHeader.h"
#include "SPANType.h"
namespace SPAN {
#define DEFINE_COMMA ,
#define DEFINE_SPAN_MESSAGE_ALIAS(                                            \
    TSZ, T, ALIAS_T, VAR, FROM_BIN_WITHOUT_HEADER, FROM_ASCII_WITHOUT_HEADER, \
    TOGGLE_ENDIAN, ...)                                                       \
    ALIGN_REGION(1)                                                           \
    struct T;                                                                 \
    typedef struct T ALIAS_T;                                                 \
    struct ALIGN(1) T {                                                       \
        Header header;                                                        \
        VAR;                                                                  \
        static bool fromBinWithoutHeader(const std::string &str, T &__t) {    \
            FROM_BIN_WITHOUT_HEADER                                           \
        }                                                                     \
        static bool fromAsciiWithoutHeader(                                   \
            const std::vector<std::string> &str, T &__t) {                    \
            try {                                                             \
                FROM_ASCII_WITHOUT_HEADER                                     \
            } catch (...) {                                                   \
                return false;                                                 \
            }                                                                 \
        }                                                                     \
        void toggleEndian(){TOGGLE_ENDIAN} __VA_ARGS__                        \
    };                                                                        \
    static_assert(sizeof(T) - sizeof(Header) == TSZ, "size error");           \
    ALIGN_ENDREGION

#define DEFINE_SPAN_MESSAGE(TSZ, T, VAR, FROM_BIN_WITHOUT_HEADER,          \
                            FROM_ASCII_WITHOUT_HEADER, TOGGLE_ENDIAN, ...) \
    DEFINE_SPAN_MESSAGE_ALIAS(TSZ, T, T, VAR, FROM_BIN_WITHOUT_HEADER,     \
                              FROM_ASCII_WITHOUT_HEADER, TOGGLE_ENDIAN,    \
                              __VA_ARGS__)

#define DEFINE_SPAN_MESSAGE_WITH_SHORT_ALIAS(                                  \
    TSZ, T, ALIAS_T, VAR, FROM_BIN_WITHOUT_HEADER, FROM_ASCII_WITHOUT_HEADER,  \
    TOGGLE_ENDIAN, ...)                                                        \
    ALIGN_REGION(1)                                                            \
    struct T;                                                                  \
    typedef struct T T;                                                        \
    struct ALIAS_T;                                                            \
    typedef struct ALIAS_T ALIAS_T;                                            \
    struct ALIGN(1) T {                                                        \
        Header header;                                                         \
        VAR;                                                                   \
        static bool fromBinWithoutHeader(const std::string &str, T &__t) {     \
            FROM_BIN_WITHOUT_HEADER                                            \
        }                                                                      \
        static bool fromAsciiWithoutHeader(                                    \
            const std::vector<std::string> &str, T &__t) {                     \
            FROM_ASCII_WITHOUT_HEADER                                          \
        }                                                                      \
        void toggleEndian(){TOGGLE_ENDIAN} __VA_ARGS__                         \
    };                                                                         \
    typedef struct ALIGN(1) ALIAS_T {                                          \
        ShortHeader header;                                                    \
        VAR;                                                                   \
        static bool fromBinWithoutHeader(const std::string &str,               \
                                         ALIAS_T &__t) {                       \
            FROM_BIN_WITHOUT_HEADER                                            \
        }                                                                      \
        static bool fromAsciiWithoutHeader(                                    \
            const std::vector<std::string> &str, ALIAS_T &__t) {               \
            FROM_ASCII_WITHOUT_HEADER                                          \
        }                                                                      \
        void toggleEndian(){TOGGLE_ENDIAN} __VA_ARGS__                         \
    } ALIAS_T;                                                                 \
    static_assert(sizeof(T) - sizeof(Header) == TSZ, "size error");            \
    static_assert(sizeof(ALIAS_T) - sizeof(ShortHeader) == TSZ, "size error"); \
    ALIGN_ENDREGION

#define DEFINE_SPAN_MESSAGE_WITH_SHORT(TSZ, T, VAR, FROM_BIN_WITHOUT_HEADER,   \
                                       FROM_ASCII_WITHOUT_HEADER,              \
                                       TOGGLE_ENDIAN, ...)                     \
    DEFINE_SPAN_MESSAGE_WITH_SHORT_ALIAS(                                      \
        TSZ, T, T##S, VAR, FROM_BIN_WITHOUT_HEADER, FROM_ASCII_WITHOUT_HEADER, \
        TOGGLE_ENDIAN, __VA_ARGS__)

DEFINE_SPAN_MESSAGE(44, TIME, ClockModelStatus clock_status; Double offset;
                    Double offset_std; Double utc_offset; ULong utc_year;
                    UChar utc_month; UChar utc_day; UChar utc_hour;
                    UChar utc_min; ULong utc_ms; UTCStatus utc_status;
                    ,
                    {
                        if (str.size() < sizeof(__t) - sizeof(__t.header))
                            return false;
                        memcpy(&__t.clock_status DEFINE_COMMA str.data()
                                    DEFINE_COMMA sizeof(__t) -
                               sizeof(__t.header));
                        DEFINE_MARCO_SPAN_MESSAGE_TOGGLE(__t)
                        return true;
                    },
                    {
                        if (str.size() < 11) {
                            return false;
                        }
                        __t.clock_status = ClockModelStatusFromName(str[0]);
                        __t.offset = stoD(str[1]);
                        __t.offset_std = stoD(str[2]);
                        __t.utc_offset = stoD(str[3]);
                        __t.utc_year = stoUL(str[4]);
                        __t.utc_month = stoUC(str[5]);
                        __t.utc_day = stoUC(str[6]);
                        __t.utc_hour = stoUC(str[7]);
                        __t.utc_min = stoUC(str[8]);
                        __t.utc_ms = stoUL(str[9]);
                        __t.utc_status = UTCStatusFromName(str[10]);
                        return true;
                    },
                    {
                        TOGGLE_SPAN_ENDIAN(clock_status);
                        TOGGLE_SPAN_ENDIAN(offset);
                        TOGGLE_SPAN_ENDIAN(offset_std);
                        TOGGLE_SPAN_ENDIAN(utc_offset);
                        TOGGLE_SPAN_ENDIAN(utc_year);
                        TOGGLE_SPAN_ENDIAN(utc_ms);
                        TOGGLE_SPAN_ENDIAN(utc_status);
                    })

DEFINE_SPAN_MESSAGE_ALIAS(
    72, BESTPOS, BESTGNSSPOS, SolutionStatus sol_stat;
    PositionOrVelocityType pos_type; Double lat; Double lon; Double hgt;
    Float undulation; DatumTransfomationParams datum_ID; Float lat_delta;
    Float lon_delta; Float hgt_delta; Char stn_id[4]; Float diff_age;
    Float sol_age; UChar SVs; UChar soln_SVs; UChar soln_L1_SVs;
    UChar soln_multi_Svs; UChar reserved; ExtendedSolutionStatus ext_sol_stat;
    BESTPOSGalileoAndBeiDouSignalUsedMask Galileo_BeiDou_sig_mask;
    BESTPOSGPSAndGLONASSSignalUsedMask GPS_GLONASS_sig_mask;
    ,
    {
        if (str.size() < sizeof(__t) - sizeof(__t.header)) return false;
        memcpy(&__t.sol_stat DEFINE_COMMA str.data() DEFINE_COMMA sizeof(__t) -
               sizeof(__t.header));
        DEFINE_MARCO_SPAN_MESSAGE_TOGGLE(__t)
        return true;
    },
    {
        if (str.size() < 21) {
            return false;
        }
        __t.sol_stat = SolutionStatusFromName(str[0]);
        __t.pos_type = PositionOrVelocityTypeFromName(str[1]);
        __t.lat = stoD(str[2]);
        __t.lon = stoD(str[3]);
        __t.hgt = stoD(str[4]);
        __t.undulation = stoF(str[5]);
        __t.datum_ID = DatumTransfomationParamsFromName(str[6]);
        __t.lat_delta = stoF(str[7]);
        __t.lon_delta = stoF(str[8]);
        __t.hgt_delta = stoF(str[9]);
        std::string s(str[10].begin() + 1, str[10].end() - 1);
        for (std::size_t i = 0; i < s.size() && i < 4; ++i) {
            __t.stn_id[i] = s[i];
        }
        __t.diff_age = stoF(str[11]);
        __t.sol_age = stoF(str[12]);
        __t.SVs = stoUC(str[13]);
        __t.soln_SVs = stoUC(str[14]);
        __t.soln_L1_SVs = stoUC(str[15]);
        __t.soln_multi_Svs = stoUC(str[16]);
        __t.reserved = stoUC(str[17]);
        __t.ext_sol_stat = stoUC(str[18], 0, 16);
        __t.Galileo_BeiDou_sig_mask = stoUC(str[19], 0, 16);
        __t.GPS_GLONASS_sig_mask = stoUC(str[20], 0, 16);
        return true;
    },
    {
        TOGGLE_SPAN_ENDIAN(sol_stat);
        TOGGLE_SPAN_ENDIAN(pos_type);
        TOGGLE_SPAN_ENDIAN(lat);
        TOGGLE_SPAN_ENDIAN(lon);
        TOGGLE_SPAN_ENDIAN(hgt);
        TOGGLE_SPAN_ENDIAN(undulation);
        TOGGLE_SPAN_ENDIAN(datum_ID);
        TOGGLE_SPAN_ENDIAN(lat_delta);
        TOGGLE_SPAN_ENDIAN(lon_delta);
        TOGGLE_SPAN_ENDIAN(hgt_delta);
        TOGGLE_SPAN_ENDIAN(diff_age);
        TOGGLE_SPAN_ENDIAN(sol_age);
    })

DEFINE_SPAN_MESSAGE(44, BESTVEL, SolutionStatus sol_status;
                    PositionOrVelocityType vel_type; Float latency; Float age;
                    Double hor_spd; Double trk_gnd; Double vert_spd;
                    Float reserved;
                    ,
                    {
                        if (str.size() < sizeof(__t) - sizeof(__t.header))
                            return false;
                        memcpy(&__t.sol_status DEFINE_COMMA str.data()
                                    DEFINE_COMMA sizeof(__t) -
                               sizeof(__t.header));
                        DEFINE_MARCO_SPAN_MESSAGE_TOGGLE(__t)
                        return true;
                    },
                    {
                        if (str.size() < 8) {
                            return false;
                        }
                        __t.sol_status = SolutionStatusFromName(str[0]);
                        __t.vel_type = PositionOrVelocityTypeFromName(str[1]);
                        __t.latency = stoF(str[2]);
                        __t.age = stoF(str[3]);
                        __t.hor_spd = stoD(str[4]);
                        __t.trk_gnd = stoD(str[5]);
                        __t.vert_spd = stoD(str[6]);
                        __t.reserved = stoF(str[7]);
                        return true;
                    },
                    {
                        TOGGLE_SPAN_ENDIAN(sol_status);
                        TOGGLE_SPAN_ENDIAN(vel_type);
                        TOGGLE_SPAN_ENDIAN(latency);
                        TOGGLE_SPAN_ENDIAN(age);
                        TOGGLE_SPAN_ENDIAN(hor_spd);
                        TOGGLE_SPAN_ENDIAN(trk_gnd);
                        TOGGLE_SPAN_ENDIAN(vert_spd);
                        TOGGLE_SPAN_ENDIAN(reserved);
                    })

DEFINE_SPAN_MESSAGE_WITH_SHORT(
    40, INSPOS, ULong week; Double seconds_into_week; Double latitude;
    Double longitude; Double height; InertialSolutionStatus status;
    ,
    {
        if (str.size() < sizeof(__t) - sizeof(__t.header)) return false;
        memcpy(&__t.week DEFINE_COMMA str.data() DEFINE_COMMA sizeof(__t) -
               sizeof(__t.header));
        DEFINE_MARCO_SPAN_MESSAGE_TOGGLE(__t)
        return true;
    },
    {
        if (str.size() < 6) {
            return false;
        }
        __t.week = stoUL(str[0]);
        __t.seconds_into_week = stoD(str[1]);
        __t.latitude = stoD(str[2]);
        __t.longitude = stoD(str[3]);
        __t.height = stoD(str[4]);
        __t.status = InertialSolutionStatusFromName(str[5]);
        return true;
    },
    {
        TOGGLE_SPAN_ENDIAN(week);
        TOGGLE_SPAN_ENDIAN(seconds_into_week);
        TOGGLE_SPAN_ENDIAN(latitude);
        TOGGLE_SPAN_ENDIAN(longitude);
        TOGGLE_SPAN_ENDIAN(height);
        TOGGLE_SPAN_ENDIAN(status);
    })

DEFINE_SPAN_MESSAGE_WITH_SHORT(
    88, INSPVA, ULong week; Double seconds; Double latitude; Double longitude;
    Double height; Double north_velocity; Double east_velocity;
    Double up_velocity; Double roll; Double pitch; Double azimuth;
    InertialSolutionStatus status;
    ,
    {
        if (str.size() < sizeof(__t) - sizeof(__t.header)) return false;
        memcpy(&__t.week DEFINE_COMMA str.data() DEFINE_COMMA sizeof(__t) -
               sizeof(__t.header));
        DEFINE_MARCO_SPAN_MESSAGE_TOGGLE(__t)
        return true;
    },
    {
        if (str.size() < 12) {
            return false;
        }
        __t.week = stoUL(str[0]);
        __t.seconds = stoD(str[1]);
        __t.latitude = stoD(str[2]);
        __t.longitude = stoD(str[3]);
        __t.height = stoD(str[4]);
        __t.north_velocity = stoD(str[5]);
        __t.east_velocity = stoD(str[6]);
        __t.up_velocity = stoD(str[7]);
        __t.roll = stoD(str[8]);
        __t.pitch = stoD(str[9]);
        __t.azimuth = stoD(str[10]);
        __t.status = InertialSolutionStatusFromName(str[11]);
        return true;
    },
    {
        TOGGLE_SPAN_ENDIAN(week);
        TOGGLE_SPAN_ENDIAN(seconds);
        TOGGLE_SPAN_ENDIAN(latitude);
        TOGGLE_SPAN_ENDIAN(longitude);
        TOGGLE_SPAN_ENDIAN(height);
        TOGGLE_SPAN_ENDIAN(north_velocity);
        TOGGLE_SPAN_ENDIAN(east_velocity);
        TOGGLE_SPAN_ENDIAN(up_velocity);
        TOGGLE_SPAN_ENDIAN(roll);
        TOGGLE_SPAN_ENDIAN(pitch);
        TOGGLE_SPAN_ENDIAN(azimuth);
        TOGGLE_SPAN_ENDIAN(status);
    })

DEFINE_SPAN_MESSAGE_WITH_SHORT(
    40, INSVEL, ULong week; Double seconds_into_week; Double north_velocity;
    Double east_velocity; Double up_velocity; InertialSolutionStatus status;
    ,
    {
        if (str.size() < sizeof(__t) - sizeof(__t.header)) return false;
        memcpy(&__t.week DEFINE_COMMA str.data() DEFINE_COMMA sizeof(__t) -
               sizeof(__t.header));
        DEFINE_MARCO_SPAN_MESSAGE_TOGGLE(__t)
        return true;
    },
    {
        if (str.size() < 6) {
            return false;
        }
        __t.week = stoUL(str[0]);
        __t.seconds_into_week = stoD(str[1]);
        __t.north_velocity = stoD(str[2]);
        __t.east_velocity = stoD(str[3]);
        __t.up_velocity = stoD(str[4]);
        __t.status = InertialSolutionStatusFromName(str[5]);
        return true;
    },
    {
        TOGGLE_SPAN_ENDIAN(week);
        TOGGLE_SPAN_ENDIAN(seconds_into_week);
        TOGGLE_SPAN_ENDIAN(north_velocity);
        TOGGLE_SPAN_ENDIAN(east_velocity);
        TOGGLE_SPAN_ENDIAN(up_velocity);
        TOGGLE_SPAN_ENDIAN(status);
    })

DEFINE_SPAN_MESSAGE_WITH_SHORT(
    40, INSSPD, ULong week; Double seconds_into_week; Double trk_gnd;
    Double horizontal_speed; Double vertical_speed;
    InertialSolutionStatus status;
    ,
    {
        if (str.size() < sizeof(__t) - sizeof(__t.header)) return false;
        memcpy(&__t.week DEFINE_COMMA str.data() DEFINE_COMMA sizeof(__t) -
               sizeof(__t.header));
        DEFINE_MARCO_SPAN_MESSAGE_TOGGLE(__t)
        return true;
    },
    {
        if (str.size() < 6) {
            return false;
        }
        __t.week = stoUL(str[0]);
        __t.seconds_into_week = stoD(str[1]);
        __t.trk_gnd = stoD(str[2]);
        __t.horizontal_speed = stoD(str[3]);
        __t.vertical_speed = stoD(str[4]);
        __t.status = InertialSolutionStatusFromName(str[5]);
        return true;
    },
    {
        TOGGLE_SPAN_ENDIAN(week);
        TOGGLE_SPAN_ENDIAN(seconds_into_week);
        TOGGLE_SPAN_ENDIAN(trk_gnd);
        TOGGLE_SPAN_ENDIAN(horizontal_speed);
        TOGGLE_SPAN_ENDIAN(vertical_speed);
        TOGGLE_SPAN_ENDIAN(status);
    })

DEFINE_SPAN_MESSAGE_WITH_SHORT(
    40, INSATT, ULong week; Double seconds_into_week; Double roll; Double pitch;
    Double azimuth; InertialSolutionStatus status;
    ,
    {
        if (str.size() < sizeof(__t) - sizeof(__t.header)) return false;
        memcpy(&__t.week DEFINE_COMMA str.data() DEFINE_COMMA sizeof(__t) -
               sizeof(__t.header));
        DEFINE_MARCO_SPAN_MESSAGE_TOGGLE(__t)
        return true;
    },
    {
        if (str.size() < 6) {
            return false;
        }
        __t.week = stoUL(str[0]);
        __t.seconds_into_week = stoD(str[1]);
        __t.roll = stoD(str[2]);
        __t.pitch = stoD(str[3]);
        __t.azimuth = stoD(str[4]);
        __t.status = InertialSolutionStatusFromName(str[5]);
        return true;
    },
    {
        TOGGLE_SPAN_ENDIAN(week);
        TOGGLE_SPAN_ENDIAN(seconds_into_week);
        TOGGLE_SPAN_ENDIAN(roll);
        TOGGLE_SPAN_ENDIAN(pitch);
        TOGGLE_SPAN_ENDIAN(azimuth);
        TOGGLE_SPAN_ENDIAN(status);
    })

DEFINE_SPAN_MESSAGE_WITH_SHORT(
    228, INSCOV, ULong week; Double seconds_into_week;
    Double position_covariance[9]; Double attitude_covariance[9];
    Double velocity_covariance[9];
    ,
    {
        if (str.size() < sizeof(__t) - sizeof(__t.header)) return false;
        memcpy(&__t.week DEFINE_COMMA str.data() DEFINE_COMMA sizeof(__t) -
               sizeof(__t.header));
        DEFINE_MARCO_SPAN_MESSAGE_TOGGLE(__t)
        return true;
    },
    {
        if (str.size() < 29) {
            return false;
        }
        __t.week = stoUL(str[0]);
        __t.seconds_into_week = stoD(str[1]);
        for (int i = 0; i < 9; ++i) {
            __t.position_covariance[i] = stoD(str[i + 2]);
            __t.attitude_covariance[i] = stoD(str[i + 11]);
            __t.velocity_covariance[i] = stoD(str[i + 20]);
        }
        return true;
    },
    {
        TOGGLE_SPAN_ENDIAN(week);
        TOGGLE_SPAN_ENDIAN(seconds_into_week);
        for (int i = 0; i < 9; ++i) {
            TOGGLE_SPAN_ENDIAN(position_covariance[i]);
            TOGGLE_SPAN_ENDIAN(attitude_covariance[i]);
            TOGGLE_SPAN_ENDIAN(velocity_covariance[i]);
        }
    })

struct BESTSATS_entry;
typedef struct BESTSATS_entry BESTSATS_entry;
struct BESTSATS_entry {
    SatelliteSystem system;
    ULong satellite_id;
    ObservationStatuses status;
    BESTSATSSignalMask signal_mask;

    static bool fromBin(const std::string &str, BESTSATS_entry &__t) {
        if (str.size() < sizeof(BESTSATS_entry)) {
            return false;
        }
        memcpy(&__t, str.data(), sizeof(BESTSATS_entry));
        DEFINE_MARCO_SPAN_MESSAGE_TOGGLE(__t)
        return true;
    }

    static bool fromAscii(const std::vector<std::string> &str,
                          BESTSATS_entry &__t) {
        if (str.size() < 4) {
            return false;
        }
        __t.system = SatelliteSystemFromName(str[0]);
        size_t index = str[1].npos;
        if ((index = str[1].find('-')) != str[1].npos) {
            __t.satellite_id = stoUS(str[1].substr(0, index)) & 0x03;
            __t.satellite_id |= (0x03 & stoUS(str[1].substr(index + 1))) << 2;
        } else {
            __t.satellite_id = std::stoul(str[1]);
        }
        __t.status = ObservationStatusesFromName(str[2]);
        __t.signal_mask = stoUL(str[3], 0, 16);
        return true;
    }

    void toggleEndian() {
        TOGGLE_SPAN_ENDIAN(system);
        TOGGLE_SPAN_ENDIAN(satellite_id);
        TOGGLE_SPAN_ENDIAN(status);
        TOGGLE_SPAN_ENDIAN(signal_mask);
    }
};

DEFINE_SPAN_MESSAGE(
    4 + sizeof(std::vector<BESTSATS_entry>), BESTSATS, ULong entries_num;
    std::vector<BESTSATS_entry> entries;
    ,
    {
        if (str.size() < sizeof(ULong)) return false;
        __t.entries_num = *(ULong *)&str[0];
        TOGGLE_SPAN_ENDIAN(__t.entries_num);
        if ((str.size() - sizeof(ULong)) % sizeof(BESTSATS_entry)) {
            return false;
        }
        BESTSATS_entry entry;
        for (ULong i = 0; i < __t.entries_num; ++i) {
            memcpy(&entry DEFINE_COMMA str.data() + i * sizeof(BESTSATS_entry) +
                   1 DEFINE_COMMA sizeof(entry));
            DEFINE_MARCO_SPAN_MESSAGE_TOGGLE(entry)
            __t.entries.push_back(entry);
        }
        return true;
    },
    {
        if (str.size() < 1) {
            return false;
        }
        if ((str.size() - 1) % 4) {
            return false;
        }
        __t.entries_num = stoUL(str[0]);
        for (ULong i = 0; i < __t.entries_num; ++i) {
            BESTSATS_entry entry;
            entry.system = SatelliteSystemFromName(str[1 + (i << 2)]);
            size_t index = str[1].npos;
            if ((index = str[1].find('-')) != str[1].npos) {
                entry.satellite_id = stoUS(str[1].substr(0, index)) & 0x03;
                entry.satellite_id |= (0x03 & stoUS(str[1].substr(index + 1)))
                                      << 2;
            } else {
                entry.satellite_id = stoUL(str[1]);
            }
            entry.status = ObservationStatusesFromName(str[3 + (i << 2)]);
            entry.signal_mask = stoUL(str[4 + (i << 2)], 0, 16);
        }
        return true;
    },
    {
        TOGGLE_SPAN_ENDIAN(entries_num);
        for (auto &entry : entries) {
            entry.toggleEndian();
        }
    })

DEFINE_SPAN_MESSAGE(126, INSPVAX, InertialSolutionStatus INS_status;
                    PositionOrVelocityType pos_type; Double lat; Double lon;
                    Double height; Float undulation; Double north_vel;
                    Double east_vel; Double up_vel; Double roll; Double pitch;
                    Double azimuth; Float lat_delta; Float lon_delta;
                    Float height_delta; Float north_vel_delta;
                    Float east_vel_delta; Float up_vel_delta; Float roll_delta;
                    Float pitch_delta; Float azimuth_delta;
                    INSExtendedSolutionStatus ext_sol_stat;
                    UShort time_since_update;
                    ,
                    {
                        if (str.size() < sizeof(__t) - sizeof(__t.header))
                            return false;
                        memcpy(&__t.INS_status DEFINE_COMMA str.data()
                                    DEFINE_COMMA sizeof(__t) -
                               sizeof(__t.header));
                        DEFINE_MARCO_SPAN_MESSAGE_TOGGLE(__t)
                        return true;
                    },
                    {
                        if (str.size() < 23) {
                            return false;
                        }
                        __t.INS_status = InertialSolutionStatusFromName(str[0]);
                        __t.pos_type = PositionOrVelocityTypeFromName(str[1]);
                        __t.lat = stoD(str[2]);
                        __t.lon = stoD(str[3]);
                        __t.height = stoD(str[4]);
                        __t.undulation = stoF(str[5]);
                        __t.north_vel = stoD(str[6]);
                        __t.east_vel = stoD(str[7]);
                        __t.up_vel = stoD(str[8]);
                        __t.roll = stoD(str[9]);
                        __t.pitch = stoD(str[10]);
                        __t.azimuth = stoD(str[11]);
                        __t.lat_delta = stoF(str[12]);
                        __t.lon_delta = stoF(str[13]);
                        __t.height_delta = stoF(str[14]);
                        __t.north_vel_delta = stoF(str[15]);
                        __t.east_vel_delta = stoF(str[16]);
                        __t.up_vel_delta = stoF(str[17]);
                        __t.roll_delta = stoF(str[18]);
                        __t.pitch_delta = stoF(str[19]);
                        __t.azimuth_delta = stoF(str[20]);
                        __t.ext_sol_stat = stoUL(str[21], 0, 16);
                        __t.time_since_update = stoUS(str[22]);
                        return true;
                    },
                    {
                        TOGGLE_SPAN_ENDIAN(INS_status);
                        TOGGLE_SPAN_ENDIAN(pos_type);
                        TOGGLE_SPAN_ENDIAN(lat);
                        TOGGLE_SPAN_ENDIAN(lon);
                        TOGGLE_SPAN_ENDIAN(height);
                        TOGGLE_SPAN_ENDIAN(undulation);
                        TOGGLE_SPAN_ENDIAN(north_vel);
                        TOGGLE_SPAN_ENDIAN(east_vel);
                        TOGGLE_SPAN_ENDIAN(up_vel);
                        TOGGLE_SPAN_ENDIAN(roll);
                        TOGGLE_SPAN_ENDIAN(pitch);
                        TOGGLE_SPAN_ENDIAN(azimuth);
                        TOGGLE_SPAN_ENDIAN(lat_delta);
                        TOGGLE_SPAN_ENDIAN(lon_delta);
                        TOGGLE_SPAN_ENDIAN(height_delta);
                        TOGGLE_SPAN_ENDIAN(north_vel_delta);
                        TOGGLE_SPAN_ENDIAN(east_vel_delta);
                        TOGGLE_SPAN_ENDIAN(up_vel_delta);
                        TOGGLE_SPAN_ENDIAN(roll_delta);
                        TOGGLE_SPAN_ENDIAN(pitch_delta);
                        TOGGLE_SPAN_ENDIAN(azimuth_delta);
                        TOGGLE_SPAN_ENDIAN(ext_sol_stat);
                        TOGGLE_SPAN_ENDIAN(time_since_update);
                    })

DEFINE_SPAN_MESSAGE_WITH_SHORT(
    40, RAWIMU, ULong week; Double seconds_into_week; IMUStatus IMU_status;
    Long Z_accel; Long _Y_accel; Long X_accel; Long Z_gyro; Long _Y_gyro;
    Long X_gyro;
    ,
    {
        if (str.size() < sizeof(__t) - sizeof(__t.header)) return false;
        memcpy(&__t.week DEFINE_COMMA str.data() DEFINE_COMMA sizeof(__t) -
               sizeof(__t.header));
        DEFINE_MARCO_SPAN_MESSAGE_TOGGLE(__t)
        return true;
    },
    {
        if (str.size() < 9) {
            return false;
        }
        __t.week = stoUL(str[0]);
        __t.seconds_into_week = stoD(str[1]);
        __t.IMU_status = stoUL(str[2], 0, 16);
        __t.Z_accel = stoL(str[3]);
        __t._Y_accel = stoL(str[4]);
        __t.X_accel = stoL(str[5]);
        __t.Z_gyro = stoL(str[6]);
        __t._Y_gyro = stoL(str[7]);
        __t.X_gyro = stoL(str[8]);

        return true;
    },
    {
        TOGGLE_SPAN_ENDIAN(week);
        TOGGLE_SPAN_ENDIAN(seconds_into_week);
        TOGGLE_SPAN_ENDIAN(IMU_status);
        TOGGLE_SPAN_ENDIAN(Z_accel);
        TOGGLE_SPAN_ENDIAN(_Y_accel);
        TOGGLE_SPAN_ENDIAN(X_accel);
        TOGGLE_SPAN_ENDIAN(Z_gyro);
        TOGGLE_SPAN_ENDIAN(_Y_gyro);
        TOGGLE_SPAN_ENDIAN(X_gyro);
    },
    static void GetScaleFactors(SPAN::IMUType imu_type, long double &gyroScale,
                                long double &accelScale) {
        accelScale = 1;
        gyroScale = 1;
        switch (imu_type) {
            case SPAN::IMUType::IMU_HG1700_AG11:
            case SPAN::IMUType::IMU_HG1700_AG58:
            case SPAN::IMUType::IMU_HG1900_CA29:
            case SPAN::IMUType::IMU_HG1900_CA50:
            case SPAN::IMUType::IMU_HG1930_AA99:
            case SPAN::IMUType::IMU_HG1930_CA50:
                gyroScale = 1 / ((long double)(1ULL << 33));
                accelScale = 1 / ((long double)(1ULL << 27));
                break;
            case SPAN::IMUType::IMU_HG1700_AG17:
            case SPAN::IMUType::IMU_HG1700_AG62:
                gyroScale = 1 / ((long double)(1ULL << 33));
                accelScale = 1 / ((long double)(1ULL << 26));
                break;
            case SPAN::IMUType::IMU_KVH_COTS:
            case SPAN::IMUType::IMU_KVH_1750:
                gyroScale = 1 / (10 * (long double)3600.0 * 256.0);
                accelScale = 1 / (10 * (long double)(1ULL << 16));
                break;
            case SPAN::IMUType::IMU_IMAR_FSAS:
                gyroScale = 1 / (10 * (long double)(1ULL << 8));
                accelScale = 1 / (10 * (long double)(1ULL << 16));
                break;
            case SPAN::IMUType::IMU_LITEF_LCI1:
                gyroScale = 1 / ((long double)(1ULL << 29));
                accelScale = 1 / ((long double)(1ULL << 30));
                break;
            case SPAN::IMUType::IMU_LN200:
                gyroScale = 1 / ((long double)(1ULL << 19));
                accelScale = 1 / ((long double)(1ULL << 14));
                break;
            case SPAN::IMUType::IMU_ISA100C:
            case SPAN::IMUType::IMU_ISA100:
            case SPAN::IMUType::IMU_ISA100_400HZ:
            case SPAN::IMUType::IMU_ISA100C_400HZ:
            case SPAN::IMUType::IMU_LITEF_MICROIMU:
                gyroScale = 1e-9;
                accelScale = 2e-8;
                break;
            case SPAN::IMUType::IMU_ADIS16488:
                gyroScale = 45 / ((long double)(1ULL << 27));
                accelScale = 25 / ((long double)(1ULL << 28));
                break;
            case SPAN::IMUType::IMU_STIM300:
                gyroScale = 1 / ((long double)(1ULL << 21));
                accelScale = 1 / ((long double)(1ULL << 22));
                break;
            case SPAN::IMUType::IMU_UNKNOWN:
            default:
                break;
        }
    })

DEFINE_SPAN_MESSAGE_WITH_SHORT_ALIAS(
    40, RAWIMUX, RAWIMUSX, IMUError IMU_error; IMUType IMU_type;
    UShort GNSS_week; Double GNSS_week_seconds; IMUStatus IMU_status;
    Long Z_accel; Long _Y_accel; Long X_accel; Long Z_gyro; Long _Y_gyro;
    Long X_gyro;
    ,
    {
        if (str.size() < sizeof(__t) - sizeof(__t.header)) return false;
        memcpy(&__t.IMU_error DEFINE_COMMA str.data() DEFINE_COMMA sizeof(__t) -
               sizeof(__t.header));
        DEFINE_MARCO_SPAN_MESSAGE_TOGGLE(__t)
        return true;
    },
    {
        if (str.size() < 11) {
            return false;
        }
        __t.IMU_error = (IMUError)stoUC(str[0], 0, 16);
        __t.IMU_type = (IMUType)stoUC(str[1]);
        __t.GNSS_week = stoUS(str[2]);
        __t.GNSS_week_seconds = stoD(str[3]);
        __t.IMU_status = stoUL(str[4], 0, 16);
        __t.Z_accel = stoL(str[5]);
        __t._Y_accel = stoL(str[6]);
        __t.X_accel = stoL(str[7]);
        __t.Z_gyro = stoL(str[8]);
        __t._Y_gyro = stoL(str[9]);
        __t.X_gyro = stoL(str[10]);

        return true;
    },
    {
        TOGGLE_SPAN_ENDIAN(IMU_type);
        TOGGLE_SPAN_ENDIAN(GNSS_week);
        TOGGLE_SPAN_ENDIAN(GNSS_week_seconds);
        TOGGLE_SPAN_ENDIAN(IMU_status);
        TOGGLE_SPAN_ENDIAN(Z_accel);
        TOGGLE_SPAN_ENDIAN(_Y_accel);
        TOGGLE_SPAN_ENDIAN(X_accel);
        TOGGLE_SPAN_ENDIAN(Z_gyro);
        TOGGLE_SPAN_ENDIAN(_Y_gyro);
        TOGGLE_SPAN_ENDIAN(X_gyro);
    },

    static void GetScaleFactors(SPAN::IMUType imu_type, long double &gyroScale,
                                long double &accelScale) {
        RAWIMU::GetScaleFactors(imu_type, gyroScale, accelScale);
    })

DEFINE_SPAN_MESSAGE_WITH_SHORT_ALIAS(
    20, TIMEDWHEELDATA__, TIMEDWHEELDATA, UShort ticks_per_rev;
    UShort wheel_vel; Float f_wheel_vel; ULong reserved[2];
    Long cumulative_ticks;,
                          {
                              if (str.size() < sizeof(__t) - sizeof(__t.header))
                                  return false;
                              memcpy(&__t.ticks_per_rev DEFINE_COMMA str.data()
                                          DEFINE_COMMA sizeof(__t) -
                                     sizeof(__t.header));
                              DEFINE_MARCO_SPAN_MESSAGE_TOGGLE(__t)
                              return true;
                          },
                          {
                              if (str.size() < 6) {
                                  return false;
                              }
                              __t.ticks_per_rev = stoUS(str[0]);
                              __t.wheel_vel = stoUS(str[1]);
                              __t.f_wheel_vel = stoF(str[2]);
                              __t.reserved[0] = stoUL(str[3]);
                              __t.reserved[1] = stoUL(str[4]);
                              __t.cumulative_ticks = stoL(str[5]);
                              return true;
                          },
                          {
                              TOGGLE_SPAN_ENDIAN(ticks_per_rev);
                              TOGGLE_SPAN_ENDIAN(wheel_vel);
                              TOGGLE_SPAN_ENDIAN(f_wheel_vel);
                              TOGGLE_SPAN_ENDIAN(reserved[0]);
                              TOGGLE_SPAN_ENDIAN(reserved[1]);
                              TOGGLE_SPAN_ENDIAN(cumulative_ticks);
                          })

DEFINE_SPAN_MESSAGE(28, INSUPDATE, PositionOrVelocityType solution_type;
                    Long reserved0; Long phase; Long reserved1;
                    Boolean zupt_flag; WheelStatus wheel_status;
                    HeadingUpdateValues heading_update;
                    ,
                    {
                        if (str.size() < sizeof(__t) - sizeof(__t.header))
                            return false;
                        memcpy(&__t.solution_type DEFINE_COMMA str.data()
                                    DEFINE_COMMA sizeof(__t) -
                               sizeof(__t.header));
                        DEFINE_MARCO_SPAN_MESSAGE_TOGGLE(__t)
                        return true;
                    },
                    {
                        if (str.size() < 7) {
                            return false;
                        }
                        __t.solution_type =
                            PositionOrVelocityTypeFromName(str[0]);
                        __t.reserved0 = stoL(str[1]);
                        __t.phase = stoL(str[2]);
                        __t.reserved1 = stoL(str[3]);
                        __t.zupt_flag = stoL(str[4]);
                        __t.wheel_status = WheelStatusFromName(str[5]);
                        __t.heading_update =
                            HeadingUpdateValuesFromName(str[6]);
                        return true;
                    },
                    {
                        TOGGLE_SPAN_ENDIAN(solution_type);
                        TOGGLE_SPAN_ENDIAN(reserved0);
                        TOGGLE_SPAN_ENDIAN(phase);
                        TOGGLE_SPAN_ENDIAN(reserved1);
                        TOGGLE_SPAN_ENDIAN(zupt_flag);
                        TOGGLE_SPAN_ENDIAN(wheel_status);
                        TOGGLE_SPAN_ENDIAN(heading_update);
                    })

// TODO: Add new message here
// DEFINE_SPAN_MESSAGE_WITH_SHORT_ALIAS
// DEFINE_SPAN_MESSAGE_WITH_SHORT
// DEFINE_SPAN_MESSAGE_WITH_ALIAS
// DEFINE_SPAN_MESSAGE

inline bool ConstructASCIIWithoutHeader(MessageID id,
                                        std::vector<std::string> data,
                                        void *var) {
#define ASCII_CASE(ID)                                                    \
    case MessageID::ID: {                                                 \
        ID::fromAsciiWithoutHeader(data, *(reinterpret_cast<ID *>(var))); \
        break;                                                            \
    }
    switch (id) {
        ASCII_CASE(BESTPOS)
        ASCII_CASE(INSATT)
        ASCII_CASE(INSATTS)
        ASCII_CASE(INSCOV)
        ASCII_CASE(INSCOVS)
        ASCII_CASE(INSPOS)
        ASCII_CASE(INSPOSS)
        ASCII_CASE(INSPVA)
        ASCII_CASE(INSPVAS)
        ASCII_CASE(INSSPD)
        ASCII_CASE(INSSPDS)
        ASCII_CASE(INSVEL)
        ASCII_CASE(INSVELS)
        ASCII_CASE(TIME)
        ASCII_CASE(INSPVAX)
        ASCII_CASE(RAWIMU)
        ASCII_CASE(RAWIMUS)
        ASCII_CASE(RAWIMUX)
        ASCII_CASE(RAWIMUSX)
        ASCII_CASE(BESTGNSSPOS)
        ASCII_CASE(TIMEDWHEELDATA)
        ASCII_CASE(INSUPDATE)
        ASCII_CASE(BESTSATS)
        ASCII_CASE(BESTVEL)
        // TODO: add message construct from string array
        // ASCII_CASE(messagetype)
        default: { return false; }
    }
    return true;
}

inline bool ConstructBINWithoutHeader(MessageID id, std::string data,
                                      void *var) {
#define BIN_CASE(ID)                                                    \
    case MessageID::ID: {                                               \
        ID::fromBinWithoutHeader(data, *(reinterpret_cast<ID *>(var))); \
    } break;
    switch (id) {
        BIN_CASE(BESTPOS)
        BIN_CASE(INSATT)
        BIN_CASE(INSATTS)
        BIN_CASE(INSCOV)
        BIN_CASE(INSCOVS)
        BIN_CASE(INSPOS)
        BIN_CASE(INSPOSS)
        BIN_CASE(INSPVA)
        BIN_CASE(INSPVAS)
        BIN_CASE(INSSPD)
        BIN_CASE(INSSPDS)
        BIN_CASE(INSVEL)
        BIN_CASE(INSVELS)
        BIN_CASE(TIME)
        BIN_CASE(INSPVAX)
        BIN_CASE(RAWIMU)
        BIN_CASE(RAWIMUS)
        BIN_CASE(RAWIMUX)
        BIN_CASE(RAWIMUSX)
        BIN_CASE(BESTGNSSPOS)
        BIN_CASE(TIMEDWHEELDATA)
        BIN_CASE(INSUPDATE)
        BIN_CASE(BESTSATS)
        BIN_CASE(BESTVEL)
        // TODO: add message construct from string
        // BIN_CASE(messagetype)
        default: { return false; }
    }
    return true;
}
}  // namespace SPAN
#endif
