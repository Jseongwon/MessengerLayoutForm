// MenuListForm.cpp
/*
���ϸ�Ī : MenuListForm.cpp
��    �� : ������ ��� �� Ŭ������ �����.
�� �� �� : ������ 
�ۼ����� : 2021.10.28
*/
#include "MenuListForm.h"
#include "SubMenuForm.h"
#include "../MessengerLayoutForm.h"
//#include "../MessengerLayout/MessengerLayoutForm.h"
#include "../Observers/ItemObservers.h"
#include "../Observers/ScrollActions.h"
#include "../Observers/Scrolls.h"
#include "../Profiles/Profile.h"
#include "../Generator/DrawingGenerator.h"

MenuListForm::MenuListForm(CWnd* pParentWnd, COLORREF accentColor, COLORREF backgroundColor, COLORREF selectedBackgroundColor,
	COLORREF textColor, COLORREF selectedTextColor)
	: CardListForm(pParentWnd, accentColor, backgroundColor, selectedBackgroundColor, textColor, selectedTextColor) {
	this->p_DownCard = 0;
	this->p_HoverCard = 0;
}

BEGIN_MESSAGE_MAP(MenuListForm, CardListForm)
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

int MenuListForm::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CWnd::OnCreate(lpCreateStruct);

	new ItemScrollController(this);

	SubMenuForm* subMenuForm;
	CardListForm* cardListForm;

	LinkedList<MenuCard>::Node* node;

	CRect clientRect;
	CRect subMenuRect;
	CRect cardListRect;

	LONG systemWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	LONG subMenuWidth;
	LONG width = systemWidth / 22;
	LONG bottomLength;

	// 1. ������ ���Ѵ�.
	this->menuCardRect.SetRect(0, 0, width, width);

	this->GetClientRect(&clientRect);
	systemWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN);

	subMenuWidth = systemWidth / 4;
	subMenuRect.SetRect(width, 0, subMenuWidth, clientRect.Height());

	bottomLength = subMenuRect.Height() - width / 3 * 2;
	cardListRect.SetRect(width, width, subMenuWidth, bottomLength);

	// 2. �޴� �����ܵ��� �����.
	node = this->menuCards.AppendFromTail(MenuCard("C:\\Users\\jeong\\source\\repos\\MessengerLayoutForm_20220316_DrawingGenerator\\MessengerLayoutForm_20220316_DrawingGenerator\\"
		"Resource\\Images\\Common\\Bell64x64.png", "�Խñ�"));

	this->menuCards.AppendFromTail(MenuCard("C:\\Users\\jeong\\source\\repos\\MessengerLayoutForm_20220316_DrawingGenerator\\MessengerLayoutForm_20220316_DrawingGenerator\\"
		"Resource\\Images\\Common\\User64x64.png", "�����"));

	this->menuCards.AppendFromTail(MenuCard("C:\\Users\\jeong\\source\\repos\\MessengerLayoutForm_20220316_DrawingGenerator\\MessengerLayoutForm_20220316_DrawingGenerator\\"
		"Resource\\Images\\Common\\Users64x64.png", "�׷�"));

	this->menuCards.AppendFromTail(MenuCard("C:\\Users\\jeong\\source\\repos\\MessengerLayoutForm_20220316_DrawingGenerator\\MessengerLayoutForm_20220316_DrawingGenerator\\"
		"Resource\\Images\\Common\\Phone64x64.png", "��ȭ"));

	this->menuCards.AppendFromTail(MenuCard("C:\\Users\\jeong\\source\\repos\\MessengerLayoutForm_20220316_DrawingGenerator\\MessengerLayoutForm_20220316_DrawingGenerator\\"
		"Resource\\Images\\Common\\File64x64.png", "����"));

	// 3. �������� ���� �޴��� �����.
	subMenuForm = new SubMenuForm(this->pParentWnd, "�Խñ�", "�۾���");
	((MessengerLayoutForm*)this->pParentWnd)->subMenuForm = subMenuForm;

	subMenuForm->Create(NULL, "SubMenu", WS_CHILD, subMenuRect, AfxGetMainWnd(), NULL);
	subMenuForm->ShowWindow(SW_SHOW);
	subMenuForm->UpdateWindow();

	// 4. �������׿� ���� ����� �����.
	cardListForm = new CardListForm(this->pParentWnd);
	cardListForm->Repair(CardListStyle::POSTINGCARDLISTSTYLE);

	((MessengerLayoutForm*)this->pParentWnd)->cardListForm = cardListForm;

	cardListForm->Create(NULL, "PostingCardList", WS_VSCROLL | WS_CHILD, cardListRect, AfxGetMainWnd(), NULL);
	cardListForm->ShowWindow(SW_SHOW);
	cardListForm->UpdateWindow();

	// 5. �������� �������� �����Ѵ�.
	this->p_DownCard = node->GetObjectLink();
	this->p_DownCard->Repair(CardState::DOWN);

	return 0;
}

