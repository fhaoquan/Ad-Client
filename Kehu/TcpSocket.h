
#pragma once
#include "stdafx.h"
#define	BUF_SZIE	64
#include "winsock2.h"
#pragma comment(lib, "ws2_32.lib")
#include<string>
#include"allvar.h"
#pragma warning(disable: 4996)
using namespace std;

class TcpSocket{

public:

	WSADATA			wsd;			//WSADATA变量
	SOCKET			sHost;			//服务端套接字
	SOCKADDR_IN		servAddr;		//服务器地址
	char			buf[BUF_SZIE];	//接收数据缓冲区
	int				retVal;			//返回值
public:

	TcpSocket(){};
	~TcpSocket(){};

	int SocketStart() {
		//初始化套结字动态库
		if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0) //异步套接字启动命令
			//版本（次，主）   
			//返回socket实现细节信息
		{
			//system("WSAStartup failed!\n");
			//system("pause");
			return -1;
		}

		//创建套接字
		sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		//协议族对于TCP/IP协议族，该参数置AF_INET
		/*　第二个参数指定要创建的套接字类型，
		流套接字类型为SOCK_STREAM、
		数据报套接字类型为SOCK_DGRAM、
		原始套接字SOCK_RAW(WinSock接口并不适用某种特定的协议去封装它，
		而是由程序自行处理数据包以及协议首部）； */
		//第三个参数指定应用程序所使用的通信协议。填零系统会自动确认
		if (INVALID_SOCKET == sHost)
		{
			//printf("socket failed!\n");
			WSACleanup();//释放套接字资源
			return  -1;
		}

		//设置服务器地址
		servAddr.sin_family = AF_INET;
		//inet_addr("203.195.192.24");
		struct hostent * remoteHost;         /*域名*/
		remoteHost=gethostbyname(hostaddr);
		if(remoteHost==NULL) 
			return -1;
		//获取第一个ip地址
		servAddr.sin_addr.s_addr = *(u_long*)remoteHost->h_addr_list[0];
		servAddr.sin_port = htons((short)80);
		int	nServAddlen = sizeof(servAddr);

		//连接服务器
		retVal = connect(sHost, (LPSOCKADDR)&servAddr, sizeof(servAddr));

