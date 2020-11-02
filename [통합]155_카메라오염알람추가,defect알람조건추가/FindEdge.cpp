#include "stdafx.h"
#include "FindEdge.h"
#include "math.h"

//////////////////////////////////////////////////////////////////////////////////////////
//
//      Local Functions( FindEdge.h에 있는 함수들 내부에서 사용하는 Subroutine들)
//
//////////////////////////////////////////////////////////////////////////////////////////
//
// (x1,y1)-(x2,y2)를 1Pixel간격으로 Sampling하는 함수 
int GetLineData(LPBYTE fm, int x1, int y1, int x2, int y2, int nPitch,
				double *pX, double *pY, int *pGrayValue);
// 두개의 직선으로부터 Cross하는 점 구하기
int FindCrossPoint(double t1, double a1, double b1,
	  			   double t2, double a2, double b2, double *cx, double *cy);
//////////////////////////////////////////////////////////////////////////////////////////

#define MAXEDGENUMBER   100    //한 Line에서 구할수 있는 최대 Edge의 수 (임의로 증가가능)
double PixelX[800], PixelY[800];
double EdgeM[MAXEDGENUMBER];
int   PixelV[800];

//////////////////////////////////////////////////////////////////////////////////////////


int LN_FindEdge1_B2W(int n, int *data, double *edge, int *slope)
{
	int i;
	int maxslope, maxpos;
	double Temp_A, Temp_B;
	
	if(n<2)	return -1;

	maxslope=maxpos=0;
	for(i=1;i<n-1;i++)
		if( (data[i+1]-data[i-1])> maxslope)
		{
			maxpos=i;
			maxslope=(data[i+1]-data[i-1]);
		}
		
	if(maxslope==0) return -2;

	*slope=abs(maxslope);
	if(maxpos<=2 || maxpos>=(n-3))
	{
		*edge=(double)maxpos;
	}
	else
	{
		if(fabs((double)data[maxpos+2]-(double)data[maxpos]) < fabs((double)data[maxpos]-(double)data[maxpos-2]))
		{
			maxpos-=1;
		}

		Temp_A=(double)fabs((double)data[maxpos+2]+(double)data[maxpos-2]-2*(double)data[maxpos]);
		Temp_B=(double)fabs((double)data[maxpos+3]+(double)data[maxpos-1]-2*(double)data[maxpos+1]);

		if((Temp_A+Temp_B)!=0)
			*edge=(double)maxpos+Temp_A/(Temp_A+Temp_B);	
		else
			*edge=(double)maxpos;
	}

	return 1;
}

int LN_FindEdge1_W2B(int n, int *data, double *edge, int *slope)
{
	int i;
	int maxslope, maxpos;
	double Temp_A, Temp_B;
	
	if(n<2)	return -1;

	maxslope=maxpos=0;
	for(i=1;i<n-1;i++)
		if( (data[i+1]-data[i-1])< maxslope)
		{
			maxpos=i;
			maxslope=(data[i+1]-data[i-1]);
		}
		
	if(maxslope==0) return -2;

	*slope=abs(maxslope);
	if(maxpos<=2 || maxpos>=(n-3))
	{
		*edge=(double)maxpos;
	}
	else
	{
		if(fabs((double)data[maxpos+2]-(double)data[maxpos]) < fabs((double)data[maxpos]-(double)data[maxpos-2]))
		{
			maxpos-=1;
		}

		Temp_A=(double)fabs((double)data[maxpos+2]+(double)data[maxpos-2]-2*(double)data[maxpos]);
		Temp_B=(double)fabs((double)data[maxpos+3]+(double)data[maxpos-1]-2*(double)data[maxpos+1]);

		if((Temp_A+Temp_B)!=0)
			*edge=(double)maxpos+Temp_A/(Temp_A+Temp_B);	
		else
			*edge=(double)maxpos;
	}

	return 1;
}

