// Subject.cpp
/*
파일명칭 : Subject.cpp
기    능 : 서브젝트 객체(클래스)를 만든다.
작성일자 : 2022.01.05
*/
#include "Subject.h"
#include "Observer.h"
#include "TextExtent.h"

// SubjectState
SubjectState::SubjectState() {
	this->textExtent = 0;
}

SubjectState::SubjectState(const SubjectState& source) {
	
}

SubjectState::~SubjectState() {
	if (this->textExtent != 0) {
		delete this->textExtent;
	}
}

SubjectState& SubjectState::operator=(const SubjectState& source) {

	return *this;
}

// Subject
Subject::Subject(Long capacity)
	: observers(capacity) {
	this->subjectState = 0;
	this->capacity = capacity;
	this->length = 0;
}

Subject::Subject(const Subject& source)
	: observers(source.observers) {
	Long i = 0;
	this->subjectState = source.subjectState->Clone();
	while (i < source.length) {
		this->observers.Modify(i, const_cast<Subject&>(source).observers.GetAt(i)->Clone());
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
}

Subject::~Subject() {
	Long i = 0;
	if (this->subjectState) {
		delete this->subjectState;
	}
	while (i < this->length) {
		delete this->observers.GetAt(i);
		i++;
	}
}

Subject& Subject::operator=(const Subject& source) {
	Long i = 0;
	if (this->subjectState) {
		delete this->subjectState;
	}
	this->subjectState = source.subjectState->Clone();
	while (i < this->length) {
		delete this->observers.GetAt(i);
		i++;
	}
	this->observers = source.observers;
	i = 0;
	while (i < source.length) {
		this->observers.Modify(i, const_cast<Subject&>(source).observers.GetAt(i)->Clone());
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}

Long Subject::Attach(Observer* observer) {
	Long index;
	if (this->length < this->capacity) {
		index = this->observers.Store(this->length, observer);
	}
	else {
		index = this->observers.AppendFromRear(observer);
		this->capacity++;
	}
	this->length++;

	return index;
}

Long Subject::Find(Long type) {
	Long index = -1;
	Long i = 0;

	Long itType;
	while (i < this->length && index <= -1) {
		itType = this->observers.GetAt(i)->GetType();
		if (itType == type) {
			index = i;
		}
		i++;
	}

	return index;
}

Long Subject::Detach(Observer* observer) {
	Long index;
	index = this->observers.LinearSearchUnique(observer, CompareObserversInSubject);

	if (index > -1) {
		delete observer;
		this->observers.Delete(index);
		this->capacity--;
		this->length--;
	}
	return -1;
}

void Subject::Notify() {
	Long i = 0;
	while (i < this->length) {
		this->observers.GetAt(i)->Update();
		i++;
	}
}

int CompareObserversInSubject(void* one, void* other) {
	int ret;
	Observer** one_ = (Observer**)one;
	Observer* other_ = (Observer*)other;

	if (*one_ < other_) {
		ret = -1;
	}
	else if (*one_ == other_) {
		ret = 0;
	}
	else if (*one_ > other_) {
		ret = 1;
	}
	return ret;
}