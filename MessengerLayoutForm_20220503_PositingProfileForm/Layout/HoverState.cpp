// HoverState.cpp
/*
���ϸ�Ī : HoverState.cpp
��    �� : ���� ������ ������ ȣ�� ���� Ŭ������ �����Ѵ�.
�� �� �� : ������
�ۼ����� : 2022.03.16
*/
#include "HoverState.h"
#include <string>
using namespace parkcom;
using namespace std;

HoverState::HoverState() {

}

HoverState::~HoverState() {

}

char* HoverState::GetState() {
	static char buffer[16] = "Hover";
	return buffer;
}

HoverState::operator char*() {
	static char buffer[16] = "Hover";
	return buffer;
}

bool HoverState::operator==(char(*cardState)) {
	bool ret = false;
	if (strcmp(cardState, "Hover") == 0) {
		ret = true;
	}

	return ret;
}

bool HoverState::operator==(int cardState) {
	bool ret = false;
	if (CardState::HOVER == cardState) {
		ret = true;
	}

	return ret;
}

bool HoverState::operator!=(char(*cardState)) {
	bool ret = false;
	if (strcmp(cardState, "Hover") != 0) {
		ret = true;
	}

	return ret;
}

bool HoverState::operator!=(int cardState) {
	bool ret = false;
	if (CardState::HOVER != cardState) {
		ret = true;
	}

	return ret;
}