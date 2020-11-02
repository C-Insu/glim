
#pragma once
#include "label1.h"
#include "afxwin.h"



// CDlgMeterData 대화 상자입니다.

class CDlgMeterData : public CDialog
{
	DECLARE_DYNAMIC(CDlgMeterData)

public:
	CDlgMeterData(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgMeterData();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_METERDATA };
	CWnd*	m_pParent;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CLabel m_lbMeterData[10];
};