void MenuListForm::OnSize(UINT nType, int cx, int cy) {
	CWnd::OnSize(nType, cx, cy);
	ItemState* itemState;

	itemState = dynamic_cast<ItemState*>(this->GetSubjectState());
	itemState->SetScrollSize(cx, cy - 5);

	this->Notify();
	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

void MenuListForm::OnClose() {
	CWnd::OnClose();
	DestroyWindow();
	delete this;
}

void MenuListForm::OnPaint() {
	CPaintDC dc(this);
	CDC memoryDC;

	DrawingGenerator drawingGenerator;

	CRect clientRect;

	LinkedList<MenuCard>::Node* node;

	LONG number;
	LONG x;
	LONG y;

	HPEN hPen;
	HPEN oldPen;

	HBITMAP hBitmap;
	HBITMAP oldBitmap;

	MenuCard* previous = NULL;
	MenuCard* it = NULL;

	this->GetClientRect(&clientRect);

	memoryDC.CreateCompatibleDC(&dc);
	hBitmap = ::CreateCompatibleBitmap(dc, clientRect.right, clientRect.bottom);
	oldBitmap = (HBITMAP)memoryDC.SelectObject(hBitmap);

	memoryDC.FillSolidRect(&clientRect, this->backgroundColor);

	drawingGenerator = DrawingGenerator(this, &memoryDC, this->backgroundColor, this->selectedBackgroundColor, this->textColor, this->selectedTextColor);

	if (this->menuCards.GetLength() > 0) {
		this->menuCards.First();
		it = this->menuCards.GetCurrent()->GetObjectLink();
	}
	while (it != previous) {
		this->menuCards.GetCurrent()->GetObjectLink()->Accept(&drawingGenerator);

		this->menuCards.Next();
		previous = it;
		it = this->menuCards.GetCurrent()->GetObjectLink();
	}

	dc.BitBlt(0, 0, clientRect.right, clientRect.bottom, &memoryDC, 0, 0, SRCCOPY);

	memoryDC.SelectObject(oldBitmap);
	::DeleteObject(hBitmap);
	memoryDC.DeleteDC();

	if (this->p_DownCard != NULL) {
		node = this->menuCards.LinearSearchUnique(this->p_DownCard, CompareMenuCardsInMenuListForm);
		number = this->menuCards.GetNumber(node);

		hPen = CreatePen(PS_DEFAULT, 3, this->selectedTextColor);
		oldPen = (HPEN)dc.SelectObject(hPen);

		x = this->menuCardRect.Width() / 15;
		y = (number - 1) * this->menuCardRect.Height();

		dc.MoveTo(x, y + this->menuCardRect.Height() / 12);
		dc.LineTo(x, y + this->menuCardRect.Height() - this->menuCardRect.Height() / 12);

		dc.SelectObject(oldPen);
		DeleteObject(hPen);
	}
}

void MenuListForm::OnSetFocus(CWnd* pCWnd) {
	CWnd::OnSetFocus(pCWnd);
	this->pParentWnd->SendMessage(WM_KILLFOCUS);
}

void MenuListForm::OnKillFocus(CWnd *pCWnd) {
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

void MenuListForm::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
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

BOOL MenuListForm::OnMouseWheel(UINT nFlags, short zDelta, CPoint point) {
	CWnd::OnMouseWheel(nFlags, zDelta, point);

	ItemScrollController* itemScrollController;

	SCROLLINFO scrollInfo;

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

void MenuListForm::OnMouseMove(UINT nFlags, CPoint point) {
	CWnd::OnMouseMove(nFlags, point);

	CRect clientRect;
	CRect currentImageRect;

	TRACKMOUSEEVENT trackMouseEvent;

	LinkedList<MenuCard>::Node* node;
	MenuCard* previous = NULL;
	MenuCard* it = NULL;

	LONG number;
	LONG i = 0;

	ZeroMemory(&trackMouseEvent, sizeof(TRACKMOUSEEVENT));

	this->GetClientRect(&clientRect);
	if (clientRect.PtInRect(point) == TRUE) {
		this->SetCapture();
	}
	else {
		this->SendMessage(WM_MOUSELEAVE);
		ReleaseCapture();
	}

	if (this->p_HoverCard != NULL) {
		node = this->menuCards.LinearSearchUnique(this->p_HoverCard, CompareMenuCardsInMenuListForm);
		number = this->menuCards.GetNumber(node);

		currentImageRect = this->menuCardRect;
		currentImageRect.MoveToY((number - 1) * this->menuCardRect.Height());

		if (currentImageRect.PtInRect(point) != TRUE) {
			this->number = number;
			this->SendMessage(WM_MOUSELEAVE);
		}
	}

	if (this->menuCards.GetCurrent() != NULL) {
		this->menuCards.First();
		it = this->menuCards.GetCurrent()->GetObjectLink();
	}
	while (it != previous && this->p_HoverCard == NULL) {
		currentImageRect.SetRect(this->menuCardRect.left, i * this->menuCardRect.Height(),
			this->menuCardRect.right, i * this->menuCardRect.Height() + this->menuCardRect.Height());

		if (currentImageRect.PtInRect(point) == TRUE && *it->GetCardState() != (char*)"HOVER") {
			this->p_HoverCard = it;
			this->number = i + 1;

			trackMouseEvent.cbSize = sizeof(TRACKMOUSEEVENT);
			trackMouseEvent.dwFlags = TME_HOVER | TME_LEAVE;
			trackMouseEvent.dwHoverTime = HOVER_DEFAULT;
			trackMouseEvent.hwndTrack = (HWND)this;

			TrackMouseEvent(&trackMouseEvent);
			this->SendMessage(WM_MOUSEHOVER);
		}
		i++;

		this->menuCards.Next();

		previous = it;
		it = this->menuCards.GetCurrent()->GetObjectLink();
	}
}

void MenuListForm::OnMouseLeave() {
	CWnd::OnMouseLeave();
	CRect currentImageRect = this->menuCardRect;
	currentImageRect.MoveToY((number - 1) * this->menuCardRect.Height());

	if (this->p_HoverCard != NULL && this->p_DownCard != this->p_HoverCard) {
		this->p_HoverCard->Repair(CardState::NORMAL);
	}
	else if (this->p_HoverCard != NULL) {
		this->p_HoverCard->Repair(CardState::DOWN);
	}
	this->p_HoverCard = NULL;

	this->InvalidateRect(&currentImageRect);
}

void MenuListForm::OnMouseHover(UINT nFlags, CPoint point) {
	CWnd::OnMouseHover(nFlags, point);
	CRect currentImageRect = this->menuCardRect;
	currentImageRect.MoveToY((number - 1) * this->menuCardRect.Height());
	
	this->SendMessage(WM_SETFOCUS);
	this->p_HoverCard->Repair(CardState::HOVER);

	this->InvalidateRect(&currentImageRect);
}

void MenuListForm::OnLButtonDown(UINT nFlags, CPoint point) {
	CWnd::OnLButtonDown(nFlags, point);

	MenuCard* it = NULL;
	MenuCard* previous = NULL;

	LONG i = 0;
	CRect currentImageRect = this->menuCardRect;

	this->p_DownCard = NULL;
	if (this->menuCards.GetCurrent() != NULL) {
		this->menuCards.First();
		it = this->menuCards.GetCurrent()->GetObjectLink();
	}
	while (it != previous) {
		currentImageRect.SetRect(this->menuCardRect.left, i * this->menuCardRect.Height(),
			this->menuCardRect.right, i * this->menuCardRect.Height() + this->menuCardRect.Height());

		if (currentImageRect.PtInRect(point) == TRUE) {
			this->p_DownCard = it;
			this->number = i + 1;
		}
		else if (it != this->p_HoverCard) {
			it->Repair(CardState::NORMAL);
		}

		i++;

		this->menuCards.Next();
		previous = it;
		it = this->menuCards.GetCurrent()->GetObjectLink();
	}

	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

void MenuListForm::OnLButtonUp(UINT nFlags, CPoint point) {
	CWnd::OnLButtonUp(nFlags, point);

	SubMenuForm* subMenuForm;
	CardListForm* cardListForm;

	CString menuName;
	CString subMenuName;
	CString fileNameLineNumberString;

	MenuCard* it = NULL;
	MenuCard* previous = NULL;

	CRect clientRect;
	CRect subMenuRect;
	CRect cardListRect;
	CRect currentImageRect;

	LONG systemWidth;
	LONG subMenuWidth;
	LONG x;
	LONG bottomLength;

	BOOL onIsNULL;

	currentImageRect = this->menuCardRect;
	if (this->p_DownCard != NULL) {
		currentImageRect.MoveToY((number - 1) * this->menuCardRect.Height());

		if (currentImageRect.PtInRect(point) == TRUE) {
			// 1. �޴� �������� ��Ī�� �д´�.
			menuName = this->p_DownCard->GetName().c_str();

			// 2. ���� �޴��� ��Ī�� �д´�.
			subMenuForm = ((SubMenuForm*)((MessengerLayoutForm*)this->pParentWnd)->subMenuForm);
			subMenuName = subMenuForm->GetSubMenuName();

			// 3. ���� �޴��� Ŭ���ϸ�
			onIsNULL = FALSE;
			if (menuName == "��ȭ" || menuName == "����") {
				// 3.1. �޽��� �ڽ��� ����Ѵ�.
				fileNameLineNumberString.Format("%s(%d): error: ", __FILE__, __LINE__ + 1);
				MessageBox(fileNameLineNumberString + "�غ����Դϴ�.", "�޽���", MB_OK);

				// 3.2. ������ ����ġ ��Ų��.
				if (this->menuCards.GetCurrent() != NULL) {
					this->menuCards.First();
					it = this->menuCards.GetCurrent()->GetObjectLink();
				}
				while (it != previous && it->GetName() != (LPCTSTR)subMenuName) {
					this->menuCards.Next();
					previous = it;
					it = this->menuCards.GetCurrent()->GetObjectLink();
				}
				if (it != previous && it->GetName() == (LPCTSTR)subMenuName) {
					this->p_DownCard->Repair(CardState::NORMAL);

					this->p_DownCard = it;
					this->p_DownCard->Repair(CardState::DOWN);
				}
				onIsNULL = TRUE;
			}

			// 4. ���� �޴��� ��Ī�� �޴� �������� ��Ī�� �ٸ���
			if (subMenuName != menuName && onIsNULL != TRUE) {/*this->p_DownCard != this->p_HoverCard*/
				// 4.1. �����Ѵ�.
				this->p_DownCard->Repair(CardState::HOVER);

				// 4.2. ���� �޴� �����츦 ���ش�.
				subMenuForm->SendMessage(WM_CLOSE);

				// 4.3. ���� �޴� �������� ������ ���Ѵ�.
				this->GetClientRect(&clientRect);
				systemWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN);
				x = systemWidth / 22;

				subMenuWidth = systemWidth / 4;
				subMenuRect.SetRect(x, 0, subMenuWidth, clientRect.Height());

				bottomLength = subMenuRect.Height() - x / 3 * 2;
				cardListRect.SetRect(x, x, subMenuWidth, bottomLength);

				// 4.4. ��Ī�� ���� ���� �޴� �����츦 �����.
				// (��������, �۾���), (�����, ��� ã�� �� �ʴ�), (�׷�, ���� �Ǵ� �׷� �����)
				if (menuName == "�Խñ�") {
					subMenuForm = new SubMenuForm(this->pParentWnd, "�Խñ�", "�۾���");
				}
				else if (menuName == "�����") {
					subMenuForm = new SubMenuForm(this->pParentWnd, "�����", "��� ã�� �� �ʴ�");
				}
				else if (menuName == "�׷�") {
					subMenuForm = new SubMenuForm(this->pParentWnd, "�׷�", "���� �Ǵ� �׷� �����");
				}
				((MessengerLayoutForm*)this->pParentWnd)->subMenuForm = subMenuForm;

				subMenuForm->Create(NULL, "SubMenu", WS_CHILD, subMenuRect, AfxGetMainWnd(), NULL);
				subMenuForm->ShowWindow(SW_SHOW);
				subMenuForm->UpdateWindow();

				cardListForm = ((CardListForm*)((MessengerLayoutForm*)this->pParentWnd)->cardListForm);
				if (cardListForm != NULL) {
					cardListForm->SendMessage(WM_CLOSE);
					((MessengerLayoutForm*)this->pParentWnd)->cardListForm = NULL;
				}

				if (menuName == "�Խñ�") {
					cardListForm = new CardListForm(this->pParentWnd);
					cardListForm->Repair(CardListStyle::POSTINGCARDLISTSTYLE);

					((MessengerLayoutForm*)this->pParentWnd)->cardListForm = cardListForm;

					cardListForm->Create(NULL, "PostingCardList", WS_VSCROLL | WS_CHILD, cardListRect, AfxGetMainWnd(), NULL);
					cardListForm->ShowWindow(SW_SHOW);
					cardListForm->UpdateWindow();
				}
				else if (menuName == "�����") {
					cardListForm = new CardListForm(this->pParentWnd);
					cardListForm->Repair(CardListStyle::USERCARDLISTSTYLE);

					((MessengerLayoutForm*)this->pParentWnd)->cardListForm = cardListForm;

					cardListForm->Create(NULL, "UserCardList", WS_VSCROLL | WS_CHILD, cardListRect, AfxGetMainWnd(), NULL);
					cardListForm->ShowWindow(SW_SHOW);
					cardListForm->UpdateWindow();
				}
				else if (menuName == "�׷�") {
					
				}
			}
		}
	}

	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

int CompareMenuCardsInMenuListForm(void* one, void* other) {
	int ret;
	if (one < other) {
		ret = -1;
	}
	else if (one == other) {
		ret = 0;
	}
	else if (one > other) {
		ret = 1;
	}
	return ret;
}