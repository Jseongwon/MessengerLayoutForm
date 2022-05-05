// PostingCommentProfile.cpp
/*
���ϸ�Ī : PostingCommentProfile.cpp
��    �� : �Խñ� ��� �̷� Ŭ������ �����Ѵ�.
�� �� �� : ������
�ۼ����� : 2022.05.03
*/
#include "PostingCommentProfile.h"
#include "../Generator/DrawingGenerator.h"
using namespace parkcom;

PostingCommentProfile::PostingCommentProfile() {

}

PostingCommentProfile::PostingCommentProfile(string attachmentImageUrl, string writer, string comment, string writedAt)
	: attachmentImageUrl(attachmentImageUrl), writer(writer), comment(comment), writedAt(writedAt) {

}

PostingCommentProfile::PostingCommentProfile(const PostingCommentProfile& source)
	: attachmentImageUrl(source.attachmentImageUrl), writer(source.writer), comment(source.comment), writedAt(source.writedAt) {

}

PostingCommentProfile::PostingCommentProfile(Builder builder)
	: attachmentImageUrl(builder.attachmentImageUrl), writer(builder.writer), comment(builder.comment), writedAt(builder.writedAt) {

}

PostingCommentProfile::~PostingCommentProfile() {

}

PostingCommentProfile& PostingCommentProfile::operator=(const PostingCommentProfile& source) {
	this->attachmentImageUrl = source.attachmentImageUrl;
	this->writer = source.writer;
	this->comment = source.comment;
	this->writedAt = source.writedAt;

	return *this;
}

void PostingCommentProfile::Accept(DrawingGenerator* drawingGenerator) {
	drawingGenerator->Visit(this);
}

Profile* PostingCommentProfile::Clone() {
	return new PostingCommentProfile(*this);
}