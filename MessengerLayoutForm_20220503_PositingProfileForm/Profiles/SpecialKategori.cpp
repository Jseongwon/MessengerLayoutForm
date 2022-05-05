// SpecialKategori.cpp
/*
파일명칭 : SpecialKategori.cpp
기    능 : 중요한 카테고리 클래스를 만든다.
작 성 자 : 정성원
작성일자 : 2022.04.29
*/
#include "SpecialKategori.h"
#include "../Generator/DrawingGenerator.h"
using namespace parkcom;

SpecialKategori::SpecialKategori() {

}

SpecialKategori::SpecialKategori(string name)
	: Kategori(name) {

}

SpecialKategori::SpecialKategori(const SpecialKategori& source)
	: Kategori(source) {

}

SpecialKategori::~SpecialKategori() {

}

SpecialKategori& SpecialKategori::operator=(const SpecialKategori& source) {
	Kategori::operator=(source);

	return *this;
}

void SpecialKategori::Accept(DrawingGenerator* drawingGenerator) {
	drawingGenerator->Visit(this);
}

Kategori* SpecialKategori::Clone() {
	return new SpecialKategori(*this);
}