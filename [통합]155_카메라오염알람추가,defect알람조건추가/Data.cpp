// Data.cpp : implementation file
//

#include "stdafx.h"
#include "VisWeb.h"
#include "Data.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CData


CData::CData()
{
////////////////////////////////////
	for(int nk = 0;nk<MAX_CAMERAS;nk++){
		for(int i=0;i<10;i++){
			m_dAverageData[i] = 0;
			for(int j=0;j<MOD_COUNT;j++){
				m_dAverageData1[nk][j][i] = 0;
			}
		}
		for(int i=0;i<20;i++){
			for(int j=0;j<MOD_COUNT;j++){
				for(int hh=0;hh<5;hh++){
					m_dDefectValue[nk][j][i][hh] = 0;
					m_dDefectValue1[nk][i][hh]=0;//0min 1max 2 average

				}
			}
		}

	}
	for(int i=0;i<40;i++)
		m_rtScratch2[i].SetRect(0,0,0,0);
	for(int k=0;k<MAX_CAMERAS;k++){
		for(int i=0;i<20;i++)
			m_rtScratch1[k][i].SetRect(0,0,0,0);
	}

	m_nNCoatBrightness[0]=m_nNCoatBrightness[1]=0;
	m_nChangeLine[0]=m_nChangeLine[1]=0;
	m_nRealDefectCountFull = 0;
	for(int k=0;k<MOD_COUNT;k++){
		for(int i=0;i<MAX_REALDEFECTNEW;i++){
			for(int j=0;j<5;j++){
				m_dDefectValueFull[k][i][i] = 0;
			}
			m_rtThreadDefectFull[k][i].SetRect(0,0,0,0);// = 0;
			m_rtThreadSizeDefectFull[k][i].SetRect(0,0,0,0);
			m_dSizeFull[k][i] = 0;
			m_dSizeXFull[k][i] = 0;//m_dSizeYFull
			m_dSizeYFull[k][i] = 0;//
			m_nNewDefectTypeFull[k][i] = 0;
			m_nNewDefectColorFull[k][i] = 0;
			m_strDefectNameFull[k][i] = "";
			m_strNewDefectNameFull[k][i] = "";
			m_dLineEdgeValueFull[k][i] = 0;
		}
		for(int i=0;i<10;i++){
			m_dAverageData1Full[k][i] = 0;
		}
		m_nKillFunctionFull[k] = 0;
		m_nThreadDefectCountFull[k] = 0;

	}
	for(int i=0;i<40;i++){
		m_rtNewInspect[i].SetRect(0,0,0,0);
		m_nDefectVMaxFull[i]=0;
		m_nDefectVMinFull[i] = 0;
		m_rtSubLine[i].SetRect(0,0,0,0);
	}

	for(int i=0;i<6;i++)
		m_nSumBadCount[i] = 0;
	m_nEdgeOffset = 10;
	m_nCamID = 2;//0 hts 1hbs 2ht 3hb 4mt 5mb
	m_nDrawMeter[0]=m_nDrawMeter[1] = 0;
	m_nCadidateEndpos = 0;
	m_nEpcPos = 1;
	m_dMisbatchScale[0]=m_dMisbatchScale[1]=0;
	m_dMisbatchScale1[0]=m_dMisbatchScale1[1]=0;
	m_nMismatchLine = 0;
	m_nDefectMag = 1;
	m_bSkipFrame = FALSE;
	m_dNewTopScale = 0.04233;
	m_nNewTopCount = 0;
	m_bAutoCoatBrightness = FALSE;
	m_nCoatAveBrightness = 0;
	m_bLineAverageData = FALSE;
	m_bAutoEdge = FALSE;
	for(int i=0;i<5;i++)m_dSizeParam[i] = 0.3;
	for(int i=0;i<100;i++)
		m_strFullLineData[i] = "";
	for(int i=0;i<3;i++){
		for(int j=0;j<METER_10;j++){
			for(int k=0;k<MAX_FRAME;k++){
				for(int l=0;l<MAX_LENGTH;l++){
					m_dDrawMisData[i][j][k][l] = 0;
				}
			}
		}
	}

	for(int i=0;i<20;i++){
		m_rtMismatchChar[i].SetRect(0,0,0,0);//mismatch 글자 영역
		m_rtCoatChar[i].SetRect(0,0,0,0);//코팅 글자 영역
		m_rtOldCoatChar[i].SetRect(0,0,0,0);//
		m_rtNullingChar[i].SetRect(0,0,0,0);//무지부 글자 영역
		m_rtInsulateChar[i].SetRect(0,0,0,0);//절연부 글자 영역
	}
	for(int i=0;i<5;i++)
		m_nLaneDefectCount[i][0]=m_nLaneDefectCount[i][1]=0;
	for(int i=0;i<1000;i++){
		m_nIgnorePixel[i] = 0;
		for(int k=0;k<3;k++)
			m_nIgnorePixel1[k][i] = 0;
	}
	for(int i=0;i<MAX_LENGTH;i++)
		m_nLanePos[i][0]=m_nLanePos[i][1] = 0;

	m_dAverageBrightness2[0]=m_dAverageBrightness2[1]=m_dAverageBrightness2[2]=0;
	m_dAverageBrightness1[0]=m_dAverageBrightness1[1]=m_dAverageBrightness1[2]=0;



	m_nEdgeAverage[0] = m_nEdgeAverage[1] = 0;
	m_nLineSelect = 1112;//1000단위 코터, 100단위 양/음(1/2), 10단위 헤더/미스(1/2), 1단위 탑백(1/2)

	m_strLineSelect = "1112";
	m_bPreprocessing = FALSE;
	m_bInsulateInspect = FALSE;
	m_bUseCLog = TRUE;
	m_dInterpolation = 0;
	m_dInterpolationPixel = 0;
	m_bLineWrite = FALSE;
	m_bInspStart = TRUE;
	m_dDefectSize = 2;
	m_nThWhite3 = 40;
	m_nThBlack3 = 40;
	m_dSlope = 220;
	m_dLineScratch = 20;
	m_dMachineLength=0;
	m_nSimmulationMode = 1;
	m_nUseChuck=0;
	m_nOldChuck=0;
	m_nSubFrameCount = 0;
	m_nChuckChange = 0;
	m_nOldMeter = 0;
	m_strDefaultModel = "Default";
	m_nMinLineWidth = 30;
	m_nMinLineWidthMid = 30;
	m_nSkipWhite[0]=m_nSkipWhite[1] = 0;
	m_nNewLineCount = 0;
	m_nOldLineCount = 0;

//Data Push용 버퍼 -탑/백 , 100미터 , 10프레임 , 최대라인수20개(0번은 총라인개수, 1번부터 라인픽셀)
	for(int nmeter=0;nmeter<100;nmeter++)
		for(int nframe=0;nframe<10;nframe++)
			for(int nlen=0;nlen<MAX_LENGTH;nlen++){
				m_nFullLineData[0][nmeter][nframe][nlen]=m_nFullLineData[1][nmeter][nframe][nlen]=0;
				for(int i0=0;i0<5;i0++)
					m_nFullLineData1[i0][nmeter][nframe][nlen]=0;
			}
	m_nMachineLengthAB[0]=m_nMachineLengthAB[1]=0;//0 A chuck 1 B chuck
	m_nCamDistance=50;//50m 
	for(int i=0;i<10;i++)
		for(int j=0;j<MAX_LENGTH;j++){
			m_dMisMatchData[0][i][j]=m_dMisMatchData[1][i][j]=m_dMisMatchData[2][i][j]=m_dMisMatchData[3][i][j]=0;//미터가 바/뀌면 리셋
			m_dLenthMismatch[j] = 0;
		}

	for(int i=0;i<MAX_LENGTH;i++){
		m_dSharpness2[i] = 0;
		m_nLinePosPixel[i]=0;//전체길이별 픽셀
		m_dLinePosLength[i]=0;//전체 길이별 누적 길이
		m_nLinePosPixel1[i]=0;//전체길이별 픽셀
		m_dLinePosLength1[i]=0;//전체 길이별 누적 길이
		m_dMisMatchLen[0][i]=m_dMisMatchLen[1][i]=0;
		m_nMisMatchPixel[0][i]=m_nMisMatchPixel[1][i]=0;
		m_dReversePitchData[i] = 0;
		m_dReversePixelData [i]= 0;
		m_dMisTopBackData[0][i]=m_dMisTopBackData[1][i]=m_dMisTopBackData[2][i]=0;
		m_dMisTopBackData1[0][i]=m_dMisTopBackData1[1][i]=m_dMisTopBackData1[2][i]=m_dMisTopBackData1[3][i]=m_dMisTopBackData1[4][i]=0;
		m_dMisTopBackDataOld[0][i]=m_dMisTopBackDataOld[1][i]=m_dMisTopBackDataOld[2][i]=0;
	}
	m_dTotalLength[0]=m_dTotalLength[1]=0;

	for(int n =0;n<10;n++)
		for(int k =0;k<MAX_LENGTH;k++)
			m_dLineAve[n][k] =0;
	for(int i=0;i<80;i++){
		m_dOldLineEdgeData1[i]=0;//짝수 Black->White 홀수White->Black
		m_dNewLineEdgeData1[i]=0;//짝수 Black->White 홀수White->Black
		m_dNewLineEdgeData3[i]=0;//짝수 Black->White 홀수White->Black
		m_dNewLineEdgeData4[i]=0;//짝수 Black->White 홀수White->Black
		m_dNewLineEdgeData1Old[i]=0;
		for(int j=0;j<MOD_COUNT;j++){
			m_dNewLineEdgeData2[j][i]==0;//짝수 Black->White 홀수White->Black
			m_dNewLineEdgeData11[j][i] = 0;

		}
	}

	for(int n=0;n<MAX_CAMERAS;n++)
	{
		m_nKillFunction[n] = 0;
		for(int i=0;i<MAX_LENGTH;i++)
			m_dOldLineData[n][i] = 0;
		m_nWhiteLineCount[n] = 0;
		for(int k=0;k<8;k++){
			for(int jj=0;jj<16;jj++){
				m_rtThreadDefect[n][k][jj].SetRect(0,0,0,0);
				m_rtThreadSizeDefect[n][k][jj].SetRect(0,0,0,0);
			}
			m_nThreadDefectCount[n][k] = 0;
			m_nLineSlopeCount[n][k] = 0;

		}
		m_dLastEdge[n] = 0;
		m_dCalTol[n] = 0;
		m_nLineCount1[n] = 0;
		m_nRoiDount[n] = 0;
		m_nRealDefectCount1[n] = 0;
//////////////////
		////////////////////0914
		for(int i=0;i<20;i++){
			m_rtInspect[n][i].SetRect(0,0,0,0);
			for(int kk=0;kk<8;kk++){
				m_rtInspect1[n][kk][i].SetRect(0,0,0,0);
				m_rtLineSlopeCount[n][kk][i].SetRect(0,0,0,0);
				m_nNewDefectColor[n][kk][i] = 0;
				m_nNewLineColor[n][kk][i] = 0;
			}
		}


		m_nFullImageSaveFrame = 10;//10장
		m_nMiniImageSaveFrame = 5;//10

		m_bMiniImageCheck[n] = FALSE;
		m_dHooktime[n] = 0;
		for(int i=0;i<20;i++){
			m_dEdgeValue1[n][i]=0;
			m_dEdgeValue2[n][i]=0;
			m_dEdgeValue3[n][i]=0;

			for(int j=0;j<10;j++)
				m_dLineAverageData1[n][j][i]=0;
			for(int j=0;j<MOD_COUNT;j++){
				m_dLineEdgeData2[n][j][i]=0;//짝수 Black->White 홀수White->Black
				m_dLineEdgeValue2[n][j][i]=0;
			}
			m_dLineEdgeData3[n][i]=0;//짝수 Black->White 홀수White->Black
			m_dLineEdgeData4[n][i]=0;//짝수 Black->White 홀수White->Black

		}
		m_bInspectComplete[n] = FALSE;
		m_dSaveTime[n] = 0;

//////////////////
		m_nCameraWidth = CAM_WIDTH_CIS;//CAM_WIDTH_4096;
		m_nCameraHeight = CAM_HEIGHT_CIS;//CAM_HEIGHT_2048;	
		m_nMachine = 0;//코팅.
		m_bSharpness[n] = TRUE;//화면 표시용
		m_dSharpness1[n] = 0.;
		m_nLgtController=0;//조명 제어기 개수

		m_dCompactness[n] = 12;

		for(int i=0;i<CAM_WIDTH_CIS;i++){
			m_dCalXPos[n][i] = 0;;
			m_nCalDummyData[n][i] = 0;
		}



		m_nBlobUse[n] = 0;		//0 convex hull 1blob
		m_nBlobLimitCount[n]=5;
	///////////////////////////////////////
		m_nCycleUse[n] = 0;
		m_nDualNotIns = 0;
		m_bDualNotIns = FALSE;

		m_nPinholeValue[n] = 120;


		m_nColorGap[n] = 0;
		m_nLv[n] = 0;
		m_nRv[n] = 0;
		m_nFLimitCnt[n] = 0;
		m_nFMarkSkip[n] = 0;

		m_dRealSpot[n] = 0;
		m_dAveHddRemain = 0;
		m_dAveFps[n] = 0;
		m_dInspTime[n] = 0;
		m_dCrossCandidatecnt[n] = 0;
		m_dCrossGap[n] = 0;
		m_dRealBrightness[n] = 0;
		m_nProjection[n] = 1;
		m_nHistoMean[n] = 0;
		m_nInsMethod[n] = 1;
		m_nNotInsArea[n]	= 0;
		m_nExposeTime[n]	= 0;
		m_dScaleFactorX[n] = 0.024;
		m_dScaleFactorY[n] = 0.024;
		m_strComName = "";
		m_dAvgBrightness[n] = 0;
		m_dCrossBrightness[n] = 0;
		m_nDefectCount[n] = 0;
		m_nDefectResultCount[n] = 0;
		m_dThUp[n] = 50;
		m_dThDn[n] = 25;
		m_nMinBrightness[n]	= 0xff;
		m_nMaxBrightness[n]	= 0;
		m_dSharpness[n] = 0;
		m_bIsSepa[n] =0;
		m_dCamDist[n] = 0;
		m_dRollsize[n] =0;
		m_dEdgeBright[n] =0;
		m_dStartPos[n] = 0;
		m_dEndPos[n] = 0;
		m_nBCRFrame[n] = 0;
		m_nTacXpos[n] = 350;
		m_nTapeSkipFrame[n] = 100;
		m_nPolarEdge[n] = 0;
		m_dCodeDistace[n] =0;
		m_dOpticsDistanceX[n]=0;
		m_dOpticsDistanceY[n]=0;
		m_nTacLine[n] =0;
		m_nBcrRollSize[n] = 0;
		m_dOriginThUp[n] = 0.0;
		m_dOriginThDn[n] = 0.0;
		m_dOriginPenMarkV[n] = 0.0;
		m_dDefectRatio[n] = 0.0;
		m_nUseInspArea[n] = 0;
		m_nUseCInspArea[n] = 0;
		m_dRectAve[n]=0;
		m_dRectMin[n]=0;
		m_dRectMax[n]=0;
		m_nWeakSave[n]=0;
		m_dMaxDistRatio[n] =0.0;
		m_bSimulation[n] = FALSE;
		m_bCrossBlobImg[n] = FALSE;
		m_dAveMaxDefectBright[n] = m_dAveMinDefectBright[n] = m_dAvePenValue[n] = 0.0;
		m_dAveThUp[n]=	m_dAveThDn[n] = 	m_dAveRealBright[n] = 0;				//크로스 평균 밝기
	///////////////////////////////////////////////////////////////////////
		m_pinholeLargeSize[n] = 0;
		m_pinholeGroupSize[n] = 0;
		m_dLimitMaxBright[n] = 0;
		m_dLimitMinBright[n] = 0;
		m_nThWhite[n] = 13;			//th White
		m_nThBlack[n] = 13;			//th Black
		m_nShutter2[n] = 2000;		//2차 Shutter 값.
		m_nThWhiteValue[n] = 2;	//param13
		m_nThBlackValue[n] = 2;	//param14
		m_nCrossOffset[n] = 2;
		m_nInspDirection[n] = 0;	//param15 0:x Nomal Y nomal 1:X reverse Y nomal		2: x nomal Y Reverse 3: x reverse Y reverse 4:x nomal Y Reverse 5: x reverse Y reverse 
		m_nMaxLineValue[n] = 0;
		m_nMinLineValue[n] = 0;
		m_nMaxLinePos[n] = 0;
		m_nMinLinePos[n] = 0;
		m_nCrossInsRt[n] = 24;
		m_dStdGap[n] = 1.4;
		m_dNewStdGap[n] = 1.0;
		m_nStdevRect[n] = 34;

		m_dLineValue = 0;
		m_nLinePos = 0;
		m_dDSAngleGap[0][0] = -10;
		m_dDSAngleGap[0][1] = 10;
		m_dTypeRatio[n] = 0.5;
		m_dBlackSize[n] = 0.5;

		int i;
	///////////////////////////////////////////////////////////////////////
		m_nDefectThCountPercent[n]=0;
		for(i=0;i<MAX_COMMUTYFRAME;i++){
			m_bNotCoating[n][i] = FALSE;
		}
		for(i=0;i<5;i++){
			m_nCommutyFrameCount[n][i] = 0;
		}
		m_dBlackSizeSkip[n] = 4;//
		m_nCommutyCountCut[n] = 4;//10;//군집 휘점 개수
		m_nCommutyFrameCountCut[n] = 4;//8;

		m_pImageSC = new CImage();
		m_pImageSC->Create(BAD_IMG_WIDTH,BAD_IMG_HEIGHT,8);

		m_pImageLine = new CImage();
		m_pImageLine->Create(BAD_IMG_WIDTH*2,BAD_IMG_HEIGHT*2,8);//32배 압축
		
		m_nLineReduce = 4;//8;
		
		for(i = 0;i<MAX_REALDEFECT;i++)
		{
			m_nDefectLane[n][i] = 0;
			m_nDefectThCount[n][i] = 0;
			m_rectDefect[n][i].SetRect(0,0,0,0);
			m_pImageDefect[n][i] = new CImage();	//m_pLastImage
			m_pImageDefect[n][i]->Create(BAD_IMG_WIDTH, BAD_IMG_HEIGHT, 8);
			m_pImageDefect1[n][i] = new CImage();	//m_pLastImage
			m_pImageDefect1[n][i]->Create(BAD_IMG_WIDTH, BAD_IMG_HEIGHT, 8);
			m_dSizeX[n][i]			= 0;		
			m_dSizeY[n][i]			= 0;
			m_dSize[n][i]			= 0;
			m_dDefectRatio[n] = 0;
			fpX[n][i]		=0;
			fpY[n][i]		=0;
			fpSizeX[n][i]		=0;
			fpSizeY[n][i]		=0;
			m_dStdevV[n][i] = 0;
			fpDefectType[n][i] = 0;
			fpDefectVMax[n][i] = 0;
			fpDefectVMin[n][i] = 0;
			m_nNewDefectType[n][i] = 0;
			m_strDefectName[n][i] = "";
			m_strNewDefectName[n][i] = "";
			m_fReturnX[n][i]		= 0;
			m_fReturnY[n][i]		= 0;
			m_bDefectWhite[n][i]	 = 0;
			m_nDefectVMin[n][i]	 = 0xff;
			m_nDefectVMax[n][i]	 = 0;

			m_dDefectLeft[n][i]=0;		//이물 위치 Left
			m_dDefectTop[n][i]=0;		//이물 위치 top	
			m_dDefectRight[n][i]=0;		//이물 위치 Right
			m_dDefectBottom[n][i]=0;	//이물 위치 Bottom
			m_fDefectRatio[n][i]=0;
			m_nDefectType[n][i]=0;
			m_ptDefect[n][i].SetPoint(0,0);			//이물 위치
			m_bResult[n][i]=FALSE;		
			m_dDyespotAngle[n][i] = 0;
			m_dTempData1[n][i] = 0;
			m_dTempData2[n][i] = 0;
			m_dTempData3[n][i] = 0;
			m_nBlobCount[n][i] = 0;
			m_dMaxWhiteSize[n][i] = 0;
			m_dWhiteCommutySize[n][i] = 0;

			m_dWhiteCommutyCount[n]=0;
		}
		m_rectIns[n].SetRect(0,0,1024,1024);
		m_nSkipCount[n] = 0;
		for(i=0;i<5;i++)
		{
			m_nSkipPixel[n][i] = 0;
			m_nSkipArea[n][5]=0;
		}
		for(i=0;i<10;i++){
			m_dCamYpos[n][i]=0;
			m_dInspDetailTime[n][i] = 0.;
		}
		for(i=0;i<PD_FRAME*PD_LEN;i++)
			m_pPacketData[n][i] = "0";
		for(i=0;i<100;i++)
		{
			m_dSumMax[n][i] = 0;
			m_dSumMin[n][i] = 0;
			m_dSumPenV[n][i] = 0;
		}
	//	for(i=0;i<1000;i++){
	//		m_dCycleX[i] = 0;
	//		m_dCycleY[i] = 0;
	//	}
		m_dCycle300[n] = 942;

		for(i=0;i<MAX_CYCLE_COUNT;i++)
		{
			m_nDefaultCycle[n][i] = 100000;
			m_nDefectFlag[n][i] = 0;
			m_dLastCycle[n][i] = -1;
		}
		for(i=0;i<CYCLELENGTH;i++)//defectcount
		{
			m_dCycleY[n][i] = 0;
			m_dCycleX[n][i] = 0;
		}


		m_dCycle[n] = 940;
		m_nCycleLimit[n] = 5;
		m_nCycleCount[n] = 0;
		memset(m_cFilename[n],0,MAX_BADIMAGE_FILENAME*MAX_REALDEFECT);
		m_strMachineName = "CT01";
		m_nFindEdge[n] = 0;
		m_nTapeDist[n] = 0;
		m_nTapeDist1[n] = 0;
	//	m_nVisionLine = 4;
		m_nLineValueCheck = 0;
	//	m_dNewStdValue = 1.6;
		m_dMinSizeX[n]	= 0.;
		m_dMinSizeY[n] = 0.;
		m_dOldInspTime[n] = 0.;
		m_nTimeCheckFrame[n] = 0;
		m_nTimeCheckFrameOld[n] = 0;
		m_nLastSendTime[n] = 0;
		m_tLastSendTime[n] = CTime::GetCurrentTime();	//서버에 마지막으로 보낸 시간.
		m_tTimeCheckFrameOld[n]=m_tLastSendTime[n];//이전 LGCHEKC Time에 들어온 시간.
		m_tTimeCheckFrame[n]=m_tLastSendTime[n];//현재 LGCHEKC Time에 들어온 시간.

		m_dSumSharp[n] = 0.0;
		m_dAveSharp[n] = 0.0;
		m_dPeakSharp[n] = 0.0;
		m_dMinSharp[n] = 0.0;
		for(int h=0;h<4;h++){
			m_nMaxImageValue[n][h]=0;//
			m_nMinImageValue[n][h]=255;//
			m_nMaxImageLine[n][h] = 0;
			m_nMinImageLine[n][h] = 255;
		}
		for(int h=0;h<40;h++){
			m_dOldLine[n][h] = 0;
			m_dMisData[n][h] = 0;
		}

	}
	m_nReadCount = 0;
	m_nLineThCount = 0;
	m_dWhiteSize = 0.5;
	m_dCommutySize[0] = 0.3;
	m_dCommutyCount[0] = 3;
	m_nDyeSpotAngle[0] = 1;
	m_nRecude = 2;


	m_overlapDefectCnt = 0;

	for(int i=0;i<10;i++){
		m_nBadTypeCount[i] = 0;
		for(int j=0;j<MAX_DEFECT;j++){
			m_ptCandidate[i][j].SetPoint(0,0);
			m_ptCandidateOrigin[i][j].SetPoint(0,0);
			m_rtCandidate[i][j].SetRect(0,0,0,0);
			m_nCandidateType[i][j] = 0;
			m_nCandidateScValue[i][j]=0;
		}
	}
	for(int i=0;i<MAX_REALDEFECT;i++)
		for(int j=0;j<10;j++)
			m_nRealDefectInfo[i][i] = 0;
	m_nUseIndex = 1;
	m_nRealDefectCount=0;
	m_nServerSendDefectCount=0;
	m_nLineLEngthCut = 20;
	m_nLineTh1 = 20;

	m_nLineSumCount = 0;//라인 누적 개수
	m_nLineSumTH=1;//라인 누적 개수

	memset(&m_nFullImageProj,0,CAM_WIDTH_CIS*3);
	for(int i=0;i<MOD_COUNT;i++)
		for(int j=0;j<CAM_WIDTH_CIS*3;j++)
			m_nFullImageProj1[i][j]=0;

	for(int i=0;i<30;i++)
		m_dFullTime[i] = 0;

	for(int i=0;i<40;i++){
		m_rtinsulate[i].SetRect(0,0,0,0);//무지만
		m_rtinsulate1[i].SetRect(0,0,0,0);//절연폭만
		m_dInsulatePos[i] = 0;
	}
	for(int i=0;i<20;i++)
		m_dGrayValue[i]=0;
	for(int i=0;i<MAX_REALDEFECT;i++){
		m_dSizeInsulate[i]=0;			//이물 SIZE	(SizeX+SizeY)/2
		m_dSizeXInsulate[i]=0;			//이물 SIZE
		m_dSizeYInsulate[i]=0;			//이물 SIZE
		m_fDefectRatioInsulate[i]=0;
		m_rectDefectInsulate[i].SetRect(0,0,0,0);		//이물 영역
		m_pImageDefectInsulate[i] = new CImage();	//m_pLastImage
		m_pImageDefectInsulate[i]->Create(BAD_IMG_WIDTH, BAD_IMG_HEIGHT, 8);
		for(int j=0;j<MOD_COUNT;j++){
			m_rectDefectInsulate1[j][i].SetRect(0,0,0,0);
			m_nDefectInsulate1[j] = 0;
		}

	}

	for(int j=0;j<MOD_COUNT;j++){
		for(int i=0;i<MAX_REALDEFECTNEW;i++){
			m_pImageDefectFull[j][i] = new CImage();	//m_pLastImage
			m_pImageDefectFull[j][i]->Create(BAD_IMG_WIDTH, BAD_IMG_HEIGHT, 8);
		}
	}
	m_nInsulateDefectCount = 0;
	m_nInsulateCount=0;//절연 개수(무지수)

	for(int i=0; i<10; i++)
		m_nTmpBadTypeCount[i] = 0;
}

