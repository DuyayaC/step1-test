/* ==========================================================================
* curve_ctrl.h —— 折线（分段线性）控制器
*
* 处理顺序：误差 -> 折线表映射（5 个折点，之间线性插值，两端饱和）
*          -> 变化率限制 -> 限幅。
*
* 折点误差：e_pt[i] = (i - 2) * (e_range / 2)，即 -e_range ~ +e_range 等分 5 点。
* 本控制器不使用 Kp / Ki / Kd，也没有积分项、微分项。
* 内部状态放在 curve_ctrl_t，由调用者持有，可定义多个实例。
* ========================================================================== */
#ifndef CURVE_CTRL_H
#define CURVE_CTRL_H

#include <stdint.h>
#define CURVE_POINT_COUNT 5u    /* 折点个数 */

/* 返回码 */
typedef enum {
CURVE_OK        =  0,   /* 成功 */
CURVE_ERR_NULL  = -1,   /* 指针是空指针 */
CURVE_ERR_PARAM = -2    /* 量程、折点输出、变化率或限幅不合法 */
} curve_status_t;

typedef struct {
float e_range;                      /* 折点误差量程，必须 > 0 */
float out_pt[CURVE_POINT_COUNT];    /* 5 个折点的输出，与 -e_range ~ +e_range 一一对应 */
float slew_max;                     /* 每单位时间允许的最大输出变化量，必须 > 0 */
float out_max;                      /* 输出限幅，必须 > 0 */
} curve_config_t;

typedef struct {
curve_config_t cfg;     /* 配置参数 */    
float out;         /* 上一次的输出 */
uint8_t first_run;/* 1 = 还没算过；0 = 已经算过 */
} curve_ctrl_t;

/* 初始化：参数存入结构体，out 清 0，first_run 置 1。
*   ctrl == NULL 或 cfg == NULL -> CURVE_ERR_NULL（不修改结构体）
*   e_range、out_max、slew_max 不是正数
*   或 out_pt 不满足单调不减-> CURVE_ERR_PARAM（不修改结构体）
*   全部合法                -> CURVE_OK */

curve_status_t curve_init(curve_ctrl_t *ctrl, const curve_config_t *cfg);
/* 复位：out 清 0，first_run 置 1，保留配置。调用者保证 ctrl 不是空指针。 */

void curve_reset(curve_ctrl_t *ctrl);
/* 算一步，返回本次输出；ctrl 为空指针时返回 0.0f。
*   dt <= 0                     -> 返回 0.0f，不改变任何内部状态
*   其余按「折线映射 -> 变化率限制 -> 限幅」计算
* 算完后 out 保存本次输出、first_run = 0。 */
float curve_update(curve_ctrl_t *ctrl, float setpoint, float measured, float dt);

#endif /* CURVE_CTRL_H */