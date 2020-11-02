#pragma once
#include "afxwin.h"
#include "Label1.h"//m_lbLastData


// CDlgLastData 대화 상자입니다.

class CDlgLastData : public CDialog
{
	DECLARE_DYNAMIC(CDlgLastData)

public:
	CDlgLastData(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgLastData();

	void CDlgLastData::ControlInit(int n);
	void CDlgLastData::LastDataShow(CString msg,CString msg2);

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOGLASTDATA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CLabel m_lbLastData;
	virtual BOOL OnInitDialog();
	CLabel m_lbLastData2;
	afx_msg void OnBnClickedButton1();
};
