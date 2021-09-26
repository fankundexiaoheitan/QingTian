#include "schedule.h"
#include "oled.h"
static void Loop_1000Hz(void)	//1ms执行一次
{
	
}

static void Loop_500Hz(void)	//2ms执行一次
{	
	Read_Mpu6050();	//读取mpu6050的数值
	OLED_ShowNum(0,0,MPU6050_Data.Acc_X,4);
}

static void Loop_200Hz(void)	//5ms执行一次
{
}

static void Loop_100Hz(void)	//10ms执行一次
{
			
				
}


//各函数进行时间上的分配
//创建不同执行频率的各线程
static sched_task_t sched_tasks[] =
{
	{Loop_1000Hz,1000,  0, 0},
	{Loop_500Hz , 500,  0, 0},
	{Loop_200Hz , 200,  0, 0},
	{Loop_100Hz , 100,  0, 0},
};

//根据数组长度，判断线程数量
#define TASK_NUM (sizeof(sched_tasks)/sizeof(sched_task_t))

void Scheduler_Setup(void)//时间调度初始化
{
	unsigned char index = 0;
	//初始化任务表
	for(index=0;index < TASK_NUM;index++)
	{
		//计算每个任务的延时周期数
		sched_tasks[index].interval_ticks = 1000/sched_tasks[index].rate_hz;
		//最短周期为1，也就是1ms
		if(sched_tasks[index].interval_ticks < 1)
		{
			sched_tasks[index].interval_ticks = 1;
		}
	}
}

void Schedule_Run(void)	//核心轮训函数
{
	unsigned char index = 0;
	//循环判断所有线程，是否应该执行

	
	for(index=0;index < TASK_NUM;index++)
	{
		//获取系统当前时间，单位MS
		unsigned int tnow = sum_time;
		//进行判断，如果当前时间减去上一次执行的时间，大于等于该线程的执行周期，则执行线程
		if(tnow - sched_tasks[index].last_run >= sched_tasks[index].interval_ticks)
		{
			
			//更新线程的执行时间，用于下一次判断
			sched_tasks[index].last_run = tnow;
			//执行线程函数，使用的是函数指针
			sched_tasks[index].task_func();

		}	 
	}
}

