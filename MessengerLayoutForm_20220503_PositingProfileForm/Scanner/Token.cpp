// Token.cpp
/*
���ϸ�Ī : Token.cpp
��    �� : ��ū Ŭ������ �����Ѵ�.
�� �� �� : ������
�ۼ����� : 2022.02.17
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