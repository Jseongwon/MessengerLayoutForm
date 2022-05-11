// EditStyle.cpp
/*
파일명칭 : EditStyle.cpp
기    능 : 편집기 스타일 클래스를 정의한다.
작 성 자 : 정성원
작성일자 : 2022.05.11
*/
#include "EditStyle.h"
using namespace parkcom;

EditStyle::EditStyle(TextEdit* textEdit) {
	this->textEdit = textEdit;
}

EditStyle::~EditStyle() {

}