#include "vex.h"

using namespace vex;
using namespace mik;

std::string red_right_winpoint(bool calibrate, mik::auto_variation var, bool get_name) { 
    if (get_name) { return "red right winpoint(test with wing toggled)"; }
    if (calibrate) {
        chassis.set_coordinates(0, 0, 0);
        // assembly.odom_lift.close();
        return "";
    }
    assembly.wing_piston.toggle();
    afterauton();
    return "";
}