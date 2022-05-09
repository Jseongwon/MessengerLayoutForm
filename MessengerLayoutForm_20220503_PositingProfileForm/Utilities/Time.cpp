// Time.h
/*
파일명칭 : Time.h
기능 : 시간 클래스를 만든다.
작성일자 : 2021.06.14
*/
#include "Time.h"
#include <ctime>
#include <cstdio>
#pragma warning(disable:4996)

Time::Time() {
	this->hour = 0;
	this->minute = 0;
	this->second = 0;
}

Time::Time(int hour, int minute, int second) {
	this->hour = hour;
	this->minute = minute;
	this->second = second;
}

Time::Time(const Time& source) {
	this->hour = source.hour;
	this->minute = source.minute;
	this->second = source.second;
}

Time::Time(char(*time)) {
	sscanf(time, "%02d%02d%02d", &this->hour, &this->minute, &this->second);
}

Time::~Time() {

}

Time& Time::operator =(const Time& source) {
	this->hour = source.hour;
	this->minute = source.minute;
	this->second = source.second;

	return *this;
}

Time::operator char*() {
	static char buffer[7];

	sprintf(buffer, "%02d%02d%02d", this->hour, this->minute, this->second);

	return buffer;
}

Time Time::GetNowTime() {
	time_t timer;
	struct tm *nowTime = { 0, };
	Time nowTime_;

	time(&timer);
	nowTime = localtime(&timer);
	nowTime_.hour = nowTime->tm_hour;
	nowTime_.minute = nowTime->tm_min;
	nowTime_.second = nowTime->tm_sec;

	return nowTime_;
}

string Time::GetConvertTimeKoreanString() {
	char buffer[32];
	char tmp[5];
	// 오전 00:00
	if (this->hour < 12) {
		sprintf_s(tmp, 5, "오전");
	}
	else {
		sprintf_s(tmp, 5, "오후");
	}

	sprintf_s(buffer, 32, "%s %02d:%02d", tmp, this->hour, this->minute);

	return buffer;
}

string Time::GetConvertTimeFormatString(char insertCharacter) {
	char buffer[32];
	sprintf_s(buffer, 32, "%02d%c%02d%c%02d", this->hour, insertCharacter, this->minute, insertCharacter, this->second);
	return buffer;
}