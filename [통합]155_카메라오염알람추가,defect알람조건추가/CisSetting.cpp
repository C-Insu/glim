// CisSetting.cpp : 구현 파일입니다.
//
#include "afxwin.h"
#include "stdafx.h"
//#include "cis_cam_settingDlg.h"
#include "CisSetting.h"
#include "ini.h"
#include <time.h>

#define MAXBUF	4096

static CEvent evtComKill;	//
//TCHAR	tCisRxData[20]="";

// CCisSetting

IMPLEMENT_DYNAMIC(CCisSetting, CWnd)

CCisSetting::CCisSetting()
{
	m_hwnd= NULL;
	//bConnected = FALSE;
	//bCisLoad = FALSE;
	//tCisRxData[20] = ""; 
}

CCisSetting::~CCisSetting()
{
// 	if(bConnected) 
// 		Close();
}


BEGIN_MESSAGE_MAP(CCisSetting, CWnd)
END_MESSAGE_MAP()



// CCisSetting 메시지 처리기입니다.



int CCisSetting::Open(CString strPort, CString strBaud)
{	
	
	
	
	bConnected=false;

// 	if(bConnected){	
// 			Close(bConnected);		 
// 		return FALSE;
// 	}

	m_ComHandle = CreateFile(strPort, GENERIC_READ|GENERIC_WRITE, 
		NULL, NULL, OPEN_EXISTING,	FILE_ATTRIBUTE_NORMAL, NULL);
	if(m_ComHandle == INVALID_HANDLE_VALUE) 
		return FALSE;

	DCB	dcb;
	GetCommState(m_ComHandle, &dcb);
	

 	 
// 	CString strTemp; 
// 	Ccis_cam_settingDlg* pMain = (Ccis_cam_settingDlg*)::AfxGetMainWnd();	//ljn 190203 ***클래스 포인터 만들때 접근 권한 갖도록 하기. 
// 	pMain->m_strBaud.GetWindowText(strTemp);
	//int nTemp = atoi(strTemp);	
	//DWORD dwBaud = (DWORD)nTemp;
	
	//cstring to dword convert 
	DWORD dwBaud = atol((char*)(LPCTSTR)strBaud);	


	dcb.BaudRate = dwBaud;				//serial setting  
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;
	dcb.fNull = FALSE;

	SetCommState(m_ComHandle, &dcb);

	DWORD evtMask = EV_RXCHAR|EV_TXEMPTY;
	SetCommMask(m_ComHandle, evtMask);

	//bConnected = true;
	bConnected= true;
	evtComKill.ResetEvent();
	m_pComThread = AfxBeginThread(ComThread, this);



	return true;
	
}


void CCisSetting::Close(bool bConnected)
{
	if(bConnected){
		bConnected=FALSE; 
		evtComKill.SetEvent();
		CloseHandle(m_ComHandle);
	}

}

UINT CCisSetting::ComThread(LPVOID pParam)
{
	TCHAR	RxData[20]="";
	DWORD	ErrorFlag = NULL;
	DWORD	ReadBytes = NULL;
	COMSTAT	ComStat;

	CCisSetting *m_CisSetting = (CCisSetting*)pParam;

	int nTimeOut = 5000;
	double d1 = GetTickCount();
	while (1)//WaitForSingleObject(evtComKill.m_hObject, 10) != WAIT_OBJECT_0) 
	{
		ClearCommError(m_CisSetting->m_ComHandle, &ErrorFlag, &ComStat);
		while(ComStat.cbInQue >= 5)			//ljn 미쯔비시 응답 데이터 사이즈 == 5					// PC에서 읽는 데이터 사이즈 (고정)
		{
			ReadFile(m_CisSetting->m_ComHandle, RxData, ComStat.cbInQue, &ReadBytes, NULL);


			strcpy_s(m_CisSetting->tCisRxData,RxData);	//응답 데이터 복사 

			//return m_CisSetting->tCisRxData;

			if(m_CisSetting->m_hwnd)
				::SendMessage(m_CisSetting->m_hwnd, WM_RECEIVEDATA, (UINT)RxData, ReadBytes);

			ClearCommError(m_CisSetting->m_ComHandle, &ErrorFlag, &ComStat);
			
// 			if (m_CisSetting->bConnected) {
// 				break;
			//}
			Sleep(1);
// 			if(GetTickCount()-d1 >nTimeOut)
// 				break;
 		} 
		Sleep(1);
// 		if(GetTickCount()-d1 >nTimeOut)
// 			break;
	}
	return NULL;
}

