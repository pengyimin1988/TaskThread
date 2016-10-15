#include "TaskMutex.h"

TaskMutex::TaskMutex()
{
	pthread_mutexattr_t m_attr;

	//set recrusive type
	pthread_mutexattr_init(&m_attr);
	pthread_mutexattr_settype(&m_attr, PTHREAD_MUTEX_RECURSIVE);

	pthread_mutex_init(&m_mutex, &m_attr);
}

TaskMutex::~TaskMutex()
{
	pthread_mutex_destroy(&m_mutex);
}

void TaskMutex::lock()
{
	pthread_mutex_lock(&m_mutex);
}

void TaskMutex::unlock()
{
	pthread_mutex_unlock(&m_mutex);
}
