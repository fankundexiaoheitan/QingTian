#include "USART.h"
#include "reg52.h"
/**************
���ڳ�ʼ������
***************/
void	USART_Init(void)
{
	TMOD |= 0X20;	//���ö�ʱ��1������ʽΪ8λ�Զ���װ��
	TH1	= 0XF7;		//���ô��ڲ�����Ϊ9600
	TL1 = 0XF7;
	SCON |= 0X40;	//ʹ�ô��ڹ�����ʽ1
	PCON |= 0X00;	//�����ʲ��ӱ�
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
