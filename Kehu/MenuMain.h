#pragma once


// MenuMain 对话框

class MenuMain : public CDialogEx
{
	DECLARE_DYNAMIC(MenuMain)

public:
	MenuMain(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MenuMain();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedMenuTm();
	afx_msg void OnStnClickedMenuSt();
	afx_msg void OnStnClickedMenuPx();
	afx_msg void OnStnClickedMenuUc();
	afx_msg void OnStnClickedmenuLt();
	afx_msg void OnStnClickedRefresh();
	afx_msg void OnStnClickedGohead();
	afx_msg void OnStnClickedGoback();
};
