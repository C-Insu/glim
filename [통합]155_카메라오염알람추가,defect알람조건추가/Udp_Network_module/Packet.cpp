// Packet.cpp: implementation of the CPacket class.
//
//////////////////////////////////////////////////////////////////////

#include "..\stdafx.h"
#include "Packet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPacket::CPacket()
{
	m_pBuf = NULL;
	m_pDefect_data = NULL;
}

CPacket::~CPacket()
{
	if(m_pDefect_data)
		delete [] m_pDefect_data;

	if(m_pBuf)
		delete [] m_pBuf;
}

int CPacket::GetCode(char* buf, int buf_len)
{
	int nCode=0;
	memcpy(&nCode, buf, 4);
	return nCode;
}

//void CPacket::MakeDataPacket(int frame_num, int defect_cnt, int* defect_class, float* defect_x, float* defect_y, float* size_x, float* size_y, char** defect_image)
void CPacket::MakeDataPacket(int frame_num, int defect_cnt,int lotNo, int* defect_class, float* defect_x, float* defect_y, float* size_x, float* size_y, char** defect_image)
{
	return;
	//------------------------------------
	//	검사 데이터 전송용 패킷.
	m_nPacket_code = NM_DATA;
	m_nDefect = defect_cnt;
	m_nBuflen = m_nFull_packet_length =  4 + 4 + 4 + 4 + 4 + sizeof(DEFECT)*m_nDefect;	//chcho
	
	if(m_pBuf)
		delete [] m_pBuf;
	m_pBuf = new char[m_nBuflen];
	memset(m_pBuf, 0, m_nBuflen);

	memcpy(m_pBuf, &m_nFull_packet_length, 4);
	memcpy(m_pBuf+4, &m_nPacket_code, 4);
//	memcpy(m_pBuf+8, &frame_num, 4);
//	memcpy(m_pBuf+12, &m_nDefect, 4);

	memcpy(m_pBuf+8, &lotNo, 4);
	
	memcpy(m_pBuf+12, &frame_num, 4);
	memcpy(m_pBuf+16, &m_nDefect, 4);



	if(m_pDefect_data)
	{
		delete [] m_pDefect_data;
		m_pDefect_data = NULL;
	}
	
	if(defect_cnt)
	{
		m_pDefect_data = new DEFECT[m_nDefect];
		
		for(int i=0; i<m_nDefect; i++)	
		{
			m_pDefect_data[i].defect_class = defect_class[i];
			m_pDefect_data[i].x_pos = defect_x[i];
			m_pDefect_data[i].y_pos = defect_y[i];
			m_pDefect_data[i].size_x = size_x[i];
			m_pDefect_data[i].size_y = size_y[i];

			strcpy(m_pDefect_data[i].filename, defect_image[i]);		
		}		
		memcpy(m_pBuf+20, m_pDefect_data, sizeof(DEFECT)*m_nDefect);
	}
}

void CPacket::PullDataPacket(char* buf, int buf_len, int& code, int& frame_num, int& defect_cnt)
{
	if(m_pBuf)
		delete [] m_pBuf;
	m_nBuflen = buf_len;
	m_pBuf = new char[m_nBuflen];
	memcpy(m_pBuf, buf, m_nBuflen);
	//----------------------------------------------

	memcpy(&code, m_pBuf+4, 4);
	m_nPacket_code = code;
	if(code !=NM_DATA)	//데이터 패킷이 아닌 커맨드 패킷인 경우.
		return;
	
	memcpy(&frame_num, m_pBuf+8, 4);
	m_nFrame_num = frame_num;
	memcpy(&defect_cnt, m_pBuf+12, 4);
	m_nDefect = defect_cnt;

	if(defect_cnt>0)
	{
		m_pDefect_data = new DEFECT[defect_cnt];
		memcpy(m_pDefect_data, m_pBuf+16, sizeof(DEFECT)*defect_cnt);
	}
	else
		m_pDefect_data = NULL;

	//-----------------------------------------------

}

void CPacket::MakeCalibPacket(int detection_frame, int avg_luminousity, int x_pos_in_pixel, int y_pos_in_pixel)
{
	//------------------------------------
	//	클라이언트에서 서버로 보내는 캘리브레이션 데이터 전송용 패킷.
	m_nPacket_code = NM_CALIB_RESULT;
	m_nBuflen = m_nFull_packet_length = 4 + 4 + 4 + 4 + 4 + 4;
	
	if(m_pBuf)
		delete [] m_pBuf;
	m_pBuf = new char[m_nBuflen];
	memset(m_pBuf, 0, m_nBuflen);

	memcpy(m_pBuf, &m_nFull_packet_length, 4);
	memcpy(m_pBuf+4, &m_nPacket_code, 4);
	memcpy(m_pBuf+8, &avg_luminousity, 4);
	memcpy(m_pBuf+12, &detection_frame, 4);
	memcpy(m_pBuf+16, &x_pos_in_pixel, 4);
	memcpy(m_pBuf+20, &y_pos_in_pixel, 4);
}

