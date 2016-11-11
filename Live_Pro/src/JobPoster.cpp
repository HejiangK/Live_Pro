/*
 * JobPoster.cpp
 *
 *  Created on: 2016年9月25日
 *      Author: kean
 */

#include "JobPoster.h"
#include "json/writer.h"
#include "json/value.h"
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



JobPoster::JobPoster(const char *filePath) {
	// TODO Auto-generated constructor stub

	this->filePath = filePath;

	char name[1024];

	struct timespec sp;

	clock_gettime(CLOCK_THREAD_CPUTIME_ID,&sp);
	srand(sp.tv_nsec);

	int num = rand();
	sprintf(name,"%d",num);

	strcat(name,".txt");

	this->logUrl = (char *)av_malloc(strlen(filePath) + strlen(name) + 1);

	strcpy(this->logUrl,filePath);
	strcat(this->logUrl,"/");
	strcat(this->logUrl,name);


}

JobPoster::~JobPoster() {
	// TODO Auto-generated destructor stub

	av_free(this->logUrl);

}

void JobPoster::save(const char *txt)
{
	FILE * file = fopen(this->logUrl,"ab+");

	fwrite(txt,sizeof(char),strlen(txt),file);

	fclose(file);

}

JOB_EXIT_CODE JobPoster::excute()
{
	using namespace Json;

	WorkQueue * queue = WorkQueue::getInstance();
	list<RtmpInfo *>::iterator it;

	list<RtmpInfo *> lists;
	FastWriter r;

	while(!isBreak)
	{
		queue->getInfo(lists);

		if(lists.size() > 0)
		{
			Value root;
			Value node;
			RtmpInfo *info;

			it = lists.begin();

			while(it != lists.end())
			{
				info = (RtmpInfo *)(*it);
				node["index"] = info->index;
				node["netConnectTime"] = info->netConnectTime;
				node["openTime"] = info->openTime;
				node["streamConnectTime"] = info->streamConnectTime;
				node["streamSize"] = info->streamSize;
				node["streamTime"] = info->streamTime;
				node["curTime"] = info->curTime;

				root.append(node);

				delete info;

				lists.erase(it++);
			}

			save(r.write(root).c_str());

			root.clear();
		}

		sleep(0.5);
	}



	return JOB_NORMAL_EXIT;
}