		if (SOCKET_ERROR == retVal)
		{
			//printf("connect failed!\n");
			closesocket(sHost);	//关闭套接字
			WSACleanup();		//释放套接字资源
			return -1;
		}
		return 0;
	}


	void sendinf(char* addr, char * host, const char  * msg, int port) {

		char *pHttpGet = "GET %s?%s HTTP/1.1\r\n"
			"Host: %s:%d\r\n\r\n";

		char strHttpGet[1024] = { 0 };
		//ZeroMemory(strHttpGet, BUF_SZIE);   //初始化内存
		sprintf(strHttpGet, pHttpGet, addr, msg, host, port);
		int var = send(sHost, strHttpGet, strlen(strHttpGet), 0);
		if (var < 0) {
			//说明socket中断，需要重启socket
			SocketStart();
			//MessageBoxA(NULL, "请求发送失败！", 0, 0);			
			return;
		}
	}

	void sendPost(char* addr, char * host,string username,string psw, int port){

		std::string header("");
		std::string content("");		//实名文件
		std::string nex_content("");	//等级文件
		std::string u_content("");      //用户名
		std::string p_content("");		//密码

		//----------------------post头开始--------------------------------  
		header += "POST ";
		header += addr;
		header += " HTTP/1.1\r\n";
		header += "Host: ";
		header += host;
		header += "\r\n";
		header += "Connection: Keep-Alive\r\n";
		header += "Accept: */*\r\n";
		header += "Pragma: no-cache\r\n";
		header += "Content-Type: multipart/form-data; boundary=71b23e4066ed\r\n";

		//用户名数据表单
		u_content += "--71b23e4066ed\r\n";
		u_content += "Content-Disposition: form-data; name=\"u\"\r\n\r\n";
		u_content += username+"\r\n";

		//密码数据表单
		p_content += "--71b23e4066ed\r\n";
		p_content += "Content-Disposition: form-data; name=\"p\"\r\n\r\n";
		p_content += psw+"\r\n";
				//post尾时间戳  
		std::string strContent("--71b23e4066ed--\r\n\r\n");
		char temp[64] = { 0 };
		//注意下面这个参数Content-Length，这个参数值是：http请求头长度+请求尾长度+文件总长度
		// 就分块传送 
		sprintf(temp, "Content-Length: %d\r\n\r\n",
			p_content.length()+u_content.length() + strContent.length());
		header += temp;
		std::string str_http_request;
		str_http_request.append(header);

		//----------------------post头结束-----------------------------------
		//发送post头  
		send(sHost, str_http_request.c_str(), str_http_request.length(), 0);
		Sleep(2);
		send(sHost, p_content.c_str(), p_content.length(), 0);
		Sleep(2);
		send(sHost, u_content.c_str(), u_content.length(), 0);
		Sleep(2);
		::send(sHost, strContent.c_str(), strContent.length(), 0);
		Sleep(2);
	}

	void sendPost1(char* addr, char * host, char *msg, int port) {
		char *pHttpPost = "POST %s HTTP/1.1\r\n"
			"Host: %s:%d\r\n"
			"Content-Type: application/x-www-form-urlencoded\r\n"
			"Content-Length: %d\r\n\r\n"
			"%s";

		//char* addr = "http://face.py91178.com/Login/getsalt";
		// char* host = "203.195.192.24";
		//	int post = 80;
		//	char* msg = "u=wangwen";

		char strHttpPost[1024] = { 0 };
		//ZeroMemory(strHttpGet, BUF_SZIE);   //初始化内存
		sprintf(strHttpPost, pHttpPost, addr, host, port, strlen(msg), msg);
		int var = send(sHost, strHttpPost, strlen(strHttpPost), 0);
		if (var < 0) {
			SocketStart();
			//MessageBox(NULL, L"请求发送失败！", 0, 0);
			return;
		}
	}

	char * ReadFile(char *pathpic, int &pic_len ){
		
		FILE *fp = fopen(pathpic, "rb");     //打开文件
		if (fp==NULL){
			fp = fopen(pathpic, "w+x");     //打开文件
			//MessageBoxA(NULL, "没有找到文件位置", 0, 0);
			return NULL;
		}
		if(fp!=NULL){
			fseek(fp, 0, SEEK_END);  //一直寻找到文件尾部
		}else return NULL;
		pic_len = ftell(fp);  //得到图片的长度
		rewind(fp);  //rewind将文件指针指向开头
		char *pic_buf = new char[pic_len + 1];  //开辟一个空间在堆上
		memset(pic_buf, 0, pic_len + 1);  //清空文件指针
		//读取文件内容
		if(fp!=NULL)
		  fread(pic_buf,sizeof(char),pic_len,fp);
		//测试将文件再保存于D:中
		/*
		MessageBoxA(NULL, "文件开始", 0, 0);
		FILE *fpw = fopen("C:\\AA.jpg","wb");
		fwrite(pic_buf,sizeof(char), pic_len, fpw);
		fclose(fpw); //关闭文件流
		MessageBoxA(NULL, "文件结束", 0, 0);
		*/
		if(fp!=NULL)
		fclose(fp);  
		return pic_buf;
	}

	void sendPic(char* addr, char * host, char *pathpic, char* picname, int port, string username, string psw) {
		
		//先读取文件流
		//实名图片读取,等级图片读取
		int Spic_len, Dpic_len;
		char *Spic_data=NULL, *Dpic_data=NULL;

		Spic_data=ReadFile(pathpic, Spic_len);       //实名图片
        Dpic_data = ReadFile(picname, Dpic_len);     //等级图片
		if (Dpic_len == 0 || Spic_len == 0)
			return;
		std::string header("");
		std::string content("");		//实名文件
		std::string nex_content("");	//等级文件
		std::string u_content("");      //用户名
		std::string p_content("");		//密码

		//----------------------post头开始--------------------------------  
		header += "POST ";
		header += addr;
		header += " HTTP/1.1\r\n";
		header += "Host: ";
		header += host;
		header += "\r\n";
		header += "Connection: Keep-Alive\r\n";
		header += "Accept: */*\r\n";
		header += "Pragma: no-cache\r\n";
		header += "Content-Type: multipart/form-data;boundary=71b23e4066ed\r\n";
		
		//用户名数据表单
		u_content += "--71b23e4066ed\r\n";
	    u_content += "Content-Disposition: form-data; name=\"u\"\r\n\r\n";
		u_content += username+"\r\n";

		//密码数据表单
		p_content += "--71b23e4066ed\r\n";
		p_content += "Content-Disposition: form-data; name=\"p\"\r\n\r\n";
		p_content += psw+"\r\n";

		//发送文件数据
		content += "--71b23e4066ed\r\n";
		content += "Content-Disposition: form-data; name=\"picurl\"; filename=\"";
		content += pathpic;
		content += "\"\r\n";
		content += "Content-Type: image/jpeg \r\n\r\n";

		//发送文件数据
		nex_content += "\r\n--71b23e4066ed\r\n";
		nex_content += "Content-Disposition: form-data; name=\"id_account\"; filename=\"";
		nex_content += picname;    //picname;
		nex_content += "\"\r\n";
		nex_content += "Content-Type: image/jpeg\r\n\r\n";

		//post尾时间戳  
		std::string strContent("\r\n--71b23e4066ed--\r\n");
		char temp[64] = { 0 };
		//注意下面这个参数Content-Length，这个参数值是：http请求头长度+请求尾长度+文件总长度
		// 就分块传送 
		sprintf(temp, "Content-Length: %d\r\n\r\n",
			content.length() + nex_content.length() +p_content.length()+u_content.length() + Spic_len + Dpic_len + strContent.length());
		header += temp;
		std::string str_http_request;
		str_http_request.append(header);

		//----------------------post头结束-----------------------------------
		//发送post头  
		int var=send(sHost, str_http_request.c_str(), str_http_request.length(), 0);
		  if (var < 0) {
			SocketStart();
			//MessageBox(NULL, L"请求发送失败！", 0, 0);
			return;
		}
		
		char fBuff[4096];
		memset(fBuff,0,sizeof(fBuff));
		int nPacketBufferSize = 4096; // 每个数据包存放文件的buffer大小  
		int nStart=0;//记录post初始位置  
		int nSize=0;//记录剩余文件大小  
		Sleep(static_cast<DWORD>(0.2));
		//发送用户名表单
		var=send(sHost, u_content.c_str(), u_content.length(), 0);
			  if (var < 0) {
			SocketStart();
			//MessageBox(NULL, L"请求发送失败！", 0, 0);
			return;
		}
		Sleep(static_cast<DWORD>(0.2));
		//发送密码表单
		var=send(sHost, p_content.c_str(), p_content.length(), 0);
			  if (var < 0) {
			SocketStart();
			//MessageBox(NULL, L"请求发送失败！", 0, 0);
			return;
		}
		Sleep(static_cast<DWORD>(0.2));
		//发送尾部
		//发送格式
		var=send(sHost, content.c_str(), content.length(), 0);
	    if (var < 0) {
			SocketStart();
			//MessageBox(NULL, L"请求发送失败！", 0, 0);
			return;
		}
		Sleep(static_cast<DWORD>(0.2));
		var=send(sHost, Spic_data, Spic_len, 0);
		if (var < 0) {
			SocketStart();
			//MessageBox(NULL, L"请求发送失败！", 0, 0);
			return;
		}
		Sleep(static_cast<DWORD>(0.2));
		//发送等级图片数据
		var=send(sHost, nex_content.c_str(), nex_content.length(), 0);
		if (var < 0) {
			SocketStart();
			//MessageBox(NULL, L"请求发送失败！", 0, 0);
			return;
		}
		Sleep(static_cast<DWORD>(0.2));
		var=send(sHost, Dpic_data, Dpic_len, 0);
	if (var < 0) {
			SocketStart();
			//MessageBox(NULL, L"请求发送失败！", 0, 0);
			return;
		}
		Sleep(static_cast<DWORD>(0.2));

		/*
		for (int i = 0; i < Spic_len; i += nPacketBufferSize)
		{
			nStart = i;
			if (i + nPacketBufferSize + 1> Spic_len){
				nSize = Spic_len - i;
			}
			else{
				nSize = nPacketBufferSize;
			}

			memcpy(fBuff, Spic_data + nStart, nSize);
			::send(sHost, fBuff, nSize, 0);
			Sleep(0.2);   //防止毡包
		}
		
		//发送等级图片数据
		::send(sHost, nex_content.c_str(), nex_content.length(), 0);
		Sleep(0.2);
		nPacketBufferSize = 4096;
		for (int i = 0; i < Dpic_len; i += nPacketBufferSize)
		{
			nStart = i;
			if (i + nPacketBufferSize + 1> Dpic_len){
				nSize = Dpic_len - i;
			}
			else{
				nSize = nPacketBufferSize;
			}

			memcpy(fBuff, Dpic_data + nStart, nSize);
			::send(sHost, fBuff, nSize, 0);
			Sleep(0.2);   //防止毡包
		}
		*/
		/*
		for (int i = 0; i < Dpic_len; i += nPacketBufferSize)
		{
			nStart = i;
			if (i + nPacketBufferSize + 1> Dpic_len){
				nSize = Dpic_len - i;
			}
			else{
				nSize = nPacketBufferSize;
			}

			memcpy(fBuff, Dpic_data + nStart, nSize);
			::send(sHost, fBuff, nSize, 0);
			Sleep(0.2);   //防止毡包
		}*/
		
		var=send(sHost, strContent.c_str(), strContent.length(), 0);
	   if (var < 0) {
			SocketStart();
			//MessageBox(NULL, L"请求发送失败！", 0, 0);
			return;
		}
		Sleep(static_cast<DWORD>(0.2));

		if (Spic_data == NULL){
			//MessageBox(NULL, L"文件数据为空", 0, 0);
		}
		//释放内存
		delete Spic_data;
		delete Dpic_data;
	}


	//单张图片上传