void CPacket::PullCalibPacket(char* buf, int buf_len, int& code, int &avg_luminousity, int &detection_frame, int& x_pos_in_pixel, int& y_pos_in_pixel)
{
	if(m_pBuf)
		delete [] m_pBuf;
	m_nBuflen = buf_len;
	m_pBuf = new char[m_nBuflen];
	memcpy(m_pBuf, buf, m_nBuflen);
	//----------------------------------------------

	memcpy(&code, m_pBuf, 4);
	if(code !=NM_CALIB_RESULT)	//Calibration pacekt이 아닌경우.
		return;
	
	memcpy(&avg_luminousity, m_pBuf+4, 4);
	memcpy(&detection_frame, m_pBuf+8, 4);
	memcpy(&x_pos_in_pixel, m_pBuf+12, 4);
	memcpy(&y_pos_in_pixel, m_pBuf+16, 4);

	//-----------------------------------------------

}

void CPacket::MakeInstantPacket(int code, LPCSTR param_name, double val)
{
	//----------------------------------------
	//	코드값과 더블 값 하나를 전송하는 패킷.
	int name_len = strlen(param_name);
	m_nPacket_code = code;
	m_nBuflen = m_nFull_packet_length = 4 + 4 + 4 + name_len + 8;
	
	if(m_pBuf)
		delete [] m_pBuf;
	m_pBuf = new char[m_nBuflen];
	memset(m_pBuf, 0, m_nBuflen);

	memcpy(m_pBuf, &m_nFull_packet_length, 4);
	memcpy(m_pBuf+4, &m_nPacket_code, 4);
	memcpy(m_pBuf+8, &name_len, 4);
	memcpy(m_pBuf+12, param_name, name_len);
	memcpy(m_pBuf+12+name_len, &val, 8);
}

void CPacket::MakeInstantPacket(int code, LPCSTR param_name, LPSTR str_val, int len)
{
	//----------------------------------------
	//	코드값과 문자열 값 하나를 전송하는 패킷.
	int name_len = strlen(param_name);
	m_nPacket_code = code;
	m_nBuflen = m_nFull_packet_length = 4 + 4 + 4 + name_len + 4 + len;
	
	if(m_pBuf)
		delete [] m_pBuf;
	m_pBuf = new char[m_nBuflen];
	memset(m_pBuf, 0, m_nBuflen);


	memcpy(m_pBuf, &m_nFull_packet_length, 4);
	memcpy(m_pBuf+4, &m_nPacket_code, 4);
	memcpy(m_pBuf+8, &name_len, 4);
	memcpy(m_pBuf+12, param_name, name_len);

	memcpy(m_pBuf+12+name_len, &len, 4);
	memcpy(m_pBuf+16+name_len, str_val, len);
}

void CPacket::PullInstantPacket(char* buf, int buf_len, int& code, LPSTR &param_name, double &val, LPSTR &str_val)
{
	//---------------------------------------------
	//	코드값 하나와 더블 값 하나를 수신하는 패킷.
	if(m_pBuf)
		delete [] m_pBuf;
	m_nBuflen = buf_len;
	m_pBuf = new char[m_nBuflen];
	memcpy(m_pBuf, buf, m_nBuflen);

	//----------------------------------------------
	memcpy(&code, m_pBuf+4, 4);
//	if(code !=NM_PARAM_INSTANT)	//Calibration pacekt이 아닌경우.
//		return;
	
	int name_len=0;
	memcpy(&name_len, m_pBuf+8, 4);
	if(param_name)
		delete [] param_name;
	param_name = new char[name_len+1];
	memset(param_name, 0, name_len+1);

	memcpy(param_name, m_pBuf+12, name_len);

	if( (!strcmp(param_name, PARAM_NAME_MODEL)) || 
		(!strcmp(param_name, PARAM_NAME_LOT_NUMBER)) || 
		(!strcmp(param_name, PARAM_NAME_UPDATE)) )
	{
		int val_len;
		memcpy(&val_len, m_pBuf+12+name_len, 4);
		if(str_val)
			delete [] str_val;
		str_val = new char[val_len+1];
		memset(str_val, 0, val_len+1);

		memcpy(str_val, m_pBuf+16+name_len, val_len);
	}
	else
		memcpy(&val, m_pBuf+12+name_len, 8);
	//-----------------------------------------------

//	delete [] param_name;

}

//DEL void CPacket::Decoding(int nPort,unsigned char* pData)
//DEL {
//DEL 	//2.  수신 데이터를 포맷화된 패킷으로 디코딩. 
//DEL 	CString string;
//DEL 	int defect_cnt=0;
//DEL 	int frame_num=0;
//DEL 	int nDataLen;
//DEL 
//DEL 	memcpy(&nDataLen,pData,4);
//DEL 	int		nCode	= GetCode((char*)pData+4, 4);
//DEL 
//DEL 	switch(nCode){
//DEL 	case NM_DATA:
//DEL 		{
//DEL 			PullDataPacket((char*)pData, nDataLen, nCode, frame_num, defect_cnt);
//DEL 			break;
//DEL 		}
//DEL 	}
//DEL }
