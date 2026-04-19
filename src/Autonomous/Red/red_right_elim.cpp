#include "vex.h"

using namespace vex;
using namespace mik;

std::string red_right_elim(bool calibrate, mik::auto_variation var, bool get_name) {   
    if (get_name) { return "red right elim(4b wing)"; }
    if (calibrate) {
        chassis.set_coordinates(-40.5, 0, 90);
        return "";
    }
    
    //dimensions of robot: 14 in wide, 12.75 behind, 15.25 back aligner, 
    // 17.25 intqke, matchloader 26
    odom_constants();
    assembly.wing_piston.toggle();
    afterauton();

    //change exit conditions to ensure robot will be on pace
    // chassis.set_turn_exit_conditions(1.5, 30, 2000);
    // chassis.set_drive_exit_conditions(1, 50, 3000);
    // chassis.set_swing_exit_conditions(1.25, 50, 3000);

    //drive towards 1st matchloader
    chassis.turn_to_point(-49.2, -47.7, {.timeout = 100});
    chassis.drive_to_point(-49.2, -47.7);
    matchloader_down();
    wait(0.2,sec);
    chassis.turn_to_angle(270, {.settle_time = 20});

    // matchloader
    intake_in();
    chassis.drive_distance(2.5, {.max_voltage=6, .min_voltage=5});
    chassis.drive_distance(500, {.max_voltage=6, .min_voltage=5.5, .timeout = 750});

    // long goal
    chassis.cancel_motion();
    chassis.drive_to_pose(-27.5, -47.2, 270, {.timeout = 1250}); //drive towards
//    chassis.turn_to_point(-27.5, -47.2, {.angle_offset=180, .wait=false, .timeout = 1250});
//     chassis.drive_to_point(-27.5, -47.2);
    score_high(); //score long goal
    chassis.drive_distance(-500, {.heading=270, .max_voltage=4, .min_voltage = 3, .timeout=500});
    matchloader_up();
    //chassis.turn_to_angle(0, {.settle_time = 15});
    
    // wing
    // chassis.drive_distance(0.5);
    //chassis.left_swing_to_angle(90);
    chassis.drive_to_pose(-32,-39, 5, {.lead = 0.1});
    stop_intake();
    chassis.turn_to_point(-8.5, -39.2);
    assembly.wing_piston.toggle();
    chassis.drive_to_point(-8.5, -39.2, {.timeout = 10000});
    chassis.turn_to_angle(55, {.timeout = 10000});
    chassis.stop_drive(hold);
    wait(10, sec);

    return "";
}