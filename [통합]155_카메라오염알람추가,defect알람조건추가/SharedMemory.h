#pragma once

class CSharedMemory
{
private:
	HANDLE	m_handle;
	LPVOID	m_pMemoryAddress;
	BOOL GetMemoryAddress(int nSizeByte);

public:
	CSharedMemory(void);
	~CSharedMemory(void);
	BOOL	Open(CString strMemoryName, int nSizeByte);
	void	Close(void);
	void	SetData(int nData);
	void	SetData(double dData);
	void	SetData(CString strData);
	void	SetData(unsigned int uiData);
	LPVOID	GetData();
};
