// Date.cpp
/*
파일명칭 :  Date.cpp
기능 : 날짜 클래스를 정의하고 테스트한다.
작성자 : 정성원
작성일자 : 2019.12.26
*/
#include "Date.h"
#include <ctime>
#include <iostream>
#include <cstdio>
#pragma warning(disable:4996)

using namespace std;

Date::Date() {
	this->year = 1900;
	this->month = JAN;
	this->day = 1;
	this->weekDay = MON;
}

Date::Date(int year, Month month, int day) {
	struct tm date = { 0, };

	date.tm_year = year - 1900;
	date.tm_mon = month - 1;
	date.tm_mday = day;
	mktime(&date);

	this->year = date.tm_year + 1900;
	this->month = static_cast<Month>(date.tm_mon + 1);
	this->day = date.tm_mday;
	this->weekDay = static_cast<WeekDay>(date.tm_wday);
}

Date::Date(char(*date)) {
	struct tm date_ = { 0, };
	sscanf(date, "%04d%02d%02d", &this->year, &this->month, &this->day);
	date_.tm_year = this->year - 1900;
	date_.tm_mon = this->month - 1;
	date_.tm_mday = this->day;
	mktime(&date_);

	this->year = date_.tm_year + 1900;
	this->month = static_cast<Month>(date_.tm_mon + 1);
	this->day = date_.tm_mday;
	this->weekDay = static_cast<WeekDay>(date_.tm_wday);
}
Date::Date(const Date& source) {
	this->year = source.year;
	this->month = source.month;
	this->day = source.day;
	this->weekDay = source.weekDay;
}
Date::~Date() {
}

/*
명칭 : Today
기능 : 오늘 날짜를 구한다.
입력 : X
출력 : Date
*/
Date Date::Today() {
	time_t timer;
	struct tm *today = { 0, };
	Date today_;

	time(&timer);
	today = localtime(&timer);
	today_.year = today->tm_year + 1900;
	today_.month = static_cast<Month>(today->tm_mon + 1);
	today_.day = today->tm_mday;
	today_.weekDay = static_cast<WeekDay>(today->tm_wday);

	return today_;
}

/*
명칭 : Yesterday
기능 : 어제 날짜를 구한다.
입력 : X
출력 : 날짜
*/
Date Date::Yesterday() {
	struct tm yesterday = { 0, };
	Date yesterday_;

	yesterday.tm_year = this->year - 1900;
	yesterday.tm_mon = this->month - 1;
	yesterday.tm_mday = this->day - 1;
	mktime(&yesterday);

	yesterday_.year = yesterday.tm_year + 1900;
	yesterday_.month = static_cast<Month>(yesterday.tm_mon + 1);
	yesterday_.day = yesterday.tm_mday;
	yesterday_.weekDay = static_cast<WeekDay>(yesterday.tm_wday);

	return yesterday_;
}

/*
명칭 : Tomorrow
기능 : 내일 날짜를 구한다.
입력 : X
출력 : 날짜
*/
Date Date::Tomorrow() {
	struct tm tomorrow = { 0, };
	Date tomorrow_;

	tomorrow.tm_year = this->year - 1900;
	tomorrow.tm_mon = this->month - 1;
	tomorrow.tm_mday = this->day + 1;
	mktime(&tomorrow);

	tomorrow_.year = tomorrow.tm_year + 1900;
	tomorrow_.month = static_cast<Month>(tomorrow.tm_mon + 1);
	tomorrow_.day = tomorrow.tm_mday;
	tomorrow_.weekDay = static_cast<WeekDay>(tomorrow.tm_wday);

	return tomorrow_;
}

/*
명칭 : PreviousDate
기능 : 이전 날짜를 구한다.
입력 : 일 수
출력 : 날짜
*/
Date Date::PreviousDate(int days) {
	struct tm previousDay = { 0, };
	Date previousDay_;

	previousDay.tm_year = this->year - 1900;
	previousDay.tm_mon = this->month - 1;
	previousDay.tm_mday = this->day - days;
	mktime(&previousDay);

	previousDay_.year = previousDay.tm_year + 1900;
	previousDay_.month = static_cast<Month>(previousDay.tm_mon + 1);
	previousDay_.day = previousDay.tm_mday;
	previousDay_.weekDay = static_cast<WeekDay>(previousDay.tm_wday);

	return previousDay_;
}

/*
명칭 : NextDate
기능 : 다음 날짜를 구한다.
입력 : 일 수
출력 : 날짜
*/
Date Date::NextDate(int days) {
	struct tm nextDay = { 0, };
	Date nextDay_;

	nextDay.tm_year = this->year - 1900;
	nextDay.tm_mon = this->month - 1;
	nextDay.tm_mday = this->day + days;
	mktime(&nextDay);

	nextDay_.year = nextDay.tm_year + 1900;
	nextDay_.month = static_cast<Month>(nextDay.tm_mon + 1);
	nextDay_.day = nextDay.tm_mday;
	nextDay_.weekDay = static_cast<WeekDay>(nextDay.tm_wday);

	return nextDay_;
}

