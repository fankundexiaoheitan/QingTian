#ifndef	__USART_H__
#define	__USART_H__

extern unsigned char uart_state;
extern unsigned char uart_BUF[5];

//����������
void	USART_Init(void);	//���ڳ�ʼ������
void Uart_Send(unsigned char	date);	//���ڷ��ͺ���

#endif


