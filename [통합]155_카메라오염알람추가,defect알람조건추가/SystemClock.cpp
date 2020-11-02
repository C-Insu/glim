// SystemClock.cpp
#include "SystemClock.h"

//----------------------------------------------------------------------------------------------------
//	Original QueryPerformance functionality
LARGE_INTEGER ClockStart()
{
	LARGE_INTEGER begin;
	if(!QueryPerformanceCounter(&begin))
	{
		// QuardPart property에 값을 써 넣는 것이 begin 변수 자체 넣는 것과 같다.
		// LARGE_INTEGER type은 64비트형 int변수와 64비트 크기의 구조체의 유니온 변수이다. 
		// 이와 같은 변수형을 만든것은 Low, High part를 쉽게 나누어 얻을수 있기 때문이다.
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