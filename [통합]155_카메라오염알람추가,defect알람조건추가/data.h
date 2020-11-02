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
//new mode - Speed Up ����� Split Image�� ���� �ҷ������� 10���� ��´�.
//////////////thread 8ro ����
	CRect m_rtScratch1[MAX_CAMERAS][20];//Scratch �� ROI
	CRect m_rtScratch2[40];//Scratch �� ROI

	int		m_nNCoatBrightness[2];//0 ���� ���� 1 ���� ����

	double	m_dSharpness2[MAX_LENGTH];
	double	m_dGrayValue[20];//0���� 1���� //�������

	int CData::LaneCheckFull(int nCam,int xpos,int nLine,int nreverse);
	int m_nCandidateLine;
	int	m_nChangeLine[2];//0 fullline 1 3����  ����
	int m_nWhiteParam;
	CRect	m_rtSubLine[40];
	double	m_dDefectValue[MAX_CAMERAS][MOD_COUNT][20][5];//0min 1max 2 average
	double	m_dDefectValueFull[MOD_COUNT][MAX_REALDEFECTNEW][5];//0min 1max 2 average	//new version
	double	m_dDefectValue1[MAX_CAMERAS][20][5];//0min 1max 2 average
	double	m_dAverageData[10];//0 ���� 1 ���� �� 2������ 3 ������ 4 ������
	double	m_dAverageData1[MAX_CAMERAS][MOD_COUNT][10];//0 pinhole	1island	2line
	double	m_dAverageData1Full[MOD_COUNT][10];//0 pinhole	1island	2line //new version
	int		m_nKillFunction[MAX_CAMERAS];
	int		m_nKillFunctionFull[MOD_COUNT];//new version
	int		m_nSumBadCount[6];//0 st 1 sb 2 ht 3 hb 4mt 5mb
	double	m_dSizeParam[5];//0 ��Ȧ 1���Ϸ��� 2���� 3�巡�׶���
	int		m_nEdgeOffset;
	int		m_nCamID;//0 hts 1hbs 2ht 3hb 4mt 5mb
	double		m_dDrawMisData[3][METER_10][MAX_FRAME][MAX_LENGTH];//[top back mis][meter][���ʹ�������][data]
	double		m_dOffsetData[3][20];//0 pixel 1mm //data
	int		m_nMaxLane;//���� ��ǰ ���μ�
	int		m_nLimitLane;
	int		m_nCadidateEndpos;
	int		m_nLaneDefectCount[5][2];//lane   - 0 ���� 1 ����
	int		m_nDrawMeter[2];//

	int CData::FindLane(int nLine,int nreverse);
	int		m_nEpcPos;//1= left 2= right
	int		CData::LaneCheck(int nCam,int xpos,int nLine,int nreverse=0);
	int		m_nDefectLane[MAX_CAMERAS][MAX_REALDEFECT];//defect lane position
	int		m_nCoatAveBrightness;//���� + ���� *0.5
	BOOL	m_bAutoCoatBrightness;
	int		m_nDefectMag;//�����̹��� Y�� Ȯ��

	BOOL	m_bLineAverageData;//��� ���� ������ ���
	double	m_dAverageBrightness1[3];//��ü ȭ�鿡 ���� ���(0 ���� 1���� 2 ��ü)
	double	m_dAverageBrightness2[3];//��ü ȭ�鿡 ���� ���(0 ���� 1���� 2 ��ü)

	BOOL	m_bSkipFrame;

	int		m_nLanePos[MAX_LENGTH][2];//�����κ�  [����][����] �ȼ�

	BOOL	m_bAutoEdge;
	int		m_nEdgeAverage[2];//0;white 1 =black
	BOOL	m_bMasterPc;
	BOOL	m_bPreprocessing;
	int m_nFoilEdge[2];
	int m_nFoilEdgeOld[2];

	int		m_nCoatBright;
	BOOL	m_bInsulateInspect;

	CRect	m_rtMismatchChar[20];//mismatch ���� ����
	CRect	m_rtCoatChar[20];//���� ���� ����
	CRect	m_rtOldCoatChar[20];//���� ���ڿ���
	CRect	m_rtNullingChar[20];//������ ���� ����
	CRect	m_rtInsulateChar[20];//������ ���� ����
	
	int		m_nLineSelect;//1000���� ����, 100���� ��/��, 10���� ���/�̽�, 1���� ž��
	CString	m_strLineSelect;//1000���� ����, 100���� ��/��, 10���� ���/�̽�, 1���� ž�� 
	double	m_dLenthMismatch[MAX_LENGTH];
	CRect	m_rtThreadDefect[MAX_CAMERAS][8][16];
	CRect	m_rtThreadDefectFull[MOD_COUNT][MAX_REALDEFECTNEW];//new version
	CRect	m_rtThreadSizeDefect[MAX_CAMERAS][8][16];
	CRect	m_rtThreadSizeDefectFull[MOD_COUNT][MAX_REALDEFECTNEW];//new version
	int		m_nThreadDefectCount[MAX_CAMERAS][8];
	int		m_nThreadDefectCountFull[MOD_COUNT];
	CRect	m_rtinsulate[40];//���� �ĺ� (����)
	CRect	m_rtinsulate1[40];//��������
	int		m_nInsulateCount;//���� ����(������)
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

	int		m_nFullImageProj[CAM_WIDTH_CIS*3];//��ü ���� ������
	int		m_nFullImageProj1[MOD_COUNT][CAM_WIDTH_CIS*3];//���� ������

	int		m_nBadTypeCount[10];//�ҷ� ������ ī��Ʈ
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
	double m_dLineAve[10][MAX_LENGTH];//�ִ� 10frame�� ���
	double m_dOldLineData[MAX_CAMERAS][MAX_LENGTH];

	double	m_dMachineLength;
	double	m_dMisMatchLen[2][MAX_LENGTH];//mismatchdatainput
	double		m_nMisMatchPixel[2][MAX_LENGTH];//mismatchdatainput
	CString m_strMatchData[2][100][10];////[0]ž[1]��-100M - M�� 10�� ����
	double		m_nLinePosPixel[MAX_LENGTH];//��ü���̺� �ȼ�
	double	m_dLinePosLength[MAX_LENGTH];//��ü ���̺� ���� ����
	int		m_nLinePosPixel1[MAX_LENGTH];//��ü���̺� �ȼ�
	double	m_dLinePosLength1[MAX_LENGTH];//��ü ���̺� ���� ����
	double	m_dTotalLength[2];//0 first 1end
	double	m_dMisMatchData[4][10][MAX_LENGTH];//0 length 1 TOP 2BACK, 10frame, 20lane  /3 - length mismatch
	double	m_dReversePitchData[MAX_LENGTH];
	DOUBLE		m_dReversePixelData[MAX_CAMERAS];//0 top reverse pixel
	double  m_dMisTopBackData[3][MAX_LENGTH];//0top pixel 1 back pixel  2 mismatch mm
	double  m_dMisTopBackData1[5][MAX_LENGTH];//0top pixel 1 back pixel  2 mismatch mm 3widmmtop 4 widmmback
	double  m_dMisTopBackDataOld[3][MAX_LENGTH];//0top pixel 1 back pixel  2 mismatch mm
	double	m_dMisbatchScale[2];//0top 1back
	double	m_dMisbatchScale1[2];//head ��0top 1back
	int		m_nMismatchLine;//Mismatch�� ���� ��
	int		m_nMismatchLine1;//Mismatch�� head ���� ��

	double		m_nFullLineData[2][100][10][MAX_LENGTH];//Data Push�� ���� -ž/�� , 100���� , 10������ , �ִ���μ�20��(0���� �Ѷ��ΰ���, 1������ �����ȼ�) //�������� Scale�� �ִ´�.*1000000 
	double		m_nFullLineData1[5][100][20][MAX_LENGTH];//mis match Full Data Push�� ���� -ž/�� , 100���� , 10������ , �ִ���μ�20��(0���� �Ѷ��ΰ���, 1������ �����ȼ�) //�������� Scale�� �ִ´�.*1000000 
	CString		m_strFullLineData[100];//mis match Full Data Push�� ���� -ž/�� , 100���� , 10������ , �ִ���μ�20��(0���� �Ѷ��ΰ���, 1������ �����ȼ�) //�������� Scale�� �ִ´�.*1000000 
	int		m_nMachineLengthAB[3];//0 A chuck 1 B chuck
	int		m_nUseChuck;//0�� A 1B
	int		m_nOldChuck;//0�� A 1B
	int		m_nCamDistance;
	int		m_nSimmulationMode;
	int		m_nSubFrameCount;
	int		m_nChuckChange;
	int		m_nOldMeter;
	CString	m_strNewLot;
	CString	m_strOldLot;


	CRect	m_rtInspect[MAX_CAMERAS][40];//Defect �˻� ROI//0914
	CRect	m_rtInspect1[MAX_CAMERAS][MOD_COUNT][40];//Defect �˻� ROI//0914
	CRect	m_rtNewInspect[40];
	int		m_nRoiDount[MAX_CAMERAS];
	double	m_dDefectSize;
	int		m_nThWhite3;
	int		m_nThBlack3;
	double	m_dSlope;
	int		m_nLineSlopeCount[MAX_CAMERAS][8];
	CRect	m_rtLineSlopeCount[MAX_CAMERAS][8][40];

	int		m_nCommutyFrameCount[MAX_CAMERAS][5];
	int		m_nCommutyCountCut[MAX_CAMERAS];//�����Ӵ� 10�� �̻��̸� �������� �ĺ� ������
	int		m_nCommutyFrameCountCut[MAX_CAMERAS];//7�� 10���� 7���� ������ ���� ����
	BOOL	m_bNotCoating[MAX_CAMERAS][MAX_COMMUTYFRAME];
	double	m_dBlackSizeSkip[MAX_CAMERAS];//4mm �̻� �̹� ��ŵ
	int		m_nComPort[MAX_CAMERAS]; // defaultport+ computername + defect code		10000 +401 * 10
	BOOL	m_bInspectComplete[MAX_CAMERAS];
	BOOL	m_bIsDispCheck;

	int		m_nLineLEngthCut;//���α��� //20
	int		m_nLineTh1;//20
	double	m_dCalXPos[MAX_CAMERAS][CAM_WIDTH_CIS];
	int		m_nCalDummyData[MAX_CAMERAS][CAM_WIDTH_CIS];

	BOOL	m_bMiniImageCheck[MAX_CAMERAS];

	BOOL	m_bLineWrite;
	BOOL	m_bInspStart;

	double m_dLastEdge[MAX_CAMERAS];
	double	m_dCalTol[MAX_CAMERAS];

	int		m_nFullImageSaveFrame;//10��
	int		m_nMiniImageSaveFrame;//10

	int		m_nLineSumCount;//���� ���� ����
	int		m_nLineSumTH;//���� ���� ����

	int		m_nLineThCount;//gl4 ���� ī��Ʈ
	CRect   m_rtLine[MAX_DEFECT];
	CPoint	m_ptLine[MAX_DEFECT];

	double	m_dCompactness[MAX_CAMERAS];//����� 
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
	CRect	m_rtCandidate[10][MAX_DEFECT];//split imaage�� ���� �ҷ��� 10ea
	int		m_nRealDefectCount;//mesh Area Real Defect Count ��/�� ��� ����
	int		m_nRealDefectCount1[MAX_CAMERAS];//mesh Area Real Defect Count ��/�� ��� ����
	int		m_nRealDefectCountFull;//mesh Area Real Defect Count ��/�� ��� ����	//new version
	int		m_nServerSendDefectCount;//�Ǵ��� �ҷ��� ���� defectcount
	int		m_nMaxImageValue[MAX_CAMERAS][MOD_COUNT];//
	int		m_nMinImageValue[MAX_CAMERAS][MOD_COUNT];//
	int		m_nMaxImageLine[MAX_CAMERAS][MOD_COUNT];//
	int		m_nMinImageLine[MAX_CAMERAS][MOD_COUNT];//
	//sc�� �ĺ�
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

	int		m_nCommityTh[MAX_CAMERAS];//���� ���� th

	int		m_dWhiteCommutySize[MAX_CAMERAS][MAX_REALDEFECT];//�����ӳ� ���� ��Ȧ ����
	int		m_dWhiteCommutyCount[MAX_CAMERAS];//�����ӳ� ���� ��Ȧ ����

	int		m_nDefectThCount[MAX_CAMERAS][MAX_REALDEFECT];
	double		m_nDefectThCountPercent[MAX_CAMERAS];//X x Y *0.4 �̻�

	int		m_nGl4BlackValue;
	int		m_nGl4BlackValue1[MAX_CAMERAS];
	double m_dBlackSize[MAX_CAMERAS];
	double m_dBlackCandidateSize[MAX_CAMERAS];//�ĺ�������

	double	m_dMaxWhiteSize[MAX_CAMERAS][MAX_REALDEFECT];//����� ������
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
	////mesh�� �ִ밪 //0max 1min 2sizex 3sizey 4size 5color 6type 7posx 8posy
	///real defect infomation
	int		m_nRealDefectInfo[MAX_REALDEFECT][10];
	double	m_dSize[MAX_CAMERAS][MAX_REALDEFECT];			//�̹� SIZE	(SizeX+SizeY)/2
	double	m_dSizeFull[MOD_COUNT][MAX_REALDEFECT];			//�̹� SIZE	(SizeX+SizeY)/2 //new version
	double	m_dDefectLeft[MAX_CAMERAS][MAX_REALDEFECT];		//�̹� ��ġ Left
	double	m_dDefectTop[MAX_CAMERAS][MAX_REALDEFECT];		//�̹� ��ġ top	
	double	m_dDefectRight[MAX_CAMERAS][MAX_REALDEFECT];		//�̹� ��ġ Right
	double	m_dDefectBottom[MAX_CAMERAS][MAX_REALDEFECT];	//�̹� ��ġ Bottom
	double	m_dSizeX[MAX_CAMERAS][MAX_REALDEFECT];			//�̹� SIZE
	double	m_dSizeY[MAX_CAMERAS][MAX_REALDEFECT];			//�̹� SIZE
	double	m_dSizeXFull[MOD_COUNT][MAX_REALDEFECTNEW];			//�̹� SIZE	//new version
	double	m_dSizeYFull[MOD_COUNT][MAX_REALDEFECTNEW];			//�̹� SIZE //new version
	float	m_fDefectRatio[MAX_CAMERAS][MAX_REALDEFECT];
	CRect	m_rectDefect[MAX_CAMERAS][MAX_REALDEFECT];		//�̹� ����
