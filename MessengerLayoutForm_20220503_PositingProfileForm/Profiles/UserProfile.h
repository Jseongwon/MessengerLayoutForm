// UserProfile.h
#ifndef _USERPROFILE_H
#define _USERPROFILE_H
#include "Profile.h"

namespace parkcom {
	class UserProfile : public Profile {
	public:
		class Builder {
			friend UserProfile;
		public:
			Builder() {

			}
			~Builder() {

			}
			Builder* AccountName(string accountName) {
				this->accountName = accountName;
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

			UserProfile* Build() {
				return new UserProfile(*this);
			}

		private:
			string accountName;
			string personalName;
			string nickname;
			string attachmentImageUrl;
		};

	public:
		UserProfile();
		UserProfile(string accountName, string personalName, string nickname, string attachmentImageUrl);
		UserProfile(const UserProfile& source);
		UserProfile(Builder builder);
		virtual ~UserProfile();
		UserProfile& operator=(const UserProfile& source);

		virtual void Accept(DrawingGenerator* drawingGenerator);
		virtual Profile* Clone();

		virtual string GetAccountName();
		virtual string GetPersonalName();
		virtual string GetNickname();
		virtual string GetAttachmentImageUrl();

	private:
		string accountName;
		string personalName;
		string nickname;
		string attachmentImageUrl;
	};
	inline string UserProfile::GetAccountName() {
		return this->accountName;
	}
	inline string UserProfile::GetPersonalName() {
		return this->personalName;
	}
	inline string UserProfile::GetNickname() {
		return this->nickname;
	}
	inline string UserProfile::GetAttachmentImageUrl() {
		return this->attachmentImageUrl;
	}
}

#endif // _CHATPROFILE_H