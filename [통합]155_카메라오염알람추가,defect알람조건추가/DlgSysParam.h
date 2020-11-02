#pragma once

#include "afxwin.h"
#include "Label1.h"


// CDlgSysParam 대화 상자입니다.

class CDlgSysParam : public CDialog
{
	DECLARE_DYNAMIC(CDlgSysParam)

public:
	CDlgSysParam(CWnd* pParent = NULL);   // 표준 생성자입니다.
	CWnd*	m_pParent;
	void CDlgSysParam::LabelInit(int nepc);

	void CDlgSysParam::DlgDirSelectComboBox(int nSel);
	void CDlgSysParam::SaveSysParam();
	void CDlgSysParam::LoadSysParam();

	void CDlgSysParam::TransParam(BOOL bTrans=TRUE);
	void ChangeControlsLanguage(BOOL bLang = ENG);

	double	m_dStandard[MAX_LENGTH];//최소값
	double	m_dMaxValue[MAX_LENGTH];//최대값

	double	m_dStandard1[MAX_LENGTH];//control최소값
	double	m_dMaxValue1[MAX_LENGTH];//control최대값

	double m_dMonitoringTol[MAX_LENGTH];//모디파이값	
	//	   m_dMonitoringTol
	int		m_nLimitLane;

	double m_dFoilSize[MAX_LENGTH];

	virtual ~CDlgSysParam();

