/*
 * ControlJob.cpp
 *
 *  Created on: 2016年9月21日
 *      Author: genue
 */

#include "ControlJob.h"
#include <stdio.h>
#include <cstring>
#include <stdlib.h>

ControlJob::ControlJob() {
	// TODO Auto-generated constructor stub

}

ControlJob::~ControlJob() {
	// TODO Auto-generated destructor stub
}

JOB_EXIT_CODE ControlJob::excute()
{
	int cmdNums = 3;
	char *str = (char *)malloc(cmdNums);

	for(;;)
	{
		fgets(str,cmdNums,stdin);

		if(strcmp(str,"wq") == 0)
			break;

		//cout << "强制退出: wq" << endl;

	}

	free(str);

	return JOB_NORMAL_EXIT;
}
