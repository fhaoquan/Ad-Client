// ScreepJieTu.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Kehu.h"
#include "ScreepJieTu.h"
#include "afxdialogex.h"
#include "TcpSocket.h"
#include "allvar.h"

extern CString DengjiPath;
// ScreepJieTu �Ի���

IMPLEMENT_DYNAMIC(ScreepJieTu, CDialogEx)

ScreepJieTu::ScreepJieTu(CWnd* pParent /*=NULL*/)
	: CDialogEx(ScreepJieTu::IDD, pParent)
{
	isStart = false;  //��ʼ������
	isEnd = false;
	isjud = false;
	st = NULL;
	stL = NULL;
	tag=0;
	dataType=0;
	scans=0;
    jietutag=0;
	memset(sccnt,0,sizeof(sccnt));
    
}
	
BOOL ScreepJieTu::OnInitDialog()
{
	CDialog::OnInitDialog();

	//�ѶԻ������ó�ȫ�����㴰��
	//SetWindowPos(&wndTopMost, 0, 0, m_xScreen, m_yScreen, SWP_SHOWWINDOW);

	//�޸Ĵ������ԣ�����ʾ������ͼ��
	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);
	//����������Ϊ͸��
	SetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE,
	GetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE) ^ WS_EX_LAYERED);
	jietutag=1;

	/*
	HINSTANCE hInst = LoadLibrary(L"User32.DLL"); //��ʽ����DLL
	if (hInst != NULL)
	{
		typedef BOOL(WINAPI *MYFUNC)(HWND, COLORREF, BYTE, DWORD);
		MYFUNC pFun = NULL;
		pFun = (MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes");//ȡ��SetLayeredWindowAttributes����ָ��
		//����0x00000002 Ϊ����Ϊ�Զ���� 0x00000001Ϊ��ȫ͸��
		COLORREF maskColor = RGB(244, 244, 244);	//Ҫ͸������ɫ
		if (pFun != NULL)
			pFun(this->GetSafeHwnd(), maskColor,150, 0x00000002);
		
		FreeLibrary(hInst);
	}
	*/
	OnSC_Button();
	return TRUE;
}


ScreepJieTu::~ScreepJieTu()
{
	if(m_hWnd!=NULL)
		DestroyWindow();
}

void ScreepJieTu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ScreepJieTu, CDialogEx)
//	ON_WM_NCXBUTTONDBLCLK()
//	ON_WM_LBUTTONDBLCLK()
//	ON_WM_LBUTTONDOWN()
//	ON_WM_MOUSEMOVE()
//	ON_WM_LBUTTONDOWN()
//	ON_WM_RBUTTONDOWN()
//	ON_WM_LBUTTONUP()
//	ON_WM_MBUTTONDBLCLK()
	ON_WM_DESTROY()
//	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(CS_BUTON, &ScreepJieTu::OnSC_Button)   //������ť
	ON_BN_CLICKED(CS_LBUTON, &ScreepJieTu::OnSCL_Button)   //������ť
END_MESSAGE_MAP()


// ScreepJieTu ��Ϣ�������



//void ScreepJieTu::OnMouseMove(UINT nFlags, CPoint point)
//{
//	HDC hdc;
//	HPEN	hPen;
//	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	//����꿪ʼ�ƶ�ʱ������������Ƿ��£��������⿪ʼ��ͼ
//	if (nFlags&MK_LBUTTON){  //����ƶ���ͬʱ�������
//
//		if (isEnd == false){
//			
//			hdc =::GetDC(m_hWnd); 
//			SetROP2(hdc, R2_NOTXORPEN);   //�������������ڲ���Ӱ
//			hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));	//����һ������
//			SelectObject(hdc, hPen);
//			SelectObject(hdc, GetStockObject(NULL_BRUSH));	//��ˢ ����sdk
//
//			Rectangle(hdc, pointBegin.x, pointBegin.y, pointEnd.x, pointEnd.y);	//�������������ⲿ��Ӱ,ǰ������SetROP2
//			pointEnd.x = point.x;
//			pointEnd.y = point.y;
//			Rectangle(hdc, pointBegin.x, pointBegin.y, pointEnd.x, pointEnd.y);
//			//����֮�󲻷���ȡ��ǰ������λ��
//
//			DeleteObject(hPen);   //ɾ������
//		    ::ReleaseDC(m_hWnd, hdc);	
//
//		}
//		isStart = true;
//	}
//
//	CDialogEx::OnMouseMove(nFlags, point);
//}

