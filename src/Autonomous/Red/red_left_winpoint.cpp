#include "vex.h"

using namespace vex;
using namespace mik;

std::string red_left_winpoint(bool calibrate, mik::auto_variation var, bool get_name) { 
    if (get_name) { return "red left winpoint"; }
    if (calibrate) {
        chassis.set_coordinates(-40.5, 0, 90);

        return "";
    }
    
    //dimensions of robot: 14 in wide, 12.75 behind, 15.25 back aligner, 
    // 17.25 intqke, matchloader 26
  odom_constants();
    keepColor = BLUE;
    scoringTime = 1.5; //score in long goal for 2s max
    //change exit conditions to ensure robot will be on pace
    chassis.set_turn_exit_conditions(1.5, 30, 2000);
    chassis.set_drive_exit_conditions(1, 50, 3000);
    chassis.set_swing_exit_conditions(1.25, 50, 3000);
    assembly.wing_piston.set(true);

    //drive towards 1st matchloader
    chassis.turn_to_point(-49.2, -47.0, {.timeout = 100});
    chassis.drive_to_point(-49.2, -47.0);
    matchloader_down();
    wait(0.2,sec);
    chassis.turn_to_angle(270, {.settle_time = 20});

    //reset x and y coordinates
    // chassis.reset_axis(front_sensor, left_wall, 5);
    // chassis.reset_axis(left_sensor, bottom_wall, 5);

    // 1st matchloader
    intake_in();
    chassis.drive_distance(2.5, {.max_voltage=6, .min_voltage=5});
    chassis.drive_distance(500, {.max_voltage=6, .min_voltage=5.5, .timeout = 650});

    //reset x and y coordinates
    // chassis.reset_axis(front_sensor, left_wall, 5);
    // chassis.reset_axis(left_sensor, bottom_wall, 5);

    // 1st long goal
    chassis.drive_to_pose(-26.8, -47.2, 270); //drive towards
    score_high(); //score long goal
    chassis.drive_distance(-500, {.heading=270, .max_voltage=4, .min_voltage = 3, .timeout=500});
    matchloader_up();
    chassis.turn_to_angle(0, {.settle_time = 15});

    // 1st 3-balls
    chassis.drive_distance(.5, {.max_voltage=6, .min_voltage=2});
    assembly.hood_piston.open();
    chassis.drive_to_pose(-23.4,-30.0, 10.0, {.min_voltage=6, .wait = false});
    wait(.45, sec);
        matchloader_down();
    chassis.wait();

    // 2nd 3-balls
    chassis.drive_to_pose(-23.25, 13.5, 355, {.max_voltage = 10, .wait=false});
    wait(.20,sec);
    matchloader_up();
    chassis.wait();
    matchloader_down();

    // towards 2nd long goal
    chassis.turn_to_point(-37.5, 44.6);
    chassis.drive_to_point(-37.5, 44.6);
    chassis.turn_to_angle(270);

    // 2nd long goal
    chassis.drive_to_pose(-32.6, 46.6, 270, {.min_voltage = 6});
    score_high();
    chassis.drive_distance(-500, {.heading=270, .min_voltage=6, .timeout=850});
    // reset in case of odom drift
    chassis.set_coordinates(-29.1, 47.2, chassis.get_absolute_heading());
    
    // ensure any unscored balls are kept
    assembly.hood_piston.open();
    assembly.middle_intake.spin(fwd, 12, volt);
    assembly.top_intake.spin(fwd, -12, volt);
    assembly.bottom_intake.spin(fwd, 12, volt);

    // 2nd matchloader
    chassis.drive_to_pose(-53, 46.8, 270, {.min_voltage = 8, .wait=false});
    wait(.1, sec);
    intake_in();
    chassis.wait();
    chassis.drive_distance(2.5, {.heading = 270, .max_voltage=8, .min_voltage=5.5});
    chassis.drive_distance(500, {.max_voltage=4.5, .timeout = 450});

    // mid goal
    chassis.set_drive_constants(12, 1.38, 0, 10, 0);
    chassis.drive_to_pose(-11.4, 14.4, 315, {.max_voltage =12, .wait=false, .settle_time=10, .settle_error = 2});
    wait(.45, sec);
    // index balls to score mid
    assembly.middle_intake.spin(fwd, 12, volt);
    assembly.top_intake.spin(fwd, -12, volt);
    assembly.bottom_intake.spin(fwd, 12, volt);
    wait(.1, sec);
    matchloader_up();
    assembly.bottom_intake.stop();
    assembly.middle_intake.stop();
    assembly.top_intake.stop();
    chassis.wait();
    // score mid
    assembly.middle_intake.spin(fwd, -12, volt);
    assembly.top_intake.spin(fwd, -3.5, volt);
    assembly.bottom_intake.spin(fwd, -12, volt);
    chassis.drive_distance(-500, {.heading=315, .max_voltage=7, .min_voltage=6});
    wait(.3,sec);
    assembly.top_intake.spin(fwd, -5.5, volt); //extra power in case of jams

    return "";
}