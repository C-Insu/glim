#pragma once
#include "afxwin.h"
#include "Label1.h"//m_lbLastData

// CDlgViewImage ��ȭ �����Դϴ�.

class CDlgViewImage : public CDialog
{
	DECLARE_DYNAMIC(CDlgViewImage)

public:
	CDlgViewImage(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgViewImage();
	CWnd*	m_pParent;
	void CDlgViewImage::DrawEdgeImage(int nCount);

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_EDGEVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonHide();
};
