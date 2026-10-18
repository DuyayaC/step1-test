#include <stdio.h>
#include "zero_check.h"

void zero_check_ecd(int32_t *target, int32_t now)
{
    int32_t DIFF=*target-now;
    if (DIFF > ZERO_ECD_HALF)
    {
        *target-=ZERO_ECD_CIRCLE;
    }
    else if (DIFF < -ZERO_ECD_HALF)
    {
        *target += ZERO_ECD_CIRCLE;
    }
}

void zero_check_angle(float *target, float now)
{
    float DIFF=*target-now;
    if (DIFF > ZERO_ANGLE_HALF)
    {
        *target-=ZERO_ANGLE_CIRCLE;
    }
    else if (DIFF < -ZERO_ANGLE_HALF)
    {
        *target += ZERO_ANGLE_CIRCLE;
    }
}