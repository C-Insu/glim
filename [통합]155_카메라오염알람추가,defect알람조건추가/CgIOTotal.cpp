#include "StdAfx.h"
#include "CgIOTotal.h"
#include "resource.h"
#include "VisWebView.h"				//maindlg헤더파일을 include해야함.



#ifdef HANAIO
bool CALLBACK Callback(BYTE *_pbyBuffer, DWORD _nNbyte);
#endif
CVisWebView* pMainDlg = NULL;

CgIO::CgIO()
{
	m_bOpen = FALSE;
	m_bInputPC = FALSE;
	for(int i=0;i<MAX_INPUT;i++)
		m_bInputData[i] = FALSE;
	m_bIoComplete = FALSE;
	m_bOkNg = TRUE;
}

CgIO::~CgIO(void)
{

}

UINT CgIO::threadPulseOut(LPVOID pParam)
{
	CgIO* pIO = (CgIO*)pParam;

// 	while(pIO->m_bRead)
// 	{		
// 		if(	WaitForSingleObject((HANDLE)pIO->m_eOneOutPulse,100))
// 		{
// 			pIO->m_eOneOutPulse.ResetEvent();
// 			pIO->WriteOutputPortPulse(0,0,100);
// 		}
// 		Sleep(0);
// 	}
	return 1;
}

UINT CgIO::threadIOOut(LPVOID pParam)
{
//	CgIO* pIO = (CgIO*)pParam;
	CVisWebView* pDlg = (CVisWebView*)pParam;
	int Retval=0;
	int nStat = 0;
	CString str;
	int nFlagCnt=0;
	static bool bOn = FALSE;

// 	while(pDlg->m_IO[0].m_bRead)
// 	{
// 		if(pDlg->m_IO[0].m_bIoComplete)
// 		{
// 			pDlg->m_IO[0].m_bIoComplete = FALSE;
// 			if(!pDlg->m_IO[0].m_bOkNg)
// 				pDlg->m_IO[0].WriteOutputPort(0,1,TRUE);
// 			else
// 				pDlg->m_IO[0].WriteOutputPort(0,0,TRUE);
// 			pDlg->m_IO[0].WriteOutputPort(0,1,true);
// 			Sleep(100);
// 			for(int i=1;i<4;i++)
// 				pDlg->m_IO[0].WriteOutputPort(0,i,FALSE);
// 
// 		}
// 		Sleep(1);
// 	}
	return Retval;
}

#ifdef HANAIO
	bool CALLBACK Callback(BYTE *_pbyBuffer, DWORD _nNbyte)
	{
		//CString strTemp,strTemp1,strTemp2;

		//if(pMainDlg->m_pDlgSet->m_FormTab3->m_bCheckInputSignal == FALSE)
		//	return TRUE;

		//for(DWORD i=0; i<_nNbyte;i++)
		//{
		//	strTemp1.Format(_T("[%02X]"), _pbyBuffer[i]);
		//	strTemp = strTemp + strTemp1;
		//}
		//strTemp2.Format("%d",_pbyBuffer[0]);

		//if(atoi(strTemp2) == 128)
		//	pMainDlg->m_IO->m_bInputPC = true;
		//else
		//	pMainDlg->m_IO->ReadInput(atoi(strTemp2));
		//pMainDlg->LoopIO(pMainDlg->m_IO->m_bInputData,pMainDlg->m_IO->m_bInputPC);

		return TRUE;
	}
#else

	UINT CgIO::threadIO(LPVOID pParam)
	{
		CFlyCapture2_EXDlg* pDlg = (CFlyCapture2_EXDlg*)pParam;
		int Retval=0;
		int nStat = 0;
		CString str;
		int nFlagCnt=0;
		static bool bOn = FALSE;

		while(pDlg->m_IO.m_bRead)
		{
			pDlg->m_IO.ReadInput(0);
			pDlg->LoopIO(pDlg->m_IO.m_bInputData);
		}
		return Retval;
	}
#endif

bool* CgIO::ReadInput(int nRet)
{
	
#ifdef	EGIO
	nRet = EGIOT_ReadInput(m_nDIODevice);
#endif		

#ifdef	CONTECIO
	BYTE data;
	DioInpByte(m_nDIODevice, 0, &data);
	nRet = data;
#endif

	int mask = 0x01;
	for(int i=0;i<MAX_INPUT;i++)
	{
		if(nRet & (mask<<i))	
			m_bInputData[i] = true;
		else
			m_bInputData[i] = false;
	}

	return m_bInputData;
}