int LN_FindEdge1_ABS(int n, int *data, double *edge, int *slope, int *dir)
{
	int i;
	int maxslope, maxpos;
	double Temp_A, Temp_B;
	
	if(n<2)	return -1;

	maxslope=maxpos=0;
	for(i=1;i<n-1;i++)
		if( abs(data[i+1]-data[i-1])> maxslope)
		{
			maxpos=i;
			maxslope=abs(data[i+1]-data[i-1]);
		}
		
	if(maxslope==0) return -2;

	*slope=abs(maxslope);
	
	if(data[maxpos+1]>data[maxpos]) *dir=1; //Black->White
	else                            *dir=0;	//White->Black

	if(maxpos<=2 || maxpos>=(n-3))
	{
		*edge=(double)maxpos;
	}
	else
	{
		if(fabs((double)data[maxpos+2]-(double)data[maxpos]) < fabs((double)data[maxpos]-(double)data[maxpos-2]))
		{
			maxpos-=1;
		}

		Temp_A=(double)fabs((double)data[maxpos+2]+(double)data[maxpos-2]-2*(double)data[maxpos]);
		Temp_B=(double)fabs((double)data[maxpos+3]+(double)data[maxpos-1]-2*(double)data[maxpos+1]);

		if((Temp_A+Temp_B)!=0)
			*edge=(double)maxpos+Temp_A/(Temp_A+Temp_B);	
		else
			*edge=(double)maxpos;
	}

	return 1;
}

int LN_FindEdgePos1_B2W(LPBYTE fm, int x1, int y1, int x2, int y2, int nPitch,
						double *edgeX, double *edgeY, int *slope)
{
	int nData;
	double edge, fLineLength;

    fLineLength=(double)sqrt((double)(x1-x2)*(double)(x1-x2)+(double)(y1-y2)*(double)(y1-y2));

	nData=GetLineData(fm, x1, y1, x2, y2, nPitch, PixelX, PixelY, PixelV);
	if(nData<0) return -1;

	if(LN_FindEdge1_B2W(nData, PixelV, &edge, slope)<0) return -2;

	*edgeX=(x1*(fLineLength-edge)+x2*edge)/fLineLength;
	*edgeY=(y1*(fLineLength-edge)+y2*edge)/fLineLength;

	return 1;
}

int LN_FindEdgePos1_W2B(LPBYTE fm, int x1, int y1, int x2, int y2, int nPitch,
						double *edgeX, double *edgeY, int *slope)
{
	int nData;
	double edge, fLineLength;

    fLineLength=(double)sqrt((double)(x1-x2)*(double)(x1-x2)+(double)(y1-y2)*(double)(y1-y2));

	nData=GetLineData(fm, x1, y1, x2, y2, nPitch, PixelX, PixelY, PixelV);
	if(nData<0) return -1;

	if(LN_FindEdge1_W2B(nData, PixelV, &edge, slope)<0) return -2;

	*edgeX=(x1*(fLineLength-edge)+x2*edge)/fLineLength;
	*edgeY=(y1*(fLineLength-edge)+y2*edge)/fLineLength;

	return 1;
}

int LN_FindEdgePos1_ABS(LPBYTE fm, int x1, int y1, int x2, int y2, int nPitch,
						double *edgeX, double *edgeY, int *slope, int *dir)
{
	int nData;
	double edge, fLineLength;

    fLineLength=(double)sqrt((double)(x1-x2)*(double)(x1-x2)+(double)(y1-y2)*(double)(y1-y2));

	nData=GetLineData(fm, x1, y1, x2, y2, nPitch, PixelX, PixelY, PixelV);
	if(nData<0) return -1;

	if(LN_FindEdge1_ABS(nData, PixelV, &edge, slope, dir)<0) return -2;

	*edgeX=(x1*(fLineLength-edge)+x2*edge)/fLineLength;
	*edgeY=(y1*(fLineLength-edge)+y2*edge)/fLineLength;

	return 1;
}

int LN_FindEdge1st_B2W(int n, int *data, int slope, double *edge)
{
	int i;
	int maxslope, maxpos;
	double Temp_A, Temp_B;
	
	if(n<2)	return -1;

	maxpos=-1;
	for(i=1;i<n-1;i++)
		if( (data[i+1]-data[i]) >= slope)
		{
			maxslope=(data[i+1]-data[i-1]);
			maxpos=i;
			break;
		}
	
	if(maxpos<0) return -2;

	for(i=maxpos+1;i<n-1;i++)
	{
		if( (data[i+1]-data[i]) >= maxslope)
		{
			maxslope=(data[i+1]-data[i]);
			maxpos=i;
		}
		else 
			break;
	}		

	if(maxpos<=2 || maxpos>=(n-3))
	{
		*edge=(double)maxpos;
	}
	else
	{
		if(fabs((double)data[maxpos+2]-(double)data[maxpos]) < fabs((double)data[maxpos]-(double)data[maxpos-2]))
		{
			maxpos-=1;
		}

		Temp_A=(double)fabs((double)data[maxpos+2]+(double)data[maxpos-2]-2*(double)data[maxpos]);
		Temp_B=(double)fabs((double)data[maxpos+3]+(double)data[maxpos-1]-2*(double)data[maxpos+1]);

		if((Temp_A+Temp_B)!=0)
			*edge=(double)maxpos+Temp_A/(Temp_A+Temp_B);	
		else
			*edge=(double)maxpos;
	}

	return 1;
}

