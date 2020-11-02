// DlgViewImage.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "VisWeb.h"
#include "VisWebDoc.h"
#include "VisWebView.h"
#include "DlgViewImage.h"


// CDlgViewImage ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDlgViewImage, CDialog)

CDlgViewImage::CDlgViewImage(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgViewImage::IDD, pParent)
{
	m_pParent = pParent;

}

CDlgViewImage::~CDlgViewImage()
{
}

void CDlgViewImage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgViewImage, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_HIDE, &CDlgViewImage::OnBnClickedButtonHide)
END_MESSAGE_MAP()


// CDlgViewImage �޽��� ó�����Դϴ�.

BOOL CDlgViewImage::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CDlgViewImage::DrawEdgeImage(int nCount)
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	CDC* pDC = GetDC();
	CString strTmp;
	CRect rcDIB, rcDest[10];
	CRect rcMain;
	GetWindowRect(rcMain);
	//��üȭ�� �̹��� ������
	for(int i=0;i<nCount && i<10;i++){
		GetDlgItem(IDC_STATIC_EDGEVIIEW1+i)->GetWindowRect(rcDest[i]);
		rcDest[i].OffsetRect(-rcMain.left-4,-rcMain.top-25);	

		rcDIB.top = 0;
		rcDIB.left = 0;
		rcDIB.right = EDGE_IMG_WIDTH;
		rcDIB.bottom = EDGE_IMG_HEIGHT;

		pView->m_fmEdgeVew[i]->Draw(pDC->m_hDC,rcDIB,&rcDest[i]);

	}

	ReleaseDC(pDC);

}
void CDlgViewImage::OnBnClickedButtonHide()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;

	pView->m_bEdgeView = FALSE;
	ShowWindow(SW_HIDE);

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
