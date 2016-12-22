#pragma once
#include "afxwin.h"


// _SetingMenu 对话框

class _SetingMenu : public CDialogEx
{
	DECLARE_DYNAMIC(_SetingMenu)

public:

	_SetingMenu(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~_SetingMenu();


//对话框数据
 enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	HICON m_hIcon;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
//	afx_msg void OnInitMenu(CMenu* pMenu);
	virtual BOOL OnInitDialog();
	afx_msg void OnStnClickedStaticMainpage();
	afx_msg void OnStnClickedStaticTasklist();
	afx_msg void OnStnClickedStaticOrderpage();
	afx_msg void OnStnClickedStaticUserpage();
	afx_msg void OnStnClickedStaticZhaoinf();
	afx_msg void OnStnClickedStaticShengshu();
	afx_msg void OnStnClickedStaticMyinf();
	afx_msg void OnStnClickedStaticStudyc();
	afx_msg void OnStnClickedStaticHelpc();
	CStatic _m_menuId;
	CStatic _m_menu_Userinf;
	CStatic _menu_pic;
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	
};
