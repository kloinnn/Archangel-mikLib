#include "vex.h"

using namespace vex;
using namespace mik;

std::string blue_sawp(bool calibrate, mik::auto_variation var, bool get_name) { 
    if (get_name) { return "blue sawp"; }
    if (calibrate) {
        chassis.set_coordinates(0, 0, 0); //change after measuring distance from tracking center

        return "";
    }

    //dimensions of robot: 14 in wide, 12.75 behind, 15.25 back aligner, 
    // 17.25 intqke, matchloader 26
    odom_constants();
    keepColor = BLUE;
    scoringTime = 2; //score in long goal for 2s max

    return "";
}