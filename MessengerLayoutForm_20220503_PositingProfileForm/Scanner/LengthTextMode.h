// LengthTextMode.h
#ifndef _LENGTHTEXTMODE_H
#define _LENGTHTEXTMODE_H
#include "TextMode.h"

namespace parkcom {
	class ListToken;
	class LengthTextMode : public TextMode {
	public:
		LengthTextMode(ListToken* listToken);
		virtual ~LengthTextMode();

		virtual int Scanning(char(*tokens));
	};
}

#endif // _LENGTHTEXTMODE_H