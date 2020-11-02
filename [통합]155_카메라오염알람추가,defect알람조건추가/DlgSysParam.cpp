// DlgSysParam.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "VisWeb.h"
#include "VisWebDoc.h"
#include "VisWebView.h"
#include "ini.h"

#include "DlgSysParam.h"




// CDlgSysParam 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgSysParam, CDialog)

CDlgSysParam::CDlgSysParam(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSysParam::IDD, pParent)
	, m_bAlarm(FALSE)
	, m_bWidthAlarm(FALSE)
	, m_bMisAlarm(FALSE)
	, m_bDefectNgFrame(FALSE)
	, m_bNgFrameInCount(FALSE)
	, m_dBadAlarmMeter(0)
	, m_dBadAlarmMismatch(0)
	, m_nBadNgFrame(0)
	, m_nBadFrameInDefect(0)
	, m_nBadFrameInCount(0)
	, m_nContinueBadcnt(0)
	, m_nContinueBadFrame(0)
	, scale_x(0)
	, scale_y(0)
	, m_dTopBackDistance(0)
	, m_bTestAlarm(FALSE)
	, m_bFullImageSave(FALSE)



	
	, m_dMismatchTolMin(0.6)
	, m_dMismatchTolMax(0.6)
	, m_dMismatchTolMin1(1)
	, m_dMismatchTolMax1(1)
	, m_dMismatchModify(0.1)
	, m_bInsideSet(FALSE)

	, m_nCLineCount(0)
	, m_bCLineUse(FALSE)
	, m_nCLineMeter(0)
	, m_bFoilSize(FALSE)
	, m_bPLCModelSync(FALSE)
	, m_bMeterRatioDefect(FALSE)
	, m_nMeterRatioCount(0)
	, m_nMeterRatioTotalM(0)
	, m_nMeterRatioMPerCount(0)
{
	m_pParent = pParent;
	for(int i=0;i<MAX_LENGTH;i++){
		m_dStandard[i] = m_dMaxValue[i] =3;
		m_dStandard1[i] = m_dMaxValue1[i] =3;
		m_dMonitoringTol[i] = 0.1;
		m_dFoilSize[i] = 600;
	}

	m_bMeterRatioDefect = FALSE;
	m_nMeterRatioCount = 0;
	m_nMeterRatioTotalM = 0;
	m_nMeterRatioMPerCount = 0;
}

CDlgSysParam::~CDlgSysParam()
{
}

void CDlgSysParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_ALARMUSE, m_bAlarm);
	DDX_Check(pDX, IDC_CHECK_WIDTHALARM, m_bWidthAlarm);
	DDX_Check(pDX, IDC_CHECK_MISMATCHALARM, m_bMisAlarm);
	DDX_Check(pDX, IDC_CHECK_DEFECTALARM, m_bDefectNgFrame);
	DDX_Check(pDX, IDC_CHECK_DEFECTALARM2, m_bNgFrameInCount);
	DDX_Text(pDX, IDC_EDIT_BAD_ALARM_LENGTH, m_dBadAlarmMeter);
	DDX_Text(pDX, IDC_EDIT_BAD_ALARM_MISMATCH, m_dBadAlarmMismatch);
	DDX_Text(pDX, IDC_EDIT_BAD_ALARM_DEFECTFRAME, m_nBadNgFrame);
	DDX_Text(pDX, IDC_EDIT_BAD_ALARM_DEFECTFRAME3, m_nBadFrameInDefect);
	DDX_Text(pDX, IDC_EDIT_BAD_ALARM_DEFECTFRAME2, m_nBadFrameInCount);
	DDX_Text(pDX, IDC_EDIT_BAD_ALARM_DEFECTFRAME4, m_nContinueBadcnt);
	DDX_Text(pDX, IDC_EDIT_BAD_ALARM_DEFECTFRAME5, m_nContinueBadFrame);
	DDX_Text(pDX, IDC_EDIT_SYS_SCALE_X, scale_x);
	DDX_Text(pDX, IDC_EDIT_SYS_SCALE_Y, scale_y);
	DDX_Text(pDX, IDC_EDIT_TOPBACK_DISTANCE, m_dTopBackDistance);
	DDX_Check(pDX, IDC_CHECK_TESTALARM, m_bTestAlarm);
	DDX_Check(pDX, IDC_CHECK_FULLSAVE, m_bFullImageSave);

	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD1_COPY, m_dStandard[0]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD2_COPY, m_dStandard[1]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD3_COPY, m_dStandard[2]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD4_COPY, m_dStandard[3]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD5_COPY, m_dStandard[4]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD6_COPY, m_dStandard[5]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD7_COPY, m_dStandard[6]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD8_COPY, m_dStandard[7]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD9_COPY, m_dStandard[8]);

	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD10_COPY, m_dMaxValue[0]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD11_COPY, m_dMaxValue[1]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD12_COPY, m_dMaxValue[2]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD13_COPY, m_dMaxValue[3]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD14_COPY, m_dMaxValue[4]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD15_COPY, m_dMaxValue[5]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD16_COPY, m_dMaxValue[6]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD17_COPY, m_dMaxValue[7]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD18_COPY, m_dMaxValue[8]);

	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD1_COPY2, m_dStandard1[0]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD2_COPY2, m_dStandard1[1]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD3_COPY2, m_dStandard1[2]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD4_COPY2, m_dStandard1[3]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD5_COPY2, m_dStandard1[4]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD6_COPY2, m_dStandard1[5]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD7_COPY2, m_dStandard1[6]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD8_COPY2, m_dStandard1[7]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD9_COPY2, m_dStandard1[8]);

	//최대값
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD10_COPY2, m_dMaxValue1[0]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD11_COPY2, m_dMaxValue1[1]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD12_COPY2, m_dMaxValue1[2]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD13_COPY2, m_dMaxValue1[3]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD14_COPY2, m_dMaxValue1[4]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD15_COPY2, m_dMaxValue1[5]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD16_COPY2, m_dMaxValue1[6]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD17_COPY2, m_dMaxValue1[7]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD18_COPY2, m_dMaxValue1[8]);

	//모디파이값 m_dMonitoringTol
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD10_COPY3, m_dMonitoringTol[0]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD11_COPY3, m_dMonitoringTol[1]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD12_COPY3, m_dMonitoringTol[2]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD13_COPY3, m_dMonitoringTol[3]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD14_COPY3, m_dMonitoringTol[4]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD15_COPY3, m_dMonitoringTol[5]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD16_COPY3, m_dMonitoringTol[6]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD17_COPY3, m_dMonitoringTol[7]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD18_COPY3, m_dMonitoringTol[8]);

	DDX_Text(pDX, IDC_EDIT_SYS_MISMATCHTOL1, m_dMismatchTolMin);
	DDX_Text(pDX, IDC_EDIT_SYS_MISMATCHTOL5, m_dMismatchTolMax);
	DDX_Text(pDX, IDC_EDIT_SYS_MISMATCHTOL2, m_dMismatchTolMin1);
	DDX_Text(pDX, IDC_EDIT_SYS_MISMATCHTOL6, m_dMismatchTolMax1);
	DDX_Text(pDX, IDC_EDIT_SYS_MISMATCHTOL10, m_dMismatchModify);
	DDX_Control(pDX, IDC_COMBO_LANE, m_cbLane);
	DDX_Control(pDX, IDC_STATIC_EPCPOS1, m_lbEpcPos1);
	DDX_Control(pDX, IDC_STATIC_EPCPOS2, m_lbEpcPos2);
	DDX_Control(pDX, IDC_STATIC_MODELNO, m_lbModelNO);
	//DDX_Check(pDX, IDC_CHECK_MODIFY, m_bInsideSet);
	DDX_Check(pDX, IDC_CHECK_MODIFY, m_bInsideSet);
	DDX_Check(pDX, IDC_CHECK_INSIDE_SET, m_bInsideSet);
	DDX_Text(pDX, IDC_EDIT_BAD_ALARM_LINECOUNT, m_nCLineCount);
	DDX_Check(pDX, IDC_CHECK_COATINGLINE, m_bCLineUse);
	DDX_Text(pDX, IDC_EDIT_BAD_ALARM_LINEMETER, m_nCLineMeter);
	DDX_Check(pDX, IDC_CHECK_FOILSIZE, m_bFoilSize);

	DDX_Text(pDX, IDC_EDIT_SYS_FOIL1, m_dFoilSize[0]);
	DDX_Text(pDX, IDC_EDIT_SYS_FOIL2, m_dFoilSize[1]);


	DDX_Check(pDX, IDC_CHECK_PLCMODELSYNC, m_bPLCModelSync);
	DDX_Check(pDX, IDC_CHECK_DEFECT_ARLARM_METER_RATIO, m_bMeterRatioDefect);
	DDX_Text(pDX, IDC_EDIT_METER_RATIO_COUNT, m_nMeterRatioCount);
	DDX_Text(pDX, IDC_EDIT_METER_RATIO_TOTAL_METER, m_nMeterRatioTotalM);
	DDX_Text(pDX, IDC_EDIT_METER_RATIO_METER_PER_COUNT, m_nMeterRatioMPerCount);
}


