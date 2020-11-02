// FileMove1.cpp : implementation file
//

#include "stdafx.h"
#include "VisWeb.h"
#include "FileMove1.h"
#include "systemclock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CSemaphore	g_sema;
/////////////////////////////////////////////////////////////////////////////
// CFileMove
UINT ThreadCheckFolder(LPVOID lParam)
{
	CFileMove *pView = (CFileMove *)lParam;	

	double stTime = Clock_set();
	int nCountPerSec = 0;	
	BOOL bCheckFolder = FALSE;

	while(pView->m_bRun)
	{		
		if(pView->m_bAuto)
		{
			Sleep(pView->m_nCheckTime);	//chcho
//			if(double(Clock_set()-stTime) > (double)(pView->m_nCheckTime))
			{
				//Check Folder
				bCheckFolder = pView->CheckFolder(1);

				if(bCheckFolder)
				{
					//Move Folder
//					pView->m_eMoveFolder.SetEvent();
					//WaitForSingleObject((HANDLE)pView->m_eCheckFolder, INFINITE);
					while(WaitForSingleObject((HANDLE)pView->m_eCheckFolder, 500) != WAIT_TIMEOUT )
					{
					//Wait Move Complite
//						pView->m_eCheckFolder.ResetEvent();
					}
				}

				stTime = Clock_set();				
			}
			Sleep(10);
		}
		Sleep(10);
	}
	return 1;
}

UINT ThreadMoveFolder(LPVOID lParam)
{
	CFileMove *pView = (CFileMove *)lParam;	

	while(pView->m_bRun)
	{		
		if(pView->m_bAuto)
		{
			//Wait Move Event
			//WaitForSingleObject((HANDLE)pView->m_eMoveFolder, INFINITE);
			while(WaitForSingleObject((HANDLE)pView->m_eMoveFolder, 500) != WAIT_TIMEOUT )
			{
//				pView->m_eMoveFolder.ResetEvent();
			//Move Folder
			g_sema.Lock();	//chcho
//				pView->MoveFolder();	
//				pView->DeleteFolder();
			g_sema.Unlock();
			//Complite Desk
//				pView->m_eCheckFolder.SetEvent();
			}
		}
		Sleep(10);
	}
	return 1;
}

CFileMove::CFileMove()
{
	m_nCheckTime = 1000;

//	m_bRun	= FALSE;
	m_bAuto	= FALSE;

	m_bInitClass = FALSE;

	m_pThreadCheckFolder= NULL;
	m_pThreadMoveFolder	= NULL;

	m_strSrcFolder = "C:\\Glim\\LOTdata\\";
//\\FILESERVER\NEXTEYE\CTRL_SERVER\LOT_DATA_IMG\\lotname\Pc_name\frame수(1000단위)\이미지명.bmp
	m_strDstFolder = "\\FILESERVER\\INSP_DATA\\CTRL_SERVER\\LOT_DATA_IMG\\lotname\\";//\Pc_name\frame수(1000단위)\이미지명.bmp";	
//	m_strDstFolder = "Z:\\";	
}

CFileMove::~CFileMove()
{
//	m_bRun = FALSE;
	m_bAuto= FALSE;	
}


BEGIN_MESSAGE_MAP(CFileMove, CWnd)
	//{{AFX_MSG_MAP(CFileMove)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CFileMove message handlers

void CFileMove::InitClass(CString Src, CString Dst, int nCheckTime)
{
	m_bInitClass = TRUE;
	
	m_strSrcFolder = Src;
	m_strDstFolder = Dst;

	m_nCheckTime = nCheckTime;
}

void CFileMove::RunMoveProgram()
{
	
	m_bRun = TRUE;
	m_bAuto= TRUE;

	//Create Thread
// 	AfxBeginThread(ThreadCheckFolder, this,THREAD_PRIORITY_NORMAL,0);
// 	AfxBeginThread(ThreadMoveFolder, this,THREAD_PRIORITY_NORMAL,0);		
}

void CFileMove::StopMoveProgram()
{
//	m_bRun = FALSE;
//	m_bAuto= FALSE;

	m_pThreadCheckFolder	= NULL;
	m_pThreadMoveFolder		= NULL;
}

BOOL CFileMove::CheckFolder(int nFolder)
{
	CFileFind cfile;
	BOOL b;
	int filecnt=0;
	CString fileName;
	CString folder;

	CTime	time=0,fsttime=0;

	folder = m_strSrcFolder;
	folder += "*.*";

	b = cfile.FindFile(folder);

	if(!b)	return FALSE;

	while(b)
	{
		b = cfile.FindNextFile();

		if (cfile.IsDots())  continue;
		if (cfile.IsDirectory())
		{
			filecnt++;

//			if(filecnt == 1)
//				fileName=cfile.GetFileName();

			cfile.GetCreationTime(time);

			if(fsttime == 0)
			{
				fileName=cfile.GetFileName();
				fsttime = time;
			}
			
			if( fsttime > time)
			{
				fileName= cfile.GetFileName();
				fsttime = time;
			}

			continue;
		}
	}

	if(filecnt > nFolder)
	//if(filecnt == nFolder)	//chcho
	{
		m_strMoveFolder = fileName;
		return  TRUE;
	}
	else
		return  FALSE;
}

void CFileMove::MoveFolder()
{	
	CString SrcFolder;
	CString DstFolder;
	CString Command;

	BOOL bRet;

	SrcFolder.Format("%s%s\\*.*",m_strSrcFolder,m_strMoveFolder);	
	//c:\nexteye\lotdata\dummy\*.*  ->    dummy         ;
	DstFolder.Format("%s%s",m_strDstFolder,m_strMoveFolder);
	//100.0.0.201\nexteye\image\dummy\*.*  ->    dummy         ;
	Command.Format("md %s",DstFolder);

	system(Command);

	Command.Format("move %s %s\\",SrcFolder,DstFolder);

	system(Command);

	SrcFolder.Format("%s%s",m_strSrcFolder,m_strMoveFolder);

	bRet = RemoveDirectory(SrcFolder);	
}

void CFileMove::DeleteFolder()
{	
	CString SrcFolder;
	CString Command;
	CString str;

	SrcFolder.Format("c:\\Glim\\lotdata");

	Command.Format("del /s /q %s\\*.*",SrcFolder);
	system(Command);

	str.Format("rd /s /q %s",SrcFolder);
	system(str);

	str.Format("c:\\necteye\\LotData\\");
	CreateDirectory(str,NULL);
	
}