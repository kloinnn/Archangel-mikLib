#include "vex.h"

using namespace vex;
using namespace mik;

std::string blue_sawp(bool calibrate, mik::auto_variation var, bool get_name) { 
    if (get_name) { return "blue sawp"; }
    if (calibrate) {
        chassis.set_coordinates(-40.5, 0, 90); //change after measuring distance from tracking center

        return "";
    }

    //dimensions of robot: 14 in wide, 12.75 behind, 15.25 back aligner, 
    // 17.25 intqke, matchloader 26
    odom_constants();
    keepColor = BLUE;
    scoringTime = 2; //score in long goal for 2s max

    chassis.turn_to_point(-48.9, -47.0); //drive towards 1st matchloader
    chassis.drive_to_point(-48.9, -47.0);

    //reset x and y coordinates
    // chassis.reset_axis(front_sensor, left_wall, 5);
    // chassis.reset_axis(left_sensor, bottom_wall, 5);

    chassis.turn_to_point(-57.2, -47.0); //drive into 1st matchloader
    intake_in(); //start intaking
    matchloader_down();
    chassis.drive_distance(8.0, {.max_voltage=6, .timeout = 1000});
    wait(.5,sec);

    //reset x and y coordinates
    // chassis.reset_axis(front_sensor, left_wall, 5);
    // chassis.reset_axis(left_sensor, bottom_wall, 5);

    chassis.drive_to_pose(-30.0, -47.2, 270); //drive towards long goal
    long_goal_colorsort_auton(); //score long goal
    matchloader_up();
    chassis.turn_to_angle(0); //pivot on long goal
    chassis.drive_distance(8, {.min_voltage = 3, .wait=false}); //drive forward to clear long goal
    chassis.wait_until(5);
    chassis.cancel_motion();

    chassis.turn_to_point(-22.2, -26.5); //first set of 3-balls
    intake_in();
    chassis.drive_to_pose(-22.2, -26.5, 358.264); //keep driving without stopping

    // chassis.reset_axis(left_sensor, left_wall, 5);
    chassis.turn_to_point(-23.7, 23.0, {.wait = false}); // turns to second set of 3-balls without stopping
    chassis.drive_to_point(-23.7, 23.0);
    // chassis.reset_axis(front_sensor, top_wall, 3);
    matchloader_down();

    chassis.drive_to_pose(-11.6, 12.1, 315); //score mid
    assembly.left_intake_top.spin(fwd, -12, volt); //intake speeds are here so it can be adjusted
    assembly.right_intake_bottom.spin(fwd, -10, volt);
    assembly.left_intake_bottom.spin(fwd, 12, volt);
    wait(.8, sec);

    chassis.turn_to_point(-48.477, 46.6); //drive towards 2nd matchloader
    suck(); //suck balls back into intake
    chassis.drive_to_point(-48.477, 46.6);

    chassis.turn_to_point(59.9, 46.6); //drive into 2nd matchloader

    //reset x and y coordinates
    // chassis.reset_axis(front_sensor, left_wall, 5);
    // chassis.reset_axis(right_sensor, top_wall, 5);
    
    intake_in();
    chassis.drive_distance(8.0, {.max_voltage=6, .timeout = 1000});
    wait(.5,sec);

    //reset x and y coordinates
    // chassis.reset_axis(front_sensor, left_wall, 5);
    // chassis.reset_axis(right_sensor, top_wall, 5);

    // scoringTime = 5; //ensures that the robot will keep scoring until auton ends
    chassis.drive_to_pose(-31.274, 47.124, 270);
    matchloader_up();
    long_goal_colorsort_auton();

    return "";
}