BEGIN_MESSAGE_MAP(CDlgSysParam, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgSysParam::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK_ALARMUSE, &CDlgSysParam::OnBnClickedCheckAlarmuse)
	ON_BN_CLICKED(IDC_CHECK_WIDTHALARM, &CDlgSysParam::OnBnClickedCheckWidthalarm)
	ON_BN_CLICKED(IDC_CHECK_MISMATCHALARM, &CDlgSysParam::OnBnClickedCheckMismatchalarm)
	ON_BN_CLICKED(IDC_CHECK_DEFECTALARM, &CDlgSysParam::OnBnClickedCheckDefectalarm)
	ON_BN_CLICKED(IDC_CHECK_DEFECTALARM2, &CDlgSysParam::OnBnClickedCheckDefectalarm2)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_INI, &CDlgSysParam::OnBnClickedButtonSaveIni)
	ON_BN_CLICKED(IDC_CHECK_TESTALARM, &CDlgSysParam::OnBnClickedCheckTestalarm)
	ON_BN_CLICKED(IDC_CHECK_FULLSAVE, &CDlgSysParam::OnBnClickedCheckFullsave)
	ON_BN_CLICKED(IDC_BUTTON_ADJUST, &CDlgSysParam::OnBnClickedButtonAdjust)
	ON_BN_SETFOCUS(IDC_CHECK_DEFECTALARM, &CDlgSysParam::OnBnSetfocusCheckDefectalarm)
	ON_BN_SETFOCUS(IDC_CHECK_DEFECTALARM2, &CDlgSysParam::OnBnSetfocusCheckDefectalarm2)
	ON_BN_SETFOCUS(IDC_CHECK_ALARMUSE, &CDlgSysParam::OnBnSetfocusCheckAlarmuse)
	ON_BN_SETFOCUS(IDC_CHECK_WIDTHALARM, &CDlgSysParam::OnBnSetfocusCheckWidthalarm)
	ON_BN_SETFOCUS(IDC_CHECK_MISMATCHALARM, &CDlgSysParam::OnBnSetfocusCheckMismatchalarm)
	ON_BN_SETFOCUS(IDC_CHECK_TESTALARM, &CDlgSysParam::OnBnSetfocusCheckTestalarm)
	ON_BN_SETFOCUS(IDC_CHECK_FULLSAVE, &CDlgSysParam::OnBnSetfocusCheckFullsave)
	ON_EN_SETFOCUS(IDC_EDIT_BAD_ALARM_LENGTH, &CDlgSysParam::OnEnSetfocusEditBadAlarmLength)
	ON_EN_SETFOCUS(IDC_EDIT_BAD_ALARM_MISMATCH, &CDlgSysParam::OnEnSetfocusEditBadAlarmMismatch)
	ON_EN_SETFOCUS(IDC_EDIT_BAD_ALARM_DEFECTFRAME, &CDlgSysParam::OnEnSetfocusEditBadAlarmDefectframe)
	ON_EN_SETFOCUS(IDC_EDIT_BAD_ALARM_DEFECTFRAME3, &CDlgSysParam::OnEnSetfocusEditBadAlarmDefectframe3)
	ON_EN_SETFOCUS(IDC_EDIT_BAD_ALARM_DEFECTFRAME2, &CDlgSysParam::OnEnSetfocusEditBadAlarmDefectframe2)
	ON_EN_SETFOCUS(IDC_EDIT_BAD_ALARM_DEFECTFRAME4, &CDlgSysParam::OnEnSetfocusEditBadAlarmDefectframe4)
	ON_EN_SETFOCUS(IDC_EDIT_BAD_ALARM_DEFECTFRAME5, &CDlgSysParam::OnEnSetfocusEditBadAlarmDefectframe5)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_SCALE_X, &CDlgSysParam::OnEnSetfocusEditSysScaleX)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_SCALE_Y, &CDlgSysParam::OnEnSetfocusEditSysScaleY)
	ON_EN_SETFOCUS(IDC_EDIT_TOPBACK_DISTANCE, &CDlgSysParam::OnEnSetfocusEditTopbackDistance)
// 	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD1, &CDlgSysParam::OnEnSetfocusEditSysStandard1)
// 	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD2, &CDlgSysParam::OnEnSetfocusEditSysStandard2)
// 	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD3, &CDlgSysParam::OnEnSetfocusEditSysStandard3)
// 	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD4, &CDlgSysParam::OnEnSetfocusEditSysStandard4)
// 	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD5, &CDlgSysParam::OnEnSetfocusEditSysStandard5)
// 	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD6, &CDlgSysParam::OnEnSetfocusEditSysStandard6)
// 	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD7, &CDlgSysParam::OnEnSetfocusEditSysStandard7)
// 	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD8, &CDlgSysParam::OnEnSetfocusEditSysStandard8)
// 	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD9, &CDlgSysParam::OnEnSetfocusEditSysStandard9)
// 	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD10, &CDlgSysParam::OnEnSetfocusEditSysStandard10)
// 	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD11, &CDlgSysParam::OnEnSetfocusEditSysStandard11)
// 	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD12, &CDlgSysParam::OnEnSetfocusEditSysStandard12)
// 	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD13, &CDlgSysParam::OnEnSetfocusEditSysStandard13)
// 	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD14, &CDlgSysParam::OnEnSetfocusEditSysStandard14)
// 	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD15, &CDlgSysParam::OnEnSetfocusEditSysStandard15)
// 	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD16, &CDlgSysParam::OnEnSetfocusEditSysStandard16)
// 	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD17, &CDlgSysParam::OnEnSetfocusEditSysStandard17)
// 	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD18, &CDlgSysParam::OnEnSetfocusEditSysStandard18)
// 	ON_EN_CHANGE(IDC_EDIT_SYS_STANDARD6, &CDlgSysParam::OnEnChangeEditSysStandard6)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD1_COPY, &CDlgSysParam::OnEnSetfocusEditSysStandard1Copy)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD2_COPY, &CDlgSysParam::OnEnSetfocusEditSysStandard2Copy)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD3_COPY, &CDlgSysParam::OnEnSetfocusEditSysStandard3Copy)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD4_COPY, &CDlgSysParam::OnEnSetfocusEditSysStandard4Copy)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD5_COPY, &CDlgSysParam::OnEnSetfocusEditSysStandard5Copy)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD6_COPY, &CDlgSysParam::OnEnSetfocusEditSysStandard6Copy)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD7_COPY, &CDlgSysParam::OnEnSetfocusEditSysStandard7Copy)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD8_COPY, &CDlgSysParam::OnEnSetfocusEditSysStandard8Copy)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD9_COPY, &CDlgSysParam::OnEnSetfocusEditSysStandard9Copy)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD10_COPY, &CDlgSysParam::OnEnSetfocusEditSysStandard10Copy)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD11_COPY, &CDlgSysParam::OnEnSetfocusEditSysStandard11Copy)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD12_COPY, &CDlgSysParam::OnEnSetfocusEditSysStandard12Copy)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD13_COPY, &CDlgSysParam::OnEnSetfocusEditSysStandard13Copy)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD14_COPY, &CDlgSysParam::OnEnSetfocusEditSysStandard14Copy)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD15_COPY, &CDlgSysParam::OnEnSetfocusEditSysStandard15Copy)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD16_COPY, &CDlgSysParam::OnEnSetfocusEditSysStandard16Copy)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD17_COPY, &CDlgSysParam::OnEnSetfocusEditSysStandard17Copy)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD18_COPY, &CDlgSysParam::OnEnSetfocusEditSysStandard18Copy)

	ON_EN_KILLFOCUS(IDC_EDIT_SYS_STANDARD1_COPY, &CDlgSysParam::OnEnKillfocusEditSysStandard1Copy)
	ON_EN_KILLFOCUS(IDC_EDIT_SYS_STANDARD2_COPY, &CDlgSysParam::OnEnKillfocusEditSysStandard2Copy)
	ON_EN_KILLFOCUS(IDC_EDIT_SYS_STANDARD3_COPY, &CDlgSysParam::OnEnKillfocusEditSysStandard3Copy)
	ON_EN_KILLFOCUS(IDC_EDIT_SYS_STANDARD4_COPY, &CDlgSysParam::OnEnKillfocusEditSysStandard4Copy)
	ON_EN_KILLFOCUS(IDC_EDIT_SYS_STANDARD5_COPY, &CDlgSysParam::OnEnKillfocusEditSysStandard5Copy)
	ON_EN_KILLFOCUS(IDC_EDIT_SYS_STANDARD6_COPY, &CDlgSysParam::OnEnKillfocusEditSysStandard6Copy)
	ON_EN_KILLFOCUS(IDC_EDIT_SYS_STANDARD7_COPY, &CDlgSysParam::OnEnKillfocusEditSysStandard7Copy)
	ON_EN_KILLFOCUS(IDC_EDIT_SYS_STANDARD8_COPY, &CDlgSysParam::OnEnKillfocusEditSysStandard8Copy)
	ON_EN_KILLFOCUS(IDC_EDIT_SYS_STANDARD9_COPY, &CDlgSysParam::OnEnKillfocusEditSysStandard9Copy)
	ON_EN_KILLFOCUS(IDC_EDIT_SYS_STANDARD10_COPY, &CDlgSysParam::OnEnKillfocusEditSysStandard10Copy)
	ON_EN_KILLFOCUS(IDC_EDIT_SYS_STANDARD11_COPY, &CDlgSysParam::OnEnKillfocusEditSysStandard11Copy)
	ON_EN_KILLFOCUS(IDC_EDIT_SYS_STANDARD12_COPY, &CDlgSysParam::OnEnKillfocusEditSysStandard12Copy)
	ON_EN_KILLFOCUS(IDC_EDIT_SYS_STANDARD13_COPY, &CDlgSysParam::OnEnKillfocusEditSysStandard13Copy)
	ON_EN_KILLFOCUS(IDC_EDIT_SYS_STANDARD14_COPY, &CDlgSysParam::OnEnKillfocusEditSysStandard14Copy)
	ON_EN_KILLFOCUS(IDC_EDIT_SYS_STANDARD15_COPY, &CDlgSysParam::OnEnKillfocusEditSysStandard15Copy)
	ON_EN_KILLFOCUS(IDC_EDIT_SYS_STANDARD16_COPY, &CDlgSysParam::OnEnKillfocusEditSysStandard16Copy)
	ON_EN_KILLFOCUS(IDC_EDIT_SYS_STANDARD17_COPY, &CDlgSysParam::OnEnKillfocusEditSysStandard17Copy)
	ON_EN_KILLFOCUS(IDC_EDIT_SYS_STANDARD18_COPY, &CDlgSysParam::OnEnKillfocusEditSysStandard18Copy)



	ON_EN_SETFOCUS(IDC_EDIT_SYS_MISMATCHTOL1, &CDlgSysParam::OnEnSetfocusEditSysMismatchtol1)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_MISMATCHTOL5, &CDlgSysParam::OnEnSetfocusEditSysMismatchtol5)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_MISMATCHTOL2, &CDlgSysParam::OnEnSetfocusEditSysMismatchtol2)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_MISMATCHTOL6, &CDlgSysParam::OnEnSetfocusEditSysMismatchtol6)
	ON_EN_KILLFOCUS(IDC_EDIT_SYS_MISMATCHTOL1, &CDlgSysParam::OnEnKillfocusEditSysMismatchtol1)
	ON_EN_KILLFOCUS(IDC_EDIT_SYS_MISMATCHTOL5, &CDlgSysParam::OnEnKillfocusEditSysMismatchtol5)
	ON_EN_KILLFOCUS(IDC_EDIT_SYS_MISMATCHTOL2, &CDlgSysParam::OnEnKillfocusEditSysMismatchtol2)
	ON_EN_KILLFOCUS(IDC_EDIT_SYS_MISMATCHTOL6, &CDlgSysParam::OnEnKillfocusEditSysMismatchtol6)
	ON_EN_CHANGE(IDC_EDIT_SYS_SCALE_X, &CDlgSysParam::OnEnChangeEditSysScaleX)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD1_COPY2, &CDlgSysParam::OnEnSetfocusEditSysStandard1Copy2)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD2_COPY2, &CDlgSysParam::OnEnSetfocusEditSysStandard2Copy2)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD3_COPY2, &CDlgSysParam::OnEnSetfocusEditSysStandard3Copy2)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD4_COPY2, &CDlgSysParam::OnEnSetfocusEditSysStandard4Copy2)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD5_COPY2, &CDlgSysParam::OnEnSetfocusEditSysStandard5Copy2)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD6_COPY2, &CDlgSysParam::OnEnSetfocusEditSysStandard6Copy2)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD7_COPY2, &CDlgSysParam::OnEnSetfocusEditSysStandard7Copy2)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD8_COPY2, &CDlgSysParam::OnEnSetfocusEditSysStandard8Copy2)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD9_COPY2, &CDlgSysParam::OnEnSetfocusEditSysStandard9Copy2)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD10_COPY2, &CDlgSysParam::OnEnSetfocusEditSysStandard10Copy2)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD11_COPY2, &CDlgSysParam::OnEnSetfocusEditSysStandard11Copy2)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD12_COPY2, &CDlgSysParam::OnEnSetfocusEditSysStandard12Copy2)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD13_COPY2, &CDlgSysParam::OnEnSetfocusEditSysStandard13Copy2)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD14_COPY2, &CDlgSysParam::OnEnSetfocusEditSysStandard14Copy2)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD15_COPY2, &CDlgSysParam::OnEnSetfocusEditSysStandard15Copy2)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD16_COPY2, &CDlgSysParam::OnEnSetfocusEditSysStandard16Copy2)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD17_COPY2, &CDlgSysParam::OnEnSetfocusEditSysStandard17Copy2)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD18_COPY2, &CDlgSysParam::OnEnSetfocusEditSysStandard18Copy2)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_INI3, &CDlgSysParam::OnBnClickedButtonSaveIni3)
	ON_CBN_SELCHANGE(IDC_COMBO_LANE, &CDlgSysParam::OnCbnSelchangeComboLane)
	//ON_BN_CLICKED(IDC_CHECK_MODIFY, &CDlgSysParam::OnBnClickedCheckModify)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD10_COPY3, &CDlgSysParam::OnEnSetfocusEditSysStandard10Copy3)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD11_COPY3, &CDlgSysParam::OnEnSetfocusEditSysStandard11Copy3)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD12_COPY3, &CDlgSysParam::OnEnSetfocusEditSysStandard12Copy3)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD13_COPY3, &CDlgSysParam::OnEnSetfocusEditSysStandard13Copy3)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD14_COPY3, &CDlgSysParam::OnEnSetfocusEditSysStandard14Copy3)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD15_COPY3, &CDlgSysParam::OnEnSetfocusEditSysStandard15Copy3)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD16_COPY3, &CDlgSysParam::OnEnSetfocusEditSysStandard16Copy3)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD17_COPY3, &CDlgSysParam::OnEnSetfocusEditSysStandard17Copy3)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD18_COPY3, &CDlgSysParam::OnEnSetfocusEditSysStandard18Copy3)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_MISMATCHTOL10, &CDlgSysParam::OnEnSetfocusEditSysMismatchtol10)
	ON_BN_CLICKED(IDC_CHECK_INSIDE_SET, &CDlgSysParam::OnBnClickedCheckInsideSet)
	ON_BN_CLICKED(IDC_CHECK_COATINGLINE, &CDlgSysParam::OnBnClickedCheckCoatingline)
	ON_BN_CLICKED(IDC_CHECK_FOILSIZE, &CDlgSysParam::OnBnClickedCheckFoilsize)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_FOIL1, &CDlgSysParam::OnEnSetfocusEditSysFoil1)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_FOIL2, &CDlgSysParam::OnEnSetfocusEditSysFoil2)
	ON_BN_CLICKED(IDC_CHECK_DEFECT_ARLARM_METER_RATIO, &CDlgSysParam::OnBnClickedCheckDefectArlarmMeterRatio)
	END_MESSAGE_MAP()


