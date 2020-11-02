#pragma once
#include "afxwin.h"
#include "Label1.h"//m_lbLastData


// CDlgFullImage 대화 상자입니다.

class CDlgFullImage : public CDialog
{
	DECLARE_DYNAMIC(CDlgFullImage)

public:
	CDlgFullImage(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgFullImage();

	CWnd*	m_pParent;
	int		DrawMagImage(int nCam);
	CImage * m_pMagImage[MAX_CAMERAS];

	double	m_dSharpness[MAX_CAMERAS];

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_FULLIMAGE1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonFullimageclose();
	virtual BOOL OnInitDialog();
};
