#ifndef SLITINSPECT_
#define SLITINSPECT_

#define MAX_FRAME_NG	1000		//�� Frame���� ã�� �� �ִ� �ҷ��� �ִ� �� 
#define MAX_NG_POINTS	100			//�� ROI���� ã�� �� �ִ� �ҷ��� �ִ�� 
#define I_WIDTH			640			//�˻� ROI X���� �ִ밪 
#define I_HEIGHT		64			//�˻� ROI Y���� �ִ밪 
#define I_HALFWIDTH		320			//�˻� Area�� 2�ȼ��� ��� �˻��ϹǷ� I_WIDTH�� �� 
#define MAX_Y_EDGE		50			//�ѹ� �˻翡 ã�� Edge�ִ� ��(�����δ� 50-20)��
//#define SHOW_GRAPHIC				//Graphic���� ��� Display (VMaster������ �����)			//@KILL
//#define USE_VMASTER					//VMaster���� ����Ҷ��� �� define�� �־�� �Ѵ�.			//@KILL


//Teaching Data 
typedef struct TEACHDATA_
{
	int     nOneFrameGrabCount;						//1 Frame�� ��� Area Frame�� �����Ǿ� �ֳ�.
	double  dOneFrameLength;						//1 Frame ���� ����      
	int		nSkip;									//�׻� 2�� �����.
	int     nMinEdgeCount;							//Y���� 1�� �ּ� Edge�� 
	int		nMinDepth;								//20~50 ������ ������ (���� ���� ������ ������ ���߸� ��)
	int     nMaxMinRange;							// nBlackValueMaxMin, nWhiteValueMaxMin, dBlackThickMaxMin, dWhiteThickMaxMin ���Ҷ� ����ϴ� Max-Min���� ã�� Range

	bool   bSlitInspection;							//  True�̸� Slit�˻� False �̸� �Ϲݰ˻� 
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


	double	dBlackMin, dBlackMax;					//�漱�� �β��� ���� 
	double	dWhiteMin, dWhiteMax;					//�鼱�� �β��� ����
	double	dPeekMax;								//Edge�� ���� ���°˻�  5Pixel�� ���� �߰����� �� �� �̻� Ƣ�� �ҷ�ó�� 
	int		nBlackValueMaxMin, nWhiteValueMaxMin;	//���� �ȼ������� ��Ⱚ�� Max-Min������ �ҷ� ã��.
	int		nBlackValueSlope,  nWhiteValueSlope;	//�漱/�鼱�� �߽��� ���� ����� ��ȭ
	double  dBlackThickMaxMin,dWhiteThickMaxMin;	//���� �ȼ������� Max-Min������ �ҷ� ã��.
	double  dBlackThickSlope, dWhiteThickSlope;		//���� �ȼ��������� �β��� ��ȭ��


}TEACHDATA;

// �� Frame�� ����� �����ϴ� ����Ÿ 
typedef struct FRAMERESULT_
{
	double dWhiteWidth;
	double dBlackWidth;

	int		nNGCount;
	int		nNGPosX[MAX_FRAME_NG];		// 1 Frame������ ��ġ (X)
	int		nNGPosY[MAX_FRAME_NG];		// 1 Frame������ ��ġ (Y)
	int		nNGType[MAX_FRAME_NG];		// 1:������  2:�߰���  3: �β��� ����  4: Edge����  5:��Ⱚ���� 
	double  dNGPosXReal[MAX_FRAME_NG];	// 1 Frame���� ���� ���� ���� ���� (X)
	double  dNGPosYReal[MAX_FRAME_NG];	// 1 Frame���� ���� ���� ���� ���� (Y) 

}FRAMERESULT;

typedef struct RESULTDATA_
{
	double dWhiteWidth;
	double dBlackWidth;
	int	   nXEdgeCount;					//Y ���� Edge���������� ���� Ƚ�� 
	int    nTop;						// Y���� Data������ 
	int    nLeft;						// X���� Data������ 

	int nNGLineBroken;					//������ Line�� �־ ����� ��� 
	int nNGLineBrokenX[MAX_NG_POINTS];		
	int nNGLineBrokenY[MAX_NG_POINTS];

	int nNGLineAdd;						//�߰��� Line�� �־ ����� ��� 
	int nNGLineAddX[MAX_NG_POINTS];		
	int nNGLineAddY[MAX_NG_POINTS];

	int nNGCountThick;					//Line�� ���� �о ����� ��� 
	int nNGThickX[MAX_NG_POINTS];
	int nNGThickY[MAX_NG_POINTS];
	double dNGThickness[MAX_NG_POINTS];

	int nNGThickSlope;					//Line�� ���� ������ �ҷ� ���� 
	int nNGThickSlopeX[MAX_NG_POINTS];
	int nNGThickSlopeY[MAX_NG_POINTS];
	double dNGThickSlope[MAX_NG_POINTS];

	int nNGEdgePeek;					//Edge�� ���������� ���� ���ؼ� ����� ���  
	int nNGEdgePeekX[MAX_NG_POINTS];
	int nNGEdgePeekY[MAX_NG_POINTS];
	double dNGEdgePeek[MAX_NG_POINTS];

	int nNGCenterGray;					//�漱, �鼱�� �߽� ��� ��ȭ�� �ҷ� ����
	int nNGCenterGrayX[MAX_NG_POINTS];	
	int nNGCenterGrayY[MAX_NG_POINTS];
	double dNGCenterGray[MAX_NG_POINTS];

}RESULTDATA;
#endif

extern int			g_nLeftRightCut;	//Save�Ǵ� ���� (�˻�� ���� �ٸ� ����)  0 : ROI������ Full�� ���, 1: Left Cut,  2:Right Cut  3:All Cut
extern TEACHDATA	g_Teach;			//Save�Ǵ� ���� (�˻�� ��� ���� ����ϴ� ����)
extern FRAMERESULT	g_FrameResult;		//Save���� �ʰ� ���α׷� �����߿��� ����ϴ� ���� 

#ifndef USE_VMASTER
	int SLIT_Inspect(LPBYTE fm, int left, int top, int right, int bottom, int pitch, int nLeftRight);
	int SLIT_InspectROI(LPBYTE fm, int left, int top, int right, int bottom, int pitch, int nLeftRight, TEACHDATA data, RESULTDATA *result);
	int SLIT_EdgeArray(LPBYTE fm, int left, int top, int right, int bottom, int pitch, int nLeftRight, TEACHDATA data, RESULTDATA *result);
	int SLIT_LineData(LPBYTE fm, int pitch, TEACHDATA data, RESULTDATA *result);
#endif
void SLIT_RemoveAdjacent(int XRange, int YRange, int nMaxCount);	 //�̿��ϴ� �ҷ��� ���� �Լ� 
void SLIT_InspectROIResult(int left, int top, RESULTDATA result);	 //�� ROI���� ���� �ҷ��� �� ������ ���Ѱ��� g_FrameResult�� �ִ´�.
int SLIT_FindLeftEnd(int nLeftRight, LPBYTE fm, int left, int top, int right, int bottom, int pitch, TEACHDATA data);
int SLIT_FindYEdge(int * pData, int nCount, int nMinDepth, float *pEdge, int *dir);
int SLIT_MakeLine(bool bFirstCall, int nXCount, int nEdge, float *dEdge, int *dir, int nLeftPoint, TEACHDATA data, RESULTDATA *result);
void SLIT_DefaultData();
int SLIT_Save(char *filename);
int SLIT_Load(char *filename);


