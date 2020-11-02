// CisSetting.cpp : ���� �����Դϴ�.
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



// CCisSetting �޽��� ó�����Դϴ�.



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
// 	Ccis_cam_settingDlg* pMain = (Ccis_cam_settingDlg*)::AfxGetMainWnd();	//ljn 190203 ***Ŭ���� ������ ���鶧 ���� ���� ������ �ϱ�. 
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
		while(ComStat.cbInQue >= 5)			//ljn ������ ���� ������ ������ == 5					// PC���� �д� ������ ������ (����)
		{
			ReadFile(m_CisSetting->m_ComHandle, RxData, ComStat.cbInQue, &ReadBytes, NULL);


			strcpy_s(m_CisSetting->tCisRxData,RxData);	//���� ������ ���� 

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
{	//�ø������ 
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
// 	//folder ����
// 	strPath.Format(_T("C:\\Glim"));
// 	CreateDirectory(strPath, NULL);
// 	strPath.Format(_T("C:\\Glim\\Model"));
// 	CreateDirectory(strPath, NULL);
// 
// 	//file �����غ� [SER_GETD(FALSE, ����(value), 0) �� ����Ǳ� ������ ������ ��������� �ʴ´�.]
// 	strPath.Format(_T("C:\\Glim\\Model\\Parameter.ini"));
// 	CIni ini1(strPath, _T("CIS_Parameter") , 0);
// 
// 	//���� ���� Ȯ��
// 	CFileStatus m_fileStatus;
// 	if(CFile::GetStatus("C:\\Glim\\Model\\Parameter.ini",m_fileStatus)){
// 		//������ ������ ���� Ž. ini ���Ͽ� �ִ� ������ ī�޶� ����[load param() �Լ� ����]
// 		
// 		//�ҰԾ���. loadparam();���� ����Ÿ �б���. 
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
// 		//������ ������ ���� Ž. �⺻������ ini ���ϻ��� + ī�޶���[loadParam(); �Լ� ����]
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

	SendCmd(_T("SR21"),0); //FPGA ����

	SendCmd(_T("SR01"),0); //ASIC ����

	bRtn[0]=SendCmd(_T("SRA0"),0); //FPGA ���� �б�

	bRtn[1]=SendCmd(_T("SR80"),0); //ASIC ���� �б� 

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
// 		//�ð�üũ 
// // 		if(tCisRxData!="")
// // 			break; 
// 
// 
// 		if(tCisRxData!=""){
// 			if(strCmd.Left(4)=="DT01"){
// 				if(1==_tcscmp(tCisRxData, "0021")){ //�޸� �ε� ����("0001")  
// 					//���� �α�
// 					//strLog.Format(_T("ī�޶� �޸� 1 �ε�"));  
// 					bRtn = true;
// 				}else{
// 					//���� �α�
// 					//strLog.Format(_T("ī�޶� �޸� 1 �ε����"));  
// 					bRtn = false;
// 				}
// 			}
// 			//���� ����Ÿ �ʱ�ȭ 
// 			strcpy_s(tCisRxData, tmp);
// 			break;
// 			
// 		}
// 	
// 		Sleep(1); 
// 	}
	return false;
}

bool CCisSetting::SendCmd(CString strCmd,int nMode)	//0x0d ������ 4���ڸ� �Է��ϸ��. 
{
	bool bRtn; 
	
	//��� ���� �� ���� ������ ���� �ʱ�ȭ 
	strcpy_s(tCisRxData,_T("")); 

	//��� ���� 
	bRtn=WriteString(strCmd); 
	
	//ī�޶� ����� �����ϴ� �ð��� ��ٷ��ش�. 
//	Sleep(2000); 

	if(nMode==0)
	Wait(1000);
	//���� Ȯ�� 
	double sttTime = clock();
	double endTime; 

	while (bConnected)
	{
		endTime = clock(); 
		//����ð� �ʰ�
		if((endTime-sttTime)/CLOCKS_PER_SEC>200){
			break;								
		}
		
		//���� ���� Ȯ�� 
		if(1==_tcscmp(tCisRxData,"00")){
			
			if(strCmd.Left(4)=="DT01"){			//�޸�-1 �ε� ���
				if(1==_tcscmp(tCisRxData,"0001")) return true;	//���� �� ����
				else							  return false; //�� �� ������ ����
			}
			else if(strCmd.Left(4)=="SR21")		//FPGA ���� ���
				if(1==_tcscmp(tCisRxData,"0021"))	return true; 
				else								return false; 
			else if(strCmd.Left(4)=="SR01")		//ASIC ���� ��� 
				if(1==_tcscmp(tCisRxData,"0001"))	return true; 
				else								return false; 
			else if(strCmd.Left(4)=="SRA0")		//FPGA ���� ���� �б�
				if(1==_tcscmp(tCisRxData,"0020"))	return true; 
				else								return false; 
			else if(strCmd.Left(4)=="SR80")		//ASIC ���� ���� �б�
				if(1==_tcscmp(tCisRxData,"0000"))	return true; 
				else								return false; 
			else	break; //��ϵ��� ���� ����� ���� ��� ����
		}
		
		Sleep(1);
	}
	
	
	
	
return false;
}
