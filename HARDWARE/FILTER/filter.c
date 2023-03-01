#include "filter.h"




/*
	data 待滤波数组地址
	num  数组长度
	fudu 限幅值
	jieshu 滤波阶数			0----均值滤波
											1----1阶限幅
											2----2阶限幅
*/

float xianfu(u16 *data,u32 num,float fudu,u8 jieshu)
{
	u32 t,k=0,m=0;
	double sum=0;
	float avr=0;

	for(t=0;t<num;t++)
	{	
		sum=data[t]+sum;
	}
	avr=sum/num;
	
	
	if(jieshu)
	{
		for(t=0;t<num;t++)
		{	
			if((data[t]<=(1+fudu)*avr)&&(data[t]>=(1-fudu)*avr))
			{
				data[k]=data[t];
				k++;
			}
		}
		
		sum=0;
		for(t=0;t<k;t++)
		{
			sum=sum+data[t];
		}
		avr=sum/k;
	}
	
	if(jieshu==2)
	{
		for(t=0;t<k;t++)
		{	
			if((data[t]<=(1+fudu)*avr)&&(data[t]>=(1-fudu)*avr))
			{
				data[m]=data[t];
				m++;
			}
		}
		sum=0;
		for(t=0;t<m;t++)
		{
			sum=sum+data[t];
		}
		avr=sum/k;
	}
	return avr;
}


/*
	kalman filter
	value  测量值
	R      测量协方差
	Q			 预测协方差
*/

float kalman(float value,float R,float Q)
{
	static float x_last=0,p_last=1;
	float x_mid,p_mid,x_now,p_now;
	float kg;
	
	x_mid=x_last;
	p_mid=p_last+Q;
	kg=p_mid/(p_mid+R);
	x_now=x_mid+kg*(value-x_mid);
	p_now=(1-kg)*p_mid;
	p_last=p_now;
	x_last=x_now;
	
	return x_now;
	
}

float kalman2(float value,float R,float Q)
{
	static float x_last=0,p_last=1;
	float x_mid,p_mid,x_now,p_now;
	float kg;
	
	x_mid=x_last;
	p_mid=p_last+Q;
	kg=p_mid/(p_mid+R);
	x_now=x_mid+kg*(value-x_mid);
	p_now=(1-kg)*p_mid;
	p_last=p_now;
	x_last=x_now;
	
	return x_now;
	
}
