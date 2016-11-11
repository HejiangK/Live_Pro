//============================================================================
// Name        : Live_pro.cpp
// Author      : Kean
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================



#include "JobPool.h"
#include "WorkQueue.h"
#include "HttpClient.h"
#include "json/json.h"
#include "curl.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>

using namespace std;
using namespace Json;

int main(int argc, char *argv[])
{
	char *filePath = NULL, *url = NULL;
	const char *flag = " live=1";
	string timeUrl = "http://124.160.104.76:10007/timestamp_directly",response;
	int connectNums = 0,tb = 10;
	JobPool *jobPool = NULL;
	CHttpClient request;
	Reader reader;
	Value timeValue;

	filePath = argv[0];

	for(int i = 0; i < argc; i++)
	{
		if(strcmp(argv[i],"-url") == 0 && i + 1 < argc)
		{
			url = (char *)malloc(strlen(argv[i + i]) + strlen(flag) + 1);
			strcpy(url,argv[i+1]);
			strcat(url,flag);
		}

		if(strcmp(argv[i],"-path") == 0 && i + 1 < argc)
		{
			filePath = (char *)malloc(strlen(argv[i + i]));
			strcpy(filePath,argv[i+1]);
		}

		if(strcmp(argv[i],"-connect") == 0 && i + 1 < argc)
		{
			connectNums = atoi(argv[i + 1]);
		}

		if(strcmp(argv[i],"-tb") == 0 && i + 1 < argc)
		{
			tb = atoi(argv[i + 1]);
		}


	}

	if(request.Get(timeUrl,response) == CURLE_OK)
	{
		reader.parse(response,timeValue);

		RtmpJob::baseTime = timeValue["time"].asInt64();
		RtmpJob::loadTime = av_gettime_relative() / 1000;

		WorkQueue::getInstance()->createBuffer(tb);

		cout << "url is "<< url << ", sev time is " << RtmpJob::baseTime << endl;

		if(url != NULL && connectNums != 0)
		{
			jobPool = new JobPool(url,filePath,connectNums);
			jobPool->start();
			delete jobPool;
		}else
		{
			cout << "url is not free or connect nums is 0" << endl;
		}

	}else
	{

		cout << "load param error" <<endl;
	}






	return 0;
}
