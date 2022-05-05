// Observer.cpp
/*
���ϸ�Ī : Observer.cpp
��    �� : ������ ��ü�� �����.
�ۼ����� : 2022.01.05
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