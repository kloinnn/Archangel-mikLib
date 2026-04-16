#include "vex.h"

using namespace vex;
using namespace mik;

enum LB_state : int { active = 206, inactive = 229, holding = 170, scoring = 43, hang = 345 };

std::string skills(bool calibrate, mik::auto_variation var, bool get_name) {
    if (get_name) { return "skills"; }
    if (calibrate) {
        chassis.set_coordinates(-40.5, 0, 90);

        return "";
    }
    
     //dimensions of robot: 14 in wide, 12.75 behind, 15.25 back aligner, 
    // 17.25 intqke, matchloader 26
    odom_constants();
    assembly.color_encoder.setLight(vex::ledState::on);

    //go forward something
    intake_in();

    // //go forward something
    // intake_in();
    // chassis.drive_with_voltage(6, 6);
    // wait(.5, sec);
    // chassis.stop_drive(coast);
    // wait(1, sec);
    // //go forward more something
    // chassis.drive_with_voltage(12, 12);
    // wait(.5, sec);
    // //add a wiggle wiggle macro
    // chassis.drive_distance(50, {.heading = 260, .timeout = 100});
    // chassis.drive_distance(50, {.heading = 280, .timeout = 200});
    // chassis.drive_distance(50, {.heading = 260, .timeout = 200});
    // chassis.drive_distance(50, {.heading = 280, .timeout = 200});
    // chassis.turn_to_angle(270, {.settle_time = 10, .timeout = 150});
    // //go backward something
    // chassis.drive_distance(-43.5, {.heading = 270, .wait=false});
    // wait(1, sec);
    // assembly.odom_lift.close();
    // chassis.wait();
    // // chassis.set_coordinates(-42, 0, chassis.get_absolute_heading());
    // // //chassis.reset_axis(front_sensor, left_wall, 10);

    // 4-balls
    chassis.turn_to_point(-24.2, -24.2);
    chassis.drive_to_point(-24.2, -24.2);

    //low goal
    chassis.turn_to_point(-12.2, -12.2);
    chassis.drive_to_point(-12.2, -12.2);
    outtake_skills();
    wait(1.5, sec);

    //back up from low goal
    chassis.drive_to_pose(-19, -21.5 , 345);

    //across to 1st matchloader
    {
        std::vector<point> path = {
            { -25.475, 1.70},
            { -25.8,   21.0 },
            { -31.274,  34.753 },
            { -43.779,  46.544 },
            { -53.015,  46.544 },
        };
        assembly.intake_lift.close();
        intake_in();
        chassis.follow_path(path, {.lookahead_distance = 3, .settle_error = 1, .wait = false});
    }
    wait(2.5, sec);
    matchloader_down();
    chassis.wait();


    //1st matchloader
    chassis.turn_to_angle(270, {.settle_time = 20, .timeout = 100});
    chassis.drive_distance(2.5, {.heading = 270, .max_voltage=8, .min_voltage=5.5});
    chassis.drive_distance(500, {.heading = 270, .max_voltage=6, .min_voltage=5.5, .timeout = 1000});

    //across field to 1st long goal
    {
        std::vector<point> path = {
            { -52.015,  46.544 },
            { -40.745,  51.376 },
            { -29.148,  58.528 },
            { -3.827,  60.5 },
            { 27.099,  60.5 },
            { 36.184,  55.049 },
            { 40.436,  47.2 },
        };
        chassis.follow_path(path, {.lookahead_distance = 3, .settle_error = 1, .wait = false});
    }
    wait(1, sec);
    stop_intake();
    matchloader_up();
    chassis.wait();

    //1st long goal
    chassis.turn_to_point(32.6, 47.2, {.angle_offset = 180});
    chassis.drive_to_point(32.6, 47.2);
    score_high();
    matchloader_down();
    chassis.drive_distance(-500, {.heading=90, .min_voltage = 6, .timeout=1500});
    // reset in case of odom drift
    chassis.set_coordinates(29.1, 47.2, chassis.get_absolute_heading());
    // ensure any unscored balls are kept
    assembly.hood_piston.open();
    outtake();

    // 2nd matchloader
    chassis.drive_to_pose(53, 46.6, 90, {.min_voltage = 8, .wait=false});
    wait(.1, sec);
    intake_in();
    chassis.wait();
    chassis.drive_distance(2.5, {.heading = 90, .max_voltage=8, .min_voltage=5.5});
    chassis.drive_distance(500, {.max_voltage=4.5, .timeout = 800});

    //score 1st long goal again
    chassis.drive_to_pose(32.6, 47.2, 90, {.min_voltage = 6});
    score_high();
    matchloader_up();
    chassis.drive_distance(-500, {.heading=90, .min_voltage=6, .timeout=1500});
    assembly.hood_piston.open();
    outtake();

    // line up for 2nd park zone
    {
        std::vector<point> path = {
            { 35,  47.2 },
            { 39,  33 },
            { 41.209,  19.097 },
            { 41.6,  0 },
        };
        chassis.follow_path(path, {.lookahead_distance = 3, .settle_error = 1, .wait=false});
    }
    wait(.1, sec);
    stop_intake();
    chassis.wait();
    chassis.turn_to_angle(90);
    intake_in();

    //go forward something
    //go forward more something
    //add a wiggle wiggle macro
    //go backward something
    chassis.drive_to_point(32.7, 0);

    // turn towards 4-balls
    chassis.turn_to_point(24.2, -24.2);
    chassis.drive_to_point(24.2, -24.2);
    matchloader_down();

    //mid goal
    chassis.turn_to_point(11.5, -11.5, {.angle_offset = 180});
    chassis.drive_to_point(11.5, -11.5, {.wait=false});
    // index balls to score mid
    outtake();
    wait(.1, sec);
    stop_intake();
    chassis.wait();
    // score mid
    assembly.middle_intake.spin(fwd, -12, volt);
    assembly.top_intake.spin(fwd, -3.5, volt);
    assembly.bottom_intake.spin(fwd, -12, volt);
    chassis.drive_distance(-500, {.heading=135, .max_voltage=7, .min_voltage=6});
    wait(2,sec);
    //colorsuck?
    
    // towards 3rd matchloader
    stop_intake();
    chassis.drive_to_pose(46.5, -46.5, 315);
    chassis.turn_to_point(62, -46.5);

    // 3rd matchloader
    intake_in();
    chassis.drive_distance(9, {.heading = 90, .max_voltage=8, .min_voltage=5.5});
    chassis.drive_distance(500, {.max_voltage=4.5, .timeout = 1000});

    //across field to 2nd long goal
    {
        std::vector<point> path = {
            { 52.015,  -46.544 },
            { 40.745,  -51.376 },
            { 29.148,  -58.528 },
            { 3.827,  -60.5 },
            { -27.099,  -60.5 },
            { -36.184,  -55.049 },
            { -40.436,  -47.2 },
        };
        chassis.follow_path(path, {.lookahead_distance = 3, .settle_error = 1, .wait = false});
    }
    wait(1, sec);
    stop_intake();
    matchloader_up();
    chassis.wait();

    //2nd long goal
    chassis.turn_to_point(-32.6, -47.2, {.angle_offset = 180});
    chassis.drive_to_point(-32.6, -47.2);
    score_high();
    matchloader_down();
    chassis.drive_distance(-500, {.heading=270, .min_voltage = 6, .timeout=1500});
    // reset in case of odom drift
    chassis.set_coordinates(-29.1, -47.2, chassis.get_absolute_heading());
    // ensure any unscored balls are kept
    assembly.hood_piston.open();
    outtake();

    // 4th matchloader
    chassis.drive_to_pose(-53, -46.6, 270, {.min_voltage = 8, .wait=false});
    wait(.1, sec);
    intake_in();
    chassis.wait();
    chassis.drive_distance(2.5, {.heading = 270, .max_voltage=8, .min_voltage=5.5});
    chassis.drive_distance(500, {.max_voltage=4.5, .timeout = 800});

    //score 2nd long goal again
    chassis.drive_to_pose(-32.6, -47.2, 270, {.min_voltage = 6});
    score_high();
    matchloader_up();
    chassis.drive_distance(-500, {.heading=270, .min_voltage=6, .timeout=1500});
    assembly.hood_piston.open();

    // park
    {
        std::vector<point> path = {
            { -44.224,  -47.2 },
            { -57.561,  -39.469 },
            { -60.654,  -30.578 },
            { -62.2,  -18.594 },
        };
        chassis.follow_path(path, {.lookahead_distance = 3, .settle_error = 1, .wait = false, .min_voltage = 6});
    }
    assembly.odom_lift.close();
    stop_intake();
    chassis.drive_distance(500, {.heading=0, .max_voltage=8, .timeout=1000});
    chassis.stop_drive(brake);





    // std::vector<point> path = {
    //     {  0.000,   0.000 },
    //     { -0.098,   1.997 },
    //     { -0.004,   3.993 },
    //     {  0.419,   5.944 },
    //     {  1.314,   7.722 },
    //     {  2.789,   9.053 },
    //     {  4.622,   9.831 },
    //     {  6.588,  10.189 },
    //     {  8.582,  10.324 },
    //     { 10.582,  10.364 },
    //     { 12.582,  10.406 },
    //     { 14.576,  10.542 },
    //     { 16.547,  10.871 },
    //     { 18.439,  11.506 },
    //     { 20.138,  12.549 },
    //     { 21.491,  14.014 },
    //     { 22.444,  15.768 },
    //     { 23.037,  17.676 },
    //     { 23.393,  19.643 },
    //     { 23.536,  21.637 },
    //     { 23.554,  23.664 },
    //     { 23.554,  23.664 },
    //     { 24.554,  24.664 },
    // };

    // chassis.follow_path(path, {.lookahead_distance = 3, .settle_error = 1});


    colorsuck();
    return 0;
}
    // // Score alliance ring
    // move_lift(hang);
    // wait(.4, sec);
    
    // // Drive into and clamp goal, idle lift
    // chassis.drive_distance(-13);
    // clamp_goal();
    // move_lift(inactive);

    // // Collect ring
    // chassis.turn_to_point(-24.5, -24); 
    // intake_forward();
    // chassis.drive_to_point(-24.5, -24); 
    
    // // Collect and stage ring into lift
    // chassis.turn_to_point(50.752, -61.884); 
    // chassis.drive_to_point(50.752, -61.884); 
    // move_lift(active);
    // chassis.drive_to_point(-0.284, -43); 
    
    // // Turn and move to wallstake, intake ring halfway
    // stop_intake();
    // move_lift(holding - 30);
    // chassis.turn_to_point(-0.284, -62.694); 
    // intake_ring_halfway();
    // chassis.drive_to_point(-0.284, -62.694); 
    // chassis.drive_distance(30, {.max_voltage = 8, .timeout = 1000}); 

    // // Score first ring
    // move_lift(scoring);
    // wait(.5, sec);

    // // Stage lift for next ring
    // move_lift(active);
    // wait(.4, sec);
    
    // // Move ring into lift
    // chassis.drive_with_voltage(4, 4);
    // intake_forward();
    // wait(.25, sec);

    // // Score next ring
    // move_lift(scoring);
    // wait(.5, sec);

    // // Reset odom X coordinate
    // chassis.reset_axis(front_sensor, right_wall, 5);

    // // Back up from wallstake, idle lift
    // chassis.drive_distance(-13); 
    // move_lift(inactive);
    
    // // Collect three rings
    // chassis.turn_to_point(-60.516, -46.973); 
    // intake_forward();
    // chassis.drive_to_point(-40.299, -46.973); 
    // chassis.drive_to_point(-60.516, -46.973, {.max_voltage = 6}); 

    // // Turn and collect one ring
    // chassis.turn_to_point(-47.818, -57.727); 
    // chassis.drive_to_point(-47.818, -57.727, {.max_voltage = 8}); 
    
    // // Drop mogo off
    // chassis.turn_to_point(-58, -61, {.angle_offset = 180}); 
    // chassis.drive_distance(-10, {.timeout = 400}); 
    // unclamp_goal();
    
    // // Leave corner
    // chassis.drive_distance(10); 
    // stop_intake();
    
    // return "";