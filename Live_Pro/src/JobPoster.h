/*
 * JobPoster.h
 *
 *  Created on: 2016年9月25日
 *      Author: kean
 */

#ifndef JOBPOSTER_H_
#define JOBPOSTER_H_

#include "JobThread.h"
#include "RtmpInfo.h"
#include "WorkQueue.h"
#include <map>
#include <unistd.h>


class JobPoster:public JobThread {

private:
	const char *filePath;
	char * logUrl;

private:
	void save(const char *txt);

public:
	JOB_EXIT_CODE excute();

public:
	JobPoster(const char *filePath);
	virtual ~JobPoster();
};

#endif /* JOBPOSTER_H_ */
