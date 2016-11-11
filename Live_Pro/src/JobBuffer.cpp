/*
 * JobBuffer.cpp
 *
 *  Created on: 2016年9月23日
 *      Author: kean
 */

#include "JobBuffer.h"
#include <iostream>
#include <list>

using namespace std;

JobBuffer::JobBuffer(int index) {

	this->index = index;

	pthread_mutex_init(&mutex,NULL);

}

JobBuffer::~JobBuffer() {
	pthread_mutex_destroy(&mutex);

	list<RtmpInfo *>::iterator it = area.begin();

		while(it != area.end())
		{
			av_free(*it);
			it ++;
		}

}

void JobBuffer::addToBuffer(RtmpInfo * data)
{
	area.push_back(data);
}

void JobBuffer::getFromBuffer(list<RtmpInfo *> & lists)
{
	list<RtmpInfo *>::iterator it = area.begin();

	while(it != area.end())
	{
		lists.push_back(*it);
		it ++;
	}

	area.clear();

}

bool JobBuffer::tryLock()
{
	return pthread_mutex_trylock(&mutex) == 0;
}

bool JobBuffer::release()
{
	pthread_mutex_unlock(&mutex);

	return true;
}
