// PostingCardListStyle.h
/*
파일명칭 : PostingCardListStyle.cpp
기    능 : 게시글 카드목록의 상태 클래스를 만든다.
작 성 자 : 정성원
작성일자 : 2022.04.28
*/
#include "PostingCardListStyle.h"
#include "CardListForm.h"
#include "ProfileForm.h"
#include "ProfileCompiler.h"
#include "ProfileCompileMode.h"
#include "../Observers/ItemObservers.h"
#include "../Observers/Scrolls.h"
#include "../MessengerLayoutForm.h"
#include "../Generator/DrawingGenerator.h"
using namespace parkcom;

PostingCardListStyle::PostingCardListStyle(CWnd* pCurrentWnd)
	: CardListStyle(pCurrentWnd) {

}

PostingCardListStyle::~PostingCardListStyle() {

}

void PostingCardListStyle::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CRect mainFormRect;
	CRect clientRect;
	CRect documentRect;

	LONG systemWidth;
	LONG menuBarWidth;
	LONG subMenuWidth;
	LONG itemHeight;

	// 영역들을 구한다.
	systemWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	menuBarWidth = systemWidth / 22;
	subMenuWidth = systemWidth / 4;
	itemHeight = menuBarWidth / 3;

	this->pCurrentWnd->GetClientRect(&clientRect);
	AfxGetMainWnd()->GetClientRect(&mainFormRect);

	documentRect.SetRect(subMenuWidth, 0, mainFormRect.right, mainFormRect.bottom);

	// 원래는 clientRect.Width()로 right 값을 줘야 하는데, 윈도우가 생성될 때 너비가 일치하지 않음.
	this->m_ProfileRect.SetRect(0, 0, subMenuWidth - menuBarWidth, itemHeight);

	((MessengerLayoutForm*)AfxGetMainWnd())->profileForm = new ProfileForm(this->pCurrentWnd);
	((MessengerLayoutForm*)AfxGetMainWnd())->profileForm->Repair(ProfileStyle::POSTINGPROFILESTYLE);
	((MessengerLayoutForm*)AfxGetMainWnd())->profileForm->Create(NULL, "Profile", WS_VSCROLL | WS_CHILD, documentRect, AfxGetMainWnd(), NULL);// WS_CLIPCHILDREN
	((MessengerLayoutForm*)AfxGetMainWnd())->profileForm->ShowWindow(SW_SHOW);
	((MessengerLayoutForm*)AfxGetMainWnd())->profileForm->UpdateWindow();
}

void PostingCardListStyle::OnMouseMove(UINT nFlags, CPoint point) {
	CRect clientRect;
	CRect currentImageRect;

	ItemScrollController* itemScrollController;

	LONG scrollCurrent = 0;
	LONG index;
	LONG i = 1;

	TRACKMOUSEEVENT trackMouseEvent;

	ZeroMemory(&trackMouseEvent, sizeof(TRACKMOUSEEVENT));

	index = ((ItemSubject*)this->pCurrentWnd)->Find(Observer::SCROLL);
	if (index >= 0) {
		itemScrollController = (ItemScrollController*)((ItemSubject*)this->pCurrentWnd)->GetAt(index);

		scrollCurrent = itemScrollController->GetVerticalScroll()->GetPosition();
	}

	this->pCurrentWnd->GetClientRect(&clientRect);
	if (clientRect.PtInRect(point) == TRUE) {
		this->pCurrentWnd->SetCapture();
	}
	else {
		this->pCurrentWnd->SendMessage(WM_MOUSELEAVE);
		ReleaseCapture();
	}

	// 1. 사용자 영역에 없으면 마우스가 떠났음을 알린다.
	if (dynamic_cast<CardListForm*>(this->pCurrentWnd)->currentRect.PtInRect(point) != TRUE && dynamic_cast<CardListForm*>(this->pCurrentWnd)->m_bTrack == TRUE) {
		this->pCurrentWnd->SendMessage(WM_MOUSELEAVE, nFlags, MAKELPARAM(point.x, point.y));
	}

	currentImageRect = this->m_ProfileRect;
	currentImageRect.MoveToY(-scrollCurrent);
	while (currentImageRect.PtInRect(point) != TRUE && i < dynamic_cast<CardListForm*>(this->pCurrentWnd)->m_CardLength && dynamic_cast<CardListForm*>(this->pCurrentWnd)->m_bTrack != TRUE) {
		i++;
		currentImageRect.MoveToY(currentImageRect.bottom);
	}

	if (currentImageRect.PtInRect(point) == TRUE && dynamic_cast<CardListForm*>(this->pCurrentWnd)->m_bTrack != TRUE) {
		dynamic_cast<CardListForm*>(this->pCurrentWnd)->currentRect = currentImageRect;

		trackMouseEvent.cbSize = sizeof(TRACKMOUSEEVENT);
		trackMouseEvent.dwFlags = TME_HOVER | TME_LEAVE;
		trackMouseEvent.dwHoverTime = HOVER_DEFAULT;
		trackMouseEvent.hwndTrack = (HWND)this->pCurrentWnd;

		TrackMouseEvent(&trackMouseEvent);
		this->pCurrentWnd->SendMessage(WM_MOUSEHOVER, nFlags, MAKELPARAM(point.x, point.y));
	}
}

