#pragma once

#include <pthread.h>

class TaskMutex {
public:
	TaskMutex();
	~TaskMutex();
	void lock();
	void unlock();
private:
	pthread_mutex_t m_mutex;
};
