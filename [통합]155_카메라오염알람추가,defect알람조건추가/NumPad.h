#pragma once
#include "afxwin.h"
#include "Label1.h"//m_lbLastData


// CNumPad ��ȭ �����Դϴ�.

class CNumPad : public CDialog
{
	DECLARE_DYNAMIC(CNumPad)

public:
	CNumPad(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	CWnd*	m_pParent;
	CWnd*	  m_pwndShow;

	CString m_strNum;
	void CNumPad::LabelInit();
	void CNumPad::LabelShow(int nStand,double dmin,double dmax);
	void CNumPad::LabelShow1(int nStand,double dmin,double dmax);
	void CNumPad::LabelShow2(int nStand,double dmin,double dmax);;//�Ϲ� �� �Է�

	void ChangeControlsLanguage(BOOL bLan);

	int m_nSelectControl;//parameter�� select
	CString	m_strResult;


	virtual ~CNumPad();


// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_KEYPAD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonNum1();
	afx_msg void OnBnClickedButtonNum2();
	afx_msg void OnBnClickedButtonNum3();
	afx_msg void OnBnClickedButtonNum4();
	afx_msg void OnBnClickedButtonNum5();
	afx_msg void OnBnClickedButtonNum6();
	afx_msg void OnBnClickedButtonNum7();
	afx_msg void OnBnClickedButtonNum8();
	afx_msg void OnBnClickedButtonNum9();
	afx_msg void OnBnClickedButtonNum10();
	afx_msg void OnBnClickedButtonNumplus();
	afx_msg void OnBnClickedButtonNumminus();
	afx_msg void OnBnClickedButtonNumplus2();
	afx_msg void OnBnClickedButtonNumplus3();
	CString m_strNumDisplay;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonNumclose();
	afx_msg void OnBnClickedButtonNumdot();
	BOOL m_bStandard;
	BOOL m_bTol1;
	afx_msg void OnBnClickedCheckStandard();
	afx_msg void OnBnClickedCheckTol1();
	CLabel m_lbDispStand;
	CLabel m_lbDispMin;
	CLabel m_lbDispMax;
};
