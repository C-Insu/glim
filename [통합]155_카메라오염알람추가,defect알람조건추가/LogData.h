// LogData.h: interface for the CLogData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGDATA_H__7D4F5FD5_D6E4_4A53_A151_1C15AC1936D4__INCLUDED_)
#define AFX_LOGDATA_H__7D4F5FD5_D6E4_4A53_A151_1C15AC1936D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLogData  
{
public:
	CLogData(CString strFile);
	virtual ~CLogData();

	void SetLogWriteEnable(BOOL bFlag)				{m_bWriteLog = bFlag;}
	void SetTimeWirteEnable(BOOL bFlag)				{m_bWriteTime = bFlag;}

	void WriteLog(CString str);
	void WriteLog(CString str, int nNum);
	void WriteLog(CString str, double dData);
	void WriteLog(CString str, CString strData);
	void SetSeparator();

private:
	BOOL	m_bWriteLog;	
	BOOL	m_bWriteTime;
	CString m_strLogFile;

	void Write(CString str);
	CString ComputerName();
};

#endif // !defined(AFX_LOGDATA_H__7D4F5FD5_D6E4_4A53_A151_1C15AC1936D4__INCLUDED_)
