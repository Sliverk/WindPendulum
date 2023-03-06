#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "timer.h"
#include "key.h"
#include "filter.h"
#include "control.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "math.h"
#include "beep.h"

u16 AD_con[32]={0};
u16 t=0,com_flag=0;
float pitch,roll,yaw,pwm_x,pwm_y;
short aacx,aacy,aacz;	
short gyrox,gyroy,gyroz;	
u16 key=0,flag=0,len=0,ang=0,num;
u8 flag1=0,flag2=0,qibu=200;;
float weizhi1=0,weizhi2=0;

struct PID pid1={0.23,0,-40,0,0,0,1000,-1000},pid2={-0.23,0,40,0,0,0,1000,-1000};
struct PID pid3={1,0,-20,0,0,0,10000,-10000},pid4={1,0,-20,0,0,0,10000,-10000},pid5={-60,0,-30,0,0,0,0,0},pid6={1,0,0,0,0,0,0,0};

void fun_one(void);
void fun_two(void);
void fun_three(void);
void fun_four(void);
void fun_five(void);
void key_fun(void);
int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init(168); 
	uart_init(115200);
	printf("SPG(19);\n");
	delay_ms(200);
	KEY_Init();
	LED_Init();
	BEEP_Init();
	MPU_Init();
	while(mpu_dmp_init())
	{
		delay_ms(200);
	}
	
	
 	TIM3_PWM_Init(1999,3);
	TIM_SetCompare1(TIM3,1999);
	TIM_SetCompare2(TIM3,1999);
	TIM_SetCompare3(TIM3,1999);
	TIM_SetCompare4(TIM3,1999);
	TIM2_Int_Init(5000,83);
  while(1) 
	{
	}
}



void TIM2_IRQHandler(void)
{
	static float hgs=0;
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
	{
		mpu_dmp_get_data(&pitch,&roll,&yaw);
		pitch=kalman(pitch,10,1);
		roll=kalman2(roll,10,1);
		key=KEY_Scan();
		key_fun();
		if(flag==1)
		{
			fun_one();
		}
		if(flag==2)
		{
			fun_two();
		}
		if(flag==3)
		{
			fun_three();
		}
		if(flag==4)
		{
			fun_five();
		}
		pwm_xianfu(&pwm_x,&pwm_y);
		set_pwm((int)(pwm_x),(int)(pwm_y));
		if(!((t++)%100))
		{
			LED0=!LED0;
			if(com_flag)
				BEEP=!BEEP;
			if((!flag)||(flag>3))
			{
				printf("DS16(230,210,'pitch:%f',15);",pitch);
				printf("DS16(40,210,'roll:%f',15);",roll);
				printf("DS32(180,130,'%3d',15);",len);
				printf("DS32(180,90,'%3d',15);",ang);
				printf("DS32(180,50,'%3d',15);\n",num);
			}
		}
	}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
}

void key_fun(void)
{
	if(key)
		switch(key)
		{
			case 13:
			{flag=5;len=num;num=0;break;}
			case 5:
			{flag=6;ang=num;num=0;break;}
			case 1:
			{flag=1;break;}
			case 2:
			{flag=2;break;}
			case 3:
			{flag=3;break;}
			case 4:
			{flag=4;break;}
			case 9:
			{
				num=(num*10);
				break;
			}
			case 14:
			{
				num=(num*10+1);
				break;
			}
			case 10:
			{
				num=(num*10+2);
				break;
			}
			case 6:
			{
				num=(num*10+3);
				break;
			}
			case 15:
			{
				num=(num*10+4);
				break;
			}
			case 11:
			{
				num=(num*10+5);
				break;
			}
			case 7:
			{
				num=(num*10+6);
				break;
			}
			case 16:
			{
				num=(num*10+7);
				break;
			}
			case 12:
			{
				num=(num*10+8);
				break;
			}
			case 8:
			{
				num=(num*10+9);
				break;
			}
		}
	}

	
