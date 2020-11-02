// NumPad.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "VisWeb.h"
#include "VisWebDoc.h"
#include "VisWebView.h"

#include "NumPad.h"


// CNumPad 대화 상자입니다.

IMPLEMENT_DYNAMIC(CNumPad, CDialog)

CNumPad::CNumPad(CWnd* pParent /*=NULL*/)
	: CDialog(CNumPad::IDD, pParent)
	, m_strNumDisplay(_T(""))
	, m_bStandard(FALSE)
	, m_bTol1(TRUE)
{
	m_pParent = pParent;
	m_pwndShow = NULL;
	m_nSelectControl = 0;

}


CNumPad::~CNumPad()
{
}

void CNumPad::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NUM_DISPLAY, m_strNumDisplay);
	DDX_Check(pDX, IDC_CHECK_STANDARD, m_bStandard);
	DDX_Check(pDX, IDC_CHECK_TOL1, m_bTol1);
	DDX_Control(pDX, IDC_STATIC_STANDARD1, m_lbDispStand);
	DDX_Control(pDX, IDC_STATIC_MINIMUM1, m_lbDispMin);
	DDX_Control(pDX, IDC_STATIC_MAXIMUM1, m_lbDispMax);
}


BEGIN_MESSAGE_MAP(CNumPad, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_NUM1, &CNumPad::OnBnClickedButtonNum1)
	ON_BN_CLICKED(IDC_BUTTON_NUM2, &CNumPad::OnBnClickedButtonNum2)
	ON_BN_CLICKED(IDC_BUTTON_NUM3, &CNumPad::OnBnClickedButtonNum3)
	ON_BN_CLICKED(IDC_BUTTON_NUM4, &CNumPad::OnBnClickedButtonNum4)
	ON_BN_CLICKED(IDC_BUTTON_NUM5, &CNumPad::OnBnClickedButtonNum5)
	ON_BN_CLICKED(IDC_BUTTON_NUM6, &CNumPad::OnBnClickedButtonNum6)
	ON_BN_CLICKED(IDC_BUTTON_NUM7, &CNumPad::OnBnClickedButtonNum7)
	ON_BN_CLICKED(IDC_BUTTON_NUM8, &CNumPad::OnBnClickedButtonNum8)
	ON_BN_CLICKED(IDC_BUTTON_NUM9, &CNumPad::OnBnClickedButtonNum9)
	ON_BN_CLICKED(IDC_BUTTON_NUM10, &CNumPad::OnBnClickedButtonNum10)
	ON_BN_CLICKED(IDC_BUTTON_NUMPLUS, &CNumPad::OnBnClickedButtonNumplus)
	ON_BN_CLICKED(IDC_BUTTON_NUMMINUS, &CNumPad::OnBnClickedButtonNumminus)
	ON_BN_CLICKED(IDC_BUTTON_NUMPLUS2, &CNumPad::OnBnClickedButtonNumplus2)
	ON_BN_CLICKED(IDC_BUTTON_NUMPLUS3, &CNumPad::OnBnClickedButtonNumplus3)
	ON_BN_CLICKED(IDC_BUTTON_NUMCLOSE, &CNumPad::OnBnClickedButtonNumclose)
	ON_BN_CLICKED(IDC_BUTTON_NUMDOT, &CNumPad::OnBnClickedButtonNumdot)
	ON_BN_CLICKED(IDC_CHECK_STANDARD, &CNumPad::OnBnClickedCheckStandard)
	ON_BN_CLICKED(IDC_CHECK_TOL1, &CNumPad::OnBnClickedCheckTol1)
END_MESSAGE_MAP()


// CNumPad 메시지 처리기입니다.

