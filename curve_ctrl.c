#include "curve_ctrl.h"
curve_status_t curve_init(curve_ctrl_t *ctrl, const curve_config_t *cfg){
    if(ctrl == NULL || cfg == NULL){
        return CURVE_ERR_NULL;
    }
    else if(cfg->e_range<=0||cfg->out_max<=0||cfg->slew_max<=0){
        return CURVE_ERR_PARAM;
    }
    else if(!(cfg->out_pt[0] <= cfg->out_pt[1] && cfg->out_pt[1] <= cfg->out_pt[2] && cfg->out_pt[2] <= cfg->out_pt[3] && cfg->out_pt[3] <= cfg->out_pt[4])){
        return CURVE_ERR_PARAM;
    }
    ctrl->cfg=*cfg;
    ctrl->out=0;
    ctrl->first_run=1;
    return CURVE_OK;
}
void curve_reset(curve_ctrl_t *ctrl){
    ctrl->out=0;
    ctrl->first_run=1;
}
float curve_update(curve_ctrl_t *ctrl, float setpoint, float measured, float dt){
    if (ctrl == NULL) {
        return 0.0f;
    }
    else if(dt <= 0){
        return 0.0f;
    }
    float e=setpoint-measured;
    float e_pt[5];
    float target;
    for(int i=0;i<CURVE_POINT_COUNT;i++){
        e_pt[i]=(i-2)*(ctrl->cfg.e_range/2);
    }
    if(e<=e_pt[0]){
        target = ctrl->cfg.out_pt[0];
    }
    else if(e>=e_pt[4]){
        target=ctrl->cfg.out_pt[4];
    }
    else{
        for(int i=0;i<=3;i++){
            if(e>e_pt[i]&&e<=e_pt[i+1]){
                target = ctrl->cfg.out_pt[i] + (e - e_pt[i]) / (e_pt[i+1] - e_pt[i]) * (ctrl->cfg.out_pt[i+1] - ctrl->cfg.out_pt[i]);
                break;
            }
        }
    }
    float step=target;
    if(ctrl->first_run==1){
        step=target;
    }
    else if(target-ctrl->out>ctrl->cfg.slew_max*dt){
        step=ctrl->out+ctrl->cfg.slew_max*dt;
    }
    else if(target-ctrl->out<-(ctrl->cfg.slew_max*dt)){
        step=ctrl->out-ctrl->cfg.slew_max*dt;
    }

    if(step>ctrl->cfg.out_max){
        step=ctrl->cfg.out_max;
    }
    else if(step<-(ctrl->cfg.out_max)){
        step=-(ctrl->cfg.out_max);
    }
    ctrl->out=step;
    ctrl->first_run=0;
    return step;
}