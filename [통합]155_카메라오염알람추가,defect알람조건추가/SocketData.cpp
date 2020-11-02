// Data.cpp : implementation file
//

#include "stdafx.h"
#include "Network.h"
#include "SocketData.h"
#include "assert.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSocketData

CSocketData::CSocketData()
{
	m_Streamsize = 0;
	m_Stream = NULL;
}

CSocketData::~CSocketData()
{
	if(m_Stream)
	{
		delete [] m_Stream;
		m_Stream = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSocketData member functions

void CSocketData::Serialize(CArchive &ar)
{
	// 네트워크로 송신
	if(ar.IsStoring())
	{
		ar.SetStoreParams();

//		ar.Write(m_Stream, m_Streamsize);

		for(int i=0; i<m_Streamsize; i++)
			ar << m_Stream[i];
	}
	// 네트워크에서 수신
	else
	{
		ar.SetLoadParams();
		//------------------------------------------------------------------------
		// 최초 4바이트 데이터를 읽어서 전체의 데이터의 길이를 구하고 한번에 읽어 들이는 방법
		DWORD dword;
		ar >> dword;		//<-- 어떤 문제에 의해 이 값이 너무 큰 값이 읽혀 지면, 메모리를 overflow 발생.

		if(m_Stream)
			delete [] m_Stream;
		m_Streamsize = dword-4;
		m_Stream = new BYTE[m_Streamsize];
		ar.Read((char*)m_Stream, m_Streamsize);

		//------------------------------------------------------------------------
		//	아래부분은 널문자를 단위 구분자로 사용하여 임의의 길이를 수신하는 방법
		/*
		int cnt=0;
		BYTE	byte;

		while(1)
		{
			ar >> byte;

			if(!byte)
				break;

			// if overflow occur
			if(m_Streamsize <= cnt)
			{
				BYTE* temp = new BYTE[m_Streamsize];
				memcpy(temp, m_Stream, m_Streamsize);

				delete [] m_Stream;
				m_Stream = new BYTE[m_Streamsize+OVERFLOW_EXTENSION];
				memset(m_Stream, 0, m_Streamsize+OVERFLOW_EXTENSION);

				memcpy(m_Stream, temp, m_Streamsize);
				m_Streamsize += OVERFLOW_EXTENSION;

				delete [] temp;				
			}
			m_Stream[cnt] = byte;
			
			cnt ++;
		}
		m_nByteRead = cnt;
		*/
	}
}

void CSocketData::SetStream(char *buf, int buf_len)
{
	if(m_Stream)
	{
		delete [] m_Stream;
		m_Stream = NULL;
		m_Streamsize = 0;
	}

	m_Streamsize = buf_len;
	m_Stream = new BYTE[buf_len];

	memcpy(m_Stream, buf, buf_len);
}
