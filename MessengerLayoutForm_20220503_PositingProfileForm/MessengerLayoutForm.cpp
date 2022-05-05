// MessengerLayoutForm.cpp
/*
파일명칭 : MessengerLayoutForm.cpp
기    능 : 메신저의 메인 윈도우 클래스를 만든다.
작 성 자 : 정성원
작성일자 : 2022.02.17
*/
#include "MessengerLayoutForm.h"
#include "Layout\CardListForm.h"
#include "Layout\ProfileForm.h"
#include "Layout\MenuListForm.h"
#include "Layout\SubMenuForm.h"
#if 0
#include "../MenuBar/NoticeMenuForm.h"
#include "../MenuBar/UserMenuForm.h"
#include "../MenuBar/GroupMenuForm.h"
#include "../Item/Items.h"
#include "../Item/ItemDirector.h"
#endif
MessengerLayoutForm::MessengerLayoutForm() {
	this->menuListForm = NULL;
	this->subMenuForm = NULL;
	this->cardListForm = NULL;
	this->profileForm = NULL;
}

BEGIN_MESSAGE_MAP(MessengerLayoutForm, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()

int MessengerLayoutForm::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CFrameWnd::OnCreate(lpCreateStruct);

	// 시스템 화면의 전체 크기를 구한다.
	CRect clientRect;
	CRect menuBarRect;

	CString hostName;

	LONG systemWidth;

	int menuBarWidth;

	this->GetClientRect(&clientRect);
	systemWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	menuBarWidth = systemWidth / 22;

	menuBarRect.right = menuBarWidth;
	menuBarRect.bottom = clientRect.Height();

	hostName = AfxGetApp()->GetProfileString("MessengerSection", "LoginInfo", "alice@hotmail.com");
	strcpy_s(this->hostName, sizeof(this->hostName), (LPCTSTR)hostName);

	this->menuListForm = new MenuListForm(this);
	this->menuListForm->Create(NULL, "MenuBar", WS_CHILD, menuBarRect, this, NULL);
	this->menuListForm->ShowWindow(SW_SHOW);
	this->menuListForm->UpdateWindow();

	this->Invalidate();

	return 0;
}

void MessengerLayoutForm::OnSize(UINT nType, int cx, int cy) {
	CFrameWnd::OnSize(nType, cx, cy);

	CRect clientRect;
	CRect menuBarRect;
	CRect subMenuRect;
	CRect cardListRect;
	CRect profileRect;

	LONG systemWidth;
	LONG subMenuWidth;
	LONG bottomLength;

	int menuBarWidth;

	this->GetClientRect(&clientRect);
	systemWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	menuBarWidth = systemWidth / 22;

	menuBarRect.right = menuBarWidth;
	menuBarRect.bottom = clientRect.Height();

	subMenuWidth = systemWidth / 4;
	subMenuRect.SetRect(menuBarWidth, 0, subMenuWidth, menuBarRect.Height());

	bottomLength = cy - menuBarWidth / 3 * 2;
	cardListRect.SetRect(menuBarWidth, menuBarWidth, systemWidth / 4, bottomLength);

	profileRect.SetRect(subMenuWidth, 0, clientRect.right, clientRect.bottom);

	this->menuListForm->SetWindowPos(NULL, menuBarRect.left, menuBarRect.top, menuBarRect.Width(), menuBarRect.Height(), SWP_DRAWFRAME);
	this->subMenuForm->SetWindowPos(NULL, subMenuRect.left, subMenuRect.top, subMenuRect.Width(), subMenuRect.Height(), SWP_DRAWFRAME);
	if(this->cardListForm != NULL)
		this->cardListForm->SetWindowPos(NULL, cardListRect.left, cardListRect.top, cardListRect.Width(), cardListRect.Height(), SWP_DRAWFRAME);
	if (this->profileForm != NULL)
		this->profileForm->SetWindowPos(NULL, profileRect.left, profileRect.top, profileRect.Width(), profileRect.Height(), SWP_DRAWFRAME);
}

