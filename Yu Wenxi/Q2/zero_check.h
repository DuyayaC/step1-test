/* ==========================================================================
* zero_check.h —— 过零检测
* ========================================================================== */
#ifndef ZERO_CHECK_H
#define ZERO_CHECK_H
#include <stdint.h>
#define ZERO_ECD_CIRCLE 8192
#define ZERO_ECD_HALF 4096
#define ZERO_ANGLE_CIRCLE 360.0f
#define ZERO_ANGLE_HALF 180.0f
void zero_check_ecd(int32_t *target, int32_t now);
void zero_check_angle(float *target, float now);
#endif /* ZERO_CHECK_H */