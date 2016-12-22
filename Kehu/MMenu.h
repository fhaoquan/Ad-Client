#pragma once
#include<cef_client.h>
#include "CWebClient.h"
#include <cef_app.h>
#include "afxwin.h"
#include "TcpSocket.h"
#include"json\json.h"
#include"_SetingMenu.h"
// MMenu 对话框
#include "include/cef_sandbox_win.h"
#if defined(CEF_USE_SANDBOX)
#pragma comment(lib, "cef_sandbox.lib")
#endif


class MMenu : public CDialogEx
{
	DECLARE_DYNAMIC(MMenu)

private:

	//CefWindowInfo info;
    
    //CefBrowserSettings browserSettings;
	void ONRUN();

public:
	MMenu(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MMenu();

// 对话框数据
	enum { IDD = IDD_DIALOG5 };

protected:
	 virtual BOOL OnEraseBkgnd(CDC* pDC);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	HICON m_hIcon;
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	//afx_msg HCURSOR OnQueryDragIcon();	
	DECLARE_MESSAGE_MAP()
public:

//	CefRefPtr<CWebClient>  m_cWebClient;
	afx_msg void OnStnClickedMenuSt();
	afx_msg void OnStnClickedMenuTm();
	afx_msg void OnStnClickedMenuPx();
	afx_msg void OnStnClickedMenuUc();
	afx_msg void OnStnClickedmenuLt();
	afx_msg void OnStnClickedGoback();
	afx_msg void OnStnClickedGohead();
	afx_msg void OnStnClickedRefresh();
	afx_msg void OnStnClickedTaskTB();
	afx_msg void OnStnClickedTaskTT();
	afx_msg void OnStnClickedTaskJD();
    afx_msg void OnStnClickedTaskYHD();
    afx_msg void OnStnClickedTaskJMYP();
	afx_msg void OnStnClickedTaskWPH();
    afx_msg void OnStnClickedTaskMGJ();
    afx_msg void OnStnClickedTaskMLS();
	afx_msg void OnStnClickedTaskSNYG();
	afx_msg void OnSize(UINT nType, int cx, int cy);
 
	CMenu m_tasklist;
	TcpSocket m_tcp;
	CRect m_rect;  //为了恢复区域
	CStatic m_GoBack;
	CStatic m_GoFward;
	bool _mouseflag;
	HBITMAP hBitmapA,hBitmapA1,hBitmapB,hBitmapB1;
//	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
//	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnStnClickedStaticMenu();
	CStatic _static_Menu;

	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnMove(int x, int y);
	void ShowTopOrNot();

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point); 
	
	POINT point;
	 CRect rect;
	 bool bo_back;  //判断是不是点击了响应的时间信息
     _SetingMenu  * setingmenu;
};

