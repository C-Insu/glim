// DlgLastData.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "VisWeb.h"
#include "VisWebDoc.h"
#include "VisWebView.h"
#include "DlgLastData.h"


// CDlgLastData ��ȭ �����Դϴ�.

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


// CDlgLastData �޽��� ó�����Դϴ�.

BOOL CDlgLastData::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	//ControlInit();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CDlgLastData::ControlInit(int n)
{
	int nSize = 30;
	CString str;
	m_lbLastData.SetTextColor(RGB(153,51,153));
	if(n==0)//����
		m_lbLastData.SetBkColor(COLOR_ORANGE1);
	else
		m_lbLastData.SetBkColor(COLOR_GRAY_WHITE1);
//		m_lbLastData.SetBkColor(RGB(102,151,151));

	m_lbLastData.SetFontName("�޸յձ�������");
	m_lbLastData.SetFontSize(nSize);
	str.Format("Last Data");
	m_lbLastData.SetText(str);

	m_lbLastData2.SetTextColor(RGB(255,255,204));
	m_lbLastData2.SetBkColor(COLOR_BLACK);
	m_lbLastData2.SetFontName("�޸յձ�������");
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
