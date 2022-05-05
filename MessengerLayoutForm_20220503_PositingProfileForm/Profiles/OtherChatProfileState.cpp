// OtherChatProfileState.cpp
/*
���ϸ�Ī : OtherChatProfileState.cpp
��    �� : �ٸ� ������� ��ȭ �̷� ���� Ŭ������ �����Ѵ�.
�� �� �� : ������
�ۼ����� : 2022.04.08
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