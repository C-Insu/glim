#if !defined(AFX_DLGINTERFACE_H__25BFBCD8_09E8_4C52_844A_E8C62C8FCF99__INCLUDED_)
#define AFX_DLGINTERFACE_H__25BFBCD8_09E8_4C52_844A_E8C62C8FCF99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInterface.h : header file
//

#include "VisWebDoc.h"
#include "afxwin.h"


/////////////////////////////////////////////////////////////////////////////
// CDlgInterface dialog

class CDlgInterface : public CDialog
{
// Construction
public:
// 	void CDlgInterface::SaveShutter();
// 	void CDlgInterface::LoadShutter();


	void CDlgInterface::SaveLightParam();
	void CDlgInterface::LoadLightParam();;

	void CDlgInterface::ChangeBrightness(int nValue,int nMod,int nCommand);//nvale 10진수 정수 nmod 소수점0.5여부 , nCommand 20 40 60
	void CDlgInterface::ShowHideButton(int nshow);
	void ShowItem(int n1);
	int CheckGradeIni();
	void LoadGradeParam();
	CString server_ip;
	void SaveInsParam();
	void SaveSysParam();
	void LoadInsParam();
	void LoadSysParam();
	void ExposureChange();
	void ExposureChange(long value);
	int	m_nSelectEdit;
	void CDlgInterface::ChangeValue(int n,CString strvalue);
	void InitControl();

	int  m_nMachine;//0 양극 1 음극

	void LoadDefaultCalib();

	CString		ComputerName();
	CString		GetIp();
	CString		GetPgmVersion();	
	CWnd*	m_pParent;	
	CDlgInterface(CWnd* pParent = NULL);   // standard constructor
	int		nCycle1;
	int		nCycle2;
	int		nCycle3;
	int		nCycle4;
	int		nCycle5;
	int		nCycle6;
	int		nCycle7;
	int		nCycle8;
	int		nCycle9;
	int		nCycle10;
	int		nCycle11;
	int		nCycle12;
	int		nCycle13;
	int		nCycle14;
	int		nCycle15;

	double	m_dStandard[MAX_LENGTH];//최소값
	double	m_dMaxValue[MAX_LENGTH];//최대값
	double	m_dStandard1[MAX_LENGTH];//최소값
	double	m_dMaxValue1[MAX_LENGTH];//최대값
	double	m_dMonitoringTol[MAX_LENGTH];	//모디파이
// Dialog Data
	//{{AFX_DATA(CDlgInterface)
	enum { IDD = IDD_DIALOG_INTERFACE };
	long	m_dExposureTime_inNano;
	float	param1;		//ThUp
	float	param2;		//ThDn
	float	param3;		//ThSize
	float	param4;		//검사하지 않는 영역
	float	param5;		//X Max Skip
	float	param6;		//세장비
	float	param7;		//흑색 밝기(크로스용)
	float	param8;		//X Max Skip
	float	param9;		//X Max Skip
	float	param10;		//영상 밝기
	float	param11;		//영상 밝기
	float	param12;		//영상 밝기
	float	param13;		//영상 밝기
	float	param14;		//영상 밝기
	float	param15;		//영상 밝기
	float	param16;		//영상 밝기
	float	param17;		//영상 밝기
	float	param18;		//영상 밝기
	float	param19;		//영상 밝기
	float	param20;		//영상 밝기
	float	param21;		//약휘점 - 약백점.
	float	param22;		//약쿠닉 후보 - 약흑점
	float	param23;		//약쿠닉판단 - 
	float	param24;		//약사이즈
	float	param25;		//

	float	paramPinholeY;
	float	paramislandX;
	float	paramislandY;
	float	paramLineX;
	float	paramLineY;

	DWORD	ip;
	double	frame_len;
	double	scale_x;
	double	scale_y;
	DWORD	shutter;
	double	cal_x;
	double	cal_y;

	double	sparam1;
	double	sparam2;
	double	sparam3;
	double	sparam4;
	double	sparam5;
	double	sparam6;
	double	sparam7;
	double	sparam8;
	double	sparam9;
	double	sparam10;

	
	int		cal_frame;
	int		algorithm_selection;
	int		LgtController;
	float	m_fInsParam6;
	//}}AFX_DATA
	CString MachineName;
	int		UseMarking;

