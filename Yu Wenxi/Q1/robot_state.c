#include <stdio.h>
#include "robot_state.h"

robot_state_t robot_state_step(robot_state_t cur, robot_event_t event)
{
    switch (cur)
    {
    case ROBOT_STATE_IDLE:
        if (event == ROBOT_EVENT_START) 
        {
        cur = ROBOT_STATE_RUN; // 迁移规则1
        // printf("状态机: IDLE -> RUN\n");
        }
        else if (event == ROBOT_EVENT_FAULT) 
        {
        cur = ROBOT_STATE_FAULT; // 迁移规则2
        // printf("状态机: IDLE -> FAULT\n");
        }
        break;

    case ROBOT_STATE_RUN:
        if (event == ROBOT_EVENT_STOP) 
        {
        cur = ROBOT_STATE_IDLE; // 迁移规则3
        // printf("状态机: RUN -> STOP\n");
        }
        else if (event == ROBOT_EVENT_FAULT) 
        {
        cur = ROBOT_STATE_FAULT; // 迁移规则4
        // printf("状态机: RUN -> FAULT\n");
        }
        break;

    case ROBOT_STATE_FAULT:
        if (event == ROBOT_EVENT_CLEAR) 
        {
        cur = ROBOT_STATE_IDLE; // 迁移规则5
        // printf("状态机: FAULT -> IDLE\n");
        }
        break;
    // default:
        // printf("状态机保持原状态%d\n",cur);
    }
    return cur;
}

