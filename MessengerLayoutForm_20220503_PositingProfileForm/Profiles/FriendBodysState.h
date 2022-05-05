// FriendBodysState.h
#ifndef _FRIENDBODYSSTATE_H
#define _FRIENDBODYSSTATE_H
#include "BodysState.h"

namespace parkcom {
	class FriendBodysState : public BodysState {
	public:
		FriendBodysState(Bodys* bodys = 0);
		virtual ~FriendBodysState();
	};
}

#endif // _FRIENDBODYSSTATE_H