// MMenu.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Kehu.h"
#include "MMenu.h"
#include "afxdialogex.h"
#include "assert.h"
#include "TcpSocket.h"
#include "math.h"

extern CImage Resour;
extern struct usr ower;




// MMenu �Ի���
IMPLEMENT_DYNAMIC(MMenu, CDialogEx)

MMenu::MMenu(CWnd* pParent /*=NULL*/)
	: CDialogEx(MMenu::IDD, pParent)
{

	bo_back=0;
	setingmenu=NULL;
	_mouseflag=false;
	m_hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//����ͼƬID
	//��ɫ����
	hBitmapA = (HBITMAP)LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDB_BITMAP39),
		IMAGE_BITMAP, 0, 0,
		LR_LOADMAP3DCOLORS);
    //��ɫ����
	hBitmapA1 = (HBITMAP)LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDB_BITMAP42),
		IMAGE_BITMAP, 0, 0,
		LR_LOADMAP3DCOLORS);
	//��ɫǰ��
   hBitmapB = (HBITMAP)LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDB_BITMAP40),
		IMAGE_BITMAP, 0, 0,
		LR_LOADMAP3DCOLORS);
   //��ɫǰ��
   hBitmapB1 = (HBITMAP)LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDB_BITMAP43),
		IMAGE_BITMAP, 0, 0,
		LR_LOADMAP3DCOLORS);
}

MMenu::~MMenu()
{
	//KillTimer(TIMEMOUSE);
	//KillTimer(ONTIME);
	
	if(m_hWnd!=NULL)
		DestroyWindow();
}

void MMenu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GOBACK, m_GoBack);
	DDX_Control(pDX, IDC_GOHEAD, m_GoFward);
	DDX_Control(pDX, IDC_STATIC_Menu, _static_Menu);
}


BEGIN_MESSAGE_MAP(MMenu, CDialogEx)
	ON_WM_SIZE()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	//ON_WM_QUERYDRAGICON()
	ON_STN_CLICKED(IDB_Menu_ST, &MMenu::OnStnClickedMenuSt)
	ON_STN_CLICKED(IDB_Menu_TM, &MMenu::OnStnClickedMenuTm)
	ON_STN_CLICKED(IDC_Menu_PX, &MMenu::OnStnClickedMenuPx)
	ON_STN_CLICKED(IDC_Menu_UC, &MMenu::OnStnClickedMenuUc)
	ON_STN_CLICKED(IDC_menu_LT, &MMenu::OnStnClickedmenuLt)
	ON_STN_CLICKED(IDC_GOBACK, &MMenu::OnStnClickedGoback)
	ON_STN_CLICKED(IDC_GOHEAD, &MMenu::OnStnClickedGohead)
	ON_STN_CLICKED(IDC_REFRESH, &MMenu::OnStnClickedRefresh)
	ON_STN_CLICKED(ID_Task_TB, &MMenu::OnStnClickedTaskTB)
	ON_STN_CLICKED(ID_Task_TT, &MMenu::OnStnClickedTaskTT)
    ON_STN_CLICKED(ID_Task_JD, &MMenu::OnStnClickedTaskJD)	
	ON_STN_CLICKED(ID_Task_YHD, &MMenu::OnStnClickedTaskYHD)
	ON_STN_CLICKED(ID_Task_JMYP, &MMenu::OnStnClickedTaskJMYP)
	ON_STN_CLICKED(ID_Task_WPH, &MMenu::OnStnClickedTaskWPH)
	ON_STN_CLICKED(ID_Task_MGJ, &MMenu::OnStnClickedTaskMGJ)
	ON_STN_CLICKED(ID_Task_MLS, &MMenu::OnStnClickedTaskMLS)
	ON_STN_CLICKED(ID_Task_SNYG, &MMenu::OnStnClickedTaskSNYG)
