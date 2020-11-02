#if !defined(AFX_DATA_H__6A52D23B_F9EA_430B_9A94_0CF4D7C0902D__INCLUDED_)
#define AFX_DATA_H__6A52D23B_F9EA_430B_9A94_0CF4D7C0902D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Data.h : header file
//
#include "Image.h"

/////////////////////////////////////////////////////////////////////////////
// CData window

class CData : public CWnd
{
// Construction
public:
	CData();

// Attributes
public:
//new mode - Speed Up 여기는 Split Image에 대한 불량임으로 10개만 잡는다.
//////////////thread 8ro 대응
	CRect m_rtScratch1[MAX_CAMERAS][20];//Scratch 용 ROI
	CRect m_rtScratch2[40];//Scratch 용 ROI

	int		m_nNCoatBrightness[2];//0 좌측 무지 1 우측 무지

	double	m_dSharpness2[MAX_LENGTH];
	double	m_dGrayValue[20];//0무지 1코팅 //순서대로

	int CData::LaneCheckFull(int nCam,int xpos,int nLine,int nreverse);
	int m_nCandidateLine;
	int	m_nChangeLine[2];//0 fullline 1 3번재  라인
	int m_nWhiteParam;
	CRect	m_rtSubLine[40];
	double	m_dDefectValue[MAX_CAMERAS][MOD_COUNT][20][5];//0min 1max 2 average
	double	m_dDefectValueFull[MOD_COUNT][MAX_REALDEFECTNEW][5];//0min 1max 2 average	//new version
	double	m_dDefectValue1[MAX_CAMERAS][20][5];//0min 1max 2 average
	double	m_dAverageData[10];//0 라인 1 코팅 백 2코팅흑 3 무지백 4 무지흑
	double	m_dAverageData1[MAX_CAMERAS][MOD_COUNT][10];//0 pinhole	1island	2line
	double	m_dAverageData1Full[MOD_COUNT][10];//0 pinhole	1island	2line //new version
	int		m_nKillFunction[MAX_CAMERAS];
	int		m_nKillFunctionFull[MOD_COUNT];//new version
	int		m_nSumBadCount[6];//0 st 1 sb 2 ht 3 hb 4mt 5mb
	double	m_dSizeParam[5];//0 핀홀 1아일랜드 2라인 3드래그라인
	int		m_nEdgeOffset;
	int		m_nCamID;//0 hts 1hbs 2ht 3hb 4mt 5mb
	double		m_dDrawMisData[3][METER_10][MAX_FRAME][MAX_LENGTH];//[top back mis][meter][미터당프레임][data]
	double		m_dOffsetData[3][20];//0 pixel 1mm //data
	int		m_nMaxLane;//현재 제품 레인수
	int		m_nLimitLane;
	int		m_nCadidateEndpos;
	int		m_nLaneDefectCount[5][2];//lane   - 0 무지 1 코팅
	int		m_nDrawMeter[2];//

	int CData::FindLane(int nLine,int nreverse);
	int		m_nEpcPos;//1= left 2= right
	int		CData::LaneCheck(int nCam,int xpos,int nLine,int nreverse=0);
	int		m_nDefectLane[MAX_CAMERAS][MAX_REALDEFECT];//defect lane position
	int		m_nCoatAveBrightness;//무지 + 코팅 *0.5
	BOOL	m_bAutoCoatBrightness;
	int		m_nDefectMag;//디펙이미지 Y축 확대

	BOOL	m_bLineAverageData;//평균 라인 데이터 사용
	double	m_dAverageBrightness1[3];//전체 화면에 대한 평균(0 무지 1코팅 2 전체)
	double	m_dAverageBrightness2[3];//전체 화면에 대한 평균(0 무지 1코팅 2 전체)

	BOOL	m_bSkipFrame;

	int		m_nLanePos[MAX_LENGTH][2];//각레인별  [시작][종로] 픽셀

	BOOL	m_bAutoEdge;
	int		m_nEdgeAverage[2];//0;white 1 =black
	BOOL	m_bMasterPc;
	BOOL	m_bPreprocessing;
	int m_nFoilEdge[2];
	int m_nFoilEdgeOld[2];

	int		m_nCoatBright;
	BOOL	m_bInsulateInspect;

	CRect	m_rtMismatchChar[20];//mismatch 글자 영역
	CRect	m_rtCoatChar[20];//코팅 글자 영역
	CRect	m_rtOldCoatChar[20];//이전 글자영역
	CRect	m_rtNullingChar[20];//무지부 글자 영역
	CRect	m_rtInsulateChar[20];//절연부 글자 영역
	
