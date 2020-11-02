// Vision.cpp: implementation of the CVision class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VisWeb.h"

#include "VisWebDoc.h"
#include "VisWebView.h"

#include "Vision.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVision::CVision(CWnd* pwnd)
{
	m_pParent = pwnd;
	for(int i=0;i<MAX_CAMERAS;i++){
		m_nBufIndexGrabStt[i]=0;
		m_nBufIndexGrabEnd[i]=0;
		m_nBufIndexCopy[i]   =0;

	}
//	m_pLogProcess = new CLogData(PATH_LOG_GRABPROCESS);
//	m_pLogProcess->SetLogWriteEnable(FALSE);
	m_nCrossCount =0;
	m_nFrameCount = -3;
}

CVision::~CVision()
{
//	delete m_pLogProcess;
/*
	MdispFree(MilDisplay);
	for(int i=0; i<MAX_BUFFER; i++)
		MbufFree(MilBuffer[i]);
	MbufFree(MilSaveBuf);
	MbufFree(MilImage);
	MbufFree(MilClipImage);
	MbufFree(MilDisplay);
	MdigFree(MilDigitizer);
	
	MsysFree(MilSystem);
	MappFree(MilApplication);
	*/
	Close();
}

BOOL CVision::Open(HWND hWnd,int nCam,int nWidth,int nHeight)
{
	BOOL bRet=TRUE;
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc *pDoc = (CVisWebDoc*)pView->GetDocument();

	// 188Line -> 133Line
	MappAlloc(M_DEFAULT, &MilApplication);
	CString strdcf;

	for(int i=0;i<MAX_CAMERAS;i++){
		if(i==0)strdcf = DCF_FILE;
		else if(i==1)strdcf = DCF_FILE1;
		else if(i==2)strdcf = DCF_FILE2;
		else strdcf = DCF_FILE;
		MsysAlloc(M_SYSTEM_SOLIOS,  i, M_DEFAULT, &MilSystem[i]);	
		if(i==0){
			if(M_NULL == MdigAlloc(MilSystem[i], M_DEV0, strdcf, M_DEFAULT, &MilDigitizer[i])){
				pView->SetWarning("카메라 설정에 실패 했습니다.");
				pView->m_bConnectCam = FALSE;
				bRet = FALSE;
				m_nSizeX = nWidth;
				m_nSizeY = nHeight;
				m_nBand = 8;
				return bRet;
			}
		}
		else{
			if(M_NULL == MdigAlloc(MilSystem[i], M_DEV0, strdcf, M_DEFAULT, &MilDigitizer[i])){
				pView->SetWarning("카메라 설정에 실패 했습니다.");
				pView->m_bConnectCam = FALSE;
				bRet = FALSE;
				m_nSizeX = nWidth;
				m_nSizeY = nHeight;
				m_nBand = 8;
				return bRet;
			}
		}

		MdigControl(MilDigitizer[i], M_GRAB_TIMEOUT, M_INFINITE);
		// CC1 Output를 정의해 주지 않으면, CC출력이 되지 않음. 반드시 추가해 주어야 함.
		MdigControl(MilDigitizer[i], M_CAMERALINK_CC1_SOURCE, M_GRAB_EXPOSURE+M_TIMER1);
		MdigControl(MilDigitizer[i], M_GRAB_MODE, M_ASYNCHRONOUS);
		m_nSizeX = nWidth;
		m_nSizeY = nHeight;
		m_nBand = 8;
		m_nBand =MdigInquire(MilDigitizer[i], M_SIZE_BAND, M_NULL);
		m_nSizeX = MdigInquire(MilDigitizer[i], M_SIZE_X, M_NULL);
		m_nSizeY = MdigInquire(MilDigitizer[i], M_SIZE_Y, M_NULL);
		int nPC = pDoc->m_data.GetVisionLine(i);
		if(nPC != GL1)
		{		
			for(int j=0; j<MAX_BUFFER; j++)
			{
				MbufAlloc2d(MilSystem[i], m_nSizeX, m_nSizeY, 8+M_UNSIGNED, M_IMAGE+M_GRAB+M_DISP, &MilBuffer[i][j]); //!!
				MbufClear(MilBuffer[i][j], 0xff);
			}
			MbufAlloc2d(MilSystem[i], m_nSizeX, m_nSizeY, 8+M_UNSIGNED, M_IMAGE+M_DISP, &MilImage[i]);
		}
		MbufClear(MilImage[i], 0);
//		MdispAlloc(MilSystem[i], M_DEV0, "M_DEFAULT", M_WINDOWED, &MilDisplay);	

		MappControl(M_ERROR , M_PRINT_DISABLE);
	}

//	MdigInquire(MilDigitizer, M_SIZE_BAND, &m_nBand);
//	MdigInquire(MilDigitizer, M_SIZE_X, &m_nSizeX);
//	MdigInquire(MilDigitizer, M_SIZE_Y, &m_nSizeY);

	
  	return bRet;
}

