#pragma once
#include "afxwin.h"


// CDlgCisCamera ��ȭ �����Դϴ�.

class CDlgCisCamera : public CDialog
{
	DECLARE_DYNAMIC(CDlgCisCamera)

public:
	CDlgCisCamera(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgCisCamera();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_CISCAMERA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonCishide();
	CStatic m_lbCISResult;
	CString m_strCisCommand;
};
