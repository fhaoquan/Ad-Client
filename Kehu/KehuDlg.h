
// KehuDlg.h : 標頭檔
//
#pragma once
#include "afxwin.h"
#include "MMenu.h"
#include"News.h"
#include "TcpSocket.h"
#include"ScreepJieTu.h"
//#include "ControlBase.h"
//NOTIFYICONDATA m_nid;



// CKehuDlg 對話方塊
class CKehuDlg : public CDialog
{

// 建構

public:
	CKehuDlg(CWnd* pParent = NULL);	// 標準建構函式
	~CKehuDlg();

// 對話方塊資料
	enum { IDD = IDD_KEHU_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援


// 程式碼實作
protected:
	HICON m_hIcon;

	// 產生的訊息對應函式
	virtual BOOL OnInitDialog();
	//添加快捷键虚函数
	virtual BOOL PreTranslateMessage(MSG*pMsg);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	NOTIFYICONDATA  m_nid;  //系统托盘
	CStatic  Yzm_Bitmap;   //设定验证码变量
	afx_msg void OnEnChangeEdit3();
afx_msg void OnBnClickedOk();
afx_msg void OnBnClickedCancel();
afx_msg void OnBnClickedButton1();
afx_msg void OnEnChangeEdit1();
afx_msg void OnStnClickedStaticYzm();
afx_msg void OnBnClickedSxin();

//托盘函数
afx_msg LRESULT OnTrayNotify(WPARAM wParam, LPARAM lParam);
afx_msg LRESULT OnHotKey(WPARAM wParam, LPARAM lParam);
afx_msg BOOL ShengChengYanZhenMa(CString str, CFile& file);//生成验证码
afx_msg BOOL myCreateBitmap(HDC hDC, HBITMAP hbitmap,
	PBITMAPFILEHEADER &outheadbuf, long *outheadsize,
	PBITMAPINFO &outinfobuf, long *outinfosize,
	LPBYTE &outdatabuf, long *outdatasize);	//生成单色位图					
afx_msg void OnStnClickedStaticTitle();
afx_msg void OnEnChangeEditUser();
// 用户名
CEdit UserName;
// 密码
CEdit PassWord;
// 验证码
CEdit Yanzma;
CString strname;
News    *m_news;   //显示新闻界面
ScreepJieTu sc;      //全局截图部分
TcpSocket m_tcp;
RECT  poswind;
afx_msg void OnEnChangeEditYzm();
afx_msg BOOL DestroyWindow();
afx_msg void OnSize(UINT nType, int cx, int cy);
afx_msg void OnStnClickedStatictouxiang();
afx_msg void OnEnChangeEditPsw();
BOOL ShowBalloonTip(LPCTSTR szMsg, LPCTSTR szTitle,
UINT uTimeout, DWORD dwInfoFlags);//显示泡泡提示
afx_msg void OnTimer(UINT_PTR nIDEvent);
friend void  FRun(LPVOID );
void Staticinit();
afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

CTime tm;      //时间变量，用于气泡
int tm_var;    //用于计算想个多长时间，单位为秒钟
int tm_h,tm_m,tm_s;
afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
HACCEL hAccel;  //添加一个快捷键
//afx_msg void OnIdrBarJietu();
BOOL IsLogin ,ISFirst;
//右键处理
CMenu menuTray ,UlMenu,*pmenu;

int menuid;
afx_msg void OnClose();

afx_msg void OnCbnSelchangeEditUser();
afx_msg void OnBnClickedCheck1();
afx_msg void OnBnClickedCheck2();
CButton m_check_ps;
CButton m_check_dl;
afx_msg void OnStnClickedStaticZc();
afx_msg void OnStnClickedStaticWjmm();
CStatic m_text_zh;
CStatic m_text_wjmm;
CButton LCance;   
afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
CButton m_button_login;				//登录按钮
CButton m_button_cance;				//取消登录

string wuser ,ptinf,tesinf;
BOOL  judPos;  
int reAuto,judCenter; /*judCenter 用来判断是否使用已经成功登陆*/
void writelogin();
ATOM m_atom[7];    //保存全局原子

/*
afx_msg void OnTRAY_EXIT();
afx_msg void ONTRAY_RESTORE();
afx_msg void OBBARIE();
afx_msg void BAR_HUOBI();
afx_msg void BAR_LLQ();
afx_msg void BAR_SCGZ();
afx_msg void BAR_GL();
afx_msg void BAR_LTT();
afx_msg void BAR_GMLB();
afx_msg void BAR_TS(); 
afx_msg void BAR_QMSZ();
afx_msg void BAR_ZQZY();
*/
afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
afx_msg void OnRButtonDown(UINT nFlags, CPoint point);



};


