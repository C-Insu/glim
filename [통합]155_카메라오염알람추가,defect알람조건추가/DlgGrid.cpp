// DlgGrid.cpp : implementation file
//

#include "stdafx.h"
#include "VisWeb.h"
#include "DlgGrid.h"

#include "VisWebDoc.h"
#include "VisWebView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgGrid dialog


CDlgGrid::CDlgGrid(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGrid::IDD, pParent)
{
	m_pParent = pParent;
	//{{AFX_DATA_INIT(CDlgGrid)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgGrid::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgGrid)
		DDX_Control(pDX, IDC_GRID, m_Grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgGrid, CDialog)
	//{{AFX_MSG_MAP(CDlgGrid)
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_GRID_EDIT_END, &CDlgGrid::OnUMGridEndEdit)
	ON_MESSAGE(UM_GRID_CLICK, &CDlgGrid::OnUMGridClick)

END_MESSAGE_MAP()

#define GRID_COL_NO			0
#define GRID_COL_AVE		1
#define GRID_COL_TH_UP		2
#define GRID_COL_MAX_V		3
#define GRID_COL_TH_DN		4
#define GRID_COL_MIN_V		5
#define GRID_COL_SIZE_X		6
#define GRID_COL_SIZE_Y		7
#define GRID_COL_TYPE		8

/////////////////////////////////////////////////////////////////////////////
// CDlgGrid message handlers

void CDlgGrid::CGridEx::FillListItems(int nCol, LPARAM cltList)
{
	CListBox*	pList = (CListBox*)cltList;
	if (nCol == 2)
	{
		pList->AddString("Yes");
		pList->AddString("No");
		pList->AddString("Cancel");
		pList->AddString("Abort");
		pList->AddString("Retry");
		pList->AddString("Accept");
	}
	else if (nCol == 3)
	{
		pList->AddString("AAA");
		pList->AddString("BBB");
		pList->AddString("CCC");
		pList->AddString("DDD");
		pList->AddString("EEE");
		pList->AddString("FFF");
		pList->AddString("GGG");
		pList->AddString("HHH");
		pList->AddString("III");
	}
}

BOOL CDlgGrid::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	m_Grid.SetEditable(TRUE);
	m_Grid.SetListMode(TRUE);
	m_Grid.EnableDragAndDrop(TRUE);
	m_Grid.SetTextBkColor(RGB(0xFF, 0xFF, 0xE0));
	

	try {
		m_Grid.SetRowCount(MAX_DEFECT+1);
		m_Grid.SetColumnCount(9);
		m_Grid.SetFixedRowCount(1);
		m_Grid.SetFixedColumnCount(1);
	}
	catch (CMemoryException* e)
	{
		e->ReportError();
		e->Delete();
		return FALSE;
	}

	// fill rows/cols with text
	//BOOL SetColumnType(int nCol, int nType);
	for (int row = 0; row < MAX_DEFECT+1; row++)
		for (int col = 0; col < 9; col++)
		{ 
			m_Grid.SetRowHeight(row, 30);
			m_Grid.SetColumnWidth(col, 50);
			GV_ITEM Item;
			Item.mask = GVIF_TEXT|GVIF_FORMAT;
			Item.row = row;
			Item.col = col;

			if (row < 1) {
				Item.nFormat = DT_LEFT|DT_VCENTER|DT_CENTER|DT_SINGLELINE|DT_WORDBREAK;
				/*m_Grid.SetColumnType(col, GVET_NOEDIT,GVET_LISTBOX,GVET_EDITBOX);*/
				if (col==GRID_COL_NO) {
//					m_Grid.SetColumnType(col, GVET_NOEDIT);
					Item.strText = "No";
				}else if (col==GRID_COL_AVE) {
//					m_Grid.SetColumnType(col, GVET_NOEDIT);
					Item.strText = "AVE";
				}else if (col==GRID_COL_TH_UP) {
//					m_Grid.SetColumnType(col, GVET_EDITBOX);
					Item.strText = "ThUp";
				}else if (col==GRID_COL_MAX_V) {
//					m_Grid.SetColumnType(col, GVET_NOEDIT);
					Item.strText = "MaxV";
				}else if (col==GRID_COL_TH_DN) {
//					m_Grid.SetColumnType(col, GVET_EDITBOX);
					Item.strText = "ThDn";
				}else if (col==GRID_COL_MIN_V) {
//					m_Grid.SetColumnType(col, GVET_NOEDIT);
					Item.strText = "MinV";
				}else if (col==GRID_COL_SIZE_X) {
//					m_Grid.SetColumnType(col, GVET_NOEDIT);
					Item.strText = "SizeX";
				}else if (col==GRID_COL_SIZE_Y) {
//					m_Grid.SetColumnType(col, GVET_NOEDIT);
					Item.strText = "SizeY";
				}else if (col==GRID_COL_TYPE) {
//					m_Grid.SetColumnType(col, GVET_EDITBOX);
					Item.strText = "Std";
				}//m_dStdGap
			} else if (col < 1) {
				Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
				Item.strText.Format(_T("No %02d"),row);
			} else {
				Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
				if (col == 2)
					Item.strText.Format(_T("Yes"),row);
				else if (col == 3)
					Item.strText.Format(_T("BBB"),row);
				else
					Item.strText.Format(_T("%d"),row*col);
			}
			m_Grid.SetItem(&Item);

			if (col == (m_Grid.GetFixedColumnCount()-1) && row >= m_Grid.GetFixedRowCount())
				m_Grid.SetItemImage(row, col, row%2);
			//else if (rand() % 10 == 1)
			//	m_Grid.SetItemImage(row, col, 0);
		
		}

	//m_Grid.AutoSize();