/*
명칭 : IsEqual
기능 : 다른 날짜와 같은지 비교한다.
입력 : other
출력 : is
*/
bool Date::IsEqual(const Date& other) {
	bool is = false;

	if (this->year == other.year && this->month == other.month && this->day == other.day) {
		is = true;
	}

	return is;
}

/*
명칭 : IsNotEqual
기능 : 다른 날짜와 다른지 비교한다.
입력 : other
출력 : is
*/
bool Date::IsNotEqual(const Date& other) {
	bool is = false;

	if (this->year != other.year || this->month != other.month || this->day != other.day) {
		is = true;
	}

	return is;
}

/*
명칭 : IsGreaterThan
기능 : 다른 날짜보다 큰지 비교한다.
입력 : other
출력 : is
*/
bool Date::IsGreaterThan(const Date& other) {
	bool is = false;

	if (this->year > other.year) {
		is = true;
	}
	else if (this->year == other.year && this->month > other.month) {
		is = true;
	}
	else if (this->year == other.year && this->month == other.month && this->day > other.day) {
		is = true;
	}

	return is;
}

/*
명칭 : IsLessThan
기능 : 다른 날짜보다 작은지 비교한다.
입력 : other
출력 : is
*/
bool Date::IsLessThan(const Date& other) {
	bool is = false;

	if (this->year < other.year) {
		is = true;
	}
	else if (this->year == other.year && this->month < other.month) {
		is = true;
	}
	else if (this->year == other.year && this->month == other.month && this->day < other.day) {
		is = true;
	}

	return is;
}

/*
명칭 : GetAt
기능 : 날짜에서 읽는다.
입력 : X
출력 : 날짜
*/
string Date::GetAt() {
	string date;
	date += to_string(this->year);
	date += to_string(this->month);
	date += "0";
	date += to_string(this->day);

	return date;
}

/*
명칭 : GetConvertDateKoreanString
기능 : 날짜에서 변환하여 읽는다.
입력 : X
출력 : 날짜 문자열
*/
string Date::GetConvertDateKoreanString() {
	char buffer[32];
	char weekDay[3];
	if (this->weekDay == SUN) {
		sprintf_s(weekDay, 3, "일");
	}
	else if (this->weekDay == MON) {
		sprintf_s(weekDay, 3, "월");
	}
	else if (this->weekDay == TUE) {
		sprintf_s(weekDay, 3, "화");
	}
	else if (this->weekDay == WED) {
		sprintf_s(weekDay, 3, "수");
	}
	else if (this->weekDay == THU) {
		sprintf_s(weekDay, 3, "목");
	}
	else if (this->weekDay == FRI) {
		sprintf_s(weekDay, 3, "금");
	}
	else if (this->weekDay == SAT) {
		sprintf_s(weekDay, 3, "토");
	}
	sprintf_s(buffer, 32, "%04d년 %2d월 %2d일 %s요일", this->year, this->month, this->day, weekDay);

	return buffer;
}

/*
명칭 : operator char*
기능 : char* 형변환 연산을 만든다.
입력 : insertCharaacter
출력 : 날짜 형식 문자열
*/
string Date::GetConvertDateFormatString(char insertCharacter) {
	char buffer[32];
	sprintf_s(buffer, 32, "%04d%c%02d%c%02d", this->year, insertCharacter, this->month, insertCharacter, this->day);

	return buffer;
}

/*
명칭 : operator char*
기능 : char* 형변환 연산을 만든다.
입력 : X
출력 : buffer
*/
Date::operator char *() {
	static char buffer[9];
	sprintf(buffer, "%4d%02d%02d", this->year, this->month, this->day);

	return buffer;
}

/*
명칭 : operator =
기능 : = 연산자를 정의한다.
입력 : source
출력 : 날짜
*/
Date& Date::operator =(const Date& source) {
	this->year = source.year;
	this->month = source.month;
	this->day = source.day;
	this->weekDay = source.weekDay;

	return *this;
}

/*
명칭 : operator --
기능 : 전위 -- 연산자를 정의한다.
입력 : X
출력 : this(this 나 실행하는 곳에 변수가 있을 경우 출력값을 참조형으로 사용하는 것이 효율적이다.)
*/
Date& Date::operator --() {
	struct tm date = { 0, };

	date.tm_year = this->year - 1900;
	date.tm_mon = this->month - 1;
	date.tm_mday = this->day - 1;
	mktime(&date);

	this->year = date.tm_year + 1900;
	this->month = static_cast<Month>(date.tm_mon + 1);
	this->day = date.tm_mday;
	this->weekDay = static_cast<WeekDay>(date.tm_wday);

	return *this;
}

