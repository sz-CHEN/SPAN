#include "SPANType.h"
namespace SPAN {
const double IMUStatus::ISA100_100CTemperatureScaleRatio = 3.90625e-3;
const double IMUStatus::ADIS16488_IGMA1TemperatureScaleRatio = 0.00565;
const double IMUStatus::ADIS16488_IGMA1TemperatureOffset = 25;
const double IMUStatus::STIM300_IGMS1TemperatureScaleRatio =
    1 / (double)(2UL << 8);
const double IMUStatus::uIMUTemperatureScaleRatio = 3.90625e-3;
}