// DownState.h
#ifndef _DOWNSTATE_H
#define _DOWNSTATE_H
#include "CardState.h"

namespace parkcom {
	class DownState : public CardState {
	public:
		DownState();
		virtual ~DownState();
		virtual char* GetState();
		virtual operator char*();
		virtual bool operator==(char(*cardState));
		virtual bool operator==(int cardState);
		virtual bool operator!=(char(*cardState));
		virtual bool operator!=(int cardState);
	};
}

#endif // _DOWNSTATE_H