	int		m_nLineSelect;//1000단위 코터, 100단위 양/음, 10단위 헤더/미스, 1단위 탑백
	CString	m_strLineSelect;//1000단위 코터, 100단위 양/음, 10단위 헤더/미스, 1단위 탑백 
	double	m_dLenthMismatch[MAX_LENGTH];
	CRect	m_rtThreadDefect[MAX_CAMERAS][8][16];
	CRect	m_rtThreadDefectFull[MOD_COUNT][MAX_REALDEFECTNEW];//new version
	CRect	m_rtThreadSizeDefect[MAX_CAMERAS][8][16];
	CRect	m_rtThreadSizeDefectFull[MOD_COUNT][MAX_REALDEFECTNEW];//new version
	int		m_nThreadDefectCount[MAX_CAMERAS][8];
	int		m_nThreadDefectCountFull[MOD_COUNT];
	CRect	m_rtinsulate[40];//절연 후보 (무지)
	CRect	m_rtinsulate1[40];//절연폭만
	int		m_nInsulateCount;//절연 개수(무지수)
	double	m_dInsulatePos[40];
//	CImage	*m_pImageThreadDefect[MAX_CAMERAS][MAX_REALDEFECT];
	double	m_dLineScratch;
	double	m_dOldLine[MAX_CAMERAS][40];
	double	m_dMisData[100][40];
	int		m_nReadCount;
	double	m_dInterpolation;
	double	m_dInterpolationPixel;

	BOOL	m_bUseCLog;

	int		m_nFullimage;

	int		m_nFullImageProj[CAM_WIDTH_CIS*3];//전체 통합 데이터
	int		m_nFullImageProj1[MOD_COUNT][CAM_WIDTH_CIS*3];//분할 데이터

	int		m_nBadTypeCount[10];//불량 종류별 카운트
	int		m_nTmpBadTypeCount[10]; // 200702 kjh
	BOOL	m_bSumEdgeData;
	double	m_dBadAlarmMeter;
	double m_dBadAlarmMismatch;//*1000) / (CAM_HEIGHT_3072*scale_y);
	double	m_dLineRatio;
	int		m_nWhiteLineCount[MAX_CAMERAS];
	int		m_nSkipWhite[2];//0 top 1bottom

	int		m_nMinLineWidth;
	int		m_nMinLineWidthMid;
	CString	m_strDefaultModel;
	double m_dLineAve[10][MAX_LENGTH];//최대 10frame의 평균
	double m_dOldLineData[MAX_CAMERAS][MAX_LENGTH];

	double	m_dMachineLength;
	double	m_dMisMatchLen[2][MAX_LENGTH];//mismatchdatainput
	double		m_nMisMatchPixel[2][MAX_LENGTH];//mismatchdatainput
	CString m_strMatchData[2][100][10];////[0]탑[1]백-100M - M당 10개 라인
	double		m_nLinePosPixel[MAX_LENGTH];//전체길이별 픽셀
	double	m_dLinePosLength[MAX_LENGTH];//전체 길이별 누적 길이
	int		m_nLinePosPixel1[MAX_LENGTH];//전체길이별 픽셀
	double	m_dLinePosLength1[MAX_LENGTH];//전체 길이별 누적 길이
	double	m_dTotalLength[2];//0 first 1end
	double	m_dMisMatchData[4][10][MAX_LENGTH];//0 length 1 TOP 2BACK, 10frame, 20lane  /3 - length mismatch
	double	m_dReversePitchData[MAX_LENGTH];
	DOUBLE		m_dReversePixelData[MAX_CAMERAS];//0 top reverse pixel
	double  m_dMisTopBackData[3][MAX_LENGTH];//0top pixel 1 back pixel  2 mismatch mm
	double  m_dMisTopBackData1[5][MAX_LENGTH];//0top pixel 1 back pixel  2 mismatch mm 3widmmtop 4 widmmback
	double  m_dMisTopBackDataOld[3][MAX_LENGTH];//0top pixel 1 back pixel  2 mismatch mm
	double	m_dMisbatchScale[2];//0top 1back
	double	m_dMisbatchScale1[2];//head 부0top 1back
	int		m_nMismatchLine;//Mismatch용 라인 수
	int		m_nMismatchLine1;//Mismatch용 head 라인 수

	double		m_nFullLineData[2][100][10][MAX_LENGTH];//Data Push용 버퍼 -탑/백 , 100미터 , 10프레임 , 최대라인수20개(0번은 총라인개수, 1번부터 라인픽셀) //마지막은 Scale을 넣는다.*1000000 
	double		m_nFullLineData1[5][100][20][MAX_LENGTH];//mis match Full Data Push용 버퍼 -탑/백 , 100미터 , 10프레임 , 최대라인수20개(0번은 총라인개수, 1번부터 라인픽셀) //마지막은 Scale을 넣는다.*1000000 
	CString		m_strFullLineData[100];//mis match Full Data Push용 버퍼 -탑/백 , 100미터 , 10프레임 , 최대라인수20개(0번은 총라인개수, 1번부터 라인픽셀) //마지막은 Scale을 넣는다.*1000000 
	int		m_nMachineLengthAB[3];//0 A chuck 1 B chuck
	int		m_nUseChuck;//0번 A 1B
	int		m_nOldChuck;//0번 A 1B
	int		m_nCamDistance;
	int		m_nSimmulationMode;
	int		m_nSubFrameCount;
	int		m_nChuckChange;
	int		m_nOldMeter;
	CString	m_strNewLot;
	CString	m_strOldLot;


