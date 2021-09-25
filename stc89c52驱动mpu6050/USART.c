#include "USART.h"
#include "reg52.h"
/**************
串口初始化函数
***************/
void	USART_Init(void)
{
	TMOD |= 0X20;	//设置定时器1工作方式为8位自动重装载
	TH1	= 0XF7;		//设置串口波特率为9600
	TL1 = 0XF7;
	SCON |= 0X40;	//使用串口工作方式1
	PCON |= 0X00;	//波特率不加倍
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
