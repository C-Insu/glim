// DlgViewImage.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "VisWeb.h"
#include "VisWebDoc.h"
#include "VisWebView.h"
#include "DlgViewImage.h"


// CDlgViewImage 대화 상자입니다.

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


// CDlgViewImage 메시지 처리기입니다.

BOOL CDlgViewImage::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
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
	//전체화면 이미지 사이즈
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

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
