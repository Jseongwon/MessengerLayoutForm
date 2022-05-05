// ScrollActions.cpp
/*
파일명칭 : ScrollActions.cpp
기능 : 이동 스크롤 행위들의 클래스를 만든다.
작성자 : 정성원
작성일자 : 2021.08.25
*/
#include "ScrollActions.h"
#include "../Observers/ItemSubject.h"
#include "../Observers/ItemObservers.h"
#include "Scrolls.h"

#define SB_LINEPREVIOUS	0 // SB_LINEUP, SB_LINELEFT
#define SB_LINENEXT		1 // SB_LINEDOWN, SB_LINERIGHT
#define SB_PAGEPREVIOUS	2 // SB_PAGEUP, SB_PAGELEFT
#define SB_PAGENEXT		3 // SB_PAGEDOWN, SB_PAGERIGHT
#define SB_FIRST		6 // SB_TOP, SB_LEFT
#define SB_LAST			7 // SB_BOTTOM, SB_RIGHT

// ScrollAction
ScrollAction::ScrollAction(ItemSubject *pParentItemSubject) {
	this->pParentItemSubject = pParentItemSubject;
}

ScrollAction::~ScrollAction() {
}

// LinePreviousScrollAction
LinePreviousScrollAction::LinePreviousScrollAction(ItemSubject *pParentItemSubject)
	: ScrollAction(pParentItemSubject) {
}

LinePreviousScrollAction::~LinePreviousScrollAction() {
}

void LinePreviousScrollAction::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	ItemScrollController* itemScrollController;

	SCROLLINFO verticalScrollInfo;

	Long index;
	index = this->pParentItemSubject->Find(Observer::SCROLL);
	if (index >= 0) {
		itemScrollController = (ItemScrollController*)this->pParentItemSubject->GetAt(index);
		itemScrollController->GetVerticalScroll()->PreviousLine();

		verticalScrollInfo = itemScrollController->GetVerticalScrollInfo();

		this->pParentItemSubject->SetScrollInfo(SB_VERT, &verticalScrollInfo, TRUE);
	}
}

void LinePreviousScrollAction::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	//this->pParentItemSubject->itemScrollController->GetHorizontalScroll()->PreviousLine();
}

// LineNextScrollAction
LineNextScrollAction::LineNextScrollAction(ItemSubject *pParentItemSubject)
	: ScrollAction(pParentItemSubject) {
}

LineNextScrollAction::~LineNextScrollAction() {
}

void LineNextScrollAction::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	ItemScrollController* itemScrollController;

	SCROLLINFO verticalScrollInfo;

	Long index;
	index = this->pParentItemSubject->Find(Observer::SCROLL);
	if (index >= 0) {
		itemScrollController = (ItemScrollController*)this->pParentItemSubject->GetAt(index);
		itemScrollController->GetVerticalScroll()->NextLine();

		verticalScrollInfo = itemScrollController->GetVerticalScrollInfo();

		this->pParentItemSubject->SetScrollInfo(SB_VERT, &verticalScrollInfo, TRUE);
	}
}

void LineNextScrollAction::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	//this->pParentItemSubject->itemScrollController->GetHorizontalScroll()->NextLine();
}

// PagePreviousScrollAction
PagePreviousScrollAction::PagePreviousScrollAction(ItemSubject *pParentItemSubject)
	: ScrollAction(pParentItemSubject) {
}

PagePreviousScrollAction::~PagePreviousScrollAction() {
}

void PagePreviousScrollAction::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	ItemScrollController* itemScrollController;

	SCROLLINFO verticalScrollInfo;

	Long index;
	index = this->pParentItemSubject->Find(Observer::SCROLL);
	if (index >= 0) {
		itemScrollController = (ItemScrollController*)this->pParentItemSubject->GetAt(index);
		itemScrollController->GetVerticalScroll()->PreviousPage();

		verticalScrollInfo = itemScrollController->GetVerticalScrollInfo();

		this->pParentItemSubject->SetScrollInfo(SB_VERT, &verticalScrollInfo, TRUE);
	}
}

void PagePreviousScrollAction::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	//this->pParentItemSubject->itemScrollController->GetHorizontalScroll()->PreviousPage();
}

// PageNextScrollAction
PageNextScrollAction::PageNextScrollAction(ItemSubject *pParentItemSubject)
	: ScrollAction(pParentItemSubject) {
}

PageNextScrollAction::~PageNextScrollAction() {
}

