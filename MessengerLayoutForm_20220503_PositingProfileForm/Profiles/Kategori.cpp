// Kategori.cpp
/*
파일명칭 : Kategori.cpp
기    능 : 카테고리 클래스를 만든다.
작 성 자 : 정성원
작성일자 : 2022.04.29
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