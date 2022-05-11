#include "GlyphMaker.h"
#include "GlyphScanner.h"
#include "GlyphFactory.h"
#include "Glyph.h"

GlyphMaker::GlyphMaker() {

}

GlyphMaker::GlyphMaker(const GlyphMaker& source) {

}

GlyphMaker::~GlyphMaker() {

}

GlyphMaker& GlyphMaker::operator=(const GlyphMaker& source) {
	return *this;
}

Glyph* GlyphMaker::Make(string content) {
	GlyphFactory glyphFactory;
	Glyph* note = glyphFactory.Make("");
	Glyph* line = glyphFactory.Make("\r\n");
	note->Add(line);
	Glyph* glyph;
	string token;
	GlyphScanner glyphScanner(content);
	while (glyphScanner.IsEnd() == false) {
		token = glyphScanner.GetToken();
		if (token != "\r\n") {
			glyph = glyphFactory.Make(token.c_str());
			line->Add(glyph);
		}
		else {
			glyph = glyphFactory.Make(token.c_str());
			Long index = note->Add(glyph);
			line = note->GetAt(index);
		}
		glyphScanner.Next();
	}

	return note;
}

Glyph* GlyphMaker::MakeChatNote(Glyph* chatNote, string content) {
	GlyphFactory glyphFactory;
	Glyph* line = glyphFactory.Make("\r\n");
	Glyph* glyph;

	string token;
	GlyphScanner glyphScanner(content);

	Long index;

	chatNote->Add(line);
	while (glyphScanner.IsEnd() == false) {
		token = glyphScanner.GetToken();
		if (token != "\r\n") {
			glyph = glyphFactory.Make(token.c_str());
			line->Add(glyph);
		}
		else {
			glyph = glyphFactory.Make(token.c_str());
			index = chatNote->Add(glyph);
			line = chatNote->GetAt(index);
		}
		glyphScanner.Next();
	}

	return chatNote;
}