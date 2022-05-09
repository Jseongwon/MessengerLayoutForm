// TextExtent.cpp
/*
파일명칭 : TextExtent.cpp
기    능 : 문자열 크기를 구하는 클래스를 정의한다.
작성일자 : 2022.01.25
*/
#include "TextExtent.h"
#include "Subject.h"
#include <afxwin.h>
#define ASCII 129

TextExtent::TextExtent() {
	this->pCurrentWnd = 0;
}

TextExtent::TextExtent(CWnd* pCurrentWnd) {
	this->pCurrentWnd = pCurrentWnd;
	this->subject = dynamic_cast<Subject*>(this->pCurrentWnd);

	CDC* dc = this->pCurrentWnd->GetDC();
	
	HFONT hFont;
	HFONT oldFont;
	LOGFONT logFont;

	CSize cSize;

	Long i = 0;

	ZeroMemory(&logFont, sizeof(LOGFONT));
	logFont.lfHeight = this->subject->GetSubjectState()->GetLogFontHeight();
	logFont.lfWidth = this->subject->GetSubjectState()->GetLogFontWidth();
	strcpy_s(logFont.lfFaceName, this->subject->GetSubjectState()->GetLogFontFaceName().c_str());

	hFont = CreateFontIndirect(&logFont);
	oldFont = (HFONT)SelectObject(*dc, hFont);

	this->widths = new Long[ASCII];

	this->widths[0] = 0;
	i++;
	while (i < 9) {
		this->widths[i] = 0;
		i++;
	}

	cSize = dc->GetTextExtent(CString("        "));
	this->widths[i] = cSize.cx;
	i++;
	while (i < 32) {
		this->widths[i] = 0;
		i++;
	}
	while (i < ASCII - 2) {
		cSize = dc->GetTextExtent(CString((char)i));
		this->widths[i] = cSize.cx;
		i++;
	}
	this->widths[i] = 0;
	i++;

	cSize = dc->GetTextExtent(CString("ㄱ"));
	this->widths[i] = cSize.cx;
	this->height = cSize.cy;

	SelectObject(*dc, oldFont);
	DeleteObject(hFont);

	this->pCurrentWnd->ReleaseDC(dc);
}

TextExtent::TextExtent(const TextExtent& source) {
	Long i = 0;
	this->pCurrentWnd = source.pCurrentWnd;
	this->widths = new Long[ASCII];
	while (i < ASCII) {
		this->widths[i] = source.widths[i];
		i++;
	}
	this->height = source.height;
}

TextExtent::~TextExtent() {
	if (this->widths != 0) {
		delete[] this->widths;
	}
}

TextExtent& TextExtent::operator =(const TextExtent& source) {
	Long i = 0;
	this->pCurrentWnd = source.pCurrentWnd;
	this->widths = new Long[ASCII];
	while (i < ASCII) {
		this->widths[i] = source.widths[i];
		i++;
	}
	this->height = source.height;

	return *this;
}

Long TextExtent::GetWidth(Long index) {
	return this->widths[index];
}

Long TextExtent::GetWidth(char(*text)) {
	Long width;

	CDC* dc;
	HFONT hFont;
	HFONT oldFont;
	LOGFONT logFont;

	string str;

	CSize cSize;

	dc = this->pCurrentWnd->GetDC();

	ZeroMemory(&logFont, sizeof(LOGFONT));
	logFont.lfHeight = this->subject->GetSubjectState()->GetLogFontHeight();
	logFont.lfWidth = this->subject->GetSubjectState()->GetLogFontWidth();
	strcpy_s(logFont.lfFaceName, this->subject->GetSubjectState()->GetLogFontFaceName().c_str());

	hFont = CreateFontIndirect(&logFont);
	oldFont = (HFONT)SelectObject(*dc, hFont);

	str = text;
	if (!(text[0] & 0x80)) {
		width = this->widths[(int)text[0]];
	}
	else if ((str >= "ㄱ" && str <= "ㅣ") || (str >= "가" && str <= "\uD7AF")) {
		width = this->widths[ASCII - 1];
	}
	else {
		cSize = dc->GetTextExtent(text);
		width = cSize.cx;
	}

	SelectObject(*dc, oldFont);
	DeleteObject(hFont);

	this->pCurrentWnd->ReleaseDC(dc);

	return width;
}

Long TextExtent::GetContentsHeight(string contents) {
	// 1. \r을 찾는다.
	Long count = 1;
	
	size_t offset = 0;
	size_t index = 0;

	// 2. 최대 높이를 구한다.
	index = contents.find('\r', offset);
	while (index != string::npos) {
		count++;
		offset = index + 1;
		index = contents.find('\r', offset);
	}

	// 3. 최대 높이를 출력한다.
	return this->height * count;
}