void PageNextScrollAction::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	ItemScrollController* itemScrollController;

	SCROLLINFO verticalScrollInfo;

	Long index;
	index = this->pParentItemSubject->Find(Observer::SCROLL);
	if (index >= 0) {
		itemScrollController = (ItemScrollController*)this->pParentItemSubject->GetAt(index);
		itemScrollController->GetVerticalScroll()->NextPage();

		verticalScrollInfo = itemScrollController->GetVerticalScrollInfo();

		this->pParentItemSubject->SetScrollInfo(SB_VERT, &verticalScrollInfo, TRUE);
	}
}

void PageNextScrollAction::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	//this->pParentItemSubject->itemScrollController->GetHorizontalScroll()->NextPage();
}

// ThumbTrackScrollAction
ThumbTrackScrollAction::ThumbTrackScrollAction(ItemSubject *pParentItemSubject)
	: ScrollAction(pParentItemSubject) {
}

ThumbTrackScrollAction::~ThumbTrackScrollAction() {
}

void ThumbTrackScrollAction::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	ItemScrollController* itemScrollController;

	SCROLLINFO verticalScrollInfo;

	Long index;
	index = this->pParentItemSubject->Find(Observer::SCROLL);
	if (index >= 0) {
		itemScrollController = (ItemScrollController*)this->pParentItemSubject->GetAt(index);
		itemScrollController->GetVerticalScroll()->Move(nPos);

		verticalScrollInfo = itemScrollController->GetVerticalScrollInfo();

		this->pParentItemSubject->SetScrollInfo(SB_VERT, &verticalScrollInfo, TRUE);
	}
}

void ThumbTrackScrollAction::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	//this->pParentItemSubject->itemScrollController->GetHorizontalScroll()->Move(nPos);
}

// FirstScrollAction
FirstScrollAction::FirstScrollAction(ItemSubject *pParentItemSubject)
	: ScrollAction(pParentItemSubject) {
}

FirstScrollAction::~FirstScrollAction() {
}

void FirstScrollAction::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	ItemScrollController* itemScrollController;

	SCROLLINFO verticalScrollInfo;

	Long index;
	index = this->pParentItemSubject->Find(Observer::SCROLL);
	if (index >= 0) {
		itemScrollController = (ItemScrollController*)this->pParentItemSubject->GetAt(index);
		itemScrollController->GetVerticalScroll()->First();

		verticalScrollInfo = itemScrollController->GetVerticalScrollInfo();

		this->pParentItemSubject->SetScrollInfo(SB_VERT, &verticalScrollInfo, TRUE);
	}
}

void FirstScrollAction::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	//this->pParentItemSubject->itemScrollController->GetHorizontalScroll()->First();
}

// LastScrollAction
LastScrollAction::LastScrollAction(ItemSubject *pParentItemSubject)
	: ScrollAction(pParentItemSubject) {
}

LastScrollAction::~LastScrollAction() {
}

void LastScrollAction::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	ItemScrollController* itemScrollController;

	SCROLLINFO verticalScrollInfo;

	Long index;
	index = this->pParentItemSubject->Find(Observer::SCROLL);
	if (index >= 0) {
		itemScrollController = (ItemScrollController*)this->pParentItemSubject->GetAt(index);
		itemScrollController->GetVerticalScroll()->Last();

		verticalScrollInfo = itemScrollController->GetVerticalScrollInfo();

		this->pParentItemSubject->SetScrollInfo(SB_VERT, &verticalScrollInfo, TRUE);
	}
}

void LastScrollAction::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	//this->pParentItemSubject->itemScrollController->GetHorizontalScroll()->Last();
}

// ScrollActionFactory
ScrollActionFactory::ScrollActionFactory(ItemSubject *pParentItemSubject) {
	this->pParentItemSubject = dynamic_cast<ItemSubject*>(pParentItemSubject);
}

ScrollActionFactory::~ScrollActionFactory() {
}

ScrollAction* ScrollActionFactory::Create(UINT nSBCode) {
	ScrollAction* scrollAction = 0;

	switch (nSBCode) {
	case SB_LINEPREVIOUS:
		scrollAction = new LinePreviousScrollAction(this->pParentItemSubject);
		break;

	case SB_LINENEXT:
		scrollAction = new LineNextScrollAction(this->pParentItemSubject);
		break;

	case SB_PAGEPREVIOUS:
		scrollAction = new PagePreviousScrollAction(this->pParentItemSubject);
		break;

	case SB_PAGENEXT:
		scrollAction = new PageNextScrollAction(this->pParentItemSubject);
		break;

	case SB_THUMBTRACK:
		scrollAction = new ThumbTrackScrollAction(this->pParentItemSubject);
		break;

	case SB_FIRST:
		scrollAction = new FirstScrollAction(this->pParentItemSubject);
		break;

	case SB_LAST:
		scrollAction = new LastScrollAction(this->pParentItemSubject);
		break;

	default:
		break;
	}

	return scrollAction;
}