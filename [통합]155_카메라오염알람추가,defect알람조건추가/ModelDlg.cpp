// ModelDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "VisWeb.h"
#include "VisWebDoc.h"
#include "VisWebView.h"
#include "ModelDlg.h"

#define NUM_COLUMNS	2


// CModelDlg 대화 상자입니다.
static _TCHAR *_gszL1Label[NUM_COLUMNS] = {_T("ModelName"), _T("PLC No.")};

static int _gnLColumnWidth[NUM_COLUMNS] = {	250, 250};

IMPLEMENT_DYNAMIC(CModelDlg, CDialog)



CModelDlg::CModelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModelDlg::IDD, pParent)
	, m_strSelectProduct(_T(""))
	, m_strProductName(_T(""))
{
	m_pParent = pParent;
	m_strProductName2.Format(_T(""));
}

CModelDlg::~CModelDlg()
{
}

void CModelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PRODUCT_TAB_1, m_pList);
	DDX_Text(pDX, IDC_EDIT_PRODUCT01, m_strSelectProduct);
	DDX_Text(pDX, IDC_EDIT_PRODUCT_NAME, m_strProductName);
	DDX_Text(pDX, IDC_EDIT_PRODUCT_NAME2, m_strProductName2);
	DDX_Text(pDX, IDC_EDIT_PRODUCT_PLC, m_strProductPLC);

	
}


BEGIN_MESSAGE_MAP(CModelDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, &CModelDlg::OnBnClickedButtonRefresh)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_TAB_1, &CModelDlg::OnBnClickedButtonSelectTab1)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_TAB_1, &CModelDlg::OnBnClickedButtonDeleteTab1)
	ON_BN_CLICKED(IDC_BUTTON_PRODCUT_TAB_1, &CModelDlg::OnBnClickedButtonProdcutTab1)
	ON_BN_CLICKED(IDC_BUTTON1, &CModelDlg::OnBnClickedButton1)
//	ON_NOTIFY(NM_THEMECHANGED, IDC_STATIC_PRODUCT01_TAB_1, &CModelDlg::OnNMThemeChangedStaticProduct01Tab1)
//	ON_NOTIFY(NM_DBLCLK, IDC_STATIC_PRODUCT01_TAB_1, &CModelDlg::OnNMThemeChangedStaticProduct01Tab1)

ON_NOTIFY(NM_DBLCLK, IDC_LIST_PRODUCT_TAB_1, &CModelDlg::OnNMDblclkListProductTab1)
ON_EN_SETFOCUS(IDC_EDIT_PRODUCT_NAME, &CModelDlg::OnEnSetfocusEditProductName)
ON_EN_CHANGE(IDC_EDIT_PRODUCT_NAME, &CModelDlg::OnEnChangeEditProductName)
ON_EN_SETFOCUS(IDC_EDIT_PRODUCT_NAME2, &CModelDlg::OnEnSetfocusEditProductName2)
END_MESSAGE_MAP()


// CModelDlg 메시지 처리기입니다.

void CModelDlg::OnBnClickedButtonRefresh()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();

	m_pList.DeleteAllItems();

	CFileFind finder;
	CString strpath,strfile,strfile1;
	strpath.Format("c:\\Glim\\Model\\*.ini");
	BOOL bfind = finder.FindFile(strpath);
	int n = 0;
	BOOL bwork = FALSE;
	int nlen = 0,ndash=0;
	CString strno,strno1;
	while(bfind)
	{
		bfind = finder.FindNextFile();
		strfile = finder.GetFileName();
		if(finder.IsDirectory() || finder.IsDots())
			continue;
		else
		{
			strfile = finder.GetFileName();
			strfile.TrimRight(".ini");
			strno1 = "";

			m_strSelectProduct = strfile;// 1-model.ini
			strno = strfile;
// 			ndash = strno.Find("-");
// 			nlen = strno.GetLength();
// 			if(!pDoc->m_pDlgInterface->m_bPLCModelSync && ndash>0)
// 				continue;
// 			if(ndash>=0){
// 
// 				strfile = strno.Mid(ndash+1,nlen-ndash);
// 				strno1 = strno.Mid(0,ndash);
// 			}
			m_strModelName = strfile;
			//loadini
			CString strPath;
			strPath = "C:\\GLIM\\";
			strPath+="Model\\"+m_strSelectProduct+".ini";
			//	m_strSelectProduct = m_strSelectProduct;

			int nNum = m_pList.GetItemCount();
			m_pList.InsertItem(nNum,NULL);
			int nn1 = atoi(strno1);

			if(nn1>20){
				pView->AddtoList("Model Name Error",0);
				continue;
			}
			//			m_pList.InsertItem(1,strfile);
			m_pList.SetItemText(nNum,0,m_strModelName);//m_strSelectProduct);
			m_pList.SetItemText(nNum,1,strno1);
			pView->m_strPlcModelname[nn1] = m_strModelName;

		}
	}
}