void fun_one(void)
{
	static u32 flag3=0,flag4=0,flag1=0,set_flag=0;
	static float pitch_last,roll_last,ang_len,ang_len_last;
	if(!(len||ang))
	{
		fun_four();
	}
	if((len)&&(!ang))
	{
		static u8 set_flag=0,BEEP_flag=0;
		static float ang_baidong,set_value=0,i,j;
		ang_baidong=57.3*atan(len/170.0);
		if(!(flag3||flag4))
		{
			if(len>=55)
			{
				i=8;
				j=0.2;
			}
			else
			{
				i=15;
				j=0.45;
			}
			set_value=len+160;
			flag3=1;
			pid1.kp=0.23;
			pid1.kd=-40;
			pid2.kp=65;
			pid2.kd=-20;
			pid1.ba=ang_baidong*1.1;
			
		}
		if((!flag4)&&flag3)
		{
			weizhi1+=pid(&pid1,pitch);
			pwm_x=pid(&pid3,weizhi1);
		}
		if((pitch>ang_baidong)&&(!flag4))
		{
			flag4=1;
			pwm_x=0;
		}
//		if((pitch>-1)&&(pitch<1))
//			BEEP_flag=1;
		if((pitch<0)&&(flag4)&&(flag3)&&set_flag)
		{
			BEEP_flag=1;
			set_flag=0;
			pwm_x=-set_value;
			flag3=0;
		}
		if((pitch>0)&&(flag4)&&(!flag3)&&set_flag)
		{
			set_flag=0;
			pwm_x=set_value;
			flag3=1;
		}
		if(((pitch-pitch_last)<0.05)&&((pitch-pitch_last)>-0.05)&&(!set_flag))
		{
			if(pitch>ang_baidong)
				set_value-=(pitch-ang_baidong)/ang_baidong*i+j;
			if((pitch<ang_baidong)&&(pitch>0))
				set_value+=(ang_baidong-pitch)/ang_baidong*i+j;
			if(pitch<(-ang_baidong))
				set_value-=(-ang_baidong-pitch)/ang_baidong*i+j;
			if((pitch>(-ang_baidong))&&(pitch<0))
				set_value+=(ang_baidong+pitch)/ang_baidong*i+j;
			set_flag=1;
		}
		pwm_y=pid(&pid2,roll);
		pitch_last=pitch;
		if(BEEP_flag)
		{
			if((pitch>=ang_baidong-1.2)||(pitch<=(-ang_baidong+1.2)))
			com_flag=1;
		}
	}
	if(ang&&(!len))
	{
		ang_len=sqrt(pitch*pitch+roll*roll);
//		if(!flag1)
//		{
//			flag1=1;
//			pid1.kp=0.23;
//			pid1.kd=-40;
//			pid2.kp=-0.23;
//			pid2.kd=40;
//			pid1.ba=20*cos(ang/360.0*6.283);
//			pid2.ba=20*sin(ang/360.0*6.283);
//		}
//		ang_len=sqrt((pitch-pid1.ba)*(pitch-pid1.ba)+(roll-pid2.ba)*(roll-pid2.ba));
//		if((ang_len<0.1)&&(!flag4))
//		{
//			flag4=1;
//			com_flag=1;
//			pwm_x=0;
//			pwm_y=0;
////			pid1.ba=-pid1.ba;
////			pid2.ba=-pid2.ba;
//		}
////		if((ang_len<1)&&(flag4))
////		{
////			flag4=0;
////			com_flag=1;
////		}
//		if(!flag4)
//		{
//			weizhi1+=pid(&pid1,pitch);
//			pwm_x=pid(&pid3,weizhi1);
//			weizhi2+=pid(&pid2,roll);
//			pwm_y=pid(&pid4,weizhi2);
//		}
	if(set_flag==150)
	{
		pwm_x=0;
		pwm_y=0;
	}
	if((!set_flag)&&(ang_len<2))	
	{
		pwm_x=1500*cos(6.283*ang/360.0);
		pwm_y=-1500*sin(6.283*ang/360.0);
	}
	if(ang_len>20)
	{		com_flag=1;}
	set_flag++;
//	if((ang_len<5)&(pitch<0)&&(set_flag))	
//	{
//		set_flag++;
//		pwm_x=-1000*cos(6.283*ang/360.0);
//		pwm_y=1000*sin(6.283*ang/360.0);
//	}
	}
}	




