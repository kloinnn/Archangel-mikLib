#include "vex.h"

using namespace vex;
using namespace mik;

std::string blue_right_winpoint(bool calibrate, mik::auto_variation var, bool get_name) {
    if (get_name) { return "blue right winpoint(4+3)"; }
    if (calibrate) {
     chassis.set_coordinates(0, 0, 0); //change after measuring distance from tracking center

        return "";
    }

    return "";
}