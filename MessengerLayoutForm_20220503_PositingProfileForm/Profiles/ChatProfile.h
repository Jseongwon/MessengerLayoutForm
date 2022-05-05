// ChatProfile.h
#ifndef _CHATPROFILE_H
#define _CHATPROFILE_H
#include "Profile.h"

namespace parkcom {
	class ChatProfileState;
	class ChatProfile : public Profile {
		friend class ChatProfileState;

	public:
		enum { SYSTEM = 0, ONE = 1, OTHER = 2 };

	public:
		class Builder {
			friend ChatProfile;
		public:
			Builder() {

			}
			Builder(string personalName, string attachmentImageUrl)
				: personalName(personalName), attachmentImageUrl(attachmentImageUrl) {

			}
			~Builder() {

			}

			Builder* AccountName(string accountName) {
				this->accountName = accountName;
				return this;
			}
			Builder* Message(string message) {
				this->message = message;
				return this;
			}
			Builder* SentAt(string sentAt) {
				this->sentAt = sentAt;
				return this;
			}

			ChatProfile* Build() {
				return new ChatProfile(*this);
			}

		private:
			string accountName;
			string personalName;
			string attachmentImageUrl;
			string message;
			string sentAt;
		};

	public:
		ChatProfile();
		ChatProfile(string accountName, string personalName, string attachmentImageUrl, string message, string sentAt);
		ChatProfile(Builder builder);
		ChatProfile(const ChatProfile& source);
		virtual ~ChatProfile();
		ChatProfile& operator=(const ChatProfile& source);
		bool operator==(int chatProfileState);

		virtual void Accept(DrawingGenerator* drawingGenerator);
		virtual Profile* Clone();

		virtual void SetState(int stateType);

		virtual ChatProfileState* GetChatProfileState() const;
		virtual string GetAccountName();
		virtual string GetPersonalName();
		virtual string GetAttachmentImageUrl();
		virtual string GetCurrentMessage();
		virtual string GetSentAt();

	private:
		ChatProfileState* chatProfileState;

		string accountName;
		string personalName;
		string attachmentImageUrl;
		string message;
		string sentAt;
	};
	inline ChatProfileState* ChatProfile::GetChatProfileState() const {
		return const_cast<ChatProfileState*>(this->chatProfileState);
	}
	inline string ChatProfile::GetAccountName() {
		return this->accountName;
	}
	inline string ChatProfile::GetPersonalName() {
		return this->personalName;
	}
	inline string ChatProfile::GetAttachmentImageUrl() {
		return this->attachmentImageUrl;
	}
	inline string ChatProfile::GetCurrentMessage() {
		return this->message;
	}
	inline string ChatProfile::GetSentAt() {
		return this->sentAt;
	}
}

#endif // _CHATPROFILE_H