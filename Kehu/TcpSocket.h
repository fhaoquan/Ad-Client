
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

	WSADATA			wsd;			//WSADATA����
	SOCKET			sHost;			//������׽���
	SOCKADDR_IN		servAddr;		//��������ַ
	char			buf[BUF_SZIE];	//�������ݻ�����
	int				retVal;			//����ֵ
public:

	TcpSocket(){};
	~TcpSocket(){};

	int SocketStart() {
		//��ʼ���׽��ֶ�̬��
		if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0) //�첽�׽�����������
			//�汾���Σ�����   
			//����socketʵ��ϸ����Ϣ
		{
			//system("WSAStartup failed!\n");
			//system("pause");
			return -1;
		}

		//�����׽���
		sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		//Э�������TCP/IPЭ���壬�ò�����AF_INET
		/*���ڶ�������ָ��Ҫ�������׽������ͣ�
		���׽�������ΪSOCK_STREAM��
		���ݱ��׽�������ΪSOCK_DGRAM��
		ԭʼ�׽���SOCK_RAW(WinSock�ӿڲ�������ĳ���ض���Э��ȥ��װ����
		�����ɳ������д������ݰ��Լ�Э���ײ����� */
		//����������ָ��Ӧ�ó�����ʹ�õ�ͨ��Э�顣����ϵͳ���Զ�ȷ��
		if (INVALID_SOCKET == sHost)
		{
			//printf("socket failed!\n");
			WSACleanup();//�ͷ��׽�����Դ
			return  -1;
		}

		//���÷�������ַ
		servAddr.sin_family = AF_INET;
		//inet_addr("203.195.192.24");
		struct hostent * remoteHost;         /*����*/
		remoteHost=gethostbyname(hostaddr);
		if(remoteHost==NULL) 
			return -1;
		//��ȡ��һ��ip��ַ
		servAddr.sin_addr.s_addr = *(u_long*)remoteHost->h_addr_list[0];
		servAddr.sin_port = htons((short)80);
		int	nServAddlen = sizeof(servAddr);

		//���ӷ�����
		retVal = connect(sHost, (LPSOCKADDR)&servAddr, sizeof(servAddr));

		if (SOCKET_ERROR == retVal)
		{
			//printf("connect failed!\n");
			closesocket(sHost);	//�ر��׽���
			WSACleanup();		//�ͷ��׽�����Դ
			return -1;
		}
		return 0;
	}


	void sendinf(char* addr, char * host, const char  * msg, int port) {

		char *pHttpGet = "GET %s?%s HTTP/1.1\r\n"
			"Host: %s:%d\r\n\r\n";

		char strHttpGet[1024] = { 0 };
		//ZeroMemory(strHttpGet, BUF_SZIE);   //��ʼ���ڴ�
		sprintf(strHttpGet, pHttpGet, addr, msg, host, port);
		int var = send(sHost, strHttpGet, strlen(strHttpGet), 0);
		if (var < 0) {
			//˵��socket�жϣ���Ҫ����socket
			SocketStart();
			//MessageBoxA(NULL, "������ʧ�ܣ�", 0, 0);			
			return;
		}
	}

	void sendPost(char* addr, char * host,string username,string psw, int port){

		std::string header("");
		std::string content("");		//ʵ���ļ�
		std::string nex_content("");	//�ȼ��ļ�
		std::string u_content("");      //�û���
		std::string p_content("");		//����

		//----------------------postͷ��ʼ--------------------------------  
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

		//�û������ݱ�
		u_content += "--71b23e4066ed\r\n";
		u_content += "Content-Disposition: form-data; name=\"u\"\r\n\r\n";
		u_content += username+"\r\n";

		//�������ݱ�
		p_content += "--71b23e4066ed\r\n";
		p_content += "Content-Disposition: form-data; name=\"p\"\r\n\r\n";
		p_content += psw+"\r\n";
				//postβʱ���  
		std::string strContent("--71b23e4066ed--\r\n\r\n");
		char temp[64] = { 0 };
		//ע�������������Content-Length���������ֵ�ǣ�http����ͷ����+����β����+�ļ��ܳ���
		// �ͷֿ鴫�� 
		sprintf(temp, "Content-Length: %d\r\n\r\n",
			p_content.length()+u_content.length() + strContent.length());
		header += temp;
		std::string str_http_request;
		str_http_request.append(header);

		//----------------------postͷ����-----------------------------------
		//����postͷ  
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
		//ZeroMemory(strHttpGet, BUF_SZIE);   //��ʼ���ڴ�
		sprintf(strHttpPost, pHttpPost, addr, host, port, strlen(msg), msg);
		int var = send(sHost, strHttpPost, strlen(strHttpPost), 0);
		if (var < 0) {
			SocketStart();
			//MessageBox(NULL, L"������ʧ�ܣ�", 0, 0);
			return;
		}
	}

	char * ReadFile(char *pathpic, int &pic_len ){
		
		FILE *fp = fopen(pathpic, "rb");     //���ļ�
		if (fp==NULL){
			fp = fopen(pathpic, "w+x");     //���ļ�
			//MessageBoxA(NULL, "û���ҵ��ļ�λ��", 0, 0);
			return NULL;
		}
		if(fp!=NULL){
			fseek(fp, 0, SEEK_END);  //һֱѰ�ҵ��ļ�β��
		}else return NULL;
		pic_len = ftell(fp);  //�õ�ͼƬ�ĳ���
		rewind(fp);  //rewind���ļ�ָ��ָ��ͷ
		char *pic_buf = new char[pic_len + 1];  //����һ���ռ��ڶ���
		memset(pic_buf, 0, pic_len + 1);  //����ļ�ָ��
		//��ȡ�ļ�����
		if(fp!=NULL)
		  fread(pic_buf,sizeof(char),pic_len,fp);
		//���Խ��ļ��ٱ�����D:��
		/*
		MessageBoxA(NULL, "�ļ���ʼ", 0, 0);
		FILE *fpw = fopen("C:\\AA.jpg","wb");
		fwrite(pic_buf,sizeof(char), pic_len, fpw);
		fclose(fpw); //�ر��ļ���
		MessageBoxA(NULL, "�ļ�����", 0, 0);
		*/
		if(fp!=NULL)
		fclose(fp);  
		return pic_buf;
	}

	void sendPic(char* addr, char * host, char *pathpic, char* picname, int port, string username, string psw) {
		
		//�ȶ�ȡ�ļ���
		//ʵ��ͼƬ��ȡ,�ȼ�ͼƬ��ȡ
		int Spic_len, Dpic_len;
		char *Spic_data=NULL, *Dpic_data=NULL;

		Spic_data=ReadFile(pathpic, Spic_len);       //ʵ��ͼƬ
        Dpic_data = ReadFile(picname, Dpic_len);     //�ȼ�ͼƬ
		if (Dpic_len == 0 || Spic_len == 0)
			return;
		std::string header("");
		std::string content("");		//ʵ���ļ�
		std::string nex_content("");	//�ȼ��ļ�
		std::string u_content("");      //�û���
		std::string p_content("");		//����

		//----------------------postͷ��ʼ--------------------------------  
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
		
		//�û������ݱ�
		u_content += "--71b23e4066ed\r\n";
	    u_content += "Content-Disposition: form-data; name=\"u\"\r\n\r\n";
		u_content += username+"\r\n";

		//�������ݱ�
		p_content += "--71b23e4066ed\r\n";
		p_content += "Content-Disposition: form-data; name=\"p\"\r\n\r\n";
		p_content += psw+"\r\n";

		//�����ļ�����
		content += "--71b23e4066ed\r\n";
		content += "Content-Disposition: form-data; name=\"picurl\"; filename=\"";
		content += pathpic;
		content += "\"\r\n";
		content += "Content-Type: image/jpeg \r\n\r\n";

		//�����ļ�����
		nex_content += "\r\n--71b23e4066ed\r\n";
		nex_content += "Content-Disposition: form-data; name=\"id_account\"; filename=\"";
		nex_content += picname;    //picname;
		nex_content += "\"\r\n";
		nex_content += "Content-Type: image/jpeg\r\n\r\n";

		//postβʱ���  
		std::string strContent("\r\n--71b23e4066ed--\r\n");
		char temp[64] = { 0 };
		//ע�������������Content-Length���������ֵ�ǣ�http����ͷ����+����β����+�ļ��ܳ���
		// �ͷֿ鴫�� 
		sprintf(temp, "Content-Length: %d\r\n\r\n",
			content.length() + nex_content.length() +p_content.length()+u_content.length() + Spic_len + Dpic_len + strContent.length());
		header += temp;
		std::string str_http_request;
		str_http_request.append(header);

		//----------------------postͷ����-----------------------------------
		//����postͷ  
		int var=send(sHost, str_http_request.c_str(), str_http_request.length(), 0);
		  if (var < 0) {
			SocketStart();
			//MessageBox(NULL, L"������ʧ�ܣ�", 0, 0);
			return;
		}
		
		char fBuff[4096];
		memset(fBuff,0,sizeof(fBuff));
		int nPacketBufferSize = 4096; // ÿ�����ݰ�����ļ���buffer��С  
		int nStart=0;//��¼post��ʼλ��  
		int nSize=0;//��¼ʣ���ļ���С  
		Sleep(static_cast<DWORD>(0.2));
		//�����û�����
		var=send(sHost, u_content.c_str(), u_content.length(), 0);
			  if (var < 0) {
			SocketStart();
			//MessageBox(NULL, L"������ʧ�ܣ�", 0, 0);
			return;
		}
		Sleep(static_cast<DWORD>(0.2));
		//���������
		var=send(sHost, p_content.c_str(), p_content.length(), 0);
			  if (var < 0) {
			SocketStart();
			//MessageBox(NULL, L"������ʧ�ܣ�", 0, 0);
			return;
		}
		Sleep(static_cast<DWORD>(0.2));
		//����β��
		//���͸�ʽ
		var=send(sHost, content.c_str(), content.length(), 0);
	    if (var < 0) {
			SocketStart();
			//MessageBox(NULL, L"������ʧ�ܣ�", 0, 0);
			return;
		}
		Sleep(static_cast<DWORD>(0.2));
		var=send(sHost, Spic_data, Spic_len, 0);
		if (var < 0) {
			SocketStart();
			//MessageBox(NULL, L"������ʧ�ܣ�", 0, 0);
			return;
		}
		Sleep(static_cast<DWORD>(0.2));
		//���͵ȼ�ͼƬ����
		var=send(sHost, nex_content.c_str(), nex_content.length(), 0);
		if (var < 0) {
			SocketStart();
			//MessageBox(NULL, L"������ʧ�ܣ�", 0, 0);
			return;
		}
		Sleep(static_cast<DWORD>(0.2));
		var=send(sHost, Dpic_data, Dpic_len, 0);
	if (var < 0) {
			SocketStart();
			//MessageBox(NULL, L"������ʧ�ܣ�", 0, 0);
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
			Sleep(0.2);   //��ֹձ��
		}
		
		//���͵ȼ�ͼƬ����
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
			Sleep(0.2);   //��ֹձ��
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
			Sleep(0.2);   //��ֹձ��
		}*/
		
		var=send(sHost, strContent.c_str(), strContent.length(), 0);
	   if (var < 0) {
			SocketStart();
			//MessageBox(NULL, L"������ʧ�ܣ�", 0, 0);
			return;
		}
		Sleep(static_cast<DWORD>(0.2));

		if (Spic_data == NULL){
			//MessageBox(NULL, L"�ļ�����Ϊ��", 0, 0);
		}
		//�ͷ��ڴ�
		delete Spic_data;
		delete Dpic_data;
	}


	//����ͼƬ�ϴ�
void sendPic(char* addr, char * host, char *pathpic,char *SessID, int port) {
		
		//�ȶ�ȡ�ļ���
		//ʵ��ͼƬ��ȡ,�ȼ�ͼƬ��ȡ
		int Spic_len=0;
		char *Spic_data=NULL;

		Spic_data  = ReadFile(pathpic,Spic_len);       //ʵ��ͼƬ
		if (Spic_len == 0)  return;
		std::string header("");
		std::string content("");		//ʵ���ļ�
		
		//----------------------postͷ��ʼ--------------------------------  
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
		//�����ļ�����
		content += "--71b23e4066ed\r\n";
		content += "Content-Disposition: form-data; name=\"picpath\"; filename=\"";
		content += pathpic;
		content += "\"\r\n";
		content += "Content-Type: image/jpeg \r\n\r\n";

		//postβʱ���  
		std::string strContent("\r\n--71b23e4066ed--\r\n");
		char temp[64] = { 0 };
		//ע�������������Content-Length���������ֵ�ǣ�http����ͷ����+����β����+�ļ��ܳ���
		// �ͷֿ鴫�� 
		sprintf(temp, "Content-Length: %d\r\n\r\n",
			content.length()+Spic_len+strContent.length());
		header += temp;
		std::string str_http_request;
		str_http_request.append(header);

		//----------------------postͷ����-----------------------------------
		//����postͷ  
		send(sHost, str_http_request.c_str(), str_http_request.length(), 0);
		char fBuff[4096];
		memset(fBuff,0,sizeof(fBuff));
		int nPacketBufferSize = 4096; // ÿ�����ݰ�����ļ���buffer��С  
		int nStart=0;//��¼post��ʼλ��  
		int nSize=0;//��¼ʣ���ļ���С  
		Sleep(static_cast<DWORD>(0.2));
		//���͸�ʽ
		send(sHost, content.c_str(), content.length(), 0);
		Sleep(static_cast<DWORD>(0.2));
		send(sHost, Spic_data, Spic_len, 0);
		Sleep(static_cast<DWORD>(0.2));

		send(sHost, strContent.c_str(), strContent.length(), 0);
		//Sleep(static_cast<DWORD>(0.2));
		
		if (Spic_data == NULL){
			//MessageBox(NULL, L"�ļ�����Ϊ��", 0, 0);
			return ;
		}
		//�ͷ��ڴ�
		delete Spic_data;	
	}
};