	CRect	m_rtInspect[MAX_CAMERAS][40];//Defect 검사 ROI//0914
	CRect	m_rtInspect1[MAX_CAMERAS][MOD_COUNT][40];//Defect 검사 ROI//0914
	CRect	m_rtNewInspect[40];
	int		m_nRoiDount[MAX_CAMERAS];
	double	m_dDefectSize;
	int		m_nThWhite3;
	int		m_nThBlack3;
	double	m_dSlope;
	int		m_nLineSlopeCount[MAX_CAMERAS][8];
	CRect	m_rtLineSlopeCount[MAX_CAMERAS][8][40];

	int		m_nCommutyFrameCount[MAX_CAMERAS][5];
	int		m_nCommutyCountCut[MAX_CAMERAS];//프레임당 10개 이상이면 군집휘점 후보 프레임
	int		m_nCommutyFrameCountCut[MAX_CAMERAS];//7장 10장중 7장이 있으면 군집 휘점
	BOOL	m_bNotCoating[MAX_CAMERAS][MAX_COMMUTYFRAME];
	double	m_dBlackSizeSkip[MAX_CAMERAS];//4mm 이상 이물 스킵
	int		m_nComPort[MAX_CAMERAS]; // defaultport+ computername + defect code		10000 +401 * 10
	BOOL	m_bInspectComplete[MAX_CAMERAS];
	BOOL	m_bIsDispCheck;

	int		m_nLineLEngthCut;//라인길이 //20
	int		m_nLineTh1;//20
	double	m_dCalXPos[MAX_CAMERAS][CAM_WIDTH_CIS];
	int		m_nCalDummyData[MAX_CAMERAS][CAM_WIDTH_CIS];

	BOOL	m_bMiniImageCheck[MAX_CAMERAS];

	BOOL	m_bLineWrite;
	BOOL	m_bInspStart;

	double m_dLastEdge[MAX_CAMERAS];
	double	m_dCalTol[MAX_CAMERAS];

	int		m_nFullImageSaveFrame;//10장
	int		m_nMiniImageSaveFrame;//10

	int		m_nLineSumCount;//라인 누적 개수
	int		m_nLineSumTH;//라인 누적 개수

	int		m_nLineThCount;//gl4 라인 카운트
	CRect   m_rtLine[MAX_DEFECT];
	CPoint	m_ptLine[MAX_DEFECT];

	double	m_dCompactness[MAX_CAMERAS];//막뜯김 
	int		m_nPinholeValue[MAX_CAMERAS];

	int		m_nUseIndex;//SplitCount
	int		m_nCameraWidth;
	int		m_nCameraHeight;
//	int * m_nProjectX[MAX_CAMERAS];
	int		m_nProjectX[MAX_CAMERAS][CAM_WIDTH_CIS];
	int		m_nAverage[MAX_CAMERAS];
	int		m_nEdgeData[MAX_CAMERAS][MOD_COUNT];//0 Left 1 Right 2top	3bottom //use Insp Roi
	void CData::InitData(int nCam,int nw,int nh);
	CPoint	m_ptCandidate[10][MAX_DEFECT];//Max Split Count 10
	CPoint	m_ptCandidateOrigin[10][MAX_DEFECT];//Max Split Count 10
	int		m_nCandidatePointCount[10];//Max Split Count 10
	void CData::AddDefectPoint(CPoint ptreverse,CPoint ptorigin,int nIdx);
	CRect	m_rtCandidate[10][MAX_DEFECT];//split imaage에 대한 불량은 10ea
	int		m_nRealDefectCount;//mesh Area Real Defect Count 양/불 모두 포함
	int		m_nRealDefectCount1[MAX_CAMERAS];//mesh Area Real Defect Count 양/불 모두 포함
	int		m_nRealDefectCountFull;//mesh Area Real Defect Count 양/불 모두 포함	//new version
	int		m_nServerSendDefectCount;//판단후 불량에 대한 defectcount
	int		m_nMaxImageValue[MAX_CAMERAS][MOD_COUNT];//
	int		m_nMinImageValue[MAX_CAMERAS][MOD_COUNT];//
	int		m_nMaxImageLine[MAX_CAMERAS][MOD_COUNT];//
	int		m_nMinImageLine[MAX_CAMERAS][MOD_COUNT];//
	//sc용 후보
	int		m_nCandidateType[10][MAX_DEFECT];
	int		m_nCandidateScValue[10][MAX_DEFECT];
	CString m_strLot;
	int		m_nDualNotIns;
	BOOL	m_bDualNotIns;

