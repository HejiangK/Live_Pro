/*
 * WorkQueue.h
 *
 *  Created on: 2016年9月22日
 *      Author: kean
 */

#ifndef WORKQUEUE_H_
#define WORKQUEUE_H_


#include "RtmpInfo.h"
#include <list>
#include "JobBuffer.h"

using namespace std;


class WorkQueue {

private:
	static WorkQueue *instance;

private:

	list<JobBuffer *> buffers;

public:

	/**
	 * 创建流信息缓冲区
	 * **/
	void createBuffer(int num);

	/**
	 * 添加一个连接信息到队列
	 * @param info 队列信息
	 * **/
	bool addInfo(RtmpInfo *cInfo);

	/**
	 * 获取连接信息
	 * **/
	bool getInfo(list<RtmpInfo *> & lists);

	/**
	 * 获取单列
	 * **/
	static WorkQueue * getInstance();

	/**
	 * 清理单利
	 * **/
	static void disponse();

private:
	WorkQueue();

public:

	virtual ~WorkQueue();
};

#endif /* WORKQUEUE_H_ */
