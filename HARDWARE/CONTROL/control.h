#ifndef _CONTROL_H_
#define _CONTROL_H_
#include "sys.h"

struct PID
{
	float kp;
	float ki;
	float kd;
	double ba;
	float i_value;
	float d_value;
	float i_value_max;
	float i_value_min;
};

void pid_init(struct PID *pid);
void pid_set(struct PID *pid,float Kp,float Ki,float Kd);
void pid_irange(struct PID *pid,float I_value_max,float I_value_min);
double pid(struct PID *pid,float value_in);
void set_pwm(int pwm_x,int pwm_y);
void pwm_xianfu(float *pwm_x,float *pwm_y);
#endif
