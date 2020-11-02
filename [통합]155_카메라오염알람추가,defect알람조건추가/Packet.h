// Packet.h: interface for the CPacket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PACKET_H__0086D72B_3BA5_46C1_A01B_A01D89AD6CDC__INCLUDED_)
#define AFX_PACKET_H__0086D72B_3BA5_46C1_A01B_A01D89AD6CDC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logData.h"

#define MAX_BADIMAGE_FILENAME	100
typedef struct tagDEFECT
{
	int			defect_class;
	float		x_pos;
	float		y_pos;
	float		size_x;
	float		size_y;
	char		filename[MAX_BADIMAGE_FILENAME];
}DEFECT;

class CPacket  
{
public:
	CPacket();
	virtual ~CPacket();

	CLogData	*m_pLogPacket;

	// 수신시에 코드값만 일단 분해. 
	int		GetCode(char* buf, int buf_len);	
	//----------------------------------------------------------------------------------------------------------------------------------------------

	// Client -> Server
//	void	MakeDataPacket(int frame_num, int defect_cnt, int* defect_class, float* defect_x, float* defect_y, float* size_x, float* size_y, char** defect_image);
	void	MakeDataPacket(int frame_num, int defect_cnt,int lotNo, int* defect_class, float* defect_x, float* defect_y, float* size_x, float* size_y, char** defect_image);
	// Server에서 받은 데이터 분해.
	void	PullDataPacket(char* buf, int buf_len, int& code, int& frame_num, int& defect_cnt, DEFECT** defect);
	//----------------------------------------------------------------------------------------------------------------------------------------------

	// Client -> Server
	void	MakeCalibPacket(int avg_luminousity, int detection_frame, int x_pos_in_pixel, int y_pos_in_pixel);
	// 서버에서 받은 캘리브레이션 데이터 분해. 
	void	PullCalibPacket(char* buf, int buf_len, int& code, int &avg_luminousity, int &detection_frame, int& x_pos_in_pixel, int& y_pos_in_pixel);
	//----------------------------------------------------------------------------------------------------------------------------------------------

	//	Server -> Client
	void	MakeInstantPacket(int code, LPCSTR param_name, double val);
	void	MakeInstantPacket(int code, LPCSTR param_name, LPSTR str_val, int len);
	//  Client에서 데이터 분해.
	void	PullInstantPacket(char* buf, int buf_len, int& code, LPSTR &param_name, double &val, LPSTR &str_val);
	//----------------------------------------------------------------------------------------------------------------------------------------------
	
	char*	m_pBuf;
	int		m_nBuflen;

protected:
	int		m_nFull_packet_length;
	int		m_nPacket_code;
//	int		m_nPacket_type;

	int		m_nDefect;
	DEFECT	*m_pDefect_data;
};

#endif // !defined(AFX_PACKET_H__0086D72B_3BA5_46C1_A01B_A01D89AD6CDC__INCLUDED_)
