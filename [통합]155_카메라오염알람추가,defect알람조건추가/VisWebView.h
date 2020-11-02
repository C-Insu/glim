// VisWebView.h : interface of the CVisWebView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VISWEBVIEW_H__CA315FDB_DA53_460F_A712_A08CAF97EF09__INCLUDED_)
#define AFX_VISWEBVIEW_H__CA315FDB_DA53_460F_A712_A08CAF97EF09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "Network_module_server/Packet.h"
#include "TimingProcess.h"
//#include "WinSerial.h"	// Added by ClassView
#include "label1.h"
//#include <Afxmt.h>
#include "Inspect.h"	// Added by ClassView
#include "afxwin.h"
#include "m_dialogCustom.h"
#include "CisSetting.h"	//ljn
#include "StdAfx.h"

//#include "LightCtrlComm.h"
#include "LightCtrlComm.h"
#include "DlgDefectMap.h"
#include "SharedMemory.h"

#include "CgIOTotal.h"

#include "NumPad.h"
#include "AlarmDlg.h"
#include "DlgSysParam.h"
#include "DlgLastData.h"
#include "Password.h"
#include "ModelDlg.h"
#include "DlgMeterData.h"
#include "DlgFullImage.h"
#include "DlgViewImage.h"
#include <queue>
#include <list>

// 20201022 KJH METER RATIO DEFECT 파라미터용 구조체
typedef struct tagMeterRatioDefect{			
	int nMeter;	// meter
	bool bDefect;	// defect 유무

	tagMeterRatioDefect(){
		nMeter = 0;
		bDefect = false;
	}
}METER_RATIO_DEFECT;

typedef struct tagLAST_DATA
{
	CString strTime;
	int nMeter;
	CString strCoat;
	CString strNCoat;
	int nLine;

	tagLAST_DATA(){
		strTime = _T("");
		nMeter = 0;
		strCoat = _T("");
		strNCoat = _T("");
		nLine = 0;
	}
}LAST_DATA;

class CVisWebView : public CFormView
{
protected: // create from serialization only
	CVisWebView();
	virtual ~CVisWebView();
	DECLARE_DYNCREATE(CVisWebView)
private:
	void UpdateStatistics(BOOL bResult, double dInsTime,int nCam);

public:
	//{{AFX_DATA(CVisWebView)
	enum { IDD = IDD_VISWEB_FORM };
	int		m_nCoatPixel1[10];
	int		m_nLastLineCount[5];//0 카운트 1 라인수 2코팅수 3무지시작
	BOOL	m_bChageShutter;
	BOOL	m_bDrawStats;
/////////////////mismatch View
	CString CVisWebView::GetLightValue1(int nValue,int nMid);//ms 10진수 -> 16진수로
	int CVisWebView::GetLightValue2(CString str);//16진수 string -> 10진수로
	int		m_nScratchCount;
	BOOL	m_bChangeLight;
	int		m_nSaveNgCode;
	BOOL	m_bNonCoat[2];//0 new 1 old
	BOOL	m_bEdgeView;
	CDlgViewImage * m_ViewImage;//EdgeView
	CImage * m_fmEdgeVew[20];
	int CVisWebView::DataResultSaveFull(int nCam);
	BOOL	m_bNewMode;//0 이전 버전 1수정버전
	BOOL CVisWebView::Inspect3(int nCam);
	void CVisWebView::SaveEdgeImage(int nMeter,int nCount,CString strLot,int nSharpness, CString& strFilePath);
	void CVisWebView::WriteSharpness(CString strLot, int nMeter,int nCount, CString strFilePath);

	int m_nInspFrame[2];//0 grab 1 inspect
	int CVisWebView::MagImageCopy(int nLine1,int nLine2);
	CString	m_strCodeMsg;
	int CVisWebView::CheckReceiveFolder();
	int CVisWebView::CheckCode(CString strcode,CString strFullpath);
	void CVisWebView::LotChange() ;
	BOOL	m_bLotChange[10];//lot change
	CString	m_strLotChangeID[10];
	CString	m_strLotChangeTime[10];
	int		m_nLotChangeCount;
	CString m_strServerSendFileName[10];//0 1M file 1 defectfile 
	void CVisWebView::WriteLotModel(CString strlot);
	void CVisWebView::WriteDefectDataServerSend(CString strLot, double dMeterY, double dMeterX, double dsx,double dsy, double dvalue,CString strType,CString strimg,CString imgname,CString newpath,int nMeter, CString strmodel,CString strcolor, double dgain,double dsize1,double dmaxgray,double dmingray, double davegray,double dthvalue,CString strLocaltime, int nInspLocation);
	void CVisWebView::WrtieMeterData(CString strLot,int nMeter, int nSubFrame, int nLineCount,int nReverse) ;
	int		m_nSelectPlcModelNo;
	CString	m_strPlcModelname[40];// PLC 최대 20개
	CString CVisWebView::CheckModelNo(int no1);
	void CVisWebView::WritePlcModel();
	void SendPgmStatus(int nTopBack, int nStatus);					// 검사기 상태정보 plc전송
	void SavePLCSendDataLog(CString* strLogCoat, CString* strLogNCoat, CString* strLogMismatch, CString strLot, int nMeter);
	int GetPGMStatus();

	//20201008
	// Lotchange시 폴더복사 및 csv파일 생성함수
	void CopyLotDataFolders(CString strlot, CString strtime);		// NG이미지 & Sharpness이미지 폴더 복사
	void CopyLotData(CString strSrc, CString strDst, CString strLot, CString strtime);
	void CopySurfaceImg(CString strBaseFolder, CString strLot);
	void MoveCSVFile(CString strbaseRoot,CString strLot);

