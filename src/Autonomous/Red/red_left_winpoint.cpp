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
    //wing.piston.open(); //not sure if its open

   chassis.turn_to_point(-49.2, -47.0); //drive towards 1st matchloader
    chassis.drive_to_point(-49.2, -47.0);
    matchloader_down();
    wait(0.3,sec);
    chassis.turn_to_angle(270, {.settle_time = 15});

    //reset x and y coordinates
    // chassis.reset_axis(front_sensor, left_wall, 5);
    // chassis.reset_axis(left_sensor, bottom_wall, 5);

    // 1st matchloader
    intake_in();
    //8.25, 2.5
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
    // //chassis.left_swing_to_angle(0, {.timeout = 1000}); //pivot on long goal with only left wheels
    chassis.turn_to_angle(0);

    chassis.drive_distance(.5, {.max_voltage=6, .min_voltage=2});
    assembly.hood_piston.open();
    chassis.drive_to_pose(-23.4,-30.0, 10.0, {.min_voltage=6, .wait = false});
    wait(.45, sec);
        matchloader_down();
    chassis.wait();
    chassis.drive_to_pose(-23.5, 13.5, 355, {.max_voltage = 10, .wait=false});
    wait(.20,sec);
    matchloader_up();
    chassis.wait();
    matchloader_down();

    //chassis.drive_to_pose(-28, 28.311, 344, {.min_voltage = 6}); 
    // chassis.drive_to_pose(-37, 47.2, 332.8);
    chassis.turn_to_point(-37.5, 44.6);
    chassis.drive_to_point(-37.5, 44.6);
    chassis.turn_to_angle(270);
    chassis.drive_to_pose(-32.6, 46.6, 270, {.min_voltage = 4});
    score_high();
    chassis.drive_distance(-500, {.heading=270, .min_voltage=4, .timeout=850});

    chassis.set_coordinates(-29.1, 47.2, chassis.get_absolute_heading());
    assembly.hood_piston.open();

    assembly.left_intake_top.spin(fwd, 12, volt);
    assembly.right_intake_bottom.spin(fwd, -12, volt);
    assembly.left_intake_bottom.spin(fwd, 12, volt);


    chassis.drive_to_pose(-53, 46.8, 270, {.min_voltage = 8, .wait=false});
    wait(.1, sec);
    intake_in();
    chassis.wait();
    chassis.drive_distance(2.5, {.heading = 270, .max_voltage=8, .min_voltage=5.5});
    chassis.drive_distance(500, {.max_voltage=4.5, .timeout = 450});

    //chassis.drive_distance(-2.5, {.max_voltage=10, .min_voltage=9});
    chassis.set_drive_constants(12, 1.38, 0, 10, 0);
    chassis.drive_to_pose(-11.4, 14.4, 315, {.max_voltage =12, .wait=false, .settle_time=10, .settle_error = 2});
    wait(.45, sec);
    matchloader_up();
    assembly.left_intake_top.spin(fwd, 12, volt);
    assembly.right_intake_bottom.spin(fwd, -12, volt);
    assembly.left_intake_bottom.spin(fwd, 12, volt);
    wait(.1, sec);
    assembly.left_intake_bottom.stop();
    assembly.left_intake_top.stop();
    assembly.right_intake_bottom.stop();
    chassis.wait();
    assembly.left_intake_top.spin(fwd, -12, volt);
    assembly.right_intake_bottom.spin(fwd, -3.5, volt);
    assembly.left_intake_bottom.spin(fwd, -12, volt);
    chassis.drive_distance(-500, {.heading=315, .max_voltage=7, .min_voltage=6});
    wait(.3,sec);
    assembly.right_intake_bottom.spin(fwd, -5.5, volt);

    return "";
}