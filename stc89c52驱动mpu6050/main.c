#include "reg52.h"
#include "USART.h"
#include "MPU_6050.h"
#include "my_IIC.h"
#include "oled.h"
#include "Timer.h"
float Angle = 0;
unsigned int num = 1;
void main(void)
{
	USART_Init();	//���ڳ�ʼ��  ������Ϊ9600
	InitMPU6050();	//mpu6050��ʼ��
	OLED_Init(); //OLED��ʼ��
	Timer0_Init();
	for(;;)	//��ѭ��
	{ 
		OLED_ShowNum(0,0,(int)Angle,4);
		OLED_ShowNum(50,0,MPU6050_Data.Gyro_X+100,4);		//+100��Ϊ�˼�Сx�ھ�ֹ״̬�µ�X�����ݵ�Ư�ƣ�ʹ�ǶȾ������ֲ���
		Read_Mpu6050();
		if(MPU6050_Data.Gyro_X > 300 || MPU6050_Data.Gyro_X < -300)	//ֱ�ӶԴ�mpu6050��ȡ������x���ϵĽ��ٶȽ��л���
			Angle = (int)(Angle + (MPU6050_Data.Gyro_X+100)*0.0035f);
	}
}


/*
�Ͷ����ͨ��Э��
'R' + '0'or'1'('0'˵���Ƕ�Ϊ����'1'˵���Ƕ�Ϊ��) + ��ǰ�ǶȾ���ֵ + '\r' + '\n'
*/

void timer0() interrupt 1
{
	unsigned int send_data_ANGLE;
	num += 1;
	TH0 = 0X00;			
	TL0 = 0X01;
	if((num%10) == 0)
	{
		Uart_Send('R');
		if(Angle < 0)	//���Ƕ�
		{
			Uart_Send('0');
			send_data_ANGLE = -Angle;
		}
		else 
		{
			Uart_Send('1');
			send_data_ANGLE = Angle;
		}
		Uart_Send(send_data_ANGLE);
		Uart_Send('\r');
		Uart_Send('\n');
	}
}



