#pragma once
#include "explorer1.h"

#ifdef _WIN32_WCE
#error "Windows CE 不支持 CDHtmlDialog。"
#endif 

extern CImage Resour;
extern struct usr ower;

// News 对话框

class News : public CDHtmlDialog
{
	DECLARE_DYNCREATE(News)

public:

	News(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~News();

//重写
	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);
// 对话框数据
	//enum { IDD = IDD_DIALOG3, IDH = IDR_HTML_NEWS };
//
	enum { IDD = IDD_DIALOG3, IDH = 0 };
protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()

public:

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void GotoUrl(LPCTSTR pszUrl);

	afx_msg void OnDestroy();
	afx_msg void OnClose();
};