void fun_two(void)
{
	static float ang_len,pitch_last,flag1=0;
	pid1.kp=-80;
	pid1.kd=270;
	pid2.kp=80;
	pid2.kd=-270;
	pid1.ba=0;
	pid2.ba=0;
	ang_len=sqrt(pitch*pitch+roll*roll);
	
	if(ang_len>8)
	{
		if(pitch>0)
			pid1.ba=1;
		else 
			pid1.ba=-1;
		if(roll>0)
			pid2.ba=1;
		else 
			pid2.ba=-1;
	}
	pwm_x=pid(&pid1,pitch);
	pwm_y=pid(&pid2,roll);
	if(ang_len>5)
	{
		flag1=1;
	}
	if((ang_len<1.7)&&flag1&&((pitch-pitch_last)>(-0.1))&&((pitch-pitch_last)<0.1))
		com_flag=1;
		
}




void fun_three(void)
{
	static float Ang_len[200]={0},len_pinjun=0;
	static float ang_len=0,cir_fudu=20;
	static float pitch_last,roll_last;
	static u16 t=0;
	
	pitch=1.5*pitch-0.5*pitch_last;
	roll=1.5*roll-0.5*roll_last;
	ang_len=sqrt((pitch*pitch)+(roll*roll));
	
	if(ang_len>57.3*atan((len-1)/170.0))
	{
		cir_fudu=cir_fudu-1.15;
	}
	if(ang_len<57.3*atan((len-1)/170.0))
	{
		cir_fudu=cir_fudu+1.15;
	}
	
	if(cir_fudu>350) cir_fudu = 350;
	pwm_x=roll/ang_len*cir_fudu+0.78*roll+60*(roll-roll_last);
	pwm_y=pitch/ang_len*cir_fudu+0.78*pitch+60*(pitch-pitch_last);
	pitch_last=pitch;
	roll_last=roll;
	Ang_len[t]=ang_len;
	len_pinjun=Ang_len[t]+len_pinjun-Ang_len[(t+1)%200];
	if(len_pinjun>11460*atan((len-1)/170.0))
	{
		com_flag=1;
//		BEEP=0;
	}
	t=(t+1)%200;
}




void fun_four(void)
{
	static double flag3=0,flag4=0;
	if(!(flag3||flag4))
	{
		flag3=1;
		pid1.kp=0.23;
		pid1.kd=-40;
		pid2.kp=65;
		pid2.kd=-20;
		pid1.ba=18;
		
	}
	if((!flag4)&&flag3)
	{
		weizhi1+=pid(&pid1,pitch);
		pwm_x=pid(&pid3,weizhi1);
	}
	if((pitch>18)&&(!flag4))
	{
		flag4=1;
		pwm_x=0;
	}
	if((pitch<0)&&(flag4)&&(flag3))
	{
		pwm_x=-250;
		flag3=0;
	}
	if((pitch>0)&&(flag4)&&(!flag3))
	{
		pwm_x=250;
		flag3=1;
	}
	pwm_y=pid(&pid2,roll);
	if((pitch>17)||(pitch<(-17)))
	{
//		BEEP=0;
		com_flag=1;
	}
}

void fun_five(void)
{
	static u8 flag1=0,ang_five;
	if(!flag1)
	{
		flag1=1;
		pid1.kp=0.23;
		pid1.kd=-40;
		pid2.kp=-0.23;
		pid2.kd=40;
		ang_five=57.3*atan(len/85.0);
		pid1.ba=ang_five*cos(ang/360.0*6.283);
		pid2.ba=ang_five*sin(ang/360.0*6.283);
	}
	weizhi1+=pid(&pid1,pitch);
	pwm_x=pid(&pid3,weizhi1);
	weizhi2+=pid(&pid2,roll);
	pwm_y=pid(&pid4,weizhi2);
}