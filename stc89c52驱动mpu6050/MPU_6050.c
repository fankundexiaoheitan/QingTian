#include "MPU_6050.h"
#include "my_IIC.h"

//******************************************************************************************************
//初始化MPU6050
//******************************************************************************************************
void InitMPU6050()
{
	Single_WriteI2C(SlaveAddress,PWR_MGMT_1, 0x00);	//解除休眠状态
	Single_WriteI2C(SlaveAddress,SMPLRT_DIV, 0x07);	//设置陀螺仪采样率为125hz
	Single_WriteI2C(SlaveAddress,CONFIG, 0x06);			//设置低通滤波频率为5hz
	Single_WriteI2C(SlaveAddress,GYRO_CONFIG, 0x18);
	Single_WriteI2C(SlaveAddress,ACCEL_CONFIG, 0x01);
}

/******************
读取mpu6050数据
*****************/
_MPU6050_Data MPU6050_Data;
void Read_Mpu6050(void)
{
	unsigned char buffer[14];
	unsigned char i;
	for(i = 0;i < 14;i++)
	{
		buffer[i] = Single_ReadI2C(SlaveAddress,ACCEL_XOUT_H+i);	//读取mpu6050中的数据
	}
	MPU6050_Data.Acc_X = buffer[0]<<8 | buffer[1];
	MPU6050_Data.Acc_Y = buffer[2]<<8 | buffer[3];
	MPU6050_Data.Acc_Z = buffer[4]<<8 | buffer[5];
	MPU6050_Data.Temp  = (21 + (buffer[6]<<8 | buffer[7]) / 333.87);
	MPU6050_Data.Gyro_X = buffer[8]<<8 | buffer[9];
	MPU6050_Data.Gyro_Y = buffer[10]<<8 | buffer[11];
	MPU6050_Data.Gyro_Z = buffer[12]<<12 | buffer[13];

}