CData::~CData()
{
	for(int n=0;n<MAX_CAMERAS;n++)
	for(int i=0; i<MAX_REALDEFECT; i++)
	{
		m_pImageDefect[n][i]->Free();
		delete m_pImageDefect[n][i];
		m_pImageDefect1[n][i]->Free();
		delete m_pImageDefect1[n][i];
	}
	for(int j=0;j<MOD_COUNT;j++){
		for(int i=0;i<MAX_REALDEFECTNEW;i++){
			m_pImageDefectFull[j][i]->Free();
			delete m_pImageDefectFull[j][i];
		}
	}	
	m_pImageSC->Free();
	delete m_pImageSC;
	m_pImageLine->Free();
	delete m_pImageLine;

	
}


BEGIN_MESSAGE_MAP(CData, CWnd)
	//{{AFX_MSG_MAP(CData)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CData message handlers

void CData::Serialize(CArchive& ar) 
{
/*
	int i;
	if (ar.IsStoring())
	{	// storing code
			ar	<<	m_dStdDevV;
//		for(i=0; i<MAX_IMG_WIDTH; i++){
//			ar	<<	m_pHistoY[i];
//		}
	}
	else
	{	// loading code
			ar	>>	m_dStdDevV;
//		for(i=0; i<MAX_IMG_WIDTH; i++){
//			ar	>>	m_pHistoY[i];
//		}
	}
//	*/
}
void CData::InitData(int nCam,int nw,int nh)
{
	for(int n=0;n<MAX_CAMERAS;n++)
	{
		m_nRealDefectCount1[n] = 0;
//		m_nProjectX[n] = new int [nw*nh];
		for(int i=0;i<nw;i++) m_nProjectX[n][i] = 0;
//		memset(m_nProjectX[n],0,nw);
		m_nAverage[n] = 0;
		for(int k=0;k<4;k++){
			m_nEdgeData[n][k]=0;//0 Left 1 Right 2top	3bottom //use Insp Roi
		}
		for(int i=0;i<10;i++){
			m_nCandidatePointCount[i]=0;
			for(int j=0;j<MAX_DEFECT;j++){
				m_ptCandidate[i][j].SetPoint(0,0);
				m_rtCandidate[i][j].SetRect(0,0,0,0);
				m_ptCandidateOrigin[i][j].SetPoint(0,0);
				m_nCandidateType[i][j] = 0;
				m_nCandidateScValue[i][j]=0;
			}
		}
		for(int i=0;i<MAX_REALDEFECT;i++){
			m_dDyespotAngle[n][i] = 0;
			m_dTempData1[n][i] = 0;
			m_dTempData2[n][i] = 0;
			m_dTempData3[n][i] = 0;
			m_dMaxWhiteSize[n][i] = 0;

			for(int j=0;j<10;j++){
				m_nRealDefectInfo[i][i] = 0;
			}
		}
		for(int h=0;h<4;h++){
			m_nMaxImageValue[n][h]=0;//
			m_nMinImageValue[n][h]=255;//
			m_nMaxImageLine[n][h] = 0;
			m_nMinImageLine[n][h] = 255;

		}
		m_nRcvEdgeData[n]=0;
	}
	//	
	m_nRealDefectCount=0;
	m_nServerSendDefectCount=0;

}