	// Lotchange시 마지막 폭데이터 디스플레이 및 이전 m의 폭데이터 csv파일로 저장
	std::queue<LAST_DATA> m_qLastData;
	void WriteLastDataCSV(CString time, int meter, CString strCoat, CString strNCoat, CString strlot, int nLine);
	void WriteLastData(CString strlot);
	CLabel m_lbLastDataCoat;
	CLabel m_lbLastDataNCoat;
	void LastDataShow(CString strCoat, CString strNCoat);
	bool m_bIsCoatedImg;

	// server model
	CString m_strServerModel;

	// cmi 수정내용
	void ShowLogControls(bool bShow);

	// 카메라 오염 알람 20201020
	int m_nNonCoatStartMeter;
	int m_nNonCoatEndMeter;
	int m_nCameraDirtCnt;
	int m_nCoatingOn;

	// 20201022 kjh meter ratio defect parameter
	std::list<METER_RATIO_DEFECT> m_listMeterRatio;
	

	CDlgFullImage * m_pDlgFullImage;
	int		m_nFoilCheck;
	int		m_nFoilCount;
	double m_dFoilSize[MAX_LENGTH];
	int	m_nThreadcheck[MAX_CAMERAS];
	void CVisWebView::ReadDefectCount(CString strlot);
	void CVisWebView::WrtieDefectCount(int nCount,CString strlot);
	int CVisWebView::WriteShareMemorySpec();//context = 0 미스매치 1무지상 2무지하 3코팅상 4코팅하 index눈 순서
	int CVisWebView::WriteShareMemory1(int context, int nindex,int dv1);//context = 0 미스매치 1무지상 2무지하 3코팅상 4코팅하 index눈 순서
	int CVisWebView::WriteShareMemory2(int context, int nindex,CString str1);//context = 0 미스매치 1무지상 2무지하 3코팅상 4코팅하 index눈 순서
	void CVisWebView::fnWriteDataFull1(CString strLot, int nMeter, double dtopscale1, double dbackscale1,double dtopscale2, double dbackscale2, int nLine,CString strHmis,CString strMmis,
		CString strHtop, CString strHback,CString strMtop, CString strMback, CString strHwid1,CString strHwid2,CString strMwid1,CString strMwid2); //미스매치부 탑백 동기화 관련

	
	BOOL	m_bLotchanging;//lot complete가 됐느느지 확인용.
	double	m_dRealMeter[2];//0척a 1척B
	void OffsetCheck();
	void CVisWebView::WriteLotEnd(CString strLot);
	void CVisWebView::CopyHeaderFile(CString strlot);
	void CVisWebView::CopyImageFile(CString strlot);
	void CVisWebView::CopyMisFile(CString strlot);
	CString m_strOldLot;//check용
	CString m_strOldLot1;//data copy용
	void CVisWebView::CopyMismatchFile2();//head back data를 mis 백에서 가져오기
	void CVisWebView::ReadMismatchData1(CString strfile,CString strLot);//mismatch bacck에서 head back 데이터 리드
	void CVisWebView::fnDataPut3(CString strInput,int nMeter,int ncount, int nRevserse);//mismatch bacck에서 head back 데이터 넣기 //ncount 1M 내에 몇번째 텍스트인지
	void CVisWebView::fnWriteDataFull(CString strLot, int nMeter, double dtopscale1, double dbackscale1,double dtopscale2, double dbackscale2, int nLine,CString strHmis,CString strMmis,
	CString strHtop, CString strHback,CString strMtop, CString strMback, CString strHwid1,CString strHwid2,CString strMwid1,CString strMwid2); //미스매치부 탑백 동기화 관련
	void CVisWebView::MoveImageFile(CString strbaseRoot,CString strLot);

	void CVisWebView::WriteSurDefect(CString strBase, CString strpath,CString strname,CString strLot);
	void CVisWebView::ReadImageFile(CString strBase, CString strBmpPath,CString strlot,CString strlot1);
	void CVisWebView::MakeOneCsvFile(CString strFilename,CString strNewName);//D:\Data\LOTdata\LotComplete\2020\03\09\NATC913 1
	void CVisWebView::MakeDefectCsv(CString strbaseRoot,CString strLot);//D:\Data\LOTdata\LotComplete\2020\03\09\NATC913 1
	BOOL CheckNsysNGFile();
	void CountNsysNg(CString strNgType);


	BOOL m_bCopyComplete;
	BOOL	m_bPassCheck;
	int	m_nCylinderOnOff;
	void CVisWebView::ReturnWidthCheck(int nLine);
	void CVisWebView::fnWriteData7(CString strLot,int nMeter,double dtopscale,double dbackscame,int nLine,CString strtop,CString strback,CString strmis,CString strwid1,CString strwid2); //미스매치부 탑백 동기화 관련;
	void CVisWebView::fnWriteData9(CString strLot,int nMeter, int nSubFrame,double dtopscale,double dbackscame,int nLine,CString strtop,CString strback,CString strmis,CString strwid1,CString strwid2); //미스매치부헤드부 동기화 관련


	BOOL	m_nUsecheck[20];
	void CVisWebView::DrawXMark(CDC * pDC,CPoint p1,CPoint p2,CPoint p3,CPoint p4,COLORREF lColor, int nLineWidth,int nline);
	int		m_nLineRunning;
	double	m_dCheckTime[2];
	CPoint	m_ptLinePos[20][2];//0 위쪽 1아래	수치표시에 X mark //0301
	CPoint	m_ptLinePos1[20][2];//0 위쪽 1아래	이미지에 X mark//0301