/*
long MFTYPE GrabStart(long HookType, MIL_ID EventId, void *DataStruct)
{
	CVisWebView *pView = (CVisWebView*)DataStruct;
	CVision		*pVision = pView->GetDocument()->m_pVision;

	pVision->m_nBufIndexGrabStt++;

	pVision->SingleGrab(pVision->m_nBufIndexGrabStt%MAX_BUFFER) ;
	return 0;
}

long MFTYPE GrabEnd(long HookType, MIL_ID EventId, void *DataStruct)
{
	CVisWebView *pView = (CVisWebView*)DataStruct;
	CVisWebDoc *pDoc = (CVisWebDoc*)pView->GetDocument();

	CVision		*pVision = pView->GetDocument()->m_pVision;
	
	if(!pView->m_bAuto)		//Auto 모드가 아니면 촬상을 끝낸다
	{
		pVision->m_nBufIndexGrabStt = 0;
		pVision->m_nBufIndexGrabEnd = 0;
		pVision->m_nBufIndexCopy	= 0;
		return 0;
	}

	pVision->m_nBufIndexGrabEnd++;
	pView->CopyMilImg();	// 이거 수정

	return 0;
}
*/
unsigned char* CVision::GetImgPtr(int nCam,int nIndex)
{
	unsigned char * pImage;
	pImage = (unsigned char*)MbufInquire(MilBuffer[nCam][nIndex], M_HOST_ADDRESS, M_NULL);
	return pImage;
}


//void  CVision::ImageClip(int index)
//{
////	MbufCopyClip(MilBuffer[m_nBufIndexCopy%MAX_BUFFER],MilClipImage,0,256*index);
//}


//unsigned char* CVision::GetOriImgPtr(int nCam,int nFrameNo)
//{
//	unsigned char * pImage=NULL;
//
//	return pImage;
//}
void CVision::HookStart()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;

/*	MdigHookFunction(MilDigitizer, M_GRAB_START, GrabStart,(void*)m_pParent);
	MdigHookFunction(MilDigitizer, M_GRAB_END, GrabEnd,(void*)m_pParent);

	SingleGrab(m_nBufIndexGrabStt);	
	*///

//	MdigProcess(MilDigitizer, MilGrabBufferList, MilGrabBufferListSize,
//	M_START, M_DEFAULT, ProcessingFunction, this);
//	MdigGrab(MilDigitizer, MilBuffer[nBufferNum]);

	for(int i=0;i<MAX_CAMERAS;i++)
		if(i==0)
			MdigProcess(MilDigitizer[i], MilBuffer[i], MAX_BUFFER,M_START, M_DEFAULT, ProcessingFunction, (void*)m_pParent);
		else if(i==1)
			MdigProcess(MilDigitizer[i], MilBuffer[i], MAX_BUFFER,M_START, M_DEFAULT, ProcessingFunction1, (void*)m_pParent);
		else 
			MdigProcess(MilDigitizer[i], MilBuffer[i], MAX_BUFFER,M_START, M_DEFAULT, ProcessingFunction2, (void*)m_pParent);
}

void CVision::HookStop()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;

/*	MdigHookFunction(MilDigitizer, M_GRAB_START+M_UNHOOK, GrabStart,(void*)m_pParent);	
	MdigHookFunction(MilDigitizer, M_GRAB_END+M_UNHOOK, GrabEnd,(void*)m_pParent);	
	MdigControl(MilDigitizer, M_GRAB_ABORT, M_DEFAULT);
	MdigProcess(MilDigitizer, MilGrabBufferList, MilGrabBufferListSize,
		M_STOP, M_DEFAULT, ProcessingFunction, this);
*/

	for(int i=0;i<MAX_CAMERAS;i++){
		if(i==0)
			MdigProcess(MilDigitizer[i], MilBuffer[i], MAX_BUFFER,M_STOP, M_DEFAULT, ProcessingFunction, (void*)m_pParent);
		else if(i==1)
			MdigProcess(MilDigitizer[i], MilBuffer[i], MAX_BUFFER,M_STOP, M_DEFAULT, ProcessingFunction1, (void*)m_pParent);
		else 
			MdigProcess(MilDigitizer[i], MilBuffer[i], MAX_BUFFER,M_STOP, M_DEFAULT, ProcessingFunction2, (void*)m_pParent);
		m_nBufIndexGrabStt[i]=0;
		m_nBufIndexGrabEnd[i]=0;
		m_nBufIndexCopy[i]   =0;
		
	}
}

