
// KehuDlg.h : ���^�n
//
#pragma once
#include "afxwin.h"
#include "MMenu.h"
#include"News.h"
#include "TcpSocket.h"
#include"ScreepJieTu.h"
//#include "ControlBase.h"
//NOTIFYICONDATA m_nid;



// CKehuDlg ��Ԓ���K
class CKehuDlg : public CDialog
{

// ����

public:
	CKehuDlg(CWnd* pParent = NULL);	// �˜ʽ�����ʽ
	~CKehuDlg();

// ��Ԓ���K�Y��
	enum { IDD = IDD_KEHU_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧Ԯ


// ��ʽ�a����
protected:
	HICON m_hIcon;

	// �a����ӍϢ������ʽ
	virtual BOOL OnInitDialog();
	//��ӿ�ݼ��麯��
	virtual BOOL PreTranslateMessage(MSG*pMsg);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	NOTIFYICONDATA  m_nid;  //ϵͳ����
	CStatic  Yzm_Bitmap;   //�趨��֤�����
	afx_msg void OnEnChangeEdit3();
afx_msg void OnBnClickedOk();
afx_msg void OnBnClickedCancel();
afx_msg void OnBnClickedButton1();
afx_msg void OnEnChangeEdit1();
afx_msg void OnStnClickedStaticYzm();
afx_msg void OnBnClickedSxin();

//���̺���
afx_msg LRESULT OnTrayNotify(WPARAM wParam, LPARAM lParam);
afx_msg LRESULT OnHotKey(WPARAM wParam, LPARAM lParam);
afx_msg BOOL ShengChengYanZhenMa(CString str, CFile& file);//������֤��
afx_msg BOOL myCreateBitmap(HDC hDC, HBITMAP hbitmap,
	PBITMAPFILEHEADER &outheadbuf, long *outheadsize,
	PBITMAPINFO &outinfobuf, long *outinfosize,
	LPBYTE &outdatabuf, long *outdatasize);	//���ɵ�ɫλͼ					
afx_msg void OnStnClickedStaticTitle();
afx_msg void OnEnChangeEditUser();
// �û���
CEdit UserName;
// ����
CEdit PassWord;
// ��֤��
CEdit Yanzma;
CString strname;
News    *m_news;   //��ʾ���Ž���
ScreepJieTu sc;      //ȫ�ֽ�ͼ����
TcpSocket m_tcp;
RECT  poswind;
afx_msg void OnEnChangeEditYzm();
afx_msg BOOL DestroyWindow();
afx_msg void OnSize(UINT nType, int cx, int cy);
afx_msg void OnStnClickedStatictouxiang();
afx_msg void OnEnChangeEditPsw();
BOOL ShowBalloonTip(LPCTSTR szMsg, LPCTSTR szTitle,
UINT uTimeout, DWORD dwInfoFlags);//��ʾ������ʾ
afx_msg void OnTimer(UINT_PTR nIDEvent);
friend void  FRun(LPVOID );
void Staticinit();
afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

CTime tm;      //ʱ���������������
int tm_var;    //���ڼ�������೤ʱ�䣬��λΪ����
int tm_h,tm_m,tm_s;
afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
HACCEL hAccel;  //���һ����ݼ�
//afx_msg void OnIdrBarJietu();
BOOL IsLogin ,ISFirst;
//�Ҽ�����
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
CButton m_button_login;				//��¼��ť
CButton m_button_cance;				//ȡ����¼

string wuser ,ptinf,tesinf;
BOOL  judPos;  
int reAuto,judCenter; /*judCenter �����ж��Ƿ�ʹ���Ѿ��ɹ���½*/
void writelogin();
ATOM m_atom[7];    //����ȫ��ԭ��

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


