//#include "stdafx.h"
//#include "VisWeb.h"
//#include "math.h"
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////																																				//
////		Slit ������ ����� Defect�˻�																											//
////																																				//
////													2008.5.15    NextEye  ����   ywko@nexteye.com												//
////																																				//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
////Local ����Ÿ (�� File������ ����Ѵ�.)===========================================================================================================
//int		l_Value[1024];										//���� ������ �ȼ�����Ÿ (2���� ��հ�)
//float	l_Edge[1024];										//�������ٿ� ���� Edge���Ҷ� ���
//int		l_Dir[1024];										//���� ������ Edge�� ���� ���� 
//
//float l_EdgeArray[I_HALFWIDTH][MAX_Y_EDGE];					//X�������� W2B Edge�� ¦���� B2W Edge�� Ȧ���� 
//int   l_BlackCenterGray[I_HALFWIDTH][MAX_Y_EDGE][4];		//X�������� ������ Center�� Gray Value  0: Gray Value,1:��(um)  2: X��ǥ, 3:Y��ǥ 
//int   l_WhiteCenterGray[I_HALFWIDTH][MAX_Y_EDGE][4];		//X�������� ��� Center�� Gray Value	0: Gray Value,1:��(um)  2: X��ǥ, 3:Y��ǥ 
//int   l_B, l_W;
////=================================================================================================================================================
//
//
////Global ����Ÿ : ���������� ����Ѵ�. =============================================================================================================
//int			g_nLeftRightCut;	//Save�Ǵ� ���� (�˻�� ���� �ٸ� ����)  0 : ROI������ Full�� ���, 1: Left Cut,  2:Right Cut  3:All Cut
//TEACHDATA	g_Teach;			//Save�Ǵ� ���� (�˻�� ��� ���� ����ϴ� ����)
//
//FRAMERESULT g_FrameResult;		//��ü Frame������ ����� ���� ����				[Save���� �ʰ� ���α׷� �����߿��� ���]
//RESULTDATA  g_result;			//I_WIDTH x I_HEIGHT ������ �˻� ����� ���� ���� [Save���� �ʰ� ���α׷� �����߿��� ���] 
//
//
//
////++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////+++++++++++++++++++++++++++++++++++++++++++++++++++ VMaster���� ����ϴ� �Լ� ++++++++++++++++++++++++++++++++++++++++++++++++++++++
//#ifdef USE_VMASTER
//void CCalibration::OnButtonEdge()  //ROI�˻� 
//{
//	UpdateData(true);
//	l_B=m_Bth;
//	l_W=m_Wth;
//
//
//	LPBYTE fm, fmR;			
//	int i, j,k, pitch;
//
//	clock_t starttime, endtime; // Time ���ϱ�
//	double dElapseTime;         // ����� �ð�
//	CString Str;
//
//	CMainFrame *pMainFrame=(CMainFrame *)AfxGetMainWnd();  //���� ������ pointer�� ����
//	pMainFrame->GetImageInfo(&fm, &fmR, &pitch);
//	pMainFrame->GetROIInfo(&m_x1, &m_y1, &m_x2, &m_y2);
//	pMainFrame->GetCurrentImage(&fm);	
//	
//	Invalidate();	//�ݺ��ؼ� ������ ȭ�� Clear
//	UpdateWindow();
//
//	starttime=clock();  // ���۽ð�
//
//
//
///*	g_Teach.nSkip=2;			//Fixed Value
//	g_Teach.nMinEdgeCount=7;	//�ּ� Edge �� 
//	g_Teach.nMaxMinRange=20;	//�ִ� ���-�ּ� ��⸦ ���ϴ� ���� 
//	g_Teach.nMinDepth=m_nEdgeDepth; //30������ ������
//
//	g_Teach.dBlackMin=m_dBlackMin;
//	g_Teach.dBlackMax=m_dBlackMax;
//	g_Teach.dWhiteMin=m_dWhiteMin;
//	g_Teach.dWhiteMax=m_dWhiteMax;
//	g_Teach.dPeekMax=m_dMaxPeek;
//
//	//Center Gray�� �˻� 
//	g_Teach.nBlackValueSlope=m_nBlackSlope;
//	g_Teach.nWhiteValueSlope=m_nWhiteSlope;
//	g_Teach.nBlackValueMaxMin=m_nBlackCenterMaxMin;
//	g_Teach.nWhiteValueMaxMin=m_nWhiteCenterMaxMin;
//
//	//�β��˻� ����Ÿ 
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
//		//�β� Display-----------------------------------
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
//		//������-----------
//		for(k=0;k<g_result.nNGLineBroken;k++)
//		{
//			for(i=g_result.nNGLineBrokenX[k]*2-5;i<g_result.nNGLineBrokenX[k]*2+5;i++)
//				pDC->SetPixel(i,10+g_result.nNGLineBrokenY[k]*2, RGB(255,0,0));
//
//			for(i=g_result.nNGLineBrokenY[k]*2-5;i<g_result.nNGLineBrokenY[k]*2+5;i++)
//				pDC->SetPixel(g_result.nNGLineBrokenX[k]*2, 10+i, RGB(255,0,0));
//		}
//
//		//�߰��� ---------------------
//		for(k=0;k<g_result.nNGLineAdd;k++)
//		{
//			for(i=g_result.nNGLineAddX[k]*2-5;i<g_result.nNGLineAddX[k]*2+5;i++)
//				pDC->SetPixel(i,10+g_result.nNGLineAddY[k]*2, RGB(0,0,255));
//
//			for(i=g_result.nNGLineAddY[k]*2-5;i<g_result.nNGLineAddY[k]*2+5;i++)
//				pDC->SetPixel(g_result.nNGLineAddX[k]*2, 10+i, RGB(0,0,255));
//		}
//
//		//�߰� ��� ��ȭ 
//		for(k=0;k<g_result.nNGCenterGray;k++)
//		{
//			for(i=g_result.nNGCenterGrayX[k]*2-5;i<g_result.nNGCenterGrayX[k]*2+5;i++)
//				pDC->SetPixel(i,10+g_result.nNGCenterGrayY[k]*2, RGB(255,128,0));
//
//			for(i=g_result.nNGCenterGrayY[k]*2-5;i<g_result.nNGCenterGrayY[k]*2+5;i++)
//				pDC->SetPixel(g_result.nNGCenterGrayX[k]*2, 10+i, RGB(255,128,0));
//		}
//
//		//Edge�˻� Pink
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
//void CCalibration::OnButtonSlitInspect()  //��ü���� �˻� 
//{
//	LPBYTE fm, fmR;			
//	int i, j,k, pitch;
//	clock_t starttime, endtime; // Time ���ϱ�
//	double dElapseTime;         // ����� �ð�
//	CString Str;
//
//	CMainFrame *pMainFrame=(CMainFrame *)AfxGetMainWnd();  //���� ������ pointer�� ����
//	pMainFrame->GetImageInfo(&fm, &fmR, &pitch);
//	pMainFrame->GetROIInfo(&m_x1, &m_y1, &m_x2, &m_y2);
//	pMainFrame->GetCurrentImage(&fm);	
//
////	starttime=clock();  // ���۽ð�
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
////��ü������ �˻��ϴ� �Լ�, Teaching Data�� g_Teach�� �ִ� ����Ÿ�� ����ϰ�, �� ����� g_FrameResult�� �ִ´�.  -------------------------
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
//	//��� ���� -------------------------------------------------------------------------------------------------------------
//	g_FrameResult.dBlackWidth/=(2*g_Teach.nOneFrameGrabCount);	//Frame ��� Black Line�� 
//	g_FrameResult.dWhiteWidth/=(2*g_Teach.nOneFrameGrabCount);	//Frame ��� White Line�� 
//
//	SLIT_RemoveAdjacent(100,100, MAX_FRAME_NG);	//�̿��ϴ� �ҷ� �ϳ��� ����.
//
//	for(i=0;i<g_FrameResult.nNGCount;i++)		//Y���� �������̷� ǥ�� 
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
//#ifdef SHOW_GRAPHIC  //�����ġ ǥ�� �ϱ� ���ؼ� �ӽ÷� ����� �R.---------------------------------
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
////nLeftRight = 0 : ROI������ Full�� ���
////			 = 1 : Left ���� �Ϻ� ����
////			 = 2 : RIght ���� �Ϻ� ����
////			 = 3 : Left, Right�Ϻ� ���� 
//
//int 
//#ifdef USE_VMASTER
//CCalibration::
//#endif
//SLIT_EdgeArray(LPBYTE fm, int left, int top, int right, int bottom, int pitch, int nLeftRight, TEACHDATA data, RESULTDATA *result)
//{
//	int ok=-1;
//	int i,j;//, k;
//	int nEdge;			//���ٿ��� ���� Edge�� 
//	int left_, right_;	//���� ������ Boundary�� �����ϰ� �������� 
//	int nBlackCount, nWhiteCount; //��� �β� ���Ҷ� ��� 
//	int nSkipX=data.nSkip;		  //�׻� 2�� �����.
//	double dBlackWidth, dWhiteWidth;
//	double dBlackWidthSum, dWhiteWidthSum;
//	int nXEdgeCount=0;
////	int nW2BCount, nB2WCount;
////	int nY;
////	double dY;
//	LPBYTE fmT;
//	bool bIsYlineError, FirstLineSuccess=false;  //���� Y Line���� Error�߻�, ù��° Y Line������ True
////----�ʱ�ȭ -----------------------------
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
//		nEdge=SLIT_FindYEdge(l_Value, (bottom-top),data.nMinDepth, l_Edge, l_Dir); //Y���� Line���� Edge�� ����.
//		if(nEdge>MAX_Y_EDGE-20) nEdge=MAX_Y_EDGE-20;
//
//		//1���� Edge�� ���� ��/�� ���� �β��� ���ؼ� ��/���� �����Ѵ� --------------------------------------
//		bIsYlineError=false;
//		for(i=1;i<nEdge;i++)
//		{
//			if(l_Dir[i]==0) //White->Black
//			{
//				dWhiteWidth=l_Edge[i]-l_Edge[i-1]; //�� �β� 
//				dWhiteWidthSum+=dWhiteWidth;
//				nWhiteCount++;
//
//				//i�� 1�̰ų�, (nEdge-1)�� ���� ���� ���� ���ü� �����Ƿ� ���� �ҷ��� �������� �ʴ´�.
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
//				dBlackWidth=l_Edge[i]-l_Edge[i-1];	//�漱 �β� 
//				dBlackWidthSum+=dBlackWidth; nBlackCount++;  //��յβ� ���Ҷ� ���
//
//				//i�� 1�̰ų�, (nEdge-1)�� ���� ���� ���� ���ü� �����Ƿ� ���� �ҷ��� �������� �ʴ´�.
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
//		//�̿��ϴ� Edge����Ÿ�� ���� ����� �����Ѵ�. -------------------------------------------------------
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
////����Edge Display -------------------------------------------------
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
//	//���� l_EdgeArray ����Ÿ�� ���� �漱, ���� �߽��� Gray Value�� ���� �β��� ���Ѵ�.
//	for(i=0;i<MAX_Y_EDGE-1;i++)
//	{
//		if(l_EdgeArray[0][i]==0) continue;
//		
//		if(nTopLine==0)
//		{	
//			nTopLine=i;	//�� ù��° Edge Line�� ã�´�.
//			continue;	//�� ù��° Edge Line�� ���� �̷�� �漱/�鼱 �� ó������ �ʴ´�.
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
//					l_BlackCenterGray[j][i][1]=(l_EdgeArray[j][i+1]-l_EdgeArray[j][i])*1000; //�� (um)
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
//					l_WhiteCenterGray[j][i][1]=(l_EdgeArray[j][i+1]-l_EdgeArray[j][i])*1000;  //�� (um)
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
//	//��� ������ Ʀ �˻� --------------------------------------------------------------------
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
//	//�漱 �˻� -------------------------------------------------------------------------------
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
//					//�漱 �߽��� ��� ���� �˻�
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
//					//�漱�� �β��� ��ȭ �˻� 
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
//	//�漱 �߽��� ����� ���� ������ ����.--------------------------------------------------------------------------
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
//	//�漱 �β��� ���� ������ ����.--------------------------------------------------------------------------
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
//	//�鼱 �˻� -------------------------------------------------------------------------------
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
//					//�鼱 �߽��� ��� ���� �˻�
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
//					//�鼱�� �β��� ��ȭ �˻� 
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
//	//�漱 �߽��� ����� ���� ������ ����.--------------------------------------------------------------------------
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
//	//�漱 �β��� ���� ������ ����.--------------------------------------------------------------------------
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
////����Edge Display -------------------------------------------------
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
////Edge�κ��� Line�� ����� ������.
////�� ������ Edge ���� ���� ����, Edge�� ����Ʀ���� ���� ū �ҷ��� ��´�. 
//int SLIT_MakeLine(bool bFirstCall, int nXCount, int nEdge, float *dEdge, int *dir, int nLeftPoint, TEACHDATA data, RESULTDATA *result)
//{
//	int i,k;
//	static int l_TopIndex, l_BotIndex;					 //Top/bottom Edge�� �����ϴ� Index (ó�� Call���� �ʱ�ȭ)
//	static double dLastOKedge[MAX_Y_EDGE];
//	static int    nLastNGCount[MAX_Y_EDGE];
//	static int    nOldTopDir, nOldBotDir, nOldEdgeCount;  //���� Edge Data
//	static double dOldTopEdge, dOldBotEdge;				  //���� Edge Data
//	static int    nBrokenError, nAddError;
//	double dY, dist, dAvgWidth;
//	double dLimitWidth;
//	double dWhiteWidth, dWhiteWidthMin, dWhiteWidthMax;
//	double dBlackWidth, dBlackWidthMin, dBlackWidthMax;
//	bool   bLineBroken=false;
//	int nDir, nCountT, nCountB;
//	bool  bIsOK=true;
//	int   nTopDir, nBotDir;  //���� Edge Data
//	int   nMaxNGEdgeRemove=5;
//	int   nNextXValue=2;
//
//	if(nEdge<2) return -1;
//	
//	if(bFirstCall)
//	{//�� �Լ��� ó�� �ҷ� ���� ���⸦ ���� �����Ѵ�.
//
//	//------------�����β��� �ִ�, �ּ�, ����β��� �ִ� �ּ� �� ���� �� �� ���� �ո����϶� START, �׷��� ������ ���������� ó�� 
//		//������ ���� Min, Max���ϴ� �κ� --------------------------------
//		dWhiteWidthMin=1000;
//		dWhiteWidthMax=0;
//		dBlackWidthMin=1000;
//		dBlackWidthMax=0;
//		for(i=2;i<nEdge-1;i++)
//		{
//			if(dir[i]==0) //White->Black
//			{
//				dWhiteWidth=dEdge[i]-dEdge[i-1];	//�� �β� 
//				if(dWhiteWidth<dWhiteWidthMin) dWhiteWidthMin=dWhiteWidth;
//				if(dWhiteWidth>dWhiteWidthMax) dWhiteWidthMax=dWhiteWidth;
//			}
//			else
//			{
//				dBlackWidth=l_Edge[i]-l_Edge[i-1];	//�漱 �β� 
//				if(dBlackWidth<dBlackWidthMin) dBlackWidthMin=dBlackWidth;
//				if(dBlackWidth>dBlackWidthMax) dBlackWidthMax=dBlackWidth;
//			}
//		}
//		
//		//������ ���� �β��� ���� �������� 3���̻��̸� Line Broken���� ó����.---------------------------------------------
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
//	//ù��° ���� Line�� Edge�� �����Ѵ�.--------------------------------------------------
//		if(dir[0]==0) l_TopIndex=10;	//ù��° Edge�� W2B�� 10���� ���� 
//		else          l_TopIndex=11;	//ù��° Edge�� B2W�� 11���� ���� 
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
//		//���� �ֱ� Edge���� BackUp--
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
//		//���� Edge�� ������� ���Ѵ�. ------------------------------------------------------
//		dAvgWidth=(dLastOKedge[l_BotIndex]-dLastOKedge[l_TopIndex])/(l_BotIndex-l_TopIndex);
//		dLimitWidth=dAvgWidth;
//
//	//Line�� �������� �ִ��� üũ�� =================================================================================================		
//		//������ üũ --------------------------------------------------------------------------------------
//		//�������� Edge���� ������ ����� 2�� �̻��̸� LineBroken���� ������.
//		//������� ������� �β��� ����ؾ��Ѵ�. ���࿡ �ٸ��� ���� ��ƾ�� ��, ������ �����Ͽ� ó���ؾ���.
//		for(i=1;i<nEdge;i++)
//		{
//			if(dEdge[i]-dEdge[i-1]>dAvgWidth*2) 
//			{
//				//Edge���� ���̰� ������ �β� �ҷ����� ó��
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
//				else //Edge���� ���̰� ������ Line ���������� ó�� 
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
//		// ������ üũ (�� �ҷ��� ����, ���� Edge�� ���ų� ������ �ؼ� ���� �ҷ��� ����---------------------------------------------
//		// Edge���� 3�� �̻� �۰ų�, 2���̻� ������ ��/�Ʒ� Edge Type�� ������ -----------------------------------------------------
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
//		// ������ üũ (�� �ҷ��� ����, ���� Edge�� ���ų� ������ �ؼ� ���� �ҷ��� ����---------------------------------------------
//		// Edge���� 2���̻� ������, �� �������� ���� Top���� 2�����ų�, ���� Bottom���� 2�� ������ �ҷ����� ó�� 
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
//		//Edge���� BackUp------------
//		nTopDir=dir[0];
//		nBotDir=dir[nEdge-1];
//		//---------------------------
//	//===============================================================================================================================
//
//
//		//���� Top Edge����Ÿ ���� Botton Edge����Ÿ ���� �ش��ϴ� Edge�� ���س��� ���� 
//		for(k=l_TopIndex;k<=l_BotIndex;k++)
//		{			
//			dY=dLastOKedge[k];  //���� OK�� Edge
//			nDir=k%2;			//�� Edge�� B2W, W2B ã��
//
//			for(i=0;i<nEdge;i++)
//			{
//				if(dir[i]!=nDir) continue;	//���� ������ �ƴϸ� Skip
//				
//				dist=dY-dEdge[i];
//				if(i==nEdge-1 || i==nEdge-2) //���� ���� �߿� �������̸� ��������Ÿ�� ���Ͽ� ������� ������.==================
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
//				else//���� ���� �߿� �������� �ƴϸ� ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//				{
//					//���� ������ ������ �ٷ� ó����.-----------------------------
//					if(dist>1 && dist<1)
//					{
//						l_EdgeArray[nXCount][k]=dEdge[i]; dir[i]=-1;
//						break;
//					}
//					//--------------------------------------------------------------
//
//					if(dist<0) //���� ���õ� Edge�� dY�� ����ģ ��� ���� Edge�� ���Ͽ� ����� ���� ������.
//					{	
//						if(i==0 || i==1) //ù° Line�� ��� 
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
//						else if(dir[i-2]<0 || dEdge[i-2]-dY<dist) //����Line�� dist���� �� �ָ� ���� Line�� ������.
//						{
//							if(dist<dLimitWidth && dist>-dLimitWidth)
//							{
//								l_EdgeArray[nXCount][k]=dEdge[i]; dir[i]=-1;
//							}
//							break;
//						}
//						else if(dir[i-2]>=0) //����Line�� dist���� �� ������, ���� Line�� ��ȿ�� Line�̸� 
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
//		//�ֱ� OK Edge Backup-----------------------------
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
//		// �߰��� Edge�� �ѽ� �������� �ҷ� ó�� ------------------------------------------------
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
//		//���� �ֱ� Edge���� BackUp--
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
//			nEdge=SLIT_FindYEdge(l_Value, (bottom-top),data.nMinDepth, l_Edge, l_Dir); //Y���� Line���� Edge�� ����.
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
//			nEdge=SLIT_FindYEdge(l_Value, (bottom-top),data.nMinDepth, l_Edge, l_Dir); //Y���� Line���� Edge�� ����.
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
////return : Edge �� 
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
//		if(pData[i]-nStartMin>nMinDepth && nFlag<=0) //�濡�� ������ �������̻� �ʰ��ϸ� 
//		{
//			if(nFlag<=0)
//			{
//				//���� Step���� ��->������ ���Ҷ��� Edge�� ���Ѵ�.
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
//		else if(nStartMax-pData[i]>nMinDepth && nFlag>=0) //�鿡�� ������ �������̻� �����ϸ� 
//		{
//			if(nFlag>=0)
//			{
//				//���� Step���� ��->������ ���Ҷ��� Edge�� ���Ѵ�.
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
////I_WIDTH x I_HEIGHT ���� ���� ����� ���� �ҷ� �������� ��ǥ���� �͵� 1~2���� �̴´�. 
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
//		break;  //1���� ����� 
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
//		break;  //1���� ����� 
//	}
//
//
//	//-----------------Thickness �ĺ� �� ---------------------------------------
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
//	//-----------------Thickness Slope �ĺ� �� ---------------------------------------
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
//	//-----------------Edge Slope �ĺ� �� ---------------------------------------
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
//	//-----------------�����  �ĺ� �� ---------------------------------------
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
////�ִ� nMaxCount���� ����� ��� ���ش�. 
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
//	g_Teach.nMaxMinRange			=20;		//FIXED ��쿡 ���� ���� ������. (�ִ� ���-�ּ� ��⸦ ���ϴ� ����)
//	g_Teach.nMinEdgeCount			=12;		//Y���� 1�� �ּ� Edge�� 
//	g_Teach.nMinDepth				=20;		//20~50 ������ ������ (���� ���� ������ ������ ���߸� ��)
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
//	g_Teach.dBlackMax	=5.5;					//�漱�� �β��� ���� 
//	g_Teach.dWhiteMin	=3.5;
//	g_Teach.dWhiteMax	=5.5;					//�鼱�� �β��� ����
//	g_Teach.dPeekMax	=1.5;					//Edge�� ���� ���°˻�  5Pixel�� ���� �߰����� �� �� �̻� Ƣ�� �ҷ�ó�� 
//
//	//<<< Line Thickness Check >>>
//	g_Teach.dBlackThickMaxMin	=2;
//	g_Teach.dWhiteThickMaxMin	=2;			//���� �ȼ������� Max-Min������ �ҷ� ã��.
//	g_Teach.dBlackThickSlope	=1.2;
//	g_Teach.dWhiteThickSlope	=1.2;		//���� �ȼ��������� �β��� ��ȭ��
//
//	//<<< Line Brightness Check >>>
//	g_Teach.nBlackValueMaxMin	=20;
//	g_Teach.nWhiteValueMaxMin	=20;		//���� �ȼ������� ��Ⱚ�� Max-Min������ �ҷ� ã��.
//	g_Teach.nBlackValueSlope	=10;
//	g_Teach.nWhiteValueSlope	=10;		//�漱/�鼱�� �߽��� ���� ����� ��ȭ
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
