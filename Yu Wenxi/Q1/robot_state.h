/* ==========================================================================
* robot_state.h —— 机器人状态机
*
* 状态(state)：系统当前所处的情况
* 事件(event)：刚刚发生的动作
* 迁移(transition)：在某个状态下收到某个事件后转到哪个状态
*
* 本模块只做计算，返回值就是下一个状态。
* ========================================================================== */
#ifndef ROBOT_STATE_H
#define ROBOT_STATE_H
#include <stdint.h>

/* 状态枚举 */
typedef enum {
    ROBOT_STATE_IDLE = 0,   /* 空闲，未运行 */
    ROBOT_STATE_RUN,        /* 运行中 */
    ROBOT_STATE_FAULT       /* 故障 */
} robot_state_t;

/* 事件枚举 */
typedef enum {
ROBOT_EVENT_NONE = 0,   /* 无事件 */
ROBOT_EVENT_START,      /* 启动 */
ROBOT_EVENT_STOP,       /* 停止 */
ROBOT_EVENT_FAULT,      /* 报故障 */
ROBOT_EVENT_CLEAR       /* 清除故障 */
} robot_event_t;

/* 计算下一个状态：在 cur 状态下收到 event 后应该转到哪个状态。
*   迁移规则表中列出的组合 -> 转到表中的下一个状态
*   未列出的组合           -> 返回 cur（保持原状态） */
robot_state_t robot_state_step(robot_state_t cur, robot_event_t event);
#endif /* ROBOT_STATE_H */