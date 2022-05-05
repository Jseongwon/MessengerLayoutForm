// ChatProfileStyle.cpp
/*
���ϸ�Ī : ChatProfileStyle.cpp
��    �� : ��ȭ �̷� �������� ��Ÿ�� Ŭ������ �����.
�� �� �� : ������
�ۼ����� : 2022.04.28
*/
#include "ChatProfileStyle.h"
#include "ProfileForm.h"
#include "ProfileCompiler.h"
#include "ProfileCompileMode.h"
#include "../Generator/DrawingGenerator.h"
using namespace parkcom;

ChatProfileStyle::ChatProfileStyle(CWnd* pCurrentWnd) {
	this->pCurrentWnd = pCurrentWnd;
}

ChatProfileStyle::~ChatProfileStyle() {

}

void ChatProfileStyle::OnDraw(CDC* pDC) {
	CDC memoryDC;

	HBITMAP hBitmap = 0;
	HBITMAP oldBitmap;

	DrawingGenerator drawingGenerator;

	ProfileCompiler profileCompiler;

	LOGFONT logFont;

	LONG i = 0;

	CRect clientRect;
	CRect friendProfileRect;

	((ProfileForm*)this->pCurrentWnd)->GetClientRect(&clientRect);

	memoryDC.CreateCompatibleDC(pDC);
	hBitmap = ::CreateCompatibleBitmap(*pDC, clientRect.right, clientRect.bottom);
	oldBitmap = (HBITMAP)memoryDC.SelectObject(hBitmap);

	memoryDC.FillSolidRect(&clientRect, ((ProfileForm*)this->pCurrentWnd)->backgroundColor);

	ZeroMemory(&logFont, sizeof(LOGFONT));
	strcpy_s(logFont.lfFaceName, "���� ���");

	drawingGenerator = DrawingGenerator(this->pCurrentWnd, &memoryDC, ((ProfileForm*)this->pCurrentWnd)->backgroundColor, ((ProfileForm*)this->pCurrentWnd)->selectedBackgroundColor, ((ProfileForm*)this->pCurrentWnd)->textColor, ((ProfileForm*)this->pCurrentWnd)->selectedTextColor);

	profileCompiler = ProfileCompiler(this->pCurrentWnd, &drawingGenerator);
	profileCompiler.Repair(ProfileCompileMode::CHATPROFILE);
	if (strcmp(((ProfileForm*)this->pCurrentWnd)->baseName, "") != 0) {
		profileCompiler.Compile();
	}

	pDC->BitBlt(0, 0, clientRect.right, clientRect.bottom, &memoryDC, 0, 0, SRCCOPY);

	memoryDC.SelectObject(oldBitmap);
	::DeleteObject(hBitmap);
	memoryDC.DeleteDC();
}