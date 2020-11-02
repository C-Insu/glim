#pragma once

//#include "Queue.h"

// CDlgDefectMap ��ȭ �����Դϴ�.

#define MAP_MAX_X_ZONE 100
#define MAP_MAX_Y_ZONE 100

class CDlgDefectMap : public CDialog
{
	DECLARE_DYNAMIC(CDlgDefectMap)

public:
	CDlgDefectMap(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgDefectMap();

	CWnd*	m_vMain;
	int		m_nID;

	//DISPLAY
	CRect	m_rtArea;
	BOOL	m_bRedrawTime;
	//CQueue	m_qDefect;

	//������ ������
	//DEFECT_DATA*	m_selDefectData;

	double	m_maxXzone;
	double	m_maxYzone;

	int		mapSttOffsetX;
	int		mapSttOffsetY;

	//MAP POS
	double	m_dViewsizex;
	double	m_dViewsizey;
	int		m_nViewSttposx_ctrl_server;
	int		m_nViewSttposy_ctrl_server;

	//Map���� ��ġ
	CPoint	m_startPos;
	CPoint	m_endPos;
	BOOL	m_startToMove;

	//Grid cnt
	int		m_displayGridX;
	int		m_displayGridY;

	//������ġ
	int		m_dViewSttPosX;
	int		m_dViewSttPosY;
	BOOL	m_isZoom;

	//DEFECT_DATA*	m_pBadpointClick_file[2];

	//20170329 lgh
	int m_nMotionPosZ;

	BOOL CDlgDefectMap::Create();
	void CDlgDefectMap::CleanSelPointData();
	void CDlgDefectMap::SelectNewDefect();
	void CDlgDefectMap::RedrawMap();
	void CDlgDefectMap::DrawGridLine(CDC *pDC);
	//void CDlgDefectMap::DrawDefectMark(DEFECT_DATA *data);
	void CDlgDefectMap::DrawDefectMark(CPoint pt, int defectClass, BOOL isSel);
	CPoint CDlgDefectMap::GetViewPos(double dSrcx, double dSrcy);

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DLGDEFECTMAP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();


};
