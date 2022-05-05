// PostingBodyProfile.cpp
/*
���ϸ�Ī : PostingBodyProfile.cpp
��    �� : �Խñ� ���� �̷� Ŭ������ �����Ѵ�.
�� �� �� : ������
�ۼ����� : 2022.05.03
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