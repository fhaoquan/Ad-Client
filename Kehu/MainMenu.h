#pragma once
#include "explorer1.h"
#include <list>
#include<vector>
#include<map>
#include"GoodInf.h"
#include "afxwin.h"
extern CImage Resour;
extern struct usr ower;

// MainMenu dialog

class MainMenu : public CDialogEx
{
	DECLARE_DYNAMIC(MainMenu)
	virtual BOOL OnInitDialog();
public:
	MainMenu(CWnd* pParent = NULL);   // standard constructor
	virtual ~MainMenu();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//重写该函数，去掉滚动条
	virtual void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS *lpncsp);
	virtual BOOL OnCreate(LPCREATESTRUCT lpCreateStruct);

	DECLARE_MESSAGE_MAP()
public:
	// 浏览器变量
afx_msg void OnBnClickedOk();
CExplorer1 m_explor;
//添加菜单项
CMenu m_Menu;
//放置url链接
std::list<CString> Url;

GoodInf *mygood;     //设置购物车登录
CImage  image, dimage;
CToolBar m_ToolBar;  //创建一个toolbar工具栏
DECLARE_EVENTSINK_MAP()
void OnNewwindow3Explorer1(LPDISPATCH* ppDisp, BOOL* Cancel, unsigned long dwFlags, LPCTSTR bstrUrlContext, LPCTSTR bstrUrl);
afx_msg void OnNMThemeChangedScrollbar1(NMHDR *pNMHDR, LRESULT *pResult);
afx_msg void OnBnClickedGohead();
afx_msg void OnBnClickedGoback();
afx_msg void OnBnClickedRefresh();
afx_msg void OnFileOpen();
afx_msg void OnFileNew();
afx_msg void OnFileSave();
afx_msg void OnAddGood();
afx_msg void OnQuit();
afx_msg void OnTaskList();
afx_msg void OnSize(UINT nType, int cx, int cy);
afx_msg void OnLbnSelchangeList1();
afx_msg void OnStnClickedMenuUc();
afx_msg void MainMenu::OnNcPaint();
CStatic m_menu_uc;
int m_UserCenter;
afx_msg void OnStnClickedMenuSt();
afx_msg void OnStnClickedMenuTm();
afx_msg void OnStnClickedMenuPx();
afx_msg void OnStnClickedmenuLt();
};
