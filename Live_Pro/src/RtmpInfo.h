/*
 * RtmpInfo.h
 *
 *  Created on: 2016-10-17
 *      Author: kean
 */

#ifndef RTMPINFO_H_
#define RTMPINFO_H_

extern "C"
{
#include "libavformat/avformat.h"
#include "libavutil/log.h"
#include "libavutil/time.h"
}

class RtmpInfo {

public:
	int64_t index;

	int64_t openTime;

	int64_t netConnectTime;

	int64_t streamConnectTime;

	int64_t streamSize;

	int64_t streamTime;

	int64_t curTime;


public:
	RtmpInfo();
	virtual ~RtmpInfo();
};

#endif /* RTMPINFO_H_ */