void CData::ResetData(int nCam)
{
	m_nSkipWhite[0]=m_nSkipWhite[1]=0;
	for(int i=0;i<40;i++){
		m_rtinsulate[i].SetRect(0,0,0,0);//무지
		m_rtinsulate1[i].SetRect(0,0,0,0);//절연폭만
		m_dInsulatePos[i] = 0;
	}
	m_nInsulateCount=0;//절연 개수(무지수)

	if(nCam==0){
		m_nRealDefectCountFull = 0;
		for(int k=0;k<MOD_COUNT;k++){
			for(int i=0;i<MAX_REALDEFECTNEW;i++){
				for(int j=0;j<5;j++){
					m_dDefectValueFull[k][i][i] = 0;
				}
				m_rtThreadDefectFull[k][i].SetRect(0,0,0,0);// = 0;
				m_rtThreadSizeDefectFull[k][i].SetRect(0,0,0,0);
				m_dSizeFull[k][i] = 0;
				m_dSizeXFull[k][i] = 0;//m_dSizeYFull
				m_dSizeYFull[k][i] = 0;//
				m_nNewDefectTypeFull[k][i] = 0;
				m_nNewDefectColorFull[k][i] = 0;
				m_strDefectNameFull[k][i] = "";
				m_strNewDefectNameFull[k][i] = "";
				m_dLineEdgeValueFull[k][i] = 0;
			}
			for(int i=0;i<10;i++){
				m_dAverageData1Full[k][i] = 0;
			}
			m_nKillFunctionFull[k] = 0;
			m_nThreadDefectCountFull[k] = 0;

		}
		for(int i=0;i<40;i++){
			m_rtNewInspect[i].SetRect(0,0,0,0);
			m_nDefectVMaxFull[i]=0;
			m_nDefectVMinFull[i] = 0;
			m_rtSubLine[i].SetRect(0,0,0,0);
		}
	}

	m_nWhiteLineCount[nCam]=0;
	m_nDefectCount[nCam] = 0;
	m_nDefectResultCount[nCam] = 0;
	m_dAvgBrightness[nCam] = 0;
	if(GetVisionLine(nCam) ==GL3)
		m_nMinBrightness[nCam] = 0;
	else
		m_nMinBrightness[nCam] = 0xff;
	m_nMaxBrightness[nCam] = 0;
	m_dSharpness[nCam] = 0;
	m_bIsSepa[nCam] = false;
	
	m_nRoiDount[nCam] = 0;
	for(int i=0;i<MAX_LENGTH;i++){
		m_nLinePosPixel[i]=0;//전체길이별 픽셀
		m_dLinePosLength[i]=0;//전체 길이별 누적 길이
		m_nLinePosPixel1[i]=0;//전체길이별 픽셀
		m_dLinePosLength1[i]=0;//전체 길이별 누적 길이
		m_dReversePitchData[i] = 0;
		m_dLenthMismatch[i] = 0;//길이 미스매치 데이터
		m_dReversePixelData[i] = 0;
		//m_dMisTopBackData[0][i]=m_dMisTopBackData[1][i]=m_dMisTopBackData[2][i]=0;

	}
	m_dTotalLength[0]=m_dTotalLength[1]=0;

	for(int i=0;i<20;i++){

		m_rtInspect[nCam][i].SetRect(0,0,0,0);

		m_dLineEdgeData1[nCam][i]=0;//짝수 Black->White 홀수White->Black
		m_dEdgeValue1[nCam][i]=0;
		m_dEdgeValue2[nCam][i]=0;
		m_dEdgeValue3[nCam][i]=0;
		m_dLineEdgeData3[nCam][i]=0;//짝수 Black->White 홀수White->Black
		m_dLineEdgeData4[nCam][i]=0;//짝수 Black->White 홀수White->Black

		m_nLineSlopeCount[nCam][i]=0;

		for(int j=0;j<MOD_COUNT;j++){
			m_rtInspect1[nCam][j][i].SetRect(0,0,0,0);

			m_dLineEdgeData2[nCam][j][i]=0;//짝수 Black->White 홀수White->Black
			m_dLineEdgeValue2[nCam][j][i]=0;
			m_rtLineSlopeCount[nCam][j][i].SetRect(0,0,0,0);
		}

	}
	for(int i=0;i<80;i++){
		m_dOldLineEdgeData1[i] = 0;
		m_dNewLineEdgeData1[i]=0;//짝수 Black->White 홀수White->Black
		m_dNewLineEdgeData3[i]=0;//짝수 Black->White 홀수White->Black
		m_dNewLineEdgeData4[i]=0;//짝수 Black->White 홀수White->Black
		m_dNewLineEdgeData1Old[i]=0;
		for(int j=0;j<MOD_COUNT;j++){
			m_dNewLineEdgeData2[j][i]==0;//짝수 Black->White 홀수White->Black
			m_dNewLineEdgeData11[j][i] = 0;
		}
	}

	m_nLineCount1[nCam] = 0;

	for(int k=0;k<8;k++){
		for(int jj=0;jj<16;jj++){
			m_rtThreadDefect[nCam][k][jj].SetRect(0,0,0,0);
			m_rtThreadSizeDefect[nCam][k][jj].SetRect(0,0,0,0);
			m_nNewDefectColor[nCam][k][jj] = 0;
			m_nNewLineColor[nCam][k][jj] = 0;
		}
		m_nThreadDefectCount[nCam][k] = 0;

	}

	for(int i=0; i<MAX_DEFECT ; i++)
	{

		m_nLineMaxV[i] = 0;
		m_rtLine[i].SetRect(0,0,0,0);
		m_ptLine[i].SetPoint(0,0);

	}
	for(int i = 0;i<MAX_REALDEFECT;i++)
	{
		m_nDefectLane[nCam][i] = 0;

		m_nDefectThCount[nCam][i] = 0;
		m_rectDefect[nCam][i].SetRect(0,0,0,0);
		m_dSizeX[nCam][i]			= 0;		
		m_dSizeY[nCam][i]			= 0;
		m_dSize[nCam][i]			= 0;
		m_dDefectRatio[nCam] = 0;
		fpX[nCam][i]		=0;
		fpY[nCam][i]		=0;
		fpSizeX[nCam][i]		=0;
		fpSizeY[nCam][i]		=0;
		m_dStdevV[nCam][i] = 0;
		fpDefectType[nCam][i] = 0;
		fpDefectVMax[nCam][i] = 0;
		fpDefectVMin[nCam][i] = 0;
		m_nNewDefectType[nCam][i] = 0;
		m_strDefectName[nCam][i] = "";
		m_strNewDefectName[nCam][i] = "";
		m_fReturnX[nCam][i]		= 0;
		m_fReturnY[nCam][i]		= 0;
		m_bDefectWhite[nCam][i]	 = 0;
		m_nDefectVMin[nCam][i]	 = 0xff;
		m_nDefectVMax[nCam][i]	 = 0;

		m_dWhiteCommutySize[nCam][i] = 0;
		m_dWhiteCommutyCount[nCam] = 0;

		m_dDefectLeft[nCam][i]	= BAD_IMG_WIDTH;	
		m_dDefectTop[nCam][i]		= BAD_IMG_HEIGHT;			
		m_dDefectRight[nCam][i]	= 0;			
		m_dDefectBottom[nCam][i]	= 0;		
		m_fDefectRatio[nCam][i]=0;
		m_nDefectType[nCam][i]=0;
		m_ptDefect[nCam][i].SetPoint(0,0);			//이물 위치
		m_bResult[nCam][i]=TRUE;	
		m_dDyespotAngle[nCam][i] = 0;
		m_dMaxWhiteSize[nCam][i]=0;
		m_dTempData1[nCam][i] = 0;
		m_dTempData2[nCam][i] = 0;
		m_dTempData3[nCam][i] = 0;
		m_nBlobCount[nCam][i] = 0;

	}
	for(int i=0;i<10;i++){
		m_nCandidatePointCount[i]=0;
		for(int j=0;j<MAX_DEFECT;j++){
			m_ptCandidate[i][j].SetPoint(0,0);
			m_rtCandidate[i][j].SetRect(0,0,0,0);
			m_ptCandidateOrigin[i][j].SetPoint(0,0);
			m_nCandidateType[i][j] = 0;
			m_nCandidateScValue[i][j]=0;
		}
	}
	for(int i=0;i<MAX_REALDEFECT;i++){
		for(int j=0;j<10;j++)
			m_nRealDefectInfo[i][j] = 0;
		m_dSizeInsulate[i]=0;			//이물 SIZE	(SizeX+SizeY)/2
		m_dSizeXInsulate[i]=0;			//이물 SIZE
		m_dSizeYInsulate[i]=0;			//이물 SIZE
		m_fDefectRatioInsulate[i]=0;
		m_rectDefectInsulate[i].SetRect(0,0,0,0);		//이물 영역
	}
	m_nInsulateDefectCount = 0;
	for(int h=0;h<MOD_COUNT;h++){
		m_nMaxImageValue[nCam][h]=0;//
		m_nMinImageValue[nCam][h]=255;//
		m_nMaxImageLine[nCam][h] = 0;
		m_nMinImageLine[nCam][h] = 255;
		m_nLineEdgeCount1[nCam][h]=0;

	}
	m_nRealDefectCount=0;
	m_nRealDefectCount1[nCam]=0;
	m_nServerSendDefectCount=0;
	m_nNewLineCount = 0;

	memset(&m_nFullImageProj,0,CAM_WIDTH_CIS*3);
	for(int i=0;i<MOD_COUNT;i++)
		memset(&m_nFullImageProj1[i],0,CAM_WIDTH_CIS*3);
// 		for(int j=0;j<CAM_WIDTH_CIS*3;j++)
// 			m_nFullImageProj1[i][j]=0;

// 	for(int i=0;i<MAX_LENGTH;i++){
// 		m_dMisTopBackData1[0][i]=m_dMisTopBackData1[1][i]=m_dMisTopBackData1[2][i]=m_dMisTopBackData1[3][i]=m_dMisTopBackData1[4][i]=0;
// 	}

}

