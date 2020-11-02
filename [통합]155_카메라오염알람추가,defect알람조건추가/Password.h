#pragma once

#include "afxwin.h"
#include "Label1.h"

// CPassword ��ȭ �����Դϴ�.

class CPassword : public CDialog
{
	DECLARE_DYNAMIC(CPassword)

public:
	CPassword(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	CWnd*	m_pParent;

	int		m_nbSelectNo;//0 �ʱ�ȭ  //1
	void ReadPassword();
	void WritePassword();
	CString	m_strReadPass;

	void CPassword::PasswordResult(int n);

	virtual ~CPassword();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_PASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonCheck3();
	afx_msg void OnBnClickedButtonCheck();
	afx_msg void OnBnClickedButtonCheck2();
	BOOL m_bModifyPass;
	afx_msg void OnBnClickedCheckModifypass();
	CString m_strPassword1;
	CString m_strPassword2;
	CString m_strPassword3;
	CString m_strPassword4;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonCheck4();
	CLabel m_lbPasswordResult;
	afx_msg void OnEnSetfocusEditPass2();
	afx_msg void OnEnSetfocusEditPass1();
	afx_msg void OnEnSetfocusEditPass3();
	afx_msg void OnEnSetfocusEditPass4();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
