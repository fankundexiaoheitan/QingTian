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
	USART_Init();	//串口初始化  波特率为9600
	InitMPU6050();	//mpu6050初始化
	OLED_Init(); //OLED初始化
	Timer0_Init();
	for(;;)	//主循环
	{ 
		OLED_ShowNum(0,0,(int)Angle,4);
		OLED_ShowNum(50,0,MPU6050_Data.Gyro_X+100,4);		//+100是为了减小x在静止状态下的X轴数据的漂移，使角度尽量保持不变
		Read_Mpu6050();
		if(MPU6050_Data.Gyro_X > 300 || MPU6050_Data.Gyro_X < -300)	//直接对从mpu6050读取出来的x轴上的角速度进行积分
			Angle = (int)(Angle + (MPU6050_Data.Gyro_X+100)*0.0035f);
	}
}


/*
和舵机的通信协议
'R' + '0'or'1'('0'说明角度为负，'1'说明角度为正) + 当前角度绝对值 + '\r' + '\n'
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
		if(Angle < 0)	//负角度
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



