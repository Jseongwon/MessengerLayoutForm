// LengthTextMode.cpp
/*
���ϸ�Ī : LengthTextMode.cpp
��    �� : ���� ���� Ŭ������ �����Ѵ�.
�� �� �� : ������
�ۼ����� : 2022.03.24
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

	// 1. ��ȣ�� ���� ���ڰ� �ִµ��� �ݺ��Ѵ�.
	// 1.1. ��ȣ�� ���� ���ڸ� ã�´�.
	parenthesesBegin = tokenString.find('(');
	while (parenthesesBegin != string::npos) {
		// 1.2. ��ȣ�� �� ���ڸ� ã�´�.
		parenthesesEnd = tokenString.find(')', parenthesesBegin);

		// 1.3. ��ȣ�� ������ �д´�.
		contentsInParentheses = tokenString.substr(parenthesesBegin + 1, parenthesesEnd - (parenthesesBegin + 1));

		// 1.4. ���̸� ���Ѵ�.
		strLength = stoi(contentsInParentheses);

		// 1.5. ��ū�� ���̸�ŭ �����.
		strOffset = parenthesesEnd + 1;
		tempToken = tokenString.substr(strOffset, strLength);
		token = tempToken;

		// 1.6. ��ū�� �߰��Ѵ�.
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

	// 2. ��ū ������ ����Ѵ�.
	return this->listToken->length;
}