//ָ�������ʱ
//void ScreepJieTu::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	if (isStart == false)		//����˫����ͼʱ���»�ȡ����
//	{
//		pointBegin.x =point.x;	//�������x
//		pointBegin.y =point.y;	//�������y
//		pointEnd.x = point.x;
//		pointEnd.y = point.y;
//	}
//	CDialogEx::OnLButtonDown(nFlags, point);
//}

//����Ҽ�ʱ
//void ScreepJieTu::OnRButtonDown(UINT nFlags, CPoint point)
//{
//
//	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	if (isStart == false){
//	   jietutag=0;
//		OnOK();
//	}
//	else
//	{	
//	   st->DestroyWindow();
//	   stL->DestroyWindow();
//	 // delete st;
//	 //delete stL;
//	  ::InvalidateRect(m_hWnd, NULL, TRUE);
//	   isStart = false;
//	   isEnd = false;
//	   isjud = false;
//
//	}
//	CDialogEx::OnRButtonDown(nFlags, point);
//}


//void ScreepJieTu::OnLButtonUp(UINT nFlags, CPoint point)
//{
//	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
//    if (isStart == true)			//���϶���Ϊtrue��˵�����ηǿ�
//	{
//		if (!isjud){
//			isjud = true;
//			if (st == NULL)  	st = new CButton();
//			if (stL == NULL)    stL = new CButton();
//			RECT rct;
//			rct.top = point.y;
//			rct.left = point.x;
//			rct.bottom = point.y + 10;
//			rct.right = point.x + 20;
//			//���ȫ���Ļ�
//			int iWidth = GetSystemMetrics(SM_CXSCREEN);
//			int iHeight = GetSystemMetrics(SM_CYSCREEN);
//			if (point.x + 80 > iWidth)
//				point.x -= 100;
//			if (point.y+30>iHeight)
//				point.y-=50;
//			st->Create(L"����", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, rct, this, CS_BUTON);
//			stL->Create(L"ȡ��", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, rct, this, CS_LBUTON);
//			st->SetWindowPos(NULL, point.x-78, point.y, 80, 30, 0);
//			stL->SetWindowPos(NULL, point.x - 170, point.y, 80, 30, 0);
//
//		}
//		isEnd = true;
//	
//	}
//	
//	CDialogEx::OnLButtonUp(nFlags, point);
//}


//void ScreepJieTu::OnMButtonDblClk(UINT nFlags, CPoint point)
//{
//	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	jietutag=0;
//	CDialogEx::OnMButtonDblClk(nFlags, point);
//}


void ScreepJieTu::OnDestroy()
{
	jietutag=0;
	CDialogEx::OnDestroy();

	// TODO:  �ڴ˴������Ϣ����������
}

//��ȡͼƬ
//-------------
HBITMAP ScreepJieTu::CopyScreenToBitmap(LPRECT lpRect)
{

	HDC       hScrDC, hMemDC;               //��Ļ���ڴ��豸������
	HBITMAP   hBitmap, hOldBitmap;			//λͼ���
	int       nX, nY, nX2, nY2;				//ѡ����������
	int       nWidth, nHeight;				//λͼ��Ⱥ͸߶�
	int       xScrn, yScrn;                 //��Ļ�ֱ���

	//ȷ��ѡ������Ϊ�վ���
	if (IsRectEmpty(lpRect))
		return NULL;

	//Ϊ��Ļ�����豸������
	hScrDC = CreateDC(L"DISPLAY", NULL, NULL, NULL);

	//Ϊ��Ļ�豸�����������ݵ��ڴ��豸������
	hMemDC = CreateCompatibleDC(hScrDC);

	//���ѡ����������
	nX = lpRect->left;
	nY = lpRect->top;
	nX2 = lpRect->right;
	nY2 = lpRect->bottom;

	//�����Ļ�ֱ���
	xScrn = GetDeviceCaps(hScrDC, HORZRES);
	yScrn = GetDeviceCaps(hScrDC, VERTRES);
	//ȷ��ѡ�������ǿɼ���
	if (nX < 0) nX = 0;
	if (nY < 0) nY = 0;
	if (nX2 > xScrn) nX2 = xScrn;
	if (nY2 > yScrn) nY2 = yScrn;

	nWidth = nX2 - nX;
	nHeight = nY2 - nY;
	//����һ������Ļ�豸��������ݵ�λͼ
	hBitmap = CreateCompatibleBitmap(hScrDC, nWidth, nHeight);

	//����λͼѡ���ڴ��豸��������
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
	
	//����Ļ�豸�����������ڴ��豸��������
	BitBlt(hMemDC, 0, 0, nWidth, nHeight, hScrDC, nX, nY, SRCCOPY);
	
	//�õ���Ļλͼ�ľ��
	hBitmap = (HBITMAP)SelectObject(hMemDC, hOldBitmap);
	
	//���
	DeleteDC(hScrDC);
	DeleteDC(hMemDC);

	//   ����λͼ���
	return   hBitmap;
}