//	ON_WM_DRAWITEM()
//ON_WM_SHOWWINDOW()
ON_STN_CLICKED(IDC_STATIC_Menu, &MMenu::OnStnClickedStaticMenu)
ON_WM_MOUSEACTIVATE()
ON_WM_LBUTTONDOWN()
ON_WM_MBUTTONDOWN()
ON_WM_RBUTTONDOWN()
ON_WM_MOUSEMOVE()
ON_WM_MOVE()
ON_WM_MOUSEMOVE()
ON_WM_NCMOUSEMOVE()
ON_WM_SHOWWINDOW()
ON_WM_CLOSE()
ON_WM_TIMER()
ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


BOOL MMenu::OnInitDialog()
{	

	
	CDialogEx::OnInitDialog();
	//�������ڴ�С
     cx1   =   GetSystemMetrics(SM_CXSCREEN);
     cy1   =   GetSystemMetrics(SM_CYSCREEN);
	 if(  Kehutmp.data > 0  ){
	     this->SetWindowPos(&wndTopMost,8,10,380,cy1-60,0);
	 }
	 else{
		 this->SetWindowPos(&wndNoTopMost,8,10,380,cy1-60,0);
	 }	   
	 CefSettingsTraits::init(&cSettings);
	 CefMainArgs main_args ( AfxGetApp()->m_hInstance ); 
	 cSettings.single_process=false;

#if !defined(CEF_USE_SANDBOX)
	 cSettings.no_sandbox = true;
#endif

	 cSettings.multi_threaded_message_loop= true;
	 cSettings.ignore_certificate_errors = true;      //���Ե�ssl֤����֤����
	 cSettings.command_line_args_disabled = true;
	  void* sandbox_info = NULL;

#if defined(CEF_USE_SANDBOX)
	  // Manage the life span of the sandbox information object. This is necessary
	  // for sandbox support on Windows. See cef_sandbox_win.h for complete details.
	  CefScopedSandboxInfo scoped_sandbox;
	  sandbox_info = scoped_sandbox.sandbox_info();
#endif
	 CefInitialize(main_args,cSettings, spApp,sandbox_info);
	 MainUrl="http://friend.yhtyt.com//Index/index.html";
	 client= CefRefPtr<CWebClient>(new CWebClient(MainUrl.c_str()));
	 manager = CefCookieManager::GetGlobalManager();
	 CefString(&cookie.name).FromASCII("PHPSESSID");
	 //SessinID+=+";client";
	 CefString(&cookie.value).FromASCII(SessinID.c_str());
	 CefString(&cookie.domain).FromASCII("friend.py91178.com");
	 CefString(&cookie.path).FromASCII("/");
	 cookie.has_expires = true;
	 cookie.expires.year = 2200;
	 cookie.expires.month = 12;
	 cookie.expires.day_of_week = 5;
	 cookie.expires.day_of_month = 31;
	 cookie.expires.hour=23;
	 cookie.expires.minute=59;
	 cookie.expires.second=59;
	 cookie.expires.millisecond=999;
	 CefPostTask(TID_IO, NewCefRunnableMethod(manager.get(), &CefCookieManager::SetCookie, CefString(MainUrl.c_str()), cookie));  

   //CefRunMessageLoop();
	//CefShutdown();

	/*
	if(  Kehutmp.data > 0  ){
		this->SetWindowPos(&wndTopMost,rect.left,rect.top,380,cy1-60,0);
	     //::SetWindowPos(this->m_hWnd,HWND_TOP,8,10,380,cy1-60,0); 
	}
	 else{
	  this->SetWindowPos(&wndNoTopMost,rect.left,rect.top,380,cy1-60,0);
	 //::SetWindowPos(this->m_hWnd,HWND_NOTOPMOST,8,10,380,cy1-60,0);
	 }
	*/
	 m_tasklist.LoadMenuW(IDR_MENU3);
	 RECT Arect;
	 RECT rectnew;
	 ::GetClientRect(this->m_hWnd, &Arect);
	 rectnew=Arect;
	 rectnew.top=Arect.top+94;
	 rectnew.bottom=Arect.bottom;
	 rectnew.left=Arect.left;
	 rectnew.right=Arect.right;
	 //info.SetAsChild(GetSafeHwnd(),rectnew);

	 client->SetHomePage(MainUrl.c_str());
	 client->CreateBrowser(this->m_hWnd,rectnew);

  int var =m_tcp.SocketStart();;
  if (var < 0) {
		//�˳�
	closesocket(m_tcp.sHost);	//�ر��׽���
	WSACleanup();		//�ͷ��׽�����Դ
	MessageBox(_T("�޷����ӷ���������������"), 0, 0);
	//throw std::exception("�޷����ӷ���������������");
	return false;
 }


	 //��ʼ��������Ϣ
	 char* addr = const_cast<char*>(loginMenu);
	 char* host = const_cast<char*>(hostaddr);
	 int post = 80;
	 m_tcp.sendinf(addr,host,NULL,post);
	 //������Ϣ
	  char recv_str[4096] = { 0 };
	 if (recv(m_tcp.sHost, recv_str, sizeof(recv_str), 0) == -1)
	 {
		 // cout << "recv failed" << endl;
		  closesocket(m_tcp.sHost);	//�ر��׽���
		  WSACleanup();		//�ͷ��׽�����Դ
		 MessageBox(_T("�����ַURL��ȡʧ�ܣ�"), 0, 0);
		 return false;
	 }
	 //���׽��ֹر�
	 closesocket(m_tcp.sHost);	//�ر��׽���
	 WSACleanup();	
//	 MessageBoxA(0,recv_str,"sss",0);
	 Json::Value troot;
	 Json::Reader reader;
	 Json::FastWriter fast_writer;

	 string sst = strstr(recv_str, "{");
	 if (!reader.parse(sst, troot, false)) {
		 MessageBox(_T("����׬��ַ������!\n"), 0, 0);
		 return false ;
	  }
	 	 // MessageBoxA(0,sst.c_str(),"sss",0);
	      string sst1 = strstr(sst.c_str(), "package");
	      sst1 = strstr(sst1.c_str(), "{");
	 	 // MessageBoxA(0,sst1.c_str(),"sss",0);
	  if (!reader.parse(sst1, troot, false)) {
		 MessageBox(_T("��Ҫ���ص�ҳ���ַ������!\n"), 0, 0);
		 return false ;
	  }
	   //MessageBoxA(0,sst1.c_str(),"sss",0);
	 order = troot["order"].asString();
	 // MessageBoxA(0,order.c_str(),"sss",0);
	 manage=troot["manage"].asString();
	 study =troot["study"].asString();
	 center =troot["center"].asString();
	 today_money = troot["today_money"].asString();;
	 userinf  =troot["user"].asString();  //�û���Ϣ
	 infor =  troot["info"].asString();  //��Ϣ����
	 rpepage = troot["help"].asString(); //��������
	 helpcen =  troot["rpe"].asString(); //��������
	 setpwdurl = troot["setpasswd"].asString();  //�����˺�URL
 	//SessinID+=+";client";
	//MessageBoxA(0,SessinID.c_str(),"PHPSESSID",0); 
	/*
	CefBrowserHost::CreateBrowser(info, static_cast<CefRefPtr<CefClient> >(client),
	MainUrl.c_str(),browserSettings,NULL);
	*/

	//Sleep(2000);   //��ֹ��ͼ���죬�����ҳ���ز���
	 //MessageBoxA(NULL, SessinID.c_str(), 0, 0);	
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	/*
	 ����������һ����ʱ��
	*/
	
	SetTimer(ONTIME,600000,0);		//10����ˢ��һ��
	SetTimer(TIMEMOUSE,2400,0);
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	//ShowWindow(SW_HIDE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}
// MMenu ��Ϣ�������

void MMenu::OnSysCommand(UINT nID, LPARAM lParam)
{
	
  CDialogEx::OnSysCommand(nID, lParam);
}


void MMenu::OnPaint(){

   	CPaintDC dc(this);
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
           bmpBackground.LoadBitmap(IDB_BITMAP24);   //IDB_BITMAP�����Լ���ͼ��Ӧ��ID   �������Ҹոռ����λͼ��Դ 
                                                     //������������IDB_Bg�������������bmpBackground.LoadBitmap(IDB_Bg);
		   //CClientDC dc(this);
		   BITMAP   bitmap;   
           bmpBackground.GetBitmap(&bitmap);   
           CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground);   
           dc.StretchBlt(0,0,rectA.Width(),94,&dcMem,0,0,   
           bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);   
		   RECT rect; 
		   this->GetClientRect(&rect);  
		  if(client.get()){
			CefRefPtr<CefBrowser>browser = client->GetBrowser();
			if(browser.get()){
				CefWindowHandle hwnd =  browser->GetHost()->GetWindowHandle();
		   // this->GetWindowRect(&rect);
		    ::MoveWindow( hwnd,rect.left,rect.top+94,rect.right-rect.left,abs(rect.bottom-rect.top-94), true); 
			::SetWindowPos(hwnd, HWND_TOPMOST, rect.left,rect.top+94,
                  rect.right-rect.left,abs(rect.bottom-rect.top-94), 0);
		  /*
		       CRect rect;
             this->GetWindowRect(&rect);  
		  //::MoveWindow( hwnd, 0, 0, cx, cy, true);  
		   //����Ⱦ�Ļ����������֮��
		 ::SetWindowPos(hwnd, HWND_TOPMOST+1, rect.left,rect.top+94,
                  rect.right-rect.left,abs(rect.bottom-rect.top-94), 0);
		 */
		 // ::MoveWindow( hwnd, 0, rect.top+94, rect.right-rect.left, abs(rect.bottom-rect.top-94), true);  
		//   CefRunMessageLoop();
	       
		  }   
	  }
	}
	 CDialogEx::OnPaint();   
}