	BOOL	m_bTestInspect[MAX_CAMERAS];
	void CVisWebView::FolderInspect();
	int		m_nRestartSkipFrame;//미코팅후 재코팅한후 스킵 프레임
	int		m_nLimitLane;
	void CVisWebView::RectInvalidate(int nCount);
	int		m_nLineCountMiss;
	CBitmap  m_Bitmap;
	int	m_nCamNoiseCheck;
	int	CVisWebView::CheckCamera();
	int m_nLastBrightness[MAX_CAMERAS];
	int		m_nStartSkipFrame[MAX_CAMERAS];
	int		m_nInspTimeOut;
	double m_dLastCoatWidth[40];
	CString m_strLastCoatWidth;
	CString m_strLastNonCoatWidth;
	int		m_nDisplayDraw;
	void CVisWebView::WriteLog2(CString str,int nCam);
	int		m_nTextColor[100]; // 0 black 1 blue 2 red
	BOOL	m_bMismatchView;
	void	DrawMismatch();
	int		m_nInspBreak[MAX_CAMERAS];//time out으로 빠져나오는거 체크
	void CVisWebView::ChangeTol2(BOOL bcheck, int nselect, CString str);
	CPassword * m_pPassword;//password

	CDlgLastData *m_DlgLastData;
	CModelDlg	*m_pModelDlg;
	CDlgMeterData *m_pMeterData;

	// lotchange interval check 200901 kjh
	double m_dLotChangeIntervalStart;
	double m_dLotChangeIntervalEnd;
	double m_dChuckChangeIntervalStart;
	double m_dChuckChangeIntervalEnd;
	int m_nOldLotMeter;


	int m_nOldEdgeCount;
	int CVisWebView::CheckPosition(int nLine);//invalidateRect
	int CVisWebView::InlinePreProcessing(int nCam,int nIndex,int nMod);//thread call
	BOOL	m_bPreprocessing[MAX_CAMERAS][10];
	void CVisWebView::fnWriteData6(CString strLot,int nMeter,double dtopscale,double dbackscame,int nLine,CString strtop,CString strback,CString strmis); //미스매치부 탑백 동기화 관련
	void CVisWebView::fnDataPut2(CString strInput,int nMeter,int ncount, int nRevserse); //ncount 1M 내에 몇번째 텍스트인지



	int CVisWebView::PreProcessing1(BYTE * fmsrc,BYTE * fmdst,int nCam,int nw,int nh,CRect rt,int nMag);//Projection
	int CVisWebView::PreProcessing2(BYTE * fmsrc,BYTE * fmdst,int nCam,int nw,int nh,CRect rt,int nMag);//미분
	int CVisWebView::PreProcessing3(BYTE * fmsrc,BYTE * fmdstblack,int nCam,int nw,int nh,CRect rt,int nMag);//영역의 흑
	int CVisWebView::PreProcessing4(BYTE * fmsrc,BYTE * fmdstwhite,int nCam,int nw,int nh,CRect rt,int nMag);//영역의 백

	int CVisWebView::PreProcessing11(BYTE * fmsrc,BYTE * fmdst,int nCam,int nw,int nh,int nIndex,int nMod,int nMag);
	int CVisWebView::PreProcessing12(BYTE * fmsrc,BYTE * fmdst,int nCam,int nw,int nh,int nIndex,int nMod,int nMag);
	int CVisWebView::PreProcessing13(BYTE * fmsrc,BYTE * fmdstblack,int nCam,int nw,int nh,int nIndex,int nMod,int nMag);
	int CVisWebView::PreProcessing14(BYTE * fmsrc,BYTE * fmdstwhite,int nCam,int nw,int nh,int nIndex,int nMod,int nMag);

	void CVisWebView::DataDraw1(CRect rt,CString str,int nLineWidth, COLORREF lColor,BOOL bRect);
	void CVisWebView::DrawRectangle1(CDC *pDC, CPoint p1, CPoint p2, CPoint p3, COLORREF lColor, int nLineWidth,int nCam,int nCount,CString strmm,CString strinsul);
	void CVisWebView::DataDraw(CPoint pt1,CPoint pt2,CString str,int nLineWidth, COLORREF lColor,BOOL bRect,int ncount);
	void CVisWebView::LightChange(int n=0);
	int CVisWebView::InsulateDefectCheck();
	int CVisWebView::InsulateDefect(int nCam,int nIndex,int nHeight=CAM_HEIGHT_CIS,int nMod = MOD_COUNT);
	BOOL	m_bInsulateDefect[10];
	double m_dDebugTime[MAX_CAMERAS][100];
	BOOL	m_bDebug;
	int CVisWebView::FullLineProjection(int nCam,int nIndex,int nHeight=CAM_HEIGHT_CIS,int nMod = MOD_COUNT);
	BOOL	m_bLineProj[10];//thread check
	int	CVisWebView::TransLineData();//개별 데이터를 전체 데이터로 평균냄
	BOOL	m_bWaitThread[3];//풀이미지 wait flag
	BOOL CVisWebView::Inspect1(int nCam);
	BOOL CVisWebView::Inspect2(int nCam);
	int	CVisWebView::FindInsulate();//절연검사

	int	CVisWebView::FullLineSearch();

	// ENG/KOR
	void	ChangeControlsLanguage(BOOL bLang = ENG);

	void CVisWebView::capture1(CString strlot,int nMeter);
	BOOL	m_bFullCopy[3];

	CString m_strPitchMismatch[20];
	int		m_nLengFrmaeGap;//top back 전체폭 차이 프레임
	double	m_dTopScale;
	int	m_nCamPort;
	int	m_nIOPort;
	int CVisWebView::ReadPort(CString strport);
	void CVisWebView::WriteMisMatchData2(int nframe,int nCount);
	void CVisWebView::SetShareMemory();
	CSharedMemory	m_sharedMemoryWrite1[20][20];//mismatch
	int CVisWebView::WriteShareMemory(int context, int nindex,double dv1);//context = 0 미스매치 1무지상 2무지하 3코팅상 4코팅하 index눈 순서
	void WriteUseCheck(int nTopBack, int nLineCnt);	// 0:top, 1:back

