// XManageSocket.cpp: implementation of the CXManageSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "..\stdafx.h"
#include "XManageSocket.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXManageSocket::CXManageSocket()
{

}

CXManageSocket::~CXManageSocket()
{

}

void CXManageSocket::OnDataReceived(LPBYTE lpBuffer, DWORD dwCount)
{
//	SendMessage((HWND)m_pParent,WM_XDATARRECIEVED,(DWORD)m_iPort-DEFAULT_PORT,(LPARAM)lpBuffer);
	SendMessage((HWND)m_pParent,WM_XDATARRECIEVED,(DWORD)m_iPort-DEFAULT_PORT,(LPARAM)lpBuffer);
}

void CXManageSocket::SendInsData(int lotNo, int frame_num, int defect_cnt, int *defect_class, float *defect_x, float *defect_y, float *size_x, float *size_y, char **defect_image)
{
	CPacket packet;
	packet.MakeDataPacket(lotNo,frame_num, defect_cnt, defect_class, defect_x, defect_y, size_x, size_y, defect_image);

	WriteComm((LPBYTE)packet.m_pBuf, packet.m_nBuflen,DEFAULT_TIMEOUT);
}

void CXManageSocket::SendInsData(CPacket* packet)
{
	WriteComm((LPBYTE)packet->m_pBuf, packet->m_nBuflen,DEFAULT_TIMEOUT);
}

void CXManageSocket::SendCommand_LocalHost(int nCommand)
{
	CPacket packet;
	packet.MakeInstantPacket(nCommand, PARAM_DUMMY, -1);	

	WriteComm((LPBYTE)packet.m_pBuf, packet.m_nBuflen,DEFAULT_TIMEOUT);
}

void CXManageSocket::SendInstantData_LocalHost(LPCSTR param_name, double value)
{
	CPacket packet;
//	packet.MakeInstantPacket(NM_PARAM_INSTANT, param_name, value);
	packet.MakeInstantPacket(NM_ACK_CAM_AVERAGE, param_name, value);

	WriteComm((LPBYTE)packet.m_pBuf, packet.m_nBuflen,DEFAULT_TIMEOUT);
}

void CXManageSocket::SendInstantData_LocalHost(LPCSTR param_name, LPSTR str_data)
{
	CPacket packet;

	int len = strlen(str_data);
	packet.MakeInstantPacket(NM_PARAM_INSTANT, param_name, str_data, len);

	WriteComm((LPBYTE)packet.m_pBuf, packet.m_nBuflen,DEFAULT_TIMEOUT);
}

void CXManageSocket::SendInstantData_LocalHostBCR(LPCSTR param_name, double value)
{
	CPacket packet;
	packet.MakeInstantPacket(MN_DATA_NEB, param_name, value);

	WriteComm((LPBYTE)packet.m_pBuf, packet.m_nBuflen,DEFAULT_TIMEOUT);
}

void CXManageSocket::SendInstantData_LocalHostLight(LPCSTR param_name, double value)
{
	CPacket packet;
//	packet.MakeInstantPacket(NM_PARAM_INSTANT, param_name, value);
	packet.MakeInstantPacket(NM_ACK_LIGHT_DATA, param_name, value);

	WriteComm((LPBYTE)packet.m_pBuf, packet.m_nBuflen,DEFAULT_TIMEOUT);
}
