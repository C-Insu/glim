#pragma once
#include "afxwin.h"
#include "Label1.h"//m_lbLastData


// CDlgFullImage ��ȭ �����Դϴ�.

class CDlgFullImage : public CDialog
{
	DECLARE_DYNAMIC(CDlgFullImage)

public:
	CDlgFullImage(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgFullImage();

	CWnd*	m_pParent;
	int		DrawMagImage(int nCam);
	CImage * m_pMagImage[MAX_CAMERAS];

	double	m_dSharpness[MAX_CAMERAS];

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_FULLIMAGE1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonFullimageclose();
	virtual BOOL OnInitDialog();
};
