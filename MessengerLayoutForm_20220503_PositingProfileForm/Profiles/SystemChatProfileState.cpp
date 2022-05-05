// SystemChatProfileState.cpp
/*
���ϸ�Ī : SystemChatProfileState.cpp
��    �� : �ý����� ��ȭ �̷� ���� Ŭ������ �����Ѵ�.
�� �� �� : ������
�ۼ����� : 2022.04.08
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