	double	m_dTypeRatio[MAX_CAMERAS];

	int		m_nLineOVerlapV[MAX_CAMERAS];
	int		m_nRecude;

	double	m_dHooktime[MAX_CAMERAS];
	double	m_dHooktime1[MAX_CAMERAS];
	int		m_nPinholeBitTh;

	double	m_dFullTime[30];
	double m_dSaveTime[MAX_CAMERAS];

	int		m_nCommityTh[MAX_CAMERAS];//휘점 군집 th

	int		m_dWhiteCommutySize[MAX_CAMERAS][MAX_REALDEFECT];//프레임내 군집 핀홀 개수
	int		m_dWhiteCommutyCount[MAX_CAMERAS];//프레임내 군집 핀홀 개수

	int		m_nDefectThCount[MAX_CAMERAS][MAX_REALDEFECT];
	double		m_nDefectThCountPercent[MAX_CAMERAS];//X x Y *0.4 이상

	int		m_nGl4BlackValue;
	int		m_nGl4BlackValue1[MAX_CAMERAS];
	double m_dBlackSize[MAX_CAMERAS];
	double m_dBlackCandidateSize[MAX_CAMERAS];//후보사이즈

	double	m_dMaxWhiteSize[MAX_CAMERAS][MAX_REALDEFECT];//막뜯김 사이즈
	double	m_dDyespotAngle[MAX_CAMERAS][MAX_REALDEFECT];
	double m_dTempData1[MAX_CAMERAS][MAX_REALDEFECT];
	double m_dTempData2[MAX_CAMERAS][MAX_REALDEFECT];
	double m_dTempData3[MAX_CAMERAS][MAX_REALDEFECT];

////////////////////////////////  2level
	double	m_dWeakThUp[MAX_CAMERAS];
	double	m_dWeakThDn[MAX_CAMERAS];
	double	m_dWeakSize[MAX_CAMERAS];
	double	m_dWeakWhiteSize[MAX_CAMERAS];
	double	m_nSizeCheck[MAX_CAMERAS];
	double	m_dDSAngleGap[MAX_CAMERAS][2];

	int		m_nDyeSpotAngle[MAX_CAMERAS];

	BOOL	m_bUse2Level[MAX_CAMERAS];
	////mesh별 최대값 //0max 1min 2sizex 3sizey 4size 5color 6type 7posx 8posy
	///real defect infomation
	int		m_nRealDefectInfo[MAX_REALDEFECT][10];
	double	m_dSize[MAX_CAMERAS][MAX_REALDEFECT];			//이물 SIZE	(SizeX+SizeY)/2
	double	m_dSizeFull[MOD_COUNT][MAX_REALDEFECT];			//이물 SIZE	(SizeX+SizeY)/2 //new version
	double	m_dDefectLeft[MAX_CAMERAS][MAX_REALDEFECT];		//이물 위치 Left
	double	m_dDefectTop[MAX_CAMERAS][MAX_REALDEFECT];		//이물 위치 top	
	double	m_dDefectRight[MAX_CAMERAS][MAX_REALDEFECT];		//이물 위치 Right
	double	m_dDefectBottom[MAX_CAMERAS][MAX_REALDEFECT];	//이물 위치 Bottom
	double	m_dSizeX[MAX_CAMERAS][MAX_REALDEFECT];			//이물 SIZE
	double	m_dSizeY[MAX_CAMERAS][MAX_REALDEFECT];			//이물 SIZE
	double	m_dSizeXFull[MOD_COUNT][MAX_REALDEFECTNEW];			//이물 SIZE	//new version
	double	m_dSizeYFull[MOD_COUNT][MAX_REALDEFECTNEW];			//이물 SIZE //new version
	float	m_fDefectRatio[MAX_CAMERAS][MAX_REALDEFECT];
	CRect	m_rectDefect[MAX_CAMERAS][MAX_REALDEFECT];		//이물 영역
//	CRect	m_rectDefectFull[MAX_REALDEFECTNEW*8];		//이물 영역	//new version
	CImage	*m_pImageDefect[MAX_CAMERAS][MAX_REALDEFECT];
	CImage	*m_pImageDefect1[MAX_CAMERAS][MAX_REALDEFECT];
	CImage	*m_pImageDefectFull[MOD_COUNT][MAX_REALDEFECTNEW];
	CImage	*m_pImageSC;

////////////////////////////////////////////////////////////
	//Insulate Defect
 	double	m_dSizeInsulate[MAX_REALDEFECT];			//이물 SIZE	(SizeX+SizeY)/2
 	double	m_dSizeXInsulate[MAX_REALDEFECT];			//이물 SIZE
 	double	m_dSizeYInsulate[MAX_REALDEFECT];			//이물 SIZE
 	float	m_fDefectRatioInsulate[MAX_REALDEFECT];
	CRect	m_rectDefectInsulate[MAX_REALDEFECT];		//이물 영역
	CRect	m_rectDefectInsulate1[MOD_COUNT][MAX_REALDEFECT];		//후보 영역
	int		m_nDefectInsulate1[MOD_COUNT];
 	CImage	*m_pImageDefectInsulate[MAX_REALDEFECT];
	int		m_nInsulateDefectCount;

