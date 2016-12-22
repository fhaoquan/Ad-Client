// GoodInf.cpp : implementation file
//

#include "stdafx.h"
#include "Kehu.h"
#include "GoodInf.h"
#include"jietu.h"
#include "afxdialogex.h"
#include <string>
#include <time.h>
#include"json\json.h"
#include "Winsock2.h"
#include"cmd5.h"
#include"common.h"
// GoodInf dialog
//extern struct usr cm_ower;

IMPLEMENT_DYNAMIC(GoodInf, CDialogEx)

GoodInf::GoodInf(CWnd* pParent /*=NULL*/)
	: CDialogEx(GoodInf::IDD, pParent)
, Man(0)
, women(0)
{
	time_cnt = 0;
	     cnt = 60;
		 JudXY = TRUE;
}

GoodInf::~GoodInf()
{
	mysql_close(&m_sqlCon);
}

void GoodInf::DoDataExchange(CDataExchange* pDX)
{

	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, ZhangHaoType);
	DDX_Control(pDX, IDC_COMBO2, ZhangHaoLevel);
	DDX_Control(pDX, IDC_EDIT1, ZhanghaoNum);
	DDX_Control(pDX, IDC_EDIT2, Birth);
	DDX_Control(pDX, IDC_EDIT3, ShouHuoRen);
	DDX_Control(pDX, IDC_EDIT4, QiehaoShangc);
	DDX_Control(pDX, IDC_EDIT5, Xiangxdiz);
	DDX_Control(pDX, IDC_COMBO4, Provice);
	DDX_Control(pDX, IDC_COMBO3, shiqu);
	DDX_Control(pDX, IDC_COMBO5, xianqu);
	DDX_Control(pDX, IDC_EDIT6, Iphone);
	DDX_Control(pDX, IDC_EDIT8, DTime);
	DDX_Control(pDX, IDC_EDIT7, SjiMa);
	DDX_Control(pDX, IDC_BUTTON2, Submit_All);
	DDX_Control(pDX, IDC_SHR, m_zhlx);
	DDX_Control(pDX, IDC_ZHDJ, m_zhdj);
	DDX_Control(pDX, IDC_SHDZ, m_shdz);
	DDX_Control(pDX, IDC_XXSHDZ, m_xxshdz);
	DDX_Control(pDX, IDC_SMQHSC, m_zhqtsc);
	DDX_Control(pDX, IDC_zhqhscdz, m_zhqhscdz);
	DDX_Control(pDX, IDC_DHYZ, m_dhyz);
	DDX_Control(pDX, IDC_DXKL, m_dxkl);
	DDX_Control(pDX, IDC_BUTTON1, m_sc);
	DDX_Control(pDX, IDC_BUTTON3, m_hqkl);
}

BEGIN_MESSAGE_MAP(GoodInf, CDialogEx)
ON_EN_CHANGE(IDC_EDIT1, &GoodInf::OnEnChangeEdit1)
ON_CBN_SELCHANGE(IDC_COMBO1, &GoodInf::OnCbnSelchangeCombo1)
ON_EN_CHANGE(IDC_EDIT3, &GoodInf::OnEnChangeEdit3)
ON_EN_CHANGE(IDC_EDIT4, &GoodInf::OnEnChangeEdit4)
ON_CBN_SELCHANGE(IDC_COMBO4, &GoodInf::OnCbnSelchangeCombo4)
ON_CBN_SELCHANGE(IDC_COMBO3, &GoodInf::OnCbnSelchangeCombo3)
ON_CBN_SELCHANGE(IDC_COMBO5, &GoodInf::OnCbnSelchangeCombo5)
ON_EN_CHANGE(IDC_EDIT5, &GoodInf::OnEnChangeEdit5)
ON_BN_CLICKED(IDC_BUTTON2, &GoodInf::OnBnClickedButton2)
ON_BN_CLICKED(IDC_BUTTON1, &GoodInf::OnBnClickedButton1)
ON_CBN_SELCHANGE(IDC_COMBO2, &GoodInf::OnCbnSelchangeCombo2)
ON_EN_CHANGE(IDC_EDIT2, &GoodInf::OnEnChangeEdit2)
ON_BN_CLICKED(IDC_RADIO1, &GoodInf::OnBnClickedRadio1)
ON_BN_CLICKED(IDC_RADIO2, &GoodInf::OnBnClickedRadio2)
ON_BN_CLICKED(IDC_BUTTON3, &GoodInf::OnBnClickedButton3)
ON_EN_CHANGE(IDC_EDIT8, &GoodInf::OnEnChangeEdit8)
ON_WM_TIMER()
END_MESSAGE_MAP()


