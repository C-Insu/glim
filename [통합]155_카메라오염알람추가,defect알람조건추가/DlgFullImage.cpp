// DlgFullImage.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "VisWeb.h"
#include "VisWebDoc.h"
#include "VisWebView.h"
#include "Image.h"
#include "DlgFullImage.h"


// CDlgFullImage 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgFullImage, CDialog)

CDlgFullImage::CDlgFullImage(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFullImage::IDD, pParent)
{
	m_pParent = pParent;

	for(int i=0;i<MAX_CAMERAS;i++){
		m_pMagImage[i] = NULL;
		m_dSharpness[i] = 0;
	}

}

CDlgFullImage::~CDlgFullImage()
{
}

void CDlgFullImage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgFullImage, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FULLIMAGECLOSE, &CDlgFullImage::OnBnClickedButtonFullimageclose)
END_MESSAGE_MAP()


// CDlgFullImage 메시지 처리기입니다.

void CDlgFullImage::OnBnClickedButtonFullimageclose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//m_bSharpness
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	pDoc->m_pDlgInterface->m_bSharpness = FALSE;
	pDoc->m_pDlgInterface->UpdateData(FALSE);
	ShowWindow(0);
}

BOOL CDlgFullImage::OnInitDialog()
{
	CDialog::OnInitDialog();

	for(int i=0;i<MAX_CAMERAS;i++){
		m_pMagImage[i] = new CImage();
		m_pMagImage[i]->Create(MAGIMAGE_X,MAGIMAGE_Y,8);
		m_pMagImage[i]->m_nWidth = BAD_IMG_WIDTH;
		m_pMagImage[i]->m_nHeight = BAD_IMG_HEIGHT;
		m_pMagImage[i]->InitDIB();
		memset(m_pMagImage[i]->GetImagePtr(),0,MAGIMAGE_X*MAGIMAGE_Y);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

int CDlgFullImage::DrawMagImage(int nCam)
{

	CString strTmp;
	CRect rcDIB, rcDest,rcDest1,rcDest2;


	CDC* pDC = GetDC();

	// 	CBitmap* pOldBmp; //oldbmp
	// 	CRect rtdraw;
	// 	rtdraw.SetRect(0,0,1920,1080);
	// 	CDC memDC;
	// 	m_Bitmap.DeleteObject(); //기존꺼 지워줌
	// 	m_Bitmap.CreateCompatibleBitmap(pDC, rtdraw.Width(), rtdraw.Height()); //새로 만들어줌
	// 	memDC.CreateCompatibleDC(pDC); //memDC도 새로 만들어줌
	// 	pOldBmp = memDC.SelectObject(&m_Bitmap); //memDC의 비트맵 선택



	CRect rcMain;
	GetWindowRect(rcMain);
	//전체화면 이미지 사이즈
	GetDlgItem(IDC_STATIC_FULLCAM1)->GetWindowRect(rcDest);
	GetDlgItem(IDC_STATIC_FULLCAM2)->GetWindowRect(rcDest1);

	rcDest.OffsetRect(-rcMain.left-4,-rcMain.top-25);	
	rcDest1.OffsetRect(-rcMain.left-4,-rcMain.top-25);	

	if(!m_pMagImage[0]->IsDataNull())
	{		
		rcDIB.top = 0;
		rcDIB.left = 0;
		rcDIB.right = MAGIMAGE_X;
		rcDIB.bottom = MAGIMAGE_Y;

		if(nCam==3){
			m_pMagImage[0]->Draw(pDC->m_hDC,&rcDIB,&rcDest);//1번 
			m_pMagImage[2]->Draw(pDC->m_hDC,&rcDIB,&rcDest1);//3번

		}
		else{
			m_pMagImage[nCam]->Draw(pDC->m_hDC,&rcDIB,&rcDest);
		}
	}

	//draw text
	CPoint pt;
	CString str;
	str.Format("Sharpness1 : %.1f",m_dSharpness[0]);
	pt.SetPoint(50,100);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,0));
	pDC->TextOut(pt.x,pt.y,str);
	str.Format("Sharpness2 : %.1f",m_dSharpness[2]);
	pt.SetPoint(50,300);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,0));
	pDC->TextOut(pt.x,pt.y,str);

// 	m_dSharpness[0] = dsharp1;
// 	m_dSharpness[2] = dsharp2;


	ReleaseDC(pDC);
	return 0;
}