#pragma once
#include "afxwin.h"
#include "Label1.h"//m_lbLastData


// CDlgLastData ��ȭ �����Դϴ�.

class CDlgLastData : public CDialog
{
	DECLARE_DYNAMIC(CDlgLastData)

public:
	CDlgLastData(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgLastData();

	void CDlgLastData::ControlInit(int n);
	void CDlgLastData::LastDataShow(CString msg,CString msg2);

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOGLASTDATA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CLabel m_lbLastData;
	virtual BOOL OnInitDialog();
	CLabel m_lbLastData2;
	afx_msg void OnBnClickedButton1();
};
