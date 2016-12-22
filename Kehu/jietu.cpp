// jietu.cpp : implementation file
//

#include "stdafx.h"
#include "Kehu.h"
#include "jietu.h"
#include "afxdialogex.h"



// jietu dialog

IMPLEMENT_DYNAMIC(jietu, CDialogEx)

jietu::jietu(CWnd* pParent /*=NULL*/)
	: CDialogEx(jietu::IDD, pParent)
{

	//设置橡皮类的样式
	ct.m_nStyle = CMyTracker::resizeInside | CMyTracker::solidLine;
	ct.m_nHandleSize = 6;
	ct.m_rect.SetRect(-1, -1, -1, -1);  //左上角，右下角
		//初始化像皮筋类,新增的resizeMiddle 类型
	   //设置矩形颜色
	ct.SetRectColor(RGB(10, 100, 130));
	  //设置矩形调整时光标,默认的太小了,弄了个大点的
    ct.SetResizeCursor(IDC_CURSOR6, IDC_CURSOR5, IDC_CURSOR4, IDC_CURSOR3, IDC_CURSOR2);
	m_hCursor = AfxGetApp()->LoadCursor(IDC_CURSOR1);
	//获取屏幕分辩率
	 m_xScreen = GetSystemMetrics(SM_CXSCREEN);
	 m_yScreen = GetSystemMetrics(SM_CYSCREEN);
	//截取屏幕到位图中
	CRect rect(0, 0, m_xScreen, m_yScreen);
	//CBitmap * m_pBitmap = CBitmap::FromHandle(CopyScreenToBitmap(&rect));
}

jietu::~jietu()
{
	

}

//重载初始化函数
BOOL jietu::OnInitDialog(){
	CDialog::OnInitDialog();

	OnStnClickedJietu();
	return TRUE;
}

void jietu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
		//	DDX_Control(pDX, IDC_JIETU, m_jietu);
		DDX_Control(pDX, IDC_JIETU, m_jietu);
		DDX_Control(pDX, IDC_pSHow, m_tushow);
}


BEGIN_MESSAGE_MAP(jietu, CDialogEx)
//ON_STN_CLICKED(IDC_JIETU, &jietu::OnStnClickedJietu)
ON_BN_CLICKED(IDOK, &jietu::OnBnClickedOk)
ON_BN_CLICKED(IDCANCEL, &jietu::OnBnClickedCancel)
ON_STN_CLICKED(IDC_JIETU, &jietu::OnStnClickedJietu)
ON_STN_CLICKED(IDC_pSHow, &jietu::OnStnClickedpshow)
ON_WM_SETCURSOR()
ON_WM_LBUTTONDOWN()
ON_WM_PAINT()
ON_WM_LBUTTONUP()
//ON_WM_LBUTTONDBLCLK()
ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// jietu message handlers
void jietu::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//Resour = tmsrc;
    CDialogEx::OnOK();
}

void jietu::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}



void jietu::OnStnClickedJietu()
{
	// TODO: Add your control notification handler code here
	//可以加载各种类型的图片

	image.Load(photoPath); // 加载一幅png图片

	//image.SetPixel(26,26,NULL);
	//m_jietu.ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
	//设置静态控件显示位图 /
//	HBITMAP bmp = image.Detach();
//	m_jietu.SetBitmap(bmp);
	float xScale;
	float yScale;
	CRect rect, rect1;
	int height = image.GetHeight();
	int width =  image.GetWidth();
 	m_jietu.GetClientRect(&rect); //获得pictrue控件所在的矩形区域
	if (width > rect.Width() || height > rect.Width()) //小图片，不缩放
	{
		 xScale = (float)rect.Width() / (float)width;
	     yScale = (float)rect.Height() / (float)height;
		 float ScaleIndex = (xScale >= yScale?xScale:yScale);
		 width = (int)width*ScaleIndex;
		 height = (int)height*ScaleIndex;
	}
	CDC *pDc = m_jietu.GetDC();//获得pictrue控件的Dc
	ct.Draw(pDc);
	//SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);
	dimage.Create(width, height,24);
	 rect1 = CRect(rect.TopLeft(), CSize(width, height));
	HDC hdc = dimage.GetDC();
	SetStretchBltMode(hdc, STRETCH_HALFTONE);
	image.StretchBlt(hdc, rect1, SRCCOPY);
	dimage.ReleaseDC();
	HBITMAP bmp = dimage.Detach();
	m_jietu.SetBitmap(bmp);	

}


void jietu::OnStnClickedpshow()
{
	// TODO: Add your control notification handler code here
}


BOOL jietu::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)

