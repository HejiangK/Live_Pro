/*
 * CvLogTotal.cpp
 *
 *  Created on: 2016-11-10
 *      Author: kean
 */

#include "CvLogTotal.h"

CvLogTotal::CvLogTotal() {
	// TODO Auto-generated constructor stub
}

CvLogTotal::~CvLogTotal() {
	// TODO Auto-generated destructor stub
}

void CvLogTotal::addRtmpInfo(const RtmpInfo & info, const char *name) {

	TotalInfo *total = getTotalInfo(name, info.index);
	StreamInfo *streamInfo;

	if (total == NULL) {

		total = new TotalInfo();

		total->index = info.index;
		total->name = name;

		streamInfo = new StreamInfo();
		streamInfo->openTime = info.openTime;
		streamInfo->netConnectTime = info.netConnectTime;
		streamInfo->streamConnectTime = info.streamConnectTime;

		total->info.push_back(streamInfo);

		totalInfo.push_back(total);

	} else {
		if (getStreamInfo(info, total->info) == NULL) {
			streamInfo = new StreamInfo();
			streamInfo->openTime = info.openTime;
			streamInfo->netConnectTime = info.netConnectTime;
			streamInfo->streamConnectTime = info.streamConnectTime;

			total->info.push_back(streamInfo);

			totalInfo.push_back(total);
		}

	}

}

StreamInfo * CvLogTotal::getStreamInfo(const RtmpInfo & info,
		list<StreamInfo*> & streamInfo) {

	list<StreamInfo*>::iterator it = streamInfo.begin();

	while (it != streamInfo.end()) {
		if (info.openTime == (*it)->openTime
				&& info.netConnectTime == (*it)->netConnectTime
				&& info.streamConnectTime == (*it)->streamConnectTime)
			return *it;

		it++;
	}

	return NULL;

}

void CvLogTotal::totalCurrent() {

	list<TotalInfo*>::iterator totalIt;
	list<StreamInfo*>::iterator streamIt;
	TotalInfo *curTotalInfo;
	StreamInfo *curStreamInfo;

	totalIt = totalInfo.begin();

	SeverTotal sevTotal;

	sevTotal.num = 0;

	int num = 0;

	int64 netConnectTime = 0;
	int64 streamConnectTime = 0;

	int miss = 0;

	while (totalIt != totalInfo.end()) {
		curTotalInfo = *totalIt;

		streamIt = curTotalInfo->info.begin();

		miss += curTotalInfo->info.size() - 1;

		sevTotal.sevName = curTotalInfo->name;
		sevTotal.num++;

		while (streamIt != curTotalInfo->info.end()) {
			curStreamInfo = *streamIt;

			netConnectTime += curStreamInfo->netConnectTime
					- curStreamInfo->openTime;
			streamConnectTime += curStreamInfo->streamConnectTime
					- curStreamInfo->netConnectTime;

			num++;

			streamIt++;
		}

		totalIt++;
	}

	sevTotal.avaNetConnectTime = netConnectTime / num;
	sevTotal.avaStreamConnectTime = streamConnectTime / num;

	serverTotalList.push_back(sevTotal);


	cout << "**********************************************************"
			<< endl;
	cout << "sever : " << sevTotal.sevName << endl;
	cout << "nums : " << sevTotal.num << endl;
	cout << "netconnetcTime : " << sevTotal.avaNetConnectTime << endl;
	cout << "streamConnectTime : " << sevTotal.avaStreamConnectTime << endl;

	cout << "**********************************************************"
			<< endl;

}


TotalInfo * CvLogTotal::getTotalInfo(const char *name, int index) {

	list<TotalInfo*>::iterator it = totalInfo.begin();

	TotalInfo *info;

	while (it != totalInfo.end()) {
		info = *it;

		if (strcmp(info->name, name) == 0 && info->index == index)
			return info;

		it++;
	}

	return NULL;
}
