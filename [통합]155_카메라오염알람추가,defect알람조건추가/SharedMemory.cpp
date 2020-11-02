#include "StdAfx.h"
#include "SharedMemory.h"

CSharedMemory::CSharedMemory(void)
{
	m_handle = NULL;
	m_pMemoryAddress = NULL;
}

CSharedMemory::~CSharedMemory(void)
{
}

BOOL CSharedMemory::Open(CString strMemoryName, int nSizeByte)
{
	BOOL bGetHandle = FALSE;

	m_handle = OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, strMemoryName);

	if(m_handle != NULL){
		bGetHandle = TRUE;
		//TRACE(_T("[Open] SharedMemory exist already\n"));
	}
	else{
		m_handle = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, nSizeByte, strMemoryName);

		if(m_handle != NULL){
			bGetHandle = TRUE;
			//TRACE(_T("[Open] SharedMemory Created\n"));
		}
		else{
			bGetHandle = FALSE;
			//TRACE(_T("[Open] SharedMemory Creation Failed\n"));
		}
	}

	BOOL bRet = FALSE;
	if(bGetHandle){
		bRet = GetMemoryAddress(nSizeByte);
	}

	return bRet;
}

void CSharedMemory::Close(void)
{
	if(m_pMemoryAddress){
		if( UnmapViewOfFile(m_pMemoryAddress) != 0 ){
			//TRACE(_T("[Close] SharedMemory Closed\n"));
			m_pMemoryAddress = NULL;
		}
	}

	if(m_handle)
		CloseHandle(m_handle);
}

BOOL CSharedMemory::GetMemoryAddress(int nSizeByte)
{
	if(m_pMemoryAddress != NULL)
		return TRUE;

	m_pMemoryAddress = MapViewOfFile(m_handle, FILE_MAP_ALL_ACCESS, 0, 0, nSizeByte); // 4byte(32bit)

	if(m_pMemoryAddress != NULL){
		//TRACE(_T("[GetMemoryAddress] Got the address\n"));
		return TRUE;
	}
	else{
		//TRACE(_T("[GetMemoryAddress] Lost the address\n"));
		return FALSE;
	}
}

LPVOID CSharedMemory::GetData()
{
	LPVOID nData = NULL;

	if(m_pMemoryAddress != NULL) {
		nData = m_pMemoryAddress;
	}

	return nData;
}

void CSharedMemory::SetData(int nData)
{
	if(m_pMemoryAddress != NULL) {
		memmove_s(m_pMemoryAddress, sizeof(int), &nData, sizeof(int));
	}
}

void CSharedMemory::SetData(double dData)
{
	if(m_pMemoryAddress != NULL) {
		memmove_s(m_pMemoryAddress, sizeof(double), &dData, sizeof(double));
	}
}

void CSharedMemory::SetData(CString strData)
{
	if(m_pMemoryAddress != NULL) {
		strcpy((char*)m_pMemoryAddress, (CT2A)strData);
	}
}

void CSharedMemory::SetData( unsigned int uiData )
{
	if(m_pMemoryAddress != NULL) {
		memmove_s(m_pMemoryAddress, sizeof(unsigned int), &uiData, sizeof(unsigned int));
	}
}