int LN_FindEdge1st_W2B(int n, int *data, int slope, double *edge)
{
	int i;
	int maxpos,maxslope;
	double Temp_A, Temp_B;
	
	if(n<2)	return -1;

	if(slope>0) slope*=-1;

	maxpos=-1;
	for(i=1;i<n-1;i++)
		if( (data[i+1]-data[i-1]) <= slope)
		{
			maxslope=(data[i+1]-data[i-1]);
			maxpos=i;
			break;
		}

	if(maxpos<0) return -2;

	for(i=maxpos+1;i<n-1;i++)
	{
		if( (data[i+1]-data[i-1]) <= maxslope)
		{
			maxslope=(data[i+1]-data[i-1]);
			maxpos=i;
		}
		else 
			break;
	}
		
	if(maxpos<=2 || maxpos>=(n-3))
	{
		*edge=(double)maxpos;
	}
	else
	{
		if(fabs((double)data[maxpos+2]-(double)data[maxpos]) < fabs((double)data[maxpos]-(double)data[maxpos-2]))
		{
			maxpos-=1;
		}

		Temp_A=(double)fabs((double)data[maxpos+2]+(double)data[maxpos-2]-2*(double)data[maxpos]);
		Temp_B=(double)fabs((double)data[maxpos+3]+(double)data[maxpos-1]-2*(double)data[maxpos+1]);

		if((Temp_A+Temp_B)!=0)
			*edge=(double)maxpos+Temp_A/(Temp_A+Temp_B);	
		else
			*edge=(double)maxpos;
	}

	return 1;
}

int LN_FindEdge1st_ABS(int n, int *data, int slope, double *edge, int *dir)
{
	int i;
	int maxpos, maxslope;
	double Temp_A, Temp_B;
	
	if(n<2)	return -1;

	maxpos=-1;
	for(i=1;i<n-1;i++)
		if( abs(data[i+1]-data[i-1]) >= slope)
		{
			maxslope=abs(data[i+1]-data[i-1]);
			maxpos=i;
			break;
		}

	if(maxpos<0) return -2;

	for(i=maxpos+1;i<n-1;i++)
	{
		if( abs(data[i+1]-data[i-1]) >= maxslope)
		{
			maxslope=abs(data[i+1]-data[i-1]);
			maxpos=i;
		}
		else 
			break;
	}
		
	if(data[maxpos+1]>data[maxpos]) *dir=1; //Black->White
	else                            *dir=0;	//White->Black

	if(maxpos<=2 || maxpos>=(n-3))
	{
		*edge=(double)maxpos;
	}
	else
	{
		if(fabs((double)data[maxpos+2]-(double)data[maxpos]) < fabs((double)data[maxpos]-(double)data[maxpos-2]))
		{
			maxpos-=1;
		}

		Temp_A=(double)fabs((double)data[maxpos+2]+(double)data[maxpos-2]-2*(double)data[maxpos]);
		Temp_B=(double)fabs((double)data[maxpos+3]+(double)data[maxpos-1]-2*(double)data[maxpos+1]);

		if((Temp_A+Temp_B)!=0)
			*edge=(double)maxpos+Temp_A/(Temp_A+Temp_B);	
		else
			*edge=(double)maxpos;
	}

	return 1;
}

int LN_FindEdgePos1st_B2W(LPBYTE fm, int x1, int y1, int x2, int y2, int nPitch, int slope,
						  double *edgeX, double *edgeY)
{
	int nData;
	double edge, fLineLength;

    fLineLength=(double)sqrt((double)(x1-x2)*(double)(x1-x2)+(double)(y1-y2)*(double)(y1-y2));

	nData=GetLineData(fm, x1, y1, x2, y2, nPitch, PixelX, PixelY, PixelV);
	if(nData<0) return -1;

	if(LN_FindEdge1st_B2W(nData, PixelV, slope, &edge)<0) return -2;

	*edgeX=(x1*(fLineLength-edge)+x2*edge)/fLineLength;
	*edgeY=(y1*(fLineLength-edge)+y2*edge)/fLineLength;

	return 1;
}