	int	m_nOldFrame;//PLC Check
	double m_dOldMeter[2];
	double m_dLastTenMeter[10][40];
	BOOL	m_bNewAlarm;
	int		m_nNewAlarm;
	int		m_nLineProjData[6][CAM_WIDTH_CIS*3];

	CString			m_strMemoryWriteAddress1[20][20];//mismatch 
	bool	m_bCoatingOnSignal;

	void CVisWebView::CheckStats(int ncam,int nio);//홀수 녹색 짝수 빨강
	double	m_dNewScaleX;
	double	m_dScaleSum;
	double m_dLenthSum;
	int		m_nLnethCnt;
	CString m_strAlarmMsg;
	CString m_strAlarmMsg1;//meter 표시
	int	m_nAlarmCnt;
	int	m_nAlarmCnt1;
	int	m_nDataMissing;
	int	m_nOldLine;
	CString	m_strOldFilename;
	CString	m_strOldFilename1;
	CString	m_strOldFilename2;
	CString	m_strOldFilename3;
	void CVisWebView::WriteLog1(CString str);
	CString m_strNewLot;
	void CVisWebView::ShowTopLength(int nCount);
	void CVisWebView::UpdateTolIni(CString strModel,BOOL bLoad=TRUE);
	CString	m_strModelPath;
	double	m_dTolerance[MAX_LENGTH*2];
	double	m_dTolerance1[MAX_LENGTH*2];
	double	m_dTolerance2[MAX_LENGTH*2];
	double	m_dStardLen[MAX_LENGTH];
	double	m_dStardLen1[MAX_LENGTH];
	int	m_nBrightcheck[MAX_CAMERAS];
	CFont	m_DispFont;
	CFont	m_DispFont1;
	int		m_nAlarmOn;
	void CVisWebView::ChangeTol1(BOOL bcheck, int nselect, CString str);
	void CVisWebView::fnDataPut1(CString strInput,int nMeter,int ncount, int nRevserse); //ncount 1M 내에 몇번째 텍스트인지
	void CVisWebView::ReadMismatchData(CString strfile,CString strLot);
	void CVisWebView::CopyDefectData(CString strLot,CString strDate);
	CString m_strOldTime;

	double	m_dMismatchModify; 
	double	m_dMismatchTolMax;
	double	m_dMismatchTolMin;
	double	m_dMismatchTolMax1;
	double	m_dMismatchTolMin1;
	BOOL	m_bMismatchBad[MAX_LENGTH];
	int		m_nSkipFrame[MAX_CAMERAS];
	void CVisWebView::WriteDefectData(CString strLot, double dMeterY, double dMeterX, double dsx,double dsy, double dvalue,CString strType,CString strimg,CString imgname,CString newpath, CString strmodel,CString strcolor, double dgain,double dsize1,double dmaxgray,double dmingray, double davegray,double dthvalue,CString strLocaltime);
	void CVisWebView::fnWriteData5(CString strLot,int nMeter, int nSubFrame, int nLineCount); //백 미스매치 기록
	void CVisWebView::CopyMismatchFile1();
	CString	m_strMisRecieve[10][100];//10 Meter 100 개 데이터
	
	int		m_nLaneCount;
	int		m_nLaneCount1;
	double	m_dLaneAve[2][MAX_LENGTH];//0top 1back
	double	m_dMismatchAve[MAX_LENGTH];
	int		m_nAlarmLog;
	int		m_nLAneDataCount[MAX_LENGTH];

	int		m_nNgFrameCount[100];//100 프레임
	int		m_nContinueCnt;

	BOOL	m_bAlarmOnOff;
	int		m_nAlarmStartFRame;
	int		m_nAlarmEndFRame;
///////////////////////////////////Log Lotdata
	CString m_strStartTime;
	CString m_strEndTime;
	double	m_dMeterY;


	////Frame 단위 불량 갯수
	int		m_nBadCountDefect[10];//0-드래그라인	1-무지라인	2아일랜드	3코팅드래그	4코팅라인	5핀홀	9토탈
	void CVisWebView::WriteLotInfo(CString strLot, CString strStartTime, CString strEndTime, double dMeter, int nDefect1, int nDefect2, int nDefect3, int nDefect4, int nDefect5,int nDefect6, int nDefect7, int nDefect8, int nDefect9, int nDefect10);

	int		m_nMismatchBadCount;

	void CVisWebView::WriteModel();
	void CVisWebView::ReaModel();
	int		m_nNGCount[MAX_LENGTH];

	CString m_strOldPath;
	BOOL	m_bMismatchUse;
	BOOL	m_bCopyFile;
	BOOL	m_bCopyFile1;
	BOOL	m_bCopyFolder;
	BOOL	m_bCopyFolder1;
	BOOL	m_bLotWriteCheck;
	BOOL	m_bDrawCheck;
	CRect	m_rtDetailView;
	CNumPad	*m_NumPad;
	CDlgSysParam * m_SysParam;
	CAlarmDlg *m_AlarmDlg;
	CCisSetting *m_cis;	//ljn 추가 
	int		m_nSelectNum;
	void CVisWebView::ChangeTol(BOOL bcheck,int nselect, CString str);
	BOOL	m_bUseLen[MAX_LENGTH];
	BOOL	m_bUseInSulate[MAX_LENGTH];//절연 사용 유무
	BOOL	m_bUseInSulate1[MAX_LENGTH];//절연 okng
	BOOL	m_bUseMismatch[MAX_LENGTH];
	BOOL	m_bNGLen[MAX_LENGTH];
	int		m_nNsysNgCount[MAX_DEFECT_COUNT];

