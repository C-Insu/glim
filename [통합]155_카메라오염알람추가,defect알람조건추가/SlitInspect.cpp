//#include "stdafx.h"
//#include "VisWeb.h"
//#include "math.h"
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////																																				//
////		Slit 조명을 사용한 Defect검사																											//
////																																				//
////													2008.5.15    NextEye  고영우   ywko@nexteye.com												//
////																																				//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
////Local 데이타 (이 File에서만 사용한다.)===========================================================================================================
//int		l_Value[1024];										//수직 한줄의 픽셀데이타 (2줄의 평균값)
//float	l_Edge[1024];										//수직한줄에 대한 Edge구할때 사용
//int		l_Dir[1024];										//수직 한줄의 Edge에 대한 정보 
//
//float l_EdgeArray[I_HALFWIDTH][MAX_Y_EDGE];					//X방향으로 W2B Edge는 짝수에 B2W Edge는 홀수에 
//int   l_BlackCenterGray[I_HALFWIDTH][MAX_Y_EDGE][4];		//X방향으로 검은색 Center의 Gray Value  0: Gray Value,1:폭(um)  2: X좌표, 3:Y좌표 
//int   l_WhiteCenterGray[I_HALFWIDTH][MAX_Y_EDGE][4];		//X방향으로 흰색 Center의 Gray Value	0: Gray Value,1:폭(um)  2: X좌표, 3:Y좌표 
//int   l_B, l_W;
////=================================================================================================================================================
//
//
////Global 데이타 : 전영역에서 사용한다. =============================================================================================================
//int			g_nLeftRightCut;	//Save되는 변수 (검사기 별로 다른 변수)  0 : ROI영역을 Full로 사용, 1: Left Cut,  2:Right Cut  3:All Cut
//TEACHDATA	g_Teach;			//Save되는 변수 (검사기 모두 같이 사용하는 변수)
//
//FRAMERESULT g_FrameResult;		//전체 Frame영역의 결과가 담기는 변수				[Save되지 않고 프로그램 실행중에만 사용]
//RESULTDATA  g_result;			//I_WIDTH x I_HEIGHT 영역의 검사 결과가 담기는 변수 [Save되지 않고 프로그램 실행중에만 사용] 
//
//
//
////++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////+++++++++++++++++++++++++++++++++++++++++++++++++++ VMaster에서 사용하는 함수 ++++++++++++++++++++++++++++++++++++++++++++++++++++++
//#ifdef USE_VMASTER
//void CCalibration::OnButtonEdge()  //ROI검사 
//{
//	UpdateData(true);
//	l_B=m_Bth;
//	l_W=m_Wth;
//
//
//	LPBYTE fm, fmR;			
//	int i, j,k, pitch;
//
//	clock_t starttime, endtime; // Time 구하기
//	double dElapseTime;         // 경과된 시간
//	CString Str;
//
//	CMainFrame *pMainFrame=(CMainFrame *)AfxGetMainWnd();  //메인 프레임 pointer를 얻음
//	pMainFrame->GetImageInfo(&fm, &fmR, &pitch);
//	pMainFrame->GetROIInfo(&m_x1, &m_y1, &m_x2, &m_y2);
//	pMainFrame->GetCurrentImage(&fm);	
//	
//	Invalidate();	//반복해서 찍을때 화면 Clear
//	UpdateWindow();
//
//	starttime=clock();  // 시작시간
//
//
//
///*	g_Teach.nSkip=2;			//Fixed Value
//	g_Teach.nMinEdgeCount=7;	//최소 Edge 수 
//	g_Teach.nMaxMinRange=20;	//최대 밝기-최소 밝기를 구하는 영역 
//	g_Teach.nMinDepth=m_nEdgeDepth; //30정도가 적절함
//
//	g_Teach.dBlackMin=m_dBlackMin;
//	g_Teach.dBlackMax=m_dBlackMax;
//	g_Teach.dWhiteMin=m_dWhiteMin;
//	g_Teach.dWhiteMax=m_dWhiteMax;
//	g_Teach.dPeekMax=m_dMaxPeek;
//
//	//Center Gray값 검사 
//	g_Teach.nBlackValueSlope=m_nBlackSlope;
//	g_Teach.nWhiteValueSlope=m_nWhiteSlope;
//	g_Teach.nBlackValueMaxMin=m_nBlackCenterMaxMin;
//	g_Teach.nWhiteValueMaxMin=m_nWhiteCenterMaxMin;
//
//	//두께검사 데이타 
//	g_Teach.dBlackThickSlope=m_dBlackWidthSlope;
//	g_Teach.dWhiteThickSlope=m_dWhiteWidthSlope;
//	g_Teach.dBlackThickMaxMin=m_dBlackWidthMaxMin;
//	g_Teach.dWhiteThickMaxMin=m_dWhiteWidthMaxMin;
//*/
//
//
//
//	for(i=0;i<1;i++)
//	{
//		SLIT_InspectROI(fm, m_x1, m_y1, m_x2, m_y2, pitch, 0, g_Teach, &g_result);
//	}
//
//
//	Str.Format("Avg White=%5.2lf,  Black=%5.2lf", 	g_result.dWhiteWidth, g_result.dBlackWidth);
//	GetDlgItem(IDC_EDIT_RESULT)->SetWindowText(Str);
//		
//#ifdef SHOW_GRAPHIC
//	CDC *pDC=GetDC();
//	bool flag;
//	CPen *oldPen, *pen;
//
//	pen=new CPen(PS_SOLID, 1, RGB(255,0,0));
//	oldPen=pDC->SelectObject(pen);
//	for(i=0;i<=MAX_Y_EDGE;i++)
//	{
//		delete pen;
//		pen=new CPen(PS_SOLID, 1, RGB(i*80+50,i*60,i*120+60));
//		pDC->SelectObject(pen);
//		flag=false;
//		for(j=0;j<g_result.nXEdgeCount;j++)
//		{
//			if(!flag) 
//			{
//				if(l_EdgeArray[j][i])
//				{
//					pDC->MoveTo((g_result.nLeft+j*2)*2, 8+l_EdgeArray[j][i]*2);
//					flag=true;		
//				}
//			}	
//			else
//			{
//				if(l_EdgeArray[j][i])
//					pDC->LineTo((g_result.nLeft+j*2)*2, 8+l_EdgeArray[j][i]*2);
//				else
//					flag=false;
//			}
//		}
//	}
//	delete pen;
//	pDC->SelectObject(oldPen);
//
//	if(m_bShowCross)
//	{
//
//		//두께 Display-----------------------------------
//		for(k=0;k<g_result.nNGCountThick;k++)
//		{
//			for(i=g_result.nNGThickX[k]*2-5;i<g_result.nNGThickX[k]*2+5;i++)
//				pDC->SetPixel(i,10+g_result.nNGThickY[k]*2, RGB(0,255,0));
//
//			for(i=g_result.nNGThickY[k]*2-5;i<g_result.nNGThickY[k]*2+5;i++)
//				pDC->SetPixel(g_result.nNGThickX[k]*2, 10+i, RGB(0,255,0));
//		}
//		for(k=0;k<g_result.nNGThickSlope;k++)
//		{
//			for(i=g_result.nNGThickSlopeX[k]*2-5;i<g_result.nNGThickSlopeX[k]*2+5;i++)
//				pDC->SetPixel(i,10+g_result.nNGThickSlopeY[k]*2, RGB(0,128,0));
//
//			for(i=g_result.nNGThickSlopeY[k]*2-5;i<g_result.nNGThickSlopeY[k]*2+5;i++)
//				pDC->SetPixel(g_result.nNGThickSlopeX[k]*2, 10+i, RGB(0,128,0));
//		}
//
//		//끊어짐-----------
//		for(k=0;k<g_result.nNGLineBroken;k++)
//		{
//			for(i=g_result.nNGLineBrokenX[k]*2-5;i<g_result.nNGLineBrokenX[k]*2+5;i++)
//				pDC->SetPixel(i,10+g_result.nNGLineBrokenY[k]*2, RGB(255,0,0));
//
//			for(i=g_result.nNGLineBrokenY[k]*2-5;i<g_result.nNGLineBrokenY[k]*2+5;i++)
//				pDC->SetPixel(g_result.nNGLineBrokenX[k]*2, 10+i, RGB(255,0,0));
//		}
//
//		//추가됨 ---------------------
//		for(k=0;k<g_result.nNGLineAdd;k++)
//		{
//			for(i=g_result.nNGLineAddX[k]*2-5;i<g_result.nNGLineAddX[k]*2+5;i++)
//				pDC->SetPixel(i,10+g_result.nNGLineAddY[k]*2, RGB(0,0,255));
//
//			for(i=g_result.nNGLineAddY[k]*2-5;i<g_result.nNGLineAddY[k]*2+5;i++)
//				pDC->SetPixel(g_result.nNGLineAddX[k]*2, 10+i, RGB(0,0,255));
//		}
//
//		//중간 밝기 변화 
//		for(k=0;k<g_result.nNGCenterGray;k++)
//		{
//			for(i=g_result.nNGCenterGrayX[k]*2-5;i<g_result.nNGCenterGrayX[k]*2+5;i++)
//				pDC->SetPixel(i,10+g_result.nNGCenterGrayY[k]*2, RGB(255,128,0));
//
//			for(i=g_result.nNGCenterGrayY[k]*2-5;i<g_result.nNGCenterGrayY[k]*2+5;i++)
//				pDC->SetPixel(g_result.nNGCenterGrayX[k]*2, 10+i, RGB(255,128,0));
//		}
//
//		//Edge검사 Pink
//		for(k=0;k<g_result.nNGEdgePeek;k++)
//		{
//			for(i=g_result.nNGEdgePeekX[k]*2-5;i<g_result.nNGEdgePeekX[k]*2+5;i++)
//				pDC->SetPixel(i,10+g_result.nNGEdgePeekY[k]*2, RGB(255,0,255));
//
//			for(i=g_result.nNGEdgePeekY[k]*2-5;i<g_result.nNGEdgePeekY[k]*2+5;i++)
//				pDC->SetPixel(g_result.nNGEdgePeekX[k]*2, 10+i, RGB(255,0,255));
//		}
//
//	}
//	ReleaseDC(pDC);
//#endif
//
//    endtime=clock();
//	dElapseTime=(double)(endtime-starttime)*1000/CLOCKS_PER_SEC;
//    Str.Format("%10.3lf", dElapseTime);
////	MessageBox(Str);
//
//}
//
//void CCalibration::OnButtonSlitInspect()  //전체영역 검사 
//{
//	LPBYTE fm, fmR;			
//	int i, j,k, pitch;
//	clock_t starttime, endtime; // Time 구하기
//	double dElapseTime;         // 경과된 시간
//	CString Str;
//
//	CMainFrame *pMainFrame=(CMainFrame *)AfxGetMainWnd();  //메인 프레임 pointer를 얻음
//	pMainFrame->GetImageInfo(&fm, &fmR, &pitch);
//	pMainFrame->GetROIInfo(&m_x1, &m_y1, &m_x2, &m_y2);
//	pMainFrame->GetCurrentImage(&fm);	
//
////	starttime=clock();  // 시작시간
//	
//	SLIT_Inspect(fm, m_x1, m_y1, m_x2, m_y2, I_WIDTH*2, 0);
//
////	endtime=clock();
////	dElapseTime=(double)(endtime-starttime)*1000/CLOCKS_PER_SEC;
////	Str.Format("%10.3lf", dElapseTime);
////	MessageBox(Str);
//}
//#endif
////++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//
//
////전체영역을 검사하는 함수, Teaching Data는 g_Teach에 있는 데이타를 사용하고, 그 결과는 g_FrameResult에 넣는다.  -------------------------
//int 
//#ifdef USE_VMASTER
//CCalibration::
//#endif
//SLIT_Inspect(LPBYTE fm, int left, int top, int right, int bottom, int pitch, int nLeftRight)  
//{
//	int i, ok=-1;
//	int nLeftCut, nRightCut;
//		
//	if(nLeftRight==1) nLeftCut=1;
//	else              nLeftCut=0;
//
//	if(nLeftRight==2) nRightCut=2;
//	else              nRightCut=0;
//
//	g_FrameResult.nNGCount=0;
//	g_FrameResult.dBlackWidth=g_FrameResult.dWhiteWidth=0;
//	for(i=0;i<g_Teach.nOneFrameGrabCount;i++)
//	{
//		SLIT_InspectROI(fm, 0,			i*I_HEIGHT, I_WIDTH,	(i+1)*I_HEIGHT , I_WIDTH*2, nLeftCut, g_Teach, &g_result);
//		SLIT_InspectROIResult(0, i*I_HEIGHT, g_result);
//
//		SLIT_InspectROI(fm, I_WIDTH,	i*I_HEIGHT, I_WIDTH*2,	(i+1)*I_HEIGHT , I_WIDTH*2, nRightCut, g_Teach, &g_result);
//		SLIT_InspectROIResult(I_WIDTH,  i*I_HEIGHT, g_result);
//	}
//
//	//결과 정리 -------------------------------------------------------------------------------------------------------------
//	g_FrameResult.dBlackWidth/=(2*g_Teach.nOneFrameGrabCount);	//Frame 평균 Black Line폭 
//	g_FrameResult.dWhiteWidth/=(2*g_Teach.nOneFrameGrabCount);	//Frame 평균 White Line폭 
//
//	SLIT_RemoveAdjacent(100,100, MAX_FRAME_NG);	//이웃하는 불량 하나로 붙임.
//
//	for(i=0;i<g_FrameResult.nNGCount;i++)		//Y방향 실제길이로 표시 
//	{
//		if(g_FrameResult.nNGPosX[i]<I_WIDTH)
//			g_FrameResult.dNGPosXReal[i]=60.0*g_FrameResult.nNGPosX[i]/I_WIDTH;
//		else
//			g_FrameResult.dNGPosXReal[i]=57+60.0*(g_FrameResult.nNGPosX[i]-I_WIDTH)/I_WIDTH;
//
//		g_FrameResult.dNGPosYReal[i]=g_Teach.dOneFrameLength*g_FrameResult.nNGPosY[i]/(I_HEIGHT*g_Teach.nOneFrameGrabCount);
//	}
//	//-----------------------------------------------------------------------------------------------------------------------
//
//
//#ifdef SHOW_GRAPHIC  //결과위치 표시 하기 위해서 임시로 만들어 둚.---------------------------------
//	CString str, strSum="";
//
//	str.Format("Black Line=%8.3lf  White Line=%8.3lf\n", g_FrameResult.dBlackWidth, g_FrameResult.dWhiteWidth);
//	strSum+=str;
//	for(i=0;i<g_FrameResult.nNGCount;i++)
//	{
//		str.Format("(%d, %d)\n", g_FrameResult.nNGPosX[i], g_FrameResult.nNGPosY[i]);
//		strSum+=str;
//	}
//	MessageBox(strSum);
//#endif	//-----------------------------------------------------------------------------------------
//
//	ok=0;
////done:	
//	return ok;
//}
////----------------------------------------------------------------------------------------------------------------------------------------
//
//
//
//int 
//#ifdef USE_VMASTER
//CCalibration::
//#endif
//SLIT_InspectROI(LPBYTE fm, int left, int top, int right, int bottom, int pitch, int nLeftRight, TEACHDATA data, RESULTDATA *result)
//{
//	int ok=-1;
//		
//	SLIT_EdgeArray(fm, left, top, right, bottom, pitch, nLeftRight, data, result);
//	SLIT_LineData(fm, pitch, g_Teach, result);
//
//	ok=0;
////done:
//	
//	return ok;
//}
////nLeftRight = 0 : ROI영역을 Full로 사용
////			 = 1 : Left 영역 일부 못씀
////			 = 2 : RIght 영역 일부 못씀
////			 = 3 : Left, Right일부 못씀 
//
//int 
//#ifdef USE_VMASTER
//CCalibration::
//#endif
//SLIT_EdgeArray(LPBYTE fm, int left, int top, int right, int bottom, int pitch, int nLeftRight, TEACHDATA data, RESULTDATA *result)
//{
//	int ok=-1;
//	int i,j;//, k;
//	int nEdge;			//한줄에서 구한 Edge수 
//	int left_, right_;	//왼쪽 오른쪽 Boundary를 제외하고 영역범위 
//	int nBlackCount, nWhiteCount; //평균 두께 구할때 사용 
//	int nSkipX=data.nSkip;		  //항상 2를 사용함.
//	double dBlackWidth, dWhiteWidth;
//	double dBlackWidthSum, dWhiteWidthSum;
//	int nXEdgeCount=0;
////	int nW2BCount, nB2WCount;
////	int nY;
////	double dY;
//	LPBYTE fmT;
//	bool bIsYlineError, FirstLineSuccess=false;  //수직 Y Line에서 Error발생, 첫번째 Y Line성공시 True
////----초기화 -----------------------------
//	memset(result, 0, sizeof(RESULTDATA));
//	memset(l_EdgeArray, 0, MAX_Y_EDGE*I_HALFWIDTH*sizeof(float));
////----------------------------------------
//
//
//	if(nLeftRight==1)		{ left_=SLIT_FindLeftEnd(1, fm, left, top, right, bottom, pitch, data); right_=right;}
//	else if(nLeftRight==2)	{ left_= left; right_=SLIT_FindLeftEnd(2, fm, left, top, right, bottom, pitch, data);}
//	else if(nLeftRight==3)	{ left_=SLIT_FindLeftEnd(1, fm, left, top, right, bottom, pitch, data); right_=SLIT_FindLeftEnd(2, fm, left, top, right, bottom, pitch, data);}
//	else					{ left_=left; right_=right;}
//	
//	if(nSkipX<2) nSkipX=2;
//
//#ifdef SHOW_GRAPHIC
//	CDC *pDC=GetDC();
//#endif
//
//	nBlackCount=nWhiteCount=0;
//	dBlackWidthSum=dWhiteWidthSum=0;
//	nXEdgeCount=0;
//
//	for(j=left_;j<right_;j+=nSkipX)
//	{
//		for(i=top;i<bottom;i++)
//		{	
//			fmT=fm+pitch*i+j;
//			l_Value[i-top]=(*(fmT)+*(fmT+1))/2;
//		}
//		nEdge=SLIT_FindYEdge(l_Value, (bottom-top),data.nMinDepth, l_Edge, l_Dir); //Y방향 Line으로 Edge를 구함.
//		if(nEdge>MAX_Y_EDGE-20) nEdge=MAX_Y_EDGE-20;
//
//		//1개의 Edge로 부터 흑/백 선의 두께를 구해서 양/불을 판정한다 --------------------------------------
//		bIsYlineError=false;
//		for(i=1;i<nEdge;i++)
//		{
//			if(l_Dir[i]==0) //White->Black
//			{
//				dWhiteWidth=l_Edge[i]-l_Edge[i-1]; //흰선 두께 
//				dWhiteWidthSum+=dWhiteWidth;
//				nWhiteCount++;
//
//				//i가 1이거나, (nEdge-1)인 경우는 작은 값이 나올수 있으므로 작은 불량은 포함하지 않는다.
//				if(data.bWhiteThickness && ((i!=1 && i!=(nEdge-1) && dWhiteWidth<data.dWhiteMin) ||  dWhiteWidth> data.dWhiteMax) )
//				{
//					result->nNGThickX[result->nNGCountThick]=j;
//					result->nNGThickY[result->nNGCountThick]=int((l_Edge[i]+l_Edge[i-1])*0.5);
//					result->dNGThickness[result->nNGCountThick]=dWhiteWidth;
//					result->nNGCountThick++;
//					bIsYlineError=true;
//				}		
//			}
//			else
//			{
//				dBlackWidth=l_Edge[i]-l_Edge[i-1];	//흑선 두께 
//				dBlackWidthSum+=dBlackWidth; nBlackCount++;  //평균두께 구할떼 사용
//
//				//i가 1이거나, (nEdge-1)인 경우는 작은 값이 나올수 있으므로 작은 불량은 포함하지 않는다.
//				if(data.bBlackThickness && ((i!=1 && i!=(nEdge-1) && dBlackWidth<data.dBlackMin) ||  dBlackWidth> data.dBlackMax) )
//				{
//					result->nNGThickX[result->nNGCountThick]=j;
//					result->nNGThickY[result->nNGCountThick]=int((l_Edge[i]+l_Edge[i-1])*0.5);
//					result->dNGThickness[result->nNGCountThick]=dBlackWidth;
//					result->nNGCountThick++;
//					bIsYlineError=true;
//				}		
//			}
//			if(result->nNGCountThick>=MAX_NG_POINTS) break;
//		}
//		if(result->nNGCountThick>=MAX_NG_POINTS) break;
//		//---------------------------------------------------------------------------------------------------
//
//		//이웃하는 Edge데이타로 부터 양불을 판정한다. -------------------------------------------------------
//		if(nEdge>=data.nMinEdgeCount && (!bIsYlineError || FirstLineSuccess))
//		{
//			if(SLIT_MakeLine(!FirstLineSuccess, nXEdgeCount, nEdge, l_Edge, l_Dir, j, data, result)==0) FirstLineSuccess=true;
//		}
//		else
//		{
//			if(result->nNGLineBroken<MAX_NG_POINTS)
//			{
//				result->nNGLineBrokenX[result->nNGLineBroken]=j;
//				result->nNGLineBrokenY[result->nNGLineBroken]=int((bottom-top)*0.5);
//				result->nNGLineBroken++;
//			}
//		}
//		//---------------------------------------------------------------------------------------------------
// 
//		nXEdgeCount++;
//
//
////구한Edge Display -------------------------------------------------
//#ifdef SHOW_GRAPHIC  
//		for(i=0;i<nEdge;i++)
//		{
//			if(l_Dir[i]==1) // Black->White
//				pDC->SetPixel(j*2, 10+l_Edge[i]*2, RGB(255,0,0));
//			else if(l_Dir[i]==0)
//				pDC->SetPixel(j*2, 10+l_Edge[i]*2, RGB(0,255,0));
//			else
//				pDC->SetPixel(j*2, 10+l_Edge[i]*2, RGB(0,0,255));
//		}
//#endif
////------------------------------------------------------------------
//	}
//
//	result->nTop =top;
//	result->nLeft=left_;
//	result->nXEdgeCount=nXEdgeCount;
//	if(nBlackCount) result->dBlackWidth=dBlackWidthSum/nBlackCount;
//	if(nWhiteCount) result->dWhiteWidth=dWhiteWidthSum/nWhiteCount;
//
//	ok=0;
////done:
//
//#ifdef SHOW_GRAPHIC
//	ReleaseDC(pDC);
//#endif
//	
//	return ok;
//}
//int 
//#ifdef USE_VMASTER
//CCalibration::
//#endif
//SLIT_LineData(LPBYTE fm, int pitch, TEACHDATA data, RESULTDATA *result)
//{
//	int i,j,k,nY;
//	int ok=-1;
//	double dY;
//	int nXOffset=result->nLeft;
//	int nBlackStart=0, nWhiteStart=0;
//	int nTopLine=0;
//
//
//	memset(l_BlackCenterGray,0, 4*I_HALFWIDTH*MAX_Y_EDGE*sizeof(int));
//	memset(l_WhiteCenterGray,0, 4*I_HALFWIDTH*MAX_Y_EDGE*sizeof(int));
//	
//	for(i=0;i<MAX_Y_EDGE;i++)
//	{
//		if(l_EdgeArray[0][i] && i%2==0)
//		{
//			nBlackStart=i;
//			break;
//		}
//	}		
//	for(i=0;i<MAX_Y_EDGE;i++)
//	{
//		if(l_EdgeArray[0][i] && i%2==1)
//		{
//			nWhiteStart=i;
//			break;
//		}
//	}	
//
//	//구한 l_EdgeArray 데이타로 부터 흑선, 흰선의 중심의 Gray Value와 선의 두께를 구한다.
//	for(i=0;i<MAX_Y_EDGE-1;i++)
//	{
//		if(l_EdgeArray[0][i]==0) continue;
//		
//		if(nTopLine==0)
//		{	
//			nTopLine=i;	//맨 첫번째 Edge Line을 찾는다.
//			continue;	//맨 첫번째 Edge Line과 쌍을 이루는 흑선/백선 은 처리하지 않는다.
//		}
//
//		if(i%2==0) //W2B
//		{
//			for(j=0;j<result->nXEdgeCount;j++)
//			{
//				if(l_EdgeArray[j][i] && l_EdgeArray[j][i+1])
//				{
//					dY=result->nTop+(l_EdgeArray[j][i]+l_EdgeArray[j][i+1])*0.5;
//					nY=(int)(dY);
//					dY=dY-nY;
////					l_BlackCenterGray[j][i][0]=*(fm+pitch*nY+nXOffset+j*2)*(1-dY)+*(fm+pitch*(nY+1)+nXOffset+j*2)*dY+
////											   *(fm+pitch*nY+nXOffset+j*2+1)*(1-dY)+*(fm+pitch*(nY+1)+nXOffset+j*2+1)*dY)*0.5;
//					l_BlackCenterGray[j][i][1]=(l_EdgeArray[j][i+1]-l_EdgeArray[j][i])*1000; //폭 (um)
//					l_BlackCenterGray[j][i][2]=nXOffset+j*2;
//					l_BlackCenterGray[j][i][3]=(l_EdgeArray[j][i]+l_EdgeArray[j][i+1])*0.5;
//				}
//			}	
//		}
//		else
//		{
//			for(j=0;j<result->nXEdgeCount;j++)
//			{
//				if(l_EdgeArray[j][i] && l_EdgeArray[j][i+1])
//				{
//					dY=result->nTop+(l_EdgeArray[j][i]+l_EdgeArray[j][i+1])*0.5;
//					nY=(int)(dY);
//					dY=dY-nY;
//					l_WhiteCenterGray[j][i][0]=(*(fm+pitch*nY+nXOffset+j*2)*(1-dY)+*(fm+pitch*(nY+1)+nXOffset+j*2)*dY+
//											 *(fm+pitch*nY+nXOffset+j*2+1)*(1-dY)+*(fm+pitch*(nY+1)+nXOffset+j*2+1)*dY)*0.5;
//					l_WhiteCenterGray[j][i][1]=(l_EdgeArray[j][i+1]-l_EdgeArray[j][i])*1000;  //폭 (um)
//					l_WhiteCenterGray[j][i][2]=nXOffset+j*2;
//					l_WhiteCenterGray[j][i][3]=(l_EdgeArray[j][i]+l_EdgeArray[j][i+1])*0.5;
//				}
//			}	
//		}
//	}
//
//	int nDiff, nMin, nMax;
//	double dDiff;
//
//
//	//모든 선들의 튐 검사 --------------------------------------------------------------------
//	if(data.bXEdgeSlope)
//	{
//		for(i=0;i<MAX_Y_EDGE;i++)
//		{
//			if(l_EdgeArray[0][i]==0) continue;
//
//			for(j=0;j<result->nXEdgeCount-2;j++)
//			{
//				if(l_EdgeArray[j][i] && l_EdgeArray[j+2][i])
//				{
//					dDiff=l_EdgeArray[j][i]-l_EdgeArray[j+2][i];
//					if(dDiff<0) dDiff*=-1;
//
//					if(dDiff>data.dPeekMax && result->nNGEdgePeek<MAX_NG_POINTS)
//					{
//						result->nNGEdgePeekX[result->nNGEdgePeek]=nXOffset+j*2;
//						result->nNGEdgePeekY[result->nNGEdgePeek]=l_EdgeArray[j][i];
//						result->dNGEdgePeek[result->nNGEdgePeek++]=dDiff;
//					}
//				}
//			}
//		}
//	}
//
//
//	//흑선 검사 -------------------------------------------------------------------------------
//	if(data.bBlackValueShortChange || data.bBlackThickShortChange)
//	{
//		for(i=0;i<MAX_Y_EDGE;i++)
//		{
//			if(l_BlackCenterGray[0][i][3]==0 || i==nTopLine) continue;
//
//			for(j=0;j<result->nXEdgeCount-2;j++)
//			{
//				
//				if(data.bBlackValueShortChange && l_BlackCenterGray[j][i][3] && l_BlackCenterGray[j+1][i][3])
//				{
//					//흑선 중심의 밝기 기울기 검사
//					nDiff=l_BlackCenterGray[j][i][0]-l_BlackCenterGray[j+1][i][0];
//					if(nDiff<0) nDiff*=-1;
//					if(nDiff>data.nBlackValueSlope && result->nNGCenterGray<MAX_NG_POINTS)
//					{
//						result->nNGCenterGrayX[result->nNGCenterGray]=l_BlackCenterGray[j][i][2];
//						result->nNGCenterGrayY[result->nNGCenterGray]=l_BlackCenterGray[j][i][3];
//						result->dNGCenterGray[result->nNGCenterGray++]=nDiff;
//					}
//				}
//				if(data.bBlackThickShortChange && l_BlackCenterGray[j][i][3] && l_BlackCenterGray[j+2][i][3])
//				{
//					//흑선의 두께의 변화 검사 
//					dDiff=l_BlackCenterGray[j][i][1]-l_BlackCenterGray[j+2][i][1];
//					if(dDiff<0) dDiff*=-1;
//					if(dDiff>data.dBlackThickSlope*1000 && result->nNGThickSlope<MAX_NG_POINTS)
//					{
//						result->nNGThickSlopeX[result->nNGThickSlope]=l_BlackCenterGray[j][i][2];
//						result->nNGThickSlopeY[result->nNGThickSlope]=l_BlackCenterGray[j][i][3];
//						result->dNGThickSlope[result->nNGThickSlope++]=dDiff;
//					}
//				}
//			}
//		}
//	}
//	//흑선 중심의 밝기의 구간 변동값 구함.--------------------------------------------------------------------------
//	if(data.bBlackValueLongChange)
//	{
//		for(i=0;i<MAX_Y_EDGE;i++)
//		{
//			if(l_BlackCenterGray[0][i][3]==0 || i==nTopLine) continue;
//
//			for(j=0;j<result->nXEdgeCount-data.nMaxMinRange*0.5;j+=(int)(data.nMaxMinRange*0.25))
//			{
//				nMin=255;
//				nMax=0;
//				for(k=j;k<j+data.nMaxMinRange*0.5;k++)
//				{
//					if(l_BlackCenterGray[k][i][3]==0) continue;
//					if(l_BlackCenterGray[k][i][0]<nMin) nMin=l_BlackCenterGray[k][i][0];
//					if(l_BlackCenterGray[k][i][0]>nMax) nMax=l_BlackCenterGray[k][i][0];
//				}
//			
//				if(nMax-nMin>data.nBlackValueMaxMin && result->nNGCenterGray<MAX_NG_POINTS)
//				{
//					result->nNGCenterGrayX[result->nNGCenterGray]=l_BlackCenterGray[j][i][2];
//					result->nNGCenterGrayY[result->nNGCenterGray]=l_BlackCenterGray[j][i][3];
//					result->dNGCenterGray[result->nNGCenterGray++]=-(nMax-nMin);
//				}
//			}
//		}
//	}
//	//흑선 두께의 구간 변동값 구함.--------------------------------------------------------------------------
//	if(data.bBlackThickLongChange)
//	{
//		for(i=0;i<MAX_Y_EDGE;i++)
//		{
//			if(l_BlackCenterGray[0][i][3]==0 || i==nTopLine) continue;
//
//			for(j=0;j<result->nXEdgeCount-data.nMaxMinRange*0.5;j+=(int)(data.nMaxMinRange*0.25))
//			{
//				nMin=1000000;
//				nMax=0;
//				for(k=j;k<j+data.nMaxMinRange*0.5;k++)
//				{
//					if(l_BlackCenterGray[k][i][3]==0) continue;
//					if(l_BlackCenterGray[k][i][1]<nMin) nMin=l_BlackCenterGray[k][i][1];
//					if(l_BlackCenterGray[k][i][1]>nMax) nMax=l_BlackCenterGray[k][i][1];
//				}
//			
//				if(nMax-nMin>data.dBlackThickMaxMin*1000 && result->nNGThickSlope<MAX_NG_POINTS)
//				{
//					result->nNGThickSlopeX[result->nNGThickSlope]=l_BlackCenterGray[j][i][2];
//					result->nNGThickSlopeY[result->nNGThickSlope]=l_BlackCenterGray[j][i][3];
//					result->dNGThickSlope[result->nNGThickSlope++]=-(nMax-nMin);
//				}
//			}
//		}
//	}
//
//	//백선 검사 -------------------------------------------------------------------------------
//	if(data.bWhiteValueShortChange || data.bWhiteThickShortChange)
//	{
//		for(i=0;i<MAX_Y_EDGE;i++)
//		{
//			if(l_WhiteCenterGray[0][i][3]==0 || i==nTopLine) continue;
//
//			for(j=0;j<result->nXEdgeCount-2;j++)
//			{
//				if(data.bWhiteValueShortChange && l_WhiteCenterGray[j][i][3] && l_WhiteCenterGray[j+1][i][3])
//				{
//					//백선 중심의 밝기 기울기 검사
//					nDiff=l_WhiteCenterGray[j][i][0]-l_WhiteCenterGray[j+1][i][0];
//					if(nDiff<0) nDiff*=-1;
//					if(nDiff>data.nWhiteValueSlope && result->nNGCenterGray<MAX_NG_POINTS)
//					{
//						result->nNGCenterGrayX[result->nNGCenterGray]=l_WhiteCenterGray[j][i][2];
//						result->nNGCenterGrayY[result->nNGCenterGray]=l_WhiteCenterGray[j][i][3];
//						result->dNGCenterGray[result->nNGCenterGray++]=nDiff;
//					}
//				}
//				if(data.bWhiteThickShortChange && l_WhiteCenterGray[j][i][3] && l_WhiteCenterGray[j+2][i][3])
//				{
//					//백선의 두께의 변화 검사 
//					dDiff=l_WhiteCenterGray[j][i][1]-l_WhiteCenterGray[j+2][i][1];
//					if(dDiff<0) dDiff*=-1;
//					if(dDiff>data.dWhiteThickSlope*1000 && result->nNGThickSlope<MAX_NG_POINTS)
//					{
//						result->nNGThickSlopeX[result->nNGThickSlope]=l_WhiteCenterGray[j][i][2];
//						result->nNGThickSlopeY[result->nNGThickSlope]=l_WhiteCenterGray[j][i][3];
//						result->dNGThickSlope[result->nNGThickSlope++]=dDiff;
//					}
//				}
//			}
//		}
//	}
//	//흑선 중심의 밝기의 구간 변동값 구함.--------------------------------------------------------------------------
//	if(data.bWhiteValueLongChange)
//	{
//		for(i=0;i<MAX_Y_EDGE;i++)
//		{
//			if(l_WhiteCenterGray[0][i][3]==0 || i==nTopLine) continue;
//
//			for(j=0;j<result->nXEdgeCount-data.nMaxMinRange*0.5;j+=(int)(data.nMaxMinRange*0.25))
//			{
//				nMin=255;
//				nMax=0;
//				for(k=j;k<j+data.nMaxMinRange*0.5;k++)
//				{
//					if(l_WhiteCenterGray[k][i][3]==0) continue;
//					if(l_WhiteCenterGray[k][i][0]<nMin) nMin=l_WhiteCenterGray[k][i][0];
//					if(l_WhiteCenterGray[k][i][0]>nMax) nMax=l_WhiteCenterGray[k][i][0];
//				}
//			
//				if(nMax-nMin>data.nWhiteValueMaxMin && result->nNGCenterGray<MAX_NG_POINTS)
//				{
//					result->nNGCenterGrayX[result->nNGCenterGray]=l_WhiteCenterGray[j][i][2];
//					result->nNGCenterGrayY[result->nNGCenterGray]=l_WhiteCenterGray[j][i][3];
//					result->dNGCenterGray[result->nNGCenterGray++]=-(nMax-nMin);
//				}
//			}
//		}
//	}
//	//흑선 두께의 구간 변동값 구함.--------------------------------------------------------------------------
//	if(data.bWhiteThickLongChange)
//	{
//		for(i=0;i<MAX_Y_EDGE;i++)
//		{
//			if(l_WhiteCenterGray[0][i][3]==0 || i==nTopLine) continue;
//
//			for(j=0;j<result->nXEdgeCount-data.nMaxMinRange*0.5;j+=(int)(data.nMaxMinRange*0.25))
//			{
//				nMin=1000000;
//				nMax=0;
//				for(k=j;k<j+data.nMaxMinRange*0.5;k++)
//				{
//					if(l_WhiteCenterGray[k][i][3]==0) continue;
//					if(l_WhiteCenterGray[k][i][1]<nMin) nMin=l_WhiteCenterGray[k][i][1];
//					if(l_WhiteCenterGray[k][i][1]>nMax) nMax=l_WhiteCenterGray[k][i][1];
//				}
//			
//				if(nMax-nMin>data.dBlackThickMaxMin*1000 && result->nNGThickSlope<MAX_NG_POINTS)
//				{
//					result->nNGThickSlopeX[result->nNGThickSlope]=l_WhiteCenterGray[j][i][2];
//					result->nNGThickSlopeY[result->nNGThickSlope]=l_WhiteCenterGray[j][i][3];
//					result->dNGThickSlope[result->nNGThickSlope++]=-(nMax-nMin);
//				}
//			}
//		}
//	}
//
////구한Edge Display -------------------------------------------------
//#ifdef SHOW_GRAPHIC  
//	CDC *pDC=GetDC();
//	CPen *oldPen, *pen;
//
//	pen=new CPen(PS_SOLID, 1, RGB(255,0,0));
//	oldPen=pDC->SelectObject(pen);
//	pDC->MoveTo(nXOffset*2, 255-l_BlackCenterGray[0][nBlackStart+l_B*2][0]);
//	for(j=1;j<result->nXEdgeCount;j++)
//	{
//		pDC->LineTo((nXOffset+j*2)*2, 255-l_BlackCenterGray[j][nBlackStart+l_B*2][0]);
//	}
//
//	delete pen;
//	pen=new CPen(PS_SOLID, 1, RGB(0,0,255));
//	pDC->SelectObject(pen);
//
//	pDC->MoveTo(nXOffset*2,  150+255-l_WhiteCenterGray[0][nWhiteStart+l_W*2][0]);
//	for(j=1;j<result->nXEdgeCount;j++)
//	{
//		pDC->LineTo((nXOffset+j*2)*2, 150+255-l_WhiteCenterGray[j][nWhiteStart+l_W*2][0]);
//	}
//
//	delete pen;
//	pDC->SelectObject(oldPen);
//	ReleaseDC(pDC);
//#endif
////------------------------------------------------------------------
//
//
//	ok=0;
////done:	
//
//	return ok;
//}
//
////Edge로부터 Line을 만드는 과정임.
////그 과정에 Edge 수의 많고 적음, Edge의 심한튐으로 인해 큰 불량을 잡는다. 
//int SLIT_MakeLine(bool bFirstCall, int nXCount, int nEdge, float *dEdge, int *dir, int nLeftPoint, TEACHDATA data, RESULTDATA *result)
//{
//	int i,k;
//	static int l_TopIndex, l_BotIndex;					 //Top/bottom Edge를 지정하는 Index (처음 Call에서 초기화)
//	static double dLastOKedge[MAX_Y_EDGE];
//	static int    nLastNGCount[MAX_Y_EDGE];
//	static int    nOldTopDir, nOldBotDir, nOldEdgeCount;  //직전 Edge Data
//	static double dOldTopEdge, dOldBotEdge;				  //직전 Edge Data
//	static int    nBrokenError, nAddError;
//	double dY, dist, dAvgWidth;
//	double dLimitWidth;
//	double dWhiteWidth, dWhiteWidthMin, dWhiteWidthMax;
//	double dBlackWidth, dBlackWidthMin, dBlackWidthMax;
//	bool   bLineBroken=false;
//	int nDir, nCountT, nCountB;
//	bool  bIsOK=true;
//	int   nTopDir, nBotDir;  //직전 Edge Data
//	int   nMaxNGEdgeRemove=5;
//	int   nNextXValue=2;
//
//	if(nEdge<2) return -1;
//	
//	if(bFirstCall)
//	{//이 함수가 처음 불러 지면 여기를 먼저 수행한다.
//
//	//------------검정두께의 최대, 최소, 흰색두께의 최대 최소 를 구한 후 이 값이 합리적일때 START, 그렇지 않으면 끊어짐으로 처리 
//		//검정선 흰선의 Min, Max구하는 부분 --------------------------------
//		dWhiteWidthMin=1000;
//		dWhiteWidthMax=0;
//		dBlackWidthMin=1000;
//		dBlackWidthMax=0;
//		for(i=2;i<nEdge-1;i++)
//		{
//			if(dir[i]==0) //White->Black
//			{
//				dWhiteWidth=dEdge[i]-dEdge[i-1];	//흰선 두께 
//				if(dWhiteWidth<dWhiteWidthMin) dWhiteWidthMin=dWhiteWidth;
//				if(dWhiteWidth>dWhiteWidthMax) dWhiteWidthMax=dWhiteWidth;
//			}
//			else
//			{
//				dBlackWidth=l_Edge[i]-l_Edge[i-1];	//흑선 두께 
//				if(dBlackWidth<dBlackWidthMin) dBlackWidthMin=dBlackWidth;
//				if(dBlackWidth>dBlackWidthMax) dBlackWidthMax=dBlackWidth;
//			}
//		}
//		
//		//검정선 흰선의 두꺼운 것이 얇은것의 3배이상이면 Line Broken으로 처리함.---------------------------------------------
//		if(dWhiteWidthMax>0 && dBlackWidthMax>0 && (dWhiteWidthMax/dBlackWidthMin>3.0 || dBlackWidthMax/dBlackWidthMin>3.0))
//		{
//			if(result->nNGLineBroken<MAX_NG_POINTS)
//			{
//					result->nNGLineBrokenX[result->nNGLineBroken]=nLeftPoint;
//					result->nNGLineBrokenY[result->nNGLineBroken]=(dEdge[0]+dEdge[nEdge-1])*0.5;
//					result->nNGLineBroken++;
//			}
//			return -1;
//		}
//	//---------------------------------------------------------------------------------------------------------------------------
//
//	//첫번째 수직 Line의 Edge를 저장한다.--------------------------------------------------
//		if(dir[0]==0) l_TopIndex=10;	//첫번째 Edge가 W2B면 10부터 시작 
//		else          l_TopIndex=11;	//첫번째 Edge가 B2W면 11부터 시작 
//
//		for(i=0;i<nEdge;i++)
//		{
//			if(dir[i]==0) //W2B
//			{
//				l_EdgeArray[nXCount][l_TopIndex+i]=dLastOKedge[l_TopIndex+i]=dEdge[i];   
//			}
//			else		 //B2W		
//			{
//				l_EdgeArray[nXCount][l_TopIndex+i]=dLastOKedge[l_TopIndex+i]=dEdge[i]; 
//			}
//			nLastNGCount[l_TopIndex+i]=0;
//		}
//		l_BotIndex=l_TopIndex+nEdge-1;
//
//		//가장 최근 Edge정보 BackUp--
//		nTopDir=dir[0];
//		nBotDir=dir[nEdge-1];
//		//---------------------------
//		nBrokenError=nAddError=false;
//		dOldTopEdge=dEdge[0];
//		dOldBotEdge=dEdge[nEdge-1];
//	//---------------------------------------------------------------------------------------	
//	}
//	else
//	{
//		//이전 Edge의 평균폭을 구한다. ------------------------------------------------------
//		dAvgWidth=(dLastOKedge[l_BotIndex]-dLastOKedge[l_TopIndex])/(l_BotIndex-l_TopIndex);
//		dLimitWidth=dAvgWidth;
//
//	//Line이 끊어짐이 있는지 체크함 =================================================================================================		
//		//폭으로 체크 --------------------------------------------------------------------------------------
//		//수직으로 Edge간의 간격이 평균의 2배 이상이면 LineBroken으로 간주함.
//		//흑색선과 백색선의 두께가 비슷해야한다. 만약에 다르면 다음 루틴을 흰선, 검정선 구분하여 처리해야함.
//		for(i=1;i<nEdge;i++)
//		{
//			if(dEdge[i]-dEdge[i-1]>dAvgWidth*2) 
//			{
//				//Edge수의 차이가 없으면 두께 불량으로 처리
//				if(abs(nOldEdgeCount-nEdge)<=1)
//				{
//					if(data.bBlackThickness && result->nNGCountThick<MAX_NG_POINTS)
//					{
//						result->nNGThickX[result->nNGCountThick]=nLeftPoint;
//						result->nNGThickY[result->nNGCountThick]=(dEdge[i]+dEdge[i-1])*0.5;
//						result->dNGThickness[result->nNGCountThick]=dEdge[i]-dEdge[i-1];
//						result->nNGCountThick++;
//					}
//				}
//				else //Edge수의 차이가 많으면 Line 끊어짐으로 처리 
//				{
//					if(result->nNGLineBroken<MAX_NG_POINTS)
//					{
//						result->nNGLineBrokenX[result->nNGLineBroken]=nLeftPoint;
//						result->nNGLineBrokenY[result->nNGLineBroken]=(dEdge[i]+dEdge[i-1])*0.5;
//						result->nNGLineBroken++;
//					}
//					bLineBroken=true;
//				}
//			}
//		}
//
//		// 갯수로 체크 (폭 불량은 없고, 직전 Edge가 많거나 적거하 해서 생긴 불량은 없고---------------------------------------------
//		// Edge수가 3개 이상 작거나, 2개이상 작은데 위/아래 Edge Type이 같을때 -----------------------------------------------------
//		if((!nBrokenError && !nAddError) && !bLineBroken	&& (nEdge<=nOldEdgeCount-3 || (nEdge<=nOldEdgeCount-2 && nOldTopDir==dir[0] &&  nOldBotDir==dir[nEdge-1])) )
//		{
//			if(result->nNGLineBroken<MAX_NG_POINTS)
//			{
//					result->nNGLineBrokenX[result->nNGLineBroken]=nLeftPoint;
//					if(fabs(dLastOKedge[l_TopIndex]-dEdge[0])>fabs(dLastOKedge[l_BotIndex]-dEdge[nEdge-1]))
//						result->nNGLineBrokenY[result->nNGLineBroken]=dEdge[0];
//					else
//						result->nNGLineBrokenY[result->nNGLineBroken]=dEdge[nEdge-1];
//					result->nNGLineBroken++;
//			}
//			nBrokenError=true;
//			bLineBroken=true;
//		}
//
//		// 갯수로 체크 (폭 불량은 없고, 직전 Edge가 많거나 적거하 해서 생긴 불량은 없고---------------------------------------------
//		// Edge수가 2개이상 많은데, 그 많은것이 직전 Top보다 2개많거나, 직전 Bottom보다 2개 많을때 불량으로 처리 
//		if((!nBrokenError && !nAddError) && !bLineBroken && nEdge>= nOldEdgeCount+2)
//		{
//			nCountT=nCountB=0;
//			for(i=0;i<nEdge;i++)
//			{
//				if(dEdge[i]<dOldTopEdge-dAvgWidth*0.5) nCountT++;
//				if(dEdge[i]>dOldBotEdge+dAvgWidth*0.5) nCountB++;
//			}
//			if( (nCountT>2 || nCountT==2 && nOldTopDir==dir[0]) || 
//				(nCountB>2 || nCountB==2 && nOldBotDir==dir[nEdge-1]))
//			{
//				if(result->nNGLineBroken<MAX_NG_POINTS)
//				{
//					result->nNGLineBrokenX[result->nNGLineBroken]=nLeftPoint-2;
//					if(nCountT>=nCountB)
//						result->nNGLineBrokenY[result->nNGLineBroken]=dLastOKedge[l_TopIndex];
//					else
//						result->nNGLineBrokenY[result->nNGLineBroken]=dLastOKedge[l_BotIndex];
//					result->nNGLineBroken++;
//				}
//				bLineBroken=true;
//				nAddError=true;
//			}
//		}
//		//-------------------------------------------------------------------------------------
//
//		if(bLineBroken) return 0;
//		nBrokenError=nAddError=false;
//
//		//Edge정보 BackUp------------
//		nTopDir=dir[0];
//		nBotDir=dir[nEdge-1];
//		//---------------------------
//	//===============================================================================================================================
//
//
//		//직전 Top Edge데이타 부터 Botton Edge데이타 까지 해당하는 Edge를 구해내는 과정 
//		for(k=l_TopIndex;k<=l_BotIndex;k++)
//		{			
//			dY=dLastOKedge[k];  //직전 OK된 Edge
//			nDir=k%2;			//그 Edge의 B2W, W2B 찾음
//
//			for(i=0;i<nEdge;i++)
//			{
//				if(dir[i]!=nDir) continue;	//같은 종류가 아니면 Skip
//				
//				dist=dY-dEdge[i];
//				if(i==nEdge-1 || i==nEdge-2) //같은 종류 중에 마지막이면 직전데이타와 비교하여 가까운쪽 선택함.==================
//				{
//					if(fabs(dist)<dY-dEdge[i-2])
//					{
//						if(dist<dLimitWidth && dist>-dLimitWidth)
//						{
//							l_EdgeArray[nXCount][k]=dEdge[i]; dir[i]=-1;
//						}		
//					}
//					else
//					{
//						dist=dY-dEdge[i-2];
//						if(dist<dLimitWidth && dist>-dLimitWidth)
//						{
//							l_EdgeArray[nXCount][k]=dEdge[i-2]; dir[i-2]=-1;
//						}		
//					}
//					break;
//				}	//=============================================================================================================		
//				else//같은 종류 중에 마지막이 아니면 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//				{
//					//아주 가까운게 있으면 바로 처리함.-----------------------------
//					if(dist>1 && dist<1)
//					{
//						l_EdgeArray[nXCount][k]=dEdge[i]; dir[i]=-1;
//						break;
//					}
//					//--------------------------------------------------------------
//
//					if(dist<0) //현재 선택된 Edge가 dY를 지나친 경우 직전 Edge와 비교하여 가까운 쪽을 선택함.
//					{	
//						if(i==0 || i==1) //첫째 Line인 경우 
//						{
////							if(fabs(dEdge[i]-l_EdgeArray[nXCount-1][k])<fabs(dEdge[i]-l_EdgeArray[nXCount-1][k+2]))
//							if(fabs(dEdge[i]-dLastOKedge[k])<fabs(dEdge[i]-dLastOKedge[k+2]))
//							{
//								if(dist<dLimitWidth && dist>-dLimitWidth)
//								{
//									l_EdgeArray[nXCount][k]=dEdge[i]; dir[i]=-1;
//								}
//							}
//							break;
//						}
//						else if(dir[i-2]<0 || dEdge[i-2]-dY<dist) //이전Line이 dist보다 더 멀면 현재 Line을 선택함.
//						{
//							if(dist<dLimitWidth && dist>-dLimitWidth)
//							{
//								l_EdgeArray[nXCount][k]=dEdge[i]; dir[i]=-1;
//							}
//							break;
//						}
//						else if(dir[i-2]>=0) //이전Line이 dist보다 더 가깝고, 이전 Line이 유효한 Line이면 
//						{
//							dist=dY-dEdge[i-2];
//							if(dist<dLimitWidth && dist>-dLimitWidth)
//							{
//								l_EdgeArray[nXCount][k]=dEdge[i-2]; dir[i-2]=-1;
//							}
//							break;
//						}		
//					}
//				}//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//			}
//		}
//		
//		//최근 OK Edge Backup-----------------------------
//		for(k=l_TopIndex;k<=l_BotIndex;k++)
//			if(l_EdgeArray[nXCount][k]) 
//			{
//				dLastOKedge[k]=l_EdgeArray[nXCount][k];
//				nLastNGCount[k]=0;
//			}
//			else						
//			{
//				nLastNGCount[k]++;
//			}
//		if(nLastNGCount[l_TopIndex]>nMaxNGEdgeRemove) 
//			l_TopIndex++;
//		if(nLastNGCount[l_BotIndex]>nMaxNGEdgeRemove) 
//			l_BotIndex--;
//		//------------------------------------------------
//
//		// 중간에 Edge가 한쌍 더있으면 불량 처리 ------------------------------------------------
//		for(i=2;i<nEdge-1;i++)
//		{
//			if(dir[i]>=0 && dir[i-1]>=0 && dEdge[i-1]>dLastOKedge[l_TopIndex]+1 && dEdge[i]<dLastOKedge[l_BotIndex]-1)
//			{
//				if(result->nNGLineAdd<MAX_NG_POINTS)
//				{
//					result->nNGLineAddX[result->nNGLineAdd]=nLeftPoint;
//					result->nNGLineAddY[result->nNGLineAdd]=(dEdge[i]+dEdge[i-1])*0.5;
//					result->nNGLineAdd++;
//				}			
//				bIsOK=false;
//				nDir=nOldEdgeCount;
//			}
//		}
//		//---------------------------------------------------------------------------------------	
//	}
//	if(bIsOK)
//	{
//		//가장 최근 Edge정보 BackUp--
//		nOldTopDir=nTopDir;
//		nOldBotDir=nBotDir;
//		nOldEdgeCount=nEdge;
//		dOldTopEdge=dEdge[0];
//		dOldBotEdge=dEdge[nEdge-1];
//		//---------------------------
//	}
//
//	return 0;
//}
//
//int SLIT_FindLeftEnd(int nLeftRight, LPBYTE fm, int left, int top, int right, int bottom, int pitch, TEACHDATA data)
//{
////	int nEnd;
//	int i,j;
//	LPBYTE fmT;
//	int nEdge;
//	int nSkipX=2;
//
//	if(nLeftRight==1)
//	{
//		for(j=left;j<right;j+=nSkipX)
//		{
//			for(i=top;i<bottom;i++)
//			{	
//				fmT=fm+pitch*i+j;
//				l_Value[i-top]=(*(fmT)+*(fmT+1))/2;
//			}
//			nEdge=SLIT_FindYEdge(l_Value, (bottom-top),data.nMinDepth, l_Edge, l_Dir); //Y방향 Line으로 Edge를 구함.
//			if(nEdge>=data.nMinEdgeCount)
//			{
//				return j+20;
//			}
//		}
//		return (int)((left+right)*0.5);
//	}
//	else if(nLeftRight==2)
//	{
//		for(j=right-1;j>=left;j-=nSkipX)
//		{
//			for(i=top;i<bottom;i++)
//			{	
//				fmT=fm+pitch*i+j;
//				l_Value[i-top]=(*(fmT)+*(fmT+1))/2;
//			}
//			nEdge=SLIT_FindYEdge(l_Value, (bottom-top),data.nMinDepth, l_Edge, l_Dir); //Y방향 Line으로 Edge를 구함.
//			if(nEdge>=data.nMinEdgeCount)
//			{
//				return j-20;
//			}
//		}	
//		return (int)((left+right)*0.5);
//	}
//	return 0;
//}
//
////return : Edge 수 
////dir:  0: White->Black, 1: Black->White
//int SLIT_FindYEdge(int * pData, int nCount, int nMinDepth, float *pEdge, int *dir)
//{
//	int i,k, nFlag=0;
//	int nEdgeCount=0;
//	int nStartMin, nStartMax;
//	float dThreshold;
//
//
//	nStartMin=nStartMax=pData[0];
//	for(i=1;i<nCount;i++)
//	{
//		if(pData[i]-nStartMin>nMinDepth && nFlag<=0) //흑에서 백으로 일정값이상 초과하면 
//		{
//			if(nFlag<=0)
//			{
//				//이전 Step에서 백->흑으로 변할때의 Edge를 구한다.
//				if(nFlag==-1)
//				{
//					dThreshold=(nStartMin+nStartMax)*0.5;
//					for(k=i;k>0;k--)
//					{
//						if((pData[k]-pData[k-1])<0 &&(pData[k]-dThreshold)*(pData[k-1]-dThreshold)<=0)
//						{
//							dir[nEdgeCount]=0;
//							pEdge[nEdgeCount++]=(float)k-(float)(pData[k]-dThreshold)/(pData[k]-pData[k-1]);
//							break;
//						}
//					}
//				}
//				nStartMax=pData[i];
//				nFlag=1;
//			}	
//		}
//		else if(nStartMax-pData[i]>nMinDepth && nFlag>=0) //백에서 흑으로 일정값이상 감소하면 
//		{
//			if(nFlag>=0)
//			{
//				//이전 Step에서 흑->백으로 변할때의 Edge를 구한다.
//				if(nFlag==1)
//				{
//					dThreshold=(nStartMin+nStartMax)*0.5;
//					for(k=i;k>0;k--)
//					{
//						if(	(pData[k]-pData[k-1])>0 && (pData[k]-dThreshold)*(pData[k-1]-dThreshold)<=0)
//						{
//							dir[nEdgeCount]=1;
//							pEdge[nEdgeCount++]=(float)k-(float)(pData[k]-dThreshold)/(pData[k]-pData[k-1]);
//							break;
//						}
//					}
//				}
//				nStartMin=pData[i];
//				nFlag=-1;
//			}
//		}
//
//		if(pData[i]<nStartMin) nStartMin=pData[i];
//		else if(pData[i]>nStartMax) nStartMax=pData[i];
//	}
//
//	return nEdgeCount;
//}
//
////I_WIDTH x I_HEIGHT 에서 구한 결과로 부터 불량 종류별로 대표적인 것들 1~2개씩 뽑는다. 
//void SLIT_InspectROIResult(int left, int top, RESULTDATA result)
//{
//	int i;
//	double dMax, dMin;
//	int nMaxPos, nMinPos;
//
//	g_FrameResult.dBlackWidth+=result.dBlackWidth;
//	g_FrameResult.dWhiteWidth+=result.dWhiteWidth;
//
//	if(g_FrameResult.nNGCount>=MAX_FRAME_NG) return;
//
//	for(i=0;i<result.nNGLineBroken;i++)
//	{
//		g_FrameResult.nNGPosX[g_FrameResult.nNGCount]=result.nNGLineBrokenX[i];
//		g_FrameResult.nNGPosY[g_FrameResult.nNGCount]=top+result.nNGLineBrokenY[i];
//		g_FrameResult.nNGType[g_FrameResult.nNGCount++]=1;
//
//		break;  //1개만 사용함 
//	}
//
//	if(g_FrameResult.nNGCount>=MAX_FRAME_NG) return;
//	for(i=0;i<result.nNGLineAdd;i++)
//	{
//		g_FrameResult.nNGPosX[g_FrameResult.nNGCount]=result.nNGLineAddX[i];
//		g_FrameResult.nNGPosY[g_FrameResult.nNGCount]=top+result.nNGLineAddY[i];
//		g_FrameResult.nNGType[g_FrameResult.nNGCount++]=2;
//
//		if(g_FrameResult.nNGCount>=MAX_FRAME_NG) return;
//		break;  //1개만 사용함 
//	}
//
//
//	//-----------------Thickness 후보 고름 ---------------------------------------
//	if(g_FrameResult.nNGCount>=MAX_FRAME_NG) return;
//	dMax=0;
//	dMin=0;
//	for(i=0;i<result.nNGCountThick;i++)
//	{
//		if(result.dNGThickness[i]<dMin) { dMin=result.dNGThickness[i]; nMinPos=i;}
//		if(result.dNGThickness[i]>dMax) { dMax=result.dNGThickness[i]; nMaxPos=i;}
//	}
//	if(dMax>0)
//	{
//		g_FrameResult.nNGPosX[g_FrameResult.nNGCount]=result.nNGThickX[nMaxPos];
//		g_FrameResult.nNGPosY[g_FrameResult.nNGCount]=top+result.nNGThickY[nMaxPos];
//		g_FrameResult.nNGType[g_FrameResult.nNGCount++]=3;
//	}
//	if(dMin<0 && nMinPos!=nMaxPos && abs(result.nNGThickX[nMaxPos]-result.nNGThickX[nMinPos])>I_HEIGHT)
//	{
//		g_FrameResult.nNGPosX[g_FrameResult.nNGCount]=result.nNGThickX[nMinPos];
//		g_FrameResult.nNGPosY[g_FrameResult.nNGCount]=top+result.nNGThickY[nMinPos];
//		g_FrameResult.nNGType[g_FrameResult.nNGCount++]=3;
//	}
//	//--------------------------------------------------------------------------------
//
//	//-----------------Thickness Slope 후보 고름 ---------------------------------------
//	if(g_FrameResult.nNGCount>=MAX_FRAME_NG) return;
//	dMax=0;
//	dMin=0;
//	for(i=0;i<result.nNGThickSlope;i++)
//	{
//		if(result.dNGThickSlope[i]<dMin) { dMin=result.dNGThickSlope[i]; nMinPos=i;}
//		if(result.dNGThickSlope[i]>dMax) { dMax=result.dNGThickSlope[i]; nMaxPos=i;}
//	}
//	if(dMax>0)
//	{
//		g_FrameResult.nNGPosX[g_FrameResult.nNGCount]=result.nNGThickSlopeX[nMaxPos];
//		g_FrameResult.nNGPosY[g_FrameResult.nNGCount]=top+result.nNGThickSlopeY[nMaxPos];
//		g_FrameResult.nNGType[g_FrameResult.nNGCount++]=4;
//	}
//	if(dMin<0 && nMinPos!=nMaxPos && abs(result.nNGThickSlopeX[nMaxPos]-result.nNGThickSlopeX[nMinPos])>I_HEIGHT)
//	{
//		g_FrameResult.nNGPosX[g_FrameResult.nNGCount]=result.nNGThickSlopeX[nMinPos];
//		g_FrameResult.nNGPosY[g_FrameResult.nNGCount]=top+result.nNGThickSlopeY[nMinPos];
//		g_FrameResult.nNGType[g_FrameResult.nNGCount++]=4;
//	}
//	//--------------------------------------------------------------------------------
//
//	//-----------------Edge Slope 후보 고름 ---------------------------------------
//	if(g_FrameResult.nNGCount>=MAX_FRAME_NG) return;
//	dMax=0;
//	dMin=0;
//	for(i=0;i<result.nNGEdgePeek;i++)
//	{
//		if(result.dNGEdgePeek[i]<dMin) { dMin=result.dNGEdgePeek[i]; nMinPos=i;}
//		if(result.dNGEdgePeek[i]>dMax) { dMax=result.dNGEdgePeek[i]; nMaxPos=i;}
//	}
//	if(dMax>0)
//	{
//		g_FrameResult.nNGPosX[g_FrameResult.nNGCount]=result.nNGEdgePeekX[nMaxPos];
//		g_FrameResult.nNGPosY[g_FrameResult.nNGCount]=top+result.nNGEdgePeekY[nMaxPos];
//		g_FrameResult.nNGType[g_FrameResult.nNGCount++]=5;
//	}
//	if(dMin<0 && nMinPos!=nMaxPos && abs(result.nNGEdgePeekX[nMaxPos]-result.nNGEdgePeekX[nMinPos])>I_HEIGHT)
//	{
//		g_FrameResult.nNGPosX[g_FrameResult.nNGCount]=result.nNGEdgePeekX[nMinPos];
//		g_FrameResult.nNGPosY[g_FrameResult.nNGCount]=top+result.nNGEdgePeekY[nMinPos];
//		g_FrameResult.nNGType[g_FrameResult.nNGCount++]=5;
//	}
//	//--------------------------------------------------------------------------------
//
//	//-----------------밝기차  후보 고름 ---------------------------------------
//	if(g_FrameResult.nNGCount>=MAX_FRAME_NG) return;
//	dMax=0;
//	dMin=0;
//	for(i=0;i<result.nNGCenterGray;i++)
//	{
//		if(result.dNGCenterGray[i]<dMin) { dMin=result.dNGCenterGray[i]; nMinPos=i;}
//		if(result.dNGCenterGray[i]>dMax) { dMax=result.dNGCenterGray[i]; nMaxPos=i;}
//	}
//	if(dMax>0)
//	{
//		g_FrameResult.nNGPosX[g_FrameResult.nNGCount]=result.nNGCenterGrayX[nMaxPos];
//		g_FrameResult.nNGPosY[g_FrameResult.nNGCount]=top+result.nNGCenterGrayY[nMaxPos];
//		g_FrameResult.nNGType[g_FrameResult.nNGCount++]=6;
//	}
//	if(dMin<0 && nMinPos!=nMaxPos && abs(result.nNGCenterGrayX[nMaxPos]-result.nNGCenterGrayX[nMinPos])>I_HEIGHT)
//	{
//		g_FrameResult.nNGPosX[g_FrameResult.nNGCount]=result.nNGCenterGrayX[nMinPos];
//		g_FrameResult.nNGPosY[g_FrameResult.nNGCount]=top+result.nNGCenterGrayY[nMinPos];
//		g_FrameResult.nNGType[g_FrameResult.nNGCount++]=6;
//	}
//	//--------------------------------------------------------------------------------
//}
//
//
////최대 nMaxCount개만 남기고 모두 없앤다. 
//void SLIT_RemoveAdjacent(int XRange, int YRange, int nMaxCount)
//{
//	int i, j, nNGCount;
//	int nType[MAX_FRAME_NG];
//	double *dX, *dY;
//
//	if(g_FrameResult.nNGCount<2) return;
//
//	dX=new double[g_FrameResult.nNGCount];
//	dY=new double[g_FrameResult.nNGCount];
//
//	nNGCount=g_FrameResult.nNGCount;
//	for(i=0;i<nNGCount;i++)
//	{
//		nType[i]=g_FrameResult.nNGType[i];
//		dX[i]=g_FrameResult.nNGPosX[i];
//		dY[i]=g_FrameResult.nNGPosY[i];
//	}
//
//	for(i=0;i<nNGCount;i++)
//	{
//		if(nType[i]==0) continue;
//		for(j=i+1;j<nNGCount;j++)
//		{
//			if(nType[j]==0) continue;
//			if( abs(dX[i]-dX[j])<XRange || abs(dY[i]-dY[j])<YRange) nType[j]=0;
//		}
//	}
//	
//	g_FrameResult.nNGCount=0;
//	for(i=0;i<nNGCount;i++)
//	{
//		if(nType[i]==0) continue;
//			
//		g_FrameResult.nNGPosX[g_FrameResult.nNGCount]=int(dX[i]);
//		g_FrameResult.nNGPosY[g_FrameResult.nNGCount]=int(dY[i]);
//		g_FrameResult.nNGType[g_FrameResult.nNGCount++]=nType[i];
//
//		if(g_FrameResult.nNGCount>=nMaxCount) break;
//	}
//
//
//	if(dX) delete dX;
//	if(dY) delete dY;
//}
//
//void SLIT_DefaultData()
//{
//	g_Teach.nOneFrameGrabCount		=60;
//	g_Teach.dOneFrameLength			=100;       //100mm
//	g_Teach.nSkip					=2;			//FIXED 
//	g_Teach.nMaxMinRange			=20;		//FIXED 경우에 따라 조정 가능함. (최대 밝기-최소 밝기를 구하는 범위)
//	g_Teach.nMinEdgeCount			=12;		//Y방향 1줄 최소 Edge수 
//	g_Teach.nMinDepth				=20;		//20~50 정도가 적절함 (아주 작은 변동도 보려면 낮추면 됨)
//
//	g_Teach.bBlackThickness			=true;		//  dBlackMin, dBlackMax
//	g_Teach.bWhiteThickness			=true;		//	dWhiteMin, dWhiteMax
//	g_Teach.bXEdgeSlope				=true;		//	dPeekMax
//	g_Teach.bBlackThickLongChange	=true;		//	nBlackValueMaxMin
//	g_Teach.bBlackThickShortChange	=true;		//  nBlackValueSlope
//	g_Teach.bWhiteThickLongChange	=true;		//  nWhiteValueMaxMin
//	g_Teach.bWhiteThickShortChange	=true;		//	nWhiteValueSlope
//	g_Teach.bBlackValueLongChange	=true;		//	dBlackThickMaxMin
//	g_Teach.bBlackValueShortChange	=true;		//	dWhiteThickMaxMin
//	g_Teach.bWhiteValueLongChange	=true;		//	dBlackThickSlope
//	g_Teach.bWhiteValueShortChange	=true;		//	dWhiteThickSlope
//
//	g_Teach.dBlackMin	=3.5;
//	g_Teach.dBlackMax	=5.5;					//흑선의 두께의 범위 
//	g_Teach.dWhiteMin	=3.5;
//	g_Teach.dWhiteMax	=5.5;					//백선의 두께의 범위
//	g_Teach.dPeekMax	=1.5;					//Edge의 연결 상태검사  5Pixel로 부터 중간값이 이 값 이상 튀면 불량처리 
//
//	//<<< Line Thickness Check >>>
//	g_Teach.dBlackThickMaxMin	=2;
//	g_Teach.dWhiteThickMaxMin	=2;			//일정 픽셀내에서 Max-Min값으로 불량 찾음.
//	g_Teach.dBlackThickSlope	=1.2;
//	g_Teach.dWhiteThickSlope	=1.2;		//일정 픽셀간격으로 두께의 변화양
//
//	//<<< Line Brightness Check >>>
//	g_Teach.nBlackValueMaxMin	=20;
//	g_Teach.nWhiteValueMaxMin	=20;		//일정 픽셀내에서 밝기값의 Max-Min값으로 불량 찾음.
//	g_Teach.nBlackValueSlope	=10;
//	g_Teach.nWhiteValueSlope	=10;		//흑선/백선의 중심을 따라서 밝기의 변화
//}
//
//int SLIT_Save(char *filename)
//{
//	CFile f;
//
//	if(f.Open(filename, CFile::modeCreate|CFile::modeWrite))
//	{
//		f.Write( &g_Teach, sizeof(TEACHDATA));
//		f.Close();
//
//		return 0;		
//	}
//	else
//	{
//		return -1;
//	}
//}
//
//int SLIT_Load(char *filename)
//{
//	CFile f;
//
//	if(f.Open(filename, CFile::modeRead))
//	{
//		f.Read( &g_Teach, sizeof(TEACHDATA));
//		f.Close();
//
//		return 0;		
//	}
//	else
//	{
//		return -1;
//	}
//}
//
