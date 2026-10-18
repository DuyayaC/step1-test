#include <stdio.h>
#include "curve_ctrl.h"

curve_status_t curve_init(curve_ctrl_t *ctrl, const curve_config_t *cfg)
{
    if (ctrl==NULL) return CURVE_ERR_NULL;
    else if((cfg->e_range)>0 && (cfg->out_max)>0 && (cfg->slew_max)>0)
    {
        for(uint8_t i=1;i<CURVE_POINT_COUNT;i++)
        {
            if (cfg->out_pt[i]<cfg->out_pt[i-1]) return CURVE_ERR_PARAM;
        }
        ctrl->first_run=1;
        ctrl->out=0;
        return CURVE_OK;
    }
}

void curve_reset(curve_ctrl_t *ctrl)
{
    ctrl->out = 0.0f;
    ctrl->first_run = 1;
}

float curve_update(curve_ctrl_t *ctrl, float setpoint, float measured, float dt)
{
    if (ctrl==NULL||dt <= 0) return 0.0f;

    float e_pt[CURVE_POINT_COUNT]; 
    for (uint8_t i = 0; i < CURVE_POINT_COUNT; i++)
    {
        e_pt[i] = ((float)i - 2.0f) * (ctrl->cfg.e_range / 2.0f);
    }

    float error = setpoint - measured; 
    float target = 0.0f;

    if (error <= e_pt[0]) 
    {
        target = ctrl->cfg.out_pt[0];
    } 
    else if (error >= e_pt[4]) 
    {
        target = ctrl->cfg.out_pt[4];
    }
    else 
    {
        uint8_t buff = 0;
        for (int i = 0; i < 4; i++) 
        {
            if (error >= e_pt[i] && error <= e_pt[i+1]) 
            {
                buff = i;
                break;
            }
        }
        target = (ctrl->cfg.out_pt[buff]) + (error - e_pt[buff]) / (e_pt[buff+1] - e_pt[buff]) * (ctrl->cfg.out_pt[buff+1] - ctrl->cfg.out_pt[buff]);
    }
    float result=target;
    if (ctrl->first_run == 0)
    {
        if (target - ctrl->out > (ctrl->cfg.slew_max)*dt) 
        {
            if (target - ctrl->out > ctrl->cfg.out_max) result=ctrl->cfg.out_max;
            else result= ctrl->out+ctrl->cfg.out_max;
        }
        else if (target - ctrl->out < -((ctrl->cfg.slew_max)*dt))
        {
            if (target - ctrl->out < -(ctrl->cfg.out_max)) result= -(ctrl->cfg.out_max);
            else result= ctrl->out-ctrl->cfg.out_max;
        }
    }
    else ctrl->first_run = 0;
    ctrl->out=result;
    return result;
}