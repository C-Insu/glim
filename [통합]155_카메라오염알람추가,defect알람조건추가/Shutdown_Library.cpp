#include "stdafx.h"

int ShutDownSystem(BOOL bReboot)
{
	// 95, 98 에서만 동작..
	BOOL bRes;

	if(bReboot)
	{
		bRes = ::ExitWindowsEx(EWX_SHUTDOWN | EWX_REBOOT,0);
	}
	else
		bRes = ::ExitWindowsEx(EWX_POWEROFF, NULL);

	return 0;
}


int ShutDownNT(BOOL bReStart)
{
	HANDLE hToken;              // handle to process token 
	TOKEN_PRIVILEGES tkp;       // pointer to token structure 
	
	BOOL fResult;               // system shutdown flag 
	
	// Get the current process token handle so we can get shutdown 
	// privilege. 
	
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
	{
		//AfxMessageBox("OpenProcessToken failed."); 
		TRACE("OpenProcessToken failed.\n");
	}
	
	// Get the LUID for shutdown privilege. 
	
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid); 
	
	tkp.PrivilegeCount = 1;  // one privilege to set    
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
	
	// Get shutdown privilege for this process. 
	
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, 
		(PTOKEN_PRIVILEGES) NULL, 0); 
	
	// Cannot test the return value of AdjustTokenPrivileges. 
	
	if (GetLastError() != ERROR_SUCCESS) 
	{
		//AfxMessageBox("AdjustTokenPrivileges enable failed."); 
		TRACE("AdjustTokenPrivileges enable failed.\n");
	}
	
	// Display the shutdown dialog box and start the time-out countdown. 
	
	fResult = InitiateSystemShutdown( 
		"Snoqualmie"	                // shut down local computer 
		, "System rebooting."   // message to user 
		, 0                     // time-out period (<- 여기를 20 이라고 쓰면 20초 후에 리부팅한다.)
		, FALSE                 // ask user to close apps 
		, bReStart);            // reboot after shutdown 
	
	if (!fResult) 
	{ 
		//AfxMessageBox("InitiateSystemShutdown failed."); 
		TRACE("InitiateSystemShutdown failed.\n");
	} 
	
	// error string..
	//PrintCSBackupAPIErrorMessage(GetLastError());
	
	// Disable shutdown privilege. 
	
	tkp.Privileges[0].Attributes = 0; 
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES) NULL, 0); 
	
	if(GetLastError() != ERROR_SUCCESS) 
	{
		//AfxMessageBox("AdjustTokenPrivileges disable failed."); 
		TRACE("AdjustTokenPrivileges disable failed.");
	} 
	return 0;
}

BOOL WinNTSystemPowerOff(int nWaitTime, BOOL bReStart)
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tp;
	LUID luid;
	
	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
	LookupPrivilegeValue(NULL,"SeShutdownPrivilege",&luid);
	
	tp.PrivilegeCount = 1;
	tp.Privileges[0].Luid = luid;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	
	AdjustTokenPrivileges(hToken, FALSE, &tp, 0, NULL, NULL);
	
	BOOL bRes = InitiateSystemShutdown(NULL, NULL, nWaitTime, FALSE, bReStart);
	DWORD dwError = ::GetLastError();

	// ExitWindowsEx(EWX_SHUTDOWN | EWX_POWAEROFF,0);
	return bRes;
}

void WinNTSystemLogOff()
{
	ExitWindowsEx(EWX_LOGOFF, 0);
}

int IsOsNT()
{
	OSVERSIONINFO os;
	os.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&os);
	if (os.dwPlatformId == VER_PLATFORM_WIN32_NT)
	{
		return 1;
	}
	else if (os.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}