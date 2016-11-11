/*
 * BasicJob.cpp
 *
 *  Created on: 2016年9月21日
 *      Author: genue
 */

#include "JobThread.h"

JobThread::JobThread() {
	this->isBreak = false;
	this->dead = false;
	this->threadHandle = 0;
}

JobThread::~JobThread() {

}

void JobThread::start()
{
	pthread_create(&threadHandle,NULL,onThreadHandle,this);
}

void * JobThread::onThreadHandle(void *args)
{
	JobThread * job = (JobThread *) args;

	if(job->excute() == JOB_EXCEPTION_EXIT)
		job->dead = true;

	return NULL;
}

void JobThread::wait()
{
	pthread_join(threadHandle,NULL);
}

void JobThread::finish()
{
	isBreak = true;
}

JOB_EXIT_CODE JobThread::excute()
{
	return JOB_NORMAL_EXIT;
}
