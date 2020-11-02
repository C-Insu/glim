#pragma once
#include "afxwin.h"
#include "Label1.h"//m_lbLastData

// CDlgViewImage 대화 상자입니다.

class CDlgViewImage : public CDialog
{
	DECLARE_DYNAMIC(CDlgViewImage)

public:
	CDlgViewImage(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgViewImage();
	CWnd*	m_pParent;
	void CDlgViewImage::DrawEdgeImage(int nCount);

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_EDGEVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonHide();
};
