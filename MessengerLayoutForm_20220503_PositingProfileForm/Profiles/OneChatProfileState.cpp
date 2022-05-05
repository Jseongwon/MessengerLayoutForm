// OneChatProfileState.cpp
/*
���ϸ�Ī : OneChatProfileState.cpp
��    �� : ������� ��ȭ �̷� ���� Ŭ������ �����Ѵ�.
�� �� �� : ������
�ۼ����� : 2022.04.08
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