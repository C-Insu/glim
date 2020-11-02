// TimingProcess.h: interface for the CTimingProcess class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TIMINGPROCESS_H__1DBACF5A_1024_4ACF_91C2_5D2C54F46C2D__INCLUDED_)
#define AFX_TIMINGPROCESS_H__1DBACF5A_1024_4ACF_91C2_5D2C54F46C2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*----------------------------------------------------------------------------------------

 1. ��� ����                                                
 - �Լ��������� ó�� �ҿ�ð� ����� �����ϵ��� �ؾ� �Ѵ�.
 - �����Լ����� �߻��Ǵ� system polling time���� ���� �Ҽ� �־�� �Ѵ�.
	-->�ý����� Process Flow�� ��Ȯ�� �������� ������, ������ ����� ������ �ȴ�.
 - Mil ���带 ����Ҷ��� ������ crystal clock�� ����ϹǷ� ��Ȯ�� ����� ���� �� ������, 
   ���带 ������� �ʰų� crystal clock�� �������� �ʴ� ������ ���� timing process�� 
   ��Ȯ�� ó���ϱ� �����.

 2. �⺻ ����
 - ������ ������ ������ ���� timing process ��ü�� �ʿ��ϴ�.
 - program ���������� ��� ��ġ������ access�� ���� �ؾ� �ϹǷ�,
   ���α׷��� �ֻ��� ��ġ�� �����ؾ� �Ѵ�.(App class�� ��ü�� ��ġ)
 - ������ timing function�� ���� versionó���� �Ǿ� �־, ������ ����� �����ؾ� �Ѵ�.
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