void CData::ResetImgData(int nCam)
{
	for(int i=0; i<MAX_REALDEFECT ; i++)
	{
		memset(m_pImageDefect[nCam][i]->GetImagePtr(), 0, BAD_IMG_WIDTH*BAD_IMG_HEIGHT);//
		memset(m_pImageDefect1[nCam][i]->GetImagePtr(), 0, BAD_IMG_WIDTH*BAD_IMG_HEIGHT);//

		memset(m_pImageDefectInsulate[i]->GetImagePtr(), 0, BAD_IMG_WIDTH*BAD_IMG_HEIGHT);//

/*
		m_dSizeX[i]			= 0;		
		m_dSizeY[i]			= 0;	
		m_dSize[i]			= 0;
		m_nDefectNo[i]		= 0;
		m_nDefectVMin[i]	= 0xff;
		m_nDefectVMax[i]	= 0;
		m_nDefectType[i]	= 0;
		m_ptDefect[i]		= (0,0);
		m_strDefectName[i] = "";
		*/
	}
	
}
void CData::AddDefectPoint(CPoint ptreverse,CPoint ptorigin,int nIdx)
{
	m_ptCandidate[nIdx][m_nCandidatePointCount[nIdx]] = ptreverse;
	m_ptCandidateOrigin[nIdx][m_nCandidatePointCount[nIdx]] = ptorigin;
	m_nCandidatePointCount[nIdx]++;
}
void CData::MoveDefectData(int nSrc, int nDest,int nCam)
{
	m_dDefectLeft[nCam][nDest]	= m_dDefectLeft[nCam][nSrc]	;	
	m_dDefectTop[nCam][nDest]		= m_dDefectTop[nCam][nSrc]	;			
	m_dDefectRight[nCam][nDest]	= m_dDefectRight[nCam][nSrc]	;	
	m_dDefectBottom[nCam][nDest]	= m_dDefectBottom[nCam][nSrc]	;		
	m_nDefectVMin[nCam][nDest]	= m_nDefectVMin[nCam][nSrc]	;
	m_nDefectVMax[nCam][nDest]	= m_nDefectVMax[nCam][nSrc]	;
	m_nDefectType[nCam][nDest]	= m_nDefectType[nCam][nSrc]	;
	m_ptDefect[nCam][nDest]		= m_ptDefect[nCam][nSrc]		;
	m_bResult[nCam][nDest]		= m_bResult[nCam][nSrc]		;
	m_dSizeX[nCam][nDest]			= m_dSizeX[nCam][nSrc]		;	
	m_dSizeY[nCam][nDest]			= m_dSizeY[nCam][nSrc]		;
	memmove(m_pImageDefect[nCam][nDest]->GetImagePtr(), m_pImageDefect[nCam][nSrc]->GetImagePtr(), BAD_IMG_WIDTH*BAD_IMG_HEIGHT);
	memmove(m_pImageDefect1[nCam][nDest]->GetImagePtr(), m_pImageDefect1[nCam][nSrc]->GetImagePtr(), BAD_IMG_WIDTH*BAD_IMG_HEIGHT);
	m_rectDefect[nCam][nDest]		= m_rectDefect[nSrc]	;	
}

