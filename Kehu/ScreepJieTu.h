#pragma once
#include "TcpSocket.h"
#include"json\json.h"

// ScreepJieTu �Ի���

class ScreepJieTu : public CDialogEx
{
	DECLARE_DYNAMIC(ScreepJieTu)
	virtual BOOL OnInitDialog();

public:

	ScreepJieTu(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ScreepJieTu();

// �Ի�������
	enum { IDD = IDD_Screepjt };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnNcXButtonDblClk(short nFlags, UINT nButton, CPoint point);
//	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	bool isStart, isEnd;  //��¼��ͼ�Ƿ�ʼ���ͽ���
    POINT	pointBegin, pointEnd; //������¼��ʼ����ͽ������꣬��ȡ��������
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
	CButton  *st ,*stL;  //����һ����ť
	bool isjud;			//�ж����Ƿ񴴽��˰�ť
	int  dataType;
	int jietutag;  //������ʾ��ͼ��״̬
	bool tag ;  // ������ղ����ͻ��ǹ�ע����
	int scans;   //����ֵ
	int sccnt[7];  //����ͳ��
	TcpSocket mytcp;  //��������ͼƬ

};
