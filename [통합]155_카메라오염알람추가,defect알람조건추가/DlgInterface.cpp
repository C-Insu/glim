// DlgInterface.cpp : implementation file
//

#include "stdafx.h"
#include "VisWeb.h"
#include "VisWebDoc.h"
#include "VisWebView.h"
#include "DlgInterface.h"
#include "ini.h"
#include "CisSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInterface dialog


CDlgInterface::CDlgInterface(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInterface::IDD, pParent)
	, m_dTopBackDistance(80)
	, m_bFullImageSave(TRUE)
	, m_bRevserseX(FALSE)
	, m_bSim1(FALSE)
	, m_bImageShowHide(TRUE)
	, m_bBlobImgShow(FALSE)
	, m_bSumEdgeData(TRUE)
	, m_dBadAlarmMeter(10)
	, m_bAlarm(FALSE)
	, m_dAlarmMeter(10)
	, m_bTestAlarm(FALSE)
	, m_dMismatchTolMin(0.6)
	, m_dMismatchTolMax(0.6)
	, m_dBadAlarmMismatch(10)
	, m_dMinLineWidth(0.6)
	, m_nLineTh1(65)
	, m_dLineRatio(2)
	, m_nColorGray(FALSE)
	, m_bLineAve(FALSE)
	, m_nLineAveFrame(5)
	, m_dSkipMeter(3)
	, m_nSkipPixel(2000)
	, m_bDefectNgFrame(FALSE)
	, m_bNgFrameInCount(FALSE)
	, m_nBadNgFrame(0)
	, m_nBadFrameInCount(0)
	, m_nBadFrameInDefect(0)
	, m_nContinueBadcnt(0)
	, m_nContinueBadFrame(0)
	, m_bWidthAlarm(FALSE)
	, m_bMisAlarm(FALSE)
	, m_dMinLineWidthMid(4)
	, m_bNewScale(FALSE)
	, m_nSumFrame(50)
	, m_bEdgeInterpolation(FALSE)
	, m_bInsulate(FALSE)
	, m_bAging(FALSE)
	, m_nInsulateTh(30)
	, m_strDefaultBright1(_T("200100"))
	, m_strDefaultBright2(_T("200100"))
	, m_nCoatBright(70)
	, m_nCoatBrightDefault(100)
	, m_bEngKor(FALSE)
	, m_bPreprocessing(TRUE)
	, m_bOriginImage(TRUE)
	, m_bMasterPc(FALSE)
	, m_bAutoEdge(FALSE)
	, m_bLineAverageData(FALSE)
	, m_bDrawData(TRUE)
	, m_bAutoCoatBrightness(FALSE)
	, m_nDefectMag(0)
	, m_bNonCoatingPitch(TRUE)
	, m_bLastData(FALSE)
	, m_bLaneDraw(FALSE)
	, m_nRewinderDistance(0)
	, m_bAutoInsp(FALSE)
	, m_bInsideSet(FALSE)
	, m_nReturnTime(0)
	, m_bReturnTime(FALSE)
	, m_bReverseTest(FALSE)
	, m_bCylinderCheck(FALSE)
	, m_nCylinderCutValue(0)
	, m_nDisplayMeter(0)
	, m_bPlcWrite(FALSE)
	, m_nHeadMisDistance(0)
	, m_dEdgeOffsetmm(0)
	, m_bBinImage(FALSE)
	, m_bAutoReset(FALSE)
	, m_bPLCModelSync(FALSE)
	, m_bServerDataSend(FALSE)
	, m_bSharpness(FALSE)
	, m_nAutoBrightness(0)
	, m_bAutoBrightness(FALSE)
	, m_nLightOnTime(16)
	, m_bInspect(FALSE)
	, m_radioTestPlc(0)
	, m_CheckPLCTest(FALSE)
	, m_nLightPrimer(0)
	, m_bAutoSCInspect(FALSE)
	, m_bShowLog(FALSE)
{
	//{{AFX_DATA_INIT(CDlgInterface)
	m_nSelectEdit = -1;
	m_dExposureTime_inNano = 0;
	m_nMachine = 0;
	param1 = 0.0f;
	param2 = 0.0f;
	param3 = 0.0f;
	param4 = 0.0f;
	param5 = 0.0f;
	param6 = 0.0f;
	param7 = 0.0f;
	param8 = 0.0f;
	param9 = 0.0f;
	param10 = 0.0f;
	param11 = 0.0f;
	param12 = 0.0f;
	param13 = 0.0f;
	param14 = 0.0f;
	param15 = 0.0f;
	paramPinholeY = 0.3;
	paramislandX = 0.3;
	paramislandY = 0.3;
	paramLineX = 0.3;
	paramLineY = 0.3;
	ip= 0;
	frame_len =0.0f;
	scale_x = 0.0f;
	scale_y = 0.0f;
	shutter = 0;
	cal_x = 0.0f;
	cal_y = 0.0f;
	cal_frame = 0;
	algorithm_selection = 0;
	m_pParent = pParent;
	m_fInsParam6 = 0.0f;
	m_dMismatchTolMin1 = 1;
	m_dMismatchTolMax1 = 1;

	for(int i=0;i<MAX_LENGTH;i++){
		m_dStandard[i] = m_dMaxValue[i] =3;
		m_dMonitoringTol[i] = 0.1; 
	}
	//}}AFX_DATA_INIT

	m_bMeterRatioDefect = FALSE;
	m_nMeterRatioCount = 0;
	m_nMeterRatioTotalM = 0;
	m_nMeterRatioMPerCount = 0;
}


void CDlgInterface::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInterface)
	DDX_Text(pDX, IDC_EDIT_EXPOSURE_TIME, m_dExposureTime_inNano);
	DDX_Text(pDX, IDC_EDIT_INS_PARAM1, param1);
	DDX_Text(pDX, IDC_EDIT_INS_PARAM2, param2);
	DDX_Text(pDX, IDC_EDIT_INS_PARAM4, param4);
	DDX_Text(pDX, IDC_EDIT_INS_PARAM5, param5);
	DDX_Text(pDX, IDC_EDIT_SYS_IP, ip);
	DDX_Text(pDX, IDC_EDIT_SYS_FRAME_LENGTH, frame_len);
	DDX_Text(pDX, IDC_EDIT_SYS_SCALE_X, scale_x);
	DDX_Text(pDX, IDC_EDIT_SYS_SCALE_Y, scale_y);
	DDX_Text(pDX, IDC_EDIT_SYS_SHUTTER, shutter);
	DDX_Text(pDX, IDC_EDIT_SYS_CALIB_Y, cal_x);
	DDX_Text(pDX, IDC_EDIT_SYS_CALIB_X, cal_y);
	DDX_Text(pDX, IDC_EDIT_SYS_CALIB_FRAME, cal_frame);
	DDX_Text(pDX, IDC_EDIT_SYS_ALG_PARAM, algorithm_selection);
	DDX_Text(pDX, IDC_EDIT_INS_PARAM6, m_fInsParam6);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_TOPBACK_DISTANCE, m_dTopBackDistance);
	DDX_Check(pDX, IDC_CHECK_FULLSAVE, m_bFullImageSave);
	DDX_Check(pDX, IDC_CHECK_REVERSEX, m_bRevserseX);
	DDX_Check(pDX, IDC_CHECK_SIM1, m_bSim1);
	DDX_Check(pDX, IDC_CHECK_IMAGESHOW, m_bImageShowHide);
	DDX_Check(pDX, IDC_CHECK_BLOBIMG, m_bBlobImgShow);
	DDX_Check(pDX, IDC_CHECK_SUMEDGEDATA, m_bSumEdgeData);
	DDX_Text(pDX, IDC_EDIT_BAD_ALARM_LENGTH, m_dBadAlarmMeter);
	//size
	DDX_Text(pDX, IDC_EDIT_INS_PARAM3, param3);//pinhole x
	DDX_Text(pDX, IDC_EDIT_INS_PARAM12, paramPinholeY);//p
	DDX_Text(pDX, IDC_EDIT_INS_PARAM13, paramislandX);
	DDX_Text(pDX, IDC_EDIT_INS_PARAM14, paramislandY);
	DDX_Text(pDX, IDC_EDIT_INS_PARAM15, paramLineX);
	DDX_Text(pDX, IDC_EDIT_INS_PARAM16, paramLineY);


	//최소값
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD1, m_dStandard[0]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD2, m_dStandard[1]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD3, m_dStandard[2]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD4, m_dStandard[3]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD5, m_dStandard[4]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD6, m_dStandard[5]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD7, m_dStandard[6]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD8, m_dStandard[7]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD9, m_dStandard[8]);

	//최대값
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD10, m_dMaxValue[0]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD11, m_dMaxValue[1]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD12, m_dMaxValue[2]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD13, m_dMaxValue[3]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD14, m_dMaxValue[4]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD15, m_dMaxValue[5]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD16, m_dMaxValue[6]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD17, m_dMaxValue[7]);
	DDX_Text(pDX, IDC_EDIT_SYS_STANDARD18, m_dMaxValue[8]);



	DDX_Check(pDX, IDC_CHECK_ALARMUSE, m_bAlarm);
	DDX_Text(pDX, IDC_EDIT_SYS_ALARM_METER, m_dAlarmMeter);
	DDX_Check(pDX, IDC_CHECK_TESTALARM, m_bTestAlarm);
	DDX_Text(pDX, IDC_EDIT_SYS_MISMATCHTOL1, m_dMismatchTolMin);
	DDX_Text(pDX, IDC_EDIT_SYS_MISMATCHTOL2, m_dMismatchTolMax);
	DDX_Text(pDX, IDC_EDIT_SYS_MISMATCHTOL3, m_dMismatchTolMin1);
	DDX_Text(pDX, IDC_EDIT_SYS_MISMATCHTOL4, m_dMismatchTolMax1);
	DDX_Text(pDX, IDC_EDIT_BAD_ALARM_MISMATCH, m_dBadAlarmMismatch);
	DDX_Text(pDX, IDC_EDIT_INS_PARAM7, m_dMinLineWidth);
	DDX_Text(pDX, IDC_EDIT_INS_PARAM8, m_nLineTh1);
	DDX_Text(pDX, IDC_EDIT_INS_PARAM9, m_dLineRatio);
	DDX_Check(pDX, IDC_CHECK_COLOR_GRAY, m_nColorGray);
	DDX_Check(pDX, IDC_CHECKLINEAVE, m_bLineAve);
	DDX_Text(pDX, IDC_EDIT_LINEAVEFRAME, m_nLineAveFrame);
	DDV_MinMaxInt(pDX, m_nLineAveFrame, 1, 10);
	DDX_Text(pDX, IDC_EDIT_SKIPMETER, m_dSkipMeter);
	DDX_Text(pDX, IDC_EDIT_SKIPPIXEL, m_nSkipPixel);
	DDX_Control(pDX, IDC_EDIT3, m_strCIS);
	DDX_Check(pDX, IDC_CHECK_DEFECTALARM, m_bDefectNgFrame);
	DDX_Check(pDX, IDC_CHECK_DEFECTALARM2, m_bNgFrameInCount);
	DDX_Text(pDX, IDC_EDIT_BAD_ALARM_DEFECTFRAME, m_nBadNgFrame);
	DDX_Text(pDX, IDC_EDIT_BAD_ALARM_DEFECTFRAME2, m_nBadFrameInCount);
	DDX_Text(pDX, IDC_EDIT_BAD_ALARM_DEFECTFRAME3, m_nBadFrameInDefect);
	DDX_Text(pDX, IDC_EDIT_BAD_ALARM_DEFECTFRAME4, m_nContinueBadcnt);
	DDX_Text(pDX, IDC_EDIT_BAD_ALARM_DEFECTFRAME5, m_nContinueBadFrame);
	DDX_Check(pDX, IDC_CHECK_WIDTHALARM, m_bWidthAlarm);
	DDX_Check(pDX, IDC_CHECK_MISMATCHALARM, m_bMisAlarm);
	DDX_Text(pDX, IDC_EDIT_INS_PARAM10, m_dMinLineWidthMid);
	DDX_Check(pDX, IDC_CK_NEWSCALE, m_bNewScale);
	DDX_Text(pDX, IDC_EDIT_SUMFRAME, m_nSumFrame);
	DDX_Check(pDX, IDC_CHECK_EDGEINTERPOLATION, m_bEdgeInterpolation);
	DDX_Check(pDX, IDC_CHECK_INSULATE, m_bInsulate);
	DDX_Check(pDX, IDC_CHECK_AGING, m_bAging);
	DDX_Text(pDX, IDC_EDIT_INS_PARAM11, m_nInsulateTh);
	DDX_Text(pDX, IDC_EDIT_DEFAULTBRIGHT, m_strDefaultBright1);
	DDX_Text(pDX, IDC_EDIT_INSULBRIGHT, m_strDefaultBright2);
	DDX_Text(pDX, IDC_EDIT_INS_PARAMCOATBRIGHT, m_nCoatBright);
	DDX_Text(pDX, IDC_EDIT_INS_PARAMCOATBRIGHT2, m_nCoatBrightDefault);
	DDX_Check(pDX, IDC_CHECK_ENG_KOR, m_bEngKor);
	DDX_Check(pDX, IDC_CHECK_PREPROCESSING, m_bPreprocessing);
	DDX_Check(pDX, IDC_CHECK_ORIGINIMAGE, m_bOriginImage);
	DDX_Check(pDX, IDC_CHECK_MASTERPC, m_bMasterPc);
	DDX_Check(pDX, IDC_CHECK_AUTOEDGE, m_bAutoEdge);
	DDX_Check(pDX, IDC_CHECK_LINEAVERAGEDATA, m_bLineAverageData);
	DDX_Check(pDX, IDC_CHECK_DRAWDATA, m_bDrawData);
	DDX_Check(pDX, IDC_CHECK_AVECOATBRIGHT, m_bAutoCoatBrightness);
	DDX_Text(pDX, IDC_EDIT_ENCODERY, m_nDefectMag);
	DDX_Check(pDX, IDC_CHECK_NONCOATPITCH, m_bNonCoatingPitch);
	DDX_Check(pDX, IDC_CHECK_LASTDATA, m_bLastData);
	DDX_Check(pDX, IDC_CHECK_LANEDRAW, m_bLaneDraw);
	DDX_Text(pDX, IDC_EDIT_REWINDERDISTANCE2, m_nRewinderDistance);
	DDX_Check(pDX, IDC_CHECK_AUTOINSP1, m_bAutoInsp);
	//DDX_Check(pDX, IDC_CHECK_MODIFY, m_bParamModify);
	DDX_Text(pDX, IDC_EDIT_RETURNTIME, m_nReturnTime);
	DDV_MinMaxInt(pDX, m_nReturnTime, 1, 100000000);
	DDX_Check(pDX, IDC_CHECK_RETURN, m_bReturnTime);
	DDX_Check(pDX, IDC_CHECK_REVERSETEST, m_bReverseTest);
	DDX_Check(pDX, IDC_CHECK_CYLINDER, m_bCylinderCheck);
	DDX_Text(pDX, IDC_EDIT_SHARPNESSVALUE, m_nCylinderCutValue);
	DDX_Text(pDX, IDC_EDIT_DISPLAYMETER, m_nDisplayMeter);
	DDX_Check(pDX, IDC_CHECK_PLCWRITE, m_bPlcWrite);
	DDX_Text(pDX, IDC_EDIT_DISPLAYMETER2, m_nHeadMisDistance);
	DDX_Text(pDX, IDC_EDIT_EDGEOFFSET, m_dEdgeOffsetmm);
	DDX_Check(pDX, IDC_CHECK_BINIMAGE, m_bBinImage);
	DDX_Check(pDX, IDC_CHECK_AUTORESET, m_bAutoReset);
	DDX_Check(pDX, IDC_CHECK_PLCMODELSYNC1, m_bPLCModelSync);
	DDX_Check(pDX, IDC_CHECK_DATASEND, m_bServerDataSend);
	DDX_Check(pDX, IDC_CHECK_SHARPNESS, m_bSharpness);
	DDX_Text(pDX, IDC_EDIT_NONCOATBRIGHTNESS, m_nAutoBrightness);
	DDX_Check(pDX, IDC_CHECK_AUTOBRIGHTNESS, m_bAutoBrightness);
	DDX_Text(pDX, IDC_EDIT_LIGHTONTIME, m_nLightOnTime);
	DDV_MinMaxInt(pDX, m_nLightOnTime, 1, 84);
	DDX_Check(pDX, IDC_CHECK_INSPECT1, m_bInspect);
	DDX_Radio(pDX, IDC_RADIO_TEST_ON, m_radioTestPlc);
	DDX_Check(pDX, IDC_CHECK_TEST_PLC, m_CheckPLCTest);
	DDX_Text(pDX, IDC_EDIT_LIGHTONTIME2, m_nLightPrimer);
	DDX_Check(pDX, IDC_CHECK_AUTOINSP2, m_bAutoSCInspect);
	DDX_Check(pDX, IDC_CHECK_SHOW_LOG, m_bShowLog);
}


