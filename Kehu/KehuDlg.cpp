// KehuDlg.cpp : �����n
#include "stdafx.h"
#include "Kehu.h"
#include "KehuDlg.h"
#include "Winsock2.h"
#include "afxdialogex.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"
#include "Resource.h"
#include "cstringt.h"
#include <afxinet.h>
#include "json\json.h"
#include <string>
#include <windows.h>
#include "cmd5.h"
#include "GetSysInfo.h"
#include "WMI_DeviceQuery.h"
#include "allvar.h"
#include <winuser.h>

//#define Debug_1
//#include"common.h"

#define		UM_TRAYNOTIFY WM_USER + 11  //���̺���
#define		M_TIMERE    23456
#define		BT_LINK_ACCOUNT		40001
#define     ISTrue  1
//#pragma comment(lib,"jsonlib.lib")
using namespace std;
extern struct usr cm_ower;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/*  
 ȫ�ֱ�����ȫ�ֺ�������  
 �趨һ�����ͼ����ӱ���
*/  

MMenu  *Mmdlg;  //����ȫ�ֱ���
HHOOK hhookmy ;  
LRESULT CALLBACK LowLevelMouseProc (INT nCode, WPARAM wParam, LPARAM lParam);  
BOOL UninstallKbHook();  
BOOL InstallKbHook();  


// CKehuDlg ��Ԓ���K

CKehuDlg::CKehuDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKehuDlg::IDD, pParent)
{
 if(hMutex[1]&&hMutex[2]==NULL&&hMutex[3]==NULL){
  	hhookmy = NULL;  //�趨����Ϊ��
	judCenter=0;
	tesinf=ptinf=wuser="";
	Mmdlg=NULL;
	//Mgobfor=NULL;
	//Mjietu=NULL;
	m_news=NULL;
	tm_var = 1;  //�趨Ϊ1��
	IsLogin = FALSE;
	ISFirst = TRUE;
	menuid = -1;
	pmenu = NULL;
	reAuto=0;  //Ĭ��Ϊ��¼״̬
	UlMenu.LoadMenu(IDR_MENU1);
	menuTray.LoadMenu(IDR_MENU_TRAY);
	memset(&m_nid, 0, sizeof(m_nid)); // Initialize NOTIFYICONDATA struct
	//memset(&tmmlog,0,sizeof(Login));      //����ļ�
	m_nid.cbSize = sizeof(m_nid);
    m_nid.hWnd = this->m_hWnd;
	m_nid.uCallbackMessage = UM_TRAYNOTIFY;//��Ϣ��
	m_nid.uFlags = NIF_ICON|NIF_TIP|NIF_MESSAGE;
	StrCpy(m_nid.szTip, L"����׬");     /*����������ʾ����׬*/
	//Shell_NotifyIcon(NIM_ADD, &m_nid);//�������ͼ�� 
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	}

}


CKehuDlg::~CKehuDlg(){
	
   //   KillTimer(M_TIMERA);				//�ͷŶ�ʱ��
   //   KillTimer(M_TIMERC);
    if(Mmdlg!=NULL){
				Mmdlg->DestroyWindow();
				delete Mmdlg;
				Mmdlg=NULL;
}
		UninstallKbHook();
	 //Shell_NotifyIcon(NIM_DELETE, &m_nid);
	
}

void CKehuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//�����������ݱ���var
	DDX_Control(pDX, IDC_STATIC_YZM, Yzm_Bitmap);
	DDX_Control(pDX, IDC_EDIT_USER, UserName);
	DDX_Control(pDX, IDC_EDIT_PSW, PassWord);
	DDX_Control(pDX, IDC_EDIT_YZM, Yanzma);
	//DDX_Control(pDX, IDC_CHECK1, m_check_ps);
	DDX_Control(pDX, IDC_CHECK2, m_check_dl);
	DDX_Control(pDX, IDC_STATIC_ZC, m_text_zh);
	DDX_Control(pDX, IDC_STATIC_WJMM, m_text_wjmm);
	DDX_Control(pDX, IDOK, m_button_login);
	DDX_Control(pDX, IDCANCEL, m_button_cance);
	DDX_Control(pDX, IDC_BUTTON1, LCance);
}

BEGIN_MESSAGE_MAP(CKehuDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_HOTKEY,OnHotKey)  //��Ӵ˾�
	ON_MESSAGE(UM_TRAYNOTIFY, &CKehuDlg::OnTrayNotify)
   // ON_EN_CHANGE(IDC_EDIT3, &CKehuDlg::OnEnChangeEdit3)
    ON_BN_CLICKED(IDOK, &CKehuDlg::OnBnClickedOk)
    ON_BN_CLICKED(IDCANCEL, &CKehuDlg::OnBnClickedCancel)
    ON_BN_CLICKED(IDC_BUTTON1, &CKehuDlg::OnBnClickedButton1)
   // ON_EN_CHANGE(IDC_EDIT1, &CKehuDlg::OnEnChangeEdit1)
    ON_STN_CLICKED(IDC_STATIC_YZM, &CKehuDlg::OnStnClickedStaticYzm)
    ON_STN_CLICKED(IDC_STATIC_Title, &CKehuDlg::OnStnClickedStaticTitle)
    ON_EN_CHANGE(IDC_EDIT_USER, &CKehuDlg::OnEnChangeEditUser)
    ON_EN_CHANGE(IDC_EDIT_YZM, &CKehuDlg::OnEnChangeEditYzm)
    ON_STN_CLICKED(IDC_STATIC_touxiang, &CKehuDlg::OnStnClickedStatictouxiang)
    ON_EN_CHANGE(IDC_EDIT_PSW, &CKehuDlg::OnEnChangeEditPsw)
ON_WM_TIMER()
ON_WM_SHOWWINDOW()
ON_WM_CHAR()
//ON_COMMAND(IDR_BAR_JIETU, &CKehuDlg::OnIdrBarJietu)
ON_WM_CLOSE()
ON_CBN_SELCHANGE(IDC_EDIT_USER, &CKehuDlg::OnCbnSelchangeEditUser)
//ON_BN_CLICKED(IDC_CHECK1, &CKehuDlg::OnBnClickedCheck1)
ON_BN_CLICKED(IDC_CHECK2, &CKehuDlg::OnBnClickedCheck2)
ON_STN_CLICKED(IDC_STATIC_ZC, &CKehuDlg::OnStnClickedStaticZc)
ON_STN_CLICKED(IDC_STATIC_WJMM, &CKehuDlg::OnStnClickedStaticWjmm)
/*
ON_STN_CLICKED(IDR_TRAY_EXIT,&CKehuDlg::OnTRAY_EXIT)
ON_STN_CLICKED(IDR_TRAY_RESTORE,&CKehuDlg::ONTRAY_RESTORE)
ON_STN_CLICKED(IDD_BAR_IE ,&CKehuDlg::OBBARIE)
ON_STN_CLICKED(IDR_BAR_HUOBI  ,&CKehuDlg::BAR_HUOBI )
ON_STN_CLICKED(IDR_BAR_LLQ ,&CKehuDlg::BAR_LLQ )
ON_STN_CLICKED(IDR_BAR_SCGZ,&CKehuDlg::BAR_SCGZ)
ON_STN_CLICKED(IDR_BAR_GL,&CKehuDlg::BAR_GL)
ON_STN_CLICKED(IDR_BAR_LTT ,&CKehuDlg::BAR_LTT)
ON_STN_CLICKED(IDR_BAR_GMLB ,&CKehuDlg::BAR_GMLB)
ON_STN_CLICKED(ID_BAR_TS ,&CKehuDlg::BAR_TS)
ON_STN_CLICKED(IDR_BAR_ZQZY ,&CKehuDlg::BAR_ZQZY)
ON_STN_CLICKED(IDR_BAR_QMSZ ,&CKehuDlg::BAR_QMSZ)
*/
ON_WM_CTLCOLOR()
ON_WM_LBUTTONDOWN()
ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()



