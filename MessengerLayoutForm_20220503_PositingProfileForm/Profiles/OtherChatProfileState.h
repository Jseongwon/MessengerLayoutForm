// OtherChatProfileState.h
#ifndef _OTHERCHATPROFILESTATE_H
#define _OTHERCHATPROFILESTATE_H
#include "ChatProfileState.h"

namespace parkcom {
	class OtherChatProfileState : public ChatProfileState {
	public:
		OtherChatProfileState(ChatProfile* chatProfile = 0);
		OtherChatProfileState(const OtherChatProfileState& source);
		virtual ~OtherChatProfileState();
		OtherChatProfileState& operator=(const OtherChatProfileState& source);
		virtual bool operator==(int chatProfileState);

		virtual void Accept(DrawingGenerator* drawingGenerator);
		virtual ChatProfileState* Clone();
	};
}

#endif // _OTHERCHATPROFILESTATE_H