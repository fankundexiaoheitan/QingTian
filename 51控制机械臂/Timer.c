#include "Timer.h"
#include "reg52.h"


void Timer0_Init(void)
{
	EA = 1;
	TMOD |= 0X01;		//设置定时器0为16位定时器
	TH0 = (65536-100)/256;			
	TL0 = (65536-100)%256;
	ET0 = 1;				//打开定时器0的中断
	TR0 = 1;				//打开定时器0
}