//void ScreepJieTu::OnLButtonDblClk(UINT nFlags, CPoint point)
//{
//
//	
//	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	jietutag=0;
//	RECT rect;
//	rect.left = (pointBegin.x < pointEnd.x) ? pointBegin.x : pointEnd.x;
//	rect.top = (pointBegin.y < pointEnd.y) ? pointBegin.y : pointEnd.y;
//	rect.right = (pointEnd.x > pointBegin.x) ? pointEnd.x : pointBegin.x;
//	rect.bottom = (pointEnd.y > pointBegin.y) ? pointEnd.y : pointBegin.y;
//
//	HBITMAP	 hBitmap;
//	hBitmap = CopyScreenToBitmap(&rect);
//
//	 	CallName();
//	if (::OpenClipboard(m_hWnd))
//	{
//		//��ռ�����
//		EmptyClipboard();
//
//		//����Ļ����ճ������������
//		SetClipboardData(CF_BITMAP, hBitmap);
//		//�رռ�����
//		CloseClipboard();
//	}
//	::InvalidateRect(m_hWnd, NULL, TRUE);
//	isStart = false;
//	isEnd = false;
//	isjud = false;
//	OnOK();  // �˳�
//	
//	//����һ�����ļ������ñ���·������
//	CFileDialog dlg(FALSE, //TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
//		NULL,
//		DengjiPath,
//		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
//		(LPCTSTR)_TEXT("BMP Files (*.bmp)|*.bmp\
//					   |JPEG Files (*.jpeg)|*.jpeg\
//					   |JPG Files (*.jpg)|*.jpg\
//					   |All Files (*.*)|*.*||"), NULL);
//	//dlg.SetWindowTextW(DengjiPath);
//	if (dlg.DoModal() == IDOK){
//	
//		DengjiPath = dlg.GetPathName(); //�ļ�����������FilePathName��
//	}
//	else return;
//
//	/*#############################################################*/
//	SaveBitmapToFile(hBitmap, DengjiPath);  //���浽���·������
//
//	//CDialogEx::OnLButtonDblClk(nFlags, point);
//}


