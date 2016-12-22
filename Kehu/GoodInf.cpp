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
   ModifyStyle(0, WS_SIZEBOX);  //���öԻ����С�ɱ�
   GetClientRect(m_rect);  //�õ���ʼ�Ի���Ĵ�С
   //���˺����ͽ��г�ʼ��
   ZhangHaoType.InsertString(0, L"�Ա�/��è/1688");
   ZhangHaoType.InsertString(1,L"����");
   ZhangHaoType.InsertString(2,L"һ�ŵ�");
   ZhangHaoType.InsertString(3,L"ΨƷ��");
   ZhangHaoType.InsertString(4,L"������Ʒ");
   ZhangHaoType.InsertString(5,L"����˵");
   ZhangHaoType.InsertString(6,L"ΨƷ��");
   ZhangHaoType.InsertString(7,L"Ģ����");
   ZhangHaoType.SetCurSel(0);
   //���˺ŵȼ����г�ʼ��
   ZhangHaoLevel.AddString(CString("1��"));
   ZhangHaoLevel.AddString(CString("2��"));
   ZhangHaoLevel.AddString(CString("3��"));
   ZhangHaoLevel.AddString(CString("4��"));
   ZhangHaoLevel.AddString(CString("5��"));
   ZhangHaoLevel.AddString(CString("1��"));
   ZhangHaoLevel.AddString(CString("2��"));
   ZhangHaoLevel.AddString(CString("3��"));
   ZhangHaoLevel.AddString(CString("4��"));
   ZhangHaoLevel.AddString(CString("5��"));
   ZhangHaoLevel.SetCurSel(0); //����Ĭ����ʾ������
   //���Ա���г�ʼ��
   ((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(1);//����Ĭ��ѡ����Ա�
     SexType = "��";
	 //��ʡ���У��أ����������г�ʼ��
	 Provice.AddString(L"ʡ");
	 Provice.SetCurSel(0);
	 shiqu.AddString(L"��");
	 shiqu.SetCurSel(0);
	 xianqu.AddString(L"��");
	 xianqu.SetCurSel(0);
	 //�������ݿ�
	  mysql_init(&m_sqlCon);
	 // localhost:������ rootΪ�˺����� testΪ���ݿ��� 3306Ϊ�˿�  
	 if (!mysql_real_connect(&m_sqlCon, hostaddr, root, tpwd, biao, port, NULL, 0)) {
		 MessageBox(_T("���ݿ�����ʧ��!"));
		 return FALSE;
	 }
	 mysql_set_character_set(&m_sqlCon, "gbk");
	 char *sql = "select province from province";
	 MYSQL_RES *res; //�����
	 MYSQL_ROW row;
	 int var = mysql_real_query(&m_sqlCon, sql, (unsigned int)strlen(sql));
	 if (var != 0) {
		 MessageBox(L"��ͼ���ݿ����ʧ�ܣ�");
		 return -1;
	 }
	 Provice.ResetContent();
	 res = mysql_store_result(&m_sqlCon);
	 wchar_t buf[128];
	 while (row = mysql_fetch_row(res)) {
		 for (int t = 0; t < mysql_num_fields(res); t++) {
			 //charת��Ϊstring
			 int charLen = strlen(row[t]);
			 //������ֽ��ַ��Ĵ�С�����ַ����㡣
			 int len = MultiByteToWideChar(CP_ACP, 0, row[t], charLen, NULL, 0);
			 //Ϊ���ֽ��ַ���������ռ䣬�����СΪ���ֽڼ���Ķ��ֽ��ַ���С
			 MultiByteToWideChar(CP_ACP, 0, row[t], charLen, buf, len);
			 buf[len] = '\0'; //����ַ�����β��ע�ⲻ��len+1
							  //stringתΪCStringT
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
	//�˺�
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
	 //˵�����ȵ��Ա�����è��1688
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
		 //�������ڴ�С
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
		
			ZhangHaoLevel.AddString(CString("1��"));
			ZhangHaoLevel.AddString(CString("2��"));
			ZhangHaoLevel.AddString(CString("3��"));
			ZhangHaoLevel.AddString(CString("4��"));
			ZhangHaoLevel.AddString(CString("5��"));
			ZhangHaoLevel.AddString(CString("1��"));
			ZhangHaoLevel.AddString(CString("2��"));
			ZhangHaoLevel.AddString(CString("3��"));
			ZhangHaoLevel.AddString(CString("4��"));
			ZhangHaoLevel.AddString(CString("5��"));
		
	}   break;
	case 1: {
		ZhangHaoLevel.AddString(L"ͭ�ƻ�Ա");
		ZhangHaoLevel.AddString(L"���ƻ�Ա");
		ZhangHaoLevel.AddString(L"���ƻ�Ա");
		ZhangHaoLevel.AddString(L"��ʯ��Ա");
	} break;
	case 2: {
		ZhangHaoLevel.AddString(L"V1");
		ZhangHaoLevel.AddString(L"V2");
		ZhangHaoLevel.AddString(L"V3");
	}break;
	case 3: {
		ZhangHaoLevel.AddString(L"���ƻ�Ա");
		ZhangHaoLevel.AddString(L"ͭ�ƻ�Ա");
		ZhangHaoLevel.AddString(L"���ƻ�Ա");
		ZhangHaoLevel.AddString(L"���ƻ�Ա");
		ZhangHaoLevel.AddString(L"��ʯ��Ա");
		ZhangHaoLevel.AddString(L"�ʹڻ�Ա");
	} break;
	case 4: {
		ZhangHaoLevel.AddString(L"��ͨ��Ա");
		ZhangHaoLevel.AddString(L"�ƽ��Ա");
		ZhangHaoLevel.AddString(L"�׽��Ա");
	}
	case 5:
	case 6:
	{
		ZhangHaoLevel.AddString(L"ע���Ա");
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
	MYSQL_RES *ares; //�����
	MYSQL_ROW arow;
	int var = mysql_real_query(&m_sqlCon, bsql.c_str(), (unsigned int)(bsql.size()));
	if (var != 0) {
		MessageBox(L"û���ҵ���ʡ����");
		return;
	}
	ares = mysql_store_result(&m_sqlCon);
	arow = mysql_fetch_row(ares);

	std::string sql = "select city from city where father =" + std::string(arow[0]);
	//char sql[] = ssql.c_str();
	MYSQL_RES *res; //�����
	MYSQL_ROW row;
	int avar = mysql_real_query(&m_sqlCon, sql.c_str(), (unsigned int)(sql.size()));
	if (avar != 0) {
		MessageBox(L"��ͼ���ݿ����ʧ�ܣ�");
		return;
	}
	shiqu.ResetContent();
	res = mysql_store_result(&m_sqlCon);
	wchar_t buf[128];
	while (row = mysql_fetch_row(res)) {

		for (int t = 0; t < mysql_num_fields(res); t++) {
			//charת��Ϊstring
			int charLen = strlen(row[t]);
			//������ֽ��ַ��Ĵ�С�����ַ����㡣
			int len = MultiByteToWideChar(CP_ACP, 0, row[t], charLen, NULL, 0);
			//Ϊ���ֽ��ַ���������ռ䣬�����СΪ���ֽڼ���Ķ��ֽ��ַ���С
			MultiByteToWideChar(CP_ACP, 0, row[t], charLen, buf, len);
			buf[len] = '\0'; //����ַ�����β��ע�ⲻ��len+1
							 //stringתΪCStringT
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
	MYSQL_RES *ares; //�����
	MYSQL_ROW arow;
	std::string bsql = "select cityID from city where city ='" +xqu+"'";
	int var = mysql_real_query(&m_sqlCon, bsql.c_str(), (unsigned int)(bsql.size()));
	if (var != 0) {
		MessageBox(L"��ͼ���ݿ����ʧ�ܣ�");
		return;
	}
	ares = mysql_store_result(&m_sqlCon);
	arow = mysql_fetch_row(ares);

	std::string sql = "select area from area where father ="+ std::string(arow[0]);
	//char sql[] = ssql.c_str();
	MYSQL_RES *res; //�����
	MYSQL_ROW row;
	int avar = mysql_real_query(&m_sqlCon, sql.c_str(), (unsigned int)(sql.size()));
	if (avar != 0) {
		MessageBox(L"��ͼ���ݿ����ʧ�ܣ�");
		return ;
	}
	xianqu.ResetContent();
	res = mysql_store_result(&m_sqlCon);
	wchar_t buf[128];
	while (row = mysql_fetch_row(res)) {

		for (int t = 0; t < mysql_num_fields(res); t++) {
			//charת��Ϊstring
			int charLen = strlen(row[t]);
			//������ֽ��ַ��Ĵ�С�����ַ����㡣
			int len = MultiByteToWideChar(CP_ACP, 0, row[t], charLen, NULL, 0);
			//Ϊ���ֽ��ַ���������ռ䣬�����СΪ���ֽڼ���Ķ��ֽ��ַ���С
			MultiByteToWideChar(CP_ACP, 0, row[t], charLen, buf, len);
			buf[len] = '\0'; //����ַ�����β��ע�ⲻ��len+1
							 //stringתΪCStringT
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
	//��������˵�����ع��ܣ�����
	//��ʡ����ע�뵽�ṹ����	Provice.
	CString  tp;
	string sql;
	int index = Provice.GetCurSel();
	if (index < 0)tp = L"0";
	else Provice.GetLBText(index, tp);

	CStringA  ap(tp.GetBuffer(0));
	buy.province = ap.GetBuffer(0);
	//��
	CString  tc;
	index = shiqu.GetCurSel();
	if (index < 0)tp = L"0";
	else shiqu.GetLBText(index, tc);
	CStringA  ac(tc.GetBuffer(0));
	buy.city = ac.GetBuffer(0);
	//����
	CString  ta;
	index = xianqu.GetCurSel();
	if (index < 0)ta = L"0";
	else xianqu.GetLBText(index, ta);

	CStringA  aa(ta.GetBuffer(0));
	buy.area = aa.GetBuffer(0);
	//��ȡ�Ա�   	
	buy.sex = (Man == 1) ? "0" : "1";
	if (buy.type == 1){
    //��֤�ֻ�����
	CString Iph_num;
	SjiMa.GetWindowTextW(Iph_num);
	CString Iph_Yz;
	Iph_Yz.Format(L"%d", tmpvar);
	if (Iph_num.Compare(Iph_Yz) == 0)	{
		//���
		CStringA Iph_tmp(Iph_num.GetBuffer(0));
	 	 buy.mobile = Iph_tmp.GetBuffer(0);
	}
	}
else
	buy.mobile = "0";

	//�ύ�����ݿ���
	char type[4], status[4];
	itoa(buy.type, type, 10);

	time_t t = time(0); //������˵һ�º�������time(NULL),ע�⣡����
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


	//��ʼ�ϴ�ͼƬPicReaaPath
	int var = m_tcp.SocketStart();
	if (var < 0) {
		MessageBoxA(0, "�޷����ӷ���������������", 0, 0);
		//�˳�
		goto loop;
		//CDialog::OnCancel();
		return;
	}
	
	//�����׽��ֽ��е�¼��֤
	//SocketStart();
	//��ʼ��������Ϣ
	char* addr = const_cast<char*>(logaddr);
	char* host = const_cast<char*>(hostaddr);
	int post = 80;

	string msg = "u=" + cm_ower.username;
	//char * ms = msg.c_str();
	CStringA realp(PicReaaPath.GetBuffer(0));
	string  realps = realp.GetBuffer(0);
	m_tcp.sendinf(addr, host, msg.c_str(), post);

	//��ȡ������Ϣ
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
	//����json��ѹ��
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

		MessageBox(_T("ͼƬ�ϴ�ʧ��!\n"), 0, 0);
		
		goto loop;
		return;
	}
	//MessageBox(ss, 0, 0);
	string name = troot["rt"].asString();
	string gender = troot["st"].asString();
	Ccommon md5Class;
	//pwdת��Ϊstring
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
	//���id_count��picurl

	CStringA pcireac(PicReaaPath.GetBuffer(0));
	CStringA realpict(m_str_save_path.GetBuffer(0));

	//string wmsg = "u=" + ower.username + "&p=" + pwdtmp + "&id_account=" + pcireac.GetBuffer(0)
		//+ "&picurl=" + realpict.GetBuffer(0);
	//��ʼ��������Ϣ
	char sinf[512] = { 0 };
	//strcpy(sinf, wmsg.c_str());
	CStringA  DejiPath(DengjiPath.GetBuffer(0));
	
	char * tmppc = const_cast<char*>(realps.c_str());
	string Dji_picnam =DejiPath.GetBuffer(0);
	char *saddr = const_cast<char *>(addr_pic);
	char *picnam = const_cast<char *>(Dji_picnam.c_str());
	m_tcp.sendPic(saddr, host, tmppc, picnam, post, cm_ower.username, pwdtmp);
	 memset(recv_str, 0, sizeof(recv_str));   //���
	if (recv(m_tcp.sHost, recv_str, sizeof(recv_str), 0) == -1)
	{
		MessageBox(_T("recv nothings !"), 0, 0);
		goto loop;
		return;
	}

	sst = strstr(recv_str, "{");
	if (!reader.parse(sst, troot, false)) {
		MessageBox(_T("ͼƬ�ϴ�δ֪����\n"), 0, 0);
		goto loop;
		return;
	}

	name = troot["status"].asString();

	if (!name.empty()&&name.compare("sucess"))
	{
		MessageBox(_T("ͼƬ�ϴ�ʧ�ܣ�,������.."), 0, 0);
		goto loop;
		return;
	}
	//������ȡ��������ʵ���͵ȼ�ͼƬ·��
	buy.id_account = troot["id_account_path"].asString();
	buy.picurl = troot["picurl"].asString();
}
	
	//�����Ƭ����ɹ��򽫽����ݱ��������ݿ���
   sql = "INSERT INTO pyt_friend_shoping values(0,'"+buy.account+"',"
	   +type+",'"+buy.level+"',"+(buy.status+=(buy.status.empty()?"0":""))+",'"+buy.born+"',0,'"+buy.picurl
	   +"',"+buy.sex+",'"+buy.manname+"','"+buy.id_account+"','"+(buy.mobile+=(buy.mobile.empty()?"0":""))+"','"+buy.address+"','"
	   +datetmp+"','"+buy.province+"','"+buy.city+"','"+buy.area+"')";
  //��ʼ����
  int tvar = mysql_real_query(&m_sqlCon, sql.c_str(), (unsigned int)sql.size());
  if (tvar != 0) {
	  MessageBox(L"ע����Ϣ���ʧ�ܣ�");
	  goto loop;
	  return;
  }
   CDialog::OnOK();
loop:;

   closesocket(m_tcp.sHost);	//�ر��׽���
   WSACleanup();		//�ͷ��׽�����Դ

}

void GoodInf::OnBnClickedButton1()
{
	
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE, //TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
		NULL,
		NULL,
		OFN_CREATEPROMPT | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("BMP Files (*.bmp)|*.bmp|JPG Files (*.jpg)|*.jpg|All Files (*.*)|*.*||"),
		NULL);

	if (dlg.DoModal() == IDOK)
	{
		m_str_save_path= dlg.GetPathName(); //�ļ�����������FilePathName��
		CStringA ppath(m_str_save_path.GetBuffer(0));
		string tpp = ppath.GetBuffer(0);
		string s(tpp.rbegin(), tpp.rend());

		int pos = s.find("/");
		if (pos<0) pos = s.find("\\");
		string sub = s.substr(0, pos);
		buy.picurl ="\\"+string(sub.rbegin(), sub.rend()); //���������·���� 
		//ת��ΪCString
		jietu mypicture ;
		mypicture.photoPath = m_str_save_path; //ȡԴ�ļ���·��
		//mypicture.lpFilepath.Format(L"%s", buy.picurl.c_str()); //�����ļ���·��
		/*�ַ�֮���ת��*/
		wchar_t trp[4096];
		int ulBytes = MultiByteToWideChar(CP_ACP, 0, buy.picurl.c_str(), -1, NULL, 0);
		ulBytes = MultiByteToWideChar(CP_ACP, 0, buy.picurl.c_str(), -1, trp, ulBytes);
		mypicture.lpFilepath = CString(trp);
		//װ��ͼƬ
	
		mypicture.DoModal();  //����ģʽ��ʾ
		PicReaaPath = mypicture.lpFilepath;  //��ȡ���·��

	}
	else
	{
	  return;
	}
	if (DengjiPath.IsEmpty())
		MessageBox(L"��Ctrl+Alt+X�����ȼ���ͼ");
	else
		QiehaoShangc.SetWindowTextW(DengjiPath);
	//����Ƭ�����ϴ���ȥ

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
	//HWND hWnd = ::GetDesktopWindow();//�����Ļ��HWND.
	HDC hScreenDC = ::GetDC(hWnd);   //�����Ļ��HDC.
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
	::ShellExecute(NULL, L"open", L"mspaint.exe",/*���û�ͼ����*/
		this->m_str_save_path,
		NULL,
		SW_SHOWMAXIMIZED);

	AfxGetMainWnd()->ShowWindow(SW_NORMAL);     //�ָ�������ʾģʽ 

}

void GoodInf::WriteBmpToFile(HBITMAP hBitmap)
{
	HDC hDC = ::CreateDC(L"DISPLAY", NULL, NULL, NULL);
	int iBits = ::GetDeviceCaps(hDC, BITSPIXEL) * ::GetDeviceCaps(hDC, PLANES);//��ǰ�ֱ�����ÿ��������ռ�ֽ���  
	::DeleteDC(hDC);

	WORD   wBitCount;   //λͼ��ÿ��������ռ�ֽ���    
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

	DWORD   dwPaletteSize = 0;	//��ɫ���С�� λͼ�������ֽڴ�С 
	if (wBitCount <= 8)
		dwPaletteSize = (1 << wBitCount) *	sizeof(RGBQUAD);


	BITMAP  bm;        //λͼ���Խṹ
	::GetObject(hBitmap, sizeof(bm), (LPSTR)&bm);


	BITMAPINFOHEADER   bi;       //λͼ��Ϣͷ�ṹ     
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = bm.bmWidth;
	bi.biHeight = bm.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = wBitCount;
	bi.biCompression = BI_RGB; //BI_RGB��ʾλͼû��ѹ��
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	DWORD dwBmBitsSize = ((bm.bmWidth * wBitCount + 31) / 32) * 4 * bm.bmHeight;
	HANDLE hDib = ::GlobalAlloc(GHND, dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));  //Ϊλͼ���ݷ����ڴ�
	LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
	*lpbi = bi;

	HANDLE hPal = ::GetStockObject(DEFAULT_PALETTE);  // �����ɫ�� 
	HANDLE  hOldPal = NULL;
	if (hPal)
	{
		hDC = ::GetDC(NULL);
		hOldPal = SelectPalette(hDC, (HPALETTE)hPal, FALSE);
		RealizePalette(hDC);
	}
	::GetDIBits(hDC, hBitmap, 0, (UINT)bm.bmHeight, (LPSTR)lpbi + sizeof(BITMAPINFOHEADER) + dwPaletteSize, (BITMAPINFO*)lpbi, DIB_RGB_COLORS);// ��ȡ�õ�ɫ�����µ�����ֵ
	if (hOldPal)//�ָ���ɫ��
	{
		SelectPalette(hDC, (HPALETTE)hOldPal, TRUE);
		RealizePalette(hDC);
		::ReleaseDC(NULL, hDC);
	}

	BITMAPFILEHEADER   bmfHdr; //λͼ�ļ�ͷ�ṹ     
	bmfHdr.bfType = 0x4D42;  // "BM"  	// ����λͼ�ļ�ͷ
	DWORD dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;

	HANDLE hFile = CreateFile(/*m_strFilePath*/this->m_str_save_path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);//����λͼ�ļ�   
	DWORD dwWritten;
	WriteFile(hFile, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);	// д��λͼ�ļ�ͷ
	WriteFile(hFile, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL);// д��λͼ�ļ���������

	GlobalUnlock(hDib);   //���   
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
	OpenClipboard(); 	//�򿪼����壬����λͼ������������ 
	EmptyClipboard();
	SetClipboardData(CF_BITMAP, hBitmap);
	CloseClipboard(); 	//�رռ�����  
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
		str.Format(L"����ȴ�..%d S!", cnt);
		 MessageBox(str);
		 return;
	}
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//���Ȼ�ȡ�绰�����������
	CString m_num;
	Iphone.GetWindowTextW(m_num);
	//��鳤�ȣ��Լ��Ƿ�����ĸ������
	CStringA a_num(m_num.GetBuffer(0));
	string  s_num = a_num.GetBuffer(0);
	int len = s_num.length();
	if (len != 11)
	{
		MessageBox(L"��������");
		return;
	}
	for (int i = 0; i < len; i++){
		if (!isalnum(s_num.at(i))){
			MessageBox(L"��������");
			return;
		}
	}

   //���Ͷ�����֤
	int var = m_tcp.SocketStart();
	if (var < 0) {
		MessageBoxA(0, "�޷����ӷ���������������", 0, 0);
		//�˳�
		//closesocket(sHost);	//�ر��׽���
		WSACleanup();		//�ͷ��׽�����Դ
		//CDialog::OnCancel();
	}
	//�����׽��ֽ��е�¼��֤
	//SocketStart();
	//��ʼ��������Ϣ
	char* addr = const_cast<char*>(addr_num);
	char* host = const_cast<char*>(hostaddr);
	int post = 80;
	string msg = "s=" + s_num;
	//char * ms = msg.c_str();
	char m_msg[1024];
	strcpy(m_msg,msg.c_str());
	m_tcp.sendPost1(addr, host, m_msg, post);
	//��ȡ������Ϣ
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
	//����json��ѹ��
	Json::Value troot;
	Json::Reader reader;
	Json::FastWriter fast_writer;

	string sst = strstr(recv_str, "{");
	if (!reader.parse(sst, troot, false)) {

		MessageBox(_T("����ʧ�ܣ����ٴη���\n"), 0, 0);
		//�˳�
		closesocket(m_tcp.sHost);	//�ر��׽���
		WSACleanup();		//�ͷ��׽�����Դ
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void GoodInf::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
	case M_TIMERB: 
		if (cnt >-1){
			CString str;
			str.Format(L"%d", cnt);
			DTime.SetWindowTextW(str);  //m_ShowΪ����ʾ���ֵı༭������ı���
			UpdateData(false);
			if (cnt == 0){
				KillTimer(M_TIMERB);   //���ٶ�ʱ��
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
