// TextExtent.h
#ifndef _TEXTEXTENT_H
#define _TEXTEXTENT_H
#include <string>
typedef signed long int Long;
using namespace std;

class CWnd;
class Subject;
class TextExtent {
public:
	TextExtent();
	TextExtent(CWnd* pCurrentWnd);
	TextExtent(const TextExtent& source);
	~TextExtent();
	TextExtent& operator =(const TextExtent& source);
	Long GetWidth(Long index);
	Long GetWidth(char(*text));
	Long GetHeight() const;
	Long GetContentsHeight(string contents);
	Long GetContentsRowLength(string sourceContents);
	Long GetContentsRowLength(string sourceContents, Long totalWidth);
	Long GetContentsWidth(string contents);
	Long GetContentsWidth(string contents, Long lfHeight, Long lfWidth, string lfFaceName);
	void WrappingContents(string sourceContents, Long totalWidth, string* wrappingContents, Long* wrappingCount = 0, Long* longestWidth = 0);

private:
	CWnd* pCurrentWnd;
	Subject* subject;
	Long(*widths);
	Long height;
};

inline Long TextExtent::GetHeight() const {
	return this->height;
}

#endif // _TEXTEXTENT_H