#pragma once
#include "afxwin.h"
#include "Label1.h"


// CAlarmDlg 대화 상자입니다.

class CAlarmDlg : public CDialog
{
	DECLARE_DYNAMIC(CAlarmDlg)

public:
	CAlarmDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	CWnd*	m_pParent;
	CWnd*	  m_pwndShow;

	void CAlarmDlg::InitLabel();
	void CAlarmDlg::AlarmOn(int nFlag,CString msg);
	void CAlarmDlg::AlarmOn1(int nFlag,CString msg,CString msg1);

	virtual ~CAlarmDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CLabel m_lAlarmMessage;
	CLabel m_lAlarmMessage1;
	virtual BOOL OnInitDialog();
};
