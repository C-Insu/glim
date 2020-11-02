// XSocketComm.h: interface for the CXSocketComm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XSOCKETCOMM_H__475406C9_20AF_4A6D_BBD9_89405FAD1BBC__INCLUDED_)
#define AFX_XSOCKETCOMM_H__475406C9_20AF_4A6D_BBD9_89405FAD1BBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <winsock2.h>
#define WSA_ASYNC		(WM_USER+1)
#define	BUFFER_SIZE		20480	//packet size 판단루틴 추가.
#define	DEFAULT_TIMEOUT	100L
//#pragma comment (lib,"ws2_32.lib")
//속성링크 WS2_32.lib 
#pragma comment (lib,"wsock32.lib")
 
class CXSocketComm  
{

protected:
	static UINT WINAPI SocketThreadProc(LPVOID pParam);
	SOCKET			m_Sock;
	SOCKADDR_IN		m_Addr;
	HWND			m_pParent;
	HANDLE			m_hThread;		// Thread Comm handle
	unsigned short	m_iPort;

public:
	CXSocketComm();
	virtual ~CXSocketComm();
	virtual void OnDataReceived(const LPBYTE lpBuffer, DWORD dwCount);

	int GetIpAdr();
	void StopComm();
	void Run();
	void WatchComm();
	int SendTo(const void* lpBuf, int nBufLen, int nFlags=0);
	DWORD WriteComm(LPBYTE lpBuffer,DWORD dwSize,DWORD dwTimeout,int nFlags =0);
	DWORD ReadComm(LPBYTE lpBuffer, DWORD dwSize, DWORD dwTimeOut);
	void Close();
	void ErrorMessage(HWND hwnd, char *error, int err_num);
	BOOL Create(HWND hWnd,
               UINT nSocketPort = 0,
               LPCTSTR lpszSocketAddress = NULL, 
               int nSocketType = SOCK_DGRAM,
               long lEvent = FD_READ | FD_WRITE | FD_OOB | FD_ACCEPT | FD_CONNECT | FD_CLOSE
               );
};

#endif // !defined(AFX_XSOCKETCOMM_H__475406C9_20AF_4A6D_BBD9_89405FAD1BBC__INCLUDED_)
