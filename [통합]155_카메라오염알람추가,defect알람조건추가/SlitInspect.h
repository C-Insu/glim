#ifndef SLITINSPECT_
#define SLITINSPECT_

#define MAX_FRAME_NG	1000		//한 Frame에서 찾을 수 있는 불량의 최대 수 
#define MAX_NG_POINTS	100			//한 ROI에서 찾을 수 있는 불량의 최대수 
#define I_WIDTH			640			//검사 ROI X방향 최대값 
#define I_HEIGHT		64			//검사 ROI Y방향 최대값 
#define I_HALFWIDTH		320			//검사 Area를 2픽셀씩 엮어서 검사하므로 I_WIDTH의 반 
#define MAX_Y_EDGE		50			//한번 검사에 찾을 Edge최대 수(실제로는 50-20)임
//#define SHOW_GRAPHIC				//Graphic으로 결과 Display (VMaster에서만 사용함)			//@KILL
//#define USE_VMASTER					//VMaster에서 사용할때는 이 define이 있어야 한다.			//@KILL


//Teaching Data 
typedef struct TEACHDATA_
{
	int     nOneFrameGrabCount;						//1 Frame은 몇개의 Area Frame로 구성되어 있나.
	double  dOneFrameLength;						//1 Frame 실제 길이      
	int		nSkip;									//항상 2로 사용함.
	int     nMinEdgeCount;							//Y방향 1줄 최소 Edge수 
	int		nMinDepth;								//20~50 정도가 적절함 (아주 작은 변동도 보려면 낮추면 됨)
	int     nMaxMinRange;							// nBlackValueMaxMin, nWhiteValueMaxMin, dBlackThickMaxMin, dWhiteThickMaxMin 구할때 사용하는 Max-Min값을 찾을 Range

	bool   bSlitInspection;							//  True이면 Slit검사 False 이면 일반검사 
	bool   bBlackThickness;							//  dBlackMin, dBlackMax
	bool   bWhiteThickness ;						//	dWhiteMin, dWhiteMax
	bool   bXEdgeSlope;								//	dPeekMax
	bool   bBlackThickLongChange;					//	dBlackThickMaxMin
	bool   bBlackThickShortChange;					//  dBlackThickSlope
	bool   bWhiteThickLongChange;					//  dWhiteThickMaxMin
	bool   bWhiteThickShortChange;					//	dWhiteThickSlope
	bool   bBlackValueLongChange;					//	nBlackValueMaxMin
	bool   bBlackValueShortChange;					//	nBlackValueSlope	
	bool   bWhiteValueLongChange;					//	nWhiteValueMaxMin
	bool   bWhiteValueShortChange;					//	nWhiteValueSlope


	double	dBlackMin, dBlackMax;					//흑선의 두께의 범위 
	double	dWhiteMin, dWhiteMax;					//백선의 두께의 범위
	double	dPeekMax;								//Edge의 연결 상태검사  5Pixel로 부터 중간값이 이 값 이상 튀면 불량처리 
	int		nBlackValueMaxMin, nWhiteValueMaxMin;	//일정 픽셀내에서 밝기값의 Max-Min값으로 불량 찾음.
	int		nBlackValueSlope,  nWhiteValueSlope;	//흑선/백선의 중심을 따라서 밝기의 변화
	double  dBlackThickMaxMin,dWhiteThickMaxMin;	//일정 픽셀내에서 Max-Min값으로 불량 찾음.
	double  dBlackThickSlope, dWhiteThickSlope;		//일정 픽셀간격으로 두께의 변화양


}TEACHDATA;

// 한 Frame의 결과를 저장하는 데이타 
typedef struct FRAMERESULT_
{
	double dWhiteWidth;
	double dBlackWidth;

	int		nNGCount;
	int		nNGPosX[MAX_FRAME_NG];		// 1 Frame에서의 위치 (X)
	int		nNGPosY[MAX_FRAME_NG];		// 1 Frame에서의 위치 (Y)
	int		nNGType[MAX_FRAME_NG];		// 1:끊어짐  2:추가됨  3: 두께의 변동  4: Edge변동  5:밝기값변동 
	double  dNGPosXReal[MAX_FRAME_NG];	// 1 Frame으로 부터 실제 길이 추정 (X)
	double  dNGPosYReal[MAX_FRAME_NG];	// 1 Frame으로 부터 실제 길이 추정 (Y) 

}FRAMERESULT;