/*
//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR MMenu::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
*/


void MMenu::OnSize(UINT nType, int cx,int cy)
{
	

	CDialogEx::OnSize(nType,cx,cy);
	if (nType == SIZE_MINIMIZED){
		ShowWindow(SW_MINIMIZE); // ����С���У�����������              
	}
	//TODO: �ڴ˴������Ϣ����������
	if(client.get())
	{
	
		CefRefPtr<CefBrowser>browser = client->GetBrowser();
		if(browser.get())
		{
			CRect rect;
			//GetWindowRect(&rect);
	       // browser->GetMainFrame()->LoadURL(MainUrl.c_str());
		  CefWindowHandle hwnd = browser->GetHost()->GetWindowHandle();
            this->GetClientRect(&rect);  
            ::MoveWindow( hwnd,cx,cy+94,rect.right-rect.left,abs(rect.bottom-rect.top-94), true);  
	        ::SetWindowPos(hwnd, HWND_TOPMOST, cx,cy+94,
                  rect.right-rect.left,abs(rect.bottom-rect.top-94), 0);
		}	 
  }
  
}
void MMenu::OnStnClickedMenuSt()
{

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	 //m_cWebClient->GetBrowser()->GetMainFrame()->LoadURL(L"http://friend.py91178.com/Task/hall.html");
    	MainUrl=order;
	    client->GetBrowser()->GetMainFrame()->LoadURL(MainUrl.c_str());
	//  HINSTANCE r = ShellExecute(NULL, L"open",L"www.taobao.com ", NULL, NULL, SW_SHOWNORMAL);
		  
}


