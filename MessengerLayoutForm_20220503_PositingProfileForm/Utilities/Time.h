// Time.h
#ifndef _TIME_H
#define _TIME_H
#include <string>
using namespace std;
class Time {
public:
	Time();
	Time(int hour, int minute, int second);
	Time(char(*time));
	Time(const Time& source);
	~Time();
	Time& operator =(const Time& source);
	operator char*();

	static Time GetNowTime();

	string GetConvertTimeKoreanString();
	string GetConvertTimeFormatString(char insertCharacter);

	int GetHour() const;
	int GetMinute() const;
	int GetSecond() const;

private:
	int hour;
	int minute;
	int second;
};

inline int Time::GetHour() const {
	return this->hour;
}

inline int Time::GetMinute() const {
	return this->minute;
}

inline int Time::GetSecond() const {
	return this->second;
}

#endif // _TIME_H