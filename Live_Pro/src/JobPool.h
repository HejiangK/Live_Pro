/*
 * JobPool.h
 *
 *  Created on: 2016年9月20日
 *      Author: genue
 */

#ifndef JOBPOOL_H_
#define JOBPOOL_H_

#include <map>
#include <unistd.h>
#include "ControlJob.h"
#include "RtmpJob.h"
#include "JobPoster.h"

class JobPool:public JobThread {

private:
	const char *url;
	const char *filePath;
	int connectNums;

	map<int,RtmpJob*> jobs;

	ControlJob *conJob;
	JobPoster *poster;

public:
	void start();
	JOB_EXIT_CODE excute();

public:
	JobPool(const char *url,const char *filePath,int connectNums);
	virtual ~JobPool();
};

#endif /* JOBPOOL_H_ */