void MMenu::OnStnClickedMenuTm()
{
	
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	  MainUrl=manage;
	 client->GetBrowser()->GetMainFrame()->LoadURL(MainUrl.c_str());
	 //m_cWebClient->GetBrowser()->GetMainFrame()->LoadURL(L"http://203.195.192.24/Task/manage.html");
	
}


void MMenu::OnStnClickedMenuPx()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	  MainUrl=study;
	client->GetBrowser()->GetMainFrame()->LoadURL(MainUrl.c_str());
	 //m_cWebClient->GetBrowser()->GetMainFrame()->LoadURL(L"http://203.195.192.24#");
	
}


void MMenu::OnStnClickedMenuUc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	  MainUrl=center;
	 client->GetBrowser()->GetMainFrame()->LoadURL(MainUrl.c_str());
	//m_cWebClient->GetBrowser()->GetMainFrame()->LoadURL(L"http://203.195.192.24/Center/index.html");
	
}

void MMenu::OnStnClickedmenuLt()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// TODO: Add your message handler code here and/or call default
	 CMenu *pPopup=m_tasklist.GetSubMenu(0);
	 CRect rectR;
     GetDlgItem(IDC_menu_LT)->GetWindowRect(&rectR);//��ȡ�ؼ��������Ļ��λ��
     //ScreenToClient(rectR);//ת��Ϊ�Ի����ϵ����λ��
	 //��ȡ������ͼ���λ��
    //��ʾ�Ҽ��˵��������ര��ӵ�С�
	 pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,rectR.right,rectR.bottom,this);
	
}

