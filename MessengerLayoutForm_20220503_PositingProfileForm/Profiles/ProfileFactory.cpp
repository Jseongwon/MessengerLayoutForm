// ProfileFactory.cpp
/*
���ϸ�Ī : ProfileFactory.cpp
��    �� : ���� ������ ������ �̷� ���� Ŭ������ �����Ѵ�.
�� �� �� : ������
�ۼ����� : 2022.02.21
*/
#include "ProfileFactory.h"
#include "PostingProfile.h"
#include "PersonalProfile.h"
#include "FriendProfile.h"
#include "ChatProfile.h"
#include "Bodys.h"
using namespace parkcom;

ProfileFactory::ProfileFactory() {

}

ProfileFactory::~ProfileFactory() {

}

Profile* ProfileFactory::CreatePostingProfile(string kategori, string title, string commentCount, string writer, string writedAt, string views) {
	return new PostingProfile(kategori, title, commentCount, writer, writedAt, views);
}

Profile* ProfileFactory::CreatePersonalProfile(string accountName, string password, string personalName, string nickname, string attachmentImageUrl, string stateMessage, Long addedLength) {
	return new PersonalProfile(accountName, password, personalName, nickname, attachmentImageUrl, stateMessage, addedLength);
}

Profile* ProfileFactory::CreateFriendProfile(string accountName, string personalName, string nickname, string attachmentImageUrl, string stateMessage, string addedAt,
	string roomID, string lastChatMember, string lastChatLogID, string messageType, string lastMessage, string lastUpdateAt, string unreadCount) {
	return new FriendProfile(accountName, personalName, nickname, attachmentImageUrl, stateMessage, addedAt, roomID, lastChatMember, lastChatLogID, messageType, lastMessage,
		lastUpdateAt, unreadCount);
}

Profile* ProfileFactory::CreateChatProfile(string accountName, string personalName, string attachmentImageUrl, string message, string sentAt) {
	return new ChatProfile(accountName, personalName, attachmentImageUrl, message, sentAt);
}

Profile* ProfileFactory::CreateBodys() {
	return new Bodys;
}