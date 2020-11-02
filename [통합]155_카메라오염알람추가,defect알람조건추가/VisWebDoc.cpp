// VisWebDoc.cpp : implementation of the CVisWebDoc class
//

#include "stdafx.h"
#include "VisWeb.h"

#include "VisWebDoc.h"
#include "vision.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVisWebDoc

IMPLEMENT_DYNCREATE(CVisWebDoc, CDocument)

BEGIN_MESSAGE_MAP(CVisWebDoc, CDocument)
	//{{AFX_MSG_MAP(CVisWebDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVisWebDoc construction/destruction

CVisWebDoc::CVisWebDoc()
{
	m_pImage = NULL;
	m_pImage1 = NULL;
	m_pImage2 = NULL;
	m_pImageBad = NULL;
	m_pImageNG =NULL;
	m_pImageNG1 =NULL;
	m_pImageNG2 =NULL;
	m_pImageDsp = NULL;
	m_pImageDsp1 = NULL;
	m_pImageDsp2 = NULL;
	m_pVision	= NULL;	
	m_pImageMini = NULL;
	m_pImageMini1 = NULL;
	m_pImageMini2 = NULL;

	//for(int i=0;i<MAX_CAMERAS;i++)
	//	m_pVision1[i]	= NULL;		//KYW
	m_pDlgGrid	= NULL;
	m_pDlgInterface = NULL;
	m_pDlgSetting	=	NULL;
	//m_pDlgSysParam	= NULL;

	for(int i=0;i<MAX_CAMERAS;i++){
		m_nTotalIns[i]	= 0;
		m_nTotalBad[i] = 0;
	}

	m_str_ini_path = "parameter.ini";
	m_str_model = "abc";
//	m_str_lot = "NONE";
//	m_str_lot_Full = "NONE";
	m_str_NEWlot= "NONE";;			//신규 LOT
	m_str_NEWlot_Full= "NONE";;		//신규 LOT
	m_nLotEnd = 0;
	m_nNewLotEnd = 0;


}

CVisWebDoc::~CVisWebDoc()
{

	if(m_data.m_nVisionLine==GL1 ||m_data.m_nVisionLine==GL9)
	{

	}
	else
	{
		m_pVision->HookStop();
		Wait(200);
		m_pVision->Close();

	}
	if(m_pVision)		delete m_pVision;
//	if(m_pVision1)		delete m_pVision1;	//KYW
/*
	if(m_pImage)		delete m_pImage;	
	if(m_pImageNG)		delete m_pImageNG;	//m_pImageMerge
	if(m_pImageDsp)		delete m_pImageDsp;
	if(m_pImageBad)		delete m_pImageBad;
	if(m_pDlgGrid)		delete m_pDlgGrid;
	if(m_pDlgInterface)	delete m_pDlgInterface;
	if(m_pDlgSetting)	delete m_pDlgSetting;
	*/
}

BOOL CVisWebDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CVisWebDoc serialization

void CVisWebDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
//	m_data.Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CVisWebDoc diagnostics

#ifdef _DEBUG
void CVisWebDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CVisWebDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVisWebDoc commands


void CVisWebDoc::OnSaveModel() 
{
	m_pDlgGrid->UpdateGrid(FALSE);
	CFileDialog dlg(false, "nxt", NULL, OFN_SHAREAWARE, "Model Files (*.nxt)|*.nxt||");
	if(AfxMessageBox("새롭게 모델을 저장하겠습니까?", MB_OKCANCEL) == IDCANCEL)	return;

	if(dlg.DoModal() == IDOK){
//		m_strCurFileName = dlg.GetPathName();
		CFile file;
		try{
			if(file.Open(dlg.GetPathName(), CFile::modeCreate|CFile::modeWrite)){
				CArchive ar( &file, CArchive::store);
				Serialize(ar);
				file.Close();
			}
		}
		catch(CFileException)
		{
			//AfxMessageBox( "File Open failed" );
		}
		catch(...)
		{
			//AfxMessageBox( "File Open failed2~" );
		}
		
	}
}

void CVisWebDoc::OnLoadModel() 
{
	CFileDialog dlg(true, "nxt", NULL, OFN_SHAREAWARE, "Model Files (*.nxt)|*.nxt||");
	if(dlg.DoModal() == IDOK){
//		m_strCurFileName = dlg.GetPathName();
		CFile file;
		try{
			if(file.Open(dlg.GetPathName(), CFile::modeRead)){
				CArchive ar( &file, CArchive::load);
				Serialize(ar);
				file.Close();
			}
		}
		catch(CFileException)
		{
			//AfxMessageBox( "File Open failed" );
		}
		catch(...)
		{
			//AfxMessageBox( "File Open failed2~" );
		}
	}
	m_pDlgGrid->UpdateGrid();
}

void CVisWebDoc::LoadHistoEquaData()
{
	CFile file;
	try{

	}
	catch(CFileException)
	{
		//AfxMessageBox( "File Open failed" );
	}
	catch(...)
	{
		//AfxMessageBox( "File Open failed2~" );
	}
}

void CVisWebDoc::SaveHistoEquaData()
{
	CFile file;
	try{

	}
	catch(CFileException)
	{
		//AfxMessageBox( "File Open failed" );
	}
	catch(...)
	{
		//AfxMessageBox( "File Open failed2~" );
	}
}
