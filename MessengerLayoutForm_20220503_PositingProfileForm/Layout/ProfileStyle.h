// ProfileStyle.h
#ifndef _PROFILESTYLE_H
#define _PROFILESTYLE_H
#include <afxwin.h>

namespace parkcom {
	class DrawingGenerator;
	class ProfileStyle {
	public:
		enum { CHATPROFILESTYLE = 0, POSTINGPROFILESTYLE = 1 };
	public:
		ProfileStyle(CWnd* pCurrentWnd = 0);
		virtual ~ProfileStyle() = 0;

		virtual void OnSize(UINT nType, int cx, int cy) {  }
		virtual void OnDraw(CDC* pDC) {  }
		virtual void SpecialPosting(bool isSpecialPosting) {  }
		virtual void SetDocumentRowLength(LONG documentRowLength) {  }

		virtual bool IsSpecialPosting() { return false; }
		virtual LONG GetDocumentRowLength() { return 0; }

	protected:
		CWnd* pCurrentWnd;
		bool onIsDrawing;
	};
}

#endif // _PROFILESTYLE_H