// CKehuDlg ӍϢ̎��ʽ
BOOL CKehuDlg::OnInitDialog()
{

 if(hMutex[1]!=NULL&&hMutex[2]==NULL&&hMutex[3]==NULL){
	InstallKbHook(); //��ʼ����깳��
	CDialog::OnInitDialog();
	// ��ȡ��ǰ���ھ��   
	HWND handle = GetSafeHwnd();   
	//��¼�ɹ�֮�󣬽�ͼ���ܲ��ܹ�ʹ�ã������޷�ʹ��
	CString tmpreg;
	for(int i=49;i<56;i++){
		tmpreg.Format(L"FriendTeam_%d",i);
		m_atom[i-49]=GlobalAddAtom(tmpreg);
		BOOL tag=RegisterHotKey(handle, m_atom[i-49], MOD_ALT , i );
		ASSERT(tag!=FALSE);
	}
	judPos=TRUE;
	int var =m_tcp.SocketStart();;
	if (var < 0) {
		//�˳�
		judPos=FALSE;
		closesocket(m_tcp.sHost);	//�ر��׽���
		WSACleanup();		//�ͷ��׽�����Դ
		//MessageBox(_T("�޷����ӷ���������������"), 0, 0);
		//throw std::exception("�޷����ӷ���������������");

	}
	if(judPos){
	//��ʼ��������Ϣ
	char* addr = const_cast<char*>(loginMenu);
	char* host = const_cast<char*>(hostaddr);
	int post = 80;
	 m_tcp.sendinf(addr,host,NULL,post);
	//������Ϣ
	char recv_str[4096] = { 0 };
	if (judPos&&recv(m_tcp.sHost, recv_str, sizeof(recv_str), 0) == -1)
	{
		// cout << "recv failed" << endl;
		judPos=FALSE;
		closesocket(m_tcp.sHost);	//�ر��׽���
		WSACleanup();		//�ͷ��׽�����Դ
	}
	if(judPos){
	//���׽��ֹر�
	closesocket(m_tcp.sHost);	//�ر��׽���
	WSACleanup();
	}
	//	 MessageBoxA(0,recv_str,"sss",0);
	Json::Value troot;
	Json::Reader reader;
	Json::FastWriter fast_writer;

	string sst = strstr(recv_str, "{");
	if (!sst.empty()&&!reader.parse(sst, troot, false)) {
	}
	// MessageBoxA(0,sst.c_str(),"sss",0);
	string sst1 = strstr(sst.c_str(), "package");
	sst1 = strstr(sst1.c_str(), "{");
	// MessageBoxA(0,sst1.c_str(),"sss",0);
	if (!reader.parse(sst1, troot, false)) {

	}
	setpwdurl = troot["setpasswd"].asString();  //�����˺�URL
	}
	//ShowOwnedPopups(FALSE);
    //ModifyStyle()
	//  ShowOwnedPopups(0);
	// �O���ˌ�Ԓ���K�ĈDʾ�������ó�ʽ����ҕ�����ǌ�Ԓ���K�r��
	// ��ܕ��Ԅӏ��´����I
	SetIcon(m_hIcon, TRUE);			// �O����Dʾ
	SetIcon(m_hIcon, FALSE);		// �O��С�Dʾ
	m_nid.hWnd = GetSafeHwnd();
	m_nid.uCallbackMessage = UM_TRAYNOTIFY;
	
	// Set tray icon and tooltip
	m_nid.hIcon = m_hIcon;
	LCance.ShowWindow(0);
	// Set tray notification tip information
	CString strToolTip = _T("����׬");
	Shell_NotifyIcon(NIM_ADD, &m_nid);
	/*
	���������������ʼ���ṹ��
	*/
	
	GetWindowRect(&poswind);
	tmmlog.autologin=0;
	tmmlog.psd[0]='\0';
	tmmlog.user[0]='\0';
	FILE *fp = NULL;
	fp=fopen("C:\\Kehu\\login.log","rb+");   //׷�ӵķ�ʽ���ļ�
	if(fp!=NULL){
		fread(&tmmlog,sizeof(Login),1,fp);    //��ȡ�ļ�
		UserName.SetWindowTextW(CString(tmmlog.user));
		PassWord.SetWindowTextW(CString(tmmlog.psd));
		/*���������û��ǿգ����Զ���¼��ʶ����*/
		reAuto=tmmlog.autologin;
		fclose(fp);  //��ʹ�ر��ļ�������
		if(tmmlog.autologin>0)
		{
			ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW,1);//����������
           // isautologin=true;  //����Ϊ�Զ���¼
  		    m_button_login.ShowWindow(1);
	        m_button_cance.ShowWindow(1);
		    LCance.ShowWindow(0);
		    m_check_dl.SetCheck(1);
		    m_check_ps.SetCheck(1);
			/*  �������ؽ���  */
			WINDOWPLACEMENT lwndpl; 
			lwndpl.length= sizeof(WINDOWPLACEMENT);
			lwndpl.flags=WPF_RESTORETOMAXIMIZED;
			//::GetWindowPlacement(m_hWnd,&lwndpl);
			lwndpl.showCmd =SW_HIDE;//SW_SHOWMINIMIZED;
			SetWindowPlacement(&lwndpl);
			SetWindowPos(&wndTopMost,-100,-100,0,0,  SWP_HIDEWINDOW);
			//SetWindowPos(&wndNoTopMost,   poswind.left,   poswind.top,   poswind.right,   poswind.bottom,  SWP_SHOWWINDOW);   
			//CenterWindow();
			 //OnBnClickedOk();
			// ShowWindow(SW_HIDE);
			//����һ����ʱ��������Ϊ1�������Զ���¼
					//�رմ򿪵��ļ�
			   SetTimer(M_TIMERE,1000, 0);   
		}else{
			if(strlen(tmmlog.user)>0)
				reAuto=1;
			   writelogin();
			   m_check_dl.SetCheck(1);
		}
	}
	OnStnClickedStaticTitle();
	OnStnClickedStaticYzm();
	}else{
		//����������
		ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW,1);//����������
		// isautologin=true;  //����Ϊ�Զ���¼
		m_button_login.ShowWindow(1);
		m_button_cance.ShowWindow(1);
		LCance.ShowWindow(0);
		m_check_dl.SetCheck(1);
		m_check_ps.SetCheck(1);
		/*  �������ؽ���  */
		WINDOWPLACEMENT lwndpl; 
		lwndpl.length= sizeof(WINDOWPLACEMENT);
		lwndpl.flags=WPF_RESTORETOMAXIMIZED;
		//::GetWindowPlacement(m_hWnd,&lwndpl);
		lwndpl.showCmd =SW_HIDE;//SW_SHOWMINIMIZED;
		SetWindowPlacement(&lwndpl);
		//OnBnClickedOk();
		// ShowWindow(SW_HIDE);
		//����һ����ʱ��������Ϊ1�������Զ���¼
		//ͬʱ��menu
		if(Mmdlg!=NULL) {
			Mmdlg->DestroyWindow();
			delete  Mmdlg;
			Mmdlg=NULL;
		}
		Mmdlg = new MMenu();
		Mmdlg->Create(IDD_DIALOG5,GetDesktopWindow());
		Mmdlg->ShowWindow(SW_SHOW);
		Mmdlg->SetFocus();// �õ�����
		IsLogin = true;
}
	return TRUE;  // ���� TRUE����������������O�����c
}

// �������С�����o�������Č�Ԓ���K������Ҫ���еĳ�ʽ�a��
// �Ա��L�u�Dʾ�����ʹ���ļ�/�zҕģʽ�� MFC ���ó�ʽ��
// ��ܕ��Ԅ���ɴ����I��

