/*
 * JobPool.cpp
 *
 *  Created on: 2016年9月20日
 *      Author: genue
 */

#include "JobPool.h"

JobPool::JobPool(const char *url,const char *filePath,int connectNums) {
	this->url = url;
	this->filePath = filePath;
	this->connectNums = connectNums;
	this->conJob = NULL;
	this->poster = NULL;

}

JobPool::~JobPool() {

	map<int,RtmpJob*>::iterator it = jobs.begin();

	while(it != jobs.end())
	{
		delete it->second;
		it++;
	}

	jobs.clear();


}
JOB_EXIT_CODE JobPool::excute()
{
	map<int,RtmpJob *>::iterator it;
	RtmpJob *tmp;

	for(;;)
	{
		if(isBreak)
			return JOB_NORMAL_EXIT;

		it = jobs.begin();

		while(it != jobs.end())
		{

			if(it->second->dead)
			{
				tmp = it->second;

				it->second = new RtmpJob(url,tmp->index);
				it->second->start();

				delete tmp;

				cout << "thread reset！" << it->first << "\t" << it->second->index << endl;

			}

			it ++;
		}

		sleep(5);

	}

	return JOB_NORMAL_EXIT;
}

void JobPool::start()
{
	av_register_all();
	avformat_network_init();
	av_log_set_level(AV_LOG_QUIET);

	for(int i = 0; i < connectNums; i ++)
	{
		RtmpJob *job = new RtmpJob(url,i);
		job->start();

		jobs[i] = job;
	}

	JobThread::start();

	conJob = new ControlJob();
	conJob->start();

	poster = new JobPoster(filePath);
	poster->start();

	conJob->wait();

	map<int,RtmpJob*>::iterator it = jobs.begin();

	while(it != jobs.end())
	{
		it->second->finish();
		it->second->wait();
		it++;
	}

	poster->finish();
	poster->wait();

	finish();
	wait();


}