// GoodInf message handlers
BOOL GoodInf::OnInitDialog(){
   CDialog::OnInitDialog();
   ModifyStyle(0, WS_SIZEBOX);  //设置对话框大小可变
   GetClientRect(m_rect);  //得到初始对话框的大小
   //对账号类型进行初始化
   ZhangHaoType.InsertString(0, L"淘宝/天猫/1688");
   ZhangHaoType.InsertString(1,L"京东");
   ZhangHaoType.InsertString(2,L"一号店");
   ZhangHaoType.InsertString(3,L"唯品会");
   ZhangHaoType.InsertString(4,L"聚美优品");
   ZhangHaoType.InsertString(5,L"美丽说");
   ZhangHaoType.InsertString(6,L"唯品会");
   ZhangHaoType.InsertString(7,L"蘑菇街");
   ZhangHaoType.SetCurSel(0);
   //对账号等级进行初始化
   ZhangHaoLevel.AddString(CString("1心"));
   ZhangHaoLevel.AddString(CString("2心"));
   ZhangHaoLevel.AddString(CString("3心"));
   ZhangHaoLevel.AddString(CString("4心"));
   ZhangHaoLevel.AddString(CString("5心"));
   ZhangHaoLevel.AddString(CString("1钻"));
   ZhangHaoLevel.AddString(CString("2钻"));
   ZhangHaoLevel.AddString(CString("3钻"));
   ZhangHaoLevel.AddString(CString("4钻"));
   ZhangHaoLevel.AddString(CString("5钻"));
   ZhangHaoLevel.SetCurSel(0); //设置默认显示的内容
   //对性别进行初始化
   ((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(1);//设置默认选择的性别
     SexType = "男";
	 //对省，市，县，区三级进行初始化
	 Provice.AddString(L"省");
	 Provice.SetCurSel(0);
	 shiqu.AddString(L"市");
	 shiqu.SetCurSel(0);
	 xianqu.AddString(L"县");
	 xianqu.SetCurSel(0);
	 //连接数据库
	  mysql_init(&m_sqlCon);
	 // localhost:服务器 root为账号密码 test为数据库名 3306为端口  
	 if (!mysql_real_connect(&m_sqlCon, hostaddr, root, tpwd, biao, port, NULL, 0)) {
		 MessageBox(_T("数据库连接失败!"));
		 return FALSE;
	 }
	 mysql_set_character_set(&m_sqlCon, "gbk");
	 char *sql = "select province from province";
	 MYSQL_RES *res; //结果集
	 MYSQL_ROW row;
	 int var = mysql_real_query(&m_sqlCon, sql, (unsigned int)strlen(sql));
	 if (var != 0) {
		 MessageBox(L"地图数据库更新失败！");
		 return -1;
	 }
	 Provice.ResetContent();
	 res = mysql_store_result(&m_sqlCon);
	 wchar_t buf[128];
	 while (row = mysql_fetch_row(res)) {
		 for (int t = 0; t < mysql_num_fields(res); t++) {
			 //char转化为string
			 int charLen = strlen(row[t]);
			 //计算多字节字符的大小，按字符计算。
			 int len = MultiByteToWideChar(CP_ACP, 0, row[t], charLen, NULL, 0);
			 //为宽字节字符数组申请空间，数组大小为按字节计算的多字节字符大小
			 MultiByteToWideChar(CP_ACP, 0, row[t], charLen, buf, len);
			 buf[len] = '\0'; //添加字符串结尾，注意不是len+1
							  //string转为CStringT
			 Provice.AddString(buf);
		 }
	 }
	 //OnCbnSelchangeCombo4();
	// mysql_close(&m_sqlCon);
   return TRUE;
}
void GoodInf::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	//账号
	CString username;
	ZhanghaoNum.GetWindowTextW(username);
	CStringA tmusr(username.GetBuffer(0));
	buy.account = tmusr.GetBuffer(0);
	// TODO:  Add your control notification handler code here
}


void GoodInf::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here

	int var = ZhangHaoType.GetCurSel();
	 buy.type = var + 1;
	 ZhangHaoLevel.ResetContent();
	 if (var == 0) JudXY = TRUE;
	 else 
	 if (JudXY)
		 JudXY = FALSE;
	 //说明是先的淘宝，天猫，1688
	 UpdateWindow();
	 m_zhlx.ShowWindow(JudXY);
	 ShouHuoRen.ShowWindow(JudXY);
	 m_shdz.ShowWindow(JudXY);
	 Provice.ShowWindow(JudXY);
	 shiqu.ShowWindow(JudXY);
	 xianqu.ShowWindow(JudXY);
	 m_xxshdz.ShowWindow(JudXY);
	 Xiangxdiz.ShowWindow(JudXY);
	 m_zhqtsc.ShowWindow(JudXY);
	 m_sc.ShowWindow(JudXY);
	 m_zhqhscdz.ShowWindow(JudXY);
	 QiehaoShangc.ShowWindow(JudXY);
	 m_dhyz.ShowWindow(JudXY);
	 Iphone.ShowWindow(JudXY);
	 m_hqkl.ShowWindow(JudXY);
	 m_dxkl.ShowWindow(JudXY);
	 SjiMa.ShowWindow(JudXY);
	 DTime.ShowWindow(JudXY);
	 if (var != 0){
		 //调整窗口大小
		 this->SetWindowPos(NULL, 460, 110, m_rect.right - m_rect.left, 400, 0);
		  Submit_All.SetWindowPos(NULL, 155, 240, 80, 30, 0);
	 }
	 else {
		 this->SetWindowPos(NULL, 460, 110, m_rect.right - m_rect.left, m_rect.bottom - m_rect.top, 0);
		 Submit_All.SetWindowPos(NULL, 155, m_rect.bottom - 70, 80, 30, 0);
	 }

	switch (var)
	{
	case 0: {
		
			ZhangHaoLevel.AddString(CString("1心"));
			ZhangHaoLevel.AddString(CString("2心"));
			ZhangHaoLevel.AddString(CString("3心"));
			ZhangHaoLevel.AddString(CString("4心"));
			ZhangHaoLevel.AddString(CString("5心"));
			ZhangHaoLevel.AddString(CString("1钻"));
			ZhangHaoLevel.AddString(CString("2钻"));
			ZhangHaoLevel.AddString(CString("3钻"));
			ZhangHaoLevel.AddString(CString("4钻"));
			ZhangHaoLevel.AddString(CString("5钻"));
		
	}   break;
	case 1: {
		ZhangHaoLevel.AddString(L"铜牌会员");
		ZhangHaoLevel.AddString(L"银牌会员");
		ZhangHaoLevel.AddString(L"金牌会员");
		ZhangHaoLevel.AddString(L"钻石会员");
	} break;
	case 2: {
		ZhangHaoLevel.AddString(L"V1");
		ZhangHaoLevel.AddString(L"V2");
		ZhangHaoLevel.AddString(L"V3");
	}break;
	case 3: {
		ZhangHaoLevel.AddString(L"铁牌会员");
		ZhangHaoLevel.AddString(L"铜牌会员");
		ZhangHaoLevel.AddString(L"银牌会员");
		ZhangHaoLevel.AddString(L"金牌会员");
		ZhangHaoLevel.AddString(L"钻石会员");
		ZhangHaoLevel.AddString(L"皇冠会员");
	} break;
	case 4: {
		ZhangHaoLevel.AddString(L"普通会员");
		ZhangHaoLevel.AddString(L"黄金会员");
		ZhangHaoLevel.AddString(L"白金会员");
	}
	case 5:
	case 6:
	{
		ZhangHaoLevel.AddString(L"注册会员");
	}break;
	default: 
		break;
	}
	ZhangHaoLevel.SetCurSel(0);
}


