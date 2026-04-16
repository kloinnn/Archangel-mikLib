#include "vex.h"

using namespace vex;
using namespace mik;

task UI;

static int run_UI() {
    UI_init();
    UI_controller_auton_selector();
    UI_render();
    return 0;
}

void pre_auton() {
    init();
    default_constants();

    UI = task(run_UI);
}

void auton(void) {
    UI.stop();
    //wtf am i even doing
    //assembly.wing_piston.close();
    auton_scr->start_auton();
}

void user_control(void) {
    while (calibrating) { task::sleep(50); }

    // toggle the odom lift as soon as driver control begins
    //assembly.odom_lift.toggle();
    
    // close the wing as soon as driver control begins
    //assembly.wing_piston.open();

    // How you want your drivetrain to stop during driver
    chassis.set_brake_type(brakeType::coast);
    
    assembly.init();

    while (true) {
        if (!control_disabled()) {
            // Add your user control code here
            chassis.control(drive_mode::SPLIT_ARCADE);
            assembly.control();
        }
        task::sleep(5);
    }
}

int main() {
    Competition.autonomous(auton);
    Competition.drivercontrol(user_control);

    pre_auton();

    while (true) {
        task::sleep(100);
    }
}