//	CRect	m_rectDefectFull[MAX_REALDEFECTNEW*8];		//�̹� ����	//new version
	CImage	*m_pImageDefect[MAX_CAMERAS][MAX_REALDEFECT];
	CImage	*m_pImageDefect1[MAX_CAMERAS][MAX_REALDEFECT];
	CImage	*m_pImageDefectFull[MOD_COUNT][MAX_REALDEFECTNEW];
	CImage	*m_pImageSC;

////////////////////////////////////////////////////////////
	//Insulate Defect
 	double	m_dSizeInsulate[MAX_REALDEFECT];			//�̹� SIZE	(SizeX+SizeY)/2
 	double	m_dSizeXInsulate[MAX_REALDEFECT];			//�̹� SIZE
 	double	m_dSizeYInsulate[MAX_REALDEFECT];			//�̹� SIZE
 	float	m_fDefectRatioInsulate[MAX_REALDEFECT];
	CRect	m_rectDefectInsulate[MAX_REALDEFECT];		//�̹� ����
	CRect	m_rectDefectInsulate1[MOD_COUNT][MAX_REALDEFECT];		//�ĺ� ����
	int		m_nDefectInsulate1[MOD_COUNT];
 	CImage	*m_pImageDefectInsulate[MAX_REALDEFECT];
	int		m_nInsulateDefectCount;

	CImage	*m_pImageLine;
	int		m_nLineReduce;//32�����

	int		m_nBlobCount[MAX_CAMERAS][MAX_REALDEFECT];

	//Marking BroadCasting Insert
	float fpX[MAX_CAMERAS][MAX_REALDEFECT];
	float fpY[MAX_CAMERAS][MAX_REALDEFECT];
	float fpSizeX[MAX_CAMERAS][MAX_REALDEFECT];
	float fpSizeY[MAX_CAMERAS][MAX_REALDEFECT];
	int fpDefectType[MAX_CAMERAS][MAX_REALDEFECT];//���� ����
	int fpDefectVMax[MAX_CAMERAS][MAX_REALDEFECT];
	int fpDefectVMin[MAX_CAMERAS][MAX_REALDEFECT];
	/////CIS NewDefect Type
	int		m_nNewDefectType[MAX_CAMERAS][MAX_REALDEFECT];
	int		m_nNewDefectTypeFull[MOD_COUNT][MAX_REALDEFECTNEW];//new version
	int		m_nNewDefectColor[MAX_CAMERAS][8][MAX_REALDEFECT];//0 init 1Black	2White	3LineBlack	4LineWhite
	int		m_nNewDefectColorFull[MOD_COUNT][MAX_REALDEFECTNEW];//0 init 1Black	2White	3LineBlack	4LineWhite //new version
	int		m_nNewLineColor[MAX_CAMERAS][8][MAX_REALDEFECT];//0init	1��������	2���ö���

	


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

	float	m_fReturnX[MAX_CAMERAS][MAX_REALDEFECT];			//���� �� ��ŷ�� �����ִ� ���� ����Ÿ X
	float	m_fReturnY[MAX_CAMERAS][MAX_REALDEFECT];			//���� �� ��ŷ�� �����ִ� ���� ����Ÿ Y
	int		m_nDefectType[MAX_CAMERAS][MAX_REALDEFECT];
	BOOL	m_bDefectWhite[MAX_CAMERAS][MAX_REALDEFECT];		//�̹��� ����̹��ΰ��� ���� �÷���
	CPoint	m_ptDefect[MAX_CAMERAS][MAX_REALDEFECT];			//�̹� ��ġ
	int		m_nDefectVMax[MAX_CAMERAS][MAX_REALDEFECT];		//�ش� �̹� �ִ� ���
	int		m_nDefectVMaxFull[MAX_REALDEFECTNEW];		//�ش� �̹� �ִ� ���///new version
	int		m_nDefectVMin[MAX_CAMERAS][MAX_REALDEFECT];		//�ش� �̹� �ּ� ���
	int		m_nDefectVMinFull[MAX_REALDEFECTNEW];		//�ش� �̹� �ּ� ���	//new version
	BOOL	m_bResult[MAX_CAMERAS][MAX_REALDEFECT];		

	int		m_nBroadEdge[MAX_CAMERAS];
	int		m_nRcvEdgeData[MAX_CAMERAS];
	int		m_nGradeShutter[MAX_CAMERAS];

