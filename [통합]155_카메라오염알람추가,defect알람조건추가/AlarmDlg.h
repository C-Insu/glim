#pragma once
#include "afxwin.h"
#include "Label1.h"


// CAlarmDlg ��ȭ �����Դϴ�.

class CAlarmDlg : public CDialog
{
	DECLARE_DYNAMIC(CAlarmDlg)

public:
	CAlarmDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	CWnd*	m_pParent;
	CWnd*	  m_pwndShow;

	void CAlarmDlg::InitLabel();
	void CAlarmDlg::AlarmOn(int nFlag,CString msg);
	void CAlarmDlg::AlarmOn1(int nFlag,CString msg,CString msg1);

	virtual ~CAlarmDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CLabel m_lAlarmMessage;
	CLabel m_lAlarmMessage1;
	virtual BOOL OnInitDialog();
};
