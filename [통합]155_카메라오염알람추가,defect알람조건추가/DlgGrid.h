#if !defined(AFX_DLGGRID_H__5FBE9AE9_718F_4C0C_95D5_CCA34FAD9F9A__INCLUDED_)
#define AFX_DLGGRID_H__5FBE9AE9_718F_4C0C_95D5_CCA34FAD9F9A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGrid.h : header file
//
#include "GridCtrl2/GridCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgGrid dialog

class CDlgGrid : public CDialog
{
	class CGridEx : public CGridCtrl
	{
		// Override this function to fill InPlaceListBoxes
		void FillListItems(int nCol, LPARAM cltList);
	};
// Construction
public:
	void UpdateGrid(BOOL bToGrid=TRUE);
	CDlgGrid(CWnd* pParent = NULL);   // standard constructor
	CWnd *m_pParent;

// Dialog Data
	//{{AFX_DATA(CDlgGrid)
	enum { IDD = IDD_DLG_GRID };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	CGridEx m_Grid;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgGrid)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgGrid)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	afx_msg LRESULT OnUMGridClick(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUMGridEndEdit(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGRID_H__5FBE9AE9_718F_4C0C_95D5_CCA34FAD9F9A__INCLUDED_)
