#pragma once
/*
203.195.192.24
face.py91178.com
*/
//include socket
#include"winsock.h"



#define	BUF_SZIE	64
/*
   �����趨ʱ��
   ��   10:00 
   ��   14:30
   ��   21:30
*/
#define Morining   36000    //��10
#define Afternoon  52200    //��2:30
#define Evening    77400    //��
 
//include "ximage"
/*
#include "CxImage/ximage.h"
#pragma comment(lib,"CxImage/cximage.lib")
#pragma comment(lib,"CxImage/jasper.lib")
#pragma comment(lib,"CxImage/jbig.lib")
#pragma comment(lib,"CxImage/Jpeg.lib")
#pragma comment(lib,"CxImage/libdcr.lib")
#pragma comment(lib,"CxImage/mng.lib")
#pragma comment(lib,"CxImage/png.lib")
#pragma comment(lib,"CxImage/Tiff.lib")
#pragma comment(lib,"CxImage/zlib.lib")
*/

#define M_min 420  //��sΪ��λ,������һ������60

#include<string>
#include<iostream>
using namespace std;
static const char root[] = {"tmp"};
static const char tpwd[] = {"py356747181"};
static const int port = 3306 ;
static const char hostaddr[] = {"friend.py91178.com"};
static const char biao[] = { "penyou" };
static const char logaddr[] =   "http://friend.py91178.com/Login/getsalt";
static const char loginaddr[] = "http://friend.py91178.com/Login/client";
static const char loginMenu[] = "http://friend.py91178.com/Login/nav";
static const char addr_num[] =  "http://friend.py91178.com/AuthCode/send.html";

static const char addr_pic[] =  "http://127.0.0.1/Login/client_upload";


struct usr {
	string username;   //�û���
	string password;   //����
};


struct Buyer {

	usr  myusr;
	string truename;   //��ϵ��
	string mobile;      //��ϵ�ֻ�
	string QQ;          //��ϵQQ
	int type;             //�̼�����
	string recommend_code; //�Ƽ��˱���
	int pid;    //�Ƽ�ע���˵�ID
	short int recommended; //�Ƿ�Ϊ�Ƽ�ע��
	short int level;       //�̼Ҽ���
	short int status;      //״̬
	string salt;         //�����
	int addtime ;      //���ʱ��
};

struct py_user_shop {
	string account;  //�����˺�
	string sex; //�Ա�
	string born; //��������
	string mobile;      //��ϵ�ֻ�
	short int type; //�˺�����
	string picurl ;//��ͼ·��
	string id_account; //�ȼ���ͼ·��
	string manname; //�ջ���
	string province;   //ʡ
	string city;       //��
	string area;       //��
	string addtime ;   //���ʱ��
	string address;    //��ϸ��ַ
	string level;      //�ȼ�
	string status;     //״̬
};



static struct usr ower ;  //�û���¼ȫ�ֱ���
static CImage  Resour;  //ͼƬ��Դ
static struct usr cm_ower;
