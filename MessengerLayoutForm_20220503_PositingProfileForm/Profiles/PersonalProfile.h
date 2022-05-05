// PersonalProfile.h
#ifndef _PERSONALPROFILE_H
#define _PERSONALPROFILE_H
#include "Profile.h"

namespace parkcom {
	class PersonalProfile : public Profile {
	public:
		class Builder {
			friend PersonalProfile;
		public:
			Builder() {

			}
			~Builder() {

			}

			Builder* AccountName(string accountName) {
				this->accountName = accountName;
				return this;
			}
			Builder* Password(string password) {
				this->password = password;
				return this;
			}
			Builder* PersonalName(string personalName) {
				this->personalName = personalName;
				return this;
			}
			Builder* Nickname(string nickname) {
				this->nickname = nickname;
				return this;
			}
			Builder* AttachmentImageUrl(string attachmentImageUrl) {
				this->attachmentImageUrl = attachmentImageUrl;
				return this;
			}
			Builder* StateMessage(string stateMessage) {
				this->stateMessage = stateMessage;
				return this;
			}
			Builder* AddedLength(Long addedLength) {
				this->addedLength = addedLength;
				return this;
			}
			PersonalProfile* Build() {
				return new PersonalProfile(*this);
			}

		private:
			string accountName;
			string password;
			string personalName;
			string nickname;
			string attachmentImageUrl;
			string stateMessage;
			Long addedLength;
		};

	public:
		PersonalProfile();
		PersonalProfile(string accountName, string password, string personalName, string nickname, string attachmentImageUrl, string stateMessage, Long addedLength);
		PersonalProfile(const PersonalProfile& source);
		PersonalProfile(Builder builder);
		virtual ~PersonalProfile();
		PersonalProfile& operator=(const PersonalProfile& source);

		virtual void Accept(DrawingGenerator* drawingGenerator);
		virtual Profile* Clone();

		virtual string GetAccountName();
		virtual string GetPassword();
		virtual string GetPersonalName();
		virtual string GetNickname();
		virtual string GetAttachmentImageUrl();
		virtual string GetStateMessage();
		virtual Long GetAddedLength();

	private:
		string accountName;
		string password;
		string personalName;
		string nickname;
		string attachmentImageUrl;
		string stateMessage;
		Long addedLength;
	};
	inline string PersonalProfile::GetAccountName() {
		return this->accountName;
	}
	inline string PersonalProfile::GetPassword() {
		return this->password;
	}
	inline string PersonalProfile::GetPersonalName() {
		return this->personalName;
	}
	inline string PersonalProfile::GetNickname() {
		return this->nickname;
	}
	inline string PersonalProfile::GetAttachmentImageUrl() {
		return this->attachmentImageUrl;
	}
	inline string PersonalProfile::GetStateMessage() {
		return this->stateMessage;
	}
	inline Long PersonalProfile::GetAddedLength() {
		return this->addedLength;
	}
}

#endif // _PERSONALPROFILE_H