BEGIN_MESSAGE_MAP(CDlgInterface, CDialog)
	//{{AFX_MSG_MAP(CDlgInterface)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_INI, OnButtonLoadIni)
	ON_BN_CLICKED(IDC_BUTTON_EXPOSURE_CHANGE, OnButtonExposureChange)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_INI, OnButtonSaveIni)
	ON_BN_CLICKED(IDC_BUTTON2, OnButtonGetShutterDefault)
//	ON_BN_CLICKED(IDC_CHECK_MODIFY, &CDlgInterface::OnBnClickedCheckModify)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON3, &CDlgInterface::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON8, &CDlgInterface::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON_PARAM_CLOSE, &CDlgInterface::OnBnClickedButtonParamClose)
	ON_BN_CLICKED(IDC_CHECK_FULLSAVE, &CDlgInterface::OnBnClickedCheckFullsave)
	ON_BN_CLICKED(IDC_CHECK_REVERSEX, &CDlgInterface::OnBnClickedCheckReversex)
	ON_BN_CLICKED(IDC_CHECK_SIM1, &CDlgInterface::OnBnClickedCheckSim1)
	ON_BN_CLICKED(IDC_CHECK_IMAGESHOW, &CDlgInterface::OnBnClickedCheckImageshow)
	ON_BN_CLICKED(IDC_CHECK_BLOBIMG, &CDlgInterface::OnBnClickedCheckBlobimg)
	ON_BN_CLICKED(IDC_CHECK_SUMEDGEDATA, &CDlgInterface::OnBnClickedCheckSumedgedata)
	ON_BN_CLICKED(IDC_BUTTON_UPDATEDATA, &CDlgInterface::OnBnClickedButtonUpdatedata)
	ON_BN_CLICKED(IDC_CHECK_ALARMUSE, &CDlgInterface::OnBnClickedCheckAlarmuse)
	ON_BN_CLICKED(IDC_CHECK_TESTALARM, &CDlgInterface::OnBnClickedCheckTestalarm)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD1, &CDlgInterface::OnEnSetfocusEditSysStandard1)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD2, &CDlgInterface::OnEnSetfocusEditSysStandard2)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD3, &CDlgInterface::OnEnSetfocusEditSysStandard3)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD4, &CDlgInterface::OnEnSetfocusEditSysStandard4)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD5, &CDlgInterface::OnEnSetfocusEditSysStandard5)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD6, &CDlgInterface::OnEnSetfocusEditSysStandard6)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD7, &CDlgInterface::OnEnSetfocusEditSysStandard7)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD8, &CDlgInterface::OnEnSetfocusEditSysStandard8)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD9, &CDlgInterface::OnEnSetfocusEditSysStandard9)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD10, &CDlgInterface::OnEnSetfocusEditSysStandard10)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD11, &CDlgInterface::OnEnSetfocusEditSysStandard11)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD12, &CDlgInterface::OnEnSetfocusEditSysStandard12)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD13, &CDlgInterface::OnEnSetfocusEditSysStandard13)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD14, &CDlgInterface::OnEnSetfocusEditSysStandard14)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD15, &CDlgInterface::OnEnSetfocusEditSysStandard15)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD16, &CDlgInterface::OnEnSetfocusEditSysStandard16)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD17, &CDlgInterface::OnEnSetfocusEditSysStandard17)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_STANDARD18, &CDlgInterface::OnEnSetfocusEditSysStandard18)
	ON_BN_CLICKED(IDC_BUTTON_NEWMODEL, &CDlgInterface::OnBnClickedButtonNewmodel)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_MISMATCHTOL1, &CDlgInterface::OnEnSetfocusEditSysMismatchtol1)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_MISMATCHTOL2, &CDlgInterface::OnEnSetfocusEditSysMismatchtol2)
	ON_BN_CLICKED(IDC_CHECK_COLOR_GRAY, &CDlgInterface::OnBnClickedCheckColorGray)
	ON_BN_CLICKED(IDC_CHECKLINEAVE, &CDlgInterface::OnBnClickedChecklineave)
	ON_BN_CLICKED(IDC_BUTTON7, &CDlgInterface::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON9, &CDlgInterface::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_CHECK_DEFECTALARM, &CDlgInterface::OnBnClickedCheckDefectalarm)
	ON_BN_CLICKED(IDC_CHECK_DEFECTALARM2, &CDlgInterface::OnBnClickedCheckDefectalarm2)
	ON_BN_CLICKED(IDC_CHECK_WIDTHALARM, &CDlgInterface::OnBnClickedCheckWidthalarm)
	ON_BN_CLICKED(IDC_CHECK_MISMATCHALARM, &CDlgInterface::OnBnClickedCheckMismatchalarm)
	ON_EN_SETFOCUS(IDC_EDIT_BAD_ALARM_LENGTH, &CDlgInterface::OnEnSetfocusEditBadAlarmLength)
	ON_EN_SETFOCUS(IDC_EDIT_BAD_ALARM_MISMATCH, &CDlgInterface::OnEnSetfocusEditBadAlarmMismatch)
	ON_EN_SETFOCUS(IDC_EDIT_BAD_ALARM_DEFECTFRAME, &CDlgInterface::OnEnSetfocusEditBadAlarmDefectframe)
	ON_EN_SETFOCUS(IDC_EDIT_BAD_ALARM_DEFECTFRAME3, &CDlgInterface::OnEnSetfocusEditBadAlarmDefectframe3)
	ON_EN_SETFOCUS(IDC_EDIT_BAD_ALARM_DEFECTFRAME2, &CDlgInterface::OnEnSetfocusEditBadAlarmDefectframe2)
	ON_EN_SETFOCUS(IDC_EDIT_BAD_ALARM_DEFECTFRAME4, &CDlgInterface::OnEnSetfocusEditBadAlarmDefectframe4)
	ON_EN_SETFOCUS(IDC_EDIT_BAD_ALARM_DEFECTFRAME5, &CDlgInterface::OnEnSetfocusEditBadAlarmDefectframe5)
	ON_EN_SETFOCUS(IDC_EDIT_LINEAVEFRAME, &CDlgInterface::OnEnSetfocusEditLineaveframe)
	ON_EN_SETFOCUS(IDC_EDIT_SKIPMETER, &CDlgInterface::OnEnSetfocusEditSkipmeter)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_SCALE_X, &CDlgInterface::OnEnSetfocusEditSysScaleX)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_SCALE_Y, &CDlgInterface::OnEnSetfocusEditSysScaleY)
	ON_EN_SETFOCUS(IDC_EDIT_TOPBACK_DISTANCE, &CDlgInterface::OnEnSetfocusEditTopbackDistance)
	ON_EN_SETFOCUS(IDC_EDIT_INS_PARAM1, &CDlgInterface::OnEnSetfocusEditInsParam1)
	ON_EN_SETFOCUS(IDC_EDIT_INS_PARAM2, &CDlgInterface::OnEnSetfocusEditInsParam2)
	ON_EN_SETFOCUS(IDC_EDIT_INS_PARAM3, &CDlgInterface::OnEnSetfocusEditInsParam3)
	ON_EN_SETFOCUS(IDC_EDIT_INS_PARAM4, &CDlgInterface::OnEnSetfocusEditInsParam4)
	ON_EN_SETFOCUS(IDC_EDIT_INS_PARAM5, &CDlgInterface::OnEnSetfocusEditInsParam5)
	ON_EN_SETFOCUS(IDC_EDIT_INS_PARAM6, &CDlgInterface::OnEnSetfocusEditInsParam6)
	ON_EN_SETFOCUS(IDC_EDIT_SKIPPIXEL, &CDlgInterface::OnEnSetfocusEditSkippixel)
	ON_EN_SETFOCUS(IDC_EDIT_INS_PARAM7, &CDlgInterface::OnEnSetfocusEditInsParam7)
	ON_EN_SETFOCUS(IDC_EDIT_INS_PARAM8, &CDlgInterface::OnEnSetfocusEditInsParam8)
	ON_EN_SETFOCUS(IDC_EDIT_INS_PARAM9, &CDlgInterface::OnEnSetfocusEditInsParam9)
	ON_EN_SETFOCUS(IDC_EDIT_INS_PARAM10, &CDlgInterface::OnEnSetfocusEditInsParam10)
	ON_BN_CLICKED(IDC_CK_NEWSCALE, &CDlgInterface::OnBnClickedCkNewscale)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_MISMATCHTOL3, &CDlgInterface::OnEnSetfocusEditSysMismatchtol3)
	ON_EN_SETFOCUS(IDC_EDIT_SYS_MISMATCHTOL4, &CDlgInterface::OnEnSetfocusEditSysMismatchtol4)
	ON_BN_CLICKED(IDC_CHECK_EDGEINTERPOLATION, &CDlgInterface::OnBnClickedCheckEdgeinterpolation)
	ON_BN_CLICKED(IDC_CHECK_INSULATE, &CDlgInterface::OnBnClickedCheckInsulate)
	ON_BN_CLICKED(IDC_CHECK_AGING, &CDlgInterface::OnBnClickedCheckAging)
	ON_EN_SETFOCUS(IDC_EDIT_INS_PARAM11, &CDlgInterface::OnEnSetfocusEditInsParam11)
	ON_BN_CLICKED(IDC_BUTTON10, &CDlgInterface::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CDlgInterface::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTONTEST1, &CDlgInterface::OnBnClickedButtontest1)
	ON_BN_CLICKED(IDC_BUTTONTEST2, &CDlgInterface::OnBnClickedButtontest2)
	ON_BN_CLICKED(IDC_CHECK_ENG_KOR, &CDlgInterface::OnBnClickedCheckEngKor)
//	ON_EN_CHANGE(IDC_EDIT_SYS_STANDARD1, &CDlgInterface::OnEnChangeEditSysStandard1)
ON_BN_CLICKED(IDC_CHECK_PREPROCESSING, &CDlgInterface::OnBnClickedCheckPreprocessing)
ON_BN_CLICKED(IDC_CHECK_ORIGINIMAGE, &CDlgInterface::OnBnClickedCheckOriginimage)
ON_BN_CLICKED(IDC_CHECK_MASTERPC, &CDlgInterface::OnBnClickedCheckMasterpc)
ON_BN_CLICKED(IDC_CHECK_AUTOEDGE, &CDlgInterface::OnBnClickedCheckAutoedge)
ON_BN_CLICKED(IDC_CHECK_LINEAVERAGEDATA, &CDlgInterface::OnBnClickedCheckLineaveragedata)
ON_BN_CLICKED(IDC_CHECK_DRAWDATA, &CDlgInterface::OnBnClickedCheckDrawdata)
ON_BN_CLICKED(IDC_CHECK_AVECOATBRIGHT, &CDlgInterface::OnBnClickedCheckAvecoatbright)
ON_BN_CLICKED(IDC_BUTTON12, &CDlgInterface::OnBnClickedButton12)
ON_BN_CLICKED(IDC_CHECK_NONCOATPITCH, &CDlgInterface::OnBnClickedCheckNoncoatpitch)
ON_BN_CLICKED(IDC_CHECK_LASTDATA, &CDlgInterface::OnBnClickedCheckLastdata)
ON_BN_CLICKED(IDC_CHECK_LANEDRAW, &CDlgInterface::OnBnClickedCheckLanedraw)
ON_BN_CLICKED(IDC_BUTTON_FOLDERINSP, &CDlgInterface::OnBnClickedButtonFolderinsp)
ON_BN_CLICKED(IDC_CHECK_AUTOINSP1, &CDlgInterface::OnBnClickedCheckAutoinsp1)
ON_BN_CLICKED(IDC_CHECK_RETURN, &CDlgInterface::OnBnClickedCheckReturn)
ON_BN_CLICKED(IDC_CHECK_REVERSETEST, &CDlgInterface::OnBnClickedCheckReversetest)
ON_BN_CLICKED(IDC_CHECK_CYLINDER, &CDlgInterface::OnBnClickedCheckCylinder)
ON_BN_CLICKED(IDC_CHECK_PLCWRITE, &CDlgInterface::OnBnClickedCheckPlcwrite)
ON_BN_CLICKED(IDC_BUTTON_METERDATA, &CDlgInterface::OnBnClickedButtonMeterdata)
ON_EN_SETFOCUS(IDC_EDIT_EDGEOFFSET, &CDlgInterface::OnEnSetfocusEditEdgeoffset)
ON_BN_CLICKED(IDC_CHECK_BINIMAGE, &CDlgInterface::OnBnClickedCheckBinimage)
ON_BN_CLICKED(IDC_CHECK_AUTORESET, &CDlgInterface::OnBnClickedCheckAutoreset)
ON_BN_CLICKED(IDC_CHECK_PLCMODELSYNC1, &CDlgInterface::OnBnClickedCheckPlcmodelsync1)
ON_BN_CLICKED(IDC_CHECK_DATASEND, &CDlgInterface::OnBnClickedCheckDatasend)
ON_BN_CLICKED(IDC_CHECK_SHARPNESS, &CDlgInterface::OnBnClickedCheckSharpness)
ON_EN_CHANGE(IDC_EDIT_INS_PARAMCOATBRIGHT2, &CDlgInterface::OnEnChangeEditInsParamcoatbright2)
ON_BN_CLICKED(IDC_BUTTON_EDGEVIEW, &CDlgInterface::OnBnClickedButtonEdgeview)
ON_BN_CLICKED(IDC_CHECK_AUTOBRIGHTNESS, &CDlgInterface::OnBnClickedCheckAutobrightness)
ON_BN_CLICKED(IDC_BUTTONLIGHTADJUST, &CDlgInterface::OnBnClickedButtonlightadjust)
ON_BN_CLICKED(IDC_CHECK_INSPECT1, &CDlgInterface::OnBnClickedCheckInspect1)
ON_BN_CLICKED(IDC_CHECK_TEST_PLC, &CDlgInterface::OnBnClickedCheckTestPlc)
ON_BN_CLICKED(IDC_CHECK_AUTOINSP2, &CDlgInterface::OnBnClickedCheckAutoinsp2)
ON_BN_CLICKED(IDC_CHECK_SHOW_LOG, &CDlgInterface::OnBnClickedCheckShowLog)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInterface message handlers

