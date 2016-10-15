#include <iostream>
#include <unistd.h>
#include "TaskThread.h"

class TaskThreadMgr;

class TaskThreadMgr
{
public:
	TaskThreadMgr();
	~TaskThreadMgr();
	TaskThread *getThread1(){return task_th1;}
	TaskThread *getThread2(){return task_th2;}

private:
	TaskThread *task_th1;
 	TaskThread *task_th2;
};


class TaskA : public Task{
public:
	TaskA():Task(){}
	~TaskA(){}
	void run() {std::cout << "TaskA run" << std::endl;}
};


class TaskB : public Task{
public:
	TaskB():Task(){}
	~TaskB(){}
	void run() {std::cout << "TaskB run" << std::endl;}
};

class TaskC : public Task{
public:
	TaskC():Task(){}
	~TaskC(){}
	void run() {std::cout << "TaskC run" << std::endl;}
};

class TaskD : public Task{
public:
	TaskD():Task(){}
	~TaskD(){}
	void run() {std::cout << "TaskD run" << std::endl;}
};

class TaskE : public Task{
public:
	TaskE():Task(){}
	~TaskE(){}
	void run() {std::cout << "TaskE run" << std::endl;}
};

class TaskF : public Task{
public:
	TaskF(TaskThreadMgr *pThreadMgr):Task(),m_pThreadMgr(pThreadMgr)
	{
		m_fTask = new TaskA();
	}

	~TaskF()
	{
		delete m_fTask;
	}
	void run() 
	{
		std::cout << "TaskF run" << std::endl;
		m_pThreadMgr->getThread2()->post(m_fTask);
		std::cout << "TaskF run end" << std::endl;
	}
private:
	TaskThreadMgr *m_pThreadMgr;
	Task *m_fTask;
};
TaskThreadMgr::TaskThreadMgr()
{
	std::cout << "TaskThreadMgr() " << std::endl;
	task_th1 = new TaskThread("TaskThread_1");
	task_th2 = new TaskThread("TaskThread_2");
}

TaskThreadMgr::~TaskThreadMgr()
{
	std::cout << "~TaskThreadMgr() " << std::endl;
	delete task_th1;
	delete task_th2;
}


int main(int argc, char *argv[])
{
	std::cout << "main start" << std::endl;	
	TaskThreadMgr taskThreadMgr;

	Task *taskA = new TaskA();
	Task *taskB = new TaskB();
	Task *taskC = new TaskC();
	Task *taskD = new TaskD();
	Task *taskE = new TaskE();
	Task *taskF = new TaskF(&taskThreadMgr);

	while(true) {
		sleep(5);
		std::cout << "main thread pid " << getpid() << std::endl;
		taskThreadMgr.getThread1()->post(taskA);
		taskThreadMgr.getThread2()->post(taskB);
		taskThreadMgr.getThread2()->post(taskC);
		taskThreadMgr.getThread1()->post(taskD);
		taskThreadMgr.getThread1()->post(taskE);
		taskThreadMgr.getThread1()->post(taskF);
	}

	delete taskA;
	delete taskB;
	delete taskC;
	delete taskD;
	delete taskE;
	delete taskF;
}