	CgIO		m_IO[1];
	int CVisWebView::InitIO();

	int		m_nLineCount;
		//ljh

	//char 배열로 가져온뒤 처리

	CString CVisWebView::ConvertCharToStr(char* cChar);


	char cLotID[100];
	char cLotCurrent[100];
	char cLotOld[100];

	


	CSharedMemory	m_sharedMemory[20];
	BOOL			m_bMemoryConnect[20];
	CString			m_strMemoryAddress[20];
	BOOL			m_bMemoryIsUse[20];
	int				m_nPlcData[20];
	CString			m_strPlcLot[2];
	CString			m_strLotID;
	int				m_nRwRollA;
	int				m_nRwRollB;
	int				m_nRwRollIncA;
	int				m_nRwRollIncB;
	int				m_nRwChkCnt;
	int				m_nRwChkCntTemp;
	BOOL			m_bRwToggle;
	int				m_nOldChuck[2];

	int CVisWebView::CheckOnRwAB(int nRwRollA, int nRwRollB);
	BOOL CVisWebView::CheckChangeLotID(CString lotID);
	int CVisWebView::GetPlcData();
	CString CVisWebView::GetDefectType(int nDefect);
	CString	m_strLbLotInfo[15];
	char*	m_charLbLotInfo[15];
	CString m_strTopMismatch;

	BYTE * fmDummy[MAX_CAMERAS];
	BOOL	m_bCopyData;//Mismatch Data Copy
	void CVisWebView::fnDataPut(CString strInput,int nMeter,int ncount, int nRevserse);
	int CVisWebView::OnebyOneMatch(int nDirect,int nframe, int nLinecount);
	void CVisWebView::WriteMisMatchData1(int nframe,int nCount);

	CDlgDefectMap* m_defectMap;
	void CVisWebView::DrawGridLine2(CDC *pDC, int nWidthCnt);
	void CVisWebView::RedrawMap();
	void CVisWebView::RoiInspect(int nCam,int nIdx,int nMod);
	void CVisWebView::ShowCoatTitle(int nCount);
	CPoint CVisWebView::DrawPitchCam(CDC *pDC, CPoint p1, CPoint p2, COLORREF lColor, int nLineWidth,int nCam,int nLine);
	void CVisWebView::DrawRectangle(CDC *pDC, CPoint p1, CPoint p2,CPoint p3, COLORREF lColor, int nLineWidth,int nCam,int nCount,CString strmm);
	void	AddtoList(CString strData,int mode,BOOL bWrite=FALSE);
	void CVisWebView::AddtoInsLog(CString strData,BOOL bWrite=FALSE);
	void CVisWebView::WriteLengthData(double dMachineLen);
	void CVisWebView::WriteLog(CString str);
	void CVisWebView::ReadLengthData(CString strfile,CString strLot,CString strcom,int nreadlen);
	void CVisWebView::CopyMismatchFile();
	int CVisWebView::DataResultSave(int nCam);
	int CVisWebView::UpdateControl();
	void CVisWebView::fnWriteData3(CString strLot,int nMeter, int nSubFrame, int nLineCount);
	void CVisWebView::fnWriteData4(CString strLot,int nMeter, int nSubFrame, int nLineCount);

	double	m_dMachineLength;//현재 설비 길이
	int		m_nOldLength;//현재 설비 길이
	int		m_nReadLength;//미스매치할 길이
	int		m_nTextWriteCount;//text파일에 기록된 카운트 줄수

	int m_nResultOkNg;
	CRect	m_rtArea;
	int m_nPosCount;
	double m_dCellPos[60];
	double m_dCellWidth[60];
//	CImage * m_pDefectImage[MAX_CAMERAS][5];
	CImage * m_pDefectImage[15];
	void CVisWebView::BadImageShift(int nCam,BYTE * fm,BOOL bchange,CString defectname);
	void CVisWebView::LoadAllImage();



	void CVisWebView::GetCaliData(int  nCam,int  nMode);
	void CVisWebView::SummaryEdgeData();

	CString staticString;
	CString staticString1;
	CString staticString2;
	int m_nSaveCheck[MAX_CAMERAS];

	void CVisWebView::ReadDummyData1(int nCam);//일부scale수정용

	void CVisWebView::LoadImage1();

	CMutex g_Mutex;
///////////// new mode

	void ReadCalData(int nCam);
	void CVisWebView::ReadDummyData(int nCam);
	void CVisWebView::fnWriteData1(int frame,int defectcnt,int defectclass,float px, float py,float sx,float sy, CString imgpath,double dBcrY,double dRecieveY,double thup, double thdn,double dtmp1,int flag,int nCam);
	void CVisWebView::fnWriteData2() ;


	void CVisWebView::InitClass();
	int CVisWebView::InitCamera(int nLine);
	void CVisWebView::InitCimage(int nLine);
	void CVisWebView::InitThread(int nLine);
	void CVisWebView::InitExposure(int nCam,int nLine,int nShutter);
	void CVisWebView::InitSocket(int nLine);
	void CVisWebView::InitData(int nLine);
	void CVisWebView::InitTimer(int nLine);
	void CVisWebView::FullImageProjection() ;
	void CVisWebView::TestInspect(int nCam,int nIdx,int nMod);
	void CVisWebView::DrawCross(CDC *pDC, CPoint p1, int nLinelength, COLORREF lColor, int nLineWidth);
	void CVisWebView::SendMarkingData(int nCam);
	void CVisWebView::SendMarkingDataTest(int nCam);
	void CVisWebView::AverageDataSet(int nCam,BOOL bokng);
	void CVisWebView::ResetFrame(int nCam);


