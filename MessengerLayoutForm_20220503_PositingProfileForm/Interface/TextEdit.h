#ifndef _TEXTEDIT_H
#define _TEXTEDIT_H

#include "ChatEditStyle.h"
#include "../TextEditor/TextEditingForm.h"
#include <string>
using namespace std;
using namespace parkcom;

class TextEdit : public TextEditingForm {
	friend ChatEditStyle;
public:
	CWnd* pParentWnd;
	EditStyle* editStyle;

	void Repair(int editStyle);

public:
	TextEdit(CWnd* pParentWnd, COLORREF backgroundColor = RGB(255, 255, 255), BOOL isShowScroll = FALSE);
	virtual int OnCreate(LPCREATESTRUCT lpCreateStruct);

	void Write(string content); //юс╫ц
	void Clear();

protected:
	afx_msg void OnClose();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSetFocus(CWnd* pNewWnd);
	afx_msg void OnKillFocus(CWnd* pOldWnd);
	afx_msg void OnLButtonUp(UINT nFlag, CPoint point);

	DECLARE_MESSAGE_MAP()
};

#endif //_TEXTEDIT_H