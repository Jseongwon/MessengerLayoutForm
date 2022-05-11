// DefaultScanMode.cpp
/*
파일명칭 : DefaultScanMode.cpp
기    능 : 기본 편집 클래스를 정의한다.
작 성 자 : 정성원
작성일자 : 2022.03.24
*/
#include "DefaultScanMode.h"
#include "ListToken.h"
using namespace parkcom;

DefaultScanMode::DefaultScanMode(ListToken* listToken)
	: ScanMode(listToken) {

}

DefaultScanMode::~DefaultScanMode() {

}

int DefaultScanMode::Scanning(char(*tokens)) {
	Token token;

	string tokenString = tokens;

	size_t strOffset = 0;
	size_t strIndex;

	this->listToken->tokens.Clear();
	this->listToken->tokens.Ready(this->listToken->capacity);
	this->listToken->length = 0;
	this->listToken->current = -1;

	// 1. 탭 문자를 찾는다.
	strIndex = tokenString.find('\t');
	while (strIndex != string::npos) {
		token = tokenString.substr(strOffset, strIndex - strOffset);

		if (this->listToken->length < this->listToken->capacity) {
			this->listToken->tokens.Store(this->listToken->length, token);
		}
		else {
			this->listToken->tokens.AppendFromRear(token);
			this->listToken->capacity++;
		}
		this->listToken->length++;

		strOffset = strIndex + 1;
		strIndex = tokenString.find('\t', strOffset);
	}
	token = tokenString.substr(strOffset, tokenString.length() - strOffset);

	if (this->listToken->length < this->listToken->capacity) {
		this->listToken->tokens.Store(this->listToken->length, token);
	}
	else {
		this->listToken->tokens.AppendFromRear(token);
		this->listToken->capacity++;
	}
	this->listToken->length++;
	this->listToken->current = 0;

	return this->listToken->length;
}