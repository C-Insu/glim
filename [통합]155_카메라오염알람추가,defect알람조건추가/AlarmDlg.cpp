// AlarmDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "VisWeb.h"
#include "VisWebDoc.h"
#include "VisWebView.h"
#include "AlarmDlg.h"


// CAlarmDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAlarmDlg, CDialog)

CAlarmDlg::CAlarmDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAlarmDlg::IDD, pParent)
{
	m_pParent = pParent;
	m_pwndShow = NULL;

}

CAlarmDlg::~CAlarmDlg()
{
}

void CAlarmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_ALARMINFO, m_lAlarmMessage);
	DDX_Control(pDX, IDC_STATIC_ALARMINFO2, m_lAlarmMessage1);
}


BEGIN_MESSAGE_MAP(CAlarmDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CAlarmDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAlarmDlg 메시지 처리기입니다.

void CAlarmDlg::OnBnClickedOk()
{
	CVisWebView *pDlg = (CVisWebView*)m_pParent;

	pDlg->KillTimer(20219);
	ShowWindow(0);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	OnOK();
}




BOOL CAlarmDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	InitLabel();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CAlarmDlg::InitLabel()
{
	m_lAlarmMessage.SetTextColor(COLOR_GREEN);
	m_lAlarmMessage.SetBkColor(COLOR_RED);
	m_lAlarmMessage.SetFontBold(TRUE);
	m_lAlarmMessage.SetFontName("굴림");
	m_lAlarmMessage.SetFontSize(30);
	m_lAlarmMessage.SetText("Alarm");

	m_lAlarmMessage1.SetTextColor(COLOR_GREEN);
	m_lAlarmMessage1.SetBkColor(COLOR_RED);
	m_lAlarmMessage1.SetFontBold(TRUE);
	m_lAlarmMessage1.SetFontName("굴림");
	m_lAlarmMessage1.SetFontSize(30);
	m_lAlarmMessage1.SetText("Meter");

}

void CAlarmDlg::AlarmOn(int nFlag,CString msg)
{
	if(nFlag==0){
		m_lAlarmMessage.SetTextColor(COLOR_GREEN);
		m_lAlarmMessage.SetBkColor(COLOR_RED);
		m_lAlarmMessage.SetFontBold(TRUE);
		m_lAlarmMessage.SetFontName("굴림");
		m_lAlarmMessage.SetFontSize(50);
		m_lAlarmMessage.SetText(msg);

	}
	else{
		m_lAlarmMessage.SetTextColor(COLOR_RED);
		m_lAlarmMessage.SetBkColor(COLOR_GREEN);
		m_lAlarmMessage.SetFontBold(TRUE);
		m_lAlarmMessage.SetFontName("굴림");
		m_lAlarmMessage.SetFontSize(60);
		m_lAlarmMessage.SetText(msg);
	}
}

void CAlarmDlg::AlarmOn1(int nFlag,CString msg,CString msg1)
{
	if(nFlag==0){
		m_lAlarmMessage.SetTextColor(COLOR_GREEN);
		m_lAlarmMessage.SetBkColor(COLOR_RED);
		m_lAlarmMessage.SetFontBold(TRUE);
		m_lAlarmMessage.SetFontName("굴림");
		m_lAlarmMessage.SetFontSize(50);
		m_lAlarmMessage.SetText(msg);

		m_lAlarmMessage1.SetTextColor(COLOR_GREEN);
		m_lAlarmMessage1.SetBkColor(COLOR_RED);
		m_lAlarmMessage1.SetFontBold(TRUE);
		m_lAlarmMessage1.SetFontName("굴림");
		m_lAlarmMessage1.SetFontSize(50);
		m_lAlarmMessage1.SetText(msg1);
	}
	else{
		m_lAlarmMessage.SetTextColor(COLOR_RED);
		m_lAlarmMessage.SetBkColor(COLOR_GREEN);
		m_lAlarmMessage.SetFontBold(TRUE);
		m_lAlarmMessage.SetFontName("굴림");
		m_lAlarmMessage.SetFontSize(60);
		m_lAlarmMessage.SetText(msg);
		m_lAlarmMessage1.SetTextColor(COLOR_RED);
		m_lAlarmMessage1.SetBkColor(COLOR_GREEN);
		m_lAlarmMessage1.SetFontBold(TRUE);
		m_lAlarmMessage1.SetFontName("굴림");
		m_lAlarmMessage1.SetFontSize(60);
		m_lAlarmMessage1.SetText(msg1);
	}
}
