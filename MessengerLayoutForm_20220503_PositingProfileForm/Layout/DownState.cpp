// DownState.cpp
/*
���ϸ�Ī : DownState.cpp
��    �� : ���� ������ ������ �ٿ� ���� Ŭ������ �����Ѵ�.
�� �� �� : ������
�ۼ����� : 2022.03.16
*/
#include "DownState.h"
#include <string>
using namespace parkcom;
using namespace std;

DownState::DownState() {

}

DownState::~DownState() {

}

char* DownState::GetState() {
	static char buffer[16] = "Down";
	return buffer;
}

DownState::operator char*() {
	static char buffer[16] = "Down";
	return buffer;
}

bool DownState::operator==(char(*cardState)) {
	bool ret = false;
	if (strcmp(cardState, "Down") == 0) {
		ret = true;
	}

	return ret;
}

bool DownState::operator==(int cardState) {
	bool ret = false;
	if (CardState::DOWN == cardState) {
		ret = true;
	}

	return ret;
}

bool DownState::operator!=(char(*cardState)) {
	bool ret = false;
	if (strcmp(cardState, "Down") != 0) {
		ret = true;
	}

	return ret;
}

bool DownState::operator!=(int cardState) {
	bool ret = false;
	if (CardState::DOWN != cardState) {
		ret = true;
	}

	return ret;
}