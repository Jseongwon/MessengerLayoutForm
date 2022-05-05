// DownState.cpp
/*
파일명칭 : DownState.cpp
기    능 : 상태 패턴을 적용한 다운 상태 클래스를 정의한다.
작 성 자 : 정성원
작성일자 : 2022.03.16
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