// CDlgSysParam 메시지 처리기입니다.

BOOL CDlgSysParam::OnInitDialog()
{
	CDialog::OnInitDialog();

	//label 초기화
	InitControl();
	//m_lbEpcPos1

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDlgSysParam::LabelInit(int nepc)
{
	m_lbEpcPos1.SetTextColor(COLOR_GREEN);
	m_lbEpcPos1.SetBkColor(COLOR_BLACK);
	m_lbEpcPos1.SetFontBold(TRUE);
	m_lbEpcPos1.SetFontName("굴림");
	m_lbEpcPos1.SetFontSize(20);

	m_lbEpcPos2.SetTextColor(COLOR_GREEN);
	m_lbEpcPos2.SetBkColor(COLOR_BLACK);
	m_lbEpcPos2.SetFontBold(TRUE);
	m_lbEpcPos2.SetFontName("굴림");
	m_lbEpcPos2.SetFontSize(20);

	if(nepc==1){
		m_lbEpcPos1.SetText("EPC");
		m_lbEpcPos2.SetText("NON-EPC");
	}
	else{
		m_lbEpcPos2.SetText("EPC");
		m_lbEpcPos1.SetText("NON-EPC");
	}
	m_lbModelNO.SetTextColor(COLOR_RED);
	m_lbModelNO.SetBkColor(COLOR_GREEN);
	m_lbModelNO.SetFontBold(TRUE);
	m_lbModelNO.SetFontName("굴림");
	m_lbModelNO.SetFontSize(30);
	m_lbModelNO.SetText("Model");

}

void CDlgSysParam::OnBnClickedButton1()
{
	ShowWindow(0);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgSysParam::OnBnClickedCheckAlarmuse()
{//m_bAlarm
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	UpdateData();
	if(m_bAlarm==FALSE){
		m_bNgFrameInCount = FALSE;
		m_bWidthAlarm=m_bMisAlarm=FALSE;
		m_bDefectNgFrame = FALSE;
		m_bNgFrameInCount = FALSE;
		UpdateData(FALSE);
		pView->m_bAlarmOff = TRUE;
		pView->UpdateData(FALSE);

	}
	else{
		// 		m_bNgFrameInCount = FALSE;
		// 		m_bWidthAlarm=m_bMisAlarm=FALSE;
		// 		m_bDefectNgFrame = FALSE;
		// 		m_bNgFrameInCount = FALSE;
		// 		UpdateData(FALSE);
		pView->m_bAlarmOff = FALSE;
		pView->UpdateData(FALSE);

	}
	TransParam();
}

void CDlgSysParam::OnBnClickedCheckWidthalarm()
{//m_bWidthAlarm
	UpdateData();
	if(m_bAlarm==FALSE){
		m_bWidthAlarm = FALSE;
		UpdateData(FALSE);
	}
	if(!m_bWidthAlarm){
		CVisWebView *pView = (CVisWebView*)m_pParent;
		pView->m_nAlarmEndFRame = 0;
	}
	TransParam();
}

void CDlgSysParam::OnBnClickedCheckMismatchalarm()
{//m_bMisAlarm
	UpdateData();
	if(m_bAlarm==FALSE){
		m_bMisAlarm = FALSE;
		UpdateData(FALSE);
	}
	if(!m_bMisAlarm){
		CVisWebView *pView = (CVisWebView*)m_pParent;
		pView->m_nAlarmEndFRame = 0;
	}
	TransParam();
}

void CDlgSysParam::OnBnClickedCheckDefectalarm()
{//m_bDefectNgFrame
	UpdateData();
	if(m_bAlarm==FALSE){
		m_bDefectNgFrame = FALSE;
		UpdateData(FALSE);
	}
	TransParam();
}

void CDlgSysParam::OnBnClickedCheckDefectalarm2()
{//m_bNgFrameInCount
	UpdateData();
	if(m_bAlarm==FALSE){
		m_bNgFrameInCount = FALSE;
		UpdateData(FALSE);
	}
	TransParam();
}

void CDlgSysParam::OnBnClickedButtonSaveIni()
{
	//m_dBadAlarmMeter
	//m_dBadAlarmMismatch
	//m_nBadNgFrame	//m_nBadFrameInDefect	//m_nBadFrameInCount
	//m_nContinueBadcnt	//m_nContinueBadFrame
	//scale_x	scale_y	m_dTopBackDistance

	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	double ddd = pView->m_SysParam->m_dBadAlarmMeter;
	UpdateData();
	TransParam();
	//param backup //m_nContinueBadcnt//m_nContinueBadFrame
	CTime ttime = CTime::GetCurrentTime();
	CString kk = ttime.Format("%Y%m%d");
	CString strTime = ttime.Format("%Y%m%d_%H%M%S");
	CString strfilename1,strfilename2,strfilename3,strfilename4;
	strfilename1.Format("c:\\Glim\\parameter.ini");
	strfilename3.Format("c:\\Glim\\Model\\%s.ini",pDoc->m_data.m_strDefaultModel);//model
	strfilename2.Format("d:\\Backup\\");
	CreateDirectory(strfilename2,NULL);	
	strfilename2.Format("d:\\Backup\\Parameter\\");
	CreateDirectory(strfilename2,NULL);	
	strfilename2.Format("d:\\Backup\\Parameter\\%s\\",kk);
	CreateDirectory(strfilename2,NULL);	
	strfilename2.Format("d:\\Backup\\Parameter\\%s\\%s_Parameter.ini",kk,strTime);
	strfilename4.Format("d:\\Backup\\Parameter\\%s\\%s_%s.ini",kk,strTime,pDoc->m_data.m_strDefaultModel);


	//m_nBadNgFrame 몇레임수중 m_nBadFrameInCount 불량 프레임수
	//m_nBadFrameInDefect 프레임당 불량 개수

	CopyFile(strfilename1,strfilename2,FALSE);
	CopyFile(strfilename3,strfilename4,FALSE);

	UpdateData(true);
	pView->UpdateTolIni(pDoc->m_data.m_strDefaultModel,0);

	SaveSysParam();
	LoadSysParam();
	pDoc->m_pDlgInterface->SaveSysParam();
	pDoc->m_pDlgInterface->LoadSysParam();

	pView->UpdateTolIni(pDoc->m_data.m_strDefaultModel,1);
	if(pDoc->m_pDlgInterface->m_bPlcWrite)
		pView->WriteShareMemorySpec();

	if(pView->m_bSendServerINI){
//		if(pView->m_strServerModel.Compare(_T(""))!=0 && pDoc->m_data.m_strDefaultModel.Compare(_T(""))!=0 && pDoc->m_data.m_strDefaultModel.Compare(pView->m_strServerModel)==0){
			pView->WriteINIFileForServer();	// kjh 200710
			pView->CreateINICheckFile();
			pView->AddtoList("Write Server INI File!", FALSE);
//		}
// 		else{
// 			if(pView->m_strComputerName.Find(_T("OCH"))>=0){
// 				AfxMessageBox(_T("통합서버와 모델이 다릅니다. 모델명을 확인하세요!"));
// 			}
// 			else if(pView->m_strComputerName.Find(_T("CMI"))>=0){
// 				AfxMessageBox(_T("Model name is differ from Sever Model name!"));
// 			}
// 
// 		}
	}
	else
		pView->m_bSendServerINI = true;


}

void CDlgSysParam::OnBnClickedCheckTestalarm()
{//m_bTestAlarm
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();
	if(m_bTestAlarm){
		pView->m_IO[0].WriteOutputPort(0,0,1);
	}
	else{
		pView->m_IO[0].WriteOutputPort(0,0,0);
	}
	TransParam();
}

void CDlgSysParam::OnBnClickedCheckFullsave()
{//m_bFullImageSave
	UpdateData();
	TransParam();
}

void CDlgSysParam::SaveSysParam()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	CString str, str_name;
	str_name = pView->m_strComputerName;
	str.Format("%s - System Parameter", str_name);

	//m_dBadAlarmMeter
	//m_dBadAlarmMismatch
	//m_nBadNgFrame	//m_nBadFrameInDefect	//m_nBadFrameInCount
	//m_nContinueBadcnt	//m_nContinueBadFrame
	//scale_x	scale_y	m_dTopBackDistance
	//m_bAlarm	m_bWidthAlarm	m_bMisAlarm	m_bDefectNgFrame	m_bNgFrameInCount
	CIni ini( PARAMETER_PATH, str, 1 );
	ini.SER_GETD(FALSE, scale_x					, 10);////
	ini.SER_GETD(FALSE, scale_y					, 10);////
	ini.SER_GETD(FALSE, m_dTopBackDistance		, 80);////
	ini.SER_GETD(FALSE, m_dBadAlarmMismatch	, 10);////.
	ini.SER_GETD(FALSE, m_dBadAlarmMeter	, 10);////.
	ini.SER_GETD(FALSE, m_bAlarm	, 0);////
//	ini.SER_GETD(FALSE, m_nColorGray	, 0);//
// 	ini.SER_GETD(FALSE, m_bLineAve	, 1);//
// 	if(m_nLineAveFrame>10)m_nLineAveFrame = 10;
// 	ini.SER_GETD(FALSE, m_nLineAveFrame	, 10);//
// 	ini.SER_GETD(FALSE, m_dSkipMeter	, 3);//int로 수정
// 	ini.SER_GETD(FALSE, m_nSkipPixel	, 2000);//
	ini.SER_GETD(FALSE, m_nBadNgFrame	, 10);////. 10M 구간중
	ini.SER_GETD(FALSE, m_nBadFrameInDefect	, 10);////10개 불량이 
	ini.SER_GETD(FALSE, m_nBadFrameInCount	, 5);////5장 
	ini.SER_GETD(FALSE, m_bDefectNgFrame	, 1);////
	ini.SER_GETD(FALSE, m_nContinueBadcnt	, 10);////10개 불량이 
	ini.SER_GETD(FALSE, m_nContinueBadFrame	, 5);////연속으로 5장
	ini.SER_GETD(FALSE, m_bWidthAlarm	, 1);////
	ini.SER_GETD(FALSE, m_bMisAlarm	, 1);////
	ini.SER_GETD(FALSE, m_bFullImageSave	, 1);////
	ini.SER_GETD(FALSE, m_bNgFrameInCount	, 1);////

	ini.SER_GETD(FALSE, m_bMeterRatioDefect	, FALSE);////
	ini.SER_GETD(FALSE, m_nMeterRatioCount	, 10);////
	ini.SER_GETD(FALSE, m_nMeterRatioTotalM	, 100);////
	ini.SER_GETD(FALSE, m_nMeterRatioMPerCount	, 2);////
	

	////
	for(int i=0;i<MAX_CAMERAS;i++){
		pDoc->m_data.m_dScaleFactorX[i] = scale_x;
		pDoc->m_data.m_dScaleFactorY[i] = scale_y;
	}
}

void CDlgSysParam::LoadSysParam()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	CString str, str_name;
	int N=pDoc->m_data.m_nVisionLine;
	for(int n=0;n<MAX_CAMERAS;n++)
	{
		str_name = pView->m_strComputerName;
		str.Format("%s - System Parameter", str_name);

		CIni ini( PARAMETER_PATH, str, 1 );
		ini.SER_GETD(TRUE, scale_x					, 0.04233);
		ini.SER_GETD(TRUE, scale_y					, 0.04233);
		ini.SER_GETD(TRUE, m_dTopBackDistance		, 70);
	///////new param
		ini.SER_GETD(TRUE, m_dBadAlarmMeter	, 10);//
		ini.SER_GETD(TRUE, m_dBadAlarmMismatch	, 10);//
		ini.SER_GETD(TRUE, m_bAlarm	, 0);//
		ini.SER_GETD(TRUE, m_bFullImageSave	, 1);//

		ini.SER_GETD(TRUE, m_bNgFrameInCount	, 1);//
		ini.SER_GETD(TRUE, m_nBadNgFrame	, 10);// 10M 구간중
		ini.SER_GETD(TRUE, m_nBadFrameInDefect	, 10);//10개 불량이 
		ini.SER_GETD(TRUE, m_nBadFrameInCount	, 5);//5장 

		ini.SER_GETD(TRUE, m_bDefectNgFrame	, 1);//
		ini.SER_GETD(TRUE, m_nContinueBadcnt	, 10);//10개 불량이 
		ini.SER_GETD(TRUE, m_nContinueBadFrame	, 5);//연속으로 5장

		ini.SER_GETD(TRUE, m_bWidthAlarm	, 1);//
		ini.SER_GETD(TRUE, m_bMisAlarm	, 1);//

		ini.SER_GETD(TRUE, m_bMeterRatioDefect	, FALSE);//
		ini.SER_GETD(TRUE, m_nMeterRatioCount	, 10);//
		ini.SER_GETD(TRUE, m_nMeterRatioTotalM	, 100);//
		ini.SER_GETD(TRUE, m_nMeterRatioMPerCount	, 2);//
		



		pDoc->m_data.m_dScaleFactorX[n] = scale_x;
		pDoc->m_data.m_dScaleFactorY[n] = scale_y;

//		m_dAlarmMeter;
//		pDoc->m_data.m_bSumEdgeData = m_bSumEdgeData;
		pDoc->m_data.m_dBadAlarmMeter = (m_dBadAlarmMeter*1000) / (CAM_HEIGHT_3072*scale_y);
		pDoc->m_data.m_dBadAlarmMismatch = (m_dBadAlarmMismatch*1000) / (CAM_HEIGHT_3072*scale_y);
		pDoc->m_pDlgInterface->m_nContinueBadMeter = (m_nContinueBadFrame*1000)/(scale_y*CAM_HEIGHT_3072);
		////////
	}
}

