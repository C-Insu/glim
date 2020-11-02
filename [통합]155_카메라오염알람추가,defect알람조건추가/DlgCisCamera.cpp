// DlgCisCamera.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "VisWeb.h"
#include "DlgCisCamera.h"


// CDlgCisCamera 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgCisCamera, CDialog)

CDlgCisCamera::CDlgCisCamera(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCisCamera::IDD, pParent)
	, m_strCisCommand(_T(""))
{

}

CDlgCisCamera::~CDlgCisCamera()
{
}

void CDlgCisCamera::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_CISRESULT, m_lbCISResult);
	DDX_Text(pDX, IDC_EDIT_CISCMAAND, m_strCisCommand);
}


BEGIN_MESSAGE_MAP(CDlgCisCamera, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgCisCamera::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_CISHIDE, &CDlgCisCamera::OnBnClickedButtonCishide)
END_MESSAGE_MAP()


// CDlgCisCamera 메시지 처리기입니다.

void CDlgCisCamera::OnBnClickedButton1()
{//m_strCisCommand
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgCisCamera::OnBnClickedButtonCishide()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
