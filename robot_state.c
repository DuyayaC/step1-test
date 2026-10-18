#include "robot_state.h"
robot_state_t robot_state_step(robot_state_t cur, robot_event_t event){
    switch(cur){
        case ROBOT_STATE_IDLE:
            switch(event){
                case ROBOT_EVENT_START:return ROBOT_STATE_RUN;
                case ROBOT_EVENT_FAULT:return ROBOT_STATE_FAULT;
                default:return cur;
            }
        case ROBOT_STATE_RUN:
            switch(event){
                case ROBOT_EVENT_STOP:return ROBOT_STATE_IDLE;
                case ROBOT_EVENT_FAULT:return ROBOT_STATE_FAULT;
                default:return cur;
            }
        case ROBOT_STATE_FAULT:
            switch(event){
                case ROBOT_EVENT_CLEAR:return ROBOT_STATE_IDLE;
                default:return cur;
            }
        default:return cur;
    }
    return cur;
}