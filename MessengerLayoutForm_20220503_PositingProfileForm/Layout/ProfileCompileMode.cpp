// ProfileCompileMode.cpp
/*
파일명칭 : ProfileCompileMode.cpp
기    능 : 컴파일모드 클래스를 정의한다.
작 성 자 : 정성원
작성일자 : 2022.03.24
*/
#include "ProfileCompileMode.h"
#include "ProfileCompiler.h"
using namespace parkcom;

ProfileCompileMode::ProfileCompileMode(ProfileCompiler* profileCompiler) {
	this->profileCompiler = profileCompiler;
}

ProfileCompileMode::~ProfileCompileMode() {

}