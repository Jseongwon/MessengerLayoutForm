// MenuListForm.h
#ifndef _MENULISTFORM_H
#define _MENULISTFORM_H
#define CARDMAX 5
#include "CardListForm.h"
#include "MenuCard.h"
#include "../Utilities/LinkedList.h"
using namespace parkcom;

class MenuListForm : public CardListForm {
public:
	MenuListForm(CWnd* pParentWnd = NULL, COLORREF accentColor = RGB(103, 116, 255), COLORREF backgroundColor = RGB(222, 222, 222),
		COLORREF selectedBackgroundColor = RGB(255, 255, 255), COLORREF textColor = RGB(0, 0, 0), COLORREF selectedTextColor = RGB(103, 116, 255));

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

private:
	LinkedList<MenuCard> menuCards;
	MenuCard* p_DownCard;
	MenuCard* p_HoverCard;

	CRect menuCardRect;

	LONG number;
};

int CompareMenuCardsInMenuListForm(void* one, void* other);

#endif // _MENULISTFORM_H