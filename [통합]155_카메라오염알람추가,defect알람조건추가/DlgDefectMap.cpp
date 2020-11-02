// DlgDefectMap.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "VisWeb.h"
#include "VisWebDoc.h"
#include "VisWebView.h"
#include "DlgDefectMap.h"

extern void DrawBMP(LPCTSTR lpszFileName, CDC *pDC, int nX, int nY, DWORD dwRop);


// CDlgDefectMap 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgDefectMap, CDialog)

CDlgDefectMap::CDlgDefectMap(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDefectMap::IDD, pParent)
	, m_bAlarmOff(FALSE)
{
//	m_vMain = pParent;
	m_nID = CDlgDefectMap::IDD;

	for(int i=0;i<2;i++)
		m_nLintTB[i][0] = m_nLintTB[i][1] = 0;

	m_pParent = pParent;
	m_pwndShow = NULL;

	m_bRedrawTime = TRUE;
	m_nPosCount = 6;

	m_bSim1 = FALSE;
	m_nTitleSize = 60;

	for(int i=0; i<CELLCNT; i++){
		m_dCellPos[i] = 0;
		m_dCellWidth[i] = 0;

	}
	for(int i=0;i<MAX_LENGTH;i++){
// 		m_lbMismatchLength[i].SetText("");
// 		m_lbTopLength[i].SetText("");
// 		m_lbBackLength[i].SetText("");
	}

}

CDlgDefectMap::~CDlgDefectMap()
{
}

void CDlgDefectMap::DoDataExchange(CDataExchange* pDX)
{

	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_MISMATCHTITLE, m_lbMismatchTitle);
	DDX_Control(pDX, IDC_STATIC_MISMATCHTITLE2, m_lbMismatchTitle1[0]);
	DDX_Control(pDX, IDC_STATIC_MISMATCHTITLE3, m_lbMismatchTitle1[1]);
	DDX_Control(pDX, IDC_STATIC_MISMATCHTITLE4, m_lbMismatchTitle1[2]);
	DDX_Control(pDX, IDC_STATIC_MISMATCHTITLE5, m_lbGapTitle);

	DDX_Control(pDX, IDC_STATIC_TOPBACKLENTH1, m_lbTopBackLenth[0]);
	DDX_Control(pDX, IDC_STATIC_TOPBACKLENTH2, m_lbTopBackLenth[1]);

	//Mismatch length 20ea
	DDX_Control(pDX, IDC_STATIC_PITCH1, m_lbMismatchLength[0]);
	DDX_Control(pDX, IDC_STATIC_PITCH2, m_lbMismatchLength[1]);
	DDX_Control(pDX, IDC_STATIC_PITCH3, m_lbMismatchLength[2]);
	DDX_Control(pDX, IDC_STATIC_PITCH4, m_lbMismatchLength[3]);
	DDX_Control(pDX, IDC_STATIC_PITCH5, m_lbMismatchLength[4]);
	DDX_Control(pDX, IDC_STATIC_PITCH6, m_lbMismatchLength[5]);
	DDX_Control(pDX, IDC_STATIC_PITCH7, m_lbMismatchLength[6]);
	DDX_Control(pDX, IDC_STATIC_PITCH8, m_lbMismatchLength[7]);
	DDX_Control(pDX, IDC_STATIC_PITCH9, m_lbMismatchLength[8]);
	DDX_Control(pDX, IDC_STATIC_PITCH10, m_lbMismatchLength[9]);
	DDX_Control(pDX, IDC_STATIC_PITCH11, m_lbMismatchLength[10]);
	DDX_Control(pDX, IDC_STATIC_PITCH12, m_lbMismatchLength[11]);
	DDX_Control(pDX, IDC_STATIC_PITCH13, m_lbMismatchLength[12]);
	DDX_Control(pDX, IDC_STATIC_PITCH14, m_lbMismatchLength[13]);
	DDX_Control(pDX, IDC_STATIC_PITCH15, m_lbMismatchLength[14]);
	DDX_Control(pDX, IDC_STATIC_PITCH16, m_lbMismatchLength[15]);
	DDX_Control(pDX, IDC_STATIC_PITCH17, m_lbMismatchLength[16]);
	DDX_Control(pDX, IDC_STATIC_PITCH18, m_lbMismatchLength[17]);
	DDX_Control(pDX, IDC_STATIC_PITCH19, m_lbMismatchLength[18]);
	DDX_Control(pDX, IDC_STATIC_PITCH20, m_lbMismatchLength[19]);
	///Top Pith length 20ea
	DDX_Control(pDX, IDC_STATIC_PITCH21, m_lbTopLength[0]);
	DDX_Control(pDX, IDC_STATIC_PITCH22, m_lbTopLength[1]);
	DDX_Control(pDX, IDC_STATIC_PITCH23, m_lbTopLength[2]);
	DDX_Control(pDX, IDC_STATIC_PITCH24, m_lbTopLength[3]);
	DDX_Control(pDX, IDC_STATIC_PITCH25, m_lbTopLength[4]);
	DDX_Control(pDX, IDC_STATIC_PITCH26, m_lbTopLength[5]);
	DDX_Control(pDX, IDC_STATIC_PITCH27, m_lbTopLength[6]);
	DDX_Control(pDX, IDC_STATIC_PITCH28, m_lbTopLength[7]);
	DDX_Control(pDX, IDC_STATIC_PITCH29, m_lbTopLength[8]);
	DDX_Control(pDX, IDC_STATIC_PITCH30, m_lbTopLength[9]);
	DDX_Control(pDX, IDC_STATIC_PITCH31, m_lbTopLength[10]);
	DDX_Control(pDX, IDC_STATIC_PITCH32, m_lbTopLength[11]);
	DDX_Control(pDX, IDC_STATIC_PITCH33, m_lbTopLength[12]);
	DDX_Control(pDX, IDC_STATIC_PITCH34, m_lbTopLength[13]);
	DDX_Control(pDX, IDC_STATIC_PITCH35, m_lbTopLength[14]);
	DDX_Control(pDX, IDC_STATIC_PITCH36, m_lbTopLength[15]);
	DDX_Control(pDX, IDC_STATIC_PITCH37, m_lbTopLength[16]);
	DDX_Control(pDX, IDC_STATIC_PITCH38, m_lbTopLength[17]);
	DDX_Control(pDX, IDC_STATIC_PITCH39, m_lbTopLength[18]);
	DDX_Control(pDX, IDC_STATIC_PITCH40, m_lbTopLength[19]);
	//back pitch length 20ea
	DDX_Control(pDX, IDC_STATIC_PITCH41, m_lbBackLength[0]);
	DDX_Control(pDX, IDC_STATIC_PITCH42, m_lbBackLength[1]);
	DDX_Control(pDX, IDC_STATIC_PITCH43, m_lbBackLength[2]);
	DDX_Control(pDX, IDC_STATIC_PITCH44, m_lbBackLength[3]);
	DDX_Control(pDX, IDC_STATIC_PITCH45, m_lbBackLength[4]);
	DDX_Control(pDX, IDC_STATIC_PITCH46, m_lbBackLength[5]);
	DDX_Control(pDX, IDC_STATIC_PITCH47, m_lbBackLength[6]);
	DDX_Control(pDX, IDC_STATIC_PITCH48, m_lbBackLength[7]);
	DDX_Control(pDX, IDC_STATIC_PITCH49, m_lbBackLength[8]);
	DDX_Control(pDX, IDC_STATIC_PITCH50, m_lbBackLength[9]);
	DDX_Control(pDX, IDC_STATIC_PITCH51, m_lbBackLength[10]);
	DDX_Control(pDX, IDC_STATIC_PITCH52, m_lbBackLength[11]);
	DDX_Control(pDX, IDC_STATIC_PITCH53, m_lbBackLength[12]);
	DDX_Control(pDX, IDC_STATIC_PITCH54, m_lbBackLength[13]);
	DDX_Control(pDX, IDC_STATIC_PITCH55, m_lbBackLength[14]);
	DDX_Control(pDX, IDC_STATIC_PITCH56, m_lbBackLength[15]);
	DDX_Control(pDX, IDC_STATIC_PITCH57, m_lbBackLength[16]);
	DDX_Control(pDX, IDC_STATIC_PITCH58, m_lbBackLength[17]);
	DDX_Control(pDX, IDC_STATIC_PITCH59, m_lbBackLength[18]);
	DDX_Control(pDX, IDC_STATIC_PITCH60, m_lbBackLength[19]);

	DDX_Check(pDX, IDC_CHECK_ALARM_OFF1, m_bAlarmOff);
	DDX_Control(pDX, IDC_STATIC_MISMATCH_EPC1, m_lbMisEpc1);
	DDX_Control(pDX, IDC_STATIC_MISMATCH_EPC2, m_lbMisEpc2);
	DDX_Control(pDX, IDC_STATIC_MISMATCHLOTNO, m_lbMisINFO[0]);
	DDX_Control(pDX, IDC_STATIC_MISMATCHROLLA, m_lbMisINFO[1]);
	DDX_Control(pDX, IDC_STATIC_MISMATCHROLLA2, m_lbMisINFO[2]);

	DDX_Control(pDX, IDC_STATIC_MISDEFECT1, m_lbMisDefect1[0]);//1레인
	DDX_Control(pDX, IDC_STATIC_MISDEFECT2, m_lbMisDefect1[1]);//2레인
	DDX_Control(pDX, IDC_STATIC_MISDEFECT3, m_lbMisDefect1[2]);//3레인
	DDX_Control(pDX, IDC_STATIC_MISDEFECT11, m_lbMisDefect2[0]);//1레인
	DDX_Control(pDX, IDC_STATIC_MISDEFECT12, m_lbMisDefect2[1]);//2레인
	DDX_Control(pDX, IDC_STATIC_MISDEFECT13, m_lbMisDefect2[2]);//3레인


	DDX_Control(pDX, IDC_LIST_LOG1, m_log_Map);
	DDX_Control(pDX, IDC_STATIC_TOPBACKLENTH3, m_lbTBGap);
}