int LN_FindEdgePos1st_W2B(LPBYTE fm, int x1, int y1, int x2, int y2, int nPitch, int slope,
						  double *edgeX, double *edgeY)
{
	int nData;
	double edge, fLineLength;

    fLineLength=(double)sqrt((double)(x1-x2)*(double)(x1-x2)+(double)(y1-y2)*(double)(y1-y2));

	nData=GetLineData(fm, x1, y1, x2, y2, nPitch, PixelX, PixelY, PixelV);
	if(nData<0) return -1;

	if(LN_FindEdge1st_W2B(nData, PixelV, slope, &edge)<0) return -2;

	*edgeX=(x1*(fLineLength-edge)+x2*edge)/fLineLength;
	*edgeY=(y1*(fLineLength-edge)+y2*edge)/fLineLength;

	return 1;
}

int LN_FindEdgePos1st_ABS(LPBYTE fm, int x1, int y1, int x2, int y2, int nPitch, int slope,
						  double *edgeX, double *edgeY, int *dir)
{
	int nData;
	double edge, fLineLength;

    fLineLength=(double)sqrt((double)(x1-x2)*(double)(x1-x2)+(double)(y1-y2)*(double)(y1-y2));

	nData=GetLineData(fm, x1, y1, x2, y2, nPitch, PixelX, PixelY, PixelV);
	if(nData<0) return -1;

	if(LN_FindEdge1st_ABS(nData, PixelV, slope, &edge, dir)<0) return -2;

	*edgeX=(x1*(fLineLength-edge)+x2*edge)/fLineLength;
	*edgeY=(y1*(fLineLength-edge)+y2*edge)/fLineLength;

	return 1;
}


int LN_FindEdgeM_B2W(int n, int *data, int slope, double *edge)
{
	int i, nCount=0;
	int offset=0, flag;
	double  edge1;

	while(1)
	{
		if(LN_FindEdge1st_B2W(n-offset, &data[offset], slope, &edge1)<0) break;
		edge[nCount++]=(double)offset+edge1;
		flag=0;
		for(i=offset+(int)edge1+1;i<n-1;i++)
			if((data[i+1]-data[i-1]) <=0)
			{
				offset=i;
				flag=1;
				break;
			}
		if(!flag) break;
		if(nCount==MAXEDGENUMBER) break;
	}	
	
	return nCount;
}	
	
int LN_FindEdgeM_W2B(int n, int *data, int slope, double *edge)
{
	int i, nCount=0;
	int offset=0, flag;
	double  edge1;

	while(1)
	{
		if(LN_FindEdge1st_W2B(n-offset, &data[offset], slope, &edge1)<0) break;
		edge[nCount++]=(double)offset+edge1;
		flag=0;
		for(i=offset+(int)edge1+1;i<n-1;i++)
			if((data[i+1]-data[i-1]) >=0)
			{
				offset=i;
				flag=1;
				break;
			}
		if(!flag) break;
		if(nCount==MAXEDGENUMBER) break;
	}	
	
	return nCount;
}	

int LN_FindEdgeM_ABS(int n, int *data, int slope, double *edge, int *dir)
{
	int i, nCount=0;
	int offset=0, flag, dir1;
	double  edge1;

	while(1)
	{
		if(LN_FindEdge1st_ABS(n-offset, &data[offset], slope, &edge1, &dir1)<0) break;
		dir[nCount]=dir1;
		edge[nCount++]=(double)offset+edge1;
		flag=0;
		for(i=offset+(int)edge1+1;i<n-1;i++)
			if((data[i+1]-data[i])*(data[i]-data[i-1]) <= 0)
			{
				offset=i;
				flag=1;
				break;
			}
		if(!flag) break;
		if(nCount==MAXEDGENUMBER) break;
	}	
	
	return nCount;
}	

int LN_FindEdgePosM_B2W(LPBYTE fm, int x1, int y1, int x2, int y2, int nPitch, int slope,
						double *edgeX, double *edgeY)
{
	int i, nData;
	double fLineLength;
	int nEdge;

    fLineLength=(double)sqrt((double)(x1-x2)*(double)(x1-x2)+(double)(y1-y2)*(double)(y1-y2));

	nData=GetLineData(fm, x1, y1, x2, y2, nPitch, PixelX, PixelY, PixelV);
	if(nData<0) return -1;

	nEdge=LN_FindEdgeM_B2W(nData, PixelV, slope, EdgeM);

	for(i=0;i<nEdge;i++)
	{
		edgeX[i]=(x1*(fLineLength-EdgeM[i])+x2*EdgeM[i])/fLineLength;
		edgeY[i]=(y1*(fLineLength-EdgeM[i])+y2*EdgeM[i])/fLineLength;
	}
	return nEdge;
}

