// NormalState.cpp
/*
파일명칭 : NormalState.cpp
기    능 : 상태 패턴을 적용한 일반 상태 클래스를 정의한다.
작 성 자 : 정성원
작성일자 : 2022.03.16
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