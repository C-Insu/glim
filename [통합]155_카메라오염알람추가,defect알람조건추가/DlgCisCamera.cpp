// DlgCisCamera.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "VisWeb.h"
#include "DlgCisCamera.h"


// CDlgCisCamera ��ȭ �����Դϴ�.

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


// CDlgCisCamera �޽��� ó�����Դϴ�.

void CDlgCisCamera::OnBnClickedButton1()
{//m_strCisCommand
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CDlgCisCamera::OnBnClickedButtonCishide()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
