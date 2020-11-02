// SystemClock.h

#include "stdafx.h"

LARGE_INTEGER ClockStart();
LARGE_INTEGER ClockEnd();
double ClockDuration(LARGE_INTEGER begin, LARGE_INTEGER end);

LONGLONG	Clock_start()	;
double Clock_set();


void Wait(DWORD dwT);
