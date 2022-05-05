// PersonalProfile.cpp
/*
파일명칭 : PersonalProfile.cpp
기    능 : 개인 이력 파일 클래스를 정의한다.
작 성 자 : 정성원
작성일자 : 2022.02.18
*/
#include "PersonalProfile.h"
#include "../Generator/DrawingGenerator.h"
using namespace parkcom;

PersonalProfile::PersonalProfile() {

}

PersonalProfile::PersonalProfile(string accountName, string password, string personalName, string nickname, string attachmentImageUrl, string stateMessage, Long addedLength)
	: accountName(accountName), password(password), personalName(personalName), nickname(nickname), attachmentImageUrl(attachmentImageUrl), stateMessage(stateMessage) {
	this->addedLength = addedLength;
}

PersonalProfile::PersonalProfile(const PersonalProfile& source)
	: accountName(source.accountName), password(source.password), personalName(source.personalName), nickname(source.nickname), attachmentImageUrl(source.attachmentImageUrl),
	stateMessage(source.stateMessage) {
	this->addedLength = source.addedLength;
}

PersonalProfile::PersonalProfile(Builder builder)
	: accountName(builder.accountName), password(builder.password), personalName(builder.personalName), nickname(builder.nickname), attachmentImageUrl(builder.attachmentImageUrl),
	stateMessage(builder.stateMessage) {
	this->addedLength = builder.addedLength;
}

PersonalProfile::~PersonalProfile() {

}

PersonalProfile& PersonalProfile::operator=(const PersonalProfile& source) {
	this->accountName = source.accountName;
	this->password = source.password;
	this->personalName = source.personalName;
	this->nickname = source.nickname;
	this->attachmentImageUrl = source.attachmentImageUrl;
	this->stateMessage = source.stateMessage;
	this->addedLength = source.addedLength;

	return *this;
}

void PersonalProfile::Accept(DrawingGenerator* drawingGenerator) {
	drawingGenerator->Visit(this);
}

Profile* PersonalProfile::Clone() {
	return new PersonalProfile(*this);
}