BEGIN_MESSAGE_MAP(CDlgDefectMap, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_SHOWHIDE, &CDlgDefectMap::OnBnClickedButtonShowhide)
	ON_BN_CLICKED(IDC_BUTTON_ALARMSPEC, &CDlgDefectMap::OnBnClickedButtonAlarmspec)
	ON_BN_CLICKED(IDC_CHECK_ALARM_OFF1, &CDlgDefectMap::OnBnClickedCheckAlarmOff1)
	ON_BN_CLICKED(IDC_BUTTON_ALARMSPEC2, &CDlgDefectMap::OnBnClickedButtonAlarmspec2)
	ON_BN_CLICKED(IDC_BUTTON_MODELMIS, &CDlgDefectMap::OnBnClickedButtonModelmis)
	ON_WM_DRAWITEM()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_LAST_WIDT_DATA, &CDlgDefectMap::OnBnClickedBtnLastWidtData)
	ON_BN_CLICKED(IDC_BTN_DATA_FOLDER_MISMATCH, &CDlgDefectMap::OnBnClickedBtnDataFolderMismatch)
END_MESSAGE_MAP()


// CDlgDefectMap 메시지 처리기입니다.
// BOOL CDlgDefectMap::Create()
// {
// 
// 	return CDialog::Create(m_nID, m_vMain);
// }


void CDlgDefectMap::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CDC dcMem;

	CDC* pDc = GetDC();

	CString strPath;
	strPath.Format("%s%s", "C:\\GLIM\\","DefectMapBackGround.bmp");
//	DrawBMP(strPath, &dc, 0, 0, SRCCOPY);	

	


	if(m_bSim1==TRUE){

		CString strline[100];
		double doldpos=0,dcamscale = 0.0425,dfirst = 0;;//.0423;
		int nLineCount1[MAX_CAMERAS]={0,},nLineCount2 = 0;
		double dLineEdgeData1[MAX_CAMERAS][10];

//data input
		nLineCount1[0] =nLineCount1[1] =nLineCount1[2] = 2;
		dLineEdgeData1[0][0] = 5329;
		dLineEdgeData1[0][1] = 5422;
		dLineEdgeData1[1][0] = 3307;
		dLineEdgeData1[1][1] = 4034;
		dLineEdgeData1[2][0] = 1913;
		dLineEdgeData1[2][1] = 1987;

		CPoint ptOld,pttmp[2];
		CPoint pt,pt2;
		for(int tb=0;tb<2;tb++){
			nLineCount2 = 0;
			for(int k=0;k<MAX_CAMERAS;k++){
				if(nLineCount1[k]>0){
					for(int i=0;i<nLineCount1[k];i++){
						pt.SetPoint(dLineEdgeData1[k][i],0);
						pt2.SetPoint(dLineEdgeData1[k][i],CAM_HEIGHT_3072);
						if(nLineCount2==0)dfirst = dLineEdgeData1[k][i];
						if(nLineCount2>0){
							if(dLineEdgeData1[k][i]-doldpos<0)
								strline[nLineCount2-1].Format("%.2f",(dLineEdgeData1[k][i]-doldpos+CAM_WIDTH_CIS*k)*dcamscale);
							else
								strline[nLineCount2-1].Format("%.2f",(dLineEdgeData1[k][i]-doldpos)*dcamscale);
						}
						doldpos = dLineEdgeData1[k][i]+CAM_WIDTH_CIS*k;
		//				DrawLineCam(pDC,pt,pt2,COLOR_GREEN,2,k);
						//그대로 밑에 그린다.
						if(tb==0){
							pt = DrawPitchCam(pDc,pt,pt2,COLOR_BLACK,4,k);
							if(nLineCount2==0)pttmp[0] = pt;
							else	pttmp[1] = pt;
							//rectangle
							if(nLineCount2>0){
								//						str1.Format("%d",nLineCount1);
								if(i%2==1){
									//여기 양극 음극 색 추가
									DrawRectangle(pDc,pt,pt2,ptOld,COLOR_ORANGE1,2,k,nLineCount2-1,strline[nLineCount2-1]);
								}
								else
									DrawRectangle(pDc,pt,pt2,ptOld,COLOR_BLACK,2,k,nLineCount2-1,strline[nLineCount2-1]);
							}
						}
						else{
							pt = DrawPitchCam1(pDc,pt,pt2,COLOR_BLACK,4,k);
 							if(nLineCount2==0)pttmp[0] = pt;
 							else	pttmp[1] = pt;
 							//rectangle
 							if(nLineCount2>0){
 								//						str1.Format("%d",nLineCount1);
 								if(i%2==1)
 									DrawRectangle1(pDc,pt,pt2,ptOld,COLOR_ORANGE1,2,k,nLineCount2-1,strline[nLineCount2-1]);
 								else
 									DrawRectangle1(pDc,pt,pt2,ptOld,COLOR_BLACK,2,k,nLineCount2-1,strline[nLineCount2-1]);
 							}
						}
						ptOld = pt;
						nLineCount2++;
					}
				}
//				if(k==0)					DrawData(pDC,k);
			}
			for(int kk=nLineCount2;kk<MAX_LENGTH;kk++){
				m_lbTopLength[kk].ShowWindow(0);
				m_lbBackLength[kk].ShowWindow(0);
				
			}
		}
// 		CString str1;
// 		double dLength = doldpos-dfirst;
// 		if(m_strComputerName.Find("Top")>=0)
// 			str1.Format("TOP 제품폭 : %.2f mm" ,  dLength  * dcamscale);
// 		else
// 			str1.Format("BACK 제품폭 : %.2f mm" ,  dLength  * dcamscale);
// 		CRect rc11;
// 		GetDlgItem(IDC_STATIC_FULL_WIDTH)->GetWindowRect(rc11);
// 
// 		m_lbFullWidth.SetText(str1);
// 		m_lbFullWidth.MoveWindow(pttmp[0].x,pttmp[0].y-250,pttmp[1].x-pttmp[0].x,rc11.Height());
	}

	DrawGridLine1();

	ReleaseDC(pDc);

	// 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.
}



void CDlgDefectMap::SetPosCount(int nCellCnt)
{
	m_nPosCount = nCellCnt;
	
}
void CDlgDefectMap::SetEdgePos(double* dPos)
{
	for(int i=0; i<m_nPosCount; i++){
		m_dCellPos[i] = dPos[i];
	}
}
void CDlgDefectMap::SetEdgeWidth(double* dWidth)
{
	for(int i=0; i<m_nPosCount-1; i++){
		m_dCellWidth[i] = dWidth[i];
	}
	
}
void CDlgDefectMap::RedrawMap()
{
	
	CDC *pDC = GetDC();

	DrawGridLine2(pDC, m_nPosCount);			

	ReleaseDC(pDC);
}

void CDlgDefectMap::DrawGridLine(CDC *pDC)
{
	//int width = m_rtArea.Width();
	//int height = m_rtArea.Height();
	//double dXscale = (double)(width/m_dViewsizex); //1mm당 pixel scalefactor
	//double dYscale = (double)(height/m_dViewsizey);
	//CString str;

	//pDC->SetBkMode(TRANSPARENT);
	//pDC->SetTextColor(COLOR_WHITE);
	//CPen *pOldPen,*pGrid;

	//pGrid = new CPen(PS_DOT, 1, RGB(85,85,85)	); 
	//pOldPen = pDC->SelectObject(pGrid);

	//for(int i=0;i<=m_displayGridY;i++)
	//{
	//	pDC->MoveTo(0,(int)(i*(m_dViewsizey/m_displayGridY)*dYscale));
	//	pDC->LineTo(width,(int)(i*(m_dViewsizey/m_displayGridY)*dYscale));
	//	str.Format("%4d",(int)(m_nViewSttposy_ctrl_server/1000+(i*m_dViewsizey/(m_displayGridY*1000))));
	//	if(i<m_displayGridY-1){
	//		pDC->TextOut(width-33,(int)((m_displayGridY - i)*(m_dViewsizey/m_displayGridY)*dYscale)-37,str);
	//	}
	//}

	//for(int i=0;i<m_displayGridX;i++)
	//{
	//	pDC->MoveTo((int)(i*(m_dViewsizex/m_displayGridX)*dXscale),0);
	//	pDC->LineTo((int)(i*(m_dViewsizex/m_displayGridX)*dXscale),height);
	//	str.Format("%4d",(int)(m_nViewSttposx_ctrl_server/1000+(i*m_dViewsizex/(m_displayGridX*1000))));
	//	if(i<m_displayGridX-1 && i%2)
	//		pDC->TextOut((int)(i*(m_dViewsizex/m_displayGridX)*dXscale)+20, (int)0 ,str);
	//}


	//pDC->SelectObject(pOldPen);
	//delete pGrid;	

}

