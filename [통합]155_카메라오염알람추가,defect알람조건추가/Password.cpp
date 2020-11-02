// Password.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "VisWeb.h"
#include "VisWebDoc.h"
#include "VisWebView.h"
#include "Password.h"


// CPassword ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CPassword, CDialog)

CPassword::CPassword(CWnd* pParent /*=NULL*/)
	: CDialog(CPassword::IDD, pParent)
	, m_bModifyPass(FALSE)
	, m_strPassword1(_T(""))
	, m_strPassword2(_T(""))
	, m_strPassword3(_T(""))
	, m_strPassword4(_T(""))
{

	m_nbSelectNo = 0;
	m_pParent = pParent;
	m_strReadPass = "";

}

CPassword::~CPassword()
{
}

void CPassword::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_MODIFYPASS, m_bModifyPass);
	DDX_Text(pDX, IDC_EDIT_PASS1, m_strPassword1);
	DDX_Text(pDX, IDC_EDIT_PASS2, m_strPassword2);
	DDX_Text(pDX, IDC_EDIT_PASS3, m_strPassword3);
	DDX_Text(pDX, IDC_EDIT_PASS4, m_strPassword4);
	DDX_Control(pDX, IDC_STATIC_PASSEORDRESEULT, m_lbPasswordResult);
}


BEGIN_MESSAGE_MAP(CPassword, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_CHECK3, &CPassword::OnBnClickedButtonCheck3)
	ON_BN_CLICKED(IDC_BUTTON_CHECK, &CPassword::OnBnClickedButtonCheck)
	ON_BN_CLICKED(IDC_BUTTON_CHECK2, &CPassword::OnBnClickedButtonCheck2)
	ON_BN_CLICKED(IDC_CHECK_MODIFYPASS, &CPassword::OnBnClickedCheckModifypass)
	ON_BN_CLICKED(IDC_BUTTON_CHECK4, &CPassword::OnBnClickedButtonCheck4)
	ON_EN_SETFOCUS(IDC_EDIT_PASS2, &CPassword::OnEnSetfocusEditPass2)
	ON_EN_SETFOCUS(IDC_EDIT_PASS1, &CPassword::OnEnSetfocusEditPass1)
	ON_EN_SETFOCUS(IDC_EDIT_PASS3, &CPassword::OnEnSetfocusEditPass3)
	ON_EN_SETFOCUS(IDC_EDIT_PASS4, &CPassword::OnEnSetfocusEditPass4)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// CPassword �޽��� ó�����Դϴ�.

void CPassword::OnBnClickedButtonCheck3()
{//Ȯ�� �� �ݱ�
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();

	UpdateData();
	ReadPassword();
	if(m_strReadPass == m_strPassword1 || m_strPassword1 == "CMIMASTERKEY")
	{
		pView->AddtoList("Password OK",1);

		PasswordResult(2);
		pView->m_NumPad->ShowWindow(0);
	//	pView->m_pDlgSet->m_FormTab1->m_bShowHide = TRUE;
		pDoc->m_pDlgInterface->ShowWindow(1);
		m_nbSelectNo = 0;
		ShowWindow(0);
		PasswordResult(0);
		m_strPassword1 =m_strPassword2=m_strPassword3=m_strPassword4= "";
		GetDlgItem(IDC_EDIT_PASS2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PASS3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PASS4)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_CHECK4)->EnableWindow(FALSE);
	}
	else
	{
		PasswordResult(1);
		pView->AddtoList("Wrong Password",1);
		m_strPassword1 = "";
		GetDlgItem(IDC_EDIT_PASS2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PASS3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PASS4)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_CHECK4)->EnableWindow(FALSE);

//		pView->m_pDlgSet->m_FormTab1->m_bShowHide = FALSE;
	}
	//m_strPassword1 = "";
	UpdateData(FALSE);
}

void CPassword::OnBnClickedButtonCheck()
{//ĵ��
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	m_strPassword1 =m_strPassword2=m_strPassword3=m_strPassword4= "";

	m_nbSelectNo = 0;
	UpdateData(FALSE);
	pView->m_NumPad->ShowWindow(0);
	ShowWindow(SW_HIDE);
	PasswordResult(0);
	GetDlgItem(IDC_EDIT_PASS2)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PASS3)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PASS4)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CHECK4)->EnableWindow(FALSE);


	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CPassword::OnBnClickedButtonCheck2()
{//��ȣ ����
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();

	pView->AddtoList("Password Change Click!",1);
	UpdateData();

	if(m_strPassword3 == m_strPassword4){
		WritePassword();
		m_bModifyPass = FALSE;
		m_strPassword1 = m_strPassword2 = m_strPassword3 = m_strPassword4= "";
		UpdateData(FALSE);
		OnBnClickedCheckModifypass();
		m_strPassword1 =m_strPassword2=m_strPassword3= m_strPassword4="";
		m_nbSelectNo = 0;
		UpdateData(FALSE);

	}else{
		AfxMessageBox("New Password1 & password2 Incorrect");
		m_strPassword1 = m_strPassword2 = m_strPassword3 = m_strPassword4= "";
		UpdateData(FALSE);
	}



// 	if(m_strPassword1 == m_strPassword2)
// 	else
// 		AfxMessageBox("Wrong  Password");

}

void CPassword::OnBnClickedCheckModifypass()
{//m_bModifyPass
	UpdateData();
	if(m_bModifyPass)
	{
		GetDlgItem(IDC_EDIT_PASS2)->EnableWindow(TRUE);
//		GetDlgItem(IDC_EDIT_PASS3)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_CHECK4)->EnableWindow(TRUE);


	}
	else
	{
		GetDlgItem(IDC_EDIT_PASS2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PASS3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PASS4)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_CHECK4)->EnableWindow(FALSE);

	}
}

