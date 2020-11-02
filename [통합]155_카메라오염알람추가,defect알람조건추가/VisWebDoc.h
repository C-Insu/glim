// VisWebDoc.h : interface of the CVisWebDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VISWEBDOC_H__3C25619B_CF88_471B_AA8A_D9CE921C58D6__INCLUDED_)
#define AFX_VISWEBDOC_H__3C25619B_CF88_471B_AA8A_D9CE921C58D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Image.h"
#include "Data.h"
#include "Vision.h"
#include "dlgGrid.h"
#include "DlgInterface.h"
//#include "Network_module_server/Network.h"
#include "Udp_Network_module/XManageSocket.h"
#include "FileMove.h"
#include "DlgSetting.h"
#include "DlgSysParam.h"

//#include "GigECamera.h"

class CVisWebDoc : public CDocument
{
protected: // create from serialization only
	CVisWebDoc();
	DECLARE_DYNCREATE(CVisWebDoc)

//-------------------------------------------------------
// Attributes
public:
//	CNetwork		*m_pNetwork;
	CVision			*m_pVision;
//	CVision1		*m_pVision1;	//KYW
//	CGigECamera		*m_pVision1[MAX_CAMERAS];
	CFileMove		m_cFileMove;
	CImage			*m_pImage;
	CImage			*m_pImage1;	//대명
	CImage			*m_pImage2;	//대명
	CImage			*m_pImageBad;
	CImage			*m_pImageNG;	
	CImage			*m_pImageNG1;	//대명
	CImage			*m_pImageNG2;	//대명
	CImage			*m_pImageDsp;	
	CImage			*m_pImageDsp1;	//대명
	CImage			*m_pImageDsp2;	//대명
	CImage			*m_pImageMini;	
	CImage			*m_pImageMini1;	//대명
	CImage			*m_pImageMini2;	//대명

	//Image 버퍼 포인터
	unsigned char*  m_pImagePtr;
	unsigned char*  m_pImage1Ptr;
	unsigned char*  m_pImage2Ptr;
	unsigned char*  m_pImageNGPtr;
	unsigned char*  m_pImageNG1Ptr;
	unsigned char*  m_pImageNG2Ptr;
	unsigned char*  m_pImageDspPtr;
	unsigned char*  m_pImageDsp1Ptr;
	unsigned char*  m_pImageMiniPtr;
	unsigned char*  m_pImageMini1Ptr;

	//Image Width 변수
	int				m_pImageWidth;
	int				m_pImage1Width;	//대
	int				m_pImage2Width;	//대
	int				m_pImageBadWidth;
	int				m_pImageNGWidth;	
	int				m_pImageNG1Width;	
	int				m_pImageNG2Width;	
	int				m_pImageDspWidth;	
	int				m_pImageDsp1Width;	
	int				m_pImageDsp2Width;	
	int				m_pImageMiniWidth;	
	int				m_pImageMini1Width;	
	int				m_pImageMini2Width;	

	//Image Height 변수
	int				m_pImageHeight;
	int				m_pImage1Height;	//대
	int				m_pImage2Height;	//대
	int				m_pImageBadHeight;
	int				m_pImageNGHeight;	
	int				m_pImageNG1Height;	
	int				m_pImageNG2Height;	
	int				m_pImageDspHeight;	
	int				m_pImageDsp1Height;	
	int				m_pImageDsp2Height;	
	int				m_pImageMiniHeight;	
	int				m_pImageMini1Height;	
	int				m_pImageMini2Height;	

	
	CData			m_data;
	CDlgGrid		*m_pDlgGrid;
	CDlgInterface	*m_pDlgInterface;
	CDlgSetting		*m_pDlgSetting;
	//CDlgSysParam	*m_pDlgSysParam;

	int				m_nTotalIns[MAX_CAMERAS];
	int				m_nTotalBad[MAX_CAMERAS];

	CString			m_str_ini_path;
	CString			m_str_model;
	CString			m_str_lot;			//로트 앞부분 10자리
	CString			m_str_lot_Full;		//로트 전체 17자리
	CString			m_str_lot_End;		//로트 뒤 6자리,
	CString			m_str_NEWlot;			//신규 LOT
	CString			m_str_NEWlot_Full;		//신규 LOT
	int				m_nLotEnd;
	int				m_nNewLotEnd;


	CXManageSocket		m_RecvtoServerSock;
	CXManageSocket		m_RecvtoNebSock;
	CXManageSocket		m_SendNebSock;
	CXManageSocket		m_SendtoServerSock;
	CXManageSocket		m_SendtoMarkingSock;
	CXManageSocket		m_SendtoMarkVisionSock1;
	CXManageSocket		m_SendtoMarkVisionSock2;
	/////대명cross
	CXManageSocket		m_SendtoServerSock1;
	CXManageSocket		m_SendtoMarkingSock1;
	CString			m_strServerip;
//-------------------------------------------------------
// Operations
public:
	void	OnSaveModel();
	void	OnLoadModel();



//-------------------------------------------------------
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVisWebDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SaveHistoEquaData();
	void LoadHistoEquaData();
	virtual ~CVisWebDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVisWebDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISWEBDOC_H__3C25619B_CF88_471B_AA8A_D9CE921C58D6__INCLUDED_)
