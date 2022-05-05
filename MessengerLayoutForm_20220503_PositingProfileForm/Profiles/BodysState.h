// BodysState.h
#ifndef _BODYSSTATE_H
#define _BODYSSTATE_H

namespace parkcom {
	class Bodys;
	class BodysState {
	public:
		enum { POSTING = 0, FRIEND = 1, CHAT = 2 };
	public:
		BodysState(Bodys* bodys = 0);
		virtual ~BodysState() = 0;

	protected:
		Bodys* bodys;
	};
}

#endif // _BODYSSTATE_H