	// 20201022 kjh		meter ratio defect
	BOOL m_bMeterRatioDefect;
	int m_nMeterRatioCount;
	int m_nMeterRatioTotalM;
	int m_nMeterRatioMPerCount;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInterface)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInterface)
	afx_msg void OnButtonLoadIni();
	afx_msg void OnButtonExposureChange();
	afx_msg void OnButtonSaveIni();
	afx_msg void OnButtonGetShutterDefault();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton8();
	double m_dTopBackDistance;
	afx_msg void OnBnClickedButtonParamClose();
	BOOL m_bFullImageSave;
	afx_msg void OnBnClickedCheckFullsave();
	BOOL m_bRevserseX;
	afx_msg void OnBnClickedCheckReversex();
	BOOL m_bSim1;
	afx_msg void OnBnClickedCheckSim1();
	BOOL m_bImageShowHide;
	afx_msg void OnBnClickedCheckImageshow();
	BOOL m_bBlobImgShow;
	afx_msg void OnBnClickedCheckBlobimg();
	BOOL m_bSumEdgeData;
	afx_msg void OnBnClickedCheckSumedgedata();
	double m_dBadAlarmMeter;
	afx_msg void OnBnClickedButtonUpdatedata();
	BOOL m_bAlarm;
	afx_msg void OnBnClickedCheckAlarmuse();
	double m_dAlarmMeter;
	BOOL m_bTestAlarm;
	afx_msg void OnBnClickedCheckTestalarm();
	afx_msg void OnEnSetfocusEditSysStandard1();
	afx_msg void OnEnSetfocusEditSysStandard2();
	afx_msg void OnEnSetfocusEditSysStandard3();
	afx_msg void OnEnSetfocusEditSysStandard4();
	afx_msg void OnEnSetfocusEditSysStandard5();
	afx_msg void OnEnSetfocusEditSysStandard6();
	afx_msg void OnEnSetfocusEditSysStandard7();
	afx_msg void OnEnSetfocusEditSysStandard8();
	afx_msg void OnEnSetfocusEditSysStandard9();
	afx_msg void OnEnSetfocusEditSysStandard10();
	afx_msg void OnEnSetfocusEditSysStandard11();
	afx_msg void OnEnSetfocusEditSysStandard12();
	afx_msg void OnEnSetfocusEditSysStandard13();
	afx_msg void OnEnSetfocusEditSysStandard14();
	afx_msg void OnEnSetfocusEditSysStandard15();
	afx_msg void OnEnSetfocusEditSysStandard16();
	afx_msg void OnEnSetfocusEditSysStandard17();
	afx_msg void OnEnSetfocusEditSysStandard18();
	afx_msg void OnBnClickedButtonNewmodel();
	double m_dMismatchTolMin;
	double m_dMismatchTolMax;
	double m_dMismatchTolMin1;
	double m_dMismatchTolMax1;
	double m_dMismatchModify; 
	bool m_bInsideSet; 
	afx_msg void OnEnSetfocusEditSysMismatchtol1();
	afx_msg void OnEnSetfocusEditSysMismatchtol2();
	double m_dBadAlarmMismatch;
	double m_dMinLineWidth;
	int m_nLineTh1;
	double m_dLineRatio;
	BOOL m_nColorGray;
	afx_msg void OnBnClickedCheckColorGray();
	BOOL m_bLineAve;
	int m_nLineAveFrame;
	afx_msg void OnBnClickedChecklineave();
	int m_dSkipMeter;
	int m_nSkipPixel;
	afx_msg void OnBnClickedButton7();
	CEdit m_strCIS;
	afx_msg void OnBnClickedButton9();
	BOOL m_bDefectNgFrame;
	afx_msg void OnBnClickedCheckDefectalarm();
	BOOL m_bNgFrameInCount;
	afx_msg void OnBnClickedCheckDefectalarm2();
	int m_nBadNgFrame;
	int m_nBadFrameInCount;
	int m_nBadFrameInDefect;
	int m_nContinueBadcnt;
	int m_nContinueBadFrame;
	int	m_nContinueBadMeter;
	BOOL m_bWidthAlarm;
	afx_msg void OnBnClickedCheckWidthalarm();
	BOOL m_bMisAlarm;
	afx_msg void OnBnClickedCheckMismatchalarm();
	afx_msg void OnEnSetfocusEditBadAlarmLength();
	afx_msg void OnEnSetfocusEditBadAlarmMismatch();
	afx_msg void OnEnSetfocusEditBadAlarmDefectframe();
	afx_msg void OnEnSetfocusEditBadAlarmDefectframe3();
	afx_msg void OnEnSetfocusEditBadAlarmDefectframe2();
	afx_msg void OnEnSetfocusEditBadAlarmDefectframe4();
	afx_msg void OnEnSetfocusEditBadAlarmDefectframe5();
	afx_msg void OnEnSetfocusEditLineaveframe();
	afx_msg void OnEnSetfocusEditSkipmeter();
	afx_msg void OnEnSetfocusEditSysScaleX();
	afx_msg void OnEnSetfocusEditSysScaleY();
	afx_msg void OnEnSetfocusEditTopbackDistance();
	afx_msg void OnEnSetfocusEditInsParam1();
	afx_msg void OnEnSetfocusEditInsParam2();
	afx_msg void OnEnSetfocusEditInsParam3();
	afx_msg void OnEnSetfocusEditInsParam4();
	afx_msg void OnEnSetfocusEditInsParam5();
	afx_msg void OnEnSetfocusEditInsParam6();
	afx_msg void OnEnSetfocusEditSkippixel();
	afx_msg void OnEnSetfocusEditInsParam7();
	afx_msg void OnEnSetfocusEditInsParam8();
	afx_msg void OnEnSetfocusEditInsParam9();
	double m_dMinLineWidthMid;
	afx_msg void OnEnSetfocusEditInsParam10();
	BOOL m_bNewScale;
	afx_msg void OnBnClickedCkNewscale();
	int m_nSumFrame;
	afx_msg void OnEnSetfocusEditSysMismatchtol3();
	afx_msg void OnEnSetfocusEditSysMismatchtol4();
	BOOL m_bEdgeInterpolation;
	afx_msg void OnBnClickedCheckEdgeinterpolation();
	BOOL m_bInsulate;
	afx_msg void OnBnClickedCheckInsulate();
	BOOL m_bAging;
	afx_msg void OnBnClickedCheckAging();
	int m_nInsulateTh;
	afx_msg void OnEnSetfocusEditInsParam11();
	CString m_strDefaultBright1;
	CString m_strDefaultBright2;
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	int m_nCoatBright;
	int m_nCoatBrightDefault;
	afx_msg void OnBnClickedButtontest1();
	afx_msg void OnBnClickedButtontest2();
	afx_msg void OnBnClickedCheckEng();
	BOOL m_bEngKor;
	afx_msg void OnBnClickedCheckEngKor();
