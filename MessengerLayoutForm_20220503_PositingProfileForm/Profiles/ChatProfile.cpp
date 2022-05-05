// ChatProfile.cpp
/*
파일명칭 : ChatProfile.cpp
기    능 : 대화 이력 클래스를 정의한다.
작 성 자 : 정성원
작성일자 : 2022.02.18
*/
#include "ChatProfile.h"
#include "SystemChatProfileState.h"
#include "OneChatProfileState.h"
#include "OtherChatProfileState.h"
#include "../Generator/DrawingGenerator.h"
using namespace parkcom;

ChatProfile::ChatProfile() {
	this->chatProfileState = 0;
}

ChatProfile::ChatProfile(string accountName, string personalName, string attachmentImageUrl, string message, string sentAt)
	: accountName(accountName), personalName(personalName), attachmentImageUrl(attachmentImageUrl), message(message), sentAt(sentAt) {
	this->chatProfileState = new OneChatProfileState(this);
}

ChatProfile::ChatProfile(const ChatProfile& source)
	: accountName(source.accountName), personalName(source.personalName), attachmentImageUrl(source.attachmentImageUrl), message(source.message), sentAt(source.sentAt) {
	this->chatProfileState = 0;
	if (dynamic_cast<OneChatProfileState*>(source.chatProfileState)) {
		this->chatProfileState = new OneChatProfileState(this);
	}
	else if (dynamic_cast<OtherChatProfileState*>(source.chatProfileState)) {
		this->chatProfileState = new OtherChatProfileState(this);
	}
	else if (dynamic_cast<SystemChatProfileState*>(source.chatProfileState)) {
		this->chatProfileState = new SystemChatProfileState(this);
	}
}

ChatProfile::ChatProfile(Builder builder)
	: accountName(builder.accountName), personalName(builder.personalName), attachmentImageUrl(builder.attachmentImageUrl), message(builder.message), sentAt(builder.sentAt) {

}

ChatProfile::~ChatProfile() {
	if (this->chatProfileState != 0) {
		delete this->chatProfileState;
	}
}

ChatProfile& ChatProfile::operator=(const ChatProfile& source) {
	if (this->chatProfileState != 0) {
		delete this->chatProfileState;
	}

	this->chatProfileState = 0;
	if (dynamic_cast<OneChatProfileState*>(source.chatProfileState)) {
		this->chatProfileState = new OneChatProfileState(this);
	}
	else if (dynamic_cast<OtherChatProfileState*>(source.chatProfileState)) {
		this->chatProfileState = new OtherChatProfileState(this);
	}
	else if (dynamic_cast<SystemChatProfileState*>(source.chatProfileState)) {
		this->chatProfileState = new SystemChatProfileState(this);
	}

	this->accountName = source.accountName;
	this->personalName = source.personalName;
	this->attachmentImageUrl = source.attachmentImageUrl;
	this->message = source.message;
	this->sentAt = source.sentAt;

	return *this;
}

bool ChatProfile::operator==(int chatProfileState) {
	return *this->chatProfileState == chatProfileState;
}

void ChatProfile::Accept(DrawingGenerator* drawingGenerator) {
	drawingGenerator->Visit(this);
}

Profile* ChatProfile::Clone() {
	return new ChatProfile(*this);
}

void ChatProfile::SetState(int stateType) {
	if (this->chatProfileState != 0) {
		delete this->chatProfileState;
	}
	if (stateType == ChatProfile::SYSTEM) {
		this->chatProfileState = new SystemChatProfileState(this);
	}
	else if (stateType == ChatProfile::ONE) {
		this->chatProfileState = new OneChatProfileState(this);
	}
	else if (stateType == ChatProfile::OTHER) {
		this->chatProfileState = new OtherChatProfileState(this);
	}
}