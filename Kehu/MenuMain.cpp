// MenuMain.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Kehu.h"
#include "MenuMain.h"
#include "afxdialogex.h"


// MenuMain �Ի���

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


// MenuMain ��Ϣ�������


void MenuMain::OnStnClickedMenuTm()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void MenuMain::OnStnClickedMenuSt()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void MenuMain::OnStnClickedMenuPx()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void MenuMain::OnStnClickedMenuUc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void MenuMain::OnStnClickedmenuLt()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void MenuMain::OnStnClickedRefresh()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void MenuMain::OnStnClickedGohead()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void MenuMain::OnStnClickedGoback()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
