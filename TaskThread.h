#pragma once
#include <pthread.h>
#include <stdint.h>
#include <iostream>
#include <queue>
#include "TaskMutex.h"

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

	pthread_t m_pid;
	pid_t m_tid;

	std::queue<Task *> m_qTask; 
	std::queue<Task *> m_qDelayTask;

	TaskMutex m_TaskMutex;
	TaskMutex m_DelayTaskMutex;
};