Long TextExtent::GetContentsRowLength(string sourceContents) {
	// 1. \r을 찾는다.
	Long count = 1;

	size_t offset = 0;
	size_t index = 0;

	// 2. 최대 높이를 구한다.
	index = sourceContents.find('\r', offset);
	while (index != string::npos) {
		count++;
		offset = index + 1;
		index = sourceContents.find('\r', offset);
	}

	return count;
}

Long TextExtent::GetContentsRowLength(string sourceContents, Long totalWidth) {
	Long rowLength = 1;
	string textString;

	CDC* dc;
	HFONT hFont;
	HFONT oldFont;
	LOGFONT logFont;

	CSize cSize;

	char text[3] = { '\0', };

	Long width;
	Long currentWidth = 0;

	size_t i = 0;

	dc = this->pCurrentWnd->GetDC();

	ZeroMemory(&logFont, sizeof(LOGFONT));
	logFont.lfHeight = this->subject->GetSubjectState()->GetLogFontHeight();
	logFont.lfWidth = this->subject->GetSubjectState()->GetLogFontWidth();
	strcpy_s(logFont.lfFaceName, this->subject->GetSubjectState()->GetLogFontFaceName().c_str());

	hFont = CreateFontIndirect(&logFont);
	oldFont = (HFONT)SelectObject(*dc, hFont);
	
	while (i < sourceContents.length()) {
		// 1. 글자를 따온다.
		text[0] = sourceContents[i];
		text[1] = '\0';
		if (text[0] & 0x80) {
			text[1] = sourceContents[i + 1];
			i++;
		}
		textString = text;

		// 2. 글자의 너비를 구한다.
		if (!(text[0] & 0x80)) {
			width = this->widths[(int)text[0]];
		}
		else if ((textString >= "ㄱ" && textString <= "ㅣ") || (textString >= "가" && textString <= "\uD7AF"/*0xED 0x9E 0xAF*/)) {
			width = this->widths[ASCII - 1];
		}
		else {
			cSize = dc->GetTextExtent(text);
			width = cSize.cx;
		}

		// 3. 총 너비를 구한다.
		currentWidth += width;

		// 4. 말풍선 너비보다 총 너비가 크면 개행문자를 추가한다.
		if (currentWidth > totalWidth) {
			rowLength++;
			currentWidth = 0;
		}

		i++;
	}

	SelectObject(*dc, oldFont);
	DeleteObject(hFont);

	this->pCurrentWnd->ReleaseDC(dc);

	return rowLength;
}

Long TextExtent::GetContentsWidth(string contents) {
	Long longestWidth = 0;
	Long totalWidth = 0;
	Long width;

	CDC* dc;
	HFONT hFont;
	HFONT oldFont;
	LOGFONT logFont;

	CSize cSize;

	string str;

	char text[3] = { '\0', };

	size_t i = 0;

	bool isFinded = false;

	dc = this->pCurrentWnd->GetDC();

	ZeroMemory(&logFont, sizeof(LOGFONT));
	logFont.lfHeight = this->subject->GetSubjectState()->GetLogFontHeight();
	logFont.lfWidth = this->subject->GetSubjectState()->GetLogFontWidth();
	strcpy_s(logFont.lfFaceName, this->subject->GetSubjectState()->GetLogFontFaceName().c_str());

	hFont = CreateFontIndirect(&logFont);
	oldFont = (HFONT)SelectObject(*dc, hFont);
	while (i < contents.length()) {
		text[0] = contents[i];
		if (text[0] & 0x80) {
			text[1] = contents[i + 1];
			i++;
		}

		str = text;
		if (!(text[0] & 0x80)) {
			width = this->widths[(int)text[0]];
		}
		else if ((str >= "ㄱ" && str <= "ㅣ") || (str >= "가" && str <= "\uD7AF")) {
			width = this->widths[ASCII - 1];
		}
		else {
			cSize = dc->GetTextExtent(text);
			width = cSize.cx;
		}
		totalWidth += width;
		if (text[0] == '\r' || text[0] == '\n' || i + 1 == contents.length()) {
			if (longestWidth < totalWidth) {
				longestWidth = totalWidth;
			}
			totalWidth = 0;
		}

		i++;
	}

	SelectObject(*dc, oldFont);
	DeleteObject(hFont);

	this->pCurrentWnd->ReleaseDC(dc);

	return longestWidth;
}

