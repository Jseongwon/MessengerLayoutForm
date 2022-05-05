// ItemObservers.cpp
/*
파일명칭 : ItemObservers.cpp
기    능 : 항목 감시자들 클래스를 정의한다.
작 성 자 : 정성원 
작성일자 : 2022.02.17
*/
#include "ItemObservers.h"
#include "ItemSubject.h"
#include "Scrolls.h"

ItemObserver::ItemObserver(Subject* pParentSubject)
	: Observer(pParentSubject) {
	
}

ItemObserver::ItemObserver(const ItemObserver& source)
	: Observer(source) {
	
}

ItemObserver::~ItemObserver() {

}

ItemObserver& ItemObserver::operator=(const ItemObserver& source) {
	Observer::operator=(source);
	
	return *this;
}

// ItemScrollController
ItemScrollController::ItemScrollController(CWnd* pParentWnd)
	: ItemObserver(dynamic_cast<Subject*>(pParentWnd)) {
	CRect rect;

	this->pParentWnd = pParentWnd;
	this->pParentWnd->GetClientRect(&rect);

	this->verticalScroll = new VerticalScroll(0, this->pParentSubject->GetSubjectState()->GetTotalHeight(), 5, rect.Height(), 0);
	this->horizontalScroll = new HorizontalScroll(0, this->pParentSubject->GetSubjectState()->GetTotalWidth(), 5, rect.Width(), 0);

	this->pParentSubject->Attach(this);
}

ItemScrollController::ItemScrollController(const ItemScrollController& source)
	: ItemObserver(source) {

	CRect rect;
	this->pParentWnd = source.pParentWnd;
	this->pParentWnd->GetClientRect(&rect);

	this->verticalScroll = new VerticalScroll(*dynamic_cast<VerticalScroll*>(source.verticalScroll));
	this->horizontalScroll = new HorizontalScroll(*dynamic_cast<HorizontalScroll*>(source.horizontalScroll));

}

ItemScrollController::~ItemScrollController() {
	if (this->verticalScroll != 0) {
		delete this->verticalScroll;
	}
	if (this->horizontalScroll != 0) {
		delete this->horizontalScroll;
	}
}

ItemScrollController& ItemScrollController::operator=(const ItemScrollController& source) {
	ItemObserver::operator=(source);
	CRect rect;
	this->pParentWnd = source.pParentWnd;
	if (this->verticalScroll != 0) {
		delete this->verticalScroll;
	}
	if (this->horizontalScroll != 0) {
		delete this->horizontalScroll;
	}
	
	this->pParentWnd->GetClientRect(&rect);

	this->verticalScroll = new VerticalScroll(*dynamic_cast<VerticalScroll*>(source.verticalScroll));
	this->horizontalScroll = new HorizontalScroll(*dynamic_cast<HorizontalScroll*>(source.horizontalScroll));

	return *this;
}

void ItemScrollController::Update() {
	// 1. 스크롤 정보를 갱신한다.
	CRect rect;

	Scroll* temp;

	SCROLLINFO verticalScrollInfo;

	LONG verticalMax;
	this->pParentWnd->GetClientRect(&rect);
	verticalMax = this->pParentSubject->GetSubjectState()->GetTotalHeight();
	if (rect.Height() != this->verticalScroll->GetPageLength() || verticalMax != this->verticalScroll->GetMaximum()) {
		temp = this->verticalScroll;
		this->verticalScroll = new VerticalScroll(temp->GetMinimum(), verticalMax,
			temp->GetLineLength(), rect.Height(), temp->GetPosition());

		// 화면 바깥으로 나갈 수도 있음.
		this->verticalScroll->Move(this->verticalScroll->GetPosition());

		this->pParentWnd->GetScrollInfo(SB_VERT, &verticalScrollInfo, SIF_ALL);
		verticalScrollInfo.nMin = this->verticalScroll->GetMinimum();
		verticalScrollInfo.nMax = this->verticalScroll->GetMaximum();
		verticalScrollInfo.nPage = this->verticalScroll->GetPageLength();
		verticalScrollInfo.nPos = this->verticalScroll->GetPosition();
		verticalScrollInfo.nTrackPos = this->verticalScroll->GetLineLength();
		this->pParentWnd->SetScrollInfo(SB_VERT, &verticalScrollInfo, TRUE);

		if (temp != 0) {
			delete temp;
		}
	}
}

ItemObserver* ItemScrollController::Clone() {
	return new ItemScrollController(*this);
}

Long ItemScrollController::GetType() const {
	return Observer::SCROLL;
}

void ItemScrollController::ChangedScroll(ScrollBuilder* scrollBuilder) {
	if (scrollBuilder->GetScrollState() == Scroll::VERTICAL) {
		if (this->verticalScroll != 0) {
			delete this->verticalScroll;
		}
		this->verticalScroll = scrollBuilder->Build();
	}
	else if (scrollBuilder->GetScrollState() == Scroll::HORIZONTAL) {
		if (this->horizontalScroll != 0) {
			delete this->horizontalScroll;
		}
		this->horizontalScroll = scrollBuilder->Build();
	}
}

SCROLLINFO ItemScrollController::GetVerticalScrollInfo() {
	SCROLLINFO verticalScrollInfo = { sizeof(SCROLLINFO), SIF_ALL, this->verticalScroll->GetMinimum(), this->verticalScroll->GetMaximum(),
		(UINT)this->verticalScroll->GetPageLength(), this->verticalScroll->GetPosition(), this->verticalScroll->GetLineLength() };
	return verticalScrollInfo;
}

SCROLLINFO ItemScrollController::GetHorizontalScrollInfo() {
	SCROLLINFO horizontalScrollInfo = { sizeof(SCROLLINFO), SIF_ALL, this->horizontalScroll->GetMinimum(), this->horizontalScroll->GetMaximum(),
		(UINT)this->horizontalScroll->GetPageLength(), this->horizontalScroll->GetPosition(), this->horizontalScroll->GetLineLength() };
	return horizontalScrollInfo;
}