void GoodInf::OnEnChangeEdit3()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	CString username;
	ShouHuoRen.GetWindowTextW(username);
	CStringA tmusr(username.GetBuffer(0));
	buy.manname = tmusr.GetBuffer(0);
	// TODO:  Add your control notification handler code here
}


void GoodInf::OnEnChangeEdit4()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	// TODO:  Add your control notification handler code here
}


void GoodInf::OnCbnSelchangeCombo4()
{
	// TODO: Add your control notification handler code here
	CString  tcity;
	int index = Provice.GetCurSel();
	Provice.GetLBText(index, tcity);
	CStringA  aticy(tcity.GetBuffer(0));
	std::string city = aticy.GetBuffer(0);
	std::string bsql = "select provinceID from province where province=+""'"+city+"'";
	MYSQL_RES *ares; //结果集
	MYSQL_ROW arow;
	int var = mysql_real_query(&m_sqlCon, bsql.c_str(), (unsigned int)(bsql.size()));
	if (var != 0) {
		MessageBox(L"没有找到该省区！");
		return;
	}
	ares = mysql_store_result(&m_sqlCon);
	arow = mysql_fetch_row(ares);

	std::string sql = "select city from city where father =" + std::string(arow[0]);
	//char sql[] = ssql.c_str();
	MYSQL_RES *res; //结果集
	MYSQL_ROW row;
	int avar = mysql_real_query(&m_sqlCon, sql.c_str(), (unsigned int)(sql.size()));
	if (avar != 0) {
		MessageBox(L"地图数据库更新失败！");
		return;
	}
	shiqu.ResetContent();
	res = mysql_store_result(&m_sqlCon);
	wchar_t buf[128];
	while (row = mysql_fetch_row(res)) {

		for (int t = 0; t < mysql_num_fields(res); t++) {
			//char转化为string
			int charLen = strlen(row[t]);
			//计算多字节字符的大小，按字符计算。
			int len = MultiByteToWideChar(CP_ACP, 0, row[t], charLen, NULL, 0);
			//为宽字节字符数组申请空间，数组大小为按字节计算的多字节字符大小
			MultiByteToWideChar(CP_ACP, 0, row[t], charLen, buf, len);
			buf[len] = '\0'; //添加字符串结尾，注意不是len+1
							 //string转为CStringT
			shiqu.AddString(buf);
		}
	}
	// mysql_close (&mysql);
}


