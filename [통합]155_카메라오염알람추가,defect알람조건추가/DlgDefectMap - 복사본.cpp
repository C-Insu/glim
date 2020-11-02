// DlgDefectMap.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DlgDefectMap.h"


//extern void DrawBMP(LPCTSTR lpszFileName, CDC *pDC, int nX, int nY, DWORD dwRop);

// CDlgDefectMap 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgDefectMap, CDialog)

CDlgDefectMap::CDlgDefectMap(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDefectMap::IDD, pParent)
{
	m_vMain = pParent;
	m_nID = CDlgDefectMap::IDD;

	m_dViewsizex = MAP_MAX_X_ZONE;
	m_dViewsizey = MAP_MAX_Y_ZONE;
	m_maxXzone	=	1900;
	m_maxYzone	=	1000;
	m_displayGridX = 19;
	m_displayGridY = 10;
	m_dViewSttPosX = 0;
	m_dViewSttPosY = 0;
	mapSttOffsetX = 27;
	mapSttOffsetY = -44;
	m_isZoom = FALSE;
	m_nViewSttposy_ctrl_server = 0;
	m_nViewSttposx_ctrl_server = 0;

//	m_pBadpointClick_file[0] = NULL;
//	m_pBadpointClick_file[1] = NULL;
	m_bRedrawTime = TRUE;
//	m_selDefectData = NULL;

}

CDlgDefectMap::~CDlgDefectMap()
{
}

void CDlgDefectMap::CleanSelPointData()
{

}

BOOL CDlgDefectMap::Create()
{
	return CDialog::Create(m_nID, m_vMain);
}

void CDlgDefectMap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgDefectMap, CDialog)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()


// CDlgDefectMap 메시지 처리기입니다.

void CDlgDefectMap::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialog::OnOK();
}

void CDlgDefectMap::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CDC dcMem;

	CDC* pDc = GetDC();

	CString strPath;
	//strPath.Format("%s%s",SKIN_PATH,"DefectMapBackGround.bmp");
	//DrawBMP(strPath, &dc, 0, 0, SRCCOPY);	
	//DrawBMP(strPath, pDc, 0, 0, SRCCOPY);	

	if(m_bRedrawTime)
		RedrawMap();

	ReleaseDC(pDc);

	// 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.
}

void CDlgDefectMap::DrawDefectMark(CPoint pt, int defectClass, BOOL isSel)
{
	CDC *pDC = GetDC();

	//int		nFont = 10;
	//int		nOffsetX = 0,nOffsetY = 0;
	//CString strDefect;

	//if(defectClass == DEFECT_OK){
	//	pDC->SetTextColor(COLOR_GREEN);
	//	strDefect = "●";
	//	nOffsetX = 0;
	//	nOffsetY = 4;
	//	nFont = 4;
	//}
	//else if(defectClass == DEFECT_NG){
	//	pDC->SetTextColor(COLOR_RED);
	//	strDefect = "x";
	//	nFont = 10;
	//}

	//CFont font;
	//font.CreateFont(nFont, 0,0,0, FW_BOLD, 0,0,0, DEFAULT_CHARSET,
	//	OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,
	//	DEFAULT_PITCH | FF_DONTCARE, "굴림");

	//CFont *pOldFont = pDC->SelectObject(&font);
	//
	//if(isSel)
	//	pDC->SetTextColor(COLOR_WHITE);

	//pDC->SetBkMode(TRANSPARENT);
	//pDC->SetTextAlign(TA_CENTER);
	//pDC->TextOut(pt.x+nOffsetX,pt.y+nOffsetY,strDefect);		//conter에 맞추기 위해 일정수만큼 offset
	//pDC->SelectObject(pOldFont);

	ReleaseDC(pDC);
}



//void CDlgDefectMap::DrawDefectMark(DEFECT_DATA *data)
//{
//	int defectClass = data->defect_class;
//	BOOL isSel = data->bMark;
//	CPoint pt;
//
//	pt = GetViewPos(data->filmPosX, data->filmPosY);
//	
//	DrawDefectMark(pt, defectClass, isSel);
//	
//}

void CDlgDefectMap::RedrawMap()
{
	//COLED_INSPECTDlg* pView = (COLED_INSPECTDlg*)m_vMain;
	CDC *pDC = GetDC();

	DrawGridLine(pDC);					//defect를 제외한 Grid 그려줌

	/*for(int i=1; i<=m_qDefect.get_count(); i++)
	{
		DEFECT_DATA* data = (DEFECT_DATA*)m_qDefect.search(i);
		DrawDefectMark(data);
	}	*/	

	
	ReleaseDC(pDC);
}



