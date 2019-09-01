#include <math.h>
float deg_to_rad(float degrees) {
    return degrees / 180.0 * M_PI;
}
float rad_to_deg(float rads) {
    return rads / M_PI * 180.0;
}