void GoodInf::OnCbnSelchangeCombo3()
{
	// TODO: Add your control notification handler code here
	CString  txianqu;
	int index = shiqu.GetCurSel();
    shiqu.GetLBText(index , txianqu);
	CStringA  axianqu(txianqu.GetBuffer(0));
	std::string xqu = axianqu.GetBuffer(0);
	MYSQL_RES *ares; //结果集
	MYSQL_ROW arow;
	std::string bsql = "select cityID from city where city ='" +xqu+"'";
	int var = mysql_real_query(&m_sqlCon, bsql.c_str(), (unsigned int)(bsql.size()));
	if (var != 0) {
		MessageBox(L"地图数据库更新失败！");
		return;
	}
	ares = mysql_store_result(&m_sqlCon);
	arow = mysql_fetch_row(ares);

	std::string sql = "select area from area where father ="+ std::string(arow[0]);
	//char sql[] = ssql.c_str();
	MYSQL_RES *res; //结果集
	MYSQL_ROW row;
	int avar = mysql_real_query(&m_sqlCon, sql.c_str(), (unsigned int)(sql.size()));
	if (avar != 0) {
		MessageBox(L"地图数据库更新失败！");
		return ;
	}
	xianqu.ResetContent();
	res = mysql_store_result(&m_sqlCon);
	wchar_t buf[128];
	while (row = mysql_fetch_row(res)) {

		for (int t = 0; t < mysql_num_fields(res); t++) {
			//char转化为string
			int charLen = strlen(row[t]);
			//计算多字节字符的大小，按字符计算。
			int len = MultiByteToWideChar(CP_ACP, 0, row[t], charLen, NULL, 0);
			//为宽字节字符数组申请空间，数组大小为按字节计算的多字节字符大小
			MultiByteToWideChar(CP_ACP, 0, row[t], charLen, buf, len);
			buf[len] = '\0'; //添加字符串结尾，注意不是len+1
							 //string转为CStringT
			xianqu.AddString(buf);
		}
	}
}


void GoodInf::OnCbnSelchangeCombo5()
{
	// TODO: Add your control notification handler code here
}


void GoodInf::OnEnChangeEdit5()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	CString username;
	Xiangxdiz.GetWindowTextW(username);
	CStringA tmusr(username.GetBuffer(0));
	buy.address = tmusr.GetBuffer(0);
	// TODO:  Add your control notification handler code here
}


