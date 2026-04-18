#include "vex.h"

using namespace vex;

// Pass in the devices we want to use
Assembly::Assembly(
        mik::motor middle_intake,
        mik::motor top_intake,
        mik::motor bottom_intake, 
        vex::optical color_encoder,
        vex::inertial inertial_sensor,
        mik::piston mid_hood_piston,
        mik::piston odom_lift,
        mik::piston hood_piston,
        mik::piston matchloader_piston,
        mik::piston wing_piston,
        mik::piston intake_lift
) :
    // Assign the ports to the devices
    middle_intake(middle_intake),
    top_intake(top_intake),
    bottom_intake(bottom_intake),
    color_encoder(color_encoder),
    inertial_sensor(inertial_sensor),
    mid_hood_piston(mid_hood_piston),   // Make sure when using a 3 wire device that isnt mik::piston you convert the port. `to_triport(PORT_A)`.
    odom_lift(odom_lift),
    hood_piston(hood_piston),
    matchloader_piston(matchloader_piston),
    wing_piston(wing_piston),
    intake_lift(intake_lift)
{};

// You want to call this function once in the user control function in main.
void Assembly::init() {
    // Create the task to move the lift arm. We only want one task to be created
    //lift_task = vex::task([](){
    //    assembly.move_lift_arm();
     //   return 0;
    //});
    // To stop the task do `assembly.lift_task.stop();`
} 

// You want to put this function inside the user control loop in main.
void Assembly::control() {
    intake_control();
    mid_hood();
    odom_lift_control();
    matchloader();
    wing();
    //anti_tip();
}

// Spins intake forward if R1 is being held, reverse if R2 is being held; stops otherwise
void Assembly::intake_control() {
    if (Controller.ButtonR2.pressing()) {
        middle_intake.spin(fwd, -12, volt);
        top_intake.spin(fwd, 12, volt);
        bottom_intake.spin(fwd, -12, volt);
    } else if (Controller.ButtonR1.pressing()) { //score low
        middle_intake.spin(fwd, 12, volt);
        top_intake.spin(fwd, -12, volt);
        bottom_intake.spin(fwd, 6, volt);
        intake_lift.open();
    } else if (Controller.ButtonL2.pressing()) { //score mid
        middle_intake.spin(fwd, -12, volt);
        top_intake.spin(fwd, -10, volt);
        bottom_intake.spin(fwd, -12, volt);
     } else if (Controller.ButtonL1.pressing()) { //score high
     middle_intake.spin(fwd, -12, volt);
     top_intake.spin(fwd, 12, volt);
     bottom_intake.spin(fwd, -12, volt);
     hood_piston.close();
    } else {
        bottom_intake.stop();
        middle_intake.stop();
        top_intake.stop();
        hood_piston.open();
        intake_lift.close();
    }
}

// Extends or retracts wing when button A is pressed, can only extend or retract again until button A is released and pressed again
void Assembly::mid_hood() {
    if (btnLeft_new_press(Controller.ButtonLeft.pressing())) {
        mid_hood_piston.toggle();
    }
}

void Assembly::odom_lift_control() {
    if (odomafterauton == true) {
        odom_lift.toggle();
        odomafterauton = false;
        //Controller.rumble("-"); //test
    }
    if (btnUp_new_press(Controller.ButtonUp.pressing())) {
        odom_lift.toggle();
        if(!odom_lift.state()){ //rumbles the controller if the odom piston is down
        Controller.rumble("-");
    } 
    }
}

void Assembly::matchloader() {
    if (btnRight_new_press(Controller.ButtonRight.pressing())) {
        matchloader_piston.toggle();
    }
}

void Assembly::wing() {
    if (wingafterauton == true && wing_piston.state()){ //ensures wing is always up at the start of driver control
        wing_piston.toggle();
        wingafterauton = false;
        Controller.rumble(".");
    }
    if (btnY_new_press(Controller.ButtonY.pressing())) {
        wing_piston.toggle();
    }
}


// HOLD WING (uncomment wingafterauton in macros.h and use afterauton macro)
// void Assembly::wing() {
//     if (Controller.ButtonY.pressing() && wingafterauton == true) {
//         wing_piston.set(false);
//     } else if (wingafterauton == false) {
//         wing_piston.set(false);
//    } else {
//     wing_piston.set(true);
//     }
// }

//     } else if (!Controller.ButtonY.pressing() && wingafterauton == false) {
//         wing_piston.set(false);
//     } else if (Controller.ButtonY.pressing() && wingafterauton == false) {
//         wingafterauton = true;




// void Assembly::anti_tip() {
//     inertial_sensor.pitch();
//     if (inertial_sensor.pitch() > 60) {
//     chassis.left_drive.spin(vex::directionType::fwd, -12, vex::voltageUnits::volt);
//     chassis.right_drive.spin(vex::directionType::fwd, -12, vex::voltageUnits::volt);
//     } else if (inertial_sensor.pitch() < -60) {
//     chassis.left_drive.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
//     chassis.right_drive.spin(vex::directionType::fwd, 12, vex::voltageUnits::volt);
//     }
// }


// void Assembly::move_lift_arm() {
    // Create a proportional controller. Increase the P just enough so there isn't much oscillation.
    //PID lift_PID(.1, 0, 0);
    //while (true) {
        // How far we need to move until desired angle
        //float error = lift_arm_position - lift_arm_encoder.angle();
        // Converting error into motor voltage
        //float output = lift_PID.compute(error);
        //lift_arm_motors.spin(fwd, output, volt);
        //vex::this_thread::sleep_for(20);
    //}
//}

// void Assembly::lift_arm_control() {
//     // new_press macro only allows input to go through when button is pressed. Resets after button is released.
//     if (btnX_new_press(Controller.ButtonX.pressing())) {
//         // If Up arrow is pressed it will swap lift positions between scoring and loading
//         if (lift_arm_position != SCORING) {
//             lift_arm_position = SCORING; // Lift task will read this value
//         } else {
//             lift_arm_position = LOADING;
//         }
//     } else if (btnUp_new_press(Controller.ButtonUp.pressing())) {
//         // If Up arrow is pressed it will swap lift positions between loading and idle
//         if (lift_arm_position != LOADING) {
//             lift_arm_position = LOADING;
//         } else {
//             lift_arm_position = IDLE;
//         }
//     }
// }