void CKehuDlg::OnPaint()
{
		Staticinit();
	if (IsIconic())
	{
		CPaintDC dc(this); // �L�u���b�Ã���

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ���Dʾ������Ñ��˾���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ���L�Dʾ
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ��ʹ������ҷ��С��ҕ���r��
// ϵ�y�����@������ȡ���Θ��@ʾ��
HCURSOR CKehuDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CKehuDlg::OnBnClickedOk()
{
	
	//	UlMenu.LoadMenu(IDR_MENU1);
	//  menuTray.LoadMenu(IDR_MENU_TRAY);



	//GoodInf  myss; 
	//myss.DoModal();
	// TODO: Add your control notification handler code here
	CString  username; //�û���
	CString  pwd ;
	CString  yzm  ;
	UserName.GetWindowTextW(username);
	PassWord.GetWindowTextW(pwd);
	Yanzma.GetWindowTextW(yzm);
	
	if (username.IsEmpty())
	{
		MessageBox(_T("�������û���"),0,0);
		return;
	}
	if (pwd.IsEmpty()) {
		MessageBox(_T("����������"), 0, 0);
		return;
	}

	if (tmmlog.autologin==0&&yzm.IsEmpty()) {
		MessageBox(_T("��������֤��"), 0, 0);
		return;
	}
	RECT rect;
	m_button_login.GetWindowRect(&rect);//��ȡ�ؼ�����ȫƵ��λ��
	ScreenToClient(&rect);//ת��Ϊ�Ի����ϵ����λ��
	m_button_login.ShowWindow(0);
	m_button_cance.ShowWindow(0);
	LCance.ShowWindow(1);
	UpdateWindow();
	//MoveWindow(rect.left+60,rect.top,100,40,TRUE);
	
	//Sleep(30);	
	//UpdateData();
	//::SetWindowPos(this->GetSafeHwnd(),LCance,rect.left+60,rect.top,100,40,SWP_SHOWWINDOW);	   
	strname.SetAt(4, '\0');
	//���Դ�С�Ƚ�
		if(tmmlog.autologin==0&&strname.CompareNoCase(yzm))
	{ 
		MessageBox(_T("��֤�벻��ȷ�����������룡"), 0, 0);
		Yanzma.SetWindowTextW(_T(""));
		OnStnClickedStaticYzm();
		//PassWord.SetWindowTextW(_T(""));

		m_button_login.ShowWindow(1);
	    m_button_cance.ShowWindow(1);
		m_check_dl.SetCheck(true);
		LCance.ShowWindow(0);
		return;
	}
	//�����׽��ֽ��е�¼��֤
	 //SocketStart();
	int var = m_tcp.SocketStart();
	if (var < 0) {
		//�˳�
		 MessageBox(_T("�޷����ӷ���������������"), 0, 0);
	 	// throw std::exception("�޷����ӷ���������������");
			WINDOWPLACEMENT lwndpl; 
			lwndpl.length= sizeof(WINDOWPLACEMENT);
			lwndpl.flags=WPF_RESTORETOMAXIMIZED;
			//::GetWindowPlacement(m_hWnd,&lwndpl);
			lwndpl.showCmd =SW_SHOW;//SW_SHOWMINIMIZED;
			SetWindowPlacement(&lwndpl);
			SetWindowPos(&wndTopMost,   poswind.left,   poswind.top,   (poswind.right-poswind.left),(poswind.bottom-poswind.top),  SWP_SHOWWINDOW);
			//SetWindowPos(&wndNoTopMost,   poswind.left,   poswind.top,   poswind.right,   poswind.bottom,  SWP_SHOWWINDOW);   
			CenterWindow();
		 closesocket(m_tcp.sHost);	//�ر��׽���
		 WSACleanup();		//�ͷ��׽�����Դ
		m_button_login.ShowWindow(1);
	    m_button_cance.ShowWindow(1);
		m_check_dl.SetCheck(true);
		LCance.ShowWindow(0);
		 return ;
	}

	CStringA wus(username.GetBuffer(0));
	 wuser = wus.GetBuffer(0);
	 //��ʼ��������Ϣ
	 char* addr = const_cast<char*>(logaddr);
	 char* host = const_cast<char*>(hostaddr);
	 int post = 80;
	 string msg = "u="+wuser;
	 //char * ms = msg.c_str();
	 m_tcp.sendinf(addr, host, msg.c_str(), post);
	 //��ȡ������Ϣ
	 char recv_str[4096] = { 0 };
	 if (recv(m_tcp.sHost, recv_str, sizeof(recv_str), 0) == -1)
	 {
		 // cout << "recv failed" << endl;
		 MessageBox(_T("recv nothings !"), 0, 0);
		WINDOWPLACEMENT lwndpl; 
			lwndpl.length= sizeof(WINDOWPLACEMENT);
			lwndpl.flags=WPF_RESTORETOMAXIMIZED;
			//::GetWindowPlacement(m_hWnd,&lwndpl);
			lwndpl.showCmd =SW_SHOW;//SW_SHOWMINIMIZED;
			SetWindowPlacement(&lwndpl);
				SetWindowPos(&wndTopMost,   poswind.left,   poswind.top,   (poswind.right-poswind.left),(poswind.bottom-poswind.top),  SWP_SHOWWINDOW);
			//SetWindowPos(&wndNoTopMost,   poswind.left,   poswind.top,   poswind.right,   poswind.bottom,  SWP_SHOWWINDOW);   
			CenterWindow();
			//�˳�
	    closesocket(m_tcp.sHost);	//�ر��׽���
	    WSACleanup();		//�ͷ��׽�����Դ
		m_button_login.ShowWindow(1);
	    m_button_cance.ShowWindow(1);
		m_check_dl.SetCheck(true);
		LCance.ShowWindow(0);
		 return;
	 }

	 wchar_t trp[4096];
	 int ulBytes = MultiByteToWideChar(CP_ACP, 0, recv_str, -1, NULL, 0);
	 ulBytes = MultiByteToWideChar(CP_ACP, 0, recv_str, -1, trp, ulBytes);
	 CString ss(trp);
	 //����json��ѹ��
	 Json::Value troot;
	 Json::Reader reader;
	 Json::FastWriter fast_writer;
	 /*
	 CStringA stra(ss.GetBuffer(0));
	 //ss.ReleaseBuffer();
	 string  st = stra.GetBuffer(0);
	 //stra.ReleaseBuffer();
	 //char *stt=
	 */
	// MessageBoxA(0,recv_str, 0, 0);
	 string sst = strstr(recv_str, "{");
	 if (!reader.parse(sst, troot, false)) {
		MessageBox(_T("�û���������!"), 0, 0);

#ifdef Debug_1
		MessageBoxA(0,recv_str,0,0);   
		MessageBoxA(0, msg.c_str(),0,0);
#endif
		 /*�ý���ָ�����*/

	  WINDOWPLACEMENT lwndpl; 
			lwndpl.length= sizeof(WINDOWPLACEMENT);
			lwndpl.flags=WPF_RESTORETOMAXIMIZED;
			//::GetWindowPlacement(m_hWnd,&lwndpl);
			lwndpl.showCmd =SW_SHOW;//SW_SHOWMINIMIZED;
			SetWindowPlacement(&lwndpl);
				SetWindowPos(&wndTopMost,   poswind.left,   poswind.top,   (poswind.right-poswind.left),(poswind.bottom-poswind.top),  SWP_SHOWWINDOW);
			//SetWindowPos(&wndNoTopMost,   poswind.left,   poswind.top,   poswind.right,   poswind.bottom,  SWP_SHOWWINDOW);   
			CenterWindow();
		UserName.SetWindowTextW(L"");
	    PassWord.SetWindowTextW(L"");
	    Yanzma.SetWindowTextW(L"");
		m_button_login.ShowWindow(1);
	    m_button_cance.ShowWindow(1);
		LCance.ShowWindow(0);
		m_check_ps.SetCheck(0);
	    m_check_dl.SetCheck(true);
		return ;
	 }
	// MessageBoxA(0,sst.c_str(), 0, 0);
	 string name = troot["rt"].asString();
	 string gender = troot["st"].asString();
	 Ccommon md5Class;
	 //pwdת��Ϊstring
	 CStringA pd(pwd.GetBuffer(0));
	 string tmpd=pd.GetBuffer(0);
	 cm_ower.username = wuser;
	 cm_ower.password = tmpd;
	 char tmps[1024],ctmps[1024];
	 memset(tmps,0,sizeof(tmps));
	 memset(tmps , 0, sizeof(ctmps));
	 tmpd += name;
	 strcpy(tmps , md5Class.md5(tmpd.c_str()));
	 strcpy(ctmps , md5Class.md5(tmps));
	 strcat(ctmps,gender.c_str());
	 strcpy(tmps , md5Class.md5(ctmps));
	 string pwdtmp(tmps);
     //��ȡ������cpu�����Ϣ���䵽���ݿ��б���
	 INT iQueryType = 3;
	 INT iSize = 1;
	 T_DEVICE_PROPERTY *properties = new T_DEVICE_PROPERTY[1];
	 int get_cnt =5;  //��ȡ����  
	 string mydata[6];
	 string data;
	 int err;
	 for (int i = 1; i<7; i++)
	 {
		iQueryType = i;
		data.clear();
		get_cnt =5; 
		while(get_cnt>0&&data.empty())
		{
		 err = WMI_DeviceQuery(iQueryType, properties, iSize);
		 for (int j = 0; j<128; j++){
			 if (char(properties[0].szProperty[j]) == '\0')  break;
			 data += char(properties[0].szProperty[j]);
			  properties[0].szProperty[j]='\0';  //���ֶ����
		 }
		  get_cnt--;
		}

		 if(data.empty()){
			 //��¼���������
			 if(err==-1)
				 data="DoesNotSurpport";//"��֧�ֵ��豸����ֵ";
			 else if(err==-2)
				 data="WMI_connectfailed";//"WMI����ʧ��";
			 else if(err==-3)
				 data="WQL_Querry_Incorr";//"����ȷWQL��ѯ���";
		 
		 }
			mydata[i - 1] = data;
	 }
	  
	 //��ȡ����IP��ַ
	 hostent *chost;
	 char hostName[20];
	 gethostname(hostName, 20);
	 chost = gethostbyname(hostName);
	 string strIPaddr;

	 strIPaddr = inet_ntoa(*(struct in_addr*)chost->h_addr_list[0]);

	  //������update�����ݿ���
	 //�������ݿ�
	 /*
	 mysql_init(&m_sqlCon);
	 // localhost:������ rootΪ�˺����� testΪ���ݿ��� 3306Ϊ�˿�  
	 if (!mysql_real_connect(&m_sqlCon, hostaddr, root, tpwd, biao, port, NULL, 0)) {
		 MessageBox(_T("���ݿ�����ʧ��!"));
		 return;
	 }
	 mysql_set_character_set(&m_sqlCon, "gbk");

	 string sql = "update pyt_friend_user set YingJianID='1" + mydata[0] +
		 "', ZhuID='" + mydata[1] + "',CPUID='" + mydata[2] + "',BIOSID='" + mydata[3] +
		 "',MACID='" + mydata[5] + "', IP='" + strIPaddr + "' WHERE username='" + wuser+"'";

	 //��ʼ����
	 int tvar = mysql_real_query(&m_sqlCon, sql.c_str(), (unsigned int)sql.size());
	 if (tvar != 0) {
		 MessageBox(L"CPU����Ϣ����ʧ�ܣ�");
		 return;
	 }

	 mysql_close(&m_sqlCon);
	 */
	 string wmsg = "u=" + wuser + "&p=" + pwdtmp+"&YingJianID="+ mydata[0]+"&ZhuID="+ mydata[4]\
		 +"&CPUID="+mydata[2]+"&BIOSID="+mydata[3]+"&MACID="+mydata[5]+"&IP="+strIPaddr;
	 //ȫ�ֻ�
	 ower.username=wuser;
	 ower.password=pwdtmp;
	 char sinf[1024] = {0};
	 strcpy(sinf,wmsg.c_str());
	 char *saddr = const_cast<char *>(loginaddr);
	 m_tcp.sendPost1(saddr, host,sinf, post);
	 memset(recv_str,0,sizeof(recv_str));
	 if (recv(m_tcp.sHost, recv_str, sizeof(recv_str), 0) == -1){
		// cout << "recv failed" << endl;
		MessageBox(_T("��վ������ϢΪ��NULL!"), 0, 0);
		WINDOWPLACEMENT lwndpl; 
			lwndpl.length= sizeof(WINDOWPLACEMENT);
			lwndpl.flags=WPF_RESTORETOMAXIMIZED;
			//::GetWindowPlacement(m_hWnd,&lwndpl);
			lwndpl.showCmd =SW_SHOW;//SW_SHOWMINIMIZED;
			SetWindowPlacement(&lwndpl);
				SetWindowPos(&wndTopMost,   poswind.left,   poswind.top,   (poswind.right-poswind.left),(poswind.bottom-poswind.top),  SWP_SHOWWINDOW);
			//SetWindowPos(&wndNoTopMost,   poswind.left,   poswind.top,   poswind.right,   poswind.bottom,  SWP_SHOWWINDOW);   
			CenterWindow();
			//�˳�
	    closesocket(m_tcp.sHost);	//�ر��׽���
		WSACleanup();		//�ͷ��׽�����Դ
		m_button_login.ShowWindow(1);
	    m_button_cance.ShowWindow(1);
		m_check_dl.SetCheck(true);
		LCance.ShowWindow(0);
		return;
	}
	 //MessageBox(recv_str, 0, 0);
	 //���׽��ֹر�
	 closesocket(m_tcp.sHost);
	 WSACleanup();
	//MessageBoxA(NULL, recv_str, 0, 0);
	//MessageBoxA(NULL, sinf, 0, 0);
	//MessageBoxA(NULL, wmsg.c_str(), 0, 0);
	sst = strstr(recv_str, "{");
	if (!reader.parse(sst, troot, false)) {

		MessageBox(_T("���ݽ����쳣!#__LINE__��"), 0, 0);
		WINDOWPLACEMENT lwndpl; 
		lwndpl.length= sizeof(WINDOWPLACEMENT);
		lwndpl.flags=WPF_RESTORETOMAXIMIZED;
		//::GetWindowPlacement(m_hWnd,&lwndpl);
		lwndpl.showCmd =SW_SHOW;//SW_SHOWMINIMIZED;
		SetWindowPlacement(&lwndpl);
		SetWindowPos(&wndTopMost,poswind.left,poswind.top,(poswind.right-poswind.left),(poswind.bottom-poswind.top),  SWP_SHOWWINDOW);
		CenterWindow();
		m_button_login.ShowWindow(1);
	    m_button_cance.ShowWindow(1);
		m_check_dl.SetCheck(true);
		LCance.ShowWindow(0);
		return;
	}

	name = troot["status"].asString();
	SessinID=troot["PHPSESSID"].asString();
	al_username = troot["username"].asString();
	al_loginId= troot["id"].asString();

	//cout<<al_loginId<<endl;
	//MessageBoxA(NULL, al_loginId.c_str(), 0, 0);
	 if (name.compare("sucess"))
	 {
		 MessageBox(_T("�û������������"), 0, 0);
		 //���µ�¼
		 /*  �������ؽ���  */
		WINDOWPLACEMENT lwndpl; 
		lwndpl.length= sizeof(WINDOWPLACEMENT);
		lwndpl.flags=WPF_RESTORETOMAXIMIZED;
		//::GetWindowPlacement(m_hWnd,&lwndpl);
		lwndpl.showCmd =SW_SHOW;//SW_SHOWMINIMIZED;
		SetWindowPlacement(&lwndpl);
		SetWindowPos(&wndTopMost,   poswind.left,   poswind.top,   (poswind.right-poswind.left),(poswind.bottom-poswind.top),  SWP_SHOWWINDOW);
		CenterWindow();
		m_button_login.ShowWindow(1);
	    m_button_cance.ShowWindow(1);
		m_check_dl.SetCheck(true);
		LCance.ShowWindow(0);
		 return;
	 }

	judCenter=1;//��ʾ�Ѿ��ɹ���½��
	/*�������һ���Ƿ��ס����*/
	//if(m_check_ps.GetCheck()){
	if(m_check_dl.GetCheck())
		reAuto=1;
	    OnBnClickedCheck1();

	// isautologin=true;
	//if(tmmlog.autologin!=ISTrue)
	{
	      /*  �������ؽ���  */
		//  WINDOWPLACEMENT lwndpl;
		//  WINDOWPLACEMENT * lpwndpl;
		//  lpwndpl = &lwndpl;
		//  GetWindowPlacement(lpwndpl);
		//  lpwndpl->showCmd =SW_SHOWMINIMIZED;
		//BOOL isjud=SetWindowPlacement(lpwndpl);
		BOOL isjud= this->ShowWindow(SW_HIDE);
		//������Զ���¼������Ҫ����
		if(!isjud){
		//�������ʧ�ܣ���ʹ�����������
		   this->ShowWindow(SW_HIDE);
		}
	 }
	 //��������Ϣ����һ��
	 IsLogin = true;

	 

    /*
	  �趨һ����ʱ��,������ʱ���͵������趨��ʱ��Ϊ7����
	*/
	SetTimer(M_TIMER,M_min*1000, 0);
	//����ð����
	/*
	 tm = GetCurrentTime();
 	 tm_h = tm.GetHour();     //ʱ
	 tm_m = tm.GetMinute();   //��
	 tm_s = tm.GetSecond();   //��
	 long int tal_tm = tm_h * 3600 + tm_m * 60 + tm_s; //����ܵ�ʱ��
    */
	SetTimer(M_TIMERA, 1800000, 0);
	SetTimer(M_TIMERC, 3200000, 0);
	if(Mmdlg!=NULL) {
		Mmdlg->DestroyWindow();
		delete  Mmdlg;
		Mmdlg=NULL;
	}
	Mmdlg = new MMenu();
	Mmdlg->Create(IDD_DIALOG5,GetDesktopWindow());
	Mmdlg->ShowWindow(SW_SHOW);
	Mmdlg->SetFocus();// �õ�����
	IsLogin = true;
	SetTimer(M_TIMERD, 18000, 0);
	 /*
	  ��¼�ɹ�֮��ʼ�趨������������
	 */
	//ShowWindow(SW_MINIMIZE);
	//this->DestroyWindow();
	 //char *tms = md5Class.md5(strcat(,gender.c_str()); 
}


void CKehuDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here

	   OnClose();
}


void CKehuDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
   // KillTimer(M_TIMERE);
	//isautologin=false;
	m_button_login.ShowWindow(TRUE);
	m_button_cance.ShowWindow(TRUE);
	LCance.ShowWindow(FALSE);

}



