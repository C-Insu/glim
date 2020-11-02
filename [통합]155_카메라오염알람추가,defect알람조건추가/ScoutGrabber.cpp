///*
//#include "stdafx.h"
//#include "VisWeb.h"
//
//#include "VisWebDoc.h"
//#include "VisWebView.h"
//#include "TimingProcess.h"
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <conio.h>
///*
//#pragma comment(lib, "PylonGenericInterface.lib")
//#pragma comment(lib, "PylonGenericInterfaced.lib")
//
//*/
///*
//#ifdef PYLON_2_2
//		PYLON_DEVICE_HANDLE		hCam[MAX_CAM];								// Camera handle	//2.2
//
//		/////////////////////////////코팅용.
//		//PYLONBUFFERHANDLE	hBuffer[MAX_CAM][NUM_BUFFERS];				// Buffer handles (one for each)//2.0
//		PYLON_STREAMBUFFER_HANDLE	hBuffer[MAX_CAM][NUM_BUFFERS];				// Buffer handles (one for each)//2.2
//
//		////////////////////////////연신용.
//		//PYLONBUFFERHANDLE	hESBuffer[MAX_CAM][ESNUM_BUFFERS];				// Buffer handles (one for each)
//		//unsigned char ESImageBuffer[MAX_CAM][ESNUM_BUFFERS][WIDTH*ESHEIGHT];	// 부분 촬상에 사용되는 메모리
//		///////////////////////////////2.2
//		PYLON_WAITOBJECT_HANDLE     hWait;                      /* Handle used for waiting for a grab to be finished. */
//		_Bool                        isAvail;                    /* Used for checking feature availability. */
//		_Bool                        isReady;                    /* Used as an output parameter. */
//			GENAPIC_RESULT              res;                        /* Return value of pylon methods. */ 
//		size_t                      numDevices;                 /* Number of available devices. */
//		PYLON_DEVICE_HANDLE         hDev;                       /* Handle for the pylon device. */
//		PYLON_STREAMGRABBER_HANDLE  hGrabber;                   /* Handle for the pylon stream grabber. */
//		int32_t                     payloadSize;                /* Size of an image frame in bytes. */
//		PylonGrabResult_t           grabResult;                 /* Stores the result of a grab operation. */ 
//		int                         nGrabs;                     /* Counts the number of buffers grabbed. */
//		size_t                      nStreams;                   /* The number of streams the device provides. */
//#else
//		PYLONCAMHANDLE		hCam[MAX_CAM];								// Camera handle
//		PYLONBUFFERHANDLE	hBuffer[MAX_CAM][NUM_BUFFERS];				// Buffer handles (one for each)
//
//#endif
//
//unsigned char ImageBuffer[MAX_CAM][NUM_BUFFERS][WIDTH*HEIGHT];	// 부분 촬상에 사용되는 메모리
//BYTE gBuffer1[MAX_FULL_BUF][WIDTH*HEIGHT*NUM_BUFFERS];			// 부분 촬상한 영상을 모으는 메모리 
//BYTE gBufferTemp[WIDTH*HEIGHT*NUM_BUFFERS];			// 부분 촬상한 영상을 모으는 메모리 
//
//TEMPDATA g_Temp;
//
//
//CVision1::CVision1(CWnd* pwnd)
//{
//	m_pParent = pwnd;
//	m_nSizeX=WIDTH;
//	m_nSizeY=NUM_BUFFERS*HEIGHT;
//}
//
//CVision1::~CVision1()
//{
//	g_Temp.m_GRAB1RUN=false;
//	g_Temp.m_GRAB1RUNSUB=false;
//	g_Temp.m_GRABControlRUN=false;
//
//	Sleep(100);
//	Close();
//}
//bool CVision1::GetAreaCameraSerialNumber(CString str)
//{
//	CString section, filepath;
//	CString sItem;
//	char	cReturn[80];
//	char    sFullName[80], sComLine[2], sComNumber[3];
//	int     nComLine, nComNumber;
//
//	filepath.Format("%s",CAMERA_SERIAL_PATH);
//
//	strcpy(sFullName,(char*)(LPCTSTR)str);
//
//	sComLine[0]=sFullName[4];
//	sComLine[1]=NULL;
//
//	sComNumber[0]=sFullName[5];
//	sComNumber[1]=sFullName[6];
//	sComNumber[2]=NULL;
//
//	nComLine=atoi(sComLine);
//	nComNumber=atoi(sComNumber);
//
//	if(nComLine==7)
//		sItem.Format("A1%02d",nComNumber*2-1);
//	else
//		sItem.Format("A2%02d",nComNumber*2-1);
//
//	if(::GetPrivateProfileString("AREA",sItem,_T("00000000"),cReturn,60,filepath) > 0)
//	{
//		strcpy(sCameraSerial[0],cReturn);
//	}
//
//	if(nComLine==7)
//		sItem.Format("A1%02d",nComNumber*2);
//	else
//		sItem.Format("A2%02d",nComNumber*2);
//
//	if(::GetPrivateProfileString("AREA",sItem,_T("00000000"),cReturn,60,filepath) > 0)
//	{
//		strcpy(sCameraSerial[1],cReturn);
//	}
//
//	if(atoi(sCameraSerial[0])>0 && atoi(sCameraSerial[1])>0) return true;
//	else													 return false;
//}
//
////Slit 티칭 데이타 읽어오는 함수 
//int CVision1::LoadSlitData(CString str)
//{
//	CString section, filepath;
//	CString sComName;
//	char	cReturn[80];
//
//	//좌우 끝단 설정 -------------------------------------------------------
//	if(str.Find("701")>=0 || str.Find("801")>=0)		g_nLeftRightCut=1;
//	else if(str.Find("724")>=0 || str.Find("824")>=0)	g_nLeftRightCut=2;
//	else												g_nLeftRightCut=0;
//	//----------------------------------------------------------------------
//
//	if(str.Find("NEL-7",0)>=0)
//		sComName.Format("NEL-7");
//	else if(str.Find("NEL-8",0)>=0)
//		sComName.Format("NEL-8");
//
//	filepath.Format(CAMERA_TEACHDATA_PATH);
//
//	g_Teach.nOneFrameGrabCount		=NUM_BUFFERS;
//	g_Teach.dOneFrameLength			=100;       //100mm
//	g_Teach.nMaxMinRange			=20;		//최대 밝기-최소 밝기를 구하는 영역 
//	g_Teach.nSkip					=2;			//FIXED 
//
//	if(::GetPrivateProfileString(sComName,"USE_SLITInspection",_T("Y"),cReturn,60,filepath) > 0)
//	{
//		if(cReturn[0]=='y'||cReturn[0]=='Y')	g_Teach.bSlitInspection=true;
//		else									g_Teach.bSlitInspection=false;
//	}
//
//	if(::GetPrivateProfileString(sComName,"MinBlackLine",_T("10"),cReturn,60,filepath) > 0)
//	{
//		g_Teach.nMinEdgeCount=atoi(cReturn)*2;
//	}
//	if(::GetPrivateProfileString(sComName,"YEdgeSlope",_T("30"),cReturn,60,filepath) > 0)
//	{
//		g_Teach.nMinDepth=atoi(cReturn);
//	}
//
//	if(::GetPrivateProfileString(sComName,"USE_BlackLineThickness",_T("Y"),cReturn,60,filepath) > 0)
//	{
//		if(cReturn[0]=='y'||cReturn[0]=='Y')	g_Teach.bBlackThickness=true;
//		else									g_Teach.bBlackThickness=false;
//	}
//	if(::GetPrivateProfileString(sComName,"_MinBlackLineThickness",_T("1"),cReturn,60,filepath) > 0)
//	{
//		g_Teach.dBlackMin=atof(cReturn);     
//	}
//	if(::GetPrivateProfileString(sComName,"_MaxBlackLineThickness",_T("10"),cReturn,60,filepath) > 0)
//	{
//		g_Teach.dBlackMax=atof(cReturn);     
//	}
//
//	if(::GetPrivateProfileString(sComName,"USE_WhiteLineThickness",_T("Y"),cReturn,60,filepath) > 0)
//	{
//		if(cReturn[0]=='y'||cReturn[0]=='Y') g_Teach.bWhiteThickness=true;
//		else							   g_Teach.bWhiteThickness=false;
//	}
//	if(::GetPrivateProfileString(sComName,"_MinWhiteLineThickness",_T("1"),cReturn,60,filepath) > 0)
//	{
//		g_Teach.dWhiteMin=atof(cReturn);     
//	}
//	if(::GetPrivateProfileString(sComName,"_MaxWhiteLineThickness",_T("10"),cReturn,60,filepath) > 0)
//	{
//		g_Teach.dWhiteMax=atof(cReturn);     
//	}
//
//
//	if(::GetPrivateProfileString(sComName,"USE_XEdgeSlope",_T("Y"),cReturn,60,filepath) > 0)
//	{
//		if(cReturn[0]=='y'||cReturn[0]=='Y') g_Teach.bXEdgeSlope=true;
//		else							   g_Teach.bXEdgeSlope=false;
//	}
//	if(::GetPrivateProfileString(sComName,"_MaxXEdgeSlope",_T("1.5"),cReturn,60,filepath) > 0)
//	{
//		g_Teach.dPeekMax=atof(cReturn);     
//	}
//
//
//	//BlackThickness
//	if(::GetPrivateProfileString(sComName,"USE_BlackThicknessLongChange",_T("Y"),cReturn,60,filepath) > 0)
//	{
//		if(cReturn[0]=='y'||cReturn[0]=='Y') g_Teach.bBlackThickLongChange=true;
//		else							   g_Teach.bBlackThickLongChange=false;
//	}
//	if(::GetPrivateProfileString(sComName,"_MaxBlackThicknessLongChange",_T("2"),cReturn,60,filepath) > 0)
//	{
//		g_Teach.dBlackThickMaxMin=atof(cReturn);     
//	}
//	if(::GetPrivateProfileString(sComName,"USE_BlackThicknessShortChange",_T("Y"),cReturn,60,filepath) > 0)
//	{
//		if(cReturn[0]=='y'||cReturn[0]=='Y') g_Teach.bBlackThickShortChange=true;
//		else							   g_Teach.bBlackThickShortChange=false;
//	}
//	if(::GetPrivateProfileString(sComName,"_MaxBlackThicknessShortChange",_T("1.5"),cReturn,60,filepath) > 0)
//	{
//		g_Teach.dBlackThickSlope=atof(cReturn);     
//	}
//
//	//WhiteThickness
//	if(::GetPrivateProfileString(sComName,"USE_WhiteThicknessLongChange",_T("Y"),cReturn,60,filepath) > 0)
//	{
//		if(cReturn[0]=='y'||cReturn[0]=='Y') g_Teach.bWhiteThickLongChange=true;
//		else							   g_Teach.bWhiteThickLongChange=false;
//	}
//	if(::GetPrivateProfileString(sComName,"_MaxWhiteThicknessLongChange",_T("2"),cReturn,60,filepath) > 0)
//	{
//		g_Teach.dWhiteThickMaxMin=atof(cReturn);     
//	}
//	if(::GetPrivateProfileString(sComName,"USE_WhiteThicknessShortChange",_T("Y"),cReturn,60,filepath) > 0)
//	{
//		if(cReturn[0]=='y'||cReturn[0]=='Y') g_Teach.bWhiteThickShortChange=true;
//		else							   g_Teach.bWhiteThickShortChange=false;
//	}
//	if(::GetPrivateProfileString(sComName,"_MaxWhiteThicknessShortChange",_T("1.5"),cReturn,60,filepath) > 0)
//	{
//		g_Teach.dWhiteThickSlope=atof(cReturn);     
//	}
//
//	//BlackGrayValue
//	if(::GetPrivateProfileString(sComName,"USE_BlackGrayValueLongChange",_T("Y"),cReturn,60,filepath) > 0)
//	{
//		if(cReturn[0]=='y'||cReturn[0]=='Y') g_Teach.bBlackValueLongChange=true;
//		else							   g_Teach.bBlackValueLongChange=false;
//	}
//	if(::GetPrivateProfileString(sComName,"_MaxBlackGrayValueLongChange",_T("20"),cReturn,60,filepath) > 0)
//	{
//		g_Teach.nBlackValueMaxMin=atoi(cReturn);     
//	}
//	if(::GetPrivateProfileString(sComName,"USE_BlackGrayValueShortChange",_T("Y"),cReturn,60,filepath) > 0)
//	{
//		if(cReturn[0]=='y'||cReturn[0]=='Y') g_Teach.bBlackValueShortChange=true;
//		else							   g_Teach.bBlackValueShortChange=false;
//	}
//	if(::GetPrivateProfileString(sComName,"_MaxBlackGrayValueShortChange",_T("10"),cReturn,60,filepath) > 0)
//	{
//		g_Teach.nBlackValueSlope=atoi(cReturn);     
//	}
//
//	//WhiteGrayValue
//	if(::GetPrivateProfileString(sComName,"USE_WhiteGrayValueLongChange",_T("Y"),cReturn,60,filepath) > 0)
//	{
//		if(cReturn[0]=='y'||cReturn[0]=='Y') g_Teach.bWhiteValueLongChange=true;
//		else							   g_Teach.bWhiteValueLongChange=false;
//	}
//	if(::GetPrivateProfileString(sComName,"_MaxWhiteGrayValueLongChange",_T("20"),cReturn,60,filepath) > 0)
//	{
//		g_Teach.nWhiteValueMaxMin=atoi(cReturn);     
//	}
//	if(::GetPrivateProfileString(sComName,"USE_WhiteGrayValueShortChange",_T("Y"),cReturn,60,filepath) > 0)
//	{
//		if(cReturn[0]=='y'||cReturn[0]=='Y') g_Teach.bWhiteValueShortChange=true;
//		else							   g_Teach.bWhiteValueShortChange=false;
//	}
//	if(::GetPrivateProfileString(sComName,"_MaxWhiteGrayValueShortChange",_T("10"),cReturn,60,filepath) > 0)
//	{
//		g_Teach.nWhiteValueSlope=atoi(cReturn);     
//	}
//
//	return 0;
//}
//
//
//#ifdef AREA_SLIT
//#ifdef PYLON_2_2
//BOOL CVision1::Open(HWND hWnd)
//{
//	int i,j;
//	BOOL bRet=TRUE;
//	long OffsetX;
//	long OffsetY;
//	long Width;
//	long Height;
//	long MaxWidth;
//	long MaxHeight;
//	long Num;
//	long BufferSize;
//	BOOL bAvail;
//
//
//	CVisWebView *pView = (CVisWebView*)m_pParent;
//	CVisWebDoc *pDoc = (CVisWebDoc*)pView->GetDocument();
//
//	PylonInitialize ();
//
//	///////////////////////////////
//	// Open the camera
//	///////////////////////////////
////	GetAreaCameraSerialNumber(pDoc->m_data.m_strComName);
//
//
//
//	 res = PylonEnumerateDevices( &NumOfCams );	//2.2
//    if ( 0 == NumOfCams )//2.2
//    {
//        /* Before exiting a program, PylonTerminate() should be called to release
//           all pylon related resources. */
//        PylonTerminate();   //2.2
//        exit(EXIT_FAILURE);	//2.2
//    }
//
//
//	for(i=0;i<NumOfCams;i++)
//	{
//	/* Get a handle for the first device found.  */
//		res = PylonCreateDeviceByIndex( 0, &hCam[i] );	//2.2
//    /* Before using the device, it must be opened. Open it for setting
//       parameters and for grabbing images. */
//		res = PylonDeviceOpen( hCam[i], PYLONC_ACCESS_MODE_CONTROL | PYLONC_ACCESS_MODE_STREAM );//2.2
//
//		if(NULL == hCam[i]) continue;
//
//
//		res = PylonDeviceFeatureFromString (hCam[i], "DeviceID", StrBuffer);		//2.2
//		PylonDeviceSetIntegerFeature( hCam[i], "Width", Width );	//2.2
//		PylonDeviceSetIntegerFeature( hCam[i], "Height", Height );	//2.2
//
//		PylonDeviceFeatureFromString( hCam[i], "AcquisitionMode", "Continuous" );//2.2
//
//
//    /* ... Select the software trigger as the trigger source. */
//        PylonDeviceFeatureFromString(hCam[i], "TriggerSelector", "AcquisitionStart");	//2.2
//
//#ifdef TEST_MODE
//		PylonDeviceFeatureFromString(hCam[i], "TriggerMode", "Off");					//2.2
//#else
//        PylonDeviceFeatureFromString(hCam[i], "TriggerMode", "On");					//2.2
//    /* Enable software triggering. */
//    /* ... Select the software trigger as the trigger source. */
//		res = PylonDeviceFeatureFromString( hCam[i], "TriggerSource", "Line1");			//2.2
//		res = PylonDeviceFeatureFromString( hCam[i], "LineSelector", "Line1");			//2.2
//		res = PylonDeviceSetFloatFeature( hCam[i], "LineDebouncerTimeAbs", 100 );		//2.2
//#endif
//        res = PylonDeviceSetIntegerFeature( hCam[0], "GevSCPSPacketSize", 1500 );//9000	//2.2
//	}
//
//
//	for(i=0;i<NumOfCams;i++)
//	{
//
//		res = PylonDeviceGetNumStreamGrabberChannels( hCam[i], &nStreams );	//2.2
//		if ( nStreams < 1 )
//		{
////			TRACE("The transport layer doesn't support image streams.\n");
//			PylonTerminate();
//			exit(EXIT_FAILURE);
//		}
//
//    /* Create and open a stream grabber for the first channel. */ 
//	    res = PylonDeviceGetStreamGrabber( hCam[i], 0, &hGrabber );			//2.2
//	    res = PylonStreamGrabberOpen( hGrabber );							//2.2
//    /* Get a handle for the stream grabber's wait object. The wait object
//       allows waiting for buffers to be filled with grabbed data. */
//	    res = PylonStreamGrabberGetWaitObject( hGrabber, &hWait );			//2.2
//    /* Determine the required size of the grab buffer. Since activating chunks will increase the
//       payload size and thus the required buffer size, do this after enabling the chunks. */
//		res = PylonDeviceGetIntegerFeatureInt32( hCam[i], "PayloadSize", &payloadSize );		//2.2
//    /* We must tell the stream grabber the number and size of the buffers 
//       we are using. */
//    /* .. We will not use more than NUM_BUFFERS for grabbing. */
//		res = PylonStreamGrabberSetMaxNumBuffer( hGrabber, NUM_BUFFERS );	//2.2
//    /* .. We will not use buffers bigger than payloadSize bytes. */
//		res = PylonStreamGrabberSetMaxBufferSize( hGrabber, payloadSize );	//2.2
//    /*  Allocate the resources required for grabbing. After this, critical parameters 
//        that impact the payload size must not be changed until FinishGrab() is called. */
//		res = PylonStreamGrabberPrepareGrab( hGrabber );	//2.2
//
//		for (j=0; j<NUM_BUFFERS; j++)
//		{
//			PylonStreamGrabberRegisterBuffer (hGrabber, ImageBuffer[i][j], payloadSize,  &hBuffer[i][j] );	//2.2
//			res = PylonStreamGrabberQueueBuffer( hGrabber, hBuffer[i][j], (void*) j );						//2.2
//		}
//	}
//
//	return bRet;
//}
//#else
//BOOL CVision1::Open(HWND hWnd)
//{
//	int i,j;
//	BOOL bRet=TRUE;
//	long OffsetX;
//	long OffsetY;
//	long Width;
//	long Height;
//	long MaxWidth;
//	long MaxHeight;
//	long Num;
//	long BufferSize;
//	BOOL bAvail;
//	EPylonAccessMode AccessMode;
//	SCameraInfo CamInfo;
//
//	CVisWebView *pView = (CVisWebView*)m_pParent;
//	CVisWebDoc *pDoc = (CVisWebDoc*)pView->GetDocument();
//
//	PylonInitialize ();
//	// get Number of cameras on the network
//	if (!PylonGetNumCam (&NumOfCams))
//	{
//		strError.Format("Number of cameras available: 0\n");
//#ifdef DEBUG_MODE
//	AfxMessageBox(strError);
//#endif
//		return false;
//	}
//
//#ifdef DEBUG_MODE
//	AfxMessageBox("debug mode");
//		return false;
//#endif
//
//		
/////////////////////////////////
//	// Open the camera
//	///////////////////////////////
////	LoadSlitData(pDoc->m_data.m_strComName);
////	GetAreaCameraSerialNumber(pDoc->m_data.m_strComName);
//
//	int	nCamStats = FALSE;
//	nCamStats = PylonGetSerialNumberByIndex(0,sCameraSerial[0]); 
//	
//	for(i=0;i<NumOfCams;i++)
//	{
//		// Open camera and get handle to Pylon camera object
//		hCam[i] = PylonCamOpenBySerialNumber (sCameraSerial[i]);
////		hCam[0] = PylonCamOpenBySerialNumber ("20817760");
//
//		if (NULL == hCam[i])
//		{
//			// no device found
//			strError.Format("No device found : %d\n", i);
////			AfxMessageBox(strError);
//#ifdef DEBUG_MODE
//	AfxMessageBox(strError);
//#endif
//			return false;
//		}
//	}
//
//	for(i=0;i<NumOfCams;i++)
//	{
//		if(NULL == hCam[i]) continue;
//
//		// read out camera information of openend camera
//		PylonGetCameraInfo (hCam[i], &CamInfo);
//		///////////////////////////////
//		// Configure the camera
//		///////////////////////////////
//
//		// Check for availability and access mode of PixelFormat
//		bAvail = PylonGetFeatureAvailability (hCam[i], CAM_FEATURE, "PixelFormat", &AccessMode);
//
//		// Get number of PixelFormat entries
//		PylonGetNumEnumEntries (hCam[i], CAM_FEATURE, "PixelFormat", &Num);
//
//		// get all entries and their access mode
//		for (j = 0; j < Num; j++)
//			PylonGetEnumEntryByIndex (hCam[i], CAM_FEATURE, "PixelFormat", j, StrBuffer, &AccessMode);
//
//		// Set Device User ID
//		PylonSetStringFeature (hCam[i], CAM_FEATURE, "DeviceUserID", "Basler's cool Camera");
//
//		// Read Out Device User ID and Device ID (= Serial number)
//		PylonGetStringFeature (hCam[i], CAM_FEATURE, "DeviceUserID", StrBuffer);
//		PylonGetStringFeature (hCam[i], CAM_FEATURE, "DeviceID", StrBuffer);
//
//		// Read out Current Pixel formatand set it to Mono 8
//		PylonGetEnumFeature (hCam[i], CAM_FEATURE, "PixelFormat", StrBuffer);
//		PylonSetEnumFeature (hCam[i], CAM_FEATURE, "PixelFormat", "Mono8");
//
//		// Read out current AOI
//		PylonGetIntFeature (hCam[i], CAM_FEATURE, "OffsetX", &OffsetX, 0, 0, 0);
//		PylonGetIntFeature (hCam[i], CAM_FEATURE, "OffsetY", &OffsetY, 0, 0, 0);
//		PylonGetIntFeature (hCam[i], CAM_FEATURE, "Width", &Width, 0, &MaxWidth, 0);
//		PylonGetIntFeature (hCam[i], CAM_FEATURE, "Height", &Height, 0, &MaxHeight, 0);
////PYLONDLL_API BOOL _stdcall PylonSetIntFeature (/*In*/ PYLONCAMHANDLE hCamera, EPylonFeatureType ftype, const char *FeatureName, long Val);
//
//		// Set and Get Width and Height of AOI
//		PylonSetIntFeature (hCam[i], CAM_FEATURE, "OffsetY", YOFFSET);
//		PylonSetIntFeature (hCam[i], CAM_FEATURE, "Width", WIDTH);
//		PylonSetIntFeature (hCam[i], CAM_FEATURE, "Height", HEIGHT);
//		PylonGetIntFeature (hCam[i], CAM_FEATURE, "Width", &Width, 0, 0, 0);
//		PylonGetIntFeature (hCam[i], CAM_FEATURE, "Height", &Height, 0, 0, 0);
//
//		// Set Testimage to Testimage 2
//		PylonSetEnumFeature (hCam[i], CAM_FEATURE, "TestImageSelector", "Testimageoff");
//
//		// Configure Acquisition
//		PylonSetEnumFeature (hCam[i], CAM_FEATURE, "TriggerSelector", "AcquisitionStart");
//		PylonSetEnumFeature (hCam[i], CAM_FEATURE, "AcquisitionMode", "Continuous");
//
//
////LineSelectorEnums
//
//#ifdef TEST_MODE
//		PylonSetEnumFeature (hCam[i], CAM_FEATURE, "TriggerMode", "Off");
//		PylonSetBoolFeature (hCam[0], CAM_FEATURE, "AcquisitionFrameRateEnable", TRUE);	//use
//		PylonSetFloatFeature (hCam[0], CAM_FEATURE, "AcquisitionFrameRateAbs", 8); //85frame /1sec
//// Trigger없이 테스트 하려면 아래 5줄 죽이고 위 한줄 살린다.
//#else
//		PylonSetEnumFeature (hCam[i], CAM_FEATURE, "TriggerMode", "On");
//		PylonSetEnumFeature (hCam[i], CAM_FEATURE, "TriggerSource", "Line1");
//		PylonSetEnumFeature (hCam[i], CAM_FEATURE, "TriggerActivation", "RisingEdge");
//		PylonSetEnumFeature (hCam[i], CAM_FEATURE, "LineSelector", "Line1");
//		PylonSetFloatFeature (hCam[i], CAM_FEATURE, "LineDebouncerTimeAbs", 100);
//		PylonSetBoolFeature (hCam[0], CAM_FEATURE, "AcquisitionFrameRateEnable", FALSE);	//use
//#endif
//
//		PylonSetEnumFeature (hCam[i], CAM_FEATURE, "ExposureMode", "Timed");
//		PylonSetEnumFeature (hCam[i], CAM_FEATURE, "ExposureTimeAbs", "500"); //3000 usec
////		PylonSetEnumFeature (hCam[i], CAM_FEATURE, "ExposureTimeRaw", "21");
//
//		
//		// Configure Streamgrabber
//		PylonSetIntFeature (hCam[i], CAM_FEATURE, "GevSCPSPacketSize", 1500);//1500);
//
//		PylonGetIntFeature (hCam[i], CAM_FEATURE, "PayloadSize", &BufferSize, 0, 0, 0);
//		PylonSetIntFeature (hCam[i], STREAM_FEATURE, "MaxBufferSize", BufferSize);
//		PylonSetIntFeature (hCam[i], STREAM_FEATURE, "MaxNumBuffer", NUM_BUFFERS);
//	}
//
//
//	for(i=0;i<NumOfCams;i++)
//	{
//		///////////////////////////////
//		// Grab Images
//		///////////////////////////////
//		PylonPrepareGrab (hCam[i]);
//
//		for (j=0; j<NUM_BUFFERS; j++)
//		{
//			hBuffer[i][j] = PylonRegisterBuffer (hCam[i], ImageBuffer[i][j], BufferSize);
//			PylonQueueBuffer (hCam[i], hBuffer[i][j], j);
//		}
//	}
//
//	return bRet;
//}
//#endif
//
//
//#ifdef PYLON_2_2
//void CVision1::Close()
//{
//	int i,j;
//
//	for(i=0;i<NumOfCams;i++)
//	{
//		if(hCam[i]==NULL) continue;
//
//		for (j=0; j<NUM_BUFFERS; j++)
//		{
//			PylonStreamGrabberDeregisterBuffer( hGrabber, hBuffer[i][j] );	//2.2
//		}
//
//		///////////////////////////////
//		// Clean Up
//		///////////////////////////////
//		PylonStreamGrabberCancelGrab( hGrabber );		//2.2
//		res = PylonStreamGrabberFinishGrab( hGrabber );	//2.2
//		res = PylonStreamGrabberClose( hGrabber );	//2.2
//
//
//	    res = PylonDeviceClose( hCam[i] );	//2.2
//		res = PylonDestroyDevice ( hCam[i] );//2.2
//
//	}
//	// Uninitialize Pylon
//	PylonTerminate ();
//}
//#else
//void CVision1::Close()
//{
//	int i,j;
//
//	for(i=0;i<NumOfCams;i++)
//	{
//		if(hCam[i]==NULL) continue;
//
//		for (j=0; j<NUM_BUFFERS; j++)
//		{
//			PylonDeregisterBuffer (hCam[i], hBuffer[i][j]);
//		}
//
//		///////////////////////////////
//		// Clean Up
//		///////////////////////////////
//		PylonCancelGrab (hCam[i]);
//		PylonFinishGrab (hCam[i]);
//		PylonCamClose (hCam[i]);
//	}
//	// Uninitialize Pylon
//	PylonTerminate ();
//}
//#endif
//
//void CVisWebView::SetGiGaLanExposure(int ntime)
//{
////	char strtime[10];
//	static int nOldSh = 0;
////	sprintf(strtime,"%d",ntime);
//	if(nOldSh != ntime)	//ExposureTimeAbs
//	{
////		PylonSetFloatFeature (hCam[0], "ExposureTimeAbs", ntime); //3000 usec//2.0
////		res = PylonDeviceSetFloatFeature( hCam[0], "ExposureTimeAbs", ntime );		//2.2
//		g_Temp.m_bChangeExposure=true;
//		g_Temp.m_nExposureData=ntime;
//	}
//	nOldSh = ntime;
//}
//
//
//
//void CVisWebView::SetChgLine(int line)
//{
//#ifdef PYLON_2_2
//	PylonDeviceSetIntegerFeatureInt32 (hCam[0], "OffsetY", line);	//2.2
//#else
//	PylonSetIntFeature (hCam[0], CAM_FEATURE, "OffsetY", line);		//2.0
//#endif
//}
//
//void CVision1::HookStart()
//{
//	g_Temp.m_nGrab1Count		=0;
//	g_Temp.m_nBuffer1ID			=0;
//	g_Temp.m_GRAB1Done			=false;
//	g_Temp.m_GRAB1START			=true;
//	g_Temp.m_GRABControlSTART	=true;
//#ifdef PYLON_2_2
//	PylonDeviceExecuteCommandFeature( hCam[0], "AcquisitionStart");	//2.2
//#else
//	PylonExecCommand (hCam[0], CAM_FEATURE, "AcquisitionStart");	//2.0
//#endif
//	
//}
//void CVision1::HookStop()
//{
//	g_Temp.m_GRAB1START			=false;
//	g_Temp.m_GRABControlSTART	=false;
//	Sleep(50);
//#ifdef PYLON_2_2
//	PylonDeviceExecuteCommandFeature( hCam[0], "AcquisitionStop");
//    res = PylonStreamGrabberCancelGrab( hGrabber );	//2.2
//    do 
//    {
//        res = PylonStreamGrabberRetrieveResult( hGrabber, &grabResult, &isReady );	//2.2
//    } while ( isReady );
//    for (int i = 0; i < NUM_BUFFERS; ++i )
//    {
//        res = PylonStreamGrabberQueueBuffer( hGrabber, hBuffer[0][i], (void*) i );	//2.2
//    }
//#else
//	PylonExecCommand (hCam[0], CAM_FEATURE, "AcquisitionStop");	//2.0
//#endif
//	
//}
//UINT Grab1Thread(LPVOID pParam)
//{
//	CVisWebView *pView = (CVisWebView *)pParam;
//	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());
//		
//	EPylonGrabStatus GrabStatus;
//	long BufferIx;
//	int nCheckBuff = -999;
//	int nTimeOut = 5000, ntimeGap = 500;
//	int nID1 = 0;
//	g_Temp.m_GRAB1RUN=true;
//	while(g_Temp.m_GRAB1RUN)
//    {
//		if(g_Temp.m_GRAB1START)
//		{
//			BufferIx = 0;
//#ifdef PYLON_2_2
//			PylonWaitObjectWait( hWait, INFINITE, &isReady );		//2.2
//			res = PylonStreamGrabberRetrieveResult( hGrabber, &grabResult, &isReady );	//2.2
//			BufferIx = (int) grabResult.Context;
//#else
//			PylonGetBuffer (hCam[0], INFINITE, &BufferIx, &GrabStatus); //INFINITE
//#endif
//
//			if(nCheckBuff ==BufferIx)
//			{
//				if(NUM_BUFFERS>1)
//				{
//					//Grab Fail
//					pView->SendMessage(WM_RESTART,0,0);
//					nCheckBuff = -999;
//				}
//			}
//			else
//			{
//				CString str;
//				str.Format("%d",GrabStatus);
//#ifdef PYLON_2_2
//				if ( grabResult.Status == Grabbed && g_Temp.m_GRAB1RUN )							//2.2
//				{
//					memcpy(gBuffer1[g_Temp.m_nBuffer1ID]+WIDTH*HEIGHT*g_Temp.m_nGrab1Count, ImageBuffer[0][BufferIx],WIDTH*HEIGHT); 
//					g_Temp.m_nGrab1Count++;
//
//					if(g_Temp.m_nGrab1Count>=NUM_BUFFERS)
//					{
//						g_Temp.m_nGrab1Count=0;
//						g_Temp.m_nBuffer1ID=(g_Temp.m_nBuffer1ID+1)%MAX_FULL_BUF;
//						g_Temp.m_GRAB1Done=true;	
//					}
//				}
//				else if ( grabResult.Status == Failed  && g_Temp.m_GRAB1RUN)						//2.2
//				{
//					pView->fnWriteEndFile(str);
//
//				}
//				else if(g_Temp.m_GRAB1RUN)
//				{
//					pView->fnWriteEndFile(str);
//				}
//				PylonStreamGrabberQueueBuffer( hGrabber, grabResult.hBuffer, (void*) BufferIx );	 //2.2
//				if(g_Temp.m_bChangeExposure)
//				{
//					PylonDeviceSetFloatFeature( hCam[0], "ExposureTimeAbs", g_Temp.m_nExposureData );//2.2
//					g_Temp.m_bChangeExposure=false;
//				}
//
//#else
//				if (GrabStatus == Grabbed)
//				{
//					memcpy(gBuffer1[g_Temp.m_nBuffer1ID]+WIDTH*HEIGHT*g_Temp.m_nGrab1Count, ImageBuffer[0][BufferIx],WIDTH*HEIGHT); 
//					g_Temp.m_nGrab1Count++;
//
//					if(g_Temp.m_nGrab1Count>=NUM_BUFFERS)
//					{
//						g_Temp.m_nGrab1Count=0;
//						g_Temp.m_nBuffer1ID=(g_Temp.m_nBuffer1ID+1)%MAX_FULL_BUF;
//						g_Temp.m_GRAB1Done=true;
//					}
//					PylonQueueBuffer (hCam[0], hBuffer[0][BufferIx], BufferIx);
//				}
//				else
//				{
//					pView->fnWriteEndFile(str);
//					PylonQueueBuffer (hCam[0], hBuffer[0][BufferIx], BufferIx);
//				}
//				if(g_Temp.m_bChangeExposure)
//				{
//					PylonSetFloatFeature (hCam[0], CAM_FEATURE, "ExposureTimeAbs", g_Temp.m_nExposureData); //2.0
//					g_Temp.m_bChangeExposure=false;
//				}
//
//#endif
//
//				nCheckBuff = BufferIx;
//			}
//		}
//		
//		Sleep(1);
//	}
//
//    return 0;
//}
//extern int g_frame_num;
//UINT Grab1ThreadSUB(LPVOID pParam)
//{
//	CVisWebView *pView = (CVisWebView *)pParam;
//	CVisWebDoc* pDoc = (CVisWebDoc*)(pView->GetDocument());
//		
//	EPylonGrabStatus GrabStatus;
//	long BufferIx;
//	int nCheckBuff = -999;
//	int nTimeOut = 5000, ntimeGap = 500;
//	int nID1 = 0;
//	g_Temp.m_GRAB1RUNSUB=true;
//	while(g_Temp.m_GRAB1RUNSUB)
//    {
//		if(!g_Temp.m_GRAB1Done)
//		{
//			Sleep(1);
//			continue;
//		}
//		
//		do
//		{
//			if(g_Temp.m_GRAB1Done)
//			{
//				g_Temp.m_GRAB1Done=false;
//				g_frame_num++;
//
//				//방금 Grab완료된 이미지를 gBufferTemp에 복사한다.---
//				nID1=g_Temp.m_nBuffer1ID-1;
//				if(nID1<0) nID1=MAX_FULL_BUF-1;
//				memcpy(gBufferTemp, gBuffer1[nID1], WIDTH*HEIGHT*NUM_BUFFERS);
//				//---------------------------------------------------
//			}
//			Sleep(1);
//			if(g_Temp.m_GRAB1RUNSUB==0) return 0;
//		}while(g_Temp.m_Inspecting);
//
//		//Inspect가 완료되면 다시 검사 이미지에 gBufferTemp 를 복사한다.
//		pView->CopyMilImgForSlit(gBufferTemp);
//			
//		Sleep(1);
//	}
//
//    return 0;
//}
//
//#else
//BOOL CVision1::Open(HWND hWnd) {return true;}
//void CVision1::Close()		  {			   }
//void CVisWebView::SetGiGaLanExposure(int ntime){}
//void CVisWebView::SetChgLine(int line) {}
//void CVision1::HookStart(){}
//void CVision1::HookStop(){}
//UINT Grab1Thread(LPVOID pParam) { return 0; }
//UINT Grab1ThreadSUB(LPVOID pParam) { return 0; }
//#endif


