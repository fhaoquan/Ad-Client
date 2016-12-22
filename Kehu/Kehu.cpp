
// Kehu.cpp : 定義應用程式的類別行為。
//

#include "stdafx.h"
#include "Kehu.h"
#include "KehuDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CKehuApp
BEGIN_MESSAGE_MAP(CKehuApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

// CKehuApp 建構

CKehuApp::CKehuApp()
{
	// 支援重新啟動管理員
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO:  在此加入建構程式碼，
	// 將所有重要的初始設定加入 InitInstance 中
}


// 僅有的一個 CKehuApp 物件

CKehuApp theApp;




BOOL CKehuApp::InitInstance()
{
	// 假如應用程式資訊清單指定使用 ComCtl32.dll 6 (含) 以後版本，
	// 來啟動視覺化樣式，在 Windows XP 上，則需要 InitCommonControls()。
	// 否則任何視窗的建立都將失敗。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 設定要包含所有您想要用於應用程式中的
	// 通用控制項類別。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();
	
	  hMutex[1]=::CreateMutex(NULL, TRUE,L"Pyouteam1");//FirstName可以随便取一个唯一的名字
	  if (hMutex[1] != NULL)
	  {
		  if (GetLastError() == ERROR_ALREADY_EXISTS)
		  {
			  hMutex[2]=::CreateMutex(NULL, TRUE,L"Pyouteam2");//FirstName可以随便取一个唯一的名字
			  if (hMutex[2] != NULL)
			  {
				  if (GetLastError() == ERROR_ALREADY_EXISTS)
				  {
					  hMutex[3]=::CreateMutex(NULL, TRUE,L"Pyouteam3");//FirstName可以随便取一个唯一的名字
				  }
			  }
		  }
	  }
	if (hMutex[1] != NULL&&hMutex[2] != NULL&&hMutex[3] != NULL)
	{
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{	
		   //MessageBox(NULL,L"程序已经运行",0,0);	
		CWnd* cwnd=CWnd::FindWindow(NULL,L"朋友赚");//windowname为你的主窗体的标题,当然你也可以通过进程来找到主窗体。
		if (cwnd)//显示原先的主界面
		{
			//MessageBox(NULL,L"程序已经运行",0,0);
			cwnd->ShowWindow(SW_SHOWNORMAL);
            cwnd->SetForegroundWindow();
          }
          return FALSE;;
		}
		  /*	
			CWnd *pWndPrev,*pWndChild;
				pWndPrev = CWnd::FindWindow(NULL,L"朋友团");
			if(NULL!=pWndPrev){
				CKehuDlg *atmp=NULL;
				atmp= (CKehuDlg *)FromHandle(pWndPrev->m_hWnd);
				if(atmp!=NULL)
				atmp->Mmdlg->ShowWindow(SW_SHOW);
				return FALSE;
		   }
		  */
	
			//CloseHandle(hMutex);
			//hMutex=NULL;
			//依据名称打开进程
			//DestroyWindow();  //销毁程序
		    //return FALSE;
	}
	// 標準初始設定
	// 如果您不使用這些功能並且想減少
	// 最後完成的可執行檔大小，您可以
	// 從下列程式碼移除不需要的初始化常式，
	// 變更儲存設定值的登錄機碼
	// TODO:  您應該適度修改此字串
	// (例如，公司名稱或組織名稱)
 
	SetRegistryKey(_T("龚细军和他的小伙伴开发公司"));
  //存储在文件中init.log中，需要文件操作
	 //CreateDirectory(L".\\Kehu",NULL);
	FILE * fp =fopen("C:\\Kehu\\init.log","r+");
	if(fp==NULL){
		 CreateDirectory(L"C:\\Kehu",NULL);
	    fp= fopen("C:\\Kehu\\init.log","wb+");
	}

	if(fp!=NULL&&fread(&Kehutmp,sizeof(Regist),1,fp)!=1){
	  //说明没有注册
		strcpy(Kehutmp.name,"register");
		strcpy(Kehutmp.status,"yes");
		Kehutmp.data =1;    //默认是将窗口置于顶端用1表示
		fwrite(&Kehutmp,sizeof(Regist),1,fp);
	}
	if(fp!=NULL)
		fclose(fp);
	CKehuDlg dlg;
	m_pMainWnd = &dlg;
	/*
	dlg.Create(IDD_KEHU_DIALOG);
	dlg.ShowWindow(SW_HIDE);
	*/

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK){
		// TODO:  在此放置於使用 [確定] 來停止使用對話方塊時
		// 處理的程式碼
	}
	else if (nResponse == IDCANCEL){
		// TODO:  在此放置於使用 [取消] 來停止使用對話方塊時
		// 處理的程式碼
	}
	else if (nResponse == -1){
		TRACE(traceAppMsg, 0 ,"警告: 對話方塊建立失敗，因此，應用程式意外終止。\n");
	}
	// 因為已經關閉對話方塊，傳回 FALSE，所以我們會結束應用程式，
	// 而非提示開始應用程式的訊息。
  
	return FALSE;
}