typedef struct RESULTDATA_
{
	double dWhiteWidth;
	double dBlackWidth;
	int	   nXEdgeCount;					//Y 방향 Edge정상적으로 구한 횟수 
	int    nTop;						// Y방향 Data시작점 
	int    nLeft;						// X방향 Data시작점 

	int nNGLineBroken;					//끊어진 Line이 있어서 검출된 경우 
	int nNGLineBrokenX[MAX_NG_POINTS];		
	int nNGLineBrokenY[MAX_NG_POINTS];

	int nNGLineAdd;						//추가된 Line이 있어서 검출된 경우 
	int nNGLineAddX[MAX_NG_POINTS];		
	int nNGLineAddY[MAX_NG_POINTS];

	int nNGCountThick;					//Line의 폭이 넓어서 검출된 경우 
	int nNGThickX[MAX_NG_POINTS];
	int nNGThickY[MAX_NG_POINTS];
	double dNGThickness[MAX_NG_POINTS];

	int nNGThickSlope;					//Line의 폭의 변동값 불량 검출 
	int nNGThickSlopeX[MAX_NG_POINTS];
	int nNGThickSlopeY[MAX_NG_POINTS];
	double dNGThickSlope[MAX_NG_POINTS];

	int nNGEdgePeek;					//Edge가 순간적으로 많이 변해서 검출된 경우  
	int nNGEdgePeekX[MAX_NG_POINTS];
	int nNGEdgePeekY[MAX_NG_POINTS];
	double dNGEdgePeek[MAX_NG_POINTS];

	int nNGCenterGray;					//흑선, 백선의 중심 밝기 변화로 불량 검출
	int nNGCenterGrayX[MAX_NG_POINTS];	
	int nNGCenterGrayY[MAX_NG_POINTS];
	double dNGCenterGray[MAX_NG_POINTS];

}RESULTDATA;
#endif

extern int			g_nLeftRightCut;	//Save되는 변수 (검사기 별로 다른 변수)  0 : ROI영역을 Full로 사용, 1: Left Cut,  2:Right Cut  3:All Cut
extern TEACHDATA	g_Teach;			//Save되는 변수 (검사기 모두 같이 사용하는 변수)
extern FRAMERESULT	g_FrameResult;		//Save되지 않고 프로그램 실행중에만 사용하는 변수 

#ifndef USE_VMASTER
	int SLIT_Inspect(LPBYTE fm, int left, int top, int right, int bottom, int pitch, int nLeftRight);
	int SLIT_InspectROI(LPBYTE fm, int left, int top, int right, int bottom, int pitch, int nLeftRight, TEACHDATA data, RESULTDATA *result);
	int SLIT_EdgeArray(LPBYTE fm, int left, int top, int right, int bottom, int pitch, int nLeftRight, TEACHDATA data, RESULTDATA *result);
	int SLIT_LineData(LPBYTE fm, int pitch, TEACHDATA data, RESULTDATA *result);
#endif
void SLIT_RemoveAdjacent(int XRange, int YRange, int nMaxCount);	 //이웃하는 불량을 묶는 함수 
void SLIT_InspectROIResult(int left, int top, RESULTDATA result);	 //각 ROI에서 구한 불량중 그 정도가 심한것을 g_FrameResult에 넣는다.
int SLIT_FindLeftEnd(int nLeftRight, LPBYTE fm, int left, int top, int right, int bottom, int pitch, TEACHDATA data);
int SLIT_FindYEdge(int * pData, int nCount, int nMinDepth, float *pEdge, int *dir);
int SLIT_MakeLine(bool bFirstCall, int nXCount, int nEdge, float *dEdge, int *dir, int nLeftPoint, TEACHDATA data, RESULTDATA *result);
void SLIT_DefaultData();
int SLIT_Save(char *filename);
int SLIT_Load(char *filename);


