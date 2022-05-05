//ScrollActions.h
#ifndef _SCROLLACTIONS_H
#define _SCROLLACTIONS_H
#include <afxwin.h>

class ItemSubject;
class ScrollAction {
public:
	ItemSubject *pParentItemSubject;

public:
	ScrollAction(ItemSubject *pParentItemSubject);
	virtual ~ScrollAction() = 0;
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) = 0;
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) = 0;
};

// LinePreviousScrollAction
class LinePreviousScrollAction : public ScrollAction {
public:
	LinePreviousScrollAction(ItemSubject *pParentItemSubject);
	virtual ~LinePreviousScrollAction();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
};

// LineNextScrollAction
class LineNextScrollAction : public ScrollAction {
public:
	LineNextScrollAction(ItemSubject *pParentItemSubject);
	virtual ~LineNextScrollAction();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
};

// PagePreviousScrollAction
class PagePreviousScrollAction : public ScrollAction {
public:
	PagePreviousScrollAction(ItemSubject *pParentItemSubject);
	virtual ~PagePreviousScrollAction();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
};

// PageNextScrollAction
class PageNextScrollAction : public ScrollAction {
public:
	PageNextScrollAction(ItemSubject *pParentItemSubject);
	virtual ~PageNextScrollAction();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
};

// ThumbTrackScrollAction
class ThumbTrackScrollAction : public ScrollAction {
public:
	ThumbTrackScrollAction(ItemSubject *pParentItemSubject);
	virtual ~ThumbTrackScrollAction();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
};

// FirstScrollAction
class FirstScrollAction : public ScrollAction {
public:
	FirstScrollAction(ItemSubject *pParentItemSubject);
	virtual ~FirstScrollAction();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
};

// LastScrollAction
class LastScrollAction : public ScrollAction {
public:
	LastScrollAction(ItemSubject *pParentItemSubject);
	virtual ~LastScrollAction();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
};

// ScrollActionFactory
class ScrollActionFactory {
public:
	ItemSubject *pParentItemSubject;

public:
	ScrollActionFactory(ItemSubject *pParentItemSubject);
	~ScrollActionFactory();
	ScrollAction* Create(UINT nSBCode);
};

#endif // _SCROLLACTIONS_H