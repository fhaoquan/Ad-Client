
// stdafx.h : ���ڴ˘��^�n�а����˜ʵ�ϵ�y Include �n��
// ���ǽ���ʹ�Ås����׃����
// �������� Include �n��

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ���^�ų�����ʹ�õĳɆT
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ���_���x���ֵ� CString ������ʽ
//#define _AFX_NO_MFC_CONTROLS_IN_DIALOGS         // �ڌ�Ԓ���K���Ƴ� MFC ����헵�֧Ԯ

// �P�] MFC �[��һЩ��Ҋ��ɺ��Ծ���ӍϢ�Ĺ���
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC �����c�˜�Ԫ��
#include <afxext.h>         // MFC �U�书��
#include <afxdisp.h>        // MFC Automation e




#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC ֧Ԯ�� Internet Explorer 4 ͨ�ÿ����
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC ֧Ԯ�� Windows ͨ�ÿ����
#endif // _AFX_NO_AFXCMN_SUPPORT


#include <afxcontrolbars.h>     // ���܅^�Ϳ����е� MFC ֧Ԯ
#include <afxdhtml.h>
#include <iostream>
#include <cef_browser.h>
#include <cef_cookie.h>  //����cookie
#include <cef_runnable.h>
#include "CWebClient.h"



/**�����ַ������������������ܵĳ�����**/
 extern std::string order;    //��ȡ����URL
 extern std::string manage;   //������URL
 extern std::string study;    //ѧϰ����
 extern std::string center;   //�û�����
extern  std::string today_money;  //����׬Ǯ����
extern  std::string userinf;   //�˺���Ϣ
extern  std::string rpepage;  //��������
extern  std::string infor;  //��Ϣ���� 
extern  std::string helpcen; //��������
extern std::string SessinID;  //��ȡcookieid
extern std::string MainUrl;   //��ȡMainUrl·��

extern std::string al_username ;
extern std::string al_loginId ;
extern	CefCookie cookie;
extern 	CefRefPtr<CWebClient>client;
extern CString DengjiPath; //�ȼ��ļ������·��
extern CefSettings cSettings;
extern CefRefPtr<CefApp>spApp;
extern CefRefPtr<CefCookieManager> manager;
extern bool go_head;
//���ýṹ�壬����ע������Ϣ

typedef struct regist{
	char name[20];
	char status[20];
	int  data;
}Regist;

extern CString  apath;   //��¼����ͼƬ·��

typedef struct login{

 	 char  user[30];   //�û��˺�
	 char  psd[20];    //�û�����
	 int  autologin;   //�û���¼״̬
}Login;


extern int cont_Appcnt;

extern 	Regist  Kehutmp;


extern int cx1, cy1;

extern Login tmmlog;

extern string setpwdurl; 
//ͨ��mod������������
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

