// FriendProfile.cpp
/*
파일명칭 : FriendProfile.cpp
기    능 : 친구 이력 파일 클래스를 정의한다.
작 성 자 : 정성원
작성일자 : 2022.02.18
*/
#include "FriendProfile.h"
#include "../Generator/DrawingGenerator.h"
using namespace parkcom;

FriendProfile::FriendProfile() {

}

FriendProfile::FriendProfile(string accountName, string personalName, string nickname, string attachmentImageUrl, string stateMessage, string addedAt,
	string roomID, string lastChatMember, string lastChatLogID, string messageType, string lastMessage, string lastUpdateAt, string unreadCount)
	: accountName(accountName), personalName(personalName), nickname(nickname), attachmentImageUrl(attachmentImageUrl), stateMessage(stateMessage),
	addedAt(addedAt), roomID(roomID), lastChatMember(lastChatMember), lastChatLogID(lastChatLogID), messageType(messageType), lastMessage(lastMessage),
	lastUpdateAt(lastUpdateAt), unreadCount(unreadCount) {

}

FriendProfile::FriendProfile(const FriendProfile& source)
	: accountName(source.accountName), personalName(source.personalName), nickname(source.nickname), attachmentImageUrl(source.attachmentImageUrl), stateMessage(source.stateMessage),
	addedAt(source.addedAt), roomID(source.roomID), lastChatMember(source.lastChatMember), lastChatLogID(source.lastChatLogID), messageType(source.messageType),
	lastMessage(source.lastMessage), lastUpdateAt(source.lastUpdateAt), unreadCount(source.unreadCount) {

}

FriendProfile::FriendProfile(Builder builder)
	: accountName(builder.accountName), personalName(builder.personalName), nickname(builder.nickname), attachmentImageUrl(builder.attachmentImageUrl), stateMessage(builder.stateMessage),
	addedAt(builder.addedAt), roomID(builder.roomID), lastChatMember(builder.lastChatMember), lastChatLogID(builder.lastChatLogID), messageType(builder.messageType),
	lastMessage(builder.lastMessage), lastUpdateAt(builder.lastUpdateAt), unreadCount(builder.unreadCount) {

}

FriendProfile::~FriendProfile() {

}

FriendProfile& FriendProfile::operator=(const FriendProfile& source) {
	this->accountName = source.accountName;
	this->personalName = source.personalName;
	this->nickname = source.nickname;
	this->attachmentImageUrl = source.attachmentImageUrl;
	this->stateMessage = source.stateMessage;
	this->addedAt = source.addedAt;
	this->roomID = source.roomID;
	this->lastChatMember = source.lastChatMember;
	this->lastChatLogID = source.lastChatLogID;
	this->messageType = source.messageType;
	this->lastMessage = source.lastMessage;
	this->lastUpdateAt = source.lastUpdateAt;
	this->unreadCount = source.unreadCount;

	return *this;
}

void FriendProfile::Accept(DrawingGenerator* drawingGenerator) {
	drawingGenerator->Visit(this);
}

Profile* FriendProfile::Clone() {
	return new FriendProfile(*this);
}