void PostingCardListStyle::OnLButtonClicked(UINT nFlags, CPoint point) {
	CRect currentImageRect;

	ItemScrollController* itemScrollController;

	LONG scrollCurrent = 0;
	LONG index;
	LONG i = 1;

	index = dynamic_cast<CardListForm*>(this->pCurrentWnd)->Find(Observer::SCROLL);
	if (index >= 0) {
		itemScrollController = (ItemScrollController*)dynamic_cast<CardListForm*>(this->pCurrentWnd)->GetAt(index);

		scrollCurrent = itemScrollController->GetVerticalScroll()->GetPosition();
	}

	currentImageRect = this->m_ProfileRect;
	currentImageRect.MoveToY(-scrollCurrent);
	while (currentImageRect.PtInRect(point) != TRUE && i < dynamic_cast<CardListForm*>(this->pCurrentWnd)->m_CardLength) {
		i++;
		currentImageRect.MoveToY(currentImageRect.bottom);
	}
	if (currentImageRect.PtInRect(point) == TRUE) {
		dynamic_cast<CardListForm*>(this->pCurrentWnd)->currentRect = currentImageRect;
	}
}

void PostingCardListStyle::OnDraw(CDC* pDC) {
	CDC memoryDC;

	DrawingGenerator drawingGenerator;

	ProfileCompiler profileCompiler;

	LOGFONT logFont;

	HBITMAP hBitmap;
	HBITMAP oldBitmap;

	HPEN hPen;
	HPEN oldPen;

	LONG i = 0;

	CRect clientRect;
	CRect friendProfileRect;

	((CardListForm*)this->pCurrentWnd)->GetClientRect(&clientRect);

	memoryDC.CreateCompatibleDC(pDC);
	hBitmap = ::CreateCompatibleBitmap(*pDC, clientRect.right, clientRect.bottom);
	oldBitmap = (HBITMAP)memoryDC.SelectObject(hBitmap);

	memoryDC.FillSolidRect(&clientRect, ((CardListForm*)this->pCurrentWnd)->backgroundColor);

	ZeroMemory(&logFont, sizeof(LOGFONT));
	strcpy_s(logFont.lfFaceName, "맑은 고딕");

	drawingGenerator = DrawingGenerator(this->pCurrentWnd, &memoryDC, ((CardListForm*)this->pCurrentWnd)->backgroundColor, ((CardListForm*)this->pCurrentWnd)->selectedBackgroundColor, ((CardListForm*)this->pCurrentWnd)->textColor, ((CardListForm*)this->pCurrentWnd)->selectedTextColor);

	profileCompiler = ProfileCompiler(this->pCurrentWnd, &drawingGenerator);
	profileCompiler.Repair(ProfileCompileMode::POSTINGPROFILE);
	profileCompiler.Compile();

	pDC->BitBlt(0, 0, clientRect.right, clientRect.bottom, &memoryDC, 0, 0, SRCCOPY);

	memoryDC.SelectObject(oldBitmap);
	::DeleteObject(hBitmap);
	memoryDC.DeleteDC();

	hPen = CreatePen(PS_DEFAULT, 1, ((CardListForm*)this->pCurrentWnd)->selectedBackgroundColor);
	oldPen = (HPEN)pDC->SelectObject(hPen);

	pDC->MoveTo(0, 0);
	pDC->LineTo(clientRect.Width(), 0);

	pDC->SelectObject(oldPen);
	DeleteObject(hPen);
}