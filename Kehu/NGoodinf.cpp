// NGoodinf.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Kehu.h"
#include "NGoodinf.h"


// NGoodinf �Ի���

IMPLEMENT_DYNCREATE(NGoodinf, CDHtmlDialog)

NGoodinf::NGoodinf(CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(NGoodinf::IDD, NGoodinf::IDH, pParent)
{

}

NGoodinf::~NGoodinf()
{
}

void NGoodinf::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
}

BOOL NGoodinf::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

BEGIN_MESSAGE_MAP(NGoodinf, CDHtmlDialog)
END_MESSAGE_MAP()

BEGIN_DHTML_EVENT_MAP(NGoodinf)
	DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
	DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
END_DHTML_EVENT_MAP()



// NGoodinf ��Ϣ�������

HRESULT NGoodinf::OnButtonOK(IHTMLElement* /*pElement*/)
{
	OnOK();
	return S_OK;
}

HRESULT NGoodinf::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	OnCancel();
	return S_OK;
}