void CVision::HookStop(int n)
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	if(n==1)
	{
		MdigControl(MilDigitizer[n], M_GRAB_ABORT, M_DEFAULT);
	}

	m_nBufIndexGrabStt[n]=0;
	m_nBufIndexGrabEnd[n]=0;
	m_nBufIndexCopy[n]   =0;
}

void CVision::SetLiveMode()
{

 }

void CVision::SetTrigMode()
{
}

void CVision::InitOriImage()
{

}

void CVision::MakeImg()
{//Copy MIL Image -> CImage

}
unsigned char* CVision::GetProcessBuf(int nCam)
{
	unsigned char* fm;
	fm = GetImgPtr(nCam, m_nBufIndexCopy[nCam]%MAX_BUFFER);
	m_nBufIndexCopy[nCam]++;
	return fm;
}
	
void CVision::ChangeVerticalLine(int Line)
{
	//m_nSizeY = Line;

	//int i;

	//for(i=0; i<MAX_BUFFER; i++)
	//	MbufFree(MilBuffer[i]);

	//MbufFree(MilImage);

	//for(i=0; i<MAX_BUFFER; i++)
	//{
	//	MbufAlloc2d(MilSystem, m_nSizeX, m_nSizeY, 8+M_UNSIGNED, M_IMAGE+M_GRAB+M_DISP, &MilBuffer[i]); //!!
	//	MbufClear(MilBuffer[i], 0);
	//}
	//
	//MbufAlloc2d(MilSystem, m_nSizeX, m_nSizeY, 8+M_UNSIGNED, M_IMAGE+M_DISP, &MilImage);
	//
	//MbufClear(MilImage, 0);

	//MdigControl(MilDigitizer,M_SOURCE_SIZE_Y ,m_nSizeY);
}
extern int g_frame_num;
void CVision::SingleGrab(int nBufferNum)
{
/*	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc *pDoc = (CVisWebDoc*)pView->GetDocument();
	m_nCrossCount++;
	pView->m_nMilGrabCount++;
	if(pDoc->m_data.GetVisionLine(nCam) == NEL1 && m_nCrossCount == CROSSIMGCOUNT)// && atoi(pDoc->m_data.m_strComName.Right(2)) <7)
	{
		g_frame_num++;
		m_nCrossCount =0;
		m_nFrameCount++;
	}
	else if(pDoc->m_data.GetVisionLine(nCam) != NEL1){
		g_frame_num++;
		m_nCrossCount =0;
		m_nFrameCount++;
	}
	MdigGrab(MilDigitizer, MilBuffer[nBufferNum]);
	*/
}
// void CVision::SaveImg(CString strpath)
// {
// 	//char filename[200];
// 	//sprintf(filename, "%s",strpath);
// 	//MbufCopy(MilBuffer[(m_nBufIndexGrabStt-1)%MAX_BUFFER] ,MilSaveBuf);
// 	//MbufExport(filename,M_BMP,MilSaveBuf);
// }


void CVision::SetExposureTime(int nCam,int nNanoSec,int flow)
{
	static int nOldShutter = 0;
	if(nOldShutter != nNanoSec || flow == 1)
	{
		MdigControl(MilDigitizer[nCam], M_GRAB_EXPOSURE_TIME, nNanoSec);
//		MdigControl(MilDigitizer[nCam], M_GRAB_EXPOSURE_TIME_DELAY, nNanoSec);
	}//
	nOldShutter = nNanoSec;
}

void CVision::GetExposureTime(double *pNanoSec)
{
//	MdigInquire(MilDigitizer, M_GRAB_EXPOSURE_TIME, pNanoSec);
}

///////////////////////////////////////////////////////////////////////////////////
unsigned short* CVision::GetProcessBufShort()
{
	unsigned short* fm;
// 	fm = GetImgPtrShort(m_nBufIndexCopy%MAX_BUFFER);
// 	m_nBufIndexCopy++;
//	MbufClear(MilBuffer[(m_nBufIndexCopy)%MAX_BUFFER], 0xff);
	return fm;
}

