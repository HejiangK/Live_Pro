/*
 * CvLogImage.h
 *
 *  Created on: 2016-11-9
 *      Author: kean
 */

#ifndef CVLOGIMAGE_H_
#define CVLOGIMAGE_H_

#include <opencv2/opencv.hpp>
#include <list>


using namespace cv;
using namespace std;

struct Line {

	int index;

	const char *name;

	int64 startTime;

	int64 endTime;

	list<cv::Point> points;
};


class CvLogImage {

private:

	Mat mat;

public:

	static const int padding = 20;

	int distance;

	int width;

	int height;

private:

	void drawBackground();

public:

	void drawLines(Line *line,bool isMain);

	void showImage();

	void save(const char *path);

public:

	CvLogImage(int width,int height);

	virtual ~CvLogImage();
};

#endif /* CVLOGIMAGE_H_ */
