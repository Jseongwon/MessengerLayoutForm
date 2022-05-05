// SystemChatProfileState.h
#ifndef _SYSTEMCHATPROFILESTATE_H
#define _SYSTEMCHATPROFILESTATE_H
#include "ChatProfileState.h"

namespace parkcom {
	class SystemChatProfileState : public ChatProfileState {
	public:
		SystemChatProfileState(ChatProfile* chatProfile = 0);
		SystemChatProfileState(const SystemChatProfileState& source);
		virtual ~SystemChatProfileState();
		SystemChatProfileState& operator=(const SystemChatProfileState& source);
		virtual bool operator==(int chatProfileState);

		virtual void Accept(DrawingGenerator* drawingGenerator);
		virtual ChatProfileState* Clone();
	};
}

#endif // _SYSTEMCHATPROFILESTATE_H