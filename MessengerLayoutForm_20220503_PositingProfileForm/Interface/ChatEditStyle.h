// ChatEditStyle.h
#ifndef _CHATEDITSTYLE_H
#define _CHATEDITSTYLE_H
#include "EditStyle.h"

namespace parkcom {
	class ChatEditStyle : public EditStyle {
	public:
		ChatEditStyle(TextEdit* textEdit = 0);
		virtual ~ChatEditStyle();

		virtual void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	};
}

#endif // _CHATEDITSTYLE_H