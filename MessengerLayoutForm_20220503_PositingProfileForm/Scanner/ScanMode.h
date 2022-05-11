// ScanMode.h
#ifndef _SCANMODE_H
#define _SCANMODE_H

namespace parkcom {
	class ListToken;
	class ScanMode {
	public:
		ScanMode(ListToken* listToken);
		virtual ~ScanMode() = 0;

		virtual int Scanning(char(*tokens)) = 0;

	protected:
		ListToken* listToken;
	};
}

#endif // _SCANMODE_H