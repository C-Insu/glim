// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__D49DDD7D_8A71_47C7_97E8_938E7B1C8E30__INCLUDED_)
#define AFX_STDAFX_H__D49DDD7D_8A71_47C7_97E8_938E7B1C8E30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

//#define PYLON_2_2

//#define TEST_MODE

//extern int  g_PROGRAM;		//0이면 기존프로그램   1이면  Area Slit검사 
//#include "ScoutGrabber.h"
#include <gdiplus.h>

#include "global.h"


//#include <afxsock.h>
#include <afxcmn.h>			// MFC support for Windows Common Controls
#include <afxmt.h>
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
extern CMutex g_Mutex;


#endif // !defined(AFX_STDAFX_H__D49DDD7D_8A71_47C7_97E8_938E7B1C8E30__INCLUDED_)
