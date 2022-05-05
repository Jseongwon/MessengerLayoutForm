// Kategori.cpp
/*
���ϸ�Ī : Kategori.cpp
��    �� : ī�װ� Ŭ������ �����.
�� �� �� : ������
�ۼ����� : 2022.04.29
*/
#include "Kategori.h"
using namespace parkcom;

Kategori::Kategori() {

}

Kategori::Kategori(string name)
	: name(name) {

}

Kategori::Kategori(const Kategori& source)
	: name(source.name) {

}

Kategori::~Kategori() {

}

Kategori& Kategori::operator=(const Kategori& source) {
	this->name = source.name;

	return *this;
}