void CDlgSysParam::TransParam(BOOL bTrans)
{//m_bFullImageSave
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	if(bTrans){//현재 DLG -> InterfaceDlg
		
		pDoc->m_pDlgInterface->m_bInsideSet			= m_bInsideSet; 
		pDoc->m_pDlgInterface->m_bAlarm				= m_bAlarm;//main alarm;
		pDoc->m_pDlgInterface->m_bNgFrameInCount	= m_bNgFrameInCount;//구간 
		pDoc->m_pDlgInterface->m_bMisAlarm			= m_bMisAlarm;//미스매치 알람
		pDoc->m_pDlgInterface->m_bWidthAlarm		= m_bWidthAlarm;//폭 연속 불량 알람
		pDoc->m_pDlgInterface->m_bDefectNgFrame		= m_bDefectNgFrame;//구간 이물불량
		pDoc->m_pDlgInterface->m_bFullImageSave		= m_bFullImageSave;//Ful save
		pDoc->m_pDlgInterface->m_bTestAlarm			= m_bTestAlarm;
		pDoc->m_pDlgInterface->m_dTopBackDistance	= m_dTopBackDistance;//탑백거리
		pDoc->m_pDlgInterface->m_dBadAlarmMismatch	= m_dBadAlarmMismatch;
		pDoc->m_pDlgInterface->m_dBadAlarmMeter		= m_dBadAlarmMeter;
		pDoc->m_pDlgInterface->m_nBadNgFrame		= m_nBadNgFrame;
		pDoc->m_pDlgInterface->m_nBadFrameInDefect	= m_nBadFrameInDefect;
		pDoc->m_pDlgInterface->m_nBadFrameInCount	= m_nBadFrameInCount;
		pDoc->m_pDlgInterface->m_nContinueBadcnt	= m_nContinueBadcnt;
		pDoc->m_pDlgInterface->m_nContinueBadFrame	= m_nContinueBadFrame;
		
		pDoc->m_pDlgInterface->scale_x				= scale_x;//스케일
		pDoc->m_pDlgInterface->scale_y				= scale_y;//스케일

		pDoc->m_pDlgInterface->m_bMeterRatioDefect = m_bMeterRatioDefect;
		pDoc->m_pDlgInterface->m_nMeterRatioCount = m_nMeterRatioCount;
		pDoc->m_pDlgInterface->m_nMeterRatioTotalM = m_nMeterRatioTotalM;
		pDoc->m_pDlgInterface->m_nMeterRatioMPerCount = m_nMeterRatioMPerCount;

	}
	else{
		m_bAlarm=pDoc->m_pDlgInterface->m_bAlarm				;//main alarm;
		m_bNgFrameInCount=pDoc->m_pDlgInterface->m_bNgFrameInCount	;//구간 
		m_bMisAlarm=pDoc->m_pDlgInterface->m_bMisAlarm			;//미스매치 알람
		m_bWidthAlarm=pDoc->m_pDlgInterface->m_bWidthAlarm		;//폭 연속 불량 알람
		m_bDefectNgFrame=pDoc->m_pDlgInterface->m_bDefectNgFrame		;//구간 이물불량
		m_bFullImageSave=pDoc->m_pDlgInterface->m_bFullImageSave		;//Ful save
		m_bTestAlarm=pDoc->m_pDlgInterface->m_bTestAlarm			;
		m_dTopBackDistance=pDoc->m_pDlgInterface->m_dTopBackDistance	;//탑백거리
		m_dBadAlarmMismatch=pDoc->m_pDlgInterface->m_dBadAlarmMismatch	;
		m_dBadAlarmMeter=pDoc->m_pDlgInterface->m_dBadAlarmMeter		;
		m_nBadNgFrame=pDoc->m_pDlgInterface->m_nBadNgFrame		;
		m_nBadFrameInDefect=pDoc->m_pDlgInterface->m_nBadFrameInDefect	;
		m_nBadFrameInCount=pDoc->m_pDlgInterface->m_nBadFrameInCount	;
		m_nContinueBadcnt=pDoc->m_pDlgInterface->m_nContinueBadcnt	;
		m_nContinueBadFrame=pDoc->m_pDlgInterface->m_nContinueBadFrame	;

		scale_x=pDoc->m_pDlgInterface->scale_x				;//스케일
		scale_y=pDoc->m_pDlgInterface->scale_y				;//스케일

		m_bMeterRatioDefect = pDoc->m_pDlgInterface->m_bMeterRatioDefect;
		m_nMeterRatioCount = pDoc->m_pDlgInterface->m_nMeterRatioCount;
		m_nMeterRatioTotalM = pDoc->m_pDlgInterface->m_nMeterRatioTotalM;
		m_nMeterRatioMPerCount = pDoc->m_pDlgInterface->m_nMeterRatioMPerCount;

		UpdateData(FALSE);
	}
}

