/*
 * BasicJob.h
 *
 *  Created on: 2016年9月19日
 *      Author: genue
 */

#ifndef RTMPJOB_H_
#define RTMPJOB_H_

#include "RtmpInfo.h"
#include "JobThread.h"
#include "WorkQueue.h"
#include <iostream>

extern "C"
{
#include "libavformat/avformat.h"
#include "libavutil/log.h"
#include "libavutil/time.h"
#include "libavcodec/avcodec.h"
}


using namespace std;


class RtmpJob:public JobThread {

public:

	static int64_t baseTime;
	static int64_t loadTime;

	AVFormatContext *formatCtx;

	const char *fileName;
	int index;

	RtmpInfo rtmpInfo;
	RtmpInfo *saveInfo;

public:

	JOB_EXIT_CODE excute();

	static int64_t getLocalTime();

public:
	RtmpJob(const char *fileName,int index);
	virtual ~RtmpJob();
};

#endif /* RTMPJOB_H_ */