	CImage	*m_pImageLine;
	int		m_nLineReduce;//32배압축

	int		m_nBlobCount[MAX_CAMERAS][MAX_REALDEFECT];

	//Marking BroadCasting Insert
	float fpX[MAX_CAMERAS][MAX_REALDEFECT];
	float fpY[MAX_CAMERAS][MAX_REALDEFECT];
	float fpSizeX[MAX_CAMERAS][MAX_REALDEFECT];
	float fpSizeY[MAX_CAMERAS][MAX_REALDEFECT];
	int fpDefectType[MAX_CAMERAS][MAX_REALDEFECT];//라인 종루
	int fpDefectVMax[MAX_CAMERAS][MAX_REALDEFECT];
	int fpDefectVMin[MAX_CAMERAS][MAX_REALDEFECT];
	/////CIS NewDefect Type
	int		m_nNewDefectType[MAX_CAMERAS][MAX_REALDEFECT];
	int		m_nNewDefectTypeFull[MOD_COUNT][MAX_REALDEFECTNEW];//new version
	int		m_nNewDefectColor[MAX_CAMERAS][8][MAX_REALDEFECT];//0 init 1Black	2White	3LineBlack	4LineWhite
	int		m_nNewDefectColorFull[MOD_COUNT][MAX_REALDEFECTNEW];//0 init 1Black	2White	3LineBlack	4LineWhite //new version
	int		m_nNewLineColor[MAX_CAMERAS][8][MAX_REALDEFECT];//0init	1무지라인	2코팅라인

	


	char*	m_cFilename[MAX_CAMERAS][MAX_BADIMAGE_FILENAME*MAX_REALDEFECT];
	CString m_strMachineName;
	int		m_useMarking;
	int		m_nTapeDist[MAX_CAMERAS];
	int		m_nTapeDist1[MAX_CAMERAS];
	int		m_nStdevRect[MAX_CAMERAS];
	double	m_dNewStdValue[MAX_CAMERAS];
	double	m_dNewStdGap[MAX_CAMERAS];
	double	m_dStdevV[MAX_CAMERAS][MAX_REALDEFECT];
	CString m_strDefectName[MAX_CAMERAS][MAX_REALDEFECT];
	CString m_strDefectNameFull[MOD_COUNT][MAX_REALDEFECTNEW];//new version
	CString m_strNewDefectName[MAX_CAMERAS][MAX_REALDEFECT];
	CString m_strNewDefectNameFull[MOD_COUNT][MAX_REALDEFECTNEW];//new version

	float	m_fReturnX[MAX_CAMERAS][MAX_REALDEFECT];			//서버 및 마킹에 보내주는 최종 데이타 X
	float	m_fReturnY[MAX_CAMERAS][MAX_REALDEFECT];			//서버 및 마킹에 보내주는 최종 데이타 Y
	int		m_nDefectType[MAX_CAMERAS][MAX_REALDEFECT];
	BOOL	m_bDefectWhite[MAX_CAMERAS][MAX_REALDEFECT];		//이물이 백색이물인가에 대한 플래그
	CPoint	m_ptDefect[MAX_CAMERAS][MAX_REALDEFECT];			//이물 위치
	int		m_nDefectVMax[MAX_CAMERAS][MAX_REALDEFECT];		//해당 이물 최대 밝기
	int		m_nDefectVMaxFull[MAX_REALDEFECTNEW];		//해당 이물 최대 밝기///new version
	int		m_nDefectVMin[MAX_CAMERAS][MAX_REALDEFECT];		//해당 이물 최소 밝기
	int		m_nDefectVMinFull[MAX_REALDEFECTNEW];		//해당 이물 최소 밝기	//new version
	BOOL	m_bResult[MAX_CAMERAS][MAX_REALDEFECT];		

	int		m_nBroadEdge[MAX_CAMERAS];
	int		m_nRcvEdgeData[MAX_CAMERAS];
	int		m_nGradeShutter[MAX_CAMERAS];

///*
//검사 결과
	////////////////////////////////////////////////////////////////////
	int		m_nLineMaxV[MAX_DEFECT];
	double	m_dLineValue;
	int		m_nLinePos;
	double	m_dTacEdge[MAX_CAMERAS];
	double	m_dEdgeSkipX[MAX_CAMERAS];
	int		m_nRcvEdge;
	int		m_nRcvEdge1;
	double	m_dCamWidth;
	CString	m_strCamName[MAX_CAMERAS];
	double	m_dWhiteSize;//백색 사이즈
	double	m_dCommutySize[MAX_CAMERAS];
	int		m_dCommutyCount[MAX_CAMERAS];

