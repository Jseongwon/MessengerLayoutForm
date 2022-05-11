// ProfileForm.cpp
/*
파일명칭 : ProfileForm.cpp
기    능 : 이력 폼 클래스를 만든다.
작 성 자 : 정성원
작성일자 : 2021.10.28
*/
#include "ProfileForm.h"
#include "ProfileCompiler.h"
#include "ProfileCompileMode.h"
#include "../Observers/ItemObservers.h"
#include "../Observers/ScrollActions.h"
#include "../Observers/Scrolls.h"
#include "../Generator/DrawingGenerator.h"

ProfileForm::ProfileForm(CWnd* pParentWnd, COLORREF accentColor, COLORREF backgroundColor, COLORREF selectedBackgroundColor,
	COLORREF textColor, COLORREF selectedTextColor) {
	this->pParentWnd = pParentWnd;
	this->profileStyle = NULL;
	this->accentColor = accentColor;
	this->backgroundColor = backgroundColor;
	this->selectedBackgroundColor = selectedBackgroundColor;
	this->textColor = textColor;
	this->selectedTextColor = selectedTextColor;

	strcpy_s(this->baseName, sizeof(this->baseName), "");
	this->baseIndex = -1;
	this->m_ProfileLength = 0;

	this->m_bTrack = FALSE;
}

void ProfileForm::Repair(int profileStyle) {
	if (this->profileStyle != NULL) {
		delete this->profileStyle;
	}
	this->profileStyle = NULL;
	if (profileStyle == ProfileStyle::CHATPROFILESTYLE) {
		this->profileStyle = new ChatProfileStyle(this);
	}
	else if (profileStyle == ProfileStyle::POSTINGPROFILESTYLE) {
		this->profileStyle = new DocumentProfileStyle(this);
	}
}

BEGIN_MESSAGE_MAP(ProfileForm, ItemSubject)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_WM_ERASEBKGND()
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

int ProfileForm::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	ItemSubject::OnCreate(lpCreateStruct);
	CRect clientRect;
	ItemState* itemState;

	strcpy_s(this->baseName, sizeof(this->baseName), "");

	new ItemScrollController(this);

	this->GetClientRect(&clientRect);

	itemState = dynamic_cast<ItemState*>(this->GetSubjectState());
	itemState->SetScrollSize(clientRect.Width(), clientRect.Height() - 5);

	return 0;
}

void ProfileForm::OnSize(UINT nType, int cx, int cy) {
	ItemSubject::OnSize(nType, cx, cy);

	this->Notify();
	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

	((ItemState*)this->subjectState)->SetPrevRect(CRect(0, 0, cx, cy));
}

void ProfileForm::OnClose() {
	if (this->profileStyle != NULL) {
		delete this->profileStyle;
	}
	ItemSubject::OnClose();
}

BOOL ProfileForm::OnEraseBkgnd(CDC* pDC) {
	return FALSE;
}

void ProfileForm::OnPaint() {
	CPaintDC dc(this);

	this->profileStyle->OnDraw(&dc);
}

void ProfileForm::OnSetFocus(CWnd* pCWnd) {
	CWnd::OnSetFocus(pCWnd);
	this->pParentWnd->SendMessage(WM_KILLFOCUS);
}