void MessengerLayoutForm::OnPaint() {
	CPaintDC dc(this);
}

void MessengerLayoutForm::OnClose() {
	//AfxGetApp()->WriteProfileString("MessengerSection", "LoginInfo", this->hostName);
	if (this->menuListForm != NULL) {
		this->menuListForm->SendMessage(WM_CLOSE);
		this->menuListForm = NULL;
	}
	if (this->subMenuForm != NULL) {
		this->subMenuForm->SendMessage(WM_CLOSE);
		this->subMenuForm = NULL;
	}
	if (this->cardListForm != NULL) {
		this->cardListForm->SendMessage(WM_CLOSE);
		this->cardListForm = NULL;
	}
	if (this->profileForm != NULL) {
		this->profileForm->SendMessage(WM_CLOSE);
		this->profileForm = NULL;
	}
	
	CFrameWnd::OnClose();
}

void MessengerLayoutForm::OnKillFocus(CWnd *pCWnd) {
	if (this->menuListForm != NULL) {
		this->menuListForm->SendMessage(WM_KILLFOCUS);
	}
	if (this->subMenuForm != NULL) {
		this->subMenuForm->SendMessage(WM_KILLFOCUS);
	}
	if (this->cardListForm != NULL) {
		this->cardListForm->SendMessage(WM_KILLFOCUS);
	}
	if (this->profileForm != NULL) {
		this->profileForm->SendMessage(WM_KILLFOCUS);
	}
	
	CFrameWnd::OnKillFocus(pCWnd);
}
#if 0
void MessengerLayoutForm::OnMouseMove(UINT nFlags, CPoint point) {
	CFrameWnd::OnMouseMove(nFlags, point);

	CRect menuBarRect;
	CRect subMenuRect;
	CRect cardListRect;

	this->menuListForm->GetClientRect(&menuBarRect);
	this->subMenuForm->GetClientRect(&subMenuRect);
	this->cardListForm->GetClientRect(&cardListRect);

	this->menuListForm->ScreenToClient(&point);
	if (menuBarRect.PtInRect(point) == TRUE) {
		this->menuListForm->SendMessage(WM_MOUSEMOVE, nFlags, MAKELPARAM(point.x, point.y));
	}
	this->subMenuForm->ScreenToClient(&point);
	if (subMenuRect.PtInRect(point) == TRUE) {
		this->subMenuForm->SendMessage(WM_MOUSEMOVE, nFlags, MAKELPARAM(point.x, point.y));
	}
	this->cardListForm->ScreenToClient(&point);
	if (cardListRect.PtInRect(point) == TRUE) {
		this->cardListForm->SendMessage(WM_MOUSEMOVE, nFlags, MAKELPARAM(point.x, point.y));
	}
}

if (menuBarRect.PtInRect(point) == TRUE) {
	point.x -= menuBarRect.left;
	point.y -= menuBarRect.top;
	this->menuListForm->SendMessage(WM_MOUSEMOVE, nFlags, MAKELPARAM(point.x, point.y));
}
else if (subMenuRect.PtInRect(point) == TRUE) {
	point.x -= subMenuRect.left;
	point.y -= subMenuRect.top;
	this->subMenuForm->SendMessage(WM_MOUSEMOVE, nFlags, MAKELPARAM(point.x, point.y));
}
else if (cardListRect.PtInRect(point) == TRUE) {
	point.x -= cardListRect.left;
	point.y -= cardListRect.top;
	this->cardListForm->SendMessage(WM_MOUSEMOVE, nFlags, MAKELPARAM(point.x, point.y));
}


// GUID 생성하기.

GUID guid;
HRESULT hr = CoCreateGuid(&guid);

// Convert the GUID to a string
_TUCHAR * guidStr;
UuidToString(&guid, &guidStr);

#endif