	BOOL	m_bSaveBmp;//1 bmp 0 jpg
	int		m_nTrembleCount[MAX_CAMERAS];
	
	int		m_nBubleSkip[MAX_CAMERAS];	//기포 Skip 
	int		m_nBlobUse[MAX_CAMERAS];						//blob use
	int     m_nBlobLimitCount[MAX_CAMERAS];
	////////////////////////////////////////////////////////////////////
	double	m_dSumSharp[MAX_CAMERAS];
	double	m_dAveSharp[MAX_CAMERAS];
	double	m_dPeakSharp[MAX_CAMERAS];
	double	m_dMinSharp[MAX_CAMERAS];

	int		m_overlapDefectCnt;
	int		m_overlapDefectPosX[40];


	CTime	m_tLastSendTime[MAX_CAMERAS];	//서버에 마지막으로 보낸 시간.
	CTime	m_tTimeCheckFrameOld[MAX_CAMERAS];//이전 LGCHEKC Time에 들어온 시간.
	CTime	m_tTimeCheckFrame[MAX_CAMERAS];//현재 LGCHEKC Time에 들어온 시간.
	int  m_nTimeCheckFrame[MAX_CAMERAS];//현재 LGCHEKC Time에 들어온 시간.
	int  m_nTimeCheckFrameOld[MAX_CAMERAS];//이전 LGCHEKC Time에 들어온 시간.
	int	 m_nLastSendTime[MAX_CAMERAS];	//서버에 마지막으로 보낸 시간.

	double	m_dOldInspTime[MAX_CAMERAS];
	int		m_nCycleUse[MAX_CAMERAS];

	double	m_dMaxMark[MAX_CAMERAS];
	int		m_nMarkCount[MAX_CAMERAS];
	int		m_nMarkValue[MAX_CAMERAS];
	int		m_edgeDetectValue[MAX_CAMERAS];

	double	m_dStrongSize[MAX_CAMERAS];


	int		m_nMachine;		//0 :연신 1:코팅.
	BOOL	m_bSharpness[MAX_CAMERAS];
	double	m_dCycleY[MAX_CAMERAS][CYCLELENGTH];
	double	m_dCycleX[MAX_CAMERAS][CYCLELENGTH];
	int		m_nLgtController;
	double	m_dSharpness1[MAX_CAMERAS];
	double	m_dCamYpos[MAX_CAMERAS][10];
	int		m_nMaxLineValue[MAX_CAMERAS];
	int		m_nMaxLinePos[MAX_CAMERAS];
	int		m_nMinLinePos[MAX_CAMERAS];
	int		m_nMinLineValue[MAX_CAMERAS];
	int		m_nColorGap[MAX_CAMERAS];
	int		m_nLv[MAX_CAMERAS];
	int		m_nRv[MAX_CAMERAS];
	int		m_nFLimitCnt[MAX_CAMERAS];
	int		m_nFMarkSkip[MAX_CAMERAS];

	double	m_dRealSpot[MAX_CAMERAS];
	double	m_dMinSizeX[MAX_CAMERAS];
	double	m_dMinSizeY[MAX_CAMERAS];
	double	m_dMaxSizeY[MAX_CAMERAS];
	double	m_dMaxSizeX[MAX_CAMERAS];
	double	m_dAveHddRemain;
	double	m_dAveFps[MAX_CAMERAS];
	double	m_dInspTime[MAX_CAMERAS];
	double	m_dInspDetailTime[MAX_CAMERAS][10];
	double	m_dCrossCandidatecnt[MAX_CAMERAS];
	double	m_dCrossGap[MAX_CAMERAS];
	double	m_dRealBrightness[MAX_CAMERAS];
	double	m_dAveThUp[MAX_CAMERAS];						//양품 평균 ThUp
	double	m_dAveThDn[MAX_CAMERAS];						//양품 평균 ThDn
	double	m_dAveRealBright[MAX_CAMERAS];				//크로스 평균 밝기
	int		m_nProjection[MAX_CAMERAS];
	double	m_pinholeLargeSize[MAX_CAMERAS];
	double	m_pinholeGroupSize[MAX_CAMERAS];
	int		m_nHistoMean[MAX_CAMERAS];
	int		m_nInsMethod[MAX_CAMERAS];
	int		m_nInspDirection[MAX_CAMERAS];
	int		m_nDefectCount[MAX_CAMERAS];					//불량 후보 모두
	int		m_nDefectResultCount[MAX_CAMERAS];			//최종 선정 불량 수
	

