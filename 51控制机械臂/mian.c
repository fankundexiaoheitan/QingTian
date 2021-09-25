#include "reg52.h"
#include "Timer.h"
#include "USART.h"

sbit pwm = P1^0;		//舵机信号
unsigned int pwm_num = 14;	//（5~20）*100us舵机高电平所占时间	总周期200*100us

void main(void)
{
	IP = 0X10;	//设置串口为高优先级
	USART_Init();	//串口初始化函数  9600
	Timer0_Init();	//定时器0初始化
	for(;;)	//主循环
	{
		if(uart_state&0X80)	//接收到信息
		{
			if(uart_BUF[0] == 'R')
			{
				if(uart_BUF[1] == '0')	//负角度
					pwm_num = 14 - (uart_BUF[2]/10);
				else if(uart_BUF[1] == '1')	//正角度
				{
					if(uart_BUF[2] >= 50)	//若正方向角度大于50度则按50度算
					{
						uart_BUF[2] = 50;
					}
					pwm_num = 14 + (uart_BUF[2]/10);
				}
				else;
			}
			uart_state = 0x00;
		}
	}
}

void Timer0_INT()	interrupt 1	//定时器0中断
{
	static unsigned int num = 0;
	TH0 = (65536-100)/256;			
	TL0 = (65536-100)%256;
	if(num < 200)
	{
		if(num < pwm_num)
			pwm = 1;
		else
			pwm = 0;
	}
	else
		num = 0;
	num += 1;
}