bool CCisSetting::WriteString(CString strValue)
{	//시리얼통신 
	DWORD dwWriteBytes = NULL;
	if(bConnected){ 
		strValue.Format(_T(strValue+"%c"),0x0d);
		WriteFile(m_ComHandle, strValue, strValue.GetLength(), &dwWriteBytes, NULL);
		return TRUE;	
	}
	return FALSE;
}

// int CCisSetting::LoadParam(void)
// {
// 
// 	CString strValue;
// 	CString strPath;
// 
// 	strPath.Format(_T("C:\\Glim\\Model\\Parameter.ini"));
// 	CIni ini1(strPath, _T("CIS_Parameter") , 0);
// 
// 	//load parameter data & set cam (write string)
// 	//Baud Rate. 00=9600, 01=19200, 02=115200  
// 	ini1.SER_GETD(TRUE, strBaudRate, 0);	//true = read, false = write  
// 	strValue.Format("BR%s%c",strBaudRate, 0x0d);
// 	WriteString(strValue);
// 	//Output Format. 09=8bit Serial Medium Configuration
// 	ini1.SER_GETD(TRUE, strOutputFormat, 0);
// 	strValue.Format("OC%s%c",strOutputFormat, 0x0d);
// 	WriteString(strValue);
// 	//Output Clock Freq. 1C=84MHz, 00(48MHz)~1C(84MHz)
// 	ini1.SER_GETD(TRUE, strOutputFreq, 0);
// 	strValue.Format("OF%s%c",strOutputFreq, 0x0d);
// 	WriteString(strValue);
// 	//Synchronous Signal Mode(Internal) & Pulse Width. 000E00=Internal(11.36fps)~002000=Internal(5.12fps)], 01=External
// 	ini1.SER_GETD(TRUE, strSyncMode, 0);
// 	strValue.Format("SS%s%c",strSyncMode, 0x0d);
// 	WriteString(strValue);
// 	//Light Control. 04=Turn Off, 05=A Turn On, 06=B Turn On, 07=A&B Turn On
// 	ini1.SER_GETD(TRUE, strLightControl, 0);
// 	strValue.Format("LC%s%c",strLightControl, 0x0d);
// 	WriteString(strValue);
// 	//Dark Correction. 00=Off, 01=On
// 	ini1.SER_GETD(TRUE, strDarkCorrection, 0);
// 	strValue.Format("DC%s%c",strDarkCorrection, 0x0d);
// 	WriteString(strValue);
// 	//White Correction. 00=Off, 01=On
// 	ini1.SER_GETD(TRUE, strWhiteCorrection, 0);
// 	strValue.Format("WC%s%c",strWhiteCorrection, 0x0d);
// 	WriteString(strValue);
// 	//Gain. 00=Off, 01=On, 200000~200400=Pos.value, 210000~210400=Neg.value
// 	ini1.SER_GETD(TRUE, strGain, 0);
// 	strValue.Format("PG%s%c",strGain, 0x0d);
// 	WriteString(strValue);
// 	//Output Resolution. 00=600dpi, 01=300dpi, 02=150dpi, 03=75dpi
// 	ini1.SER_GETD(TRUE, strResolution, 0);
// 	strValue.Format("GC%s%c",strResolution, 0x0d);
// 	WriteString(strValue);
// 	//Test Pattern Output. 00=Off, 01=On
// 	ini1.SER_GETD(TRUE, strTestPattern, 0);
// 	strValue.Format("RC%s%c",strTestPattern, 0x0d);
// 	WriteString(strValue);
// 	//Software Reset 01=FPGA boot, 21=ASIC boot 
// 	ini1.SER_GETD(TRUE, strResetMode, 0);
// 	strValue.Format("TP%s%c",strResetMode, 0x0d);
// 	WriteString(strValue);
// 	
// 
// 	return 0;
// }