///*
//�˻� ���
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
	double	m_dWhiteSize;//��� ������
	double	m_dCommutySize[MAX_CAMERAS];
	int		m_dCommutyCount[MAX_CAMERAS];

	BOOL	m_bSaveBmp;//1 bmp 0 jpg
	int		m_nTrembleCount[MAX_CAMERAS];
	
	int		m_nBubleSkip[MAX_CAMERAS];	//���� Skip 
	int		m_nBlobUse[MAX_CAMERAS];						//blob use
	int     m_nBlobLimitCount[MAX_CAMERAS];
	////////////////////////////////////////////////////////////////////
	double	m_dSumSharp[MAX_CAMERAS];
	double	m_dAveSharp[MAX_CAMERAS];
	double	m_dPeakSharp[MAX_CAMERAS];
	double	m_dMinSharp[MAX_CAMERAS];

	int		m_overlapDefectCnt;
	int		m_overlapDefectPosX[40];


	CTime	m_tLastSendTime[MAX_CAMERAS];	//������ ���������� ���� �ð�.
	CTime	m_tTimeCheckFrameOld[MAX_CAMERAS];//���� LGCHEKC Time�� ���� �ð�.
	CTime	m_tTimeCheckFrame[MAX_CAMERAS];//���� LGCHEKC Time�� ���� �ð�.
	int  m_nTimeCheckFrame[MAX_CAMERAS];//���� LGCHEKC Time�� ���� �ð�.
	int  m_nTimeCheckFrameOld[MAX_CAMERAS];//���� LGCHEKC Time�� ���� �ð�.
	int	 m_nLastSendTime[MAX_CAMERAS];	//������ ���������� ���� �ð�.

	double	m_dOldInspTime[MAX_CAMERAS];
	int		m_nCycleUse[MAX_CAMERAS];

	double	m_dMaxMark[MAX_CAMERAS];
	int		m_nMarkCount[MAX_CAMERAS];
	int		m_nMarkValue[MAX_CAMERAS];
	int		m_edgeDetectValue[MAX_CAMERAS];

	double	m_dStrongSize[MAX_CAMERAS];


	int		m_nMachine;		//0 :���� 1:����.
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
	double	m_dAveThUp[MAX_CAMERAS];						//��ǰ ��� ThUp
	double	m_dAveThDn[MAX_CAMERAS];						//��ǰ ��� ThDn
	double	m_dAveRealBright[MAX_CAMERAS];				//ũ�ν� ��� ���
	int		m_nProjection[MAX_CAMERAS];
	double	m_pinholeLargeSize[MAX_CAMERAS];
	double	m_pinholeGroupSize[MAX_CAMERAS];
	int		m_nHistoMean[MAX_CAMERAS];
	int		m_nInsMethod[MAX_CAMERAS];
	int		m_nInspDirection[MAX_CAMERAS];
	int		m_nDefectCount[MAX_CAMERAS];					//�ҷ� �ĺ� ���
	int		m_nDefectResultCount[MAX_CAMERAS];			//���� ���� �ҷ� ��
	

	double	m_dAvgBrightness[MAX_CAMERAS];				//��� ���
	int		m_nMinBrightness[MAX_CAMERAS];				//��ü ������ �ּ� ���
	int		m_nMaxBrightness[MAX_CAMERAS];				//��ü ������ �ִ� ���
	double	m_dSharpness[MAX_CAMERAS];					//�̹��� ���� ��
	double	m_dThUp[MAX_CAMERAS];						//���� ��� �Ӱ�ġ		//���� ��ġ�� �Ӱ�ġ
	double	m_dThDn[MAX_CAMERAS];						//���� ��� �Ӱ�ġ		//���ڴ� ��ġ�� �Ӱ�ġ
	double	m_dThSize[MAX_CAMERAS];						//�ҷ� ũ�� ���� �Ķ����
	double	m_dThMaxSizeX[MAX_CAMERAS];					//�ҷ��� X���� �ִ� ũ�� --> �������� �������� �߰��� �κ� 07.2.15 by Sun 
	double	m_dXlineSkip[MAX_CAMERAS];					//���� XLine Skip �κ� �߰� -> MAx Ave Brightness - Min Ave Brightness ���̰�
	double	m_dStdBrightness[MAX_CAMERAS];				//���� ��Ⱚ
	double	m_dSizeSkip[MAX_CAMERAS];					//����� skip
	double	m_dWBThDn[MAX_CAMERAS];						//��� ����
	double	m_dCamDist[MAX_CAMERAS];						//���ö��̽� ��ȣ�� �Ի� Frame
	int		m_dRollsize[MAX_CAMERAS];					//���� 1 ���� 0
	double		m_dEdgeBright[MAX_CAMERAS];					//������ ������ S/F
	double	m_dStartPos[MAX_CAMERAS];					// �������� ���� pos
	double	m_dEndPos[MAX_CAMERAS];						// �������� end pos
	int		m_nBCRFrame[MAX_CAMERAS];
	int		m_nTacXpos[MAX_CAMERAS];						//tac x Position
	int		m_nTapeSkipFrame[MAX_CAMERAS];
	double		m_nPolarEdge[MAX_CAMERAS];					//�� ������.
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
	int		m_nUseInspArea[MAX_CAMERAS];				//�ڵ� ���� �˻� ��� �̻��. 0 unuse 1 use
	int		m_nUseCInspArea[MAX_CAMERAS];			//Cross Edge Detect use

