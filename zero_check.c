#include "zero_check.h"

#define ZERO_ECD_CIRCLE 8192
#define ZERO_ECD_HALF 4096
#define ZERO_ANGLE_CIRCLE 360.0f
#define ZERO_ANGLE_HALF 180.0f

void zero_check_ecd(int32_t *target, int32_t now) {
    if (*target-now>ZERO_ECD_HALF){
        *target=*target-ZERO_ECD_CIRCLE;
    }
    else if (*target-now<-ZERO_ECD_HALF){
        *target=*target+ZERO_ECD_CIRCLE;
    }
}

void zero_check_angle(float *target, float now) {
    if(*target-now>ZERO_ANGLE_HALF){
        *target=*target-ZERO_ANGLE_CIRCLE;
    }
    else if (*target-now<-ZERO_ANGLE_HALF){
        *target=*target+ZERO_ANGLE_CIRCLE;
    }
}