void MMenu::OnStnClickedGoback()
{ 
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	client->GetBrowser()->GoBack();
    
}

void MMenu::OnStnClickedGohead()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	client->GetBrowser()->GoForward();
	
}

void MMenu::OnStnClickedRefresh()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	client->GetBrowser()->Reload();
}


void MMenu::ShowTopOrNot(){

   //��ȡ��ǰ����λ��
	//CRect rect;
    //GetWindowRect(&rect);
	if(  Kehutmp.data > 0  ){
	   this->SetWindowPos(&wndTopMost,rect.left,rect.top,380,cy1-60,0);
	  //::SetWindowPos(this->m_hWnd,HWND_TOPMOST,rect.left,rect.top,380,cy1-60,0); 
	}
	 else{
		 this->SetWindowPos(&wndNoTopMost,rect.left,rect.top,380,cy1-60,0);
	 //::SetWindowPos(this->m_hWnd,HWND_NOTOPMOST,rect.left,rect.top,380,cy1-60,0);
	 }

}

void MMenu::ONRUN(){

if(client.get()){
	CefRefPtr<CefBrowser>browser = client->GetBrowser();
if(browser.get()){
  if(client->GetBrowser()->CanGoBack())
		 m_GoBack.SetBitmap(hBitmapA1);
	else
		 m_GoBack.SetBitmap(hBitmapA);
 if(client->GetBrowser()->CanGoForward())
		m_GoFward.SetBitmap(hBitmapB1);
	else
	    m_GoFward.SetBitmap(hBitmapB);
	UpdateData();
	}
}
}

void MMenu::OnStnClickedTaskTB(){
	 HINSTANCE r = ShellExecute(NULL, L"open",L"http://www.taobao.com", NULL, NULL, SW_SHOWNORMAL);
}

void MMenu::OnStnClickedTaskTT(){
   HINSTANCE r = ShellExecute(NULL, L"open",L"https://www.tmall.com/", NULL, NULL, SW_SHOWNORMAL);
}
void MMenu::OnStnClickedTaskJD(){

	HINSTANCE r = ShellExecute(NULL, L"open",L"http://www.jd.com/", NULL, NULL, SW_SHOWNORMAL);
}

void MMenu::OnStnClickedTaskYHD(){
 
  HINSTANCE r = ShellExecute(NULL, L"open",L"http://www.yhd.com/", NULL, NULL, SW_SHOWNORMAL);
}

void MMenu::OnStnClickedTaskJMYP(){
 
  HINSTANCE r = ShellExecute(NULL, L"open",L"http://sh.jumei.com/", NULL, NULL, SW_SHOWNORMAL);
}

void MMenu::OnStnClickedTaskWPH(){
 
HINSTANCE r = ShellExecute(NULL, L"open",L"http://www.vip.com/", NULL, NULL, SW_SHOWNORMAL);
}

void MMenu::OnStnClickedTaskMGJ(){
 
	HINSTANCE r = ShellExecute(NULL, L"open",L"http://www.mogujie.com/", NULL, NULL, SW_SHOWNORMAL);
}

void MMenu::OnStnClickedTaskMLS(){
 
	  HINSTANCE r = ShellExecute(NULL, L"open",L"http://www.meilishuo.com/", NULL, NULL, SW_SHOWNORMAL);
}


void MMenu::OnStnClickedTaskSNYG(){
 
	  HINSTANCE r = ShellExecute(NULL, L"open",L"http://www.suning.com/", NULL, NULL, SW_SHOWNORMAL);
	
}

