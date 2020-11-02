// TimingProcess.h: interface for the CTimingProcess class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TIMINGPROCESS_H__1DBACF5A_1024_4ACF_91C2_5D2C54F46C2D__INCLUDED_)
#define AFX_TIMINGPROCESS_H__1DBACF5A_1024_4ACF_91C2_5D2C54F46C2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*----------------------------------------------------------------------------------------

 1. 고려 사항                                                
 - 함수내에서의 처리 소요시간 계산이 가능하도록 해야 한다.
 - 구현함수간에 발생되는 system polling time까지 포함 할수 있어야 한다.
	-->시스템의 Process Flow를 정확히 예측하지 않으면, 엉뚱한 결과가 나오게 된다.
 - Mil 보드를 사용할때는 보드의 crystal clock을 사용하므로 정확한 결과를 얻을 수 있으나, 
   보드를 사용하지 않거나 crystal clock을 지원하지 않는 보드의 경우는 timing process를 
   정확히 처리하기 힘들다.

 2. 기본 조건
 - 간단한 데이터 형식을 갖춘 timing process 객체가 필요하다.
 - program 내부적으로 어느 위치에서도 access가 가능 해야 하므로,
   프로그램의 최상위 위치에 존재해야 한다.(App class의 객체로 위치)
 - 실제의 timing function이 복합 version처리가 되어 있어서, 선택적 사용이 가능해야 한다.
   (QueryPerformance, Mil timer)
 
 3. 

  
-----------------------------------------------------------------------------------------*/

#define		MAX_TIMER	40

typedef struct tagTimerTable
{
	double	start_time;
	double	end_time;
	double	elapse_time;
}TIMER_TABLE;

typedef double (*Real_set_timer_fp)(void);
typedef double (*Real_get_timer_fp)(void);

#define TIMING_IDX_RESULT_RESPONSE			0
#define	TIMING_IDX_IMG_SAVE					1
#define TIMING_IDX_PROCESSING_TIME			2
#define TIMING_IDX_INSP_TIMEOUT				3
#define TIMING_IDX_INSP_TESTTIME			4
#define TIMING_IDX_TEST_TIME				5
#define TIMING_IDX_TEST_GRAB				6
#define TIMING_IDX_GRAB						7
#define TIMING_IDX_AREA_GRAB				8
#define TIMING_IDX_CHECK_SEND				11
#define TIMING_IDX_CHECK_FRAME				12
#define TIMING_IDX_CHECK_FRAMEOLD			13
#define TIMING_IDX_PROCESSING_TIME1			22


class CTimingProcess
{
public:
	CTimingProcess();
	virtual ~CTimingProcess();
	
	// Method
	double	SetTimer(int timer_index);
	double	GetTimer(int timer_index);
	double	ElapseTimer(int timer_index);

	// Attribute function
	void	initialize_timer(Real_set_timer_fp timer_start, Real_get_timer_fp timer_end);
public:
	TIMER_TABLE timer[MAX_TIMER];
	
	Real_set_timer_fp Timer_start;
	Real_set_timer_fp Timer_end;

};

#endif // !defined(AFX_TIMINGPROCESS_H__1DBACF5A_1024_4ACF_91C2_5D2C54F46C2D__INCLUDED_)
