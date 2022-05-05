// BodysState.cpp
/*
파일명칭 : BodysState.cpp
기    능 : 이력을 관리하는 클래스의 상태 클래스를 정의한다.
작 성 자 : 정성원
작성일자 : 2022.04.29
*/
#include "BodysState.h"
using namespace parkcom;

BodysState::BodysState(Bodys* bodys) {
	this->bodys = bodys;
}

BodysState::~BodysState() {

}