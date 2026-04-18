#pragma once

#include "vex.h"

using namespace vex;

//enum lift_positions : int { IDLE = 229, LOADING = 206, SCORING = 99 };

class Assembly {
public:
    Assembly(
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
    );
    
    void init();
    void control();

    void intake_control();
    void mid_hood();
    void odom_lift_control();
    void matchloader();
    void wing();
    //void anti_tip();
 
    mik::motor middle_intake;
    mik::motor top_intake;
    mik::motor bottom_intake;
    vex::optical color_encoder;
    vex::inertial inertial_sensor;
    mik::piston mid_hood_piston;
    mik::piston odom_lift;
    mik::piston hood_piston;
    mik::piston matchloader_piston;
    mik::piston wing_piston;
    mik::piston intake_lift;
};