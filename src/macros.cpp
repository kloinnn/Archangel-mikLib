#include "vex.h"

using namespace vex;
using namespace mik;

AllianceColor keepColor;
double hue;
double scoringTime;
bool wingafterauton = false;
bool odomafterauton = false;

void intake_in(){
    assembly.middle_intake.spin(fwd, -12, volt);
    assembly.top_intake.spin(fwd, 12, volt);
    assembly.bottom_intake.spin(fwd, -12, volt);

}

void stop_intake(){
  assembly.middle_intake.stop(brake);
  assembly.top_intake.stop(brake);
  assembly.bottom_intake.stop(brake);
}

void score_high(){
    assembly.middle_intake.spin(fwd, -12, volt);
    assembly.top_intake.spin(fwd, 12, volt);
    assembly.bottom_intake.spin(fwd, -12, volt);
    assembly.hood_piston.close();
}

void outtake(){
    assembly.middle_intake.spin(fwd, 12, volt);
    assembly.top_intake.spin(fwd, -12, volt);
    assembly.bottom_intake.spin(fwd, 12, volt);
}

void outtake_skills(){
    assembly.middle_intake.spin(fwd, 12, volt);
    assembly.top_intake.spin(fwd, -12, volt);
    assembly.bottom_intake.spin(fwd, 5, volt);
    assembly.intake_lift.open();
}

void matchloader_down(){assembly.matchloader_piston.open();}
void matchloader_up(){assembly.matchloader_piston.close();}

void wiggle(){
    chassis.drive_with_voltage(-2, 8);
    wait(0.3, sec);
    chassis.drive_with_voltage(8, -2);
    wait(0.6, sec);
    chassis.drive_with_voltage(-2, 8);
    wait(0.6, sec);
    chassis.drive_with_voltage(8, -2);
    wait(0.3, sec);
}

void afterauton() {
    odomafterauton = true;
    wingafterauton = true;
}




void long_goal_colorsort_auton(){
    assembly.middle_intake.spin(fwd, -12, volt);
    assembly.top_intake.spin(fwd, 12, volt);
    assembly.bottom_intake.spin(fwd, -12, volt);
    assembly.hood_piston.open();

                int timeout_start = Brain.Timer.time(vex::timeUnits::sec); //start a timeout timer
                assembly.color_encoder.objectDetectThreshold(60); //ensures the object is detected close to the sensor

                while (1) {
                bool ballnear = assembly.color_encoder.isNearObject(); //get proximity of the object
                double hue = assembly.color_encoder.hue(); //get color of the object

                //if blue ball is detected on red alliance or red ball is detected on blue alliance
                    if ((ballnear && (keepColor == RED) && (hue > 180 && hue < 250)) || (ballnear && (keepColor == BLUE) && (hue > 350 || hue < 20))) {
                    wait(0.6, sec); //continue outtaking for 0.2s before spinning the motors back
                        vex::task outtake_one_ball_mid([](){ //task so that it can get rid of the ball as it moves on
                            assembly.hood_piston.close();
                            assembly.middle_intake.spin(fwd, 12, volt); //outtake
                            assembly.top_intake.spin(fwd, -12, volt);
                            assembly.bottom_intake.spin(fwd, 12, volt);
                            vex::this_thread::sleep_for(200);
                            assembly.middle_intake.spin(fwd, -8, volt); //score the wrong color ball mid
                            assembly.top_intake.spin(fwd, -10, volt);
                            assembly.bottom_intake.spin(fwd, -12, volt);
                            vex::this_thread::sleep_for(200);
                            assembly.hood_piston.open();
                            suck();
                        return 0;
                        });
                        break;
                    }
                    if (Brain.Timer.time(vex::timeUnits::sec) - timeout_start > scoringTime) { //if no oppposite-colored balls appear after the allotted scoring time, the task will end
                        assembly.hood_piston.close();
                        break;
                    }
                    vex::this_thread::sleep_for(20);

                }


}



void suck() {
    vex::task suck_middle_task([](){
    assembly.middle_intake.spin(fwd, 12, volt); //suck balls back into intake
    assembly.top_intake.spin(fwd, 12, volt);
    assembly.bottom_intake.spin(fwd, 12, volt);
    vex::this_thread::sleep_for(200);
    assembly.middle_intake.spin(fwd, -12, volt); //bring balls back into primed position
    assembly.top_intake.spin(fwd, 12, volt);
    assembly.bottom_intake.spin(fwd, -12, volt);
    vex::this_thread::sleep_for(200);
    assembly.middle_intake.stop(brake);
    assembly.top_intake.stop(brake);
    assembly.bottom_intake.stop(brake);
    return 0;
    });
    
}


void colorsuck() { //with an optical sensor near the top roller, we can prevent any blue balls from being scored in the middle goal during skills
    assembly.middle_intake.spin(fwd, -8, volt); //score in the middle goal while blue object is not recognized
    assembly.top_intake.spin(fwd, -10, volt);
    assembly.bottom_intake.spin(fwd, 12, volt);

            int timeout_start = Brain.Timer.time(vex::timeUnits::sec); //start a timeout timer
            assembly.color_encoder.objectDetectThreshold(60); //ensures the object is detected close to the sensor

            while (1) {
            bool ballnear = assembly.color_encoder.isNearObject(); //get proximity of the object
            double hue = assembly.color_encoder.hue(); //get color of the object

                if (ballnear && (hue > 180 && hue < 250)) { //if blue ball is detected
                wait(0.2, sec); //continue outtaking for 0.2s before spinning the motors back
                suck();
                    break;
                }
                if (Brain.Timer.time(vex::timeUnits::sec) - timeout_start > 4.5) { //in case the bot has no blue balls, the task will end
                    break;
                }
                vex::this_thread::sleep_for(20);

            }

}



// void intake_ring_halfway() {
//     assembly.intake_motor.spin(fwd, 10, volt);
//     vex::task intake_ring_halfway_task([](){
//         vex::distance d(PORT12);
//         int timeout_start = Brain.Timer.time(vex::timeUnits::sec);
//         while (1) {
//             if (d.objectDistance(mm) < 50) {
//                 assembly.intake_motor.stop(brake);
//                 break;
//             }
//             if (Brain.Timer.time(vex::timeUnits::sec) - timeout_start > 5) {
//                 break;
//             }
//             vex::this_thread::sleep_for(50);

//         }
//         return 0;
//   });
// }

// void intake_in() {
//     assembly.intake_motor.spin(fwd, 12, volt);
// }

// void stop_intake() {
//     assembly.intake_motor.stop(brake);
// }

// void intake_reverse() {
//     assembly.intake_motor.spin(fwd, -12, volt);
// }

// void clamp_goal() {
//     assembly.long_piston.set(true);
//     wait(.2, sec);
//     mogo_constants();
// }

// void unclamp_goal() {
//     assembly.long_piston.set(false);
//     odom_constants();
// }

// void move_lift(int pos) {
//     static bool lift_task_started = false;
//     if (!lift_task_started) {
//         assembly.init();
//         lift_task_started = true;
//     }
//     assembly.lift_arm_position = pos;
// }
