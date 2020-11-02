#if !defined(AFX_DLGSETTING_H__1BF6E6E9_12E7_4C1B_8E95_E78204839A42__INCLUDED_)
#define AFX_DLGSETTING_H__1BF6E6E9_12E7_4C1B_8E95_E78204839A42__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSetting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSetting dialog

class CDlgSetting : public CDialog
{
// Construction
public:
	CDlgSetting(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSetting)
	enum { IDD = IDD_DIALOG_SET };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSetting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSetting)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETTING_H__1BF6E6E9_12E7_4C1B_8E95_E78204839A42__INCLUDED_)
