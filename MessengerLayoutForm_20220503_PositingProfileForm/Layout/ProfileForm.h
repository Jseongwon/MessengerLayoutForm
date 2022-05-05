// ProfileForm.h
#ifndef _PROFILEFORM_H
#define _PROFILEFORM_H
#define LAYOUT_PATH "C:\\Users\\jeong\\AppData\\Local\\Parkcom\\ParkcomMessenger\\Profiles"
#define BASENAME_LENGTH 64
#include "../Observers/ItemSubject.h"
#include "../Profiles/Profile.h"
#include "ChatProfileStyle.h"
#include "PostingProfileStyle.h"
using namespace parkcom;

class ProfileForm : public ItemSubject {
	friend class ProfileDirector;
	friend ChatProfileStyle;
	friend PostingProfileStyle;
public:
	CWnd* pParentWnd;
	ProfileStyle* profileStyle;

public:
	ProfileForm(CWnd* pParentWnd = NULL, COLORREF accentColor = RGB(103, 116, 255), COLORREF backgroundColor = RGB(237, 237, 237),
		COLORREF selectedBackgroundColor = RGB(179, 186, 255), COLORREF textColor = RGB(0, 0, 0), COLORREF selectedTextColor = RGB(103, 116, 255));

	virtual CString GetBaseName();

	COLORREF GetAccentColor();
	COLORREF GetBackgroundColor();
	COLORREF GetSelectedBackgroundColor();
	COLORREF GetTextColor();
	COLORREF GetSelectedTextColor();

	LONG GetBaseIndex();
	LONG GetProfileLength();

	void Repair(int profileStyle);

protected:
	afx_msg virtual int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pCWnd);
	afx_msg void OnKillFocus(CWnd* pCWnd);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()

protected:
	COLORREF accentColor;
	COLORREF backgroundColor;
	COLORREF selectedBackgroundColor;
	COLORREF textColor;
	COLORREF selectedTextColor;

	TCHAR itemListName[32];
	TCHAR baseName[64];

	LONG baseIndex;
	LONG m_ProfileLength;

	BOOL m_bTrack;
};

inline COLORREF ProfileForm::GetAccentColor() {
	return this->accentColor;
}
inline COLORREF ProfileForm::GetBackgroundColor() {
	return this->backgroundColor;
}
inline COLORREF ProfileForm::GetSelectedBackgroundColor() {
	return this->selectedBackgroundColor;
}
inline COLORREF ProfileForm::GetTextColor() {
	return this->textColor;
}
inline COLORREF ProfileForm::GetSelectedTextColor() {
	return this->selectedTextColor;
}

inline CString ProfileForm::GetBaseName() {
	return this->baseName;
}

inline LONG ProfileForm::GetBaseIndex() {
	return this->baseIndex;
}
inline LONG ProfileForm::GetProfileLength() {
	return this->m_ProfileLength;
}

#endif // _PROFILEFORM_H