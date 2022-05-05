// TextMode.cpp
/*
파일명칭 : TextMode.cpp
기    능 : 편집 클래스를 정의한다.
작 성 자 : 정성원
작성일자 : 2022.03.24
*/
#include "TextMode.h"
#include "ListToken.h"
using namespace parkcom;

TextMode::TextMode(ListToken* listToken) {
	this->listToken = listToken;
}

TextMode::~TextMode() {

}