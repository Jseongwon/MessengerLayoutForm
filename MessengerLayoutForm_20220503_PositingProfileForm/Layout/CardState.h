// CardState.h
#ifndef _CARDSTATE_H
#define _CARDSTATE_H

namespace parkcom {
	class CardState {
	public:
		enum { NORMAL = 0, DOWN = 1, HOVER = 2 };

	public:
		CardState();
		virtual ~CardState() = 0;

		virtual char* GetState() = 0;
		virtual operator char*() = 0;
		virtual bool operator==(char(*cardState)) = 0;
		virtual bool operator==(int cardState) = 0;
		virtual bool operator!=(char(*cardState)) = 0;
		virtual bool operator!=(int cardState) = 0;
	};
}

#endif // _CARDSTATE_H