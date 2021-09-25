#ifndef __SCHEDULE_H__
#define __SCHEDULE_H__
#include "Timer.h"
#include "MPU_6050.h"


//ʱ����Ƚṹ��
typedef struct
{
	void(*task_func)(void);
	unsigned short int rate_hz;
	unsigned short int interval_ticks;
	unsigned int last_run;
}sched_task_t;

//����������
void Scheduler_Setup(void);
void Scheduler_Run(void);//����ѭ��

#endif