//�˻� �Ķ����
	CString m_strComName;				//��ǻ�� �̸� 
	double	m_dStdDevV[MAX_CAMERAS];					//ǥ������ �� - ���� ����
	double	m_dStdDevVTh[MAX_CAMERAS];				//ǥ������ �Ӱ谪 - ���� ����
	double	m_dStdDevH[MAX_CAMERAS];					//ǥ������ �� - ���� ����
	double	m_dStdDevHTh[MAX_CAMERAS];				//ǥ������ �Ӱ谪 - ���� ����				
	CRect	m_rectIns[MAX_CAMERAS];					//�˻� ����
	int		m_nNotInsArea[MAX_CAMERAS];				//�˻����� �ʴ� ���� -���̸� ������ ���ϰ� +���̸� ������ �˻����� �ʴ´�.
	int		m_nExposeTime[MAX_CAMERAS];
//�˻� ����
	double	m_dScaleFactorX[MAX_CAMERAS];			//Scale Factor X
	double	m_dScaleFactorY[MAX_CAMERAS];			//Scale Factor Y
	double	m_dCalibSttX[MAX_CAMERAS];				//Calibration Start X
	double	m_dCalibSttY[MAX_CAMERAS];				//Calibration Start Y

	double	m_dRectAve[MAX_CAMERAS];					//ũ�ν��� roi Ave
	double	m_dRectMin[MAX_CAMERAS];					//ũ�ν��� roi Min
	double	m_dRectMax[MAX_CAMERAS];					//ũ�ν��� roi Max
