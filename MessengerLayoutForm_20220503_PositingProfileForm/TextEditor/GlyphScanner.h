#ifndef _GLYPHSCANNER_H
#define _GLYPHSCANNER_H

#include <string>

using namespace std;
typedef signed long int Long;

class GlyphScanner {
public:
	GlyphScanner(string pattern);
	GlyphScanner(const GlyphScanner& source);
	~GlyphScanner();
	GlyphScanner& operator=(const GlyphScanner& source);

	string GetToken();
	Long Next();
	bool IsEnd();

	string GetPattern() const;
	Long GetCurrent() const;
	Long GetLength() const;
private:
	string pattern;
	Long current;
	Long length;
};

inline string GlyphScanner::GetPattern() const {
	return this->pattern;
}

inline Long GlyphScanner::GetCurrent() const {
	return this->current;
}

inline Long GlyphScanner::GetLength() const {
	return this->length;
}

#endif // !_SCANNER_H
