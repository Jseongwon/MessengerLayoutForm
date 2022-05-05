// SubMenuForm.cpp
/*
���ϸ�Ī : SubMenuForm.cpp
��    �� : ���� �޴� �� Ŭ������ �����.
�� �� �� : ������
�ۼ����� : 2022.03.18
*/
#include "SubMenuForm.h"
#include "CardListForm.h"
#include "../MessengerLayoutForm.h"
#include "../Generator/DrawingGenerator.h"
#define IMAGE_RATE 3

SubMenuForm::SubMenuForm(CWnd* pParentWnd, CString subMenuName, CString buttonName, COLORREF accentColor, COLORREF backgroundColor, COLORREF selectedBackgroundColor, COLORREF textColor, COLORREF selectedTextColor) {
	this->pParentWnd = pParentWnd;
	this->p_SubMenuCard = 0;
	this->accentColor = accentColor;
	this->backgroundColor = backgroundColor;
	this->selectedBackgroundColor = selectedBackgroundColor;
	this->textColor = textColor;
	this->selectedTextColor = selectedTextColor;

	this->onIsFilter = FALSE;
	this->onIsSetting = FALSE;
	this->onIsButtonArea = FALSE;
	this->m_bTrack = FALSE;

	this->downImageNumber = -1;

	strcpy_s(this->subMenuName, sizeof(this->subMenuName), (LPCTSTR)subMenuName);
	strcpy_s(this->buttonName, sizeof(this->buttonName), (LPCTSTR)buttonName);
}

BEGIN_MESSAGE_MAP(SubMenuForm, CWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEHOVER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

int SubMenuForm::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CWnd::OnCreate(lpCreateStruct);

	this->p_SubMenuCard = new SubMenuCard(this->subMenuName, this->buttonName);

	return 0;
}

void SubMenuForm::OnSize(UINT nType, int cx, int cy) {
	CWnd::OnSize(nType, cx, cy);
}

void SubMenuForm::OnClose() {
	if (this->p_SubMenuCard != NULL) {
		delete this->p_SubMenuCard;
	}

	CWnd::OnClose();
	DestroyWindow();
	delete this;
}

void SubMenuForm::OnPaint() {
	CPaintDC dc(this);

	DrawingGenerator drawingGenerator(this, &dc, this->backgroundColor, this->selectedBackgroundColor, this->textColor, this->selectedTextColor);

	CRect clientRect;
	CRect topRect;
	CRect bottomRect;

	LONG systemWidth;
	LONG x;
	LONG subMenuWidth;
	LONG bottomLength;

	this->GetClientRect(&clientRect);
	systemWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	x = systemWidth / 22;

	subMenuWidth = systemWidth / 4;
	topRect.SetRect(0, 0, clientRect.Width(), x);
	
	bottomLength = clientRect.Height() - x / 3 * 2;
	bottomRect.SetRect(0, bottomLength, clientRect.Width(), clientRect.Height());

	dc.FillSolidRect(&topRect, this->backgroundColor);
	dc.FillSolidRect(&bottomRect, this->backgroundColor);

	this->p_SubMenuCard->Accept(&drawingGenerator);
}

void SubMenuForm::OnSetFocus(CWnd* pCWnd) {
	CWnd::OnSetFocus(pCWnd);
	this->pParentWnd->SendMessage(WM_KILLFOCUS);
}