void CDlgSysParam::OnBnClickedButtonAdjust()
{
	UpdateData();
	int n = m_cbLane.GetCurSel();//m_comboWeldingNum.SetCurSel(m_nWeldingNum);
	TransParam();
}

void CDlgSysParam::OnBnSetfocusCheckDefectalarm()
{
	//구간이물불량
}

void CDlgSysParam::OnBnSetfocusCheckDefectalarm2()
{
	// 이물 연속 불량
}

void CDlgSysParam::OnBnSetfocusCheckAlarmuse()
{
	// 알람
}

void CDlgSysParam::OnBnSetfocusCheckWidthalarm()
{
	// 폭연속 부량 거리
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();//m_dBadAlarmMeter
	pView->m_NumPad->m_nSelectControl = 1;
	pView->m_NumPad->LabelShow2(0,m_dBadAlarmMeter,m_dBadAlarmMeter);
	pView->m_NumPad->ShowWindow(1);

}

void CDlgSysParam::OnBnSetfocusCheckMismatchalarm()
{
	// 미스매치 연속 불량 거리
}

void CDlgSysParam::OnBnSetfocusCheckTestalarm()
{
	// 알람테스트
}

void CDlgSysParam::OnBnSetfocusCheckFullsave()
{
	// 풀세이브
}

void CDlgSysParam::OnEnSetfocusEditBadAlarmLength()
{
	// 폭연속불량거리값
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();//m_dBadAlarmMeter
	pView->m_NumPad->m_nSelectControl = 1;
	pView->m_NumPad->LabelShow2(0,m_dBadAlarmMeter,m_dBadAlarmMeter);
	pView->m_NumPad->ShowWindow(1);

}

void CDlgSysParam::OnEnSetfocusEditBadAlarmMismatch()
{
	// 미스매치연속불량거리값
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();//m_dBadAlarmMismatch
	pView->m_NumPad->m_nSelectControl = 2;
	pView->m_NumPad->LabelShow2(0,m_dBadAlarmMismatch,m_dBadAlarmMismatch);
	pView->m_NumPad->ShowWindow(1);

}

void CDlgSysParam::OnEnSetfocusEditBadAlarmDefectframe()
{
	// 구간이물불량 미터1
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();//m_nBadNgFrame
	pView->m_NumPad->m_nSelectControl = 3;
	pView->m_NumPad->LabelShow2(0,m_nBadNgFrame,m_nBadNgFrame);
	pView->m_NumPad->ShowWindow(1);

}

void CDlgSysParam::OnEnSetfocusEditBadAlarmDefectframe3()
{
	// 구간이물 불량 개수
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();//m_nBadFrameInDefect
	pView->m_NumPad->m_nSelectControl = 4;
	pView->m_NumPad->LabelShow2(0,m_nBadFrameInDefect,m_nBadFrameInDefect);
	pView->m_NumPad->ShowWindow(1);

}

void CDlgSysParam::OnEnSetfocusEditBadAlarmDefectframe2()
{
	// 구간이물 불량 미터2
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();//m_nBadFrameInCount
	pView->m_NumPad->m_nSelectControl = 5;
	pView->m_NumPad->LabelShow2(0,m_nBadFrameInCount,m_nBadFrameInCount);
	pView->m_NumPad->ShowWindow(1);

}

void CDlgSysParam::OnEnSetfocusEditBadAlarmDefectframe4()
{
	// 이물연속불량 개수
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();//m_nContinueBadcnt
	pView->m_NumPad->m_nSelectControl = 6;
	pView->m_NumPad->LabelShow2(0,m_nContinueBadcnt,m_nContinueBadcnt);
	pView->m_NumPad->ShowWindow(1);

}

void CDlgSysParam::OnEnSetfocusEditBadAlarmDefectframe5()
{
	// 이물연속불량 미터
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();//m_nContinueBadFrame
	pView->m_NumPad->m_nSelectControl = 7;
	pView->m_NumPad->LabelShow2(0,m_nContinueBadFrame,m_nContinueBadFrame);
	pView->m_NumPad->ShowWindow(1);

}

void CDlgSysParam::OnEnSetfocusEditSysScaleX()
{
	// 스케일 엑스 값
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();//scale_x
	pView->m_NumPad->m_nSelectControl = 10;
	pView->m_NumPad->LabelShow2(0,scale_x,scale_x);
	pView->m_NumPad->ShowWindow(1);

}

void CDlgSysParam::OnEnSetfocusEditSysScaleY()
{
	// 스케일 와이값
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();//scale_y
	pView->m_NumPad->m_nSelectControl = 11;
	pView->m_NumPad->LabelShow2(0,scale_y,scale_y);
	pView->m_NumPad->ShowWindow(1);

}

void CDlgSysParam::OnEnSetfocusEditTopbackDistance()
{
	// 탑백 거리
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();//m_dTopBackDistance
	pView->m_NumPad->m_nSelectControl = 12;
	pView->m_NumPad->LabelShow2(0,m_dTopBackDistance,m_dTopBackDistance);
	pView->m_NumPad->ShowWindow(1);

}

void CDlgSysParam::ChangeControlsLanguage( BOOL bLang /*= ENG*/ )
{
	if(bLang == ENG){			// 영어 
		SetDlgItemText(IDC_CHECK_ALARMUSE, _T("ALARM"));

		SetDlgItemText(IDC_SYS_STATIC_ALARM1, _T("WIDTH NG"));
		SetDlgItemText(IDC_CHECK_WIDTHALARM, _T("WIDTH SIZE NG"));
		SetDlgItemText(IDC_CHECK_MISMATCHALARM, _T("MISMATCH NG"));

		SetDlgItemText(IDC_SYS_STATIC_ALARM2, _T("Defect NG"));
		SetDlgItemText(IDC_CHECK_DEFECTALARM, _T("Non-Continuous Defect"));
		SetDlgItemText(IDC_CHECK_DEFECTALARM2, _T("Continuous Defect"));
		SetDlgItemText(IDC_SYS_STATIC_ALARM2_1, _T("M /"));
		SetDlgItemText(IDC_SYS_STATIC_ALARM2_2, _T("COUNT"));
		SetDlgItemText(IDC_SYS_STATIC_ALARM2_3, _T("COUNT"));

		SetDlgItemText(IDC_SYS_STATIC_SYSPARAM1_1, _T("TOP-BACK DIS."));
		SetDlgItemText(IDC_CHECK_TESTALARM, _T("TEST ALARM"));
		

		SetDlgItemText(IDC_SYS_STATIC_SYSPARAM2, _T("Coat , N-Coat Spec."));
		SetDlgItemText(IDC_SYS_STATIC_SYSPARAM2_MIN, _T(" MIN"));
		SetDlgItemText(IDC_SYS_STATIC_SYSPARAM2_MAX, _T(" MAX"));
		SetDlgItemText(IDC_SYS_STATIC_SYSPARAM2_1, _T("N-Coat1"));
		SetDlgItemText(IDC_SYS_STATIC_SYSPARAM2_2, _T("COAT1"));
		SetDlgItemText(IDC_SYS_STATIC_SYSPARAM2_3, _T("N-Coat2"));
		SetDlgItemText(IDC_SYS_STATIC_SYSPARAM2_4, _T("COAT2"));
		SetDlgItemText(IDC_SYS_STATIC_SYSPARAM2_5, _T("N-Coat3"));
		SetDlgItemText(IDC_SYS_STATIC_SYSPARAM2_6, _T("COAT3"));
		SetDlgItemText(IDC_SYS_STATIC_SYSPARAM2_7, _T("N-Coat4"));
		SetDlgItemText(IDC_SYS_STATIC_SYSPARAM2_8, _T("COAT4"));
		SetDlgItemText(IDC_SYS_STATIC_SYSPARAM2_9, _T("N-Coat5"));
		SetDlgItemText(IDC_SYS_STATIC_SYSPARAM2_M1, _T("MISMATCH"));
		SetDlgItemText(IDC_SYS_STATIC_SYSPARAM2_M2, _T("MISMATCH2"));

		SetDlgItemText(IDC_BUTTON_ADJUST, _T("ADJUST"));
		SetDlgItemText(IDC_BUTTON_SAVE_INI, _T("SAVE"));
		SetDlgItemText(IDC_BUTTON_CLOSE, _T("CLOSE"));

		SetDlgItemText(IDC_BUTTON_SAVE_INI3, _T("Model Control"));




	}
	else if(bLang == KOR){		// 한글
		SetDlgItemText(IDC_CHECK_ALARMUSE, _T("알람"));

		SetDlgItemText(IDC_SYS_STATIC_ALARM1, _T("치수"));
		SetDlgItemText(IDC_CHECK_WIDTHALARM, _T("폭 연속 불량 거리"));
		SetDlgItemText(IDC_CHECK_MISMATCHALARM, _T("미스매치 연속불량 거리"));

		SetDlgItemText(IDC_SYS_STATIC_ALARM2, _T("이물"));
		SetDlgItemText(IDC_CHECK_DEFECTALARM, _T("구간이물불량"));
		SetDlgItemText(IDC_CHECK_DEFECTALARM2, _T("이물연속불량"));
		SetDlgItemText(IDC_SYS_STATIC_ALARM2_1, _T("M /"));
		SetDlgItemText(IDC_SYS_STATIC_ALARM2_2, _T("초과발생"));
		SetDlgItemText(IDC_SYS_STATIC_ALARM2_3, _T("초과발생"));

		SetDlgItemText(IDC_SYS_STATIC_SYSPARAM1_1, _T("탑-백 거리"));
		SetDlgItemText(IDC_CHECK_TESTALARM, _T("알람테스트"));


		SetDlgItemText(IDC_SYS_STATIC_SYSPARAM2, _T("기준 폭 파라미터"));
		SetDlgItemText(IDC_SYS_STATIC_SYSPARAM2_MIN, _T("최 소"));
		SetDlgItemText(IDC_SYS_STATIC_SYSPARAM2_MAX, _T("최 대"));
		SetDlgItemText(IDC_SYS_STATIC_SYSPARAM2_1, _T("무지1"));
		SetDlgItemText(IDC_SYS_STATIC_SYSPARAM2_2, _T("코팅1"));
		SetDlgItemText(IDC_SYS_STATIC_SYSPARAM2_3, _T("무지2"));
		SetDlgItemText(IDC_SYS_STATIC_SYSPARAM2_4, _T("코팅2"));
		SetDlgItemText(IDC_SYS_STATIC_SYSPARAM2_5, _T("무지3"));
		SetDlgItemText(IDC_SYS_STATIC_SYSPARAM2_6, _T("코팅3"));
		SetDlgItemText(IDC_SYS_STATIC_SYSPARAM2_7, _T("무지4"));
		SetDlgItemText(IDC_SYS_STATIC_SYSPARAM2_8, _T("코팅4"));
		SetDlgItemText(IDC_SYS_STATIC_SYSPARAM2_9, _T("무지5"));
		SetDlgItemText(IDC_SYS_STATIC_SYSPARAM2_M1, _T("미스매치"));
		SetDlgItemText(IDC_SYS_STATIC_SYSPARAM2_M2, _T("미스매치2"));
		

		SetDlgItemText(IDC_BUTTON_ADJUST, _T("적용"));
		SetDlgItemText(IDC_BUTTON_SAVE_INI, _T("모델저장"));
		SetDlgItemText(IDC_BUTTON_CLOSE, _T("닫기"));

		SetDlgItemText(IDC_BUTTON_SAVE_INI3, _T("새모델저장"));

	}
}

