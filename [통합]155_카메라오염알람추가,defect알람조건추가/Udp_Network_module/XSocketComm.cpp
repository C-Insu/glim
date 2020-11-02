// XSocketComm.cpp: implementation of the CXSocketComm class.
//
//////////////////////////////////////////////////////////////////////

#include "..\stdafx.h"
#include "XSocketComm.h"
#include <atlconv.h>
#include <process.h>
#include <stdio.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXSocketComm::CXSocketComm():
m_hThread(NULL)
{

}

CXSocketComm::~CXSocketComm()
{
	StopComm();
}

void CXSocketComm::WatchComm()
{
		HANDLE hThread;
		UINT uiThreadId = 0;
		hThread = (HANDLE)_beginthreadex(NULL,	// Security attributes
								  0,	// stack
					SocketThreadProc,	// Thread proc
								this,	// Thread param
					CREATE_SUSPENDED,	// creation mode
						&uiThreadId);	// Thread ID
		if ( NULL != hThread)
		{
			ResumeThread( hThread );
			m_hThread = hThread;
			return ;
		}
}

///////////////////////////////////////////////////////////////////////////////
// SocketThreadProc
///////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:
//     Socket Thread function.  This function is the main thread for socket
//     communication - Asynchronous mode.
// PARAMETERS:
//     LPVOID pParam : Thread parameter - a CSocketComm pointer
// NOTES:
///////////////////////////////////////////////////////////////////////////////
UINT WINAPI CXSocketComm::SocketThreadProc(LPVOID pParam)
{
	CXSocketComm* pThis = reinterpret_cast<CXSocketComm*>( pParam );
	_ASSERTE( pThis != NULL );

	pThis->Run();

	return 1L;
} // end SocketThreadProc

void CXSocketComm::Run()
{
	BYTE	byData[BUFFER_SIZE];
	LPBYTE  lpData = byData;
	DWORD	dwBytes = 0L;

	while(m_hThread)
	{
		memset(byData,0,BUFFER_SIZE);
		dwBytes = ReadComm(lpData,BUFFER_SIZE,DEFAULT_TIMEOUT);
		if(dwBytes > 0L)
		{
			OnDataReceived( lpData, dwBytes);
		}
		Sleep(0);
	}
}

BOOL CXSocketComm::Create(HWND hWnd, UINT nSocketPort, LPCTSTR lpszSocketAddress, int nSocketType, long lEvent)
{				//63010
	m_pParent = hWnd;
	WSADATA wsaData;
	
	if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
	{		
		ErrorMessage(hWnd, "WSAStartup() Failure!!!", WSAGetLastError());
		return FALSE;
	}
	
	m_Sock = socket(AF_INET, nSocketType, 0);
	if(m_Sock == SOCKET_ERROR)
	{
		ErrorMessage(hWnd, "socket() Failure!!!", WSAGetLastError());
		return FALSE;
	}
	
	m_iPort = nSocketPort;
	m_Addr.sin_family = AF_INET;
	m_Addr.sin_port = htons(nSocketPort);
	
	if(lpszSocketAddress)	//sending socket
	{
		m_Addr.sin_addr.s_addr = inet_addr(lpszSocketAddress);
		BOOL optval = TRUE;
		if ( SOCKET_ERROR == setsockopt( m_Sock, SOL_SOCKET, SO_BROADCAST, (char *) &optval, sizeof( BOOL ) ) )
		{
			ErrorMessage(hWnd, "socket error!!!", WSAGetLastError());
			Close();
			return false;
		}	
	}
	else					//recieve socket
	{
		m_Addr.sin_addr.s_addr = htonl(INADDR_ANY);
		// Inform Windows Sockets provider that broadcast messages are allowed

		if(bind(m_Sock, (struct sockaddr *)&m_Addr, sizeof(m_Addr)) == SOCKET_ERROR)
		{
			ErrorMessage(hWnd, "bind() Failure!!!", WSAGetLastError());
			Close();
			return FALSE;
		}
		if(WSAAsyncSelect(m_Sock, hWnd, WSA_ASYNC, FD_ACCEPT | FD_READ | FD_CLOSE | FD_OOB) == SOCKET_ERROR) // | FD_READ | FD_CLOSE
		{
			ErrorMessage(hWnd, "WSAAsyncSelect(FD_ACCEPT) Failure!!!", WSAGetLastError());
			return FALSE;
		}
	}
	
	return TRUE;
}