unsigned short* CVision::GetImgPtrShort(int nIndex)
{
	unsigned short * pImage;
//	pImage = (unsigned short*)MbufInquire(MilBuffer[nIndex], M_HOST_ADDRESS, M_NULL);
	return pImage;
}
///////////////////////////////////////////////////////////////////////////////////

void CVision::Close()
{

//	MdispFree(MilDisplay);
// 	for(int i=0;i<MAX_CAMERAS;i++){
// 		for(int j=0; j<MAX_BUFFER; j++)
// 			MbufFree(MilBuffer[i][j]);
// 		MbufFree(MilImage[i]);
// 	//	MbufFree(MilDisplay);
// 		MdigFree(MilDigitizer[i]);
// 		
// 		MsysFree(MilSystem[i]);
// 	}
// 	MappFree(MilApplication);

}

//long MFTYPE ProcessingFunction(long HookType, MIL_ID HookId, void MPTYPE *HookDataPtr)
MIL_INT MFTYPE ProcessingFunction(MIL_INT HookType, MIL_ID HookId, void* HookDataPtr)
{
	CVisWebView *pView = (CVisWebView*)HookDataPtr;
	CVisWebDoc *pDoc = (CVisWebDoc*)pView->GetDocument();

	CVision		*pVision = pView->GetDocument()->m_pVision;


//	CMdigProcess2Dlg *UserHookDataPtr = (CMdigProcess2Dlg *)HookDataPtr;
//	MIL_ID ModifiedBufferId;
//	MIL_TEXT_CHAR Text[STRING_LENGTH_MAX]= {'\0',};
	
	/* Retrieve the MIL_ID of the grabbed buffer. */
	MdigGetHookInfo(HookId, M_MODIFIED_BUFFER+M_BUFFER_ID, &pVision->MilBuffer[0][pVision->m_nBufIndexGrabStt[0]%MAX_BUFFER]);//MilImage);
	
	/* Print and draw the frame count. */
//	UserHookDataPtr->ProcessedImageCount++;
	pView->CopyMilImg(0);	// 이거 수정

	pVision->m_nBufIndexGrabStt[0]++;
	/*CString str;
	str.Format("%d", g_frame_num);
	pView->WriteLog("c:\\glim\\log", "frame_debug", str);
	pView->WriteLog("c:\\glim\\log", "frame_debug", "frame1");*/
	g_frame_num++;
	//str.Format("%d", g_frame_num);
	//pView->WriteLog("c:\\glim\\log", "frame_debug", str);

	/* Perform the processing and update the display. */
//	MbufCopy(ModifiedBufferId, UserHookDataPtr->MilImageDisp);
	
	return 0;
}

MIL_INT MFTYPE ProcessingFunction1(MIL_INT HookType, MIL_ID HookId, void* HookDataPtr)
{
	CVisWebView *pView = (CVisWebView*)HookDataPtr;
	CVisWebDoc *pDoc = (CVisWebDoc*)pView->GetDocument();

	CVision		*pVision = pView->GetDocument()->m_pVision;


//	CMdigProcess2Dlg *UserHookDataPtr = (CMdigProcess2Dlg *)HookDataPtr;
//	MIL_ID ModifiedBufferId;
//	MIL_TEXT_CHAR Text[STRING_LENGTH_MAX]= {'\0',};
	
	/* Retrieve the MIL_ID of the grabbed buffer. */
	MdigGetHookInfo(HookId, M_MODIFIED_BUFFER+M_BUFFER_ID, &pVision->MilBuffer[1][pVision->m_nBufIndexGrabStt[1]%MAX_BUFFER]);//MilImage);
	
	/* Print and draw the frame count. */
//	UserHookDataPtr->ProcessedImageCount++;
	pView->CopyMilImg(1);	// 이거 수정

	pVision->m_nBufIndexGrabStt[1]++;
	/*CString str;
	str.Format("%d", g_frame_num);
	pView->WriteLog("c:\\glim\\log", "frame_debug", str);
	pView->WriteLog("c:\\glim\\log", "frame_debug", "frame1");*/
//	g_frame_num++;
	//str.Format("%d", g_frame_num);
	//pView->WriteLog("c:\\glim\\log", "frame_debug", str);

	/* Perform the processing and update the display. */
//	MbufCopy(ModifiedBufferId, UserHookDataPtr->MilImageDisp);
	
	return 0;
}


