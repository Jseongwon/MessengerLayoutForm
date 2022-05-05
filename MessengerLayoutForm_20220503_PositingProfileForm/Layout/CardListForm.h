// CardListForm.h
#ifndef _CARDLISTFORM_H
#define _CARDLISTFORM_H
#include "../Observers/ItemSubject.h"
#include "../Profiles/Profile.h"
#include "../Layout/UserCardListStyle.h"
#include "../Layout/PostingCardListStyle.h"
using namespace parkcom;

class CardListForm : public ItemSubject {
	friend class ProfileDirector;
	friend UserCardListStyle;
	friend PostingCardListStyle;
public:
	CWnd* pParentWnd;
	CardListStyle* cardListStyle;

public:
	CardListForm(CWnd* pParentWnd = NULL, COLORREF accentColor = RGB(103, 116, 255), COLORREF backgroundColor = RGB(232, 232, 232),
		COLORREF selectedBackgroundColor = RGB(255, 255, 255), COLORREF textColor = RGB(0, 0, 0), COLORREF selectedTextColor = RGB(102, 102, 102));

	COLORREF GetAccentColor();
	COLORREF GetBackgroundColor();
	COLORREF GetSelectedBackgroundColor();
	COLORREF GetTextColor();
	COLORREF GetSelectedTextColor();

	CPoint& GetHoverPoint() const;
	CPoint& GetDownPoint() const;

	void Repair(int cardListStyle);

protected:
	afx_msg virtual int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
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

	CRect currentRect;
	CRect m_ProfileRect;

	LONG m_CardLength;

	CPoint m_ptHoverPoint;
	CPoint m_ptDownPoint;

	BOOL m_bTrack;
};

inline COLORREF CardListForm::GetAccentColor() {
	return this->accentColor;
}
inline COLORREF CardListForm::GetBackgroundColor() {
	return this->backgroundColor;
}
inline COLORREF CardListForm::GetSelectedBackgroundColor() {
	return this->selectedBackgroundColor;
}
inline COLORREF CardListForm::GetTextColor() {
	return this->textColor;
}
inline COLORREF CardListForm::GetSelectedTextColor() {
	return this->selectedTextColor;
}

inline CPoint& CardListForm::GetHoverPoint() const {
	return const_cast<CPoint&>(this->m_ptHoverPoint);
}
inline CPoint& CardListForm::GetDownPoint() const {
	return const_cast<CPoint&>(this->m_ptDownPoint);
}

#endif // _CARDLISTFORM_H