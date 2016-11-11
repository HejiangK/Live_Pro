/*
 * ControlJob.h
 *
 *  Created on: 2016年9月21日
 *      Author: genue
 */

#ifndef CONTROLJOB_H_
#define CONTROLJOB_H_

#include "JobThread.h"

class ControlJob : public JobThread {

public:
	JOB_EXIT_CODE excute();

public:
	ControlJob();
	virtual ~ControlJob();
};

#endif /* CONTROLJOB_H_ */