void CKehuDlg::OnStnClickedStaticYzm()
{
	// TODO: Add your control notification handler code here
	srand((int)time(NULL));
	char tmpvar;
	wchar_t tmp[7] = {'\0'};
	int i = 0;
	while (i<4)
	{
		tmpvar = (char)(48 + rand() % 75);
		if (isalpha(tmpvar) || isdigit(tmpvar)){
			if (tmpvar != '0'&&tmpvar != 'o'&&tmpvar != 'O'&&tmpvar!='l' \
				&&tmpvar != '1'&&tmpvar != 'I'
				)
			 tmp[i++] = tmpvar;
		}
	}
	  tmp[4] = ' ';
	  tmp[5] = 1;
	  tmp[6] = '\0';
	//wchar_t *wide = new wchar_t[8];
	//MultiByteToWideChar(0, 0, tmp, -1, wide, 7);
	strname = "";
	strname.Insert(0, tmp);
	//����������ַ���֮�󣬺ϳ�ͼƬ
	//system("pause");
	CString strFileName = _T("C:\\Kehu\\tmp.bmp");
	CFile file;
	//strncpy(tmp, (LPCTSTR )str, sizeof(tmp));
	file.Open(strFileName, CFile::modeCreate | CFile::modeWrite);
	//strname.SetAt(7, '\0');
	ShengChengYanZhenMa(strname, file);

	file.Close();
	HBITMAP bitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(), strFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	Yzm_Bitmap.SetBitmap(bitmap);
	UpdateData(false);

}




