// ItemSubject.cpp
/*
파일명칭 : ItemSubject.cpp
기    능 : 항목 서브젝트 클래스를 만든다.
작성일자 : 2021.12.28
*/
#include "ItemSubject.h"
#include "TextExtent.h"

// ItemState
ItemState::ItemState() {
	this->totalWidth = 0;
	this->totalHeight = 0;
	this->selectedXPoint = -1;
	this->selectedYPoint = -1;
}

ItemState::ItemState(Long totalWidth, Long totalHeight) {
	this->totalWidth = totalWidth;
	this->totalHeight = totalHeight;
}

ItemState::ItemState(const ItemState& source) {
	this->totalWidth = source.totalWidth;
	this->totalHeight = source.totalHeight;
	this->selectedXPoint = source.selectedXPoint;
	this->selectedYPoint = source.selectedYPoint;
}

ItemState::~ItemState() {

}

ItemState& ItemState::operator=(const ItemState& source) {
	this->totalWidth = source.totalWidth;
	this->totalHeight = source.totalHeight;

	return *this;
}

SubjectState* ItemState::Clone() {
	return new ItemState(*this);
}

// ItemSubject
ItemSubject::ItemSubject(Long capacity)
	: Subject(capacity) {
	this->subjectState = new ItemState();
}

ItemSubject::ItemSubject(const ItemSubject& source)
	: Subject(source) {
	this->subjectState = new ItemState(*dynamic_cast<ItemState*>(source.subjectState));
}

ItemSubject::~ItemSubject() {
	
}

ItemSubject& ItemSubject::operator=(const ItemSubject& source) {
	Subject::operator=(source);
	this->subjectState = new ItemState(*dynamic_cast<ItemState*>(source.subjectState));
	return *this;
}

BEGIN_MESSAGE_MAP(ItemSubject, CWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

int ItemSubject::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CWnd::OnCreate(lpCreateStruct);
	CDC* pDC = this->GetDC();
	this->subjectState->SetLogFontState(-MulDiv(9, pDC->GetDeviceCaps(LOGPIXELSY), 72), 0, "맑은 고딕");
	this->subjectState->textExtent = new TextExtent(this);

	ReleaseDC(pDC);
	return 0;
}

void ItemSubject::OnSize(UINT nType, int cx, int cy) {
	CWnd::OnSize(nType, cx, cy);
}

void ItemSubject::OnClose() {
	CWnd::OnClose();
	DestroyWindow();
	delete this;
}