	double	m_dAvgBrightness[MAX_CAMERAS];				//평균 밝기
	int		m_nMinBrightness[MAX_CAMERAS];				//전체 영역중 최소 밝기
	int		m_nMaxBrightness[MAX_CAMERAS];				//전체 영역중 최대 밝기
	double	m_dSharpness[MAX_CAMERAS];					//이미지 선명도 값
	double	m_dThUp[MAX_CAMERAS];						//상향 밝기 임계치		//무라 수치값 임계치
	double	m_dThDn[MAX_CAMERAS];						//하향 밝기 임계치		//요코단 수치값 임계치
	double	m_dThSize[MAX_CAMERAS];						//불량 크기 기준 파라미터
	double	m_dThMaxSizeX[MAX_CAMERAS];					//불량의 X방향 최대 크기 --> 과검출을 막기위해 추가된 부분 07.2.15 by Sun 
	double	m_dXlineSkip[MAX_CAMERAS];					//무라 XLine Skip 부분 추가 -> MAx Ave Brightness - Min Ave Brightness 차이값
	double	m_dStdBrightness[MAX_CAMERAS];				//기준 밝기값
	double	m_dSizeSkip[MAX_CAMERAS];					//세장비 skip
	double	m_dWBThDn[MAX_CAMERAS];						//흑백 교차
	double	m_dCamDist[MAX_CAMERAS];						//스플라이스 신호후 촬상 Frame
	int		m_dRollsize[MAX_CAMERAS];					//협폭 1 광폭 0
	double		m_dEdgeBright[MAX_CAMERAS];					//정투과 사이즈 S/F
	double	m_dStartPos[MAX_CAMERAS];					// 광협폭시 시작 pos
	double	m_dEndPos[MAX_CAMERAS];						// 광협폭시 end pos
	int		m_nBCRFrame[MAX_CAMERAS];
	int		m_nTacXpos[MAX_CAMERAS];						//tac x Position
	int		m_nTapeSkipFrame[MAX_CAMERAS];
	double		m_nPolarEdge[MAX_CAMERAS];					//편광 에지점.
	double	m_dCodeDistace[MAX_CAMERAS];
	double	m_dOpticsDistanceX[MAX_CAMERAS];
	double	m_dOpticsDistanceY[MAX_CAMERAS];
	int		m_nTacLine[MAX_CAMERAS];				
	double	m_dOriginThUp[MAX_CAMERAS];
	double	m_dOriginThDn[MAX_CAMERAS];
	double	m_dOriginPenMarkV[MAX_CAMERAS];
	double	m_dDefectRatio[MAX_CAMERAS];
	int		m_nCrossInsRt[MAX_CAMERAS];
	
	CString	m_pPacketData[MAX_CAMERAS][PD_FRAME*PD_LEN];					//packetdata
	int		m_nBcrRollSize[MAX_CAMERAS];
	double	m_dMaxDistRatio[MAX_CAMERAS];
	double  m_dCrossBrightness[MAX_CAMERAS];
	void	ResetImgData(int nCam);
	BOOL	m_bBlobImg;
	BOOL	m_bCrossBlobImg[MAX_CAMERAS];
	int		m_nCrossOffset[MAX_CAMERAS];
	int		m_nUseInspArea[MAX_CAMERAS];				//자동 에지 검사 사용 미사용. 0 unuse 1 use
	int		m_nUseCInspArea[MAX_CAMERAS];			//Cross Edge Detect use

//검사 파라미터
	CString m_strComName;				//컴퓨터 이름 
	double	m_dStdDevV[MAX_CAMERAS];					//표준편차 값 - 세로 방향
	double	m_dStdDevVTh[MAX_CAMERAS];				//표준편차 임계값 - 세로 방향
	double	m_dStdDevH[MAX_CAMERAS];					//표준편차 값 - 가로 방향
	double	m_dStdDevHTh[MAX_CAMERAS];				//표준편차 임계값 - 가로 방향				
	CRect	m_rectIns[MAX_CAMERAS];					//검사 영역
	int		m_nNotInsArea[MAX_CAMERAS];				//검사하지 않는 영역 -값이면 좌측을 안하고 +값이면 우측을 검사하지 않는다.
	int		m_nExposeTime[MAX_CAMERAS];
//검사 정보
	double	m_dScaleFactorX[MAX_CAMERAS];			//Scale Factor X
	double	m_dScaleFactorY[MAX_CAMERAS];			//Scale Factor Y
	double	m_dCalibSttX[MAX_CAMERAS];				//Calibration Start X
	double	m_dCalibSttY[MAX_CAMERAS];				//Calibration Start Y

	double	m_dRectAve[MAX_CAMERAS];					//크로스용 roi Ave
	double	m_dRectMin[MAX_CAMERAS];					//크로스용 roi Min
	double	m_dRectMax[MAX_CAMERAS];					//크로스용 roi Max
//	double	m_dWeakThDn;				//정투과 약흑점 검출Param
	int		m_nLineValueCheck;
	int		m_nWeakSave[MAX_CAMERAS];
	double	m_dStdGap[MAX_CAMERAS];

//*/
	BOOL	m_bIsSepa[MAX_CAMERAS];

