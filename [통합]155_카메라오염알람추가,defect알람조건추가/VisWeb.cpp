// VisWeb.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "VisWeb.h"

#include "MainFrm.h"
#include "VisWebDoc.h"
#include "VisWebView.h"
#include "ini.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVisWebApp
//int  g_PROGRAM=0;		//0이면 기존프로그램   1이면  Area Slit검사 

BEGIN_MESSAGE_MAP(CVisWebApp, CWinApp)
	//{{AFX_MSG_MAP(CVisWebApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVisWebApp construction

CVisWebApp::CVisWebApp()
//: logCppLog(log4cpp::Category::getRoot())
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CVisWebApp object

CVisWebApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CVisWebApp initialization

BOOL CVisWebApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	static const char szProgName[] = "MyProgram";

	CreateMutex(NULL, TRUE, szProgName);
	if( GetLastError() == ERROR_ALREADY_EXISTS) 
	{
//		AfxMessageBox("MyProgram이 이미 실행중 입니다");
		//Write log
		return FALSE;
	}

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CVisWebDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CVisWebView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);	
	m_pMainWnd->UpdateWindow();

	TCHAR szComputerName[MAX_COMPUTERNAME_LENGTH + 1] = "\0" ;
	DWORD dwSize = MAX_COMPUTERNAME_LENGTH + 1 ;
	GetComputerName( szComputerName, &dwSize ) ;
	CString str;
	str.Format("Web Inspection System - COATER Vision ▒▒▒▶ Glim Co.,Ltd ◀▒▒▒ Sleep Ver. 2020-10-27 0.0.155. %s", &szComputerName);

	m_pMainWnd->SetWindowText(str);

	m_pTiming = new CTimingProcess;
	m_pTiming->initialize_timer(Clock_set, Clock_set);

	float m_debugLogWriteEnable = 0;

	CIni ini1( PARAMETER_PATH1, "Control Parameter" );
	ini1.SER_GETD(TRUE, m_debugLogWriteEnable					, 0);

	m_debugLogWrite = m_debugLogWriteEnable;	//디버그 로그 기록 유무

	if(((CVisWebApp*)AfxGetApp())->m_debugLogWrite == TRUE){
		WriteLog(PATH_DEBUG_LOG, "debug_log", "\nProgram-Start");
	}

	return TRUE;
}

void CVisWebApp::WriteLog(CString path, CString fileName, CString strdata)
{

	CStdioFile   file;
	CString filename;
	CString strpath;
	CString str;

	strpath.Format(path);
	CreateDirectory(strpath,NULL);	

	CTime time = CTime::GetCurrentTime();
	CString strTime = time.Format("%Y%m%d");

	filename.Format("%s%s_%s.txt",strpath, strTime, fileName);

	try{
		g_Mutex.Lock();                    // 뮤텍스를 잠근다.

		if(!file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
		{		
			file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText);
			file.WriteString(strdata);
			file.WriteString("\n");	
			file.Close();
		}
		else
		{
			file.SeekToEnd();			
			file.WriteString(strdata);
			file.WriteString("\n");
			file.Close(); 
		}	
		g_Mutex.Unlock();                 // 뮤텍스를 풀어준다.
	}
	catch(...){
		WriteLog("D:\\LOG\\", "logError", "******Write Fail******");
	}
}




// App command to run the dialog
void CVisWebApp::OnAppAbout()
{
}

/////////////////////////////////////////////////////////////////////////////
// CVisWebApp message handlers

int CVisWebApp::ExitInstance() 
{
	Gdiplus::GdiplusShutdown(m_gdiplusToken);

	delete m_pTiming;
	return CWinApp::ExitInstance();
}
