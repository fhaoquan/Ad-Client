#pragma once
#include "include/cef_client.h"
#include<cef_browser.h>
#include<cef_cookie.h>  //设置cookie
#include<cef_runnable.h>
#include<cef_app.h>
#include <list>
#include <string>

using std::string;


#define REQUIRE_UI_THREAD()   ASSERT(CefCurrentlyOn(TID_UI));
#define REQUIRE_IO_THREAD()   ASSERT(CefCurrentlyOn(TID_IO));
#define REQUIRE_FILE_THREAD() ASSERT(CefCurrentlyOn(TID_FILE));




class CWebClient
  : public CefClient,  
    public CefDisplayHandler,  
    public CefLifeSpanHandler,  
    public CefLoadHandler,  
    public CefRequestHandler,  
    public CefContextMenuHandler,  
    public CefDownloadHandler ,
	public CefApp

{  
public:  
    CWebClient(const string& strUrl="");  
    virtual ~CWebClient();  
    //自定义方法  
    CefRefPtr<CefBrowser> GetBrowser() { return m_pBrowser; }  
    CefRefPtr<CefFrame>   GetMainFram() { return m_pBrowser.get()?m_pBrowser->GetMainFrame():NULL; }  
    HWND    GetBrowserHostWnd() { return m_pBrowser.get()?m_pBrowser->GetHost()->GetWindowHandle():NULL; }  
    void    SetHomePage(const string& strUrl) { m_strHomePage=strUrl; }  
    const string& GetHomePage()const { return m_strHomePage; }  
    string GetLoadingUrl();  
    void    Navigate(const string& strUrl);  
    void    CreateBrowser(HWND hParentWnd, const RECT& rect);  
    bool    IsClosing() const { return m_bIsClose; }  
  
  //凡是继承了的处理功能都在这里返回this指针  
    virtual CefRefPtr<CefDisplayHandler>      GetDisplayHandler()     { return this; }  
    virtual CefRefPtr<CefLifeSpanHandler>     GetLifeSpanHandler()    { return this; }  
    virtual CefRefPtr<CefLoadHandler>         GetLoadHandler()        { return this; }  
    virtual CefRefPtr<CefContextMenuHandler>  GetContextMenuHandler() { return this; }  
    virtual CefRefPtr<CefDownloadHandler>     GetDownloadHandler()    { return this; }  
  // CefDisplayHandler methods:  
  virtual void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title);  
  virtual void OnAddressChange(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& url);  
  virtual bool OnTooltip(CefRefPtr<CefBrowser> browser, CefString& text);  
  virtual void OnStatusMessage(CefRefPtr<CefBrowser> browser, const CefString& value);  
  
  // CefLifeSpanHandler methods:  
  virtual bool OnBeforePopup(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, 
      const CefString& target_url, const CefString& target_frame_name, const CefPopupFeatures& popupFeatures,   
      CefWindowInfo& windowInfo, CefRefPtr<CefClient>& client, CefBrowserSettings& settings,  
      bool* no_javascript_access);  
  virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser);  
  virtual bool DoClose(CefRefPtr<CefBrowser> browser);  
  virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser);  
  
  // CefLoadHandler methods:  
  virtual void OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame);  
  virtual void OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode);  
  virtual void OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl);  
  
  // Request that all existing browser windows close.  
  void CloseAllBrowsers(bool force_close);  
  //  
  virtual bool OnBeforeBrowse(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
      CefRefPtr<CefRequest> request, bool is_redirect)   
  {  

          //return true;  
          return false;  
  }  
  
  virtual bool OnBeforeResourceLoad(CefRefPtr<CefBrowser> browser,  
      CefRefPtr<CefFrame> frame,  
      CefRefPtr<CefRequest> request) {  
          return false;  
  }  
  //定义单线程处理
 virtual void OnBeforeCommandLineProcessing( const CefString& process_type,CefRefPtr<CefCommandLine> command_line)
{
	
	 command_line->AppendSwitch(CefString("process-per-site"));
 }
  //菜单处理  
  virtual void OnBeforeContextMenu(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,  
      CefRefPtr<CefContextMenuParams> params, CefRefPtr<CefMenuModel> model);  
  
  virtual bool OnContextMenuCommand(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,  
      CefRefPtr<CefContextMenuParams> params, int command_id, EventFlags event_flags);  
  
  //下载处理  
  virtual void OnBeforeDownload( CefRefPtr<CefBrowser> browser, CefRefPtr<CefDownloadItem> download_item,
      const CefString& suggested_name, CefRefPtr<CefBeforeDownloadCallback> callback);  
  
  virtual void OnDownloadUpdated( CefRefPtr<CefBrowser> browser, CefRefPtr<CefDownloadItem> download_item,  
      CefRefPtr<CefDownloadItemCallback> callback);  

private:  
    typedef std::list<CefRefPtr<CefBrowser> > BrowserList;  
    BrowserList browser_list_;  
    CefRefPtr<CefBrowser> m_pBrowser;  
    bool    m_bIsClose;  
    string m_strHomePage;  
    static int  m_nBrowserCount;  
	HWND m_hParent;
	// Include the default reference counting implementation.
	IMPLEMENT_REFCOUNTING(CWebClient);
	IMPLEMENT_LOCKING(CWebClient);

};