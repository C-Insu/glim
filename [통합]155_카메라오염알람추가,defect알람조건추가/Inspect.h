// Inspect.h: interface for the CInspect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INSPECT_H__1387D31A_280C_4020_B39F_BE013B2EEADD__INCLUDED_)
#define AFX_INSPECT_H__1387D31A_280C_4020_B39F_BE013B2EEADD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "data.h"
#include "image.h"
#include "fchain.h"
//#include "FchainDll.h"
#include "VisWebDoc.h"

class CInspect  
{
public:

	/*log4cpp::Appender* syslogAppender2;
	log4cpp::Category& log4cpp_inspect;*/
	int		m_nCheckLine;//0 ok 1 2

///////////////////////////////
	int CInspect::GetSplitImgRoiFindNew(BYTE* fm, CData* pData,int nCam,int nIdx,int nMod);//Edge detect, AverageBrightness, FullImageProfileData[x], ROI Set
	CRect CInspect::CheckDefect3(int nCam,BYTE* fmsrc,CData *pData,int l,int r,int t,int b,int nIdx,int ndefectcnt,int nPos,BOOL bColor,int nTh1,int *nPeakb,int *nPeakw,int *nave1);//npos 0 무지 1코팅
	void CInspect::ImageSelectCopy5(CData* pData,unsigned char* fmSrc,unsigned char* fmDest,int nSrcW,int nSrcH,int l,int r,int t,int b,int nDestW,int nDestH,int nDestSttX,int nDestSttY,int nmag,int nCam);
	void CInspect::GetLineDataSortNew(BYTE * fm, CData* pData,int nCam,int nFrame);
	CRect m_rtBound;
	BOOL	m_bBinImage;
	void CInspect::ImageSelectCopy4(CData* pData,unsigned char* fmSrc,unsigned char* fmDest,int nSrcW,int nSrcH,int l,int r,int t,int b,int nDestW,int nDestH,int nDestSttX,int nDestSttY,int nmag,int nCam);

	int CInspect::FullLineSearch3(CData *pData);//무지에 에지만 찾는다.

	BYTE * m_fmPreprocess[MAX_CAMERAS];
// 	BYTE * m_fmPreprocess1;
// 	BYTE * m_fmPreprocess2;
// 	BYTE * m_fmPreprocess3;
	double CInspect::GetSharpness1(int nCam,CImage* pImage,CRect rt,int nWidth);

	int CInspect::FullLineSearch1(CData *pData);

	int CInspect::checkDragLine(CData *pData,BYTE* fm);

	BYTE * m_fmLine;
	BYTE * m_FullImage;
	int CInspect::FullLineSearch(CData *pData);
	void CInspect::ImageSelectCopyScratch2(unsigned char* fmSrc,unsigned char* fmDest,int nSrcW,int nSrcH,CRect rtArea,int nDestW,int nDestH,int nDestSttX,int nDestSttY,int nYOffset);
	void ImageSelectCopy3(unsigned char* fmSrc,unsigned char* fmDest,int nSrcW,int nSrcH,int l,int r,int t,int b,int nDestW,int nDestH,int nDestSttX,int nDestSttY,int nmag);

////////////////////////////////////////////////////////////Speed-up
	int CInspect::GetSplitImgRoiFind(CImage* pImage, CData* pData,int nCam,int nIdx,int nMod);//Edge detect, AverageBrightness, FullImageProfileData[x], ROI Set
	void CInspect::WriteInsLow( CData* pData,CString strLot, CString fileName, CString strdata);
	CRect CInspect::CheckDefect1(int nCam,BYTE* fmsrc,CData *pData,CRect rtDefect,int nIdx,int nPos,BOOL bColor,int nTh1,int *nPeak,int *nPeakw,int *nave1);//npos 0 무지 1코팅
	CRect CInspect::SetBoundary1(CRect rt,CRect rtlimit);
	CRect CInspect::CheckDefect2(int nCam,BYTE* fmsrc,CData *pData,int l,int r,int t,int b,int nIdx,int ndefectcnt,int nPos,BOOL bColor,int nTh1,int *nPeakb,int *nPeakw,int *nave1);//npos 0 무지 1코팅
	void CInspect::ImageSelectCopy2(unsigned char* fmSrc,unsigned char* fmDest,int nSrcW,int nSrcH,int l,int r,int t,int b,int nDestW,int nDestH,int nDestSttX,int nDestSttY);
	int CInspect::GetDefectSize(int nCam,CData *pData,BYTE * fm,int nw,int nh,int nblackwhite,int nth,double *dsizex,double *dsizey,double *dsize);
	int CInspect::GetSplitImgLineFind1(CImage* pImage, CData* pData,int nCam,int nIdx,int nMod);//Edge detect, AverageBrightness, FullImageProfileData[x], ROI Set

