/*
 * CvFileReader.h
 *
 *  Created on: 2016-11-9
 *      Author: kean
 */

#ifndef CVFILEREADER_H_
#define CVFILEREADER_H_

#include <dirent.h>
#include <sys/stat.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <cstring>
#include <list>
#include <stdio.h>
#include <pthread.h>

using namespace std;

struct LogDirInfo {
	char * name;
	char * path;
	list<char*> logs;
};

class CvFileReader {

private:

	const char *path;

	pthread_t threadHandle;

	list<LogDirInfo*> logDirInfo;

public:

	void (*readCallBack)(const char *, list<const char *>);

	void (*readFinish)(void);

	void readLog();

private:

	void init();

	void initSubLogs(const char *path, list<char*> & logs);

	void readText(const char *name,const char *path,list<const char*> & logTxts);

protected:

	static void * onThreadFunc(void *arg);

public:

	void read(void (*readCallBack)(const char *, list<const char *>),void (*readFinish)(void));

public:
	CvFileReader();
	CvFileReader(const char *path);
	virtual ~CvFileReader();
};

#endif /* CVFILEREADER_H_ */