int ScreepJieTu::SaveBitmapToFile(HBITMAP hBitmap, LPCWSTR lpFileName) {



	//lpFileName Ϊλͼ�ļ��� 
	HDC hDC;
	//�豸������ 
	int iBits;
	//��ǰ��ʾ�ֱ�����ÿ��������ռ�ֽ��� 
	WORD wBitCount;
	//λͼ��ÿ��������ռ�ֽ��� 
	//�����ɫ���С�� λͼ�������ֽڴ�С �� λͼ�ļ���С �� д���ļ��ֽ��� 
	DWORD dwPaletteSize = 0, dwBmBitsSize, dwDIBSize, dwWritten;
	BITMAP Bitmap;
	//λͼ���Խṹ 
	BITMAPFILEHEADER bmfHdr;
	//λͼ�ļ�ͷ�ṹ 
	BITMAPINFOHEADER bi;
	//λͼ��Ϣͷ�ṹ 
	LPBITMAPINFOHEADER lpbi;
	//ָ��λͼ��Ϣͷ�ṹ 
	HANDLE fh, hDib, hPal;
	HPALETTE hOldPal = NULL;
	//�����ļ��������ڴ�������ɫ���� 

	//����λͼ�ļ�ÿ��������ռ�ֽ��� 
	hDC = CreateDC(L"DISPLAY", NULL, NULL, NULL);
	iBits = GetDeviceCaps(hDC, BITSPIXEL) *
		GetDeviceCaps(hDC, PLANES);
	DeleteDC(hDC);
	if (iBits <= 1)
		wBitCount = 1;
	else if (iBits <= 4)
		wBitCount = 4;
	else if (iBits <= 8)
		wBitCount = 8;
	else if (iBits <= 24)
		wBitCount = 24;
	else
		wBitCount = 32;
	//�����ɫ���С 
	if (wBitCount <= 8)
		dwPaletteSize = (1 << wBitCount)*sizeof(RGBQUAD);

	//����λͼ��Ϣͷ�ṹ 
	GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&Bitmap);
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = Bitmap.bmWidth;
	bi.biHeight = Bitmap.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = wBitCount;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	dwBmBitsSize = ((Bitmap.bmWidth*wBitCount + 31) / 32) * 4 * Bitmap.bmHeight;
	//Ϊλͼ���ݷ����ڴ� 
	/*xxxxxxxx����λͼ��С�ֽ�һ��(����һ����������)xxxxxxxxxxxxxxxxxxxx
	//ÿ��ɨ������ռ���ֽ���Ӧ��Ϊ4���������������㷨Ϊ:
	1int biWidth = (Bitmap.bmWidth*wBitCount) / 32;
	if((Bitmap.bmWidth*wBitCount) % 32)
	biWidth++; //�����������ļ�1
	biWidth *= 4;//���������õ���Ϊÿ��ɨ���е��ֽ�����
	dwBmBitsSize = biWidth * Bitmap.bmHeight;//�õ���С
	xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/

	hDib = GlobalAlloc(GHND, dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
	*lpbi = bi;
	// �����ɫ�� 
	hPal = GetStockObject(DEFAULT_PALETTE);
	if (hPal)
	{
		hDC = ::GetDC(NULL);
		hOldPal = SelectPalette(hDC, (HPALETTE)hPal, FALSE);
		RealizePalette(hDC);
	}

	// ��ȡ�õ�ɫ�����µ�����ֵ 
	GetDIBits(hDC, hBitmap, 0, (UINT)Bitmap.bmHeight, (LPSTR)lpbi + sizeof(BITMAPINFOHEADER)+dwPaletteSize, (BITMAPINFO *)lpbi, DIB_RGB_COLORS);
	
	//�ָ���ɫ��
	if (hOldPal){
		SelectPalette(hDC, hOldPal, TRUE);
		RealizePalette(hDC);
		::ReleaseDC(NULL, hDC);
	}
	
	//����λͼ�ļ� 
	fh = CreateFile(lpFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (fh == INVALID_HANDLE_VALUE)
		return FALSE;
	
	// ����λͼ�ļ�ͷ 
	bmfHdr.bfType = 0x4D42; // "BM" 
	dwDIBSize = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+dwPaletteSize + dwBmBitsSize;
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER)+(DWORD)sizeof(BITMAPINFOHEADER)+dwPaletteSize;
	
	// д��λͼ�ļ�ͷ 
	WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
	
	// д��λͼ�ļ��������� 
	WriteFile(fh, (LPSTR)lpbi, sizeof(BITMAPINFOHEADER)+dwPaletteSize + dwBmBitsSize, &dwWritten, NULL);
    //��� 
	GlobalUnlock(hDib);
	GlobalFree(hDib);
	CloseHandle(fh);
	return TRUE;
}

void ScreepJieTu::CreateStretchImage(CImage *pImage,CImage *ResultImage,int StretchHeight,int StretchWidth)
{
    if(pImage->IsDIBSection())
{
          // ȡ�� pImage �� DC
 CDC* pImageDC1 = CDC::FromHandle(pImage->GetDC()); // Image ������Լ��� DC, ���Ա��ʹ�� FromHandle ȡ�Ì����� DC


  
 CBitmap *bitmap1=pImageDC1->GetCurrentBitmap();
 BITMAP bmpInfo;
 bitmap1->GetBitmap(&bmpInfo);


 // �����µ� CImage
 ResultImage->Create(StretchWidth,StretchHeight,bmpInfo.bmBitsPixel);
 CDC* ResultImageDC = CDC::FromHandle(ResultImage->GetDC());


 // �� Destination ���^С�ĕr��, ������ Destination DC �ϵ� Stretch Blt mode �Q���Ƿ�Ҫ�������h���c���YӍ
 ResultImageDC->SetStretchBltMode(HALFTONE); // ʹ�����Ʒ�|�ķ�ʽ
 ::SetBrushOrgEx(ResultImageDC->m_hDC,0,0,NULL); // �{�� Brush �����c


 // �� pImage ���� ResultImage ����
 StretchBlt(*ResultImageDC,0,0,StretchWidth,StretchHeight,*pImageDC1,0,0,pImage->GetWidth(),pImage->GetHeight(),SRCCOPY);
 // pImage->Draw(*ResultImageDC,0,0,StretchWidth,StretchHeight,0,0,pImage->GetWidth(),pImage->GetHeight());
 pImage->ReleaseDC();
 ResultImage->ReleaseDC();
   }
}


void ScreepJieTu::WebClient(const string  str){

	if(client.get()){
	CefRefPtr<CefBrowser> browser = client->GetBrowser();
    CefRefPtr<CefFrame> frame = browser->GetMainFrame();
    frame->ExecuteJavaScript("flashReturn1('upload_complete',"+str+");",
    frame->GetURL(), 0);
	}
}

void ScreepJieTu::OnSC_Button(){

	RECT rect;
	::GetWindowRect (::GetDesktopWindow(),&rect);
	//rect.left = (pointBegin.x < pointEnd.x) ? pointBegin.x : pointEnd.x;
	//rect.top = (pointBegin.y < pointEnd.y) ? pointBegin.y : pointEnd.y;
	//rect.right = (pointEnd.x > pointBegin.x) ? pointEnd.x : pointBegin.x;
	//rect.bottom = (pointEnd.y > pointBegin.y) ? pointEnd.y : pointBegin.y;

	HBITMAP	 hBitmap;
	hBitmap = CopyScreenToBitmap(&rect);
	/*��ʱ�����������*/
	CallName();
	if (::OpenClipboard(m_hWnd))
	{
		//��ռ�����
		EmptyClipboard();

		//����Ļ����ճ������������
		SetClipboardData(CF_BITMAP, hBitmap);
		//�رռ�����
		CloseClipboard();
	}
	::InvalidateRect(m_hWnd, NULL, TRUE);
	isStart = false;
	isEnd = false;
	isjud = false;
	OnOK();  // �˳�

	//����һ�����ļ������ñ���·������
	CFileDialog dlg(FALSE, //TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
		NULL,
		DengjiPath,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("BMP Files (*.bmp)|*.bmp\
					   |JPEG Files (*.jpeg)|*.jpeg\
					   |JPG Files (*.jpg)|*.jpg\
					   |All Files (*.*)|*.*||"), NULL);
	//dlg.SetWindowTextW(DengjiPath);
	if (dlg.DoModal() == IDOK){
	
		DengjiPath = dlg.GetPathName(); //�ļ�����������FilePathName��
		/*#############################################################*/

		/*����ļ���ʽ�Ƿ���ȷ������ȷ����*/
		//CstringתΪstring
		CStringA tmp_Dnegj(DengjiPath.GetBuffer(0));
		string sdengj = tmp_Dnegj.GetBuffer(0);
		int pos=sdengj.find(".");
		if(pos!=std::string::npos)
			sdengj=sdengj.substr(0,pos);
			sdengj+=".jpg";
			SaveBitmapToFile(hBitmap, CString(sdengj.c_str()));  //���浽���·������
		//m_strFile  �ļ�·��
        CImage  wImg,sImg;
        wImg.Load(CString(sdengj.c_str()));
        CreateStretchImage(&wImg,&sImg,(wImg.GetHeight()/4)*3,(wImg.GetWidth()/4)*3);
        sImg.Save(CString(sdengj.c_str()));
		
	    //�ϴ�ͼƬ���������С�
		/*
		mytcp.SocketStart();
		char* Scraddr = static_cast<char *>("http://friend.py91178.com/friendx/task/up_img"); 
		char* Scrhost = const_cast<char *>(hostaddr);		
		CStringA  ScrPath(DengjiPath.GetBuffer(0)); 

	    mytcp.sendPic(Scraddr,Scrhost,const_cast<char *>((string(ScrPath.GetBuffer(0))).c_str()),const_cast<char *>(SessinID.c_str()),80);
		char recv_str[4096] = { 0 };
	 if (recv(mytcp.sHost, recv_str, sizeof(recv_str), 0) == -1){
		 // cout << "recv failed" << endl;
		 MessageBox(_T("recv nothings !"), 0, 0);
		 return;
	  }
	 closesocket(mytcp.sHost);	//�ر��׽���
    WSACleanup();		//�ͷ��׽�����Դ
	 //MessageBoxA(0,recv_str,0,0);
	 //�������ص�ͼƬ
	 //����json��ѹ��
     Json::Value troot;
	 Json::Reader reader;
	 Json::FastWriter fast_writer;
	  string sst = strstr(recv_str, "{");
	 if (!reader.parse(sst, troot, false)) {
		 MessageBox(_T("��������ַ������!\n"), 0, 0);
		 return  ;
	  }
	 	 // MessageBoxA(0,sst.c_str(),"sss",0);
	      string sst1 = strstr(sst.c_str(), "package");
	      sst1 = strstr(sst1.c_str(), "{");
	 	  //MessageBoxA(0,sst1.c_str(),"sss",0);
	  if (!reader.parse(sst1, troot, false)) {
		 MessageBox(_T("��Ҫ���ص�ҳ���ַ������!\n"), 0, 0);
		 return  ;
	  }
	  //��ȡ��ǰͼƬ��·��
	    string  tmpScr = troot["picurl"].asString(); 
		//WebClient(tmpScr);
	*/

     jietutag=0;   //��ֹ��β��н�ͼ

	 switch (this->dataType){
		case 1:    sccnt[0]++; break;
		case 2:    sccnt[1]++; break;
		case 3:    sccnt[2]++; break;
	    case 4:    sccnt[3]++; break;
		case 5:    sccnt[4]++; break;
		case 6:    sccnt[5]++; break;
		case 7:    sccnt[6]++; break;
		default:    	break;   
	 }
	}
	else 
		return;
}