	void	InitControl();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_SYSPARAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	BOOL m_bAlarm;
	afx_msg void OnBnClickedCheckAlarmuse();
	BOOL m_bWidthAlarm;
	afx_msg void OnBnClickedCheckWidthalarm();
	BOOL m_bMisAlarm;
	afx_msg void OnBnClickedCheckMismatchalarm();
	BOOL m_bDefectNgFrame;
	afx_msg void OnBnClickedCheckDefectalarm();
	BOOL m_bNgFrameInCount;
	afx_msg void OnBnClickedCheckDefectalarm2();
	double m_dBadAlarmMeter;
	afx_msg void OnBnClickedButtonSaveIni();
	double m_dBadAlarmMismatch;
	int m_nBadNgFrame;
	int m_nBadFrameInDefect;
	int m_nBadFrameInCount;
	int m_nContinueBadcnt;
	int m_nContinueBadFrame;
	double scale_x;
	double scale_y;
	double m_dTopBackDistance;
	BOOL m_bTestAlarm;
	afx_msg void OnBnClickedCheckTestalarm();
	BOOL m_bFullImageSave;
	afx_msg void OnBnClickedCheckFullsave();
	afx_msg void OnBnClickedButtonAdjust();
	afx_msg void OnBnSetfocusCheckDefectalarm();
	afx_msg void OnBnSetfocusCheckDefectalarm2();
	afx_msg void OnBnSetfocusCheckAlarmuse();
	afx_msg void OnBnSetfocusCheckWidthalarm();
	afx_msg void OnBnSetfocusCheckMismatchalarm();
	afx_msg void OnBnSetfocusCheckTestalarm();
	afx_msg void OnBnSetfocusCheckFullsave();
	afx_msg void OnEnSetfocusEditBadAlarmLength();
	afx_msg void OnEnSetfocusEditBadAlarmMismatch();
	afx_msg void OnEnSetfocusEditBadAlarmDefectframe();
	afx_msg void OnEnSetfocusEditBadAlarmDefectframe3();
	afx_msg void OnEnSetfocusEditBadAlarmDefectframe2();
	afx_msg void OnEnSetfocusEditBadAlarmDefectframe4();
	afx_msg void OnEnSetfocusEditBadAlarmDefectframe5();
	afx_msg void OnEnSetfocusEditSysScaleX();
	afx_msg void OnEnSetfocusEditSysScaleY();
	afx_msg void OnEnSetfocusEditTopbackDistance();
// 	afx_msg void OnEnSetfocusEditSysStandard1();
// 	afx_msg void OnEnSetfocusEditSysStandard2();
// 	afx_msg void OnEnSetfocusEditSysStandard3();
// 	afx_msg void OnEnSetfocusEditSysStandard4();
// 	afx_msg void OnEnSetfocusEditSysStandard5();
// 	afx_msg void OnEnSetfocusEditSysStandard6();
// 	afx_msg void OnEnSetfocusEditSysStandard7();
// 	afx_msg void OnEnSetfocusEditSysStandard8();
// 	afx_msg void OnEnSetfocusEditSysStandard9();
// 	afx_msg void OnEnSetfocusEditSysStandard10();
// 	afx_msg void OnEnSetfocusEditSysStandard11();
// 	afx_msg void OnEnSetfocusEditSysStandard12();
// 	afx_msg void OnEnSetfocusEditSysStandard13();
// 	afx_msg void OnEnSetfocusEditSysStandard14();
// 	afx_msg void OnEnSetfocusEditSysStandard15();
// 	afx_msg void OnEnSetfocusEditSysStandard16();
// 	afx_msg void OnEnSetfocusEditSysStandard17();
// 	afx_msg void OnEnSetfocusEditSysStandard18();
// 	//double m_dStandard1;
// 	afx_msg void OnEnChangeEditSysStandard6();
	//double m_dStand123;
	afx_msg void OnEnSetfocusEditSysStandard1Copy();
	afx_msg void OnEnSetfocusEditSysStandard2Copy();
	afx_msg void OnEnSetfocusEditSysStandard3Copy();
	afx_msg void OnEnSetfocusEditSysStandard4Copy();
	afx_msg void OnEnSetfocusEditSysStandard5Copy();
	afx_msg void OnEnSetfocusEditSysStandard6Copy();
	afx_msg void OnEnSetfocusEditSysStandard7Copy();
	afx_msg void OnEnSetfocusEditSysStandard8Copy();
	afx_msg void OnEnSetfocusEditSysStandard9Copy();
	afx_msg void OnEnSetfocusEditSysStandard10Copy();
	afx_msg void OnEnSetfocusEditSysStandard11Copy();
	afx_msg void OnEnSetfocusEditSysStandard12Copy();
	afx_msg void OnEnSetfocusEditSysStandard13Copy();
	afx_msg void OnEnSetfocusEditSysStandard14Copy();
	afx_msg void OnEnSetfocusEditSysStandard15Copy();
	afx_msg void OnEnSetfocusEditSysStandard16Copy();
	afx_msg void OnEnSetfocusEditSysStandard17Copy();
	afx_msg void OnEnSetfocusEditSysStandard18Copy();
	afx_msg void OnEnKillfocusEditSysStandard1Copy();
	afx_msg void OnEnKillfocusEditSysStandard2Copy();
	afx_msg void OnEnKillfocusEditSysStandard3Copy();
	afx_msg void OnEnKillfocusEditSysStandard4Copy();
	afx_msg void OnEnKillfocusEditSysStandard5Copy();
	afx_msg void OnEnKillfocusEditSysStandard6Copy();
	afx_msg void OnEnKillfocusEditSysStandard7Copy();
	afx_msg void OnEnKillfocusEditSysStandard8Copy();
	afx_msg void OnEnKillfocusEditSysStandard9Copy();
	afx_msg void OnEnKillfocusEditSysStandard10Copy();
	afx_msg void OnEnKillfocusEditSysStandard11Copy();
	afx_msg void OnEnKillfocusEditSysStandard12Copy();
	afx_msg void OnEnKillfocusEditSysStandard13Copy();
	afx_msg void OnEnKillfocusEditSysStandard14Copy();
	afx_msg void OnEnKillfocusEditSysStandard15Copy();
	afx_msg void OnEnKillfocusEditSysStandard16Copy();
	afx_msg void OnEnKillfocusEditSysStandard17Copy();
	afx_msg void OnEnKillfocusEditSysStandard18Copy();


