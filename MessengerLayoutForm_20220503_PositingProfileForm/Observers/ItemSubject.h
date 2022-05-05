// ItemSubject.h
#ifndef _ITEMSUBJECT_H
#define _ITEMSUBJECT_H
#include <afxwin.h>
#include "Subject.h"

class ItemState : public SubjectState {
public:
	ItemState();
	ItemState(Long width, Long height);
	ItemState(const ItemState& source);
	virtual ~ItemState();
	ItemState& operator=(const ItemState& source);

	virtual SubjectState* Clone();

	void SetPrevRect(CRect prevRect);
	virtual void SetScrollSize(Long totalWidth, Long totalHeight);
	virtual void SetLogFontState(Long lfHeight, Long lfWidth, string lfFaceName);
	virtual void SetSelectedPoint(Long selectedXPoint, Long selectedYPoint);

	CRect& GetPrevRect() const;

	virtual Long GetTotalWidth() const;
	virtual Long GetTotalHeight() const;
	virtual Long GetLogFontHeight() const;
	virtual Long GetLogFontWidth() const;
	virtual string GetLogFontFaceName();
	virtual Long GetSelectedXPoint() const;
	virtual Long GetSelectedYPoint() const;

private:
	CRect prevRect;

	Long totalWidth;
	Long totalHeight;
	Long logFontHeight;
	Long logFontWidth;
	string logFontFaceName;

	Long selectedXPoint;
	Long selectedYPoint;
};

inline void ItemState::SetPrevRect(CRect prevRect) {
	this->prevRect = prevRect;
}
inline void ItemState::SetScrollSize(Long totalWidth, Long totalHeight) {
	this->totalWidth = totalWidth;
	this->totalHeight = totalHeight;
}
inline void ItemState::SetLogFontState(Long lfHeight, Long lfWidth, string lfFaceName) {
	this->logFontHeight = lfHeight;
	this->logFontWidth = lfWidth;
	this->logFontFaceName = lfFaceName;
}
inline void ItemState::SetSelectedPoint(Long selectedXPoint, Long selectedYPoint) {
	this->selectedXPoint = selectedXPoint;
	this->selectedYPoint = selectedYPoint;
}

inline CRect& ItemState::GetPrevRect() const {
	return const_cast<CRect&>(this->prevRect);
}
inline Long ItemState::GetTotalWidth() const {
	return this->totalWidth;
}
inline Long ItemState::GetTotalHeight() const {
	return this->totalHeight;
}
inline Long ItemState::GetLogFontHeight() const {
	return this->logFontHeight;
}
inline Long ItemState::GetLogFontWidth() const {
	return this->logFontWidth;
}
inline string ItemState::GetLogFontFaceName() {
	return this->logFontFaceName;
}
inline Long ItemState::GetSelectedXPoint() const {
	return this->selectedXPoint;
}
inline Long ItemState::GetSelectedYPoint() const {
	return this->selectedYPoint;
}

class ItemSubject : public CWnd, public Subject {
public:
	ItemSubject(Long capacity = 8);
	ItemSubject(const ItemSubject& source);
	virtual ~ItemSubject() = 0;
	ItemSubject& operator=(const ItemSubject& source);

protected:
	afx_msg virtual int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();

	DECLARE_MESSAGE_MAP()
};

#endif // _ITEMSUBJECT_H