// OneChatProfileState.cpp
/*
파일명칭 : OneChatProfileState.cpp
기    능 : 사용자의 대화 이력 상태 클래스를 정의한다.
작 성 자 : 정성원
작성일자 : 2022.04.08
*/
#include "OneChatProfileState.h"
#include "ChatProfile.h"
#include "../Generator/DrawingGenerator.h"
using namespace parkcom;

OneChatProfileState::OneChatProfileState(ChatProfile* chatProfile)
	: ChatProfileState(chatProfile) {

}
OneChatProfileState::OneChatProfileState(const OneChatProfileState& source)
	: ChatProfileState(source) {

}

OneChatProfileState::~OneChatProfileState() {

}

OneChatProfileState& OneChatProfileState::operator=(const OneChatProfileState& source) {
	ChatProfileState::operator=(source);
	return *this;
}

bool OneChatProfileState::operator==(int chatProfileState) {
	return ChatProfile::ONE == chatProfileState;
}

void OneChatProfileState::Accept(DrawingGenerator* drawingGenerator) {
	drawingGenerator->Visit(this);
}

ChatProfileState* OneChatProfileState::Clone() {
	return new OneChatProfileState(*this);
}