void CVisWebView::SetFrameRate(int ncount)
{
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
}

void CVision1::GetExposureTime(double *dValue)
{
	*dValue=m_nExposure;
}

unsigned short* CVision1::GetProcessBufShort()
{
	return 0;
}

LPBYTE CVision1::GetProcessBuf()
{
	return 0;
}

int CVisWebView::CopyMilImgForSlit(LPBYTE fmLeft)//, LPBYTE fmRight)
{
	int i,k,j =0;
	CVisWebDoc *pDoc = (CVisWebDoc*)GetDocument();
	BOOL nRet = 1;
	static int nc= 0;
	int npos;
	int nheight= pDoc->m_pImage->GetHeight();
	int nwidth = pDoc->m_pImage->GetWidth();

	CTimingProcess* timer = ((CVisWebApp*)AfxGetApp())->m_pTiming;
	unsigned char* fmImg = pDoc->m_pImage->GetImagePtr();
	unsigned char* fmNgImg = pDoc->m_pImageNG->GetImagePtr();

//	if((pDoc->m_data.m_nInspDirection == 2 ||pDoc->m_data.m_nInspDirection == 3) && pDoc->m_data.m_nMachine==1)
	if(pDoc->m_data.m_nInspDirection == 2 ||pDoc->m_data.m_nInspDirection == 3)// && pDoc->m_data.m_nMachine==1)
	{//coating

		for(i=0;i<nheight;i++)
		{//reverse
			if(j%HEIGHT == 0) j = 0;
			npos = (i/HEIGHT)+1;
			k = ((npos*HEIGHT) - j)-1;
			memcpy(fmImg+nwidth*i,   fmLeft+WIDTH*k, WIDTH);
			memcpy(fmNgImg+nwidth*i, fmLeft+WIDTH*k, WIDTH);
			j++;
		}
	}
	else
	{
		for(i=0;i<nheight;i++)
		{
			memcpy(fmImg+nwidth*i, fmLeft+WIDTH*i, WIDTH);
			memcpy(fmNgImg+nwidth*i, fmLeft+WIDTH*i, WIDTH);
		}
	}

	nRet = 1;

	if(nc%10==0)
	{
		m_img_save_time = timer->GetTimer(TIMING_IDX_TEST_GRAB);
		m_fFps = float(10000 / m_img_save_time);
		timer->SetTimer(TIMING_IDX_TEST_GRAB);
	}
	g_Temp.m_Inspecting=true;
	m_ev_Inspect.SetEvent();
	nc++;
	return nRet;
}
//
//void CInspect::FindDefectSlitArea(CImage* pImage, CData *pData)
//{
////	if(pData->m_nDefectCount == MAX_DEFECT-1){	//chcho
//	if(pData->m_nDefectCount == MAX_DEFECT){
//		RejectDefect(pData);
//		return;
//	}
//	int i;
//	CRect rect = pData->m_rectIns;
//	int nSkipX = 2;
//	int nSkipY = 2;
//	unsigned char* fm = pImage->GetImagePtr();
//
//	int nVisionLine = pData->GetVisionLine();//GetVisionLine(pData->m_strComName);
//
//
////	SLIT_Inspect(fm, rect.left, rect.top, rect.right, rect.bottom, IMAGE_WIDTH, g_nLeftRightCut);
//
//
//
//	for(i=0;i<g_FrameResult.nNGCount;i++)
//	{	
//		pData->m_bDefectWhite[pData->m_nDefectCount]= FALSE;			//흑색이물
//		pData->m_bResult[pData->m_nDefectCount]		= FALSE;
//
//		pData->m_nDefectVMin[pData->m_nDefectCount] = 0;
//		pData->m_ptDefect[pData->m_nDefectCount].x = g_FrameResult.nNGPosX[i];
//		pData->m_ptDefect[pData->m_nDefectCount].y = g_FrameResult.nNGPosY[i];
//
//		pData->m_rectDefect[pData->m_nDefectCount].SetRect(g_FrameResult.nNGPosX[i],g_FrameResult.nNGPosY[i],g_FrameResult.nNGPosX[i],g_FrameResult.nNGPosY[i]);
//		pData->m_rectDefect[pData->m_nDefectCount].InflateRect(BAD_IMG_WIDTH/2, BAD_IMG_HEIGHT/2);
//		ValidRect(&pData->m_rectDefect[pData->m_nDefectCount]);
//		UpdateNGImage(pImage, pData);
//		GetDefectInfo(pData);
//
//		pData->m_nDefectCount++;
//		if(pData->m_nDefectCount == MAX_DEFECT)	goto done;
//		
//	}
//done:
//	RejectDefect(pData);
//}
//
