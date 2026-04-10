#include "vex.h"

using namespace vex;
using namespace mik;

// adjust throttle sensitivity/deadzone
void default_constants(void) {
	chassis.set_control_constants(3, 8, 1.019, 3, 2, 1.045);

	// Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
    chassis.set_turn_constants(12, .257, .011, 2.0, 15);
    chassis.set_drive_constants(12, 1.38, 0, 8.5, 0);
    chassis.set_heading_constants(6, .4, 0, 1, 0);
    chassis.set_swing_constants(12, .487, .0063, 5.256, 15);


	// Each exit condition set is in the form of (settle_error, settle_time, timeout).
    chassis.set_turn_exit_conditions(1.5, 75, 2000);
    chassis.set_drive_exit_conditions(1, 75, 3000);
    chassis.set_swing_exit_conditions(1.25, 75, 3000);
}

void odom_constants(void) {
	default_constants();
	//was 0, .3
	chassis.set_tracking_offsets(0, -0.984375);

	chassis.heading_max_voltage = 10;
	chassis.drive_max_voltage = 8;
	chassis.drive_settle_error = 3;
	chassis.boomerang_lead = .5;
	chassis.boomerang_setback = 2;
	chassis.drive_min_voltage = 0;
}

void mogo_constants() {
	odom_constants();
	mogo_offsets();

	chassis.set_turn_constants(12, .437, 0.02, 3.7, 15);
	chassis.set_turn_exit_conditions(.1, 300, 3000);
	}

void mogo_offsets() {
  	chassis.set_tracking_offsets(0, 1);
}