int LN_FindEdgePosM_W2B(LPBYTE fm, int x1, int y1, int x2, int y2, int nPitch, int slope,
						double *edgeX, double *edgeY)
{
	int i, nData;
	double fLineLength;
	int nEdge;

    fLineLength=(double)sqrt((double)(x1-x2)*(double)(x1-x2)+(double)(y1-y2)*(double)(y1-y2));

	nData=GetLineData(fm, x1, y1, x2, y2, nPitch, PixelX, PixelY, PixelV);
	if(nData<0) return -1;

	nEdge=LN_FindEdgeM_W2B(nData, PixelV, slope, EdgeM);

	for(i=0;i<nEdge;i++)
	{
		edgeX[i]=(x1*(fLineLength-EdgeM[i])+x2*EdgeM[i])/fLineLength;
		edgeY[i]=(y1*(fLineLength-EdgeM[i])+y2*EdgeM[i])/fLineLength;
	}
	return nEdge;
}

int LN_FindEdgePosM_ABS(LPBYTE fm, int x1, int y1, int x2, int y2, int nPitch, int slope,
						double *edgeX, double *edgeY, int *dir)
{
	int i, nData;
	double fLineLength;
	int nEdge;

    fLineLength=(double)sqrt((double)(x1-x2)*(double)(x1-x2)+(double)(y1-y2)*(double)(y1-y2));

	nData=GetLineData(fm, x1, y1, x2, y2, nPitch, PixelX, PixelY, PixelV);
	if(nData<0) return -1;

	nEdge=LN_FindEdgeM_ABS(nData, PixelV, slope, EdgeM, dir);

	for(i=0;i<nEdge;i++)
	{
		edgeX[i]=(x1*(fLineLength-EdgeM[i])+x2*EdgeM[i])/fLineLength;
		edgeY[i]=(y1*(fLineLength-EdgeM[i])+y2*EdgeM[i])/fLineLength;
	}
	return nEdge;
}

//return -1: (Left,top)-(right,bottom) Error
//		 -2: Memory Allocation Error
//       -3: Edge못찾음 
//		 
//        1: SUCCESS
int AR_FindEdge_T2B_B2W(LPBYTE fm, int left, int top, int right, int bottom, int nPitch,
						double *edgeX, double *edgeY)
{
	int i, nCount=0;
	int nData=right-left+1;
	int slope;
	double *edgeX1, *edgeY1;
	double l_t, l_a, l_b;  //Line함수의 Parameter (t*y=a*x+b)
	
	if(nData<2) return -1;
	edgeX1 = (double*)malloc(nData*sizeof(double));
	edgeY1 = (double*)malloc(nData*sizeof(double));
	if(edgeX1==0 || edgeY1==0) return -2;

	for(i=left;i<=right;i++)
	{
		if(LN_FindEdgePos1_B2W(fm, i, top, i, bottom, nPitch,&edgeX1[nCount], &edgeY1[nCount], &slope)>0)
			nCount++;
	}

	if(nCount>=2)
	{
		if(LineFitting(nCount, edgeX1, edgeY1, (int)(nCount*0.5), 0.1, &l_t, &l_a, &l_b)<0)
			return -2;

		if(FindCrossPoint(l_t, l_a, l_b, 0, -1, (double)(left+right)/2.0,edgeX,edgeY)<0) return -3;
		if(*edgeX<left || *edgeX>right || *edgeY<top && *edgeY>bottom) return -3;

	}
	else return -3;

	if(edgeX1) free(edgeX1);
	if(edgeY1) free(edgeY1);
	return 1;
}

//return -1: (Left,top)-(right,bottom) Error
//		 -2: Memory Allocation Error
//       -3: Edge못찾음 
//		 
//        1: SUCCESS
int AR_FindEdge_T2B_W2B(LPBYTE fm, int left, int top, int right, int bottom, int nPitch,
						double *edgeX, double *edgeY)
{
	int i, nCount=0;
	int nData=right-left+1;
	int slope;
	double *edgeX1, *edgeY1;
	double l_t, l_a, l_b;  //Line함수의 Parameter (t*y=a*x+b)
	
	if(nData<2) return -1;
	edgeX1 = (double*)malloc(nData*sizeof(double));
	edgeY1 = (double*)malloc(nData*sizeof(double));
	if(edgeX1==0 || edgeY1==0) return -2;

	for(i=left;i<=right;i++)
	{
		if(LN_FindEdgePos1_W2B(fm, i, top, i, bottom, nPitch,&edgeX1[nCount], &edgeY1[nCount], &slope)>0)
			nCount++;
	}

	if(nCount>=2)
	{
		if(LineFitting(nCount, edgeX1, edgeY1, (int)(nCount*0.5), 0.1, &l_t, &l_a, &l_b)<0)
			return -2;

		if(FindCrossPoint(l_t, l_a, l_b, 0, -1, (double)(left+right)/2.0,edgeX,edgeY)<0) return -3;
		if(*edgeX<left || *edgeX>right || *edgeY<top && *edgeY>bottom) return -3;
	}
	else return -3;

	if(edgeX1) free(edgeX1);
	if(edgeY1) free(edgeY1);
	return 1;
}

