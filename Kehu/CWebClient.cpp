#include "stdafx.h"  
#include "CWebClient.h"  
#include <sstream>  
//#include "util.h"  
#include "../include/cef_app.h"  
#include "../include/cef_runnable.h"  
  
  
int  CWebClient::m_nBrowserCount = 0;  
CWebClient::CWebClient( const string& strUrl/*=L""*/ )  
: m_bIsClose(false)   
, m_strHomePage(strUrl)  
{  
  
}  
  
  
CWebClient::~CWebClient()   
{  
  
}  
 void CWebClient::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
	 REQUIRE_UI_THREAD();  
	// Remove from the list of existing browsers.  
    BrowserList::iterator bit = browser_list_.begin();  
    for (; bit != browser_list_.end(); ++bit) {  
        if ((*bit)->IsSame(browser)) {  
            browser_list_.erase(bit);  
            break;  
        }  
    }  
	CefQuitMessageLoop();
	/*
    if (browser_list_.empty()) {  
        // All browser windows have closed. Quit the application message loop.  
        CefQuitMessageLoop();  
    }*/ 
}
  
  
void CWebClient::CloseAllBrowsers(bool force_close)   
{  
    if (!CefCurrentlyOn(TID_UI))   
    {  
        // Execute on the UI thread.  
        CefPostTask(TID_UI, NewCefRunnableMethod(this, &CWebClient::CloseAllBrowsers, force_close)); 
		
        return;  
    }  
  
  if (browser_list_.empty())  
    return;  
  
  BrowserList::const_iterator it = browser_list_.begin();  
  for (; it != browser_list_.end(); ++it)  
    (*it)->GetHost()->CloseBrowser(force_close);  
}  
  
string CWebClient::GetLoadingUrl()  
{  
    CefRefPtr<CefFrame> pMainFram=GetMainFram();  
    return pMainFram.get()?pMainFram->GetURL():L"";  
}  
  
void CWebClient::Navigate( const string& strUrl )  
{  
    CefRefPtr<CefFrame> pMainFram=GetMainFram();  
    if ( pMainFram.get() )  
        pMainFram->LoadURL(strUrl.c_str());  
}  
  
void CWebClient::CreateBrowser( HWND hParentWnd, const RECT& rect )  
{  
    CefWindowInfo info;  
    CefBrowserSettings settings;  
    static wchar_t* pCharset = L"GB2312";  
    settings.default_encoding.str = pCharset;  
    settings.default_encoding.length = wcslen(pCharset); 
    info.SetAsChild(hParentWnd, rect);  
    m_hParent=hParentWnd;
    CefBrowserHost::CreateBrowser(info, this, m_strHomePage.c_str(), settings, NULL);  
}  
  
//****************************************************  
//菜单加载接口  
void CWebClient::OnBeforeContextMenu( CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
                                      CefRefPtr<CefContextMenuParams> params, CefRefPtr<CefMenuModel> model )  
{  
	  if ((params->GetTypeFlags() & (CM_TYPEFLAG_PAGE | CM_TYPEFLAG_FRAME)) != 0) {
    // Add a separator if the menu already has items.
    if (model->GetCount() > 0)
{
  model->Clear();
 //model->AddSeparator();
}
  }
    //在这里，我添加了自己想要的菜单  
   /* 
	cef_context_menu_type_flags_t flag =   params->GetTypeFlags();  
    if ( flag & CM_TYPEFLAG_PAGE )  
    {//普通页面的右键消息  
        model->SetLabel(MENU_ID_BACK, L"后退");  
        model->SetLabel(MENU_ID_FORWARD, L"前进");  
        model->SetLabel(MENU_ID_VIEW_SOURCE, L"查看源代码");  
        model->SetLabel(MENU_ID_PRINT, L"打印");  
        model->SetLabel(MENU_ID_RELOAD, L"刷新");  
        model->SetLabel(MENU_ID_RELOAD_NOCACHE, L"强制刷新");  
        model->SetLabel(MENU_ID_STOPLOAD, L"停止加载");  
        model->SetLabel(MENU_ID_REDO, L"重复");  
    }  
    if ( flag & CM_TYPEFLAG_EDITABLE)  
    {//编辑框的右键消息  
        model->SetLabel(MENU_ID_UNDO, L"撤销");  
        model->SetLabel(MENU_ID_REDO, L"重做");  
        model->SetLabel(MENU_ID_CUT, L"剪切");  
        model->SetLabel(MENU_ID_COPY, L"复制");  
        model->SetLabel(MENU_ID_PASTE, L"粘贴");  
        model->SetLabel(MENU_ID_DELETE, L"删除");  
        model->SetLabel(MENU_ID_SELECT_ALL, L"全选");  
    }
	*/
}  
  
