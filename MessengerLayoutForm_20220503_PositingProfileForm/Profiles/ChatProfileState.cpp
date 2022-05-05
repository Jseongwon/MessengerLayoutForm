// ChatProfileStateState.cpp
/*
���ϸ�Ī : ChatProfileState.cpp
��    �� : ��ȭ �̷� ���� Ŭ������ �����Ѵ�.
�� �� �� : ������
�ۼ����� : 2022.04.08
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