void CDlgInterface::OnButtonLoadIni() 
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();

// 	pView->m_strOldLot1 = "NATC418 1";
// 	pView->SetTimer(14123,1000,NULL);
// 	pView->MoveImageFile("D:\\Data\\LotComplete\\2020\\03\\09\\NATC913 1\\","NATC913 1");
// 	pView->MakeDefectCsv("D:\\Data\\LotComplete\\2020\\03\\09\\NATC913 1\\","NATC913 1");
// 
// 
// // 	CString strtb,strpath,strlot;
// // 	strtb = pView->m_strComputerName.Left(8)+"H"+pView->m_strComputerName.Right(2);
// // 	strpath.Format("D:\\Data\\LOTdata\\LotComplete\\2020\\03\\06\\NATC613 2\\Surface\\NATC613\\");
// // 	strlot.Format("NATC613 2");
// // 	pView->ReadImageFile(strpath,strlot);
// 
// 	return;
	LoadSysParam();
//	LoadGradeParam();	//Grade
	LoadInsParam();
	LoadLightParam();

	UpdateData(false);	
}

void CDlgInterface::OnButtonSaveIni() 
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
//param backup //m_nContinueBadcnt//m_nContinueBadFrame //m_nRewinderDistance
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
	SaveSysParam();
	SaveInsParam();
	SaveLightParam();
	LoadInsParam();
	LoadSysParam();
	LoadLightParam();

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

void CDlgInterface::LoadDefaultCalib()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();



	//---------------------------------------------
	AfxMessageBox("Computer Name is wrong, Please check it again!");
}

void CDlgInterface::LoadSysParam()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	CString str, str_name,strModelPath,strModel;//cis
	strModel = pDoc->m_data.m_strDefaultModel;//cis
	strModelPath.Format("%s%s.ini","c:\\Glim\\Model\\",strModel);//cis

	int N=pDoc->m_data.m_nVisionLine;
	for(int n=0;n<MAX_CAMERAS;n++)
	{
		str_name = ComputerName();
		str.Format("%s - System Parameter", str_name);		
		if(str_name.Find("OCH")>=0)strModelPath = PARAMETER_PATH;
		CIni ini( strModelPath, str, 1 );//cis
//		CIni ini( PARAMETER_PATH, str, 1 );
		ini.SER_GETD(TRUE, ip						, 0);
		ini.SER_GETD(TRUE, shutter					, 700);
		ini.SER_GETD(TRUE, cal_x					, 0);
		ini.SER_GETD(TRUE, cal_y					, 0);
		ini.SER_GETD(TRUE, cal_frame				, 0);
		ini.SER_GETD(TRUE, frame_len				, 0);
		ini.SER_GETD(TRUE, scale_x					, 0.04233);
		ini.SER_GETD(TRUE, scale_y					, 0.04233);
		ini.SER_GETD(TRUE, algorithm_selection		, 0);
		ini.SER_GETD(TRUE, m_dTopBackDistance		, 70);

		ini.SER_GETD(TRUE, m_bNewScale	, 1);//
		ini.SER_GETD(TRUE, m_nSumFrame	, 100);//

		ini.SER_GETD(TRUE, m_strDefaultBright1	, "600100");//밝기값 16 

		ini.SER_GETD(TRUE, m_nAutoBrightness	, 250);//밝기값 16 
		ini.SER_GETD(TRUE, m_bAutoBrightness	, 0);//밝기값 16 
	
		ini.SER_GETD(TRUE, m_bSumEdgeData		, 1);
		ini.SER_GETD(TRUE, m_nColorGray	, 0);//

		ini.SER_GETD(TRUE, m_bLineAve	, 0);//
		ini.SER_GETD(TRUE, m_nLineAveFrame	, 10);//
		if(m_nLineAveFrame>10)
			m_nLineAveFrame = 10;

		ini.SER_GETD(TRUE, m_nSkipPixel	, 2000);//

		ini.SER_GETD(TRUE, m_bEngKor	, ENG);


///////new param
		ini.SER_GETD(TRUE, sparam1		, 45);//에지 후보1 원단에지
		ini.SER_GETD(TRUE, sparam2		, 22);//Coat edge
		ini.SER_GETD(TRUE, sparam3		, 145);//검사 최대 밝기
		ini.SER_GETD(TRUE, sparam4		, 1);//Edge Offset
		ini.SER_GETD(TRUE, sparam5		, 1);//
		ini.SER_GETD(TRUE, sparam6		, 250);
		ini.SER_GETD(TRUE, sparam7		, 4);
		ini.SER_GETD(TRUE, sparam8		, 12);//
		ini.SER_GETD(TRUE, sparam9		, 0);//
		ini.SER_GETD(TRUE, sparam10	, 1);//
		ini.SER_GETD(TRUE, m_dBadAlarmMeter	, 10);//
		ini.SER_GETD(TRUE, m_dBadAlarmMismatch	, 10);//
		ini.SER_GETD(TRUE, m_bAlarm	, 0);//


		
		ini.SER_GETD(TRUE, m_dSkipMeter	, 3);//
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

// 		ini.SER_GETD(TRUE, m_strDefaultBright1	, "200400");//
// 		ini.SER_GETD(TRUE, m_strDefaultBright2	, "200100");//

		ini.SER_GETD(TRUE, m_nMachine	, 0);//0 양극 1 음극
		ini.SER_GETD(TRUE, m_bNonCoatingPitch	, 1);//무지 폭 화면에 보이기
		ini.SER_GETD(TRUE, m_bLastData	, 1);//마지막 데이터 화면에 보이기
		ini.SER_GETD(TRUE, m_bLaneDraw	, 1);//마지막 데이터 화면에 보이기
		ini.SER_GETD(TRUE, m_nRewinderDistance	, 10);//마지막 데이터 화면에 보이기

		ini.SER_GETD(TRUE, m_nReturnTime	, 10);//마지막 데이터 화면에 보이기
		ini.SER_GETD(TRUE, m_bReturnTime	, 1);//마지막 데이터 화면에 보이기
			
	
		ini.SER_GETD(TRUE, m_bCylinderCheck	, 1);//마지막 데이터 화면에 보이기
		ini.SER_GETD(TRUE, m_nCylinderCutValue	, 200);//마지막 데이터 화면에 보이기
		ini.SER_GETD(TRUE, m_nDisplayMeter	, 5);//마지막 데이터 화면에 보이기

		ini.SER_GETD(TRUE, m_bPlcWrite	, 0);//마지막 데이터 화면에 보이기
		ini.SER_GETD(TRUE, m_nHeadMisDistance	, 62);//마지막 데이터 화면에 보이기

		ini.SER_GETD(TRUE, m_dEdgeOffsetmm	, 0.3);//마지막 데이터 화면에 보이기
		ini.SER_GETD(TRUE, m_bAutoReset	, 0);//마지막 데이터 화면에 보이기
		ini.SER_GETD(TRUE, m_bPLCModelSync	, 0);//마지막 데이터 화면에 보이기
		ini.SER_GETD(TRUE, m_bServerDataSend	, 0);//마지막 데이터 화면에 보이기
	
		ini.SER_GETD(TRUE, m_nLightOnTime	,16);// 조명 노출 타임
		ini.SER_GETD(TRUE, m_bShowLog	,TRUE);

		ini.SER_GETD(TRUE, m_bMeterRatioDefect	,FALSE);		// meter ratio defect 20201022 kjh
		ini.SER_GETD(TRUE, m_nMeterRatioCount	,10);
		ini.SER_GETD(TRUE, m_nMeterRatioTotalM	,100);
		ini.SER_GETD(TRUE, m_nMeterRatioMPerCount	,2);
		


		m_bLineAve = FALSE;
		
		pDoc->m_data.m_nEdgeOffset = m_dEdgeOffsetmm/scale_x;

		pDoc->m_data.m_nWhiteParam = m_nSkipPixel;

		//m_bNgFrameInCount //m_bDefectNgFrame
		//m_nBadNgFrame 몇레임수중 m_nBadFrameInCount 불량 프레임수
		//m_nBadFrameInDefect 프레임당 불량 개수

//		pDoc->m_data.m_dThUp[n] = sparam1;
		pDoc->m_data.m_dThDn[n] = sparam2;
		pDoc->m_data.m_dLimitMaxBright[n] = int(sparam3);
		pDoc->m_data.m_nGl4BlackValue1[n] = int(sparam4);

		pDoc->m_data.m_dScaleFactorX[n] = scale_x;
		pDoc->m_data.m_dScaleFactorY[n] = scale_y;
//		pDoc->m_data.m_dCalibSttX[n]	 = (n*(CAM_WIDTH_CIS*scale_x));
		pDoc->m_data.m_dCalibSttX[n]	 = (n*(CAM_WIDTH_CIS*scale_x+scale_x*24));
		pDoc->m_data.m_dCalibSttY[n]	 = cal_y;

		m_dAlarmMeter;
		pDoc->m_data.m_dBadAlarmMeter = (m_dBadAlarmMeter*1000) / (CAM_HEIGHT_3072*scale_y);

		pDoc->m_data.m_dBadAlarmMismatch = (m_dBadAlarmMismatch*1000) / (CAM_HEIGHT_3072*scale_y);
		pDoc->m_data.m_bSumEdgeData = m_bSumEdgeData;
		m_nContinueBadMeter = (m_nContinueBadFrame*1000)/(scale_y*CAM_HEIGHT_3072);
		////////
		pDoc->m_data.m_nMachine = m_nMachine;

		if (MAX_CAMERAS>1)
		{
			if(n==0){
				pView->m_nExpose		= int(shutter);

			}
			else if(n==1){
				pView->m_nExposre1		= int(shutter);
			}
			else{
				pView->m_nExposre2		= int(shutter);
			}
		}
		else
			pView->m_nExpose		= int(shutter);
		//pDoc->m_data.m_nGradeShutter[n] = int(shutter);
		//pDoc->m_data.m_dThUp[n] = sparam1;//처음 에지
		//pDoc->m_data.m_dThDn[n] = sparam2;//두번째 에지
		//pDoc->m_data.m_nMaxBrightness[n] = sparam3;
		m_nInsulateTh;
		
	}

	if(m_bReturnTime)		GetDlgItem(IDC_EDIT_RETURNTIME)->EnableWindow(1);
	else					GetDlgItem(IDC_EDIT_RETURNTIME)->EnableWindow(0);
	if(m_bCylinderCheck)	GetDlgItem(IDC_EDIT_SHARPNESSVALUE)->EnableWindow(1);
	else					GetDlgItem(IDC_EDIT_SHARPNESSVALUE)->EnableWindow(0);

	CIni ini1( PARAMETER_PATH1, "DB Upload" );
	ini1.SER_GETD(TRUE, LgtController						, 2);
	pDoc->m_data.m_nLgtController = LgtController;
	
	str.Format("server");
	CIni ini2( PARAMETER_PATH, str, 25 );
	ini2.SER_GETD(TRUE, MachineName		, "CT01");
	ini2.SER_GETD(TRUE, UseMarking		, 1);
	pDoc->m_data.m_strMachineName = MachineName;
	pDoc->m_data.m_useMarking = UseMarking;

	pView->m_SysParam->TransParam(FALSE);
	pView->m_pModelDlg->GetDlgItem(IDC_EDIT_PRODUCT_PLC)->EnableWindow(m_bPLCModelSync);


	//AfxMessageBox(MachineName);
}

int CDlgInterface::CheckGradeIni()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();

	CFileFind finder;
	BOOL IsFind;
	CString filename;
	filename.Format("c:\\Glim\\GradeParameter.ini");

	IsFind = finder.FindFile(filename);
// 	if(!IsFind)	
// 		pDoc->m_data.m_nGradeUse = 0;
// 	else
// 		pDoc->m_data.m_nGradeUse = 1;
	finder.Close();
	return 0;
}

void CDlgInterface::LoadGradeParam()
{
// 	CVisWebView *pView = (CVisWebView*)m_pParent;
// 	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
// 	CString str, str_name;
// 	int N = pDoc->m_data.m_nVisionLine;
// 	for(int n=0;n<MAX_CAMERAS;n++)
// 	{
// 		str_name = ComputerName();
// 		str.Format("%s - System Parameter", str_name);
// 		CheckGradeIni();
// 		CIni ini( SHUTTER_PATH, str, 1 );
// 		ini.SER_GETD(TRUE, shutter					, 4000);
// 
// 		if(pDoc->m_data.m_nGradeUse)
// 		{
// 			if(N==GL9 && n==0)
// 				pView->m_nExpose		= int(shutter);
// 			else if(N==GL9 && n==1)
// 				pView->m_nExposre1		= int(shutter);
// 			else
// 				pView->m_nExpose		= int(shutter);
// 		}
// 		else{
// 			if(N==GL9 && n==0)
// 				pView->m_nExpose		= pDoc->m_data.m_nGradeShutter[n];
// 			else if(N==GL9 && n==1)
// 				pView->m_nExposre1		= pDoc->m_data.m_nGradeShutter[n];
// 			else
// 				pView->m_nExpose = 	pDoc->m_data.m_nGradeShutter[n];
// 		}
// 	}
//	pView->UpdateData(FALSE);

}