BOOL CKehuDlg::myCreateBitmap(HDC hDC, HBITMAP hbitmap,
	PBITMAPFILEHEADER &outheadbuf, long *outheadsize,
	PBITMAPINFO &outinfobuf, long *outinfosize,
	LPBYTE &outdatabuf, long *outdatasize)	//���ɵ�ɫλͼ					 
  {
	BITMAP bmp;
	WORD cClrBits;
	DWORD my_biClrUsed = 0;
	outinfobuf = NULL;
	outdatabuf = NULL;
	outheadbuf = NULL;

	if (!GetObject(hbitmap, sizeof(BITMAP), (LPSTR)&bmp))
		goto errout;
	bmp.bmPlanes = 1;
	bmp.bmBitsPixel = 1;  //ǿ�Ƹ�ֵת��������ÿ����BIT��
	cClrBits = 1;  //�õ�ÿ���ض���λ		
	*outinfosize = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * (1 << cClrBits);
	outinfobuf = (PBITMAPINFO)GlobalAlloc(GPTR, *outinfosize);
	outinfobuf->bmiHeader.biSize = sizeof(BITMAPINFOHEADER); //��Ϣͷ��С��������ɫ�壩	
	outinfobuf->bmiHeader.biWidth = bmp.bmWidth;
	outinfobuf->bmiHeader.biHeight = bmp.bmHeight;
	outinfobuf->bmiHeader.biPlanes = bmp.bmPlanes;
	outinfobuf->bmiHeader.biBitCount = bmp.bmBitsPixel;
	my_biClrUsed = (1 << cClrBits);
	outinfobuf->bmiHeader.biClrUsed = my_biClrUsed;
	outinfobuf->bmiHeader.biCompression = BI_RGB;
	outinfobuf->bmiHeader.biSizeImage = ((outinfobuf->bmiHeader.biWidth * cClrBits + 31) & ~31)\

		/ 8 * outinfobuf->bmiHeader.biHeight;
	//ͼ���С	
	outinfobuf->bmiHeader.biClrImportant = 0;
	/////////////////////////////////�õ�λͼ����	
	// GlobalAlloc����λͼ���ݵ��ڴ�	
	// GetDIBits ����hDC ��HBITMAP�õ�λͼ���ݡ���ɫ������	
	*outdatasize = outinfobuf->bmiHeader.biSizeImage;
	outdatabuf = (LPBYTE)GlobalAlloc(GPTR, *outdatasize);  //����λͼ��С�����ڴ�	
	if (!outdatabuf)
		goto errout;
	if (!GetDIBits(//����DC��BITMAP�õ�λͼ����		
		hDC,
		hbitmap,
		0,
		(WORD)outinfobuf->bmiHeader.biHeight,
		outdatabuf,     // outdatabuf�еõ�λͼ����		
		outinfobuf,
		DIB_RGB_COLORS))
   {
		goto errout;
	}

	/////////////////////////////////�õ��ļ�ͷ	
	*outheadsize = sizeof(BITMAPFILEHEADER);
	outheadbuf = (PBITMAPFILEHEADER)GlobalAlloc(GPTR, *outheadsize);
	//����λͼ��С�����ڴ�	
	if (!outheadbuf)
		goto errout;
	outheadbuf->bfType = 0x4d42;
	outheadbuf->bfSize = (DWORD)(sizeof(BITMAPFILEHEADER) +
		outinfobuf->bmiHeader.biSize +
		my_biClrUsed * sizeof(RGBQUAD) +
		outinfobuf->bmiHeader.biSizeImage);
	outheadbuf->bfReserved1 = 0;
	outheadbuf->bfReserved2 = 0;

	outheadbuf->bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) +
		outinfobuf->bmiHeader.biSize +
		my_biClrUsed * sizeof(RGBQUAD);
	return TRUE;

	//////////////////////������	
errout:
	if (outinfobuf) GlobalFree(outinfobuf);
	if (outdatabuf) GlobalFree(outdatabuf);
	if (outheadbuf) GlobalFree(outheadbuf);
	outinfobuf = NULL;
	outdatabuf = NULL;
	outheadbuf = NULL;
	*outheadsize = 0;
	*outinfosize = 0;
	*outdatasize = 0;
	return FALSE;
}


BOOL CKehuDlg::ShengChengYanZhenMa(CString str, CFile& file)//������֤��
{
	ASSERT(0 == str.GetLength() % 2);

	CWnd* pDesk = CWnd::GetDesktopWindow();
	CDC* pDC = pDesk->GetDC();

	//ÿ���ַ���λ�����ƫ��4
	CRect r(0, 0, 0, 0);
	pDC->DrawText(str, &r, DT_CALCRECT);
	const int w = r.Width() + 12;
	const int h = r.Height() + 15;
	const int iCharWidth = w * 2 / str.GetLength() + rand() % 5;  //�������λ��

																  //�����ڴ�DC��λͼ����䱳��
	CBitmap bm;
	bm.CreateCompatibleBitmap(pDC, w, h);
	CDC memdc;
	memdc.CreateCompatibleDC(pDC);
	CBitmap*pOld = memdc.SelectObject(&bm);
	memdc.FillSolidRect(0, 0, w, h, RGB(255, 255, 255));

	::SetGraphicsMode(memdc.m_hDC, GM_ADVANCED);//Ϊ������б��׼��

	for (int i = 0; i < str.GetLength() / 2; i++)
	{
		//��������
		CFont* pFont = memdc.GetCurrentFont();
		LOGFONT logFont;
		pFont->GetLogFont(&logFont);
		logFont.lfOutPrecision = OUT_TT_ONLY_PRECIS;
		logFont.lfStrikeOut= TRUE;
		logFont.lfHeight=24;
		logFont.lfOrientation = rand() % 90;
		CFont font;
		font.CreateFontIndirect(&logFont);
		memdc.SelectObject(&font);

		int x = iCharWidth*i + rand() % 5;
		int y = rand() % 5;
		memdc.TextOut(x, y, str.Mid(i * 2, 2));
	}

	//�����ݴ浽�ļ�(CFile��CMemFile)
	PBITMAPFILEHEADER outheadbuf;
	PBITMAPINFO outinfobuf;
	LPBYTE outdatabuf;
	long outheadsize, outinfosize, outdatasize;
	if (!myCreateBitmap(memdc.m_hDC, bm,
		outheadbuf, &outheadsize,
		outinfobuf, &outinfosize,
		outdatabuf, &outdatasize))
		return FALSE;


	file.Write(outheadbuf, outheadsize);
	file.Write(outinfobuf, outinfosize);
	file.Write(outdatabuf, outdatasize);

	memdc.SelectObject(pOld);
	bm.DeleteObject();
	memdc.DeleteDC();
	pDC->ReleaseAttribDC();
	return true;
}

void CKehuDlg::OnStnClickedStaticTitle()
{
	// TODO: Add your control notification handler code here
	HBITMAP hBitmap;
	//����ͼƬID
	hBitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDB_BITMAP1),
		IMAGE_BITMAP, 0, 0,
		LR_LOADMAP3DCOLORS);

	//���ָ��̬�ؼ���ָ��  IDC_STATIC_Title
	CStatic *pStatic = (CStatic *)GetDlgItem(IDC_STATIC_Title);//�ؼ�ID   
															   //���þ�̬�ؼ�����ʽ��ʹ�����ʹ��λͼ������λ����ʾʹ����  
	pStatic->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
	//���þ�̬�ؼ���ʾλͼ  
	pStatic->SetBitmap(hBitmap);
	UpdateData();

}


void CKehuDlg::OnSize(UINT nType, int cx, int cy)

{
	CDialog::OnSize(nType, cx, cy);
	// TODO: Add your message handler code here
	if (nType == SIZE_MINIMIZED){
		ShowWindow(SW_HIDE); // ����С���У�����������              
	}

}


BOOL CKehuDlg::DestroyWindow()

{

	// TODO: Add your specialized code here and/or call the base class

	// ��������ɾ��ͼ��
    //Shell_NotifyIcon(NIM_DELETE, &m_nid);

	return CDialog::DestroyWindow();

}
void CKehuDlg::OnEnChangeEditUser()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	 PassWord.SetWindowTextW(_T(""));
	// TODO:  Add your control notification handler code here
}


void CKehuDlg::OnEnChangeEditYzm()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CKehuDlg::OnStnClickedStatictouxiang()
{
	// TODO: Add your control notification handler code here
	HBITMAP hBitmap;
	//����ͼƬID
	hBitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDB_BITMAP2),
		IMAGE_BITMAP, 0, 0,
		LR_LOADMAP3DCOLORS);

	//���ָ��̬�ؼ���ָ��  IDC_STATIC_Title
	CStatic *pStatic = (CStatic *)GetDlgItem(IDC_STATIC_touxiang);//�ؼ�ID   
															   //���þ�̬�ؼ�����ʽ��ʹ�����ʹ��λͼ������λ����ʾʹ����  
	pStatic->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
	//���þ�̬�ؼ���ʾλͼ  
	pStatic->SetBitmap(hBitmap);
	UpdateData();
}


void CKehuDlg::OnEnChangeEditPsw()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