	CLightCtrlComm m_LightCtrl[MAXLIGHTCOUNT]; 
	void CVisWebView::LightONWAVE(int nCh=0,int nPort=0);
	void CVisWebView::LightOFFWAVE(int nCh=0,int nPort=0);
	double CVisWebView::ReadLightDataWave(char data,int ch);

	void CVisWebView::DrawLineCam(CDC *pDC, CPoint p1, CPoint p2, COLORREF lColor, int nLineWidth,int nCam,int nLine);


	// Parameter send & receive		200709 kjh
	void WriteINIFileForServer();
	void ReadINIFileFromServer();
	BOOL ExistFile(CString strPath);
	void CreateINICheckFile();
	void AddCommentToServerINI(CString strINIFile, CString strINIFileNew);
	bool m_bSendServerINI;
	BOOL LoadModelINIFile(CString strModel);

////////////
	double CVisWebView::GetPrecisionTime(void);
	BOOL				m_bTestFlag[MAX_CAMERAS][MAX_INSPECT_COUNT];
	int				m_nInspFlag[MAX_CAMERAS][MAX_INSPECT_COUNT];
	BOOL	m_bTest[MAX_CAMERAS][MAX_INSPECT_COUNT];
	void CVisWebView::TestCopy(int nIdx,int nMod);
	BOOL CVisWebView::checkRect(int x1,int x2,int y1,int y2,int nx,int ny);

	BOOL	m_glabDoneCam0;
	BOOL	m_glabDoneCam1;

	bool	m_imageSaveExt;

	BOOL	m_bImageDelete;
	CLabel	m_labelWarning;
	CLabel	m_labelNGInfo;
	CLabel	m_labelStatistics;
	CLabel	m_labelResult;
	CLabel	m_labelSysInfo;
	CStatic	m_ctrlDisplay;
	UINT	m_nPortNum;
	BOOL	m_bImageSave;
	BOOL	m_bCheckAuto;
	BOOL	m_bAutoRun;
	BOOL	m_bImageSelect;
	int		m_nNotInsAreaView;
	BOOL	m_bViewImage;
	double	m_dXLineSkip;
	BOOL	m_bSimmulation;
	BOOL	m_bLotSave;
	BOOL	m_bLotDel;
	int		m_nExpose;
	int		m_nTacX;
	BOOL	m_bBinaryView;
	int		m_nYLine;
	BOOL	m_bViewTest;
	BOOL	m_bCrossBlobImg;
	int		m_nInsMethod;
	BOOL	m_bViewTest1;
	CString	m_strVolt;
	CString	m_strCElect;
	CString	m_strElect;
	int		m_nSelectCam;
	CString m_autoInsPath;
	CString m_autoPeriodInsPath1;
	CString m_autoPeriodInsPath2;

	CString m_strComputerName;
	//}}AFX_DATA

// Attributes
public:
	CVisWebDoc* GetDocument();

	int		m_nGrabFrame[MAX_CAMERAS];
	CInspect	m_Inspect;
	BOOL		m_bAuto;
	BOOL		m_bRun;
	CRect		m_rectNGImage;
	BOOL		m_autoEncoder;

	CEvent		m_eGrab;
	CEvent		m_eTextCopy;
	CEvent		m_eSaveImage;
	CEvent		m_eSaveImageCam2;
	CEvent		m_eSaveImageCam3;
	CEvent		m_eTextEndCopy;
	CEvent		m_ev_rbutton_down;
	CEvent		m_eLight;
	void	GrabSaveMini(int nCam);

	CEvent		m_eSaveImage1;
	CEvent		m_eSaveImage2;
	CEvent		m_eSaveImage3;
	CEvent		m_eSaveImage4;
	CEvent		m_eSaveImage5;
	CEvent		m_eSaveImage6;
	CEvent		m_eSaveImage7;
	CEvent		m_eSaveImage8;
	CEvent		m_eSaveImage9;
	CEvent		m_eSaveImage10;
	CEvent		m_eSaveImage11;
	CEvent		m_eSaveImage12;
	CEvent		m_eSaveImage13;
	CEvent		m_eSaveImage14;
	CEvent		m_eSaveImage15;

	BOOL		m_isLogSave;

	CWinThread	*m_pThreadMain;
	CWinThread	*m_pThreadAutoEncoder;
	CWinThread	*m_pThreadInspectTest;
	CWinThread	*m_pThreadInspect;
	CWinThread	*m_pThreadInspect1;//crosss cam 2
	CWinThread	*m_pThreadInspect2;//crosss cam 2
//	CWinThread  *m_pThreadlog;
	//CComPort m_cComm[MAXLIGHTCOUNT];

	int			m_nCkSplice;
	int			m_nCkSplice1;
	int			m_nCkSpliceCount;
	int			m_nCkTape;
	int			m_nSplice;
	BOOL		m_bSaving[MAX_CAMERAS];
	BOOL		m_bSaving1;
	BOOL		m_bSaving2;
	int			nRegCheck;
	int			m_nBestYLine;
	void		fnCheckLight();
	void	fnSaveThreadInit();

	int			m_nDefectSaveCnt;
	BOOL		m_bDefectSaveStats;

	
	void capture();
	HANDLE DDBToDIB(CBitmap &bitmap, DWORD dwCompression, CPalette *pPal);
	bool WriteDIB(CString szFile, HANDLE hDIB);	
/////////////////////////////////대명
	double	dCmaAverage[MAX_CAMERAS];// = 0;
	int		nAveCount[MAX_CAMERAS];// = 1;
	int		nEdgeCnt[MAX_CAMERAS];// = 1;
	double	dCamEdge[MAX_CAMERAS];

	int					InitCam();
	void CVisWebView::WriteLog(CString path,CString fileName, CString strdata);