void CDlgInterface::LoadInsParam()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();

	CString str, str_name,strModelPath,strModel;//cis
	strModel = pDoc->m_data.m_strDefaultModel;//cis
		strModelPath.Format("%s%s.ini","c:\\Glim\\Model\\",strModel);//cis
	for(int i=0;i<MAX_CAMERAS;i++)
	{

// 		if(pDoc->m_data.m_nVisionLine !=GL9 && i==1)
// 			break;
		str_name = ComputerName();

		if(i==0)
			str.Format("%s - Inspect Parameter", str_name);
		else //if(i==1)
			str.Format("%s - Inspect Parameter", str_name);
// 		else
// 			str.Format("%sTB - Inspect Parameter", str_name);
		if(str_name.Find("OCH")>=0)strModelPath = PARAMETER_PATH;

		CIni ini( strModelPath, str, 25 );//cis
//		CIni ini( PARAMETER_PATH, str, 25 );//cis
		ini.SER_GETD(TRUE, param1	, 65);	//gl3- white th  //gl4- dyeSpot th
		ini.SER_GETD(TRUE, param2	, 35);	//gl3- black th  //gl4- Scratch th
		ini.SER_GETD(TRUE, param3	, (float)0.3);//defect size th
		ini.SER_GETD(TRUE, param4	, 100);	//not ins area
		ini.SER_GETD(TRUE, param5	, 0);//gl4 - 진원도
		ini.SER_GETD(TRUE, m_fInsParam6	, 150);//gl4 - 진원도

		ini.SER_GETD(TRUE, m_dMinLineWidth	, 0.6);
		ini.SER_GETD(TRUE, m_dMinLineWidthMid	, 1);

		ini.SER_GETD(TRUE, m_nLineTh1	, 65);
		ini.SER_GETD(TRUE, m_dLineRatio	, 2);

		ini.SER_GETD(TRUE, m_bEdgeInterpolation	, 0);//길이보상
		ini.SER_GETD(TRUE, m_nInsulateTh	, 30);//길이보상
		ini.SER_GETD(TRUE, m_nCoatBright	, 60);//길이보상
		ini.SER_GETD(TRUE, m_nCoatBrightDefault	, 100);//길이보상
		ini.SER_GETD(TRUE, m_bInsulate	, 0);//길이보상
		
		ini.SER_GETD(TRUE, paramPinholeY	, (float)0.3);//defect size th
		ini.SER_GETD(TRUE, paramislandX	, (float)0.3);//defect size th
		ini.SER_GETD(TRUE, paramislandY	, (float)0.3);//defect size th
		ini.SER_GETD(TRUE, paramLineX	, (float)0.3);//defect size th
		ini.SER_GETD(TRUE, paramLineY	, (float)0.3);//defect size th

		
		ini.SER_GETD(TRUE, m_bAutoEdge	, 1);//길이보상
		ini.SER_GETD(TRUE, m_bLineAverageData	, 1);//평균 라인 에지값
		ini.SER_GETD(TRUE, m_bDrawData	, 1);//화면에 글자쓰기
		ini.SER_GETD(TRUE, m_bAutoCoatBrightness	, 1);//화면에 글자쓰기
		ini.SER_GETD(TRUE, m_nDefectMag	, 1);//화면에 글자쓰기

		pDoc->m_data.m_dSizeParam[0] = param3;////0 핀홀/에지덴트 1아일랜드/드레그라인 2라인 3드래그라인
		pDoc->m_data.m_dSizeParam[1] = paramislandX;////0 핀홀 1아일랜드 2라인 3드래그라인
		pDoc->m_data.m_dSizeParam[2] = paramLineX;////0 핀홀 1아일랜드 2라인 3드래그라인

		pDoc->m_data.m_nDefectMag = m_nDefectMag;
		ShowHideButton(!m_bAutoCoatBrightness);

		pDoc->m_data.m_bAutoCoatBrightness = m_bAutoCoatBrightness;
		
		pDoc->m_data.m_bLineAverageData = m_bLineAverageData;


		pDoc->m_data.m_bAutoEdge = m_bAutoEdge;

		pDoc->m_data.m_bInsulateInspect = m_bInsulate;
		pView->m_bInsulateInspect = m_bInsulate;
	

		if(m_bInsulate)
			pDoc->m_data.m_nCoatBright = m_nCoatBright;
		else
			pDoc->m_data.m_nCoatBright = m_nCoatBrightDefault;


		pDoc->m_data.m_dLineRatio = m_dLineRatio;

		pDoc->m_data.m_nMinLineWidth = m_dMinLineWidth/scale_x;
		pDoc->m_data.m_nMinLineWidthMid = m_dMinLineWidthMid/scale_x;

		pDoc->m_data.m_nThWhite3 = param1;//핀홀
		pDoc->m_data.m_nThBlack3 = param2;//아일랜드
		pDoc->m_data.m_dLineScratch = param4;
		pDoc->m_data.m_dInterpolation = param5;
		if(pDoc->m_data.m_dScaleFactorX[0]!=0)
			pDoc->m_data.m_dInterpolationPixel = param5/pDoc->m_data.m_dScaleFactorX[0];

		pDoc->m_data.m_dThSize[i] = double(param3);

//		for(int i=0;i<MAX_CAMERAS;i++){
			pDoc->m_data.m_dLimitMaxBright[i] = m_fInsParam6;
			pDoc->m_data.m_dThUp[i] = m_nLineTh1;
//		}
	}
// 	str.Format("marking");
// 	CIni ini1( PARAMETER_PATH, str, 25 );
// 	ini1.SER_GETD(TRUE, param20						, 1330); 
// 
// 	pDoc->m_data.m_nRcvEdge1 = param20;

	pView->UpdateData(FALSE);
	pDoc->m_pDlgGrid->UpdateGrid(TRUE);
}
//

void CDlgInterface::SaveSysParam()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	CString str, str_name,strModelPath,strModel;//cis
	strModel = pDoc->m_data.m_strDefaultModel;//cis
	strModelPath.Format("%s%s.ini","c:\\Glim\\Model\\",strModel);//cis
	str_name = ComputerName();
	str.Format("%s - System Parameter", str_name);
	
	if(str_name.Find("OCH")>=0)strModelPath = PARAMETER_PATH;

	CIni ini( strModelPath, str, 1 );//cis
//	CIni ini( PARAMETER_PATH, str, 1 );//cis
	ini.SER_GETD(FALSE, ip						, 10);
	ini.SER_GETD(FALSE, shutter					, 10);
	ini.SER_GETD(FALSE, cal_x					, 10);
	ini.SER_GETD(FALSE, cal_y					, 10);
	ini.SER_GETD(FALSE, cal_frame				, 10);
	ini.SER_GETD(FALSE, frame_len				, 10);
	ini.SER_GETD(FALSE, scale_x					, 10);
	ini.SER_GETD(FALSE, scale_y					, 10);
	ini.SER_GETD(FALSE, algorithm_selection		, 10);
	ini.SER_GETD(FALSE, m_dTopBackDistance		, 80);

	ini.SER_GETD(FALSE, m_dBadAlarmMismatch	, 10);//
	ini.SER_GETD(FALSE, m_dBadAlarmMeter	, 10);//
	ini.SER_GETD(FALSE, m_bAlarm	, 0);//
	ini.SER_GETD(FALSE, m_nColorGray	, 0);//

	ini.SER_GETD(FALSE, m_bLineAve	, 0);//
	if(m_nLineAveFrame>10)m_nLineAveFrame = 10;
	ini.SER_GETD(FALSE, m_nLineAveFrame	, 10);//
	ini.SER_GETD(FALSE, m_dSkipMeter	, 3);//int로 수정
	ini.SER_GETD(FALSE, m_nSkipPixel	, 2000);//
	ini.SER_GETD(FALSE, m_bFullImageSave	, 1);//
	
	ini.SER_GETD(FALSE, m_strDefaultBright1	, "600100");//밝기값 16 
	ini.SER_GETD(FALSE, m_nAutoBrightness	, 250);//밝기값 16 
	ini.SER_GETD(FALSE, m_bAutoBrightness	, 0);//밝기값 16 
//  //

	ini.SER_GETD(FALSE, m_bNgFrameInCount	, 1);//
	ini.SER_GETD(FALSE, m_nBadNgFrame	, 10);// 10M 구간중
	ini.SER_GETD(FALSE, m_nBadFrameInDefect	, 10);//10개 불량이 
	ini.SER_GETD(FALSE, m_nBadFrameInCount	, 5);//5장 

	ini.SER_GETD(FALSE, m_bDefectNgFrame	, 1);//
	ini.SER_GETD(FALSE, m_nContinueBadcnt	, 10);//10개 불량이 
	ini.SER_GETD(FALSE, m_nContinueBadFrame	, 5);//연속으로 5장

	ini.SER_GETD(FALSE, m_bWidthAlarm	, 1);//
	ini.SER_GETD(FALSE, m_bMisAlarm	, 1);//

	ini.SER_GETD(FALSE, m_bNewScale	, 1);//
	ini.SER_GETD(FALSE, m_nSumFrame	, 100);//

// 	ini.SER_GETD(FALSE, m_strDefaultBright1	, "200400");//
// 	ini.SER_GETD(FALSE, m_strDefaultBright2	, "200100");//

	ini.SER_GETD(FALSE, m_bEngKor	, KOR);
	ini.SER_GETD(FALSE, m_bPreprocessing	, 1);
	ini.SER_GETD(FALSE, m_bNonCoatingPitch	, 1);
	ini.SER_GETD(FALSE, m_bLastData	, 1);
	ini.SER_GETD(FALSE, m_bLaneDraw	, 1);

	ini.SER_GETD(FALSE, m_nRewinderDistance	, 10);

	ini.SER_GETD(FALSE, m_nReturnTime	, 10);//마지막 데이터 화면에 보이기
	ini.SER_GETD(FALSE, m_bReturnTime	, 1);//마지막 데이터 화면에 보이기

	ini.SER_GETD(FALSE, m_bCylinderCheck	, 1);//마지막 데이터 화면에 보이기
	ini.SER_GETD(FALSE, m_nCylinderCutValue	, 200);//마지막 데이터 화면에 보이기

	ini.SER_GETD(FALSE, m_nDisplayMeter	, 5);//마지막 데이터 화면에 보이기

	ini.SER_GETD(FALSE, m_bPlcWrite	, 0);//마지막 데이터 화면에 보이기
	ini.SER_GETD(FALSE, m_nHeadMisDistance	, 62);//마지막 데이터 화면에 보이기

	ini.SER_GETD(FALSE, m_dEdgeOffsetmm	, 0.3);//마지막 데이터 화면에 보이기
	ini.SER_GETD(FALSE, m_bAutoReset	,0);//마지막 데이터 화면에 보이기
	ini.SER_GETD(FALSE, m_bPLCModelSync	,0);//마지막 데이터 화면에 보이기
	ini.SER_GETD(FALSE, m_bServerDataSend	,0);//마지막 데이터 화면에 보이기

	ini.SER_GETD(FALSE, m_nLightOnTime	,16);// 조명 노출 타임

	ini.SER_GETD(FALSE, m_bShowLog	,TRUE);

	ini.SER_GETD(FALSE, m_bMeterRatioDefect	,FALSE);	// meter ratio defect 20201022 kjh
	ini.SER_GETD(FALSE, m_nMeterRatioCount	,10);
	ini.SER_GETD(FALSE, m_nMeterRatioTotalM	,100);
	ini.SER_GETD(FALSE, m_nMeterRatioMPerCount, 2);
	
	m_bLineAve = FALSE;
	pDoc->m_data.m_nEdgeOffset = m_dEdgeOffsetmm/scale_x;

	pDoc->m_data.m_nWhiteParam = m_nSkipPixel;

	if(pView->m_bNewMode==0)
		pView->m_Inspect.m_rtBound.SetRect(0,1,CAM_WIDTH_CIS,CAM_HEIGHT_CIS);
	else
		pView->m_Inspect.m_rtBound.SetRect(0,1,CAM_WIDTH_CIS*3,CAM_HEIGHT_CIS);

	if(m_nDefectMag>1){
		if(pView->m_bNewMode==0)
			pView->m_Inspect.m_rtBound.SetRect(0,-32,CAM_WIDTH_CIS,CAM_HEIGHT_CIS+32);
		else 
			pView->m_Inspect.m_rtBound.SetRect(0,-32,CAM_WIDTH_CIS*3,CAM_HEIGHT_CIS+32);
	}
	////

	//m_bNgFrameInCount //m_bDefectNgFrame
	//m_nBadNgFrame 몇레임수중 m_nBadFrameInCount 불량 프레임수
	//m_nBadFrameInDefect 프레임당 불량 개수

	if(m_bReturnTime)		GetDlgItem(IDC_EDIT_RETURNTIME)->EnableWindow(1);
	else					GetDlgItem(IDC_EDIT_RETURNTIME)->EnableWindow(0);
	if(m_bCylinderCheck)	GetDlgItem(IDC_EDIT_SHARPNESSVALUE)->EnableWindow(1);
	else					GetDlgItem(IDC_EDIT_SHARPNESSVALUE)->EnableWindow(0);

	for(int i=0;i<MAX_CAMERAS;i++){
		pDoc->m_data.m_dScaleFactorX[i] = scale_x;
		pDoc->m_data.m_dScaleFactorY[i] = scale_y;
	}


}

void CDlgInterface::SaveInsParam()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	UpdateData();
	CString str, str_name,strModelPath,strModel;//cis
	strModel = pDoc->m_data.m_strDefaultModel;//cis
	strModelPath.Format("%s%s.ini","c:\\Glim\\Model\\",strModel);//cis
	str_name = ComputerName();
	str.Format("%s - Inspect Parameter", str_name);
	if(str_name.Find("OCH")>=0)strModelPath = PARAMETER_PATH;

	CIni ini( strModelPath, str, 1 );	
//	CIni ini( PARAMETER_PATH, str, 1 );	
	ini.SER_GETD(FALSE, param1	, 40);
	ini.SER_GETD(FALSE, param2	, 10);
	ini.SER_GETD(FALSE, param3	, 0.3);
	ini.SER_GETD(FALSE, param4	, 10);
	ini.SER_GETD(FALSE, param5	, 10);
	ini.SER_GETD(FALSE, m_fInsParam6	, 1300);
	ini.SER_GETD(FALSE, m_dMinLineWidth	, 1);
	ini.SER_GETD(FALSE, m_dMinLineWidthMid	, 1);
	ini.SER_GETD(FALSE, m_nLineTh1	, 65);
	ini.SER_GETD(FALSE, m_dLineRatio	, 2);

	ini.SER_GETD(FALSE, m_nInsulateTh	, 50);//길이보상
	ini.SER_GETD(FALSE, m_nCoatBright	, 60);//길이보상
	ini.SER_GETD(FALSE, m_nCoatBrightDefault	, 100);//길이보상
	ini.SER_GETD(FALSE, m_bInsulate	, 0);//길이보상

	ini.SER_GETD(FALSE, m_bAutoEdge	, 1);//길이보상

	ini.SER_GETD(FALSE, paramPinholeY	, (float)0.3);//defect size th
	ini.SER_GETD(FALSE, paramislandX	, (float)0.3);//defect size th
	ini.SER_GETD(FALSE, paramislandY	, (float)0.3);//defect size th
	ini.SER_GETD(FALSE, paramLineX	, (float)0.3);//defect size th
	ini.SER_GETD(FALSE, paramLineY	, (float)0.3);//defect size th
	ini.SER_GETD(FALSE, m_bLineAverageData	,1);//defect size th
	ini.SER_GETD(FALSE, m_bDrawData	,1);//defect size th
	ini.SER_GETD(FALSE, m_bAutoCoatBrightness	,1);//defect size th

	ini.SER_GETD(FALSE, m_bEdgeInterpolation	, 0);//길이보상
	ini.SER_GETD(FALSE, m_nDefectMag	, 1);//길이보상

	pDoc->m_data.m_nDefectMag = m_nDefectMag;

	pDoc->m_data.m_dSizeParam[0] = param3;////0 핀홀/에지덴트 1아일랜드/드레그라인 2라인 3드래그라인
	pDoc->m_data.m_dSizeParam[1] = paramislandX;////0 핀홀 1아일랜드 2라인 3드래그라인
	pDoc->m_data.m_dSizeParam[2] = paramLineX;////0 핀홀 1아일랜드 2라인 3드래그라인
	
	pDoc->m_data.m_bAutoCoatBrightness = m_bAutoCoatBrightness;
	pDoc->m_data.m_bLineAverageData = m_bLineAverageData;

	
	pDoc->m_data.m_bAutoEdge = m_bAutoEdge;
	pDoc->m_data.m_bInsulateInspect = m_bInsulate;
	pView->m_bInsulateInspect = m_bInsulate;
	pView->UpdateData(FALSE);
	
	if(m_bInsulate)
		pDoc->m_data.m_nCoatBright = m_nCoatBright;
	else
		pDoc->m_data.m_nCoatBright = m_nCoatBrightDefault;
	pDoc->m_data.m_dLineRatio = m_dLineRatio;



	

	pDoc->m_data.m_nThWhite3 = param1;
	pDoc->m_data.m_nThBlack3 = param2;
	pDoc->m_data.m_dLineScratch = param4;

	pDoc->m_data.m_nMinLineWidth = m_dMinLineWidth/scale_x;
	pDoc->m_data.m_nMinLineWidthMid = m_dMinLineWidthMid/scale_x;

	for(int i=0;i<MAX_CAMERAS;i++){
		pDoc->m_data.m_dThSize[i] = double(param3);

		pDoc->m_data.m_dLimitMaxBright[i] = m_fInsParam6;
			pDoc->m_data.m_dThUp[i] = m_nLineTh1;
	}

}

