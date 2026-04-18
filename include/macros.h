#pragma once

#include "vex.h"

enum AllianceColor {
    BLUE,
    RED
};

extern AllianceColor keepColor;
extern double hue;
extern double scoringTime;
extern bool wingafterauton;
extern bool odomafterauton;

void intake_in();

void stop_intake();

void score_high();

void outtake();

void outtake_skills();

void intake_mid();

void intake_high();
void intake_high_slow();

void wing_down();
void wing_up();

void matchloader_down();
void matchloader_up();

void suck();

void colorsuck();

void long_goal_colorsort_auton();

void wiggle();

void afterauton();