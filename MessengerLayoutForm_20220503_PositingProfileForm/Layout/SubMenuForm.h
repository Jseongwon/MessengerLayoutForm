// SubMenuForm.h
#ifndef _SUBMENUFORM_H
#define _SUBMENUFORM_H
#include <afxwin.h>
#include "SubMenuCard.h"
using namespace parkcom;

class SubMenuForm : public CWnd {
public:
	enum { CARDLIST = 0, FILTER = 1, SETTING = 2, BOTTOMBUTTON = 3 };

public:
	CWnd* pParentWnd;

public:
	SubMenuForm(CWnd* pParentWnd = NULL, CString subMenuName = "", CString buttonName = "", COLORREF accentColor = RGB(103, 116, 255), COLORREF backgroundColor = RGB(232, 232, 232),
		COLORREF selectedBackgroundColor = RGB(255, 255, 255), COLORREF textColor = RGB(0, 0, 0), COLORREF selectedTextColor = RGB(103, 116, 255));

	COLORREF GetAccentColor();
	COLORREF GetBackgroundColor();
	COLORREF GetSelectedBackgroundColor();
	COLORREF GetTextColor();
	COLORREF GetSelectedTextColor();

	TCHAR* GetSubMenuName() const;
	TCHAR* GetButtonName() const;

protected:
	afx_msg virtual int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pCWnd);
	afx_msg void OnKillFocus(CWnd* pCWnd);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()

private:
	SubMenuCard* p_SubMenuCard;

	BOOL onIsFilter;
	BOOL onIsSetting;
	BOOL onIsButtonArea;
	BOOL m_bTrack;

	INT downImageNumber;

	CRect currentRect;

	COLORREF accentColor;
	COLORREF backgroundColor;
	COLORREF selectedBackgroundColor;
	COLORREF textColor;
	COLORREF selectedTextColor;

	TCHAR subMenuName[32];
	TCHAR buttonName[64];
};

inline COLORREF SubMenuForm::GetAccentColor() {
	return this->accentColor;
}
inline COLORREF SubMenuForm::GetBackgroundColor() {
	return this->backgroundColor;
}
inline COLORREF SubMenuForm::GetSelectedBackgroundColor() {
	return this->selectedBackgroundColor;
}
inline COLORREF SubMenuForm::GetTextColor() {
	return this->textColor;
}
inline COLORREF SubMenuForm::GetSelectedTextColor() {
	return this->selectedTextColor;
}
inline TCHAR* SubMenuForm::GetSubMenuName() const {
	return const_cast<TCHAR*>(this->subMenuName);
}
inline TCHAR* SubMenuForm::GetButtonName() const {
	return const_cast<TCHAR*>(this->buttonName);
}

#endif // _SUBMENUFORM_H