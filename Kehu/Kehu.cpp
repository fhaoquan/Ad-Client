
// Kehu.cpp : ���x���ó�ʽ��e�О顣
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

// CKehuApp ����

CKehuApp::CKehuApp()
{
	// ֧Ԯ�����ӹ���T
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO:  �ڴ˼��뽨����ʽ�a��
	// ��������Ҫ�ĳ�ʼ�O������ InitInstance ��
}


// �H�е�һ�� CKehuApp ���

CKehuApp theApp;




BOOL CKehuApp::InitInstance()
{
	// ���瑪�ó�ʽ�YӍ���ָ��ʹ�� ComCtl32.dll 6 (��) ����汾��
	// �톢��ҕ�X����ʽ���� Windows XP �ϣ��t��Ҫ InitCommonControls()��
	// ��t�κ�ҕ���Ľ�������ʧ����
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// �O��Ҫ������������Ҫ��춑��ó�ʽ�е�
	// ͨ�ÿ����e��
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();
	
	  hMutex[1]=::CreateMutex(NULL, TRUE,L"Pyouteam1");//FirstName�������ȡһ��Ψһ������
	  if (hMutex[1] != NULL)
	  {
		  if (GetLastError() == ERROR_ALREADY_EXISTS)
		  {
			  hMutex[2]=::CreateMutex(NULL, TRUE,L"Pyouteam2");//FirstName�������ȡһ��Ψһ������
			  if (hMutex[2] != NULL)
			  {
				  if (GetLastError() == ERROR_ALREADY_EXISTS)
				  {
					  hMutex[3]=::CreateMutex(NULL, TRUE,L"Pyouteam3");//FirstName�������ȡһ��Ψһ������
				  }
			  }
		  }
	  }
	if (hMutex[1] != NULL&&hMutex[2] != NULL&&hMutex[3] != NULL)
	{
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{	
		   //MessageBox(NULL,L"�����Ѿ�����",0,0);	
		CWnd* cwnd=CWnd::FindWindow(NULL,L"����׬");//windownameΪ���������ı���,��Ȼ��Ҳ����ͨ���������ҵ������塣
		if (cwnd)//��ʾԭ�ȵ�������
		{
			//MessageBox(NULL,L"�����Ѿ�����",0,0);
			cwnd->ShowWindow(SW_SHOWNORMAL);
            cwnd->SetForegroundWindow();
          }
          return FALSE;;
		}
		  /*	
			CWnd *pWndPrev,*pWndChild;
				pWndPrev = CWnd::FindWindow(NULL,L"������");
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
			//�������ƴ򿪽���
			//DestroyWindow();  //���ٳ���
		    //return FALSE;
	}
	// �˜ʳ�ʼ�O��
	// �������ʹ���@Щ���܁K����p��
	// ������ɵĿɈ��Йn��С��������
	// �����г�ʽ�a�Ƴ�����Ҫ�ĳ�ʼ����ʽ��
	// ׃�������O��ֵ�ĵ�䛙C�a
	// TODO:  ����ԓ�m���޸Ĵ��ִ�
	// (���磬��˾���Q��M�����Q)
 
	SetRegistryKey(_T("��ϸ��������С��鿪����˾"));
  //�洢���ļ���init.log�У���Ҫ�ļ�����
	 //CreateDirectory(L".\\Kehu",NULL);
	FILE * fp =fopen("C:\\Kehu\\init.log","r+");
	if(fp==NULL){
		 CreateDirectory(L"C:\\Kehu",NULL);
	    fp= fopen("C:\\Kehu\\init.log","wb+");
	}

	if(fp!=NULL&&fread(&Kehutmp,sizeof(Regist),1,fp)!=1){
	  //˵��û��ע��
		strcpy(Kehutmp.name,"register");
		strcpy(Kehutmp.status,"yes");
		Kehutmp.data =1;    //Ĭ���ǽ��������ڶ�����1��ʾ
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
		// TODO:  �ڴ˷����ʹ�� [�_��] ��ֹͣʹ�Ì�Ԓ���K�r
		// ̎��ĳ�ʽ�a
	}
	else if (nResponse == IDCANCEL){
		// TODO:  �ڴ˷����ʹ�� [ȡ��] ��ֹͣʹ�Ì�Ԓ���K�r
		// ̎��ĳ�ʽ�a
	}
	else if (nResponse == -1){
		TRACE(traceAppMsg, 0 ,"����: ��Ԓ���K����ʧ������ˣ����ó�ʽ����Kֹ��\n");
	}
	// ����ѽ��P�]��Ԓ���K������ FALSE�������҂����Y�����ó�ʽ��
	// ������ʾ�_ʼ���ó�ʽ��ӍϢ��
  
	return FALSE;
}


