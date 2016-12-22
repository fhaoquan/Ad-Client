// News.cpp : 实现文件
//

#include "stdafx.h"
#include "Kehu.h"
#include "News.h"


// News 对话框

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
	// 在OnInitDialog()中添加
	// 获得桌面大小
	CRect rectWorkArea;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rectWorkArea, SPIF_SENDCHANGE);
	// 获得对话框大小
	CRect rectDlg;
	GetWindowRect(&rectDlg);
	int nW = rectDlg.Width();
	int nH = rectDlg.Height();
	//ShowOwnedPopups(False);
	// 将窗口设置到右下角
	::SetWindowPos(GetSafeHwnd(), HWND_BOTTOM, rectWorkArea.right - nW - 20, rectWorkArea.bottom - nH, nW, nH, SWP_NOZORDER);
	// 动画显示弹窗效果
	AnimateWindow(800, AW_SLIDE | AW_VER_NEGATIVE);
	COleVariant noArg;
	Navigate(CString(today_money.c_str()));
	// 捕获控件的错误
	m_pBrowserApp->put_Silent(VARIANT_TRUE);//禁止脚本错误提示
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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



// News 消息处理程序

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
	// TODO:  在此添加控件通知处理程序代码
}


void News::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
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

	// TODO:  在此处添加消息处理程序代码
	//this->DestroyWindow();
}


void News::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	/*CString strParams, strDir;
	CString strURL = L"http://www.cnblogs.com/gongxijun/";
	int nRet = (int)ShellExecute(NULL, L"open", strURL, strParams, strDir, SW_SHOWNORMAL);
	*/
	CDialog::OnCancel();
	//CDHtmlDialog::OnClose();
}
