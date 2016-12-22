// _SetingMenu.cpp : 实现文件
//

#include "stdafx.h"
#include "Kehu.h"
#include "_SetingMenu.h"
#include "afxdialogex.h"






// _SetingMenu 对话框

IMPLEMENT_DYNAMIC(_SetingMenu, CDialogEx)

_SetingMenu::_SetingMenu(CWnd* pParent /*=NULL*/)
	: CDialogEx(_SetingMenu::IDD, pParent)
{
	go_head=0;
	m_hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

_SetingMenu::~_SetingMenu()
{

	if(m_hWnd!=NULL)
		DestroyWindow();
}

void _SetingMenu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_MENUID, _m_menuId);
	DDX_Control(pDX, IDC_STATIC_User, _m_menu_Userinf);
	DDX_Control(pDX, IDC_STATIC_TitlePic, _menu_pic);
}


BEGIN_MESSAGE_MAP(_SetingMenu, CDialogEx)
	ON_WM_PAINT()
//	ON_WM_INITMENU()
ON_STN_CLICKED(IDC_STATIC_MainPage, &_SetingMenu::OnStnClickedStaticMainpage)
ON_STN_CLICKED(IDC_STATIC_Tasklist, &_SetingMenu::OnStnClickedStaticTasklist)
ON_STN_CLICKED(IDC_STATIC_Orderpage, &_SetingMenu::OnStnClickedStaticOrderpage)
ON_STN_CLICKED(IDC_STATIC_UserPage, &_SetingMenu::OnStnClickedStaticUserpage)
ON_STN_CLICKED(IDC_STATIC_ZHaoinf, &_SetingMenu::OnStnClickedStaticZhaoinf)
ON_STN_CLICKED(IDC_STATIC_Shengshu, &_SetingMenu::OnStnClickedStaticShengshu)
ON_STN_CLICKED(IDC_STATIC_MyInf, &_SetingMenu::OnStnClickedStaticMyinf)
ON_STN_CLICKED(IDC_STATIC_StudyC, &_SetingMenu::OnStnClickedStaticStudyc)
ON_STN_CLICKED(IDC_STATIC_HelpC, &_SetingMenu::OnStnClickedStaticHelpc)
ON_WM_MOUSEACTIVATE()
ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// _SetingMenu 消息处理程序


void _SetingMenu::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
   if (IsIconic()){
	 
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon+1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);

	}
	else{ 
		 
	   CRect   rectA;   
           GetClientRect(&rectA);   
         
		   CDC   dcMem;   
           dcMem.CreateCompatibleDC(&dc);   
           CBitmap   bmpBackground;   
           bmpBackground.LoadBitmap(IDB_BITMAP35);   //IDB_BITMAP是你自己的图对应的ID   ，由于我刚刚加入的位图资源 
                                                     //被我命名成了IDB_Bg，因而我这句就是bmpBackground.LoadBitmap(IDB_Bg);                 
           
		   BITMAP   bitmap;   
           bmpBackground.GetBitmap(&bitmap);   
           CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground);   
		   dc.StretchBlt(0,0,rectA.Width(),rectA.Height(),&dcMem,0,0,   
           bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);   
	      // CDialogEx::OnPaint();
	}
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
}


//void _SetingMenu::OnInitMenu(CMenu* pMenu)
//{
//	CDialogEx::OnInitMenu(pMenu);
//
//	// TODO: 在此处添加消息处理程序代码
//}


BOOL _SetingMenu::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// TODO:  在此添加额外的初始化
	_m_menu_Userinf.SetWindowText(CString(al_username.c_str()));
	_m_menuId.SetWindowText(CString(al_loginId.c_str()));

	ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW,1);//任务栏隐藏
	// TODO: 在此添加额外的初始化代码
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


//首页
void _SetingMenu::OnStnClickedStaticMainpage()
{

	
	client->GetBrowser()->GetMainFrame()->LoadURL(L"http://friend.py91178.com/Index/index.html");
	CDialog::OnOK();
	// TODO: 在此添加控件通知处理程序代码
}

//去领任务
void _SetingMenu::OnStnClickedStaticTasklist(){

	// TODO: 在此添加控件通知处理程序代码
	if(manage.empty()) 
		manage="http://friend.py91178.com/Index/index.html";
	client->GetBrowser()->GetMainFrame()->LoadURL(manage.c_str());	
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}

//任务管理
void _SetingMenu::OnStnClickedStaticOrderpage()
{
	
	if(order.empty()) 
		order="http://friend.py91178.com/Index/index.html";
	client->GetBrowser()->GetMainFrame()->LoadURL(order.c_str());
  CDialog::OnOK();
}

//用户中心
void _SetingMenu::OnStnClickedStaticUserpage()
{
	// TODO: 在此添加控件通知处理程序代码
	if(center.empty()) 
		center="http://friend.py91178.com/Index/index.html";
	client->GetBrowser()->GetMainFrame()->LoadURL(center.c_str());
    CDialog::OnOK();
}

//账号信息
void _SetingMenu::OnStnClickedStaticZhaoinf()
{
	// TODO: 在此添加控件通知处理程序代码
	if(userinf.empty()) 
		userinf="http://friend.py91178.com/Index/index.html";
	client->GetBrowser()->GetMainFrame()->LoadURL(userinf.c_str());
	CDialog::OnOK();
}

//申诉中心
void _SetingMenu::OnStnClickedStaticShengshu()
{
		// TODO: 在此添加控件通知处理程序代码
	if(helpcen.empty()) 
		helpcen="http://friend.py91178.com/Index/index.html";
  client->GetBrowser()->GetMainFrame()->LoadURL(helpcen.c_str());
	CDialog::OnOK();
}

//我的消息
void _SetingMenu::OnStnClickedStaticMyinf()
{
	// TODO: 在此添加控件通知处理程序代码
	if(infor.empty()) 
		infor="http://friend.py91178.com/Index/index.html";
	client->GetBrowser()->GetMainFrame()->LoadURL(infor.c_str());
	CDialog::OnOK();
}


void _SetingMenu::OnStnClickedStaticStudyc()
{
	// TODO: 在此添加控件通知处理程序代码
	if(study.empty()) 
		study="http://friend.py91178.com/Index/index.html";
	client->GetBrowser()->GetMainFrame()->LoadURL(study.c_str());
	CDialog::OnOK();
}


void _SetingMenu::OnStnClickedStaticHelpc()
{
	// TODO: 在此添加控件通知处理程序代码

	if(rpepage.empty()) 
		 rpepage="http://friend.py91178.com/Index/index.html";
	client->GetBrowser()->GetMainFrame()->LoadURL(rpepage.c_str());

  CDialog::OnOK();
}


int _SetingMenu::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	 CDialog::OnOK();
	return CDialogEx::OnMouseActivate(pDesktopWnd, nHitTest, message);
}


BOOL _SetingMenu::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类
	//if(lParam&WM_LBUTTONUP) CDialog::OnOK();
   return CDialogEx::OnCommand(wParam, lParam);
}


BOOL _SetingMenu::PreTranslateMessage(MSG* pMsg)
{
	//MessageBoxW(L"Menu");
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message==WM_LBUTTONDOWN||pMsg->message==WM_RBUTTONDOWN
		||pMsg->message==WM_LBUTTONUP||pMsg->message==WM_RBUTTONUP){
		 
		CDialog::OnOK();
	}
	
	return CDialogEx::PreTranslateMessage(pMsg);
}


void _SetingMenu::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialogEx::OnLButtonDown(nFlags, point);
}





