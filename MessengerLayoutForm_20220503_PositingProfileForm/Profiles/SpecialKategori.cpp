// SpecialKategori.cpp
/*
���ϸ�Ī : SpecialKategori.cpp
��    �� : �߿��� ī�װ� Ŭ������ �����.
�� �� �� : ������
�ۼ����� : 2022.04.29
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