int CgIO::InitIO(LPVOID pParam,int nDeviceid)
{
	m_pMain = pParam;
	m_nDIODevice = nDeviceid;
	CVisWebView* pDlg = (CVisWebView*)m_pMain;
	long nRet=1;
	CString strTemp;
	pMainDlg = pDlg;

#ifdef	HANAIO
	if(nDeviceid==0)
		hinst = LoadLibraryA("DLL_IOModule.dll");
	else
		hinst = LoadLibraryA("DLL_IOModule1.dll");

	COM_Open  = (int (__stdcall*)(int   nPort, CallbackFunc* Callback, bool _bThreadUseFlag))GetProcAddress(hinst, "COM_Open");
	COM_Close = (bool (__stdcall*)())GetProcAddress(hinst, "COM_Close");
	COM_IsOpened  = (bool (__stdcall*)())GetProcAddress(hinst, "COM_IsOpened");
	COM_Read = (void (__stdcall*)())GetProcAddress(hinst, "COM_Read");
	Get_State_Info = (void (__stdcall*)())GetProcAddress(hinst, "Get_State_Info");
	Set_DO_Port_Ctrl = (void (__stdcall*)(BYTE cPort, int _nOnOffCtrl))GetProcAddress(hinst, "Set_DO_Port_Ctrl");
	KeyCode = (void (__stdcall*)(unsigned char *_pData, unsigned char _cDataSize, unsigned char *_pBuf, PINT _cBufSize))GetProcAddress(hinst, "KeyCode");


	bool	bUseThreadFlag = FALSE;//true;
	int nport1 = pDlg->m_nIOPort;
	if(COM_Open(nport1, Callback, bUseThreadFlag) != 1)
		nRet=0;
	else
		nRet=1;	
#endif

	if (nRet!=0)
	{
		m_bRead = TRUE;

//		CWinThread *pThread = ::AfxBeginThread(threadIO, m_pMain); // thread 생성
		strTemp.Format(_T("IO Connected"));
	}
	else
		strTemp.Format(_T("IO Disconnected"));
	pDlg->AddtoList(strTemp,0,0);
//	pDlg->AddtoCamList(0,strTemp);

//	AfxBeginThread(threadIOOut, m_pMain);
	m_bOpen = nRet;
	return nRet;
}

void CgIO::Destroy(void)
{
	m_bRead = FALSE;
	Sleep(100);

#ifdef	HANAIO
	if(m_bOpen)
		COM_Close();
#endif	

}

void CgIO::WriteOutputPort(int nCam,int port, bool bValue)
{
	CVisWebView* pDlg = (CVisWebView*)m_pMain;
	CString strTemp;
	//int	nLow = port%2;
	CTime time = CTime::GetCurrentTime();

	if(port == 0)
		strTemp.Format("outGOOD_On[CAM%d]v-%d\n",nCam+1,bValue);
	if(port == 1)
		strTemp.Format("outNG_On[CAM%d]v-%d\n",nCam+1,bValue);

	if(bValue && ( port == 0 || port == 1 )){
		strTemp = time.Format("[%H:%M:%S]") + strTemp;
		//pMainDlg->AddtoCamList(nCam,strTemp);
//		pDlg->m_strLogData += strTemp;
	}

// 	if(bValue && ( port == OUTPUT_GOOD || port == OUTPUT_NG || port == OUTPUT_COMPLETE )){
// 		pDlg->m_dSignalTime[port-1] = pDlg->GetPrecisionTime();
// 	}


#ifdef HANAIO

	BYTE 	cPort = 0x00;
	if(port == 0) cPort = 0x00;
	if(port == 1) cPort = 0x01;
	if(port == 2) cPort = 0x02;
	if(port == 3) cPort = 0x03;

	Set_DO_Port_Ctrl(cPort, bValue);
#endif	
}




int CgIO::ReadInputPort(int port)
{
	int nRet=0;


	return nRet;
}

const bool* CgIO::GetInputState()
{
	return m_bInputData;
}

void CgIO::OneOutPulseEvent()
{
	m_eOneOutPulse.SetEvent();
}

void CgIO::WriteOutputPortPulse(int nCam,int port,int ms)
{
	WriteOutputPort(nCam,port, TRUE);
	Sleep(ms);
	WriteOutputPort(nCam,port, FALSE);
}