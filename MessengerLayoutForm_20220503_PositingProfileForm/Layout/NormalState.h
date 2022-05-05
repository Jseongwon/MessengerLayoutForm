// NormalState.h
#ifndef _NORMALSTATE_H
#define _NORMALSTATE_H
#include "CardState.h"

namespace parkcom {
	class NormalState : public CardState {
	public:
		NormalState();
		virtual ~NormalState();
		virtual char* GetState();
		virtual operator char*();
		virtual bool operator==(char(*cardState));
		virtual bool operator==(int cardState);
		virtual bool operator!=(char(*cardState));
		virtual bool operator!=(int cardState);
	};
}

#endif // _NORMALSTATE_H