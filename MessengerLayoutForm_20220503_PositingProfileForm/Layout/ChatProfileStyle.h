// ChatProfileStyle.h
#ifndef _CHATPROFILESTYLE_H
#define _CHATPROFILESTYLE_H
#include "ProfileStyle.h"

class TextEdit;
namespace parkcom {
	class ChatProfileStyle : public ProfileStyle {
	public:
		TextEdit* textEdit;

	public:
		ChatProfileStyle(CWnd* pCurrentWnd = 0);
		virtual ~ChatProfileStyle();

		virtual void OnSize(UINT nType, int cx, int cy);
		virtual void OnDraw(CDC* pDC);
	};
}

#endif // _CHATPROFILESTYLE_H