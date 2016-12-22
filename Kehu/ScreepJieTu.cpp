// ScreepJieTu.cpp : 实现文件
//

#include "stdafx.h"
#include "Kehu.h"
#include "ScreepJieTu.h"
#include "afxdialogex.h"
#include "TcpSocket.h"
#include "allvar.h"

extern CString DengjiPath;
// ScreepJieTu 对话框

IMPLEMENT_DYNAMIC(ScreepJieTu, CDialogEx)

ScreepJieTu::ScreepJieTu(CWnd* pParent /*=NULL*/)
	: CDialogEx(ScreepJieTu::IDD, pParent)
{
	isStart = false;  //初始化参数
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

	//把对化框设置成全屏顶层窗口
	//SetWindowPos(&wndTopMost, 0, 0, m_xScreen, m_yScreen, SWP_SHOWWINDOW);

	//修改窗口属性，不显示任务栏图标
	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);
	//将窗体设置为透明
	SetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE,
	GetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE) ^ WS_EX_LAYERED);
	jietutag=1;

	/*
	HINSTANCE hInst = LoadLibrary(L"User32.DLL"); //显式加载DLL
	if (hInst != NULL)
	{
		typedef BOOL(WINAPI *MYFUNC)(HWND, COLORREF, BYTE, DWORD);
		MYFUNC pFun = NULL;
		pFun = (MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes");//取得SetLayeredWindowAttributes函数指针
		//对于0x00000002 为设置为自定义的 0x00000001为完全透明
		COLORREF maskColor = RGB(244, 244, 244);	//要透明的颜色
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
	ON_BN_CLICKED(CS_BUTON, &ScreepJieTu::OnSC_Button)   //单击按钮
	ON_BN_CLICKED(CS_LBUTON, &ScreepJieTu::OnSCL_Button)   //单击按钮
END_MESSAGE_MAP()


// ScreepJieTu 消息处理程序



//void ScreepJieTu::OnMouseMove(UINT nFlags, CPoint point)
//{
//	HDC hdc;
//	HPEN	hPen;
//	// TODO:  在此添加消息处理程序代码和/或调用默认值
//	//当鼠标开始移动时，检测鼠标左键是否按下，若按下这开始截图
//	if (nFlags&MK_LBUTTON){  //鼠标移动，同时左键按下
//
//		if (isEnd == false){
//			
//			hdc =::GetDC(m_hWnd); 
//			SetROP2(hdc, R2_NOTXORPEN);   //需这句才能消除内部残影
//			hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));	//创建一个画笔
//			SelectObject(hdc, hPen);
//			SelectObject(hdc, GetStockObject(NULL_BRUSH));	//画刷 调用sdk
//
//			Rectangle(hdc, pointBegin.x, pointBegin.y, pointEnd.x, pointEnd.y);	//需这句才能消除外部残影,前提是有SetROP2
//			pointEnd.x = point.x;
//			pointEnd.y = point.y;
//			Rectangle(hdc, pointBegin.x, pointBegin.y, pointEnd.x, pointEnd.y);
//			//定型之后不妨获取当前的鼠标的位置
//
//			DeleteObject(hPen);   //删除画笔
//		    ::ReleaseDC(m_hWnd, hdc);	
//
//		}
//		isStart = true;
//	}
//
//	CDialogEx::OnMouseMove(nFlags, point);
//}

//指左键按下时
//void ScreepJieTu::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO:  在此添加消息处理程序代码和/或调用默认值
//	if (isStart == false)		//避免双击截图时重新获取坐标
//	{
//		pointBegin.x =point.x;	//矩形起点x
//		pointBegin.y =point.y;	//矩形起点y
//		pointEnd.x = point.x;
//		pointEnd.y = point.y;
//	}
//	CDialogEx::OnLButtonDown(nFlags, point);
//}

//点击右键时
//void ScreepJieTu::OnRButtonDown(UINT nFlags, CPoint point)
//{
//
//	// TODO:  在此添加消息处理程序代码和/或调用默认值
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
//	// TODO:  在此添加消息处理程序代码和/或调用默认值
//    if (isStart == true)			//有拖动才为true，说明矩形非空
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
//			//如果全屏的话
//			int iWidth = GetSystemMetrics(SM_CXSCREEN);
//			int iHeight = GetSystemMetrics(SM_CYSCREEN);
//			if (point.x + 80 > iWidth)
//				point.x -= 100;
//			if (point.y+30>iHeight)
//				point.y-=50;
//			st->Create(L"保存", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, rct, this, CS_BUTON);
//			stL->Create(L"取消", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, rct, this, CS_LBUTON);
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
//	// TODO:  在此添加消息处理程序代码和/或调用默认值
//	jietutag=0;
//	CDialogEx::OnMButtonDblClk(nFlags, point);
//}


void ScreepJieTu::OnDestroy()
{
	jietutag=0;
	CDialogEx::OnDestroy();

	// TODO:  在此处添加消息处理程序代码
}

//截取图片
//-------------
HBITMAP ScreepJieTu::CopyScreenToBitmap(LPRECT lpRect)
{

	HDC       hScrDC, hMemDC;               //屏幕和内存设备描述表
	HBITMAP   hBitmap, hOldBitmap;			//位图句柄
	int       nX, nY, nX2, nY2;				//选定区域坐标
	int       nWidth, nHeight;				//位图宽度和高度
	int       xScrn, yScrn;                 //屏幕分辨率

	//确保选定区域不为空矩形
	if (IsRectEmpty(lpRect))
		return NULL;

	//为屏幕创建设备描述表
	hScrDC = CreateDC(L"DISPLAY", NULL, NULL, NULL);

	//为屏幕设备描述表创建兼容的内存设备描述表
	hMemDC = CreateCompatibleDC(hScrDC);

	//获得选定区域坐标
	nX = lpRect->left;
	nY = lpRect->top;
	nX2 = lpRect->right;
	nY2 = lpRect->bottom;

	//获得屏幕分辨率
	xScrn = GetDeviceCaps(hScrDC, HORZRES);
	yScrn = GetDeviceCaps(hScrDC, VERTRES);
	//确保选定区域是可见的
	if (nX < 0) nX = 0;
	if (nY < 0) nY = 0;
	if (nX2 > xScrn) nX2 = xScrn;
	if (nY2 > yScrn) nY2 = yScrn;

	nWidth = nX2 - nX;
	nHeight = nY2 - nY;
	//创建一个与屏幕设备描述表兼容的位图
	hBitmap = CreateCompatibleBitmap(hScrDC, nWidth, nHeight);

	//把新位图选到内存设备描述表中
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
	
	//把屏幕设备描述表拷贝到内存设备描述表中
	BitBlt(hMemDC, 0, 0, nWidth, nHeight, hScrDC, nX, nY, SRCCOPY);
	
	//得到屏幕位图的句柄
	hBitmap = (HBITMAP)SelectObject(hMemDC, hOldBitmap);
	
	//清除
	DeleteDC(hScrDC);
	DeleteDC(hMemDC);

	//   返回位图句柄
	return   hBitmap;
}

//void ScreepJieTu::OnLButtonDblClk(UINT nFlags, CPoint point)
//{
//
//	
//	// TODO:  在此添加消息处理程序代码和/或调用默认值
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
//		//清空剪贴板
//		EmptyClipboard();
//
//		//把屏幕内容粘贴到剪贴板上
//		SetClipboardData(CF_BITMAP, hBitmap);
//		//关闭剪贴板
//		CloseClipboard();
//	}
//	::InvalidateRect(m_hWnd, NULL, TRUE);
//	isStart = false;
//	isEnd = false;
//	isjud = false;
//	OnOK();  // 退出
//	
//	//设置一个打开文件，设置保存路径窗口
//	CFileDialog dlg(FALSE, //TRUE为OPEN对话框，FALSE为SAVE AS对话框
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
//		DengjiPath = dlg.GetPathName(); //文件名保存在了FilePathName里
//	}
//	else return;
//
//	/*#############################################################*/
//	SaveBitmapToFile(hBitmap, DengjiPath);  //保存到相对路径下面
//
//	//CDialogEx::OnLButtonDblClk(nFlags, point);
//}


