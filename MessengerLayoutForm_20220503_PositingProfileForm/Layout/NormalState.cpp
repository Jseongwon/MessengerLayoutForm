// NormalState.cpp
/*
���ϸ�Ī : NormalState.cpp
��    �� : ���� ������ ������ �Ϲ� ���� Ŭ������ �����Ѵ�.
�� �� �� : ������
�ۼ����� : 2022.03.16
*/
#include "NormalState.h"
#include <string>
using namespace parkcom;
using namespace std;

NormalState::NormalState() {

}

NormalState::~NormalState() {

}

char* NormalState::GetState() {
	static char buffer[16] = "Normal";
	return buffer;
}

NormalState::operator char*() {
	static char buffer[16] = "Normal";
	return buffer;
}

bool NormalState::operator==(char(*cardState)) {
	bool ret = false;
	if (strcmp(cardState, "Normal") == 0) {
		ret = true;
	}

	return ret;
}

bool NormalState::operator==(int cardState) {
	bool ret = false;
	if (CardState::NORMAL == cardState) {
		ret = true;
	}

	return ret;
}

bool NormalState::operator!=(char(*cardState)) {
	bool ret = false;
	if (strcmp(cardState, "Normal") != 0) {
		ret = true;
	}

	return ret;
}

bool NormalState::operator!=(int cardState) {
	bool ret = false;
	if (CardState::NORMAL != cardState) {
		ret = true;
	}

	return ret;
}