void CDlgSysParam::OnEnSetfocusEditSysStandard1Copy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDC_BUTTON_ADJUST)->SetFocus(); 
	
}
void CDlgSysParam::OnEnSetfocusEditSysStandard2Copy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDC_BUTTON_ADJUST)->SetFocus(); 
}
void CDlgSysParam::OnEnSetfocusEditSysStandard3Copy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDC_BUTTON_ADJUST)->SetFocus(); 
}
void CDlgSysParam::OnEnSetfocusEditSysStandard4Copy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDC_BUTTON_ADJUST)->SetFocus(); 
}
void CDlgSysParam::OnEnSetfocusEditSysStandard5Copy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDC_BUTTON_ADJUST)->SetFocus(); 
}
void CDlgSysParam::OnEnSetfocusEditSysStandard6Copy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDC_BUTTON_ADJUST)->SetFocus(); 
}
void CDlgSysParam::OnEnSetfocusEditSysStandard7Copy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDC_BUTTON_ADJUST)->SetFocus(); 
}
void CDlgSysParam::OnEnSetfocusEditSysStandard8Copy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDC_BUTTON_ADJUST)->SetFocus(); 
}
void CDlgSysParam::OnEnSetfocusEditSysStandard9Copy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDC_BUTTON_ADJUST)->SetFocus(); 
}
void CDlgSysParam::OnEnSetfocusEditSysStandard10Copy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDC_BUTTON_ADJUST)->SetFocus(); 
}
void CDlgSysParam::OnEnSetfocusEditSysStandard11Copy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDC_BUTTON_ADJUST)->SetFocus(); 
}
void CDlgSysParam::OnEnSetfocusEditSysStandard12Copy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDC_BUTTON_ADJUST)->SetFocus(); 
}
void CDlgSysParam::OnEnSetfocusEditSysStandard13Copy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDC_BUTTON_ADJUST)->SetFocus(); 
}
void CDlgSysParam::OnEnSetfocusEditSysStandard14Copy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDC_BUTTON_ADJUST)->SetFocus(); 
}
void CDlgSysParam::OnEnSetfocusEditSysStandard15Copy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDC_BUTTON_ADJUST)->SetFocus(); 
}
void CDlgSysParam::OnEnSetfocusEditSysStandard16Copy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDC_BUTTON_ADJUST)->SetFocus(); 
}
void CDlgSysParam::OnEnSetfocusEditSysStandard17Copy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDC_BUTTON_ADJUST)->SetFocus(); 
}
void CDlgSysParam::OnEnSetfocusEditSysStandard18Copy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDC_BUTTON_ADJUST)->SetFocus(); 
}

//
void CDlgSysParam::OnEnKillfocusEditSysStandard1Copy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 1;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dStandard[pDoc->m_pDlgInterface->m_nSelectEdit-1],pView->m_SysParam->m_dMaxValue[pDoc->m_pDlgInterface->m_nSelectEdit-1]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnKillfocusEditSysStandard2Copy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 2;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dStandard[pDoc->m_pDlgInterface->m_nSelectEdit-1],pView->m_SysParam->m_dMaxValue[pDoc->m_pDlgInterface->m_nSelectEdit-1]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnKillfocusEditSysStandard3Copy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 3;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dStandard[pDoc->m_pDlgInterface->m_nSelectEdit-1],pView->m_SysParam->m_dMaxValue[pDoc->m_pDlgInterface->m_nSelectEdit-1]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnKillfocusEditSysStandard4Copy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 4;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dStandard[pDoc->m_pDlgInterface->m_nSelectEdit-1],pView->m_SysParam->m_dMaxValue[pDoc->m_pDlgInterface->m_nSelectEdit-1]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnKillfocusEditSysStandard5Copy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 5;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dStandard[pDoc->m_pDlgInterface->m_nSelectEdit-1],pView->m_SysParam->m_dMaxValue[pDoc->m_pDlgInterface->m_nSelectEdit-1]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnKillfocusEditSysStandard6Copy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 6;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dStandard[pDoc->m_pDlgInterface->m_nSelectEdit-1],pView->m_SysParam->m_dMaxValue[pDoc->m_pDlgInterface->m_nSelectEdit-1]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnKillfocusEditSysStandard7Copy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 7;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dStandard[pDoc->m_pDlgInterface->m_nSelectEdit-1],pView->m_SysParam->m_dMaxValue[pDoc->m_pDlgInterface->m_nSelectEdit-1]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnKillfocusEditSysStandard8Copy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 8;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dStandard[pDoc->m_pDlgInterface->m_nSelectEdit-1],pView->m_SysParam->m_dMaxValue[pDoc->m_pDlgInterface->m_nSelectEdit-1]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnKillfocusEditSysStandard9Copy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 9;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dStandard[pDoc->m_pDlgInterface->m_nSelectEdit-1],pView->m_SysParam->m_dMaxValue[pDoc->m_pDlgInterface->m_nSelectEdit-1]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnKillfocusEditSysStandard10Copy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 11;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dStandard[pDoc->m_pDlgInterface->m_nSelectEdit-1-10],pView->m_SysParam->m_dMaxValue[pDoc->m_pDlgInterface->m_nSelectEdit-1-10]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnKillfocusEditSysStandard11Copy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 12;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dStandard[pDoc->m_pDlgInterface->m_nSelectEdit-1-10],pView->m_SysParam->m_dMaxValue[pDoc->m_pDlgInterface->m_nSelectEdit-1-10]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnKillfocusEditSysStandard12Copy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 13;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dStandard[pDoc->m_pDlgInterface->m_nSelectEdit-11],pView->m_SysParam->m_dMaxValue[pDoc->m_pDlgInterface->m_nSelectEdit-11]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnKillfocusEditSysStandard13Copy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 14;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dStandard[pDoc->m_pDlgInterface->m_nSelectEdit-11],pView->m_SysParam->m_dMaxValue[pDoc->m_pDlgInterface->m_nSelectEdit-11]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnKillfocusEditSysStandard14Copy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 15;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dStandard[pDoc->m_pDlgInterface->m_nSelectEdit-11],pView->m_SysParam->m_dMaxValue[pDoc->m_pDlgInterface->m_nSelectEdit-11]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnKillfocusEditSysStandard15Copy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 16;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dStandard[pDoc->m_pDlgInterface->m_nSelectEdit-11],pView->m_SysParam->m_dMaxValue[pDoc->m_pDlgInterface->m_nSelectEdit-11]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnKillfocusEditSysStandard16Copy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 17;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dStandard[pDoc->m_pDlgInterface->m_nSelectEdit-11],pView->m_SysParam->m_dMaxValue[pDoc->m_pDlgInterface->m_nSelectEdit-11]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnKillfocusEditSysStandard17Copy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 18;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dStandard[pDoc->m_pDlgInterface->m_nSelectEdit-11],pView->m_SysParam->m_dMaxValue[pDoc->m_pDlgInterface->m_nSelectEdit-11]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnKillfocusEditSysStandard18Copy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 19;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dStandard[pDoc->m_pDlgInterface->m_nSelectEdit-11],pView->m_SysParam->m_dMaxValue[pDoc->m_pDlgInterface->m_nSelectEdit-11]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnSetfocusEditSysMismatchtol1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDC_BUTTON_ADJUST)->SetFocus(); 
}

void CDlgSysParam::OnEnSetfocusEditSysMismatchtol5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDC_BUTTON_ADJUST)->SetFocus(); 

}

void CDlgSysParam::OnEnSetfocusEditSysMismatchtol2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDC_BUTTON_ADJUST)->SetFocus(); 
}

void CDlgSysParam::OnEnSetfocusEditSysMismatchtol6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDC_BUTTON_ADJUST)->SetFocus(); 
}

void CDlgSysParam::OnEnKillfocusEditSysMismatchtol1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 31;
	pView->m_NumPad->LabelShow1(0,pDoc->m_pDlgInterface->m_dMismatchTolMin,pDoc->m_pDlgInterface->m_dMismatchTolMax);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnKillfocusEditSysMismatchtol5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 32;
	pView->m_NumPad->LabelShow1(0,pDoc->m_pDlgInterface->m_dMismatchTolMin,pDoc->m_pDlgInterface->m_dMismatchTolMax);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnKillfocusEditSysMismatchtol2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 33;
	pView->m_NumPad->LabelShow1(0,pDoc->m_pDlgInterface->m_dMismatchTolMin1,pDoc->m_pDlgInterface->m_dMismatchTolMax1);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnKillfocusEditSysMismatchtol6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 34;
	pView->m_NumPad->LabelShow1(0,pDoc->m_pDlgInterface->m_dMismatchTolMin1,pDoc->m_pDlgInterface->m_dMismatchTolMax1);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnChangeEditSysScaleX()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


//////////////////////control limit

