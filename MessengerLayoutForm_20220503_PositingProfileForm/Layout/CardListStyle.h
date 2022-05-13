// CardListStyle.h
#ifndef _CARDLISTSTYLE_H
#define _CARDLISTSTYLE_H
#include <afxwin.h>

namespace parkcom {
	class DrawingGenerator;
	class CardListStyle {
	public:
		enum { USERCARDLISTSTYLE = 0, POSTINGCARDLISTSTYLE = 1 };
	public:
		CardListStyle(CWnd* pCurrentWnd = 0);
		virtual ~CardListStyle() = 0;

		virtual void OnCreate(LPCREATESTRUCT lpCreateStruct) {  }
		virtual void OnSize(UINT nType, int cx, int cy) {  }
		virtual void OnMouseMove(UINT nFlags, CPoint point) {  }
		virtual void OnLButtonClicked(UINT nFlags, CPoint point) {  }

		virtual void OnDraw(CDC* pDC) {  }

	protected:
		CWnd* pCurrentWnd;
		bool onIsDrawing;
	};
}

#endif // _CARDLISTSTYLE_H