// ScanMode.cpp
/*
파일명칭 : ScanMode.cpp
기    능 : 편집 클래스를 정의한다.
작 성 자 : 정성원
작성일자 : 2022.03.24
*/
#include "ScanMode.h"
#include "ListToken.h"
using namespace parkcom;

ScanMode::ScanMode(ListToken* listToken) {
	this->listToken = listToken;
}

ScanMode::~ScanMode() {

}