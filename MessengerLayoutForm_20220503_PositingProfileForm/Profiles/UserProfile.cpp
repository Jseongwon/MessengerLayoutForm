// UserProfile.cpp
/*
파일명칭 : UserProfile.cpp
기    능 : 사용자 이력 파일 클래스를 정의한다.
작 성 자 : 정성원
작성일자 : 2022.02.18
*/
#include "UserProfile.h"
#include "../Generator/DrawingGenerator.h"
using namespace parkcom;

UserProfile::UserProfile() {

}

UserProfile::UserProfile(string accountName, string personalName, string nickname, string attachmentImageUrl)
	: accountName(accountName), personalName(personalName), nickname(nickname), attachmentImageUrl(attachmentImageUrl) {

}

UserProfile::UserProfile(const UserProfile& source)
	: accountName(source.accountName), personalName(source.personalName), nickname(source.nickname), attachmentImageUrl(source.attachmentImageUrl) {

}

UserProfile::UserProfile(Builder builder)
	: accountName(builder.accountName), personalName(builder.personalName), nickname(builder.nickname), attachmentImageUrl(builder.attachmentImageUrl) {

}

UserProfile::~UserProfile() {

}

UserProfile& UserProfile::operator=(const UserProfile& source) {
	this->accountName = source.accountName;
	this->personalName = source.personalName;
	this->nickname = source.nickname;
	this->attachmentImageUrl = source.attachmentImageUrl;

	return *this;
}

void UserProfile::Accept(DrawingGenerator* drawingGenerator) {
	//drawingGenerator->Visit(this);
}

Profile* UserProfile::Clone() {
	return new UserProfile(*this);
}