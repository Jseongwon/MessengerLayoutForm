// PostingProfile.cpp
/*
파일명칭 : PostingProfile.cpp
기    능 : 대화 이력 클래스를 정의한다.
작 성 자 : 정성원
작성일자 : 2022.02.18
*/
#include "PostingProfile.h"
#include "NormalKategori.h"
#include "SpecialKategori.h"
#include "../Generator/DrawingGenerator.h"
using namespace parkcom;

PostingProfile::PostingProfile() {
	this->kategori = 0;
}

PostingProfile::PostingProfile(string kategori, string title, string commentCount, string writer, string writedAt, string views)
	: title(title), commentCount(commentCount), writer(writer), writedAt(writedAt), views(views) {
	this->kategori = new NormalKategori(kategori);
}

PostingProfile::PostingProfile(const PostingProfile& source)
	: title(source.title), commentCount(source.commentCount), writer(source.writer), writedAt(source.writedAt), views(source.views) {
	this->kategori = 0;
	if (dynamic_cast<NormalKategori*>(source.kategori)) {
		this->kategori = new NormalKategori(source.kategori->GetName());
	}
	else if (dynamic_cast<SpecialKategori*>(source.kategori)) {
		this->kategori = new SpecialKategori(source.kategori->GetName());
	}
}

PostingProfile::PostingProfile(Builder builder)
	: title(builder.title), commentCount(builder.commentCount), writer(builder.writer), writedAt(builder.writedAt), views(builder.views) {
	this->kategori = new NormalKategori(builder.kategori);
}

PostingProfile::~PostingProfile() {
	if (this->kategori != 0) {
		delete this->kategori;
	}
}

PostingProfile& PostingProfile::operator=(const PostingProfile& source) {
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
	this->commentCount = source.commentCount;
	this->writer = source.writer;
	this->writedAt = source.writedAt;
	this->views = source.views;

	return *this;
}

void PostingProfile::Accept(DrawingGenerator* drawingGenerator) {
	drawingGenerator->Visit(this);
}

Profile* PostingProfile::Clone() {
	return new PostingProfile(*this);
}

void PostingProfile::Repair(int kategoriState) {
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