	int	CInspect::GetImageLineData(CImage* pImage, CData* pData,int nCam,int nEdge,CRect rtInsp);//Edge detect, AverageBrightness, FullImageProfileData[x], ROI Set
	int CInspect::GetSplitImgLineFind(CImage* pImage, CData* pData,int nCam,int nIdx,int nMod);//Edge detect, AverageBrightness, FullImageProfileData[x], ROI Set
	void CInspect::GetLineDataSort(CImage* pImage, CData* pData,int nCam,int nFrame);

	int CInspect::GetSplitInspect4(CImage* pImage, CData* pData,int nCam,int nIdx,int nMod);//Edge detect, AverageBrightness, FullImageProfileData[x], ROI Set

	void CInspect::fnDilate(LPBYTE fmSour, LPBYTE fmDest,int npitch,CRect rt,int dir) ;
	void CInspect::InitInspect(int nLine);
	void CInspect::GetLineWidthCheck(int nCam,BYTE* fmsrc,CData *pData,CRect rtDefect,int nIdx,BOOL bColor);
	int	GetImageData(CImage* pImage, CData* pData,int nCam,int nEdge,CRect rtInsp);//Edge detect, AverageBrightness, FullImageProfileData[x], ROI Set
	int CInspect::GetSplitImgData(CImage* pImage, CData* pData,int nCam,int nIdx,int nMod);//Edge detect, AverageBrightness, FullImageProfileData[x], ROI Set
	CRect CInspect::SetBoundary(CRect rt,int nwidth,int nh1,int nh2,int *nx1,int *ny1,int* nx2,int * ny2);
	void CInspect::ImageSelectCopy1(unsigned char* fmSrc,unsigned char* fmDest,int nSrcW,int nSrcH,CRect rtArea,int nDestW,int nDestH,int nDestSttX,int nDestSttY,int nReduce,BOOL bColor);

	void CInspect::ImageSelectCopyScratch(unsigned char* fmSrc,unsigned char* fmDest,int nSrcW,int nSrcH,CRect rtArea,int nDestW,int nDestH,int nDestSttX,int nDestSttY,int nYOffset);
	int CInspect::GetSplitImgScratch(CImage* pImage, CData* pData,int nCam,int nIdx,int nMod);//Edge detect, AverageBrightness, FullImageProfileData[x], ROI Set
	int CInspect::GetSplitImgScratch1(CImage* pImage, CData* pData,int nCam,int nIdx,int nMod);//Edge detect, AverageBrightness, FullImageProfileData[x], ROI Set
	int CInspect::GetSplitImgScratchNDefect(CImage* pImage, CData* pData,int nCam,int nIdx,int nMod);//Edge detect, AverageBrightness, FullImageProfileData[x], ROI Set