void CXSocketComm::ErrorMessage(HWND hwnd, char *error, int err_num)
{
	char	szError[80];
	
	wsprintf(szError, "%s : %d", error, err_num);
	MessageBox(hwnd, szError, "Chatting Client", MB_OK | MB_ICONERROR);
}

void CXSocketComm::Close()
{
	closesocket(m_Sock);
	WSACleanup();
}

int CXSocketComm::SendTo(const void* lpBuf, int nBufLen, int nFlags)
{
	_ASSERTE( nBufLen<BUFFER_SIZE );

	char buf[BUFFER_SIZE];
	memcpy(buf,lpBuf,nBufLen);
	int iResult = sendto(m_Sock, buf, nBufLen, nFlags, (const struct sockaddr *)&m_Addr, sizeof(m_Addr));

	return iResult;
}

DWORD CXSocketComm::ReadComm(LPBYTE lpBuffer, DWORD dwSize,DWORD dwTimeout)
{
	LPBYTE lpData = lpBuffer;

	if (lpBuffer == NULL || dwSize < 1L)
		return 0L;

	fd_set	fdRead  = { 0 };
	TIMEVAL	stTime;
	TIMEVAL	*pstTime = NULL;

	if ( INFINITE != dwTimeout ) {
		stTime.tv_sec = dwTimeout/1000;
		stTime.tv_usec = dwTimeout % 1000;
		pstTime = &stTime;
	}

	// Set Descriptor
	if ( !FD_ISSET( m_Sock, &fdRead ) )
		FD_SET( m_Sock, &fdRead );
	
	// Select function set read timeout
	DWORD dwBytesRead = 0L;
	int res = select( m_Sock+1, &fdRead, NULL, NULL, pstTime );
	if(res>0)
	{
		res = recv(m_Sock, (LPSTR)lpData, dwSize, 0);
	}

	dwBytesRead = (DWORD)((res >= 0)?(res) : (-1L));
	
	return dwBytesRead;
}

void CXSocketComm::OnDataReceived(LPBYTE lpBuffer, DWORD dwCount)
{

}

DWORD CXSocketComm::WriteComm(LPBYTE lpBuffer, DWORD dwSize,DWORD dwTimeout, int nFlags)
{
	// Accept 0 bytes message
	if (NULL == lpBuffer)
		return 0L;

	fd_set	fdWrite  = { 0 };
	TIMEVAL	stTime;
	TIMEVAL	*pstTime = NULL;

	if ( INFINITE != dwTimeout ) {
		stTime.tv_sec = dwTimeout/1000;
		stTime.tv_usec = dwTimeout % 1000;
		pstTime = &stTime;
	}
	// Set Descriptor
	if ( !FD_ISSET( m_Sock, &fdWrite ) )
		FD_SET( m_Sock, &fdWrite );

	// Select function set write timeout
	DWORD dwBytesWritten = 0L;
	int res = select( m_Sock+1, NULL, &fdWrite, NULL, pstTime );
	if(res>0)
	{
		res = SendTo(lpBuffer,dwSize);
		dwBytesWritten = (DWORD)((res >= 0)?(res) : (-1));
	}
	return res;
}

void CXSocketComm::StopComm()
{
	if (WaitForSingleObject(m_hThread, 1000L) == WAIT_TIMEOUT)
		TerminateThread(m_hThread, 1L);
	CloseHandle(m_hThread);
	m_hThread = NULL;
}

int CXSocketComm::GetIpAdr()
{
	char name[256];
	char ip[4];
	memset(ip,0,4);
	PHOSTENT hostinfo;
    int re = gethostname(name, sizeof(name));

    if(re == 0)
    {
        if((hostinfo = gethostbyname(name)) != NULL)
        {
            strcpy(name,inet_ntoa(*(struct in_addr *)*hostinfo->h_addr_list));
			re = strlen(name);
			int dot=0,i;
			for( i=1;i<re&&dot!=3;i++)
			{
				if(name[i]=='.')
					dot++;
			}
			_ASSERTE( dot==3 );
			memcpy(ip,&name[i],re-i);
        }
    }
	
   return atoi(ip);
}