void CDlgDefectMap::DrawGridLine(CDC *pDC)
{

	int width = m_rtArea.Width();
	int height = m_rtArea.Height();
	double dXscale = (double)(width/m_dViewsizex); //1mm당 pixel scalefactor
	double dYscale = (double)(height/m_dViewsizey);
	CString str;

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(COLOR_WHITE);
	CPen *pOldPen,*pGrid;

	pGrid = new CPen(PS_DOT, 1, RGB(85,85,85)	); 
	pOldPen = pDC->SelectObject(pGrid);

	for(int i=0;i<=m_displayGridY;i++)
	{
		pDC->MoveTo(0,(int)(i*(m_dViewsizey/m_displayGridY)*dYscale));
		pDC->LineTo(width,(int)(i*(m_dViewsizey/m_displayGridY)*dYscale));
		str.Format("%4d",(int)(m_nViewSttposy_ctrl_server/1000+(i*m_dViewsizey/(m_displayGridY*1000))));
		if(i<m_displayGridY-1){
			pDC->TextOut(width-33,(int)((m_displayGridY - i)*(m_dViewsizey/m_displayGridY)*dYscale)-37,str);
		}
	}

	for(int i=0;i<m_displayGridX;i++)
	{
		pDC->MoveTo((int)(i*(m_dViewsizex/m_displayGridX)*dXscale),0);
		pDC->LineTo((int)(i*(m_dViewsizex/m_displayGridX)*dXscale),height);
		str.Format("%4d",(int)(m_nViewSttposx_ctrl_server/1000+(i*m_dViewsizex/(m_displayGridX*1000))));
		if(i<m_displayGridX-1 && i%2)
			pDC->TextOut((int)(i*(m_dViewsizex/m_displayGridX)*dXscale)+20, (int)0 ,str);
	}

	
	pDC->SelectObject(pOldPen);
	delete pGrid;	

}

CPoint CDlgDefectMap::GetViewPos(double dSrcx, double dSrcy)
{
	CPoint pt;
	double dXscale = m_rtArea.Width()/(m_dViewsizex/1000); //1mm당 pixel scalefactor
	double dYscale = m_rtArea.Height()/(m_dViewsizey/1000);

	if(m_nViewSttposx_ctrl_server==0 && m_nViewSttposy_ctrl_server==0){
		pt.x = int(dSrcx*dXscale) +mapSttOffsetX;
		pt.y = int((m_rtArea.Height())-dSrcy*dYscale) + mapSttOffsetY;
	}
	else{
		pt.x = int(dXscale*(dSrcx-m_nViewSttposx_ctrl_server/1000)) + mapSttOffsetX;
		pt.y = int( (m_rtArea.Height() - (dYscale*(dSrcy-m_nViewSttposy_ctrl_server/1000) + mapSttOffsetY) ));
	}
	return pt;
}


LRESULT CDlgDefectMap::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	switch(message)	
	{
		/*case WM_INVALIDATE:
			Invalidate();
			break;*/
	}
	return CDialog::WindowProc(message, wParam, lParam);
}

void CDlgDefectMap::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	if(m_startToMove == TRUE){
		m_endPos = point;
	}

	CDialog::OnMouseMove(nFlags, point);
}

void CDlgDefectMap::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(m_startToMove == TRUE){
		if(m_nViewSttposx_ctrl_server != 0 && m_nViewSttposy_ctrl_server != 0)
		{
			m_endPos = point;

			//scaleTrans
			double dXscale = m_rtArea.Width()/(m_dViewsizex/1000); //1mm당 pixel scalefactor
			double dYscale = m_rtArea.Height()/(m_dViewsizey/1000);
			
			CPoint moveDist;

			moveDist.x = -(m_endPos.x-m_startPos.x) * dXscale;
			moveDist.y = +(m_endPos.y-m_startPos.y) * dYscale;

			m_nViewSttposx_ctrl_server += moveDist.x *100;
			m_nViewSttposy_ctrl_server += moveDist.y *100;

			//SendMessage(WM_INVALIDATE, 0,0);
		}
	}
	m_startToMove = FALSE;
	CDialog::OnLButtonUp(nFlags, point);
	//COLED_INSPECTDlg* pView = (COLED_INSPECTDlg*)m_vMain;
	//pView->SetFocus();
}