bool CWebClient::OnContextMenuCommand( CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, 
                                       CefRefPtr<CefContextMenuParams> params, int command_id, EventFlags event_flags )  
{  
    return false;  
}  
  
  
//****************************************************  
//网页加载状态回调接口  
void CWebClient::OnLoadStart( CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame )  
{  

}  
  
void CWebClient::OnLoadEnd( CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode )  
{  
    //CefRefPtr<CefV8Context> v8 = frame->GetV8Context();  
}  
  
void CWebClient::OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, 
                              ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl)   
{  
    REQUIRE_UI_THREAD();  
    // Don't display an error for downloaded files.  
    if (errorCode == ERR_ABORTED)  
        return;  
    // Display a load error message.  
    std::wstringstream ss;  
    //std::wstring   
    ss << L"<html><body bgcolor=\"white\">"  
        L"<h2>内容错误 ---Gxjun " << std::wstring(failedUrl) <<  
        L" with error " << std::wstring(errorText) << L" (" << errorCode <<  
        L").</h2></body></html>"<<'\0';  
    frame->LoadString(ss.str(), failedUrl);  
}  
  
//****************************************************  
//状态改变回调接口  
void CWebClient::OnTitleChange( CefRefPtr<CefBrowser> browser, const CefString& title )  
{  
  
}  
  
void CWebClient::OnAddressChange( CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& url )  
{  
  
}  
  
bool CWebClient::OnTooltip( CefRefPtr<CefBrowser> browser, CefString& text )  
{  
    return false;  
}  
  
void CWebClient::OnStatusMessage( CefRefPtr<CefBrowser> browser, const CefString& value )  
{  
      
}  
  
//****************************************************  
//网页生命周期回调接口  
bool CWebClient::OnBeforePopup( CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,  
        const CefString& target_url, const CefString& target_frame_name, const CefPopupFeatures& popupFeatures,  
        CefWindowInfo& windowInfo, CefRefPtr<CefClient>& client, CefBrowserSettings& settings, 
        bool* no_javascript_access )  
{  
    //这里使用默认浏览器打开网页，避免CEF重新创建窗口  
    ShellExecute(NULL, L"open", target_url.c_str(), NULL, NULL, SW_SHOW);  
    //return false;//创建新窗口  
    return true; //禁止创建新的窗口  
}  
  
void CWebClient::OnAfterCreated(CefRefPtr<CefBrowser> browser)   
{  
    REQUIRE_UI_THREAD();  
	// Add to the list of existing browsers.  
    browser_list_.push_back(browser);  
    AutoLock scopLock(this);  
    if ( ! m_pBrowser.get() )  
        m_pBrowser=browser;  
    m_nBrowserCount++;  

}  
  
bool CWebClient::DoClose(CefRefPtr<CefBrowser> browser)   
{  
    REQUIRE_UI_THREAD();  
    // Closing the main window requires special handling. See the DoClose()  
    // documentation in the CEF header for a detailed destription of this  
    // process.  
    if (browser_list_.size() == 1) {  
        // Set a flag to indicate that the window close should be allowed.  
        m_bIsClose = true;  
    }  
  
    // Allow the close. For windowed browsers this will result in the OS close  
    // event being sent.  
    return false;  
}  
  

void CWebClient::OnBeforeDownload( CefRefPtr<CefBrowser> browser, CefRefPtr<CefDownloadItem> download_item,
        const CefString& suggested_name, CefRefPtr<CefBeforeDownloadCallback> callback )  
{  
    int i=0;  
}  
  
void CWebClient::OnDownloadUpdated( CefRefPtr<CefBrowser> browser, CefRefPtr<CefDownloadItem> download_item, 
        CefRefPtr<CefDownloadItemCallback> callback )  
{  
    //取消CEF内部下载文件，使用默认浏览器打开链接去下载，下载过程就不需要我们关心了，毕竟不是做浏览器  
     callback->Cancel(); 
    CefString strUrl = download_item->GetURL();  
    ShellExecute(NULL, L"open", strUrl.c_str(), NULL, NULL, SW_SHOW);  
    int i = 0;  
}  