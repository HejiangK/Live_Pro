/*
 * JobBuffer.h
 *
 *  Created on: 2016年9月23日
 *      Author: kean
 */

#ifndef JOBBUFFER_H_
#define JOBBUFFER_H_

#include "RtmpInfo.h"
#include <pthread.h>
#include <iostream>
#include <list>
using namespace std;

class JobBuffer {

private:
	pthread_mutex_t mutex;

	list<RtmpInfo *> area;

public:
	int index;

public:

	bool tryLock();

	bool release();

	void addToBuffer(RtmpInfo *data);

	void getFromBuffer(list<RtmpInfo *> & lists);

public:
	JobBuffer(int index);
	virtual ~JobBuffer();
};

#endif /* JOBBUFFER_H_ */
