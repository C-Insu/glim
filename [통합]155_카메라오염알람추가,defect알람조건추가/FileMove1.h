#if !defined(AFX_FILEMOVE_H__806C449D_F100_41C5_99AD_DFA535A57311__INCLUDED_)
#define AFX_FILEMOVE_H__806C449D_F100_41C5_99AD_DFA535A57311__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileMove1.h : header file
//
#include <Afxmt.h>

/////////////////////////////////////////////////////////////////////////////
// CFileMove window

class CFileMove : public CWnd
{
// Construction
public:
	CFileMove();

// Attributes
public:
	CWinThread	*m_pThreadCheckFolder;
	CWinThread	*m_pThreadMoveFolder;

	int		m_nCheckTime;

	BOOL	m_bRun;
	BOOL	m_bAuto;
	BOOL	m_bInitClass;

	CString m_strSrcFolder;
	CString m_strDstFolder;	
	CString m_strMoveFolder;

	CEvent	m_eCheckFolder;
	CEvent	m_eMoveFolder;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileMove)
	//}}AFX_VIRTUAL

// Implementation
public:		
	void InitClass(CString Src,CString Dst,int nCheckTime=1000);	//Setting Src 소스폴더,Dst 타겟폴더,nCheckTime 체크시간
	void MoveFolder();												//Folder Move
	void StopMoveProgram();											//Folder Move Stop
	void RunMoveProgram();											//Folder Move Start

	BOOL CheckFolder(int nFolder);									//Cheack Folder
	void DeleteFolder();


	virtual ~CFileMove();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFileMove)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEMOVE_H__806C449D_F100_41C5_99AD_DFA535A57311__INCLUDED_)