Long TextExtent::GetContentsWidth(string contents, Long lfHeight, Long lfWidth, string lfFaceName) {
	Long longestWidth = 0;
	Long totalWidth = 0;
	Long width;

	CDC* dc;
	HFONT hFont;
	HFONT oldFont;
	LOGFONT logFont;

	CSize cSize;

	string str;

	char text[3] = { '\0', };

	size_t i = 0;

	bool isFinded = false;

	dc = this->pCurrentWnd->GetDC();

	ZeroMemory(&logFont, sizeof(LOGFONT));
	logFont.lfHeight = lfHeight;
	logFont.lfWidth = lfWidth;
	strcpy_s(logFont.lfFaceName, lfFaceName.c_str());

	hFont = CreateFontIndirect(&logFont);
	oldFont = (HFONT)SelectObject(*dc, hFont);
	while (i < contents.length()) {
		text[0] = contents[i];
		if (text[0] & 0x80) {
			text[1] = contents[i + 1];
			i++;
		}

		str = text;
		if (!(text[0] & 0x80)) {
			width = this->widths[(int)text[0]];
		}
		else if ((str >= "ㄱ" && str <= "ㅣ") || (str >= "가" && str <= "\uD7AF")) {
			width = this->widths[ASCII - 1];
		}
		else {
			cSize = dc->GetTextExtent(text);
			width = cSize.cx;
		}
		totalWidth += width;
		if (text[0] == '\r' || text[0] == '\n' || i + 1 == contents.length()) {
			if (longestWidth < totalWidth) {
				longestWidth = totalWidth;
			}
			totalWidth = 0;
		}

		i++;
	}

	SelectObject(*dc, oldFont);
	DeleteObject(hFont);

	this->pCurrentWnd->ReleaseDC(dc);

	return longestWidth;
}

void TextExtent::WrappingContents(string sourceContents, Long totalWidth, string* wrappingContents, Long* wrappingCount, Long* longestWidth) {
	string textString;

	CDC* dc;
	HFONT hFont;
	HFONT oldFont;
	LOGFONT logFont;

	CSize cSize;

	char text[3] = { '\0', };

	Long width;
	Long currentWidth = 0;

	size_t i = 0;

	dc = this->pCurrentWnd->GetDC();

	ZeroMemory(&logFont, sizeof(LOGFONT));
	logFont.lfHeight = this->subject->GetSubjectState()->GetLogFontHeight();
	logFont.lfWidth = this->subject->GetSubjectState()->GetLogFontWidth();
	strcpy_s(logFont.lfFaceName, this->subject->GetSubjectState()->GetLogFontFaceName().c_str());

	hFont = CreateFontIndirect(&logFont);
	oldFont = (HFONT)SelectObject(*dc, hFont);
	if (wrappingCount != 0) {
		*wrappingCount = 0;
	}
	if (longestWidth != 0) {
		*longestWidth = 0;
	}

	while (i < sourceContents.length()) {
		// 1. 글자를 따온다.
		text[0] = sourceContents[i];
		text[1] = '\0';
		if (text[0] & 0x80) {
			text[1] = sourceContents[i + 1];
			i++;
		}
		textString = text;

		// 2. 글자의 너비를 구한다.
		if (!(text[0] & 0x80)) {
			width = this->widths[(int)text[0]];
		}
		else if ((textString >= "ㄱ" && textString <= "ㅣ") || (textString >= "가" && textString <= "\uD7AF"/*0xED 0x9E 0xAF*/)) {
			width = this->widths[ASCII - 1];
		}
		else {
			cSize = dc->GetTextExtent(text);
			width = cSize.cx;
		}

		// 3. 총 너비를 구한다.
		currentWidth += width;

		// 4. 글자가 개행문자이면 줄 수를 센다.
		if (textString == "\n" && wrappingCount != 0) {
			(*wrappingCount)++;
		}

		// 5. 말풍선 너비보다 총 너비가 크면 개행문자를 추가한다.
		if (currentWidth > totalWidth) {
			(*wrappingContents) += '\r';
			if (wrappingCount != 0) {
				(*wrappingCount)++;
			}
			if (longestWidth != 0) {
				*longestWidth = totalWidth;
			}
			currentWidth = 0;
		}
		if (longestWidth != 0 && *longestWidth < currentWidth) {
			*longestWidth = currentWidth;
		}
		// 6. 따온 글자를 추가한다.
		(*wrappingContents) += textString;

		i++;
	}

	SelectObject(*dc, oldFont);
	DeleteObject(hFont);

	this->pCurrentWnd->ReleaseDC(dc);
}