void sendPic(char* addr, char * host, char *pathpic,char *SessID, int port) {
		
		//先读取文件流
		//实名图片读取,等级图片读取
		int Spic_len=0;
		char *Spic_data=NULL;

		Spic_data  = ReadFile(pathpic,Spic_len);       //实名图片
		if (Spic_len == 0)  return;
		std::string header("");
		std::string content("");		//实名文件
		
		//----------------------post头开始--------------------------------  
		header += "POST ";
		header += addr;
		header += " HTTP/1.1\r\n";
		header += "Host: ";
		header += host;
		header += "\r\n";
		header += "Connection: Keep-Alive\r\n";
		header += "Accept: */*\r\n";
		header += "Pragma: no-cache\r\n";
		header += "Cookie: PHPSESSID=";
		header +=SessID;
		header +=";path=/";
		header += "\r\n";
		header += "Content-Type: multipart/form-data;boundary=71b23e4066ed\r\n";
		//发送文件数据
		content += "--71b23e4066ed\r\n";
		content += "Content-Disposition: form-data; name=\"picpath\"; filename=\"";
		content += pathpic;
		content += "\"\r\n";
		content += "Content-Type: image/jpeg \r\n\r\n";

		//post尾时间戳  
		std::string strContent("\r\n--71b23e4066ed--\r\n");
		char temp[64] = { 0 };
		//注意下面这个参数Content-Length，这个参数值是：http请求头长度+请求尾长度+文件总长度
		// 就分块传送 
		sprintf(temp, "Content-Length: %d\r\n\r\n",
			content.length()+Spic_len+strContent.length());
		header += temp;
		std::string str_http_request;
		str_http_request.append(header);

		//----------------------post头结束-----------------------------------
		//发送post头  
		send(sHost, str_http_request.c_str(), str_http_request.length(), 0);
		char fBuff[4096];
		memset(fBuff,0,sizeof(fBuff));
		int nPacketBufferSize = 4096; // 每个数据包存放文件的buffer大小  
		int nStart=0;//记录post初始位置  
		int nSize=0;//记录剩余文件大小  
		Sleep(static_cast<DWORD>(0.2));
		//发送格式
		send(sHost, content.c_str(), content.length(), 0);
		Sleep(static_cast<DWORD>(0.2));
		send(sHost, Spic_data, Spic_len, 0);
		Sleep(static_cast<DWORD>(0.2));

		send(sHost, strContent.c_str(), strContent.length(), 0);
		//Sleep(static_cast<DWORD>(0.2));
		
		if (Spic_data == NULL){
			//MessageBox(NULL, L"文件数据为空", 0, 0);
			return ;
		}
		//释放内存
		delete Spic_data;	
	}
};