void CNumPad::OnBnClickedButtonNum1()
{
	m_strNum += "1";
	m_strNumDisplay = m_strNum;
	UpdateData(FALSE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CNumPad::OnBnClickedButtonNum2()
{
	m_strNum += "2";
	m_strNumDisplay = m_strNum;
	UpdateData(FALSE);
}

void CNumPad::OnBnClickedButtonNum3()
{
	m_strNum += "3";
	m_strNumDisplay = m_strNum;
	UpdateData(FALSE);
}

void CNumPad::OnBnClickedButtonNum4()
{
	m_strNum += "4";
	m_strNumDisplay = m_strNum;
	UpdateData(FALSE);
}

void CNumPad::OnBnClickedButtonNum5()
{
	m_strNum += "5";
	m_strNumDisplay = m_strNum;
	UpdateData(FALSE);
}

void CNumPad::OnBnClickedButtonNum6()
{
	m_strNum += "6";
	m_strNumDisplay = m_strNum;
	UpdateData(FALSE);
}

void CNumPad::OnBnClickedButtonNum7()
{
	m_strNum += "7";
	m_strNumDisplay = m_strNum;
	UpdateData(FALSE);
}

void CNumPad::OnBnClickedButtonNum8()
{
	m_strNum += "8";
	m_strNumDisplay = m_strNum;
	UpdateData(FALSE);
}

void CNumPad::OnBnClickedButtonNum9()
{
	m_strNum += "9";
	m_strNumDisplay = m_strNum;
	UpdateData(FALSE);
}

void CNumPad::OnBnClickedButtonNum10()
{
	m_strNum += "0";
	m_strNumDisplay = m_strNum;
	UpdateData(FALSE);
}

void CNumPad::OnBnClickedButtonNumplus()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CNumPad::OnBnClickedButtonNumminus()
{
	m_strNum += "-";
	m_strNumDisplay = m_strNum;
	UpdateData(FALSE);
}

void CNumPad::OnBnClickedButtonNumplus2()
{//클리어
	m_strNum = "";
	m_strNumDisplay = m_strNum;
	UpdateData(FALSE);
}

void CNumPad::OnBnClickedButtonNumplus3()
{//적용
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisWebView *pDlg = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pDlg->GetDocument();
	
	if(m_strNumDisplay=="")return;
	CString str = m_strNumDisplay;
	if(pDlg->m_pPassword->m_nbSelectNo>0){
		if(pDlg->m_pPassword->m_nbSelectNo==1){
			pDlg->m_pPassword->m_strPassword1 = m_strNumDisplay;
		}
		else if(pDlg->m_pPassword->m_nbSelectNo==2){
			pDlg->m_pPassword->m_strPassword2 = m_strNumDisplay;
		}
		else if(pDlg->m_pPassword->m_nbSelectNo==3){
			pDlg->m_pPassword->m_strPassword3 = m_strNumDisplay;
		}
		else if(pDlg->m_pPassword->m_nbSelectNo==4){
			pDlg->m_pPassword->m_strPassword4 = m_strNumDisplay;
		}
		pDlg->m_pPassword->UpdateData(FALSE);	
	}
	else{
		if(m_nSelectControl>0){
			m_strResult = str;
			pDoc->m_pDlgInterface->ChangeValue(m_nSelectControl,m_strResult);
			m_nSelectControl = 0;
		}
		else{
			if(pDoc->m_pDlgInterface->m_nSelectEdit>=0){

				//		if(pDoc->m_pDlgInterface->m_nSelectEdit)
				int nn = pDoc->m_pDlgInterface->m_nSelectEdit;
				if(pDoc->m_pDlgInterface->m_nSelectEdit>100){
					pDlg->ChangeTol2(m_bTol1,nn,str);

				}
				else
					pDlg->ChangeTol1(m_bTol1,nn,str);
				//		pDoc->m_pDlgInterface->m_nSelectEdit = -1;
			}
			else{

				pDlg->ChangeTol(m_bTol1,pDlg->m_nSelectNum,str);
			}
		}
	}


	m_strNum = "";
	m_strNumDisplay = m_strNum;
	//pDoc->m_pDlgInterface->GetDlgItem(IDC_BUTTON_SAVE_INI)->SetFocus();
	ShowWindow(1);

	UpdateData(FALSE);
	if(pDlg->m_SysParam->IsWindowVisible()){
		pDlg->m_SysParam->UpdateData(FALSE);
	}

	if(pDoc->m_pDlgInterface->m_bPlcWrite){
		pDlg->WriteShareMemorySpec();		//200811 kjh
	
	}
	
	if(pDlg->m_bSendServerINI){
//		if(pDlg->m_strServerModel.Compare(_T(""))!=0 && pDoc->m_data.m_strDefaultModel.Compare(_T(""))!=0 && pDoc->m_data.m_strDefaultModel.Compare(pDlg->m_strServerModel)==0){
			pDlg->WriteINIFileForServer();	// kjh 200710
			pDlg->CreateINICheckFile();
			pDlg->AddtoList("Write Server INI File!", FALSE);
//		}
// 		else{
// 			if(pDlg->m_strComputerName.Find(_T("OCH"))>=0){
// 				AfxMessageBox(_T("통합서버와 모델이 다릅니다. 모델명을 확인하세요!"));
// 			}
// 			else if(pDlg->m_strComputerName.Find(_T("CMI"))>=0){
// 				AfxMessageBox(_T("Model name is differ from Sever Model name!"));
// 			}
// 
// 		}
	}
	else
		pDlg->m_bSendServerINI = true;

}

BOOL CNumPad::OnInitDialog()
{
	CDialog::OnInitDialog();

	CVisWebView *pDlg = (CVisWebView*)m_pParent;
	
	LabelInit();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CNumPad::OnBnClickedButtonNumclose()
{
	CVisWebView *pDlg = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pDlg->GetDocument();
	m_strNum = "";
	m_strNumDisplay = m_strNum;
	pDoc->m_pDlgInterface->m_nSelectEdit = -1;
	UpdateData(FALSE);
	if(pDlg->m_SysParam->IsWindowVisible())
		pDlg->m_SysParam->GetDlgItem(IDC_BUTTON_SAVE_INI)->SetFocus();
	else
		pDoc->m_pDlgInterface->GetDlgItem(IDC_BUTTON_SAVE_INI)->SetFocus();
	ShowWindow(0);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CNumPad::OnBnClickedButtonNumdot()
{
	m_strNum += ".";
	m_strNumDisplay = m_strNum;
	UpdateData(FALSE);
}

void CNumPad::OnBnClickedCheckStandard()
{//m_bStandard
	UpdateData();
	if(m_bStandard){
		m_bTol1 = FALSE;
		UpdateData(FALSE);
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CNumPad::OnBnClickedCheckTol1()
{//m_bTol1
	UpdateData();
	if(m_bTol1){
		m_bStandard = FALSE;
		UpdateData(FALSE);
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CNumPad::LabelInit()
{
	//
// 	m_lbDispStand.SetTextColor(COLOR_GREEN);
// 	m_lbDispStand.SetBkColor(COLOR_BLACK);
// 	m_lbDispStand.SetFontBold(TRUE);
// 	m_lbDispStand.SetFontName("굴림");
// 	m_lbDispStand.SetFontSize(20);
// 	m_lbDispStand.SetText("기준값");
	

	m_lbDispMin.SetTextColor(COLOR_GREEN);
	m_lbDispMin.SetBkColor(COLOR_BLACK);
	m_lbDispMin.SetFontBold(TRUE);
	m_lbDispMin.SetFontName("굴림");
	m_lbDispMin.SetFontSize(30);
	m_lbDispMin.SetText("최소값");

	m_lbDispMax.SetTextColor(COLOR_GREEN);
	m_lbDispMax.SetBkColor(COLOR_BLACK);
	m_lbDispMax.SetFontBold(TRUE);
	m_lbDispMax.SetFontName("굴림");
	m_lbDispMax.SetFontSize(30);
	m_lbDispMax.SetText("최대값");

}

void CNumPad::LabelShow(int nStand,double dmin,double dmax)
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	CString str;
// 	if(dstand>0){
// 		str.Format("기준값 : %.2f",dstand);
// 		m_lbDispStand.SetText(str);
// 	}
	if(nStand%2==0){
		m_lbDispMin.SetTextColor(COLOR_YELLOW);
		m_lbDispMax.SetTextColor(COLOR_BLUE);
	}else
	{
		m_lbDispMin.SetTextColor(COLOR_BLUE);
		m_lbDispMax.SetTextColor(COLOR_YELLOW);
	}
	if(pDoc->m_pDlgInterface->m_bEngKor == ENG)
		str.Format("Min   :   %.2f",dmin);
	else if(pDoc->m_pDlgInterface->m_bEngKor == KOR)
		str.Format("최소값   :   %.2f",dmin);
	m_lbDispMin.SetText(str);
	if(pDoc->m_pDlgInterface->m_bEngKor == ENG)
		str.Format("Max   :   %.2f",dmax);
	else if(pDoc->m_pDlgInterface->m_bEngKor == KOR)
		str.Format("최대값   :   %.2f",dmax);
	m_lbDispMax.SetText(str);

}
void CNumPad::LabelShow1(int nStand,double dmin,double dmax)
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	CString str;
	// 	if(dstand>0){
	// 		str.Format("기준값 : %.2f",dstand);
	// 		m_lbDispStand.SetText(str);
	// 	}
	if(nStand==0){
		m_lbDispMin.SetTextColor(COLOR_YELLOW);
		m_lbDispMax.SetTextColor(COLOR_BLUE);
	}
	else if(nStand==2)
	{
		m_lbDispMin.SetTextColor(COLOR_YELLOW);
		m_lbDispMax.SetTextColor(COLOR_BLUE);
		str.Format("PASSWORD");

		m_lbDispMin.SetText(str);
		m_lbDispMax.SetText(str);

	}
	else
	{
		m_lbDispMin.SetTextColor(COLOR_BLUE);
		m_lbDispMax.SetTextColor(COLOR_YELLOW);
	}
	if(nStand<2){
		if(pDoc->m_pDlgInterface->m_bEngKor == ENG)
			str.Format("Min   :   %.2f",dmin);
		else if(pDoc->m_pDlgInterface->m_bEngKor == KOR)
			str.Format("최소값   :   %.2f",dmin);
		m_lbDispMin.SetText(str);
		if(pDoc->m_pDlgInterface->m_bEngKor == ENG)
			str.Format("Max   :   %.2f",dmax);
		else if(pDoc->m_pDlgInterface->m_bEngKor == KOR)
			str.Format("최대값   :   %.2f",dmax);
		m_lbDispMax.SetText(str);
	}

}

void CNumPad::LabelShow2(int nStand,double dmin,double dmax)//일반 값 입력
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	CString str;
	if(nStand==0){
		m_lbDispMin.SetTextColor(COLOR_YELLOW);
		m_lbDispMax.SetTextColor(COLOR_BLUE);
	}else
	{
		m_lbDispMin.SetTextColor(COLOR_BLUE);
		m_lbDispMax.SetTextColor(COLOR_YELLOW);
	}
	if(pDoc->m_pDlgInterface->m_bEngKor == ENG)
		str.Format("Existing Value   :   %.2f",dmin);
	else if(pDoc->m_pDlgInterface->m_bEngKor == KOR)
		str.Format("기존값   :   %.2f",dmin);
	m_lbDispMin.SetText(str);
	if(pDoc->m_pDlgInterface->m_bEngKor == ENG)
		str.Format("Existing Value   :   %.2f",dmax);
	else if(pDoc->m_pDlgInterface->m_bEngKor == KOR)
		str.Format("기존값   :   %.2f",dmax);
	m_lbDispMax.SetText(str);

}

void CNumPad::ChangeControlsLanguage( BOOL bLan )
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();

	if(pDoc->m_pDlgInterface->m_bEngKor == ENG){
		
	}
	else if(pDoc->m_pDlgInterface->m_bEngKor == KOR){

	}
}
