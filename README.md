# NovAtel-SPAN

A NovAtel SPAN series parser developed with C++.

## SPAN

1. SPANType.h - Define the field types used in SPAN.  
2. SPANHeader.h - Define the message header used in SPAN.  
3. SPANMessage.h - Define some SPAN message structs and some convert.
4. SPANParser.h - The main class to parse message received.  

## References

[SPAN® on OEM6 Firmware Reference Manual(OM-20000144)](https://www.novatel.com/assets/Documents/Manuals/OM-20000144UM.pdf)  
[SPAN-CPT™ Quick Start Guide(GM-14915124)](https://www.novatel.com/assets/Documents/Manuals/SPAN-CPT-QSG-GM-14915124-Rev-1.pdf)  
[OEM6® Firmware Reference Guide(OM-20000129)](https://www.novatel.com/assets/Documents/Manuals/om-20000129.pdf)  

## Usage

```cpp
#include <iostream>
#include "SPANMessage.h"
#include "SPANParser.h"

int main(int argc, char* argv[]){
    SPAN::Parser parser;
    parser.RegisterCallback<SPAN::BESTPOS>(
        [&](const SPAN::BESTPOS *msg) -> void {
            std::cout << std::setprecision(std::numeric_limits<double>::digits10)
                     << msg->header.week << "\t" << msg->header.ms / 1000.0
                     << "\t" << SPAN::NameFromSolutionStatus(msg->sol_stat)
                     << "\t"
                     << SPAN::NameFromPositionOrVelocityType(msg->pos_type)
                     << "\t" << msg->lat << "\t" << msg->lon << "\t" << msg->hgt
                     << "\n";
        },
        SPAN::MessageID::BESTPOS);
    parser.push("#BESTPOSA,USB2_1,0,58.0,FINESTEERING,2001,552919.800,00000000,b1f6,14039;"
    "SOL_COMPUTED,NARROW_INT,30.53258681161,114.35918699405,33.3996,-14.4000,WGS84,0.0155,0.0109,0.0480,"
    "\"19\",0.800,0.000,13,9,9,9,00,01,00,33*77ae42d7");
    return 0;
}

```

## Extendable

***Add new messages***

### Example

***Find TODO***

1. INSVEL

| Field | Field Type        | Description                                                    | Format | Binary Bytes | Binary Offset |
|-------|-------------------|----------------------------------------------------------------|--------|--------------|---------------|
| 1     | Log Header        | Log header                                                     | -      | H            | 0             |
| 2     | Week              | GNSS Week                                                      | ULong  | 4            | H             |
| 3     | Seconds into Week | Seconds from week start                                        | Double | 8            | H+4           |
| 4     | North Velocity    | Velocity North in m/s                                          | Double | 8            | H+12          |
| 5     | East Velocity     | Velocity East in m/s                                           | Double | 8            | H+20          |
| 6     | Up Velocity       | Velocity Up in m/s                                             | Double | 8            | H+28          |
| 7     | Status            | INS status, see Table 32, Inertial Solution Status on page 136 | Enum   | 4            | H+36          |
| 8     | xxxx              | 32-bit CRC (ASCII, Binary and Short Binary only)               | Hex    | 4            | H+40          |
| 9     | [CR][LF]          | Sentence terminator (ASCII only)                               | -      | -            | -             |

```cpp
//SPANMessage.h

// Example for messages with general header.

////// TODO: Add here
DEFINE_SPAN_MESSAGE(
    INSVEL,
    //The data fields of INSVEL except Log Header, xxxx and [CR][LF]
    ULong week; Double seconds_into_week; Double north_velocity;
    Double east_velocity; Double up_velocity; InertialSolutionStatus status;
    ,
    // fill data fields with binary string
    // static bool fromBinWithoutHeader(const std::string& str, T& __t)
    {
        if (str.size() < sizeof(__t) - sizeof(__t.header)) return false;
        memcpy(&__t.week DEFINE_COMMA str.data() DEFINE_COMMA sizeof(__t) -
               sizeof(__t.header));
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
        __t.toggleEndian();
#endif
        return true;
    },
    // fill data fields with ascii strings
    // static bool fromAsciiWithoutHeader(const std::vector<std::string>& str, T& __t)
    {
        if (str.size() < 6) {
            return false;
        }
        __t.week = std::stoul(str[0]);
        __t.seconds_into_week = std::stod(str[1]);
        __t.north_velocity = std::stod(str[2]);
        __t.east_velocity = std::stod(str[3]);
        __t.up_velocity = std::stod(str[4]);
        __t.status = InertialSolutionStatusFromName(str[5]);
        return true;
    },
    // little endian <--> big endian
    // void toggleEndian()
    {
        TOGGLE_SPAN_ENDIAN(week);
        TOGGLE_SPAN_ENDIAN(seconds_into_week);
        TOGGLE_SPAN_ENDIAN(north_velocity);
        TOGGLE_SPAN_ENDIAN(east_velocity);
        TOGGLE_SPAN_ENDIAN(up_velocity);
        TOGGLE_SPAN_ENDIAN(status);
    })
//////

// ...
// ...

inline bool ConstructASCIIWithoutHeader(MessageID id,
                                        std::vector<std::string> data,
                                        void* var) {
#define ASCII_CASE(ID)                                                   \
    case MessageID::ID: {                                                \
        ID::fromAsciiWithoutHeader(data, *(reinterpret_cast<ID*>(var))); \
        break;                                                           \
    }
    switch (id) {
        ///// TODO: Add here
        ASCII_CASE(INSVEL)
        /////
        default: { return false; }
    }
    return true;
}

inline bool ConstructBINWithoutHeader(MessageID id, std::string data,
                                      void* var) {
#define BIN_CASE(ID)                                                   \
    case MessageID::ID: {                                              \
        ID::fromBinWithoutHeader(data, *(reinterpret_cast<ID*>(var))); \
    } break;
    switch (id) {
        ///// TODO: Add here
        BIN_CASE(INSVEL)
        /////
        default: { return false; }
    }
    return true;
}

```

2. INSVELS

This log is the short header version of the INSVEL log.  

```cpp
//SPANMessage.h

// Example for messages with general header and short header.
// If the message  has both general header and short header, do this part only.

////// TODO: Add here
// Replace last part DEFINE_SPAN_MESSAGE to DEFINE_SPAN_MESSAGE_WITH_SHORT
DEFINE_SPAN_MESSAGE_WITH_SHORT(
    INSVEL,
    //The data fields of INSVEL except Log Header, xxxx and [CR][LF]
    ULong week; Double seconds_into_week; Double north_velocity;
    Double east_velocity; Double up_velocity; InertialSolutionStatus status;
    ,
    // fill data fields with binary string
    // static bool fromBinWithoutHeader(const std::string& str, T& __t)
    {
        if (str.size() < sizeof(__t) - sizeof(__t.header)) return false;
        memcpy(&__t.week DEFINE_COMMA str.data() DEFINE_COMMA sizeof(__t) -
               sizeof(__t.header));
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
        __t.toggleEndian();
#endif
        return true;
    },
    // fill data fields with ascii strings
    // static bool fromAsciiWithoutHeader(const std::vector<std::string>& str, T& __t)
    {
        if (str.size() < 6) {
            return false;
        }
        __t.week = std::stoul(str[0]);
        __t.seconds_into_week = std::stod(str[1]);
        __t.north_velocity = std::stod(str[2]);
        __t.east_velocity = std::stod(str[3]);
        __t.up_velocity = std::stod(str[4]);
        __t.status = InertialSolutionStatusFromName(str[5]);
        return true;
    },
    // little endian <--> big endian
    // void toggleEndian()
    {
        TOGGLE_SPAN_ENDIAN(week);
        TOGGLE_SPAN_ENDIAN(seconds_into_week);
        TOGGLE_SPAN_ENDIAN(north_velocity);
        TOGGLE_SPAN_ENDIAN(east_velocity);
        TOGGLE_SPAN_ENDIAN(up_velocity);
        TOGGLE_SPAN_ENDIAN(status);
    })
//////

// ...
// ...

inline bool ConstructASCIIWithoutHeader(MessageID id,
                                        std::vector<std::string> data,
                                        void* var) {
#define ASCII_CASE(ID)                                                   \
    case MessageID::ID: {                                                \
        ID::fromAsciiWithoutHeader(data, *(reinterpret_cast<ID*>(var))); \
        break;                                                           \
    }
    switch (id) {
        ///// TODO: Add here
        ASCII_CASE(INSVELS)
        /////
        default: { return false; }
    }
    return true;
}

inline bool ConstructBINWithoutHeader(MessageID id, std::string data,
                                      void* var) {
#define BIN_CASE(ID)                                                   \
    case MessageID::ID: {                                              \
        ID::fromBinWithoutHeader(data, *(reinterpret_cast<ID*>(var))); \
    } break;
    switch (id) {
        ///// TODO: Add here
        BIN_CASE(INSVELS)
        /////
        default: { return false; }
    }
    return true;
}

```