// SystemChatProfileState.cpp
/*
파일명칭 : SystemChatProfileState.cpp
기    능 : 시스템의 대화 이력 상태 클래스를 정의한다.
작 성 자 : 정성원
작성일자 : 2022.04.08
*/
#include "SystemChatProfileState.h"
#include "ChatProfile.h"
#include "../Generator/DrawingGenerator.h"
using namespace parkcom;

SystemChatProfileState::SystemChatProfileState(ChatProfile* chatProfile)
	: ChatProfileState(chatProfile) {

}

SystemChatProfileState::SystemChatProfileState(const SystemChatProfileState& source)
	: ChatProfileState(source) {

}

SystemChatProfileState::~SystemChatProfileState() {

}

SystemChatProfileState& SystemChatProfileState::operator=(const SystemChatProfileState& source) {
	ChatProfileState::operator=(source);
	return *this;
}

bool SystemChatProfileState::operator==(int chatProfileState) {
	return ChatProfile::SYSTEM == chatProfileState;
}

void SystemChatProfileState::Accept(DrawingGenerator* drawingGenerator) {
	drawingGenerator->Visit(this);
}

ChatProfileState* SystemChatProfileState::Clone() {
	return new SystemChatProfileState(*this);
}