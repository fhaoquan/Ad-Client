
// stdafx.cpp : �H�����˜� Include �n��ԭʼ��ʽ�n
// Kehu.pch ���ɞ����о��g���^�n
// stdafx.obj ���������о��g����YӍ

#include "stdafx.h"

 std::string SessinID;

 std::string order;    //��ȡ����URL
 std::string manage;   //������URL
 std::string study;
 std::string center;  
 std::string userinf;	
 std::string rpepage;
 std::string infor;
 std::string helpcen;
 std::string al_username ;
 std::string al_loginId ;

bool go_head;

 CefCookie cookie;
   std::string today_money;
 std::string MainUrl="http://friend.py91178.com/Task/hall.html";

 Regist  Kehutmp;

 int cont_Appcnt=0;
 
 CefRefPtr<CWebClient> client;

 CString  apath;   //��¼����ͼƬ·��
 CString DengjiPath; //�ȼ��ļ������·��
 int cx1, cy1;
	CefSettings cSettings;
	CefRefPtr<CefApp>spApp;
	CefRefPtr<CefCookieManager> manager;
	Login tmmlog;
	string setpwdurl; 
	HANDLE hMutex[3]={NULL};