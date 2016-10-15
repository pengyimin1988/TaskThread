#include "TaskTool.h"
#include "TaskThread.h"
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/syscall.h>

void *TaskThread::_TaskThread(void *param)
{

#ifdef SYS_gettid
	pid_t tid = syscall(SYS_gettid);
#else
#error "SYS_gettid unavailable on this system"
#endif

	printf("_TaskThread addr %d tid %d\n",_TaskThread,tid); 
	TaskThread *task_th = (TaskThread *)param;
	task_th->loop(tid);
}

TaskThread::TaskThread(std::string name)
{
//创建线程,先不管pthread_attr
	int ret;
	ret = pthread_create(&m_pid, NULL, &_TaskThread, this);
	if(ret < 0) {
		printf("Error. return code pthread_create %d \n",ret);
		exit(0);
	}
	pthread_setname_np(m_pid,name.c_str());

//暂时不设置mutex的属性,比如可重入性
	pthread_mutex_init(&m_TaskMutex, NULL);
	pthread_mutex_init(&m_DelayTaskMutex, NULL);
}

TaskThread::~TaskThread()
{
	pthread_cancel(m_pid);
	pthread_mutex_destroy(&m_TaskMutex);
	pthread_mutex_destroy(&m_DelayTaskMutex);
}

void TaskThread::loop(pid_t tid)
{
	while(true) {
		pthread_mutex_lock(&m_TaskMutex);
		while(!m_qTask.empty()){
			//std::queue<Task*>::iterator it;
			//for(it = m_qTask.begin(); it != m_qTask.end(); it++) 
			//	(*it)->run();  //run函数里面改变了m_qTask怎么办
			Task *task = m_qTask.front();
			m_qTask.pop();
			printf("thread tid %d execute task \n",tid);
			task->run();
		}
		pthread_mutex_unlock(&m_TaskMutex);
		
	}
}

void TaskThread::post(Task *task)
{
	pthread_mutex_lock(&m_TaskMutex);
	m_qTask.push(task);
	pthread_mutex_unlock(&m_TaskMutex);
}

void TaskThread::post(Task *task,uint32_t delay)
{
	task->m_time = TaskTool::getCurrTime();
	task->m_delay = delay;

	pthread_mutex_lock(&m_DelayTaskMutex);
	m_qDelayTask.push(task);
	pthread_mutex_unlock(&m_DelayTaskMutex);
	m_qDelayTask.push(task);
}

Task::Task()
{
}

Task::~Task()
{
}
