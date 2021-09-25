#ifndef	__USART_H__
#define	__USART_H__

extern unsigned char uart_state;
extern unsigned char uart_BUF[5];

//函数声明区
void	USART_Init(void);	//串口初始化函数
void Uart_Send(unsigned char	date);	//串口发送函数

#endif


