// PostingCardListStyle.h
#ifndef _POSTINGCARDLISTSTYLE_H
#define _POSTINGCARDLISTSTYLE_H
#include "CardListStyle.h"

namespace parkcom {
	class PostingCardListStyle : public CardListStyle {
	public:
		PostingCardListStyle(CWnd* pCurrentWnd = 0);
		virtual ~PostingCardListStyle();

		virtual void OnCreate(LPCREATESTRUCT lpCreateStruct);
		virtual void OnMouseMove(UINT nFlags, CPoint point);
		virtual void OnLButtonClicked(UINT nFlags, CPoint point);

		virtual void OnDraw(CDC* pDC);

	private:
		CRect m_ProfileRect;
	};
}

#endif // _POSTINGCARDLISTSTYLE_H