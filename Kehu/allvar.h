#pragma once
/*
203.195.192.24
face.py91178.com
*/
//include socket
#include"winsock.h"



#define	BUF_SZIE	64
/*
   气泡设定时间
   早   10:00 
   中   14:30
   晚   21:30
*/
#define Morining   36000    //早10
#define Afternoon  52200    //中2:30
#define Evening    77400    //晚
 
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

#define M_min 420  //以s为单位,如设置一分钟这60

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
	string username;   //用户名
	string password;   //密码
};


struct Buyer {

	usr  myusr;
	string truename;   //联系人
	string mobile;      //联系手机
	string QQ;          //联系QQ
	int type;             //商家类型
	string recommend_code; //推荐人编码
	int pid;    //推荐注册人的ID
	short int recommended; //是否为推荐注册
	short int level;       //商家级别
	short int status;      //状态
	string salt;         //随机码
	int addtime ;      //添加时间
};

struct py_user_shop {
	string account;  //购物账号
	string sex; //性别
	string born; //出生年月
	string mobile;      //联系手机
	short int type; //账号类型
	string picurl ;//切图路径
	string id_account; //等级切图路径
	string manname; //收货人
	string province;   //省
	string city;       //市
	string area;       //县
	string addtime ;   //添加时间
	string address;    //详细地址
	string level;      //等级
	string status;     //状态
};



static struct usr ower ;  //用户登录全局变量
static CImage  Resour;  //图片资源
static struct usr cm_ower;
