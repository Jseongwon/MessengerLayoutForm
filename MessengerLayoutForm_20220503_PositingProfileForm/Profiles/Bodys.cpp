// Bodys.cpp
/*
파일명칭 : Bodys.cpp
기    능 : 컴포지트 패턴을 적용한 친구 본문 클래스를 정의한다.
작 성 자 : 정성원
작성일자 : 2022.02.16
*/
#include "Bodys.h"
#include "PostingBodysState.h"
#include "FriendBodysState.h"
#include "ChatBodysState.h"
#include "../Generator/DrawingGenerator.h"
using namespace parkcom;

Bodys::Bodys(Long capacity)
	: Profiles(capacity) {
	this->bodysState = 0;
}

Bodys::Bodys(const Bodys& source)
	: Profiles(source) {
	this->bodysState = 0;
	if (dynamic_cast<PostingBodysState*>(source.bodysState)) {
		this->bodysState = new PostingBodysState(this);
	}
	else if (dynamic_cast<FriendBodysState*>(source.bodysState)) {
		this->bodysState = new FriendBodysState(this);
	}
	else if (dynamic_cast<ChatBodysState*>(source.bodysState)) {
		this->bodysState = new ChatBodysState(this);
	}
}

Bodys::~Bodys() {
	if (this->bodysState != 0) {
		delete this->bodysState;
	}
}

Bodys& Bodys::operator=(const Bodys& source) {
	Profiles::operator=(source);
	if (this->bodysState != 0) {
		delete this->bodysState;
	}
	this->bodysState = 0;
	if (dynamic_cast<PostingBodysState*>(source.bodysState)) {
		this->bodysState = new PostingBodysState(this);
	}
	else if (dynamic_cast<FriendBodysState*>(source.bodysState)) {
		this->bodysState = new FriendBodysState(this);
	}
	else if (dynamic_cast<ChatBodysState*>(source.bodysState)) {
		this->bodysState = new ChatBodysState(this);
	}

	return *this;
}

void Bodys::Accept(DrawingGenerator* drawingGenerator) {
	drawingGenerator->Visit(this);
}

Profile* Bodys::Clone() {
	return new Bodys(*this);
}

void Bodys::Repair(int bodysState) {
	if (this->bodysState != 0) {
		delete this->bodysState;
	}
	this->bodysState = 0;
	if (bodysState == BodysState::POSTING) {
		this->bodysState = new PostingBodysState(this);
	}
	else if (bodysState == BodysState::FRIEND) {
		this->bodysState = new FriendBodysState(this);
	}
	else if (bodysState == BodysState::CHAT) {
		this->bodysState = new ChatBodysState(this);
	}
}

int Bodys::GetBodysState() {
	int bodysState = -1;
	if (dynamic_cast<PostingBodysState*>(this->bodysState)) {
		bodysState = BodysState::POSTING;
	}
	else if (dynamic_cast<FriendBodysState*>(this->bodysState)) {
		bodysState = BodysState::FRIEND;
	}
	else if (dynamic_cast<ChatBodysState*>(this->bodysState)) {
		bodysState = BodysState::CHAT;
	}
	return bodysState;
}