// Observer.cpp
/*
파일명칭 : Observer.cpp
기    능 : 감시자 객체를 만든다.
작성일자 : 2022.01.05
*/
#include "Observer.h"

// Observer
Observer::Observer(Subject* pParentSubject) {
	this->pParentSubject = pParentSubject;
}

Observer::Observer(const Observer& source) {
	this->pParentSubject = source.pParentSubject;
}

Observer::~Observer() {

}

Observer& Observer::operator=(const Observer& source) {
	this->pParentSubject = source.pParentSubject;
	return *this;
}