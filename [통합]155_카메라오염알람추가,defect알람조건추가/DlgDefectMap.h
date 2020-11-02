
#pragma once
#include "label1.h"
#include "afxwin.h"



// CDlgDefectMap 대화 상자입니다.
#define WHITE RGB(255,255,255)
#define BLACK RGB(50,50,50)
#define GRAY RGB(190,190,190)

#define CELLCNT 60


class CDlgDefectMap : public CDialog
{
	DECLARE_DYNAMIC(CDlgDefectMap)

public:
	CDlgDefectMap(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgDefectMap();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLGDEFECTMAP };

	CWnd*	m_vMain;
	int		m_nID;
	CWnd*	m_pParent;
	CWnd*	  m_pwndShow;
	CFont	m_DispFont1;
	void CDlgDefectMap::RedrawRect(int n);
	void CDlgDefectMap::DrawModel(CString str);
	void CDlgDefectMap::DrawLane(int nLane1,int nLane2,int nLane3);
	int	CDlgDefectMap::CheckSpec(CString strdata,int ncount);

	void CDlgDefectMap::AddtoMapLog(CString strData,BOOL bWrite=FALSE);
	CFont	m_DispFont;
	BOOL	m_bSim1;
	int		m_nTitleSize;
	int		m_nOldEdgeCount;
	int		m_nLintTB[2][2];//0 top 1 bottom  // 0위 1아래

	int CDlgDefectMap::CheckPosition(int nLine);

	void CDlgDefectMap::DrawRectangle2(CDC *pDC, CPoint p1, CPoint p2, CPoint p3, COLORREF lColor, int nLineWidth,int nCam,int nCount,CString strmm,CString strmis);
	CPoint CDlgDefectMap::DrawPitchCam2(CDC *pDC, CPoint p1, CPoint p2, COLORREF lColor, int nLineWidth,int nCam,double dmismatch,CString strmis,int nIndex,double dgap,CString strgap);
	void CDlgDefectMap::DataDraw2(CRect rt,CString str,int nLineWidth, COLORREF lColor,BOOL bRect);//gap data
	void CDlgDefectMap::DataDraw1(CRect rt,CString str,int nLineWidth, COLORREF lColor,BOOL bRect);//mismatch data
	int CDlgDefectMap::DrawFullLine(int nLinecnt1, double * nedge1,double *dpitch1,int nLinecnt2, double * nedge2,double *dpitch2,int nMiscnt1, double * nMisEdge1,double *dMispitch1);


	CPoint CDlgDefectMap::DrawPitchCam(CDC *pDC, CPoint p1, CPoint p2, COLORREF lColor, int nLineWidth,int nCam);
	void CDlgDefectMap::DrawRectangle(CDC *pDC, CPoint p1, CPoint p2, CPoint p3, COLORREF lColor, int nLineWidth,int nCam,int nCount,CString strmm);
	CPoint CDlgDefectMap::Scale(CPoint point,int nCam);
	CPoint CDlgDefectMap::DrawPitchCam1(CDC *pDC, CPoint p1, CPoint p2, COLORREF lColor, int nLineWidth,int nCam);
	void CDlgDefectMap::DrawRectangle1(CDC *pDC, CPoint p1, CPoint p2, CPoint p3, COLORREF lColor, int nLineWidth,int nCam,int nCount,CString strmm);
	CPoint CDlgDefectMap::Scale1(CPoint point,int nCam);

	//DISPLAY
	CRect	m_rtArea;
	BOOL	m_bRedrawTime;

	int m_nPosCount;
	double m_dCellPos[CELLCNT];
	double m_dCellWidth[CELLCNT];

	void CDlgDefectMap::SetPosCount(int nCellCnt);
	void CDlgDefectMap::SetEdgePos(double* dPos);
	void CDlgDefectMap::SetEdgeWidth(double* dWidth);
//	BOOL CDlgDefectMap::Create();
	void CDlgDefectMap::RedrawMap();
	void CDlgDefectMap::DrawGridLine(CDC *pDC);
	void CDlgDefectMap::DrawGridLine2(CDC *pDC, int nWidthCnt);

	void CDlgDefectMap::DrawGridLine1();
	void CDlgDefectMap::DrawGridLine3(int nLineCount);
	CPoint CDlgDefectMap::Scale(CPoint point,int nW1,int nH1);

	void ShowMismatchControl();

	CLabel m_lbMismatchTitle;
	CLabel m_lbMismatchTitle1[3];//0top 1back 2 mis

	CLabel m_lbGapTitle;//IDC_STATIC_MISMATCHTITLE5

	
	void CDlgDefectMap::ShowHideMisMatch(int nMismatch,int nTop,int nback);
	void CDlgDefectMap::InitControl();


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	virtual BOOL OnInitDialog();
	CLabel m_lbMismatchLength[MAX_LENGTH];
	CLabel m_lbTopLength[MAX_LENGTH];
	CLabel m_lbBackLength[MAX_LENGTH];

	CLabel m_lbTopBackLenth[2];//	IDC_STATIC_TOPBACKLENTH2


	afx_msg void OnBnClickedButtonShowhide();
	afx_msg void OnBnClickedButtonAlarmspec();
	BOOL m_bAlarmOff;
	afx_msg void OnBnClickedCheckAlarmOff1();
	afx_msg void OnBnClickedButtonAlarmspec2();
	afx_msg void OnBnClickedButtonModelmis();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	CLabel m_lbMisEpc1;
	CLabel m_lbMisEpc2;

	CLabel m_lbMisINFO[5];
	CLabel m_lbMisDefect1[5];
	CLabel m_lbMisDefect2[5];

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CListBox m_log_Map;
	CLabel m_lbTBGap;
	afx_msg void OnBnClickedBtnLastWidtData();
	afx_msg void OnBnClickedBtnDataFolderMismatch();
};
