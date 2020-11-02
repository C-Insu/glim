#pragma once


// m_dialogCustom 대화 상자입니다.

class m_dialogCustom : public CDialog
{
	DECLARE_DYNAMIC(m_dialogCustom)

public:
	m_dialogCustom(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~m_dialogCustom();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_CUSTOM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_autoInsPath;
	afx_msg void OnBnClickedOk();
};
