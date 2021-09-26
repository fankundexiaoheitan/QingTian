#ifndef	__MY_IIC_H__
#define __MY_IIC_H__
#include "reg52.h"
typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;
//****************************************
// ����51��Ƭ���˿�
//****************************************
sbit    SCL=P3^6;			//IICʱ�����Ŷ���
sbit    SDA=P3^7;			//IIC�������Ŷ���

void Single_WriteI2C(uchar PC_Address,uchar REG_Address,uchar REG_data);		//��IIC�豸д��һ���ֽ�����
uchar Single_ReadI2C(uchar PC_Address,uchar REG_Address);		//��IIC�豸��ȡһ���ֽ�����


#endif