void MMenu::OnStnClickedStaticMenu()
{
	if(setingmenu!=NULL){
		setingmenu->DestroyWindow();
		delete setingmenu;
		setingmenu=NULL;
	}

	setingmenu = new  _SetingMenu();
	setingmenu->Create(IDD_DIALOG2,this);
	bo_back=1;  //���������Ҫ��ʾ������
	
	//��ȡ�ؼ���λ��
	//POINT  _mouse;
	//GetCursorPos(&_mouse);
	

	CRect rectL,rect;
	 GetClientRect(&rectL);//��ȡ�Ի���ͻ������С  
    ClientToScreen(&rectL);//ת��ΪӫĻ����  
	int x= GetSystemMetrics(SM_CXSCREEN);//��ȡӫĻ����Ŀ�ȣ���λΪ����  
    int y=  GetSystemMetrics(SM_CYSCREEN);//��ȡӫĻ����ĸ߶ȣ���λΪ����  

	setingmenu->GetClientRect(rect);
	if(30>=x-rect.Width()-rectL.right)
		 setingmenu->SetWindowPos(&wndTopMost,rectL.left+130,rectL.top+70,rect.Width(),rect.Height(),0);
	 else
	     setingmenu->SetWindowPos(&wndTopMost,rectL.right+8,rectL.top+70,rect.Width(),rect.Height(),0);
	setingmenu->ShowWindow(SW_SHOW);
	setingmenu->SetFocus();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

//�ⲿ���������ҳ�渲�����⣬�������ڽ������
BOOL MMenu::OnEraseBkgnd(CDC* pDC){
	//return TRUE;
	return FALSE;
}

int MMenu::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	/*
    if(setingmenu!=NULL){
		setingmenu->DestroyWindow();
		delete setingmenu;
		setingmenu=NULL;
	}
	*/
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return CDialogEx::OnMouseActivate(pDesktopWnd, nHitTest, message);
}


void MMenu::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	/*
		if(setingmenu!=NULL){
		setingmenu->DestroyWindow();
		delete setingmenu;
		setingmenu=NULL;
	}
	*/
	CDialogEx::OnLButtonDown(nFlags, point);
}


void MMenu::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
/*	
	if(setingmenu!=NULL){
		setingmenu->DestroyWindow();
		delete setingmenu;
		setingmenu=NULL;
	}
*/
	CDialogEx::OnMButtonDown(nFlags, point);
}


void MMenu::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	/*
		if(setingmenu!=NULL){
		setingmenu->DestroyWindow();
		delete setingmenu;
		setingmenu=NULL;
	}
	*/
	CDialogEx::OnRButtonDown(nFlags, point);
}

void MMenu::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);
		if(client.get())
		{

		CefRefPtr<CefBrowser>browser = client->GetBrowser();
		if(browser.get())
		{
	       // browser->GetMainFrame()->LoadURL(MainUrl.c_str());
		  CefWindowHandle hwnd = browser->GetHost()->GetWindowHandle(); 
          CRect rect;
		  this->GetClientRect(&rect);  
           
          //GetWindowRect(&rect);  
		   /*
		    ::MoveWindow( hwnd,x,y+94,
                  rect.right-rect.left,abs(rect.bottom-rect.top-94),true);  
		     */
		    ::MoveWindow( hwnd,x+999999,y+999999,rect.right-rect.left,abs(rect.bottom-rect.top-94),true); 
		   //����Ⱦ�Ļ����������֮��
		   ::SetWindowPos(hwnd, HWND_TOPMOST,x,y,
                    rect.right-rect.left,abs(rect.bottom-rect.top-94),0);
		}	 
  }
	// TODO: �ڴ˴������Ϣ����������
}

