
// Kehu.h : PROJECT_NAME ���ó�ʽ����Ҫ���^�n
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �����˙n��ǰ�Ȱ��� 'stdafx.h'"
#endif

#include "resource.h"		// ��Ҫ��̖


// CKehuApp: 
// Ո��醌�����e�� Kehu.cpp
//

class CKehuApp : public CWinApp
{
public:
	CKehuApp();

// ����
public:
	virtual BOOL InitInstance();

// ��ʽ�a����

	DECLARE_MESSAGE_MAP()
};



extern CKehuApp theApp;