// ChatProfileStyle.h
#ifndef _CHATPROFILESTYLE_H
#define _CHATPROFILESTYLE_H
#include "ProfileStyle.h"

namespace parkcom {
	class ChatProfileStyle : public ProfileStyle {
	public:
		ChatProfileStyle(CWnd* pCurrentWnd = 0);
		virtual ~ChatProfileStyle();

		virtual void OnDraw(CDC* pDC);
	};
}

#endif // _CHATPROFILESTYLE_H