void CDlgDefectMap::DrawGridLine2(CDC *pDC, int nWidthCnt)
{
	if(nWidthCnt <= 1 || nWidthCnt > 60 ){
		return;
	}
	int marginX = 60;
	int marginY = 100;
	int nCellWidth = (m_rtArea.Width()-(marginX*2)) / (nWidthCnt-1);
	int nCellHeight = m_rtArea.Height()-(marginY*2);
	int width = m_rtArea.Width();
	int height = m_rtArea.Height();

	int offsetX = 0;
	
	CString str;

// 	CPen pen;
// 	CBrush brush;
// 	CPen* oldPen;
// 	CBrush* oldBrush;
	//Rect만들기
	//CRect* rtRect = new CRect[nWidthCnt];
	double dRatio = 0.3;
	

	for(int i=0;i<nWidthCnt;i++){
		CPoint pos;
		if(i%2 ==0){
			//pos.x = nCellWidth*i +nCellWidth-(nCellWidth*0.5) + offsetX;
			pos.x = nCellWidth*i;
			pos.x += ((nCellWidth*dRatio));	
		}
		else{
			//pos.x = nCellWidth*i+nCellWidth-(nCellWidth*0.5) + offsetX;
			pos.x = nCellWidth*i;
			
			pos.x -= ((nCellWidth*dRatio));
		}
		pos.y = height*0.5;
		str.Format("%0.2f", m_dCellPos[i]);
		pDC->TextOut(pos.x - 12, pos.y - 60, str);
	}

	for(int i=0;i<nWidthCnt-1;i++){
		CPoint pos;
		pos.x = nCellWidth*i+nCellWidth-(nCellWidth*0.5) + offsetX;
		pos.y = height*0.5;
		CRect destRect;
		destRect.SetRect(pos.x - (nCellWidth*0.5), pos.y - (nCellHeight*0.5), pos.x + (nCellWidth*0.5), pos.y + (nCellHeight*0.5));

		// 색상선택
		if(i%2 ==0){
// 			pen.CreatePen( PS_DOT, 3, GRAY );    
// 			brush.CreateSolidBrush( GRAY ); 
			destRect.InflateRect(-(destRect.Width()*dRatio), 0);
		}
		else{
// 			pen.CreatePen( PS_DOT, 3, BLACK );    
// 			brush.CreateSolidBrush( BLACK );
			destRect.InflateRect(+(destRect.Width()*dRatio), 0);
		}

// 		oldPen = (CPen*)pDC->SelectObject( &pen );
// 		oldBrush = (CBrush*)pDC->SelectObject( &brush );
		pDC->Rectangle(destRect);
	
		pos.x = nCellWidth*i+nCellWidth-(nCellWidth*0.5) + offsetX;
		pos.y = height*0.5;

		str.Format("%0.2f", m_dCellWidth[i]);
		//pDC->TextOut(pos.x - (nCellWidth*0.5) - 12, pos.y - 50, str);
		pDC->TextOut(pos.x - 15, pos.y - 9, str);

// 	
//  		pen.DeleteObject();
//  		brush.DeleteObject();
	}

//	pDC->SelectObject( oldPen );
//	pDC->SelectObject( oldBrush );

	//delete pGrid;	

	//delete[] rtRect;

}

LRESULT CDlgDefectMap::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialog::WindowProc(message, wParam, lParam);
}

