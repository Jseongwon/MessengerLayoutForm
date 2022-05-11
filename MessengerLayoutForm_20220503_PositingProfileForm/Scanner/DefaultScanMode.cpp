// DefaultScanMode.cpp
/*
���ϸ�Ī : DefaultScanMode.cpp
��    �� : �⺻ ���� Ŭ������ �����Ѵ�.
�� �� �� : ������
�ۼ����� : 2022.03.24
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

	// 1. �� ���ڸ� ã�´�.
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