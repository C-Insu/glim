
#pragma once
#include "label1.h"
#include "afxwin.h"



// CDlgMeterData ��ȭ �����Դϴ�.

class CDlgMeterData : public CDialog
{
	DECLARE_DYNAMIC(CDlgMeterData)

public:
	CDlgMeterData(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgMeterData();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_METERDATA };
	CWnd*	m_pParent;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CLabel m_lbMeterData[10];
};