void ScreepJieTu::OnSCL_Button(){


	if(st!=NULL){
	st->DestroyWindow();
	st = NULL;
	}
	if(stL){
	stL->DestroyWindow();
	stL = NULL;
	}
	//delete st;
	::InvalidateRect(m_hWnd, NULL, TRUE);
	isStart = false;
	isEnd = false;
	isjud = false;
}

void ScreepJieTu::CallName(){

		/*��ʱ�����������*/
	std::string scname="NULL";
	switch (this->dataType){
	case 1:{
		scans=sccnt[0];
		//scans=(sccnt[0])%3+1;
		scname="����";
		}break;
	case 2:{
	   scname="���"; 
	   scans=sccnt[1];
	   //scans=(sccnt[1])%4 +1;
      }break;
    case 3: {
		 scans=(sccnt[2]+1)/2;
	    if(!tag)  {
			scname="�ղ�";
			 tag=1;
		}
	     else  {
		  scname="��ע";
		  tag=0;
		 }
	 }break;
	case 4:{
	    scans=sccnt[3];
		// scans=(sccnt[3])%4+1;
	  scname="����"; 
      }break;
	case 5: {
		//scans=1;
		  scans=sccnt[4];
		scname="����"; break;
	}
	case 6: {
		//scans=1;
		scans=sccnt[5];
		scname="�ѹ��б�"; 
	}break;
	case 7: {
		scans=sccnt[6];
		//scans=(sccnt[6])%6+1;
		scname="����"; 
	}break;
	default: scname="NULL"; break;
  }
	//��ʾ������
	  
CTime time = CTime::GetCurrentTime(); ///����CTime����  
  
int _year = time.GetYear(); ///��  
  
int _month = time.GetMonth(); ///��  
  
int _day = time.GetDay(); ///��  
 
DengjiPath.Format(L"%s%d%d%d_%d.jpg",CString(scname.c_str()),_year,_month,_day,scans);

}