// int CCisSetting::CreateParamINI()
// {		
// 
// 	CString strValue;
// 	CString strPath;
// 	//folder 생성
// 	strPath.Format(_T("C:\\Glim"));
// 	CreateDirectory(strPath, NULL);
// 	strPath.Format(_T("C:\\Glim\\Model"));
// 	CreateDirectory(strPath, NULL);
// 
// 	//file 생성준비 [SER_GETD(FALSE, 변수(value), 0) 가 실행되기 전에는 파일이 만들어지지 않는다.]
// 	strPath.Format(_T("C:\\Glim\\Model\\Parameter.ini"));
// 	CIni ini1(strPath, _T("CIS_Parameter") , 0);
// 
// 	//파일 유무 확인
// 	CFileStatus m_fileStatus;
// 	if(CFile::GetStatus("C:\\Glim\\Model\\Parameter.ini",m_fileStatus)){
// 		//파일이 있으면 여기 탐. ini 파일에 있는 값으로 카메라 세팅[load param() 함수 실행]
// 		
// 		//할게없다. loadparam();에서 데이타 읽기함. 
// 
// // 		//read data
// // 		//Baud Rate. 00=9600, 01=19200, 02=115200 
// // 		ini1.SER_GETD(TRUE, strBaudRate, 0);	//true = read, false = write 
// // 		//Output Format. 09=8bit Serial Medium Configuration
// // 		ini1.SER_GETD(TRUE, strOutputFormat, 0);
// // 		//Output Clock Freq. 1C=84MHz, 00(48MHz)~1C(84MHz)
// // 		ini1.SER_GETD(TRUE, strOutputFreq, 0);
// // 		//Syncronous Signal Mode(Internal) & Pulse Width. 000E00=Internal(11.36fps)~002000=Internal(5.12fps)], 01=External
// // 		ini1.SER_GETD(TRUE, strSyncMode, 0);
// // 		//Light Control. 04=Turn Off, 05=A Turn On, 06=B Turn On, 07=A&B Turn On
// // 		ini1.SER_GETD(TRUE, strLightControl, 0);
// // 		//Dark Correction. 00=Off, 01=On
// // 		ini1.SER_GETD(TRUE, strDarkCorrection, 0);
// // 		//White Correction. 00=Off, 01=On
// // 		ini1.SER_GETD(TRUE, strWhiteCorrection, 0);
// // 		//Gain. 00=Off, 01=On, 200000~200400=Pos.value, 210000~210400=Neg.value
// // 		ini1.SER_GETD(TRUE, strGain, 0);
// // 		//Gamma. 00=Off, 01=On
// // 		ini1.SER_GETD(TRUE, strGamma, 0);
// // 		//Output Resolution. 00=600dpi, 01=300dpi, 02=150dpi, 03=75dpi
// // 		ini1.SER_GETD(TRUE, strResolution, 0);
// // 		//Test Pattern Output. 00=Off, 01=On
// // 		ini1.SER_GETD(TRUE, strTestPattern, 0);
// // 		//Software Reset 01=FPGA boot, 21=ASIC boot 
// // 		ini1.SER_GETD(TRUE, strResetMode, 0);
// 	}
//  	else{
// 		//파일이 없으면 여기 탐. 기본값으로 ini 파일생성 + 카메라세팅[loadParam(); 함수 실행]
// 	
// 		//write data
// 		//Baud Rate. 00=9600, 01=19200, 02=115200 
// 		strBaudRate.Format("00");
// 		ini1.SER_GETD(FALSE, strBaudRate, 0);	//true = read, false = write 
// 		//Output Format. 09=8bit Serial Medium Configuration
// 		strOutputFormat.Format("09");
// 		ini1.SER_GETD(FALSE, strOutputFormat, 0);
// 		//Output Clock Freq. 1C=84MHz, 00(48MHz)~1C(84MHz)
// 		strOutputFreq.Format("1C");
// 		ini1.SER_GETD(FALSE, strOutputFreq, 0);
// 		//Syncronous Signal Mode(Internal) & Pulse Width. 000E00=Internal(11.36fps)~002000=Internal(5.12fps)], 01=External
// 		strSyncMode.Format("001000");
// 		ini1.SER_GETD(FALSE, strSyncMode, 0);
// 		//Light Control. 04=Turn Off, 05=A Turn On, 06=B Turn On, 07=A&B Turn On
// 		strLightControl.Format("07");
// 		ini1.SER_GETD(FALSE, strLightControl, 0);
// 		//Dark Correction. 00=Off, 01=On
// 		strDarkCorrection.Format("01");
// 		ini1.SER_GETD(FALSE, strDarkCorrection, 0);
// 		//White Correction. 00=Off, 01=On
// 		strWhiteCorrection.Format("01");
// 		ini1.SER_GETD(FALSE, strWhiteCorrection, 0);
// 		//Gain. 00=Off, 01=On, 200000~200400=Pos.value, 210000~210400=Neg.value
// 		strGain.Format("01");
// 		ini1.SER_GETD(FALSE, strGain, 0);
// 		//Gamma. 00=Off, 01=On
// 		strGamma.Format("01");
// 		ini1.SER_GETD(FALSE, strGamma, 0);
// 		//Output Resolution. 00=600dpi, 01=300dpi, 02=150dpi, 03=75dpi
// 		strResolution.Format("00");
// 		ini1.SER_GETD(FALSE, strResolution, 0);
// 		//Test Pattern Output. 00=Off, 01=On
// 		strTestPattern.Format("01");
// 		ini1.SER_GETD(FALSE, strTestPattern, 0);
// 		//Software Reset 01=FPGA boot, 21=ASIC boot 
// 		strResetMode.Format("01");
// 		ini1.SER_GETD(FALSE, strResetMode, 0);
// 
// 	}
// 	
// 
// 
// 
// 	return 0;
// }
// 