void SubMenuForm::OnKillFocus(CWnd *pCWnd) {
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

BOOL SubMenuForm::OnMouseWheel(UINT nFlags, short zDelta, CPoint point) {
	CWnd::OnMouseWheel(nFlags, zDelta, point);

	CRect cardListRect;

	LONG subMenuCardTopExtent;

	WORD wKeyState = 0;

	CardListForm* cardListForm;
	CPoint cardListPoint;

	this->ScreenToClient(&point);

	subMenuCardTopExtent = GetSystemMetrics(SM_CXVIRTUALSCREEN) / 22;

	cardListPoint = CPoint(point.x, point.y - subMenuCardTopExtent);
	cardListForm = ((CardListForm*)((MessengerLayoutForm*)this->pParentWnd)->cardListForm);
	if (cardListForm != NULL) {
		cardListForm->GetClientRect(&cardListRect);
		cardListRect.MoveToY(subMenuCardTopExtent);
	}

	if (cardListRect.PtInRect(cardListPoint)) {
		if (GetKeyState(VK_CONTROL) & 0x8000) {
			wKeyState |= MK_CONTROL;
		}
		if (GetKeyState(VK_CONTROL) & 0x8000) {
			wKeyState |= MK_SHIFT;
		}

		cardListForm->SendMessage(WM_MOUSEWHEEL, MAKEWPARAM(wKeyState, zDelta), MAKELPARAM(cardListPoint.x, cardListPoint.y));
	}

	return TRUE;
}

void SubMenuForm::OnMouseMove(UINT nFlags, CPoint point) {
	CWnd::OnMouseMove(nFlags, point);

	CRect clientRect;
	CRect cardListRect;
	CRect subMenuCardRect;
	CRect filterRect;
	CRect settingRect;
	CRect buttonAreaRect;

	LONG subMenuCardTopExtent;
	LONG imageMargin;
	LONG buttonExtent;
	LONG x;
	LONG y;
	LONG width;
	LONG height;

	BOOL onIsItemListFormInside = FALSE;

	BITMAP filterBitmap;
	BITMAP settingBitmap;

	CardListForm* cardListForm;

	TRACKMOUSEEVENT trackMouseEvent;

	CPoint cardListPoint;

	ZeroMemory(&trackMouseEvent, sizeof(TRACKMOUSEEVENT));

	// 1. �������� ���Ѵ�.
	this->GetClientRect(&subMenuCardRect);
	subMenuCardTopExtent = GetSystemMetrics(SM_CXVIRTUALSCREEN) / 22;
	imageMargin = subMenuCardRect.Width() / 16;

	// ����
	this->p_SubMenuCard->GetFilterImage().GetBitmap(&filterBitmap);
	x = subMenuCardRect.Width() - ((filterBitmap.bmWidth / IMAGE_RATE) * 2 + imageMargin * 2);
	y = subMenuCardTopExtent / 2 - filterBitmap.bmHeight / IMAGE_RATE / 2;
	width = x + (filterBitmap.bmWidth / IMAGE_RATE);
	height = y + filterBitmap.bmHeight / IMAGE_RATE;

	filterRect.SetRect(x, y, width, height);

	// ����
	this->p_SubMenuCard->GetSettingImage().GetBitmap(&settingBitmap);
	x = filterRect.right + imageMargin;
	y = subMenuCardTopExtent / 2 - settingBitmap.bmHeight / IMAGE_RATE / 2;
	width = x + (settingBitmap.bmWidth / IMAGE_RATE);
	height = y + settingBitmap.bmHeight / IMAGE_RATE;

	settingRect.SetRect(x, y, width, height);

	// ��ư
	buttonExtent = subMenuCardTopExtent / 3 * 2;

	buttonAreaRect.SetRect(subMenuCardRect.left + imageMargin, subMenuCardRect.Height() - buttonExtent, subMenuCardRect.right - imageMargin, subMenuCardRect.bottom - imageMargin);

	cardListPoint = CPoint(point.x, point.y - subMenuCardTopExtent);
	cardListForm = ((CardListForm*)((MessengerLayoutForm*)this->pParentWnd)->cardListForm);
	if (cardListForm != NULL) {
		cardListForm->GetClientRect(&cardListRect);
	}
	// 2. ī�� ��� ������ ������
	if (cardListRect.PtInRect(cardListPoint) == TRUE) {
		this->SendMessage(WM_MOUSELEAVE);

		// 2.1. �׸� ��Ͽ� ���콺 �̵��� ������ �˸���.
		cardListForm->SendMessage(WM_MOUSEMOVE, nFlags, MAKELPARAM(cardListPoint.x, cardListPoint.y));

		onIsItemListFormInside = TRUE;
	}

	// 3. �׸� ��� ������ ������
	if (onIsItemListFormInside != TRUE) {
		// + ȭ�� ���� �ȿ� ������ ĸ���ϰ� ������ ĸ�ĸ� �����.
		this->GetClientRect(&clientRect);
		if (clientRect.PtInRect(point) == TRUE && cardListRect.PtInRect(point) != TRUE) {
			this->SetCapture();
		}
		else {
			this->SendMessage(WM_MOUSELEAVE);
			ReleaseCapture();
		}
		// 3.1. ���� �̹��� ������ ���õǾ� �ְ�, ������ ����Ʈ�� ���ų� ���� �̹��� ������ ���õǾ� �ְ�, ������ ����Ʈ�� ������ ���콺�� �������� �˸���.
		if ((filterRect.PtInRect(point) != TRUE && this->onIsFilter == TRUE) ||
			(settingRect.PtInRect(point) != TRUE && this->onIsSetting == TRUE) ||
			buttonAreaRect.PtInRect(point) != TRUE && this->onIsButtonArea == TRUE) {
			this->SendMessage(WM_MOUSELEAVE);
		}

		this->onIsFilter = FALSE;
		this->onIsSetting = FALSE;
		this->onIsButtonArea = FALSE;
		// 3.2. ���� �̹��� ������ ����Ʈ�� ������ ���� �̹��� ������ ���õǾ� ������ �����Ѵ�.
		if (filterRect.PtInRect(point) == TRUE) {
			this->onIsFilter = TRUE;
			this->currentRect = filterRect;
		}
		// 3.3. ���� �̹��� ������ ����Ʈ�� ������ ���� �̹��� ������ ���õǾ� ������ �����Ѵ�.
		else if (settingRect.PtInRect(point) == TRUE) {
			this->onIsSetting = TRUE;
			this->currentRect = settingRect;
		}
		// 3.4. ��ư ������ ����Ʈ�� ������ ��ư ������ ���õǾ� ������ �����Ѵ�.
		else if (buttonAreaRect.PtInRect(point) == TRUE) {
			this->onIsButtonArea = TRUE;
			this->currentRect = buttonAreaRect;
		}
		// 3.5. �̹��� ������ ���õǾ� �ְ�, ���� �ȿ��� �����̴� ���� �ƴϸ� ������ ���콺�� �������� �˸���.
		if ((this->onIsFilter == TRUE || this->onIsSetting == TRUE || this->onIsButtonArea == TRUE) && this->m_bTrack != TRUE) {
			trackMouseEvent.cbSize = sizeof(TRACKMOUSEEVENT);
			trackMouseEvent.dwFlags = TME_HOVER | TME_LEAVE;
			trackMouseEvent.dwHoverTime = HOVER_DEFAULT;
			trackMouseEvent.hwndTrack = (HWND)this;

			TrackMouseEvent(&trackMouseEvent);
			this->SendMessage(WM_MOUSEHOVER);
		}
	}
}

void SubMenuForm::OnMouseLeave() {
	CWnd::OnMouseLeave();
	if (this->onIsFilter == TRUE) {
		this->p_SubMenuCard->Repair(SubMenuCard::FILTER, false);
		this->onIsFilter = FALSE;
	}
	else if (this->onIsSetting == TRUE) {
		this->p_SubMenuCard->Repair(SubMenuCard::SETTING, false);
		this->onIsSetting = FALSE;
	}
	else if (this->onIsButtonArea == TRUE) {
		this->p_SubMenuCard->SetButtonState(SubMenuCard::NORMAL);
		this->onIsButtonArea = FALSE;
	}
	this->m_bTrack = FALSE;
	this->InvalidateRect(&this->currentRect);
}

void SubMenuForm::OnMouseHover(UINT nFlags, CPoint point) {
	CWnd::OnMouseHover(nFlags, point);
	if (this->onIsFilter == TRUE) {
		this->p_SubMenuCard->Repair(SubMenuCard::FILTER, true);
		this->onIsFilter = FALSE;
	}
	else if (this->onIsSetting == TRUE) {
		this->p_SubMenuCard->Repair(SubMenuCard::SETTING, true);
		this->onIsSetting = FALSE;
	}
	else if (this->onIsButtonArea == TRUE) {
		this->p_SubMenuCard->SetButtonState(SubMenuCard::HOVER);
		this->onIsButtonArea = FALSE;
	}
	this->m_bTrack = TRUE;
	this->InvalidateRect(&this->currentRect);
}

void SubMenuForm::OnLButtonDown(UINT nFlags, CPoint point) {
	CWnd::OnLButtonDown(nFlags, point);

	CardListForm* cardListForm;

	CPoint cardListPoint;

	CRect subMenuCardRect;
	CRect cardListRect;
	CRect filterRect;
	CRect settingRect;
	CRect buttonAreaRect;

	LONG subMenuCardTopExtent;
	Long imageMargin;
	Long buttonExtent;
	LONG x;
	LONG y;
	LONG width;
	LONG height;

	BOOL onIsItemListFormInside = FALSE;

	BITMAP filterBitmap;
	BITMAP settingBitmap;

	// 1. �������� ���Ѵ�.
	this->GetClientRect(&subMenuCardRect);
	subMenuCardTopExtent = GetSystemMetrics(SM_CXVIRTUALSCREEN) / 22;
	imageMargin = subMenuCardRect.Width() / 16;

	// ����
	this->p_SubMenuCard->GetFilterImage().GetBitmap(&filterBitmap);
	x = subMenuCardRect.Width() - ((filterBitmap.bmWidth / IMAGE_RATE) * 2 + imageMargin * 2);
	y = subMenuCardTopExtent / 2 - filterBitmap.bmHeight / IMAGE_RATE / 2;
	width = x + (filterBitmap.bmWidth / IMAGE_RATE);
	height = y + filterBitmap.bmHeight / IMAGE_RATE;

	filterRect.SetRect(x, y, width, height);

	// ����
	this->p_SubMenuCard->GetSettingImage().GetBitmap(&settingBitmap);
	x = filterRect.right + imageMargin;
	y = subMenuCardTopExtent / 2 - settingBitmap.bmHeight / IMAGE_RATE / 2;
	width = x + (settingBitmap.bmWidth / IMAGE_RATE);
	height = y + settingBitmap.bmHeight / IMAGE_RATE;

	settingRect.SetRect(x, y, width, height);

	// ��ư
	buttonExtent = subMenuCardTopExtent / 3 * 2;

	buttonAreaRect.SetRect(subMenuCardRect.left + imageMargin, subMenuCardRect.Height() - buttonExtent, subMenuCardRect.right - imageMargin, subMenuCardRect.bottom - imageMargin);

	cardListForm = ((CardListForm*)((MessengerLayoutForm*)this->pParentWnd)->cardListForm);
	if (cardListForm != NULL) {
		cardListForm->GetClientRect(&cardListRect);
		cardListRect.MoveToY(subMenuCardTopExtent);
	}
	// 2. ī�� ��� ������ Ŭ���ϸ�
	this->downImageNumber = -1;
	if (cardListRect.PtInRect(point) == TRUE) {
		cardListPoint = CPoint(point.x, point.y - subMenuCardTopExtent);
		// 2.1. �׸� ��Ͽ� ���콺 �̵��� ������ �˸���.
		cardListForm->SendMessage(WM_LBUTTONDOWN, nFlags, MAKELPARAM(cardListPoint.x, cardListPoint.y));

		this->currentRect = cardListRect;
		this->downImageNumber = CARDLIST;

		onIsItemListFormInside = TRUE;
	}
	// 3. ���� �̹����� Ŭ���ϸ�
	else if (filterRect.PtInRect(point) == TRUE) {
		this->currentRect = filterRect;
		this->downImageNumber = FILTER;
	}
	// 4. ���� �̹����� Ŭ���ϸ�
	else if (settingRect.PtInRect(point) == TRUE) {
		this->currentRect = settingRect;
		this->downImageNumber = SETTING;
	}
	// 5. ��ư�� Ŭ���ϸ�
	else if (buttonAreaRect.PtInRect(point) == TRUE) {
		this->currentRect = buttonAreaRect;
		this->p_SubMenuCard->SetButtonState(SubMenuCard::DOWN);
		this->downImageNumber = BOTTOMBUTTON;
	}
	this->InvalidateRect(&this->currentRect);
}

void SubMenuForm::OnLButtonUp(UINT nFlags, CPoint point) {
	CWnd::OnLButtonUp(nFlags, point);

	CardListForm* cardListForm;

	CPoint cardListPoint;

	LONG subMenuCardTopExtent = GetSystemMetrics(SM_CXVIRTUALSCREEN) / 22;

	// 1. ī�� ��� ������ ����� Ŭ��������
	if (this->downImageNumber == CARDLIST && this->currentRect.PtInRect(point) == TRUE) {
		cardListForm = ((CardListForm*)((MessengerLayoutForm*)this->pParentWnd)->cardListForm);

		cardListPoint = CPoint(point.x, point.y - subMenuCardTopExtent);
		// 2.1. �׸� ��Ͽ� ���콺 �̵��� ������ �˸���.
		cardListForm->SendMessage(WM_LBUTTONUP, nFlags, MAKELPARAM(cardListPoint.x, cardListPoint.y));
	}
	// 2. ���� �̹����� ����� Ŭ��������
	else if (this->downImageNumber == FILTER && this->currentRect.PtInRect(point) == TRUE) {

	}
	// 3. ���� �̹����� ����� Ŭ��������
	else if (this->downImageNumber == SETTING && this->currentRect.PtInRect(point) == TRUE) {

	}
	// 4. ��ư�� ����� Ŭ��������
	else if (this->downImageNumber == BOTTOMBUTTON && this->currentRect.PtInRect(point) == TRUE) {
		this->p_SubMenuCard->SetButtonState(SubMenuCard::NORMAL);
	}
	this->InvalidateRect(&this->currentRect);
}