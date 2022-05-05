// PostingBodysState.h
#ifndef _POSTINGBODYSSTATE_H
#define _POSTINGBODYSSTATE_H
#include "BodysState.h"

namespace parkcom {
	class PostingBodysState : public BodysState {
	public:
		PostingBodysState(Bodys* bodys = 0);
		virtual ~PostingBodysState();
	};
}

#endif // _POSTINGBODYSSTATE_H