/*
명칭 : operator --
기능 : 후위 -- 연산자를 정의한다.
입력 : X
출력 : 날짜(값)
*/
Date Date::operator --(int) {
	struct tm date = { 0, };
	Date date_(*this);

	date.tm_year = this->year - 1900;
	date.tm_mon = this->month - 1;
	date.tm_mday = this->day - 1;
	mktime(&date);

	this->year = date.tm_year + 1900;
	this->month = static_cast<Month>(date.tm_mon + 1);
	this->day = date.tm_mday;
	this->weekDay = static_cast<WeekDay>(date.tm_wday);

	return date_;
}

/*
명칭 : operator ++
기능 : 전위 ++ 연산자를 정의한다.
입력 : X
출력 : this
*/
Date& Date::operator ++() {
	struct tm date = { 0, };

	date.tm_year = this->year - 1900;
	date.tm_mon = this->month - 1;
	date.tm_mday = this->day + 1;
	mktime(&date);

	this->year = date.tm_year + 1900;
	this->month = static_cast<Month>(date.tm_mon + 1);
	this->day = date.tm_mday;
	this->weekDay = static_cast<WeekDay>(date.tm_wday);

	return *this;
}

/*
명칭 : operator ++
기능 : 후위 ++ 연산자를 정의한다.
입력 : X
출력 : 날짜(값)
*/
Date Date::operator ++(int) {
	struct tm date = { 0, };
	Date date_(*this);

	date.tm_year = this->year - 1900;
	date.tm_mon = this->month - 1;
	date.tm_mday = this->day + 1;
	mktime(&date);

	this->year = date.tm_year + 1900;
	this->month = static_cast<Month>(date.tm_mon + 1);
	this->day = date.tm_mday;
	this->weekDay = static_cast<WeekDay>(date.tm_wday);

	return date_;
}

/*
명칭 : operator -
기능 : - 연산자를 정의한다.
입력 : 일 수
출력 : 날짜
*/
Date Date::operator -(int days) {
	struct tm minusDay = { 0, };
	Date minusDay_;

	minusDay.tm_year = this->year - 1900;
	minusDay.tm_mon = this->month - 1;
	minusDay.tm_mday = this->day - days;
	mktime(&minusDay);

	minusDay_.year = minusDay.tm_year + 1900;
	minusDay_.month = static_cast<Month>(minusDay.tm_mon + 1);
	minusDay_.day = minusDay.tm_mday;
	minusDay_.weekDay = static_cast<WeekDay>(minusDay.tm_wday);

	return minusDay_;
}

/*
명칭 : operator +
기능 : + 연산자를 정의한다.
입력 : 일 수
출력 : 날짜
*/
Date Date::operator +(int days) {
	struct tm plusDay = { 0, };
	Date plusDay_;

	plusDay.tm_year = this->year - 1900;
	plusDay.tm_mon = this->month - 1;
	plusDay.tm_mday = this->day + days;
	mktime(&plusDay);

	plusDay_.year = plusDay.tm_year + 1900;
	plusDay_.month = static_cast<Month>(plusDay.tm_mon + 1);
	plusDay_.day = plusDay.tm_mday;
	plusDay_.weekDay = static_cast<WeekDay>(plusDay.tm_wday);

	return plusDay_;
}


/*
명칭 : operator ==
출력 : == 연산자를 정의한다.
입력 : other
출력 : is
*/
bool Date::operator ==(const Date& other) {
	bool is = false;

	if (this->year == other.year && this->month == other.month && this->day == other.day) {
		is = true;
	}

	return is;
}

/*
명칭 : operator !=
기능 : != 연산자를 정의한다.
입력 : other
출력 : is
*/
bool Date::operator !=(const Date& other) {
	bool is = false;

	if (this->year != other.year || this->month != other.month || this->day != other.day) {
		is = true;
	}

	return is;
}

/*
명칭 : operator >
기능 : > 연산자를 정의한다.
입력 : other
출력 : is
*/
bool Date::operator >(const Date& other) {
	bool is = false;
	
	if (this->year > other.year) {
		is = true;
	}
	else if (this->year == other.year && this->month > other.month) {
		is = true;
	}
	else if (this->year == other.year && this->month == other.month && this->day > other.day) {
		is = true;
	}
	
	return is;
}

/*
명칭 : operator >=
기능 : >= 연산자를 정의한다.
입력 : other
출력 : is
*/
bool Date::operator >=(const Date& other) {
	bool is = false;

	if (this->year > other.year) {
		is = true;
	}
	else if (this->year == other.year && this->month > other.month) {
		is = true;
	}
	else if (this->year == other.year && this->month == other.month && this->day >= other.day) {
		is = true;
	}

	return is;
}