void MMenu::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
/*		CRect rect;
    GetWindowRect(&rect);
	/* �ж�����Ƿ��ڶԻ����У�����ڲ�������,�򽫴���ֻ����Ϊ�ö� */
    //CString cstd;
	//cstd.Format(L"%d %d %d %d %d %d",rect.left ,rect.right,rect.top,rect.bottom,point.x,point.y);
	//MessageBox(cstd);
	/*
	if(point.x>rect.left&&point.x<rect.right
		&&point.y>rect.top&&point.y<rect.bottom){
			if(!_mouseflag){
				_mouseflag=true;
	    this->SetWindowPos(&wndNoTopMost,rect.left,rect.top,380,cy1-60,0);
	  }
	}
	else if(_mouseflag){
	 	_mouseflag=false; 
		 ShowTopOrNot();
	}
*/
	CDialogEx::OnMouseMove(nFlags, point);
}


void MMenu::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
/*
	CRect rect;
    GetWindowRect(&rect);
	/* �ж�����Ƿ��ڶԻ����У�����ڲ�������,�򽫴���ֻ����Ϊ�ö� */
    //CString cstd;
	//cstd.Format(L"%d %d %d %d %d %d",rect.left ,rect.right,rect.top,rect.bottom,point.x,point.y);
	//MessageBox(cstd);
/*
	if(point.x>rect.left&&point.x<rect.right
		&&point.y>rect.top&&point.y<rect.bottom){
			if(!_mouseflag){
				_mouseflag=true;
	    this->SetWindowPos(&wndNoTopMost,rect.left,rect.top,380,cy1-60,0);
	  }
	}
	else if(_mouseflag){
	 	_mouseflag=false; 
		 ShowTopOrNot();
	}
  */
	CDialogEx::OnNcMouseMove(nHitTest, point);
}


void MMenu::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: �ڴ˴������Ϣ����������
}


BOOL MMenu::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
   /*	
	if(pMsg->message==WM_CLOSE||pMsg->message==SW_HIDE||pMsg->message==SW_MINIMIZE){
		KillTimer(TIMEMOUSE);
	}
	if(pMsg->message==SW_SHOW||pMsg->message==SW_SHOWNORMAL){
	   	KillTimer(TIMEMOUSE);
		SetTimer(TIMEMOUSE,10,0);
	}
	*/
	return CDialogEx::PreTranslateMessage(pMsg);
}


void MMenu::OnClose(){
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//KillTimer(TIMEMOUSE);
	CDialogEx::OnClose();
}


void MMenu::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent){

	 case ONTIME:
		 CefPostTask(TID_IO, NewCefRunnableMethod(manager.get(), &CefCookieManager::SetCookie, CefString(MainUrl.c_str()), cookie));
		 break;
    case TIMEMOUSE:   {
	 GetCursorPos(&point);
     GetWindowRect(&rect);
	/* �ж�����Ƿ��ڶԻ����У�����ڲ�������,�򽫴���ֻ����Ϊ�ö� */
    //CString cstd;
	//cstd.Format(L"%d %d %d %d %d %d",rect.left ,rect.right,rect.top,rect.bottom,point.x,point.y);
	//MessageBox(cstd);
	if(point.x>rect.left&&point.x<rect.right
		&&point.y>rect.top&&point.y<rect.bottom){
		  if(!_mouseflag){
				_mouseflag=true;
	      this->SetWindowPos(&wndNoTopMost,rect.left,rect.top,380,cy1-60,0);
		  }
	}
	else{
		if(_mouseflag){
	 	_mouseflag=false; 
		ShowTopOrNot();
	   }
	}

	if(client.get()){
	CefRefPtr<CefBrowser>browser = client->GetBrowser();
  if(browser.get()){
     if(client->GetBrowser()->CanGoBack())
	   	 m_GoBack.SetBitmap(hBitmapA1);
	else
		 m_GoBack.SetBitmap(hBitmapA);
 if(client->GetBrowser()->CanGoForward())
		m_GoFward.SetBitmap(hBitmapB1);
	else
	    m_GoFward.SetBitmap(hBitmapB);
	UpdateData();
	// Sleep(30);
   }
	}
  } break;
   default : break;
  }
	CDialogEx::OnTimer(nIDEvent);
}


void MMenu::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	CDialogEx::OnLButtonUp(nFlags, point);
}

