// VisWeb.h : main header file for the VISWEB application
//

#if !defined(AFX_VISWEB_H__5CA14EEE_2808_4CF1_BD44_9024543941FE__INCLUDED_)
#define AFX_VISWEB_H__5CA14EEE_2808_4CF1_BD44_9024543941FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "TimingProcess.h"	// Added by ClassView
//#include "Log/log4cpp.h"
#include <Afxmt.h>

/////////////////////////////////////////////////////////////////////////////
// CVisWebApp:
// See VisWeb.cpp for the implementation of this class
//

class CVisWebApp : public CWinApp
{
public:
	CTimingProcess *m_pTiming;

	//log4cpp::Appender* syslogAppender;
	//log4cpp::Category& logCppLog;

	CVisWebApp();
	ULONG_PTR m_gdiplusToken;


	//CMutex g_Mutex;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVisWebApp)
	public:
	bool m_debugLogWrite;
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	void CVisWebApp::WriteLog(CString path, CString fileName, CString strdata);
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CVisWebApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISWEB_H__5CA14EEE_2808_4CF1_BD44_9024543941FE__INCLUDED_)
