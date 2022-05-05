// NormalKategori.cpp
/*
���ϸ�Ī : NormalKategori.cpp
��    �� : �Ϲ� ī�װ� Ŭ������ �����.
�� �� �� : ������
�ۼ����� : 2022.04.29
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