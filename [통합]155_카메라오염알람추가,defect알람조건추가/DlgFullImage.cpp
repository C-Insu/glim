// DlgFullImage.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "VisWeb.h"
#include "VisWebDoc.h"
#include "VisWebView.h"
#include "Image.h"
#include "DlgFullImage.h"


// CDlgFullImage ��ȭ �����Դϴ�.

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


// CDlgFullImage �޽��� ó�����Դϴ�.

void CDlgFullImage::OnBnClickedButtonFullimageclose()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
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
	// 	m_Bitmap.DeleteObject(); //������ ������
	// 	m_Bitmap.CreateCompatibleBitmap(pDC, rtdraw.Width(), rtdraw.Height()); //���� �������
	// 	memDC.CreateCompatibleDC(pDC); //memDC�� ���� �������
	// 	pOldBmp = memDC.SelectObject(&m_Bitmap); //memDC�� ��Ʈ�� ����



	CRect rcMain;
	GetWindowRect(rcMain);
	//��üȭ�� �̹��� ������
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
			m_pMagImage[0]->Draw(pDC->m_hDC,&rcDIB,&rcDest);//1�� 
			m_pMagImage[2]->Draw(pDC->m_hDC,&rcDIB,&rcDest1);//3��

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