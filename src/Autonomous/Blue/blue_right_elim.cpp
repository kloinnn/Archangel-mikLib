#include "vex.h"

using namespace vex;
using namespace mik;

std::string blue_right_elim(bool calibrate, mik::auto_variation var, bool get_name) {
    if (get_name) { return "blue right elim (7b push)"; }
    if (calibrate) {
        chassis.set_coordinates(-40.5, 0, 90);

        return "";
    }

    odom_constants();
    assembly.wing_piston.toggle();
    afterauton();

    //assembly.wing_piston.toggle();
    chassis.turn_to_point(-25, -20.5, {.timeout = 100});
    intake_in();
    chassis.drive_to_point(-25, -20.5, {.wait=false});
    wait(.7, sec);
    matchloader_down();
    chassis.wait();


    //drive towards 1st matchloader
    chassis.turn_to_point(-48.7, -47.4, {.settle_time=25});
    chassis.drive_to_point(-48.7, -47.4);
    wait(0.2,sec);
    chassis.turn_to_angle(270, {.settle_time = 20});

    // 1st matchloader
    chassis.drive_distance(2.5, {.max_voltage=6, .min_voltage=5});
    chassis.drive_distance(500, {.max_voltage=6, .min_voltage=5.5, .timeout = 850});

    // 1st long goal
    chassis.turn_to_point(-27.5, -47.2, {.angle_offset=180, .wait=false});
    chassis.drive_to_point(-27.5, -47.2, {.timeout = 1250});
    matchloader_up();
    score_high(); //score long goal
    chassis.drive_distance(-500, {.heading=270, .max_voltage=4, .min_voltage = 3, .timeout=1200});
    //bump
    chassis.drive_distance(6, {.heading = 270});
    assembly.hood_piston.open();
    stop_intake();
    chassis.drive_distance(-500, {.heading = 270, .max_voltage = 12, .timeout = 400});
    chassis.drive_distance(-500, {.heading = 270, .max_voltage = 4, .timeout = 700});
    chassis.stop_drive(hold);
    assembly.top_intake.spin(fwd, 12, volt);
    wait(10, sec);
    return "";

}