	bool m_inspectCu1;
	bool m_inspectCu2;

	

	//테스트를 위한 부분-------------------------------------------- 
	CTimingProcess		*m_pTiming;			//	Coding reliability
	double				m_img_save_time;
	long				m_grab_index;
	void				GrabImgSave();
	void				GrabImgSaveCam2(int nCam);
	void				fnWriteMura(int bresult,double dave, int nmura, int nyoko);
// 	CEvent				m_ev_Inspect;
// 	CEvent				m_ev_Inspect1;
// 	CEvent				m_ev_Inspect2;
	void				fnWriteEndFile(CString name, int nCam);
	void				SetResolution(int nWidth,int nHeight);
	void				ChgExposure(int nCam);
	void	fnWriteData(CString strlot,int frame,int defectcnt,int defectclass,float px, float py,float sx,float sy, CString imgpath,double dBcrY,double dRecieveY,double thup, double thdn,double dtmp1,int flag,int nCam);
	void	CopyTextFile(CString src,CString dst,int Status);
	void	CopyEndTextFile(CString src,CString dst);
//	CString m_strSrctxtPath;
//	CString m_strDsttxtPath;
	CString m_strEnd;
	int		m_nTextcopy;
	int		m_nEndText;
	bool	m_bYSim;
	void	fnWriteSlice(int n,int nc,int nCam);
	int		m_nNewLot;
	void	fnWriteReceive(double dval, CString strReceive);
	void	fnPushPacket(CString strpacket,double dval,int nCam);
	int		fnPullData(int nframe,int nCam);
	void	fnDataReset();
	void	fnWritePacket(double dval,CString strReceive,CString strpack,int nCam);
	int		m_nGrabCount;
	int		m_nChgExposure;
	void	fnReadSkipPixel(int nCam);
	void	fnReadSkipPixel1(CString name,int nCam);
	void	PushDefectCycle(double x,double y,int nCam);
	int	CheckCycle(double x,double y,int nCam);
	int		m_nCheckCycle;
//	int		m_nLineValue[IMAGE_X];
	void	fnTrebleSkip(int nCam) ;
	void	fnRegLineValue(int nCam);
	void	fnWriteLight(CString strData);
	int		m_nCrossPolFrame;
	int		m_nCrossPolOffset;

	//--------------------------------------------------------------

	int		m_nStopFrame;
	int		m_nReStartFrame;
	void	fnFindFrame(CString str,int nCam);
	void	WriteAveParam(int nCam);
	void	AdjustAveParam(int nCam);
	void	fnAutoParam(int nStats,int nCam);
	CString				m_strImgTestName;
	void	fnchgExposure(int nCam) ;
	void		fnChangeLine(int nCam);

	double				m_dRemainHDDSpace;
	double				m_dRemainMainSpace;
	//// cho
	void		fnWriteResult(CString path,int nResult,CString strname,CString strmonth,int nCam);
	void		fnWritehtml(CString path,int nResult,CString strname,int nCam);
	void		fnDispButton(int nIndex);
	int			fnCheckLine(double *tv,double *bv,int nCam);
	void		fnSetPort();
	double		ReadLightData1CH(char data,int nport);
	char		m_cLamp;
	int			m_nPortNumber;
	void	getCurrentData(int nport=0);
	double	m_CurrentElectric[MAXLIGHTCOUNT];
	double	m_Voltage[MAXLIGHTCOUNT];
	double	m_Electric[MAXLIGHTCOUNT];

	void CVisWebView::LightONWAVE1CH(int nport);
	void CVisWebView::LightOFFWAVE1CH(int nport);

	BOOL m_bInsulateInspect;


// Operations
public:
	void		RecursiveDelete(CString szPath);
	void		AutoStart();
	void		AutoStop();
	void		AutoStartE();
	void		AutoStopE();

	void		ParamInstantRead(int nCode, LPSTR param_name, double val, LPSTR str_val);

	void		LoadImage();
	void		SaveImage();

	CRect		Scale(CRect rect);
	CPoint		Scale(CPoint point);
	CPoint		Scale(CPoint point,int nCam);

	void		DrawLine(CDC* pDC, CPoint p1, CPoint p2, COLORREF lColor, int nLineWidth = 1);
	void		DrawRect(CDC* pDC, CPoint p1, CPoint p2, COLORREF lColor, int nLineWidth = 1);
	void		DrawRect(CDC* pDC, CRect rect, COLORREF lColor, int nLineWidth = 1, BOOL bScale=TRUE);
	void		DrawText(CDC *pDC, CPoint pt, CString str);
	
	void		GetHDDSpace(CString strPath, long *total, long *occupied, long *remaining);
	void		HddRemainingAlarm();
	int			m_nMilGrabCount;
	int			m_nMilCopyCount;
	int			fnCheckFrame(CString strpacket,int nCam);
	int			m_nResetSystem;
	int			m_nResetCount;
	void		fnWriteBrightness(CString strPC,int nBright,int nCam);
	void		fnWriteResetFrame(int n,int nCam);

	int			CopyMilImgForSlit(LPBYTE fmLeft,int nCam);//, LPBYTE fmRight);
//	int			CopyMilImgForAreaReverse(LPBYTE fmOrigin, int nIndex);
//	void		SetChgLine(int line);
//	void		SetGiGaLanExposure(int ntime);
//	void		SetFrameRate(int ncount);
	int			m_nCheckNewLot;
	int			fnLGCheckFrame(CString strpacket,int nCam);
	int			m_nOldCount[MAX_CAMERAS];
	void		fnWriteEdge(int nLeft,int nRight,int nEdge,CString str11,int nCam);
	int			m_nThCount[MAX_CAMERAS];
	void		fnWriteSplice(int frame,int framecnt, int tapecnt);
	void		fnGetRealBrightness(int nCam);
	void		fnWriteFrame(int f1,int f2);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVisWebView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnDraw(CDC* pDC);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
//	BYTE*	m_backup_list;
	int		m_backup_idx;