LRESULT CKehuDlg::OnTrayNotify(WPARAM wParam, LPARAM lParam)
{
	UINT uMsg = (UINT)lParam;
	CPoint point;
	switch (uMsg)
		{

		case WM_RBUTTONUP:{

			int id;
			GetCursorPos(&point);  //������λ��
		
			  CMenu * pPopup= menuTray.GetSubMenu(0);     
			 // Cmenu *pPAuTo = menuTray.GetSubMenu(0);
		   ASSERT(pPopup!=NULL); 
		   if(Kehutmp.data==1)
				pPopup->ModifyMenu(IDR_BAR_QMSZ, MF_BYCOMMAND | MF_STRING, IDR_BAR_QMSZ,L"����ǰ�棨��)");
		   else 
				pPopup->ModifyMenu(IDR_BAR_QMSZ, MF_BYCOMMAND | MF_STRING, IDR_BAR_QMSZ,L"����ǰ�棨����");
		   pPopup->ModifyMenu(ID_AuToLogin, MF_BYCOMMAND | MF_STRING, ID_AuToLogin,reAuto>0?L"�Զ���¼���̣�":L"�Զ���¼������");
		   pmenu=(IsLogin == TRUE) ? &menuTray : &UlMenu;
			SetForegroundWindow();
			id = pmenu->GetSubMenu(0)->TrackPopupMenu(TPM_RETURNCMD | TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	#if 0     
			CString strInfo;
			strInfo.Format(L"menuid %d", id);
			LPCTSTR strtmp;
			strtmp = strInfo.GetBuffer(0);
			MessageBox(strtmp, L"test");
	#endif
			switch (id)
			{
				//�Ƿ��Զ���¼
			case ID_AuToLogin:{
				if(reAuto>0)
					reAuto=0;
				else 
					reAuto=1;
			/*����Ϣ���浽�ļ���*/				  
				writelogin(); 
		    }break;
			case IDR_TRAY_EXIT:
				OnClose();
				 //OnCancel();
				//OnOK();
				break;
			case IDR_TRAY_RESTORE:

				//����ǰ����ʾ
				//SetForegroundWindow();
				//ShowWindow(SW_SHOWNORMAL);

#if 0
		 if(Mmdlg!=NULL){
				Mmdlg->DestroyWindow();
				delete Mmdlg;
				Mmdlg=NULL;
			}
	#endif 
			if(Mmdlg==NULL){
				Mmdlg = new MMenu;
				Mmdlg->Create(IDD_DIALOG5, GetDesktopWindow());
			  }
				Mmdlg->ShowWindow(SW_SHOW);
				Mmdlg->SetFocus();// �õ�����
				break;
			case IDD_BAR_IE :
	#if 0
				if(Mmdlg!=NULL){
					Mmdlg->DestroyWindow();
					delete Mmdlg;
					Mmdlg=NULL;
				}
	#endif

				if(Mmdlg==NULL){
				Mmdlg = new MMenu;
				Mmdlg->Create(IDD_DIALOG5, GetDesktopWindow());
			  }
				Mmdlg->ShowWindow(SW_SHOW);
				Mmdlg->SetFocus();// �õ�����
				break;

			case IDR_BAR_HUOBI :
			{
				sc.dataType=1;
			 if(sc.jietutag<1){
			   sc.Create(IDD_Screepjt, GetDesktopWindow());
			   sc.ShowWindow(SW_MAXIMIZE);
			   sc.SetFocus();// �õ�����
			 }
			}
			break;

			case IDR_BAR_LLQ :
			{
				sc.dataType=2;
				if(sc.jietutag<1){
				sc.Create(IDD_Screepjt, GetDesktopWindow());
			   sc.ShowWindow(SW_MAXIMIZE);
			   sc.SetFocus();// �õ�����
				}
			}
			break;
			
			case IDR_BAR_SCGZ :
			{
				sc.dataType=3;
				 if(sc.jietutag<1){
			   sc.Create(IDD_Screepjt, GetDesktopWindow());
			   sc.ShowWindow(SW_MAXIMIZE);
			   sc.SetFocus();// �õ�����
			  }
			}
			break;
			
			case IDR_BAR_GL :
			{
				sc.dataType=4;
				if(sc.jietutag<1){
			   sc.Create(IDD_Screepjt, GetDesktopWindow());
			   sc.ShowWindow(SW_MAXIMIZE);
			   sc.SetFocus();// �õ�����
				}
			}break;
			
			case IDR_BAR_LTT :
			{
			   sc.dataType=5;
				if(sc.jietutag<1){
			   sc.Create(IDD_Screepjt, GetDesktopWindow());
			   sc.ShowWindow(SW_MAXIMIZE);
			   sc.SetFocus();// �õ�����
				}
			}break;
			
			case IDR_BAR_GMLB :
			{
			   sc.dataType=6;
				if(sc.jietutag<1){
			   sc.Create(IDD_Screepjt, GetDesktopWindow());
			   sc.ShowWindow(SW_MAXIMIZE);
			   sc.SetFocus();// �õ�����
			  }
			}
			break;
			case ID_BAR_TS :
			{
			   sc.dataType=7;
				if(sc.jietutag<1){
			   sc.Create(IDD_Screepjt, GetDesktopWindow());
			   sc.ShowWindow(SW_MAXIMIZE);
			   sc.SetFocus();// �õ�����
			  }
			}
			break;
		   case IDR_BAR_ZQZY:
		   {
			   
           if(m_news==NULL){
			   m_news = new News;
				m_news->Create(IDD_DIALOG3, GetDesktopWindow());
			}
		     m_news->ShowWindow(SW_SHOW);
		     m_news->SetFocus();// �õ�����
		}break;
		 
	case IDR_BAR_QMSZ:
		   { 
	     if(Kehutmp.data==1) Kehutmp.data=0;
		   else   Kehutmp.data=1;
			   //�޸�����
			CMenu* pPopup= menuTray.GetSubMenu(0);     
			ASSERT(pPopup!=NULL); 
		   if(Kehutmp.data){
			pPopup-> ModifyMenu(IDR_BAR_QMSZ, MF_BYCOMMAND | MF_STRING, IDR_BAR_QMSZ,L"����ǰ�棨�̣�");
			
		   }
		   else 
			pPopup-> ModifyMenu(IDR_BAR_QMSZ, MF_BYCOMMAND | MF_STRING, IDR_BAR_QMSZ,L"����ǰ�棨����");
		   UpdateData();
	/*
		   if(Mmdlg!=NULL){ 
				Mmdlg->DestroyWindow();
			   delete Mmdlg;
			   Mmdlg=NULL;
		   }
	*/
		   if(Mmdlg==NULL){
			  Mmdlg = new MMenu;
				Mmdlg->Create(IDD_DIALOG5, GetDesktopWindow());
		   }
				Mmdlg->ShowWindow(SW_SHOW);
				Mmdlg->SetFocus();// �õ�����
		   //�����ļ���
		   FILE *fp = fopen("C:\\Kehu\\init.log","wb+");
		   if(fp==NULL){
			   fp = fopen("C:\\Kehu\\init.log","wb+");
			   //Mess("init.log is open err !");
			  // break;
		   }
		   if(fp!=NULL){
		   fwrite(&Kehutmp,sizeof(Regist),1,fp);
		   fclose(fp);
		   }
		  }break;
	      default:  break;
		}
		}break;
      
	case WM_LBUTTONDBLCLK:{

		/*
		this->UserName.SetWindowTextW(L"");
		this->PassWord.SetWindowTextW(L"");
		this->Yanzma.SetWindowTextW(L"");
		SetForegroundWindow();
		ShowWindow(SW_SHOWNORMAL);
		*/
		if (IsLogin){
#if 0
			if(Mmdlg!=NULL){
				Mmdlg->DestroyWindow();
				delete Mmdlg;
				Mmdlg=NULL;
			}
#endif
			if(Mmdlg==NULL){
			Mmdlg = new MMenu;
			Mmdlg->Create(IDD_DIALOG5, GetDesktopWindow());
		
			}
		    Mmdlg->ShowWindow(SW_SHOWNORMAL);
		   Mmdlg->SetFocus();// �õ�����
		}
	}break;
    
	default:  break;
	}
	return 0;
}


BOOL  CKehuDlg::ShowBalloonTip(LPCTSTR szMsg, LPCTSTR szTitle, UINT uTimeout, DWORD dwInfoFlags)
{
	m_nid.hBalloonIcon =HICON(IDB_BITMAP1);
	m_nid.cbSize = sizeof(NOTIFYICONDATA);
	m_nid.uFlags = NIF_INFO;//��ʾ���� ��������ʾ�������Ϸ���ͬͼ�꣬
						  //���⻹��NIIF_ERROR��

	m_nid.uTimeout = uTimeout;//��ʾʱ��
	m_nid.dwInfoFlags = dwInfoFlags;
    StrCpy(m_nid.szInfo,szMsg? szMsg : _T(""));
	StrCpy(m_nid.szInfoTitle, szTitle ? szTitle : _T(""));//��ʾ����

	return Shell_NotifyIcon(NIM_MODIFY, &m_nid);
}

void CKehuDlg::OnTimer(UINT_PTR nIDEvent){

	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent )
	{
	case M_TIMER:{
	   //���ö��߳�ʵ��������ܣ������Ϳ��Բ��໥Ӱ��
	  //    AfxBeginThread((AFX_THREADPROC)FRun, 0);
	   // CWnd *tmp = new CWnd();
	     KillTimer(M_TIMER);
#if 0
		if(m_news!=NULL){
		   m_news->DestroyWindow();
		   delete m_news;
		   m_news=NULL;
		}
#endif
		if(m_news==NULL){
		   m_news = new News;
		   m_news->Create(IDD_DIALOG3, GetDesktopWindow());	
		}
		   m_news->ShowWindow(SW_SHOWNORMAL);
		   m_news->SetFocus();// �õ�����
							//AfxEndThread()
	} break;
	case M_TIMERA:  //��ͨ�û�֪ͨ
	{
    int var = m_tcp.SocketStart();
	if (var < 0) {
		//�˳�
		MessageBox(_T("�޷����ӷ���������������"), 0, 0);
	 	 //throw std::exception("�޷����ӷ���������������");
		 closesocket(m_tcp.sHost);	//�ر��׽���
		  WSACleanup();		//�ͷ��׽�����Դ
		  break;
	}
	 char* addr = const_cast<char*>("http://friend.py91178.com/Login/system_push");
	 char* host = const_cast<char*>(hostaddr);
	 int post = 80;
	 string msg = "u="+wuser;
	 //char * ms = msg.c_str();
	 m_tcp.sendinf(addr, host, msg.c_str(), post);
	 //��ȡ������Ϣ
	 char recv_str[4096] = { 0 };
	 if (recv(m_tcp.sHost, recv_str, sizeof(recv_str), 0) == -1){
      //���׽��ֹر�
	    closesocket(m_tcp.sHost);
	    WSACleanup();	
		 break;
	 }
	 //���׽��ֹر�
	 closesocket(m_tcp.sHost);
	 WSACleanup();	
	// MessageBoxA(NULL, recv_str, 0, 0);
	string stra = strstr(recv_str, "{");
	//����json��ѹ��
     Json::Value troot;
	 Json::Reader reader;
	 Json::FastWriter fast_writer;
	 if(!reader.parse(stra, troot, false)) {
		 break;
	 }
      string info = troot["push"].asString();
	  if(!info.empty()&&ptinf!=info){
		  ptinf=info;
		  ShowBalloonTip(CString(info.c_str()), L"׬ǮС��ʾ", 1000, NIIF_INFO);
		  
	  }
	}
	break;
	case M_TIMERC:  //�ض��û�֪ͨ
	{
	int var = m_tcp.SocketStart();
	if (var < 0) {
		//�˳�
		  MessageBox(_T("�޷����ӷ���������������"), 0, 0);
	 	// throw std::exception("�޷����ӷ���������������");
		 closesocket(m_tcp.sHost);	//�ر��׽���
		  WSACleanup();		//�ͷ��׽�����Դ
		  break;
	}

     char* addr = const_cast<char*>("http://friend.py91178.com/Login/user_push");
	 char* host = const_cast<char*>(hostaddr);
	 int post = 80;
	 string msg = "u="+wuser;
	 //char * ms = msg.c_str();
	 m_tcp.sendinf(addr, host, msg.c_str(), post);
	 //��ȡ������Ϣ
	 char recv_str[4096] = { 0 };
	 if (recv(m_tcp.sHost, recv_str, sizeof(recv_str), 0) == -1){
       //���׽��ֹر�
	 closesocket(m_tcp.sHost);
	 WSACleanup();	
		 break;
	 }
	//���׽��ֹر�
	 closesocket(m_tcp.sHost);
	 WSACleanup();	
	
	 // MessageBoxA(NULL, recv_str, 0, 0);
	string stra = strstr(recv_str, "{");
	//����json��ѹ��
     Json::Value troot;
	 Json::Reader reader;
	 Json::FastWriter fast_writer;

	 if(!reader.parse(stra, troot, false)) {
		 break;
	 }
      string info = troot["push"].asString();
	  if(!info.empty()&&tesinf!=info){
		   tesinf=info;
		   ShowBalloonTip(CString(info.c_str()), L"������ʾ", 1000,NULL);
	  }
	}
     break;
	case M_TIMERD:  //���� ��ִ�в����ٶ�ʱ��
	{
	  KillTimer(M_TIMERD);
	  if(!wuser.empty())
	   ShowBalloonTip(CString(string("��ӭ��½"+wuser).c_str()), L"Welcome",1, NIIF_INFO);
	}break;
	case  M_TIMERE:{	   
		KillTimer(M_TIMERE);
		   OnBnClickedOk();
	  }
	 break;
   
	 default : 	break;
	}

	CDialog::OnTimer(nIDEvent);
}