int CData::GetVisionLine(int nCam)
{
	int nRet=0;

	if(m_strComName.Find("CMI")>=0){
//이름 구조
		//CMI	CT01	A/C(양음)		H/M(헤드미스매치)		T/B(탑백)	1
		m_nLineSelect = 0;//1000단위 코터, 100단위 양/음(1/2), 10단위 헤더/미스(1/2), 1단위 탑백(1/2)
		if(m_strComName.Find("CT")>=0)m_nLineSelect +=1000;
		if(m_strComName.Mid(7,1)=="A")m_nLineSelect +=100;//양극
		else if(m_strComName.Mid(7,1)=="C")m_nLineSelect +=200;//음극

		if(m_strComName.Mid(8,1)=="H")m_nLineSelect +=10;
		else if(m_strComName.Mid(8,1)=="M")m_nLineSelect +=20;
		if(m_strComName.Mid(9,1)=="T")m_nLineSelect +=1;
		else if(m_strComName.Mid(9,1)=="B")m_nLineSelect +=2;
//CMICT01AHB1 = 1112
		m_strLineSelect.Format("%d",m_nLineSelect);//끝에 한자리
		nRet = GLCIS;//~
	}
	else{
		//오창도 cmi 처럼 변경
		if(m_strComName.Find("TOP")>=0)		m_nLineSelect = 1001;
		else								m_nLineSelect = 1002;
		//양극 음극
		if(	m_nMachine==0)					m_nLineSelect+=100;//양극
		else								m_nLineSelect+=200;//음극
		m_nLineSelect += 10;//header부
		m_strLineSelect.Format("%d",m_nLineSelect);
		nRet = GLCIS;//~
			//		m_strComName = "GL404";
			//		m_dDefectRatio = 100;
			//		m_nUseCInspArea = 1;
	}

	return nRet;
}