void GoodInf::OnBnClickedButton2()
{


	// TODO: Add your control notification handler code here
	//添加下拉菜单的相关功能！！！
	//将省市区注入到结构体中	Provice.
	CString  tp;
	string sql;
	int index = Provice.GetCurSel();
	if (index < 0)tp = L"0";
	else Provice.GetLBText(index, tp);

	CStringA  ap(tp.GetBuffer(0));
	buy.province = ap.GetBuffer(0);
	//市
	CString  tc;
	index = shiqu.GetCurSel();
	if (index < 0)tp = L"0";
	else shiqu.GetLBText(index, tc);
	CStringA  ac(tc.GetBuffer(0));
	buy.city = ac.GetBuffer(0);
	//县区
	CString  ta;
	index = xianqu.GetCurSel();
	if (index < 0)ta = L"0";
	else xianqu.GetLBText(index, ta);

	CStringA  aa(ta.GetBuffer(0));
	buy.area = aa.GetBuffer(0);
	//获取性别   	
	buy.sex = (Man == 1) ? "0" : "1";
	if (buy.type == 1){
    //验证手机号码
	CString Iph_num;
	SjiMa.GetWindowTextW(Iph_num);
	CString Iph_Yz;
	Iph_Yz.Format(L"%d", tmpvar);
	if (Iph_num.Compare(Iph_Yz) == 0)	{
		//相等
		CStringA Iph_tmp(Iph_num.GetBuffer(0));
	 	 buy.mobile = Iph_tmp.GetBuffer(0);
	}
	}
else
	buy.mobile = "0";

	//提交到数据库中
	char type[4], status[4];
	itoa(buy.type, type, 10);

	time_t t = time(0); //另外再说一下好像不能用time(NULL),注意！！！
	char datetmp[64];
	strftime(datetmp, sizeof(datetmp), "%Y/%m/%d %X %A", localtime(&t));
	buy.picurl = "0";
	if (buy.type == 1)
{
	//buy.picurl = m_str_save_path;
	CStringA ppath(m_str_save_path.GetBuffer(0));
	string tpp = ppath.GetBuffer(0);
	string s(tpp.rbegin(), tpp.rend());
	int pos = s.find("/");
	if(pos<0) pos = s.find("\\");
	string sub =s.substr(0,pos);
	buy.picurl=string(sub.rbegin(),sub.rend());
	//itoa(buy.status, status, 10);
	//string sql_cnt = "SELECT COUNT(*) FROM pyt_friend_shoping where "


	//开始上传图片PicReaaPath
	int var = m_tcp.SocketStart();
	if (var < 0) {
		MessageBoxA(0, "无法连接服务器，请检查网络", 0, 0);
		//退出
		goto loop;
		//CDialog::OnCancel();
		return;
	}
	
	//采用套接字进行登录验证
	//SocketStart();
	//初始化发送信息
	char* addr = const_cast<char*>(logaddr);
	char* host = const_cast<char*>(hostaddr);
	int post = 80;

	string msg = "u=" + cm_ower.username;
	//char * ms = msg.c_str();
	CStringA realp(PicReaaPath.GetBuffer(0));
	string  realps = realp.GetBuffer(0);
	m_tcp.sendinf(addr, host, msg.c_str(), post);

	//获取返回信息
	char recv_str[4096] = { 0 };
	if (recv(m_tcp.sHost, recv_str, sizeof(recv_str), 0) == -1)
	{
		// cout << "recv failed" << endl;
		MessageBox(_T("recv nothings !"), 0, 0);
		goto loop;
		return;
	}
	wchar_t trp[4096];
	int ulBytes = MultiByteToWideChar(CP_ACP, 0, recv_str, -1, NULL, 0);
	ulBytes = MultiByteToWideChar(CP_ACP, 0, recv_str, -1, trp, ulBytes);
	CString ss(trp);
	//采用json解压包
	Json::Value troot;
	Json::Reader reader;
	Json::FastWriter fast_writer;
	/*
	CStringA stra(ss.GetBuffer(0));
	//ss.ReleaseBuffer();
	string  st = stra.GetBuffer(0);
	//stra.ReleaseBuffer();
	//char *stt=	
	*/
	string sst = strstr(recv_str, "{");
	if (!reader.parse(sst, troot, false)) {

		MessageBox(_T("图片上传失败!\n"), 0, 0);
		
		goto loop;
		return;
	}
	//MessageBox(ss, 0, 0);
	string name = troot["rt"].asString();
	string gender = troot["st"].asString();
	Ccommon md5Class;
	//pwd转化为string
	string tmpd = cm_ower.password;
	char tmps[1024], ctmps[1024];
	memset(tmps, 0, sizeof(tmps));
	memset(tmps, 0, sizeof(ctmps));
	tmpd += name;

	strcpy(tmps, md5Class.md5(tmpd.c_str()));
	strcpy(ctmps, md5Class.md5(tmps));
	strcat(ctmps, gender.c_str());
	strcpy(tmps, md5Class.md5(ctmps));
	string pwdtmp(tmps);
	//添加id_count，picurl

	CStringA pcireac(PicReaaPath.GetBuffer(0));
	CStringA realpict(m_str_save_path.GetBuffer(0));

	//string wmsg = "u=" + ower.username + "&p=" + pwdtmp + "&id_account=" + pcireac.GetBuffer(0)
		//+ "&picurl=" + realpict.GetBuffer(0);
	//初始化发送信息
	char sinf[512] = { 0 };
	//strcpy(sinf, wmsg.c_str());
	CStringA  DejiPath(DengjiPath.GetBuffer(0));
	
	char * tmppc = const_cast<char*>(realps.c_str());
	string Dji_picnam =DejiPath.GetBuffer(0);
	char *saddr = const_cast<char *>(addr_pic);
	char *picnam = const_cast<char *>(Dji_picnam.c_str());
	m_tcp.sendPic(saddr, host, tmppc, picnam, post, cm_ower.username, pwdtmp);
	 memset(recv_str, 0, sizeof(recv_str));   //清空
	if (recv(m_tcp.sHost, recv_str, sizeof(recv_str), 0) == -1)
	{
		MessageBox(_T("recv nothings !"), 0, 0);
		goto loop;
		return;
	}

	sst = strstr(recv_str, "{");
	if (!reader.parse(sst, troot, false)) {
		MessageBox(_T("图片上传未知错误！\n"), 0, 0);
		goto loop;
		return;
	}

	name = troot["status"].asString();

	if (!name.empty()&&name.compare("sucess"))
	{
		MessageBox(_T("图片上传失败！,请重试.."), 0, 0);
		goto loop;
		return;
	}
	//继续获取服务器的实名和等级图片路径
	buy.id_account = troot["id_account_path"].asString();
	buy.picurl = troot["picurl"].asString();
}
	
	//如果照片传输成功则将将数据保存至数据库中
   sql = "INSERT INTO pyt_friend_shoping values(0,'"+buy.account+"',"
	   +type+",'"+buy.level+"',"+(buy.status+=(buy.status.empty()?"0":""))+",'"+buy.born+"',0,'"+buy.picurl
	   +"',"+buy.sex+",'"+buy.manname+"','"+buy.id_account+"','"+(buy.mobile+=(buy.mobile.empty()?"0":""))+"','"+buy.address+"','"
	   +datetmp+"','"+buy.province+"','"+buy.city+"','"+buy.area+"')";
  //开始更新
  int tvar = mysql_real_query(&m_sqlCon, sql.c_str(), (unsigned int)sql.size());
  if (tvar != 0) {
	  MessageBox(L"注册信息添加失败！");
	  goto loop;
	  return;
  }
   CDialog::OnOK();
loop:;

   closesocket(m_tcp.sHost);	//关闭套接字
   WSACleanup();		//释放套接字资源

}

