#ifndef __SCHEDULE_H__
#define __SCHEDULE_H__
#include "Timer.h"
#include "MPU_6050.h"


//时间调度结构体
typedef struct
{
	void(*task_func)(void);
	unsigned short int rate_hz;
	unsigned short int interval_ticks;
	unsigned int last_run;
}sched_task_t;

//函数声明区
void Scheduler_Setup(void);
void Scheduler_Run(void);//核心循环

#endif


