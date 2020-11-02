// Inspect.cpp: implementation of the CInspect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VisWeb.h"
#include "Inspect.h"
#include <math.h>
#include <STDLIB.H>
#include "findEdge.h"

#include "VisWebDoc.h"
#include "VisWebView.h"

#include "fchain.h"
//#include "FchainDll.h"

#include <algorithm>
//#include "NeProtocol.h"
using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define OBJECT		0xff
#define BACKGROUND	0

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInspect::CInspect()
 //:log4cpp_inspect(log4cpp::Category::getRoot())
{

	m_nCheckLine = 0;
	m_bBinImage = FALSE;

	for(int k=0;k<MAX_CAMERAS;k++)
	for(int i=0;i<8;i++)
		m_pChain[k][i] = NULL;
	for(int i=0;i<8;i++)
		m_pChainFull[i] = NULL;

	m_fmLine = new BYTE[BAD_IMG_WIDTH*2*BAD_IMG_HEIGHT*2];
	m_FullImage = new BYTE[CAM_WIDTH_CIS*3*3072];//폭 검사용 Full Image
	memset(m_FullImage,0,CAM_WIDTH_CIS*3*3072);
	for(int i=0;i<MAX_CAMERAS;i++){
		m_fmPreprocess[i] = new BYTE[CAM_WIDTH_CIS*CAM_HEIGHT_3072];
		memset(m_fmPreprocess[i],0,CAM_WIDTH_CIS*CAM_HEIGHT_3072);
	}

// 	m_fmPreprocess1 = new BYTE[CAM_WIDTH_CIS*CAM_HEIGHT_3072];
// 	m_fmPreprocess2 = new BYTE[CAM_WIDTH_CIS*CAM_HEIGHT_3072];
// 	m_fmPreprocess3 = new BYTE[CAM_WIDTH_CIS*CAM_HEIGHT_3072];
// 	memset(m_fmPreprocess1,0,CAM_WIDTH_CIS*CAM_HEIGHT_3072);
// 	memset(m_fmPreprocess2,0,CAM_WIDTH_CIS*CAM_HEIGHT_3072);
// 	memset(m_fmPreprocess3,0,CAM_WIDTH_CIS*CAM_HEIGHT_3072);

	
}

CInspect::~CInspect()
{

	for(int k=0;k<MAX_CAMERAS;k++)
		for(int i=0;i<8;i++)
			if(m_pChain[k][i])	delete m_pChain[k][i];
	for(int i=0;i<8;i++)
		if(m_pChainFull[i])	delete m_pChainFull[i];
	delete m_fmLine;
	delete m_FullImage;	
}
void CInspect::InitInspect(int nLine)
{
//	if(nLine == GL9)
	for(int k=0;k<MAX_CAMERAS;k++)
		for(int i=0;i<8;i++)
			m_pChain[k][i] = new CChain(100,100000);
	for(int i=0;i<8;i++)
		m_pChainFull[i] = new CChain(100,100000);
	//FChain_Init(100, 10000);
}

//대명_기포, 이물
int CInspect::Inspect(CImage* pImage,CImage* pFilterImage, CImage* pOrgImage, CData *pData, CWnd* pwnd,int nCam, CVisWebDoc* pDoc)
{
	return 0;
	//Main View에서 기본 

	//1	Mainview -> Copymil에서 영상 ptr 가져옴
	//2	MainView -> Inspect Call
	//3	m/v -> inspect -> vision Line select
	//						Overlap Range에 대한 설정은??
	//4					> Master Projection	> Projection x Data return
	//										> Edge , average return 
	//		밝기 조건에 의한 미검 실시?????
	//					> Thread Flag로 Image Split Project inspect
	//					> split 영상별 불량 최대개수 10개로 제한
	//					> Split 검사가 끝나면 Data Sort 시작
	//					> 4x4 = 16 개의 mesh로 Data 정리(후보군의 최대 밝기인 점을 기준)
	//					> 디펙 사이즈 측정
	//					> 디펙 판단
		//RO필터 추가 중첩영역 검사안함.
		//290픽셀 11.89mm sfx:0.041
					
}


CRect CInspect::FlipRect(CRect rect,int nCam)
{
	if(nCam == 0){
		rect.bottom = m_nHeight0 - rect.bottom;
		rect.top	= m_nHeight0 - rect.top;
	}
	else{
		rect.bottom = m_nHeight1 - rect.bottom;
		rect.top	= m_nHeight1 - rect.top;
	}
	int nTmp = rect.bottom;
	rect.bottom = rect.top;
	rect.top = nTmp;

	return rect;
}

CPoint CInspect::FlipPoint1(CPoint point,int nCam)
{
	if(nCam == 0){
		point.y = m_nHeight0*2 - point.y;
	}
	else{
		point.y = m_nHeight1*2 - point.y;
	}
	return point;
}


CRect CInspect::FlipRect1(CRect rect,int nCam)
{
	if(nCam == 0){
		rect.bottom = (m_nHeight0*2-10) - rect.bottom;
		rect.top	= (m_nHeight0*2-10) - rect.top;
	}
	else{
		rect.bottom = (m_nHeight1*2-10) - rect.bottom;
		rect.top	= (m_nHeight1*2-10) - rect.top;
	}

	int nTmp = rect.bottom;
	rect.bottom = rect.top;
	rect.top = nTmp;

	return rect;
}

CPoint CInspect::FlipPoint(CPoint point,int nCam)
{
	if(nCam == 0){
		point.y = m_nHeight0 - point.y;
	}
	else{
		point.y = m_nHeight1 - point.y;
	}
	return point;
}

double CInspect::GetAveValue(unsigned char *fm, CRect rect, int nPitch, int nSkipX, int nSkipY,int nCam)
{
	if(((CVisWebApp*)AfxGetApp())->m_debugLogWrite == TRUE){
		((CVisWebApp*)AfxGetApp())->WriteLog(PATH_DEBUG_LOG, "debug_log", "GetAveValue");
	}

	try{
		double dRet=0;
		int i,j;
		int nSum=0;
		int nCount=0;
	
		for(j=rect.top; j<rect.bottom; j+=nSkipY){
			for(i=rect.left; i<rect.right; i+=nSkipX){
				nSum += *(fm+j*nPitch+i);
				nCount++;
			}
		}
	
		if(nCount != 0){
			dRet = (double)nSum / nCount;
		}else{
			dRet = 0;
		}
	
		return dRet;
	}
	catch(...){
	}
	if(((CVisWebApp*)AfxGetApp())->m_debugLogWrite == TRUE){
		((CVisWebApp*)AfxGetApp())->WriteLog(PATH_DEBUG_LOG, "debug_log", "GetAveValue-end");
	}

}

#include "logData.h"
void CInspect::SetResultPosFlip(CData *pData,int nCam)
{
	for(int i=0; i<pData->m_nDefectCount[nCam]; i++){
		if(i>=MAX_DEFECT) break;
		if(pData->GetVisionLine(nCam)==GL1 || pData->GetVisionLine(nCam)==GL9)
		{
			pData->m_rectDefect[nCam][i] = FlipRect1(pData->m_rectDefect[nCam][i],nCam);
			pData->m_ptDefect[nCam][i] = FlipPoint1(pData->m_ptDefect[nCam][i],nCam);
		}
		else
		{
			pData->m_rectDefect[nCam][i] = FlipRect(pData->m_rectDefect[nCam][i],nCam);
			pData->m_ptDefect[nCam][i] = FlipPoint(pData->m_ptDefect[nCam][i],nCam);
		}
	}
}

BOOL CInspect::DefectJudge(int nCam,CData *pData,int nIndex)
{//1412
	BOOL bRet = TRUE;
	int nline = pData->m_nVisionLine;

//defect size //defect value
	if(nline ==GL3){
		if(pData->m_nDefectType[nCam][nIndex] == DCLASS_GBR_GROUP_PINHOLE){
			pData->m_bResult[nCam][nIndex] = !bRet;
			return bRet;
		}
		else if(pData->m_nDefectType[nCam][nIndex] != DCLASS_GBR_SCRATCH){
			if(pData->m_nDefectType[nCam][nIndex]==0)
				bRet = FALSE;
			else if(!pData->m_bDefectWhite[nCam][nIndex] && pData->m_dSize[nCam][nIndex] < pData->m_dWeakSize[nCam])
				bRet = FALSE;
			else if(!pData->m_bDefectWhite[nCam][nIndex] && pData->m_nDefectVMin[nCam][nIndex] > -pData->m_dWeakThDn[nCam])
				bRet = FALSE;
			else if(pData->m_bDefectWhite[nCam][nIndex] && pData->m_nDefectVMax[nCam][nIndex] < pData->m_dWeakThUp[nCam])
				bRet = FALSE;
			if(pData->m_bDefectWhite[nCam][nIndex] && pData->m_dSize[nCam][nIndex] < pData->m_dWeakWhiteSize[nCam] )
				bRet = FALSE;

			//이물 흑 스캡
			if(!pData->m_bDefectWhite[nCam][nIndex] && pData->m_dSize[nCam][nIndex] >= pData->m_dBlackSizeSkip[nCam])
				bRet = FALSE;

			
		}
	}
	else if(nline==GL4 && pData->m_nDefectType[nCam][nIndex] != DCLASS_GSR_SCRATCH &&  pData->m_nDefectType[nCam][nIndex] != DCLASS_GSR_LIMUL){
		if(pData->m_bDualNotIns){
			if(pData->m_dSize[nCam][nIndex] < pData->m_dThSize[nCam] || pData->m_nDefectVMin[nCam][nIndex] > -pData->m_dThDn[nCam])
				bRet = FALSE;
		}
		else{
			if(pData->m_bDefectWhite[nCam][nIndex])
			{
				if(pData->m_dSizeX[nCam][nIndex] < pData->m_dWeakSize[nCam]||pData->m_dSizeY[nCam][nIndex] < pData->m_dWeakSize[nCam] || pData->m_nDefectVMax[nCam][nIndex] < pData->m_dWeakThUp[nCam])
					bRet = FALSE;

				if(pData->m_nDefectType[nCam][nIndex] == DCLASS_GSR_CIMUL &&pData->m_dStdBrightness[nCam]>pData->m_dStdevV[nCam][nIndex])// && pData->m_dSize[nCam][nIndex]< 1)//0.5mm 보다 작을때만 비율
					pData->m_nDefectType[nCam][nIndex] = DCLASS_GSR_LOW_CIMUL;
				if(pData->m_nDefectType[nCam][nIndex] == DCLASS_GSR_CIMUL){// && pData->m_nDyeSpotAngle[0]==1){
					if(pData->m_dDSAngleGap[nCam][0] > pData->m_dDyespotAngle[nCam][nIndex] || pData->m_dDSAngleGap[nCam][1] < pData->m_dDyespotAngle[nCam][nIndex])//-10~+10도
						pData->m_nDefectType[nCam][nIndex] = DCLASS_GSR_LOW_CIMUL;
				}
				if(pData->m_nDefectType[nCam][nIndex] != DCLASS_GSR_PIMUL){
					if(pData->m_dSizeX[nCam][nIndex] < pData->m_dThSize[nCam] ||pData->m_dSizeY[nCam][nIndex] < pData->m_dThSize[nCam] || pData->m_nDefectVMax[nCam][nIndex] < pData->m_dThUp[nCam])
						bRet = FALSE;
				}
			}
			else{


			}
		}
		//170307	bh
		if( pData->m_nDefectType[nCam][nIndex] == DCLASS_GSR_SKIP){
			pData->m_dSizeY[nCam][nIndex] = 0;
			bRet = FALSE;
		}
	}
	else if(nline==GL4 && (pData->m_nDefectType[nCam][nIndex] == DCLASS_GSR_SCRATCH ||  pData->m_nDefectType[nCam][nIndex] == DCLASS_GSR_LIMUL)){
		if(pData->m_nDefectVMax[nCam][nIndex] < pData->m_dThDn[nCam])
			bRet = FALSE;
	}

//etc 
	if(pData->m_dSizeX[nCam][nIndex] < 0 && pData->m_nDefectType[nCam][nIndex] != DCLASS_GSR_SCRATCH){
		pData->m_dSizeX[nCam][nIndex] = 0;
		bRet = FALSE;
	}
	if(pData->m_dSizeY[nCam][nIndex] < 0 && pData->m_nDefectType[nCam][nIndex] != DCLASS_GSR_SCRATCH){
		pData->m_dSizeY[nCam][nIndex] = 0;
		bRet = FALSE;
	}

	if(pData->m_nDefectType[nCam][nIndex] == DCLASS_GBR_WATERDROP)
		bRet = FALSE;

	if(pData->m_dSizeX[nCam][nIndex]<0.1 || pData->m_dSizeY[nCam][nIndex]<0.1)
		bRet = FALSE;

//매장 마다 군집 피놀 날리기 -> 디펙 판단후 군집 핀홀로 날리기로 바꿈
	//if(nline ==GL3 && pData->m_dWhiteCommutyCount[nCam]>=pData->m_nCommutyCountCut[nCam] && pData->m_nDefectType[nCam][nIndex] == DCLASS_GBR_LOW_PIMUL){
	//	pData->m_nDefectType[nCam][nIndex] = DCLASS_GBR_GROUP_PINHOLE;//군집 핀홀
	//	bRet = TRUE;
	//}
	

	pData->m_bResult[nCam][nIndex] = !bRet;
	return bRet;

	//if(nline != GL9 && nline !=GL2 && nline !=GL4)
	//{
	//	if( (pData->m_dSizeX[nCam][nIndex] > pData->m_dThMaxSizeX[nCam] || pData->m_dSizeY[nCam][nIndex] > pData->m_dThMaxSizeX[nCam]) && pData->m_nDefectType[nCam][nIndex] != DCLASS_GSR_SCRATCH)
	//		bRet = FALSE;
	//}
	////////////////////반사류 과검.
	//if(nline == GL5 ||nline == GL6 || nline ==GL3)
	//{
	//	if(pData->m_dSizeY[nCam][nIndex] == pData->m_dScaleFactorY[nCam] && pData->m_dSizeX[nCam][nIndex] <= pData->m_dScaleFactorX[nCam]*7 && pData->m_nDefectType[nCam][nIndex] != DCLASS_GSR_SCRATCH
	//		&& pData->m_nDefectType[nCam][nIndex] != DCLASS_GBR_CIMUL && pData->m_nDefectType[nCam][nIndex] != DCLASS_GBR_SCRATCH)
	//	{	
	//		//Skip
	//		bRet = FALSE;
	//	}
	//}
}

//False 리턴이면 양품
BOOL CInspect::ValidDefect(CData *pData, int nIndex,int nCam)
{
	BOOL bRet = TRUE;
// 	int nline = pData->m_nVisionLine;
// 	//m_dWhiteSize
// 	if(pData->m_dSizeX[nCam][nIndex] < 0 && pData->m_nDefectType[nCam][nIndex] != DCLASS_GSR_SCRATCH){
// 		pData->m_dSizeX[nCam][nIndex] = 0;
// 		bRet = FALSE;
// 	}
// 	if(pData->m_dSizeY[nCam][nIndex] < 0 && pData->m_nDefectType[nCam][nIndex] != DCLASS_GSR_SCRATCH){
// 		pData->m_dSizeY[nCam][nIndex] = 0;
// 		bRet = FALSE;
// 	}
// ///////////////////////////////////
// 	//2level
// 	if(!pData->m_bDefectWhite[nCam][nIndex] && pData->m_dSize[nCam][nIndex] < pData->m_dThSize[nCam] 
// 		&& pData->m_nDefectType[nCam][nIndex] != DCLASS_GBR_CIMUL && pData->m_nDefectType[nCam][nIndex] != DCLASS_GBR_SCRATCH){//&& pData->m_nDefectType[nIndex] != DCLASS_NEL3_SCRATCH){
// 		bRet = FALSE;
// 	}
// 	if(pData->m_bDefectWhite[nCam][nIndex] && pData->m_dSize[nCam][nIndex] < pData->m_dWhiteSize 
// 		&& pData->m_nDefectType[nCam][nIndex] != DCLASS_GBR_CIMUL && pData->m_nDefectType[nCam][nIndex] != DCLASS_GBR_SCRATCH){//&& pData->m_nDefectType[nIndex] != DCLASS_NEL3_SCRATCH){
// 		bRet = FALSE;
// 	}
// ///////////////////////////////////////////
// 	if(nline == GL4)
// 	{
// 		if(pData->m_dSizeY[nCam][nIndex] <= pData->m_dScaleFactorY[nCam]*2 && pData->m_dSize[nCam][nIndex] >= int(pData->m_dScaleFactorX[nCam]*BAD_IMG_WIDTH))
// 		{
// 			bRet = FALSE;
// 		}
// 	}
// 	if(nline != GL9 && nline !=GL2 && nline !=GL4)
// 	{
// 		if( (pData->m_dSizeX[nCam][nIndex] > pData->m_dThMaxSizeX[nCam] || pData->m_dSizeY[nCam][nIndex] > pData->m_dThMaxSizeX[nCam]) && pData->m_nDefectType[nCam][nIndex] != DCLASS_GSR_SCRATCH)
// 			bRet = FALSE;
// 	}
// 	////////////////////반사류 과검.
// 	if(nline == GL5 ||nline == GL6 || nline ==GL7)
// 	{
// 		if(pData->m_dSizeY[nCam][nIndex] == pData->m_dScaleFactorY[nCam] && pData->m_dSizeX[nCam][nIndex] <= pData->m_dScaleFactorX[nCam]*7 && pData->m_nDefectType[nCam][nIndex] != DCLASS_GSR_SCRATCH
// 			&& pData->m_nDefectType[nCam][nIndex] != DCLASS_GBR_CIMUL && pData->m_nDefectType[nCam][nIndex] != DCLASS_GBR_SCRATCH)
// 		{	
// 				//Skip
// 			bRet = FALSE;
// 		}
// 	}
// /////////////////////////Cross W/V 추가.
// 	if(nline ==GL9 || nline ==GL2)
// 	{
// 		if(pData->m_dSizeX[nCam][nIndex]<pData->m_dMinSizeX[nCam])	bRet = FALSE;
// 		if(pData->m_dSizeY[nCam][nIndex]<pData->m_dMinSizeY[nCam]) 	bRet = FALSE;
// 		if(pData->m_nDefectVMax[nCam][nIndex] >= pData->m_dRealSpot[nCam]) bRet = TRUE;
// //		if(pData->m_dSize[nCam][nIndex] >= pData->m_dCommunitySize[nCam]) bRet = TRUE; //군집사이즈추가.
// 	}
// 	if(nline == GL4 && pData->m_nDefectType[nCam][nIndex] != DCLASS_GSR_SCRATCH){
// 		if(pData->m_nDefectVMax[nCam][nIndex]<pData->m_dThUp[nCam] || pData->m_dSize[nCam][nIndex] < pData->m_dThSize[nCam])
// 			bRet = FALSE;
// 	}
// 	if(nline ==GL3){
// 		if(pData->m_dRealSpot[nCam] < pData->m_nDefectVMax[nCam][nIndex])	
// 			bRet = TRUE; //max value
// 		if(pData->m_nDefectType[nCam][nIndex] == DCLASS_GSR_SCRATCH)
// 			bRet = TRUE;
// 	}
	return bRet;
}
void CInspect::CopyBlockImg(CImage *pImgSrc, CRect rect, CImage *pImgDest,int nCam)
{
	unsigned char* fmSrc	= pImgSrc->GetImagePtr();
	unsigned char* fmDest	= pImgDest->GetImagePtr();
	int nPitchSrc	= pImgSrc->GetWidth();
	int nPitchDest	= pImgDest->GetWidth();

	for(int j=rect.top; j<rect.bottom; j++){
		memmove( fmDest+((j-rect.top)*nPitchDest), fmSrc+(j*nPitchSrc+rect.left), sizeof(BYTE)*rect.Width());	
	}
}

void CInspect::SortDefectData(CData *pData,int nCam)
{
	int i;
	for(i=0; i<pData->m_nDefectCount[nCam]; i++){
		if(i>MAX_DEFECT) break;
		if(pData->m_bResult[nCam][i]){	//양품이라면
			pData->MoveDefectData(pData->m_nDefectCount[nCam]-1, i,nCam);
			pData->m_nDefectCount[nCam]--;
		}
	}
}



void CInspect::GetDefectType(CData *pData,int nCam,int nIdx)
{
	double dSizeOfDotOrCircle = 0.5;
	double dThNewMachine		= 2;
	int nIndex = nIdx;//pData->m_nDefectCount[nCam];
	double	dtemp1,dtemp2;
	dtemp1 =0.0;
	dtemp2 =0.0;
//점이냐 원이냐 판단하는 루틴
	int nPc = pData->m_nVisionLine;
	int nx1 = pData->m_dSizeX[nCam][nIndex]/pData->m_dScaleFactorX[nCam];
	int ny1 = pData->m_dSizeY[nCam][nIndex]/pData->m_dScaleFactorY[nCam];
	if(nx1<1)nx1 = 1;if(ny1<1)ny1 =1;
	double dPercent = pData->m_nDefectThCount[nCam][nIndex]/double( nx1*ny1);//사이즈의 면적이 얼마인지 확인
	if(nPc == GL3 )
	{
		if(pData->m_bDefectWhite[nCam][nIndex])
		{//백점일경우
			if(pData->m_nDefectType[nCam][nIndex] != DCLASS_GBR_SCRATCH)
			{
				double dratio = pData->m_fDefectRatio[nCam][nIndex];	
				if(pData->m_dSize[nCam][nIndex]>=pData->m_dWeakWhiteSize[nCam] && pData->m_nDefectVMax[nCam][nIndex]>=pData->m_dWeakThUp[nCam]){//강 약을 구분한다.
					if(pData->m_nDefectVMax[nCam][nIndex]>=pData->m_dThUp[nCam])//백th 보다 큰경우
					{
						if(dratio <pData->m_dTypeRatio[nCam]){//가로 세로비 확인
							// 막뜯김 먼저 체크
							if(pData->m_dSize[nCam][nIndex] >=pData->m_pinholeGroupSize[nCam]){//param7
								//다시 흰ㅅ색의 사이즈
								if(pData->m_dMaxWhiteSize[nCam][nIndex] > pData->m_pinholeGroupSize[nCam])
									pData->m_nDefectType[nCam][nIndex] = DCLASS_GBR_PINHOLE_BIT;//막뜯김
								else{
									double dcompact = pData->m_dCompactness[nCam];12;//sparam3
									if(pData->m_dStdevV[nCam][nIndex]*100<dcompact)
										pData->m_nDefectType[nCam][nIndex] = DCLASS_GBR_PINHOLE_BIT;//막뜯김
									else
										pData->m_nDefectType[nCam][nIndex] = DCLASS_GBR_LOW_PINHOLE_BIT;//약 막뜯김
								}
							}
							else if(pData->m_dSize[nCam][nIndex] >=pData->m_dWhiteSize){// 핀홀 사이즈 확인
								if(dPercent>=pData->m_nDefectThCountPercent[nCam]){
									if(pData->m_nPinholeValue[nCam]<pData->m_nDefectVMax[nCam][nIndex])
										pData->m_nDefectType[nCam][nIndex] = DCLASS_GBR_PIMUL;//핀홀
									else
										pData->m_nDefectType[nCam][nIndex] = DCLASS_GBR_LOW_PIMUL;//약찍힘
								}
								else //얇은거니까
									pData->m_nDefectType[nCam][nIndex] = DCLASS_GBR_LOW_PINHOLE_L;//약찍힘
							}
							else{
								//if(pData->m_dWhiteCommutyCount[nCam]>=10)
								//	pData->m_nDefectType[nCam][nIndex] = DCLASS_GBR_GROUP_PINHOLE;//군집 핀홀
								//else
									pData->m_nDefectType[nCam][nIndex] = DCLASS_GBR_LOW_PIMUL;//약핀홀
							}
						}
						else{
							if(pData->m_dSize[nCam][nIndex] >=pData->m_dEdgeBright[nCam])//param8 //1.5
							{
								if(dPercent<=pData->m_nDefectThCountPercent[nCam])
									pData->m_nDefectType[nCam][nIndex] = DCLASS_GBR_PINHOLE_C_L;//s/F
								else{
									//X 폭이 작은경우 다시 SF 로 구분한다.
									if(pData->m_dSizeX[nCam][nIndex] < 0.5 && fabs(pData->m_dDyespotAngle[nCam][nIndex]) >= 77 )
										pData->m_nDefectType[nCam][nIndex] = DCLASS_GBR_PINHOLE_C_L;//s/F
									else if(pData->m_dSizeY[nCam][nIndex] < 0.5 && fabs(pData->m_dDyespotAngle[nCam][nIndex]) < 12 )
										pData->m_nDefectType[nCam][nIndex] = DCLASS_GBR_PINHOLE_C_L;//s/F
									else
										pData->m_nDefectType[nCam][nIndex] = DCLASS_GBR_PINHOLE_L;//찍힘//DCLASS_GBR_LOW_PINHOLE_C_L
								}
							}
							else if(pData->m_dSize[nCam][nIndex] >=pData->m_pinholeLargeSize[nCam])//param5 //0.7
							{
								if(pData->m_strMachineName.Find("CA")>=0){
										pData->m_nDefectType[nCam][nIndex] = DCLASS_GBR_PINHOLE_L;//찍힘//DCLASS_GBR_LOW_PINHOLE_C_L
								}
								else{
									if(dPercent>=pData->m_nDefectThCountPercent[nCam])
										pData->m_nDefectType[nCam][nIndex] = DCLASS_GBR_PINHOLE_L;//찍힘//DCLASS_GBR_LOW_PINHOLE_C_L
									else
										pData->m_nDefectType[nCam][nIndex] = DCLASS_GBR_LOW_PINHOLE_C_L;//약SF//
								}
							}
							else
								pData->m_nDefectType[nCam][nIndex] = DCLASS_GBR_LOW_PINHOLE_L;//약찍힘
						}
					}
					else{
						//사이즈가 큰경우
						if(pData->m_dSize[nCam][nIndex] > pData->m_dEdgeBright[nCam] && pData->m_dSizeX[nCam][nIndex]<0.5)//sf 사이즈 보다 큰경우
						{
							//if(fabs(pData->.m_dDyespotAngle[nCam][nIndex]) > 88  && pData->m_fDefectRatio[nCam][nIndex]>12)
							//	;//sc
							//else
								pData->m_nDefectType[nCam][nIndex] = DCLASS_GBR_LOW_PINHOLE_C_L;//약SF//
						}
						else if(dratio>3)
							pData->m_nDefectType[nCam][nIndex] = DCLASS_GBR_LOW_PINHOLE_C_L;//약SF//
						else
							pData->m_nDefectType[nCam][nIndex] = DCLASS_GBR_LOW_PIMUL;//약핀홀
					}
				}
				else{
//불량 아님
				}
			}
			else{//sc
				

			}
		}
		else{//black defect
			int nTh1 = pData->m_dThDn[0];50;//35;//블랙 th
			int nTh2 = pData->m_dWeakThDn[0];35;//50;//블랙 후보
			double dsize1 = pData->m_dWeakSize[0];1.0;//2.0;//약 이물 사이즈
			double dsize2 = pData->m_dRealSpot[0];5.0;//1.0;//강 사이즈
			double dsize3 = pData->m_dThSize[0];2.0;//5.0;//후면 사이즈


			if(abs(pData->m_nDefectVMin[nCam][nIndex]) >= nTh2){//후보 th
				if(abs(pData->m_nDefectVMin[nCam][nIndex])>nTh1){//강 th 혹은 약이물
					if(pData->m_dSize[nCam][nIndex] > dsize2)
						pData->m_nDefectType[nCam][nIndex] = DCLASS_GBR_LIMUL;//이물
					else 
						pData->m_nDefectType[nCam][nIndex] = DCLASS_GBR_LOW_LIMUL;//약이물
				}
				else{
					if(pData->m_dDyespotAngle[nCam][nIndex] > pData->m_nProjection[nCam])
						pData->m_nDefectType[nCam][nIndex] = DCLASS_GBR_WATERDROP;
					else if(pData->m_dSize[nCam][nIndex] > dsize2 || pData->m_dSize[nCam][nIndex] < dsize1)
						pData->m_nDefectType[nCam][nIndex] = DCLASS_GBR_LOW_LIMUL;//약이물
					else if(pData->m_dSize[nCam][nIndex] > dsize3 &&pData->m_dSizeX[nCam][nIndex] > dsize3&&pData->m_dSizeY[nCam][nIndex] > dsize3 && pData->m_dDyespotAngle[nCam][nIndex] < pData->m_nProjection[nCam]){//물방울 스킵
//추가 조건 필요.
						if(dPercent>=pData->m_nDefectThCountPercent[nCam])
							pData->m_nDefectType[nCam][nIndex] = DCLASS_GBR_BACKDENT;//후면 돌기
						else
							pData->m_nDefectType[nCam][nIndex] = DCLASS_GBR_LOW_LIMUL;//약이물
					}
					else
						pData->m_nDefectType[nCam][nIndex] = DCLASS_GBR_LOW_LIMUL;//약이물
				}

			}
			else{
				//skip
			}
		}
	}
	else if(nPc == GL4)
	{//scratch
		if(pData->m_nDefectType[nCam][nIndex] == DCLASS_GSR_SKIP ) return;
		if(pData->m_bUse2Level[0]){
			//scratch는 다른 곳에서 정의 한다.
			if(pData->m_nSizeCheck[0] == 0){//m_dsize만 체크
				if(pData->m_nDefectType[nCam][nIndex] != DCLASS_GSR_PIMUL && pData->m_nDefectType[nCam][nIndex] != DCLASS_GSR_SCRATCH){//군집과 스크래치가 아닐때
					if(pData->m_nDefectVMax[nCam][nIndex]>pData->m_dThUp[nCam] && pData->m_dSize[nCam][nIndex]> pData->m_dThSize[0])//value & size 
						pData->m_nDefectType[nCam][nIndex] = DCLASS_GSR_CIMUL;	//black //DCLASS_GBR_LOW_LIMUL
					else //iiiiif(pData->m_nDefectVMax[nCam][nIndex]>pData->m_dWeakThUp[nCam] && pData->m_dSize[nCam][nIndex]> pData->m_dWeakSize[0])
						pData->m_nDefectType[nCam][nIndex] = DCLASS_GSR_LOW_CIMUL;
				}
			}
			else if(pData->m_nSizeCheck[0] == 1){//사이즈 X/Y 둘다 본다
				// 군집이 아니고 미건조도 아니고 스크래치도 아닐때 다이스팟만 남는다.

				if(pData->m_bDualNotIns){
					if(pData->m_dSize[nCam][nIndex]>pData->m_dThSize[0])
						pData->m_nDefectType[nCam][nIndex] = DCLASS_GSR_CIMUL;	

				}
				else{//dl
					if(pData->m_nDefectType[nCam][nIndex] != DCLASS_GSR_PIMUL && pData->m_nDefectType[nCam][nIndex] != DCLASS_GSR_NOTDRY && pData->m_nDefectType[nCam][nIndex] != DCLASS_GSR_SCRATCH){
						//다이스팟은 Ratoi를 체크한다. 일정 사이즈만을 체크한다.
						//20170308
						if(pData->m_nDefectType[nCam][nIndex] ==DCLASS_GSR_SURFACE_DEFECT){
							if(pData->m_dSize[nCam][nIndex]>pData->m_dBlackSize[0] && pData->m_dSizeX[nCam][nIndex]>pData->m_dBlackSize[0]&& pData->m_dSizeY[nCam][nIndex]>pData->m_dBlackSize[0])
								pData->m_nDefectType[nCam][nIndex] =DCLASS_GSR_SURFACE_DEFECT;
							else if(pData->m_dSize[nCam][nIndex]>=pData->m_dBlackCandidateSize[0])
								pData->m_nDefectType[nCam][nIndex] =DCLASS_GSR_LOW_SURFACE_DEFECT;
							else 
								pData->m_nDefectType[nCam][nIndex] =DCLASS_GSR_SKIP;
						}
						else if(pData->m_nDefectType[nCam][nIndex] != DCLASS_GSR_SKIP && pData->m_nDefectVMax[nCam][nIndex]>pData->m_dThUp[nCam] && pData->m_dSizeX[nCam][nIndex]> pData->m_dThSize[0]&& pData->m_dSizeY[nCam][nIndex]> pData->m_dThSize[0] && pData->m_dSize[nCam][nIndex]<pData->m_dStrongSize[0] )//value & size 
						{
							//compactness를 체크한다.
							if(pData->m_dStdBrightness[nCam]<pData->m_dStdevV[nCam][nIndex])
								pData->m_nDefectType[nCam][nIndex] = DCLASS_GSR_CIMUL;	
							else
								pData->m_nDefectType[nCam][nIndex] = DCLASS_GSR_LOW_CIMUL;	
						}
						else {//if(pData->m_nDefectVMax[nCam][nIndex]>pData->m_dWeakThUp[nCam] && pData->m_dSizeX[nCam][nIndex]> pData->m_dWeakSize[0]&& pData->m_dSizeY[nCam][nIndex]> pData->m_dWeakSize[0])
							//사이즈가 큰경우?
							if(pData->m_nDefectType[nCam][nIndex] == DCLASS_GSR_SKIP)	//170307	bh//20170308
								;
							else if(pData->m_dSize[nCam][nIndex]>pData->m_dStrongSize[0] && pData->m_dStdBrightness[nCam]>pData->m_dStdevV[nCam][nIndex])
								pData->m_nDefectType[nCam][nIndex] = DCLASS_GSR_NOTDRY;
							else
								pData->m_nDefectType[nCam][nIndex] = DCLASS_GSR_LOW_CIMUL;
						}
					}
				}
			}
			else{// if(pData->m_nSizeCheck[0] == 2){//강 - 사이즈 X/Y 둘다 본다 약은 최대 사이즈만 본다.
				if(pData->m_nDefectType[nCam][nIndex] != DCLASS_GSR_PIMUL && pData->m_nDefectType[nCam][nIndex] != DCLASS_GSR_SCRATCH){
					if(pData->m_nDefectVMax[nCam][nIndex]>pData->m_dThUp[nCam] && pData->m_dSizeX[nCam][nIndex]> pData->m_dThSize[0]&& pData->m_dSizeY[nCam][nIndex]> pData->m_dThSize[0])//value & size 
						pData->m_nDefectType[nCam][nIndex] = DCLASS_GSR_CIMUL;	//black //DCLASS_GBR_LOW_LIMUL
					else //if(pData->m_nDefectVMax[nCam][nIndex]>pData->m_dWeakThUp[nCam] && pData->m_dSize[nCam][nIndex]> pData->m_dWeakSize[0])
						pData->m_nDefectType[nCam][nIndex] = DCLASS_GSR_LOW_CIMUL;
				}
			}
			if(pData->m_nDefectType[nCam][nIndex] != DCLASS_GSR_SKIP &&pData->m_nDefectType[nCam][nIndex] !=DCLASS_GSR_LOW_SURFACE_DEFECT &&pData->m_nDefectType[nCam][nIndex] !=DCLASS_GSR_SURFACE_DEFECT &&pData->m_nDefectType[nCam][nIndex] != DCLASS_GSR_PIMUL && pData->m_nDefectType[nCam][nIndex] != DCLASS_GSR_SCRATCH)// && pData->m_nDyeSpotAngle[0]==1)
				if(pData->m_dDSAngleGap[nCam][0] > pData->m_dDyespotAngle[nCam][nIndex] || pData->m_dDSAngleGap[nCam][1] < pData->m_dDyespotAngle[nCam][nIndex])
					pData->m_nDefectType[nCam][nIndex] = DCLASS_GSR_LOW_CIMUL;
			if(pData->m_nDefectType[nCam][nIndex] == DCLASS_GSR_SKIP)	//170307	bh //20170308
				;			
			else if(pData->m_nDefectType[nCam][nIndex] !=DCLASS_GSR_LOW_SURFACE_DEFECT &&pData->m_nDefectType[nCam][nIndex] !=DCLASS_GSR_SURFACE_DEFECT &&pData->m_dStdBrightness[nCam]>pData->m_dStdevV[nCam][nIndex] && pData->m_dSize[nCam][nIndex]< 0.5)//0.5mm 보다 작을때만 비율
				pData->m_nDefectType[nCam][nIndex] = DCLASS_GSR_LOW_CIMUL;

			if(pData->m_nDefectType[nCam][nIndex] != DCLASS_GSR_SKIP &&pData->m_nDefectType[nCam][nIndex] !=DCLASS_GSR_LOW_SURFACE_DEFECT &&pData->m_nDefectType[nCam][nIndex] !=DCLASS_GSR_SURFACE_DEFECT &&pData->m_dStdBrightness[nCam]>pData->m_dStdevV[nCam][nIndex] &&pData->m_nDefectType[nCam][nIndex] == DCLASS_GSR_CIMUL && pData->m_dSize[nCam][nIndex]> 1.5)//0.5mm 보다 작을때만 비율
				pData->m_nDefectType[nCam][nIndex] = DCLASS_GSR_NOTDRY;
			if(pData->m_bDualNotIns){
				if(pData->m_dSize[nCam][nIndex]>pData->m_dThSize[0])
					pData->m_nDefectType[nCam][nIndex] = DCLASS_GSR_CIMUL;	
			}
		}
		else{
			//다이스팟과 군집형 정의 //DCLASS_GSR_PIMUL 514-202
			if(pData->m_nDefectType[nCam][nIndex] != DCLASS_GSR_PIMUL && pData->m_nDefectType[nCam][nIndex] != DCLASS_GSR_SCRATCH)//군집과 스크래치가 아닐때
				pData->m_nDefectType[nCam][nIndex] = DCLASS_GSR_CIMUL;
		}
	}
	else if(nPc == GL6){
		if(pData->m_bDefectWhite[nCam][nIndex]){//백점일경우
			int bitSurfaceThUpValue = 120;//RO막뜯김 구분 밝기
			float m_ratio = 3;
			// 핀홀 세분화
			if(pData->m_dSize[nCam][nIndex] >= pData->m_dWhiteSize
						&& pData->m_dSize[nCam][nIndex] < pData->m_pinholeLargeSize[nCam]
						&& pData->m_fDefectRatio[nCam][nIndex] < m_ratio){//핀홀S
				pData->m_nDefectType[nCam][nIndex] = DCLASS_GBR_PIMUL;
			}
			else if(pData->m_dSize[nCam][nIndex] >= pData->m_pinholeLargeSize[nCam]	//핀홀L
						&& pData->m_dSize[nCam][nIndex] < pData->m_pinholeGroupSize[nCam]
						&& pData->m_fDefectRatio[nCam][nIndex] < m_ratio){
				pData->m_nDefectType[nCam][nIndex] = DCLASS_GBR_PINHOLE_L;
			}
			else if(pData->m_dSize[nCam][nIndex] >= pData->m_pinholeGroupSize[nCam]//원형//막뜯김
						&& pData->m_fDefectRatio[nCam][nIndex] < m_ratio){
				pData->m_nDefectType[nCam][nIndex] = DCLASS_GBR_PINHOLE_BIT;
			}
			else if(pData->m_dSize[nCam][nIndex] >= pData->m_dWhiteSize//선형//스탠딩파이버
						&& pData->m_fDefectRatio[nCam][nIndex] > m_ratio){
				pData->m_nDefectType[nCam][nIndex] = DCLASS_GBR_PINHOLE_C_L;
			}
			else if(pData->m_dSize[nCam][nIndex] >= pData->m_pinholeGroupSize[nCam]
						&& pData->fpDefectVMax[nCam][nIndex] >= bitSurfaceThUpValue){//막뜯김
				pData->m_nDefectType[nCam][nIndex] = DCLASS_GBR_PINHOLE_BIT;
			}
			else{
				pData->m_nDefectType[nCam][nIndex] = DCLASS_GBR_PINHOLE_BIT;
			}
		}
	
		//흑점
		else{
			pData->m_nDefectType[nCam][nIndex] = DCLASS_GBR_LIMUL;	//black
		}
	}

}

void CInspect::WriteLogIns(CString path, CString fileName, CString strdata)
{

	CStdioFile   file;
	CString filename;
	CString strpath,strpath1;
	CString str;

	CTime ttime = CTime::GetCurrentTime();
	CString kk = ttime.Format("%Y%m%d");
	CString strTime = ttime.Format("[%Y %m %d %H:%M:%S]");

	//strpath.Format("C:\\Glim\\Log\\");
	strpath1.Format("c:\\Glim\\");
	CreateDirectory(strpath1,NULL);	
	strpath1.Format("c:\\Glim\\Log\\");
	CreateDirectory(strpath1,NULL);	
	strpath1.Format("c:\\Glim\\Log\\LowData\\");
	CreateDirectory(strpath1,NULL);	
	strpath1.Format("c:\\Glim\\Log\\LowData\\%s\\",kk);//년월일
	CreateDirectory(strpath1,NULL);	
	strpath1.Format("c:\\Glim\\Log\\LowData\\%s\\%s\\",kk,path);//년월일\\lot
	CreateDirectory(strpath1,NULL);	

	filename.Format("%s%s.txt",strpath1, fileName);//년월일\lot\GL601T


	if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
	{		
		file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText);
		file.WriteString(strdata);
		file.WriteString("\n");	
		file.Close();
	}
	else
	{
		file.SeekToEnd();			
		file.WriteString(strdata);
		file.WriteString("\n");
		file.Close(); 
	}	
}

void CInspect::WriteInsLow( CData* pData,CString strLot, CString fileName, CString strdata)
{

	CStdioFile   file;
	CString filename;
	CString strpath,strpath1;
	CString str;

	CTime ttime = CTime::GetCurrentTime();
	CString kk = ttime.Format("%Y%m%d");
	CString strTime = ttime.Format("[%Y %m %d %H:%M:%S]");

	//strpath.Format("C:\\Glim\\Log\\");
	strpath1.Format("c:\\Glim\\");
	CreateDirectory(strpath1,NULL);	
	strpath1.Format("c:\\Glim\\Log\\");
	CreateDirectory(strpath1,NULL);	
	strpath1.Format("c:\\Glim\\Log\\LowData\\");
	CreateDirectory(strpath1,NULL);	
	strpath1.Format("c:\\Glim\\Log\\LowData\\%s\\",kk);//년월일
	CreateDirectory(strpath1,NULL);	
	strpath1.Format("c:\\Glim\\Log\\LowData\\%s\\%s\\",kk,strLot);//년월일\\lot
	CreateDirectory(strpath1,NULL);	

	filename.Format("%s%s.txt",strpath1, fileName);//년월일\lot\GL601T


	if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
	{		
		file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText);
		file.WriteString(strdata);
		file.WriteString("\n");	
		file.Close();
	}
	else
	{
		file.SeekToEnd();			
		file.WriteString(strdata);
		file.WriteString("\n");
		file.Close(); 
	}	
}

double CInspect::GetSharpness(CImage *pImage,  CData* pData,int nCam)
{
	int i,j;
	unsigned char* fm = pImage->GetImagePtr();
	int nPitch = pImage->GetWidth();
	int nHeight = pImage->GetHeight();
	int nSkip = 8;
	double dRet=0.;
	double dSum=0.;
	int cn = 0;
	for(j=0; j<nHeight; j+=nSkip){
		for(i=pData->m_rectIns[nCam].left; i<pData->m_rectIns[nCam].right; i++){
			dSum += abs(*(fm+j*nPitch+i) - *(fm+j*nPitch+i-1)); 
			cn++;
		}
	}
	if(cn)
		dRet = (dSum/cn)*10;
	else
		dRet = 0;
	return dRet;
}
double CInspect::GetSharpness1(int nCam,CImage* pImage,CRect rt,int nWidth)
{
	int i,j;
	int nPitch = nWidth;// pImage->GetWidth();
	int nHeight = pImage->GetHeight();
	unsigned char* fm = pImage->GetImagePtr();
	int nSkip = 8;
	double dRet=0.;
	double dSum=0.;
	int cn = 0;
	for(j=rt.top; j<rt.bottom; j+=nSkip){
		for(i=rt.left; i<rt.right; i++){
			dSum += abs(*(fm+j*nWidth+i) - *(fm+j*nWidth+i-1)); 
			cn++;
		}
	}
	if(cn)
		dRet = (dSum/cn)*10;
	else
		dRet = 0;
	return dRet;
}

void CInspect::FindVSlitDefect(CImage* pImage, CData* pData,int nCam)
{
	int ret = 0;
	int i,j,k,nc=0;
	CRect rect = pData->m_rectIns[nCam];
	int nSkipX = 1;
	int nSkipY = 2;
	int nx,ny,ncnt=0;
	unsigned char* fm = pImage->GetImagePtr();
	double	dv= 0.9;

	int m_nHeight = 0;
	int m_nPitch = 0;
	if(nCam == 0){
		m_nPitch = m_nPitch0;
		m_nHeight = m_nHeight0;
	}
	else{
		m_nPitch = m_nPitch1;
		m_nHeight = m_nHeight1;
	}

//	pData->m_nMaxBrightness[nCam] = 0;
	double* dData= (double*)malloc(sizeof(double)*m_nPitch);
	double* dData1= (double*)malloc(sizeof(double)*m_nPitch);
	double* dData2= (double*)malloc(sizeof(double)*m_nPitch);
	double* dData3= (double*)malloc(sizeof(double)*m_nPitch);

	memset(dData, 0, sizeof(double)*m_nPitch);
	memset(dData1, 0, sizeof(double)*m_nPitch);
	memset(dData2, 0, sizeof(double)*m_nPitch);
	memset(dData3, 0, sizeof(double)*m_nPitch);
	int ncc = 0;
	double nSkipValuel,nSkipValuer;
	nSkipValuel=nSkipValuer= 0;
	for(j=rect.top; j<rect.bottom; j+=nSkipY)
	{
		for(i=rect.left; i<rect.right; i+=nSkipX)
		{	dData3[i] += fm[j*m_nPitch+i];		
		}
		ncnt++;
	}
	for(i=rect.left+2; i<rect.right-2; i++)
	{
		nSkipValuel = (dData3[i]/(ncnt-2))-(dData3[i-1]/(ncnt-2));
		nSkipValuer = (dData3[i]/(ncnt-2))-(dData3[i+1]/(ncnt-2));
		if(nSkipValuel<=-dv && nSkipValuer<=-dv)
		{
			if(nSkipValuel<=nSkipValuer)
				for(j=rect.top; j<rect.bottom; j+=nSkipY)
					fm[j*m_nPitch+i] = fm[j*m_nPitch+i+1];
			else
				for(j=rect.top; j<rect.bottom; j+=nSkipY)
					fm[j*m_nPitch+i] = fm[j*m_nPitch+i-1];
					
			ncc++;
		}
	}

	int nTmpH = 0;
	int nOffSetY = 128;//128;//200
	double dMax=0;
	for(k=0;k<16;k++)
	{//400
		if(pData->m_nDefectCount[nCam] == MAX_DEFECT){
			goto done;//return;
		}

		memset(dData, 0, sizeof(double)*m_nPitch);
		memset(dData1, 0, sizeof(double)*m_nPitch);
		memset(dData2, 0, sizeof(double)*m_nPitch);
		memset(dData3, 0, sizeof(double)*m_nPitch);
		ncnt = 0;
		nTmpH = k*nOffSetY;
		for(j=nTmpH; j<nTmpH+(nOffSetY*2); j+=nSkipY)
		{
			if(j>=m_nHeight)	break;
			for(i=rect.left+3; i<rect.right-3; i+=nSkipX)
			{
				dData1[i] += abs(fm[j*m_nPitch+i]-fm[j*m_nPitch+i+2])+abs(fm[j*m_nPitch+i]-fm[j*m_nPitch+i-2]);
				dData2[i] += fm[j*m_nPitch+i];		
			}
			ncnt++;
		}
		for(i=rect.left+5; i<rect.right-5; i++)
		{
			dData[i] += fabs(dData1[i]-dData1[i+2])+fabs(dData1[i]-dData1[i-2]);
		}

		double dSum=0;
		int nTemp = pData->m_nThWhiteValue[nCam];
		CPoint ptNG;
		for(i=rect.left+10; i<rect.right-5; i++)
		{
			dSum += dData[i];
			nc++;
			if(dMax < dData[i])
				dMax = dData[i];
			if(pData->m_nMaxBrightness[nCam] < (int)dMax)
				pData->m_nMaxBrightness[nCam] = (int)dMax;

			if(dData[i] > pData->m_dThUp[nCam])//dMax)
			{
				if(pData->m_nDefectCount[nCam] == MAX_DEFECT){
					goto done;//return;
				}

				dMax = dData[i];
				ptNG.x = i;
				ptNG.y = nTmpH+nOffSetY;//m_nHeight/2;
				pData->m_bResult[nCam][pData->m_nDefectCount[nCam]]		= FALSE;
				
				pData->m_nDefectVMax[nCam][pData->m_nDefectCount[nCam]] = (int)dMax;
				pData->m_nDefectVMin[nCam][pData->m_nDefectCount[nCam]] = (int)dMax;

				nx = pData->m_ptDefect[nCam][pData->m_nDefectCount[nCam]].x = ptNG.x;
				ny = pData->m_ptDefect[nCam][pData->m_nDefectCount[nCam]].y = ptNG.y;

				if(nx-10<0) nx = 10;
				if(nx+10>m_nPitch) nx = m_nPitch-10;
				for(i=nx-10;i<nx+10;i++)
				{
					dData2[i] = dData2[i]/ncnt;
				}
				for(i=nx-6;i<nx+6;i++)
				{
					pData->m_nLv[nCam] = int(dData2[i]-dData2[i-4]);
					pData->m_nRv[nCam] = int(dData2[i]-dData2[i+4]);
					if(pData->m_nLv[nCam]>=nTemp && pData->m_nRv[nCam]>=nTemp)//백선
					{
						pData->m_nDefectType[nCam][pData->m_nDefectCount[nCam]] = DCLASS_NEL3_SCRATCH;
						pData->m_bDefectWhite[nCam][pData->m_nDefectCount[nCam]] = TRUE;
						if(pData->m_nMaxBrightness[nCam] < (int)dMax)
							pData->m_nMaxBrightness[nCam] = (int)dMax;

						ret = 1;
						pData->m_nColorGap[nCam] = 1;
						break;
					}
					else if(pData->m_nLv[nCam]<=-nTemp && pData->m_nRv[nCam]<=-nTemp)//흑선
					{
						pData->m_nDefectType[nCam][pData->m_nDefectCount[nCam]] = DCLASS_NEL3_SCRATCH;	
						pData->m_bDefectWhite[nCam][pData->m_nDefectCount[nCam]] = FALSE;
						if(-pData->m_nMaxBrightness[nCam] < (int)dMax)
							pData->m_nMaxBrightness[nCam] = -(int)dMax;
						pData->m_nDefectVMax[nCam][pData->m_nDefectCount[nCam]] = -(int)dMax;
						pData->m_nDefectVMin[nCam][pData->m_nDefectCount[nCam]] = -(int)dMax;
						pData->m_nColorGap[nCam] = -1;
						ret = 1;
						break;
					}
					else
					{
						pData->m_nDefectType[nCam][pData->m_nDefectCount[nCam]] = DCLASS_NEL3_SCRATCH;
						pData->m_bDefectWhite[nCam][pData->m_nDefectCount[nCam]] = FALSE;
						if(-pData->m_nMaxBrightness[nCam] < (int)dMax)
							pData->m_nMaxBrightness [nCam]= -(int)dMax;
						pData->m_nDefectVMax[nCam][pData->m_nDefectCount[nCam]] = -(int)dMax;
						pData->m_nDefectVMin[nCam][pData->m_nDefectCount[nCam]] = -(int)dMax;
						pData->m_nColorGap[nCam] = 0;
						ret = 1;
					}

				}
				pData->m_nMinBrightness[nCam] = 0;
				pData->m_rectDefect[nCam][pData->m_nDefectCount[nCam]].SetRect(ptNG.x,ptNG.y,ptNG.x,ptNG.y);
				pData->m_rectDefect[nCam][pData->m_nDefectCount[nCam]].InflateRect(BAD_IMG_WIDTH/2, BAD_IMG_HEIGHT/2);
				ValidRect(&pData->m_rectDefect[nCam][pData->m_nDefectCount[nCam]],nCam,1);
				UpdateNGImage(pImage, pData,nCam);
				if(ret){
					pData->m_nDefectCount[nCam]++;
					pData->m_nDefectResultCount[nCam]++;
				}
				i += 350;
			}
		}
		pData->m_dSharpness[nCam] = dSum/(nc);
	}
done:
	free(dData);
	free(dData1);
	free(dData2);
	free(dData3);
}
void CInspect::ValidRect(CRect *rect,int nCam,int nflag)
{
	int m_nHeight = 0;
	int m_nPitch = 0;

	m_nPitch = CAM_WIDTH_CIS;
	m_nHeight = CAM_HEIGHT_CIS;

	CRect rectImg(0,0,m_nPitch, m_nHeight);

	if(rect->left	< 0)			rect->OffsetRect(-rect->left, 0);
	if(rect->top	< 0)			rect->OffsetRect(0, -rect->top);
	if(nflag)
	{
		if(rect->right	>= m_nPitch)	rect->OffsetRect(m_nPitch-rect->right, 0);
		if(rect->bottom >= m_nHeight)	rect->OffsetRect(0, m_nHeight-rect->bottom);
	}
	else
	{
		if(rect->right	>= m_nPitch*2)	rect->OffsetRect(m_nPitch*2-rect->right, 0);
		if(rect->bottom >= m_nHeight*2)	rect->OffsetRect(0, m_nHeight*2-rect->bottom);
	}
}

extern int g_frame_num;


void CInspect::WriteLog(int nCam,CString strdata)
{

	CStdioFile   file;
	CString filename;
	CString strpath;
	CString str;
	strpath.Format("C:\\Glim\\Log\\");
	CreateDirectory(strpath,NULL);	
	filename.Format("%sInspLog_%d.txt",strpath,nCam);

	if(file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText))
	{		
		file.WriteString(strdata);
		file.Close();
	}	

}


void CInspect::FindScratch5(CImage* pImage, CData* pData,int nCam)
{
//	if(((CVisWebApp*)AfxGetApp())->m_debugLogWrite == TRUE){
//		((CVisWebApp*)AfxGetApp())->WriteLog(PATH_DEBUG_LOG, "debug_log", "FindScratch5");
//	}
//	
//	if(pData->m_nDefectCount[nCam] >= MAX_DEFECT)	return;
//
//	unsigned char* fm = pImage->GetImagePtr();
//	CRect rt = pData->m_rectIns[nCam];
//
//
//	BYTE * fmtmp = new BYTE[pData->m_nCameraWidth*pData->m_nCameraHeight];
//	memcpy(fmtmp,fm,pData->m_nCameraWidth*pData->m_nCameraHeight);
//	if(rt.left < 100)rt.left = 200;
////	rt.left = 600;
//	if(rt.right>4096-100)rt.right = 4096-200;
//	int nProj[4096],nProj1[4096];
//	memset(nProj,0,sizeof(int)*4096);
//	memset(nProj1,0,sizeof(int)*4096);
//
//	CRect rt2;// = pData->m_rectIns[nCam];
//	rt2.SetRect(rt.left,rt.top,rt.right,rt.bottom);
//
//	if(((CVisWebApp*)AfxGetApp())->m_debugLogWrite == TRUE){
//		((CVisWebApp*)AfxGetApp())->WriteLog(PATH_DEBUG_LOG, "debug_log", "scr-Profile");
//	}
//
//	m_nCheckProject = 1;
//	int ndataSum  = 5,ntmp = 0;
//	if(((CVisWebApp*)AfxGetApp())->m_debugLogWrite == TRUE){
//		((CVisWebApp*)AfxGetApp())->WriteLog(PATH_DEBUG_LOG, "debug_log", "scr-delNoise");
//	}
//	
//	for(int i=rt.left;i<rt.right-ndataSum;i++)//noise 제거
//	{
//		ntmp = 0;
//		for(int j=i;j<i+ndataSum;j++)
//		{
//			ntmp += pData->m_nProjectX[nCam][i];
//		}
//		nProj1[i] = ntmp/ndataSum;
//
//	}
//	
//	int ngap = 8;
//	int nWhiteTh = pData->m_nCycleUse[nCam];// 20;//caster(sc5함수에서 사용) 
//	if(((CVisWebApp*)AfxGetApp())->m_debugLogWrite == TRUE){
//		((CVisWebApp*)AfxGetApp())->WriteLog(PATH_DEBUG_LOG, "debug_log", "scr-detectLine");
//	}
//	
//	int maxVal = 0;
//	for(int i=rt.left+15;i<rt.right-25-ndataSum-ngap;i++)
//	{
////미분
//		if(maxVal < nProj1[i+ngap] - nProj1[i]){
//			maxVal = nProj1[i+ngap] - nProj1[i];
//		}
//		if(maxVal < (nProj1[i]-nProj1[i+ngap])){
//			maxVal = (nProj1[i]-nProj1[i+ngap]);
//		}
//		if((nProj1[i+ngap] - nProj1[i] >nWhiteTh) || (nProj1[i]-nProj1[i+ngap]  >nWhiteTh) )
//		{
//			pData->m_bDefectWhite[nCam][pData->m_nDefectCount[nCam]]= TRUE;				//백색이물
//			pData->m_bResult[nCam][pData->m_nDefectCount[nCam]]		= FALSE;
//			pData->m_nDefectVMax[nCam][pData->m_nDefectCount[nCam]] = (nProj1[i]-nProj1[i-ngap] )*10;
//			pData->m_nDefectVMin[nCam][pData->m_nDefectCount[nCam]] = (nProj1[i]-nProj1[i-ngap] )*10;
//			pData->m_ptDefect[nCam][pData->m_nDefectCount[nCam]].x = i;
//			pData->m_ptDefect[nCam][pData->m_nDefectCount[nCam]].y = 1000;
//			pData->m_rectDefect[nCam][pData->m_nDefectCount[nCam]].SetRect(i,1000,i,1000);
//			pData->m_rectDefect[nCam][pData->m_nDefectCount[nCam]].InflateRect(BAD_IMG_WIDTH/2, BAD_IMG_HEIGHT/2);
//			ValidRect(&pData->m_rectDefect[nCam][pData->m_nDefectCount[nCam]],nCam,1);
//			pData->m_nDefectType[nCam][pData->m_nDefectCount[nCam]] = DCLASS_GBR_CIMUL;
//			UpdateNGImage(pImage, pData,nCam);
//			pData->m_nDefectCount[nCam]++;// Normal
//			break;
//
//		}
//	}
//
//	int nCont = 0,nIsol=0,nflag = 0,nmax1 = 0;
//	int nTh11 = pData->m_dOpticsDistanceY[nCam];
//	int nStart = 0,nConnect = 0,nTop = 0,nBottom = 0,nleft=0,nright=0,m,n1;
//	int nmaxline =  pData->m_dEdgeBright[nCam];//70;//param 8 //사용하면 안됨.
//	int nlinecount = 0,linecheck = 0,n11=1;
//
//	if(((CVisWebApp*)AfxGetApp())->m_debugLogWrite == TRUE){
//		((CVisWebApp*)AfxGetApp())->WriteLog(PATH_DEBUG_LOG, "debug_log", "scr-lineChek");
//	}
//	
//	for(int j=rt.top;j<rt.bottom-100;j+=n11){
//		nlinecount = linecheck=0;
//		for(int i=rt.left;i<rt.right-20;i++){
//			if(*(fmtmp+(j)*pData->m_nCameraWidth+(i))<nProj1[i]-nTh11 && *(fmtmp+(j+1)*pData->m_nCameraWidth+(i))<nProj1[i+1]-nTh11 &&*(fmtmp+(j)*pData->m_nCameraWidth+(i+1))<nProj1[i]-nTh11 && *(fmtmp+(j+1)*pData->m_nCameraWidth+(i+1))<nProj1[i+1]-nTh11){
//			//	 *(fmtmp+(j)*IMAGE_X+(i)) = 0;
//				nStart = j;
//				m=i;
//				n1 = m+3;
//				
//				for(int k=j+2;k<rt.bottom-100;k++){
//					nConnect = 0;
//					linecheck=0;
//					for(int l=m-1;l<n1;l++){
//						nTop = *(fmtmp+(k)*pData->m_nCameraWidth+(l));
//						if(*(fmtmp+(k)*pData->m_nCameraWidth+(l))<nProj1[l]-nTh11){
////							for(int l1=m-1;l<m+3;l++)
//							if(pData->m_bCrossBlobImg[nCam])
//								*(fm+(k)*pData->m_nCameraWidth+(l)) = 0;//nProj1[l1];
//							m = l;
//							linecheck++;
//							nConnect=1;
//							break;
//						}
//					}
//					if(linecheck>nlinecount )
//						nlinecount=linecheck;
//					if(nConnect==0 || (nConnect && k-nStart > nmaxline+1)){
//						nBottom = k;
//						if(nleft<nBottom-nStart){
//							nleft=nBottom-nStart;
//							nright = i;
//						}
//						if(nBottom-nStart>nmaxline){
//							int overlapDefectFrameNum = 10; //ljh 꼽침과검 막기위해 현장 권취 텐션롤 움직임.
//							int nXposDiffVal = 0;
//							int nXposDiffValue = 100;
//							pData->m_overlapDefectPosX[pData->m_overlapDefectCnt] = i;
//							pData->m_overlapDefectCnt++;
//
//							if(pData->m_overlapDefectCnt >= overlapDefectFrameNum){
//								for(int ni=1; ni<pData->m_overlapDefectCnt; ni++){
//									nXposDiffVal += abs(pData->m_overlapDefectPosX[0] - pData->m_overlapDefectPosX[ni]);
//								}
//								
//								if(pData->m_overlapDefectCnt != 0){
//									nXposDiffVal /= pData->m_overlapDefectCnt;
//									//TRACE("xPodDiff : %d \n", nXposDiffVal);
//								}
//							}
//							if(pData->m_overlapDefectCnt >= overlapDefectFrameNum && nXposDiffVal <= nXposDiffValue){
//								pData->m_bDefectWhite[nCam][pData->m_nDefectCount[nCam]]= TRUE;				//백색이물
//								pData->m_bResult[nCam][pData->m_nDefectCount[nCam]]		= FALSE;
//								pData->m_nDefectVMax[nCam][pData->m_nDefectCount[nCam]] = nleft;
//								pData->m_nDefectVMin[nCam][pData->m_nDefectCount[nCam]] = nleft;//dprojAve[i]*10;
//								pData->m_ptDefect[nCam][pData->m_nDefectCount[nCam]].x = i;
//								pData->m_ptDefect[nCam][pData->m_nDefectCount[nCam]].y = j;
//								pData->m_rectDefect[nCam][pData->m_nDefectCount[nCam]].SetRect(i,j,i,j);
//								pData->m_rectDefect[nCam][pData->m_nDefectCount[nCam]].InflateRect(BAD_IMG_WIDTH/2, BAD_IMG_HEIGHT/2);
//								ValidRect(&pData->m_rectDefect[nCam][pData->m_nDefectCount[nCam]],nCam,1);
//								pData->m_nDefectType[nCam][pData->m_nDefectCount[nCam]] = DCLASS_GBR_SCRATCH;
//								UpdateNGImage(pImage, pData,nCam);
//								pData->m_nDefectCount[nCam]++;
//								nIsol = 0;
//								nflag = 1;i+=100;
//								pData->m_nLinePos = nright;
//								pData->m_dLineValue = nleft;
//								pData->m_overlapDefectCnt = 0;
//							}
//
//							if(pData->m_nDefectCount[nCam] >= 1){
//								delete[] fmtmp;
//								pData->m_overlapDefectCnt = 0;
//								if(((CVisWebApp*)AfxGetApp())->m_debugLogWrite == TRUE){
//									((CVisWebApp*)AfxGetApp())->WriteLog(PATH_DEBUG_LOG, "debug_log", "FindScratch5-rt1-end");
//								}
//
//								return;
//							}
//
//							if(pData->m_overlapDefectCnt >= overlapDefectFrameNum){
//								pData->m_overlapDefectCnt = 0;
//							}
//
//							delete[] fmtmp;
//							if(((CVisWebApp*)AfxGetApp())->m_debugLogWrite == TRUE){
//								((CVisWebApp*)AfxGetApp())->WriteLog(PATH_DEBUG_LOG, "debug_log", "FindScratch5-rt2-end");
//							}
//			
//							return;
//						}
//
//						break;
//					}
//				}
//			}
//			else
//			{
//			//	 *(fmtmp+(j)*IMAGE_X+(i)) = 255;
//			}
//		}
//		if(nlinecount < 10)
//			n11 = 4;
//		else				n11 = 1;
//
//	}
//	pData->m_nLinePos = nright;
//	pData->m_dLineValue = nleft;
//
//	delete[] fmtmp;
//
//	if(((CVisWebApp*)AfxGetApp())->m_debugLogWrite == TRUE){
//		((CVisWebApp*)AfxGetApp())->WriteLog(PATH_DEBUG_LOG, "debug_log", "FindScratch5-end");
//	}

}

int	CInspect::GetImageData(CImage* pImage, CData* pData,int nCam,int nEdge,CRect rtInsp)//Edge detect, AverageBrightness, FullImageProfileData[x], ROI Set
{//nedge=-1일때 L->R 에지 검사 0일때 RT Insp 사용 1일때 R->l에지검사  
	int nw = pImage->GetWidth();
	int nh = pImage->GetHeight();
	pData->ResetData(nCam);
	int ntmp = 0,ntmp1=0,nc=0;
	pData->m_nLineThCount = 0;
	CString str,str1;
	BYTE * fm = pImage->GetImagePtr();
	
	int nx1,ny1,nw1 = nw/pData->m_nLineReduce;
	for(int i=0;i<nh;i++)
	{
		//reduce 만큼 점프해서 검사하자 
		ny1 = i/pData->m_nLineReduce;

		if(MAX_CAMERAS<2)
		{
			for(int j=0;j<nw;j++){
				pData->m_nProjectX[nCam][j] += *(fm+i*nw+j);//Full Data를 다 사용한다?? 왜??
				if(pData->m_nVisionLine==GL4)//압축 영상을 만드네 왜?
					*(m_fmLine+(ny1)*(nw1)+(j/pData->m_nLineReduce)) = *(fm+i*nw+j);
			}
		}
		else
		{
			for(int j=0;j<nw;j++)
				pData->m_nProjectX[nCam][j] += *(fm+i*nw+j);//Full Data를 다 사용한다?? 왜??
			i +=pData->m_nLineReduce;
		}

	}//여기서 평균 밝기를 구하면 미검영역의 밝기도 포함된다.???
	//insrect가 0일경우 어떻게?? 
//	for(int j=rtInsp.left;j<rtInsp.right;j++)
	for(int j=0;j<nw;j++)
	{
		if(MAX_CAMERAS>1)
			pData->m_nProjectX[nCam][j] /= pData->m_nLineReduce;
		else
			pData->m_nProjectX[nCam][j] /= nh;

		ntmp1+=pData->m_nProjectX[nCam][j];
		//str1.Format("BaseProfile%d",nCam);str.Format("%d , %d ",j,pData->m_nProjectX[nCam][j]);WriteLog(str1,str);Sleep(1);//Log로 테스트시.
		nc++;
	}
//에지 찾기 추가할것.//chcho
	int nEdgeth = 5;BOOL bAve = FALSE;
	if(pData->m_nVisionLine==GL4)nEdgeth = 4;
//	if(pData->m_strMachineName.Find("CA")>=0 && pData->m_nVisionLine==GL3)nEdgeth = 10;
	if(nEdge==-1){//L->R
		nc=ntmp1=0;
		for(int i=10;i<nw-6;i++){
			if(bAve==FALSE && abs(pData->m_nProjectX[nCam][i]-pData->m_nProjectX[nCam][i+4]) >= nEdgeth && abs(pData->m_nProjectX[nCam][i+1]-pData->m_nProjectX[nCam][i+5]) >= nEdgeth&&(pData->m_nProjectX[nCam][i]>20 ||pData->m_nProjectX[nCam][i+4]>20)){
				pData->m_rectIns[nCam].left = i;bAve=TRUE;
				if(pData->m_nTacXpos[0]>0)pData->m_rectIns[nCam].left += pData->m_nTacXpos[0];
				pData->m_nPolarEdge[0]=i;
			}
			else if(bAve==TRUE && pData->m_rectIns[nCam].left<i){
				ntmp1+=pData->m_nProjectX[nCam][i];nc++;}
		}
	}
	else if(nEdge== 1){//R->L
		nc=ntmp1=0;
		for(int i=nw-10;i>6;i--){
			if(bAve==FALSE &&abs(pData->m_nProjectX[nCam][i]-pData->m_nProjectX[nCam][i-4]) >= nEdgeth && abs(pData->m_nProjectX[nCam][i-1]-pData->m_nProjectX[nCam][i-5]) >= nEdgeth &&(pData->m_nProjectX[nCam][i]>20 ||pData->m_nProjectX[nCam][i-4]>20)){
				pData->m_rectIns[nCam].right = i;bAve=TRUE;
				if(pData->m_nTacXpos[0]>0)pData->m_rectIns[nCam].right -= pData->m_nTacXpos[0];
				pData->m_nPolarEdge[0]=i;
			}
			else if(bAve==TRUE &&pData->m_rectIns[nCam].right>i){
				ntmp1+=pData->m_nProjectX[nCam][i];nc++;}
		}
	}
	else{
		pData->m_rectIns[nCam]=rtInsp;//.SetRect(0,0,nw,nh);
		if(nEdge>1)pData->m_rectIns[nCam].left = nEdge;
		else if(nEdge<-1)pData->m_rectIns[nCam].right = pData->m_nCameraWidth+nEdge;
		pData->m_nPolarEdge[0]=0;
	}

	if(pData->m_rectIns[nCam].left<0)pData->m_rectIns[nCam].left = 0;
	if(pData->m_rectIns[nCam].right<0)pData->m_rectIns[nCam].right = 0;
	if(pData->m_rectIns[nCam].left>=pData->m_nCameraWidth)pData->m_rectIns[nCam].left = pData->m_nCameraWidth-1;
	if(pData->m_rectIns[nCam].right>=pData->m_nCameraWidth)pData->m_rectIns[nCam].right = pData->m_nCameraWidth-1;
//에지 자동캐..킹 검증시 사용 ㅊ캐스터와 코터는 카메라 위치가 반대
// 	if(pData->m_bDualNotIns){
// 		if( pData->m_strComName.Find("301")>=0 || pData->m_strComName.Find("401")>=0 && pData->m_nInspDirection[nCam]%2==0 )pData->m_rectIns[nCam].right = pData->m_nDualNotIns;
// 		else if( pData->m_strComName.Find("308")>=0 || pData->m_strComName.Find("411")>=0&& pData->m_nInspDirection[nCam]%2==0 )pData->m_rectIns[nCam].left = pData->m_nDualNotIns;
// 	}
// 	else{
// 		//if(pData->m_strMachineName.Find("CT01")>=0 ){
// 		//	if( pData->m_strComName.Find("301")>=0 ||pData->m_strComName.Find("401")>=0  && pData->m_nInspDirection[nCam]%2==0)pData->m_rectIns[nCam].right = pData->m_nCameraWidth;
// 		//	else if( pData->m_strComName.Find("308")>=0 || pData->m_strComName.Find("411")>=0 && pData->m_nInspDirection[nCam]%2==0 )pData->m_rectIns[nCam].left =0;
// 		//}
// 	}
///////////////////////////////////////////////
	//라인 검사
	if(nc<1)return 0;
	
	if(pData->m_nVisionLine==GL4 ){
		nx1 = nw/pData->m_nLineReduce;
		ny1 = nh/pData->m_nLineReduce;
		int nCut = pData->m_nLineTh1;//15;//param check
		int nlineth = ntmp1/nc;
		BYTE * fmLine1 = new BYTE[nx1*ny1];
		memset(fmLine1,0,nx1*ny1);
		int ntol = 10;
		for(int i=0;i<ny1;i++)
		{
			for(int j=0;j<nx1;j++){
				if(i<= ntol|| j<=ntol ||i>=ny1-ntol || j >= nx1-ntol)
					*(fmLine1+i*nx1+j) = 0;
				else{
					nlineth = pData->m_nProjectX[nCam][j*pData->m_nLineReduce];
					if(*(m_fmLine+i*nx1+j) > nlineth + nCut)			
						*(fmLine1+i*nx1+j) = 255;
					else												
						*(fmLine1+i*nx1+j) = 0;
				}
			}
		} 
		CRect rt1;
//검사 영역 설정
		rt1.SetRect(pData->m_rectIns[nCam].left/pData->m_nLineReduce+ntol,0,pData->m_rectIns[nCam].right/pData->m_nLineReduce-ntol,nh/pData->m_nLineReduce);
		if(rt1.Width()<15) {
			delete fmLine1;
			return ntmp1/nc;
		}
		fnDilate(fmLine1,m_fmLine,nx1,rt1,1);
		fnDilate(m_fmLine,fmLine1,nx1,rt1,1);
		memcpy(m_fmLine,fmLine1,nx1*ny1);

//		fnDilate(fmLine1,m_fmLine,nx1,rt1,1);

		//chain

//		FChain_SetChainData(1,m_fmLine,1,0,0,10000,nx1,ny1);
		int nBlobCount = 0;// FChain_FastChain(rt1.left, 0, rt1.right-1,ny1-1);

		double dTemp = 0,dBlobSize = 0;
		int nBlobNo = 0;
		double dCx,dCy,dAngle,dcompact,dx1,dy1;
		for(int i=0;i<nBlobCount;i++)
		{
//			FChain_Area(i, &dTemp);//			dTemp = m_pChain->Chain_Area(i);ttt
			if(dTemp<2)continue;
			if(dTemp>=dBlobSize)//최대 불량 사이즈.
			{
				nBlobNo = i;
				dBlobSize = dTemp;//면적
			}
			if(dTemp>25 && dTemp<1000){
				if(pData->m_nLineThCount>= MAX_DEFECT-1){
					delete fmLine1;
					return ntmp1/nc;
				}
//				dx1 = (FChain_FindMaxX(i) - FChain_FindMinX(i));// * pData->m_dScaleFactorX[nCam]*pData->m_nRecude;
//				dy1 = (FChain_FindMaxY(i) - FChain_FindMinY(i));// *pData->m_dScaleFactorY[nCam]*pData->m_nRecude;	
//				FChain_Center(i, &dCx, &dCy);
//				FChain_FindAngle(i, &dAngle);
//				FChain_FindCompactness(i,&dcompact);
				dcompact = dcompact;
				if(dy1 <pData->m_nLineLEngthCut || dy1/dx1 <2)//20
					continue;

//				pData->m_rtLine[pData->m_nLineThCount].SetRect(FChain_FindMinX(i)*pData->m_nLineReduce,nh-FChain_FindMinY(i)*pData->m_nLineReduce,FChain_FindMaxX(i)*pData->m_nLineReduce,nh-FChain_FindMaxY(i)*pData->m_nLineReduce);
//				pData->m_ptLine[pData->m_nLineThCount].SetPoint(dCx*pData->m_nLineReduce,nh-dCy*pData->m_nLineReduce);

				//defect type
				int nLinecount = 768;
				pData->m_bDefectWhite[nCam][pData->m_nLineThCount] = pData->m_nRealDefectInfo[pData->m_nLineThCount][5]= TRUE;
				pData->m_ptDefect[nCam][pData->m_nLineThCount].x= pData->m_nRealDefectInfo[pData->m_nLineThCount][7]= pData->m_ptLine[pData->m_nLineThCount].x;
				pData->m_ptDefect[nCam][pData->m_nLineThCount].y= pData->m_nRealDefectInfo[pData->m_nLineThCount][8]= pData->m_ptLine[pData->m_nLineThCount].y;
//				pData->m_rectDefect[0][pData->m_nRealDefectCount] = rtMeshTrans[i][nIndex];
				BYTE * fmdefect = pData->m_pImageDefect[0][pData->m_nLineThCount]->GetImagePtr();//new BYTE[BAD_IMG_WIDTH*BAD_IMG_HEIGHT];

				CRect rtsc,rtsc1;
				int nbadx = BAD_IMG_WIDTH*0.5;
				int nbady = BAD_IMG_HEIGHT*0.5;
				int nMax1,nMin1;
				rtsc.SetRect(pData->m_ptLine[pData->m_nLineThCount].x-nbadx,((pData->m_ptLine[pData->m_nLineThCount].y)/nLinecount)*nLinecount,pData->m_ptLine[pData->m_nLineThCount].x+nbadx,((pData->m_ptLine[pData->m_nLineThCount].y)/nLinecount)*nLinecount+nLinecount);
				pData->m_rectDefect[0][pData->m_nLineThCount] = rtsc1 = rtsc;
				rtsc1.bottom = nh-rtsc.top;
				rtsc1.top = nh-rtsc.bottom;
				GetPeakValue(fm,pData,nCam,rtsc1,&nMax1,&nMin1);
				ImageSelectCopyScratch(fm,fmdefect,pData->m_nCameraWidth,pData->m_nCameraHeight,rtsc1,BAD_IMG_WIDTH,BAD_IMG_HEIGHT,0,0,nLinecount/128);

				//max data 
				pData->m_nDefectVMax[nCam][pData->m_nLineThCount]=pData->m_nRealDefectInfo[pData->m_nLineThCount][0]= nMax1;
				pData->m_nDefectVMin[nCam][pData->m_nLineThCount]=pData->m_nRealDefectInfo[pData->m_nLineThCount][1]= 0;

				

				pData->m_nRealDefectInfo[pData->m_nLineThCount][2]= pData->m_dSizeX[0][pData->m_nLineThCount] = dx1*pData->m_nLineReduce* pData->m_dScaleFactorX[nCam];
				pData->m_nRealDefectInfo[pData->m_nLineThCount][3]= pData->m_dSizeY[0][pData->m_nLineThCount] = dy1*pData->m_nLineReduce* pData->m_dScaleFactorX[nCam];
				pData->m_nRealDefectInfo[pData->m_nLineThCount][4]= pData->m_dSize[0][pData->m_nLineThCount] = dy1*pData->m_nLineReduce* pData->m_dScaleFactorX[nCam];

				//꼽침 구분
				//압축된 영상을 이진화 하여 영상의 Hight 길이의 불량이 있을경우 
					//꼽침
				pData->m_nDefectType[nCam][pData->m_nLineThCount] = DCLASS_GSR_LIMUL;
				pData->m_bResult[nCam][pData->m_nLineThCount] = FALSE;

				pData->m_nLineThCount++;

			}
		}
		if(pData->m_nLineThCount>0){
			pData->m_nLineSumCount++;
			delete fmLine1;
			return ntmp1/nc;
		}
		else
			pData->m_nLineSumCount=0;

		delete fmLine1;
	}

	return ntmp1/nc;
}

int CInspect::GetSplitImgData(CImage* pImage, CData* pData,int nCam,int nIdx,int nMod)//Edge detect, AverageBrightness, FullImageProfileData[x], ROI Set
{
	unsigned char* fm = pImage->GetImagePtr();
	int nCount = 10;
	int nw = pImage->GetWidth();
	int nh = pImage->GetHeight();
	int nstt = 0;
	int nend = nh;
	if( nIdx==0)
		nstt=0,nend = nh/nMod;
	else 
		nstt = (nh/nMod)*(nIdx),nend=(nh/nMod)*(nIdx+1); 

	nIdx = nh/nMod;
	if(nIdx<0)nIdx = 0;
	if(nw<1)return 0;
	int *nWidth1 = new int[nw];
	int ntmp = 0;
	memset(nWidth1,0,nw);
	for(int y=nstt;y<nend;y++)
	{
		for(int x=0;x<nw;x++){
			ntmp = *(fm+y*nw+x);
			nWidth1[x]+= ntmp;//*(fm+y*nw+x);
		}
	}
	for(int x=0;x<nw;x++)
		nWidth1[x]/=nIdx;
	delete nWidth1;
	return 0;
}

int CInspect::GetSplitInspect1(CImage* pImage, CData* pData,int nCam,int nIdx,int nMod)//Edge detect, AverageBrightness, FullImageProfileData[x], ROI Set
{
	unsigned char* fm = pImage->GetImagePtr();
	int nCount = 10;
	int nw = pImage->GetWidth();
	int nh = pImage->GetHeight();
	int nstt = 0;
	int nend = nh;
	if( nIdx==0)
		nstt=0,nend = nh/nMod;
	else 
		nstt = (nh/nMod)*(nIdx),nend=(nh/nMod)*(nIdx+1); 

	if(nIdx<0)nIdx = 0;
	int nindex = nIdx;
	int nh1 = nh/nMod;
	if(nh1<0 || nw<1)return 0;
	if(nend-nstt==0)return 0;
		
	int *nWidth1,ntmp = 0;
	nWidth1=(int*)malloc(nw*sizeof(int));
	for(int i=0;i<nw;i++) nWidth1[i]=0;

	for(int y=nstt;y<nend;y++)
	{
		for(int x=0;x<nw;x++){
			ntmp = *(fm+y*nw+x);
			nWidth1[x]+= ntmp;//*(fm+y*nw+x);
		}
	}
	for(int x=0;x<nw;x++)
		nWidth1[x]/=(nend-nstt);

	CPoint ptCandidate[MAX_DEFECT];
	int nx1[MAX_DEFECT],ny1[MAX_DEFECT],nx2[MAX_DEFECT],ny2[MAX_DEFECT],nColor[MAX_DEFECT];
	for(int i=0;i<MAX_DEFECT;i++){
		ptCandidate[i].SetPoint(0,0);
		nx1[i]=ny1[i]=nx2[i]=ny2[i]=0;
		nColor[i] = 0;
	}
	//defect condidate
	int nDefectCount = 0;
	int nbadx = BAD_IMG_WIDTH*0.5;
	int nbady = BAD_IMG_HEIGHT*0.5;
	BOOL bJump = FALSE,nskipx = 0;
	int nthup = pData->m_dThUp[0];
	int nthdn = pData->m_dThDn[0];
	for(int y=nstt;y<nend;y++)
	{
		for(int x=0;x<nw;x++){
			if(nDefectCount >= MAX_DEFECT-1) goto done;
			bJump = FALSE;
			ntmp = *(fm+y*nw+x);
			if(nWidth1[x]-ntmp >= nthup){
				for(int i=0;i<nDefectCount && bJump==FALSE;i++){
					if(x>=nx1[i] && x<nx2[i] && y >= ny1[i] && y<ny2[i]){
						x = nx2[i];
						bJump = TRUE;
					}
				}
				if(bJump)continue;
			//우선 후보로만 뽑는다.
				ptCandidate[nDefectCount].SetPoint(x,nh-y);
				pData->AddDefectPoint(ptCandidate[nDefectCount],CPoint(x,y),nindex);
				SetBoundary(CRect(x-nbadx,y-nbady,x+nbadx,y+nbady),nw,nstt,nend,&nx1[nDefectCount],&ny1[nDefectCount],&nx2[nDefectCount],&ny2[nDefectCount]);			
				nColor[nDefectCount] = 255;
				nDefectCount++;
			//가장 강한 값을 뽑는다.
			}
			if(nWidth1[x]-ntmp<=-nthdn)
			{
				for(int i=0;i<nDefectCount && bJump==FALSE;i++){
					if(x>=nx1[i] && x<nx2[i] && y >= ny1[i] && y<ny2[i]){
						x = nx2[i];
						bJump = TRUE;
					}
				}
				if(bJump)continue;
				//우선 후보로만 뽑는다.
				ptCandidate[nDefectCount].SetPoint(x,nh-y);
				pData->AddDefectPoint(ptCandidate[nDefectCount],CPoint(x,y),nindex);
				SetBoundary(CRect(x-nbadx,y-nbady,x+nbadx,y+nbady),nw,nstt,nend,&nx1[nDefectCount],&ny1[nDefectCount],&nx2[nDefectCount],&ny2[nDefectCount]);			
				nColor[nDefectCount] = 0;
				nDefectCount++;
			}
		}
	}
done:
	//원래 RT 리턴

	if(nWidth1) free(nWidth1);
	return 0;
}
CRect CInspect::SetBoundary(CRect rt,int nwidth,int nh1,int nh2,int *nx1,int *ny1,int* nx2,int * ny2)
{	if(rt.left	< 0)			rt.OffsetRect(-rt.left, 0);
	if(rt.top	< nh1)			rt.OffsetRect(0, nh1-rt.top);
	if(rt.right	>= nwidth)		rt.OffsetRect(nwidth-rt.right, 0);
	if(rt.bottom >= nh2)	rt.OffsetRect(0, nh2-rt.bottom);
	*nx1 = rt.left;
	*ny1 = rt.top;
	*nx2 = rt.right;
	*ny2 = rt.bottom;
	return rt;
}



int CInspect::GetSplitInspect2(CImage* pImage, CData* pData,int nCam,int nIdx,int nMod)//Edge detect, AverageBrightness, FullImageProfileData[x], ROI Set
{
	unsigned char* fm = pImage->GetImagePtr();
	int nCount = 10;
	int nw = pImage->GetWidth();
	int nh = pImage->GetHeight();
	int nstt = 0;
	int nend = nh;
	if( nIdx==0)
		nstt=0,nend = nh/nMod;
	else 
		nstt = (nh/nMod)*(nIdx),nend=(nh/nMod)*(nIdx+1); 

	int x1 = pData->m_rectIns[0].left,x2= pData->m_rectIns[0].right;//검사영역

	int nindex = nIdx;
	int nh1 = nh/nMod;

	int *nWidth1,*nWidth2,*nWidth3,ntmp = 0;
	nWidth1=(int*)malloc(nw*sizeof(int));
	nWidth2=(int*)malloc(nw*sizeof(int));
	nWidth3=(int*)malloc(nw*sizeof(int));
	for(int i=0;i<nw;i++) nWidth1[i]=nWidth2[i]=nWidth3[i]=0;

	for(int y=nstt;y<nend;y++)
	{
		for(int x=0;x<nw;x++){
			ntmp = *(fm+y*nw+x);
			nWidth1[x]+= ntmp;//*(fm+y*nw+x);
		}
	}
	for(int x=0;x<nw;x++)
		nWidth1[x]/=(nend-nstt);
	for(int x=x1+20;x<x2-20;x++){
		nWidth2[x] = abs(nWidth1[x] - nWidth1[x+8]);
		nWidth3[x] = nWidth1[x] - nWidth1[x+8];
	}

	CPoint ptCandidate[MAX_DEFECT];
	int nx1[MAX_DEFECT],ny1[MAX_DEFECT],nx2[MAX_DEFECT],ny2[MAX_DEFECT],nColor[MAX_DEFECT];
	for(int i=0;i<MAX_DEFECT;i++){
		ptCandidate[i].SetPoint(0,0);
		nx1[i]=ny1[i]=nx2[i]=ny2[i]=0;
		nColor[i] = 0;
	}
	//defect candidate
	int nDefectCount = 0,nmin=255,nmax=0,nmin1=255,nmax1=0;
	int nbadx = BAD_IMG_WIDTH*0.5;
	int nbady = BAD_IMG_HEIGHT*0.5;
	BOOL bJump = FALSE,nskipx = 0;
	int nthup = pData->m_dThUp[0];
	int nthdn = pData->m_dThDn[0];

//	if(pData->m_bUse2Level[0] && pData->m_strMachineName.Find("CT")>=0)
	{
		//흑점만 본다. 백에는 구분이 많아 어떤 방향으로 갈지 ???
		nthdn = pData->m_dWeakThDn[0];
		nthup = pData->m_dWeakThUp[0];
	}
	int nLineV = pData->m_nCycleUse[0];
	for(int y=nstt;y<nend;y++)
	{
		for(int x=x1;x<x2;x++){
			if(nDefectCount >= MAX_DEFECT-1) goto done;
			bJump = FALSE;
			ntmp = *(fm+y*nw+x);
			if(nmax<ntmp-pData->m_nProjectX[0][x])
				nmax = ntmp-pData->m_nProjectX[0][x];
			if(nmin>ntmp-pData->m_nProjectX[0][x])
				nmin = ntmp-pData->m_nProjectX[0][x];

			if(nmax1<nWidth2[x])nmax1 = nWidth2[x];
			if(nmin1>nWidth2[x])nmin1 = nWidth2[x];

			if(nWidth2[x]>2 && nWidth2[x]>nLineV && nLineV >0){//꼽침 라인
				ptCandidate[nDefectCount].SetPoint(x,y);
				pData->AddDefectPoint(ptCandidate[nDefectCount],CPoint(x,y),nindex);
				pData->m_rtCandidate[nindex][nDefectCount]=	SetBoundary(CRect(x-nbadx,y-nbady,x+nbadx,y+nbady),nw,nstt,nend,&nx1[nDefectCount],&ny1[nDefectCount],&nx2[nDefectCount],&ny2[nDefectCount]);			
				nColor[nDefectCount] = 0;
				//백 흑을 찾아볼까?

				pData->m_nCandidateType[nindex][nDefectCount]= DCLASS_GBR_SCRATCH;
				pData->m_nCandidateScValue[nindex][nDefectCount] = nWidth2[x];
				nDefectCount++;
				x+=128;

			}
			else if(ntmp-pData->m_nProjectX[0][x] >= nthup){
				for(int i=0;i<nDefectCount && bJump==FALSE;i++){
					if(x>=nx1[i] && x<nx2[i] )
						if( y >= ny1[i] && y<ny2[i]){
							x = nx2[i];
							bJump = TRUE;
					}
				}
				if(bJump)continue;
			//우선 후보로만 뽑는다.
				ptCandidate[nDefectCount].SetPoint(x,y);
				pData->AddDefectPoint(ptCandidate[nDefectCount],CPoint(x,y),nindex);
				pData->m_rtCandidate[nindex][nDefectCount]=	SetBoundary(CRect(x-nbadx,y-nbady,x+nbadx,y+nbady),nw,nstt,nend,&nx1[nDefectCount],&ny1[nDefectCount],&nx2[nDefectCount],&ny2[nDefectCount]);			
				nColor[nDefectCount] = 255;
				nDefectCount++;
				x+=128;
			}
			else if(ntmp-pData->m_nProjectX[0][x]<=-nthdn)
			{
				for(int i=0;i<nDefectCount && bJump==FALSE;i++){
					if(x>=nx1[i] && x<nx2[i] && y >= ny1[i] && y<ny2[i]){
						x = nx2[i];
						bJump = TRUE;
					}
				}
				if(bJump)continue;
				//우선 후보로만 뽑는다.
				ptCandidate[nDefectCount].SetPoint(x,y);
				pData->AddDefectPoint(ptCandidate[nDefectCount],CPoint(x,y),nindex);
				pData->m_rtCandidate[nindex][nDefectCount]=	SetBoundary(CRect(x-nbadx,y-nbady,x+nbadx,y+nbady),nw,nstt,nend,&nx1[nDefectCount],&ny1[nDefectCount],&nx2[nDefectCount],&ny2[nDefectCount]);			
				nColor[nDefectCount] = 0;
				nDefectCount++;
				x+=128;
			}
			
		
		}
	}
done:
	pData->m_nMaxImageValue[0][nIdx]=nmax;//
	pData->m_nMinImageValue[0][nIdx]=nmin;//
	
	pData->m_nMaxImageLine[0][nindex] = nmax1;
	if(nWidth1) free(nWidth1);
	if(nWidth2) free(nWidth2);
	if(nWidth3) free(nWidth3);

	return 0;
}

void CInspect::GetDataSort(CImage* pImage, CData* pData,int nCam)
{
	//Condidate Peak Brightness Check //4x4 mesh 단위 불량 선별
	int nsplit = pData->m_nUseIndex;
	int nw = pData->m_nCameraWidth;
	int nh = pData->m_nCameraHeight;
	int nmeshCount = 4,nMeshFull = 16;
	int	nDefectInfo[16][10];//mesh별 최대값 //0max 1min 2sizex 3sizey 4size 5color 6type 7posx 8posy
	CPoint ptMeshTrans[16][10];
	CRect	rtMeshTrans[16][10];
	CRect	rtMeshTrans1[16][10];
	int nposcount[16],ntmp;//mesh position
	int nxsplit[4+1];//top bottom left right를 포함하기 위해
	int nxmod = nw/nmeshCount;
	int nbadx = BAD_IMG_WIDTH*0.5;
	int nbady = BAD_IMG_HEIGHT*0.5;
	int nx1[MAX_DEFECT],ny1[MAX_DEFECT],nx2[MAX_DEFECT],ny2[MAX_DEFECT],nColor[MAX_DEFECT];
	BOOL	bScFind = FALSE,bScFind1 = FALSE;
	int nMeshDefectType[16][10],nMeshSCValue[16][10];
	for(int i=0;i<16;i++)nposcount[i] = 0;
	for(int i=0;i<4+1;i++)nxsplit[i] = i*nxmod;
	for(int i=0;i<16;i++)for(int j=0;j<10;j++){nDefectInfo[i][j] = -1;ptMeshTrans[i][j].SetPoint(0,0);rtMeshTrans[i][j].SetRect(0,0,0,0);rtMeshTrans1[i][j].SetRect(0,0,0,0);nMeshDefectType[i][j]=nMeshSCValue[i][j]=0;}
	//mesh에 후보 포지션 넣기
	for(int i=0;i<nsplit;i++)
	{
		ntmp = 0;
		for(int j = 0;j<pData->m_nCandidatePointCount[i];j++)
		{
			if(nposcount[ntmp]>=10 || j>=MAX_DEFECT) continue;
			int nmod = pData->m_ptCandidate[i][j].x/nxmod;
			ntmp = (nmeshCount*i)+nmod;//index
			ptMeshTrans[ntmp][nposcount[ntmp]] = pData->m_ptCandidate[i][j];
			//Defect Point 기준으로 영역을 다시 설정한다.//chcho
			pData->m_rtCandidate[i][j]=	SetBoundary(CRect(pData->m_ptCandidate[i][j].x-nbadx,pData->m_ptCandidate[i][j].y-nbady,pData->m_ptCandidate[i][j].x+nbadx,pData->m_ptCandidate[i][j].y+nbady),
				nw,0,nh,&nx1[j],&ny1[j],&nx2[j],&ny2[j]);	
			rtMeshTrans1[ntmp][nposcount[ntmp]]=	SetBoundary(CRect(pData->m_ptCandidate[i][j].x-BAD_IMG_WIDTH,pData->m_ptCandidate[i][j].y-BAD_IMG_HEIGHT,pData->m_ptCandidate[i][j].x+BAD_IMG_WIDTH,pData->m_ptCandidate[i][j].y+BAD_IMG_HEIGHT),
				nw,0,nh,&nx1[j],&ny1[j],&nx2[j],&ny2[j]);		

			rtMeshTrans[ntmp][nposcount[ntmp]] = pData->m_rtCandidate[i][j];
			nMeshDefectType[ntmp][nposcount[ntmp]] = pData->m_nCandidateType[i][j];//pData->m_dTempData3[nCam][nDefectCount] = DCLASS_GBR_SCRATCH;
			nMeshSCValue[ntmp][nposcount[ntmp]] = pData->m_nCandidateScValue[i][j];
			nposcount[ntmp]++;
		}
	}
	//전체 영상을 기준으로 작업//pData->m_nCandidateScValue[nindex][nDefectCount]
//Data find
	CRect rt;
	BYTE * fm = pImage->GetImagePtr();
	BOOL bColor[10],bping = FALSE;//False=white true=black
	int nMax = 0,nMin=0,nMax1 = 0,nMin1=0,nIndex = 0,npeak=0;
	int nMeshDefect = 0;
	int nVisionLine = pData->m_nVisionLine;
	//4x4 mesh별 가장 강한 불량 1ea씩 검출
	pData->m_dAveRealBright[nCam] ;
	int nBright1 = 60;
	int nBright2 = 80;//pData->m_nDefaultCycle[nCam][14];//85
//m_nCommityTh
	int nCandiCount1 = 0;//후보개수
	if(g_frame_num>1 && nVisionLine == GL4 && pData->m_dAveRealBright[nCam] > pData->m_nCommityTh[nCam]){//nBright2){// && g_frame_num%11 == atoi(pData->m_strComName.Right(2))){
		//미코팅 //11 번 마다 불량
		pData->m_bNotCoating[nCam][g_frame_num%MAX_COMMUTYFRAME] = TRUE;
//		pData->m_nDefectType[nCam][pData->m_nRealDefectCount] = DCLASS_GSR_NOTCOATING;
//		pData->m_nRealDefectCount++;
	}//
	else 
		pData->m_bNotCoating[nCam][g_frame_num%MAX_COMMUTYFRAME] = FALSE;
	//10장에 대한 미코팅 체크
	if(g_frame_num>1 && pData->m_bNotCoating[nCam][g_frame_num%MAX_COMMUTYFRAME]){
		int ntmp12 = 0;
		for(int i=0;i<MAX_COMMUTYFRAME;i++){
			if(pData->m_bNotCoating[nCam][i])
				ntmp12++;
		}
		if(ntmp12>=3){
			if(pData->m_nRealDefectCount == 0){
				//pData->m_nRealDefectCount = 1;
			}
			pData->m_nDefectType[nCam][0] = DCLASS_GSR_NOTCOATING;
			pData->m_bResult[nCam][0] = FALSE;

			//pData->m_nDefectType[nCam][pData->m_nRealDefectCount] = DCLASS_GSR_NOTCOATING;
			//pData->m_bResult[nCam][pData->m_nRealDefectCount] = FALSE;
			pData->m_nRealDefectCount++;
			for(int i=0;i<MAX_COMMUTYFRAME;i++){
				pData->m_bNotCoating[nCam][i] = FALSE;
			}
			return;
		}
	}
// 	for(int i=0;i<nMeshFull;i++){
// 		for(int j=0;j<10;j++)bColor[j] = FALSE;
// 		nMax1=nMin1=nIndex=npeak=nMax=0;
// 		bScFind = FALSE;
// 		bScFind1 = FALSE;
// 		nCandiCount1++;
// 		for(int j=0;j<nposcount[i];j++){
// 			if(j>= MAX_DEFECT)continue;
// 			// sc가 있는 경우  최고 우선순위를 둔다.
// 			if(nVisionLine == GL4 && (nMeshDefectType[i][j] == DCLASS_GSR_SCRATCH ||nMeshDefectType[i][j] == DCLASS_GSR_LOW_SCRATCH ||nMeshDefectType[i][j] == DCLASS_GSR_LIMUL )){
// 				bScFind = TRUE;
// 				nIndex = j;
// 				nMeshDefect = nMeshDefectType[i][j];
// 				break;//
// 			}
// 			if(nVisionLine==GL3 &&  nMeshDefectType[i][j] == DCLASS_GBR_SCRATCH){
// 				bScFind1 = TRUE;
// 				nIndex = j;
// 				nMeshDefect = nMeshDefectType[i][j];
// 				break;//
// 			}
// 			if(rtMeshTrans[i][j].Width() ==0)break;
// 			//영상에서 min max 찾기
// 			bColor[j]=GetPeakValue(fm,pData,nCam,rtMeshTrans[i][j],&nMax1,&nMin1);
// 
// 			if(pData->m_nVisionLine==GL4 &&nMeshDefectType[i][j] ==DCLASS_GSR_SURFACE_DEFECT){
// 				nMeshDefect = DCLASS_GSR_SURFACE_DEFECT;
// 				npeak = nMin1;
// 			}
// 			else{
// 				if(nMax1>=abs(nMin1) )npeak = nMax1;
// 				else				npeak = nMin1;
// 			}
// 			if(abs(npeak)>nMax){nMax = abs(npeak);nIndex = j;}
// 		}
// 		if(bScFind){//sc일때
// 			if(nMeshSCValue[i][nIndex]>0){
// 				pData->m_nDefectVMax[nCam][pData->m_nRealDefectCount]=pData->m_nRealDefectInfo[pData->m_nRealDefectCount][0]=nDefectInfo[i][0] = nMeshSCValue[i][nIndex];
// 				pData->m_nDefectVMin[nCam][pData->m_nRealDefectCount]=pData->m_nRealDefectInfo[pData->m_nRealDefectCount][1]=nDefectInfo[i][1] = 0;
// 				bColor[nIndex] = TRUE;
// 			}
// 			else if(nMeshSCValue[i][nIndex]<0){
// 				pData->m_nDefectVMax[nCam][pData->m_nRealDefectCount]=pData->m_nRealDefectInfo[pData->m_nRealDefectCount][0]=nDefectInfo[i][0] = 0;
// 				pData->m_nDefectVMin[nCam][pData->m_nRealDefectCount]=pData->m_nRealDefectInfo[pData->m_nRealDefectCount][1]=nDefectInfo[i][1] = nMeshSCValue[i][nIndex];
// 				bColor[nIndex] = FALSE;
// 			}
// 			//image copy
// 
// 			int nLinecount = 768;
// 
// 			pData->m_bDefectWhite[nCam][pData->m_nRealDefectCount] = pData->m_nRealDefectInfo[pData->m_nRealDefectCount][5]=nDefectInfo[i][5] = bColor[nIndex];
// 			pData->m_ptDefect[nCam][pData->m_nRealDefectCount].x= pData->m_nRealDefectInfo[pData->m_nRealDefectCount][7]=nDefectInfo[i][7] = ptMeshTrans[i][nIndex].x;
// 			pData->m_ptDefect[nCam][pData->m_nRealDefectCount].y= pData->m_nRealDefectInfo[pData->m_nRealDefectCount][8]=nDefectInfo[i][8] = ptMeshTrans[i][nIndex].y;
// 			pData->m_rectDefect[0][pData->m_nRealDefectCount] = rtMeshTrans[i][nIndex];
// 			BYTE * fmdefect = pData->m_pImageDefect[0][pData->m_nRealDefectCount]->GetImagePtr();//new BYTE[BAD_IMG_WIDTH*BAD_IMG_HEIGHT];
// 
// 			CRect rtsc,rtsc1;
// 			rtsc.SetRect(ptMeshTrans[i][nIndex].x-nbadx,((ptMeshTrans[i][nIndex].y)/nLinecount)*nLinecount,ptMeshTrans[i][nIndex].x+nbadx,((ptMeshTrans[i][nIndex].y)/nLinecount)*nLinecount+nLinecount);
// 			pData->m_rectDefect[0][pData->m_nRealDefectCount] = rtsc1 = rtsc;
// 			rtsc1.bottom = nh-rtsc.top;
// 			rtsc1.top = nh-rtsc.bottom;
// 			ImageSelectCopyScratch(fm,fmdefect,pData->m_nCameraWidth,pData->m_nCameraHeight,rtsc1,BAD_IMG_WIDTH,BAD_IMG_HEIGHT,0,0,nLinecount/128);
// 
// 			//꼽침 구분
// 			//압축된 영상을 이진화 하여 영상의 Hight 길이의 불량이 있을경우 
// 			GetLineWidthCheck(nCam,fmdefect,pData,rtsc1,pData->m_nRealDefectCount,1);
// 
// 			pData->m_nRealDefectInfo[pData->m_nRealDefectCount][2]=nDefectInfo[i][2] = pData->m_dSizeX[0][pData->m_nRealDefectCount];//=2;
// 			pData->m_nRealDefectInfo[pData->m_nRealDefectCount][3]=nDefectInfo[i][3] = pData->m_dSizeY[0][pData->m_nRealDefectCount];//=2;
// 			pData->m_nRealDefectInfo[pData->m_nRealDefectCount][4]=nDefectInfo[i][4] = pData->m_dSize[0][pData->m_nRealDefectCount]=pData->m_dSizeY[0][pData->m_nRealDefectCount];//2;
// 			//꼽침을 먼저 구분한다.
// 			if(pData->m_dTempData1[nCam][pData->m_nRealDefectCount]>3500 && pData->m_dTempData2[nCam][pData->m_nRealDefectCount]>350 && pData->m_dSizeY[0][pData->m_nRealDefectCount]>1.5 && pData->m_nBlobCount[nCam][nIndex] <8){
// 				//꼽침
// 				pData->m_nDefectType[nCam][pData->m_nRealDefectCount] = DCLASS_GSR_LIMUL;
// 			}
// 			else if(nMeshDefect == DCLASS_GSR_LIMUL)
// 				pData->m_nDefectType[nCam][pData->m_nRealDefectCount] = DCLASS_GSR_LOW_LIMUL;
// 			else{
// 				if(pData->m_nDefectVMax[nCam][pData->m_nRealDefectCount] > pData->m_dThDn[nCam])
// 					pData->m_nDefectType[nCam][pData->m_nRealDefectCount] = DCLASS_GSR_SCRATCH;
// 				else
// 					pData->m_nDefectType[nCam][pData->m_nRealDefectCount] = DCLASS_GSR_LOW_SCRATCH;
// 			}
// 			pData->m_nRealDefectCount++;
// 		}
// 		else if(bScFind1){//gl3 꼽침
// 
// 			npeak = nMeshSCValue[i][nIndex];
// 			pData->m_nDefectType[nCam][pData->m_nRealDefectCount] = DCLASS_GBR_SCRATCH;
// 			//if(bColor[nIndex])
// 			{//white
// 				pData->m_nDefectVMax[nCam][pData->m_nRealDefectCount]=pData->m_nRealDefectInfo[pData->m_nRealDefectCount][0]=nDefectInfo[i][0] = npeak;
// 				pData->m_nDefectVMin[nCam][pData->m_nRealDefectCount]=pData->m_nRealDefectInfo[pData->m_nRealDefectCount][1]=nDefectInfo[i][1] = 0;
// 			}
// 			pData->m_bDefectWhite[nCam][pData->m_nRealDefectCount] = pData->m_nRealDefectInfo[pData->m_nRealDefectCount][5]=nDefectInfo[i][5] = TRUE;//bColor[nIndex];
// 			pData->m_ptDefect[nCam][pData->m_nRealDefectCount].x= pData->m_nRealDefectInfo[pData->m_nRealDefectCount][7]=nDefectInfo[i][7] = ptMeshTrans[i][nIndex].x;
// 			//영상 뒤집힘.
// 			pData->m_ptDefect[nCam][pData->m_nRealDefectCount].y= pData->m_nRealDefectInfo[pData->m_nRealDefectCount][8]=nDefectInfo[i][8] = nh-ptMeshTrans[i][nIndex].y;
// 			//원본과 영상이 뒤집힘. // 2대 압축
// 			pData->m_rectDefect[0][pData->m_nRealDefectCount] = rtMeshTrans[i][nIndex];
// 			pData->m_rectDefect[0][pData->m_nRealDefectCount].top = nh -rtMeshTrans[i][nIndex].bottom;
// 			pData->m_rectDefect[0][pData->m_nRealDefectCount].bottom = nh -rtMeshTrans[i][nIndex].top;
// 
// 		/////////////////////////////////////////////////////////////
// 			BYTE * fmdefect = pData->m_pImageDefect[0][pData->m_nRealDefectCount]->GetImagePtr();//new BYTE[BAD_IMG_WIDTH*BAD_IMG_HEIGHT];
// 			CRect rtsc,rtsc1;
// 			int nLinecount = 768;
// //			if(pData->m_nMachine==0)nLinecount=512;
// 			if(nh<2200)
// 				nLinecount=512;
// 			rtsc.SetRect(ptMeshTrans[i][nIndex].x-nbadx,((nh-ptMeshTrans[i][nIndex].y)/nLinecount)*nLinecount,ptMeshTrans[i][nIndex].x+nbadx,((nh-ptMeshTrans[i][nIndex].y)/nLinecount)*nLinecount+nLinecount);
// 			rtsc.SetRect(ptMeshTrans[i][nIndex].x-nbadx,((nh-ptMeshTrans[i][nIndex].y)/nLinecount)*nLinecount-nLinecount,ptMeshTrans[i][nIndex].x+nbadx,((nh-ptMeshTrans[i][nIndex].y)/nLinecount)*nLinecount);
// 			pData->m_rectDefect[0][pData->m_nRealDefectCount] = rtsc1 = rtsc;
// 			rtsc1.bottom = nh-rtsc.top;
// 			rtsc1.top = nh-rtsc.bottom;
// 			ImageSelectCopyScratch(fm,fmdefect,pData->m_nCameraWidth,pData->m_nCameraHeight,rtsc1,BAD_IMG_WIDTH,BAD_IMG_HEIGHT,0,0,nLinecount/128);
// //			GetNewDefectSize(0,fm,pData,rtMeshTrans[i][nIndex],pData->m_nRealDefectCount,bColor[nIndex]);
// 			pData->m_nRealDefectInfo[pData->m_nRealDefectCount][2]=nDefectInfo[i][2] = pData->m_dSizeX[0][pData->m_nRealDefectCount]=2;
// 			pData->m_nRealDefectInfo[pData->m_nRealDefectCount][3]=nDefectInfo[i][3] = pData->m_dSizeY[0][pData->m_nRealDefectCount]=2;
// 			pData->m_nRealDefectInfo[pData->m_nRealDefectCount][4]=nDefectInfo[i][4] = pData->m_dSize[0][pData->m_nRealDefectCount]=2;
// 			GetDefectType(pData,nCam,pData->m_nRealDefectCount);//2level일때 어떻해야 하나?
// 			pData->m_nRealDefectCount++;
// 		}
// 		else if(nposcount[i]>0){
// 			////mesh별 최대값 //0max 1min 2sizex 3sizey 4size 5color 6type 7posx 8posy
// 			if(pData->m_nVisionLine==GL4 && nMeshDefect==DCLASS_GSR_SURFACE_DEFECT){
// 				bColor[nIndex] = FALSE;
// 				pData->m_nDefectVMax[nCam][pData->m_nRealDefectCount]=pData->m_nRealDefectInfo[pData->m_nRealDefectCount][0]=nDefectInfo[i][0] = 0;
// 				pData->m_nDefectVMin[nCam][pData->m_nRealDefectCount]=pData->m_nRealDefectInfo[pData->m_nRealDefectCount][1]=nDefectInfo[i][1] = nMax;
// 
// 			}
// 			else{
// 				if(bColor[nIndex]){//white
// 					pData->m_nDefectVMax[nCam][pData->m_nRealDefectCount]=pData->m_nRealDefectInfo[pData->m_nRealDefectCount][0]=nDefectInfo[i][0] = nMax;
// 					pData->m_nDefectVMin[nCam][pData->m_nRealDefectCount]=pData->m_nRealDefectInfo[pData->m_nRealDefectCount][1]=nDefectInfo[i][1] = 0;
// 				}
// 				else{//m_nDefectVMax
// 					pData->m_nDefectVMax[nCam][pData->m_nRealDefectCount]=pData->m_nRealDefectInfo[pData->m_nRealDefectCount][0]=nDefectInfo[i][0] = 0;
// 					pData->m_nDefectVMin[nCam][pData->m_nRealDefectCount]=pData->m_nRealDefectInfo[pData->m_nRealDefectCount][1]=nDefectInfo[i][1] = -nMax;
// 				}	
// 			}
// 			pData->m_bDefectWhite[nCam][pData->m_nRealDefectCount] = pData->m_nRealDefectInfo[pData->m_nRealDefectCount][5]=nDefectInfo[i][5] = bColor[nIndex];
// 			pData->m_ptDefect[nCam][pData->m_nRealDefectCount].x= pData->m_nRealDefectInfo[pData->m_nRealDefectCount][7]=nDefectInfo[i][7] = ptMeshTrans[i][nIndex].x;
// 			//영상 뒤집힘.
// 			pData->m_ptDefect[nCam][pData->m_nRealDefectCount].y= pData->m_nRealDefectInfo[pData->m_nRealDefectCount][8]=nDefectInfo[i][8] = nh-ptMeshTrans[i][nIndex].y;
// 			//원본과 영상이 뒤집힘. // 2대 압축
// 			if(pData->m_nVisionLine==GL4){
// 				pData->m_rectDefect[0][pData->m_nRealDefectCount] = rtMeshTrans1[i][nIndex];
// 				pData->m_rectDefect[0][pData->m_nRealDefectCount].top = nh -rtMeshTrans1[i][nIndex].bottom;
// 				pData->m_rectDefect[0][pData->m_nRealDefectCount].bottom = nh -rtMeshTrans1[i][nIndex].top;
// 				GetNewDefectSize(0,fm,pData,rtMeshTrans1[i][nIndex],pData->m_nRealDefectCount,bColor[nIndex]);
// 			}
// 			else if(pData->m_nVisionLine==GL3){
// 				pData->m_rectDefect[0][pData->m_nRealDefectCount] = rtMeshTrans[i][nIndex];
// 				pData->m_rectDefect[0][pData->m_nRealDefectCount].top = nh -rtMeshTrans[i][nIndex].bottom;
// 				pData->m_rectDefect[0][pData->m_nRealDefectCount].bottom = nh -rtMeshTrans[i][nIndex].top;
// 				GetNewDefectSize(0,fm,pData,rtMeshTrans[i][nIndex],pData->m_nRealDefectCount,bColor[nIndex]);
// 			}
// 			if(nMeshDefect != 0)
// 				pData->m_nDefectType[nCam][pData->m_nRealDefectCount] = nMeshDefect;
// 			pData->m_nRealDefectInfo[pData->m_nRealDefectCount][2]=nDefectInfo[i][2] = pData->m_dSizeX[0][pData->m_nRealDefectCount];
// 			pData->m_nRealDefectInfo[pData->m_nRealDefectCount][3]=nDefectInfo[i][3] = pData->m_dSizeY[0][pData->m_nRealDefectCount];
// 			pData->m_nRealDefectInfo[pData->m_nRealDefectCount][4]=nDefectInfo[i][4] = pData->m_dSize[0][pData->m_nRealDefectCount];
// 			GetDefectType(pData,nCam,pData->m_nRealDefectCount);//2level일때 어떻해야 하나?
// 			pData->m_nRealDefectCount++;
// 		}
// 	}

	return;
}

BOOL CInspect::GetPeakValue(BYTE* fm,CData *pData,int nCam,CRect rtinsp,int * nMax,int * nMin)
{
	int i,nTmp,nmax=0,nmin=0;
	int nw = pData->m_nCameraWidth;
	int nh = pData->m_nCameraHeight;
	if(rtinsp.left <0)rtinsp.left = 0;
	if(rtinsp.right >pData->m_nCameraWidth)rtinsp.right = pData->m_nCameraWidth-1;
	if(rtinsp.top <0)rtinsp.top = 0;
	if(rtinsp.bottom >pData->m_nCameraHeight)rtinsp.bottom = pData->m_nCameraHeight-1;

	for(int i=rtinsp.top;i<rtinsp.bottom;i++)
	{
		for(int j=rtinsp.left;j<rtinsp.right;j++)
		{
			nTmp = *(fm+i*nw+j) - pData->m_nProjectX[0][j];
			if(nTmp >= nmax)nmax = nTmp;
			else if(nTmp<=nmin)nmin = nTmp;

		}
	}
	*nMax = nmax;
	*nMin = nmin;
	if(nmax>=abs(nmin))return TRUE;//white
	return FALSE;//black
}

void CInspect::GetNewDefectSize(int nCam,BYTE* fmsrc,CData *pData,CRect rtDefect,int nIdx,BOOL bColor)
{
	
	int nIndex = nIdx;//pData->m_nRealDefectCount;
	BYTE * fmdefect = pData->m_pImageDefect[0][nIdx]->GetImagePtr();//new BYTE[BAD_IMG_WIDTH*BAD_IMG_HEIGHT];
//불량 이미지 후보 복사
	//
	if(pData->m_nVisionLine==GL4)
		ImageSelectCopy1(fmsrc,fmdefect,pData->m_nCameraWidth,pData->m_nCameraHeight,rtDefect,BAD_IMG_WIDTH,BAD_IMG_HEIGHT,0,0,2,bColor);
	else if(pData->m_nVisionLine==GL3)
		ImageSelectCopy(fmsrc,fmdefect,pData->m_nCameraWidth,pData->m_nCameraHeight,rtDefect,BAD_IMG_WIDTH,BAD_IMG_HEIGHT,0,0);

	unsigned char* fmtmp =	new BYTE[BAD_IMG_WIDTH*BAD_IMG_HEIGHT];
	memcpy(fmtmp,fmdefect,BAD_IMG_WIDTH*BAD_IMG_HEIGHT);
	unsigned char* fmtmp1 =	new BYTE[BAD_IMG_WIDTH*BAD_IMG_HEIGHT];//캐스터 블랙일 경우 물방울 체크
	memset(fmtmp1,0,BAD_IMG_WIDTH*BAD_IMG_HEIGHT);


	// stdev 를 위한 변수

	int nTotalCnt = 0;
	int nAve = 0;
	int nsum = 0,nsum1 = 0;
	double dstd = 0;

	int nTh = 0;
	int nTh1 = 220,nTh1Count=0;//막뜯김 찾기
	int nTh11 = pData->m_nCommityTh[nCam];//군집 휘점 220
	int nBWTh1 = 0, nBWTh2 = 10,nBWx1=0,nBWy1=0,nBWcnt1=0;//캐스터 블랙일 경우 물방울 체크
	if(bColor){//white
		for(int i=0;i<BAD_IMG_HEIGHT;i++){
			for(int j=0;j<BAD_IMG_WIDTH;j++){
				nTh = int(pData->m_nProjectX[nCam][pData->m_rectDefect[nCam][nIndex].left + i] + pData->m_nThWhiteValue[nCam]);
				if(*(fmdefect+i*BAD_IMG_WIDTH+j)>nTh)	*(fmtmp+i*BAD_IMG_WIDTH+j) = OBJECT;
				else									*(fmtmp+i*BAD_IMG_WIDTH+j) = BACKGROUND;
				if(*(fmdefect+i*BAD_IMG_WIDTH+j)>=nTh1){
					nTh1Count++;//막뜯김
				}
				if(*(fmdefect+i*BAD_IMG_WIDTH+j)>=nTh11){
					pData->m_dWhiteCommutySize[nCam][nIndex]++;//군집 휘점
				}
				nAve += *(fmdefect+i*BAD_IMG_WIDTH+j);
				nsum1 += *(fmdefect+i*BAD_IMG_WIDTH+j);
				nsum += *(fmdefect+i*BAD_IMG_WIDTH+j)**(fmdefect+i*BAD_IMG_WIDTH+j);
				nTotalCnt++;
			}
		}
		if(pData->m_nVisionLine==GL3)pData->m_dMaxWhiteSize[nCam][nIndex] = sqrt(double(nTh1Count))*pData->m_dScaleFactorX[nCam]*1.414;//막뜯김 사이즈용
	}
	else{//black
		for(int i=0;i<BAD_IMG_HEIGHT;i++){
			for(int j=0;j<BAD_IMG_WIDTH;j++){
				if(pData->m_nVisionLine==GL4){
					nTh = pData->m_nProjectX[0][rtDefect.left+j] - pData->m_nGl4BlackValue;//pData->m_dThDn[0];
					if(*(fmdefect+i*BAD_IMG_WIDTH+j)<nTh)	*(fmtmp+i*BAD_IMG_WIDTH+j) = OBJECT;
					else									*(fmtmp+i*BAD_IMG_WIDTH+j) = BACKGROUND;

				}
				else{
					nTh = pData->m_nProjectX[0][rtDefect.left+j] - pData->m_nThBlackValue[nCam];//pData->m_dThDn[0];
					if(*(fmdefect+i*BAD_IMG_WIDTH+j)<nTh)	*(fmtmp+i*BAD_IMG_WIDTH+j) = OBJECT;
					else									*(fmtmp+i*BAD_IMG_WIDTH+j) = BACKGROUND;

					if(pData->m_nMachine==0){
						nBWTh1 =  pData->m_nProjectX[0][rtDefect.left+j] + nBWTh2;//물방울 체크용
						if(*(fmdefect+i*BAD_IMG_WIDTH+j)>nBWTh1){
							nBWx1 += j;nBWy1+=i;nBWcnt1++;
							*(fmtmp1+i*BAD_IMG_WIDTH+j) = OBJECT;
						}
						else									*(fmtmp1+i*BAD_IMG_WIDTH+j) = BACKGROUND;

					}
				}
			}
		}
	}
	//memcpy(img.GetImagePtr(),fmtmp,BAD_IMG_WIDTH*BAD_IMG_HEIGHT);
	//img.Save("D:\\after.bmp");
//blob param
	double dTemp,dBlobSize;
	int  nBlobCount =-1, nBlobNo =0;
	CRect rtBlob;
//거리를 측정하기위한 param
	double dCx, dCy, dAngle, dPos[4][2], dShortLength, dLongLength,dMin,dMax,dAve;
	double dLengTemp,dLengTemp1,dLengTemp2,dPeriment;
	double dlongLine = 0.0;
//defect 개수가 1개로 저의 되어 있음. 수정 필요.
	dBlobSize = pData->m_dSize[nCam][nIndex]=  0.0;
	int nVisionLine = pData->m_nVisionLine;

	if(pData->m_nBlobUse[nCam] == 0)	//0 convex hull
	{
		for(int j=0; j<BAD_IMG_HEIGHT; j++){
			for(int i=0; i<BAD_IMG_WIDTH; i++){
				if(fmtmp[j*BAD_IMG_WIDTH+i]==OBJECT){
					if(i<pData->m_dDefectLeft[nCam][nIndex])	
						pData->m_dDefectLeft[nCam][nIndex]	= i;
					if(i>pData->m_dDefectRight[nCam][nIndex])	
						pData->m_dDefectRight[nCam][nIndex]	= i;
					if(j<pData->m_dDefectTop[nCam][nIndex])
						pData->m_dDefectTop[nCam][nIndex]		= j;
					if(j>pData->m_dDefectBottom[nCam][nIndex])
						pData->m_dDefectBottom[nCam][nIndex]	= j;
				}
			}
		}

		pData->m_dSizeX[nCam][nIndex] = (pData->m_dDefectRight[nCam][nIndex]-pData->m_dDefectLeft[nCam][nIndex]+1) * pData->m_dScaleFactorX[nCam]*pData->m_nRecude;
		pData->m_dSizeY[nCam][nIndex] = (pData->m_dDefectBottom[nCam][nIndex]-pData->m_dDefectTop[nCam][nIndex]+1) * pData->m_dScaleFactorY[nCam]*pData->m_nRecude;	
		if(pData->m_dSizeX[nCam][nIndex] >pData->m_dSizeY[nCam][nIndex])
			pData->m_dSize[nCam][nIndex] = pData->m_dSizeX[nCam][nIndex];
		else
			pData->m_dSize[nCam][nIndex] = pData->m_dSizeY[nCam][nIndex];
	}
	else// 
	{//	

//		FChain_SetChainData(1,fmtmp,1,0,0,100000,BAD_IMG_WIDTH,BAD_IMG_HEIGHT);
//		nBlobCount = FChain_FastChain(0, 0, BAD_IMG_WIDTH-1,BAD_IMG_HEIGHT-1);
		double dcompact = 0;
		
		double dth1 = pData->m_dCommutySize[0],dx1,dy1;
		int nCommunityCount = 0,nCommunityTh = pData->m_dCommutyCount[0],nCommunityCount1 = 0,nSkipCnt=0;

		for(int i=0;i<nBlobCount;i++)
		{
//			FChain_Area(i, &dTemp);//			dTemp = m_pChain->Chain_Area(i);ttt
			if(dTemp<2)continue;
			if(dTemp>=dBlobSize)//최대 불량 사이즈.
			{
				nBlobNo = i;
				dBlobSize = dTemp;//면적
				pData->m_nDefectThCount[nCam][nIndex] = dTemp;
			}
			if(pData->m_nVisionLine == GL4 && dTemp>0){//군집 check
//				dx1 = (FChain_FindMaxX(i) - FChain_FindMinX(i)) * pData->m_dScaleFactorX[nCam]*pData->m_nRecude;
//				dy1 = (FChain_FindMaxY(i) - FChain_FindMinY(i)) *pData->m_dScaleFactorY[nCam]*pData->m_nRecude;	
//				FChain_Center(i, &dCx, &dCy);
//				FChain_FindAngle(i, &dAngle);
//				FChain_FindCompactness(nBlobNo,&dcompact);


				if(dx1 >= dth1 && dy1 >= dth1){
					if( dcompact>0.3)
						nCommunityCount1++;
					else
						nCommunityCount++;
				}
				//170307	bh
				if(dx1>0.01 &&dx1<0.35 &&dy1>0.01 && dy1<0.35)
					nSkipCnt++;
			}
		}
		if(nBlobCount==0)
		{//Blob이 zero일 경우 ScaleScalefactor를 입력한다.
			pData->m_dSizeX[nCam][nIndex] =  pData->m_dScaleFactorX[nCam]*pData->m_nRecude;
			pData->m_dSizeY[nCam][nIndex] =  pData->m_dScaleFactorY[nCam]*pData->m_nRecude;	
			if(pData->m_dSizeX[nCam][nIndex] >pData->m_dSizeY[nCam][nIndex])
				pData->m_dSize[nCam][nIndex] = pData->m_dSizeX[nCam][nIndex];
			else
				pData->m_dSize[nCam][nIndex] = pData->m_dSizeY[nCam][nIndex];
		}
		else
		{
			pData->m_nBlobCount[nCam][nIndex] = nBlobCount;
			pData->m_dTempData3[nCam][nIndex] = dBlobSize;
			//장축 구하기.
//			FChain_Center(nBlobNo, &dCx, &dCy);
//			FChain_FindAngle(nBlobNo, &dAngle);
//			FChain_FindMinRect(nBlobNo, dCx, dCy, dAngle, dPos);  //Blob을 포함하는 최소 사각형 구하는 함수
//			FChain_FineDistFromPoint(nBlobNo, dCx,dCy, &dMin, &dMax, &dAve);
//			FChain_FindCompactness(nBlobNo,&dcompact);
//			FChain_Perimeter(nBlobNo,&dPeriment);
			pData->m_dStdevV[nCam][nIndex] = dcompact;
			pData->m_dDyespotAngle[nCam][nIndex] = dAngle;
			dShortLength=sqrt( (dPos[0][0]-dPos[1][0])*(dPos[0][0]-dPos[1][0])+(dPos[0][1]-dPos[1][1])*(dPos[0][1]-dPos[1][1])); 
			if(dShortLength<1 || dShortLength>1000) dShortLength=1;
			dLongLength=sqrt( (dPos[2][0]-dPos[1][0])*(dPos[2][0]-dPos[1][0])+(dPos[2][1]-dPos[1][1])*(dPos[2][1]-dPos[1][1]));
			if(dLongLength<1 || dLongLength>1000)  dLongLength=1;

			double dratio = 0;
			if(dShortLength < dLongLength)
				dratio = (double)(dLongLength / dShortLength);
			else
				dratio = (double)(dShortLength / dLongLength);
			pData->m_fDefectRatio[nCam][nIndex] =  dratio;

			pData->m_dTempData1[nCam][nIndex] = dMin;
			pData->m_dTempData2[nCam][nIndex] = dMax;
			pData->m_dTempData2[nCam][nIndex] = dAve;


			///stdev
			if(pData->m_nVisionLine==GL3 &&  bColor){
				pData->m_dStdevV[nCam][nIndex] = dcompact*100;

//				nAve /= nTotalCnt;
//				dstd = sqrt((nTotalCnt*nsum-nsum1*nsum1)/((double)nTotalCnt*((double)nTotalCnt-1)));
//	//			dstd = sqrt((nTotalCnt*nsum-nAve*nAve)/((double)nTotalCnt*(double)(nTotalCnt-1)));
//				pData->m_dTempData1[nCam][nIndex] = dstd;

			}

//			pData->m_dDefectLeft[nCam][nIndex]	= FChain_FindMinX(nBlobNo);
//			pData->m_dDefectRight[nCam][nIndex]	= FChain_FindMaxX(nBlobNo);
//			pData->m_dDefectTop[nCam][nIndex]		= FChain_FindMinY(nBlobNo);
//			pData->m_dDefectBottom[nCam][nIndex]	= FChain_FindMaxY(nBlobNo);

			pData->m_dSizeX[nCam][nIndex] = (pData->m_dDefectRight[nCam][nIndex]-pData->m_dDefectLeft[nCam][nIndex]+1) * pData->m_dScaleFactorX[nCam]*pData->m_nRecude;
			pData->m_dSizeY[nCam][nIndex] = (pData->m_dDefectBottom[nCam][nIndex]-pData->m_dDefectTop[nCam][nIndex]+1) * pData->m_dScaleFactorY[nCam]*pData->m_nRecude;	
			if(pData->m_dSizeX[nCam][nIndex] >pData->m_dSizeY[nCam][nIndex])
				pData->m_dSize[nCam][nIndex] = pData->m_dSizeX[nCam][nIndex];
			else
				pData->m_dSize[nCam][nIndex] = pData->m_dSizeY[nCam][nIndex];
			dLengTemp = (dMax*2) * pData->m_dScaleFactorX[nCam]*pData->m_nRecude;
			dLengTemp1 = (dMin*2) *pData->m_dScaleFactorX[nCam]*pData->m_nRecude;
			dLengTemp2 = sqrt(pData->m_dSizeX[nCam][nIndex]*pData->m_dSizeX[nCam][nIndex]+pData->m_dSizeY[nCam][nIndex] *pData->m_dSizeY[nCam][nIndex] );

//물방울 체크
			if(pData->m_nMachine==0 && bColor==FALSE) {
				pData->m_dDyespotAngle[nCam][nIndex] = nBWcnt1;

				if( nBWcnt1==0)
					nBWx1=nBWy1=0;
				else{
					nBWx1 /= nBWcnt1;nBWy1 /= nBWcnt1;
					//dx dy 비고
					if(abs(int(dCx)-nBWx1) > 10 ){

					}


				}
			}

			if(pData->m_nVisionLine == GL4 && nSkipCnt >=pData->m_nThBlackValue[nCam]){
				pData->m_nDefectType[nCam][nIndex] = DCLASS_GSR_SKIP;//skip	//170307	bh
			}	
			//Y 길이가 길고 
			if(nCommunityCount1 >=nCommunityTh && pData->m_nVisionLine == GL4 ){
				//DCLASS_GSR_NOTDRY
				pData->m_nDefectType[nCam][nIndex] = DCLASS_GSR_PIMUL;//군집비정형
			}
			else if(nCommunityCount >=nCommunityTh && pData->m_nVisionLine == GL4 ){
				pData->m_nDefectType[nCam][nIndex] = DCLASS_GSR_NOTDRY;//미건조
			}
			//if(nCommunityCount1 + nCommunityCount >=7 && pData->m_nVisionLine == GL4){
			//	pData->m_nDefectType[nCam][nIndex] = DCLASS_GSR_NOTDRY;//미건조
			//}

		}
	}


	if(pData->m_dSizeX[nCam][nIndex] < 0)	pData->m_dSizeX[nCam][nIndex] =pData->m_dScaleFactorX[nCam]*pData->m_nRecude;
	if(pData->m_dSizeY[nCam][nIndex] < 0)	pData->m_dSizeY[nCam][nIndex] =pData->m_dScaleFactorY[nCam]*pData->m_nRecude;
	if(pData->m_dSize[nCam][nIndex] < 0)	pData->m_dSize[nCam][nIndex] =pData->m_dScaleFactorX[nCam]*pData->m_nRecude;

	if(pData->m_bCrossBlobImg[0]){
		if(pData->m_nMachine==0 && bColor==FALSE )
			memcpy(fmdefect,fmtmp1,BAD_IMG_WIDTH*BAD_IMG_HEIGHT);
		else
			memcpy(fmdefect,fmtmp,BAD_IMG_WIDTH*BAD_IMG_HEIGHT);
	}

	delete fmtmp;
	delete fmtmp1;
}

//fmSrc 영상에서 fmDest영상으로 rtArea부분만큼만 복사한다.
void CInspect::ImageSelectCopy(unsigned char* fmSrc,unsigned char* fmDest,int nSrcW,int nSrcH,CRect rtArea,int nDestW,int nDestH,int nDestSttX,int nDestSttY)
{
	int x,y;
	CPoint ptOffset(0,0);
	if(rtArea.Width()>nDestW || rtArea.Height()>nDestH)	return;
	if(rtArea.left<0)			ptOffset.x = abs(rtArea.left);
	if(rtArea.right>=nSrcW)		ptOffset.x = nSrcW-rtArea.right-1;
	if(rtArea.top<0)			ptOffset.y = abs(rtArea.top);
	if(rtArea.bottom>=nSrcH)	ptOffset.y = nSrcH-rtArea.bottom-1;
	rtArea.OffsetRect(ptOffset);

	for(int j=rtArea.top;j<rtArea.bottom;j++)
		for(int i=rtArea.left;i<rtArea.right;i++)
		{
			x = (nDestSttX+i-rtArea.left);
			y = (nDestSttY+j-rtArea.top);
			if(0<=x && x<nDestW && 0<=y && y<nDestH)
				fmDest[x+nDestW*y] = fmSrc[i+nSrcW*j];
		}
}
void CInspect::ImageSelectCopy2(unsigned char* fmSrc,unsigned char* fmDest,int nSrcW,int nSrcH,int l,int r,int t,int b,int nDestW,int nDestH,int nDestSttX,int nDestSttY)
{
	int x,y;
	CPoint ptOffset(0,0);
	CRect rtArea;
	rtArea.SetRect(l,t,r,b);
	if(rtArea.Width()>nDestW || rtArea.Height()>nDestH)	return;
	if(rtArea.left<0)			ptOffset.x = abs(rtArea.left);
	if(rtArea.right>=nSrcW)		ptOffset.x = nSrcW-rtArea.right-1;
	if(rtArea.top<0)			ptOffset.y = abs(rtArea.top);
	if(rtArea.bottom>=nSrcH)	ptOffset.y = nSrcH-rtArea.bottom-1;
	rtArea.OffsetRect(ptOffset);

	for(int j=rtArea.top;j<rtArea.bottom;j++)
		for(int i=rtArea.left;i<rtArea.right;i++)
		{
			x = (nDestSttX+i-rtArea.left);
			y = (nDestSttY+j-rtArea.top);
			if(0<=x && x<nDestW && 0<=y && y<nDestH)
				fmDest[x+nDestW*y] = fmSrc[i+nSrcW*j];
		}
}

void CInspect::ImageSelectCopy3(unsigned char* fmSrc,unsigned char* fmDest,int nSrcW,int nSrcH,int l,int r,int t,int b,int nDestW,int nDestH,int nDestSttX,int nDestSttY,int nmag)
{
	int x,y;
	CPoint ptOffset(0,0);
	int nmid = (t+b)*0.5;
	CRect rtmag;
	rtmag.SetRect(l,nmid-(nDestH*0.5/nmag),r,nmid+(nDestH*0.5/nmag));
	CRect rtArea;
	if(nmag>1)
		rtArea = rtmag;
	else
		rtArea.SetRect(l,t,r,b);
	if(rtArea.Width()>nDestW || rtArea.Height()>nDestH)	return;
	if(rtArea.left<0)			ptOffset.x = abs(rtArea.left);
	if(rtArea.right>=nSrcW)		ptOffset.x = nSrcW-rtArea.right-1;
	if(rtArea.top<0)			ptOffset.y = abs(rtArea.top);
	if(rtArea.bottom>=nSrcH)	ptOffset.y = nSrcH-rtArea.bottom-1;
	rtArea.OffsetRect(ptOffset);

	if(nmag>1){
		for(int j=rtArea.top;j<rtArea.bottom;j++)
			for(int i=rtArea.left;i<rtArea.right;i++)
			{
				x = (nDestSttX+i-rtArea.left);
				y = (nDestSttY+j-rtArea.top)*nmag;
				if(0<=x && x<nDestW && 0<=y && y<nDestH){
					for(int k=y;k<nmag+y;k++){
						fmDest[x+nDestW*k] = fmSrc[i+nSrcW*j];
					}
				}
			}
	}
	else{
		for(int j=rtArea.top;j<rtArea.bottom;j++)
			for(int i=rtArea.left;i<rtArea.right;i++)
			{
				x = (nDestSttX+i-rtArea.left);
				y = (nDestSttY+j-rtArea.top);
				if(0<=x && x<nDestW && 0<=y && y<nDestH){
					fmDest[x+nDestW*y] = fmSrc[i+nSrcW*j];
				}
			}
	}
}

void CInspect::ImageSelectCopy4(CData* pData,unsigned char* fmSrc,unsigned char* fmDest,int nSrcW,int nSrcH,int l,int r,int t,int b,int nDestW,int nDestH,int nDestSttX,int nDestSttY,int nmag,int nCam)
{
	int x,y;
	CPoint ptOffset(0,0);
	int nmid = (t+b)*0.5;
	CRect rtmag;
	rtmag.SetRect(l,nmid-(nDestH*0.5/nmag),r,nmid+(nDestH*0.5/nmag));
	CRect rtArea;
	if(nmag>1)
		rtArea = rtmag;
	else
		rtArea.SetRect(l,t,r,b);
	if(rtArea.Width()>nDestW || rtArea.Height()>nDestH)	return;
	if(rtArea.left<0)			ptOffset.x = abs(rtArea.left);
	if(rtArea.right>=nSrcW)		ptOffset.x = nSrcW-rtArea.right-1;
	if(rtArea.top<0)			ptOffset.y = abs(rtArea.top);
	if(rtArea.bottom>=nSrcH)	ptOffset.y = nSrcH-rtArea.bottom-1;
	rtArea.OffsetRect(ptOffset);

	BYTE* fmtmp1 =	new BYTE[BAD_IMG_WIDTH*BAD_IMG_HEIGHT];
	memset(fmtmp1,0,BAD_IMG_WIDTH*BAD_IMG_HEIGHT);
	//m_bBinImage
	if(nmag>1){
		for(int j=rtArea.top;j<rtArea.bottom;j++)
			for(int i=rtArea.left;i<rtArea.right;i++)
			{
				x = (nDestSttX+i-rtArea.left);
				y = (nDestSttY+j-rtArea.top)*nmag;
				if(0<=x && x<nDestW && 0<=y && y<nDestH){
					for(int k=y;k<nmag+y;k++){
						fmDest[x+nDestW*k] = fmSrc[i+nSrcW*j];
						if(m_bBinImage ){
							int nTh = int(pData->m_nProjectX[nCam][i]+ pData->m_nThWhite3);
							if(k==0 || k==nDestW-1||x==0 || x==nDestW-1)	*(fmtmp1+k*nDestW+x) = 0;
							else if(*(fmSrc+(j)*nSrcW+i)>nTh)
								*(fmtmp1+k*nDestW+x) = 255;
							else						
								*(fmtmp1+k*nDestW+x) = 0;

						}
					}
				}
			}
	}
	else{
		for(int j=rtArea.top;j<rtArea.bottom;j++)
			for(int i=rtArea.left;i<rtArea.right;i++)
			{
				x = (nDestSttX+i-rtArea.left);
				y = (nDestSttY+j-rtArea.top);
				if(0<=x && x<nDestW && 0<=y && y<nDestH){
					fmDest[x+nDestW*y] = fmSrc[i+nSrcW*j];
				}
			}
	}
	if(m_bBinImage && nmag>1)
		memcpy(fmDest,fmtmp1,BAD_IMG_WIDTH*BAD_IMG_HEIGHT);

	delete fmtmp1;
}
void CInspect::ImageSelectCopy5(CData* pData,unsigned char* fmSrc,unsigned char* fmDest,int nSrcW,int nSrcH,int l,int r,int t,int b,int nDestW,int nDestH,int nDestSttX,int nDestSttY,int nmag,int nCam)
{
	int x,y;
	CPoint ptOffset(0,0);
	int nmid = (t+b)*0.5;
	CRect rtmag;
	if(nmag>1 && nmag%2 ==1)
		nmag--;
	rtmag.SetRect(l,nmid-(nDestH*0.5/nmag),r,nmid+(nDestH*0.5/nmag));
	CRect rtArea;
	if(nmag>1)
		rtArea = rtmag;
	else
		rtArea.SetRect(l,t,r,b);
	if(rtArea.Width()>nDestW || rtArea.Height()>nDestH)	return;
	if(rtArea.left<0)			ptOffset.x = abs(rtArea.left);
	if(rtArea.right>=nSrcW)		ptOffset.x = nSrcW-rtArea.right-1;
	if(rtArea.top<0)			ptOffset.y = abs(rtArea.top);
	if(rtArea.bottom>=nSrcH)	ptOffset.y = nSrcH-rtArea.bottom-1;
	rtArea.OffsetRect(ptOffset);

	BYTE* fmtmp1 =	new BYTE[BAD_IMG_WIDTH*BAD_IMG_HEIGHT];
	memset(fmtmp1,0,BAD_IMG_WIDTH*BAD_IMG_HEIGHT);
	//m_bBinImage
	if(nmag>1){
		for(int j=rtArea.top;j<rtArea.bottom;j++)
			for(int i=rtArea.left;i<rtArea.right;i++)
			{
				x = (nDestSttX+i-rtArea.left);
				y = (nDestSttY+j-rtArea.top)*nmag;
				if(0<=x && x<nDestW && 0<=y && y<nDestH){
					for(int k=y;k<nmag+y;k++){
						fmDest[x+nDestW*k] = fmSrc[i+nSrcW*j];
						if(m_bBinImage ){
							int nTh = int(pData->m_nFullImageProj[i]+ pData->m_nThWhite3);
							if(k==0 || k==nDestW-1||x==0 || x==nDestW-1)	*(fmtmp1+k*nDestW+x) = 0;
							else if(*(fmSrc+(j)*nSrcW+i)>nTh)
								*(fmtmp1+k*nDestW+x) = 255;
							else						
								*(fmtmp1+k*nDestW+x) = 0;

						}
					}
				}
			}
	}
	else{
		for(int j=rtArea.top;j<rtArea.bottom;j++)
			for(int i=rtArea.left;i<rtArea.right;i++)
			{
				x = (nDestSttX+i-rtArea.left);
				y = (nDestSttY+j-rtArea.top);
				if(0<=x && x<nDestW && 0<=y && y<nDestH){
					fmDest[x+nDestW*y] = fmSrc[i+nSrcW*j];
				}
			}
	}
	if(m_bBinImage && nmag>1)
		memcpy(fmDest,fmtmp1,BAD_IMG_WIDTH*BAD_IMG_HEIGHT);

	delete fmtmp1;
}
void CInspect::ImageSelectCopy1(unsigned char* fmSrc,unsigned char* fmDest,int nSrcW,int nSrcH,CRect rtArea,int nDestW,int nDestH,int nDestSttX,int nDestSttY,int nReduce,BOOL bColor)
{
	int x,y;
	CPoint ptOffset(0,0);
//	if(rtArea.Width()>nDestW || rtArea.Height()>nDestH)	return;
	if(rtArea.left<0)			ptOffset.x = abs(rtArea.left);
	if(rtArea.right>=nSrcW)		ptOffset.x = nSrcW-rtArea.right-1;
	if(rtArea.top<0)			ptOffset.y = abs(rtArea.top);
	if(rtArea.bottom>=nSrcH)	ptOffset.y = nSrcH-rtArea.bottom-1;
	rtArea.OffsetRect(ptOffset);

	int ntmp1 = 1000;
	for(int j=rtArea.top;j<rtArea.bottom;j+=nReduce)
		for(int i=rtArea.left;i<rtArea.right;i+=nReduce)
		{
			x = (nDestSttX+i-rtArea.left)/nReduce;
			y = (nDestSttY+j-rtArea.top)/nReduce;
			if(0<=x && x<nDestW && 0<=y && y<nDestH){
				if(bColor){//white
					ntmp1 = 0;
					for(int y1 = j;y1<j+nReduce;y1++){
						for(int x1 = i;x1<i+nReduce;x1++){
							if(fmSrc[x1+nSrcW*y1]>ntmp1)
								ntmp1 = fmSrc[x1+nSrcW*y1];
						}	
					}
				}
				else{//black
					ntmp1 = 1000;
					for(int y1 = j;y1<j+nReduce;y1++){
						for(int x1 = i;x1<i+nReduce;x1++){
							if(fmSrc[x1+nSrcW*y1]<ntmp1)
								ntmp1 = fmSrc[x1+nSrcW*y1];
						}	
					}

				}
				fmDest[x+nDestW*y] = ntmp1;
			}
		}
}

void CInspect::ImageSelectCopyScratch(unsigned char* fmSrc,unsigned char* fmDest,int nSrcW,int nSrcH,CRect rtArea,int nDestW,int nDestH,int nDestSttX,int nDestSttY,int nYOffset)
{
	int x,y;
	CPoint ptOffset(0,0);
	if(rtArea.Width()>nDestW || rtArea.Height()>nDestH*nYOffset)	return;
	if(rtArea.left<0)			ptOffset.x = abs(rtArea.left);
	if(rtArea.right>=nSrcW)		ptOffset.x = nSrcW-rtArea.right-1;
	if(rtArea.top<0)			ptOffset.y = abs(rtArea.top);
	if(rtArea.bottom>=nSrcH)	ptOffset.y = nSrcH-rtArea.bottom-1;
	rtArea.OffsetRect(ptOffset);
	int nTmp = 0,noldtmp = 0;;
	for(int j=rtArea.top;j<rtArea.bottom;j+=nYOffset)
		for(int i=rtArea.left;i<rtArea.right;i++)
		{
			nTmp = 0;
			for(int k=j;k<j+nYOffset*2;k++){
				if(k>=nSrcH){
					nTmp = noldtmp;
				}
				else{
					if( fmSrc[i+nSrcW*k]>nTmp)
						nTmp = fmSrc[i+nSrcW*k];
				}
				noldtmp = nTmp;
			}
			x = (nDestSttX+i-rtArea.left);
			y = (nDestSttY+j-rtArea.top)/nYOffset;
			if(0<=x && x<nDestW && 0<=y && y<nDestH*nYOffset)
				fmDest[x+nDestW*y] = nTmp;//fmSrc[i+nSrcW*j];
		}
}
void CInspect::ImageSelectCopyScratch1(unsigned char* fmSrc,unsigned char* fmDest,int nSrcW,int nSrcH,CRect rtArea,int nDestW,int nDestH,int nDestSttX,int nDestSttY,int nYOffset)
{
	int x,y;
	CPoint ptOffset(0,0);
	if(rtArea.Width()>nDestW || rtArea.Height()>nDestH*nYOffset)	return;
	if(rtArea.left<0)			ptOffset.x = abs(rtArea.left);
	if(rtArea.right>=nSrcW)		ptOffset.x = nSrcW-rtArea.right-1;
	if(rtArea.top<0)			ptOffset.y = abs(rtArea.top);
	if(rtArea.bottom>=nSrcH)	ptOffset.y = nSrcH-rtArea.bottom-1;
	rtArea.OffsetRect(ptOffset);
	for(int j=rtArea.top;j<rtArea.bottom;j+=nYOffset)
		for(int i=rtArea.left;i<rtArea.right;i++)
		{

			x = (nDestSttX+i-rtArea.left);
			y = (nDestSttY+j-rtArea.top)/nYOffset;
			if(0<=x && x<nDestW && 0<=y && y<nDestH*nYOffset)
				fmDest[x+nDestW*y] = fmSrc[i+nSrcW*j];
		}
}

void CInspect::ImageSelectCopyScratch2(unsigned char* fmSrc,unsigned char* fmDest,int nSrcW,int nSrcH,CRect rtArea,int nDestW,int nDestH,int nDestSttX,int nDestSttY,int nYOffset)
{
	int x,y;
	CPoint ptOffset(0,0);
	if(rtArea.Width()>nDestW || rtArea.Height()>nDestH*nYOffset)	return;
	if(rtArea.left<0)			ptOffset.x = abs(rtArea.left);
	if(rtArea.right>=nSrcW)		ptOffset.x = nSrcW-rtArea.right-1;
	if(rtArea.top<0)			ptOffset.y = abs(rtArea.top);
	if(rtArea.bottom>=nSrcH)	ptOffset.y = nSrcH-rtArea.bottom-1;
	rtArea.OffsetRect(ptOffset);
	for(int j=rtArea.top;j<rtArea.bottom;j+=nYOffset)
		for(int i=rtArea.left;i<rtArea.right;i++)
		{

			x = (nDestSttX+i-rtArea.left);
			y = (nDestSttY+j-rtArea.top)/nYOffset;
			if(0<=x && x<nDestW && 0<=y && y<nDestH*nYOffset)
				fmDest[x+nDestW*y] = fmSrc[i+nSrcW*j];
		}
}

int CInspect::GetSplitImgScratch(CImage* pImage, CData* pData,int nCam,int nIdx,int nMod)//Edge detect, AverageBrightness, FullImageProfileData[x], ROI Set
{
	//defect count duration.
	unsigned char* fm = pImage->GetImagePtr();
	int nCount = 10;
	int nw = pImage->GetWidth();
	int nh = pImage->GetHeight();
	int nstt = 0,nend = nh;
	if( nIdx==0)
		nstt=0,nend = nh/nMod;
	else 
		nstt = (nh/nMod)*(nIdx),nend=(nh/nMod)*(nIdx+1); 

	int nindex = nIdx;
	int nh1 = nh/nMod;
	int x1 = pData->m_rectIns[0].left,x2= pData->m_rectIns[0].right;//검사영역
	CString str,str1;
	
	int ntmp = 0,nmin=10000,nmax=0;
	double *dWidth1,*dWidth2,*dWidth3;
	dWidth1=(double*)malloc(nw*sizeof(double));//Split Image Projection Data
	dWidth2=(double*)malloc(nw*sizeof(double));//Projection Data Slope Value
	dWidth3=(double*)malloc(nw*sizeof(double));//Projection Data Slope Value
	for(int i=0;i<nw;i++) dWidth1[i]=dWidth2[i]=dWidth3[i]=0;

	for(int y=nstt;y<nend;y++)
		for(int x=x1;x<x2;x++)
			dWidth1[x] += *(fm+y*nw+x);
	
	for(int x=x1;x<x2;x++)		dWidth1[x]/=(double(nend)-double(nstt));
	int nGap = 6;//4pixel의 gap을 본다.
	for(int x=x1+nGap;x<x2-nGap;x++){
		dWidth2[x] = dWidth1[x]-dWidth1[x+nGap];
		dWidth3[x] = ((dWidth1[x]-dWidth1[x-nGap])+(dWidth1[x]-dWidth1[x+nGap]))*10;
		//str1.Format("scdata%d",nIdx);str.Format("%d , %.1f , %.1f",x,dWidth2[x],dWidth3[x]);WriteLog(str1,str);Sleep(1);
	}

	CPoint ptCandidate[MAX_DEFECT];
	int nx1[MAX_DEFECT],ny1[MAX_DEFECT],nx2[MAX_DEFECT],ny2[MAX_DEFECT],nColor[MAX_DEFECT];
	for(int i=0;i<MAX_DEFECT;i++){
		ptCandidate[i].SetPoint(0,0);
		nx1[i]=ny1[i]=nx2[i]=ny2[i]=0;
		nColor[i] = 0;
	}
	//defect condidate
	int nDefectCount = pData->m_nCandidatePointCount[nindex];//defect count 유지
	int nOriginCount = pData->m_nCandidatePointCount[nindex];//jumping을 위한 count
	int nbadx = BAD_IMG_WIDTH*0.5;
	int nbady = BAD_IMG_HEIGHT*0.5;
	BOOL bJump = FALSE,nskipx = 0;
//	int nthup = pData->m_dThUp[0];
	int nthdn = pData->m_dThDn[0];
	int y = nstt+(nend-nstt)*0.5;

	//mesh 단위 가장 센것만 찾는다.
	int nXRange[4],noffset = nw/4;;
	for(int i=0;i<4;i++)nXRange[i] = noffset*i;
	for(int x=x1;x<x2;x++){
		if(nDefectCount >= MAX_DEFECT-1) goto done;
		bJump = FALSE;
		if(dWidth3[x]>nmax)nmax = dWidth3[x];
		if(dWidth3[x]<nmin)nmin = dWidth3[x];
		if(dWidth3[x] >= nthdn){//nthup
			for(int i=nOriginCount;i<nDefectCount && bJump==FALSE;i++){
				if(x>=nx1[i] && x<nx2[i] && y >= ny1[i] && y<ny2[i]){
					x = nx2[i];
					bJump = TRUE;
				}
			}
			if(bJump)continue;
			ptCandidate[nDefectCount].SetPoint(x,nh-y);
			pData->AddDefectPoint(ptCandidate[nDefectCount],CPoint(x,y),nindex);
			SetBoundary(CRect(x-nbadx,y-nbady,x+nbadx,y+nbady),nw,nstt,nend,&nx1[nDefectCount],&ny1[nDefectCount],&nx2[nDefectCount],&ny2[nDefectCount]);			
			nColor[nDefectCount] = 255;
			pData->m_nCandidateType[nindex][nDefectCount] = DCLASS_GSR_SCRATCH;
			pData->m_nCandidateScValue[nindex][nDefectCount] = dWidth3[x];
//			pData->m_nDefectType[0][nDefectCount] = ;
			x += BAD_IMG_WIDTH;
			nDefectCount++;
		}
		else if(dWidth3[x]<=-nthdn)
		{
			for(int i=nOriginCount;i<nDefectCount && bJump==FALSE;i++){
				if(x>=nx1[i] && x<nx2[i] && y >= ny1[i] && y<ny2[i]){
					x = nx2[i];
					bJump = TRUE;
				}
			}
			if(bJump)continue;
			//우선 후보로만 뽑는다.
			ptCandidate[nDefectCount].SetPoint(x,nh-y);
			pData->AddDefectPoint(ptCandidate[nDefectCount],CPoint(x,y),nindex);
			SetBoundary(CRect(x-nbadx,y-nbady,x+nbadx,y+nbady),nw,nstt,nend,&nx1[nDefectCount],&ny1[nDefectCount],&nx2[nDefectCount],&ny2[nDefectCount]);			
			nColor[nDefectCount] = 0;
			pData->m_nCandidateType[nindex][nDefectCount] = DCLASS_GSR_SCRATCH;
			pData->m_nCandidateScValue[nindex][nDefectCount] = dWidth3[x];
//			pData->m_nDefectType[0][nDefectCount] = DCLASS_GSR_SCRATCH;
			x += BAD_IMG_WIDTH;
			nDefectCount++;
		}
	}
done:

	pData->m_nMaxImageLine[0][nindex]=nmax;//
	pData->m_nMinImageLine[0][nindex]=nmin;//

	if(dWidth1) free(dWidth1);
	if(dWidth2) free(dWidth2);
	if(dWidth3) free(dWidth3);
	return 0;
}
void CInspect::WriteLog(CString strFilename,CString str)
{
	CTime time = CTime::GetCurrentTime();

	CString strFile,strPath;
	CString kk = time.Format("%y%m%d");
	strPath.Format(_T("%s\\"),"c:\\Glim\\Log\\");
	CreateDirectory(strPath,NULL);
	strPath.Format(_T("%s\\%s\\"),"c:\\Glim\\Log\\",kk);
	CreateDirectory(strPath,NULL);
	strFile.Format("%s\\%s_%s.txt",strPath,time.Format("%Y%m%d"),strFilename);

	FILE *fp;
	fp = fopen((LPCSTR)strFile, "a");

	if(!fp)
		return;
	char* buf = new char[str.GetLength()+1];
	memcpy(buf, str.LockBuffer(), str.GetLength());
	buf[str.GetLength()] = '\0';

	fputs(buf, fp);
	fputs("\n",fp);
	delete []buf;
	fclose(fp);
}

void CInspect::UpdateNGImage(CImage *pImage, CData *pData,int nCam)
{
	if(pData->m_nRealDefectCount >= MAX_DEFECT)
		return;
	CRect rect;
	rect.left = rect.right = pData->m_rectDefect[nCam][pData->m_nRealDefectCount].CenterPoint().x;
	rect.top = rect.bottom = pData->m_rectDefect[nCam][pData->m_nRealDefectCount].CenterPoint().y;
	rect.InflateRect(BAD_IMG_WIDTH/2, BAD_IMG_HEIGHT/2);
	ValidRect(&rect,nCam,1);
	CopyBlockImg(pImage, rect, pData->m_pImageDefect[nCam][pData->m_nRealDefectCount],nCam);
}


//mesh 단위 가장 센 스크래치만 잡는다.
int CInspect::GetSplitImgScratch1(CImage* pImage, CData* pData,int nCam,int nIdx,int nMod)//Edge detect, AverageBrightness, FullImageProfileData[x], ROI Set
{
	//defect count duration.
	unsigned char* fm = pImage->GetImagePtr();
	int nCount = 10;
	int nw = pImage->GetWidth();
	int nh = pImage->GetHeight();
	int nstt = 0,nend = nh;
	if( nIdx==0)
		nstt=0,nend = nh/nMod;
	else 
		nstt = (nh/nMod)*(nIdx),nend=(nh/nMod)*(nIdx+1); 

	int nindex = nIdx;
	int nh1 = nh/nMod;
	int x1 = pData->m_rectIns[0].left,x2= pData->m_rectIns[0].right;//검사영역
	CString str,str1;

	int ntmp = 0,nmin=10000,nmax=0;
	double *dWidth1,*dWidth2,*dWidth3;
	dWidth1=(double*)malloc(nw*sizeof(double));//Split Image Projection Data
	dWidth2=(double*)malloc(nw*sizeof(double));//Projection Data Slope Value
	dWidth3=(double*)malloc(nw*sizeof(double));//Projection Data Slope Value
	for(int i=0;i<nw;i++) dWidth1[i]=dWidth2[i]=dWidth3[i]=0;

	for(int y=nstt;y<nend;y++)
		for(int x=x1;x<x2;x++)
			dWidth1[x] += *(fm+y*nw+x);

	for(int x=x1;x<x2;x++)		dWidth1[x]/=(double(nend)-double(nstt));
	int nGap = 6;//4pixel의 gap을 본다.
	for(int x=x1+nGap;x<x2-nGap;x++){
		dWidth2[x] = dWidth1[x]-dWidth1[x+nGap];
		dWidth3[x] = ((dWidth1[x]-dWidth1[x-nGap])+(dWidth1[x]-dWidth1[x+nGap]))*10;
		//str1.Format("scdata%d",nIdx);str.Format("%d , %.1f , %.1f",x,dWidth2[x],dWidth3[x]);WriteLog(str1,str);Sleep(1);
	}

	CPoint ptCandidate[MAX_DEFECT];
	int nx1[MAX_DEFECT],ny1[MAX_DEFECT],nx2[MAX_DEFECT],ny2[MAX_DEFECT],nColor[MAX_DEFECT];
	for(int i=0;i<MAX_DEFECT;i++){
		ptCandidate[i].SetPoint(0,0);
		nx1[i]=ny1[i]=nx2[i]=ny2[i]=0;
		nColor[i] = 0;
	}
	//defect condidate
	int nDefectCount = pData->m_nCandidatePointCount[nindex];//defect count 유지
	int nOriginCount = pData->m_nCandidatePointCount[nindex];//jumping을 위한 count
	int nbadx = BAD_IMG_WIDTH*0.5;
	int nbady = BAD_IMG_HEIGHT*0.5;
	BOOL bJump = FALSE,nskipx = 0;
	//	int nthup = pData->m_dThUp[0];
	int nthdn = pData->m_dThDn[0];
	int y = nstt+(nend-nstt)*0.5;

	//mesh 단위 가장 센것만 찾는다.
	int nXRange[4],noffset = nw/4;;
	for(int i=0;i<4;i++)nXRange[i] = noffset*(i+1);

	int x11=x1,x12;
	for(int k=0;k<4;k++){
		if(x11<nXRange[k]){
			x11 = noffset*k;
			x12 = noffset*(k+1);
		}
		int nPeakX=0;
		double dPeak = 0;
		for(int x=x11;x<x12;x++){
			if(x<x1+nGap || x>x2-nGap)continue;
			if(dWidth3[x]>nmax)nmax = dWidth3[x];
			if(dWidth3[x]<nmin)nmin = dWidth3[x];
			if(fabs(dWidth3[x])>dPeak){
				dPeak = fabs(dWidth3[x]);
				nPeakX = x;
			}
		}
		if(dPeak >= nthdn){//판단
			ptCandidate[nDefectCount].SetPoint(nPeakX,nh-y);
			pData->AddDefectPoint(ptCandidate[nDefectCount],CPoint(nPeakX,y),nindex);
			SetBoundary(CRect(nPeakX-nbadx,y-nbady,nPeakX+nbadx,y+nbady),nw,nstt,nend,&nx1[nDefectCount],&ny1[nDefectCount],&nx2[nDefectCount],&ny2[nDefectCount]);			
			nColor[nDefectCount] = 255;
			pData->m_nCandidateType[nindex][nDefectCount] = DCLASS_GSR_SCRATCH;
			pData->m_nCandidateScValue[nindex][nDefectCount] = dWidth3[nPeakX];
			nDefectCount++;

		}
	}
	pData->m_nMaxImageLine[0][nindex]=nmax;//
	pData->m_nMinImageLine[0][nindex]=nmin;//



	if(dWidth1) free(dWidth1);
	if(dWidth2) free(dWidth2);
	if(dWidth3) free(dWidth3);
	return 0;
}
int CInspect::GetSplitInspect3(CImage* pImage, CData* pData,int nCam,int nIdx,int nMod)//Edge detect, AverageBrightness, FullImageProfileData[x], ROI Set
{
	unsigned char* fm = pImage->GetImagePtr();
	int nCount = 10;
	int nw = pImage->GetWidth();
	int nh = pImage->GetHeight();
	int nstt = 0;
	int nend = nh;
	if( nIdx==0)
		nstt=0,nend = nh/nMod;
	else 
		nstt = (nh/nMod)*(nIdx),nend=(nh/nMod)*(nIdx+1); 

	int x1 = pData->m_rectIns[0].left,x2= pData->m_rectIns[0].right;//검사영역

	int nindex = nIdx;
	int nh1 = nh/nMod;

	CPoint ptCandidate[MAX_DEFECT];
	int nx1[MAX_DEFECT],ny1[MAX_DEFECT],nx2[MAX_DEFECT],ny2[MAX_DEFECT],nColor[MAX_DEFECT];
	for(int i=0;i<MAX_DEFECT;i++){
		ptCandidate[i].SetPoint(0,0);
		nx1[i]=ny1[i]=nx2[i]=ny2[i]=0;
		nColor[i] = 0;
	}
	//defect condidate
	int ntmp=0,nmin=255,nmax=0;
	int nbadx = BAD_IMG_WIDTH*0.5;
	int nbady = BAD_IMG_HEIGHT*0.5;
	BOOL bJump = FALSE,nskipx = 0;
	int nthup = pData->m_dThUp[0];
	int nthdn = pData->m_dThDn[0];
	int nDefectCount = pData->m_nCandidatePointCount[nindex];//defect count 유지
	int nOriginCount = pData->m_nCandidatePointCount[nindex];//jumping을 위한 count


	for(int y=nstt;y<nend;y++)
	{
		for(int x=x1;x<x2;x++){
			if(nDefectCount >= MAX_DEFECT-1) goto done;
			bJump = FALSE;
			ntmp = *(fm+y*nw+x);
			if(nmax<ntmp-pData->m_nProjectX[0][x])				nmax = ntmp-pData->m_nProjectX[0][x];
			if(nmin>ntmp-pData->m_nProjectX[0][x])				nmin = ntmp-pData->m_nProjectX[0][x];
			if(ntmp-pData->m_nProjectX[0][x] >= nthup){
				for(int i=nOriginCount;i<nDefectCount && bJump==FALSE;i++){
					if(x>=nx1[i] && x<nx2[i] )
						if( y >= ny1[i] && y<ny2[i]){
							x = nx2[i];bJump = TRUE;
						}
				}
				if(bJump)continue;
				//우선 후보로만 뽑는다.
				ptCandidate[nDefectCount].SetPoint(x,nh-y);//y reverse
				pData->AddDefectPoint(ptCandidate[nDefectCount],CPoint(x,y),nindex);
				pData->m_rtCandidate[nindex][nDefectCount]=	SetBoundary(CRect(x-nbadx,y-nbady,x+nbadx,y+nbady),nw,nstt,nend,&nx1[nDefectCount],&ny1[nDefectCount],&nx2[nDefectCount],&ny2[nDefectCount]);			
				nColor[nDefectCount] = 255;
				nDefectCount++;
			}
		}
	}
done:
	pData->m_nMaxImageValue[0][nIdx]=nmax;//
	pData->m_nMinImageValue[0][nIdx]=nmin;//

	return 0;
}

//mesh 단위 가장 센 스크래치와 백점을 같이 잡는다.
int CInspect::GetSplitImgScratchNDefect(CImage* pImage, CData* pData,int nCam,int nIdx,int nMod)//Edge detect, AverageBrightness, FullImageProfileData[x], ROI Set
{
	//defect count duration.
	unsigned char* fm = pImage->GetImagePtr();
	int nCount = 10;
	int nw = pImage->GetWidth();
	int nh = pImage->GetHeight();
	int nstt = 0,nend = nh;
	if( nIdx==0)
		nstt=0,nend = nh/nMod;
	else 
		nstt = (nh/nMod)*(nIdx),nend=(nh/nMod)*(nIdx+1); 

	int nindex = nIdx;
	int nh1 = nh/nMod;
	int x1 = pData->m_rectIns[0].left,x2= pData->m_rectIns[0].right;//검사영역
	CString str,str1;
	if(nIdx<0 || nh1<0 || nw<1 || x2-x1<5 || nend-nstt==0)return 0;

	int ntmp = 0,nmin=10000,nmax=0,ntmp1,ntmp2;
	double *dWidth1,*dWidth2,*dWidth3;
	dWidth1=(double*)malloc(nw*sizeof(double));//Split Image Projection Data
	dWidth2=(double*)malloc(nw*sizeof(double));//Projection Data Slope Value
	dWidth3=(double*)malloc(nw*sizeof(double));//Projection Data Slope Value
	for(int i=0;i<nw;i++) dWidth1[i]=dWidth2[i]=dWidth3[i]=0;

	int nIgnore = 4,nRisingV = 15;//pixel 이상은 제외시킨다.
	BOOL bFallingCheck = FALSE;
	for(int y=nstt;y<nend;y++){
		for(int x=x1;x<x2-nIgnore;x++){
			//noise ignore
			bFallingCheck = FALSE;
			ntmp1 = *(fm+y*nw+x);
			ntmp2 = *(fm+y*nw+x+2);
			//rising edge detect
			if(ntmp2-ntmp1>nRisingV){//Up
				bFallingCheck = TRUE;
				for(int m = x;m<x+nIgnore && m<x2-nIgnore;m++){
					//Falling Check
					ntmp1 = *(fm+y*nw+m);
					ntmp2 = *(fm+y*nw+m+2);
					if(ntmp1-ntmp2>nRisingV){
						//falling
						bFallingCheck = FALSE;
						break;
					}
				}
			}
			if(bFallingCheck){
				for(int m = x;m<x+nIgnore && m<x2-nIgnore;m++){
					dWidth1[m] += *(fm+y*nw+x);
				}
				x += nIgnore;
			}
			else
			{
				dWidth1[x] += *(fm+y*nw+x);
			}
		}
	}

	for(int x=x1;x<x2;x++)		dWidth1[x]/=(double(nend)-double(nstt));
	int nGap = 6,nGap1 = 32;//4pixel의 gap을 본다.
	int nX11 = x1+nGap1+1,nX22 = x2-nGap1*2;
	for(int x=x1+nGap;x<x2-nGap*2;x++){
		if(x>nX11 && x<nX22)
			dWidth2[x] = (dWidth1[x]-dWidth1[x-nGap1])+(dWidth1[x+nGap1]-dWidth1[x]);
//		dWidth2[x] = ((dWidth1[x]-dWidth1[x-nGap]))*10;
		dWidth3[x] = ((dWidth1[x]-dWidth1[x-nGap])+(dWidth1[x]-dWidth1[x+nGap]))*10;
//		str1.Format("scdata%d",nIdx);str.Format("%d , %.1f, %.1f , %.1f",x,dWidth1[x],dWidth2[x],dWidth3[x]);WriteLog(str1,str);Sleep(1);
	}

	CPoint ptCandidate[MAX_DEFECT];
	int nx1[MAX_DEFECT],ny1[MAX_DEFECT],nx2[MAX_DEFECT],ny2[MAX_DEFECT],nColor[MAX_DEFECT];
	for(int i=0;i<MAX_DEFECT;i++){
		ptCandidate[i].SetPoint(0,0);
		nx1[i]=ny1[i]=nx2[i]=ny2[i]=0;
		nColor[i] = 0;
	}
	//defect condidate
	int nDefectCount = pData->m_nCandidatePointCount[nindex];//defect count 유지
	int nOriginCount = pData->m_nCandidatePointCount[nindex];//jumping을 위한 count
	int nbadx = BAD_IMG_WIDTH*0.5;
	int nbady = BAD_IMG_HEIGHT*0.5;
	BOOL bJump = FALSE,nskipx = 0;
	//	int nthup = pData->m_dThUp[0];
	int nthdn = pData->m_dThDn[0];
	int nThUp = pData->m_dThUp[0];
	int y = nstt+(nend-nstt)*0.5;
	if(pData->m_bUse2Level[nCam]){
		nThUp = pData->m_dWeakThUp[0];//param21  약 d/s
		nthdn = pData->m_dWeakThDn[0];//param22  약 s/c
	}
	int	nOverlapLineV = pData->m_nLineOVerlapV[0];//param20 line
	double dOverlapPeak = 0;
	int nOverlpaPos = 0;

	//mesh 단위 가장 센것만 찾는다.
	int nXRange[4],noffset = nw/4;;
	for(int i=0;i<4;i++)nXRange[i] = noffset*(i+1);

	int x11=x1,x12;
	for(int k=0;k<4;k++){
		if(x11<nXRange[k]){//Mesh 단위 Range set
			x11 = noffset*k;
			x12 = noffset*(k+1);
		}
		else
			continue;
		int nPeakX=0,nPeakWhiteX= 0,nPeakWhiteY=0,nPeakBlackX= 0,nPeakBlackY=0;
		double dPeak = 0,dPeakWhiteValue=0,dPeakBlackValue=0;
		dOverlapPeak = 0;

		for(int x=x11;x<x12;x++){//한줄 
			if(x<x1+nGap || x>x2-nGap)continue;
			if(dWidth3[x]>nmax)nmax = dWidth3[x];
			if(dWidth3[x]<nmin)nmin = dWidth3[x];
			if(x>nX11 && x<nX22 &&dOverlapPeak<dWidth2[x] && dWidth2[x]>2){
				dOverlapPeak = dWidth2[x];
				nOverlpaPos = x+nGap1;

			}
			if(fabs(dWidth3[x])>dPeak){
				dPeak = fabs(dWidth3[x]);
				nPeakX = x;
			}
		}
		//white Search
		if((dPeak >= nthdn && nthdn>0)){//SC
			ptCandidate[nDefectCount].SetPoint(nPeakX,nh-y);
			pData->AddDefectPoint(ptCandidate[nDefectCount],CPoint(nPeakX,y),nindex);
			SetBoundary(CRect(nPeakX-nbadx,y-nbady,nPeakX+nbadx,y+nbady),nw,nstt,nend,&nx1[nDefectCount],&ny1[nDefectCount],&nx2[nDefectCount],&ny2[nDefectCount]);			
			nColor[nDefectCount] = 255;
			if(pData->m_bUse2Level[0] ){
				pData->m_nCandidateType[nindex][nDefectCount] = DCLASS_GSR_LOW_SCRATCH;
				if(dPeak >= pData->m_dThDn[0])
					pData->m_nCandidateType[nindex][nDefectCount] = DCLASS_GSR_SCRATCH;
			}
			else
				pData->m_nCandidateType[nindex][nDefectCount] = DCLASS_GSR_SCRATCH;
			
			pData->m_nCandidateScValue[nindex][nDefectCount] = fabs(dWidth3[nPeakX]);
			nDefectCount++;
		}
		else if(dOverlapPeak>=nOverlapLineV ){//꼽침
			ptCandidate[nDefectCount].SetPoint(nOverlpaPos,nh-y);
			pData->AddDefectPoint(ptCandidate[nDefectCount],CPoint(nOverlpaPos,y),nindex);
			SetBoundary(CRect(nOverlpaPos-nbadx,y-nbady,nOverlpaPos+nbadx,y+nbady),nw,nstt,nend,&nx1[nDefectCount],&ny1[nDefectCount],&nx2[nDefectCount],&ny2[nDefectCount]);			
			nColor[nDefectCount] = 255;
			if(pData->m_bUse2Level[0] ){
				pData->m_nCandidateType[nindex][nDefectCount] = DCLASS_GSR_LIMUL;
				if(dPeak >= pData->m_dThDn[0])
					pData->m_nCandidateType[nindex][nDefectCount] = DCLASS_GSR_LIMUL;
			}
			else
				pData->m_nCandidateType[nindex][nDefectCount] = DCLASS_GSR_LIMUL;

			pData->m_nCandidateScValue[nindex][nDefectCount] = fabs(dOverlapPeak);
			nDefectCount++;
		}
		else{//이때만 white를 찾는다.
			dPeakBlackValue = dPeakWhiteValue=0;
			for(int y=nstt;y<nend;y++)
			{
				for(int x=x11;x<x12;x++)
				{
					if(x<x1 || x>x2)continue;

					ntmp = *(fm+y*nw+x)-pData->m_nProjectX[0][x];
					if(pData->m_nMaxImageValue[0][nIdx]<ntmp)				pData->m_nMaxImageValue[0][nIdx] = ntmp;
					if(dPeakWhiteValue<ntmp){
						dPeakWhiteValue = ntmp;
						nPeakWhiteX = x;nPeakWhiteY=y;
					}
					if(dPeakBlackValue>ntmp){
						dPeakBlackValue = ntmp;
						nPeakBlackX = x;nPeakBlackY=y;
					}
				}
			}
			if(dPeakWhiteValue > nThUp ){
				//				ptCandidate[nDefectCount].SetPoint(nPeakWhiteX,nh-nPeakWhiteY);//y reverse
				ptCandidate[nDefectCount].SetPoint(nPeakWhiteX,nPeakWhiteY);//y reverse
				pData->AddDefectPoint(ptCandidate[nDefectCount],CPoint(nPeakWhiteX,nPeakWhiteY),nindex);
				pData->m_rtCandidate[nindex][nDefectCount]=	SetBoundary(CRect(nPeakWhiteX-nbadx,nPeakWhiteY-nbady,nPeakWhiteX+nbadx,nPeakWhiteY+nbady),nw,nstt,nend,&nx1[nDefectCount],&ny1[nDefectCount],&nx2[nDefectCount],&ny2[nDefectCount]);			
				pData->m_nCandidateType[nindex][nDefectCount] = DCLASS_GSR_CIMUL;
				nColor[nDefectCount] = 255;
				nDefectCount++;
			}
			if(dPeakBlackValue < -pData->m_nGl4BlackValue ){//여기 값 수정 필요 //param19
				//				ptCandidate[nDefectCount].SetPoint(nPeakWhiteX,nh-nPeakWhiteY);//y reverse
				ptCandidate[nDefectCount].SetPoint(nPeakBlackX,nPeakBlackY);//y reverse
				pData->AddDefectPoint(ptCandidate[nDefectCount],CPoint(nPeakBlackX,nPeakBlackY),nindex);
				pData->m_rtCandidate[nindex][nDefectCount]=	SetBoundary(CRect(nPeakBlackX-nbadx,nPeakBlackY-nbady,nPeakBlackX+nbadx,nPeakBlackY+nbady),nw,nstt,nend,&nx1[nDefectCount],&ny1[nDefectCount],&nx2[nDefectCount],&ny2[nDefectCount]);			
				pData->m_nCandidateType[nindex][nDefectCount] = DCLASS_GSR_SURFACE_DEFECT;
				nColor[nDefectCount] = 255;
				nDefectCount++;
			}
		}
	}
	pData->m_nMaxImageLine[0][nindex]=nmax;//
	pData->m_nMinImageLine[0][nindex]=nmin;//


	if(dWidth1) free(dWidth1);
	if(dWidth2) free(dWidth2);
	if(dWidth3) free(dWidth3);
	return 0;
}

void CInspect::GetLineWidthCheck(int nCam,BYTE* fmsrc,CData *pData,CRect rtDefect,int nIdx,BOOL bColor)
{

	int nIndex = nIdx;//pData->m_nRealDefectCount;

	unsigned char* fmtmp =	new BYTE[BAD_IMG_WIDTH*BAD_IMG_HEIGHT];
	memcpy(fmtmp,fmsrc,BAD_IMG_WIDTH*BAD_IMG_HEIGHT);
	unsigned char* fmtmp1 =	new BYTE[BAD_IMG_WIDTH*BAD_IMG_HEIGHT];
	memset(fmtmp1,0,BAD_IMG_WIDTH*BAD_IMG_HEIGHT);

	int nTh = 0;
	//평균밝기를 찾고 120%
	double dsum=0,dc1=0;
	for(int i=0;i<BAD_IMG_HEIGHT;i++){
		for(int j=0;j<BAD_IMG_WIDTH;j++){
			dsum += *(fmsrc+i*BAD_IMG_WIDTH+j);
			dc1++;
		}
	}
	dsum /= dc1;
	nTh = dsum * 1.2;
	for(int i=0;i<BAD_IMG_HEIGHT;i++){
		for(int j=0;j<BAD_IMG_WIDTH;j++){
			if(*(fmsrc+i*BAD_IMG_WIDTH+j)>nTh)	*(fmtmp+i*BAD_IMG_WIDTH+j) = OBJECT;
			else									*(fmtmp+i*BAD_IMG_WIDTH+j) = BACKGROUND;
		}
	}

	CRect rt1;
	
	rt1.SetRect(0,0,BAD_IMG_WIDTH,BAD_IMG_HEIGHT);
	fnDilate(fmtmp,fmtmp1,BAD_IMG_WIDTH,rt1,1);
	fnDilate(fmtmp1,fmtmp,BAD_IMG_WIDTH,rt1,1);
	fnDilate(fmtmp,fmtmp1,BAD_IMG_WIDTH,rt1,1);
	fnDilate(fmtmp1,fmtmp,BAD_IMG_WIDTH,rt1,1);

	double dTemp,dBlobSize;
	int  nBlobCount =-1, nBlobNo =0;
	CRect rtBlob;
	//거리를 측정하기위한 param
	double dCx, dCy, dAngle, dPos[4][2], dShortLength, dLongLength,dMin,dMax,dAve;
	double dLengTemp,dLengTemp1,dLengTemp2;
	double dlongLine = 0.0;
	//defect 개수가 1개로 저의 되어 있음. 수정 필요.
	dBlobSize = pData->m_dSize[nCam][nIndex]=  0.0;
	int nVisionLine = pData->m_nVisionLine;

//	FChain_SetChainData(1,fmtmp,1,0,0,100000,BAD_IMG_WIDTH,BAD_IMG_HEIGHT);
//	nBlobCount = FChain_FastChain(0, 0, BAD_IMG_WIDTH-1,BAD_IMG_HEIGHT-1);
	double dcompact = 0;

	//가장 큰면적만 따진다.
	for(int i=0;i<nBlobCount;i++)
	{
//		FChain_Area(i, &dTemp);//			dTemp = m_pChain->Chain_Area(i);ttt
		if(dTemp>=dBlobSize)//최대 불량 사이즈.
		{
			nBlobNo = i;
			dBlobSize = dTemp;//면적
		}
	}
	if(nBlobCount<=0)
	{
		delete fmtmp;
		delete fmtmp1;
		return;
	}
// 중심의 X 길이만 체크한다.
//	FChain_Center(nBlobNo, &dCx, &dCy);
	int nL1,nR1,nL2=0,nR2=0,nlrcnt = 0;
	int nst1 = dCy-3,ned1=dCy+3;
	if(nst1>=BAD_IMG_HEIGHT || nst1<0 || ned1>=BAD_IMG_HEIGHT || ned1<0){
		nst1 = BAD_IMG_HEIGHT*0.5-3;
		ned1 = nst1+6;
	}

	//최대 길이
	double dLength = 0;
//	FChain_Perimeter(nBlobNo,&dLength);
//sc경우 stdev에 값을 넣는다.
	//periment와 면적으로 구분한다.
	for(int i=nst1;i<ned1;i++){
//		FChain_LeftRightBoundary(nBlobNo,int(dCy),&nL1,&nR1);
		nL2 += nL1;nR2 += nR1;nlrcnt++;
	}

	if(nlrcnt>0){
		nL2 /= nlrcnt;nR2 /= nlrcnt;
		pData->m_dSizeX[nCam][nIndex] = (nR2-nL2) * pData->m_dScaleFactorX[nCam];
//		pData->m_dSizeY[nCam][nIndex] = (FChain_FindMaxY(nBlobNo)-FChain_FindMinY(nBlobNo))*  pData->m_dScaleFactorX[nCam];
	}


	pData->m_dTempData1[nCam][nIndex] = dBlobSize;//area
	pData->m_dTempData2[nCam][nIndex] = dLength;
	pData->m_nBlobCount[nCam][nIndex] = nBlobCount;


	if(pData->m_bCrossBlobImg[0])
		memcpy(fmsrc,fmtmp,BAD_IMG_WIDTH*BAD_IMG_HEIGHT);

	delete fmtmp;
	delete fmtmp1;
}

void CInspect::fnDilate(LPBYTE fmSour, LPBYTE fmDest,int npitch,CRect rt,int dir) 
{
	int i,j,k,l;
	int nOrgX, nOrgY;
	int nKernelSizeY,nKernelSizeX;
	nKernelSizeY = nKernelSizeX = 3;
	int nHeight = rt.Height();
	int nWidth = rt.Width();
	int kernel[9];
	for(i=0;i<9;i++) kernel[i] = 1;

	nOrgX=(int)(nKernelSizeX/2.0-0.5);
	nOrgY=(int)(nKernelSizeY/2.0-0.5);


	for(i=rt.top;i<rt.bottom-nKernelSizeY;i++)         //
		for(j=rt.left;j<rt.right-nKernelSizeX;j++)      //                     
		{
			if(dir)
			{
				for(k=0;k<nKernelSizeY;k++)
					for(l=0;l<nKernelSizeX;l++)
						//				   if( *(pKernel+nKernelSizeX*k+l) )    //				   if( *(kernel+nKernelSizeX*k+l) )                
						if( *(fmSour+(i+k)*npitch+j+l) )
						{
							*(fmDest+(i+nOrgY)*npitch+j+nOrgX)=255;
							goto LOOP;
						}
						*(fmDest+(i+nOrgY)*npitch+j+nOrgX)=0;					   
			}
			else
			{
				for(k=0;k<nKernelSizeY;k++)
					for(l=0;l<nKernelSizeX;l++)
						//				   if( *(pKernel+nKernelSizeX*k+l) )     //				   if( *(kernel+nKernelSizeX*k+l) )                
						if( *(fmSour+(i+k)*npitch+j+l) ==0)
						{
							*(fmDest+(i+nOrgY)*npitch+j+nOrgX)=0;
							goto LOOP;
						}
						*(fmDest+(i+nOrgY)*npitch+j+nOrgX)=255;					   
			}

LOOP:      continue;
		}

}


int CInspect::GetSplitInspect4(CImage* pImage, CData* pData,int nCam,int nIdx,int nMod)//Edge detect, AverageBrightness, FullImageProfileData[x], ROI Set
{//마키 검증용
	unsigned char* fm = pImage->GetImagePtr();
	int nCount = 10;
	int nw = pImage->GetWidth();
	int nh = pImage->GetHeight();
	int nstt = 0;
	int nend = nh;
	if( nIdx==0)
		nstt=0,nend = nh/nMod;
	else 
		nstt = (nh/nMod)*(nIdx),nend=(nh/nMod)*(nIdx+1); 

	int x1 = pData->m_rectIns[0].left,x2= pData->m_rectIns[0].right;//검사영역

	int nindex = nIdx;
	int nh1 = nh/nMod;

	int *nWidth1,*nWidth2,ntmp = 0;
	nWidth1=(int*)malloc(nw*sizeof(int));
	nWidth2=(int*)malloc(nw*sizeof(int));
	for(int i=0;i<nw;i++) nWidth1[i]=nWidth2[i]=0;

	for(int y=nstt;y<nend;y++)
	{
		for(int x=0;x<nw;x++){
			ntmp = *(fm+y*nw+x);
			nWidth1[x]+= ntmp;//*(fm+y*nw+x);
		}
	}
	for(int x=0;x<nw;x++)
		nWidth1[x]/=(nend-nstt);
	for(int x=x1+20;x<x2-20;x++)
		nWidth2[x] = abs(nWidth1[x] - nWidth1[x+8]);

	CPoint ptCandidate[MAX_DEFECT];
	int nx1[MAX_DEFECT],ny1[MAX_DEFECT],nx2[MAX_DEFECT],ny2[MAX_DEFECT],nColor[MAX_DEFECT];
	for(int i=0;i<MAX_DEFECT;i++){
		ptCandidate[i].SetPoint(0,0);
		nx1[i]=ny1[i]=nx2[i]=ny2[i]=0;
		nColor[i] = 0;
	}
	//defect candidate
	int nDefectCount = 0,nmin=255,nmax=0,nmin1=255,nmax1=0;
	int nbadx = BAD_IMG_WIDTH*0.5;
	int nbady = BAD_IMG_HEIGHT*0.5;
	BOOL bJump = FALSE,nskipx = 0;
	int nthup = pData->m_dThUp[0];
	int nthdn = pData->m_dThDn[0];

		//흑점만 본다. 백에는 구분이 많아 어떤 방향으로 갈지 ???
		nthdn = pData->m_dThDn[0];
	int nLineV = pData->m_nCycleUse[0];
	for(int y=nstt;y<nend;y++)
	{
		for(int x=x1;x<x2;x++){
			if(nDefectCount >= MAX_DEFECT-1) goto done;
			bJump = FALSE;
			ntmp = *(fm+y*nw+x);
			if(nmax<ntmp-pData->m_nProjectX[0][x])
				nmax = ntmp-pData->m_nProjectX[0][x];
			if(nmin>ntmp-pData->m_nProjectX[0][x])
				nmin = ntmp-pData->m_nProjectX[0][x];

			if(nmax1<nWidth2[x])nmax1 = nWidth2[x];
			if(nmin1>nWidth2[x])nmin1 = nWidth2[x];

			if(ntmp-pData->m_nProjectX[0][x]<=-nthdn)
			{
				for(int i=0;i<nDefectCount && bJump==FALSE;i++){
					if(x>=nx1[i] && x<nx2[i] && y >= ny1[i] && y<ny2[i]){
						x = nx2[i];
						bJump = TRUE;
					}
				}
				if(bJump)continue;
				//우선 후보로만 뽑는다.
				ptCandidate[nDefectCount].SetPoint(x,y);
				pData->AddDefectPoint(ptCandidate[nDefectCount],CPoint(x,y),nindex);
				pData->m_rtCandidate[nindex][nDefectCount]=	SetBoundary(CRect(x-nbadx,y-nbady,x+nbadx,y+nbady),nw,nstt,nend,&nx1[nDefectCount],&ny1[nDefectCount],&nx2[nDefectCount],&ny2[nDefectCount]);			
				nColor[nDefectCount] = 0;
				nDefectCount++;
			}
			
		
		}
	}
done:
	pData->m_nMaxImageValue[0][nIdx]=nmax;//
	pData->m_nMinImageValue[0][nIdx]=nmin;//
	
	pData->m_nMaxImageLine[0][nindex] = nmax1;
	if(nWidth1) free(nWidth1);
	if(nWidth2) free(nWidth2);

	return 0;
}

int	CInspect::GetImageLineData(CImage* pImage, CData* pData,int nCam,int nEdge,CRect rtInsp)//Edge detect, AverageBrightness, FullImageProfileData[x], ROI Set
{//nedge=-1일때 L->R 에지 검사 0일때 RT Insp 사용 1일때 R->l에지검사  
	int nw = pImage->GetWidth();
	int nh = pImage->GetHeight();
	pData->ResetData(nCam);
	int ntmp = 0,ntmp1=0,nc=0,nc11=0;
	pData->m_nLineThCount = 0;
	CString str,str1;
	BYTE * fm = pImage->GetImagePtr();

	int nx1,ny1,nw1 = nw/pData->m_nLineReduce;
	double dedge[CAM_WIDTH_CIS] = {0,};
	//제일 윗줄과 제일 아래줄의 white count를 센다
	int	nTopWhite = 0,nBotWhite=0,nFullWhiteLine = 0,nWhiteLineCnt = 0;
	int nmid = nw*0.5;
	for(int i=0;i<nh;i++)
	{
		//reduce 만큼 점프해서 검사하자 
		ny1 = i/pData->m_nLineReduce;
		if(MAX_CAMERAS<2)
		{//영상 압축을 한다.
			for(int j=0;j<nw;j++){
				pData->m_nProjectX[nCam][j] += *(fm+i*nw+j);//Full Data를 다 사용한다?? 왜??
				if(pData->m_nVisionLine==GL4)//압축 영상을 만드네 왜?
					*(m_fmLine+(ny1)*(nw1)+(j/pData->m_nLineReduce)) = *(fm+i*nw+j);
			}
		}
		else
		{
			nFullWhiteLine = 0;
			for(int j=0;j<nw;j++){
				pData->m_nProjectX[nCam][j] += *(fm+i*nw+j);//Full Data를 다 사용한다?? 왜??
				if(*(fm+i*nw+j)>200)
					nFullWhiteLine++;
				if(i==0 && *(fm+i*nw+j)>200)nTopWhite++;
				else if(i>=3030&&i<3050 && *(fm+i*nw+j)>200)nBotWhite++;
			}
			if(nFullWhiteLine>nmid)
				nWhiteLineCnt++;
			i +=pData->m_nLineReduce; //y를 점프한다.
		}
	}

// 	if(nTopWhite<nBotWhite)nTopWhite= nBotWhite;
// //	if(nTopWhite<nFullWhiteLine)nTopWhite = nFullWhiteLine;
// 
	//처음 에지는 가까울수 있다.
	int nOffset1 = 15;
	int nOffset2 = 20;//200 //@chcho0821 중앙 좁은 무지폭 투입관련
	nc11 = nh/pData->m_nLineReduce;

	int nTol = pData->m_nGl4BlackValue1[nCam];
	for(int j=0;j<nw;j++)
	{
		if(MAX_CAMERAS>1)	pData->m_nProjectX[nCam][j] /= nc11;// pData->m_nLineReduce;
		else				pData->m_nProjectX[nCam][j] /= nh;
		if(nCam==0){
			if(j>3000){
				ntmp1+=pData->m_nProjectX[nCam][j];
				nc++;
			}
		}
		else if(nCam==2){
			if(j<nw-3000){
				ntmp1+=pData->m_nProjectX[nCam][j];
				nc++;
			}
		}
		else{
			ntmp1+=pData->m_nProjectX[nCam][j];
			nc++;
		}
		//str1.Format("BaseProfile%d",nCam);str.Format("%d , %d ",j,pData->m_nProjectX[nCam][j]);WriteLog(str1,str);Sleep(1);//Log로 테스트시.
	}
	if(nc>0)//개략적인 평균 밝기
		ntmp1 /= nc;
	else
		ntmp1 = 0;

	if(nWhiteLineCnt>5){

		return 255;
	}
	
	//에지 찾기 추가할것.//chcho
	int nEdgeth = 55;
	BOOL bAve = FALSE;
	nEdgeth = pData->m_dThUp[nCam];//sparam1
//	nEdgeth =35;
	//화면내 모든 에지 찾기
	//카메라0 인경우 왼쪽(black)->오른쪽(White) = 원단 끝 일정 offset 후 White->Black (coating Start pos)
	int nOffset = 50,ncount1 = 0;
	int nskip = 30;
	double dEdgeSum = 0,dcount1=0;
	int nc1 = 0,nMode = 0;
	int		nEdgeData[CAM_WIDTH_CIS];
	int nMax=0,nMin=255,npos1=0,npos2=0,nmax1=0,npos11=0,nmax2=0,npos12=0;
	int nBlackValue = 30;
	for(int i=0;i<CAM_WIDTH_CIS;i++)nEdgeData[i] = 0;

	int nEnd = 2500;
	nEnd = 600;
	if(pData->m_strComName.Find("02")>=0)
		nEnd = 1400;
	int nRoiCount = 0;
	//최소 라인폭 
	int nMinLineWidth = pData->m_nMinLineWidth;
	int nMinLineWidth1 = pData->m_nMinLineWidthMid;
	int nLineJump= 0;
	int nGap1 = 6,ngap2=10;

	if(nMode==1){//전체 미분 Data를 구한뒤 미분 평균으로 에지를 구한다.
		for(int i=0;i<nw-10;i++){
			//highcut 을 사용하여 에지 data를 넣는다.
			nEdgeData[i] = pData->m_nProjectX[nCam][i]-pData->m_nProjectX[nCam][i+4];
			if(abs(pData->m_nProjectX[nCam][i]-pData->m_nProjectX[nCam][i+4])>10){
				dEdgeSum += abs(pData->m_nProjectX[nCam][i]-pData->m_nProjectX[nCam][i+4]);
				dcount1++;
			}
			ncount1++;
		}
		dEdgeSum  /=  dcount1; //th value
	}
	else if(nMode==2){//흑에서 백만 찾는다.
	}
	else{//그냥 에지를 찾는다.
		int nlinecount = 0;
		int nWhitev1 = 100;//150;
		int nBlack1 = 50;
		if(nCam==0 ){//상부
			//L -> R  Black ->White
			for(int i=nEnd;i<nw-10;i++){
				if(nc1>=MAX_REALDEFECT-1) break;
				if(bAve==FALSE && abs(pData->m_nProjectX[nCam][i]-pData->m_nProjectX[nCam][i+nGap1]) >= nEdgeth && abs(pData->m_nProjectX[nCam][i+1]-pData->m_nProjectX[nCam][i+nGap1+1]) >= nEdgeth && pData->m_nProjectX[nCam][i+8]>nWhitev1/*&&(pData->m_nProjectX[nCam][i]>20 ||pData->m_nProjectX[nCam][i+4]>20)*/)
				{
					if(i<3470)
						i = i;
					//if(nlinecount>0 )
					{//&&  abs(i - pData->m_dLineEdgeData1[nCam][nlinecount-1]) < nMinLineWidth){
						for(int xx1=i+ngap2;xx1<i+nMinLineWidth;xx1++){
							if(xx1>=CAM_WIDTH_CIS-nMinLineWidth-10 || i>=CAM_WIDTH_CIS-nMinLineWidth-10)
								break;

							if(abs(pData->m_nProjectX[nCam][xx1]-pData->m_nProjectX[nCam][xx1+4]) >= nEdgeth)
							{
								nLineJump = 1;
								i= xx1+10;
								break;
							}
						}
					}
					if(nLineJump==1){nLineJump = 0;continue;}
					pData->m_rectIns[nCam].left = i;bAve=TRUE;
					if(pData->m_nTacXpos[0]>0)pData->m_rectIns[nCam].left += pData->m_nTacXpos[0];
					////다시 에지가 가장 강한데를 찾는다.
					nMax = 0;
					for(int k=i-4;k<i+20;k++){
						if(k<10)k=10;if(k>=CAM_WIDTH_CIS-10)break;
						ntmp = abs(pData->m_nProjectX[nCam][k]-pData->m_nProjectX[nCam][k+2]);
						if(ntmp >= nMax){npos1 = k+nTol;	nMax = ntmp;}
					}
					int nc21 = 0;
					for(int k=0;k<CAM_HEIGHT_3072;k+=pData->m_nLineReduce){
						nmax1 = 0;
						for(int n1=npos1-4;n1<npos1+6;n1++){
							if( abs(*(fm+k*nw+n1) -  *(fm+k*nw+n1+2)) > nmax1){
								npos11 = n1+nTol;nmax1=abs(*(fm+k*nw+n1) -  *(fm+k*nw+n1+2));
							}
						}
						dedge[nc1] += npos11;
						nc21++;
					}
					dedge[nc1] /= nc21;

					if(pData->m_bSumEdgeData==TRUE){
						pData->m_nPolarEdge[0]=dedge[nc1];
						pData->m_dLineEdgeData1[nCam][nc1] = dedge[nc1];
					}
					else{
						pData->m_nPolarEdge[0]=npos1;
						pData->m_dLineEdgeData1[nCam][nc1] = npos1;
					}
//					pData->m_nPolarEdge[0]=npos1;
//					pData->m_dLineEdgeData1[nCam][nc1] = npos1;
					pData->m_dEdgeValue1[nCam][nc1] = nMax;// pData->m_nProjectX[nCam][i]-pData->m_nProjectX[nCam][i+4];
					if(nRoiCount>0){
						pData->m_rtInspect[nCam][nRoiCount].right = npos1%CAM_WIDTH_CIS;//black end
						nRoiCount++;
					}
					pData->m_rtInspect[nCam][nRoiCount].left = npos1%CAM_WIDTH_CIS;//white start

					//최소갑을 증가시킨다.
					if(nc1==0)
						nMinLineWidth = nMinLineWidth1;
					nc1++;
					if(nc1==1)
						i+=nOffset1;
					else
						i+= nOffset2;
					bAve=TRUE;
					nlinecount++;
				}
				else if(bAve==TRUE && abs(pData->m_nProjectX[nCam][i]-pData->m_nProjectX[nCam][i+nGap1]) >= nEdgeth && abs(pData->m_nProjectX[nCam][i+1]-pData->m_nProjectX[nCam][i+nGap1+1]) >= nEdgeth/*&&(pData->m_nProjectX[nCam][i]>20 ||pData->m_nProjectX[nCam][i+4]>20)*/)
				{

					if(i<3470)
						i = i;

					//if(nlinecount>0 )
					{//&&  abs(i - pData->m_dLineEdgeData1[nCam][nlinecount-1]) < nMinLineWidth){
						for(int xx1=i+ngap2;xx1<i+nMinLineWidth;xx1++){
							if(xx1>=CAM_WIDTH_CIS-nMinLineWidth-10 || i>=CAM_WIDTH_CIS-nMinLineWidth-10)
								break;
							if(abs(pData->m_nProjectX[nCam][xx1]-pData->m_nProjectX[nCam][xx1+4]) >= nEdgeth)
							{
								nLineJump = 1;
								i= xx1+10;
								break;
							}
						}
					}
					if(nLineJump==1){nLineJump = 0;continue;}

					nMax = 0;
					for(int k=i-4;k<i+20;k++){
						if(k<10)k=10;if(k>=CAM_WIDTH_CIS-10)break;
						ntmp = abs(pData->m_nProjectX[nCam][k]-pData->m_nProjectX[nCam][k+2]);
						if(ntmp >= nMax){npos1 = k+nTol;	nMax = ntmp;}
					}

// 					ntmp1+=pData->m_nProjectX[nCam][i];
					int nc21 = 0;
					for(int k=0;k<CAM_HEIGHT_3072;k+=pData->m_nLineReduce){
						nmax1 = 0;
						for(int n1=npos1-4;n1<npos1+6;n1++){
							
							if(abs( *(fm+k*nw+n1) -  *(fm+k*nw+n1+2)) > nmax1){
								npos11 = n1+nTol;nmax1=abs(*(fm+k*nw+n1) -  *(fm+k*nw+n1+2));
							}
						}
						dedge[nc1] += npos11;
						nc21++;
					}
					dedge[nc1] /= nc21;

					if(pData->m_bSumEdgeData){
						pData->m_nPolarEdge[0]=dedge[nc1];
						pData->m_dLineEdgeData1[nCam][nc1] = dedge[nc1];
					}
					else{
						pData->m_nPolarEdge[0]=npos1;
						pData->m_dLineEdgeData1[nCam][nc1] = npos1;
					}

//					pData->m_dLineEdgeData1[nCam][nc1] = npos1;// i;
//					pData->m_dEdgeValue1[nCam][nc1] = nMax;// pData->m_nProjectX[nCam][i]-pData->m_nProjectX[nCam][i+4];
					pData->m_rtInspect[nCam][nRoiCount].right = npos1%CAM_WIDTH_CIS;//white end
					nRoiCount++;
					pData->m_rtInspect[nCam][nRoiCount].left = npos1%CAM_WIDTH_CIS;//black start
					
					nc1++;
					if(nc1==1)
						i+=nOffset1;
					else
						i+= nOffset2;

//					i+= nOffset;
					bAve=FALSE;
					nlinecount++;

				}
				if(nc1>=MAX_REALDEFECT-1) break;
				if(i>=nw-15){
					pData->m_rtInspect[nCam][nRoiCount].right = i%CAM_WIDTH_CIS;//white end
					nRoiCount++;
					break;
				}
			}
		}
		if(nCam==1 || nCam==2 ){
			//L -> R  Black ->White
			nEnd = 1;
			int nFlag1 = 0;
			int nend1 = nw-10;
//첫라인이 화이트 중앙인 경우 예외 처리 필요함.
			if(nCam==2)nend1 = nw-600;
			nMinLineWidth = nMinLineWidth1;
			for(int i=nEnd;i<nend1;i++){
				if(nCam==2 && nFlag1==0 &&i>1500){
					nMinLineWidth = pData->m_nMinLineWidth;
					nFlag1 = 1;
				}
				if(nc1>=MAX_REALDEFECT-1) break;
				if(pData->m_nProjectX[nCam][i+nGap1]>nWhitev1 && abs(pData->m_nProjectX[nCam][i]-pData->m_nProjectX[nCam][i+nGap1]) >= nEdgeth && abs(pData->m_nProjectX[nCam][i+1]-pData->m_nProjectX[nCam][i+nGap1+1]) >= nEdgeth )// &&(pData->m_nProjectX[nCam][i]>20 ||pData->m_nProjectX[nCam][i+4]>20))
				{
//					bAve==FALSE
					//밝기를 찾는다.
					//if(nlinecount>0 )
					{//&&  abs(i - pData->m_dLineEdgeData1[nCam][nlinecount-1]) < nMinLineWidth){
						if(nCam==1 && i+ngap2> nend1-nMinLineWidth*2)
							;
						else{
							for(int xx1=i+ngap2;xx1<i+nMinLineWidth;xx1++){//캄[라 처음과 끝은 스킵
								if(abs(pData->m_nProjectX[nCam][xx1]-pData->m_nProjectX[nCam][xx1+4]) >= nEdgeth)
								{
									nLineJump = 1;
								i= xx1+10;
									break;
								}
							}
						}

					}
					if(nLineJump==1){nLineJump = 0;continue;}

					pData->m_rectIns[nCam].left = i;bAve=TRUE;
					if(pData->m_nTacXpos[0]>0)pData->m_rectIns[nCam].left += pData->m_nTacXpos[0];
					////다시 에지가 가장 강한데를 찾는다.
					nMax = 0;
					for(int k=i-4;k<i+10;k++){
						if(k<10)k=10;if(k>=CAM_WIDTH_CIS-10)break;
						ntmp = abs(pData->m_nProjectX[nCam][k]-pData->m_nProjectX[nCam][k+2]);
						if(ntmp >= nMax){npos1 = k+nTol;	nMax = ntmp;}
					}
					int nc21 = 0;
					for(int k=0;k<CAM_HEIGHT_3072;k+=pData->m_nLineReduce){
						nmax1 = 0;
						for(int n1=npos1-4;n1<npos1+6;n1++){
							if( abs(*(fm+k*nw+n1) -  *(fm+k*nw+n1+2)) > nmax1){
								npos11 = n1+nTol;nmax1=abs(*(fm+k*nw+n1) -  *(fm+k*nw+n1+2));
							}
						}
						dedge[nc1] += npos11;
						nc21++;
					}
					dedge[nc1] /= nc21;
					if(nCam==2)
						nCam = nCam;


					if(pData->m_bSumEdgeData){
						pData->m_nPolarEdge[0]=dedge[nc1];
						pData->m_dLineEdgeData1[nCam][nc1] = dedge[nc1];
					}
					else{
						pData->m_nPolarEdge[0]=npos1;
						pData->m_dLineEdgeData1[nCam][nc1] = npos1;
					}

//					pData->m_nPolarEdge[0]=npos1;
//					pData->m_dLineEdgeData1[nCam][nc1] = npos1;
					pData->m_dEdgeValue1[nCam][nc1] = nMax;// pData->m_nProjectX[nCam][i]-pData->m_nProjectX[nCam][i+4];
					if(pData->m_nProjectX[nCam][i+1]>100 && nRoiCount==0){//white -> black
						pData->m_rtInspect[nCam][nRoiCount].left = 10;//white start
						pData->m_rtInspect[nCam][nRoiCount].right = npos1%CAM_WIDTH_CIS;//white end
						nRoiCount++;//1
						pData->m_rtInspect[nCam][nRoiCount].left = npos1%CAM_WIDTH_CIS;//black start
					}
					else if(pData->m_nProjectX[nCam][i+5]>100 && nRoiCount==0){//black->white
						nRoiCount=1;
						pData->m_rtInspect[nCam][nRoiCount].left = 10;//black start
						pData->m_rtInspect[nCam][nRoiCount].right = npos1%CAM_WIDTH_CIS;//black end
						nRoiCount++;//2
						pData->m_rtInspect[nCam][nRoiCount].left = npos1%CAM_WIDTH_CIS;//white start

					}
					else{
						pData->m_rtInspect[nCam][nRoiCount].right = npos1%CAM_WIDTH_CIS;//white start
						nRoiCount++;//4 6 8
						pData->m_rtInspect[nCam][nRoiCount].left = npos1%CAM_WIDTH_CIS;//white start

					}
					nc1++;
					if(nc1==1)
						i+=nOffset1;
					else
						i+= nOffset2;
					bAve=TRUE;
					if(nc1>=MAX_REALDEFECT-1) break;
					nlinecount++;
				}
				else if(/*bAve==TRUE && */pData->m_nProjectX[nCam][i+nGap1]<nWhitev1 && abs(pData->m_nProjectX[nCam][i]-pData->m_nProjectX[nCam][i+nGap1]) >= nEdgeth && abs(pData->m_nProjectX[nCam][i+1]-pData->m_nProjectX[nCam][i+nGap1+1]) >= nEdgeth/*&&(pData->m_nProjectX[nCam][i]>20 ||pData->m_nProjectX[nCam][i+4]>20 )*/)
				{
//					if(nlinecount>0 )
					{//&&  abs(i - pData->m_dLineEdgeData1[nCam][nlinecount-1]) < nMinLineWidth){
						for(int xx1=i+ngap2;xx1<i+nMinLineWidth;xx1++){
							if(abs(pData->m_nProjectX[nCam][xx1]-pData->m_nProjectX[nCam][xx1+4]) >= nEdgeth )
							{
								nLineJump = 1;
								i= xx1+10;
								break;
							}
						}
					}
					if(nLineJump==1){nLineJump = 0;continue;}

					nMax = 0;
					if(nc1>=MAX_REALDEFECT-1) break;
					for(int k=i-4;k<i+10;k++){
						if(k<10)k=10;if(k>=CAM_WIDTH_CIS-10)break;
						ntmp = abs(pData->m_nProjectX[nCam][k]-pData->m_nProjectX[nCam][k+2]);
						if(ntmp >= nMax){npos1 = k+nTol;	nMax = ntmp;}
					}
					int nc21 = 0;
					
					for(int k=0;k<CAM_HEIGHT_3072;k+=pData->m_nLineReduce){
						nmax1 = 0;
						for(int n1=npos1-4;n1<npos1+6;n1++){
							if(abs( *(fm+k*nw+n1) -  *(fm+k*nw+n1+2) )> nmax1){
								npos11 = n1+nTol;nmax1=abs(*(fm+k*nw+n1) -  *(fm+k*nw+n1+2));
							}
						}
						dedge[nc1] += npos11;
						nc21++;
					}
					dedge[nc1] /= nc21;
					if(nCam==2)
						nCam = nCam;

					if(pData->m_bSumEdgeData){
						pData->m_nPolarEdge[0]=dedge[nc1];
						pData->m_dLineEdgeData1[nCam][nc1] = dedge[nc1];
					}
					else{
						pData->m_nPolarEdge[0]=npos1;
						pData->m_dLineEdgeData1[nCam][nc1] = npos1;
					}

//					pData->m_dLineEdgeData1[nCam][nc1] = npos1;// i;
//					pData->m_dEdgeValue1[nCam][nc1] = nMax;// pData->m_nProjectX[nCam][i]-pData->m_nProjectX[nCam][i+4];
					pData->m_rtInspect[nCam][nRoiCount].right = npos1%CAM_WIDTH_CIS;//white end
					nRoiCount++;
					pData->m_rtInspect[nCam][nRoiCount].left = npos1%CAM_WIDTH_CIS;//black start
					nc1++;
					if(nc1==1)
						i+=nOffset1;
					else
						i+= nOffset2;
					bAve=FALSE;
					nlinecount++;
				}
				if(nc1>=MAX_REALDEFECT-1) break;
				if(i>=nw-15){
					pData->m_rtInspect[nCam][nRoiCount].right = i;//white end
					nRoiCount++;
					break;
				}
			}
		}
		if(nCam==1 && nc1<4)
			nc1 = nc1;
		if(nCam==0 && nc1 !=3)
			nc1 = nc1;
	}
		pData->m_nRoiDount[nCam] = nRoiCount;
	pData->m_nLineCount1[nCam] = nc1;//					pData->m_dLineEdgeData1[nCam][nc1] = npos1;
	return ntmp1;
}

int CInspect::GetSplitImgLineFind(CImage* pImage, CData* pData,int nCam,int nIdx,int nMod)//Edge detect, AverageBrightness, FullImageProfileData[x], ROI Set
{
	//defect count duration.
	unsigned char* fm = pImage->GetImagePtr();
	int nCount = 10;
	int nw = pImage->GetWidth();
	int nh = pImage->GetHeight();
	int nstt = 0,nend = nh;
	if( nIdx==0)
		nstt=0,nend = nh/nMod;
	else 
		nstt = (nh/nMod)*(nIdx),nend=(nh/nMod)*(nIdx+1); 

	int nindex = nIdx;
	int nh1 = nh/nMod;
	int x1 = pData->m_rectIns[0].left,x2= pData->m_rectIns[0].right;//검사영역
	CString str,str1;
	if(nIdx<0 || nh1<0 || nw<1 || x2-x1<5 || nend-nstt==0)return 0;

	int ntmp = 0,nmin=10000,nmax=0,ntmp1=0,ntmp2=0;
	double *dWidth1,*dWidth2,*dWidth3;
	dWidth1=(double*)malloc(nw*sizeof(double));//Split Image Projection Data
	dWidth2=(double*)malloc(nw*sizeof(double));//Projection Data Slope Value
	dWidth3=(double*)malloc(nw*sizeof(double));//Projection Data Slope Value
	for(int i=0;i<nw;i++) dWidth1[i]=dWidth2[i]=dWidth3[i]=0;

	int nIgnore = 4,nRisingV = 15;//pixel 이상은 제외시킨다.
	BOOL bFallingCheck = FALSE;

	x1 = 0;x2=CAM_WIDTH_CIS;

	//base projection data
	for(int y=nstt;y<nend;y++){
		for(int x=x1;x<x2;x++){
			dWidth1[x] += *(fm+y*nw+x);
		}
	}
	for(int x=x1;x<x2;x++)		dWidth1[x]/=(double(nend)-double(nstt));
	int nTol = pData->m_nGl4BlackValue1[nCam];//sparam4

	int nGap = 6,nGap1 = 32;//4pixel의 gap을 본다.
	int nX11 = x1+nGap1+1,nX22 = x2-nGap1*2;
	for(int x=x1+nGap;x<x2-nGap*2;x++){
		if(x>nX11 && x<nX22)
			dWidth2[x] = (dWidth1[x]-dWidth1[x-nGap1])+(dWidth1[x+nGap1]-dWidth1[x]);
		//		dWidth2[x] = ((dWidth1[x]-dWidth1[x-nGap]))*10;
		dWidth3[x] = ((dWidth1[x]-dWidth1[x-nGap])+(dWidth1[x]-dWidth1[x+nGap]))*10;
		//		str1.Format("scdata%d",nIdx);str.Format("%d , %.1f, %.1f , %.1f",x,dWidth1[x],dWidth2[x],dWidth3[x]);WriteLog(str1,str);Sleep(1);
	}
	BOOL bAve = FALSE;
	int nEdgeth = 18,nMax=0,nMin=255,npos1=0,npos2=0,nc1=0,nOffset=100;
	nEdgeth = pData->m_dThDn[nCam];
	int nBlackValue = 20;

	//main edge에서만 찾게 수정ㅎㄴ다.
	if(pData->m_strComName.Find("01")>=0){//좌측
		//L -> R  Black ->White
		for(int i=2500;i<nw-20;i++){
			if(bAve==FALSE && abs(dWidth1[i]-dWidth1[i+4]) >= nEdgeth){
				bAve=TRUE;
				////다시 에지가 가장 강한데를 찾는다.
				nMax = 0;
				for(int k=i-10;k<i+20;k++){
					if(k<5)k=5;if(k>=CAM_WIDTH_CIS)break;
					ntmp = abs(dWidth1[k]-dWidth1[k+2]);
					if(ntmp >= nMax){npos1 = k+nTol;	nMax = ntmp;}
				}
				if(nCam==0)
					nCam = 0;

//				pData->m_nPolarEdge[0]=npos1;
				pData->m_dLineEdgeData2[nCam][nIdx][nc1] = npos1;
				pData->m_dLineEdgeValue2[nCam][nIdx][nc1] = nMax;


				if(pData->m_bLineWrite)	for(int k=nstt;k<nstt+100;k++)*(fm+k*CAM_WIDTH_CIS+npos1) = *(fm+k*CAM_WIDTH_CIS+npos1-1) = *(fm+k*CAM_WIDTH_CIS+npos1+1) = 255;
				


				nc1++;
				i+= nOffset;

			}
			else if(bAve==TRUE && abs(dWidth1[i]-dWidth1[i+4]) >= nEdgeth ){
				nMax = 0;
				for(int k=i+100;k>i-10;k--){//흑에서 백을 찾는다.
					if(k<=5)k=10;if(k>=CAM_WIDTH_CIS)k=CAM_WIDTH_CIS-10;
					ntmp = abs(dWidth1[k]-dWidth1[k-2]);
					if(ntmp >= nMax){npos1 = k-nTol;	nMax = ntmp;}
				}

				ntmp1+=dWidth1[i];
				pData->m_dLineEdgeData2[nCam][nIdx][nc1] = npos1;
				pData->m_dLineEdgeValue2[nCam][nIdx][nc1] = nMax;
				if(pData->m_bLineWrite)	for(int k=nstt;k<nstt+100;k++)*(fm+k*CAM_WIDTH_CIS+npos1) = *(fm+k*CAM_WIDTH_CIS+npos1-1) = *(fm+k*CAM_WIDTH_CIS+npos1+1) = 255;
				i+= nOffset;
				nc1++;
				bAve=FALSE;

			}
			if(nc1>=MAX_REALDEFECT-1) break;
		}
	}
	else{//우측
		//L -> R  Black ->White
		for(int i=nw-2500;i>30;i--){
			if(bAve==FALSE && abs(dWidth1[i]-dWidth1[i-4]) >= nEdgeth){
				bAve=TRUE;
				nMax = 0;
				for(int k=i+10;k>i-20;k--){
					if(k<=5)break;if(k>=CAM_WIDTH_CIS)k=CAM_WIDTH_CIS-01;
					ntmp = abs(dWidth1[k]-dWidth1[k-2]);
					if(ntmp >= nMax){npos1 = k-nTol;	nMax = ntmp;}
				}

//				pData->m_nPolarEdge[0]= npos1;//i;
				pData->m_dLineEdgeData2[nCam][nIdx][nc1] = npos1;
				pData->m_dLineEdgeValue2[nCam][nIdx][nc1] = nMax;
				if(pData->m_bLineWrite)	for(int k=nstt;k<nstt+100;k++)*(fm+k*CAM_WIDTH_CIS+npos1) = *(fm+k*CAM_WIDTH_CIS+npos1-1) = *(fm+k*CAM_WIDTH_CIS+npos1+1) = 255;
				nc1++;
				i-= nOffset;

			}
			else if(bAve==TRUE && abs(dWidth1[i]-dWidth1[i-4]) >= nEdgeth){
				ntmp1+=dWidth1[i];

				nMax = 0;
				for(int k=i-100;k<i+10;k++){
					if(k<5)k=5;if(k>=CAM_WIDTH_CIS)break;
					ntmp = abs(dWidth1[k]-dWidth1[k+2]);
					if(ntmp >= nMax){npos1 = k+nTol;	nMax = ntmp;}
				}

				pData->m_dLineEdgeData2[nCam][nIdx][nc1] = npos1;
				pData->m_dLineEdgeValue2[nCam][nIdx][nc1] = nMax;
				if(pData->m_bLineWrite)	for(int k=nstt;k<nstt+100;k++)*(fm+k*CAM_WIDTH_CIS+npos1) = *(fm+k*CAM_WIDTH_CIS+npos1-1) = *(fm+k*CAM_WIDTH_CIS+npos1+1) = 255;

				i-= nOffset;
				nc1++;
				bAve=FALSE;

			}
			if(nc1>=MAX_REALDEFECT-1) break;
		}
	}
	pData->m_nLineEdgeCount1[nCam][nIdx]=nc1;


	//Image Write


	if(dWidth1) free(dWidth1);
	if(dWidth2) free(dWidth2);
	if(dWidth3) free(dWidth3);
	return 0;
}

void CInspect::GetLineDataSort(CImage* pImage, CData* pData,int nCam,int nFrame)
{
	//Condidate Peak Brightness Check //4x4 mesh 단위 불량 선별
	int nw = pData->m_nCameraWidth;
	int nh = pData->m_nCameraHeight;
	CRect rt;
	BYTE * fm = pImage->GetImagePtr();
	BOOL bColor[10],bping = FALSE;//False=white true=black
	int nMax = 0,nMin=0,nMax1 = 0,nMin1=0,nIndex = 0,npeak=0;
	int nMeshDefect = 0;
	int nVisionLine = pData->m_nVisionLine;
	pData->m_dAveRealBright[nCam] ;
	int nBright1 = 60;
	int nBright2 = 80;
	int nCandiCount1 = 0;//


	//Data Write & Edge Code Insert
 	for(int i=0;i<pData->m_nLineCount1[nCam] && i<MAX_REALDEFECT-1;i++){
 //class
//  		if(i==0){//edge
//  			pData->m_dLastEdge[nCam] = pData->m_dLineEdgeData1[nCam][i];//EDge 보정값을 넣기 위해 에지의 끝을 찾는다.
//  			if(nCam==0)				pData->fpDefectType[nCam][i] = LCLASS_TOP_EDGE;
//  			else							pData->fpDefectType[nCam][i] = LCLASS_BOTTOM_EDGE;
//  			
//  		}
//  		else if(i%2==0){//black->white
//  			if(nCam==0)				pData->fpDefectType[nCam][i] = LCLASS_TOP_BW;
//  			else							pData->fpDefectType[nCam][i] = LCLASS_BOTTOM_BW;
//  
//  		}
//  		else{//white->black
//  			if(nCam==0)				pData->fpDefectType[nCam][i] = LCLASS_TOP_WB;
//  			else							pData->fpDefectType[nCam][i] = LCLASS_BOTTOM_WB;
//  		}
//  		pData->m_fReturnX[nCam][i] = pData->m_dLineEdgeData1[nCam][i]*pData->m_dScaleFactorX[0];// + pData->m_dCalibSttX[nCam] ;//pos x
//  		
 	}

	double dave=0,dcnt=0,dtmp=0;
	int nMode = 2,minpos=0,maxpos=0;
	double dmin=0,dmax=0,dsortdata[MOD_COUNT];
	int nDataNo[MOD_COUNT];
	for(int o=0;o<MOD_COUNT;o++){
		dsortdata[o]=0;nDataNo[o] = 0;}
	int nCalPos = 0;
	double doffsetScale = pData->m_dScaleFactorX[nCam];
	if(nMode==1){

//		pData->m_dLineAverageData1[nCam][nFrame%5][i] = pData->m_dLineEdgeData1[nCam][i];//5장 평균을 구한다.
//			pData->m_fReturnX[nCam][i] = pData->m_dLineEdgeData1[nCam][i]*pData->m_dScaleFactorX[nCam] + pData->m_dCalibSttX[nCam] ;//pos x
	}
	else if(nMode==2){
	//edge count compare 
 		if(pData->m_nLineEdgeCount1[nCam][0] ==pData->m_nLineEdgeCount1[nCam][1] && pData->m_nLineEdgeCount1[nCam][0] ==pData->m_nLineEdgeCount1[nCam][2]&&pData->m_nLineEdgeCount1[nCam][0] ==pData->m_nLineEdgeCount1[nCam][3]){
//  			for(int i=0;i<pData->m_nLineEdgeCount1[nCam][0];i++){
//  				 dave = 0;
//  				 dmin=0,dmax=0;
//  				 for(int o=0;o<MOD_COUNT;o++)
//  					 dsortdata[o] = 0;
//  //data의 min을 찾는다.
//  				 for(int k=0;k<MOD_COUNT;k++){	
//  					 if(k==0){
//  						 dsortdata[k] =	pData->m_dLineEdgeData2[nCam][k][i];
//  					 }
//  					 else{
//  						 if(dsortdata[k-1] > pData->m_dLineEdgeData2[nCam][k][i]){
//  							 dsortdata[k] = dsortdata[k-1];
//  							 dsortdata[k-1] = pData->m_dLineEdgeData2[nCam][k][i];
//  
//  							 for(int h=k-1;h>0;h--){
//  								 if(dsortdata[h] > pData->m_dLineEdgeData2[nCam][k][i]){
//  									 dsortdata[h] = dsortdata[h-1];
//  									 dsortdata[h-1] = pData->m_dLineEdgeData2[nCam][k][i];
//  								 }
//  								 else
//  									 dsortdata[h] = pData->m_dLineEdgeData2[nCam][k][i];
//  							 }
//  						 }
//  						 else{
//  							dsortdata[k] = 	pData->m_dLineEdgeData2[nCam][k][i];	
//  						 }
//  					 }
//  				}
//  				 if(i==0){
//  					 for(int k=0;k<MOD_COUNT;k++){
//  						 if(dsortdata[k]==pData->m_dLineEdgeData2[nCam][k][i])
//  							 nDataNo[k] = k;
//  					 }
//  				 }
//  				 for(int k=2;k<MOD_COUNT-2;k++){	
//  					 dave+=	dsortdata[k];
//  				 }
// //			 폭에 대한 Data 정리
//  
//  //				dave += pData->m_dLineEdgeData1[nCam][i];
//  				pData->m_dLineEdgeData3[nCam][i]=(dave/(double)(MOD_COUNT-4));//짝수 Black->White 홀수White->Black
//  				//0912 kbh
//  				if(nCam==0 && pData->m_dLineEdgeData3[nCam][i]>3655 && pData->m_dLineEdgeData3[nCam][i]<3670)
//  					nCam = 0;
// //  				nCalPos = (dave/(double)(MOD_COUNT-4));
// //  				doffsetScale = pData->m_dCalXPos[nCam][nCalPos+1]-pData->m_dCalXPos[nCam][nCalPos];
// 				//0912 kbh 
// 			}
//////////////deffect data sort
			int nDefectCount1 = 0;
			double dx1,dy1,dsize;
			for(int ss=0;ss<8;ss++){
				if(nDefectCount1>=15)break;

				if(pData->m_nLineSlopeCount[nCam][ss]>=0){//라인 검출 불량
					if(nDefectCount1>=15)break;
					for(int kk=0;kk<pData->m_nLineSlopeCount[nCam][ss];kk++){
						CRect rtsc;
						rtsc = pData->m_rtLineSlopeCount[nCam][ss][kk]; //Y 축으로 3배 큰 이미지
						rtsc.InflateRect(0,128,0,-128);
						if( pData->m_rtLineSlopeCount[nCam][ss][kk].Width()<BAD_IMG_WIDTH)
							continue;
						pData->m_rectDefect[nCam][nDefectCount1] = rtsc;//pData->m_rtLineSlopeCount[nCam][ss][kk];//pData->m_rtThreadDefect[nCam][ss][kk];
						rtsc = pData->m_rtLineSlopeCount[nCam][ss][kk]; //Y 축으로 3배 큰 이미지
						pData->m_nDefectVMax[nCam][nDefectCount1] = pData->m_dLineEdgeValue2[nCam][ss][kk];


						//pData->m_nNewDefectColor[nCam][nDefectCount1] = 
//						ImageSelectCopy2(fm,pData->m_pImageDefect1[nCam][nDefectCount1]->GetImagePtr(),CAM_WIDTH_CIS,CAM_HEIGHT_CIS,pData->m_rectDefect[nCam][nDefectCount1].left,pData->m_rectDefect[nCam][nDefectCount1].right,pData->m_rectDefect[nCam][nDefectCount1].top,pData->m_rectDefect[nCam][nDefectCount1].bottom,BAD_IMG_WIDTH,BAD_IMG_HEIGHT,0,0);
						ImageSelectCopyScratch1(fm,pData->m_pImageDefect1[nCam][nDefectCount1]->GetImagePtr(),CAM_WIDTH_CIS,CAM_HEIGHT_CIS,rtsc,BAD_IMG_WIDTH,BAD_IMG_HEIGHT,0,0,3);
						pData->m_nNewDefectType[nCam][nDefectCount1] = pData->m_nNewLineColor[nCam][ss][kk]*100+1;//101;//무지라인 201코팅라인 1번더미
						double dsizex,dsizey,dsize;
						nDefectCount1++;
						pData->m_nRealDefectCount1[nCam]++;
						if(nDefectCount1>=15)break;
					}
				}
				if(pData->m_nThreadDefectCount[nCam][ss]>0){
					if(nDefectCount1>=15)break;
					for(int kk=0;kk<pData->m_nThreadDefectCount[nCam][ss];kk++){
						//
						pData->m_nDefectVMax[nCam][nDefectCount1] = pData->m_dLineEdgeValue2[nCam][ss][kk];
						pData->m_rectDefect[nCam][nDefectCount1] = pData->m_rtThreadDefect[nCam][ss][kk];
						CRect rtdefect1;
						rtdefect1 = pData->m_rectDefect[nCam][nDefectCount1];

						if(pData->m_nDefectMag>1){
							//ImageSelectCopy3(fm,pData->m_pImageDefect1[nCam][nDefectCount1]->GetImagePtr(),CAM_WIDTH_CIS,CAM_HEIGHT_CIS,pData->m_rectDefect[nCam][nDefectCount1].left,pData->m_rectDefect[nCam][nDefectCount1].right,pData->m_rectDefect[nCam][nDefectCount1].top,pData->m_rectDefect[nCam][nDefectCount1].bottom,BAD_IMG_WIDTH,BAD_IMG_HEIGHT,0,0,pData->m_nDefectMag);
							ImageSelectCopy4(pData,fm,pData->m_pImageDefect1[nCam][nDefectCount1]->GetImagePtr(),CAM_WIDTH_CIS,CAM_HEIGHT_CIS,pData->m_rectDefect[nCam][nDefectCount1].left,pData->m_rectDefect[nCam][nDefectCount1].right,pData->m_rectDefect[nCam][nDefectCount1].top,pData->m_rectDefect[nCam][nDefectCount1].bottom,BAD_IMG_WIDTH,BAD_IMG_HEIGHT,0,0,pData->m_nDefectMag,nCam);
						}
						else	ImageSelectCopy2(fm,pData->m_pImageDefect1[nCam][nDefectCount1]->GetImagePtr(),CAM_WIDTH_CIS,CAM_HEIGHT_CIS,pData->m_rectDefect[nCam][nDefectCount1].left,pData->m_rectDefect[nCam][nDefectCount1].right,pData->m_rectDefect[nCam][nDefectCount1].top,pData->m_rectDefect[nCam][nDefectCount1].bottom,BAD_IMG_WIDTH,BAD_IMG_HEIGHT,0,0);
						pData->m_nNewDefectType[nCam][nDefectCount1] = pData->m_nNewDefectColor[nCam][ss][kk]*1000+1;//1 init 1001Black	2001White	3001LineBlack	4001LineWhite
						if(pData->m_nNewDefectType[nCam][nDefectCount1]==1001){
							int nn1 = checkDragLine(pData,pData->m_pImageDefect1[nCam][nDefectCount1]->GetImagePtr());
							pData->m_nNewDefectType[nCam][nDefectCount1] += nn1;
						}
						else if(pData->m_nNewDefectType[nCam][nDefectCount1]==2001){//파임과 핀홀을 구분

						}
// 						if(pData->m_nNewDefectColor[nCam][ss][kk]==1)
// 							GetDefectSize(nCam,pData,pData->m_pImageDefect1[nCam][nDefectCount1]->GetImagePtr(),BAD_IMG_WIDTH,BAD_IMG_HEIGHT,1,pData->m_nThBlack3,&dx1,&dy1,&dsize);
// 						else
// 							GetDefectSize(nCam,pData,pData->m_pImageDefect1[nCam][nDefectCount1]->GetImagePtr(),BAD_IMG_WIDTH,BAD_IMG_HEIGHT,2,pData->m_nThWhite3,&dx1,&dy1,&dsize);
//						pData->m_dSize[nCam][nDefectCount1] = dsize;
						pData->m_dSizeX[nCam][nDefectCount1] = pData->m_rtThreadSizeDefect[nCam][ss][kk].Width() * pData->m_dScaleFactorX[nCam];
						pData->m_dSizeY[nCam][nDefectCount1] = pData->m_rtThreadSizeDefect[nCam][ss][kk].Height() * pData->m_dScaleFactorY[nCam];
						pData->m_dDefectValue1[nCam][nDefectCount1][0] = pData->m_dDefectValue[nCam][ss][kk][0];//0min 1max 2 average
						pData->m_dDefectValue1[nCam][nDefectCount1][1] = pData->m_dDefectValue[nCam][ss][kk][1];//0min 1max 2 average
						pData->m_dDefectValue1[nCam][nDefectCount1][2] = pData->m_dDefectValue[nCam][ss][kk][2];//0min 1max 2 average

//						pData->m_dSize[nCam][nDefectCount1] = pData->m_dSizeX[nCam][nDefectCount1] * 
						pData->m_dSize[nCam][nDefectCount1] = pData->m_dSizeX[nCam][nDefectCount1];
						if(pData->m_dSizeX[nCam][nDefectCount1]<pData->m_dSizeY[nCam][nDefectCount1])
							pData->m_dSize[nCam][nDefectCount1] = pData->m_dSizeY[nCam][nDefectCount1];
							
						if(pData->m_rtThreadSizeDefect[nCam][ss][kk].Width() >0 && pData->m_rtThreadSizeDefect[nCam][ss][kk].Height() >0 )//&& pData->m_rtThreadSizeDefect[nCam][ss][kk].Height()/pData->m_rtThreadSizeDefect[nCam][ss][kk].Width()>1 )
						{
							if(pData->m_dSizeY[nCam][nDefectCount1] > 2 && pData->m_dSizeY[nCam][nDefectCount1]/pData->m_dSizeX[nCam][nDefectCount1]>pData->m_dLineRatio){
								pData->m_nNewDefectType[nCam][nDefectCount1] = 3001;//pData->m_nNewDefectColor[nCam][ss][kk]*1000+1;//1 init 1001Black	2001White	3001LineBlack	4001LineWhite
									pData->m_dSize[nCam][nDefectCount1] = pData->m_dSizeX[nCam][nDefectCount1];
							}
							else{
								//불량 사이즈 구분
// 								pDoc->m_data.m_dSizeParam[0] = param3;////0 핀홀/에지덴트 1아일랜드/드레그라인 2라인 3드래그라인
								if(pData->m_nNewDefectType[nCam][nDefectCount1]==2001){//핀홀
									if(pData->m_dThSize[nCam]> pData->m_dSize[nCam][nDefectCount1]){
										//양품
										continue;
									}
								}
								else if(pData->m_nNewDefectType[nCam][nDefectCount1]==7001){//에지덴트
									if(pData->m_dThSize[nCam]> pData->m_dSize[nCam][nDefectCount1]){
										//양품
										continue;
									}
								}
								else if(pData->m_nNewDefectType[nCam][nDefectCount1]==1001){//아일랜드
									if(pData->m_dSizeParam[1]> pData->m_dSize[nCam][nDefectCount1]){
										//양품
										continue;
									}
								}
								else if(pData->m_nNewDefectType[nCam][nDefectCount1]==1002){//드래그라인
									if(pData->m_dSizeParam[1]> pData->m_dSize[nCam][nDefectCount1]){
										//양품
										continue;
									}
								}
								else{
									if(pData->m_dThSize[nCam]> pData->m_dSize[nCam][nDefectCount1]){
										//양품
										continue;
									}
								}
							}
						}
						else
							continue;

						nDefectCount1++;
						pData->m_nRealDefectCount1[nCam]++;
						if(nDefectCount1>=15)break;
					}
				}

			}

		}
	}
	return;
}

void CInspect::UpdateNGImage1(CImage *pImage, CData *pData,int nCam,CPoint pt,int nindex)
{
	if(nindex >= MAX_DEFECT)
		return;
	CRect rect;
	rect.left = rect.right = pt.x;
	rect.top = rect.bottom = pt.y;
	rect.InflateRect(BAD_IMG_WIDTH/2, BAD_IMG_HEIGHT/2);
	ValidRect(&rect,nCam,1);
	CopyBlockImg(pImage, rect, pData->m_pImageDefect[nCam][nindex],nCam);
}



int CInspect::GetSplitImgLineFind1(CImage* pImage, CData* pData,int nCam,int nIdx,int nMod)//Edge detect, AverageBrightness, FullImageProfileData[x], ROI Set
{
	//defect count duration.
	unsigned char* fm = pImage->GetImagePtr();
	int nCount = 10;
	int nw = pImage->GetWidth();
	int nh = pImage->GetHeight();
	int nstt = 0,nend = nh;
	if( nIdx==0)
		nstt=0,nend = nh/nMod;
	else 
		nstt = (nh/nMod)*(nIdx),nend=(nh/nMod)*(nIdx+1); 

	int nindex = nIdx;
	int nh1 = nh/nMod;
	int x1 = pData->m_rectIns[0].left,x2= CAM_WIDTH_CIS;//pData->m_rectIns[0].right;//검사영역
	CString str,str1;
	if(nIdx<0 || nh1<0 || nw<1 || x2-x1<5 || nend-nstt==0)return 0;

	int ntmp = 0,nmin=10000,nmax=0,ntmp1=0,ntmp2=0;
	double *dWidth1,*dWidth2,*dWidth3;
	int nProjData[CAM_HEIGHT_CIS]={0,};
	int nProjData1[CAM_HEIGHT_CIS]={0,};
	dWidth1=(double*)malloc(nw*sizeof(double));//Split Image Projection Data
	dWidth2=(double*)malloc(nw*sizeof(double));//Projection Data Slope Value
	dWidth3=(double*)malloc(nw*sizeof(double));//Projection Data Slope Value
	for(int i=0;i<nw;i++) dWidth1[i]=dWidth2[i]=dWidth3[i]=0;
	for(int i=0;i<CAM_HEIGHT_CIS;i++)nProjData[i]=nProjData1[i]=0;

	int nIgnore = 4,nRisingV = 15;//pixel 이상은 제외시킨다.
	BOOL bFallingCheck = FALSE;

	x1 = 0;x2=CAM_WIDTH_CIS;//CAM_WIDTH_16384;

	//base projection data
	for(int y=nstt;y<nend;y+=2){
		for(int x=x1;x<x2;x++){
			dWidth1[x] += *(fm+y*nw+x);
		}
	}
	for(int x=x1;x<x2;x++)		dWidth1[x]/=(double(nend)-double(nstt));//Line에 평균

	int nGap = 6,nGap1 = 32;//4pixel의 gap을 본다.
	int nX11 = x1+nGap1+1,nX22 = x2-nGap1*2;
	for(int x=x1+nGap;x<x2-nGap*2;x++){
		if(x>nX11 && x<nX22)
			dWidth2[x] = (dWidth1[x]-dWidth1[x-nGap1])+(dWidth1[x+nGap1]-dWidth1[x]);
		//		dWidth2[x] = ((dWidth1[x]-dWidth1[x-nGap]))*10;
		dWidth3[x] = ((dWidth1[x]-dWidth1[x-nGap])+(dWidth1[x]-dWidth1[x+nGap]))*10;
		//		str1.Format("scdata%d",nIdx);str.Format("%d , %.1f, %.1f , %.1f",x,dWidth1[x],dWidth2[x],dWidth3[x]);WriteLog(str1,str);Sleep(1);
	}
	BOOL bAve = FALSE;
	int nEdgeth = 18,nMax=0,nMin=255,npos1=0,npos2=0,nc1=0,nOffset=100;

	//main edge에서만 찾게 수정ㅎㄴ다.
	int nPosition1 = 0;
	int nTol = pData->m_nGl4BlackValue1[nCam];//sparam4
	CRect rttmp;
	int nOffset12 = 4,nmax1=0,nmax1pos=0;
	double dEdgeSlope = pData->m_dSlope;
	int nslopeCount = 0;
	int nCoatBright = pData->m_nCoatBright;


//	if(pData->m_strComName.Find("01")>=0){//좌측
	if(nCam==0 || nCam==1){//좌측
		//L -> R  Black ->White
		for(int m=0;m<pData->m_nLineCount1[nCam] && pData->m_nLineCount1[nCam]> 1;m++){
			if(pData->m_nKillFunction[nCam]==1)
				goto done;//return;
			nPosition1 = pData->m_dLineEdgeData1[nCam][m];
			nMax = 0;
			npos1 = nPosition1;
			if(bAve==FALSE){
				bAve=TRUE;
				for(int k=nPosition1-10;k<nPosition1+18;k++){
					if(k<10)k=10;if(k>=CAM_WIDTH_CIS*3-10)break;
					ntmp = abs(dWidth1[k]-dWidth1[k+2]);
					if(ntmp >= nMax){npos1 = k+nTol;	nMax = ntmp;}
				}
				if(nMax==0){
					pData->m_dLineEdgeData2[nCam][nIdx][nc1] = nPosition1;
//					pData->m_dLineEdgeValue2[nCam][nIdx][nc1] = nMax;

				}
				else{

					pData->m_dLineEdgeData2[nCam][nIdx][nc1] = npos1;
//					pData->m_dLineEdgeValue2[nCam][nIdx][nc1] = nMax;
				}
////////////////lineSlope 
				rttmp.SetRect(pData->m_dLineEdgeData2[nCam][nIdx][nc1]-50,nstt,pData->m_dLineEdgeData2[nCam][nIdx][nc1]+50,nend);
				rttmp=	SetBoundary1(rttmp,CRect(10,nstt,CAM_WIDTH_CIS,nend));	
				int nmax11=0,ncnt = 0;
				for(int yy = rttmp.top;yy<rttmp.bottom;yy++){
					nmax11=ncnt=0;
					for(int xx = rttmp.left;xx<rttmp.right-4;xx++){
						if(xx+nOffset12>=CAM_WIDTH_CIS)continue;
						if(abs(*(fm+yy*nw+xx) - *(fm+yy*nw+xx+nOffset12)) > nmax11){
							nmax11 = abs(*(fm+yy*nw+xx) - *(fm+yy*nw+xx+nOffset12));
							nmax1pos = xx+nOffset12;
							ncnt++;
						}
					}
					nProjData[yy] = nmax1pos;
					nProjData1[yy] = nmax11;
				}
				for(int yy = rttmp.top;yy<rttmp.bottom-4;yy++){
					if(nProjData[yy]>0 && nProjData[yy+3]>0 ){
						if(yy+3>=CAM_HEIGHT_CIS)continue;
						if(abs(pData->m_dLineEdgeData2[nCam][nIdx][nc1]-nProjData[yy] )> dEdgeSlope &&abs(pData->m_dLineEdgeData2[nCam][nIdx][nc1]-nProjData[yy+3] ) > dEdgeSlope && nProjData1[yy]<nCoatBright){
							//line 불량
							pData->m_rtLineSlopeCount[nCam][nIdx][nslopeCount].SetRect(nProjData[yy+3]-BAD_IMG_WIDTH*0.5,yy-BAD_IMG_WIDTH*0.5,nProjData[yy+3]+BAD_IMG_WIDTH*0.5,yy+BAD_IMG_WIDTH*0.5);
							pData->m_rtLineSlopeCount[nCam][nIdx][nslopeCount] = SetBoundary1(pData->m_rtLineSlopeCount[nCam][nIdx][nslopeCount],CRect(10,10,CAM_WIDTH_CIS-10,CAM_HEIGHT_CIS-10));
							pData->m_nNewLineColor[nCam][nIdx][nslopeCount] = 2;//코팅라인 black
							pData->m_dLineEdgeValue2[nCam][nIdx][nslopeCount] = abs(pData->m_dLineEdgeData2[nCam][nIdx][nc1]-nProjData[yy] );
							pData->m_nLineSlopeCount[nCam][nIdx]++;
							nslopeCount++;
							yy+=100;
						}

					}
				}
				for(int i=0;i<CAM_HEIGHT_CIS;i++)nProjData[i]=nProjData1[i]=0;

////////////////lineSlope
				if(pData->m_bLineWrite)	for(int k=nstt;k<nstt+100;k++)*(fm+k*CAM_WIDTH_CIS+npos1) = *(fm+k*CAM_WIDTH_CIS+npos1-1) = *(fm+k*CAM_WIDTH_CIS+npos1+1) = 255;
				nc1++;
			}
			else{
				bAve=FALSE;
				for(int k=nPosition1+100;k>nPosition1-10;k--){
					if(k<10)break;if(k>=CAM_WIDTH_CIS*3-10)k=CAM_WIDTH_CIS*3-10;

					ntmp = abs(dWidth1[k]-dWidth1[k-2]);
					if(ntmp >= nMax){npos1 = k-nTol;	nMax = ntmp;}
				}
				if(nMax==0){
					pData->m_dLineEdgeData2[nCam][nIdx][nc1] = nPosition1;
//					pData->m_dLineEdgeValue2[nCam][nIdx][nc1] = nMax;

				}
				else{

				pData->m_dLineEdgeData2[nCam][nIdx][nc1] = npos1;
//				pData->m_dLineEdgeValue2[nCam][nIdx][nc1] = nMax;
				}
				////////////////lineSlope
				rttmp.SetRect(pData->m_dLineEdgeData2[nCam][nIdx][nc1]-50,nstt,pData->m_dLineEdgeData2[nCam][nIdx][nc1]+50,nend);
				rttmp=	SetBoundary1(rttmp,CRect(10,nstt,CAM_WIDTH_CIS,nend));		
				int nmax11=0;
				for(int yy = rttmp.top;yy<rttmp.bottom;yy++){
					nmax11=0;
					for(int xx = rttmp.left;xx<rttmp.right-4;xx++){
						if(xx+nOffset12>=CAM_WIDTH_CIS)continue;
						if(abs(*(fm+yy*nw+xx) - *(fm+yy*nw+xx+nOffset12)) > nmax11){
							nmax11 = abs(*(fm+yy*nw+xx) - *(fm+yy*nw+xx+nOffset12));
							nmax1pos = xx+4;
						}
					}
					nProjData[yy] = nmax1pos;
					nProjData1[yy] = nmax11;
				}
				for(int yy = rttmp.top;yy<rttmp.bottom-4;yy++){
					if(nProjData[yy]>0 && nProjData[yy+3]>0 ){
						if(yy+3>=CAM_HEIGHT_CIS)continue;
						if(abs(pData->m_dLineEdgeData2[nCam][nIdx][nc1]-nProjData[yy] )> dEdgeSlope &&abs(pData->m_dLineEdgeData2[nCam][nIdx][nc1]-nProjData[yy+3] ) > dEdgeSlope && nProjData1[yy]>nCoatBright){							//line 불량
							//line 불량
							pData->m_rtLineSlopeCount[nCam][nIdx][nslopeCount].SetRect(nProjData[yy+3]-BAD_IMG_WIDTH*0.5,yy-BAD_IMG_WIDTH*0.5,nProjData[yy+3]+BAD_IMG_WIDTH*0.5,yy+BAD_IMG_WIDTH*0.5);
							pData->m_rtLineSlopeCount[nCam][nIdx][nslopeCount] = SetBoundary1(pData->m_rtLineSlopeCount[nCam][nIdx][nslopeCount],CRect(10,10,CAM_WIDTH_CIS-10,CAM_HEIGHT_CIS-10));
							pData->m_nNewLineColor[nCam][nIdx][nslopeCount] = 1;//코팅라인 white

							pData->m_dLineEdgeValue2[nCam][nIdx][nslopeCount] = abs(pData->m_dLineEdgeData2[nCam][nIdx][nc1]-nProjData[yy] );

							
							pData->m_nLineSlopeCount[nCam][nIdx]++;
							nslopeCount++;
							yy+=100;
						}

					}
				}
				for(int i=0;i<CAM_HEIGHT_CIS;i++)nProjData[i]=nProjData1[i]=0;

				////////////////lineSlope
				if(pData->m_bLineWrite)	for(int k=nstt;k<nstt+100;k++)*(fm+k*CAM_WIDTH_CIS+npos1) = *(fm+k*CAM_WIDTH_CIS+npos1-1) = *(fm+k*CAM_WIDTH_CIS+npos1+1) = 255;
				nc1++;
			}
			if(nCam==0 && nIdx==0 && pData->m_dLineEdgeData2[0][0][0]>3660 && pData->m_dLineEdgeData2[0][0][0]<3670)
				nCam = 0;

			if(pData->m_nKillFunction[nCam]==1)
				goto done;//return;

			if(nc1>=MAX_REALDEFECT-1) break;
		}
	}
	else{//우측

		for(int m=0;m<pData->m_nLineCount1[nCam];m++){
			if(pData->m_nKillFunction[nCam]==1)
				goto done;//return;

			nPosition1 = pData->m_dLineEdgeData1[nCam][m];
			nMax = 0;
			npos1 = nPosition1;
			if(bAve==FALSE){
				bAve=TRUE;
				for(int k=nPosition1+10;k>nPosition1-20;k--){
					if(k<10)break;if(k>=CAM_WIDTH_CIS-10)k=CAM_WIDTH_CIS-10;

					ntmp = abs(dWidth1[k]-dWidth1[k-2]);
					if(ntmp >= nMax){npos1 = k-nTol;	nMax = ntmp;}
				}
				if(nMax==0){
					pData->m_dLineEdgeData2[nCam][nIdx][nc1] = nPosition1;
//					pData->m_dLineEdgeValue2[nCam][nIdx][nc1] = nMax;

				}
				else{

				pData->m_dLineEdgeData2[nCam][nIdx][nc1] = npos1;
//				pData->m_dLineEdgeValue2[nCam][nIdx][nc1] = nMax;
				}
				////////////////lineSlope
				rttmp.SetRect(pData->m_dLineEdgeData2[nCam][nIdx][nc1]-50,nstt,pData->m_dLineEdgeData2[nCam][nIdx][nc1]+50,nend);
				rttmp=	SetBoundary1(rttmp,CRect(10,nstt,CAM_WIDTH_CIS,nend));	
				int nmax11=0;
				for(int yy = rttmp.top;yy<rttmp.bottom;yy++){
					nmax11=0;
					for(int xx = rttmp.left;xx<rttmp.right-4;xx++){
						if(xx+nOffset12>=CAM_WIDTH_CIS)continue;
						if(abs(*(fm+yy*nw+xx) - *(fm+yy*nw+xx+nOffset12)) > nmax11){
							nmax11 = abs(*(fm+yy*nw+xx) - *(fm+yy*nw+xx+nOffset12));
							nmax1pos = xx+4;
						}
					}
					nProjData[yy] = nmax1pos;
					nProjData1[yy] = nmax11;
				}
				for(int yy = rttmp.top;yy<rttmp.bottom-4;yy++){
					if(nProjData[yy]>0 && nProjData[yy+3]>0 ){
						if(yy+3>=CAM_HEIGHT_CIS)continue;
						if(abs(pData->m_dLineEdgeData2[nCam][nIdx][nc1]-nProjData[yy] )> dEdgeSlope &&abs(pData->m_dLineEdgeData2[nCam][nIdx][nc1]-nProjData[yy+3] ) > dEdgeSlope && nProjData1[yy]<nCoatBright){							//line 불량
							//line 불량
							pData->m_rtLineSlopeCount[nCam][nIdx][nslopeCount].SetRect(nProjData[yy+3]-BAD_IMG_WIDTH*0.5,yy-BAD_IMG_WIDTH*0.5,nProjData[yy+3]+BAD_IMG_WIDTH*0.5,yy+BAD_IMG_WIDTH*0.5);
							pData->m_rtLineSlopeCount[nCam][nIdx][nslopeCount] = SetBoundary1(pData->m_rtLineSlopeCount[nCam][nIdx][nslopeCount],CRect(10,10,CAM_WIDTH_CIS-10,CAM_HEIGHT_CIS-10));
							pData->m_nNewLineColor[nCam][nIdx][nslopeCount] = 2;//코팅라인 white
							pData->m_dLineEdgeValue2[nCam][nIdx][nslopeCount] = abs(pData->m_dLineEdgeData2[nCam][nIdx][nc1]-nProjData[yy] );
							pData->m_nLineSlopeCount[nCam][nIdx]++;
							nslopeCount++;
							yy+= 100;
						}

					}
				}
				for(int i=0;i<CAM_HEIGHT_CIS;i++)nProjData[i]=nProjData1[i]=0;

				////////////////lineSlope
				if(pData->m_bLineWrite)	for(int k=nstt;k<nstt+100;k++)*(fm+k*CAM_WIDTH_CIS+npos1) = *(fm+k*CAM_WIDTH_CIS+npos1-1) = *(fm+k*CAM_WIDTH_CIS+npos1+1) = 255;
				nc1++;
			}
			else{
				bAve=FALSE;
				for(int k=nPosition1-100;k<nPosition1+10;k++){
					if(k<10)k=10;if(k>=CAM_WIDTH_CIS-10)break;

					ntmp = abs(dWidth1[k]-dWidth1[k+2]);
					if(ntmp >= nMax){npos1 = k+nTol;	nMax = ntmp;}
				}
				if(nMax==0){
					pData->m_dLineEdgeData2[nCam][nIdx][nc1] = nPosition1;
//					pData->m_dLineEdgeValue2[nCam][nIdx][nc1] = nMax;

				}
				else{
				pData->m_dLineEdgeData2[nCam][nIdx][nc1] = npos1;
//				pData->m_dLineEdgeValue2[nCam][nIdx][nc1] = nMax;
				}
				////////////////lineSlope
				rttmp.SetRect(pData->m_dLineEdgeData2[nCam][nIdx][nc1]-50,nstt,pData->m_dLineEdgeData2[nCam][nIdx][nc1]+50,nend);
				rttmp=	SetBoundary1(rttmp,CRect(10,nstt,CAM_WIDTH_CIS,nend));	
				int nmax11 = 0;
				for(int yy = rttmp.top;yy<rttmp.bottom;yy++){
					nmax11=0;
					for(int xx = rttmp.left;xx<rttmp.right-4;xx++){
						if(xx+nOffset12>=CAM_WIDTH_CIS)continue;
						if(abs(*(fm+yy*nw+xx) - *(fm+yy*nw+xx+nOffset12)) > nmax11){
							nmax11 = abs(*(fm+yy*nw+xx) - *(fm+yy*nw+xx+nOffset12));
							nmax1pos = xx+4;
						}
					}
					nProjData[yy] = nmax1pos;
					nProjData1[yy] = nmax11;
				}
				for(int yy = rttmp.top;yy<rttmp.bottom-4;yy++){
					if(nProjData[yy]>0 && nProjData[yy+3]>0 ){
						if(yy+3>=CAM_HEIGHT_CIS)continue;
						if(abs(pData->m_dLineEdgeData2[nCam][nIdx][nc1]-nProjData[yy] )> dEdgeSlope &&abs(pData->m_dLineEdgeData2[nCam][nIdx][nc1]-nProjData[yy+3] ) > dEdgeSlope && nProjData1[yy]>20){							//line 불량
							//line 불량
							pData->m_rtLineSlopeCount[nCam][nIdx][nslopeCount].SetRect(nProjData[yy+3]-BAD_IMG_WIDTH*0.5,yy-BAD_IMG_WIDTH*0.5,nProjData[yy+3]+BAD_IMG_WIDTH*0.5,yy+BAD_IMG_WIDTH*0.5);
							pData->m_rtLineSlopeCount[nCam][nIdx][nslopeCount] = SetBoundary1(pData->m_rtLineSlopeCount[nCam][nIdx][nslopeCount],CRect(10,10,CAM_WIDTH_CIS-10,CAM_HEIGHT_CIS-10));
							pData->m_nNewLineColor[nCam][nIdx][nslopeCount] = 1;//코팅라인 white
							pData->m_dLineEdgeValue2[nCam][nIdx][nslopeCount] = abs(pData->m_dLineEdgeData2[nCam][nIdx][nc1]-nProjData[yy] );

							pData->m_nLineSlopeCount[nCam][nIdx]++;
							nslopeCount++;
							yy+=100;
						}

					}
				}
				for(int i=0;i<CAM_HEIGHT_CIS;i++)nProjData[i]=nProjData1[i]=0;

				////////////////lineSlope
				if(pData->m_bLineWrite)	for(int k=nstt;k<nstt+100;k++)*(fm+k*CAM_WIDTH_CIS+npos1) = *(fm+k*CAM_WIDTH_CIS+npos1-1) = *(fm+k*CAM_WIDTH_CIS+npos1+1) = 255;
				nc1++;
			}
			if(pData->m_nKillFunction[nCam]==1)
				goto done;//return;

			if(nc1>=MAX_REALDEFECT-1) break;
		}
	}

done:
	pData->m_nLineEdgeCount1[nCam][nIdx]=nc1;
	if(dWidth1) free(dWidth1);
	if(dWidth2) free(dWidth2);
	if(dWidth3) free(dWidth3);
	return 0;
}


int CInspect::GetSplitImgRoiFind(CImage* pImage, CData* pData,int nCam,int nIdx,int nMod)//Edge detect, AverageBrightness, FullImageProfileData[x], ROI Set
{
	//defect count duration.
	unsigned char* fm = pImage->GetImagePtr();
	int nCount = 10;
	int nw = pImage->GetWidth();
	int nh = pImage->GetHeight();
	int nstt = 0,nend = nh;
	if( nIdx==0)
		nstt=0,nend = nh/nMod;
	else 
		nstt = (nh/nMod)*(nIdx),nend=(nh/nMod)*(nIdx+1); 

	CRect rtInspect[40];
	for(int i=0;i<40;i++){
		rtInspect[i] = pData->m_rtInspect[nCam][i];
		rtInspect[i] = pData->m_rtInspect1[nCam][nIdx][i];
	}
	int nroicnt = pData->m_nLineCount1[nCam];//m_nRoiDount[nCam];
	BOOL bScratch = FALSE;

	int nindex = nIdx;
	int nh1 = nh/nMod;
	int x1 = 0,x2= 0;//검사영역
//	int x1 = pData->m_rectIns[0].left,x2= pData->m_rectIns[0].right;//검사영역
	CString str,str1;
	if(nIdx<0 || nh1<0 || nw<1  || nend-nstt==0)
		return 0;

	int ntmp = 0,nmin=10000,nmax=0,ntmp1=0,ntmp2=0;
	double *dWidth1;
	double *dWidth2;
	dWidth1=(double*)malloc(nw*sizeof(double));//Split Image Projection Data
	dWidth2=(double*)malloc(nw*sizeof(double));//Split Image Projection Data
	for(int i=0;i<nw;i++) dWidth1[i]=dWidth2[i]=0;

	int nIgnore = 4,nRisingV = 15;//pixel 이상은 제외시킨다.
	BOOL bFallingCheck = FALSE;
	double dcount11 = 0;
	x1 = 0;x2=CAM_WIDTH_CIS;//CAM_WIDTH_16384;

	//base projection data
	for(int y=nstt;y<nend;y+=2){
		for(int x=x1;x<x2;x++){
			dWidth1[x] += *(fm+y*nw+x);
			if(bScratch)
				dWidth2[x] += *(m_fmPreprocess[nCam]+y*nw+x);			
		}
		dcount11++;
	}
//	;
	for(int x=x1;x<x2;x++)	{
		dWidth1[x]/=dcount11;
		if(bScratch)
			dWidth2[x]/=dcount11;
	}

	int nGap = 6,nGap1 = 32;//4pixel의 gap을 본다.
	int nX11 = x1+nGap1+1,nX22 = x2-nGap1*2;
	BOOL bAve = FALSE;
	int nEdgeth = 18,nMax=0,nMin=255,npos1=0,npos2=0,nc1=0,nOffset=100;

	//main edge에서만 찾게 수정ㅎㄴ다.
	int nPosition1 = 0;
	int nTol = pData->m_nGl4BlackValue1[nCam];//sparam4
	int nWth1 = 50;//백->백
	int nWth2 = pData->m_nThBlack3;//백-흑
	int nBth1 = pData->m_nThWhite3;//흑-백
	int nBth2 = 50;//흑-흑
	CPoint ptDefect[50];
	int nDefect = 0,nPeak1=0,nPeak2=0,nAverage=0;
	CRect rtdefect[50],rtsize[50];
	int defectx = BAD_IMG_WIDTH*0.5;
	int defecty = BAD_IMG_HEIGHT*0.5;
	CRect rtPos[40];
	for(int i=0;i<40;i++)
		rtPos[i].SetRect(0,0,0,0);
	int nJump = 0;
	double dParamScratch = pData->m_dLineScratch;//라인

	double dscalex = pData->m_dScaleFactorX[0],dscaley = pData->m_dScaleFactorY[0];
	double dPeakData[10] = {0,};//0 라인 1 코팅 백 2코팅흑 3 무지백 4 무지흑
	dPeakData[3] =dPeakData[1] = 255;

//roi별 검사
	int nbwcheck = 0;//0 coating 1 nulling
	int nSelectBright = 180;//무지인지 코팅인지 확인  밝기가 올가가거나 낮아질경우 문제 발생 소지 있음.
	if(pData->m_dAvgBrightness[nCam]>100)
		nSelectBright = 220;
	else if(pData->m_dAvgBrightness[nCam]>50)
		nSelectBright = 180;
	else if(pData->m_dAvgBrightness[nCam]>30)
		nSelectBright = 150;
	else 
		nSelectBright = 100;
	if(nCam==2)
		nCam = nCam;
	bool bcoat = FALSE;//false 무지 true 코팅
	for(int k=0;k<nroicnt;k++){
		if(nDefect>=14)		break;
		if(rtInspect[k].Width()<60)continue;
		for(int y=nstt;y<nend;y+=2){
			if(nDefect>=14)		break;
			nJump = 0;
			for(int x = rtInspect[k].left;x<rtInspect[k].right-4;x++){//roi 만큼만
				if(x<5 || x> CAM_WIDTH_CIS-10)continue;
				if(y<0 || y> CAM_HEIGHT_CIS-1)continue;
				if(pData->m_nKillFunction[nCam]==1)
					goto done;//return;
				if(x==rtInspect[k].left && x+8 <rtInspect[k].right-4){

					if((pData->m_nProjectX[nCam][x] + pData->m_nProjectX[nCam][x+4]+pData->m_nProjectX[nCam][x+8])*0.33>nSelectBright )
						nbwcheck=1;//무지면
					else
						nbwcheck = 0;//@@chcho 191031 1로 되어 있는거 수정  //코팅면
				}
//				ntmp = dWidth1[x]-*(fm+y*nw+x);//
				ntmp = pData->m_nProjectX[nCam][x]-*(fm+y*nw+x);//전체 프로파일 데이터를 사용한다.
				if(nCam==2 && k==1){
					if(x>2450 && x<2460 && y>=0 && y<2)
					x= x;
				}
				//sc 검사 먼저
				if(bScratch){
					if( y==nstt && x <rtInspect[k].right && fabs(dWidth1[x]-dWidth1[x+4]) > dPeakData[0])dPeakData[0] = fabs(dWidth1[x]-dWidth1[x+4]);
					if(	nbwcheck==1){//화이트검사 무지부 //흑만 검색  음수값//백색 불량
						if(ntmp<dPeakData[3])dPeakData[3] = ntmp;//코팅백
						if(ntmp>dPeakData[4])dPeakData[4] = ntmp;//코팅흑
					}
					else{
						if(ntmp<dPeakData[1])dPeakData[1] = ntmp;//코팅백
						if(ntmp>dPeakData[2])dPeakData[2] = ntmp;//코팅흑

					}
				}


//				if(!pData->m_bPreprocessing && nbwcheck==0 &&dWidth1[x+4] <rtInspect[k].right &&        fabs(dWidth1[x]-dWidth1[x+4]) > dParamScratch){
				if(bScratch && !pData->m_bPreprocessing && nbwcheck==0 && y==nstt && x <rtInspect[k].right &&        fabs(dWidth1[x]-dWidth1[x+4]) > dParamScratch){
					for(int nn=0;nn<nDefect;nn++){
						if(x>rtPos[nn].left && x<rtPos[nn].right && y>rtPos[nn].top&& y<rtPos[nn].bottom){
							nJump = 1;
							if(nJump){
								x+= 64;
								break;;
							}
						}
					}
					if(nJump==1)continue;

//					rtdefect[nDefect].SetRect(x-defectx,y-defecty,x+defectx,y+defecty);
					rtdefect[nDefect].SetRect(x-defectx,nstt,x+defectx,nend);//Line 불량 Y 라인 축소
					pData->m_dLineEdgeValue2[nCam][nIdx][nDefect] = fabs(dWidth2[x]-dWidth2[x+4]);
					CRect rttmp;
					rttmp = rtdefect[nDefect];
					rtdefect[nDefect] = SetBoundary1(rtdefect[nDefect],CRect(rtInspect[k].left,1,rtInspect[k].right,CAM_HEIGHT_CIS-1));
						//							ImageSelect	Copy2(pImage->GetImagePtr(),pData->m_pImageDefect1[nCam][nDefect]->GetImagePtr(),CAM_WIDTH_CIS,CAM_HEIGHT_CIS,rttmp.left,rttmp.right,rttmp.top,rttmp.bottom,BAD_IMG_WIDTH,BAD_IMG_HEIGHT,0,0);
						pData->m_rtThreadDefect[nCam][nIdx][nDefect] = rtdefect[nDefect];
						pData->m_nNewDefectColor[nCam][nIdx][nDefect] = 2;//코팅라인 white
						pData->m_nNewLineColor[nCam][nIdx][nDefect] = 2;
						pData->m_rtLineSlopeCount[nCam][nIdx][nDefect] = rtdefect[nDefect];
						pData->m_nLineSlopeCount[nCam][nIdx]++;

						rtPos[nDefect] = rtdefect[nDefect];
						rtPos[nDefect].InflateRect(64,128);
						nDefect++;
//					}
					x+= 64;
				}
				else if(bScratch && pData->m_bPreprocessing && y==nstt && x <rtInspect[k].right &&        fabs(dWidth2[x]-dWidth2[x+4]) > dParamScratch){
					if(nbwcheck==1 && x >= rtInspect[k].right-5)
						continue;
					for(int nn=0;nn<nDefect;nn++){
						if(x>rtPos[nn].left && x<rtPos[nn].right && y>rtPos[nn].top&& y<rtPos[nn].bottom){
							nJump = 1;
							if(nJump){
								x+= 64;
								break;;
							}
						}
					}
					if(nJump==1)
						continue;

					//					rtdefect[nDefect].SetRect(x-defectx,y-defecty,x+defectx,y+defecty);
					rtdefect[nDefect].SetRect(x-defectx,nstt,x+defectx,nend);//Line 불량 Y 라인 축소
					pData->m_dLineEdgeValue2[nCam][nIdx][nDefect] = fabs(dWidth2[x]-dWidth2[x+4]);

					CRect rttmp;
					rttmp = rtdefect[nDefect];
					rtdefect[nDefect] = SetBoundary1(rtdefect[nDefect],CRect(rtInspect[k].left-50,1,rtInspect[k].right+50,CAM_HEIGHT_CIS-1));
					//							ImageSelect	Copy2(pImage->GetImagePtr(),pData->m_pImageDefect1[nCam][nDefect]->GetImagePtr(),CAM_WIDTH_CIS,CAM_HEIGHT_CIS,rttmp.left,rttmp.right,rttmp.top,rttmp.bottom,BAD_IMG_WIDTH,BAD_IMG_HEIGHT,0,0);
					pData->m_rtThreadDefect[nCam][nIdx][nDefect] = rtdefect[nDefect];
					pData->m_nNewDefectColor[nCam][nIdx][nDefect] = 2;//코팅라인 white
					pData->m_nNewLineColor[nCam][nIdx][nDefect] = 2;
					pData->m_rtLineSlopeCount[nCam][nIdx][nDefect] = rtdefect[nDefect];
					pData->m_nLineSlopeCount[nCam][nIdx]++;

					rtPos[nDefect] = rtdefect[nDefect];
					rtPos[nDefect].InflateRect(64,128);
					nDefect++;
					//					}
					x+= 64;
				}
				else if(nbwcheck==1){//화이트검사 무지부 //흑만 검색  음수값
					if(ntmp < -nWth1){//백색 불량
// 						rtdefect[nDefect].SetRect(x-defectx,y-defecty,x+defectx,y+defecty);
// 						rtdefect[nDefect] = SetBoundary1(rtdefect[nDefect],CRect(rtInspect[k].left,1,rtInspect[k].right,CAM_HEIGHT_CIS-1));
// //						rtsize[nDefect] = CheckDefect1(nCam,fm,pData,rtdefect[nDefect],nDefect,0,1,nWth1,&nPeak1,&nPeak2,&nAverage);//npos 0 무지 1코팅
// 						rtsize[nDefect] = CheckDefect2(nCam,pImage->GetImagePtr(),pData,rtdefect[nDefect].left,rtdefect[nDefect].right,rtdefect[nDefect].top,rtdefect[nDefect].bottom,nIdx,nDefect,0,1,nWth1,&nPeak1,&nPeak2,&nAverage);//npos 0 무지 1코팅
// 						nDefect++;
						
					}
					else if(ntmp > nWth2){//흑색 불량
						for(int nn=0;nn<nDefect;nn++){
							if(x>rtPos[nn].left && x<rtPos[nn].right && y>rtPos[nn].top&& y<rtPos[nn].bottom){
								nJump = 1;
								if(nJump){
									x+= 64;
									break;;
								}
							}
						}
						if(nJump==1)continue;
						rtdefect[nDefect].SetRect(x-defectx,y-defecty,x+defectx,y+defecty);
						CRect rttmp;
						rttmp = rtdefect[nDefect];

						rttmp = SetBoundary1(rttmp,m_rtBound);
						pData->m_dLineEdgeValue2[nCam][nIdx][nDefect] = abs(ntmp);


						rtdefect[nDefect] = SetBoundary1(rtdefect[nDefect],CRect(rtInspect[k].left,1,rtInspect[k].right,CAM_HEIGHT_CIS-1));
//						rtsize[nDefect] = CheckDefect1(nCam,fm,pData,rtdefect[nDefect],nDefect,0,0,nWth2,&nPeak1,&nPeak2,&nAverage);//npos 0 무지 1코팅
						rtsize[nDefect] = CheckDefect2(nCam,pImage->GetImagePtr(),pData,rtdefect[nDefect].left,rtdefect[nDefect].right,rtdefect[nDefect].top,rtdefect[nDefect].bottom,nIdx,nDefect,0,0,nWth2,&nPeak1,&nPeak2,&nAverage);//npos 0 무지 1코팅
						if(rtInspect[k].left>rttmp.left||rtInspect[k].right<rttmp.right)rtdefect[nDefect] = rttmp;
						if((rtsize[nDefect].Width()+1)*dscalex>pData->m_dThSize[0] || (rtsize[nDefect].Height()+1)*dscaley>pData->m_dThSize[0]){
//							ImageSelectCopy2(pImage->GetImagePtr(),pData->m_pImageDefect1[nCam][nDefect]->GetImagePtr(),CAM_WIDTH_CIS,CAM_HEIGHT_CIS,rttmp.left,rttmp.right,rttmp.top,rttmp.bottom,BAD_IMG_WIDTH,BAD_IMG_HEIGHT,0,0);
							pData->m_rtThreadDefect[nCam][nIdx][nDefect] = rtdefect[nDefect];
							pData->m_rtThreadSizeDefect[nCam][nIdx][nDefect] = rtsize[nDefect];
							pData->m_nNewDefectColor[nCam][nIdx][nDefect] = 1;////0 init 1Black	2White	3LineBlack	4LineWhite
							pData->m_nThreadDefectCount[nCam][nIdx]++;
							rtPos[nDefect] = rtdefect[nDefect];
							nDefect++;
						}
						x+= 64;
					}
				}
				else{//블랙검사 코팅명 //백색검출
					if(ntmp < -nBth1){//백색불량
						for(int nn=0;nn<nDefect;nn++){
							if(x>rtPos[nn].left && x<rtPos[nn].right && y>rtPos[nn].top&& y<rtPos[nn].bottom){
								nJump = 1;
								if(nJump){
									x+= 64;
									break;
								}
							}
						}
						if(nJump==1)continue;
						CRect rttmp;
						pData->m_dLineEdgeValue2[nCam][nIdx][nDefect] = abs(ntmp);
						rtdefect[nDefect].SetRect(x-defectx,y-defecty,x+defectx,y+defecty);
						rttmp = rtdefect[nDefect];
						rtdefect[nDefect] = SetBoundary1(rtdefect[nDefect],CRect(rtInspect[k].left,1,rtInspect[k].right,CAM_HEIGHT_CIS-1));
//						rtsize[nDefect] = CheckDefect1(nCam,fm,pData,rtdefect[nDefect],nDefect,1,1,nBth1,&nPeak1,&nPeak2,&nAverage);//npos 0 무지 1코팅
						rtsize[nDefect] = CheckDefect2(nCam,pImage->GetImagePtr(),pData,rtdefect[nDefect].left,rtdefect[nDefect].right,rtdefect[nDefect].top,rtdefect[nDefect].bottom,nIdx,nDefect,1,1,nBth1,&nPeak1,&nPeak2,&nAverage);//npos 0 무지 1코팅
						if(rtsize[nDefect].Width()<=0 || rtsize[nDefect].Height()<=0){
							x+=64;continue;
						}
						if(rtInspect[k].left>rttmp.left||rtInspect[k].right<rttmp.right)rtdefect[nDefect] = rttmp;
						if((rtsize[nDefect].Width())*dscalex>pData->m_dThSize[0] || (rtsize[nDefect].Height())*dscaley>pData->m_dThSize[0]){
//							ImageSelectCopy2(pImage->GetImagePtr(),pData->m_pImageDefect1[nCam][nDefect]->GetImagePtr(),CAM_WIDTH_CIS,CAM_HEIGHT_CIS,rttmp.left,rttmp.right,rttmp.top,rttmp.bottom,BAD_IMG_WIDTH,BAD_IMG_HEIGHT,0,0);
							pData->m_rtThreadDefect[nCam][nIdx][nDefect] = rtdefect[nDefect];
							pData->m_rtThreadSizeDefect[nCam][nIdx][nDefect] = rtsize[nDefect];
							pData->m_nNewDefectColor[nCam][nIdx][nDefect] = 2;////0 init 1Black	2White	3LineBlack	4LineWhite
							pData->m_dDefectValue[nCam][nIdx][nDefect][0] = nPeak1;//min
							pData->m_dDefectValue[nCam][nIdx][nDefect][1] = nPeak2;//max
							pData->m_dDefectValue[nCam][nIdx][nDefect][2] = nAverage;//max

							//edge spur edge dent
							if((rtdefect[nDefect].left+rtsize[nDefect].left <rtInspect[k].left && rtdefect[nDefect].left+rtsize[nDefect].right <rtInspect[k].left) ||
								(rtdefect[nDefect].left+rtsize[nDefect].left >rtInspect[k].right && rtdefect[nDefect].left+rtsize[nDefect].right >rtInspect[k].right))
								pData->m_nNewDefectColor[nCam][nIdx][nDefect] = 7;////0 init 1Black	2White	3LineBlack	4LineWhite
							pData->m_nThreadDefectCount[nCam][nIdx]++;

							rtPos[nDefect] = rtdefect[nDefect];
							nDefect++;
						}
						x+= 64;
					}
					else if(ntmp > nBth2){//black defect
						for(int nn=0;nn<nDefect;nn++){
							if(x>rtPos[nn].left && x<rtPos[nn].right && y>rtPos[nn].top&& y<rtPos[nn].bottom){
								nJump = 1;
								if(nJump){
									x+= 64;
									break;
								}
							}
						}
						if(nJump==1)continue;
						CRect rttmp;
						pData->m_dLineEdgeValue2[nCam][nIdx][nDefect] = abs(ntmp);
						rtdefect[nDefect].SetRect(x-defectx,y-defecty,x+defectx,y+defecty);
						rttmp = rtdefect[nDefect];
						rtdefect[nDefect] = SetBoundary1(rtdefect[nDefect],CRect(rtInspect[k].left,1,rtInspect[k].right,CAM_HEIGHT_CIS-1));
						//						rtsize[nDefect] = CheckDefect1(nCam,fm,pData,rtdefect[nDefect],nDefect,1,1,nBth1,&nPeak1,&nPeak2,&nAverage);//npos 0 무지 1코팅
						rtsize[nDefect] = CheckDefect2(nCam,pImage->GetImagePtr(),pData,rtdefect[nDefect].left,rtdefect[nDefect].right,rtdefect[nDefect].top,rtdefect[nDefect].bottom,nIdx,nDefect,1,1,nBth1,&nPeak1,&nPeak2,&nAverage);//npos 0 무지 1코팅
						if(rtsize[nDefect].Width()<=0 || rtsize[nDefect].Height()<=0){
							x+=64;continue;
						}
						if(rtInspect[k].left>rttmp.left||rtInspect[k].right<rttmp.right)rtdefect[nDefect] = rttmp;
						if((rtsize[nDefect].Width())*dscalex>pData->m_dThSize[0] || (rtsize[nDefect].Height())*dscaley>pData->m_dThSize[0]){
							//							ImageSelectCopy2(pImage->GetImagePtr(),pData->m_pImageDefect1[nCam][nDefect]->GetImagePtr(),CAM_WIDTH_CIS,CAM_HEIGHT_CIS,rttmp.left,rttmp.right,rttmp.top,rttmp.bottom,BAD_IMG_WIDTH,BAD_IMG_HEIGHT,0,0);
							pData->m_rtThreadDefect[nCam][nIdx][nDefect] = rtdefect[nDefect];
							pData->m_rtThreadSizeDefect[nCam][nIdx][nDefect] = rtsize[nDefect];
							pData->m_dDefectValue[nCam][nIdx][nDefect][0] = nPeak1;//min
							pData->m_dDefectValue[nCam][nIdx][nDefect][1] = nPeak2;//max
							pData->m_dDefectValue[nCam][nIdx][nDefect][2] = nAverage;//max
							pData->m_nNewDefectColor[nCam][nIdx][nDefect] = 1;////0 init 1Black	2White	3LineBlack	4LineWhite
							pData->m_nThreadDefectCount[nCam][nIdx]++;

							rtPos[nDefect] = rtdefect[nDefect];
							nDefect++;
						}
						x+= 64;
					}
				}
				if(nDefect>=14)			break;
				if(pData->m_nKillFunction[nCam]==1)
					goto done;//return;
			}
			if(nDefect>=14)		break;
		}
		if(nDefect>=14)		break;
	}
done:
	for(int i=0;i<5;i++)
		pData->m_dAverageData1[nCam][nIdx][i] = dPeakData[i];
	if(dWidth1) free(dWidth1);
	if(dWidth2) free(dWidth2);
	return 0;
}
//사이즈 value 리턴

CRect CInspect::CheckDefect2(int nCam,BYTE* fmsrc,CData *pData,int l,int r,int t,int b,int nIdx,int ndefectcnt,int nPos,BOOL bColor,int nTh1,int *nPeakb,int *nPeakw,int *nave1)//npos 0 무지 1코팅
{
	CRect rtsize,rtDefect;
	rtDefect.SetRect(l,t,r,b);
	rtsize.SetRect(0,0,0,0);
	int nIndex = nIdx;//pData->m_nRealDefectCount;
	BYTE * fmdefect = new BYTE[BAD_IMG_WIDTH*BAD_IMG_HEIGHT];//pData->m_pImageDefect[0][nIdx]->GetImagePtr();//new BYTE[BAD_IMG_WIDTH*BAD_IMG_HEIGHT];
	memset(fmdefect,0,BAD_IMG_WIDTH*BAD_IMG_HEIGHT);
	unsigned char* fmtmp1 =	new BYTE[BAD_IMG_WIDTH*BAD_IMG_HEIGHT];
	memset(fmtmp1,0,BAD_IMG_WIDTH*BAD_IMG_HEIGHT);
//	ImageSelectCopy(fmsrc,fmdefect,CAM_WIDTH_CIS,CAM_HEIGHT_CIS,rtDefect,BAD_IMG_WIDTH,BAD_IMG_HEIGHT,0,0);
	ImageSelectCopy2(fmsrc,fmdefect,CAM_WIDTH_CIS,CAM_HEIGHT_CIS,l,r,t,b,BAD_IMG_WIDTH,BAD_IMG_HEIGHT,0,0);
	// stdev 를 위한 변수
	int nTotalCnt = 0;
	int nAve = 0;
	int nsum = 0,nsum1 = 0;
	double dstd = 0;
	int nTh = nTh1;
	int nPeakb1=1000,nPeakw1=0;
	if(bColor){
		for(int y=0;y<BAD_IMG_HEIGHT;y++){
			for(int x=0;x<BAD_IMG_WIDTH;x++){
				nTh = int(pData->m_nProjectX[nCam][rtDefect.left+x] +nTh1);
				if(y==0 || y==BAD_IMG_HEIGHT-1||x==0 || x==BAD_IMG_WIDTH-1)	*(fmtmp1+y*BAD_IMG_WIDTH+x) = 0;
				else if(*(fmsrc+(y+t)*CAM_WIDTH_CIS+x+l)>nTh)	
					*(fmtmp1+y*BAD_IMG_WIDTH+x) = 255;
				else									
					*(fmtmp1+y*BAD_IMG_WIDTH+x) = 0;
				nAve += *(fmsrc+(y+t)*CAM_WIDTH_CIS+x+l);
				if(*(fmsrc+(y+t)*CAM_WIDTH_CIS+x+l)-pData->m_nProjectX[nCam][rtDefect.left+x]> nPeakw1)nPeakw1 = *(fmsrc+(y+t)*CAM_WIDTH_CIS+x+l)-pData->m_nProjectX[nCam][rtDefect.left+x];
				if(pData->m_nProjectX[nCam][rtDefect.left+x]-*(fmsrc+(y+t)*CAM_WIDTH_CIS+x+l)< nPeakb1)nPeakb1 = pData->m_nProjectX[nCam][rtDefect.left+x]-*(fmsrc+(y+t)*CAM_WIDTH_CIS+x+l);
			}
		}
	}
	else{
		for(int y=0;y<BAD_IMG_HEIGHT;y++){
			for(int x=0;x<BAD_IMG_WIDTH;x++){
				nTh = int(pData->m_nProjectX[nCam][rtDefect.left+x] - nTh1);
				if(y==0 || y==BAD_IMG_HEIGHT-1||x==0 || x==BAD_IMG_WIDTH-1)	*(fmtmp1+y*BAD_IMG_WIDTH+x) = 0;
				else if(*(fmsrc+(y+t)*CAM_WIDTH_CIS+x+l)<nTh)
					*(fmtmp1+y*BAD_IMG_WIDTH+x) = 255;
				else										*(fmtmp1+y*BAD_IMG_WIDTH+x) = 0;
				nAve += *(fmsrc+(y+t)*CAM_WIDTH_CIS+x+l);
				if(*(fmsrc+(y+t)*CAM_WIDTH_CIS+x+l)-pData->m_nProjectX[nCam][rtDefect.left+x]> nPeakw1)nPeakw1 = *(fmsrc+(y+t)*CAM_WIDTH_CIS+x+l)-pData->m_nProjectX[nCam][rtDefect.left+x];
				if(pData->m_nProjectX[nCam][rtDefect.left+x]-*(fmsrc+(y+t)*CAM_WIDTH_CIS+x+l)< nPeakb1)nPeakb1 = pData->m_nProjectX[nCam][rtDefect.left+x]-*(fmsrc+(y+t)*CAM_WIDTH_CIS+x+l);
			}
		}
	}
	nAve /= (BAD_IMG_HEIGHT*BAD_IMG_WIDTH);
	*nave1 = nAve;
	*nPeakb = nPeakb1;
	*nPeakw = nPeakw1;
//	return rtsize;

	double dTemp,dBlobSize;
	int  nBlobCount =-1, nBlobNo =0;
	CRect rtBlob;
	//거리를 측정하기위한 param
	double dCx, dCy, dAngle, dPos[4][2], dShortLength, dLongLength,dMin,dMax,dAve;
	double dLengTemp,dLengTemp1,dLengTemp2,dPeriment,dx1,dy1,dcompact;
	double dlongLine = 0.0;
	//defect 개수가 1개로 저의 되어 있음. 수정 필요.
	dBlobSize = pData->m_dSize[nCam][nIndex]=  0.0;
	int nVisionLine = pData->m_nVisionLine;

 	m_pChain[nCam][nIndex]->SetChainData(1,fmtmp1,2,1,2,100000,BAD_IMG_WIDTH,BAD_IMG_HEIGHT);
 	nBlobCount = m_pChain[nCam][nIndex]->FastChain(0, 0, BAD_IMG_WIDTH-1,BAD_IMG_HEIGHT-1);
// 	// 	FChain_SetChainData(1,fmtmp,1,0,0,100000,BAD_IMG_WIDTH,BAD_IMG_HEIGHT);
// 	// 	nBlobCount = FChain_FastChain(0, 0, BAD_IMG_WIDTH-1,BAD_IMG_HEIGHT-1);
 	for(int i=0;i<nBlobCount;i++)
 	{
 		dTemp = m_pChain[nCam][nIndex]->Chain_Area(i);//FChain_Area(i, &dTemp);//			ttt
 		if(dTemp<2)continue;
 		if(dTemp>=dBlobSize)//최대 불량 사이즈.
 		{
 			nBlobNo = i;
 			dBlobSize = dTemp;//면적
 		}
 	}
	if(pData->m_nRealDefectCount1[nCam]>=14){
		delete fmtmp1;
		delete fmdefect;
		return rtsize;
	}
 	if(nBlobCount>0){
 		rtsize.SetRect(m_pChain[nCam][nIndex]->FindMinX(nBlobNo),m_pChain[nCam][nIndex]->FindMinY(nBlobNo),m_pChain[nCam][nIndex]->FindMaxX(nBlobNo),m_pChain[nCam][nIndex]->FindMaxY(nBlobNo));
 		dx1 = rtsize.Width()+1;// * pData->m_dScaleFactorX[nCam]*pData->m_nRecude;
 		dy1 = rtsize.Height()+1;// *pData->m_dScaleFactorY[nCam]*pData->m_nRecude;	
		if(dx1>pData->m_dDefectSize || dy1>pData->m_dDefectSize){
//			int nDefect = pData->m_nRealDefectCount1[nCam];
//			pData->m_nRealDefectCount1[nCam]++;
//   			CImage *img = new CImage();
//   			img->Create(BAD_IMG_WIDTH,BAD_IMG_HEIGHT,8);
//   			img->InitDIB();
//   			img->m_nWidth = BAD_IMG_WIDTH;
//   			img->m_nHeight = BAD_IMG_HEIGHT;
	  
	  //		memcpy(img->GetImagePtr(),fmtmp,BAD_IMG_WIDTH*BAD_IMG_HEIGHT);
 // 			memcpy(img->GetImagePtr(),fmdefect,BAD_IMG_WIDTH*BAD_IMG_HEIGHT);
//			memcpy(pData->m_pImageDefect1[nCam][nDefect]->GetImagePtr(),fmdefect,BAD_IMG_WIDTH*BAD_IMG_HEIGHT);
//   			CString str12;
//   			str12.Format("c:\\Data\\%d_Defect%d_%d.jpg",g_frame_num,nIdx,nDefect);
//   			img->Save(str12);
//   			delete img;
// 			if(pData->m_nRealDefectCount1[nCam]>=15){
// 				delete fmtmp;
// 				delete fmdefect;
// 				return rtsize;
// 			}
		}
 	}

	//	dx1 = (FChain_FindMaxX(nBlobNo) - FChain_FindMinX(nBlobNo)) * pData->m_dScaleFactorX[nCam]*pData->m_nRecude;
	//	dy1 = (FChain_FindMaxY(nBlobNo) - FChain_FindMinY(nBlobNo)) *pData->m_dScaleFactorY[nCam]*pData->m_nRecude;	
	//장축 구하기.
	// 	FChain_Center(nBlobNo, &dCx, &dCy);
	// 	FChain_FindAngle(nBlobNo, &dAngle);
	// 	FChain_FindMinRect(nBlobNo, dCx, dCy, dAngle, dPos);  //Blob을 포함하는 최소 사각형 구하는 함수
	// 	FChain_FineDistFromPoint(nBlobNo, dCx,dCy, &dMin, &dMax, &dAve);
	// 	FChain_FindCompactness(nBlobNo,&dcompact);
	// 	FChain_Perimeter(nBlobNo,&dPeriment);
	// 	dShortLength=sqrt( (dPos[0][0]-dPos[1][0])*(dPos[0][0]-dPos[1][0])+(dPos[0][1]-dPos[1][1])*(dPos[0][1]-dPos[1][1])); 
	// 	if(dShortLength<1 || dShortLength>1000) dShortLength=1;
	// 	dLongLength=sqrt( (dPos[2][0]-dPos[1][0])*(dPos[2][0]-dPos[1][0])+(dPos[2][1]-dPos[1][1])*(dPos[2][1]-dPos[1][1]));
	// 	if(dLongLength<1 || dLongLength>1000)  dLongLength=1;
	// 	rtsize.SetRect(FChain_FindMinX(nBlobNo),FChain_FindMinY(nBlobNo),FChain_FindMaxX(nBlobNo),FChain_FindMaxY(nBlobNo));


	delete fmtmp1;
	delete fmdefect;
	return rtsize;
}


CRect CInspect::SetBoundary1(CRect rt,CRect rtlimit)
{	
	if(rt.left	< rtlimit.left)			rt.OffsetRect(rtlimit.left-rt.left, 0);
	if(rt.top	< rtlimit.top)			rt.OffsetRect(0, rtlimit.top-rt.top);
	if(rt.right	>= rtlimit.right)		rt.OffsetRect(rtlimit.right-rt.right, 0);
	if(rt.bottom >= rtlimit.bottom)		rt.OffsetRect(0, rtlimit.bottom-rt.bottom);
	return rt;
}

CRect CInspect::CheckDefect1(int nCam,BYTE* fmsrc,CData *pData,CRect rtDefect,int nIdx,int nPos,BOOL bColor,int nTh1,int *nPeakb,int *nPeakw,int *nave1)//npos 0 무지 1코팅
{
	CRect rtsize;
	rtsize.SetRect(0,0,0,0);
	// 	int nIndex = nIdx;//pData->m_nRealDefectCount;
	// 	BYTE * fmdefect = new BYTE[BAD_IMG_WIDTH*BAD_IMG_HEIGHT];//pData->m_pImageDefect[0][nIdx]->GetImagePtr();//new BYTE[BAD_IMG_WIDTH*BAD_IMG_HEIGHT];
	// 	ImageSelectCopy(fmsrc,fmdefect,CAM_WIDTH_CIS,CAM_HEIGHT_CIS,rtDefect,BAD_IMG_WIDTH,BAD_IMG_HEIGHT,0,0);
	// 	unsigned char* fmtmp =	new BYTE[BAD_IMG_WIDTH*BAD_IMG_HEIGHT];
	// 	memset(fmtmp,0,BAD_IMG_WIDTH*BAD_IMG_HEIGHT);
	// 	// stdev 를 위한 변수
	// 	int nTotalCnt = 0;
	// 	int nAve = 0;
	// 	int nsum = 0,nsum1 = 0;
	// 	double dstd = 0;
	// 	int nTh = nTh1;
	// 	int nPeakb1=1000,nPeakw1=0;
	// 	if(bColor){
	// 		for(int y=0;y<BAD_IMG_HEIGHT;y++){
	// 			for(int x=0;x<BAD_IMG_WIDTH;x++){
	// 				nTh = int(pData->m_nProjectX[nCam][rtDefect.left+x] +nTh1);
	// 				if(y==0 || y==BAD_IMG_HEIGHT-1||x==0 || x==BAD_IMG_WIDTH-1)	*(fmtmp+y*BAD_IMG_WIDTH+x) = BACKGROUND;
	// 				else if(*(fmdefect+y*BAD_IMG_WIDTH+x)>nTh)	*(fmtmp+y*BAD_IMG_WIDTH+x) = OBJECT;
	// 				else									*(fmtmp+y*BAD_IMG_WIDTH+x) = BACKGROUND;
	// 				nAve += *(fmdefect+y*BAD_IMG_WIDTH+x);
	// 				if(*(fmdefect+y*BAD_IMG_WIDTH+x)-pData->m_nProjectX[nCam][rtDefect.left+x]> nPeakw1)nPeakw1 = *(fmdefect+y*BAD_IMG_WIDTH+x)-pData->m_nProjectX[nCam][rtDefect.left+x];
	// 				if(pData->m_nProjectX[nCam][rtDefect.left+x]-*(fmdefect+y*BAD_IMG_WIDTH+x)< nPeakb1)nPeakb1 = pData->m_nProjectX[nCam][rtDefect.left+x]-*(fmdefect+y*BAD_IMG_WIDTH+x);
	// 			}
	// 		}
	// 	}
	// 	else{
	// 		for(int y=0;y<BAD_IMG_HEIGHT;y++){
	// 			for(int x=0;x<BAD_IMG_WIDTH;x++){
	// 				nTh = int(pData->m_nProjectX[nCam][rtDefect.left+x] - nTh1);
	// 				if(y==0 || y==BAD_IMG_HEIGHT-1||x==0 || x==BAD_IMG_WIDTH-1)	*(fmtmp+y*BAD_IMG_WIDTH+x) = BACKGROUND;
	// 				else if(*(fmdefect+y*BAD_IMG_WIDTH+x)<nTh)	*(fmtmp+y*BAD_IMG_WIDTH+x) = OBJECT;
	// 				else										*(fmtmp+y*BAD_IMG_WIDTH+x) = BACKGROUND;
	// 				nAve += *(fmdefect+y*BAD_IMG_WIDTH+x);
	// 				if(*(fmdefect+y*BAD_IMG_WIDTH+x)-pData->m_nProjectX[nCam][rtDefect.left+x]> nPeakw1)nPeakw1 = *(fmdefect+y*BAD_IMG_WIDTH+x)-pData->m_nProjectX[nCam][rtDefect.left+x];
	// 				if(pData->m_nProjectX[nCam][rtDefect.left+x]-*(fmdefect+y*BAD_IMG_WIDTH+x)< nPeakb1)nPeakb1 = pData->m_nProjectX[nCam][rtDefect.left+x]-*(fmdefect+y*BAD_IMG_WIDTH+x);
	// 			}
	// 		}
	// 	}
	// 	nAve /= (BAD_IMG_HEIGHT*BAD_IMG_WIDTH);
	// 	*nave1 = nAve;
	// 	*nPeakb = nPeakb1;
	// 	*nPeakw = nPeakw1;
	// 
	// 	double dTemp,dBlobSize;
	// 	int  nBlobCount =-1, nBlobNo =0;
	// 	CRect rtBlob;
	// 	//거리를 측정하기위한 param
	// 	double dCx, dCy, dAngle, dPos[4][2], dShortLength, dLongLength,dMin,dMax,dAve;
	// 	double dLengTemp,dLengTemp1,dLengTemp2,dPeriment,dx1,dy1,dcompact;
	// 	double dlongLine = 0.0;
	// 	//defect 개수가 1개로 저의 되어 있음. 수정 필요.
	// 	dBlobSize = pData->m_dSize[nCam][nIndex]=  0.0;
	// 	int nVisionLine = pData->m_nVisionLine;
	// 
	// 	m_pChain->SetChainData(1,fmtmp,1,1,5,100000,BAD_IMG_WIDTH,BAD_IMG_HEIGHT);
	// 	nBlobCount = m_pChain->FastChain(0, 0, BAD_IMG_WIDTH-1,BAD_IMG_HEIGHT-1);
	// // 	FChain_SetChainData(1,fmtmp,1,0,0,100000,BAD_IMG_WIDTH,BAD_IMG_HEIGHT);
	// // 	nBlobCount = FChain_FastChain(0, 0, BAD_IMG_WIDTH-1,BAD_IMG_HEIGHT-1);
	// 	for(int i=0;i<nBlobCount;i++)
	// 	{
	// 		dTemp = m_pChain->Chain_Area(i);//FChain_Area(i, &dTemp);//			ttt
	// 		if(dTemp<2)continue;
	// 		if(dTemp>=dBlobSize)//최대 불량 사이즈.
	// 		{
	// 			nBlobNo = i;
	// 			dBlobSize = dTemp;//면적
	// 		}
	// 	}
	// 	rtsize.SetRect(m_pChain->FindMinX(nBlobNo),m_pChain->FindMinY(nBlobNo),m_pChain->FindMaxX(nBlobNo),m_pChain->FindMaxY(nBlobNo));
	// 	dx1 = rtsize.Width();// * pData->m_dScaleFactorX[nCam]*pData->m_nRecude;
	// 	dy1 = rtsize.Height();// *pData->m_dScaleFactorY[nCam]*pData->m_nRecude;	
	// 
	// //	dx1 = (FChain_FindMaxX(nBlobNo) - FChain_FindMinX(nBlobNo)) * pData->m_dScaleFactorX[nCam]*pData->m_nRecude;
	// //	dy1 = (FChain_FindMaxY(nBlobNo) - FChain_FindMinY(nBlobNo)) *pData->m_dScaleFactorY[nCam]*pData->m_nRecude;	
	// 	//장축 구하기.
	// // 	FChain_Center(nBlobNo, &dCx, &dCy);
	// // 	FChain_FindAngle(nBlobNo, &dAngle);
	// // 	FChain_FindMinRect(nBlobNo, dCx, dCy, dAngle, dPos);  //Blob을 포함하는 최소 사각형 구하는 함수
	// // 	FChain_FineDistFromPoint(nBlobNo, dCx,dCy, &dMin, &dMax, &dAve);
	// // 	FChain_FindCompactness(nBlobNo,&dcompact);
	// // 	FChain_Perimeter(nBlobNo,&dPeriment);
	// // 	dShortLength=sqrt( (dPos[0][0]-dPos[1][0])*(dPos[0][0]-dPos[1][0])+(dPos[0][1]-dPos[1][1])*(dPos[0][1]-dPos[1][1])); 
	// // 	if(dShortLength<1 || dShortLength>1000) dShortLength=1;
	// // 	dLongLength=sqrt( (dPos[2][0]-dPos[1][0])*(dPos[2][0]-dPos[1][0])+(dPos[2][1]-dPos[1][1])*(dPos[2][1]-dPos[1][1]));
	// // 	if(dLongLength<1 || dLongLength>1000)  dLongLength=1;
	// // 	rtsize.SetRect(FChain_FindMinX(nBlobNo),FChain_FindMinY(nBlobNo),FChain_FindMaxX(nBlobNo),FChain_FindMaxY(nBlobNo));
	// 
	// 	delete fmtmp;
	// 	delete fmdefect;
	return rtsize;
}
int CInspect::GetDefectSize(int nCam,CData *pData,BYTE * fm,int nw,int nh,int nblackwhite,int nth,double *dsizex,double *dsizey,double *dsize)
{
// 	if(nw<=0 || nh<=0){
// 		*dsize = 0;*dsizex=0;*dsizey=0;return -1;
// 	}
// 	BYTE * fmtmp = new BYTE[nw*nh];
// 	memset(fmtmp,0,nw*nh);
// 
// //	memcpy(fmtmp,fm,nw*nh);
// //평균밝기 구하기
// 	double dsum=0,dc=0;
// 	for(int i=0;i<nh;i++)		for(int j=0;j<nw;j++)			dsum += *(fm+i*nw+j);
// 	dsum /= (nh*nw);
// //	int nthw = pData->m_nThWhite3;
// 	double dth = dsum+nth;
// 	if(nblackwhite==1)dth = dsum-nth;
// 	for(int i=0;i<nh;i++)
// 		for(int j=0;j<nw;j++){
// 			if(nblackwhite==1){
// 				if(*(fm+i*nw+j) <= nth)					*(fmtmp+i*nw+j) = 255;
// 				else	*(fmtmp+i*nw+j) = 0;
// 			}
// 			else{
// 				if(*(fm+i*nw+j) >= nth)					*(fmtmp+i*nw+j) = 255;
// 				else	*(fmtmp+i*nw+j) = 0;
// 			}
// 		}
// 
// 	double dTemp = 0,dBlobSize = 0,dx1=0,dy1=0;
// 	int nBlobNo = 0;
// 
// 	m_pChain[nCam]->SetChainData(1,fmtmp,1,1,2,100000,nw,nh);
// 	int nBlobCount = m_pChain[nCam]->FastChain(0, 0, nw-1,nh-1);
// 	for(int i=0;i<nBlobCount;i++)
// 	{
// 		dTemp = m_pChain[nCam]->Chain_Area(i);//FChain_Area(i, &dTemp);//			ttt
// 		if(dTemp<2)continue;
// 		if(dTemp>=dBlobSize)//최대 불량 사이즈.
// 		{
// 			nBlobNo = i;
// 			dBlobSize = dTemp;//면적
// 		}
// 	}
// 	if(pData->m_bBlobImg )
// 		memcpy(fm,fmtmp,nw*nh);
// 
// 
// 	delete fmtmp;
// 	CRect rtsize;
// 	if(nBlobCount>0){
// 		rtsize.SetRect(m_pChain[nCam]->FindMinX(nBlobNo),m_pChain[nCam]->FindMinY(nBlobNo),m_pChain[nCam]->FindMaxX(nBlobNo),m_pChain[nCam]->FindMaxY(nBlobNo));
// 		dx1 = rtsize.Width()+1;// * pData->m_dScaleFactorX[nCam]*pData->m_nRecude;
// 		dy1 = rtsize.Height()+1;// *pData->m_dScaleFactorY[nCam]*pData->m_nRecude;	
// 	}
// 	if(dBlobSize<4 || dx1<=0 || dy1<=0){
// 		*dsize = 0;*dsizex=0;*dsizey=0;return int(dsum);
// 	}
// 	*dsizex = dx1;*dsizey=dy1;*dsize=(dx1*dy1)*0.5;

	return int(0);
}

int CInspect::FullLineSearch(CData *pData)
{
	//Full Image에 대한 에지 검색 Projection Data 사용
	pData->m_nChangeLine[0]=pData->m_nChangeLine[1] = 0;
	int nstart=10,nend=CAM_WIDTH_CIS*3;
	int ngap = 8,ngap2=14;
	//먼저 무지와 코팅 부만 구분한다
	int nEdgeth = 55,nWhitev1 = pData->m_nCoatBright,nTol=2;//param
	int nMinLineWidth = pData->m_nMinLineWidth;
	int nMinLineWidth1 = pData->m_nMinLineWidthMid;
	int nLineJump = 0,ntmp=0;
	int nCam = 0,nMax=0,nc1=0,nRoiCount=0,nlinecount=0,noldcam=0,npos1 = 0;
	double dpos1= 0;
	nEdgeth = pData->m_dThUp[0];//sparam1
	if(pData->m_bAutoEdge && pData->m_nEdgeAverage[0]>10)
		nEdgeth = pData->m_nEdgeAverage[0];
	if(nEdgeth>180)
		nEdgeth = 160;
	int nOffset1 = 15;
	double ddata1[8]={0,};
	int nOffset2 = 20;//200 //@chcho0821 중앙 좁은 무지폭 투입관련
	BOOL bAve=TRUE;
	int nAve = 0,ncunt1=0,nc2[3]={0,},ngraycount[10]={0,};
	if(nstart <2300)nstart = 2300;//limit inspect range
	if(nend>CAM_WIDTH_CIS*3-2300)nend = CAM_WIDTH_CIS*3-2300;//limit inspect range
	if(pData->m_bAutoCoatBrightness){
		nWhitev1 = pData->m_dAverageBrightness2[1]*1.5;
 	    if(nWhitev1<50 || nWhitev1>120) nWhitev1 = pData->m_nCoatBright;
		nWhitev1 = (pData->m_dAverageBrightness2[0] -pData->m_dAverageBrightness2[1]) *0.3;
	}
	pData->m_dAverageBrightness2[2] = nWhitev1;
	for(int i=0;i<40;i++)	pData->m_rtNewInspect[i].SetRect(0,0,0,0);
	for(int i=0;i<20;i++)
		pData->m_dGrayValue[i]=0;
	BOOL bPing = FALSE;
	int nWhitelimit = pData->m_nMinLineWidth;
	int	m_nCheckCount = 0;
	//프라이머 절연 세라믹일경우 에지 보강해야함.
	for(int x=nstart;x<nend-(ngap*2);x++){
		nCam = x/CAM_WIDTH_CIS;
		if(nCam >noldcam){	//카메라 바뀌는거 체크
			int nX2 = x%CAM_WIDTH_CIS;
			pData->m_rtInspect[noldcam][nRoiCount].right = CAM_WIDTH_CIS-1;
			for(int i8=0;i8<MOD_COUNT;i8++)
				pData->m_rtInspect1[noldcam][i8][nRoiCount].right = CAM_WIDTH_CIS-1;
			nRoiCount++;
			pData->m_nLineCount1[noldcam] =nRoiCount; 
			nRoiCount = 0;	 //영역 설정
			pData->m_rtInspect[nCam][nRoiCount].left = 0;//nX2;
			for(int i8=0;i8<MOD_COUNT;i8++)
				pData->m_rtInspect1[nCam][i8][nRoiCount].left = 0;

		}
		if(bPing)		{
			nAve += pData->m_nFullImageProj[x];ncunt1++;
			if(nc1>0){
				pData->m_dGrayValue[nc1-1]+= pData->m_nFullImageProj[x];
				ngraycount[nc1-1]++;
			}

			if(bAve==FALSE){//무지부
				pData->m_dAverageBrightness1[0] += pData->m_nFullImageProj[x];nc2[0]++;
			}
			else{//코팅부
				pData->m_dAverageBrightness1[1] += pData->m_nFullImageProj[x];nc2[1]++;
			}
			
		}//전체 밝기
//		TRACE("%d  %d \n", x,pData->m_nFullImageProj[x]);
		//full Projection Data 
		if(bAve==TRUE &&pData->m_nFullImageProj[x-12]<nWhitev1&&pData->m_nFullImageProj[x-8]<nWhitev1 && abs(pData->m_nFullImageProj[x]-pData->m_nFullImageProj[x+ngap]) >= nEdgeth&& abs(pData->m_nFullImageProj[x+1]-pData->m_nFullImageProj[x+ngap+1])>= nEdgeth )
		{//black 조건  왼쪽이 어두움 //제일 처음 여기로 들어옴
// 			for(int xx1=x+ngap2;xx1<x+nMinLineWidth;xx1++){//라인 이후 일정 간격이후 라인 데이터는 스킵한다 불량으로 검출해야함
// 				if(xx1>=nend-ngap2*2)	break;//영상 끝부분까지 갈경우 스킵한다
// 				if(abs(pData->m_nFullImageProj[xx1]-pData->m_nFullImageProj[xx1+ngap]) >= nEdgeth){
// 					nLineJump = 1;x= xx1+10;break;
// 				}
// 			}
// 			if(nLineJump==1){nLineJump = 0;continue;}
			if(bPing==TRUE){//cis 여기가 
				int nWhiteCheck = 0,nWhiteCheck1=0;
				int nwhitecut1 = (pData->m_dAverageBrightness2[1]+pData->m_dAverageBrightness2[0])*0.3;
				for(int x11=x;x11<x+100;x11++){
					if(pData->m_nFullImageProj[x11]>nwhitecut1)nWhiteCheck++;
					else nWhiteCheck=0;
					if(nWhiteCheck1 <nWhiteCheck )
						nWhiteCheck1 = nWhiteCheck;

				}
				nWhiteCheck1 = nWhiteCheck1;
				if(nWhiteCheck1<nWhitelimit){
					x+= nWhiteCheck1;
					continue;
				}

			}
	
			pData->m_rectIns[nCam].left = x;
			nMax = 0;
			for(int k=x-4;k<x+10;k++){//에지 주위 가장 강한 에지를 구한다
				if(k<10)k=10;if(k>=nend-ngap2)break;
				ntmp = abs(pData->m_nFullImageProj[k]-pData->m_nFullImageProj[k+2]);
				if(ntmp >= nMax){npos1 = k+nTol;	nMax = ntmp;}
			}
			int nc21 = 0,nmax1=0;
			double dedge1 = 0,npos11=0;
			int ncount2 = 0;
			{//8개 data의 평균을 구한다.

				for(int k1=0;k1<MOD_COUNT;k1++){
					nmax1 = 0;
					for(int n1=npos1-4;n1<npos1+12;n1++){
						if( abs(pData->m_nFullImageProj1[k1][n1] -  pData->m_nFullImageProj1[k1][n1+2]) > nmax1){
							npos11 = n1+nTol;nmax1=abs(pData->m_nFullImageProj1[k1][n1] -  pData->m_nFullImageProj1[k1][n1+2]);
						}
					}
					pData->m_dNewLineEdgeData11[k1][nc1] = npos11;
					ddata1[k1] = npos11;
					if(nmax1==0)
						npos11 = npos1;
					dedge1 += npos11;nc21++;
				}
//				if(pData->m_bSumEdgeData==TRUE)
					dedge1 /= nc21;
				pData->m_dLineEdgeData1[nCam][nRoiCount] = int(dedge1)%CAM_WIDTH_CIS;
				if(pData->m_bLineAverageData){
					npos1 = dedge1;
					dpos1 = dedge1;
				}
				else{
					dedge1 = 0;
					sort(ddata1,ddata1+8);
					for(int i=2;i<6;i++){
						dedge1 += ddata1[i];
					}
					dedge1 /= 4;
					npos1 = dedge1;
					dpos1 = dedge1;
//					dpos1 = npos1;

				}
			}
// 			else{
// 				pData->m_nPolarEdge[0]=npos1;
// 				pData->m_dLineEdgeData1[nCam][nRoiCount] = npos1%CAM_WIDTH_CIS;
// 				dpos1 = npos1;
// 			}
			if(pData->m_nFoilEdge[0]==0)
				pData->m_nFoilEdge[0] = npos1;
			else
				pData->m_nFoilEdge[1] = npos1;

			pData->m_dEdgeValue1[nCam][nRoiCount] = nMax;// pData->m_nProjectX[nCam][i]-pData->m_nProjectX[nCam][i+4];
			if(pData->m_rtInspect[nCam][nRoiCount].left>10|| nCam>0){
				pData->m_rtInspect[nCam][nRoiCount].right = npos1%CAM_WIDTH_CIS;//black end
				for(int i8=0;i8<MOD_COUNT;i8++)
					pData->m_rtInspect1[nCam][i8][nRoiCount].right = int(pData->m_dNewLineEdgeData11[i8][nc1])%CAM_WIDTH_CIS;
				nRoiCount++;
			}
			pData->m_rtInspect[nCam][nRoiCount].left = npos1%CAM_WIDTH_CIS;//white start
			for(int i8=0;i8<MOD_COUNT;i8++)
				pData->m_rtInspect1[nCam][i8][nRoiCount].left = int(pData->m_dNewLineEdgeData11[i8][nc1])%CAM_WIDTH_CIS;

// 			if(nCam==0 && nRoiCount==0)
// 				nRoiCount++;
			pData->m_dNewLineEdgeData1[nc1] = dpos1;//전체 에지
			pData->m_rtinsulate[pData->m_nInsulateCount].left = npos1;
			if(nc1==0)	nMinLineWidth = nMinLineWidth1;//옵셋2 값을 적용시킨다
			nc1++;
			//
			if(bPing){
			//	x+= 250;
				x+= nMinLineWidth;//30;//cis 최소 라인폭 만큼만 더하기 해준다. 0.3d으로 셋팅할것 그리고 아일랜드 200으로 셋팅
			}
			if(x>=pData->m_nCadidateEndpos)
				x = pData->m_nCadidateEndpos-20;
 			if(nc1==1)	x+= nMinLineWidth;//nOffset1;
// 			else		x+= nMinLineWidth;//nOffset2;
			nlinecount++;bAve=FALSE;
			bPing = TRUE;
		}
		else if(bAve==FALSE && pData->m_nFullImageProj[x+12]<nWhitev1 && abs(pData->m_nFullImageProj[x]-pData->m_nFullImageProj[x+ngap]) >= nEdgeth&& abs(pData->m_nFullImageProj[x+1]-pData->m_nFullImageProj[x+ngap+1])>= nEdgeth )
		{//우측이 어두움 // 여긴 최소 10mm 이상 어두워야함 //300 
			if(nCam==2 && x>1000)
				nMinLineWidth = pData->m_nMinLineWidth;//3번 카메라의 제일 마지막 라인인 경우
// 			for(int xx1=x+ngap2;xx1<x+nMinLineWidth;xx1++){//라인 이후 일정 간격이후 라인 데이터는 스킵한다 불량으로 검출해야함
// 				if(xx1>=nend-ngap2*2)	break;//영상 끝부분까지 갈경우 스킵한다
// 				if(abs(pData->m_nFullImageProj[xx1]-pData->m_nFullImageProj[xx1+ngap]) >= nEdgeth){
// 					nLineJump = 1;x= xx1+10;break;
// 				}
// 			}
// 			if(nLineJump==1){nLineJump = 0;continue;}
			nMax = 0;
			for(int k=x-4;k<x+10;k++){//에지 주위 가장 강한 에지를 구한다
				if(k<10)k=10;if(k>=nend-ngap2)break;
				ntmp = abs(pData->m_nFullImageProj[k]-pData->m_nFullImageProj[k+2]);
				if(ntmp >= nMax){npos1 = k+nTol;	nMax = ntmp;}
			}
			int nc21 = 0,nmax1=0,npos11=0;
			double dedge1 = 0;
			
			{//8개 data의 평균을 구한다.			//Projecttion Data중에 에지의 평균을 구한다 //m_nFullImageProj1
				for(int k1=0;k1<MOD_COUNT;k1++){
					nmax1 = 0;
					for(int n1=npos1-4;n1<npos1+8;n1++){
						if( abs(pData->m_nFullImageProj1[k1][n1] -  pData->m_nFullImageProj1[k1][n1+2]) > nmax1){
							npos11 = n1+nTol+1;nmax1=abs(pData->m_nFullImageProj1[k1][n1] -  pData->m_nFullImageProj1[k1][n1+2]);
						}
					}
					if(nmax1==0)
						npos11 = npos1;
					ddata1[k1] = npos11;
					pData->m_dNewLineEdgeData11[k1][nc1] = npos11;

					dedge1 += npos11;nc21++;
				}
//				if(pData->m_bSumEdgeData==TRUE)
					dedge1 /= nc21;
				pData->m_dLineEdgeData1[nCam][nRoiCount+1] = int(dedge1)%CAM_WIDTH_CIS;
				if(pData->m_bLineAverageData && abs(dedge1-npos1)<10){
					npos1 = dedge1;
					dpos1 = dedge1;
				}
				else{
					dedge1 = 0;
					sort(ddata1,ddata1+8);
					for(int i=2;i<6;i++){
						dedge1 += ddata1[i];
					}
					dedge1 /= 4;
					npos1 = dedge1;
					dpos1 = dedge1;

					//dpos1 = npos1;
				}
			}
// 			else{
// 				pData->m_nPolarEdge[0]=npos1;
// 				pData->m_dLineEdgeData1[nCam][nRoiCount+1] = npos1*CAM_WIDTH_CIS;
// 				dpos1 = npos1;
// 			}
			pData->m_rtInspect[nCam][nRoiCount].right = npos1%CAM_WIDTH_CIS;//white end
			for(int i8=0;i8<MOD_COUNT;i8++)
				pData->m_rtInspect1[nCam][i8][nRoiCount].right = int(pData->m_dNewLineEdgeData11[i8][nc1])%CAM_WIDTH_CIS;

			pData->m_nFoilEdge[1] = npos1;

			////무지 절연 roi 입력
			pData->m_rtinsulate[pData->m_nInsulateCount].right = npos1;
			pData->m_nInsulateCount++;
			nRoiCount++;
			pData->m_rtInspect[nCam][nRoiCount].left = npos1%CAM_WIDTH_CIS;//black start
			for(int i8=0;i8<MOD_COUNT;i8++)
				pData->m_rtInspect1[nCam][i8][nRoiCount].left = int(pData->m_dNewLineEdgeData11[i8][nc1])%CAM_WIDTH_CIS;

			pData->m_dNewLineEdgeData1[nc1] =dpos1;// npos1;

			nc1++;
			if(nc1==1)	x+= 1000;//nMinLineWidth;//nOffset1;
			else		x+= 1000;//nMinLineWidth;//nOffset2;
			nlinecount++;
			bAve=TRUE;
		}
		if(nc1>=MAX_REALDEFECT-1) break;
		noldcam = nCam;
		if(nCam==2 && x>CAM_WIDTH_CIS*2)
			pData->m_nLineCount1[2] =nRoiCount; 

	}

///////////////////////밝기 조건이 맞고 포일 

	if(pData->m_nSkipWhite[0] < pData->m_nWhiteParam && (nc1<2 || nc1%2==1)) {
		if(pData->m_nCandidateLine>2 && pData->m_nCandidateLine%2==0){
			pData->m_nChangeLine[0] = nc1;
			pData->m_nChangeLine[1] =  pData->m_nCandidateLine;
			nc1 =nlinecount= pData->m_nCandidateLine;
			for(int i=0;i<pData->m_nCandidateLine;i++){
				pData->m_dNewLineEdgeData1[i] = pData->m_rtSubLine[i].left;
			}
		}
		else{
			//이전값//	
			if(pData->m_nOldLineCount>2){
				m_nCheckLine = 1;//line research1
				nc1 = pData->m_nOldLineCount;
				for(int i=0;i<nc1;i++)
					pData->m_dNewLineEdgeData1[i]=pData->m_dNewLineEdgeData1Old[i];
			}
		}
	}

///사행 체크 및 라인이 이상할 경우 
	//m_rtSubLine
	if(nc1 < pData->m_nCandidateLine &&  pData->m_nCandidateLine%2==0){
		pData->m_nChangeLine[0] = nc1;
		pData->m_nChangeLine[1] =  pData->m_nCandidateLine;
		nc1 =nlinecount= pData->m_nCandidateLine;
		m_nCheckLine = 2;//line refind 1
		for(int i=0;i<pData->m_nCandidateLine;i++){
			pData->m_dNewLineEdgeData1[i] = pData->m_rtSubLine[i].left;

		}
	}

	pData->m_nNewLineCount = nc1;
	for(int i=0;i<nc1-1;i++){
		pData->m_rtNewInspect[i].SetRect(pData->m_dNewLineEdgeData1[i],0,pData->m_dNewLineEdgeData1[i+1],CAM_HEIGHT_CIS);
	}
	if(nc2[0]>0)		pData->m_dAverageBrightness1[0]/=nc2[0];
	if(nc2[1]>0)		pData->m_dAverageBrightness1[1]/=nc2[1];

	for(int i=0;i<nc1-1;i++){
		if(ngraycount[i]>0)	pData->m_dGrayValue[i] /= ngraycount[i];
		else pData->m_dGrayValue[i] = 0;
	}
	if(ncunt1>0)	nAve /= ncunt1;
	else nAve = -1;
	pData->m_dAverageBrightness1[2] = nAve;

	return nAve;
}

int CInspect::FullLineSearch1(CData *pData)
{//역방향 
	//Full Image에 대한 에지 검색 Projection Data 사용
	int nstart=10,nend=CAM_WIDTH_CIS*3;
	int ngap = 6,ngap2=14;
	//먼저 무지와 코팅 부만 구분한다
	int nEdgeth = 55,nWhitev1 = pData->m_nCoatBright,nTol=2;//param
	int nMinLineWidth = pData->m_nMinLineWidth;
	int nMinLineWidth1 = pData->m_nMinLineWidthMid;
	int nLineJump = 0,ntmp=0;
	int nCam = 0,nMax=0,npos1=0,nc1=0,nRoiCount=0,nlinecount=0,noldcam=2;
	nEdgeth = pData->m_dThUp[0];//sparam1
	if(pData->m_bAutoEdge && pData->m_nEdgeAverage[0]>10)
		nEdgeth = pData->m_nEdgeAverage[0];
	if(nEdgeth>180)
		nEdgeth = 160;
	int nOffset1 = 15;
	int nOffset2 = 20;//200 //@chcho0821 중앙 좁은 무지폭 투입관련
	BOOL bAve=TRUE;
	int nAve = 0,ncunt1=0,nc2[3]={0,};
	if(nstart <2300)nstart = 2300;//limit inspect range
	if(nend>CAM_WIDTH_CIS*3-2300)nend = CAM_WIDTH_CIS*3-2300;//limit inspect range
	if(pData->m_bAutoCoatBrightness)
		nWhitev1 = pData->m_nCoatAveBrightness;
	//	if(pData->m_nCoatAveBrightness<)
	BOOL bPing = FALSE;
	int nWhitelimit = pData->m_nMinLineWidth;
//	for(int x=nstart;x<nend-(ngap*2);x++)
	for(int x=nend;x>nstart+(ngap*2);x--)
	{
		nCam = x/CAM_WIDTH_CIS;
		if(nCam <noldcam){	//카메라 바뀌는거 체크
			int nX2 = x%CAM_WIDTH_CIS;
			pData->m_rtInspect[noldcam][nRoiCount].left = 1;//CAM_WIDTH_CIS-1;
			nRoiCount++;
			pData->m_nLineCount1[noldcam] =nRoiCount; 
			nRoiCount = 0;	 //영역 설정
			pData->m_rtInspect[nCam][nRoiCount].right = CAM_WIDTH_CIS-1;//0;//nX2;
		}
		if(bPing)		{
			nAve += pData->m_nFullImageProj[x];ncunt1++;
			if(bAve==FALSE){//무지부
				pData->m_dAverageBrightness1[0] += pData->m_nFullImageProj[x];nc2[0]++;
			}
			else{//코팅부
				pData->m_dAverageBrightness1[1] += pData->m_nFullImageProj[x];nc2[1]++;
			}

		}//전체 밝기
		//		TRACE("%d  %d \n", x,pData->m_nFullImageProj[x]);
		//full Projection Data 
		if(bAve==TRUE &&pData->m_nFullImageProj[x+12]<nWhitev1&&pData->m_nFullImageProj[x+4]<nWhitev1&&pData->m_nFullImageProj[x+8]<nWhitev1 && abs(pData->m_nFullImageProj[x]-pData->m_nFullImageProj[x-ngap]) >= nEdgeth&& abs(pData->m_nFullImageProj[x-1]-pData->m_nFullImageProj[x-ngap-1])>= nEdgeth )
		{//black 조건  왼쪽이 어두움 //제일 처음 여기로 들어옴
			// 			for(int xx1=x+ngap2;xx1<x+nMinLineWidth;xx1++){//라인 이후 일정 간격이후 라인 데이터는 스킵한다 불량으로 검출해야함
			// 				if(xx1>=nend-ngap2*2)	break;//영상 끝부분까지 갈경우 스킵한다
			// 				if(abs(pData->m_nFullImageProj[xx1]-pData->m_nFullImageProj[xx1+ngap]) >= nEdgeth){
			// 					nLineJump = 1;x= xx1+10;break;
			// 				}
			// 			}
			// 			if(nLineJump==1){nLineJump = 0;continue;}
			if(bPing==TRUE){
				int nWhiteCheck = 0,nWhiteCheck1=0;
				int nwhitecut1 = (pData->m_dAverageBrightness2[1]+pData->m_dAverageBrightness2[0])*0.3;
				for(int x11=x;x11>x-100 && x>0;x11--){
					if(pData->m_nFullImageProj[x11]>nwhitecut1)nWhiteCheck++;
					else nWhiteCheck=0;
					if(nWhiteCheck1 <nWhiteCheck )
						nWhiteCheck1 = nWhiteCheck;

				}
				nWhiteCheck1 = nWhiteCheck1;
				if(nWhiteCheck1<nWhitelimit){
					x+= nWhiteCheck1;
					continue;
				}

			}

			pData->m_rectIns[nCam].left = x;
			nMax = 0;
			for(int k=x+4;k>x-6;k--){//에지 주위 가장 강한 에지를 구한다
				if(k<10)k=10;if(k<=nstart+ngap2)break;
				ntmp = abs(pData->m_nFullImageProj[k]-pData->m_nFullImageProj[k-2]);
				if(ntmp >= nMax){npos1 = k-nTol;	nMax = ntmp;}
			}
			int nc21 = 0,nmax1=0,npos11=0;
			double dedge1 = 0;
			if(pData->m_bSumEdgeData==TRUE){//8개 data의 평균을 구한다.

				for(int k1=0;k1<MOD_COUNT;k1++){
					nmax1 = 0;
					for(int n1=npos1+4;n1>npos1-6;n1--){
						if( abs(pData->m_nFullImageProj1[k1][n1] -  pData->m_nFullImageProj1[k1][n1-2]) > nmax1){
							npos11 = n1-nTol;nmax1=abs(pData->m_nFullImageProj1[k1][n1] -  pData->m_nFullImageProj1[k1][n1-2]);
						}
					}
					dedge1 += npos11;nc21++;
				}
				dedge1 /= nc21;
				pData->m_dLineEdgeData1[nCam][nRoiCount] = int(dedge1)%CAM_WIDTH_CIS;
				if(pData->m_bLineAverageData)
					npos1 = dedge1;
			}
			else{
				pData->m_nPolarEdge[0]=npos1;
				pData->m_dLineEdgeData1[nCam][nRoiCount] = npos1%CAM_WIDTH_CIS;
			}
			if(pData->m_nFoilEdge[0]==0)
				pData->m_nFoilEdge[0] = npos1;
			else
				pData->m_nFoilEdge[1] = npos1;

			pData->m_dEdgeValue1[nCam][nRoiCount] = nMax;// pData->m_nProjectX[nCam][i]-pData->m_nProjectX[nCam][i+4];
			if(pData->m_rtInspect[nCam][nRoiCount].left>10|| nCam>0){
				pData->m_rtInspect[nCam][nRoiCount].left = npos1%CAM_WIDTH_CIS;//black end
				nRoiCount++;
			}
			pData->m_rtInspect[nCam][nRoiCount].right = npos1%CAM_WIDTH_CIS;//white start
			// 			if(nCam==0 && nRoiCount==0)
			// 				nRoiCount++;
			pData->m_dNewLineEdgeData1[nc1] = npos1;//전체 에지
			pData->m_rtinsulate[pData->m_nInsulateCount].left = npos1;
			if(nc1==0)	nMinLineWidth = nMinLineWidth1;//옵셋2 값을 적용시킨다
			nc1++;
			//
			if(bPing){
				x-= 250;
			}
// 			if(x>=pData->m_nCadidateEndpos)
// 				x = pData->m_nCadidateEndpos-20;
			if(nc1==1)	x-= nMinLineWidth;//nOffset1;
			// 			else		x+= nMinLineWidth;//nOffset2;
			nlinecount++;bAve=FALSE;
			bPing = TRUE;
		}
		else if(bAve==FALSE && pData->m_nFullImageProj[x-12]<nWhitev1 && abs(pData->m_nFullImageProj[x]-pData->m_nFullImageProj[x-ngap]) >= nEdgeth&& abs(pData->m_nFullImageProj[x-1]-pData->m_nFullImageProj[x-ngap-1])>= nEdgeth )
		{//우측이 어두움 // 여긴 최소 10mm 이상 어두워야함 //300 
// 			if(nCam==2 && x>1000)
// 				nMinLineWidth = pData->m_nMinLineWidth;//3번 카메라의 제일 마지막 라인인 경우
			nMax = 0;
			for(int k=x+4;k>x-6;k--){//에지 주위 가장 강한 에지를 구한다
				if(k<10)k=10;if(k<=nstart-ngap2)break;
				ntmp = abs(pData->m_nFullImageProj[k]-pData->m_nFullImageProj[k-2]);
				if(ntmp >= nMax){npos1 = k-nTol;	nMax = ntmp;}
			}
			int nc21 = 0,nmax1=0,npos11=0;
			double dedge1 = 0;
			if(pData->m_bSumEdgeData==TRUE){//8개 data의 평균을 구한다.			//Projecttion Data중에 에지의 평균을 구한다 //m_nFullImageProj1
				for(int k1=0;k1<MOD_COUNT;k1++){
					nmax1 = 0;
					for(int n1=npos1+4;n1>npos1-6;n1--){
						if( abs(pData->m_nFullImageProj1[k1][n1] -  pData->m_nFullImageProj1[k1][n1-2]) > nmax1){
							npos11 = n1-nTol-1;nmax1=abs(pData->m_nFullImageProj1[k1][n1] -  pData->m_nFullImageProj1[k1][n1-2]);
						}
					}
					dedge1 += npos11;nc21++;
				}
				dedge1 /= nc21;
				pData->m_dLineEdgeData1[nCam][nRoiCount+1] = int(dedge1)%CAM_WIDTH_CIS;
				if(pData->m_bLineAverageData && abs(dedge1-npos1)<10)
					npos1 = dedge1;
			}
			else{
				pData->m_nPolarEdge[0]=npos1;
				pData->m_dLineEdgeData1[nCam][nRoiCount+1] = npos1*CAM_WIDTH_CIS;
			}
			pData->m_rtInspect[nCam][nRoiCount].left = npos1%CAM_WIDTH_CIS;//white end
			pData->m_nFoilEdge[1] = npos1;

			////무지 절연 roi 입력
			pData->m_rtinsulate[pData->m_nInsulateCount].right = npos1;
			pData->m_nInsulateCount++;
			nRoiCount++;
			pData->m_rtInspect[nCam][nRoiCount].right = npos1%CAM_WIDTH_CIS;//black start
			pData->m_dNewLineEdgeData1[nc1] = npos1;

			nc1++;
			if(nc1==1)	x-= 1000;//nMinLineWidth;//nOffset1;
			else		x-= 1000;//nMinLineWidth;//nOffset2;
			nlinecount++;
			bAve=TRUE;
		}
		if(nc1>=MAX_REALDEFECT-1) break;
		noldcam = nCam;
		if(nCam==0 && x<CAM_WIDTH_CIS)
			pData->m_nLineCount1[2] =nRoiCount; 

	}

	pData->m_nNewLineCount = nc1;
	if(nc2[0]>0)		pData->m_dAverageBrightness1[0]/=nc2[0];
	if(nc2[1]>0)		pData->m_dAverageBrightness1[1]/=nc2[1];

	if(ncunt1>0)	nAve /= ncunt1;
	else nAve = -1;
	pData->m_dAverageBrightness1[2] = nAve;

	return nAve;
}
int CInspect::checkDragLine(CData *pData,BYTE* fm)
{
	int nRet = 1;//드래그
	int nXProj[BAD_IMG_WIDTH]={0,};
	double dsum=0,dc=0,dc1=0;
	double dwcogx=0,dwcogy=0,dbcogx=0,dbcogy=0;
	for(int i=0;i<BAD_IMG_HEIGHT;i++){
		for(int j=0;j<BAD_IMG_WIDTH;j++){
			nXProj[j] +=  *(fm+i*BAD_IMG_WIDTH+j);
			dsum += *(fm+i*BAD_IMG_WIDTH+j);
			dc++;
		}
	}
	dsum /= dc;
// 	dc=0;
// 	for(int i=0;i<BAD_IMG_HEIGHT;i++){
// 		for(int j=0;j<BAD_IMG_WIDTH;j++){
// 			if(*(fm+i*BAD_IMG_WIDTH+j)>dsum){
// 				dwcogx+=j;dwcogy+=i;dc++;
// 			}
// 			else{
// 				dbcogx+=j;dbcogy+=i;dc1++;
// 			}
// 		}
// 	}
// 	dwcogx/= dc;dwcogy/=dc;
// 	dbcogx/= dc1;dbcogy/=dc1;
	int nleftsum=0,nrightsum=0;
	for(int j=0;j<BAD_IMG_WIDTH;j++){
		nXProj[j] /= BAD_IMG_HEIGHT;
		if(j<5)nleftsum+=nXProj[j];
		if(j>BAD_IMG_WIDTH-5)nrightsum += nXProj[j];
	}
	int nwcnt = 0;
	if(nleftsum> nrightsum){
		for(int i=BAD_IMG_WIDTH*0.5;i<BAD_IMG_WIDTH-10;i++){
			nwcnt = 0;
			for(int j=0;j<BAD_IMG_HEIGHT;j++){
				if(*(fm+j*BAD_IMG_WIDTH+i) > dsum-10)nwcnt++;
				else	nwcnt=0;

			}
			if(nwcnt>=BAD_IMG_HEIGHT-5)
				return 0;
		}
	}
	else{
		for(int i=BAD_IMG_WIDTH*0.5;i>10;i--){
			nwcnt = 0;
			for(int j=0;j<BAD_IMG_HEIGHT;j++){
				if(*(fm+j*BAD_IMG_WIDTH+i) > dsum-20)nwcnt++;
				else	nwcnt=0;

			}
			if(nwcnt>=BAD_IMG_HEIGHT-5)
				return 0;
		}
	}


	return nRet;
}

int CInspect::FullLineSearch3(CData *pData)//무지에 에지만 찾는다.
{
	//Full Image에 대한 에지 검색 Projection Data 사용
	int nstart=10,nend=CAM_WIDTH_CIS*3;
	int ngap = 6,ngap2=14;
	pData->m_nFoilEdge[0] = pData->m_nFoilEdge[1] = 0;
	//먼저 무지와 코팅 부만 구분한다
	int nEdgeth = 55,nWhitev1 = pData->m_nCoatBright,nTol=2;//param
	int nMinLineWidth = pData->m_nMinLineWidth;
	int nMinLineWidth1 = pData->m_nMinLineWidthMid;
	int nLineJump = 0,ntmp=0;
	int nCam = 0,nMax=0,nc1=0,nRoiCount=0,nlinecount=0,noldcam=0,npos1 = 0;
	double dpos1= 0;
	nEdgeth = 30;//pData->m_dThUp[0];//sparam1
	if(pData->m_bAutoEdge && pData->m_nEdgeAverage[0]>10)
		nEdgeth = pData->m_nEdgeAverage[0];
	if(nEdgeth>180)
		nEdgeth = 160;
//	nEdgeth = 20;
	int nOffset1 = 15;
	int nOffset2 = 20;//200 //@chcho0821 중앙 좁은 무지폭 투입관련
	BOOL bAve=TRUE;
	int nAve = 0,ncunt1=0,nc2[3]={0,};
	if(nstart <2300)nstart = 2300;//limit inspect range
	if(nend>CAM_WIDTH_CIS*3-2300)nend = CAM_WIDTH_CIS*3-2300;//limit inspect range
	if(pData->m_bAutoCoatBrightness)
		nWhitev1 = pData->m_nCoatAveBrightness;
	//	if(pData->m_nCoatAveBrightness<)
	BOOL bPing = FALSE;
	int nWhitelimit = pData->m_nMinLineWidth;
	for(int x=nstart;x<nend-(ngap*2);x++){
		if(bAve==TRUE &&pData->m_nFullImageProj[x-12]<nWhitev1&&pData->m_nFullImageProj[x-4]<nWhitev1&&pData->m_nFullImageProj[x-8]<nWhitev1 && abs(pData->m_nFullImageProj[x]-pData->m_nFullImageProj[x+ngap]) >= nEdgeth&& abs(pData->m_nFullImageProj[x+1]-pData->m_nFullImageProj[x+ngap+1])>= nEdgeth )
		{//black 조건  왼쪽이 어두움 //제일 처음 여기로 들어옴

			nMax = 0;
			for(int k=x-4;k<x+6;k++){//에지 주위 가장 강한 에지를 구한다
				if(k<10)k=10;if(k>=nend-ngap2)break;
				ntmp = abs(pData->m_nFullImageProj[k]-pData->m_nFullImageProj[k+2]);
				if(ntmp >= nMax){npos1 = k+nTol;	nMax = ntmp;}
			}
			int nc21 = 0,nmax1=0;
			double dedge1 = 0,npos11=0;

			if(pData->m_nFoilEdge[0]==0)
				pData->m_nFoilEdge[0] = npos1;
			else
				pData->m_nFoilEdge[1] = npos1;
			break;
		}
	}
	for(int x=nend-(ngap*2);x>nstart+(ngap*2);x--){
		if(pData->m_nFullImageProj[x+12]<nWhitev1 && abs(pData->m_nFullImageProj[x]-pData->m_nFullImageProj[x+ngap]) >= nEdgeth&& abs(pData->m_nFullImageProj[x+1]-pData->m_nFullImageProj[x+ngap+1])>= nEdgeth )
		{//black 조건  왼쪽이 어두움 //제일 처음 여기로 들어옴
			nMax = 0;
			for(int k=x-4;k<x+6;k++){//에지 주위 가장 강한 에지를 구한다
				if(k<10)k=10;if(k>=nend-ngap2)break;
				ntmp = abs(pData->m_nFullImageProj[k]-pData->m_nFullImageProj[k+2]);
				if(ntmp >= nMax){npos1 = k+nTol;	nMax = ntmp;}
			}
			int nc21 = 0,nmax1=0;
			double dedge1 = 0,npos11=0;

			if(pData->m_nFoilEdge[0]==0)
				pData->m_nFoilEdge[0] = npos1;
			else
				pData->m_nFoilEdge[1] = npos1;
			break;
		}
	}

	return nAve;
}

int CInspect::GetSplitImgRoiFindNew(BYTE* fm, CData* pData,int nCam,int nIdx,int nMod)//Edge detect, AverageBrightness, FullImageProfileData[x], ROI Set
{
	//defect count duration.
	int nCount = 10;
	int nw = CAM_WIDTH_CIS*3;
	int nh = CAM_HEIGHT_CIS;
	int nstt = 0,nend = nh;
	if( nIdx==0)
		nstt=0,nend = nh/nMod;
	else 
		nstt = (nh/nMod)*(nIdx),nend=(nh/nMod)*(nIdx+1); 

	CRect rtInspect[40];
	for(int i=0;i<40;i++){
		rtInspect[i] = pData->m_rtNewInspect[i];
		rtInspect[i].InflateRect(-5,0);
	}
	int nroicnt = pData->m_nNewLineCount;//pData->m_nLineCount1[nCam];//m_nRoiDount[nCam];
	BOOL bScratch = FALSE;

	int nindex = nIdx;
	int nh1 = nh/nMod;
	int x1 = 0,x2= 0;//검사영역
	//	int x1 = pData->m_rectIns[0].left,x2= pData->m_rectIns[0].right;//검사영역
	CString str,str1;
	if(nIdx<0 || nh1<0 || nw<1  || nend-nstt==0)
		return 0;

	int ntmp = 0,nmin=10000,nmax=0,ntmp1=0,ntmp2=0;
	double *dWidth1;
	double *dWidth2;
	dWidth1=(double*)malloc(nw*sizeof(double));//Split Image Projection Data
	dWidth2=(double*)malloc(nw*sizeof(double));//Split Image Projection Data
	for(int i=0;i<nw;i++) dWidth1[i]=dWidth2[i]=0;

	int nIgnore = 4,nRisingV = 15;//pixel 이상은 제외시킨다.
	BOOL bFallingCheck = FALSE;
	double dcount11 = 0;
	x1 = 0+1000;x2=CAM_WIDTH_CIS*3-1000;//CAM_WIDTH_16384;

	//base projection data
	for(int y=nstt;y<nend;y+=2){
		for(int x=x1;x<x2;x++){
			dWidth1[x] += *(fm+y*nw+x);
// 			if(bScratch)
// 				dWidth2[x] += *(m_fmPreprocess[nCam]+y*nw+x);			
		}
		dcount11++;
	}
	//	;
	for(int x=x1;x<x2;x++)	{
		dWidth1[x]/=dcount11;
// 		if(bScratch)
// 			dWidth2[x]/=dcount11;
	}

	int nGap = 6,nGap1 = 32;//4pixel의 gap을 본다.
	int nX11 = x1+nGap1+1,nX22 = x2-nGap1*2;
	BOOL bAve = FALSE;
	int nEdgeth = 18,nMax=0,nMin=255,npos1=0,npos2=0,nc1=0,nOffset=100;

	//main edge에서만 찾게 수정ㅎㄴ다.
	int nPosition1 = 0;
	int nTol = pData->m_nGl4BlackValue1[0];//sparam4
	int nWth1 = 50;//백->백
	int nWth2 = pData->m_nThBlack3;//백-흑//아일랜드
	int nBth1 = pData->m_nThWhite3;//흑-백//핀홀
	int nBth2 = 50;//흑-흑
	CPoint ptDefect[50];
	int nDefect = 0,nPeak1=0,nPeak2=0,nAverage=0;
	CRect rtdefect[50],rtsize[50];
	int defectx = BAD_IMG_WIDTH*0.5;
	int defecty = BAD_IMG_HEIGHT*0.5;
	CRect rtPos[40];
	for(int i=0;i<40;i++)
		rtPos[i].SetRect(0,0,0,0);
	int nJump = 0;
	double dParamScratch = pData->m_dLineScratch;//라인

	double dscalex = pData->m_dScaleFactorX[0],dscaley = pData->m_dScaleFactorY[0];
	double dPeakData[10] = {0,};//0 라인 1 코팅 백 2코팅흑 3 무지백 4 무지흑
	dPeakData[3] =dPeakData[1] = 255;

	//roi별 검사
	int nbwcheck = 0;//0 coating 1 nulling
	int nSelectBright = 180;//무지인지 코팅인지 확인  밝기가 올가가거나 낮아질경우 문제 발생 소지 있음.
	if(pData->m_dAvgBrightness[0]>100)
		nSelectBright = 220;
	else if(pData->m_dAvgBrightness[0]>50)
		nSelectBright = 180;
	else if(pData->m_dAvgBrightness[0]>30)
		nSelectBright = 150;
	else 
		nSelectBright = 100;
	int nDefectCnt[MAX_CAMERAS] = {0,};
	int nCandidateCount = 0;
	bool bcoat = FALSE;//false 무지 true 코팅
	for(int k=0;k<nroicnt;k++){
		if(nDefect>=14)		break;
		if(rtInspect[k].Width()<60)continue;
		for(int y=nstt;y<nend;y+=2){
			if(nDefect>=14)		break;
			if(nCandidateCount>30)
				break;
			nJump = 0;
			for(int x = rtInspect[k].left;x<rtInspect[k].right-4;x+=2){//roi 만큼만
				if(x<5 || x> CAM_WIDTH_CIS*3-10)continue;
				if(y<0 || y> CAM_HEIGHT_CIS-1)continue;
				if(pData->m_nKillFunction[0]==1)
					goto done;//return;
				if(x==rtInspect[k].left && x+8 <rtInspect[k].right-4){

					if(k%2==0)
						nbwcheck=1;//무지면
					else
						nbwcheck = 0;//@@chcho 191031 1로 되어 있는거 수정  //코팅면
				}
				ntmp = pData->m_nFullImageProj[x]-*(fm+y*nw+x);//전체 프로파일 데이터를 사용한다.//				ntmp = dWidth1[x]-*(fm+y*nw+x);//
				//sc 검사 먼저
				if(bScratch){
					if( y==nstt && x <rtInspect[k].right && fabs(dWidth1[x]-dWidth1[x+4]) > dPeakData[0])dPeakData[0] = fabs(dWidth1[x]-dWidth1[x+4]);
					if(	nbwcheck==1 ){//화이트검사 무지부 //흑만 검색  음수값//백색 불량
						if(ntmp<dPeakData[3])dPeakData[3] = ntmp;//코팅백
						if(ntmp>dPeakData[4])dPeakData[4] = ntmp;//코팅흑
					}
					else{
						if(ntmp<dPeakData[1])dPeakData[1] = ntmp;//코팅백
						if(ntmp>dPeakData[2])dPeakData[2] = ntmp;//코팅흑

					}
				}


				//				if(!pData->m_bPreprocessing && nbwcheck==0 &&dWidth1[x+4] <rtInspect[k].right &&        fabs(dWidth1[x]-dWidth1[x+4]) > dParamScratch){
				if(k%1==0 &&bScratch && !pData->m_bPreprocessing && nbwcheck==0 && y==nstt && x <rtInspect[k].right &&        fabs(dWidth1[x]-dWidth1[x+4]) > dParamScratch){
//					nCandidateCount++;
					for(int nn=0;nn<nDefect;nn++){
						if(x>rtPos[nn].left && x<rtPos[nn].right && y>rtPos[nn].top&& y<rtPos[nn].bottom){
							nJump = 1;
							if(nJump){
								x+= 64;
								break;;
							}
						}
					}
					if(nJump==1)continue;
					rtdefect[nDefect].SetRect(x-defectx,nstt,x+defectx,nend);//Line 불량 Y 라인 축소
					pData->m_dLineEdgeValue2[nCam][nIdx][nDefect] = fabs(dWidth2[x]-dWidth2[x+4]);
					CRect rttmp;
					rttmp = rtdefect[nDefect];
					rtdefect[nDefect] = SetBoundary1(rtdefect[nDefect],CRect(rtInspect[k].left,1,rtInspect[k].right,CAM_HEIGHT_CIS-1));
					//							ImageSelect	Copy2(pImage->GetImagePtr(),pData->m_pImageDefect1[nCam][nDefect]->GetImagePtr(),CAM_WIDTH_CIS,CAM_HEIGHT_CIS,rttmp.left,rttmp.right,rttmp.top,rttmp.bottom,BAD_IMG_WIDTH,BAD_IMG_HEIGHT,0,0);
					pData->m_rtThreadDefect[nCam][nIdx][nDefect] = rtdefect[nDefect];
					pData->m_nNewDefectColor[nCam][nIdx][nDefect] = 2;//코팅라인 white
					pData->m_nNewLineColor[nCam][nIdx][nDefect] = 2;
					pData->m_rtLineSlopeCount[nCam][nIdx][nDefect] = rtdefect[nDefect];
					pData->m_nLineSlopeCount[nCam][nIdx]++;

					rtPos[nDefect] = rtdefect[nDefect];
					rtPos[nDefect].InflateRect(64,128);
					nDefect++;
					//					}
					x+= 64;
				}
				else if(k%1==0 &&bScratch && pData->m_bPreprocessing && y==nstt && x <rtInspect[k].right &&        fabs(dWidth2[x]-dWidth2[x+4]) > dParamScratch){
//					nCandidateCount++;
					if(nbwcheck==1 && x >= rtInspect[k].right-5)
						continue;
					for(int nn=0;nn<nDefect;nn++){
						if(x>rtPos[nn].left && x<rtPos[nn].right && y>rtPos[nn].top&& y<rtPos[nn].bottom){
							nJump = 1;
							if(nJump){
								x+= 64;
								break;;
							}
						}
					}
					if(nJump==1)
						continue;

					//					rtdefect[nDefect].SetRect(x-defectx,y-defecty,x+defectx,y+defecty);
					rtdefect[nDefect].SetRect(x-defectx,nstt,x+defectx,nend);//Line 불량 Y 라인 축소
					pData->m_dLineEdgeValue2[nCam][nIdx][nDefect] = fabs(dWidth2[x]-dWidth2[x+4]);

					CRect rttmp;
					rttmp = rtdefect[nDefect];
					rtdefect[nDefect] = SetBoundary1(rtdefect[nDefect],CRect(rtInspect[k].left-50,1,rtInspect[k].right+50,CAM_HEIGHT_CIS-1));
					//							ImageSelect	Copy2(pImage->GetImagePtr(),pData->m_pImageDefect1[nCam][nDefect]->GetImagePtr(),CAM_WIDTH_CIS,CAM_HEIGHT_CIS,rttmp.left,rttmp.right,rttmp.top,rttmp.bottom,BAD_IMG_WIDTH,BAD_IMG_HEIGHT,0,0);
					pData->m_rtThreadDefect[nCam][nIdx][nDefect] = rtdefect[nDefect];
					pData->m_nNewDefectColor[nCam][nIdx][nDefect] = 2;//코팅라인 white
					pData->m_nNewLineColor[nCam][nIdx][nDefect] = 2;
					pData->m_rtLineSlopeCount[nCam][nIdx][nDefect] = rtdefect[nDefect];
					pData->m_nLineSlopeCount[nCam][nIdx]++;

					rtPos[nDefect] = rtdefect[nDefect];
					rtPos[nDefect].InflateRect(64,128);
					nDefect++;
					//					}
					x+= 64;
				}
				else if(nbwcheck==1 || k%2==0){//화이트검사 무지부 //흑만 검색  음수값
					if(ntmp < -nWth1){//백색 불량
					}
					else if(ntmp > nWth2){//흑색 불량
						nCandidateCount++;

						for(int nn=0;nn<nDefect;nn++){
							if(x>rtPos[nn].left && x<rtPos[nn].right && y>rtPos[nn].top&& y<rtPos[nn].bottom){
								nJump = 1;
								if(nJump){
									x+= 64;
									break;;
								}
							}
						}
						if(nJump==1)continue;
						rtdefect[nDefect].SetRect(x-defectx,y-defecty,x+defectx,y+defecty);
						CRect rttmp;
						rttmp = rtdefect[nDefect];
						rttmp = SetBoundary1(rttmp,m_rtBound);
						nCam = x/CAM_WIDTH_CIS;
						pData->m_dLineEdgeValueFull[nIdx][nDefect] = abs(ntmp);
						rtdefect[nDefect] = SetBoundary1(rtdefect[nDefect],CRect(rtInspect[k].left,1,rtInspect[k].right,CAM_HEIGHT_CIS-1));
						//						rtsize[nDefect] = CheckDefect1(nCam,fm,pData,rtdefect[nDefect],nDefect,0,0,nWth2,&nPeak1,&nPeak2,&nAverage);//npos 0 무지 1코팅
						rtsize[nDefect] = CheckDefect3(nCam,fm,pData,rtdefect[nDefect].left,rtdefect[nDefect].right,rtdefect[nDefect].top,rtdefect[nDefect].bottom,nIdx,nDefect,0,0,nWth2,&nPeak1,&nPeak2,&nAverage);//npos 0 무지 1코팅
						if(rtInspect[k].left>rttmp.left||rtInspect[k].right<rttmp.right)rtdefect[nDefect] = rttmp;
						if((rtsize[nDefect].Width()+1)*dscalex>pData->m_dThSize[0] || (rtsize[nDefect].Height()+1)*dscaley>pData->m_dThSize[0]){
							pData->m_rtThreadDefectFull[nIdx][nDefect] = rtdefect[nDefect];
							pData->m_rtThreadSizeDefectFull[nIdx][nDefect] = rtsize[nDefect];
							pData->m_nNewDefectColorFull[nIdx][nDefect] = 1;////0 init 1Black	2White	3LineBlack	4LineWhite
							pData->m_nThreadDefectCountFull[nIdx]++;
							rtPos[nDefect] = rtdefect[nDefect];
							nDefect++;
						}
						x+= 64;
					}
				}
				else{//블랙검사 코팅명 //백색검출
					if(ntmp < -nBth1){//백색불량
						nCandidateCount++;

						for(int nn=0;nn<nDefect;nn++){
							if(x>rtPos[nn].left && x<rtPos[nn].right && y>rtPos[nn].top&& y<rtPos[nn].bottom){
								nJump = 1;
								if(nJump){
									x+= 64;
									break;
								}
							}
						}
						if(nJump==1)continue;
						CRect rttmp;
						pData->m_dLineEdgeValueFull[nIdx][nDefect] = abs(ntmp);
						rtdefect[nDefect].SetRect(x-defectx,y-defecty,x+defectx,y+defecty);
						rttmp = rtdefect[nDefect];
						rtdefect[nDefect] = SetBoundary1(rtdefect[nDefect],CRect(rtInspect[k].left,1,rtInspect[k].right,CAM_HEIGHT_CIS-1));
						rtsize[nDefect] = CheckDefect3(nCam,fm,pData,rtdefect[nDefect].left,rtdefect[nDefect].right,rtdefect[nDefect].top,rtdefect[nDefect].bottom,nIdx,nDefect,1,1,nBth1,&nPeak1,&nPeak2,&nAverage);//npos 0 무지 1코팅
						if(rtsize[nDefect].Width()<=0 || rtsize[nDefect].Height()<=0){
							x+=64;continue;
						}
						if(rtInspect[k].left>rttmp.left||rtInspect[k].right<rttmp.right)rtdefect[nDefect] = rttmp;
						if((rtsize[nDefect].Width())*dscalex>pData->m_dThSize[0] || (rtsize[nDefect].Height())*dscaley>pData->m_dThSize[0]){
							pData->m_rtThreadDefectFull[nIdx][nDefect] = rtdefect[nDefect];
							pData->m_rtThreadSizeDefectFull[nIdx][nDefect] = rtsize[nDefect];
							pData->m_nNewDefectColorFull[nIdx][nDefect] = 2;////0 init 1Black	2White	3LineBlack	4LineWhite
							pData->m_dDefectValueFull[nIdx][nDefect][0] = nPeak1;//min
							pData->m_dDefectValueFull[nIdx][nDefect][1] = nPeak2;//max
							pData->m_dDefectValueFull[nIdx][nDefect][2] = nAverage;//max

							//edge spur edge dent
							if((rtdefect[nDefect].left+rtsize[nDefect].left <rtInspect[k].left && rtdefect[nDefect].left+rtsize[nDefect].right <rtInspect[k].left) ||
								(rtdefect[nDefect].left+rtsize[nDefect].left >rtInspect[k].right && rtdefect[nDefect].left+rtsize[nDefect].right >rtInspect[k].right))
								pData->m_nNewDefectColorFull[nIdx][nDefect] = 7;////0 init 1Black	2White	3LineBlack	4LineWhite
							pData->m_nThreadDefectCountFull[nIdx]++;

							rtPos[nDefect] = rtdefect[nDefect];
							nDefect++;
						}
						x+= 64;
					}
					else if(ntmp > nBth2){//black defect
						nCandidateCount++;
						for(int nn=0;nn<nDefect;nn++){
							if(x>rtPos[nn].left && x<rtPos[nn].right && y>rtPos[nn].top&& y<rtPos[nn].bottom){
								nJump = 1;
								if(nJump){
									x+= 64;
									break;
								}
							}
						}
						if(nJump==1)continue;
						CRect rttmp;
						pData->m_dLineEdgeValueFull[nIdx][nDefect] = abs(ntmp);
						rtdefect[nDefect].SetRect(x-defectx,y-defecty,x+defectx,y+defecty);
						rttmp = rtdefect[nDefect];
						rtdefect[nDefect] = SetBoundary1(rtdefect[nDefect],CRect(rtInspect[k].left,1,rtInspect[k].right,CAM_HEIGHT_CIS-1));
						rtsize[nDefect] = CheckDefect3(nCam,fm,pData,rtdefect[nDefect].left,rtdefect[nDefect].right,rtdefect[nDefect].top,rtdefect[nDefect].bottom,nIdx,nDefect,1,1,nBth1,&nPeak1,&nPeak2,&nAverage);//npos 0 무지 1코팅
						if(rtsize[nDefect].Width()<=0 || rtsize[nDefect].Height()<=0){
							x+=64;continue;
						}
						if(rtInspect[k].left>rttmp.left||rtInspect[k].right<rttmp.right)rtdefect[nDefect] = rttmp;
						if((rtsize[nDefect].Width())*dscalex>pData->m_dThSize[0] || (rtsize[nDefect].Height())*dscaley>pData->m_dThSize[0]){
							pData->m_rtThreadDefectFull[nIdx][nDefect] = rtdefect[nDefect];
							pData->m_rtThreadSizeDefectFull[nIdx][nDefect] = rtsize[nDefect];
							pData->m_dDefectValueFull[nIdx][nDefect][0] = nPeak1;//min
							pData->m_dDefectValueFull[nIdx][nDefect][1] = nPeak2;//max
							pData->m_dDefectValueFull[nIdx][nDefect][2] = nAverage;//max
							pData->m_nNewDefectColorFull[nIdx][nDefect] = 1;////0 init 1Black	2White	3LineBlack	4LineWhite
							pData->m_nThreadDefectCountFull[nIdx]++;

							rtPos[nDefect] = rtdefect[nDefect];
							nDefect++;
						}
						x+= 64;
					}
				}
				if(nDefect>=15)			break;
				if(pData->m_nKillFunctionFull[nIdx]==1)
					goto done;//return;
			}
			if(nDefect>=14)		break;
		}
		if(nDefect>=14)		break;
	}
done:
	for(int i=0;i<5;i++)
		pData->m_dAverageData1Full[nIdx][i] = dPeakData[i];
	if(dWidth1) free(dWidth1);
	if(dWidth2) free(dWidth2);
	return 0;
}

CRect CInspect::CheckDefect3(int nCam,BYTE* fmsrc,CData *pData,int l,int r,int t,int b,int nIdx,int ndefectcnt,int nPos,BOOL bColor,int nTh1,int *nPeakb,int *nPeakw,int *nave1)//npos 0 무지 1코팅
{
	CRect rtsize,rtDefect;
	rtDefect.SetRect(l,t,r,b);
	rtsize.SetRect(0,0,0,0);
	int nIndex = nIdx;//pData->m_nRealDefectCount;
	BYTE * fmdefect = new BYTE[BAD_IMG_WIDTH*BAD_IMG_HEIGHT];//pData->m_pImageDefect[0][nIdx]->GetImagePtr();//new BYTE[BAD_IMG_WIDTH*BAD_IMG_HEIGHT];
	memset(fmdefect,0,BAD_IMG_WIDTH*BAD_IMG_HEIGHT);
	unsigned char* fmtmp1 =	new BYTE[BAD_IMG_WIDTH*BAD_IMG_HEIGHT];
	memset(fmtmp1,0,BAD_IMG_WIDTH*BAD_IMG_HEIGHT);
	int nw1 = CAM_WIDTH_CIS*3;
	ImageSelectCopy2(fmsrc,fmdefect,nw1,CAM_HEIGHT_CIS,l,r,t,b,BAD_IMG_WIDTH,BAD_IMG_HEIGHT,0,0);
	// stdev 를 위한 변수
	int nTotalCnt = 0;
	int nAve = 0;
	int nsum = 0,nsum1 = 0;
	double dstd = 0;
	int nTh = nTh1;
	int nPeakb1=1000,nPeakw1=0;
	if(bColor){
		for(int y=0;y<BAD_IMG_HEIGHT;y++){
			for(int x=0;x<BAD_IMG_WIDTH;x++){
				nTh = int(pData->m_nFullImageProj[rtDefect.left+x] +nTh1);
				if(y==0 || y==BAD_IMG_HEIGHT-1||x==0 || x==BAD_IMG_WIDTH-1)	*(fmtmp1+y*BAD_IMG_WIDTH+x) = 0;
				else if(*(fmsrc+(y+t)*nw1+x+l)>nTh)	
					*(fmtmp1+y*BAD_IMG_WIDTH+x) = 255;
				else									
					*(fmtmp1+y*BAD_IMG_WIDTH+x) = 0;
				nAve += *(fmsrc+(y+t)*nw1+x+l);
				if(*(fmsrc+(y+t)*nw1+x+l)-pData->m_nFullImageProj[rtDefect.left+x]> nPeakw1)nPeakw1 = *(fmsrc+(y+t)*nw1+x+l)-pData->m_nFullImageProj[rtDefect.left+x];
				if(pData->m_nFullImageProj[rtDefect.left+x]-*(fmsrc+(y+t)*nw1+x+l)< nPeakb1)nPeakb1 = pData->m_nFullImageProj[rtDefect.left+x]-*(fmsrc+(y+t)*nw1+x+l);
			}
		}
	}
	else{
		for(int y=0;y<BAD_IMG_HEIGHT;y++){
			for(int x=0;x<BAD_IMG_WIDTH;x++){
				nTh = int(pData->m_nFullImageProj[rtDefect.left+x] - nTh1);
				if(y==0 || y==BAD_IMG_HEIGHT-1||x==0 || x==BAD_IMG_WIDTH-1)	*(fmtmp1+y*BAD_IMG_WIDTH+x) = 0;
				else if(*(fmsrc+(y+t)*nw1+x+l)<nTh)
					*(fmtmp1+y*BAD_IMG_WIDTH+x) = 255;
				else										*(fmtmp1+y*BAD_IMG_WIDTH+x) = 0;
				nAve += *(fmsrc+(y+t)*nw1+x+l);
				if(*(fmsrc+(y+t)*nw1+x+l)-pData->m_nFullImageProj[rtDefect.left+x]> nPeakw1)nPeakw1 = *(fmsrc+(y+t)*nw1+x+l)-pData->m_nFullImageProj[rtDefect.left+x];
				if(pData->m_nFullImageProj[rtDefect.left+x]-*(fmsrc+(y+t)*nw1+x+l)< nPeakb1)nPeakb1 = pData->m_nFullImageProj[rtDefect.left+x]-*(fmsrc+(y+t)*nw1+x+l);
			}
		}
	}
	nAve /= (BAD_IMG_HEIGHT*BAD_IMG_WIDTH);
	*nave1 = nAve;
	*nPeakb = nPeakb1;
	*nPeakw = nPeakw1;
	//	return rtsize;

	double dTemp,dBlobSize;
	int  nBlobCount =-1, nBlobNo =0;
	CRect rtBlob;
	//거리를 측정하기위한 param
	double dCx, dCy, dAngle, dPos[4][2], dShortLength, dLongLength,dMin,dMax,dAve;
	double dLengTemp,dLengTemp1,dLengTemp2,dPeriment,dx1,dy1,dcompact;
	double dlongLine = 0.0;
	//defect 개수가 1개로 저의 되어 있음. 수정 필요.
	dBlobSize =  0.0;
	int nVisionLine = pData->m_nVisionLine;

	m_pChainFull[nIndex]->SetChainData(1,fmtmp1,2,1,2,100000,BAD_IMG_WIDTH,BAD_IMG_HEIGHT);
	nBlobCount = m_pChainFull[nIndex]->FastChain(0, 0, BAD_IMG_WIDTH-1,BAD_IMG_HEIGHT-1);
	for(int i=0;i<nBlobCount;i++)
	{
		dTemp = m_pChainFull[nIndex]->Chain_Area(i);//FChain_Area(i, &dTemp);//			ttt
		if(dTemp<2)continue;
		if(dTemp>=dBlobSize)//최대 불량 사이즈.
		{
			nBlobNo = i;
			dBlobSize = dTemp;//면적
		}
	}
// 	if(pData->m_nRealDefectCount1[nCam]>=14){
// 		delete fmtmp1;
// 		delete fmdefect;
// 		return rtsize;
// 	}
	if(nBlobCount>0){
		rtsize.SetRect(m_pChainFull[nIndex]->FindMinX(nBlobNo),m_pChainFull[nIndex]->FindMinY(nBlobNo),m_pChainFull[nIndex]->FindMaxX(nBlobNo),m_pChainFull[nIndex]->FindMaxY(nBlobNo));
		dx1 = rtsize.Width()+1;// * pData->m_dScaleFactorX[nCam]*pData->m_nRecude;
		dy1 = rtsize.Height()+1;// *pData->m_dScaleFactorY[nCam]*pData->m_nRecude;	
		if(dx1>pData->m_dDefectSize || dy1>pData->m_dDefectSize){

		}
	}

	//	dx1 = (FChain_FindMaxX(nBlobNo) - FChain_FindMinX(nBlobNo)) * pData->m_dScaleFactorX[nCam]*pData->m_nRecude;
	//	dy1 = (FChain_FindMaxY(nBlobNo) - FChain_FindMinY(nBlobNo)) *pData->m_dScaleFactorY[nCam]*pData->m_nRecude;	
	//장축 구하기.
	// 	FChain_Center(nBlobNo, &dCx, &dCy);
	// 	FChain_FindAngle(nBlobNo, &dAngle);
	// 	FChain_FindMinRect(nBlobNo, dCx, dCy, dAngle, dPos);  //Blob을 포함하는 최소 사각형 구하는 함수
	// 	FChain_FineDistFromPoint(nBlobNo, dCx,dCy, &dMin, &dMax, &dAve);
	// 	FChain_FindCompactness(nBlobNo,&dcompact);
	// 	FChain_Perimeter(nBlobNo,&dPeriment);
	// 	dShortLength=sqrt( (dPos[0][0]-dPos[1][0])*(dPos[0][0]-dPos[1][0])+(dPos[0][1]-dPos[1][1])*(dPos[0][1]-dPos[1][1])); 
	// 	if(dShortLength<1 || dShortLength>1000) dShortLength=1;
	// 	dLongLength=sqrt( (dPos[2][0]-dPos[1][0])*(dPos[2][0]-dPos[1][0])+(dPos[2][1]-dPos[1][1])*(dPos[2][1]-dPos[1][1]));
	// 	if(dLongLength<1 || dLongLength>1000)  dLongLength=1;
	// 	rtsize.SetRect(FChain_FindMinX(nBlobNo),FChain_FindMinY(nBlobNo),FChain_FindMaxX(nBlobNo),FChain_FindMaxY(nBlobNo));


	delete fmtmp1;
	delete fmdefect;
	return rtsize;
}
void CInspect::GetLineDataSortNew(BYTE * fm, CData* pData,int nCam,int nFrame)
{
	//Condidate Peak Brightness Check //4x4 mesh 단위 불량 선별
	int nw = CAM_WIDTH_CIS*3;
	int nh = CAM_HEIGHT_CIS;
	CRect rt;
	BOOL bColor[10],bping = FALSE;//False=white true=black
	int nMax = 0,nMin=0,nMax1 = 0,nMin1=0,nIndex = 0,npeak=0;
	int nMeshDefect = 0;
	int nVisionLine = pData->m_nVisionLine;
	pData->m_dAveRealBright[nCam] ;
	int nBright1 = 60;
	int nBright2 = 80;
	int nCandiCount1 = 0;//


	double dave=0,dcnt=0,dtmp=0;
	int nMode = 2,minpos=0,maxpos=0;
	double dmin=0,dmax=0,dsortdata[MOD_COUNT];
	int nDataNo[MOD_COUNT];
	for(int o=0;o<MOD_COUNT;o++){
		dsortdata[o]=0;nDataNo[o] = 0;}
	int nCalPos = 0;
	int nMaxDefect = 38;
	double doffsetScale = pData->m_dScaleFactorX[nCam];
	if(nMode==1){

	}
	else if(nMode==2){
		//edge count compare 
//		if(pData->m_nLineEdgeCount1[nCam][0] ==pData->m_nLineEdgeCount1[nCam][1] && pData->m_nLineEdgeCount1[nCam][0] ==pData->m_nLineEdgeCount1[nCam][2]&&pData->m_nLineEdgeCount1[nCam][0] ==pData->m_nLineEdgeCount1[nCam][3])
		{
			double dx1,dy1,dsize;
			for(int ss=0;ss<8;ss++){
				int nDefectCount1 = 0;
				if(nDefectCount1>=nMaxDefect)break;
				if(pData->m_nLineSlopeCount[nCam][ss]>=0){//라인 검출 불량
					if(nDefectCount1>=nMaxDefect)break;
					for(int kk=0;kk<pData->m_nLineSlopeCount[nCam][ss];kk++){
						CRect rtsc;
						rtsc = pData->m_rtLineSlopeCount[nCam][ss][kk]; //Y 축으로 3배 큰 이미지
						rtsc.InflateRect(0,128,0,-128);
						if( pData->m_rtLineSlopeCount[nCam][ss][kk].Width()<BAD_IMG_WIDTH)
							continue;
						pData->m_rectDefect[nCam][nDefectCount1] = rtsc;//pData->m_rtLineSlopeCount[nCam][ss][kk];//pData->m_rtThreadDefect[nCam][ss][kk];
						rtsc = pData->m_rtLineSlopeCount[nCam][ss][kk]; //Y 축으로 3배 큰 이미지
						pData->m_nDefectVMax[nCam][nDefectCount1] = pData->m_dLineEdgeValue2[nCam][ss][kk];

						ImageSelectCopyScratch1(fm,pData->m_pImageDefect1[nCam][nDefectCount1]->GetImagePtr(),CAM_WIDTH_CIS,CAM_HEIGHT_CIS,rtsc,BAD_IMG_WIDTH,BAD_IMG_HEIGHT,0,0,3);
						pData->m_nNewDefectType[nCam][nDefectCount1] = pData->m_nNewLineColor[nCam][ss][kk]*100+1;//101;//무지라인 201코팅라인 1번더미
						double dsizex,dsizey,dsize;
						nDefectCount1++;
						pData->m_nRealDefectCount1[nCam]++;
						if(nDefectCount1>=15)break;
					}
				}
				if(pData->m_nThreadDefectCountFull[ss]>0){
					if(nDefectCount1>=nMaxDefect)break;
					for(int kk=0;kk<pData->m_nThreadDefectCountFull[ss];kk++){
						//
//						pData->m_nDefectVMaxFull[nDefectCount1] = pData->m_dLineEdgeValueFull[ss][kk];
//						pData->m_rectDefectFull[nDefectCount1] = pData->m_rtThreadDefectFull[ss][kk];
						CRect rtdefect1;
						rtdefect1 =  pData->m_rtThreadDefectFull[ss][kk];
						if(rtdefect1.Width()<10 ||rtdefect1.Height()<10)
							continue;

						ImageSelectCopy5(pData,fm,pData->m_pImageDefectFull[ss][kk]->GetImagePtr(),CAM_WIDTH_CIS*3,CAM_HEIGHT_CIS,rtdefect1.left,rtdefect1.right,rtdefect1.top,rtdefect1.bottom,BAD_IMG_WIDTH,BAD_IMG_HEIGHT,0,0,pData->m_nDefectMag,nCam);
						pData->m_nNewDefectTypeFull[ss][kk] = pData->m_nNewDefectColorFull[ss][kk]*1000+1;//1 init 1001Black	2001White	3001LineBlack	4001LineWhite
						if(pData->m_nNewDefectTypeFull[ss][kk]==1001){
							int nn1 = checkDragLine(pData,pData->m_pImageDefectFull[ss][kk]->GetImagePtr());
							pData->m_nNewDefectTypeFull[ss][kk] += nn1;
						}
						else if(pData->m_nNewDefectTypeFull[ss][kk]==2001){//파임과 핀홀을 구분

						}
						
						pData->m_dSizeXFull[ss][kk] = pData->m_rtThreadSizeDefectFull[ss][kk].Width() * pData->m_dScaleFactorX[nCam];
						pData->m_dSizeYFull[ss][kk] = pData->m_rtThreadSizeDefectFull[ss][kk].Height() * pData->m_dScaleFactorY[nCam];
						pData->m_dDefectValueFull[ss][kk][0];//0min 1max 2 average
						pData->m_dDefectValueFull[ss][kk][1];//0min 1max 2 average
						pData->m_dDefectValueFull[ss][kk][2];//0min 1max 2 average

						pData->m_dSizeFull[ss][kk] = pData->m_dSizeXFull[ss][kk];
						if(pData->m_dSizeXFull[ss][kk]<pData->m_dSizeYFull[ss][kk])
							pData->m_dSizeFull[ss][kk] = pData->m_dSizeYFull[ss][kk];

						if(pData->m_rtThreadSizeDefectFull[ss][kk].Width() >0 && pData->m_rtThreadSizeDefectFull[ss][kk].Height() >0 )//&& pData->m_rtThreadSizeDefect[nCam][ss][kk].Height()/pData->m_rtThreadSizeDefect[nCam][ss][kk].Width()>1 )
						{
							if(pData->m_dSizeYFull[ss][kk] > 4 && pData->m_dSizeYFull[ss][kk]/pData->m_dSizeXFull[ss][kk]>pData->m_dLineRatio){
								pData->m_nNewDefectTypeFull[ss][kk] = 3001;//pData->m_nNewDefectColor[nCam][ss][kk]*1000+1;//1 init 1001Black	2001White	3001LineBlack	4001LineWhite
								pData->m_dSizeFull[ss][kk] = pData->m_dSizeXFull[ss][kk];
							}
							else{
								//불량 사이즈 구분
								if(pData->m_nNewDefectTypeFull[ss][kk]==2001){//핀홀
									if(pData->m_dThSize[nCam]> pData->m_dSizeFull[ss][kk]){
										//양품
										continue;
									}
								}
								else if(pData->m_nNewDefectTypeFull[ss][kk]==7001){//에지덴트
									if(pData->m_dThSize[nCam]> pData->m_dSizeFull[ss][kk]){
										//양품
										continue;
									}
								}
								else if(pData->m_nNewDefectTypeFull[ss][kk]==1001){//아일랜드
									if(pData->m_dSizeParam[1]> pData->m_dSizeFull[ss][kk]){
										//양품
										continue;
									}
								}
								else if(pData->m_nNewDefectTypeFull[ss][kk]==1002){//드래그라인
									if(pData->m_dSizeParam[1]> pData->m_dSizeFull[ss][kk]){
										//양품
										continue;
									}
								}
								else{
									if(pData->m_dThSize[nCam]> pData->m_dSizeFull[ss][kk]){
										//양품
										continue;
									}
								}
							}
						}
						else
							continue;

						nDefectCount1++;
						pData->m_nRealDefectCountFull++;
						if(nDefectCount1>=15)break;
					}
				}

			}

		}
	}
	return;
}