void GoodInf::OnBnClickedButton1()
{
	
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE, //TRUE为OPEN对话框，FALSE为SAVE AS对话框
		NULL,
		NULL,
		OFN_CREATEPROMPT | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("BMP Files (*.bmp)|*.bmp|JPG Files (*.jpg)|*.jpg|All Files (*.*)|*.*||"),
		NULL);

	if (dlg.DoModal() == IDOK)
	{
		m_str_save_path= dlg.GetPathName(); //文件名保存在了FilePathName里
		CStringA ppath(m_str_save_path.GetBuffer(0));
		string tpp = ppath.GetBuffer(0);
		string s(tpp.rbegin(), tpp.rend());

		int pos = s.find("/");
		if (pos<0) pos = s.find("\\");
		string sub = s.substr(0, pos);
		buy.picurl ="\\"+string(sub.rbegin(), sub.rend()); //放置于相对路径下 
		//转化为CString
		jietu mypicture ;
		mypicture.photoPath = m_str_save_path; //取源文件的路径
		//mypicture.lpFilepath.Format(L"%s", buy.picurl.c_str()); //保存文件的路径
		/*字符之间的转换*/
		wchar_t trp[4096];
		int ulBytes = MultiByteToWideChar(CP_ACP, 0, buy.picurl.c_str(), -1, NULL, 0);
		ulBytes = MultiByteToWideChar(CP_ACP, 0, buy.picurl.c_str(), -1, trp, ulBytes);
		mypicture.lpFilepath = CString(trp);
		//装载图片
	
		mypicture.DoModal();  //采用模式显示
		PicReaaPath = mypicture.lpFilepath;  //获取相对路径

	}
	else
	{
	  return;
	}
	if (DengjiPath.IsEmpty())
		MessageBox(L"请Ctrl+Alt+X继续等级切图");
	else
		QiehaoShangc.SetWindowTextW(DengjiPath);
	//将照片数据上传出去

	return;
}

