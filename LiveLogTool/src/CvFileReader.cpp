/*
 * CvFileReader.cpp
 *
 *  Created on: 2016-11-9
 *      Author: kean
 */

#include "CvFileReader.h"

CvFileReader::CvFileReader() {

	this->path = NULL;
	this->readCallBack = NULL;

}

CvFileReader::CvFileReader(const char *path) {
	// TODO Auto-generated constructor stub
	this->path = path;
	this->readCallBack = NULL;

	init();
}

CvFileReader::~CvFileReader() {
	// TODO Auto-generated destructor stub
}

void CvFileReader::init() {
	DIR *dir;
	struct dirent *entry;
	struct stat statbuf;

	if ((dir = opendir(path)) == NULL) {
		cout << path << " is not exist" << endl;

		return;
	}

	chdir(path);

	while ((entry = readdir(dir)) != NULL) {
		lstat(entry->d_name, &statbuf);

		if (S_ISDIR(statbuf.st_mode)) {
			if (strcmp(entry->d_name, ".") == 0
					|| strcmp(entry->d_name, "..") == 0) {
				continue;
			}

			LogDirInfo *info = new LogDirInfo();

			info->name = new char[strlen(entry->d_name)];
			strcpy(info->name, entry->d_name);

			info->path = new char[256];

			strcpy(info->path, path);
			strcat(info->path, "/");
			strcat(info->path, info->name);

			initSubLogs(info->path, info->logs);

			if (strcmp(info->name, "main") == 0)
				logDirInfo.push_front(info);
			else
				logDirInfo.push_back(info);

		}

	}

	chdir("..");

	closedir(dir);

}

void CvFileReader::initSubLogs(const char *path, list<char *> & logs) {

	DIR *dir;
	struct dirent *entry;

	if ((dir = opendir(path)) == NULL) {
		cout << path << " is not exist" << endl;

		return;
	}

	while ((entry = readdir(dir)) != NULL) {

		if (strcmp(entry->d_name, ".") == 0
				|| strcmp(entry->d_name, "..") == 0) {
			continue;
		}

		if (entry->d_type == 4) {

			char p[256] = { 0 };

			sprintf(p, "%s%s%s", path, "/", entry->d_name);

			initSubLogs(p, logs);

		} else if (entry->d_type == 8) {
			char *logPath = new char[256];
			sprintf(logPath, "%s%s%s", path, "//", entry->d_name);

			logs.push_back(logPath);

		}

	}

	closedir(dir);

}

void CvFileReader::read(void (*readCallBack)(const char*, list<const char*>),
		void (*readFinish)(void)) {
	this->readCallBack = readCallBack;
	this->readFinish = readFinish;

	pthread_create(&threadHandle, NULL, onThreadFunc, this);
	pthread_join(threadHandle, NULL);
}

void * CvFileReader::onThreadFunc(void *arg) {

	((CvFileReader*) arg)->readLog();

	return NULL;
}

void CvFileReader::readLog() {

	list<LogDirInfo*>::iterator it = logDirInfo.begin();
	list<char*>::iterator logIt;
	LogDirInfo *curInfo;

	while (it != logDirInfo.end()) {
		curInfo = *it;

		logIt = curInfo->logs.begin();

		while (logIt != curInfo->logs.end()) {

			list<const char*> logTxts;

			readText(curInfo->name, *logIt, logTxts);

			logIt++;
		}

		it++;
	}

	readFinish();

}

void CvFileReader::readText(const char *name, const char *path,
		list<const char*> & logTxts) {

	char *line = NULL;
	size_t len = 0;

	FILE *file = fopen(path, "r");

	while (getline(&line, &len, file) != -1) {
		logTxts.push_back(line);

		line = NULL;
	}

	readCallBack(name, logTxts);

	fclose(file);

}

