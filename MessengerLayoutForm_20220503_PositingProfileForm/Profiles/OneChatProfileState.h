// OneChatProfileState.h
#ifndef _ONECHATPROFILESTATE_H
#define _ONECHATPROFILESTATE_H
#include "ChatProfileState.h"

namespace parkcom {
	class OneChatProfileState : public ChatProfileState {
	public:
		OneChatProfileState(ChatProfile* chatProfile = 0);
		OneChatProfileState(const OneChatProfileState& source);
		virtual ~OneChatProfileState();
		OneChatProfileState& operator=(const OneChatProfileState& source);
		virtual bool operator==(int chatProfileState);

		virtual void Accept(DrawingGenerator* drawingGenerator);
		virtual ChatProfileState* Clone();
	};
}

#endif // _ONECHATPROFILESTATE_H