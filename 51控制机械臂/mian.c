#include "reg52.h"
#include "Timer.h"
#include "USART.h"

sbit pwm = P1^0;		//����ź�
unsigned int pwm_num = 14;	//��5~20��*100us����ߵ�ƽ��ռʱ��	������200*100us

void main(void)
{
	IP = 0X10;	//���ô���Ϊ�����ȼ�
	USART_Init();	//���ڳ�ʼ������  9600
	Timer0_Init();	//��ʱ��0��ʼ��
	for(;;)	//��ѭ��
	{
		if(uart_state&0X80)	//���յ���Ϣ
		{
			if(uart_BUF[0] == 'R')
			{
				if(uart_BUF[1] == '0')	//���Ƕ�
					pwm_num = 14 - (uart_BUF[2]/10);
				else if(uart_BUF[1] == '1')	//���Ƕ�
				{
					if(uart_BUF[2] >= 50)	//��������Ƕȴ���50����50����
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

void Timer0_INT()	interrupt 1	//��ʱ��0�ж�
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


