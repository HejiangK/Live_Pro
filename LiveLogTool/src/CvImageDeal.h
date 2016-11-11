/*
 * CvImageDeal.h
 *
 *  Created on: 2016-11-9
 *      Author: kean
 */

#ifndef CVIMAGEDEAL_H_
#define CVIMAGEDEAL_H_

#include <opencv2/opencv.hpp>
#include <cstring>
#include <list>
#include <map>
#include <stdio.h>
#include <cmath>
#include "json/json.h"
#include "CvLogImage.h"

using namespace std;

struct RtmpInfo {

	int index;

	int64 curTime;

	int64 openTime;

	int64 netConnectTime;

	int64 streamConnectTime;

	int64 streamSize;

	int64 streamTime;
};


class CvImageDeal {

private:

	int64 minTime;

	const char *path;

	map<int64,CvLogImage*> images;

private:
	Line * getLine(list<Line*> & lines,int64 startTime,int index);

	void drawLines(list<Line*> & lines,bool isMain);

public:

	void draw(const char *name, list<RtmpInfo> & datas);

	void save();

public:
	CvImageDeal();
	CvImageDeal(const char *path);
	virtual ~CvImageDeal();
};

#endif /* CVIMAGEDEAL_H_ */
