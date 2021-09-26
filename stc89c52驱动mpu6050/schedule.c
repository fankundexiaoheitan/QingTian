#include "schedule.h"
#include "oled.h"
static void Loop_1000Hz(void)	//1msִ��һ��
{
	
}

static void Loop_500Hz(void)	//2msִ��һ��
{	
	Read_Mpu6050();	//��ȡmpu6050����ֵ
	OLED_ShowNum(0,0,MPU6050_Data.Acc_X,4);
}

static void Loop_200Hz(void)	//5msִ��һ��
{
}

static void Loop_100Hz(void)	//10msִ��һ��
{
			
				
}


//����������ʱ���ϵķ���
//������ִͬ��Ƶ�ʵĸ��߳�
static sched_task_t sched_tasks[] =
{
	{Loop_1000Hz,1000,  0, 0},
	{Loop_500Hz , 500,  0, 0},
	{Loop_200Hz , 200,  0, 0},
	{Loop_100Hz , 100,  0, 0},
};

//�������鳤�ȣ��ж��߳�����
#define TASK_NUM (sizeof(sched_tasks)/sizeof(sched_task_t))

void Scheduler_Setup(void)//ʱ����ȳ�ʼ��
{
	unsigned char index = 0;
	//��ʼ�������
	for(index=0;index < TASK_NUM;index++)
	{
		//����ÿ���������ʱ������
		sched_tasks[index].interval_ticks = 1000/sched_tasks[index].rate_hz;
		//�������Ϊ1��Ҳ����1ms
		if(sched_tasks[index].interval_ticks < 1)
		{
			sched_tasks[index].interval_ticks = 1;
		}
	}
}

void Schedule_Run(void)	//������ѵ����
{
	unsigned char index = 0;
	//ѭ���ж������̣߳��Ƿ�Ӧ��ִ��

	
	for(index=0;index < TASK_NUM;index++)
	{
		//��ȡϵͳ��ǰʱ�䣬��λMS
		unsigned int tnow = sum_time;
		//�����жϣ������ǰʱ���ȥ��һ��ִ�е�ʱ�䣬���ڵ��ڸ��̵߳�ִ�����ڣ���ִ���߳�
		if(tnow - sched_tasks[index].last_run >= sched_tasks[index].interval_ticks)
		{
			
			//�����̵߳�ִ��ʱ�䣬������һ���ж�
			sched_tasks[index].last_run = tnow;
			//ִ���̺߳�����ʹ�õ��Ǻ���ָ��
			sched_tasks[index].task_func();

		}	 
	}
}

