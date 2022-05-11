// ProfileStyle.cpp
/*
파일명칭 : ProfileStyle.cpp
기    능 : 이력 윈도우의 스타일 클래스를 만든다.
작 성 자 : 정성원
작성일자 : 2022.04.28
*/
#include "ProfileStyle.h"
using namespace parkcom;

ProfileStyle::ProfileStyle(CWnd* pCurrentWnd) {
	this->pCurrentWnd = pCurrentWnd;
	this->onIsDrawing = true;
}

ProfileStyle::~ProfileStyle() {

}