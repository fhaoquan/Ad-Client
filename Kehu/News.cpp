// News.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Kehu.h"
#include "News.h"


// News �Ի���

IMPLEMENT_DYNCREATE(News, CDHtmlDialog)

News::News(CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(News::IDD, News::IDH, pParent)
{
}

News::~News()
{
	
}

void News::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);

}

BOOL News::OnInitDialog()
{	
	//UpdateWindow();
	CDHtmlDialog::OnInitDialog();
	//ModifyStyleEx(0, WS_EX_APPWINDOW);
	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);
	// ��OnInitDialog()�����
	// ��������С
	CRect rectWorkArea;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rectWorkArea, SPIF_SENDCHANGE);
	// ��öԻ����С
	CRect rectDlg;
	GetWindowRect(&rectDlg);
	int nW = rectDlg.Width();
	int nH = rectDlg.Height();
	//ShowOwnedPopups(False);
	// ���������õ����½�
	::SetWindowPos(GetSafeHwnd(), HWND_BOTTOM, rectWorkArea.right - nW - 20, rectWorkArea.bottom - nH, nW, nH, SWP_NOZORDER);
	// ������ʾ����Ч��
	AnimateWindow(800, AW_SLIDE | AW_VER_NEGATIVE);
	COleVariant noArg;
	Navigate(CString(today_money.c_str()));
	// ����ؼ��Ĵ���
	m_pBrowserApp->put_Silent(VARIANT_TRUE);//��ֹ�ű�������ʾ
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

BEGIN_MESSAGE_MAP(News, CDHtmlDialog)
	ON_BN_CLICKED(IDOK, &News::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &News::OnBnClickedCancel)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

BEGIN_DHTML_EVENT_MAP(News)
	DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
	DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
END_DHTML_EVENT_MAP()



// News ��Ϣ�������

HRESULT News::OnButtonOK(IHTMLElement* /*pElement*/)
{
	OnOK();
	return S_OK;
}

HRESULT News::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	OnCancel();
	return S_OK;
}


void News::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void News::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
void News::GotoUrl(LPCTSTR pszUrl){

	CString strPath, str;
	DWORD dwSize = MAX_PATH;
	::GetModuleFileName(NULL, strPath.GetBuffer(MAX_PATH), dwSize); //AfxGetResourceHandle()
	strPath.ReleaseBuffer(dwSize);
	str = strPath.Left(strPath.ReverseFind('//')+1);
	ASSERT(pszUrl != NULL);
	if (pszUrl != NULL){
		CString strUrl;
		strUrl = str+pszUrl;
		//Navigate(_T("file:///"),strUrl);

	}
}

void News::OnDestroy()
{
	CDHtmlDialog::OnDestroy();

	// TODO:  �ڴ˴������Ϣ����������
	//this->DestroyWindow();
}


void News::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	/*CString strParams, strDir;
	CString strURL = L"http://www.cnblogs.com/gongxijun/";
	int nRet = (int)ShellExecute(NULL, L"open", strURL, strParams, strDir, SW_SHOWNORMAL);
	*/
	CDialog::OnCancel();
	//CDHtmlDialog::OnClose();
}