//	afx_msg void OnEnChangeEditSysStandard1();
	BOOL m_bPreprocessing;
	afx_msg void OnBnClickedCheckPreprocessing();
	BOOL m_bOriginImage;
	afx_msg void OnBnClickedCheckOriginimage();
	BOOL m_bMasterPc;
	afx_msg void OnBnClickedCheckMasterpc();
	BOOL m_bAutoEdge;
	afx_msg void OnBnClickedCheckAutoedge();
	BOOL m_bLineAverageData;
	afx_msg void OnBnClickedCheckLineaveragedata();
	BOOL m_bDrawData;
	afx_msg void OnBnClickedCheckDrawdata();
	BOOL m_bAutoCoatBrightness;
	afx_msg void OnBnClickedCheckAvecoatbright();
	int m_nDefectMag;
	afx_msg void OnBnClickedButton12();
	BOOL m_bNonCoatingPitch;
	afx_msg void OnBnClickedCheckNoncoatpitch();
	BOOL m_bLastData;
	afx_msg void OnBnClickedCheckLastdata();
	BOOL m_bLaneDraw;
	afx_msg void OnBnClickedCheckLanedraw();
	int m_nRewinderDistance;
	afx_msg void OnBnClickedButtonFolderinsp();
	BOOL m_bAutoInsp;
	afx_msg void OnBnClickedCheckAutoinsp1();
	int m_nReturnTime;
	BOOL m_bReturnTime;
	afx_msg void OnBnClickedCheckReturn();
	BOOL m_bReverseTest;
	afx_msg void OnBnClickedCheckReversetest();
	BOOL m_bCylinderCheck;
	afx_msg void OnBnClickedCheckCylinder();
	int m_nCylinderCutValue;
	int m_nDisplayMeter;
	BOOL m_bPlcWrite;
	afx_msg void OnBnClickedCheckPlcwrite();
	afx_msg void OnBnClickedButtonMeterdata();
	int m_nHeadMisDistance;
	double m_dEdgeOffsetmm;
	afx_msg void OnEnSetfocusEditEdgeoffset();
	BOOL m_bBinImage;
	afx_msg void OnBnClickedCheckBinimage();
	BOOL m_bAutoReset;
	afx_msg void OnBnClickedCheckAutoreset();
	BOOL m_bPLCModelSync;
	afx_msg void OnBnClickedCheckPlcmodelsync1();
	BOOL m_bServerDataSend;
	afx_msg void OnBnClickedCheckDatasend();
	BOOL m_bSharpness;
	afx_msg void OnBnClickedCheckSharpness();
	afx_msg void OnEnChangeEditInsParamcoatbright2();
	afx_msg void OnBnClickedButtonEdgeview();
	int m_nAutoBrightness;
	afx_msg void OnBnClickedCheckAutobrightness();
	// 자동 조명 밝기 사용
	BOOL m_bAutoBrightness;
	// 조명노출시간
	int m_nLightOnTime;
	afx_msg void OnBnClickedButtonlightadjust();
	BOOL m_bInspect;
	afx_msg void OnBnClickedCheckInspect1();
	int m_radioTestPlc;
	BOOL m_CheckPLCTest;
	afx_msg void OnBnClickedCheckTestPlc();
	int m_nLightPrimer;
	BOOL m_bAutoSCInspect;
	afx_msg void OnBnClickedCheckAutoinsp2();
	afx_msg void OnBnClickedCheckShowLog();
	BOOL m_bShowLog;
	virtual BOOL OnInitDialog();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINTERFACE_H__25BFBCD8_09E8_4C52_844A_E8C62C8FCF99__INCLUDED_)
