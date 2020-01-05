#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include "SPANHeader.h"
#include "SPANMessage.h"
#include "SPANParser.h"

int main(int argc, char const *argv[]) {
    std::ifstream gpsFile("BFN16410081_09-06-2018_21-56-27.gps");
    if (!gpsFile.good()) {
        return -1;
    }
    std::ofstream fINSPVAS("INSPVAS.txt");
    fINSPVAS << "week\tseconds\tlatitude\tlongitude\theight\tnorth_"
                "velocity\teast_velocity\tup_"
                "velocity\troll\tpitch\tazimuth\tInertialSolutionStatus\n";
    std::ofstream fBESTPOS("BESTPOS.txt");
    fBESTPOS << "Week\tSeconds\tSolutionStatus\tPositionType\tLatitude\tLongitu"
                "de\tHeight\n";
    std::ofstream fBESTGNSSPOS("BESTGNSSPOS.txt");
    fBESTGNSSPOS
        << "Week\tSeconds\tSolutionStatus\tPositionType\tLatitude\tLongitu"
           "de\tHeight\n";
    std::ofstream fINSPVAX("INSPVAX.txt");
    fINSPVAX << "Week\tSeconds\tInertialSolutionStatus\tPositionType\tLatitude"
                "\tLongitude\tHeight\tNorth_Velocity\tEast_Velocity\tUp_"
                "Veloctiy\tRoll\tPitch\tAzimuth\n";
    std::ofstream fRAWIMUS("RAWIMUS.txt");
    fRAWIMUS << "Week\tSeconds\tGNSSWeek\tGNSSWeekSeconds\tZAccel\t-"
                "YAccel\tXAccel\tZGyro\t-YGyro\tXGyro\tZAccelScaled\t-"
                "YAccelScaled\tXAccelScaled\tZGyroScaled\t-"
                "YGyroScaled\tXGyroScaled\n";
    std::ofstream fRAWIMUSX("RAWIMUSX.txt");
    fRAWIMUSX << "Week\tSeconds\tIMUType\tGNSSWeek\tGNSSWeekSeconds\tZAccel\t-"
                 "YAccel\tXAccel\tZGyro\t-YGyro\tXGyro\tZAccelScaled\t-"
                 "YAccelScaled\tXAccelScaled\tZGyroScaled\t-"
                 "YGyroScaled\tXGyroScaled\n";
    std::ofstream fRAWIMUX("RAWIMUX.txt");
    fRAWIMUX << "Week\tSeconds\tIMUType\tGNSSWeek\tGNSSWeekSeconds\tZAccel\t-"
                "YAccel\tXAccel\tZGyro\t-YGyro\tXGyro\tZAccelScaled\t-"
                "YAccelScaled\tXAccelScaled\tZGyroScaled\t-"
                "YGyroScaled\tXGyroScaled\n";
    std::ofstream fTIMEDWHEELDATA("TIMEDWHEELDATA.txt");
    fTIMEDWHEELDATA
        << "Week\tSeconds\tTicksPerRev\tWheelVel\tfWheelVel\tCumulativeTicks\n";

    SPAN::Parser parser;

    parser.RegisterCallback<SPAN::BESTPOS>(
        [&](const SPAN::BESTPOS *msg) -> void {
            fBESTPOS << std::setprecision(std::numeric_limits<double>::digits10)
                     << msg->header.week << "\t" << msg->header.ms / 1000.0
                     << "\t" << SPAN::NameFromSolutionStatus(msg->sol_stat)
                     << "\t"
                     << SPAN::NameFromPositionOrVelocityType(msg->pos_type)
                     << "\t" << msg->lat << "\t" << msg->lon << "\t" << msg->hgt
                     << "\n";
        },
        SPAN::MessageID::BESTPOS);

    parser.RegisterCallback<SPAN::BESTGNSSPOS>(
        [&](const SPAN::BESTGNSSPOS *msg) -> void {
            fBESTGNSSPOS << std::setprecision(
                                std::numeric_limits<double>::digits10)
                         << msg->header.week << "\t" << msg->header.ms / 1000.0
                         << "\t" << SPAN::NameFromSolutionStatus(msg->sol_stat)
                         << "\t"
                         << SPAN::NameFromPositionOrVelocityType(msg->pos_type)
                         << "\t" << msg->lat << "\t" << msg->lon << "\t"
                         << msg->hgt << "\n";
        },
        SPAN::MessageID::BESTGNSSPOS);

    parser.RegisterCallback<SPAN::INSPVAX>(
        [&](const SPAN::INSPVAX *msg) -> void {
            fINSPVAX << std::setprecision(std::numeric_limits<double>::digits10)
                     << msg->header.week << "\t" << msg->header.ms / 1000.0
                     << "\t"
                     << SPAN::NameFromInertialSolutionStatus(msg->INS_status)
                     << "\t"
                     << SPAN::NameFromPositionOrVelocityType(msg->pos_type)
                     << "\t" << msg->lat << "\t" << msg->lon << "\t"
                     << msg->height << "\t" << msg->north_vel << "\t"
                     << msg->east_vel << "\t" << msg->up_vel << "\t"
                     << msg->roll << "\t" << msg->pitch << "\t" << msg->azimuth
                     << "\n";
        },
        SPAN::MessageID::INSPVAX);

    parser.RegisterCallback<SPAN::RAWIMUS>(
        [&](const SPAN::RAWIMUS *msg) -> void {
            long double scale_accel = 1;
            long double scale_gyro = 1;
            SPAN::RAWIMUSX::GetScaleFactors(SPAN::IMUType::IMU_KVH_COTS,
                                            scale_gyro, scale_accel);

            fRAWIMUS << std::setprecision(std::numeric_limits<double>::digits10)
                     << msg->header.week_number << "\t"
                     << msg->header.milliseconds / 1000.0 << "\t" << msg->week
                     << "\t" << msg->seconds_into_week << "\t" << msg->Z_accel
                     << "\t" << msg->_Y_accel << "\t" << msg->X_accel << "\t"
                     << msg->Z_gyro << "\t" << msg->_Y_gyro << "\t"
                     << msg->X_gyro << "\t" << msg->Z_accel * scale_accel
                     << "\t" << msg->_Y_accel * scale_accel << "\t"
                     << msg->X_accel * scale_accel << "\t"
                     << msg->Z_gyro * scale_gyro << "\t"
                     << msg->_Y_gyro * scale_gyro << "\t"
                     << msg->X_gyro * scale_gyro << "\n";
        },
        SPAN::MessageID::RAWIMUS);

    parser.RegisterCallback<SPAN::RAWIMUSX>(
        [&](const SPAN::RAWIMUSX *msg) -> void {
            long double scale_accel = 1;
            long double scale_gyro = 1;
            SPAN::RAWIMUSX::GetScaleFactors(msg->IMU_type, scale_gyro,
                                            scale_accel);

            fRAWIMUSX << std::setprecision(
                             std::numeric_limits<double>::digits10)
                      << msg->header.week_number << "\t"
                      << msg->header.milliseconds / 1000.0 << "\t"
                      << SPAN::NameFromIMUType(msg->IMU_type) << "\t"
                      << msg->GNSS_week << "\t" << msg->GNSS_week_seconds
                      << "\t" << msg->Z_accel << "\t" << msg->_Y_accel << "\t"
                      << msg->X_accel << "\t" << msg->Z_gyro << "\t"
                      << msg->_Y_gyro << "\t" << msg->X_gyro << "\t"
                      << msg->Z_accel * scale_accel << "\t"
                      << msg->_Y_accel * scale_accel << "\t"
                      << msg->X_accel * scale_accel << "\t"
                      << msg->Z_gyro * scale_gyro << "\t"
                      << msg->_Y_gyro * scale_gyro << "\t"
                      << msg->X_gyro * scale_gyro << "\n";
        },
        SPAN::MessageID::RAWIMUSX);

    parser.RegisterCallback<SPAN::RAWIMUX>(
        [&](const SPAN::RAWIMUX *msg) -> void {
            long double scale_accel = 1;
            long double scale_gyro = 1;
            SPAN::RAWIMUX::GetScaleFactors(msg->IMU_type, scale_gyro,
                                           scale_accel);

            fRAWIMUX << std::setprecision(std::numeric_limits<double>::digits10)
                     << msg->header.week << "\t" << msg->header.ms / 1000.0
                     << "\t" << SPAN::NameFromIMUType(msg->IMU_type) << "\t"
                     << msg->GNSS_week << "\t" << msg->GNSS_week_seconds << "\t"
                     << msg->Z_accel << "\t" << msg->_Y_accel << "\t"
                     << msg->X_accel << "\t" << msg->Z_gyro << "\t"
                     << msg->_Y_gyro << "\t" << msg->X_gyro << "\t"
                     << msg->Z_accel * scale_accel << "\t"
                     << msg->_Y_accel * scale_accel << "\t"
                     << msg->X_accel * scale_accel << "\t"
                     << msg->Z_gyro * scale_gyro << "\t"
                     << msg->_Y_gyro * scale_gyro << "\t"
                     << msg->X_gyro * scale_gyro << "\n";
        },
        SPAN::MessageID::RAWIMUX);

    parser.RegisterCallback<SPAN::TIMEDWHEELDATA>(

        [&](const SPAN::TIMEDWHEELDATA *msg) -> void {
            fTIMEDWHEELDATA
                << std::setprecision(std::numeric_limits<double>::digits10)
                << msg->header.week_number << "\t"
                << msg->header.milliseconds / 1000.0 << "\t"
                << msg->ticks_per_rev << "\t" << msg->wheel_vel << "\t"
                << msg->f_wheel_vel << "\t" << msg->cumulative_ticks << "\n";
        },
        SPAN::MessageID::TIMEDWHEELDATA);

    parser.RegisterCallback<SPAN::INSPVAS>(
        [&](const SPAN::INSPVAS *msg) -> void {
            fINSPVAS << std::setprecision(std::numeric_limits<double>::digits10)
                     << msg->week << "\t" << msg->seconds << "\t"
                     << msg->latitude << "\t" << msg->longitude << "\t"
                     << msg->height << "\t" << msg->north_velocity << "\t"
                     << msg->east_velocity << "\t" << msg->up_velocity << "\t"
                     << msg->roll << "\t" << msg->pitch << "\t" << msg->azimuth
                     << "\t"
                     << SPAN::NameFromInertialSolutionStatus(msg->status)
                     << "\n";
        },
        SPAN::MessageID::INSPVAS);

    while (!gpsFile.eof()) {
        std::string s;
        std::getline(gpsFile, s);
        // std::cout<<s<<std::endl;
        parser.push(s);
    }
    fINSPVAS.close();
    fBESTPOS.close();
    fBESTGNSSPOS.close();
    fINSPVAS.close();
    fINSPVAX.close();
    fRAWIMUS.close();
    fRAWIMUSX.close();
    fRAWIMUX.close();
    fTIMEDWHEELDATA.close();
    std::cout << "end" << std::endl;
    return 0;
}