int ScreepJieTu::SaveBitmapToFile(HBITMAP hBitmap, LPCWSTR lpFileName) {



	//lpFileName 为位图文件名 
	HDC hDC;
	//设备描述表 
	int iBits;
	//当前显示分辨率下每个像素所占字节数 
	WORD wBitCount;
	//位图中每个像素所占字节数 
	//定义调色板大小， 位图中像素字节大小 ， 位图文件大小 ， 写入文件字节数 
	DWORD dwPaletteSize = 0, dwBmBitsSize, dwDIBSize, dwWritten;
	BITMAP Bitmap;
	//位图属性结构 
	BITMAPFILEHEADER bmfHdr;
	//位图文件头结构 
	BITMAPINFOHEADER bi;
	//位图信息头结构 
	LPBITMAPINFOHEADER lpbi;
	//指向位图信息头结构 
	HANDLE fh, hDib, hPal;
	HPALETTE hOldPal = NULL;
	//定义文件，分配内存句柄，调色板句柄 

	//计算位图文件每个像素所占字节数 
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
	//计算调色板大小 
	if (wBitCount <= 8)
		dwPaletteSize = (1 << wBitCount)*sizeof(RGBQUAD);

	//设置位图信息头结构 
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
	//为位图内容分配内存 
	/*xxxxxxxx计算位图大小分解一下(解释一下上面的语句)xxxxxxxxxxxxxxxxxxxx
	//每个扫描行所占的字节数应该为4的整数倍，具体算法为:
	1int biWidth = (Bitmap.bmWidth*wBitCount) / 32;
	if((Bitmap.bmWidth*wBitCount) % 32)
	biWidth++; //不是整数倍的加1
	biWidth *= 4;//到这里，计算得到的为每个扫描行的字节数。
	dwBmBitsSize = biWidth * Bitmap.bmHeight;//得到大小
	xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/

	hDib = GlobalAlloc(GHND, dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
	*lpbi = bi;
	// 处理调色板 
	hPal = GetStockObject(DEFAULT_PALETTE);
	if (hPal)
	{
		hDC = ::GetDC(NULL);
		hOldPal = SelectPalette(hDC, (HPALETTE)hPal, FALSE);
		RealizePalette(hDC);
	}

	// 获取该调色板下新的像素值 
	GetDIBits(hDC, hBitmap, 0, (UINT)Bitmap.bmHeight, (LPSTR)lpbi + sizeof(BITMAPINFOHEADER)+dwPaletteSize, (BITMAPINFO *)lpbi, DIB_RGB_COLORS);
	
	//恢复调色板
	if (hOldPal){
		SelectPalette(hDC, hOldPal, TRUE);
		RealizePalette(hDC);
		::ReleaseDC(NULL, hDC);
	}
	
	//创建位图文件 
	fh = CreateFile(lpFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (fh == INVALID_HANDLE_VALUE)
		return FALSE;
	
	// 设置位图文件头 
	bmfHdr.bfType = 0x4D42; // "BM" 
	dwDIBSize = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+dwPaletteSize + dwBmBitsSize;
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER)+(DWORD)sizeof(BITMAPINFOHEADER)+dwPaletteSize;
	
	// 写入位图文件头 
	WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
	
	// 写入位图文件其余内容 
	WriteFile(fh, (LPSTR)lpbi, sizeof(BITMAPINFOHEADER)+dwPaletteSize + dwBmBitsSize, &dwWritten, NULL);
    //清除 
	GlobalUnlock(hDib);
	GlobalFree(hDib);
	CloseHandle(fh);
	return TRUE;
}

void ScreepJieTu::CreateStretchImage(CImage *pImage,CImage *ResultImage,int StretchHeight,int StretchWidth)
{
    if(pImage->IsDIBSection())
{
          // 取得 pImage 的 DC
 CDC* pImageDC1 = CDC::FromHandle(pImage->GetDC()); // Image 因為有自己的 DC, 所以必須使用 FromHandle 取得對應的 DC


  
 CBitmap *bitmap1=pImageDC1->GetCurrentBitmap();
 BITMAP bmpInfo;
 bitmap1->GetBitmap(&bmpInfo);


 // 建立新的 CImage
 ResultImage->Create(StretchWidth,StretchHeight,bmpInfo.bmBitsPixel);
 CDC* ResultImageDC = CDC::FromHandle(ResultImage->GetDC());


 // 當 Destination 比較小的時候, 會根據 Destination DC 上的 Stretch Blt mode 決定是否要保留被刪除點的資訊
 ResultImageDC->SetStretchBltMode(HALFTONE); // 使用最高品質的方式
 ::SetBrushOrgEx(ResultImageDC->m_hDC,0,0,NULL); // 調整 Brush 的起點


 // 把 pImage 畫到 ResultImage 上面
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
	/*以时间和日期起名*/
	CallName();
	if (::OpenClipboard(m_hWnd))
	{
		//清空剪贴板
		EmptyClipboard();

		//把屏幕内容粘贴到剪贴板上
		SetClipboardData(CF_BITMAP, hBitmap);
		//关闭剪贴板
		CloseClipboard();
	}
	::InvalidateRect(m_hWnd, NULL, TRUE);
	isStart = false;
	isEnd = false;
	isjud = false;
	OnOK();  // 退出

	//设置一个打开文件，设置保存路径窗口
	CFileDialog dlg(FALSE, //TRUE为OPEN对话框，FALSE为SAVE AS对话框
		NULL,
		DengjiPath,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("BMP Files (*.bmp)|*.bmp\
					   |JPEG Files (*.jpeg)|*.jpeg\
					   |JPG Files (*.jpg)|*.jpg\
					   |All Files (*.*)|*.*||"), NULL);
	//dlg.SetWindowTextW(DengjiPath);
	if (dlg.DoModal() == IDOK){
	
		DengjiPath = dlg.GetPathName(); //文件名保存在了FilePathName里
		/*#############################################################*/

		/*检查文件格式是否正确，不正确修正*/
		//Cstring转为string
		CStringA tmp_Dnegj(DengjiPath.GetBuffer(0));
		string sdengj = tmp_Dnegj.GetBuffer(0);
		int pos=sdengj.find(".");
		if(pos!=std::string::npos)
			sdengj=sdengj.substr(0,pos);
			sdengj+=".jpg";
			SaveBitmapToFile(hBitmap, CString(sdengj.c_str()));  //保存到相对路径下面
		//m_strFile  文件路径
        CImage  wImg,sImg;
        wImg.Load(CString(sdengj.c_str()));
        CreateStretchImage(&wImg,&sImg,(wImg.GetHeight()/4)*3,(wImg.GetWidth()/4)*3);
        sImg.Save(CString(sdengj.c_str()));
		
	    //上传图片到服务器中、
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
	 closesocket(mytcp.sHost);	//关闭套接字
    WSACleanup();		//释放套接字资源
	 //MessageBoxA(0,recv_str,0,0);
	 //解析返回的图片
	 //采用json解压包
     Json::Value troot;
	 Json::Reader reader;
	 Json::FastWriter fast_writer;
	  string sst = strstr(recv_str, "{");
	 if (!reader.parse(sst, troot, false)) {
		 MessageBox(_T("朋友网地址不存在!\n"), 0, 0);
		 return  ;
	  }
	 	 // MessageBoxA(0,sst.c_str(),"sss",0);
	      string sst1 = strstr(sst.c_str(), "package");
	      sst1 = strstr(sst1.c_str(), "{");
	 	  //MessageBoxA(0,sst1.c_str(),"sss",0);
	  if (!reader.parse(sst1, troot, false)) {
		 MessageBox(_T("需要加载的页面地址不存在!\n"), 0, 0);
		 return  ;
	  }
	  //获取当前图片的路径
	    string  tmpScr = troot["picurl"].asString(); 
		//WebClient(tmpScr);
	*/

     jietutag=0;   //防止多次并行截图

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

		/*以时间和日期起名*/
	std::string scname="NULL";
	switch (this->dataType){
	case 1:{
		scans=sccnt[0];
		//scans=(sccnt[0])%3+1;
		scname="货比";
		}break;
	case 2:{
	   scname="浏览"; 
	   scans=sccnt[1];
	   //scans=(sccnt[1])%4 +1;
      }break;
    case 3: {
		 scans=(sccnt[2]+1)/2;
	    if(!tag)  {
			scname="收藏";
			 tag=1;
		}
	     else  {
		  scname="关注";
		  tag=0;
		 }
	 }break;
	case 4:{
	    scans=sccnt[3];
		// scans=(sccnt[3])%4+1;
	  scname="关联"; 
      }break;
	case 5: {
		//scans=1;
		  scans=sccnt[4];
		scname="聊天"; break;
	}
	case 6: {
		//scans=1;
		scans=sccnt[5];
		scname="已购列表"; 
	}break;
	case 7: {
		scans=sccnt[6];
		//scans=(sccnt[6])%6+1;
		scname="特殊"; 
	}break;
	default: scname="NULL"; break;
  }
	//显示年月日
	  
CTime time = CTime::GetCurrentTime(); ///构造CTime对象  
  
int _year = time.GetYear(); ///年  
  
int _month = time.GetMonth(); ///月  
  
int _day = time.GetDay(); ///日  
 
DengjiPath.Format(L"%s%d%d%d_%d.jpg",CString(scname.c_str()),_year,_month,_day,scans);

}

