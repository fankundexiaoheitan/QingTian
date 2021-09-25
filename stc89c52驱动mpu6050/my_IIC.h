#ifndef	__MY_IIC_H__
#define __MY_IIC_H__
#include "reg52.h"
typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;
//****************************************
// 定义51单片机端口
//****************************************
sbit    SCL=P3^6;			//IIC时钟引脚定义
sbit    SDA=P3^7;			//IIC数据引脚定义

void Single_WriteI2C(uchar PC_Address,uchar REG_Address,uchar REG_data);		//向IIC设备写入一个字节数据
uchar Single_ReadI2C(uchar PC_Address,uchar REG_Address);		//从IIC设备读取一个字节数据


#endif



