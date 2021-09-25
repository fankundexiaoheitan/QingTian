#include "Timer.h"
#include "reg52.h"


void Timer0_Init(void)
{
	EA = 1;
	TMOD |= 0X01;		//���ö�ʱ��0Ϊ16λ��ʱ��
	TH0 = (65536-100)/256;			
	TL0 = (65536-100)%256;
	ET0 = 1;				//�򿪶�ʱ��0���ж�
	TR0 = 1;				//�򿪶�ʱ��0
}