//--------------------------------------------------------------------------------
void CDlgInterface::OnButtonExposureChange() 
{
	ExposureChange();	
}

void CDlgInterface::ExposureChange()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	m_dExposureTime_inNano = (long)(shutter);

	if(pDoc->m_pVision)
		pDoc->m_pVision->SetExposureTime(0,m_dExposureTime_inNano,0);
}

void CDlgInterface::ExposureChange(long value)
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	m_dExposureTime_inNano = value;
	if(pDoc->m_pVision)
		pDoc->m_pVision->SetExposureTime(0,m_dExposureTime_inNano,0);
}

void CDlgInterface::OnButtonGetShutterDefault() 
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();

// 	double value1 = 0;
// 	if(pDoc->m_pVision)
// 		pDoc->m_pVision->GetExposureTime(&value1);
// 	CString str;
// 	str.Format("%.2f nano sec", value1);
// 	AfxMessageBox(str);	

	CString str;
	int n1 = 0;
	str.Format("1,2,3,4,5,6,7,8,9,10000,2222,3333,4445,6,7,7,8,5,2");
	for(int i=0;i<str.GetLength();i++){
		if(str.GetAt(i) == ',')
			n1++;
	}
	int nn = str.FindOneOf(",");
	nn = nn;
}

CString CDlgInterface::ComputerName()
{
	TCHAR szComputerName[MAX_COMPUTERNAME_LENGTH + 1] = "\0" ;
	DWORD dwSize = MAX_COMPUTERNAME_LENGTH + 1 ;
	GetComputerName( szComputerName, &dwSize ) ;
	CString str;
	str.Format("%s", &szComputerName);
	if(str.Find("CHO")>=0 || str.Find("LJH")>=0 || str.Find("KWON")>=0 )
//	if(str.Find("CHO")>=0 || str.Find("LJH")>=0 || str.Find("KWON")>=0 || str.Find("DESKTOP")>=0)
//	str = "DA01TOPCH";//1412
	str = "OCHCT01CHB1";//1412//chcho
	

#ifdef TEST_MODE
	str = "GL103";  //@@ 
#endif
	return str;
}

CString CDlgInterface::GetIp()
{
	char szHostName[256];
	HOSTENT *pHostInfo = NULL;
	IN_ADDR inAddr;
	
	gethostname(szHostName, 256);
	pHostInfo = gethostbyname(szHostName);
	
	for(int i = 0 ; pHostInfo->h_addr_list[i] != NULL ; i++)
	{
		memcpy(&inAddr, pHostInfo->h_addr_list[i], sizeof(IN_ADDR));
		inet_ntoa(inAddr);  // 리턴값이 자신의 IP
	}
	CString str;
	str.Format("%d.%d.%d.%d", inAddr.S_un.S_un_b.s_b1, inAddr.S_un.S_un_b.s_b2, 
		inAddr.S_un.S_un_b.s_b3, inAddr.S_un.S_un_b.s_b4);
	
	return str;
}

CString CDlgInterface::GetPgmVersion()
{
	
	// 확인 필요사항!--> C:\Program Files\Microsoft Visual Studio\VC98\Lib 의
	// version.lib 를 프로젝트에 포함해야 한다.
//	BYTE       *block;
//	DWORD FAR  *translation;
//	DWORD FAR  *buffer;
//	DWORD        handle;
//	UINT        bytes;
//	TCHAR           *lpszFileName  = _T("c:\\Glim\\VisWeb.exe");
//	TCHAR        name[512];
//	TCHAR        data[256];
	CString        szString;
//	
//	// 버전 정보의 실제 크기를 가져온다.
//	bytes = (UINT)::GetFileVersionInfoSize( lpszFileName, &handle);
//	
//	if(bytes) {
//		block = new BYTE[bytes];
//		
//		// 버전 정보에 대한 실제 블록을 가져온다.
//		if( ::GetFileVersionInfo( lpszFileName, handle, bytes, block) ) {
//			if( ::VerQueryValue( block, _T("\\VarFileInfo\\Translation"), (LPVOID *)&translation,
//				(UINT FAR *)&bytes) ) {
//				
//				// 버전 정보
//				wsprintf(name, _T("\\StringFileInfo\\%04x%04x\\FileVersion"), 
//					LOWORD(*translation), HIWORD(*translation) );
//				
//				if( ::VerQueryValue(block, name, (LPVOID *)&buffer, (UINT FAR *)&bytes) ) {
//					szString.Format(_T("Version %s"), (LPCTSTR)buffer );
////				MessageBox(szString);           //여기서 버전을 얻어온다. 
//				delete[] block;
//				return szString;
//
//				}
//				else
//					szString.Format(_T("Unable to get Version Info"), data);
//				
//				// Product Name 정보
//				wsprintf(name, _T("\\StringFileInfo\\%04x%04x\\ProductName"), LOWORD(*translation),          HIWORD(*translation) );
//				
//				if( ::VerQueryValue(block, name, (LPVOID *)&buffer, (UINT FAR *)&bytes) ) {
//					szString.Format( _T("%s"), (LPCTSTR)buffer );
//				}
//				else
//					szString.Format( _T("Unable to get Product Name") );
//			}
//			else 
//				szString.Format( _T("(Unable to get translation type)") );
//		}
//		else 
//			szString.Format( _T("(Unable to get FileVersionInfo)") );
//		
//		delete [] block;
//	}
//	else {
//		szString.Format( _T("(Unable to get FileVersionInfo size)") );
//	}
	return szString;
}




void CDlgInterface::OnBnClickedButton3()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pView->LoadAllImage();

}

void CDlgInterface::OnBnClickedButton8()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();

	pView->m_nInspBreak[0] = pView->m_nInspBreak[1] = pView->m_nInspBreak[2] = 0;

	double dt1 = pView->GetPrecisionTime();
	for(int k=0;k<MAX_CAMERAS;k++){
		for(int i=0;i<10;i++){
			pDoc->m_data.m_dInspDetailTime[k][i]=0.;
		pDoc->m_data.m_dFullTime[k*10+2] = pDoc->m_data.m_dInspDetailTime[k][0] = pView->GetPrecisionTime();
		}
	}

	static double doldtime1 = 0;

	double dtime1 = pView->GetPrecisionTime();

	if(doldtime1>0){
		pView->m_fFps = float(1000 /( (dtime1-doldtime1)*1000));
	}
	doldtime1 = dtime1;

	pDoc->m_data.ResetData(0);
	pDoc->m_data.ResetData(1);
	pDoc->m_data.ResetData(2);
	if(pDoc->m_pDlgInterface->m_bPreprocessing)
		for(int k=0;k<3;k++)
			for(int idx=0;idx<MOD_COUNT;idx++)
				pView->m_bPreprocessing[k][idx] = TRUE;

	
	{
		//put data
// 		pView->TransLineData();
// 		double dt2 = pView->GetPrecisionTime();
// 		CString str1;	str1.Format("%.1f",(dt2-dt1)*1000);
// 		pView->AddtoList(str1,0);

		pView->m_bFullCopy[0] =pView->m_bFullCopy[1] =pView->m_bFullCopy[2] = TRUE;
	}
//	pView->Inspect(0);
//	pView->Inspect(1);
//	pView->Inspect(2);

//	pView->capture1(pDoc->m_data.m_strLot,pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck]);
}

void CDlgInterface::OnBnClickedButtonParamClose()
{
	m_nSelectEdit = -1;
	ShowWindow(SW_HIDE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgInterface::OnBnClickedCheckFullsave()
{//m_bFullImageSave
	UpdateData();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgInterface::OnBnClickedCheckReversex()
{//m_bRevserseX
	UpdateData();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgInterface::OnBnClickedCheckSim1()
{//m_bSim1
	UpdateData();
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();

//	pView->m_defectMap->m_bSim1 = m_bSim1;
	if(m_bSim1==TRUE){

		pView->DrawImage(3);
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgInterface::OnBnClickedCheckImageshow()
{//m_bImageShowHide
	UpdateData();
	CVisWebView *pView = (CVisWebView*)m_pParent;
	if(!m_bImageShowHide)
		pView->m_bDrawCheck = TRUE;
	else{
		pView->ShowTopLength(0);
	}
	pView->SetTimer(12011,1000,NULL);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgInterface::OnBnClickedCheckBlobimg()
{//m_bBlobImgShow
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	UpdateData();
	pDoc->m_data.m_bBlobImg = m_bBlobImgShow;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgInterface::OnBnClickedCheckSumedgedata()
{//m_bSumEdgeData
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	UpdateData();
	pDoc->m_data.m_bSumEdgeData = m_bSumEdgeData;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgInterface::OnBnClickedButtonUpdatedata()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	UpdateData();
	pDoc->m_data.m_dBadAlarmMeter = (m_dBadAlarmMeter*1000) / (CAM_HEIGHT_3072*scale_y);
	pDoc->m_data.m_dBadAlarmMismatch = (m_dBadAlarmMismatch*1000) / (CAM_HEIGHT_3072*scale_y);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgInterface::OnBnClickedCheckAlarmuse()
{//m_bAlarm
	UpdateData();
	if(m_bAlarm==FALSE){
		m_bNgFrameInCount = FALSE;
		m_bWidthAlarm=m_bMisAlarm=FALSE;
		m_bDefectNgFrame = FALSE;
		m_bNgFrameInCount = FALSE;
		UpdateData(FALSE);
	}
	else{
// 		m_bNgFrameInCount = FALSE;
// 		m_bWidthAlarm=m_bMisAlarm=FALSE;
// 		m_bDefectNgFrame = FALSE;
// 		m_bNgFrameInCount = FALSE;
// 		UpdateData(FALSE);

	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgInterface::OnBnClickedCheckTestalarm()
{//m_btestAlarm
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();
	if(m_bTestAlarm){
		pView->m_IO[0].WriteOutputPort(0,0,1);
	}
	else{
		pView->m_IO[0].WriteOutputPort(0,0,0);
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgInterface::OnEnSetfocusEditSysStandard1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	m_nSelectEdit = 1;
	pView->m_NumPad->LabelShow1(0,m_dStandard[m_nSelectEdit-1],m_dMaxValue[m_nSelectEdit-1]);
	pView->m_NumPad->ShowWindow(1);

}
void CDlgInterface::OnEnSetfocusEditSysStandard2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	m_nSelectEdit = 2;
	pView->m_NumPad->LabelShow1(0,m_dStandard[m_nSelectEdit-1],m_dMaxValue[m_nSelectEdit-1]);
	pView->m_NumPad->ShowWindow(1);

}
void CDlgInterface::OnEnSetfocusEditSysStandard3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	m_nSelectEdit = 3;
	pView->m_NumPad->LabelShow1(0,m_dStandard[m_nSelectEdit-1],m_dMaxValue[m_nSelectEdit-1]);
	pView->m_NumPad->ShowWindow(1);

}
void CDlgInterface::OnEnSetfocusEditSysStandard4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	m_nSelectEdit = 4;
	pView->m_NumPad->LabelShow1(0,m_dStandard[m_nSelectEdit-1],m_dMaxValue[m_nSelectEdit-1]);
	pView->m_NumPad->ShowWindow(1);

}
void CDlgInterface::OnEnSetfocusEditSysStandard5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	m_nSelectEdit = 5;
	pView->m_NumPad->LabelShow1(0,m_dStandard[m_nSelectEdit-1],m_dMaxValue[m_nSelectEdit-1]);

	pView->m_NumPad->ShowWindow(1);

}
void CDlgInterface::OnEnSetfocusEditSysStandard6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	m_nSelectEdit = 6;
	pView->m_NumPad->LabelShow1(0,m_dStandard[m_nSelectEdit-1],m_dMaxValue[m_nSelectEdit-1]);
	pView->m_NumPad->ShowWindow(1);

}
void CDlgInterface::OnEnSetfocusEditSysStandard7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	m_nSelectEdit = 7;
	pView->m_NumPad->LabelShow1(0,m_dStandard[m_nSelectEdit-1],m_dMaxValue[m_nSelectEdit-1]);
	pView->m_NumPad->ShowWindow(1);

}
void CDlgInterface::OnEnSetfocusEditSysStandard8()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	m_nSelectEdit = 8;
	pView->m_NumPad->LabelShow1(0,m_dStandard[m_nSelectEdit-1],m_dMaxValue[m_nSelectEdit-1]);
	pView->m_NumPad->ShowWindow(1);

}
void CDlgInterface::OnEnSetfocusEditSysStandard9()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	m_nSelectEdit = 9;
	pView->m_NumPad->LabelShow1(0,m_dStandard[m_nSelectEdit-1],m_dMaxValue[m_nSelectEdit-1]);
	pView->m_NumPad->ShowWindow(1);

}

///최대값
void CDlgInterface::OnEnSetfocusEditSysStandard10()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	m_nSelectEdit = 11;
	pView->m_NumPad->LabelShow1(1,m_dMaxValue[m_nSelectEdit-11],m_dMaxValue[m_nSelectEdit-11]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgInterface::OnEnSetfocusEditSysStandard11()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	m_nSelectEdit = 12;
	pView->m_NumPad->LabelShow1(1,m_dMaxValue[m_nSelectEdit-11],m_dMaxValue[m_nSelectEdit-11]);
	pView->m_NumPad->ShowWindow(1);
}
void CDlgInterface::OnEnSetfocusEditSysStandard12()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	m_nSelectEdit = 13;
	pView->m_NumPad->LabelShow1(1,m_dMaxValue[m_nSelectEdit-11],m_dMaxValue[m_nSelectEdit-11]);
	pView->m_NumPad->ShowWindow(1);
}
void CDlgInterface::OnEnSetfocusEditSysStandard13()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	m_nSelectEdit = 14;
	pView->m_NumPad->LabelShow1(1,m_dMaxValue[m_nSelectEdit-11],m_dMaxValue[m_nSelectEdit-11]);
	pView->m_NumPad->ShowWindow(1);
}
void CDlgInterface::OnEnSetfocusEditSysStandard14()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	m_nSelectEdit = 15;
	pView->m_NumPad->LabelShow1(1,m_dMaxValue[m_nSelectEdit-11],m_dMaxValue[m_nSelectEdit-11]);
	pView->m_NumPad->ShowWindow(1);
}
void CDlgInterface::OnEnSetfocusEditSysStandard15()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	m_nSelectEdit = 16;
	pView->m_NumPad->LabelShow1(1,m_dMaxValue[m_nSelectEdit-11],m_dMaxValue[m_nSelectEdit-11]);
	pView->m_NumPad->ShowWindow(1);
}
void CDlgInterface::OnEnSetfocusEditSysStandard16()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	m_nSelectEdit = 17;
	pView->m_NumPad->LabelShow1(1,m_dMaxValue[m_nSelectEdit-11],m_dMaxValue[m_nSelectEdit-11]);
	pView->m_NumPad->ShowWindow(1);
}
void CDlgInterface::OnEnSetfocusEditSysStandard17()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	m_nSelectEdit = 18;
	pView->m_NumPad->LabelShow1(1,m_dMaxValue[m_nSelectEdit-11],m_dMaxValue[m_nSelectEdit-11]);
	pView->m_NumPad->ShowWindow(1);
}
void CDlgInterface::OnEnSetfocusEditSysStandard18()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	m_nSelectEdit = 19;
	pView->m_NumPad->LabelShow1(1,m_dMaxValue[m_nSelectEdit-11],m_dMaxValue[m_nSelectEdit-11]);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgInterface::OnBnClickedButtonNewmodel()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();

	ShellExecute(NULL,"open","OSK.exe",NULL,NULL,SW_SHOWNORMAL);
	CFileDialog dlg(FALSE, _T("ini"), NULL, OFN_SHAREAWARE, _T("Model (*.ini)|*.ini||"));

