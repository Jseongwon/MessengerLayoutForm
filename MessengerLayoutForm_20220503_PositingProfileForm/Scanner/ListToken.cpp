// ListToken.cpp
/*
파일명칭 : ListToken.cpp
기    능 : 리스트 토큰 클래스를 정의한다.
작 성 자 : 정성원
작성일자 : 2022.02.18
*/
#include "ListToken.h"
#include "DefaultTextMode.h"
#include "LengthTextMode.h"
using namespace parkcom;

ListToken::ListToken(Long capacity)
	: tokens(capacity) {
	this->capacity = capacity;
	this->length = 0;
	this->current = -1;

	this->textMode = new DefaultTextMode(this);
}

ListToken::ListToken(string tokens, int textMode, Long capacity)
	: tokens(capacity) {
	this->capacity = capacity;
	this->length = 0;
	this->current = -1;

	if (textMode == ListToken::DEFAULT) {
		this->textMode = new DefaultTextMode(this);
	}
	else if (textMode == ListToken::LENGTH) {
		this->textMode = new LengthTextMode(this);
	}
	this->textMode->Scanning((char*)tokens.c_str());
}

ListToken::ListToken(const ListToken& source)
	: tokens(source.tokens) {
	this->capacity = source.capacity;
	this->length = source.length;
	this->current = source.current;

	if (dynamic_cast<DefaultTextMode*>(source.textMode)) {
		this->textMode = new DefaultTextMode(this);
	}
	else if(dynamic_cast<LengthTextMode*>(source.textMode)) {
		this->textMode = new LengthTextMode(this);
	}
}

ListToken::~ListToken() {
	if (this->textMode != 0) {
		delete this->textMode;
	}
}

ListToken& ListToken::operator=(const ListToken& source) {
	this->tokens = source.tokens;
	this->capacity = source.capacity;
	this->length = source.length;
	this->current = source.current;

	if (this->textMode != 0) {
		delete this->textMode;
	}
	if (dynamic_cast<DefaultTextMode*>(source.textMode)) {
		this->textMode = new DefaultTextMode(this);
	}
	else if(dynamic_cast<LengthTextMode*>(source.textMode)) {
		this->textMode = new LengthTextMode(this);
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
	
	length = this->textMode->Scanning((char*)tokens.c_str());

	return length;
}

void ListToken::Repair(int textMode) {
	if (this->textMode != 0) {
		delete this->textMode;
		this->textMode = 0;
	}
	if (textMode == ListToken::DEFAULT) {
		this->textMode = new DefaultTextMode(this);
	}
	else if (textMode == ListToken::LENGTH) {
		this->textMode = new LengthTextMode(this);
	}
}

void ListToken::Repair(string textMode) {
	if (this->textMode != 0) {
		delete this->textMode;
		this->textMode = 0;
	}
	if (textMode == "Default") {
		this->textMode = new DefaultTextMode(this);
	}
	else if (textMode == "Length") {
		this->textMode = new LengthTextMode(this);
	}
}

Token& ListToken::Scan() const {
	Token& token = const_cast<ListToken*>(this)->tokens.GetAt(this->current);
	const_cast<ListToken*>(this)->current++;
	return token;
}