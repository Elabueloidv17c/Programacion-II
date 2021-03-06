#pragma once
#include "CGame.h"

class CBreakoutfinalDlg : public CDialog
{
public:

	CBreakoutfinalDlg(CWnd* pParent = nullptr);
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BREAKOUT_FINAL_DIALOG };
#endif

protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	bool m_isClic;

	CDC * m_DC;
	CPoint m_mouse;
	CStatic m_playArea;

	CButton m_jugar;
	CButton m_editar;
	CButton m_crearNivel;
	CButton m_crearBloque;
	CButton m_crearPelota;
	CButton m_guardarCambios;
	
	CEdit m_vidasEdit;

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnEnChangeEdit1();
	CButton m_crearBloqueResistente;
	CButton m_crearBloqueIrrompible;
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	CButton m_anterior;
	CButton m_siguiente;
	afx_msg void OnEnChangeEdit2();
	CString m_nivelActual;
	CString m_ultimoNivel;
	CString m_vidas;
	afx_msg void OnEnChangeEdit3();
	CButton m_crear;
	afx_msg void OnBnClickedButton11();
};
