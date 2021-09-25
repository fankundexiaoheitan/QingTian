#include "USART.h"
#include "reg52.h"
/**************
���ڳ�ʼ������
***************/
void	USART_Init(void)
{
	EA = 1;
	TMOD |= 0X20;	//���ö�ʱ��1������ʽΪ8λ�Զ���װ��
	TH1	= 0XFD;		//���ô��ڲ�����Ϊ9600
	TL1 = 0XFD;
	SCON |= 0X40;	//ʹ�ô��ڹ�����ʽ1
	PCON |= 0X00;	//�����ʲ��ӱ�
	REN = 1;//�������ڽ���
	ES = 1;	//���������ж�
	TR1 = 1;		//������ʱ��1
}

/*****************
���ڷ��ͺ���
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
	if(uart_state == 0x00)	//δ���յ���Ϣ
	{
		uart_BUF[i++] = a;
		if(uart_BUF[0] != 'R')	//������յ�����һ�����ݵ�һ��ΪR���������������������һ������
			i = 0;
		if(i >= 5)
		{
			i = 0;
			uart_state |= 0x80;
		}
	}
	RI = 0;
}

