// HoverState.cpp
/*
파일명칭 : HoverState.cpp
기    능 : 상태 패턴을 적용한 호버 상태 클래스를 정의한다.
작 성 자 : 정성원
작성일자 : 2022.03.16
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