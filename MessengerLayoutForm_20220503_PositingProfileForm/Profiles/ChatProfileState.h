// ChatProfileState.h
#ifndef _CHATPROFILESTATE_H
#define _CHATPROFILESTATE_H
#include "ChatProfile.h"

namespace parkcom {
	class ChatProfile;
	class DrawingGenerator;
	class ChatProfileState {
	public:
		ChatProfileState(ChatProfile* chatProfile = 0);
		ChatProfileState(const ChatProfileState& source);
		virtual ~ChatProfileState() = 0;
		ChatProfileState& operator=(const ChatProfileState& source);
		virtual bool operator==(int chatProfileState) { return false; }

		virtual void Accept(DrawingGenerator* drawingGenerator) = 0;
		virtual ChatProfileState* Clone() = 0;

		virtual string GetAccountName();
		virtual string GetPersonalName();
		virtual string GetAttachmentImageUrl();
		virtual string GetCurrentMessage();
		virtual string GetSentAt();

	protected:
		ChatProfile* chatProfile;
	};
	inline string ChatProfileState::GetAccountName() {
		return this->chatProfile->GetAccountName();
	}
	inline string ChatProfileState::GetPersonalName() {
		return this->chatProfile->GetPersonalName();
	}
	inline string ChatProfileState::GetAttachmentImageUrl() {
		return this->chatProfile->GetAttachmentImageUrl();
	}
	inline string ChatProfileState::GetCurrentMessage() {
		return this->chatProfile->GetCurrentMessage();
	}
	inline string ChatProfileState::GetSentAt() {
		return this->chatProfile->GetSentAt();
	}
}

#endif // _CHATPROFILESTATE_H