// VisWebView.cpp : implementation of the CVisWebView class
#include "stdafx.h"
#include "VisWeb.h"
#include "VisWebDoc.h"
#include "VisWebView.h"
#include "LogData.h"
#include "TimingProcess.h"
#include "ini.h"
#include "inspect.h"
#include "Disk_File.h"
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "ImageFormat.h"
#include <algorithm>
//#include "NeProtocol.h"
#pragma comment (lib, "gdiplus.lib")
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern UINT ThreadDefectCopy(LPVOID lParam);
extern UINT ThreadCameraCheck(LPVOID lParam);

extern UINT ThreadFileCopy(LPVOID lParam);
extern UINT ThreadMain(LPVOID lParam);
extern UINT ThreadAutoEncorder(LPVOID lParam);
extern UINT ThreadInspectTest(LPVOID lParam);
extern UINT ThreadInspect(LPVOID lParam);
extern UINT ThreadInspect1(LPVOID lParam);//
extern UINT ThreadInspect2(LPVOID lParam);//
//extern UINT Threadlog(LPVOID lParam);
extern UINT ThreadSaveImage(LPVOID lParam);
extern UINT ThreadSaveImageCam2(LPVOID lParam);
extern UINT ThreadSaveImageCam3(LPVOID lParam);
extern UINT ThreadLightCheck(LPVOID lParam);

extern UINT ThreadSaveImage1(LPVOID lParam);
extern UINT ThreadSaveImage2(LPVOID lParam);
extern UINT ThreadDeleteImageFile(LPVOID lParam);
extern UINT ThreadLotChange1(LPVOID lParam);


extern UINT ThreadMismatch(LPVOID lParam);


extern UINT ThreadInspectMain(LPVOID lParam);//buf copy 부터 인스펙트까지 관리

//extern UINT ThreadInspectCu1(LPVOID lParam);
//extern UINT ThreadInspectCu2(LPVOID lParam);

/////////////////
extern UINT ThreadTest1(LPVOID lParam);
extern UINT ThreadTest2(LPVOID lParam);
extern UINT ThreadTest3(LPVOID lParam);
extern UINT ThreadTest4(LPVOID lParam);
extern UINT ThreadTest5(LPVOID lParam);
extern UINT ThreadTest6(LPVOID lParam);
extern UINT ThreadTest7(LPVOID lParam);
extern UINT ThreadTest8(LPVOID lParam);

extern UINT ThreadTest11(LPVOID lParam);
extern UINT ThreadTest12(LPVOID lParam);
extern UINT ThreadTest13(LPVOID lParam);
extern UINT ThreadTest14(LPVOID lParam);
extern UINT ThreadTest15(LPVOID lParam);
extern UINT ThreadTest16(LPVOID lParam);
extern UINT ThreadTest17(LPVOID lParam);
extern UINT ThreadTest18(LPVOID lParam);

extern UINT ThreadTest21(LPVOID lParam);
extern UINT ThreadTest22(LPVOID lParam);
extern UINT ThreadTest23(LPVOID lParam);
extern UINT ThreadTest24(LPVOID lParam);
extern UINT ThreadTest25(LPVOID lParam);
extern UINT ThreadTest26(LPVOID lParam);
extern UINT ThreadTest27(LPVOID lParam);
extern UINT ThreadTest28(LPVOID lParam);
/////////////////
extern UINT ThreadInsp1(LPVOID lParam);
extern UINT ThreadInsp2(LPVOID lParam);
extern UINT ThreadInsp3(LPVOID lParam);
extern UINT ThreadInsp4(LPVOID lParam);
extern UINT ThreadInsp5(LPVOID lParam);
extern UINT ThreadInsp6(LPVOID lParam);
extern UINT ThreadInsp7(LPVOID lParam);
extern UINT ThreadInsp8(LPVOID lParam);

extern UINT ThreadInsp11(LPVOID lParam);
extern UINT ThreadInsp12(LPVOID lParam);
extern UINT ThreadInsp13(LPVOID lParam);
extern UINT ThreadInsp14(LPVOID lParam);
extern UINT ThreadInsp15(LPVOID lParam);
extern UINT ThreadInsp16(LPVOID lParam);
extern UINT ThreadInsp17(LPVOID lParam);
extern UINT ThreadInsp18(LPVOID lParam);

extern UINT ThreadInsp21(LPVOID lParam);
extern UINT ThreadInsp22(LPVOID lParam);
extern UINT ThreadInsp23(LPVOID lParam);
extern UINT ThreadInsp24(LPVOID lParam);
extern UINT ThreadInsp25(LPVOID lParam);
extern UINT ThreadInsp26(LPVOID lParam);
extern UINT ThreadInsp27(LPVOID lParam);
extern UINT ThreadInsp28(LPVOID lParam);

extern UINT ThreadFullLine1(LPVOID lParam);
extern UINT ThreadFullLine2(LPVOID lParam);
extern UINT ThreadFullLine3(LPVOID lParam);
extern UINT ThreadFullLine4(LPVOID lParam);
extern UINT ThreadFullLine5(LPVOID lParam);
extern UINT ThreadFullLine6(LPVOID lParam);
extern UINT ThreadFullLine7(LPVOID lParam);
extern UINT ThreadFullLine8(LPVOID lParam);


extern UINT ThreadInsulateDefect1(LPVOID lParam);
extern UINT ThreadInsulateDefect2(LPVOID lParam);
extern UINT ThreadInsulateDefect3(LPVOID lParam);
extern UINT ThreadInsulateDefect4(LPVOID lParam);
extern UINT ThreadInsulateDefect5(LPVOID lParam);
extern UINT ThreadInsulateDefect6(LPVOID lParam);
extern UINT ThreadInsulateDefect7(LPVOID lParam);
extern UINT ThreadInsulateDefect8(LPVOID lParam);

/////////////////////////////////////////////////////
//preprocessing
extern UINT ThreadPreprocessing1(LPVOID lParam);
extern UINT ThreadPreprocessing2(LPVOID lParam);
extern UINT ThreadPreprocessing3(LPVOID lParam);
extern UINT ThreadPreprocessing4(LPVOID lParam);
extern UINT ThreadPreprocessing5(LPVOID lParam);
extern UINT ThreadPreprocessing6(LPVOID lParam);
extern UINT ThreadPreprocessing7(LPVOID lParam);
extern UINT ThreadPreprocessing8(LPVOID lParam);

extern UINT ThreadPreprocessing11(LPVOID lParam);
extern UINT ThreadPreprocessing12(LPVOID lParam);
extern UINT ThreadPreprocessing13(LPVOID lParam);
extern UINT ThreadPreprocessing14(LPVOID lParam);
extern UINT ThreadPreprocessing15(LPVOID lParam);
extern UINT ThreadPreprocessing16(LPVOID lParam);
extern UINT ThreadPreprocessing17(LPVOID lParam);
extern UINT ThreadPreprocessing18(LPVOID lParam);

extern UINT ThreadPreprocessing21(LPVOID lParam);
extern UINT ThreadPreprocessing22(LPVOID lParam);
extern UINT ThreadPreprocessing23(LPVOID lParam);
extern UINT ThreadPreprocessing24(LPVOID lParam);
extern UINT ThreadPreprocessing25(LPVOID lParam);
extern UINT ThreadPreprocessing26(LPVOID lParam);
extern UINT ThreadPreprocessing27(LPVOID lParam);
extern UINT ThreadPreprocessing28(LPVOID lParam);


double s_inspectTime;
int g_frame_num = -3;
CPacket g_packet;

#define TEVENT_HDD_SPACE 2
#define TEVENT_LIGHT_CHECK 3
#define TIMER_UPDATESTATICS 1005
#define TEVENT_CHECKLENGTH	1221
#define READ_SHARED_MEM	1300
#define ROLL_LEFT	2200
#define ROLL_RIGHT	19590
#define TIMER_PGM_STATUS 20000


CBitmap g_bitmap;
int g_Test = 0;
	
CWinThread	*g_GrabThread;
CWinThread	*g_GrabThreadSUB;

extern void DrawBMP(LPCTSTR lpszFileName, CDC *pDC, int nX, int nY, DWORD dwRop);

/////////////////////////////////////////////////////////////////////////////
// CVisWebView

IMPLEMENT_DYNCREATE(CVisWebView, CFormView)

BEGIN_MESSAGE_MAP(CVisWebView, CFormView)
	//{{AFX_MSG_MAP(CVisWebView)
	ON_COMMAND(IDM_IMAGE_LOAD, OnImageLoad)
	ON_COMMAND(IDM_IMAGE_SAVE, OnImageSave)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_BN_CLICKED(IDC_BTN_LOAD_IMG, OnBtnLoadImg)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_INSPECT, OnBtnInspect)
	ON_BN_CLICKED(IDC_BUTTON_FRAME_RESET, OnButtonFrameReset)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_RESTART_CASTING, OnButtonRestartCasting)
	ON_BN_CLICKED(IDC_BUTTON_INTERFACE, OnButtonInterface)
	ON_BN_CLICKED(IDC_CHECK_IMAGE_SAVE, OnCheckImageSave)
	ON_BN_CLICKED(IDC_BUTTON_GRID_MODIFY, OnButtonGridModify)
	ON_BN_CLICKED(IDC_CHECK_AUTO, OnCheckAuto)
	ON_BN_CLICKED(IDC_BTN_NG_IMG_BACWARD, OnBtnNgImgBacward)
	ON_BN_CLICKED(IDC_BTN_NG_IMG_FORWARD, OnBtnNgImgForward)
	ON_BN_CLICKED(IDC_BT_IMG_TEST, OnBtImgTest)
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(IDC_CK_AUTO, OnCkAuto)
	ON_BN_CLICKED(IDC_CK_SAVE_IMAGE, OnCkSaveImage)
	ON_BN_CLICKED(IDC_BTN_GET_PROFILE, OnBtnGetProfile)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE_NOTINSAREA, OnButtonUpdateNotinsarea)
	ON_BN_CLICKED(IDC_CK_VIEW_IMAGE, OnCkViewImage)
	ON_BN_CLICKED(IDC_NETWORK_TEST, OnNetworkTest)
	ON_BN_CLICKED(IDC_CK_SIM, OnCkSim)
	ON_BN_CLICKED(IDC_CK_LOT, OnCkLot)
	ON_BN_CLICKED(IDC_CK_LOTDEL, OnCkLotdel)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BINARY_VIEW, OnBinaryView)
	ON_BN_CLICKED(IDC_CK_VIEW2, OnCkView2)
	ON_BN_CLICKED(IDC_CK_BLOB, OnCkBlob)
	ON_BN_CLICKED(IDC_CK_VIEW3, OnCkView3)
	ON_BN_CLICKED(IDC_BTN_GET_PROFILE2, OnBtnGetProfile2)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
	ON_BN_CLICKED(IDC_CHECK_CAMCHANGE, &CVisWebView::OnBnClickedCheckCamchange)
	ON_BN_CLICKED(IDC_BTN_IMAGE_SAVE, &CVisWebView::OnBnClickedBtnImageSave)
	ON_BN_CLICKED(IDC_CHECK_IMAGE_SAVE_ALL, &CVisWebView::OnBnClickedCheckImageSaveAll)
	ON_BN_CLICKED(IDC_BUTTON4, &CVisWebView::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &CVisWebView::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BTN_GET_PROFILE3, &CVisWebView::OnBnClickedBtnGetProfile3)
	ON_BN_CLICKED(IDC_BUTTON7, &CVisWebView::OnBnClickedButton7)
	ON_WM_LBUTTONDOWN()
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_CHECK_ALARM_OFF, &CVisWebView::OnBnClickedCheckAlarmOff)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BT_ALARM_SET, &CVisWebView::OnBnClickedBtAlarmSet)
	ON_BN_CLICKED(IDC_CHECK_INSUL, &CVisWebView::OnBnClickedCheckInsul)
	ON_WM_PAINT()
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_BTN_WIDTH_DATA, &CVisWebView::OnBnClickedBtnWidthData)
	ON_BN_CLICKED(IDC_CHECK_PRIMER, &CVisWebView::OnBnClickedCheckPrimer)
	ON_BN_CLICKED(IDC_BUTTON_RESETIMAGE, &CVisWebView::OnBnClickedButtonResetimage)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVisWebView construction/destruction
UINT ThreadFullLine1(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());
	int nindex = 0;
	BOOL	bStart1 = TRUE;
	while(pView->m_bRun)
	{		
		{
			if(pView->m_bLineProj[nindex]){		
				pView->FullLineProjection(0,nindex);
			}
			Wait(1);
		}
	}
	return 1;
}
UINT ThreadFullLine2(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nindex = 1;
	BOOL	bStart1 = TRUE;

	while(pView->m_bRun)
	{		
		{
			if(pView->m_bLineProj[nindex]){
				pView->FullLineProjection(0,nindex);
			}
			Wait(1);
		}
	}
	return 1;
}
UINT ThreadFullLine3(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nindex = 2;
	BOOL	bStart1 = TRUE;

	while(pView->m_bRun)
	{		
		{
			if(pView->m_bLineProj[nindex]){
				pView->FullLineProjection(0,nindex);
			}
			Wait(1);
		}
	}
	return 1;
}
UINT ThreadFullLine4(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nindex = 3;
	BOOL	bStart1 = TRUE;

	while(pView->m_bRun)
	{		
		{
			if(pView->m_bLineProj[nindex]){
				pView->FullLineProjection(0,nindex);
			}
			Wait(1);
		}
	}
	return 1;
}
UINT ThreadFullLine5(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nindex = 4;
	BOOL	bStart1 = TRUE;

	while(pView->m_bRun)
	{		
		{
			if(pView->m_bLineProj[nindex]){
				pView->FullLineProjection(0,nindex);
			}
			Wait(1);
		}
	}
	return 1;
}
UINT ThreadFullLine6(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nindex = 5;
	BOOL	bStart1 = TRUE;

	while(pView->m_bRun)
	{		
		{
			if(pView->m_bLineProj[nindex]){
				pView->FullLineProjection(0,nindex);
			}
			Wait(1);
		}
	}
	return 1;
}
UINT ThreadFullLine7(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nindex = 6;
	BOOL	bStart1 = TRUE;

	while(pView->m_bRun)
	{		
		{
			if(pView->m_bLineProj[nindex]){
				pView->FullLineProjection(0,nindex);
			}
			Wait(1);
		}
	}
	return 1;
}
UINT ThreadFullLine8(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nindex = 7;
	BOOL	bStart1 = TRUE;

	while(pView->m_bRun)
	{		
		{
			if(pView->m_bLineProj[nindex]){
				pView->FullLineProjection(0,nindex);
			}
			Wait(1);
		}
	}
	return 1;
}

UINT ThreadInsulateDefect1(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());
	int nindex = 0;
	BOOL	bStart1 = TRUE;
	while(pView->m_bRun)
	{		
		{
			if(pView->m_bInsulateDefect[nindex]){		
				pView->InsulateDefect(0,nindex);
			}
			Wait(1);
		}
	}
	return 1;
}
UINT ThreadInsulateDefect2(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nindex = 1;
	BOOL	bStart1 = TRUE;

	while(pView->m_bRun)
	{		
		{
			if(pView->m_bInsulateDefect[nindex]){
				pView->InsulateDefect(0,nindex);
			}
			Wait(1);
		}
	}
	return 1;
}
UINT ThreadInsulateDefect3(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nindex = 2;
	BOOL	bStart1 = TRUE;

	while(pView->m_bRun)
	{		
		{
			if(pView->m_bInsulateDefect[nindex]){
				pView->InsulateDefect(0,nindex);
			}
			Wait(1);
		}
	}
	return 1;
}
UINT ThreadInsulateDefect4(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nindex = 3;
	BOOL	bStart1 = TRUE;

	while(pView->m_bRun)
	{		
		{
			if(pView->m_bInsulateDefect[nindex]){
				pView->InsulateDefect(0,nindex);
			}
			Wait(1);
		}
	}
	return 1;
}
UINT ThreadInsulateDefect5(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nindex = 4;
	BOOL	bStart1 = TRUE;

	while(pView->m_bRun)
	{		
		{
			if(pView->m_bInsulateDefect[nindex]){
				pView->InsulateDefect(0,nindex);
			}
			Wait(1);
		}
	}
	return 1;
}
UINT ThreadInsulateDefect6(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nindex = 5;
	BOOL	bStart1 = TRUE;

	while(pView->m_bRun)
	{		
		{
			if(pView->m_bInsulateDefect[nindex]){
				pView->InsulateDefect(0,nindex);
			}
			Wait(1);
		}
	}
	return 1;
}
UINT ThreadInsulateDefect7(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nindex = 6;
	BOOL	bStart1 = TRUE;

	while(pView->m_bRun)
	{		
		{
			if(pView->m_bInsulateDefect[nindex]){
				pView->InsulateDefect(0,nindex);
			}
			Wait(1);
		}
	}
	return 1;
}
UINT ThreadInsulateDefect8(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nindex = 7;
	BOOL	bStart1 = TRUE;

	while(pView->m_bRun)
	{		
		{
			if(pView->m_bInsulateDefect[nindex]){
				pView->InsulateDefect(0,nindex);
			}
			Wait(1);
		}
	}
	return 1;
}

////////////////////////////////////////////////////////////////////////////////
//preprocessing   InlinePreProcessing(int nCam,int nIndex,int nMod)

UINT ThreadPreprocessing1(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());
	int nCam = 0;
	int nindex = 0;
	BOOL	bStart1 = TRUE;

	while(pView->m_bRun)
	{		
		{
			if(pView->m_bPreprocessing[nCam][nindex]){
				pView->InlinePreProcessing(nCam,nindex,MOD_COUNT);
				pView->m_bPreprocessing[nCam][nindex] = FALSE;
			}
			Wait(1);
		}
	}
	return 1;
}
UINT ThreadPreprocessing2(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());
	int nCam = 0;
	int nindex = 1;
	BOOL	bStart1 = TRUE;

	while(pView->m_bRun)
	{		
		{
			if(pView->m_bPreprocessing[nCam][nindex]){
				pView->InlinePreProcessing(nCam,nindex,MOD_COUNT);
				pView->m_bPreprocessing[nCam][nindex] = FALSE;
			}
			Wait(1);
		}
	}
	return 1;
}
UINT ThreadPreprocessing3(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());
	int nCam = 0;
	int nindex = 2;
	BOOL	bStart1 = TRUE;

	while(pView->m_bRun)
	{		
		{
			if(pView->m_bPreprocessing[nCam][nindex]){
				pView->InlinePreProcessing(nCam,nindex,MOD_COUNT);
				pView->m_bPreprocessing[nCam][nindex] = FALSE;
			}
			Wait(1);
		}
	}
	return 1;
}
UINT ThreadPreprocessing4(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());
	int nCam = 0;
	int nindex = 3;
	BOOL	bStart1 = TRUE;

	while(pView->m_bRun)
	{		
		{
			if(pView->m_bPreprocessing[nCam][nindex]){
				pView->InlinePreProcessing(nCam,nindex,MOD_COUNT);
				pView->m_bPreprocessing[nCam][nindex] = FALSE;
			}
			Wait(1);
		}
	}
	return 1;
}
UINT ThreadPreprocessing5(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());
	int nCam = 0;
	int nindex = 4;
	BOOL	bStart1 = TRUE;

	while(pView->m_bRun)
	{		
		{
			if(pView->m_bPreprocessing[nCam][nindex]){
				pView->InlinePreProcessing(nCam,nindex,MOD_COUNT);
				pView->m_bPreprocessing[nCam][nindex] = FALSE;
			}
			Wait(1);
		}
	}
	return 1;
}
UINT ThreadPreprocessing6(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());
	int nCam = 0;
	int nindex = 5;
	BOOL	bStart1 = TRUE;

	while(pView->m_bRun)
	{		
		{
			if(pView->m_bPreprocessing[nCam][nindex]){
				pView->InlinePreProcessing(nCam,nindex,MOD_COUNT);
				pView->m_bPreprocessing[nCam][nindex] = FALSE;
			}
			Wait(1);
		}
	}
	return 1;
}
UINT ThreadPreprocessing7(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());
	int nCam = 0;
	int nindex = 6;
	BOOL	bStart1 = TRUE;

	while(pView->m_bRun)
	{		
		{
			if(pView->m_bPreprocessing[nCam][nindex]){
				pView->InlinePreProcessing(nCam,nindex,MOD_COUNT);
				pView->m_bPreprocessing[nCam][nindex] = FALSE;
			}
			Wait(1);
		}
	}
	return 1;
}
UINT ThreadPreprocessing8(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());
	int nCam = 0;
	int nindex = 7;
	BOOL	bStart1 = TRUE;

	while(pView->m_bRun)
	{		
		{
			if(pView->m_bPreprocessing[nCam][nindex]){
				pView->InlinePreProcessing(nCam,nindex,MOD_COUNT);
				pView->m_bPreprocessing[nCam][nindex] = FALSE;
			}
			Wait(1);
		}
	}
	return 1;
}
UINT ThreadPreprocessing11(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());
	int nCam = 1;
	int nindex = 0;
	BOOL	bStart1 = TRUE;

	while(pView->m_bRun)
	{		
		{
			if(pView->m_bPreprocessing[nCam][nindex]){
				pView->InlinePreProcessing(nCam,nindex,MOD_COUNT);
				pView->m_bPreprocessing[nCam][nindex] = FALSE;
			}
			Wait(1);
		}
	}
	return 1;
}
UINT ThreadPreprocessing12(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());
	int nCam = 1;
	int nindex = 1;
	BOOL	bStart1 = TRUE;

	while(pView->m_bRun)
	{		
		{
			if(pView->m_bPreprocessing[nCam][nindex]){
				pView->InlinePreProcessing(nCam,nindex,MOD_COUNT);
				pView->m_bPreprocessing[nCam][nindex] = FALSE;
			}
			Wait(1);
		}
	}
	return 1;
}
UINT ThreadPreprocessing13(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());
	int nCam = 1;
	int nindex = 2;
	BOOL	bStart1 = TRUE;

	while(pView->m_bRun)
	{		
		{
			if(pView->m_bPreprocessing[nCam][nindex]){
				pView->InlinePreProcessing(nCam,nindex,MOD_COUNT);
				pView->m_bPreprocessing[nCam][nindex] = FALSE;
			}
			Wait(1);
		}
	}
	return 1;
}
UINT ThreadPreprocessing14(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());
	int nCam = 1;
	int nindex = 3;
	BOOL	bStart1 = TRUE;

	while(pView->m_bRun)
	{		
		{
			if(pView->m_bPreprocessing[nCam][nindex]){
				pView->InlinePreProcessing(nCam,nindex,MOD_COUNT);
				pView->m_bPreprocessing[nCam][nindex] = FALSE;
			}
			Wait(1);
		}
	}
	return 1;
}
UINT ThreadPreprocessing15(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());
	int nCam = 1;
	int nindex = 4;
	BOOL	bStart1 = TRUE;

	while(pView->m_bRun)
	{		
		{
			if(pView->m_bPreprocessing[nCam][nindex]){
				pView->InlinePreProcessing(nCam,nindex,MOD_COUNT);
				pView->m_bPreprocessing[nCam][nindex] = FALSE;
			}
			Wait(1);
		}
	}
	return 1;
}
UINT ThreadPreprocessing16(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());
	int nCam = 1;
	int nindex = 5;
	BOOL	bStart1 = TRUE;

	while(pView->m_bRun)
	{		
		{
			if(pView->m_bPreprocessing[nCam][nindex]){
				pView->InlinePreProcessing(nCam,nindex,MOD_COUNT);
				pView->m_bPreprocessing[nCam][nindex] = FALSE;
			}
			Wait(1);
		}
	}
	return 1;
}
UINT ThreadPreprocessing17(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());
	int nCam = 1;
	int nindex = 6;
	BOOL	bStart1 = TRUE;

	while(pView->m_bRun)
	{		
		{
			if(pView->m_bPreprocessing[nCam][nindex]){
				pView->InlinePreProcessing(nCam,nindex,MOD_COUNT);
				pView->m_bPreprocessing[nCam][nindex] = FALSE;
			}
			Wait(1);
		}
	}
	return 1;
}
UINT ThreadPreprocessing18(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());
	int nCam = 1;
	int nindex = 7;
	BOOL	bStart1 = TRUE;

	while(pView->m_bRun)
	{		
		{
			if(pView->m_bPreprocessing[nCam][nindex]){
				pView->InlinePreProcessing(nCam,nindex,MOD_COUNT);
				pView->m_bPreprocessing[nCam][nindex] = FALSE;
			}
			Wait(1);
		}
	}
	return 1;
}

UINT ThreadPreprocessing21(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());
	int nCam = 2;
	int nindex = 0;
	BOOL	bStart1 = TRUE;

	while(pView->m_bRun)
	{		
		{
			if(pView->m_bPreprocessing[nCam][nindex]){
				pView->InlinePreProcessing(nCam,nindex,MOD_COUNT);
				pView->m_bPreprocessing[nCam][nindex] = FALSE;
			}
			Wait(1);
		}
	}
	return 1;
}
UINT ThreadPreprocessing22(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());
	int nCam = 2;
	int nindex = 1;
	BOOL	bStart1 = TRUE;

	while(pView->m_bRun)
	{		
		{
			if(pView->m_bPreprocessing[nCam][nindex]){
				pView->InlinePreProcessing(nCam,nindex,MOD_COUNT);
				pView->m_bPreprocessing[nCam][nindex] = FALSE;
			}
			Wait(1);
		}
	}
	return 1;
}
UINT ThreadPreprocessing23(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());
	int nCam = 2;
	int nindex = 2;
	BOOL	bStart1 = TRUE;

	while(pView->m_bRun)
	{		
		{
			if(pView->m_bPreprocessing[nCam][nindex]){
				pView->InlinePreProcessing(nCam,nindex,MOD_COUNT);
				pView->m_bPreprocessing[nCam][nindex] = FALSE;
			}
			Wait(1);
		}
	}
	return 1;
}
UINT ThreadPreprocessing24(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());
	int nCam = 2;
	int nindex = 3;
	BOOL	bStart1 = TRUE;

	while(pView->m_bRun)
	{		
		{
			if(pView->m_bPreprocessing[nCam][nindex]){
				pView->InlinePreProcessing(nCam,nindex,MOD_COUNT);
				pView->m_bPreprocessing[nCam][nindex] = FALSE;
			}
			Wait(1);
		}
	}
	return 1;
}
UINT ThreadPreprocessing25(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());
	int nCam = 2;
	int nindex = 4;
	BOOL	bStart1 = TRUE;

	while(pView->m_bRun)
	{		
		{
			if(pView->m_bPreprocessing[nCam][nindex]){
				pView->InlinePreProcessing(nCam,nindex,MOD_COUNT);
				pView->m_bPreprocessing[nCam][nindex] = FALSE;
			}
			Wait(1);
		}
	}
	return 1;
}
UINT ThreadPreprocessing26(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());
	int nCam = 2;
	int nindex = 5;
	BOOL	bStart1 = TRUE;

	while(pView->m_bRun)
	{		
		{
			if(pView->m_bPreprocessing[nCam][nindex]){
				pView->InlinePreProcessing(nCam,nindex,MOD_COUNT);
				pView->m_bPreprocessing[nCam][nindex] = FALSE;
			}
			Wait(1);
		}
	}
	return 1;
}
UINT ThreadPreprocessing27(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());
	int nCam = 2;
	int nindex = 6;
	BOOL	bStart1 = TRUE;

	while(pView->m_bRun)
	{		
		{
			if(pView->m_bPreprocessing[nCam][nindex]){
				pView->InlinePreProcessing(nCam,nindex,MOD_COUNT);
				pView->m_bPreprocessing[nCam][nindex] = FALSE;
			}
			Wait(1);
		}
	}
	return 1;
}
UINT ThreadPreprocessing28(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());
	int nCam = 2;
	int nindex = 7;
	BOOL	bStart1 = TRUE;

	while(pView->m_bRun)
	{		
		{
			if(pView->m_bPreprocessing[nCam][nindex]){
				pView->InlinePreProcessing(nCam,nindex,MOD_COUNT);
				pView->m_bPreprocessing[nCam][nindex] = FALSE;
			}
			Wait(1);
		}
	}
	return 1;
}

UINT ThreadMain(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nBuffer = 0;
	int nImageCount = 0;
	int nTmp =0;
	CString msg;

	while(pView->m_bRun)
	{		
		{
			WaitForSingleObject((HANDLE)pView->m_eGrab,INFINITE);
			
			pView->m_nGrabCount++;

			nImageCount = 0;
			
			pView->m_bGrabDone = FALSE;
			Wait(1);
		}
		Wait(1);
	}
	return 1;
}

UINT ThreadMismatch(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nBuffer = 0;
	int nImageCount = 0;
	int nTmp =0;
	CString msg;

	while(pView->m_bRun)
	{		
		if(pView->m_bAuto || pView->m_bDebug)
		{//복사해주는게 빠른지 복사해 오는게 빠른지??? 길이가 바뀌는 시점에 flag를 켜준다.
// 			if(pView->m_bCopyData==TRUE){
// 				pView->m_bCopyData = FALSE;
// 				pView->CopyMismatchFile();
// 			}
// 			Wait(5);
		}
		Wait(10);
	}
	return 1;
}


UINT ThreadAutoEncorder(LPVOID lParam)
{
	return 1;
}

UINT ThreadLightCheck(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nBuffer = 0;
	int nImageCount = 0;
	int nTmp =0;
	CString msg;

	while(1)
	{		
		while(WaitForSingleObject((HANDLE)pView->m_eLight, 1000) != WAIT_TIMEOUT )
		{
			if((pView->m_bAuto==FALSE && pView->m_bRun==FALSE) || (pView->m_bAuto<0 && pView->m_bRun<0))		return 0;

			pView->fnCheckLight();
		}
		
		Wait(5);
	}
	return 1;
}

UINT ThreadInspectTest(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;

	return 0;
	
}

UINT ThreadInspectMain(LPVOID lParam)//buf copy 부터 인스펙트까지 관리
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());
	int nTimeCout = 300;//m_dCheckTime
	while(pView->m_bRun){
		if(pView->m_bFullCopy[0]==TRUE || pView->m_bFullCopy[1]==TRUE ||pView->m_bFullCopy[2]==TRUE ){
			
			//Full Line Search
			pView->FullLineSearch();

			pView->m_bFullCopy[0] =pView->m_bFullCopy[1] =pView->m_bFullCopy[2] = FALSE;
		}
		Wait(1);
	}

	return 0;

}

//Nre Main Thread
UINT ThreadInspect(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam = 0;

	while(pView->m_bRun){
		{
			if(pView->m_bWaitThread[nCam]){
				pView->m_bWaitThread[nCam] = FALSE;
				pView->Inspect2(nCam);		//일반 검사 모드
			}
			Wait(1);
		}
	}

	return 1;
}


UINT ThreadInspect1(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=1;
	while(pView->m_bRun)
	{
		{
			if(pView->m_bWaitThread[nCam])
			{
				pView->m_bWaitThread[nCam] = FALSE;
				pView->Inspect2(nCam);		//일반 검사 모드 
			}
			Wait(1);
		}
	}

	return 1;
}

UINT ThreadInspect2(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());


	int nCam=2;
	while(pView->m_bRun)
	{
		{
			if(pView->m_bWaitThread[nCam])
			{
				pView->m_bWaitThread[nCam] = FALSE;
				pView->Inspect2(nCam);		//일반 검사 모드 
			}
			Wait(1);
		}
	}

	return 1;
}


UINT ThreadSaveImage(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nBuffer = 0;
	int nImageCount = 0;
	int nTmp =0;
	int nCam = 0;

	while(pView->m_bRun)
	{		
		//if(pView->m_bAuto)
		{
			while(WaitForSingleObject((HANDLE)pView->m_eSaveImage, 50) != WAIT_TIMEOUT )
			{
				if(pView->m_bSaving[nCam] == FALSE){
					//pView->GrabImgSave();
					pView->GrabImgSaveCam2(nCam);
				}			
			}
			//
			Wait(10);
		}
		Wait(10);
	}
	return 1;
}

UINT ThreadSaveImageCam2(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nBuffer = 0;
	int nImageCount = 0;
	int nTmp =0;
	int nCam = 1;

	while(pView->m_bRun)
	{		
		if(pView->m_bAuto )
		{
			while(WaitForSingleObject((HANDLE)pView->m_eSaveImageCam2, 50) != WAIT_TIMEOUT )
			{
				if(pView->m_bSaving[nCam] == FALSE){
					pView->GrabImgSaveCam2(nCam);
				}			
			}
			//
			Wait(10);
		}
		Wait(10);
	}
	return 1;
}

UINT ThreadSaveImageCam3(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nBuffer = 0;
	int nImageCount = 0;
	int nTmp =0;
	int nCam = 2;

	while(pView->m_bRun)
	{		
		if(pView->m_bAuto )
		{
			while(WaitForSingleObject((HANDLE)pView->m_eSaveImageCam3, 50) != WAIT_TIMEOUT )
			{
				if(pView->m_bSaving[nCam] == FALSE){
					pView->GrabImgSaveCam2(nCam);
				}			
			}
			//
			Wait(10);
		}
		Wait(10);
	}
	return 1;
}


UINT ThreadSaveImage1(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nBuffer = 0;
	int nImageCount = 0;
	int nTmp =0;

	while(pView->m_bRun)
	{		
//		if(pView->m_bAuto)
		{
			while(WaitForSingleObject((HANDLE)pView->m_eSaveImage1, 50) != WAIT_TIMEOUT )
			{
				if(pView->m_bDefectSaveStats == TRUE){
					pView->m_bDefectSaveStats = FALSE;
					pDoc->m_data.m_pImageDefect[0][pView->m_nDefectSaveCnt]->Save(pDoc->m_data.m_strDefectName[0][pView->m_nDefectSaveCnt]);
					pView->m_bDefectSaveStats = TRUE;
				}			
			}
			Wait(1);
		}
		Wait(1);
	}
	return 1;
}



UINT ThreadSaveImage2(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nBuffer = 0;
	int nImageCount = 0;
	int nTmp =0;

	while(pView->m_bRun)
	{		
		if(pView->m_bAuto || pView->m_bDebug)
		{
			while(WaitForSingleObject((HANDLE)pView->m_eSaveImage2, 50) != WAIT_TIMEOUT )
			{
				if(pView->m_dRemainHDDSpace>10){
					pDoc->m_data.m_pImageDefect[1][0]->Save(pDoc->m_data.m_strDefectName[1][1]);
				}			
			}
			//
			Wait(1);
		}
		Wait(1);
	}
	return 1;
}
//////////////////////////////////////////////////////////////// line find thread start
UINT ThreadTest1(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=0,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{
		if(pView->m_bTestFlag[0][nCam])//while(WaitForSingleObject((HANDLE)pView->m_evTest[0], 50) != WAIT_TIMEOUT )
		{
			pView->TestInspect(0,nCam,nMod);
			pView->m_bTestFlag[0][nCam]=FALSE;
//			pView->m_bTest[0][nCam] = TRUE;
		}
		Wait(2);
	}

	return 1;
}
UINT ThreadTest2(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=1,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{

		if(pView->m_bTestFlag[0][nCam])//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->TestInspect(0,nCam,nMod);
			pView->m_bTestFlag[0][nCam] = FALSE;
			//pView->m_bTest[0][nCam] = TRUE;

		}
		Wait(2);
	}

	return 1;
}

UINT ThreadTest3(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=2,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{

		if(pView->m_bTestFlag[0][nCam])//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->TestInspect(0,nCam,nMod);
			pView->m_bTestFlag[0][nCam] = FALSE;
			//pView->bTest[0][nCam] = TRUE;

		}
		Wait(2);
	}

	return 1;
}
UINT ThreadTest4(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=3,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{

		if(pView->m_bTestFlag[0][nCam])//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->TestInspect(0,nCam,nMod);
			pView->m_bTestFlag[0][nCam] = FALSE;
			//pView->m_bTest[0][nCam] = TRUE;

		}
		Wait(2);
	}

	return 1;
}

UINT ThreadTest5(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=4,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{

		if(pView->m_bTestFlag[0][nCam])//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->TestInspect(0,nCam,nMod);
			pView->m_bTestFlag[0][nCam] = FALSE;
			//pView->m_bTest[0][nCam] = TRUE;

		}
		Wait(2);
	}

	return 1;
}
UINT ThreadTest6(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=5,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{

		if(pView->m_bTestFlag[0][nCam])//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->TestInspect(0,nCam,nMod);
			pView->m_bTestFlag[0][nCam] = FALSE;
			//pView->m_bTest[0][nCam] = TRUE;

		}
		Wait(2);
	}

	return 1;
}
UINT ThreadTest7(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=6,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{

		if(pView->m_bTestFlag[0][nCam])//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->TestInspect(0,nCam,nMod);
			pView->m_bTestFlag[0][nCam] = FALSE;
			//pView->m_bTest[0][nCam] = TRUE;

		}
		Wait(2);
	}

	return 1;
}
UINT ThreadTest8(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=7,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{

		if(pView->m_bTestFlag[0][nCam])//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->TestInspect(0,nCam,nMod);
			pView->m_bTestFlag[0][nCam] = FALSE;
			//pView->m_bTest[0][nCam] = TRUE;

		}
		Wait(2);
	}

	return 1;
}

UINT ThreadTest11(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=0,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{
		if(pView->m_bTestFlag[1][nCam])//while(WaitForSingleObject((HANDLE)pView->m_evTest[0], 50) != WAIT_TIMEOUT )
		{
			pView->TestInspect(1,nCam,nMod);
			pView->m_bTestFlag[1][nCam]=FALSE;
			//pView->m_bTest[1][nCam] = TRUE;
		}
		Wait(2);
	}

	return 1;
}
UINT ThreadTest12(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=1,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{

		if(pView->m_bTestFlag[1][nCam])//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->TestInspect(1,nCam,nMod);
			pView->m_bTestFlag[1][nCam] = FALSE;
			//pView->m_bTest[1][nCam] = TRUE;

		}
		Wait(2);
	}

	return 1;
}

UINT ThreadTest13(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=2,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{

		if(pView->m_bTestFlag[1][nCam])//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->TestInspect(1,nCam,nMod);
			pView->m_bTestFlag[1][nCam] = FALSE;
			//pView->m_bTest[1][nCam] = TRUE;

		}
		Wait(1);
	}

	return 1;
}
UINT ThreadTest14(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=3,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{

		if(pView->m_bTestFlag[1][nCam])//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->TestInspect(1,nCam,nMod);
			pView->m_bTestFlag[1][nCam] = FALSE;
			//pView->m_bTest[1][nCam] = TRUE;

		}
		Wait(1);
	}

	return 1;
}
UINT ThreadTest15(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=4,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{

		if(pView->m_bTestFlag[1][nCam])//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->TestInspect(1,nCam,nMod);
			pView->m_bTestFlag[1][nCam] = FALSE;
			//pView->m_bTest[1][nCam] = TRUE;

		}
		Wait(2);
	}

	return 1;
}
UINT ThreadTest16(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=5,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{

		if(pView->m_bTestFlag[1][nCam])//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->TestInspect(1,nCam,nMod);
			pView->m_bTestFlag[1][nCam] = FALSE;
			//pView->m_bTest[1][nCam] = TRUE;

		}
		Wait(2);
	}

	return 1;
}
UINT ThreadTest17(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=6,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{

		if(pView->m_bTestFlag[1][nCam])//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->TestInspect(1,nCam,nMod);
			pView->m_bTestFlag[1][nCam] = FALSE;
			//pView->m_bTest[1][nCam] = TRUE;

		}
		Wait(2);
	}

	return 1;
}
UINT ThreadTest18(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=7,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{

		if(pView->m_bTestFlag[1][nCam])//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->TestInspect(1,nCam,nMod);
			pView->m_bTestFlag[1][nCam] = FALSE;
			//pView->m_bTest[1][nCam] = TRUE;

		}
		Wait(2);
	}

	return 1;
}

UINT ThreadTest21(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=0,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{
		if(pView->m_bTestFlag[2][nCam])//while(WaitForSingleObject((HANDLE)pView->m_evTest[0], 50) != WAIT_TIMEOUT )
		{
			pView->TestInspect(2,nCam,nMod);
			pView->m_bTestFlag[2][nCam]=FALSE;
			//pView->m_bTest[2][nCam] = TRUE;
		}
		Wait(2);
	}

	return 1;
}
UINT ThreadTest22(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=1,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{

		if(pView->m_bTestFlag[2][nCam])//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->TestInspect(2,nCam,nMod);
			pView->m_bTestFlag[2][nCam] = FALSE;
			//pView->m_bTest[2][nCam] = TRUE;

		}
		Wait(2);
	}

	return 1;
}

UINT ThreadTest23(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=2,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{

		if(pView->m_bTestFlag[2][nCam])//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->TestInspect(2,nCam,nMod);
			pView->m_bTestFlag[2][nCam] = FALSE;
			//pView->m_bTest[2][nCam] = TRUE;

		}
		Wait(2);
	}

	return 1;
}
UINT ThreadTest24(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=3,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{

		if(pView->m_bTestFlag[2][nCam])//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->TestInspect(2,nCam,nMod);
			pView->m_bTestFlag[2][nCam] = FALSE;
			//pView->m_bTest[2][nCam] = TRUE;

		}
		Wait(2);
	}

	return 1;
}
UINT ThreadTest25(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=4,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{

		if(pView->m_bTestFlag[2][nCam])//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->TestInspect(2,nCam,nMod);
			pView->m_bTestFlag[2][nCam] = FALSE;
			//pView->m_bTest[2][nCam] = TRUE;

		}
		Wait(2);
	}

	return 1;
}
UINT ThreadTest26(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=5,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{

		if(pView->m_bTestFlag[2][nCam])//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->TestInspect(2,nCam,nMod);
			pView->m_bTestFlag[2][nCam] = FALSE;
			//pView->m_bTest[2][nCam] = TRUE;

		}
		Wait(2);
	}

	return 1;
}
UINT ThreadTest27(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=6,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{

		if(pView->m_bTestFlag[2][nCam])//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->TestInspect(2,nCam,nMod);
			pView->m_bTestFlag[2][nCam] = FALSE;
			//pView->m_bTest[2][nCam] = TRUE;

		}
		Wait(2);
	}

	return 1;
}
UINT ThreadTest28(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=7,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{

		if(pView->m_bTestFlag[2][nCam])//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->TestInspect(2,nCam,nMod);
			pView->m_bTestFlag[2][nCam] = FALSE;
			//pView->m_bTest[2][nCam] = TRUE;

		}
		Wait(2);
	}

	return 1;
}
//////////////////////////////////////////////////////////////// line find thread end
//////////////////////////////////////////////////////////////// line find thread start22222222222222222222222222222222
UINT ThreadInsp1(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=0,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{
		if(pView->m_nInspFlag[0][nCam]==1)//while(WaitForSingleObject((HANDLE)pView->m_evTest[0], 50) != WAIT_TIMEOUT )
		{
			pView->m_nInspFlag[0][nCam]=2;
			pView->RoiInspect(0,nCam,nMod);
			pView->m_nInspFlag[0][nCam]=0;
		}
		Wait(2);
	}

	return 1;
}
UINT ThreadInsp2(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=1,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{

		if(pView->m_nInspFlag[0][nCam]==1)//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->m_nInspFlag[0][nCam]=2;
			pView->RoiInspect(0,nCam,nMod);
			pView->m_nInspFlag[0][nCam]=0;

		}
		Wait(2);
	}

	return 1;
}

UINT ThreadInsp3(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=2,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{

		if(pView->m_nInspFlag[0][nCam]==1)//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->m_nInspFlag[0][nCam]=2;
			pView->RoiInspect(0,nCam,nMod);
			pView->m_nInspFlag[0][nCam]=0;

		}
		Wait(2);
	}

	return 1;
}
UINT ThreadInsp4(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=3,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{
		if(pView->m_nInspFlag[0][nCam]==1)//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->m_nInspFlag[0][nCam]=2;
			pView->RoiInspect(0,nCam,nMod);
			pView->m_nInspFlag[0][nCam]=0;

		}
		Wait(2);
	}

	return 1;
}

UINT ThreadInsp5(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=4,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{
		if(pView->m_nInspFlag[0][nCam]==1)//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->m_nInspFlag[0][nCam]=2;
			pView->RoiInspect(0,nCam,nMod);
			pView->m_nInspFlag[0][nCam]=0;

		}
		Wait(2);
	}

	return 1;
}
UINT ThreadInsp6(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=5,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{
		if(pView->m_nInspFlag[0][nCam]==1)//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->m_nInspFlag[0][nCam]=2;
			pView->RoiInspect(0,nCam,nMod);
			pView->m_nInspFlag[0][nCam]=0;

		}

		Wait(2);
	}

	return 1;
}
UINT ThreadInsp7(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=6,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{
		if(pView->m_nInspFlag[0][nCam]==1)//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->m_nInspFlag[0][nCam]=2;
			pView->RoiInspect(0,nCam,nMod);
			pView->m_nInspFlag[0][nCam]=0;

		}

		Wait(2);
	}

	return 1;
}
UINT ThreadInsp8(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=7,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{
		if(pView->m_nInspFlag[0][nCam]==1)//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->m_nInspFlag[0][nCam]=2;
			pView->RoiInspect(0,nCam,nMod);
			pView->m_nInspFlag[0][nCam]=0;

		}

		Wait(2);
	}

	return 1;
}

UINT ThreadInsp11(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=0,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{
		if(pView->m_nInspFlag[1][nCam]==1)//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->m_nInspFlag[1][nCam]=2;
			pView->RoiInspect(1,nCam,nMod);
			pView->m_nInspFlag[1][nCam]=0;

		}
		Wait(2);
	}

	return 1;
}
UINT ThreadInsp12(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=1,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{
		if(pView->m_nInspFlag[1][nCam]==1)//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->m_nInspFlag[1][nCam]=2;
			pView->RoiInspect(1,nCam,nMod);
			pView->m_nInspFlag[1][nCam]=0;

		}
		Wait(2);
	}

	return 1;
}

UINT ThreadInsp13(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=2,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{
		if(pView->m_nInspFlag[1][nCam]==1)//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->m_nInspFlag[1][nCam]=2;
			pView->RoiInspect(1,nCam,nMod);
			pView->m_nInspFlag[1][nCam]=0;

		}
		Wait(2);
	}

	return 1;
}
UINT ThreadInsp14(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=3,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{
		if(pView->m_nInspFlag[1][nCam]==1)//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->m_nInspFlag[1][nCam]=2;
			pView->RoiInspect(1,nCam,nMod);
			pView->m_nInspFlag[1][nCam]=0;

		}
		Wait(2);
	}

	return 1;
}
UINT ThreadInsp15(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=4,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{
		if(pView->m_nInspFlag[1][nCam]==1)//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->m_nInspFlag[1][nCam]=2;
			pView->RoiInspect(1,nCam,nMod);
			pView->m_nInspFlag[1][nCam]=0;

		}
		Wait(2);
	}

	return 1;
}
UINT ThreadInsp16(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=5,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{

		if(pView->m_nInspFlag[1][nCam]==1)//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->m_nInspFlag[1][nCam]=2;
			pView->RoiInspect(1,nCam,nMod);
			pView->m_nInspFlag[1][nCam]=0;

		}
		Wait(2);
	}

	return 1;
}
UINT ThreadInsp17(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=6,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{
		if(pView->m_nInspFlag[1][nCam]==1)//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->m_nInspFlag[1][nCam]=2;
			pView->RoiInspect(1,nCam,nMod);
			pView->m_nInspFlag[1][nCam]=0;

		}
		Wait(2);
	}

	return 1;
}
UINT ThreadInsp18(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=7,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{
		if(pView->m_nInspFlag[1][nCam]==1)//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->m_nInspFlag[1][nCam]=2;
			pView->RoiInspect(1,nCam,nMod);
			pView->m_nInspFlag[1][nCam]=0;

		}
		Wait(2);
	}

	return 1;
}

UINT ThreadInsp21(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=0,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{
		if(pView->m_nInspFlag[2][nCam]==1)//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->m_nInspFlag[2][nCam]=2;
			pView->RoiInspect(2,nCam,nMod);
			pView->m_nInspFlag[2][nCam]=0;

		}
		Wait(2);
	}

	return 1;
}
UINT ThreadInsp22(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=1,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{
		if(pView->m_nInspFlag[2][nCam]==1)//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->m_nInspFlag[2][nCam]=2;
			pView->RoiInspect(2,nCam,nMod);
			pView->m_nInspFlag[2][nCam]=0;

		}
		Wait(2);
	}

	return 1;
}

UINT ThreadInsp23(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=2,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{
		if(pView->m_nInspFlag[2][nCam]==1)//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->m_nInspFlag[2][nCam]=2;
			pView->RoiInspect(2,nCam,nMod);
			pView->m_nInspFlag[2][nCam]=0;

		}
		Wait(2);
	}

	return 1;
}
UINT ThreadInsp24(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=3,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{
		if(pView->m_nInspFlag[2][nCam]==1)//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->m_nInspFlag[2][nCam]=2;
			pView->RoiInspect(2,nCam,nMod);
			pView->m_nInspFlag[2][nCam]=0;

		}
		Wait(2);
	}

	return 1;
}
UINT ThreadInsp25(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=4,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{
		if(pView->m_nInspFlag[2][nCam]==1)//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->m_nInspFlag[2][nCam]=2;
			pView->RoiInspect(2,nCam,nMod);
			pView->m_nInspFlag[2][nCam]=0;

		}
		Wait(2);
	}

	return 1;
}
UINT ThreadInsp26(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=5,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{
		if(pView->m_nInspFlag[2][nCam]==1)//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->m_nInspFlag[2][nCam]=2;
			pView->RoiInspect(2,nCam,nMod);
			pView->m_nInspFlag[2][nCam]=0;

		}
		Wait(2);
	}

	return 1;
}
UINT ThreadInsp27(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=6,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{
		if(pView->m_nInspFlag[2][nCam]==1)//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->m_nInspFlag[2][nCam]=2;
			pView->RoiInspect(2,nCam,nMod);
			pView->m_nInspFlag[2][nCam]=0;

		}
		Wait(2);
	}

	return 1;
}

UINT ThreadInsp28(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	int nCam=7,nMod=MOD_COUNT;
	while(pView->m_bRun)
	{
		if(pView->m_nInspFlag[2][nCam]==1)//while(WaitForSingleObject((HANDLE)pView->m_evTest[1], 50) != WAIT_TIMEOUT )
		{
			pView->m_nInspFlag[2][nCam]=2;
			pView->RoiInspect(2,nCam,nMod);
			pView->m_nInspFlag[2][nCam]=0;

		}
		Wait(2);
	}

	return 1;
}
UINT ThreadFileCopy(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	while(pView->m_bRun)
	{
		if(pView->m_bAuto){
			if(pView->m_bCopyFile==TRUE){
				if(pView->m_strComputerName.Find("BACK")>=0 || pDoc->m_data.m_strComName.Mid(9,1)=="B" ){
					pView->CopyMismatchFile();
					if(pView->m_strComputerName.Mid(8,1)=="M")
						pView->CopyMismatchFile2();
				}
				else
					pView->CopyMismatchFile1();

				pView->m_bCopyFile = FALSE;
			}
			Wait(5);
		}
		Wait(5);
	}

	return 1;
}


////defect Image copy
UINT ThreadDefectCopy(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

//  	while(pView->m_bRun)
//  	{
//  		if(pView->m_bAuto){
//  			if(pView->m_bCopyFile==TRUE){
//  				pView->m_bCopyFile = FALSE;
//  				pView->CopyMismatchFile();
//  
//  			}
//  			Wait(10);
//  		}
//  		Wait(10);
//  	}

	return 1;
}
//////////////////////////////////////////////////////////////// CIS Camera check
UINT ThreadCameraCheck(LPVOID lParam)//chcho //1412
{
	CVisWebView *pView = (CVisWebView *)lParam;
	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());

	BOOL	bCheck = TRUE,bCheck1 = TRUE;
	int nOldFrame = 0,nNullBright = 0,nMargin = 5,newBright=0,oldBright=0,nMod=0;
	CString strBright1=pDoc->m_pDlgInterface->m_strDefaultBright1,strBright2="",strBright3="";//LC 60 01 00 //15
	while(pView->m_bRun){
		if(pView->m_bAuto && pDoc->m_pDlgInterface->m_bAutoBrightness){//Lot change시만 실시한다.
			newBright = pDoc->m_pDlgInterface->m_nLightOnTime;

			//Frame 변화 체크
			//좌 우 무지중 어두운 밝기를 기준으로 한다.
			if(nOldFrame>0 && nOldFrame < pDoc->m_nTotalIns[0]+2 && pView->m_bChageShutter && pView->m_bChangeLight){//한번 실행후 2frame 후에 다시 실행한다.
				//밝기 체크 - 어두운 무지부 밝기를 가져온다. 좌측 / 우측
				nNullBright = pDoc->m_data.m_nNCoatBrightness[0];
				if(pDoc->m_data.m_nNCoatBrightness[1]>0 && nNullBright>pDoc->m_data.m_nNCoatBrightness[1])nNullBright = pDoc->m_data.m_nNCoatBrightness[1];
				if(nMod>1000)nMod -=1000;
//				strBright2 = strBright1.Mid(3,2);strBright3 = strBright1.Right(2);//
				
				if(pDoc->m_pDlgInterface->m_nAutoBrightness+5<nNullBright){//250 설정시 //밝기 1 다운
					nMod++;
					if(nMod%2==0)
						newBright--;
					strBright2 = pView->GetLightValue1(newBright,nMod);
				}
				else if(pDoc->m_pDlgInterface->m_nAutoBrightness-10>nNullBright){//250 설정시 245 보다 작다 밝기 1 up
					nMod++;
					if(nMod%2==0)
						newBright++;
					strBright2 = pView->GetLightValue1(newBright,nMod);
				}
				else{
					pView->m_bChangeLight = FALSE;
					continue;
				}
				if(newBright<2){
					newBright = 2;
					continue;
				}
				else if(newBright>50){
					newBright = 50;continue;
				}
				if( oldBright != newBright){
					//밝기 조절
					pDoc->m_pDlgInterface->ChangeBrightness(newBright,nMod,60);
// 					CString strCmd; 
// 					strCmd.Format(_T("LC%s"),strBright2);
// 					pView->m_cis->SendCmd(strCmd); 
// 
// 					strCmd.Format(_T("Camera Response: %s,%s"),pView->m_cis->tCisRxData,strBright2);
// 					pView->AddtoList(strCmd, 0, 0);  

					pDoc->m_pDlgInterface->m_nLightOnTime = newBright;
					pDoc->m_pDlgInterface->SaveLightParam();
					pView->SendMessage(WM_UPDATEDLG,0,0);
				}
				oldBright = newBright;
			}
			nOldFrame = pDoc->m_nTotalIns[0];
			Wait(100);
		}
		Wait(1000);
	}
//밝기값 자동 조정 으로 사용한다.
//	ini.SER_GETD(FALSE, m_nAutoBrightness	, 250);//밝기값 16 
//	ini.SER_GETD(FALSE, m_bAutoBrightness	, 0);//밝기값 16 


// 	while(bCheck){
// 
// 		if(bCheck1)
// 			bCheck = FALSE;
// 		
// 		Wait(10);
// 	}


	return 1;
}
//////////////////////////////////////////////////////////////// line find thread end2222222222222222222222
UINT ThreadDeleteImageFile(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;

	while(1)
	{		
		if(pView->m_bImageDelete == TRUE)
		{
			pView->RecursiveDelete("C:\\GLIM\\IMAGE");
			pView->m_bImageDelete = false;
		}
		Wait(100);
	}
	return 1;
}
//LotChange
UINT ThreadLotChange1(LPVOID lParam)
{
	CVisWebView *pView = (CVisWebView *)lParam;

	int nCheck = 0;
	while(1)
	{	
		for(int i=0;i<10 ;i++){
			if(pView->m_bLotChange[i]){
				Wait(5000);
				pView->LotChange();
				break;
			}
		}

		Wait(500);
	}
	return 1;
}

//20150303_ljh
//폴더 내 디렉토리 및 파일 모두 지우는 펑션
void CVisWebView::RecursiveDelete(CString szPath)
{
	CFileFind ff;
	CString path = szPath;

	if(path.Right(1) != "\\")
		path += "\\";

	path += "*.*";

	BOOL res = ff.FindFile(path);

	while(res)
	{
		res = ff.FindNextFile();
		
		if (!ff.IsDots() && !ff.IsDirectory())	//file
			DeleteFile(ff.GetFilePath());
		else if (ff.IsDirectory())	//directory
		{
			CString DirName = ff.GetFileName();
			// 현재폴더 상위폴더 썸네일파일은 제외
			if( DirName == _T(".") || 
				DirName == _T("..")|| 
				DirName == _T("Thumbs.db") ) continue;
			
			path = ff.GetFilePath();
			RecursiveDelete(path);
			RemoveDirectory(path);
		}
	}
}


CVisWebView::CVisWebView()
	: CFormView(CVisWebView::IDD)
	, m_bCamChange(FALSE)
	, m_nExposre1(0)
	, m_nYLine1(33)
	, m_bImageSaveAll(FALSE)
	, m_binaryValue(0)
	, m_dDefectSize(6)
	, m_nThWhite(45)
	, m_nThBlack(40)
	, m_dSlope(220)
	, m_dLineScratch(15)
	, m_bAlarmOff(FALSE)
	, m_bInsulateInspect(FALSE)
	, m_bPrimer(FALSE)
{
	//{{AFX_DATA_INIT(CVisWebView)
	m_nScratchCount = 0;
	m_bChangeLight = FALSE;
	m_bDrawStats = FALSE;
	m_bChageShutter = FALSE;
	m_nSaveNgCode = 0;
	m_bEdgeView = FALSE;
	m_nSelectPlcModelNo = 1;
	m_nFoilCount = 0;
	m_nFoilCheck = 0;
	m_bLotchanging = FALSE;
	m_bPassCheck = FALSE;
	m_nLineCountMiss = 0;
	m_nCylinderOnOff = 0;
	m_nLineRunning = 0;
	m_nLastLineCount[0]=m_nLastLineCount[1]=0;
	m_nInspFrame[0]=m_nInspFrame[1] = 0;
	for(int i=0;i<100;i++)
		m_nTextColor[i] = 0;
	m_dCheckTime[0]=m_dCheckTime[1] = 0;
	m_bCopyComplete = FALSE;
	m_dRealMeter[0]=m_dRealMeter[1] = 0;

	m_bNonCoat[0] = FALSE;
	m_bNonCoat[1] = FALSE;
	for(int i=0;i<10;i++){
		m_bLotChange[i] = FALSE;
		m_strLotChangeID[i] = "";
		m_strLotChangeTime[i] = "";
	}
	m_nLotChangeCount = 0;
	m_nThreadcheck[0]=m_nThreadcheck[1]=m_nThreadcheck[2] = 0;

	for(int i=0;i<10;i++)m_strServerSendFileName[i] = "";
	for(int i=0;i<40;i++)
		m_strPlcModelname[i] = "";
	for(int i=0;i<20;i++){	
		m_nUsecheck[i] = -1;
		for(int j=0;j<2;j++)			m_ptLinePos[i][j].SetPoint(0,0);}//0301}

	for(int i=0;i<40;i++){
		m_dLastCoatWidth[i] = 0;
	}
	m_strLastCoatWidth = "";
	m_strLastNonCoatWidth = "";
	m_nDisplayDraw = 0;
	m_nInspTimeOut = 0;

	m_nCamNoiseCheck = 0;
	m_nStartSkipFrame[0]=m_nStartSkipFrame[1]=m_nStartSkipFrame[2]= -1;

	m_bMismatchView = FALSE;
	m_bDebug = FALSE;
	m_bNewAlarm = FALSE;
	m_nNewAlarm = 0;
	m_nCamPort=9;
	m_nIOPort = 4;

	m_nOldFrame = 0;
	m_nLengFrmaeGap = 0;
	m_nAlarmCnt = 0;
	m_nAlarmCnt1 = 0;
	m_nDataMissing = 0;
	m_nMismatchBadCount = 0;
	m_nSelectNum = 0;
	m_bDrawCheck = FALSE;
	m_bCopyFile = FALSE;
	m_bCopyFolder = FALSE;
	m_bCopyFolder1 = FALSE;
	m_strOldPath = "";
	m_nOldLine = 0;
	m_nLineCount = 0;
	m_strAlarmMsg = "Alarm";
	m_strAlarmMsg1 = "Meter";

	m_dMismatchTolMax = 0.6;
	m_dMismatchTolMin = 0.6;
	m_dMismatchTolMax = 1;
	m_dMismatchTolMin = 1;
	m_bAlarmOnOff = FALSE;
	m_nAlarmStartFRame=0;
	m_nAlarmEndFRame=0;
	m_nContinueCnt = 0;
	m_bFullCopy[0]=m_bFullCopy[1]=m_bFullCopy[2]=FALSE;

	//ljh
	for(int i=0; i<20; i++){
		m_bMemoryConnect[i] = FALSE;
		m_bMemoryIsUse[i] = FALSE;
		m_strMemoryAddress[i].Empty();
		for(int k1=0;k1<10;k1++)
			m_strMemoryWriteAddress1[k1][i].Empty();//mismatch
	}
	for(int i=0;i<10;i++)m_nBadCountDefect[i] = 0;

	for(int i=0;i<10;i++)for(int j=0;j<40;j++)
		m_dLastTenMeter[i][j] =0;
	for(int i=0; i<15; i++){
		m_charLbLotInfo[i] = new char[100];
		memset(m_charLbLotInfo[i], NULL, sizeof(char)*100);
	}

	for(int i=0;i<100;i++)
		m_nNgFrameCount[i] = 0;
	memset(cLotID, NULL, sizeof(char)*100);
	memset(cLotCurrent, NULL, sizeof(char)*100);
	memset(cLotOld, NULL, sizeof(char)*100);

	m_strLotID.Empty();
	m_nRwRollA = 0;
	m_nRwRollB = 0;
	m_nRwRollIncA = 0;
	m_nRwRollIncB = 0;
	m_nRwChkCntTemp = 0;
	m_nRwChkCnt = 8;



	m_nPortNum = 7000;
	m_bImageSave = FALSE;
	m_bImageSaveAll = FALSE;
	m_bAutoRun = FALSE;
	m_bImageSelect = FALSE;
	m_nNotInsAreaView = 0;
	m_bViewImage = TRUE;
	m_dXLineSkip = 0.0;
	m_bSimmulation = TRUE;
	m_bLotSave = FALSE;
	m_bLotDel = FALSE;
	m_nSelectCam = 0;
	m_dMachineLength = 0;
	m_nTextWriteCount = 0;
	m_bAuto = FALSE;
	for(int n=0;n<MAX_CAMERAS;n++)
	{
		m_bTestInspect[n] = FALSE;
		m_nLastBrightness[n] = 0;
		m_nSkipFrame[n] = 1000;

		m_nBrightcheck[n] = 0;
		m_nExpose = 700;
		m_nExposre1 = 700;
		m_nExposre2 = 700;
		m_nThCount[n] = 0;
		for(int i=0;i<10;i++){
			m_bTestFlag[n][i]=FALSE;
			m_bPreprocessing[n][i] = FALSE;
		}

	}
	for(int i=0;i<15;i++){
		m_pDefectImage[i] = NULL;
	}
	for(int i=0;i<20;i++){
		m_fmEdgeVew[i] = NULL;
	}
	

	ConvertCharToStr(cLotID) = "None";
	m_nTacX = 0;
	m_bBinaryView = TRUE;
	m_nYLine = 33;
	m_bViewTest = TRUE;
	m_bCrossBlobImg = FALSE;
	m_nInsMethod = 1;
	m_bViewTest1 = FALSE;
	m_nSplice =0;
	m_nNewLot = 1;
	m_nChgExposure = 0;
	m_strVolt = _T("");
	m_strCElect = _T("");
	m_strElect = _T("");
	m_isLogSave = false;
	//}}AFX_DATA_INIT
	// TODO: add construction code here

	m_bRun = TRUE;
	m_pThreadMain = NULL;
	m_pThreadInspect = NULL;

	m_bDraw = FALSE;
	m_bTest1 = FALSE;
	m_bYSim = FALSE;

	m_bAuto		= FALSE;

	m_bReset = FALSE;
	m_bSaving[0]=m_bSaving[1]=m_bSaving[2] = FALSE;
	m_bSaving1 = FALSE;
	m_bSaving2 = FALSE;
	m_nGrabCount =0;
	m_bMismatchUse = FALSE;

	m_backup_idx = 0;
	m_nTextcopy = 0;
	m_nEndText	= 0;
	m_img_save_time = 0;
	m_dRemainHDDSpace = 0;
	m_dRemainMainSpace = 0;
	m_imageSaveExt = TRUE;//d drive
	m_fFps = 0;
	m_bGrabDone = FALSE;
	m_nCurNGImgIndex = 0;
	m_bConnectCam = TRUE;
//	m_rectNGImage.SetRect(FORM_IMG_WIDTH + 5, 500, FORM_IMG_WIDTH+5 + BAD_IMG_WIDTH, 500+BAD_IMG_HEIGHT);
	m_rectNGImage.SetRect(550, 700+50+50,550 + 200, 750+200+50);

	m_nMilGrabCount	 = -1;
	m_nMilCopyCount	 = -1;
	m_nResetSystem = -1;
	m_nResetCount = 0;
	m_nCheckNewLot = 0;
	m_nCheckCycle = 0;
	m_nOldCount[0] = 0;
	m_nOldCount[1] = 0;

	nRegCheck=0;

	for(int i=0;i<MAXLIGHTCOUNT;i++)
	{
		m_CurrentElectric[i] = 0;
		m_Voltage[i] = 0;
		m_Electric[i] = 0;
	}
	m_nCrossPolFrame = 0;
	m_nCrossPolOffset = 0;
	m_nCkSpliceCount = 0;
	m_nLaneCount = 0;
	m_nLaneCount1 =0;

	for(int i=0;i<MAX_LENGTH;i++){
		m_dTolerance[i] = 0.2;
		m_dTolerance1[i] = 0.2;
		m_bUseLen[i] = TRUE;
		m_bUseInSulate[i] = TRUE;
		m_bUseInSulate1[i] = FALSE;
		m_bUseMismatch[i] = TRUE;
		m_bNGLen[i] = FALSE;
		m_nNGCount[i] = 0;
		m_dStardLen[i] = 0;
		m_bMismatchBad[i] = FALSE;
		m_dLaneAve[0][i] = 0;//top
		m_dLaneAve[1][i] = 0;//back
		m_nLAneDataCount[i] = 0;
		m_dMismatchAve[i] = 0;
	}

	for(int i=0;i<MAX_CAMERAS;i++)
		fmDummy[i] = new BYTE [CAM_WIDTH*CAM_PATIAL*CAM_PATIAL_FRAME];

	m_defectMap = NULL;
	m_NumPad = NULL;
	m_AlarmDlg = NULL;
	m_SysParam = NULL;
	m_DlgLastData = NULL;
	m_pDlgFullImage = NULL;
	m_pPassword = NULL;
	m_bLotWriteCheck = FALSE;
	m_cis = NULL;	//ljn 추가 
	m_pModelDlg = NULL;
	m_pMeterData = NULL;
	m_ViewImage = NULL;
	for(int i=0;i<15;i++)
		m_strLbLotInfo[i].Format("Defect Info");

	m_dTopScale = 0.0421;

	m_bWaitThread[0]=m_bWaitThread[1]=m_bWaitThread[2]=FALSE;

	for(int i=0;i<6;i++)	for(int j=0;j<CAM_WIDTH_CIS;j++)		m_nLineProjData[i][j] = 0;
	for(int i=0;i<10;i++){m_bLineProj[i] = FALSE;m_bInsulateDefect[i] = FALSE;}

	for(int i=0; i<MAX_DEFECT_COUNT; i++)
		m_nNsysNgCount[i] = 0;	
	m_bSendServerINI = true;
	m_bCoatingOnSignal = false;
	m_dLotChangeIntervalStart = 0.0;
	m_dLotChangeIntervalEnd = 0.0;
	m_dChuckChangeIntervalStart = 0.0;
	m_dChuckChangeIntervalEnd = 0.0;
	m_nOldLotMeter = 0;
	m_strServerModel = _T("");
	m_bIsCoatedImg = false;

	// 카메라 오염알람
	m_nNonCoatStartMeter = 0;
	m_nNonCoatEndMeter = 0;
	m_nCameraDirtCnt = 0;
	m_nCoatingOn = 0;


}

CVisWebView::~CVisWebView()
{
	m_bRun = FALSE;
	m_bAuto = FALSE;


//	KillTimer(TEVENT_LIGHT_CHECK);
//	KillTimer(TEVENT_HDD_SPACE);
//	KillTimer(200);

//	Wait(300);

//	if(m_pTiming)
//		delete m_pTiming;

//	FChain_Close();

}

void CVisWebView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVisWebView)
	DDX_Control(pDX, IDC_STATC_WARNING, m_labelWarning);
	DDX_Control(pDX, IDC_STATIC_NG_INFO, m_labelNGInfo);
	DDX_Control(pDX, IDC_STATISTICS, m_labelStatistics);
	DDX_Control(pDX, IDC_STATIC_RESULT, m_labelResult);
	DDX_Control(pDX, IDC_STATIC_SYS_INFO, m_labelSysInfo);
	DDX_Control(pDX, IDC_DISPLAY, m_ctrlDisplay);
	DDX_Text(pDX, IDC_EDIT_PORTNUM, m_nPortNum);
	DDX_Check(pDX, IDC_CHECK_IMAGE_SAVE, m_bImageSave);
	DDX_Check(pDX, IDC_CK_AUTO, m_bAutoRun);
	DDX_Check(pDX, IDC_CK_SAVE_IMAGE, m_bImageSelect);
	DDX_Text(pDX, IDC_EDIT_NOTINSAREA, m_nNotInsAreaView);
	DDX_Check(pDX, IDC_CK_VIEW_IMAGE, m_bViewImage);
	DDX_Text(pDX, IDC_EDIT_XLINESKIP, m_dXLineSkip);
	DDX_Check(pDX, IDC_CK_SIM, m_bSimmulation);
	DDX_Check(pDX, IDC_CK_LOT, m_bLotSave);
	DDX_Check(pDX, IDC_CK_LOTDEL, m_bLotDel);
	DDX_Text(pDX, IDC_EDIT_SHUTTER, m_nExpose);
	DDX_Text(pDX, IDC_EDIT_TACLINE, m_nTacX);
	DDX_Check(pDX, IDC_BINARY_VIEW, m_bBinaryView);
	DDX_Text(pDX, IDC_EDIT_YLINE, m_nYLine);
	DDX_Check(pDX, IDC_CK_VIEW2, m_bViewTest);
	DDX_Check(pDX, IDC_CK_BLOB, m_bCrossBlobImg);
	DDX_Text(pDX, IDC_EDIT_INSMETHOD, m_nInsMethod);
	DDX_Check(pDX, IDC_CK_VIEW3, m_bViewTest1);
	DDX_Text(pDX, IDC_STATIC_VOLTAGE, m_strVolt);
	DDX_Text(pDX, IDC_STATIC_CELECTRIC, m_strCElect);
	DDX_Text(pDX, IDC_STATIC_ELECTRIC, m_strElect);
	//}}AFX_DATA_MAP
	DDX_Check(pDX, IDC_CHECK_CAMCHANGE, m_bCamChange);
	DDX_Text(pDX, IDC_EDIT_SHUTTER2, m_nExposre1);
	DDX_Text(pDX, IDC_EDIT_YLINE2, m_nYLine1);
	DDX_Check(pDX, IDC_CHECK_IMAGE_SAVE_ALL, m_bImageSaveAll);
	DDX_Control(pDX, IDC_LIST1, m_log2);
	DDX_Text(pDX, IDC_BI_VALUE, m_binaryValue);
	DDX_Text(pDX, IDC_EDIT_SIZE, m_dDefectSize);
	DDX_Text(pDX, IDC_EDIT_THWHITE, m_nThWhite);
	DDX_Text(pDX, IDC_EDIT_THBLACK, m_nThBlack);
	DDX_Text(pDX, IDC_EDIT_SLOPE, m_dSlope);
	DDX_Text(pDX, IDC_EDIT_SCRATCH, m_dLineScratch);
	DDX_Control(pDX, IDC_STATIC_LOT_INFO, m_lbLotInfo);
	DDX_Control(pDX, IDC_STATIC_WINDER1, m_lbWinder1);
	DDX_Control(pDX, IDC_STATIC_WINDER2, m_lbWinder2);

	DDX_Control(pDX, IDC_STATIC_NULL_DRAG, m_lbNullDrag);
	DDX_Control(pDX, IDC_STATIC_NULL_LINE, m_lbNullLine);
	DDX_Control(pDX, IDC_STATIC_NULL_ISLAND, m_lbNullIsland);

	DDX_Control(pDX, IDC_STATIC_COAT_DRAG, m_lbCoatDrag);
	DDX_Control(pDX, IDC_STATIC_COAT_LINE, m_lbCoatLine);
	DDX_Control(pDX, IDC_STATIC_COAT_PINHOLE, m_lbCoatPinHole);

	DDX_Control(pDX, IDC_STATIC_FULL_WIDTH, m_lbFullWidth);

	//coat title
	DDX_Control(pDX, IDC_STATIC_COAT_TITLE1, m_lbCoatTitle[0]);
	DDX_Control(pDX, IDC_STATIC_COAT_TITLE2, m_lbCoatTitle[1]);
	DDX_Control(pDX, IDC_STATIC_COAT_TITLE3, m_lbCoatTitle[2]);
	DDX_Control(pDX, IDC_STATIC_COAT_TITLE4, m_lbCoatTitle[3]);
	DDX_Control(pDX, IDC_STATIC_COAT_TITLE5, m_lbCoatTitle[4]);
	DDX_Control(pDX, IDC_STATIC_COAT_TITLE6, m_lbCoatTitle[5]);
	DDX_Control(pDX, IDC_STATIC_COAT_TITLE7, m_lbCoatTitle[6]);
	DDX_Control(pDX, IDC_STATIC_COAT_TITLE8, m_lbCoatTitle[7]);
	DDX_Control(pDX, IDC_STATIC_COAT_TITLE9, m_lbCoatTitle[8]);
	DDX_Control(pDX, IDC_STATIC_COAT_TITLE10, m_lbCoatTitle[9]);
	DDX_Control(pDX, IDC_STATIC_COAT_TITLE11, m_lbCoatTitle[10]);
	DDX_Control(pDX, IDC_STATIC_COAT_TITLE12, m_lbCoatTitle[11]);
	DDX_Control(pDX, IDC_STATIC_COAT_TITLE13, m_lbCoatTitle[12]);
	DDX_Control(pDX, IDC_STATIC_COAT_TITLE14, m_lbCoatTitle[13]);
	DDX_Control(pDX, IDC_STATIC_COAT_TITLE15, m_lbCoatTitle[14]);
	DDX_Control(pDX, IDC_STATIC_COAT_TITLE16, m_lbCoatTitle[15]);
	DDX_Control(pDX, IDC_STATIC_COAT_TITLE17, m_lbCoatTitle[16]);
	DDX_Control(pDX, IDC_STATIC_COAT_TITLE18, m_lbCoatTitle[17]);
	DDX_Control(pDX, IDC_STATIC_COAT_TITLE19, m_lbCoatTitle[18]);
	DDX_Control(pDX, IDC_STATIC_COAT_TITLE20, m_lbCoatTitle[19]);
	DDX_Control(pDX, IDC_STATIC_COAT_LEN1, m_lbCoatLen[0]);
	DDX_Control(pDX, IDC_STATIC_COAT_LEN2, m_lbCoatLen[1]);
	DDX_Control(pDX, IDC_STATIC_COAT_LEN3, m_lbCoatLen[2]);
	DDX_Control(pDX, IDC_STATIC_COAT_LEN4, m_lbCoatLen[3]);
	DDX_Control(pDX, IDC_STATIC_COAT_LEN5, m_lbCoatLen[4]);
	DDX_Control(pDX, IDC_STATIC_COAT_LEN6, m_lbCoatLen[5]);
	DDX_Control(pDX, IDC_STATIC_COAT_LEN7, m_lbCoatLen[6]);
	DDX_Control(pDX, IDC_STATIC_COAT_LEN8, m_lbCoatLen[7]);
	DDX_Control(pDX, IDC_STATIC_COAT_LEN9, m_lbCoatLen[8]);
	DDX_Control(pDX, IDC_STATIC_COAT_LEN10, m_lbCoatLen[9]);
	DDX_Control(pDX, IDC_STATIC_COAT_LEN11, m_lbCoatLen[10]);
	DDX_Control(pDX, IDC_STATIC_COAT_LEN12, m_lbCoatLen[11]);
	DDX_Control(pDX, IDC_STATIC_COAT_LEN13, m_lbCoatLen[12]);
	DDX_Control(pDX, IDC_STATIC_COAT_LEN14, m_lbCoatLen[13]);
	DDX_Control(pDX, IDC_STATIC_COAT_LEN15, m_lbCoatLen[14]);
	DDX_Control(pDX, IDC_STATIC_COAT_LEN16, m_lbCoatLen[15]);
	DDX_Control(pDX, IDC_STATIC_COAT_LEN17, m_lbCoatLen[16]);
	DDX_Control(pDX, IDC_STATIC_COAT_LEN18, m_lbCoatLen[17]);
	DDX_Control(pDX, IDC_STATIC_COAT_LEN19, m_lbCoatLen[18]);
	DDX_Control(pDX, IDC_STATIC_COAT_LEN20, m_lbCoatLen[19]);
	DDX_Control(pDX, IDC_STATIC_TOP_COAT_LEN1, m_lbCoatLenTop[0]);
	DDX_Control(pDX, IDC_STATIC_TOP_COAT_LEN2, m_lbCoatLenTop[1]);
	DDX_Control(pDX, IDC_STATIC_TOP_COAT_LEN3, m_lbCoatLenTop[2]);
	DDX_Control(pDX, IDC_STATIC_TOP_COAT_LEN4, m_lbCoatLenTop[3]);
	DDX_Control(pDX, IDC_STATIC_TOP_COAT_LEN5, m_lbCoatLenTop[4]);
	DDX_Control(pDX, IDC_STATIC_TOP_COAT_LEN6, m_lbCoatLenTop[5]);
	DDX_Control(pDX, IDC_STATIC_TOP_COAT_LEN7, m_lbCoatLenTop[6]);
	DDX_Control(pDX, IDC_STATIC_TOP_COAT_LEN8, m_lbCoatLenTop[7]);
	DDX_Control(pDX, IDC_STATIC_TOP_COAT_LEN9, m_lbCoatLenTop[8]);
	DDX_Control(pDX, IDC_STATIC_TOP_COAT_LEN10, m_lbCoatLenTop[9]);
	DDX_Control(pDX, IDC_STATIC_TOP_COAT_LEN11, m_lbCoatLenTop[10]);
	DDX_Control(pDX, IDC_STATIC_TOP_COAT_LEN12, m_lbCoatLenTop[11]);
	DDX_Control(pDX, IDC_STATIC_TOP_COAT_LEN13, m_lbCoatLenTop[12]);
	DDX_Control(pDX, IDC_STATIC_TOP_COAT_LEN14, m_lbCoatLenTop[13]);
	DDX_Control(pDX, IDC_STATIC_TOP_COAT_LEN15, m_lbCoatLenTop[14]);
	DDX_Control(pDX, IDC_STATIC_TOP_COAT_LEN16, m_lbCoatLenTop[15]);
	DDX_Control(pDX, IDC_STATIC_TOP_COAT_LEN17, m_lbCoatLenTop[16]);
	DDX_Control(pDX, IDC_STATIC_TOP_COAT_LEN18, m_lbCoatLenTop[17]);
	DDX_Control(pDX, IDC_STATIC_TOP_COAT_LEN19, m_lbCoatLenTop[18]);
	DDX_Control(pDX, IDC_STATIC_TOP_COAT_LEN20, m_lbCoatLenTop[19]);

	DDX_Control(pDX, IDC_STATIC_BAD_INFO1, m_lbDefectInfo[0]);
	DDX_Control(pDX, IDC_STATIC_BAD_INFO2, m_lbDefectInfo[1]);
	DDX_Control(pDX, IDC_STATIC_BAD_INFO3, m_lbDefectInfo[2]);
	DDX_Control(pDX, IDC_STATIC_BAD_INFO4, m_lbDefectInfo[3]);
	DDX_Control(pDX, IDC_STATIC_BAD_INFO5, m_lbDefectInfo[4]);
	DDX_Control(pDX, IDC_STATIC_BAD_INFO6, m_lbDefectInfo[5]);
	DDX_Control(pDX, IDC_STATIC_BAD_INFO7, m_lbDefectInfo[6]);
	DDX_Control(pDX, IDC_STATIC_BAD_INFO8, m_lbDefectInfo[7]);
	DDX_Control(pDX, IDC_STATIC_BAD_INFO9, m_lbDefectInfo[8]);
	DDX_Control(pDX, IDC_STATIC_BAD_INFO10, m_lbDefectInfo[9]);
	DDX_Control(pDX, IDC_STATIC_BAD_INFO11, m_lbDefectInfo[10]);
	DDX_Control(pDX, IDC_STATIC_BAD_INFO12, m_lbDefectInfo[11]);
	DDX_Control(pDX, IDC_STATIC_BAD_INFO13, m_lbDefectInfo[12]);
	DDX_Control(pDX, IDC_STATIC_BAD_INFO14, m_lbDefectInfo[13]);
	DDX_Control(pDX, IDC_STATIC_BAD_INFO15, m_lbDefectInfo[14]);


	DDX_Control(pDX, IDC_LIST2, m_InspLog1);
	DDX_Control(pDX, IDC_STATIC_TOP_COAT_TITLE1, m_lbTopTitle);
	DDX_Control(pDX, IDC_STATIC_MISMATCHTITLE1, m_lbMisMatchTitle);

	DDX_Control(pDX, IDC_STATIC_PITCH_TOL1, m_lPitchTol[0]);
	DDX_Control(pDX, IDC_STATIC_PITCH_TOL2, m_lPitchTol[1]);
	DDX_Control(pDX, IDC_STATIC_PITCH_TOL3, m_lPitchTol[2]);
	DDX_Control(pDX, IDC_STATIC_PITCH_TOL4, m_lPitchTol[3]);
	DDX_Control(pDX, IDC_STATIC_PITCH_TOL5, m_lPitchTol[4]);
	DDX_Control(pDX, IDC_STATIC_PITCH_TOL6, m_lPitchTol[5]);
	DDX_Control(pDX, IDC_STATIC_PITCH_TOL7, m_lPitchTol[6]);
	DDX_Control(pDX, IDC_STATIC_PITCH_TOL8, m_lPitchTol[7]);
	DDX_Control(pDX, IDC_STATIC_PITCH_TOL9, m_lPitchTol[8]);
	DDX_Control(pDX, IDC_STATIC_PITCH_TOL10, m_lPitchTol[9]);
	DDX_Control(pDX, IDC_STATIC_PITCH_TOL11, m_lPitchTol[10]);
	DDX_Control(pDX, IDC_STATIC_PITCH_TOL12, m_lPitchTol[11]);
	DDX_Control(pDX, IDC_STATIC_PITCH_TOL13, m_lPitchTol[12]);
	DDX_Control(pDX, IDC_STATIC_PITCH_TOL14, m_lPitchTol[13]);
	DDX_Control(pDX, IDC_STATIC_PITCH_TOL15, m_lPitchTol[14]);
	DDX_Control(pDX, IDC_STATIC_PITCH_TOL16, m_lPitchTol[15]);
	DDX_Control(pDX, IDC_STATIC_PITCH_TOL17, m_lPitchTol[16]);
	DDX_Control(pDX, IDC_STATIC_PITCH_TOL18, m_lPitchTol[17]);
	DDX_Control(pDX, IDC_STATIC_PITCH_TOL19, m_lPitchTol[18]);
	DDX_Control(pDX, IDC_STATIC_PITCH_TOL20, m_lPitchTol[19]);

	DDX_Check(pDX, IDC_CHECK_ALARM_OFF, m_bAlarmOff);
	DDX_Control(pDX, IDC_STATIC_LEFT, m_lbLeft);
	DDX_Control(pDX, IDC_STATIC_RIGHT, m_lbRight);
	DDX_Control(pDX, IDC_STATIC_MISMATCHTOL1, m_lbMismatchTolMin);
	DDX_Control(pDX, IDC_STATIC_MISMATCHTOL2, m_lbMismatchTolMax);

	DDX_Control(pDX, IDC_STATIC_STATS_IO, m_lbStatsIO);
	DDX_Control(pDX, IDC_STATIC_STATS_CAM, m_lbStatsCAM);
	DDX_Control(pDX, IDC_STATIC_STATS_PLC, m_lbStatsPLC);



	DDX_Control(pDX, IDC_STATIC_GAPMISMATCH1, m_lbGapMisMatch[0]);
	DDX_Control(pDX, IDC_STATIC_GAPMISMATCH2, m_lbGapMisMatch[1]);
	DDX_Control(pDX, IDC_STATIC_GAPMISMATCH3, m_lbGapMisMatch[2]);
	DDX_Control(pDX, IDC_STATIC_GAPMISMATCH4, m_lbGapMisMatch[3]);
	DDX_Control(pDX, IDC_STATIC_GAPMISMATCH5, m_lbGapMisMatch[4]);
	DDX_Control(pDX, IDC_STATIC_GAPMISMATCH6, m_lbGapMisMatch[5]);
	DDX_Control(pDX, IDC_STATIC_GAPMISMATCH7, m_lbGapMisMatch[6]);
	DDX_Control(pDX, IDC_STATIC_GAPMISMATCH8, m_lbGapMisMatch[7]);
	DDX_Control(pDX, IDC_STATIC_GAPMISMATCH9, m_lbGapMisMatch[8]);
	DDX_Control(pDX, IDC_STATIC_GAPMISMATCH10, m_lbGapMisMatch[9]);
	DDX_Control(pDX, IDC_STATIC_GAPMISMATCH11, m_lbGapMisMatch[10]);
	DDX_Control(pDX, IDC_STATIC_GAPMISMATCH12, m_lbGapMisMatch[11]);
	DDX_Control(pDX, IDC_STATIC_GAPMISMATCH13, m_lbGapMisMatch[12]);
	DDX_Control(pDX, IDC_STATIC_GAPMISMATCH14, m_lbGapMisMatch[13]);
	DDX_Control(pDX, IDC_STATIC_GAPMISMATCH15, m_lbGapMisMatch[14]);
	DDX_Control(pDX, IDC_STATIC_GAPMISMATCH16, m_lbGapMisMatch[15]);
	DDX_Control(pDX, IDC_STATIC_GAPMISMATCH17, m_lbGapMisMatch[16]);
	DDX_Control(pDX, IDC_STATIC_GAPMISMATCH18, m_lbGapMisMatch[17]);
	DDX_Control(pDX, IDC_STATIC_GAPMISMATCH19, m_lbGapMisMatch[18]);
	DDX_Control(pDX, IDC_STATIC_GAPMISMATCH20, m_lbGapMisMatch[19]);

	DDX_Control(pDX, IDC_STATIC_BACKTOPGAP, m_lbStaticTBGap);


	DDX_Check(pDX, IDC_CHECK_INSUL, m_bInsulateInspect);
	DDX_Control(pDX, IDC_STATIC_NONCOATING, m_lbNonCoating);
	DDX_Check(pDX, IDC_CHECK_PRIMER, m_bPrimer);

	//20201017 kjh
	DDX_Control(pDX, IDC_STATIC_LAST_DATA_COAT, m_lbLastDataCoat);
	DDX_Control(pDX, IDC_STATIC_LAST_DATA_NCOAT, m_lbLastDataNCoat);

}

BOOL CVisWebView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

BOOL CVisWebView::OnTestFunction(LPBYTE fmLeft,int nCam)
{
	 int i,j =0;
	 CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	 BOOL nRet = 1;
	 static int nc= 0;
	 static int nc1= 0;
	 int nheight = 0;
	 int nwidth = 0; 

	 unsigned char* fmImg;
	 unsigned char* fmNgImg;
 	 unsigned char* fmImg1;
	 unsigned char* fmNgImg1;
  
	 unsigned char* fmDspImg;
	 unsigned char* fmDspImg1;

	 CString str1;

	 
	 if(nCam == 0){
		 nheight= pDoc->m_pImageHeight;//pDoc->m_pImage->GetHeight();
		 nwidth = pDoc->m_pImageWidth;//pDoc->m_pImage->GetWidth();
		 

		 fmImg = pDoc->m_pImagePtr;//pDoc->m_pImage->GetImagePtr();
		 fmNgImg = pDoc->m_pImageNGPtr;//pDoc->m_pImageNG->GetImagePtr();
		 fmDspImg = pDoc->m_pImageDspPtr;//pDoc->m_pImageDsp->GetImagePtr();

	 }
	 else{
		 nheight= pDoc->m_pImage1Height;//pDoc->m_pImage1->GetHeight();
		 nwidth = pDoc->m_pImage1Width;//pDoc->m_pImage1->GetWidth();
		 

		 fmImg1 = pDoc->m_pImage1Ptr;//pDoc->m_pImage1->GetImagePtr();
		 fmNgImg1 = pDoc->m_pImageNG1Ptr;//pDoc->m_pImageNG1->GetImagePtr();
		 fmDspImg1 = pDoc->m_pImageDsp1Ptr;//pDoc->m_pImageDsp1->GetImagePtr();

	 }
	 

	 CTimingProcess* timer = ((CVisWebApp*)AfxGetApp())->m_pTiming;
	 int y=0,y1=0,yy1;// = (m_nGrabFrame[nCam]-1)%2;
	 yy1 = (m_nGrabFrame[nCam]-1)%NUM_BUFFERS;

	 //m_nGrabFrame 1, 2, 3 순서로 들어옴
	 if( (m_nGrabFrame[nCam]-1)%NUM_BUFFERS==0)
		 y = 0;
	 else
		 y = CAM_PATIAL *yy1 ;

	 //y는 0, 1, 2 순서로 1,2 체인지
	 //if(y==1)
	 // y = 2;
	 //else if(y==2)
	 // y=1;
	 DWORD dwStart;


	 if(pDoc->m_data.m_nInspDirection[nCam] == 2 ||pDoc->m_data.m_nInspDirection[nCam] == 3)// && pDoc->m_data.m_nMachine==1)
	 {//coating
		 dwStart = GetTickCount();
		 str1.Format("[%d]%s%d_%d\n",dwStart, "Grab_Cam_St_", nCam, yy1);
		 staticString += str1;
		 j = y+CAM_PATIAL;
		 for(i=0;i<CAM_PATIAL;i++)
		 {//y1 = y+i;
			 //if(j%HEIGHT == 0) j = 0;
			 //npos = (i/CAM_PATIAL)+1;
			 //k = ((npos*CAM_PATIAL) - j)-1;
			 y1 = j-i;
			 if(nCam==0){
				 memcpy(fmDummy[nCam]+nwidth*y1, fmLeft+WIDTH*i, WIDTH);
				 //				memcpy(fmImg+nwidth*y1, fmLeft+WIDTH*i, WIDTH);


				 ////				memcpy(fmNgImg+nwidth*y1, fmLeft+WIDTH*i, WIDTH);
			 }
			 else
			 {
				 memcpy(fmDummy[nCam]+nwidth*y1, fmLeft+WIDTH*i, WIDTH);
				 //				memcpy(fmImg1+nwidth*y1, fmLeft+WIDTH*i, WIDTH);


				 //				memcpy(fmNgImg1+nwidth*y1, fmLeft+WIDTH*i, WIDTH);
			 }
			 //			j++;
		 }
		
		 dwStart = GetTickCount();
		 str1.Format("[%d]%s%d_%d\n",dwStart, "Grab_Cam_End", nCam, yy1);
		 staticString += str1;
	 }
	 else{
		 for(i=0;i<CAM_PATIAL;i++){
			 y1 = y+i;
			 if(nCam==0){
				 memcpy(fmImg+nwidth*y1, fmLeft+WIDTH*i, WIDTH);
			 }
			 else{
				 memcpy(fmImg1+nwidth*y1, fmLeft+WIDTH*i, WIDTH);
			 }
		 }
	 }

	 if(pDoc->m_data.m_nMachine==1){
	 }
	 else
	 {//1frame
		 /*dwStart = GetTickCount();
		 str1.Format("[%d]%s%d\n",dwStart, "Grab_Copy_", nCam);
		 staticString += str1;*/
		 if(nCam==0)
			 memcpy(fmNgImg,fmImg,WIDTH*CAM_PATIAL);
		 else
			 memcpy(fmNgImg1,fmImg1,WIDTH*CAM_PATIAL);

	 }

	 nRet = 1;

	 int nf = 0;
	 if(NUM_BUFFERS>1)nf = 2;
	 if(nCam==0 && (m_nGrabFrame[nCam]-1)%NUM_BUFFERS==nf ){
		 if(nc%10==0 && nCam==0)
		 {
			/* m_img_save_time = timer->GetTimer(TIMING_IDX_TEST_GRAB);
			 m_fFps = float(10000 / m_img_save_time);
			 timer->SetTimer(TIMING_IDX_TEST_GRAB);*/
		 }
		 dwStart = GetTickCount();
		 str1.Format("[%d]%s%d\n",dwStart, "Grab_Copy_st_", nCam);
		 staticString += str1;
		 staticString += "1 func\n";

		 memcpy(fmImg,fmDummy[nCam],WIDTH*CAM_PATIAL*NUM_BUFFERS);
		 memcpy(fmNgImg,fmImg,WIDTH*CAM_PATIAL*NUM_BUFFERS);

		  dwStart = GetTickCount();
		 str1.Format("[%d]%s%d\n",dwStart, "Grab_Copy_do_", nCam);
		 staticString += str1;

		 if(!m_bViewTest){
			 //memcpy(pDoc->m_pImageDsp->GetImagePtr(),pDoc->m_pImageNG->GetImagePtr(),pDoc->m_pImageNGWidth*pDoc->m_pImageNGHeight);
			 memcpy(pDoc->m_pImageDspPtr,pDoc->m_pImageNGPtr, pDoc->m_pImageNGWidth * pDoc->m_pImageNGHeight);
		 }
		 //m_ev_Inspect.SetEvent();
		

		 g_frame_num++;

		 nc++;
	 }
	 else if(nCam==1 && (m_nGrabFrame[nCam]-1)%NUM_BUFFERS==nf)
	 {
		 dwStart = GetTickCount();
		 str1.Format("[%d]%s%d\n",dwStart, "Grab_Copy_st_", nCam);
		 staticString += str1;
		 staticString += "2 func\n";

		 memcpy(fmImg1,fmDummy[nCam],WIDTH*CAM_PATIAL*NUM_BUFFERS);
		 memcpy(fmNgImg1,fmImg1,WIDTH*CAM_PATIAL*NUM_BUFFERS);
		 
		  dwStart = GetTickCount();
		 str1.Format("[%d]%s%d\n",dwStart, "Grab_Copy_do_", nCam);
		 staticString += str1;


		 if(!m_bViewTest){
			 //memcpy(pDoc->m_pImageDsp1->GetImagePtr(),pDoc->m_pImageNG1->GetImagePtr(),pDoc->m_pImageNG1Width*pDoc->m_pImageNG1Height);
			 memcpy(pDoc->m_pImageDsp1Ptr, pDoc->m_pImageNG1Ptr, pDoc->m_pImageNG1Width * pDoc->m_pImageNG1Height);
		 }

//		 m_ev_Inspect1.SetEvent();
		
		 nc1++;
	 }
	 return nRet;
}

void CVisWebView::OnInitialUpdate()
{
	
	CFormView::OnInitialUpdate();

// 	CMenu * menu = this->GetSystemMenu(FALSE);
// 	menu->RemoveMenu(SC_CLOSE,MF_BYCOMMAND);

	m_DispFont.CreatePointFont(180,"굴림");
	GetDlgItem(IDC_CHECK_ALARM_OFF)->SetFont(&m_DispFont);
	GetDlgItem(IDC_CHECK_INSUL)->SetFont(&m_DispFont);
	GetDlgItem(IDC_CHECK_PRIMER)->SetFont(&m_DispFont);

	GetDlgItem(IDC_BT_ALARM_SET)->SetFont(&m_DispFont);
	GetDlgItem(IDC_BUTTON_RESETIMAGE)->SetFont(&m_DispFont);
	

	

	GetDlgItem(IDC_CHECK_AUTO)->SetFont(&m_DispFont);
	GetDlgItem(IDC_BUTTON_INTERFACE)->SetFont(&m_DispFont);
	GetDlgItem(IDC_BUTTON_EXIT)->SetFont(&m_DispFont);
	GetDlgItem(IDC_BTN_GET_PROFILE)->SetFont(&m_DispFont);
	GetDlgItem(IDC_BTN_WIDTH_DATA)->SetFont(&m_DispFont);

	m_DispFont1.CreatePointFont(200,"휴먼둥근헤드라인");
	GetDlgItem(IDC_NETWORK_TEST)->SetFont(&m_DispFont1);

	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	m_bNewMode = 1;


	m_strModelPath.Format("c:\\Glim\\Model\\");
	pDoc->m_data.m_bUseCLog=FALSE;

	if(pDoc->m_data.m_bUseCLog==FALSE){
		CString strpath;
		strpath.Format("D:\\Data\\");
		CreateDirectory(strpath,NULL); 
		strpath.Format("D:\\Data\\LotData\\");
		CreateDirectory(strpath,NULL); 
	}
	

	ShellExecute(NULL,"open","c:\\Glim\\ControlCommunication.exe",NULL,NULL,SW_SHOWMINIMIZED);
	int nPcNo;
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	CRect rcDest;
	GetDlgItem(IDC_DISPLAY)->GetWindowRect(rcDest);

	m_ctrlDisplay.MoveWindow(0,0,rcDest.Width(),rcDest.Height());

	InitSystemInfo();//computername & version
	//설비명 컴퓨터 이름으로 각 라인 설정

	// 
 	pDoc->m_data.m_nVisionLine =nPcNo= pDoc->m_data.GetVisionLine(0);//chcho
	
	InitClass();
	pDoc->m_pDlgInterface->LoadSysParam();
	for(int i=0;i<MAX_CAMERAS;i++)
	pDoc->m_data.m_nComPort[i] = (atoi(m_strComputerName.Right(3))*10+(i));
	pDoc->m_data.m_nCameraWidth = CAM_WIDTH_CIS;
	pDoc->m_data.m_nCameraHeight = CAM_HEIGHT_CIS;

	m_nCamPort=9;
	m_nIOPort = 4;
	m_nCamPort = ReadPort("CAM");
	m_nIOPort = ReadPort("IO");
	
//m_pImageDsp//@1412
	int ncam1 = InitCamera(pDoc->m_data.m_nVisionLine);
	//Main Display
	InitCimage(pDoc->m_data.m_nVisionLine);
//init grid
	pDoc->m_pDlgInterface->m_bImageShowHide = TRUE;
	InitControl();//label init
	CreateDefaultDirectory();

	SetPriorityClass(::AfxGetInstanceHandle(), REALTIME_PRIORITY_CLASS);
	InitThread(pDoc->m_data.m_nVisionLine);//Split Count 
	////////////////////////////////////////////////////
//Network Init
// Timing Process
	m_pTiming = new CTimingProcess;
	m_pTiming->initialize_timer(Clock_set, Clock_set);

// Load Default Calibration Data
//	pDoc->m_pDlgInterface->LoadSysParam();


	pDoc->m_pDlgInterface->UpdateData(false);	
	UpdateData(FALSE);

	fnReadSkipPixel(0);

	Wait(10);
	LightChange(m_bInsulateInspect);

//	UpdateIni()
	ReaModel();// Read Model name 
	UpdateTolIni(pDoc->m_data.m_strDefaultModel);
	pDoc->m_pDlgInterface->LoadInsParam();
	pDoc->m_pDlgInterface->LoadSysParam();//sparam을 사용해야한다.
	pDoc->m_pDlgInterface->	LoadLightParam();

	CString strmodel;
	strmodel.Format("Model:\r\n %s", pDoc->m_data.m_strDefaultModel);
	SetDlgItemText(IDC_NETWORK_TEST,strmodel);
	m_pModelDlg->m_strSelectProduct = pDoc->m_data.m_strDefaultModel;
	m_pModelDlg->UpdateData(FALSE);
	pDoc->m_pDlgInterface->UpdateData(FALSE);	


	m_defectMap->DrawModel(strmodel);
	if(m_strComputerName.Find("BACK")>=0 || pDoc->m_data.m_strComName.Mid(9,1)=="B"){//마지막 2
		CString str1;
		if(pDoc->m_pDlgInterface->m_bEngKor)
			str1.Format("MIN-%.2f",m_dMismatchTolMin);
		else
			str1.Format("최소-%.2f",m_dMismatchTolMin);
		m_lbMismatchTolMin.SetText(str1);
		if(pDoc->m_pDlgInterface->m_bEngKor)
			str1.Format("MAX+%.2f",m_dMismatchTolMax);
		else
			str1.Format("최대+%.2f",m_dMismatchTolMax);
		m_lbMismatchTolMax.SetText(str1);
	}
	else{

		
	}


	//SetTimer(11235,1000,NULL);//test
	CTime time = CTime::GetCurrentTime();
	CString kk = time.Format("%y%m%d%H");

// image id   //0 hts 1hbs 2ht 3hb 4mt 5mb
	if(m_strComputerName.Mid(8,1)=="H"){
		if(m_strComputerName.Mid(9,1)=="T")
			pDoc->m_data.m_nCamID = 2;
		else
			pDoc->m_data.m_nCamID = 3;
	}
	else{
		if(m_strComputerName.Mid(9,1)=="T")
			pDoc->m_data.m_nCamID = 4;
		else
			pDoc->m_data.m_nCamID = 5;
	}

	//양극 음극 구분
	CString str16;
	m_nMachine = pDoc->m_data.m_nMachine ;
	CString strtmp1 = pDoc->m_data.m_strLineSelect.Mid(1,1);
	if(pDoc->m_data.m_strLineSelect.Mid(1,1)=="1"){//>0){//A 1 C 2
		m_nMachine = 0;//음극  //양극
	}
	else{
		 m_nMachine = 1;//양극 //음극
	}

	if(m_nMachine==0){
		str16.Format("LineNo. Anode,%s",m_strComputerName);//음극
		m_DlgLastData->ControlInit(0);		
	}
	else{
		str16.Format("LineNo. Cathode,%s",m_strComputerName);//양극
		m_DlgLastData->ControlInit(1);		
	}
	if(pDoc->m_pDlgInterface->m_bAutoCoatBrightness)
		pDoc->m_pDlgInterface->ShowHideButton(0);
	else
		pDoc->m_pDlgInterface->ShowHideButton(1);


	CString str15;
	str15.Format("Com:%d Machine:%d",pDoc->m_data.m_nLineSelect,m_nMachine);
	AddtoList(str15,0);

	
	m_nTacX = pDoc->m_data.m_nTacXpos[0];

	//Camera exposure
// 	InitExposure(0,pDoc->m_data.m_nVisionLine,m_nExpose);
// 	if(MAX_CAMERAS>1)
// 		InitExposure(1,pDoc->m_data.m_nVisionLine,m_nExposre1);
// 	if(MAX_CAMERAS>2)
// 		InitExposure(21,pDoc->m_data.m_nVisionLine,m_nExposre2);
	m_Inspect.InitInspect( pDoc->m_data.m_nVisionLine);
	InitSocket(pDoc->m_data.m_nVisionLine);
	InitTimer(pDoc->m_data.m_nVisionLine);	//조명check
	InitData(pDoc->m_data.m_nVisionLine);

	SetShareMemory();

//	for(int i=0;i<MAX_CAMERAS;i++)
//		ReadCalData(i);

	pDoc->m_data.m_nRecude = 1;
	int nIo = InitIO();//0 불량 1 ok

//I/O camera check
	CheckStats(ncam1,nIo);//홀수 녹색 짝수 빨강

	pDoc->m_data.m_bBlobImg = pDoc->m_pDlgInterface->m_bBlobImgShow;


	pDoc->m_data.m_strLot = ConvertCharToStr(cLotID);
	UpdateData(false);
	
	if(!pDoc->m_pDlgInterface->m_bImageShowHide)
		m_bDrawCheck = FALSE;
///sim mode
 	if( m_strComputerName.Find("CHO")>=0 || pDoc->m_pDlgInterface->m_bAging || pDoc->m_pDlgInterface->m_bMasterPc){
 		SetTimer(20213,1000,NULL);
 	}
	if(m_strComputerName.Mid(8,1) == "H")
		GetDlgItem(IDC_BTN_GET_PROFILE)->ShowWindow(0);
	
	m_lbTopTitle.ShowWindow(0);

	CTime ttime = CTime::GetCurrentTime();
	CString strTime = ttime.Format("%Y-%m-%d-%H:%M:%S");
	m_strStartTime =strTime;
	
	m_dLenthSum = 0;m_nLnethCnt=0;
	m_dNewScaleX = pDoc->m_data.m_dScaleFactorX[0];

	pDoc->m_data.m_nFullimage = 1;

	pDoc->m_data.m_bPreprocessing = pDoc->m_pDlgInterface->m_bPreprocessing;
	AddtoList(str16,0);
	AddtoList("Pgm On",0);
	OffsetCheck();

	OnCheckAuto();
	SetTimer(TIMER_UPDATESTATICS,1000,NULL);

//	SetTimer(20134,1000*15,NULL);//capture

	if(m_strComputerName.Mid(7,1)=="A"){
		GetDlgItem(IDC_CHECK_INSUL)->ShowWindow(0);
		pDoc->m_pDlgInterface->ShowItem(0);
	}
	if(pDoc->m_pDlgInterface->m_bAutoCoatBrightness)
		pDoc->m_pDlgInterface->ShowHideButton(!pDoc->m_pDlgInterface->m_bAutoCoatBrightness);

	GetDlgItem(IDC_BTN_WIDTH_DATA)->ShowWindow(pDoc->m_pDlgInterface->m_bLastData);


	if(m_SysParam->m_bAlarm==FALSE){
		m_bAlarmOff = TRUE;
		UpdateData(FALSE);
	}
	else{
		m_bAlarmOff = FALSE;
		UpdateData(FALSE);
	}
	//Check offset
	if(pDoc->m_pDlgInterface->m_bPlcWrite)
		WriteShareMemorySpec();

	m_bPassCheck = TRUE;
	// set language
	pDoc->m_pDlgInterface->OnBnClickedCheckEngKor();


	pDoc->m_pDlgInterface->m_bLineAve = FALSE;


//	if(pDoc->m_pDlgInterface->m_bAutoBrightness)
	{
		pDoc->m_pDlgInterface->ChangeBrightness(55,0,20);
		Wait(200);
		pDoc->m_pDlgInterface->ChangeBrightness(55,0,40);
		Wait(200);
		pDoc->m_pDlgInterface->ChangeBrightness(pDoc->m_pDlgInterface->m_nLightOnTime,0,60);
		Wait(200);
	}

	
	AfxBeginThread(ThreadCameraCheck, this,THREAD_PRIORITY_NORMAL,0);


	// 통합서버 parameter ini파일
	WriteINIFileForServer();	// kjh 200710
	CreateINICheckFile();
	AddtoList("Write Server INI File!", FALSE);

	SetTimer(WM_TIMER_CHECK_SERVER_INI_RECEIVE, 1000, NULL);
	//SetTimer(TIMER_PGM_STATUS, 1000, NULL);

	// MISMATCH 화면 DISPLAY
	if(m_strComputerName.Find(_T("CMI"))>=0 && m_strComputerName.Mid(8,1)=="M"){
		if(m_defectMap->IsWindowVisible()){//m_bMismatchView
			m_defectMap->ShowWindow(SW_HIDE);
			m_bMismatchView = FALSE;
		}
		else{
			m_defectMap->ShowWindow(SW_SHOW);
			m_bMismatchView = TRUE;
		}
	}

	pDoc->m_pDlgInterface->m_bLastData = TRUE;
	pDoc->m_pDlgInterface->UpdateData(FALSE);
	ShowLogControls(pDoc->m_pDlgInterface->m_bShowLog);	// 20201016 kjh

}


void CVisWebView::OffsetCheck()
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	//file 유무 체크
	CFileFind finder;
	BOOL IsFind;
	CString filename,str;
	filename.Format("c:\\Melsec\\Model\\%s_Off.txt",pDoc->m_data.m_strDefaultModel);
	for(int k=0;k<3;k++){
		for(int i=0;i<20;i++){
			pDoc->m_data.m_dOffsetData[k][i]=0;
		}
	}
	IsFind = finder.FindFile(filename);
	if(IsFind){
		//옵셋 불러오기
		CStdioFile   file;
	 	if(file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
	 	{	
			for(int i=0;i<20;i++){
				file.ReadString(str);
				if(str=="")		break;
				if(str=="0"){

				}
				else{
					double dtmp = atof(str);
					double dtmp1 = dtmp / pDoc->m_data.m_dScaleFactorX[0];
					pDoc->m_data.m_dOffsetData[0][i] =dtmp1;//pixel
					pDoc->m_data.m_dOffsetData[1][i] =dtmp;//mm
				}
	
			}
			file.Close(); 
	 	}
	}
	// 	if(!IsFind)	
	// 		pDoc->m_data.m_nGradeUse = 0;
	// 	else
	// 		pDoc->m_data.m_nGradeUse = 1;
	finder.Close();

}

/////////////////////////////////////////////////////////////////////////////
// CVisWebView printing
void CVisWebView::fnSaveThreadInit()
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

//	AfxBeginThread(ThreadSaveImage1, this,THREAD_PRIORITY_NORMAL,0);
//	if(pDoc->m_data.m_nVisionLine==GL9)
//		AfxBeginThread(ThreadSaveImage2, this,THREAD_PRIORITY_NORMAL,0);
/*	AfxBeginThread(ThreadSaveImage3, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadSaveImage4, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadSaveImage5, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadSaveImage6, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadSaveImage7, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadSaveImage8, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadSaveImage9, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadSaveImage10, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadSaveImage11, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadSaveImage12, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadSaveImage13, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadSaveImage14, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadSaveImage15, this,THREAD_PRIORITY_NORMAL,0);
	*/
}

BOOL CVisWebView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CVisWebView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CVisWebView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CVisWebView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CVisWebView diagnostics

#ifdef _DEBUG
void CVisWebView::AssertValid() const
{
	CFormView::AssertValid();
}

void CVisWebView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CVisWebDoc* CVisWebView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVisWebDoc)));
	return (CVisWebDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVisWebView message handlers

void CVisWebView::OnDraw(CDC* pDC) 
{
//	UpdateData();

	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	CRect rcDIB, rcDest,rcDest1,rcDest2;
	if(m_bViewTest)
		m_bViewTest = m_bViewTest;

	CRect rcDest3;


	if(m_bViewTest )
	{
		CRect rcMain;
		GetWindowRect(rcMain);
		//전체화면 이미지 사이즈
		GetDlgItem(IDC_DISPLAY)->GetWindowRect(rcDest);
		GetDlgItem(IDC_DISPLAY2)->GetWindowRect(rcDest1);
		GetDlgItem(IDC_DISPLAY3)->GetWindowRect(rcDest2);
		GetDlgItem(IDC_DEFECT_MAP)->GetWindowRect(rcDest3);

		rcDest.OffsetRect(-rcMain.left,-rcMain.top);	
		rcDest1.OffsetRect(-rcMain.left,-rcMain.top);	
		rcDest2.OffsetRect(-rcMain.left,-rcMain.top);	
		rcDest3.OffsetRect(-rcMain.left,-rcMain.top);

		
		static bool m_bFirst = true;
		if(m_bFirst){
			m_bFirst = false;
			GetDlgItem(IDC_DETAIL_LINE)->GetWindowRect(m_rtDetailView);
			m_rtDetailView.OffsetRect(-rcMain.left,-rcMain.top);
		}

		//m_defectMap->ShowWindow(SW_SHOW);
		{
			if(!pDoc->m_pImage->IsDataNull())
			{		
				rcDIB.top = 0;
				rcDIB.left = 0;
				rcDIB.right = pDoc->m_pImage->GetWidth();
				rcDIB.bottom = pDoc->m_pImage->GetHeight();

				double dScale = 1;

				pDoc->m_pImage->Draw(pDC->m_hDC,&rcDIB,&rcDest);
				if(MAX_CAMERAS>1){
					pDoc->m_pImage1->Draw(pDC->m_hDC,&rcDIB,&rcDest1);
				}
				if(MAX_CAMERAS>2){
					pDoc->m_pImage2->Draw(pDC->m_hDC,&rcDIB,&rcDest2);
				}

			}
		}
	}
	DrawNGImage(pDC,m_nSelectCam);
	DrawData(pDC,m_nSelectCam);
}

void CVisWebView::OnImageLoad() 
{
	LoadImage();

}

void CVisWebView::OnImageSave() 
{
	SaveImage();	
}

void CVisWebView::OnCheckAuto() 
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	m_bDraw = TRUE;
	m_bTest1 = TRUE;
	m_nRestartSkipFrame = 0;
	m_nSaveNgCode = 0;
	for(int i=0;i<20;i++){	for(int j=0;j<2;j++)			m_ptLinePos[i][j].SetPoint(0,0);}//0301}
	for(int i=0;i<20;i++){	
		m_nUsecheck[i] = -1;
	}


	m_bNonCoat[1] = m_bNonCoat[0] = FALSE;
	if(m_bNewMode==0)
		m_Inspect.m_rtBound.SetRect(0,1,CAM_WIDTH_CIS,CAM_HEIGHT_CIS);
	else
		m_Inspect.m_rtBound.SetRect(0,1,CAM_WIDTH_CIS*3,CAM_HEIGHT_CIS);

	if(pDoc->m_pDlgInterface->m_nDefectMag>1){
		if(m_bNewMode==0)
			m_Inspect.m_rtBound.SetRect(0,-32,CAM_WIDTH_CIS,CAM_HEIGHT_CIS+32);
		else 
			m_Inspect.m_rtBound.SetRect(0,-32,CAM_WIDTH_CIS*3,CAM_HEIGHT_CIS+32);
	}

	m_nLastBrightness[0]=m_nLastBrightness[1]=m_nLastBrightness[2] = 0;
	m_nStartSkipFrame[0]=m_nStartSkipFrame[1]=m_nStartSkipFrame[2]= -1;
	UpdateData();
	m_nGrabFrame[0] = m_nGrabFrame[1] = 0;
	m_nNewAlarm = 0;
	m_bNewAlarm = FALSE;
	m_nInspBreak[0] = m_nInspBreak[1] = m_nInspBreak[2] = 0;
	for(int i=0;i<5;i++)
		pDoc->m_data.m_nLaneDefectCount[i][0]=pDoc->m_data.m_nLaneDefectCount[i][1]=0;

	m_nLineCountMiss = 0;

	for(int i=0;i<MAX_LENGTH;i++)
		pDoc->m_data.m_nLanePos[i][0]=pDoc->m_data.m_nLanePos[i][1] = 0;

	m_nInspFrame[0]=m_nInspFrame[1] = 0;
	/////chcho
	m_nOldEdgeCount = 0;
	pDoc->m_data.m_nFoilEdge[0]=pDoc->m_data.m_nFoilEdge[1]=0;
	pDoc->m_data.m_nFoilEdgeOld[0]=pDoc->m_data.m_nFoilEdgeOld[1]=0;

	m_bCopyFile1 = FALSE;

	pDoc->m_data.m_strLot = ConvertCharToStr(cLotID);
	if(m_bAuto)
	{
		m_bAuto = FALSE;
		fnDispButton(0);	//Write Reset Data//200805 - 13
		Wait(10);
		AddtoList("Auto Insp. Stop!",0);		

		WriteModel();
		m_nDataMissing = 0;
	
		pDoc->m_pVision->HookStop();
		for(int i=0;i<MAX_REALDEFECT;i++)
			pDoc->m_data.m_strDefectName[0][i] = pDoc->m_data.m_strDefectName[1][i] = "";

		if(pDoc->m_pDlgInterface->m_bEngKor == ENG)
			SetDlgItemText(IDC_CHECK_AUTO,"START");
		else if(pDoc->m_pDlgInterface->m_bEngKor == KOR)
			SetDlgItemText(IDC_CHECK_AUTO,"자동검사");

	}
	else
	{
//		SetTimer(12011,1000,NULL);//화면 리프레시
		m_bAuto = TRUE;
		fnDispButton(1);	//Write Reset Data//200805 - 13
		AddtoList("Auto Insp. Start!",0);
		m_dNewScaleX = pDoc->m_data.m_dScaleFactorX[0];
		for(int i1=0;i1<MAX_CAMERAS;i1++)
			m_nSkipFrame[i1] = 1000;
		for(int n =0;n<10;n++)
			for(int k =0;k<MAX_LENGTH;k++)
				pDoc->m_data.m_dLineAve[n][k] = 0;

		pDoc->m_pVision->HookStart();
		m_nDataMissing = 0;
		m_nAlarmOn = 0;
		m_strOldFilename = "";
		m_strOldFilename1 = "";
		m_strAlarmMsg = "";
		m_strAlarmMsg1 = "";
		for(int i=0;i<10;i++)
			pDoc->m_data.m_nBadTypeCount[i] = 0;

		if(pDoc->m_pDlgInterface->m_bServerDataSend)
			SetTimer(23689,1000,NULL);//		WriteLotModel(m_strLotID);

		if(pDoc->m_pDlgInterface->m_bEngKor == ENG)
			SetDlgItemText(IDC_CHECK_AUTO,"STOP");
		else if(pDoc->m_pDlgInterface->m_bEngKor == KOR)
			SetDlgItemText(IDC_CHECK_AUTO,"검사중지");
	}
	Invalidate();	
}

void CVisWebView::AutoStart()
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	if(!m_bAuto)
	{		
		OnCheckAuto();
	}
	else
	{
	}
}

void CVisWebView::AutoStop()
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	if(m_bAuto)
	{
		OnCheckAuto();	
	}
}

void CVisWebView::AutoStartE()
{

	if(!m_bAuto)
	{		
		OnCheckAuto();	
	}
}

void CVisWebView::AutoStopE()
{
	if(m_bAuto)
	{
		OnCheckAuto();	
	}
}

//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Operations
void CVisWebView::LoadImage()
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
//	CFileDialog dlg(TRUE, "bmp", NULL, OFN_SHAREAWARE, "Bitmap Files (*.bmp)|*.bmp||");
	CFileDialog dlg(TRUE, "bmp", NULL, OFN_SHAREAWARE, "Bitmap Files (*.*)|*.*||");

	if(dlg.DoModal() == IDOK)
	{
		CString str = dlg.GetPathName();
		{

			if(str.Find("BMP")>=0){
				if(!pDoc->m_pImage->IsDataNull())	
					pDoc->m_pImage->Free();
				if(!pDoc->m_pImageNG->IsDataNull())	
					pDoc->m_pImageNG->Free();
				if(!pDoc->m_pImageDsp->IsDataNull())	
					pDoc->m_pImageDsp->Free();

				pDoc->m_pImage->Load(str);
				pDoc->m_pImageNG->Load(str);
				pDoc->m_pImageDsp->Load(str);

			}
			else{
				pDoc->m_pImage->Load(str);

			}


		}
		int nPcNo= pDoc->m_data.GetVisionLine(0);//chcho

		//20150706 ljh CImage Setting Expention
		pDoc->m_pImageWidth = pDoc->m_pImage->GetWidth();
		pDoc->m_pImageBadWidth = pDoc->m_pImageBad->GetWidth();
		pDoc->m_pImageNGWidth = pDoc->m_pImageNG->GetWidth();	
		pDoc->m_pImageDspWidth = pDoc->m_pImageDsp->GetWidth();		
		pDoc->m_pImageHeight = pDoc->m_pImage->GetHeight();
		pDoc->m_pImageBadHeight = pDoc->m_pImageBad->GetHeight();
		pDoc->m_pImageNGHeight = pDoc->m_pImageNG->GetHeight();
		pDoc->m_pImageDspHeight = pDoc->m_pImageDsp->GetHeight();	
		pDoc->m_pImagePtr = pDoc->m_pImage->GetImagePtr();
		pDoc->m_pImageNGPtr = pDoc->m_pImageNG->GetImagePtr();
		pDoc->m_pImageDspPtr = pDoc->m_pImageDsp->GetImagePtr();
/*		else
		{
			
			if(!pDoc->m_pImage->IsDataNull())	
				pDoc->m_pImage->Free();

			pDoc->m_pImage->Load(str);
		}
*/
			DrawImage(0);
	}

//	Invalidate();
}

void CVisWebView::LoadAllImage()
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
//	CFileDialog dlg(TRUE, "bmp", NULL, OFN_SHAREAWARE, "Bitmap Files (*.bmp)|*.bmp||");
	CFileDialog dlg(TRUE, "bmp", NULL, OFN_SHAREAWARE, "Bitmap Files (*0.*)|*0.*||");

	if(dlg.DoModal() == IDOK)
	{
		CString str = dlg.GetPathName();
		CString str1,str2,strtmp,strpath,strname;
		strname =dlg.GetFileName();
		strpath = dlg.GetFolderPath();
		int nfind = str.Find(".jpg");
		strtmp = str.Left(nfind-1);
		str1.Format("%s1.jpg",strtmp);
		str2.Format("%s2.jpg",strtmp);
		{

			if(str.Find("BMP")>=0){
				if(!pDoc->m_pImage->IsDataNull())	
					pDoc->m_pImage->Free();
				if(!pDoc->m_pImageNG->IsDataNull())	
					pDoc->m_pImageNG->Free();
				if(!pDoc->m_pImageDsp->IsDataNull())	
					pDoc->m_pImageDsp->Free();

				pDoc->m_pImage->Load(str);
				pDoc->m_pImageNG->Load(str);
				pDoc->m_pImageDsp->Load(str);

			}
			else{
// 				if(!pDoc->m_pImage->IsDataNull())	pDoc->m_pImage->Free();
//  				if(!pDoc->m_pImage1->IsDataNull())	pDoc->m_pImage1->Free();
//  				if(!pDoc->m_pImage2->IsDataNull())	pDoc->m_pImage2->Free();
				pDoc->m_pImage->Load(str);

				if(pDoc->m_pDlgInterface->m_bPreprocessing)
					for(int idx=0;idx<MOD_COUNT;idx++)
						m_bPreprocessing[0][idx] = TRUE;

				if(!pDoc->m_pImage1->Load(str1)){
					m_log2.AddString("1 Fail");
				}
				if(pDoc->m_pDlgInterface->m_bPreprocessing)
					for(int idx=0;idx<MOD_COUNT;idx++)
						m_bPreprocessing[1][idx] = TRUE;

				if(!pDoc->m_pImage2->Load(str2)){
					m_log2.AddString("2 Fail");
				}
				if(pDoc->m_pDlgInterface->m_bPreprocessing)
					for(int idx=0;idx<MOD_COUNT;idx++)
						m_bPreprocessing[2][idx] = TRUE;

			}
		}
		pDoc->m_data.m_dInspDetailTime[0][0] =pDoc->m_data.m_dInspDetailTime[1][0] =pDoc->m_data.m_dInspDetailTime[2][0] = GetPrecisionTime();
		if(pDoc->m_data.m_nFullimage){
			if(pDoc->m_data.m_nIgnorePixel1[1][0]>0){
				for(int k1=0;k1<1000;k1++){
					if(pDoc->m_data.m_nIgnorePixel1[1][k1]==0){
						break;
					}
					for(int y=0;y<CAM_HEIGHT_3072;y++){
						*(pDoc->m_pImage1->GetImagePtr()+y*CAM_WIDTH_CIS+(pDoc->m_data.m_nIgnorePixel1[1][k1])) = *(pDoc->m_pImage1->GetImagePtr()+y*CAM_WIDTH_CIS+(pDoc->m_data.m_nIgnorePixel1[1][k1]-1)) ;
					}
				}
			}
			
			memset(m_Inspect.m_FullImage,0,CAM_WIDTH_CIS*3*3072);
//memcopy

			double dt1 = GetPrecisionTime();
			for(int i=0;i<CAM_HEIGHT_CIS;i++)
				memcpy((m_Inspect.m_FullImage+CAM_WIDTH_CIS*(i*3)),pDoc->m_pImage->GetImagePtr()+CAM_WIDTH_CIS*i,CAM_WIDTH_CIS);
			double dt2 = GetPrecisionTime();
			for(int i=0;i<CAM_HEIGHT_CIS;i++)
				memcpy((m_Inspect.m_FullImage+CAM_WIDTH_CIS*(i*3)+CAM_WIDTH_CIS),pDoc->m_pImage1->GetImagePtr()+CAM_WIDTH_CIS*i,CAM_WIDTH_CIS);
			double dt3 = GetPrecisionTime();
			for(int i=0;i<CAM_HEIGHT_CIS;i++)
				memcpy((m_Inspect.m_FullImage+CAM_WIDTH_CIS*(i*3)+CAM_WIDTH_CIS*2),pDoc->m_pImage2->GetImagePtr()+CAM_WIDTH_CIS*i,CAM_WIDTH_CIS);
			m_bFullCopy[0] = m_bFullCopy[1] = m_bFullCopy[2] = TRUE;
			double dt4 = GetPrecisionTime();
			CString strtmp1;
			strtmp1.Format("T:%.0f,1:%.0f,2:%.0f,3:%.0f",(dt4-dt1)*1000,(dt2-dt1)*1000,(dt3-dt2)*1000,(dt4-dt3)*1000);
//			AddtoList(strtmp1,0);
		}

		int nPcNo= pDoc->m_data.GetVisionLine(0);//chcho

		//20150706 ljh CImage Setting Expention
		pDoc->m_pImageWidth = pDoc->m_pImage->GetWidth();
		pDoc->m_pImageBadWidth = pDoc->m_pImageBad->GetWidth();
		pDoc->m_pImageNGWidth = pDoc->m_pImageNG->GetWidth();	
		pDoc->m_pImageDspWidth = pDoc->m_pImageDsp->GetWidth();		
		pDoc->m_pImageHeight = pDoc->m_pImage->GetHeight();
		pDoc->m_pImageBadHeight = pDoc->m_pImageBad->GetHeight();
		pDoc->m_pImageNGHeight = pDoc->m_pImageNG->GetHeight();
		pDoc->m_pImageDspHeight = pDoc->m_pImageDsp->GetHeight();	
		pDoc->m_pImagePtr = pDoc->m_pImage->GetImagePtr();
		pDoc->m_pImageNGPtr = pDoc->m_pImageNG->GetImagePtr();
		pDoc->m_pImageDspPtr = pDoc->m_pImageDsp->GetImagePtr();
/*		else
		{
			
			if(!pDoc->m_pImage->IsDataNull())	
				pDoc->m_pImage->Free();

			pDoc->m_pImage->Load(str);
		}
*/
///		DrawImage(0);
//		DrawImage(1);
//		DrawImage(3);
	}

//	Invalidate();
}

void CVisWebView::LoadImage1()
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
//	CFileDialog dlg(TRUE, "bmp", NULL, OFN_SHAREAWARE, "Bitmap Files (*.bmp)|*.bmp||");
	CFileDialog dlg(TRUE, "bmp", NULL, OFN_SHAREAWARE, "Bitmap Files (*.*)|*.*||");

	if(dlg.DoModal() == IDOK)
	{
		CString str = dlg.GetPathName();
		{

			if(str.Find("BMP")>=0){
				if(!pDoc->m_pImage1->IsDataNull())	
					pDoc->m_pImage1->Free();

				pDoc->m_pImage1->Load(str);
			}
			else{
				pDoc->m_pImage1->Load(str);

			}


		}
		int nPcNo= pDoc->m_data.GetVisionLine(0);//chcho

		//{
		//	pDoc->m_pImage1Width = pDoc->m_pImage1->GetWidth();	//	
		//	pDoc->m_pImageNG1Width = pDoc->m_pImageNG1->GetWidth();	
		//	pDoc->m_pImageDsp1Width = pDoc->m_pImageDsp1->GetWidth();	
		//	pDoc->m_pImageMini1Width = pDoc->m_pImageMini1->GetWidth();
		//	pDoc->m_pImageMiniWidth = pDoc->m_pImageMini->GetWidth();
		//	pDoc->m_pImage1Height = pDoc->m_pImage1->GetHeight();
		//	pDoc->m_pImageNG1Height = pDoc->m_pImageNG1->GetHeight();	
		//	pDoc->m_pImageDsp1Height = pDoc->m_pImageDsp1->GetHeight();
		//	pDoc->m_pImageMini1Height = pDoc->m_pImageMini1->GetHeight();
		//	pDoc->m_pImage1Ptr = pDoc->m_pImage1->GetImagePtr();
		//	pDoc->m_pImageNG1Ptr = pDoc->m_pImageNG1->GetImagePtr();
		//	pDoc->m_pImageDsp1Ptr = pDoc->m_pImageDsp1->GetImagePtr();
		//	pDoc->m_pImageMiniPtr = pDoc->m_pImageMini->GetImagePtr();
		//	pDoc->m_pImageMini1Ptr = pDoc->m_pImageMini1->GetImagePtr();
		//	pDoc->m_pImageMiniHeight = pDoc->m_pImageMini->GetHeight();	
		//}
		//20150706 ljh CImage Setting Expention
		pDoc->m_pImageWidth = pDoc->m_pImage->GetWidth();
		pDoc->m_pImageBadWidth = pDoc->m_pImageBad->GetWidth();
		pDoc->m_pImageNGWidth = pDoc->m_pImageNG->GetWidth();	
		pDoc->m_pImageDspWidth = pDoc->m_pImageDsp->GetWidth();		
		pDoc->m_pImageHeight = pDoc->m_pImage->GetHeight();
		pDoc->m_pImageBadHeight = pDoc->m_pImageBad->GetHeight();
		pDoc->m_pImageNGHeight = pDoc->m_pImageNG->GetHeight();
		pDoc->m_pImageDspHeight = pDoc->m_pImageDsp->GetHeight();	
		pDoc->m_pImagePtr = pDoc->m_pImage->GetImagePtr();
		pDoc->m_pImageNGPtr = pDoc->m_pImageNG->GetImagePtr();
		pDoc->m_pImageDspPtr = pDoc->m_pImageDsp->GetImagePtr();
/*		else
		{
			
			if(!pDoc->m_pImage->IsDataNull())	
				pDoc->m_pImage->Free();

			pDoc->m_pImage->Load(str);
		}
*/
			DrawImage(1);
	}

//	Invalidate();
}

void CVisWebView::LoadImage2()
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
//	CFileDialog dlg(TRUE, "bmp", NULL, OFN_SHAREAWARE, "Bitmap Files (*.bmp)|*.bmp||");
	CFileDialog dlg(TRUE, "bmp", NULL, OFN_SHAREAWARE, "Bitmap Files (*.*)|*.*||");

	if(dlg.DoModal() == IDOK)
	{
		CString str = dlg.GetPathName();
		{

			if(str.Find("BMP")>=0){
				if(!pDoc->m_pImage2->IsDataNull())	
					pDoc->m_pImage2->Free();

				pDoc->m_pImage2->Load(str);
			}
			else{
				pDoc->m_pImage2->Load(str);

			}


		}
		int nPcNo= pDoc->m_data.GetVisionLine(0);//chcho

		//{
		//	pDoc->m_pImage1Width = pDoc->m_pImage1->GetWidth();	//	
		//	pDoc->m_pImageNG1Width = pDoc->m_pImageNG1->GetWidth();	
		//	pDoc->m_pImageDsp1Width = pDoc->m_pImageDsp1->GetWidth();	
		//	pDoc->m_pImageMini1Width = pDoc->m_pImageMini1->GetWidth();
		//	pDoc->m_pImageMiniWidth = pDoc->m_pImageMini->GetWidth();
		//	pDoc->m_pImage1Height = pDoc->m_pImage1->GetHeight();
		//	pDoc->m_pImageNG1Height = pDoc->m_pImageNG1->GetHeight();	
		//	pDoc->m_pImageDsp1Height = pDoc->m_pImageDsp1->GetHeight();
		//	pDoc->m_pImageMini1Height = pDoc->m_pImageMini1->GetHeight();
		//	pDoc->m_pImage1Ptr = pDoc->m_pImage1->GetImagePtr();
		//	pDoc->m_pImageNG1Ptr = pDoc->m_pImageNG1->GetImagePtr();
		//	pDoc->m_pImageDsp1Ptr = pDoc->m_pImageDsp1->GetImagePtr();
		//	pDoc->m_pImageMiniPtr = pDoc->m_pImageMini->GetImagePtr();
		//	pDoc->m_pImageMini1Ptr = pDoc->m_pImageMini1->GetImagePtr();
		//	pDoc->m_pImageMiniHeight = pDoc->m_pImageMini->GetHeight();	
		//}
		//20150706 ljh CImage Setting Expention
		pDoc->m_pImageWidth = pDoc->m_pImage->GetWidth();
		pDoc->m_pImageBadWidth = pDoc->m_pImageBad->GetWidth();
		pDoc->m_pImageNGWidth = pDoc->m_pImageNG->GetWidth();	
		pDoc->m_pImageDspWidth = pDoc->m_pImageDsp->GetWidth();		
		pDoc->m_pImageHeight = pDoc->m_pImage->GetHeight();
		pDoc->m_pImageBadHeight = pDoc->m_pImageBad->GetHeight();
		pDoc->m_pImageNGHeight = pDoc->m_pImageNG->GetHeight();
		pDoc->m_pImageDspHeight = pDoc->m_pImageDsp->GetHeight();	
		pDoc->m_pImagePtr = pDoc->m_pImage->GetImagePtr();
		pDoc->m_pImageNGPtr = pDoc->m_pImageNG->GetImagePtr();
		pDoc->m_pImageDspPtr = pDoc->m_pImageDsp->GetImagePtr();
/*		else
		{
			
			if(!pDoc->m_pImage->IsDataNull())	
				pDoc->m_pImage->Free();

			pDoc->m_pImage->Load(str);
		}
*/
			DrawImage(2);
	}

//	Invalidate();
}

void CVisWebView::SaveImage()
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CFileDialog dlg(false, "*.*", NULL, OFN_SHAREAWARE, "Bitmap Files (*.bmp)|*.bmp||");

	if(dlg.DoModal() == IDOK)
	{
		CString str = dlg.GetPathName();
		
		if(!pDoc->m_pImage->IsDataNull())
		{
			pDoc->m_pImage->Save(str);
		}
	}
}
// Utility Operations
void CVisWebView::DrawLine(CDC *pDC, CPoint p1, CPoint p2, COLORREF lColor, int nLineWidth)
{

	CPen pen,*pOldPen;
	pen.CreatePen(PS_SOLID,nLineWidth, lColor);
	pOldPen = (CPen*)pDC->SelectObject(&pen);

	p1 = Scale(p1);
	p2 = Scale(p2);
	pDC->MoveTo(p1);
	pDC->LineTo(p2);

	pDC->SelectObject(pOldPen);
}
void CVisWebView::DrawLineCam(CDC *pDC, CPoint p1, CPoint p2, COLORREF lColor, int nLineWidth,int nCam,int nLine)
{

	CPen pen,*pOldPen;
	pen.CreatePen(PS_SOLID,nLineWidth, lColor);
	pOldPen = (CPen*)pDC->SelectObject(&pen);

	p1 = Scale(p1,nCam);
	p2 = Scale(p2,nCam);
// 	if(nCam==0)
// 	{
// 		p2.y -= 480;
// //		int height = FORM_IMG_HEIGHT*0.5-10;//FORM_IMG_HEIGHT;
// //		p2.Offset(0,height);
// 	}
// 	else{
// 		p1.y+= 480;
// 	}
	m_ptLinePos1[nLine][0] = p1;
	m_ptLinePos1[nLine][1] = p2;
	pDC->MoveTo(p1);
	pDC->LineTo(p2);

	pDC->SelectObject(pOldPen);
}
CPoint CVisWebView::DrawPitchCam(CDC *pDC, CPoint p1, CPoint p2, COLORREF lColor, int nLineWidth,int nCam,int nLine)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	CPen pen,*pOldPen;
	pen.CreatePen(PS_SOLID,nLineWidth, lColor);
	pOldPen = (CPen*)pDC->SelectObject(&pen);
//X point만 사용한다.
	p1 = Scale(p1,nCam);
	p2 = Scale(p2,nCam);
	CRect rcDest,rcMain;
	GetWindowRect(rcMain);
	GetDlgItem(IDC_DETAIL_LINE)->GetWindowRect(rcDest);
	rcDest.OffsetRect(-rcMain.left,-rcMain.top);	
	p1.y = rcDest.top;	p2.y = rcDest.bottom;
	int nLen = abs(p2.y-p1.y);
	if(pDoc->m_pDlgInterface->m_bImageShowHide==FALSE)
		p2.y += (nLen*0.8);

	m_ptLinePos[nLine][0] = p1;//0301
	m_ptLinePos[nLine][1] = p2;//0301


	pDC->MoveTo(p1);
	pDC->LineTo(p2);

	pDC->SelectObject(pOldPen);
	return p1;
}
void CVisWebView::DrawRectangle(CDC *pDC, CPoint p1, CPoint p2, CPoint p3, COLORREF lColor, int nLineWidth,int nCam,int nCount,CString strmm)
{
	int nTest = 0;
	if(nCount>= MAX_LENGTH-2) return;
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CPen pen,*pOldPen;
	pen.CreatePen(PS_SOLID,nLineWidth, lColor);
	pOldPen = (CPen*)pDC->SelectObject(&pen);
	CBrush brush;
	brush.CreateSolidBrush(lColor );     // 오렌지색 채움색을 생성
	CBrush* oldBrush = pDC->SelectObject( &brush );
	//X point만 사용한다.
	p1 = Scale(p1,nCam);
	p2 = Scale(p2,nCam);
	CRect rcDest,rcMain,rtRect,rctitle,rcLength,rcview;
	GetWindowRect(rcMain);
	if(!pDoc->m_pDlgInterface->m_bImageShowHide && m_bDrawCheck==TRUE){
		m_bDrawCheck = FALSE;
		GetDlgItem(IDC_DETAIL_LINE)->GetWindowRect(rcDest);
		GetDlgItem(IDC_DISPLAY)->GetWindowRect(rcview);
		GetDlgItem(IDC_DETAIL_LINE)->MoveWindow(rcDest.left,rcview.top+220,rcDest.Width(),rcDest.Height());
		GetDlgItem(IDC_DETAIL_LINE)->GetWindowRect(rcDest);
	}
	else{
		if(pDoc->m_pDlgInterface->m_bImageShowHide)
			GetDlgItem(IDC_DETAIL_LINE)->MoveWindow(m_rtDetailView);
		GetDlgItem(IDC_DETAIL_LINE)->GetWindowRect(rcDest);
	}
	GetDlgItem(IDC_STATIC_COAT_TITLE1)->GetWindowRect(rctitle);
	GetDlgItem(IDC_STATIC_COAT_LEN1)->GetWindowRect(rcLength);
	rcDest.OffsetRect(-rcMain.left,-rcMain.top);	
	p1.y = rcDest.top;	p2.y = rcDest.bottom;
	if(p3.x>0)p1  = p3;
	rtRect.SetRect(p1.x,p1.y,p2.x,p2.y);
	pDC->Rectangle(rtRect);

	//타이틀 쓰기
	CRect rtTitle,rtTol1,rtTol2;
	//		rtTitle.SetRect((p1.x+p2.x)*0.5 - rctitle.Width()*0.5,p1.y-rctitle.Height() - 100,(p1.x+p2.x)*0.5+ rctitle.Width()*0.5,p1.y - 100);//기존 길이 위에 표시
	int nOffsety1 = 130,noffsety2=150;
	if(nCount<1){
		rtTitle.SetRect(rcDest.left-0,p1.y-rctitle.Height() - 10,rcDest.left-0+ rctitle.Width(),p1.y - 10);//기존 길이 위에 표시
		m_lbCoatTitle[0].MoveWindow(rtTitle);
		m_lbCoatTitle[0].ShowWindow(1);

		rtTitle.SetRect(rcDest.left-0,p1.y-rctitle.Height() + nOffsety1,rcDest.left-0+ rctitle.Width(),p1.y +nOffsety1);//기존 길이 위에 표시
		m_lbCoatTitle[1].MoveWindow(rtTitle);
		m_lbCoatTitle[1].ShowWindow(1);
		
	}
	// 	사이즈
	if(nCount%2==0){//위에
		rtTitle.SetRect((p1.x+p2.x)*0.5 - rcLength.Width()*0.5,p1.y-rcLength.Height() - 10,(p1.x+p2.x)*0.5+ rcLength.Width()*0.5,p1.y - 10);
		rtTol1.SetRect((p1.x+p2.x)*0.5 - rcLength.Width()*0.5,p1.y-rcLength.Height() - 60,(p1.x+p2.x)*0.5-rcLength.Width()*0.5+100,p1.y-rcLength.Height() - 10);
		rtTol2.SetRect((p1.x+p2.x)*0.5 - rcLength.Width()*0.5+140,p1.y-rcLength.Height() - 60,(p1.x+p2.x)*0.5- rcLength.Width()*0.5+240,p1.y-rcLength.Height() - 10);
//		if(m_bUseLen[nCount])
		{
			if(m_nTextColor[nCount]==0)			m_lbCoatLen[nCount].SetTextColor(COLOR_BLACK);
			else if(m_nTextColor[nCount]==1)	m_lbCoatLen[nCount].SetTextColor(COLOR_ORANGE);
			else if(m_nTextColor[nCount]==2){	m_lbCoatLen[nCount].SetTextColor(COLOR_RED);m_nResultOkNg = 1;}
			else{
				m_lbCoatLen[nCount].SetTextColor(COLOR_GRAY);
// 				pDC->MoveTo(m_ptLinePos[nCount][0]);pDC->LineTo(m_ptLinePos[nCount+1][1]);
// 				pDC->MoveTo(m_ptLinePos[nCount][1]);pDC->LineTo(m_ptLinePos[nCount+1][0]);
			}
		}

	}
	else{
		rtTitle.SetRect((p1.x+p2.x)*0.5 - rcLength.Width()*0.5,p1.y-rcLength.Height() + noffsety2,(p1.x+p2.x)*0.5+ rcLength.Width()*0.5,p1.y +noffsety2);
		rtTol1.SetRect((p1.x+p2.x)*0.5 - rcLength.Width()*0.5,p1.y-rcLength.Height() + noffsety2+ 145,(p1.x+p2.x)*0.5-rcLength.Width()*0.5+100,p1.y-rcLength.Height() +noffsety2+195);
		rtTol2.SetRect((p1.x+p2.x)*0.5 - rcLength.Width()*0.5+140,p1.y-rcLength.Height() + noffsety2+ 145,(p1.x+p2.x)*0.5- rcLength.Width()*0.5+240,p1.y-rcLength.Height() +noffsety2+195);
	

//		if(m_bUseLen[nCount])
		{
			if(m_nTextColor[nCount]==0)			m_lbCoatLen[nCount].SetTextColor(COLOR_BLACK);
			else if(m_nTextColor[nCount]==1)	m_lbCoatLen[nCount].SetTextColor(COLOR_ORANGE);
			else if(m_nTextColor[nCount]==2){	m_lbCoatLen[nCount].SetTextColor(COLOR_RED);m_nResultOkNg = 1;}
			else{
				m_lbCoatLen[nCount].SetTextColor(COLOR_GRAY);
// 				pDC->MoveTo(m_ptLinePos[nCount][0]);pDC->LineTo(m_ptLinePos[nCount+1][1]);
// 				pDC->MoveTo(m_ptLinePos[nCount][1]);pDC->LineTo(m_ptLinePos[nCount+1][0]);
			}
		}

		m_lbCoatLen[nCount].MoveWindow(rtTitle);
		m_lbCoatLen[nCount].SetText(strmm);
		m_lbCoatLen[nCount].ShowWindow(1);
	}
	if(nCount>=9) return;
	m_lPitchTol[nCount*2].MoveWindow(rtTol1);
	m_lPitchTol[nCount*2+1].MoveWindow(rtTol2);
	m_lPitchTol[nCount*2].ShowWindow(1);
	m_lPitchTol[nCount*2+1].ShowWindow(1);
	if(nTest==1){
		m_lbCoatLen[nCount].MoveWindow(rtTitle);
		m_lbCoatLen[nCount].SetText(strmm);
		m_lbCoatLen[nCount].ShowWindow(1);
	}
	else{
		//// 글자크기만큼의 보이지 않는 사각형 넣기
		pDoc->m_data.m_rtCoatChar[nCount] = rtTitle;//0124 폭 글자 영역
		if(m_bInsulateInspect){
			//영역이 작아져야 함.
			pDoc->m_data.m_rtCoatChar[nCount].InflateRect(0,0,0,-50);
			pDoc->m_data.m_rtInsulateChar[nCount]=pDoc->m_data.m_rtCoatChar[nCount];
			pDoc->m_data.m_rtInsulateChar[nCount].OffsetRect(0,pDoc->m_data.m_rtInsulateChar[nCount].Height()+5);
		}
		COLORREF lColor1;

//		if(m_bUseLen[nCount])
		{
			if(m_nTextColor[nCount]==0)			lColor1 = COLOR_BLACK;
			else if(m_nTextColor[nCount]==1)	lColor1 = COLOR_ORANGE;
			else if(m_nTextColor[nCount]==2){	lColor1 = COLOR_RED;m_nResultOkNg = 1;}
			else								lColor1 = COLOR_GRAY;
		}

		if(nCount%2==0){//위에  코팅일대는 기존것을 쓴다.
			if(m_bUseLen[nCount]==FALSE)			DataDraw(pDoc->m_data.m_rtCoatChar[nCount].TopLeft(),pDoc->m_data.m_rtCoatChar[nCount].BottomRight(),strmm,450,lColor1,1,nCount);
			else if(m_bNGLen[nCount] == TRUE){
				DataDraw(pDoc->m_data.m_rtCoatChar[nCount].TopLeft(),pDoc->m_data.m_rtCoatChar[nCount].BottomRight(),strmm,450,lColor1,1,nCount);
				m_nResultOkNg = 1;
			}
			else									DataDraw(pDoc->m_data.m_rtCoatChar[nCount].TopLeft(),pDoc->m_data.m_rtCoatChar[nCount].BottomRight(),strmm,450,lColor1,1,nCount);//color_white
		}

	}


	if(!pDoc->m_pDlgInterface->m_bImageShowHide && m_bMismatchUse && (m_strComputerName.Find("BACK")>=0 ||pDoc->m_data.m_strComName.Mid(9,1)=="B")){
		int noffsety3 = 430,noffsety4 = 160;
		if(nCount%2==0){//밑에
			rtTitle.SetRect((p1.x+p2.x)*0.5 - rcLength.Width()*0.5,p1.y-rcLength.Height() - 10+noffsety3,(p1.x+p2.x)*0.5+ rcLength.Width()*0.5,p1.y - 10+noffsety3-50);
			
		}
		else{
			rtTitle.SetRect((p1.x+p2.x)*0.5 - rcLength.Width()*0.5,p1.y-rcLength.Height() + noffsety2+noffsety4,(p1.x+p2.x)*0.5+ rcLength.Width()*0.5,p1.y +noffsety2+noffsety4-50);
		}
		m_lbCoatLenTop[nCount+2].MoveWindow(rtTitle);
//		m_lbCoatLenTop[nCount].SetText(strmm);
		m_lbCoatLenTop[nCount+2].ShowWindow(1);
		
		m_lbTopTitle.ShowWindow(1);
		//m_lbMisMatchTitle.ShowWindow(1);
		if(nCount<1){
			rtTitle.SetRect(rcDest.left+0,p1.y-rctitle.Height() - 10+noffsety3-30,rcDest.left+0+ rctitle.Width(),p1.y - 10+noffsety3-50);//기존 길이 위에 표시
			m_lbCoatLenTop[0].MoveWindow(rtTitle);
			m_lbCoatLenTop[0].ShowWindow(1);

			rtTitle.SetRect(rcDest.left+0,p1.y-rctitle.Height() + noffsety2+noffsety4-30,rcDest.left+0+ rctitle.Width(),p1.y +noffsety2+noffsety4-50);//기존 길이 위에 표시
			m_lbCoatLenTop[1].MoveWindow(rtTitle);
			m_lbCoatLenTop[1].ShowWindow(1);
		}


	}

	//크기 쓰기

	pDC->SelectObject( oldBrush );
	pDC->SelectObject(pOldPen);
}

void CVisWebView::DrawCross(CDC *pDC, CPoint p1, int nLinelength, COLORREF lColor, int nLineWidth)
{

	CPen pen,*pOldPen;
	pen.CreatePen(PS_SOLID,nLineWidth, lColor);
	pOldPen = (CPen*)pDC->SelectObject(&pen);
	CPoint pt1,pt2;
	pt1 =pt2 = p1;
	pt1.x = p1.x-nLinelength;
	pt2.x = p1.x+nLinelength;
	pt1 = Scale(pt1);
	pt2 = Scale(pt2);
	pDC->MoveTo(pt1);
	pDC->LineTo(pt2);

	pt1 =pt2 = p1;
	pt1.y = p1.y-nLinelength;
	pt2.y = p1.y+nLinelength;
	pt1 = Scale(pt1);
	pt2 = Scale(pt2);
	pDC->MoveTo(pt1);
	pDC->LineTo(pt2);

	pDC->SelectObject(pOldPen);
}

void CVisWebView::DrawRect(CDC *pDC, CPoint p1, CPoint p2, COLORREF lColor, int nLineWidth)
{
	CPen pen,*pOldPen;
	pen.CreatePen(PS_SOLID,nLineWidth, lColor);
	pOldPen = (CPen*)pDC->SelectObject(&pen);
	
	pDC->MoveTo(p1.x, p1.y);
	pDC->LineTo(p2.x, p1.y);
	pDC->LineTo(p2.x, p2.y);
	pDC->LineTo(p1.x, p2.y);
	pDC->LineTo(p1.x, p1.y-1);

	pDC->SelectObject(pOldPen);
}

void CVisWebView::DrawRect(CDC *pDC, CRect rect, COLORREF lColor, int nLineWidth, BOOL bScale)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	if(rect.left < 0)			rect.left = 0;
	if(rect.top	< 0)			rect.top = 0;
//	if(rect.right > pDoc->m_pImage->GetWidth())			rect.right = pDoc->m_pImage->GetWidth();
	if(lColor == COLOR_RED || lColor == COLOR_GREEN)
		if(rect.bottom	> pDoc->m_pImage->GetHeight())			rect.bottom = pDoc->m_pImage->GetHeight();

	if(bScale)	rect = Scale(rect);
	DrawRect(pDC, CPoint(rect.left, rect.top), CPoint(rect.right, rect.bottom), lColor, nLineWidth);
}



void CVisWebView::DrawText(CDC *pDC, CPoint pt, CString str)
{
	pt = Scale(pt);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,0));
	pDC->TextOut(pt.x,pt.y,str);
}

void CVisWebView::DrawNGImage(CDC *pDC,int nCam)
{
	if(((CVisWebApp*)AfxGetApp())->m_debugLogWrite == TRUE){
		((CVisWebApp*)AfxGetApp())->WriteLog(PATH_DEBUG_LOG, "debug_log", "DrawNGImage");
	}
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	CRect rcDIB, rcDest;
// 	if(!pDoc->m_data.m_pImageDefect[nCam][m_nCurNGImgIndex]->IsDataNull())
// 	{		
// 		rcDIB.top = 0;
// 		rcDIB.left = 0;
// 		rcDIB.right = BAD_IMG_WIDTH;//pDoc->m_data.m_pImageDefect[0]->GetWidth();
// 		rcDIB.bottom = BAD_IMG_HEIGHT;//pDoc->m_data.m_pImageDefect[0]->GetHeight();
// 
// 		double dScale = 1;//double(pDoc->m_nMul) / pDoc->m_nDiv;
// 		rcDest = m_rectNGImage;
// 		pDoc->m_data.m_pImageDefect[nCam][m_nCurNGImgIndex]->Draw(pDC->m_hDC,&rcDIB,&rcDest);
// 	}
	if(nCam==0){
		CRect rcMain;
		GetWindowRect(rcMain);
		for(int n=0;n<15;n++){
			rcDIB.top = 0;
			rcDIB.left = 0;
			rcDIB.right = BAD_IMG_WIDTH;//pDoc->m_data.m_pImageDefect[0]->GetWidth();
			rcDIB.bottom = BAD_IMG_HEIGHT;//pDoc->m_data.m_pImageDefect[0]->GetHeight();

			int mm = n;
			if(mm>0)mm+=1;		
			GetDlgItem(IDC_STATIC_001+mm)->GetWindowRect(rcDest);
			rcDest.OffsetRect(-rcMain.left,-rcMain.top);
			m_pDefectImage[n]->Draw(pDC->m_hDC,&rcDIB,&rcDest);
		}
	}
	if(((CVisWebApp*)AfxGetApp())->m_debugLogWrite == TRUE){
		((CVisWebApp*)AfxGetApp())->WriteLog(PATH_DEBUG_LOG, "debug_log", "DrawNGImage-end");
	}
}

CPoint CVisWebView::Scale(CPoint point)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	
	CPoint point_original= point;
	CPoint point_trans = CPoint(0,0);

	CRect rcDest;
	GetDlgItem(IDC_DISPLAY)->GetWindowRect(rcDest);

	int width = rcDest.Width();
	int height = rcDest.Height();//*0.5-10;//FORM_IMG_HEIGHT;

	point_trans.x = (long) ((float)(width) / (float)((pDoc->m_pImage->GetWidth())) * (float)(point_original.x));
	point_trans.y = (long) ((float)(height) / (float)((pDoc->m_pImage->GetHeight())) * (float)(point_original.y));

	point = point_trans;

	return point;
}

CPoint CVisWebView::Scale(CPoint point,int nCam)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	
	CPoint point_original= point;
	CPoint point_trans = CPoint(0,0);

	CRect rcDest;
	if(nCam==0)
		GetDlgItem(IDC_DISPLAY)->GetWindowRect(rcDest);
	else if(nCam==1)
		GetDlgItem(IDC_DISPLAY2)->GetWindowRect(rcDest);
	else
		GetDlgItem(IDC_DISPLAY3)->GetWindowRect(rcDest);

	int width = rcDest.Width();
	int height = rcDest.Height();//*0.5-10;//FORM_IMG_HEIGHT;
	int nOffsetX = rcDest.left;

	point_trans.x = (long) ((float)(width) / (float)((pDoc->m_pImage->GetWidth())) * (float)(point_original.x)) +nOffsetX;
	point_trans.y = (long) ((float)(height) / (float)((pDoc->m_pImage->GetHeight())) * (float)(point_original.y));

	point = point_trans;

	return point;
}

CRect CVisWebView::Scale(CRect rect)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	
	CRect rect_original = rect;
	CRect rect_trans = CRect(0,0,0,0);

	CRect rcDest;
	GetDlgItem(IDC_DISPLAY)->GetWindowRect(rcDest);

	int width = rcDest.Width();
	int height = rcDest.Height();//*0.5-10;//FORM_IMG_HEIGHT;

	rect_trans.left = (long)((float)(width) / (float)(pDoc->m_pImage->GetWidth()) * (float)(rect_original.left));
	rect_trans.top = (long)((float)(height) / (pDoc->m_pImage->GetHeight()) * (float)(rect_original.top));

	rect_trans.right = (long)((float)(width) / (float)(pDoc->m_pImage->GetWidth()) * (float)(rect_original.right));
	rect_trans.bottom = (long)((float)(height) / (float)(pDoc->m_pImage->GetHeight()) * (float)(rect_original.bottom));

	rect = rect_trans;

	return rect;
}

void CVisWebView::OnBtnLoadImg()
{
	LoadImage();
}

void CVisWebView::InitControl()
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	//Init Result	
	CString str;
	m_labelResult.SetTextColor(COLOR_GREEN);
	m_labelResult.SetBkColor(COLOR_BLACK);
	m_labelResult.SetFontBold(TRUE);
	m_labelResult.SetFontName("굴림");
	m_labelResult.SetFontSize(50);

	m_lbLeft.SetTextColor(COLOR_BLACK);
	m_lbLeft.SetBkColor(COLOR_YELLOW);
	m_lbLeft.SetFontBold(TRUE);
	m_lbLeft.SetFontName("굴림");
	m_lbLeft.SetFontSize(40);
	if(pDoc->m_pDlgInterface->m_bEngKor){
		str.Format("N-EPC"); 
		pDoc->m_data.m_nEpcPos = 2;
	}
	else
		str.Format("왼쪽");
	m_lbLeft.SetText(str);

	m_lbRight.SetTextColor(COLOR_BLACK);
	m_lbRight.SetBkColor(COLOR_YELLOW);
	m_lbRight.SetFontBold(TRUE);
	m_lbRight.SetFontName("굴림");
	m_lbRight.SetFontSize(40);
	if(pDoc->m_pDlgInterface->m_bEngKor){
		str.Format("EPC"); 
		pDoc->m_data.m_nEpcPos = 2;
	}
	else
		str.Format("오른쪽");
	m_lbRight.SetText(str);

	if(pDoc->m_pDlgInterface->m_bEngKor){
		if(m_strComputerName.Mid(7,1)=="C"){
			if(m_strComputerName.Mid(8,1) == "H"){
				if(m_strComputerName.Mid(9,1) == "T"){
					str.Format("N-EPC"); 
					m_lbLeft.SetText(str);
					str.Format("EPC(1)");				// 20201020 kjh EPC에 (1)추가
					m_lbRight.SetText(str);
					pDoc->m_data.m_nEpcPos = 2; 
				}
				else{
					str.Format("N-EPC"); 
					m_lbRight.SetText(str);
					str.Format("EPC(1)"); 
					m_lbLeft.SetText(str);
					pDoc->m_data.m_nEpcPos = 1;
				}
			}
			else{
				str.Format("N-EPC"); 
				m_lbRight.SetText(str);
				str.Format("EPC(1)"); 
				m_lbLeft.SetText(str);
				pDoc->m_data.m_nEpcPos = 1;//LabelInit
			}
		}
		else{
			if(m_strComputerName.Mid(8,1) == "H"){
				if(m_strComputerName.Mid(9,1) == "T"){
					str.Format("EPC(1)"); 
					m_lbLeft.SetText(str);
					str.Format("N-EPC"); 
					m_lbRight.SetText(str);
					pDoc->m_data.m_nEpcPos = 1;
				}
				else{
					str.Format("EPC(1)"); 
					m_lbRight.SetText(str);
					str.Format("N-EPC"); 
					m_lbLeft.SetText(str);
					pDoc->m_data.m_nEpcPos = 2; 
				}
			}
			else{
				str.Format("N-EPC"); 
				m_lbRight.SetText(str);
				str.Format("EPC(1)"); 
				m_lbLeft.SetText(str);
				pDoc->m_data.m_nEpcPos = 1;
			}

		}
	}
	m_SysParam->LabelInit(pDoc->m_data.m_nEpcPos);

	m_labelStatistics.SetTextColor(COLOR_YELLOW);
	m_labelStatistics.SetBkColor(COLOR_BLACK);
	m_labelStatistics.SetFontBold(TRUE);
	m_labelStatistics.SetFontName("굴림체");
	m_labelStatistics.SetFontSize(15);

	m_labelWarning.SetTextColor(COLOR_RED);
	m_labelWarning.SetBkColor(COLOR_BLACK);
	m_labelWarning.SetFontBold(TRUE);
	m_labelWarning.SetFontName("굴림체");
	m_labelWarning.SetFontSize(12);

	m_labelNGInfo.SetTextColor(COLOR_YELLOW);
	m_labelNGInfo.SetBkColor(COLOR_BLACK);
	m_labelNGInfo.SetFontName("굴림체");
	m_labelNGInfo.SetFontSize(11);
//////////////////////////////////////////////////////////////////////
	int nSize = 30;
	m_lbLotInfo.SetTextColor(COLOR_YELLOW);
	m_lbLotInfo.SetBkColor(RGB(51,51,151));
	m_lbLotInfo.SetFontName("휴먼둥근헤드라인");
	m_lbLotInfo.SetFontSize(nSize);
	str.Format("Lot No. ABCDEFGHIJKLM");
	m_lbLotInfo.SetText(str);

	m_lbWinder1.SetTextColor(COLOR_YELLOW);
	m_lbWinder1.SetBkColor(RGB(51,51,151));
	m_lbWinder1.SetFontName("휴먼둥근헤드라인");
	m_lbWinder1.SetFontSize(nSize);
	if(pDoc->m_pDlgInterface->m_bEngKor)
		str.Format("CORE_A:"); 
	else
		str.Format("CORE A:");//pDoc->m_data.m_nMachineLengthAB[ntime%2] 
	m_lbWinder1.SetText(str);

	m_lbWinder2.SetTextColor(COLOR_YELLOW);
	m_lbWinder2.SetBkColor(RGB(51,51,151));
	m_lbWinder2.SetFontName("휴먼둥근헤드라인");
	m_lbWinder2.SetFontSize(nSize);
	if(pDoc->m_pDlgInterface->m_bEngKor)
		str.Format("CORE_B"); 
	else
		str.Format("CORE B:");
	m_lbWinder2.SetText(str);

	m_lbNullDrag.SetTextColor(COLOR_YELLOW);
	m_lbNullDrag.SetBkColor(COLOR_GRAY_WHITE1);
	m_lbNullDrag.SetFontName("휴먼둥근헤드라인");
	m_lbNullDrag.SetFontSize(nSize);
	if(pDoc->m_pDlgInterface->m_bEngKor)
		str.Format("DRAG LINE:"); 
	else
		str.Format("드래그라인:");
	m_lbNullDrag.SetText(str);

	m_lbNullLine.SetTextColor(COLOR_YELLOW);
	m_lbNullLine.SetBkColor(COLOR_GRAY_WHITE1);
	m_lbNullLine.SetFontName("휴먼둥근헤드라인");
	m_lbNullLine.SetFontSize(nSize);
	if(pDoc->m_pDlgInterface->m_bEngKor)
		str.Format("N/COAT LINE"); 
	else
		str.Format("무지라인:");
	m_lbNullLine.SetText(str);

	m_lbNullIsland.SetTextColor(COLOR_YELLOW);
	m_lbNullIsland.SetBkColor(COLOR_GRAY_WHITE1);
	m_lbNullIsland.SetFontName("휴먼둥근헤드라인");
	m_lbNullIsland.SetFontSize(nSize);
	if(pDoc->m_pDlgInterface->m_bEngKor)
		str.Format("ISLAND"); 
	else
		str.Format("아일랜드:");
	m_lbNullIsland.SetText(str);

	m_lbCoatDrag.SetTextColor(COLOR_YELLOW);
	m_lbCoatDrag.SetBkColor(COLOR_BLACK);
	m_lbCoatDrag.SetFontName("휴먼둥근헤드라인");
	m_lbCoatDrag.SetFontSize(nSize);
	if(pDoc->m_pDlgInterface->m_bEngKor)
		str.Format("EDGE SPUR:"); 
	else
		str.Format("코팅드래그:");
	m_lbCoatDrag.SetText(str);

	m_lbCoatLine.SetTextColor(COLOR_YELLOW);
	m_lbCoatLine.SetBkColor(COLOR_BLACK);
	m_lbCoatLine.SetFontName("휴먼둥근헤드라인");
	m_lbCoatLine.SetFontSize(nSize);
	if(pDoc->m_pDlgInterface->m_bEngKor)
		str.Format("COAT LINE:"); 
	else
		str.Format("코팅라인:");
	m_lbCoatLine.SetText(str);

	m_lbCoatPinHole.SetTextColor(COLOR_YELLOW);
	m_lbCoatPinHole.SetBkColor(COLOR_BLACK);
	m_lbCoatPinHole.SetFontName("휴먼둥근헤드라인");
	m_lbCoatPinHole.SetFontSize(nSize);
	m_lbCoatPinHole.SetFontBold(1);
	if(pDoc->m_pDlgInterface->m_bEngKor)
		str.Format("PINHOLE:"); 
	else
		str.Format("핀     홀:");
	m_lbCoatPinHole.SetText(str);

	m_lbFullWidth.SetTextColor(COLOR_YELLOW);
	m_lbFullWidth.SetBkColor(COLOR_BLACK);
	m_lbFullWidth.SetFontName("휴먼둥근헤드라인");
	m_lbFullWidth.SetFontSize(64);
	m_lbFullWidth.SetFontBold(1);
	if(pDoc->m_pDlgInterface->m_bEngKor){
		CString str1;
		if(m_strComputerName.Mid(8,1)=="H"){
			if(m_strComputerName.Mid(9,1)=="T")
				str.Format("%s - Head Top : %.2f mm",m_strComputerName.Mid(7,1),0);
			else
				str.Format("%s - Head BACK : %.2f mm",m_strComputerName.Mid(7,1),0);
		}
		else{
			if(m_strComputerName.Mid(9,1)=="T")
				str.Format("%s - Mis. Top : %.2f mm",m_strComputerName.Mid(7,1),0);
			else
				str.Format("%s - Mis. BACK : %.2f mm",m_strComputerName.Mid(7,1),0);

		}
		CRect rc11,rc12;
		GetDlgItem(IDC_STATIC_FULL_WIDTH)->GetWindowRect(rc11);
		m_lbTopTitle.GetWindowRect(rc12);

		int nx1=0,nx2=0,ny1=0,ny2=0;
		nx1 = 310;nx2 = 1290;ny1=90;ny2=rc11.Height();
		if((m_strComputerName.Find("BACK")>=0 ||  pDoc->m_data.m_strComName.Mid(9,1)=="B") && pDoc->m_pDlgInterface->m_bImageShowHide==FALSE)
			m_lbFullWidth.MoveWindow(nx1,ny1,nx2,ny2);
		else	
			m_lbFullWidth.MoveWindow(nx1,ny1,nx2,rc11.Height());

	//	str.Format("TOTAL WIDTH:  mm"); 
	}
	else
		str.Format("제 품 폭 :  mm");
	m_lbFullWidth.SetText(str);
	
	if(pDoc->m_pDlgInterface->m_bEngKor)
		nSize = 30; 
	else
		nSize = 48;//64;
	int nSize1 = 28;
	for(int i=0;i<MAX_LENGTH;i++){
		m_lbCoatTitle[i].SetFontName("휴먼둥근헤드라인");
		if(i>1)	{
			m_lbCoatTitle[i].SetFontSize(nSize1);
			m_lbCoatTitle[i].SetTextColor(COLOR_BLUE);
			m_lbCoatTitle[i].SetBkColor(COLOR_GREEN);
		}
		else{
			m_lbCoatTitle[i].SetFontSize(nSize);
			if(i%2==0){
				m_lbCoatTitle[i].SetTextColor(COLOR_BLACK);
				if(!pDoc->m_pDlgInterface->m_nColorGray)
					m_lbCoatTitle[i].SetBkColor(COLOR_ORANGE1);//라인별 색상 정리
				else
					m_lbCoatTitle[i].SetBkColor(COLOR_GRAY_WHITE1);//라인별 색상 정리
			}
			else{
				m_lbCoatTitle[i].SetTextColor(COLOR_WHITE);
				m_lbCoatTitle[i].SetBkColor(COLOR_BLACK);
			}
		}
		m_lbCoatTitle[i].SetFontBold(1);
		m_lbCoatLen[i].SetFontName("휴먼둥근헤드라인");
		if(m_strComputerName.Find("BACK")>=0 ||  pDoc->m_data.m_strComName.Mid(9,1)=="B"){
			m_lbCoatLenTop[i].SetFontName("휴먼둥근헤드라인");
			m_lbCoatLenTop[i].SetFontSize(44);
			m_lbCoatLenTop[i].SetFontBold(1);
		}
		m_lbCoatLen[i].SetFontSize(50);//60
		m_lbCoatLen[i].SetFontBold(1);
		if(i%2==0){
//			m_lbCoatTitle[i].SetTextColor(COLOR_BLACK);
//			m_lbCoatTitle[i].SetBkColor(COLOR_ORANGE1);//라인별 색상 정리
			m_lbCoatLen[i].SetTextColor(COLOR_BLACK);
			if(!pDoc->m_pDlgInterface->m_nColorGray)
				m_lbCoatLen[i].SetBkColor(COLOR_ORANGE1);//라인별 색상 정리
			else
				m_lbCoatLen[i].SetBkColor(COLOR_GRAY_WHITE1);//라인별 색상 정리

//			m_lbCoatLen[i].SetBkColor(COLOR_ORANGE1);
			if(m_strComputerName.Find("BACK")>=0 || pDoc->m_data.m_strComName.Mid(9,1)=="B"){
				m_lbCoatLenTop[i].SetTextColor(COLOR_BLACK);

				if(!pDoc->m_pDlgInterface->m_nColorGray || pDoc->m_data.m_strComName.Mid(7,1)=="A")
					m_lbCoatLenTop[i].SetBkColor(COLOR_ORANGE1);//라인별 색상 정리
				else
					m_lbCoatLenTop[i].SetBkColor(COLOR_GRAY_WHITE1);//라인별 색상 정리
//				m_lbCoatLenTop[i].SetBkColor(COLOR_ORANGE1);
			}
			if(pDoc->m_pDlgInterface->m_bEngKor)
				str.Format("N/COAT"); 
			else
				str.Format("무지");
		}
		else{
//			m_lbCoatTitle[i].SetTextColor(COLOR_WHITE);
//			m_lbCoatTitle[i].SetBkColor(COLOR_BLACK);
			m_lbCoatLen[i].SetTextColor(COLOR_WHITE);
			m_lbCoatLen[i].SetBkColor(COLOR_BLACK);
			if(m_strComputerName.Find("BACK")>=0 || pDoc->m_data.m_strComName.Mid(9,1)=="B"){
				m_lbCoatLenTop[i].SetTextColor(COLOR_WHITE);
				m_lbCoatLenTop[i].SetBkColor(COLOR_BLACK);
			}
			if(pDoc->m_pDlgInterface->m_bEngKor)
				str.Format("COAT"); 
			else
				str.Format("코팅");
		}
		m_lbCoatTitle[i].SetText(str);
		m_lbCoatLen[i].SetText(str);
		if(m_strComputerName.Find("BACK")>=0 || pDoc->m_data.m_strComName.Mid(9,1)=="B"){
			m_lbCoatLenTop[i].SetText(str);
		}
		m_lbCoatLenTop[i].ShowWindow(0);

		m_lPitchTol[i].SetFontSize(20);
		m_lPitchTol[i].SetFontBold(1);
		m_lPitchTol[i].SetTextColor(COLOR_YELLOW);
		m_lPitchTol[i].SetBkColor(COLOR_BLACK);
		m_lPitchTol[i].ShowWindow(0);

 		m_lbGapMisMatch[i].SetFontSize(18);
		m_lbGapMisMatch[i].SetTextColor(COLOR_WHITE);
		m_lbGapMisMatch[i].SetBkColor(COLOR_BTNHIGHLIGHT);
		m_lbGapMisMatch[i].SetFontName("휴먼둥근헤드라인");
		m_lbGapMisMatch[i].SetFontBold(1);
 		m_lbGapMisMatch[i].ShowWindow(0);
		
	}
	ShowCoatTitle(0);

	for(int i=0;i<15;i++){
		m_lbDefectInfo[i].SetTextColor(COLOR_YELLOW);
		m_lbDefectInfo[i].SetBkColor(COLOR_BLACK);
		m_lbDefectInfo[i].SetFontName("굴림체");
		m_lbDefectInfo[i].SetFontSize(14);
		str.Format("Defect\nInformation");
		m_lbDefectInfo[i].SetText(str);		
	}
	
	
	m_lbTopTitle.SetTextColor(COLOR_YELLOW);
	m_lbTopTitle.SetBkColor(COLOR_BLACK);
	m_lbTopTitle.SetFontName("휴먼둥근헤드라인");
	m_lbTopTitle.SetFontSize(44);
	m_lbTopTitle.SetFontBold(1);
	if(pDoc->m_pDlgInterface->m_bEngKor)
		str.Format("TOP WIDTH"); 
	else
		str.Format("Top폭");
	m_lbTopTitle.SetText(str);

	m_lbMisMatchTitle.SetTextColor(COLOR_YELLOW);
	m_lbMisMatchTitle.SetBkColor(COLOR_BLUE);
	m_lbMisMatchTitle.SetFontName("휴먼둥근헤드라인");
	m_lbMisMatchTitle.SetFontSize(28);
	m_lbMisMatchTitle.SetFontBold(1);
	if(pDoc->m_pDlgInterface->m_bEngKor)
		str.Format("MIS."); 
	else
		str.Format("미스매치");
	m_lbMisMatchTitle.SetText(str);
///////////////////////////////////////


	if(m_strComputerName.Find("BACK")>=0 || pDoc->m_data.m_strComName.Mid(9,1)=="B"){
		m_lbMismatchTolMin.SetTextColor(COLOR_BLACK);
		m_lbMismatchTolMin.SetBkColor(COLOR_GREEN);
		m_lbMismatchTolMin.SetFontName("휴먼둥근헤드라인");
		m_lbMismatchTolMin.SetFontSize(18);
		m_lbMismatchTolMin.SetFontBold(1);
		if(pDoc->m_pDlgInterface->m_bEngKor)
			str.Format("MIN"); 
		else
			str.Format("최소");
		m_lbMismatchTolMin.SetText(str);

		m_lbMismatchTolMax.SetTextColor(COLOR_BLACK);
		m_lbMismatchTolMax.SetBkColor(COLOR_GREEN);
		m_lbMismatchTolMax.SetFontName("휴먼둥근헤드라인");
		m_lbMismatchTolMax.SetFontSize(18);
		m_lbMismatchTolMax.SetFontBold(1);
		if(pDoc->m_pDlgInterface->m_bEngKor)
			str.Format("MAX"); 
		else
			str.Format("최대");
		m_lbMismatchTolMax.SetText(str);

	}
	else{
		m_lbMismatchTolMax.ShowWindow(0);
		m_lbMismatchTolMin.ShowWindow(0);
	}

	
	m_lbStatsCAM.SetTextColor(COLOR_BLACK);
	m_lbStatsCAM.SetBkColor(COLOR_GREEN);
	m_lbStatsCAM.SetFontName("휴먼둥근헤드라인");
	m_lbStatsCAM.SetFontSize(18);
	m_lbStatsCAM.SetFontBold(1);
	if(pDoc->m_pDlgInterface->m_bEngKor)
		str.Format("CAM"); 
	else
		str.Format("카메라");
	m_lbStatsCAM.SetText(str);

	m_lbStatsIO.SetTextColor(COLOR_BLACK);
	m_lbStatsIO.SetBkColor(COLOR_GREEN);
	m_lbStatsIO.SetFontName("휴먼둥근헤드라인");
	m_lbStatsIO.SetFontSize(18);
	m_lbStatsIO.SetFontBold(1);
	str.Format("I/O");
	m_lbStatsIO.SetText(str);
	
	m_lbStatsPLC.SetTextColor(COLOR_BLACK);
	m_lbStatsPLC.SetBkColor(COLOR_GREEN);
	m_lbStatsPLC.SetFontName("휴먼둥근헤드라인");
	m_lbStatsPLC.SetFontSize(18);
	m_lbStatsPLC.SetFontBold(1);
	str.Format("PLC");
	m_lbStatsPLC.SetText(str);

	m_lbStaticTBGap.SetTextColor(COLOR_WHITE);
	m_lbStaticTBGap.SetBkColor(COLOR_BTNHIGHLIGHT);
	m_lbStaticTBGap.SetFontName("휴먼둥근헤드라인");
	m_lbStaticTBGap.SetFontSize(14);
	m_lbStaticTBGap.SetFontBold(1);
	str.Format("B-T Gap");
	m_lbStaticTBGap.SetText(str);
	m_lbStaticTBGap.ShowWindow(0);

	
	m_lbNonCoating.SetTextColor(COLOR_RED);
	m_lbNonCoating.SetBkColor(COLOR_GRAY_WHITE1);
	m_lbNonCoating.SetFontName("휴먼둥근헤드라인");
	m_lbNonCoating.SetFontSize(40);
	m_lbNonCoating.SetFontBold(0);
	str.Format("Line needs to be running to enable vision.");
	m_lbNonCoating.SetText(str);
	m_lbNonCoating.ShowWindow(0);

	// last data
	m_defectMap->ShowMismatchControl();		//20201015 kjh

	m_lbLastDataCoat.SetTextColor(RGB(255,255,204));		// 20201017 kjh
	m_lbLastDataCoat.SetBkColor(COLOR_BLACK);
	m_lbLastDataCoat.SetFontName("휴먼둥근헤드라인");
	m_lbLastDataCoat.SetFontSize(20);
	str.Format("Last Data");
	m_lbLastDataCoat.SetText(str);

	m_lbLastDataNCoat.SetTextColor(RGB(153,51,153));		// 20201017 kjh
	if(m_strComputerName.Mid(7,1)=="A")//음극
		m_lbLastDataNCoat.SetBkColor(COLOR_ORANGE1);
	else
		m_lbLastDataNCoat.SetBkColor(COLOR_GRAY_WHITE1);

	m_lbLastDataNCoat.SetFontName("휴먼둥근헤드라인");
	m_lbLastDataNCoat.SetFontSize(20);
	str.Format("Last Data");
	m_lbLastDataNCoat.SetText(str);

	
//	str.Format("\n 검사 갯수\n\n 불량 갯수\n\n 양 품 율 \n\n 검사 시간 \n\n 초당 프레임 \n\n HDD 잔여량  ");
//	m_labelStatistics.SetText(str);
}

void CVisWebView::InitSystemInfo()
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	//Init Result	
	m_labelSysInfo.SetTextColor(COLOR_WHITE);
	m_labelSysInfo.SetBkColor(COLOR_BLACK);
	m_labelSysInfo.SetFontBold(FALSE);
	m_labelSysInfo.SetFontName("굴림");
	m_labelSysInfo.SetFontSize(12);

	CString sstr1, sstr2, sstr3, str_info;
	sstr1 = pDoc->m_pDlgInterface->ComputerName();
//	sstr3 = pDoc->m_pDlgInterface->GetPgmVersion();
	str_info.Format("Vision No.: %s        %s", sstr1, sstr3);
	m_labelSysInfo.SetText(str_info);
	m_strComputerName = pDoc->m_data.m_strComName = sstr1;
}

void CVisWebView::DrawData(CDC *pDC,int nCam)
{
	if(((CVisWebApp*)AfxGetApp())->m_debugLogWrite == TRUE){
		((CVisWebApp*)AfxGetApp())->WriteLog(PATH_DEBUG_LOG, "debug_log", "DrawData");
	}
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	CString str, strbWhite;
	int nMaxValue=0;
	int nVisionLine = pDoc->m_data.m_nVisionLine;

	pDoc->m_data.m_dAverageBrightness1[2];
	int nYoffset = 270;
	CRect rt;
	rt.SetRect(100,nYoffset,1100,nYoffset*2);
	str.Format("N-Coat = %2.2f  , %.0f", pDoc->m_data.m_dAverageBrightness1[0],pDoc->m_data.m_dAverageBrightness2[0]);
//	pDC->DrawText(str,rt,DT_LEFT);
	DrawText(pDC, CPoint(100,0+nYoffset), str);

	rt.SetRect(100,nYoffset*3,1100,nYoffset*4);
	str.Format("Coat = %2.2f  , %.0f( %d, %d)", pDoc->m_data.m_dAverageBrightness1[1],pDoc->m_data.m_dAverageBrightness2[1],pDoc->m_data.m_nNCoatBrightness[0],pDoc->m_data.m_nNCoatBrightness[1]);
//	pDC->DrawText(str,rt,DT_LEFT);
	DrawText(pDC, CPoint(100,0+nYoffset*3), str);
	//pData->m_dAverageBrightness2[2]

 	str.Format("CoatCut = %2.0f ,Edge TH: %.0f, %d", pDoc->m_data.m_dAverageBrightness2[2],pDoc->m_data.m_dThUp[0],pDoc->m_data.m_nEdgeAverage[0]);
 	DrawText(pDC, CPoint(100,0+nYoffset*5), str);

// 	str.Format("Average = %2.2f , %d", pDoc->m_data.m_dAverageBrightness1[2],pDoc->m_data.m_nEdgeAverage[0]);
// 	str.Format("L=%.0f ,C1=%.0f ,C2=%.0f ,N1=%.0f ,N2=%.0f",pDoc->m_data.m_dAverageData[0],pDoc->m_data.m_dAverageData[1],pDoc->m_data.m_dAverageData[2],pDoc->m_data.m_dAverageData[3],pDoc->m_data.m_dAverageData[4]);
//  	DrawText(pDC, CPoint(100,0+nYoffset*5), str);

	str.Format("Frame = %d , %d , %.2f", pDoc->m_nTotalIns[0],pDoc->m_data.m_nSubFrameCount,m_fFps);
	//	pDC->DrawText(str,rt,DT_LEFT);
	DrawText(pDC, CPoint(100,0+nYoffset*7), str);

	str.Format("Sharpness = %.0f", pDoc->m_data.m_dSharpness1[0]);
	//	pDC->DrawText(str,rt,DT_LEFT);
	DrawText(pDC, CPoint(100,0+nYoffset*9), str);

	
	if(((CVisWebApp*)AfxGetApp())->m_debugLogWrite == TRUE){
		((CVisWebApp*)AfxGetApp())->WriteLog(PATH_DEBUG_LOG, "debug_log", "DrawData-end");
	}

}

void CVisWebView::DrawFocusing(CDC *pDC)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	CPoint p1,p2;
	p1.x = p2.x = pDoc->m_pImage->GetWidth()/2;
	p1.y = 0;
	p2.y = pDoc->m_pImage->GetHeight();
	DrawLine(pDC, p1, p2, COLOR_GREEN, 1);

	p1.x = 0;
	p1.y = p2.y = pDoc->m_pImage->GetHeight()/2;
	p2.x = pDoc->m_pImage->GetWidth();
	DrawLine(pDC, p1, p2, COLOR_GREEN, 1);
	DrawHistoData(pDC);
}

void CVisWebView::DrawNotInsArea(CDC *pDC,int nCam)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	CPoint p1,p2,p3,p4;							//  P1---P2
												//    |X|
												//  P4---P3
	CString str;
	CPoint pt;
	int i=0;//j,
	p1.y = p2.y = 0;
	p3.y = p4.y = pDoc->m_pImage->GetHeight();
	p1.x = p2.x = p3.x = p4.x = 0;
	if(pDoc->m_data.m_nNotInsArea[nCam]==-1){
		p1.x = p4.x =0;
		p2.x = p3.x = pDoc->m_data.m_rectIns[nCam].left;
	}
	else if(pDoc->m_data.m_nNotInsArea[nCam]==1){
		p1.x = p4.x =pDoc->m_data.m_rectIns[nCam].right;
		p2.x = p3.x = pDoc->m_data.m_nCameraWidth;
	}
	else if(pDoc->m_data.m_nNotInsArea[nCam] > 0){
		p1.x = p4.x = 0;
		p2.x = p3.x = pDoc->m_data.m_nNotInsArea[nCam];
	}else if(pDoc->m_data.m_nNotInsArea[nCam] < 0){
		p1.x = p4.x = pDoc->m_pImage->GetWidth();
		p2.x = p3.x = pDoc->m_pImage->GetWidth() + pDoc->m_data.m_nNotInsArea[nCam];
	}
// 	DrawLine(pDC, p2, p3, COLOR_RED, 1);
// 	DrawLine(pDC, p1, p3, COLOR_RED, 1);
// 	DrawLine(pDC, p2, p4, COLOR_RED, 1);
// 	DrawLine(pDC, p1, p4, COLOR_RED, 1);
// 	DrawLine(pDC, p1, p2, COLOR_RED, 1);
// 	DrawLine(pDC, p3, p4, COLOR_RED, 1);

	p1.y = p2.y = (int)(pDoc->m_pImage->GetHeight() / 2);
	p1.x = 0;
	p2.x = pDoc->m_pImage->GetWidth();

//	DrawLine(pDC, p1, p2, COLOR_RED, 1);

	//여기는 픽셀과 다른 눈금	//실제 치수와 근접
/*	for(j=0;j<100;j++)
	{
		p3.x = p4.x = (int)(j*pDoc->m_pImage->GetWidth()/100);
		if(j%5==0)
		{
			if(i%2 == 0){
				p3.y = (int)(pDoc->m_pImage->GetHeight() / 2) - 60;
				p4.y = (int)(pDoc->m_pImage->GetHeight() / 2) + 60;
				str.Format("%d",j);
				DrawText(pDC, CPoint(p3.x,p3.y-30), str);
			}
			else{
				p3.y = (int)(pDoc->m_pImage->GetHeight() / 2) - 40;
				p4.y = (int)(pDoc->m_pImage->GetHeight() / 2) + 40;
			}
			DrawLine(pDC, p3, p4, COLOR_YELLOW, 1);	
			i++;
		}
		else{
			p3.y = (int)(pDoc->m_pImage->GetHeight() / 2) - 20;
			p4.y = (int)(pDoc->m_pImage->GetHeight() / 2) + 20;
			DrawLine(pDC, p3, p4, COLOR_RED, 1);	
		}
	}
	*/
	
//여기는 픽셀과 동일한 눈금
/*	for(j=0;j<103;j++)
	{
		p3.x = p4.x = (int)(j*(pDoc->m_pImage->GetWidth()/100));
		if(j%5==0)
		{
			if(i%2 == 0){
				p3.y = (int)(pDoc->m_pImage->GetHeight() / 2) - 60;
				p4.y = (int)(pDoc->m_pImage->GetHeight() / 2) + 60;
				str.Format("%d",j);
				DrawText(pDC, CPoint(p3.x,p3.y-30), str);
			}
			else{
				p3.y = (int)(pDoc->m_pImage->GetHeight() / 2) - 40;
				p4.y = (int)(pDoc->m_pImage->GetHeight() / 2) + 40;
			}
			DrawLine(pDC, p3, p4, COLOR_YELLOW, 1);	
			i++;
		}
		else{
			p3.y = (int)(pDoc->m_pImage->GetHeight() / 2) - 20;
			p4.y = (int)(pDoc->m_pImage->GetHeight() / 2) + 20;
			DrawLine(pDC, p3, p4, COLOR_RED, 1);	
		}
	}
	*/
}

void CVisWebView::OnDestroy() 
{
	CFormView::OnDestroy();
	m_bRun	= FALSE;
	AddtoList("Pgm Close",0);
	WriteModel();


	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	pDoc->m_RecvtoServerSock.StopComm();	
	pDoc->m_RecvtoNebSock.StopComm();	
	pDoc->m_SendtoServerSock.StopComm();
	pDoc->m_SendtoMarkingSock.StopComm();
	if(MAX_CAMERAS>1)
	{
		pDoc->m_SendtoServerSock1.StopComm();
		pDoc->m_SendtoMarkingSock1.StopComm();
	}
	pDoc->m_SendNebSock.StopComm();
	
}

void CVisWebView::OnBtnInspect() 
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	g_frame_num++;
	Inspect(0);
	if(pDoc->m_data.m_nVisionLine == GL9 ){
		//ljh. 주석
		//Inspect(1);
	}
		
}

int gCount=0;
/*
int CVisWebView::CopyMilImgForAreaReverse(LPBYTE fmOrigin, int nIndex)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	int i;
	BOOL nRet = 1;
	int nheight= pDoc->m_pImage->GetHeight();
	int nwidth = pDoc->m_pImage->GetWidth();

	CTimingProcess* timer = ((CVisWebApp*)AfxGetApp())->m_pTiming;
	unsigned char* fmImg = pDoc->m_pImage->GetImagePtr();

	for(i=0;i<nheight;i++)
	{
		memcpy(fmImg+nwidth*i, fmOrigin+WIDTH*i, WIDTH);
	}

	nRet = 1;

	return nRet;
}
*/

int CVisWebView::CopyMilImg(int nCam)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	BOOL nRet = 1;
	int pcNo;
	CRect rt;
	m_nInspBreak[nCam] = 0;
	static double doldtime1 = 0;
	
	double dtime1 = GetPrecisionTime();

	if(nCam==1){
		if(doldtime1>0){
			m_fFps = float(1000 / ((dtime1-doldtime1)*1000));
		}
		doldtime1 = dtime1;

	}

	int nSimMode = 1,nSimMeter =  dtime1*1000;
	if(nSimMode==1){

	}
	CString str12;
	str12.Format("%d-Cam%d_Frame:%d,Meter:%d,",m_bFullCopy[nCam],nCam,pDoc->m_nTotalIns[nCam],pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck]);
	WriteLog2(str12,nCam);
	if(nCam==2 && !pDoc->m_pDlgInterface->m_bAging && !pDoc->m_pDlgInterface->m_bMasterPc){
		GetPlcData();
	}
	for(int i=0;i<10;i++)pDoc->m_data.m_dInspDetailTime[nCam][i]=0.;
	pDoc->m_data.m_dFullTime[nCam*10+2] = pDoc->m_data.m_dInspDetailTime[nCam][0] = GetPrecisionTime();

	if(nCam==2 && pDoc->m_pVision->m_nBufIndexGrabStt[nCam]%10==0){
		if(m_dOldMeter[0] ==pDoc->m_data.m_nMachineLengthAB[0] && m_dOldMeter[1] == pDoc->m_data.m_nMachineLengthAB[1]){
			m_nOldFrame++;
		}
		else{
			if(pDoc->m_data.m_nMachineLengthAB[0]>0 && pDoc->m_data.m_nMachineLengthAB[1]>0){
				m_nOldFrame = 0;
				m_lbStatsPLC.SetBkColor(COLOR_GREEN);
			}
		}
		m_lbStatsPLC.Invalidate();
		m_dOldMeter[0] = pDoc->m_data.m_nMachineLengthAB[0];
		m_dOldMeter[1] = pDoc->m_data.m_nMachineLengthAB[1];

		if(m_nOldFrame>2){
			//PLC NG
			m_lbStatsPLC.SetBkColor(COLOR_RED);
			if(m_nOldFrame==0)
				AddtoList("PLC Error!",0,1);

		}
	}

	pDoc->m_data.m_dFullTime[nCam*10+0] = GetPrecisionTime();
	int nheight= pDoc->m_pImage->GetHeight();
	int nwidth = pDoc->m_pImage->GetWidth();
	rt.SetRect(0,0,nwidth,nheight);
	static int nBrightGap = 0;
	int nMeanValue = 90;
	int nImageValue = 0;
	unsigned char* fmDspImg = pDoc->m_pImageDsp->GetImagePtr();
	pcNo = pDoc->m_data.m_nVisionLine;

	CTimingProcess* timer = ((CVisWebApp*)AfxGetApp())->m_pTiming;

	unsigned char* fmMil;
	fmMil = pDoc->m_pVision->GetProcessBuf(nCam);

	unsigned char* fmImg = pDoc->m_pImage->GetImagePtr();// = pDoc->m_pImage->GetImagePtr();
	unsigned char* fmImg1 = pDoc->m_pImage1->GetImagePtr();// = pDoc->m_pImage->GetImagePtr();
	unsigned char* fmImg2 = pDoc->m_pImage2->GetImagePtr();// = pDoc->m_pImage->GetImagePtr();


	// m_FullImage thread로 카피

//m_bAging
	int ntmp = 0;

	{
		if((m_bAuto==FALSE && m_bRun==FALSE) || (m_bAuto<0 && m_bRun<0)){
			AddtoList("CopyMil Return",0);
			return 0;
		}

		if(nCam==0){
			m_nInspFrame[0]++;
			if(pDoc->m_pDlgInterface->m_bAging)
				;
			else{
				if(pDoc->m_pDlgInterface->m_bRevserseX){
					for(int i=0;i<nheight;i++)
						for(int x=0;x<nwidth;x++)
							*(fmImg+i*nwidth+(nwidth-x-1)) = *(fmMil+i*nwidth+x);
				}
				else
					memcpy(fmImg, fmMil, nwidth *nheight);// sizeof(unsigned char)*pDoc->m_pImage->GetWidth()*pDoc->m_pImage->GetHeight());

				if(pDoc->m_data.m_nIgnorePixel1[nCam][0]>0){
					for(int k1=0;k1<1000;k1++){
						if(pDoc->m_data.m_nIgnorePixel1[nCam][k1]==0){
							break;
						}
						if(pDoc->m_data.m_nIgnorePixel1[nCam][k1]<0 || pDoc->m_data.m_nIgnorePixel1[nCam][k1] >=CAM_WIDTH_CIS)
							break;
						for(int y=0;y<CAM_HEIGHT_3072;y++){
							*(fmImg+y*nwidth+(pDoc->m_data.m_nIgnorePixel1[nCam][k1])) = *(fmImg+y*nwidth+(pDoc->m_data.m_nIgnorePixel1[nCam][k1]-1)) ;
						}
					}
				}
			}
			if(pDoc->m_pDlgInterface->m_bPreprocessing)
				for(int idx=0;idx<MOD_COUNT;idx++)
					m_bPreprocessing[nCam][idx] = TRUE;

//			if(pDoc->m_data.m_nFullimage==1)
			{
				for(int i=0;i<nheight;i++)
					memcpy((m_Inspect.m_FullImage+CAM_WIDTH_CIS*(i*3)),fmImg+CAM_WIDTH_CIS*i,nwidth);
				//m_dDebugTime[nCam][1] = GetPrecisionTime();//Chcho0115
				m_bFullCopy[0] = TRUE;
			}
//			m_ev_Inspect.SetEvent();	
		}
		else if(nCam==1){
			if(pDoc->m_pDlgInterface->m_bAging)
				;
			else{
				if(pDoc->m_pDlgInterface->m_bRevserseX){
					for(int i=0;i<nheight;i++)
						for(int x=0;x<nwidth;x++)
							*(fmImg1+i*nwidth+(nwidth-x-1)) = *(fmMil+i*nwidth+x);
				}
				else
					memcpy(fmImg1, fmMil, sizeof(unsigned char)*pDoc->m_pImage1->GetWidth()*pDoc->m_pImage1->GetHeight());
				if(pDoc->m_data.m_nIgnorePixel1[nCam][0]>0){
					for(int k1=0;k1<1000;k1++){
						if(pDoc->m_data.m_nIgnorePixel1[nCam][k1]==0){
							break;
						}
						if(pDoc->m_data.m_nIgnorePixel1[nCam][k1]<0 || pDoc->m_data.m_nIgnorePixel1[nCam][k1] >=CAM_WIDTH_CIS)
							break;
						for(int y=0;y<CAM_HEIGHT_3072;y++){
							*(fmImg1+y*nwidth+(pDoc->m_data.m_nIgnorePixel1[nCam][k1])) = *(fmImg1+y*nwidth+(pDoc->m_data.m_nIgnorePixel1[nCam][k1]-1)) ;
						}
					}
				}

			}
			if(pDoc->m_pDlgInterface->m_bPreprocessing)
				for(int idx=0;idx<MOD_COUNT;idx++)
					m_bPreprocessing[nCam][idx] = TRUE;

//			if(pDoc->m_data.m_nFullimage==1)
			{
				for(int i=0;i<nheight;i++)
					memcpy((m_Inspect.m_FullImage+CAM_WIDTH_CIS*(i*3)+CAM_WIDTH_CIS),fmImg1+CAM_WIDTH_CIS*i,nwidth);
				//m_dDebugTime[nCam][1]  = GetPrecisionTime();//Chcho0115
				m_bFullCopy[1] = TRUE;
			}
			//m_ev_Inspect1.SetEvent();
		}
		else {
			if(pDoc->m_pDlgInterface->m_bAging)
				;
			else{
				if(pDoc->m_pDlgInterface->m_bRevserseX){
					for(int i=0;i<nheight;i++)
						for(int x=0;x<nwidth;x++)
							*(fmImg2+i*nwidth+(nwidth-x-1)) = *(fmMil+i*nwidth+x);
				}
				else
					memcpy(fmImg2, fmMil, sizeof(unsigned char)*pDoc->m_pImage2->GetWidth()*pDoc->m_pImage2->GetHeight());
				if(pDoc->m_data.m_nIgnorePixel1[nCam][0]>0){
					for(int k1=0;k1<1000;k1++){
						if(pDoc->m_data.m_nIgnorePixel1[nCam][k1]==0){
							break;
						}
						if(pDoc->m_data.m_nIgnorePixel1[nCam][k1]<0 || pDoc->m_data.m_nIgnorePixel1[nCam][k1] >=CAM_WIDTH_CIS)
							break;
						for(int y=0;y<CAM_HEIGHT_3072;y++){
							*(fmImg2+y*nwidth+(pDoc->m_data.m_nIgnorePixel1[nCam][k1])) = *(fmImg2+y*nwidth+(pDoc->m_data.m_nIgnorePixel1[nCam][k1]-1)) ;
						}
					}
				}

			}
			if(pDoc->m_pDlgInterface->m_bPreprocessing)
				for(int idx=0;idx<MOD_COUNT;idx++)
					m_bPreprocessing[nCam][idx] = TRUE;

//			if(pDoc->m_data.m_nFullimage==1)
			{
				for(int i=0;i<nheight;i++)
					memcpy((m_Inspect.m_FullImage+CAM_WIDTH_CIS*(i*3)+CAM_WIDTH_CIS*2),fmImg2+CAM_WIDTH_CIS*i,nwidth);
				//m_dDebugTime[nCam][1]  = GetPrecisionTime();//Chcho0115
				m_bFullCopy[2] = TRUE;
			}

//			m_ev_Inspect2.SetEvent();
		}
		nRet = 1;

		gCount =0;
	}
	str12.Format("%d-Cam%d_Frame:%d,Meter:%d,Time:%.0fms",m_bFullCopy[nCam],nCam,pDoc->m_nTotalIns[nCam],pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck],	(GetPrecisionTime()- dtime1)*1000 );
	WriteLog2(str12,nCam);

	pDoc->m_data.m_dHooktime[nCam] = GetPrecisionTime()-dtime1;

	m_nMilCopyCount++;

	pDoc->m_data.m_dFullTime[nCam*10+1] = GetPrecisionTime();
	return nRet;
}

void CVisWebView::WriteLog(CString path, CString fileName, CString strdata)
{

	CStdioFile   file;
	CString filename;
	CString strpath;
	CString str;

	strpath.Format(path);
	CreateDirectory(strpath,NULL);	
	filename.Format("%s%s.txt",strpath, fileName);
	
	try{
		g_Mutex.Lock();                    // 뮤텍스를 잠근다.
		
		if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
		{		
			file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText);
			file.WriteString(strdata);
			file.WriteString("\n");	
			file.Close();
		}
		else
		{
			file.SeekToEnd();			
			file.WriteString(strdata);
			file.WriteString("\n");
			file.Close(); 
		}	
		g_Mutex.Unlock();                 // 뮤텍스를 풀어준다.
	}
	catch(...){
		WriteLog("C:\\LOG\\", "grab_log", "******Write Fail******");
	}
}

BOOL CVisWebView::Inspect(int nCam)
{

	return 0;
}

BOOL CVisWebView::Inspect1(int nCam)
{
	return 0;

}

void CVisWebView::SummaryEdgeData()
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	int nEdgeCntAll = 0;
	int nEdgeCntCam[MAX_CAMERAS];
	double dEdgePosInfo[MAX_CAMERAS][40];
	double dEdgePosPixel[MAX_CAMERAS][40][10];//0-7 라인별 data 8평균 data
	int nPixelPos[100]={0,};
	double dComputePos[100]={0,};
	int nLineCount=0,nCamOffset=0;//Master가 되는 Pixel
	double doldpos=0,dcamscale = pDoc->m_data.m_dScaleFactorX[0];//.0423;

	double dt1 = GetPrecisionTime();
	double dinterplation = 0;
	if(dcamscale>0 && pDoc->m_pDlgInterface->m_bEdgeInterpolation){
		dinterplation = pDoc->m_data.m_dInterpolation/dcamscale;//픽셀 보상
	}
	pDoc->m_data.m_dInterpolationPixel = dinterplation;
	for(int i=0;i<MAX_CAMERAS;i++)for(int j=0;j<20;j++){
		dEdgePosInfo[i][j] = 0;for(int k=0;k<10;k++)dEdgePosPixel[i][j][k] = 0;
	}
	//data init  //pDoc->m_data.m_dMisMatchLen[0][i] //pDoc->m_data.m_nMisMatchPixel[0][i]
	for(int i=0;i<MAX_LENGTH;i++){
		pDoc->m_data.m_dMisMatchLen[0][i] =pDoc->m_data.m_dMisMatchLen[1][i] =0;
		pDoc->m_data.m_nMisMatchPixel[0][i]=pDoc->m_data.m_nMisMatchPixel[1][i]=0;
	}
	int ntopback =0,nMeter =pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck];//0 top 1back
	if(nMeter != pDoc->m_data.m_nOldMeter)
		pDoc->m_data.m_nSubFrameCount = 0;
	int nLine1 = 0,nLine2 = 0,ncamline[3] = {0,};
	m_nLineCount=nLine1=pDoc->m_data.m_nNewLineCount ;
	if(m_strComputerName.Mid(8,1)=="M"){//mismatch
		if(nMeter%1==0 && nMeter>0)
			m_bCopyFile = m_bCopyFile1=TRUE;

	}


	pDoc->m_data.m_nOldLineCount = nLine1;
	for(int i=0;i<nLine1;i++){
		pDoc->m_data.m_dNewLineEdgeData1Old[i] = pDoc->m_data.m_dNewLineEdgeData1[i];
		if(pDoc->m_pDlgInterface->m_bEdgeInterpolation && dinterplation!=0){//여기서 data 보상
			if((i==0) || i >= nLine1-1)
				;
			else{//여기서 보상함.
				if(i%2==1)//white -> black// time check
					pDoc->m_data.m_dNewLineEdgeData1[i] -= (dinterplation);
				else
					pDoc->m_data.m_dNewLineEdgeData1[i] += (dinterplation);
			}
		}
	}

	for(int i=0;i<nLine1-1;i++){
		if(pDoc->m_pDlgInterface->m_bEdgeInterpolation )
			pDoc->m_data.m_dNewLineEdgeData1[i+1] += pDoc->m_data.m_dOffsetData[0][i];


	}
	if(m_nOldLine<=0)//check
		m_nOldLine = nLine1;
	else{
		if(m_nOldLine != nLine1){
			m_nOldLine = -1;
		}
	}
	//data average
	double dt2 = GetPrecisionTime();

	BOOL	bUseAve = TRUE,bJump= FALSE;
	if(pDoc->m_pDlgInterface->m_bLineAve){

		for(int i=0;i<nLine1 && nLine1>3 && nLine1%2 ==0;i++){
			if(pDoc->m_data.m_dNewLineEdgeData1[i]>0){
				if(pDoc->m_data.m_dOldLineEdgeData1[i]==0)
					pDoc->m_data.m_dOldLineEdgeData1[i] = pDoc->m_data.m_dNewLineEdgeData1[i];
				else{
					if(abs(pDoc->m_data.m_dOldLineEdgeData1[i] - pDoc->m_data.m_dNewLineEdgeData1[i]) > 20 ){//10 픽셀 이상 차이가 날경우
						pDoc->m_data.m_dNewLineEdgeData1[i] = pDoc->m_data.m_dOldLineEdgeData1[i];
						pDoc->m_data.m_dOldLineEdgeData1[i]=0;
						AddtoInsLog("LineError");
						bJump = TRUE;
					}
					else
						pDoc->m_data.m_dOldLineEdgeData1[i] = pDoc->m_data.m_dNewLineEdgeData1[i];
				}
				pDoc->m_data.m_dLineAve[pDoc->m_nTotalIns[0]%10][i] =pDoc->m_data.m_dNewLineEdgeData1[i];//+nCamOffset ;
			}
			else
				pDoc->m_data.m_dLineAve[pDoc->m_nTotalIns[0]%10][i] = 0;//pDoc->m_data.m_dLineAve[j][i]/pDoc->m_pDlgInterface->m_nLineAveFrame;
		}
		for(int i=0;i<pDoc->m_pDlgInterface->m_nLineAveFrame && nLine1>2;i++){
			if(pDoc->m_data.m_dLineAve[i][nLine1-1]>0)
				bUseAve = TRUE;
			else
				bUseAve = FALSE;
		}
		if(nLine1<2)
			bUseAve = FALSE;
		pDoc->m_data.m_dLineAve[pDoc->m_nTotalIns[0]%10][MAX_LENGTH-1] = nLine1;
		m_nLineCountMiss = 0;
		for(int i=0;i<pDoc->m_pDlgInterface->m_nLineAveFrame;i++){
			if(pDoc->m_data.m_dLineAve[i][MAX_LENGTH-1] != nLine1){
				m_nLineCountMiss++;
				bJump = TRUE;
			}
		}


	}
	if(bUseAve && pDoc->m_pDlgInterface->m_bLineAve && bJump==FALSE){
		//		if(m_nLineCountMiss
		int nkk = 0,nk2=0,nc123=0;
		double dsum=0;
		for(int i=0;i<nLine1;i++){
			dsum=0;nc123 = 0;
			if(pDoc->m_nTotalIns[0]>pDoc->m_pDlgInterface->m_nLineAveFrame){
				for(int j=pDoc->m_nTotalIns[0];j>pDoc->m_nTotalIns[0]-pDoc->m_pDlgInterface->m_nLineAveFrame && j>0;j--){
					if(pDoc->m_data.m_dLineAve[(j+10)%10][0]<100)
						nc123 = nc123;
					if(pDoc->m_data.m_dLineAve[(j+10)%10][i]>0){
						dsum += pDoc->m_data.m_dLineAve[(j+10)%10][i];
						nc123++;
					}
				}
				if(nc123==0)nc123 = 1;
				dsum /= nc123;//pDoc->m_pDlgInterface->m_nLineAveFrame;
				pDoc->m_data.m_dNewLineEdgeData1[i] = dsum;
			}
			else{
			}
		}
	}

	double dt3 = GetPrecisionTime();

	if(pDoc->m_data.m_nSubFrameCount>18){
		pDoc->m_data.m_nSubFrameCount = 0;return;
	}

	if(m_strComputerName.Find("BACK")>=0 || pDoc->m_data.m_strComName.Mid(9,1)=="B")ntopback = 1;	  
	for(int i=0;i<nLine1;i++){
		if(i>=MAX_LENGTH-1)break;
		if(i==0)	pDoc->m_data.m_dTotalLength[0] = pDoc->m_data.m_dNewLineEdgeData1[0];
		else		pDoc->m_data.m_dTotalLength[1] = pDoc->m_data.m_dNewLineEdgeData1[i];
		pDoc->m_data.m_nLinePosPixel[i] = pDoc->m_data.m_dNewLineEdgeData1[i]+nCamOffset;
		pDoc->m_data.m_dLinePosLength[i] = (pDoc->m_data.m_dNewLineEdgeData1[i]+nCamOffset)*dcamscale;
		if(m_strComputerName.Find("BACK")>=0 ||  pDoc->m_data.m_strComName.Mid(9,1)=="B")
			pDoc->m_data.m_nFullLineData[ntopback][nMeter%100][pDoc->m_data.m_nSubFrameCount][i]=pDoc->m_data.m_dNewLineEdgeData1[i]+nCamOffset;
		else
			pDoc->m_data.m_nFullLineData[ntopback][nMeter%100][pDoc->m_data.m_nSubFrameCount][i+1]=pDoc->m_data.m_dNewLineEdgeData1[i]+nCamOffset;

	}
	pDoc->m_data.m_nFullLineData[ntopback][nMeter%100][pDoc->m_data.m_nSubFrameCount][0]=nLineCount;

	if(m_strComputerName.Find("BACK")>=0 ||  pDoc->m_data.m_strComName.Mid(9,1)=="B"){
		for(int i=0;i<nLine1;i++){
			pDoc->m_data.m_dMisMatchLen[1][i] = pDoc->m_data.m_dLinePosLength[i];
			pDoc->m_data.m_nMisMatchPixel[1][i] = pDoc->m_data.m_nLinePosPixel[i];
			pDoc->m_data.m_dMisTopBackData[1][i] = pDoc->m_data.m_dNewLineEdgeData1[i];//미스매치 동기화 백 데이터
			pDoc->m_data.m_dMisTopBackData1[1][i] = pDoc->m_data.m_dNewLineEdgeData1[i];//미스매치 동기화 백 데이터 //백데이터 넣기

			int nmeter1 = (nMeter+pDoc->m_pDlgInterface->m_nDisplayMeter)%10;
			int nmeter2 = (nMeter+pDoc->m_pDlgInterface->m_nDisplayMeter+1)%10;
			pDoc->m_data.m_dDrawMisData[1][nmeter1][0][i] =  pDoc->m_data.m_dNewLineEdgeData1[i];//미스매치 동기화 백 데이터  10meter 배열에 넣기
			pDoc->m_data.m_dDrawMisData[1][nmeter2][0][i] =  pDoc->m_data.m_dNewLineEdgeData1[i];//미스매치 동기화 백 데이터  10meter 배열에 넣기

		}
		//top data는 이미 들어가 있음.
		int nOffsetMeter = abs((1000+nMeter)- pDoc->m_pDlgInterface->m_dTopBackDistance);
		if(pDoc->m_data.m_strComName.Mid(8,1)=="M")
			nOffsetMeter = abs((1000+nMeter)- pDoc->m_pDlgInterface->m_dTopBackDistance+2);

		//pDoc->m_data.m_nFullLineData[0][nMeter][ncount][MAX_LENGTH-1]
		double dscaletop = m_dTopScale;//double(pDoc->m_data.m_nFullLineData[0][nOffsetMeter%100][pDoc->m_data.m_nSubFrameCount][MAX_LENGTH-1])/1000000;
		int nLineCountTop = pDoc->m_data.m_nFullLineData[0][nOffsetMeter%100][pDoc->m_data.m_nSubFrameCount][MAX_LENGTH-2];
		pDoc->m_data.m_nNewTopCount = nLine1;//nLineCountTop;
		for(int i=0;i<nLine1;i++){
			pDoc->m_data.m_dMisMatchLen[0][i] = pDoc->m_data.m_nFullLineData[0][nOffsetMeter%100][pDoc->m_data.m_nSubFrameCount][i]*dscaletop;
			pDoc->m_data.m_nMisMatchPixel[0][i] = pDoc->m_data.m_nFullLineData[0][nOffsetMeter%100][pDoc->m_data.m_nSubFrameCount][i];
			if(pDoc->m_data.m_nMisMatchPixel[0][i] >0)
				pDoc->m_data.m_nMisMatchPixel[0][i] = pDoc->m_data.m_nMisMatchPixel[0][i];
		}
		//여기 길이별 미스매치 넣기//chcho
		pDoc->m_data.m_dMisMatchLen[0][MAX_LENGTH-1] = dscaletop;
		pDoc->m_data.m_dMisMatchLen[1][MAX_LENGTH-1] = dcamscale;
		if(dscaletop>0.01)
			m_dScaleSum = dscaletop;
		if(OnebyOneMatch(1,pDoc->m_data.m_nSubFrameCount,nLine1)==0)
			m_bMismatchUse = TRUE;
		else
			m_bMismatchUse = FALSE;
		//mismatch write()
		if(nLine1>0 && pDoc->m_data.m_dMisMatchData[1][pDoc->m_data.m_nSubFrameCount][1]>0&& pDoc->m_data.m_dMisMatchData[2][pDoc->m_data.m_nSubFrameCount][1]>0){
			//top용 미스매치 데이터
			if(m_strComputerName.Find("CHO")>=0)
				;
			else{
				if(m_strComputerName.Mid(8,1) == "H"){//10m 기준
					fnWriteData5(ConvertCharToStr(cLotID),pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck],pDoc->m_data.m_nSubFrameCount,nLine1);
					//mismatch에서 동기화 하기 위한 data
					if(nLine1 == pDoc->m_data.m_nNewTopCount){
						double dtopscale = dscaletop;
						double dbackscame = dcamscale;
						int nLine = nLine1;
						CString strtop="",strback="",strmis="",strtmp1="",strwidth1="",strwidth2="";
						double dold1=0,dold2=0;
						//헤드부도 m_dMisTopBackData1에 데이터 들어가는 지 확인필요.
						//EPC 기준으로 Data를 정리 해야함.
						if(pDoc->m_data.m_nEpcPos==1){
							for(int i=0;i<nLine;i++){//Data Put
								strtmp1.Format("%.6f,",pDoc->m_data.m_dMisTopBackData1[0][i]);//topdata pixel
								strtop+= strtmp1;
								strtmp1.Format("%.6f,",pDoc->m_data.m_dMisTopBackData1[1][i]);//backdata pixel
								strback+= strtmp1;
								strtmp1.Format("%.6f,",pDoc->m_data.m_dMisTopBackData1[2][i]);//mismatch mm
								strmis+= strtmp1;

								if(dold1>0){
									strtmp1.Format("%.6f,",(pDoc->m_data.m_dMisTopBackData1[0][i]-dold1)*dtopscale);//top mm
									strwidth1+= strtmp1;
									strtmp1.Format("%.6f,",(pDoc->m_data.m_dMisTopBackData1[1][i]-dold2)*dbackscame);//back mm
									strwidth2+= strtmp1;
								}
								else{
									strtmp1.Format("0.000000,");//top mm
									strwidth1+= strtmp1;
									strtmp1.Format("0.000000,");//back mm
									strwidth2+= strtmp1;
								}

								dold2 = pDoc->m_data.m_dMisTopBackData1[1][i];
								dold1 = pDoc->m_data.m_dMisTopBackData1[0][i];
							}
						}
						else if(pDoc->m_data.m_nEpcPos==2){
							//Data reverse
							double dtmptp[20]={0,},dtmpbp[20]={0,},dtmpmis[20]={0,},dtmptm[20]={0,},dtmpbm[20]={0,};
							int k12 =  0,nleft1[2],nright1[2];
							double dold1=0,dold2=0;

							nleft1[0] = pDoc->m_data.m_dMisTopBackData1[0][0];
							nleft1[1] = pDoc->m_data.m_dMisTopBackData1[1][0];
							nright1[0] = pDoc->m_data.m_dMisTopBackData1[0][nLine-1];
							nright1[1] = pDoc->m_data.m_dMisTopBackData1[1][nLine-1];
							for(int i=nLine-1;i>=0 && i<20;i--){//Data Put
								dtmptp[k12] = nright1[0] - pDoc->m_data.m_dMisTopBackData1[0][i] + nleft1[0];//top pixel
								dtmpbp[k12] = nright1[1] - pDoc->m_data.m_dMisTopBackData1[1][i] + nleft1[1];//back pixel
								dtmpmis[k12] = pDoc->m_data.m_dMisTopBackData1[2][i];//mismatch mm3
								dtmptm[k12] = pDoc->m_data.m_dMisTopBackData1[0][i] ;//top mm
								dtmpbm[k12] = pDoc->m_data.m_dMisTopBackData1[1][i] ;//back mm
								k12++;
							}
							for(int i=0;i<nLine;i++){//Data Put
								strtmp1.Format("%.6f,",dtmptp[i]);//topdata pixel
								strtop+= strtmp1;
								strtmp1.Format("%.6f,",dtmpbp[i]);//backdata pixel
								strback+= strtmp1;
								strtmp1.Format("%.6f,",dtmpmis[i]);//mismatch mm
								strmis+= strtmp1;

								if(dold1>0){
									strtmp1.Format("%.6f,",(dtmptp[i]-dold1)*dtopscale);//top mm
									strwidth1+= strtmp1;
									strtmp1.Format("%.6f,",(dtmpbp[i]-dold2)*dbackscame);//back mm
									strwidth2+= strtmp1;
								}
								else{
									strtmp1.Format("0.000000,");//top mm
									strwidth1+= strtmp1;
									strtmp1.Format("0.000000,");//back mm
									strwidth2+= strtmp1;
								}

								dold2 = dtmpbp[i];
								dold1 = dtmptp[i];
							}
						}

						fnWriteData9(ConvertCharToStr(cLotID), nMeter,pDoc->m_data.m_nSubFrameCount, dtopscale, dbackscame, nLine, strtop, strback, strmis,strwidth1,strwidth2); //미스매치부 탑백 동기화 관련
						fnWriteDataFull1(ConvertCharToStr(cLotID), nMeter,dtopscale, dbackscame, dtopscale, dbackscame, nLine, strmis, strmis,strwidth1,strwidth2,strwidth1,strwidth2,strtop,strback,strtop,strback); //미스매치부 탑백 동기화 관련

					}
				}
				else{
					if(nLine1 == pDoc->m_data.m_nNewTopCount){
						double dtopscale = dscaletop;
						double dbackscale = dcamscale;
						int nLine = nLine1;
						CString strtop="",strback="",strmis="",strtmp1="",strwidth1="",strwidth2="";
						CString strtop10="",strback10="",strmis10="",strtmp10="",strwidth10="",strwidth20="";
						double dold1=0,dold2=0, dold10=0,dold20=0;

						for(int i=0;i<nLine;i++){//Data Put
							//Mismatch part
							strtmp1.Format("%.6f,",pDoc->m_data.m_dMisTopBackData1[0][i]);
							strtop+= strtmp1;
							strtmp1.Format("%.6f,",pDoc->m_data.m_dMisTopBackData1[1][i]);
							strback+= strtmp1;
							strtmp1.Format("%.6f,",pDoc->m_data.m_dMisTopBackData1[2][i]);
							strmis+= strtmp1;
	
// 							if(i==0)								// 20201016 kjh
// 								strtmp1.Format(_T("0"));
// 							else
								strtmp1.Format("%.6f,",(pDoc->m_data.m_dMisTopBackData1[0][i]-dold1)*dtopscale);//top
							strwidth1+= strtmp1;

// 							if(i==0)
// 								strtmp1.Format(_T("0"));
// 							else
								strtmp1.Format("%.6f,",(pDoc->m_data.m_dNewLineEdgeData1[i]-dold2)*dbackscale);//back
							strwidth2+= strtmp1;
							dold2 = pDoc->m_data.m_dNewLineEdgeData1[i];
							dold1 = pDoc->m_data.m_dMisTopBackData1[0][i];

							///////////////////////////head part
							//pDoc->m_data.m_nFullLineData1[0][nMeter][ncount][i]
							int nOffmeter = (pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck]+1000 - pDoc->m_pDlgInterface->m_nHeadMisDistance)%100;
							strtmp10.Format("%.6f,",pDoc->m_data.m_nFullLineData1[0][nOffmeter][0][i]);//top pixel
							strtop10+= strtmp10;
							strtmp10.Format("%.6f,",pDoc->m_data.m_nFullLineData1[1][nOffmeter][0][i]);//back pixel
							strback10+= strtmp10;
							strtmp10.Format("%.6f,",pDoc->m_data.m_nFullLineData1[2][nOffmeter][0][i]);//mismatch
							strmis10+= strtmp10;

							strtmp10.Format("%.6f,",pDoc->m_data.m_nFullLineData1[3][nOffmeter][0][i]);//top mm
							strwidth10+= strtmp10;
							strtmp10.Format("%.6f,",pDoc->m_data.m_nFullLineData1[4][nOffmeter][0][i]);//back mm
							strwidth20+= strtmp10;
							dold2 = pDoc->m_data.m_dNewLineEdgeData1[i];
							dold1 = pDoc->m_data.m_dMisTopBackData1[0][i];

						}
						//						fnWriteData6(ConvertCharToStr(cLotID), nMeter, dtopscale, dbackscame, nLine, strtop, strback, strmis); //미스매치부 탑백 동기화 관련
						fnWriteData7(ConvertCharToStr(cLotID), nMeter, dtopscale, dbackscale, nLine, strtop, strback, strmis,strwidth1,strwidth2); //미스매치부 탑백 동기화 관련
						double dtopscale1 =pDoc->m_data.m_dMisbatchScale1[0];
						double dbackscale1 =pDoc->m_data.m_dMisbatchScale1[1];
						//Full Log
						fnWriteDataFull(ConvertCharToStr(cLotID), nMeter,dtopscale1, dbackscale1, dtopscale, dbackscale, nLine, strmis10, strmis,strwidth10,strwidth20,strwidth1,strwidth2,strtop10,strback10,strtop,strback); //미스매치부 탑백 동기화 관련
					}
				}

				WriteMisMatchData1( pDoc->m_data.m_nSubFrameCount,nLine1);//프레임당 풀데이터(mm 픽섹 미스매치
				double d12 = GetPrecisionTime();
				WriteMisMatchData2(pDoc->m_data.m_nSubFrameCount,nLine1);//프레임당 피치 mm 데이터 탑/백  //plc Data Write
				CString strtime;
				strtime.Format("Time - %.0f",(GetPrecisionTime()-d12)*1000);
			}
			//				AddtoList(strtime,0);
		}
		//reverse data input
		for(int i=0;i<MAX_LENGTH-2;i++){
			//누적 거리
			// 		pDoc->m_data.m_dMisMatchLen[0][i] =dtmp1[i];
			// 		pDoc->m_data.m_nMisMatchPixel[0][i]=ntmp1[i];
			// //		pDoc->m_data.m_dMisMatchLen[0][i] =ntmp1[i]*dcamScale[0];
			// 		pDoc->m_data.m_dMisMatchLen[0][i] =dtmp1[i];
			// 		pDoc->m_data.m_nMisMatchPixel[0][i]=ntmp1[i];
			pDoc->m_data.m_dMisMatchLen[0][i] = pDoc->m_data.m_dMisMatchLen[1][i]=0;
			pDoc->m_data.m_nMisMatchPixel[0][i] = pDoc->m_data.m_nMisMatchPixel[1][i] = 0;
		}
		if(m_strComputerName.Mid(8,1)=="M"){//mismatch

		}
		else{
			if(nMeter%10==0 && m_bCopyFile1 == FALSE)
				m_bCopyFile = m_bCopyFile1=TRUE;
			else if(nMeter%10!=0 )
				m_bCopyFile1=FALSE;
		}
	}
	else{
		fnWriteData3(ConvertCharToStr(cLotID),pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck],pDoc->m_data.m_nSubFrameCount,  nLine1) ;//1M edge data
		//		if(m_strComputerName.Find("DA01TOP")>=0)
		fnWriteData4(ConvertCharToStr(cLotID),pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck],pDoc->m_data.m_nSubFrameCount,  nLine1) ;//1M edge data
		if(m_strComputerName.Mid(8,1)=="M"){
			if(nMeter%1==0 && m_bCopyFile1 == FALSE)
				m_bCopyFile = m_bCopyFile1=TRUE;
			else if(nMeter%1!=0 )
				m_bCopyFile1=FALSE;
		}
		else{
			if(nMeter%10==0 && m_bCopyFile1 == FALSE)
				m_bCopyFile = m_bCopyFile1=TRUE;
			else if(nMeter%10!=0 )
				m_bCopyFile1=FALSE;
		}

	}
	//
	//server에서 받아가는 data
	if(pDoc->m_pDlgInterface->m_bServerDataSend)
		WrtieMeterData(ConvertCharToStr(cLotID),pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck],pDoc->m_data.m_nSubFrameCount,nLine1,pDoc->m_data.m_nEpcPos);//CString strLot,int nMeter, int nSubFrame, int nLineCount
	double dt4 = GetPrecisionTime();

	pDoc->m_data.m_nSubFrameCount++;
	pDoc->m_data.m_nOldMeter = nMeter;
}

CString CVisWebView::ConvertCharToStr(char* cChar)
{
	CString strTemp;
	strTemp.Empty();
	strTemp.Format("%s", cChar);

	return strTemp;

}

void CVisWebView::AverageDataSet(int nCam,BOOL bokng)
{
	//////////////////////Camera & Inspection Stats Average Sending
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	int npc = pDoc->m_data.GetVisionLine(nCam);
	double dtmp = 0,dtmp1=0;
	char strEdge[300];
	static int nCount = 0;

	//server에 전송하기 위해 가장 강한 값을 뽑는다.
//	pDoc->m_data.m_nMaxBrightness[nCam] = pDoc->m_data.m_nMinBrightness[nCam] = 0;
	for(int i=0;i<pDoc->m_data.m_nUseIndex;i++){
		if(pDoc->m_data.m_nMaxImageValue[nCam][i]>pDoc->m_data.m_nMaxBrightness[nCam])pDoc->m_data.m_nMaxBrightness[nCam] = pDoc->m_data.m_nMaxImageValue[nCam][i];
		if(pDoc->m_data.m_nMinImageValue[nCam][i]>pDoc->m_data.m_nMinBrightness[nCam])pDoc->m_data.m_nMinBrightness[nCam] = pDoc->m_data.m_nMinImageValue[nCam][i];
	}

	//Server Data Send
	if(((nAveCount[nCam]%10 ==0 && npc != GL9 && nAveCount[nCam] !=0) || (nAveCount[nCam]%20 ==0  && nAveCount[nCam] !=0 && npc == GL9)))// && pDoc->m_data.m_nMachine==1)
	{
		CPacket* packet = new CPacket;
	
		if(nAveCount[nCam]!=0){
			if(npc==GL9){
				dtmp = pDoc->m_data.m_dAveRealBright[nCam]/nAveCount[nCam];
			}
			else{
				dtmp = dCmaAverage[nCam]/nAveCount[nCam];
			}
			
		}
		else dtmp = 0;
		if(nEdgeCnt[nCam]!=0)	dtmp1 = dCamEdge[nCam]/nEdgeCnt[nCam];
		else			dtmp1 = 0;

		if(m_nThCount[nCam]==0)
		{
			pDoc->m_data.m_dAveThUp[nCam] = pDoc->m_data.m_dAveThDn[nCam] = pDoc->m_data.m_dCrossGap[nCam] =  0;
		}
		else
		{
			pDoc->m_data.m_dAveThUp[nCam]	=	pDoc->m_data.m_dAveThUp[nCam]/m_nThCount[nCam];
			pDoc->m_data.m_dAveThDn[nCam]	=	pDoc->m_data.m_dAveThDn[nCam]/m_nThCount[nCam];
	
			//Peak 사용.
			if(npc==GL9 && pDoc->m_data.m_dCrossCandidatecnt[nCam] >0)
				pDoc->m_data.m_dCrossGap[nCam] =	pDoc->m_data.m_dCrossGap[nCam];

			else
				pDoc->m_data.m_dCrossGap[nCam] =	pDoc->m_data.m_dCrossGap[nCam]/m_nThCount[nCam];
		}
		if((npc==GL9 || npc==GL2)&& nAveCount[nCam] !=0)
		{
			pDoc->m_data.m_dAveRealBright[nCam] =pDoc->m_data.m_dAveRealBright[nCam]/nAveCount[nCam];
		}
		else
		{
			pDoc->m_data.m_dAveRealBright[nCam] =dtmp;
		}
			
		if(nAveCount[nCam]!=0)
		{
			pDoc->m_data.m_dInspTime[nCam] = pDoc->m_data.m_dInspTime[nCam]/nAveCount[nCam];
			pDoc->m_data.m_dAveFps[nCam] = pDoc->m_data.m_dAveFps[nCam]/nAveCount[nCam];
			pDoc->m_data.m_dAveHddRemain = pDoc->m_data.m_dAveHddRemain/nAveCount[nCam];
			pDoc->m_data.m_dAveSharp[nCam] = pDoc->m_data.m_dSumSharp[nCam]/nAveCount[nCam];
		}
		else
		{
			pDoc->m_data.m_dInspTime[nCam] = 0;
			pDoc->m_data.m_dAveFps[nCam] = 0;
			pDoc->m_data.m_dAveHddRemain = 0;
			pDoc->m_data.m_dAveSharp[nCam] = 0;
		}
		//1273.1_70_70_3_16_0.000_290.88_0.00_8.80_14.17
		//edge_realBright_DspBright_avethup_avethdn_CrossGap_TacTime_FpS_HDDRemain_SharpnessAve
		if(pDoc->m_data.m_strMachineName.Find("DC0")>=0 ||pDoc->m_data.m_strMachineName.Find("BC01")>=0 ||pDoc->m_data.m_strMachineName.Find("CC01")>=0){
			sprintf(strEdge, "%.1f_%.0f_%.0f_%.0f_%.0f_%.3f_%.2f_%.2f_%.2f_%.2f", 
				(dtmp1*pDoc->m_data.m_dScaleFactorX[nCam]) + pDoc->m_data.m_dCalibSttX[nCam],
				dtmp,dtmp,pDoc->m_data.m_dAveThUp[nCam],pDoc->m_data.m_dAveThDn[nCam],pDoc->m_data.m_dCrossGap[nCam],
				pDoc->m_data.m_dInspTime[nCam],pDoc->m_data.m_dAveFps[nCam],pDoc->m_data.m_dAveHddRemain,pDoc->m_data.m_dAveSharp[nCam]);
		}
		else{
			sprintf(strEdge, "%.1f_%.0f_%.0f_%.0f_%.0f_%.3f_%.2f_%.2f_%.2f_%.2f",
				(dtmp1*pDoc->m_data.m_dScaleFactorX[nCam]) + pDoc->m_data.m_dCalibSttX[nCam],
				pDoc->m_data.m_dAveRealBright[nCam],dtmp,pDoc->m_data.m_dAveThUp[nCam],pDoc->m_data.m_dAveThDn[nCam],pDoc->m_data.m_dCrossGap[nCam],
				pDoc->m_data.m_dInspTime[nCam],pDoc->m_data.m_dAveFps[nCam],pDoc->m_data.m_dAveHddRemain,pDoc->m_data.m_dAveSharp[nCam]);
		}
		if(nCam==0)
			pDoc->m_SendtoServerSock.SendInstantData_LocalHost(strEdge,dtmp);//str : edge_realBright_DspBright_avethup_avethdn_CrossGap_TacTime_FpS_HDDRemain , double : ave Brightness
		else
			pDoc->m_SendtoServerSock1.SendInstantData_LocalHost(strEdge,dtmp);//str : edge_realBright_DspBright_avethup_avethdn_CrossGap_TacTime_FpS_HDDRemain , double : ave Brightness

		delete packet;
		nCount++;

		if(nCount==1 ){
			nCount = 0;
			fnWriteEdge(pDoc->m_data.m_rectIns[nCam].left,pDoc->m_data.m_rectIns[nCam].right,pDoc->m_data.m_nPolarEdge[nCam],strEdge,nCam);
		}
	
		pDoc->m_data.m_dCrossGap[nCam] = pDoc->m_data.m_dAveThUp[nCam] = pDoc->m_data.m_dAveThDn[nCam] = pDoc->m_data.m_dAveRealBright[nCam] =
			 pDoc->m_data.m_dCrossCandidatecnt[nCam] = pDoc->m_data.m_dInspTime[nCam] = 
			pDoc->m_data.m_dAveFps[nCam] = pDoc->m_data.m_dAveHddRemain =0.0;
		m_nThCount[nCam] = nAveCount[nCam] = nEdgeCnt[nCam] = 0;
		dCmaAverage[nCam] = dCamEdge[nCam] =pDoc->m_data.m_dSharpness[nCam]= 0.0;
		pDoc->m_data.m_dSumSharp[nCam]  = 0.0;
	}
	if(nCam == 0){
		pDoc->m_data.m_dAveHddRemain += m_dRemainHDDSpace;
	}

	dCmaAverage[nCam] += m_avgBrightness[nCam];
	pDoc->m_data.m_dAveFps[nCam] += m_fFps;
	/////////////////Sharpness
	pDoc->m_data.m_dSumSharp[nCam] += pDoc->m_data.m_dSharpness1[nCam];

	pDoc->m_data.m_dAveRealBright[nCam] += pDoc->m_data.m_dRealBrightness[nCam];
	if(bokng==1){
		//수정 필요.
		pDoc->m_data.m_dAveThUp[nCam]	+=	pDoc->m_data.m_nMaxBrightness[nCam];
		pDoc->m_data.m_dAveThDn[nCam]	+=	pDoc->m_data.m_nMinBrightness[nCam];
		//Cross만 해당.//Peak로 수정.
		if(pDoc->m_data.m_dSharpness[nCam]>=pDoc->m_data.m_dCrossGap[nCam])
			pDoc->m_data.m_dCrossGap[nCam]	=	pDoc->m_data.m_dSharpness[nCam];
		//평균 사용.
		//		pDoc->m_data.m_dCrossGap+=	pDoc->m_data.m_dSharpness;
		m_nThCount[nCam]++;
	}
	if(pDoc->m_data.m_nPolarEdge[nCam] > 0){
		if(pDoc->m_data.m_nInspDirection[nCam]==0 ||pDoc->m_data.m_nInspDirection[nCam]==2)
			dCamEdge[nCam] += pDoc->m_data.m_nPolarEdge[nCam];
		else{
			dCamEdge[nCam] += abs(pDoc->m_data.m_nCameraWidth-pDoc->m_data.m_nPolarEdge[nCam]);
			//20150703 ljh 수정
			//dCamEdge[nCam] += abs(pDoc->m_pImage->GetWidth()-pDoc->m_data.m_nPolarEdge[nCam]);
		}

		nEdgeCnt[nCam]++;
	}
	nAveCount[nCam]++;

}

void CVisWebView::SendMarkingData(int nCam)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	//마킹기 불량 Data 전송
	if(m_nOldCount[nCam] >0 && pDoc->m_data.m_nMachine==1)
	{//불량이 존재하고, 코팅일경우.
		CPacket* packet = new CPacket;
		int nbroadtmp = 0;
		char** file_list = new char*[m_nOldCount[nCam]];
		memset(file_list, 0, m_nOldCount[nCam]);
		char path[100];//("c:\\Glim\\set\\");
		sprintf(path, "%s", "c:\\Glim\\set\\");
		char fileName[100];
		char buff[100];
		for(int i=0; i<m_nOldCount[nCam]; i++)
		{
			if(pDoc->m_data.m_bSaveBmp){
				sprintf(buff, "%d_%d.bmp", 777, i%8);
			}
			else{
				sprintf(buff, "%d_%d.jpg", 777, i%8);
			}
			sprintf(fileName, "%s%s",path, buff);
			//str = path+tt;
			file_list[i] = new char[MAX_BADIMAGE_FILENAME];
			memset(file_list[i], 0, MAX_BADIMAGE_FILENAME);
			//strcpy(file_list[i], str.LockBuffer());
			strcpy(file_list[i], fileName);
		}
		if(	pDoc->m_data.m_strComName == "GL608")
		{//에지 Data 전송
			if(pDoc->m_data.m_nInspDirection[nCam]%2 == 0)
			{
				if(pDoc->m_data.m_nBroadEdge[nCam] <=0)
					nbroadtmp = nbroadtmp;//int(pDoc->m_data.m_dScaleFactorX);
				else
					nbroadtmp = pDoc->m_data.m_nBroadEdge[nCam]*pDoc->m_data.m_dScaleFactorX[nCam];
			}
			else
			{
				if(pDoc->m_data.m_nBroadEdge[nCam] <=0)
					nbroadtmp = nbroadtmp;//int(pDoc->m_data.m_dCalibSttX);
				else
					nbroadtmp = float(((pDoc->m_data.m_nCameraWidth - pDoc->m_data.m_nBroadEdge[nCam]) *  pDoc->m_data.m_dScaleFactorX[nCam]) + pDoc->m_data.m_dCalibSttX[nCam]);//Camera Reverse
			}
		}

		//마킹서버 전송
		//if(pDoc->m_data.m_nMachine==1){ //RO필터 마킹서버 전송안함
		if(pDoc->m_data.m_useMarking == 0){

		}
		else{
//			packet->MakeDataPacket(g_frame_num-1, m_nOldCount[nCam],nbroadtmp, pDoc->m_data.fpDefectType[nCam], pDoc->m_data.fpX[nCam], pDoc->m_data.fpY[nCam], pDoc->m_data.fpSizeX[nCam], pDoc->m_data.fpSizeY[nCam],file_list);// pDoc->m_data.m_cFilename);
			if(nCam==0){
				SendMessage(WM_SIMULATEMARK, (DWORD)packet, 100);
			}
			else{
				SendMessage(WM_SIMULATEMARK1, (DWORD)packet, 100);
			}
		}
		//data 초기화 지금 필요한가?//chcho
		for(int i=0; i<m_nOldCount[nCam];i++)//검사 시작전 reset data에서 초기화함.
			pDoc->m_data.fpX[nCam][i]=pDoc->m_data.fpY[nCam][i]=pDoc->m_data.fpSizeX[nCam][i]= pDoc->m_data.fpSizeY[nCam][i]=0;
		memset(pDoc->m_data.m_cFilename[nCam],0,MAX_BADIMAGE_FILENAME*MAX_REALDEFECT);
		for(int i=0; i<m_nOldCount[nCam]; i++)
		{
			if(file_list[i])
			{
				delete [] file_list[i];
				file_list[i] = NULL;
			}
		}
		if(m_nOldCount[nCam] ==0);
		else
		{
			if(file_list)
				delete [] file_list ;
		}
		delete packet;
	}	
	m_nOldCount[nCam] = 0;
}

void CVisWebView::SendMarkingDataTest(int nCam)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	m_nOldCount[nCam] = 1;
	//마킹기 불량 Data 전송
	if(m_nOldCount[nCam] > 0 && pDoc->m_data.m_nMachine == 1 && pDoc->m_data.m_useMarking == 1)
	{//불량이 존재하고, 코팅일경우.
		CPacket* packet = new CPacket;
		int nbroadtmp = 0;
		char** file_list = new char*[m_nOldCount[nCam]];
		memset(file_list, 0, m_nOldCount[nCam]);
		char path[100];//("c:\\Glim\\set\\");
		sprintf(path, "%s", "c:\\Glim\\set\\");
		char fileName[100];
		char buff[100];
		for(int i=0; i<m_nOldCount[nCam]; i++)
		{
			if(pDoc->m_data.m_bSaveBmp){
				sprintf(buff, "%d_%d.bmp", 777, i%8);
			}
			else{
				sprintf(buff, "%d_%d.jpg", 777, i%8);
			}
			sprintf(fileName, "%s%s",path, buff);
			//str = path+tt;
			file_list[i] = new char[MAX_BADIMAGE_FILENAME];
			memset(file_list[i], 0, MAX_BADIMAGE_FILENAME);
			//strcpy(file_list[i], str.LockBuffer());
			strcpy(file_list[i], fileName);
		}
		if(	pDoc->m_data.m_strComName == "GL608")
		{//에지 Data 전송
			if(pDoc->m_data.m_nInspDirection[nCam]%2 == 0)
			{
				if(pDoc->m_data.m_nBroadEdge[nCam] <=0)
					nbroadtmp = nbroadtmp;//int(pDoc->m_data.m_dScaleFactorX);
				else
					nbroadtmp = pDoc->m_data.m_nBroadEdge[nCam]*pDoc->m_data.m_dScaleFactorX[nCam];
			}
			else
			{
				if(pDoc->m_data.m_nBroadEdge[nCam] <=0)
					nbroadtmp = nbroadtmp;//int(pDoc->m_data.m_dCalibSttX);
				else
					nbroadtmp = float(((pDoc->m_data.m_nCameraWidth - pDoc->m_data.m_nBroadEdge[nCam]) *  pDoc->m_data.m_dScaleFactorX[nCam]) + pDoc->m_data.m_dCalibSttX[nCam]);//Camera Reverse
			}
		}

		//마킹서버 전송
		//if(pDoc->m_data.m_nMachine==1){ //RO필터 마킹서버 전송안함
		if(pDoc->m_data.m_useMarking == 0){

		}
		else{
			pDoc->m_data.fpDefectType[nCam][0] = DCLASS_GBR_PIMUL;
			
			for(int i=0; i<10; i++){
//				packet->MakeDataPacket(g_frame_num-1, m_nOldCount[nCam],nbroadtmp, pDoc->m_data.fpDefectType[nCam], pDoc->m_data.fpX[nCam], pDoc->m_data.fpY[nCam], pDoc->m_data.fpSizeX[nCam], pDoc->m_data.fpSizeY[nCam],file_list);// pDoc->m_data.m_cFilename);
				Wait(80);
				if(nCam==0){
					SendMessage(WM_SIMULATEMARK, (DWORD)packet, 100);
				}
				else{
					SendMessage(WM_SIMULATEMARK1, (DWORD)packet, 100);
				}
			}
			
		}
		//data 초기화 지금 필요한가?//chcho
		for(int i=0; i<m_nOldCount[nCam];i++)//검사 시작전 reset data에서 초기화함.
			pDoc->m_data.fpX[nCam][i]=pDoc->m_data.fpY[nCam][i]=pDoc->m_data.fpSizeX[nCam][i]= pDoc->m_data.fpSizeY[nCam][i]=0;
		memset(pDoc->m_data.m_cFilename[nCam],0,MAX_BADIMAGE_FILENAME*MAX_REALDEFECT);
		for(int i=0; i<m_nOldCount[nCam]; i++)
		{
			if(file_list[i])
			{
				delete [] file_list[i];
				file_list[i] = NULL;
			}
		}
		if(m_nOldCount[nCam] ==0);
		else
		{
			if(file_list)
				delete [] file_list ;
		}
		delete packet;
	}	
	m_nOldCount[nCam] = 0;
}

//error.1
void CVisWebView::UpdateStatistics(BOOL bResult, double dInsTime,int nCam)
{
	if(((CVisWebApp*)AfxGetApp())->m_debugLogWrite == TRUE){
		((CVisWebApp*)AfxGetApp())->WriteLog(PATH_DEBUG_LOG, "debug_log", "UpdateStatistics");
	}
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	if(bResult){	//양품
		m_labelResult.SetTextColor(COLOR_GREEN);
		m_labelResult.SetBkColor(COLOR_BLACK);
		m_labelResult.SetText("GOOD");
	}
	else{	//NG
		pDoc->m_nTotalBad[nCam]++;
		m_labelResult.SetTextColor(COLOR_YELLOW);
		m_labelResult.SetBkColor(COLOR_RED);
		m_nResultOkNg = 1;
		m_labelResult.SetText("NG");
// 		if(nCam == 1){	
// 			m_eSaveImageCam2.SetEvent();
// 		}
// 		if(nCam == 2){	
// 			m_eSaveImageCam3.SetEvent();
// 		}
// 		else{
// 			m_eSaveImage.SetEvent();
// 		}
	}

	double dGoodYield = (double(pDoc->m_nTotalIns[0]-pDoc->m_nTotalBad[0])/pDoc->m_nTotalIns[0])*100;
	double dGoodYield1;// = (double(pDoc->m_nTotalIns[0]-pDoc->m_nTotalBad)/pDoc->m_nTotalIns[0])*100;
	if(pDoc->m_nTotalIns[0] == 0) dGoodYield = 100;
//	pDoc->m_pDlgGrid->UpdateGrid();

	if(MAX_CAMERAS>1 ){
		dGoodYield1 = (double(pDoc->m_nTotalIns[1]-pDoc->m_nTotalBad[1])/pDoc->m_nTotalIns[1])*100;
		if(pDoc->m_nTotalIns[1] == 0) dGoodYield1 = 100;
	}
	CTimingProcess* timer = ((CVisWebApp*)AfxGetApp())->m_pTiming;
	static double dInsTime1=0,dInsTime2=0;

	dInsTime1 = pDoc->m_data.m_dInspTime[0];//dInsTime;
	dInsTime2 = pDoc->m_data.m_dInspTime[1];//dInsTime;
	s_inspectTime = dInsTime;
	pDoc->m_data.m_dInspTime[nCam] =dInsTime;//+= dInsTime;
	CString stroldtime;

	CString str;
	if(MAX_CAMERAS>1)
		str.Format("\n 검사 갯수  : %07d - %07d\n\n 불량 갯수  : %06d - %06d\n\n 양 품 율   : %1.2f%% - %1.2f%%\n\n 검사 시간  : %2.3fms(%2.3fmsf)\n\n 초당프레임 : %.2fFps \n\n HDD 잔여량 : %2.2f%%,%2.2f%% ",
			pDoc->m_nTotalIns[0], pDoc->m_nTotalIns[1],/*g_frame_num,*/
			pDoc->m_nTotalBad[0], pDoc->m_nTotalBad[1],
			dGoodYield,dGoodYield1,
			dInsTime1,dInsTime2,
			m_fFps, 
			m_dRemainMainSpace,
			m_dRemainHDDSpace);
	else
		str.Format("\n 검사 갯수  : %07d - %06d\n\n 불량 갯수  : %07d\n\n 양 품 율   : %1.2f%%\n\n 검사 시간  : %2.3fms(%2.2f)\n\n 초당프레임 : %.2fFps \n\n HDD 잔여량 : %2.2f%%,%2.2f%% ",
		pDoc->m_nTotalIns, g_frame_num,
		pDoc->m_nTotalBad, 
		dGoodYield,
		dInsTime1,dInsTime2,
		m_fFps, 
		m_dRemainMainSpace,
		m_dRemainHDDSpace);

	m_labelStatistics.SetText(str);

	if(((CVisWebApp*)AfxGetApp())->m_debugLogWrite == TRUE){
		((CVisWebApp*)AfxGetApp())->WriteLog(PATH_DEBUG_LOG, "debug_log", "UpdateStatistics-end");
	}

}

LRESULT CVisWebView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	CString str1,str2;
	CTime ttime = CTime::GetCurrentTime();
	CString kk = ttime.Format("%Y_%m_%d");
	CString strTime = ttime.Format("[%Y %m %d %H:%M:%S]");
	str2.Format("c:\\Glim\\Log\\%s_Packet\\",kk);
	str1.Format("%s - %d",strTime,message);
	if(message == WM_UPDATEDLG){
		CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
		pDoc->m_pDlgInterface->UpdateData(FALSE);
	}
	if(message == WM_XDATARRECIEVED)
	{
		Decoding((int)wParam,(unsigned char*)lParam);
	}
	if(message == WM_RECEIVE)
	{
//		WriteLog(str2,"PacketDat",str1);
	}
	if(message == WM_ACCEPT)
	{		
//		"통신 상태 메인유아이에 표시"
//		CString ip_addr;
//		UINT	port;

	}
	if(message == WM_DISCONNECTED)
	{
//		WriteLog(str2,"PacketDat",str1);

	}
	if(message == WM_SENDDONE)
	{	
		//WriteLog(str2,"PacketDat",str1);

	}
	if(message == WM_SIMULATE)
	{
		CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

		if(lParam == 100)	//			
			pDoc->m_SendtoMarkingSock.SendInsData((CPacket*)wParam);
		else
			pDoc->m_SendtoServerSock.SendInsData((CPacket*)wParam);
		
//		WriteLog(str2,"PacketDat",str1);

	}
	if(message == WM_SIMULATE1)
	{
		CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

		if(lParam == 100)	//			
			pDoc->m_SendtoMarkingSock1.SendInsData((CPacket*)wParam);
		else
			pDoc->m_SendtoServerSock1.SendInsData((CPacket*)wParam);
//		WriteLog(str2,"PacketDat",str1);

	}
	if(message == WM_SIMULATEMARK)
	{
		CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
		//		if(lParam == 100)	//			
		CString logFileName = "MarkingSend";
		CString logStr;
		pDoc->m_SendtoMarkingSock.SendInsData((CPacket*)wParam);
		logStr.Format("Frame:%d, Tick_cnt:%d,", g_frame_num, (int)GetTickCount());
		//WriteLog("C:\\Glim\\Log\\",logFileName, logStr);
//		WriteLog(str2,"PacketDat",str1);

	}
	if(message == WM_SIMULATEMARK1)
	{
		CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
		
//		if(lParam == 100)	//			
		pDoc->m_SendtoMarkingSock1.SendInsData((CPacket*)wParam);
//		WriteLog(str2,"PacketDat",str1);

	}
	if(message == WM_SHUTTER)
	{
		PreStep();	//WriteLog(str2,"PacketDat",str1);

	}
	if(message == WM_RESTART)
	{
		CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
//		WriteLog(str2,"PacketDat",str1);

// 		if(pDoc->m_data.GetVisionLine(0) == GL9 ||pDoc->m_data.GetVisionLine(0) == GL8 || pDoc->m_data.GetVisionLine(0) == GL2)
// 		{
// 		}
// 		else
// 		{
// 			m_bAuto = FALSE;
// 			capture();
// 			fnDispButton(0);	//Write Reset Data//200805 - 13
// 			Wait(1);
// 			pDoc->m_pVision->HookStop(1);
// 
// 			fnWriteReceive(0.0 ,"ReOpen Start");
// 			OnButtonFrameReset();
// 			Wait(300);
// 			pDoc->m_pVision->Close();
// 			Wait(2000);
// 			pDoc->m_pVision->Open(m_ctrlDisplay.m_hWnd,0,pDoc->m_data.m_nCameraWidth,pDoc->m_data.m_nCameraHeight);
// 			Wait(500);
// 			PreStep();
// 
// 			pDoc->m_pVision->SetExposureTime(m_nExpose*25,1);
// 			Wait(10);
// 			m_nResetSystem = 1;
// 			AutoStart();
// 		}
	}
	if(message == WM_CAMYPOS)
	{
		fnChangeLine(0);
		UpdateData(FALSE);
//		WriteLog(str2,"PacketDat",str1);

	}

	//WM_CAMYPOS
	return CFormView::WindowProc(message, wParam, lParam);
}


void CVisWebView::Decoding(int nPort, unsigned char* pData)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	CString ip_addr;
//	UINT	port;
	

	//-------------------------------------------------------------
	//1.  수신 데이터를 문자열로 받는 경우. 
//	CString str;
//	str.Format("%s", (LPCSTR)data->m_Stream);
//	AfxMessageBox(str);
	//-------------------------------------------------------------
	//2.  수신 데이터를 포맷화된 패킷으로 디코딩. 

	CPacket packet;
	int		frame_num=0;
	int		defect_cnt=0;
	DEFECT	*defect=NULL;
	LPSTR	param_name = NULL;
	double	val = -1;
	LPSTR	str_val = NULL;
	int nCheck=0;

	int code = packet.GetCode((char*)pData+4,4);
	int nDataLen;
	memcpy(&nDataLen,pData,4);
//	pDoc->m_pVision->m_pLogProcess->WriteLog("Decode\t%d", nCode);
	CString str1,str2;
	CTime ttime = CTime::GetCurrentTime();
	CString kk = ttime.Format("%Y_%m_%d");
	CString strTime = ttime.Format("[%Y %m %d %H:%M:%S]");
	str2.Format("c:\\Glim\\Log\\%s_Packet\\",kk);
	str1.Format("%s - %d",strTime,code);
	WriteLog(str2,"PacketDat",str1);

	switch(code){
	case NM_DATA:	//서버에서 검사 데이터를 보내는 경우. 테스트 상황이므로 주석 처리
		{
			break;
		}
	case NM_PARAM_INSTANT:
		{
//			packet.PullInstantPacket(pData,nDataLen,nCode,param_name,val,str_val);
//			ParamInstantRead(nCode, param_name, val, str_val);
			break;
		}
	case NM_CALIB_START:
		{
			//splice signal
			break;
		}
	case NM_CALIB_RESULT:
		{
			break;
		}
	case NM_ON_SAVE:
		{
//			m_bImageSave = TRUE;//!m_bImageSave;
			m_bImageSaveAll = TRUE;
			pDoc->m_data.m_bLineWrite = m_bImageSaveAll;
			UpdateData(false);
			break;
		}
	case NM_NOT_SAVE:
		{
//			m_bImageSave = FALSE;//!m_bImageSave;
			m_bImageSaveAll = FALSE;
			pDoc->m_data.m_bLineWrite = m_bImageSaveAll;
			UpdateData(false);
			break;
		}
	case NM_IMAGE_DELETE:
		{
			m_bImageDelete = true;
			UpdateData(false);
			break;
		}
	case NM_INS_PRESET:
		{
			PreStep();
			break;
		}
	case NM_LOTDATA_CLEAR:
		{
			Delete_All_in_Folder("c:\\Glim\\LotData");
			break;
		}
	case NM_INS_START:
		{
			m_nCheckNewLot = 1;
			AutoStart();
			break;
		}
	case NM_INS_STOP:
		{
			AutoStop();
			OnButtonFrameReset();
			break;
		}
	case NM_EXIT_PGM:
		{
			if(defect)
				delete [] defect;
			PostQuitMessage(-1);
			break;
		}
	case NM_REBOOTING:
		{
			if(IsOsNT())	// Windows NT/2000/XP
				ShutDownNT(true);
			else			// Windows 98/ME
				ShutDownSystem(true);
		}
		break;

	case NM_SHUTDOWN:
		{
			if(IsOsNT())	// Windows NT/2000/XP
				WinNTSystemPowerOff(0, false);//ShutDownNT(false);
			else			// Windows 98/ME
				ShutDownSystem(false);
		}
		break;

	case NM_RESET:
		{
			OnButtonFrameReset();
		}
		break;

	case NM_REQ_HDD_REMAINING:
		{

		}
		break;

	case NM_CLIENT_SIMULATION_MODE:
		{

		}
		break;
	case NM_HISTO_EQUA:
		{
			pDoc->SaveHistoEquaData();
		}
		break;
	case NM_SPLICE:	//Tape 검지	080811
		{
			if(pDoc->m_data.m_dCamDist != 0)
			{
				m_nCkTape = 1;
				fnWriteSlice(g_frame_num,0,0);
			}
		}
		break;
	case MN_DATA_LOT_NAME:	//서버에서 lot name 보내주는 데이터
		{


		}
		break;
	case MN_DATA_LOT_NAME2:	//서버에서 lot name 보내주는 데이터 (3동만 적용)
		{
			
		}
		break;
	case MN_DATA_NEB:	//401에서 BROADCASTING
		{
		}
		break;
	case NM_ACK_MODEL:	//Start Cross
		{
			if(pDoc->m_data.m_nVisionLine == GL1||pDoc->m_data.m_nVisionLine == GL9)
			{
				AutoStart();
			}
		}
		break;
	case NM_ACK_LOT_NUMBER:	//Stop Cross
		{	
			if(pDoc->m_data.m_nVisionLine == GL1||pDoc->m_data.m_nVisionLine == GL9)
			{
				AutoStop();
				Wait(50);
				OnButtonFrameReset();
				pDoc->m_pDlgInterface->LoadInsParam();
				pDoc->m_pDlgInterface->	LoadLightParam();

			}
		}
		break;
/*	case NM_CROSS_POL_MOVE:	//Cross Pol Moving
		{	
			if(pDoc->m_data.m_nVisionLine == NEL1||pDoc->m_data.m_nVisionLine == NEL9)
			{
				//검사 안함.
				packet.PullInstantPacket((char*)pData,nDataLen,code,param_name,val,str_val);
				m_nCrossPolOffset = val;
				m_nCrossPolFrame = g_frame_num + m_nCrossPolOffset;
				fnWriteReceive(val,"0");
			}
		}
		break;*/
	case NM_ACK_KBH:	//병훈이 Ack. 서버에서 시작 신호
		{
//			pDoc->m_SendtoServerSock.SendCommand_LocalHost(NM_ACK_KBH);
			if(pDoc->m_data.m_nVisionLine==GL9)
			{
				//for (int i=0;i<MAX_CAMERAS;i++){
				//	if(pDoc->m_pVision1[i] !=NULL)
				//	{

				//		//					int n = pDoc->m_pVision1[i]->CamStatus();
				//		if(i==0)
				//			pDoc->m_SendtoServerSock.SendCommand_LocalHost(NM_ACK_KBH);//,1);
				//		else
				//			pDoc->m_SendtoServerSock1.SendCommand_LocalHost(NM_ACK_KBH);//,-1);
				//	}
				//	else
				//	{
				//		if(i==0)
				//			pDoc->m_SendtoServerSock.SendCommand_LocalHost(NM_ACK_KBH);//,-1);
				//		else
				//			pDoc->m_SendtoServerSock1.SendCommand_LocalHost(NM_ACK_KBH);//,-1);
				//	}

				//	Wait(5);
				//}

			}
			else{
				pDoc->m_SendtoServerSock.SendCommand_LocalHost(NM_ACK_KBH);
				pDoc->m_SendtoServerSock1.SendCommand_LocalHost(NM_ACK_KBH);
			}
			
			SetWarning("Net Send 49");


		}
		break;
	case NM_DATA_FRAME:	//Server->Frame수 Receive
		{
			packet.PullInstantPacket((char*)pData,nDataLen,code,param_name,val,str_val);
			CString strFRMData(param_name);
			fnLGCheckFrame(param_name,0);
//			pDoc->m_data.m_tTimeCheckFrameOld[0] = pDoc->m_data.m_tTimeCheckFrame[0];
			//			pDoc->m_data.m_nTimeCheckFrame = pDoc->m_data.m_nTimeCheckFrameOld;


		}
		break;
	case GM_NOT_INSP:	//설비 미검사 Signal
		{
			pDoc->m_data.m_bInspStart = FALSE;

		}
		break;
	case GM_USE_INSP:	//설비 검사 Signal
		{
			pDoc->m_data.m_bInspStart = TRUE;
		}
		break;
	case 72:	//Light On Off
		{
			packet.PullInstantPacket((char*)pData,nDataLen,code,param_name,val,str_val);
//			if(m_strComputerName.Right(2)!="01")
//				break;

			int nmax = 1;
			if(m_strComputerName.Right(3)=="401")
				nmax = 3;

//			for(int i=0;i<nmax;i++)if(m_LightCtrl[i].m_bConnected == false && m_strComputerName.Right(3)=="401")
//				return;
			if(val==0)//off
			{
				LightOFFWAVE1CH(0);
				LightOFFWAVE1CH(1);
			}
			else if(val==1){
				LightONWAVE1CH(0);
				LightONWAVE1CH(1);

			}
		}
		break;
	default:
		break;
	}
	if(defect)
		delete [] defect;
	//
}

int CVisWebView::fnCheckFrame(CString strpacket,int nCam)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	int nTemp = int((pDoc->m_data.m_dOpticsDistanceY[nCam]-1) + (pDoc->m_data.m_dOpticsDistanceY[nCam]/2));
	if(strpacket.Left(1) == "F")
	{
		if(atoi(strpacket.Mid(2,6)) > pDoc->m_nTotalIns[nCam]  && m_nResetSystem == -1)	//0805 - 15 Frame이 늦을 경우
		{
			//pDoc->m_data.m_dOpticsDistanceY-1
			m_nResetSystem = 1;	
			AutoStop();
//			fnWriteReceive(0.0 ,strpacket);
			Wait(1);
			OnButtonFrameReset();
			return 1;
		}
		else if(atoi(strpacket.Mid(2,6)) > pDoc->m_nTotalIns[nCam]  && m_nResetSystem == 1){
			m_nResetCount++;
		}
		else if(pDoc->m_nTotalIns[nCam] - nTemp >atoi(strpacket.Mid(2,6)))				//0805 - 15 Frame이 빠를경우.
		{
			m_nResetSystem = 1;	
			AutoStop();
//			fnWriteReceive(0.0 ,strpacket);
			Wait(1);
			OnButtonFrameReset();
			return 1;
		}
		
		if(m_nResetSystem == 1 && m_nResetCount == 5){
			//m_log2.AddString("체크프레임");
			m_nResetSystem =-1;
			/*CString str;
			str.Format("%d", g_frame_num);
			WriteLog("c:\\glim\\log", "frame_debug", str);
			WriteLog("c:\\glim\\log", "frame_debug", "frame2");*/
			g_frame_num = atoi(strpacket.Mid(2,6))+1;
			/*str.Format("%d", g_frame_num);
			WriteLog("c:\\glim\\log", "frame_debug", str);*/
			AutoStart();
			m_nResetCount =0;
			return 0;
		}

		if(m_nResetSystem == -1 )		return 0;
	}

	return 1;
}

void CVisWebView::fnPushPacket(CString strpacket,double dval,int nCam)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	int i;
	for(i=0;i<PD_FRAME*PD_LEN;i++){
		if(pDoc->m_data.m_pPacketData[nCam][i].Left(1) == "0")
		{
			pDoc->m_data.m_pPacketData[nCam][i].Format("%s_D_%.2f",strpacket,dval);
//			fnWritePacket(dval,strpacket,pDoc->m_data.m_pPacketData[i]);
			break;
		}
	}
}

void CVisWebView::ParamInstantRead(int nCode, LPSTR param_name, double val, LPSTR str_val)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
		
	if(!strcmp(param_name, PARAM_NAME_UPDATE) )
	{
		pDoc->m_str_ini_path = str_val;
//		pDoc->m_pDlgInterface->LoadSysParam();
//		pDoc->m_pDlgInterface->LoadGradeParam();	//Grade
		pDoc->m_pDlgInterface->LoadInsParam();
		pDoc->m_pDlgInterface->LoadSysParam();
		pDoc->m_pDlgInterface->	LoadLightParam();

		pDoc->m_pDlgInterface->ExposureChange();		
		pDoc->m_pDlgInterface->UpdateData(false);

	}
	else if(!strcmp(param_name, PARAM_NAME_SHUTTER_CONTROL))
	{
//		pDoc->m_pDlgInterface->m_dExposureTime_inNano = (long)(val);
//		pDoc->m_pDlgInterface->ExposureChange();		

		Calib_Brightness(long(val));
	}
	else if(!strcmp(param_name, PARAM_NAME_ALGORITHM_SELECT))
	{
		CString str;
		str.Format("%s", param_name);
//		AfxMessageBox(str);

	}
	else if(!strcmp(param_name, PARAM_NAME_MODEL))
	{
		pDoc->m_str_model = str_val;
	}
	else if(!strcmp(param_name, PARAM_NAME_LOT_NUMBER))
	{
//		pDoc->m_str_lot = str_val;
	}
	else if(!strcmp(param_name, PARAM_NAME_CAL_X))
	{
	}
	
	else if(!strcmp(param_name, PARAM_NAME_CAL_Y))
	{
	}	
	else if(!strcmp(param_name, PARAM_NAME_CAL_FRAME))
	{
	}	
	else if(!strcmp(param_name, PARAM_NAME_FRAME_LENGTH))
	{
	}	
	else if(!strcmp(param_name, PARAM_NAME_SFY))
	{
	}	
	else if(!strcmp(param_name, PARAM_NAME_SFX))
	{
	}
	else if(!strcmp(param_name, PARAM_CLIENT_MODE))
	{

		if(val == 0.0)
			m_bViewImage = true;
		else
			m_bViewImage = false;
		UpdateData(false);
	}
	else if(!strcmp(param_name, PARAM_NAME_SLY_WAKE_UP))
	{

	}
}


int g_defect_class=0;
int CVisWebView::BroadCasting(int bInspectResult,int nCam)
{

	return 0;
}
//700 25 = x = 100 = 


void CVisWebView::OnButtonFrameReset() 
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	
	{
		g_frame_num = m_nMilGrabCount = m_nMilCopyCount =  -3;
		for(int i=0;i<5;i++)
			pDoc->m_data.m_nCommutyFrameCount[0][i] = 0;

	}
	int nCam = 0;
	m_nThCount[nCam] = 0;
	CString sstr;

	sstr.Format("%d", g_frame_num);
	//m_log2.AddString(sstr);
	GetDlgItem(IDC_STATIC_FRAME_NUM)->SetWindowText(sstr);

	for(int i=0;i<MAX_CAMERAS;i++){
		pDoc->m_nTotalIns[i]=0;
		pDoc->m_nTotalBad[i]=0;
	}
	m_nStopFrame = -10;
	m_nReStartFrame = -10;
	m_nCheckCycle = 0;
	nRegCheck = 0;
	pDoc->m_data.m_nLineValueCheck = 0;
	
	int i,n;
	for( i=0; i<CYCLELENGTH;i++)// 10000;i++)
	{
		pDoc->m_data.m_dCycleY[nCam][i] = 0;
		pDoc->m_data.m_dCycleX[nCam][i] = 0;
	}
	for( n=0;n<MAX_CYCLE_COUNT;n++)
			pDoc->m_data.m_nDefectFlag[nCam][n] = 1; 

	for(i=0;i<10;i++)	pDoc->m_data.m_dCamYpos[nCam][i]=0;
	UpdateStatistics(true,0.0,nCam);
	pDoc->m_data.m_dOldInspTime[nCam] = 0.;

	Wait(1);
}
void CVisWebView::ResetFrame(int nCam)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	if(nCam==0){
		m_nStopFrame = -10;
		m_nReStartFrame = -10;
		m_nCheckCycle = 0;
		nRegCheck = 0;
		pDoc->m_data.m_nLineValueCheck = 0;
		g_frame_num = m_nMilGrabCount = m_nMilCopyCount =  -3;
	}
	m_nThCount[nCam] = 0;
//	CString sstr;
//	sstr.Format("%d", g_frame_num);
//	GetDlgItem(IDC_STATIC_FRAME_NUM)->SetWindowText(sstr);

	for(int j=0;j<10;j++)
		for(int i=0;i<20;i++)
			pDoc->m_data.m_dLineAverageData1[nCam][j][i]=0;

	pDoc->m_nTotalIns[nCam]=0;
	pDoc->m_nTotalBad[nCam]=0;

	UpdateStatistics(true,0.0,nCam);
	pDoc->m_data.m_dOldInspTime[nCam] = 0.;

	Wait(1);
}

BOOL CVisWebView::CheckChangeLotID(CString lotID) 
{
	BOOL bChgLotID = FALSE;
	
	if(m_strLotID.GetLength() < 1){
		m_strLotID = lotID;
	}

	//m_strLotID.Format("%s", "DASBL150");
	int nRetMatch = lotID.Compare(m_strLotID) ;

	if(m_strLotID.GetLength() >= 1 && nRetMatch != 0){
		m_dLotChangeIntervalEnd = GetPrecisionTime();
		if((m_dLotChangeIntervalEnd-m_dLotChangeIntervalStart)*1000 > 10000){
			m_strLotID = lotID;
			bChgLotID = TRUE;
			m_dLotChangeIntervalStart = m_dLotChangeIntervalEnd;
		}
	}
	return bChgLotID;
}

// return 0:A, 1:B, 2:Both On 3:Both Stop
int CVisWebView::CheckOnRwAB(int nRwRollA, int nRwRollB) 
{
	int nRet = 4;

	int nRollDiffA = abs(m_nRwRollA - nRwRollA);
	int nRollDiffB = abs(m_nRwRollB - nRwRollB);

	if(nRollDiffA > 1){
		m_nRwRollIncA++;
	}
	if(nRollDiffB > 1){
		m_nRwRollIncB++;
	}

	if(m_nRwChkCntTemp >= m_nRwChkCnt){
		if(m_nRwRollIncA >= 2 && m_nRwRollIncB == 0){
			nRet = 0;	//A On State
			m_nRwRollA = nRwRollA;
			m_nRwRollIncA = 0;
		}
		else if(m_nRwRollIncA == 0 && m_nRwRollIncB >= 2){
			nRet = 1;	//B On State
			m_nRwRollB = nRwRollB;
			m_nRwRollIncB = 0;
		}
		//else if(bOnRollA == TRUE && bOnRollB == TRUE){
		else if(m_nRwRollIncA >= 2 && m_nRwRollIncB >= 2){
			nRet = 2;	//Both On
			m_nRwRollA = nRwRollA;
			m_nRwRollB = nRwRollB;
			m_nRwRollIncA = 0;
			m_nRwRollIncB = 0;
		}
		else if(m_nRwRollIncA == 0 && m_nRwRollIncB == 0){
			nRet = 3;	//Both Stop
			m_nRwRollA = nRwRollA;
			m_nRwRollB = nRwRollB;
			m_nRwRollIncA = 0;
			m_nRwRollIncB = 0;
		}
		m_nRwChkCntTemp = 0;
	}
	else{

	}

	//if(m_nRwChkCntTemp >= m_nRwChkCnt){
	//	//if(bOnRollA == TRUE && bOnRollB == FALSE){
	//	if(m_nRwRollIncA >= 2 && m_nRwRollIncB == 0){
	//		nRet = 0;	//A On State
	//		m_nRwRollA = nRwRollA;
	//		m_nRwRollB = 0;
	//		m_nRwRollIncA = 0;
	//	}
	//	//else if(bOnRollA == FALSE && bOnRollB == TRUE){
	//	else if(m_nRwRollIncA == 0 && m_nRwRollIncB >= 2){
	//		nRet = 1;	//B On State
	//		m_nRwRollB = nRwRollB;
	//		m_nRwRollA = 0;
	//		m_nRwRollIncB = 0;
	//	}
	//	//else if(bOnRollA == TRUE && bOnRollB == TRUE){
	//	else if(m_nRwRollIncA >= 2 && m_nRwRollIncB >= 2){
	//		nRet = 2;	//Both On
	//		m_nRwRollA = nRwRollA;
	//		m_nRwRollB = nRwRollB;
	//		m_nRwRollIncA = 0;
	//		m_nRwRollIncB = 0;
	//	}
	//	else if(m_nRwRollIncA == 0 && m_nRwRollIncB == 0){
	//		nRet = 3;	//Both Stop
	//		m_nRwRollA = nRwRollA;
	//		m_nRwRollB = nRwRollB;
	//		m_nRwRollIncA = 0;
	//		m_nRwRollIncB = 0;
	//	}
	//	m_nRwChkCntTemp = 0;
	//}
	//else{

	//}

	//if(nRwRollA == 0 && nRwRollB == 0){
	//	m_nRwRollA = 0;
	//	m_nRwRollB = 0;
	//	m_nRwRollIncA = 0;
	//	m_nRwRollIncB = 0;
	//}
	
	m_nRwChkCntTemp++;

	return nRet;
}

//void CVisWebView::OnTimer(UINT nIDEvent) 
void CVisWebView::OnTimer(UINT_PTR nIDEvent) 
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	if(nIDEvent==1267){
		KillTimer(1267);
		pDoc->m_pDlgInterface->LoadSysParam();
		pDoc->m_pDlgInterface->LoadInsParam();
		pDoc->m_pDlgInterface->	LoadLightParam();

		AddtoList("Param Reload",0);
		capture1(m_strLotID,pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck]);
	}
	if(nIDEvent==23689){
		KillTimer(23689);
		WriteLotModel(m_strLotID);
	}
// 	if(nIDEvent == 14123){//lot change 시 작업
// 		KillTimer(14123);
// 		//copy file//
// 		CopyHeaderFile();
// 		CopyMisFile();
// 		CopyImageFile();
// 	}
	if(nIDEvent== 200611){//Alive
		CFileFind finder;
		BOOL IsFind;
		CString filename,filename1, strLine;
		int nStatus = 0;
		bool bInspect = false;	// 검사가능상태여부

	
		//ochct01cht1
		if(m_strComputerName.Mid(8,1)=="H"){
			if(m_strComputerName.Mid(9,1)=="T")
				filename.Format("d:\\Data\\Alive\\1");
			else if(m_strComputerName.Mid(9,1)=="B")
				filename.Format("d:\\Data\\Alive\\3");
		}
		else if(m_strComputerName.Mid(8,1)=="M"){
			if(m_strComputerName.Mid(9,1)=="T")
				filename.Format("d:\\Data\\Alive\\6");
			else if(m_strComputerName.Mid(9,1)=="B")
				filename.Format("d:\\Data\\Alive\\7");
		}

		
		nStatus = GetPGMStatus();
		bInspect = m_bAuto;
		strLine.Format(_T("%d,%d,%s"), (bInspect)?1:0, nStatus,pDoc->m_data.m_strDefaultModel);//cis);			// 검사가능상태여부, 검사기 상태, 모델명

		IsFind = finder.FindFile(filename+_T(".txt"));
		if(IsFind){
			CStdioFile fileServer;
			if(fileServer.Open(filename+_T(".txt"), CFile::modeRead|CFile::typeText)){
				fileServer.ReadString(m_strServerModel);
				fileServer.Close();
			}
			filename1.Format("%s-1.txt",filename);
			CStdioFile   file;
			if(file.Open(filename1, CFile::modeCreate|CFile::modeWrite|CFile::typeText)){
				file.WriteString(strLine);
				file.Close();
				DeleteFile(filename);	
			}
		}
	}
	if(nIDEvent == 14223){//foil size 알람
		if(m_nFoilCount%2==0){
			m_lbFullWidth.SetTextColor(COLOR_RED);
			m_lbFullWidth.SetBkColor(COLOR_WHITE);

		}
		else{
			m_lbFullWidth.SetTextColor(COLOR_YELLOW);
			m_lbFullWidth.SetBkColor(COLOR_BLACK);
		}
		m_strAlarmMsg = "Foil Width";
		if(m_nFoilCount%2==0)
			m_IO[0].WriteOutputPort(0,0,TRUE);
		else
			m_IO[0].WriteOutputPort(0,0,FALSE);

		//		m_AlarmDlg->AlarmOn(m_nAlarmCnt%2,m_strAlarmMsg);
		m_AlarmDlg->AlarmOn1(m_nFoilCount%2,m_strAlarmMsg,m_strAlarmMsg1);
		m_AlarmDlg->ShowWindow(1);
		m_nFoilCount++;
	}
	if(nIDEvent==25151){
		KillTimer(25151);		m_bUseLen[0] = TRUE;m_nUsecheck[0]=-1;
	}
	else if(nIDEvent==25152){KillTimer(25152);	
	m_bUseLen[1] = TRUE;m_nUsecheck[1]=-1;	}
	else if(nIDEvent==25153){KillTimer(25153);		
	m_bUseLen[2] = TRUE;m_nUsecheck[2]=-1;	}
	else if(nIDEvent==25154){KillTimer(25154);	
	m_bUseLen[3] = TRUE;m_nUsecheck[3]=-1;	}
	else if(nIDEvent==25155){KillTimer(25155);	
	m_bUseLen[4] = TRUE;m_nUsecheck[4]=-1;	}
	else if(nIDEvent==25156){KillTimer(25156);	
	m_bUseLen[5] = TRUE;m_nUsecheck[5]=-1;	}
	else if(nIDEvent==25157){KillTimer(25157);	
	m_bUseLen[6] = TRUE;m_nUsecheck[6]=-1;	}
	else if(nIDEvent==25158){KillTimer(25158);	
	m_bUseLen[7] = TRUE;m_nUsecheck[7]=-1;	}
	else if(nIDEvent==25159){KillTimer(25159);	
	m_bUseLen[8] = TRUE;m_nUsecheck[8]=-1;	}

	if(nIDEvent == 20145){
		KillTimer(20145);

		m_eSaveImageCam2.SetEvent();m_eSaveImageCam3.SetEvent();m_eSaveImage.SetEvent();

		OnCheckAuto();
		Wait(1000);
		OnCheckAuto();
		//data Write
		
	}
	if(nIDEvent == 20136){
		KillTimer(20136);
		//data Write
		m_DlgLastData->ShowWindow(1);
	}
	if(nIDEvent == 20134){
		//capture
		KillTimer(20134);
		capture1(m_strLotID,pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck]);
	}
	if(nIDEvent == 20013){
		int n1 = m_nPlcData[0]*0.1;
		int n2 = m_nPlcData[1]*0.1;


// 		if(m_nOldChuck[0] == n1 && m_nOldChuck[1] != n2)//meter
// 		{	pDoc->m_data.m_nUseChuck = 1;m_nLineRunning=1;
// 		}
// 		else if(m_nOldChuck[0] != n1 && m_nOldChuck[1] == n2)//meter
// 		{	pDoc->m_data.m_nUseChuck = 0;m_nLineRunning=1;
// 		}
// 		else m_nLineRunning = 0;
		if(m_nOldChuck[1] < n2)//meter
		{	
			if(pDoc->m_data.m_nUseChuck == 0){
				m_dChuckChangeIntervalEnd = GetPrecisionTime();
				if((m_dChuckChangeIntervalEnd - m_dChuckChangeIntervalStart)*1000 > 10000){
					pDoc->m_data.m_nUseChuck = 1;m_nLineRunning=1;
					m_dChuckChangeIntervalStart = m_dChuckChangeIntervalEnd;
				}
			}
			else
				pDoc->m_data.m_nUseChuck = 1;m_nLineRunning=1;
		}
		else if(m_nOldChuck[0] <n1 )//meter
		{
			if(pDoc->m_data.m_nUseChuck == 1){
				m_dChuckChangeIntervalEnd = GetPrecisionTime();
				if((m_dChuckChangeIntervalEnd - m_dChuckChangeIntervalStart)*1000 > 10000){
					pDoc->m_data.m_nUseChuck = 0;m_nLineRunning=1;
					m_dChuckChangeIntervalStart = m_dChuckChangeIntervalEnd;
				}
		}
		else
			pDoc->m_data.m_nUseChuck = 0;m_nLineRunning=1;
		}
		else m_nLineRunning = 0;

		if(m_nLineRunning==0){
// 			CString str1;
// 			str1.Format("Line Stop");
// 			m_lbFullWidth.SetText(str1);
// 			m_defectMap->m_lbMismatchTitle.SetText(str1);
		}
		
		m_nOldChuck[0] = n1;
		m_nOldChuck[1] = n2;
		if(pDoc->m_data.m_nCamID==5){
			ReadDefectCount(m_strLotID);//WriteShareMemory1
			WriteShareMemory1(5,2,pDoc->m_data.m_nSumBadCount[4]);
			WriteShareMemory1(5,3,pDoc->m_data.m_nSumBadCount[5]);
		}
	}
	if(nIDEvent == READ_SHARED_MEM){
//		KillTimer(READ_SHARED_MEM);
		m_strMemoryAddress[0] = "RW_A_ROLL";
		m_strMemoryAddress[1] = "RW_B_ROLL";
		m_strMemoryAddress[2] = "LINE_SPEED";
		m_strMemoryAddress[3] = "LOT_ID_1";
		m_strMemoryAddress[4] = "LOT_ID_2";
		m_strMemoryAddress[5] = "LOT_ID_3";
		m_strMemoryAddress[6] = "LOT_ID_4";
		m_strMemoryAddress[7] = "CUT_NO";
		m_strMemoryAddress[8] = "MODEL_PTN_TOP";
		m_strMemoryAddress[9] = "CT_ON_TOP";
		m_strMemoryAddress[10] = "MODEL_PTN_BACK";
		m_strMemoryAddress[11] = "CT_ON_BACK";
		m_strMemoryAddress[12] = "A_ROLL_CT_ON";
		m_strMemoryAddress[13] = "B_ROLL_CT_ON";
		m_strMemoryAddress[14] = "UW_A_ROLL";
		m_strMemoryAddress[15] = "UW_B_ROLL";
		m_bMemoryIsUse[0] = TRUE;
		m_bMemoryIsUse[1] = TRUE;
		m_bMemoryIsUse[2] = TRUE;
		m_bMemoryIsUse[3] = TRUE;
		m_bMemoryIsUse[4] = TRUE;
		m_bMemoryIsUse[5] = TRUE;
		m_bMemoryIsUse[6] = TRUE;
		m_bMemoryIsUse[7] = TRUE;
		m_bMemoryIsUse[8] = TRUE;
		m_bMemoryIsUse[9] = TRUE;
		m_bMemoryIsUse[10] = TRUE;
		m_bMemoryIsUse[11] = TRUE;
		m_bMemoryIsUse[12] = TRUE;
		m_bMemoryIsUse[13] = TRUE;
		m_bMemoryIsUse[14] = TRUE;
		m_bMemoryIsUse[15] = TRUE;

		BOOL bRet[20];
		for(int i=0; i<20; i++){
			bRet[i] = FALSE;
		}
		bRet[0] = m_sharedMemory[0].Open(m_strMemoryAddress[0], sizeof(int));
		bRet[1] = m_sharedMemory[1].Open(m_strMemoryAddress[1], sizeof(int));
		bRet[2] = m_sharedMemory[2].Open(m_strMemoryAddress[2], sizeof(int));
		bRet[3] = m_sharedMemory[3].Open(m_strMemoryAddress[3], sizeof(int));
		bRet[4] = m_sharedMemory[4].Open(m_strMemoryAddress[4], sizeof(int));
		bRet[5] = m_sharedMemory[5].Open(m_strMemoryAddress[5], sizeof(int));
		bRet[6] = m_sharedMemory[6].Open(m_strMemoryAddress[6], sizeof(int));
		bRet[7] = m_sharedMemory[7].Open(m_strMemoryAddress[7], sizeof(int));
		bRet[8] = m_sharedMemory[8].Open(m_strMemoryAddress[8], sizeof(int));
		bRet[9] = m_sharedMemory[9].Open(m_strMemoryAddress[9], sizeof(int));
		bRet[10] = m_sharedMemory[10].Open(m_strMemoryAddress[10], sizeof(int));
		bRet[11] = m_sharedMemory[11].Open(m_strMemoryAddress[11], sizeof(int));
		bRet[12] = m_sharedMemory[12].Open(m_strMemoryAddress[12], sizeof(int));
		bRet[13] = m_sharedMemory[13].Open(m_strMemoryAddress[13], sizeof(int));
		bRet[14] = m_sharedMemory[14].Open(m_strMemoryAddress[14], sizeof(int));
		bRet[15] = m_sharedMemory[15].Open(m_strMemoryAddress[15], sizeof(int));
		int* nValue[20];
		char* cValue[20];
		nValue[0] = (int*)m_sharedMemory[0].GetData();	//RW_A_ROLL
		nValue[1] = (int*)m_sharedMemory[1].GetData();	//RW_B_ROLL
		nValue[2] = (int*)m_sharedMemory[2].GetData();	//LINE_SPEED
		nValue[4] = (int*)m_sharedMemory[7].GetData();	//CUT_NO
		nValue[5] = (int*)m_sharedMemory[8].GetData();	//MODEL_PTN_TOP
		nValue[6] = (int*)m_sharedMemory[9].GetData();	//CT_ON_TOP
		nValue[7] = (int*)m_sharedMemory[10].GetData();	//MODEL_PTN_BACK
		nValue[8] = (int*)m_sharedMemory[11].GetData();	//CT_ON_BACK
		nValue[9] = (int*)m_sharedMemory[12].GetData();	//A_ROLL_CT_ON
		nValue[10] = (int*)m_sharedMemory[13].GetData();//B_ROLL_CT_ON
		nValue[11] = (int*)m_sharedMemory[14].GetData();//UW_A_ROLL
		nValue[12] = (int*)m_sharedMemory[15].GetData();//UW_B_ROLL

//		int				m_nPlcData[20];
//		CString			m_strPlcLot[2];

		int nold[2];
		int nRwRollA =nold[0] = (int)(*nValue[0]);
		int nRwRollB =nold[1] = (int)(*nValue[1]);

		m_nPlcData[0] = nRwRollA;
		m_nPlcData[1] = nRwRollB;
		float fRwRollA = (*nValue[0]) * 0.1;
		float fRwRollB = (*nValue[1]) * 0.1;
		float fLineSpeed =m_nPlcData[2] = (*nValue[2]) * 0.1;
		//int nCutNo =m_nPlcData[4] = (*nValue[4]);
		int nModelPtnTop =m_nPlcData[5] = (*nValue[5]);
		int nCtOnTop =m_nPlcData[6] = (*nValue[6]);
		int nModelPtnBack =m_nPlcData[7] = (*nValue[7]);
		int nCoatingOnBack =m_nPlcData[8] = (*nValue[8]);
		int nRollCoatingA =m_nPlcData[9] = (*nValue[9]);
		int nRollCoatingB =m_nPlcData[10] = (*nValue[10]);
		int nUwRollA =m_nPlcData[11] = (*nValue[11]);
		int nUwRollB =m_nPlcData[12] = (*nValue[12]);

		cValue[0] = (char*)m_sharedMemory[3].GetData();	//LOT_ID_1
		cValue[1] = (char*)m_sharedMemory[4].GetData();	//LOT_ID_2
		cValue[2] = (char*)m_sharedMemory[5].GetData();	//LOT_ID_3
		cValue[3]= (char*)m_sharedMemory[6].GetData();	//LOT_ID_4
		cValue[4]= (char*)m_sharedMemory[7].GetData();	//CUT_NO

		//m_nPlcData[19] = (*nValue[19]);

		int nRet = CheckOnRwAB(nRwRollA, nRwRollB);
	
		if(nRet == 0){
			//AddtoList("A Chuck Run", 0, TRUE);	
		}
		else if(nRet == 1){
			//AddtoList("B Chuck Run", 0, TRUE);	
		}
		else if(nRet == 2){
			//AddtoList("A,B Chuck Run", 0, TRUE);	
		}
		else if(nRet == 3){
			//AddtoList("A,B Chuck Stop", 0, TRUE);	
		}
		else{
			//AddtoList("UnKnown", 0, TRUE);
		}

		CString strSum1, strSum2, strSum3, strSum4, strSum5, strSum6, strSum7, strSum8, strSum9, strSum10, strSum11, strSum12;
		CString strLotID,strOldLot;;

		if(pDoc->m_pDlgInterface->m_bEngKor){			//ENG-KOR
			strSum1.Format("CORE_A : %0.1f ", fRwRollA);
			strSum2.Format("CORE_B : %0.1f ", fRwRollB);
		}
		else{
			strSum1.Format("제품위치_A : %0.1f ", fRwRollA);
			strSum2.Format("제품위치_B : %0.1f ", fRwRollB);	

		}
		strLotID.Format("%s%s%s%s%s", cValue[0], cValue[1], cValue[2], cValue[3], cValue[4]);
		if(m_bLotWriteCheck==FALSE)
			m_strPlcLot[0] = strLotID;
		strSum3.Format("LotNo.  %s", strLotID);
	
		//strSum4.Format("CutNo : %d", nCutNo);
		strSum5.Format("ModelPtnTop : %d", nModelPtnTop);
		strSum6.Format("CTOnTop : %d", nCtOnTop);
		strSum7.Format("ModelPtnBack : %d", nModelPtnBack);
		strSum8.Format("CTOnBack : %d", nCoatingOnBack);
		strSum9.Format("RollCoatingA : %d", nRollCoatingA);
		strSum10.Format("RollCoatingB : %d", nRollCoatingB);
		strSum11.Format("UW_A : %d", nUwRollA);
		strSum12.Format("UW_B : %d", nUwRollB);

		m_lbLotInfo.SetText(strSum3);
		m_lbWinder1.SetText(strSum1);
		m_lbWinder2.SetText(strSum2);

		//20201020 kjh
		if(m_strComputerName.Mid(9,1)=="T"){
			if(m_nCoatingOn == 1 && nCtOnTop == 0){
				m_nNonCoatStartMeter = pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck];
			}
			else{
				m_nNonCoatEndMeter = pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck];
			}
			m_nCoatingOn = nCtOnTop;
		}
		else{
			if(m_nCoatingOn == 1 && nCoatingOnBack == 0){
				m_nNonCoatStartMeter = pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck];
			}
			else{
				m_nNonCoatEndMeter = pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck];
			}
			m_nCoatingOn = nCoatingOnBack;
		}

		
		memset(cLotCurrent, NULL, sizeof(char)*100);
		//memset(cLotAfter, ' ', sizeof(char)*100);

		sprintf(cLotCurrent, "%s", m_strPlcLot[0]);
		//sprintf(cLotAfter, "%s", m_strPlcLot[1]);

		if(nRet >=0 && nRet <= 3){	
		}


		if(CheckChangeLotID(strLotID) == TRUE){		
			AddtoList("LotID Chg!!!!!!!!", 0, TRUE);
// 			KillTimer(READ_SHARED_MEM);
// 			Sleep(5000);													// 200831 LotChange 중복해서 되는 문제 수정
// 			SetTimer(READ_SHARED_MEM, 500, NULL);//plc read

			if(pDoc->m_pDlgInterface->m_bServerDataSend)
				WriteLotModel(strLotID);
			

			//param reload 모델 바뀔때 파람 리로드
			pDoc->m_pDlgInterface->LoadSysParam();
			pDoc->m_pDlgInterface->LoadInsParam();
			pDoc->m_pDlgInterface->	LoadLightParam();

			m_bCopyComplete = TRUE;
			m_nRestartSkipFrame = 0;
			m_strEndTime = m_strStartTime;
			CTime ttime = CTime::GetCurrentTime();
			CString strTime = ttime.Format("%Y-%m-%d-%H:%M:%S");
			m_strStartTime =strTime;
			m_dMeterY = pDoc->m_data.m_nMachineLengthAB[(pDoc->m_data.m_nUseChuck+1)%2];
			if(m_dMeterY == 0)
				m_dMeterY =  pDoc->m_data.m_nMachineLengthAB[(pDoc->m_data.m_nUseChuck)%2];
			m_bAlarmOff = FALSE;
			UpdateData(FALSE);
			m_nAlarmCnt = 0;
			m_nAlarmCnt1 = 0;
			m_strAlarmMsg = "";
			m_strAlarmMsg1 = "";
			m_AlarmDlg->ShowWindow(0);
			KillTimer(20219);//alarm 해제
		
			SetTimer(190319,100,NULL);//defect image reset

			//이전 Lot id를 넣어준다.
			m_strLotChangeID[m_nLotChangeCount%10] = m_strOldLot;
			m_strLotChangeTime[m_nLotChangeCount%10] = m_strOldTime;

			m_bLotChange[m_nLotChangeCount%10] = TRUE;//Thread에서 작업

			// write Last Data
			WriteLastData(m_strOldLot);		// 20201013 kjh 


// 			if(m_bLotchanging){// - 4에서 5로 갈때 2미터 이내의 생산 거리가 나온다
// 				for(int k1 = 0;k1<1000*20;k1++){
// 					Wait(5);					if(m_bLotchanging==FALSE)break;
// 				}
// 			}
// 			m_bLotchanging = TRUE;
			m_strOldLot1 = m_strOldLot;
			for(int ij=0;ij<5;ij++)
				pDoc->m_data.m_nLaneDefectCount[ij][0] = pDoc->m_data.m_nLaneDefectCount[ij][1] = 0; 

// 			if(m_strComputerName.Find("BACK")>=0 ||  pDoc->m_data.m_strComName.Mid(9,1)=="B")
// 				CopyDefectData(m_strOldLot1,m_strOldTime);//topdata copy
// 			//CSV 생성 //20190414
// 			if(m_strComputerName.Find("BACK")>=0 ||  (pDoc->m_data.m_strComName.Mid(9,1)=="B" && m_strComputerName.Mid(8,1)=="M")) //백에서만 LotInfo를 만든다.
// 				WriteLotInfo(m_strOldLot1,  m_strEndTime,m_strStartTime, m_dMeterY, pDoc->m_data.m_nBadTypeCount[5], pDoc->m_data.m_nBadTypeCount[1], pDoc->m_data.m_nBadTypeCount[4], pDoc->m_data.m_nBadTypeCount[2], pDoc->m_data.m_nBadTypeCount[0],pDoc->m_data.m_nBadTypeCount[3]);

			SetTimer(12011,2000,NULL);//invalidate
			m_nBrightcheck[0]=m_nBrightcheck[1]=m_nBrightcheck[2] = 0;
			m_nAlarmEndFRame = 0;
			m_bAlarmOnOff = FALSE;
			m_IO[0].WriteOutputPort(0,0,FALSE);//io off
//			AddtoList("LotChange Off",0,TRUE);

			for(int i=0;i<6;i++)
				pDoc->m_data.m_nSumBadCount[i] = 0;
			for(int i=0; i<10; i++)
				pDoc->m_data.m_nTmpBadTypeCount[i] = pDoc->m_data.m_nTmpBadTypeCount[i];	// 200702 kjh
// 			if(m_strComputerName.Mid(8,1)=="M" &&m_strComputerName.Mid(9,1)=="B")
// 				SetTimer(14123,100,NULL);//file move
// 			else
// 				m_bLotchanging = FALSE;
			if(pDoc->m_pDlgInterface->m_bAutoReset){//파라미터 reset 체크시 랏체인지시마다 검사기 중지 시작
				SetTimer(20145,200,NULL);
				AddtoList("Reset Data",0);
			}
			m_nLotChangeCount++;
			if(m_nLotChangeCount>=10)m_nLotChangeCount = 0;
			//조명 체크를 한다.
			m_bChangeLight = TRUE;
			m_nLastLineCount[0] = m_nLastLineCount[1] = 0;

			// 20201022 kjh 
			if(m_listMeterRatio.size()>0)
				m_listMeterRatio.clear();

		}		
		m_strOldLot = strOldLot = m_strLotID = strLotID;//	ConvertCharToStr(cLotID) = "None";
		m_nOldLotMeter = pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck];

		int nSig = 0;

		// Coating On signal		// 200818 kjh
// 		if(m_strComputerName.Mid(9,1) == "T"){
// 			nSig = (nValue[6]&(1<<6));
// 			m_bCoatingOnSignal = (nSig==0)?false:true;
// 		}
// 		else{
// 			nSig = (nValue[8]&(1<<6));
// 			m_bCoatingOnSignal = (nSig==0)?false:true;
// 		}

		m_sharedMemory[0].Close();
		m_sharedMemory[1].Close();
		m_sharedMemory[2].Close();
		m_sharedMemory[3].Close();
		m_sharedMemory[4].Close();
		m_sharedMemory[5].Close();
		m_sharedMemory[6].Close();
		m_sharedMemory[7].Close();
		m_sharedMemory[8].Close();
		m_sharedMemory[9].Close();
		m_sharedMemory[10].Close();
		m_sharedMemory[11].Close();
		m_sharedMemory[12].Close();
		m_sharedMemory[13].Close();
		m_sharedMemory[14].Close();
		m_sharedMemory[15].Close();
	}

	if(nIDEvent == 20216){
		//data Recieve //not use
		KillTimer(20216);
		CopyMismatchFile();
	}
	if(nIDEvent == 20219){//alarm message
//		m_AlarmDlg->AlarmOn(m_nAlarmCnt%2,m_strAlarmMsg);
		m_AlarmDlg->AlarmOn1(m_nAlarmCnt%2,m_strAlarmMsg,m_strAlarmMsg1);
		m_nAlarmCnt++;
	}
	if(nIDEvent == 20218){//NEW Alarm
		if(m_nAlarmCnt1%2==0)
			m_IO[0].WriteOutputPort(0,0,TRUE);
		else
			m_IO[0].WriteOutputPort(0,0,FALSE);

//		m_AlarmDlg->AlarmOn(m_nAlarmCnt%2,m_strAlarmMsg);
		m_AlarmDlg->AlarmOn1(m_nAlarmCnt%2,m_strAlarmMsg,m_strAlarmMsg1);
		m_nAlarmCnt1++;
	}
 	if(nIDEvent == 20213){
//  		if(pDoc->m_data.m_nSimmulationMode!=1)
//  			KillTimer(20213);
 		CTime time = CTime::GetCurrentTime();
 		CString kk = time.Format("%H");int ntime = atoi(kk);
 		pDoc->m_data.m_nUseChuck = ntime%2;
 		pDoc->m_data.m_nMachineLengthAB[ntime%2]++;
		m_strLotID.Format("TEST-%s",kk);
		pDoc->m_str_lot = m_strLotID;
 		if(pDoc->m_data.m_nOldChuck != pDoc->m_data.m_nUseChuck){
 			pDoc->m_data.m_nMachineLengthAB[ntime%2] = 0;
 			pDoc->m_data.m_nChuckChange=1;
 		}
 		CString str;
 		str.Format("CORE A:    %d M",pDoc->m_data.m_nMachineLengthAB[0] );//pDoc->m_data.m_nMachineLengthAB[ntime%2] 
 		m_lbWinder1.SetText(str);
 		str.Format("CORE B:    %d M",pDoc->m_data.m_nMachineLengthAB[1] );
 		m_lbWinder2.SetText(str);

		str.Format("Lot No  %s",m_strLotID );
		m_lbLotInfo.SetText(str);
		sprintf(cLotID, "%s", str);

 		pDoc->m_data.m_nOldChuck = pDoc->m_data.m_nUseChuck;//m_nUseChuck
 	}
	if(nIDEvent == 12011){
		//rectangle refresh
		KillTimer(12011);
		Invalidate();
	}

	if(nIDEvent==190319){
		KillTimer(190319);
		//Lot Change
	//	이미지 리셋
		for(int i=0;i<15;i++){
			memset(m_pDefectImage[i]->GetImagePtr(),0,BAD_IMG_HEIGHT*BAD_IMG_WIDTH);
			memset(m_charLbLotInfo[i], NULL, sizeof(char)*100);
			m_lbDefectInfo[i].SetText(m_charLbLotInfo[i]);
		}
	//	불량 ㅋ운트 리셋
		m_nMismatchBadCount = 0;
		for(int k1=0;k1<MAX_CAMERAS;k1++)
			pDoc->m_nTotalIns[k1]=0;

		for(int i=0;i<10;i++)m_nBadCountDefect[i] =pDoc->m_data.m_nBadTypeCount[i]= 0;
		CString str;
		UpdateControl();
// 		if(pDoc->m_pDlgInterface->m_bEngKor){									//ENG-KOR
// 			str.Format("DRAG LINE:   %dEA",pDoc->m_data.m_nBadTypeCount[0]);
// 			m_lbNullDrag.SetText(str);
// 			str.Format("N-COAT LINE:   %dEA",pDoc->m_data.m_nBadTypeCount[1]);
// 			m_lbNullLine.SetText(str);
// 			str.Format("ISLAND  :   %dEA",pDoc->m_data.m_nBadTypeCount[2]);
// 			m_lbNullIsland.SetText(str);
// 			str.Format("EDGE SPUR:   %dEA",pDoc->m_data.m_nBadTypeCount[3]);
// 			m_lbCoatDrag.SetText(str);
// 			str.Format("COAT LINE:   %dEA",pDoc->m_data.m_nBadTypeCount[4]);
// 			m_lbCoatLine.SetText(str);
// 			str.Format("PINHOLE:   %dEA",pDoc->m_data.m_nBadTypeCount[5]);
// 		}
// 		else{
// 			str.Format("드래그라인:   %dEA",pDoc->m_data.m_nBadTypeCount[0]);
// 			m_lbNullDrag.SetText(str);
// 			str.Format("무지  라인:   %dEA",pDoc->m_data.m_nBadTypeCount[1]);
// 			m_lbNullLine.SetText(str);
// 			str.Format("아일랜드  :   %dEA",pDoc->m_data.m_nBadTypeCount[2]);
// 			m_lbNullIsland.SetText(str);
// 			str.Format("코팅드래그:   %dEA",pDoc->m_data.m_nBadTypeCount[3]);
// 			m_lbCoatDrag.SetText(str);
// 			str.Format("코팅  라인:   %dEA",pDoc->m_data.m_nBadTypeCount[4]);
// 			m_lbCoatLine.SetText(str);
// 			str.Format("핀     홀:   %dEA",pDoc->m_data.m_nBadTypeCount[5]);
// 		}
		
//draw추가
		CRect rcMain;
		GetWindowRect(rcMain);
		CDC *pDC = GetDC();

		for(int n=0;n<15;n++){
			CRect rcDIB, rcDest;
			rcDIB.top = 0;
			rcDIB.left = 0;
			rcDIB.right = BAD_IMG_WIDTH;//pDoc->m_data.m_pImageDefect[0]->GetWidth();
			rcDIB.bottom = BAD_IMG_HEIGHT;//pDoc->m_data.m_pImageDefect[0]->GetHeight();
			int mm = n;
			if(mm>0)mm+=1;		
			GetDlgItem(IDC_STATIC_001+mm)->GetWindowRect(rcDest);
			rcDest.OffsetRect(-rcMain.left,-rcMain.top);
			m_pDefectImage[n]->Draw(pDC->m_hDC,&rcDIB,&rcDest);
		}
		ReleaseDC(pDC);
	}
	if(nIDEvent==1)
	{
		if((m_bAuto==FALSE && m_bRun==FALSE) || (m_bAuto<0 && m_bRun<0))		return ;

		// Auto model load
		CFile file;
		try{
			g_Mutex.Lock();                    // 뮤텍스를 잠근다.
			if(file.Open("c:\\Glim\\set\\abc.nxt", CFile::modeRead))
			{
				CArchive ar( &file, CArchive::load);
				pDoc->Serialize(ar);
				file.Close();
			}
			g_Mutex.Unlock();                    
		}
		catch(CFileException)
		{
			//AfxMessageBox( "File Open failed" );
		}
		catch(...)
		{
			//AfxMessageBox( "File Open failed2~" );
		}
		pDoc->m_pDlgGrid->UpdateGrid();
		Invalidate();
		KillTimer(1);
	}
	if(nIDEvent == TEVENT_LIGHT_CHECK)
	{
// 		if(pDoc->m_data.m_strComName.Right(2) == "01" || pDoc->m_data.m_strComName.Right(2) == "02")
// 		{
// 			if((m_bAuto==FALSE && m_bRun==FALSE) || (m_bAuto<0 && m_bRun<0))		return ;
// 			m_eLight.SetEvent();
// 		}
	}

	if(nIDEvent == TEVENT_HDD_SPACE)
	{
		//		CString str;
		long lTotal, lOccupied, lRemaining;
		long lTotal2=0, lOccupied2=0, lRemaining2=0;
		if((m_bAuto==FALSE && m_bRun==FALSE) || (m_bAuto<0 && m_bRun<0))		return ;
		GetHDDSpace("C:\\", &lTotal, &lOccupied, &lRemaining);
		GetHDDSpace("D:\\", &lTotal2, &lOccupied2, &lRemaining2);
		m_dRemainMainSpace = ((double)lRemaining / lTotal)*100;
		if(lTotal2<=1){
			m_dRemainHDDSpace = 0;
		}
		else
			m_dRemainHDDSpace = ((double)lRemaining2 / lTotal2)*100;	//D
		if(m_dRemainHDDSpace < HDD_PERCENTAGE_LIMIT)
			HddRemainingAlarm();
	}
	if(nIDEvent==200)//Frame 기록.
	{
	}
	if(nIDEvent==TEVENT_CHECKLENGTH)//Frame 기록.
	{
		if(int(m_dMachineLength) > m_nOldLength){
	//화일 복사 // 파일 리드 //길이에 넣기

			m_nOldLength = int(m_dMachineLength);
		}
	}
	if(nIDEvent == TIMER_UPDATESTATICS){
//		if(m_bAuto){
 //		m_defectMap->Invalidate();
 //		m_defectMap->RedrawMap();
			RedrawMap();
//		}
	}
	if(nIDEvent == 200624){			// kjh 200624
		BOOL bResult = CheckNsysNGFile();
	}
	if(nIDEvent == WM_TIMER_CHECK_SERVER_INI_RECEIVE){		// 200709 kjh
		CString strCheckFilePath, strModelPath1, strModelPath2;
		int nCheck;
		CStdioFile chkFile;

		if(m_strComputerName.Mid(8,1) == "H" && m_strComputerName.Mid(9,1) == "T")
			nCheck = 1;
		else if(m_strComputerName.Mid(8,1) == "H" && m_strComputerName.Mid(9,1) == "B")
			nCheck = 3;
		else if(m_strComputerName.Mid(8,1) == "M" && m_strComputerName.Mid(9,1) == "T")
			nCheck = 6;
		else
			nCheck = 7;

		strCheckFilePath.Format(_T("%s\\%d.txt"), FOLDER_PATH_SERVER_INI_CHECK, nCheck);
		// 20201021 kjh 체크파일에서 서버 모델명 가져오기
		BOOL bExist = ExistFile(strCheckFilePath);
		if(bExist && chkFile.Open(strCheckFilePath, CFile::modeRead|CFile::typeText)){	
			chkFile.ReadString(m_strServerModel);
			chkFile.Close();
		}
		else
			bExist = FALSE;

		if(bExist){	
			if(m_strServerModel.Compare(_T(""))!=0){		
				if(m_strServerModel.Compare(pDoc->m_data.m_strDefaultModel)!=0){		// 20201019 kjh // 통합서버와 모델이 다를경우 해당 모델 로드
					strModelPath1.Format(_T("C:\\Glim\\Model\\%s.ini"), pDoc->m_data.m_strDefaultModel);
					strModelPath2.Format(_T("C:\\Glim\\Model\\%s.ini"), m_strServerModel);
					if(!ExistFile(strModelPath2)){										// 해당 모델이 없을 경우 현재 모델파일을 복사해서 생성
						CopyFile(strModelPath1, strModelPath2, FALSE);	
						AddtoList(_T("Copy Model File - ")+m_strServerModel,0);
					}	
					LoadModelINIFile(m_strServerModel);									// 모델 파일 로드
					UpdateData(FALSE);
				}
				ReadINIFileFromServer();												// 서버 파라미터 로드
				m_SysParam->TransParam();
				pDoc->m_pDlgInterface->UpdateData(FALSE);
				m_SysParam->UpdateData(FALSE);
				m_bSendServerINI = false;
				//pDoc->m_pDlgInterface->OnButtonSaveIni();
				pDoc->m_pDlgInterface->SendMessage(WM_COMMAND,IDC_BUTTON_SAVE_INI,0);	// save
				m_bSendServerINI = false;
				//m_SysParam->OnBnClickedButtonSaveIni();			
				m_SysParam->SendMessage(WM_COMMAND, IDC_BUTTON_SAVE_INI,0);
				AddtoList("Read Server INI File!", FALSE);
				DeleteFile(strCheckFilePath);
			}
			else
				AfxMessageBox(_T("Integrated Server Model is Empty!!"));
		}
	}
	if(nIDEvent == TIMER_PGM_STATUS){
		static bool bTestMode = false;
		bool bMachineRun;
		int nStatus = 0;
		bMachineRun = (m_bNonCoat[0]==FALSE)?true:false;

		if(bTestMode)
			nStatus = 2;
		else{
			if(bMachineRun){
				if(m_bAuto)
					nStatus = 0;
				else
					nStatus = 1;
			}
			else{
				nStatus = 3;
			}
		}

		if(pDoc->m_pDlgInterface->m_CheckPLCTest){
			pDoc->m_pDlgInterface->UpdateData();
			if(pDoc->m_pDlgInterface->m_radioTestPlc == 0)
				nStatus = 0;
			else if(pDoc->m_pDlgInterface->m_radioTestPlc == 1)
				nStatus = 1;
			else if(pDoc->m_pDlgInterface->m_radioTestPlc == 2)
				nStatus = 2;
			else
				nStatus = 3;

			if(m_strComputerName.Mid(9,1) == "T")
				SendPgmStatus(0, nStatus);
			else
				SendPgmStatus(1, nStatus);
		}
		else{
			if(m_strComputerName.Mid(9,1) == "T")
				SendPgmStatus(0, nStatus);
			else
				SendPgmStatus(1, nStatus);
		}
	}

	CFormView::OnTimer(nIDEvent);
}

void CVisWebView::fnCheckLight()
{
	if((m_bAuto==FALSE && m_bRun==FALSE) || (m_bAuto<0 && m_bRun<0))		return ;

	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CString str;
	CString strSendData,strtmp;
	strSendData = "";

	int comPort = DEFAULTPORT;

	int i,j;
	for( i=0;i<pDoc->m_data.m_nLgtController;i++)
	{
//		if(m_LightCtrl[i].m_bConnected == TRUE)
//			getCurrentData(i);
	}
	if(i!=0)
	{
		//CPacket* packet = new CPacket;

		////m_strElect.Format("%.1f",m_Electric[0]);					//전류
		////m_strVolt.Format("%.1f",m_Voltage[0]);						//전압 
		////m_strCElect.Format("%.0f",m_CurrentElectric[0]);			//현재설정값 
		////UpdateData(FALSE);

		////SendPacket Insert
		//for(j=0;j<pDoc->m_data.m_nLgtController;j++)
		//{
		//	//전체 개수_00.0_00.0_000_00.0_00.0_000
		//	if(j==0)	strtmp.Format("%.1f_%.1f_%.0f",m_Electric[j],m_Voltage[j],m_CurrentElectric[j]);
		//	else		strtmp.Format("_%.1f_%.1f_%.0f",m_Electric[j],m_Voltage[j],m_CurrentElectric[j]);
		//	strSendData += strtmp;				
		//}
		//pDoc->m_SendtoServerSock.SendInstantData_LocalHostLight(strSendData,double(pDoc->m_data.m_nLgtController));		//str : Data // double : Count
		//delete packet;

		//fnWriteLight(strSendData);
	}
}


void CVisWebView::HddRemainingAlarm()
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
}

#define KILO	1024
void CVisWebView::GetHDDSpace(CString strPath, long *total, long *occupied, long *remaining)
{
	ULARGE_INTEGER lpFree;
	ULARGE_INTEGER lpTotal;
	ULARGE_INTEGER lpOccupied;

	double d_longtotal = 0;
	double d_longremaining = 0;
	double d_longoccupied = 0;

	GetDiskFreeSpaceEx(strPath, &lpFree, &lpTotal, &lpOccupied);

	d_longremaining = ((double)lpFree.HighPart * UINT_MAX) + lpFree.LowPart; // 사용한 공간
	d_longtotal = ((double)lpTotal.HighPart * UINT_MAX) + lpTotal.LowPart; // 총 드라이브 크기
	d_longoccupied = d_longtotal - d_longremaining; // 사용한 공간

	// mega based
	*occupied = (unsigned int)(d_longoccupied / (KILO*KILO));
	*remaining = (unsigned int)(d_longremaining / (KILO*KILO));
	*total = (unsigned int)(d_longtotal / (KILO*KILO));
}

void CVisWebView::OnButtonRestartCasting() 
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	UpdateData();
}

void CVisWebView::GrabImgSave()
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	if(m_dRemainHDDSpace < 25 || m_bSaving[0])	return;

	m_bSaving[0] = TRUE;
	if(pDoc->m_data.m_nVisionLine == GL1){
	}
	else if(pDoc->m_data.m_nVisionLine == GL9){
	}
	else	memmove(pDoc->m_pImageNG->GetImagePtr(),pDoc->m_pImage->GetImagePtr(),pDoc->m_pImage->GetWidth()*pDoc->m_pImage->GetHeight());

	CTime time = CTime::GetCurrentTime();
	CString str_time = time.Format("%Y_%m_%d__%H_%M_%S");

//*TEST KMY
	int pY = int(pDoc->m_data.m_fReturnY[0]);
	int fBcrY = int(pDoc->m_data.m_dCodeDistace);

//*/

	
	CString str,str1;
	CString strLot;
	if(strLot=="")strLot = "NONE";

	{
		str1.Format("%s%s","C:\\Glim\\Image\\",strLot);
		CreateDirectory(str1,NULL);
	}

	//if(pDoc->m_data.m_bSaveBmp)
	//	str.Format("%s\\%s[%05d]%s_%05d_.bmp", str1, pDoc->m_str_lot, g_frame_num, 	pDoc->m_pDlgInterface->ComputerName(), fBcrY);
	//else
//	str.Format("%s\\%s[%05d]%s_%05d_.jpg", str1, pDoc->m_str_lot, g_frame_num, 	pDoc->m_pDlgInterface->ComputerName(), fBcrY);
	str.Format("%s\\%s[%05d]%s_%05d_.bmp", str1, ConvertCharToStr(cLotID), g_frame_num, 	pDoc->m_pDlgInterface->ComputerName(), fBcrY);

//	pDoc->m_pVision->SaveImg(str);
//	pDoc->m_pImageNG->Save(str);
	if(pDoc->m_data.m_nVisionLine == GL9)
		pDoc->m_pImage->Save(str);
	else 
		pDoc->m_pImage->Save(str);

	m_bSaving[0] = FALSE;
}

void CVisWebView::GrabImgSaveCam2(int nCam)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	double d1,d2;
	d1 = GetPrecisionTime();

	if((m_dRemainHDDSpace < 5 && m_dRemainHDDSpace !=0) || m_bSaving[nCam]){	m_bSaving[nCam] = FALSE;		return;	}
	if((m_dRemainHDDSpace ==0 && m_dRemainMainSpace <5) || m_bSaving[nCam]){	m_bSaving[nCam] = FALSE;		return;	}
	m_bSaving[nCam] = TRUE;
		//		memmove(pDoc->m_pImageNG->GetImagePtr(),pDoc->m_pImage->GetImagePtr(),pDoc->m_pImage->GetWidth()*pDoc->m_pImage->GetHeight());


	CTime time = CTime::GetCurrentTime();
	CString str_time = time.Format("%Y%m%d_%H%M%S");

//*TEST KMY
	int pY = int(pDoc->m_data.m_fReturnY[0]);
	int fBcrY = int(pDoc->m_data.m_dCodeDistace);

//*/

	CString path1;
	if( m_dRemainHDDSpace>5){	//D 드라이브 저장
		path1 = PATH_IMAGE_EXT1;
	}
	else{
		path1 = PATH_IMAGE_INSIDE;
	}
	
	CString strLot;
	strLot = ConvertCharToStr(cLotID);
	if(strLot=="")strLot = "NONE";
	if(strLot.Find("NONE")>=0 || strLot =="")
		{	m_bSaving[nCam] = FALSE;		return;	}

	CTime ttime = CTime::GetCurrentTime();
	CString kk = ttime.Format("%Y%m%d");//ttime.Format("%H_%M_%S");

	CString strTime = ttime.Format("%Y%m%d-%H:%M:%S");

	CString str,str1;
	{

		//str1.Format("%s%s","C:\\Glim\\Image\\",pDoc->m_str_lot);
		str1.Format("%s",path1);
		CreateDirectory(str1,NULL);
		str1.Format("%s%s\\",path1,kk);
		CreateDirectory(str1,NULL);
		str1.Format("%s%s\\%s",path1,kk,strLot);
		CreateDirectory(str1,NULL);
	}
	if(str1 == "d:\\Image1\\"){
		str1 = "d:\\Image1\\None\\";
		CreateDirectory(str1,NULL);
		{	m_bSaving[nCam] = FALSE;		return;	}
	}


//	str.Format("%s\\%s[%05d]%s_%s_CAM%d.jpg", str1, pDoc->m_str_lot, pDoc->m_nTotalIns[nCam], m_strComputerName, str_time, nCam);
	str.Format("%s\\%s[%05d]%s_%d_CAM%d.jpg", str1, strLot, pDoc->m_nTotalIns[0], m_strComputerName, pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck], nCam);
//	str.Format("%s\\%s[%05d]%s_%s_CAM%d.bmp", str1, pDoc->m_str_lot, pDoc->m_nTotalIns[nCam], pDoc->m_pDlgInterface->ComputerName(), str_time, nCam);
	{
		if(nCam == 1){
			pDoc->m_pImage1->Save(str);
		}
		else if(nCam == 2){
			pDoc->m_pImage2->Save(str);
		}
 		else{
 			pDoc->m_pImage->Save(str);
 		}
		m_bSaving[nCam] = FALSE;
	}
// 	else 
// 		pDoc->m_pImageNG->Save(str);

	d2 = GetPrecisionTime();
	pDoc->m_data.m_dSaveTime[nCam] = d2-d1;
}



void CVisWebView::GrabSaveMini(int nCam)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	
	
	if(m_dRemainHDDSpace < 30 || m_bSaving[0] || m_bSaving1)	return;

	CTime time = CTime::GetCurrentTime();
	CString str_time = time.Format("%Y_%m_%d__%H_%M_%S");

//*TEST KMY
	int pY = int(pDoc->m_data.m_fReturnY[0]);
	int fBcrY = int(pDoc->m_data.m_dCodeDistace);
	CString strLot;
	strLot = ConvertCharToStr(cLotID);
	if(strLot=="")strLot = "NONE";

	
	CString str,str1;
		str1.Format("%s%s","C:\\Glim\\Image\\",strLot);
		CreateDirectory(str1,NULL);

	if(pDoc->m_data.m_bSaveBmp)
		str.Format("%s\\%s[%05d]%s_%05d_%d.bmp", str1, strLot, g_frame_num, pDoc->m_pDlgInterface->ComputerName(), fBcrY,nCam);
	else
		str.Format("%s\\%s[%05d]%s_%05d_%d.jpg", str1, strLot, g_frame_num, pDoc->m_pDlgInterface->ComputerName(), fBcrY,nCam);
		
	if(nCam==0)
		pDoc->m_pImageMini->Save(str);
	else
		pDoc->m_pImageMini1->Save(str);


}

void CVisWebView::DrawImage(int nCam)
{
	if(((CVisWebApp*)AfxGetApp())->m_debugLogWrite == TRUE){
		((CVisWebApp*)AfxGetApp())->WriteLog(PATH_DEBUG_LOG, "debug_log", "DrawImage");
	}
	m_bDrawStats = TRUE;

	CVisWebDoc	*pDoc	 = (CVisWebDoc*)GetDocument();
	CString strTmp;
	CRect rcDIB, rcDest,rcDest1,rcDest2;

	if((m_bAuto==FALSE && m_bRun==FALSE) ){
		m_bDrawStats = FALSE;
		return ;
	}

	if(m_bViewTest)
		m_bViewTest = m_bViewTest;
	CDC* pDC = GetDC();

// 	CBitmap* pOldBmp; //oldbmp
// 	CRect rtdraw;
// 	rtdraw.SetRect(0,0,1920,1080);
// 	CDC memDC;
// 	m_Bitmap.DeleteObject(); //기존꺼 지워줌
// 	m_Bitmap.CreateCompatibleBitmap(pDC, rtdraw.Width(), rtdraw.Height()); //새로 만들어줌
// 	memDC.CreateCompatibleDC(pDC); //memDC도 새로 만들어줌
// 	pOldBmp = memDC.SelectObject(&m_Bitmap); //memDC의 비트맵 선택


	double dtime1 = GetPrecisionTime();

	if(m_bViewImage){
		CRect rcMain;
		GetWindowRect(rcMain);
		//전체화면 이미지 사이즈
		GetDlgItem(IDC_DISPLAY)->GetWindowRect(rcDest);
		GetDlgItem(IDC_DISPLAY2)->GetWindowRect(rcDest1);
		GetDlgItem(IDC_DISPLAY3)->GetWindowRect(rcDest2);

		rcDest.OffsetRect(-rcMain.left,-rcMain.top);	
		rcDest1.OffsetRect(-rcMain.left,-rcMain.top);	
		rcDest2.OffsetRect(-rcMain.left,-rcMain.top);	

		if(pDoc->m_pDlgInterface->m_bImageShowHide)
		{
			if(!pDoc->m_pImage->IsDataNull())
			{		
 				rcDIB.top = 0;
 				rcDIB.left = 0;
 				rcDIB.right = pDoc->m_pImage->GetWidth();
 				rcDIB.bottom = pDoc->m_pImage->GetHeight();
				
				if(nCam==3){
					pDoc->m_pImage->Draw(pDC->m_hDC,&rcDIB,&rcDest);
					pDoc->m_pImage1->Draw(pDC->m_hDC,&rcDIB,&rcDest1);
					pDoc->m_pImage2->Draw(pDC->m_hDC,&rcDIB,&rcDest2);

				}
				else if(nCam==4){
					pDoc->m_pImage->Draw(pDC->m_hDC,&rcDIB,&rcDest);
					pDoc->m_pImage1->Draw(pDC->m_hDC,&rcDIB,&rcDest1);
					pDoc->m_pImage2->Draw(pDC->m_hDC,&rcDIB,&rcDest2);
					DrawData(pDC,0);
					ReleaseDC(pDC);
					m_bDrawStats = FALSE;

					return;
				}
				else{
					pDoc->m_pImage->Draw(pDC->m_hDC,&rcDIB,&rcDest);
					if(nCam==1){
						pDoc->m_pImage1->Draw(pDC->m_hDC,&rcDIB,&rcDest1);
					}
					if(nCam==2){
						pDoc->m_pImage2->Draw(pDC->m_hDC,&rcDIB,&rcDest2);
					}
				}

			}
		}
		else{
		}
	}
	double dtime2 = GetPrecisionTime();

	CString strline[100];
	double doldpos=0,dcamscale = pDoc->m_data.m_dScaleFactorX[0],dfirst = 0;;//.0423;

	doldpos = pDoc->m_data.m_dNewLineEdgeData1[pDoc->m_data.m_nNewLineCount-1];
	if(doldpos<0)doldpos = 0;

	CString str1;
	dfirst = pDoc->m_data.m_dNewLineEdgeData1[0];
	double dLength = doldpos-dfirst;
// 	if(m_strComputerName.Find("CMI")>=0 && pDoc->m_data.m_nNewLineCount>2&& (dLength  * dcamscale > m_SysParam->m_dFoilSize[1] || dLength  * dcamscale < m_SysParam->m_dFoilSize[0])){
// 		m_nFoilCheck++;
// 		CString strsize;
// 		strsize.Format("Foil1 %.2f , %d,%.1f,%.1f",dLength  * dcamscale,pDoc->m_data.m_nNewLineCount, doldpos,dfirst);
// 		AddtoList(strsize,0);
// 		if(nCam==3){
// 			m_eSaveImageCam2.SetEvent();m_eSaveImageCam3.SetEvent();m_eSaveImage.SetEvent();
// 		}
// 		m_bDrawStats = FALSE;
// 		return;
// 	}			// 20201026 kjh, foil size check 안함. 주석처리.				

	if(pDoc->m_pDlgInterface->m_bEngKor){
		if(m_strComputerName.Mid(8,1)=="H"){
			if(m_strComputerName.Mid(9,1)=="T")
				str1.Format("%s - Head Top : %.2f mm",m_strComputerName.Mid(7,1),dLength  * dcamscale);
			else
				str1.Format("%s - Head BACK : %.2f mm",m_strComputerName.Mid(7,1),dLength  * dcamscale);
		}
		else{
			if(m_strComputerName.Mid(9,1)=="T")
				str1.Format("%s - Mis. Top : %.2f mm",m_strComputerName.Mid(7,1),dLength  * dcamscale);
			else
				str1.Format("%s - Mis. BACK : %.2f mm",m_strComputerName.Mid(7,1),dLength  * dcamscale);

		}
	}
	else{
		if(m_strComputerName.Find("TOP")>=0 || pDoc->m_data.m_strComName.Mid(9,1)=="T")
			if(pDoc->m_pDlgInterface->m_bEngKor)
				str1.Format("TOP WIDHT : %.2f mm" ,  dLength  * dcamscale);
			else
				str1.Format("TOP 제품폭 : %.2f mm" ,  dLength  * dcamscale);
		else
			if(pDoc->m_pDlgInterface->m_bEngKor)
				str1.Format("BACK WIDTH : %.2f mm" ,  dLength  * dcamscale);
			else
				str1.Format("BACK 제품폭 : %.2f mm" ,  dLength  * dcamscale);

	}
	CRect rc11,rc12;
	GetDlgItem(IDC_STATIC_FULL_WIDTH)->GetWindowRect(rc11);
	m_lbTopTitle.GetWindowRect(rc12);

	int nHGap1 = 300;//300
	m_lbFullWidth.SetText(str1);
	int nx1=0,nx2=0,ny1=0,ny2=0;
	nx1 = 310;nx2 = 1290;ny1=90;ny2=rc11.Height();
	if((m_strComputerName.Find("BACK")>=0 ||  pDoc->m_data.m_strComName.Mid(9,1)=="B") && pDoc->m_pDlgInterface->m_bImageShowHide==FALSE)
		m_lbFullWidth.MoveWindow(nx1,ny1,nx2,ny2);
	else	
		m_lbFullWidth.MoveWindow(nx1,ny1,nx2,rc11.Height());

	if(pDoc->m_pDlgInterface->m_bDrawData)
		DrawData(pDC,0);//이미지에 글씨 쓰기
	double dtime3 = GetPrecisionTime();

	if(pDoc->m_pDlgInterface->m_bImageShowHide)
	{//이미지에 불량 rect
		if(m_bNewMode==0){
			int nk1 = nCam;
			for(int kk=0;kk<3;kk++){
				if(nCam==3)nk1 = kk;
				for(int i=0;i<pDoc->m_data.m_nRealDefectCount1[nk1];i++){
	//				if(nCam==1)
					CRect rtrt,rttmp1;
					rtrt=pDoc->m_data.m_rectDefect[kk][i];
					
	// 				rtrt.left = pDoc->m_data.m_rectDefect[kk][i].left + CAM_WIDTH_CIS*kk;
	// 				rtrt.right = rtrt.left + pDoc->m_data.m_rectDefect[kk][i].Width();							
					int width = rcDest.Width();
					int height = rcDest.Height();//*0.5-10;//FORM_IMG_HEIGHT;

					rttmp1.left = (long)((float)(width) / (float)(pDoc->m_pImage->GetWidth()) * (float)(rtrt.left+CAM_WIDTH_CIS*kk));
					rttmp1.top = (long)((float)(height) / (pDoc->m_pImage->GetHeight()) * (float)(rtrt.top));
					rttmp1.right = (long)((float)(width) / (float)(pDoc->m_pImage->GetWidth()) * (float)(rtrt.right+CAM_WIDTH_CIS*kk));
					rttmp1.bottom = (long)((float)(height) / (float)(pDoc->m_pImage->GetHeight()) * (float)(rtrt.bottom));

					DrawRect(pDC, CPoint(rttmp1.left, rttmp1.top), CPoint(rttmp1.right, rttmp1.bottom), COLOR_RED, 2);
					m_nResultOkNg = 1;
				}
				if(nCam<MAX_CAMERAS)break;
			}
			for(int i=0;i<pDoc->m_data.m_nInsulateDefectCount;i++){//이미지에 절연 영역 그리기
					CRect rtrt,rttmp1;
					rtrt=pDoc->m_data.m_rectDefectInsulate[i];
					int width = rcDest.Width();
					int height = rcDest.Height();//*0.5-10;//FORM_IMG_HEIGHT;

					rttmp1.left = (long)((float)(width) / (float)(pDoc->m_pImage->GetWidth())*(float)(rtrt.left) );
					rttmp1.top = (long)((float)(height) / (pDoc->m_pImage->GetHeight()) * (float)(rtrt.top));
					rttmp1.right = (long)((float)(width) / (float)(pDoc->m_pImage->GetWidth())*(float)(rtrt.right));
					rttmp1.bottom = (long)((float)(height) / (float)(pDoc->m_pImage->GetHeight()) * (float)(rtrt.bottom));

					DrawRect(pDC, CPoint(rttmp1.left, rttmp1.top), CPoint(rttmp1.right, rttmp1.bottom), COLOR_INSULATE, 2);
			}
		}
		else{
			for(int kk=0;kk<MOD_COUNT;kk++){
				for(int i=0;i<pDoc->m_data.m_nThreadDefectCountFull[kk];i++){
					CRect rtrt,rttmp1;
					rtrt=pDoc->m_data.m_rtThreadDefectFull[kk][i];
					int width = rcDest.Width();
					int height = rcDest.Height();//*0.5-10;//FORM_IMG_HEIGHT;

					rttmp1.left = (long)((float)(width) / (float)(pDoc->m_pImage->GetWidth()) * (float)(rtrt.left));
					rttmp1.top = (long)((float)(height) / (pDoc->m_pImage->GetHeight()) * (float)(rtrt.top));
					rttmp1.right = (long)((float)(width) / (float)(pDoc->m_pImage->GetWidth()) * (float)(rtrt.right));
					rttmp1.bottom = (long)((float)(height) / (float)(pDoc->m_pImage->GetHeight()) * (float)(rtrt.bottom));

					DrawRect(pDC, CPoint(rttmp1.left, rttmp1.top), CPoint(rttmp1.right, rttmp1.bottom), COLOR_RED, 2);
					m_nResultOkNg = 1;
				}
				if(nCam<MAX_CAMERAS)break;
			}
		}

	}
	double dtime4 = GetPrecisionTime();

	int nmod = pDoc->m_data.m_nCameraWidth/4;
	int nmod1 = pDoc->m_data.m_nCameraHeight/4;

	DrawNGImage(pDC,m_nSelectCam);//??

	double dtime5 = GetPrecisionTime();

	if(nCam==3){//all draw
		for(int kk=0;kk<MAX_CAMERAS;kk++){
			pDoc->m_data.m_bInspectComplete[kk] = FALSE;
		}
	}
	else
		pDoc->m_data.m_bInspectComplete[nCam] = FALSE;

	if(m_avgBrightness[1] > pDoc->m_data.m_dLimitMaxBright[1] || pDoc->m_data.m_nWhiteLineCount[1]>pDoc->m_pDlgInterface->m_nSkipPixel)
	{//코팅이 안되 있을경우 그리지 않는다 ? 폭만 그려야 되나??? 수정 필요
		CString strtmp12;
		if(m_nCylinderOnOff == 0||pDoc->m_data.m_strComName.Find("CMI")>=0){
			strtmp12.Format("Camera Cylinder Off! Check the Camera");
			m_lbNonCoating.SetText(strtmp12);

//		m_lbNonCoating.ShowWindow(1);//코팅 안되 있으면 화며에 글시 쓰기

		}
		else{
			if(pDoc->m_pDlgInterface->m_bEngKor==ENG||pDoc->m_data.m_strComName.Find("CMI")>=0){
				strtmp12.Format("Line needs to be running to enable vision.");
				m_lbNonCoating.SetText(strtmp12);
				m_lbNonCoating.ShowWindow(1);//코팅 안되 있으면 화며에 글시 쓰기
			}
		}


		//라인 그리기 그리고 
		for(int kk=0;kk<MAX_LENGTH;kk++){
			m_lbCoatLen[kk].ShowWindow(0);
		}
		for(int kk=0;kk<MAX_LENGTH;kk++){
			m_lPitchTol[kk].ShowWindow(0);
		}
		CPoint ptOld,pttmp[2];
		CPoint pt,pt2;
		CPoint pt11;
		if(pDoc->m_pDlgInterface->m_bNonCoatingPitch){
			for(int i=0;i<pDoc->m_data.m_nNewLineCount;i++){//전체 영상이 라인 개수
				pt.SetPoint(int(pDoc->m_data.m_dNewLineEdgeData1[i]),0);//(int(pDoc->m_data.m_dLineEdgeData1[k][i]),0);
				pt2.SetPoint(int(pDoc->m_data.m_dNewLineEdgeData1[i]),pDoc->m_data.m_nCameraHeight);//(int(pDoc->m_data.m_dLineEdgeData1[k][i]),0);
				doldpos = pDoc->m_data.m_dNewLineEdgeData1[i];
				if(pDoc->m_pDlgInterface->m_bImageShowHide)
					DrawLineCam(pDC,pt,pt2,COLOR_GREEN,2,0,i);//영상에 라인 그리기
				pt = DrawPitchCam(pDC,pt,pt2,COLOR_BLACK,2,0,i);//화면에 선 그리기
				if(i==0)pttmp[0] = pt;
				else	pttmp[1] = pt;
			}
		}

		if(pDoc->m_data.m_nNewLineCount>2&&  dLength  * dcamscale > m_SysParam->m_dFoilSize[1] || dLength  * dcamscale < m_SysParam->m_dFoilSize[0]){
			m_nFoilCheck++;
			CString strsize;
			strsize.Format("Foil Width %.2f ",dLength  * dcamscale);
			strsize.Format("Foil2 %.2f , %d,%.1f,%.1f",dLength  * dcamscale,pDoc->m_data.m_nNewLineCount, doldpos,dfirst);
			if(nCam==3){
				m_eSaveImageCam2.SetEvent();m_eSaveImageCam3.SetEvent();m_eSaveImage.SetEvent();
			}
			AddtoList(strsize,0);

		}
		else{
			m_nFoilCheck = 0;
			m_nFoilCount = 0;
			KillTimer(14223);
			if(	m_strAlarmMsg == "Foil Width"){
				m_AlarmDlg->ShowWindow(0);
				m_lbFullWidth.SetTextColor(COLOR_YELLOW);
				m_lbFullWidth.SetBkColor(COLOR_BLACK);

			}
		}
		AddtoList("Display Skip",0);
		ReleaseDC(pDC);
		m_bDrawStats = FALSE;
		return;
	}
	else{
		if(m_nCylinderOnOff == 0 && pDoc->m_data.m_strComName.Find("CMI")>=0){
			CString strtmp12;
			strtmp12.Format("Camera Cylinder Off! Check the Camera");
			m_lbNonCoating.SetText(strtmp12);
//			m_lbNonCoating.ShowWindow(1);

		}else		m_lbNonCoating.ShowWindow(0);
	}



	if(pDoc->m_pDlgInterface->m_bSim1==TRUE){	
		for(int k=0;k<MAX_CAMERAS;k++){
			pDoc->m_data.m_nLineCount1[k] = 2;
			pDoc->m_data.m_dLineEdgeData1[0][0] = 5329;
			pDoc->m_data.m_dLineEdgeData1[0][1] = 5422;
			pDoc->m_data.m_dLineEdgeData1[1][0] = 3307;
			pDoc->m_data.m_dLineEdgeData1[1][1] = 4034;
			pDoc->m_data.m_dLineEdgeData1[2][0] = 1913;
			pDoc->m_data.m_dLineEdgeData1[2][1] = 1987;
		}
	}

	for(int i=0;i<pDoc->m_data.m_nNewLineCount && i<10;i++){
		if(i>0){
			strline[i-1].Format("%.2f",(pDoc->m_data.m_dNewLineEdgeData1[i]-doldpos)*dcamscale);
		}
		doldpos = pDoc->m_data.m_dNewLineEdgeData1[i];
	}
//검사가 다 끝난 경우
	BOOL	bLooping = FALSE;
	for(int i1=0;i1<1;i1++){
		if((pDoc->m_data.m_bInspectComplete[0] == FALSE && pDoc->m_data.m_bInspectComplete[1]==FALSE && pDoc->m_data.m_bInspectComplete[2]==FALSE) || bLooping){
			if( m_bMismatchView){
				DrawMismatch();

			}
			else{
				int nLineCount1 = pDoc->m_data.m_nNewLineCount;
				CPoint ptOld,pttmp[2];
				CPoint pt,pt2;
				CPoint pt11;
				pDoc->m_data.m_bIsDispCheck = FALSE;
				int	nAlarmCheck = 0;
				for(int k=0;k<MAX_CAMERAS;k++){
					pDoc->m_data.m_bInspectComplete[k] = TRUE;
				}

				for(int i=0;i<pDoc->m_data.m_nNewLineCount && i<10;i++){//전체 영상이 라인 개수
					if(i>=MAX_LENGTH-1)break;
					pt.SetPoint(int(pDoc->m_data.m_dNewLineEdgeData1[i]),0);//(int(pDoc->m_data.m_dLineEdgeData1[k][i]),0);
					pt2.SetPoint(int(pDoc->m_data.m_dNewLineEdgeData1[i]),pDoc->m_data.m_nCameraHeight);//(int(pDoc->m_data.m_dLineEdgeData1[k][i]),0);
					if(i==0)dfirst = pDoc->m_data.m_dNewLineEdgeData1[i];//pDoc->m_data.m_dLineEdgeData1[k][i];
					if(i>0){
						strline[i-1].Format("%.2f",(pDoc->m_data.m_dNewLineEdgeData1[i]-doldpos)*dcamscale);
					}
					doldpos = pDoc->m_data.m_dNewLineEdgeData1[i];
					if(pDoc->m_pDlgInterface->m_bImageShowHide)
						DrawLineCam(pDC,pt,pt2,COLOR_GREEN,2,0,i);//영상에 라인 그리기
					pt = DrawPitchCam(pDC,pt,pt2,COLOR_BLACK,2,0,i);//화면에 선 그리기
					if(i==0)pttmp[0] = pt;
					else	pttmp[1] = pt;
					if(i>0/* && m_nDataMissing==0*/){
						if(m_avgBrightness[0] > pDoc->m_data.m_dLimitMaxBright[0] || pDoc->m_data.m_nWhiteLineCount[0]>pDoc->m_pDlgInterface->m_nSkipPixel)
							continue;
						double d1 =  m_dTolerance[(i-1)*2];//m_dStardLen[nLineCount1-1] +	 min 
						double d2 =  m_dTolerance[(i-1)*2+1];//m_dStardLen[nLineCount1-1] -	max 
					
						double d3=0; 
						double d4=0;
						if(pDoc->m_pDlgInterface->m_bInsideSet){		//모디파이 체크 시 min/max 값으로 설정 	
 							d3 =  m_dTolerance1[(i-1)*2];//m_dStardLen[nLineCount1-1] +
 							d4 =  m_dTolerance1[(i-1)*2+1];//m_dStardLen[nLineCount1-1] -
 						}
 						else{								//모디파이 언체크 시 설정값 만큼 안쪽으로 설정 
 							d3 = d1 + m_dTolerance2[i-1];		//min = min + 설정값
 							d4 = d2 - m_dTolerance2[i-1];		//max = max - 설정값
						}
						
					

						if(m_bUseLen[i-1] ==TRUE &&(atof(strline[i-1]) <d3 || atof(strline[i-1]) >d4)){
							if(m_bUseLen[i-1] ==TRUE &&(atof(strline[i-1]) <d1 || atof(strline[i-1]) >d2)){
								//ng
								m_nNGCount[i-1]++;
								//해당 글자 빨간색
								m_bNGLen[i-1] = TRUE;
								m_nTextColor[i-1] = 2;//red
								if(pDoc->m_data.m_dBadAlarmMeter <m_nNGCount[i-1]){//Alarm
									if(pDoc->m_pDlgInterface->m_bAlarm ){//Alarm//알람
										nAlarmCheck++;
									}
								}
							}
							else{//파란글씨
								m_nTextColor[i-1] = 1;//blue
							}
						}
						else{
							m_nNGCount[i-1] = 0;//연속 미터수
							m_bNGLen[i-1] = FALSE;//현재 불량
							m_nTextColor[i-1] = 0;//black
						}
					}
					if(i>0 && i<=10){
						CString strtemp1="",strtemp2="";
						//글자 추가
						if(i%2==1){//양극 절연 일때만 글자 표시
							for(int k2=0;k2<pDoc->m_data.m_nInsulateCount;k2++){
								CRect rtinsul;
								rtinsul = pDoc->m_data.m_rtinsulate1[k2];
								rtinsul.InflateRect(30,0);
								if(	(rtinsul.left<pt2.x && rtinsul.right>pt2.x)  ){
									strtemp2.Format("%.2f",pDoc->m_data.m_rtinsulate1[k2].Width()*pDoc->m_data.m_dScaleFactorX[0]);
									break;
								}
								else if(i>2 &&(rtinsul.left<pt11.x && rtinsul.right>pt11.x)  ){
									strtemp2.Format("%.2f",pDoc->m_data.m_rtinsulate1[k2].Width()*pDoc->m_data.m_dScaleFactorX[0]);
									break;
								}
							}
							strtemp1 .Format("%s",strline[i-1]);//= strline[i-1];

							if(pDoc->m_pDlgInterface->m_nColorGray|| pDoc->m_data.m_strComName.Mid(7,1)=="C")
								DrawRectangle1(pDC,pt,pt2,ptOld,COLOR_GRAY_WHITE1,2,0,i-1,strtemp1,strtemp2);//공차 폭 
							else
								DrawRectangle1(pDC,pt,pt2,ptOld,COLOR_ORANGE1,2,0,i-1,strtemp1,strtemp2);
						}
						else{
							strtemp1 .Format("\r\n%s",strline[i-1]);//= strline[i-1];
							DrawRectangle1(pDC,pt,pt2,ptOld,COLOR_BLACK,2,0,i-1,strtemp1,strtemp2);//strline[i-1]);
						}
					}	
					pt11 = pt2;

					ptOld = pt;
				}
// 				CString strtmp1 = "  N-Coat : ",strtmp2 = "  Coat    : ";
// 				CString strLastData1, strLastData2;
// 				strtmp1 += (strline[0]);
// 				strtmp2 += (strline[1]);
// 				strLastData1 += strline[0];
// 				strLastData2 += strline[1];
// 
// 				for(int i=2;i<pDoc->m_data.m_nNewLineCount-1 && pDoc->m_data.m_nNewLineCount%2==0;i++){//전체 영상이 라인 개수
// 					if(i%2==0){//무지
// 						strtmp1 += (",   "+strline[i] );
// 						strLastData1 += strline[i]+",";
// 					}
// 					else{
// 						strtmp2 += (",   "+strline[i] );
// 						strLastData2 += strline[i]+",";
// 					}
// 				}
// 				m_strLastCoatWidth = strtmp1;
// 				m_strLastNonCoatWidth = strtmp2;
// 
// 				// 20201008 kjh last data
// 				static int nLastMeter = 0;
// 				LAST_DATA lastData;
// 
// 				if((nLastMeter != pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck]) && pDoc->m_pDlgInterface->m_bLastData){
// 					CString data[6], strTime;
// 					CTime timer=CTime::GetCurrentTime();	
// 					CString ymd = timer.Format("%Y%m%d");
// 					data[0].Format("%d", timer.GetYear());
// 					if(timer.GetMonth() < 10)		data[1].Format("0%d", timer.GetMonth());
// 					else		data[1].Format("%d", timer.GetMonth());
// 					if(timer.GetDay() < 10)		data[2].Format("0%d", timer.GetDay());
// 					else		data[2].Format("%d", timer.GetDay());
// 					if(timer.GetHour() < 10)		data[3].Format("0%d", timer.GetHour());
// 					else		data[3].Format("%d", timer.GetHour());
// 					if(timer.GetMinute() < 10)		data[4].Format("0%d", timer.GetMinute());
// 					else		data[4].Format("%d", timer.GetMinute());
// 					if(timer.GetSecond() < 10)		data[5].Format("0%d", timer.GetSecond());
// 					else		data[5].Format("%d", timer.GetSecond());
// 
// 					strTime.Format(_T("%s%s%s-%s:%s:%s"), data[0],data[1],data[2],data[3],data[4],data[5]);
// 					nLastMeter = pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck];
// 					lastData.strTime = strTime;
// 					lastData.nMeter = nLastMeter;
// 					lastData.strCoat = strLastData2;
// 					lastData.strNCoat = strLastData1;
// 					if(m_qLastData.size() >= 250)
// 						m_qLastData.pop();
// 					m_qLastData.push(lastData);					
// 				}



				if(pDoc->m_pDlgInterface->m_bAlarm && pDoc->m_pDlgInterface->m_bWidthAlarm && nAlarmCheck>0 /* && m_nDataMissing==0*/){
					//m_IO[0].WriteOutputPort(0,0,TRUE);
					m_bAlarmOnOff = TRUE;
					int ntmpmeter =  pDoc->m_nTotalIns[0]+pDoc->m_pDlgInterface->m_dBadAlarmMeter;
					if(m_nAlarmEndFRame < ntmpmeter)
						m_nAlarmEndFRame = ntmpmeter;
					m_nAlarmLog =1;
					CString str;
					//	str.Format("폭Alarm On E:%d,")
					m_strAlarmMsg = "Width NG";
					m_strAlarmMsg1.Format("%d M", pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck]) ;

					AddtoList("Alarm On Width",0,TRUE);
				}
				else{
					// 			m_IO[0].WriteOutputPort(0,0,FALSE);
				}
				if(nLineCount1%2==1)nLineCount1--;//홀수일때 짝수를 만든다.
				if(nLineCount1<0)nLineCount1 = 0;
				if(nLineCount1>0){
					for(int kk=nLineCount1-1;kk<MAX_LENGTH;kk++){
						m_lbCoatLen[kk].ShowWindow(0);
					}
					for(int kk=nLineCount1*2-2;kk<MAX_LENGTH;kk++){
						m_lPitchTol[kk].ShowWindow(0);
					}
				}
				else{
					for(int kk=0;kk<MAX_LENGTH;kk++){
						m_lbCoatLen[kk].ShowWindow(0);
					}
					for(int kk=0;kk<MAX_LENGTH;kk++){
						m_lPitchTol[kk].ShowWindow(0);
					}
				}
				//mismatch data show
				CString strpitch1;
				int nstaticWidth = 110;//20;
				if(m_strComputerName.Find("BACK")>=0 ||  pDoc->m_data.m_strComName.Mid(9,1)=="B"){
					double dsumdata1 = 0;
					CRect rcMain11,rtMis1,rtmis2,rtmis3,rctmp11;
					GetWindowRect(rcMain11);
					GetDlgItem(IDC_DETAIL_LINE)->GetWindowRect(rctmp11);
					rctmp11.OffsetRect(-rcMain11.left,-rcMain11.top);	
					int ngap1 = 46,nGap2 = 20;;
					CString strtmp;
					for(int kk=0;kk<nLineCount1 && m_nDataMissing==0;kk+=2){
						if(kk>=MAX_LENGTH-4)break;
						int ncontext = IDC_STATIC_COAT_LEN1+kk;
						GetDlgItem(ncontext)->GetWindowRect(rtMis1);
						rtMis1 = pDoc->m_data.m_rtCoatChar[kk];
						if(pDoc->m_pDlgInterface->m_bImageShowHide){
							rtmis2.SetRect(rtMis1.left-nGap2,rctmp11.bottom+20+ngap1,rtMis1.left+nstaticWidth-nGap2,rctmp11.bottom+36+20+ngap1);//125
							rtmis3.SetRect(rtMis1.right-nstaticWidth+15+nGap2,rctmp11.bottom+20+ngap1,rtMis1.right-10+nGap2,rctmp11.bottom+36+20+ngap1);//95
						}
						else{
							rtmis2.SetRect(rtMis1.left-nGap2,m_rtDetailView.bottom+20+ngap1,rtMis1.left+nstaticWidth-nGap2,m_rtDetailView.bottom+36+20+ngap1);
							rtmis3.SetRect(rtMis1.right-nstaticWidth+15+nGap2,m_rtDetailView.bottom+20+ngap1,rtMis1.right-10+nGap2,m_rtDetailView.bottom+36+20+ngap1);
						}
						m_lbCoatTitle[2+kk].MoveWindow(rtmis2);
						m_lbCoatTitle[2+kk+1].MoveWindow(rtmis3);
						if(kk==nLineCount1-2 &&nLineCount1>2)
							m_lbCoatTitle[2+kk+1].ShowWindow(0);

						CRect rtgap1,rtgap2;
						// 기존 누적 피치에서 탑백 폭으로 교체
						// 					rtgap1.left = rtmis2.left;
						// 					rtgap1.top = rtmis2.bottom+5;
						// 					rtgap1.right = rtmis2.Width()+rtmis2.left;;
						// 					rtgap1.bottom = rtmis2.Height()+rtgap1.top-15;
						// 					m_lbGapMisMatch[kk].MoveWindow(rtgap1);
						// 					rtgap2.left = rtmis3.left;
						// 					rtgap2.top = rtmis3.bottom+5;
						// 					rtgap2.right = rtmis3.Width()+rtmis3.left;;
						// 					rtgap2.bottom = rtmis3.Height()+rtgap2.top-15;
						// 					m_lbGapMisMatch[kk+1].MoveWindow(rtgap2);
						// 					if(kk>0)
						// 						m_lbGapMisMatch[kk].ShowWindow(1);
						// 					m_lbGapMisMatch[kk+1].ShowWindow(1);
						// 

						dsumdata1 = pDoc->m_data.m_dReversePitchData[kk+1] - pDoc->m_data.m_dReversePitchData[kk];
						if(dsumdata1<=0)continue;
						strtmp.Format("%.2f",dsumdata1);
						m_lbCoatLenTop[kk+2].SetText(strtmp);
						dsumdata1 = pDoc->m_data.m_dReversePitchData[kk+2] - pDoc->m_data.m_dReversePitchData[kk+1];
						if(dsumdata1<=0)continue;
						strtmp.Format("%.2f",dsumdata1);
						m_lbCoatLenTop[kk+1+2].SetText(strtmp);


					}
					for(int kk=nLineCount1;kk<MAX_LENGTH;kk++)
						m_lbGapMisMatch[kk].ShowWindow(0);
					for(int kk=nLineCount1+2;kk<MAX_LENGTH;kk++){
						m_lbCoatTitle[kk].ShowWindow(0);
//						m_lPitchTol[kk].ShowWindow(0);//check

					}
					for(int kk=nLineCount1*2-2;kk<MAX_LENGTH;kk++){
						m_lPitchTol[kk].ShowWindow(0);
					}

					double dLength13 = (doldpos-dfirst)*dcamscale;//back pitch 
					double dlengap = fabs(pDoc->m_data.m_dReversePitchData[nLineCount1-1] - dLength13);

					//길이가 일정 이상 차이나ㅕㄴ 무조건 실행
					if(dlengap>0.08 && pDoc->m_data.m_dReversePitchData[nLineCount1-1]>100){
						m_nLengFrmaeGap++;
						if(pDoc->m_pDlgInterface->m_bNewScale && m_nLengFrmaeGap>=pDoc->m_pDlgInterface->m_nSumFrame )
						{
							m_dNewScaleX = (dLength13*m_dScaleSum)/pDoc->m_data.m_dReversePitchData[nLineCount1-1];
							double ds1 = (pDoc->m_data.m_dReversePitchData[nLineCount1-1]*m_dScaleSum)/dLength13;
							double ds2 = (pDoc->m_data.m_dReversePitchData[nLineCount1-1]*dcamscale)/dLength13;
							pDoc->m_data.m_dScaleFactorX[0]=pDoc->m_data.m_dScaleFactorX[1]=pDoc->m_data.m_dScaleFactorX[2]=m_dNewScaleX=ds2;
							CString strtt;
							strtt.Format("New Scale %.6f",m_dNewScaleX);
							AddtoList(strtt,0);

							m_nLengFrmaeGap = 0;
						}
					}
					else{
						m_nLengFrmaeGap = 0;
					}

					strtmp.Format("Top폭\n%.2fmm",pDoc->m_data.m_dReversePitchData[nLineCount1-1]);
					if(pDoc->m_data.m_dReversePitchData[nLineCount1-1]>1){
						m_lbTopTitle.SetText(strtmp);	
					}
				}
				else{
					//if(pDoc->m_data.m_dMisData[pDoc->m_data.m_nReadCount][0] == -1000)
					{
						double dsumdata1 = 0;
						CRect rcMain11,rtMis1,rtmis2,rtmis3,rctmp11;
						GetWindowRect(rcMain11);
						GetDlgItem(IDC_DETAIL_LINE)->GetWindowRect(rctmp11);
						rctmp11.OffsetRect(-rcMain11.left,-rcMain11.top);	
						int ngap1 = 46,nGap2 = 20;;
						CString strtmp;
						if(pDoc->m_data.m_nReadCount>99)pDoc->m_data.m_nReadCount = 0;
						for(int i=0;i<nLineCount1;i+=2){
							if(i>=MAX_LENGTH-4)break;
							int ncontext = IDC_STATIC_COAT_LEN1+i;//m_
							GetDlgItem(ncontext)->GetWindowRect(rtMis1);
							rtMis1 = pDoc->m_data.m_rtCoatChar[i];
							if(pDoc->m_pDlgInterface->m_bImageShowHide){
								rtmis2.SetRect(rtMis1.left-nGap2,rctmp11.bottom+20+ngap1,rtMis1.left+nstaticWidth-nGap2,rctmp11.bottom+36+20+ngap1);
								rtmis3.SetRect(rtMis1.right-nstaticWidth+nGap2,rctmp11.bottom+20+ngap1,rtMis1.right+nGap2,rctmp11.bottom+36+20+ngap1);
							}
							else
							{
								rtmis2.SetRect(rtMis1.left-nGap2,m_rtDetailView.bottom+20+ngap1,rtMis1.left+nstaticWidth-nGap2,m_rtDetailView.bottom+36+20+ngap1);
								rtmis3.SetRect(rtMis1.right-nstaticWidth+nGap2,m_rtDetailView.bottom+20+ngap1,rtMis1.right+nGap2,m_rtDetailView.bottom+36+20+ngap1);
							}
							m_lbCoatTitle[2+i].MoveWindow(rtmis2);
							m_lbCoatTitle[2+i+1].MoveWindow(rtmis3);
							if(pDoc->m_data.m_dMisData[pDoc->m_data.m_nReadCount][0] == -1000)
								strtmp.Format("%.2f",pDoc->m_data.m_dMisData[pDoc->m_data.m_nReadCount][i]);
							else {
								if(pDoc->m_data.m_dMisData[(pDoc->m_data.m_nReadCount+99)%100][0] == -1000 )
									strtmp.Format("%.2f",pDoc->m_data.m_dMisData[(pDoc->m_data.m_nReadCount+99)%100][i]);
								else if(pDoc->m_data.m_dMisData[(pDoc->m_data.m_nReadCount+98)%100][0] == -1000 )
									strtmp.Format("%.2f",pDoc->m_data.m_dMisData[(pDoc->m_data.m_nReadCount+98)%100][i]);
								else if(pDoc->m_data.m_dMisData[(pDoc->m_data.m_nReadCount+97)%100][0] == -1000 )
									strtmp.Format("%.2f",pDoc->m_data.m_dMisData[(pDoc->m_data.m_nReadCount+97)%100][i]);
								else{
									if(m_dLastTenMeter[pDoc->m_data.m_nReadCount%10][i] !=0)
										strtmp.Format("%.2f",m_dLastTenMeter[pDoc->m_data.m_nReadCount%10][i]);
									else
										strtmp = "0.0";
								}
							}
							if(atof(strtmp) !=0)
								m_dLastTenMeter[pDoc->m_data.m_nReadCount%10][i] = atof(strtmp);
							CPoint pt12;
							pt12.SetPoint(rtmis2.left+pDoc->m_nTotalIns[1],rtmis2.top);
							//DataDraw(pt12,"999",300,COLOR_BLUE);
							pt12.SetPoint(rtmis3.left+pDoc->m_nTotalIns[1],rtmis3.top);
							//DataDraw(pt12,"999",300,COLOR_BLUE);

							m_lbCoatTitle[2+i].SetText(strtmp);
							if(pDoc->m_data.m_dMisData[pDoc->m_data.m_nReadCount][0] == -1000)
								strtmp.Format("%.2f",pDoc->m_data.m_dMisData[pDoc->m_data.m_nReadCount][i+1]);
							else {
								if(pDoc->m_data.m_dMisData[(pDoc->m_data.m_nReadCount+99)%100][0] == -1000 )
									strtmp.Format("%.2f",pDoc->m_data.m_dMisData[(pDoc->m_data.m_nReadCount+99)%100][i+1]);
								else if(pDoc->m_data.m_dMisData[(pDoc->m_data.m_nReadCount+98)%100][0] == -1000 )
									strtmp.Format("%.2f",pDoc->m_data.m_dMisData[(pDoc->m_data.m_nReadCount+98)%100][i+1]);
								else if(pDoc->m_data.m_dMisData[(pDoc->m_data.m_nReadCount+97)%100][0] == -1000 )
									strtmp.Format("%.2f",pDoc->m_data.m_dMisData[(pDoc->m_data.m_nReadCount+97)%100][i+1]);
								else	{
									if(m_dLastTenMeter[pDoc->m_data.m_nReadCount%10][i] !=0)
										strtmp.Format("%.2f",m_dLastTenMeter[pDoc->m_data.m_nReadCount%10][i+1]);
									else
										strtmp = "0.0";
								}
							}
							if(atof(strtmp) !=0)
								m_dLastTenMeter[pDoc->m_data.m_nReadCount%10][i+1] = atof(strtmp);

							m_lbCoatTitle[2+i+1].SetText(strtmp);
							int nSize1 = 20;
							m_lbCoatTitle[2+i].SetFontSize(nSize1);
							m_lbCoatTitle[2+i+1].SetFontSize(nSize1);

						}
						for(int kk=3;kk<MAX_LENGTH;kk++){
							// 						if(kk>=nLineCount1+2)
							m_lbCoatTitle[kk].ShowWindow(0);
						}
						m_lbCoatTitle[2].ShowWindow(0);

						pDoc->m_data.m_nReadCount++;
					}

				}
				///무지폭 드로우
				BOOL bAnode = TRUE;
				if(bAnode){
					for(int i=0;i<pDoc->m_data.m_nInsulateCount;i++)
						DrawRect(pDC,pDoc->m_data.m_rtinsulate1[i],COLOR_ORANGE1,2);
				}
			}

			CString strtmp1 = "  N-Coat : ",strtmp2 = "  Coat    : ";
			CString strLastData1, strLastData2;
			strtmp1 += (strline[0]);
			strtmp2 += (strline[1]);
			strLastData1 += strline[0] + _T(",");
			strLastData2 += strline[1] + _T(",");
			bool bZero = false;
			for(int i=2;i<pDoc->m_data.m_nNewLineCount-1 && pDoc->m_data.m_nNewLineCount%2==0;i++){//전체 영상이 라인 개수
				if(i%2==0){//무지
					strtmp1 += (",   "+strline[i] );
					strLastData1 += strline[i]+", ";
					if((int)atof(strline[i]) <= 0)
						bZero = true;
				}
				else{
					strtmp2 += (",   "+strline[i] );
					strLastData2 += strline[i]+", ";
					if((int)atof(strline[i]) <= 0)
						bZero = true;
				}
			}
			m_strLastCoatWidth = strtmp1;
			m_strLastNonCoatWidth = strtmp2;

			///// 20201008 kjh last data
			static int nLastMeter = 0;
			LAST_DATA lastData;

			if((nLastMeter != pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck]) && pDoc->m_pDlgInterface->m_bLastData){
				CString data[6], strTime;
				CTime timer=CTime::GetCurrentTime();	
				CString ymd = timer.Format("%Y%m%d");
				data[0].Format("%d", timer.GetYear());
				if(timer.GetMonth() < 10)		data[1].Format("0%d", timer.GetMonth());
				else		data[1].Format("%d", timer.GetMonth());
				if(timer.GetDay() < 10)		data[2].Format("0%d", timer.GetDay());
				else		data[2].Format("%d", timer.GetDay());
				if(timer.GetHour() < 10)		data[3].Format("0%d", timer.GetHour());
				else		data[3].Format("%d", timer.GetHour());
				if(timer.GetMinute() < 10)		data[4].Format("0%d", timer.GetMinute());
				else		data[4].Format("%d", timer.GetMinute());
				if(timer.GetSecond() < 10)		data[5].Format("0%d", timer.GetSecond());
				else		data[5].Format("%d", timer.GetSecond());

				strTime.Format(_T("%s%s%s-%s:%s:%s"), data[0],data[1],data[2],data[3],data[4],data[5]);
				nLastMeter = pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck];
				lastData.strTime = strTime;
				lastData.nMeter = nLastMeter;
				lastData.strCoat = strLastData2;
				lastData.strNCoat = strLastData1;
				lastData.nLine = pDoc->m_data.m_nNewLineCount;
				if(m_qLastData.size() >= 250)
					m_qLastData.pop();
				if(!bZero)
					m_qLastData.push(lastData);					
			}

			//<<<<<<<<
			//글자영역 위치 복사
			BOOL bInvalidate = FALSE;
			////////cis
// 			for(int i=0;i<20;i++){//전체 영상이 라인 개수
// 				CRect rt12;
// 				m_lbCoatLen[i].GetWindowRect(rt12);
// 
// 				if(abs(pDoc->m_data.m_rtOldCoatChar[i].left - pDoc->m_data.m_rtCoatChar[i].left) >=10 ||abs(pDoc->m_data.m_rtOldCoatChar[i].right - pDoc->m_data.m_rtCoatChar[i].right) >=10)
// 					bInvalidate = TRUE;
// 				pDoc->m_data.m_rtOldCoatChar[i] = pDoc->m_data.m_rtCoatChar[i];
// 			}
			if(bInvalidate && bLooping==FALSE){
				//InvalidateRect(CRect(100,100,1800,1000));
				RectInvalidate(pDoc->m_data.m_nNewLineCount);
				Wait(10);
				bLooping = TRUE;
				i1 = -1;
				AddtoList("Pos Change1",0);
			}
		}
	}
	if(pDoc->m_data.m_nNewLineCount>2&& ( dLength  * dcamscale > m_SysParam->m_dFoilSize[1] || dLength  * dcamscale < m_SysParam->m_dFoilSize[0])){
		m_nFoilCheck++;
		CString strsize;
		strsize.Format("Foil1 %.2f , %d,%.1f,%.1f",dLength  * dcamscale,pDoc->m_data.m_nNewLineCount, doldpos,dfirst);
		AddtoList(strsize,0);
		if(nCam==3){
			m_eSaveImageCam2.SetEvent();m_eSaveImageCam3.SetEvent();m_eSaveImage.SetEvent();
		}
	}
	else{
		m_nFoilCheck = 0;
		m_nFoilCount = 0;
		KillTimer(14223);
		if(	m_strAlarmMsg == "Foil Width"){
			m_AlarmDlg->ShowWindow(0);
			m_lbFullWidth.SetTextColor(COLOR_YELLOW);
			m_lbFullWidth.SetBkColor(COLOR_BLACK);

		}
	}
	if(m_nFoilCheck>=10){
		//알람 및 타이틀 밝기 변화
		AddtoList("Foil Width NG",0);
		SetTimer(14223,500,NULL);
	}


	double dtime6 = GetPrecisionTime();

	CString strmsg1;
	strmsg1.Format(	"%.0f, (%0.f,%0.f,%0.f,%0.f,%0.f)",(dtime6-dtime1)*1000,(dtime2-dtime1)*1000,(dtime3-dtime2)*1000,(dtime4-dtime3)*1000,(dtime5-dtime4)*1000,(dtime6-dtime5)*1000);
	if((dtime6-dtime1)*1000 > 100)
		AddtoList(strmsg1,0);
//	pDC->BitBlt(0, 0, rtdraw.right, rtdraw.bottom, &memDC, 0, 0, SRCCOPY);

// 	memDC.SelectObject(pOldBmp);
// 	memDC.DeleteDC();

	ReleaseDC(pDC);
	m_bDrawStats = FALSE;
	if(((CVisWebApp*)AfxGetApp())->m_debugLogWrite == TRUE){
		((CVisWebApp*)AfxGetApp())->WriteLog(PATH_DEBUG_LOG, "debug_log", "DrawImage-end");
	}
}
void CVisWebView::RectInvalidate(int nCount)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	InvalidateRect(CRect(200,100,1800,1000));

// 	for(int i=0;i<nCount;i++){
// 		CRect rt1 = pDoc->m_data.m_rtOldCoatChar[i];
// 		rt1.InflateRect(150,10,150,20);
// 		InvalidateRect(rt1);
// 	}
}
	
void CVisWebView::OnCheckImageSave() 
{
	UpdateData();
}

void CVisWebView::OnButtonInterface() 
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	UpdateTolIni(pDoc->m_data.m_strDefaultModel);					// 20201015 kjh
	pDoc->m_pDlgInterface->LoadInsParam();
	pDoc->m_pDlgInterface->LoadSysParam();//sparam을 사용해야한다.
	pDoc->m_pDlgInterface->	LoadLightParam();

	if(pDoc->m_pDlgInterface->m_bEngKor == KOR){
		if(pDoc->m_pDlgInterface->IsWindowVisible())
			pDoc->m_pDlgInterface->ShowWindow(SW_HIDE);
		else
			pDoc->m_pDlgInterface->ShowWindow(SW_SHOW);
	}
	else{
		if(pDoc->m_pDlgInterface->IsWindowVisible()){
			pDoc->m_pDlgInterface->m_nSelectEdit = -1;
			pDoc->m_pDlgInterface->ShowWindow(SW_HIDE);
			
		}
		else{
			m_pPassword->m_strPassword1 = "";
			m_NumPad->m_nSelectControl=-2;
			m_pPassword->PasswordResult(0);


			m_pPassword->ShowWindow(SW_SHOW);
			m_NumPad->LabelShow1(2,0,0);

			m_pPassword->m_nbSelectNo = 1;
			m_NumPad->ShowWindow(1);
			m_pPassword->GetDlgItem(IDC_EDIT_PASS1)->SetFocus();


	//		pDoc->m_pDlgInterface->ShowWindow(SW_SHOW);
		}
	}

}


void CVisWebView::OnButtonGridModify() 
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	if(pDoc->m_pDlgGrid->IsWindowVisible())
		pDoc->m_pDlgGrid->ShowWindow(SW_HIDE);
	else
		pDoc->m_pDlgGrid->ShowWindow(SW_SHOW);	
}

void CVisWebView::PreStep()
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	int nPcNo = pDoc->m_data.GetVisionLine(0);
//	pDoc->m_pDlgInterface->LoadSysParam();
//	pDoc->m_pDlgInterface->LoadGradeParam();		//Grade
	pDoc->m_pDlgInterface->LoadInsParam();
	pDoc->m_pDlgInterface->LoadSysParam();
	pDoc->m_pDlgInterface->	LoadLightParam();


	for(int i=0;i<MAX_CAMERAS;i++)
		ReadCalData(i);

	m_bDefectSaveStats = TRUE;

	//line
	if(nPcNo != GL1  && nPcNo != GL8&& nPcNo != GL9)
		for(int i=0;i<MAX_CAMERAS;i++){
			if(i==0)
				pDoc->m_pVision->SetExposureTime(i,m_nExpose*25,1);
			else
				pDoc->m_pVision->SetExposureTime(i,m_nExposre1*25,1);
		}

		UpdateData(FALSE);

}

void CVisWebView::Calib_Brightness(int value)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	
//	m_bCalibBrightness = TRUE;
//
//	float temp_avg1 = float(value);
//	float temp_avg2	= 0.0;//(float)m_dAvgBrightness;					//각 프레임의 평균값을 구하여 넣는다.
//	float temp_diff = temp_avg2 - temp_avg1; 				
//	
//	long shutter1 = 0;
//	long shutter2 = pDoc->m_pDlgInterface->m_dExposureTime_inNano;
//	long shutter_diff = 0;
//
//	while( !(temp_diff > -5 && temp_diff < 5) )
//	{				
//		if(temp_diff > 0)
//		{
//			//셔터 스피드 값 변경 - 내림 
//			shutter_diff = abs(shutter2 - shutter1);
//			shutter1 = shutter2;
//			shutter2 = shutter2 - shutter_diff/2;
//			pDoc->m_pDlgInterface->ExposureChange(shutter2);
//			Wait(1000);
//			
//		}
//		else if(temp_diff < 0)
//		{
//			//셔터 스피드 값 변경 - 올림 
//			shutter_diff = abs(shutter1 - shutter2);
//			shutter1 = shutter2;
//			shutter2 = shutter2 + shutter_diff/2;
//			pDoc->m_pDlgInterface->ExposureChange(shutter2);
//			Wait(1000);
//		}
//		else
//		{
//			break;
//		}
//		temp_avg2 = 0.0;//(float)m_dAvgBrightness;					//각 프레임의 평균값을 구하여 넣는다.
//		temp_diff = temp_avg2 - temp_avg1;
//	}
//
////---------여기에서 현재 셔터스피드 값을 서버로 전송을 한다.
////------------------------------------------
//	CString str;
//	str.Format("shutter:%d   brightness:%f", 
//		pDoc->m_pDlgInterface->m_dExposureTime_inNano, 0.0);//m_dAvgBrightness);
//	AfxMessageBox(str);
////------------------------------------------
	
	m_bCalibBrightness = FALSE;
}

void CVisWebView::OnBtnNgImgBacward() 
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	if(m_nCurNGImgIndex > 0)
		m_nCurNGImgIndex--;

	CDC* pDC = GetDC();
	DrawNGImage(pDC,m_nSelectCam);
	ReleaseDC(pDC);


//	DrawImage(m_nSelectCam);
}

void CVisWebView::OnBtnNgImgForward() 
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

//	if(m_nCurNGImgIndex < pDoc->m_data.m_nDefectCount[m_nSelectCam]-1)
	if(m_nCurNGImgIndex < pDoc->m_data.m_nLineCount1[m_nSelectCam]-1)
		m_nCurNGImgIndex++;
	CDC* pDC = GetDC();

	DrawNGImage(pDC,m_nSelectCam);
	ReleaseDC(pDC);

//	DrawImage(m_nSelectCam);
}

void CVisWebView::SetWarning(CString str)
{
	if((m_bAuto==FALSE && m_bRun==FALSE) || (m_bAuto<0 && m_bRun<0))		return;

	
	m_labelWarning.SetText(str);
	
	
//	log데이타로 저장하는 루틴 [날짜 일시 포함]
}


void CVisWebView::DrawHistoData(CDC *pDC)
{
	int i;
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CPoint p1,p2;
	int nSkip = 1;

	int nHeight = pDoc->m_pImage->GetHeight();

	for(i=0; i<pDoc->m_pImage->GetWidth(); i+=nSkip){
		p1.x = i;
		p2.x = i+nSkip;
		p1.y = int(nHeight - pDoc->m_data.m_nProjectX[m_nSelectCam][i]*nHeight/256);
		p2.y = int(nHeight - pDoc->m_data.m_nProjectX[m_nSelectCam][i+nSkip]*nHeight/256);
		DrawLine(pDC, p1, p2, COLOR_RED);
	}
	for(i=0; i<pDoc->m_pImage->GetWidth(); i+=nSkip){
		p1.x = i;
		p2.x = i+nSkip;
		p1.y = int(nHeight - pDoc->m_data.m_nProjectX[m_nSelectCam][i]*nHeight/256);
		p2.y = int(nHeight - pDoc->m_data.m_nProjectX[m_nSelectCam][i+nSkip]*nHeight/256);
		DrawLine(pDC, p1, p2, COLOR_YELLOW);
	}
}


void CVisWebView::GetHistoEqua()
{

}


void CVisWebView::FullImageProjection() 
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	unsigned char* fm = pDoc->m_pImage->GetImagePtr();
	int nCount = 1;
	int nw = pDoc->m_pImage->GetWidth();
	int nh = pDoc->m_pImage->GetHeight();
	int *nprojw = new int[nw];
	memset(nprojw,0,nw);
	pDoc->m_data.m_nEdgeAverage[0] = pDoc->m_data.m_nEdgeAverage[1] = 0;


	for(int y=0;y<nh;y++)
	{
		int ntmp = 0;
		for(int x=0;x<nw;x++){
			nprojw[x] +=*(fm+y*nw+x);
		}
	}
	for(int x=0;x<nw;x++)
		nprojw[x] /= nh;
	delete nprojw;
	//memcpy(pDoc->m_data.m_nProjectX,nprojw,nw);

}




void CVisWebView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	m_ev_rbutton_down.SetEvent();
	
	CFormView::OnRButtonDown(nFlags, point);
}
void CVisWebView::fnWriteResult(CString path,int nResult,CString strname,CString strmonth,int nCam) 
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	CStdioFile   file;
	CString filename;
	CString strtmp,str,strTitle,strpath;

//	strpath.Format("C:\\NEXTEYE\\MODEL\\%s",);
//	CreateDirectory(strpath,NULL);

//	filename.Format("c:\\work\\%s_%s_Result.txt",strname,strmonth);
	filename.Format("c:\\work\\Result.txt");
	Wait(1);
	if(nResult)	str = "OK";
	else		str = "NG";

	//<a title="" href="c:\0.bmp">c:\0.bmp</a>
	strtmp.Format("%s\t%2.2f\t%d\t%d\t%5.4f\t%5.4f\t%5.4f\t%s",path,
		pDoc->m_data.m_dAvgBrightness,
		pDoc->m_data.m_nMaxBrightness,
		pDoc->m_data.m_nMinBrightness,
		pDoc->m_data.m_dSize[0],
		pDoc->m_data.m_dSizeX[0],
		pDoc->m_data.m_dSizeY[0],
		str);

	if(!nResult){
		try{
			g_Mutex.Lock();                    // 뮤텍스를 잠근다.
			if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
			{		
				file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText);

				strTitle.Format("화일명\tAve\tMax\tMin\tSizeX\tSizeY\tResult");
				file.WriteString(strTitle);
				file.WriteString("\n");
				file.WriteString(strtmp);
				file.WriteString("\n");
			
				file.Close();
			}
			else
			{
				file.SeekToEnd();
				
				file.WriteString(strtmp);
				file.WriteString("\n");

				file.Close(); 
			}
			g_Mutex.Unlock();                
		}
		catch(CFileException)
		{
			//AfxMessageBox( "File Open failed" );
		}
		catch(...)
		{
			//AfxMessageBox( "File Open failed2~" );
		}
	}
}


void CVisWebView::OnCkAuto() 
{
	m_bAutoRun = !m_bAutoRun;	
}

void CVisWebView::OnCkSaveImage() 
{
	m_bImageSelect	= !m_bImageSelect;	
}

void CVisWebView::fnDispButton(int nIndex)
{		//index = 0 ready / 1=auto	/2=stop
	if(nIndex==0)
	{
		((CButton*)GetDlgItem(IDC_CHECK_AUTO))->EnableWindow(true);				//auto
		((CButton*)GetDlgItem(IDC_BUTTON_FRAME_RESET))->EnableWindow(true);		//reset
		((CButton*)GetDlgItem(IDC_BTN_INSPECT))->EnableWindow(true);			//inspect
		((CButton*)GetDlgItem(IDC_BTN_LOAD_IMG))->EnableWindow(true);			//load Image
		((CButton*)GetDlgItem(IDC_BT_IMG_TEST))->EnableWindow(true);			//test
		((CButton*)GetDlgItem(IDC_BTN_GET_PROFILE2))->EnableWindow(true);			//test
		((CButton*)GetDlgItem(IDC_BUTTON3))->EnableWindow(true);			//test
		//
	}
	else if(nIndex==1)	
	{
		((CButton*)GetDlgItem(IDC_CHECK_AUTO))->EnableWindow(true);				//auto
		((CButton*)GetDlgItem(IDC_BUTTON_FRAME_RESET))->EnableWindow(false);		//reset
		((CButton*)GetDlgItem(IDC_BTN_INSPECT))->EnableWindow(false);			//inspect
		((CButton*)GetDlgItem(IDC_BTN_LOAD_IMG))->EnableWindow(false);			//load Image
		((CButton*)GetDlgItem(IDC_BT_IMG_TEST))->EnableWindow(false);			//test
		((CButton*)GetDlgItem(IDC_BTN_GET_PROFILE2))->EnableWindow(FALSE);			//test
		((CButton*)GetDlgItem(IDC_BUTTON3))->EnableWindow(FALSE);			//test
	}
	else if(nIndex==6)
	{
		((CButton*)GetDlgItem(IDC_CHECK_AUTO))->EnableWindow(true);				//auto
		((CButton*)GetDlgItem(IDC_BUTTON_FRAME_RESET))->EnableWindow(true);	//reset
		((CButton*)GetDlgItem(IDC_BTN_INSPECT))->EnableWindow(true);			//inspect
		((CButton*)GetDlgItem(IDC_BTN_LOAD_IMG))->EnableWindow(true);			//load Image
		((CButton*)GetDlgItem(IDC_BT_IMG_TEST))->EnableWindow(true);			//test
	}	
}



void CVisWebView::CreateDefaultDirectory()
{
	CString path;
	path =  "c:\\Glim\\";
	CreateDirectory(path,NULL);
	path =  "c:\\Glim\\LOTdata\\";
	CreateDirectory(path,NULL);
	path =  "c:\\Glim\\Image\\";
	CreateDirectory(path,NULL);
	path =  "c:\\Glim\\Gray\\";
	CreateDirectory(path,NULL);
	path =  "c:\\Glim\\Log\\";
	CreateDirectory(path,NULL);
	path.Format("C:\\Glim\\LotDataTmp\\");
	CreateDirectory(path,NULL);	
	path.Format("C:\\Glim\\Model\\");
	CreateDirectory(path,NULL);	

//	path =  "c:\\nexteye\\Model\\";
//	CreateDirectory(path,NULL);


	// parameter send & receive
	path.Format(_T("%s"), FOLDER_PATH_SERVER_PARAMETER);
	CreateDirectory(path, NULL);
	path.Format(_T("%s"), FOLDER_PATH_SERVER_INI_CHECK);
	CreateDirectory(path, NULL);
	path.Format(_T("%s"), FOLDER_PATH_SERVER_INI);
	CreateDirectory(path, NULL);

	//Alive
	CreateDirectory(_T("D:\\Data\\Alive"), NULL);
}

void CVisWebView::OnButtonUpdateNotinsarea() 
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	
	UpdateData(TRUE);
	pDoc->m_data.m_nDualNotIns = m_dXLineSkip;
	pDoc->m_data.m_dLineScratch = m_dLineScratch;

	pDoc->m_data.m_dDefectSize = m_dDefectSize;
	int N;
//m_nThWhite
// 	pDoc->m_data.m_nThWhite3 = m_nThWhite;
// 	pDoc->m_data.m_nThBlack3 = m_nThBlack;
	int nCam = m_nSelectCam;
	pDoc->m_data.m_nNotInsArea[nCam] = m_nNotInsAreaView;
	pDoc->m_data.m_nFindEdge[nCam] = m_nNotInsAreaView;
//	pDoc->m_data.m_dXlineSkip = m_dXLineSkip;
//	pDoc->m_data.m_nExposeTime = (m_nExpose*25);

	pDoc->m_data.m_nInsMethod[nCam] = m_nInsMethod;
	pDoc->m_data.m_nTacXpos[nCam] = m_nTacX;

	N=pDoc->m_data.m_nVisionLine;
	if(N != GL1 && N != GL8&& N != GL9)
	{
		for(int i=0;i<MAX_CAMERAS;i++){
			if(i==0)
				pDoc->m_pVision->SetExposureTime(i,m_nExpose*25,1);
			else
				pDoc->m_pVision->SetExposureTime(i,m_nExposre1*25,1);
		}
	}

	m_bDefectSaveStats = TRUE;

}

void CVisWebView::fnChangeLine(int nCam) 
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	int N;

	N=pDoc->m_data.m_nVisionLine;
	if(N == GL9)
	{
		//if(m_nExpose<100) m_nExpose = 100;
		//if(m_nExpose>2000) m_nExpose = 1200;

		//pDoc->m_pVision1[0]->SetAOI(0,m_nYLine,CAM_WIDTH,CAM_PATIAL);
		//pDoc->m_pVision1[0]->SetExpose(m_nExpose);
		//if(pDoc->m_data.m_strComName != "GL113")
		//{
		//	if(m_nMachine==0 && pDoc->m_data.m_strComName == "GL108"){}
		//	else{
		//		pDoc->m_pVision1[1]->SetAOI(0,m_nYLine1,CAM_WIDTH,CAM_PATIAL);
		//		pDoc->m_pVision1[1]->SetExpose(m_nExposre1);
		//	}
		//}
//		SetChgLine(m_nYLine);
//		SetGiGaLanExposure(m_nExpose);
//		SetFrameRate(m_nTacX);
	}
}


void CVisWebView::fnWriteMura(int bresult,double dave, int nmura, int nyoko) 
{
//	CStdioFile   file;
//	CString filename;
//	CString strtmp,str,strTitle,strpath,strOkNg;
//
////////////////
//	CString data[6];
//
//	CTime timer=CTime::GetCurrentTime();
//		
//	data[0].Format("%d", timer.GetYear());
//	if(timer.GetMonth() < 10)
//		data[1].Format("0%d", timer.GetMonth());
//	else
//		data[1].Format("%d", timer.GetMonth());
//	if(timer.GetDay() < 10)
//		data[2].Format("0%d", timer.GetDay());
//	else
//		data[2].Format("%d", timer.GetDay());
//	if(timer.GetHour() < 10)
//		data[3].Format("0%d", timer.GetHour());
//	else
//		data[3].Format("%d", timer.GetHour());
//	if(timer.GetMinute() < 10)
//		data[4].Format("0%d", timer.GetMinute());
//	else
//		data[4].Format("%d", timer.GetMinute());
//	if(timer.GetSecond() < 10)
//		data[5].Format("0%d", timer.GetSecond());
//	else
//		data[5].Format("%d", timer.GetSecond());
//
//	if(bresult)					strOkNg.Format("OK");
//	else						strOkNg.Format("NG");
//
//
//	strpath.Format("C:\\Glim\\Mura\\");
//	CreateDirectory(strpath,NULL);
//
//	filename.Format("%s%s_%s_%s_Result.txt",strpath,data[0],data[1],data[2]);
//	
//	strtmp.Format("%s%s%s:%s%s%s\t%2.2f\t%d\t%d\t%s",
//		data[0],data[1],data[2],data[3],data[4],data[5],
//		dave,nmura,nyoko,strOkNg);
//
//	if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
//	{		
//		file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText);
//
//		strTitle.Format("년월일:시분초\tAve\tMURA\tYoko\tResult");
//		file.WriteString(strTitle);
//		file.WriteString("\n");
//		file.WriteString(strtmp);
//		file.WriteString("\n");
//	
//		file.Close();
//	}
//	else
//	{
//		file.SeekToEnd();
//		
//		file.WriteString(strtmp);
//		file.WriteString("\n");
//
//		file.Close(); 
//	}	
}

void CVisWebView::OnCkViewImage() 
{
//	UpdateData();	
//	Invalidate();
	UpdateData();
//	m_bViewImage = !m_bViewImage;
}

void CVisWebView::OnButtonExit() 
{
	if(AfxMessageBox("Exit This Program?",IDOK)==IDOK)
	{	
//		WriteModel();

		AfxGetMainWnd()->DestroyWindow();  //SendMessage(WM_CLOSE); 	
	}	
}

void CVisWebView::OnNetworkTest() 
{
	CVisWebDoc* pDoc = GetDocument();

// 	CFileDialog dlg(TRUE, _T("ini"), NULL, OFN_SHAREAWARE, _T("Model (*.ini)|*.ini||"));
// 	dlg.m_ofn.lpstrInitialDir = m_strModelPath;
// 	if(dlg.DoModal() == IDOK)
// 	{
// 		CString strModel = dlg.GetFileName();
// 		strModel.TrimRight(".ini");
// 		pDoc->m_data.m_strDefaultModel = strModel;
// 		UpdateTolIni(strModel);
// // 		m_strModel = strModel;
// // 		UpdateSetupIni(TRUE, strModel);
// // 		UpdateIniTabIns(strModel,TRUE);
// // 		UpdateIniWeldingIns(strModel,TRUE);
// // 		UpdateIniTapeIns(strModel,TRUE);
// // 		UpdateIniReverseIns(strModel,TRUE);
// // 		pDlg->ResetData();		
// 	}



// 	CString strmodel;
// 	strmodel.Format("Model:%s", pDoc->m_data.m_strDefaultModel);
// 	SetDlgItemText(IDC_NETWORK_TEST,strmodel);
// 	m_SysParam->m_lbModelNO.SetText(strmodel);
// 
// 	WriteModel();
//
	if(m_pModelDlg->IsWindowVisible()){
		m_pModelDlg->ShowWindow(SW_HIDE);
	}
	else{
		m_pModelDlg->GetDlgItem(IDC_BUTTON_REFRESH)->SetFocus();

		m_pModelDlg->ShowWindow(1);
	}




}

void CVisWebView::OnCkSim() 
{
	CVisWebDoc* pDoc = GetDocument();
	m_bSimmulation = !m_bSimmulation;
	pDoc->m_data.m_bSharpness[0] = m_bSimmulation;
}

void CVisWebView::OnCkLot() 
{
	m_bLotSave = !m_bLotSave;	
}

void CVisWebView::OnCkLotdel() 
{
	m_bLotDel = !m_bLotDel;	
}
void CVisWebView::SetResolution(int nWidth,int nHeight)
{
/*	DEVMODE     dv;
    BOOL        bRetVal = FALSE;
    DWORD       iMode = 0;

    int width, height, bits, freq;

    width=nWidth;
    height=nHeight;
    bits=32;
    freq=60;    

    do{
        bRetVal = ::EnumDisplaySettings(NULL, iMode, &dv);
        if( dv.dmPelsWidth == width && dv.dmPelsHeight == height && 
            dv.dmBitsPerPel == bits && dv.dmDisplayFrequency == freq ) break;
        iMode++;
	}while (bRetVal);

    // 디스플레이 정보를 바꾼다.
    bRetVal = ::EnumDisplaySettings(NULL, iMode, &dv);

    if (bRetVal)
    {
        dv.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL | DM_DISPLAYFREQUENCY;
        ::ChangeDisplaySettings(&dv, 0);
    }
	*/
}

void CVisWebView::ChgExposure(int nCam)
{
	CVisWebDoc* pDoc = GetDocument();
	int ntmp =0;
//	int nshutter =1000;
	int tmp =0;

	if(pDoc->m_data.m_nVisionLine==3) tmp=6;
	else	tmp = 3;

	if(abs(int(pDoc->m_data.m_dStdBrightness[nCam]) - int(pDoc->m_data.m_dAvgBrightness[nCam]))>10)
	{
		ntmp = int((pDoc->m_data.m_dStdBrightness[nCam] - pDoc->m_data.m_dAvgBrightness[nCam])/tmp);
		//		80 - 100 = -20
		if(ntmp > 0)m_nExpose += ntmp*100;	
		else if(ntmp < 0) m_nExpose -= ntmp*100;	

		if(m_nExpose > 2400)	m_nExpose = 2400;
		if(pDoc->m_pVision)
			pDoc->m_pVision->SetExposureTime(nCam,m_nExpose*25,0);
	}	
}

void CVisWebView::fnWriteData(CString strlot,int frame,int defectcnt,int defectclass,float px, float py,float sx,float sy, CString imgpath,double dBcrY,double dRecieveY,double thup, double thdn,double dtmp1,int flag,int nCam) 
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	CStdioFile   file;
	CString filename;
	CString strtmp,str,strTitle,strpath,strOkNg,strpc;
	CString txtscr,txtdst;
	int nPcno =0;
	int nLine =0;
	//날자 LotNo. Frame	DefectCount	Defect-Class	x-Pos	Y-Pos	X-Size	Y-Size	ImagePath
	//////////////
	CString data[6];
	CTime timer=CTime::GetCurrentTime();

	data[0].Format("%d", timer.GetYear());
	if(timer.GetMonth() < 10)
		data[1].Format("0%d", timer.GetMonth());
	else
		data[1].Format("%d", timer.GetMonth());
	if(timer.GetDay() < 10)
		data[2].Format("0%d", timer.GetDay());
	else
		data[2].Format("%d", timer.GetDay());
	if(timer.GetHour() < 10)
		data[3].Format("0%d", timer.GetHour());
	else
		data[3].Format("%d", timer.GetHour());
	if(timer.GetMinute() < 10)
		data[4].Format("0%d", timer.GetMinute());
	else
		data[4].Format("%d", timer.GetMinute());
	if(timer.GetSecond() < 10)
		data[5].Format("0%d", timer.GetSecond());
	else
		data[5].Format("%d", timer.GetSecond());

	if(strlot=="")
		strlot = "NONE";
	//if(nCam == 0){//20150723 ljh
// 	if(pDoc->m_data.m_bUseCLog){
// 		strpath.Format("C:\\Glim\\Log\\");
// 		CreateDirectory(strpath,NULL);
// 		strpath.Format("C:\\Glim\\Log\\%s\\",strlot);
// 		CreateDirectory(strpath,NULL);
// 	}
//	else{
		strpath.Format("D:\\Data\\Log\\");
		CreateDirectory(strpath,NULL);
		strpath.Format("D:\\Data\\Log\\%s\\",strlot);
		CreateDirectory(strpath,NULL);
	//}
	//}

	if(flag == 0)
	{
		if(pDoc->m_data.m_nVisionLine<=GL9)
		{
			filename.Format("%s%s_Defect.txt",strpath,pDoc->m_data.m_strComName);
			strpc = pDoc->m_data.m_strCamName[nCam];//.Right(3);
		}
		else
		{

				filename.Format("%s%s_Defect.txt",strpath,pDoc->m_data.m_strComName);
			strpc = pDoc->m_data.m_strComName;//.Right(3);
		}
	}
	else
		filename.Format("%s%s_Mark.txt",strpath,pDoc->m_data.m_strComName);



	nLine = pDoc->m_data.m_nVisionLine;

	pDoc->m_data.m_dStartPos[nCam] = pDoc->m_data.m_dEndPos[nCam] = 0;

	//	else
	//20161111 원본
	//strtmp.Format("%s%s%s%s%s%s\t%s\t%d\t%s\t%2.2f\t%d\t%d\t%2.2f\t%2.2f\t%2.2f\t%2.2f\t%s\t%2.2f\t%2.2f\t%2.2f\t%2.2f\t%2.2f",
	strtmp.Format("%s%s%s%s%s%s\t%s\t%d\t%s\t%2.2f\t%d\t%d\t%2.2f\t%2.2f\t%2.3f\t%2.3f\t%s\t%2.2f\t%2.2f\t%2.2f\t%2.2f\t%2.2f",
		data[0],data[1],data[2],data[3],data[4],data[5],
		pDoc->m_str_lot,
		frame,strpc,pDoc->m_data.m_dStartPos[nCam],defectcnt,defectclass,
		px,py,sx,sy,imgpath,dBcrY,dRecieveY,thup,thdn,dtmp1);
	//	strtmp.Format("%s%s%s:%s%s%s\t
	//	%s\t	pDoc->m_str_lot,
	//	%d\t	frame
	//	%d\t	pDoc->m_data.m_dRollsize
	//	%2.2f\t	pDoc->m_data.m_dStartPos
	//%d\t	defectcnt
	//%d\t	defectclass
	//%2.2f\t	ppx
	//%2.2f\t	py
	//%2.2f\t	sx
	//%2.2f\t	sy
	//%s\t		imgpath
	//%2.2f\t	bcry
	//%2.2f\t	re
	//%2.2f\t//	thup
	//%2.2f\t	thdn
	//%2.2f",	tmp

	//	협폭 1, 광폭 : 2  //  X Offset : Default 0 ; NEL 1||2  nel 14||nel15
	try{
		g_Mutex.Lock();                    // 뮤텍스를 잠근다.

		if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
		{		
			if(file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText))
			{
				file.WriteString(strtmp);
				file.Close();
			}
			else
			{
			}
		}
		else
		{
			file.SeekToEnd();
			file.WriteString("\n");
			file.WriteString(strtmp);
			file.Close(); 
		}

		g_Mutex.Unlock();                 // 뮤텍스를 풀어준다.
	}
	catch(CFileException)
	{
		g_Mutex.Unlock();                 // 뮤텍스를 풀어준다.
		//AfxMessageBox( "File Open failed" );
	}
	catch(...)
	{
		g_Mutex.Unlock();                 // 뮤텍스를 풀어준다.
		//AfxMessageBox( "File Open failed2~" );
	}
 }

 void CVisWebView::fnWriteEndFile(CString name,int nCam)
 {
	 if(((CVisWebApp*)AfxGetApp())->m_debugLogWrite == TRUE){
		((CVisWebApp*)AfxGetApp())->WriteLog(PATH_DEBUG_LOG, "debug_log", "fnWriteEndFile");
	 }
	
	 CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	 CStdioFile   file;
	 CString filename;
	 CString strtmp,str,strTitle,strpath;
	 CTime ttime = CTime::GetCurrentTime();
	 CString kk = ttime.Format("%Y_%m_%d");
	 CString strTime = ttime.Format("[%Y %m %d %H:%M:%S]");
	 CString strpathtime = ttime.Format("%Y_%m_Packet");
	 strpath.Format("c:\\Glim\\Log\\%s",strpathtime);
	 CreateDirectory(strpath,NULL);

	 filename.Format("%s\\%s_Packet.txt",strpath,ConvertCharToStr(cLotID));
	 
	 //밝기 20이상차이나느것의 갯수 카운트
	 strtmp.Format("%s , %s , %s ,   %d ,  %s",
		 strTime,pDoc->m_data.m_strComName,ConvertCharToStr(cLotID),g_frame_num,name);
	 try{
		 g_Mutex.Lock();                    // 뮤텍스를 잠근다.

		 if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
		 {		
			 file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText);
			 file.WriteString(strtmp);
			 file.WriteString("\n");	
			 file.Close();
		 }
		 else
		 {
			 file.SeekToEnd();			
			 file.WriteString(strtmp);
			 file.WriteString("\n");
			 file.Close(); 
		 }
		 g_Mutex.Unlock();                 // 뮤텍스를 풀어준다.
	 }
	 catch(CFileException)
	 {
		 //AfxMessageBox( "File Open failed" );
		 g_Mutex.Unlock();                 // 뮤텍스를 풀어준다.
	 }
	 catch(...)
	 {
		 //AfxMessageBox( "File Open failed2~" );
		 g_Mutex.Unlock();                 // 뮤텍스를 풀어준다.
	 }
	 if(((CVisWebApp*)AfxGetApp())->m_debugLogWrite == TRUE){
		 ((CVisWebApp*)AfxGetApp())->WriteLog(PATH_DEBUG_LOG, "debug_log", "fnWriteEndFile-end");
	 }
 }

void CVisWebView::OnButton2() 
{
	SendMessage(WM_SHUTTER,0,0);
//	SendMessage(WM_RESTART,0,0);
}

void CVisWebView::CopyTextFile(CString src,CString dst,int Status)
{	
/*	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CString Command,SrcFolder,DstFolder;

//	DstFolder.Format("\\\\fileserver\\NEXTEYE\\CTRL_SERVER\\LOT_DATA_TEXT\\%s\\"
//		,pDoc->m_str_lot);
///	DstFolder.Format("c:\\NEXTEYE\\Backup\\");
	Command.Format("md %s",DstFolder);
//	DstFolder.Format("c:\\NEXTEYE\\Backup\\LOT_DATA_TEXT\\");
//	Command.Format("md %s",DstFolder);
//	DstFolder.Format("c:\\NEXTEYE\\Backup\\LOT_DATA_TEXT\\%s\\",pDoc->m_str_lot);
//	Command.Format("md %s",DstFolder);

	system(Command);
//Status

	if(Status ==1){
		Command.Format("copy %s %s",src,dst);
		system(Command);
		Command.Format("copy %s %s",m_strEnd,dst);
		system(Command);
	}
	else
	{	
		Command.Format("copy %s %s",src,dst);

		system(Command);

		if(m_nTextcopy){
			Command.Format("copy %s %s",m_strEnd,dst);
			system(Command);
			m_nTextcopy =0;
		}
	}
	*/
}

void CVisWebView::CopyEndTextFile(CString src,CString dst)
{	
/*	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CString Command,SrcFolder,DstFolder;

	m_strEnd.Format("C:\\Glim\\Log\\%s\\",pDoc->m_str_lot);

	DstFolder.Format("\\\\fileserver\\Glim\\CTRL_SERVER\\LOT_DATA_TEXT\\%s\\"
		,pDoc->m_str_lot);
	//\\fileserver\nexteye\CTRL_SERVER\LOT_DATA_TEXT\LOT_NAME
	
	Command.Format("md %s",DstFolder);

	system(Command);

	Command.Format("copy %s*.txt %s",m_strEnd,DstFolder);

	system(Command);
*/

}

void CVisWebView::OnButton3() 
{
	//CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	//pDoc->m_pVision1[0]->Grab();
	//
	//pDoc->m_pVision1[0]->SetMode(MODE_SOFTTRIGGER);
	//pDoc->m_pVision1[0]->SoftTriggerSend();
	//Wait(70);
	//pDoc->m_pVision1[0]->SetMode(MODE_HARDTRIGGER);
	//
	//pDoc->m_pVision1[0]->Stop();
	
	/*
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	capture();*/
	//m_nCkTape = 1;
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
//	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	g_frame_num++;
	Inspect(1);

	return;

	//Calibration Data Get
	m_eSaveImageCam2.SetEvent();
	m_eSaveImage.SetEvent();


//	GetCaliData( 0, 0);//


//	SendMarkingDataTest(0);
	
	//GrabImgSaveCam2(0);
//	m_autoEncoder = !m_autoEncoder;
}
void CVisWebView::GetCaliData(int  nCam,int  nMode)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	if(nMode==0){//Printing Mode
		//Projection
		double dProjw[CAM_WIDTH_CIS];
		int nPosx[CAM_WIDTH_CIS];
		int nPosx1[CAM_WIDTH_CIS];
		double dPos[4000];
		double dsum=0;
		for(int x=0;x<CAM_WIDTH_CIS;x++){
			dProjw[x] = 0;
			nPosx[x] = nPosx1[x]= 0;
			if(x<4000)dPos[x] = 0;
		}
	
		BYTE * fm = pDoc->m_pImage->GetImagePtr();
		for(int y=0;y<CAM_HEIGHT_CIS;y++){
			for(int x=0;x<CAM_WIDTH_CIS;x++){
				dProjw[x] += *(fm+y*CAM_WIDTH_CIS+x);
				dsum +=  *(fm+y*CAM_WIDTH_CIS+x);
			}
		}
		for(int x=0;x<CAM_WIDTH_CIS;x++){
			dProjw[x] /=CAM_HEIGHT_CIS; 
		}
		dsum /= (CAM_WIDTH_CIS*CAM_HEIGHT_CIS);
		//검은 선을 에지를 찾고
		int nTh = dsum*0.6; //절대 값에 의한 검출은 안됨.
		// x2-x0 차이값이 일정값 이상일때 에지로 인식하게 수정.
		CString strpath,strname,strdata;
		strpath.Format("c:\\Glim\\Log\\");
		strname.Format("CalData");
		for(int x=0;x<CAM_WIDTH_CIS;x++){
			if(dProjw[x] > nTh)nPosx[x] = 1;
		}

		int nstart = 0,nend=0,ncount=0;
		for(int x=1;x<CAM_WIDTH_CIS;x++){
			if(nPosx[x] == 0 && nPosx[x-1] == 1 )nstart = x;
			if(nPosx[x] == 1 && nPosx[x-1] == 0 && nstart>0)nend = x;

			if(nstart >0 && nend>0){
				dPos[ncount] = (nstart+nend)*0.5;
				strdata.Format("%d  %.1f  %d  %d",ncount,dPos[ncount],nstart,nend);
				m_Inspect.WriteLogIns(strpath,strname,strdata);
				ncount++;
				nstart = 0;nend = 0;
			}
		}

		nTh = nTh;

		//검은선을 중심을 구하고

		// 1mm 단위 or 10mm 단위 Pixel 별 Pos Data 입력.
	}
	else{//Laser Mode

	}
}


void CVisWebView::fnWriteSlice(int n,int nc,int nCam)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	CTime ttime = CTime::GetCurrentTime();
	CString kk = ttime.Format("[%H-%M-%S]");

	CStdioFile   file;
	CString filename;
	CString strpath;
	CString str;

	strpath.Format("C:\\Glim\\");
	filename.Format("%sSlice_%s.txt",strpath,pDoc->m_data.m_strComName);
	str.Format("%s\t%s\tSplice : %d, frame : %d",pDoc->m_data.m_strComName,kk,nc,n);
	try{
		g_Mutex.Lock();                    // 뮤텍스를 잠근다.

		if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
		{		
			if(file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText))
			{
				file.WriteString(str);	
				file.Close();
			}
		}
		else
		{
			file.SeekToEnd();
			file.WriteString("\n");
			file.WriteString(str);
			file.Close(); 
		}	
		 g_Mutex.Unlock();                 // 뮤텍스를 풀어준다.
	}
	catch(CFileException)
	{
		//AfxMessageBox( "File Open failed" );
	}
	catch(...)
	{
		//AfxMessageBox( "File Open failed2~" );
	}
}

void CVisWebView::fnWriteBrightness(CString strPC,int nBright,int nCam)
{
	CStdioFile   file;
	CString filename;
	CString strpath;
	CString str;

	strpath.Format("C:\\Glim\\Gray\\");
	filename.Format("%s%s.txt",strpath,strPC);
	str.Format("%d",nBright);
	try{
		g_Mutex.Lock();                    // 뮤텍스를 잠근다.

		if(file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText))
		{		
			file.WriteString(str);	
			file.Close();
		}
		 g_Mutex.Unlock();                 // 뮤텍스를 풀어준다.
	}
	catch(CFileException)
	{
		//AfxMessageBox( "File Open failed" );
	}
	catch(...)
	{
		//AfxMessageBox( "File Open failed2~" );
	}
}

void CVisWebView::OnBinaryView() 
{
	// TODO: Add your control notification handler code here
//	m_bBinaryView = !m_bBinaryView;	
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	UpdateData();
	if(pDoc->m_data.m_strMachineName.Find("CT02")>=0)
		m_imageSaveExt = m_bBinaryView;

}

void CVisWebView::fnWriteReceive(double dval,CString strReceive)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	CTime ttime = CTime::GetCurrentTime();
	CString kk = ttime.Format("[%H-%M-%S]");
	CString kk1 = ttime.Format("%Y_%m_%d");//ttime.Format("%H_%M_%S");
	
	CStdioFile   file;
	CString filename;
	CString strpath;
	CString str;

	strpath.Format("C:\\Glim\\Log\\");
	CreateDirectory(strpath,NULL);	

	if(dval == 0.0)
		filename.Format("%s%s_%s_packdata.txt",strpath,pDoc->m_data.m_strComName,kk1);
	else 
		filename.Format("%s%s_%s_Receive_%s.txt",strpath,pDoc->m_data.m_strComName,kk1,ConvertCharToStr(cLotID));

	if(strReceive=="0")
	{
		filename.Format("%s%s_%s_PolMoving.txt",strpath,pDoc->m_data.m_strComName,kk1,ConvertCharToStr(cLotID));
		str.Format("%s\t%s\t%d\t%f\t%s",pDoc->m_data.m_strComName,kk,g_frame_num,dval,strReceive);
	}
	else
		str.Format("%s\t%s\t%d\t%d\t%s",pDoc->m_data.m_strComName,kk,g_frame_num,m_nMilGrabCount,strReceive);

	try{
		g_Mutex.Lock();                    // 뮤텍스를 잠근다.

		if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
		{		
			if(file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText))
			{
				file.WriteString(str);	
				file.Close();
			}
		}
		else
		{
			file.SeekToEnd();
			file.WriteString("\n");
			file.WriteString(str);
			file.Close(); 
		}	
		g_Mutex.Unlock();                 // 뮤텍스를 풀어준다.
	}
	catch(CFileException)
	{
		//AfxMessageBox( "File Open failed" );
	}
	catch(...)
	{
		//AfxMessageBox( "File Open failed2~" );
	}

}

void CVisWebView::fnWritePacket(double dval,CString strReceive,CString strpack,int nCam)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	CTime ttime = CTime::GetCurrentTime();
	CString kk = ttime.Format("[%H-%M-%S]");

	CStdioFile   file;
	CString filename;
	CString strpath;
	CString str;

	strpath.Format("C:\\Glim\\Log\\");
	CreateDirectory(strpath,NULL);	
	filename.Format("%s%s_Receive_Pack_%s.txt",strpath,pDoc->m_data.m_strComName,ConvertCharToStr(cLotID));
	str.Format("%s\t%s\t%d - %s\t%.2f\t%s - %s",pDoc->m_data.m_strComName,kk,g_frame_num,strReceive.Mid(2,6),dval,strReceive,str);

	try{
		g_Mutex.Lock();                    // 뮤텍스를 잠근다.
		if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
		{		
			if(file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText))
			{
				file.WriteString(str);	
				file.Close();
			}
		}
		else
		{
			file.SeekToEnd();
			file.WriteString("\n");
			file.WriteString(str);
			file.Close(); 
		}	
		g_Mutex.Unlock();                 // 뮤텍스를 풀어준다.
	}
	catch(CFileException)
	{
		//AfxMessageBox( "File Open failed" );
	}
	catch(...)
	{
		//AfxMessageBox( "File Open failed2~" );
	}

}

int CVisWebView::fnPullData(int nframe,int nCam)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	CString str;
	int i=0;
	int ntmp,ntmp1;
// 	for(i=0;i<PD_FRAME*PD_LEN;i++)
// 	{
// 		if(pDoc->m_data.m_pPacketData[nCam][i].Left(1) == "F")
// 		{
// 			//F_123456_EC71003-01_000123_1_1_distance
// 			//F_frame_bcr17자리_협광폭_Read여부_distance
// 			if(atoi(pDoc->m_data.m_pPacketData[nCam][i].Mid(2,6)) == nframe){
// 				pDoc->m_str_lot = pDoc->m_data.m_pPacketData[nCam][i].Mid(9,10);// : Lot 10자리
// 				pDoc->m_str_lot_Full = pDoc->m_data.m_pPacketData[nCam][i].Mid(9,17);// : Lot 10자리
// //				pDoc->m_str_lot_End = pDoc->m_str_lot_Full.Right(6);
// 				str = pDoc->m_data.m_pPacketData[nCam][i].Mid(27,1);//.Right(1);
// 				pDoc->m_data.m_nBcrRollSize[nCam] = atoi(str);// : 1협폭 3광폭
// 				ntmp = pDoc->m_data.m_pPacketData[nCam][i].GetLength();
// 				ntmp1 = pDoc->m_data.m_pPacketData[nCam][i].Find("D_",10);
// 				str = pDoc->m_data.m_pPacketData[nCam][i].Right(ntmp-ntmp1-2);
// 				pDoc->m_data.m_dCodeDistace[nCam] = atof(str);
// 				//초기화
// 				pDoc->m_data.m_pPacketData[nCam][i] = "0";
// 				SetWarning(pDoc->m_str_lot);
// 				return 1;	//09:00
// 			}
// 		}
// 	}
// 
	fnDataReset();
	
	return 0;
}

void CVisWebView::fnDataReset()
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

			//F_123456_EC71003-01_000123_1_1_distance
			//F_frame_bcr17자리_협광폭_Read여부_distance
//	pDoc->m_str_lot = "NONE";// : Lot 10자리
//	pDoc->m_str_lot_Full = "NONE";
//	pDoc->m_str_lot_End = "NONE";
	for(int n=0;n<MAX_CAMERAS;n++)
	{
		pDoc->m_data.m_nBcrRollSize[n] = 1;// : 1협폭 3광폭	
		pDoc->m_data.m_dCodeDistace[n] = 0.;
	}
	//초기화
//	SetWarning(ConvertCharToStr(cLotID));
}


void CVisWebView::OnCkView2() 
{
	// TODO: Add your control notification handler code here
	m_bViewTest = !m_bViewTest;	

//	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
//	pDoc->m_data.m_nProjection[m_nSelectCam] = !pDoc->m_data.m_nProjection[m_nSelectCam];
	
}
//200805 - 13
void CVisWebView::fnWriteResetFrame(int n,int nCam)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	CTime ttime = CTime::GetCurrentTime();
	CString kk = ttime.Format("%Y_%m_%d");//ttime.Format("%H_%M_%S");
	CString strTime = ttime.Format("[%Y %m %d %H:%M:%S]");
	CStdioFile   file;
	CString filename;
	CString strpath;
	CString str;

	strpath.Format("C:\\Glim\\Log\\");
	CreateDirectory(strpath,NULL);	
	strpath.Format("C:\\Glim\\Log\\%s\\",kk);
	CreateDirectory(strpath,NULL);	
	filename.Format("%sResetProgram_%s.txt",strpath,pDoc->m_data.m_strComName);
	if(n)
		str.Format("%s\t%s\tProgram On",pDoc->m_data.m_strComName,strTime);	
	else
		str.Format("%s\t%s\tProgram Start",pDoc->m_data.m_strComName,strTime);

	try{
		g_Mutex.Lock();                    // 뮤텍스를 잠근다.
		if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
		{		
			if(file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText))
			{
				file.WriteString(str);	
				file.Close();
			}
		}
		else
		{
			file.SeekToEnd();
			file.WriteString("\n");
			file.WriteString(str);
			file.Close(); 
		}	
		g_Mutex.Unlock();                 // 뮤텍스를 풀어준다.
	}
	catch(CFileException)
	{
		//AfxMessageBox( "File Open failed" );
	}
	catch(...)
	{
		//AfxMessageBox( "File Open failed2~" );
	}
}
void CVisWebView::fnReadSkipPixel(int nCam)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CStdioFile   file;
	CString filename;
	CString strpath;
	CString str;

	filename.Format("C:\\Glim\\SkipPixel.txt");
	int ncn[MAX_CAMERAS]={0,};

	if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
	{	
// 		pDoc->m_data.m_nIgnorePos[0] = 0;	//0805 - 15
// 		pDoc->m_data.m_nIgnoreRange = 0;	//0805 - 15
		for(int i=0;i<1000;i++){
			pDoc->m_data.m_nIgnorePixel[i] = 0;
			for(int k=0;k<3;k++)
				pDoc->m_data.m_nIgnorePixel1[k][i] = 0;
		}
	}
	else
	{
		for(int i=0;i<1000;i++){
			file.ReadString(str);	//Pixel
			if(str == "")
			{
				file.Close();
				return;
			}
			int nl = str.Find("_");
			int cam = atoi(str.Mid(3,1));
			int nl1 = str.GetLength();
			pDoc->m_data.m_nIgnorePixel1[cam][ncn[cam]] = atoi(str.Mid(nl+1,nl1-nl-1));
			ncn[cam]++;
			i = i;
		}
		file.Close(); 
	}	
}

void CVisWebView::fnReadSkipPixel1(CString name,int nCam)
{
	//CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	//CTime ttime = CTime::GetCurrentTime();
	//CString kk = ttime.Format("%Y_%m_%d");//ttime.Format("%H_%M_%S");
	//CString strTime = ttime.Format("[%Y %m %d %H:%M:%S]");
	//CStdioFile   file;
	//CString filename;
	//CString strpath;
	//CString str;

	//filename.Format("%s",name);

	//if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
	//{	
	//	pDoc->m_data.m_nIgnorePos = 0;	//0805 - 15
	//	pDoc->m_data.m_nIgnoreRange = 0;	//0805 - 15
	//}
	//else
	//{
	//	file.ReadString(str);	//Pixel
	//	pDoc->m_data.m_nIgnorePos = atoi(str);	//0805 - 15
	//	file.ReadString(str);	//range
	//	pDoc->m_data.m_nIgnoreRange = atoi(str);	//0805 - 15
	//	file.Close(); 
	//}	//m_dCalXPos
}



void CVisWebView::WriteAveParam(int nCam)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();


	CStdioFile   file;
	CString filename;
	CString strpath;
	CString str;

	strpath.Format("C:\\Glim\\");
	CreateDirectory(strpath,NULL);	
	filename.Format("%s%s_AverageParam.txt",strpath,pDoc->m_data.m_strComName);

	try{
		g_Mutex.Lock();                    // 뮤텍스를 잠근다.
		if(file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText))
		{		
			str.Format("%f",pDoc->m_data.m_dAveMaxDefectBright[nCam]);
			file.WriteString(str);	
			file.WriteString("\n");	
			str.Format("%f",pDoc->m_data.m_dAveMinDefectBright[nCam]);
			file.WriteString(str);	
			file.WriteString("\n");	
			str.Format("%f",pDoc->m_data.m_dAvePenValue[nCam]);
			file.WriteString(str);	

			file.Close();
		}	
		g_Mutex.Unlock();                 // 뮤텍스를 풀어준다.
	}
	catch(CFileException)
	{
		//AfxMessageBox( "File Open failed" );
	}
	catch(...)
	{
		//AfxMessageBox( "File Open failed2~" );
	}
}
//m_strDefaultModel
void CVisWebView::WriteModel()
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CStdioFile   file;
	CString filename;
	CString strpath;
	CString str;

	strpath.Format("C:\\Glim\\");
	CreateDirectory(strpath,NULL);	
	filename.Format("%sModel.txt",strpath);

	try{
		g_Mutex.Lock();                    // 뮤텍스를 잠근다.
		if(file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText))
		{		
			file.WriteString(pDoc->m_data.m_strDefaultModel);	

			file.Close();
		}	
		g_Mutex.Unlock();                 // 뮤텍스를 풀어준다.
	}
	catch(CFileException)
	{
		//AfxMessageBox( "File Open failed" );
	}
	catch(...)
	{
		//AfxMessageBox( "File Open failed2~" );
	}
}
void CVisWebView::ReaModel()
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CStdioFile   file;
	CString filename;
	CString strpath;
	CString str;

	strpath.Format("C:\\Glim\\");
	CreateDirectory(strpath,NULL);	
	filename.Format("%sModel.txt",strpath);

	try{
		g_Mutex.Lock();                    // 뮤텍스를 잠근다.
		if(file.Open(filename, CFile::modeReadWrite|CFile::typeText))
		{		
			file.ReadString(str);//pDoc->m_data.m_strDefaultModel);	
			if(str == "")str = "Default";
			pDoc->m_data.m_strDefaultModel = str;
			
			file.Close();
		}	
		g_Mutex.Unlock();                 // 뮤텍스를 풀어준다.
	}
	catch(CFileException)
	{
		//AfxMessageBox( "File Open failed" );
	}
	catch(...)
	{
		//AfxMessageBox( "File Open failed2~" );
	}
}
void CVisWebView::AdjustAveParam(int nCam)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
}

void CVisWebView::OnCkBlob() 
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	UpdateData();
//	m_bCrossBlobImg = !m_bCrossBlobImg;	 //m_bViewTest1

}

void CVisWebView::PushDefectCycle(double x,double y,int nCam)
{
	//log4cpp::Category& debugLog = ((CVisWebApp*)AfxGetApp())->logCppLog;
	//debugLog.debug("PushDefectCycle");
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	for(int i=0;i<CYCLELENGTH;i++){//10000;i++){
		if(pDoc->m_data.m_dCycleY[nCam][i] == 0)
		{
			pDoc->m_data.m_dCycleY[nCam][i] = y;
			pDoc->m_data.m_dCycleX[nCam][i] = x;
			break;
		}
	}
	//debugLog.debug("PushDefectCycle-end");
}

/*
파이	3.14
320	1004.8
300	942
210	659.4
160	502.4
150	471
140	439.6
117	367.38
98	307.72
*/

int CVisWebView::fnLGCheckFrame(CString strpacket,int nCam)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	//00000025	00000009	00000010	00000011	12345678
	//크로스투과 라미전반사 라미후반사 정투과 롯트

	int nPc = pDoc->m_data.m_nVisionLine;
	/*CString str1;
	str1.Format("%s", strpacket);
	WriteLog("c:\\glim\\log", "frame_check_Str", str1);*/
	
	
	int nWidth = pDoc->m_pImage->GetWidth();
	int nAreaMargin = 50;
	int nLineMargin = 5;
	int nN = 0;
	pDoc->m_data.m_nRcvEdge = atoi(strpacket.Left(8));
	pDoc->m_data.m_dCamWidth = pDoc->m_data.m_dCalibSttX[nCam]+(nWidth*pDoc->m_data.m_dScaleFactorX[nCam]);
	


//	pDoc->m_str_lot = strpacket.Right(8);
	pDoc->m_data.m_nRcvEdgeData[nCam] = atoi(strpacket.Left(8));	//EdgeData

	//if(nPc == GL9){
	//	nN = atoi(strpacket.Left(8));	//크로스
	//}
	//else if(nPc == GL2 || nPc == GL5){
	//	nN = atoi(strpacket.Mid(8,8));	//라미전반사
	//}
	//else if(nPc == GL3 || nPc == GL6){
	//	nN = atoi(strpacket.Mid(8*2,8));	//라미후반사
	//}
	//else if(nPc == GL6){
		nN = atoi(strpacket.Mid(8*2,8));	//coater mismatch
	//}
	//else if(nPc == GL5){
	//	nN = atoi(strpacket.Mid(8*4,8));	//정반사
	//}
	//else if(nPc == GL6){
	//	nN = atoi(strpacket.Mid(8*2,8));	//투과
	//}
	//else{
	//	nN = atoi(strpacket.Mid(8*3,8));	//투과
	//}

	CString strlot;
	strlot= strpacket.Right(8);
//	if(pDoc->m_str_lot == "" ||pDoc->m_str_lot == "NONE" )
//		pDoc->m_str_lot = pDoc->m_str_lot_Full=strlot;
	pDoc->m_data.m_tTimeCheckFrame[nCam]  = CTime::GetCurrentTime();
	pDoc->m_data.m_nTimeCheckFrame[nCam] = atoi(pDoc->m_data.m_tTimeCheckFrame[nCam].Format("%H%M%S"));
	CTimeSpan ts = pDoc->m_data.m_nTimeCheckFrame[nCam]-pDoc->m_data.m_nTimeCheckFrameOld[nCam];
	CTimeSpan ts1 = pDoc->m_data.m_nTimeCheckFrame[nCam]-pDoc->m_data.m_nLastSendTime[nCam];
	if(ts<ts1)
	{//현재 시간 - 이전 들어온 시간 > 현재시간 - 패킷전송시간.
		//Open -> Close
		capture();
		fnWriteReceive(0.0 ,strpacket);
		SendMessage(WM_RESTART,0,0);
		pDoc->m_nTotalIns[0]=pDoc->m_nTotalIns[1] = nN+1;
		
		return 1;

	}
	else
	{
		if(!m_bAuto){
			capture();
			AutoStart();
		}
		//m_log2.AddString("체크프레임3");
	/*	CString str;
		str.Format("%d", g_frame_num);
		WriteLog("c:\\glim\\log", "frame_debug", str);*/
		//Frame Count Change//

		if(nN > pDoc->m_nTotalIns[0] + nLineMargin && nPc != GL9 && nPc != GL8 && nN>10)		//라인스캔
		{
			pDoc->m_nTotalIns[0]=pDoc->m_nTotalIns[1] = nN+1;
			
			//WriteLog("c:\\glim\\log", "frame_debug", "frame5-1");
		}
		else if(nN < pDoc->m_nTotalIns[0] - nLineMargin && nPc != GL9 && nPc != GL8 && nN>10)		//라인스캔
		{
			pDoc->m_nTotalIns[0]=pDoc->m_nTotalIns[1] = nN+1;
			//WriteLog("c:\\glim\\log", "frame_debug", "frame5-4");
		}
		else if(nN < pDoc->m_nTotalIns[1] - nLineMargin && nPc != GL9 && nPc != GL8 && nN>10)		//라인스캔
		{
			pDoc->m_nTotalIns[0]=pDoc->m_nTotalIns[1] = nN+1;
			//WriteLog("c:\\glim\\log", "frame_debug", "frame5-4");
		}
		else if(nN < pDoc->m_nTotalIns[1] - nLineMargin && nPc != GL9 && nPc != GL8 && nN>10)		//라인스캔
		{
			pDoc->m_nTotalIns[0]=pDoc->m_nTotalIns[1] = nN+1;
			//WriteLog("c:\\glim\\log", "frame_debug", "frame5-4");
		}
	//str.Format("%d", g_frame_num);
			//WriteLog("c:\\glim\\log", "frame_debug", str);
		return 1;
	}

	return 1;
}

//MAX_CYCLE_COUNT
void CVisWebView::fnWriteEdge(int nLeft,int nRight,int nEdge,CString str11,int nCam) 
{
	if(((CVisWebApp*)AfxGetApp())->m_debugLogWrite == TRUE){
		((CVisWebApp*)AfxGetApp())->WriteLog(PATH_DEBUG_LOG, "debug_log", "fnWriteEdge");
	}
	
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	CStdioFile   file;
	CString filename;
	CString strtmp,str,strTitle,strpath;
	CTime ttime = CTime::GetCurrentTime();
	CString kk = ttime.Format("%Y_%m_%d");
	CString strTime = ttime.Format("[%Y %m %d %H:%M:%S]");
	CString strpathtime = ttime.Format("%Y_%m_Edge");

//	strpath.Format("c:\\Glim\\Log\\%s",strpathtime);
//	CreateDirectory(strpath,NULL);
	strpath.Format("C:\\Glim\\Log\\");
	CreateDirectory(strpath,NULL);
	strpath.Format("C:\\Glim\\Log\\%s\\",ConvertCharToStr(cLotID));
	CreateDirectory(strpath,NULL);
	//}

	filename.Format("%s%s_Edge.txt",strpath,pDoc->m_data.m_strComName);
//	strpc = pDoc->m_data.m_strComName;//.Right(3);


	double dEdge1 = nEdge*pDoc->m_data.m_dScaleFactorX[nCam]+pDoc->m_data.m_dCalibSttX[nCam];
	if(pDoc->m_data.m_nInspDirection[nCam] %2==1)
		dEdge1 = (pDoc->m_data.m_nCameraWidth-nEdge)*pDoc->m_data.m_dScaleFactorX[nCam]+pDoc->m_data.m_dCalibSttX[nCam];

//	filename.Format("%s\\%s_Edge_%d.txt",strpath,pDoc->m_str_lot,nCam);
	////////////////////////
	strtmp.Format("%s\t%s\t%s\t%d\t%.1f\tOs-Pixel : %d, Pos: %d , DS-Pixel:%d,Pos: %d = Edge: %d , STR = %s",
		strTime,pDoc->m_data.m_strComName,ConvertCharToStr(cLotID),g_frame_num,dEdge1,nLeft,1,nRight,1,nEdge,str11);

	try{
		g_Mutex.Lock();                    // 뮤텍스를 잠근다.
		if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
		{		
			file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText);
			file.WriteString(strtmp);
			file.WriteString("\n");	
			file.Close();
		}
		else
		{
			file.SeekToEnd();			
			file.WriteString(strtmp);
			file.WriteString("\n");
			file.Close(); 
		}	
		g_Mutex.Unlock();                 // 뮤텍스를 풀어준다.
	}
	catch(CFileException)
	{
		//AfxMessageBox( "File Open failed" );
		g_Mutex.Unlock();                 // 뮤텍스를 풀어준다.
	}
	catch(...)
	{
		//AfxMessageBox( "File Open failed2~" );
		g_Mutex.Unlock();                 // 뮤텍스를 풀어준다.
	}
	if(((CVisWebApp*)AfxGetApp())->m_debugLogWrite == TRUE){
		((CVisWebApp*)AfxGetApp())->WriteLog(PATH_DEBUG_LOG, "debug_log", "fnWriteEdge-end");
	}
}
void CVisWebView::fnchgExposure(int nCam) 
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	int	nPcNo = pDoc->m_data.GetVisionLine(nCam);
	int nshutter = m_nExpose;
	if(nCam==1)
		nshutter = m_nExposre1;
	if(nPcNo != GL1  && nPcNo != GL8 && nPcNo != GL9)
		pDoc->m_pVision->SetExposureTime(nCam,nshutter*25,0);

	if(nPcNo == GL9)
	{
//		m_nYLine = int(pDoc->m_data.m_nEdgeBright[nCam]);
		//pDoc->m_pVision1[0]->SetAOI(0,m_nYLine,CAM_WIDTH,CAM_PATIAL);
		//pDoc->m_pVision1[0]->SetExpose(m_nExpose);
		//if(pDoc->m_data.m_strComName != "GL113")
		//{
		//	if(m_nMachine==0 && pDoc->m_data.m_strComName == "GL108"){}
		//	else
		//	{
		//		pDoc->m_pVision1[1]->SetAOI(0,m_nYLine1,CAM_WIDTH,CAM_PATIAL);
		//		pDoc->m_pVision1[1]->SetExpose(m_nExposre1);
		//	}
		//}
//		SetGiGaLanExposure(m_nExpose);
//		SetChgLine(m_nYLine);
	}
}

void CVisWebView::fnTrebleSkip(int nCam) 
{
	//CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	//unsigned char* fm = pDoc->m_pImage->GetImagePtr();
	//int nSum= 0,nCount = 0,nAve = 0;
	//int i,j;
	//int nPitch = pDoc->m_pImage->GetWidth();
	//for(i=pDoc->m_data.m_rectIns[nCam].left; i<pDoc->m_data.m_rectIns[nCam].right; i+=8){
	//	for(j=pDoc->m_data.m_rectIns[nCam].top; j<pDoc->m_data.m_rectIns[nCam].bottom; j+=2){
	//		nSum += fm[j*nPitch+i];
	//		nCount++;
	//	}
	//	nAve= int(nSum/nCount);
	//	if(nAve<m_nLineValue[i])
	//	{
	//	}
	//}
}

void CVisWebView::fnRegLineValue(int nCam) 
{
	//CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	//unsigned char* fm = pDoc->m_pImage->GetImagePtr();
	//int nSum= 0,nCount = 0;
	//int i,j;
	//int nPitch = pDoc->m_pImage->GetWidth();
	//for(i=pDoc->m_data.m_rectIns[nCam].left; i<pDoc->m_data.m_rectIns[nCam].right; i++){
	//	for(j=pDoc->m_data.m_rectIns[nCam].top; j<pDoc->m_data.m_rectIns[nCam].bottom; j+=4){
	//		nSum += fm[j*nPitch+i];
	//		nCount++;
	//	}
	//	pDoc->m_data.m_nLineValue[nCam][i] = int(nSum/nCount);
	//	nSum = nCount=0;
	//	if(i >= 1024)
	//		i = i;
	//}
}


void CVisWebView::OnCkView3() 
{
//	m_bViewTest1 = !m_bViewTest1;
	UpdateData();

	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	pDoc->m_data.m_bDualNotIns = m_bViewTest1;

}

int	CVisWebView::fnCheckLine(double *tv,double *bv,int nCam) 
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	int ret = 0;
	///영상의 Height 찾기.
	int nHight = pDoc->m_pImage->GetHeight();
	int nw = pDoc->m_pImage->GetWidth();
	int nMod = 8;
	int nYpos = nHight/nMod;
	unsigned char* fm = pDoc->m_pImage->GetImagePtr();
	// 이음매 라인 2줄을 가져온다.
	//2줄중 밝기가 특정값 이상일 경우 Skip한다.
	int i,j,nsum1,nsum2,ncount,ntmp1,ntmp2,nc;
	double dsum1,dave1,dsum2,dave2,dgap;
	double dt[10],db[10];
	int nLimit = 87*2;
	double dLevel = 2.0;
	int nc1=0;
	CString str;
	nsum1 = nsum2=ncount = nc=0;dsum1 = dave1 = dave2=dsum2=0.0;
	for(i=0;i<10;i++)	dt[i] = db[i] = 0.0;
	for(j=nYpos;j<nHight;j+=nYpos)
	{
		dave1=dave2=0.;ncount = nsum1=nsum2=0;
		for(i=0;i<nw;i++)
		{
			ntmp1 = fm[i+nw*(j-1)]+fm[i+nw*(j-2)];
			ntmp2 = fm[i+nw*j]+fm[i+nw*(j+1)];
			if(ntmp1 > nLimit)
				ntmp1 = nLimit;
			if(ntmp2 > nLimit)
				ntmp2 = nLimit;
			nsum1 +=ntmp1;
			nsum2 +=ntmp2;
			ncount++;
		}
		//위가 밝으면 CamPosY 값 감소,아래가 밝으면 CamPosY값 증가.
		dave1 = double(nsum1/ncount/2);
		dave2 = double(nsum2/ncount/2);
		dgap = dave1-dave2;
		dt[nc1] = dave1;
		db[nc1] = dave2;
/*		if(dgap>=dLevel)//영상의 아래가 밝음. 
		{//CamPosY값 증가.
			m_nYLine = m_nYLine-10;
			str.Format("%f",dgap);
			SetWarning(str);
			SendMessage(WM_CAMYPOS,0,0);
			if(fabs(dave1-dave2)>dLevel*2)
				ret = 2;
			else
				ret = 1;
			break;
		}
		else if(dgap<=-dLevel)//영상의 위가 밝음.
		{//CamPosY 감소.
			m_nYLine = m_nYLine+10;
			str.Format("%f",dgap);
			SetWarning(str);
			SendMessage(WM_CAMYPOS,0,0);
			if(fabs(dave1-dave2)>dLevel*2)
				ret = 2;
			else
				ret = -1;
			break;
		}
		*/
		nc1++;
	}
	double dtmin,dbmin;
	dtmin=dbmin=0;
	for(i=0;i<nc1;i++)
	{
//		if(dtmin>dt[i]) dtmin = dt[i];
//		if(dbmin>dt[i]) dbmin = db[i];
		dtmin += dt[i];
		dbmin += db[i];
	}
	*tv = dtmin/nc1;
	*bv = dbmin/nc1;
	return ret;
}

void CVisWebView::fnWriteSplice(int frame,int framecnt, int tapecnt) 
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	CStdioFile   file;
	CString filename;
	CString strtmp,str,strTitle,strpath;
	CTime ttime = CTime::GetCurrentTime();
	CString kk = ttime.Format("%Y_%m_%d");
	CString strTime = ttime.Format("[%Y %m %d %H:%M:%S]");

	strpath.Format("c:\\Glim\\Splice\\");
	CreateDirectory(strpath,NULL);
	strpath.Format("c:\\Glim\\Splice\\%s\\",kk);
	CreateDirectory(strpath,NULL);
	filename.Format("%s%s.txt",strpath,ConvertCharToStr(cLotID));
	
	////////////////////////
	strtmp.Format("Frame : %d , FCnt : %d , TapeCnt : %d ",frame,framecnt,tapecnt);

	try{
		g_Mutex.Lock();                    // 뮤텍스를 잠근다.
		if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
		{		
			file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText);
			file.WriteString(strtmp);
			file.WriteString("\n");	
			file.Close();
		}
		else
		{
			file.SeekToEnd();			
			file.WriteString(strtmp);
			file.WriteString("\n");
			file.Close(); 
		}	
		g_Mutex.Unlock();                 // 뮤텍스를 풀어준다.
	}
	catch(CFileException)
	{
		//AfxMessageBox( "File Open failed" );
	}
	catch(...)
	{
		//AfxMessageBox( "File Open failed2~" );
	}
}

void CVisWebView::fnGetRealBrightness(int nCam) 
{
	if(((CVisWebApp*)AfxGetApp())->m_debugLogWrite == TRUE){
		((CVisWebApp*)AfxGetApp())->WriteLog(PATH_DEBUG_LOG, "debug_log", "fnGetRealBrightness");
	}
	
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CTimingProcess* timer = ((CVisWebApp*)AfxGetApp())->m_pTiming;
	timer->SetTimer(TIMING_IDX_INSP_TESTTIME);

	unsigned char* fmImg;
	unsigned char* fmMini;
	int nheight;
	int nwidth;
	BOOL halfSizeProcess = true;


	if(pDoc->m_data.m_nVisionLine==GL9)
	{
		if(nCam==0){
			/*fmImg =pDoc->m_pImageNG->GetImagePtr();
			fmMini =pDoc->m_pImageMini->GetImagePtr();*/
			fmImg =pDoc->m_pImageNGPtr;
			fmMini =pDoc->m_pImageMiniPtr;

			if(halfSizeProcess == TRUE){	//축소시 m_pImageMini 사이즈를 가져온다.
				/*nheight= pDoc->m_pImageMini->GetHeight();
				nwidth = pDoc->m_pImageMini->GetWidth();	*/
				nheight= pDoc->m_pImageMiniHeight;
				nwidth = pDoc->m_pImageMiniWidth;	
			}
			else{
			/*	nheight= pDoc->m_pImage->GetHeight();
				nwidth = pDoc->m_pImage->GetWidth();*/
				nheight= pDoc->m_pImageHeight;
				nwidth = pDoc->m_pImageWidth;
			}
		}
		else{
		/*	fmImg = pDoc->m_pImageNG1->GetImagePtr();
			fmMini =pDoc->m_pImageMini1->GetImagePtr();*/
			fmImg = pDoc->m_pImageNG1Ptr;
			fmMini =pDoc->m_pImageMini1Ptr;
			if(halfSizeProcess == TRUE){
				/*nheight= pDoc->m_pImageMini1->GetHeight();
				nwidth = pDoc->m_pImageMini1->GetWidth();	*/
				nheight= pDoc->m_pImageMini1Height;
				nwidth = pDoc->m_pImageMini1Width;
			}
			else{
				/*nheight= pDoc->m_pImage1->GetHeight();
				nwidth = pDoc->m_pImage1->GetWidth();*/
				nheight= pDoc->m_pImage1Height;
				nwidth = pDoc->m_pImage1Width;
			}	
		}
	}
	else{
		/*fmImg = pDoc->m_pImage->GetImagePtr();
		nheight= pDoc->m_pImage->GetHeight();
		nwidth = pDoc->m_pImage->GetWidth();*/
		fmImg = pDoc->m_pImagePtr;
		nheight= pDoc->m_pImageHeight;
		nwidth = pDoc->m_pImageWidth;

	}

	int i,j;
	int xskip,yskip;
	int nTemp = 0;
	int nCount1 = 0;
	int npcnt=0,npsum = 0;

	if(pDoc->m_data.m_nVisionLine==GL9){
		//속도개량 - ljh
		for(j=0; j<nheight*2; j+=2){
			for(i=0; i<nwidth*2; i+=2)
			{
				int n1,n2,n0;
				n0 = nwidth;
				n1 = j*0.5;
				n2 = i*0.5;
				nTemp += *(fmImg+nwidth*2*j+i);
				*(fmMini+n0*n1+n2) = *(fmImg+nwidth*2*j+i);
				nCount1++;

			}
		}
		//원소스
		/*	for(j=0; j<nheight*2; j++){
		for(i=0; i<nwidth*2; i++)
		{
		int n1,n2,n0;
		n0 = nwidth;
		n1 = j*0.5;
		n2 = i*0.5;
		nTemp += *(fmImg+nwidth*2*j+i);
		*(fmMini+n0*n1+n2) = *(fmImg+nwidth*2*j+i);
		nCount1++;

		}
		}*/
	}
	else
	{

		xskip=yskip=8;
		for(j=0; j<nheight; j++){
			for(i=0; i<nwidth; i++)
			{
				nTemp += fmImg[j*nwidth+i];
				nCount1++;
				//npcnt++;
				//npsum +=fm11[j*nwidth+i];
			}
			//nProj[j] = npsum/npcnt;
			//npcnt=npsum = 0;
		}
	}
	


	if(nCount1>0)
		pDoc->m_data.m_dRealBrightness[nCam] = double(nTemp/nCount1);
	else pDoc->m_data.m_dRealBrightness[nCam] = 0;
	//		pData->m_dAvgBrightness = GetAveValue(fm, pData->m_rectIns, m_nPitch,4, 4);

	if(((CVisWebApp*)AfxGetApp())->m_debugLogWrite == TRUE){
		((CVisWebApp*)AfxGetApp())->WriteLog(PATH_DEBUG_LOG, "debug_log", "fnGetRealBrightness-end");
	}
}


int CVisWebView::CheckCycle(double x,double y,int nCam)
{
	if(((CVisWebApp*)AfxGetApp())->m_debugLogWrite == TRUE){
		((CVisWebApp*)AfxGetApp())->WriteLog(PATH_DEBUG_LOG, "debug_log", "CheckCycle");
	}
	
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	int i,j;
	int nMargin = 20;	//주기체크시 +-오프셋. default 10->20 수정 ljh

	for(i=0;i<CYCLELENGTH;i++){//defectcount
		if(pDoc->m_data.m_dCycleY[nCam][i] < y-40000){
			pDoc->m_data.m_dCycleY[nCam][i] = 0;
			pDoc->m_data.m_dCycleX[nCam][i] = 0;
		}
	}
	
	for(i=0;i<CYCLELENGTH;i++){//defectcount
		if(pDoc->m_data.m_dCycleY[nCam][i] >1000){//초기 10m 무시.
			for(j=0;j<MAX_CYCLE_COUNT;j++){	//m_nDefaultCycle 롤파이규격
				if(y-(pDoc->m_data.m_nDefaultCycle[nCam][j]*PI)-nMargin <pDoc->m_data.m_dCycleY[nCam][i] && y-(pDoc->m_data.m_nDefaultCycle[nCam][j]*PI)+nMargin >pDoc->m_data.m_dCycleY[nCam][i]){
//				if(y-(pDoc->m_data.m_nDefaultCycle[j])-nMargin <pDoc->m_data.m_dCycleY[i] && y-(pDoc->m_data.m_nDefaultCycle[j])+nMargin >pDoc->m_data.m_dCycleY[i])
					if(x - pDoc->m_data.m_dCycleX[nCam][i]<5 && x - pDoc->m_data.m_dCycleX[nCam][i]>-5 ){
						if(pDoc->m_data.m_dLastCycle[nCam][j]+((pDoc->m_data.m_nDefaultCycle[nCam][j]*PI)*8) > y){
							pDoc->m_data.m_dLastCycle[nCam][j] = y;
							pDoc->m_data.m_nDefectFlag[nCam][j]++; 
							return pDoc->m_data.m_nDefaultCycle[nCam][j];
						}
						else{
							pDoc->m_data.m_dLastCycle[nCam][j] = y;
							pDoc->m_data.m_nDefectFlag[nCam][j] = 1; 
							return pDoc->m_data.m_nDefaultCycle[nCam][j];
						}
					}
				}
			}
		}
	}
	if(((CVisWebApp*)AfxGetApp())->m_debugLogWrite == TRUE){
		((CVisWebApp*)AfxGetApp())->WriteLog(PATH_DEBUG_LOG, "debug_log", "CheckCycle-end");
	}
	return 0;
}


void CVisWebView::OnBtnGetProfile() 
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();


//	CopyMismatchFile1();
	if(m_defectMap->IsWindowVisible()){//m_bMismatchView
 		m_defectMap->ShowWindow(SW_HIDE);
//		m_defectMap->KillTimer(20213);
		m_bMismatchView = FALSE;
	}
	else{
//		m_defectMap->m_bSim1 = TRUE;
 		m_defectMap->ShowWindow(SW_SHOW);
//		m_defectMap->SetTimer(20213,1000,NULL);//20213
		m_bMismatchView = TRUE;
	}
	// 	SetTimer(20219,500,NULL);
	// 	m_strAlarmMsg = "구간이물";
	// 	m_AlarmDlg->ShowWindow(1);
	// 	return;

}

void CVisWebView::fnWriteFrame(int f1,int f2) 
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	CStdioFile   file;
	CString filename;
	CString strtmp,str,strTitle,strpath;
	CTime ttime = CTime::GetCurrentTime();
	CString kk = ttime.Format("%Y_%m_%d");
	CString strTime = ttime.Format("[%Y %m %d %H:%M:%S]");

	strpath.Format("c:\\Glim\\Log\\");
	CreateDirectory(strpath,NULL);
	strpath.Format("c:\\Glim\\Log\\%s\\",kk);
	CreateDirectory(strpath,NULL);
	filename.Format("%s%s_Frame.txt",strpath,pDoc->m_data.m_strComName);
	
	////////////////////////
	strtmp.Format("%s %d - %d",strTime,f1,f2);

	try{
		g_Mutex.Lock();                    // 뮤텍스를 잠근다.
		if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
		{		
			file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText);
			file.WriteString(strtmp);
			file.WriteString("\n");	
			file.Close();
		}
		else
		{
			file.SeekToEnd();			
			file.WriteString(strtmp);
			file.WriteString("\n");
			file.Close(); 
		}	
		g_Mutex.Unlock();                 // 뮤텍스를 풀어준다.
	}
	catch(CFileException)
	{
		//AfxMessageBox( "File Open failed" );
	}
	catch(...)
	{
		//AfxMessageBox( "File Open failed2~" );
	}
}

void CVisWebView::capture()
{  
	return;
     CClientDC  dc(this); //dc생성
//     CRect rc(0,0,GetSystemMetrics(SM_CXMAXTRACK),GetSystemMetrics(SM_CYMAXTRACK)); 
//     CRect rc(0,0,FORM_IMG_WIDTH,FORM_IMG_HEIGHT); 
     CRect rc;
	 rc.SetRect(0,0,1024,768); //m_rtSaveRect;
     //전체화면 구역설정
//m_rtSaveRect
     CBitmap  captureBmp; 
     captureBmp.CreateCompatibleBitmap(&dc,  rc.Width(),  rc.Height()); 

     CDC  dcMem; 
     dcMem.CreateCompatibleDC(&dc); 
     CBitmap  *pOldBitmap  =  dcMem.SelectObject(&captureBmp); 

      //  복사한다. 
//     dcMem.BitBlt(0,0,rc.Width(),  rc.Height(),  &dc,  0,0,SRCCOPY); 
     dcMem.BitBlt(0,0,rc.Width(),  rc.Height(),  &dc,  rc.left,rc.top,SRCCOPY); 
     dcMem.SelectObject(pOldBitmap); 

     HANDLE hDIB = DDBToDIB(captureBmp, BI_RGB, NULL); // 이 함수들은 여기! bu.cpp
/////////////////////////////////////
	CString str;
	CTime ttime = CTime::GetCurrentTime();
	CString kk = ttime.Format("%H-%M-%S");
	CString kk1 = ttime.Format("%y%m%d");
	CString	kk2 = ttime.Format("%H");
	str.Format("c:\\Glim\\");
	CreateDirectory(str,NULL);
	str.Format("c:\\Glim\\Img\\");
	CreateDirectory(str,NULL);
	str.Format("c:\\Glim\\Img\\%s",kk1);
	CreateDirectory(str,NULL);
	str.Format("c:\\Glim\\Img\\%s\\%s",kk1,kk2);
	CreateDirectory(str,NULL);
	str.Format("c:\\Glim\\Img\\%s\\%s\\OverlayImage\\",kk1,kk2);
	CreateDirectory(str,NULL);
	str.Format("c:\\Glim\\Img\\%s\\%s\\OverlayImage\\%s_%d_Overlay.bmp",kk1,kk2,kk,g_frame_num);


////////////////////////////////////////////
	 if(hDIB != NULL && m_dRemainHDDSpace > 10)
     {
        WriteDIB(str, hDIB);
//		CloseHandle(hDIB);
		GlobalFree(hDIB);
     }
     captureBmp.DeleteObject();
}
void CVisWebView::capture1(CString strlot,int nMeter)
{  
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	if(m_dRemainHDDSpace <1) 
		return;

     CClientDC  dc(this); //dc생성
//     CRect rc(0,0,GetSystemMetrics(SM_CXMAXTRACK),GetSystemMetrics(SM_CYMAXTRACK)); 
//     CRect rc(0,0,FORM_IMG_WIDTH,FORM_IMG_HEIGHT); 
	 CRect rcMain,rcDest,rcDest1;
	 //Setdlgitem 해서 사이즈 8의 배수로 만들것
     CRect rc;
	 rc .SetRect(0,0,1920,1080); //m_rtSaveRect;
	 //
     //전체화면 구역설정
//m_rtSaveRect
     CBitmap  captureBmp; 
     captureBmp.CreateCompatibleBitmap(&dc,  rc.Width(),  rc.Height()); 

     CDC  dcMem; 
     dcMem.CreateCompatibleDC(&dc); 
     CBitmap  *pOldBitmap  =  dcMem.SelectObject(&captureBmp); 

      //  복사한다. 
//     dcMem.BitBlt(0,0,rc.Width(),  rc.Height(),  &dc,  0,0,SRCCOPY); 
     dcMem.BitBlt(0,0,rc.Width(),  rc.Height(),  &dc,  rc.left,rc.top,SRCCOPY); 
     dcMem.SelectObject(pOldBitmap); 

//     HANDLE hDIB = DDBToDIB(captureBmp, BI_RGB, NULL); // 이 함수들은 여기! bu.cpp

	 /////////////////////////////////////
	 ////0922
	 CString str;
	 CTime ttime = CTime::GetCurrentTime();
	CString kk = ttime.Format("%Y%m%d");
	CString kk2 = ttime.Format("%Y%m");
	CString kk3 = ttime.Format("%d");
	CString kk1 = ttime.Format("[%Y%m%d_%H%M%S]");
	CString kk4 = ttime.Format("%H%M%S");
	CString kk5 = ttime.Format("%H");

	//if(m_strTimePath == "")
	//	m_strTimePath.Format("C-%s",kk4);
	//년월	일	m_strModelName	m_strInspStartTime
	int nn=0;
	if(pDoc->m_data.m_strComName.Find("CHO")>=0)
		nn = 1;
	if(nn==1){
		str.Format("c:\\Data\\");
		CreateDirectory(str,NULL);
		str.Format("c:\\Data\\Capture\\");
		CreateDirectory(str,NULL);
		str.Format("c:\\Data\\Capture\\%s\\",kk);//년월일
		CreateDirectory(str,NULL);
		str.Format("c:\\Data\\Capture\\%s\\%s\\",kk,strlot);//lot
		CreateDirectory(str,NULL);
		str.Format("c:\\Data\\Capture\\%s\\%s\\%s_%dMismatch.bmp",kk,strlot,kk1,nMeter);//time
	}
	else{
		str.Format("d:\\Data\\");
		CreateDirectory(str,NULL);
		str.Format("d:\\Data\\Capture\\");
		CreateDirectory(str,NULL);
		str.Format("d:\\Data\\Capture\\%s\\",kk);//년월일
		CreateDirectory(str,NULL);
		str.Format("d:\\Data\\Capture\\%s\\%s\\",kk,strlot);//랏
		CreateDirectory(str,NULL);
		str.Format("d:\\Data\\Capture\\%s\\%s\\%s_%dMismatch.jpg",kk,strlot,kk1,nMeter);//time
	}

	ImageFormatPtr img = ImageFormat::create();
	//	img->loadAndSaveAs((HBITMAP)captureBmp, 0, L"jpg", L"c:\\test.jpg");

	wchar_t* pStr;
	//멀티 바이트 크기 계산 길이 반환
	int strSize = MultiByteToWideChar(CP_ACP, 0,str, -1, NULL, NULL);

	//wchar_t 메모리 할당
	pStr = new WCHAR[strSize];
	//형 변환
	MultiByteToWideChar(CP_ACP, 0,str, strlen(str)+1, pStr, strSize);

	img->loadAndSaveAs((HBITMAP)captureBmp, 0, L"jpg",pStr);
	delete pStr;
	DeleteObject(dcMem);
	captureBmp.DeleteObject();


// 	if(hDIB != NULL && m_dRemainHDDSpace > 10)
// 	{
// 		WriteDIB(str, hDIB);
// 		//		CloseHandle(hDIB);
// 		GlobalFree(hDIB);
// 	}
// 	captureBmp.DeleteObject();
}

HANDLE CVisWebView::DDBToDIB(CBitmap &bitmap, DWORD dwCompression, CPalette *pPal)
{
        BITMAP   bm;
        BITMAPINFOHEADER bi;
        LPBITMAPINFOHEADER  lpbi;
        DWORD   dwLen;
        HANDLE   hDIB;
        HANDLE   handle;
        HDC    hDC;
        HPALETTE  hPal;
 
 
        ASSERT( bitmap.GetSafeHandle() );
 
        // The function has no arg for bitfields
        if( dwCompression == BI_BITFIELDS )
         return NULL;
 
        // If a palette has not been supplied use defaul palette
        hPal = (HPALETTE) pPal->GetSafeHandle();
        if (hPal==NULL)
         hPal = (HPALETTE) GetStockObject(DEFAULT_PALETTE);
 
        // Get bitmap information
        bitmap.GetObject(sizeof(bm),(LPSTR)&bm);
 
        // Initialize the bitmapinfoheader
        bi.biSize  = sizeof(BITMAPINFOHEADER);
        bi.biWidth  = bm.bmWidth;
        bi.biHeight   = bm.bmHeight;
        bi.biPlanes   = 1;
        bi.biBitCount  = bm.bmPlanes * bm.bmBitsPixel;
        bi.biCompression = dwCompression;
        bi.biSizeImage  = 0;
        bi.biXPelsPerMeter = 0;
        bi.biYPelsPerMeter = 0;
        bi.biClrUsed  = 0;
        bi.biClrImportant = 0;
 
        // Compute the size of the  infoheader and the color table
        int nColors = (1 << bi.biBitCount);
        if( nColors > 256 )
         nColors = 0;
        dwLen  = bi.biSize + nColors * sizeof(RGBQUAD);
 
        // We need a device context to get the DIB from
        hDC = ::GetDC(NULL);
        hPal = SelectPalette(hDC,hPal,FALSE);
        RealizePalette(hDC);
 
        // Allocate enough memory to hold bitmapinfoheader and color table
        hDIB = GlobalAlloc(GMEM_FIXED,dwLen);
 
        if (!hDIB){
         SelectPalette(hDC,hPal,FALSE);
         ::ReleaseDC(NULL,hDC);
         return NULL;
        }
 
        lpbi = (LPBITMAPINFOHEADER)hDIB;
 
        *lpbi = bi;
 
        // Call GetDIBits with a NULL lpBits param, so the device driver 
        // will calculate the biSizeImage field 
        GetDIBits(hDC, (HBITMAP)bitmap.GetSafeHandle(), 0L, (DWORD)bi.biHeight,
          (LPBYTE)NULL, (LPBITMAPINFO)lpbi, (DWORD)DIB_RGB_COLORS);
 
        bi = *lpbi;
 
        // If the driver did not fill in the biSizeImage field, then compute it
        // Each scan line of the image is aligned on a DWORD (32bit) boundary
        if (bi.biSizeImage == 0){
         bi.biSizeImage = ((((bi.biWidth * bi.biBitCount) + 31) & ~31) / 8)
                * bi.biHeight;
 
         // If a compression scheme is used the result may infact be larger
         // Increase the size to account for this.
         if (dwCompression != BI_RGB)
          bi.biSizeImage = (bi.biSizeImage * 3) / 2;
        }
 
        // Realloc the buffer so that it can hold all the bits
        dwLen += bi.biSizeImage;
        if (handle = GlobalReAlloc(hDIB, dwLen, GMEM_MOVEABLE))
         hDIB = handle;
        else{
         GlobalFree(hDIB);
 
         // Reselect the original palette
         SelectPalette(hDC,hPal,FALSE);
         ::ReleaseDC(NULL,hDC);
         return NULL;
        }
 
        // Get the bitmap bits
        lpbi = (LPBITMAPINFOHEADER)hDIB;
 
        // FINALLY get the DIB
        BOOL bGotBits = GetDIBits( hDC, (HBITMAP)bitmap.GetSafeHandle(),
           0L,    // Start scan line
           (DWORD)bi.biHeight,  // # of scan lines
           (LPBYTE)lpbi    // address for bitmap bits
           + (bi.biSize + nColors * sizeof(RGBQUAD)),
           (LPBITMAPINFO)lpbi,  // address of bitmapinfo
           (DWORD)DIB_RGB_COLORS);  // Use RGB for color table
 
        if( !bGotBits )
        {
         GlobalFree(hDIB);
 
         SelectPalette(hDC,hPal,FALSE);
         ::ReleaseDC(NULL,hDC);
         return NULL;
        }
 
        SelectPalette(hDC,hPal,FALSE);
        ::ReleaseDC(NULL,hDC);
        return hDIB;
 
}
 
 bool CVisWebView::WriteDIB(CString szFile, HANDLE hDIB)
{
          BITMAPFILEHEADER    hdr;
          LPBITMAPINFOHEADER  lpbi;
 
           if(!hDIB)
                  return FALSE;
 
           CFile file;
		
		   g_Mutex.Lock();                    // 뮤텍스를 잠근다.
		   try{
			   if(!file.Open( szFile, CFile::modeWrite|CFile::modeCreate) )
					  return FALSE;
		   }
		   catch(CFileException)
		   {
			   //AfxMessageBox( "File Open failed" );
		   }
		   catch(...)
		   {
			   //AfxMessageBox( "File Open failed2~" );
		   }
           lpbi = (LPBITMAPINFOHEADER)hDIB;
           int nColors = 1 << lpbi->biBitCount;
 
           // Fill in the fields of the file header 
           hdr.bfType      = ((WORD) ('M' << 8) | 'B');    // is always "BM"
           hdr.bfSize      = GlobalSize (hDIB) + sizeof(hdr);
           hdr.bfReserved1 = 0;
           hdr.bfReserved2 = 0;
           hdr.bfOffBits   = (DWORD) (sizeof( hdr ) + lpbi->biSize + nColors * sizeof(RGBQUAD));
 
           // Write the file header 
           file.Write(&hdr, sizeof(hdr));
 
           // Write the DIB header and the bits 
           file.Write(lpbi, GlobalSize(hDIB));

		   g_Mutex.Unlock();                   
 
           return TRUE;	
}
 
 int CVisWebView::CopyMilImgForSlit(LPBYTE fmLeft,int nCam)//, LPBYTE fmRight)
 {
	 try{
		 if(nCam == 0){
			m_glabDoneCam0 = false;
		 }
		 else{
			m_glabDoneCam1 = false;
		 }
		 
		 int i,j =0;
		 CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
		 BOOL nRet = 1;
		 static int nc= 0;
		 static int nc1= 0;
		 int nheight = 0;
		 int nwidth = 0; 

		 unsigned char* fmImg;
		 unsigned char* fmNgImg;
		 unsigned char* fmImg1;
		 unsigned char* fmNgImg1;

		 unsigned char* fmDspImg;
		 unsigned char* fmDspImg1;

		 CString str1;
		 std::string buffAsStdStr;


		 if(nCam == 0){
			 nheight= pDoc->m_pImageHeight;//pDoc->m_pImage->GetHeight();
			 nwidth = pDoc->m_pImageWidth;//pDoc->m_pImage->GetWidth();
			 

			 fmImg = pDoc->m_pImagePtr;//pDoc->m_pImage->GetImagePtr();
			 fmNgImg = pDoc->m_pImageNGPtr;//pDoc->m_pImageNG->GetImagePtr();
			 fmDspImg = pDoc->m_pImageDspPtr;//pDoc->m_pImageDsp->GetImagePtr();

		 }
		 else{
			 nheight= pDoc->m_pImage1Height;//pDoc->m_pImage1->GetHeight();
			 nwidth = pDoc->m_pImage1Width;//pDoc->m_pImage1->GetWidth();
			 

			 fmImg1 = pDoc->m_pImage1Ptr;//pDoc->m_pImage1->GetImagePtr();
			 fmNgImg1 = pDoc->m_pImageNG1Ptr;//pDoc->m_pImageNG1->GetImagePtr();
			 fmDspImg1 = pDoc->m_pImageDsp1Ptr;//pDoc->m_pImageDsp1->GetImagePtr();

		 }
		 CTimingProcess* timer;
		 if(nCam == 0){
			timer = ((CVisWebApp*)AfxGetApp())->m_pTiming;
		 }
		 
		 int y=0,y1=0,yy1;
		 yy1 = (m_nGrabFrame[nCam]-1)%NUM_BUFFERS;

		 //m_nGrabFrame 1, 2, 3 순서로 들어옴
		 if( (m_nGrabFrame[nCam]-1)%NUM_BUFFERS==0)
			 y = 0;
		 else
			 y = CAM_PATIAL *yy1 ;

		 //y는 0, 1, 2 순서로 1,2 체인지
		 //if(y==1)
		 // y = 2;
		 //else if(y==2)
		 // y=1;
		 DWORD dwStart = 0;


		 if(pDoc->m_data.m_nInspDirection[nCam] == 2 ||pDoc->m_data.m_nInspDirection[nCam] == 3)// && pDoc->m_data.m_nMachine==1)
		 {//coating
			 /*dwStart = GetTickCount();
			 str1.Format("[%d]%s%d_%d", dwStart, "Grab_Cam_St_", nCam, yy1);
			 sprintf(buff, "[%d]%s%d_%d", dwStart, "Grab_Cam_St_", nCam, yy1);
			 buffAsStdStr = buff;
			 WriteLog("c:\\glim\\log\\", "grab_log", str1);*/
		     //root.error(buffAsStdStr);
		
			 j = y+CAM_PATIAL;
			 for(i=0;i<CAM_PATIAL;i++)
			 {//y1 = y+i;
				 //if(j%HEIGHT == 0) j = 0;
				 //npos = (i/CAM_PATIAL)+1;
				 //k = ((npos*CAM_PATIAL) - j)-1;
				 y1 = j-i;
				 if(nCam==0){
					 memcpy(fmDummy[nCam]+nwidth*y1, fmLeft+WIDTH*i, WIDTH);
					 m_glabDoneCam0 = true;
				 }
				 else{
					 memcpy(fmDummy[nCam]+nwidth*y1, fmLeft+WIDTH*i, WIDTH);
					 m_glabDoneCam1 = true;
				 }
			 }
			
			/* dwStart = GetTickCount();
			 str1.Format("[%d]%s%d_%d", dwStart, "Grab_Cam_End_", nCam, yy1);
			 sprintf(buff, "[%d]%s%d_%d", dwStart, "Grab_Cam_End_", nCam, yy1);
			 buffAsStdStr = buff;
			 WriteLog("c:\\glim\\log\\", "grab_log", str1);*/
			 //root.error(buffAsStdStr);
			
			
		 }
		 else{
			 for(i=0;i<CAM_PATIAL;i++){
				 y1 = y+i;
				 if(nCam==0){
					 memcpy(fmImg+nwidth*y1, fmLeft+WIDTH*i, WIDTH);
				 }
				 else{
					 memcpy(fmImg1+nwidth*y1, fmLeft+WIDTH*i, WIDTH);
				 }
			 }
		 }

		 if(pDoc->m_data.m_nMachine==1){
		 }
		 else {//1frame
			
			 if(nCam==0){
				 memcpy(fmNgImg,fmImg,WIDTH*CAM_PATIAL);
			 }
			 else{
				 memcpy(fmNgImg1,fmImg1,WIDTH*CAM_PATIAL);
			 }

		 }

		 nRet = 1;

		 int nf = 0;
		 if(NUM_BUFFERS>1)nf = 2;
		 if(nCam==0 && (m_nGrabFrame[nCam]-1)%NUM_BUFFERS==nf ){
			 if(nc%10==0 && nCam==0)
			 {
				 m_img_save_time = timer->GetTimer(TIMING_IDX_TEST_GRAB);
				 m_fFps = float(10000 / m_img_save_time);
				 timer->SetTimer(TIMING_IDX_TEST_GRAB);
			 }
			 /*dwStart = GetTickCount();
			 str1.Format("[%d]%s%d_%d", dwStart, "Grab_Copy_st_", nCam, yy1);
			 sprintf(buff, "[%d]%s%d_%d", dwStart, "Grab_Copy_st_", nCam, yy1);
			 buffAsStdStr = buff;
			 WriteLog("c:\\glim\\log\\", "grab_log", str1);*/
			 //root.error(buffAsStdStr);
			
			

			 memcpy(fmImg,fmDummy[nCam],WIDTH*CAM_PATIAL*NUM_BUFFERS);
			 memcpy(fmNgImg,fmImg,WIDTH*CAM_PATIAL*NUM_BUFFERS);

			/* dwStart = GetTickCount();
			 str1.Format("[%d]%s%d_%d", dwStart, "Grab_Copy_end_", nCam, yy1);
			 sprintf(buff, "[%d]%s%d_%d", dwStart, "Grab_Copy_end_", nCam, yy1);
			 buffAsStdStr = buff;
			 WriteLog("c:\\glim\\log\\", "grab_log", str1);*/
			 //root.error(buffAsStdStr);
			
			 m_glabDoneCam0 = true;
			
			 if(!m_bViewTest){
				 //memcpy(pDoc->m_pImageDsp->GetImagePtr(),pDoc->m_pImageNG->GetImagePtr(),pDoc->m_pImageNGWidth*pDoc->m_pImageNGHeight);
				 memcpy(pDoc->m_pImageDspPtr,pDoc->m_pImageNGPtr, pDoc->m_pImageNGWidth * pDoc->m_pImageNGHeight);
			 }
			 //m_ev_Inspect.SetEvent();
			

			 g_frame_num++;

			 nc++;
		 }
		 else if(nCam==1 && (m_nGrabFrame[nCam]-1)%NUM_BUFFERS==nf){
			/* dwStart = GetTickCount();
			 str1.Format("[%d]%s%d_%d", dwStart, "Grab_Copy_st_", nCam, yy1);
			 sprintf(buff, "[%d]%s%d_%d", dwStart, "Grab_Copy_st_", nCam, yy1);
			 buffAsStdStr = buff;
			 WriteLog("c:\\glim\\log\\", "grab_log", str1);*/
			 //root.error(buffAsStdStr);
			

			 memcpy(fmImg1,fmDummy[nCam],WIDTH*CAM_PATIAL*NUM_BUFFERS);
			 memcpy(fmNgImg1,fmImg1,WIDTH*CAM_PATIAL*NUM_BUFFERS);
			 
			/* dwStart = GetTickCount();
			 str1.Format("[%d]%s%d_%d", dwStart, "Grab_Copy_do_", nCam, yy1);
			 sprintf(buff, "[%d]%s%d_%d", dwStart, "Grab_Copy_do_", nCam, yy1);
			 buffAsStdStr = buff;
			 WriteLog("c:\\glim\\log\\", "grab_log", str1);*/
			 //root.error(buffAsStdStr);
			
			
			 m_glabDoneCam1 = true;

			 if(!m_bViewTest){
				 //memcpy(pDoc->m_pImageDsp1->GetImagePtr(),pDoc->m_pImageNG1->GetImagePtr(),pDoc->m_pImageNG1Width*pDoc->m_pImageNG1Height);
				 memcpy(pDoc->m_pImageDsp1Ptr, pDoc->m_pImageNG1Ptr, pDoc->m_pImageNG1Width * pDoc->m_pImageNG1Height);
			 }

			 //m_ev_Inspect1.SetEvent();
			
			 nc1++;
		 }
		 return nRet;
	}
	catch(...){
		if(nCam == 0){
			WriteLog("C:\\GLIM\\LOG\\", "exception_log","Slit Cam0 Exception \n");
		}
		else{
			WriteLog("C:\\GLIM\\LOG\\", "exception_log","Slit Cam1 Exception \n");
		}	
	}
	return 0;
 }


int CVisWebView::InitCam()
{

	//
//	CStdioFile   file;
//	CString filename;
//	CString strtmp, strpath;
//	CTime ttime = CTime::GetCurrentTime();
//	CString kk = ttime.Format("%Y_%m_%d");
//	CString strTime = ttime.Format("[%Y %m %d %H:%M:%S]");
//
//	strpath.Format("c:\\Glim\\Log\\");
//	CreateDirectory(strpath,NULL);
//	strpath.Format("c:\\Glim\\Log\\%s\\", "Debug");
//	CreateDirectory(strpath,NULL);
//	filename.Format("%sdebugLog.txt", strpath);
//
//
//	
//	//
//	CString str;
//	putenv("PYLON_GIGE_HEARTBEAT=3000");
//	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
//	int nret = 0;
//	for (int i = 0; i < MAX_CAMERAS; i++)
//	{
//		if(m_nMachine==0 && pDoc->m_data.m_strComName == "GL108" && i==1)
//			break;//대명
////		if(m_nMachine==1 && pDoc->m_data.m_strComName == "GL113" && i==1)
//		if(pDoc->m_data.m_strComName == "GL113" && i==1)
//			break;//대명
//		switch (i)
//		{
//		case 0:
//			pDoc->m_pVision1[i] = new CGigECamera("192.168.0.2", i);
//			break;
//
//		case 1:
//			pDoc->m_pVision1[i] = new CGigECamera("192.168.1.2", i);
//			break;
//
//		case 2:
//			pDoc->m_pVision1[i] = new CGigECamera("192.168.3.2", i);
//			break;
//
//		case 3:
//			pDoc->m_pVision1[i] = new CGigECamera("192.168.4.2", i);
//			break;
//
//		default:
//			break;
//		}
//
//		if (pDoc->m_pVision1[i] != NULL)
//		{
//			if (pDoc->m_pVision1[i]->Open() == true)
//			{
//				str.Format("%s %d 연결성공",strTime, i+1);
//				pDoc->m_pVision1[i]->SetAOI(0,0,CAM_WIDTH,CAM_PATIAL);
//				pDoc->m_pVision1[i]->InitGigE(this);
//				pDoc->m_pVision1[i]->SetMode(MODE_HARDTRIGGER);
//				//pDoc->m_pVision1[i]->SetMode(MODE_SOFTTRIGGER);
//				pDoc->m_pVision1[i]->SetExpose(600);//m_nExpose
//				nret ++;
//			}
//			else
//			{
//				str.Format("%s %d 연결실패",strTime, i+1);
//				delete pDoc->m_pVision1[i];
//				pDoc->m_pVision1[i] = NULL;
//				nret = 0;
//
//
//			}
//			
//			try{
//				g_Mutex.Lock();                    // 뮤텍스를 잠근다.
//				if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
//				{		
//					file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText);
//					file.WriteString(str);
//					file.WriteString("\n");	
//					file.Close();
//				}
//				else
//				{
//					file.SeekToEnd();			
//					file.WriteString(str);
//					file.WriteString("\n");
//					file.Close(); 
//				}	
//				g_Mutex.Unlock();                    
//			}
//			catch(CFileException)
//			{
//				//AfxMessageBox( "File Open failed" );
//			}
//
//			catch(...)
//			{
//				//AfxMessageBox( "File Open failed2~" );
//			}
////			AddtoList(str);
//		}
//	}

	//	if(m_Vision.InitCam(this,0,0,CAMERA_WIDTH,CAMERA_HEIGHT,0,m_pDlgSet->m_FormTab2->m_dShutter,0))
	////	if(m_Vision.InitCam(this))	//area용
	//	{
	//		m_strStats += ",카메라 정상";
	//		LabelStats(m_strStats,m_nStats);	
	//	}
	//	else
	//	{
	//		m_strStats += ",카메라 에러";
	//		m_nStats++;
	//		LabelStats(m_strStats,m_nStats);	
	//	}

	//20150626
	/*pDoc->m_pVision1[0]->Stop();
	pDoc->m_pVision1[0]->SetMode(MODE_SOFTTRIGGER);
	pDoc->m_pVision1[0]->Grab();
	pDoc->m_pVision1[1]->Stop();
	pDoc->m_pVision1[1]->SetMode(MODE_SOFTTRIGGER);
	pDoc->m_pVision1[1]->Grab();*/
	Wait(50);

	return 0;// nret;
}

int CVisWebView::InitIO()
{
	CString str;
	int nret = 0;
	for(int i=0;i<1;i++)
	{
		long Ret = m_IO[i].InitIO(this,i);

		if(Ret==0){
			str.Format(_T("I/O카드 이상"));
		}
		else
		{
			str.Format(_T("I/O카드 정상"));
			nret = 1;
		}
	}
	return nret;
}

void CVisWebView::OnBnClickedCheckCamchange()
{//m_bCamChange
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	UpdateData();
	m_nSelectCam = m_bCamChange;
	//if(pDoc->m_data.m_nVisionLine==GL9 && pDoc->m_pVision1[1] != NULL && m_bCamChange )
	//{
	//	m_nSelectCam = 1; 
	//}
	//else m_nSelectCam = 0;
//	UpdateData(FALSE);

}


void CVisWebView::OnBnClickedBtnImageSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


	SaveImage();
	//AfxMessageBox( "File Open failed" );
}

void CVisWebView::OnBnClickedCheckImageSaveAll()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	pDoc->m_data.m_bLineWrite = m_bImageSaveAll;
	//m_bImageSaveAll = !m_bImageSaveAll;
}

void CVisWebView::OnBnClickedButton4()
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	pDoc->m_pDlgInterface->LoadInsParam();
	pDoc->m_pDlgInterface->LoadSysParam();
	pDoc->m_pDlgInterface->	LoadLightParam();

	for(int i=0;i<MAX_CAMERAS;i++)
		ReadCalData(i);

	return;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_inspectCu1 = false;
	m_inspectCu2 = false;

	bool autoInsMode;

	m_autoPeriodInsPath1 = "F:\\20150318\\image\\102\\20150317BC01002\\cam0";
	m_autoPeriodInsPath2 = "F:\\20150318\\image\\102\\20150317BC01002\\cam1";
	
	autoInsMode = true;		//자동검사
	//autoInsMode = false;	//무한검사

	//20150706 ljh CImage Setting Expention
	


	UpdateData(true);
	if(autoInsMode == true){	//자동검사
		m_dialogCustom customDlg;
		if(customDlg.DoModal() == IDOK){
			m_autoInsPath = customDlg.m_autoInsPath;
			CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
			int nCam = 0;
			//1.이미지리스트 가져오기
			
			CString strFile;
			CString imageFolderPath1 = m_autoInsPath;
			CString imageFolderPath2 = "\\*.bmp";
			CFileFind finder;
			BOOL bRet;
			BOOL isFind = finder.FindFile(imageFolderPath1+imageFolderPath2);
			int imageListCount = 0;
			int imageCount = 5000;
			CString imageListContainer[5000];
			while (isFind){
				isFind = finder.FindNextFile();
				strFile = finder.GetFileName();
				if ( finder.IsDirectory() || finder.IsDots() )
					continue;
				else
				{
					strFile = finder.GetFileName();

					if(imageListCount < imageCount)	//횟수제한
						imageListContainer[imageListCount++] = strFile;
				}
			}

			for(int imageNo = 0; imageNo < imageListCount; imageNo++){
				CString imagePath;
				imagePath.Format("%s\\%s", imageFolderPath1,imageListContainer[imageNo]);

				/*if(imageNo == imageListCount-1){
					imageNo=0;
				}*/
				if(!pDoc->m_pImageNG->IsDataNull())	
					pDoc->m_pImageNG->Free();
				if(!pDoc->m_pImageDsp->IsDataNull())	
					pDoc->m_pImageDsp->Free();

				pDoc->m_pImage->Load(imagePath);
				pDoc->m_pImageNG->Load(imagePath);
				pDoc->m_pImageDsp->Load(imagePath);

				pDoc->m_pImageWidth = pDoc->m_pImage->GetWidth();
				pDoc->m_pImageBadWidth = pDoc->m_pImageBad->GetWidth();
				pDoc->m_pImageNGWidth = pDoc->m_pImageNG->GetWidth();	
				pDoc->m_pImageDspWidth = pDoc->m_pImageDsp->GetWidth();		
				pDoc->m_pImageHeight = pDoc->m_pImage->GetHeight();
				pDoc->m_pImageBadHeight = pDoc->m_pImageBad->GetHeight();
				pDoc->m_pImageNGHeight = pDoc->m_pImageNG->GetHeight();
				pDoc->m_pImageDspHeight = pDoc->m_pImageDsp->GetHeight();	
				pDoc->m_pImagePtr = pDoc->m_pImage->GetImagePtr();
				pDoc->m_pImageNGPtr = pDoc->m_pImageNG->GetImagePtr();
				pDoc->m_pImageDspPtr = pDoc->m_pImageDsp->GetImagePtr();

				if(pDoc->m_data.GetVisionLine(0)==GL9)
				{

					if(!pDoc->m_pImageNG1->IsDataNull())	
						pDoc->m_pImageNG1->Free();
					if(!pDoc->m_pImageDsp1->IsDataNull())	
						pDoc->m_pImageDsp1->Free();

					pDoc->m_pImage1->Load(imagePath);
					pDoc->m_pImageNG1->Load(imagePath);
					pDoc->m_pImageDsp1->Load(imagePath);
				}

				bRet = Inspect(0);

				if(bRet == 1){
					CString str = imagePath;
					CString defectImageFolder = imageFolderPath1+"\\OK";
					//디렉토리 생성 후 OK이미지 따로 저장
					CreateDirectory(defectImageFolder,NULL);
					pDoc->m_pImage->Save(defectImageFolder+"\\"+imageListContainer[imageNo]);	
				}
				else{
					CString str = imagePath;
					CString defectImageFolder = imageFolderPath1+"\\NG";
					//디렉토리 생성 후 NG이미지 따로 저장
					CreateDirectory(defectImageFolder,NULL);
					pDoc->m_pImage->Save(defectImageFolder+"\\"+imageListContainer[imageNo]);
				}
				//계속반복
				/*if(imageNo == imageListCount - 1){
					imageNo = 0;
				}*/
				
				//메모리해제
				pDoc->m_pImage->Free();
				pDoc->m_pImageNG->Free();
				pDoc->m_pImageDsp->Free();

				if(pDoc->m_data.GetVisionLine(0)==GL9){
					pDoc->m_pImage1->Free();
					pDoc->m_pImageNG1->Free();
					pDoc->m_pImageDsp1->Free();
				}
			}
			
		}
	}
	else{//무한검사
		//자동검사 스레드
//		AfxBeginThread(ThreadInspectCu1, this,THREAD_PRIORITY_NORMAL,0);
//		AfxBeginThread(ThreadInspectCu2, this,THREAD_PRIORITY_NORMAL,0);
//		m_inspectCu1 = true;
//		m_inspectCu2 = true;
	}


	//CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	//int nCam = 0;
	////1.이미지리스트 가져오기
	//CString strFile;
	//CString imageFolderPath1 = "D:\\샘플이미지\\102";
	//CString imageFolderPath2 = "\\*.bmp";
	//CFileFind finder;
	//BOOL bRet;
	//BOOL isFind = finder.FindFile(imageFolderPath1+imageFolderPath2);
	//int imageListCount = 0;
	//int imageCount = 5000;
	//CString imageListContainer[5000];
	//while (isFind)
	//{
	//	isFind = finder.FindNextFile();
	//	strFile = finder.GetFileName();
	//	if ( finder.IsDirectory() || finder.IsDots() )
	//		continue;
	//	else
	//	{
	//		strFile = finder.GetFileName();

	//		if(imageListCount < imageCount)	//횟수제한
	//			imageListContainer[imageListCount++] = strFile;
	//	}
	//}

	//while(1){
	//for(int imageNo = 0; imageNo < imageListCount; imageNo++){	//10장씩 offset
	//	CString imagePath;
	//	imagePath.Format("%s\\%s", imageFolderPath1,imageListContainer[imageNo]);
	//	//pDoc->m_pImage->Load(imagePath);


	//	if(!pDoc->m_pImageNG->IsDataNull())	
	//		pDoc->m_pImageNG->Free();
	//	if(!pDoc->m_pImageDsp->IsDataNull())	
	//		pDoc->m_pImageDsp->Free();

	//	pDoc->m_pImage->Load(imagePath);
	//	pDoc->m_pImageNG->Load(imagePath);
	//	pDoc->m_pImageDsp->Load(imagePath);

	//	if(pDoc->m_data.GetVisionLine(0)==GL9)
	//	{

	//		if(!pDoc->m_pImageNG1->IsDataNull())	
	//			pDoc->m_pImageNG1->Free();
	//		if(!pDoc->m_pImageDsp1->IsDataNull())	
	//			pDoc->m_pImageDsp1->Free();

	//		pDoc->m_pImage1->Load(imagePath);
	//		pDoc->m_pImageNG1->Load(imagePath);
	//		pDoc->m_pImageDsp1->Load(imagePath);
	//	}

	//	//bRet = Inspect(0);
	//	m_inspectCu1 = true;
	//	m_inspectCu2 = true;

	//	//if(bRet == 1){
	//	//	CString str = imagePath;
	//	//}
	//	//else{
	//	//	CString str = imagePath;
	//	//	CString defectImageFolder = imageFolderPath1+"\\NG";
	//	//	//디렉토리 생성
	//	//	CreateDirectory(defectImageFolder,NULL);
	//	//	//pDoc->m_pImage->Save(defectImageFolder+"\\"+imageListContainer[imageNo]);	//이미지 따로 저장
	//	//}
	//	while(m_inspectCu1 == true || m_inspectCu2 == true){
	//		Wait(10);
	//	}

	//	//메모리해제
	//	pDoc->m_pImage->Free();
	//	pDoc->m_pImageNG->Free();
	//	pDoc->m_pImageDsp->Free();

	//	if(pDoc->m_data.GetVisionLine(0)==GL9){
	//		pDoc->m_pImage1->Free();
	//		pDoc->m_pImageNG1->Free();
	//		pDoc->m_pImageDsp1->Free();
	//	}

	//}
	//}
}

double CVisWebView::GetPrecisionTime(void)
{
	LARGE_INTEGER lpFrequency;
	LARGE_INTEGER lpPerformanceCount;
	QueryPerformanceFrequency(&lpFrequency);
	QueryPerformanceCounter(&lpPerformanceCount);
	return  (double)lpPerformanceCount.QuadPart /(double)lpFrequency.QuadPart;
}
void CVisWebView::TestInspect(int nCam,int nIdx,int nMod) 
{//1412
//	return;

	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	int nAve =0;//??
	int nLine = pDoc->m_data.GetVisionLine(0);
	//신규 검사 모드 추가 //전체 이미지에서 불량 검사
	nAve = m_Inspect.GetSplitImgRoiFindNew(m_Inspect.m_FullImage,&pDoc->m_data,nCam,nIdx,nMod);

//  	if(nCam==0)
//  		nAve = m_Inspect.GetSplitImgLineFind1(pDoc->m_pImage,&pDoc->m_data,nCam,nIdx,nMod);//이물 검출용.
//  	if(nCam==1)	nAve = m_Inspect.GetSplitImgLineFind1(pDoc->m_pImage1,&pDoc->m_data,nCam,nIdx,nMod);//이물 검출용.
//  	else				nAve = m_Inspect.GetSplitImgLineFind1(pDoc->m_pImage2,&pDoc->m_data,nCam,nIdx,nMod);//이물 검출용.
	if(nCam==0)
		nCam = 0;
}
void CVisWebView::RoiInspect(int nCam,int nIdx,int nMod) 
{//1412

	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	int nAve =0;//??
	int nLine = pDoc->m_data.GetVisionLine(0);
// 	//	pDoc->m_data.m_dLimitMinBright[0] = 10;
// 	//	if(pDoc->m_data.m_rectIns[0].Width()<10 || m_avgBrightness[0] < pDoc->m_data.m_dLimitMinBright[0]|| m_avgBrightness[0] > pDoc->m_data.m_dLimitMaxBright[0]) return;
// 	//	if(nCam==0)	nAve = m_Inspect.GetSplitImgLineFind(pDoc->m_pImage,&pDoc->m_data,nCam,nIdx,nMod);//이물 검출용.
// 	//	else				nAve = m_Inspect.GetSplitImgLineFind(pDoc->m_pImage1,&pDoc->m_data,nCam,nIdx,nMod);//이물 검출용.
 	if(nCam==0 )
 		nAve = m_Inspect.GetSplitImgRoiFind(pDoc->m_pImage,&pDoc->m_data,nCam,nIdx,nMod);//이물 검출용.
 	if(nCam==1)	nAve = m_Inspect.GetSplitImgRoiFind(pDoc->m_pImage1,&pDoc->m_data,nCam,nIdx,nMod);//이물 검출용.
 	else if(nCam==2)				nAve = m_Inspect.GetSplitImgRoiFind(pDoc->m_pImage2,&pDoc->m_data,nCam,nIdx,nMod);//이물 검출용.
	if(nCam==0 && nIdx==0){
		nCam = 0;
//		pDoc->m_pImage->Save("c:\\Data\\test1.jpg");
	}
}

void CVisWebView::TestCopy(int nIdx,int nMod) 
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	unsigned char* fm = pDoc->m_pImage->GetImagePtr();
	int nw = pDoc->m_pImage->GetWidth();
	int nh = pDoc->m_pImage->GetHeight(); 

	int nAve = m_Inspect.GetImageData(pDoc->m_pImage,&pDoc->m_data,0,0,CRect(0,0,nw,nh));

	int nCount = 1;
	int nstt = 0;
	int nend = nh;
	if( nIdx==0)
		nstt=0,nend = nh/nMod;
	else if(nIdx==1)
		nstt = nh/nMod,nend=(nh/nMod)*(nIdx+1); 
	else if(nIdx==2)
		nstt = (nh/nMod)*(nIdx),nend=(nh/nMod)*(nIdx+1); 
	else if(nIdx==3)
		nstt = (nh/nMod)*(nIdx),nend=(nh/nMod)*(nIdx+1);
	nIdx = nh/nMod;
		
	int *nWidth1 = new int[nw];
	for(int i=0; i<nCount; i++)
	{
		int ntmp = 0;
		memset(nWidth1,0,nw);
		for(int y=nstt;y<nend;y++)
		{
			for(int x=0;x<nw;x+=2){
				ntmp = *(fm+y*nw+x)+*(fm+y*nw+x+1);
				nWidth1[x]+= ntmp;//*(fm+y*nw+x);
			}
		}
		for(int x=0;x<nw;x++)
			nWidth1[x]/=nIdx;
	}
	delete nWidth1;
}

BOOL CVisWebView::checkRect(int x1,int x2,int y1,int y2,int nx,int ny)
{
	if(nx>=x1 && nx<=x2 && ny>y1 && ny<y2)
		return TRUE;

	return FALSE;
}
void CVisWebView::InitClass()
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	if(pDoc->m_pImage !=NULL)
		delete pDoc->m_pImage;
	if(pDoc->m_pImageNG !=NULL)
		delete pDoc->m_pImageNG;
	if(pDoc->m_pImage1 !=NULL)
		delete pDoc->m_pImage1;
	if(pDoc->m_pImageNG1 !=NULL)
		delete pDoc->m_pImageNG1;
	if(pDoc->m_pImage2 !=NULL)
		delete pDoc->m_pImage2;
	if(pDoc->m_pImageNG2 !=NULL)
		delete pDoc->m_pImageNG2;
	if(pDoc->m_pImageDsp !=NULL)
		delete pDoc->m_pImageDsp;
	if(pDoc->m_pImageDsp1 !=NULL)
		delete pDoc->m_pImageDsp1;
	if(pDoc->m_pImageDsp2 !=NULL)
		delete pDoc->m_pImageDsp2;
	if(pDoc->m_pImageMini !=NULL)
		delete pDoc->m_pImageMini;
	if(pDoc->m_pImageMini1 !=NULL)
		delete pDoc->m_pImageMini1;
	if(pDoc->m_pImageMini2 !=NULL)
		delete pDoc->m_pImageMini2;


//	if(pDoc->m_pDlgInterface == NULL)
	{
		pDoc->m_pDlgInterface = new CDlgInterface(this);
		pDoc->m_pDlgInterface->Create(IDD_DIALOG_INTERFACE, NULL);
		pDoc->m_pDlgInterface->MoveWindow(100, 100, 900, 750);
//		pDoc->m_pDlgInterface->SetWindowPos(&CWnd::wndTopMost,100, 100, 700, 750,SWP_NOMOVE | SWP_NOSIZE);//dialog 최상위

	}

	if(m_NumPad == NULL)
	{
		m_NumPad = new CNumPad(this);
		m_NumPad->Create(IDD_DIALOG_KEYPAD,NULL);
		m_NumPad->SetWindowPos(&CWnd::wndTopMost,0, 0, 0, 0,SWP_NOMOVE | SWP_NOSIZE);//dialog 최상위
		m_NumPad->ShowWindow(0);
	}
	if(m_AlarmDlg==NULL){
		m_AlarmDlg = new CAlarmDlg(this);
		m_AlarmDlg->Create(IDD_DIALOG1,NULL);
		m_AlarmDlg->MoveWindow(1400,700,500,280);
		m_AlarmDlg->ShowWindow(0);
	}
	if(m_SysParam == NULL){
		m_SysParam = new CDlgSysParam(this);
		m_SysParam->Create(IDD_DLG_SYSPARAM,NULL);
		m_SysParam->ShowWindow(0);

	}
	if(m_DlgLastData==NULL){
		m_DlgLastData = new CDlgLastData(this);
		m_DlgLastData->Create(IDD_DIALOGLASTDATA);
		m_DlgLastData->MoveWindow(0,850,1920,200);
		m_DlgLastData->ShowWindow(0);
	}
	if(m_pDlgFullImage==NULL){
		m_pDlgFullImage = new CDlgFullImage(this);
		m_pDlgFullImage->Create(IDD_DIALOG_FULLIMAGE1);
		m_pDlgFullImage->MoveWindow(0,10,1920,1000);
		m_pDlgFullImage->ShowWindow(0);

	}
	if(m_pModelDlg==NULL){
		m_pModelDlg = new CModelDlg(this);
		m_pModelDlg->Create(IDD_DIALOG_MODEL);
		m_pModelDlg->MoveWindow(1350,250,550,650);
		m_pModelDlg->ShowWindow(0);
	}

	pDoc->m_pDlgInterface->LoadSysParam();
	if(pDoc->m_pDlgGrid == NULL)
	{
		pDoc->m_pDlgGrid = new CDlgGrid(this);
		pDoc->m_pDlgGrid->Create(IDD_DLG_GRID, NULL);
		pDoc->m_pDlgGrid->MoveWindow(FORM_IMG_WIDTH-150, 40, 480, 340);
	}
	if(pDoc->m_pDlgSetting == NULL)
	{
		pDoc->m_pDlgSetting = new CDlgSetting(this);
		pDoc->m_pDlgSetting->Create(IDD_DIALOG_SET, NULL);
		pDoc->m_pDlgSetting->MoveWindow(FORM_IMG_WIDTH-150, 40, 480, 340);
	}
	if(m_pPassword==NULL){
		m_pPassword = new CPassword(this);
		m_pPassword->Create(IDD_DIALOG_PASSWORD);
		m_pPassword->MoveWindow(1550,50,370,450);
		m_pPassword->ShowWindow(0);
	}
	if(m_pMeterData==NULL){
		m_pMeterData = new CDlgMeterData(this);
		m_pMeterData->Create(IDD_DIALOG_METERDATA);
		//		m_pMeterData->MoveWindow(0,850,1920,200);
		m_pMeterData->ShowWindow(0);
	}
	if(m_ViewImage==NULL){
		m_ViewImage = new CDlgViewImage(this);
		m_ViewImage->Create(IDD_DIALOG_EDGEVIEW);
		m_ViewImage->MoveWindow(0,750,1920,300);
		m_ViewImage->ShowWindow(0);
	}

	
 	if(!m_defectMap)//1
 	{
		CString str;
		m_defectMap = new CDlgDefectMap(this);
//		m_defectMap->Create();
		m_defectMap->Create(IDD_DLGDEFECTMAP,NULL);
		m_defectMap->MoveWindow(0,22,1920,700);//mis 메인화면
		m_defectMap->m_lbMismatchTitle.SetTextColor(COLOR_YELLOW);
		m_defectMap->m_lbMismatchTitle.SetBkColor(COLOR_BLACK);
		m_defectMap->m_lbMismatchTitle.SetFontName("휴먼둥근헤드라인");
		m_defectMap->m_lbMismatchTitle.SetFontSize(40);
		CString str11;
		if(m_strComputerName.Mid(7,1)=="C")
			str.Format("Cathode");
		else	str.Format("Anode");
		if(m_strComputerName.Mid(9,1)=="T")
			str11.Format("%s - Top Mismatch",str);
		else
			str11.Format("%s - Back Mismatch",str);

//		str.Format("MISMATCH");
		m_defectMap->m_lbMismatchTitle.SetText(str11);
		m_defectMap->m_lbMismatchTitle1[0].SetText(str);
		m_defectMap->m_lbMismatchTitle1[0].SetTextColor(COLOR_YELLOW);
		m_defectMap->m_lbMismatchTitle1[0].SetBkColor(COLOR_BLACK);
		m_defectMap->m_lbMismatchTitle1[0].SetFontName("휴먼둥근헤드라인");
		m_defectMap->m_lbMismatchTitle1[0].SetFontSize(24);
		str.Format("BACK");m_defectMap->m_lbMismatchTitle1[0].SetText(str);
		m_defectMap->m_lbMismatchTitle1[1].SetTextColor(COLOR_YELLOW);
		m_defectMap->m_lbMismatchTitle1[1].SetBkColor(COLOR_BLACK);
		m_defectMap->m_lbMismatchTitle1[1].SetFontName("휴먼둥근헤드라인");
		m_defectMap->m_lbMismatchTitle1[1].SetFontSize(24);
		str.Format("TOP");m_defectMap->m_lbMismatchTitle1[1].SetText(str);
		m_defectMap->m_lbMismatchTitle1[2].SetTextColor(COLOR_YELLOW);
		m_defectMap->m_lbMismatchTitle1[2].SetBkColor(COLOR_BLACK);
		m_defectMap->m_lbMismatchTitle1[2].SetFontName("휴먼둥근헤드라인");
		m_defectMap->m_lbMismatchTitle1[2].SetFontSize(24);
		str.Format("Mismatch");m_defectMap->m_lbMismatchTitle1[2].SetText(str);
		m_defectMap->m_lbGapTitle.SetTextColor(COLOR_GRAY_WHITE1);
		m_defectMap->m_lbGapTitle.SetBkColor(COLOR_BLACK);
		m_defectMap->m_lbGapTitle.SetFontName("휴먼둥근헤드라인");
		m_defectMap->m_lbGapTitle.SetFontSize(16);
		str.Format("Width Gap B-T");m_defectMap->m_lbGapTitle.SetText(str);
		m_defectMap->m_lbTopBackLenth[0].SetTextColor(RGB(51,51,153));
		m_defectMap->m_lbTopBackLenth[0].SetBkColor(RGB(204,204,52));
		m_defectMap->m_lbTopBackLenth[0].SetFontName("휴먼둥근헤드라인");
		m_defectMap->m_lbTopBackLenth[0].SetFontSize(16);
		str.Format("TOP PITCH");m_defectMap->m_lbTopBackLenth[0].SetText(str);
		m_defectMap->m_lbTopBackLenth[1].SetTextColor(RGB(51,51,153));
		m_defectMap->m_lbTopBackLenth[1].SetBkColor(RGB(204,204,52));
		m_defectMap->m_lbTopBackLenth[1].SetFontName("휴먼둥근헤드라인");
		m_defectMap->m_lbTopBackLenth[1].SetFontSize(16);
		str.Format("BACK PITCH");m_defectMap->m_lbTopBackLenth[1].SetText(str);


		
 		m_defectMap->ShowWindow(SW_HIDE);
 	}
}
int CVisWebView::InitCamera(int nLine)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	int nret = 0;
	if(nLine==GL8||nLine==GL9)
	{//Area

	}
	else
	{
		if(pDoc->m_pVision == NULL)
		{
			pDoc->m_pVision = new CVision(this);
			if(pDoc->m_pVision->Open(m_ctrlDisplay.m_hWnd,0,pDoc->m_data.m_nCameraWidth,pDoc->m_data.m_nCameraHeight))
				nret = 1;
		}
	}


	//ljn 추가 - 프로그램 시작 시, CIS 메모리-1 로드 
	m_cis = new CCisSetting(); 

	bool bRtn=false;
	
	CString strport;
	if(m_nCamPort>=10){
		strport.Format("\\\\.\\COM%d",m_nCamPort);
	}
	else
		strport.Format("COM%d",m_nCamPort);

// 	if(m_strComputerName.Find("DA01TOP")>=0){
// 		//시리얼 통신 연결 
// 		if(m_cis->Open(_T("COM8"), _T("9600"))){
// 			//메모리-1 로드 명령
// 			bRtn=m_cis->SendCmd(_T("DT01")); 
// 		}
// 	}
// 	else{
		//시리얼 통신 연결 
	if(m_cis->Open(strport, _T("9600"))){
		//메모리-1 로드 명령
		bRtn=m_cis->SendCmd(_T("DT01"),0); 
	}
	//메모리-1 응답 확인 
	if(bRtn){
		//성공
		AddtoList(_T("Memory1 Load"),0,0);
		nret = 1;
	}else{
		//실패
		AddtoList(_T("Memory1 Load Fail!"),0,0);
		nret = 0;
	}

	return nret;
}
void CVisWebView::InitCimage(int nLine)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	int nw = pDoc->m_data.m_nCameraWidth;
	int nh = pDoc->m_data.m_nCameraHeight;
	pDoc->m_pImage = new CImage();
	pDoc->m_pImageNG = new CImage();
	pDoc->m_pImageDsp = new CImage();
	if(MAX_CAMERAS>1)
		pDoc->m_pImage1 = new CImage();
	if(MAX_CAMERAS>2)
		pDoc->m_pImage2 = new CImage();
	pDoc->m_pImage->Create(nw, nh, 8);
	pDoc->m_pImageNG->Create(nw, nh, 8);
	pDoc->m_pImageDsp->Create(nw, nh, 8);
	if(MAX_CAMERAS>1)
		pDoc->m_pImage1->Create(nw, nh, 8);
	if(MAX_CAMERAS>2)
		pDoc->m_pImage2->Create(nw, nh, 8);
	pDoc->m_pImage->m_nWidth = CAM_WIDTH_CIS;
	pDoc->m_pImage->m_nHeight = CAM_HEIGHT_CIS;
	pDoc->m_pImage1->m_nWidth = CAM_WIDTH_CIS;
	pDoc->m_pImage1->m_nHeight = CAM_HEIGHT_CIS;
	pDoc->m_pImage2->m_nWidth = CAM_WIDTH_CIS;
	pDoc->m_pImage2->m_nHeight = CAM_HEIGHT_CIS;
	for(int i=0;i<15;i++){
		m_pDefectImage[i] = new CImage();
		m_pDefectImage[i]->Create(BAD_IMG_WIDTH,BAD_IMG_HEIGHT,8);
		m_pDefectImage[i]->m_nWidth = BAD_IMG_WIDTH;
		m_pDefectImage[i]->m_nHeight = BAD_IMG_HEIGHT;
		m_pDefectImage[i]->InitDIB();
		memset(m_pDefectImage[i]->GetImagePtr(),0,BAD_IMG_HEIGHT*BAD_IMG_WIDTH);
	}

	for(int i=0;i<20;i++){
		m_fmEdgeVew[i] = new CImage();
		m_fmEdgeVew[i]->Create(EDGE_IMG_WIDTH,EDGE_IMG_HEIGHT,8);
		m_fmEdgeVew[i]->m_nWidth = EDGE_IMG_WIDTH;
		m_fmEdgeVew[i]->m_nHeight = EDGE_IMG_HEIGHT;
		m_fmEdgeVew[i]->InitDIB();
		memset(m_fmEdgeVew[i]->GetImagePtr(),0,EDGE_IMG_HEIGHT*EDGE_IMG_WIDTH);
	}

	
	pDoc->m_pImage->InitDIB();
	pDoc->m_pImageNG->InitDIB();
	pDoc->m_pImageDsp->InitDIB();


	if(MAX_CAMERAS>1)
		pDoc->m_pImage1->InitDIB();
	if(MAX_CAMERAS>2)
		pDoc->m_pImage2->InitDIB();
	pDoc->m_pImageBad = new CImage();
	pDoc->m_pImageBad->Create(BAD_IMG_WIDTH, BAD_IMG_HEIGHT, 8);

	//20150706 ljh CImage Setting Expention
	pDoc->m_pImageWidth = pDoc->m_pImage->GetWidth();
	pDoc->m_pImageBadWidth = pDoc->m_pImageBad->GetWidth();
	pDoc->m_pImageNGWidth = pDoc->m_pImageNG->GetWidth();	
	pDoc->m_pImageDspWidth = pDoc->m_pImageDsp->GetWidth();		
	pDoc->m_pImageHeight = pDoc->m_pImage->GetHeight();
	pDoc->m_pImageBadHeight = pDoc->m_pImageBad->GetHeight();
	pDoc->m_pImageNGHeight = pDoc->m_pImageNG->GetHeight();
	pDoc->m_pImageDspHeight = pDoc->m_pImageDsp->GetHeight();	
	pDoc->m_pImagePtr = pDoc->m_pImage->GetImagePtr();
	pDoc->m_pImageNGPtr = pDoc->m_pImageNG->GetImagePtr();
	pDoc->m_pImageDspPtr = pDoc->m_pImageDsp->GetImagePtr();
	if(MAX_CAMERAS>1){
		pDoc->m_pImage1Width =  pDoc->m_pImage1->GetWidth();
		pDoc->m_pImage1Height = pDoc->m_pImage1->GetHeight();
	}
	if(MAX_CAMERAS>2){
		pDoc->m_pImage2Width =  pDoc->m_pImage2->GetWidth();
		pDoc->m_pImage2Height = pDoc->m_pImage2->GetHeight();
	}


}
void CVisWebView::InitThread(int nLine)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	pDoc->m_data.m_nUseIndex = 4;
	////////////////////inspect 1
	AfxBeginThread(ThreadTest1, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadTest2, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadTest3, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadTest4, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadTest5, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadTest6, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadTest7, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadTest8, this,THREAD_PRIORITY_NORMAL,0);

	AfxBeginThread(ThreadTest11, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadTest12, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadTest13, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadTest14, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadTest15, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadTest16, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadTest17, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadTest18, this,THREAD_PRIORITY_NORMAL,0);

	AfxBeginThread(ThreadTest21, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadTest22, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadTest23, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadTest24, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadTest25, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadTest26, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadTest27, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadTest28, this,THREAD_PRIORITY_NORMAL,0);

	////////////////////inspect2
	AfxBeginThread(ThreadInsp1, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadInsp2, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadInsp3, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadInsp4, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadInsp5, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadInsp6, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadInsp7, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadInsp8, this,THREAD_PRIORITY_NORMAL,0);

	AfxBeginThread(ThreadInsp11, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadInsp12, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadInsp13, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadInsp14, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadInsp15, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadInsp16, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadInsp17, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadInsp18, this,THREAD_PRIORITY_NORMAL,0);

	AfxBeginThread(ThreadInsp21, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadInsp22, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadInsp23, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadInsp24, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadInsp25, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadInsp26, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadInsp27, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadInsp28, this,THREAD_PRIORITY_NORMAL,0);

///////Fullimage Edge Detace
	AfxBeginThread(ThreadFullLine1, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadFullLine2, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadFullLine3, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadFullLine4, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadFullLine5, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadFullLine6, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadFullLine7, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadFullLine8, this,THREAD_PRIORITY_NORMAL,0);
//Insulate Inspect
	AfxBeginThread(ThreadInsulateDefect1, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadInsulateDefect2, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadInsulateDefect3, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadInsulateDefect4, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadInsulateDefect5, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadInsulateDefect6, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadInsulateDefect7, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadInsulateDefect8, this,THREAD_PRIORITY_NORMAL,0);

	//Preprocessing
	if(pDoc->m_pDlgInterface->m_bPreprocessing){
		AfxBeginThread(ThreadPreprocessing1, this,THREAD_PRIORITY_NORMAL,0);
		AfxBeginThread(ThreadPreprocessing2, this,THREAD_PRIORITY_NORMAL,0);
		AfxBeginThread(ThreadPreprocessing3, this,THREAD_PRIORITY_NORMAL,0);
		AfxBeginThread(ThreadPreprocessing4, this,THREAD_PRIORITY_NORMAL,0);
		AfxBeginThread(ThreadPreprocessing5, this,THREAD_PRIORITY_NORMAL,0);
		AfxBeginThread(ThreadPreprocessing6, this,THREAD_PRIORITY_NORMAL,0);
		AfxBeginThread(ThreadPreprocessing7, this,THREAD_PRIORITY_NORMAL,0);
		AfxBeginThread(ThreadPreprocessing8, this,THREAD_PRIORITY_NORMAL,0);

		AfxBeginThread(ThreadPreprocessing11, this,THREAD_PRIORITY_NORMAL,0);
		AfxBeginThread(ThreadPreprocessing12, this,THREAD_PRIORITY_NORMAL,0);
		AfxBeginThread(ThreadPreprocessing13, this,THREAD_PRIORITY_NORMAL,0);
		AfxBeginThread(ThreadPreprocessing14, this,THREAD_PRIORITY_NORMAL,0);
		AfxBeginThread(ThreadPreprocessing15, this,THREAD_PRIORITY_NORMAL,0);
		AfxBeginThread(ThreadPreprocessing16, this,THREAD_PRIORITY_NORMAL,0);
		AfxBeginThread(ThreadPreprocessing17, this,THREAD_PRIORITY_NORMAL,0);
		AfxBeginThread(ThreadPreprocessing18, this,THREAD_PRIORITY_NORMAL,0);

		AfxBeginThread(ThreadPreprocessing21, this,THREAD_PRIORITY_NORMAL,0);
		AfxBeginThread(ThreadPreprocessing22, this,THREAD_PRIORITY_NORMAL,0);
		AfxBeginThread(ThreadPreprocessing23, this,THREAD_PRIORITY_NORMAL,0);
		AfxBeginThread(ThreadPreprocessing24, this,THREAD_PRIORITY_NORMAL,0);
		AfxBeginThread(ThreadPreprocessing25, this,THREAD_PRIORITY_NORMAL,0);
		AfxBeginThread(ThreadPreprocessing26, this,THREAD_PRIORITY_NORMAL,0);
		AfxBeginThread(ThreadPreprocessing27, this,THREAD_PRIORITY_NORMAL,0);
		AfxBeginThread(ThreadPreprocessing28, this,THREAD_PRIORITY_NORMAL,0);
	}
	
	AfxBeginThread(ThreadInspectMain, this,THREAD_PRIORITY_HIGHEST,0);//THREAD_PRIORITY_NORMAL,0); // 스레드 우선순위 조정

	
	//Thread Init
	AfxBeginThread(ThreadMain, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadInspect, this,THREAD_PRIORITY_NORMAL,0);



	if(MAX_CAMERAS>1){
		AfxBeginThread(ThreadInspect1, this,THREAD_PRIORITY_NORMAL,0);
	}
	if(MAX_CAMERAS>2){
		AfxBeginThread(ThreadInspect2, this,THREAD_PRIORITY_NORMAL,0);
	}
	AfxBeginThread(ThreadSaveImage, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadSaveImageCam2, this,THREAD_PRIORITY_NORMAL,0);
	AfxBeginThread(ThreadSaveImageCam3, this,THREAD_PRIORITY_NORMAL,0);

	if(m_strComputerName.Find("BACK")>=0 ||  pDoc->m_data.m_strComName.Mid(9,1)=="B"){//pc name
		//file copy and Data Put
		AfxBeginThread(ThreadMismatch, this,THREAD_PRIORITY_NORMAL,0);

	}
	AfxBeginThread(ThreadFileCopy, this,THREAD_PRIORITY_NORMAL,0);//top은 미스매치 가져오고 백은 탑폭 가져온다
	//ljh추가

	// lot change시 데이터 복사(mismatch back 이거나 head back에서)
 	if((m_strComputerName.Mid(8,1)=="M" && pDoc->m_data.m_strComName.Mid(9,1)=="B" && m_strComputerName.Find(_T("CMI"))>=0) || 
 		(m_strComputerName.Find(_T("OCH"))>=0 && m_strComputerName.Mid(8,1)=="H" && pDoc->m_data.m_strComName.Mid(9,1)=="B"))
 		AfxBeginThread(ThreadLotChange1, this,THREAD_PRIORITY_NORMAL,0);

	

	//Image Delete Thread 추가
	m_bImageDelete = false;
//	fnSaveThreadInit();

}
void CVisWebView::InitExposure(int nCam,int nLine,int nShutter)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	if(nLine != GL1  && nLine != GL8&& nLine != GL9)//line scan
//		for(int i=0;i<MAX_CAMERAS;i++)
			pDoc->m_pVision->SetExposureTime(nCam, nShutter*25,1);

}

void CVisWebView::InitSocket(int nLine)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	//udp network	
	if(pDoc->m_RecvtoServerSock.Create((HWND)this->m_hWnd,DEFAULT_PORT))//10000
		pDoc->m_RecvtoServerSock.WatchComm();
	//Socket Initializing
	int n = pDoc->m_RecvtoServerSock.GetIpAdr();
		
	pDoc->m_SendtoServerSock.Create((HWND)this->m_hWnd,DEFAULT_PORT + pDoc->m_data.m_nComPort[0],"200.0.0.254");
	if(MAX_CAMERAS>1)
		pDoc->m_SendtoServerSock1.Create((HWND)this->m_hWnd,DEFAULT_PORT + pDoc->m_data.m_nComPort[1],"200,0.0.254");
		//마킹기 주소
//		pDoc->m_SendtoMarkingSock.Create((HWND)this->m_hWnd,MARKING_PORT + pDoc->m_data.m_nComPort[0],"200.0.0.253");

	//Marking Vision Socket
	//	pDoc->m_SendtoMarkVisionSock1.Create((HWND)this->m_hWnd,MARKING_PORT+pDoc->m_RecvtoServerSock.GetIpAdr(),"100.0.0.241");
	//	pDoc->m_SendtoMarkVisionSock2.Create((HWND)this->m_hWnd,MARKING_PORT+pDoc->m_RecvtoServerSock.GetIpAdr(),"100.0.0.242");
}

void CVisWebView::InitData(int nLine)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	int nw = pDoc->m_pImage->GetWidth();
	int nh = pDoc->m_pImage->GetHeight();
	pDoc->m_data.InitData(1,nw,nh);
	s_inspectTime = 0;
	g_frame_num = -3;
	m_nCkTape = 0;
	//20150626
	m_autoEncoder = false;
	///////////////////////대명
	for(int n=0;n<MAX_CAMERAS;n++)
	{

		dCmaAverage[n] = 0;
		nAveCount[n] = 1;
		nEdgeCnt[n] = 1;
		dCamEdge[n] = 0;
	}
	if(nLine == GL9)//pDoc->m_data.m_strMachineName == "")
	{
		m_bImageSave = FALSE;
		m_bImageSaveAll = FALSE;
	}
	m_bImageSave = TRUE;
	//image jpg
	pDoc->m_data.m_bSaveBmp = TRUE;//t = bmp   f=jpg
	m_bDefectSaveStats = TRUE;
	m_binaryValue = 80;

}
void CVisWebView::InitTimer(int nLine)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	//	SetTimer(1, 500, NULL);
	SetTimer(TEVENT_HDD_SPACE, 10*1000, NULL);
	SetTimer(200,30*1000,NULL);//Frame ㅣ기록. 미사용
	if(m_strComputerName.Find("CHO")<=0 && !pDoc->m_pDlgInterface->m_bMasterPc)
		SetTimer(READ_SHARED_MEM, 500, NULL);//plc read

	SetTimer(20013,50,NULL);//chuck check core A or B
	SetTimer(200611,1000*10/**60*3*/,NULL);

	//조명통신 초기화
// 	if(pDoc->m_data.m_strComName.Right(1) == "1" || pDoc->m_data.m_strComName.Right(1) == "2")
// 	{//3sec light check
// 		fnSetPort();
// 		AfxBeginThread(ThreadLightCheck, this,THREAD_PRIORITY_NORMAL,0);
// 	}
	SetTimer(TEVENT_CHECKLENGTH,500,NULL);

	// nsys 불량 체크
	if(pDoc->m_data.m_strComName.Find("OCH")>=0){
		if(pDoc->m_data.m_strComName.Mid(9,1)=="B")
			SetTimer(200624, 1000, NULL);
	}
	else if(pDoc->m_data.m_strComName.Find("CMI")>=0){
		if(pDoc->m_data.m_strComName.Mid(8,1)=="M" && pDoc->m_data.m_strComName.Mid(9,1)=="B")
			SetTimer(200624, 1000, NULL);
	}
}
void CVisWebView::OnBtImgTest() 
{
// 	return;
// 	GrabImgSaveCam2(0);
// 	return;
// 	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
// 	unsigned char* fm = pDoc->m_pImage->GetImagePtr();
// 	CDC* pDc;
// 	pDc = GetDC();
// 
// 	int k=0;
// 
// 	DrawCross(pDc,CPoint(100,100),100,COLOR_RED,2);
// 	DrawCross(pDc,CPoint(300,300),100,COLOR_RED,2);
// 	ReleaseDC(pDc);
// 	
// 	return;
// 	int nCount = 1;
// 	int nw = pDoc->m_pImage->GetWidth();
// 	int nh = pDoc->m_pImage->GetHeight();
// 	double dxcount = 1/nw;
// 	double dycount = 1/nh;
// 	int ncc = 0,ncc1=0;
// 
// 	double pretime1,ctime[10];//1,ctime2,ctime3;
// 	pretime1 = GetPrecisionTime();
// 	ctime[2] = GetPrecisionTime();
// 	int *nWidth = new int[nw];
// 	memset(nWidth,0,nw);
// 	for(int x=0;x<nw;x++)
// 	{
// 		for(int y=0;y<nh;y++)
// 			nWidth[x]+=*(fm+y*nw+x);
// 		nWidth[x]/=nh;//dycount;//nh;
// 	}
// 	ctime[3] = GetPrecisionTime();
// 	CRect rt[30];
// 	CPoint pt;
// 	for (int i=0;i<30;i++)
// 	{
// 		rt[i].SetRect(10*i,10*i,10*i+128,10*i+128);
// 	}
// 	unsigned int *nHeight = new unsigned int[nh];
// 	for(int i=0; i<nCount; i++)
// 	{
// 		memset(nHeight,0,nh);
// 		
// 		for(int y=0;y<nh;y++)
// 		{
// 			int ntmp = 0;
// 			for(int x=0;x<nw;x++){
// 				pt.SetPoint(x,y);
// 				for(int k=0;k<30;k++){
// 					if(rt[k].PtInRect(pt))
// 						ncc++;;
// 				}
// 
// 				ntmp += *(fm+y*nw+x);
// 			}
// //				nHeight[y]+= *(fm+y*nw+x);
// 			nHeight[y]= ntmp/nw;//*=dxcount;//nw;
// 		}
// //		for(int y=0;y<nh;y++)
//  //			*(nHeight+y) /=nw;
// 	}
// 	ctime[4] = GetPrecisionTime();
// 
// 	int *nWidth1 = new int[nw];
// 	for(int i=0; i<nCount; i++)
// 	{
// 		int ntmp = 0;
// 		memset(nWidth1,0,nw);
// 		for(int y=0;y<nh;y++)
// 		{
// 			for(int x=0;x<nw;x+=2){
// 				ntmp = *(fm+y*nw+x)+*(fm+y*nw+x+1);
// 				nWidth1[x]+= ntmp;//*(fm+y*nw+x);
// 			}
// 		}
// 		for(int x=0;x<nw;x++)
// 			nWidth1[x]/=nh;
// 	}
// 
// 	ctime[5] = GetPrecisionTime();
// 	int nx[30],ny[30],nx1[30],ny1[30];
// 	for (int i=0;i<30;i++)
// 	{
// 	//	rt[i].SetRect(10*i,10*i,10*i+128,10*i+128);
// 		nx[i] = 10*i;nx1[i] = 10*i+128;
// 		ny[i] = 10*i;ny1[i] = 10*i+128;
// 	}
// 	for(int i=0; i<nCount; i++)
// 	{
// 		memset(nHeight,0,nh);
// 		for(int y=0;y<nh;y++)
// 		{
// 			int ntmp = 0;
// 			for(int x=0;x<nw;x++){
// //				pt.SetPoint(x,y);
// 				for(int k=0;k<30;k++){
// //					if(checkRect(nx[k],nx1[k],ny[k],ny1[k],x,y))
// 					if(x>=nx[k] && x<nx1[k] && y>=ny[k] && y<ny1[k])
// 						ncc1++;
// 				}
// 				ntmp +=*(fm+y*nw+x);
// 			}
// 			nHeight[y]= ntmp/nw;//*=dxcount;//nw;
// 		}
// // 		for(int y=0;y<nh;y++)
// // 			nHeight[y]/=nw;
// 	}
// 	ctime[6] = GetPrecisionTime();
// 
// 
// 	ctime[7] = GetPrecisionTime();
// 	int nn3 = ncc = ncc1;//=0 ;
// 	CString str;
// //	str.Format("%.3f,%.3f,%.3f,%.3f,%.3f,%d,%d",ctime[3]-ctime[2],ctime[4]-ctime[3],ctime[5]-ctime[4],ctime[6]-ctime[5],ctime[7]-ctime[6],ncc,ncc1);
// //	str.Format("%.3f,%.3f,%d",ctime[6]-ctime[5],ctime[7]-ctime[6],nn3);
// 	str.Format("%.3f,%.3f,%.3f,%.3f,%.3f",ctime[3]-ctime[2],ctime[4]-ctime[3],ctime[5]-ctime[4],ctime[6]-ctime[5],ctime[7]-ctime[6]);
// 	m_labelWarning.SetText(str);
// //	str.Format("%d , %d",ncc,ncc1);
// //	MessageBox(str);
// 
// 	delete nWidth1;
// 	delete nWidth;
// 	delete nHeight;
//	m_bImageDelete = true;
//	return;
//
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	CFile file;
	CString str,strng,strok;
	TCHAR	spath[100];
	BROWSEINFO bi;
	memset(&bi,0,sizeof(bi));
	bi.hwndOwner = GetSafeHwnd();

	bi.ulFlags=BIF_RETURNONLYFSDIRS;
	
	LPITEMIDLIST lpifq=SHBrowseForFolder(&bi);

	if(lpifq)
	{
		SHGetPathFromIDList(lpifq,spath);
		LPMALLOC lpMalloc=NULL;
		HRESULT hr = SHGetMalloc(&lpMalloc);
		if(SUCCEEDED(hr))
		{
			lpMalloc->Free(lpifq);
			lpifq = NULL;
			lpMalloc->Release();
			lpMalloc = NULL;
		}
	}
	else
	{
	}

	CString src, tar,strDevice;
	HANDLE hFind;				// FindFirstFile 핸들
	WIN32_FIND_DATA	fd;			// 검색한 화일의 정보
	BOOL bRet = TRUE;
	CString strfile;
	str = LPCTSTR(spath);
	if(pDoc->m_data.m_bSaveBmp)
		str += "\\*.bmp";
	else
		str += "\\*.jpg";
	int ntmp =0;
	CString strMonth;

	bRet = TRUE;
	hFind = FindFirstFile( str, &fd);
	strDevice = strfile.Left(3);
	while(hFind != INVALID_HANDLE_VALUE && bRet)
	{			
		strfile.Format("%s\\%s", spath, fd.cFileName);
		if( !(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )		// Not directory, which means file.
		{
//			strDevice = fd.cFileName;
//			strMonth = strDevice.Mid(10,5);
//			strDevice = strDevice.Left(4);
			pDoc->m_pImage->Load(strfile);
			Wait(10);
			pDoc->m_pImageNG->Load(strfile);
			pDoc->m_pImageDsp->Load(strfile);
			m_strImgTestName = strfile;
			DrawImage(m_nSelectCam);
			ntmp = Inspect(0);
			SetWarning(strfile);
			/*CString str;
			str.Format("%d", g_frame_num);
				WriteLog("c:\\glim\\log", "frame_debug", str);
			WriteLog("c:\\glim\\log", "frame_debug", "frame3");*/
			g_frame_num++;
			/*str.Format("%d", g_frame_num);
				WriteLog("c:\\glim\\log", "frame_debug", str);*/

			if(m_bImageSelect){
				if(ntmp==1){
//					strng.Format("%s\\OK_%.0f_%.0f\\",spath,pDoc->m_data.m_dThUp,pDoc->m_data.m_dThDn); 
//					CreateDirectory(strng,NULL);
//					strng += fd.cFileName;
//					pDoc->m_pImageNG->Save(strng);
				}
				else{
					strng.Format("%s\\NG_%.0f_%.0f\\",spath,pDoc->m_data.m_dThUp,pDoc->m_data.m_dThDn); 
					CreateDirectory(strng,NULL);
					strng += fd.cFileName;
					pDoc->m_pImageNG->Save(strng);
				}
				Wait(100);
			}
//		fnWriteResult(strfile,ntmp,strDevice,strMonth);//*/
			if(!m_bAutoRun)	while( WaitForSingleObject((HANDLE)m_ev_rbutton_down, 100) != WAIT_OBJECT_0 ) Wait(1);
			else			Wait(10);
//			Wait(100);
		}
		else if( strfile == "." || strfile == "..")
		{
			// do nothing
		}
		else	// it is directory
		{
			// do nothing	choi-sh@koreno.co.kr
		}
		bRet= FindNextFile(hFind, &fd);
	}
	::FindClose(hFind);
	AfxMessageBox("Directory Inspect Complete!!!");	
}
void CVisWebView::OnBtnGetProfile2() 
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	LoadImage1();

//	m_eSaveImageCam2.SetEvent();
//	m_eSaveImage.SetEvent();

//	ReadDummyData1(0);
//	ReadDummyData1(1);
	return;

	pDoc->m_pImage->Load("out70.jpg");
	DrawImage(0);


	return;
	pDoc->m_pImage->Save("c.jpg");
	return;
	static int nn1 = 0;
	if( pDoc->m_data.m_strComName.Right(3)=="401"){
		if(nn1%2==0){
			pDoc->m_data.m_nLgtController = 3;
			for(int i=0;i<pDoc->m_data.m_nLgtController;i++){
				LightOFFWAVE(i,0);

			}

		}
		else
			for(int i=0;i<pDoc->m_data.m_nLgtController;i++){
				LightONWAVE(i,0);

			}
			nn1++;
	}
	return;

	double ctime[10];//1,ctime2,ctime3;
	ctime[0] = GetPrecisionTime();
	CRect rt;
	rt.SetRect(0,0,pDoc->m_data.m_nCameraWidth,pDoc->m_data.m_nCameraHeight);

	int nAve = m_Inspect.GetImageData(pDoc->m_pImage,&pDoc->m_data,0,0,rt);


	ctime[2] = GetPrecisionTime();
	m_Inspect.GetDataSort(pDoc->m_pImage,&pDoc->m_data,0);
	ctime[3] = GetPrecisionTime();

	DrawImage(0);
	ctime[4] = GetPrecisionTime();
	CString str;
	str.Format("%.3f , %.3f , %.3f , %.3f",ctime[4]-ctime[0],ctime[1]-ctime[0],ctime[2]-ctime[1],ctime[3]-ctime[2]);
	m_labelWarning.SetText(str);
}

void CVisWebView::LightONWAVE(int nCh, int nPort) 
{
	CString strCmd(_T(""));

	int nOnOff = 1; // 1=true, 0=false

	if(nPort==0){
		//조명 on off
		strCmd.Format(_T("%cSA%d%c"), 0x02, nOnOff, 0x03); 
//		m_LightCtrl[nCh].WriteString(strCmd); 
//		Wait(200);
		//조명 밝기 설정 0~100%
//		strCmd.Format(_T("%cWA%d%c"), 0x02,255,0x03); //100
//		m_LightCtrl[nCh].WriteString(strCmd); 
	}
	else{
		//조명 on off
		strCmd.Format(_T("%cSA%d%c"), 0x02, nPort,nOnOff, 0x03); 
//		m_LightCtrl[nCh].WriteString(strCmd); 
		//조명 밝기 설정 0~100%
//		strCmd.Format(_T("%cWA100%c"), 0x02,nPort,0x03); 
//		m_LightCtrl[nCh].WriteString(strCmd); 
	}

}
void CVisWebView::LightOFFWAVE(int nCh,int nPort)
{
	CString strCmd(_T(""));

	int nOnOff = 0; // 1=true, 0=false

	if(nPort==0){
		//조명 밝기 설정 0~100%
//		strCmd.Format(_T("%cWA0%c"), 0x02,0x03); 
//		m_LightCtrl[nCh].WriteString(strCmd);
		//조명 on off
		strCmd.Format(_T("%cSA%d%c"), 0x02, nOnOff, 0x03); 
//		m_LightCtrl[nCh].WriteString(strCmd); 

	}
	else{
		//조명 밝기 설정 0~100%
		strCmd.Format(_T("%cW%d0%c"), 0x02,nPort+1,0x03); 
//		m_LightCtrl[nCh].WriteString(strCmd);
		//조명 on off
		strCmd.Format(_T("%cS%d%d%c"), 0x02,nPort+11, nOnOff, 0x03); 
//		m_LightCtrl[nCh].WriteString(strCmd); 
		strCmd.Format(_T("%cW%d0%c"), 0x02,nPort,0x03); 
//		m_LightCtrl[nCh].WriteString(strCmd);
		//조명 on off
		strCmd.Format(_T("%cS%d%d%c"), 0x02,nPort, nOnOff, 0x03); 
//		m_LightCtrl[nCh].WriteString(strCmd); 

	}

}

void CVisWebView::LightONWAVE1CH(int nport)
{
	CString strCmd(_T(""));
	char cLightVal = 80;
	strCmd.Format(_T("%cW%c%c"), 0x02,cLightVal,0x03);
	m_LightCtrl[nport].WriteString(strCmd); 

	//BYTE temp = 0;
	//double value = 0;
	//char pCommand[4];
	//pCommand[0] = 0x02;		// STX
	//pCommand[1] = 'W';		// Read명령
	//pCommand[2] = 80;		// 'A' - 전류값  V
	//pCommand[3] = 0x03;		// ETX

	
	//m_cComm[nport].Write(pCommand,4);
}


void CVisWebView::LightOFFWAVE1CH(int nport)
{
	CString strCmd(_T(""));
	char cLightVal = 0;
	strCmd.Format(_T("%cW%c%c"), 0x02,cLightVal,0x03);
	m_LightCtrl[nport].WriteString(strCmd); 

	//BYTE temp = 0;
	//double value = 0;
	//char pCommand[4];
	//pCommand[0] = 0x02;		// STX
	//pCommand[1] = 'W';		// Read명령///
	//pCommand[2] = 0;		// 'A' - 전류값  V
	//pCommand[3] = 0x03;		// ETX

	//m_LightCtrl[nport].WriteString(pCommand); 

	//m_cComm[nport].Write(pCommand,4);
}


void CVisWebView::fnSetPort() 
{

	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
//default Port 1 , 2
	pDoc->m_data.m_nLgtController = 2;
	CString str;
	for(int i=0; i<pDoc->m_data.m_nLgtController; i++){
		str.Format("COM%d",i+1);
		if(m_LightCtrl[i].Open(str)){
			SetWarning("Light Success!");
			LightONWAVE1CH(i); // Turn On
			// LightOFFWAVE1CH(i);// Turn Off
			Wait(500);
		}
		else{
			SetWarning("Light Fail!");
		}
	}
/*
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CString str;
	int nport = DEFAULTPORT;
//조명 port define
	if( pDoc->m_data.m_strComName.Right(3)=="401"){	//동축
		pDoc->m_data.m_nLgtController = 3;
		for(int i=nport;i<nport+pDoc->m_data.m_nLgtController;i++){
			str.Format("COM%d",i);
			if(m_LightCtrl[i-nport].Open(str)){//open
//				LightOFFWAVE(i-nport,0);
//				LightOFFWAVE(i-nport,1);
//				Wait(500);
////				LightONWAVE(i-nport,0);
				LightONWAVE(i-nport,0);
				Wait(100);
				LightONWAVE(i-nport,0);
				getCurrentData(i-nport);

			}
			else{
				SetWarning("Light Fail!");
			}
		}

	}
	else if(pDoc->m_data.m_strComName.Right(3) == "301"){	//정투과
		pDoc->m_data.m_nLgtController = 1;
		nport = 5;
		for(int i=nport;i<nport+pDoc->m_data.m_nLgtController;i++)
		{
			m_cComm[i-nport].Close();

			m_nPortNumber = i;
			m_cComm[i-nport].SetPortSetting(CBR_9600,8,ONESTOPBIT,NOPARITY);		//통신설정
			if(!m_cComm[i-nport].Open(m_nPortNumber)){
				SetWarning("Light Fail!");
			}
			else
			{
				LightONWAVE1CH(i-nport);
				Wait(100);
				i = i;
				getCurrentData(i-nport);
			}
		}
	}


*/

	//int i;
	//int dport = DEFAULTPORT;
	//	Lamp = (char)m_CurrentElectric;

}

double CVisWebView::ReadLightDataWave(char data,int ch)
{
/*
	BYTE temp = 0;
	double value = 0;

	CString strCmd(_T(""));
	strCmd.Format(_T("%cR%d%c%c"), 0x02,ch,data,0x03); 
	m_LightCtrl[ch-1].WriteString(strCmd);
	//조명 on off
	Wait(100);

	value = m_LightCtrl[ch-1].ReadString("");
*/
	return 0;//value;
}


double CVisWebView::ReadLightData1CH(char data,int nport)
{
	/*
	BYTE temp = 0;
	double value = 0;
	char pCommand[4];
	pCommand[0] = 0x02;		// STX
	pCommand[1] = 'R';		// Read명령
	pCommand[2] = data;		// 'A' - 전류값  V
	pCommand[3] = 0x03;		// ETX

	m_cComm[nport].Write(pCommand,4);

	Wait(100);

	char pRead[5];
	pRead[0] = 0x00;		// STX
	pRead[1] = 0x00;		// Read명령
	pRead[2] = 0x00;		// 'A' - 전류값
	pRead[3] = 0x00;		// ETX

	m_cComm[nport].Read(pRead,4);

	temp = pRead[2];
	value = (double)temp/10;
*/
	return 0;//value;
}


void CVisWebView::getCurrentData(int nport) 
{
	/*
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	if(pDoc->m_data.m_strComName.Right(3) == "401"){//신규 조명제어기
		pDoc->m_data.m_nLgtController = 3;

		m_Electric[nport] = ReadLightDataWave('A',nport+1);
		m_Voltage[nport] = ReadLightDataWave('V',nport+1);
	}
	else 	if(pDoc->m_data.m_strComName.Right(3) == "301"){//기존 조명 제어기
		pDoc->m_data.m_nLgtController = 1;

		m_cComm[nport].ClearRXBuffer();
		//	m_Electric[nport-DEFAULTPORT] = ReadLightData('A',nport);					//전류
		//	m_Voltage[nport-DEFAULTPORT] = ReadLightData('V',nport);						//전압 
		//	m_CurrentElectric[nport-DEFAULTPORT] = ReadLightData('P',nport)*10;			//현재설정값 
		m_Electric[nport] = ReadLightData1CH('A',nport);					//전류
		m_Voltage[nport] = ReadLightData1CH('V',nport);						//전압 
		m_CurrentElectric[nport] = ReadLightData1CH('P',nport)*10;			//현재설정값 
	}
*/
}

void CVisWebView::fnWriteLight(CString strData) 
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	CStdioFile   file;
	CString filename;
	CString strtmp,str,strTitle,strpath;
	CTime ttime = CTime::GetCurrentTime();
	CString kk = ttime.Format("%Y_%m_%d");

	strpath.Format("c:\\Glim\\");
	CreateDirectory(strpath,NULL);
	strpath.Format("c:\\Glim\\Log\\");
	CreateDirectory(strpath,NULL);
	strpath.Format("c:\\Glim\\Log\\Light\\");
	CreateDirectory(strpath,NULL);
	filename.Format("%s%s_LightData.txt",strpath,kk);

	////////////////////////
	{	
		try{
			if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
			{		
				file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText);
				file.WriteString(strData);
				file.WriteString("\n");	
				file.Close();
			}
			else
			{
				file.SeekToEnd();			
				file.WriteString(strData);
				file.WriteString("\n");
				file.Close(); 
			}	

		}
		catch(CFileException)
		{
			//AfxMessageBox( "File Open failed" );
		}
		catch(...)
		{
			//AfxMessageBox( "File Open failed2~" );
		}

	}

}

void CVisWebView::ReadCalData(int nCam)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	CTime ttime = CTime::GetCurrentTime();
	CString kk = ttime.Format("%Y_%m_%d");//ttime.Format("%H_%M_%S");
	CString strTime = ttime.Format("[%Y %m %d %H:%M:%S]");
	CStdioFile   file;
	CString filename;
	CString strpath;
	CString str;
	double dtmp1=pDoc->m_data.m_dCalibSttX[nCam],dtmp2=pDoc->m_data.m_dScaleFactorX[nCam];

// 	filename.Format("c:\\Glim\\CalData\\%sCam%d_Scale.txt",pDoc->m_data.m_strComName,nCam);
// 	//filename.Format("%s",name);
// 
// 	if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
// 	{	
// 		for(int i=0;i<CAM_WIDTH_CIS;i++){			
// 			pDoc->m_data.m_dCalXPos[nCam][i] = (dtmp2*i);
// 		}
// 	}
// 	else
// 	{
// 		for(int i=0;i<CAM_WIDTH_CIS;i++){
// 			file.ReadString(str);	//Pixel
// 			pDoc->m_data.m_dCalXPos[nCam][i] = atof(str);
// 		}
// 		file.Close(); 
// 	}	//m_dCalXPos
	for(int i=0;i<CAM_WIDTH_CIS;i++){

		int tmp = i/304.;
		pDoc->m_data.m_dCalXPos[nCam][i] = dtmp2*i+ tmp*dtmp2;
//		pDoc->m_data.m_dCalXPos[nCam][i] = dtmp2*i + tmp*0.08467;
	}
}
int CVisWebView::ReadPort(CString strport)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CStdioFile   file;
	CString filename;
	CString strpath;
	CString str;

	strpath.Format("C:\\Glim\\");
	CreateDirectory(strpath,NULL);	
	if(strport.Find("IO")>=0)
		filename.Format("%sIOPort.glm",strpath);
	else if(strport.Find("CAM")>=0)
		filename.Format("%sCAMPort.glm",strpath);

	if(file.Open(filename, CFile::modeReadWrite|CFile::typeText))
	{		
		file.ReadString(str);//pDoc->m_data.m_strDefaultModel);	
		file.Close();
	}	
	else{
		file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText);
		if(strport.Find("CAM")>=0)str.Format("9");
		if(strport.Find("IO")>=0)str.Format("4");
		file.WriteString(str);
		file.Close();
	}
	return atoi(str);
}

void CVisWebView::ReadDummyData(int nCam)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	CTime ttime = CTime::GetCurrentTime();
	CString kk = ttime.Format("%Y_%m_%d");//ttime.Format("%H_%M_%S");
	CString strTime = ttime.Format("[%Y %m %d %H:%M:%S]");
	CStdioFile   file;
	CString filename;
	CString strpath;
	CString str;
	double dtmp1=pDoc->m_data.m_dCalibSttX[nCam],dtmp2=pDoc->m_data.m_dScaleFactorX[nCam];

	filename.Format("c:\\Glim\\Temp\\Cam%d.txt",nCam);
	//filename.Format("%s",name);
	int nCount = 0;
	double dcount1=0;

	if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
	{	
		for(int i=0;i<CAM_WIDTH_CIS;i++){			
			pDoc->m_data.m_dCalXPos[nCam][i] = (dtmp2*i)+dtmp1;
		}
	}
	else
	{
		for(int i=0;i<CAM_WIDTH_CIS;i++){

			file.ReadString(str);	//Pixel
			if(str == "")break;
			
			pDoc->m_data.m_nCalDummyData[nCam][nCount] = atoi(str);
			nCount++;
		}
		file.Close(); 
	}	//m_dCalXPos

	double dMastermm = 10;
	double dummy1=0,dummy2=0,dummy3=0,dummy4=0;
	
	

	for(int i=0;i<nCount-1;i++){
		dummy1 = pDoc->m_data.m_nCalDummyData[nCam][i+1]-pDoc->m_data.m_nCalDummyData[nCam][i];
		dummy2 = dMastermm/dummy1;
		dummy3 += dummy2;
		dcount1++;
		for(int k=pDoc->m_data.m_nCalDummyData[nCam][i];k<pDoc->m_data.m_nCalDummyData[nCam][i+1];k++)
		pDoc->m_data.m_dCalXPos[nCam][k] = dummy2*k;
	}

	dummy4 = dummy3/dcount1;
	for(int i=0;i<pDoc->m_data.m_nCalDummyData[nCam][0];i++)
		pDoc->m_data.m_dCalXPos[nCam][i] = dummy4*i;
	for(int i=pDoc->m_data.m_nCalDummyData[nCam][nCount-1];i<CAM_WIDTH_CIS;i++)
		pDoc->m_data.m_dCalXPos[nCam][i] = dummy4*i;

	filename.Format("c:\\Glim\\Temp\\Cam%d_Scale.txt",nCam);


	double dold = 0;
	file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText);
	for(int i=0;i<CAM_WIDTH_CIS;i++){
		str.Format("%.6f",pDoc->m_data.m_dCalXPos[nCam][i]);
		if(i<10870){
			dummy2 = 0.02475;
		}
		else if(i>=10870 && i<15500){
			dummy2 = 0.024728;
		}
		//else if(i>=1758 && i<2913){
		//	dummy2 = 0.024728;
		//}
// 		else if(i>=2913 && i<4198){
// 			dummy2 = 0.02484;
// 		}
// 		else if(i>=4198 && i<4943){
// 			dummy2 = 0.024839;
// 		}
// 		else if(i>=4943 && i<7656){
// 			dummy2 = 0.024829;
// 		}
// 		else if(i>=7656 && i<8813){
// 			dummy2 = 0.024818;
// 		}
// 		else if(i>=8813 && i<9634){
// 			dummy2 = 0.024836;
// 		}
		//else if(i>=14377 && i<14783){
		//	dummy2 = 0.024667;
		//}
		//else if(i>=14783 && i<15194){
		//	dummy2 = 0.024684;
		//}
// 		else if(i>=15194 && i<16005){
// 			dummy2 = 0.024669;
// 		}
// 		else if(i>=13848 && i<14377){
// 			dummy2 = 0.024669;
// 		}
		else {
			dummy2 = 0.02475;
		}
		dummy3 = dold;// dummy2*i;
		str.Format("%.6f",dummy3);
		file.WriteString(str);
		file.WriteString("\n");	
		dold += dummy2;

	}
	file.Close();


	
}

void CVisWebView::ReadDummyData1(int nCam)//일부scale수정용
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	CTime ttime = CTime::GetCurrentTime();
	CString kk = ttime.Format("%Y_%m_%d");//ttime.Format("%H_%M_%S");
	CString strTime = ttime.Format("[%Y %m %d %H:%M:%S]");
	CStdioFile   file;
	CString filename;
	CString strpath;
	CString str;
	double dtmp1=pDoc->m_data.m_dCalibSttX[nCam],dtmp2=pDoc->m_data.m_dScaleFactorX[nCam];

	filename.Format("c:\\Glim\\Temp\\Cam%d.txt",nCam);
	//filename.Format("%s",name);
	int nCount = 0;
	double dcount1=0;
	double  ddata1[CAM_WIDTH_CIS];
	for(int i=0;i<CAM_WIDTH_CIS;i++)ddata1[i] = 0;

	if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
	{	
		for(int i=0;i<CAM_WIDTH_CIS;i++){			
			pDoc->m_data.m_dCalXPos[nCam][i] = (dtmp2*i)+dtmp1;
		}
	}
	else
	{
		for(int i=0;i<CAM_WIDTH_CIS;i++){

			file.ReadString(str);	//Pixel
			if(str == "")break;

			ddata1[i] = atof(str);
			nCount++;
		}
		file.Close(); 
	}	//m_dCalXPos

	double dMastermm = 10;
	double dummy1=0,dummy2=0,dummy3=0,dummy4=0;


	filename.Format("c:\\Glim\\Temp\\Cam%d_Scale.txt",nCam);


	double dold = 0;
	if(nCam ==0)
		dummy4 = 0.02452;
	else
		dummy4 = 0.02446;

	file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText);
	for(int i=0;i<CAM_WIDTH_CIS;i++){
		str.Format("%.6f",ddata1[i]);
		if(i>CAM_WIDTH_CIS-1600){
			dummy2 = dummy4;//0.024859;
			ddata1[i] =ddata1[i-1]+dummy2;
		}
 		else if(i==0){
 			ddata1[i] = 0;
 		}
 		else{
 			dummy2 = 0.02485;
 			ddata1[i] =ddata1[i-1]+dummy2;
 		}
		//else if(i>=10870 && i<15500){
		//	dummy2 = 0.024728;
		//}
		//else {
		//	dummy2 = 0.02475;
		//}
		str.Format("%.6f",ddata1[i] );
		file.WriteString(str);
		file.WriteString("\n");	

	}
	file.Close();
}

void CVisWebView::fnWriteData1(int frame,int defectcnt,int defectclass,float px, float py,float sx,float sy, CString imgpath,double dBcrY,double dRecieveY,double thup, double thdn,double dtmp1,int flag,int nCam) 
{
	//log4cpp::Category& debugLog = ((CVisWebApp*)AfxGetApp())->logCppLog;
	//debugLog.debug("fnWriteData");
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	CStdioFile   file;
	CString filename;
	CString strtmp,str,strTitle,strpath,strOkNg,strpc,strtmp1,strtmp2,strtime;
	CString txtscr,txtdst;
	int nPcno =0;
	int nLine =0;
	//날자 LotNo. Frame	DefectCount	Defect-Class	x-Pos	Y-Pos	X-Size	Y-Size	ImagePath
	//////////////
	CString data[6];
	CTime timer=CTime::GetCurrentTime();	
	data[0].Format("%d", timer.GetYear());
	if(timer.GetMonth() < 10)		data[1].Format("0%d", timer.GetMonth());
	else		data[1].Format("%d", timer.GetMonth());
	if(timer.GetDay() < 10)		data[2].Format("0%d", timer.GetDay());
	else		data[2].Format("%d", timer.GetDay());
	if(timer.GetHour() < 10)		data[3].Format("0%d", timer.GetHour());
	else		data[3].Format("%d", timer.GetHour());
	if(timer.GetMinute() < 10)		data[4].Format("0%d", timer.GetMinute());
	else		data[4].Format("%d", timer.GetMinute());
	if(timer.GetSecond() < 10)		data[5].Format("0%d", timer.GetSecond());
	else		data[5].Format("%d", timer.GetSecond());

	CString strLot;
	strLot = ConvertCharToStr(cLotID);
	if(strLot=="")strLot = "NONE";

	strpath.Format("C:\\Glim\\Log\\");
	CreateDirectory(strpath,NULL);
	strpath.Format("C:\\Glim\\Log\\%s\\",strLot);
	CreateDirectory(strpath,NULL);

	if(flag == 0)
	{
		if(nCam==0){
			filename.Format("%s%sT_Raw.txt",strpath,pDoc->m_data.m_strComName);
			strpc.Format("%sT",pDoc->m_data.m_strComName);//.Right(3);
		}
		else{
			filename.Format("%s%sB_Raw.txt",strpath,pDoc->m_data.m_strComName);
			strpc.Format("%sB",pDoc->m_data.m_strComName);//.Right(3);
		}	
	}
	else
		filename.Format("%s%s_Mark.txt",strpath,pDoc->m_data.m_strComName);

	nLine = pDoc->m_data.m_nVisionLine;
	pDoc->m_data.m_dStartPos[nCam] = pDoc->m_data.m_dEndPos[nCam] = 0;

	frame = pDoc->m_nTotalIns[nCam];

	//20161111 원본
	//strtmp.Format("%s%s%s%s%s%s\t%s\t%d\t%s\t%2.2f\t%d\t%d\t%2.2f\t%2.2f\t%2.2f\t%2.2f\t%s\t%2.2f\t%2.2f\t%2.2f\t%2.2f\t%2.2f",
	//기존
	//년월일시분초	LotNo	Frame	Comname		notuse	defectcount	defectclass	posx		posy		sizex	sizey	imagepath	notuse	thup	thdn dummy

	//수정
	//년월일시분초	Lotno	Frame	name	LineCount		class	pos			Value	data1	data2	class	pos	vlaue 	data1	data2  ........
	//년월일시분초	abcd111	100	701A		2					edge	100mm		80				0			0		wb		120	70			0			0
	//w->b b->w edge
	//edge w->b


	strtime.Format("%s%s%s%s%s%s",data[0],data[1],data[2],data[3],data[4],data[5]);
	int nCount1 = pDoc->m_data.m_nLineCount1[nCam];
	int nc1 = 0;
	double d1=0,doffsetScale=0.002485;
	int nCalPos = 0;
	for(int k=0;k<MOD_COUNT;k++){
		strtmp2 = "";
		nc1 = 0;
		for(int i=0;i<nCount1;i++){
			nCalPos = pDoc->m_data.m_dLineEdgeData2[nCam][k][i];
			doffsetScale = pDoc->m_data.m_dCalXPos[nCam][nCalPos+1]-pDoc->m_data.m_dCalXPos[nCam][nCalPos];

			d1 = pDoc->m_data.m_dCalXPos[nCam][nCalPos] +(pDoc->m_data.m_dLineEdgeData2[nCam][k][i]-nCalPos)*doffsetScale +   pDoc->m_data.m_dCalibSttX[nCam]+ pDoc->m_data.m_dCalTol[nCam];
			if(pDoc->m_data.m_strDefectName[nCam][i] == "")pDoc->m_data.m_strDefectName[nCam][i] = "0";
			strtmp1.Format("%.d\t%.2f\t%.1f\t%.1f\t%.1f\t%s\t",pDoc->m_data.fpDefectType[nCam][i],d1,pDoc->m_data.m_dEdgeValue1[nCam][i],pDoc->m_data.m_dEdgeValue2[nCam][i],pDoc->m_data.m_dLineEdgeData2[nCam][k][i],pDoc->m_data.m_strDefectName[nCam][i]);
			strtmp2 += strtmp1;
			nc1++;
		}
		strtmp.Format("%s\t%s\t%d\t%s\t%d\t%s",strtime,strLot,frame,strpc,nc1,strtmp2);
		if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
		{		
			if(file.Open(filename, CFile::modeCreate|CFile::modeWrite|CFile::typeText))
			{
				file.WriteString(strtmp);
				file.Close();
			}
		}
		else
		{
			file.SeekToEnd();
			file.WriteString("\n");
			file.WriteString(strtmp);
			file.Close(); 
		}
	}
	//전체 data기록
	strtmp2 = "";
	nc1 = 0;
	for(int i=0;i<nCount1;i++){
		nCalPos = pDoc->m_data.m_dLineEdgeData1[nCam][i];
		doffsetScale = pDoc->m_data.m_dCalXPos[nCam][nCalPos+1]-pDoc->m_data.m_dCalXPos[nCam][nCalPos];

		d1 = pDoc->m_data.m_dCalXPos[nCam][nCalPos] +(pDoc->m_data.m_dLineEdgeData1[nCam][i]-nCalPos)*doffsetScale +   pDoc->m_data.m_dCalibSttX[nCam]+ pDoc->m_data.m_dCalTol[nCam];
		if(pDoc->m_data.m_strDefectName[nCam][i] == "")pDoc->m_data.m_strDefectName[nCam][i] = "0";
		strtmp1.Format("%.d\t%.2f\t%.1f\t%.1f\t%.1f\t%s\t",pDoc->m_data.fpDefectType[nCam][i],d1,pDoc->m_data.m_dEdgeValue1[nCam][i],pDoc->m_data.m_dEdgeValue2[nCam][i],pDoc->m_data.m_dLineEdgeData1[nCam][i],pDoc->m_data.m_strDefectName[nCam][i]);
		strtmp2 += strtmp1;
		nc1++;
	}
	strtmp.Format("%s\t%s\t%d\t%s\t%d\t%s",strtime,strLot,frame,strpc,nc1,strtmp2);
	if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
	{		
		if(file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText))
		{
			file.WriteString(strtmp);
			file.Close();
		}
	}
	else
	{
		file.SeekToEnd();
		file.WriteString("\n");
		file.WriteString(strtmp);
		file.Close(); 
	}


//	pData->m_dLineEdgeData1[nCam][nc1] = npos1;// i;
//	pData->m_dEdgeValue1[nCam][nc1] = nMax;// pData->m_nProjectX[nCam][i]-pData->m_nProjectX[nCam][i+4];


}

void CVisWebView::OnBnClickedButton6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	g_frame_num++;
	Inspect(2);
}

void CVisWebView::OnBnClickedBtnGetProfile3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	LoadImage2();
}

void DrawBMP(LPCTSTR lpszFileName, CDC *pDC, int nX, int nY, DWORD dwRop)
{
	CDC         memDC;
	CBitmap     bmp, *pOldBmp;
	HBITMAP     hBMP;
	BITMAP      bm;

	hBMP = (HBITMAP)LoadImage(NULL, lpszFileName, 
		IMAGE_BITMAP, 0, 0, 
		LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
//0912
// 	bmp.Attach(hBMP);
// 	bmp.GetBitmap(&bm);
// 	memDC.CreateCompatibleDC(pDC);
// 	pOldBmp = memDC.SelectObject(&bmp);
// 	pDC->BitBlt(nX, nY, bm.bmWidth, bm.bmHeight, &memDC, 0, 0, dwRop);
// 	memDC.SelectObject(pOldBmp);

} 




void CVisWebView::fnWriteData2() 
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CStdioFile   file;
	CString filename;
	CString strtmp,str,strTitle,strpath,strOkNg,strpc,strtmp1,strtmp2,strtmp3,strtmp4,strtmp5,strtmp6,strtime;
	CString txtscr,txtdst;
	int nPcno =0;
	int nLine =0;
	//날자 LotNo. Frame	DefectCount	Defect-Class	x-Pos	Y-Pos	X-Size	Y-Size	ImagePath
	//////////////
	CString data[6];
	CTime timer=CTime::GetCurrentTime();	
	data[0].Format("%d", timer.GetYear());
	if(timer.GetMonth() < 10)		data[1].Format("0%d", timer.GetMonth());
	else		data[1].Format("%d", timer.GetMonth());
	if(timer.GetDay() < 10)		data[2].Format("0%d", timer.GetDay());
	else		data[2].Format("%d", timer.GetDay());
	if(timer.GetHour() < 10)		data[3].Format("0%d", timer.GetHour());
	else		data[3].Format("%d", timer.GetHour());
	if(timer.GetMinute() < 10)		data[4].Format("0%d", timer.GetMinute());
	else		data[4].Format("%d", timer.GetMinute());
	if(timer.GetSecond() < 10)		data[5].Format("0%d", timer.GetSecond());
	else		data[5].Format("%d", timer.GetSecond());

	CString strLot;
	strLot = ConvertCharToStr(cLotID);
	if(strLot=="")strLot = "NONE";

	strpath.Format("C:\\Data\\");
	CreateDirectory(strpath,NULL);//년월일
	strpath.Format("C:\\Data\\Log\\");
	CreateDirectory(strpath,NULL);//년월일
	strpath.Format("C:\\Data\\Log\\%s\\",data[0]);
	CreateDirectory(strpath,NULL);//년월일
	strpath.Format("C:\\Glim\\Log\\%s\\%s\\",data[0],strLot);
	CreateDirectory(strpath,NULL);

	filename.Format("%s%s_EdgeData.csv",strpath,pDoc->m_data.m_strComName);

	nLine = pDoc->m_data.m_nVisionLine;
	int frame = pDoc->m_nTotalIns[0];
	strtmp1 = strtmp2 = strtmp3 = strtmp4 =strtmp5=strtmp6= "";

	CString sttrtile1,sttrtile2,sttrtile3,sttrtile4,sttrtile5,sttrtile6;
	strtime.Format("%s년%s월%s일%s시%s분%s초",data[0],data[1],data[2],data[3],data[4],data[5]);
	int nCount1 = pDoc->m_data.m_nLineCount1[0];
	int nc1 = 0;
	double d1=0,doffsetScale=0.002485;
	int nCalPos = 0;
	int nLineCount = 0;
	double d2=0,d3;
	for(int i=0;i<MAX_CAMERAS;i++){
		nLineCount += pDoc->m_data.m_nLineCount1[i];

		for(int j=0;j< pDoc->m_data.m_nLineCount1[i];j++){
			int nindex = j;
			if(i==2){
				nindex = pDoc->m_data.m_nLineCount1[i]-j-1;
			}
			d1 = pDoc->m_data.m_fReturnX[i][nindex];
			if(d2>0)
				d3 = d1-d2;
			strtmp1.Format(",%.2f",d1);
			strtmp2 += strtmp1;
			if(pDoc->m_data.m_dLineEdgeData3[i][nindex]==0)return;
			strtmp3.Format(",%.2f",pDoc->m_data.m_dLineEdgeData3[i][nindex]+CAM_WIDTH_CIS*i);
			strtmp4 += strtmp3;
			if(d2>0){
				strtmp5.Format(",%.2f",d3);
				strtmp6 += strtmp5;

			}
			d2 = d1;
		}
	}
	for(int i=0;i<nLineCount;i++){
		sttrtile1.Format(",픽셀%d",i+1);
		sttrtile2.Format(",거리mm%d",i+1);
		if(i<nLineCount-1){
			sttrtile3.Format(",폭mm%d",i+1);
			sttrtile6 += sttrtile3;
		}
		sttrtile4 += sttrtile1;
		sttrtile5 += sttrtile2;
		
	}
	strTitle.Format("년월일시분초,LotID,FrameNo,LineCount%s%s%s",sttrtile4,sttrtile5,sttrtile6);

	strtmp.Format("%s,%s,%d,%d%s%s%s,",strtime,strLot,frame,nLineCount,strtmp4,strtmp2,strtmp6);
	if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
	{		
		if(file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText))
		{
			file.WriteString(strTitle);
			file.WriteString("\n");
			file.WriteString(strtmp);
			file.Close();
		}
	}
	else
	{
		file.SeekToEnd();
		file.WriteString("\n");
		file.WriteString(strtmp);
		file.Close(); 
	}
}
void CVisWebView::RedrawMap()
{

	CDC *pDC = GetDC();

	DrawGridLine2(pDC, m_nPosCount);			

	ReleaseDC(pDC);
}

void CVisWebView::DrawGridLine2(CDC *pDC, int nWidthCnt)
{
	if(nWidthCnt <= 1 || nWidthCnt > 60 ){
		return;
	}
	int marginX = 60;
	int marginY = 70;
	int nCellWidth = (m_rtArea.Width()-(marginX*2)) / (nWidthCnt-1);
	int nCellHeight = m_rtArea.Height()-(marginY*2);
//	m_rtArea.OffsetRect(1,220);

	int width = m_rtArea.Width();
	int height = m_rtArea.Height();

	int offsetX = 0;
	int offsetY = 500;

	CString str;

	 	CPen pen;
	 	CBrush brush;
	 	CPen* oldPen;
	 	CBrush* oldBrush;
	//Rect만들기
	//CRect* rtRect = new CRect[nWidthCnt];
	double dRatio = 0.3;


	for(int i=0;i<nWidthCnt;i++){
		CPoint pos;
		if(i%2 ==0){
			//pos.x = nCellWidth*i +nCellWidth-(nCellWidth*0.5) + offsetX;
			pos.x = nCellWidth*i;
			pos.x += ((nCellWidth*dRatio));	
		}
		else{
			//pos.x = nCellWidth*i+nCellWidth-(nCellWidth*0.5) + offsetX;
			pos.x = nCellWidth*i;

			pos.x -= ((nCellWidth*dRatio));
		}
		pos.y = height*0.5+offsetY;
		str.Format("%0.2f", m_dCellPos[i]);
		pDC->TextOut(pos.x - 12, pos.y - 60, str);
	}

	for(int i=0;i<nWidthCnt-1;i++){
		CPoint pos;
		pos.x = nCellWidth*i+nCellWidth-(nCellWidth*0.5) + offsetX;
		pos.y = height*0.5+offsetY;
		CRect destRect;
		destRect.SetRect(pos.x - (nCellWidth*0.5), pos.y - (nCellHeight*0.8), pos.x + (nCellWidth*0.5), pos.y + (nCellHeight*0.8));

		// 색상선택
		if(i%2 ==0){
			 			pen.CreatePen( PS_DOT, 3, GRAY );    
			 			brush.CreateSolidBrush( GRAY ); 
			destRect.InflateRect(-(destRect.Width()*dRatio), 0);
		}
		else{
			 			pen.CreatePen( PS_DOT, 3, BLACK );    
			 			brush.CreateSolidBrush( BLACK );
			destRect.InflateRect(+(destRect.Width()*dRatio), 0);
		}

		 		oldPen = (CPen*)pDC->SelectObject( &pen );
		 		oldBrush = (CBrush*)pDC->SelectObject( &brush );
		pDC->Rectangle(destRect);

		pos.x = nCellWidth*i+nCellWidth-(nCellWidth*0.5) + offsetX;
		pos.y = height*0.5;

		str.Format("%0.2f", m_dCellWidth[i]);
		//pDC->TextOut(pos.x - (nCellWidth*0.5) - 12, pos.y - 50, str);
		pDC->TextOut(pos.x - 15, pos.y - 9+offsetY, str);

		// 	
		  		pen.DeleteObject();
		  		brush.DeleteObject();
	}

		pDC->SelectObject( oldPen );
		pDC->SelectObject( oldBrush );

	//delete pGrid;	

	//delete[] rtRect;

}

void CVisWebView::BadImageShift(int nCam,BYTE * fm,BOOL bchange,CString defectname)
{
	if(bchange){
		for(int i=13;i>=0;i--){
			memcpy(m_pDefectImage[i+1]->GetImagePtr(),m_pDefectImage[i]->GetImagePtr(),BAD_IMG_HEIGHT*BAD_IMG_WIDTH);
			strcpy_s(m_charLbLotInfo[i+1], 100, m_charLbLotInfo[i]); 
			
			m_lbDefectInfo[i+1].SetText(ConvertCharToStr(m_charLbLotInfo[i+1]));
			
			//m_strLbLotInfo[i+1] = m_strLbLotInfo[i];
			//m_lbDefectInfo[i+1].SetText(m_strLbLotInfo[i+1]);
		}
		memcpy(m_pDefectImage[0]->GetImagePtr(),fm,BAD_IMG_HEIGHT*BAD_IMG_WIDTH);


		sprintf(m_charLbLotInfo[0], "%s", defectname);
		m_lbDefectInfo[0].SetText(m_charLbLotInfo[0]);
		
		//m_strLbLotInfo[0] = defectname;
		//m_lbDefectInfo[0].SetText(m_strLbLotInfo[0]);
	}
}

// void CVisWebView::BadImageShift(int nCam,BYTE * fm,BOOL bchange,CString defectname)
// {
// 	if(bchange){
// 		for(int i=13;i>=0;i--){
// 			memcpy(m_pDefectImage[i+1]->GetImagePtr(),m_pDefectImage[i]->GetImagePtr(),BAD_IMG_HEIGHT*BAD_IMG_WIDTH);
// 			m_strLbLotInfo[i+1] = m_strLbLotInfo[i];
// 			m_lbDefectInfo[i+1].SetText(m_strLbLotInfo[i+1]);
// 		}
// 		memcpy(m_pDefectImage[0]->GetImagePtr(),fm,BAD_IMG_HEIGHT*BAD_IMG_WIDTH);
// 		m_strLbLotInfo[0] = defectname;
// 		m_lbDefectInfo[0].SetText(m_strLbLotInfo[0]);
// 	}
// }
void CVisWebView::OnBnClickedButton7()
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	UpdateData(TRUE);
	pDoc->m_data.m_nDualNotIns = m_dXLineSkip;

	pDoc->m_data.m_dLineScratch = m_dLineScratch;
	pDoc->m_data.m_dDefectSize = m_dDefectSize;
	int N;
	//m_dSlope
	pDoc->m_data.m_dSlope = m_dSlope;
	//m_nThWhite
	pDoc->m_data.m_nThWhite3 = m_nThWhite;
	pDoc->m_data.m_nThBlack3 = m_nThBlack;
	int nCam = m_nSelectCam;
	pDoc->m_data.m_nNotInsArea[nCam] = m_nNotInsAreaView;
	pDoc->m_data.m_nFindEdge[nCam] = m_nNotInsAreaView;
	//	pDoc->m_data.m_dXlineSkip = m_dXLineSkip;
	//	pDoc->m_data.m_nExposeTime = (m_nExpose*25);

	pDoc->m_data.m_nInsMethod[nCam] = m_nInsMethod;
	pDoc->m_data.m_nTacXpos[nCam] = m_nTacX;

	m_bDefectSaveStats = TRUE;
}

void CVisWebView::ShowCoatTitle(int nCount)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	for(int i=0;i<MAX_LENGTH;i++){
		int nIndex = IDC_STATIC_COAT_TITLE1+i;
		if(i<nCount)		GetDlgItem(nIndex)->ShowWindow(1);//and
		else				GetDlgItem(nIndex)->ShowWindow(0);//and
		nIndex = IDC_STATIC_COAT_LEN1+i;
		if(i<nCount)		GetDlgItem(nIndex)->ShowWindow(1);//and
		else				GetDlgItem(nIndex)->ShowWindow(0);//and
		if(m_strComputerName.Find("BACK")>=0  ||  pDoc->m_data.m_strComName.Mid(9,1)=="B"){
			nIndex = IDC_STATIC_TOP_COAT_LEN1+i;
			if(i<nCount)		GetDlgItem(nIndex)->ShowWindow(1);//and
			else				GetDlgItem(nIndex)->ShowWindow(0);//and
		}
	}
}

void CVisWebView::ShowTopLength(int nCount)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	for(int i=0;i<MAX_LENGTH;i++){
		if(m_strComputerName.Find("BACK")>=0  ||  pDoc->m_data.m_strComName.Mid(9,1)=="B"){
			int nIndex = IDC_STATIC_TOP_COAT_LEN1+i;
			if(i<nCount)		GetDlgItem(nIndex)->ShowWindow(1);//and
			else				GetDlgItem(nIndex)->ShowWindow(0);//and
		}
	}
	if(nCount==0){
		m_lbTopTitle.ShowWindow(0);
//		m_lbMisMatchTitle.ShowWindow(0);
	}
	else{
		m_lbTopTitle.ShowWindow(1);
//		m_lbMisMatchTitle.ShowWindow(1);
	}
}


#define TOTAL_LOG_LIST_COL		30

void CVisWebView::AddtoList(CString strData,int mode,BOOL bWrite)
{
	CString str;
	CTime time = CTime::GetCurrentTime();
	strData = time.Format("[%H:%M:%S]") + strData;

// 	if(mode==1)
// 		m_Multi.WriteLog(strData);
// 	else if(mode==2)
// 		WriteMesLog(strData);//mes
// 	else if(mode==3)
// 		m_Multi.WriteCpuLog(strData);//cpu
// 	else if(mode==4)
// 		WriteInspLog(strData,strData);//cpu
// 	else{
// 		m_Multi.WriteLog(strData);
// 		WriteMesLog(strData);//mes
// 	}

	WriteLog(strData);
	///*	
	m_log2.InsertString(-1,strData);
	int x = m_log2.GetCount();
	m_log2.SetTopIndex(x-1);
	m_log2.SendMessage(WM_VSCROLL,SB_BOTTOM);
	if(x > TOTAL_LOG_LIST_COL)
	{
		m_log2.DeleteString(0);
		m_log2.SetCurSel(TOTAL_LOG_LIST_COL-1);
	}
	//*/
	
}
void CVisWebView::AddtoInsLog(CString strData,BOOL bWrite)
{
	CString str;
	CTime time = CTime::GetCurrentTime();
	strData = time.Format("[%H:%M:%S]") + strData;
	///*	
	WriteLog1(strData);
	m_InspLog1.InsertString(-1,strData);
	int x = m_InspLog1.GetCount();
	m_InspLog1.SetTopIndex(x-1);
	m_InspLog1.SendMessage(WM_VSCROLL,SB_BOTTOM);
	if(x > TOTAL_LOG_LIST_COL)
	{
		m_InspLog1.DeleteString(0);
		m_InspLog1.SetCurSel(TOTAL_LOG_LIST_COL-1);
	}
	//*/
	
}

void CVisWebView::WriteLengthData(double dMachineLen)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();


	CString data[6];
	CTime timer=CTime::GetCurrentTime();	
	data[0].Format("%d", timer.GetYear());
	if(timer.GetMonth() < 10)		data[1].Format("0%d", timer.GetMonth());
	else		data[1].Format("%d", timer.GetMonth());
	if(timer.GetDay() < 10)		data[2].Format("0%d", timer.GetDay());
	else		data[2].Format("%d", timer.GetDay());
	if(timer.GetHour() < 10)		data[3].Format("0%d", timer.GetHour());
	else		data[3].Format("%d", timer.GetHour());
	if(timer.GetMinute() < 10)		data[4].Format("0%d", timer.GetMinute());
	else		data[4].Format("%d", timer.GetMinute());
	if(timer.GetSecond() < 10)		data[5].Format("0%d", timer.GetSecond());
	else		data[5].Format("%d", timer.GetSecond());
	CStdioFile   file;
	CString filename;
	CString strpath;
	CString str,strtmp1,strtmp2,strtmp,strtime;
	int nLen = dMachineLen;
	int nLen1 = nLen %100;
	CString strLot;
	strLot = ConvertCharToStr(cLotID);
	if(strLot=="")strLot = "NONE";

// 	if(pDoc->m_data.m_bUseCLog){
// 		strpath.Format("C:\\Glim\\LotData\\");
// 		CreateDirectory(strpath,NULL);	
// 		strpath.Format("C:\\Glim\\LotData\\%s\\",strLot);
// 		CreateDirectory(strpath,NULL);	
// 	}
// 	else{
		strpath.Format("D:\\Data\\LotData\\");
		CreateDirectory(strpath,NULL);	
		strpath.Format("D:\\Data\\LotData\\%s%s%s\\",data[0],data[1],data[2]);
		CreateDirectory(strpath,NULL);	
		strpath.Format("D:\\Data\\LotData\\%s%s%s\\%s\\",data[0],data[1],data[2],strLot);
		CreateDirectory(strpath,NULL);	
//	}
	filename.Format("%s%s_%d.txt",strpath,pDoc->m_data.m_strComName,nLen);
// 설비길이 , Frame , len1,len2,len3....
	int nc1 = 0;
	for(int k=0;k<MAX_CAMERAS;k++){
		int nCount1 = pDoc->m_data.m_nLineCount1[k];
		for(int i=0;i<nCount1;i++){
			strtmp1.Format("%.2lf\t",pDoc->m_data.m_fReturnX[k][i]);
			strtmp2 += strtmp1;
			nc1++;
		}
	}
	strtime.Format("%s%s%s%s%s%s",data[0],data[1],data[2],data[3],data[4],data[5]);
	//////////////time lot 설비길이  카운트  
	strtmp.Format("%s\t%s\t%.2f\t%d\t%s",strtime,strLot,dMachineLen,nc1,strtmp2);

	try{
		g_Mutex.Lock();                    // 뮤텍스를 잠근다.
		if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
		{		
			m_nTextWriteCount = 0;
			file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText);
			file.WriteString(strtmp);
			file.WriteString("\n");	
			file.Close();
		}
		else
		{
			file.SeekToEnd();			
			file.WriteString(strtmp);
			file.WriteString("\n");
			file.Close(); 
		}	
		pDoc->m_data.m_strMatchData[1][nLen1][m_nTextWriteCount] = strtmp;//Data Input
		m_nTextWriteCount++;
		g_Mutex.Unlock();                 // 뮤텍스를 풀어준다.
	}
	catch(CFileException)
	{
		//AfxMessageBox( "File Open failed" );
	}
	catch(...)
	{
		//AfxMessageBox( "File Open failed2~" );
	}
}

void CVisWebView::ReadLengthData(CString strfile,CString strLot,CString strcom,int nreadlen)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CString data[6];
	CTime timer=CTime::GetCurrentTime();	
	data[0].Format("%d", timer.GetYear());
	if(timer.GetMonth() < 10)		data[1].Format("0%d", timer.GetMonth());
	else		data[1].Format("%d", timer.GetMonth());
	if(timer.GetDay() < 10)		data[2].Format("0%d", timer.GetDay());
	else		data[2].Format("%d", timer.GetDay());
	if(timer.GetHour() < 10)		data[3].Format("0%d", timer.GetHour());
	else		data[3].Format("%d", timer.GetHour());
	if(timer.GetMinute() < 10)		data[4].Format("0%d", timer.GetMinute());
	else		data[4].Format("%d", timer.GetMinute());
	if(timer.GetSecond() < 10)		data[5].Format("0%d", timer.GetSecond());
	else		data[5].Format("%d", timer.GetSecond());
	CStdioFile   file;
	CString filename;
	CString strpath;
	CString str,strtmp1,strtmp2,strtmp,strtime;
	if(m_strComputerName.Mid(8,1)=="M")
		nreadlen += 1;
	int nLen = nreadlen;
	int nLen1 = nLen%100;
	int nLen2 = (nLen+1)%100;
	////c:\\glim\\data\\log\\년\\lotno\\pcname_생산미터.csv
//	strdst1.Format("c:\\Glim\\LotDataTmp\\%s\\Top\\*_%d.csv",pDoc->m_str_lot,nLen);

	strpath.Format("C:\\Glim\\LotDataTmp\\%s\\Top\\",strLot);
	filename = strfile;//.Format("%s%s_%d.txt",strpath,strcom,nLen);

	//////////////time lot 설비길이  카운트  
	CFileFind finder;
	BOOL IsFind;

	IsFind = finder.FindFile(filename);
	if(IsFind){
		if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
		{		
	//File Open fail
			strtmp1.Format("File Open Fail-%s",filename);
			AddtoList(strtmp1,0);
		}
		else
		{
			file.ReadString(strtmp);//0번은 타이틀
			for(int k=0;k<9;k++){
				file.ReadString(strtmp);
				if(strtmp=="")break;
				pDoc->m_data.m_strMatchData[0][nLen1][k] = strtmp;//	strTitle.Format("년월일시분초,PC,LotID,Meter,FrameNo,Scale,LineCount%s",sttrtile4);//,sttrtile5,sttrtile6);
				pDoc->m_data.m_strMatchData[0][nLen2][k] = strtmp;//	strTitle.Format("년월일시분초,PC,LotID,Meter,FrameNo,Scale,LineCount%s",sttrtile4);//,sttrtile5,sttrtile6);
				fnDataPut(strtmp,nLen1,k, -1); //ncount 1M 내에 몇번째 텍스트인지
			}
			file.Close(); 
		}	
	}
	else{
		strtmp1.Format("File Not Found-%s",filename);
		AddtoList(strtmp1,0);
	}

}

void CVisWebView::ReadMismatchData(CString strfile,CString strLot)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CStdioFile   file;
	CString filename;
	CString str,strtmp1,strtmp2,strtmp,strtime;

	filename = strfile;//.Format("%s%s_%d.txt",strpath,strcom,nLen);

	//////////////time lot 설비길이  카운트  
	CFileFind finder;
	BOOL IsFind;

	IsFind = finder.FindFile(filename);
	if(IsFind){
		if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
		{		
			//File Open fail
			strtmp1.Format("File Open Fail-%s",filename);
			AddtoList(strtmp1,0);
		}
		else
		{
			for(int k=0;k<100;k++){
				file.ReadString(strtmp);
				if(strtmp=="")break;
				if(m_strComputerName.Mid(8,1) == "M")
					fnDataPut2(strtmp,0,k, -1); //ncount 1M 내에 몇번째 텍스트인지
				else				fnDataPut1(strtmp,0,k, -1); //ncount 1M 내에 몇번째 텍스트인지
			}
			file.Close(); 
			pDoc->m_data.m_nReadCount = 0;
		}	
	}
	else{
		strtmp1.Format("File Not Found-%s",filename);
		AddtoList(strtmp1,0);
	}

}
void CVisWebView::ReadMismatchData1(CString strfile,CString strLot)//mismatch bacck에서 head back 데이터 리드
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CStdioFile   file;
	CString filename;
	CString str,strtmp1,strtmp2,strtmp,strtime;

	filename = strfile;//.Format("%s%s_%d.txt",strpath,strcom,nLen);

	//////////////time lot 설비길이  카운트  
	CFileFind finder;
	BOOL IsFind;
	int nLen = pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck];//   m_nReadLength;//m_dMachineLength;
	int nLen1 = nLen%100;
	int nLen2 = (nLen+1)%100;
	int nLen3 = nLen1;
	IsFind = finder.FindFile(filename);
	CString strolddata;
	if(IsFind){
		if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
		{		
			//File Open fail
			strtmp1.Format("File Open Fail-%s",filename);
			AddtoList(strtmp1,0);
		}
		else
		{
			int ncount1 = 0;
			for(int k=0;k<100;k++){//10개 data가 있음
				file.ReadString(strtmp);
				if(ncount1>19){
					file.Close();
					return;
				}
				if(strtmp==""){
					if(ncount1<10){
						for(int k=ncount1;k<10;k++){
							nLen3 = (nLen1)%100;
							pDoc->m_data.m_strFullLineData[nLen3] = strolddata;
							nLen1++;
							ncount1++;
						}
					}
					break;
				}
				if(m_strComputerName.Mid(8,1) == "M"){
					if(k>19){
						file.Close();
						return;
					}
					nLen3 = (nLen1)%100;
					fnDataPut3(strtmp,nLen3,k, -1); //ncount 1M 내에 몇번째 텍스트인지
//					if(k==0)
					pDoc->m_data.m_strFullLineData[nLen3] = strtmp;
					nLen1++;
				}
				strolddata = strtmp;
				ncount1++;
			}
			file.Close(); 
			pDoc->m_data.m_nReadCount = 0;
		}	
	}
	else{
		strtmp1.Format("File Not Found-%s",filename);
		AddtoList(strtmp1,0);
	}

}

void CVisWebView::WriteLog(CString str)
{
	CTime time = CTime::GetCurrentTime();

	CString kk1 = time.Format("%Y%m");
	CString strpath;
	strpath.Format("c:\\Glim\\Log\\");
	CreateDirectory(strpath,NULL);
	strpath.Format("c:\\Glim\\Log\\%s\\",kk1);
	CreateDirectory(strpath,NULL);

	CString strFile;
	strFile.Format("%s%s_LOG_%s.txt",strpath,time.Format("%Y%m%d"),m_strComputerName);

	FILE *fp;
	fp = fopen((LPCSTR)strFile, "a");

	if(!fp)
		return;
	char* buf = new char[str.GetLength()+1];
	memcpy(buf, str.LockBuffer(), str.GetLength());
	buf[str.GetLength()] = '\0';

	fputs(buf, fp);
	fputs("\n",fp);
	delete []buf;
	fclose(fp);
}

void CVisWebView::WriteLog1(CString str)
{
	CTime time = CTime::GetCurrentTime();

	CString kk1 = time.Format("%Y%m");
	CString strpath;
	strpath.Format("c:\\Glim\\Log\\");
	CreateDirectory(strpath,NULL);
	strpath.Format("c:\\Glim\\Log\\%s\\",kk1);
	CreateDirectory(strpath,NULL);

	CString strFile;
	strFile.Format("%s%sInsp_LOG_%s.txt",strpath,time.Format("%Y%m%d"),m_strComputerName);

	FILE *fp;
	fp = fopen((LPCSTR)strFile, "a");

	if(!fp)
		return;
	char* buf = new char[str.GetLength()+1];
	memcpy(buf, str.LockBuffer(), str.GetLength());
	buf[str.GetLength()] = '\0';

	fputs(buf, fp);
	fputs("\n",fp);
	delete []buf;
	fclose(fp);
}
void CVisWebView::CopyMismatchFile()
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CString strsrc1,strsrc2,strdst1,strdst2,strtmp,strLot;
	strLot = ConvertCharToStr(cLotID);
//	CString strLot;
//	strLot = ConvertCharToStr(cLotID);
	if(strLot=="")strLot = "NONE";

	CString data[6];
	CTime timer=CTime::GetCurrentTime();	
	data[0].Format("%d", timer.GetYear());
	if(timer.GetMonth() < 10)		data[1].Format("0%d", timer.GetMonth());
	else		data[1].Format("%d", timer.GetMonth());
	if(timer.GetDay() < 10)		data[2].Format("0%d", timer.GetDay());
	else		data[2].Format("%d", timer.GetDay());
	if(timer.GetHour() < 10)		data[3].Format("0%d", timer.GetHour());
	else		data[3].Format("%d", timer.GetHour());
	if(timer.GetMinute() < 10)		data[4].Format("0%d", timer.GetMinute());
	else		data[4].Format("%d", timer.GetMinute());
	if(timer.GetSecond() < 10)		data[5].Format("0%d", timer.GetSecond());
	else		data[5].Format("%d", timer.GetSecond());

	CTime ttime=CTime::GetCurrentTime();	
	CString kk = ttime.Format("%Y%m%d");

// 	if(pDoc->m_data.m_bUseCLog){
// 		strdst1.Format("c:\\Glim\\LotDataTmp\\");
// 		CreateDirectory(strdst1,NULL);	
// 		strdst1.Format("c:\\Glim\\LotDataTmp\\%s\\",kk);
// 		CreateDirectory(strdst1,NULL);	
// 		strdst1.Format("c:\\Glim\\LotDataTmp\\%s\\%s\\",kk,strLot);
// 		CreateDirectory(strdst1,NULL);	
// 		strdst1.Format("c:\\Glim\\LotDataTmp\\%s\\%s\\Top\\",kk,strLot);
// 		CreateDirectory(strdst1,NULL);	
// 		strdst2 = strdst1;
// 		strdst2.Format("c:\\Glim\\LotDataTmp\\%s\\%s\\Top\\Backup\\",kk,strLot);
// 		CreateDirectory(strdst2,NULL);	
// 	}
// 	else{
		strdst1.Format("D:\\Data\\");
		CreateDirectory(strdst1,NULL);	
		strdst1.Format("D:\\Data\\LotDataTmp\\");
		CreateDirectory(strdst1,NULL);	
		strdst1.Format("D:\\Data\\LotDataTmp\\%s\\",kk);
		CreateDirectory(strdst1,NULL);	
		strdst1.Format("D:\\Data\\LotDataTmp\\%s\\%s\\",kk,strLot);
		CreateDirectory(strdst1,NULL);	
		strdst1.Format("D:\\Data\\LotDataTmp\\%s\\%s\\Top\\",kk,strLot);
		CreateDirectory(strdst1,NULL);	
		strdst2 = strdst1; 
		strdst2.Format("D:\\Data\\LotDataTmp\\%s\\%s\\Top\\Backup\\",kk,strLot);
		CreateDirectory(strdst2,NULL);	
//	}

//현재길이 - offset 길이 (전체길이의 절반정도의 마진을 둔다.
//	Data가 없을시 미스매치를 실시하지 않는다.
	int nLen = pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck]-30;//   m_nReadLength;//m_dMachineLength;
//	if(nLen<=0)		return;
	//자기 이름을 기준으로 top pc 이름을 찾는다.
	CString strToppc;
	if(m_strComputerName.Find("CMI")>=0 ||m_strComputerName.Find("OCH")>=0 || m_strComputerName.Find("OCH")>=0){
		//|| pDoc->m_data.m_nLineSelect%10==2
		//head part   //CMICT01AMT1	//CMICT01CMT1  //CMICT01AHT1 //CMICT01CHT1
		strToppc = m_strComputerName.Left(9)+"T1";		
	}
	else
		strToppc = m_strComputerName.Left(m_strComputerName.Find("BACK"))+ "TOP";

//정해진 길이의 파일만 가져온다.
////c:\\glim\\data\\log\\년\\lotno\\pcname_생산미터.csv		//\\100.0.0.13\Glim\Data\Log\2019\19021917 //
// 	if(pDoc->m_data.m_bUseCLog){
// // 		strsrc1.Format("\\%s\\Glim\\Data\\Log\\%s\\%s\\%s_%d.csv",strToppc,data[0],strLot,strToppc,nLen);
// // 		strdst1.Format("c:\\Glim\\LotDataTmp\\%s%s\\Top\\%s_%d.csv",strLot,strToppc,nLen);
// // 		strdst2.Format("c:\\Glim\\LotDataTmp\\%s\\%s\\Top\\Backup\\%s_%d.csv",strLot,strToppc,nLen);
// 	}
//	else{
		strsrc1.Format("\\\\%s\\Data\\Data\\Log\\%s\\%s%s\\%s\\%s_%d.csv",strToppc,data[0],data[1],data[2],strLot,strToppc,nLen);//check 1104
		strdst1.Format("D:\\Data\\LotDataTmp\\%s\\%s\\Top\\%s_%d.csv",kk,strLot,strToppc,nLen);
		strdst2.Format("D:\\Data\\LotDataTmp\\%s\\%s\\Top\\Backup\\%s_%d.csv",kk,strLot,strToppc,nLen);
//	}
//	if(!CopyFile(strsrc1,strdst1,FALSE)){
	//정해진 길이에 데이터만 가져온다
	double dtime = GetPrecisionTime();
	int nStart,nEnd,ncount1 = 0;
	int ngap1 = 80;//start
	int ngap2 = 50;//end
	int ngap3 = 10;//end2
	if(m_strComputerName.Mid(8,1) == "M"){
		ngap1 = 80;
		ngap2 = 20;
		ngap3 = 0;
	}
	nStart = pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck] - ngap1;//pDoc->m_data.m_nCamDistance;
	if(nStart<0)nStart = 0;
	nEnd = pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck];//nStart+ngap2;
	if(nEnd>=pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck]  )
		nEnd = pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck] -ngap3;
	for(int i=nStart;i<nEnd;i++){
// 		if(pDoc->m_data.m_bUseCLog){
// // 			strsrc1.Format("\\\\%s\\Glim\\Data\\Log\\%s\\%s\\%s_%d.csv",strToppc,data[0],data[1],data[2],strLot,strToppc,i);
// // 			strdst1.Format("c:\\Glim\\LotDataTmp\\%s\\Top\\%s_%d.csv",strLot,strToppc,i);
// // 			strdst2.Format("c:\\Glim\\LotDataTmp\\%s\\Top\\Backup\\%s_%d.csv",strLot,strToppc,i);
// 		}
// 		else{
			strsrc1.Format("\\\\%s\\Data\\Data\\Log\\%s\\%s%s\\%s\\%s_%d.csv",strToppc,data[0],data[1],data[2],strLot,strToppc,i);
			strdst1.Format("D:\\Data\\LotDataTmp\\%s\\%s\\Top\\%s_%d.csv",kk,strLot,strToppc,i);
			strdst2.Format("D:\\Data\\LotDataTmp\\%s\\%s\\Top\\Backup\\%s_%d.csv",kk,strLot,strToppc,i);
//		}
		//	if(!CopyFile(strsrc1,strdst1,FALSE)){
		//정해진 길이에 데이터만 가져온다
		//if(::MoveFile(strsrc1,strdst1)==FALSE)
		if(::CopyFile(strsrc1,strdst1,FALSE)==FALSE)
		{
			strtmp.Format("File copy Fail %s",strsrc1);
//						AddtoList(strtmp,0);
		}
		else{
			::DeleteFile(strsrc1);
			ncount1++;
			ReadLengthData(strdst1,strLot,strToppc,i);//file을 읽고 버퍼에 넣는다.
			//data put
			if(::CopyFile(strdst1,strdst2,FALSE))
				::DeleteFile(strdst1);
		}
	}
//	DeleteFile(strsrc1);
	double dtime1 = GetPrecisionTime();
	strtmp.Format("t%.0f-%d-%d -%d",(dtime1-dtime)*1000,nStart,nEnd,ncount1);//50개 debug mode 180ms
//	AddtoInsLog(strtmp,0);
}
void CVisWebView::CopyMismatchFile1()//back 미스매치 데이커 가져오기
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CString strsrc1,strsrc2,strdst1,strdst2,strtmp,strLot,strdst3;
	strLot = ConvertCharToStr(cLotID);
//	CString strLot;
//	strLot = ConvertCharToStr(cLotID);
	if(strLot=="")strLot = "NONE";
	CString data[6];
	CTime timer=CTime::GetCurrentTime();	
	data[0].Format("%d", timer.GetYear());
	if(timer.GetMonth() < 10)		data[1].Format("0%d", timer.GetMonth());
	else		data[1].Format("%d", timer.GetMonth());
	if(timer.GetDay() < 10)		data[2].Format("0%d", timer.GetDay());
	else		data[2].Format("%d", timer.GetDay());
	if(timer.GetHour() < 10)		data[3].Format("0%d", timer.GetHour());
	else		data[3].Format("%d", timer.GetHour());
	if(timer.GetMinute() < 10)		data[4].Format("0%d", timer.GetMinute());
	else		data[4].Format("%d", timer.GetMinute());
	if(timer.GetSecond() < 10)		data[5].Format("0%d", timer.GetSecond());
	else		data[5].Format("%d", timer.GetSecond());

	CTime ttime=CTime::GetCurrentTime();	
	CString kk = ttime.Format("%Y%m%d");


// 	if(pDoc->m_data.m_bUseCLog){
// 		strdst1.Format("c:\\Glim\\LotDataTmp\\");
// 		CreateDirectory(strdst1,NULL);	
// 		strdst1.Format("c:\\Glim\\LotDataTmp\\%s\\",strLot);
// 		CreateDirectory(strdst1,NULL);	
// 		strdst1.Format("c:\\Glim\\LotDataTmp\\%s\\Mismatch\\",strLot);
// 		CreateDirectory(strdst1,NULL);	
// 		strdst2 = strdst1;
// 		strdst2.Format("c:\\Glim\\LotDataTmp\\%s\\Mismatch\\Move\\",strLot);
// 		CreateDirectory(strdst2,NULL);	
// 	}
// 	else{
 		strdst1.Format("D:\\Data\\LotDataTmp\\");
		CreateDirectory(strdst1,NULL);	
		strdst1.Format("D:\\Data\\LotDataTmp\\%s\\",kk);//년월일
		CreateDirectory(strdst1,NULL);	
		strdst1.Format("D:\\Data\\LotDataTmp\\%s\\%s\\",kk,strLot);
		CreateDirectory(strdst1,NULL);	
		strdst1.Format("D:\\Data\\LotDataTmp\\%s\\%s\\Mismatch\\",kk,strLot);
		CreateDirectory(strdst1,NULL);	
		strdst2 = strdst1;
		strdst3 = strdst1;
		strdst2.Format("D:\\Data\\LotDataTmp\\%s\\%s\\Mismatch\\Move\\",kk,strLot);
		CreateDirectory(strdst2,NULL);	
		strdst3.Format("D:\\Data\\LotDataTmp\\%s\\%s\\Mismatch\\Backup\\",kk,strLot);
		CreateDirectory(strdst3,NULL);	

	//}

	//현재길이 - offset 길이 (전체길이의 절반정도의 마진을 둔다.
	//	Data가 없을시 미스매치를 실시하지 않는다.
	int nLen = pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck]-30;//   m_nReadLength;//m_dMachineLength;
	//	if(nLen<=0)		return;
	//자기 이름을 기준으로 top pc 이름을 찾는다.
	CString strToppc;
	if(m_strComputerName.Find("CMI")>=0 ||m_strComputerName.Find("OCH")>=0){
//|| pDoc->m_data.m_nLineSelect%10==2
		strToppc = m_strComputerName.Left(9)+"B1";		
	}
	else
		strToppc = m_strComputerName.Left(m_strComputerName.Find("TOP"))+ "BACK";

	//정해진 길이의 파일만 가져온다.
	int nStart,nEnd,ncount1 = 0;
	nStart = pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck] - 80;//pDoc->m_data.m_nCamDistance;
	if(nStart<0)nStart = 0;
	nEnd = nStart+50;
	if(m_strComputerName.Mid(8,1)=="M"){
		nStart = pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck]-10;
		nEnd = pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck];

	}
//	double dtime;
	if(nEnd>=pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck]  )
		nEnd = pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck] -10;
	////c:\\glim\\data\\log\\년\\lotno\\pcname_생산미터.csv		//\\100.0.0.13\Glim\Data\Log\2019\19021917
// 	if(pDoc->m_data.m_bUseCLog){
// 	}
// 	else{
		strsrc1.Format("\\\\%s\\Data\\Data\\Log\\%s\\%s%s\\%s\\Move\\",strToppc,data[0],data[1],data[2],strLot);
		//	strsrc1.Format("\\\\%s\\Glim\\Data\\Log\\%s\\%s\\MOVE\\","192.168.0.86",data[0],strLot);//1412
		strdst1.Format("D:\\Data\\LotDataTmp\\%s\\%s\\Mismatch\\",kk,strLot);
		CreateDirectory(strdst1,NULL);	
		strdst2.Format("D:\\Data\\LotDataTmp\\%s\\%s\\Mismatch\\Move\\",kk,strLot);
		CreateDirectory(strdst2,NULL);	
		strdst2.Format("D:\\Data\\LotDataTmp\\%s\\%s\\Mismatch\\Move\\*.csv",kk,strLot);

//	}

	SHFILEOPSTRUCT    shfo;
	WORD        wfunc;
	TCHAR        pszTo[1024] = {0};
	TCHAR        pszFrom[1024] = {0};
	TCHAR        pszTitle[MAX_PATH] = {0};
	wfunc = FO_MOVE;
	memset(pszTo, 0, sizeof(pszTo));   // 중요
	memset(pszFrom, 0, sizeof(pszFrom));
	strcpy(pszTitle, "파일이동");
	strcpy(pszTo, strdst1);
	strcpy(pszFrom , strsrc1);
	ZeroMemory(&shfo, sizeof(shfo));
	shfo.hwnd = AfxGetMainWnd()->m_hWnd;
	shfo.wFunc = wfunc;
	shfo.lpszProgressTitle=pszTitle;
	shfo.pTo=pszTo;
	shfo.pFrom=pszFrom;//FOF_NOCONFIRMATION
	shfo.fFlags = FOF_NOCONFIRMMKDIR|FOF_NOCONFIRMATION|FOF_SILENT|FOF_NOERRORUI;

	int ret = SHFileOperation(&shfo);


	CFileFind ff;
	CString path = strdst2;
	BOOL res = ff.FindFile(path);
	CString strfile3;
//strdst3
	int nc=0;
	while(res)
	{
		res = ff.FindNextFile();

		if (!ff.IsDots() && !ff.IsDirectory()){	//file
			//read
			ReadMismatchData(ff.GetFilePath(),strLot);
			strfile3 = ff.GetFileName();
			strdst3+= strfile3;
//			MoveFile(ff.GetFilePath(),strdst3);
			DeleteFile(ff.GetFilePath());
			nc++	;
		}
		else if (ff.IsDirectory())	//directory
		{
		}
	}

// 	double dtime1 = GetPrecisionTime();
// 	strtmp.Format("t%.0f-%d",(dtime1-dtime)*1000,nc);//50개 debug mode 180ms
//	AddtoInsLog(strtmp,0);
}

void CVisWebView::CopyMismatchFile2()//head back data를 mis 백에서 가져오기
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CString strsrc1,strsrc2,strdst1,strdst2,strtmp,strLot,strdst3;
	strLot = ConvertCharToStr(cLotID);
	//	CString strLot;
	//	strLot = ConvertCharToStr(cLotID);
	if(strLot=="")strLot = "NONE";
	CString data[6];
	CTime timer=CTime::GetCurrentTime();	
	data[0].Format("%d", timer.GetYear());
	if(timer.GetMonth() < 10)		data[1].Format("0%d", timer.GetMonth());
	else		data[1].Format("%d", timer.GetMonth());
	if(timer.GetDay() < 10)		data[2].Format("0%d", timer.GetDay());
	else		data[2].Format("%d", timer.GetDay());
	if(timer.GetHour() < 10)		data[3].Format("0%d", timer.GetHour());
	else		data[3].Format("%d", timer.GetHour());
	if(timer.GetMinute() < 10)		data[4].Format("0%d", timer.GetMinute());
	else		data[4].Format("%d", timer.GetMinute());
	if(timer.GetSecond() < 10)		data[5].Format("0%d", timer.GetSecond());
	else		data[5].Format("%d", timer.GetSecond());

	CTime ttime=CTime::GetCurrentTime();	
	CString kk = ttime.Format("%Y%m%d");


// 	if(pDoc->m_data.m_bUseCLog){
// 		strdst1.Format("c:\\Glim\\LotDataTmp\\");
// 		CreateDirectory(strdst1,NULL);	
// 		strdst1.Format("c:\\Glim\\LotDataTmp\\%s\\",strLot);
// 		CreateDirectory(strdst1,NULL);	
// 		strdst1.Format("c:\\Glim\\LotDataTmp\\%s\\Mismatch\\",strLot);
// 		CreateDirectory(strdst1,NULL);	
// 		strdst2 = strdst1;
// 		strdst2.Format("c:\\Glim\\LotDataTmp\\%s\\Mismatch\\Move\\",strLot);
// 		CreateDirectory(strdst2,NULL);	
// 	}
// 	else{
		strdst1.Format("D:\\Data\\LotDataTmp\\");
		CreateDirectory(strdst1,NULL);	
		strdst1.Format("D:\\Data\\LotDataTmp\\%s\\",kk);//년월일
		CreateDirectory(strdst1,NULL);	
		strdst1.Format("D:\\Data\\LotDataTmp\\%s\\%s\\",kk,strLot);
		CreateDirectory(strdst1,NULL);	
		strdst1.Format("D:\\Data\\LotDataTmp\\%s\\%s\\Mismatch\\",kk,strLot);
		CreateDirectory(strdst1,NULL);	
		strdst2 = strdst1;
		strdst3 = strdst1;
		strdst2.Format("D:\\Data\\LotDataTmp\\%s\\%s\\Mismatch\\HeadBack\\",kk,strLot);//mismatch back에서 할일
		CreateDirectory(strdst2,NULL);	
		strdst3.Format("D:\\Data\\LotDataTmp\\%s\\%s\\Mismatch\\HeadBackup\\",kk,strLot);
		CreateDirectory(strdst3,NULL);	

	//}

	//현재길이 - offset 길이 (전체길이의 절반정도의 마진을 둔다.
	//	Data가 없을시 미스매치를 실시하지 않는다.
	int nLen = pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck]-30;//   m_nReadLength;//m_dMachineLength;
	//	if(nLen<=0)		return;
	//자기 이름을 기준으로 top pc 이름을 찾는다.
	CString strToppc;
	if(m_strComputerName.Find("CMI")>=0 ||m_strComputerName.Find("OCH")>=0){
		//|| pDoc->m_data.m_nLineSelect%10==2 //CMICT01AMB1 CMICT01AHB1
		strToppc = m_strComputerName.Left(8)+"HB1";		
	}
	else
		strToppc = m_strComputerName.Left(m_strComputerName.Find("TOP"))+ "BACK";

	//정해진 길이의 파일만 가져온다.
	int nStart,nEnd,ncount1 = 0;
	nStart = pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck] - 80;//pDoc->m_data.m_nCamDistance;
	if(nStart<0)nStart = 0;
	nEnd = nStart+50;
	if(m_strComputerName.Mid(8,1)=="M"){
		nStart = pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck]-10;
		nEnd = pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck];

	}
	//	double dtime;
	if(nEnd>=pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck]  )
		nEnd = pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck] -10;
	////c:\\glim\\data\\log\\년\\lotno\\pcname_생산미터.csv		//\\100.0.0.13\Glim\Data\Log\2019\19021917
// 	if(pDoc->m_data.m_bUseCLog){
// 	}
// 	else{
		strsrc1.Format("\\\\%s\\Data\\Data\\Log\\%s\\%s%s\\%s\\Mis\\",strToppc,data[0],data[1],data[2],strLot);
		//	strsrc1.Format("\\\\%s\\Glim\\Data\\Log\\%s\\%s\\MOVE\\","192.168.0.86",data[0],strLot);//1412
		strdst1.Format("D:\\Data\\LotDataTmp\\%s\\%s\\Mismatch\\",kk,strLot);
		CreateDirectory(strdst1,NULL);	
		strdst2.Format("D:\\Data\\LotDataTmp\\%s\\%s\\Mismatch\\Mis\\",kk,strLot);
		CreateDirectory(strdst2,NULL);	
		strdst3.Format("D:\\Data\\LotDataTmp\\%s\\%s\\Mismatch\\Mis\\Backup\\",kk,strLot);
		CreateDirectory(strdst3,NULL);	
		strdst2.Format("D:\\Data\\LotDataTmp\\%s\\%s\\Mismatch\\Mis\\*.csv",kk,strLot);

//	}

	SHFILEOPSTRUCT    shfo;
	WORD        wfunc;
	TCHAR        pszTo[1024] = {0};
	TCHAR        pszFrom[1024] = {0};
	TCHAR        pszTitle[MAX_PATH] = {0};
	wfunc = FO_MOVE;
	memset(pszTo, 0, sizeof(pszTo));   // 중요
	memset(pszFrom, 0, sizeof(pszFrom));
	strcpy(pszTitle, "FileMove");
	strcpy(pszTo, strdst1);
	strcpy(pszFrom , strsrc1);
	ZeroMemory(&shfo, sizeof(shfo));
	shfo.hwnd = AfxGetMainWnd()->m_hWnd;
	shfo.wFunc = wfunc;
	shfo.lpszProgressTitle=pszTitle;
	shfo.pTo=pszTo;
	shfo.pFrom=pszFrom;//FOF_NOCONFIRMATION
	shfo.fFlags = FOF_NOCONFIRMMKDIR|FOF_NOCONFIRMATION|FOF_SILENT|FOF_NOERRORUI;

	int ret = SHFileOperation(&shfo);


	CFileFind ff;
	CString path = strdst2;
	BOOL res = ff.FindFile(path);
	CString strfile3;
	//strdst3
	int nc=0;
	while(res)
	{
		res = ff.FindNextFile();

		if (!ff.IsDots() && !ff.IsDirectory()){	//file
			//read
			ReadMismatchData1(ff.GetFilePath(),strLot);
			strfile3 = ff.GetFileName();
			strdst3+= strfile3;
			MoveFile(ff.GetFilePath(),strdst3);
//			DeleteFile(ff.GetFilePath());
			nc++	;
//  			strtmp.Format("%s - %s read",ff.GetFilePath(),strdst3);
//  			AddtoInsLog(strtmp,0);
		}
		else if (ff.IsDirectory())	//directory
		{
		}
	}

	// 	double dtime1 = GetPrecisionTime();
	// 	strtmp.Format("t%.0f-%d",(dtime1-dtime)*1000,nc);//50개 debug mode 180ms
	//	AddtoInsLog(strtmp,0);
}
int CVisWebView::DataResultSave(int nCam)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CString strsrc1,strsrc2,strdst1,strdst2,strtmp,strLot;
	int nDefect = 0,nret=0;
// 	if( pDoc->m_data.m_nLineCount1[nCam]>0)
// 		nDefect =  pDoc->m_data.m_nLineCount1[nCam];
	CTime ttime = CTime::GetCurrentTime();
	CString kk = ttime.Format("[%H-%M-%S]");
	CString kk12 = ttime.Format("%H:%M:%S");
	CString kk1 = ttime.Format("%Y%m%d");
	CString strsave,strsave1,strpath,strsave2,strsave3,strpath1;
	strLot = ConvertCharToStr(cLotID);
	if(strLot =="")
		strLot = "NONE";
	CString data[6];
	CTime timer=CTime::GetCurrentTime();	
	data[0].Format("%d", timer.GetYear());
	if(timer.GetMonth() < 10)		data[1].Format("0%d", timer.GetMonth());
	else		data[1].Format("%d", timer.GetMonth());
	if(timer.GetDay() < 10)		data[2].Format("0%d", timer.GetDay());
	else		data[2].Format("%d", timer.GetDay());
	if(timer.GetHour() < 10)		data[3].Format("0%d", timer.GetHour());
	else		data[3].Format("%d", timer.GetHour());
	if(timer.GetMinute() < 10)		data[4].Format("0%d", timer.GetMinute());
	else		data[4].Format("%d", timer.GetMinute());
	if(timer.GetSecond() < 10)		data[5].Format("0%d", timer.GetSecond());
	else		data[5].Format("%d", timer.GetSecond());

	//frame별 max data 뽑기
	//data 초기화
	for(int k=0;k<MAX_CAMERAS && nCam==3;k++){
		for(int i=0;i<10;i++)			pDoc->m_data.m_dAverageData[i] = 0;
		pDoc->m_data.m_dAverageData[3] =pDoc->m_data.m_dAverageData[1] = 255;

		for(int i=0;i<MOD_COUNT;i++){
			for(int j=0;j<6;j++){
				if(j==0 || j==2 || j==4){
					if(pDoc->m_data.m_dAverageData[j]<pDoc->m_data.m_dAverageData1[k][i][j])pDoc->m_data.m_dAverageData[j]=pDoc->m_data.m_dAverageData1[k][i][j];
				}
				else{
					if(pDoc->m_data.m_dAverageData[j]>pDoc->m_data.m_dAverageData1[k][i][j])pDoc->m_data.m_dAverageData[j]=pDoc->m_data.m_dAverageData1[k][i][j];
				}
			}
		}
	}
// 	if(pDoc->m_data.m_bUseCLog){
// 		strpath.Format("c:\\Glim\\LOTdata\\");
// 		CreateDirectory(strpath,NULL);
// 		strpath.Format("c:\\Glim\\LOTdata\\%s\\",kk1);
// 		CreateDirectory(strpath,NULL);
// 		strpath.Format("c:\\Glim\\LOTdata\\%s\\%s\\",kk1,strLot);
// 		CreateDirectory(strpath,NULL);
// 		strpath.Format("c:\\Glim\\LOTdata\\%s\\%s\\%s\\",kk1,strLot,pDoc->m_data.m_strComName);
// 		CreateDirectory(strpath,NULL);
// 	}
// 	else{
		strpath.Format("D:\\Data\\LOTdata\\");
		CreateDirectory(strpath,NULL);
		strpath.Format("D:\\Data\\LOTdata\\%s\\",kk1);
		CreateDirectory(strpath,NULL);
 		strpath.Format("D:\\Data\\LOTdata\\%s\\%s\\",kk1,strLot);
		CreateDirectory(strpath,NULL);
		strpath.Format("D:\\Data\\LOTdata\\%s\\%s\\%s\\",kk1,strLot,pDoc->m_data.m_strComName);
		CreateDirectory(strpath,NULL);
		if(pDoc->m_data.m_nCamID==2)//top
			strpath1.Format("D:\\Data\\LotComplete\\%s\\%s\\%s\\%s\\HeadTop",data[0],data[1],data[2],strLot);
		else if(pDoc->m_data.m_nCamID==3)//back
		{
			strpath1.Format("D:\\Data\\LotComplete\\%s\\%s\\%s\\%s\\HeadBack",data[0],data[1],data[2],strLot);
	         CreateDirectory(strpath1,NULL); 
		}
		else if(pDoc->m_data.m_nCamID==4)//mis top
			strpath1.Format("D:\\Data\\LotComplete\\%s\\%s\\%s\\%s\\MisTop",data[0],data[1],data[2],strLot);
		else if(pDoc->m_data.m_nCamID==5)//mis back
			strpath1.Format("D:\\Data\\LotComplete\\%s\\%s\\%s\\%s\\MisBack",data[0],data[1],data[2],strLot);
	//}
////	strpath.Format("C:\\Glim\\LotData\\%s%s%s\\%s\\",data[0],data[1],data[2],pDoc->m_str_lot);


		
	int nMeter = pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck];

	if((nMeter>10 && nMeter<20) || m_strOldTime=="")
		m_strOldTime = kk1;
	if(nMeter>50 && nMeter<200)
		m_strOldPath = "";
	int nBad[10] = {0,};
	//Defect Type
	//bad image save
	//먼저 부루량 갯수부터 파악
	int nBadCount = 0,nBadCount1=0;
	for(int k=0;k<MAX_CAMERAS;k++){
		for(int i=0; i<pDoc->m_data.m_nRealDefectCount1[k]; i++)
			nBadCount++;
	}
	pDoc->m_data.m_nSumBadCount[pDoc->m_data.m_nCamID] += nBadCount;
	for(int k=0;k<MAX_CAMERAS;k++){
		int k1 = nCam;
		if(nCam==3)k1 =k;
		for(int i=0; i<pDoc->m_data.m_nRealDefectCount1[k1]; i++)
		{
			nret=1;
			m_nResultOkNg = 1;
			if(i >= MAX_REALDEFECT-1) break;
			int ndefectposx = pDoc->m_data.m_rectDefect[k1][i].left+(pDoc->m_data.m_rectDefect[k1][i].Width()*0.5);
			if(ndefectposx<=0)continue;

			int nLane = pDoc->m_data.LaneCheck(k1,ndefectposx,0,pDoc->m_data.m_nEpcPos);
			CPoint ptPos = pDoc->m_data.m_rectDefect[k1][i].CenterPoint();
			double dpos[2];
			dpos[0] = (k1*CAM_WIDTH_CIS+ptPos.x) * pDoc->m_data.m_dScaleFactorX[0];//poㄴY
			dpos[1] = ptPos.y * pDoc->m_data.m_dScaleFactorY[0];
			strsave2.Format("Cam%dDefect_%06d_%02d_%d_%d.bmp",k1,pDoc->m_nTotalIns[0],i+1,pDoc->m_data.m_nNewDefectType[k1][i],nMeter);
			strsave1.Format("%sCam%dDefect_%06d_%02d_%d_%d.bmp",strpath,k1,pDoc->m_nTotalIns[0],i+1,pDoc->m_data.m_nNewDefectType[k1][i],nMeter);
			strsave3.Format("%sCam%dDefect_%06d_%02d_%d_%d.bmp",strpath1,k1,pDoc->m_nTotalIns[0],i+1,pDoc->m_data.m_nNewDefectType[k1][i],nMeter);
			pDoc->m_data.m_strDefectName[k1][i]=strsave1;
			pDoc->m_data.m_strNewDefectName[k1][i] = GetDefectType(pDoc->m_data.m_nNewDefectType[k1][i]);

			if(nLane>0){
				if(pDoc->m_data.m_nNewDefectType[k1][i]==101 || pDoc->m_data.m_nNewDefectType[k1][i]==1001 || pDoc->m_data.m_nNewDefectType[k1][i]==1002 ){
					pDoc->m_data.m_nLaneDefectCount[nLane-1][0]++;
				}
				else{
					pDoc->m_data.m_nLaneDefectCount[nLane-1][1]++;
				}
			}

//bad write //20190414
			double dpx,dpy;
			dpx = pDoc->m_data.m_rectDefect[k1][i].left*pDoc->m_data.m_dScaleFactorX[0] + k1*CAM_WIDTH_CIS*pDoc->m_data.m_dScaleFactorX[0] - (pDoc->m_data.m_dNewLineEdgeData1[0]*pDoc->m_data.m_dScaleFactorX[0]);
			dpy = pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck] + (pDoc->m_data.m_rectDefect[k1][i].top*pDoc->m_data.m_dScaleFactorY[0])/1000;
//MODEL,color,gain,size,maxgray,mingray,avegray,검출값,
			CString strcolor,strmodel;
			strmodel = pDoc->m_data.m_strDefaultModel;
			if(pDoc->m_data.m_nNewDefectType[k1][i]==201 ||pDoc->m_data.m_nNewDefectType[k1][i]==1001 ||pDoc->m_data.m_nNewDefectType[k1][i]==3001 )
				strcolor = "BLACK";
			else strcolor = "WHITE";
			double dgain = 0.0;
			double dsize1 = (pDoc->m_data.m_dSizeX[k1][i]*pDoc->m_data.m_dSizeY[k1][i])*0.5;
			double dmaxgray = pDoc->m_data.m_dDefectValue1[k1][i][2]+abs(pDoc->m_data.m_dDefectValue1[k1][i][1]);
			if(dmaxgray>255)dmaxgray = 255;
			double dmingray = pDoc->m_data.m_dDefectValue1[k1][i][2]- abs(pDoc->m_data.m_dDefectValue1[k1][i][0]);
			if(dmingray<0)dmingray = 0;
			double davegray = pDoc->m_data.m_dDefectValue1[k1][i][2];
			double dThvalue = abs(pDoc->m_data.m_nDefectVMax[k1][i]);
			SYSTEMTIME stime1;
			GetLocalTime(&stime1);
			CString strLocaltime;
			strLocaltime.Format("%04d%02d%02d%02d%02d%02d%03d",
				stime1.wYear,
				stime1.wMonth,
				stime1.wDay,
				stime1.wHour,
				stime1.wMinute,
				stime1.wSecond,
				stime1.wMilliseconds);

			if(m_strComputerName.Find("CHO")<1)
				WriteDefectData(strLot, dpy,dpx, pDoc->m_data.m_dSizeX[k1][i],pDoc->m_data.m_dSizeY[k1][i], pDoc->m_data.m_nDefectVMax[k1][i],pDoc->m_data.m_strNewDefectName[k1][i],strsave1,strsave2,strsave3,
				strmodel,strcolor,dgain,dsize1,dmaxgray,dmingray,davegray,dThvalue,strLocaltime);
			//WriteDefectData(strLot, dpy,dpx, pDoc->m_data.m_dSizeX[k1][i],pDoc->m_data.m_dSizeY[k1][i], pDoc->m_data.m_nDefectVMax[k1][i],pDoc->m_data.m_strNewDefectName[k1][i],strsave1,strsave2,strsave3);
//			fnWriteData(strLot,pDoc->m_nTotalIns[0],nBadCount1,pDoc->m_data.fpDefectType[k1][i],dpx,dpy,pDoc->m_data.m_dSizeX[k1][i],pDoc->m_data.m_dSizeY[k1][i],"",0,0,
//				double(pDoc->m_data.fpDefectVMax[k1][i]),double(pDoc->m_data.fpDefectVMin[k1][i]),pDoc->m_data.m_dAvgBrightness[k1],0,k1);
			if(pDoc->m_pDlgInterface->m_bServerDataSend)
				WriteDefectDataServerSend(strLot, dpy,dpx, pDoc->m_data.m_dSizeX[k1][i],pDoc->m_data.m_dSizeY[k1][i], pDoc->m_data.m_nDefectVMax[k1][i],pDoc->m_data.m_strNewDefectName[k1][i],strsave1,strsave2,strsave3,pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck],
				strmodel,strcolor,dgain,dsize1,dmaxgray,dmingray,davegray,dThvalue,strLocaltime,pDoc->m_data.m_nCamID);

//server send
			if(pDoc->m_pDlgInterface->m_bServerDataSend){

			}
			CString str1;
			str1.Format("%s - %s\n%04dM, Lane:%d \n%.2f , %d",pDoc->m_data.m_strNewDefectName[k1][i],kk12,pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck],nLane,pDoc->m_data.m_dSize[k1][i],pDoc->m_data.m_nDefectVMax[k1][i]);
			if(nBadCount>10){
				if(nBadCount-nBadCount1<9 && nBadCount-nBadCount1>=0)
					BadImageShift(k1,pDoc->m_data.m_pImageDefect1[k1][i]->GetImagePtr(),1,str1);
			}
			else
				BadImageShift(k1,pDoc->m_data.m_pImageDefect1[k1][i]->GetImagePtr(),1,str1);
			nBadCount1++;
			if(m_dRemainMainSpace>5 ){
				pDoc->m_data.m_pImageDefect1[k1][i]->Save(strsave1);
			}
// 			if(nDefect == 101)str.Format("NC-Line");
// 			else if(nDefect == 201)str.Format("C-Line");//c
// 			else if(nDefect == 1001)str.Format("Island");//n
// 			else if(nDefect == 1002)str.Format("DragLine");//n
// 			else if(nDefect == 2001)str.Format("Pinhole");//c
// 			else if(nDefect == 3001)str.Format("C-Line");
// 			else if(nDefect == 4001)str.Format("C-Line");
// 			else if(nDefect == 7001)str.Format("Edge Spur");
// 			else					str.Format("PinHole");
			//부량 카운트
			if(pDoc->m_pDlgInterface->m_bEngKor){
				if(pDoc->m_data.m_strNewDefectName[k1][i].Find("Pinhole")>=0){
					pDoc->m_data.m_nBadTypeCount[5]++;nBad[5]++;}
				else if(pDoc->m_data.m_strNewDefectName[k1][i].Find("Line")>=0){
					pDoc->m_data.m_nBadTypeCount[1]++;nBad[1]++;}
				else if(pDoc->m_data.m_strNewDefectName[k1][i].Find("Line")>=0){
					pDoc->m_data.m_nBadTypeCount[4]++;nBad[4]++;}
				else if(pDoc->m_data.m_strNewDefectName[k1][i].Find("Island")>=0){
					pDoc->m_data.m_nBadTypeCount[2]++;nBad[2]++;}
				else if(pDoc->m_data.m_strNewDefectName[k1][i].Find("Drag")>=0 ){
					pDoc->m_data.m_nBadTypeCount[0]++;nBad[0]++;}
				else if(pDoc->m_data.m_strNewDefectName[k1][i].Find("Chipping")>=0){
					pDoc->m_data.m_nBadTypeCount[3]++;nBad[3]++;}
				else
					pDoc->m_data.m_nBadTypeCount[5]++;

			}
			else{
				if(pDoc->m_data.m_strNewDefectName[k1][i].Find("핀홀")>=0){
					pDoc->m_data.m_nBadTypeCount[5]++;nBad[5]++;}
				else if(pDoc->m_data.m_strNewDefectName[k1][i].Find("라인")>=0){
					pDoc->m_data.m_nBadTypeCount[1]++;nBad[1]++;}
				else if(pDoc->m_data.m_strNewDefectName[k1][i].Find("라인")>=0){
					pDoc->m_data.m_nBadTypeCount[4]++;nBad[4]++;}
				else if(pDoc->m_data.m_strNewDefectName[k1][i].Find("아일랜드")>=0){
					pDoc->m_data.m_nBadTypeCount[2]++;nBad[2]++;}
				else if(pDoc->m_data.m_strNewDefectName[k1][i].Find("드래그")>=0){
					pDoc->m_data.m_nBadTypeCount[0]++;nBad[0]++;}
				else if(pDoc->m_data.m_strNewDefectName[k1][i].Find("파인")>=0){
					pDoc->m_data.m_nBadTypeCount[3]++;nBad[3]++;}
				else
					pDoc->m_data.m_nBadTypeCount[5]++;
			}

		}
		if(k1>MAX_CAMERAS)break;
	}
	if(nBadCount>0){
		//wrtie ng count
		WrtieDefectCount(pDoc->m_data.m_nSumBadCount[pDoc->m_data.m_nCamID],strLot);
	}

	if(pDoc->m_data.m_nInsulateDefectCount>0){
		for(int i=0;i<pDoc->m_data.m_nInsulateDefectCount;i++){
			CString str1;
			str1.Format("%s\n%.2f","절연",0.0);
			if(pDoc->m_data.m_nInsulateDefectCount>10){
				if(nBadCount-nBadCount1<9 && nBadCount-nBadCount1>=0)
					BadImageShift(0,pDoc->m_data.m_pImageDefectInsulate[i]->GetImagePtr(),1,str1);
			}
			else
				BadImageShift(0,pDoc->m_data.m_pImageDefectInsulate[i]->GetImagePtr(),1,str1);

		}
	}
	
	//if(nBadCount> pDoc->m_pDlgInterface->m_nBadFrameInDefect)
	if(pDoc->m_pDlgInterface->m_bDefectNgFrame && pDoc->m_pDlgInterface->m_bAlarm)
	{
		m_nNgFrameCount[pDoc->m_nTotalIns[0]%100] += nBadCount1;
		double dFrameHeight = 1000 /(pDoc->m_data.m_dScaleFactorY[0]*CAM_HEIGHT_3072);
		int nf1 = dFrameHeight * pDoc->m_pDlgInterface->m_nBadFrameInCount;
		//m_nBadFrameInCount

		m_nNgFrameCount[(pDoc->m_nTotalIns[0]+10000-nf1)%100] = 0;
	}
	else
		m_nNgFrameCount[pDoc->m_nTotalIns[0]%100] =0;
	if(pDoc->m_pDlgInterface->m_bNgFrameInCount && pDoc->m_pDlgInterface->m_bAlarm){//연셕ㅇ;물
		//dusthr qnffid
		//m_nContinueBadcnt//m_nContinueBadFrame
		if(nBadCount>pDoc->m_pDlgInterface->m_nContinueBadcnt)
			m_nContinueCnt++;
		else
			m_nContinueCnt=0;
		if(m_nContinueCnt>pDoc->m_pDlgInterface->m_nContinueBadMeter){//Meter로 변환
			m_bAlarmOnOff = TRUE;
			int ntmpmeter = pDoc->m_nTotalIns[0]+4;
			if(m_nAlarmEndFRame<ntmpmeter)
				m_nAlarmEndFRame = ntmpmeter;
			m_strAlarmMsg = "Defect";//연속이물
			m_strAlarmMsg1.Format("%d M", pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck]) ;

			AddtoList("Alarm Continuous Defect!",0,TRUE);
			m_nAlarmLog += 4;
		}

	}
	if(pDoc->m_pDlgInterface->m_bDefectNgFrame && pDoc->m_pDlgInterface->m_bAlarm){
		int nNgcnt = 0;
		int ntmpframe = pDoc->m_nTotalIns[0]%100+1000;
		int nFrameHeight = 1000 /(pDoc->m_data.m_dScaleFactorY[0]*CAM_HEIGHT_3072);
		if(pDoc->m_pDlgInterface->m_nBadNgFrame>999)pDoc->m_pDlgInterface->m_nBadNgFrame = 999;
		
		for(int nf = ntmpframe;nf>ntmpframe-pDoc->m_pDlgInterface->m_nBadNgFrame*nFrameHeight  ;nf--){
			if(nf<0)break;
			if(m_nNgFrameCount[nf%100]>0)nNgcnt++;
		}
		if(nNgcnt>pDoc->m_pDlgInterface->m_nBadFrameInCount*nFrameHeight && pDoc->m_pDlgInterface->m_bAlarm){
			//Alaram on
			m_bAlarmOnOff = TRUE;
			int ntmpmeter =pDoc->m_nTotalIns[0]+4;
			if(m_nAlarmEndFRame<ntmpmeter)
				m_nAlarmEndFRame = ntmpmeter;
			m_nAlarmLog += 8;
			m_strAlarmMsg = "defect";//"구간이물";
			m_strAlarmMsg1.Format("%d M", pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck]) ;

			AddtoList("Alarm Interval Defect!",0,TRUE);

		}
//		for(int l1 = pDoc->m_nTotalIns[0]-(ntmpframe-pDoc->m_pDlgInterface->m_nBadNgFrame*nFrameHeight)+1000;l1> pDoc->m_nTotalIns[0]+1000 )
		m_nNgFrameCount[((1000+pDoc->m_nTotalIns[0]) - ntmpframe-pDoc->m_pDlgInterface->m_nBadNgFrame*nFrameHeight)%100]  = 0;
	}
	if(nCam==3){
		//연속 불량
		BOOL bflag = FALSE;
		for(int i=0;i<9;i++){
			if(nBad[i]>=1){
				m_nBadCountDefect[i]++;
				bflag = TRUE;
			}
			else			m_nBadCountDefect[i] = 0;
		}
		if(bflag==TRUE)
			m_nBadCountDefect[9]++;//
	}

	return nret;
}

int CVisWebView::UpdateControl()
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CString str;
	pDoc->m_data.m_nBadTypeCount[0];

	if(pDoc->m_pDlgInterface->m_bEngKor){
		str.Format("DRAG LINE:   %dea",pDoc->m_data.m_nBadTypeCount[0]);
		m_lbNullDrag.SetText(str);

		str.Format("N-COAT LINE:   %dea",pDoc->m_data.m_nBadTypeCount[1]);
		m_lbNullLine.SetText(str);

		str.Format("ISLAND  :   %dea",pDoc->m_data.m_nBadTypeCount[2]);
		m_lbNullIsland.SetText(str);

		str.Format("EDGE SPUR:   %dea",pDoc->m_data.m_nBadTypeCount[3]);
		m_lbCoatDrag.SetText(str);

		str.Format("COAT LINE:   %dea",pDoc->m_data.m_nBadTypeCount[4]);
		m_lbCoatLine.SetText(str);

		str.Format("PINHOLE:   %dea",pDoc->m_data.m_nBadTypeCount[5]);
		m_lbCoatPinHole.SetText(str);
	}
	else{
	str.Format("드래그라인:   %d개",pDoc->m_data.m_nBadTypeCount[0]);
	m_lbNullDrag.SetText(str);

	str.Format("무지  라인:   %d개",pDoc->m_data.m_nBadTypeCount[1]);
	m_lbNullLine.SetText(str);

	str.Format("아일랜드  :   %d개",pDoc->m_data.m_nBadTypeCount[2]);
	m_lbNullIsland.SetText(str);

	str.Format("코팅드래그:   %d개",pDoc->m_data.m_nBadTypeCount[3]);
	m_lbCoatDrag.SetText(str);

	str.Format("코팅  라인:   %d개",pDoc->m_data.m_nBadTypeCount[4]);
	m_lbCoatLine.SetText(str);

	str.Format("핀     홀:   %d개",pDoc->m_data.m_nBadTypeCount[5]);
	m_lbCoatPinHole.SetText(str);
	}

//	str.Format("제 품 폭 :  mm");
//	m_lbFullWidth.SetText(str);
	return 0;
}


//c:\\glim\\data\\log\\년\\lotno\\pcname_생산미터.csv
void CVisWebView::fnWriteData3(CString strLot,int nMeter, int nSubFrame, int nLineCount) 
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CStdioFile   file;
	CString filename;
	CString strtmp,str,strTitle,strpath,strOkNg,strpc,strtmp1,strtmp2,strtmp3,strtmp4,strtmp5,strtmp6,strtime;
	CString txtscr,txtdst;
	int nPcno =0;
	int nLine =0;
	//날자 LotNo. Frame	DefectCount	Defect-Class	x-Pos	Y-Pos	X-Size	Y-Size	ImagePath
	//////////////
	CString data[6];
	CTime timer=CTime::GetCurrentTime();	
	data[0].Format("%d", timer.GetYear());
	if(timer.GetMonth() < 10)		data[1].Format("0%d", timer.GetMonth());
	else		data[1].Format("%d", timer.GetMonth());
	if(timer.GetDay() < 10)		data[2].Format("0%d", timer.GetDay());
	else		data[2].Format("%d", timer.GetDay());
	if(timer.GetHour() < 10)		data[3].Format("0%d", timer.GetHour());
	else		data[3].Format("%d", timer.GetHour());
	if(timer.GetMinute() < 10)		data[4].Format("0%d", timer.GetMinute());
	else		data[4].Format("%d", timer.GetMinute());
	if(timer.GetSecond() < 10)		data[5].Format("0%d", timer.GetSecond());
	else		data[5].Format("%d", timer.GetSecond());

	if(strLot=="")strLot = "NONE";

// 	if(pDoc->m_data.m_bUseCLog){
// 		strpath.Format("C:\\Glim\\");
// 		CreateDirectory(strpath,NULL);//년월일
// 		strpath.Format("C:\\Glim\\Data\\");
// 		CreateDirectory(strpath,NULL);//년월일
// 		strpath.Format("C:\\Glim\\Data\\Log\\");
// 		CreateDirectory(strpath,NULL);//년월일
// 		strpath.Format("C:\\Glim\\Data\\Log\\%s\\",data[0]);
// 		CreateDirectory(strpath,NULL);//년월일
// 		strpath.Format("C:\\Glim\\Data\\Log\\%s\\%s\\",data[0],strLot);
// 		CreateDirectory(strpath,NULL);
// 	}
// 	else{
		strpath.Format("D:\\Data\\");
		CreateDirectory(strpath,NULL);//년월일
		strpath.Format("D:\\Data\\Data\\");
		CreateDirectory(strpath,NULL);//년월일
		strpath.Format("D:\\Data\\Data\\Log\\");
		CreateDirectory(strpath,NULL);//년월일
		strpath.Format("D:\\Data\\Data\\Log\\%s\\",data[0]);
		CreateDirectory(strpath,NULL);//년월일
		strpath.Format("D:\\Data\\Data\\Log\\%s\\%s%s\\",data[0],data[1],data[2]);
		CreateDirectory(strpath,NULL);//년월일
		strpath.Format("D:\\Data\\Data\\Log\\%s\\%s%s\\%s\\",data[0],data[1],data[2],strLot);
		CreateDirectory(strpath,NULL);

//	}

	filename.Format("%s%s_%d.csv",strpath,pDoc->m_data.m_strComName,nMeter);

	int frame = nSubFrame;
	strtmp1 = strtmp2 = strtmp3 = strtmp4 =strtmp5=strtmp6= "";

	CString sttrtile1,sttrtile2,sttrtile3,sttrtile4,sttrtile5,sttrtile6;
	strtime.Format("%s년%s월%s일%s시%s분%s초",data[0],data[1],data[2],data[3],data[4],data[5]);
	int nCount1 = nLineCount;
	int nc1 = 0;
	double d1=0,doffsetScale=0.002485;
	int nCalPos = 0;
	double d2=0,d3;
	double dtmp[20]={0,};
	CString strWidth;
	int n1=0,n2=0;
	double dTmpWidth = 0.0;

	double dScale = pDoc->m_data.m_dScaleFactorX[0];
	int ntopback =0;
	if(m_strComputerName.Find("CMI")>=0 ||m_strComputerName.Find("OCH")>=0){
		//|| pDoc->m_data.m_nLineSelect%10==2
	}

	if(m_strComputerName.Find("BACK")>=0 ||  pDoc->m_data.m_strComName.Mid(9,1)=="B")ntopback = 1;	 

// 	for(int i=1;i<nCount1+1;i++){//0번은 갯수
// 		strtmp1.Format(",%.2f",pDoc->m_data.m_nFullLineData[ntopback][nMeter%100][frame][i]);
// 		strWidth.Format("%.2f",pDoc->m_data.m_nFullLineData[ntopback][nMeter%100][frame][i]*dScale);
// 		dtmp[i]=atof(strWidth);
// 		strtmp2 += strtmp1;
// 	}
	for(int i=0;i<pDoc->m_data.m_nNewLineCount;i++){//0번은 갯수
		//		strtmp1.Format(",%.2f",pDoc->m_data.m_nFullLineData[ntopback][nMeter%100][frame][i]);
		//		strWidth.Format("%.2f",pDoc->m_data.m_nFullLineData[ntopback][nMeter%100][frame][i]*dScale);
			strtmp1.Format(",%.2f",pDoc->m_data.m_dNewLineEdgeData1[i]);//[ntopback][nMeter%100][frame][i]);
			strWidth.Format("%.2f",pDoc->m_data.m_dNewLineEdgeData1[i]*dScale);
			dtmp[i]=atof(strWidth);
			strtmp2 += strtmp1;

	}

	
	if(pDoc->m_pDlgInterface->m_bPlcWrite){
		CString strLogCoat[10];
		CString strLogNCoat[10];
		CString strLogMismatch[10] = {_T(""),};

		for (int i=0;i<nCount1-1;i++)//cis top Plc Write
		{ 	    
			if (dtmp[i]<=0) continue;

			dTmpWidth=dtmp[i+1]-dtmp[i];
			strWidth.Format("%.2f",dTmpWidth);
			if(i%2==0){
				WriteShareMemory(1,n1,atof(strWidth)+0.005);  // 무지
				strLogNCoat[n1] = strWidth;
				n1++;
			}
			else {
				WriteShareMemory(3,n2,atof(strWidth)+0.005);	// 코팅
				strLogCoat[n2] = strWidth;
				n2++;
			}

		}

		for(int i=n1; i<10; i++){				// 200812 kjh
			WriteShareMemory(1, i, 0.0);
			strLogNCoat[i] = _T("0");
		}

		for(int i=n2; i<10; i++){
			WriteShareMemory(3, i, 0.0);
			strLogCoat[i] = _T("0");
		}


		// write use check(top)
		WriteUseCheck(0, nCount1);


		WriteShareMemorySpec();
		SavePLCSendDataLog(strLogCoat, strLogNCoat, strLogMismatch, strLot, nMeter);
	}
	
	
	for(int i=0;i<nLineCount;i++){
		sttrtile1.Format(",픽셀%d",i+1);
		sttrtile4 += sttrtile1;
	}
	strTitle.Format("년월일시분초,PC,LotID,Meter,FrameNo,Scale,LineCount%s",sttrtile4);//,sttrtile5,sttrtile6);

	strtmp.Format("%s,%s,%s,%d,%d,%.7f,%d%s",strtime,m_strComputerName,strLot,nMeter,frame,dScale,nLineCount,strtmp2);
//	strtmp.Format("%s,%s,%d,%d%s%s%s",strtime,pDoc->m_str_lot,frame,nLineCount,strtmp4,strtmp2,strtmp6);
	if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
	{		
		if(file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText))
		{
			file.WriteString(strTitle);
			file.WriteString("\n");
			file.WriteString(strtmp);
			file.Close();
		}
	}
	else
	{
		file.SeekToEnd();
		file.WriteString("\n");
		file.WriteString(strtmp);
		file.Close(); 
	}
}

void CVisWebView::fnWriteData4(CString strLot,int nMeter, int nSubFrame, int nLineCount) 
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CStdioFile   file;
	CString filename;
	CString strtmp,str,strTitle,strpath,strOkNg,strpc,strtmp1,strtmp2,strtmp3,strtmp4,strtmp5,strtmp6,strtime;
	CString txtscr,txtdst;
	int nPcno =0;
	int nLine =0;
	//날자 LotNo. Frame	DefectCount	Defect-Class	x-Pos	Y-Pos	X-Size	Y-Size	ImagePath
	//////////////
	CString data[6];
	CTime timer=CTime::GetCurrentTime();	
	data[0].Format("%d", timer.GetYear());
	if(timer.GetMonth() < 10)		data[1].Format("0%d", timer.GetMonth());
	else		data[1].Format("%d", timer.GetMonth());
	if(timer.GetDay() < 10)		data[2].Format("0%d", timer.GetDay());
	else		data[2].Format("%d", timer.GetDay());
	if(timer.GetHour() < 10)		data[3].Format("0%d", timer.GetHour());
	else		data[3].Format("%d", timer.GetHour());
	if(timer.GetMinute() < 10)		data[4].Format("0%d", timer.GetMinute());
	else		data[4].Format("%d", timer.GetMinute());
	if(timer.GetSecond() < 10)		data[5].Format("0%d", timer.GetSecond());
	else		data[5].Format("%d", timer.GetSecond());
	if(strLot=="")strLot = "NONE";
// 	if(pDoc->m_data.m_bUseCLog){
// 		strpath.Format("C:\\Glim\\");
// 		CreateDirectory(strpath,NULL);//년월일
// 		strpath.Format("C:\\Glim\\Data\\");
// 		CreateDirectory(strpath,NULL);//년월일
// 		strpath.Format("C:\\Glim\\Data\\Log\\");
// 		CreateDirectory(strpath,NULL);//년월일
// 		strpath.Format("C:\\Glim\\Data\\Log\\%s\\",data[0]);
// 		CreateDirectory(strpath,NULL);//년월일
// 		strpath.Format("C:\\Glim\\Data\\Log\\%s\\%s\\",data[0],strLot);
// 		CreateDirectory(strpath,NULL);
// 	}
// 	else{
		strpath.Format("D:\\Data\\");
		CreateDirectory(strpath,NULL);//년월일
		strpath.Format("D:\\Data\\Data\\");
		CreateDirectory(strpath,NULL);//년월일
		strpath.Format("D:\\Data\\Data\\Log\\");
		CreateDirectory(strpath,NULL);//년월일
		strpath.Format("D:\\Data\\Data\\Log\\%s\\",data[0]);
		CreateDirectory(strpath,NULL);//년월일
		strpath.Format("D:\\Data\\Data\\Log\\%s\\%s%s\\",data[0],data[1],data[2]);
		CreateDirectory(strpath,NULL);//년월일
		strpath.Format("D:\\Data\\Data\\Log\\%s\\%s%s\\%s\\",data[0],data[1],data[2],strLot);
		CreateDirectory(strpath,NULL);
//	}

	filename.Format("%s%s_FULL.csv",strpath,pDoc->m_data.m_strComName);

	int frame = nSubFrame;
	strtmp1 = strtmp2 = strtmp3 = strtmp4 =strtmp5=strtmp6= "";

	CString sttrtile1,sttrtile2,sttrtile3,sttrtile4,sttrtile5,sttrtile6;
	strtime.Format("%s년%s월%s일%s시%s분%s초",data[0],data[1],data[2],data[3],data[4],data[5]);
	int nCount1 = nLineCount;
	int nc1 = 0;
	double d1=0,doffsetScale=0.002485;
	int nCalPos = 0;
	double d2=0,d3;

	double dScale = pDoc->m_data.m_dScaleFactorX[0];
	int ntopback =0;
	if(m_strComputerName.Find("BACK")>=0 ||  pDoc->m_data.m_strComName.Mid(9,1)=="B" )ntopback = 1;

// 	for(int i=1;i<nCount1+1;i++){//0번은 갯수
// 		strtmp1.Format(",%d",pDoc->m_data.m_nFullLineData[ntopback][nMeter%100][frame][i]);
// 		strtmp2 += strtmp1;
// 		strtmp3.Format(",%.2f",pDoc->m_data.m_nFullLineData[ntopback][nMeter%100][frame][i]*dScale);
// 		strtmp4 += strtmp3;
// 	}
	for(int i=0;i<pDoc->m_data.m_nNewLineCount;i++){//
		strtmp1.Format(",%d",pDoc->m_data.m_dNewLineEdgeData1[i]);//[ntopback][nMeter%100][frame][i]);
		strtmp2 += strtmp1;
		strtmp3.Format(",%.2f",pDoc->m_data.m_dNewLineEdgeData1[i]*dScale);//[ntopback][nMeter%100][frame][i]*dScale);
		strtmp4 += strtmp3;
	}
	for(int i=0;i<nLineCount;i++){
		sttrtile1.Format(",픽셀%d",i+1);
		sttrtile4 += sttrtile1;
	}
	strTitle.Format("년월일시분초,PC,LotID,Meter,FrameNo,Scale,LineCount%s",sttrtile4);//,sttrtile5,sttrtile6);

	strtmp.Format("%s,%s,%s,%d,%d,%.7f,%d%s%s",strtime,m_strComputerName,strLot,nMeter,frame,dScale,nLineCount,strtmp2,strtmp4);
	//	strtmp.Format("%s,%s,%d,%d%s%s%s",strtime,pDoc->m_str_lot,frame,nLineCount,strtmp4,strtmp2,strtmp6);
	if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
	{		
		if(file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText))
		{
			file.WriteString(strTitle);
			file.WriteString("\n");
			file.WriteString(strtmp);
			file.Close();
		}
	}
	else
	{
		file.SeekToEnd();
		file.WriteString("\n");
		file.WriteString(strtmp);
		file.Close(); 
	}
}

void CVisWebView::fnWriteData5(CString strLot,int nMeter, int nSubFrame, int nLineCount) //백 미스매치 기록
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CStdioFile   file;
	CString filename,filename1,filename2,filename3;
	CString strtmp,str,strTitle,strpath,strOkNg,strpc,strtmp1,strtmp2,strtmp3,strtmp4,strtmp5,strtmp6,strtime,strpath1,strpath2;//path2 mis용 10M
	CString txtscr,txtdst;
	int nPcno =0;
	int nLine =0;
	//날자 LotNo. Frame	DefectCount	Defect-Class	x-Pos	Y-Pos	X-Size	Y-Size	ImagePath
	//////////////
	CString data[6];
	CTime timer=CTime::GetCurrentTime();	
	data[0].Format("%d", timer.GetYear());
	if(timer.GetMonth() < 10)		data[1].Format("0%d", timer.GetMonth());
	else		data[1].Format("%d", timer.GetMonth());
	if(timer.GetDay() < 10)		data[2].Format("0%d", timer.GetDay());
	else		data[2].Format("%d", timer.GetDay());
	if(timer.GetHour() < 10)		data[3].Format("0%d", timer.GetHour());
	else		data[3].Format("%d", timer.GetHour());
	if(timer.GetMinute() < 10)		data[4].Format("0%d", timer.GetMinute());
	else		data[4].Format("%d", timer.GetMinute());
	if(timer.GetSecond() < 10)		data[5].Format("0%d", timer.GetSecond());
	else		data[5].Format("%d", timer.GetSecond());

	if(strLot=="")strLot = "NONE";
// 	if(pDoc->m_data.m_bUseCLog){
// 		strpath.Format("C:\\Glim\\");
// 		CreateDirectory(strpath,NULL);//년월일
// 		strpath.Format("C:\\Glim\\Data\\");
// 		CreateDirectory(strpath,NULL);//년월일
// 		strpath.Format("C:\\Glim\\Data\\Log\\");
// 		CreateDirectory(strpath,NULL);//년월일
// 		strpath.Format("C:\\Glim\\Data\\Log\\%s\\",data[0]);
// 		CreateDirectory(strpath,NULL);//년월일
// 		strpath.Format("C:\\Glim\\Data\\Log\\%s\\%s\\",data[0],data[1],data[2]);
// 		CreateDirectory(strpath,NULL);//년월일
// 		strpath.Format("C:\\Glim\\Data\\Log\\%s\\%s\\%s\\",data[0],data[1],data[2],strLot);
// 		CreateDirectory(strpath,NULL);
// 		strpath1.Format("C:\\Glim\\Data\\Log\\%s\\%s\\%s\\Move\\",data[0],data[1],data[2],strLot);
// 		CreateDirectory(strpath1,NULL);
// 	}
// 	else{
		strpath.Format("D:\\Data\\");
		CreateDirectory(strpath,NULL);//년월일
		strpath.Format("D:\\Data\\Data\\");
		CreateDirectory(strpath,NULL);//년월일
		strpath.Format("D:\\Data\\Data\\Log\\");
		CreateDirectory(strpath,NULL);//년월일
		strpath.Format("D:\\Data\\Data\\Log\\%s\\",data[0]);
		CreateDirectory(strpath,NULL);//년월일
		strpath.Format("D:\\Data\\Data\\Log\\%s\\%s%s\\",data[0],data[1],data[2]);
		CreateDirectory(strpath,NULL);//년월일
		strpath.Format("D:\\Data\\Data\\Log\\%s\\%s%s\\%s\\",data[0],data[1],data[2],strLot);
		CreateDirectory(strpath,NULL);
		strpath2 = strpath1;
		strpath1.Format("D:\\Data\\Data\\Log\\%s\\%s%s\\%s\\Move\\",data[0],data[1],data[2],strLot);
		CreateDirectory(strpath1,NULL);//top head용 경로
		strpath2.Format("D:\\Data\\Data\\Log\\%s\\%s%s\\%s\\Mis\\",data[0],data[1],data[2],strLot);
		CreateDirectory(strpath2,NULL);//mis메치용 경로

	//}
	CreateDirectory(strpath1,NULL);
	int nm1 = nMeter/10;

	filename.Format("%s%s_%d.csv",strpath,pDoc->m_data.m_strComName,nm1);
	filename1.Format("%s%s_%d.csv",strpath1,pDoc->m_data.m_strComName,nm1);
	
	int frame = nSubFrame;
	strtmp1 = strtmp2 = strtmp3 = strtmp4 =strtmp5=strtmp6= "";

	CString sttrtile1,sttrtile2,sttrtile3,sttrtile4,sttrtile5,sttrtile6;
	strtime.Format("%s년%s월%s일%s시%s분%s초",data[0],data[1],data[2],data[3],data[4],data[5]);
	int nCount1 = nLineCount;
	int nc1 = 0;
	double d1=0,doffsetScale=0.002485;
	int nCalPos = 0;
	double d2=0,d3;

	int ntopback =0;
	if(m_strComputerName.Find("BACK")>=0 ||  pDoc->m_data.m_strComName.Mid(9,1)=="B" )ntopback = 1;	 

	strtmp2 = m_strTopMismatch;

	strtmp.Format("%s,%s,%s,%d,%d,%d,%s",strtime,m_strComputerName,strLot,nMeter,frame,nLineCount,strtmp2);
	if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
	{		
		if(file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText))
		{
			file.WriteString(strtmp);
			file.Close();
		}
	}
	else
	{
		file.SeekToEnd();
		file.WriteString("\n");
		file.WriteString(strtmp);
		file.Close(); 
	}

	if(m_strOldFilename != filename && m_strOldFilename!=""){
		CString oldfile,oldfile1;
		oldfile = m_strOldFilename;
		oldfile1 = m_strOldFilename1;//.Left(m_strOldFilename.Find(".txt"))+".csv";
// 		if(pDoc->m_data.m_bUseCLog)
// 			strpath1.Format("C:\\Glim\\Data\\Log\\%s\\%s\\Move\\",data[0],strLot);
// 		else
// 			strpath1.Format("D:\\Data\\Data\\Log\\%s\\%s\\Move\\",data[0],strLot);

		CreateDirectory(strpath1,NULL);
		CFileFind cfile;
		BOOL b;
		m_strOldFilename = filename;
		b = cfile.FindFile(oldfile);
		if(!b)	return ;
		else{
			//move
			MoveFile(oldfile,oldfile1);
//			rename(oldfile,oldfile1);
		}
	}
	else{
		m_strOldFilename = filename;
		m_strOldFilename1 = filename1;
	}
}

//void CVisWebView::fnWriteData9(CString strLot,int nMeter, int nSubFrame, int nLineCount) //백 미스매치 기록
void CVisWebView::fnWriteData9(CString strLot,int nMeter, int nSubFrame,double dtopscale,double dbackscame,int nLine,CString strtop,CString strback,CString strmis,CString strwid1,CString strwid2) //미스매치부헤드부 동기화 관련

{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CStdioFile   file;
	CString filename,filename1,filename2,filename3;
	CString strtmp,str,strTitle,strpath,strOkNg,strpc,strtmp1,strtmp2,strtmp3,strtmp4,strtmp5,strtmp6,strtime,strpath1,strpath2;//path2 mis용 10M
	CString txtscr,txtdst;
	int nPcno =0;
	//날자 LotNo. Frame	DefectCount	Defect-Class	x-Pos	Y-Pos	X-Size	Y-Size	ImagePath
	//////////////
	CString data[6];
	CTime timer=CTime::GetCurrentTime();	
	data[0].Format("%d", timer.GetYear());
	if(timer.GetMonth() < 10)		data[1].Format("0%d", timer.GetMonth());
	else		data[1].Format("%d", timer.GetMonth());
	if(timer.GetDay() < 10)		data[2].Format("0%d", timer.GetDay());
	else		data[2].Format("%d", timer.GetDay());
	if(timer.GetHour() < 10)		data[3].Format("0%d", timer.GetHour());
	else		data[3].Format("%d", timer.GetHour());
	if(timer.GetMinute() < 10)		data[4].Format("0%d", timer.GetMinute());
	else		data[4].Format("%d", timer.GetMinute());
	if(timer.GetSecond() < 10)		data[5].Format("0%d", timer.GetSecond());
	else		data[5].Format("%d", timer.GetSecond());

	if(strLot=="")strLot = "NONE";
// 	if(pDoc->m_data.m_bUseCLog){
// 		strpath.Format("C:\\Glim\\");
// 		CreateDirectory(strpath,NULL);//년월일
// 		strpath.Format("C:\\Glim\\Data\\");
// 		CreateDirectory(strpath,NULL);//년월일
// 		strpath.Format("C:\\Glim\\Data\\Log\\");
// 		CreateDirectory(strpath,NULL);//년월일
// 		strpath.Format("C:\\Glim\\Data\\Log\\%s\\",data[0]);
// 		CreateDirectory(strpath,NULL);//년월일
// 		strpath.Format("C:\\Glim\\Data\\Log\\%s\\%s\\",data[0],data[1],data[2]);
// 		CreateDirectory(strpath,NULL);//년월일
// 		strpath.Format("C:\\Glim\\Data\\Log\\%s\\%s\\%s\\",data[0],data[1],data[2],strLot);
// 		CreateDirectory(strpath,NULL);
// 		strpath1.Format("C:\\Glim\\Data\\Log\\%s\\%s\\%s\\Move\\",data[0],data[1],data[2],strLot);
// 		CreateDirectory(strpath1,NULL);
// 	}
// 	else{
		strpath.Format("D:\\Data\\");
		CreateDirectory(strpath,NULL);//년월일
		strpath.Format("D:\\Data\\Data\\");
		CreateDirectory(strpath,NULL);//년월일
		strpath.Format("D:\\Data\\Data\\Log\\");
		CreateDirectory(strpath,NULL);//년월일
		strpath.Format("D:\\Data\\Data\\Log\\%s\\",data[0]);
		CreateDirectory(strpath,NULL);//년월일
		strpath.Format("D:\\Data\\Data\\Log\\%s\\%s%s\\",data[0],data[1],data[2]);
		CreateDirectory(strpath,NULL);//년월일
		strpath.Format("D:\\Data\\Data\\Log\\%s\\%s%s\\%s\\",data[0],data[1],data[2],strLot);
		CreateDirectory(strpath,NULL);
		strpath2 = strpath1;
		strpath1.Format("D:\\Data\\Data\\Log\\%s\\%s%s\\%s\\Move\\",data[0],data[1],data[2],strLot);
		CreateDirectory(strpath1,NULL);//top head용 경로
		strpath2.Format("D:\\Data\\Data\\Log\\%s\\%s%s\\%s\\Mis\\",data[0],data[1],data[2],strLot);
		CreateDirectory(strpath2,NULL);//mis메치용 경로

//	}
	CreateDirectory(strpath1,NULL);
	int nm1 = nMeter/10;

	filename2.Format("%sHead_%s_%d.csv",strpath,pDoc->m_data.m_strComName,nm1);
	filename3.Format("%sHead_%s_%d.csv",strpath2,pDoc->m_data.m_strComName,nm1);


	int frame = nSubFrame;
	strtmp1 = strtmp2 = strtmp3 = strtmp4 =strtmp5=strtmp6= "";

	CString sttrtile1,sttrtile2,sttrtile3,sttrtile4,sttrtile5,sttrtile6;
	strtime.Format("%s년%s월%s일%s시%s분%s초",data[0],data[1],data[2],data[3],data[4],data[5]);
	int nCount1 = nLine;
	int nc1 = 0;
	double d1=0,doffsetScale=0.002485;
	int nCalPos = 0;
	double d2=0,d3;

	int ntopback =0;
	if(m_strComputerName.Find("BACK")>=0 ||  pDoc->m_data.m_strComName.Mid(9,1)=="B" )ntopback = 1;	 

	strtmp2 = m_strTopMismatch;
	strtmp.Format("%s,%s,%s,%d,%d,%d,%s",strtime,m_strComputerName,strLot,nMeter,frame,nLine,strtmp2);//기존 헤더부간 데이터 파일
	strtmp.Format("%d,%.8f,%.8f,%d,%s%s%s%s%s",nMeter,dtopscale,dbackscame,nLine,strtop,strback,strmis,strwid1,strwid2);//헤더백솨 미스백에 데이터 파일

	if(!file.Open(filename2, CFile::modeReadWrite|CFile::typeText)) 
	{		
		if(file.Open(filename2, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText))
		{
			file.WriteString(strtmp);
			file.Close();
		}
	}
	else
	{
		file.SeekToEnd();
		file.WriteString("\n");
		file.WriteString(strtmp);
		file.Close(); 
	}

	if(m_strOldFilename2 != filename2 && m_strOldFilename2 != ""){
		CString oldfile,oldfile1;
		oldfile = m_strOldFilename2;
		oldfile1 = m_strOldFilename3;//.Left(m_strOldFilename.Find(".txt"))+".csv";
// 		if(pDoc->m_data.m_bUseCLog)
// 			strpath1.Format("C:\\Glim\\Data\\Log\\%s\\%s\\Mis\\",data[0],strLot);
// 		else
// 			strpath1.Format("D:\\Data\\Data\\Log\\%s\\%s\\Mis\\",data[0],strLot);

		CreateDirectory(strpath1,NULL);
		CFileFind cfile;
		BOOL b;
		m_strOldFilename2 = filename2;
		b = cfile.FindFile(oldfile);
		if(!b)	return ;
		else{
			//move
			MoveFile(oldfile,oldfile1);
			//			rename(oldfile,oldfile1);
		}
	}
	else{
		m_strOldFilename2 = filename2;
		m_strOldFilename3 = filename3;
	}
}

void CVisWebView::fnWriteData6(CString strLot,int nMeter,double dtopscale,double dbackscame,int nLine,CString strtop,CString strback,CString strmis) //미스매치부 탑백 동기화 관련
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CStdioFile   file;
	CString filename,filename1;
	CString strtmp,str,strTitle,strpath,strOkNg,strpc,strtmp1,strtmp2,strtmp3,strtmp4,strtmp5,strtmp6,strtime,strpath1;
	CString txtscr,txtdst;
	int nPcno =0;
	//날자 LotNo. Frame	DefectCount	Defect-Class	x-Pos	Y-Pos	X-Size	Y-Size	ImagePath
	//////////////
	CString data[6];
	CTime ttime=CTime::GetCurrentTime();	
	CString kk = ttime.Format("%Y%m%d");

	CTime timer=CTime::GetCurrentTime();	
	data[0].Format("%d", timer.GetYear());
	if(timer.GetMonth() < 10)		data[1].Format("0%d", timer.GetMonth());
	else		data[1].Format("%d", timer.GetMonth());
	if(timer.GetDay() < 10)		data[2].Format("0%d", timer.GetDay());
	else		data[2].Format("%d", timer.GetDay());
	if(timer.GetHour() < 10)		data[3].Format("0%d", timer.GetHour());
	else		data[3].Format("%d", timer.GetHour());
	if(timer.GetMinute() < 10)		data[4].Format("0%d", timer.GetMinute());
	else		data[4].Format("%d", timer.GetMinute());
	if(timer.GetSecond() < 10)		data[5].Format("0%d", timer.GetSecond());
	else		data[5].Format("%d", timer.GetSecond());

// 	if(pDoc->m_data.m_bUseCLog){
// 		strpath.Format("C:\\Glim\\");
// 		CreateDirectory(strpath,NULL);//년월일
// 		strpath.Format("C:\\Glim\\Data\\");
// 		CreateDirectory(strpath,NULL);//년월일
// 		strpath.Format("C:\\Glim\\Data\\Log\\");
// 		CreateDirectory(strpath,NULL);//년월일
// 		strpath.Format("C:\\Glim\\Data\\Log\\%s\\",data[0]);
// 		CreateDirectory(strpath,NULL);//년월일
// 		strpath.Format("C:\\Glim\\Data\\Log\\%s\\%s\\",data[0],strLot);
// 		CreateDirectory(strpath,NULL);
// 		strpath1.Format("C:\\Glim\\Data\\Log\\%s\\%s\\Move\\",data[0],strLot);
// 		CreateDirectory(strpath1,NULL);
// 	}
// 	else{
		strpath.Format("D:\\Data\\");
		CreateDirectory(strpath,NULL);//년월일
		strpath.Format("D:\\Data\\Data\\");
		CreateDirectory(strpath,NULL);//년월일
		strpath.Format("D:\\Data\\Data\\Log\\");
		CreateDirectory(strpath,NULL);//년월일
		strpath.Format("D:\\Data\\Data\\Log\\%s\\",data[0]);
		CreateDirectory(strpath,NULL);//년월일
		strpath.Format("D:\\Data\\Data\\Log\\%s\\%s%s\\",data[0],data[1],data[2]);
		CreateDirectory(strpath,NULL);//년월일
		strpath.Format("D:\\Data\\Data\\Log\\%s\\%s%s\\%s\\",data[0],data[1],data[2],strLot);
		CreateDirectory(strpath,NULL);
		strpath1.Format("D:\\Data\\Data\\Log\\%s\\%s%s\\%s\\Move\\",data[0],data[1],data[2],strLot);
		CreateDirectory(strpath1,NULL);


	//}
	CreateDirectory(strpath1,NULL);
	int nm1 = nMeter + pDoc->m_pDlgInterface->m_dTopBackDistance;
	if(pDoc->m_data.m_strComName.Mid(8,1)=="M")
		nm1 = nMeter + pDoc->m_pDlgInterface->m_dTopBackDistance;


	filename.Format("%s%s_%d.csv",strpath,pDoc->m_data.m_strComName,nm1);
	filename1.Format("%s%s_%d.csv",strpath1,pDoc->m_data.m_strComName,nm1);

	strtmp1 = strtmp2 = strtmp3 = strtmp4 =strtmp5=strtmp6= "";

	CString sttrtile1,sttrtile2,sttrtile3,sttrtile4,sttrtile5,sttrtile6;
	strtime.Format("%s년%s월%s일%s시%s분%s초",data[0],data[1],data[2],data[3],data[4],data[5]);
	int nCount1 = nLine;
	int nc1 = 0;
	double d1=0,doffsetScale=0.002485;
	int nCalPos = 0;
	double d2=0,d3;

	int ntopback =0;
	if(m_strComputerName.Find("BACK")>=0 ||  pDoc->m_data.m_strComName.Mid(9,1)=="B" )ntopback = 1;	 

	strtmp2 = m_strTopMismatch;

	strtmp.Format("%d,%.8f,%.8f,%d,%s%s%s",nm1,dtopscale,dbackscame,nLine,strtop,strback,strmis);
	//	strtmp.Format("%s,%s,%s,%d,%d,%d,%s",strtime,m_strComputerName,strLot,nMeter,frame,nLineCount,strtmp2);
	if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
	{		
		if(file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText))
		{
			file.WriteString(strtmp);
			file.Close();
		}
	}
	else
	{
		file.SeekToEnd();
		file.WriteString("\n");
		file.WriteString(strtmp);
		file.Close(); 
	}

	if(m_strOldFilename != filename && m_strOldFilename!=""){
		CString oldfile,oldfile1;
		oldfile = m_strOldFilename;
		oldfile1 = m_strOldFilename1;//.Left(m_strOldFilename.Find(".txt"))+".csv";
// 		if(pDoc->m_data.m_bUseCLog)
// 			strpath1.Format("C:\\Glim\\Data\\Log\\%s\\%s\\Move\\",data[0],strLot);
// 		else
// 			strpath1.Format("D:\\Data\\Data\\Log\\%s\\%s\\Move\\",data[0],strLot);

		CreateDirectory(strpath1,NULL);
		CFileFind cfile;
		BOOL b;
		m_strOldFilename = filename;
		b = cfile.FindFile(oldfile);
		if(!b)	return ;
		else{
			//move
			MoveFile(oldfile,oldfile1);
			//			rename(oldfile,oldfile1);
		}
	}
	else{
		m_strOldFilename = filename;
		m_strOldFilename1 = filename1;
	}
}




void CVisWebView::fnWriteData7(CString strLot,int nMeter,double dtopscale,double dbackscame,int nLine,CString strtop,CString strback,CString strmis,CString strwid1,CString strwid2) //미스매치부 탑백 동기화 관련
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CStdioFile   file;
	CString filename,filename1;
	CString strtmp,str,strTitle,strpath,strOkNg,strpc,strtmp1,strtmp2,strtmp3,strtmp4,strtmp5,strtmp6,strtime,strpath1;
	CString txtscr,txtdst;
	int nPcno =0;
	//날자 LotNo. Frame	DefectCount	Defect-Class	x-Pos	Y-Pos	X-Size	Y-Size	ImagePath
	//////////////
	CString data[6];
	CTime ttime=CTime::GetCurrentTime();	
	CString kk = ttime.Format("%Y%m%d");

	CTime timer=CTime::GetCurrentTime();	
	data[0].Format("%d", timer.GetYear());
	if(timer.GetMonth() < 10)		data[1].Format("0%d", timer.GetMonth());
	else		data[1].Format("%d", timer.GetMonth());
	if(timer.GetDay() < 10)		data[2].Format("0%d", timer.GetDay());
	else		data[2].Format("%d", timer.GetDay());
	if(timer.GetHour() < 10)		data[3].Format("0%d", timer.GetHour());
	else		data[3].Format("%d", timer.GetHour());
	if(timer.GetMinute() < 10)		data[4].Format("0%d", timer.GetMinute());
	else		data[4].Format("%d", timer.GetMinute());
	if(timer.GetSecond() < 10)		data[5].Format("0%d", timer.GetSecond());
	else		data[5].Format("%d", timer.GetSecond());

// 	if(pDoc->m_data.m_bUseCLog){
// 		strpath.Format("C:\\Glim\\");
// 		CreateDirectory(strpath,NULL);//년월일
// 		strpath.Format("C:\\Glim\\Data\\");
// 		CreateDirectory(strpath,NULL);//년월일
// 		strpath.Format("C:\\Glim\\Data\\Log\\");
// 		CreateDirectory(strpath,NULL);//년월일
// 		strpath.Format("C:\\Glim\\Data\\Log\\%s\\",data[0]);
// 		CreateDirectory(strpath,NULL);//년월일
// 		strpath.Format("C:\\Glim\\Data\\Log\\%s\\%s\\",data[0],strLot);
// 		CreateDirectory(strpath,NULL);
// 		strpath1.Format("C:\\Glim\\Data\\Log\\%s\\%s\\Move\\",data[0],strLot);
// 		CreateDirectory(strpath1,NULL);
// 	}
// 	else{
		strpath.Format("D:\\Data\\");
		CreateDirectory(strpath,NULL);//년월일
		strpath.Format("D:\\Data\\Data\\");
		CreateDirectory(strpath,NULL);//년월일
		strpath.Format("D:\\Data\\Data\\Log\\");
		CreateDirectory(strpath,NULL);//년월일
		strpath.Format("D:\\Data\\Data\\Log\\%s\\",data[0]);
		CreateDirectory(strpath,NULL);//년월일
		strpath.Format("D:\\Data\\Data\\Log\\%s\\%s%s\\",data[0],data[1],data[2]);
		CreateDirectory(strpath,NULL);//년월일
		strpath.Format("D:\\Data\\Data\\Log\\%s\\%s%s\\%s\\",data[0],data[1],data[2],strLot);
		CreateDirectory(strpath,NULL);
		strpath1.Format("D:\\Data\\Data\\Log\\%s\\%s%s\\%s\\Move\\",data[0],data[1],data[2],strLot);
		CreateDirectory(strpath1,NULL);


	//}
	CreateDirectory(strpath1,NULL);
	int nm1 = nMeter + pDoc->m_pDlgInterface->m_dTopBackDistance;
	if(pDoc->m_data.m_strComName.Mid(8,1)=="M")
		nm1 = nMeter + pDoc->m_pDlgInterface->m_dTopBackDistance;


	filename.Format("%s%s_%d.csv",strpath,pDoc->m_data.m_strComName,nm1);
	filename1.Format("%s%s_%d.csv",strpath1,pDoc->m_data.m_strComName,nm1);

	strtmp1 = strtmp2 = strtmp3 = strtmp4 =strtmp5=strtmp6= "";

	CString sttrtile1,sttrtile2,sttrtile3,sttrtile4,sttrtile5,sttrtile6;
	strtime.Format("%s년%s월%s일%s시%s분%s초",data[0],data[1],data[2],data[3],data[4],data[5]);
	int nCount1 = nLine;
	int nc1 = 0;
	double d1=0,doffsetScale=0.002485;
	int nCalPos = 0;
	double d2=0,d3;

	int ntopback =0;
	if(m_strComputerName.Find("BACK")>=0 ||  pDoc->m_data.m_strComName.Mid(9,1)=="B" )ntopback = 1;	 

	strtmp2 = m_strTopMismatch;

	strtmp.Format("%d,%.8f,%.8f,%d,%s%s%s%s%s",nm1,dtopscale,dbackscame,nLine,strtop,strback,strmis,strwid1,strwid2);
	//	strtmp.Format("%s,%s,%s,%d,%d,%d,%s",strtime,m_strComputerName,strLot,nMeter,frame,nLineCount,strtmp2);
	if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
	{		
		if(file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText))
		{
			file.WriteString(strtmp);
			file.Close();
		}
	}
	else
	{
		file.SeekToEnd();
		file.WriteString("\n");
		file.WriteString(strtmp);
		file.Close(); 
	}

	if(m_strOldFilename != filename && m_strOldFilename!=""){
		CString oldfile,oldfile1;
		oldfile = m_strOldFilename;
		oldfile1 = m_strOldFilename1;//.Left(m_strOldFilename.Find(".txt"))+".csv";
// 		if(pDoc->m_data.m_bUseCLog)
// 			strpath1.Format("C:\\Glim\\Data\\Log\\%s\\%s\\Move\\",data[0],strLot);
//		else
			strpath1.Format("D:\\Data\\Data\\Log\\%s\\%s\\Move\\",data[0],strLot);

		CreateDirectory(strpath1,NULL);
		CFileFind cfile;
		BOOL b;
		m_strOldFilename = filename;
		b = cfile.FindFile(oldfile);
		if(!b)	return ;
		else{
			//move
			MoveFile(oldfile,oldfile1);
			//			rename(oldfile,oldfile1);
		}
	}
	else{
		m_strOldFilename = filename;
		m_strOldFilename1 = filename1;
	}
}

//void CVisWebView::fnWriteData7(,,,,,,,,CString strwid1,CString strwid2) //미스매치부 탑백 동기화 관련
void CVisWebView::fnWriteDataFull(CString strLot, int nMeter, double dtopscale1, double dbackscale1,double dtopscale2, double dbackscale2, int nLine,CString strHmis,CString strMmis,
								  CString strHtop, CString strHback,CString strMtop, CString strMback, CString strHwid1,CString strHwid2,CString strMwid1,CString strMwid2) //미스매치부 탑백 동기화 관련
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CStdioFile   file;
	CString filename,filename1;
	CString strtmp,str,strTitle,strpath,strOkNg,strpc,strtmp1,strtmp2,strtmp3,strtmp4,strtmp5,strtmp6,strtime,strpath1;
	CString txtscr,txtdst;
	int nPcno =0;
	//날자 LotNo. Frame	DefectCount	Defect-Class	x-Pos	Y-Pos	X-Size	Y-Size	ImagePath
	//////////////
	CString data[6];
	CTime ttime=CTime::GetCurrentTime();	
	CString kk = ttime.Format("%Y%m%d");
	CTime timer=CTime::GetCurrentTime();	
	data[0].Format("%d", timer.GetYear());
	if(timer.GetMonth() < 10)		data[1].Format("0%d", timer.GetMonth());
	else		data[1].Format("%d", timer.GetMonth());
	if(timer.GetDay() < 10)		data[2].Format("0%d", timer.GetDay());
	else		data[2].Format("%d", timer.GetDay());
	if(timer.GetHour() < 10)		data[3].Format("0%d", timer.GetHour());
	else		data[3].Format("%d", timer.GetHour());
	if(timer.GetMinute() < 10)		data[4].Format("0%d", timer.GetMinute());
	else		data[4].Format("%d", timer.GetMinute());
	if(timer.GetSecond() < 10)		data[5].Format("0%d", timer.GetSecond());
	else		data[5].Format("%d", timer.GetSecond());

// 	if(pDoc->m_data.m_bUseCLog){
// 		strpath.Format("C:\\Glim\\");
// 		CreateDirectory(strpath,NULL);//년월일
// 		strpath.Format("C:\\Glim\\Data\\");
// 		CreateDirectory(strpath,NULL);//년월일
// 		strpath.Format("C:\\Glim\\Data\\Log\\");
// 		CreateDirectory(strpath,NULL);//년월일
// 		strpath.Format("C:\\Glim\\Data\\Log\\%s\\",data[0]);
// 		CreateDirectory(strpath,NULL);//년월일
// 		strpath.Format("C:\\Glim\\Data\\Log\\%s\\%s\\",data[0],strLot);
// 		CreateDirectory(strpath,NULL);
// 		strpath1.Format("C:\\Glim\\Data\\Log\\%s\\%s\\Move\\",data[0],strLot);
// 		CreateDirectory(strpath1,NULL);
// 	}
// 	else{

		strpath.Format("D:\\Data\\LotData\\");
		CreateDirectory(strpath,NULL); 
		strpath.Format("D:\\Data\\LotData\\%s%s%s\\",data[0],data[1],data[2]);
		CreateDirectory(strpath,NULL); 
		strpath.Format("D:\\Data\\LotData\\%s%s%s\\%s\\",data[0],data[1],data[2],strLot);
		CreateDirectory(strpath,NULL); 
		filename.Format("%s%s_FullData.csv",strpath,strLot);
// 
// 	}
	CreateDirectory(strpath1,NULL);
	int nm1 = nMeter + pDoc->m_pDlgInterface->m_dTopBackDistance;
	if(pDoc->m_data.m_strComName.Mid(8,1)=="M")
		nm1 = nMeter + pDoc->m_pDlgInterface->m_dTopBackDistance;
	
	CString strmm1,strmm2,strHTW,strHBW,strMTW,strMBW,strHTPx,strHBPx,strMTPx,strMBPx,strTmpTitle, strEPC;		// 20201016 kjh
	strmm1=strmm2=strHTW=strHBW=strMTW=strMBW=strHTPx=strHBPx=strMTPx=strMBPx=strTmpTitle=strEPC=_T("");
	for(int i=0; i<nLine; i++){
		if(i==0)
			strEPC.Format(_T("(EPC)"));
		else
			strEPC.Format(_T(""));

		strTmpTitle.Format(_T("Mismatch %d"),i+1);
		strmm1 += strTmpTitle+strEPC+_T(",");

		strTmpTitle.Format(_T("Final Mismatch %d"),i+1);
		strmm2 += strTmpTitle+strEPC+_T(",");

		strTmpTitle.Format(_T("Top Head Width %d"),i+1);
		strHTW += strTmpTitle+strEPC+_T(",");

		strTmpTitle.Format(_T("Back Head Width %d"),i+1);
		strHBW += strTmpTitle+strEPC+_T(",");

		strTmpTitle.Format(_T("Mismatch Top Width %d"),i+1);
		strMTW += strTmpTitle+strEPC+_T(",");

		strTmpTitle.Format(_T("Mismatch Back Width %d"),i+1);
		strMBW += strTmpTitle+strEPC+_T(",");

		strTmpTitle.Format(_T("Top Head Pixel %d"),i+1);
		strHTPx += strTmpTitle+strEPC+_T(",");

		strTmpTitle.Format(_T("Back Head Pixel %d"),i+1);
		strHBPx += strTmpTitle+strEPC+_T(",");

		strTmpTitle.Format(_T("Mismatch Top Pixel %d"),i+1);
		strMTPx += strTmpTitle+strEPC+_T(",");

		strTmpTitle.Format(_T("Mismatch Back Pixel %d"),i+1);
		strMBPx += strTmpTitle+strEPC+_T(",");

	}

	strtmp1 = strtmp2 = strtmp3 = strtmp4 =strtmp5=strtmp6= "";
	strTitle.Format(_T("Time,Lot,Meter,Top Scale,Back Scale,MisTop Scale,MIsBack Scale,Edge,%s%s%s%s%s%s%s%s%s%s"), strmm1,strmm2,strHTW,strHBW,strMTW,strMBW,strHTPx,strHBPx,strMTPx,strMBPx);

	CString sttrtile1,sttrtile2,sttrtile3,sttrtile4,sttrtile5,sttrtile6;
	strtime.Format("%s-%s-%s-%s:%s:%s",data[0],data[1],data[2],data[3],data[4],data[5]);
	int nCount1 = nLine;
//date,lot,  data는 뒤에,
	strtmp.Format("%s,%s,%d,%.8f,%.8f,%.8f,%.8f,%d,%s%s%s%s%s%s%s%s%s%s",
		strtime,strLot,nMeter,dtopscale1,dbackscale1,dtopscale2,dbackscale2,nLine,strHmis,strMmis,strHtop,strHback,strMtop,strMback,strHwid1,strHwid2,strMwid1,strMwid2);

	//	strtmp.Format("%s,%s,%s,%d,%d,%d,%s",strtime,m_strComputerName,strLot,nMeter,frame,nLineCount,strtmp2);
	if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
	{		
		if(file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText))
		{
			file.WriteString(strTitle);
			file.WriteString("\n");
			file.WriteString(strtmp);
			file.Close();
		}
	}
	else
	{
		file.SeekToEnd();
		file.WriteString("\n");
		file.WriteString(strtmp);
		file.Close(); 
	}

}

void CVisWebView::fnWriteDataFull1(CString strLot, int nMeter, double dtopscale1, double dbackscale1,double dtopscale2, double dbackscale2, int nLine,CString strHmis,CString strMmis,
								  CString strHtop, CString strHback,CString strMtop, CString strMback, CString strHwid1,CString strHwid2,CString strMwid1,CString strMwid2) //미스매치부 탑백 동기화 관련
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CStdioFile   file;
	CString filename,filename1;
	CString strtmp,str,strTitle,strpath,strOkNg,strpc,strtmp1,strtmp2,strtmp3,strtmp4,strtmp5,strtmp6,strtime,strpath1;
	CString txtscr,txtdst;
	int nPcno =0;
	//날자 LotNo. Frame	DefectCount	Defect-Class	x-Pos	Y-Pos	X-Size	Y-Size	ImagePath
	//////////////
	CString data[6];
	CTime ttime=CTime::GetCurrentTime();	
	CString kk = ttime.Format("%Y%m%d");
	CTime timer=CTime::GetCurrentTime();	
	data[0].Format("%d", timer.GetYear());
	if(timer.GetMonth() < 10)		data[1].Format("0%d", timer.GetMonth());
	else		data[1].Format("%d", timer.GetMonth());
	if(timer.GetDay() < 10)		data[2].Format("0%d", timer.GetDay());
	else		data[2].Format("%d", timer.GetDay());
	if(timer.GetHour() < 10)		data[3].Format("0%d", timer.GetHour());
	else		data[3].Format("%d", timer.GetHour());
	if(timer.GetMinute() < 10)		data[4].Format("0%d", timer.GetMinute());
	else		data[4].Format("%d", timer.GetMinute());
	if(timer.GetSecond() < 10)		data[5].Format("0%d", timer.GetSecond());
	else		data[5].Format("%d", timer.GetSecond());

// 	if(pDoc->m_data.m_bUseCLog){
// 		strpath.Format("C:\\Glim\\");
// 		CreateDirectory(strpath,NULL);//년월일
// 		strpath.Format("C:\\Glim\\Data\\");
// 		CreateDirectory(strpath,NULL);//년월일
// 		strpath.Format("C:\\Glim\\Data\\Log\\");
// 		CreateDirectory(strpath,NULL);//년월일
// 		strpath.Format("C:\\Glim\\Data\\Log\\%s\\",data[0]);
// 		CreateDirectory(strpath,NULL);//년월일
// 		strpath.Format("C:\\Glim\\Data\\Log\\%s\\%s\\",data[0],strLot);
// 		CreateDirectory(strpath,NULL);
// 		strpath1.Format("C:\\Glim\\Data\\Log\\%s\\%s\\Move\\",data[0],strLot);
// 		CreateDirectory(strpath1,NULL);
// 	}
// 	else{

		strpath.Format("D:\\Data\\LotData\\");
		CreateDirectory(strpath,NULL); 
		strpath.Format("D:\\Data\\LotData\\%s%s%s\\",data[0],data[1],data[2]);
		CreateDirectory(strpath,NULL); 
		strpath.Format("D:\\Data\\LotData\\%s%s%s\\%s\\",data[0],data[1],data[2],strLot);
		CreateDirectory(strpath,NULL); 
		filename.Format("%s%s_FullData.csv",strpath,strLot);

//	}
	CreateDirectory(strpath1,NULL);
	int nm1 = nMeter + pDoc->m_pDlgInterface->m_dTopBackDistance;
	if(pDoc->m_data.m_strComName.Mid(8,1)=="M")
		nm1 = nMeter + pDoc->m_pDlgInterface->m_dTopBackDistance;



	strtmp1 = strtmp2 = strtmp3 = strtmp4 =strtmp5=strtmp6= "";

	CString sttrtile1,sttrtile2,sttrtile3,sttrtile4,sttrtile5,sttrtile6;
	strtime.Format("%s-%s-%s-%s:%s:%s",data[0],data[1],data[2],data[3],data[4],data[5]);
	int nCount1 = nLine;
	//date,lot,  data는 뒤에,
	strtmp.Format("%s,%s,%d,%.8f,%.8f,%.8f,%.8f,%d,%s%s%s%s%s%s%s%s%s%s",
		strtime,strLot,nMeter,dtopscale1,dbackscale1,dtopscale2,dbackscale2,nLine,strHmis,strMmis,strHtop,strHback,strMtop,strMback,strHwid1,strHwid2,strMwid1,strMwid2);

	CString strEPC=_T("(EPC)");
	CString strtitlemis="",strtitlehtop="",strtitilehback="",strtitlemistop="",strtitlemisback="",strnnumeric="",strtopp="",strbbackp="",strtopp1="",strbackp1="";
	for(int i=0;i<nLine;i++){
		strnnumeric.Format("%d",i+1);
		strtitlemis += "Mismatch"+strnnumeric+",";
		strtitlehtop += "HTopPitch"+strnnumeric+",";
		strtitilehback += "HBackPitch"+strnnumeric+",";
		strtitlemistop += "MisTopPitch"+strnnumeric+",";
		strtitlemisback += "MisBackpitch"+strnnumeric+",";
		strtopp += "HTopPixel"+strnnumeric+",";
		strbbackp += "HBackPixel"+strnnumeric+",";
		strtopp1 += "MisTopPixel"+strnnumeric+",";
		strbackp1 += "MisBackPixel"+strnnumeric+",";

		if(i==0){					// 20201014 kjh
			strtitlemis += strEPC;
			strtitlehtop += strEPC;
			strtitlemistop += strEPC;
			strtitlemisback += strEPC;
			strtopp += strEPC;
			strtopp1 += strEPC;
			strbackp1 += strEPC;
		}

		if(i==nLine-1){
			strtitilehback += strEPC;
			strtitlemisback += strEPC;
			strbbackp += strEPC;
		}
	}
	strTitle.Format("시간,Lot,Meter,H/TScale,H/BScale,M/TScale,M/BScale,검출라인수,%s%s%s%s%s%s%s%s%s%s",strtitlemis,strtitlemis,strtitlehtop,strtitilehback,strtitlemistop,strtitlemisback,strtopp,strbbackp,strtopp1,strbackp1);
	//	strtmp.Format("%s,%s,%s,%d,%d,%d,%s",strtime,m_strComputerName,strLot,nMeter,frame,nLineCount,strtmp2);
	if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
	{		
		if(file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText))
		{
			file.WriteString(strTitle);
			file.WriteString("\n");
			file.WriteString(strtmp);
			file.Close();
		}
	}
	else
	{
		file.SeekToEnd();
		file.WriteString("\n");
		file.WriteString(strtmp);
		file.Close(); 
	}

}


void CVisWebView::fnDataPut(CString strInput,int nMeter,int ncount, int nRevserse) //ncount 1M 내에 몇번째 텍스트인지
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
//먼저 들어온 문자를 분리하여 개수를 파악한다.
	CString strTok;    
	int sepCount =0;
	for(int i=0;i<strInput.GetLength();i++)	if(strInput.GetAt(i) == ',')	sepCount++;
	CString* temp1 = new CString[sepCount+1]; 
	int cnt=0,ndata = 7;//정확히는 
	while(AfxExtractSubString(strTok, strInput, cnt, ','))  
		temp1[cnt++] = strTok;// 해당 배열에 순차적으로 넣어준다.
	//	strTitle.Format("년월일시분초,PC,LotID,Meter,FrameNo,Scale,LineCount%s",sttrtile4);//,sttrtile5,sttrtile6);
//	m_nFullLineData[2][100][10][MAX_LENGTH];//Data Push용 버퍼 -탑/백 , 100미터 , 10프레임 , 최대라인수20개(0번은 총라인개수, 1번부터 라인픽셀)
	//Data input
	double dscale = atof(temp1[5]);//scale
	m_dTopScale = dscale;//탑 스케일 넣기 백에서 사용
	int nLineCount = atoi(temp1[6]);
	int nMeter1 = (nMeter+1)%100;
	if(nRevserse==0)
	{
		dscale = pDoc->m_data.m_dScaleFactorX[0];
		nLineCount = atoi(temp1[5]);
		ndata = 6;
	}
	for(int i=0;i<nLineCount && i<MAX_LENGTH-3 && ndata+i<sepCount+1;i++){
		pDoc->m_data.m_nFullLineData[0][nMeter][ncount][i] = atof(temp1[ndata+i]);
		pDoc->m_data.m_nFullLineData[0][nMeter1][0][i] = atof(temp1[ndata+i]);
		for(int k=ncount+1;k<8;k++){//서브프레임도 채운다
			pDoc->m_data.m_nFullLineData[0][nMeter][k][i] = atof(temp1[ndata+i]);
			pDoc->m_data.m_nFullLineData[0][nMeter1][k][i] = atof(temp1[ndata+i]);
		}
	}
	if(ncount>8)ncount = 8;
	pDoc->m_data.m_nFullLineData[0][nMeter][ncount][MAX_LENGTH-1] = dscale;//int로 선언했으므로 1000000을 곱한다. 더블 형으로 수정
	pDoc->m_data.m_nFullLineData[0][nMeter][ncount][MAX_LENGTH-2] = nLineCount;//개수
	pDoc->m_data.m_nFullLineData[0][nMeter][ncount+1][MAX_LENGTH-1] = dscale;//int로 선언했으므로 1000000을 곱한다.
	pDoc->m_data.m_nFullLineData[0][nMeter][ncount+1][MAX_LENGTH-2] = nLineCount;//개수

	pDoc->m_data.m_nFullLineData[0][nMeter1][0][MAX_LENGTH-1] = dscale;//int로 선언했으므로 1000000을 곱한다.
	pDoc->m_data.m_nFullLineData[0][nMeter1][0][MAX_LENGTH-2] = nLineCount;//개수
	pDoc->m_data.m_nFullLineData[0][nMeter1][0+1][MAX_LENGTH-1] = dscale;//int로 선언했으므로 1000000을 곱한다.
	pDoc->m_data.m_nFullLineData[0][nMeter1][0+1][MAX_LENGTH-2] = nLineCount;//개수

	delete[] temp1;

}
void CVisWebView::fnDataPut1(CString strInput,int nMeter,int ncount, int nRevserse) //ncount 1M 내에 몇번째 텍스트인지
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	//먼저 들어온 문자를 분리하여 개수를 파악한다.
	CString strTok;    
	int sepCount =0;
	for(int i=0;i<strInput.GetLength();i++)	if(strInput.GetAt(i) == ',')	sepCount++;
	if(sepCount<=6){
		if(ncount>1){
			for(int i=0;i<30 && i<MAX_LENGTH-3 &&pDoc->m_data.m_dMisData[ncount-1][0]==-1000 && ncount<100;i++){
				//m_nReadCount
				if(i==0){
					pDoc->m_data.m_dMisData[ncount][i] =  -1000;
					pDoc->m_data.m_dMisData[ncount+1][i] =  -1000;
				}
				else{
					pDoc->m_data.m_dMisData[ncount][i] =  pDoc->m_data.m_dMisData[ncount-1][i];
					for(int k=ncount+1;k<8;k++)
						pDoc->m_data.m_dMisData[k][i] =  pDoc->m_data.m_dMisData[ncount][i];
				}
			}
		}
		return;
	}
	CString* temp1 = new CString[sepCount+1]; 
	int cnt=0,ndata = 6;//정확히는 
	while(AfxExtractSubString(strTok, strInput, cnt, ','))  
		temp1[cnt++] = strTok;// 해당 배열에 순차적으로 넣어준다.
	//	strTitle.Format("년월일시분초,PC,LotID,Meter,FrameNo,Scale,LineCount%s",sttrtile4);//,sttrtile5,sttrtile6);
	//	m_nFullLineData[2][100][10][MAX_LENGTH];//Data Push용 버퍼 -탑/백 , 100미터 , 10프레임 , 최대라인수20개(0번은 총라인개수, 1번부터 라인픽셀)
	//Data input
	double dscale = atof(temp1[5]);//scale
	int nLineCount = atoi(temp1[5]);
	if(nRevserse==0)
	{
		dscale = pDoc->m_data.m_dScaleFactorX[0];
		nLineCount = atoi(temp1[5]);
		ndata = 6;
	}
	for(int i=0;i<nLineCount && i<MAX_LENGTH-3 && ncount<100;i++){
		//m_nReadCount
		if(i==0){
			pDoc->m_data.m_dMisData[ncount][i] =  -1000;
			pDoc->m_data.m_dMisData[ncount+1][i] =  -1000;
		}
		else{
			pDoc->m_data.m_dMisData[ncount][i] =  atof(temp1[ndata+i])*-1;
			pDoc->m_data.m_dMisData[ncount+1][i] =  atof(temp1[ndata+i])*-1;
		}
// 		pDoc->m_data.m_nFullLineData[1][nMeter][ncount][i] = atof(temp1[ndata+i]);
// 		pDoc->m_data.m_nFullLineData[1][nMeter][ncount+1][i] = atof(temp1[ndata+i]);
	}
	delete[] temp1;
} 

void CVisWebView::fnDataPut2(CString strInput,int nMeter,int ncount, int nRevserse) //ncount 1M 내에 몇번째 텍스트인지
{//MIS부 DATA 입력
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	//먼저 들어온 문자를 분리하여 개수를 파악한다.
	CString strTok;    
	int sepCount =0;
	for(int i=0;i<strInput.GetLength();i++)	if(strInput.GetAt(i) == ',')	sepCount++;
	// 	if(sepCount<=6){
	// 		if(ncount>1){
	// 			for(int i=0;i<30 && i<MAX_LENGTH-3 &&pDoc->m_data.m_dMisData[ncount-1][0]==-1000 && ncount<100;i++){
	// 				//m_nReadCount
	// 				if(i==0){
	// 					pDoc->m_data.m_dMisData[ncount][i] =  -1000;
	// 					pDoc->m_data.m_dMisData[ncount+1][i] =  -1000;
	// 				}
	// 				else{
	// 					pDoc->m_data.m_dMisData[ncount][i] =  pDoc->m_data.m_dMisData[ncount-1][i];
	// 					for(int k=ncount+1;k<8;k++)
	// 						pDoc->m_data.m_dMisData[k][i] =  pDoc->m_data.m_dMisData[ncount][i];
	// 				}
	// 			}
	// 		}
	// 		return;
	// 	}
	CString* temp1 = new CString[sepCount+1]; 
	int cnt=0,ndata = 6;//정확히는 
	while(AfxExtractSubString(strTok, strInput, cnt, ','))  
		temp1[cnt++] = strTok;// 해당 배열에 순차적으로 넣어준다.
	//	strTitle.Format("년월일시분초,PC,LotID,Meter,FrameNo,Scale,LineCount%s",sttrtile4);//,sttrtile5,sttrtile6);
	//	m_nFullLineData[2][100][10][MAX_LENGTH];//Data Push용 버퍼 -탑/백 , 100미터 , 10프레임 , 최대라인수20개(0번은 총라인개수, 1번부터 라인픽셀)
	//Data input
	//1 meter 
	int nMn1 = atoi(temp1[0]);
	pDoc->m_data.m_dMisbatchScale[0] = atof(temp1[1]);
	pDoc->m_data.m_dMisbatchScale[1] = atof(temp1[2]);
	pDoc->m_data.m_nMismatchLine = atoi(temp1[3]);
	int nGap = pDoc->m_data.m_nMismatchLine;
	for(int i=0;i<pDoc->m_data.m_nMismatchLine;i++){
		if(sepCount <=4+i+(nGap*4) )break;
		pDoc->m_data.m_dMisTopBackData1[0][i] = atof(temp1[4+i+(nGap*0)]);
		pDoc->m_data.m_dMisTopBackData1[1][i] = atof(temp1[4+i+(nGap*1)]);
		pDoc->m_data.m_dMisTopBackData1[2][i] = atof(temp1[4+i+(nGap*2)]);
		pDoc->m_data.m_dMisTopBackData1[3][i] = atof(temp1[4+i+(nGap*3)]);//top wid
		pDoc->m_data.m_dMisTopBackData1[4][i] = atof(temp1[4+i+(nGap*4)]);//back wid
	}

	delete[] temp1;


} 

void CVisWebView::fnDataPut3(CString strInput,int nMeter,int ncount, int nRevserse) //ncount 1M 내에 몇번째 텍스트인지
{//MIS부 DATA 입력
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	//먼저 들어온 문자를 분리하여 개수를 파악한다.
	CString strTok;    
	int sepCount =0;
	for(int i=0;i<strInput.GetLength();i++)	if(strInput.GetAt(i) == ',')	sepCount++;

	CString* temp1 = new CString[sepCount+1]; 
	int cnt=0,ndata = 4;//정확히는 //0meter 1topscale 2backscale 3count 4topdata
	while(AfxExtractSubString(strTok, strInput, cnt, ','))  
		temp1[cnt++] = strTok;// 해당 배열에 순차적으로 넣어준다.
	//	strTitle.Format("년월일시분초,PC,LotID,Meter,FrameNo,Scale,LineCount%s",sttrtile4);//,sttrtile5,sttrtile6);
	//	m_nFullLineData[2][100][10][MAX_LENGTH];//Data Push용 버퍼 -탑/백 , 100미터 , 10프레임 , 최대라인수20개(0번은 총라인개수, 1번부터 라인픽셀)
	//Data input
	//1 meter 
	int nMn1 = atoi(temp1[0]);//meter
	pDoc->m_data.m_dMisbatchScale1[0] = atof(temp1[1]);//topscale
	pDoc->m_data.m_dMisbatchScale1[1] = atof(temp1[2]);//back scale
	pDoc->m_data.m_nMismatchLine1 = atoi(temp1[3]);//line cnt
	int nGap = pDoc->m_data.m_nMismatchLine1;

	int nMeter1 = (nMeter+1)%100;

	////////////////////////////////////////////
	for(int i=0;i<nGap && i<MAX_LENGTH-3 && ndata+i<sepCount+1;i++){
		//thead top
		pDoc->m_data.m_nFullLineData1[0][nMeter][ncount][i] = atof(temp1[ndata+i+(nGap*0)]);
		pDoc->m_data.m_nFullLineData1[0][nMeter1][0][i] = atof(temp1[ndata+i+(nGap*0)]);
		//head back
		pDoc->m_data.m_nFullLineData1[1][nMeter][ncount][i] = atof(temp1[4+i+(nGap*1)]);
		pDoc->m_data.m_nFullLineData1[1][nMeter1][0][i] = atof(temp1[4+i+(nGap*1)]);
		//mis mm
		pDoc->m_data.m_nFullLineData1[2][nMeter][ncount][i] = atof(temp1[4+i+(nGap*2)]);
		pDoc->m_data.m_nFullLineData1[2][nMeter1][0][i] = atof(temp1[4+i+(nGap*2)]);
		//top mm
		pDoc->m_data.m_nFullLineData1[3][nMeter][ncount][i] = atof(temp1[4+i+(nGap*3)]);
		pDoc->m_data.m_nFullLineData1[3][nMeter1][0][i] = atof(temp1[4+i+(nGap*3)]);
		//back mm
		pDoc->m_data.m_nFullLineData1[4][nMeter][ncount][i] = atof(temp1[4+i+(nGap*4)]);
		pDoc->m_data.m_nFullLineData1[4][nMeter1][0][i] = atof(temp1[4+i+(nGap*4)]);

		int j=0;
		for(int k=ncount+1;k<10;k++){//서브프레임도 채운다
			//thead top
			pDoc->m_data.m_nFullLineData1[0][nMeter][k][i] = atof(temp1[ndata+i+(nGap*0)]);
			pDoc->m_data.m_nFullLineData1[0][nMeter1][j][i] = atof(temp1[ndata+i+(nGap*0)]);
			//head back
			pDoc->m_data.m_nFullLineData1[1][nMeter][k][i] = atof(temp1[4+i+(nGap*1)]);
			pDoc->m_data.m_nFullLineData1[1][nMeter1][j][i] = atof(temp1[4+i+(nGap*1)]);
			//mis mm
			pDoc->m_data.m_nFullLineData1[2][nMeter][k][i] = atof(temp1[4+i+(nGap*2)]);
			pDoc->m_data.m_nFullLineData1[2][nMeter1][j][i] = atof(temp1[4+i+(nGap*2)]);
			//top mm
			pDoc->m_data.m_nFullLineData1[3][nMeter][k][i] = atof(temp1[4+i+(nGap*3)]);
			pDoc->m_data.m_nFullLineData1[3][nMeter1][j][i] = atof(temp1[4+i+(nGap*3)]);
			//back mm
			pDoc->m_data.m_nFullLineData1[4][nMeter][k][i] = atof(temp1[4+i+(nGap*4)]);
			pDoc->m_data.m_nFullLineData1[4][nMeter1][j][i] = atof(temp1[4+i+(nGap*4)]);
			j++;
		}
	}
	if(ncount>10)ncount = 10;
	pDoc->m_data.m_nFullLineData1[0][nMeter][ncount][MAX_LENGTH-1] = pDoc->m_data.m_dMisbatchScale1[0];//int로 선언했으므로 1000000을 곱한다. 더블 형으로 수정
	pDoc->m_data.m_nFullLineData1[0][nMeter][ncount][MAX_LENGTH-2] = nGap;//개수
	pDoc->m_data.m_nFullLineData1[0][nMeter][ncount+1][MAX_LENGTH-1] =  pDoc->m_data.m_dMisbatchScale1[0];//int로 선언했으므로 1000000을 곱한다.
	pDoc->m_data.m_nFullLineData1[0][nMeter][ncount+1][MAX_LENGTH-2] = nGap;//개수
	pDoc->m_data.m_nFullLineData1[0][nMeter1][0][MAX_LENGTH-1] =  pDoc->m_data.m_dMisbatchScale1[0];//int로 선언했으므로 1000000을 곱한다.
	pDoc->m_data.m_nFullLineData1[0][nMeter1][0][MAX_LENGTH-2] = nGap;//개수
	pDoc->m_data.m_nFullLineData1[0][nMeter1][0+1][MAX_LENGTH-1] =  pDoc->m_data.m_dMisbatchScale1[0];//int로 선언했으므로 1000000을 곱한다.
	pDoc->m_data.m_nFullLineData1[0][nMeter1][0+1][MAX_LENGTH-2] = nGap;//개수

	pDoc->m_data.m_nFullLineData1[1][nMeter][ncount][MAX_LENGTH-1] = pDoc->m_data.m_dMisbatchScale1[1];//int로 선언했으므로 1000000을 곱한다. 더블 형으로 수정
	pDoc->m_data.m_nFullLineData1[1][nMeter][ncount][MAX_LENGTH-2] = nGap;//개수
	pDoc->m_data.m_nFullLineData1[1][nMeter][ncount+1][MAX_LENGTH-1] =  pDoc->m_data.m_dMisbatchScale1[1];//int로 선언했으므로 1000000을 곱한다.
	pDoc->m_data.m_nFullLineData1[1][nMeter][ncount+1][MAX_LENGTH-2] = nGap;//개수
	pDoc->m_data.m_nFullLineData1[1][nMeter1][0][MAX_LENGTH-1] =  pDoc->m_data.m_dMisbatchScale1[1];//int로 선언했으므로 1000000을 곱한다.
	pDoc->m_data.m_nFullLineData1[1][nMeter1][0][MAX_LENGTH-2] = nGap;//개수
	pDoc->m_data.m_nFullLineData1[1][nMeter1][0+1][MAX_LENGTH-1] =  pDoc->m_data.m_dMisbatchScale1[1];//int로 선언했으므로 1000000을 곱한다.
	pDoc->m_data.m_nFullLineData1[1][nMeter1][0+1][MAX_LENGTH-2] = nGap;//개수

	delete[] temp1;


} 
int CVisWebView::OnebyOneMatch(int nDirect,int nframe, int nLinecount)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	m_nNewAlarm = 0;
	if(m_strComputerName.Find("CHO")>=0){
		for(int i=0;i<nLinecount;i++)
			pDoc->m_data.m_nMisMatchPixel[0][i] = pDoc->m_data.m_nMisMatchPixel[1][i];
		pDoc->m_data.m_dMisMatchLen[0][MAX_LENGTH-1] = pDoc->m_data.m_dScaleFactorX[0];
	}

	double dtmp1[MAX_LENGTH]={0,},dtmp2[MAX_LENGTH]={0,};
	double ntmp1[MAX_LENGTH]={0,},ntmp2[MAX_LENGTH]={0,},nLeft[2]={0,};
	double dLeft[2]={0,};
	int nc1=0,nc2=0;
	double dcamScale[2];
	dcamScale[0] = pDoc->m_data.m_dMisMatchLen[0][MAX_LENGTH-1];
	dcamScale[1] = pDoc->m_data.m_dMisMatchLen[1][MAX_LENGTH-1];//pDoc->m_data.m_dMisMatchData[1][nframe][i]
	if(m_strComputerName.Find("CHO")>=0){
		if(dcamScale[0]<0.07)
		dcamScale[0] += 0.01;
		m_dTopScale = dcamScale[0];

	}
	int ncheck = 0;
	if(pDoc->m_data.m_strComName.Mid(8,1)=="M"){
		for(int i=0;i<MAX_LENGTH;i++){
			if(pDoc->m_data.m_nMisMatchPixel[0][i]>0){
				ntmp1[nc1] = pDoc->m_data.m_nMisMatchPixel[0][i];//reverse data
// 				if(nc1>0 && ntmp1[nc1]-ntmp1[nc1-1]<0)
// 					ncheck++;
				nc1++;
			}
		}
	}
	else{//head부는 데이터를 리버스시킨다.
		for(int i=MAX_LENGTH-2;i>=0;i--){
			if(pDoc->m_data.m_nMisMatchPixel[0][i]>0){
	//			dtmp1[nc1] = pDoc->m_data.m_dMisMatchLen[0][i];
				ntmp1[nc1] = CAM_WIDTH_CIS*3- pDoc->m_data.m_nMisMatchPixel[0][i];//reverse data
				if(nc1>0 && ntmp1[nc1]-ntmp1[nc1-1]<0)
					ncheck++;
				nc1++;
			}
		}
	}


	for(int i=0;i<MAX_LENGTH-1;i++){//20190611 여기 MAX_LENGTH-2로 바꿔서 test해 볼것
		if(pDoc->m_data.m_nMisMatchPixel[1][i]>0){
			nc2++;
		}
	}

	if(nc1 != nc2){
		m_nDataMissing = 1;
		CString strtmp2;
		strtmp2.Format("Data %d,%d",pDoc->m_data.m_nNewTopCount,nc1);
//		AddtoList(strtmp2,0,TRUE);
//		return 1;
	}
	else{
		m_nDataMissing = 0;
		CString strtmp2;
		strtmp2.Format("Data %d,%d",pDoc->m_data.m_nNewTopCount,nc1);
//		AddtoList(strtmp2,0,TRUE);
	}
	//OldData Put
	for(int i=0;i<nc1;i++){
		pDoc->m_data.m_dMisTopBackDataOld[0][i] = pDoc->m_data.m_dMisTopBackData1[0][i];
		pDoc->m_data.m_dMisTopBackDataOld[1][i] = pDoc->m_data.m_dMisTopBackData1[1][i];
		pDoc->m_data.m_dMisTopBackDataOld[2][i] = pDoc->m_data.m_dMisTopBackData1[2][i];
	}

	int nmeter1 = (pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck]+pDoc->m_pDlgInterface->m_nDisplayMeter)%10;
	int nmeter2 = (pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck]+pDoc->m_pDlgInterface->m_nDisplayMeter+1)%10;

	//data gap check
	int ngapoffset = pDoc->m_data.m_nMisMatchPixel[1][0]-ntmp1[0];
	if(nDirect==2)
		ngapoffset = pDoc->m_data.m_nMisMatchPixel[1][nc1-1]-ntmp1[nc1-1];
	for(int i=0;i<nc1;i++){
		ntmp1[i] += ngapoffset;
		pDoc->m_data.m_dMisTopBackData1[0][i] = ntmp1[i];//mismatch 동기화 data  //top data넣기
		
		//10meter
		pDoc->m_data.m_dDrawMisData[0][nmeter1][0][i] = ntmp1[i];
		pDoc->m_data.m_dDrawMisData[0][nmeter2][0][i] = ntmp1[i];

		dtmp1[i] = ntmp1[i]*dcamScale[0];
	}
	double dPitch1[20] = {0,};
	double dPitch2[20] = {0,};
	double dPitch3[20] = {0,};
////////Line edge matching
	//왼족기준으로 데이터의 길이를 새로 구하다.
	nLeft[0] = ntmp1[0];nLeft[1]=pDoc->m_data.m_nMisMatchPixel[1][0];
	CString strPitchGap[40] = {"",};
	for(int i=0;i<nc1;i++){
//길이 계산으 다시한다.
		pDoc->m_data.m_dReversePixelData[i] = ntmp1[i];
		ntmp1[i] -= nLeft[0];
		ntmp2[i] = pDoc->m_data.m_nMisMatchPixel[1][i]-nLeft[1];

		dtmp1[i] = ntmp1[i]*dcamScale[0];
		dtmp2[i] = ntmp2[i]*dcamScale[1];
		pDoc->m_data.m_dReversePitchData[i] = ntmp1[i]*dcamScale[0];
		if(i>0){
			dPitch1[i] = dtmp1[i]-dtmp1[i-1];
			dPitch2[i] = dtmp2[i]-dtmp2[i-1];
//			dPitch3[i] = dtmp2[i]-dtmp2[i-1];
			strPitchGap[i].Format("%.2f",dPitch2[i]-dPitch1[i]);
		}
		else if(i==0){
			dPitch1[i] = 0;
			dPitch2[i] = 0;
		}
	}

	CString strtmp,strtmp1="",strtmp2;
	int nmismatchbad = 0,nmismatchcnt = 0;
	for(int i=0;i<MAX_LENGTH-2 && nc1>0 && nLinecount>0 && nc1 ==nLinecount && ncheck==0 && m_nDataMissing==0;i++){
		if(pDoc->m_data.m_nMisMatchPixel[1][i]==0 || pDoc->m_data.m_nMisMatchPixel[0][i]==0)break;//back 값이 0 이면 미스매치를 하지 않는다.

		if(nDirect==1){//left-> right //back - top  탑코팅기준 크면 플러스 작으면 마이너스
			if(i%2==1){
//				pDoc->m_data.m_dMisMatchData[0][nframe][i] = (pDoc->m_data.m_dMisMatchLen[1][i]-dtmp1[i])*-1;
				pDoc->m_data.m_dMisMatchData[0][nframe][i] = (dtmp2[i]-dtmp1[i]);//*-1;//(pDoc->m_data.m_nMisMatchPixel[1][i]-ntmp1[i])*-1*dcamScale[0];
				pDoc->m_data.m_dMisMatchData[3][nframe][i] = (dPitch2[i]-dPitch1[i]);//*-1;//(pDoc->m_data.m_nMisMatchPixel[1][i]-ntmp1[i])*-1*dcamScale[0];
				
			}
			else{
//				pDoc->m_data.m_dMisMatchData[0][nframe][i] = pDoc->m_data.m_dMisMatchLen[1][i]-dtmp1[i];
				pDoc->m_data.m_dMisMatchData[0][nframe][i] = (dtmp2[i]-dtmp1[i])*-1;//(pDoc->m_data.m_nMisMatchPixel[1][i]-ntmp1[i])*dcamScale[0];
//				pDoc->m_data.m_dMisMatchData[1][nframe][i] = ntmp2[i]-ntmp1[i];//(pDoc->m_data.m_nMisMatchPixel[1][i]-ntmp1[i]);
				pDoc->m_data.m_dMisMatchData[3][nframe][i] = (dPitch2[i]-dPitch1[i])*-1;//(pDoc->m_data.m_nMisMatchPixel[1][i]-ntmp1[i])*-1*dcamScale[0];
			}
			pDoc->m_data.m_dMisTopBackData1[2][i] = pDoc->m_data.m_dMisMatchData[0][nframe][i];//미스매치 동기화 데이터 //mismatch data 넣기
			//여기에 top back mm data 넣기
			pDoc->m_data.m_dMisTopBackData1[3][i] = dtmp1[i];//top data
			pDoc->m_data.m_dMisTopBackData1[4][i] = dtmp2[i];//back data

			//10meter
			pDoc->m_data.m_dDrawMisData[2][nmeter1][0][i] = pDoc->m_data.m_dMisMatchData[0][nframe][i];
			pDoc->m_data.m_dDrawMisData[2][nmeter2][0][i] = pDoc->m_data.m_dMisMatchData[0][nframe][i];

			
			pDoc->m_data.m_dMisMatchData[1][nframe][i] = dtmp1[i];//(ntmp2[i]-ntmp1[i])*-1;//(pDoc->m_data.m_nMisMatchPixel[1][i]-ntmp1[i])*-1;
			pDoc->m_data.m_dMisMatchData[2][nframe][i] = dtmp2[i];//(ntmp2[i]-ntmp1[i])*-1;//(pDoc->m_data.m_nMisMatchPixel[1][i]-ntmp1[i])*-1;

			if(fabs(pDoc->m_data.m_dMisMatchData[0][nframe][i])>100 && m_strComputerName.Find("CHO")==0)
				return -1;
//				pDoc->m_data.m_dMisMatchData[0][nframe][i]=pDoc->m_data.m_dMisMatchData[0][nframe][i];
			strtmp.Format("%.2f",pDoc->m_data.m_dMisMatchData[0][nframe][i]);
			m_strPitchMismatch[i].Format("%.2f",pDoc->m_data.m_dMisMatchData[3][nframe][i]);
//			m_lbGapMisMatch[i].SetText(m_strPitchMismatch[i]);//기존 피치간 미스매치에서 피치간 폭차이로 수정
//			m_lbGapMisMatch[i].SetText(strPitchGap[i]);//기존 피치간 미스매치에서 피치간 폭차이로 수정
//			m_lbGapMisMatch[i].ShowWindow(1);
			nmismatchcnt++;
			//Mismatch 판단
			if(m_bUseMismatch[i] && pDoc->m_data.m_dMisMatchData[0][nframe][i] > m_dMismatchTolMax || pDoc->m_data.m_dMisMatchData[0][nframe][i] < -m_dMismatchTolMin){
				if( pDoc->m_data.m_dMisMatchData[0][nframe][i] > m_dMismatchTolMax1 || pDoc->m_data.m_dMisMatchData[0][nframe][i] < -m_dMismatchTolMin1)
				{
					m_nNewAlarm++;
					m_bNewAlarm = TRUE;
				}

				if(m_bUseMismatch[i])
					nmismatchbad++;
//				if(m_bUseMismatch[i] == FALSE)//m_bUseMismatch//m_bUseMismatch
				if(m_bUseMismatch[i]==TRUE)
					m_lbCoatTitle[2+i].SetTextColor(COLOR_RED);
				else
					m_lbCoatTitle[2+i].SetTextColor(COLOR_GRAY_WHITE1);
			}
			else if(m_bUseMismatch[i]==FALSE)
				m_lbCoatTitle[2+i].SetTextColor(COLOR_GRAY_WHITE1);
			else
				m_lbCoatTitle[2+i].SetTextColor(COLOR_BLUE);
			
			int nSize1 = 20,nSize = 20;
			if(fabs(pDoc->m_data.m_dMisMatchData[0][nframe][i])>=100)
				m_lbCoatTitle[2+i].SetFontSize(nSize1);
			else m_lbCoatTitle[2+i].SetFontSize(nSize);
			
			m_lbCoatTitle[2+i].SetText(strtmp);
			if(i==0)
				m_lbCoatTitle[2+i].ShowWindow(0);
			else{
				if(i!=nLinecount-1)
				m_lbCoatTitle[2+i].ShowWindow(1);
			}

			if(dtmp1[i]>0 && dtmp2[i]>0 ){////20190414
				m_dLaneAve[0][i] += dtmp1[i];//top
				m_dLaneAve[1][i] += dtmp2[i];//back
				m_dMismatchAve[i] += pDoc->m_data.m_dMisMatchData[0][nframe][i];
				m_nLAneDataCount[i]++;
				if(i==0){
					m_nLaneCount += nLinecount;
					m_nLaneCount1++;
				}
			}
		}//m_lbCoatTitle
		else if(nDirect==2){//right->left
			pDoc->m_data.m_dMisMatchData[0][nframe][i];
		}
	}
	//top은 역순이여야 한다.
	if(m_strComputerName.Mid(8,1)=="M"){
		for(int i=0;i<nmismatchcnt;i++){
			strtmp.Format("%.2f,",pDoc->m_data.m_dMisMatchData[0][nframe][i]);
			strtmp1 += strtmp;
		}

	}
	else{
		for(int i=nmismatchcnt-1;i>0;i--){
			strtmp.Format("%.2f,",pDoc->m_data.m_dMisMatchData[0][nframe][i]);
			strtmp1 += strtmp;
		}

	}
	//mismatch data write //10meter 단위
	if(nmismatchcnt>1)
		m_strTopMismatch = strtmp1;
	else
		m_strTopMismatch = "";
	if(nmismatchbad>0 && pDoc->m_pDlgInterface->m_bMisAlarm)	
		m_nMismatchBadCount++;
	else 
		m_nMismatchBadCount=0;

 	if(pDoc->m_pDlgInterface->m_bAlarm && pDoc->m_pDlgInterface->m_bMisAlarm && pDoc->m_data.m_dBadAlarmMismatch <m_nMismatchBadCount){//여기
// 		//Alarm
 		if(pDoc->m_pDlgInterface->m_bAlarm ){
 			//Alarm//알람
 			//m_IO[0].WriteOutputPort(0,0,TRUE);
			m_bAlarmOnOff = TRUE;
			int ntmpmeter = pDoc->m_nTotalIns[0]+pDoc->m_pDlgInterface->m_dBadAlarmMismatch;
			if(m_nAlarmEndFRame< ntmpmeter)
				m_nAlarmEndFRame = ntmpmeter; 

			m_nAlarmLog += 2;
			m_strAlarmMsg = "Mismatch";//"미스매치";
			m_strAlarmMsg1.Format("%d M", pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck]) ;

//			m_nNewAlarm++;
			m_bNewAlarm = TRUE;

			CString str1;
			str1.Format("Alarm On Mismatch %d , %d",m_nNewAlarm,m_bNewAlarm);
 			AddtoList(str1,0,TRUE);
 		}
  	}
	if(pDoc->m_pDlgInterface->m_bMisAlarm==FALSE){
//		m_nAlarmEndFRame = 0;
//		m_bAlarmOnOff = FALSE;
	}
 
 	return 0;
}

//190312 추가
void CVisWebView::WriteMisMatchData1(int nframe,int nCount)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CString strLot;
	strLot = ConvertCharToStr(cLotID);
	if(strLot=="")strLot = "NONE";

	CString data[6];
	CTime timer=CTime::GetCurrentTime();  
	data[0].Format("%d", timer.GetYear());
	if(timer.GetMonth() < 10)             data[1].Format("0%d", timer.GetMonth());
	else           data[1].Format("%d", timer.GetMonth());
	if(timer.GetDay() < 10)               data[2].Format("0%d", timer.GetDay());
	else           data[2].Format("%d", timer.GetDay());
	if(timer.GetHour() < 10)              data[3].Format("0%d", timer.GetHour());
	else           data[3].Format("%d", timer.GetHour());
	if(timer.GetMinute() < 10)            data[4].Format("0%d", timer.GetMinute());
	else           data[4].Format("%d", timer.GetMinute());
	if(timer.GetSecond() < 10)            data[5].Format("0%d", timer.GetSecond());
	else           data[5].Format("%d", timer.GetSecond());
	CStdioFile   file;
	CString filename;
	CString strpath,strtitle;
	CString str,strtmp1="",strtmp2="",strtmp3="",strtmp4="",strtmp5="",strtmp6="",strtmp7="",strtmp8="",strtmp9="",strtmp10="",strtmp,strtime,strtmp11[4]={"",};
	int nLen = nCount;
	int nLen1 = nLen %100;
// 	if(pDoc->m_data.m_bUseCLog){
// 		strpath.Format("C:\\Glim\\LotData\\");
// 		CreateDirectory(strpath,NULL); 
// 		strpath.Format("C:\\Glim\\LotData\\%s%s%s\\",data[0],data[1],data[2]);
// 		CreateDirectory(strpath,NULL); 
// 		strpath.Format("C:\\Glim\\LotData\\%s%s%s\\%s\\",data[0],data[1],data[2],strLot);
// 		CreateDirectory(strpath,NULL); 
// 		filename.Format("%s%s_Mismatch.csv",strpath,pDoc->m_data.m_strComName);
// 	}
// 	else{
		strpath.Format("D:\\Data\\LotData\\");
		CreateDirectory(strpath,NULL); 
		strpath.Format("D:\\Data\\LotData\\%s%s%s\\",data[0],data[1],data[2]);
		CreateDirectory(strpath,NULL); 
		strpath.Format("D:\\Data\\LotData\\%s%s%s\\%s\\",data[0],data[1],data[2],strLot);
		CreateDirectory(strpath,NULL); 
		filename.Format("%s%s_Mismatch.csv",strpath,pDoc->m_data.m_strComName);
//	}
	// 설비길이, Frame , len1,len2,len3....
	//pDoc->m_data.m_nMisMatchPixel[0][i]  //pDoc->m_data.m_nMisMatchPixel[0][i]
	int nc1 = 0;
	CString strEPC=_T("(EPC)");
	CString strtitle1[10]={"",},strnumeric="";
	for(int i=0;i<nCount;i++){
		strtmp1.Format(",%.2f",pDoc->m_data.m_dMisMatchData[0][nframe][i]);
		strtmp2 += strtmp1;
		strtmp1.Format(",%.2f",pDoc->m_data.m_dMisMatchData[1][nframe][i]);
		strtmp3 += strtmp1;
		strtmp1.Format(",%.2f",pDoc->m_data.m_dMisMatchData[2][nframe][i]);
		strtmp4 += strtmp1;
		//0312
		strtmp5.Format(",%.2f",pDoc->m_data.m_nMisMatchPixel[0][i]);
		strtmp6 += strtmp5;
		strtmp7.Format(",%.2f",pDoc->m_data.m_nMisMatchPixel[1][i]);
		strtmp8 += strtmp7;
		strtmp9.Format(",%.2f",pDoc->m_data.m_dMisMatchData[3][nframe][i]);
		strtmp10 += strtmp9;
		//폭데이터
		if(m_strComputerName.Find(_T("OCH"))>=0){
			strnumeric.Format("%d",i+1);
			strtitle1[0] += "Mismatch"+strnumeric+",";
			strtitle1[3] += "탑누적폭"+strnumeric+",";
			strtitle1[4] += "백누적폭"+strnumeric+",";
			strtitle1[5] += "탑픽셀"+strnumeric+",";
			strtitle1[6] += "백픽셀"+strnumeric+",";

			strtitle1[7] += "폭Mismatch"+strnumeric+",";
			if(i==0) continue;
			strtmp1.Format(",%.2f",pDoc->m_data.m_dMisMatchData[1][nframe][i]-pDoc->m_data.m_dMisMatchData[1][nframe][i-1]);
			strtmp11[0] += strtmp1;//top pitch
			strtmp1.Format(",%.2f",pDoc->m_data.m_dMisMatchData[2][nframe][i]-pDoc->m_data.m_dMisMatchData[2][nframe][i-1]);
			strtmp11[1] += strtmp1;//back pitch

			strnumeric.Format("%d",i);
			strtitle1[1] += "탑폭"+strnumeric+",";
			strtitle1[2] += "백폭"+strnumeric+",";
		}
		else{
			strnumeric.Format("%d",i+1);
			strtitle1[0] += "Mismatch"+strnumeric+",";
			strtitle1[3] += "Top Accumulated Width"+strnumeric+",";
			strtitle1[4] += "Back Accumulated Width"+strnumeric+",";
			strtitle1[5] += "Top Pixel"+strnumeric+",";
			strtitle1[6] += "Back Pixel"+strnumeric+",";

			strtitle1[7] += "Width Mismatch"+strnumeric+",";
			if(i==0) continue;
			strtmp1.Format(",%.2f",pDoc->m_data.m_dMisMatchData[1][nframe][i]-pDoc->m_data.m_dMisMatchData[1][nframe][i-1]);
			strtmp11[0] += strtmp1;//top pitch
			strtmp1.Format(",%.2f",pDoc->m_data.m_dMisMatchData[2][nframe][i]-pDoc->m_data.m_dMisMatchData[2][nframe][i-1]);
			strtmp11[1] += strtmp1;//back pitch

			strnumeric.Format("%d",i);
			strtitle1[1] += "Top Width"+strnumeric+",";
			strtitle1[2] += "Back Width"+strnumeric+",";
		}



		if(m_strComputerName.Mid(8,1)=="H"){
			if(i==0){					// 20201014 kjh
				strtitle1[3] += strEPC;
				strtitle1[5] += strEPC;
				strtitle1[1] += strEPC;
			}
			if(i==nCount-1){
				strtitle1[4] += strEPC;
				strtitle1[6] += strEPC;
				strtitle1[2] += strEPC;
			}
		}
		else{
			if(i==0){					// 20201014 kjh
				strtitle1[3] += strEPC;
				strtitle1[5] += strEPC;
				strtitle1[1] += strEPC;
				strtitle1[4] += strEPC;
				strtitle1[6] += strEPC;
				strtitle1[2] += strEPC;
			}			
		}



	}
	strtime.Format("%s%s%s%s%s%s",data[0],data[1],data[2],data[3],data[4],data[5]);
	//////////////time lot 설비길이 카운트 
	//0312

	strtitle.Format("Time,LOTNO,Meter,Line,%s%s%s%s%s%s%s%s",strtitle1[0],strtitle1[1],strtitle1[2],strtitle1[3],strtitle1[4],strtitle1[5],strtitle1[6],strtitle1[7]);
	strtmp.Format("%s,%s,%d,%d	%s	%s  %s  %s	%s	%s	%s	%s, ",strtime,strLot,pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck],nCount,strtmp2,strtmp11[0],strtmp11[1],strtmp3,strtmp4,strtmp6,strtmp8,strtmp10);

	try{
		g_Mutex.Lock();                    // 뮤텍스를잠근다.
		if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
		{              		
			m_nTextWriteCount = 0;
			if(file.Open(filename, CFile::modeCreate|CFile::modeWrite|CFile::typeText)){
				file.WriteString(strtitle);
				file.WriteString("\n");       
				file.WriteString(strtmp);
				file.WriteString("\n");       
				file.Close();
			}
		}
		else
		{
			file.SeekToEnd();                     
			file.WriteString(strtmp);
			file.WriteString("\n");
			file.Close(); 
		}       
		g_Mutex.Unlock();                 // 뮤텍스를풀어준다.
	}
	catch(CFileException)
	{
		//AfxMessageBox( "File Open failed" );
	}
	catch(...)
	{
		//AfxMessageBox( "File Open failed2~" );
	}
}

//void CVisWebView::WriteMisMatchData1(int nframe,int nCount)
//{
//	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
//	CString strlot;
//	strlot = ConvertCharToStr(cLotID);
//	CString data[6];
//	CTime timer=CTime::GetCurrentTime();	
//	data[0].Format("%d", timer.GetYear());
//	if(timer.GetMonth() < 10)		data[1].Format("0%d", timer.GetMonth());
//	else		data[1].Format("%d", timer.GetMonth());
//	if(timer.GetDay() < 10)		data[2].Format("0%d", timer.GetDay());
//	else		data[2].Format("%d", timer.GetDay());
//	if(timer.GetHour() < 10)		data[3].Format("0%d", timer.GetHour());
//	else		data[3].Format("%d", timer.GetHour());
//	if(timer.GetMinute() < 10)		data[4].Format("0%d", timer.GetMinute());
//	else		data[4].Format("%d", timer.GetMinute());
//	if(timer.GetSecond() < 10)		data[5].Format("0%d", timer.GetSecond());
//	else		data[5].Format("%d", timer.GetSecond());
//	CStdioFile   file;
//	CString filename;
//	CString strpath;
//	CString str,strtmp1="",strtmp2="",strtmp3="",strtmp4="",strtmp,strtime;
//	int nLen = nCount;
//	int nLen1 = nLen %100;
//	strpath.Format("C:\\Glim\\LotData\\");
//	CreateDirectory(strpath,NULL);	
//	strpath.Format("C:\\Glim\\LotData\\%s%s%s\\",data[0],data[1],data[2]);
//	CreateDirectory(strpath,NULL);	
//	strpath.Format("C:\\Glim\\LotData\\%s%s%s\\%s\\",data[0],data[1],data[2],strlot);
//	CreateDirectory(strpath,NULL);	
//	filename.Format("%s%s_Mismatch.txt",strpath,pDoc->m_data.m_strComName);
//	// 설비길이 , Frame , len1,len2,len3....
//
//	int nc1 = 0;
//	for(int i=0;i<nCount;i++){
//		strtmp1.Format(",%.2f",pDoc->m_data.m_dMisMatchData[0][nframe][i]);
//		strtmp2 += strtmp1;
//		strtmp1.Format(",%.2f",pDoc->m_data.m_dMisMatchData[1][nframe][i]);
//		strtmp3 += strtmp1;
//		strtmp1.Format(",%.2f",pDoc->m_data.m_dMisMatchData[2][nframe][i]);
//		strtmp4 += strtmp1;
//		pDoc->m_data.m_dMisMatchData[0][nframe][i] = pDoc->m_data.m_dMisMatchData[1][nframe][i]=0;
//	}
//	strtime.Format("%s%s%s%s%s%s",data[0],data[1],data[2],data[3],data[4],data[5]);
//	//////////////time lot 설비길이  카운트  
//	strtmp.Format("%s\t%s\t%d\t%d\t%s\t%s\t%s",strtime,strlot,pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck],nCount,strtmp2,strtmp3,strtmp4);
//
//	try{
//		g_Mutex.Lock();                    // 뮤텍스를 잠근다.
//		if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
//		{		
//			m_nTextWriteCount = 0;
//			file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText);
//			file.WriteString(strtmp);
//			file.WriteString("\n");	
//			file.Close();
//		}
//		else
//		{
//			file.SeekToEnd();			
//			file.WriteString(strtmp);
//			file.WriteString("\n");
//			file.Close(); 
//		}	
//		g_Mutex.Unlock();                 // 뮤텍스를 풀어준다.
//	}
//	catch(CFileException)
//	{
//		//AfxMessageBox( "File Open failed" );
//	}
//	catch(...)
//	{
//		//AfxMessageBox( "File Open failed2~" );
//	}
//}

int CVisWebView::GetPlcData()
{
	// plc 데이터 동기화
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	m_bLotWriteCheck = TRUE;
	int nRetVal = strcmp(cLotCurrent, cLotOld);
	if(nRetVal != 0){
		strcpy_s(cLotID, 100, cLotCurrent);
	}
	m_bLotWriteCheck = FALSE;
	strcpy_s(cLotOld, 100, cLotCurrent);
	pDoc->m_data.m_nMachineLengthAB[0] = m_nPlcData[0]*0.1;
	pDoc->m_data.m_nMachineLengthAB[1] = m_nPlcData[1]*0.1;
	m_dRealMeter[0] = m_nPlcData[0];
	m_dRealMeter[1] = m_nPlcData[1];
	return 0;
}


CString CVisWebView::GetDefectType(int nDefect)
{
	CString str;
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	if(pDoc->m_pDlgInterface->m_bEngKor){
		if(nDefect == 101)str.Format("Line");
		else if(nDefect == 201)str.Format("Line");//c
		else if(nDefect == 1001)str.Format("Island");//n
		else if(nDefect == 1002)str.Format("Drag");//n
		else if(nDefect == 2001)str.Format("Pinhole");//c
		else if(nDefect == 3001)str.Format("Line");
		else if(nDefect == 4001)str.Format("Line");
		else if(nDefect == 7001)str.Format("Chipping Pinhole");
		else					str.Format("Pinhole");
	}
	else{
		if(nDefect == 101)str.Format("라인");
		else if(nDefect == 201)str.Format("라인");
		else if(nDefect == 1001)str.Format("아일랜드");
		else if(nDefect == 1002)str.Format("드래그");
		else if(nDefect == 2001)str.Format("핀홀");
		else if(nDefect == 3001)str.Format("라인");
		else if(nDefect == 4001)str.Format("라인");
		else if(nDefect == 7001)str.Format("파인 핀홀");
		else					str.Format("핀홀");
	}

	return str;
}
void CVisWebView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CRect rt,rt1,rt2;
	int nChagne = 0;
	CRect rcMain;
	GetWindowRect(rcMain);
	for(int i=0;i< m_nLineCount*2;i++){
		m_lPitchTol[i].GetWindowRect(rt);
		rt.OffsetRect(-rcMain.left,-rcMain.top);	
	//	rt.InflateRect(30,30);
		if(rt.PtInRect(point)){
			point = point;
			m_nSelectNum = i;
			m_NumPad->m_bTol1 = TRUE;
			m_NumPad->m_bStandard = FALSE;
			m_NumPad->UpdateData(FALSE);
			m_NumPad->m_nSelectControl = 0;
			pDoc->m_pDlgInterface->m_nSelectEdit = -1;
			int nn = m_nSelectNum;
			if(nn>0 && nn%2==1)nn -=1;
			m_NumPad->LabelShow(m_nSelectNum,m_dTolerance[nn],m_dTolerance[nn+1]);
			m_NumPad->ShowWindow(1);
		}
		if(i>=m_nLineCount)continue;
		m_lbCoatLen[i].GetWindowRect(rt1);
		rt1.OffsetRect(-rcMain.left,-rcMain.top);	
		if(rt1.PtInRect(point)){
//			m_nSelectNum = i;
			m_bUseLen[i] = !m_bUseLen[i];
//			m_NumPad->ShowWindow(1);
			nChagne = 1;
		}
		rt2 = pDoc->m_data.m_rtCoatChar[i];
		rt2.OffsetRect(-rcMain.left,-rcMain.top);	
		if(rt2.PtInRect(point) && nChagne==0){
			//			m_nSelectNum = i;
			m_bUseLen[i] = !m_bUseLen[i];
			//			m_NumPad->ShowWindow(1);
			nChagne = 1;
		}
		rt2 = pDoc->m_data.m_rtInsulateChar[i];
		rt2.OffsetRect(-rcMain.left,-rcMain.top);	
		if(rt2.PtInRect(point)&& nChagne==0){
			//			m_nSelectNum = i;
			m_bUseInSulate[i] = !m_bUseInSulate[i];
			//			m_NumPad->ShowWindow(1);
			nChagne = 1;
		}

	}
	
	
	if(m_strComputerName.Find("BACK")>=0 ||  pDoc->m_data.m_strComName.Mid(9,1)=="B"){
		for(int i=0;i< m_nLineCount;i++){
			m_lbCoatTitle[i+2].GetWindowRect(rt1);
			rt1.OffsetRect(-rcMain.left,-rcMain.top);	
			if(rt1.PtInRect(point)&& nChagne==0){
				m_bUseMismatch[i] = !m_bUseMismatch[i];
				nChagne = 1;
			}
		}
		m_lbMismatchTolMin.GetWindowRect(rt);
		rt.OffsetRect(-rcMain.left,-rcMain.top);	
		rt.InflateRect(10,10);
		if(rt.PtInRect(point)&& nChagne==0){
			point = point;
			m_NumPad->m_bTol1 = TRUE;
			m_NumPad->m_bStandard = FALSE;
			m_NumPad->UpdateData(FALSE);
			pDoc->m_pDlgInterface->m_nSelectEdit = 31;
			m_NumPad->LabelShow1(0,m_dMismatchTolMin,m_dMismatchTolMax);
			m_NumPad->ShowWindow(1);
		}
		m_lbMismatchTolMax.GetWindowRect(rt);
		rt.OffsetRect(-rcMain.left,-rcMain.top);	
		rt.InflateRect(10,10);
		if(rt.PtInRect(point)&& nChagne==0){
			point = point;
			m_NumPad->m_bTol1 = TRUE;
			m_NumPad->m_bStandard = FALSE;
			m_NumPad->UpdateData(FALSE);
			pDoc->m_pDlgInterface->m_nSelectEdit = 32;
			m_NumPad->LabelShow1(1,m_dMismatchTolMin,m_dMismatchTolMax);
			m_NumPad->ShowWindow(1);
		}
	}

	if(nChagne==1 && !m_bAuto)DrawImage(3);

	CFormView::OnLButtonDown(nFlags, point);
}

void CVisWebView::ChangeTol(BOOL bcheck, int nselect, CString str)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
//	if(bcheck){//공차
		m_dTolerance[nselect] = atof(str);
		CString str1;
		if(nselect%2==0)
			if(pDoc->m_pDlgInterface->m_bEngKor)
				str1.Format("MIN\n%s",str);
			else
				str1.Format("최소\n%s",str);
		else
			if(pDoc->m_pDlgInterface->m_bEngKor)
				str1.Format("MAX\n%s",str);
			else
				str1.Format("최대\n%s",str);
		m_lPitchTol[nselect].SetText(str1);
// 	}
// 	else{
// 		int nn = nselect*0.5;
// 		m_dStardLen[nn] = atof(str);
// 		pDoc->m_pDlgInterface->m_dStandard[nn] = m_dStardLen[nn];
// 		pDoc->m_pDlgInterface->UpdateData(FALSE);
// 		pDoc->m_pDlgInterface->SaveSysParam();
// 	}

	UpdateTolIni(pDoc->m_data.m_strDefaultModel,0);
	int nn1 = nselect;
	if(nn1%2==1)nn1 -= nn1;
		m_NumPad->LabelShow(nselect,m_dTolerance[nn1],m_dTolerance[nn1+1]);

}

void CVisWebView::ChangeTol1(BOOL bcheck, int nselect, CString str)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	//	if(bcheck){//공차
	int nn = 0;
	if(nselect>=10 && nselect<30){	//max 치 에디트 컨트롤 선택 시 (10~29)
		nn = (nselect-11)*2+1;
	}
	else if(nselect>30){

	}
	else{							//min 치 에디트 컨트롤 선택 시 (0~9) 
		nn = (nselect -1)*2;
	}
	if(nselect<30){
		m_dTolerance[nn] = atof(str);
		CString str1;
		if(nn%2==0)
			if(pDoc->m_pDlgInterface->m_bEngKor)
				str1.Format("MIN\n%s",str);
			else	
				str1.Format("최소\n%s",str);
		else
			if(pDoc->m_pDlgInterface->m_bEngKor)
				str1.Format("MAX\n%s",str);
			else
				str1.Format("최대\n%s",str);
		m_lPitchTol[nn].SetText(str1);
		// 	}
		// 	else{
		// 		int nn = nselect*0.5;
		// 		m_dStardLen[nn] = atof(str);
		// 		pDoc->m_pDlgInterface->m_dStandard[nn] = m_dStardLen[nn];
		// 		pDoc->m_pDlgInterface->UpdateData(FALSE);
		// 		pDoc->m_pDlgInterface->SaveSysParam();
		// 	}

		UpdateTolIni(pDoc->m_data.m_strDefaultModel,0);
		int nn1 = nselect;
		if(nn1%2==1)nn1 -= nn1;
		m_NumPad->LabelShow(nselect,m_dTolerance[nn1],m_dTolerance[nn1+1]);
	}
	else{
//		m_dTolerance[nn] = atof(str);
		CString str1;
		if(nselect==31){
			m_SysParam->m_dMismatchTolMin = m_dMismatchTolMin = atof(str);
			str1.Format("최소%s",str);	
			m_lbMismatchTolMin.SetText(str1);
		}
		else if(nselect==32){
			m_SysParam->m_dMismatchTolMax = m_dMismatchTolMax = atof(str);
			if(pDoc->m_pDlgInterface->m_bEngKor)
				str1.Format("MAX%s",str);		
			else
				str1.Format("최대%s",str);
			m_lbMismatchTolMax.SetText(str1);
		}
		else if(nselect==33){
			m_SysParam->m_dMismatchTolMin1 = m_dMismatchTolMin1 = atof(str);
			if(pDoc->m_pDlgInterface->m_bEngKor)
				str1.Format("MIN%s",str);	
			else
				str1.Format("최소%s",str);	
			// 			m_lbMismatchTolMin1.SetText(str1);
		}
		else if(nselect==34){
			m_SysParam->m_dMismatchTolMax1 = m_dMismatchTolMax1 = atof(str);
			if(pDoc->m_pDlgInterface->m_bEngKor)
				str1.Format("MIN%s",str);	
			else
				str1.Format("최소%s",str);	
			// 			m_lbMismatchTolMin1.SetText(str1);
		}
		else if(nselect==35){
			m_SysParam->m_dMismatchTolMin1 = m_dMismatchTolMin1 = atof(str);
			if(pDoc->m_pDlgInterface->m_bEngKor)
				str1.Format("MIN%s",str);	
			else
				str1.Format("최소%s",str);	
			// 			m_lbMismatchTolMin1.SetText(str1);
		}
 		else{
 			pDoc->m_pDlgInterface->m_nInsulateTh = atoi(str);
 			if(pDoc->m_pDlgInterface->m_bEngKor)
				str1.Format("MAX%s",str);
			else
				str1.Format("최대%s",str);
// 			m_lbMismatchTolMax1.SetText(str1);
 		}

		UpdateTolIni(pDoc->m_data.m_strDefaultModel,0);

		m_NumPad->LabelShow1((nselect+1)%2,m_dMismatchTolMin,m_dMismatchTolMax);
	}


}
void CVisWebView::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
 	if (nIDCtl == IDC_NETWORK_TEST)//로드
 	{//버튼 오너드로우 속성 true로 변경할것.
 		CDC dc;
 		RECT rect;
 		dc.Attach(lpDrawItemStruct -> hDC);                //버튼의 dc구하기
 		rect = lpDrawItemStruct->rcItem;                   //버튼영역 구하기
 		dc.Draw3dRect(&rect,RGB(255,255,255),RGB(0,0,0));  //버튼의 외각선 그리기
 		dc.FillSolidRect(&rect,COLOR_GREEN);             //버튼색상
 		UINT state = lpDrawItemStruct-> itemState;         //버튼상태구하기
 		if((state &ODS_SELECTED))
 		{
 			dc.DrawEdge(&rect,EDGE_SUNKEN,BF_RECT);
 		}
 		else
 		{
 			dc.DrawEdge(&rect,EDGE_RAISED,BF_RECT);
 		}
 		//		dc.SetBkColor(RGB(51,51,51));                       //text의 백그라운드 색상
 		dc.SetTextColor(COLOR_RED);                     //texttort
 		TCHAR buffer[MAX_PATH];                            //버튼의 text를 얻기위한 임시버퍼
 		ZeroMemory(buffer,MAX_PATH);                       //버퍼초기화
 		::GetWindowTextA(lpDrawItemStruct->hwndItem,buffer,MAX_PATH); //버튼의 text얻기
 		dc.DrawText(buffer,&rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE); //버튼의 text넣기
 		dc.Detach();                                                  //버튼의 dc 풀어주기
 	}

	CFormView::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CVisWebView::UpdateTolIni(CString strModel,BOOL bLoad)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	int n1=1;
	if(bLoad==FALSE){	//save
		UpdateData(TRUE);
		int n1 = m_SysParam->m_cbLane.GetCurSel();
		m_nLimitLane = n1+1;
	}
	
	CString strPath("c:\\Glim\\Model\\");
	CString strModelPath,str;

	strModelPath.Format("%s%s.ini","c:\\Glim\\Model\\",strModel);
// 	str.Format(_T(" %s | Model: %s."),PRODUCT_NAME,strModel);
// 	pDlg->m_ctTTitle.SetCaption(str);
// 	pDlg->m_OperatorDisplay->m_ctTitle.SetCaption(str);

//	CIni ini1(strModelPath, "Tolerance" , 1 );
	CIni ini( strModelPath, "Tolerance", 25 );
//	ini.SER_GETD(TRUE, param1	, 25);	//gl3- white th  //gl4- dyeSpot th

	ini.SER_GETD(bLoad,m_dTolerance[0], 0.3);//min
	ini.SER_GETD(bLoad,m_dTolerance[1], 0.3);//max
	ini.SER_GETD(bLoad,m_dTolerance[2], 0.3);//min
	ini.SER_GETD(bLoad,m_dTolerance[3], 0.3);//max
	ini.SER_GETD(bLoad,m_dTolerance[4], 0.3);//min
	ini.SER_GETD(bLoad,m_dTolerance[5], 0.3);//max
	ini.SER_GETD(bLoad,m_dTolerance[6], 0.3);
	ini.SER_GETD(bLoad,m_dTolerance[7], 0.3);
	ini.SER_GETD(bLoad,m_dTolerance[8], 0.3);
	ini.SER_GETD(bLoad,m_dTolerance[9], 0.3);
	ini.SER_GETD(bLoad,m_dTolerance[10], 0.3);
	ini.SER_GETD(bLoad,m_dTolerance[11], 0.3);
	ini.SER_GETD(bLoad,m_dTolerance[12], 0.3);
	ini.SER_GETD(bLoad,m_dTolerance[13], 0.3);
	ini.SER_GETD(bLoad,m_dTolerance[14], 0.3);
	ini.SER_GETD(bLoad,m_dTolerance[15], 0.3);
	ini.SER_GETD(bLoad,m_dTolerance[16], 0.3);
	ini.SER_GETD(bLoad,m_dTolerance[17], 0.3);
	ini.SER_GETD(bLoad,m_dTolerance[18], 0.3);
	ini.SER_GETD(bLoad,m_dTolerance[19], 0.3);

	ini.SER_GETD(bLoad,m_dTolerance1[0], 0.3);//min
	ini.SER_GETD(bLoad,m_dTolerance1[1], 0.3);//max
	ini.SER_GETD(bLoad,m_dTolerance1[2], 0.3);//min
	ini.SER_GETD(bLoad,m_dTolerance1[3], 0.3);//max
	ini.SER_GETD(bLoad,m_dTolerance1[4], 0.3);//min
	ini.SER_GETD(bLoad,m_dTolerance1[5], 0.3);//max
	ini.SER_GETD(bLoad,m_dTolerance1[6], 0.3);
	ini.SER_GETD(bLoad,m_dTolerance1[7], 0.3);
	ini.SER_GETD(bLoad,m_dTolerance1[8], 0.3);
	ini.SER_GETD(bLoad,m_dTolerance1[9], 0.3);
	ini.SER_GETD(bLoad,m_dTolerance1[10], 0.3);
	ini.SER_GETD(bLoad,m_dTolerance1[11], 0.3);
	ini.SER_GETD(bLoad,m_dTolerance1[12], 0.3);
	ini.SER_GETD(bLoad,m_dTolerance1[13], 0.3);
	ini.SER_GETD(bLoad,m_dTolerance1[14], 0.3);
	ini.SER_GETD(bLoad,m_dTolerance1[15], 0.3);
	ini.SER_GETD(bLoad,m_dTolerance1[16], 0.3);
	ini.SER_GETD(bLoad,m_dTolerance1[17], 0.3);
	ini.SER_GETD(bLoad,m_dTolerance1[18], 0.3);
	ini.SER_GETD(bLoad,m_dTolerance1[19], 0.3);

	ini.SER_GETD(bLoad,m_dTolerance2[0], 0.1);//모디파이
	ini.SER_GETD(bLoad,m_dTolerance2[1], 0.1);
	ini.SER_GETD(bLoad,m_dTolerance2[2], 0.1);
	ini.SER_GETD(bLoad,m_dTolerance2[3], 0.1);
	ini.SER_GETD(bLoad,m_dTolerance2[4], 0.1);
	ini.SER_GETD(bLoad,m_dTolerance2[5], 0.1);
	ini.SER_GETD(bLoad,m_dTolerance2[6], 0.1);
	ini.SER_GETD(bLoad,m_dTolerance2[7], 0.1);
	ini.SER_GETD(bLoad,m_dTolerance2[8], 0.1);
	ini.SER_GETD(bLoad,m_dTolerance2[9], 0.1);

	ini.SER_GETD(bLoad,m_dStardLen[0], 3);
	ini.SER_GETD(bLoad,m_dStardLen[1], 3);
	ini.SER_GETD(bLoad,m_dStardLen[2], 3);
	ini.SER_GETD(bLoad,m_dStardLen[3], 3);
	ini.SER_GETD(bLoad,m_dStardLen[4], 3);
	ini.SER_GETD(bLoad,m_dStardLen[5], 3);
	ini.SER_GETD(bLoad,m_dStardLen[6], 3);
	ini.SER_GETD(bLoad,m_dStardLen[7], 3);
	ini.SER_GETD(bLoad,m_dStardLen[8], 3);
	ini.SER_GETD(bLoad,m_dStardLen[9], 3);
	ini.SER_GETD(bLoad,m_dStardLen[10], 3);

	ini.SER_GETD(bLoad,m_dStardLen1[0], 3);
	ini.SER_GETD(bLoad,m_dStardLen1[1], 3);
	ini.SER_GETD(bLoad,m_dStardLen1[2], 3);
	ini.SER_GETD(bLoad,m_dStardLen1[3], 3);
	ini.SER_GETD(bLoad,m_dStardLen1[4], 3);
	ini.SER_GETD(bLoad,m_dStardLen1[5], 3);
	ini.SER_GETD(bLoad,m_dStardLen1[6], 3);
	ini.SER_GETD(bLoad,m_dStardLen1[7], 3);
	ini.SER_GETD(bLoad,m_dStardLen1[8], 3);
	ini.SER_GETD(bLoad,m_dStardLen1[9], 3);
	ini.SER_GETD(bLoad,m_dStardLen1[10], 3);


	ini.SER_GETD(bLoad,m_dMismatchTolMax, 0.6);
	ini.SER_GETD(bLoad,m_dMismatchTolMin, 0.6);

	ini.SER_GETD(bLoad,m_dMismatchTolMax1, 1);
	ini.SER_GETD(bLoad,m_dMismatchTolMin1, 1);

	ini.SER_GETD(bLoad,m_dMismatchModify, 0.1);

	ini.SER_GETD(bLoad,m_nLimitLane, 1);

	ini.SER_GETD(bLoad,m_dFoilSize[0], 300);
	ini.SER_GETD(bLoad,m_dFoilSize[1], 650);

	
	for(int i=0;i<20;i++){
		pDoc->m_pDlgInterface->m_dStandard[i] = m_dStardLen[i];
		m_SysParam->m_dStandard[i] = m_dStardLen[i]; 
		m_SysParam->m_dStandard1[i] = m_dStardLen[i]; 
	}
	pDoc->m_pDlgInterface->m_dMismatchTolMin = m_dMismatchTolMin;
	pDoc->m_pDlgInterface->m_dMismatchTolMax = m_dMismatchTolMax;
	pDoc->m_pDlgInterface->m_dMismatchTolMin1 = m_dMismatchTolMin1;
	pDoc->m_pDlgInterface->m_dMismatchTolMax1 = m_dMismatchTolMax1;
	pDoc->m_pDlgInterface->m_dMismatchModify=m_dMismatchModify;
	m_SysParam->m_dMismatchTolMin = m_dMismatchTolMin;
	m_SysParam->m_dMismatchTolMax =	m_dMismatchTolMax;
	m_SysParam->m_dMismatchTolMin1 = m_dMismatchTolMin1;
	m_SysParam->m_dMismatchTolMax1 = m_dMismatchTolMax1;
	m_SysParam->m_dMismatchModify=m_dMismatchModify;

	CString strtmp;
	if(bLoad){//load
		UpdateData(FALSE);
		int ncount = 0;
		for(int i=0; i<9; i++){
			//모디파이
			pDoc->m_pDlgInterface->m_dMonitoringTol[i] = m_SysParam->m_dMonitoringTol[i] = m_dTolerance2[i]; 
		}
		for(int i=0;i<MAX_LENGTH;i++)
		{
			if(i%2==0){
				if(pDoc->m_pDlgInterface->m_bEngKor == ENG)
					strtmp.Format("Min\n%.2f",m_dTolerance[i]);
				else if(pDoc->m_pDlgInterface->m_bEngKor == KOR)
					strtmp.Format("최소\n%.2f",m_dTolerance[i]);
				pDoc->m_pDlgInterface->m_dStandard[ncount] = m_dTolerance[i];
				m_SysParam->m_dStandard[ncount] = m_dTolerance[i]; 
				m_SysParam->m_dStandard1[ncount] = m_dTolerance1[i]; 
			}
			else{
				if(pDoc->m_pDlgInterface->m_bEngKor == ENG)
					strtmp.Format("Max\n%.2f",m_dTolerance[i]);
				else if(pDoc->m_pDlgInterface->m_bEngKor == KOR)
					strtmp.Format("최대\n%.2f",m_dTolerance[i]);
				pDoc->m_pDlgInterface->m_dMaxValue[ncount] = m_dTolerance[i];
				m_SysParam->m_dMaxValue[ncount] = m_dTolerance[i]; 
				m_SysParam->m_dMaxValue1[ncount] = m_dTolerance1[i]; 
				ncount++;
			}

			m_lPitchTol[i].SetText(strtmp);

		}
		if(pDoc->m_pDlgInterface->m_bEngKor == ENG)
			strtmp.Format("Min-%.2f",m_dMismatchTolMin);
		else if(pDoc->m_pDlgInterface->m_bEngKor == KOR)
			strtmp.Format("최소-%.2f",m_dMismatchTolMin);
		m_lbMismatchTolMin.SetText(strtmp);
		if(pDoc->m_pDlgInterface->m_bEngKor == ENG)
			strtmp.Format("Max%.2f",m_dMismatchTolMax);
		else if(pDoc->m_pDlgInterface->m_bEngKor == KOR)
			strtmp.Format("최대%.2f",m_dMismatchTolMax);
		m_lbMismatchTolMax.SetText(strtmp);
		//T-B Gap
		strtmp.Format("B-T Gap");
		m_lbStaticTBGap.SetText(strtmp);

		m_SysParam->m_dFoilSize[0] = m_dFoilSize[0];
		m_SysParam->m_dFoilSize[1] = m_dFoilSize[1];

		n1 = m_nLimitLane-1;
		m_SysParam->m_cbLane.SetCurSel(n1);
		m_SysParam->DlgDirSelectComboBox(m_nLimitLane);
		m_SysParam->UpdateData(FALSE);

	}
	else{//save
		for(int i=0; i<9; i++){
			if(pDoc->m_pDlgInterface->m_bEngKor == ENG)
				strtmp.Format("Min\n%.2f",m_dTolerance[i]);
			else if(pDoc->m_pDlgInterface->m_bEngKor == KOR)
				strtmp.Format("최소\n%.2f",m_dTolerance[i]);
			pDoc->m_pDlgInterface->m_dMonitoringTol[i] = m_dTolerance2[i];
			m_SysParam->m_dMonitoringTol[i] = m_dTolerance2[i]; 
		}
		int ncount = 0;
		for(int i=0;i<MAX_LENGTH;i++)
		{
			if(i%2==0){
				if(pDoc->m_pDlgInterface->m_bEngKor == ENG)
					strtmp.Format("Min\n%.2f",m_dTolerance[i]);
				else if(pDoc->m_pDlgInterface->m_bEngKor == KOR)
					strtmp.Format("최소\n%.2f",m_dTolerance[i]);
				pDoc->m_pDlgInterface->m_dStandard[ncount] = m_dTolerance[i];
				m_SysParam->m_dStandard[ncount] = m_dTolerance[i]; 
				m_SysParam->m_dStandard1[ncount] = m_dTolerance1[i]; 
			}
			else{
				if(pDoc->m_pDlgInterface->m_bEngKor == ENG)
					strtmp.Format("Max\n%.2f",m_dTolerance[i]);
				else if(pDoc->m_pDlgInterface->m_bEngKor == KOR)
					strtmp.Format("최대\n%.2f",m_dTolerance[i]);
				pDoc->m_pDlgInterface->m_dMaxValue[ncount] = m_dTolerance[i];
				m_SysParam->m_dMaxValue[ncount] = m_dTolerance[i]; 
				m_SysParam->m_dMaxValue1[ncount] = m_dTolerance1[i]; 
				ncount++;
			}
//			double d1 =  m_dTolerance[(i-1)*2];//m_dStardLen[nLineCount1-1] +	 min 
//			double d2 =  m_dTolerance[(i-1)*2+1];//m_dStardLen[nLineCount1-1] -	max 

			m_lPitchTol[i].SetText(strtmp);

		}
		for(int i=0;i<9 && !m_SysParam->m_bInsideSet;i++)
		{
			m_SysParam->m_dStandard1[i] = m_SysParam->m_dStandard[i]+m_dTolerance2[i]; 
			m_SysParam->m_dMaxValue1[i] = m_SysParam->m_dMaxValue[i]- m_dTolerance2[i]; 

		}
		if(pDoc->m_pDlgInterface->m_bEngKor == ENG)
			strtmp.Format("Min-%.2f",m_dMismatchTolMin);
		else if(pDoc->m_pDlgInterface->m_bEngKor == KOR)
			strtmp.Format("최소-%.2f",m_dMismatchTolMin);
		m_lbMismatchTolMin.SetText(strtmp);
		if(pDoc->m_pDlgInterface->m_bEngKor == ENG)
			strtmp.Format("Max%.2f",m_dMismatchTolMax);
		else if(pDoc->m_pDlgInterface->m_bEngKor == KOR)
			strtmp.Format("최대%.2f",m_dMismatchTolMax);
		m_lbMismatchTolMax.SetText(strtmp);
	}
	pDoc->m_pDlgInterface->UpdateData(FALSE);
	m_SysParam->UpdateData(FALSE); 
}

void CVisWebView::OnBnClickedCheckAlarmOff()
{//m_bAlarmOff
	UpdateData();
	if(m_bAlarmOff==TRUE)
	{//알람
		//SetDlgItemText(IDC_CHECK_ALARM_OFF,"알람OFF");
		m_IO[0].WriteOutputPort(0,0,0);
		KillTimer(14223);
		m_AlarmDlg->ShowWindow(0);
		AddtoList("Alarm Off",0,TRUE);

	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

HBRUSH CVisWebView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(nCtlColor){
	case CTLCOLOR_DLG:   /// 다이얼로그 배경색을 white로.
		{
			return (HBRUSH)GetStockObject(WHITE_BRUSH);
			break;
		}
 	case CTLCOLOR_BTN :    // 버튼의 배경색을 투명으로...
 		{
 			pDC->SetBkMode(TRANSPARENT);
 			return (HBRUSH)::GetStockObject(NULL_BRUSH);
 		}
 	case CTLCOLOR_STATIC:
 		{
//  			pDC->SetTextColor(RGB(0,255,255));  // static text 글자색 변경
//  			pDC->SetBkMode(TRANSPARENT);   // static text 배경색 투명
//  			return (HBRUSH)::GetStockObject(NULL_BRUSH);
 		} 
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

// void CVisWebView::ResetCamera(void)
// {
// 	CCisSetting m_cis;
// 	bool bRtn; 
// 
// 	bRtn=m_cis.SendCmd(_T("TP01"));
// 
// }



void CVisWebView::WriteLotInfo(CString strLot, CString strStartTime, CString strEndTime, double dMeter, int nDefect1, int nDefect2, int nDefect3, int nDefect4, int nDefect5, int nDefect6, int nDefect7, int nDefect8, int nDefect9, int nDefect10)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CStdioFile   file;
	CString filename;
	CString strpath;
	CString str,strTitle,strtmp,strtmp1,strtmp2,strtmp3,strtmp4,strtmp5,strtmp6;
	CTime ttime = CTime::GetCurrentTime();
	CString kk = ttime.Format("%Y%m%d");//ttime.Format("%H_%M_%S");
	CString strTime = ttime.Format("[%Y %m %d %H:%M:%S]");
	CString data[6];
	CTime timer=CTime::GetCurrentTime();  
	data[0].Format("%d", timer.GetYear());
	if(timer.GetMonth() < 10)             data[1].Format("0%d", timer.GetMonth());
	else           data[1].Format("%d", timer.GetMonth());
	if(timer.GetDay() < 10)               data[2].Format("0%d", timer.GetDay());
	else           data[2].Format("%d", timer.GetDay());
	if(timer.GetHour() < 10)              data[3].Format("0%d", timer.GetHour());
	else           data[3].Format("%d", timer.GetHour());
	if(timer.GetMinute() < 10)            data[4].Format("0%d", timer.GetMinute());
	else           data[4].Format("%d", timer.GetMinute());
	if(timer.GetSecond() < 10)            data[5].Format("0%d", timer.GetSecond());
	else           data[5].Format("%d", timer.GetSecond());

	if(strLot=="")strLot = "NONE";


	strpath.Format("d:\\Data\\LotInfo\\");
	CreateDirectory(strpath,NULL);
	strpath.Format("d:\\Data\\LotInfo\\%s\\",data[0]);//yy
	CreateDirectory(strpath,NULL);
	strpath.Format("d:\\Data\\LotInfo\\%s\\%s\\",data[0],data[1]);//yymm
	CreateDirectory(strpath,NULL);
	strpath.Format("d:\\Data\\LotInfo\\%s\\%s\\%s\\",data[0],data[1],data[2]);//yymmdd
	CreateDirectory(strpath,NULL);
	filename.Format("%s%s_LotInfo.csv",strpath,kk);
//시작	//종료	//Lot	//생산미터	
	strtmp1=strtmp2=strtmp3=strtmp4=strtmp5=strtmp6="";

	for(int i=0;i<MAX_LENGTH;i++){
		if(m_nLAneDataCount[i]>0 &&m_dLaneAve[0][i]>0 && m_dLaneAve[1][i]>0){
			strtmp1.Format("%.2f,",m_dLaneAve[0][i]/m_nLAneDataCount[i]);
			strtmp2 += strtmp1;
			strtmp3.Format("%.2f,",m_dLaneAve[1][i]/m_nLAneDataCount[i]);
			strtmp4 += strtmp3;
			strtmp5.Format("%.2f,",m_dMismatchAve[i]/m_nLAneDataCount[i]);
			strtmp6 += strtmp5;
		}
		else if(i<10){
			strtmp1.Format(",");
			strtmp2 += strtmp1;
			strtmp3.Format(",");
			strtmp4 += strtmp3;
			strtmp5.Format(",");
			strtmp6 += strtmp5;

		}
	}
	int nLane = 0;
// 	if(m_nLaneCount1>0 && m_nLaneCount>0)
// 		nLane = m_nLineCount/m_nLaneCount1;
	nLane = (pDoc->m_data.m_nNewLineCount/2)-1;	// 200702 kjh
	//라인,핀홀,파인핀홀,분화구,크랙,표면불량,미스매치,아일랜드,드래그,주름
	strTitle.Format("StartTime,EndTime,LotNo,Meter,LIne,Pinhole,Chipping Pinhole,Crater,Crack,Surface Defect,MisMatch, Island, Drag, Wrinkle, Lane,TopLane1,TopLane2,TopLane3,TopLane4,TopLane5,TopLane6,TopLane7,TopLane8,TopLane9,TopLane10,BackLane1,BackLane2,BackLane3,BackLane4,BackLane5,BackLane6,BackLane7,BackLane8,BackLane9,BackLane10,Mismacht1,Mismacht2,Mismacht3,Mismacht4,Mismacht5,Mismacht6,Mismacht7,Mismacht8,Mismacht9,Mismacht10");
	strtmp.Format("%s,%s,%s,%.1f,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s%s%s",strStartTime,strEndTime,strLot,dMeter,nDefect1,nDefect2,nDefect3,nDefect4,nDefect5,nDefect6,nDefect7,nDefect8,nDefect9,nDefect10,nLane,strtmp2,strtmp4,strtmp6);
	
	for(int i=0;i<MAX_LENGTH;i++){
		m_dLaneAve[0][i]=0;//top
		m_dLaneAve[1][i] =0;//back
		m_dMismatchAve[i] =0;
		m_nLAneDataCount[i] = 0;
		m_nLaneCount = 0;
		m_nLaneCount1 = 0;
	}

	if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
	{		
		if(file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText))
		{
			file.WriteString(strTitle);
			file.WriteString("\n");
			file.WriteString(strtmp);
			file.Close();
		}
	}
	else
	{
		file.SeekToEnd();
		file.WriteString("\n");
		file.WriteString(strtmp);
		file.Close(); 
	}
}
//MODEL,color,gain,size,maxgray,mingray,avegray,검출값,
void CVisWebView::WriteDefectData(CString strLot, double dMeterY, double dMeterX, double dsx,double dsy, double dvalue,CString strType,CString strimg,CString imgname,CString newpath,
								  CString strmodel,CString strcolor, double dgain,double dsize1,double dmaxgray,double dmingray, double davegray,double dthvalue,CString strLocaltime)
{
	CStdioFile   file;
	CString filename;
	CString strpath;
	CString str,strTitle,strtmp;
	CTime ttime = CTime::GetCurrentTime();
	CString kk = ttime.Format("%Y%m%d");//ttime.Format("%H_%M_%S");
	CString kk1;// = ttime.Format("%Y");//ttime.Format("%H_%M_%S");
	kk1.Format("%d", ttime.GetYear());

	CString strTime = ttime.Format("%Y%m%d-%H:%M:%S");
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

// 	if(pDoc->m_data.m_bUseCLog){
// 		strpath.Format("C:\\Glim\\LotData\\");
// 		CreateDirectory(strpath,NULL);
// 		strpath.Format("C:\\Glim\\LotData\\%s\\",kk);
// 		CreateDirectory(strpath,NULL);
// 		strpath.Format("C:\\Glim\\LotData\\%s\\%s\\",kk,strLot);
// 		CreateDirectory(strpath,NULL);
// 		filename.Format("%s%s_%sDefect.csv",strpath,strLot,m_strComputerName);
// 	}
// 	else{
		strpath.Format("D:\\Data\\LotData\\");
		CreateDirectory(strpath,NULL);
		strpath.Format("D:\\Data\\LotData\\%s\\",kk);
		CreateDirectory(strpath,NULL);
		strpath.Format("D:\\Data\\LotData\\%s\\%s\\",kk,strLot);
		CreateDirectory(strpath,NULL);
		filename.Format("%s%s_%sDefect.csv",strpath,strLot,m_strComputerName);
	//}
	//	strTitle.Format("Date,lot,Pos x,Pos y, Size X,Size Y,Value,name,Path,File Name");

	//시작	//종료	//Lot	//생산미터	
	strTitle.Format("Time,LotNo,YPos,XPos,SizeX,SizeY,Value,Type,CamPos,ImagePath,FileName,path1");
//	strtmp.Format("%s,%s,%.1f,%.1f,%.1f,%.1f,%.0f,%s,%d,%s,%s,%s",strTime,strLot,dMeterY,dMeterX,dsx,dsy,dvalue,strType,pDoc->m_data.m_nCamID,strimg,imgname,newpath);
	strtmp.Format("%s,%s,%.1f,%.1f,%.1f,%.1f,%.0f,%s,%d,%s,%s,%s,%s,%s,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%s",strTime,strLot,dMeterY,dMeterX,dsx,dsy,dvalue,strType,pDoc->m_data.m_nCamID,strimg,imgname,newpath,
		strmodel,strcolor,dgain,dsize1,dmaxgray,dmingray,davegray,dthvalue,strLocaltime);

	if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
	{		
		if(file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText))
		{
			file.WriteString(strtmp);
			file.Close();
		}
	}
	else
	{
		file.SeekToEnd();
		file.WriteString("\n");
		file.WriteString(strtmp);
		file.Close(); 
	}
}

void CVisWebView::CopyDefectData(CString strLot,CString strDate)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	if(strLot == "")strLot = "NONE";
	CString strsrc1,strdst1,strToppc;
	if(m_strComputerName.Find("CMI")>=0 ||m_strComputerName.Find("OCH")>=0){
		//|| pDoc->m_data.m_nLineSelect%10==2
		strToppc = m_strComputerName.Left(9)+"T1";		
	}
	else
		strToppc = m_strComputerName.Left(m_strComputerName.Find("BACK"))+ "TOP";
	//pcname\\glim\\lotdata\\date\\lot\\ 전부
	// 	if(pDoc->m_data.m_bUseCLog){
	// 		strsrc1.Format("\\\\%s\\Glim\\Lotdata\\%s\\%s\\",strToppc,strDate,strLot);
	// 		strdst1.Format("c:\\Glim\\Lotdata\\%s\\",strDate,strLot);
	// 	}
	//	else{
	strsrc1.Format("\\\\%s\\Data\\Lotdata\\%s\\%s\\",strToppc,strDate,strLot);
	strdst1.Format("D:\\Data\\Lotdata\\%s\\%s\\",strDate,strLot);
	//	}
	double dtime1 = GetPrecisionTime();
	CString str1;
	str1.Format("FileMove Start (%s) %s - %s",strLot,strsrc1,strdst1);
	AddtoList(str1,0);

	SHFILEOPSTRUCT    shfo;
	WORD        wfunc;
	TCHAR        pszTo[1024] = {0};
	TCHAR        pszFrom[1024] = {0};
	TCHAR        pszTitle[MAX_PATH] = {0};
	wfunc = FO_MOVE;
	memset(pszTo, 0, sizeof(pszTo));   // 중요
	memset(pszFrom, 0, sizeof(pszFrom));
	strcpy(pszTitle, "파일이동");
	strcpy(pszTo, strdst1);
	strcpy(pszFrom , strsrc1);
	ZeroMemory(&shfo, sizeof(shfo));
	shfo.hwnd = AfxGetMainWnd()->m_hWnd;
	shfo.wFunc = wfunc;
	shfo.lpszProgressTitle=pszTitle;
	shfo.pTo=pszTo;
	shfo.pFrom=pszFrom;//FOF_NOCONFIRMATION
	shfo.fFlags = FOF_NOCONFIRMMKDIR|FOF_NOCONFIRMATION|FOF_SILENT|FOF_NOERRORUI;

	int ret = SHFileOperation(&shfo);
	double dtime2 = GetPrecisionTime();

	str1.Format("File move End(%s) %s - %.0f",strLot,strDate , (dtime2-dtime1)*1000);
	AddtoList(str1,0,TRUE);
	m_bCopyComplete = FALSE;

}
void CVisWebView::OnBnClickedBtAlarmSet()
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	UpdateTolIni(pDoc->m_data.m_strDefaultModel);				// 20201015 KJH
	pDoc->m_pDlgInterface->LoadInsParam();
	pDoc->m_pDlgInterface->LoadSysParam();//sparam을 사용해야한다.
	pDoc->m_pDlgInterface->	LoadLightParam();

	if(m_SysParam->IsWindowVisible()){
		m_SysParam->ShowWindow(0);
	}
	else{
		m_SysParam->ShowWindow(1);
//		InvalidateRect(CRect(100,100,1800,1000));

	}

}

void CVisWebView::WriteMisMatchData2(int nframe,int nCount)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CString strLot;
	strLot = ConvertCharToStr(cLotID);
	if(strLot=="")strLot = "NONE";

	CString data[6];
	CTime timer=CTime::GetCurrentTime();  
	data[0].Format("%d", timer.GetYear());
	if(timer.GetMonth() < 10)             data[1].Format("0%d", timer.GetMonth());
	else           data[1].Format("%d", timer.GetMonth());
	if(timer.GetDay() < 10)               data[2].Format("0%d", timer.GetDay());
	else           data[2].Format("%d", timer.GetDay());
	if(timer.GetHour() < 10)              data[3].Format("0%d", timer.GetHour());
	else           data[3].Format("%d", timer.GetHour());
	if(timer.GetMinute() < 10)            data[4].Format("0%d", timer.GetMinute());
	else           data[4].Format("%d", timer.GetMinute());
	if(timer.GetSecond() < 10)            data[5].Format("0%d", timer.GetSecond());
	else           data[5].Format("%d", timer.GetSecond());
	CStdioFile   file;
	CString filename;
	CString strpath,strtitle;
	CString str,strtmp1="",strtmp2="",strtmp3="",strtmp4="",strtmp5="",strtmp6="",strtmp7="",strtmp8="",strtmp,strtime;
	int nLen = nCount;
	int nLen1 = nLen %100;
// 	if(pDoc->m_data.m_bUseCLog){
// 		strpath.Format("C:\\Glim\\LotData\\");
// 		CreateDirectory(strpath,NULL); 
// 		strpath.Format("C:\\Glim\\LotData\\%s%s%s\\",data[0],data[1],data[2]);
// 		CreateDirectory(strpath,NULL); 
// 		strpath.Format("C:\\Glim\\LotData\\%s%s%s\\%s\\",data[0],data[1],data[2],strLot);
// 		CreateDirectory(strpath,NULL); 
// 	}
// 	else{
		strpath.Format("D:\\Data\\LotData\\");
		CreateDirectory(strpath,NULL); 
		strpath.Format("D:\\Data\\LotData\\%s%s%s\\",data[0],data[1],data[2]);
		CreateDirectory(strpath,NULL); 
		strpath.Format("D:\\Data\\LotData\\%s%s%s\\%s\\",data[0],data[1],data[2],strLot);
		CreateDirectory(strpath,NULL); 
//	}
	filename.Format("%s%s_MismatchPitch.csv",strpath,pDoc->m_data.m_strComName);
	// 설비길이, Frame , len1,len2,len3....
	//pDoc->m_data.m_nMisMatchPixel[0][i]  //pDoc->m_data.m_nMisMatchPixel[0][i]
	int nc1 = 0, nc2 = 0, nc3 = 0;
	CString strNcoat1,strNcoat2,strCoat1,strCoat2;
	int nframe1 = nframe;
	CString strLogCoat[10];
	CString strLogNCoat[10];
	CString strLogMismatch[10];

	if(pDoc->m_pDlgInterface->m_bPlcWrite){
		for(int i=0;i<10;i++){

			if(i==0) continue;
			else{
				if(i+1<=nCount){

					strtmp1.Format(",%.2f",pDoc->m_data.m_dMisMatchData[0][nframe][i]-pDoc->m_data.m_dMisMatchData[0][nframe][i-1]);
					CString str12;
					str12.Format("%.2f",pDoc->m_data.m_dMisMatchData[0][nframe1][i]-pDoc->m_data.m_dMisMatchData[0][nframe1][i-1]);//0 length 1 TOP 2BACK, 10frame, 20lane  /3 - length mismatch
					if(pDoc->m_pDlgInterface->m_bPlcWrite && i < nCount-1){
						WriteShareMemory(0, i-1,atof(str12)+0.005);// mismatch
						strLogMismatch[nc3] = str12;
						nc3++;
					}

					strtmp2 += strtmp1;

					strtmp1.Format(",%.2f",pDoc->m_data.m_dMisMatchData[1][nframe][i]-pDoc->m_data.m_dMisMatchData[1][nframe][i-1]);
					strtmp3 += strtmp1;
					strtmp1.Format(",%.2f",pDoc->m_data.m_dMisMatchData[2][nframe][i]-pDoc->m_data.m_dMisMatchData[2][nframe][i-1]);
					strtmp4 += strtmp1;
					if(pDoc->m_pDlgInterface->m_bPlcWrite){
						if(i%2==1){//무지 
							strNcoat1.Format("%.2f",pDoc->m_data.m_dMisMatchData[1][nframe1][i]-pDoc->m_data.m_dMisMatchData[1][nframe1][i-1]);//상부 무지
							strNcoat2.Format("%.2f",pDoc->m_data.m_dMisMatchData[2][nframe1][i]-pDoc->m_data.m_dMisMatchData[2][nframe1][i-1]);//하부 무지
							//	WriteShareMemory(1, nc1,atof(strNcoat1)); //context = 0 미스매치 1무지상 2무지하 3코팅상 4코팅하 index눈 순서
							WriteShareMemory(2, nc2,atof(strNcoat2)+0.005);//무지
							strLogNCoat[nc2] = strNcoat2;

							nc2++;
						}
						else{
							strCoat1.Format("%.2f",pDoc->m_data.m_dMisMatchData[1][nframe1][i]-pDoc->m_data.m_dMisMatchData[1][nframe1][i-1]);//상부 코팅
							strCoat2.Format("%.2f",pDoc->m_data.m_dMisMatchData[2][nframe1][i]-pDoc->m_data.m_dMisMatchData[2][nframe1][i-1]);//하부 코팅
							//	WriteShareMemory(3, nc1,atof(strCoat1));
							WriteShareMemory(4, nc1,atof(strCoat2)+0.005);//코팅
							strLogCoat[nc1] = strCoat2;

							nc1++;
						}
						//0312  미스매치   상부 무지폭  하부 무지폭 상부 코팅폭   하부 코팅폭
					}
					pDoc->m_data.m_dMisMatchData[0][nframe][i] = 0;//pDoc->m_data.m_dMisMatchData[1][nframe][i]=0;
				}
				else{
					strtmp1.Format(",0");
					// 				if(pDoc->m_pDlgInterface->m_bPlcWrite){
					// 					WriteShareMemory(0, i-1,atof(strtmp1));
					// 				//	WriteShareMemory(1, i-1,atof(strtmp1));
					// 					WriteShareMemory(2, i-1,atof(strtmp1));
					// 				//	WriteShareMemory(3, i-1,atof(strtmp1));
					// 					WriteShareMemory(4, i-1,atof(strtmp1));
					//	}
					strtmp2 += strtmp1;
					strtmp1.Format(",0");
					strtmp3 += strtmp1;
					strtmp1.Format(",0");
					strtmp4 += strtmp1;
					pDoc->m_data.m_dMisMatchData[0][nframe][i] = pDoc->m_data.m_dMisMatchData[1][nframe][i]=0;
					//0312
				}
			}
		}

		for(int i=nc1; i<10; i++){
			WriteShareMemory(4, i, 0.0);
			strLogCoat[i] = _T("0");
		}
		for(int i=nc2; i<10; i++){
			WriteShareMemory(2, i, 0.0);
			strLogNCoat[i] = _T("0");
		}
		for(int i=nc3; i<10; i++){
			WriteShareMemory(0, i, 0.0);
			strLogMismatch[i] = _T("0");
		}

		// write use check(back)
	
		WriteUseCheck(1, nCount);
		WriteShareMemorySpec();		

		SavePLCSendDataLog(strLogCoat, strLogNCoat, strLogMismatch, strLot, pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck]);
	}
	
	strtime.Format("%s%s%s%s%s%s",data[0],data[1],data[2],data[3],data[4],data[5]);
	//////////////time lot 설비길이 카운트 
	//0312
	
	if(m_strComputerName.Find(_T("OCH"))>=0)
		strtitle.Format("년월일시분초\tLOTNO\t생산M\t에지수\t무지1\t코팅1\t무지2\t코팅2\t무지3\t코팅3\t무지4\t코팅4\t무지5\t무지1\t코팅1\t무지2\t코팅2\t무지3\t코팅3\t무지4\t코팅4\t무지5");
	else
		strtitle.Format("Time\tLOTNO\tMeter\tEdge\tN-Coat1\tCoat1\tN-Coat2\tCoat2\tN-Coat3\tCoat3\tN-Coat4\tCoat4\tN-Coat5\tN-Coat1\tCoat1\tN-Coat2\tCoat2\tN-Coat3\tCoat3\tN-Coat4\tCoat4\tN-Coat5");
//	strtmp.Format("%s\t%s\t%d\t%d\t%s\t%s\t%s",strtime,strLot,pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck],nCount,strtmp2,strtmp3,strtmp4);
	strtmp.Format("%s,%s,%d,%d	,%s	,%s",strtime,strLot,pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck],nCount,strtmp3,strtmp4);

	try{
		g_Mutex.Lock();                    // 뮤텍스를잠근다.
		if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
		{              
			m_nTextWriteCount = 0;
			file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText);
			file.WriteString(strtitle);
			file.WriteString("\n");       
			file.WriteString(strtmp);
			file.WriteString("\n");       
			file.Close();
		}
		else
		{
			file.SeekToEnd();                     
			file.WriteString(strtmp);
			file.WriteString("\n");
			file.Close(); 
		}       
		g_Mutex.Unlock();                 // 뮤텍스를풀어준다.
	}
	catch(CFileException)
	{
		//AfxMessageBox( "File Open failed" );
	}
	catch(...)
	{
		//AfxMessageBox( "File Open failed2~" );
	}
}

void CVisWebView::CheckStats(int ncam,int nio)//홀수 녹색 짝수 빨강
{
	if(ncam%2==0){
		m_lbStatsCAM.SetBkColor(COLOR_RED);
	}
	else if(ncam%2==1){
		m_lbStatsCAM.SetBkColor(COLOR_GREEN);
	}
	if(nio%2==0){
		m_lbStatsIO.SetBkColor(COLOR_RED);
	}
	else if(nio%2==1){
		m_lbStatsIO.SetBkColor(COLOR_GREEN);
	}
}

void CVisWebView::SetShareMemory()
{
	m_strMemoryWriteAddress1[0][0] = "Vision  Missmatch PV_0";
	m_strMemoryWriteAddress1[0][1] = "Vision  Missmatch PV_1";
	m_strMemoryWriteAddress1[0][2] = "Vision  Missmatch PV_2";
	m_strMemoryWriteAddress1[0][3] = "Vision  Missmatch PV_3";
	m_strMemoryWriteAddress1[0][4] = "Vision  Missmatch PV_4";
	m_strMemoryWriteAddress1[0][5] = "Vision  Missmatch PV_5";
	m_strMemoryWriteAddress1[0][6] = "Vision  Missmatch PV_6";
	m_strMemoryWriteAddress1[0][7] = "Vision  Missmatch PV_7";
	m_strMemoryWriteAddress1[0][8] = "Vision  Missmatch PV_8";
	m_strMemoryWriteAddress1[0][9] = "Vision  Missmatch PV_9";
	m_strMemoryWriteAddress1[0][10] = "Vision  Missmatch PV_10";
	m_strMemoryWriteAddress1[0][11] = "Vision  Missmatch PV_11";

	m_strMemoryWriteAddress1[1][0] = "Vision A Non CoatPV_0";
	m_strMemoryWriteAddress1[1][1] = "Vision A Non CoatPV_1";
	m_strMemoryWriteAddress1[1][2] = "Vision A Non CoatPV_2";
	m_strMemoryWriteAddress1[1][3] = "Vision A Non CoatPV_3";
	m_strMemoryWriteAddress1[1][4] = "Vision A Non CoatPV_4";
	m_strMemoryWriteAddress1[1][5] = "Vision A Non CoatPV_5";
	m_strMemoryWriteAddress1[1][6] = "Vision A Non CoatPV_6";
	m_strMemoryWriteAddress1[1][7] = "Vision A Non CoatPV_7";
	m_strMemoryWriteAddress1[1][8] = "Vision A Non CoatPV_8";
	m_strMemoryWriteAddress1[1][9] = "Vision A Non CoatPV_9";


	m_strMemoryWriteAddress1[2][0] = "Vision B Non CoatPV_0";
	m_strMemoryWriteAddress1[2][1] = "Vision B Non CoatPV_1";
	m_strMemoryWriteAddress1[2][2] = "Vision B Non CoatPV_2";
	m_strMemoryWriteAddress1[2][3] = "Vision B Non CoatPV_3";
	m_strMemoryWriteAddress1[2][4] = "Vision B Non CoatPV_4";
	m_strMemoryWriteAddress1[2][5] = "Vision B Non CoatPV_5";
	m_strMemoryWriteAddress1[2][6] = "Vision B Non CoatPV_6";
	m_strMemoryWriteAddress1[2][7] = "Vision B Non CoatPV_7";
	m_strMemoryWriteAddress1[2][8] = "Vision B Non CoatPV_8";
	m_strMemoryWriteAddress1[2][9] = "Vision B Non CoatPV_9";

	m_strMemoryWriteAddress1[3][0] = "Vision A CoatPV_0";
	m_strMemoryWriteAddress1[3][1] = "Vision A CoatPV_1";
	m_strMemoryWriteAddress1[3][2] = "Vision A CoatPV_2";
	m_strMemoryWriteAddress1[3][3] = "Vision A CoatPV_3";
	m_strMemoryWriteAddress1[3][4] = "Vision A CoatPV_4";
	m_strMemoryWriteAddress1[3][5] = "Vision A CoatPV_5";
	m_strMemoryWriteAddress1[3][6] = "Vision A CoatPV_6";
	m_strMemoryWriteAddress1[3][7] = "Vision A CoatPV_7";
	m_strMemoryWriteAddress1[3][8] = "Vision A CoatPV_8";
	m_strMemoryWriteAddress1[3][9] = "Vision A CoatPV_9";

	m_strMemoryWriteAddress1[4][0] = "Vision B CoatPV_0";
	m_strMemoryWriteAddress1[4][1] = "Vision B CoatPV_1";
	m_strMemoryWriteAddress1[4][2] = "Vision B CoatPV_2";
	m_strMemoryWriteAddress1[4][3] = "Vision B CoatPV_3";
	m_strMemoryWriteAddress1[4][4] = "Vision B CoatPV_4";
	m_strMemoryWriteAddress1[4][5] = "Vision B CoatPV_5";
	m_strMemoryWriteAddress1[4][6] = "Vision B CoatPV_6";
	m_strMemoryWriteAddress1[4][7] = "Vision B CoatPV_7";
	m_strMemoryWriteAddress1[4][8] = "Vision B CoatPV_8";
	m_strMemoryWriteAddress1[4][9] = "Vision B CoatPV_9";


	m_strMemoryWriteAddress1[6][0] = "Vision A NonCoatMINMAX_0";
	m_strMemoryWriteAddress1[6][1] = "Vision A NonCoatMINMAX_1";
	m_strMemoryWriteAddress1[6][2] = "Vision A NonCoatMINMAX_2";
	m_strMemoryWriteAddress1[6][3] = "Vision A NonCoatMINMAX_3";
	m_strMemoryWriteAddress1[6][4] = "Vision A NonCoatMINMAX_4";
	m_strMemoryWriteAddress1[6][5] = "Vision A NonCoatMINMAX_5";
	m_strMemoryWriteAddress1[6][6] = "Vision A NonCoatMINMAX_6";
	m_strMemoryWriteAddress1[6][7] = "Vision A NonCoatMINMAX_7";
	m_strMemoryWriteAddress1[6][8] = "Vision A NonCoatMINMAX_8";
	m_strMemoryWriteAddress1[6][9] = "Vision A NonCoatMINMAX_9";


	m_strMemoryWriteAddress1[7][0] = "Vision A CoatMINMAX_0";
	m_strMemoryWriteAddress1[7][1] = "Vision A CoatMINMAX_1";
	m_strMemoryWriteAddress1[7][2] = "Vision A CoatMINMAX_2";
	m_strMemoryWriteAddress1[7][3] = "Vision A CoatMINMAX_3";
	m_strMemoryWriteAddress1[7][4] = "Vision A CoatMINMAX_4";
	m_strMemoryWriteAddress1[7][5] = "Vision A CoatMINMAX_5";
	m_strMemoryWriteAddress1[7][6] = "Vision A CoatMINMAX_6";
	m_strMemoryWriteAddress1[7][7] = "Vision A CoatMINMAX_7";
	m_strMemoryWriteAddress1[7][8] = "Vision A CoatMINMAX_8";
	m_strMemoryWriteAddress1[7][9] = "Vision A CoatMINMAX_9";

	m_strMemoryWriteAddress1[8][0] = "Vision B NonCoatMINMAX_0";
	m_strMemoryWriteAddress1[8][1] = "Vision B NonCoatMINMAX_1";
	m_strMemoryWriteAddress1[8][2] = "Vision B NonCoatMINMAX_2";
	m_strMemoryWriteAddress1[8][3] = "Vision B NonCoatMINMAX_3";
	m_strMemoryWriteAddress1[8][4] = "Vision B NonCoatMINMAX_4";
	m_strMemoryWriteAddress1[8][5] = "Vision B NonCoatMINMAX_5";
	m_strMemoryWriteAddress1[8][6] = "Vision B NonCoatMINMAX_6";
	m_strMemoryWriteAddress1[8][7] = "Vision B NonCoatMINMAX_7";
	m_strMemoryWriteAddress1[8][8] = "Vision B NonCoatMINMAX_8";
	m_strMemoryWriteAddress1[8][9] = "Vision B NonCoatMINMAX_9";


	m_strMemoryWriteAddress1[9][0] = "Vision B CoatMINMAX_0";
	m_strMemoryWriteAddress1[9][1] = "Vision B CoatMINMAX_1";
	m_strMemoryWriteAddress1[9][2] = "Vision B CoatMINMAX_2";
	m_strMemoryWriteAddress1[9][3] = "Vision B CoatMINMAX_3";
	m_strMemoryWriteAddress1[9][4] = "Vision B CoatMINMAX_4";
	m_strMemoryWriteAddress1[9][5] = "Vision B CoatMINMAX_5";
	m_strMemoryWriteAddress1[9][6] = "Vision B CoatMINMAX_6";
	m_strMemoryWriteAddress1[9][7] = "Vision B CoatMINMAX_7";
	m_strMemoryWriteAddress1[9][8] = "Vision B CoatMINMAX_8";
	m_strMemoryWriteAddress1[9][9] = "Vision B CoatMINMAX_9";

	m_strMemoryWriteAddress1[5][0] = "MISSMATCH_TOLERANCE_0";
	m_strMemoryWriteAddress1[5][1] = "MISSMATCH_TOLERANCE_1";
	m_strMemoryWriteAddress1[5][2] = "DEFECT_NUMBER_0";
	m_strMemoryWriteAddress1[5][3] = "DEFECT_NUMBER_1";
	m_strMemoryWriteAddress1[5][4] = "";
	m_strMemoryWriteAddress1[5][5] = "";
	m_strMemoryWriteAddress1[5][6] = "";
	m_strMemoryWriteAddress1[5][7] = "";
	m_strMemoryWriteAddress1[5][8] = "";
	m_strMemoryWriteAddress1[5][9] = "";


	m_strMemoryWriteAddress1[10][0] = "PLC_MODELNAME_1_0";
	m_strMemoryWriteAddress1[10][1] = "PLC_MODELNAME_1_1";
	m_strMemoryWriteAddress1[10][2] = "PLC_MODELNAME_1_2";
	m_strMemoryWriteAddress1[10][3] = "PLC_MODELNAME_1_3";
	m_strMemoryWriteAddress1[10][4] = "PLC_MODELNAME_1_4";
	m_strMemoryWriteAddress1[10][5] = "PLC_MODELNAME_1_5";
	m_strMemoryWriteAddress1[10][6] = "PLC_MODELNAME_1_6";
	m_strMemoryWriteAddress1[10][7] = "PLC_MODELNAME_1_7";
	m_strMemoryWriteAddress1[10][8] = "PLC_MODELNAME_1_8";
	m_strMemoryWriteAddress1[10][9] = "PLC_MODELNAME_1_9";

	m_strMemoryWriteAddress1[11][0] = "PLC_MODELNAME_1_10";
	m_strMemoryWriteAddress1[11][1] = "PLC_MODELNAME_1_11";
	m_strMemoryWriteAddress1[11][2] = "PLC_MODELNAME_1_12";
	m_strMemoryWriteAddress1[11][3] = "PLC_MODELNAME_1_13";
	m_strMemoryWriteAddress1[11][4] = "PLC_MODELNAME_1_14";
	m_strMemoryWriteAddress1[11][5] = "PLC_MODELNAME_1_15";
	m_strMemoryWriteAddress1[11][6] = "PLC_MODELNAME_1_16";
	m_strMemoryWriteAddress1[11][7] = "PLC_MODELNAME_1_17";
	m_strMemoryWriteAddress1[11][8] = "PLC_MODELNAME_1_18";
	m_strMemoryWriteAddress1[11][9] = "PLC_MODELNAME_1_19";

	m_strMemoryWriteAddress1[12][0] = "PLC_MODELNAME_2_0";
	m_strMemoryWriteAddress1[12][1] = "PLC_MODELNAME_2_1";
	m_strMemoryWriteAddress1[12][2] = "PLC_MODELNAME_2_2";
	m_strMemoryWriteAddress1[12][3] = "PLC_MODELNAME_2_3";
	m_strMemoryWriteAddress1[12][4] = "PLC_MODELNAME_2_4";
	m_strMemoryWriteAddress1[12][5] = "PLC_MODELNAME_2_5";
	m_strMemoryWriteAddress1[12][6] = "PLC_MODELNAME_2_6";
	m_strMemoryWriteAddress1[12][7] = "PLC_MODELNAME_2_7";
	m_strMemoryWriteAddress1[12][8] = "PLC_MODELNAME_2_8";
	m_strMemoryWriteAddress1[12][9] = "PLC_MODELNAME_2_9";

	m_strMemoryWriteAddress1[13][0] = "PLC_MODELNAME_2_10";
	m_strMemoryWriteAddress1[13][1] = "PLC_MODELNAME_2_11";
	m_strMemoryWriteAddress1[13][2] = "PLC_MODELNAME_2_12";
	m_strMemoryWriteAddress1[13][3] = "PLC_MODELNAME_2_13";
	m_strMemoryWriteAddress1[13][4] = "PLC_MODELNAME_2_14";
	m_strMemoryWriteAddress1[13][5] = "PLC_MODELNAME_2_15";
	m_strMemoryWriteAddress1[13][6] = "PLC_MODELNAME_2_16";
	m_strMemoryWriteAddress1[13][7] = "PLC_MODELNAME_2_17";
	m_strMemoryWriteAddress1[13][8] = "PLC_MODELNAME_2_18";
	m_strMemoryWriteAddress1[13][9] = "PLC_MODELNAME_2_19";

	m_strMemoryWriteAddress1[14][0] = "PLC_MODELNAME_3_0";
	m_strMemoryWriteAddress1[14][1] = "PLC_MODELNAME_3_1";
	m_strMemoryWriteAddress1[14][2] = "PLC_MODELNAME_3_2";
	m_strMemoryWriteAddress1[14][3] = "PLC_MODELNAME_3_3";
	m_strMemoryWriteAddress1[14][4] = "PLC_MODELNAME_3_4";
	m_strMemoryWriteAddress1[14][5] = "PLC_MODELNAME_3_5";
	m_strMemoryWriteAddress1[14][6] = "PLC_MODELNAME_3_6";
	m_strMemoryWriteAddress1[14][7] = "PLC_MODELNAME_3_7";
	m_strMemoryWriteAddress1[14][8] = "PLC_MODELNAME_3_8";
	m_strMemoryWriteAddress1[14][9] = "PLC_MODELNAME_3_9";

	m_strMemoryWriteAddress1[15][0] = "PLC_MODELNAME_3_10";
	m_strMemoryWriteAddress1[15][1] = "PLC_MODELNAME_3_11";
	m_strMemoryWriteAddress1[15][2] = "PLC_MODELNAME_3_12";
	m_strMemoryWriteAddress1[15][3] = "PLC_MODELNAME_3_13";
	m_strMemoryWriteAddress1[15][4] = "PLC_MODELNAME_3_14";
	m_strMemoryWriteAddress1[15][5] = "PLC_MODELNAME_3_15";
	m_strMemoryWriteAddress1[15][6] = "PLC_MODELNAME_3_16";
	m_strMemoryWriteAddress1[15][7] = "PLC_MODELNAME_3_17";
	m_strMemoryWriteAddress1[15][8] = "PLC_MODELNAME_3_18";
	m_strMemoryWriteAddress1[15][9] = "PLC_MODELNAME_3_19";

	m_strMemoryWriteAddress1[16][0] = "TOP_PGM_STATUS_0";
 	m_strMemoryWriteAddress1[16][1] = "TOP_PGM_STATUS_1";
// 	m_strMemoryWriteAddress1[16][2] = "PLC_MODELNAME_4_2";
// 	m_strMemoryWriteAddress1[16][3] = "PLC_MODELNAME_4_3";
// 	m_strMemoryWriteAddress1[16][4] = "PLC_MODELNAME_4_4";
// 	m_strMemoryWriteAddress1[16][5] = "PLC_MODELNAME_4_5";
// 	m_strMemoryWriteAddress1[16][6] = "PLC_MODELNAME_4_6";
// 	m_strMemoryWriteAddress1[16][7] = "PLC_MODELNAME_4_7";
// 	m_strMemoryWriteAddress1[16][8] = "PLC_MODELNAME_4_8";
// 	m_strMemoryWriteAddress1[16][9] = "PLC_MODELNAME_4_9";

	m_strMemoryWriteAddress1[17][0] = "BACK_PGM_STATUS_0";
 	m_strMemoryWriteAddress1[17][1] = "BACK_PGM_STATUS_1";
// 	m_strMemoryWriteAddress1[17][2] = "PLC_MODELNAME_4_12";
// 	m_strMemoryWriteAddress1[17][3] = "PLC_MODELNAME_4_13";
// 	m_strMemoryWriteAddress1[17][4] = "PLC_MODELNAME_4_14";
// 	m_strMemoryWriteAddress1[17][5] = "PLC_MODELNAME_4_15";
// 	m_strMemoryWriteAddress1[17][6] = "PLC_MODELNAME_4_16";
// 	m_strMemoryWriteAddress1[17][7] = "PLC_MODELNAME_4_17";
// 	m_strMemoryWriteAddress1[17][8] = "PLC_MODELNAME_4_18";
// 	m_strMemoryWriteAddress1[17][9] = "PLC_MODELNAME_4_19";

	m_strMemoryWriteAddress1[18][0] = "TOP_USE_CHECK_0";
	m_strMemoryWriteAddress1[18][1] = "TOP_USE_CHECK_1";
// 	m_strMemoryWriteAddress1[18][2] = "PLC_MODELNAME_5_2";
// 	m_strMemoryWriteAddress1[18][3] = "PLC_MODELNAME_5_3";
// 	m_strMemoryWriteAddress1[18][4] = "PLC_MODELNAME_5_4";
// 	m_strMemoryWriteAddress1[18][5] = "PLC_MODELNAME_5_5";
// 	m_strMemoryWriteAddress1[18][6] = "PLC_MODELNAME_5_6";
// 	m_strMemoryWriteAddress1[18][7] = "PLC_MODELNAME_5_7";
// 	m_strMemoryWriteAddress1[18][8] = "PLC_MODELNAME_5_8";
// 	m_strMemoryWriteAddress1[18][9] = "PLC_MODELNAME_5_9";

	m_strMemoryWriteAddress1[19][0] = "BACK_USE_CHECK_0";
	m_strMemoryWriteAddress1[19][1] = "BACK_USE_CHECK_1";
// 	m_strMemoryWriteAddress1[19][2] = "PLC_MODELNAME_5_12";
// 	m_strMemoryWriteAddress1[19][3] = "PLC_MODELNAME_5_13";
// 	m_strMemoryWriteAddress1[19][4] = "PLC_MODELNAME_5_14";
// 	m_strMemoryWriteAddress1[19][5] = "PLC_MODELNAME_5_15";
// 	m_strMemoryWriteAddress1[19][6] = "PLC_MODELNAME_5_16";
// 	m_strMemoryWriteAddress1[19][7] = "PLC_MODELNAME_5_17";
// 	m_strMemoryWriteAddress1[19][8] = "PLC_MODELNAME_5_18";
// 	m_strMemoryWriteAddress1[19][9] = "PLC_MODELNAME_5_19";

	
}

int CVisWebView::WriteShareMemory(int context, int nindex,double dv1)//context = 0 미스매치 1무지상 2무지하 3코팅상 4코팅하 index눈 순서
{
	int nvalue = dv1*100;

	m_sharedMemoryWrite1[context][nindex].Open(m_strMemoryWriteAddress1[context][nindex],sizeof(int));
	m_sharedMemoryWrite1[context][nindex].SetData(nvalue);
	m_sharedMemoryWrite1[context][nindex].Close();
	return 0;
}

int CVisWebView::WriteShareMemory1(int context, int nindex,int dv1)//context = 0 미스매치 1무지상 2무지하 3코팅상 4코팅하 index눈 순서
{

	m_sharedMemoryWrite1[context][nindex].Open(m_strMemoryWriteAddress1[context][nindex],sizeof(int));
	m_sharedMemoryWrite1[context][nindex].SetData(dv1);
	m_sharedMemoryWrite1[context][nindex].Close();
	return 0;
}

int CVisWebView::WriteShareMemory2(int context, int nindex,CString str1)//context = 0 미스매치 1무지상 2무지하 3코팅상 4코팅하 index눈 순서
{

	m_sharedMemoryWrite1[context][nindex].Open(m_strMemoryWriteAddress1[context][nindex],sizeof(int));
	m_sharedMemoryWrite1[context][nindex].SetData(str1);
	m_sharedMemoryWrite1[context][nindex].Close();
	return 0;
}


int CVisWebView::WriteShareMemorySpec()//context = 0 미스매치 1무지상 2무지하 3코팅상 4코팅하 index눈 순서
{
	int nvalue = 100;
//mis min
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	nvalue = (pDoc->m_pDlgInterface->m_dMismatchTolMin+0.005)*100;
	WriteShareMemory1(5, 0,nvalue);
	nvalue = (pDoc->m_pDlgInterface->m_dMismatchTolMax+0.005)*100*-1;
	WriteShareMemory1(5, 1,nvalue);

	for(int i=0;i<5;i++){
		nvalue = (pDoc->m_pDlgInterface->m_dStandard[i*2]+0.005)*100;//min
		WriteShareMemory1(6, i*2,nvalue);
		WriteShareMemory1(8, i*2,nvalue);
		nvalue = (pDoc->m_pDlgInterface->m_dMaxValue[i*2]+0.005)*100;//max
		WriteShareMemory1(6, i*2+1,nvalue);
		WriteShareMemory1(8, i*2+1,nvalue);
	}
	for(int i=0;i<5;i++){//코팅
		nvalue = (pDoc->m_pDlgInterface->m_dStandard[i*2+1]+0.005)*100;//min
		WriteShareMemory1(7, i*2,nvalue);
		WriteShareMemory1(9, i*2,nvalue);
		nvalue = (pDoc->m_pDlgInterface->m_dMaxValue[i*2+1]+0.005)*100;//max
		WriteShareMemory1(7, i*2+1,nvalue);
		WriteShareMemory1(9, i*2+1,nvalue);
	}


	return 0;
}



int CVisWebView::FullLineProjection(int nCam,int nIndex,int nHeight,int nMod)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	int ndivide = nHeight/nMod;
	int nmaxy1 = ndivide*nIndex,nmaxy2 = ndivide*(nIndex+1);
	int nmaxx1 = 1000,nmaxx2 = CAM_WIDTH_CIS*3-1000;
	int nMod1 = pDoc->m_data.m_nLineReduce,nWhTh = 200,nwhitecnt=0;

	double * dproj= (double*)malloc(CAM_WIDTH_CIS*3*sizeof(double));
	memset(dproj,0,sizeof(double)*(CAM_WIDTH_CIS*3));

	for(int y=nmaxy1;y<nmaxy2;y+=nMod1){
		for(int x=nmaxx1;x<nmaxx2;x++){
			if(y==0 || y==CAM_HEIGHT_CIS-nMod1){//첫줄 white Line Check
				if(*(m_Inspect.m_FullImage + y*(CAM_WIDTH_CIS*3)+x)>nWhTh)//개수만 본다
					nwhitecnt++;
			}
			if(y>=CAM_HEIGHT_CIS|| y<0){
				if(dproj) free(dproj);m_bLineProj[nIndex] = FALSE;return -1;
			}
			if(dproj[x]<0)	dproj[x] =0;
			dproj[x] += *(m_Inspect.m_FullImage + y*(CAM_WIDTH_CIS*3)+x);
		}
	}
	for(int x=nmaxx1;x<nmaxx2;x++){
		dproj[x] /= (ndivide/nMod1);
		pDoc->m_data.m_nFullImageProj1[nIndex][x] = int(dproj[x]);//분할 데이터 입력	
//		if(dproj[x]>10)		TRACE("%d,%d,%d \n", x,nIndex,pDoc->m_data.m_nFullImageProj1[nIndex][x]);
	}

 	if(nmaxy1==0)pDoc->m_data.m_nSkipWhite[0] = nwhitecnt;
 	else if(nmaxy2==CAM_HEIGHT_CIS)
 		pDoc->m_data.m_nSkipWhite[1] = nwhitecnt;

	if(dproj) free(dproj);
	m_bLineProj[nIndex] = FALSE;

	return 0;
}
int	CVisWebView::TransLineData()
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	int nTmp=0,nTmp1 = 0;;
	int nCam = 0;
	int nmax = 0,ncnt1= 0;
	int nstart = 0;
	int nend = CAM_WIDTH_CIS*3;
 	if(nstart <2300)nstart = 2300;//limit inspect range
 	if(nend>CAM_WIDTH_CIS*3-2300)nend = CAM_WIDTH_CIS*3-2300;//limit inspect range
	BOOL bPing = FALSE;
	pDoc->m_data.m_nCadidateEndpos = 0;
	int nJump1 = 15,nJunp2 = 0,nWhite=0,nBlack=0;
	int nHisto[256] = {0,};
	//한개 data로 우측 끝만 먼저 찾는다.
	int nEndPos = nend,nstart11=nstart;
	for(int x=nend;x>nstart;x--){
		if(abs(pDoc->m_data.m_nFullImageProj1[0][x] - pDoc->m_data.m_nFullImageProj1[0][x-6])>30){
			nEndPos = x-6;break;}
	}
	//처음과 마지막의 무지부 밝기를 체크한다. 10픽셀 //자동 밝기용
	pDoc->m_data.m_nNCoatBrightness[1] = 0;
	for(int x=nEndPos-2;x>nEndPos-2-10;x--){
		pDoc->m_data.m_nNCoatBrightness[1] += pDoc->m_data.m_nFullImageProj1[0][x];
	}
	pDoc->m_data.m_nNCoatBrightness[1] /= 10;
	pDoc->m_data.m_nNCoatBrightness[0] = 0;
	for(int x=nstart;x<CAM_WIDTH_CIS;x++){//카메라 0번에서만 찾늗나.
		if(abs(pDoc->m_data.m_nFullImageProj1[0][x] - pDoc->m_data.m_nFullImageProj1[0][x+6])>30){
			nstart11 = x+6;
			for(int x11=nstart11+2;x11<nstart11+2+10;x11++)
				pDoc->m_data.m_nNCoatBrightness[0] += pDoc->m_data.m_nFullImageProj1[0][x11];
		break;
		}

	}
	pDoc->m_data.m_nNCoatBrightness[0] /= 10;

	pDoc->m_data.m_nCadidateEndpos = nEndPos;
	int nBlackCut = 350,nWhiteCut = 50,nWhiteCut1 = 15,nWhiteCut2 = 50;
	for(int x=nstart;x<nend;x++){
		nTmp = 0;
		for(int i=0;i<MOD_COUNT;i++){
			nTmp += pDoc->m_data.m_nFullImageProj1[i][x];

		}
		if(nTmp<0)
			return -1;
		if(pDoc->m_data.m_nCandidateLine==1)//처음 무지
			nWhiteCut = nWhiteCut1; //15
		else nWhiteCut = nWhiteCut2;//50 //중간 무지
		if(x>nEndPos-100)nWhiteCut = nWhiteCut1;//15 //마지막 무지
		if(nWhite==0 && abs(pDoc->m_data.m_nFullImageProj1[3][x] - pDoc->m_data.m_nFullImageProj1[3][x-2])<pDoc->m_pDlgInterface->m_nLineTh1)
		{
			nBlack++;
		}
		else if(nBlack==0 &&abs(pDoc->m_data.m_nFullImageProj1[3][x] - pDoc->m_data.m_nFullImageProj1[3][x-2])<pDoc->m_pDlgInterface->m_nLineTh1){
			nWhite++;
			if(pDoc->m_data.m_nCandidateLine==1)
				nJump1 =0;
		}
		else{
			if(nBlack>nBlackCut){
				nBlack = 0;
				nWhite = 1;
				if(pDoc->m_data.m_nCandidateLine==0)pDoc->m_data.m_rtSubLine[pDoc->m_data.m_nCandidateLine].left = x;
				else								pDoc->m_data.m_rtSubLine[pDoc->m_data.m_nCandidateLine-1].right = x;
				pDoc->m_data.m_nCandidateLine++;
				if(pDoc->m_data.m_nCandidateLine>1)
					pDoc->m_data.m_rtSubLine[pDoc->m_data.m_nCandidateLine-1].left = x;
			}
			else if(nWhite>nWhiteCut){
				if(pDoc->m_data.m_nCandidateLine>0){
					pDoc->m_data.m_rtSubLine[pDoc->m_data.m_nCandidateLine-1].right = x;;
					pDoc->m_data.m_rtSubLine[pDoc->m_data.m_nCandidateLine].left = x;;
					pDoc->m_data.m_nCandidateLine++;
					//				pDoc->m_data.m_rtSubLine[pDoc->m_data.m_nCandidateLine].left = x;;
				}
				nBlack = 1;
				nWhite = 0;
			}else{

			}
		}
		pDoc->m_data.m_nFullImageProj[x] = (nTmp/MOD_COUNT);//평균 Proj Data
		if(bPing&& x<nEndPos)
			nHisto[pDoc->m_data.m_nFullImageProj[x]]++;
		if(x > nstart+10){
			nTmp1 = abs(pDoc->m_data.m_nFullImageProj[x]-pDoc->m_data.m_nFullImageProj[x-4]);
			if(nTmp1>20){
				bPing = TRUE;
				ncnt1++;
				nmax+= nTmp1;
			}
		}

//		if(nTmp>10)		TRACE("%d  %d \n", x,pDoc->m_data.m_nFullImageProj[x]);
		if(x<CAM_WIDTH_CIS)nCam = 0;
		else if(x<CAM_WIDTH_CIS*2)nCam=1;
		else	nCam=2;
		int x1 = (x%CAM_WIDTH_CIS);
		pDoc->m_data.m_nProjectX[nCam][x1] =pDoc->m_data.m_nFullImageProj[x];//기존 Data 분기
	}
	if(ncnt1>0){//20 이상 밝기 차이는 Edge 평균 Data
		pDoc->m_data.m_nEdgeAverage[0] = (nmax/ncnt1);
	}
	else
		pDoc->m_data.m_nEdgeAverage[0] = 0;
	if(pDoc->m_data.m_nEdgeAverage[0]>80)pDoc->m_data.m_nEdgeAverage[0] = 70;
	int nmin1 = 0,nmax1=0;//한줄 data
	int ncut1 = 2500,ncut2 = 500;
	for(int i=0;i<256;i++){
		if(nmin1>ncut1){		
			nmin1 = i;break;	}
		nmin1 += nHisto[i];
	}
	for(int i=255;i>=0;i--){
		if(nmax1>ncut2){		
			nmax1 = i;break;	}
		nmax1 += nHisto[i];
	}

	if(nmin1<200)
		pDoc->m_data.m_dAverageBrightness2[1] = nmin1;
	if(nmax1<255)
		pDoc->m_data.m_dAverageBrightness2[0] = nmax1;

	pDoc->m_data.m_dAverageBrightness2[2] = pDoc->m_data.m_nEdgeAverage[0];

	pDoc->m_data.m_nCoatAveBrightness = (nmax1+nmin1)*0.5;
	if(pDoc->m_data.m_nCoatAveBrightness > 200){
		pDoc->m_data.m_nCoatAveBrightness = 180;
	}
	return 0;
}

int	CVisWebView::FullLineSearch()
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CString strtmp1;
//	double dBufCopy = GetPrecisionTime();////				
	pDoc->m_data.m_dInspDetailTime[0][9] = GetPrecisionTime();

	strtmp1.Format("%d Line Search (%f.0ms)",pDoc->m_nTotalIns[0],(pDoc->m_data.m_dInspDetailTime[0][9]-pDoc->m_data.m_dInspDetailTime[0][0])*1000);//2750	//pDoc->m_data.m_dInspDetailTime[nCam][0]
	AddtoInsLog(strtmp1);
	m_Inspect.m_nCheckLine = 0;
	pDoc->m_data.ResetData(0);
	pDoc->m_data.ResetData(1);
	pDoc->m_data.ResetData(2);

	pDoc->m_data.m_nCandidateLine = 0;

	// 무지용 ROI를 만든다.
	
	int nSleep1 = 0;
	for(int i=0;i<MAX_LENGTH;i++)
		pDoc->m_data.m_nLanePos[i][0]=pDoc->m_data.m_nLanePos[i][1] = 0;

	for(int i=0;i<20;i++){	for(int j=0;j<2;j++)			m_ptLinePos[i][j].SetPoint(0,0);}//0301}

	for(int i=0;i<500;i++){//Waiting
		if(m_bFullCopy[0] && m_bFullCopy[1] && m_bFullCopy[2]){
			m_nInspTimeOut = 0;
			break;
		}
		Wait(1);
		nSleep1++;
		m_nInspTimeOut = 1;
	}
	int nmeter11 = pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck];

	if(m_nInspTimeOut==1){
		m_bFullCopy[0] =m_bFullCopy[1] =m_bFullCopy[2] = FALSE;
		strtmp1.Format("%d Insp. Time Out Meter:%d",pDoc->m_nTotalIns[0],nmeter11);
		AddtoInsLog(strtmp1);
		return 0;
	}
	for(int i=0;i<MOD_COUNT;i++)m_bLineProj[i]=TRUE; //Porjection start
	int ncnt=0,ncnt1=0,nAve=0;
	pDoc->m_data.m_nInsulateDefectCount = 0;
	pDoc->m_data.m_dAverageBrightness1[0]=pDoc->m_data.m_dAverageBrightness1[1]=pDoc->m_data.m_dAverageBrightness1[2]=0;
	int nSleep = 200;
	if(m_strComputerName.Find("CHO")>=0)
		nSleep = 500;


	while(1){
		Wait(1);ncnt++;ncnt1 = 0;
		for(int i=0;i<MOD_COUNT;i++){
			if(m_bLineProj[i]==FALSE)ncnt1++;
		}
		if( ncnt1>=MOD_COUNT){//100ms 대기 및 완료 체크 m_nInspBreak
			break;
		}
		if(ncnt>nSleep ){
			m_nInspBreak[0]=m_nInspBreak[1]=m_nInspBreak[2] = 10;
			break;
		}
	}	
	
	int nRtn; 
	BOOL bAnode = FALSE;
	if(m_nMachine==0 && m_bInsulateInspect)bAnode = FALSE;
	CString strFilePath = _T("");
	if(ncnt1>=MOD_COUNT)
	{//put data
		TransLineData();//w전체 Proj DAta 생성
		//check Camera //라인 유무 체크

		if(pDoc->m_pDlgInterface->m_bSharpness){
//sharpness 구하기

			m_Inspect.FullLineSearch3(&pDoc->m_data);
			MagImageCopy(pDoc->m_data.m_nFoilEdge[0],pDoc->m_data.m_nFoilEdge[1]);
			m_pDlgFullImage->DrawMagImage(3);

			m_bFullCopy[0] =m_bFullCopy[1] =m_bFullCopy[2] = FALSE;

			return 0;
		}
		CheckCamera();
		//실린더 올라가있는지 체크 
		m_nCylinderOnOff = 1;
		nRtn = CamCheckWD();
// 		if(!nRtn){
// 			AddtoList("Cylinder off!",0);
// 			CString str;str.Format("Camera Cylinder Off!");
// 			m_lbNonCoating.SetText(str);
// 			m_lbNonCoating.ShowWindow(1);
// 			m_nCylinderOnOff = 0;
// 
// 		}
		if(m_nCamNoiseCheck>200 ){
			//settime
			if(m_strComputerName.Find("CHO")>=0) ;
			else
				SetTimer(20145,200,NULL);
			AddtoList("Cam Initailization",0);
		}
// 		if(pDoc->m_pDlgInterface->m_bReverseTest)		nAve = m_Inspect.FullLineSearch1(&pDoc->m_data);//전체영상 라인 에지 검출
//		else	
			nAve = m_Inspect.FullLineSearch(&pDoc->m_data);//전체영상 라인 에지 검출
			if(m_Inspect.m_nCheckLine>0){
				if(m_Inspect.m_nCheckLine==1)
					AddtoList("Line Research 1",0);
				else if(m_Inspect.m_nCheckLine==2)	AddtoList("Line Refind 1",0);
			}
			//에지 이미지 copy
			if(m_bEdgeView || nmeter11%100==0){
				CRect rttmp;
				int hy = CAM_HEIGHT_3072*0.5,ngap1 = EDGE_IMG_WIDTH*0.5;
				for(int i=0;i<pDoc->m_data.m_nNewLineCount;i++){
					int nx1 = pDoc->m_data.m_dNewLineEdgeData1[i];
					rttmp.SetRect(nx1-ngap1,hy-ngap1,nx1+ngap1,hy+ngap1);
					m_Inspect.ImageSelectCopy2(m_Inspect.m_FullImage,m_fmEdgeVew[i]->GetImagePtr(),CAM_WIDTH_CIS*3,CAM_HEIGHT_CIS,rttmp.left,rttmp.right,rttmp.top,rttmp.bottom,EDGE_IMG_WIDTH,EDGE_IMG_HEIGHT,0,0);

					pDoc->m_data.m_dSharpness2[i] = 0;
					//sharpness도 구한다.
					double dmax1 = 0,dmax2 = 0,dc=0;
					for(int y=0;y<EDGE_IMG_HEIGHT;y++){
						dmax1 = 0;
						for(int x=44;x<84;x++){
							double dsharp = abs(*(m_fmEdgeVew[i]->GetImagePtr()+y*EDGE_IMG_WIDTH+x) - *(m_fmEdgeVew[i]->GetImagePtr()+y*EDGE_IMG_WIDTH+x+1))*12;
							if(dmax1<dsharp)dmax1 = dsharp;
							if(y<65 &&x>=63 && x <= 65)//이미지에 라인 ㄱ리기
								*(m_fmEdgeVew[i]->GetImagePtr()+y*EDGE_IMG_WIDTH+x) = 0x00;
						}
						dmax2 += dmax1;
						dc++;
					}
					dmax2 /= dc;
					pDoc->m_data.m_dSharpness2[i] = dmax2;

					if(nmeter11%100==0){
						//sharpness
						SaveEdgeImage(nmeter11,i,m_strLotID,dmax2, strFilePath);//
					}
				}
				m_ViewImage->DrawEdgeImage(pDoc->m_data.m_nNewLineCount);
				if(nmeter11%100==0 /*&& pDoc->m_data.m_nSubFrameCount==0*/){
					WriteSharpness(m_strLotID,nmeter11,pDoc->m_data.m_nNewLineCount, strFilePath);
				}

			}
			if(pDoc->m_data.m_nChangeLine[1]%2 ==0 && pDoc->m_data.m_nChangeLine[0] != pDoc->m_data.m_nChangeLine[1]){
				CString strtmp13;
				strtmp13.Format("Line Change %d, %d",pDoc->m_data.m_nChangeLine[0],pDoc->m_data.m_nChangeLine[1]);
				AddtoList(strtmp13,0);
			}
		//절연 체크
		if(bAnode==TRUE){
			int nStats = FindInsulate();
			if(nStats>-1){
				for(int i=0;i<MOD_COUNT;i++)
					m_bInsulateDefect[i] = TRUE;
			}
			else{
				pDoc->m_data.m_nInsulateCount = 0;
				for(int k2=0;k2<40;k2++){
					pDoc->m_data.m_dInsulatePos[k2] = 0;
					pDoc->m_data.m_rtinsulate1[k2].SetRect(0,0,0,0);//절연폭만
				}
				for(int i=0;i<MOD_COUNT;i++)
					m_bInsulateDefect[i] = FALSE;
			}
		}
//Lane check
//		pDoc->m_data.FindLane();
		if(pDoc->m_nTotalIns[0]>1)
			CheckPosition(pDoc->m_data.m_nNewLineCount);
		int  nLane = pDoc->m_data.FindLane( pDoc->m_data.m_nNewLineCount, pDoc->m_data.m_nEpcPos);
		if(pDoc->m_data.m_nSkipWhite[0]<pDoc->m_data.m_nSkipWhite[1])pDoc->m_data.m_nSkipWhite[0] = pDoc->m_data.m_nSkipWhite[1];//코팅 안된 카운트
		pDoc->m_data.m_nWhiteLineCount[0]=pDoc->m_data.m_nWhiteLineCount[1]=pDoc->m_data.m_nWhiteLineCount[2]=pDoc->m_data.m_nSkipWhite[0];
		for(int i=0;i<MAX_CAMERAS;i++)m_avgBrightness[i] = pDoc->m_data.m_dAvgBrightness[i] =pDoc->m_data.m_dAveRealBright[i] =nAve;//전체영상 제품 평균 밝기 무지+코팅

		pDoc->m_data.m_nOldLineCount=0;
			for(int i=0;i<40;i++)
				pDoc->m_data.m_dNewLineEdgeData1Old[i] = 0;;
		

		int nTesting = m_bNewMode;
		if(nTesting==0)
			m_bWaitThread[0]=m_bWaitThread[1]=m_bWaitThread[2]=TRUE;//thread check
		else{

			strtmp1.Format("%d Line End (%f.0ms)",pDoc->m_nTotalIns[0],(GetPrecisionTime()-pDoc->m_data.m_dInspDetailTime[0][9])*1000);//2750	//pDoc->m_data.m_dInspDetailTime[nCam][0]
			AddtoInsLog(strtmp1);

			//검사 
			Inspect3(0);
		}
	}
	m_bFullCopy[0] =m_bFullCopy[1] =m_bFullCopy[2] = FALSE;


	return 0;
}
BOOL CVisWebView::Inspect2(int nCam)
{
	try
	{
		//1412
		CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
		pDoc->m_data.m_bInspectComplete[nCam] = TRUE;
		pDoc->m_data.m_bIsDispCheck = TRUE;
		m_nSaveCheck[0] = 0;
		m_nResultOkNg = 0;
		double dLimitTimeout = 800;
		if(pDoc->m_data.m_nSubFrameCount>=18){
			pDoc->m_data.m_nSubFrameCount = 0;
		}
		if(nCam==0){
			m_nAlarmLog = 0;
			for(int i=0;i<20;i++)
				m_strPitchMismatch[i] = "";
		}
		int cam = nCam;
		if((m_bAuto==FALSE && m_bRun==FALSE) || (m_bAuto<0 && m_bRun<0)){
			return 0;
		}
		pDoc->m_nTotalIns[nCam]++;

		if(nCam==1){
			CString str123;
			str123.Format("Cam1 Inspect %d",pDoc->m_nTotalIns[nCam]);
			AddtoInsLog(str123);

		}
		BOOL bRet=TRUE;
		int npc = pDoc->m_data.GetVisionLine(cam);
		double dtmp = 0.,dtmp1 = 0.,dAve =0, dInsTime=0;
		m_nOldCount[cam] = 0;//marking 전송용 불량 개수
		pDoc->m_data.m_nServerSendDefectCount = 0;
		pDoc->m_data.m_dFullTime[nCam*10+3] = pDoc->m_data.m_dInspDetailTime[nCam][1] = GetPrecisionTime();//
		CRect rtinsp;
		if(pDoc->m_data.m_rectIns[0].Width()<10)
			rtinsp = pDoc->m_data.m_rectIns[0];
		else
			rtinsp.SetRect(0,0,pDoc->m_data.m_nCameraWidth,pDoc->m_data.m_nCameraHeight);
		pDoc->m_data.m_rectIns[cam] = rtinsp;
		int nEdgeDir = pDoc->m_data.m_nNotInsArea[0];//-1;//-1 l2r 1 r2l 0 param
		int nAve[3] = {0,};
		if(m_bCrossBlobImg &&m_bViewTest1){//Cal mode
			pDoc->m_data.m_nFullImageSaveFrame = 50;//10장
			pDoc->m_data.m_nMiniImageSaveFrame = 50;//10
		}
		else{
			pDoc->m_data.m_nFullImageSaveFrame = 100;//10장
			pDoc->m_data.m_nMiniImageSaveFrame = 10;//10
		}
		pDoc->m_data.m_bSumEdgeData = TRUE;

		for(int i=0;i<10;i++){
//			pDoc->m_data.m_dAverageData[i] = 0;
			for(int j=0;j<MOD_COUNT;j++)pDoc->m_data.m_dAverageData1[nCam][j][i] = 0;
		}

		if(nCam==0){
			CString strtmp1,strtmp2,strtime1;
			for(int i=0;i<pDoc->m_data.m_nNewLineCount;i++){
				strtmp1.Format("%d : %.2f \t",i+1,pDoc->m_data.m_dNewLineEdgeData1[i]);
				strtmp2 += strtmp1;
			}
			strtime1.Format("Pixel %s",strtmp2);
			strtmp1.Format("%d Defect Find %d - %s",pDoc->m_nTotalIns[0],pDoc->m_data.m_nNewLineCount,strtime1);

			AddtoInsLog(strtmp1);
		}
	
		if(nCam==1)
			nCam = nCam;
		///에지 검출 Full Image
		int ncnt = 0,ncnt1 = 0;
		BOOL bTesting = FALSE;
		if(m_nLastBrightness[nCam] > pDoc->m_pDlgInterface->m_nSkipPixel || pDoc->m_data.m_nWhiteLineCount[nCam] > pDoc->m_pDlgInterface->m_nSkipPixel )
		{
			bTesting = TRUE;
			if(nCam==1)
				m_nRestartSkipFrame = pDoc->m_nTotalIns[nCam]+3;
		}

		if(bTesting == FALSE && nCam==1 && pDoc->m_nTotalIns[nCam] < m_nRestartSkipFrame)
			bTesting = TRUE;
		m_nLastBrightness[nCam] = pDoc->m_data.m_nWhiteLineCount[nCam];

		if(bTesting==FALSE && pDoc->m_data.m_bInspStart && pDoc->m_data.m_nNewLineCount>2){// 설비 검사 Signal On


			//이전 쓰래드 살아있는지 확인
			int ncheck11 = 0;
//  			for(int j=0;j<8;j++)//8개의 Thread
//  				if(m_bTestFlag[nCam][j]!=FALSE)
// 					ncheck11++;
// 			if(ncheck11 >= 1){
// // 				for(int j=0;j<8;j++)//8개의 Thread
// // 					m_bTestFlag[nCam][j]=FALSE;
// 				CString strtmp11;
// 				strtmp11.Format("Line Error 1");
// 				AddtoInsLog(strtmp11);
// 				goto DONE;
// //				return 0; 
// 			}
			double dtime = pDoc->m_data.m_dFullTime[nCam*10+4] = pDoc->m_data.m_dInspDetailTime[nCam][2] = GetPrecisionTime();
			BOOL bThread = FALSE;
			if(pDoc->m_data.m_nWhiteLineCount[nCam]<pDoc->m_pDlgInterface->m_nSkipPixel) //코팅이 안되있으면 스킵
				bThread = TRUE;
			else{
				m_nSkipFrame[nCam]=0;
			}
			if(m_nSkipFrame[0] <=pDoc->m_pDlgInterface->m_dSkipMeter ||m_nSkipFrame[1] <=pDoc->m_pDlgInterface->m_dSkipMeter ||m_nSkipFrame[2] <=pDoc->m_pDlgInterface->m_dSkipMeter)
				bThread = FALSE;
			//m_dSkipMeter
			if(bThread){
				if(m_avgBrightness[cam] > pDoc->m_data.m_dLimitMaxBright[nCam]){
					m_nBrightcheck[nCam] = 1;
				}
				else{
					for(int k=0;k<pDoc->m_data.m_nLineCount1[nCam];k++){
						pDoc->m_data.m_rtInspect[nCam][k].DeflateRect(pDoc->m_data.m_nEdgeOffset,0);
						for(int kk1=0;kk1<MOD_COUNT;kk1++)
							pDoc->m_data.m_rtInspect1[nCam][kk1][k].DeflateRect(pDoc->m_data.m_nEdgeOffset,0);
					}
//flag check
					int ncheckcnt = 0,ncheckcnt1 = 0;
					for(int l=0;l<8;l++){
// 						if(m_bTestFlag[nCam][l])
// 							ncheckcnt++;
						if(m_nInspFlag[nCam][l]==2)
							ncheckcnt1++;
					}
					pDoc->m_data.m_nKillFunction[nCam] = 0;

					if(ncheckcnt >0 || ncheckcnt1>0){
						CString strtmp12;
						strtmp12.Format("%d-%d -TestInsp:%d,RoiInsp:%d",nCam,pDoc->m_nTotalIns[nCam],ncheckcnt,ncheckcnt1);
						AddtoList(strtmp12,0);
						m_nThreadcheck[0]=m_nThreadcheck[1]=m_nThreadcheck[2] = 1;
						pDoc->m_data.m_nKillFunction[nCam] = 1;
						goto DONE;
						//return 0; 

					}
					for(int l=0;l<8;l++){
//						m_bTest[nCam][l]=FALSE;//edge 검사 완료  //TestInspect
// 						m_bTestFlag[nCam][l] = TRUE;//에지검사 스타트 //test inspect
						m_nInspFlag[nCam][l] = 1;//무지 검사 스타트  roiinsp
//						m_bPreprocessing[nCam][l] = TRUE;
					}

					//thread 분기
					BOOL bTesting = TRUE;
					if(!pDoc->m_pDlgInterface->m_bPreprocessing)bTesting = FALSE;
					while(1)
					{//2번 카메라의 평균 밝기로 검사 유무 판다.
						if(m_avgBrightness[1] > 0 &&m_avgBrightness[1] >=  pDoc->m_data.m_dLimitMaxBright[0]){// ||nAve <=  pDoc->m_data.m_dLimitMinBright[cam])
							m_nAlarmEndFRame = 0;
							m_bAlarmOnOff = FALSE;
							m_IO[0].WriteOutputPort(0,0,FALSE);
							AddtoList("Product Change1 Off",0,TRUE);
							m_nBrightcheck[nCam] = 1;
							break;
						}
						if(bTesting){
							if(/*m_bTest[nCam][0] && m_bTest[nCam][1]&&m_bTest[nCam][2] && m_bTest[nCam][3]&& m_bTest[nCam][4]&& m_bTest[nCam][5]&& m_bTest[nCam][6]&& m_bTest[nCam][7]&&*/
								m_nInspFlag[nCam][0]==0 && m_nInspFlag[nCam][1]==0&&m_nInspFlag[nCam][2]==0 && m_nInspFlag[nCam][3]==0&& m_nInspFlag[nCam][4]==0&& m_nInspFlag[nCam][5]==0&& m_nInspFlag[nCam][6]==0&& m_nInspFlag[nCam][7]==0&&
								m_bPreprocessing[nCam][0]==FALSE  &&m_bPreprocessing[nCam][1]==FALSE &&m_bPreprocessing[nCam][2]==FALSE &&m_bPreprocessing[nCam][3]==FALSE &&m_bPreprocessing[nCam][4]==FALSE &&m_bPreprocessing[nCam][5]==FALSE &&m_bPreprocessing[nCam][6]==FALSE &&m_bPreprocessing[nCam][7]==FALSE ){
									break;//
							}
						}
						else{
							if(/*m_bTest[nCam][0] && m_bTest[nCam][1]&&m_bTest[nCam][2] && m_bTest[nCam][3]&& m_bTest[nCam][4]&& m_bTest[nCam][5]&& m_bTest[nCam][6]&& m_bTest[nCam][7]&&*/
								m_nInspFlag[nCam][0]==0 && m_nInspFlag[nCam][1]==0&&m_nInspFlag[nCam][2]==0 && m_nInspFlag[nCam][3]==0&& m_nInspFlag[nCam][4]==0&& m_nInspFlag[nCam][5]==0&& m_nInspFlag[nCam][6]==0&& m_nInspFlag[nCam][7]==0){
									break;//
							}
						}
						Wait(1);
						if(nCam==2)
							nCam = 2;
						double dtime1 =  GetPrecisionTime();
						if((dtime1-dtime)*1000 >dLimitTimeout)
						{
							m_nInspBreak[nCam] += 100;

							break;
						}
					}
				}
				if(pDoc->m_pDlgInterface->m_bOriginImage==FALSE){
					if(nCam==0)		memcpy(pDoc->m_pImage->GetImagePtr(),m_Inspect.m_fmPreprocess[nCam],CAM_WIDTH_CIS*CAM_HEIGHT_3072);
					else if(nCam==1)memcpy(pDoc->m_pImage1->GetImagePtr(),m_Inspect.m_fmPreprocess[nCam],CAM_WIDTH_CIS*CAM_HEIGHT_3072);
					else			memcpy(pDoc->m_pImage2->GetImagePtr(),m_Inspect.m_fmPreprocess[nCam],CAM_WIDTH_CIS*CAM_HEIGHT_3072);
				}

				pDoc->m_data.m_dFullTime[nCam*10+5] = pDoc->m_data.m_dInspDetailTime[nCam][3] = GetPrecisionTime();
				//		m_Inspect.GetDataSort(pDoc->m_pImage,&pDoc->m_data,0);//Line Code insert //m_dLineEdgeData1if(nc
				if(nCam==0)
					m_Inspect.GetLineDataSort(pDoc->m_pImage,&pDoc->m_data,nCam,pDoc->m_nTotalIns[0]);//Line Code insert //m_dLineEdgeData1  //defect 이미지 정리
				else if(nCam==2)
					m_Inspect.GetLineDataSort(pDoc->m_pImage2,&pDoc->m_data,nCam,pDoc->m_nTotalIns[0]);//Line Code insert //m_dLineEdgeData1
				else
					m_Inspect.GetLineDataSort(pDoc->m_pImage1,&pDoc->m_data,nCam,pDoc->m_nTotalIns[0]);//Line Code insert //m_dLineEdgeData1

				pDoc->m_data.m_dFullTime[nCam*10+6] = pDoc->m_data.m_dInspDetailTime[nCam][4] = GetPrecisionTime();
			}

			if(npc != GL1&&npc != GL9){//check
				if(pDoc->m_data.m_nServerSendDefectCount)		bRet=FALSE;
				else											bRet=TRUE;
			}
		}
		else{	// 설비 검사 Signal Off
			pDoc->m_data.m_nLineCount1[nCam] = 0;
//			RectInvalidate(10);
			Wait(10);
			if(nCam==1){
				CString strttp1;
				strttp1.Format("Skip %d, %d",m_nRestartSkipFrame,pDoc->m_nTotalIns[nCam]);
				AddtoList(strttp1,0,0);

			}
			for(int i2=0;i2<20;i2++)
			{
				pDoc->m_data.m_rtOldCoatChar[i2].SetRect(0,0,0,0);
				pDoc->m_data.m_rtCoatChar[i2].SetRect(0,0,0,0);
				m_lbCoatLen[i2].ShowWindow(0);
			}
			if(pDoc->m_pDlgInterface->m_bOriginImage==FALSE){
				if(nCam==0)		memcpy(pDoc->m_pImage->GetImagePtr(),m_Inspect.m_fmPreprocess[nCam],CAM_WIDTH_CIS*CAM_HEIGHT_3072);
				else if(nCam==1)memcpy(pDoc->m_pImage1->GetImagePtr(),m_Inspect.m_fmPreprocess[nCam],CAM_WIDTH_CIS*CAM_HEIGHT_3072);
				else			memcpy(pDoc->m_pImage2->GetImagePtr(),m_Inspect.m_fmPreprocess[nCam],CAM_WIDTH_CIS*CAM_HEIGHT_3072);
			}
			if(nCam==1)
				DrawImage(4);
			return 0;
		}

		// 모든 카메라가 검사가 끝날때 까지 기다린다.
// 		int nComplete = 1;
// 		if( m_avgBrightness[1] <pDoc->m_data.m_dLimitMaxBright[nCam] ){
// 			for(int i=0;i<500 ;i++){//1초 Ready
// 				for(int k=0;k<MAX_CAMERAS;k++)
// 					for(int j=0;j<8;j++)//8개의 Thread
// 						//if(m_bTest[k][j]==TRUE)
// 						if(m_bTestFlag[k][j]==FALSE)
// 							nComplete = 0;
// 				Wait(1);
// 				if(nComplete==0)break;
// 				nComplete = 1;
// 				if(m_nThreadcheck[nCam] == 1){
// 					m_nThreadcheck[nCam] = 0;
// 					CString strtmp11;
// 					strtmp11.Format("Line Error 2");
// 					if(nCam==1)
// 						AddtoInsLog(strtmp11);
// 					goto DONE;
// 					//return 0; 
// 				}
// 			}
// 			if(nComplete==1)
// 				m_nInspBreak[nCam] += 1000;
// 
// 		}
DONE:
		pDoc->m_data.m_dFullTime[nCam*10+7] = pDoc->m_data.m_dInspDetailTime[nCam][5] = GetPrecisionTime();
		if( m_nBrightcheck[1] == 1 && m_avgBrightness[1] < pDoc->m_data.m_dLimitMaxBright[nCam] ){
			if(nCam==1){
				m_nBrightcheck[0]=m_nBrightcheck[1]=m_nBrightcheck[2] = 0;
				m_nAlarmEndFRame = 0;
				m_bAlarmOnOff = FALSE;
				m_IO[0].WriteOutputPort(0,0,FALSE);

				AddtoList("Product Change2 Off",0,TRUE);

				SetTimer(12011,2000,NULL);//redraw invalidate
				for(int n1 =0;n1<10;n1++)
					for(int k1 =0;k1<MAX_LENGTH;k1++)
						pDoc->m_data.m_dLineAve[n1][k1] = 0;

				for(int k1=0;k1<MAX_CAMERAS;k1++)
					for(int k2=0;k2<40;k2++)
						pDoc->m_data.m_dOldLine[k1][k2] = 0;

			}
		}
		else if(nCam==2 && m_nSkipFrame[0] == pDoc->m_pDlgInterface->m_dSkipMeter+1){
			SetTimer(12011,2000,NULL);//redraw invalidate
		}
		if(m_avgBrightness[1] > pDoc->m_data.m_dLimitMaxBright[nCam] || pDoc->m_data.m_nWhiteLineCount[nCam]>pDoc->m_pDlgInterface->m_nSkipPixel){
			//			GetDlgItem(IDC_DETAIL_LINE)->Invalidate();
			m_nDisplayDraw = 1;
			m_nAlarmEndFRame = 0;
			m_bAlarmOnOff = FALSE;
			m_IO[0].WriteOutputPort(0,0,FALSE);
			AddtoList("Product Change3 Off",0,TRUE);

			for(int n1 =0;n1<10;n1++)
				for(int k1 =0;k1<MAX_LENGTH;k1++)
					pDoc->m_data.m_dLineAve[n1][k1] = 0;

			DrawImage(3);
			//io 추가 이재능 끄기
			m_IO[0].WriteOutputPort(0,2,FALSE);
		}
		else{
			{
				//io 추가 이재능  켜기
				m_IO[0].WriteOutputPort(0,2,TRUE);

				if(nCam==1) {//0번 카메라에서만 데이터를 취합한다.  //pDoc->m_data.m_dMisMatchLen[0][i] //pDoc->m_data.m_nMisMatchPixel[0][i]
					//절연이 끝났는지 체크한다
					if(m_nMachine == 0)InsulateDefectCheck();
					SummaryEdgeData();//pixel pos를 mm로 변환.여기서 텍스트 저장  라인에 대해서만 체크한다.
					if(m_nOldLine==-1){
						CString strtmp11;
						strtmp11.Format("Line Error 3");
						AddtoInsLog(strtmp11);
						return 0;
					}
					CString stttmp;
					stttmp.Format("%d Cam0 Summary",pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck]);

					//					AddtoInsLog(stttmp);
				}

				//불량 영상 저장 및 개별 텍스트 기록
				if(nCam==1){//1번카메라에서 일괄적으로 이미지를 저장및 쉬프트 한다.
					int ntmp1 = DataResultSave(3);//nCam);//여기서 디펙이미지저장 //BroadCasting(bRet,cam);//서버가 없음.이거 필요없음. 
					UpdateControl();//불량 개수 업데이트 
				}

				pDoc->m_data.m_dFullTime[nCam*10+8] = pDoc->m_data.m_dInspDetailTime[nCam][6] = GetPrecisionTime();

				if( nCam==1 ){
					CString stttmp;
					stttmp.Format("%d DrawImage1",pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck]);
					//					AddtoInsLog(stttmp);
					DrawImage(3);
				}
			}

			pDoc->m_data.m_dInspDetailTime[nCam][7] = GetPrecisionTime();
			
			pDoc->m_data.m_dInspTime[cam]=dInsTime = pDoc->m_data.m_dInspDetailTime[nCam][7]-pDoc->m_data.m_dInspDetailTime[nCam][0];
		}

		//Buffer copy Time5
		if(nCam==1){
			m_nSkipFrame[0]++;
			m_nSkipFrame[1]=m_nSkipFrame[2]=m_nSkipFrame[0];
			if(pDoc->m_pDlgInterface->m_bLastData)
				m_DlgLastData->LastDataShow(m_strLastNonCoatWidth,m_strLastCoatWidth);

			CString strtime;//reverse X 50ms소요 ,,,, memcpy 8ms
 			strtime.Format("%d-Time %.0f, %.0f, %.0f",pDoc->m_nTotalIns[0],pDoc->m_data.m_dInspTime[0]*1000,pDoc->m_data.m_dInspTime[1]*1000,pDoc->m_data.m_dInspTime[2]*1000);
 			AddtoInsLog(strtime);
 			strtime.Format("WPixel %d, %d, %d",pDoc->m_data.m_nWhiteLineCount[0],pDoc->m_data.m_nWhiteLineCount[1],pDoc->m_data.m_nWhiteLineCount[2]);
 			AddtoInsLog(strtime);
 			strtime.Format("%dLine %d, %d, %d  - %s",pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck],pDoc->m_data.m_nLineCount1[0],pDoc->m_data.m_nLineCount1[1],pDoc->m_data.m_nLineCount1[2],m_strLotID);
 			AddtoInsLog(strtime);
			CString strtmp1,strtmp2="";
			for(int i=0;i<pDoc->m_data.m_nNewLineCount;i++){
				strtmp1.Format("%d : %.2f \t",i+1,pDoc->m_data.m_dNewLineEdgeData1[i]);
				strtmp2 += strtmp1;
			}
			strtime.Format("Pixel %s",strtmp2);
//			AddtoInsLog(strtime);

			if(	m_nInspBreak[0]||m_nInspBreak[1]||m_nInspBreak[2]){
				strtime.Format("%dTimeOut %d, %d, %d",pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck],	m_nInspBreak[0],m_nInspBreak[1],m_nInspBreak[2]);
				AddtoInsLog(strtime);
			}


 			BOOL bAnode = TRUE;
// 
//  			if(pDoc->m_data.m_strComName.Mid(7,1)=="A"){
// 				strtmp2 = "";
//  				for(int i=0;i<pDoc->m_data.m_nInsulateCount;i++){
//  					strtmp1.Format("%d : %.2f \t",i+1,pDoc->m_data.m_rtinsulate1[i].Width()*pDoc->m_data.m_dScaleFactorX[0]);
//  					strtmp2 += strtmp1;
//  				}
//  				strtime.Format("Insulate %s",strtmp2);
//  				AddtoInsLog(strtime);
//  			}

// 			int n1 = 92,n2=91;
// 			strtime.Format("Time %.0f, %.0f, %.0f",(m_dDebugTime[nCam][n1]-m_dDebugTime[nCam][n2])*1000,(m_dDebugTime[nCam][n1]-m_dDebugTime[nCam][n2])*1000,(m_dDebugTime[nCam][n1]-m_dDebugTime[nCam][n2])*1000);
// 			AddtoInsLog(strtime);
// 
			///////////////////여기서 알람 전체 관리
			if(m_bAlarmOff==FALSE && pDoc->m_pDlgInterface->m_bAlarm && m_nAlarmEndFRame > pDoc->m_nTotalIns[nCam] ){
				if(m_bNewAlarm && m_nNewAlarm>0){
					m_strAlarmMsg = "Mismatch";
					m_strAlarmMsg1.Format("%d M", pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck]) ;

					CString stralarm;
					stralarm.Format("Spec Alram On %d",m_nAlarmLog);//0 폭 /
					AddtoList(stralarm,0,TRUE);
					m_nAlarmOn = 1;
					if(m_AlarmDlg->IsWindowVisible()){
					}
					else{
						m_nAlarmCnt1 = 0;
						m_AlarmDlg->ShowWindow(1);
						SetTimer(20218,500,NULL);
					}
				}
				else{
					//nMeter =pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck]
					m_nNewAlarm = 0;
					m_IO[0].WriteOutputPort(0,0,TRUE);
					CString stralarm;
					stralarm.Format("Alarm On %d",m_nAlarmLog);//0 폭 /
					AddtoList(stralarm,0,TRUE);
					m_nAlarmOn = 1;
					m_AlarmDlg->ShowWindow(1);
					SetTimer(20219,500,NULL);
				}
			}
			else{
				KillTimer(20219);
				m_nNewAlarm = 0;
				m_strAlarmMsg = "";
				m_strAlarmMsg1= "" ;

				m_nAlarmEndFRame = 0;
				m_bAlarmOnOff = FALSE;
				m_bNewAlarm = FALSE;
				KillTimer(20218);
				if(m_nAlarmOn==1)
					AddtoList("Alarm Off",0,TRUE);
				m_IO[0].WriteOutputPort(0,0,FALSE);
				m_nAlarmOn = 0;
				m_AlarmDlg->ShowWindow(0);

			}
			if(m_strComputerName.Mid(8,1)=="M" ){
				if(m_pMeterData->IsWindowVisible()){
					CString str;
					int nlen1 = pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck];
					int nc12 = 0;
					for(int i=nlen1-5;i<nlen1+5;i++){
						if(nc12>10)break;
						int ntmplen = ((i+1000) - pDoc->m_pDlgInterface->m_nHeadMisDistance)%100;
						CString strtmp14;
						strtmp14.Format("%d - %s",i,pDoc->m_data.m_strFullLineData[ntmplen]);
						m_pMeterData->m_lbMeterData[nc12%10].SetText(strtmp14);
						nc12++;

					}
				}
			}
		}

		//save전 flag 초기화
		m_bWaitThread[nCam]=FALSE;
		for(int i=0;i<6;i++)	for(int j=0;j<CAM_WIDTH_CIS;j++)		m_nLineProjData[i][j] = 0;

		memset(m_Inspect.m_fmPreprocess[nCam],0,CAM_WIDTH_CIS*CAM_HEIGHT_3072);
		//ljn 190401
		if(m_strLotID != "NONE"){
			if(pDoc->m_pDlgInterface->m_bFullImageSave ){
				if(nCam==0){
					m_eSaveImageCam2.SetEvent();m_eSaveImageCam3.SetEvent();m_eSaveImage.SetEvent();
				}
			}
			else if(m_nResultOkNg==1 && nCam==1)//불량 영상만 저장 //3개 셋트로 저장
			{
				m_eSaveImageCam2.SetEvent();
				m_eSaveImageCam3.SetEvent();
				m_eSaveImage.SetEvent();
			}
		}

		m_nThreadcheck[nCam] = 0;
		m_bTestInspect[nCam]= FALSE;
		return bRet;
	}

	catch(...){
		//m_Inspect.fnWriteFile(m_methodName + "Exception", nCam);
	}
}

int	CVisWebView::FindInsulate()
{
	//절연 폭검사  무지영역에서만 검사
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	int nGap = 10;
	int nMaxV[10][10],nPos[10][10];
	for(int k=0;k<10;k++)for(int l=0;l<10;l++){nMaxV[k][l]=nPos[k][l]=0;}
	//절연의 위치를 찾기 위해 무지 왼쪽의 10픽셀 무지 우측 10픽셀의 평균을 구하여 더 낮은 쪽이 무지임

	int nOffset = 20,nOffset1=10;//코팅 튐으로 인한 과검 축소 offset 만큼 건너뛰고 offset1만큼 평균 구하기
	int nLeftSum = 0,nRightSum=0;

	int nMininmunV = 7;

	//절연 유무 검사
	//무지내 좌/우 밝기 차가 일정값 이상일 차이가 날경우만 절연으로 인식.
	int nLeftRightV = 10;

	double dInsulAve = 0,dc1=0;
	for(int i=0;i<pDoc->m_data.m_nInsulateCount;i++){
		pDoc->m_data.m_dInsulatePos[i] = 0;
		nLeftSum =nRightSum=0;
		for(int k=0;k<10;k++)for(int l=0;l<10;l++){nMaxV[k][l]=nPos[k][l]=0;}
		for(int x=pDoc->m_data.m_rtinsulate[i].left+nGap;x<pDoc->m_data.m_rtinsulate[i].right-nGap;x++){
			dInsulAve += pDoc->m_data.m_nFullImageProj[x] ;
			dc1++;
			int nTmp = abs(pDoc->m_data.m_nFullImageProj[x] - pDoc->m_data.m_nFullImageProj[x+4]);
			int nTmp1 = abs(pDoc->m_data.m_nFullImageProj[x] - pDoc->m_data.m_nFullImageProj[x+2]);
			int nTmp2 = abs(pDoc->m_data.m_nFullImageProj[x] - pDoc->m_data.m_nFullImageProj[x+6]);

			if(x>=pDoc->m_data.m_rtinsulate[i].left+nOffset&& x<pDoc->m_data.m_rtinsulate[i].left+nOffset+nOffset1)
				nLeftSum+=pDoc->m_data.m_nFullImageProj[x];
			if(x>=pDoc->m_data.m_rtinsulate[i].right-nOffset-nOffset1&& x<pDoc->m_data.m_rtinsulate[i].right-nOffset)
				nRightSum+=pDoc->m_data.m_nFullImageProj[x];
			int nMag = 1;
			if(pDoc->m_data.m_nFullImageProj[x]<pDoc->m_data.m_nFullImageProj[x+4])nMag=0;
			if(nTmp>nMininmunV&&nMaxV[i][0]<nTmp){nMaxV[i][0] = nTmp;nPos[i][0]=x+(4*nMag);}
			if(nTmp>nMininmunV&&nMaxV[i][1]<nTmp1){nMaxV[i][1] = nTmp1;nPos[i][1]=x+(2*nMag);}
			if(nTmp>nMininmunV&&nMaxV[i][2]<nTmp2){nMaxV[i][2] = nTmp2;nPos[i][2]=x+(6*nMag);}
			
//			TRACE("%d, %d, %d, %d, %d\n",i, x,nTmp,nTmp1,nTmp2);
		}

		if(dc1>0)
			dInsulAve /= dc1;
		if(dInsulAve > 200){
			pDoc->m_data.m_rtinsulate1[i].SetRect(0,0,0,0);
			return -1;
		}
// 		double dinsul=0;
// 		for(int k2=1;k2<3;k2++){
// 			if(nPos[i][k2-1]<nPos[i][k2-1]);
// 		}
//		pDoc->m_data.m_dInsulatePos[i] = (nPos[i][0]+nPos[i][1]+nPos[i][2])/3;
		pDoc->m_data.m_dInsulatePos[i] = (nPos[i][0]);//+nPos[i][1]+nPos[i][2])/3;
		nLeftSum /= nOffset1;nRightSum/=nOffset1;
		if(abs(nLeftSum - nRightSum)<nLeftRightV){
			pDoc->m_data.m_rtinsulate1[i].SetRect(0,0,0,0);
			return -1;
		}
		if(nLeftSum>nRightSum){
			pDoc->m_data.m_rtinsulate1[i].SetRect(pDoc->m_data.m_dInsulatePos[i],0,pDoc->m_data.m_rtinsulate[i].right,CAM_HEIGHT_CIS);
		}
		else{
			pDoc->m_data.m_rtinsulate1[i].SetRect(pDoc->m_data.m_rtinsulate[i].left,0,pDoc->m_data.m_dInsulatePos[i],CAM_HEIGHT_CIS);
		}
	}
	return 0;

}

int CVisWebView::InsulateDefect(int nCam,int nIndex,int nHeight,int nMod)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	int ndivide = nHeight/nMod;
	int nmaxy1 = ndivide*nIndex,nmaxy2 = ndivide*(nIndex+1);
	int nmaxx1 = 0,nmaxx2 = CAM_WIDTH_CIS*3;
	int nMod1 = pDoc->m_data.m_nLineReduce,nWhTh = 200,nwhitecnt=0;
	int nInsulateValue = pDoc->m_pDlgInterface->m_nInsulateTh;//30

	int nInsulate = pDoc->m_data.m_nInsulateCount;
	int nDefect = 0;
	CRect rtPos[40];
	CRect rtdefect[50],rtsize[50];
	int defectx = BAD_IMG_WIDTH*0.5;
	int defecty = BAD_IMG_HEIGHT*0.5;
	for(int j=0;j<MAX_REALDEFECT;j++)pDoc->m_data.m_rectDefectInsulate1[nInsulate][j].SetRect(0,0,0,0);
	pDoc->m_data.m_nDefectInsulate1[nIndex] = 0;

	for(int i=0;i<40;i++)
		rtPos[i].SetRect(0,0,0,0);
	int nJump = 0;


	for(int k=0;k<nInsulate;k++){
		CRect rt1;
		rt1 = pDoc->m_data.m_rtinsulate1[k];
		rt1.InflateRect(-8,0);
		for(int y=nmaxy1;y<nmaxy2;y++){
			for(int x=rt1.left;x<rt1.right;x++){
				int ntmp = *(m_Inspect.m_FullImage + y*(CAM_WIDTH_CIS*3)+x)-pDoc->m_data.m_nFullImageProj[x];
				if(ntmp > nInsulateValue )//전체 Projection  백색 이물만 잡는다
				{//불량
 					for(int nn=0;nn<nDefect;nn++){
 						if(x>rtPos[nn].left && x<rtPos[nn].right && y>rtPos[nn].top&& y<rtPos[nn].bottom){
 							nJump = 1;
 							if(nJump){
 								x+= 64;
 								break;;
 							}
 						}
 					}
 					if(nJump==1)continue;
 					rtdefect[nDefect].SetRect(x-defectx,y-defecty,x+defectx,y+defecty);
 					CRect rttmp;
					rttmp = rtdefect[nDefect];
					rttmp = m_Inspect.SetBoundary1(rttmp,CRect(0,1,CAM_WIDTH_CIS*3,CAM_HEIGHT_CIS));
					pDoc->m_data.m_rectDefectInsulate1[nIndex][nDefect] = rttmp;
 
// 					rtdefect[nDefect] = m_Inspect.SetBoundary1(rtdefect[nDefect],CRect(rtInspect[k].left,1,rtInspect[k].right,CAM_HEIGHT_CIS-1));
 					//						rtsize[nDefect] = CheckDefect1(nCam,fm,pData,rtdefect[nDefect],nDefect,0,0,nWth2,&nPeak1,&nPeak2,&nAverage);//npos 0 무지 1코팅
// 					rtsize[nDefect] = m_Inspect.CheckDefect2(nCam,m_Inspect.m_FullImage,pDoc->m_data,rtdefect[nDefect].left,rtdefect[nDefect].right,rtdefect[nDefect].top,rtdefect[nDefect].bottom,nIdx,nDefect,0,0,nWth2,&nPeak1,&nPeak2,&nAverage);//npos 0 무지 1코팅
//  					if(rtInspect[k].left>rttmp.left||rtInspect[k].right<rttmp.right)rtdefect[nDefect] = rttmp;
//  					if((rtsize[nDefect].Width()+1)*dscalex>pData->m_dThSize[0] || (rtsize[nDefect].Height()+1)*dscaley>pData->m_dThSize[0]){
//  						//							ImageSelectCopy2(pImage->GetImagePtr(),pData->m_pImageDefect1[nCam][nDefect]->GetImagePtr(),CAM_WIDTH_CIS,CAM_HEIGHT_CIS,rttmp.left,rttmp.right,rttmp.top,rttmp.bottom,BAD_IMG_WIDTH,BAD_IMG_HEIGHT,0,0);
//  						pData->m_rtThreadDefect[nCam][nIdx][nDefect] = rtdefect[nDefect];
//  						pData->m_rtThreadSizeDefect[nCam][nIdx][nDefect] = rtsize[nDefect];
//  						pData->m_nNewDefectColor[nCam][nIdx][nDefect] = 1;////0 init 1Black	2White	3LineBlack	4LineWhite
//  						pData->m_nThreadDefectCount[nCam][nIdx]++;
//  						rtPos[nDefect] = rtdefect[nDefect];
//  						nDefect++;
//  					}
					rtPos[nDefect] = rttmp;//rtdefect[nDefect];
 					x+= 64;
					nDefect++;
					pDoc->m_data.m_nDefectInsulate1[nIndex]++;
					if(nDefect >= MAX_REALDEFECT-1) return 0;
 				}
				if(nDefect >= MAX_REALDEFECT-1) return 0;
			}
			if(nDefect >= MAX_REALDEFECT-1) return 0;
		}
		if(nDefect >= MAX_REALDEFECT-1) return 0;
	}
	m_bInsulateDefect[nIndex] = FALSE;

	return 0;
}

int CVisWebView::InsulateDefectCheck()
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	int ninsulate1 = 0;;
	for(int i=0;i<500 ;i++){//1초 Ready
		ninsulate1 = 0;
		for(int k=0;k<MOD_COUNT;k++)
			if(m_bInsulateDefect[k]==FALSE)ninsulate1++;
		Wait(1);
		if(ninsulate1>=MOD_COUNT)break;
	}
	ninsulate1 = 0;
	for(int k=0;k<MOD_COUNT;k++){
		if(pDoc->m_data.m_nDefectInsulate1[k]>0){
			ninsulate1 += pDoc->m_data.m_nDefectInsulate1[k];
			//							if(ninsulate1>= MAX_REALDEFECT-1)break;
			for(int l=0;l<pDoc->m_data.m_nDefectInsulate1[k] ;l++){
				pDoc->m_data.m_rectDefectInsulate[pDoc->m_data.m_nInsulateDefectCount] = pDoc->m_data.m_rectDefectInsulate1[k][l];
				CRect rt;
				rt = pDoc->m_data.m_rectDefectInsulate[pDoc->m_data.m_nInsulateDefectCount];
				//image select copy
				m_Inspect.ImageSelectCopy2(m_Inspect.m_FullImage,pDoc->m_data.m_pImageDefectInsulate[pDoc->m_data.m_nInsulateDefectCount]->GetImagePtr(),CAM_WIDTH_CIS*3,CAM_HEIGHT_CIS,rt.left,rt.right,rt.top,rt.bottom,BAD_IMG_WIDTH,BAD_IMG_HEIGHT,0,0);
				pDoc->m_data.m_nInsulateDefectCount++;
				if(pDoc->m_data.m_nInsulateDefectCount>= MAX_REALDEFECT-1)break;
			}
		}
		if(pDoc->m_data.m_nInsulateDefectCount>= MAX_REALDEFECT-1)break;
	}
	return 0;
}

//LC400000	//B
//LC200000 //A

//LC600000 //Total

void CVisWebView::OnBnClickedCheckInsul()
{//m_bInsulateInspect
	UpdateData();
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	if(m_bInsulateInspect){
		pDoc->m_pDlgInterface->OnBnClickedButton11();
		pDoc->m_data.m_nCoatBright = pDoc->m_pDlgInterface->m_nCoatBright;


	}
	else{

		pDoc->m_pDlgInterface->OnBnClickedButton10();
		pDoc->m_data.m_nCoatBright = pDoc->m_pDlgInterface->m_nCoatBrightDefault;

	}
	pDoc->m_pDlgInterface->m_bInsulate = m_bInsulateInspect;
	pDoc->m_data.m_bInsulateInspect = m_bInsulateInspect;
	pDoc->m_pDlgInterface->UpdateData(FALSE);
	Invalidate();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CVisWebView::LightChange(int n)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	if(n==1)
	{		pDoc->m_pDlgInterface->OnBnClickedButton11();

	}
	else{

		pDoc->m_pDlgInterface->OnBnClickedButton10();
	}

}
void CVisWebView::DataDraw(CPoint pt1,CPoint pt2,CString str,int nLineWidth, COLORREF lColor,BOOL bRect,int ncount)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CClientDC cdc(this);
 	CPen pen,*pOldPen,pen1;
 	pen.CreatePen(PS_SOLID,nLineWidth, lColor);
 	pOldPen = (CPen*)cdc.SelectObject(&pen);

	CFont font,*pOldFont;
	font.CreatePointFont(nLineWidth,_T("휴먼둥근헤드라인"));
	pOldFont=(CFont*)cdc.SelectObject(&font);


//	
	cdc.SetTextColor(lColor);//
	cdc.TextOut(pt1.x,pt1.y,str);
//	cdc.DrawText(str,)
// 	CRect rt;
// 	rt.SetRect(pt.x,pt.y,pt.x+200,pt.y+200);
// 	cdc.DrawText(str,rt,DT_LEFT);

	if(bRect==FALSE){
		pen1.CreatePen(PS_SOLID,2, COLOR_BLUE);
		pOldPen = (CPen*)cdc.SelectObject(&pen1);

		cdc.MoveTo(pt1.x, pt1.y);
		cdc.LineTo(pt2.x, pt1.y);
		cdc.LineTo(pt2.x, pt2.y);
		cdc.LineTo(pt1.x, pt2.y);
		cdc.LineTo(pt1.x, pt1.y);

	}

	cdc.SelectObject(pOldPen);
	cdc.SelectObject(pOldFont);
	

}
void CVisWebView::DataDraw1(CRect rt,CString str,int nLineWidth, COLORREF lColor,BOOL bRect)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CClientDC cdc(this);
	CPen pen,*pOldPen,pen1;
	pen.CreatePen(PS_SOLID,nLineWidth, lColor);
	pOldPen = (CPen*)cdc.SelectObject(&pen);

	CFont font,*pOldFont;
	font.CreatePointFont(nLineWidth,_T("휴먼둥근헤드라인"));
	pOldFont=(CFont*)cdc.SelectObject(&font);


	//	
	cdc.SetTextColor(lColor);//
//	cdc.TextOut(pt1.x,pt1.y,str);
	cdc.DrawText(str,rt,DT_CENTER);
	//	cdc.DrawText(str,)
	// 	CRect rt;
	// 	rt.SetRect(pt.x,pt.y,pt.x+200,pt.y+200);
	// 	cdc.DrawText(str,rt,DT_LEFT);

	if(bRect==FALSE){
		pen1.CreatePen(PS_SOLID,2, COLOR_BLUE);
		pOldPen = (CPen*)cdc.SelectObject(&pen1);

		cdc.MoveTo(rt.left, rt.top);
		cdc.LineTo(rt.right,rt.top);
		cdc.LineTo(rt.right,rt.bottom);
		cdc.LineTo(rt.left,rt.bottom);
		cdc.LineTo(rt.left,rt.top);

	}

	cdc.SelectObject(pOldPen);
	cdc.SelectObject(pOldFont);


}

//무지와 절연을 다씀
void CVisWebView::DrawRectangle1(CDC *pDC, CPoint p1, CPoint p2, CPoint p3, COLORREF lColor, int nLineWidth,int nCam,int nCount,CString strmm,CString strinsul)
{
	int nTest = 0;
	if(nCount>= MAX_LENGTH-2) return;
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CPen pen,*pOldPen;
	pen.CreatePen(PS_SOLID,nLineWidth, lColor);
	pOldPen = (CPen*)pDC->SelectObject(&pen);
	CBrush brush;
	brush.CreateSolidBrush(lColor );     // 오렌지색 채움색을 생성
	CBrush* oldBrush = pDC->SelectObject( &brush );
	//X point만 사용한다.
	p1 = Scale(p1,nCam);
	p2 = Scale(p2,nCam);
	CRect rcDest,rcMain,rtRect,rctitle,rcLength,rcview;
	GetWindowRect(rcMain);
/*	if(!pDoc->m_pDlgInterface->m_bImageShowHide && m_bDrawCheck==TRUE){
		m_bDrawCheck = FALSE;
		GetDlgItem(IDC_DETAIL_LINE)->GetWindowRect(rcDest);
		GetDlgItem(IDC_DISPLAY)->GetWindowRect(rcview);
		GetDlgItem(IDC_DETAIL_LINE)->MoveWindow(rcDest.left,rcview.top+220,rcDest.Width(),rcDest.Height());
		GetDlgItem(IDC_DETAIL_LINE)->GetWindowRect(rcDest);
	}
	else*/{
		if(pDoc->m_pDlgInterface->m_bImageShowHide)
			GetDlgItem(IDC_DETAIL_LINE)->MoveWindow(m_rtDetailView);
		GetDlgItem(IDC_DETAIL_LINE)->GetWindowRect(rcDest);
	}
	GetDlgItem(IDC_STATIC_COAT_TITLE1)->GetWindowRect(rctitle);
	GetDlgItem(IDC_STATIC_COAT_LEN1)->GetWindowRect(rcLength);
	rcDest.OffsetRect(-rcMain.left,-rcMain.top);	
	p1.y = rcDest.top;	p2.y = rcDest.bottom;
	if(p3.x>0)p1  = p3;
	rtRect.SetRect(p1.x,p1.y,p2.x,p2.y);
//	if(lColor!=COLOR_BLACK)
	pDC->Rectangle(rtRect);

	//타이틀 쓰기
	CRect rtTitle,rtTol1,rtTol2;
	//		rtTitle.SetRect((p1.x+p2.x)*0.5 - rctitle.Width()*0.5,p1.y-rctitle.Height() - 100,(p1.x+p2.x)*0.5+ rctitle.Width()*0.5,p1.y - 100);//기존 길이 위에 표시
	int nOffsety1 = 130,noffsety2=150;
	if(nCount<1){
		rtTitle.SetRect(rcDest.left-0,p1.y-rctitle.Height() - 10,rcDest.left-0+ rctitle.Width(),p1.y - 10);//기존 길이 위에 표시
		m_lbCoatTitle[0].MoveWindow(rtTitle);
		m_lbCoatTitle[0].ShowWindow(1);

		rtTitle.SetRect(rcDest.left-0,p1.y-rctitle.Height() + nOffsety1,rcDest.left-0+ rctitle.Width(),p1.y +nOffsety1);//기존 길이 위에 표시
		m_lbCoatTitle[1].MoveWindow(rtTitle);
		m_lbCoatTitle[1].ShowWindow(1);

	}
	// 	사이즈
	int nXOffset1 = 20;
	if(nCount%2==0){//위에
		if(m_strComputerName.Mid(7,1)=="C" && m_bInsulateInspect){
			rtTitle.SetRect((p1.x+p2.x)*0.5 - rcLength.Width()*0.5+20-nXOffset1,p1.y-rcLength.Height() - 10,(p1.x+p2.x)*0.5+ rcLength.Width()*0.5+nXOffset1,p1.y - 10);
		}
		else{
			rtTitle.SetRect((p1.x+p2.x)*0.5 - rcLength.Width()*0.5+20-nXOffset1,p1.y-rcLength.Height() + 30,(p1.x+p2.x)*0.5+ rcLength.Width()*0.5+nXOffset1,p1.y - 10);
		}
		rtTol1.SetRect((p1.x+p2.x)*0.5 - rcLength.Width()*0.5,p1.y-rcLength.Height() - 60,(p1.x+p2.x)*0.5-rcLength.Width()*0.5+100,p1.y-rcLength.Height() - 10);
		rtTol2.SetRect((p1.x+p2.x)*0.5 - rcLength.Width()*0.5+140,p1.y-rcLength.Height() - 60,(p1.x+p2.x)*0.5- rcLength.Width()*0.5+240,p1.y-rcLength.Height() - 10);

 		if(m_nTextColor[nCount]==0)			m_lbCoatLen[nCount].SetTextColor(COLOR_BLACK);
 		else if(m_nTextColor[nCount]==1)	m_lbCoatLen[nCount].SetTextColor(COLOR_ORANGE);
		else if(m_nTextColor[nCount]==2){	m_lbCoatLen[nCount].SetTextColor(COLOR_RED);m_nResultOkNg = 1;}
		else{
			m_lbCoatLen[nCount].SetTextColor(COLOR_GRAY);
			pDC->MoveTo(m_ptLinePos[nCount][0]);pDC->LineTo(m_ptLinePos[nCount+1][1]);
			pDC->MoveTo(m_ptLinePos[nCount][1]);pDC->LineTo(m_ptLinePos[nCount+1][0]);
		}

		CRect rttmp,rttmp1;//rtTitle
		GetDlgItem(IDC_STATIC_GAPMISMATCH1)->GetWindowRect(rttmp);
		rttmp1.SetRect(rtTitle.left+50,rtTitle.top+390,rtTitle.left+50+rttmp.Width(),rtTitle.top+390+rttmp.Height());
		m_lbGapMisMatch[nCount+1].MoveWindow(rttmp1);
		m_lbGapMisMatch[nCount+1].ShowWindow(0);//여기 막음 모름
	}
	else{
		rtTitle.SetRect((p1.x+p2.x)*0.5 - rcLength.Width()*0.5-nXOffset1+10,p1.y-rcLength.Height() + noffsety2,(p1.x+p2.x)*0.5+ rcLength.Width()*0.5+nXOffset1,p1.y +noffsety2);
		rtTol1.SetRect((p1.x+p2.x)*0.5 - rcLength.Width()*0.5,p1.y-rcLength.Height() + noffsety2+ 145,(p1.x+p2.x)*0.5-rcLength.Width()*0.5+100,p1.y-rcLength.Height() +noffsety2+195);
		rtTol2.SetRect((p1.x+p2.x)*0.5 - rcLength.Width()*0.5+140,p1.y-rcLength.Height() + noffsety2+ 145,(p1.x+p2.x)*0.5- rcLength.Width()*0.5+240,p1.y-rcLength.Height() +noffsety2+195);


//		if(m_bUseLen[nCount])
		{
			if(!m_bUseLen[nCount]){
				m_lbCoatLen[nCount].SetTextColor(COLOR_GRAY);
				DrawXMark(pDC,m_ptLinePos[nCount][0],m_ptLinePos[nCount+1][1],m_ptLinePos[nCount][1],m_ptLinePos[nCount+1][0],COLOR_RED,4,nCount);
				ReturnWidthCheck(nCount);

			}
			else if(m_nTextColor[nCount]==0)			m_lbCoatLen[nCount].SetTextColor(COLOR_WHITE);
			else if(m_nTextColor[nCount]==1)	m_lbCoatLen[nCount].SetTextColor(COLOR_ORANGE);
			else if(m_nTextColor[nCount]==2){	m_lbCoatLen[nCount].SetTextColor(COLOR_RED);m_nResultOkNg = 1;}
			else{
				m_lbCoatLen[nCount].SetTextColor(COLOR_GRAY);
				DrawXMark(pDC,m_ptLinePos[nCount][0],m_ptLinePos[nCount+1][1],m_ptLinePos[nCount][1],m_ptLinePos[nCount+1][0],COLOR_RED,4,nCount);
				ReturnWidthCheck(nCount);

			}
		}
		m_lbCoatLen[nCount].MoveWindow(rtTitle);//rtRect
//		m_lbCoatLen[nCount].MoveWindow(rtRect);//rtRect
		m_lbCoatLen[nCount].SetText(strmm);
		m_lbCoatLen[nCount].ShowWindow(1);

		CRect rttmp,rttmp1;//rtTitle
		GetDlgItem(IDC_STATIC_GAPMISMATCH1)->GetWindowRect(rttmp);
		rttmp1.SetRect(rtTitle.left+50,rtTitle.top+270,rtTitle.left+rttmp.Width()+50,rtTitle.top+270+rttmp.Height());
		m_lbGapMisMatch[nCount+1].MoveWindow(rttmp1);
		m_lbGapMisMatch[nCount+1].ShowWindow(0);//여기막음 모름

	}
	if(nCount>=9) return;
	m_lPitchTol[nCount*2].MoveWindow(rtTol1);
	m_lPitchTol[nCount*2+1].MoveWindow(rtTol2);
	m_lPitchTol[nCount*2].ShowWindow(1);
	m_lPitchTol[nCount*2+1].ShowWindow(1);
	if(nTest==1){
		m_lbCoatLen[nCount].MoveWindow(rtTitle);
		m_lbCoatLen[nCount].SetText(strmm);
		m_lbCoatLen[nCount].ShowWindow(1);
	}
	else{
		//// 글자크기만큼의 보이지 않는 사각형 넣기
		pDoc->m_data.m_rtCoatChar[nCount] = rtTitle;//0124 폭 글자 영역
		pDoc->m_data.m_rtCoatChar[nCount].InflateRect(0,0,0,-30);
//		pDoc->m_data.m_rtCoatChar[nCount].OffsetRect(pDoc->m_nTotalIns[0],0);//0124 폭 글자 영역

		if(m_bInsulateInspect){
			//영역이 작아져야 함.
//			pDoc->m_data.m_rtCoatChar[nCount].InflateRect(0,0,0,-50);
			pDoc->m_data.m_rtInsulateChar[nCount]=pDoc->m_data.m_rtCoatChar[nCount];
			pDoc->m_data.m_rtInsulateChar[nCount].OffsetRect(0,pDoc->m_data.m_rtInsulateChar[nCount].Height()+5);
			pDoc->m_data.m_rtInsulateChar[nCount].bottom = pDoc->m_data.m_rtInsulateChar[nCount].top+50;
		}
		COLORREF lColor1;

//		if(m_bUseLen[nCount])
		{
			if(m_nTextColor[nCount]==0)			lColor1 = COLOR_BLACK;
			else if(m_nTextColor[nCount]==1)	lColor1 = COLOR_ORANGE;
			else if(m_nTextColor[nCount]==2)	lColor1 = COLOR_RED;
			else								lColor1 = COLOR_GRAY;
		}
		if(nCount%2==0){//위에  코팅일대는 기존것을 쓴다.
			if(strinsul == ""){
				if(m_bUseLen[nCount]==FALSE){
					DataDraw(pDoc->m_data.m_rtCoatChar[nCount].TopLeft(),pDoc->m_data.m_rtCoatChar[nCount].BottomRight(),strmm,400,COLOR_GRAY,1,nCount);
					DrawXMark(pDC,m_ptLinePos[nCount][0],m_ptLinePos[nCount+1][1],m_ptLinePos[nCount][1],m_ptLinePos[nCount+1][0],COLOR_RED,4,nCount);
					ReturnWidthCheck(nCount);

// 					pDC->MoveTo(m_ptLinePos[nCount][0]);pDC->LineTo(m_ptLinePos[nCount+1][1]);
// 					pDC->MoveTo(m_ptLinePos[nCount][1]);pDC->LineTo(m_ptLinePos[nCount+1][0]);
				}
				else if(m_bNGLen[nCount] == TRUE){
					DataDraw(pDoc->m_data.m_rtCoatChar[nCount].TopLeft(),pDoc->m_data.m_rtCoatChar[nCount].BottomRight(),strmm,400,lColor1,1,nCount);
					m_nResultOkNg = 1;
				}
				else									DataDraw(pDoc->m_data.m_rtCoatChar[nCount].TopLeft(),pDoc->m_data.m_rtCoatChar[nCount].BottomRight(),strmm,400,lColor1,1,nCount);//color_white
			}
			else{
//  				if(m_bUseLen[nCount]==FALSE)			DataDraw(pDoc->m_data.m_rtCoatChar[nCount].TopLeft(),pDoc->m_data.m_rtCoatChar[nCount].BottomRight(),strmm,450,COLOR_GRAY,1);
//  				else if(m_bNGLen[nCount] == TRUE)		DataDraw(pDoc->m_data.m_rtCoatChar[nCount].TopLeft(),pDoc->m_data.m_rtCoatChar[nCount].BottomRight(),strmm,450,COLOR_RED,1);
//  				else									DataDraw(pDoc->m_data.m_rtCoatChar[nCount].TopLeft(),pDoc->m_data.m_rtCoatChar[nCount].BottomRight(),strmm,450,COLOR_BLACK,1);//color_white
//  				if(m_bUseLen[nCount]==FALSE)			DataDraw(pDoc->m_data.m_rtInsulateChar[nCount].TopLeft(),pDoc->m_data.m_rtInsulateChar[nCount].BottomRight(),strinsul,350,COLOR_GRAY,1);
//  				else if(m_bNGLen[nCount] == TRUE)		DataDraw(pDoc->m_data.m_rtInsulateChar[nCount].TopLeft(),pDoc->m_data.m_rtInsulateChar[nCount].BottomRight(),strinsul,350,COLOR_RED,1);
//  				else									DataDraw(pDoc->m_data.m_rtInsulateChar[nCount].TopLeft(),pDoc->m_data.m_rtInsulateChar[nCount].BottomRight(),strinsul,350,COLOR_YELLOW,1);//color_white


				if(m_bUseLen[nCount]==FALSE){
					DataDraw1(pDoc->m_data.m_rtCoatChar[nCount],strmm,400,COLOR_GRAY,1);
// 					pDC->MoveTo(m_ptLinePos[nCount][0]);pDC->LineTo(m_ptLinePos[nCount+1][1]);
// 					pDC->MoveTo(m_ptLinePos[nCount][1]);pDC->LineTo(m_ptLinePos[nCount+1][0]);
					DrawXMark(pDC,m_ptLinePos[nCount][0],m_ptLinePos[nCount+1][1],m_ptLinePos[nCount][1],m_ptLinePos[nCount+1][0],COLOR_RED,4,nCount);
					ReturnWidthCheck(nCount);

				}
				else if(m_bNGLen[nCount] == TRUE){
					DataDraw1(pDoc->m_data.m_rtCoatChar[nCount],strmm,400,lColor1,1);
					m_nResultOkNg = 1;
				}
 				else									DataDraw1(pDoc->m_data.m_rtCoatChar[nCount],strmm,400,lColor1,1);//color_white
				if(m_bInsulateInspect){

 					if(m_bUseInSulate[nCount]==FALSE)		DataDraw1(pDoc->m_data.m_rtInsulateChar[nCount],strinsul,300,lColor1,1);
					else if(m_bNGLen[nCount] == TRUE){
						DataDraw1(pDoc->m_data.m_rtInsulateChar[nCount],strinsul,300,lColor1,1);
						m_nResultOkNg = 1;
					}
 					else									DataDraw1(pDoc->m_data.m_rtInsulateChar[nCount],strinsul,300,lColor1,1);//color_white
				}

			}
			//			DataDraw(rtTitle.TopLeft(),rtTitle.BottomRight(),strmm,450,COLOR_BLACK,1);
		}

	}


	if(!pDoc->m_pDlgInterface->m_bImageShowHide && m_bMismatchUse && (m_strComputerName.Find("BACK")>=0 ||  pDoc->m_data.m_strComName.Mid(9,1)=="B")){
		int noffsety3 = 430,noffsety4 = 160;
		int noffsetx1 = 0;
		if(nCount%2==0){//밑에
			rtTitle.SetRect((p1.x+p2.x)*0.5 - rcLength.Width()*0.5-noffsetx1,p1.y-rcLength.Height() - 10+noffsety3,(p1.x+p2.x)*0.5+ rcLength.Width()*0.5+noffsetx1,p1.y - 10+noffsety3-50);

		}
		else{
			rtTitle.SetRect((p1.x+p2.x)*0.5 - rcLength.Width()*0.5-noffsetx1,p1.y-rcLength.Height() + noffsety2+noffsety4,(p1.x+p2.x)*0.5+ rcLength.Width()*0.5+noffsetx1,p1.y +noffsety2+noffsety4-50);
		}
		m_lbCoatLenTop[nCount+2].MoveWindow(rtTitle);
		//		m_lbCoatLenTop[nCount].SetText(strmm);
		m_lbCoatLenTop[nCount+2].ShowWindow(1);

		m_lbTopTitle.ShowWindow(1);
		//m_lbMisMatchTitle.ShowWindow(1);
		if(nCount<1){
			rtTitle.SetRect(rcDest.left+0,p1.y-rctitle.Height() - 10+noffsety3-30,rcDest.left+0+ rctitle.Width(),p1.y - 10+noffsety3-50);//기존 길이 위에 표시
			m_lbCoatLenTop[0].MoveWindow(rtTitle);
			m_lbCoatLenTop[0].ShowWindow(1);

			rtTitle.SetRect(rcDest.left+0,p1.y-rctitle.Height() + noffsety2+noffsety4-30,rcDest.left+0+ rctitle.Width(),p1.y +noffsety2+noffsety4-50);//기존 길이 위에 표시
			m_lbCoatLenTop[1].MoveWindow(rtTitle);
			m_lbCoatLenTop[1].ShowWindow(1);
		}


	}

	//크기 쓰기

//	pDC->Rectangle(rtRect);

	pDC->SelectObject( oldBrush );
	pDC->SelectObject(pOldPen);
}
//
//
int CVisWebView::PreProcessing1(BYTE * fmsrc,BYTE * fmdst,int nCam,int nw,int nh,CRect rt,int nMag)
{//전체 영상 및 ROI
	//Projection Base 영상 Flat 처리
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	int    *nImageProjection=new int[nw];
	int nValue = 80, nTmp = 0,nCount=0,nMagnification = nMag;//128
	int x0=0,x1=nw,y0=0,y1=nh;
	if(rt.Width()>1){	x0 = rt.left;x1=rt.right;y0=rt.top;y1=rt.bottom;}
	for(int x=x0;x<x1;x++)		nImageProjection[x] =0;
	for(int y=y0;y<y1;y+=4){
		for(int x=x0;x<x1;x++)	nImageProjection[x] += *(fmsrc+nw*y+x);
		nCount++;
	}
	if(nCount==0){
		delete nImageProjection;		return -1;
	}
	for(int x=x0;x<x1;x++){
		nImageProjection[x] /= nCount;
	}
	for(int y=y0;y<y1;y++){
		for(int x=x0;x<x1;x++){
			nTmp = nValue + (*(fmsrc+nw*y+x)-nImageProjection[x])*nMagnification;
			if(nTmp<0) nTmp=0;
			if(x>1850)
				x= x;
			else if(nTmp>255) nTmp=255;
			*(fmdst+y*nw+x) = nTmp;
		}
	}
	delete nImageProjection;
	return 0;
}
int CVisWebView::PreProcessing11(BYTE * fmsrc,BYTE * fmdst,int nCam,int nw,int nh,int nIndex,int nMod,int nMag)
{//Patial 전처리
	//Projection Base 영상 Flat 처리
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	int    *nImageProjection=new int[nw];
	int nValue = 80, nTmp = 0,nCount=0,nMagnification = nMag;//128
	int x0=0,x1=nw;
	int y0 = (nh/nMod)*nIndex; 
	int y1 = (nh/nMod)*(nIndex+1); 
	for(int x=x0;x<x1;x++)		nImageProjection[x] =0;
	for(int y=y0;y<y1;y+=4){
		for(int x=x0;x<x1;x++)	nImageProjection[x] += *(fmsrc+nw*y+x);
		nCount++;
	}
	if(nCount==0){
		delete nImageProjection;		return -1;
	}
	for(int x=x0;x<x1;x++){
		nImageProjection[x] /= nCount;
	}
	for(int y=y0;y<y1;y++){
		for(int x=x0;x<x1;x++){
			nTmp = nValue + (*(fmsrc+nw*y+x)-nImageProjection[x])*nMagnification;
			if(nTmp<0) nTmp=0;
			else if(nTmp>255) nTmp=255;
			*(fmdst+y*nw+x) = nTmp;
		}
	}
	delete nImageProjection;
	return 0;
}

int CVisWebView::PreProcessing2(BYTE * fmsrc,BYTE * fmdst,int nCam,int nw,int nh,CRect rt,int nMag)
{//전체 영상 및 ROI
	//1차 미분 Base 영상 Flat 처리
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	int nValue = 80, nTmp = 0,nTmp2 = 0,nCount=0,nMagnification = nMag,nGap=4;//128
	int x0=0,x1=nw,y0=0,y1=nh;
	if(rt.Width()>1){	x0 = rt.left;x1=rt.right;y0=rt.top;y1=rt.bottom;}
	for(int y=y0;y<y1;y++){
		for(int x=x0;x<x1;x++){
			if(x>x1-nGap)	nTmp = abs(*(fmsrc+y*nw+x)-*(fmsrc+y*nw+x-nGap));
			else			nTmp = abs(*(fmsrc+y*nw+x)-*(fmsrc+y*nw+x+nGap));
			nTmp2 = nValue+nTmp*nMagnification;
			if(nTmp2>255)nTmp2 = 255;if(nTmp2<0)nTmp2=0;
			*(fmdst+y*nw+x) = nTmp2;
		}
	}
	return 0;
}
int CVisWebView::PreProcessing12(BYTE * fmsrc,BYTE * fmdst,int nCam,int nw,int nh,int nIndex,int nMod,int nMag)
{//patial
	//1차 미분 Base 영상 Flat 처리
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	int nValue = 80, nTmp = 0,nTmp2 = 0,nCount=0,nMagnification = nMag,nGap=4;//gap 만큼의 차이값으로 처리
	int x0=0,x1=nw;
	int y0 = (nh/nMod)*nIndex; 
	int y1 = (nh/nMod)*(nIndex+1); 
	int nLowcut = 5,nHighcut = 5;
	for(int y=y0;y<y1;y++){
		for(int x=x0;x<x1-nGap;x++){
// 			if(x>x1-nGap)	nTmp = abs(*(fmsrc+y*nw+x)-*(fmsrc+y*nw+x-nGap));
// 			else			nTmp = abs(*(fmsrc+y*nw+x)-*(fmsrc+y*nw+x+nGap));
			nTmp = abs(*(fmsrc+y*nw+x)-*(fmsrc+y*nw+x+nGap));
			if(nTmp<nHighcut)nMagnification = nMag*0.5;
			else nMagnification = nMag;
			nTmp2 = nValue+nTmp*nMagnification;
			if(nTmp2>255)nTmp2 = 255;if(nTmp2<0)nTmp2=0;
			*(fmdst+y*nw+x) = nTmp2;
		}
	}
	return 0;
}
int CVisWebView::PreProcessing3(BYTE * fmsrc,BYTE * fmdstblack,int nCam,int nw,int nh,CRect rt,int nMag)
{//전체 영상 및 ROI
	//ngap area 내에 가장 어두운 밝기로 치환
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	int nValue = 80, nTmp = 0,nTmp2 = 0,nCount=0,nMagnification = nMag,nGap=3;//gap 만큼의 영역의 밝기를 기준으로
	int x0=0,x1=nw,y0=0,y1=nh;
	if(rt.Width()>1){	x0 = rt.left;x1=rt.right;y0=rt.top;y1=rt.bottom;}
	for(int y=y0;y<y1-nGap;y++){
		if(y<y1-nGap){
			for(int x=x0;x<x1;x++){
				if(x<x1-nGap){//에지처리
					nTmp = nTmp2=255;
					for(int y2=y;y2<y+nGap;y2++){
						for(int x2=x;x2<x+nGap;x2++){
							nTmp = *(fmsrc+y2*nw+x2);
							if(nTmp<nTmp2){//가장 어두운값
								nTmp2 = nTmp;
							}
						}
					}
				}
				*(fmdstblack+y*CAM_WIDTH_CIS+x) = nTmp2;
			}
		}
		else	memcpy(fmdstblack+y*nw,fmdstblack+(y-1)*nw,nw);//에지 처리
	}
	return 0;
}
int CVisWebView::PreProcessing13(BYTE * fmsrc,BYTE * fmdstblack,int nCam,int nw,int nh,int nIndex,int nMod,int nMag)
{//patial
	//ngap area 내에 가장 어두운 밝기로 치환
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	int nValue = 80, nTmp = 0,nTmp2 = 0,nCount=0,nMagnification = nMag,nGap=3;//gap 만큼의 영역의 밝기를 기준으로
	int x0=0,x1=nw;
	int y0 = (nh/nMod)*nIndex; 
	int y1 = (nh/nMod)*(nIndex+1); 
	for(int y=y0;y<y1-nGap;y++){
		if(y<y1-nGap || y1 !=nh){//영상의 중간부분일때는 계속 진행한다.
			for(int x=x0;x<x1;x++){
				if(x<x1-nGap){//에지처리
					nTmp = nTmp2=255;
					for(int y2=y;y2<y+nGap;y2++){
						for(int x2=x;x2<x+nGap;x2++){
							nTmp = *(fmsrc+y2*nw+x2);
							if(nTmp<nTmp2){//가장 어두운값
								nTmp2 = nTmp;
							}
						}
					}
				}
				*(fmdstblack+y*CAM_WIDTH_CIS+x) = nTmp2;
			}
		}
		else{
			memcpy(fmdstblack+y*nw,fmdstblack+(y-1)*nw,nw);//에지 처리
		}
	}
	return 0;
}
int CVisWebView::PreProcessing4(BYTE * fmsrc,BYTE * fmdstwhite,int nCam,int nw,int nh,CRect rt,int nMag)
{//전체 영상 및 ROI
	//ngap area 내에 가장 어두운 밝기로 치환
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	int nValue = 80, nTmp = 0,nTmp2 = 0,nCount=0,nMagnification = nMag,nGap=3;//gap 만큼의 영역의 밝기를 기준으로
	int x0=0,x1=nw,y0=0,y1=nh;
	if(rt.Width()>1){	x0 = rt.left;x1=rt.right;y0=rt.top;y1=rt.bottom;}
	for(int y=y0;y<y1-nGap;y++){
		if(y<y1-nGap){
			for(int x=x0;x<x1;x++){
				if(x<x1-nGap){//에지처리
					nTmp = nTmp2=0;
					for(int y2=y;y2<y+nGap;y2++){
						for(int x2=x;x2<x+nGap;x2++){
							nTmp = *(fmsrc+y2*nw+x2);
							if(nTmp>nTmp2){//가장 어두운값
								nTmp2 = nTmp;
							}
						}
					}
				}
				*(fmdstwhite+y*CAM_WIDTH_CIS+x) = nTmp2;
			}
		}
		else	memcpy(fmdstwhite+y*nw,fmdstwhite+(y-1)*nw,nw);//에지 처리
	}
	return 0;
}
int CVisWebView::PreProcessing14(BYTE * fmsrc,BYTE * fmdstwhite,int nCam,int nw,int nh,int nIndex,int nMod,int nMag)
{//patial
	//ngap area 내에 가장 어두운 밝기로 치환
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	int nValue = 80, nTmp = 0,nTmp2 = 0,nCount=0,nMagnification = nMag,nGap=3;//gap 만큼의 영역의 밝기를 기준으로
	int x0=0,x1=nw;
	int y0 = (nh/nMod)*nIndex; 
	int y1 = (nh/nMod)*(nIndex+1); 
	for(int y=y0;y<y1-nGap;y++){
		if(y<y1-nGap || y1 !=nh){//영상의 중간부분일때는 계속 진행한다.
			for(int x=x0;x<x1;x++){
				if(x<x1-nGap){//에지처리
					nTmp = nTmp2=255;
					for(int y2=y;y2<y+nGap;y2++){
						for(int x2=x;x2<x+nGap;x2++){
							nTmp = *(fmsrc+y2*nw+x2);
							if(nTmp<nTmp2){//가장 어두운값
								nTmp2 = nTmp;
							}
						}
					}
				}
				*(fmdstwhite+y*CAM_WIDTH_CIS+x) = nTmp2;
			}
		}
		else{
			memcpy(fmdstwhite+y*nw,fmdstwhite+(y-1)*nw,nw);//에지 처리
		}
	}
	return 0;
}
/////////////////////////////////////////////////////////////////////
int CVisWebView::InlinePreProcessing(int nCam,int nIndex,int nMod)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	BYTE * fm;
	if(nCam==0)		fm = pDoc->m_pImage->GetImagePtr();
	else if(nCam==1)fm = pDoc->m_pImage1->GetImagePtr();
	else			fm = pDoc->m_pImage2->GetImagePtr();
	int nMag = 5;

//	PreProcessing11(fm,m_Inspect.m_fmPreprocess[nCam],nCam,CAM_WIDTH_CIS,CAM_HEIGHT_3072,nIndex,nMod,nMag);
	PreProcessing12(fm,m_Inspect.m_fmPreprocess[nCam],nCam,CAM_WIDTH_CIS,CAM_HEIGHT_3072,nIndex,nMod,nMag);
// 	if(nCam==0)
// 		PreProcessing11(fm,m_Inspect.m_fmPreprocess1,nCam,CAM_WIDTH_CIS,CAM_HEIGHT_3072,nIndex,nMod,nMag);
// 	else if(nCam==1)
// 		PreProcessing11(fm,m_Inspect.m_fmPreprocess2,nCam,CAM_WIDTH_CIS,CAM_HEIGHT_3072,nIndex,nMod,nMag);
// 	else
// 		PreProcessing11(fm,m_Inspect.m_fmPreprocess3,nCam,CAM_WIDTH_CIS,CAM_HEIGHT_3072,nIndex,nMod,nMag);


	return 0;
}

int CVisWebView::CheckPosition(int nLine)
{
	//올드 초기화를 언제 하나? Lot change시 ? 
	int nret = 0;
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	int nGap = 10;//pixel 단위

	if(m_nDisplayDraw==1){
		m_nDisplayDraw = 2;
		InvalidateRect(CRect(100,220,1800,700));
		AddtoList("Product change",0);
	}
	else if(nLine<3){
//		InvalidateRect(CRect(100,220,1800,700));
	}
	else if(nLine != m_nOldEdgeCount){
//		InvalidateRect(CRect(100,220,1800,700));
		CString str;
		str.Format("%d Line Incorrect %d - %d - %d",pDoc->m_nTotalIns[0],nLine,pDoc->m_data.m_nNewLineCount,m_nOldEdgeCount);
		AddtoList(str,0);
		m_nSaveNgCode = 1;
		m_eSaveImageCam2.SetEvent();m_eSaveImageCam3.SetEvent();m_eSaveImage.SetEvent();

	}
	else if(abs(pDoc->m_data.m_nFoilEdgeOld[0]-pDoc->m_data.m_nFoilEdge[0])>nGap ||abs(pDoc->m_data.m_nFoilEdgeOld[1]-pDoc->m_data.m_nFoilEdge[1])>nGap)//좌/우 젤 끝 에지 위치만 체크
	{
		InvalidateRect(CRect(100,220,1800,700));		
		AddtoList("Start Pos Change",0);
	}
	if(pDoc->m_nTotalIns[0]>10 && nLine == m_nOldEdgeCount && m_nLastLineCount[0]<20 && m_nLastLineCount[1]==0){//SC를 위한 조건 설정
		m_nLastLineCount[0]++;
	}
 	else
 		m_nLastLineCount[0] = 0;
	if(m_nLastLineCount[0]>=20){
		m_nLastLineCount[1] = nLine;
		//ROI SET //
		//무지는 건너뛰고 코팅에서만 찾는다.
		int ncnt1 = 0,nCamno=0,nx1=0,nx2=0,ncnt2=0,nCamno1=0;
		for(int i=0;i<nLine-1;i++){
			if(i==0)m_nLastLineCount[3] = pDoc->m_data.m_rtNewInspect[i].left;
			if(i%2==1){
				pDoc->m_data.m_rtScratch2[ncnt1] = pDoc->m_data.m_rtNewInspect[i];//m_nLastLineCount[2]
				pDoc->m_data.m_rtScratch2[ncnt1].InflateRect(-20,0);
				ncnt1++;
			}
		}
		m_nLastLineCount[2] = ncnt1;//코팅수
		CString strmsg;
		strmsg.Format("Data Set Coat : %d",ncnt1);
		AddtoList(strmsg,0,0);

	}


	if(pDoc->m_data.m_nNewLineCount>=2)
	m_nOldEdgeCount = pDoc->m_data.m_nNewLineCount;
	pDoc->m_data.m_nFoilEdgeOld[0] = pDoc->m_data.m_nFoilEdge[0];
	pDoc->m_data.m_nFoilEdgeOld[1] = pDoc->m_data.m_nFoilEdge[1];
	pDoc->m_data.m_nFoilEdge[0]=pDoc->m_data.m_nFoilEdge[1] = 0;

	return nret;
}

void CVisWebView::ChangeControlsLanguage( BOOL bLang /*= ENG*/ )
{
	if(bLang == ENG){			// 영어
		if(m_bAuto)
			SetDlgItemText(IDC_CHECK_AUTO,"STOP");		
		else
			SetDlgItemText(IDC_CHECK_AUTO,"START");


	SetDlgItemText(IDC_BUTTON_INTERFACE,"SETTING");
	SetDlgItemText(IDC_BUTTON_EXIT,"EXIT");
	SetDlgItemText(IDC_CHECK_ALARM_OFF, "Alarm OFF");
	SetDlgItemText(IDC_BT_ALARM_SET, "Recipe");
	SetDlgItemText(IDC_CHECK_INSUL, "Insulation");
	GetDlgItem(IDC_BUTTON_RESETIMAGE)->SetWindowText(_T("Image Reset"));
	GetDlgItem(IDC_CHECK_PRIMER)->SetWindowText(_T("PRIMER"));	
	
	


	}
	else if(bLang == KOR){		// 한글
		if(m_bAuto)
			SetDlgItemText(IDC_CHECK_AUTO, _T("검사중지"));
		else
			SetDlgItemText(IDC_CHECK_AUTO, _T("자동검사"));


	SetDlgItemText(IDC_BUTTON_INTERFACE,"셋팅");
	SetDlgItemText(IDC_BUTTON_EXIT,"종료");	
	SetDlgItemText(IDC_CHECK_ALARM_OFF, "알람 OFF");
	SetDlgItemText(IDC_BT_ALARM_SET, "알람설정");
	SetDlgItemText(IDC_CHECK_INSUL, "절연검사");

	GetDlgItem(IDC_BUTTON_RESETIMAGE)->SetWindowText(_T("이미지리셋"));
	GetDlgItem(IDC_CHECK_PRIMER)->SetWindowText(_T("프라이머"));
	
	}
}

void CVisWebView::DrawMismatch()
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	int nLinecnt[3] = {0,};//#define CAM_WIDTH_CIS	7296 //7320 //7296	 

	double nEdgeDataTop[20]={0,};
	double nEdgeDataBack[20]={0,};
	double nWidthDataTop[20]={0,};
	double nWidthDataBack[20]={0,};
	double dedgepitch[20] = {0,};
	//	double	m_dMisMatchData[4][10][MAX_LENGTH];//0 length 1 TOP 2BACK, 10frame, 20lane  /3 - length mismatch
	nLinecnt[0] =nLinecnt[1] =nLinecnt[2] = pDoc->m_data.m_nNewLineCount;
	if(pDoc->m_data.m_nNewLineCount>=8)
		m_defectMap->m_nTitleSize=40;
	else if(pDoc->m_data.m_nNewLineCount>=6)
		m_defectMap->m_nTitleSize=45;
	else	m_defectMap->m_nTitleSize=50;

	double dinterplation = 0;
	double doldpos=0,dcamscale = pDoc->m_data.m_dScaleFactorX[0];//.0423;

	if(dcamscale>0 && pDoc->m_pDlgInterface->m_bEdgeInterpolation){
		dinterplation = pDoc->m_data.m_dInterpolation/dcamscale;//픽셀 보상
	}
	pDoc->m_data.m_dInterpolationPixel = dinterplation;

	int nline = pDoc->m_data.m_nNewTopCount;
	if(m_strComputerName.Mid(9,1)=="T")
		nline = pDoc->m_data.m_nMismatchLine;
	if(pDoc->m_pDlgInterface->m_bMasterPc){
		nline = pDoc->m_data.m_nNewLineCount;
	}
	int nTest = 1;
	if(m_strComputerName.Mid(9,1) == "B"){
		int nmeter1 = (pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck])%METER_10;

		for(int i=0;i<nline;i++){//
			nEdgeDataTop[i] = pDoc->m_data.m_dDrawMisData[0][nmeter1][0][i];//top data
// 			if(pDoc->m_data.m_dMisTopBackData1[0][i]<=0)
// 				pDoc->m_data.m_dMisTopBackData1[0][i] = pDoc->m_data.m_dMisTopBackData1[0][i];
		}
		if(nline<=2)
			nline = nline;
		for(int i=0;i<nline;i++)//
			nEdgeDataBack[i] = pDoc->m_data.m_dDrawMisData[1][nmeter1][0][i];//back data
		for(int i=0;i<nline;i++)//
			dedgepitch[i] = pDoc->m_data.m_dDrawMisData[2][nmeter1][0][i];//back data
	}
	else{
		for(int i=0;i<nline;i++){//
			nEdgeDataTop[i] = pDoc->m_data.m_dMisTopBackData1[0][i];//top data
			nEdgeDataBack[i] = pDoc->m_data.m_dMisTopBackData1[1][i];//back data
			dedgepitch[i] = pDoc->m_data.m_dMisTopBackData1[2][i];//mis data
			nWidthDataTop[i] = pDoc->m_data.m_dMisTopBackData1[3][i];//top data
			nWidthDataBack[i] = pDoc->m_data.m_dMisTopBackData1[4][i];//back data
		}
	}
	//백이 위
	if(pDoc->m_pDlgInterface->m_bMasterPc){
		nline = pDoc->m_data.m_nNewLineCount;
		m_defectMap->DrawFullLine(nline,  nEdgeDataBack ,dedgepitch,nline,nEdgeDataBack ,dedgepitch,nline, dedgepitch,dedgepitch);//
	}
	else
		m_defectMap->DrawFullLine(nline,  nEdgeDataBack ,nWidthDataBack,nline,nEdgeDataTop ,nWidthDataTop,nline, dedgepitch,dedgepitch);//
}
void CVisWebView::ChangeTol2(BOOL bcheck, int nselect, CString str)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	//	if(bcheck){//공차
	int nn = 0;
	int nGap = 100;
	if(nselect<119){
		nselect -= 100;
		if(nselect>=10 && nselect<30){	//max 치 에디트 컨트롤 선택 시 (10~29)
			nn = (nselect-10)*2+1;
		}
		else if(nselect>30){

		}
		else{							//min 치 에디트 컨트롤 선택 시 (0~9) 
			nn = (nselect-1 )*2;
		}

		if(nselect<30){
			m_dTolerance1[nn] = atof(str);
			CString str1;
			if(nn%2==0)
				if(pDoc->m_pDlgInterface->m_bEngKor)
					str1.Format("MIN\n%s",str);
				else	
					str1.Format("최소\n%s",str);
			else
				if(pDoc->m_pDlgInterface->m_bEngKor)
					str1.Format("MAX\n%s",str);
				else
					str1.Format("최대\n%s",str);
	//		m_lPitchTol[nn].SetText(str1);
			// 	}
			// 	else{
			// 		int nn = nselect*0.5;
			// 		m_dStardLen[nn] = atof(str);
			// 		pDoc->m_pDlgInterface->m_dStandard[nn] = m_dStardLen[nn];
			// 		pDoc->m_pDlgInterface->UpdateData(FALSE);
			// 		pDoc->m_pDlgInterface->SaveSysParam();
			// 	}

			UpdateTolIni(pDoc->m_data.m_strDefaultModel,0);
			int nn1 = nselect;
			if(nn1%2==1)nn1 -= nn1;
			m_NumPad->LabelShow(nselect,0,0);
	//		m_NumPad->LabelShow(nselect,m_dTolerance1[nn1],m_dTolerance1[nn1+1]);
		}
		else{
			//		m_dTolerance[nn] = atof(str);
			CString str1;
			if(nselect==31){
				m_SysParam->m_dMismatchTolMin = m_dMismatchTolMin = atof(str);
				str1.Format("최소%s",str);	
				m_lbMismatchTolMin.SetText(str1);
			}
			else if(nselect==32){
				m_SysParam->m_dMismatchTolMax = m_dMismatchTolMax = atof(str);
				if(pDoc->m_pDlgInterface->m_bEngKor)
					str1.Format("MAX%s",str);		
				else
					str1.Format("최대%s",str);
				m_lbMismatchTolMax.SetText(str1);
			}
			else if(nselect==33){
				m_SysParam->m_dMismatchTolMin1 = m_dMismatchTolMin1 = atof(str);
				if(pDoc->m_pDlgInterface->m_bEngKor)
					str1.Format("MIN%s",str);	
				else
					str1.Format("최소%s",str);	
				// 			m_lbMismatchTolMin1.SetText(str1);
			}
			else if(nselect==34){
				m_SysParam->m_dMismatchTolMax1 = m_dMismatchTolMax1 = atof(str);
				if(pDoc->m_pDlgInterface->m_bEngKor)
					str1.Format("MIN%s",str);	
				else
					str1.Format("최소%s",str);	
				// 			m_lbMismatchTolMin1.SetText(str1);
			}
			else if(nselect==35){
				m_SysParam->m_dMismatchTolMin1 = m_dMismatchTolMin1 = atof(str);
				if(pDoc->m_pDlgInterface->m_bEngKor)
					str1.Format("MIN%s",str);	
				else
					str1.Format("최소%s",str);	
				// 			m_lbMismatchTolMin1.SetText(str1);
			}
			else{
				pDoc->m_pDlgInterface->m_nInsulateTh = atoi(str);
				if(pDoc->m_pDlgInterface->m_bEngKor)
					str1.Format("MAX%s",str);
				else
					str1.Format("최대%s",str);
				// 			m_lbMismatchTolMax1.SetText(str1);
			}

			UpdateTolIni(pDoc->m_data.m_strDefaultModel,0);

			m_NumPad->LabelShow1((nselect+1)%2,m_dMismatchTolMin,m_dMismatchTolMax);
		}
	}
	else{	//모디파이 값 설정 (119번 이상)
		if(nselect==128)
			m_SysParam->m_dMismatchModify = m_dMismatchModify = atof(str);
		else if(nselect==129)//foil min
			m_SysParam->m_dFoilSize[0] = m_dFoilSize[0] = atof(str);
		else if(nselect==130)//foil max
			m_SysParam->m_dFoilSize[1] = m_dFoilSize[1] = atof(str);
		else{
			nn = nselect - 119;
			m_dTolerance2[nn] = atof(str);
		}
		CString str1;
		nn=2;
		if(nn%2==0)
			if(pDoc->m_pDlgInterface->m_bEngKor)
				str1.Format("MIN\n%s",str);
			else	
				str1.Format("최소\n%s",str);
		else
			if(pDoc->m_pDlgInterface->m_bEngKor)
				str1.Format("MAX\n%s",str);
			else
				str1.Format("최대\n%s",str);
		//		m_lPitchTol[nn].SetText(str1);
		// 	}
		// 	else{
		// 		int nn = nselect*0.5;
		// 		m_dStardLen[nn] = atof(str);
		// 		pDoc->m_pDlgInterface->m_dStandard[nn] = m_dStardLen[nn];
		// 		pDoc->m_pDlgInterface->UpdateData(FALSE);
		// 		pDoc->m_pDlgInterface->SaveSysParam();
		// 	}

		UpdateTolIni(pDoc->m_data.m_strDefaultModel,0);
// 		int nn1 = nselect;
// 		if(nn1%2==1)nn1 -= nn1;
//		m_SysParam->UpdateData(FA)
		m_NumPad->LabelShow(nn,0,0);

	}

}

void CVisWebView::WriteLog2(CString str,int nCam)
{
	CTime time = CTime::GetCurrentTime();

	CString kk1 = time.Format("%Y%m");
	CString strpath,strData;
	strpath.Format("c:\\Glim\\Log\\");
	CreateDirectory(strpath,NULL);
	strpath.Format("c:\\Glim\\Log\\%s\\",kk1);
	CreateDirectory(strpath,NULL);

	CTime time1 = CTime::GetCurrentTime();
	strData = time1.Format("[%H:%M:%S]") + str;

	CString strFile;
	strFile.Format("%s%sCam%d_LOG_%s.txt",strpath,time.Format("%Y%m%d"),nCam+1,m_strComputerName);

	FILE *fp;
	fp = fopen((LPCSTR)strFile, "a");

	if(!fp)
		return;
	char* buf = new char[strData.GetLength()+1];
	memcpy(buf, strData.LockBuffer(), strData.GetLength());
	buf[strData.GetLength()] = '\0';

	fputs(buf, fp);
	fputs("\n",fp);
	delete []buf;
	fclose(fp);
}

int	CVisWebView::CheckCamera()
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	int nTmp=0,nTmp1 = 0;;
	int nCam = 0;
	int nmax = 0,ncnt1= 0;
	int nstart = 0;
	int nend = CAM_WIDTH_CIS*3;
	if(nstart <2300)nstart = 2300;//limit inspect range
	if(nend>CAM_WIDTH_CIS*3-2300)nend = CAM_WIDTH_CIS*3-2300;//limit inspect range
	m_nCamNoiseCheck = 0;
	for(int x=nstart;x<nend;x++){

		nTmp1 = abs(pDoc->m_data.m_nFullImageProj[x]-pDoc->m_data.m_nFullImageProj[x+2]);

		if(nTmp1>200)
			m_nCamNoiseCheck++;


	}
	return m_nCamNoiseCheck;
}
void CVisWebView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CFormView::OnPaint()을(를) 호출하지 마십시오.
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

// 	CDC MemDC;
// 	CBitmap* pOldBmp;
// 	CRect rtdraw;
// 	rtdraw.SetRect(100,100,1800,1000);
// 	MemDC.CreateCompatibleDC(&dc);
// 	pOldBmp = MemDC.SelectObject(&m_Bitmap);

	CRect rcDIB, rcDest,rcDest1,rcDest2;
	if(m_bViewTest)
		m_bViewTest = m_bViewTest;

	CRect rcDest3;


	if(m_bViewTest )
	{
		CRect rcMain;
		GetWindowRect(rcMain);
		//전체화면 이미지 사이즈
		GetDlgItem(IDC_DISPLAY)->GetWindowRect(rcDest);
		GetDlgItem(IDC_DISPLAY2)->GetWindowRect(rcDest1);
		GetDlgItem(IDC_DISPLAY3)->GetWindowRect(rcDest2);
		GetDlgItem(IDC_DEFECT_MAP)->GetWindowRect(rcDest3);

		rcDest.OffsetRect(-rcMain.left,-rcMain.top);	
		rcDest1.OffsetRect(-rcMain.left,-rcMain.top);	
		rcDest2.OffsetRect(-rcMain.left,-rcMain.top);	
		rcDest3.OffsetRect(-rcMain.left,-rcMain.top);


		static bool m_bFirst = true;
		if(m_bFirst){
			m_bFirst = false;
			GetDlgItem(IDC_DETAIL_LINE)->GetWindowRect(m_rtDetailView);
			m_rtDetailView.OffsetRect(-rcMain.left,-rcMain.top);
		}

		//m_defectMap->ShowWindow(SW_SHOW);
		{
			if(!pDoc->m_pImage->IsDataNull())
			{		
				rcDIB.top = 0;
				rcDIB.left = 0;
				rcDIB.right = pDoc->m_pImage->GetWidth();
				rcDIB.bottom = pDoc->m_pImage->GetHeight();

				double dScale = 1;

				pDoc->m_pImage->Draw(dc.m_hDC,&rcDIB,&rcDest);
				if(MAX_CAMERAS>1){
					pDoc->m_pImage1->Draw(dc.m_hDC,&rcDIB,&rcDest1);
				}
				if(MAX_CAMERAS>2){
					pDoc->m_pImage2->Draw(dc.m_hDC,&rcDIB,&rcDest2);
				}

			}
		}
	}
	DrawNGImage(&dc,m_nSelectCam);
	DrawData(&dc,m_nSelectCam);

// 	dc.BitBlt(0,0,rtdraw.right,rtdraw.bottom, &MemDC, 0,0,SRCCOPY);
// 
// 	MemDC.SelectObject(pOldBmp);
// 	MemDC.DeleteDC();
}



void CVisWebView::OnBnClickedBtnWidthData()
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	if(m_DlgLastData->IsWindowVisible()){
		m_DlgLastData->ShowWindow(SW_HIDE);
	}
	else
		m_DlgLastData->ShowWindow(SW_SHOW);
}

void CVisWebView::FolderInspect()
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CFile file;
	CString str,strng,strok;
	TCHAR	spath[100];
	BROWSEINFO bi;
	memset(&bi,0,sizeof(bi));
	bi.hwndOwner = GetSafeHwnd();

	bi.ulFlags=BIF_RETURNONLYFSDIRS;
	
	LPITEMIDLIST lpifq=SHBrowseForFolder(&bi);

	if(lpifq)
	{
		SHGetPathFromIDList(lpifq,spath);
		LPMALLOC lpMalloc=NULL;
		HRESULT hr = SHGetMalloc(&lpMalloc);
		if(SUCCEEDED(hr))
		{
			lpMalloc->Free(lpifq);
			lpifq = NULL;
			lpMalloc->Release();
			lpMalloc = NULL;
		}
	}
	else
	{
	}

	CString src, tar,strDevice;
	HANDLE hFind;				// FindFirstFile 핸들
	WIN32_FIND_DATA	fd;			// 검색한 화일의 정보
	BOOL bRet = TRUE;
	CString strfile;
	str = LPCTSTR(spath);
	str += "\\*.jpg";
	int ntmp =0;
	CString strMonth;

	bRet = TRUE;
	hFind = FindFirstFile( str, &fd);
	strDevice = strfile.Left(3);
	while(hFind != INVALID_HANDLE_VALUE && bRet)
	{			
		strfile.Format("%s\\%s", spath, fd.cFileName);
		CString str =strfile;

		if( !(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)  && strfile.Find("0.jpg")>0)		// Not directory, which means file.
		{
			CString str1,str2,strtmp,strpath,strname;
			strname =fd.cFileName;
			strpath = spath;
			int nfind = str.Find(".jpg");
			strtmp = str.Left(nfind-1);
			str1.Format("%s1.jpg",strtmp);
			str2.Format("%s2.jpg",strtmp);
			pDoc->m_pImage->Load(strfile);
			if(pDoc->m_pDlgInterface->m_bPreprocessing)			for(int idx=0;idx<MOD_COUNT;idx++)					m_bPreprocessing[0][idx] = TRUE;
			pDoc->m_pImage1->Load(str1);
			if(pDoc->m_pDlgInterface->m_bPreprocessing)	for(int idx=0;idx<MOD_COUNT;idx++)					m_bPreprocessing[1][idx] = TRUE;
			pDoc->m_pImage2->Load(str2);
			if(pDoc->m_pDlgInterface->m_bPreprocessing)	for(int idx=0;idx<MOD_COUNT;idx++)			m_bPreprocessing[2][idx] = TRUE;
			Wait(10);
			pDoc->m_data.m_dInspDetailTime[0][0] =pDoc->m_data.m_dInspDetailTime[1][0] =pDoc->m_data.m_dInspDetailTime[2][0] = GetPrecisionTime();

			memset(m_Inspect.m_FullImage,0,CAM_WIDTH_CIS*3*3072);

			double dt1 = GetPrecisionTime();
			for(int i=0;i<CAM_HEIGHT_CIS;i++)
				memcpy((m_Inspect.m_FullImage+CAM_WIDTH_CIS*(i*3)),pDoc->m_pImage->GetImagePtr()+CAM_WIDTH_CIS*i,CAM_WIDTH_CIS);
			double dt2 = GetPrecisionTime();
			for(int i=0;i<CAM_HEIGHT_CIS;i++)
				memcpy((m_Inspect.m_FullImage+CAM_WIDTH_CIS*(i*3)+CAM_WIDTH_CIS),pDoc->m_pImage1->GetImagePtr()+CAM_WIDTH_CIS*i,CAM_WIDTH_CIS);
			double dt3 = GetPrecisionTime();
			for(int i=0;i<CAM_HEIGHT_CIS;i++)
				memcpy((m_Inspect.m_FullImage+CAM_WIDTH_CIS*(i*3)+CAM_WIDTH_CIS*2),pDoc->m_pImage2->GetImagePtr()+CAM_WIDTH_CIS*i,CAM_WIDTH_CIS);
			m_bFullCopy[0] = m_bFullCopy[1] = m_bFullCopy[2] = TRUE;
			m_bTestInspect[0]=m_bTestInspect[1]=m_bTestInspect[2] = TRUE;
			//검사가 끝나는걸 기다린다.
			int ncnt = 0;
			while(1){
				if(!m_bTestInspect[0] && !m_bTestInspect[1] &&!m_bTestInspect[2])
					break;
				Wait(2);
				ncnt++;
				if(ncnt>=500)break;
			}
			m_strImgTestName = strfile;

// 			if(m_bImageSelect){
// 				if(ntmp==1){
// //					strng.Format("%s\\OK_%.0f_%.0f\\",spath,pDoc->m_data.m_dThUp,pDoc->m_data.m_dThDn); 
// //					CreateDirectory(strng,NULL);
// //					strng += fd.cFileName;
// //					pDoc->m_pImageNG->Save(strng);
// 				}
// 				else{
// 					strng.Format("%s\\NG_%.0f_%.0f\\",spath,pDoc->m_data.m_dThUp,pDoc->m_data.m_dThDn); 
// 					CreateDirectory(strng,NULL);
// 					strng += fd.cFileName;
// 					pDoc->m_pImageNG->Save(strng);
// 				}
// 				Wait(100);
// 			}
//		fnWriteResult(strfile,ntmp,strDevice,strMonth);//*/
			AddtoInsLog(strfile,0);
			if(!m_bAutoRun)	while( WaitForSingleObject((HANDLE)m_ev_rbutton_down, 100) != WAIT_OBJECT_0 ) Wait(1);
			else{
				Wait(300);
//				Wait(500);
			}
//			Wait(100);
		}
		else if( strfile == "." || strfile == "..")
		{
			// do nothing
		}
		else	// it is directory
		{
			// do nothing	choi-sh@koreno.co.kr
		}
		bRet= FindNextFile(hFind, &fd);
	}
	::FindClose(hFind);
	AfxMessageBox("Directory Inspect Complete!!!");	
}
int CVisWebView::CamCheckWD(void)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	int nCnt=0; 
	for(int i=ROLL_LEFT;i<ROLL_RIGHT;i++){				 
		if(abs(pDoc->m_data.m_nFullImageProj[i])>150)	//흰픽셀(150이상) 개수 체크 
			nCnt++; 	
	}
	//sharpness check
	//원단의 사작과 끝만체크하낟.

	int nsharpness = 0,nsum0=0,nc0=0,nmax0=0,nmax1=0;
	for(int j=0;j<CAM_HEIGHT_CIS;j+=8){
		nmax0 = 0;
		for(int i=pDoc->m_data.m_nCadidateEndpos-100;i<pDoc->m_data.m_nCadidateEndpos+100;i++){
			nsharpness = abs(*(m_Inspect.m_FullImage + j*(CAM_WIDTH_CIS*3)+i)-*(m_Inspect.m_FullImage + j*(CAM_WIDTH_CIS*3)+i+1))*10;
//			nsharpness = abs(pDoc->m_data.m_nFullImageProj[i]-pDoc->m_data.m_nFullImageProj[i+1]);
//			nsum0+=nsharpness;
			if(nmax0<nsharpness)nmax0 = nsharpness;
		}
		nmax1 += nmax0;
		nc0++;
	}

//	nsum0/=nc0;
	nmax1 /=  nc0;//(CAM_HEIGHT_CIS/8);

	pDoc->m_data.m_dSharpness1[0] = nmax1;
	if(nmax1>=pDoc->m_pDlgInterface->m_nCylinderCutValue){
		return 1;
	}
	else
		return 0;
	if(nCnt>500)	//정상, 올라간상태 카운트 비교해서 정할 것
		return 1; 
	else
		return 0; 
}

void CVisWebView::DrawXMark(CDC * pDC,CPoint p1,CPoint p2,CPoint p3,CPoint p4,COLORREF lColor, int nLineWidth,int nline)
{
	CPen pen,*pOldPen;
	pen.CreatePen(PS_SOLID,nLineWidth, lColor);
	pOldPen = (CPen*)pDC->SelectObject(&pen);
	if(nline>=0){
		pDC->MoveTo(m_ptLinePos[nline][0]);
		pDC->LineTo(m_ptLinePos[nline+1][1]);
		pDC->MoveTo(m_ptLinePos[nline][1]);
		pDC->LineTo(m_ptLinePos[nline+1][0]);

		pDC->MoveTo(m_ptLinePos1[nline][0]);
		pDC->LineTo(m_ptLinePos1[nline+1][1]);
		pDC->MoveTo(m_ptLinePos1[nline][1]);
		pDC->LineTo(m_ptLinePos1[nline+1][0]);

	}
	else{
		pDC->MoveTo(p1);
		pDC->LineTo(p2);
		pDC->MoveTo(p3);
		pDC->LineTo(p4);

	}


	pDC->SelectObject(pOldPen);

}
void CVisWebView::ReturnWidthCheck(int nLine)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	if(pDoc->m_pDlgInterface->m_bReturnTime){
		if(nLine==0 && m_nUsecheck[nLine] !=1)
			SetTimer(25151,1000*pDoc->m_pDlgInterface->m_nReturnTime,NULL);
		else if(nLine==1 && m_nUsecheck[nLine] !=1)
			SetTimer(25152,1000*pDoc->m_pDlgInterface->m_nReturnTime,NULL);
		else if(nLine==2 && m_nUsecheck[nLine] !=1)
			SetTimer(25153,1000*pDoc->m_pDlgInterface->m_nReturnTime,NULL);
		else if(nLine==3 && m_nUsecheck[nLine] !=1)
			SetTimer(25154,1000*pDoc->m_pDlgInterface->m_nReturnTime,NULL);
		else if(nLine==4 && m_nUsecheck[nLine] !=1)
			SetTimer(25155,1000*pDoc->m_pDlgInterface->m_nReturnTime,NULL);
		else if(nLine==5 && m_nUsecheck[nLine] !=1)
			SetTimer(25156,1000*pDoc->m_pDlgInterface->m_nReturnTime,NULL);
		else if(nLine==6 && m_nUsecheck[nLine] !=1)
			SetTimer(25157,1000*pDoc->m_pDlgInterface->m_nReturnTime,NULL);
		else if(nLine==7 && m_nUsecheck[nLine] !=1)
			SetTimer(25158,1000*pDoc->m_pDlgInterface->m_nReturnTime,NULL);
		else if(nLine==8 && m_nUsecheck[nLine] !=1)
			SetTimer(25159,1000*pDoc->m_pDlgInterface->m_nReturnTime,NULL);
		m_nUsecheck[nLine] = 1;
	}
	else{
		KillTimer(25151);
		KillTimer(25152);
		KillTimer(25153);
		KillTimer(25154);
		KillTimer(25155);
		KillTimer(25156);
		KillTimer(25157);
		KillTimer(25158);
		KillTimer(25159);
		m_nUsecheck[nLine] = -1;
	}

}

void CVisWebView::CopyHeaderFile(CString strlot)
{
	double d1 = GetPrecisionTime();
	CString strsrc1,strdst1,strpath,strpath1,strdst2;
	CString data[6];
	CTime timer=CTime::GetCurrentTime();	
	data[0].Format("%d", timer.GetYear());
	if(timer.GetMonth() < 10)		data[1].Format("0%d", timer.GetMonth());
	else		data[1].Format("%d", timer.GetMonth());
	if(timer.GetDay() < 10)		data[2].Format("0%d", timer.GetDay());
	else		data[2].Format("%d", timer.GetDay());
	if(timer.GetHour() < 10)		data[3].Format("0%d", timer.GetHour());
	else		data[3].Format("%d", timer.GetHour());
	if(timer.GetMinute() < 10)		data[4].Format("0%d", timer.GetMinute());
	else		data[4].Format("%d", timer.GetMinute());
	if(timer.GetSecond() < 10)		data[5].Format("0%d", timer.GetSecond());
	else		data[5].Format("%d", timer.GetSecond());

	CTime ttime=CTime::GetCurrentTime();	
	CString kk = ttime.Format("%Y%m%d");
	//Create
	strdst1.Format("d:\\Data\\LotComplete\\");
	CreateDirectory(strdst1,NULL);	
	strdst1.Format("d:\\Data\\LotComplete\\%s\\",data[0]);//년
	CreateDirectory(strdst1,NULL);	
	strdst1.Format("d:\\Data\\LotComplete\\%s\\%s\\",data[0],data[1]);//month
	CreateDirectory(strdst1,NULL);	
	strdst1.Format("d:\\Data\\LotComplete\\%s\\%s\\%s\\",data[0],data[1],data[2]);//day
	CreateDirectory(strdst1,NULL);	
	strdst1.Format("d:\\Data\\LotComplete\\%s\\%s\\%s\\%s\\",data[0],data[1],data[2],strlot);//lot
	CreateDirectory(strdst1,NULL);	
	strdst1.Format("d:\\Data\\LotComplete\\%s\\%s\\%s\\%s\\Head\\",data[0],data[1],data[2],strlot);//lot
	CreateDirectory(strdst1,NULL);	
	strdst2 = strdst1;

	CString strtb;
	strtb = m_strComputerName.Left(8)+"H"+m_strComputerName.Right(2);//ochct01aht1

	strsrc1.Format("\\\\100.0.0.21\\data\\Lotdata\\%s\\%s\\",kk,strlot);//head back
	strsrc1.Format("\\\\%s\\data\\Lotdata\\%s\\%s\\",strtb,kk,strlot);//head back
	SHFILEOPSTRUCT    shfo;
	WORD        wfunc;
	TCHAR        pszTo[1024] = {0};
	TCHAR        pszFrom[1024] = {0};
	TCHAR        pszTitle[MAX_PATH] = {0};
	wfunc = FO_MOVE;
	memset(pszTo, 0, sizeof(pszTo));   // 중요
	memset(pszFrom, 0, sizeof(pszFrom));
	strcpy(pszTitle, "MoveFile");
	strcpy(pszTo, strdst1);
	strcpy(pszFrom , strsrc1);
	ZeroMemory(&shfo, sizeof(shfo));
	shfo.hwnd = AfxGetMainWnd()->m_hWnd;
	shfo.wFunc = wfunc;
	shfo.lpszProgressTitle=pszTitle;
	shfo.pTo=pszTo;
	shfo.pFrom=pszFrom;//FOF_NOCONFIRMATION
	shfo.fFlags = FOF_NOCONFIRMMKDIR|FOF_NOCONFIRMATION|FOF_SILENT|FOF_NOERRORUI;
	int ret = SHFileOperation(&shfo);
	CString str;
	str.Format("%s Head File Copy %.0f",strlot,(d1-GetPrecisionTime())*1000);
	AddtoList(str,0);
	
}

void CVisWebView::CopyImageFile(CString strlot)
{
	double d1 = GetPrecisionTime();
	CString strsrc1,strdst1,strpath,strpath1,strdst2,strdst3;
	CString data[6];
	CTime timer=CTime::GetCurrentTime();	
	data[0].Format("%d", timer.GetYear());
	if(timer.GetMonth() < 10)		data[1].Format("0%d", timer.GetMonth());
	else		data[1].Format("%d", timer.GetMonth());
	if(timer.GetDay() < 10)		data[2].Format("0%d", timer.GetDay());
	else		data[2].Format("%d", timer.GetDay());
	if(timer.GetHour() < 10)		data[3].Format("0%d", timer.GetHour());
	else		data[3].Format("%d", timer.GetHour());
	if(timer.GetMinute() < 10)		data[4].Format("0%d", timer.GetMinute());
	else		data[4].Format("%d", timer.GetMinute());
	if(timer.GetSecond() < 10)		data[5].Format("0%d", timer.GetSecond());
	else		data[5].Format("%d", timer.GetSecond());

	CTime ttime=CTime::GetCurrentTime();	
	CString kk = ttime.Format("%Y%m%d");
	//Create
	strdst1.Format("d:\\Data\\LotComplete\\");
	CreateDirectory(strdst1,NULL);	
	strdst1.Format("d:\\Data\\LotComplete\\%s\\",data[0]);//년
	CreateDirectory(strdst1,NULL);	
	strdst1.Format("d:\\Data\\LotComplete\\%s\\%s\\",data[0],data[1]);//month
	CreateDirectory(strdst1,NULL);	
	strdst1.Format("d:\\Data\\LotComplete\\%s\\%s\\%s\\",data[0],data[1],data[2]);//day
	CreateDirectory(strdst1,NULL);	
	strdst1.Format("d:\\Data\\LotComplete\\%s\\%s\\%s\\%s\\",data[0],data[1],data[2],strlot);//lot
	CreateDirectory(strdst1,NULL);	
	strdst2 = strdst1;
	strdst1.Format("d:\\Data\\LotComplete\\%s\\%s\\%s\\%s\\Surface\\",data[0],data[1],data[2],strlot);//lot
	CreateDirectory(strdst1,NULL);	

	CString strLot1,strLot2,strLot3;
	int ncutno = atoi(strlot.Right(2));
	strLot1 = strlot.Left(7);
	strLot2.Format("%s_%03d",strLot1,ncutno);
	
	if(m_strComputerName.Find("CMI")>=0){
	//	strsrc1.Format("\\\\192.168.0.100\\data\\Lotdata\\%s\\%s\\%s\\%s\\",data[0],data[1],data[2],strLot1);//head back
		if(m_strComputerName.Mid(7,1)=="A")
			strsrc1.Format("\\\\100.0.0.31\\data\\Lotdata\\%s\\%s\\%s\\%s\\",data[0],data[1],data[2],strLot2);//head back
		else
			strsrc1.Format("\\\\100.0.0.36\\data\\Lotdata\\%s\\%s\\%s\\%s\\",data[0],data[1],data[2],strLot2);//head back

	}
	else if(m_strComputerName.Find("OCH")>=0){
		//41 42 46 47
		strLot2 = strlot;		//200624 kjh
		CString strno;
		if(m_strComputerName.Mid(6,1)=="1"){ //ochct01aht1
			if(m_strComputerName.Mid(7,1)=="A"){//음극
				strno = "46";
			}
			else
				strno = "41";
		}
		else{
			if(m_strComputerName.Mid(7,1)=="A"){//음극
				strno = "47";
			}
			else
				strno = "42";
		}

		//strsrc1.Format("\\\\100.0.0.%s\\data\\Lotdata\\%s\\%s\\%s\\%s\\",strno,data[0],data[1],data[2],strLot1);//head back
		//strsrc1.Format("\\\\100.0.0.%s\\data\\Lotdata\\%s\\%s\\%s\\%s\\",strno,data[0],data[1],data[2],strLot2);//head back
		//strsrc1.Format("d:\\data\\Lotdata\\%s\\%s\\%s\\%s\\Surface\\",kk, strLot2);//head back
		strsrc1.Format("%s\\Head\\%s\\Surface\\", strdst2, strLot2);
		
	}

	// 표면검사 불량 이미지폴더 move
	strLot3.Format("path:%s , Lot:%s",strsrc1,strLot2);
	AddtoList(strLot3,0);
	SHFILEOPSTRUCT    shfo;
	WORD        wfunc;
	TCHAR        pszTo[1024] = {0};
	TCHAR        pszFrom[1024] = {0};
	TCHAR        pszTitle[MAX_PATH] = {0};
	wfunc = FO_MOVE;
	memset(pszTo, 0, sizeof(pszTo));   // 중요
	memset(pszFrom, 0, sizeof(pszFrom));
	strcpy(pszTitle, "MoveFile");
	strcpy(pszTo, strdst2);
	strcpy(pszFrom , strsrc1);
	ZeroMemory(&shfo, sizeof(shfo));
	shfo.hwnd = AfxGetMainWnd()->m_hWnd;
	shfo.wFunc = wfunc;
	shfo.lpszProgressTitle=pszTitle;
	shfo.pTo=pszTo;
	shfo.pFrom=pszFrom;//FOF_NOCONFIRMATION
	shfo.fFlags = FOF_NOCONFIRMMKDIR|FOF_NOCONFIRMATION|FOF_SILENT|FOF_NOERRORUI;
	int ret = SHFileOperation(&shfo); //200624 kjh
	CString str;
	//ReadImageFile(strdst2,strdst1,strlot,strLot2);
	ReadImageFile(strdst2,strdst1,strlot,strLot2);	  // 표면검사 이미지 로드후 csv만듬

	//
// 	MoveImageFile(strdst2,strlot);
// 	MakeDefectCsv(strdst2,strlot);		// defectFull.csv만듬	

	m_bLotchanging = FALSE;//Lot change 헤제
	str.Format("%s Lot End sur-Image Copy %.0f_%s_%s",strlot,(d1-GetPrecisionTime())*1000,strdst1,strlot);
	AddtoList(str,0);
}

void CVisWebView::CopyMisFile(CString strlot)
{
	double d1 = GetPrecisionTime();
	CString strsrc1,strdst1,strpath,strpath1,strdst2;
	CString data[6];
	CTime timer=CTime::GetCurrentTime();	
	data[0].Format("%d", timer.GetYear());
	if(timer.GetMonth() < 10)		data[1].Format("0%d", timer.GetMonth());
	else		data[1].Format("%d", timer.GetMonth());
	if(timer.GetDay() < 10)		data[2].Format("0%d", timer.GetDay());
	else		data[2].Format("%d", timer.GetDay());
	if(timer.GetHour() < 10)		data[3].Format("0%d", timer.GetHour());
	else		data[3].Format("%d", timer.GetHour());
	if(timer.GetMinute() < 10)		data[4].Format("0%d", timer.GetMinute());
	else		data[4].Format("%d", timer.GetMinute());
	if(timer.GetSecond() < 10)		data[5].Format("0%d", timer.GetSecond());
	else		data[5].Format("%d", timer.GetSecond());

	CTime ttime=CTime::GetCurrentTime();	
	CString kk = ttime.Format("%Y%m%d");
	//Create
	strdst1.Format("d:\\Data\\LotComplete\\");
	CreateDirectory(strdst1,NULL);	
	strdst1.Format("d:\\Data\\LotComplete\\%s\\",data[0]);//년
	CreateDirectory(strdst1,NULL);	
	strdst1.Format("d:\\Data\\LotComplete\\%s\\%s\\",data[0],data[1]);//month
	CreateDirectory(strdst1,NULL);	
	strdst1.Format("d:\\Data\\LotComplete\\%s\\%s\\%s\\",data[0],data[1],data[2]);//day
	CreateDirectory(strdst1,NULL);	
	strdst1.Format("d:\\Data\\LotComplete\\%s\\%s\\%s\\%s\\",data[0],data[1],data[2],strlot);//lot
	CreateDirectory(strdst1,NULL);	
	strdst1.Format("d:\\Data\\LotComplete\\%s\\%s\\%s\\%s\\Mis\\",data[0],data[1],data[2],strlot);//lot
	CreateDirectory(strdst1,NULL);	
	strdst2 = strdst1;

	strsrc1.Format("d:\\data\\Lotdata\\%s\\%s\\",kk,strlot);//head back
	SHFILEOPSTRUCT    shfo;
	WORD        wfunc;
	TCHAR        pszTo[1024] = {0};
	TCHAR        pszFrom[1024] = {0};
	TCHAR        pszTitle[MAX_PATH] = {0};
	wfunc = FO_MOVE;
	memset(pszTo, 0, sizeof(pszTo));   // 중요
	memset(pszFrom, 0, sizeof(pszFrom));
	strcpy(pszTitle, "MoveFile");
	strcpy(pszTo, strdst1);
	strcpy(pszFrom , strsrc1);
	ZeroMemory(&shfo, sizeof(shfo));
	shfo.hwnd = AfxGetMainWnd()->m_hWnd;
	shfo.wFunc = wfunc;
	shfo.lpszProgressTitle=pszTitle;
	shfo.pTo=pszTo;
	shfo.pFrom=pszFrom;//FOF_NOCONFIRMATION
	shfo.fFlags = FOF_NOCONFIRMMKDIR|FOF_NOCONFIRMATION|FOF_SILENT|FOF_NOERRORUI;
	int ret = SHFileOperation(&shfo);
	CString str;
	str.Format("%s MisFile Copy %.0f",strlot,(d1-GetPrecisionTime())*1000);
	AddtoList(str,0);
}

void CVisWebView::ReadImageFile(CString strBase, CString strBmpPath,CString strlot,CString strlot1)
{
	//file read
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CStdioFile   file;
	CString filename,strtmp,strpathname,pathname;
	CString imageFolderPath1 = strBmpPath+"\\";
	CString imageFolderPath2 = "*.jpg"; // \\ 넣어야 하는지 확인
	CFileFind finder;
	BOOL bRet;
	BOOL isFind = finder.FindFile(imageFolderPath1+imageFolderPath2);
	int imageListCount = 0;
	int imageCount = 10000;
	
	while (isFind){
		isFind = finder.FindNextFile();
		pathname = finder.GetFilePath();
		filename = finder.GetFileName();
		strpathname = finder.GetFilePath();
		if ( finder.IsDirectory() || finder.IsDots() )
			continue;
		else
		{
//			WriteSurDefect(strBmpPath,filename, strlot);
			WriteSurDefect(strBase,imageFolderPath1,filename, strlot);

		}
	}

}

void CVisWebView::WriteSurDefect(CString strBase, CString strpath,CString strname,CString strLot)
{
	//화일을 쪼개고
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CString strfile1;
	int n1 = strname.GetLength();
	strfile1 = strname.Left(n1-4);//.bmp


	CStdioFile   file;
	CString filename;
	CString strtmp,str,strTitle,strtmp1;

	CString strTok;    
	int sepCount =0;
	for(int i=0;i<strfile1.GetLength();i++)	if(strfile1.GetAt(i) == '_')	sepCount++;
	CString* temp1 = new CString[sepCount+1]; 
	int cnt=0;// 
	while(AfxExtractSubString(strTok, strfile1, cnt, '_'))  
		temp1[cnt++] = strTok;// 해당 배열에 순차적으로 넣어준다.

	//년월일시분초_불량명_posx_posy_Lane_sx_sy_V_이미지 경로
	//0				1	  2      3    4   5  6  7  8
	if(cnt<8)
		return;
//	strTitle.Format("Date,Defect name,Pos x,Pos y,Lane, Size X,Size Y,Value,Path,File Name");
	strTitle.Format("Date,lot,Pos x,Pos y, Size X,Size Y,Value,name,CamID,Path,File Name");
	strTitle.Format("Date,lot,Pos x,Pos y, Size X,Size Y,Value,name,Path,File Name");
//	strtmp1.Format("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,",temp1[0],strLot,temp1[2],temp1[3],temp1[5],temp1[6],temp1[7],temp1[1],temp1[8],strpath,strname); //엔시스 업그레이드후 여기 해제
	strtmp1.Format("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",temp1[0],strLot,temp1[3],temp1[2],temp1[5],temp1[6],temp1[7],temp1[1],temp1[8],strpath,strname);			//200624 kjh
	filename.Format("%s\\%s_SurDefect.csv",strBase,strLot);	//200624 kjh
//	화일 기록
	if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
	{		
		if(file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText))
		{
// 			file.WriteString(strTitle);
// 			file.WriteString("\n");
			file.WriteString(strtmp1);
			file.Close();
		}
	}
	else
	{
		file.SeekToEnd();
		file.WriteString("\n");
		file.WriteString(strtmp1);
		file.Close(); 
	}
}

void CVisWebView::MoveImageFile(CString strbaseRoot,CString strLot)//D:\Data\LOTdata\LotComplete\2020\03\09\NATC913 1
{
	// 헤드 백  D:\Data\LOTdata\LotComplete\2020\03\09\NATC913 1\Head\NATC913 1\CMICT01AHB1
	// 헤드 탑  D:\Data\LOTdata\LotComplete\2020\03\09\NATC913 1\Head\NATC913 1\NATC913 1\CMICT01AHT1
	// 미스 백  D:\Data\LOTdata\LotComplete\2020\03\09\NATC913 1\Mis\NATC913 1\CMICT01AMB1
	// 미스 탑  D:\Data\LOTdata\LotComplete\2020\03\09\NATC913 1\Mis\NATC913 1\NATC913 1\CMICT01AMT1
	//표면검사  D:\Data\LOTdata\LotComplete\2020\03\09\NATC913 1\Surface\NATC913_001

	CString strMovepath[5],strMovepath1[5],strpc[5],strlot,strlot1;
	strlot = strlot1 = strLot;
	int ncutno = atoi(strlot1.Right(2));
	strlot1.Format("%s_%03d",strLot.Left(7),ncutno);
	if(m_strComputerName.Mid(7,1)=="A"){
		strpc[0].Format("CMICT01AHT1");
		strpc[1].Format("CMICT01AHB1");
		strpc[2].Format("CMICT01AMT1");
		strpc[3].Format("CMICT01AMB1");
	}
	else{
		strpc[0].Format("CMICT01CHT1");
		strpc[1].Format("CMICT01CHB1");
		strpc[2].Format("CMICT01CMT1");
		strpc[3].Format("CMICT01CMB1");
	}
//이동경로
	strMovepath[0].Format("%sHeadTop\\",strbaseRoot);
	strMovepath[1].Format("%sHeadBack\\",strbaseRoot);
	strMovepath[2].Format("%sMisTop\\",strbaseRoot);
	strMovepath[3].Format("%sMisBack\\",strbaseRoot);
	strMovepath[4].Format("%sSurface\\",strbaseRoot);
	for(int i=0;i<5;i++)	CreateDirectory(strMovepath[i],NULL);

//오리진 경로
	strMovepath1[0].Format("%sHead\\%s\\%s\\",strbaseRoot,strlot,strlot);
	strMovepath1[1].Format("%sHead\\%s\\",strbaseRoot,strlot);
	strMovepath1[2].Format("%sMis\\%s\\%s\\",strbaseRoot,strlot,strlot);
	strMovepath1[3].Format("%sMis\\%s\\",strbaseRoot,strlot);
	strMovepath1[4].Format("%sSurface\\%s\\",strbaseRoot,strlot1);

	//move file
	CFileFind finder,finder1;
	BOOL bRet;
	CString strFile1,pathname,filename,strpathname,strnewfile,strFile2;
	strFile1.Format("*.bmp");
	strFile2.Format("*.csv");
	for(int i=0;i<5;i++){
		BOOL isFind = finder.FindFile(strMovepath1[i]+strpc[i]+"\\"+strFile1);

		while (isFind){
			isFind = finder.FindNextFile();
			pathname = finder.GetFilePath();
			filename = finder.GetFileName();
			strpathname = finder.GetFilePath();
			if ( finder.IsDirectory() || finder.IsDots() )
				continue;
			else
			{
				strnewfile.Format("%s\\%s",strMovepath[i],filename);
//				CopyFile(pathname,strnewfile,FALSE);
				MoveFile(pathname,strnewfile);
			}
		}
//csvfile
		BOOL isFind1 = finder1.FindFile(strMovepath1[i]+strFile2);
		while (isFind1){
			isFind1 = finder1.FindNextFile();
			pathname = finder1.GetFilePath();
			filename = finder1.GetFileName();
			strpathname = finder1.GetFilePath();
			if ( finder1.IsDirectory() || finder1.IsDots() )
				continue;
			else
			{
				strnewfile.Format("%s\\%s",strbaseRoot,filename);
//				CopyFile(pathname,strnewfile,FALSE);
				MoveFile(pathname,strnewfile);
			}
		}
	}
}

void CVisWebView::MakeDefectCsv(CString strbaseRoot,CString strLot)//D:\Data\LOTdata\LotComplete\2020\03\09\NATC913 1
{
	CFileFind finder,finder1;
	BOOL bRet;
	CString strFile1,pathname,filename;
	strFile1.Format("*Defect.csv");
	BOOL isFind = finder.FindFile(strbaseRoot+"\\"+strFile1);

	CStdioFile   file;
	CString strNewfile;
	strNewfile.Format("%s\\%s_DefectFull.csv",strbaseRoot,strLot);

	while (isFind){
		isFind = finder.FindNextFile();
		pathname = finder.GetFilePath();
		filename = finder.GetFileName();
		if ( finder.IsDirectory() || finder.IsDots() )
			continue;
		else
		{
			//read Csv
			MakeOneCsvFile(pathname,strNewfile);

		}
	}

}

void CVisWebView::MakeOneCsvFile(CString strFilename,CString strNewName)//D:\Data\LOTdata\LotComplete\2020\03\09\NATC913 1
{
	CStdioFile   file,file1;
	CString filename,filename1;
	CString strtmp,str,strTitle,strtmp1;
	filename.Format("%s",strFilename);
	filename1 = strNewName;
	//	화일 기록
 
 	if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
 	{	
		//file error
 	}
 	else
 	{
		if(!file1.Open(filename1, CFile::modeReadWrite|CFile::typeText)) 
		{
			file1.Open(filename1, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText);
		}
 		while(1){

			if(file.ReadString(str) == NULL)
				break;
			else{
				if(str==""){
					file1.Close();
					file.Close();
					return;
				}		
				file1.SeekToEnd();
				file1.WriteString(str);
				file1.WriteString("\n");
			}	
 		}
		file1.Close();
		file.Close();
 	}	
}


void CVisWebView::WriteLotEnd(CString strLot)
{
	CStdioFile   file;
	CString filename;
	CString strpath;
	CString str,strTitle,strtmp,strtmp1,strtmp2,strtmp3,strtmp4,strtmp5,strtmp6;
	CTime ttime = CTime::GetCurrentTime();
	CString kk = ttime.Format("%Y%m%d");//ttime.Format("%H_%M_%S");
	CString strTime = ttime.Format("[%Y %m %d %H:%M:%S]");
	CString data[6];
	CTime timer=CTime::GetCurrentTime();  
	data[0].Format("%d", timer.GetYear());
	if(timer.GetMonth() < 10)             data[1].Format("0%d", timer.GetMonth());
	else           data[1].Format("%d", timer.GetMonth());
	if(timer.GetDay() < 10)               data[2].Format("0%d", timer.GetDay());
	else           data[2].Format("%d", timer.GetDay());
	if(timer.GetHour() < 10)              data[3].Format("0%d", timer.GetHour());
	else           data[3].Format("%d", timer.GetHour());
	if(timer.GetMinute() < 10)            data[4].Format("0%d", timer.GetMinute());
	else           data[4].Format("%d", timer.GetMinute());
	if(timer.GetSecond() < 10)            data[5].Format("0%d", timer.GetSecond());
	else           data[5].Format("%d", timer.GetSecond());

	if(strLot=="")strLot = "NONE";


	strpath.Format("d:\\Data\\LotInfo\\");
	CreateDirectory(strpath,NULL);
	strpath.Format("d:\\Data\\LotInfo\\%s\\",data[0]);//yy
	CreateDirectory(strpath,NULL);
	strpath.Format("d:\\Data\\LotInfo\\%s\\%s\\",data[0],data[1]);//yymm
	CreateDirectory(strpath,NULL);
	strpath.Format("d:\\Data\\LotInfo\\%s\\%s\\%s\\",data[0],data[1],data[2]);//yymmdd
	CreateDirectory(strpath,NULL);
	filename.Format("%s%s_End.Lot",strpath,strLot);


	if(file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText))
	{
		file.WriteString("\n");
		file.Close();
	}

}

void CVisWebView::WrtieDefectCount(int nCount,CString strlot)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CStdioFile   file;
	CString filename;
	CString strpath;
	CString str;
	CString data[6];
	CTime timer=CTime::GetCurrentTime();  
	data[0].Format("%d", timer.GetYear());
	if(timer.GetMonth() < 10)             data[1].Format("0%d", timer.GetMonth());
	else           data[1].Format("%d", timer.GetMonth());
	if(timer.GetDay() < 10)               data[2].Format("0%d", timer.GetDay());
	else           data[2].Format("%d", timer.GetDay());
	if(timer.GetHour() < 10)              data[3].Format("0%d", timer.GetHour());
	else           data[3].Format("%d", timer.GetHour());
	if(timer.GetMinute() < 10)            data[4].Format("0%d", timer.GetMinute());
	else           data[4].Format("%d", timer.GetMinute());
	if(timer.GetSecond() < 10)            data[5].Format("0%d", timer.GetSecond());
	else           data[5].Format("%d", timer.GetSecond());

	strpath.Format("d:\\Data\\BadDefect\\");
	CreateDirectory(strpath,NULL);
	strpath.Format("d:\\Data\\BadDefect\\%s\\",data[0]);
	CreateDirectory(strpath,NULL);
	strpath.Format("d:\\Data\\BadDefect\\%s\\%s\\",data[0],data[1]);
	CreateDirectory(strpath,NULL);
	strpath.Format("d:\\Data\\BadDefect\\%s\\%s\\%s\\",data[0],data[1],data[2]);
	CreateDirectory(strpath,NULL);
	strpath.Format("d:\\Data\\BadDefect\\%s\\%s\\%s\\%s\\",data[0],data[1],data[2],strlot);
	CreateDirectory(strpath,NULL);
	filename.Format("%s%s_%s_count.txt",strpath,strlot,m_strComputerName);
	str.Format("%d",nCount);

	CString strdefect[10];
	strdefect[0].Format("%d",pDoc->m_data.m_nBadTypeCount[0]);//drag
	strdefect[1].Format("%d",pDoc->m_data.m_nBadTypeCount[1]);//nc-line
	strdefect[2].Format("%d",pDoc->m_data.m_nBadTypeCount[2]);//island
	strdefect[3].Format("%d",pDoc->m_data.m_nBadTypeCount[3]);//edge spur
	strdefect[4].Format("%d",pDoc->m_data.m_nBadTypeCount[4]);//c-line
	strdefect[5].Format("%d",pDoc->m_data.m_nBadTypeCount[5]);//pinhole

	try{
		g_Mutex.Lock();                    // 뮤텍스를 잠근다.

		if(file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText))
		{		
			file.WriteString(str);	//총개수
			file.WriteString("\n");	
			for(int i=0;i<6;i++){
				file.WriteString(strdefect[i]);	
				file.WriteString("\n");	
			}
			file.Close();
		}
		g_Mutex.Unlock();                 // 뮤텍스를 풀어준다.
	}
	catch(CFileException)
	{
		//AfxMessageBox( "File Open failed" );
	}
	catch(...)
	{
		//AfxMessageBox( "File Open failed2~" );
	}
}

void CVisWebView::ReadDefectCount(CString strlot)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CStdioFile   file;
	CString filename;
	CString strpath;
	CString str;
	CString data[6];
	CTime timer=CTime::GetCurrentTime();  
	data[0].Format("%d", timer.GetYear());
	if(timer.GetMonth() < 10)             data[1].Format("0%d", timer.GetMonth());
	else           data[1].Format("%d", timer.GetMonth());
	if(timer.GetDay() < 10)               data[2].Format("0%d", timer.GetDay());
	else           data[2].Format("%d", timer.GetDay());
	if(timer.GetHour() < 10)              data[3].Format("0%d", timer.GetHour());
	else           data[3].Format("%d", timer.GetHour());
	if(timer.GetMinute() < 10)            data[4].Format("0%d", timer.GetMinute());
	else           data[4].Format("%d", timer.GetMinute());
	if(timer.GetSecond() < 10)            data[5].Format("0%d", timer.GetSecond());
	else           data[5].Format("%d", timer.GetSecond());

	if(pDoc->m_data.m_nCamID-1<0)return;
//file을 찾는다
	CString strpc,strsrc1;
	strpc = m_strComputerName.Left(9)+"T1";
	strsrc1.Format("\\\\%s\\Data\\BadDefect\\%s\\%s\\%s\\%s\\%s_%s_count.txt",strpc,data[0],data[1],data[2],strlot,strlot,strpc);//check 1104

	filename = strsrc1;
	CFileFind finder;
	BOOL IsFind;
	IsFind = finder.FindFile(filename);
	if(IsFind){
		if(file.Open(filename, CFile::modeReadWrite|CFile::typeText)) {
			file.ReadString(str);//총불량만 본다
			pDoc->m_data.m_nSumBadCount[pDoc->m_data.m_nCamID-1] = atoi(str);//mt count
			file.Close();
		}
		else
			pDoc->m_data.m_nSumBadCount[pDoc->m_data.m_nCamID-1] = 0;//mt count
	}

}

CString CVisWebView::CheckModelNo(int no1)
{
//모델 번호 찾기
	CString str;
// 	for(int i=0;i<20;i++){
// 		m_strPlcModelname[i] == 
// 	}
	//m_nSelectPlcModelNo
	str.Format("%d-%s",no1,m_strPlcModelname[no1]);
	//PLC에 기록
	//WriteShareMemory2(int context, int nindex,CString str1)//context = 0 미스매치 1무지상 2무지하 3코팅상 4코팅하 index눈 순서

	return str;
}

void CVisWebView::WritePlcModel()
{
	//모델 번호 찾기
	CString str;
 	for(int i=0;i<10;i++){
		//글자 쪼개기
		for(int k=0;k<5;k++){
			str = m_strPlcModelname[(i*2)+1].Mid(k*2,2);
			WriteShareMemory2(10+i,k,str);
			str = m_strPlcModelname[(i*2)+2].Mid(k*2,2);
			WriteShareMemory2(10+i,k+5,str);
		}
 	}
//	str.Format("%d-%s",no1,m_strPlcModelname[no1]);
}


void CVisWebView::WriteLotModel(CString strlot)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CStdioFile   file;
	CString filename;
	CString strpath;
	CString str;
	CString data[6];
	CTime timer=CTime::GetCurrentTime();  
	data[0].Format("%d", timer.GetYear());
	if(timer.GetMonth() < 10)             data[1].Format("0%d", timer.GetMonth());
	else           data[1].Format("%d", timer.GetMonth());
	if(timer.GetDay() < 10)               data[2].Format("0%d", timer.GetDay());
	else           data[2].Format("%d", timer.GetDay());
	if(timer.GetHour() < 10)              data[3].Format("0%d", timer.GetHour());
	else           data[3].Format("%d", timer.GetHour());
	if(timer.GetMinute() < 10)            data[4].Format("0%d", timer.GetMinute());
	else           data[4].Format("%d", timer.GetMinute());
	if(timer.GetSecond() < 10)            data[5].Format("0%d", timer.GetSecond());
	else           data[5].Format("%d", timer.GetSecond());

	strpath.Format("d:\\Data\\Server\\");
	CreateDirectory(strpath,NULL);
	strpath.Format("d:\\Data\\Server\\%s\\",data[0]);
	CreateDirectory(strpath,NULL);
	strpath.Format("d:\\Data\\Server\\%s\\%s\\",data[0],data[1]);
	CreateDirectory(strpath,NULL);
	strpath.Format("d:\\Data\\Server\\%s\\%s\\%s\\",data[0],data[1],data[2]);
	CreateDirectory(strpath,NULL);
	filename.Format("%s%s.lot",strpath,strlot);

	try{
		g_Mutex.Lock();                    // 뮤텍스를 잠근다.

		if(file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText))
		{		
			file.WriteString(strlot);	//총개수
			file.Close();
		}
		g_Mutex.Unlock();                 // 뮤텍스를 풀어준다.
	}
	catch(CFileException)
	{
		//AfxMessageBox( "File Open failed" );
	}
	catch(...)
	{
		//AfxMessageBox( "File Open failed2~" );
	}
}

void CVisWebView::WriteDefectDataServerSend(CString strLot, double dMeterY, double dMeterX, double dsx,double dsy, double dvalue,CString strType,CString strimg,CString imgname,CString newpath,int nMeter,
											 CString strmodel,CString strcolor, double dgain,double dsize1,double dmaxgray,double dmingray, double davegray,double dthvalue,CString strLocaltime, int nInspLocation)
{
	CStdioFile   file;
	CString filename,filename1;
	CString strpath,strpath1;
	CString str,strTitle,strtmp;
	CTime ttime = CTime::GetCurrentTime();
	CString kk = ttime.Format("%Y%m%d");//ttime.Format("%H_%M_%S");
	CString kk1;// = ttime.Format("%Y");//ttime.Format("%H_%M_%S");
	kk1.Format("%d", ttime.GetYear());
	CString data[6];
	CTime timer=CTime::GetCurrentTime();  
	data[0].Format("%d", timer.GetYear());
	if(timer.GetMonth() < 10)             data[1].Format("0%d", timer.GetMonth());
	else           data[1].Format("%d", timer.GetMonth());
	if(timer.GetDay() < 10)               data[2].Format("0%d", timer.GetDay());
	else           data[2].Format("%d", timer.GetDay());
	if(timer.GetHour() < 10)              data[3].Format("0%d", timer.GetHour());
	else           data[3].Format("%d", timer.GetHour());
	if(timer.GetMinute() < 10)            data[4].Format("0%d", timer.GetMinute());
	else           data[4].Format("%d", timer.GetMinute());
	if(timer.GetSecond() < 10)            data[5].Format("0%d", timer.GetSecond());
	else           data[5].Format("%d", timer.GetSecond());

	CString strTime = ttime.Format("%Y%m%d-%H:%M:%S");
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

// 	if(pDoc->m_data.m_bUseCLog){
// 		strpath.Format("C:\\Glim\\LotData\\");
// 		CreateDirectory(strpath,NULL);
// 		strpath.Format("C:\\Glim\\LotData\\%s\\",kk);
// 		CreateDirectory(strpath,NULL);
// 		strpath.Format("C:\\Glim\\LotData\\%s\\%s\\",kk,strLot);
// 		CreateDirectory(strpath,NULL);
// 		filename.Format("%s%s_%sDefect.csv",strpath,strLot,m_strComputerName);
// 	}
// 	else{
		strpath.Format("D:\\Data\\Server\\");
		CreateDirectory(strpath,NULL);
		strpath.Format("D:\\Data\\Server\\Log\\");
		CreateDirectory(strpath,NULL);
		strpath.Format("D:\\Data\\Server\\Log\\%s\\",data[0]);
		CreateDirectory(strpath,NULL);
		strpath.Format("D:\\Data\\Server\\Log\\%s\\%s\\",data[0],data[1]);
		CreateDirectory(strpath,NULL);
		strpath.Format("D:\\Data\\Server\\Log\\%s\\%s\\%s\\",data[0],data[1],data[2]);
		CreateDirectory(strpath,NULL);
		strpath.Format("D:\\Data\\Server\\Log\\%s\\%s\\%s\\%s\\",data[0],data[1],data[2],strLot);
		CreateDirectory(strpath,NULL);
		strpath1 = strpath;
		strpath1.Format("D:\\Data\\Server\\Log\\%s\\%s\\%s\\%s\\Complete\\",data[0],data[1],data[2],strLot);
		CreateDirectory(strpath1,NULL);

		filename.Format("%sDefect_%d.csv",strpath,nMeter);
		filename1.Format("%sDefect_%d.csv",strpath1,nMeter);
	//}
	//	strTitle.Format("Date,lot,Pos x,Pos y, Size X,Size Y,Value,name,Path,File Name");

	if(m_strServerSendFileName[2] !="" && filename != m_strServerSendFileName[2]){
		MoveFile(m_strServerSendFileName[2],m_strServerSendFileName[3]);
//		MoveFile(m_strServerSendFileName[],m_strServerSendFileName[3]);
	}

	m_strServerSendFileName[2] = filename;
	m_strServerSendFileName[3] = filename1;


	//시작	//종료	//Lot	//생산미터	
	strTitle.Format("Time,LotNo,YPos,XPos,SizeX,SizeY,Value,Type,CamPos,ImagePath,FileName,path1");
//	strtmp.Format("%s,%s,%.1f,%.1f,%.1f,%.1f,%.0f,%s,%d,%s,%s,%s",strTime,strLot,dMeterY,dMeterX,dsx,dsy,dvalue,strType,pDoc->m_data.m_nCamID,strimg,imgname,newpath);
	strtmp.Format("%s,%s,%.1f,%.1f,%.1f,%.1f,%.0f,%s,%d,%s,%s,%s,%s,%s,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%s",strTime,strLot,dMeterY,dMeterX,dsx,dsy,dvalue,strType,nInspLocation,strimg,imgname,newpath,
		strmodel,strcolor,dgain,dsize1,dmaxgray,dmingray,davegray,dthvalue,strLocaltime);

	if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
	{		
		if(file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText))
		{
			file.WriteString(strtmp);
			file.Close();
		}
	}
	else
	{
		file.SeekToEnd();
		file.WriteString("\n");
		file.WriteString(strtmp);
		file.Close(); 
	}
}
void CVisWebView::WrtieMeterData(CString strLot,int nMeter, int nSubFrame, int nLineCount,int nReverse) 
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CStdioFile   file;
	CString filename,filename1;
	CString strtmp,str,strTitle,strpath,strpath1,strOkNg,strpc,strtmp1,strtmp2,strtmp3,strtmp4,strtmp5,strtmp6,strtime;
	CString txtscr,txtdst;
	int nPcno =0;
	int nLine =0;
	//날자 LotNo. Frame	DefectCount	Defect-Class	x-Pos	Y-Pos	X-Size	Y-Size	ImagePath
	//////////////
	CString data[6];
	CTime timer=CTime::GetCurrentTime();	
	data[0].Format("%d", timer.GetYear());
	if(timer.GetMonth() < 10)		data[1].Format("0%d", timer.GetMonth());
	else		data[1].Format("%d", timer.GetMonth());
	if(timer.GetDay() < 10)		data[2].Format("0%d", timer.GetDay());
	else		data[2].Format("%d", timer.GetDay());
	if(timer.GetHour() < 10)		data[3].Format("0%d", timer.GetHour());
	else		data[3].Format("%d", timer.GetHour());
	if(timer.GetMinute() < 10)		data[4].Format("0%d", timer.GetMinute());
	else		data[4].Format("%d", timer.GetMinute());
	if(timer.GetSecond() < 10)		data[5].Format("0%d", timer.GetSecond());
	else		data[5].Format("%d", timer.GetSecond());
	if(strLot=="")strLot = "NONE";

	strpath.Format("D:\\Data\\");
	CreateDirectory(strpath,NULL);//년월일
	strpath.Format("D:\\Data\\Server\\");
	CreateDirectory(strpath,NULL);//년월일
	strpath.Format("D:\\Data\\Server\\Log\\");
	CreateDirectory(strpath,NULL);//년월일
	strpath.Format("D:\\Data\\Server\\Log\\%s\\",data[0]);
	CreateDirectory(strpath,NULL);//년월일
	strpath.Format("D:\\Data\\Server\\Log\\%s\\%s\\",data[0],data[1]);
	CreateDirectory(strpath,NULL);//년월일
	strpath.Format("D:\\Data\\Server\\Log\\%s\\%s\\%s\\",data[0],data[1],data[2]);
	CreateDirectory(strpath,NULL);//년월일
	strpath.Format("D:\\Data\\Server\\Log\\%s\\%s\\%s\\%s\\",data[0],data[1],data[2],strLot);
	CreateDirectory(strpath,NULL);
	strpath1.Format("D:\\Data\\Server\\Log\\%s\\%s\\%s\\%s\\Complete\\",data[0],data[1],data[2],strLot);
	CreateDirectory(strpath1,NULL);

	filename.Format("%s%s_%d.csv",strpath,pDoc->m_data.m_strComName,nMeter);//공유 c:\\glim\receive
	filename1.Format("%s%s_%d.csv",strpath1,pDoc->m_data.m_strComName,nMeter);//공유 c:\\glim\receive
	//
	if(m_strServerSendFileName[0] !="" && filename != m_strServerSendFileName[0]){
		MoveFile(m_strServerSendFileName[0],m_strServerSendFileName[1]);
		if(m_strServerSendFileName[2] != "")
			MoveFile(m_strServerSendFileName[2],m_strServerSendFileName[3]);

	}

	m_strServerSendFileName[0] = filename;
	m_strServerSendFileName[1] = filename1;
	int frame = nSubFrame;
	strtmp1 = strtmp2 = strtmp3 = strtmp4 =strtmp5=strtmp6= "";

	CString sttrtile1,sttrtile2,sttrtile3,sttrtile4,sttrtile5,sttrtile6;
	strtime.Format("%s-%s-%s-%s:%s:%s",data[0],data[1],data[2],data[3],data[4],data[5]);
	int nCount1 = nLineCount;
	int nc1 = 0;
	double d1=0,doffsetScale=0.002485;
	int nCalPos = 0;
	double d2=0,d3;

	double dScale = pDoc->m_data.m_dScaleFactorX[0];
	int ntopback =0;
	if(m_strComputerName.Find("CMI")>=0 ||m_strComputerName.Find("OCH")>=0){
		//|| pDoc->m_data.m_nLineSelect%10==2
	}
	if(m_strComputerName.Find("BACK")>=0 ||  pDoc->m_data.m_strComName.Mid(9,1)=="B")ntopback = 1;	 
	double dtmp[20] = {0,};
	int cnt =0;
	if(nReverse==2){
		double dmaster = pDoc->m_data.m_dNewLineEdgeData1[nCount1-1];
		double dmaster1 = pDoc->m_data.m_dNewLineEdgeData1[0];
		for(int i=nCount1-1;i>=0;i--){
			dtmp[cnt] = dmaster- pDoc->m_data.m_dNewLineEdgeData1[i] + dmaster1;
			cnt++;
		}
	}
	else{
		for(int i=0;i<nCount1;i++)//0번은 갯수
			dtmp[i] = pDoc->m_data.m_dNewLineEdgeData1[i];
	}

	for(int i=0;i<nCount1;i++){//0번은 갯수
		strtmp1.Format(",%.2f",dtmp[i]);
		strtmp2 += strtmp1;
		if(i==0)
			strtmp3.Format(",0");
		else
			strtmp3.Format(",%.2f",(dtmp[i]-dtmp[i-1])*pDoc->m_data.m_dScaleFactorX[0]);

		strtmp4 += strtmp3;
	}

	//	strTitle.Format("Time,PC,LotID,Meter,FrameNo,Scale,LineCount%s",sttrtile4);//,sttrtile5,sttrtile6);
	strtmp.Format("%s,%s,%s,%d,%d,%.7f,%d%s%s",strtime,m_strComputerName,strLot,nMeter,frame,dScale,nLineCount,strtmp2,strtmp4);
	if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
	{		
		if(file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText))
		{
			file.WriteString(strtmp);
			file.Close();
		}
	}
	else
	{
		file.SeekToEnd();
		file.WriteString("\n");
		file.WriteString(strtmp);
		file.Close(); 
	}
}

void CVisWebView::LotChange() 
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CString strlot,strtime,strtime1,strtime2, strBaseFolder;
	CString data[6];
	CTime timer=CTime::GetCurrentTime();	
	
	strtime1 =m_strEndTime;
	strtime2 =m_strStartTime;
	double dmeter = m_dMeterY;		//200904 kjh
	for(int i=0;i<10;i++){
		if(m_bLotChange[i]){
			strlot = m_strLotChangeID[i];
			strtime = m_strLotChangeTime[i];
			m_bLotChange[i] = FALSE;
			m_strLotChangeID[i] = "";
			m_strLotChangeTime[i] = "";
			break;
		}
	}

	data[0].Format("%d", timer.GetYear());
	if(timer.GetMonth() < 10)		data[1].Format("0%d", timer.GetMonth());
	else		data[1].Format("%d", timer.GetMonth());
	if(timer.GetDay() < 10)		data[2].Format("0%d", timer.GetDay());
	else		data[2].Format("%d", timer.GetDay());
	if(timer.GetHour() < 10)		data[3].Format("0%d", timer.GetHour());
	else		data[3].Format("%d", timer.GetHour());
	if(timer.GetMinute() < 10)		data[4].Format("0%d", timer.GetMinute());
	else		data[4].Format("%d", timer.GetMinute());
	if(timer.GetSecond() < 10)		data[5].Format("0%d", timer.GetSecond());
	else		data[5].Format("%d", timer.GetSecond());


	strBaseFolder.Format("d:\\Data\\LotComplete\\");
	CreateDirectory(strBaseFolder,NULL);	
	strBaseFolder.Format("d:\\Data\\LotComplete\\%s\\",data[0]);//년
	CreateDirectory(strBaseFolder,NULL);	
	strBaseFolder.Format("d:\\Data\\LotComplete\\%s\\%s\\",data[0],data[1]);//month
	CreateDirectory(strBaseFolder,NULL);	
	strBaseFolder.Format("d:\\Data\\LotComplete\\%s\\%s\\%s\\",data[0],data[1],data[2]);//day
	CreateDirectory(strBaseFolder,NULL);	
	strBaseFolder.Format("d:\\Data\\LotComplete\\%s\\%s\\%s\\%s",data[0],data[1],data[2],strlot);//lot
	CreateDirectory(strBaseFolder,NULL);	


	int nTotalLineDefect = pDoc->m_data.m_nTmpBadTypeCount[1]+pDoc->m_data.m_nTmpBadTypeCount[4];		// 200702 m_nTmpBadTypeCount
	//라인,핀홀,파인핀홀,분화구,크랙,표면불량,미스매치,아일랜드,드래그,주름
	WriteLotInfo(strlot,  strtime1,strtime2, dmeter, nTotalLineDefect+m_nNsysNgCount[0], pDoc->m_data.m_nTmpBadTypeCount[5]+m_nNsysNgCount[1], pDoc->m_data.m_nTmpBadTypeCount[3]+m_nNsysNgCount[2], 0/*분화구*/, 0/*크랙*/, 0/*표면불량*/, 0/*미스매치*/,  pDoc->m_data.m_nTmpBadTypeCount[2]+m_nNsysNgCount[7], pDoc->m_data.m_nTmpBadTypeCount[0]+m_nNsysNgCount[8], 0/*주름*/);
	
	CopyLotDataFolders(strlot, strtime);		// 검사기별 불량 이미지 & sharpness 이미지 폴더 move
	CopySurfaceImg(strBaseFolder, strlot);
	
	for(int i=0; i<MAX_DEFECT_COUNT; i++)
		m_nNsysNgCount[i] = 0;

	//	SetTimer(14123,100,NULL);//file move
	MoveCSVFile(strBaseFolder, strlot);

	MakeDefectCsv(strBaseFolder,strlot);		// defectFull.csv만듬

	WriteLotEnd(strlot);

	AddtoList("LotChange Off",0,TRUE);


}

 int CVisWebView::CheckReceiveFolder()
 {//
	 CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CString data[6];
 	CTime timer=CTime::GetCurrentTime();	
 	data[0].Format("%d", timer.GetYear());
 	if(timer.GetMonth() < 10)		data[1].Format("0%d", timer.GetMonth());
 	else		data[1].Format("%d", timer.GetMonth());
 	if(timer.GetDay() < 10)		data[2].Format("0%d", timer.GetDay());
 	else		data[2].Format("%d", timer.GetDay());
 	if(timer.GetHour() < 10)		data[3].Format("0%d", timer.GetHour());
 	else		data[3].Format("%d", timer.GetHour());
 	if(timer.GetMinute() < 10)		data[4].Format("0%d", timer.GetMinute());
 	else		data[4].Format("%d", timer.GetMinute());
 	if(timer.GetSecond() < 10)		data[5].Format("0%d", timer.GetSecond());
 	else		data[5].Format("%d", timer.GetSecond());
 	CString strfolder1,strfile,pathname,filename,strpathname,strCode;
 
 	strfolder1.Format("d:\\Data\\Server\\Receive\\");
 	CreateDirectory(strfolder1,NULL);//년월일
 	strfolder1.Format("d:\\Data\\Server\\Receive\\%s\\",data[0]);
 	CreateDirectory(strfolder1,NULL);//년월일
	strfolder1.Format("d:\\Data\\Server\\Receive\\%s\\%s\\",data[0],data[1]);
	CreateDirectory(strfolder1,NULL);//년월일
	strfolder1.Format("d:\\Data\\Server\\Receive\\%s\\%s\\%s\\",data[0],data[1],data[2]);
	CreateDirectory(strfolder1,NULL);//년월일
	strfile.Format("%s*.rcv",strfolder1);

	//file read
	CStdioFile   file;
	CFileFind finder;
	BOOL bRet;
	BOOL isFind = finder.FindFile(strfile);
	int imageListCount = 0;
	int imageCount = 10000;

	while (isFind){
		isFind = finder.FindNextFile();
		pathname = finder.GetFilePath();
		filename = finder.GetFileName();
		strpathname = finder.GetFilePath();
		strCode = strpathname;
		strCode.TrimRight(".rcv");
		if ( finder.IsDirectory() || finder.IsDots() )
			continue;
		else
		{
			//화일명이 코드 내용은 할일
			CheckCode(strCode,strpathname);
		}
	}

 	return 0;
 }

 int CVisWebView::CheckCode(CString strcode,CString strFullpath)
 {
	 CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	 CString data[6];
	 CTime timer=CTime::GetCurrentTime();	
	 data[0].Format("%d", timer.GetYear());
	 if(timer.GetMonth() < 10)		data[1].Format("0%d", timer.GetMonth());
	 else		data[1].Format("%d", timer.GetMonth());
	 if(timer.GetDay() < 10)		data[2].Format("0%d", timer.GetDay());
	 else		data[2].Format("%d", timer.GetDay());
	 if(timer.GetHour() < 10)		data[3].Format("0%d", timer.GetHour());
	 else		data[3].Format("%d", timer.GetHour());
	 if(timer.GetMinute() < 10)		data[4].Format("0%d", timer.GetMinute());
	 else		data[4].Format("%d", timer.GetMinute());
	 if(timer.GetSecond() < 10)		data[5].Format("0%d", timer.GetSecond());
	 else		data[5].Format("%d", timer.GetSecond());
	 CString strfolder1,strfile,pathname,filename,strpathname,strCode,str;

	 strfolder1.Format("d:\\Data\\Server\\Receive\\");
	 CreateDirectory(strfolder1,NULL);//년월일
	 strfolder1.Format("d:\\Data\\Server\\Receive\\%s\\",data[0]);
	 CreateDirectory(strfolder1,NULL);//년월일
	 strfolder1.Format("d:\\Data\\Server\\Receive\\%s\\%s\\",data[0],data[1]);
	 CreateDirectory(strfolder1,NULL);//년월일
	 strfolder1.Format("d:\\Data\\Server\\Receive\\%s\\%s\\%s\\",data[0],data[1],data[2]);
	 CreateDirectory(strfolder1,NULL);//년월일
	 strfile.Format("%s*.rcv",strfolder1);

	 filename = strFullpath;
	 //file read
	 CStdioFile   file;
	 if(file.Open(filename, CFile::modeReadWrite|CFile::typeText)) {
		 file.ReadString(str);//
		 m_strCodeMsg = (str);//mt count
		 file.Close();
		 ///////////////////////////여기에 할 작업을 남긴다.
		 if(strcode == "ALARM"){//m_strCodeMsg msaage를 표시하고 알람을 울린다.
		 }
		 else if(strcode == "MODEL"){//m_strCodeMsg 모델로 모델체이지를 한다.
		 }
		 else if(strcode == "TEST"){
		 }
	 }
	 return 0;

 }



 int CVisWebView::MagImageCopy(int nLine1,int nLine2)
 {
	 CVisWebDoc	*pDoc	 = (CVisWebDoc*)GetDocument();

	 BYTE * fm1 = m_pDlgFullImage->m_pMagImage[0]->GetImagePtr();
	 BYTE * fm2 = m_pDlgFullImage->m_pMagImage[2]->GetImagePtr();
	 int x1 = nLine1 - (MAGIMAGE_X*0.5);
	 int x2 = nLine2 - (MAGIMAGE_X*0.5);
	 int x3=0,x4=0;
	 for(int y=0;y<MAGIMAGE_Y;y++){
		 x3 = x4=0;
		 for(int x=x1;x<x1+MAGIMAGE_X && x<CAM_WIDTH_CIS*3;x++,x3++)
			 *(fm1+y*MAGIMAGE_X+x3) = *(m_Inspect.m_FullImage+y*(CAM_WIDTH_CIS*3)+x);
		 for(int x=x2;x<x2+MAGIMAGE_X && x<CAM_WIDTH_CIS*3;x++,x4++)
			 *(fm2+y*MAGIMAGE_X+x4) = *(m_Inspect.m_FullImage+y*(CAM_WIDTH_CIS*3)+x);
	 }
//crop image preprocess
	 int nValue = 80, nTmp = 0,nTmp2 = 0,nCount=0,nMagnification = 1,nGap=4,nw=MAGIMAGE_X;//128
	 BYTE * fmdst = new BYTE[MAGIMAGE_X*MAGIMAGE_Y];
	 BYTE * fmdst1 = new BYTE[MAGIMAGE_X*MAGIMAGE_Y];
	 x1=MAGIMAGE_X;
	 int x0=0,y0=0,y1=MAGIMAGE_Y;
	 memset(fmdst,0,MAGIMAGE_X*MAGIMAGE_Y);
	 memset(fmdst1,0,MAGIMAGE_X*MAGIMAGE_Y);
	 double dsharp1 = 0,dsharp2=0;
	 double dmax1 = 0,dmax2=0;
	 int nx11 = (MAGIMAGE_X*0.5)-60;
	 int nx12 = (MAGIMAGE_X*0.5)+60;
//전처리를 다른방법으로 한번 더 해서 샤프니스를 하나더 구해야함.
	 for(int y=0;y<MAGIMAGE_Y;y++){
		 dmax1 = 0,dmax2=0;
		 for(int x=0;x<MAGIMAGE_X ;x++){
			 if(x>x1-nGap)	nTmp = abs(*(fm1+y*nw+x)-*(fm1+y*nw+x-nGap));
			 else			nTmp = abs(*(fm1+y*nw+x)-*(fm1+y*nw+x+nGap));
			 nTmp2 = nValue+nTmp*nMagnification;
			 if(nTmp2>255)nTmp2 = 255;if(nTmp2<0)nTmp2=0;
			 *(fmdst+y*nw+x) = nTmp2;
			 if(x>x1-nGap)	nTmp = abs(*(fm2+y*nw+x)-*(fm2+y*nw+x-nGap));
			 else			nTmp = abs(*(fm2+y*nw+x)-*(fm2+y*nw+x+nGap));
			 nTmp2 = nValue+nTmp*nMagnification;
			 if(nTmp2>255)nTmp2 = 255;if(nTmp2<0)nTmp2=0;
			 *(fmdst1+y*nw+x) = nTmp2;
			 if(x>nx11 && x<nx12){
				 if(dmax1< abs(*(fmdst+y*nw+x) - *(fmdst+y*nw+x-nGap)))
					 dmax1 = abs(*(fmdst+y*nw+x) - *(fmdst+y*nw+x-nGap));
				 if(dmax2< abs(*(fmdst1+y*nw+x) - *(fmdst1+y*nw+x-nGap)))
					 dmax2 = abs(*(fmdst1+y*nw+x) - *(fmdst1+y*nw+x-nGap));
			 }
		 }
		 dsharp1 += dmax1;
		 dsharp2 += dmax2;
	}
	
//가장큰 에지값 을 누적해서 샤프니스를 구한다.
	 if(!pDoc->m_pDlgInterface->m_bOriginImage){
		 memcpy(fm1,fmdst,MAGIMAGE_X*MAGIMAGE_Y);
		 memcpy(fm2,fmdst1,MAGIMAGE_X*MAGIMAGE_Y);
	 }
	 m_pDlgFullImage->m_dSharpness[0] = dsharp1/MAGIMAGE_Y*12;				// 20201016  kjh(*12추가)
	 m_pDlgFullImage->m_dSharpness[2] = dsharp2/MAGIMAGE_Y*12;
	 delete fmdst;
	 delete fmdst1;
	 return 0;
 }

BOOL CVisWebView::Inspect3(int nCam)
{
	nCam = 0;
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	for(int i=0;i<3;i++){
		pDoc->m_nTotalIns[i]++;
		pDoc->m_data.m_bInspectComplete[i] = TRUE;
	}
	pDoc->m_data.m_bIsDispCheck = TRUE;
	m_nSaveCheck[0] = 0;
	m_nResultOkNg = 0;
	double dLimitTimeout = 800;
	if(pDoc->m_data.m_nSubFrameCount>=18){
		pDoc->m_data.m_nSubFrameCount = 0;
	}
	m_nAlarmLog = 0;
	for(int i=0;i<20;i++)
		m_strPitchMismatch[i] = "";
	if((m_bAuto==FALSE && m_bRun==FALSE) || (m_bAuto<0 && m_bRun<0)){
		return 0;
	}
	BOOL bRet=TRUE;
	double dtmp = 0.,dtmp1 = 0.,dAve =0, dInsTime=0;
	m_nOldCount[0] = 0;//marking 전송용 불량 개수
	pDoc->m_data.m_nServerSendDefectCount = 0;
	pDoc->m_data.m_dFullTime[0*10+3] = pDoc->m_data.m_dInspDetailTime[0][1] = GetPrecisionTime();//
	CRect rtinsp;
	int nAve[3] = {0,};
	pDoc->m_data.m_bSumEdgeData = TRUE;
	for(int i=0;i<10;i++){		for(int j=0;j<MOD_COUNT;j++)pDoc->m_data.m_dAverageData1[0][j][i] = 0;}
	CString strtmp1,strtmp2 = "",strtime1,strtmp3="",strtmp4="",strtime2="";
	for(int i=0;i<pDoc->m_data.m_nNewLineCount;i++){
		strtmp1.Format("%d: %.2f \t",i+1,pDoc->m_data.m_dNewLineEdgeData1[i]);
		strtmp2 += strtmp1;
		if(i>0){
			strtmp3.Format("%d:%.2f ,",i,(pDoc->m_data.m_dNewLineEdgeData1[i]-pDoc->m_data.m_dNewLineEdgeData1[i-1])*pDoc->m_data.m_dScaleFactorX[0]);
			strtmp4 += strtmp3;
		}
	}
	strtime1.Format("%s , P:%s , %.0f ms",strtmp4,strtmp2,(pDoc->m_data.m_dInspDetailTime[0][9]-pDoc->m_data.m_dInspDetailTime[0][1])*1000);
	strtmp1.Format("%d %d : %s",pDoc->m_nTotalIns[0],pDoc->m_data.m_nNewLineCount,strtime1);
	AddtoInsLog(strtmp1);

	///에지 검출 Full Image
	int ncnt = 0,ncnt1 = 0;
	BOOL bTesting = FALSE;
	//백색 라인수 체크해서 검사 유무 확인
	if(m_nLastBrightness[0] > pDoc->m_pDlgInterface->m_nSkipPixel || pDoc->m_data.m_nWhiteLineCount[0] > pDoc->m_pDlgInterface->m_nSkipPixel )
	{
		m_bNonCoat[0] = TRUE;
		bTesting = TRUE;
		m_nRestartSkipFrame = pDoc->m_nTotalIns[0]+3;
		m_bChageShutter = FALSE;
	}
	else	m_bChageShutter = TRUE;
	if(m_bNonCoat[1]==FALSE && m_bNonCoat[0]){
		//미코팅 시작점
		//old Data reset
		SetTimer(20134,10,NULL);//capture
	}

	if (m_nRestartSkipFrame-pDoc->m_nTotalIns[0]>3)
	{
		m_nRestartSkipFrame=pDoc->m_nTotalIns[0]+1;
	}


	if(bTesting == FALSE && pDoc->m_nTotalIns[0] < m_nRestartSkipFrame)
		bTesting = TRUE;
	if(nCam==0 && bTesting==FALSE &&pDoc->m_nTotalIns[0] == m_nRestartSkipFrame+5){
		SetTimer(1267,10,NULL);
	}
	m_bNonCoat[1] = m_bNonCoat[0];

	m_nLastBrightness[0] = pDoc->m_data.m_nWhiteLineCount[0];
	m_nScratchCount = 0;
	if(pDoc->m_pDlgInterface->m_bInspect)goto DONE;
	if(bTesting==FALSE && pDoc->m_data.m_bInspStart && pDoc->m_data.m_nNewLineCount>2){// 설비 검사 Signal On
		//이전 쓰래드 살아있는지 확인
		//Line ROI 만들기
		if(pDoc->m_pDlgInterface->m_bAutoSCInspect && pDoc->m_nTotalIns[0]>10 && pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck] >10 ){//프레임수가 10프레임보다 크고 생산미터가 10미터 이상일 경우 실행.
			//
			CTime ttime = CTime::GetCurrentTime();
			CString kk12 = ttime.Format("%H:%M:%S");

			if(m_nLastLineCount[1]>0){
				CRect rttmmp11,rttmmp12;
				int nEdgeOffset1 = pDoc->m_data.m_dNewLineEdgeData1[0] - m_nLastLineCount[3];
				for(int k=0;k<m_nLastLineCount[2];k++){
					rttmmp11 = pDoc->m_data.m_rtScratch2[k];
					rttmmp11.OffsetRect(nEdgeOffset1,0);
					for(int i=0;i<pDoc->m_data.m_nNewLineCount;i++){
						if(pDoc->m_data.m_dNewLineEdgeData1[i] > rttmmp11.left && pDoc->m_data.m_dNewLineEdgeData1[i] < rttmmp11.right){
							//라인 존재함
							rttmmp11 = rttmmp11;
							int hy = CAM_HEIGHT_CIS/2;
							rttmmp12.SetRect(pDoc->m_data.m_dNewLineEdgeData1[i]-64, hy-64 ,pDoc->m_data.m_dNewLineEdgeData1[i]+64, hy+64);
							m_Inspect.ImageSelectCopy2(m_Inspect.m_FullImage,pDoc->m_data.m_pImageDefect1[0][m_nScratchCount]->GetImagePtr(),CAM_WIDTH_CIS*3,CAM_HEIGHT_CIS,rttmmp12.left,rttmmp12.right,rttmmp12.top,rttmmp12.bottom,EDGE_IMG_WIDTH,EDGE_IMG_HEIGHT,0,0);
							
							pDoc->m_data.m_rectDefect[nCam][m_nScratchCount] = rttmmp12;//pData->m_rtLineSlopeCount[nCam][ss][kk];//pData->m_rtThreadDefect[nCam][ss][kk];
							pDoc->m_data.m_nNewDefectType[nCam][m_nScratchCount] = 201;//101;//무지라인 201코팅라인 1번더미
							double dsizex,dsizey,dsize;
							CString strtemp1;
							strtemp1.Format("S/C - %s",kk12);
							BadImageShift(0,pDoc->m_data.m_pImageDefect1[0][m_nScratchCount]->GetImagePtr(),1,strtemp1);

							m_nScratchCount++;
							pDoc->m_data.m_nThreadDefectCountFull[0]++;
							if(m_nScratchCount>=5)break;
						}
						if(m_nScratchCount>=5)break;
					}
					if(m_nScratchCount>=5)break;
				}
			}
		}
		int ncheck11 = 0;
		for(int j=0;j<8;j++)//8개의 Thread
			if(m_bTestFlag[0][j]!=FALSE)
				ncheck11++;
		if(ncheck11 >= 1){
			for(int j=0;j<8;j++)//8개의 Thread
				m_bTestFlag[0][j]=FALSE;
			CString strtmp11;
			strtmp11.Format("Line Error 1");
			AddtoInsLog(strtmp11);
			goto DONE;
			//				return 0; 
		}
		double dtime = pDoc->m_data.m_dFullTime[nCam*10+4] = pDoc->m_data.m_dInspDetailTime[nCam][2] = GetPrecisionTime();
		BOOL bThread = FALSE;
		if(pDoc->m_data.m_nWhiteLineCount[nCam]<pDoc->m_pDlgInterface->m_nSkipPixel){		// 코팅이 안되어 있으면 스킵
			bThread = TRUE;
			if(!m_bIsCoatedImg){				// 20201019 kjh		코팅이 끊겼을때 마지막 데이터 write
				while(m_qLastData.size()>0){
					m_qLastData.pop();
				}
			}	
			m_bIsCoatedImg = true;
		}
		else{
			if(m_bIsCoatedImg){
				WriteLastData(m_strLotID);
			}
			m_nSkipFrame[nCam]=0;
			m_bIsCoatedImg = false;
		}
		if(m_nSkipFrame[0] <=pDoc->m_pDlgInterface->m_dSkipMeter ||m_nSkipFrame[1] <=pDoc->m_pDlgInterface->m_dSkipMeter ||m_nSkipFrame[2] <=pDoc->m_pDlgInterface->m_dSkipMeter)
			bThread = FALSE;
		//m_dSkipMeter
		if(bThread){
			if(m_avgBrightness[0] > pDoc->m_data.m_dLimitMaxBright[nCam]){
				m_nBrightcheck[nCam] = 1;
			}
			else{
				for(int k=0;k<pDoc->m_data.m_nLineCount1[nCam];k++){
					pDoc->m_data.m_rtNewInspect[k].DeflateRect(pDoc->m_data.m_nEdgeOffset,0);
				}
				//flag check
				int ncheckcnt = 0,ncheckcnt1 = 0;
				for(int l=0;l<8;l++){
					if(m_bTestFlag[nCam][l])
						ncheckcnt++;
				}
				pDoc->m_data.m_nKillFunction[nCam] = 0;
				if(ncheckcnt >0 || ncheckcnt1>0){
					CString strtmp12;
					strtmp12.Format("%d-%d -TestInsp:%d,RoiInsp:%d",nCam,pDoc->m_nTotalIns[nCam],ncheckcnt,ncheckcnt1);
					AddtoList(strtmp12,0);
					m_nThreadcheck[0]=m_nThreadcheck[1]=m_nThreadcheck[2] = 1;
					pDoc->m_data.m_nKillFunction[nCam] = 1;
					goto DONE;
					//return 0; 

				}
				for(int l=0;l<8;l++){
					m_bTestFlag[nCam][l] = TRUE;//에지검사 스타트 //test inspect
				}

				//thread 분기
				BOOL bTesting = TRUE;
				if(!pDoc->m_pDlgInterface->m_bPreprocessing)bTesting = FALSE;
				while(1)
				{//2번 카메라의 평균 밝기로 검사 유무 판다.
					if(m_avgBrightness[0] > 0 &&m_avgBrightness[0] >=  pDoc->m_data.m_dLimitMaxBright[0]){// ||nAve <=  pDoc->m_data.m_dLimitMinBright[cam])
						m_nAlarmEndFRame = 0;
						m_bAlarmOnOff = FALSE;
						m_IO[0].WriteOutputPort(0,0,FALSE);
						AddtoList("Product Change1 Off",0,TRUE);
						m_nBrightcheck[nCam] = 1;
						break;
					}
					if(bTesting){
						if(	m_bTestFlag[nCam][0]==0 && m_bTestFlag[nCam][1]==0&&m_bTestFlag[nCam][2]==0 && m_bTestFlag[nCam][3]==0&& m_bTestFlag[nCam][4]==0&& m_bTestFlag[nCam][5]==0&& m_bTestFlag[nCam][6]==0&& m_bTestFlag[nCam][7]==0)
							break;//
						//							m_bPreprocessing[nCam][0]==FALSE  &&m_bPreprocessing[nCam][1]==FALSE &&m_bPreprocessing[nCam][2]==FALSE &&m_bPreprocessing[nCam][3]==FALSE &&m_bPreprocessing[nCam][4]==FALSE &&m_bPreprocessing[nCam][5]==FALSE &&m_bPreprocessing[nCam][6]==FALSE &&m_bPreprocessing[nCam][7]==FALSE ){
					}
					Wait(1);
					double dtime1 =  GetPrecisionTime();
					if((dtime1-dtime)*1000 >dLimitTimeout)
					{
						m_nInspBreak[nCam] += 100;

						break;
					}
				}
			}

			pDoc->m_data.m_dFullTime[nCam*10+5] = pDoc->m_data.m_dInspDetailTime[nCam][3] = GetPrecisionTime();
			//		m_Inspect.GetDataSort(pDoc->m_pImage,&pDoc->m_data,0);//Line Code insert //m_dLineEdgeData1if(nc
				m_Inspect.GetLineDataSortNew(m_Inspect.m_FullImage,&pDoc->m_data,nCam,pDoc->m_nTotalIns[0]);//Line Code insert //m_dLineEdgeData1  //defect 이미지 정리

			pDoc->m_data.m_dFullTime[nCam*10+6] = pDoc->m_data.m_dInspDetailTime[nCam][4] = GetPrecisionTime();
		}

			if(pDoc->m_data.m_nServerSendDefectCount)		bRet=FALSE;
			else											bRet=TRUE;
			
			// 20201020 kjh 카메라 오염 체크
			int nDist = 0;
			if(m_strComputerName.Mid(8,1)=="H" && m_strComputerName.Mid(9,1)=="T")
				nDist = 5;
			else if(m_strComputerName.Mid(8,1)=="H" && m_strComputerName.Mid(9,1)=="B")
				nDist = pDoc->m_pDlgInterface->m_dTopBackDistance + 5;
			else if(m_strComputerName.Mid(8,1)=="M")
				nDist = pDoc->m_pDlgInterface->m_dTopBackDistance*2 + 5;

			if(m_nCoatingOn == 0 && m_nNonCoatStartMeter+nDist < pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck]){
				if(pDoc->m_data.m_dNewLineEdgeData1[2]-pDoc->m_data.m_dNewLineEdgeData1[1] > 0){
						m_bAlarmOnOff = TRUE;
						int ntmpmeter = pDoc->m_nTotalIns[0]+4;
						if(m_nAlarmEndFRame<ntmpmeter)
							m_nAlarmEndFRame = ntmpmeter;
						m_strAlarmMsg = "camera contamination"; // 카메라 오염
						m_strAlarmMsg1.Format("%d M", pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck]) ;

						AddtoList(m_strAlarmMsg,0,TRUE);
						m_nAlarmLog += 4;
					}
				
			}
	}
	else{	// 설비 검사 Signal Off
		pDoc->m_data.m_nLineCount1[nCam] = 0;
//		RectInvalidate(10);
		Wait(10);
		if(1){
			CString strttp1;
			strttp1.Format("Skip %d, %d,L %d",m_nRestartSkipFrame,pDoc->m_nTotalIns[nCam],pDoc->m_data.m_nNewLineCount);
			AddtoList(strttp1,0,0);

		}
		for(int i2=0;i2<20;i2++)
		{
			pDoc->m_data.m_rtOldCoatChar[i2].SetRect(0,0,0,0);
			pDoc->m_data.m_rtCoatChar[i2].SetRect(0,0,0,0);
			m_lbCoatLen[i2].ShowWindow(0);
		}
		if(pDoc->m_pDlgInterface->m_bOriginImage==FALSE){
// 			if(nCam==0)		memcpy(pDoc->m_pImage->GetImagePtr(),m_Inspect.m_fmPreprocess[nCam],CAM_WIDTH_CIS*CAM_HEIGHT_3072);
// 			else if(nCam==1)memcpy(pDoc->m_pImage1->GetImagePtr(),m_Inspect.m_fmPreprocess[nCam],CAM_WIDTH_CIS*CAM_HEIGHT_3072);
// 			else			memcpy(pDoc->m_pImage2->GetImagePtr(),m_Inspect.m_fmPreprocess[nCam],CAM_WIDTH_CIS*CAM_HEIGHT_3072);
		}
		if(!m_bDrawStats)
			DrawImage(4);
		return 0;
	}

DONE:
	pDoc->m_data.m_dFullTime[nCam*10+7] = pDoc->m_data.m_dInspDetailTime[nCam][5] = GetPrecisionTime();
	if( m_nBrightcheck[0] == 1 && m_avgBrightness[0] < pDoc->m_data.m_dLimitMaxBright[nCam] ){
		if(1){
			m_nBrightcheck[0]=m_nBrightcheck[1]=m_nBrightcheck[2] = 0;
			m_nAlarmEndFRame = 0;
			m_bAlarmOnOff = FALSE;
			m_IO[0].WriteOutputPort(0,0,FALSE);

			AddtoList("Product Change2 Off",0,TRUE);

			SetTimer(12011,2000,NULL);//redraw invalidate
			for(int n1 =0;n1<10;n1++)
				for(int k1 =0;k1<MAX_LENGTH;k1++)
					pDoc->m_data.m_dLineAve[n1][k1] = 0;
			for(int k1=0;k1<MAX_CAMERAS;k1++)
				for(int k2=0;k2<40;k2++)
					pDoc->m_data.m_dOldLine[k1][k2] = 0;
		}
	}
// 	else if(nCam==2 && m_nSkipFrame[0] == pDoc->m_pDlgInterface->m_dSkipMeter+1){
// 		SetTimer(12011,2000,NULL);//redraw invalidate
//	}
	if(m_avgBrightness[0] > pDoc->m_data.m_dLimitMaxBright[0] || pDoc->m_data.m_nWhiteLineCount[nCam]>pDoc->m_pDlgInterface->m_nSkipPixel){
		//			GetDlgItem(IDC_DETAIL_LINE)->Invalidate();
		m_nDisplayDraw = 1;
		m_nAlarmEndFRame = 0;
		m_bAlarmOnOff = FALSE;
		m_IO[0].WriteOutputPort(0,0,FALSE);
		AddtoList("Product Change3 Off",0,TRUE);
		for(int n1 =0;n1<10;n1++)
			for(int k1 =0;k1<MAX_LENGTH;k1++)
				pDoc->m_data.m_dLineAve[n1][k1] = 0;
		if(!m_bDrawStats)
			DrawImage(3);
		//io 추가 이재능 끄기
		m_IO[0].WriteOutputPort(0,2,FALSE);
	}
	else{
		{
			//io 추가 이재능  켜기
			m_IO[0].WriteOutputPort(0,2,TRUE);

				//절연이 끝났는지 체크한다
				if(m_nMachine == 0)InsulateDefectCheck();
				SummaryEdgeData();//pixel pos를 mm로 변환.여기서 텍스트 저장  라인에 대해서만 체크한다.
				if(m_nOldLine==-1){
					CString strtmp11;
					strtmp11.Format("Line Error 3");
					AddtoInsLog(strtmp11);
					return 0;
				}
				CString stttmp;
				stttmp.Format("%d Cam0 Summary",pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck]);
				//					AddtoInsLog(stttmp);

			//불량 영상 저장 및 개별 텍스트 기록
				int ntmp1 = DataResultSaveFull(0);//nCam);//여기서 디펙이미지저장 //BroadCasting(bRet,cam);//서버가 없음.이거 필요없음. 
				UpdateControl();//불량 개수 업데이트 

			pDoc->m_data.m_dFullTime[nCam*10+8] = pDoc->m_data.m_dInspDetailTime[nCam][6] = GetPrecisionTime();//0-9-1-5-7

			if(!m_bDrawStats)
			{
				CString stttmp;
				stttmp.Format("%d DrawImage1",pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck]);
				//					AddtoInsLog(stttmp);
				DrawImage(3);
			}
		}

		pDoc->m_data.m_dInspDetailTime[nCam][7] = GetPrecisionTime();//0-9-1-5-7 9-0버퍼카피  1-9라인서치  5-1디펙검사 7-5드로우 서마리

		pDoc->m_data.m_dInspTime[nCam]=dInsTime = pDoc->m_data.m_dInspDetailTime[nCam][7]-pDoc->m_data.m_dInspDetailTime[nCam][0];
	}

	//Buffer copy Time5
	m_nSkipFrame[0]++;
	m_nSkipFrame[1]=m_nSkipFrame[2]=m_nSkipFrame[0];
// 	if(pDoc->m_pDlgInterface->m_bLastData)
// 		m_DlgLastData->LastDataShow(m_strLastCoatWidth,m_strLastNonCoatWidth);

	CString strtime;//reverse X 50ms소요 ,,,, memcpy 8ms

	strtime.Format("Pixel %d, %d, %d",pDoc->m_data.m_nWhiteLineCount[0],pDoc->m_data.m_nWhiteLineCount[1],pDoc->m_data.m_nWhiteLineCount[2]);
	AddtoInsLog(strtime);
	strtime.Format("%dLine %d, %d, %d  - %s",pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck],pDoc->m_data.m_nLineCount1[0],pDoc->m_data.m_nLineCount1[1],pDoc->m_data.m_nLineCount1[2],m_strLotID);
//	AddtoInsLog(strtime);
	strtmp2="";
	for(int i=0;i<pDoc->m_data.m_nNewLineCount;i++){
		strtmp1.Format("%d : %.2f \t",i+1,pDoc->m_data.m_dNewLineEdgeData1[i]);
		strtmp2 += strtmp1;
	}
	strtime.Format("Pixel %s",strtmp2);
	if(	m_nInspBreak[0]||m_nInspBreak[1]||m_nInspBreak[2]){
		strtime.Format("%dTimeOut %d, %d, %d",pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck],	m_nInspBreak[0],m_nInspBreak[1],m_nInspBreak[2]);
		AddtoInsLog(strtime);
	}

	strtime.Format("%d-Time %.0f (b:%.0f,L:%.0f,d1:%.0f,d2:%.0f",pDoc->m_nTotalIns[0],pDoc->m_data.m_dInspTime[0]*1000,
		( pDoc->m_data.m_dInspDetailTime[nCam][9]-pDoc->m_data.m_dInspDetailTime[nCam][0])*1000,( pDoc->m_data.m_dInspDetailTime[nCam][1]-pDoc->m_data.m_dInspDetailTime[nCam][9])*1000,
		( pDoc->m_data.m_dInspDetailTime[nCam][5]-pDoc->m_data.m_dInspDetailTime[nCam][1])*1000,( pDoc->m_data.m_dInspDetailTime[nCam][7]-pDoc->m_data.m_dInspDetailTime[nCam][5])*1000);
	AddtoInsLog(strtime);


	BOOL bAnode = TRUE;
	
	if(m_bAlarmOff==FALSE && pDoc->m_pDlgInterface->m_bAlarm && m_nAlarmEndFRame > pDoc->m_nTotalIns[nCam] ){
		if(m_bNewAlarm && m_nNewAlarm>0){
			m_strAlarmMsg = "Mismatch";
			m_strAlarmMsg1.Format("%d M", pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck]) ;

			CString stralarm;
			stralarm.Format("Spec Alram On %d",m_nAlarmLog);//0 폭 /
			AddtoList(stralarm,0,TRUE);
			m_nAlarmOn = 1;
			if(m_AlarmDlg->IsWindowVisible()){
			}
			else{
				m_nAlarmCnt1 = 0;
				m_AlarmDlg->ShowWindow(1);
				SetTimer(20218,500,NULL);
			}
		}
		else{
			//nMeter =pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck]
			m_nNewAlarm = 0;
			m_IO[0].WriteOutputPort(0,0,TRUE);
			CString stralarm;
			stralarm.Format("Alarm On %d",m_nAlarmLog);//0 폭 /
			AddtoList(stralarm,0,TRUE);
			m_nAlarmOn = 1;
			m_AlarmDlg->ShowWindow(1);
			SetTimer(20219,500,NULL);
		}
	}
	else{
		KillTimer(20219);
		m_nNewAlarm = 0;
		m_strAlarmMsg = "";
		m_strAlarmMsg1= "" ;

		m_nAlarmEndFRame = 0;
		m_bAlarmOnOff = FALSE;
		m_bNewAlarm = FALSE;
		KillTimer(20218);
		if(m_nAlarmOn==1)
			AddtoList("Alarm Off",0,TRUE);
		m_IO[0].WriteOutputPort(0,0,FALSE);
		m_nAlarmOn = 0;
		m_AlarmDlg->ShowWindow(0);

	}
	if(m_strComputerName.Mid(9,1)=="B"){//m_strComputerName.Mid(8,1)=="M"
		if(m_pMeterData->IsWindowVisible()){
			CString str;
			int nlen1 = pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck];
			int nc12 = 0;
			for(int i=nlen1-5;i<nlen1+5;i++){
				if(nc12>10)break;
				int ntmplen = ((i+1000) - pDoc->m_pDlgInterface->m_nHeadMisDistance)%100;
				if(m_strComputerName.Mid(8,1)=="H") 
					ntmplen = ((i+1000) - int(pDoc->m_pDlgInterface->m_dTopBackDistance))%100;
				CString strtmp14;
				strtmp14.Format("%d - %s",i,pDoc->m_data.m_strFullLineData[ntmplen]);
				m_pMeterData->m_lbMeterData[nc12%10].SetText(strtmp14);
				nc12++;

			}
		}
	}



	//save전 flag 초기화
	m_bWaitThread[nCam]=FALSE;
	for(int i=0;i<6;i++)	for(int j=0;j<CAM_WIDTH_CIS;j++)		m_nLineProjData[i][j] = 0;

//	memset(m_Inspect.m_fmPreprocess[nCam],0,CAM_WIDTH_CIS*CAM_HEIGHT_3072);
	//ljn 190401
	if(m_strLotID != "NONE"){
		if(pDoc->m_pDlgInterface->m_bFullImageSave ){
			{
				m_eSaveImageCam2.SetEvent();m_eSaveImageCam3.SetEvent();m_eSaveImage.SetEvent();
			}
		}
		else if(m_nResultOkNg==1)//불량 영상만 저장 //3개 셋트로 저장
		{
			m_eSaveImageCam2.SetEvent();
			m_eSaveImageCam3.SetEvent();
			m_eSaveImage.SetEvent();
		}
	}

	m_nThreadcheck[nCam] = 0;
	m_bTestInspect[nCam]= FALSE;
	return 0;
}

int CVisWebView::DataResultSaveFull(int nCam)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CString strsrc1,strsrc2,strdst1,strdst2,strtmp,strLot;
	int nDefect = 0,nret=0;
	CTime ttime = CTime::GetCurrentTime();
	CString kk = ttime.Format("[%H-%M-%S]");
	CString kk12 = ttime.Format("%H:%M:%S");
	CString kk1 = ttime.Format("%Y%m%d");
	CString strsave,strsave1,strpath,strsave2,strsave3,strpath1;
	strLot = ConvertCharToStr(cLotID);
	if(strLot =="")
		strLot = "NONE";
	CString data[6];
	CTime timer=CTime::GetCurrentTime();	
	data[0].Format("%d", timer.GetYear());
	if(timer.GetMonth() < 10)		data[1].Format("0%d", timer.GetMonth());
	else		data[1].Format("%d", timer.GetMonth());
	if(timer.GetDay() < 10)		data[2].Format("0%d", timer.GetDay());
	else		data[2].Format("%d", timer.GetDay());
	if(timer.GetHour() < 10)		data[3].Format("0%d", timer.GetHour());
	else		data[3].Format("%d", timer.GetHour());
	if(timer.GetMinute() < 10)		data[4].Format("0%d", timer.GetMinute());
	else		data[4].Format("%d", timer.GetMinute());
	if(timer.GetSecond() < 10)		data[5].Format("0%d", timer.GetSecond());
	else		data[5].Format("%d", timer.GetSecond());

	//frame별 max data 뽑기
	//data 초기화
	for(int i=0;i<10;i++)			pDoc->m_data.m_dAverageData[i] = 0;
	pDoc->m_data.m_dAverageData[3] =pDoc->m_data.m_dAverageData[1] = 255;

	for(int i=0;i<MOD_COUNT;i++){
		for(int j=0;j<6;j++){
			if(j==0 || j==2 || j==4){
				if(pDoc->m_data.m_dAverageData[j]<pDoc->m_data.m_dAverageData1Full[i][j])pDoc->m_data.m_dAverageData[j]=pDoc->m_data.m_dAverageData1Full[i][j];
			}
			else{
				if(pDoc->m_data.m_dAverageData[j]>pDoc->m_data.m_dAverageData1Full[i][j])pDoc->m_data.m_dAverageData[j]=pDoc->m_data.m_dAverageData1Full[i][j];
			}
		}
	}
	
// 	if(pDoc->m_data.m_bUseCLog){
// 		strpath.Format("c:\\Glim\\LOTdata\\");
// 		CreateDirectory(strpath,NULL);
// 		strpath.Format("c:\\Glim\\LOTdata\\%s\\",kk1);
// 		CreateDirectory(strpath,NULL);
// 		strpath.Format("c:\\Glim\\LOTdata\\%s\\%s\\",kk1,strLot);
// 		CreateDirectory(strpath,NULL);
// 		strpath.Format("c:\\Glim\\LOTdata\\%s\\%s\\%s\\",kk1,strLot,pDoc->m_data.m_strComName);
// 		CreateDirectory(strpath,NULL);
// 	}
//	else{
		strpath.Format("D:\\Data\\LOTdata\\");
		CreateDirectory(strpath,NULL);
		strpath.Format("D:\\Data\\LOTdata\\%s\\",kk1);
		CreateDirectory(strpath,NULL);
		strpath.Format("D:\\Data\\LOTdata\\%s\\%s\\",kk1,strLot);
		CreateDirectory(strpath,NULL);
		strpath.Format("D:\\Data\\LOTdata\\%s\\%s\\%s\\",kk1,strLot,pDoc->m_data.m_strComName);
		CreateDirectory(strpath,NULL);
		if(pDoc->m_data.m_nCamID==2)//top
			strpath1.Format("D:\\Data\\LotComplete\\%s\\%s\\%s\\%s\\HeadTop",data[0],data[1],data[2],strLot);
		else if(pDoc->m_data.m_nCamID==3)//back
		{
			strpath1.Format("D:\\Data\\LotComplete\\%s\\%s\\%s\\%s\\HeadBack",data[0],data[1],data[2],strLot);
			CreateDirectory(strpath1,NULL); 
		}
		else if(pDoc->m_data.m_nCamID==4)//mis top
			strpath1.Format("D:\\Data\\LotComplete\\%s\\%s\\%s\\%s\\MisTop",data[0],data[1],data[2],strLot);
		else if(pDoc->m_data.m_nCamID==5)//mis back
			strpath1.Format("D:\\Data\\LotComplete\\%s\\%s\\%s\\%s\\MisBack",data[0],data[1],data[2],strLot);
//	}
	//	strpath.Format("C:\\Glim\\LotData\\%s%s%s\\%s\\",data[0],data[1],data[2],pDoc->m_str_lot);



	int nMeter = pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck];

	if((nMeter>10 && nMeter<20) || m_strOldTime=="")
		m_strOldTime = kk1;
	if(nMeter>50 && nMeter<200)
		m_strOldPath = "";
	int nBad[10] = {0,};
	//Defect Type
	//bad image save
	//먼저 부루량 갯수부터 파악
	int nBadCount = 0,nBadCount1=0;
	nBadCount = pDoc->m_data.m_nRealDefectCountFull;
	pDoc->m_data.m_nSumBadCount[pDoc->m_data.m_nCamID] += nBadCount;
	for(int k=0;k<MOD_COUNT;k++){
		for(int i=0; i<pDoc->m_data.m_nThreadDefectCountFull[k]; i++)
		{
			nret=1;
			m_nResultOkNg = 1;
			if(i >= MAX_REALDEFECT-1) break;
			int ndefectposx = pDoc->m_data.m_rtThreadDefectFull[k][i].left+(pDoc->m_data.m_rtThreadDefectFull[k][i].Width()*0.5);
			if(ndefectposx<=0)continue;

			int nLane = pDoc->m_data.LaneCheckFull(0,ndefectposx,0,pDoc->m_data.m_nEpcPos);
			CPoint ptPos = pDoc->m_data.m_rtThreadDefectFull[k][i].CenterPoint();
			double dpos[2];
			dpos[0] = (ptPos.x) * pDoc->m_data.m_dScaleFactorX[0];//poㄴY
			dpos[1] = ptPos.y * pDoc->m_data.m_dScaleFactorY[0];
			strsave2.Format("Defect_%06d_%02d_%d_%d.bmp",pDoc->m_nTotalIns[0],i+1,pDoc->m_data.m_nNewDefectTypeFull[k][i],nMeter);
			strsave1.Format("%sDefect_%06d_%02d_%d_%d.bmp",strpath,pDoc->m_nTotalIns[0],i+1,pDoc->m_data.m_nNewDefectTypeFull[k][i],nMeter);
			strsave3.Format("%sDefect_%06d_%02d_%d_%d.bmp",strpath1,pDoc->m_nTotalIns[0],i+1,pDoc->m_data.m_nNewDefectTypeFull[k][i],nMeter);
			pDoc->m_data.m_strDefectNameFull[k][i]=strsave1;
			pDoc->m_data.m_strNewDefectNameFull[k][i] = GetDefectType(pDoc->m_data.m_nNewDefectTypeFull[k][i]);

			if(nLane>0){
				if(pDoc->m_data.m_nNewDefectTypeFull[k][i]==101 || pDoc->m_data.m_nNewDefectTypeFull[k][i]==1001 || pDoc->m_data.m_nNewDefectTypeFull[k][i]==1002 ){
					pDoc->m_data.m_nLaneDefectCount[nLane-1][0]++;
				}
				else{
					pDoc->m_data.m_nLaneDefectCount[nLane-1][1]++;
				}
			}

			//bad write //20190414
			double dpx,dpy;
			dpx = pDoc->m_data.m_rtThreadDefectFull[k][i].left*pDoc->m_data.m_dScaleFactorX[0] - (pDoc->m_data.m_dNewLineEdgeData1[0]*pDoc->m_data.m_dScaleFactorX[0]);
			dpy = pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck] + (pDoc->m_data.m_rtThreadDefectFull[k][i].top*pDoc->m_data.m_dScaleFactorY[0])/1000;
			//MODEL,color,gain,size,maxgray,mingray,avegray,검출값,
			CString strcolor,strmodel;
			strmodel = pDoc->m_data.m_strDefaultModel;
			if(pDoc->m_data.m_nNewDefectTypeFull[k][i]==201 ||pDoc->m_data.m_nNewDefectTypeFull[k][i]==1001 ||pDoc->m_data.m_nNewDefectTypeFull[k][i]==3001 )
				strcolor = "BLACK";
			else strcolor = "WHITE";
			double dgain = 0.0;
			double dsize1 = (pDoc->m_data.m_dSizeXFull[k][i]*pDoc->m_data.m_dSizeYFull[k][i])*0.5;
			double dmaxgray = pDoc->m_data.m_dDefectValueFull[k][i][2]+abs(pDoc->m_data.m_dDefectValueFull[k][i][1]);
			if(dmaxgray>255)dmaxgray = 255;
			double dmingray = pDoc->m_data.m_dDefectValueFull[k][i][2]- abs(pDoc->m_data.m_dDefectValueFull[k][i][0]);
			if(dmingray<0)dmingray = 0;
			double davegray = pDoc->m_data.m_dDefectValueFull[k][i][2];
			double dThvalue = abs(pDoc->m_data.m_dLineEdgeValueFull[k][i]);
			SYSTEMTIME stime1;
			GetLocalTime(&stime1);
			CString strLocaltime;
			strLocaltime.Format("%04d%02d%02d%02d%02d%02d%03d",
				stime1.wYear,
				stime1.wMonth,
				stime1.wDay,
				stime1.wHour,
				stime1.wMinute,
				stime1.wSecond,
				stime1.wMilliseconds);

			if(m_strComputerName.Find("CHO")<1)
				WriteDefectData(strLot, dpy,dpx, pDoc->m_data.m_dSizeXFull[k][i],pDoc->m_data.m_dSizeYFull[k][i], pDoc->m_data.m_dLineEdgeValueFull[k][i],pDoc->m_data.m_strNewDefectNameFull[k][i],strsave1,strsave2,strsave3,
				strmodel,strcolor,dgain,dsize1,dmaxgray,dmingray,davegray,dThvalue,strLocaltime);
			//WriteDefectData(strLot, dpy,dpx, pDoc->m_data.m_dSizeX[k1][i],pDoc->m_data.m_dSizeY[k1][i], pDoc->m_data.m_nDefectVMax[k1][i],pDoc->m_data.m_strNewDefectName[k1][i],strsave1,strsave2,strsave3);
			//			fnWriteData(strLot,pDoc->m_nTotalIns[0],nBadCount1,pDoc->m_data.fpDefectType[k1][i],dpx,dpy,pDoc->m_data.m_dSizeX[k1][i],pDoc->m_data.m_dSizeY[k1][i],"",0,0,
			//				double(pDoc->m_data.fpDefectVMax[k1][i]),double(pDoc->m_data.fpDefectVMin[k1][i]),pDoc->m_data.m_dAvgBrightness[k1],0,k1);
			if(pDoc->m_pDlgInterface->m_bServerDataSend)
				WriteDefectDataServerSend(strLot, dpy,dpx, pDoc->m_data.m_dSizeXFull[k][i],pDoc->m_data.m_dSizeYFull[k][i], pDoc->m_data.m_dLineEdgeValueFull[k][i],pDoc->m_data.m_strNewDefectNameFull[k][i],strsave1,strsave2,strsave3,pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck],
				strmodel,strcolor,dgain,dsize1,dmaxgray,dmingray,davegray,dThvalue,strLocaltime,pDoc->m_data.m_nCamID);

			//server send
			if(pDoc->m_pDlgInterface->m_bServerDataSend){

			}
			CString str1;
			str1.Format("%s - %s\n%04dM, Lane:%d \n%.2f , %d",pDoc->m_data.m_strNewDefectNameFull[k][i],kk12,pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck],nLane,pDoc->m_data.m_dSizeFull[k][i],pDoc->m_data.m_dLineEdgeValueFull[k][i]);
			if(nBadCount>10){
				if(i%3==0)
					BadImageShift(0,pDoc->m_data.m_pImageDefectFull[k][i]->GetImagePtr(),1,str1);
			}
			else
				BadImageShift(0,pDoc->m_data.m_pImageDefectFull[k][i]->GetImagePtr(),1,str1);
			nBadCount1++;
			if(m_dRemainMainSpace>5 ){
				pDoc->m_data.m_pImageDefectFull[k][i]->Save(strsave1);
			}
			// 			if(nDefect == 101)str.Format("NC-Line");
			// 			else if(nDefect == 201)str.Format("C-Line");//c
			// 			else if(nDefect == 1001)str.Format("Island");//n
			// 			else if(nDefect == 1002)str.Format("DragLine");//n
			// 			else if(nDefect == 2001)str.Format("Pinhole");//c
			// 			else if(nDefect == 3001)str.Format("C-Line");
			// 			else if(nDefect == 4001)str.Format("C-Line");
			// 			else if(nDefect == 7001)str.Format("Edge Spur");
			// 			else					str.Format("PinHole");
			//부량 카운트
			if(pDoc->m_pDlgInterface->m_bEngKor){
				if(pDoc->m_data.m_strNewDefectNameFull[k][i].Find("Pinhole")>=0){
					pDoc->m_data.m_nBadTypeCount[5]++;nBad[5]++;}
				else if(pDoc->m_data.m_strNewDefectNameFull[k][i].Find("Line")>=0){		
					pDoc->m_data.m_nBadTypeCount[1]++;nBad[1]++;}
				else if(pDoc->m_data.m_strNewDefectNameFull[k][i].Find("Line")>=0){
					pDoc->m_data.m_nBadTypeCount[4]++;nBad[4]++;}
				else if(pDoc->m_data.m_strNewDefectNameFull[k][i].Find("Island")>=0){
					pDoc->m_data.m_nBadTypeCount[2]++;nBad[2]++;}
				else if(pDoc->m_data.m_strNewDefectNameFull[k][i].Find("Drag")>=0 ){
					pDoc->m_data.m_nBadTypeCount[0]++;nBad[0]++;}
				else if(pDoc->m_data.m_strNewDefectNameFull[k][i].Find("Chipping")>=0){
					pDoc->m_data.m_nBadTypeCount[3]++;nBad[3]++;}
				else
					pDoc->m_data.m_nBadTypeCount[5]++;

			}
			else{
				if(pDoc->m_data.m_strNewDefectNameFull[k][i].Find("핀홀")>=0){
					pDoc->m_data.m_nBadTypeCount[5]++;nBad[5]++;}
				else if(pDoc->m_data.m_strNewDefectNameFull[k][i].Find("라인")>=0){
					pDoc->m_data.m_nBadTypeCount[1]++;nBad[1]++;}
				else if(pDoc->m_data.m_strNewDefectNameFull[k][i].Find("라인")>=0){
					pDoc->m_data.m_nBadTypeCount[4]++;nBad[4]++;}
				else if(pDoc->m_data.m_strNewDefectNameFull[k][i].Find("아일랜드")>=0){
					pDoc->m_data.m_nBadTypeCount[2]++;nBad[2]++;}
				else if(pDoc->m_data.m_strNewDefectNameFull[k][i].Find("드래그")>=0){
					pDoc->m_data.m_nBadTypeCount[0]++;nBad[0]++;}
				else if(pDoc->m_data.m_strNewDefectNameFull[k][i].Find("파인")>=0){
					pDoc->m_data.m_nBadTypeCount[3]++;nBad[3]++;}
				else
					pDoc->m_data.m_nBadTypeCount[5]++;
			}

		}
	}
	if(nBadCount>0){
		//wrtie ng count
		WrtieDefectCount(pDoc->m_data.m_nSumBadCount[pDoc->m_data.m_nCamID],strLot);
	}

	if(pDoc->m_data.m_nInsulateDefectCount>0){
		for(int i=0;i<pDoc->m_data.m_nInsulateDefectCount;i++){
			CString str1;
			str1.Format("%s\n%.2f","절연",0.0);
			if(pDoc->m_data.m_nInsulateDefectCount>10){
				if(nBadCount-nBadCount1<9 && nBadCount-nBadCount1>=0)
					BadImageShift(0,pDoc->m_data.m_pImageDefectInsulate[i]->GetImagePtr(),1,str1);
			}
			else
				BadImageShift(0,pDoc->m_data.m_pImageDefectInsulate[i]->GetImagePtr(),1,str1);

		}
	}

	//if(nBadCount> pDoc->m_pDlgInterface->m_nBadFrameInDefect)
	if(pDoc->m_pDlgInterface->m_bDefectNgFrame && pDoc->m_pDlgInterface->m_bAlarm)
	{
		m_nNgFrameCount[pDoc->m_nTotalIns[0]%100] += nBadCount1;
		double dFrameHeight = 1000 /(pDoc->m_data.m_dScaleFactorY[0]*CAM_HEIGHT_3072);
		int nf1 = dFrameHeight * pDoc->m_pDlgInterface->m_nBadFrameInCount;
		//m_nBadFrameInCount

		m_nNgFrameCount[(pDoc->m_nTotalIns[0]+10000-nf1)%100] = 0;
	}
	else
		m_nNgFrameCount[pDoc->m_nTotalIns[0]%100] =0;
	if(pDoc->m_pDlgInterface->m_bNgFrameInCount && pDoc->m_pDlgInterface->m_bAlarm){//연셕ㅇ;물
		//dusthr qnffid
		//m_nContinueBadcnt//m_nContinueBadFrame
		if(nBadCount>pDoc->m_pDlgInterface->m_nContinueBadcnt)
			m_nContinueCnt++;
		else
			m_nContinueCnt=0;
		if(m_nContinueCnt>pDoc->m_pDlgInterface->m_nContinueBadMeter){//Meter로 변환
			m_bAlarmOnOff = TRUE;
			int ntmpmeter = pDoc->m_nTotalIns[0]+4;
			if(m_nAlarmEndFRame<ntmpmeter)
				m_nAlarmEndFRame = ntmpmeter;
			m_strAlarmMsg = "Defect";//연속이물
			m_strAlarmMsg1.Format("%d M", pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck]) ;

			AddtoList("Alarm Continuous Defect!",0,TRUE);
			m_nAlarmLog += 4;
		}

	}
	if(pDoc->m_pDlgInterface->m_bDefectNgFrame && pDoc->m_pDlgInterface->m_bAlarm){
		int nNgcnt = 0;
		int ntmpframe = pDoc->m_nTotalIns[0]%100+1000;
		int nFrameHeight = 1000 /(pDoc->m_data.m_dScaleFactorY[0]*CAM_HEIGHT_3072);
		if(pDoc->m_pDlgInterface->m_nBadNgFrame>999)pDoc->m_pDlgInterface->m_nBadNgFrame = 999;

		for(int nf = ntmpframe;nf>ntmpframe-pDoc->m_pDlgInterface->m_nBadNgFrame*nFrameHeight  ;nf--){
			if(nf<0)break;
			if(m_nNgFrameCount[nf%100]>0)nNgcnt++;
		}
		if(nNgcnt>pDoc->m_pDlgInterface->m_nBadFrameInCount*nFrameHeight && pDoc->m_pDlgInterface->m_bAlarm){
			//Alaram on
			m_bAlarmOnOff = TRUE;
			int ntmpmeter =pDoc->m_nTotalIns[0]+4;
			if(m_nAlarmEndFRame<ntmpmeter)
				m_nAlarmEndFRame = ntmpmeter;
			m_nAlarmLog += 8;
			m_strAlarmMsg = "defect";//"구간이물";
			m_strAlarmMsg1.Format("%d M", pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck]) ;

			AddtoList("Alarm Interval Defect!",0,TRUE);

		}
		//		for(int l1 = pDoc->m_nTotalIns[0]-(ntmpframe-pDoc->m_pDlgInterface->m_nBadNgFrame*nFrameHeight)+1000;l1> pDoc->m_nTotalIns[0]+1000 )
		m_nNgFrameCount[((1000+pDoc->m_nTotalIns[0]) - ntmpframe-pDoc->m_pDlgInterface->m_nBadNgFrame*nFrameHeight)%100]  = 0;
	}

	// 20201022 kjh meter ratio defect
	METER_RATIO_DEFECT meterRatio;
	int nDefectMeterCount = 0, nMeterCount = 0;
	bool bDefectInInterval = false;

	if(m_SysParam->m_bMeterRatioDefect && pDoc->m_pDlgInterface->m_bAlarm){
		meterRatio.nMeter = pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck];
		if(pDoc->m_data.m_nRealDefectCountFull>0)
			meterRatio.bDefect = true;
		if(m_listMeterRatio.size()>0){					// 데이터가 있는경우 설정된 total meter 이내인지 확인하고 push
			/*if*/while(meterRatio.nMeter - m_listMeterRatio.front().nMeter > m_SysParam->m_nMeterRatioTotalM){
					m_listMeterRatio.pop_front();
					if(m_listMeterRatio.size() == 0)
						break;
				//	m_listMeterRatio.push_back(meterRatio);
			}
			/*else*/							
			m_listMeterRatio.push_back(meterRatio);		
		}
		else
			m_listMeterRatio.push_back(meterRatio);	// 데이터가 없는경우 바로 push

		// count check
		std::list<METER_RATIO_DEFECT>::iterator iter;
		for (iter = m_listMeterRatio.begin(); iter != m_listMeterRatio.end(); ++iter){
			nMeterCount++;
			if(iter->bDefect)
				bDefectInInterval = true;
			if(nMeterCount > 0 && nMeterCount == m_SysParam->m_nMeterRatioMPerCount){
				nMeterCount = 0;
				if(bDefectInInterval){
					nDefectMeterCount++;
					bDefectInInterval = false;
				}
			}
		}

		// 알람여부 체크
		if(m_SysParam->m_nMeterRatioCount < nDefectMeterCount){
			// 알람
			m_bAlarmOnOff = TRUE;
			int ntmpmeter =pDoc->m_nTotalIns[0]+4;
			if(m_nAlarmEndFRame<ntmpmeter)
				m_nAlarmEndFRame = ntmpmeter;
			m_nAlarmLog += 4;
			m_strAlarmMsg = "Meter Ratio Defect";
			m_strAlarmMsg1.Format("%d Count in %d Meter", m_SysParam->m_nMeterRatioCount, m_SysParam->m_nMeterRatioTotalM) ;

			AddtoList("Alarm Meter Ratio Defect!",0,TRUE);
		}
// 		else{
// 			m_nNewAlarm = 0;
// 			m_strAlarmMsg = "";
// 			m_strAlarmMsg1= "" ;
// 
// 			m_nAlarmEndFRame = 0;
// 			m_bAlarmOnOff = FALSE;
// 			m_bNewAlarm = FALSE;
// 			KillTimer(20218);
// 			if(m_nAlarmOn==1)
// 				AddtoList("Alarm Off",0,TRUE);
// 			m_IO[0].WriteOutputPort(0,0,FALSE);
// 			m_nAlarmOn = 0;
// 			m_AlarmDlg->ShowWindow(0);
// 		}
	}

	//연속 불량
	BOOL bflag = FALSE;
	for(int i=0;i<9;i++){
		if(nBad[i]>=1){
			m_nBadCountDefect[i]++;
			bflag = TRUE;
		}
		else			m_nBadCountDefect[i] = 0;
	}
	if(bflag==TRUE)
		m_nBadCountDefect[9]++;//

	return nret;
}

BOOL CVisWebView::CheckNsysNGFile()			//200624 kjh
{
	CString strsrc, strdst, strsrcFolder=_T("Json"), strIP;
	CString strlot = ConvertCharToStr(cLotID);;
	double d1 = GetPrecisionTime();
	CString strFileName, strFilePath, strFolderPath, strFolder;
	CString data[6];
	CTime timer=CTime::GetCurrentTime();	

	data[0].Format("%d", timer.GetYear());
	if(timer.GetMonth() < 10)		data[1].Format("0%d", timer.GetMonth());
	else		data[1].Format("%d", timer.GetMonth());
	if(timer.GetDay() < 10)		data[2].Format("0%d", timer.GetDay());
	else		data[2].Format("%d", timer.GetDay());
	if(timer.GetHour() < 10)		data[3].Format("0%d", timer.GetHour());
	else		data[3].Format("%d", timer.GetHour());
	if(timer.GetMinute() < 10)		data[4].Format("0%d", timer.GetMinute());
	else		data[4].Format("%d", timer.GetMinute());
	if(timer.GetSecond() < 10)		data[5].Format("0%d", timer.GetSecond());
	else		data[5].Format("%d", timer.GetSecond());

	CString strLot1,strLot2,strLot3;
	int ncutno = atoi(strlot.Right(2));
	strLot1 = strlot.Left(7);
	strLot2.Format("%s_%03d",strLot1,ncutno);

	if(m_strComputerName.Find("CMI")>=0){
		if(m_strComputerName.Mid(7,1)=="A")
			strIP = IP_ADDRESS_CMI_ANODE_SURFACE;
		else
			strIP = IP_ADDRESS_CMI_CATHODE_SURFACE;

			strsrc.Format("\\\\%s\\data\\Lotdata\\%s\\%s\\%s\\%s\\",strIP,data[0],data[1],data[2],strlot);
	}
	else if(m_strComputerName.Find("OCH")>=0){
		//41 42 46 47
		CString strno;
		if(m_strComputerName.Mid(6,1)=="1"){
			if(m_strComputerName.Mid(7,1)=="A"){//음극
				strno = "46";
			}
			else
				strno = "41";
		}
		else{
			if(m_strComputerName.Mid(7,1)=="A"){//음극
				strno = "47";
			}
			else
				strno = "42";
		}
		strsrc.Format("\\\\100.0.0.%s\\data\\Lotdata\\%s\\%s\\%s\\%s\\",strno,data[0],data[1],data[2],strlot);//head back
	}

	CFileFind finder;
	BOOL bWorking = finder.FindFile(strsrc+_T("*.*"));
	if(!bWorking)
		return FALSE;

	while (bWorking)				// 불량이미지가 발생했는지 체크 
	{
		bWorking = finder.FindNextFile();
		if ( finder.IsDirectory() || finder.IsDots() )
			continue;
		else
		{
			strFileName = finder.GetFileName();
			strFilePath = finder.GetFilePath();

			CString strTok;    
			int sepCount =0;
			for(int i=0;i<strFileName.GetLength();i++)	if(strFileName.GetAt(i) == '_')	sepCount++;
			CString* temp1 = new CString[sepCount+1]; 
			int cnt=0;// 
			while(AfxExtractSubString(strTok, strFileName, cnt, '_'))  
				temp1[cnt++] = strTok;// 해당 배열에 순차적으로 넣어준다.

			//년월일시분초_불량명_posx_posy_Lane_sx_sy_Value_검사기위치(0:탑,1:백)
			//     0		  1	    2     3    4   5  6   7       8
			if(cnt<9)
				return FALSE;

			// ng conut
			CountNsysNg(temp1[1]);

			// image file move
			CString strTmp;
			strTmp.Format("D:\\Data\\LotData\\");
			CreateDirectory(strTmp,NULL);	
			strTmp.Format("D:\\Data\\LotData\\%s%s%s\\",data[0],data[1],data[2]);
			CreateDirectory(strTmp,NULL);	
			strTmp.Format("D:\\Data\\LotData\\%s%s%s\\%s\\",data[0],data[1],data[2],strlot);
			CreateDirectory(strTmp,NULL);	
			strTmp.Format("D:\\Data\\LotData\\%s%s%s\\%s\\Surface\\%s",data[0],data[1],data[2],strlot, strFileName);

			SHFILEOPSTRUCT    shfo;
			WORD        wfunc;
			TCHAR        pszTo[1024] = {0};
			TCHAR        pszFrom[1024] = {0};
			TCHAR        pszTitle[MAX_PATH] = {0};
			wfunc = FO_MOVE;
			memset(pszTo, 0, sizeof(pszTo));   // 중요
			memset(pszFrom, 0, sizeof(pszFrom));
			strcpy(pszTitle, "MoveFile");
			strcpy(pszTo, strTmp);
			strcpy(pszFrom , strFilePath);
			ZeroMemory(&shfo, sizeof(shfo));
			shfo.hwnd = AfxGetMainWnd()->m_hWnd;
			shfo.wFunc = wfunc;
			shfo.lpszProgressTitle=pszTitle;
			shfo.pTo=pszTo;
			shfo.pFrom=pszFrom;//FOF_NOCONFIRMATION
			shfo.fFlags = FOF_NOCONFIRMMKDIR|FOF_NOCONFIRMATION|FOF_SILENT|FOF_NOERRORUI;
			int ret = SHFileOperation(&shfo);

			// send ng data to server
			CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
			CString strNewPath;

			strNewPath.Format(_T("D:\\Data\\LotComplete\\%s\\%s\\%s\\%s\\Surface\\%s"), data[0], data[1], data[2], strlot, strFileName);
			WriteDefectDataServerSend(strlot, atof(temp1[3]), atof(temp1[2]), atof(temp1[5]), atof(temp1[6]), atof(temp1[7]), temp1[1], strsrc, strFileName,strNewPath, atof(temp1[3]),_T(""), _T(""), 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 ,_T(""), atoi(temp1[8]));

			delete [] temp1;
		}
	}

	return TRUE;
}

void CVisWebView::CountNsysNg(CString strNgType)
{
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)GetDocument();

	if(pDoc->m_pDlgInterface->m_bEngKor){
		if(strNgType.Find("Line")>=0)
			m_nNsysNgCount[0]++;
		else if(strNgType.Find("Pinhole")>=0)
			m_nNsysNgCount[1]++;
		else if(strNgType.Find("Chipping")>=0)
			m_nNsysNgCount[2]++;
		else if(strNgType.Find("Island")>=0)
			m_nNsysNgCount[7]++;
		else if(strNgType.Find("Drag")>=0)
			m_nNsysNgCount[8]++;
		else if(strNgType.Find("Wrinkle")>=0)
			m_nNsysNgCount[9]++;
		else
			m_nNsysNgCount[0]++;
	}
	else{
		if(strNgType.Find("라인")>=0)
			m_nNsysNgCount[0]++;
		else if(strNgType.Find("핀홀")>=0)
			m_nNsysNgCount[1]++;
		else if(strNgType.Find("파인")>=0)
			m_nNsysNgCount[2]++;
		else if(strNgType.Find("아일랜드")>=0)
			m_nNsysNgCount[7]++;
		else if(strNgType.Find("드래그")>=0)
			m_nNsysNgCount[8]++;
		else if(strNgType.Find("주름")>=0)
			m_nNsysNgCount[9]++;
		else
			m_nNsysNgCount[0]++;
	}
}

void CVisWebView::WriteINIFileForServer()
{
	CString strSection, strINIFilePath, strINIFileNewPath;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)GetDocument();
	CDlgInterface* pInterface = (CDlgInterface*)pDoc->m_pDlgInterface;
	CDlgSysParam* pSysParam = (CDlgSysParam*)m_SysParam;
	int nClient = 0;
	CString strModel = pDoc->m_data.m_strDefaultModel;

	// 1:head top, 2:surface top, 3:head back, 4:surface back, 5:surface master, 6:mismatch top, 7:mismatch back
	if(m_strComputerName.Mid(8,1) == "H" && m_strComputerName.Mid(9,1) == "T"){
		strSection = _T("Top Head");
		nClient = 1;
	}
	else if(m_strComputerName.Mid(8,1) == "H" && m_strComputerName.Mid(9,1) == "B"){
		strSection = _T("Back Head");
		nClient = 3;
	}
	else if(m_strComputerName.Mid(8,1) == "M" && m_strComputerName.Mid(9,1) == "T"){
		strSection = _T("Mismatch Top");
		nClient = 6;
	}
	else{
		strSection = _T("Mismatch Back");
		nClient = 7;
	}	

	pInterface->UpdateData(TRUE);
	pSysParam->UpdateData(TRUE);
	
	strINIFilePath.Format(_T("%s\\Parameter_%d.ini"), FOLDER_PATH_SERVER_INI, nClient);
	strINIFileNewPath.Format(_T("%s\\Parameter_%d_Tmp.ini"), FOLDER_PATH_SERVER_INI, nClient);

	CIni ini( strINIFilePath, strSection );
	double	param1,param2,param3,param4,param5,param6,param7,param8,param9,param10
		,param11,param12,param13,param14,param15,param16,param17,param18,param19,param20
		,param21,param22,param23,param24,param25,param26,param27,param28,param29,param30
		,param31,param32,param33,param34,param35,param36,param37,param38,param39,param40
		,param41,param42,param43,param44,param45,param46,param47,param48,param49,param50
		,param51,param52,param53,param54,param55,param56,param57,param58,param59,param60
		,param61,param62,param63,param64,param65,param66,param67,param68,param69,param70
		,param71,param72,param73,param74,param75,param76,param77,param78,param79,param80
		,param81,param82,param83,param84,param85,param86,param87,param88,param89,param90
		,param91,param92,param93,param94,param95,param96,param97,param98,param99,param100;
// 		,param101,param102,param103,param104,param105,param106,param107,param108,param109,param110
// 		,param111,param112,param113,param114,param115,param116,param117,param118,param119,param120
// 		,param121,param122,param123,param124,param125,param126,param127,param128,param129,param130
// 		,param131,param132,param133,param134,param135,param136,param137,param138,param139,param140;

	// 코팅부
	param1 = pInterface->param1;							ini.SER_GET(FALSE, param1);	 // 핀홀 value
	param2 = pInterface->param3;							ini.SER_GET(FALSE, param2);  // 핀홀 sizeX
	param3 = pInterface->paramPinholeY;						ini.SER_GET(FALSE, param3);  // 핀홀 sizeY
	param4 = 0.0;											ini.SER_GET(FALSE, param4);  // 돌출 value
	param5 = 0.0;											ini.SER_GET(FALSE, param5);  // 돌출 sizeX
	param6 = 0.0;											ini.SER_GET(FALSE, param6);  // 돌출 sizeY
	param7 = 0.0;											ini.SER_GET(FALSE, param7);  // 코팅부파임 value
	param8 = 0.0;											ini.SER_GET(FALSE, param8);  // 코팅부파임 sizeX
	param9 = 0.0;											ini.SER_GET(FALSE, param9);  // 코팅부파임 sizeY
	param10 = 0.0;											ini.SER_GET(FALSE, param10); // 표면 불량Value
	param11 = 0.0;											ini.SER_GET(FALSE, param11); // 표면 불량Size X
	param12 = 0.0;											ini.SER_GET(FALSE, param12); // 표면 불량Size Y
	param13 = 0.0;											ini.SER_GET(FALSE, param13); // 분화구Value
	param14 = 0.0;											ini.SER_GET(FALSE, param14); // 분화구Size X
	param15 = 0.0;											ini.SER_GET(FALSE, param15); // 분화구Size Y
	param16 = 0.0;											ini.SER_GET(FALSE, param16); // 핀홀성 분화구Value
	param17 = 0.0;											ini.SER_GET(FALSE, param17); // 핀홀성 분화구Size X
	param18 = 0.0;											ini.SER_GET(FALSE, param18); // 핀홀성 분화구Size Y
	param19 = 0.0;											ini.SER_GET(FALSE, param19); // 경계 라인불량Value
	param20 = 0.0;											ini.SER_GET(FALSE, param20); // 경계 라인불량Size X
	param21 = 0.0;											ini.SER_GET(FALSE, param21); // 경계 라인불량Size Y
	param22 = pInterface->param4;							ini.SER_GET(FALSE, param22); // 라인불량Value
	param23 = pInterface->paramLineX;						ini.SER_GET(FALSE, param23); // 라인불량Size X
	param24 = pInterface->paramLineY;						ini.SER_GET(FALSE, param24); // 라인불량Size Y
	param25 = 0.0;											ini.SER_GET(FALSE, param25); // 거대라인불량Value
	param26 = 0.0;											ini.SER_GET(FALSE, param26); // 거대라인불량Size X
	param27 = 0.0;											ini.SER_GET(FALSE, param27); // 거대라인불량Size Y
	param28 = 0.0;											ini.SER_GET(FALSE, param28); // 코팅부 주름Value
	param29 = 0.0;											ini.SER_GET(FALSE, param29); // 코팅부 주름Size X
	param30 = 0.0;											ini.SER_GET(FALSE, param30); // 코팅부 주름Size Y
	param31 = 0.0;											ini.SER_GET(FALSE, param31); // 열 주름Value
	param32 = 0.0;											ini.SER_GET(FALSE, param32); // 열 주름Size X
	param33 = 0.0;											ini.SER_GET(FALSE, param33); // 열 주름Size Y
	param34 = 0.0;											ini.SER_GET(FALSE, param34); // 긁힘Value
	param35 = 0.0;											ini.SER_GET(FALSE, param35); // 긁힘Size X
	param36 = 0.0;											ini.SER_GET(FALSE, param36); // 긁힘Size Y
	param37 = 0.0;											ini.SER_GET(FALSE, param37); // 크랙Value
	param38 = 0.0;											ini.SER_GET(FALSE, param38); // 크랙Size X
	param39 = 0.0;											ini.SER_GET(FALSE, param39); // 크랙Size Y
	param40 = 0.0;											ini.SER_GET(FALSE, param40); // 미코팅불량Value
	param41 = 0.0;											ini.SER_GET(FALSE, param41); // 미코팅불량Size X
	param42 = 0.0;											ini.SER_GET(FALSE, param42); // 미코팅불량Size Y
	// 미코팅부
	param43 = pInterface->param2;							ini.SER_GET(FALSE, param43); // 아일랜드Value
	param44 = pInterface->paramislandX;						ini.SER_GET(FALSE, param44); // 아일랜드Size X
	param45 = pInterface->paramislandY;						ini.SER_GET(FALSE, param45); // 아일랜드Size Y
	param46 = 0.0;											ini.SER_GET(FALSE, param46); // 주름Value
	param47 = 0.0;											ini.SER_GET(FALSE, param47); // 주름Size X
	param48 = 0.0;											ini.SER_GET(FALSE, param48); // 주름Size Y
	param49 = 0.0;											ini.SER_GET(FALSE, param49); // DragValue
	param50 = 0.0;											ini.SER_GET(FALSE, param50); // DragSize X
	param51 = 0.0;											ini.SER_GET(FALSE, param51); // DragSize Y
	// 공통
	param52 = pInterface->scale_x;							ini.SER_GET(FALSE, param52); // Scale Xmm
	param53 = pInterface->scale_y;							ini.SER_GET(FALSE, param53); // Scale Ymm
	param54 = pInterface->m_nLineTh1;						ini.SER_GET(FALSE, param54); // 에지 THValue
	// 치수
	param55 = pSysParam->m_dStandard[0];					ini.SER_GET(FALSE, param55); // 무지 1min
	param56 = pSysParam->m_dMaxValue[0];					ini.SER_GET(FALSE, param56); // 무지 1max
	param57 = pSysParam->m_dStandard[1];					ini.SER_GET(FALSE, param57); // 코팅 1min
	param58 = pSysParam->m_dMaxValue[1];					ini.SER_GET(FALSE, param58); // 코팅 1max
	param59 = pSysParam->m_dStandard[2];					ini.SER_GET(FALSE, param59); // 무지 2min
	param60 = pSysParam->m_dMaxValue[2];					ini.SER_GET(FALSE, param60); // 무지 2max
	param61 = pSysParam->m_dStandard[3];					ini.SER_GET(FALSE, param61); // 코팅 2min
	param62 = pSysParam->m_dMaxValue[3];					ini.SER_GET(FALSE, param62); // 코팅 2max
	param63 = pSysParam->m_dStandard[4];					ini.SER_GET(FALSE, param63); // 무지 3min
	param64 = pSysParam->m_dMaxValue[4];					ini.SER_GET(FALSE, param64); // 무지 3max
	param65 = pSysParam->m_dStandard[5];					ini.SER_GET(FALSE, param65); // 코팅 3min
	param66 = pSysParam->m_dMaxValue[5];					ini.SER_GET(FALSE, param66); // 코팅 3max
	param67 = pSysParam->m_dStandard[6];					ini.SER_GET(FALSE, param67); // 무지 4min
	param68 = pSysParam->m_dMaxValue[6];					ini.SER_GET(FALSE, param68); // 무지 4max
	param69 = pSysParam->m_dStandard[7];					ini.SER_GET(FALSE, param69); // 코팅 4min
	param70 = pSysParam->m_dMaxValue[7];					ini.SER_GET(FALSE, param70); // 코팅 4max
	param71 = pSysParam->m_dStandard[8];					ini.SER_GET(FALSE, param71); // 무지 5min
	param72 = pSysParam->m_dMaxValue[8];					ini.SER_GET(FALSE, param72); // 무지 5max
	param73 = pDoc->m_pDlgInterface->m_dMismatchTolMin1;	ini.SER_GET(FALSE, param73); // 미스매치min
	param74 = pDoc->m_pDlgInterface->m_dMismatchTolMax1;	ini.SER_GET(FALSE, param74); // 미스매치max
	// 알람
	param75 = pSysParam->m_dBadAlarmMeter;					ini.SER_GET(FALSE, param75); // 폭연속Meter
	param76 = pSysParam->m_dBadAlarmMismatch;				ini.SER_GET(FALSE, param76); // 미스매치 연속Meter
	param77 = pSysParam->m_nBadFrameInCount;				ini.SER_GET(FALSE, param77); // 구간이물Meter
	param78 = pSysParam->m_nBadFrameInDefect;				ini.SER_GET(FALSE, param78); // 구간이물EA
	param79 = pSysParam->m_nContinueBadFrame;				ini.SER_GET(FALSE, param79); // 이물 연속Meter
	param80 = pSysParam->m_nContinueBadcnt;					ini.SER_GET(FALSE, param80); // 이물 연속EA

	AddCommentToServerINI(strINIFilePath, strINIFileNewPath);

}

BOOL CVisWebView::ExistFile(CString strPath)
{
	CFileFind finder;
	BOOL bWorking = finder.FindFile(strPath);
	int nCount = 0;
	BOOL	bRet = FALSE;
	CString strOut;
	int nMinusIndex = 2;
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if ( finder.IsDirectory() || finder.IsDots() )
			continue;
		else
		{
			CString strPath2;
			strPath2 = finder.GetFileName();
			bRet = TRUE;
		}
	}
	return bRet;
}

void CVisWebView::ReadINIFileFromServer()
{
	CString strSection, strINIFilePath;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)GetDocument();
	CDlgInterface* pInterface = (CDlgInterface*)pDoc->m_pDlgInterface;
	CDlgSysParam* pSysParam = (CDlgSysParam*)m_SysParam;
	int nClient = 0;
	double	param1,param2,param3,param4,param5,param6,param7,param8,param9,param10
		,param11,param12,param13,param14,param15,param16,param17,param18,param19,param20
		,param21,param22,param23,param24,param25,param26,param27,param28,param29,param30
		,param31,param32,param33,param34,param35,param36,param37,param38,param39,param40
		,param41,param42,param43,param44,param45,param46,param47,param48,param49,param50
		,param51,param52,param53,param54,param55,param56,param57,param58,param59,param60
		,param61,param62,param63,param64,param65,param66,param67,param68,param69,param70
		,param71,param72,param73,param74,param75,param76,param77,param78,param79,param80
		,param81,param82,param83,param84,param85,param86,param87,param88,param89,param90
		,param91,param92,param93,param94,param95,param96,param97,param98,param99,param100;
		// 		,param101,param102,param103,param104,param105,param106,param107,param108,param109,param110
		// 		,param111,param112,param113,param114,param115,param116,param117,param118,param119,param120
		// 		,param121,param122,param123,param124,param125,param126,param127,param128,param129,param130
		// 		,param131,param132,param133,param134,param135,param136,param137,param138,param139,param140;


	
	if(m_strComputerName.Mid(8,1) == "H" && m_strComputerName.Mid(9,1) == "T"){
		strSection = _T("Top Head");
		nClient = 1;
	}
	else if(m_strComputerName.Mid(8,1) == "H" && m_strComputerName.Mid(9,1) == "B"){
		strSection = _T("Back Head");
		nClient = 3;
	}
	else if(m_strComputerName.Mid(8,1) == "M" && m_strComputerName.Mid(9,1) == "T"){
		strSection = _T("Mismatch Top");
		nClient = 6;
	}
	else{
		strSection = _T("Mismatch Back");
		nClient = 7;
	}	

	strINIFilePath.Format(_T("%s\\Parameter_%d.ini"), FOLDER_PATH_SERVER_INI, nClient);
	CIni ini( strINIFilePath, strSection );

	ini.SER_GETD(TRUE, param1, 0);			pInterface->param1				= 	param1;
	ini.SER_GETD(TRUE, param2, 0);			pInterface->param3				= 	param2;
	ini.SER_GETD(TRUE, param3, 0);			pInterface->paramPinholeY		= 	param3;
	ini.SER_GETD(TRUE, param4, 0);											
	ini.SER_GETD(TRUE, param5, 0);											
	ini.SER_GETD(TRUE, param6, 0);											
	ini.SER_GETD(TRUE, param7, 0);											
	ini.SER_GETD(TRUE, param8, 0);											
	ini.SER_GETD(TRUE, param9, 0);											
	ini.SER_GETD(TRUE, param10, 0);										
	ini.SER_GETD(TRUE, param11, 0);										
	ini.SER_GETD(TRUE, param12, 0);										
	ini.SER_GETD(TRUE, param13, 0);										
	ini.SER_GETD(TRUE, param14, 0);										
	ini.SER_GETD(TRUE, param15, 0);										
	ini.SER_GETD(TRUE, param16, 0);										
	ini.SER_GETD(TRUE, param17, 0);										
	ini.SER_GETD(TRUE, param18, 0);										
	ini.SER_GETD(TRUE, param19, 0);										
	ini.SER_GETD(TRUE, param20, 0);										
	ini.SER_GETD(TRUE, param21, 0);										
	ini.SER_GETD(TRUE, param22, 0);		 pInterface->param4				=	param22;
	ini.SER_GETD(TRUE, param23, 0);		 pInterface->paramLineX			=	param23;
	ini.SER_GETD(TRUE, param24, 0);		 pInterface->paramLineY			=	param24;
	ini.SER_GETD(TRUE, param25, 0);		 								
	ini.SER_GETD(TRUE, param26, 0);		 								
	ini.SER_GETD(TRUE, param27, 0);		 								
	ini.SER_GETD(TRUE, param28, 0);		 								
	ini.SER_GETD(TRUE, param29, 0);		 								
	ini.SER_GETD(TRUE, param30, 0);		 								
	ini.SER_GETD(TRUE, param31, 0);		 								
	ini.SER_GETD(TRUE, param32, 0);		 								
	ini.SER_GETD(TRUE, param33, 0);		 								
	ini.SER_GETD(TRUE, param34, 0);		 								
	ini.SER_GETD(TRUE, param35, 0);		 								
	ini.SER_GETD(TRUE, param36, 0);		 								
	ini.SER_GETD(TRUE, param37, 0);		 								
	ini.SER_GETD(TRUE, param38, 0);		 								
	ini.SER_GETD(TRUE, param39, 0);		 								
	ini.SER_GETD(TRUE, param40, 0);		 								
	ini.SER_GETD(TRUE, param41, 0);		 								
	ini.SER_GETD(TRUE, param42, 0);		 								
																				
	ini.SER_GETD(TRUE, param43, 0);		 pInterface->param2				=	param43;
	ini.SER_GETD(TRUE, param44, 0);		 pInterface->paramislandX		=	param44;
	ini.SER_GETD(TRUE, param45, 0);		 pInterface->paramislandY		=	param45;
	ini.SER_GETD(TRUE, param46, 0);		 								
	ini.SER_GETD(TRUE, param47, 0);		 								
	ini.SER_GETD(TRUE, param48, 0);		 								
	ini.SER_GETD(TRUE, param49, 0);		 								
	ini.SER_GETD(TRUE, param50, 0);		 								
	ini.SER_GETD(TRUE, param51, 0);		 								
																				   
	ini.SER_GETD(TRUE, param52, 0);		 pSysParam->scale_x			=	param52;
	ini.SER_GETD(TRUE, param53, 0);		 pSysParam->scale_y			=	param53;
	ini.SER_GETD(TRUE, param54, 0);		 pInterface->m_nLineTh1		=	param54;
																				   
	ini.SER_GETD(TRUE, param55, 0);		 m_dTolerance[0]		=	param55;
	ini.SER_GETD(TRUE, param56, 0);		 m_dTolerance[1]		=	param56;
	ini.SER_GETD(TRUE, param57, 0);		 m_dTolerance[2]		=	param57;
	ini.SER_GETD(TRUE, param58, 0);		 m_dTolerance[3]		=	param58;
	ini.SER_GETD(TRUE, param59, 0);		 m_dTolerance[4]		=	param59;
	ini.SER_GETD(TRUE, param60, 0);		 m_dTolerance[5]		=	param60;
	ini.SER_GETD(TRUE, param61, 0);		 m_dTolerance[6]		=	param61;
	ini.SER_GETD(TRUE, param62, 0);		 m_dTolerance[7]		=	param62;
	ini.SER_GETD(TRUE, param63, 0);		 m_dTolerance[8]		=	param63;
	ini.SER_GETD(TRUE, param64, 0);		 m_dTolerance[9]		=	param64;
	ini.SER_GETD(TRUE, param65, 0);		 m_dTolerance[10]		=	param65;
	ini.SER_GETD(TRUE, param66, 0);		 m_dTolerance[11]		=	param66;
	ini.SER_GETD(TRUE, param67, 0);		 m_dTolerance[12]		=	param67;
	ini.SER_GETD(TRUE, param68, 0);		 m_dTolerance[13]		=	param68;
	ini.SER_GETD(TRUE, param69, 0);		 m_dTolerance[14]		=	param69;
	ini.SER_GETD(TRUE, param70, 0);		 m_dTolerance[15]		=	param70;
	ini.SER_GETD(TRUE, param71, 0);		 m_dTolerance[16]		=	param71;
	ini.SER_GETD(TRUE, param72, 0);		 m_dTolerance[17]		=	param72;
	ini.SER_GETD(TRUE, param73, 0);		 m_dMismatchTolMin1	=	param73;
	ini.SER_GETD(TRUE, param74, 0);		 m_dMismatchTolMax1	=	param74;
																				   
	ini.SER_GETD(TRUE, param75, 0);		 pSysParam->m_dBadAlarmMeter	=	param75;
	ini.SER_GETD(TRUE, param76, 0);		 pSysParam->m_dBadAlarmMismatch	=	param76;
	ini.SER_GETD(TRUE, param77, 0);		 pSysParam->m_nBadFrameInCount	=	param77;
	ini.SER_GETD(TRUE, param78, 0);		 pSysParam->m_nBadFrameInDefect	=	param78;
	ini.SER_GETD(TRUE, param79, 0);		 pSysParam->m_nContinueBadFrame	=	param79;
	ini.SER_GETD(TRUE, param80, 0);		 pSysParam->m_nContinueBadcnt	=	param80;
								
	pInterface->UpdateData(FALSE);
	pSysParam->UpdateData(FALSE);
																						   
}

void CVisWebView::CreateINICheckFile()
{
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)GetDocument();
	CString strINIFilePath;
	CStdioFile file;
	int nClient = 0;
	CString strModel = pDoc->m_data.m_strDefaultModel;

	if(m_strComputerName.Mid(8,1) == "H" && m_strComputerName.Mid(9,1) == "T")
		nClient = 1;
	else if(m_strComputerName.Mid(8,1) == "H" && m_strComputerName.Mid(9,1) == "B")
		nClient = 3;
	else if(m_strComputerName.Mid(8,1) == "M" && m_strComputerName.Mid(9,1) == "T")
		nClient = 6;
	else
		nClient = 7;




	strINIFilePath.Format(_T("%s\\%d-1.txt"), FOLDER_PATH_SERVER_INI_CHECK, nClient);
	if(file.Open(strINIFilePath,CFile::modeCreate|CFile::modeReadWrite|CFile::typeText,NULL)){			// 20201021 kjh 모델명 체크파일에 쓰기
		file.WriteString(strModel);
		file.Close();
	}
}

void CVisWebView::AddCommentToServerINI(CString strINIFileName, CString strINIFileNew)
{
	CStdioFile fileSrc, fileDst;
	CString strFile, strBuffer, strBufferNew;
	int nParamCnt = 0, nSectionCnt = 0;
	int idx = 0;
	int idx2 = 0;
	CString (*pParamDataTop)[5];
	CString (*pParamDataBack)[5];
	bool bValidParam = false;
	CopyFile(strINIFileName,strINIFileNew,FALSE);
	//CFile::Rename(strINIFileName, strINIFileNew);
	
	if(fileSrc.Open(strINIFileNew, CFile::modeRead|CFile::typeText))
	{
		if(fileDst.Open(strINIFileName,CFile::modeCreate|CFile::modeWrite|CFile::typeText,NULL)){
			while(1){
				fileSrc.ReadString(strBuffer);if(strBuffer=="")break;
				if(strBuffer.GetAt(0) =='['){
					strBuffer += "\n";
					fileDst.WriteString(strBuffer);
				}
				else{					
					if(m_strComputerName.Find(_T("OCH"))>=0)
						strBufferNew.Format(_T("%s;%s,%d,%d\n"), strBuffer, g_strServerParamName_KOR[nParamCnt++], 0, 100);
					else
						strBufferNew.Format(_T("%s;%s,%d,%d\n"), strBuffer, g_strServerParamName_ENG[nParamCnt++], 0, 100);		// 20201016 kjh
					fileDst.WriteString(strBufferNew);					
				}				
			}
			fileSrc.Close();
		}
		fileDst.Close();
	}
	DeleteFile(strINIFileNew);
}	

// save sharpness image 
void CVisWebView::SaveEdgeImage(int nMeter,int nCount,CString strLot,int nSharpness, CString& strFilePath)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	CString data[6];
	CTime timer=CTime::GetCurrentTime();  
	data[0].Format("%d", timer.GetYear());
	if(timer.GetMonth() < 10)             data[1].Format("0%d", timer.GetMonth());
	else           data[1].Format("%d", timer.GetMonth());
	if(timer.GetDay() < 10)               data[2].Format("0%d", timer.GetDay());
	else           data[2].Format("%d", timer.GetDay());
	if(timer.GetHour() < 10)              data[3].Format("0%d", timer.GetHour());
	else           data[3].Format("%d", timer.GetHour());
	if(timer.GetMinute() < 10)            data[4].Format("0%d", timer.GetMinute());
	else           data[4].Format("%d", timer.GetMinute());
	if(timer.GetSecond() < 10)            data[5].Format("0%d", timer.GetSecond());
	else           data[5].Format("%d", timer.GetSecond());
	CString strtmp,strpath,filename;
	strpath.Format("D:\\Data\\LotData\\");
	CreateDirectory(strpath,NULL); 
	strpath.Format("D:\\Data\\LotData\\%s%s%s\\",data[0],data[1],data[2]);
	CreateDirectory(strpath,NULL); 
	strpath.Format("D:\\Data\\LotData\\%s%s%s\\%s\\",data[0],data[1],data[2],strLot);
	CreateDirectory(strpath,NULL); 
	strpath.Format("D:\\Data\\LotData\\%s%s%s\\%s\\Sharpness\\",data[0],data[1],data[2],strLot);
	CreateDirectory(strpath,NULL); 
	filename.Format("%s%d_Sharpness_%d.jpg",strpath,nMeter,nCount);
	strFilePath = filename;

	m_fmEdgeVew[nCount]->SaveMini(filename);
}

// Gray Level &  Sharpness data file
void CVisWebView::WriteSharpness(CString strLot, int nMeter,int nCount, CString strFilePath)
{
	//화일을 쪼개고
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CString data[6];
	CTime timer=CTime::GetCurrentTime();  
	data[0].Format("%d", timer.GetYear());
	if(timer.GetMonth() < 10)             data[1].Format("0%d", timer.GetMonth());
	else           data[1].Format("%d", timer.GetMonth());
	if(timer.GetDay() < 10)               data[2].Format("0%d", timer.GetDay());
	else           data[2].Format("%d", timer.GetDay());
	if(timer.GetHour() < 10)              data[3].Format("0%d", timer.GetHour());
	else           data[3].Format("%d", timer.GetHour());
	if(timer.GetMinute() < 10)            data[4].Format("0%d", timer.GetMinute());
	else           data[4].Format("%d", timer.GetMinute());
	if(timer.GetSecond() < 10)            data[5].Format("0%d", timer.GetSecond());
	else           data[5].Format("%d", timer.GetSecond());
	CString strtmp="",strpath,filename,strtmp1,strtime,strtmp2="",strtmp3="",strtmp4="";
	strpath.Format("D:\\Data\\LotData\\");
	CreateDirectory(strpath,NULL); 
	strpath.Format("D:\\Data\\LotData\\%s%s%s\\",data[0],data[1],data[2]);
	CreateDirectory(strpath,NULL); 
	strpath.Format("D:\\Data\\LotData\\%s%s%s\\%s\\",data[0],data[1],data[2],strLot);
	CreateDirectory(strpath,NULL); 
	strpath.Format("D:\\Data\\LotData\\%s%s%s\\%s\\Sharpness\\",data[0],data[1],data[2],strLot);
	CreateDirectory(strpath,NULL); 
	filename.Format("%s%s_Sharpness.txt",strpath,strLot);

	for(int i=0;i<nCount;i++){
		strtmp2.Format("%.0f,",pDoc->m_data.m_dSharpness2[i]);
		strtmp+=strtmp2;
		if(i<nCount-1){
			strtmp3.Format("%.0f,",pDoc->m_data.m_dGrayValue[i]);
			strtmp4+= strtmp3;
		}
	}//m_dGrayValue
	strtime.Format("%s%s%s%s%s%s",data[0],data[1],data[2],data[3],data[4],data[5]);
//시간 LOT Meter count 1/2/3/4...
	strtmp1.Format("%s,%s,%d,%s,%d,%s%s",strtime,strLot,nMeter,strFilePath, nCount,strtmp,strtmp4);			//200624 kjh
		CStdioFile   file;
		//	화일 기록
		if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
		{		
			if(file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText))
			{
				file.WriteString(strtmp1);
				file.Close();
			}
		}
		else
		{
			file.SeekToEnd();
			file.WriteString("\n");
			file.WriteString(strtmp1);
			file.Close(); 
		}
}

CString CVisWebView::GetLightValue1(int nValue,int nMid)//ms -> 16진수로
{
	CString str;
//20 01 40
	if(nValue<16){
		if(nMid%2==0)	str.Format("00%X0",nValue);//16진수  20-> 0140	%x %X
		else			str.Format("00%X8",nValue);//16진수  20-> 0140
	}
	else{
		if(nMid%2==0)	str.Format("0%X0",nValue);//16진수  20-> 0140
		else			str.Format("0%X8",nValue);//16진수  20-> 0140
	} 

	return str;
}
int CVisWebView::GetLightValue2(CString str)
{//소수점은 무시하면서 변환한다.

	//중간 2글자만 분리한다.
	CString str1;
	int nlen = str.GetLength();
	if(nlen==6)	str1 = (str.Mid(4,2));//600100 16
	else		str1 = (str.Mid(2,2));//0100	16

	int  nDec = (int)strtol(str1, NULL, 16);

	return nDec;
}

void CVisWebView::WriteUseCheck(int nTopBack, int nLineCnt)
{
	int nWidthData = 0;
	int nMismatchData = 0;
	int nTmp = 0, nLane = 0, nNCoat = 0;
	int nData[2][2] = {0,}; //	top/back word1,2
	
	nLane = (nLineCnt/2)-1;
	nNCoat = nLane+1;
	if(nTopBack == 0){		//top
		for(int i=0; i<nNCoat; i++){
			if(m_bUseLen[i*2])
				nData[0][0] += (1<<(i+5));		
		}
		for(int i=0; i<nLane; i++){
			if(m_bUseLen[i*2+1])
				nData[0][0] += (1<<i);	
		}
		WriteShareMemory1(18,0,nData[0][0]);
	}
	else{					//back
		for(int i=0; i<nNCoat; i++){
			if(m_bUseLen[i*2])
				nData[1][0] += (1<<(i+5));		
		}
		for(int i=0; i<nLane; i++){
			if(m_bUseLen[i*2+1])
				nData[1][0] += (1<<i);	
		}
		WriteShareMemory1(19,0,nData[1][0]);

		for(int i=0; i<nLane*2; i++)
			if(m_bUseMismatch[i+1])
				nData[1][1] += (1<<i);
		WriteShareMemory1(19,1,nData[1][1]);

	}
}

void CVisWebView::SendPgmStatus(int nTopBack, int nStatus)
{
	static int nToggle = 0;

	if(nToggle == 0)	nToggle = 1;
	else nToggle = 0;

	if(nTopBack == 0){
		WriteShareMemory1(16, 0, nToggle);
		WriteShareMemory1(16, 1, nStatus);
	}
	else{
		WriteShareMemory1(17, 0, nToggle);
		WriteShareMemory1(17, 1, nStatus);
	}
	
}

void CVisWebView::SavePLCSendDataLog( CString* strLogCoat, CString* strLogNCoat, CString* strLogMismatch, CString strLot, int nMeter)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CString data[6];
	CTime timer=CTime::GetCurrentTime();  
	data[0].Format("%d", timer.GetYear());
	if(timer.GetMonth() < 10)             data[1].Format("0%d", timer.GetMonth());
	else           data[1].Format("%d", timer.GetMonth());
	if(timer.GetDay() < 10)               data[2].Format("0%d", timer.GetDay());
	else           data[2].Format("%d", timer.GetDay());
	if(timer.GetHour() < 10)              data[3].Format("0%d", timer.GetHour());
	else           data[3].Format("%d", timer.GetHour());
	if(timer.GetMinute() < 10)            data[4].Format("0%d", timer.GetMinute());
	else           data[4].Format("%d", timer.GetMinute());
	if(timer.GetSecond() < 10)            data[5].Format("0%d", timer.GetSecond());
	else           data[5].Format("%d", timer.GetSecond());
	CString strtmp="",strpath,filename,strtmp1,strtime,strCoat="",strNCoat="",strMM="", strTitle="";
	strpath.Format("D:\\Data\\PLC_LOG\\");
	CreateDirectory(strpath,NULL); 
	strpath.Format("D:\\Data\\PLC_LOG\\%s%s%s\\",data[0],data[1],data[2]);
	CreateDirectory(strpath,NULL); 
	strpath.Format("D:\\Data\\PLC_LOG\\%s%s%s\\%s\\",data[0],data[1],data[2],strLot);
	CreateDirectory(strpath,NULL); 
	filename.Format("%s\\%s_PLC_Data.csv",strpath, strLot);
	strCoat.Format(_T("%s,%s,%s,%s"), strLogCoat[0], strLogCoat[1], strLogCoat[2], strLogCoat[3]);
	strNCoat.Format(_T("%s,%s,%s,%s,%s"), strLogNCoat[0], strLogNCoat[1], strLogNCoat[2], strLogNCoat[3], strLogNCoat[4]);
	strMM.Format(_T("%s,%s,%s,%s,%s,%s,%s,%s"), strLogMismatch[0], strLogMismatch[1], strLogMismatch[2], strLogMismatch[3], strLogMismatch[4], strLogMismatch[5], strLogMismatch[6], strLogMismatch[7]);
	strtime.Format("%s%s%s%s%s%s",data[0],data[1],data[2],data[3],data[4],data[5]);
	strtmp1.Format(_T("%s,%d,%s,%s,%s"), strtime, nMeter, strCoat, strNCoat, strMM);
	

	CStdioFile   file;
	//	화일 기록
	if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
	{		
		if(file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText))
		{
			strTitle.Format(_T("시간,미터,코팅폭1,코팅폭2,코팅폭3,코팅폭4,무지폭1,무지폭2,무지폭3,무지폭4,무지폭5,미스매치1,미스매치2,미스매치3,미스매치4,미스매치5,미스매치6,미스매치7,미스매치8"));
			file.WriteString(strTitle);
			file.WriteString("\n");
			file.WriteString(strtmp1);
			file.Close();
		}
	}
	else
	{
		file.SeekToEnd();
		file.WriteString("\n");
		file.WriteString(strtmp1);
		file.Close(); 
	}
}


void CVisWebView::OnBnClickedCheckPrimer()
{//m_bPrimer
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	UpdateData();
	if(m_bPrimer){
		//shutter change
		pDoc->m_pDlgInterface->ChangeBrightness(pDoc->m_pDlgInterface->m_nLightPrimer,0,60);//프라이머
	}
	else{
		pDoc->m_pDlgInterface->ChangeBrightness(pDoc->m_pDlgInterface->m_nLightOnTime,0,60);//일반 밝기
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CVisWebView::OnBnClickedButtonResetimage()
{//리셋 이미지
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	for(int i=0;i<15;i++){
		memset(m_pDefectImage[i]->GetImagePtr(),0,BAD_IMG_HEIGHT*BAD_IMG_WIDTH);
		memset(m_charLbLotInfo[i], NULL, sizeof(char)*100);
		m_lbDefectInfo[i].SetText(m_charLbLotInfo[i]);
	}
	//	불량 ㅋ운트 리셋
	m_nMismatchBadCount = 0;
	for(int k1=0;k1<MAX_CAMERAS;k1++)
		pDoc->m_nTotalIns[k1]=0;

	for(int i=0;i<10;i++)m_nBadCountDefect[i] =pDoc->m_data.m_nBadTypeCount[i]= 0;
	UpdateControl();

}

int CVisWebView::GetPGMStatus()
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	static bool bTestMode = false;
	bool bMachineRun;
	int nStatus = 0;		// 0:On(코팅on, pgm on), 1:Stop(코팅on, pgm stop), 2:Test(Test모드), 3:Ready(코팅Stop)
	bMachineRun = (m_bNonCoat[0]==FALSE)?true:false;

	if(bTestMode)
		nStatus = 2;
	else{
		if(bMachineRun){
			if(m_bAuto)
				nStatus = 0;
			else
				nStatus = 1;
		}
		else{
			nStatus = 3;
		}
	}

	if(pDoc->m_pDlgInterface->m_CheckPLCTest){
		pDoc->m_pDlgInterface->UpdateData();
		if(pDoc->m_pDlgInterface->m_radioTestPlc == 0)
			nStatus = 0;
		else if(pDoc->m_pDlgInterface->m_radioTestPlc == 1)
			nStatus = 1;
		else if(pDoc->m_pDlgInterface->m_radioTestPlc == 2)
			nStatus = 2;
		else
			nStatus = 3;

// 		if(m_strComputerName.Mid(9,1) == "T")
// 			SendPgmStatus(0, nStatus);
// 		else
// 			SendPgmStatus(1, nStatus);
	}
	else{
// 		if(m_strComputerName.Mid(9,1) == "T")
// 			SendPgmStatus(0, nStatus);
// 		else
// 			SendPgmStatus(1, nStatus);
	}

	return nStatus;
}

void CVisWebView::CopyLotDataFolders(CString strlot, CString strtime)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CString strtime1,strtime2, strBaseFolder;
	CString data[6];
	CTime timer=CTime::GetCurrentTime();	
	data[0].Format("%d", timer.GetYear());
	if(timer.GetMonth() < 10)		data[1].Format("0%d", timer.GetMonth());
	else		data[1].Format("%d", timer.GetMonth());
	if(timer.GetDay() < 10)		data[2].Format("0%d", timer.GetDay());
	else		data[2].Format("%d", timer.GetDay());
	if(timer.GetHour() < 10)		data[3].Format("0%d", timer.GetHour());
	else		data[3].Format("%d", timer.GetHour());
	if(timer.GetMinute() < 10)		data[4].Format("0%d", timer.GetMinute());
	else		data[4].Format("%d", timer.GetMinute());
	if(timer.GetSecond() < 10)		data[5].Format("0%d", timer.GetSecond());
	else		data[5].Format("%d", timer.GetSecond());

	strBaseFolder.Format("D:\\Data\\LotComplete\\%s\\%s\\%s\\%s",data[0],data[1],data[2],strlot);//lot

	CString strSrc, strDst, strComputername;
	if(m_strComputerName.Find("OCH")>=0){
		//|| pDoc->m_data.m_nLineSelect%10==2
		strDst = m_strComputerName.Left(8)+"HB1";		
	}
	else if(m_strComputerName.Find("CMI")>=0){
		strDst = m_strComputerName.Left(8)+"MB1";
	}

	strComputername = m_strComputerName.Left(8)+"HT1";			// top
	strSrc.Format("\\\\%s\\Data\\Lotdata\\%s\\%s",strComputername,strtime,strlot);
	strDst.Format("%s\\HeadTop", strBaseFolder);
	CopyLotData(strSrc, strDst, strlot, strtime);

	strComputername = m_strComputerName.Left(8)+"HB1";			// back
	strSrc.Format("\\\\%s\\Data\\Lotdata\\%s\\%s",strComputername,strtime,strlot);
	strDst.Format("%s\\HeadBack", strBaseFolder);
	CopyLotData(strSrc, strDst, strlot, strtime);

	if(m_strComputerName.Find(_T("CMI"))>=0){
		strComputername = m_strComputerName.Left(8)+"MT1";		// mis top
		strSrc.Format("\\\\%s\\Data\\Lotdata\\%s\\%s",strComputername,strtime,strlot);
		strDst.Format("%s\\MisTop", strBaseFolder);
		CopyLotData(strSrc, strDst, strlot, strtime);

		strComputername = m_strComputerName.Left(8)+"MB1";		// mis back
		strSrc.Format("\\\\%s\\Data\\Lotdata\\%s\\%s",strComputername,strtime,strlot);
		strDst.Format("%s\\MisBack", strBaseFolder);
		CopyLotData(strSrc, strDst, strlot, strtime);
	}
}

void CVisWebView::CopyLotData(CString strSrc, CString strDst, CString strLot, CString strDate)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	if(strLot == "")strLot = "NONE";

	double dtime1 = GetPrecisionTime();
	CString str1;
	str1.Format("FileMove Start (%s) %s - %s",strLot,strSrc,strDst);
	AddtoList(str1,0);

	SHFILEOPSTRUCT    shfo;
	WORD        wfunc;
	TCHAR        pszTo[1024] = {0};
	TCHAR        pszFrom[1024] = {0};
	TCHAR        pszTitle[MAX_PATH] = {0};
	wfunc = FO_MOVE;
	memset(pszTo, 0, sizeof(pszTo));   // 중요
	memset(pszFrom, 0, sizeof(pszFrom));
	strcpy(pszTitle, "파일이동");
	strcpy(pszTo, strDst);
	strcpy(pszFrom , strSrc);
	ZeroMemory(&shfo, sizeof(shfo));
	shfo.hwnd = AfxGetMainWnd()->m_hWnd;
	shfo.wFunc = wfunc;
	shfo.lpszProgressTitle=pszTitle;
	shfo.pTo=pszTo;
	shfo.pFrom=pszFrom;//FOF_NOCONFIRMATION
	shfo.fFlags = FOF_NOCONFIRMMKDIR|FOF_NOCONFIRMATION|FOF_SILENT|FOF_NOERRORUI;

	int ret = SHFileOperation(&shfo);
	double dtime2 = GetPrecisionTime();

	str1.Format("File move End(%s) %s - %.0f",strLot,strDate , (dtime2-dtime1)*1000);
	AddtoList(str1,0,TRUE);
	m_bCopyComplete = FALSE;
}

void CVisWebView::CopySurfaceImg( CString strBaseFolder, CString strLot )
{
	double d1 = GetPrecisionTime();
	CString strsrc1,strdst1,strpath,strpath1,strdst2,strdst3;

	strdst1.Format("%s\\Surface\\",strBaseFolder);//lot
	CreateDirectory(strdst1,NULL);	

	CString strLot1,strLot2,strLot3;
	int ncutno = atoi(strLot.Right(2));
	strLot1 = strLot.Left(7);
	strLot2.Format("%s_%03d",strLot1,ncutno);

	if(m_strComputerName.Find("CMI")>=0){
		strsrc1.Format("%s\\MisBack\\%s\\Surface\\",strBaseFolder, strLot);//head back

	}
	else if(m_strComputerName.Find("OCH")>=0){
		//41 42 46 47
		strLot2 = strLot;		//200624 kjh
		strsrc1.Format("%s\\HeadBack\\%s\\Surface\\", strBaseFolder, strLot2);

	}

	// 표면검사 불량 이미지폴더 move
	strLot3.Format("path:%s , Lot:%s",strsrc1,strLot2);
	AddtoList(strLot3,0);
	SHFILEOPSTRUCT    shfo;
	WORD        wfunc;
	TCHAR        pszTo[1024] = {0};
	TCHAR        pszFrom[1024] = {0};
	TCHAR        pszTitle[MAX_PATH] = {0};
	wfunc = FO_MOVE;
	memset(pszTo, 0, sizeof(pszTo));   // 중요
	memset(pszFrom, 0, sizeof(pszFrom));
	strcpy(pszTitle, "MoveFile");
	strcpy(pszTo, strBaseFolder);
	strcpy(pszFrom , strsrc1);
	ZeroMemory(&shfo, sizeof(shfo));
	shfo.hwnd = AfxGetMainWnd()->m_hWnd;
	shfo.wFunc = wfunc;
	shfo.lpszProgressTitle=pszTitle;
	shfo.pTo=pszTo;
	shfo.pFrom=pszFrom;//FOF_NOCONFIRMATION
	shfo.fFlags = FOF_NOCONFIRMMKDIR|FOF_NOCONFIRMATION|FOF_SILENT|FOF_NOERRORUI;
	int ret = SHFileOperation(&shfo); //200624 kjh
	CString str;
	//ReadImageFile(strdst2,strdst1,strlot,strLot2);
	ReadImageFile(strBaseFolder,strdst1,strLot,strLot2);	  // 표면검사 이미지 로드후 csv만듬

	//
	// 	MoveImageFile(strdst2,strlot);
	// 	MakeDefectCsv(strdst2,strlot);		// defectFull.csv만듬	

	m_bLotchanging = FALSE;//Lot change 헤제
	str.Format("%s Lot End sur-Image Copy %.0f_%s_%s",strLot,(d1-GetPrecisionTime())*1000,strdst1,strLot);
	AddtoList(str,0);
}

void CVisWebView::MoveCSVFile(CString strbaseRoot,CString strLot)
{
	// 헤드 백  D:\Data\LOTdata\LotComplete\2020\03\09\NATC913 1\Head\NATC913 1\CMICT01AHB1
	// 헤드 탑  D:\Data\LOTdata\LotComplete\2020\03\09\NATC913 1\Head\NATC913 1\NATC913 1\CMICT01AHT1
	// 미스 백  D:\Data\LOTdata\LotComplete\2020\03\09\NATC913 1\Mis\NATC913 1\CMICT01AMB1
	// 미스 탑  D:\Data\LOTdata\LotComplete\2020\03\09\NATC913 1\Mis\NATC913 1\NATC913 1\CMICT01AMT1
	//표면검사  D:\Data\LOTdata\LotComplete\2020\03\09\NATC913 1\Surface\NATC913_001

	CString strMovepath[5],strMovepath1[5],strlot,strlot1;
	strlot = strlot1 = strLot;
	int ncutno = atoi(strlot1.Right(2));
	strlot1.Format("%s_%03d",strLot.Left(7),ncutno);

	//이동경로
	strMovepath[0].Format("%s\\HeadTop\\",strbaseRoot);
	strMovepath[1].Format("%s\\HeadBack\\",strbaseRoot);
	strMovepath[2].Format("%s\\MisTop\\",strbaseRoot);
	strMovepath[3].Format("%s\\MisBack\\",strbaseRoot);
	strMovepath[4].Format("%s\\Surface\\",strbaseRoot);
//	for(int i=0;i<5;i++)	CreateDirectory(strMovepath[i],NULL);

	//오리진 경로
	strMovepath1[0].Format("%s\\HeadTop\\",strbaseRoot);
	strMovepath1[1].Format("%s\\HeadBack\\",strbaseRoot);
	strMovepath1[2].Format("%s\\MisTop\\",strbaseRoot);
	strMovepath1[3].Format("%s\\MisBack\\",strbaseRoot);
	strMovepath1[4].Format("%s\\Surface\\",strbaseRoot);

	//move file
	CFileFind finder,finder1;
	BOOL bRet;
	CString strFile1,pathname,filename,strpathname,strnewfile,strFile2;
	strFile1.Format("*.bmp");
	strFile2.Format("*.csv");
	for(int i=0;i<4;i++){
// 		BOOL isFind = finder.FindFile(strMovepath1[i]+strpc[i]+"\\"+strFile1);
// 
// 		while (isFind){
// 			isFind = finder.FindNextFile();
// 			pathname = finder.GetFilePath();
// 			filename = finder.GetFileName();
// 			strpathname = finder.GetFilePath();
// 			if ( finder.IsDirectory() || finder.IsDots() )
// 				continue;
// 			else
// 			{
// 				strnewfile.Format("%s\\%s",strMovepath[i],filename);
// 				//				CopyFile(pathname,strnewfile,FALSE);
// 				MoveFile(pathname,strnewfile);
// 			}
	//	}
		//csvfile
		BOOL isFind1 = finder1.FindFile(strMovepath1[i]+strFile2);
		while (isFind1){
			isFind1 = finder1.FindNextFile();
			pathname = finder1.GetFilePath();
			filename = finder1.GetFileName();
			strpathname = finder1.GetFilePath();
			if ( finder1.IsDirectory() || finder1.IsDots() )
				continue;
			else
			{
				strnewfile.Format("%s\\%s",strbaseRoot,filename);
				//				CopyFile(pathname,strnewfile,FALSE);
				MoveFileEx(pathname,strnewfile,MOVEFILE_REPLACE_EXISTING);
			}
		}
	}
}

void CVisWebView::WriteLastDataCSV(CString time, int meter, CString strCoat, CString strNCoat, CString strlot, int nLine)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	CString strTime, strLot, strData, strfilepath, strtmp;
	CStdioFile   file;
	int nMeter = 0;
	CString data[6];
	CTime timer=CTime::GetCurrentTime();	
	CString ymd = timer.Format("%Y%m%d");
	CString strTitle;

	strTitle.Format(_T("Time,Lot,Meter,"));
	for(int i=0; i<(nLine/2)-1; i++){
		strtmp.Format(_T("Coat%d,"), i+1);
		strTitle += strtmp;
	}

	for(int i=0; i<nLine/2; i++){
		strtmp.Format(_T("N-Coat%d,"), i+1);
		strTitle += strtmp;
	}

	strTime = time;
	strLot = strlot;
	nMeter = meter;
	strData.Format(_T("%s,%s,%d,%s%s"), strTime, strLot, nMeter, strCoat, strNCoat);
	strfilepath.Format(_T("D:\\Data\\Lotdata\\%s\\%s\\%s_%s_LastData.csv"), ymd, strLot, strLot, m_strComputerName);

	if(!file.Open(strfilepath, CFile::modeReadWrite|CFile::typeText)) 
	{		
		if(file.Open(strfilepath, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText))
		{	
			file.WriteString(strTitle);
			file.WriteString("\n");
			file.WriteString(strData);
			file.Close();
		}
	}
	else
	{
		file.SeekToEnd();
		file.WriteString("\n");
		file.WriteString(strData);
		file.Close(); 
	}

}

void CVisWebView::WriteLastData(CString strlot)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();

	// Last Data show
	CString strLastDataC;
	CString strLastDataNC;
	int nDist = 0;
	if(pDoc->m_pDlgInterface->m_bLastData){
		if(m_strComputerName.Mid(8,1)=="H"){
			if(m_strComputerName.Mid(9,1)=="T")
				nDist = (int)(pDoc->m_pDlgInterface->m_dTopBackDistance*2)+pDoc->m_pDlgInterface->m_nRewinderDistance;
			else
				nDist = (int)(pDoc->m_pDlgInterface->m_dTopBackDistance)+pDoc->m_pDlgInterface->m_nRewinderDistance;
		}
		else{
			nDist = pDoc->m_pDlgInterface->m_nRewinderDistance;
		}
		while (m_qLastData.size()>100+nDist){
			if(!m_qLastData.empty())
				m_qLastData.pop();
		}

		for(int i=0; i<100; i++){
			if(!m_qLastData.empty()){
				strLastDataC = m_qLastData.front().strCoat;
				strLastDataNC = m_qLastData.front().strNCoat;			
				WriteLastDataCSV(m_qLastData.front().strTime, m_qLastData.front().nMeter, strLastDataC, strLastDataNC, strlot, m_qLastData.front().nLine);
				m_qLastData.pop();
			}
		}
		strLastDataC = _T("COAT : ") + strLastDataC;
		strLastDataNC = _T("NCOAT : ") + strLastDataNC;
		m_DlgLastData->LastDataShow(strLastDataNC, strLastDataC);
		LastDataShow(strLastDataC, strLastDataNC);

		// last data queue clear
		for(int i=0; i<m_qLastData.size(); i++)
			m_qLastData.pop();
	}
}
	
// 20201016 kjh
void CVisWebView::ShowLogControls( bool bShow )
{
	BOOL bShowNew = FALSE;
	
	bShowNew = bShow?TRUE:FALSE;

	GetDlgItem(IDC_LIST1)->ShowWindow(bShowNew);
	GetDlgItem(IDC_LIST2)->ShowWindow(bShowNew);
	GetDlgItem(IDC_STATIC_LAST_DATA_COAT)->ShowWindow(!bShowNew);
	GetDlgItem(IDC_STATIC_LAST_DATA_NCOAT)->ShowWindow(!bShowNew);
}

void CVisWebView::LastDataShow( CString strCoat, CString strNCoat )
{
	m_lbLastDataCoat.SetText(strCoat);
	m_lbLastDataNCoat.SetText(strNCoat);
}

// 20201019 kjh
BOOL CVisWebView::LoadModelINIFile( CString strModel )
{
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)GetDocument();

	CString strPath = "C:\\GLIM\\";
	strPath+="Model\\"+strModel+".ini";
	BOOL bProductCheck = FALSE;
	CString str1;


	pDoc->m_data.m_strDefaultModel = strModel;
	//화면 update
	CString strmodel;
	strmodel.Format("Model:\r\n %s", pDoc->m_data.m_strDefaultModel);
	SetDlgItemText(IDC_NETWORK_TEST,strmodel);
	m_SysParam->m_lbModelNO.SetText(strmodel);
	m_defectMap->DrawModel(strmodel);			// 20201018 kjh

	UpdateTolIni(strModel);
	pDoc->m_pDlgInterface->LoadSysParam();
	pDoc->m_pDlgInterface->LoadInsParam();
	pDoc->m_pDlgInterface->	LoadLightParam();

	WriteModel();

	if(pDoc->m_pDlgInterface->m_bPLCModelSync)
		WriteShareMemorySpec();

	OffsetCheck();
	pDoc->m_pDlgInterface->UpdateData(false);	
	m_pModelDlg->m_strSelectProduct = strModel;
	m_pModelDlg->UpdateData(false);

	UpdateData(FALSE);
	return TRUE;
}

	