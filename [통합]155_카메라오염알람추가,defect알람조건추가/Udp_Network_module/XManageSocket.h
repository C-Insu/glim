// XManageSocket.h: interface for the CXManageSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XMANAGESOCKET_H__9F129CF5_44BF_4F3F_8CD7_C179C4EF9DF0__INCLUDED_)
#define AFX_XMANAGESOCKET_H__9F129CF5_44BF_4F3F_8CD7_C179C4EF9DF0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XSocketComm.h"
#include "Packet.h"

class CXManageSocket : public CXSocketComm  
{
public:
	void SendInsData(CPacket *packet);
//	void SendInsData(int frame_num, int defect_cnt, int* defect_class, float* defect_x, float* defect_y, float* size_x, float* size_y, char** defect_image);
	void SendInsData(int lotNo, int frame_num, int defect_cnt, int* defect_class, float* defect_x, float* defect_y, float* size_x, float* size_y, char** defect_image);
	CXManageSocket();
	virtual ~CXManageSocket();
	virtual void OnDataReceived(const LPBYTE lpBuffer, DWORD dwCount);
	void SendInstantData_LocalHost(LPCSTR param_name, LPSTR str_data);
	void SendInstantData_LocalHost(LPCSTR param_name, double value);
	void SendInstantData_LocalHostBCR(LPCSTR param_name, double value);
	void SendCommand_LocalHost(int nCommand);
	void SendInstantData_LocalHostLight(LPCSTR param_name, double value);
};

#endif // !defined(AFX_XMANAGESOCKET_H__9F129CF5_44BF_4F3F_8CD7_C179C4EF9DF0__INCLUDED_)
