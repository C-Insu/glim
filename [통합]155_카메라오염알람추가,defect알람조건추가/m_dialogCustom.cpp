// m_dialogCustom.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "VisWeb.h"
#include "m_dialogCustom.h"


// m_dialogCustom ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(m_dialogCustom, CDialog)

m_dialogCustom::m_dialogCustom(CWnd* pParent /*=NULL*/)
	: CDialog(m_dialogCustom::IDD, pParent)
	, m_autoInsPath(_T(""))
{

}

m_dialogCustom::~m_dialogCustom()
{
}

void m_dialogCustom::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_AUTO_INS_PATH, m_autoInsPath);
}


BEGIN_MESSAGE_MAP(m_dialogCustom, CDialog)
	ON_BN_CLICKED(IDOK, &m_dialogCustom::OnBnClickedOk)
END_MESSAGE_MAP()


// m_dialogCustom �޽��� ó�����Դϴ�.

void m_dialogCustom::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnOK();
}