void GoodInf::OnBtnPrintScreen()
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	AfxGetMainWnd()->ShowWindow(SW_MINIMIZE);
	Sleep(500);
	HWND hWnd;
	hWnd = GetDlgItem(IDD_KEHU_DIALOG)->GetSafeHwnd();
	//HWND hWnd = ::GetDesktopWindow();//获得屏幕的HWND.
	HDC hScreenDC = ::GetDC(hWnd);   //获得屏幕的HDC.
	HDC MemDC = ::CreateCompatibleDC(hScreenDC);
	RECT rect;
	::GetWindowRect(hWnd, &rect);
	SIZE screensize;
	screensize.cx = rect.right - rect.left;
	screensize.cy = rect.bottom - rect.top;
	HBITMAP hBitmap = ::CreateCompatibleBitmap(hScreenDC, screensize.cx, screensize.cy);
	HGDIOBJ hOldBMP = ::SelectObject(MemDC, hBitmap);
	::BitBlt(MemDC, 0, 0, screensize.cx, screensize.cy, hScreenDC, rect.left, rect.top, SRCCOPY);
	::SelectObject(MemDC, hOldBMP);
	::DeleteObject(MemDC);
	::ReleaseDC(hWnd, hScreenDC);


	//	if(this->m_bSaveToFile)
	this->WriteBmpToFile(hBitmap);

	//	if(this->m_bCopyToClip)
	this->CopyBmpToClipBoard(hBitmap);

	//	if(this->m_bOpenMspaint)
	::ShellExecute(NULL, L"open", L"mspaint.exe",/*调用画图程序*/
		this->m_str_save_path,
		NULL,
		SW_SHOWMAXIMIZED);

	AfxGetMainWnd()->ShowWindow(SW_NORMAL);     //恢复窗口显示模式 

}

void GoodInf::WriteBmpToFile(HBITMAP hBitmap)
{
	HDC hDC = ::CreateDC(L"DISPLAY", NULL, NULL, NULL);
	int iBits = ::GetDeviceCaps(hDC, BITSPIXEL) * ::GetDeviceCaps(hDC, PLANES);//当前分辨率下每个像素所占字节数  
	::DeleteDC(hDC);

	WORD   wBitCount;   //位图中每个像素所占字节数    
	if (iBits <= 1)
		wBitCount = 1;
	else if (iBits <= 4)
		wBitCount = 4;
	else if (iBits <= 8)
		wBitCount = 8;
	else if (iBits <= 24)
		wBitCount = 24;
	else
		wBitCount = iBits;

	DWORD   dwPaletteSize = 0;	//调色板大小， 位图中像素字节大小 
	if (wBitCount <= 8)
		dwPaletteSize = (1 << wBitCount) *	sizeof(RGBQUAD);


	BITMAP  bm;        //位图属性结构
	::GetObject(hBitmap, sizeof(bm), (LPSTR)&bm);


	BITMAPINFOHEADER   bi;       //位图信息头结构     
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = bm.bmWidth;
	bi.biHeight = bm.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = wBitCount;
	bi.biCompression = BI_RGB; //BI_RGB表示位图没有压缩
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	DWORD dwBmBitsSize = ((bm.bmWidth * wBitCount + 31) / 32) * 4 * bm.bmHeight;
	HANDLE hDib = ::GlobalAlloc(GHND, dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));  //为位图内容分配内存
	LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
	*lpbi = bi;

	HANDLE hPal = ::GetStockObject(DEFAULT_PALETTE);  // 处理调色板 
	HANDLE  hOldPal = NULL;
	if (hPal)
	{
		hDC = ::GetDC(NULL);
		hOldPal = SelectPalette(hDC, (HPALETTE)hPal, FALSE);
		RealizePalette(hDC);
	}
	::GetDIBits(hDC, hBitmap, 0, (UINT)bm.bmHeight, (LPSTR)lpbi + sizeof(BITMAPINFOHEADER) + dwPaletteSize, (BITMAPINFO*)lpbi, DIB_RGB_COLORS);// 获取该调色板下新的像素值
	if (hOldPal)//恢复调色板
	{
		SelectPalette(hDC, (HPALETTE)hOldPal, TRUE);
		RealizePalette(hDC);
		::ReleaseDC(NULL, hDC);
	}

	BITMAPFILEHEADER   bmfHdr; //位图文件头结构     
	bmfHdr.bfType = 0x4D42;  // "BM"  	// 设置位图文件头
	DWORD dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;

	HANDLE hFile = CreateFile(/*m_strFilePath*/this->m_str_save_path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);//创建位图文件   
	DWORD dwWritten;
	WriteFile(hFile, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);	// 写入位图文件头
	WriteFile(hFile, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL);// 写入位图文件其余内容

	GlobalUnlock(hDib);   //清除   
	GlobalFree(hDib);
	CloseHandle(hFile);

}
void GoodInf::OnCbnSelchangeCombo2()
{
	// TODO: Add your control notification handler code here
	CString  tcity;
	int index = ZhangHaoLevel.GetCurSel();
	ZhangHaoLevel.GetLBText(index, tcity);
	CStringA  aticy(tcity.GetBuffer(0));
	buy.level = aticy.GetBuffer(0);
}

