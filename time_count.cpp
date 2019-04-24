/*
 * time_count.cpp
 *
 *  Created on: 2015-6-13
 *      Author: root
 */

#include "time_count.h"

#ifdef linux
void time_count::startcount(void)
{
gettimeofday(&startTime, 0);
}
void time_count::endcount()
{
gettimeofday(&endTime, 0);
}
long time_count::gettime(void)
{
	long time ;    //unit us
  long usec;
  long sec;
	if (startTime.tv_sec > endTime.tv_sec)
		return -1;
	if ((startTime.tv_sec==endTime.tv_sec) && (startTime.tv_usec > endTime.tv_usec))
		return -1;
	sec = (endTime.tv_sec - startTime.tv_sec);
	usec = (endTime.tv_usec - startTime.tv_usec);;
	if (usec < 0)
	{
		sec--;
		usec+=1000000;
	}
	time = sec*1000000 + usec;
return time;

}
#endif

#ifdef WIN32

void time_count::startcount(void)  //��ʼ��ʱ
{
	QueryPerformanceCounter(&nBeginTime);
}
void time_count::endcount(void)  //��ֹ��ʱ
{
	QueryPerformanceCounter(&nEndTime);
}
long time_count::gettime(void)   //��ȡʱ��
{
	long time;
	QueryPerformanceFrequency(&nFreq);
	time = (long)(((nEndTime.QuadPart-nBeginTime.QuadPart)*1000000)/nFreq.QuadPart); //show time
	return time;
}
//////////////////////////////////////////////////////////////

#endif