/*
명칭 : operator <
기능 : < 연산자를 정의한다.
입력 : other
출력 : is
*/
bool Date::operator <(const Date& other) {
	bool is = false;

	if (this->year < other.year) {
		is = true;
	}
	else if (this->year == other.year && this->month < other.month) {
		is = true;
	}
	else if (this->year == other.year && this->month == other.month && this->day < other.day) {
		is = true;
	}

	return is;
}

/*
명칭 : operator <=
기능 : <= 연산자를 정의한다.
입력 : other
출력 : is
*/
bool Date::operator <=(const Date& other) {
	bool is = false;

	if (this->year < other.year) {
		is = true;
	}
	else if (this->year == other.year && this->month < other.month) {
		is = true;
	}
	else if (this->year == other.year && this->month == other.month && this->day <= other.day) {
		is = true;
	}

	return is;
}
#if 0
/*
명칭 : main
기능 : 날짜 객체를 테스트한다.
입력 : X
출력 : X
*/
int main(int argc, char *argv[]) {
	Date birth(1995, FEB, 11);
	Date other_((char*)("19950211"));
	Date today;
	Date yesterday;
	Date previousDay;
	Date tomorrow;
	Date nextDay;
	Date frontDay;
	Date rearDay;
	Date plusDay;
	Date minusDay;

	bool is;

	char(*other);

	cout << birth.GetYear() << "-"
		<< birth.GetMonth() << "-"
		<< birth.GetDay() << endl;
	
	cout << other_.GetYear() << "-"
		<< other_.GetMonth() << "-"
		<< other_.GetDay() << endl;

	other = static_cast<char*>(other_);

	cout << other << endl;

	today = Date::Today();
	cout << today.GetYear() << "-"
		<< today.GetMonth() << "-"
		<< today.GetDay() << endl;

	yesterday = today.Yesterday();
	cout << yesterday.GetYear() << "-"
		<< yesterday.GetMonth() << "-"
		<< yesterday.GetDay() << endl;

	is = yesterday.IsLessThan(today);
	if (is == true) {
		cout << "작습니다." << endl;
	}
	if (yesterday < today) {
		cout << "작습니다. - < 연산자 -" << endl;
	}
	if (yesterday <= today) {
		cout << "작거나 같습니다. - <= 연산자 -" << endl;
	}

	previousDay = today.PreviousDate(1);
	cout << previousDay.GetYear() << "-"
		<< previousDay.GetMonth() << "-"
		<< previousDay.GetDay() << endl;

	is = previousDay.IsEqual(yesterday);
	if (is == true) {
		cout << "같습니다." << endl;
	}

	if (previousDay == yesterday) {
		cout << "같습니다. - == 연산자 -" << endl;
	}

	tomorrow = today.Tomorrow();
	cout << tomorrow.GetYear() << "-"
		<< tomorrow.GetMonth() << "-"
		<< tomorrow.GetDay() << endl;

	is = tomorrow.IsGreaterThan(today);
	if (is = true) {
		cout << "큽니다." << endl;
	}

	if (tomorrow > today) {
		cout << "큽니다. - > 연산자 -" << endl;
	}

	if (tomorrow >= today) {
		cout << "크거나 같습니다 - >= 연산자 -" << endl;
	}

	nextDay = today.NextDate(5);
	cout << nextDay.GetYear() << "-"
		<< nextDay.GetMonth() << "-"
		<< nextDay.GetDay() << endl;

	is = nextDay.IsNotEqual(tomorrow);
	if (is == true) {
		cout << "다릅니다." << endl;
	}

	if (nextDay != tomorrow) {
		cout << "다릅니다. - != 연산자 -" << endl;
	}

	frontDay = Date::Today();

	--(frontDay);
	cout << frontDay.GetYear() << "-"
		<< frontDay.GetMonth() << "-"
		<< frontDay.GetDay() << endl;

	(frontDay)--;
	cout << frontDay.GetYear() << "-"
		<< frontDay.GetMonth() << "-"
		<< frontDay.GetDay() << endl;

	rearDay = Date::Today();

	++(rearDay);
	cout << rearDay.GetYear() << "-"
		<< rearDay.GetMonth() << "-"
		<< rearDay.GetDay() << endl;

	(rearDay)++;
	cout << rearDay.GetYear() << "-"
		<< rearDay.GetMonth() << "-"
		<< rearDay.GetDay() << endl;

	minusDay = Date::Today();
	minusDay = minusDay - 30;

	cout << minusDay.GetYear() << "-"
		<< minusDay.GetMonth() << "-"
		<< minusDay.GetDay() << endl;

	plusDay = Date::Today();
	plusDay = plusDay + 6;

	cout << plusDay.GetYear() << "-"
		<< plusDay.GetMonth() << "-"
		<< plusDay.GetDay() << endl;

	return 0;
}
#endif