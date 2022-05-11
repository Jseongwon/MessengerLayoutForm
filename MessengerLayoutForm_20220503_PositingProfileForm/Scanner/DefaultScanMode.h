// DefaultScanMode.h
#ifndef _DEFAULTSCANMODE_H
#define _DEFAULTSCANMODE_H
#include "ScanMode.h"

namespace parkcom {
	class ListToken;
	class DefaultScanMode : public ScanMode {
	public:
		DefaultScanMode(ListToken* listToken);
		virtual ~DefaultScanMode();

		virtual int Scanning(char(*tokens));
	};
}

#endif // _DEFAULTSCANMODE_H