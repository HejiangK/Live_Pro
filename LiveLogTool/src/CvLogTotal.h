/*
 * CvLogTotal.h
 *
 *  Created on: 2016-11-10
 *      Author: kean
 */

#ifndef CVLOGTOTAL_H_
#define CVLOGTOTAL_H_

#include <list>
#include <stdlib.h>
#include "CvImageDeal.h"

using namespace std;

struct StreamInfo{

	int64 openTime;

	int64 netConnectTime;

	int64 streamConnectTime;

};

struct TotalInfo{

	const char *name;

	int index;

	list<StreamInfo*> info;

};

struct SeverTotal{

	int num;

	const char *sevName;

	int64 avaNetConnectTime;

	int64 avaStreamConnectTime;

};

class CvLogTotal {

private:

	list<TotalInfo*> totalInfo;

	list<SeverTotal> serverTotalList;

private:

	TotalInfo * getTotalInfo(const char *name,int index);

	StreamInfo * getStreamInfo(const RtmpInfo & info,list<StreamInfo*> & streamInfo);

public:

	void addRtmpInfo(const RtmpInfo & info,const char *name);

	void totalCurrent();

public:
	CvLogTotal();
	virtual ~CvLogTotal();
};

#endif /* CVLOGTOTAL_H_ */
