// SystemClock.cpp
#include "SystemClock.h"

//----------------------------------------------------------------------------------------------------
//	Original QueryPerformance functionality
LARGE_INTEGER ClockStart()
{
	LARGE_INTEGER begin;
	if(!QueryPerformanceCounter(&begin))
	{
		// QuardPart property�� ���� �� �ִ� ���� begin ���� ��ü �ִ� �Ͱ� ����.
		// LARGE_INTEGER type�� 64��Ʈ�� int������ 64��Ʈ ũ���� ����ü�� ���Ͽ� �����̴�. 
		// �̿� ���� �������� ������� Low, High part�� ���� ������ ������ �ֱ� �����̴�.
		begin.QuadPart = 0;	
	}	
	return begin;
}

LARGE_INTEGER ClockEnd()
{
	LARGE_INTEGER end;
	if(!QueryPerformanceCounter(&end))
	{
		end.QuadPart = 0;
	}
	return end;
}

double ClockDuration(LARGE_INTEGER begin, LARGE_INTEGER end)
{
	double duration_milisec;
	LARGE_INTEGER freq;
	if(!QueryPerformanceFrequency(&freq))
		return -1000;	

	LARGE_INTEGER duration;
	duration.QuadPart = (end.QuadPart - begin.QuadPart);
	duration_milisec = (double)duration.QuadPart/(freq.QuadPart/1000.0);

	return duration_milisec;
}
//----------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------
//	Modified QueryPerformance functionality

//----------------------------------------------------------------------------------------------------

LARGE_INTEGER counter_start;

// if return value is 0, QueryPerformance cannot adapt to use.
// make this point of time to be zero.
LONGLONG	Clock_start()	
{
	LARGE_INTEGER counter_start;
	
	if(!QueryPerformanceCounter(&counter_start))
	{
		counter_start.QuadPart = 0;	
	}	
	return counter_start.QuadPart;
}

// Stop watch to retrive the time elapsed since first Clock_start()
double Clock_set()
{
	double duration_milisec;
	LARGE_INTEGER freq, set;
	if(!QueryPerformanceFrequency(&freq))
		return -1000.;	

	QueryPerformanceCounter(&set);

	LARGE_INTEGER duration;
	duration.QuadPart = (set.QuadPart - counter_start.QuadPart);
	duration_milisec = (double)duration.QuadPart/(freq.QuadPart/1000.0);

	return duration_milisec;
}


//----------------------------------------------------------------------------------------------------

BOOL PeekAndPump()
{
	static MSG msg;
	while (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) 
	{
		if (!AfxGetApp()->PumpMessage()) 
		{
			::PostQuitMessage(0);
			return FALSE;
		}
		Sleep(1);
	}
	return TRUE;
}

void Wait(DWORD dwT)
{
	DWORD dwST = GetTickCount();
	DWORD val = GetTickCount() - dwST;
    while( val < dwT)
	{
		PeekAndPump();
		Sleep(1);

		val = GetTickCount()-dwST;
	}
}