//return -1: (Left,top)-(right,bottom) Error
//		 -2: Memory Allocation Error
//       -3: Edge못찾음 
//		 
//        1: SUCCESS
int AR_FindEdge_L2R_B2W(LPBYTE fm, int left, int top, int right, int bottom, int nPitch,
						double *edgeX, double *edgeY)
{
	int i, nCount=0;
	int nData=bottom-top+1;
	int slope;
	double *edgeX1, *edgeY1;
	double l_t, l_a, l_b;  //Line함수의 Parameter (t*y=a*x+b)
	
	if(nData<2) return -1;
	edgeX1 = (double*)malloc(nData*sizeof(double));
	edgeY1 = (double*)malloc(nData*sizeof(double));
	if(edgeX1==0 || edgeY1==0) return -2;

	for(i=top;i<=bottom;i++)
	{
		if(LN_FindEdgePos1_B2W(fm, left, i, right, i, nPitch,&edgeX1[nCount], &edgeY1[nCount], &slope)>0)
			nCount++;
	}

	if(nCount>=2)
	{
		if(LineFitting1(nCount, edgeX1, edgeY1, (int)(nCount*0.5), 0.1, &l_t, &l_a, &l_b)<0)
			return -2;

		if(FindCrossPoint(l_t, l_a, l_b, 1, 0, (double)(top+bottom)/2.0,edgeX,edgeY)<0) return -3;
		if(*edgeX<left || *edgeX>right || *edgeY<top && *edgeY>bottom) return -3;
	}
	else return -3;

	if(edgeX1) free(edgeX1);
	if(edgeY1) free(edgeY1);
	return 1;
}

//return -1: (Left,top)-(right,bottom) Error
//		 -2: Memory Allocation Error
//       -3: Edge못찾음 
//		 
//        1: SUCCESS
int AR_FindEdge_L2R_W2B(LPBYTE fm, int left, int top, int right, int bottom, int nPitch,
						double *edgeX, double *edgeY)
{
	int i, nCount=0;
	int nData=bottom-top+1;
	int slope;
	double *edgeX1, *edgeY1;
	double l_t, l_a, l_b;  //Line함수의 Parameter (t*y=a*x+b)
	
	if(nData<2) return -1;
	edgeX1 = (double*)malloc(nData*sizeof(double));
	edgeY1 = (double*)malloc(nData*sizeof(double));
	if(edgeX1==0 || edgeY1==0) return -2;

	for(i=top;i<=bottom;i++)
	{
		if(LN_FindEdgePos1_W2B(fm, left, i, right, i, nPitch,&edgeX1[nCount], &edgeY1[nCount], &slope)>0)
			nCount++;
	}

	if(nCount>=2)
	{
		if(LineFitting1(nCount, edgeX1, edgeY1, (int)(nCount*0.5), 0.1, &l_t, &l_a, &l_b)<0)
			return -2;

		if(FindCrossPoint(l_t, l_a, l_b, 1, 0, (double)(top+bottom)/2.0,edgeX,edgeY)<0) return -3;
		if(*edgeX<left || *edgeX>right || *edgeY<top && *edgeY>bottom) return -3;
	}
	else return -3;

	if(edgeX1) free(edgeX1);
	if(edgeY1) free(edgeY1);
	return 1;
}
int AR_FindEdge_B2T_B2W(LPBYTE fm, int left, int top, int right, int bottom, int nPitch,
						double *edgeX, double *edgeY)
{
	return AR_FindEdge_T2B_W2B(fm, left, top, right, bottom, nPitch,edgeX, edgeY);
}
int AR_FindEdge_B2T_W2B(LPBYTE fm, int left, int top, int right, int bottom, int nPitch,
						double *edgeX, double *edgeY)
{
	return AR_FindEdge_T2B_B2W(fm, left, top, right, bottom, nPitch,edgeX, edgeY);
}
int AR_FindEdge_R2L_B2W(LPBYTE fm, int left, int top, int right, int bottom, int nPitch,
						double *edgeX, double *edgeY)
{
	return AR_FindEdge_L2R_W2B(fm, left, top, right, bottom, nPitch,edgeX, edgeY);
}
int AR_FindEdge_R2L_W2B(LPBYTE fm, int left, int top, int right, int bottom, int nPitch,
						double *edgeX, double *edgeY)
{
	return AR_FindEdge_L2R_B2W(fm, left, top, right, bottom, nPitch,edgeX, edgeY);
}