void CDlgDefectMap::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//COLED_INSPECTDlg* pView = (COLED_INSPECTDlg*)m_vMain;
	//CPoint m_pPoint = point;
	//m_startPos = point;
	//m_startToMove = TRUE;

	//CPoint ptList;
	//double dtmpdist;
	//double dApproch_dist = 100000;
	////DEFECT_DATA* selData = NULL;

	////st
	//for(int i=1; i<=m_qDefect.get_count(); i++)
	//{
	//	DEFECT_DATA* data = (DEFECT_DATA*)m_qDefect.search(i);

	//	ptList = GetViewPos(data->filmPosX, data->filmPosY);

	//	dtmpdist = DISTANCE(ptList.x,ptList.y,m_pPoint.x,m_pPoint.y);

	//	//CString str;
	//	//str.Format("마크좌표:%d, %d, 클릭좌표:%d, %d", ptList.x, ptList.y, m_pPoint.x, m_pPoint.y);
	//	//pView->AddtoList(str);

	//	if(m_selDefectData == NULL)
	//	{
	//		dApproch_dist = dtmpdist;
	//		//selData = data;
	//		m_selDefectData = data;
	//	}
	//	else if(dApproch_dist>dtmpdist)
	//	{
	//		//selData = data;
	//		m_selDefectData = data;
	//		dApproch_dist = dtmpdist;
	//	}
	//}

	//if(m_selDefectData != NULL && dApproch_dist < 10)
	//{ 
	//	SelectNewDefect();

	//	int nSaveQueueCnt = pView->m_Project->m_defectSaveQueue.get_count();
	//	int nQueueCnt = pView->m_defectMap->m_qDefect.get_count();

	//	for(int i=0; i<nSaveQueueCnt; i++){
	//		DEFECT_DATA* data = (DEFECT_DATA*)pView->m_Project->m_defectSaveQueue.search(i);
	//		int zoneIndex = data->zoneIdx;
	//		int defectIndex = data->defectIdx;

	//		if(zoneIndex == m_selDefectData->zoneIdx && defectIndex == m_selDefectData->defectIdx){
	//			pView->m_Project->m_currentDefectIndex = i;
	//			CString str;
	//			str.Format("Defect No < %4d / %4d >", pView->m_Project->m_currentDefectIndex, nSaveQueueCnt);
	//			pView->m_defectConfirmProcessText.SetText(str);
	//		}
	//	}
	//}
	//
	CDialog::OnLButtonDown(nFlags, point);

	//COLED_INSPECTDlg* pView = (COLED_INSPECTDlg*)m_vMain;
	//pView->SetFocus();
}

