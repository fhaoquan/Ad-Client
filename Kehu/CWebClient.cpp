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
//�˵����ؽӿ�  
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
    //�������������Լ���Ҫ�Ĳ˵�  
   /* 
	cef_context_menu_type_flags_t flag =   params->GetTypeFlags();  
    if ( flag & CM_TYPEFLAG_PAGE )  
    {//��ͨҳ����Ҽ���Ϣ  
        model->SetLabel(MENU_ID_BACK, L"����");  
        model->SetLabel(MENU_ID_FORWARD, L"ǰ��");  
        model->SetLabel(MENU_ID_VIEW_SOURCE, L"�鿴Դ����");  
        model->SetLabel(MENU_ID_PRINT, L"��ӡ");  
        model->SetLabel(MENU_ID_RELOAD, L"ˢ��");  
        model->SetLabel(MENU_ID_RELOAD_NOCACHE, L"ǿ��ˢ��");  
        model->SetLabel(MENU_ID_STOPLOAD, L"ֹͣ����");  
        model->SetLabel(MENU_ID_REDO, L"�ظ�");  
    }  
    if ( flag & CM_TYPEFLAG_EDITABLE)  
    {//�༭����Ҽ���Ϣ  
        model->SetLabel(MENU_ID_UNDO, L"����");  
        model->SetLabel(MENU_ID_REDO, L"����");  
        model->SetLabel(MENU_ID_CUT, L"����");  
        model->SetLabel(MENU_ID_COPY, L"����");  
        model->SetLabel(MENU_ID_PASTE, L"ճ��");  
        model->SetLabel(MENU_ID_DELETE, L"ɾ��");  
        model->SetLabel(MENU_ID_SELECT_ALL, L"ȫѡ");  
    }
	*/
}  
  
bool CWebClient::OnContextMenuCommand( CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, 
                                       CefRefPtr<CefContextMenuParams> params, int command_id, EventFlags event_flags )  
{  
    return false;  
}  
  
  
//****************************************************  
//��ҳ����״̬�ص��ӿ�  
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
        L"<h2>���ݴ��� ---Gxjun " << std::wstring(failedUrl) <<  
        L" with error " << std::wstring(errorText) << L" (" << errorCode <<  
        L").</h2></body></html>"<<'\0';  
    frame->LoadString(ss.str(), failedUrl);  
}  
  
//****************************************************  
//״̬�ı�ص��ӿ�  
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
//��ҳ�������ڻص��ӿ�  
bool CWebClient::OnBeforePopup( CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,  
        const CefString& target_url, const CefString& target_frame_name, const CefPopupFeatures& popupFeatures,  
        CefWindowInfo& windowInfo, CefRefPtr<CefClient>& client, CefBrowserSettings& settings, 
        bool* no_javascript_access )  
{  
    //����ʹ��Ĭ�����������ҳ������CEF���´�������  
    ShellExecute(NULL, L"open", target_url.c_str(), NULL, NULL, SW_SHOW);  
    //return false;//�����´���  
    return true; //��ֹ�����µĴ���  
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
    //ȡ��CEF�ڲ������ļ���ʹ��Ĭ�������������ȥ���أ����ع��̾Ͳ���Ҫ���ǹ����ˣ��Ͼ������������  
     callback->Cancel(); 
    CefString strUrl = download_item->GetURL();  
    ShellExecute(NULL, L"open", strUrl.c_str(), NULL, NULL, SW_SHOW);  
    int i = 0;  
}  