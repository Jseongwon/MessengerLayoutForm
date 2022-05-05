// PostingBodyProfile.cpp
/*
파일명칭 : PostingBodyProfile.cpp
기    능 : 게시글 본문 이력 클래스를 정의한다.
작 성 자 : 정성원
작성일자 : 2022.05.03
*/
#include "PostingBodyProfile.h"
#include "../Generator/DrawingGenerator.h"
using namespace parkcom;

PostingBodyProfile::PostingBodyProfile() {
	
}

PostingBodyProfile::PostingBodyProfile(string contents)
	: contents(contents) {
	
}

PostingBodyProfile::PostingBodyProfile(const PostingBodyProfile& source)
	: contents(source.contents) {
	
}

PostingBodyProfile::~PostingBodyProfile() {
	
}

PostingBodyProfile& PostingBodyProfile::operator=(const PostingBodyProfile& source) {
	this->contents = source.contents;

	return *this;
}

void PostingBodyProfile::Accept(DrawingGenerator* drawingGenerator) {
	drawingGenerator->Visit(this);
}

Profile* PostingBodyProfile::Clone() {
	return new PostingBodyProfile(*this);
}