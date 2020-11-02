// m_dialogCustom.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "VisWeb.h"
#include "m_dialogCustom.h"


// m_dialogCustom 대화 상자입니다.

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


// m_dialogCustom 메시지 처리기입니다.

void m_dialogCustom::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}
