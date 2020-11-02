// Vision.h: interface for the CVision class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VISION_H__BCDEE2C5_BA6F_475A_A4ED_BD3C30038CDC__INCLUDED_)
#define AFX_VISION_H__BCDEE2C5_BA6F_475A_A4ED_BD3C30038CDC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "mil.h"
#include <mil.h>
#include "LogData.h"	// Added by ClassView
#pragma comment(lib,"mil.lib")



typedef struct
{
	MIL_ID MilApplication;
	MIL_ID MilSystem[MAX_CAMERAS];
	MIL_ID MilDigitizer[MAX_CAMERAS];
	MIL_ID MilBuffer[MAX_CAMERAS][MAX_BUFFER];
	MIL_ID MilImage[MAX_CAMERAS];
//	MIL_ID MilDisplay;
//	MIL_ID MilClipImage;
	int		i;
}UserDataStruct;
//long MFTYPE GrabStart(long HookType, MIL_ID EventId,void *vMilData);
//long MFTYPE GrabEnd(long HookType, MIL_ID EventId,void *vMilData);
//long MFTYPE ProcessingFunction(long HookType, MIL_ID HookId, void MPTYPE *HookDataPtr);

/* User's processing function prototype. */
MIL_INT MFTYPE ProcessingFunction(MIL_INT HookType, MIL_ID HookId, void* HookDataPtr);
MIL_INT MFTYPE ProcessingFunction1(MIL_INT HookType, MIL_ID HookId, void* HookDataPtr);
MIL_INT MFTYPE ProcessingFunction2(MIL_INT HookType, MIL_ID HookId, void* HookDataPtr);


class CVision  
{
public:
	BOOL CVision::Open1(int nWidth,int nHeight);
	void Close();
	void HookStop(int n);
	CLogData *m_pLogProcess;
	void GetExposureTime(double* pNanoSec);
	void SetExposureTime(int nCam, int nNanoSec,int flow);
	unsigned char* GetProcessBuf(int nCam);
	void SingleGrab(int nBufferNum);
//	BOOL m_bBufIndex;
	void ChangeVerticalLine(int Line);
	void MakeImg();
	int m_nImgVCount;
	void InitOriImage();
	void SetTrigMode();
	void SetLiveMode();
	void HookStop();
	void HookStart();
	unsigned char* GetImgPtr(int nCam,int nIndex);
//	unsigned char* GetOriImgPtr(int nCam,int nFrameNo);
//	BOOL Open(HWND hWnd,int nCam);
	BOOL Open(HWND hWnd,int nCam,int nWidth,int nHeight);

	CVision(CWnd* pwnd=NULL);
	virtual ~CVision();
	MIL_ID MilApplication;
	MIL_ID MilSystem[MAX_CAMERAS];
	MIL_ID MilDigitizer[MAX_CAMERAS];
	MIL_ID MilBuffer[MAX_CAMERAS][MAX_BUFFER];
	MIL_ID MilImage[MAX_CAMERAS];
//	MIL_ID MilDisplay;
	long m_nBand;
	long m_nSizeX;
	long m_nSizeY;
	CWnd*	m_pParent;	
//	void ImageClip(int nBufferNum);
//	void SaveImg(CString strpath);
	int m_nCrossCount;
	int m_nFrameCount;
/////////////////////////////////////////////////////@pwj
	unsigned short* GetProcessBufShort();
	unsigned short* GetImgPtrShort(int nIndex);
////////////////////////////////////////////////////	

	int		m_nBufIndexGrabStt[MAX_CAMERAS];
	int		m_nBufIndexGrabEnd[MAX_CAMERAS];
	int		m_nBufIndexCopy[MAX_CAMERAS];
//	int		m_nGrabCount;
};

#endif // !defined(AFX_VISION_H__BCDEE2C5_BA6F_475A_A4ED_BD3C30038CDC__INCLUDED_)
