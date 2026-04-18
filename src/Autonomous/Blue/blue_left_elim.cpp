#include "vex.h"

using namespace vex;
using namespace mik;

std::string blue_left_elim(bool calibrate, mik::auto_variation var, bool get_name) {   
    chassis.mirror_all_auton_y_pos();
    if (get_name) { return "blue left elim (7b push)"; }
    if (calibrate) {
      	blue_right_elim(calibrate, var, get_name);

      	return "";
    }

blue_right_elim(calibrate, var, get_name);

    return "";
}