// ListToken.cpp
/*
파일명칭 : ListToken.cpp
기    능 : 리스트 토큰 클래스를 정의한다.
작 성 자 : 정성원
작성일자 : 2022.02.18
*/
#include "ListToken.h"
#include "DefaultScanMode.h"
#include "LengthScanMode.h"
using namespace parkcom;

ListToken::ListToken(Long capacity)
	: tokens(capacity) {
	this->capacity = capacity;
	this->length = 0;
	this->current = -1;

	this->scanMode = new DefaultScanMode(this);
}

ListToken::ListToken(string tokens, int scanMode, Long capacity)
	: tokens(capacity) {
	this->capacity = capacity;
	this->length = 0;
	this->current = -1;

	if (scanMode == ListToken::DEFAULT) {
		this->scanMode = new DefaultScanMode(this);
	}
	else if (scanMode == ListToken::LENGTH) {
		this->scanMode = new LengthScanMode(this);
	}
	this->scanMode->Scanning((char*)tokens.c_str());
}

ListToken::ListToken(const ListToken& source)
	: tokens(source.tokens) {
	this->capacity = source.capacity;
	this->length = source.length;
	this->current = source.current;

	if (dynamic_cast<DefaultScanMode*>(source.scanMode)) {
		this->scanMode = new DefaultScanMode(this);
	}
	else if(dynamic_cast<LengthScanMode*>(source.scanMode)) {
		this->scanMode = new LengthScanMode(this);
	}
}

ListToken::~ListToken() {
	if (this->scanMode != 0) {
		delete this->scanMode;
	}
}

ListToken& ListToken::operator=(const ListToken& source) {
	this->tokens = source.tokens;
	this->capacity = source.capacity;
	this->length = source.length;
	this->current = source.current;

	if (this->scanMode != 0) {
		delete this->scanMode;
	}
	if (dynamic_cast<DefaultScanMode*>(source.scanMode)) {
		this->scanMode = new DefaultScanMode(this);
	}
	else if(dynamic_cast<LengthScanMode*>(source.scanMode)) {
		this->scanMode = new LengthScanMode(this);
	}

	return *this;
}

ListToken::operator string() {
	static string contents;
	Long i = 0;
	while (i < this->length - 1) {
		contents += static_cast<string>(this->tokens.GetAt(i)) + " ";
		i++;
	}
	if (i < this->length) {
		contents += static_cast<string>(this->tokens.GetAt(i));
	}
	return contents;
}

Long ListToken::Scanning(string tokens) {
	Long length = 0;
	
	length = this->scanMode->Scanning((char*)tokens.c_str());

	return length;
}

void ListToken::Repair(int scanMode) {
	if (this->scanMode != 0) {
		delete this->scanMode;
		this->scanMode = 0;
	}
	if (scanMode == ListToken::DEFAULT) {
		this->scanMode = new DefaultScanMode(this);
	}
	else if (scanMode == ListToken::LENGTH) {
		this->scanMode = new LengthScanMode(this);
	}
}

void ListToken::Repair(string scanMode) {
	if (this->scanMode != 0) {
		delete this->scanMode;
		this->scanMode = 0;
	}
	if (scanMode == "Default") {
		this->scanMode = new DefaultScanMode(this);
	}
	else if (scanMode == "Length") {
		this->scanMode = new LengthScanMode(this);
	}
}

Token& ListToken::Scan() const {
	Token& token = const_cast<ListToken*>(this)->tokens.GetAt(this->current);
	const_cast<ListToken*>(this)->current++;
	return token;
}