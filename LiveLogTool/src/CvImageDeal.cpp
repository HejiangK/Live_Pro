/*
 * CvImageDeal.cpp
 *
 *  Created on: 2016-11-9
 *      Author: kean
 */

#include "CvImageDeal.h"

CvImageDeal::CvImageDeal() {
	minTime = -1;
	this->path = NULL;
}

CvImageDeal::CvImageDeal(const char *path) {
	// TODO Auto-generated constructor stub
	this->path = path;

	minTime = -1;
}

CvImageDeal::~CvImageDeal() {
	// TODO Auto-generated destructor stub
}

void CvImageDeal::draw(const char *name, list<RtmpInfo> & datas) {

	list<RtmpInfo>::iterator it = datas.begin();
	RtmpInfo info;

	list<Line*> lines;
	Line *line;

	double index;

	while (it != datas.end()) {

		info = *it;

		if (strcmp(name, "main") == 0 && minTime == -1) {
			minTime = info.curTime;

			line = new Line();

			line->index = info.index;
			line->name = name;
			line->startTime = minTime;
			line->endTime = minTime + 60000;
			lines.push_back(line);

		}

		line = getLine(lines, info.curTime,info.index);

		if (line == NULL) {
			line = new Line();

			index = floor((double) (info.curTime - minTime) / 60000);

			line->index = info.index;
			line->name = name;
			line->startTime = minTime + index * 60000;
			line->endTime = minTime + (index + 1) * 60000;

			lines.push_back(line);
		}

		line->points.push_back(
				cv::Point(
						(info.streamConnectTime + info.streamTime
								- line->startTime) / 1000,
						(info.curTime - line->startTime) / 1000));

		it++;
	}

	drawLines(lines,strcmp(name,"main") == 0);


}

void CvImageDeal::drawLines(list<Line*> & lines,bool isMain) {
	list<Line*>::iterator it = lines.begin();

	Line *line;

	while (it != lines.end()) {

		line = *it;

		if (!images[line->startTime]) {
			images[line->startTime] = new CvLogImage(600, 600);
		}

		images[line->startTime]->drawLines(line,isMain);

		delete line;
		lines.erase(it++);
	}

}

Line * CvImageDeal::getLine(list<Line*> & lines, int64 startTime,int index) {
	list<Line*>::iterator it = lines.begin();

	Line* line;

	while (it != lines.end()) {
		line = *it;

		if (line->startTime <= startTime && line->endTime > startTime && index == line->index)
			return line;

		it++;

	}

	return NULL;

}

void CvImageDeal::save() {
	map<int64, CvLogImage*>::iterator it = images.begin();

	CvLogImage *image;

	char path[256];

	while (it != images.end()) {

		image = (*it).second;

		sprintf(path, "%s%s%d%s", this->path, "/",
				((*it).first - minTime) / 60000, ".bmp");

		image->save(path);

		it++;
	}

}

