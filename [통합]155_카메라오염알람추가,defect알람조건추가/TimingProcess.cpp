// TimingProcess.cpp: implementation of the CTimingProcess class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VisWeb.h"
#include "TimingProcess.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTimingProcess::CTimingProcess()
{
	memset(timer, 0, sizeof(tagTimerTable)*MAX_TIMER);

}

CTimingProcess::~CTimingProcess()
{

}

//------------------------------------------------------------------------------------------------
//	Mil-board carrying timing function
void CTimingProcess::initialize_timer(Real_set_timer_fp timer_start, Real_get_timer_fp timer_end)
{
	Timer_start = timer_start;
	Timer_end = timer_end;
	memset(timer, 0, sizeof(tagTimerTable)*MAX_TIMER);
}

//------------------------------------------------------------------------------------------------

double CTimingProcess::SetTimer(int timer_index)
{
	timer[timer_index].start_time = Timer_start();
	return timer[timer_index].start_time;
}
//------------------------------------------------------------------------------------------------

double CTimingProcess::GetTimer(int timer_index)
{
	timer[timer_index].end_time = Timer_end();
	timer[timer_index].elapse_time = (timer[timer_index].end_time - timer[timer_index].start_time);

	return timer[timer_index].elapse_time;
}

double CTimingProcess::ElapseTimer(int timer_index)
{
	return timer[timer_index].elapse_time;
}