BOOL CDlgDefectMap::OnInitDialog()
{
	CDialog::OnInitDialog();

	CVisWebView *pDlg = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pDlg->GetDocument();

	//Default Line draw
	m_DispFont.CreatePointFont(180,"굴림");
	GetDlgItem(IDC_BUTTON_SHOWHIDE)->SetFont(&m_DispFont);
	GetDlgItem(IDC_BUTTON_ALARMSPEC)->SetFont(&m_DispFont);
	GetDlgItem(IDC_CHECK_ALARM_OFF1)->SetFont(&m_DispFont);
	GetDlgItem(IDC_BUTTON_ALARMSPEC2)->SetFont(&m_DispFont);

	GetDlgItem(IDC_BTN_DATA_FOLDER_MISMATCH)->SetFont(&m_DispFont);
	GetDlgItem(IDC_BTN_LAST_WIDT_DATA)->SetFont(&m_DispFont);

	m_DispFont1.CreatePointFont(200,"휴먼둥근헤드라인");
	GetDlgItem(IDC_BUTTON_MODELMIS)->SetFont(&m_DispFont1);


	InitControl();
	ShowHideMisMatch(2,0,0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDlgDefectMap::DrawGridLine1()
{
	CDC *pDC = GetDC();

	CPen pen;
	pen.CreatePen(PS_SOLID, 4, COLOR_TOP_BK);

	CPen* pOldPen = (CPen*) pDC->SelectObject(&pen);

	CRect rcDest;
	GetDlgItem(IDC_STATIC_MISMATCHVIEW)->GetWindowRect(rcDest);
	CPoint pt1,pt2;
	int nOffsetX1 = 100;
	int nygap = 50;
	pt1.SetPoint(rcDest.left, rcDest.top+rcDest.Height()*0.5+nygap-45);
	pt2.SetPoint(rcDest.right,rcDest.top+rcDest.Height()*0.5+nygap-45);
//	pDC->MoveTo(pt1);pDC->LineTo(pt2);//중앙 가로 선			// 20201022 kjh

	CRect rcLabel;
	GetDlgItem(IDC_STATIC_PITCH2)->GetWindowRect(rcLabel);

	//가용범위 좌 / 우측 라인 
	pt1.SetPoint(rcDest.left, rcDest.top-30);
	pt2.SetPoint(rcDest.left, rcDest.bottom-30);
	//pDC->MoveTo(pt1);pDC->LineTo(pt2);//
	//
	GetDlgItem(IDC_STATIC_PITCH1)->MoveWindow(pt1.x-rcLabel.Width()*0.5,pt1.y-rcLabel.Height()-60,rcLabel.Width(),rcLabel.Height()-30);//
//	m_lbMismatchLength[0].SetText("0");
	m_lbMismatchLength[0].ShowWindow(0);

	pt1.SetPoint(rcDest.right, rcDest.top);
	pt2.SetPoint(rcDest.right,rcDest.bottom);
//	pDC->MoveTo(pt1);pDC->LineTo(pt2);//
	GetDlgItem(IDC_STATIC_PITCH2)->MoveWindow(pt1.x-rcLabel.Width()*0.5,pt1.y-rcLabel.Height()-60,rcLabel.Width(),rcLabel.Height()-30);//
	//m_lbMismatchLength[1].SetText("900");
	m_lbMismatchLength[1].ShowWindow(0);

	pDC->SelectObject(pOldPen);

	ReleaseDC(pDC);

}

void CDlgDefectMap::DrawGridLine3(int nLineCount)
{
	if(nLineCount<1)return;
	CDC *pDC = GetDC();
	CPen pen;
	pen.CreatePen(PS_SOLID, 4, BLACK);
	CPen* pOldPen = (CPen*) pDC->SelectObject(&pen);
	CRect rcDest;
	GetDlgItem(IDC_STATIC_MISMATCHVIEW)->GetWindowRect(rcDest);
	CPoint pt1,pt2;
	int nOffsetX1 = 100;
	int nMod = rcDest.Width()/(nLineCount+1);
	for(int i=0;i<nLineCount;i++){

	}

	pt1.SetPoint(rcDest.left+nOffsetX1, rcDest.top);
	pt2.SetPoint(rcDest.left+nOffsetX1, rcDest.bottom);
	pDC->MoveTo(pt1);pDC->LineTo(pt2);//중앙 가로 선
	pt1.SetPoint(rcDest.right-nOffsetX1, rcDest.top);
	pt2.SetPoint(rcDest.right-nOffsetX1,rcDest.bottom);
	pDC->MoveTo(pt1);pDC->LineTo(pt2);//중앙 가로 선

	pDC->SelectObject(pOldPen);

	ReleaseDC(pDC);

}

CPoint CDlgDefectMap::Scale(CPoint point,int nW1,int nH1)
{
	
	CPoint point_original= point;
	CPoint point_trans = CPoint(0,0);

	CRect rcDest;
	GetDlgItem(IDC_STATIC_MISMATCHVIEW)->GetWindowRect(rcDest);

	int width = rcDest.Width();
	int height = rcDest.Height();//*0.5-10;//FORM_IMG_HEIGHT;
	int nOffsetX = rcDest.left;

	point_trans.x = (long) ((float)(width) / (float)((nW1)) * (float)(point_original.x)) +nOffsetX;
	point_trans.y = (long) ((float)(height) / (float)((nH1)) * (float)(point_original.y));

	point = point_trans;

	return point;
}
void CDlgDefectMap::ShowHideMisMatch(int nMismatch,int nTop,int nback){

	for(int i=0;i<MAX_LENGTH;i++){
		int nIndex = IDC_STATIC_PITCH1+i;
		if(i<nMismatch)		GetDlgItem(nIndex)->ShowWindow(1);//and
		else				GetDlgItem(nIndex)->ShowWindow(0);//and
		nIndex = IDC_STATIC_PITCH21 + i;
		if(i<nTop)			GetDlgItem(nIndex)->ShowWindow(1);//and
		else				GetDlgItem(nIndex)->ShowWindow(0);//and
		nIndex = IDC_STATIC_PITCH41 + i;
		if(i<nback)			GetDlgItem(nIndex)->ShowWindow(1);//and
		else				GetDlgItem(nIndex)->ShowWindow(0);//and
	}
}

void CDlgDefectMap::InitControl(){
	CVisWebView *pDlg = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pDlg->GetDocument();
	for(int i=0;i<20;i++){
		m_lbMismatchLength[i].SetBkColor(COLOR_TOP_BK);
		m_lbMismatchLength[i].SetFontBold(TRUE);
		m_lbMismatchLength[i].SetFontName(_T("굴림"));
		m_lbMismatchLength[i].SetFontSize(25);
		m_lbMismatchLength[i].SetText("");



		if(pDlg->m_strComputerName.Mid(7,1)=="A"){
			if(i%2==0){
				m_lbTopLength[i].SetTextColor(COLOR_BLACK);
				m_lbTopLength[i].SetBkColor(COLOR_GRAY_WHITE1);
				m_lbBackLength[i].SetTextColor(COLOR_BLACK);
				m_lbBackLength[i].SetBkColor(COLOR_GRAY_WHITE1);
			}
			else{
				m_lbTopLength[i].SetTextColor(COLOR_WHITE);
				m_lbTopLength[i].SetBkColor(COLOR_BLACK);
				m_lbBackLength[i].SetTextColor(COLOR_WHITE);
				m_lbBackLength[i].SetBkColor(COLOR_BLACK);
			}
		}
		else{
			if(i%2==0){
				m_lbTopLength[i].SetTextColor(COLOR_BLACK);
				m_lbTopLength[i].SetBkColor(COLOR_TOP_BK);
				m_lbBackLength[i].SetTextColor(COLOR_BLACK);
				m_lbBackLength[i].SetBkColor(COLOR_TOP_BK);
			}
			else{
				m_lbTopLength[i].SetTextColor(COLOR_WHITE);
				m_lbTopLength[i].SetBkColor(COLOR_BLACK);
				m_lbBackLength[i].SetTextColor(COLOR_WHITE);
				m_lbBackLength[i].SetBkColor(COLOR_BLACK);
			}
		}

		m_lbTopLength[i].SetFontBold(TRUE);
		m_lbTopLength[i].SetFontName(_T("굴림"));
		m_lbTopLength[i].SetFontSize(50);
		m_lbTopLength[i].SetText("");

//		m_lbBackLength[i].SetBkColor(COLOR_TOP_BK);
		m_lbBackLength[i].SetFontBold(TRUE);
		m_lbBackLength[i].SetFontName(_T("굴림"));
		m_lbBackLength[i].SetFontSize(50);
		m_lbBackLength[i].SetText("");

	}

	m_lbMisEpc1.SetBkColor(COLOR_YELLOW);
	m_lbMisEpc1.SetFontBold(TRUE);
	m_lbMisEpc1.SetFontName(_T("굴림"));
	m_lbMisEpc1.SetFontSize(25);
	m_lbMisEpc2.SetBkColor(COLOR_YELLOW);
	m_lbMisEpc2.SetFontBold(TRUE);
	m_lbMisEpc2.SetFontName(_T("굴림"));
	m_lbMisEpc2.SetFontSize(25);
	if(pDoc->m_data.m_nEpcPos==1){
		m_lbMisEpc1.SetText("EPC(1)");
		m_lbMisEpc2.SetText("N-EPC");
	}
	else{
		m_lbMisEpc1.SetText("N-EPC");
		m_lbMisEpc2.SetText("EPC(1)");
	}

	int nSize = 20;
	CString str;
	m_lbMisINFO[0].SetTextColor(COLOR_YELLOW);
	m_lbMisINFO[0].SetBkColor(RGB(51,51,151));
	m_lbMisINFO[0].SetFontName("휴먼둥근헤드라인");
	m_lbMisINFO[0].SetFontSize(nSize);
	str.Format("  Lot No. ABCDEFGHI");
	m_lbMisINFO[0].SetText(str);

	m_lbMisINFO[1].SetTextColor(COLOR_YELLOW);
	m_lbMisINFO[1].SetBkColor(RGB(51,51,151));
	m_lbMisINFO[1].SetFontName("휴먼둥근헤드라인");
	m_lbMisINFO[1].SetFontSize(nSize);
	str.Format("  CORE A:");//pDoc->m_data.m_nMachineLengthAB[ntime%2] 
	m_lbMisINFO[1].SetText(str);

	m_lbMisINFO[2].SetTextColor(COLOR_YELLOW);
	m_lbMisINFO[2].SetBkColor(RGB(51,51,151));
	m_lbMisINFO[2].SetFontName("휴먼둥근헤드라인");
	m_lbMisINFO[2].SetFontSize(nSize);
	str.Format("  CORE B:");
	m_lbMisINFO[2].SetText(str);

	m_lbTBGap.SetTextColor(COLOR_BLUE);
	m_lbTBGap.SetBkColor(COLOR_WHITE);
	m_lbTBGap.SetFontName("휴먼둥근헤드라인");
	m_lbTBGap.SetFontSize(20);
	str.Format("  mm  ");
	m_lbTBGap.SetText(str);


	for(int i=0;i<3;i++){
		m_lbMisDefect1[i].SetTextColor(COLOR_YELLOW);
		m_lbMisDefect1[i].SetBkColor(COLOR_GRAY_WHITE1);
		m_lbMisDefect1[i].SetFontName("휴먼둥근헤드라인");
		m_lbMisDefect1[i].SetFontSize(nSize);
		str.Format("%d Lane Coat Defect : 0 ea",i+1);
		m_lbMisDefect1[i].SetText(str);

		m_lbMisDefect2[i].SetTextColor(COLOR_YELLOW);
		m_lbMisDefect2[i].SetBkColor(COLOR_BLACK);
		m_lbMisDefect2[i].SetFontName("휴먼둥근헤드라인");
		m_lbMisDefect2[i].SetFontSize(nSize);
		str.Format("%d Lane N-Coat Defect : 0 ea",i+1);
		m_lbMisDefect2[i].SetText(str);
	}


}

//////////////////////sim
CPoint CDlgDefectMap::DrawPitchCam(CDC *pDC, CPoint p1, CPoint p2, COLORREF lColor, int nLineWidth,int nCam)
{

	CPen pen,*pOldPen;
	pen.CreatePen(PS_SOLID,nLineWidth, lColor);
	pOldPen = (CPen*)pDC->SelectObject(&pen);
	//X point만 사용한다.
	p1 = Scale(p1,nCam);
	p2 = Scale(p2,nCam);
	CRect rcDest,rcMain;
	GetWindowRect(rcMain);
//	GetDlgItem(IDC_DETAIL_LINE)->GetWindowRect(rcDest);
	rcDest.SetRect(2,479,1878,663);

	rcDest.OffsetRect(-rcMain.left,-rcMain.top);	
	p1.y = rcDest.top;	p2.y = rcDest.bottom;

	CPoint p3,p4;
	p3.SetPoint(p1.x,p1.y-150);
	p4.SetPoint(p2.x,p2.y-217);
// 	pDC->MoveTo(p3);					// 20201022 kjh
// 	pDC->LineTo(p4);
	m_nLintTB[0][0] = p3.y;
	m_nLintTB[0][1] = p4.y;
	pDC->SelectObject(pOldPen);
	return p1;
}
void CDlgDefectMap::DrawRectangle(CDC *pDC, CPoint p1, CPoint p2, CPoint p3, COLORREF lColor, int nLineWidth,int nCam,int nCount,CString strmm)
{
	CPen pen,*pOldPen;
	pen.CreatePen(PS_SOLID,nLineWidth, lColor);
	pOldPen = (CPen*)pDC->SelectObject(&pen);
	CBrush brush;
	brush.CreateSolidBrush(lColor );     // 오렌지색 채움색을 생성
	CBrush* oldBrush = pDC->SelectObject( &brush );
	//X point만 사용한다.
	p1 = Scale(p1,nCam);
	p2 = Scale(p2,nCam);
	CRect rcDest,rcMain,rtRect,rctitle,rcLength;
	GetWindowRect(rcMain);
//	GetDlgItem(IDC_DETAIL_LINE)->GetWindowRect(rcDest);
//	GetDlgItem(IDC_STATIC_COAT_TITLE1)->GetWindowRect(rctitle);
//	GetDlgItem(IDC_STATIC_COAT_LEN1)->GetWindowRect(rcLength);
	rcDest.SetRect(2,479,1878,663);
	rctitle.SetRect(196,25,396,138);//(196,25,396,138);
	rcLength.SetRect(2,31,277,166);//31166
	rcDest.OffsetRect(-rcMain.left,-rcMain.top);	
	p1.y = rcDest.top;	p2.y = rcDest.bottom;
	if(p3.x>0)p1  = p3;
//	rtRect.SetRect(p1.x,p1.y-140,p2.x,p2.y-145);
	rtRect.SetRect(p1.x,p1.y-200,p2.x,p2.y-265);

//	if(lColor!=COLOR_ORANGE1)
		pDC->Rectangle(rtRect);
	//타이틀 쓰기
	CRect rtTitle;
	//		rtTitle.SetRect((p1.x+p2.x)*0.5 - rctitle.Width()*0.5,p1.y-rctitle.Height() - 100,(p1.x+p2.x)*0.5+ rctitle.Width()*0.5,p1.y - 100);//기존 길이 위에 표시
	if(nCount<1){
	}
	// 	사이즈
	int ncheck = 0;
	if(nCount%2==0){
		//위에
		rtTitle.SetRect((p1.x+p2.x)*0.5 - rcLength.Width()*0.5,p1.y-rcLength.Height() - 141,(p1.x+p2.x)*0.5+ rcLength.Width()*0.5,p1.y - 141);
		rtTitle.top -=20;
		rtTitle.bottom -=50;
// 		if(rtTitle.Width()>= rtRect.Width()){
// 			rtTitle.InflateRect(rtRect.Width()-rtTitle.Width(),0);
// 			ncheck = 1;
// 		}
//		rtTitle.InflateRect(-30,0);
		rtTitle.InflateRect(-30,-20);


	}
	else{
		rtTitle.SetRect((p1.x+p2.x)*0.5 - rcLength.Width()*0.5,p1.y-rcLength.Height()+10 ,(p1.x+p2.x)*0.5+ rcLength.Width()*0.5,p1.y +10);
		rtTitle.top -=20;
		rtTitle.bottom -=50;
		if(rtTitle.Width()>= rtRect.Width()){
			rtTitle.InflateRect(rtRect.Width()-rtTitle.Width(),0);
			ncheck = 1;
		}
		
		rtTitle.InflateRect(0,-60,0,0);
		rtTitle.OffsetRect(0,-60);
	}
	m_lbTopLength[nCount].SetFontSize(m_nTitleSize-10);

	m_lbTopLength[nCount].MoveWindow(rtTitle);
	m_lbTopLength[nCount].SetText(strmm);

	//색상 변경
	if(nCount>=0){
		int nret = CheckSpec(strmm,nCount);
		if(nret==2){//red
			m_lbTopLength[nCount].SetTextColor(COLOR_RED);
		}
		else if(nret ==1){
			m_lbTopLength[nCount].SetTextColor(COLOR_ORANGE);
		}
		else{
			if(nCount%2==1)
				m_lbTopLength[nCount].SetTextColor(COLOR_WHITE);
			else
				m_lbTopLength[nCount].SetTextColor(COLOR_BLACK);
		}
	}
//	m_lbTopLength[nCount].SetFontBold(TRUE);

	m_lbTopLength[nCount].ShowWindow(1);
	pDC->SelectObject( oldBrush );
	pDC->SelectObject(pOldPen);
}
CPoint CDlgDefectMap::Scale(CPoint point,int nCam)
{
	CPoint point_original= point;
	CPoint point_trans = CPoint(0,0);

	CRect rcDest;
	if(nCam==0)
		rcDest.SetRect(2,25,637,218);
	else if(nCam==1)
		rcDest.SetRect(637,25,1271,218);
	else
		rcDest.SetRect(1271,25,1906,218);

	int width = rcDest.Width();
	int height = rcDest.Height();//*0.5-10;//FORM_IMG_HEIGHT;
	int nOffsetX = rcDest.left;

	point_trans.x = (long) ((float)(width) / (float)((CAM_WIDTH_CIS)) * (float)(point_original.x)) +nOffsetX;
	point_trans.y = (long) ((float)(height) / (float)((CAM_HEIGHT_3072)) * (float)(point_original.y));

	point = point_trans;

	return point;
}
CPoint CDlgDefectMap::DrawPitchCam1(CDC *pDC, CPoint p1, CPoint p2, COLORREF lColor, int nLineWidth,int nCam)
{

	CPen pen,*pOldPen;
	pen.CreatePen(PS_SOLID,nLineWidth, lColor);
	pOldPen = (CPen*)pDC->SelectObject(&pen);
	//X point만 사용한다.
	p1 = Scale1(p1,nCam);
	p2 = Scale1(p2,nCam);
	CRect rcDest,rcMain;
	GetWindowRect(rcMain);
//	GetDlgItem(IDC_DETAIL_LINE)->GetWindowRect(rcDest);
	rcDest.SetRect(2,479,1878,663);

	rcDest.OffsetRect(-rcMain.left,-rcMain.top);	
	p1.y = rcDest.top;	p2.y = rcDest.bottom;

	CPoint p3,p4;
	p3.SetPoint(p1.x,p2.y-140);
	p4.SetPoint(p2.x,p2.y+190);
	pDC->MoveTo(p3);
	pDC->LineTo(p4);

//

	pDC->SelectObject(pOldPen);
	return p1;
}
CPoint CDlgDefectMap::DrawPitchCam2(CDC *pDC, CPoint p1, CPoint p2, COLORREF lColor, int nLineWidth,int nCam,double dmismatch,CString strmis,int nIndex,double dgap,CString strgap)
{

	CPen pen,*pOldPen;
	pen.CreatePen(PS_SOLID,nLineWidth, lColor);
	pOldPen = (CPen*)pDC->SelectObject(&pen);
	//X point만 사용한다.
	p1 = Scale1(p1,nCam);
	p2 = Scale1(p2,nCam);
	CRect rcDest,rcMain;
	GetWindowRect(rcMain);
	//	GetDlgItem(IDC_DETAIL_LINE)->GetWindowRect(rcDest);
	rcDest.SetRect(2,479,1878,663);

	rcDest.OffsetRect(-rcMain.left,-rcMain.top);	
	p1.y = rcDest.top;	p2.y = rcDest.bottom;

	CPoint p3,p4,p5;
	p3.SetPoint(p1.x,p2.y-217);
	p4.SetPoint(p2.x,p2.y+20);
	p5.SetPoint(p2.x,p2.y+20-120);
// 	pDC->MoveTo(p3);						// 20201022 kjh
// 	pDC->LineTo(p5);

	m_nLintTB[1][0] = p3.y;
	m_nLintTB[1][1] = p4.y;

	//
	if(nIndex>0){
		CRect rt1;
		int nxoffset = 60, nyoffset=60,noffset1 = 60,noffset2=280;
		//mismatch
		if(nIndex%2==1)
			rt1.SetRect(p4.x-nxoffset+noffset1,p4.y+noffset2,p4.x+nxoffset+noffset1,p4.y+nyoffset+noffset2);
		 else
			rt1.SetRect(p4.x-nxoffset-noffset1,p4.y+noffset2,p4.x+nxoffset-noffset1,p4.y+nyoffset+noffset2);
		rt1.OffsetRect(0,-220);
		rt1.top -= 80;
		rt1.bottom -= 80;
		if(strmis != "1000")
			DataDraw1(rt1,strmis,300,COLOR_BLUE,1);
		else{

		}
// 		rt1.SetRect(p4.x-nxoffset,p4.y+noffset2+60,p4.x+nxoffset,p4.y+nyoffset+noffset2+60);
// 		DataDraw2(rt1,strmis,300,COLOR_GRAY_WHITE1,1);
	}
	pDC->SelectObject(pOldPen);
	return p1;
}
void CDlgDefectMap::DrawRectangle1(CDC *pDC, CPoint p1, CPoint p2, CPoint p3, COLORREF lColor, int nLineWidth,int nCam,int nCount,CString strmm)
{
	CPen pen,*pOldPen;
	pen.CreatePen(PS_SOLID,nLineWidth, lColor);
	pOldPen = (CPen*)pDC->SelectObject(&pen);
	CBrush brush;
	brush.CreateSolidBrush(lColor );     // 오렌지색 채움색을 생성
	CBrush* oldBrush = pDC->SelectObject( &brush );
	//X point만 사용한다.
	p1 = Scale1(p1,nCam);
	p2 = Scale1(p2,nCam);
	CRect rcDest,rcMain,rtRect,rctitle,rcLength;
	GetWindowRect(rcMain);
//	GetDlgItem(IDC_DETAIL_LINE)->GetWindowRect(rcDest);
//	GetDlgItem(IDC_STATIC_COAT_TITLE1)->GetWindowRect(rctitle);
//	GetDlgItem(IDC_STATIC_COAT_LEN1)->GetWindowRect(rcLength);
	rcDest.SetRect(2,479,1878,663);
	rctitle.SetRect(196,25,396,138);
	rcLength.SetRect(2,31,277,166);
	int noffset1 = 178,noffset2 = 340;
	rcDest.OffsetRect(-rcMain.left,-rcMain.top);	
	p1.y = rcDest.top;	p2.y = rcDest.bottom;
	if(p3.x>0)p1  = p3;
	rtRect.SetRect(p1.x,p1.y-noffset2,p2.x,p2.y-noffset2);
	CRect rttmp;
	rttmp = rtRect;//.OffsetRect(0,200);
	rttmp.OffsetRect(0,382);//360
	if(lColor!=COLOR_ORANGE1)
		pDC->Rectangle(rttmp);
	//타이틀 쓰기
	CRect rtTitle;
	int noffset3 = 20;
	CRect rt1;
	if(nCount%2==0){
		//위에
		rtTitle.SetRect((p1.x+p2.x)*0.5 - rcLength.Width()*0.5,p1.y-rcLength.Height() + noffset2+noffset3,(p1.x+p2.x)*0.5+ rcLength.Width()*0.5,p1.y + noffset2+noffset3);
	}
	else{
		rtTitle.SetRect((p1.x+p2.x)*0.5 - rcLength.Width()*0.5,p1.y-rcLength.Height() +noffset1+noffset3,(p1.x+p2.x)*0.5+ rcLength.Width()*0.5,p1.y +noffset1+noffset3);
	}


	m_lbBackLength[nCount].MoveWindow(rtTitle);
	m_lbBackLength[nCount].SetText(strmm);
	m_lbBackLength[nCount].ShowWindow(1);
	pDC->SelectObject( oldBrush );
	pDC->SelectObject(pOldPen);
}

void CDlgDefectMap::DrawRectangle2(CDC *pDC, CPoint p1, CPoint p2, CPoint p3, COLORREF lColor, int nLineWidth,int nCam,int nCount,CString strmm,CString strmis)
{
	CPen pen,*pOldPen;
	pen.CreatePen(PS_SOLID,nLineWidth, lColor);
	pOldPen = (CPen*)pDC->SelectObject(&pen);
	CBrush brush;
	brush.CreateSolidBrush(lColor );     // 오렌지색 채움색을 생성
	CBrush* oldBrush = pDC->SelectObject( &brush );
	//X point만 사용한다.
	p1 = Scale1(p1,nCam);
	p2 = Scale1(p2,nCam);
	CRect rcDest,rcMain,rtRect,rctitle,rcLength;
	GetWindowRect(rcMain);
	//	GetDlgItem(IDC_DETAIL_LINE)->GetWindowRect(rcDest);
	//	GetDlgItem(IDC_STATIC_COAT_TITLE1)->GetWindowRect(rctitle);
	//	GetDlgItem(IDC_STATIC_COAT_LEN1)->GetWindowRect(rcLength);
	rcDest.SetRect(2,479,1878,663);
	rctitle.SetRect(196,25,396,138);
	rcLength.SetRect(2,31,277,166);
//	int noffset1 = 178,noffset2 = 340;
	int noffset1 = 190,noffset2 = 230;
	rcDest.OffsetRect(-rcMain.left,-rcMain.top);	
	p1.y = rcDest.top;	p2.y = rcDest.bottom;
	if(p3.x>0)p1  = p3;
	rtRect.SetRect(p1.x,p1.y-noffset2-70,p2.x,p2.y-noffset2-140);
	CRect rttmp;
	rttmp = rtRect;//.OffsetRect(0,200);
	rttmp.OffsetRect(0,221);//360
//	if(lColor!=COLOR_ORANGE1)
		pDC->Rectangle(rttmp);
	//타이틀 쓰기
	CRect rtTitle;
	int noffset3 = 20;
	CRect rt1;
	int ncheck = 0;
	if(nCount%2==0){
		//밑에
		rtTitle.SetRect((p1.x+p2.x)*0.5 - rcLength.Width()*0.5,p1.y-rcLength.Height() + noffset2+noffset3,(p1.x+p2.x)*0.5+ rcLength.Width()*0.5,p1.y + noffset2+noffset3-30);
		rtTitle.top -=50;
		rtTitle.bottom -=80;
		rtTitle.InflateRect(-30,-8);
		rtTitle.OffsetRect(0,-32);
		rt1 = rtTitle;
		rt1.OffsetRect(0,100);
		rt1.top -= 30;
		rt1.bottom -= 30;
	}
	else{
		//위에
		rtTitle.SetRect((p1.x+p2.x)*0.5 - rcLength.Width()*0.5,p1.y-rcLength.Height() +noffset1+noffset3-20,(p1.x+p2.x)*0.5+ rcLength.Width()*0.5,p1.y +noffset1+noffset3);
		rtTitle.top -=50;
		rtTitle.bottom -=80;
		if(rtTitle.Width()>= rttmp.Width()){
			rtTitle.InflateRect(rttmp.Width()-rtTitle.Width(),0);
			ncheck = 1;
		}
		rtTitle.InflateRect(0,0,0,-30);
		rtTitle.OffsetRect(0,-100);
		rt1 = rtTitle;
		rt1.OffsetRect(0,170+46);
		rt1.top -= 30;
		rt1.bottom -= 30;
	}
	m_lbBackLength[nCount].SetFontSize(m_nTitleSize-10);


	//DataDraw1(rt1,strmis,200,COLOR_GRAY_WHITE1,1);//no draw mis pith

	m_lbBackLength[nCount].MoveWindow(rtTitle);
	m_lbBackLength[nCount].SetText(strmm);
	//색상 변경
	if(nCount>=0){
		int nret = CheckSpec(strmm,nCount);
		if(nret==2){//red
			m_lbBackLength[nCount].SetTextColor(COLOR_RED);
		}
		else if(nret ==1){
			m_lbBackLength[nCount].SetTextColor(COLOR_ORANGE);
		}
		else{
			if(nCount%2==1)
				m_lbBackLength[nCount].SetTextColor(COLOR_WHITE);
			else
				m_lbBackLength[nCount].SetTextColor(COLOR_BLACK);
		}
	}
	m_lbBackLength[nCount].ShowWindow(1);

	pDC->SelectObject( oldBrush );
	pDC->SelectObject(pOldPen);
}
CPoint CDlgDefectMap::Scale1(CPoint point,int nCam)
{
	CPoint point_original= point;
	CPoint point_trans = CPoint(0,0);

	CRect rcDest;
	if(nCam==0)
		rcDest.SetRect(2,25,637,218);
	else if(nCam==1)
		rcDest.SetRect(637,25,1271,218);
	else
		rcDest.SetRect(1271,25,1906,218);

	int width = rcDest.Width();
	int height = rcDest.Height();//*0.5-10;//FORM_IMG_HEIGHT;
	int nOffsetX = rcDest.left;

	point_trans.x = (long) ((float)(width) / (float)((CAM_WIDTH_CIS)) * (float)(point_original.x)) +nOffsetX;
	point_trans.y = (long) ((float)(height) / (float)((CAM_HEIGHT_3072)) * (float)(point_original.y));

	point = point_trans;

	return point;
}

int CDlgDefectMap::DrawFullLine(int nLinecnt1, double * nedge1,double *dpitch1,int nLinecnt2, double * nedge2,double *dpitch2,int nMiscnt1, double * nMisEdge1,double *dMispitch1)
{//필요 Data 에지 픽셀 , 에지 카운트 , 에지 미리, 

	CVisWebView *pDlg = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pDlg->GetDocument();
	//	CheckPosition(pDoc->m_data.m_nNewLineCount);
	//	DrawLane(pDoc->m_data.m_nLanePos[0][1],0,0);
	CString str12;
	str12.Format("F:%d , %d , %d",pDoc->m_nTotalIns[0], pDoc->m_data.m_nMachineLengthAB[pDoc->m_data.m_nUseChuck],pDoc->m_data.m_nUseChuck);
	AddtoMapLog(str12,0);
	if(pDoc->m_nTotalIns[0] %20 ==0)
		RedrawRect(2);
	//pDoc->m_data.m_nLaneDefectCount[ij][0]
	int nlane1 = 2;
	if(pDlg->m_nLimitLane<=2){
		nlane1 = 2;
		m_lbMisDefect2[0].ShowWindow(1);
		m_lbMisDefect2[1].ShowWindow(1);
		m_lbMisDefect2[2].ShowWindow(0);
		m_lbMisDefect1[0].ShowWindow(1);
		m_lbMisDefect1[1].ShowWindow(1);
		m_lbMisDefect1[2].ShowWindow(0);
	}
	else if(pDlg->m_nLimitLane==3){
		nlane1 = 3;
		m_lbMisDefect2[0].ShowWindow(1);
		m_lbMisDefect2[1].ShowWindow(1);
		m_lbMisDefect2[2].ShowWindow(1);
		m_lbMisDefect1[0].ShowWindow(1);
		m_lbMisDefect1[1].ShowWindow(1);
		m_lbMisDefect1[2].ShowWindow(1);
	}
	else{
		m_lbMisDefect2[0].ShowWindow(1);
		m_lbMisDefect2[1].ShowWindow(1);
		m_lbMisDefect2[2].ShowWindow(1);
		m_lbMisDefect1[0].ShowWindow(1);
		m_lbMisDefect1[1].ShowWindow(1);
		m_lbMisDefect1[2].ShowWindow(1);
		nlane1 = 4;
	}
	for(int i=0;i<nlane1 && i<3;i++){
		str12.Format("%d Lane N-Coat Defect : %d EA",i+1,pDoc->m_data.m_nLaneDefectCount[i][0]);
		m_lbMisDefect1[i].SetText(str12);
		str12.Format("%d Lane Coat Defect : %d EA",i+1,pDoc->m_data.m_nLaneDefectCount[i][1]);
		m_lbMisDefect2[i].SetText(str12);
	}

	CDC* pDc = GetDC();
	double dLineEdgeData1[6][40];//0 Top 1 back 2 mismatch 3 gapdata  4width top  5 width back
	CString strline[100];
	CString strline1[100];//mismatch
	CString strline2[100];//gap data
	double dlen1[2] = {0,};
	double dcamscale = pDoc->m_data.m_dScaleFactorX[0];// 0.0425;//.0423;
	double dtopscale = pDoc->m_data.m_dMisbatchScale[0];
	double dbackscale = pDoc->m_data.m_dMisbatchScale[1];
	if(pDoc->m_pDlgInterface->m_bMasterPc){
		dtopscale =dcamscale;// pDoc->m_data.m_dMisbatchScale[1];
		dbackscale = dcamscale;// pDoc->m_data.m_dMisbatchScale[0];

	}
	else{
		if(pDlg->m_strComputerName.Mid(9,1)=="B"){//backdl 이 위 탑이 아래
			dtopscale = dcamscale;//백스케일
			dbackscale = pDlg->m_dTopScale;
		}
		else{
			dtopscale = pDoc->m_data.m_dMisbatchScale[1];
			dbackscale =  pDoc->m_data.m_dMisbatchScale[0];
		}

	}
	if(dtopscale==0)dtopscale = dcamscale;if(dbackscale==0)dbackscale = dcamscale;
	for(int i=0;i<6;i++){
		for(int j=0;j<40;j++)
			dLineEdgeData1[i][j] = 0;
	}
	for(int i=0;i<nLinecnt1;i++){
		dLineEdgeData1[0][i] = nedge1[i];//back
		dLineEdgeData1[4][i] = dpitch1[i];//back
		dLineEdgeData1[5][i] = dpitch2[i];//back
	}
	for(int i=0;i<nLinecnt2;i++)		dLineEdgeData1[1][i] = nedge2[i];//top
	for(int i=0;i<nMiscnt1;i++){			
		dLineEdgeData1[2][i] = nMisEdge1[i];//dMispitch1[i];
		strline1[i].Format("%.2f",(dLineEdgeData1[2][i]));//MISMATCH
		//		dLineEdgeData1[3][i] =  nMisEdge1[i];
	}
	for(int i=0;i<nLinecnt1;i++){			
		dLineEdgeData1[3][i] = dLineEdgeData1[0][i]-dLineEdgeData1[1][i];//[i];//dMispitch1[i];//nMisEdge1 //dMispitch1
		dLineEdgeData1[3][i] = dMispitch1[i];//dLineEdgeData1[0][i]-dLineEdgeData1[1][i];//[i];//dMispitch1[i];//nMisEdge1 //dMispitch1
		//		strline2[i].Format("%.2f",dLineEdgeData1[3][i]);//dMispitch1[i]);//GAP DATA
	}
	dlen1[0] = nedge1[nLinecnt1-1]-nedge1[0];//back
	dlen1[1] = nedge2[nLinecnt1-1]-nedge2[0];//top

	//Mismatch data 확인
	if(dlen1[0]>0 && dlen1[1] > 0){
		for(int i=0;i<nLinecnt1;i++)	{//mismatchsms 는 길이 데이터로 해야함
			if(i>0){
				if(i%2==1)					dLineEdgeData1[3][i] = (dLineEdgeData1[0][i]-dLineEdgeData1[0][i-1])*dtopscale -(dLineEdgeData1[1][i]-dLineEdgeData1[1][i-1])*dbackscale ;
				else						dLineEdgeData1[3][i] = (dLineEdgeData1[0][i]-dLineEdgeData1[0][i-1])*dtopscale -(dLineEdgeData1[1][i]-dLineEdgeData1[1][i-1])*dbackscale;
				strline2[i].Format("%.2f",(dLineEdgeData1[3][i]));
			}
		}
	}

	int nOffsetx = 300;
	CPoint ptOld,pttmp[2];
	CPoint pt,pt2;
	double dfirst[2] ={0,},doldpos[2]={0,};//;
	for(int i=0;i<nLinecnt1 && dlen1[0]>0;i++){//topData
		pt.SetPoint(dLineEdgeData1[0][i]+nOffsetx,0);
		pt2.SetPoint(dLineEdgeData1[0][i]+nOffsetx,CAM_HEIGHT_3072);
		pt.y -=50;
		pt2.y -=50;
		if(i==0)dfirst[0] = dLineEdgeData1[0][i];
		if(i>0){
			if(pDlg->m_strComputerName.Mid(9,1)=="B")
				strline[i-1].Format("%.2f",(dLineEdgeData1[0][i]-doldpos[0])*dtopscale);
			else
				strline[i-1].Format("%.2f",dLineEdgeData1[4][i]);
		}
		doldpos[0] = dLineEdgeData1[0][i];
		pt = DrawPitchCam(pDc,pt,pt2,COLOR_BLACK,4,0);//라인 그리기
		if(i==0)pttmp[0] = pt;
		else	pttmp[1] = pt;
		if(i>0){
			if(pDlg->m_strComputerName.Mid(7,1)=="A"){
				if(i%2==1){
					DrawRectangle(pDc,pt,pt2,ptOld,COLOR_ORANGE1,2,0,i-1,strline[i-1]);//위에 그리기
				}
				else
					DrawRectangle(pDc,pt,pt2,ptOld,COLOR_BLACK,2,0,i-1,strline[i-1]);
			}
			else{
				if(i%2==1){
					DrawRectangle(pDc,pt,pt2,ptOld,COLOR_GRAY_WHITE1,2,0,i-1,strline[i-1]);//위에 그리기
				}
				else
					DrawRectangle(pDc,pt,pt2,ptOld,COLOR_BLACK,2,0,i-1,strline[i-1]);
			}
		}
		ptOld = pt;

	}
	for(int i=0;i<nLinecnt2&& dlen1[1]>0&&dLineEdgeData1[1][i]>100;i++){//backData					// 20201016 kjh
		pt.SetPoint(dLineEdgeData1[1][i]+nOffsetx,0);
		pt2.SetPoint(dLineEdgeData1[1][i]+nOffsetx,CAM_HEIGHT_3072);
		if(i==0)dfirst[1] = dLineEdgeData1[1][i];
		if(i>0){
			if(pDlg->m_strComputerName.Mid(9,1)=="B")
				strline[i-1].Format("%.2f",(dLineEdgeData1[1][i]-doldpos[1])*dbackscale);
			else			strline[i-1].Format("%.2f",dLineEdgeData1[5][i]);
		}
		doldpos[1] = dLineEdgeData1[1][i];
		//		pt = DrawPitchCam1(pDc,pt,pt2,COLOR_BLACK,4,0);
		if(i==nLinecnt2-1)
			strline1[i] = "1000";
		pt = DrawPitchCam2(pDc,pt,pt2,COLOR_BLACK,4,0,dLineEdgeData1[2][i],strline1[i],i,dLineEdgeData1[3][i],strline2[i]);//mismatch 값도 여기서 보인다.
		if(i==0)pttmp[0] = pt;
		else	pttmp[1] = pt;
		if(i>0){
			// 			if(i%2==1)				DrawRectangle1(pDc,pt,pt2,ptOld,COLOR_ORANGE1,2,0,i-1,strline[i-1],strline2[i]);
			// 			else				DrawRectangle1(pDc,pt,pt2,ptOld,COLOR_BLACK,2,0,i-1,strline[i-1],strline2[i]);
			if(pDlg->m_strComputerName.Mid(7,1)=="A"){
				if(i%2==1)				DrawRectangle2(pDc,pt,pt2,ptOld,COLOR_ORANGE1,2,0,i-1,strline[i-1],strline2[i]);
				else				DrawRectangle2(pDc,pt,pt2,ptOld,COLOR_BLACK,2,0,i-1,strline[i-1],strline2[i]);
			}
			else{
				if(i%2==1)				DrawRectangle2(pDc,pt,pt2,ptOld,COLOR_GRAY_WHITE1,2,0,i-1,strline[i-1],strline2[i]);
				else				DrawRectangle2(pDc,pt,pt2,ptOld,COLOR_BLACK,2,0,i-1,strline[i-1],strline2[i]);
			}
		}	

		//mismatch data draw

		ptOld = pt;

	}

	//////////////////////////////////////////////////////////
	//mismatch
	CRect rt1;//0124 폭 글자 영역
	for(int kk=nLinecnt1;kk<MAX_LENGTH;kk++){
		m_lbTopLength[kk].ShowWindow(0);
		m_lbBackLength[kk].ShowWindow(0);

	}

	if(dlen1[0] *dtopscale<=0)
		dlen1[0] =dlen1[0];
	CString str1;
	str1.Format("BACK : %.2f (%.6fmm)",dlen1[0] *dtopscale,dtopscale);m_lbTopBackLenth[0].SetText(str1);
	str1.Format("TOP  : %.2f (%.6fmm)",dlen1[1] *dbackscale,dbackscale);m_lbTopBackLenth[1].SetText(str1);
	str1.Format("%.2f mm",(dlen1[0] *dtopscale)-(dlen1[1] *dbackscale));m_lbTBGap.SetText(str1);
	


	ReleaseDC(pDc);
	CString strmsg;
	strmsg.Format("  CORE A:    %d M",pDoc->m_data.m_nMachineLengthAB[0] );//pDoc->m_data.m_nMachineLengthAB[ntime%2] 
	m_lbMisINFO[1].SetText(strmsg);
	strmsg.Format("  CORE B:    %d M",pDoc->m_data.m_nMachineLengthAB[1] );
	m_lbMisINFO[2].SetText(strmsg);

	if (pDlg->m_strComputerName.Find("CMI")>=0) strmsg.Format("  Lot No  : %s C1",pDlg->m_strLotID );
	else strmsg.Format("  Lot No  : %s",pDlg->m_strLotID );
	
	m_lbMisINFO[0].SetText(strmsg);


	return 0;
}
void CDlgDefectMap::OnBnClickedButtonShowhide()
{
	CVisWebView *pDlg = (CVisWebView*)m_pParent;
	pDlg->m_bMismatchView = FALSE;//m_bMismatchView

	KillTimer(20213);
	ShowWindow(0);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CDlgDefectMap::OnBnClickedButtonAlarmspec()
{
	CVisWebView *pDlg = (CVisWebView*)m_pParent;
	if(pDlg->m_SysParam->IsWindowVisible()){
		pDlg->m_SysParam->ShowWindow(0);
	}
	else{
		pDlg->m_SysParam->ShowWindow(1);
		InvalidateRect(CRect(0,100,1920,800));
	}


}

void CDlgDefectMap::OnBnClickedCheckAlarmOff1()
{//m_bAlarmOff
	UpdateData();
	if(m_bAlarmOff==TRUE)
	{//알람
		//SetDlgItemText(IDC_CHECK_ALARM_OFF,"알람OFF");
		CVisWebView *pDlg = (CVisWebView*)m_pParent;
		pDlg->m_IO[0].WriteOutputPort(0,0,0);
		pDlg->AddtoList("Alarm Off",0,TRUE);

	}
}

void CDlgDefectMap::OnBnClickedButtonAlarmspec2()
{
	CVisWebView *pDlg = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pDlg->GetDocument();

	pDlg->OnButtonInterface();
	
}

void CDlgDefectMap::DataDraw1(CRect rt,CString str,int nLineWidth, COLORREF lColor,BOOL bRect)
{//mismatch
	CVisWebView *pDlg = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pDlg->GetDocument();
	CClientDC cdc(this);
	CPen pen,*pOldPen,pen1;
	pen.CreatePen(PS_SOLID,nLineWidth, lColor);
	pOldPen = (CPen*)cdc.SelectObject(&pen);

	CFont font,*pOldFont;
	font.CreatePointFont(nLineWidth,_T("휴먼둥근헤드라인"));
	pOldFont=(CFont*)cdc.SelectObject(&font);

	cdc.SetTextColor(lColor);//
	//	cdc.TextOut(pt1.x,pt1.y,str);
	cdc.DrawText(str,rt,DT_CENTER);

	if(bRect==FALSE){
		pen1.CreatePen(PS_SOLID,2, COLOR_BLUE);
		pOldPen = (CPen*)cdc.SelectObject(&pen1);

		cdc.MoveTo(rt.left, rt.top);
		cdc.LineTo(rt.right,rt.top);
		cdc.LineTo(rt.right,rt.bottom);
		cdc.LineTo(rt.left,rt.bottom);
		cdc.LineTo(rt.left,rt.top);

	}

	cdc.SelectObject(pOldPen);
	cdc.SelectObject(pOldFont);


}
void CDlgDefectMap::DataDraw2(CRect rt,CString str,int nLineWidth, COLORREF lColor,BOOL bRect)
{//gapData
	CVisWebView *pDlg = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pDlg->GetDocument();
	CClientDC cdc(this);
	CPen pen,*pOldPen,pen1;
	pen.CreatePen(PS_SOLID,nLineWidth, lColor);
	pOldPen = (CPen*)cdc.SelectObject(&pen);

	CFont font,*pOldFont;
	font.CreatePointFont(nLineWidth,_T("휴먼둥근헤드라인"));
	pOldFont=(CFont*)cdc.SelectObject(&font);

	cdc.SetTextColor(lColor);//
	//	cdc.TextOut(pt1.x,pt1.y,str);
	cdc.DrawText(str,rt,DT_CENTER);
	//	cdc.DrawText(str,)
	// 	CRect rt;
	// 	rt.SetRect(pt.x,pt.y,pt.x+200,pt.y+200);
	// 	cdc.DrawText(str,rt,DT_LEFT);

	if(bRect==FALSE){
		pen1.CreatePen(PS_SOLID,2, COLOR_BLUE);
		pOldPen = (CPen*)cdc.SelectObject(&pen1);

		cdc.MoveTo(rt.left, rt.top);
		cdc.LineTo(rt.right,rt.top);
		cdc.LineTo(rt.right,rt.bottom);
		cdc.LineTo(rt.left,rt.bottom);
		cdc.LineTo(rt.left,rt.top);

	}

	cdc.SelectObject(pOldPen);
	cdc.SelectObject(pOldFont);


}


int CDlgDefectMap::CheckPosition(int nLine)
{
	//올드 초기화를 언제 하나? Lot change시 ? 
	int nret = 0;
	CVisWebView *pDlg = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pDlg->GetDocument();

	int nGap = 2;//pixel 단위

	if(m_nOldEdgeCount==0){
	}
	else if(nLine<3){
		InvalidateRect(CRect(100,100,1800,1000));
		Sleep(1);
	}
	else if(nLine != m_nOldEdgeCount){
		InvalidateRect(CRect(100,100,1800,1000));
		Sleep(1);
	}
	else if(abs(pDoc->m_data.m_nFoilEdgeOld[0]-pDoc->m_data.m_nFoilEdge[0])>nGap ||abs(pDoc->m_data.m_nFoilEdgeOld[1]-pDoc->m_data.m_nFoilEdge[1])>nGap)//좌/우 젤 끝 에지 위치만 체크
	{
		InvalidateRect(CRect(100,100,1800,1000));	
		Sleep(1);
	}
	m_nOldEdgeCount = pDoc->m_data.m_nNewLineCount;
	pDoc->m_data.m_nFoilEdgeOld[0] = pDoc->m_data.m_nFoilEdge[0];
	pDoc->m_data.m_nFoilEdgeOld[1] = pDoc->m_data.m_nFoilEdge[1];
	pDoc->m_data.m_nFoilEdge[0]=pDoc->m_data.m_nFoilEdge[1] = 0;

	return nret;
}

void CDlgDefectMap::OnBnClickedButtonModelmis()
{//mismatch model
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();

	pView->OnNetworkTest();
	CString strmodel;
	strmodel.Format("Model:%s", pDoc->m_data.m_strDefaultModel);
	SetDlgItemText(IDC_BUTTON_MODELMIS,strmodel);

	// TODO: ¿?±?¿¡ ??Æ®·? ¾?¸² ?³¸®±? ????¸? ?ß°¡??´?´?.
}


void CDlgDefectMap::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
 	if (nIDCtl == IDC_BUTTON_MODELMIS)//로드
	{//버튼 오너드로우 속성 true로 변경할것.
		CDC dc;
		RECT rect;
		dc.Attach(lpDrawItemStruct -> hDC);                //버튼의 dc구하기
		rect = lpDrawItemStruct->rcItem;                   //버튼영역 구하기
		dc.Draw3dRect(&rect,RGB(255,255,255),RGB(0,0,0));  //버튼의 외각선 그리기
		dc.FillSolidRect(&rect,COLOR_GREEN);             //버튼색상
		UINT state = lpDrawItemStruct-> itemState;         //버튼상태구하기
		if((state &ODS_SELECTED))
		{
			dc.DrawEdge(&rect,EDGE_SUNKEN,BF_RECT);
		}
		else
		{
			dc.DrawEdge(&rect,EDGE_RAISED,BF_RECT);
		}
		//		dc.SetBkColor(RGB(51,51,51));                       //text의 백그라운드 색상
		dc.SetTextColor(COLOR_RED);                     //texttort
		TCHAR buffer[MAX_PATH];                            //버튼의 text를 얻기위한 임시버퍼
		ZeroMemory(buffer,MAX_PATH);                       //버퍼초기화
		::GetWindowTextA(lpDrawItemStruct->hwndItem,buffer,MAX_PATH); //버튼의 text얻기
		dc.DrawText(buffer,&rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE); //버튼의 text넣기
		dc.Detach();                                                  //버튼의 dc 풀어주기
	}
	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CDlgDefectMap::DrawModel(CString str)
{
	CString strmodel;
	strmodel.Format("%s",str);
	SetDlgItemText(IDC_BUTTON_MODELMIS,strmodel);

}
void CDlgDefectMap::OnTimer(UINT_PTR nIDEvent)
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	if(nIDEvent == 20213){
		//  		if(pDoc->m_data.m_nSimmulationMode!=1)
		//  			KillTimer(20213);
		CString str;
		str.Format("  CORE A:    %d M",pDoc->m_data.m_nMachineLengthAB[0] );//pDoc->m_data.m_nMachineLengthAB[ntime%2] 
		m_lbMisINFO[1].SetText(str);
		str.Format("  CORE B:    %d M",pDoc->m_data.m_nMachineLengthAB[1] );
		m_lbMisINFO[2].SetText(str);

		if (pView->m_strComputerName.Find("CMI")>=0) str.Format("LotNo.  %s C1", pView->m_strLotID);
		else str.Format("  Lot No  : %s",pView->m_strLotID );
		
		m_lbMisINFO[0].SetText(str);

		pDoc->m_data.m_nOldChuck = pDoc->m_data.m_nUseChuck;//m_nUseChuck
	}

	CDialog::OnTimer(nIDEvent);
}


void CDlgDefectMap::DrawLane(int nLane1,int nLane2,int nLane3)
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();

	CDC *pDC = GetDC();

	CPen pen;
	pen.CreatePen(PS_DASHDOTDOT, 2, COLOR_RED);

	CPen* pOldPen = (CPen*) pDC->SelectObject(&pen);
	CPoint p1,p2,p3,p4;
	p1.SetPoint(nLane1,m_nLintTB[0][0]);
	p1 = Scale(p1,0);
	p2.SetPoint(nLane1,m_nLintTB[0][1]);
	p2 = Scale(p2,0);
	p1.y = m_nLintTB[0][0]+20;p2.y = m_nLintTB[0][1];
	pDC->MoveTo(p1);pDC->LineTo(p2);

	p3.SetPoint(nLane1,m_nLintTB[1][0]);
	p3 = Scale(p3,0);
	p4.SetPoint(nLane1,m_nLintTB[1][1]);
	p4 = Scale(p4,0);

	p3.y = m_nLintTB[1][0];p4.y = m_nLintTB[1][1]-20;
	pDC->MoveTo(p3);pDC->LineTo(p4);
// 	m_nLintTB[0][0];
// 	m_nLintTB[0][1];
// 
// 	CRect rcDest;
// 	GetDlgItem(IDC_STATIC_MISMATCHVIEW)->GetWindowRect(rcDest);
// 	CPoint pt1,pt2;
// 	int nOffsetX1 = 100;
// 	pt1.SetPoint(rcDest.left-nOffsetX1, rcDest.top+rcDest.Height()*0.5);
// 	pt2.SetPoint(rcDest.right+nOffsetX1,rcDest.top+rcDest.Height()*0.5);
// 	pDC->MoveTo(pt1);pDC->LineTo(pt2);//중앙 가로 선
// 


	pDC->SelectObject(pOldPen);

	ReleaseDC(pDC);

}

void CDlgDefectMap::RedrawRect(int n)
{
	if(n==0){
		//width gap
		InvalidateRect(CRect(200,630,1800,710));
	}
	else if(n==1){
		//mismatch
		InvalidateRect(CRect(200,725,1800,810));

	}
	else if(n==2){
		//both
		InvalidateRect(CRect(200,630,1800,810));

	}

}
#define TOTAL_LOG_LIST_COL1		30

void CDlgDefectMap::AddtoMapLog(CString strData,BOOL bWrite)
{
	CString str;
	CTime time = CTime::GetCurrentTime();
	strData = time.Format("[%H:%M:%S]") + strData;

//	WriteLog(strData);
	///*	
	m_log_Map.InsertString(-1,strData);
	int x = m_log_Map.GetCount();
	m_log_Map.SetTopIndex(x-1);
	m_log_Map.SendMessage(WM_VSCROLL,SB_BOTTOM);
	if(x > TOTAL_LOG_LIST_COL1)
	{
		m_log_Map.DeleteString(0);
		m_log_Map.SetCurSel(TOTAL_LOG_LIST_COL1-1);
	}
	//*/
	
}

int	CDlgDefectMap::CheckSpec(CString strdata,int ncount)
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	double d1 =  pView->m_dTolerance[(ncount)*2];//m_dStardLen[nLineCount1-1] +	 min 
	double d2 =  pView->m_dTolerance[(ncount)*2+1];//m_dStardLen[nLineCount1-1] -	max 
	double d3=0,d4=0;
	int nret = 0;
	int	nAlarmCheck = 0;
	if(pDoc->m_pDlgInterface->m_bInsideSet){		//모디파이 체크 시 min/max 값으로 설정 	
		d3 =  pView->m_dTolerance1[(ncount)*2];//m_dStardLen[nLineCount1-1] +
		d4 =  pView->m_dTolerance1[(ncount)*2+1];//m_dStardLen[nLineCount1-1] -
	}
	else{								//모디파이 언체크 시 설정값 만큼 안쪽으로 설정 
		d3 = d1 + pView->m_dTolerance2[ncount];		//min = min + 설정값
		d4 = d2 - pView->m_dTolerance2[ncount];		//max = max - 설정값
	}

	if((atof(strdata) <d3 || atof(strdata) >d4)){
		if((atof(strdata) <d1 || atof(strdata) >d2)){
			pView->m_nNGCount[ncount]++;
			//해당 글자 빨간색
			pView->m_bNGLen[ncount] = TRUE;
			pView->m_nTextColor[ncount] = 2;//red
			nret = 2;
			if(pDoc->m_data.m_dBadAlarmMeter <pView->m_nNGCount[ncount]){//Alarm
				if(pDoc->m_pDlgInterface->m_bAlarm ){//Alarm//알람
					nAlarmCheck++;
				}
			}
		}
		else{
			pView->m_nTextColor[ncount] = 1;//blue
			nret = 1;
		}
	}
	else{
		pView->m_nNGCount[ncount] = 0;//연속 미터수
		pView->m_bNGLen[ncount] = FALSE;//현재 불량
		pView->m_nTextColor[ncount] = 0;//black
		nret = 0;
	}
	return nret;
}
void CDlgDefectMap::OnBnClickedBtnLastWidtData()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();

	if(pView->m_DlgLastData->IsWindowVisible()){
		pView->m_DlgLastData->ShowWindow(SW_HIDE);
	}
	else
		pView->m_DlgLastData->ShowWindow(SW_SHOW);
}

void CDlgDefectMap::OnBnClickedBtnDataFolderMismatch()
{
	CString strPath;

	strPath.Format(_T("D:\\Data\\LotComplete\\"));
	ShellExecute(NULL, _T("open"),strPath , NULL, NULL, SW_SHOW);
}

void CDlgDefectMap::ShowMismatchControl()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();

	if(pView->m_strComputerName.Mid(8,1)=="M" && pView->m_strComputerName.Mid(9,1)=="B")
		GetDlgItem(IDC_BTN_DATA_FOLDER_MISMATCH)->ShowWindow(SW_SHOW);
}
