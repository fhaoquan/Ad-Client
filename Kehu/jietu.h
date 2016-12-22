#pragma once
#include "afxwin.h"
#include "allvar.h"
#include "MyTracker.h"
// jietu dialog

extern CImage Resour;
extern struct usr ower;

class jietu : public CDialogEx
{
	DECLARE_DYNAMIC(jietu)

public:
	jietu(CWnd* pParent = NULL);   // standard constructor
	virtual ~jietu();

// Dialog Data
	enum { IDD = IDD_JIETU };

protected:
	virtual BOOL OnInitDialog();
	void DrawMessage(CRect &inRect, CDC * pDC);
	void PaintWindow();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
public:
//文件打开路径
	CString  photoPath;
	CString  lpFilepath;
afx_msg void OnBnClickedOk();
afx_msg void OnBnClickedCancel();
afx_msg void OnStnClickedJietu();
afx_msg void OnStnClickedpshow();

HCURSOR m_hCursor;              //光标
// 截图
CStatic m_jietu;
CImage  image , tmsrc,dimage;
CMyTracker  ct;  //橡皮筋类
CBitmap * m_pBitmap;
int m_xScreen, m_yScreen;
afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
afx_msg void OnPaint();
afx_msg HBITMAP CopyScreenToBitmap(LPRECT lpRect);
afx_msg int SaveBitmapToFile(HBITMAP hBitmap, LPCWSTR lpFileName);
// 效果展示
CStatic m_tushow;
//byte mybyte[];   //定义
HBITMAP m_sav_bmp;  //需要保存到图片
 afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
//afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
afx_msg void OnMouseMove(UINT nFlags, CPoint point);

};
