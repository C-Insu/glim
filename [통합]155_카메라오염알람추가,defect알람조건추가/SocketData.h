#if !defined(AFX_DATA_H__98BA7ABB_2D49_49AA_9F38_6BCB606E3839__INCLUDED_)
#define AFX_DATA_H__98BA7ABB_2D49_49AA_9F38_6BCB606E3839__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Data.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSocketData command target

const int OVERFLOW_EXTENSION = 1024;
class CSocketData : public CObject
{
// Attributes
public:

// Operations
public:
	void	SetStream(char* buf, int buf_len);
	
	CSocketData();
	virtual ~CSocketData();

	virtual void Serialize(CArchive &ar);

	BYTE*			m_Stream;
	int				m_Streamsize;
	int				m_nByteRead;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATA_H__98BA7ABB_2D49_49AA_9F38_6BCB606E3839__INCLUDED_)