	int		m_nSkipCount[MAX_CAMERAS];
	int		m_nSkipPixel[MAX_CAMERAS][5];
	int		m_nSkipArea[MAX_CAMERAS][5];
	BOOL	m_bSimulation[MAX_CAMERAS];
	double	m_dAveMaxDefectBright[MAX_CAMERAS];
	double	m_dAveMinDefectBright[MAX_CAMERAS];
	double	m_dAvePenValue[MAX_CAMERAS];
	double	m_dSumMax[MAX_CAMERAS][100];
	double	m_dSumMin[MAX_CAMERAS][100];
	double	m_dSumPenV[MAX_CAMERAS][100];
//	int		m_nLineValue[MAX_CAMERAS][IMAGE_X];

	int		m_nIgnorePos[MAX_CAMERAS];	//0805 - 15
	int		m_nIgnorePixel1[MAX_CAMERAS][1000];	//0805 - 15
	int		m_nIgnorePixel[1000];	//0805 - 15
	int		m_nIgnoreRange[MAX_CAMERAS];	//0805 - 15
	/////////////////////////////////////////////////////////
	double	m_dLimitMaxBright[MAX_CAMERAS];	//Max Brightness
	double	m_dLimitMinBright[MAX_CAMERAS];	//Min Brightness
	int		m_nThWhite[MAX_CAMERAS];			//th White
	int		m_nThBlack[MAX_CAMERAS];			//th Black
	int		m_nShutter2[MAX_CAMERAS];		//2차 Shutter 값.
	int		m_nThWhiteValue[MAX_CAMERAS];	//param13
	int		m_nThBlackValue[MAX_CAMERAS];	//param14

	double	m_dCycle[MAX_CAMERAS];			//Y
	double m_dCycle300[MAX_CAMERAS];
	int		m_nCycleLimit[MAX_CAMERAS];
	int		m_nCycleCount[MAX_CAMERAS];
	int		m_nFindEdge[MAX_CAMERAS];
	int		m_nVisionLine;

	int	m_nDefaultCycle[MAX_CAMERAS][MAX_CYCLE_COUNT];
	int		m_nDefectFlag[MAX_CAMERAS][MAX_CYCLE_COUNT];
	double	m_dLastCycle[MAX_CAMERAS][MAX_CYCLE_COUNT];


	double	m_dLineEdgeData1[MAX_CAMERAS][40];//짝수 Black->White 홀수White->Black
	double	m_dLineEdgeData2[MAX_CAMERAS][MOD_COUNT][40];//짝수 Black->White 홀수White->Black
	double	m_dLineEdgeData3[MAX_CAMERAS][40];//짝수 Black->White 홀수White->Black
	double	m_dLineEdgeData4[MAX_CAMERAS][40];//짝수 Black->White 홀수White->Black
	double	m_dLineEdgeValue2[MAX_CAMERAS][MOD_COUNT][40];//짝수 Black->White 홀수White->Black
	double	m_dLineEdgeValueFull[MOD_COUNT][MAX_REALDEFECTNEW];//new version
	int			m_nLineEdgeCount1[MAX_CAMERAS][MOD_COUNT];

	int		m_nNewLineCount;
	int		m_nNewTopCount;
	double  m_dNewTopScale;
	double	m_dNewLineEdgeData1[80];//짝수 Black->White 홀수White->Black
	double	m_dNewLineEdgeData1Old[80];//짝수 Black->White 홀수White->Black
	double	m_dNewLineEdgeData11[MOD_COUNT][80];//영역별 라인수
	int		m_nOldLineCount;
	double	m_dOldLineEdgeData1[80];//짝수 Black->White 홀수White->Black
	double	m_dNewLineEdgeData2[MOD_COUNT][80];//짝수 Black->White 홀수White->Black
	double	m_dNewLineEdgeData3[80];//짝수 Black->White 홀수White->Black
	double	m_dNewLineEdgeData4[80];//짝수 Black->White 홀수White->Black


	double	m_dLineAverageData1[MAX_CAMERAS][10][40];//10frame 20개 에지

	int		m_nLineCount1[MAX_CAMERAS];
	double m_dEdgeValue1[MAX_CAMERAS][40];
	double m_dEdgeValue2[MAX_CAMERAS][40];
	double m_dEdgeValue3[MAX_CAMERAS][40];

////////////////////////////////////////////////////////////////////////////

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CData)
	public:
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	void ComputeReturnData(int nCam);
	int GetVisionLine(int nCam);
	void MoveDefectData(int nSrc, int nDest,int nCam);
	void ResetData(int nCam);
	virtual ~CData();

	// Generated message map functions
protected:
	//{{AFX_MSG(CData)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATA_H__6A52D23B_F9EA_430B_9A94_0CF4D7C0902D__INCLUDED_)
