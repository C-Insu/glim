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
	// ��Ʈ��ũ�� �۽�
	if(ar.IsStoring())
	{
		ar.SetStoreParams();

//		ar.Write(m_Stream, m_Streamsize);

		for(int i=0; i<m_Streamsize; i++)
			ar << m_Stream[i];
	}
	// ��Ʈ��ũ���� ����
	else
	{
		ar.SetLoadParams();
		//------------------------------------------------------------------------
		// ���� 4����Ʈ �����͸� �о ��ü�� �������� ���̸� ���ϰ� �ѹ��� �о� ���̴� ���
		DWORD dword;
		ar >> dword;		//<-- � ������ ���� �� ���� �ʹ� ū ���� ���� ����, �޸𸮸� overflow �߻�.

		if(m_Stream)
			delete [] m_Stream;
		m_Streamsize = dword-4;
		m_Stream = new BYTE[m_Streamsize];
		ar.Read((char*)m_Stream, m_Streamsize);

		//------------------------------------------------------------------------
		//	�Ʒ��κ��� �ι��ڸ� ���� �����ڷ� ����Ͽ� ������ ���̸� �����ϴ� ���
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
