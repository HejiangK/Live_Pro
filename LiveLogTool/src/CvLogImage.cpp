/*
 * CvLogImage.cpp
 *
 *  Created on: 2016-11-9
 *      Author: kean
 */

#include "CvLogImage.h"

CvLogImage::CvLogImage(int width, int height) {

	this->width = width;
	this->height = height;

	mat = Mat(height, width, CV_8UC4, Scalar(255, 255, 255));

	drawBackground();

}

void CvLogImage::drawBackground() {

	int w = this->width - padding * 2;
	int h = this->height - padding * 2;

	distance = w / 60;

	int row = w / distance;

	int col = h / distance;

	int i;

	for (i = 1; i < row; i++) {
		line(mat, Point(i * distance + padding, padding), Point(i * distance + padding, height - padding),
				Scalar(172, 172, 172));

	}

	for (i = 1; i < col; i++) {
		line(mat, Point(padding, i * distance + padding), Point(width - padding, padding + i * distance),
				Scalar(172, 172, 172));

	}


}

void CvLogImage::drawLines(Line *line, bool isMain) {
	list<cv::Point>::iterator it = line->points.begin();

	cv::Point *p = NULL;

	Scalar scalar;

	if (isMain)
		scalar = Scalar(0, 0, 255);
	else
		scalar = Scalar(0, 0, 0);

	while (it != line->points.end()) {
		(*it).x *= distance;
		(*it).y *= distance;
		(*it).y = this->height - padding * 2 - (*it).y;
		(*it).x += padding;
		(*it).y += padding;

		if (p == NULL)
			p = &(*it);
		else
			cv::line(mat, *p, *it, scalar, isMain?2:1);

		p = &(*it);

		it++;
	}

}

void CvLogImage::showImage() {
	imshow("test", mat);
}

void CvLogImage::save(const char *path) {

	imwrite(path, mat);
}

CvLogImage::~CvLogImage() {
	// TODO Auto-generated destructor stub
}