void CModelDlg::OnBnClickedButtonSelectTab1()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();


	CString strPath = "C:\\GLIM\\";
	strPath+="Model\\"+m_strSelectProduct+".ini";
	BOOL bProductCheck = FALSE;

	CListCtrl* pCtrl;
	pCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_PRODUCT_TAB_1);
	POSITION pos = pCtrl->GetFirstSelectedItemPosition();
	CString str1;
	if (pos != NULL)
	{
		while (pos)
		{
			int nItem = pCtrl->GetNextSelectedItem(pos);//int nItem = m_ctlLstScanResults.GetNextSelectedItem(pos);
//			pCtrl->GetItemPosition(nItem,)
			pCtrl->SetCheck(nItem , TRUE);
			// you could do your own processing on nItem here

			if(MessageBox(m_pList.GetItemText(nItem,0)+" Do You Wanna Change Model?",
				"GLIM",MB_OKCANCEL) != IDOK)
			{
				return;
			}

			m_strSelectProduct = m_pList.GetItemText(nItem,0);
			m_strProductPLC = m_pList.GetItemText(nItem,1);
			strPath = "C:\\GLIM\\";
			if(pDoc->m_pDlgInterface->m_bPLCModelSync)
				strPath+="Model\\"+m_strProductPLC + "-" + m_strSelectProduct+".ini";
			else
				strPath+="Model\\"+ m_strSelectProduct+".ini";

			bProductCheck = TRUE;
			pDoc->m_data.m_strDefaultModel = m_strSelectProduct;
			//화면 update
			CString strmodel;
			strmodel.Format("Model:\r\n %s", pDoc->m_data.m_strDefaultModel);
			pView->SetDlgItemText(IDC_NETWORK_TEST,strmodel);
			pView->m_SysParam->m_lbModelNO.SetText(strmodel);
			pView->m_defectMap->DrawModel(strmodel);			// 20201018 kjh

// 			CString strModel = dlg.GetFileName();
// 			strModel.TrimRight(".ini");
// 			pDoc->m_data.m_strDefaultModel = strModel;
			pView->UpdateTolIni(m_strSelectProduct);
			pDoc->m_pDlgInterface->LoadSysParam();
			pDoc->m_pDlgInterface->LoadInsParam();
			pDoc->m_pDlgInterface->	LoadLightParam();

			if(pView->m_bSendServerINI){
				//if(pView->m_strServerModel.Compare(_T(""))!=0 && pDoc->m_data.m_strDefaultModel.Compare(_T(""))!=0 && pDoc->m_data.m_strDefaultModel.Compare(pView->m_strServerModel)==0){
					pView->WriteINIFileForServer();	// kjh 200710
					pView->CreateINICheckFile();
					pView->AddtoList("Write Server INI File!", FALSE);
			//	}
// 				else{
// 					if(pView->m_strComputerName.Find(_T("OCH"))>=0){
// 						AfxMessageBox(_T("통합서버와 모델이 다릅니다. 모델명을 확인하세요!"));
// 					}
// 					else if(pView->m_strComputerName.Find(_T("CMI"))>=0){
// 						AfxMessageBox(_T("Model name is differ from Sever Model name!"));
// 					}
// 
// 				}
			}
			else
				pView->m_bSendServerINI = true;



			pView->	WriteModel();

			if(pDoc->m_pDlgInterface->m_bPLCModelSync)
				pView->WriteShareMemorySpec();

			pView->OffsetCheck();
			pDoc->m_pDlgInterface->UpdateData(false);	

//			pDlg->SendMessage(UM_SELECT_PRODUCT_MESSAGE,0,0);

			break;
		}
	}

	UpdateData(FALSE);
}

