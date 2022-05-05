// UserCardListStyle.h
#ifndef _USERCARDLISTSTYLE_H
#define _USERCARDLISTSTYLE_H
#include "CardListStyle.h"

namespace parkcom {
	class UserCardListStyle : public CardListStyle {
	public:
		UserCardListStyle(CWnd* pCurrentWnd = 0);
		virtual ~UserCardListStyle();

		virtual void OnCreate(LPCREATESTRUCT lpCreateStruct);
		virtual void OnMouseMove(UINT nFlags, CPoint point);
		virtual void OnLButtonClicked(UINT nFlags, CPoint point);

		virtual void OnDraw(CDC* pDC);

	private:
		CRect m_PersonalProfileRect;
		CRect m_FriendProfileRect;
	};
}

#endif // _USERCARDLISTSTYLE_H