//	m_Grid.SetRowHeight(0, 3*m_Grid.GetRowHeight(0)/2);

	m_Grid.SetHeaderSort(FALSE);
	m_Grid.SetColumnResize(FALSE);
	m_Grid.SetRowResize(FALSE);

	UpdateGrid();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgGrid::UpdateGrid(BOOL bToGrid)
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
//*
	int i;
	int nCam = 0;
	GV_ITEM Item;
	Item.mask = GVIF_TEXT|GVIF_FORMAT;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	if(bToGrid){
		Item.col = GRID_COL_AVE;
		for(i=0; i<MAX_DEFECT; i++){
			Item.row = i+1;
			Item.strText.Format("%d",int(pDoc->m_data.m_dAvgBrightness[nCam]));
			m_Grid.SetItem(&Item);
		}

		Item.col = GRID_COL_TH_UP;
		for(i=0; i<MAX_DEFECT; i++){
			Item.row = i+1;
			Item.strText.Format("%2.0f",pDoc->m_data.m_dThUp[nCam]);
			m_Grid.SetItem(&Item);
		}
		
		Item.col = GRID_COL_MAX_V;
		for(i=0; i<MAX_DEFECT; i++){
			Item.row = i+1;
			Item.strText.Format("%d",pDoc->m_data.m_nDefectVMax[nCam][i]);
			m_Grid.SetItem(&Item);
		}

		Item.col = GRID_COL_TH_DN;
		for(i=0; i<MAX_DEFECT; i++){
			Item.row = i+1;
			Item.strText.Format("%2.0f",pDoc->m_data.m_dThDn[nCam]);
			m_Grid.SetItem(&Item);
		}

		Item.col = GRID_COL_MIN_V;
		for(i=0; i<MAX_DEFECT; i++){
			Item.row = i+1;
			Item.strText.Format("%d",pDoc->m_data.m_nDefectVMin[nCam][i]);
			m_Grid.SetItem(&Item);
		}

		Item.col = GRID_COL_SIZE_X;
		for(i=0; i<MAX_DEFECT; i++){
			Item.row = i+1;
			Item.strText.Format("%2.3f",pDoc->m_data.m_dSizeX[nCam][i]);
			m_Grid.SetItem(&Item);
		}

		Item.col = GRID_COL_SIZE_Y;
		for(i=0; i<MAX_DEFECT; i++){
			Item.row = i+1;
			Item.strText.Format("%2.3f",pDoc->m_data.m_dSizeY[nCam][i]);
			m_Grid.SetItem(&Item);
		}

		Item.col = GRID_COL_TYPE;
		for(i=0; i<MAX_DEFECT; i++){
			Item.row = i+1;
			Item.strText.Format("%.2f",pDoc->m_data.m_dEdgeBright[nCam]);
//			Item.strText.Format("%2.3f",pDoc->m_data.m_dStdGap[nCam]);
			m_Grid.SetItem(&Item);
		}
	}else{
		Item.col = m_Grid.GetFocusCell().col;
		Item.row = m_Grid.GetFocusCell().row;
		m_Grid.GetItem(&Item);
		if(Item.col == GRID_COL_TH_UP)
		{
			pDoc->m_data.m_dThUp[nCam] = atof(Item.strText);
			if(pDoc->m_data.GetVisionLine(nCam) == GL3)
				pDoc->m_data.m_nThWhite[nCam] = int(pDoc->m_data.m_dThDn[nCam]);// - pDoc->m_data.m_nThWhiteValue;			//th White
			else{
				pDoc->m_data.m_nThWhite[nCam] = int(pDoc->m_data.m_dThUp[nCam]) - pDoc->m_data.m_nThWhiteValue[nCam];			//th White
				if(pDoc->m_data.m_nThWhite[nCam] < 10)	pDoc->m_data.m_nThWhite[nCam] = 10;
			}
		}
		if(Item.col == GRID_COL_TH_DN)	
		{
			pDoc->m_data.m_dThDn[nCam] = atof(Item.strText);
			pDoc->m_data.m_nThBlack[nCam] = int(pDoc->m_data.m_dThDn[nCam]) - pDoc->m_data.m_nThBlackValue[nCam];			//th Black
		}
		if(Item.col == GRID_COL_TYPE)	
		{
			pDoc->m_data.m_dEdgeBright[nCam] = atof(Item.strText);
//			pDoc->m_data.m_dStdGap[nCam] = atof(Item.strText);
		}		

		//m_dStdGap
//		UpdateGrid();
	}
	m_Grid.Invalidate();
//	pView->Invalidate();
}

LRESULT CDlgGrid::OnUMGridEndEdit(WPARAM wParam, LPARAM lParam)
{
	UpdateGrid(false);
	return 0;
}

LRESULT CDlgGrid::OnUMGridClick(WPARAM wParam, LPARAM lParam)
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();

	pView->Invalidate();
	return 0;
}
