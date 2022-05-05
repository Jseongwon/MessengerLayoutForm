// Profiles.cpp
/*
파일명칭 : Profiles.cpp
기    능 : 컴포지트 패턴을 적용한 이력 클래스를 정의한다.
작 성 자 : 정성원
작성일자 : 2022.02.16
*/
#include "Profiles.h"
using namespace parkcom;

Profiles::Profiles(Long capacity)
	: profiles(capacity) {
	this->capacity = capacity;
	this->length = 0;
	this->current = -1;
}

Profiles::Profiles(const Profiles& source)
	: profiles(source.profiles) {
	Profile* profile;
	Long i = 0;
	while (i < source.length) {
		profile = this->profiles.GetAt(i)->Clone();
		this->profiles.Modify(i, profile);
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
	this->current = source.current;
}

Profiles::~Profiles() {
	Long i = 0;
	while (i < this->length) {
		delete this->profiles.GetAt(i);
		i++;
	}
}

Profiles& Profiles::operator=(const Profiles& source) {
	Profile* profile;
	Long i = 0;
	while (i < this->length) {
		delete this->profiles.GetAt(i);
		i++;
	}
	this->profiles = source.profiles;
	i = 0;
	while (i < source.length) {
		profile = this->profiles.GetAt(i)->Clone();
		this->profiles.Modify(i, profile);
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
	this->current = source.current;

	return *this;
}

Long Profiles::Add(Profile* profile) {
	if (this->length < this->capacity) {
		this->current = this->profiles.Store(this->length, profile);
	}
	else {
		this->current = this->profiles.AppendFromRear(profile);
		this->capacity++;
	}
	this->length++;
	if (this->current < 0) {
		this->current = 0;
	}

	return this->current;
}

Long Profiles::Remove(Profile* index) {
	Long findedIndex;
	findedIndex = this->profiles.LinearSearchUnique(index, CompareProfileLinksInProfiles);
	this->profiles.Delete(findedIndex);
	this->capacity--;
	this->length--;

	return -1;
}

Long Profiles::Change(Long positionOfProfile, Long positionOfDesired) {
	Profile* temp;
	temp = this->profiles.GetAt(positionOfProfile);
	this->profiles.Modify(positionOfProfile, this->profiles.GetAt(positionOfDesired));
	this->current = this->profiles.Modify(positionOfDesired, temp);

	return this->current;
}

Profile* Profiles::GetAt(Long index) {
	return this->profiles.GetAt(index);
}

Long Profiles::Move(Long index) {
	this->current = index;
	if (this->current < 0) {
		this->current = 0;
	}
	else if (this->current >= this->length) {
		this->current = this->length - 1;
	}
	return this->current;
}

int CompareProfileLinksInProfiles(void* one, void* other) {
	Long ret;
	Profile** one_ = (Profile**)one;
	Profile* other_ = (Profile*)other;
	
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