/*
 * BasicJob.cpp
 *
 *  Created on: 2016年9月19日
 *      Author: genue
 */

#include "RtmpJob.h"

extern "C"
{
#include "libavformat/avformat.h"
#include "libavutil/log.h"
#include "libavutil/time.h"
}

int64_t RtmpJob::baseTime = 0;
int64_t RtmpJob::loadTime = 0;

RtmpJob::RtmpJob(const char *fileName,int index) {
	this->fileName = fileName;
	this->index = index;

	this->formatCtx = NULL;

	this->isBreak = false;
	this->saveInfo = NULL;

	rtmpInfo.netConnectTime = 0;
	rtmpInfo.openTime = 0;
	rtmpInfo.streamConnectTime = 0;
	rtmpInfo.streamTime = 0;
	rtmpInfo.streamSize = 0;
	rtmpInfo.index = index;
}

RtmpJob::~RtmpJob() {

	avformat_close_input(&formatCtx);
	avformat_free_context(formatCtx);

	formatCtx = NULL;

}

int64_t RtmpJob::getLocalTime()
{
	return av_gettime_relative() / 1000 - loadTime + baseTime;
}

/**
 * 执行job任务
 * 每个job实现模拟拉取一条rtmp流
 * **/
JOB_EXIT_CODE RtmpJob::excute()
{
	int64_t lastWorkTime = 0;
	int64_t tmpTime = 0;

	AVPacket *pkt = (AVPacket*)av_malloc(sizeof(AVPacket));

	rtmpInfo.openTime = getLocalTime();

	formatCtx = avformat_alloc_context();

	if(avformat_open_input(&formatCtx,fileName,NULL,NULL)< 0)
		goto fail;

	rtmpInfo.netConnectTime = getLocalTime();

	if(avformat_find_stream_info(formatCtx,NULL) < 0)
		goto fail;

	while(av_read_frame(formatCtx,pkt) >= 0)
	{
		if(rtmpInfo.streamConnectTime == 0)
			rtmpInfo.streamConnectTime = getLocalTime();

		rtmpInfo.streamSize += pkt->size;

		rtmpInfo.streamTime =  1000 * ((double)formatCtx->streams[pkt->stream_index]->time_base.num /
									formatCtx->streams[pkt->stream_index]->time_base.den * pkt->pts);
		rtmpInfo.curTime = getLocalTime();

		tmpTime = getLocalTime();

		if(tmpTime - lastWorkTime > 1000 * 2)
		{
			lastWorkTime = tmpTime;

			saveInfo = new RtmpInfo(rtmpInfo);

			if(!WorkQueue::getInstance()->addInfo(saveInfo))
			{
				delete saveInfo;
			}

		}
		av_packet_unref(pkt);

		if(isBreak)
			goto success;

	}


fail:

	av_free(pkt);

	cout << "connect error " << index << endl;
	return JOB_EXCEPTION_EXIT;


success:

	av_free(pkt);

	cout << "thread " << index << " released" << endl;
	return JOB_NORMAL_EXIT;


}

