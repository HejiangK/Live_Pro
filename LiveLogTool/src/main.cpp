//============================================================================
// Name        : LiveLogTool.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <list>
#include "CvLogImage.h"
#include "CvFileReader.h"
#include "json/json.h"
#include "CvImageDeal.h"

using namespace std;
using namespace Json;

struct TotalInfo {

	int totalNum;

	int missed;

	const char * sevName;

	int64 avaNetConnectTime;

	int64 avaStreamConnectTime;

};

CvImageDeal imageDeal;

CvFileReader fileReader;

list<TotalInfo> totalInfos;

void onReadFinish();

void onRead(const char *name, list<const char*> strs);

void countResult(list<RtmpInfo> & datas, const char *sevName);

int main(int argc, char *argv[]) {

	char *input, *output;

	for (int i = 0; i < argc; i++) {

		if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
			input = (char *) malloc(strlen(argv[i + i]));
			strcpy(input, argv[i + 1]);
		}

		if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
			output = (char *) malloc(strlen(argv[i + i]));
			strcpy(output, argv[i + 1]);
		}

	}

	imageDeal = CvImageDeal(output);

	fileReader = CvFileReader(input);

	fileReader.read(onRead, onReadFinish);

	return 0;
}

void onReadFinish() {

	imageDeal.save();

	list<TotalInfo>::iterator it = totalInfos.begin();

	TotalInfo info;
	TotalInfo curInfo;

	info.avaNetConnectTime = 0;
	info.avaStreamConnectTime = 0;
	info.missed = 0;
	info.totalNum = 0;

	while (it != totalInfos.end()) {

		curInfo = *it;

		if (strcmp(curInfo.sevName, "main") != 0) {

			info.avaNetConnectTime = (info.avaNetConnectTime * info.totalNum
					+ curInfo.avaNetConnectTime * curInfo.totalNum)
					/ (info.totalNum + curInfo.totalNum);

			info.avaStreamConnectTime = (info.avaStreamConnectTime
					* info.totalNum
					+ curInfo.avaStreamConnectTime * curInfo.totalNum)
					/ (info.totalNum + curInfo.totalNum);

			info.totalNum += curInfo.totalNum;

			info.missed += curInfo.missed;

		}

		it++;
	}

	cout << endl;

	cout << "*************************" << endl;
	cout << "all ava total" << endl;
	cout << "total nums is " << info.totalNum << endl;
	cout << "miss nums is " << info.missed << endl;
	cout << "avaNetConnectTime is " << info.avaNetConnectTime << endl;
	cout << "avaStreamConnectTime is " << info.avaStreamConnectTime << endl;
	cout << "******************" << endl;

	cout << endl;

}

void onRead(const char *name, list<const char*> strs) {
	list<const char*>::iterator it = strs.begin();

	const char *line;
	Reader reader;
	Value root;

	RtmpInfo info;

	list<RtmpInfo> curDatas;

	unsigned int i;

	while (it != strs.end()) {
		line = *it;

		reader.parse(line, root);

		for (i = 0; i < root.size(); i++) {

			info.curTime = root[i]["curTime"].asInt64();
			info.index = root[i]["index"].asInt();
			info.netConnectTime = root[i]["netConnectTime"].asInt64();
			info.openTime = root[i]["openTime"].asInt64();
			info.streamConnectTime = root[i]["streamConnectTime"].asInt64();
			info.streamSize = root[i]["streamSize"].asInt64();
			info.streamTime = root[i]["streamTime"].asInt64();

			curDatas.push_back(info);

		}

		root.clear();

		delete line;

		strs.erase(it++);
	}

	imageDeal.draw(name, curDatas);

	countResult(curDatas, name);

	curDatas.clear();

}

void countResult(list<RtmpInfo> & datas, const char *sevName) {

	list<RtmpInfo>::iterator it = datas.begin();

	typedef map<int64, RtmpInfo> rtmap;

	map<int, rtmap> totaled;

	map<int, rtmap>::iterator totalIt;

	TotalInfo totalInfo;

	totalInfo.avaNetConnectTime = 0;
	totalInfo.avaStreamConnectTime = 0;
	totalInfo.missed = 0;
	totalInfo.totalNum = 0;
	totalInfo.sevName = sevName;

	RtmpInfo curInfo;

	while (it != datas.end()) {

		curInfo = *it;

		totalIt = totaled.find(curInfo.index);

		if (totalIt == totaled.end()) {

			totaled[curInfo.index][curInfo.openTime] = curInfo;

			totalInfo.avaNetConnectTime = (totalInfo.totalNum
					* totalInfo.avaNetConnectTime + curInfo.netConnectTime
					- curInfo.openTime) / (totalInfo.totalNum + 1);

			totalInfo.avaStreamConnectTime = (totalInfo.totalNum
					* totalInfo.avaStreamConnectTime + curInfo.streamConnectTime
					- curInfo.netConnectTime) / (totalInfo.totalNum + 1);

			totalInfo.totalNum++;

		} else if (totalIt != totaled.end()
				&& (*totalIt).second.find(curInfo.openTime)
						== (*totalIt).second.end()) {

			totaled[curInfo.index][curInfo.openTime] = curInfo;

			totalInfo.missed++;

			totalInfo.avaNetConnectTime = (totalInfo.totalNum
					* totalInfo.avaNetConnectTime + curInfo.netConnectTime
					- curInfo.openTime) / (totalInfo.totalNum + 1);

			totalInfo.avaStreamConnectTime = (totalInfo.totalNum
					* totalInfo.avaStreamConnectTime + curInfo.streamConnectTime
					- curInfo.netConnectTime) / (totalInfo.totalNum + 1);

			totalInfo.totalNum++;
		}

		it++;
	}

	totaled.clear();

	totalInfos.push_back(totalInfo);

	cout << endl;

	cout << "*************************" << endl;
	cout << "server is " << totalInfo.sevName << endl;
	cout << "total nums is " << totalInfo.totalNum << endl;
	cout << "miss nums is " << totalInfo.missed << endl;
	cout << "avaNetConnectTime is " << totalInfo.avaNetConnectTime << endl;
	cout << "avaStreamConnectTime is " << totalInfo.avaStreamConnectTime
			<< endl;
	cout << "******************" << endl;

	cout << endl;

}

