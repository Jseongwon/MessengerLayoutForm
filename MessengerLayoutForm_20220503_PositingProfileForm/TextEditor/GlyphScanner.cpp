#include "GlyphScanner.h"

GlyphScanner::GlyphScanner(string pattern)
	: pattern(pattern) {
	this->current = 0;
	this->length = pattern.length();
}

GlyphScanner::GlyphScanner(const GlyphScanner& source)
	: pattern(source.pattern) {
	this->current = source.current;
	this->length = source.length;
}

GlyphScanner::~GlyphScanner() {

}

GlyphScanner& GlyphScanner::operator=(const GlyphScanner& source) {
	this->pattern = source.pattern;
	this->current = source.current;
	this->length = source.length;

	return *this;
}

string GlyphScanner::GetToken() {
	string token = "";

	if (!(this->pattern[current] & 0x80) && !(this->pattern[current] == '\r' && this->pattern[current + 1] == '\n')) {
		token = pattern.substr(current, 1);
	}
	else {
		token = pattern.substr(current, 2);
	}

	return token;
}

Long GlyphScanner::Next() {
	if (this->current < this->length) {
		if (!(this->pattern[current] & 0x80) && !(this->pattern[current] == '\r' && this->pattern[current + 1] == '\n')) {
			this->current++;
		}
		else {
			this->current += 2;
		}
	}
	return this->current;
}

bool GlyphScanner::IsEnd() {
	bool ret = false;
	if (current >= length)
	{
		ret = true;
	}

	return ret;
}

/*
#include "File.h"
#include "GlyphScanner.h"
#include "GlyphFactory.h"
#include "Note.h"
#include "Glyph.h"

int main(int argc, char *argv[]) {
	GlyphFactory glyphFactory;
	Glyph *note = glyphFactory.Make("");
	Glyph *glyph = glyphFactory.Make("\r\n");
	Glyph *line;

	Long index = note->Add(glyph); //�� ���� �����.
	line = note->GetAt(index); //���� ���� �ּҸ� �����´�.

	glyph = glyphFactory.Make("a"); //a�� �Է¹޴´�.
	index = line->Add(glyph); //a�� ���� �ٿ� �߰��Ѵ�.
	glyph = line->GetAt(index); //�߰��� ������ �ּҸ� �����´�.

	glyph = glyphFactory.Make("��"); //���� �Է¹޴´�.
	index = line->Add(glyph); //���� ���� �ٿ� �߰��Ѵ�.

	glyph = glyphFactory.Make("\r\n"); //����Ű�� �Է¹޴´�.
	index = note->Add(glyph); //�� ���� �����.
	line = note->GetAt(index); //���� ���� �ּҸ� �����´�.
	glyph = glyphFactory.Make("1"); //3�� �Է¹޴´�.
	index = line->Add(glyph); //3�� ���� �ٿ� �߰��Ѵ�.

	glyph = glyphFactory.Make("��"); //���� �Է¹޴´�.
	index = line->Add(glyph); //���� ���� �ٿ� �߰��Ѵ�.
	glyph = line->GetAt(index); //�߰��� ������ �ּҸ� �����´�.

	glyph = glyphFactory.Make("\r\n");
	note->Add(glyph);

	File fileOut("test.txt", ios_base::out);
	fileOut.Save(note->GetContent());

	File fileIn("test.txt", ios_base::in);

	string content;
	content = fileIn.Load();
	Glyph *anotherNote = glyphFactory.Make("");
	line = glyphFactory.Make("\r\n");
	anotherNote->Add(line);

	GlyphScanner scanner(content);

	while (!scanner.IsEnd()) {
		string token = scanner.GetToken();
		glyph = glyphFactory.Make(token.c_str());

		if (token != "\r\n") {
			line->Add(glyph);
		}
		else {
			anotherNote->Add(glyph);
			line = glyph;
		}

		scanner.Next();
	}

	content = anotherNote->GetContent();
	cout << content << endl;

	if (note != 0) {
		delete note;
	}

	if (anotherNote != 0) {
		delete anotherNote;
	}
}
*/