void GoodInf::CopyBmpToClipBoard(HBITMAP hBitmap)
{
	OpenClipboard(); 	//打开剪贴板，并将位图拷到剪贴板上 
	EmptyClipboard();
	SetClipboardData(CF_BITMAP, hBitmap);
	CloseClipboard(); 	//关闭剪贴板  
}

void GoodInf::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	CString username;
	Birth.GetWindowTextW(username);
	CStringA tmusr(username.GetBuffer(0));
	buy.born = tmusr.GetBuffer(0);
	// TODO:  Add your control notification handler code here
}


void GoodInf::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
	women = 0;
	Man = 1;
}


void GoodInf::OnBnClickedRadio2()
{
	// TODO: Add your control notification handler code here
	women = 1;
	Man = 0;
}


void GoodInf::OnBnClickedButton3()
{
	if (time_cnt){
		CString str;
		str.Format(L"还需等待..%d S!", cnt);
		 MessageBox(str);
		 return;
	}
	// TODO:  在此添加控件通知处理程序代码
	//首先获取电话框里面的内容
	CString m_num;
	Iphone.GetWindowTextW(m_num);
	//检查长度，以及是否含有字母或其他
	CStringA a_num(m_num.GetBuffer(0));
	string  s_num = a_num.GetBuffer(0);
	int len = s_num.length();
	if (len != 11)
	{
		MessageBox(L"号码有误！");
		return;
	}
	for (int i = 0; i < len; i++){
		if (!isalnum(s_num.at(i))){
			MessageBox(L"号码有误！");
			return;
		}
	}

   //发送短信验证
	int var = m_tcp.SocketStart();
	if (var < 0) {
		MessageBoxA(0, "无法连接服务器，请检查网络", 0, 0);
		//退出
		//closesocket(sHost);	//关闭套接字
		WSACleanup();		//释放套接字资源
		//CDialog::OnCancel();
	}
	//采用套接字进行登录验证
	//SocketStart();
	//初始化发送信息
	char* addr = const_cast<char*>(addr_num);
	char* host = const_cast<char*>(hostaddr);
	int post = 80;
	string msg = "s=" + s_num;
	//char * ms = msg.c_str();
	char m_msg[1024];
	strcpy(m_msg,msg.c_str());
	m_tcp.sendPost1(addr, host, m_msg, post);
	//获取返回信息
	char recv_str[4096] = { 0 };
	if (recv(m_tcp.sHost, recv_str, sizeof(recv_str), 0) == -1)
	{
		// cout << "recv failed" << endl;
		MessageBox(_T("recv nothings !"), 0, 0);
		return;
	}

	wchar_t trp[4096];
	int ulBytes = MultiByteToWideChar(CP_ACP, 0, recv_str, -1, NULL, 0);
	ulBytes = MultiByteToWideChar(CP_ACP, 0, recv_str, -1, trp, ulBytes);
	CString ss(trp);
	//采用json解压包
	Json::Value troot;
	Json::Reader reader;
	Json::FastWriter fast_writer;

	string sst = strstr(recv_str, "{");
	if (!reader.parse(sst, troot, false)) {

		MessageBox(_T("发送失败，请再次发送\n"), 0, 0);
		//退出
		closesocket(m_tcp.sHost);	//关闭套接字
		WSACleanup();		//释放套接字资源
		return;
	}
	//MessageBox(ss, 0, 0);
	number = troot["Number"].asString();
	//coder 
	tmpvar= troot["Auth_code"].asInt();
	wchar_t trptmp[5];
	char tm_tmp[5];
	//MessageBoxA(NULL,coder.c_str(),""+tmpvar,0);
	closesocket(m_tcp.sHost);
	WSACleanup();
	SetTimer(M_TIMERB, 1000, 0);
	//SetTimer(1, 1000, 0);
	time_cnt = true;

}


void GoodInf::OnEnChangeEdit8()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void GoodInf::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case M_TIMERB: 
		if (cnt >-1){
			CString str;
			str.Format(L"%d", cnt);
			DTime.SetWindowTextW(str);  //m_Show为与显示数字的编辑框关联的变量
			UpdateData(false);
			if (cnt == 0){
				KillTimer(M_TIMERB);   //销毁定时器
				time_cnt = false;
				cnt = 60;
			}
			else   cnt--;
		}		break;

		default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}
