// DefaultTextMode.h
#ifndef _DEFAULTTEXTMODE_H
#define _DEFAULTTEXTMODE_H
#include "TextMode.h"

namespace parkcom {
	class ListToken;
	class DefaultTextMode : public TextMode {
	public:
		DefaultTextMode(ListToken* listToken);
		virtual ~DefaultTextMode();

		virtual int Scanning(char(*tokens));
	};
}

#endif // _DEFAULTTEXTMODE_H