// 	CString strInitPath;
// 	strInitPath.Format(_T("C:\\Glim\\\TesImg\\")); //C:\glim\TesImg
// 	bi.lParam = (LPARAM)strInitPath.GetBuffer(strInitPath.GetLength()); 
// 	LPITEMIDLIST lpifq=SHBrowseForFolder(&bi);

	dlg.m_ofn.lpstrInitialDir = pView->m_strModelPath;
	if(dlg.DoModal() == IDOK)
	{
		
		CString strModel = dlg.GetFileName();
		strModel.TrimRight(".ini");
		
		pDoc->m_data.m_strDefaultModel = strModel;

		pView->UpdateTolIni(pDoc->m_data.m_strDefaultModel,0);


// 		m_FormTab2->m_strModel = strModel;
// 		m_FormTab2->UpdateSetupIni(FALSE);
// 		m_FormTab1->UpdateIniTabIns(strModel,FALSE);
// 		m_FormTab4->UpdateIniWeldingIns(strModel,FALSE);
// 		m_FormTab5->UpdateIniTapeIns(strModel,FALSE);
// 		m_FormTab6->UpdateIniReverseIns(strModel,FALSE);
// 
// 		m_FormTab2->UpdateSetupIni(TRUE);
// 		m_FormTab1->UpdateIniTabIns(strModel,TRUE);
// 		m_FormTab4->UpdateIniWeldingIns(strModel,TRUE);
// 		m_FormTab5->UpdateIniTapeIns(strModel,TRUE);
// 		m_FormTab6->UpdateIniReverseIns(strModel,TRUE);

	}
}

void CDlgInterface::OnEnSetfocusEditSysMismatchtol1()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	m_nSelectEdit = 31;
	pView->m_NumPad->LabelShow1(0,m_dMismatchTolMin,m_dMismatchTolMax);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgInterface::OnEnSetfocusEditSysMismatchtol2()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	m_nSelectEdit = 32;
	pView->m_NumPad->LabelShow1(1,m_dMismatchTolMin,m_dMismatchTolMax);
	pView->m_NumPad->ShowWindow(1);
	
}

void CDlgInterface::OnBnClickedCheckColorGray()
{//	ini.SER_GETD(FALSE, m_nColorGray	, 0);//
	UpdateData();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgInterface::OnBnClickedChecklineave()
{//m_bLineAve
	UpdateData();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgInterface::OnBnClickedButton7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.	
	CVisWebView *pView = (CVisWebView*)m_pParent;
	bool bRtn=false;

	if(!pView->m_bAuto){
		bRtn = pView->m_cis->ResetCamera();	//8초 이상 소요됨. 
	}

	if(bRtn){
		pView->m_cis->SendCmd(_T("DT01"),0); //메모리 1 다시 로드 
		pView->AddtoList(_T("camera reset"),0,0); 
	}else
		pView->AddtoList(_T("camera reset fail!"),0,0); 

			
	
}

void CDlgInterface::OnBnClickedButton9()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	
	CString strCmd; 

	m_strCIS.GetWindowText(strCmd); 
	strCmd.Format(_T("%s"),strCmd);
	
	pView->m_cis->SendCmd(strCmd,0); 
	
	m_strCIS.SetWindowText(_T("")); 

	strCmd.Format(_T("Camera Response: %s"),pView->m_cis->tCisRxData);
	pView->AddtoList(strCmd, 0, 0);  

}

void CDlgInterface::OnBnClickedCheckDefectalarm()
{//m_bDefectNgFrame;
	UpdateData();
	if(m_bAlarm==FALSE){
		m_bDefectNgFrame = FALSE;
		UpdateData(FALSE);
	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgInterface::OnBnClickedCheckDefectalarm2()
{//m_bNgFrameInCount //
	UpdateData();
	if(m_bAlarm==FALSE){
		m_bNgFrameInCount = FALSE;
		UpdateData(FALSE);
	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgInterface::OnBnClickedCheckWidthalarm()
{//m_bWidthAlarm//m_bMisAlarm
	UpdateData();
	if(m_bAlarm==FALSE){
		m_bWidthAlarm = FALSE;
		UpdateData(FALSE);
	}
	if(!m_bWidthAlarm){
		CVisWebView *pView = (CVisWebView*)m_pParent;
		pView->m_nAlarmEndFRame = 0;
	}
}

void CDlgInterface::OnBnClickedCheckMismatchalarm()
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgInterface::OnEnSetfocusEditBadAlarmLength()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();//m_dBadAlarmMeter
	pView->m_NumPad->m_nSelectControl = 1;
	pView->m_NumPad->LabelShow2(0,m_dBadAlarmMeter,m_dBadAlarmMeter);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgInterface::OnEnSetfocusEditBadAlarmMismatch()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();//m_dBadAlarmMismatch
	pView->m_NumPad->m_nSelectControl = 2;
	pView->m_NumPad->LabelShow2(0,m_dBadAlarmMismatch,m_dBadAlarmMismatch);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgInterface::OnEnSetfocusEditBadAlarmDefectframe()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();//m_nBadNgFrame
	pView->m_NumPad->m_nSelectControl = 3;
	pView->m_NumPad->LabelShow2(0,m_nBadNgFrame,m_nBadNgFrame);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgInterface::OnEnSetfocusEditBadAlarmDefectframe3()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();//m_nBadFrameInDefect
	pView->m_NumPad->m_nSelectControl = 4;
	pView->m_NumPad->LabelShow2(0,m_nBadFrameInDefect,m_nBadFrameInDefect);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgInterface::OnEnSetfocusEditBadAlarmDefectframe2()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();//m_nBadFrameInCount
	pView->m_NumPad->m_nSelectControl = 5;
	pView->m_NumPad->LabelShow2(0,m_nBadFrameInCount,m_nBadFrameInCount);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgInterface::OnEnSetfocusEditBadAlarmDefectframe4()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();//m_nContinueBadcnt
	pView->m_NumPad->m_nSelectControl = 6;
	pView->m_NumPad->LabelShow2(0,m_nContinueBadcnt,m_nContinueBadcnt);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgInterface::OnEnSetfocusEditBadAlarmDefectframe5()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();//m_nContinueBadFrame
	pView->m_NumPad->m_nSelectControl = 7;
	pView->m_NumPad->LabelShow2(0,m_nContinueBadFrame,m_nContinueBadFrame);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgInterface::OnEnSetfocusEditLineaveframe()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();//m_nLineAveFrame
	pView->m_NumPad->m_nSelectControl = 8;
	pView->m_NumPad->LabelShow2(0,m_nLineAveFrame,m_nLineAveFrame);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgInterface::OnEnSetfocusEditSkipmeter()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();//m_dSkipMeter
	pView->m_NumPad->m_nSelectControl = 9;
	pView->m_NumPad->LabelShow2(0,m_dSkipMeter,m_dSkipMeter);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgInterface::OnEnSetfocusEditSysScaleX()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();//scale_x
	pView->m_NumPad->m_nSelectControl = 10;
	pView->m_NumPad->LabelShow2(0,scale_x,scale_x);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgInterface::OnEnSetfocusEditSysScaleY()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();//scale_y
	pView->m_NumPad->m_nSelectControl = 11;
	pView->m_NumPad->LabelShow2(0,scale_y,scale_y);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgInterface::OnEnSetfocusEditTopbackDistance()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();//m_dTopBackDistance
	pView->m_NumPad->m_nSelectControl = 12;
	pView->m_NumPad->LabelShow2(0,m_dTopBackDistance,m_dTopBackDistance);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgInterface::OnEnSetfocusEditInsParam1()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();//param1
	pView->m_NumPad->m_nSelectControl = 13;
	pView->m_NumPad->LabelShow2(0,param1,param1);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgInterface::OnEnSetfocusEditInsParam2()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();//param2
	pView->m_NumPad->m_nSelectControl = 14;
	pView->m_NumPad->LabelShow2(0,param2,param2);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgInterface::OnEnSetfocusEditInsParam3()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();//param2
	pView->m_NumPad->m_nSelectControl = 15;
	pView->m_NumPad->LabelShow2(0,param3,param3);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgInterface::OnEnSetfocusEditInsParam4()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();//param2
	pView->m_NumPad->m_nSelectControl = 16;
	pView->m_NumPad->LabelShow2(0,param4,param4);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgInterface::OnEnSetfocusEditInsParam5()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();//param2
	pView->m_NumPad->m_nSelectControl = 17;
	pView->m_NumPad->LabelShow2(0,param5,param5);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgInterface::OnEnSetfocusEditInsParam6()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();//param2
	pView->m_NumPad->m_nSelectControl = 18;
	pView->m_NumPad->LabelShow2(0,m_fInsParam6,m_fInsParam6);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgInterface::OnEnSetfocusEditSkippixel()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();//param2
	pView->m_NumPad->m_nSelectControl = 19;
	pView->m_NumPad->LabelShow2(0,m_nSkipPixel,m_nSkipPixel);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgInterface::OnEnSetfocusEditInsParam7()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();//param2
	pView->m_NumPad->m_nSelectControl = 20;
	pView->m_NumPad->LabelShow2(0,m_dMinLineWidth,m_dMinLineWidth);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgInterface::OnEnSetfocusEditInsParam8()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();//param2
	pView->m_NumPad->m_nSelectControl = 21;
	pView->m_NumPad->LabelShow2(0,m_nLineTh1,m_nLineTh1);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgInterface::OnEnSetfocusEditInsParam9()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();//param2
	pView->m_NumPad->m_nSelectControl = 22;
	pView->m_NumPad->LabelShow2(0,m_dLineRatio,m_dLineRatio);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgInterface::OnEnSetfocusEditInsParam10()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();//param2
	pView->m_NumPad->m_nSelectControl = 23;
	pView->m_NumPad->LabelShow2(0,m_dMinLineWidthMid,m_dMinLineWidthMid);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgInterface::ChangeValue(int n,CString strvalue)
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	CString strint,strduble,strduble1;
	double dtmp,dtmp1;
	dtmp = atof(strvalue);
	strduble.Format("%.1f",dtmp);
	strduble1.Format("%.2f",dtmp);
	dtmp = atof(strduble);
	dtmp1 = atof(strduble1);
	if(n<=0)
		return;
	else if(n==1)	m_dBadAlarmMeter = atoi(strvalue);
	else if(n==2)		m_dBadAlarmMismatch = atoi(strvalue);
	else if(n==3)		m_nBadNgFrame = atoi(strvalue);
	else if(n==4)		m_nBadFrameInDefect = atoi(strvalue);
	else if(n==5)		m_nBadFrameInCount = atoi(strvalue);
	else if(n==6)		m_nContinueBadcnt = atoi(strvalue);
	else if(n==7)		m_nContinueBadFrame = atoi(strvalue);
	else if(n==8)		m_nLineAveFrame = atoi(strvalue);
	else if(n==9)		m_dSkipMeter = atoi(strvalue);
	else if(n==10)		scale_x = atof(strvalue);
	else if(n==11)		scale_y = atof(strvalue);
	else if(n==12)		m_dTopBackDistance = dtmp;
	else if(n==13)		param1 = atoi(strvalue);
	else if(n==14)		param2 = atoi(strvalue);
	else if(n==15)		param3 = dtmp;
	else if(n==16)		param4 = atoi(strvalue);
	else if(n==17)		param5 = atof(strvalue);//dtmp;
	else if(n==18)		m_fInsParam6 = atoi(strvalue);
	else if(n==19)		m_nSkipPixel = atoi(strvalue);//dtmp;
	else if(n==20)		m_dMinLineWidth = dtmp;//atoi(strvalue);
	else if(n==21)		m_nLineTh1 = atoi(strvalue);
	else if(n==22)		m_dLineRatio = atoi(strvalue);
	else if(n==23)		m_dMinLineWidthMid = dtmp;
	else if(n==24){
		m_dEdgeOffsetmm = dtmp1;
	}
	else if(n==35)		m_nInsulateTh = atoi(strvalue);
	
	if(n<=0)
		return;
	else if(n==1)	pView->m_SysParam->m_dBadAlarmMeter = atoi(strvalue);
	else if(n==2)		pView->m_SysParam->m_dBadAlarmMismatch = atoi(strvalue);
	else if(n==3)		pView->m_SysParam->m_nBadNgFrame = atoi(strvalue);
	else if(n==4)		pView->m_SysParam->m_nBadFrameInDefect = atoi(strvalue);
	else if(n==5)		pView->m_SysParam->m_nBadFrameInCount = atoi(strvalue);
	else if(n==6)		pView->m_SysParam->m_nContinueBadcnt = atoi(strvalue);
	else if(n==7)		pView->m_SysParam->m_nContinueBadFrame = atoi(strvalue);
	else if(n==10)		pView->m_SysParam->scale_x = atof(strvalue);
	else if(n==11)		pView->m_SysParam->scale_y = atof(strvalue);
	else if(n==12)		pView->m_SysParam->m_dTopBackDistance = dtmp;
	if(m_nLineAveFrame>10)m_nLineAveFrame = 10;

	UpdateData(FALSE);
}
//head 원본 이미지 + 핀홀 이미지

void CDlgInterface::OnBnClickedCkNewscale()
{//m_bNewScale
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();

	UpdateData();
	if(m_bNewScale==FALSE){
		pView->m_dLenthSum = 0;
		pView->m_nAlarmCnt = 0;
//		pView->m_dNewScaleX = scale_x;
		pDoc->m_data.m_dScaleFactorX[0]=pDoc->m_data.m_dScaleFactorX[1]=pDoc->m_data.m_dScaleFactorX[2]=scale_x;
	}
}

void CDlgInterface::OnEnSetfocusEditSysMismatchtol3()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	m_nSelectEdit = 33;
	pView->m_NumPad->LabelShow1(0,m_dMismatchTolMin1,m_dMismatchTolMax1);
	pView->m_NumPad->ShowWindow(1);

}

void CDlgInterface::OnEnSetfocusEditSysMismatchtol4()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	m_nSelectEdit = 34;
	pView->m_NumPad->LabelShow1(1,m_dMismatchTolMin1,m_dMismatchTolMax1);
	pView->m_NumPad->ShowWindow(1);
}

void CDlgInterface::OnBnClickedCheckEdgeinterpolation()
{//m_bEdgeInterpolation
	UpdateData();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgInterface::OnBnClickedCheckInsulate()
{//m_bInsulate
	UpdateData();
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	if(m_bInsulate){
		OnBnClickedButton11();
		pDoc->m_data.m_nCoatBright = m_nCoatBright;

	}
	else{
		OnBnClickedButton10();
		pDoc->m_data.m_nCoatBright = m_nCoatBrightDefault;
	}
	pView->m_bInsulateInspect = m_bInsulate;
	pDoc->m_data.m_bInsulateInspect = m_bInsulate;
	pView->UpdateData(FALSE);
}

void CDlgInterface::OnBnClickedCheckAging()
{//m_bAging
	UpdateData();
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();

	if(m_bAging){
		pView->KillTimer(1300);
		pView->SetTimer(20213,1000,NULL);


		CString strpath;
		strpath.Format("c:\\Glim\\Aging\\Cam%d.jpg",0);
		pDoc->m_pImage->Load(strpath);
		strpath.Format("c:\\Glim\\Aging\\Cam%d.jpg",1);
		pDoc->m_pImage1->Load(strpath);
		strpath.Format("c:\\Glim\\Aging\\Cam%d.jpg",2);
		pDoc->m_pImage2->Load(strpath);

	}
	else
	{
		pView->KillTimer(20213);
		pView->SetTimer(1300, 250, NULL);
		
	}
	
}

void CDlgInterface::OnEnSetfocusEditInsParam11()
{
	//절연 th value
	CVisWebView *pView = (CVisWebView*)m_pParent;
	pView->m_NumPad->m_nSelectControl = 35;
	pView->m_NumPad->LabelShow1(1,m_nInsulateTh,m_nInsulateTh);
	pView->m_NumPad->ShowWindow(1);

}

void CDlgInterface::OnBnClickedButton10()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;

	UpdateData();
	CString strCmd; 
	strCmd.Format(_T("LC%s"),m_strDefaultBright1);
	pView->m_cis->SendCmd(strCmd,0); 

	strCmd.Format(_T("Camera Response: %s,%s"),pView->m_cis->tCisRxData,m_strDefaultBright1);
	pView->AddtoList(strCmd, 0, 0);  
}

void CDlgInterface::OnBnClickedButton11()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;

	UpdateData();
	CString strCmd; 
	strCmd.Format(_T("LC%s"),m_strDefaultBright2);
	pView->m_cis->SendCmd(strCmd,0); 

	strCmd.Format(_T("Camera Response: %s,%s"),pView->m_cis->tCisRxData,m_strDefaultBright2);
	pView->AddtoList(strCmd, 0, 0);  
}

