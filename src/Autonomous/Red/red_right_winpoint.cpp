#include "vex.h"

using namespace vex;
using namespace mik;

std::string red_right_winpoint(bool calibrate, mik::auto_variation var, bool get_name) { 
    if (get_name) { return "red right winpoint"; }
    if (calibrate) {
        chassis.set_coordinates(-40.5, 0, 90);
        // assembly.odom_lift.close();
        return "";
    }
     //dimensions of robot: 14 in wide, 12.75 behind, 15.25 back aligner, 
    // 17.25 intqke, matchloader 26
    odom_constants();
    assembly.color_encoder.setLight(vex::ledState::on);

    //go forward something
    intake_in();

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
    return "";
}