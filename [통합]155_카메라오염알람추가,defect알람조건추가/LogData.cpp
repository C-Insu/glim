// LogData.cpp: implementation of the CLogData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LogData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogData::CLogData(CString strFile)
{
	CString str;
	CStdioFile file;

	m_strLogFile = strFile+ComputerName()+".txt";//"c:\\nexteye\\GrabLog.txt";

	try{
		if (!file.Open(m_strLogFile, CFile::modeWrite|CFile::typeText)) 	
		{
			if(!file.Open(m_strLogFile, CFile::modeWrite|CFile::typeText|CFile::modeCreate))
				return;	//File Create Error
		}

	
		file.Close();
	}
	catch(CFileException)
	{
		//AfxMessageBox( "File Open failed" );
		//file.Close();
	}
	catch(...)
	{
		//AfxMessageBox( "File Open failed2~" );
	}

	m_bWriteLog	 = TRUE;
	m_bWriteTime = TRUE;
}

CLogData::~CLogData()
{

}

void CLogData::SetSeparator()
{
	Write("\n");
}

void CLogData::WriteLog(CString str)
{
	Write(str);
}

void CLogData::WriteLog(CString str, int nNum)
{
	CString strWrite;
	strWrite.Format(str, nNum);
	Write(strWrite);
}

void CLogData::WriteLog(CString str, double dData)
{
	CString strWrite;
	strWrite.Format(str, dData);
	Write(strWrite);
}

void CLogData::WriteLog(CString str, CString strData)
{
	CString strWrite;
	strWrite.Format(str, strData);
	Write(strWrite);
}

void CLogData::Write(CString str)
{
	if(!m_bWriteLog)	return;

	CStdioFile file;
	try{
		if(!file.Open(m_strLogFile, CFile::modeWrite|CFile::typeText)) 
			return;	
	}

	catch(CFileException)
	{
		//AfxMessageBox( "File Open failed" );
	}
	catch(...)
	{
		//AfxMessageBox( "File Open failed2~" );
	}

	if(m_bWriteTime){
		
		CTime time = CTime::GetCurrentTime();
		CString strTime = time.Format("[%Y %m %d %H:%M:%S]\t");	//2006 11 27 18:34:26 
		str.Format("\n%s%s", strTime, str);
	}else{
		str.Format("\n%s", str);
	}

	file.SeekToEnd();
	file.WriteString(str);
	file.Close();
}

CString CLogData::ComputerName()
{
	TCHAR szComputerName[MAX_COMPUTERNAME_LENGTH + 1] = "\0" ;
	DWORD dwSize = MAX_COMPUTERNAME_LENGTH + 1 ;
	GetComputerName( szComputerName, &dwSize ) ;

	CString str;
	str.Format("[%s]", &szComputerName);
	return str;
}
