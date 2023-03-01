#include "control.h"


void pid_init(struct PID *pid)
{
	pid->kp=0;
	pid->ki=0;
	pid->kd=0;
	pid->ba=0;
	pid->i_value=0;
	pid->d_value=0;
	pid->i_value_max=0;
	pid->i_value_min=0;
}

void pid_set(struct PID *pid,float Kp,float Ki,float Kd)
{
	pid->kp=Kp;
	pid->ki=Ki;
	pid->kd=Kd;
}

void pid_irange(struct PID *pid,float I_value_max,float I_value_min)
{
	pid->i_value_max=I_value_max;
	pid->i_value_min=I_value_min;
}

double pid(struct PID *pid,float value_in)
{
	double control_val,error;
	error=value_in-pid->ba;
	control_val=error*pid->kp+(value_in-pid->d_value)*pid->kd+pid->i_value*pid->ki;
	pid->d_value=value_in;
	pid->i_value=pid->i_value+error;
	if(pid->i_value>pid->i_value_max)
		pid->i_value=pid->i_value_max;
	if(pid->i_value<pid->i_value_min)
		pid->i_value=pid->i_value_min;
	return control_val;
}



void set_pwm(int pwm_x,int pwm_y)
{
	if((pwm_x>(0))&&(pwm_x<150))
		pwm_x=150;
	if((pwm_x>-150)&&(pwm_x<=0))
		pwm_x=-150;
	if((pwm_y>(0))&&(pwm_y<150))
		pwm_y=150;
	if((pwm_y>-150)&&(pwm_y<=0))
		pwm_y=-150;
//	if((pwm_x<=(-50))&&(pwm_x>(-100)))
//		pwm_x=-100;
//	if((pwm_y>(-50))&&(pwm_y<50))
//		pwm_y=0;
//	if((pwm_y>=50)&&(pwm_y<100))
//		pwm_y=100;
//	if((pwm_y<=(-50))&&(pwm_y>(-100)))
//		pwm_y=-100;
	

	if(pwm_x>=0)
	{
		TIM_SetCompare1(TIM3,1850);
		TIM_SetCompare3(TIM3,1999-pwm_x);
	}
	if(pwm_x<0)
	{
		TIM_SetCompare1(TIM3,1999+pwm_x);
		TIM_SetCompare3(TIM3,1850);
	}
	
	if(pwm_y>=0)
	{
		TIM_SetCompare2(TIM3,1850);
		TIM_SetCompare4(TIM3,1999-pwm_y);
	}
	if(pwm_y<0)
	{
		TIM_SetCompare2(TIM3,1999+pwm_y);
		TIM_SetCompare4(TIM3,1850);
	}
}

void pwm_xianfu(float *pwm_x,float *pwm_y)
{
	if(*pwm_x>1999)
		*pwm_x=1999;
	if(*pwm_x<(-1999))
		*pwm_x=-1999;
	if(*pwm_y>1999)
		*pwm_y=1999;
	if(*pwm_y<(-1999))
		*pwm_y=-1999;
	
}
