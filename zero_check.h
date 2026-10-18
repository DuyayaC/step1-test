/* ==========================================================================
* zero_check.h —— 过零检测
* ========================================================================== */
#ifndef ZERO_CHECK_H
#define ZERO_CHECK_H
#include <stdint.h>
#define ZERO_ECD_CIRCLE 
#define ZERO_ECD_HALF 
#define ZERO_ANGLE_CIRCLE 
#define ZERO_ANGLE_HALF 
void zero_check_ecd(int32_t *target, int32_t now);
void zero_check_angle(float *target, float now);
#endif /* ZERO_CHECK_H */