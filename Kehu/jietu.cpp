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

	//������Ƥ�����ʽ
	ct.m_nStyle = CMyTracker::resizeInside | CMyTracker::solidLine;
	ct.m_nHandleSize = 6;
	ct.m_rect.SetRect(-1, -1, -1, -1);  //���Ͻǣ����½�
		//��ʼ����Ƥ����,������resizeMiddle ����
	   //���þ�����ɫ
	ct.SetRectColor(RGB(10, 100, 130));
	  //���þ��ε���ʱ���,Ĭ�ϵ�̫С��,Ū�˸�����
    ct.SetResizeCursor(IDC_CURSOR6, IDC_CURSOR5, IDC_CURSOR4, IDC_CURSOR3, IDC_CURSOR2);
	m_hCursor = AfxGetApp()->LoadCursor(IDC_CURSOR1);
	//��ȡ��Ļ�ֱ���
	 m_xScreen = GetSystemMetrics(SM_CXSCREEN);
	 m_yScreen = GetSystemMetrics(SM_CYSCREEN);
	//��ȡ��Ļ��λͼ��
	CRect rect(0, 0, m_xScreen, m_yScreen);
	//CBitmap * m_pBitmap = CBitmap::FromHandle(CopyScreenToBitmap(&rect));
}

jietu::~jietu()
{
	

}

//���س�ʼ������
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
	//���Լ��ظ������͵�ͼƬ

	image.Load(photoPath); // ����һ��pngͼƬ

	//image.SetPixel(26,26,NULL);
	//m_jietu.ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
	//���þ�̬�ؼ���ʾλͼ /
//	HBITMAP bmp = image.Detach();
//	m_jietu.SetBitmap(bmp);
	float xScale;
	float yScale;
	CRect rect, rect1;
	int height = image.GetHeight();
	int width =  image.GetWidth();
 	m_jietu.GetClientRect(&rect); //���pictrue�ؼ����ڵľ�������
	if (width > rect.Width() || height > rect.Width()) //СͼƬ��������
	{
		 xScale = (float)rect.Width() / (float)width;
	     yScale = (float)rect.Height() / (float)height;
		 float ScaleIndex = (xScale >= yScale?xScale:yScale);
		 width = (int)width*ScaleIndex;
		 height = (int)height*ScaleIndex;
	}
	CDC *pDc = m_jietu.GetDC();//���pictrue�ؼ���Dc
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
		//��ʼ��ѡ���
		ct.TrackRubberBand(this,point,TRUE);
	else 
		//�������ѡ���
		ct.Track(this, point ,TRUE);
	    ct.m_rect.NormalizeRect();
	    //Invalidate(); //ˢ�Ǵ���
					  //��ͼ����
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
		 m_tushow.GetClientRect(&rect); //���pictrue�ؼ����ڵľ�������
		 if (width > rect.Width() || height > rect.Width()) //СͼƬ��������
		 {
			 xScale = (float)rect.Width() / (float)width;
			 yScale = (float)rect.Height() / (float)height;
			 float ScaleIndex = (xScale >= yScale ? xScale : yScale);
			 width = (int)width*ScaleIndex;
			 height = (int)height*ScaleIndex;
		 }
		 CDC *pDc = m_tushow.GetDC();//���pictrue�ؼ���Dc
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
		 SaveBitmapToFile(m_sav_bmp, lpFilepath);  //����Ƭ���浽���·����

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
	// ��Ļ���ڴ��豸������ 
	HBITMAP hBitmap, hOldBitmap;
	// λͼ��� 
	int nX, nY, nX2, nY2;
	// ѡ���������� 
	int nWidth, nHeight;
	// λͼ��Ⱥ͸߶� 
	int xScrn, yScrn;
	// ��Ļ�ֱ��� 
	// ȷ��ѡ������Ϊ�վ��� 
	if (IsRectEmpty(lpRect))
		return NULL;
	//Ϊ��Ļ�����豸������ 
//	CDC * dc = m_jietu.GetDC();
	hScrDC =CreateDC(L"DISPLAY", NULL, NULL, NULL);
	//Ϊ��Ļ�豸�����������ݵ��ڴ��豸������ 
	hMemDC = CreateCompatibleDC(hScrDC);
	// ���ѡ���������� 
	nX = lpRect->left;
	nY = lpRect->top;
	nX2 = lpRect->right;
	nY2 = lpRect->bottom;
	// �����Ļ�ֱ��� 
	xScrn = GetDeviceCaps(hScrDC, HORZRES);
	yScrn = GetDeviceCaps(hScrDC, VERTRES);
	//ȷ��ѡ�������ǿɼ��� 
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
	// ����һ������Ļ�豸��������ݵ�λͼ 
	hBitmap = CreateCompatibleBitmap(hScrDC, nWidth, nHeight);
	// ����λͼѡ���ڴ��豸�������� 
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
	// ����Ļ�豸�����������ڴ��豸��������
	CRect rct;
	UpdateWindow();
     m_jietu.GetWindowRect(rct);
	 //m_jietu.ScreenToClient(rct);
	BitBlt(hMemDC, 0, 0, nWidth, nHeight, hScrDC, rct.left+nX ,rct.top+nY, SRCCOPY);
	//�õ���Ļλͼ�ľ�� 
	hBitmap = (HBITMAP)SelectObject(hMemDC, hOldBitmap);

	//��� 
	DeleteDC(hScrDC);
	
	DeleteDC(hMemDC);
	// ����λͼ��� 
	return hBitmap;

}

int jietu::SaveBitmapToFile(HBITMAP hBitmap, LPCWSTR lpFileName) {

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
	GetDIBits(hDC, hBitmap, 0, (UINT)Bitmap.bmHeight, (LPSTR)lpbi + sizeof(BITMAPINFOHEADER) + dwPaletteSize, (BITMAPINFO *)lpbi, DIB_RGB_COLORS);
	//�ָ���ɫ�� 
	if (hOldPal)
	{
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
	dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;
	// д��λͼ�ļ�ͷ 
	WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
	// д��λͼ�ļ��������� 
	WriteFile(fh, (LPSTR)lpbi, sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize, &dwWritten, NULL);
	//��� 
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
//	//������Ǿ����ڲ�˫��
//	if (nHitTest == 8)
//	{
//		//����λͼ��ճ������,bSave ΪTRUE,
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
