#include <sys/time.h>
#include "TaskTool.h"

uint32_t TaskTool::getCurrTime()
{
	struct timeval tv;
	gettimeofday(&tv,0);
	return tv.tv_sec*1000 + tv.tv_usec;
}
