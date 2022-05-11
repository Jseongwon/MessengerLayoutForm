// LengthScanMode.h
#ifndef _LENGTHSCANMODE_H
#define _LENGTHSCANMODE_H
#include "ScanMode.h"

namespace parkcom {
	class ListToken;
	class LengthScanMode : public ScanMode {
	public:
		LengthScanMode(ListToken* listToken);
		virtual ~LengthScanMode();

		virtual int Scanning(char(*tokens));
	};
}

#endif // _LENGTHSCANMODE_H