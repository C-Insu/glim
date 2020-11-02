// Disk_File.cpp

#include "Disk_File.h"
#include "Direct.h"

#define KILO	1024
void C_Drive_check(long &total, long &occupied, long &remaining)
{
	ULARGE_INTEGER lpFree;
	ULARGE_INTEGER lpTotal;
	ULARGE_INTEGER lpOccupied;

	double d_longtotal = 0;
	double d_longremaining = 0;
	double d_longoccupied = 0;

	GetDiskFreeSpaceEx("C:\\", &lpFree, &lpTotal, &lpOccupied);

	d_longremaining = ((double)lpFree.HighPart * UINT_MAX) + lpFree.LowPart; // 사용한 공간
	d_longtotal = ((double)lpTotal.HighPart * UINT_MAX) + lpTotal.LowPart; // 총 드라이브 크기
	d_longoccupied = d_longtotal - d_longremaining; // 사용한 공간

	// mega based
	occupied = (unsigned int)(d_longoccupied / (KILO*KILO));
	remaining = (unsigned int)(d_longremaining / (KILO*KILO));
	total = (unsigned int)(d_longtotal / (KILO*KILO));
}

void Nth_Drive_check(char Nth, long &total, long &occupied, long &remaining)
{
	ULARGE_INTEGER lpFree;
	ULARGE_INTEGER lpTotal;
	ULARGE_INTEGER lpOccupied;

	double d_longtotal = 0;
	double d_longremaining = 0;
	double d_longoccupied = 0;

	CString path;

	path = Nth;
	path +=":\\";
	GetDiskFreeSpaceEx((LPCSTR)path, &lpFree, &lpTotal, &lpOccupied);

	d_longremaining = ((double)lpFree.HighPart * UINT_MAX) + lpFree.LowPart; // 사용한 공간
	d_longtotal = ((double)lpTotal.HighPart * UINT_MAX) + lpTotal.LowPart; // 총 드라이브 크기
	d_longoccupied = d_longtotal - d_longremaining; // 사용한 공간

	// mega based
	occupied = (unsigned int)(d_longoccupied / (KILO*KILO));
	remaining = (unsigned int)(d_longremaining / (KILO*KILO));
	total = (unsigned int)(d_longtotal / (KILO*KILO));
}

void Delete_All_in_Folder(CString path)
{
	CString file;
	
	HANDLE hFind;				// FindFirstFile 핸들
	WIN32_FIND_DATA	fd;			// 검색한 화일의 정보
	BOOL bRet = TRUE;
	CString strfile, First_File("*.*");

	CString transient;
	char temp[100];
	::GetCurrentDirectory(100, temp);
	::SetCurrentDirectory((LPCSTR)path);

	hFind = FindFirstFile(First_File, &fd);
	while(hFind != INVALID_HANDLE_VALUE && bRet)
	{			
		strfile = fd.cFileName;

		if( !(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )		// Not directory, which means file.
			::DeleteFile((LPCSTR)(path+"\\"+strfile));
		else if( strfile == "." || strfile == "..")
			;
		else	// it is directory
		{
			transient = path+"\\"+strfile;
			Delete_All_in_Folder(transient);
			RemoveDirectory((LPCSTR)transient);
		}
		bRet= FindNextFile(hFind, &fd);
	}
	::SetCurrentDirectory(temp);

	::FindClose(hFind);
}

void Delete_Folder(CString path)
{
	CString folder_path = path;
	char temp[100];
	::GetCurrentDirectory(100, temp);

	// Set to designated drive
	int cur_drive = _getdrive();
	int target_drive = path[0]-'A'+1;

	if( target_drive != cur_drive )
		_chdrive(target_drive);

	// Set to just prior directory
	::_chdir((LPCSTR)folder_path);
	::system("cd ..");	

	Delete_All_in_Folder(folder_path);
	
	int ret = ::_rmdir((LPCSTR)folder_path);
	if(ret)
		AfxMessageBox("Directory is not empty");

	_chdrive(cur_drive);
	::SetCurrentDirectory((LPCSTR)temp);
}