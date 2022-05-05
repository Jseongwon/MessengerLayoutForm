// Observer.h
#ifndef _OBSERVER_H
#define _OBSERVER_H
typedef signed long int Long;

class Scroll;
class Subject;
class Observer {
public:
	enum { SUBJECTERROR = -1, CARET = 0, SCROLL = 1 };
public:
	Observer(Subject* pParentSubject = 0);
	Observer(const Observer& source);
	virtual ~Observer() = 0;
	Observer& operator=(const Observer& source);

	virtual void Update() = 0;
	virtual Observer* Clone() = 0;
	virtual Long GetType() const = 0;

protected:
	Subject* pParentSubject;
};

#endif // _OBSERVER_H