// int CCisSetting::SaveUserSetting(int nUserNum)
// {
// 	if(nUserNum==0)	//SR8'0' = not available save to 'factory setting memory' 
// 		return -1; 
// 	CString strValue; 
// 	//Memory Register. 81=Save User#1, 82=Save User#2, 83=Save User#3
// 	strValue.Format("SR8%s%c",nUserNum, 0x0d);
// 	WriteString(strValue);
// 	return 0;
// }
// 
// int CCisSetting::LoadUserSetting(int nUserNum)
// {
// 	CString strValue; 
// 	//Memory Register. 00=Load Factory setting, 01=Load User#1, 02=Load User#2, 03=Load User#3
// 	strValue.Format("SR0%s%c",nUserNum, 0x0d);
// 	WriteString(strValue);
// 	return 0;
// }

bool CCisSetting::ResetCamera(void)
{	
	bool bRtn[2]; 

	SendCmd(_T("SR21"),0); //FPGA 부팅

	SendCmd(_T("SR01"),0); //ASIC 부팅

	bRtn[0]=SendCmd(_T("SRA0"),0); //FPGA 상태 읽기

	bRtn[1]=SendCmd(_T("SR80"),0); //ASIC 상태 읽기 

	if(bRtn[0]&&bRtn[1])
		return true;
	
	
	return bRtn;
}

bool CCisSetting::checkResponse(CString strCmd)
{	
// 	bool bRtn; 
// 	TCHAR tmp[20]=""; 
// 	
// 
// 	while (bConnected)
// 	{
// 		//시간체크 
// // 		if(tCisRxData!="")
// // 			break; 
// 
// 
// 		if(tCisRxData!=""){
// 			if(strCmd.Left(4)=="DT01"){
// 				if(1==_tcscmp(tCisRxData, "0021")){ //메모리 로드 성공("0001")  
// 					//성공 로그
// 					//strLog.Format(_T("카메라 메모리 1 로드"));  
// 					bRtn = true;
// 				}else{
// 					//실패 로그
// 					//strLog.Format(_T("카메라 메모리 1 로드실패"));  
// 					bRtn = false;
// 				}
// 			}
// 			//응답 데이타 초기화 
// 			strcpy_s(tCisRxData, tmp);
// 			break;
// 			
// 		}
// 	
// 		Sleep(1); 
// 	}
	return false;
}

bool CCisSetting::SendCmd(CString strCmd,int nMode)	//0x0d 제외한 4글자만 입력하면됨. 
{
	bool bRtn; 
	
	//명령 전달 전 응답 데이터 버퍼 초기화 
	strcpy_s(tCisRxData,_T("")); 

	//명령 전달 
	bRtn=WriteString(strCmd); 
	
	//카메라가 명령을 수행하는 시간을 기다려준다. 
//	Sleep(2000); 

	if(nMode==0)
	Wait(1000);
	//응답 확인 
	double sttTime = clock();
	double endTime; 

	while (bConnected)
	{
		endTime = clock(); 
		//응답시간 초과
		if((endTime-sttTime)/CLOCKS_PER_SEC>200){
			break;								
		}
		
		//응답 버퍼 확인 
		if(1==_tcscmp(tCisRxData,"00")){
			
			if(strCmd.Left(4)=="DT01"){			//메모리-1 로드 명령
				if(1==_tcscmp(tCisRxData,"0001")) return true;	//성공 시 응답
				else							  return false; //그 외 응답은 실패
			}
			else if(strCmd.Left(4)=="SR21")		//FPGA 부팅 명령
				if(1==_tcscmp(tCisRxData,"0021"))	return true; 
				else								return false; 
			else if(strCmd.Left(4)=="SR01")		//ASIC 부팅 명령 
				if(1==_tcscmp(tCisRxData,"0001"))	return true; 
				else								return false; 
			else if(strCmd.Left(4)=="SRA0")		//FPGA 상태 정보 읽기
				if(1==_tcscmp(tCisRxData,"0020"))	return true; 
				else								return false; 
			else if(strCmd.Left(4)=="SR80")		//ASIC 상태 정보 읽기
				if(1==_tcscmp(tCisRxData,"0000"))	return true; 
				else								return false; 
			else	break; //등록되지 않은 명령이 들어온 경우 나감
		}
		
		Sleep(1);
	}
	
	
	
	
return false;
}
