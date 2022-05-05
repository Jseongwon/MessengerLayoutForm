// ItemObservers.h
#ifndef _ITEMOBSERVERS_H
#define _ITEMOBSERVERS_H
#include <afxwin.h>
#include "Observer.h"

class CWnd;
class Scroll;
class ScrollBuilder;
class Subject;
class ItemObserver : public Observer {
public:
	ItemObserver(Subject* pParentSubject = 0);
	ItemObserver(const ItemObserver& source);
	virtual ~ItemObserver() = 0;
	ItemObserver& operator=(const ItemObserver& source);

	virtual void Update() = 0;
	virtual ItemObserver* Clone() = 0;
	virtual Long GetType() const = 0;
};

// ItemScrollController
class ItemScrollController : public ItemObserver {
public:
	CWnd* pParentWnd;

public:
	ItemScrollController(CWnd* pParentWnd = 0);
	ItemScrollController(const ItemScrollController& source);
	virtual ~ItemScrollController();
	ItemScrollController& operator=(const ItemScrollController& source);

	virtual void Update();
	virtual ItemObserver* Clone();
	virtual Long GetType() const;

	void ChangedScroll(ScrollBuilder* scrollBuilder);

	Scroll* GetVerticalScroll() const;
	Scroll* GetHorizontalScroll() const;

	SCROLLINFO GetVerticalScrollInfo();
	SCROLLINFO GetHorizontalScrollInfo();

private:
	Scroll* verticalScroll;
	Scroll* horizontalScroll;
};

inline Scroll* ItemScrollController::GetVerticalScroll() const {
	return const_cast<Scroll*>(this->verticalScroll);
}
inline Scroll* ItemScrollController::GetHorizontalScroll() const {
	return const_cast<Scroll*>(this->horizontalScroll);
}

#endif // _ITEMOBSERVERS_H