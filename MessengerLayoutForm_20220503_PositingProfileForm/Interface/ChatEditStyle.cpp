// ChatEditStyle.cpp
/*
���ϸ�Ī : ChatEditStyle.cpp
��    �� : ä�� ���� ��Ÿ�� Ŭ������ �����Ѵ�.
�� �� �� : ������
�ۼ����� : 2022.05.11
*/
#include "ChatEditStyle.h"
#include "TextEdit.h"
#include "../TextEditor/Glyph.h"
#include "../TextEditor/DummyLine.h"
#include "../Printer/Printer.h"
#define TEMPPATH "C:\\Users\\jeong\\AppData\\Local\\Parkcom\\ParkcomMessenger\\Profiles\\Temp"
using namespace parkcom;

ChatEditStyle::ChatEditStyle(TextEdit* textEdit)
	: EditStyle(textEdit) {

}

ChatEditStyle::~ChatEditStyle() {

}

void ChatEditStyle::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Glyph* line = 0;
	Glyph* nextLine;

	string path;
	string tmpFileName;
	string content;
	string noteContents;
	string printContents;

	Printer printer;

	Long j;
	Long i = 0;
	while (i < this->textEdit->note->GetLength() - 1) {
		line = this->textEdit->note->GetAt(i);
		nextLine = this->textEdit->note->GetAt(i + 1);

		j = 0;
		while (j < line->GetLength()) {
			content = line->GetAt(j)->GetContent();
			if (content.length() == 8) {
				content = '\t';
			}
			noteContents += content;

			j++;
		}
		if (dynamic_cast<DummyLine*>(nextLine) == 0) {
			noteContents += "\r\n";
		}

		i++;
	}
	if (i < this->textEdit->note->GetLength()) {
		line = this->textEdit->note->GetAt(i);
		j = 0;
		while (j < line->GetLength()) {
			content = line->GetAt(j)->GetContent();
			if (content.length() == 8) {
				content = '\t';
			}
			noteContents += content;

			j++;
		}
	}

	this->textEdit->Clear();

	// ���� ������ �����.
	printContents = printer.GetAddedFieldLengthString(noteContents);
	printContents = printer.GetAddedTableLengthString(printContents);

	// ���� �������� ������ �����. <Printer>
	tmpFileName = TEMPPATH;
	tmpFileName += "\\SendChatData.tmp";

	printer.Printing((char*)tmpFileName.c_str(), (char*)printContents.c_str());
}