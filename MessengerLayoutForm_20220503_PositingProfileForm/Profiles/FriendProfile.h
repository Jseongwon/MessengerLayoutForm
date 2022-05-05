// FriendProfile.h
#ifndef _FRIENDPROFILE_H
#define _FRIENDPROFILE_H
#include "Profile.h"

namespace parkcom {
	class FriendProfile : public Profile {
	public:
		class Builder {
			friend FriendProfile;
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
			Builder* StateMessage(string stateMessage) {
				this->stateMessage = stateMessage;
				return this;
			}
			Builder* AddedAt(string addedAt) {
				this->addedAt = addedAt;
				return this;
			}
			Builder* RoomID(string roomID) {
				this->roomID = roomID;
				return this;
			}
			Builder* LastChatMember(string roomID) {
				this->roomID = roomID;
				return this;
			}
			Builder* LastChatLogID(string lastChatLogID) {
				this->lastChatLogID = lastChatLogID;
				return this;
			}
			Builder* MessageType(string messageType) {
				this->messageType = messageType;
				return this;
			}
			Builder* LastMessage(string lastMessage) {
				this->lastMessage = lastMessage;
				return this;
			}
			Builder* LastUpdateAt(string lastUpdateAt) {
				this->lastUpdateAt = lastUpdateAt;
				return this;
			}
			Builder* UnreadCount(string unreadCount) {
				this->unreadCount = unreadCount;
				return this;
			}

			FriendProfile* Build() {
				return new FriendProfile(*this);
			}

		private:
			string accountName;
			string personalName;
			string nickname;
			string attachmentImageUrl; // ģ���� �̷� �̹���
			string stateMessage;
			string addedAt; // ���� �߰��� ��¥
			string roomID; // �� ID
			string lastChatMember; // ���������� ��ȭ�� ������� ������
			string lastChatLogID; // ���������� ��ȭ�� ������ ID
			string messageType; // �޽��� ũ���� Ÿ��
			string lastMessage;
			string lastUpdateAt; // ���������� ��ȭ�� ��¥
			string unreadCount; // ���� ���� �޽��� ��
		};

	public:
		FriendProfile();
		FriendProfile(string accountName, string personalName, string nickname, string attachmentImageUrl, string stateMessage, string addedAt,
			string roomID, string lastChatMember, string lastChatLogID, string messageType, string lastMessage, string lastUpdateAt, string unreadCount);
		FriendProfile(const FriendProfile& source);
		FriendProfile(Builder builder);
		virtual ~FriendProfile();
		FriendProfile& operator=(const FriendProfile& source);

		virtual void Accept(DrawingGenerator* drawingGenerator);
		virtual Profile* Clone();

		virtual string GetAccountName();
		virtual string GetPersonalName();
		virtual string GetNickname();
		virtual string GetAttachmentImageUrl();
		virtual string GetStateMessage();
		virtual string GetAddedAt();
		virtual string GetRoomID();
		virtual string GetLastChatMember();
		virtual string GetLastChatLogID();
		virtual string GetMessageType();
		virtual string GetLastMessage();
		virtual string GetLastUpdateAt();
		virtual string GetUnreadCount();

	private:
		string accountName;
		string personalName;
		string nickname;
		string attachmentImageUrl; // ģ���� �̷� �̹���
		string stateMessage;
		string addedAt; // ���� �߰��� ��¥
		string roomID; // �� ID
		string lastChatMember; // ���������� ��ȭ�� ������� ������
		string lastChatLogID; // ���������� ��ȭ�� ������ ID
		string messageType; // �޽��� ũ���� Ÿ��
		string lastMessage;
		string lastUpdateAt; // ���������� ��ȭ�� ��¥
		string unreadCount; // ���� ���� �޽��� ��
	};
	inline string FriendProfile::GetAccountName() {
		return this->accountName;
	}
	inline string FriendProfile::GetPersonalName() {
		return this->personalName;
	}
	inline string FriendProfile::GetNickname() {
		return this->nickname;
	}
	inline string FriendProfile::GetAttachmentImageUrl() {
		return this->attachmentImageUrl;
	}
	inline string FriendProfile::GetStateMessage() {
		return this->stateMessage;
	}
	inline string FriendProfile::GetAddedAt() {
		return this->addedAt;
	}
	inline string FriendProfile::GetRoomID() {
		return this->roomID;
	}
	inline string FriendProfile::GetLastChatMember() {
		return this->lastChatMember;
	}
	inline string FriendProfile::GetLastChatLogID() {
		return this->lastChatLogID;
	}
	inline string FriendProfile::GetMessageType() {
		return this->messageType;
	}
	inline string FriendProfile::GetLastMessage() {
		return this->lastMessage;
	}
	inline string FriendProfile::GetLastUpdateAt() {
		return this->lastUpdateAt;
	}
	inline string FriendProfile::GetUnreadCount() {
		return this->unreadCount;
	}
}

#endif // _FRIENDPROFILE_H