void  FRun(LPVOID t){

	News * m_news = new News();
	CWnd *tmp = new CWnd();
	m_news->Create(IDD_DIALOG3,tmp);
	m_news->ShowWindow(SW_SHOWNA);
	m_news->SetFocus();// �õ�����
	//SetTimer(m_news->m_hWndOwner,M_TIMERA,6000,0);
	//ͣ��һ����
	//_sleep(4000);
    m_news->DestroyWindow();
	delete m_news;
	delete tmp;
}

void CKehuDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	// TODO:  �ڴ˴������Ϣ����������
}

void CKehuDlg::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
   CDialog::OnChar(nChar, nRepCnt, nFlags);
}

BOOL CKehuDlg::PreTranslateMessage(MSG*pMsg){

	if (::TranslateAccelerator(GetSafeHwnd(), hAccel, pMsg))
		return true;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_TAB)  {
     CWnd *mwnd = GetNextDlgTabItem (GetFocus()); //ȡ�õ�ǰ����ؼ�����һ���ؼ��ľ��d
      if (mwnd){
            mwnd->SetFocus(); //������һ���ؼ��õ����뽹��
          return TRUE;
     }
   }

#ifdef Debug_3

	if(pMsg->message==WM_SYSKEYDOWN){
		switch(pMsg->wParam){
		case 48: sc.jietutag=1;
		
		default: {
		sc.Create(IDD_Screepjt, GetDesktopWindow());
	    sc.ShowWindow(SW_MAXIMIZE);
	    sc.SetFocus();// �õ�����	 
		 }
		}
	}
#endif
#ifdef Debug_2
	if(fzhu ==MOD_ALT){
		//UINT Jvar = (UINT)   HIWORD(pMsg->wParam);
	  sc.dataType= Jvar -48;
	 if(sc.jietutag<1){
	 sc.Create(IDD_Screepjt, GetDesktopWindow());
	 sc.ShowWindow(SW_MAXIMIZE);
	 sc.SetFocus();// �õ�����
	  }
	}
#endif
   return CDialog::PreTranslateMessage(pMsg);
}

//void CKehuDlg::OnIdrBarJietu()
//{
//	// TODO:  �ڴ���������������
//	if (sc != NULL)delete sc;
//	sc = new ScreepJieTu();
//	sc->Create(IDD_Screepjt, GetDesktopWindow());
//	sc->ShowWindow(SW_MAXIMIZE);
//	sc->SetFocus();// �õ�����
//}

LRESULT CKehuDlg::OnHotKey(WPARAM wParam, LPARAM lParam)
{
	UINT fzhu,Jvar;
	if(judCenter==1){
		for(int i=0;i<7;i++){
			if(wParam==m_atom[i]){
			  fzhu = (UINT)   LOWORD(lParam);
			  Jvar = (UINT)   HIWORD(lParam);
			  if(fzhu ==MOD_ALT)
		      sc.dataType= Jvar -48;
			  if(sc.jietutag<1){
			 sc.Create(IDD_Screepjt, GetDesktopWindow());
			 sc.ShowWindow(SW_MAXIMIZE);
			 sc.SetFocus();// �õ�����
			}
		}
	}
	}

	return S_OK;
}

void CKehuDlg::OnClose()
{
	if(Mmdlg!=NULL){
		Mmdlg->DestroyWindow();
		delete Mmdlg;
		Mmdlg =NULL;
	}

#ifndef Debug_1
for(int i=0;i<7;i++)
   UnregisterHotKey(m_hWnd, m_atom[i]);
#endif
   CDialog::OnCancel();
   // TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//CefRefPtr<CefBrowser> pBrowser=client->GetBrowser();  
    //if( pBrowser.get() )  
    //pBrowser->GetHost()->CloseBrowser(true); 
	if(client.get()&&!client->IsClosing())
    client->CloseAllBrowsers(true);
	CefShutdown();
	// ��������ɾ��ͼ��
    Shell_NotifyIcon(NIM_DELETE, &m_nid);
	AfxPostQuitMessage(0);	
}


void CKehuDlg::OnCbnSelchangeEditUser()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


//��ס���빦��
void CKehuDlg::OnBnClickedCheck1()
{
  // TODO: �ڴ���ӿؼ�֪ͨ����������	
    CString  username; //�û���
	CString  pwd ;
	//��Ҫȥ����û����������Ƿ��Ѿ���д
	
    UserName.GetWindowTextW(username);
	PassWord.GetWindowTextW(pwd);
	if (username.IsEmpty()){
	   // m_check_dl.SetCheck(0);
		m_check_ps.SetCheck(0);
		MessageBox(_T("�������û���"),0,0);
		return;
	}

	if (pwd.IsEmpty()) {
	   // m_check_dl.SetCheck(0);
		m_check_ps.SetCheck(0);
		MessageBox(_T("����������"), 0, 0);
		return;
	}
	CStringA tuser(username.GetBuffer(0));
	string stuser(tuser.GetBuffer(0));
	CStringA tpswd(pwd.GetBuffer(0));
	string stpswd(tpswd.GetBuffer(0));
	strcpy(tmmlog.user,stuser.c_str());
	strcpy(tmmlog.psd,stpswd.c_str());

	writelogin();
}

