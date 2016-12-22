
// stdafx.cpp : 僅包含標準 Include 檔的原始程式檔
// Kehu.pch 會成為先行編譯標頭檔
// stdafx.obj 會包含先行編譯類型資訊

#include "stdafx.h"

 std::string SessinID;

 std::string order;    //领取任务URL
 std::string manage;   //管理栏URL
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

 CString  apath;   //记录保存图片路径
 CString DengjiPath; //等级文件的相对路径
 int cx1, cy1;
	CefSettings cSettings;
	CefRefPtr<CefApp>spApp;
	CefRefPtr<CefCookieManager> manager;
	Login tmmlog;
	string setpwdurl; 
	HANDLE hMutex[3]={NULL};