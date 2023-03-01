#include "timer.h"
 

void TIM3_PWM_Init(u16 arr,u16 psc)
{		 					 
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;         
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;      
	GPIO_Init(GPIOC,&GPIO_InitStructure);              
	  
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM3);
	
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period=arr;  
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 
	TIM_OC1Init(TIM3, &TIM_OCInitStructure); 
	TIM_OC2Init(TIM3, &TIM_OCInitStructure); 
	TIM_OC3Init(TIM3, &TIM_OCInitStructure); 
	TIM_OC4Init(TIM3, &TIM_OCInitStructure); 

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable); 
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
 
  TIM_ARRPreloadConfig(TIM3,ENABLE);
	TIM_Cmd(TIM3, ENABLE);
	
}  

//void TIM4_Cap_Init(u16 arr,u16 psc)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//	TIM_ICInitTypeDef  TIM4_ICInitStructure;

//	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  	   
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 	
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9; 
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 
//	GPIO_Init(GPIOC,&GPIO_InitStructure);

//	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM4);
//  GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM4);
//	GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_TIM4);
//	GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM4);
//	  
//	TIM_TimeBaseStructure.TIM_Prescaler=psc;
//	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
//	TIM_TimeBaseStructure.TIM_Period=arr; 
//	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
//	
//	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
//	
//	TIM4_ICInitStructure.TIM_Channel= TIM_Channel_1;
//  TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	
//  TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 
//  TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	
//  TIM4_ICInitStructure.TIM_ICFilter = 0x00;
//  TIM_ICInit(TIM4, &TIM4_ICInitStructure);
//	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_2;
//	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
//	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_3;
//	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
//	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_4;
//	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
//		
//	TIM_ITConfig(TIM4,TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,ENABLE);
//  TIM_Cmd(TIM4,ENABLE ); 

// 
//  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		
//	NVIC_Init(&NVIC_InitStructure);	
//}

void TIM2_Int_Init(u32 arr,u32 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
  TIM_TimeBaseInitStructure.TIM_Period = arr;
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc; 
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); 
	TIM_Cmd(TIM2,ENABLE); 
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}


u16 CH1_value1=0,CH2_value1=0,CH3_value1=0,CH4_value1=0,CH1_value2=0,CH2_value2=0,CH3_value2=0,CH4_value2=0;
u16 FLAG=0,cap1_flag=0,cap2_flag=0,cap3_flag=0,cap4_flag=0;
u16 freq1,freq2,freq3,freq4;

//void TIM4_IRQHandler(void)
//{ 		    
//	if(TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
//	{	
//		if(!cap1_flag)
//			CH1_value1=TIM_GetCapture1(TIM4);
//		if(cap1_flag)
//			CH1_value2=TIM_GetCapture1(TIM4);
//		cap1_flag++;
//	}			
//	if(TIM_GetITStatus(TIM4, TIM_IT_CC2) != RESET)//捕获1发生捕获事件
//	{	
//		if(!cap2_flag)
//			CH2_value1=TIM_GetCapture2(TIM4);
//		if(cap2_flag)
//			CH2_value2=TIM_GetCapture2(TIM4);
//		cap2_flag++;
//	}		
//	if(TIM_GetITStatus(TIM4, TIM_IT_CC3) != RESET)//捕获1发生捕获事件
//	{	
//		if(!cap3_flag)
//			CH3_value1=TIM_GetCapture3(TIM4);
//		if(cap3_flag)
//			CH3_value2=TIM_GetCapture3(TIM4);
//		cap3_flag++;
//	}		
//	if(TIM_GetITStatus(TIM4, TIM_IT_CC4) != RESET)//捕获1发生捕获事件
//	{	
//		if(!cap4_flag)
//			CH4_value1=TIM_GetCapture4(TIM4);
//		if(cap4_flag)
//			CH4_value2=TIM_GetCapture4(TIM4);
//		cap4_flag++;
//	}		
//	if((cap1_flag>1)&&(cap2_flag>1)&&(cap3_flag>1)&&(cap4_flag>1))
//	{
//		freq1=(CH1_value2-CH1_value1)/(cap1_flag-1);
//		freq2=(CH2_value2-CH2_value1)/(cap2_flag-1);
//		freq3=(CH3_value2-CH3_value1)/(cap3_flag-1);
//		freq4=(CH4_value2-CH4_value1)/(cap4_flag-1);
//		cap1_flag=0,cap2_flag=0,cap3_flag=0,cap4_flag=0;
//		TIM_SetCounter(TIM4,0);
//		TIM_Cmd(TIM4,ENABLE );
//		FLAG=1;
//	}		
//	TIM_ClearITPendingBit(TIM4,TIM_IT_CC4|TIM_IT_CC3|TIM_IT_CC2|TIM_IT_CC1|TIM_IT_Update); //清除中断标志位
//}