void CDlgInterface::ShowItem(int n1)
{
		GetDlgItem(IDC_CHECK_INSULATE)->ShowWindow(n1);

		GetDlgItem(IDC_EDIT_INS_PARAM11)->ShowWindow(n1);
		GetDlgItem(IDC_EDIT_INS_PARAMCOATBRIGHT)->ShowWindow(n1);
	
}
void CDlgInterface::OnBnClickedButtontest1()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	int nValue = 20;
	CString str1;
	str1.Format("%X",nValue);

	int  nDec = (int)strtol(str1, NULL, 16);
	return;
	double dq1 = pView->GetPrecisionTime();
	int nSum = 0,nc=0;
	for(int y=0;y<500;y++){
		for(int x=0;x<CAM_WIDTH_CIS*3;x++){
			nSum += *(pView->m_Inspect.m_FullImage+y*(CAM_WIDTH_CIS*3)+x);
			nc++;
		}
	}
	nSum/= nc;

	double dq2 = pView->GetPrecisionTime();

	double d33 = (dq2-dq1)*1000;

	return;
// 	CString str1,str2;
// 
// 	str1.Format("c:\\G.gg");
// 	str2.Format("c:\\Glim\\G.gg");
// 	MoveFile(str1,str2);
// 	return;
	BYTE * fm1 = pDoc->m_pImage->GetImagePtr();
	BYTE * fm2 = pDoc->m_pImage1->GetImagePtr();
	BYTE * fm3 = pDoc->m_pImage2->GetImagePtr();
	int nMag = 2;

	double dt1 = pView->GetPrecisionTime();
	pView->PreProcessing1(fm1,pView->m_Inspect.m_fmPreprocess[0],0,CAM_WIDTH_CIS,CAM_HEIGHT_3072,CRect(0,0,0,0),nMag);
	double dt2 = pView->GetPrecisionTime();
	pView->PreProcessing1(fm2,pView->m_Inspect.m_fmPreprocess[1],1,CAM_WIDTH_CIS,CAM_HEIGHT_3072,CRect(0,0,0,0),nMag);
	double dt3 = pView->GetPrecisionTime();
	pView->PreProcessing1(fm3,pView->m_Inspect.m_fmPreprocess[2],2,CAM_WIDTH_CIS,CAM_HEIGHT_3072,CRect(0,0,0,0),nMag);
	double dt4 = pView->GetPrecisionTime();

	BOOL btest = TRUE;
	//data 확인
	if(btest){
		int nidx1 = CAM_HEIGHT_3072/8;
		int dcount11 = 0;
		double *dWidth[MAX_CAMERAS][8];
		for(int k=0;k<3;k++){
			for(int i=0;i<8;i++){
				dWidth[k][i]=(double*)malloc(CAM_WIDTH_CIS*sizeof(double));//Split Image Projection Data
				for(int x=0;x<CAM_WIDTH_CIS;x++) dWidth[k][i][x]=0;
				dcount11 = 0;
				for(int y=nidx1*i;y<nidx1*(i+1);y+=2){
					for(int x=0;x<CAM_WIDTH_CIS;x++){
						dWidth[k][i][x] += *(pView->m_Inspect.m_fmPreprocess[k]+y*CAM_WIDTH_CIS+x);
					}
					dcount11++;
				}
				for(int x=0;x<CAM_WIDTH_CIS;x++){
					dWidth[k][i][x] /= dcount11;
//					TRACE("cam:%d,index:%d ,Xpos: %d , %.0f \n", k,i,x,dWidth[k][i][x]);
				}
				dcount11 = 0;

			}
		}



		for(int k=0;k<3;k++){
			for(int i=0;i<8;i++){
				if(dWidth[k][i]) free(dWidth[k][i]);
			}
		}

	}



	if(!m_bOriginImage){
		memcpy(fm1,pView->m_Inspect.m_fmPreprocess[0],CAM_WIDTH_CIS*CAM_HEIGHT_3072);
		memcpy(fm2,pView->m_Inspect.m_fmPreprocess[1],CAM_WIDTH_CIS*CAM_HEIGHT_3072);
		memcpy(fm3,pView->m_Inspect.m_fmPreprocess[2],CAM_WIDTH_CIS*CAM_HEIGHT_3072);
	}
	pView->DrawImage(3);

	CTime ttime = CTime::GetCurrentTime();
	CString strTime = ttime.Format("%H%M%S");
	CString str;
	str.Format("c:\\Glim\\Test\\Proj1_%s.jpg",strTime);
	pDoc->m_pImage->Save(str);
	str.Format("c:\\Glim\\Test\\Proj2_%s.jpg",strTime);
	pDoc->m_pImage1->Save(str);
	str.Format("c:\\Glim\\Test\\Proj3_%s.jpg",strTime);
	pDoc->m_pImage2->Save(str);
	str.Format("PF%.0f, %.0f, %.0f, %.0f",(dt4-dt1)*1000,(dt2-dt1)*1000,(dt3-dt2)*1000,(dt4-dt3)*1000);
	pView->AddtoInsLog(str);

}

void CDlgInterface::OnBnClickedButtontest2()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	BYTE * fm1 = pDoc->m_pImage->GetImagePtr();
	BYTE * fm2 = pDoc->m_pImage1->GetImagePtr();
	BYTE * fm3 = pDoc->m_pImage2->GetImagePtr();
	int nMag = 5;

	double dt1 = pView->GetPrecisionTime();
	pView->PreProcessing2(fm1,fm1,0,CAM_WIDTH_CIS,CAM_HEIGHT_3072,CRect(0,0,0,0),nMag);
	double dt2 = pView->GetPrecisionTime();
	pView->PreProcessing2(fm2,fm2,0,CAM_WIDTH_CIS,CAM_HEIGHT_3072,CRect(0,0,0,0),nMag);
	double dt3 = pView->GetPrecisionTime();
	pView->PreProcessing2(fm3,fm3,0,CAM_WIDTH_CIS,CAM_HEIGHT_3072,CRect(0,0,0,0),nMag);
	double dt4 = pView->GetPrecisionTime();

	pView->DrawImage(3);

	CTime ttime = CTime::GetCurrentTime();
	CString strTime = ttime.Format("%H%M%S");
	CString str;
	str.Format("c:\\Glim\\Test\\Diff1_%s.jpg",strTime);
	pDoc->m_pImage->Save(str);
	str.Format("c:\\Glim\\Test\\Diff2_%s.jpg",strTime);
	pDoc->m_pImage1->Save(str);
	str.Format("c:\\Glim\\Test\\Diff3_%s.jpg",strTime);
	pDoc->m_pImage2->Save(str);
	str.Format("DF%.0f, %.0f, %.0f, %.0f",(dt4-dt1)*1000,(dt2-dt1)*1000,(dt3-dt2)*1000,(dt4-dt3)*1000);
	pView->AddtoInsLog(str);

}

void CDlgInterface::OnBnClickedCheckEngKor()		//200129 kjh
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();

	UpdateData();

	if(m_bEngKor == ENG){			// 영어
		// setting
// 		GetDlgItem(IDC_STATIC_INTERFACE_GBOX_WIDTH_PARA)->SetWindowText(_T("Width Parameter"));
// 		GetDlgItem(IDC_STATIC_INTERFACE_COL_LEFTBASE)->SetWindowText(_T("Left Base"));
// 		GetDlgItem(IDC_CHECK_ALARM_OFF)->SetWindowText(_T("Alarm OFF"));


		GetDlgItem(IDC_INTER_STATIC_LC)->SetWindowText(_T("Insulate INSPECT"));
		GetDlgItem(IDC_INTER_STATIC_LC_1)->SetWindowText(_T("DEFAULT. LIGHT SET"));
		GetDlgItem(IDC_INTER_STATIC_LC_2)->SetWindowText(_T("Insulate LIGHT SET"));
		GetDlgItem(IDC_INTER_STATIC_LC_3)->SetWindowText(_T("COAT VALUE"));
		GetDlgItem(IDC_INTER_STATIC_LC_4)->SetWindowText(_T("COAT VALUE2"));
		GetDlgItem(IDC_INTER_STATIC_SKIP)->SetWindowText(_T("SKIP DIS."));
		GetDlgItem(IDC_INTER_STATIC_INS_1)->SetWindowText(_T("PINHOLE"));
		GetDlgItem(IDC_INTER_STATIC_INS_2)->SetWindowText(_T("ISLAND"));
		GetDlgItem(IDC_INTER_STATIC_INS_3)->SetWindowText(_T("SizeX"));
		GetDlgItem(IDC_INTER_STATIC_INS_4)->SetWindowText(_T("LINE"));
		GetDlgItem(IDC_INTER_STATIC_INS_5)->SetWindowText(_T("MAX WHITE"));
		GetDlgItem(IDC_INTER_STATIC_INS_6)->SetWindowText(_T("SKIP LINE"));
		GetDlgItem(IDC_INTER_STATIC_INS_7)->SetWindowText(_T("MIN LINE W(SIDE)"));
		GetDlgItem(IDC_INTER_STATIC_INS_8)->SetWindowText(_T("MIN LINE W(CEN)"));
		GetDlgItem(IDC_INTER_STATIC_INS_9)->SetWindowText(_T("LINE TH"));
		GetDlgItem(IDC_INTER_STATIC_INS_11)->SetWindowText(_T("LINE RATIO"));
		GetDlgItem(IDC_CHECK_AUTOBRIGHTNESS)->SetWindowText(_T("Auto Brightness"));
		GetDlgItem(IDC_STATIC_NONCOAT_BRIGHTNESS)->SetWindowText(_T("N-Coat Brightness"));
		GetDlgItem(IDC_STATIC_PRIMER_BRIGHTNESS)->SetWindowText(_T("PRIMER Brightness"));
		GetDlgItem(IDC_STATIC_LIGHT_TIME)->SetWindowText(_T("Light Time"));
		GetDlgItem(IDC_BUTTONLIGHTADJUST)->SetWindowText(_T("Apply"));
		

		GetDlgItem(IDC_CHECK_INSULATE)->SetWindowText(_T("Insulate INS."));
		GetDlgItem(IDC_BUTTON_NEWMODEL)->SetWindowText(_T("NEW MODEL"));
		GetDlgItem(IDC_BUTTON_SAVE_INI)->SetWindowText(_T("SAVE"));
		GetDlgItem(IDC_BUTTON8)->SetWindowText(_T("TEST"));
		GetDlgItem(IDC_BUTTON_PARAM_CLOSE)->SetWindowText(_T("CLOSE"));
		pView->GetDlgItem(IDC_BTN_GET_PROFILE)->ShowWindow(1);
		
		pView->InitControl();
		// main view
		pView->ChangeControlsLanguage(ENG);

		// dialog sysparam
		pView->m_SysParam->ChangeControlsLanguage(ENG);

		// numpad
		//pView->m_NumPad->


	}
	else if(m_bEngKor == KOR){		// 한글
		// setting
// 		GetDlgItem(IDC_STATIC_INTERFACE_GBOX_WIDTH_PARA)->SetWindowText(_T("기준 폭 파라미터"));
// 		GetDlgItem(IDC_STATIC_INTERFACE_COL_LEFTBASE)->SetWindowText(_T("좌측기준"));
// 		GetDlgItem(IDC_CHECK_ALARM_OFF)->SetWindowText(_T("알람 OFF"));
		GetDlgItem(IDC_INTER_STATIC_LC)->SetWindowText(_T("절연검사"));
		GetDlgItem(IDC_INTER_STATIC_LC_1)->SetWindowText(_T("DEFAULT 밝기 LC"));
		GetDlgItem(IDC_INTER_STATIC_LC_2)->SetWindowText(_T("절연 밝기    LC"));
		GetDlgItem(IDC_INTER_STATIC_LC_3)->SetWindowText(_T("코팅밝기1(절연)"));
		GetDlgItem(IDC_INTER_STATIC_LC_4)->SetWindowText(_T("코팅밝기2(절연)"));
		GetDlgItem(IDC_INTER_STATIC_SKIP)->SetWindowText(_T("스킵거리"));

		GetDlgItem(IDC_INTER_STATIC_INS_1)->SetWindowText(_T("핀홀"));
		GetDlgItem(IDC_INTER_STATIC_INS_2)->SetWindowText(_T("아일랜드"));
		GetDlgItem(IDC_INTER_STATIC_INS_3)->SetWindowText(_T("SizeX"));
		GetDlgItem(IDC_INTER_STATIC_INS_4)->SetWindowText(_T("라인"));
		GetDlgItem(IDC_INTER_STATIC_INS_5)->SetWindowText(_T("최대밝기"));
		GetDlgItem(IDC_INTER_STATIC_INS_6)->SetWindowText(_T("스킵라인"));
		GetDlgItem(IDC_INTER_STATIC_INS_7)->SetWindowText(_T("최소라인폭(좌우)"));
		GetDlgItem(IDC_INTER_STATIC_INS_8)->SetWindowText(_T("최소라인폭(중앙)"));
		GetDlgItem(IDC_INTER_STATIC_INS_9)->SetWindowText(_T("라인TH"));
		GetDlgItem(IDC_INTER_STATIC_INS_11)->SetWindowText(_T("라인비율"));
		GetDlgItem(IDC_CHECK_AUTOBRIGHTNESS)->SetWindowText(_T("자동 조명 밝기"));
		GetDlgItem(IDC_STATIC_NONCOAT_BRIGHTNESS)->SetWindowText(_T("무지밝기"));
		GetDlgItem(IDC_STATIC_PRIMER_BRIGHTNESS)->SetWindowText(_T("프라이머"));
		GetDlgItem(IDC_STATIC_LIGHT_TIME)->SetWindowText(_T("조명시간(일반)"));
		GetDlgItem(IDC_BUTTONLIGHTADJUST)->SetWindowText(_T("적용"));
		
		
		GetDlgItem(IDC_CHECK_INSULATE)->SetWindowText(_T("절연검사"));
		GetDlgItem(IDC_BUTTON_NEWMODEL)->SetWindowText(_T("새모델저장"));
		GetDlgItem(IDC_BUTTON_SAVE_INI)->SetWindowText(_T("모델저장"));
		GetDlgItem(IDC_BUTTON8)->SetWindowText(_T("테스트"));
		GetDlgItem(IDC_BUTTON_PARAM_CLOSE)->SetWindowText(_T("닫기"));
	

		// main view
		pView->InitControl();

		pView->ChangeControlsLanguage(KOR);
		pView->GetDlgItem(IDC_BTN_GET_PROFILE)->ShowWindow(0);

		// dialog sysparam
		pView->m_SysParam->ChangeControlsLanguage(KOR);
	}
}

