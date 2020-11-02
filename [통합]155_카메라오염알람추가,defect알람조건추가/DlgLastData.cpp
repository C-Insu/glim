// DlgLastData.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "VisWeb.h"
#include "VisWebDoc.h"
#include "VisWebView.h"
#include "DlgLastData.h"


// CDlgLastData 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgLastData, CDialog)

CDlgLastData::CDlgLastData(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLastData::IDD, pParent)
{

}

CDlgLastData::~CDlgLastData()
{
}

void CDlgLastData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_LASTDATA, m_lbLastData);
	DDX_Control(pDX, IDC_STATIC_LASTDATA2, m_lbLastData2);
}


BEGIN_MESSAGE_MAP(CDlgLastData, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgLastData::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDlgLastData 메시지 처리기입니다.

BOOL CDlgLastData::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	//ControlInit();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDlgLastData::ControlInit(int n)
{
	int nSize = 30;
	CString str;
	m_lbLastData.SetTextColor(RGB(153,51,153));
	if(n==0)//음극
		m_lbLastData.SetBkColor(COLOR_ORANGE1);
	else
		m_lbLastData.SetBkColor(COLOR_GRAY_WHITE1);
//		m_lbLastData.SetBkColor(RGB(102,151,151));

	m_lbLastData.SetFontName("휴먼둥근헤드라인");
	m_lbLastData.SetFontSize(nSize);
	str.Format("Last Data");
	m_lbLastData.SetText(str);

	m_lbLastData2.SetTextColor(RGB(255,255,204));
	m_lbLastData2.SetBkColor(COLOR_BLACK);
	m_lbLastData2.SetFontName("휴먼둥근헤드라인");
	m_lbLastData2.SetFontSize(nSize);
	str.Format("Last Data");
	m_lbLastData2.SetText(str);


}

void CDlgLastData::LastDataShow(CString msg1,CString msg2)
{
	m_lbLastData.SetText(msg1);
	m_lbLastData2.SetText(msg2);
}
void CDlgLastData::OnBnClickedButton1()
{
	ShowWindow(0);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
