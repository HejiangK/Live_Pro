/*
 * BasicJob.h
 *
 *  Created on: 2016年9月21日
 *      Author: genue
 */

#ifndef JOBTHREAD_H_
#define JOBTHREAD_H_

#include <pthread.h>
#include <iostream>

using namespace std;

enum JOB_EXIT_CODE
{
	/**
	 * 正常退出，一般是break之后退出
	 * **/
	JOB_NORMAL_EXIT,

	/**
	 * 异常退出，一般是流断了之后退出
	 * **/
	JOB_EXCEPTION_EXIT

};


class JobThread {

protected:
	pthread_t threadHandle;
	bool isBreak;

public:
	bool dead;

protected:
	static void * onThreadHandle(void *arg);


public:

	void start();

	void wait();

	void finish();

	virtual JOB_EXIT_CODE excute();

public:
	JobThread();
	virtual ~JobThread();
};

#endif /* JOBTHREAD_H_ */
