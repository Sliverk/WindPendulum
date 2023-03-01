#include "key.h"
#include "delay.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//����������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

//������ʼ������
void KEY_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOA,GPIOEʱ��
 
  GPIO_InitStructure.GPIO_Pin = 0x00f0; //KEY0 KEY1 KEY2��Ӧ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE1��2,3,4
	GPIO_InitStructure.GPIO_Pin = 0x000f; //KEY0 KEY1 KEY2��Ӧ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
	GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE1��2,3,4
	
	
} 
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��KEY0����
//2��KEY1����
//3��KEY2���� 
//4��WKUP���� WK_UP
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY2>WK_UP!!
u8 KEY_Scan(void)
{	 
	u16 t,k=0,value=0;
	static u16 key_pres=0,keyval=0;
	static uint16_t gpiovalue;
	gpiovalue = GPIO_ReadOutputData(GPIOE);
	gpiovalue &= 0xff00;
	GPIO_Write(GPIOE,0x0000|gpiovalue);
	if(!(KEY0&&KEY1&&KEY2&&KEY3))
	{
		for(t=0x10;t<=0x80;t=t<<1)
		{	
			GPIO_Write(GPIOE,((~t)&0xf0)|gpiovalue);
			if(!(KEY0&KEY1&KEY2&KEY3))
				break;
			k=k+4;
		}			 
		if(KEY0==0)			value =k+1;
		else if(KEY1==0)value= k+2;
		else if(KEY2==0)value= k+3;
		else if(KEY3==0)value= k+4;
	}	   

	if((!key_pres)&&value)
	{
		key_pres=1;
		keyval=value;
	}
	if(key_pres&&(!value))
	{
		key_pres=0;
		return keyval;
	}
 	return 0;// �ް�������
}















