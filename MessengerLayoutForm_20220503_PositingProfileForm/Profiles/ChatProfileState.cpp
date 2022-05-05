// ChatProfileStateState.cpp
/*
파일명칭 : ChatProfileState.cpp
기    능 : 대화 이력 상태 클래스를 정의한다.
작 성 자 : 정성원
작성일자 : 2022.04.08
*/
#include "ChatProfileState.h"
#include "ChatProfile.h"
#include "../Generator/DrawingGenerator.h"
using namespace parkcom;

ChatProfileState::ChatProfileState(ChatProfile* chatProfile) {
	this->chatProfile = chatProfile;
}

ChatProfileState::ChatProfileState(const ChatProfileState& source) {
	this->chatProfile = source.chatProfile;
}

ChatProfileState::~ChatProfileState() {

}

ChatProfileState& ChatProfileState::operator=(const ChatProfileState& source) {
	this->chatProfile = source.chatProfile;
	return *this;
}