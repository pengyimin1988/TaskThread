#include "TaskTool.h"
#include "TaskThread.h"
#include "TaskMutex.h"
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

	printf("_TaskThread addr %p tid %x \n",_TaskThread,tid); 
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
}

TaskThread::~TaskThread()
{
	pthread_cancel(m_pid);
}

void TaskThread::loop(pid_t tid)
{
	m_tid = tid;	
	while(true) {
		m_TaskMutex.lock();
		while(!m_qTask.empty()){
			//std::queue<Task*>::iterator it;
			//for(it = m_qTask.begin(); it != m_qTask.end(); it++) 
			//	(*it)->run();  //run函数里面改变了m_qTask怎么办
			Task *task = m_qTask.front();
			m_qTask.pop();
			printf("thread tid %d execute task \n",m_tid);
			task->run();
		}
		m_TaskMutex.unlock();
		
	}
}

void TaskThread::post(Task *task)
{
	m_TaskMutex.lock();
	m_qTask.push(task);
	m_TaskMutex.unlock();
}

void TaskThread::post(Task *task,uint32_t delay)
{
	task->m_time = TaskTool::getCurrTime();
	task->m_delay = delay;

	m_DelayTaskMutex.lock();
	m_qDelayTask.push(task);
	m_DelayTaskMutex.unlock();
}

Task::Task()
{
}

Task::~Task()
{
}
