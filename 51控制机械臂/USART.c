#include "USART.h"
#include "reg52.h"
/**************
串口初始化函数
***************/
void	USART_Init(void)
{
	EA = 1;
	TMOD |= 0X20;	//设置定时器1工作方式为8位自动重装载
	TH1	= 0XFD;		//设置串口波特率为9600
	TL1 = 0XFD;
	SCON |= 0X40;	//使用串口工作方式1
	PCON |= 0X00;	//波特率不加倍
	REN = 1;//开启串口接收
	ES = 1;	//开启串口中断
	TR1 = 1;		//开启定时器1
}

/*****************
串口发送函数
******************/
void Uart_Send(unsigned char	date)
{
	TI = 0;
	SBUF = date;
	while(!TI);
	TI = 0;
}


unsigned char uart_state = 0x00;
unsigned char uart_BUF[5] = {0};
unsigned char i = 0;
void	Uart_INT()	interrupt 4
{
	unsigned char a;
	a = SBUF;
	if(uart_state == 0x00)	//未接收到信息
	{
		uart_BUF[i++] = a;
		if(uart_BUF[0] != 'R')	//如果接收到到的一组数据第一个为R继续接收若不是则清空这一组数据
			i = 0;
		if(i >= 5)
		{
			i = 0;
			uart_state |= 0x80;
		}
	}
	RI = 0;
}

