#include "vex.h"

using namespace vex;
using namespace mik;

std::string red_right_elim(bool calibrate, mik::auto_variation var, bool get_name) {   
    if (get_name) { return "red right elim"; }
    if (calibrate) {
        chassis.set_coordinates(0, 0, 0);
        assembly.odom_lift.close();
        return "";
    }
    
    //go forward something
    intake_in();
    chassis.drive_with_voltage(6, 6);
    wait(.5, sec);
    chassis.stop_drive(coast);
    wait(1, sec);
    //go forward more something
    chassis.drive_with_voltage(12, 12);
    wait(.5, sec);
    //add a wiggle wiggle macro
    chassis.drive_distance(50, {.heading = 260, .timeout = 100});
    chassis.drive_distance(50, {.heading = 280, .timeout = 200});
    chassis.drive_distance(50, {.heading = 260, .timeout = 200});
    chassis.drive_distance(50, {.heading = 280, .timeout = 200});
    chassis.turn_to_angle(270, {.settle_time = 10, .timeout = 150});
    //go backward something
    chassis.drive_distance(-43.5, {.heading = 270, .wait=false});
    wait(1, sec);
    assembly.odom_lift.close();
    chassis.wait();
    // chassis.set_coordinates(-42, 0, chassis.get_absolute_heading());
    // //chassis.reset_axis(front_sensor, left_wall, 10);
    return "";
}