void CData::ComputeReturnData(int nCam)
{
	int nLine = m_nVisionLine;//
	int nWidth= m_nCameraWidth;//;	
	//에지쪽 카메라의 경우 불량 위치를 수정해줘야 한다.

	for(int i=0; i<m_nRealDefectCount; i++){
		if(i>=MAX_REALDEFECT)	break;

		if(m_nInspDirection[nCam] == 0)	//X nomal Y nomal
		{
			m_fReturnX[nCam][i] = float((m_ptDefect[nCam][i].x *  m_dScaleFactorX[nCam]) + m_dCalibSttX[nCam]);//Camera Reverse
			m_fReturnY[nCam][i] = float(( float(m_ptDefect[nCam][i].y) *  m_dScaleFactorY[nCam]) + m_dCalibSttY[nCam]);
		}
		else if(m_nInspDirection[nCam] == 1)	//X reverse Y nomal
		{
			m_fReturnX[nCam][i] = float(((nWidth - m_ptDefect[nCam][i].x) *  m_dScaleFactorX[nCam]) + m_dCalibSttX[nCam]);//Camera Reverse
			m_fReturnY[nCam][i] = float(( float(m_ptDefect[nCam][i].y) *  m_dScaleFactorY[nCam]) + m_dCalibSttY[nCam]);
		}
		else if(m_nInspDirection[nCam] == 2)	//X nomal Y reverse
		{
			m_fReturnX[nCam][i] = float((m_ptDefect[nCam][i].x *  m_dScaleFactorX[nCam]) + m_dCalibSttX[nCam]);//Camera Reverse
			m_fReturnY[nCam][i] = float(( float(m_nCameraHeight - m_ptDefect[nCam][i].y) *  m_dScaleFactorY[nCam])+ m_dCalibSttY[nCam]);
		}
		else if(m_nInspDirection[nCam] == 3)	//X reverse Y reverse
		{
			m_fReturnX[nCam][i] = float(((nWidth - m_ptDefect[nCam][i].x) *  m_dScaleFactorX[nCam]) + m_dCalibSttX[nCam]);//Camera Reverse
			m_fReturnY[nCam][i] = float(( float(m_nCameraHeight - m_ptDefect[nCam][i].y) *  m_dScaleFactorY[nCam]) + m_dCalibSttY[nCam]);
		}
		else if(m_nInspDirection[nCam] == 4)	//X nomal Y reverse
		{
			m_fReturnX[nCam][i] = float((m_ptDefect[nCam][i].x *  m_dScaleFactorX[nCam]) + m_dCalibSttX[nCam]);//Camera Reverse
			m_fReturnY[nCam][i] = float(( float(m_nCameraHeight- m_ptDefect[nCam][i].y) *  m_dScaleFactorY[nCam])+ m_dCalibSttY[nCam]);
		}
		else if(m_nInspDirection[nCam] == 5)	//X reverse Y reverse
		{
			m_fReturnX[nCam][i] = float(((nWidth - m_ptDefect[nCam][i].x) *  m_dScaleFactorX[nCam]) + m_dCalibSttX[nCam]);//Camera Reverse
			m_fReturnY[nCam][i] = float(( float(m_nCameraHeight - m_ptDefect[nCam][i].y) *  m_dScaleFactorY[nCam]) + m_dCalibSttY[nCam]);
		}
		else
		{
			m_fReturnX[nCam][i] = float((m_ptDefect[nCam][i].x *  m_dScaleFactorX[nCam]) + m_dCalibSttX[nCam]);//Camera Reverse
			m_fReturnY[nCam][i] = float(( float(m_nCameraHeight - m_ptDefect[nCam][i].y) *  m_dScaleFactorY[nCam]) + m_dCalibSttY[nCam]);
		}
		if(m_fReturnX[nCam][i] < 0) m_fReturnX[nCam][i] = 0;
		if(m_fReturnY[nCam][i] < 0) m_fReturnY[nCam][i] = 0;

		//Scratch Y Pos 수정.
		//Y = y+X*tan(m_dOpticsAngle)
//		m_nInspDirection = 2;
		//33 = 0.64940759319751057698206291131145
		//30 = 0.57735026918962576450914878050196);//tan(m_dOpticsAngle));
		//33.5 = 0.66188556119569151791452786950945
/*		if(m_strMachineName == "CC02")
		{
			if(nLine == GL3 && m_nInspDirection[nCam]==3)//2동 2호기 사선 방향 역방향 추가할것..
			{
				m_fReturnY[nCam][i] = m_fReturnY[nCam][i]+ float(((nWidth-m_ptDefect[nCam][i].x) *  m_dScaleFactorX[nCam])*0.5773);//0.57735026918962576450914878050196);//tan(m_dOpticsAngle));
			}
			else if(nLine == GL3 && m_nInspDirection[nCam]==2)
			{
				m_fReturnY[nCam][i] = m_fReturnY[nCam][i]- float((m_ptDefect[nCam][i].x *  m_dScaleFactorX)*0.5773);//0.57735026918962576450914878050196);//tan(m_dOpticsAngle));
			}
		}
		else
		{
			if(nLine == GL3 && m_nInspDirection[nCam]==3)//2동 2호기 사선 방향 역방향 추가할것..
			{
				m_fReturnY[nCam][i] = m_fReturnY[nCam][i]- float(((nWidth-m_ptDefect[nCam][i].x) *  m_dScaleFactorX)*0.5773);//0.57735026918962576450914878050196);//tan(m_dOpticsAngle));
			}
			else if(nLine == GL3 && m_nInspDirection[nCam]==2)
			{
				m_fReturnY[nCam][i] = m_fReturnY[nCam][i]+ float((m_ptDefect[nCam][i].x *  m_dScaleFactorX)*0.5773);//0.57735026918962576450914878050196);//tan(m_dOpticsAngle));
			}
		}
*/
	}
}

