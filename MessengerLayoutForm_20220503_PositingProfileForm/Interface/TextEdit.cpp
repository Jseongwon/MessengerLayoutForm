#include "TextEdit.h"
#include "../TextEditor/GlyphFactory.h"
#include "../TextEditor/GlyphScanner.h"
#include "../TextEditor/Glyph.h"
#include "../TextEditor/CharacterMetrics.h"
#include "../TextEditor/ScrollController.h"

TextEdit::TextEdit(COLORREF backgroundColor, BOOL isShowScroll)
	: TextEditingForm(backgroundColor, isShowScroll) {
	this->editStyle = 0;
}

void TextEdit::Repair(int editStyle) {
	if (this->editStyle != NULL) {
		delete this->editStyle;
	}
	this->editStyle = NULL;
	if (editStyle == EditStyle::CHATEDITSTYLE) {
		this->editStyle = new ChatEditStyle(this);
	}
	else if (editStyle == EditStyle::POSTINGEDITSTYLE) {
		//this->editStyle = new PostingEditStyle(this);
	}
	else if (editStyle == EditStyle::COMMENTEDITSTYLE) {
		//this->editStyle = new CommentEditStyle(this);
	}
}

BEGIN_MESSAGE_MAP(TextEdit, TextEditingForm)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_CHAR()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

int TextEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	TextEditingForm::OnCreate(lpCreateStruct);

	return 0;
}

void TextEdit::OnClose() {
	if (this->editStyle != NULL) {
		delete this->editStyle;
	}
	TextEditingForm::OnClose();
}

void TextEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	TextEditingForm::OnChar(nChar, nRepCnt, nFlags);
}

void TextEdit::OnSetFocus(CWnd* pNewWnd) {
	TextEditingForm::OnSetFocus(pNewWnd);
}

void TextEdit::OnKillFocus(CWnd* pOldWnd) {
	TextEditingForm::OnKillFocus(pOldWnd);
}

void TextEdit::OnLButtonUp(UINT nFlag, CPoint point) {
	TextEditingForm::OnLButtonUp(nFlag, point);
}

void TextEdit::Write(string content) {
	GlyphFactory glyphFactory;
	Glyph* glyph;
	string token;
	string resultBuffer(content);
	//resultBuffer += "\r\n";
	GlyphScanner glyphScanner(resultBuffer);
	while (glyphScanner.IsEnd() == FALSE) {
		token = glyphScanner.GetToken();
		if (token != "\r\n") {
			glyph = glyphFactory.Make(token.c_str());
			this->current->Add(glyph);
		}
		else {
			glyph = glyphFactory.Make(token.c_str());
			Long index = this->note->Add(glyph);
			this->current = this->note->GetAt(index);
		}
		glyphScanner.Next();
	}

	this->Invalidate();
	this->Notify();

	Long x = this->characterMetrics->GetX(this->current) + 1; // 
	Long y = this->characterMetrics->GetY(this->note->GetCurrent() + 1); // 0베이스이므로 1더함
	this->scrollController->SmartScrollToPoint(x, y);
}

void TextEdit::Clear() {
	GlyphFactory glyphFactory;

	if (this->note != NULL) {
		delete this->note;
	}
	this->note = glyphFactory.Make("");
	this->current = glyphFactory.Make("\r\n");

	this->note->Add(this->current);

	Long index = this->note->Move(0);
	this->current = this->note->GetAt(index);
	this->current->First();
	this->Invalidate();
	this->Notify();
}