void CModelDlg::OnBnClickedButtonDeleteTab1()
{
	CListCtrl* pCtrl;
	pCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_PRODUCT_TAB_1);
	CString strSelectProduct;
	CString strFilePath;
	strFilePath = "C:\\GLIM\\";
	strFilePath+="Model\\";

	POSITION pos = pCtrl->GetFirstSelectedItemPosition();

	if (pos != NULL)
	{
		while (pos)
		{
			int nItem = pCtrl->GetNextSelectedItem(pos);
			pCtrl->SetCheck(nItem , TRUE);
			// you could do your own processing on nItem here
			strSelectProduct = m_pList.GetItemText(nItem,0);
			strFilePath+=strSelectProduct+".ini";
			if(strSelectProduct == m_strSelectProduct)
			{
				AfxMessageBox("Don't Delete This Model! Because this Model Running!");
				return;
			}

			CString str;
			str.Format("Delete Model? %s",strSelectProduct);
			if(MessageBox(str,	"GLIM",MB_OKCANCEL) == IDOK)
			{
			}
			else
				return;

			m_pList.DeleteItem(nItem);
			break;
		}

	}

	DeleteFile(strFilePath);
}

void CModelDlg::OnBnClickedButtonProdcutTab1()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();

	UpdateData(TRUE);

	{
		if(m_strProductName2 == "" )
		{
			AfxMessageBox("Do you Type Model Name!");
			return;
		}//ndash
		if(pDoc->m_pDlgInterface->m_bPLCModelSync && m_strProductPLC == "")
		{
			AfxMessageBox("Do you Type PLC NO.");
			return;
		}
		int n1 = m_strProductName2.GetLength();
		if(n1>10){
			AfxMessageBox("Model Name is Long!!");
			return;

		}
		if(pDoc->m_pDlgInterface->m_bPLCModelSync && atoi(m_strProductPLC)>20){
			AfxMessageBox("Wrong PLC No!!");
			return;
		}

		for(int i=0; i < m_pList.GetItemCount(); i++)
		{
			if(m_strProductName2 == m_pList.GetItemText(i,0))
			{
				AfxMessageBox("Registration Model have a Same Model Name");
				return;
			}
			if(pDoc->m_pDlgInterface->m_bPLCModelSync &&  m_strProductPLC == m_pList.GetItemText(i,1))
			{
				AfxMessageBox("Registration PLC No. have a Same PLC No.");
				return;
			}
		}

		CListCtrl* pCtrl;
		pCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_PRODUCT_TAB_1);
		CString strSelectProduct,strno;
		CString strFilePath;
		strFilePath = "C:\\GLIM\\";
		strFilePath+="Model\\";

		POSITION pos = pCtrl->GetFirstSelectedItemPosition();

		if (pos != NULL)
		{
			while (pos)
			{
				int nItem = pCtrl->GetNextSelectedItem(pos);
				pCtrl->SetCheck(nItem , TRUE);
				// you could do your own processing on nItem here
				strSelectProduct = m_pList.GetItemText(nItem,0);
				if(pDoc->m_pDlgInterface->m_bPLCModelSync){
					strno = m_pList.GetItemText(nItem,1);
					strFilePath+= (strno + "-" + strSelectProduct+".ini");
				}
				else{
					strFilePath+= (strSelectProduct+".ini");
				}
				//if(strSelectProduct == m_strSelectProduct)
				//{
				//	AfxMessageBox("This Model Don't Delete! Because this Model Running!");
				//	return;
				//}
				//			m_pList.DeleteItem(nItem);
				break;
			}

		}
		CString str;
		str.Format("Copy Model? (%s -> %s)",strSelectProduct,m_strProductName2);
		if(MessageBox(str,	"GLIM",MB_OKCANCEL) == IDOK)
		{
			CString strnewpath;
			strnewpath.Format("c:\\Glim\\Model\\%s.ini",m_strProductName2);
			if(pDoc->m_pDlgInterface->m_bPLCModelSync)
				strnewpath.Format("c:\\Glim\\Model\\%s-%s.ini",m_strProductPLC,m_strProductName2);
			CopyFile(strFilePath,strnewpath,TRUE);

			//m_strProductName
			int nNum = m_pList.GetItemCount();
			CString strTemp;	
			m_pList.InsertItem(nNum,NULL);

			m_pList.SetItemText(nNum,0,m_strProductName2);
			if(pDoc->m_pDlgInterface->m_bPLCModelSync)
				m_pList.SetItemText(nNum,1,m_strProductPLC);
			m_strProductName2 = "";
			m_strProductPLC = "";
			UpdateData(FALSE);

		}
	}
}