int CData::LaneCheck(int nCam,int xpos,int nLine,int nreverse)
{
//	m_nDefectLane;m_nEpcPos = 1;left 2right
	int nLane = 0;
	int nx1 = nCam*CAM_WIDTH_CIS+xpos;
	if(nLine<4){
		nLane = 0;
	}
	else if(nLine==4 ||nLine==6){//전체 폭의 절반
		nLane = 2;
	}
	else if(nLine==8){//무지 코팅이 한셋트 EPC 기준
		nLane = 3;
	}
	else if(nLine==10){
		nLane = 4;
	}
	else{
		nLane = 2;
	}

	nLane = FindLane( nLine, nreverse);
	for(int i=0;i<nLane;i++){
		if(nx1>=m_nLanePos[i][0] && nx1<m_nLanePos[i][1] )
		{
			nLane = i+1;
			return nLane;
		}
	}

	return nLane;
}
int CData::LaneCheckFull(int nCam,int xpos,int nLine,int nreverse)
{
	//	m_nDefectLane;m_nEpcPos = 1;left 2right
	int nLane = 0;
	int nx1 = nCam*CAM_WIDTH_CIS+xpos;
	if(nLine<4){
		nLane = 0;
	}
	else if(nLine==4 ||nLine==6){//전체 폭의 절반
		nLane = 2;
	}
	else if(nLine==8){//무지 코팅이 한셋트 EPC 기준
		nLane = 3;
	}
	else if(nLine==10){
		nLane = 4;
	}
	else{
		nLane = 2;
	}

	nLane = FindLane( nLine, nreverse);
	for(int i=0;i<nLane;i++){
		if(nx1>=m_nLanePos[i][0] && nx1<m_nLanePos[i][1] )
		{
			nLane = i+1;
			return nLane;
		}
	}

	return nLane;
}
int CData::FindLane(int nLine,int nreverse)
{
	//	m_nDefectLane;m_nEpcPos = 1;left 2right
	nLine = m_nNewLineCount;//m_dNewLineEdgeData1
	int nLane = 0,nc=0;
	if(nLine<4){
		nLane = 0;
	}
	else if(nLine==4 ||nLine==6){//전체 폭의 절반
		nLane = 2;
	}
	else if(nLine==8){//무지 코팅이 한셋트 EPC 기준
		nLane = 3;
	}
	else if(nLine==10){
		nLane = 4;
	}
	else{
		nLane = 2;
	}
	int nWd = m_dNewLineEdgeData1[nLine-1] - m_dNewLineEdgeData1[0];
	int nWd1 =  (m_dNewLineEdgeData1[nLine-1] + m_dNewLineEdgeData1[0])*0.5;
	if(nreverse==1){
		if(nLane==2){
			m_nLanePos[0][0] = m_dNewLineEdgeData1[0];
			m_nLanePos[0][1] = nWd1;
			m_nLanePos[1][0] = nWd1;
			m_nLanePos[1][1] = m_dNewLineEdgeData1[nLine-1];
		}
		else if(nLane==3){
			m_nLanePos[0][0] = m_dNewLineEdgeData1[0];
			m_nLanePos[0][1] = m_dNewLineEdgeData1[2];
			m_nLanePos[1][0] = m_dNewLineEdgeData1[2];
			m_nLanePos[1][1] = m_dNewLineEdgeData1[4];
			m_nLanePos[2][0] = m_dNewLineEdgeData1[4];
			m_nLanePos[2][1] = m_dNewLineEdgeData1[nLine-1];
		}
	}
	else{
		if(nLane==2){
			m_nLanePos[0][0] = m_dNewLineEdgeData1[nLine-1];
			m_nLanePos[0][1] = nWd1;
			m_nLanePos[1][0] = nWd1;
			m_nLanePos[1][1] = m_dNewLineEdgeData1[0];
		}
		else if(nLane==3){
			m_nLanePos[2][1] = m_dNewLineEdgeData1[0];
			m_nLanePos[2][0] = m_dNewLineEdgeData1[2];
			m_nLanePos[1][1] = m_dNewLineEdgeData1[2];
			m_nLanePos[1][0] = m_dNewLineEdgeData1[4];
			m_nLanePos[0][1] = m_dNewLineEdgeData1[4];
			m_nLanePos[0][0] = m_dNewLineEdgeData1[nLine-1];
		}

	}

	return nLane;
}