{
	// TODO: Add your message handler code here and/or call default
	if (pWnd == this &&ct.SetCursor(pWnd , nHitTest)) {
		return TRUE;
	}

	return FALSE;
	//return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}



void jietu::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (ct.HitTest(point) < 0) 
		//开始画选择框
		ct.TrackRubberBand(this,point,TRUE);
	else 
		//点击矩形选择框
		ct.Track(this, point ,TRUE);
	    ct.m_rect.NormalizeRect();
	    //Invalidate(); //刷星窗口
					  //截图操作
		CRect  rect2,rect3;
	//	ct.m_rect.Height();
		ct.GetTrueRect(rect2);
	//	m_tushow.GetClientRect(&rect);
	//	POINT re = rect2.TopLeft();
	//	rect3 = CRect(rect.TopLeft(), CSize(rect2.Width(), rect2.Height()));
		//rect5 = CRect(rect3.TopLeft(), CSize(rect2.Width(), rect2.Height()));
		HBITMAP abmp = CopyScreenToBitmap(rect2);
		 //m_tushow.SetBitmap(abmp);

		 CImage tmpimg;
		 tmpimg.Attach(abmp);
		 float xScale;
		 float yScale;
		 CRect rect, rect1;
		 int height = tmpimg.GetHeight();
		 int width = tmpimg.GetWidth();
		 m_tushow.GetClientRect(&rect); //获得pictrue控件所在的矩形区域
		 if (width > rect.Width() || height > rect.Width()) //小图片，不缩放
		 {
			 xScale = (float)rect.Width() / (float)width;
			 yScale = (float)rect.Height() / (float)height;
			 float ScaleIndex = (xScale >= yScale ? xScale : yScale);
			 width = (int)width*ScaleIndex;
			 height = (int)height*ScaleIndex;
		 }
		 CDC *pDc = m_tushow.GetDC();//获得pictrue控件的Dc
		 //SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);
		 tmsrc.Create(width, height, 24);
		 rect1 = CRect(rect.TopLeft(), CSize(width, height));
		 HDC hdc = tmsrc.GetDC();
		 SetStretchBltMode(hdc, STRETCH_HALFTONE);
		 tmpimg.StretchBlt(hdc, rect1, SRCCOPY);
		 Resour = tmsrc; 
		 tmsrc.ReleaseDC();
		 m_sav_bmp  = tmsrc.Detach();
		// Touxiang.Attach(bmp);
		 m_tushow.SetBitmap(m_sav_bmp);
		 SaveBitmapToFile(m_sav_bmp, lpFilepath);  //将相片保存到相对路径下

		 //MessageBox(lpFilepath);
		return;
	//CDialogEx::OnLButtonDown(nFlags, point);
}


void jietu::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CDialogEx::OnPaint() for painting messages
	
}

HBITMAP jietu::CopyScreenToBitmap(LPRECT lpRect )
{

	HDC hScrDC, hMemDC;
	// 屏幕和内存设备描述表 
	HBITMAP hBitmap, hOldBitmap;
	// 位图句柄 
	int nX, nY, nX2, nY2;
	// 选定区域坐标 
	int nWidth, nHeight;
	// 位图宽度和高度 
	int xScrn, yScrn;
	// 屏幕分辨率 
	// 确保选定区域不为空矩形 
	if (IsRectEmpty(lpRect))
		return NULL;
	//为屏幕创建设备描述表 
//	CDC * dc = m_jietu.GetDC();
	hScrDC =CreateDC(L"DISPLAY", NULL, NULL, NULL);
	//为屏幕设备描述表创建兼容的内存设备描述表 
	hMemDC = CreateCompatibleDC(hScrDC);
	// 获得选定区域坐标 
	nX = lpRect->left;
	nY = lpRect->top;
	nX2 = lpRect->right;
	nY2 = lpRect->bottom;
	// 获得屏幕分辨率 
	xScrn = GetDeviceCaps(hScrDC, HORZRES);
	yScrn = GetDeviceCaps(hScrDC, VERTRES);
	//确保选定区域是可见的 
	if (nX < 0)
		nX = 0;
	if (nY < 0)
		nY = 0;
	if (nX2 > xScrn)
		nX2 = xScrn;
	if (nY2 > yScrn)
		nY2 = yScrn;
	nWidth = nX2 - nX;
	nHeight = nY2 - nY;
	// 创建一个与屏幕设备描述表兼容的位图 
	hBitmap = CreateCompatibleBitmap(hScrDC, nWidth, nHeight);
	// 把新位图选到内存设备描述表中 
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
	// 把屏幕设备描述表拷贝到内存设备描述表中
	CRect rct;
	UpdateWindow();
     m_jietu.GetWindowRect(rct);
	 //m_jietu.ScreenToClient(rct);
	BitBlt(hMemDC, 0, 0, nWidth, nHeight, hScrDC, rct.left+nX ,rct.top+nY, SRCCOPY);
	//得到屏幕位图的句柄 
	hBitmap = (HBITMAP)SelectObject(hMemDC, hOldBitmap);

	//清除 
	DeleteDC(hScrDC);
	
	DeleteDC(hMemDC);
	// 返回位图句柄 
	return hBitmap;

}

int jietu::SaveBitmapToFile(HBITMAP hBitmap, LPCWSTR lpFileName) {

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
	GetDIBits(hDC, hBitmap, 0, (UINT)Bitmap.bmHeight, (LPSTR)lpbi + sizeof(BITMAPINFOHEADER) + dwPaletteSize, (BITMAPINFO *)lpbi, DIB_RGB_COLORS);
	//恢复调色板 
	if (hOldPal)
	{
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
	dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;
	// 写入位图文件头 
	WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
	// 写入位图文件其余内容 
	WriteFile(fh, (LPSTR)lpbi, sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize, &dwWritten, NULL);
	//清除 
	GlobalUnlock(hDib);
	GlobalFree(hDib);
	CloseHandle(fh);
	return TRUE;
}

void jietu::DrawMessage(CRect &inRect, CDC * pDC)
{

}

void jietu::PaintWindow()
{

}

void jietu::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CDialogEx::OnLButtonUp(nFlags, point);
}


//void jietu::OnLButtonDblClk(UINT nFlags, CPoint point)
//{
//	// TODO: Add your message handler code here and/or call default
//	int nHitTest;
//	nHitTest = ct.HitTest(point);
//	//如果在是矩形内部双击
//	if (nHitTest == 8)
//	{
//		//保存位图到粘贴板中,bSave 为TRUE,
//		CopyScreenToBitmap(ct.m_rect);
//		PostQuitMessage(0);
//	}
//	CDialogEx::OnLButtonDblClk(nFlags, point);
//}


void jietu::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	//m_tushow.SetBitmap(*m_pBitmap);
	CDialogEx::OnMouseMove(nFlags, point);
}
