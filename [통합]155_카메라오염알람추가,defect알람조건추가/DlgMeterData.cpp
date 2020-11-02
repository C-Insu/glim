// DlgMeterData.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "VisWeb.h"
#include "VisWebDoc.h"
#include "VisWebView.h"
#include "DlgMeterData.h"


// CDlgMeterData 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgMeterData, CDialog)

CDlgMeterData::CDlgMeterData(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMeterData::IDD, pParent)
{
	m_pParent = pParent;

}

CDlgMeterData::~CDlgMeterData()
{
}

void CDlgMeterData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_METER1, m_lbMeterData[0]);
	DDX_Control(pDX, IDC_STATIC_METER2, m_lbMeterData[1]);
	DDX_Control(pDX, IDC_STATIC_METER3, m_lbMeterData[2]);
	DDX_Control(pDX, IDC_STATIC_METER4, m_lbMeterData[3]);
	DDX_Control(pDX, IDC_STATIC_METER5, m_lbMeterData[4]);
	DDX_Control(pDX, IDC_STATIC_METER6, m_lbMeterData[5]);
	DDX_Control(pDX, IDC_STATIC_METER7, m_lbMeterData[6]);
	DDX_Control(pDX, IDC_STATIC_METER8, m_lbMeterData[7]);
	DDX_Control(pDX, IDC_STATIC_METER9, m_lbMeterData[8]);
	DDX_Control(pDX, IDC_STATIC_METER10, m_lbMeterData[9]);
}


BEGIN_MESSAGE_MAP(CDlgMeterData, CDialog)
END_MESSAGE_MAP()


// CDlgMeterData 메시지 처리기입니다.