void ProfileForm::OnKillFocus(CWnd *pCWnd) {
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

void ProfileForm::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
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

BOOL ProfileForm::OnMouseWheel(UINT nFlags, short zDelta, CPoint point) {
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

void ProfileForm::OnMouseMove(UINT nFlags, CPoint point) {
	CWnd::OnMouseMove(nFlags, point);
#if 0
	CRect currentImageRect;

	ItemScrollController* itemScrollController;

	LONG scrollCurrent = 0;
	LONG yPos;
	LONG index;
	LONG i = 1;

	TRACKMOUSEEVENT trackMouseEvent;

	ZeroMemory(&trackMouseEvent, sizeof(TRACKMOUSEEVENT));

	index = this->Find(Observer::SCROLL);
	if (index >= 0) {
		itemScrollController = (ItemScrollController*)this->observers.GetAt(index);

		scrollCurrent = itemScrollController->GetVerticalScroll()->GetPosition();
	}

	// 1. 사용자 영역에 없으면 마우스가 떠났음을 알린다.
	if (this->currentRect.PtInRect(point) != TRUE && this->m_bTrack == TRUE) {
		this->SendMessage(WM_MOUSELEAVE, nFlags, MAKELPARAM(point.x, point.y));
	}
	// 2. 마우스가 카드에 없는 동안 반복한다.
	// 3. 있으면 마우스가 카드에 있음을 알린다.
	currentImageRect = this->m_PersonalProfileRect;
	currentImageRect.MoveToY(-scrollCurrent);
	if (currentImageRect.PtInRect(point) == TRUE && this->m_bTrack != TRUE) {
		this->currentRect = currentImageRect;

		trackMouseEvent.cbSize = sizeof(TRACKMOUSEEVENT);
		trackMouseEvent.dwFlags = TME_HOVER | TME_LEAVE;
		trackMouseEvent.dwHoverTime = HOVER_DEFAULT;
		trackMouseEvent.hwndTrack = (HWND)this;

		TrackMouseEvent(&trackMouseEvent);
		this->SendMessage(WM_MOUSEHOVER, nFlags, MAKELPARAM(point.x, point.y));
	}

	yPos = currentImageRect.bottom;
	currentImageRect = this->m_FriendProfileRect;
	currentImageRect.MoveToY(yPos);
	while (currentImageRect.PtInRect(point) != TRUE && i < this->m_FriendProfileLength && this->m_bTrack != TRUE) {
		i++;
		currentImageRect.MoveToY(currentImageRect.bottom);
	}

	if (currentImageRect.PtInRect(point) == TRUE && this->m_bTrack != TRUE) {
		this->currentRect = currentImageRect;

		trackMouseEvent.cbSize = sizeof(TRACKMOUSEEVENT);
		trackMouseEvent.dwFlags = TME_HOVER | TME_LEAVE;
		trackMouseEvent.dwHoverTime = HOVER_DEFAULT;
		trackMouseEvent.hwndTrack = (HWND)this;

		TrackMouseEvent(&trackMouseEvent);
		this->SendMessage(WM_MOUSEHOVER, nFlags, MAKELPARAM(point.x, point.y));
	}
#endif
}

void ProfileForm::OnMouseLeave() {
	CWnd::OnMouseLeave();
#if 0
	this->m_bTrack = FALSE;

	this->InvalidateRect(&this->currentRect);
#endif
}

void ProfileForm::OnMouseHover(UINT nFlags, CPoint point) {
	CWnd::OnMouseHover(nFlags, point);
	// 현재 범위를 벗어났을 때 FALSE 처리를 해주어야 한다.
	//this->SendMessage(WM_SETFOCUS);
#if 0
	this->m_bTrack = TRUE;

	this->InvalidateRect(&this->currentRect);
#endif
}

void ProfileForm::OnLButtonDown(UINT nFlags, CPoint point) {
	CWnd::OnLButtonDown(nFlags, point);
#if 0
	CRect currentImageRect;

	ItemScrollController* itemScrollController;

	LONG scrollCurrent = 0;
	LONG yPos;
	LONG index;
	LONG i = 1;

	index = this->Find(Observer::SCROLL);
	if (index >= 0) {
		itemScrollController = (ItemScrollController*)this->observers.GetAt(index);

		scrollCurrent = itemScrollController->GetVerticalScroll()->GetPosition();
	}

	currentImageRect = this->m_PersonalProfileRect;
	currentImageRect.MoveToY(-scrollCurrent);
	if (currentImageRect.PtInRect(point) == TRUE) {
		this->currentRect = currentImageRect;
	}

	yPos = currentImageRect.bottom;
	currentImageRect = this->m_FriendProfileRect;
	currentImageRect.MoveToY(yPos);
	while (currentImageRect.PtInRect(point) != TRUE && i < this->m_FriendProfileLength) {
		i++;
		currentImageRect.MoveToY(currentImageRect.bottom);
	}
	if (currentImageRect.PtInRect(point) == TRUE) {
		this->currentRect = currentImageRect;
	}
#endif
}

void ProfileForm::OnLButtonUp(UINT nFlags, CPoint point) {
	CWnd::OnLButtonUp(nFlags, point);
#if 0
	SubjectState* itemState;

	if (this->currentRect.PtInRect(point) == TRUE/* && item->IsFocus() != true*/) {
		this->m_ptDownPoint = point;

		itemState = this->GetSubjectState();
		itemState->SetSelectedPoint(this->m_ptDownPoint.x, this->m_ptDownPoint.y);
	}

	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
#endif
}