// NormalKategori.cpp
/*
���ϸ�Ī : NormalKategori.cpp
��    �� : �Ϲ� ī�װ� Ŭ������ �����.
�� �� �� : ������
�ۼ����� : 2022.04.29
*/
#include "NormalKategori.h"
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

Kategori* NormalKategori::Clone() {
	return new NormalKategori(*this);
}