BOOL CModelDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_pList.SetExtendedStyle(  LVS_EX_FLATSB | LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	for(int i = 0 ; i <NUM_COLUMNS; i++)
		m_pList.InsertColumn(i,_gszL1Label[i], LVCFMT_LEFT, _gnLColumnWidth[i]);

	CString str;
	str="C:\\GLIM\\";
	str+="Model";
	CreateDirectory(str,NULL);
	DirFileCount((LPSTR)(LPCSTR)str);
	OnBnClickedButtonRefresh();
	GetDlgItem(IDC_BUTTON_REFRESH)->SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

int CModelDlg::DirFileCount(char *pDirName)
{
	struct _finddata_t c_file;
	char FileSpec[_MAX_PATH], TmpFileName[_MAX_PATH];
	long hFile;
	int SubDirCount=0;

	sprintf( (char *)FileSpec, "%s\\*.*", pDirName);

	if( (hFile = _findfirst( (const char *)FileSpec, &c_file )) == -1L ) 
	{
		return 0;
	}else 
	{
		SubDirCount=0;
		if( c_file.attrib & _A_SUBDIR) 
		{
			if( c_file.name[0] != '.') 
				SubDirCount++;
		}else 
		{
			sprintf( (char *)TmpFileName, "%s\\%s", pDirName, c_file.name);
		}

		while( _findnext( hFile, &c_file ) == 0 ) 
		{ // possible uninitialized memory read from Purify
			if( c_file.attrib & _A_SUBDIR) 
			{
				if( c_file.name[0] != '.') 
					SubDirCount++;
			} else 
			{
				CString str,strTemp;
				sprintf( (char *)TmpFileName, "%s\\%s", pDirName, c_file.name);
				str = TmpFileName;
				strTemp = str.Right(4);
			}
		}
		_findclose( hFile );
	}

	if ( SubDirCount < 1 ) 
	{
		return 0;
	}

	char **SubDirNames;
	int i;

	SubDirNames = (char **)malloc( SubDirCount * sizeof(char *));
	if( SubDirNames == NULL ) 
		return 0;

	for( i=0;i<SubDirCount;i++) 
	{
		SubDirNames[i] = (char *)malloc(_MAX_PATH);
		if ( SubDirNames[i] == NULL ) 
			return 0;
	}

	i=0;
	if( (hFile = _findfirst( (const char *)FileSpec, &c_file )) == -1L ) 
		return 0;
	else 
	{
		if( (c_file.attrib & _A_SUBDIR) && (c_file.name[0] != '.')) 
			sprintf( (char *)SubDirNames[i++], "%s\\%s", pDirName, c_file.name);

		while( _findnext( hFile, &c_file ) == 0 ) 
		{
			if( (c_file.attrib & _A_SUBDIR) && (c_file.name[0] != '.')) 
				sprintf( (char *)SubDirNames[i++], "%s\\%s", pDirName, c_file.name);
		}

		_findclose( hFile );
	}

	if( i != SubDirCount ) 
		return 0;

	for(i=0;i<SubDirCount;i++) 
	{
		DirFileCount( SubDirNames[i] );
		free( SubDirNames[i] );
	}

	free( SubDirNames );

	return 0;
}
void CModelDlg::OnBnClickedButton1()
{
	ShowWindow(0);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

// void CModelDlg::OnNMThemeChangedStaticProduct01Tab1(NMHDR *pNMHDR, LRESULT *pResult)
// {
// 	// 이 기능을 사용하려면 Windows XP 이상이 필요합니다.//OnNMDblclkListProductTab1
// 	// _WIN32_WINNT 기호는 0x0501보다 크거나 같아야 합니다.
// 	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
// 	OnBnClickedButtonSelectTab1();
// 
// 	*pResult = 0;
// }

void CModelDlg::OnNMDblclkListProductTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
//	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	OnBnClickedButtonSelectTab1();
	*pResult = 0;
}


void CModelDlg::OnEnSetfocusEditProductName()
{
}

void CModelDlg::OnEnChangeEditProductName()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	if(m_strSelectProduct==""){
		AfxMessageBox("Do you Type Model Name!");
		return;

	}

	ShellExecute(NULL,"open","OSK.exe",NULL,NULL,SW_SHOWNORMAL);

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CModelDlg::OnEnSetfocusEditProductName2()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
// 	if(m_strSelectProduct==""){
// 		AfxMessageBox("Do you Type Model Name!");
// 		return;
// 
// 	}

	ShellExecute(NULL,"open","OSK.exe",NULL,NULL,SW_SHOWNOACTIVATE);
}

void CModelDlg::UpdateDataManual( BOOL bSave )
{
	UpdateData(bSave);
}
