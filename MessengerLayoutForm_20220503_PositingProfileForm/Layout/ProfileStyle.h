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

		virtual void OnDraw(CDC* pDC) {  }
		virtual void SpecialPosting(bool isSpecialPosting) {  }
		virtual bool IsSpecialPosting() { return false; }

	protected:
		CWnd* pCurrentWnd;
	};
}

#endif // _PROFILESTYLE_H