//void CDlgInterface::OnEnChangeEditSysStandard1()
//{
//	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
//	// CDialog::OnInitDialog() 함수를 재지정 
//	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
//	// 이 알림 메시지를 보내지 않습니다.
//
//	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
//}

void CDlgInterface::OnBnClickedCheckPreprocessing()
{//m_bPreprocessing
	UpdateData();
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_data.m_bPreprocessing = m_bPreprocessing;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgInterface::OnBnClickedCheckOriginimage()
{//m_bOriginImage
	UpdateData();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgInterface::OnBnClickedCheckMasterpc()
{//m_bMasterPc
	UpdateData();
	CVisWebView *pView = (CVisWebView*)m_pParent;
	if(m_bMasterPc){
		pView->SetTimer(20213,1000,NULL);
		pView->KillTimer(1300);//plc read
		pView->KillTimer(20013);
	}
	else{
		pView->KillTimer(20213);
		pView->SetTimer(1300, 250, NULL);//plc read
		pView->SetTimer(20013,50,NULL);//chuck check core A or B
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgInterface::OnBnClickedCheckAutoedge()
{//m_bAutoEdge
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	UpdateData();
	pDoc->m_data.m_bAutoEdge = m_bAutoEdge;
	GetDlgItem(IDC_EDIT_INS_PARAM8)->ShowWindow(!m_bAutoEdge);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgInterface::OnBnClickedCheckLineaveragedata()
{//m_bLineAverageData
	UpdateData();
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_data.m_bLineAverageData = m_bLineAverageData;

}

void CDlgInterface::OnBnClickedCheckDrawdata()
{//m_bDrawData
	UpdateData();
	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgInterface::OnBnClickedCheckAvecoatbright()
{//m_bAutoCoatBrightness
	UpdateData();
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();

	pDoc->m_data.m_bAutoCoatBrightness = m_bAutoCoatBrightness;
	if(m_bAutoCoatBrightness){
		ShowHideButton(0);
	}
	else{
		ShowHideButton(1);
	}
}

void CDlgInterface::ShowHideButton(int nshow)
{
	//GetDlgItem(IDC_INTER_STATIC_LC_3)->ShowWindow(nshow);
	GetDlgItem(IDC_INTER_STATIC_LC_4)->ShowWindow(nshow);//
	//GetDlgItem(IDC_EDIT_INS_PARAMCOATBRIGHT)->ShowWindow(nshow);//
	GetDlgItem(IDC_EDIT_INS_PARAMCOATBRIGHT2)->ShowWindow(nshow);//
	GetDlgItem(IDC_EDIT_INS_PARAM8)->ShowWindow(!m_bAutoEdge);

}
void CDlgInterface::OnBnClickedButton12()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	if(pView->m_bAuto){//검사중
		pView->OnCheckAuto();
		Sleep(500);
		pDoc->m_pVision->Open1(CAM_WIDTH_CIS,CAM_HEIGHT_CIS);
		Sleep(1000);
		pView->OnCheckAuto();
	}
	else{
		Sleep(500);
		pDoc->m_pVision->Open1(CAM_WIDTH_CIS,CAM_HEIGHT_CIS);
		Sleep(500);
	}
	
}

void CDlgInterface::OnBnClickedCheckNoncoatpitch()
{//m_bNonCoatingPitch
	UpdateData();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgInterface::OnBnClickedCheckLastdata()
{//m_bLastData
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	UpdateData();
	if(m_bLastData){
		pView->m_DlgLastData->LastDataShow(pView->m_strLastNonCoatWidth,pView->m_strLastCoatWidth);
//		pView->m_DlgLastData->ShowWindow(1);
	}
	pView->GetDlgItem(IDC_BTN_WIDTH_DATA)->ShowWindow(m_bLastData);
}

void CDlgInterface::OnBnClickedCheckLanedraw()
{//m_bLaneDraw
	UpdateData();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgInterface::OnBnClickedButtonFolderinsp()
{//
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();

// 	pView->OffsetCheck();
// 	return;
	//
	pView->FolderInspect();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgInterface::OnBnClickedCheckAutoinsp1()
{//m_bAutoInsp

	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();
	pView->m_bAutoRun = m_bAutoInsp;

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgInterface::OnBnClickedCheckReturn()
{//m_nReturnTime //m_nReturnTime
	UpdateData();
	if(m_bReturnTime){
		GetDlgItem(IDC_EDIT_RETURNTIME)->EnableWindow(1);
		//m_nReturnTime
	}
	else
		GetDlgItem(IDC_EDIT_RETURNTIME)->EnableWindow(0);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgInterface::OnBnClickedCheckReversetest()
{//m_bReverseTest
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
}

void CDlgInterface::OnBnClickedCheckCylinder()
{//m_bCylinderCheck  m_nCylinderCutValue
	UpdateData();
	if(m_bCylinderCheck){//m_nCylinderCutValue
		GetDlgItem(IDC_EDIT_SHARPNESSVALUE)->EnableWindow(1);

	}
	else{
		GetDlgItem(IDC_EDIT_SHARPNESSVALUE)->EnableWindow(0);
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgInterface::OnBnClickedCheckPlcwrite()
{//m_bPlcWrite
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	UpdateData();
	if(m_bPlcWrite){
		pView->WriteShareMemorySpec();
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgInterface::OnBnClickedButtonMeterdata()
{//meterdata show
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();

	if(pView->m_pMeterData->IsWindowVisible()){
		pView->m_pMeterData->ShowWindow(SW_HIDE);
	}
	else{
		pView->m_pMeterData->ShowWindow(SW_SHOW);
	}
}

void CDlgInterface::OnEnSetfocusEditEdgeoffset()
{//m_dEdgeOffsetmm
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();//에지옵셋
	pView->m_NumPad->m_nSelectControl = 24;
	pView->m_NumPad->LabelShow2(0,param1,param1);
	pView->m_NumPad->ShowWindow(1);

}

void CDlgInterface::OnBnClickedCheckBinimage()
{//m_bBinImage
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	UpdateData();
	pView->m_Inspect.m_bBinImage = m_bBinImage;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgInterface::OnBnClickedCheckAutoreset()
{//m_bAutoReset
	UpdateData();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgInterface::OnBnClickedCheckPlcmodelsync1()
{//m_bPLCModelSync
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	UpdateData();
	pView->m_pModelDlg->GetDlgItem(IDC_EDIT_PRODUCT_PLC)->EnableWindow(m_bPLCModelSync);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgInterface::OnBnClickedCheckDatasend()
{//m_bServerDataSend
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();
	if(m_bServerDataSend){
		pView->SetTimer(23689,1000,NULL);//		WriteLotModel(m_strLotID);
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgInterface::OnBnClickedCheckSharpness()
{//m_bSharpness
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();
	if(m_bSharpness){
		//password 추가
		
		//Camera mode Change

		


	}
	pView->m_pDlgFullImage->ShowWindow(m_bSharpness);
}

void CDlgInterface::OnEnChangeEditInsParamcoatbright2()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgInterface::OnBnClickedButtonEdgeview()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc *pDoc = (CVisWebDoc*)pView->GetDocument();
	if(pView->m_ViewImage->IsWindowVisible()){
		pView->m_bEdgeView = FALSE;
		pView->m_ViewImage->ShowWindow(SW_HIDE);
	}
	else{
		pView->m_bEdgeView = TRUE;
		pView->m_ViewImage->ShowWindow(SW_SHOW);

	}
}

void CDlgInterface::OnBnClickedCheckAutobrightness()
{//m_nAutoBrightness  //m_bAutoBrightness
	UpdateData();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgInterface::OnBnClickedButtonlightadjust()
{//m_nLightOnTime

	CVisWebView *pView = (CVisWebView*)m_pParent;

	UpdateData();
	ChangeBrightness(m_nLightOnTime,0,60);

}

void CDlgInterface::ChangeBrightness(int nValue,int nMod,int nCommand)
{//m_nLightOnTime

	CVisWebView *pView = (CVisWebView*)m_pParent;

	CString strCmd,str; 
	//10진수 -> 16진수 
	str = pView->GetLightValue1(nValue,nMod);
	strCmd.Format(_T("LC%d%s"),nCommand,str);
	pView->m_cis->SendCmd(strCmd,1); 

	strCmd.Format(_T("Camera: %s,%s"),pView->m_cis->tCisRxData,str);
	pView->AddtoList(strCmd, 0, 0);  

}

// void CDlgInterface::LoadShutter()
// {
// 	CVisWebView *pView = (CVisWebView*)m_pParent;
// 	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
// 	CString str, str_name,strModelPath,strModel;//cis
// 	strModel = pDoc->m_data.m_strDefaultModel;//cis
// 	strModelPath.Format("%s%s.ini","c:\\Glim\\Model\\",strModel);//cis
// 
// 	str_name = ComputerName();
// 	str.Format("%s - System Parameter", str_name);		
// 	if(str_name.Find("OCH")>=0)strModelPath = PARAMETER_PATH;
// 	CIni ini( strModelPath, str, 1 );//cis
// 	//		CIni ini( PARAMETER_PATH, str, 1 );
// 	ini.SER_GETD(TRUE, m_nLightOnTime				, 16);
// 	
// }
// 
// void CDlgInterface::SaveShutter()
// {
// 	CVisWebView *pView = (CVisWebView*)m_pParent;
// 	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
// 	CString str, str_name,strModelPath,strModel;//cis
// 	strModel = pDoc->m_data.m_strDefaultModel;//cis
// 	strModelPath.Format("%s%s.ini","c:\\Glim\\Model\\",strModel);//cis
// 
// 	str_name = ComputerName();
// 	str.Format("%s - System Parameter", str_name);		
// 	if(str_name.Find("OCH")>=0)strModelPath = PARAMETER_PATH;
// 	CIni ini( strModelPath, str, 1 );//cis
// 	//		CIni ini( PARAMETER_PATH, str, 1 );
// 	ini.SER_GETD(FALSE, m_nLightOnTime				, 16);
// 
// }
void CDlgInterface::OnBnClickedCheckInspect1()
{//m_bInspect
	UpdateData();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgInterface::OnBnClickedCheckTestPlc()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
}


void CDlgInterface::SaveLightParam()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	CString str, str_name,strModelPath,strModel;//cis
	strModel = pDoc->m_data.m_strDefaultModel;//cis
	strModelPath.Format("%s.ini","c:\\Glim\\Model\\LightParam");//cis
	str_name = ComputerName();
	str.Format("%s - Light Parameter", str_name);


	CIni ini( strModelPath, str, 1 );//cis
	//	CIni ini( PARAMETER_PATH, str, 1 );//cis
	ini.SER_GETD(FALSE, m_nLightOnTime			, 15);//일반 밝기
	ini.SER_GETD(FALSE, m_nLightPrimer			, 22);//프라이머
//	ini.SER_GETD(FALSE, shutter					, 10);//세라믹

}

void CDlgInterface::LoadLightParam()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	CString str, str_name,strModelPath,strModel;//cis
	strModel = pDoc->m_data.m_strDefaultModel;//cis
	strModelPath.Format("%s.ini","c:\\Glim\\Model\\LightParam");//cis
	str_name = ComputerName();
	str.Format("%s - Light Parameter", str_name);


	CIni ini( strModelPath, str, 1 );//cis
	//	CIni ini( PARAMETER_PATH, str, 1 );//cis
	ini.SER_GETD(TRUE, m_nLightOnTime			, 15);//일반 밝기
	ini.SER_GETD(TRUE, m_nLightPrimer			, 22);//프라이머
	//	ini.SER_GETD(FALSE, shutter					, 10);//세라믹
}
void CDlgInterface::OnBnClickedCheckAutoinsp2()
{//m_bAutoSCInspect
	UpdateData();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

//20201016 kjh
void CDlgInterface::OnBnClickedCheckShowLog()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();

	UpdateData();

	pView->ShowLogControls(m_bShowLog);
}

BOOL CDlgInterface::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	InitControl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDlgInterface::InitControl()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();

	if(pView->m_strComputerName.Find(_T("CMI")) >= 0){
		GetDlgItem(IDC_CHECK_INSPECT1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHECK_PLCMODELSYNC1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHECK_PLCWRITE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHECK_AUTORESET)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHECK_BINIMAGE)->ShowWindow(SW_HIDE);	
		GetDlgItem(IDC_CHECK_AUTOINSP2)->ShowWindow(SW_HIDE);			
		
	}
}
