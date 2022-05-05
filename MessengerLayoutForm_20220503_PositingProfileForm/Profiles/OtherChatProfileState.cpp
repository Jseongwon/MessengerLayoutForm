// OtherChatProfileState.cpp
/*
파일명칭 : OtherChatProfileState.cpp
기    능 : 다른 사용자의 대화 이력 상태 클래스를 정의한다.
작 성 자 : 정성원
작성일자 : 2022.04.08
*/
#include "OtherChatProfileState.h"
#include "ChatProfile.h"
#include "../Generator/DrawingGenerator.h"
using namespace parkcom;

OtherChatProfileState::OtherChatProfileState(ChatProfile* chatProfile)
	: ChatProfileState(chatProfile) {

}

OtherChatProfileState::OtherChatProfileState(const OtherChatProfileState& source)
	: ChatProfileState(source) {

}

OtherChatProfileState::~OtherChatProfileState() {

}

OtherChatProfileState& OtherChatProfileState::operator=(const OtherChatProfileState& source) {
	ChatProfileState::operator=(source);
	return *this;
}

bool OtherChatProfileState::operator==(int chatProfileState) {
	return ChatProfile::OTHER == chatProfileState;
}

void OtherChatProfileState::Accept(DrawingGenerator* drawingGenerator) {
	drawingGenerator->Visit(this);
}

ChatProfileState* OtherChatProfileState::Clone() {
	return new OtherChatProfileState(*this);
}