void CDlgSysParam::OnEnSetfocusEditSysStandard1Copy2()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 101;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dStandard1[pDoc->m_pDlgInterface->m_nSelectEdit-1-100],pView->m_SysParam->m_dMaxValue1[pDoc->m_pDlgInterface->m_nSelectEdit-1-100]);
	pView->m_NumPad->ShowWindow(1);
}
void CDlgSysParam::OnEnSetfocusEditSysStandard2Copy2()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 102;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dStandard1[pDoc->m_pDlgInterface->m_nSelectEdit-1-100],pView->m_SysParam->m_dMaxValue1[pDoc->m_pDlgInterface->m_nSelectEdit-1-100]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnSetfocusEditSysStandard3Copy2()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 103;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dStandard1[pDoc->m_pDlgInterface->m_nSelectEdit-1-100],pView->m_SysParam->m_dMaxValue1[pDoc->m_pDlgInterface->m_nSelectEdit-1-100]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnSetfocusEditSysStandard4Copy2()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 104;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dStandard1[pDoc->m_pDlgInterface->m_nSelectEdit-1-100],pView->m_SysParam->m_dMaxValue1[pDoc->m_pDlgInterface->m_nSelectEdit-1-100]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnSetfocusEditSysStandard5Copy2()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 105;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dStandard1[pDoc->m_pDlgInterface->m_nSelectEdit-1-100],pView->m_SysParam->m_dMaxValue1[pDoc->m_pDlgInterface->m_nSelectEdit-1-100]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnSetfocusEditSysStandard6Copy2()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 106;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dStandard1[pDoc->m_pDlgInterface->m_nSelectEdit-1-100],pView->m_SysParam->m_dMaxValue1[pDoc->m_pDlgInterface->m_nSelectEdit-1-100]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnSetfocusEditSysStandard7Copy2()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 107;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dStandard1[pDoc->m_pDlgInterface->m_nSelectEdit-1-100],pView->m_SysParam->m_dMaxValue1[pDoc->m_pDlgInterface->m_nSelectEdit-1-100]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnSetfocusEditSysStandard8Copy2()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 108;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dStandard1[pDoc->m_pDlgInterface->m_nSelectEdit-1-100],pView->m_SysParam->m_dMaxValue1[pDoc->m_pDlgInterface->m_nSelectEdit-1-100]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnSetfocusEditSysStandard9Copy2()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 109;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dStandard1[pDoc->m_pDlgInterface->m_nSelectEdit-1-100],pView->m_SysParam->m_dMaxValue1[pDoc->m_pDlgInterface->m_nSelectEdit-1-100]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnSetfocusEditSysStandard10Copy2()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 110;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dStandard1[pDoc->m_pDlgInterface->m_nSelectEdit-110],pView->m_SysParam->m_dMaxValue1[pDoc->m_pDlgInterface->m_nSelectEdit-110]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnSetfocusEditSysStandard11Copy2()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 111;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dStandard1[pDoc->m_pDlgInterface->m_nSelectEdit-110],pView->m_SysParam->m_dMaxValue1[pDoc->m_pDlgInterface->m_nSelectEdit-110]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnSetfocusEditSysStandard12Copy2()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 112;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dStandard1[pDoc->m_pDlgInterface->m_nSelectEdit-110],pView->m_SysParam->m_dMaxValue1[pDoc->m_pDlgInterface->m_nSelectEdit-110]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnSetfocusEditSysStandard13Copy2()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 113;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dStandard1[pDoc->m_pDlgInterface->m_nSelectEdit-110],pView->m_SysParam->m_dMaxValue1[pDoc->m_pDlgInterface->m_nSelectEdit-110]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnSetfocusEditSysStandard14Copy2()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 114;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dStandard1[pDoc->m_pDlgInterface->m_nSelectEdit-110],pView->m_SysParam->m_dMaxValue1[pDoc->m_pDlgInterface->m_nSelectEdit-110]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnSetfocusEditSysStandard15Copy2()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 115;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dStandard1[pDoc->m_pDlgInterface->m_nSelectEdit-110],pView->m_SysParam->m_dMaxValue1[pDoc->m_pDlgInterface->m_nSelectEdit-110]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnSetfocusEditSysStandard16Copy2()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 116;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dStandard1[pDoc->m_pDlgInterface->m_nSelectEdit-110],pView->m_SysParam->m_dMaxValue1[pDoc->m_pDlgInterface->m_nSelectEdit-110]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnSetfocusEditSysStandard17Copy2()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 117;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dStandard1[pDoc->m_pDlgInterface->m_nSelectEdit-110],pView->m_SysParam->m_dMaxValue1[pDoc->m_pDlgInterface->m_nSelectEdit-110]);
	pView->m_NumPad->ShowWindow(1);
}
void CDlgSysParam::OnEnSetfocusEditSysStandard18Copy2()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 118;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dStandard1[pDoc->m_pDlgInterface->m_nSelectEdit-110],pView->m_SysParam->m_dMaxValue1[pDoc->m_pDlgInterface->m_nSelectEdit-110]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnBnClickedButtonSaveIni3()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();

	if(pView->m_pModelDlg->IsWindowVisible()){
		pView->m_pModelDlg->ShowWindow(0);
	}
	else{
		pView->m_pModelDlg->GetDlgItem(IDC_BUTTON_REFRESH)->SetFocus();
		pView->m_pModelDlg->ShowWindow(1);

	}


//	pDoc->m_pDlgInterface->OnBnClickedButtonNewmodel();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgSysParam::OnCbnSelchangeComboLane()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	int n = m_cbLane.GetCurSel();

	m_nLimitLane= n+1;
	pView->m_nLimitLane = m_nLimitLane;
	DlgDirSelectComboBox(m_nLimitLane);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgSysParam::DlgDirSelectComboBox(int nSel)
{
	if(m_bInsideSet){	//check 
		if(nSel==1){
			//IDC_EDIT_SYS_STANDARD3_COPY //IDC_EDIT_SYS_STANDARD12_COPY
			//IDC_EDIT_SYS_STANDARD3_COPY2 //IDC_EDIT_SYS_STANDARD12_COPY2
			GetDlgItem(IDC_EDIT_SYS_STANDARD1_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD2_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD3_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD4_COPY)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SYS_STANDARD5_COPY)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SYS_STANDARD6_COPY)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SYS_STANDARD7_COPY)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SYS_STANDARD8_COPY)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SYS_STANDARD9_COPY)->EnableWindow(FALSE);

			GetDlgItem(IDC_EDIT_SYS_STANDARD10_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD11_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD12_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD13_COPY)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SYS_STANDARD14_COPY)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SYS_STANDARD15_COPY)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SYS_STANDARD16_COPY)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SYS_STANDARD17_COPY)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SYS_STANDARD18_COPY)->EnableWindow(FALSE);

			GetDlgItem(IDC_EDIT_SYS_STANDARD1_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD2_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD3_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD4_COPY2)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SYS_STANDARD5_COPY2)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SYS_STANDARD6_COPY2)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SYS_STANDARD7_COPY2)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SYS_STANDARD8_COPY2)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SYS_STANDARD9_COPY2)->EnableWindow(FALSE);

			GetDlgItem(IDC_EDIT_SYS_STANDARD10_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD11_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD12_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD13_COPY2)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SYS_STANDARD14_COPY2)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SYS_STANDARD15_COPY2)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SYS_STANDARD16_COPY2)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SYS_STANDARD17_COPY2)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SYS_STANDARD18_COPY2)->EnableWindow(FALSE);
		}
		else if(nSel==2){
			//IDC_EDIT_SYS_STANDARD5_COPY //IDC_EDIT_SYS_STANDARD14_COPY
			//IDC_EDIT_SYS_STANDARD5_COPY2 //IDC_EDIT_SYS_STANDARD14_COPY2
			GetDlgItem(IDC_EDIT_SYS_STANDARD1_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD2_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD3_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD4_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD5_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD6_COPY)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SYS_STANDARD7_COPY)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SYS_STANDARD8_COPY)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SYS_STANDARD9_COPY)->EnableWindow(FALSE);

			GetDlgItem(IDC_EDIT_SYS_STANDARD10_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD11_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD12_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD13_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD14_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD15_COPY)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SYS_STANDARD16_COPY)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SYS_STANDARD17_COPY)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SYS_STANDARD18_COPY)->EnableWindow(FALSE);

			GetDlgItem(IDC_EDIT_SYS_STANDARD1_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD2_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD3_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD4_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD5_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD6_COPY2)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SYS_STANDARD7_COPY2)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SYS_STANDARD8_COPY2)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SYS_STANDARD9_COPY2)->EnableWindow(FALSE);

			GetDlgItem(IDC_EDIT_SYS_STANDARD10_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD11_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD12_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD13_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD14_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD15_COPY2)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SYS_STANDARD16_COPY2)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SYS_STANDARD17_COPY2)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SYS_STANDARD18_COPY2)->EnableWindow(FALSE);
		}
		else if(nSel==3){
			//IDC_EDIT_SYS_STANDARD7_COPY //IDC_EDIT_SYS_STANDARD16_COPY
			//IDC_EDIT_SYS_STANDARD7_COPY2 //IDC_EDIT_SYS_STANDARD16_COPY2
			GetDlgItem(IDC_EDIT_SYS_STANDARD1_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD2_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD3_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD4_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD5_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD6_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD7_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD8_COPY)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SYS_STANDARD9_COPY)->EnableWindow(FALSE);

			GetDlgItem(IDC_EDIT_SYS_STANDARD10_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD11_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD12_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD13_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD14_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD15_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD16_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD17_COPY)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SYS_STANDARD18_COPY)->EnableWindow(FALSE);

			GetDlgItem(IDC_EDIT_SYS_STANDARD1_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD2_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD3_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD4_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD5_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD6_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD7_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD8_COPY2)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SYS_STANDARD9_COPY2)->EnableWindow(FALSE);

			GetDlgItem(IDC_EDIT_SYS_STANDARD10_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD11_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD12_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD13_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD14_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD15_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD16_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD17_COPY2)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SYS_STANDARD18_COPY2)->EnableWindow(FALSE);
		}
		else{
			//IDC_EDIT_SYS_STANDARD9_COPY //IDC_EDIT_SYS_STANDARD18_COPY
			//IDC_EDIT_SYS_STANDARD9_COPY2 //IDC_EDIT_SYS_STANDARD18_COPY2
			GetDlgItem(IDC_EDIT_SYS_STANDARD1_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD2_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD3_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD4_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD5_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD6_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD7_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD8_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD9_COPY)->EnableWindow(true);

			GetDlgItem(IDC_EDIT_SYS_STANDARD10_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD11_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD12_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD13_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD14_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD15_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD16_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD17_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD18_COPY)->EnableWindow(true);

			GetDlgItem(IDC_EDIT_SYS_STANDARD1_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD2_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD3_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD4_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD5_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD6_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD7_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD8_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD9_COPY2)->EnableWindow(true);

			GetDlgItem(IDC_EDIT_SYS_STANDARD10_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD11_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD12_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD13_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD14_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD15_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD16_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD17_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD18_COPY2)->EnableWindow(true);

		}
		//mismatch 
		GetDlgItem(IDC_EDIT_SYS_MISMATCHTOL10)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_MISMATCHTOL1)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_SYS_MISMATCHTOL5)->EnableWindow(true);

	}
	else{	//modify uncheck 
		//mismatch 
		GetDlgItem(IDC_EDIT_SYS_MISMATCHTOL10)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_SYS_MISMATCHTOL1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_MISMATCHTOL5)->EnableWindow(FALSE);

		//monitor
		GetDlgItem(IDC_EDIT_SYS_STANDARD1_COPY2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD2_COPY2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD3_COPY2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD4_COPY2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD5_COPY2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD6_COPY2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD7_COPY2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD8_COPY2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD9_COPY2)->EnableWindow(FALSE);

		GetDlgItem(IDC_EDIT_SYS_STANDARD10_COPY2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD11_COPY2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD12_COPY2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD13_COPY2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD14_COPY2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD15_COPY2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD16_COPY2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD17_COPY2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD18_COPY2)->EnableWindow(FALSE);

		//min/max 
		GetDlgItem(IDC_EDIT_SYS_STANDARD4_COPY)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD5_COPY)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD6_COPY)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD7_COPY)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD8_COPY)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD9_COPY)->EnableWindow(FALSE);

		GetDlgItem(IDC_EDIT_SYS_STANDARD13_COPY)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD14_COPY)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD15_COPY)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD16_COPY)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD17_COPY)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD18_COPY)->EnableWindow(FALSE);

		GetDlgItem(IDC_EDIT_SYS_STANDARD1_COPY)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_SYS_STANDARD2_COPY)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_SYS_STANDARD3_COPY)->EnableWindow(true);

		GetDlgItem(IDC_EDIT_SYS_STANDARD10_COPY)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_SYS_STANDARD11_COPY)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_SYS_STANDARD12_COPY)->EnableWindow(true);


		//modify	lane == 1 일 경우 나머지는 모두 비활성화 
		GetDlgItem(IDC_EDIT_SYS_STANDARD13_COPY3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD14_COPY3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD15_COPY3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD16_COPY3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD17_COPY3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD18_COPY3)->EnableWindow(FALSE);

		GetDlgItem(IDC_EDIT_SYS_STANDARD10_COPY3)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_SYS_STANDARD11_COPY3)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_SYS_STANDARD12_COPY3)->EnableWindow(true);	//1Lane
		
		if(nSel>1){
			GetDlgItem(IDC_EDIT_SYS_STANDARD13_COPY3)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD14_COPY3)->EnableWindow(true);	//2Lane

			GetDlgItem(IDC_EDIT_SYS_STANDARD4_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD5_COPY)->EnableWindow(true);

			GetDlgItem(IDC_EDIT_SYS_STANDARD13_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD14_COPY)->EnableWindow(true);
		}
		if(nSel>2){
			GetDlgItem(IDC_EDIT_SYS_STANDARD15_COPY3)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD16_COPY3)->EnableWindow(true);	//3Lane

			GetDlgItem(IDC_EDIT_SYS_STANDARD6_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD7_COPY)->EnableWindow(true);

			GetDlgItem(IDC_EDIT_SYS_STANDARD15_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD16_COPY)->EnableWindow(true);
		}
		if(nSel>3){
			GetDlgItem(IDC_EDIT_SYS_STANDARD17_COPY3)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD18_COPY3)->EnableWindow(true);	//4Lane

			GetDlgItem(IDC_EDIT_SYS_STANDARD8_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD9_COPY)->EnableWindow(true);

			GetDlgItem(IDC_EDIT_SYS_STANDARD17_COPY)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD18_COPY)->EnableWindow(true);
		}
	}
}

