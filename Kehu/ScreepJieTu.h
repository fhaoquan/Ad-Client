#pragma once
#include "TcpSocket.h"
#include"json\json.h"

// ScreepJieTu 对话框

class ScreepJieTu : public CDialogEx
{
	DECLARE_DYNAMIC(ScreepJieTu)
	virtual BOOL OnInitDialog();

public:

	ScreepJieTu(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ScreepJieTu();

// 对话框数据
	enum { IDD = IDD_Screepjt };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnNcXButtonDblClk(short nFlags, UINT nButton, CPoint point);
//	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	bool isStart, isEnd;  //记录截图是否开始，和结束
    POINT	pointBegin, pointEnd; //用来记录开始坐标和结束坐标，获取矩形区域
//	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	HBITMAP CopyScreenToBitmap(LPRECT lpRect);
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
//	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnSC_Button();
	afx_msg void OnSCL_Button();
	        void WebClient(const string  str);
	        void CallName();
			void CreateStretchImage(CImage *pImage,CImage *ResultImage,int StretchHeight,int StretchWidth);
	int SaveBitmapToFile(HBITMAP hBitmap, LPCWSTR lpFileName);
	CButton  *st ,*stL;  //定义一个按钮
	bool isjud;			//判断是是否创建了按钮
	int  dataType;
	int jietutag;  //用来表示截图的状态
	bool tag ;  // 甄别是收藏类型还是关注类型
	int scans;   //类型值
	int sccnt[7];  //类型统计
	TcpSocket mytcp;  //用来发送图片

};
