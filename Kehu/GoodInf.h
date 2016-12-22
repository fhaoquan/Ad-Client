#pragma once
#include "afxwin.h"
#include<string>
#include"allvar.h"
#include "TcpSocket.h"
// GoodInf dialog

class GoodInf : public CDialogEx
{
	DECLARE_DYNAMIC(GoodInf)

public:

	GoodInf(CWnd* pParent = NULL);   // standard constructor
	virtual ~GoodInf();

// Dialog Data
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
CComboBox ZhangHaoType;
// �˺ŵȼ�
CComboBox ZhangHaoLevel;
std::string SexType;
afx_msg void OnCbnSelchangeCombo1();

afx_msg void OnEnChangeEdit3();
afx_msg void OnEnChangeEdit4();
afx_msg void OnCbnSelchangeCombo4();
afx_msg void OnCbnSelchangeCombo3();
afx_msg void OnCbnSelchangeCombo5();
afx_msg void OnEnChangeEdit5();
afx_msg void OnBnClickedButton2();
afx_msg void OnBnClickedButton1();
// �˺�
CEdit ZhanghaoNum;
// ��������
CEdit Birth;
// �ջ���
CEdit ShouHuoRen;
// �к��ϴ�
CEdit QiehaoShangc;
// ��ϸ��ַ
CEdit Xiangxdiz;
//ͼƬ�����ַ
CString m_str_save_path;
// ʡ
CComboBox Provice;
// ��
CComboBox shiqu;
// �أ���
CComboBox xianqu;
//���ù����߾ֲ�����

//���õ�ͷ��
CImage Touxiang;

BOOL JudXY; //�ж�����ʾ��������
CRect m_rect;  //Ϊ�˻ָ�����
struct py_user_shop buy;
afx_msg void OnCbnSelchangeCombo2();
afx_msg void OnEnChangeEdit2();
// ��
int Man;
// Ů
int women;
afx_msg void OnBnClickedRadio1();
afx_msg void OnBtnPrintScreen();
afx_msg void WriteBmpToFile(HBITMAP hBitmap);
afx_msg void CopyBmpToClipBoard(HBITMAP hBitmap);
afx_msg void OnBnClickedRadio2();
// //�绰����
CEdit Iphone;
afx_msg void OnBnClickedButton3();
// ��ʱ��
CEdit DTime;
afx_msg void OnEnChangeEdit8();
bool time_cnt;
string number;
string coder;
TcpSocket m_tcp;
int cnt; //������
int tmpvar; //�����

afx_msg void OnTimer(UINT_PTR nIDEvent);
// �������
CEdit SjiMa;

CString PicReaaPath ;   //�ļ������·��

// //ȫ���ύ
CButton Submit_All;
// //�˺�����
CStatic m_zhlx;
// //�˺ŵȼ�
CStatic m_zhdj;
// �ջ���ַ
CStatic m_shdz;
// ��ϸ�ջ���ַ
CStatic m_xxshdz;
// �˺�ʵ����ͼ�ϴ�
CStatic m_zhqtsc;
// �˺��к��ϴ���ַ
CStatic m_zhqhscdz;
// �绰��֤
CStatic m_dhyz;
// ���ſ���
CStatic m_dxkl;
// �ϴ�
CButton m_sc;
// ��ȡ����
CButton m_hqkl;

};