/////////////////////////////////////////////////////////////////////////////////////
//
//	각종 LOCAL 함수들 
//
/////////////////////////////////////////////////////////////////////////////////////


// 함수설명 : 임의의 라인을 1Pixel 간격으로 ReSampling해주는 함수 
// return Value : 구한 좌표의 개수       
//               <0 FAILURE
int GetLineData(LPBYTE fm, int x1, int y1, int x2, int y2, int nPitch,
				double *pX, double *pY, int *pGrayValue)
{
	int i, nCount=0;
    double fLineLength;
	int	  nAbsX1_X2, nAbsY1_Y2;
	double t=1.0;
    double slope;
	int  N, M ; // Interpolation Function에서 사용하는 변수들 
	double a,b;  // f(a,b)=P(N,M)(1-a)(1-b)+P(N+1,M)(a)(1-b)+p(N,M+1)(1-a)(b)+P(N+1,M+1)(a)(b)

    nAbsX1_X2 = abs(x1-x2);
	nAbsY1_Y2 = abs(y1-y2);

	// 라인의 길이 
    fLineLength=(double)sqrt((double)(x1-x2)*(double)(x1-x2)+(double)(y1-y2)*(double)(y1-y2));
	if(fLineLength<2) return -1;

	if(nAbsX1_X2>0 && nAbsY1_Y2>0)
    {
		if(nAbsX1_X2 >= nAbsY1_Y2)  // 선이 x축으로 누운경우 
        {
            t=(double)nAbsX1_X2/fLineLength;
			if(x1>x2) t*=-1;
			slope = (double)(y1-y2)/(double)(x1-x2);
            for(i=0;i<=(int)fLineLength;i++)
            {
				pX[i]=(double)(x1+i*t);
				pY[i]=slope*(pX[i]-x1)+y1;  //직선의 방정식으로 부터 각 좌표를 구한다. 
            }
		}	
		else                     // 선이 y축으로 누운경우 
        {
            t=(double)nAbsY1_Y2/fLineLength;
			if(y1>y2) t*=-1;
			slope = (double)(x1-x2)/(double)(y1-y2);
            for(i=0;i<=(int)fLineLength;i++)
            {
				pY[i]=(double)(y1+i*t);
				pX[i]=slope*(pY[i]-y1)+x1; //직선의 방정식으로 부터 각 좌표를 구한다.
            }           
        }

        // 각 좌표에서의 픽셀값을 구한다.
		for(i=0;i<=(int)fLineLength;i++)
        {
			N=(int)pX[i];
			M=(int)pY[i];
			if(N>638 || M<=0 || M>478) break;
			a=pX[i]-N;
			b=pY[i]-M;
			pGrayValue[i]=(int)(*(fm+M*nPitch+N)*(1.0-a)*(1.0-b)+*(fm+M*nPitch+N+1)*(a)*(1.0-b)+
								*(fm+(M+1)*nPitch+N)*(1.0-a)*(b)+*(fm+(M+1)*nPitch+N+1)*(a)*(b));
			nCount++;
        }

    }
	else if(nAbsY1_Y2==0)
	{
		if(x1>x2) t=-1.0;
        for(i=0;i<=(int)fLineLength;i++)
        {
			pX[i]=(double)(x1+i*t);
			pY[i]=(double)y1;  
			pGrayValue[i]=(int)*(fm+nPitch*y1+(int)pX[i]);
			nCount++;
        }
	}
	else if(nAbsX1_X2==0)
	{
		if(y1>y2) t=-1.0;
        for(i=0;i<=(int)fLineLength;i++)
        {
			pY[i]=(double)(y1+i*t);
			pX[i]=(double) x1; 
			pGrayValue[i]=(int)*(fm+nPitch*(int)pY[i]+x1);
			nCount++;
        }
	}

    return (nCount);
}

