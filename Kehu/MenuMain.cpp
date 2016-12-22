// MenuMain.cpp : 实现文件
//

#include "stdafx.h"
#include "Kehu.h"
#include "MenuMain.h"
#include "afxdialogex.h"


// MenuMain 对话框

IMPLEMENT_DYNAMIC(MenuMain, CDialogEx)

MenuMain::MenuMain(CWnd* pParent /*=NULL*/)
	: CDialogEx(MenuMain::IDD, pParent)
{

}

MenuMain::~MenuMain()
{
}

void MenuMain::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MenuMain, CDialogEx)
	ON_STN_CLICKED(IDB_Menu_TM, &MenuMain::OnStnClickedMenuTm)
	ON_STN_CLICKED(IDB_Menu_ST, &MenuMain::OnStnClickedMenuSt)
	ON_STN_CLICKED(IDC_Menu_PX, &MenuMain::OnStnClickedMenuPx)
	ON_STN_CLICKED(IDC_Menu_UC, &MenuMain::OnStnClickedMenuUc)
	ON_STN_CLICKED(IDC_menu_LT, &MenuMain::OnStnClickedmenuLt)
	ON_STN_CLICKED(IDC_REFRESH, &MenuMain::OnStnClickedRefresh)
	ON_STN_CLICKED(IDC_GOHEAD, &MenuMain::OnStnClickedGohead)
	ON_STN_CLICKED(IDC_GOBACK, &MenuMain::OnStnClickedGoback)
END_MESSAGE_MAP()


// MenuMain 消息处理程序


void MenuMain::OnStnClickedMenuTm()
{
	// TODO: 在此添加控件通知处理程序代码
}


void MenuMain::OnStnClickedMenuSt()
{
	// TODO: 在此添加控件通知处理程序代码
}


void MenuMain::OnStnClickedMenuPx()
{
	// TODO: 在此添加控件通知处理程序代码
}


void MenuMain::OnStnClickedMenuUc()
{
	// TODO: 在此添加控件通知处理程序代码
}


void MenuMain::OnStnClickedmenuLt()
{
	// TODO: 在此添加控件通知处理程序代码
}


void MenuMain::OnStnClickedRefresh()
{
	// TODO: 在此添加控件通知处理程序代码
}


void MenuMain::OnStnClickedGohead()
{
	// TODO: 在此添加控件通知处理程序代码
}


void MenuMain::OnStnClickedGoback()
{
	// TODO: 在此添加控件通知处理程序代码
}
