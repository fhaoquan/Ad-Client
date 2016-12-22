// _SetingMenu.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Kehu.h"
#include "_SetingMenu.h"
#include "afxdialogex.h"






// _SetingMenu �Ի���

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


// _SetingMenu ��Ϣ�������


void _SetingMenu::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
   if (IsIconic()){
	 
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon+1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);

	}
	else{ 
		 
	   CRect   rectA;   
           GetClientRect(&rectA);   
         
		   CDC   dcMem;   
           dcMem.CreateCompatibleDC(&dc);   
           CBitmap   bmpBackground;   
           bmpBackground.LoadBitmap(IDB_BITMAP35);   //IDB_BITMAP�����Լ���ͼ��Ӧ��ID   �������Ҹոռ����λͼ��Դ 
                                                     //������������IDB_Bg�������������bmpBackground.LoadBitmap(IDB_Bg);                 
           
		   BITMAP   bitmap;   
           bmpBackground.GetBitmap(&bitmap);   
           CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground);   
		   dc.StretchBlt(0,0,rectA.Width(),rectA.Height(),&dcMem,0,0,   
           bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);   
	      // CDialogEx::OnPaint();
	}
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}


//void _SetingMenu::OnInitMenu(CMenu* pMenu)
//{
//	CDialogEx::OnInitMenu(pMenu);
//
//	// TODO: �ڴ˴������Ϣ����������
//}


BOOL _SetingMenu::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	_m_menu_Userinf.SetWindowText(CString(al_username.c_str()));
	_m_menuId.SetWindowText(CString(al_loginId.c_str()));

	ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW,1);//����������
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


//��ҳ
void _SetingMenu::OnStnClickedStaticMainpage()
{

	
	client->GetBrowser()->GetMainFrame()->LoadURL(L"http://friend.py91178.com/Index/index.html");
	CDialog::OnOK();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

//ȥ������
void _SetingMenu::OnStnClickedStaticTasklist(){

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(manage.empty()) 
		manage="http://friend.py91178.com/Index/index.html";
	client->GetBrowser()->GetMainFrame()->LoadURL(manage.c_str());	
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnOK();
}

//�������
void _SetingMenu::OnStnClickedStaticOrderpage()
{
	
	if(order.empty()) 
		order="http://friend.py91178.com/Index/index.html";
	client->GetBrowser()->GetMainFrame()->LoadURL(order.c_str());
  CDialog::OnOK();
}

//�û�����
void _SetingMenu::OnStnClickedStaticUserpage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(center.empty()) 
		center="http://friend.py91178.com/Index/index.html";
	client->GetBrowser()->GetMainFrame()->LoadURL(center.c_str());
    CDialog::OnOK();
}

//�˺���Ϣ
void _SetingMenu::OnStnClickedStaticZhaoinf()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(userinf.empty()) 
		userinf="http://friend.py91178.com/Index/index.html";
	client->GetBrowser()->GetMainFrame()->LoadURL(userinf.c_str());
	CDialog::OnOK();
}

//��������
void _SetingMenu::OnStnClickedStaticShengshu()
{
		// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(helpcen.empty()) 
		helpcen="http://friend.py91178.com/Index/index.html";
  client->GetBrowser()->GetMainFrame()->LoadURL(helpcen.c_str());
	CDialog::OnOK();
}

//�ҵ���Ϣ
void _SetingMenu::OnStnClickedStaticMyinf()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(infor.empty()) 
		infor="http://friend.py91178.com/Index/index.html";
	client->GetBrowser()->GetMainFrame()->LoadURL(infor.c_str());
	CDialog::OnOK();
}


void _SetingMenu::OnStnClickedStaticStudyc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(study.empty()) 
		study="http://friend.py91178.com/Index/index.html";
	client->GetBrowser()->GetMainFrame()->LoadURL(study.c_str());
	CDialog::OnOK();
}


void _SetingMenu::OnStnClickedStaticHelpc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if(rpepage.empty()) 
		 rpepage="http://friend.py91178.com/Index/index.html";
	client->GetBrowser()->GetMainFrame()->LoadURL(rpepage.c_str());

  CDialog::OnOK();
}


int _SetingMenu::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	 CDialog::OnOK();
	return CDialogEx::OnMouseActivate(pDesktopWnd, nHitTest, message);
}


BOOL _SetingMenu::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: �ڴ����ר�ô����/����û���
	//if(lParam&WM_LBUTTONUP) CDialog::OnOK();
   return CDialogEx::OnCommand(wParam, lParam);
}


BOOL _SetingMenu::PreTranslateMessage(MSG* pMsg)
{
	//MessageBoxW(L"Menu");
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->message==WM_LBUTTONDOWN||pMsg->message==WM_RBUTTONDOWN
		||pMsg->message==WM_LBUTTONUP||pMsg->message==WM_RBUTTONUP){
		 
		CDialog::OnOK();
	}
	
	return CDialogEx::PreTranslateMessage(pMsg);
}


void _SetingMenu::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDialogEx::OnLButtonDown(nFlags, point);
}





