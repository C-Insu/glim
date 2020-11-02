// 2.0	egio에서 hanaio dll 통합버젼

#pragma once
#include <Afxmt.h>
//#define	 MAX_INPUT	32

//#define	EGIO
#define	HANAIO
//#define	CONTECIO
#define MAX_INPUT	4


#ifdef HANAIO
	#include "DLL_IOModule.h"
#endif



class CgIO
{
public:
	CgIO();
public:
	~CgIO(void);
protected:
	BOOL	m_bOpen;
	BOOL	m_bRead;
	short	m_nDIODevice;
	LPVOID	m_pMain;
	CEvent	m_eOneOutPulse;

public:
	
	BOOL	m_bOkNg;//0ng , 1ok
	BOOL	m_bIoComplete;
	bool	m_bInputData[MAX_INPUT];
	bool	m_bInputPC;
	static UINT threadPulseOut(LPVOID pParam);
	static UINT threadIOOut(LPVOID pParam);

	BOOL InitIO(LPVOID pParam,int nDeviceid);
	void OneOutPulseEvent();
	void Destroy(void);
	void WriteOutputPort(int nCam,int port, bool bValue);
	void WriteOutputPortPulse(int nCam,int port,int ms);
	int ReadInputPort(int port);
	bool* ReadInput(int nRet);
	const bool* GetInputState();

#ifdef	HANAIO
	HINSTANCE 	hinst;
	int (__stdcall* COM_Open)(int nPort, CallbackFunc* Callback, bool _bThreadUseFlag);
	bool (__stdcall* COM_Close)();
	bool (__stdcall* COM_IsOpened)();
	void (__stdcall* COM_Read)();
	void (__stdcall* Get_State_Info)();
	void (__stdcall* Set_DO_Port_Ctrl)(BYTE cPort, int _nOnOffCtrl);
	void (__stdcall* KeyCode)(unsigned char *_pData, unsigned char _cDataSize, unsigned char *_pBuf, PINT _cBufSize);
#else if 	
	static UINT threadIO(LPVOID pParam);
#endif
};
