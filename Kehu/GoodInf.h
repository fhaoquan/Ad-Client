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
// 账号等级
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
// 账号
CEdit ZhanghaoNum;
// 出生年月
CEdit Birth;
// 收货人
CEdit ShouHuoRen;
// 切号上传
CEdit QiehaoShangc;
// 详细地址
CEdit Xiangxdiz;
//图片保存地址
CString m_str_save_path;
// 省
CComboBox Provice;
// 市
CComboBox shiqu;
// 县，区
CComboBox xianqu;
//设置购物者局部变量

//设置的头像
CImage Touxiang;

BOOL JudXY; //判断是显示还是隐藏
CRect m_rect;  //为了恢复区域
struct py_user_shop buy;
afx_msg void OnCbnSelchangeCombo2();
afx_msg void OnEnChangeEdit2();
// 男
int Man;
// 女
int women;
afx_msg void OnBnClickedRadio1();
afx_msg void OnBtnPrintScreen();
afx_msg void WriteBmpToFile(HBITMAP hBitmap);
afx_msg void CopyBmpToClipBoard(HBITMAP hBitmap);
afx_msg void OnBnClickedRadio2();
// //电话号码
CEdit Iphone;
afx_msg void OnBnClickedButton3();
// 计时器
CEdit DTime;
afx_msg void OnEnChangeEdit8();
bool time_cnt;
string number;
string coder;
TcpSocket m_tcp;
int cnt; //计数器
int tmpvar; //随机码

afx_msg void OnTimer(UINT_PTR nIDEvent);
// 随机口令
CEdit SjiMa;

CString PicReaaPath ;   //文件的相对路径

// //全部提交
CButton Submit_All;
// //账号类型
CStatic m_zhlx;
// //账号等级
CStatic m_zhdj;
// 收货地址
CStatic m_shdz;
// 详细收货地址
CStatic m_xxshdz;
// 账号实名切图上传
CStatic m_zhqtsc;
// 账号切号上传地址
CStatic m_zhqhscdz;
// 电话验证
CStatic m_dhyz;
// 短信口令
CStatic m_dxkl;
// 上传
CButton m_sc;
// 获取口令
CButton m_hqkl;

};