	BOOL m_bReset;

	int BroadCasting(int bInspectResult,int nCam);

	void Decoding(int nPort, unsigned char* pData);//retouch
	BOOL Inspect(int nCam);
	void DrawData(CDC* pDC,int nCam);
	void InitControl();
	void InitSystemInfo();
	BOOL m_bDraw;
	BOOL m_bTest1;
	int m_nExposre1;
	int m_nExposre2;
	int m_nYLine1;


#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
public:
	int m_nMachine;//0양극 1음극
	void MakeIdelData(int nCam);
	int m_nFrameNum;
	void CreateDefaultDirectory();
	void DrawNotInsArea(CDC* pDC,int nCam);
	void GetHistoEqua();
	void DrawHistoData(CDC* pDC);
	BOOL m_bConnectCam;
	void SetWarning(CString str);
	void DrawFocusing(CDC* pDC);
	void DrawNGImage(CDC* pDC,int nCam);
	int m_nCurNGImgIndex;
	double m_avgBrightness[MAX_CAMERAS];
	BOOL m_bCalibBrightness;
	void Calib_Brightness(int value);
	BOOL m_bGrabDone;
	CString m_str_LotDataPath;
	void PreStep();
	float m_fFps;
	void DrawImage(int nCam);
	int CopyMilImg(int nCam);
	CListBox m_log2;
	BOOL m_bAlarmOff;

	BOOL CVisWebView::OnTestFunction(LPBYTE fmLeft,int nCam);

	void CVisWebView::LoadImage2();

	//{{AFX_MSG(CVisWebView)
	afx_msg void OnImageLoad();
	afx_msg void OnImageSave();
	afx_msg void OnButtonAuto();
	afx_msg void OnButtonExit();
	afx_msg void OnBtnLoadImg();
	afx_msg void OnDestroy();
	afx_msg void OnBtnInspect();
	afx_msg void OnButtonFrameReset();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnButtonRestartCasting();
	afx_msg void OnButtonInterface();
	afx_msg void OnCheckImageSave();
	afx_msg void OnButtonGridModify();
	afx_msg void OnCheckAuto();
	afx_msg void OnBtnNgImgBacward();
	afx_msg void OnBtnNgImgForward();
	afx_msg void OnBtImgTest();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnCkAuto();
	afx_msg void OnCkSaveImage();
	afx_msg void OnBtnGetProfile();
	afx_msg void OnButtonUpdateNotinsarea();
	afx_msg void OnCkViewImage();
	afx_msg void OnNetworkTest();
	afx_msg void OnCkSim();
	afx_msg void OnCkLot();
	afx_msg void OnCkLotdel();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnBinaryView();
	afx_msg void OnCkView2();
	afx_msg void OnCkBlob();
	afx_msg void OnCkView3();
	afx_msg void OnBtnGetProfile2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	BOOL m_bCamChange;
	afx_msg void OnBnClickedCheckCamchange();
	afx_msg void OnBnClickedBtnImageSave();
	BOOL m_bImageSaveAll;
	afx_msg void OnBnClickedCheckImageSaveAll();
	
	afx_msg void OnBnClickedButton4();
	
	int m_binaryValue;
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedBtnGetProfile3();
	double m_dDefectSize;
	int m_nThWhite;
	int m_nThBlack;
	afx_msg void OnBnClickedButton7();
	double m_dSlope;
	double m_dLineScratch;


////////////////////////////CLabel
	CLabel m_lbLotInfo;
	CLabel m_lbWinder1;
	CLabel m_lbWinder2;
	CLabel m_lbNullDrag;
	CLabel m_lbNullLine;
	CLabel m_lbNullIsland;
	CLabel m_lbCoatDrag;
	CLabel m_lbCoatLine;
	CLabel m_lbCoatPinHole;
	CLabel m_lbFullWidth;


	CLabel m_lbCoatTitle[MAX_LENGTH];
	CLabel m_lbCoatLen[MAX_LENGTH];
	CLabel m_lbCoatLenTop[MAX_LENGTH];

	CLabel m_lbDefectInfo[15];//Defect Information
	CListBox m_InspLog1;
	CLabel m_lbTopTitle;
	CLabel m_lbMisMatchTitle;
	CLabel	m_lPitchTol[MAX_LENGTH];
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnBnClickedCheckAlarmOff();
	CLabel m_lbLeft;
	CLabel m_lbRight;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CLabel m_lbMismatchTolMin;
	CLabel m_lbMismatchTolMax;

	CLabel m_lbStatsCAM;
	CLabel m_lbStatsIO;//IDC_STATIC_STATS_IO
	CLabel m_lbStatsPLC;//IDC_STATIC_STATS_IO
	CLabel m_lbStaticTBGap;//IDC_STATIC_BACKTOPGAP


	CLabel m_lbGapMisMatch[25];//IDC_STATIC_STATS_IO

	
	//void ResetCamera(void);
	afx_msg void OnBnClickedBtAlarmSet();
	afx_msg void OnBnClickedCheckInsul();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnWidthData();
	CLabel m_lbNonCoating;
	int CamCheckWD(void);
	BOOL m_bPrimer;
	afx_msg void OnBnClickedCheckPrimer();
	afx_msg void OnBnClickedButtonResetimage();
};

#ifndef _DEBUG  // debug version in VisWebView.cpp
inline CVisWebDoc* CVisWebView::GetDocument()
   { return (CVisWebDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISWEBVIEW_H__CA315FDB_DA53_460F_A712_A08CAF97EF09__INCLUDED_)
