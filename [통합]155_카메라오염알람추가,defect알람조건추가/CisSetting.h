#include <time.h>

#pragma once




// CCisSetting
#define WM_RECEIVEDATA	WM_USER+13
#define LOAD_SUCCESS	"0001"

class CCisSetting : public CWnd
{
	DECLARE_DYNAMIC(CCisSetting)

public:
	CCisSetting();
	virtual ~CCisSetting();
//	Ccis_cam_settingDlg pjntest;


protected:
	DECLARE_MESSAGE_MAP()
	HANDLE m_ComHandle;
	CWinThread* m_pComThread;
	static UINT ComThread(LPVOID pParam);
	
public:
	
	HWND m_hwnd;

	bool bConnected;
	TCHAR tCisRxData[20];

	void Close(bool bConnected);
	int Open(CString strPort, CString strBaud);

	bool WriteString(CString strValue);

	bool ResetCamera(void);
	bool checkResponse(CString strCmd);
	bool SendCmd(CString strCmd,int nMode);




	//int LoadParam(void);
	//int CreateParamINI();
	
	//int SaveUserSetting(int nUserNum);
	//int LoadUserSetting(int nUserNum);
	//parameter.ini 받는 변수  
// 	CString strBaudRate;			//Baud Rate. 00=9600, 01=19200, 02=115200 
// 	CString strOutputFormat;		//Output Format. 09=8bit Serial Medium Configuration
// 	CString strOutputFreq;		//Output Clock Freq. 1C=84MHz, 00(48MHz)~1C(84MHz)
// 	CString strSyncMode;			//Syncronous Signal Mode(Internal) & Pulse Width. 000E00=Internal(11.36fps)~002000=Internal(5.12fps)], 01=External
// 	CString strLightControl;		//Light Control. 04=Turn Off, 05=A Turn On, 06=B Turn On, 07=A&B Turn On
// 	CString strDarkCorrection;	//Dark Correction. 00=Off, 01=On
// 	CString strWhiteCorrection;	//White Correction. 00=Off, 01=On
// 	CString strGain;				//Gain. 00=Off, 01=On, 200000~200400=Pos.value, 210000~210400=Neg.value
// 	CString strGamma;				//01: GC01<CR> Gamma Correction On
// 	CString strResolution;		//Output Resolution. 00=600dpi, 01=300dpi, 02=150dpi, 03=75dpi
// 	CString strTestPattern;		//Test Pattern Output. 00=Off, 01=On
// 	CString strResetMode;			//Software Reset 01=FPGA boot, 21=ASIC boot 
// 	CString strUserMemory;		//Memory Register 00=Load Factory setting, 01=Load User#1, 02=Load User#2, 03=Load User#3, 81=Save User#1, 82=Save User#2, 83=Save User#3



	

};


