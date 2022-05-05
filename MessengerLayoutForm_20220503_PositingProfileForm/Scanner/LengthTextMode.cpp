// LengthTextMode.cpp
/*
파일명칭 : LengthTextMode.cpp
기    능 : 길이 편집 클래스를 정의한다.
작 성 자 : 정성원
작성일자 : 2022.03.24
*/
#include "LengthTextMode.h"
#include "ListToken.h"
using namespace parkcom;

LengthTextMode::LengthTextMode(ListToken* listToken)
	: TextMode(listToken) {

}

LengthTextMode::~LengthTextMode() {

}

int LengthTextMode::Scanning(char(*tokens)) {
	Token token;

	string tokenString = tokens;
	string tempToken;
	string contentsInParentheses;

	size_t parenthesesBegin;
	size_t parenthesesEnd;

	size_t strOffset = 0;
	size_t strLength;

	this->listToken->tokens.Clear();
	this->listToken->tokens.Ready(this->listToken->capacity);
	this->listToken->length = 0;

	// 1. 괄호의 시작 문자가 있는동안 반복한다.
	// 1.1. 괄호의 시작 문자를 찾는다.
	parenthesesBegin = tokenString.find('(');
	while (parenthesesBegin != string::npos) {
		// 1.2. 괄호의 끝 문자를 찾는다.
		parenthesesEnd = tokenString.find(')', parenthesesBegin);

		// 1.3. 괄호의 내용을 읽는다.
		contentsInParentheses = tokenString.substr(parenthesesBegin + 1, parenthesesEnd - (parenthesesBegin + 1));

		// 1.4. 길이를 구한다.
		strLength = stoi(contentsInParentheses);

		// 1.5. 토큰을 길이만큼 만든다.
		strOffset = parenthesesEnd + 1;
		tempToken = tokenString.substr(strOffset, strLength);
		token = tempToken;

		// 1.6. 토큰을 추가한다.
		if (this->listToken->length < this->listToken->capacity) {
			this->listToken->tokens.Store(this->listToken->length, token);
		}
		else {
			this->listToken->tokens.AppendFromRear(token);
			this->listToken->capacity++;
		}
		this->listToken->length++;

		strOffset = strOffset + strLength;
		parenthesesBegin = tokenString.find('(', strOffset);
	}
	this->listToken->current = 0;

	// 2. 토큰 개수를 출력한다.
	return this->listToken->length;
}