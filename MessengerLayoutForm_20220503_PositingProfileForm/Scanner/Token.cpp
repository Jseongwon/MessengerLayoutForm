// Token.cpp
/*
파일명칭 : Token.cpp
기    능 : 토큰 클래스를 정의한다.
작 성 자 : 정성원
작성일자 : 2022.02.17
*/
#include "Token.h"
using namespace parkcom;

Token::Token(string contents)
	: contents(contents) {

}

Token::Token(const Token& source)
	: contents(source.contents) {

}

Token::~Token() {

}

Token& Token::operator=(const Token& source) {
	this->contents = source.contents;

	return *this;
}

Token::operator const string() {
	return this->contents;
}

bool Token::IsDAT() {
	bool ret = false;
	if (contents.length() >= 3 && contents[0] == 'D' && contents[1] == 'A' && contents[2] == 'T') {
		ret = true;
	}

	return ret;
}