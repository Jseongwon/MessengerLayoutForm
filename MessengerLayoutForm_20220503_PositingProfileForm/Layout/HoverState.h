// HoverState.h
#ifndef _HOVERSTATE_H
#define _HOVERSTATE_H
#include "CardState.h"

namespace parkcom {
	class HoverState : public CardState {
	public:
		HoverState();
		virtual ~HoverState();
		virtual char* GetState();
		virtual operator char*();
		virtual bool operator==(char(*cardState));
		virtual bool operator==(int cardState);
		virtual bool operator!=(char(*cardState));
		virtual bool operator!=(int cardState);
	};
}

#endif // _HOVERSTATE_H