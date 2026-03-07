#include "vex.h"

using namespace vex;
using namespace mik;

std::string blue_right_winpoint(bool calibrate, mik::auto_variation var, bool get_name) {
    if (get_name) { return "blue right winpoint(4+3)"; }
    if (calibrate) {
     chassis.set_coordinates(-40.5, 0, 90); //change after measuring distance from tracking center

        return "";
    }

//     experimental auton using more drivetopose and pure pursuit (path following)


    odom_constants();
    keepColor = BLUE;
    scoringTime = 1.5; //score in long goal for 2s max

    chassis.drive_to_pose(-48.0, -47.0, 270, {.min_voltage=2}); //drive towards 1st matchloader

    //reset x and y coordinates
    // chassis.reset_axis(front_sensor, left_wall, 5);
    // chassis.reset_axis(left_sensor, bottom_wall, 5);

    // 1st matchloader
    intake_in();
    matchloader_down();
    chassis.drive_distance(6.0, {.max_voltage=6, .timeout = 2000});
    wait(.75,sec);

    //reset x and y coordinates
    // chassis.reset_axis(front_sensor, left_wall, 5);
    // chassis.reset_axis(left_sensor, bottom_wall, 5);

    // 1st long goal
    chassis.drive_to_pose(-30.0, -47.2, 270); //drive towards
    chassis.turn_to_angle(270, {.timeout = 1000, .settle_error=0.5, .wait=false});
    long_goal_colorsort_auton(); //score long goal
    matchloader_up();
    chassis.left_swing_to_angle(0, {.timeout = 1000}); //pivot on long goal with only left wheels

    // 3-balls
    intake_in(); //might conflict with suck task
    const std::vector<point> path = {{-24.316,-28.645}, {-21.996,-5.064}, {-19.29, 15.424}, {-34.173, 34.367}, {-36.686, 46.93}};
    chassis.follow_path(path, follow_path_params{.wait=false});
    chassis.wait_until(12); // get to first set of 3-balls then put matchloader down
    matchloader_down();
    chassis.wait_until(5);
    matchloader_up();
    chassis.wait_until(38.5);
    matchloader_down(); //catch 2nd set of 3-balls
    chassis.wait(); //wait until the end of the motion
    chassis.turn_to_angle(270); //line up with long goal

    // chassis.reset_axis(front_sensor, left_wall, 5);
    // chassis.reset_axis(right_sensor, top_wall, 5);

    //drive into 2nd long goal
    scoringTime = 2;
    chassis.drive_to_pose(-30.0, 47.2, 270);
    chassis.turn_to_angle(270, {.timeout = 1000, .settle_error=0.5, .wait=false});
    long_goal_colorsort_auton();

    chassis.drive_to_pose(-48.0, 47.0, 270, {.min_voltage=2}); //drive towards 2nd matchloader perpendicular to the wall

    // reset x and y coordinates
    // chassis.reset_axis(front_sensor, left_wall, 5);
    // chassis.reset_axis(right_sensor, top_wall, 5);
    
    // 2nd matchloader
    intake_in(); //start intaking
    chassis.drive_distance(6.0, {.max_voltage=6, .timeout = 2000}); //2nd matchload
    wait(.5,sec);

    // drive mid
    chassis.drive_distance(-6.0, {.min_voltage=3});
    matchloader_up();
    chassis.drive_to_pose(-10, 10, 315);
    assembly.left_intake_top.spin(fwd, -12, volt); //intake speeds are here so it can be adjusted
    assembly.right_intake_bottom.spin(fwd, -10, volt);
    assembly.left_intake_bottom.spin(fwd, 12, volt);

    return "";
}