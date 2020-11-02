// ServerSocket.cpp : implementation file
//

#include "stdafx.h"
#include "ServerSocket.h"
#include "Network.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServerSocket

CServerSocket::CServerSocket()
{
}

CServerSocket::~CServerSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CServerSocket, CSocket)
	//{{AFX_MSG_MAP(CServerSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CServerSocket member functions

void CServerSocket::Init(CNetwork* org, CWnd *pWnd, int nPortNum)
{
	m_org = org;
	m_pWnd = pWnd;
	m_nPort =nPortNum;
	
	Create(nPortNum);
	if(!Listen())
		AfxMessageBox("Listen mechanism flaw");
}

void CServerSocket::OnAccept(int nErrorCode) 
{
	m_org->Accept();
	CSocket::OnAccept(nErrorCode);
}

void CServerSocket::OnClose(int nErrorCode) 
{
	CSocket::OnClose(nErrorCode);
}