	int CInspect::GetSplitInspect1(CImage* pImage, CData* pData,int nCam,int nIdx,int nMod);//스플릿 데이터 이용 흑/백 찾기
	int CInspect::GetSplitInspect2(CImage* pImage, CData* pData,int nCam,int nIdx,int nMod);//전체 데이터 이용 흑/백 찾기
	int CInspect::GetSplitInspect3(CImage* pImage, CData* pData,int nCam,int nIdx,int nMod);//다이스팟용 백만 검출 후 흑여부 판다.
	void CInspect::GetDataSort(CImage* pImage, CData* pData,int nCam);
	BOOL CInspect::GetPeakValue(BYTE* fm,CData *pData,int nCam,CRect rtinsp,int * nMax,int * nMin);
	void CInspect::GetNewDefectSize(int nCam,BYTE* fmsrc,CData *pData,CRect rtDefect,int nIdx,BOOL bColor);
	void CInspect::ImageSelectCopy(unsigned char* fmSrc,unsigned char* fmDest,int nSrcW,int nSrcH,CRect rtArea,int nDestW,int nDestH,int nDestSttX,int nDestSttY);
	BOOL CInspect::DefectJudge(int nCam,CData *pData,int nIndex);

	void CInspect::WriteLog(CString strFilename,CString str);

	void CInspect::ImageSelectCopyScratch1(unsigned char* fmSrc,unsigned char* fmDest,int nSrcW,int nSrcH,CRect rtArea,int nDestW,int nDestH,int nDestSttX,int nDestSttY,int nYOffset);

////////////////////////////////////////////////////////////
	int m_nCheckProject;
	void CInspect::FindScratch5(CImage* pImage, CData* pData,int nCam);
	void	WriteLog(int nCam,CString strdata);

	CChain *m_pChain[MAX_CAMERAS][MOD_COUNT];
	CChain *m_pChainFull[MOD_COUNT];
	double	GetSharpness(CImage* pImage,  CData* pData,int nCam);
	void	GetDefectType(CData* pData,int nCam,int nIdx);
	void	SortDefectData(CData* pData,int nCam);
	BOOL	ValidDefect(CData* pData, int nIndex,int nCam);
	CPoint	FlipPoint1(CPoint point,int nCam);
	CRect	FlipRect1(CRect rect,int nCam);
	void CInspect::WriteLogIns(CString path, CString fileName, CString strdata);

	void	UpdateNGImage(CImage* pImage, CData* pData, int nDefect,int nCam);

	void UpdateNGImage1(CImage *pImage, CData *pData,int nCam,CPoint pt,int nindex);

	void	CopyBlockImg(CImage* pImgSrc, CRect rect, CImage* pImgDest,int nCam);
	void	SetResultPosFlip(CData* pData,int nCam);

	int		m_nHeight0;
	int		m_nHeight1;
	int		m_nPitch0;
	int		m_nPitch1;
	CRect	FlipRect(CRect rect,int nCam);
	CPoint	FlipPoint(CPoint point,int nCam);
	//int		m_nPitch;
	int		Inspect(CImage *pImage, CImage* pFilterImage, CImage* pOrgImage, CData* pData, CWnd* pwnd,int nCam, CVisWebDoc* pDoc);
	void	ValidRect(CRect *rect,int nCam,int nflag);;
	void	UpdateNGImage(CImage* pImage, CData* pData,int nCam);

	//////////////////////////////////////////////////////////
	int		GetStartPolarLine(unsigned char *fm,CRect rect,int nPitch,int nSkipY,int direction,int gap,int nCam);
	double	m_dRectAv[MAX_CAMERAS];
	void	FindVSlitDefect(CImage* pImage, CData* pData,int nCam);
	double	GetAveValue(unsigned char *fm, CRect rect, int nPitch, int nSkipX, int nSkipY,int nCam);
	void	FindDefectSlitArea(CImage* pImage, CData *pData,int nCam); 
//////////////////////////////////////////////////////////////////////////
	int		m_nMaxDefectBright[MAX_CAMERAS];
	int		m_nMinDefectBright[MAX_CAMERAS];
	double	m_dPenV[MAX_CAMERAS];
	int		m_nAddFrame[MAX_CAMERAS];
	int		m_nCnt[MAX_CAMERAS];

	CInspect();
	virtual ~CInspect();

private:
	CWnd*	m_pParent;	
};

#endif // !defined(AFX_INSPECT_H__1387D31A_280C_4020_B39F_BE013B2EEADD__INCLUDED_)
