// PostingHeaderProfile.cpp
/*
파일명칭 : PostingHeaderProfile.cpp
기    능 : 게시글 헤더 이력 클래스를 정의한다.
작 성 자 : 정성원
작성일자 : 2022.05.03
*/
#include "PostingHeaderProfile.h"
#include "NormalKategori.h"
#include "SpecialKategori.h"
#include "../Generator/DrawingGenerator.h"
using namespace parkcom;

PostingHeaderProfile::PostingHeaderProfile() {
	this->kategori = 0;
}

PostingHeaderProfile::PostingHeaderProfile(string kategori, string title, string attachmentImageUrl, string writer, string writerGrade, string writedAt, string views)
	: title(title), attachmentImageUrl(attachmentImageUrl), writer(writer), writerGrade(writerGrade), writedAt(writedAt), views(views) {
	this->kategori = new NormalKategori(kategori);
}

PostingHeaderProfile::PostingHeaderProfile(const PostingHeaderProfile& source)
	: title(source.title), attachmentImageUrl(source.attachmentImageUrl), writer(source.writer), writerGrade(source.writerGrade), writedAt(source.writedAt), views(source.views) {
	this->kategori = 0;
	if (dynamic_cast<NormalKategori*>(source.kategori)) {
		this->kategori = new NormalKategori(source.kategori->GetName());
	}
	else if (dynamic_cast<SpecialKategori*>(source.kategori)) {
		this->kategori = new SpecialKategori(source.kategori->GetName());
	}
}

PostingHeaderProfile::PostingHeaderProfile(Builder builder)
	: title(builder.title), attachmentImageUrl(builder.attachmentImageUrl), writer(builder.writer), writerGrade(builder.writerGrade), writedAt(builder.writedAt), views(builder.views) {
	this->kategori = new NormalKategori(builder.kategori);
}

PostingHeaderProfile::~PostingHeaderProfile() {
	if (this->kategori != 0) {
		delete this->kategori;
	}
}

PostingHeaderProfile& PostingHeaderProfile::operator=(const PostingHeaderProfile& source) {
	if (this->kategori != 0) {
		delete this->kategori;
	}
	this->kategori = 0;
	if (dynamic_cast<NormalKategori*>(source.kategori)) {
		this->kategori = new NormalKategori(source.kategori->GetName());
	}
	else if (dynamic_cast<SpecialKategori*>(source.kategori)) {
		this->kategori = new SpecialKategori(source.kategori->GetName());
	}

	this->title = source.title;
	this->attachmentImageUrl = source.attachmentImageUrl;
	this->writer = source.writer;
	this->writerGrade = source.writerGrade;
	this->writedAt = source.writedAt;
	this->views = source.views;

	return *this;
}

void PostingHeaderProfile::Accept(DrawingGenerator* drawingGenerator) {
	drawingGenerator->Visit(this);
}

Profile* PostingHeaderProfile::Clone() {
	return new PostingHeaderProfile(*this);
}

void PostingHeaderProfile::Repair(int kategoriState) {
	string kategori;
	if (this->kategori != 0) {
		kategori = this->kategori->GetName();
		delete this->kategori;
	}
	this->kategori = 0;
	if (kategoriState == Kategori::NORMAL) {
		this->kategori = new NormalKategori(kategori);
	}
	else if (kategoriState == Kategori::SPECIAL) {
		this->kategori = new SpecialKategori(kategori);
	}
}