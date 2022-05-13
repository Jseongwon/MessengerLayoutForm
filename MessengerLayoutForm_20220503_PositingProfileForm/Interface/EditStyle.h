// EditStyle.h
#ifndef _EDITSTYLE_H
#define _EDITSTYLE_H
#include <afxwin.h>

class TextEdit;
namespace parkcom {
	class EditStyle {
	public:
		enum { CHATEDITSTYLE = 0, POSTINGEDITSTYLE = 1, COMMENTEDITSTYLE = 2 };

	public:
		EditStyle(TextEdit* textEdit = 0);
		virtual ~EditStyle() = 0;

		virtual void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) = 0;

	protected:
		TextEdit* textEdit;
	};
}

#endif // _EDITSTYLE_H