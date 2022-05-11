// ChatEditStyle.cpp
/*
파일명칭 : ChatEditStyle.cpp
기    능 : 채팅 편집 스타일 클래스를 정의한다.
작 성 자 : 정성원
작성일자 : 2022.05.11
*/
#include "ChatEditStyle.h"
#include "TextEdit.h"
using namespace parkcom;

ChatEditStyle::ChatEditStyle(TextEdit* textEdit)
	: EditStyle(textEdit) {

}

ChatEditStyle::~ChatEditStyle() {

}