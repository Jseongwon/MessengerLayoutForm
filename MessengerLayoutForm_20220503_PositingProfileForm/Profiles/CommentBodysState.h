// CommentBodysState.h
#ifndef _COMMENTBODYSSTATE_H
#define _COMMENTBODYSSTATE_H
#include "BodysState.h"

namespace parkcom {
	class CommentBodysState : public BodysState {
	public:
		CommentBodysState(Bodys* bodys = 0);
		virtual ~CommentBodysState();
	};
}

#endif // _COMMENTBODYSSTATE_H