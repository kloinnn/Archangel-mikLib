#include "vex.h"

using namespace vex;
using namespace mik;

std::string red_left_elim(bool calibrate, mik::auto_variation var, bool get_name) { 
    if (get_name) { return "red left elim(7b split+wing)"; }
    if (calibrate) {
        chassis.set_coordinates(-40.5, 0, 90);
        
        return "";
    }
        //dimensions of robot: 14 in wide, 12.75 behind, 15.25 back aligner, 
    // 17.25 intqke, matchloader 26
    odom_constants();
    assembly.wing_piston.toggle();

    //change exit conditions to ensure robot will be on pace
    // chassis.set_turn_exit_conditions(1.5, 30, 2000);
    // chassis.set_drive_exit_conditions(1, 50, 3000);
    // chassis.set_swing_exit_conditions(1.25, 50, 3000);

    //drive towards 1st matchloader
    chassis.turn_to_point(-49.2, 47.7, {.timeout = 100});
    chassis.drive_to_point(-49.2, 47.7);
    matchloader_down();
    wait(0.2,sec);
    chassis.turn_to_angle(270, {.settle_time = 20});

    // matchloader
    intake_in();
    chassis.drive_distance(2.5, {.max_voltage=6, .min_voltage=5});
    chassis.drive_distance(500, {.max_voltage=6, .min_voltage=5.5, .timeout = 750});

    // long goal
    chassis.stop_drive(brake);
    chassis.turn_to_point(-27.5, 47.2, {.angle_offset=180, .wait=false});
    chassis.drive_to_point(-27.5, 47.2, {.timeout = 1250});
    //chassis.drive_to_pose(-27.0, 47.2, 270); //drive towards
    score_high(); //score long goal
    chassis.drive_distance(-500, {.heading=270, .max_voltage=4, .min_voltage = 3, .timeout=500});
    matchloader_up();
   // chassis.turn_to_angle(180, {.settle_time = 15});
    
    // 3 ball
    // chassis.drive_distance(.5, {.max_voltage=6, .min_voltage=2});
    assembly.hood_piston.open();
    chassis.turn_to_point(-22.1, 23.4, {.settle_time = 20});
    chassis.drive_to_point(-22.1, 23.4, {.wait=false});    
    // chassis.drive_to_pose(-19.1,16.4, 170, {.wait = false});
    wait(.45, sec);
        matchloader_down();
    chassis.wait();
    chassis.turn_to_angle(315, {.settle_time = 20});
    chassis.drive_distance(-9.5, {.heading = 315, .min_voltage = 6, .wait = false});
    // index balls to score mid
    outtake();
    wait(.1, sec);
    matchloader_up();
    stop_intake();
    chassis.wait();

    // // score mid
    assembly.middle_intake.spin(fwd, -12, volt);
    assembly.top_intake.spin(fwd, -6, volt);
    assembly.bottom_intake.spin(fwd, -12, volt);
    chassis.drive_distance(-500, {.heading=315, .max_voltage=2, .min_voltage=1, .timeout = 700});

    chassis.turn_to_point(-29.6, 35.7, {.settle_time = 20});
    matchloader_up();
    chassis.drive_to_point(-29.6, 35.7, {.settle_time = 20});
    stop_intake();
    assembly.wing_piston.toggle();
    chassis.turn_to_angle(270);
    chassis.drive_distance(-18, {.heading=270, .max_voltage=12, .timeout = 15000});
    chassis.stop_drive(hold);
    wait(10, sec);



    // // wing
    // // chassis.drive_distance(0.5);
    // //chassis.left_swing_to_angle(90);
    // chassis.drive_to_pose(-32,-36,5, {.lead = 0.1});
    // stop_intake();
    // chassis.turn_to_point(-8.5, -36.2);
    // assembly.wing_piston.toggle();
    // chassis.drive_to_point(-8.5, -36.2, {.timeout = 15000});
    // chassis.turn_to_angle(55, {.timeout = 15000});
    // chassis.stop_drive(hold);
    // wait(10, sec);


    //{.lead = 0.3}
    return "";
}