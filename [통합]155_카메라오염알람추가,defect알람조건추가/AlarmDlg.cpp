// AlarmDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "VisWeb.h"
#include "VisWebDoc.h"
#include "VisWebView.h"
#include "AlarmDlg.h"


// CAlarmDlg ��ȭ �����Դϴ�.

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


// CAlarmDlg �޽��� ó�����Դϴ�.

void CAlarmDlg::OnBnClickedOk()
{
	CVisWebView *pDlg = (CVisWebView*)m_pParent;

	pDlg->KillTimer(20219);
	ShowWindow(0);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
//	OnOK();
}




BOOL CAlarmDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	InitLabel();
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CAlarmDlg::InitLabel()
{
	m_lAlarmMessage.SetTextColor(COLOR_GREEN);
	m_lAlarmMessage.SetBkColor(COLOR_RED);
	m_lAlarmMessage.SetFontBold(TRUE);
	m_lAlarmMessage.SetFontName("����");
	m_lAlarmMessage.SetFontSize(30);
	m_lAlarmMessage.SetText("Alarm");

	m_lAlarmMessage1.SetTextColor(COLOR_GREEN);
	m_lAlarmMessage1.SetBkColor(COLOR_RED);
	m_lAlarmMessage1.SetFontBold(TRUE);
	m_lAlarmMessage1.SetFontName("����");
	m_lAlarmMessage1.SetFontSize(30);
	m_lAlarmMessage1.SetText("Meter");

}

void CAlarmDlg::AlarmOn(int nFlag,CString msg)
{
	if(nFlag==0){
		m_lAlarmMessage.SetTextColor(COLOR_GREEN);
		m_lAlarmMessage.SetBkColor(COLOR_RED);
		m_lAlarmMessage.SetFontBold(TRUE);
		m_lAlarmMessage.SetFontName("����");
		m_lAlarmMessage.SetFontSize(50);
		m_lAlarmMessage.SetText(msg);

	}
	else{
		m_lAlarmMessage.SetTextColor(COLOR_RED);
		m_lAlarmMessage.SetBkColor(COLOR_GREEN);
		m_lAlarmMessage.SetFontBold(TRUE);
		m_lAlarmMessage.SetFontName("����");
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
		m_lAlarmMessage.SetFontName("����");
		m_lAlarmMessage.SetFontSize(50);
		m_lAlarmMessage.SetText(msg);

		m_lAlarmMessage1.SetTextColor(COLOR_GREEN);
		m_lAlarmMessage1.SetBkColor(COLOR_RED);
		m_lAlarmMessage1.SetFontBold(TRUE);
		m_lAlarmMessage1.SetFontName("����");
		m_lAlarmMessage1.SetFontSize(50);
		m_lAlarmMessage1.SetText(msg1);
	}
	else{
		m_lAlarmMessage.SetTextColor(COLOR_RED);
		m_lAlarmMessage.SetBkColor(COLOR_GREEN);
		m_lAlarmMessage.SetFontBold(TRUE);
		m_lAlarmMessage.SetFontName("����");
		m_lAlarmMessage.SetFontSize(60);
		m_lAlarmMessage.SetText(msg);
		m_lAlarmMessage1.SetTextColor(COLOR_RED);
		m_lAlarmMessage1.SetBkColor(COLOR_GREEN);
		m_lAlarmMessage1.SetFontBold(TRUE);
		m_lAlarmMessage1.SetFontName("����");
		m_lAlarmMessage1.SetFontSize(60);
		m_lAlarmMessage1.SetText(msg1);
	}
}
