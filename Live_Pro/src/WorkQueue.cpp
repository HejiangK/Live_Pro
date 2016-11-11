/*
 * WorkQueue.cpp
 *
 *  Created on: 2016年9月22日
 *      Author: kean
 */

#include "WorkQueue.h"


WorkQueue* WorkQueue::instance = NULL;

WorkQueue::WorkQueue(){

}

WorkQueue::~WorkQueue() {

	list<JobBuffer*>::iterator it = buffers.begin();

	while(it != buffers.end())
	{
		delete *it;
		buffers.erase(it++);
	}

}

WorkQueue * WorkQueue::getInstance()
{
	if(instance == NULL)
		instance = new WorkQueue();

	return instance;
}

void WorkQueue::disponse()
{
	if(WorkQueue::instance)
			delete WorkQueue::instance;
}

void WorkQueue::createBuffer(int num)
{
	for(int i = 0; i < num; i ++)
	{
		buffers.push_back(new JobBuffer(i));
	}


}


bool WorkQueue::addInfo(RtmpInfo *cInfo)
{
	list<JobBuffer *>::iterator it = buffers.begin();

	while(it != buffers.end())
	{

		if((*it)->tryLock())
		{
			(*it)->addToBuffer(cInfo);
			(*it)->release();
			return true;
		}

		it ++;
	}


	return false;

}

bool WorkQueue::getInfo(list<RtmpInfo *> & lists)
{
	list<JobBuffer *>::iterator it = buffers.begin();

		while(it != buffers.end())
		{
			if((*it)->tryLock())
			{
				(*it)->getFromBuffer(lists);
				(*it)->release();
			}

			it ++;
		}

		return true;
}
