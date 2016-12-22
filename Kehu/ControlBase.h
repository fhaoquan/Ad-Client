#pragma once

// ��ť״̬
enum enumButtonState
{
	bsNormal = 0,
	bsHover,
	bsDown,
	bsDisable,
	bsHoverDown,	
	bsDisableDown
};

#define				BUTTOM_DOWN			1
#define				BUTTOM_UP			2

class CControlBase
{
public:
	CControlBase(HWND hWnd, UINT uControlID, CRect rc, CString strTitle = L"", BOOL bIsVisible = TRUE, BOOL bIsDisable = FALSE ,
		 BOOL bRresponse = TRUE) ;
	virtual ~CControlBase(void);

	virtual void Draw(CDC &dc, CRect rcUpdate) = 0;
	virtual BOOL IsDraw(CPoint point) { return FALSE; };
	virtual BOOL OnFocus(bool bFocus){ return FALSE;};

	virtual void SetRect(CRect rc) { m_rc = rc;};
	virtual CRect GetRect() { return m_rc;};
	virtual void SetTitle(CString strTitle);
	virtual CString GetTitle() { return m_strTitle;};
	UINT GetControlID() {return m_uID;};
	void SetVisible(BOOL bIsVisible) { m_bIsVisible = bIsVisible;};
	BOOL GetVisible() {return m_bIsVisible;};
	void SetDisable(BOOL bIsDisable) { m_bIsDisable = bIsDisable;};
	BOOL GetDisable() {return m_bIsDisable;};
	void SetRresponse(BOOL bRresponse) { m_bRresponse = bRresponse;};
	BOOL GetRresponse() {return m_bRresponse;};

	virtual BOOL OnMouseMove(UINT nFlags, CPoint point){ return FALSE;};
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point){ return FALSE;};
	virtual BOOL OnLButtonUp(UINT nFlags, CPoint point){ return FALSE;};

	virtual BOOL GetLButtonDown(){ return TRUE;};
	virtual BOOL GetLButtonUp(){ return TRUE;};

	// ����֪ͨ��Ϣ
	bool SendMessage(UINT Msg, WPARAM wParam, LPARAM lParam);

protected:
	UINT	m_uID;					// �ؼ� ID
	CRect	m_rc;					// ����
	BOOL	m_bIsVisible;			// �ɼ�
	BOOL	m_bIsDisable;			// �Ƿ����
	BOOL	m_bRresponse;			// ��Ӧ
	BOOL	m_bIsSelect;			// �Ƿ�ѡ��
	CString	m_strTitle;				// ����
	HWND	m_hWnd;
	CFont	m_font;
};
