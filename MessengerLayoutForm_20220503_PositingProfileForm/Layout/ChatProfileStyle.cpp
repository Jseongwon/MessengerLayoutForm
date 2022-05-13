// ChatProfileStyle.cpp
/*
파일명칭 : ChatProfileStyle.cpp
기    능 : 대화 이력 윈도우의 스타일 클래스를 만든다.
작 성 자 : 정성원
작성일자 : 2022.04.28
*/
#include "ChatProfileStyle.h"
#include "ProfileForm.h"
#include "ProfileCompiler.h"
#include "ProfileCompileMode.h"
#include "../Profiles/ProfileDirector.h"
#include "../Generator/DrawingGenerator.h"
#include "../Interface/TextEdit.h"
using namespace parkcom;

ChatProfileStyle::ChatProfileStyle(CWnd* pCurrentWnd) {
	this->pCurrentWnd = pCurrentWnd;
	this->textEdit = new TextEdit(this->pCurrentWnd);
	this->textEdit->Repair(EditStyle::CHATEDITSTYLE);

	this->textEdit->Create(NULL, "TextEdit", WS_CHILD,
		CRect(0, 0, 0, 0) , AfxGetMainWnd(), NULL, NULL);
	this->textEdit->ShowWindow(SW_SHOW);
	this->textEdit->UpdateWindow();
}

ChatProfileStyle::~ChatProfileStyle() {
	if (this->textEdit != NULL) {
		this->textEdit->SendMessage(WM_CLOSE);
		this->textEdit = NULL;
	}
}

void ChatProfileStyle::OnSize(UINT nType, int cx, int cy) {
	ProfileDirector profileDirector(this->pCurrentWnd);

	string baseName;

	CRect editAreaRect;
	CRect sendButtonAreaRect;

	LONG systemWidth;
	LONG editExtent;
	LONG sideMargin;
	LONG subMenuWidth;

	baseName = profileDirector.GetBaseName();

	systemWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	editExtent = systemWidth / 22;
	sideMargin = editExtent / 3;

	subMenuWidth = systemWidth / 4;

	editAreaRect.SetRect(sideMargin, cy - (editExtent + sideMargin), (cx - sideMargin) - editExtent, cy - sideMargin);
	editAreaRect.MoveToX(subMenuWidth + (cx / 2 - (cx - sideMargin) / 2));

	sendButtonAreaRect.SetRect(editAreaRect.right, cy - (editExtent + sideMargin),
		cx - sideMargin, cy - sideMargin);

	if(this->textEdit != NULL && baseName != "")
		this->textEdit->SetWindowPos(NULL, editAreaRect.left, editAreaRect.top, editAreaRect.Width(), editAreaRect.Height(), SWP_DRAWFRAME);
}

void ChatProfileStyle::OnDraw(CDC* pDC) {
	CDC memoryDC;

	HBITMAP hBitmap = 0;
	HBITMAP oldBitmap;

	DrawingGenerator drawingGenerator;

	ProfileCompiler profileCompiler;

	LOGFONT logFont;

	CRect clientRect;
	CRect friendProfileRect;
	
	LONG i = 0;

	((ProfileForm*)this->pCurrentWnd)->GetClientRect(&clientRect);

	memoryDC.CreateCompatibleDC(pDC);
	hBitmap = ::CreateCompatibleBitmap(*pDC, clientRect.right, clientRect.bottom);
	oldBitmap = (HBITMAP)memoryDC.SelectObject(hBitmap);

	memoryDC.FillSolidRect(&clientRect, ((ProfileForm*)this->pCurrentWnd)->backgroundColor);

	ZeroMemory(&logFont, sizeof(LOGFONT));
	strcpy_s(logFont.lfFaceName, "맑은 고딕");

	drawingGenerator = DrawingGenerator(this->pCurrentWnd, &memoryDC, ((ProfileForm*)this->pCurrentWnd)->backgroundColor, ((ProfileForm*)this->pCurrentWnd)->selectedBackgroundColor, ((ProfileForm*)this->pCurrentWnd)->textColor, ((ProfileForm*)this->pCurrentWnd)->selectedTextColor);

	profileCompiler = ProfileCompiler(this->pCurrentWnd, &drawingGenerator);
	profileCompiler.Repair(ProfileCompileMode::CHATPROFILE);
	if (strcmp(((ProfileForm*)this->pCurrentWnd)->baseName, "") != 0 && this->onIsDrawing == true) {
		this->onIsDrawing = false;
		profileCompiler.Compile();
	}

	pDC->BitBlt(0, 0, clientRect.right, clientRect.bottom, &memoryDC, 0, 0, SRCCOPY);

	memoryDC.SelectObject(oldBitmap);
	::DeleteObject(hBitmap);
	memoryDC.DeleteDC();

	this->onIsDrawing = true;
}