	afx_msg void OnEnSetfocusEditSysMismatchtol1();
	double m_dMismatchTolMin;
	double m_dMismatchTolMax;
	double m_dMismatchTolMin1;
	double m_dMismatchTolMax1;
	double m_dMismatchModify; 
	afx_msg void OnEnSetfocusEditSysMismatchtol5();
	afx_msg void OnEnSetfocusEditSysMismatchtol2();
	afx_msg void OnEnSetfocusEditSysMismatchtol6();
	afx_msg void OnEnKillfocusEditSysMismatchtol1();
	afx_msg void OnEnKillfocusEditSysMismatchtol5();
	afx_msg void OnEnKillfocusEditSysMismatchtol2();
	afx_msg void OnEnKillfocusEditSysMismatchtol6();
	afx_msg void OnEnChangeEditSysScaleX();
	afx_msg void OnEnSetfocusEditSysStandard1Copy2();
	afx_msg void OnEnSetfocusEditSysStandard2Copy2();
	afx_msg void OnEnSetfocusEditSysStandard3Copy2();
	afx_msg void OnEnSetfocusEditSysStandard4Copy2();
	afx_msg void OnEnSetfocusEditSysStandard5Copy2();
	afx_msg void OnEnSetfocusEditSysStandard6Copy2();
	afx_msg void OnEnSetfocusEditSysStandard7Copy2();
	afx_msg void OnEnSetfocusEditSysStandard8Copy2();
	afx_msg void OnEnSetfocusEditSysStandard9Copy2();
	afx_msg void OnEnSetfocusEditSysStandard10Copy2();
	afx_msg void OnEnSetfocusEditSysStandard11Copy2();
	afx_msg void OnEnSetfocusEditSysStandard12Copy2();
	afx_msg void OnEnSetfocusEditSysStandard13Copy2();
	afx_msg void OnEnSetfocusEditSysStandard14Copy2();
	afx_msg void OnEnSetfocusEditSysStandard15Copy2();
	afx_msg void OnEnSetfocusEditSysStandard16Copy2();
	afx_msg void OnEnSetfocusEditSysStandard17Copy2();
	afx_msg void OnEnSetfocusEditSysStandard18Copy2();
	afx_msg void OnBnClickedButtonSaveIni3();
	CComboBox m_cbLane;
	afx_msg void OnCbnSelchangeComboLane();
	CLabel m_lbEpcPos1;//m_lbEpcPos1
	CLabel m_lbEpcPos2;//m_lbEpcPos1
	CLabel m_lbModelNO;
	bool m_bParamModify;
	afx_msg void OnBnClickedCheckModify();
	afx_msg void OnEnSetfocusEditSysStandard10Copy3();
	afx_msg void OnEnSetfocusEditSysStandard11Copy3();
	afx_msg void OnEnSetfocusEditSysStandard12Copy3();
	afx_msg void OnEnSetfocusEditSysStandard13Copy3();
	afx_msg void OnEnSetfocusEditSysStandard14Copy3();
	afx_msg void OnEnSetfocusEditSysStandard15Copy3();
	afx_msg void OnEnSetfocusEditSysStandard16Copy3();
	afx_msg void OnEnSetfocusEditSysStandard17Copy3();
	afx_msg void OnEnSetfocusEditSysStandard18Copy3();
	afx_msg void OnEnSetfocusEditSysMismatchtol10();
	BOOL m_bParaModify;
	BOOL m_bInsideSet;
	afx_msg void OnBnClickedCheckInsideSet();
	int m_nCLineCount;
	BOOL m_bCLineUse;
	afx_msg void OnBnClickedCheckCoatingline();
	int m_nCLineMeter;
	BOOL m_bFoilSize;
	afx_msg void OnBnClickedCheckFoilsize();
	afx_msg void OnEnSetfocusEditSysFoil1();
	afx_msg void OnEnSetfocusEditSysFoil2();
	BOOL m_bPLCModelSync;
	afx_msg void OnBnClickedCheckDefectArlarmMeterRatio();
	BOOL m_bMeterRatioDefect;
	int m_nMeterRatioCount;
	int m_nMeterRatioTotalM;
	int m_nMeterRatioMPerCount;
};
