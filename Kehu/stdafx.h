
// stdafx.h : 可在此標頭檔中包含標準的系統 Include 檔，
// 或是經常使用卻很少變更的
// 專案專用 Include 檔案

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 從 Windows 標頭排除不常使用的成員
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 明確定義部分的 CString 建構函式
//#define _AFX_NO_MFC_CONTROLS_IN_DIALOGS         // 在對話方塊中移除 MFC 控制項的支援

// 關閉 MFC 隱藏一些常見或可忽略警告訊息的功能
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心與標準元件
#include <afxext.h>         // MFC 擴充功能
#include <afxdisp.h>        // MFC Automation 類別




#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 支援的 Internet Explorer 4 通用控制項
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 支援的 Windows 通用控制項
#endif // _AFX_NO_AFXCMN_SUPPORT


#include <afxcontrolbars.h>     // 功能區和控制列的 MFC 支援
#include <afxdhtml.h>
#include <iostream>
#include <cef_browser.h>
#include <cef_cookie.h>  //设置cookie
#include <cef_runnable.h>
#include "CWebClient.h"



/**下面字符串用来存贮各个功能的超链接**/
 extern std::string order;    //领取任务URL
 extern std::string manage;   //管理栏URL
 extern std::string study;    //学习中心
 extern std::string center;   //用户中心
extern  std::string today_money;  //今天赚钱新闻
extern  std::string userinf;   //账号信息
extern  std::string rpepage;  //申诉中心
extern  std::string infor;  //消息中心 
extern  std::string helpcen; //帮助中心
extern std::string SessinID;  //获取cookieid
extern std::string MainUrl;   //获取MainUrl路径

extern std::string al_username ;
extern std::string al_loginId ;
extern	CefCookie cookie;
extern 	CefRefPtr<CWebClient>client;
extern CString DengjiPath; //等级文件的相对路径
extern CefSettings cSettings;
extern CefRefPtr<CefApp>spApp;
extern CefRefPtr<CefCookieManager> manager;
extern bool go_head;
//设置结构体，关于注册表的信息

typedef struct regist{
	char name[20];
	char status[20];
	int  data;
}Regist;

extern CString  apath;   //记录保存图片路径

typedef struct login{

 	 char  user[30];   //用户账号
	 char  psd[20];    //用户密码
	 int  autologin;   //用户登录状态
}Login;


extern int cont_Appcnt;

extern 	Regist  Kehutmp;


extern int cx1, cy1;

extern Login tmmlog;

extern string setpwdurl; 
//通过mod生成三个变量
extern 	HANDLE hMutex[3];
#ifndef WINVER
#define WINVER 0X500
#endif

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