MIL_INT MFTYPE ProcessingFunction2(MIL_INT HookType, MIL_ID HookId, void* HookDataPtr)
{
	CVisWebView *pView = (CVisWebView*)HookDataPtr;
	CVisWebDoc *pDoc = (CVisWebDoc*)pView->GetDocument();

	CVision		*pVision = pView->GetDocument()->m_pVision;


//	CMdigProcess2Dlg *UserHookDataPtr = (CMdigProcess2Dlg *)HookDataPtr;
//	MIL_ID ModifiedBufferId;
//	MIL_TEXT_CHAR Text[STRING_LENGTH_MAX]= {'\0',};
	
	/* Retrieve the MIL_ID of the grabbed buffer. */
	MdigGetHookInfo(HookId, M_MODIFIED_BUFFER+M_BUFFER_ID, &pVision->MilBuffer[2][pVision->m_nBufIndexGrabStt[2]%MAX_BUFFER]);//MilImage);
	
	/* Print and draw the frame count. */
//	UserHookDataPtr->ProcessedImageCount++;
	pView->CopyMilImg(2);	// 이거 수정

	pVision->m_nBufIndexGrabStt[2]++;
	/*CString str;
	str.Format("%d", g_frame_num);
	pView->WriteLog("c:\\glim\\log", "frame_debug", str);
	pView->WriteLog("c:\\glim\\log", "frame_debug", "frame1");*/
//	g_frame_num++;
	//str.Format("%d", g_frame_num);
	//pView->WriteLog("c:\\glim\\log", "frame_debug", str);

	/* Perform the processing and update the display. */
//	MbufCopy(ModifiedBufferId, UserHookDataPtr->MilImageDisp);
	
	return 0;
}

BOOL CVision::Open1(int nWidth,int nHeight)
{
	BOOL bRet = TRUE;
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc *pDoc = (CVisWebDoc*)pView->GetDocument();

	//delete
	for(int i=0;i<MAX_CAMERAS ;i++){
		for(int j=0; j<MAX_BUFFER; j++)
			MbufFree(MilBuffer[i][j]);
		//	MbufFree(MilDisplay);
		MdigFree(MilDigitizer[i]);

		MsysFree(MilSystem[i]);
	}
	MappFree(MilApplication);


	MappAlloc(M_DEFAULT, &MilApplication);
	CString strdcf;
	for(int i=0;i<MAX_CAMERAS ;i++){
		if(i==0)strdcf = DCF_FILE;
		else if(i==1)strdcf = DCF_FILE1;
		else if(i==2)strdcf = DCF_FILE2;
		else strdcf = DCF_FILE;
		MsysAlloc(M_SYSTEM_SOLIOS,  i, M_DEFAULT, &MilSystem[i]);	
		if(M_NULL == MdigAlloc(MilSystem[i], M_DEV0, strdcf, M_DEFAULT, &MilDigitizer[i]))
		{
			pView->SetWarning("카메라 설정에 실패 했습니다.");
			pView->m_bConnectCam = FALSE;
			bRet = FALSE;
			m_nSizeX = nWidth;
			m_nSizeY = nHeight;
			m_nBand = 8;
			return bRet;
		}


		MdigControl(MilDigitizer[i], M_GRAB_TIMEOUT, M_INFINITE);
		// CC1 Output를 정의해 주지 않으면, CC출력이 되지 않음. 반드시 추가해 주어야 함.
		MdigControl(MilDigitizer[i], M_CAMERALINK_CC1_SOURCE, M_GRAB_EXPOSURE+M_TIMER1);
		MdigControl(MilDigitizer[i], M_GRAB_MODE, M_ASYNCHRONOUS);
		m_nSizeX = nWidth;
		m_nSizeY = nHeight;
		m_nBand = 8;
		m_nBand = MdigInquire(MilDigitizer[i], M_SIZE_BAND, M_NULL);
		m_nSizeX = MdigInquire(MilDigitizer[i], M_SIZE_X, M_NULL);
		m_nSizeY = MdigInquire(MilDigitizer[i], M_SIZE_Y, M_NULL);

		for(int j=0; j<MAX_BUFFER; j++)
		{
			MbufAlloc2d(MilSystem[i], m_nSizeX, m_nSizeY, 8+M_UNSIGNED, M_IMAGE+M_GRAB+M_DISP, &MilBuffer[i][j]); //!!
			MbufClear(MilBuffer[i][j], 0xff);
		}
	}


	return bRet;
}