//	double	m_dWeakThDn;				//������ ������ ����Param
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
	int		m_nShutter2[MAX_CAMERAS];		//2�� Shutter ��.
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


	double	m_dLineEdgeData1[MAX_CAMERAS][40];//¦�� Black->White Ȧ��White->Black
	double	m_dLineEdgeData2[MAX_CAMERAS][MOD_COUNT][40];//¦�� Black->White Ȧ��White->Black
	double	m_dLineEdgeData3[MAX_CAMERAS][40];//¦�� Black->White Ȧ��White->Black
	double	m_dLineEdgeData4[MAX_CAMERAS][40];//¦�� Black->White Ȧ��White->Black
	double	m_dLineEdgeValue2[MAX_CAMERAS][MOD_COUNT][40];//¦�� Black->White Ȧ��White->Black
	double	m_dLineEdgeValueFull[MOD_COUNT][MAX_REALDEFECTNEW];//new version
	int			m_nLineEdgeCount1[MAX_CAMERAS][MOD_COUNT];

	int		m_nNewLineCount;
	int		m_nNewTopCount;
	double  m_dNewTopScale;
	double	m_dNewLineEdgeData1[80];//¦�� Black->White Ȧ��White->Black
	double	m_dNewLineEdgeData1Old[80];//¦�� Black->White Ȧ��White->Black
	double	m_dNewLineEdgeData11[MOD_COUNT][80];//������ ���μ�
	int		m_nOldLineCount;
	double	m_dOldLineEdgeData1[80];//¦�� Black->White Ȧ��White->Black
	double	m_dNewLineEdgeData2[MOD_COUNT][80];//¦�� Black->White Ȧ��White->Black
	double	m_dNewLineEdgeData3[80];//¦�� Black->White Ȧ��White->Black
	double	m_dNewLineEdgeData4[80];//¦�� Black->White Ȧ��White->Black


	double	m_dLineAverageData1[MAX_CAMERAS][10][40];//10frame 20�� ����

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