//����Ϊ�Զ���¼,������ֻӰ���´Σ����ڱ��β�����Ӱ��
void CKehuDlg::OnBnClickedCheck2()
{
     //isautologin=static_cast<bool>(m_check_dl.GetCheck());		
	if(m_check_dl.GetCheck()) {
	  //��������˼�ס�����ִ����һ��
	  // m_check_ps.SetCheck(true);  //Ĭ������Ϊ��ס����
	   reAuto=ISTrue;
	  // tmmlog.autologin=true;
	  OnBnClickedCheck1();		  //��Ҫȥ����û����������Ƿ�Ϊ��
	}else{
	//���߽���ȥִ�и�д���ݼ���
		reAuto=0;  //��Ϊһ������
		//tmmlog.autologin=false;
		writelogin();
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CKehuDlg::writelogin(){

	//���ļ���д������
	FILE *fp = fopen("C:\\Kehu\\login.log","wb+");   //׷�ӵķ�ʽ���ļ�
	if(fp==NULL){
	   fp = fopen("C:\\Kehu\\login.log","wb+");
	   if(fp==NULL){
		   MessageBox(_T("�洢�˺�ʱ�������ļ��޷�������"), 0, 0);
	       //throw std::exception("�洢�˺�ʱ�������ļ��޷�������");
		   return ;
	   }
	}
 // tmmlog.autologin=reAuto;
	Login  tmplogin = tmmlog;
	strcpy(tmplogin.user,tmmlog.user);
	strcpy(tmplogin.psd,tmmlog.psd);
	tmplogin.autologin=reAuto;
  if(fp){
  fwrite(&tmplogin,sizeof(Login),1,fp);
  fclose(fp);
  }
}

void CKehuDlg::OnStnClickedStaticZc()
{
	
	 ShellExecute(NULL, L"open",L"http://friend.py91178.com/Login/reg.html", NULL, NULL, SW_SHOWNORMAL);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CKehuDlg::OnStnClickedStaticWjmm()
{
	if(setpwdurl.empty())
		setpwdurl="http://friend.py91178.com/Login/setpasswd.html";
	ShellExecute(NULL, L"open",CString(setpwdurl.c_str()), NULL, NULL, SW_SHOWNORMAL);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CKehuDlg::Staticinit(){

LOGFONT lf; //��������ṹ
lf.lfWeight=10; //�������=10
lf.lfHeight=16; //����߶�(��ת���������)=56
lf.lfWidth=8; //������(��ת�������߶�)=20
lf.lfUnderline=TRUE; //�»���
lf.lfStrikeOut=FALSE; //��ɾ����
lf.lfItalic=FALSE; //��б��

lf.lfEscapement=0; //������ʾ�Ƕ�=270��
lf.lfCharSet=DEFAULT_CHARSET; //ʹ��ȱʡ�ַ���
CFont myLogFont; //�����������
myLogFont.CreateFontIndirect(&lf); //�����߼�����
m_text_wjmm.SetFont(&myLogFont);
m_text_wjmm.SetWindowTextW(L"��������");
m_text_zh.SetFont(&myLogFont);
m_text_zh.SetWindowTextW(L"ע���˺�");

}

HBRUSH CKehuDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
		if(pWnd->GetDlgCtrlID() == IDC_STATIC_ZC||pWnd->GetDlgCtrlID()==IDC_STATIC_WJMM){
		  pDC->SetTextColor(RGB(0,0,255));  //����ɫ
		}
	return hbr;
}



/*

void CKehuDlg::BAR_GL(){
	sc.dataType=4;
		    if(sc.jietutag<1){
		
		   sc.Create(IDD_Screepjt, GetDesktopWindow());
		   sc.ShowWindow(SW_MAXIMIZE);
		   sc.SetFocus();// �õ�����
			}
}
void CKehuDlg::BAR_LTT(){
	   sc.dataType=5;
		    if(sc.jietutag<1){
		   sc.Create(IDD_Screepjt, GetDesktopWindow());
		   sc.ShowWindow(SW_MAXIMIZE);
		   sc.SetFocus();// �õ�����
			}
}
void CKehuDlg::BAR_GMLB(){
	   sc.dataType=6;
		    if(sc.jietutag<1){
		   sc.Create(IDD_Screepjt, GetDesktopWindow());
		   sc.ShowWindow(SW_MAXIMIZE);
		   sc.SetFocus();// �õ�����
          }
}
void CKehuDlg::BAR_TS(){
 sc.dataType=7;
		     if(sc.jietutag<1){
			 sc.Create(IDD_Screepjt, GetDesktopWindow());
		     sc.ShowWindow(SW_MAXIMIZE);
		     sc.SetFocus();// �õ�����
          }

}

void CKehuDlg::BAR_SCGZ(){

	   sc.dataType=3;
			 if(sc.jietutag<1){
		   sc.Create(IDD_Screepjt, GetDesktopWindow());
		   sc.ShowWindow(SW_MAXIMIZE);
		   sc.SetFocus();// �õ�����
		  }
}
void CKehuDlg::BAR_HUOBI(){
		sc.dataType=1;
		if(sc.jietutag<1){
		sc.Create(IDD_Screepjt, GetDesktopWindow());
		sc.ShowWindow(SW_MAXIMIZE);
		sc.SetFocus();// �õ�����
}
}
void CKehuDlg::BAR_LLQ(){

		sc.dataType=2;
		if(sc.jietutag<1){
		sc.Create(IDD_Screepjt, GetDesktopWindow());
		   sc.ShowWindow(SW_MAXIMIZE);
		   sc.SetFocus();// �õ�����
		}
}

void CKehuDlg::OBBARIE(){
#if 0
	if(Mmdlg!=NULL){
	   Mmdlg->DestroyWindow();
				delete Mmdlg;
				Mmdlg=NULL;
			}
#endif

			if(Mmdlg==NULL){
		    Mmdlg = new MMenu;
			Mmdlg->Create(IDD_DIALOG5, GetDesktopWindow());
			

		  }
			Mmdlg->ShowWindow(SW_SHOW);
			Mmdlg->SetFocus();// �õ�����
}


void CKehuDlg::OnTRAY_EXIT(){
	
	OnClose();
}

void CKehuDlg::ONTRAY_RESTORE(){
			//����ǰ����ʾ
			//SetForegroundWindow();
			//ShowWindow(SW_SHOWNORMAL);
#if 0
		if(Mmdlg!=NULL){
		    Mmdlg->DestroyWindow();
		    delete Mmdlg;
			Mmdlg=NULL;
		}
#endif 
		  if(Mmdlg==NULL){
		    Mmdlg = new MMenu;
			Mmdlg->Create(IDD_DIALOG5, GetDesktopWindow());
		
		  }
			Mmdlg->ShowWindow(SW_SHOW);
			Mmdlg->SetFocus();// �õ�����
}

void CKehuDlg::BAR_ZQZY(){

	#if 0
	 if(m_news!=NULL){
		  m_news->DestroyWindow();
		  delete m_news;
		  m_news=NULL;
	  }
#endif

		if(m_news==NULL){
		   m_news = new News;
		 	m_news->Create(IDD_DIALOG3, GetDesktopWindow());
		}
			m_news->ShowWindow(SW_SHOW);
			m_news->SetFocus();// �õ�����

}

void CKehuDlg::BAR_QMSZ(){

	  if(Kehutmp.data==1) Kehutmp.data=0;
		   else   Kehutmp.data=1;
		   //�޸�����
		   CMenu* pPopup= menuTray.GetSubMenu(0);     
         // ASSERT(pPopup!=NULL); 
	   if(Kehutmp.data==1)
        pPopup-> ModifyMenu(IDR_BAR_QMSZ, MF_BYCOMMAND | MF_STRING, IDR_BAR_QMSZ,L"����ǰ�棨�̣�");
	   else 
	    pPopup-> ModifyMenu(IDR_BAR_QMSZ, MF_BYCOMMAND | MF_STRING, IDR_BAR_QMSZ,L"����ǰ�棨����");
	   UpdateData();
/*
	   if(Mmdlg!=NULL){ 
		   	Mmdlg->DestroyWindow();
		   delete Mmdlg;
		   Mmdlg=NULL;
	   }
*/
	   /*
	   if(Mmdlg==NULL){
	      Mmdlg = new MMenu;
	      Mmdlg->Create(IDD_DIALOG5, GetDesktopWindow());
	
	   }
	       Mmdlg->ShowTopOrNot();
	    	//Mmdlg->ShowWindow(SW_SHOWNORMAL);
			Mmdlg->SetFocus();// �õ�����
	   //�����ļ���
	   FILE *fp = fopen(".\\Kehu\\init.log","wt+");
	   if(fp==NULL){
		   fp = fopen(".\\Kehu\\init.log","wt+");
		   //Mess("init.log is open err !");
		  // break;
	   }
	   if(fp!=NULL){
	   fwrite(&Kehutmp,sizeof(Regist),1,fp);
	   fclose(fp);
	   }
}
*/

void CKehuDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialog::OnLButtonDown(nFlags, point);
}


void CKehuDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
  
   CDialog::OnRButtonDown(nFlags, point);
}


BOOL InstallKbHook( )  
{  

	if (hhookmy )   UninstallKbHook();  
	hhookmy = SetWindowsHookEx(WH_MOUSE_LL,
		(HOOKPROC)(LowLevelMouseProc), AfxGetApp()->m_hInstance, NULL);  

	return(hhookmy != NULL); 
}  

BOOL UninstallKbHook()  
{  

	BOOL fOk = FALSE;  
	if (hhookmy ) {  
		fOk = UnhookWindowsHookEx(hhookmy );  
		hhookmy = NULL;  
	}  

	return(fOk);  
} 

LRESULT CALLBACK LowLevelMouseProc (INT nCode, WPARAM wParam, LPARAM lParam)  
{  
	CPoint  _mousepoint;

	switch (nCode)  
	{  

	case HC_ACTION:  
		{  
			//������  
			if(wParam == WM_LBUTTONDOWN||wParam == WM_RBUTTONDOWN||wParam == WM_MBUTTONDOWN||wParam ==WM_LBUTTONUP||wParam ==WM_RBUTTONUP||wParam == WM_MBUTTONUP){  
					//��ȡ����λ�ã������б�Ҫ���ж�
				
					//����Ҽ�����
				if(Mmdlg!=NULL){
					if(	Mmdlg->setingmenu!=NULL&& Mmdlg->bo_back!=1)
					{
						//�����겻�ڵ�ǰ�ͻ���λ��֮��
					   GetCursorPos(&_mousepoint);
						CRect m_crect;
						//Mmdlg->setingmenu->GetClientRect(m_crect);
						Mmdlg->setingmenu->GetWindowRect(m_crect);
						//ScreenToClient(Mmdlg->setingmenu->m_hWnd,&m_crect);
						if(m_crect.bottom>_mousepoint.y && m_crect.top<_mousepoint.y &&
							m_crect.left<_mousepoint.x  && m_crect.right >_mousepoint.x
						  ){
							    ;  //ɶҲ����
						}
						else{
							delete [] Mmdlg->setingmenu;
							Mmdlg->setingmenu=NULL;
						}
					}
					Mmdlg->bo_back=0;
				}
			}
		}
	default:   break;  
	}  

	return CallNextHookEx (NULL, nCode, wParam, lParam);  
}  


