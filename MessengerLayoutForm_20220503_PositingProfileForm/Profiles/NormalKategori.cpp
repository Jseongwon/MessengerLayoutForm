// NormalKategori.cpp
/*
파일명칭 : NormalKategori.cpp
기    능 : 일반 카테고리 클래스를 만든다.
작 성 자 : 정성원
작성일자 : 2022.04.29
*/
#include "NormalKategori.h"
#include "../Generator/DrawingGenerator.h"
using namespace parkcom;

NormalKategori::NormalKategori() {

}

NormalKategori::NormalKategori(string name)
	: Kategori(name) {

}

NormalKategori::NormalKategori(const NormalKategori& source)
	: Kategori(source) {

}

NormalKategori::~NormalKategori() {

}

NormalKategori& NormalKategori::operator=(const NormalKategori& source) {
	Kategori::operator=(source);

	return *this;
}

void NormalKategori::Accept(DrawingGenerator* drawingGenerator) {
	drawingGenerator->Visit(this);
}

Kategori* NormalKategori::Clone() {
	return new NormalKategori(*this);
}