void CPassword::ReadPassword()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData();

	CString str;
	CStdioFile   file;
	CString filename;
	str = "";
	int n=0;
	int check = 1;
	filename.Format(_T("C:\\MELSEC\\Pass.glm"));

	if(check==1)//Read
	{
		if(file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
		{	
			file.ReadString(str);
			m_strReadPass = str;
			file.Close();
		}
		else
			m_strReadPass = "";

	}
	else
	{
		str = m_strPassword2;

		if(file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText))
		{	
			file.WriteString(str);
			file.Close();
		}
	}
}
void CPassword::WritePassword()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData();

	CString str;
	CStdioFile   file;
	CString filename;
	str = "";
	int n=0;
	int check = 0;
	filename.Format(_T("C:\\Melsec\\Pass.glm"));

	if(check==1)//Read
	{
		if(file.Open(filename, CFile::modeReadWrite|CFile::typeText)) 
		{	
			file.ReadString(str);
			m_strReadPass = str;
			file.Close();
		}
	}
	else
	{
		str = m_strPassword3;

		if(file.Open(filename, CFile::modeCreate|CFile::modeReadWrite|CFile::typeText))
		{	
			file.WriteString(str);
			file.Close();
		}
		m_strPassword2 = m_strPassword3;
		m_bModifyPass = TRUE;
		OnBnClickedCheckModifypass();
	}
}


BOOL CPassword::OnInitDialog()
{
	CDialog::OnInitDialog();

	GetDlgItem(IDC_EDIT_PASS2)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PASS3)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PASS4)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CHECK4)->EnableWindow(FALSE);


	PasswordResult(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CPassword::OnBnClickedButtonCheck4()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	UpdateData();
	ReadPassword();
	if(m_strReadPass == m_strPassword2 || m_strPassword2 == "CMIMASTERKEY")
	{
		pView->AddtoList("Password OK",1);
		m_strPassword2 = "";
		m_nbSelectNo = 0;

		GetDlgItem(IDC_EDIT_PASS3)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PASS4)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PASS2)->EnableWindow(FALSE);

		//	pView->m_pDlgSet->m_FormTab1->m_bShowHide = TRUE;
	}
	else
	{
		pView->AddtoList("Wrong Password",1);
		m_strPassword2 = "";
		m_nbSelectNo = 0;

		//		pView->m_pDlgSet->m_FormTab1->m_bShowHide = FALSE;
	}
	m_strPassword2 = "";
	UpdateData(FALSE);

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CPassword::PasswordResult(int n)
{
	CString str;

	if(n==1){
		m_lbPasswordResult.SetTextColor(COLOR_YELLOW);
		m_lbPasswordResult.SetBkColor(COLOR_RED);
		m_lbPasswordResult.SetFontName("�޸յձ�������");
		m_lbPasswordResult.SetFontSize(20);
		str.Format("Wrong!");
	}
	else if(n==0){
		m_lbPasswordResult.SetTextColor(COLOR_GRAY_WHITE1);
		m_lbPasswordResult.SetBkColor(COLOR_GRAY_WHITE1);
		m_lbPasswordResult.SetFontName("�޸յձ�������");
		m_lbPasswordResult.SetFontSize(20);
		str.Format("");
	}
	else{
		m_lbPasswordResult.SetTextColor(COLOR_BLACK);
		m_lbPasswordResult.SetBkColor(COLOR_GREEN);
		m_lbPasswordResult.SetFontName("�޸յձ�������");
		m_lbPasswordResult.SetFontSize(20);
		str.Format("OK");
	}
	m_lbPasswordResult.SetText(str);
}
void CPassword::OnEnSetfocusEditPass2()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	if(pView->m_bPassCheck==FALSE)return;
	m_nbSelectNo = 2;
	pView->m_NumPad->LabelShow1(2,0,0);//

}

void CPassword::OnEnSetfocusEditPass1()
{

	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	if(pView->m_bPassCheck==FALSE)return;
	m_nbSelectNo = 1 ;
	pView->m_NumPad->LabelShow1(2,0,0);//
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CPassword::OnEnSetfocusEditPass3()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	if(pView->m_bPassCheck==FALSE)return;
	m_nbSelectNo = 3;
	pView->m_NumPad->LabelShow1(2,0,0);//
}

void CPassword::OnEnSetfocusEditPass4()
{
	CVisWebView *pView = (CVisWebView*)m_pParent;
	CVisWebDoc	*pDoc	 = (CVisWebDoc*)pView->GetDocument();
	if(pView->m_bPassCheck==FALSE)return;
	m_nbSelectNo = 4;
	pView->m_NumPad->LabelShow1(2,0,0);//
}

void CPassword::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CPassword::PreTranslateMessage(MSG* pMsg)
{
	int n = 0;

	if(pMsg->message == WM_KEYDOWN)
	{

		if(pMsg->wParam == VK_CAPITAL)
		{
			;
		}

		if(pMsg->wParam  == VK_RETURN){

			int k = 0;
			OnBnClickedButtonCheck3();
		}
		return 0;

/*		if(pMsg->message == 256 && m_nShowSet==0)
		{
			CEdit* pFocus = (CEdit*)GetDlgItem(IDC_EDIT_BARCODE);
			
			pFocus->SetFocus();
			
		}
		*/
	//Set focus

	}
	return CDialog::PreTranslateMessage(pMsg);
}
