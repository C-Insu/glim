#pragma once
#include "afxwin.h"
#include "Label1.h"
#include "afxcmn.h"

// CModelDlg 대화 상자입니다.

class CModelDlg : public CDialog
{
	DECLARE_DYNAMIC(CModelDlg)

public:
	CModelDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.

	CWnd*	m_pParent;
	int CModelDlg::DirFileCount(char *pDirName);
	CString	m_strModelNo;
	CString m_strProductPLC;
	CString m_strModelName;
//	CString m_strSelectProduct;

	virtual ~CModelDlg();
	void UpdateDataManual(BOOL bSave);

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_MODEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_pList;
	CString m_strSelectProduct;
	afx_msg void OnBnClickedButtonRefresh();
	afx_msg void OnBnClickedButtonSelectTab1();
	afx_msg void OnBnClickedButtonDeleteTab1();
	CString m_strProductName;
	CString m_strProductName2;
	afx_msg void OnBnClickedButtonProdcutTab1();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
//	afx_msg void OnNMThemeChangedStaticProduct01Tab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListProductTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnSetfocusEditProductName();
	afx_msg void OnEnChangeEditProductName();
	afx_msg void OnEnSetfocusEditProductName2();
};