//Line Fitting
//ty=ax+b
//dataN : 주어진 (x,y)수
//*x, *y; (x,y)좌표 
//removeN : LineFitting후 Line에서 가장 멀리있는 점을 없애고 다시 fitting울 반복한다.
//          이 반복횟수를 나타낸다.
//ErrorLimit: LineFitting후 Line에서 가장 멀리있는 점이 이값 이하이면 반복을 중지한다.
//결과값 return: 1: 정상수행
//				 <0 : FAILURE
//              *t, *a, *b (ty=ax+b)

int LineFitting(int dataN, double *x, double *y, int removeN, double ErrorLimit,
				 double *t, double *a, double *b)
{
	int k,i,j;
	int nCount, MaxPos,*nValid;  
	double xvalue,yvalue;
	double Sxx, Sx, Sy,Sxy, SxSy, dd, MaxDist=0,dist;
	double ZeroData=0.00001;
	if(dataN<2) return -1;

	if(removeN>(dataN-2)) removeN=(dataN-2);

	nValid=(int*)malloc(dataN*sizeof(int));
	if(nValid==0) return -1;

	for(i=0;i<dataN;i++) nValid[i]=0;

	for(k=0;k<removeN+1;k++)
	{
		if(k==0)
		{
			Sx=Sy=Sxx=Sxy=SxSy=0.0;
			for(i=0;i<dataN;i++)
			{
				xvalue=*(x+i);
				yvalue=*(y+i);
				Sx+=xvalue;
				Sy+=yvalue;
				Sxx+=xvalue*xvalue;
				Sxy+=xvalue*yvalue;
			}
		}
		else
		{
			xvalue=*(x+MaxPos);
			yvalue=*(y+MaxPos);
			Sx-=xvalue;
			Sy-=yvalue;
			Sxx-=xvalue*xvalue;
			Sxy-=xvalue*yvalue;		
		}

		nCount=dataN-k;
		SxSy=Sx*Sy;

		dd=nCount*Sxx-Sx*Sx;
		if(fabs(dd)<ZeroData)
		{
			*t=0;
			*a=1;
			*b=-Sx/nCount;
			goto done;
		}
		else
		{
			*t=1;
			*a=(nCount*Sxy-Sx*Sy)/dd;
			*b=(-Sxy*Sx+Sy*Sxx)/dd;
		}

		dd=sqrt(*a**a+1);
		MaxDist=0;
		for(j=0;j<dataN;j++)
		{
			if(nValid[j]) continue;
			dist=fabs(-*(y+j)+*a**(x+j)+*b);
			if(dist>MaxDist)
			{
				MaxDist=dist;
				MaxPos=j;
			}
		}
		if(MaxDist/dd<ErrorLimit) goto done;
		else nValid[MaxPos]=1;
	}
done:
	if(nValid) free(nValid);
	return 1;
}


//1st Line Fitting(Line이 거의 수직일때)
// return 1: SUCCESS
//        -1: FAILURE
int LineFitting1(int dataN, double *x, double *y, int removeN, double ErrorLimit,
				 double *t, double *a, double *b)
{
	int returnValue;
	double la,lb,lt;

	returnValue=LineFitting(dataN,y, x, removeN, ErrorLimit, &lt,&la,&lb);

	if(returnValue==1)
	{
		if(fabs(la)<0.0001)  //기울기가 10000이상은 y축에 평행한것으로 간주한다.
		{
			*t=0;
			*a=lt;
			*b=-lb;
		}
		else
		{
			*t=1;
			*a=lt/la;
			*b=-lb/la;
		}	
		return 1;
	}
	else return returnValue;
}

// 두개의 직선으로부터 Cross하는 점 구하기
//t1y=a1x+b1
//t2y=a2x+b2
//return 1: SUCCESS
//       -1: FAILURE
int FindCrossPoint(double t1, double a1, double b1,
	  			   double t2, double a2, double b2, double *cx, double *cy)
{
	double local_LIMIT=1e-10;;
	

	if(fabs(t1-1)<local_LIMIT && fabs(t2-1) <local_LIMIT)
	{
		if(fabs(a1-a2) < local_LIMIT)
			return -1;
		*cx=(b2-b1)/(a1-a2);
		*cy=a1*(*cx)+b1;
	}
	else if(fabs(t1)<local_LIMIT && fabs(t2-1) <local_LIMIT)
	{
		if(fabs(a1) < local_LIMIT)
			return -1;
		*cx=-b1/a1;
		*cy=a2*(*cx)+b2;
	}
	else if(fabs(t1-1)<local_LIMIT && fabs(t2)<local_LIMIT)
	{
		if(fabs(a2) < local_LIMIT)
			return -1;
		*cx=-b2/a2;
		*cy=a1*(*cx)+b1;
	}
	else
		return -1;

	return 1;
}