#pragma once


// m_dialogCustom ��ȭ �����Դϴ�.

class m_dialogCustom : public CDialog
{
	DECLARE_DYNAMIC(m_dialogCustom)

public:
	m_dialogCustom(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~m_dialogCustom();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_CUSTOM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString m_autoInsPath;
	afx_msg void OnBnClickedOk();
};
