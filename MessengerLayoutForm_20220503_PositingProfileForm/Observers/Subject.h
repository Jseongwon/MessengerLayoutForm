// Subject.h
#ifndef _SUBJECT_H
#define _SUBJECT_H
#include "../Utilities/Array.h"
#include <string>
using namespace std;

class Observer;
class TextExtent;
// SubjectState
class SubjectState {
public:
	TextExtent* textExtent;

public:
	SubjectState();
	SubjectState(const SubjectState& source);
	virtual ~SubjectState() = 0;
	SubjectState& operator=(const SubjectState& source);

	virtual SubjectState* Clone() = 0;

	virtual void SetScrollSize(Long totalWidth, Long totalHeight) {  }
	virtual void SetLogFontState(Long lfHeight, Long lfWidth, string lfFaceName) {  }
	virtual void SetSelectedPoint(Long xPoint, Long yPoint) {  }

	virtual Long GetTotalWidth() const { return 0; }
	virtual Long GetTotalHeight() const { return 0; }
	virtual Long GetLogFontHeight() const { return 0; }
	virtual Long GetLogFontWidth() const { return 0; }
	virtual string GetLogFontFaceName() { return string("ERROR"); }
	virtual Long GetSelectedXPoint() const { return 0; }
	virtual Long GetSelectedYPoint() const { return 0; }
};

// Subject
class Subject {
public:
	Subject(Long capacity = 8);
	Subject(const Subject& source);
	virtual ~Subject() = 0;
	Subject& operator=(const Subject& source);

	Long Attach(Observer* itemObserver);
	Long Find(Long type);
	Long Detach(Observer* itemObserver);
	void Notify();

	virtual SubjectState* GetSubjectState() const;

	Observer* GetAt(Long index) const;
	Long GetCapacity() const;
	Long GetLength() const;

protected:
	SubjectState* subjectState;

	Array<Observer*> observers;
	Long capacity;
	Long length;
};

inline SubjectState* Subject::GetSubjectState() const {
	return const_cast<SubjectState*>(this->subjectState);
}

inline Observer* Subject::GetAt(Long index) const {
	return const_cast<Observer*>(const_cast<Subject*>(this)->observers.GetAt(index));
}
inline Long Subject::GetCapacity() const {
	return this->capacity;
}
inline Long Subject::GetLength() const {
	return this->length;
}

int CompareObserversInSubject(void* one, void* other);

#endif // _SUBJECT_H