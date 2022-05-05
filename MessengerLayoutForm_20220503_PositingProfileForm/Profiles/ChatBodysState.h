// ChatBodysState.h
#ifndef _CHATBODYSSTATE_H
#define _CHATBODYSSTATE_H
#include "BodysState.h"

namespace parkcom {
	class ChatBodysState : public BodysState {
	public:
		ChatBodysState(Bodys* bodys = 0);
		virtual ~ChatBodysState();
	};
}

#endif // _CHATBODYSSTATE_H