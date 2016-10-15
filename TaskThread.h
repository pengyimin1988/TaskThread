#pragma once
#include "pthread.h"
#include <stdint.h>
#include <iostream>
#include <queue>

class TaskThread;

class Task{
friend TaskThread;
public:
	Task();
	virtual ~Task();
	virtual void run() = 0;
private:
	uint32_t m_time;
	uint32_t m_delay;
};

class TaskThread {

public:
	TaskThread(std::string name);
	virtual ~TaskThread();
	void post(Task *task);
	void post(Task *task, uint32_t delay);
	void loop(pid_t tid);
	
private:

	static void *_TaskThread(void *param);
	std::queue<Task *> m_qTask; 
	std::queue<Task *> m_qDelayTask;
	pthread_t m_pid;
	pthread_mutex_t m_TaskMutex;
	pthread_mutex_t m_DelayTaskMutex;
};

