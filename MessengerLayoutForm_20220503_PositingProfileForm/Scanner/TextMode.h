// TextMode.h
#ifndef _TEXTMODE_H
#define _TEXTMODE_H

namespace parkcom {
	class ListToken;
	class TextMode {
	public:
		TextMode(ListToken* listToken);
		virtual ~TextMode() = 0;

		virtual int Scanning(char(*tokens)) = 0;

	protected:
		ListToken* listToken;
	};
}

#endif // _TEXTMODE_H