//모디파이 EditBox & 미스매치 모디파이 EditBox 
void CDlgSysParam::OnEnSetfocusEditSysStandard10Copy3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 119;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dMonitoringTol[0], pView->m_SysParam->m_dMonitoringTol[0]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnSetfocusEditSysStandard11Copy3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 120;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dMonitoringTol[1], pView->m_SysParam->m_dMonitoringTol[1]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnSetfocusEditSysStandard12Copy3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 121;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dMonitoringTol[2], pView->m_SysParam->m_dMonitoringTol[2]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnSetfocusEditSysStandard13Copy3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 122;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dMonitoringTol[3], pView->m_SysParam->m_dMonitoringTol[3]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnSetfocusEditSysStandard14Copy3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 123;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dMonitoringTol[4], pView->m_SysParam->m_dMonitoringTol[4]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnSetfocusEditSysStandard15Copy3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 124;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dMonitoringTol[5], pView->m_SysParam->m_dMonitoringTol[5]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnSetfocusEditSysStandard16Copy3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 125;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dMonitoringTol[6], pView->m_SysParam->m_dMonitoringTol[6]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnSetfocusEditSysStandard17Copy3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 126;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dMonitoringTol[7], pView->m_SysParam->m_dMonitoringTol[7]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnSetfocusEditSysStandard18Copy3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 127;
	pView->m_NumPad->LabelShow1(0,pView->m_SysParam->m_dMonitoringTol[8], pView->m_SysParam->m_dMonitoringTol[8]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnSetfocusEditSysMismatchtol10()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 128;
	pView->m_NumPad->LabelShow1(0,pDoc->m_pDlgInterface->m_dMismatchModify, pDoc->m_pDlgInterface->m_dMismatchModify);
	pView->m_NumPad->ShowWindow(1);
	
}

void CDlgSysParam::OnBnClickedCheckInsideSet()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_bInsideSet = m_bInsideSet;

	CString strLane; 
	m_cbLane.GetWindowText(strLane);
	int nLane = atoi(strLane); 

	if(m_bInsideSet){	//check 
		//min/max 
		GetDlgItem(IDC_EDIT_SYS_STANDARD1_COPY2)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_SYS_STANDARD2_COPY2)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_SYS_STANDARD3_COPY2)->EnableWindow(true);	//1Lane

		GetDlgItem(IDC_EDIT_SYS_STANDARD10_COPY2)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_SYS_STANDARD11_COPY2)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_SYS_STANDARD12_COPY2)->EnableWindow(true);	//1Lane

		if(nLane > 1){
			GetDlgItem(IDC_EDIT_SYS_STANDARD4_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD5_COPY2)->EnableWindow(true);	//2Lane

			GetDlgItem(IDC_EDIT_SYS_STANDARD13_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD14_COPY2)->EnableWindow(true);	//2Lane
		}

		if(nLane > 2){
			GetDlgItem(IDC_EDIT_SYS_STANDARD6_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD7_COPY2)->EnableWindow(true);	//3Lane

			GetDlgItem(IDC_EDIT_SYS_STANDARD15_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD16_COPY2)->EnableWindow(true);	//3Lane
		}

		if(nLane > 3){
			GetDlgItem(IDC_EDIT_SYS_STANDARD8_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD9_COPY2)->EnableWindow(true);	//4Lane

			GetDlgItem(IDC_EDIT_SYS_STANDARD17_COPY2)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD18_COPY2)->EnableWindow(true);	//4Lane
		}

		//modify
		GetDlgItem(IDC_EDIT_SYS_STANDARD10_COPY3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD11_COPY3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD12_COPY3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD13_COPY3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD14_COPY3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD15_COPY3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD16_COPY3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD17_COPY3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD18_COPY3)->EnableWindow(FALSE);

		//mismatch modify
		GetDlgItem(IDC_EDIT_SYS_MISMATCHTOL10)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_MISMATCHTOL1)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_SYS_MISMATCHTOL5)->EnableWindow(true);


	}
	else{	//uncheck 

		//min/max 
		GetDlgItem(IDC_EDIT_SYS_STANDARD1_COPY2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD2_COPY2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD3_COPY2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD4_COPY2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD5_COPY2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD6_COPY2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD7_COPY2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD8_COPY2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD9_COPY2)->EnableWindow(FALSE);

		GetDlgItem(IDC_EDIT_SYS_STANDARD10_COPY2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD11_COPY2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD12_COPY2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD13_COPY2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD14_COPY2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD15_COPY2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD16_COPY2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD17_COPY2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_STANDARD18_COPY2)->EnableWindow(FALSE);

		//modify
		GetDlgItem(IDC_EDIT_SYS_STANDARD10_COPY3)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_SYS_STANDARD11_COPY3)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_SYS_STANDARD12_COPY3)->EnableWindow(true);	//1Lane
		if(nLane>1){
			GetDlgItem(IDC_EDIT_SYS_STANDARD13_COPY3)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD14_COPY3)->EnableWindow(true);	//2Lane
		}
		if(nLane>2){
			GetDlgItem(IDC_EDIT_SYS_STANDARD15_COPY3)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD16_COPY3)->EnableWindow(true);	//3Lane
		}
		if(nLane>3){
			GetDlgItem(IDC_EDIT_SYS_STANDARD17_COPY3)->EnableWindow(true);
			GetDlgItem(IDC_EDIT_SYS_STANDARD18_COPY3)->EnableWindow(true);	//4Lane
		}

		//mismatch modify
		GetDlgItem(IDC_EDIT_SYS_MISMATCHTOL10)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_SYS_MISMATCHTOL1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SYS_MISMATCHTOL5)->EnableWindow(FALSE);

	}

}

void CDlgSysParam::OnBnClickedCheckCoatingline()
{//m_bCLineUse //m_nCLineCount //m_nCLineMeter
	UpdateData();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgSysParam::OnBnClickedCheckFoilsize()
{//m_bFoilSize
	UpdateData();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgSysParam::OnEnSetfocusEditSysFoil1()
{//foil min  //m_dFoilSize
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 129;
	pView->m_NumPad->LabelShow1(0,m_dFoilSize[0], m_dFoilSize[1]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgSysParam::OnEnSetfocusEditSysFoil2()
{//foil max  //m_dFoilSize
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_nSelectEdit = 130;
	pView->m_NumPad->LabelShow1(0,m_dFoilSize[0], m_dFoilSize[1]);
	pView->m_NumPad->ShowWindow(1);
}


void CDlgSysParam::OnBnClickedCheckDefectArlarmMeterRatio()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgSysParam::InitControl()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;

	if(pView->m_strComputerName.Find(_T("CMI"))>=0){
		GetDlgItem(IDC_CHECK_DEFECTALARM)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_BAD_ALARM_DEFECTFRAME3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_BAD_ALARM_DEFECTFRAME2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_BAD_ALARM_DEFECTFRAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_SYS_STATIC_INTERVAL_ALARM_1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_SYS_STATIC_INTERVAL_ALARM_2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_SYS_STATIC_INTERVAL_ALARM_3)->ShowWindow(SW_HIDE);
	}
	else{
		GetDlgItem(IDC_CHECK_DEFECTALARM)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_BAD_ALARM_DEFECTFRAME3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_BAD_ALARM_DEFECTFRAME2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_BAD_ALARM_DEFECTFRAME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_SYS_STATIC_INTERVAL_ALARM_1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_SYS_STATIC_INTERVAL_ALARM_2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_SYS_STATIC_INTERVAL_ALARM_3)->ShowWindow(SW_SHOW);
	}
}