void CDlgDefectMap::SelectNewDefect()
{
	/*COLED_INSPECTDlg* pView = (COLED_INSPECTDlg*)m_vMain;

	if(pView->m_Project->isMoveDone != TRUE && pView->m_Project->workThreadMove != FALSE){
		return;
	}*/

	//CDC* pDC = pView->GetDC();

	//m_pBadpointClick_file[1] = m_pBadpointClick_file[0];
	////이전 표시를 지운다.
	//if(m_pBadpointClick_file[0])
	//{
	//	m_pBadpointClick_file[0]->bMark = FALSE;
	//	DrawDefectMark(GetViewPos(m_pBadpointClick_file[0]->filmPosX, m_pBadpointClick_file[0]->filmPosY), m_pBadpointClick_file[0]->defect_class, m_pBadpointClick_file[0]->bMark);
	//}
	////새로운 표시를 한다.
	//m_pBadpointClick_file[0] = m_selDefectData;
	//m_pBadpointClick_file[0]->bMark = TRUE;
	//DrawDefectMark(GetViewPos(m_pBadpointClick_file[0]->filmPosX, m_pBadpointClick_file[0]->filmPosY), m_pBadpointClick_file[0]->defect_class, m_pBadpointClick_file[0]->bMark);

	//CString str;
	//str.Format("No.Sel [%d]", m_selDefectData->zoneIdx);
	//pView->AddtoList(str);

	////데이터표시
	//CString str2;
	//if(m_selDefectData->defect_class == DEFECT_OK){
	//	str2 = "OK";
	//	pView->SetDefectJudge(0);
	//}
	//else if(m_selDefectData->defect_class == DEFECT_NG){
	//	str2 = "NG";
	//	pView->SetDefectJudge(1);
	//}

	////170530 lgh
	//if(m_selDefectData->inOffset == TRUE){
	//	str2 = "OK";
	//	pView->SetDefectJudge1(0);
	//}
	//else if(m_selDefectData->inOffset == FALSE){
	//	str2 = "NG";
	//	pView->SetDefectJudge1(1);
	//}

	//if(m_selDefectData->defect_class == DEFECT_NG){
	//	CString str3;
	//	str3.Format("\n No %04d \n\n Value(Dark) = %5.3f \n\n SizeX = %5.3f \n\n SizeY = %5.3f \n\n Ratio = %5.3f, %5.3f \n\n Pos = %5.3f, %5.3f",
	//		m_selDefectData->zoneIdx
	//		,m_selDefectData->dValue
	//		,m_selDefectData->sizeX
	//		,m_selDefectData->sizeY
	//		,m_selDefectData->ratio1
	//		,m_selDefectData->ratio2
	//		,m_selDefectData->filmPosX
	//		,m_selDefectData->filmPosY
	//		);

	//	pView->m_labelClickInfo.SetText(str3);

	//	//이미지표시
	//	pView->m_Project->CopyImages(m_selDefectData->filename, pView->m_Project->m_pImageDefect[1][0]->GetImagePtr());
	//	pView->m_Project->DrawClickImage(pDC);
	//}
	//else{
	//	
	//	if(m_selDefectData->filename != ""){
	//		//이미지표시
	//		pView->m_Project->CopyImages(m_selDefectData->filename, pView->m_Project->m_pImageDefect[1][0]->GetImagePtr());
	//		pView->m_Project->DrawClickImage(pDC);
	//		CString str3;
	//		str3.Format("\n No %04d \n\n Value(Dark) = %5.3f \n\n SizeX = %5.3f \n\n SizeY = %5.3f \n\n Ratio = %5.3f, %5.3f \n\n Pos = %5.3f, %5.3f",
	//			m_selDefectData->zoneIdx
	//			,m_selDefectData->dValue
	//			,m_selDefectData->sizeX
	//			,m_selDefectData->sizeY
	//			,m_selDefectData->ratio1
	//			,m_selDefectData->ratio2
	//			,m_selDefectData->filmPosX
	//			,m_selDefectData->filmPosY
	//			);

	//		pView->m_labelClickInfo.SetText(str3);
	//	}
	//	else{
	//		memset(pView->m_Project->m_pImageDefect[1][0]->GetImagePtr(), 0, BAD_IMG_WIDTH*BAD_IMG_HEIGHT);
	//		pView->m_labelClickInfo.SetText("");
	//	}

	//	pView->m_Project->DrawClickImage(pDC);
	//
	//}

	////Z모션 Move
	////170518 lgh
	//double motionPosZ;
	//if(pView->m_chk55Inch == TRUE && pView->m_chk65Inch == FALSE)
	//	motionPosZ = pView->m_Project->calibData55[m_selDefectData->zoneIdx][1];
	//if(pView->m_chk55Inch == FALSE && pView->m_chk65Inch == TRUE)
	//	motionPosZ = pView->m_Project->calibData65[m_selDefectData->zoneIdx][1];

	//int nMotionPosZ = motionPosZ / pView->m_inspectParam->MotionScaleZ;
	//m_nMotionPosZ = nMotionPosZ;
	//pView->m_Project->m_ZAxisMotion->MovePosABS(-nMotionPosZ);

	//pView->m_Project->SetMotionSpeedManual(2);

	////선택된 포인트로 이동
	//float pointMoveOffsetX = 0;
	//float pointMoveOffsetY = 0;

	//if(m_pBadpointClick_file[0]->defect_class == DEFECT_NG){
	//	pointMoveOffsetX = pView->m_inspectParam->PointMoveOffsetX;
	//	pointMoveOffsetY = pView->m_inspectParam->PointMoveOffsetY;
	//}
	//pView->m_Project->SetCamView(m_selDefectData->filmPosX+pointMoveOffsetX, m_selDefectData->filmPosY+pointMoveOffsetY);

	//pView->Invalidate();

	//pView->ReleaseDC(pDC);
}

void CDlgDefectMap::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	

	CDialog::OnLButtonDblClk(nFlags, point);
}

void CDlgDefectMap::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int offsetX = 0;
	int offsetY = 0;

	if(m_dViewsizey == m_maxYzone*50)	//전체
	{
		m_nViewSttposx_ctrl_server = 0;
		m_nViewSttposy_ctrl_server = 0;
		m_dViewsizex = m_maxXzone*1000;
		m_dViewsizey = m_maxYzone*1000;
	}	
	else	//확대
	{
		double dXscale = m_dViewsizex/m_rtArea.Width();
		double dYscale = m_dViewsizey/m_rtArea.Height();
		m_nViewSttposx_ctrl_server +=(int)dXscale*(point.x - mapSttOffsetX);
		m_nViewSttposy_ctrl_server +=(int)dYscale*(m_rtArea.Height()- (point.y - mapSttOffsetY));
		m_dViewsizex = m_maxXzone*50;
		m_dViewsizey = m_maxYzone*50;
		m_nViewSttposx_ctrl_server -= (int)m_dViewsizex/2;
		m_nViewSttposy_ctrl_server -= (int)m_dViewsizey/2;
	}

	//SendMessage(WM_INVALIDATE, 0, 0);

	CDialog::OnRButtonDown(nFlags, point);

	//COLED_INSPECTDlg* pView = (COLED_INSPECTDlg*)m_vMain;
	//pView->SetFocus();
}

BOOL CDlgDefectMap::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return FALSE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
