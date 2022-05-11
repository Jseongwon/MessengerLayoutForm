// CardListForm.cpp
/*
파일명칭 : CardListForm.cpp
기    능 : 아이템 목록 폼 클래스를 만든다.
작성일자 : 2021.10.28
*/
#include "CardListForm.h"
#include "ProfileForm.h"
#include "PostingCardListStyle.h"
#include "UserCardListStyle.h"
#include "../MessengerLayoutForm.h"
#include "../Observers/ItemObservers.h"
#include "../Observers/ScrollActions.h"
#include "../Observers/Scrolls.h"

CardListForm::CardListForm(CWnd* pParentWnd, COLORREF accentColor, COLORREF backgroundColor, COLORREF selectedBackgroundColor,
	COLORREF textColor, COLORREF selectedTextColor) {
	this->pParentWnd = pParentWnd;
	this->cardListStyle = 0;

	this->accentColor = accentColor;
	this->backgroundColor = backgroundColor;
	this->selectedBackgroundColor = selectedBackgroundColor;
	this->textColor = textColor;
	this->selectedTextColor = selectedTextColor;

	this->m_bTrack = FALSE;
}

void CardListForm::Repair(int cardListStyle) {
	if (this->cardListStyle != 0) {
		delete this->cardListStyle;
	}
	this->cardListStyle = 0;
	if (cardListStyle == CardListStyle::POSTINGCARDLISTSTYLE) {
		this->cardListStyle = new PostingCardListStyle(this);
	}
	else if (cardListStyle == CardListStyle::USERCARDLISTSTYLE) {
		this->cardListStyle = new UserCardListStyle(this);
	}
}

BEGIN_MESSAGE_MAP(CardListForm, CWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEHOVER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

int CardListForm::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	ItemSubject::OnCreate(lpCreateStruct);
	ItemState* itemState;
	CRect clientRect;

	CString fileNameLineNumberString;

	new ItemScrollController(this);

	this->GetClientRect(&clientRect);

	itemState = dynamic_cast<ItemState*>(this->GetSubjectState());
	itemState->SetScrollSize(clientRect.Width(), clientRect.Height() - 5);

	if (this->cardListStyle == 0) {
		fileNameLineNumberString.Format("%s(%d): error: ", __FILE__, __LINE__ + 1);
		AfxMessageBox(fileNameLineNumberString + "카드 목록의 스타일이 설정되어 있지 않습니다..\n", MB_OK);
	}
	this->cardListStyle->OnCreate(lpCreateStruct);

	return 0;
}

void CardListForm::OnSize(UINT nType, int cx, int cy) {
	CWnd::OnSize(nType, cx, cy);

	this->Notify();
	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

void CardListForm::OnClose() {
	if (((MessengerLayoutForm*)AfxGetMainWnd())->profileForm != NULL) {
		((MessengerLayoutForm*)AfxGetMainWnd())->profileForm->SendMessage(WM_CLOSE);
		((MessengerLayoutForm*)AfxGetMainWnd())->profileForm = NULL;
	}
	if (this->cardListStyle != 0) {
		delete this->cardListStyle;
		this->cardListStyle = 0;
	}
	ItemSubject::OnClose();
}

void CardListForm::OnPaint() {
	CPaintDC dc(this);

	this->cardListStyle->OnDraw(&dc);
}

void CardListForm::OnSetFocus(CWnd* pCWnd) {
	CWnd::OnSetFocus(pCWnd);
	this->pParentWnd->SendMessage(WM_KILLFOCUS);
}

void CardListForm::OnKillFocus(CWnd *pCWnd) {
	CWnd::OnKillFocus(pCWnd);
#if 0
	Item* item;
	LONG i = 0;
	while (i < this->p_ItemList->GetLength()) {
		item = this->p_ItemList->GetAt(i);
		item->Focus(false);

		i++;
	}
#endif
	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

void CardListForm::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
	SCROLLINFO scrollInfo;
	ScrollActionFactory scrollActionFactory(this);
	ScrollAction *scrollAction;
	scrollAction = scrollActionFactory.Create(nSBCode);

	this->GetScrollInfo(SB_VERT, &scrollInfo, SIF_ALL);
	nPos = scrollInfo.nTrackPos;
	if (scrollAction != 0) {
		scrollAction->OnVScroll(nSBCode, nPos, pScrollBar);
		delete scrollAction;
	}
	this->Notify();

	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

BOOL CardListForm::OnMouseWheel(UINT nFlags, short zDelta, CPoint point) {
	CWnd::OnMouseWheel(nFlags, zDelta, point);

	SCROLLINFO scrollInfo;

	ItemScrollController* itemScrollController;

	LONG scrollCurrent = 0;
	LONG index;

	index = this->Find(Observer::SCROLL);
	if (index >= 0) {
		itemScrollController = (ItemScrollController*)this->observers.GetAt(index);

		scrollCurrent = itemScrollController->GetVerticalScroll()->GetPosition() - zDelta;
	}

	this->GetScrollInfo(SB_VERT, &scrollInfo, SIF_ALL);
	scrollInfo.nPos = scrollCurrent;
	this->SetScrollInfo(SB_VERT, &scrollInfo, FALSE);

	this->SendMessage(WM_VSCROLL, MAKELONG(SB_THUMBTRACK, scrollCurrent));

	return TRUE;
}

void CardListForm::OnMouseMove(UINT nFlags, CPoint point) {
	CWnd::OnMouseMove(nFlags, point);

	this->cardListStyle->OnMouseMove(nFlags, point);
}

void CardListForm::OnMouseLeave() {
	CWnd::OnMouseLeave();

	this->m_bTrack = FALSE;

	this->InvalidateRect(&this->currentRect);
}

void CardListForm::OnMouseHover(UINT nFlags, CPoint point) {
	CWnd::OnMouseHover(nFlags, point);
	// 현재 범위를 벗어났을 때 FALSE 처리를 해주어야 한다.
	//this->SendMessage(WM_SETFOCUS);

	this->m_bTrack = TRUE;

	this->InvalidateRect(&this->currentRect);
}

void CardListForm::OnLButtonDown(UINT nFlags, CPoint point) {
	CWnd::OnLButtonDown(nFlags, point);

	this->cardListStyle->OnLButtonClicked(nFlags, point);
}

void CardListForm::OnLButtonUp(UINT nFlags, CPoint point) {
	CWnd::OnLButtonUp(nFlags, point);
	SubjectState* itemState;

	if (this->currentRect.PtInRect(point) == TRUE/* && item->IsFocus() != true*/) {
		this->m_ptDownPoint = point;

		itemState = this->GetSubjectState();
		itemState->SetSelectedPoint(this->m_ptDownPoint.x, this->m_ptDownPoint.y);
	}

	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}