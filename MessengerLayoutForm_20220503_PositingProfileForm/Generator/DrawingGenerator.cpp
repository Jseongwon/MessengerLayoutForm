// DrawingGenerator.cpp
/*
파일명칭 : DrawingGenerator.cpp
기    능 : 방문자 패턴을 적용한 칠하는 생성기 클래스를 정의한다.
작 성 자 : 정성원
작성일자 : 2022.02.17
*/
#include "DrawingGenerator.h"
#include <afxwin.h>
#include "../Layout/MenuCard.h"
#include "../Layout/SubMenuCard.h"
#include "../Profiles/ProfileDirector.h"
#include "../Profiles/PostingProfile.h"
#include "../Profiles/PostingHeaderProfile.h"
#include "../Profiles/PostingBodyProfile.h"
#include "../Profiles/PostingCommentProfile.h"
#include "../Profiles/NormalKategori.h"
#include "../Profiles/SpecialKategori.h"
#include "../Profiles/PersonalProfile.h"
#include "../Profiles/FriendProfile.h"
#include "../Profiles/ChatProfile.h"
#include "../Profiles/SystemChatProfileState.h"
#include "../Profiles/OneChatProfileState.h"
#include "../Profiles/OtherChatProfileState.h"
#include "../Profiles/Bodys.h"
#include "../Profiles/BodysState.h"
#include "../Utilities/Date.h"
#include "../Utilities/Time.h"
#include "../Utilities/UtilityFunction.h"
#include "../Observers/ItemSubject.h"
#include "../Observers/TextExtent.h"
#include "../Observers/ItemObservers.h"
#include "../Observers/Scrolls.h"
#include <GdiPlus.h>
#pragma comment(lib, "Gdiplus.lib")
#define DEFAULT_HEADER_ROWLENGTH	9
#define DEFAULT_POSTING_ROWLENGTH	7
#define DEFAULT_COMMENT_ROWLENGTH	5
#define DEFAULT_EDITOR_ROWLENGTH	5
#define DEFAULT_CHAT_ROWLENGTH		4
#define DEFAULT_TITLE_POINT			12
#define DEFAULT_CONTENTS_POINT		9
#define DEFAULT_FACENAME "맑은 고딕"
#define SIZE64x64 64
#define IMAGE_RATE 3
#define ITEM_MARGIN 5
#define TEXT_MARGIN 2
using namespace Gdiplus;
using namespace parkcom;

DrawingGenerator::DrawingGenerator() {
	this->onIsFirst = true;
}

DrawingGenerator::DrawingGenerator(CWnd* pCurrentWnd, CDC* pDC, COLORREF backgroundColor, COLORREF selectedBackgroundColor,
	COLORREF textColor, COLORREF selectedTextColor) {
	this->pCurrentWnd = pCurrentWnd;
	this->pDC = pDC;

	this->backgroundColor = backgroundColor;
	this->selectedBackgroundColor = selectedBackgroundColor;
	this->textColor = textColor;
	this->selectedTextColor = selectedTextColor;

	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;

	this->onIsFirst = true;
}

DrawingGenerator::DrawingGenerator(const DrawingGenerator& source) {
	this->pCurrentWnd = source.pCurrentWnd;
	this->pDC = source.pDC;

	this->backgroundColor = source.backgroundColor;
	this->selectedBackgroundColor = source.selectedBackgroundColor;
	this->textColor = source.textColor;
	this->selectedTextColor = source.selectedTextColor;

	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;

	this->onIsFirst = source.onIsFirst;
}

DrawingGenerator::~DrawingGenerator() {

}

DrawingGenerator& DrawingGenerator::operator=(const DrawingGenerator& source) {
	this->pCurrentWnd = source.pCurrentWnd;
	this->pDC = source.pDC;

	this->backgroundColor = source.backgroundColor;
	this->selectedBackgroundColor = source.selectedBackgroundColor;
	this->textColor = source.textColor;
	this->selectedTextColor = source.selectedTextColor;

	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;

	this->onIsFirst = source.onIsFirst;
	return *this;
}

void DrawingGenerator::Visit(MenuCard* menuCard) {
	// 메뉴 카드
	// 메뉴 이미지, 명칭 + 상태에 따른 이미지 그리기. 색상별로 이미지 파일들 만들어 놓고, 상태에 따라 불러오기
	CRect menuCardRect;
	CRect imageRect;
	CRect textRect;

	LONG systemWidth;
	LONG width;

	CDC memoryDC;

	HFONT hFont;
	HFONT oldFont;

	LOGFONT logFont;

	COLORREF backgroundColor;
	COLORREF textColor;
	COLORREF oldColor;
	COLORREF oldTextColor;

	this->pDC->SetStretchBltMode(HALFTONE);
	// 1. 영역을 구한다.
	systemWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	width = systemWidth / 22;

	menuCardRect.SetRect(0, this->y, width, this->y + width);

	imageRect.SetRect(menuCardRect.CenterPoint().x - (SIZE64x64 / 3) / 2, menuCardRect.top + menuCardRect.Height() / 5,
		menuCardRect.CenterPoint().x - (SIZE64x64 / 3) / 2 + SIZE64x64 / 3, menuCardRect.top + menuCardRect.Height() / 5 * 3);
	imageRect.DeflateRect(0, menuCardRect.Height() / 15);

	textRect.SetRect(0, menuCardRect.top + menuCardRect.Height() / 5 * 3, menuCardRect.Width(), menuCardRect.top + menuCardRect.Height() / 5 * 4);

	// 2. 배경을 그린다.
	backgroundColor = this->backgroundColor;
	textColor = this->textColor;

	if (*menuCard->GetCardState() == CardState::HOVER) {
		backgroundColor = this->selectedBackgroundColor;
	}
	if (*menuCard->GetCardState() != CardState::NORMAL) {
		textColor = this->selectedTextColor;
	}

	this->pDC->FillSolidRect(&menuCardRect, backgroundColor);

	// 3. 메뉴카드에서 이미지를 그린다.
	memoryDC.CreateCompatibleDC(this->pDC);

	(HBITMAP)memoryDC.SelectObject(menuCard->GetImage());

	this->pDC->StretchBlt(imageRect.left, imageRect.top, imageRect.Width(), imageRect.Height(), &memoryDC, 0, 0,
		SIZE64x64, SIZE64x64, SRCCOPY);

	// 4. 명칭을 그린다.
	logFont = FindFontInRect(this->pDC, &textRect, "맑은 고딕", 12);

	hFont = CreateFontIndirect(&logFont);
	oldFont = (HFONT)this->pDC->SelectObject(hFont);

	oldColor = this->pDC->SetBkColor(backgroundColor);
	oldTextColor = this->pDC->SetTextColor(textColor);

	this->pDC->DrawText(menuCard->GetName().c_str(), &textRect, DT_CENTER | DT_VCENTER);

	this->pDC->SetTextColor(oldTextColor);
	this->pDC->SetBkColor(oldColor);

	this->pDC->SelectObject(oldFont);
	DeleteObject(hFont);
	
	this->y += menuCardRect.Height();
}

void DrawingGenerator::Visit(SubMenuCard* subMenuCard) {
	CRect subMenuCardRect;
	CRect textRect;
	CRect fontRect;
	CRect filterRect;
	CRect settingRect;
	CRect buttonAreaRect;
	CRect buttonRect;

	Long subMenuCardTopExtent = GetSystemMetrics(SM_CXVIRTUALSCREEN) / 22;
	Long imageMargin;
	Long buttonExtent;
	Long x;
	Long y;
	Long width;
	Long height;

	UINT nFormat = DT_VCENTER | DT_SINGLELINE;

	HFONT hFont;
	HFONT oldFont;

	LOGFONT logFont;

	COLORREF backgroundColor;
	COLORREF textColor;
	COLORREF oldColor;
	COLORREF oldTextColor;

	BITMAP filterBitmap;
	BITMAP settingBitmap;

	CDC memoryDC;

	this->pDC->SetStretchBltMode(HALFTONE);
	// 1. 영역을 구한다.
	this->pCurrentWnd->GetClientRect(&subMenuCardRect);

	// 명칭
	imageMargin = subMenuCardRect.Width() / 16;
	textRect.SetRect(imageMargin, 0, subMenuCardRect.Width() / 2, subMenuCardTopExtent);

	// 필터
	subMenuCard->GetFilterImage().GetBitmap(&filterBitmap);
	x = subMenuCardRect.Width() - ((filterBitmap.bmWidth / IMAGE_RATE) * 2 + imageMargin * 2);
	y = subMenuCardTopExtent / 2 - filterBitmap.bmHeight / IMAGE_RATE / 2;
	width = x + (filterBitmap.bmWidth / IMAGE_RATE);
	height = y + filterBitmap.bmHeight / IMAGE_RATE;

	filterRect.SetRect(x, y, width, height);

	// 설정
	subMenuCard->GetSettingImage().GetBitmap(&settingBitmap);
	x = filterRect.right + imageMargin;
	y = subMenuCardTopExtent / 2 - settingBitmap.bmHeight / IMAGE_RATE / 2;
	width = x + (settingBitmap.bmWidth / IMAGE_RATE);
	height = y + settingBitmap.bmHeight / IMAGE_RATE;

	settingRect.SetRect(x, y, width, height);

	// 버튼
	buttonExtent = subMenuCardTopExtent / 3 * 2;

	buttonAreaRect.SetRect(subMenuCardRect.left + imageMargin, subMenuCardRect.Height() - buttonExtent, subMenuCardRect.right - imageMargin, subMenuCardRect.bottom - imageMargin);

	// 2. 명칭을 그린다.
	fontRect.SetRect(textRect.left, textRect.CenterPoint().y - textRect.Height() / 4, textRect.right, textRect.CenterPoint().y + textRect.Height() / 4);

	logFont = FindFontInRect(this->pDC, &fontRect, "맑은 고딕", 12);

	hFont = CreateFontIndirect(&logFont);
	oldFont = (HFONT)this->pDC->SelectObject(hFont);

	oldColor = this->pDC->SetBkColor(this->backgroundColor);
	oldTextColor = this->pDC->SetTextColor(this->textColor);
	
	this->pDC->DrawText(subMenuCard->GetName().c_str(), &textRect, nFormat);

	this->pDC->SetTextColor(oldTextColor);
	this->pDC->SetBkColor(oldColor);

	this->pDC->SelectObject(oldFont);
	DeleteObject(hFont);

	// 3. 필터 이미지를 그린다.
	memoryDC.CreateCompatibleDC(this->pDC);

	(HBITMAP)memoryDC.SelectObject(subMenuCard->GetFilterImage());

	this->pDC->StretchBlt(filterRect.left, filterRect.top, filterRect.Width(), filterRect.Height(), &memoryDC, 0, 0,
		filterBitmap.bmWidth, filterBitmap.bmHeight, SRCCOPY);

	// 4. 설정 이미지를 그린다.
	(HBITMAP)memoryDC.SelectObject(subMenuCard->GetSettingImage());

	this->pDC->StretchBlt(settingRect.left, settingRect.top, settingRect.Width(), settingRect.Height(), &memoryDC, 0, 0,
		settingBitmap.bmWidth, settingBitmap.bmHeight, SRCCOPY);

	// 5. 전용 버튼을 그린다.
	fontRect.SetRect(buttonAreaRect.left, buttonAreaRect.top + IMAGE_RATE, buttonAreaRect.right, buttonAreaRect.bottom - IMAGE_RATE);

	nFormat = DT_CENTER | DT_SINGLELINE;
	backgroundColor = this->selectedBackgroundColor;
	textColor = this->textColor;
	if (subMenuCard->GetButtonState() == SubMenuCard::ButtonState::HOVER) {
		backgroundColor = RGB(179, 186, 255);
		textColor = this->selectedBackgroundColor;
	}
	else if (subMenuCard->GetButtonState() == SubMenuCard::ButtonState::DOWN) {
		backgroundColor = this->selectedTextColor;
		textColor = this->selectedBackgroundColor;
	}

	logFont = FindFontInRect(this->pDC, &fontRect, "맑은 고딕", 12);

	hFont = CreateFontIndirect(&logFont);
	oldFont = (HFONT)this->pDC->SelectObject(hFont);

	oldColor = this->pDC->SetBkColor(backgroundColor);
	oldTextColor = this->pDC->SetTextColor(textColor);
	this->pDC->FillSolidRect(&buttonAreaRect, backgroundColor);
	this->pDC->DrawText(subMenuCard->GetButtonName().c_str(), &buttonAreaRect, nFormat);

	this->pDC->SetTextColor(oldTextColor);
	this->pDC->SetBkColor(oldColor);

	this->pDC->SelectObject(oldFont);
	DeleteObject(hFont);
}

void DrawingGenerator::Visit(PostingProfile* postingProfile) {
	CRect clientRect;
	CRect profileRect;
	CRect textRect;
	CRect kategoriRect;
	CRect titleRect;
	CRect writerRect;
	CRect writedAtRect;
	CRect viewsRect;
	CRect fontRect;

	CPoint point;
	CPoint downPoint;

	LONG systemWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	LONG topHeight = systemWidth / 22;
	LONG itemHeight;

	string title;
	string writedAt;
	string dateString;
	string printingString;

	LOGFONT logFont;

	HFONT hFont;
	HFONT oldFont;

	COLORREF backgroundColor;
	COLORREF textColor;
	COLORREF oldColor;
	COLORREF oldTextColor;
	COLORREF kategoriBkColor;
	COLORREF kategoriTextColor;
	COLORREF kategoriOldColor;
	COLORREF kategoriOldTextColor;

	Date date;

	GetCursorPos(&point);
	this->pCurrentWnd->ScreenToClient(&point);

	downPoint = CPoint(((ItemSubject*)this->pCurrentWnd)->GetSubjectState()->GetSelectedXPoint(),
		((ItemSubject*)this->pCurrentWnd)->GetSubjectState()->GetSelectedYPoint());
	// ============================================================================================================================================
	// 1. <사용자 이미지 영역들을 구한다>
	this->pCurrentWnd->GetClientRect(&clientRect);

	itemHeight = topHeight / 3;

	profileRect.SetRect(0, this->y, clientRect.Width(), this->y + itemHeight);

	// 1. 카테고리 영역을 구한다.
	textRect.SetRect(ITEM_MARGIN - 3, profileRect.top, profileRect.Width() / 12 + 2, profileRect.bottom);
	kategoriRect = textRect;
	
	// 2. 제목 영역을 구한다.
	textRect.SetRect(textRect.right + ITEM_MARGIN, profileRect.top, textRect.right + profileRect.Width() / 2 - 2, profileRect.bottom);
	titleRect = textRect;
	
	// 3. 작성자 영역을 구한다.
	textRect.SetRect(textRect.right + ITEM_MARGIN, profileRect.top, textRect.right + profileRect.Width() / 6 - 2, profileRect.bottom);
	writerRect = textRect;
	
	// 4. 작성일자 영역을 구한다.
	textRect.SetRect(textRect.right + ITEM_MARGIN, profileRect.top, textRect.right + profileRect.Width() / 6 - 2, profileRect.bottom);
	writedAtRect = textRect;
	
	// 5. 조회수 영역을 구한다.
	textRect.SetRect(textRect.right + ITEM_MARGIN, profileRect.top, textRect.right + profileRect.Width() / 12 - 2, profileRect.bottom);
	viewsRect = textRect;

	// </영역들을 구한다>
	// ============================================================================================================================================

	// ============================================================================================================================================
	// 2. <그릴 준비를 한다>

	fontRect.SetRect(profileRect.left, 0, profileRect.right, profileRect.Height() / 2);

	logFont = FindFontInRect(this->pDC, &fontRect, "맑은 고딕", 12);

	hFont = CreateFontIndirect(&logFont);
	oldFont = (HFONT)this->pDC->SelectObject(hFont);

	backgroundColor = this->backgroundColor;
	textColor = this->textColor;
	if (profileRect.PtInRect(point) == TRUE || profileRect.PtInRect(downPoint) == TRUE) {
		backgroundColor = this->selectedBackgroundColor;
	}

	oldColor = this->pDC->SetBkColor(backgroundColor);
	oldTextColor = this->pDC->SetTextColor(textColor);

	// </그릴 준비를 한다>
	// ============================================================================================================================================

	// ============================================================================================================================================
	// 3. <그린다>
	this->pDC->FillSolidRect(&profileRect, backgroundColor);

	// 1. 카테고리 텍스트를 그린다.
	if (dynamic_cast<NormalKategori*>(postingProfile->GetKategori())) {
		kategoriBkColor = this->backgroundColor;
		kategoriTextColor = this->textColor;

		kategoriOldColor = this->pDC->SetBkColor(kategoriBkColor);
		kategoriOldTextColor = this->pDC->SetTextColor(kategoriTextColor);

		this->pDC->DrawText(postingProfile->GetKategori()->GetName().c_str(), &kategoriRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);

		this->pDC->SetBkColor(kategoriOldColor);
		this->pDC->SetTextColor(kategoriOldTextColor);
	}
	else if (dynamic_cast<SpecialKategori*>(postingProfile->GetKategori())) {
		kategoriBkColor = RGB(103, 116, 255);
		kategoriTextColor = RGB(179, 186, 255);

		kategoriOldColor = this->pDC->SetBkColor(kategoriBkColor);
		kategoriOldTextColor = this->pDC->SetTextColor(kategoriTextColor);

		this->pDC->DrawText(postingProfile->GetKategori()->GetName().c_str(), &kategoriRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);

		this->pDC->SetBkColor(kategoriOldColor);
		this->pDC->SetTextColor(kategoriOldTextColor);
	}

	// 2. 제목 텍스트을 그린다.
	this->pDC->DrawText(postingProfile->GetTitle().c_str(), &titleRect, DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);

	// 3. 작성자 텍스트를 그린다.
	this->pDC->DrawText(postingProfile->GetWriter().c_str(), &writerRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	// 4. 작성일자 텍스트를 그린다.
	writedAt = postingProfile->GetWritedAt();
	dateString = writedAt.substr(0, 8);
	
	date = Date((char*)dateString.c_str());
	printingString = date.GetConvertDateFormatString('.');

	this->pDC->DrawText(printingString.c_str(), &writedAtRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	// 5. 조회수 텍스트를 그린다.
	printingString = (LPCTSTR)IntToString(atoi(postingProfile->GetViews().c_str()), true);
	this->pDC->DrawText(printingString.c_str(), &viewsRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	// </그린다>
	// ============================================================================================================================================

	this->pDC->SetBkColor(oldColor);
	this->pDC->SetTextColor(oldTextColor);

	this->pDC->SelectObject(oldFont);
	DeleteObject(hFont);

	this->y += profileRect.Height();
}

void DrawingGenerator::Visit(PostingHeaderProfile* postingHeaderProfile) {
	CRect clientRect;
	CRect fillRect;
	CRect postingHeaderProfileRect;
	CRect kategoriRect;
	CRect titleRect;
	CRect writerImageRect;
	CRect writerRect;
	CRect writerGradeRect;
	CRect writedDateRect;
	CRect writedTimeRect;
	CRect viewsRect;
	CRect fontRect;

	CDC* pDC;

	LOGFONT titleFont;
	LOGFONT contentsFont;

	HPEN hPen;
	HPEN oldPen;

	HFONT hFont;
	HFONT oldFont;

	TEXTMETRIC metric;

	string titleString;
	string printTitleString;
	string kategoriString;
	string writedAtString;
	string dateString;
	string timeString;
	string printDateString;
	string printTimeString;
	string viewsString;

	Date date;
	Time time;

	Long wrappingCount;
	Long systemWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	Long imageWidth = systemWidth / 22;
	Long sideMargin = imageWidth / 3;
	Long lineMargin = sideMargin / 4;
	Long pageSideMargin = sideMargin * 2;
	Long pointedWidth = sideMargin / 2;
	Long textHeight;
	Long contentsWidth;
	Long x;
	Long y;

	COLORREF backgroundColor;
	COLORREF textColor;
	COLORREF oldColor;
	COLORREF oldTextColor;

	CDC memoryDC;

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	Gdiplus::Bitmap* image;
	Gdiplus::Status imageStatus;

	CBitmap* pBitmap;

	BITMAP bitmap;
	HBITMAP hBitmap = 0;
	HBITMAP oldBitmap;

	string fileName;
	wstring fileName_w;

	CPoint point;
	CPoint downPoint;

	SubjectState* subjectState;
	TextExtent* textExtent;

	GetCursorPos(&point);
	this->pCurrentWnd->ScreenToClient(&point);

	downPoint = CPoint(((ItemSubject*)this->pCurrentWnd)->GetSubjectState()->GetSelectedXPoint(),
		((ItemSubject*)this->pCurrentWnd)->GetSubjectState()->GetSelectedYPoint());

	subjectState = dynamic_cast<ItemSubject*>(this->pCurrentWnd)->GetSubjectState();//
	textExtent = subjectState->textExtent;

	ZeroMemory(&contentsFont, sizeof(LOGFONT));

	pDC = this->pCurrentWnd->GetDC();

	// ============================================================================================================================================
	// <1. 영역들을 구한다.>
	this->pCurrentWnd->GetClientRect(&clientRect);

	titleFont.lfHeight = -MulDiv(DEFAULT_TITLE_POINT, pDC->GetDeviceCaps(LOGPIXELSY), 72);
	strcpy_s(contentsFont.lfFaceName, DEFAULT_FACENAME);

	contentsFont.lfHeight = -MulDiv(DEFAULT_CONTENTS_POINT, pDC->GetDeviceCaps(LOGPIXELSY), 72);
	strcpy_s(contentsFont.lfFaceName, DEFAULT_FACENAME);

	hFont = CreateFontIndirect(&contentsFont);
	oldFont = (HFONT)pDC->SelectObject(hFont);

	pDC->GetTextMetrics(&metric);

	textHeight = metric.tmHeight;

	titleString = postingHeaderProfile->GetTitle();
	textExtent->WrappingContents(titleString, clientRect.Width() - imageWidth / 5 * 4 - pointedWidth * 2 - pageSideMargin * 2, &printTitleString, &wrappingCount);

	fillRect.SetRect(sideMargin, this->y + sideMargin, clientRect.Width() - sideMargin, this->y + pageSideMargin + (DEFAULT_HEADER_ROWLENGTH + wrappingCount) * textHeight);
	postingHeaderProfileRect.SetRect(pageSideMargin, this->y + pageSideMargin, clientRect.Width() - pageSideMargin, this->y + pageSideMargin + (DEFAULT_HEADER_ROWLENGTH + wrappingCount) * textHeight);

	// 1. 카테고리 영역을 구한다.
	kategoriRect.SetRect(postingHeaderProfileRect.left, postingHeaderProfileRect.top + imageWidth / 5,
		postingHeaderProfileRect.left + imageWidth / 5 * 4, postingHeaderProfileRect.top + imageWidth / 5 * 3);

	// 2. 제목 영역을 구한다.
	titleRect.SetRect(kategoriRect.right + pointedWidth, kategoriRect.top,
		postingHeaderProfileRect.right - pointedWidth, kategoriRect.bottom);

	// 3. 작성자 이미지 영역을 구한다.
	writerImageRect.SetRect(kategoriRect.CenterPoint().x - imageWidth / 5 * 2 / 2, kategoriRect.bottom + pointedWidth,
		kategoriRect.CenterPoint().x + imageWidth / 5 * 2 / 2, kategoriRect.bottom + pointedWidth + imageWidth / 5 * 2);

	// 4. 작성자 영역을 구한다.
	contentsWidth = textExtent->GetContentsWidth(postingHeaderProfile->GetWriter());
	writerRect.SetRect(writerImageRect.right + pointedWidth / 2, writerImageRect.top,
		writerImageRect.right + pointedWidth  / 2 + contentsWidth + sideMargin, writerImageRect.top + writerImageRect.Height() / 2);

	// 5. 작성자 등급 영역을 구한다.
	fontRect = writerRect;
	fontRect.DeflateRect(1, 1);

	contentsFont = FindFontInRect(pDC, fontRect, DEFAULT_FACENAME, 9);

	contentsWidth = textExtent->GetContentsWidth(postingHeaderProfile->GetWriterGrade(), contentsFont.lfHeight, contentsFont.lfWidth, contentsFont.lfFaceName);
	writerGradeRect.SetRect(writerRect.right + pointedWidth / 2, writerRect.top,
		writerRect.right + pointedWidth / 2 + contentsWidth + sideMargin, writerRect.bottom);

	// 6. 작성 일자 영역을 구한다.
	writedAtString = postingHeaderProfile->GetWritedAt();

	dateString = writedAtString.substr(0, 8);
	date = Date((char*)dateString.c_str());
	printDateString = date.GetConvertDateFormatString('.');

	contentsWidth = textExtent->GetContentsWidth(printDateString, contentsFont.lfHeight, contentsFont.lfWidth, contentsFont.lfFaceName);
	writedDateRect.SetRect(writerRect.left, writerRect.bottom + pointedWidth / 2,
		writerRect.left + contentsWidth, writerRect.bottom + pointedWidth / 2 + writerRect.Height());

	// 7. 작성 시간 영역을 구한다.
	timeString = writedAtString.substr(8, writedAtString.length() - 8);
	time = Time((char*)timeString.c_str());

	timeString = time.GetConvertTimeKoreanString();
	printTimeString = timeString.substr(5, timeString.length() - 5);

	contentsWidth = textExtent->GetContentsWidth(printTimeString, contentsFont.lfHeight, contentsFont.lfWidth, contentsFont.lfFaceName);
	writedTimeRect.SetRect(writedDateRect.right + pointedWidth / 2, writedDateRect.top,
		writedDateRect.right + pointedWidth / 2 + contentsWidth, writedDateRect.bottom);

	// 8. 조회수 영역을 구한다.
	viewsString = IntToString(atoi(postingHeaderProfile->GetViews().c_str()), TRUE);
	viewsString = "조회 " + viewsString;
	contentsWidth = textExtent->GetContentsWidth(viewsString, contentsFont.lfHeight, contentsFont.lfWidth, contentsFont.lfFaceName);
	viewsRect.SetRect(writedTimeRect.right + pointedWidth / 2, writedTimeRect.top,
		writedTimeRect.right + pointedWidth / 2 + contentsWidth, writedTimeRect.bottom);

	// ============================================================================================================================================

	// ============================================================================================================================================
	// <2. 그릴 준비를 한다.>
	backgroundColor = RGB(255, 255, 255);
	textColor = this->textColor;

	oldColor = this->pDC->SetBkColor(backgroundColor);
	oldTextColor = this->pDC->SetTextColor(textColor);

	// ============================================================================================================================================

	// ============================================================================================================================================
	// <3. 그린다.>
	this->pDC->FillSolidRect(&fillRect, backgroundColor);

	hPen = CreatePen(PS_DEFAULT, 1, this->backgroundColor);
	oldPen = (HPEN)this->pDC->SelectObject(hPen);

	x = postingHeaderProfileRect.left;
	y = postingHeaderProfileRect.bottom;

	this->pDC->MoveTo(x - lineMargin, y);
	this->pDC->LineTo(x - lineMargin, postingHeaderProfileRect.top - lineMargin);
	this->pDC->LineTo(postingHeaderProfileRect.right + lineMargin, postingHeaderProfileRect.top - lineMargin);
	this->pDC->LineTo(postingHeaderProfileRect.right + lineMargin, postingHeaderProfileRect.bottom);

	this->pDC->SelectObject(oldPen);
	DeleteObject(hPen);

	// 1.카테고리 텍스트를 그린다.
	fontRect = kategoriRect;
	fontRect.DeflateRect(1, 1);
	contentsFont = FindFontInRect(pDC, fontRect, DEFAULT_FACENAME, 9);

	hFont = CreateFontIndirect(&contentsFont);
	oldFont = (HFONT)this->pDC->SelectObject(hFont);

	backgroundColor = this->backgroundColor;
	textColor = this->textColor;
	if (dynamic_cast<SpecialKategori*>(postingHeaderProfile->GetKategori())) {
		backgroundColor = RGB(103, 116, 255);
		textColor = RGB(179, 186, 255);
	}

	oldColor = this->pDC->SetBkColor(backgroundColor);
	oldTextColor = this->pDC->SetTextColor(textColor);

	// 1. 카테고리 텍스트를 그린다.
	kategoriString = postingHeaderProfile->GetKategori()->GetName();
	if (kategoriString == "전체공지") {
		kategoriString = "공지";
	}
	this->pDC->DrawText(kategoriString.c_str(), &kategoriRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	this->pDC->SetBkColor(oldColor);
	this->pDC->SetTextColor(oldTextColor);

	this->pDC->SelectObject(oldFont);
	DeleteObject(hFont);

	// 2. 제목 텍스트를 그린다.
	fontRect = titleRect;
	fontRect.DeflateRect(1, 1);
	contentsFont = FindFontInRect(pDC, fontRect, DEFAULT_FACENAME, 9);

	hFont = CreateFontIndirect(&contentsFont);
	oldFont = (HFONT)this->pDC->SelectObject(hFont);
	this->pDC->DrawText(printTitleString.c_str(), &titleRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

	this->pDC->SelectObject(oldFont);
	DeleteObject(hFont);

	// 3. 작성자 이미지를 그린다.
	fileName = postingHeaderProfile->GetAttachmentImageUrl();

	fileName_w.assign(fileName.begin(), fileName.end());

	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	image = Gdiplus::Bitmap::FromFile(fileName_w.c_str());
	imageStatus = image->GetLastStatus();
	if (imageStatus != Gdiplus::Status::Ok) {
		fileName = "Resource\\Images\\DefaultPersonalProfile.png";
		fileName_w.assign(fileName.begin(), fileName.end());
		image = Gdiplus::Bitmap::FromFile(fileName_w.c_str());
	}

	image->GetHBITMAP(Color::White, &hBitmap);

	pBitmap = CBitmap::FromHandle(hBitmap);

	pBitmap->GetBitmap(&bitmap);
	memoryDC.CreateCompatibleDC(this->pDC);

	oldBitmap = (HBITMAP)memoryDC.SelectObject(*pBitmap);

	this->pDC->StretchBlt(writerImageRect.left, writerImageRect.top, writerImageRect.Width(), writerImageRect.Height(), &memoryDC, 0, 0,
		bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

	memoryDC.SelectObject(oldBitmap);
	DeleteObject(hBitmap);

	delete image;
	GdiplusShutdown(gdiplusToken);

	// 4. 작성자 텍스트를 그린다.
	fontRect = writerRect;
	fontRect.DeflateRect(1, 1);
	contentsFont = FindFontInRect(pDC, fontRect, DEFAULT_FACENAME, 9);

	hFont = CreateFontIndirect(&contentsFont);
	oldFont = (HFONT)this->pDC->SelectObject(hFont);
	this->pDC->DrawText(postingHeaderProfile->GetWriter().c_str(), &writerRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	this->pDC->SelectObject(oldFont);
	DeleteObject(hFont);

	// 5. 작성자 등급 텍스트를 그린다.
	fontRect = writerGradeRect;
	fontRect.DeflateRect(1, 1);
	contentsFont = FindFontInRect(pDC, fontRect, DEFAULT_FACENAME, 9);

	hFont = CreateFontIndirect(&contentsFont);
	oldFont = (HFONT)this->pDC->SelectObject(hFont);
	this->pDC->DrawText(postingHeaderProfile->GetWriterGrade().c_str(), &writerGradeRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	this->pDC->SelectObject(oldFont);
	DeleteObject(hFont);

	// 6. 작성 일자 텍스트를 그린다.
	fontRect = writedDateRect;
	fontRect.DeflateRect(1, 1);
	contentsFont = FindFontInRect(pDC, fontRect, DEFAULT_FACENAME, 9);

	hFont = CreateFontIndirect(&contentsFont);
	oldFont = (HFONT)this->pDC->SelectObject(hFont);
	this->pDC->DrawText(printDateString.c_str(), &writedDateRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	this->pDC->SelectObject(oldFont);
	DeleteObject(hFont);

	// 7. 작성 시간 텍스트를 그린다.
	fontRect = writedTimeRect;
	fontRect.DeflateRect(1, 1);
	contentsFont = FindFontInRect(pDC, fontRect, DEFAULT_FACENAME, 9);

	hFont = CreateFontIndirect(&contentsFont);
	oldFont = (HFONT)this->pDC->SelectObject(hFont);
	this->pDC->DrawText(printTimeString.c_str(), &writedTimeRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	this->pDC->SelectObject(oldFont);
	DeleteObject(hFont);

	// 8. 조회수 텍스트를 그린다.
	fontRect = writedTimeRect;
	fontRect.DeflateRect(1, 1);
	contentsFont = FindFontInRect(pDC, fontRect, DEFAULT_FACENAME, 9);
	
	hFont = CreateFontIndirect(&contentsFont);
	oldFont = (HFONT)this->pDC->SelectObject(hFont);
	this->pDC->DrawText(viewsString.c_str(), &viewsRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	this->pDC->SelectObject(oldFont);
	DeleteObject(hFont);

	// ============================================================================================================================================
	this->pCurrentWnd->ReleaseDC(pDC);

	this->pDC->SetBkColor(oldColor);
	this->pDC->SetTextColor(oldTextColor);

	this->pDC->SelectObject(oldFont);
	DeleteObject(hFont);

	this->y += postingHeaderProfileRect.Height();
}

void DrawingGenerator::Visit(PostingBodyProfile* postingBodyProfile) {
	ProfileDirector profileDirector(this->pCurrentWnd);

	CRect clientRect;
	CRect fillRect;
	CRect postingBodyProfileRect;
	
	CDC* pDC;

	LOGFONT contentsFont;

	HPEN hPen;
	HPEN oldPen;

	HFONT hFont;
	HFONT oldFont;

	TEXTMETRIC metric;

	string contents;
	string wrappingContents;

	Long wrappingContentsLength;
	Long systemWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	Long imageWidth = systemWidth / 22;
	Long sideMargin = imageWidth / 3;
	Long pageSideMargin = sideMargin * 2;
	Long pointedWidth = sideMargin / 2;
	Long lineMargin = sideMargin / 4;
	Long textHeight;
	Long x;
	Long y;

	COLORREF backgroundColor;
	COLORREF textColor;
	COLORREF oldColor;
	COLORREF oldTextColor;

	SubjectState* subjectState;
	TextExtent* textExtent;

	subjectState = dynamic_cast<ItemSubject*>(this->pCurrentWnd)->GetSubjectState();//
	textExtent = subjectState->textExtent;

	ZeroMemory(&contentsFont, sizeof(LOGFONT));

	pDC = this->pCurrentWnd->GetDC();

	// ============================================================================================================================================
	// <1. 영역들을 구한다.>
	this->pCurrentWnd->GetClientRect(&clientRect);

	contentsFont.lfHeight = -MulDiv(DEFAULT_CONTENTS_POINT, pDC->GetDeviceCaps(LOGPIXELSY), 72);
	strcpy_s(contentsFont.lfFaceName, DEFAULT_FACENAME);

	hFont = CreateFontIndirect(&contentsFont);
	oldFont = (HFONT)pDC->SelectObject(hFont);

	pDC->GetTextMetrics(&metric);

	this->pCurrentWnd->ReleaseDC(pDC);

	textHeight = metric.tmHeight;

	contents = postingBodyProfile->GetContents();
	textExtent->WrappingContents(contents, clientRect.Width() - pageSideMargin * 2, &wrappingContents, &wrappingContentsLength);

	fillRect.SetRect(sideMargin, this->y,
		clientRect.Width() - sideMargin, this->y + (DEFAULT_POSTING_ROWLENGTH + wrappingContentsLength + 1) * textHeight);

	postingBodyProfileRect.SetRect(pageSideMargin, this->y,
		clientRect.Width() - pageSideMargin, this->y + (DEFAULT_POSTING_ROWLENGTH + wrappingContentsLength + 1) * textHeight);

	// ============================================================================================================================================

	// ============================================================================================================================================
	// <2. 그릴 준비를 한다.>
	hFont = CreateFontIndirect(&contentsFont);
	oldFont = (HFONT)this->pDC->SelectObject(hFont);

	backgroundColor = RGB(255, 255, 255);
	textColor = this->textColor;

	oldColor = this->pDC->SetBkColor(backgroundColor);
	oldTextColor = this->pDC->SetTextColor(textColor);

	// ============================================================================================================================================

	// ============================================================================================================================================
	// <3. 그린다.>
	this->pDC->FillSolidRect(&fillRect, backgroundColor);

	hPen = CreatePen(PS_DEFAULT, 1, this->backgroundColor);
	oldPen = (HPEN)this->pDC->SelectObject(hPen);

	x = postingBodyProfileRect.left;
	y = postingBodyProfileRect.bottom;

	this->pDC->MoveTo(x - lineMargin, y);
	this->pDC->LineTo(x - lineMargin, postingBodyProfileRect.top - lineMargin);
	this->pDC->LineTo(postingBodyProfileRect.right + lineMargin, postingBodyProfileRect.top - lineMargin);
	this->pDC->LineTo(postingBodyProfileRect.right + lineMargin, postingBodyProfileRect.bottom);

	this->pDC->SelectObject(oldPen);
	DeleteObject(hPen);

	this->pDC->DrawText(contents.c_str(), &postingBodyProfileRect, DT_EDITCONTROL | DT_WORDBREAK);

	// ============================================================================================================================================

	this->pDC->SetBkColor(oldColor);
	this->pDC->SetTextColor(oldTextColor);

	this->pDC->SelectObject(oldFont);
	DeleteObject(hFont);

	this->y += postingBodyProfileRect.Height();
}

void DrawingGenerator::Visit(PostingCommentProfile* postingCommentProfile) {
	ProfileDirector profileDirector(this->pCurrentWnd);

	CRect clientRect;
	CRect fillRect;
	CRect postingCommentProfileRect;
	CRect writerImageRect;
	CRect writerRect;
	CRect commentRect;
	CRect writedDateRect;
	CRect writedTimeRect;

	CDC* pDC;
	CDC memoryDC;

	LOGFONT contentsFont;

	HPEN hPen;
	HPEN oldPen;

	HFONT hFont;
	HFONT oldFont;

	TEXTMETRIC metric;

	wstring fileName_w;
	string fileName;
	string contents;
	string commentWrappingContents;
	string writedAtString;
	string dateString;
	string timeString;
	string printDateString;
	string printTimeString;

	Long contentsWidth;
	Long wrappingContentsLength;
	Long commentWrappingContentsLength;
	Long systemWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	Long imageWidth = systemWidth / 22;
	Long sideMargin = imageWidth / 3;
	Long pageSideMargin = sideMargin * 2;
	Long pointedWidth = sideMargin / 2;
	Long lineMargin = sideMargin / 4;
	Long textHeight;
	Long x;
	Long y;

	Date date;
	Time time;

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	Gdiplus::Bitmap* image;
	Gdiplus::Status imageStatus;

	CBitmap* pBitmap;

	BITMAP bitmap;
	HBITMAP hBitmap = 0;
	HBITMAP oldBitmap;

	COLORREF backgroundColor;
	COLORREF textColor;
	COLORREF oldColor;
	COLORREF oldTextColor;

	SubjectState* subjectState;
	TextExtent* textExtent;

	subjectState = dynamic_cast<ItemSubject*>(this->pCurrentWnd)->GetSubjectState();//
	textExtent = subjectState->textExtent;

	ZeroMemory(&contentsFont, sizeof(LOGFONT));

	pDC = this->pCurrentWnd->GetDC();

	// ============================================================================================================================================
	// <1. 영역들을 구한다.>
	this->pCurrentWnd->GetClientRect(&clientRect);

	contentsFont.lfHeight = -MulDiv(DEFAULT_CONTENTS_POINT, pDC->GetDeviceCaps(LOGPIXELSY), 72);
	strcpy_s(contentsFont.lfFaceName, DEFAULT_FACENAME);

	hFont = CreateFontIndirect(&contentsFont);
	oldFont = (HFONT)pDC->SelectObject(hFont);

	pDC->GetTextMetrics(&metric);

	this->pCurrentWnd->ReleaseDC(pDC);

	textHeight = metric.tmHeight;

	wrappingContentsLength = profileDirector.GetProfileLength();
	contents = postingCommentProfile->GetComment();
	textExtent->WrappingContents(contents, clientRect.Width() - pageSideMargin * 2, &commentWrappingContents, &commentWrappingContentsLength);

	fillRect.SetRect(sideMargin, this->y,
		clientRect.Width() - sideMargin, this->y + (DEFAULT_COMMENT_ROWLENGTH + commentWrappingContentsLength + 1) * textHeight);

	postingCommentProfileRect.SetRect(pageSideMargin, this->y,
		clientRect.Width() - pageSideMargin, this->y + (DEFAULT_COMMENT_ROWLENGTH + commentWrappingContentsLength + 1) * textHeight);

	// 1. 작성자 이미지 영역을 구한다.
	writerImageRect.SetRect(postingCommentProfileRect.left + pointedWidth, postingCommentProfileRect.top + pointedWidth,
		postingCommentProfileRect.left + pointedWidth + imageWidth / 5 * 2, postingCommentProfileRect.top + pointedWidth + imageWidth / 5 * 2);

	// 2. 작성자 영역을 구한다.
	writerRect.SetRect(writerImageRect.right + pointedWidth, writerImageRect.top,
		postingCommentProfileRect.right, writerImageRect.top + textHeight + textHeight / 2);

	// 3. 댓글 내용 영역을 구한다.
	commentRect.SetRect(writerRect.left, writerRect.bottom + ITEM_MARGIN,
		writerRect.right, writerRect.bottom + textHeight / 2 + (commentWrappingContentsLength + 1) * textHeight + textHeight / 2);

	// 4. 작성시간 영역을 구한다.
	writedAtString = postingCommentProfile->GetWritedAt();

	// 5. 일자 영역을 구한다.
	// + 일자 문자열을 구한다.
	dateString = writedAtString.substr(0, 8);
	date = Date((char*)dateString.c_str());

	// + 출력할 일자 문자열을 구한다.
	printDateString = date.GetConvertDateFormatString('.');

	// + 시간 문자열을 구한다.
	timeString = writedAtString.substr(8, writedAtString.length() - 8);
	time = Time((char*)timeString.c_str());

	// + 출력할 시간 문자열을 구한다.
	timeString = time.GetConvertTimeKoreanString();
	printTimeString = timeString.substr(5, timeString.length() - 5);

	// + 출력할 일자 문자열로 출력 일자 영역을 구한다.
	contentsWidth = textExtent->GetContentsWidth(printDateString, contentsFont.lfHeight, contentsFont.lfWidth, contentsFont.lfFaceName);
	writedDateRect.SetRect(commentRect.left, commentRect.bottom + ITEM_MARGIN,
		commentRect.left + contentsWidth + ITEM_MARGIN, commentRect.bottom + ITEM_MARGIN + textHeight);

	// + 출력할 시간 문자열로 출력 시간 영역을 구한다.
	contentsWidth = textExtent->GetContentsWidth(printTimeString, contentsFont.lfHeight, contentsFont.lfWidth, contentsFont.lfFaceName);
	writedTimeRect.SetRect(writedDateRect.right, writedDateRect.top,
		writedDateRect.right + contentsWidth + ITEM_MARGIN, writedDateRect.bottom);

	// ============================================================================================================================================

	// ============================================================================================================================================
	// <2. 그릴 준비를 한다.>
	hFont = CreateFontIndirect(&contentsFont);
	oldFont = (HFONT)this->pDC->SelectObject(hFont);

	backgroundColor = RGB(255, 255, 255);
	textColor = this->textColor;

	oldColor = this->pDC->SetBkColor(backgroundColor);
	oldTextColor = this->pDC->SetTextColor(textColor);

	// ============================================================================================================================================

	// ============================================================================================================================================
	// <3. 그린다.>
	this->pDC->FillSolidRect(&fillRect, backgroundColor);

	hPen = CreatePen(PS_DEFAULT, 1, this->backgroundColor);
	oldPen = (HPEN)this->pDC->SelectObject(hPen);

	x = postingCommentProfileRect.left;
	y = postingCommentProfileRect.bottom;

	this->pDC->MoveTo(x - lineMargin, y);
	this->pDC->LineTo(x - lineMargin, postingCommentProfileRect.top - lineMargin);
	if (this->onIsFirst == true) {
		this->pDC->LineTo(postingCommentProfileRect.right + lineMargin, postingCommentProfileRect.top - lineMargin);

		this->onIsFirst = false;
	}
	else {
		this->pDC->MoveTo(postingCommentProfileRect.right + lineMargin, postingCommentProfileRect.top - lineMargin);
	}
	this->pDC->LineTo(postingCommentProfileRect.right + lineMargin, postingCommentProfileRect.bottom);

	this->pDC->SelectObject(oldPen);
	DeleteObject(hPen);

	// 1. 작성자 이미지를 그린다.
	fileName = postingCommentProfile->GetAttachmentImageUrl();

	fileName_w.assign(fileName.begin(), fileName.end());

	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	image = Gdiplus::Bitmap::FromFile(fileName_w.c_str());
	imageStatus = image->GetLastStatus();
	if (imageStatus != Gdiplus::Status::Ok) {
		fileName = "Resource\\Images\\DefaultPersonalProfile.png";
		fileName_w.assign(fileName.begin(), fileName.end());
		image = Gdiplus::Bitmap::FromFile(fileName_w.c_str());
	}

	image->GetHBITMAP(Color::White, &hBitmap);

	pBitmap = CBitmap::FromHandle(hBitmap);

	pBitmap->GetBitmap(&bitmap);
	memoryDC.CreateCompatibleDC(this->pDC);

	oldBitmap = (HBITMAP)memoryDC.SelectObject(*pBitmap);

	this->pDC->StretchBlt(writerImageRect.left, writerImageRect.top, writerImageRect.Width(), writerImageRect.Height(), &memoryDC, 0, 0,
		bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

	memoryDC.SelectObject(oldBitmap);
	DeleteObject(hBitmap);

	delete image;
	GdiplusShutdown(gdiplusToken);

	// 2. 작성자 텍스트를 그린다.
	this->pDC->DrawText(postingCommentProfile->GetWriter().c_str(), &writerRect, DT_LEFT | DT_VCENTER);

	// 3. 댓글 내용 텍스트를 그린다.
	this->pDC->DrawText(commentWrappingContents.c_str(), &commentRect, DT_LEFT);

	// 4. 작성 일자 텍스트를 그린다.
	this->pDC->DrawText(printDateString.c_str(), &writedDateRect, DT_CENTER | DT_VCENTER);

	// 5. 작성 시간 텍스트를 그린다.
	this->pDC->DrawText(printTimeString.c_str(), &writedTimeRect, DT_CENTER | DT_VCENTER);

	// ============================================================================================================================================

	this->pDC->SetBkColor(oldColor);
	this->pDC->SetTextColor(oldTextColor);

	this->pDC->SelectObject(oldFont);
	DeleteObject(hFont);

	this->y += postingCommentProfileRect.Height();
}

void DrawingGenerator::Visit(PersonalProfile* personalProfile) {
	CRect profileRect;
	CRect frontRect;
	CRect rearRect;
	CRect imageRect;

	// 사용자 이미지, 상태, 별명, 상태 메시지, 추가옵션
	// ============================================================================================================================================
	// 1. <영역을 구한다>
	CRect clientRect;
	CRect accountImageRect;
	CRect stateRect;
	CRect nicknameRect;
	CRect stateMessageRect;
	CRect additionalOptionRect;
	CRect fontRect;
	CRect itemRect;

	LONG systemWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	LONG topHeight = systemWidth / 22;
	LONG scrollCurrent = 0;
	LONG margin;
	LONG one_third;
	LONG quarter;

	CDC memoryDC;

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	Gdiplus::Bitmap* image;
	Gdiplus::Status imageStatus;

	CBitmap* pBitmap;

	BITMAP bitmap;
	HBITMAP hBitmap = 0;
	HBITMAP oldBitmap;

	string fileName;
	wstring fileName_w;

	HBRUSH hBrush;
	HBRUSH oldBrush;

	HFONT hFont;
	HFONT oldFont;

	LOGFONT logFont;

	COLORREF backgroundColor;
	COLORREF textColor;
	COLORREF oldColor;
	COLORREF oldTextColor;

	CPoint point;

	GetCursorPos(&point);
	this->pCurrentWnd->ScreenToClient(&point);
	this->pDC->SetStretchBltMode(HALFTONE);
	// ============================================================================================================================================
	// 1. <사용자 이미지 영역들을 구한다>
	this->pCurrentWnd->GetClientRect(&clientRect);

	profileRect.SetRect(0, this->y, clientRect.Width(), this->y + topHeight);

	// 1. 화면 범위를 구한다.
	frontRect = profileRect;
	frontRect.right = frontRect.Height();

	rearRect = profileRect;
	rearRect.MoveToXY(frontRect.right, frontRect.top);
	rearRect.right = profileRect.right;

	// 2. 사용자 이미지 x = 전체너비 / 2 - 전체너비 / 4, y = 전체높이 / 5, width = 전체너비 / 2, height = 전체높이 / 5 * 2
	accountImageRect.SetRect(frontRect.left + frontRect.Width() / 2 - frontRect.Width() / 4, frontRect.top + frontRect.Height() / 5,
		frontRect.left + frontRect.Width() / 2 + frontRect.Width() / 4, frontRect.top + frontRect.Height() / 5 * 3);

	// 3. 상태 영역을 설정한다.
	stateRect.SetRect(accountImageRect.left + accountImageRect.Width() - accountImageRect.Width() / 2,
		accountImageRect.top + accountImageRect.Height() - accountImageRect.Height() / 2, accountImageRect.right, accountImageRect.bottom);

	// 4. 별명 영역을 설정한다.
	nicknameRect.SetRect(frontRect.left, frontRect.top + frontRect.Height() / 5 * 3,
		frontRect.left + frontRect.Width(), frontRect.top + frontRect.Height() / 5 * 4);

	// 5. 상태 메시지 영역을 설정한다.
	margin = rearRect.Height() / 8;

	stateMessageRect = rearRect;
	stateMessageRect.right -= margin * 2;
	
	// 6. 추가 옵션 영역을 설정한다.
	rearRect.DeflateRect(margin, margin);

	imageRect.SetRect(0, 0, profileRect.Height(), profileRect.Height());

	additionalOptionRect.SetRect(rearRect.right - imageRect.Width(), profileRect.top + profileRect.Height() / 2 - imageRect.Height() / 2,
		rearRect.right, profileRect.top + profileRect.Height() / 2 - imageRect.Height() / 2 + imageRect.Height());
	additionalOptionRect.DeflateRect(imageRect.Width() / 5 * 3 / 2, imageRect.Height() / 5 * 3 / 2);
	// </영역들을 구한다>
	// ============================================================================================================================================

	// ============================================================================================================================================
	// 2. <그릴 준비를 한다>
	backgroundColor = this->backgroundColor;
	textColor = this->textColor;
	if (profileRect.PtInRect(point) == TRUE) {
		stateMessageRect.right = additionalOptionRect.left;

		backgroundColor = this->selectedBackgroundColor;
	}

	oldColor = this->pDC->SetBkColor(backgroundColor);
	oldTextColor = this->pDC->SetTextColor(textColor);
	// </그릴 준비를 한다>
	// ============================================================================================================================================
	
	// ============================================================================================================================================
	// 3. <그린다>
	this->pDC->FillSolidRect(&profileRect, backgroundColor);
	// 1. 사용자 이미지를 그린다.
	fileName = personalProfile->GetAttachmentImageUrl();

	fileName_w.assign(fileName.begin(), fileName.end());

	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	image = Gdiplus::Bitmap::FromFile(fileName_w.c_str());
	imageStatus = image->GetLastStatus();
	if (imageStatus != Gdiplus::Status::Ok) {
		fileName = "Resource\\Images\\DefaultPersonalProfile.png";
		fileName_w.assign(fileName.begin(), fileName.end());
		image = Gdiplus::Bitmap::FromFile(fileName_w.c_str());
	}

	image->GetHBITMAP(Color::White, &hBitmap);

	pBitmap = CBitmap::FromHandle(hBitmap);

	pBitmap->GetBitmap(&bitmap);
	memoryDC.CreateCompatibleDC(this->pDC);

	oldBitmap = (HBITMAP)memoryDC.SelectObject(*pBitmap);

	this->pDC->StretchBlt(accountImageRect.left, accountImageRect.top, accountImageRect.Width(), accountImageRect.Height(), &memoryDC, 0, 0,
		bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

	memoryDC.SelectObject(oldBitmap);
	DeleteObject(hBitmap);

	delete image;
	GdiplusShutdown(gdiplusToken);

	// 2. 상태 도형을 그린다.
	hBrush = CreateSolidBrush(RGB(127, 127, 127));
	oldBrush = (HBRUSH)this->pDC->SelectObject(hBrush);

	this->pDC->Ellipse(stateRect);

	this->pDC->SelectObject(oldBrush);
	DeleteObject(hBrush);

	// 3. 별명 텍스트를 그린다.
	fontRect.SetRect(nicknameRect.left, nicknameRect.top, nicknameRect.right, nicknameRect.bottom);

	logFont = FindFontInRect(this->pDC, &fontRect, "맑은 고딕", 12);

	hFont = CreateFontIndirect(&logFont);
	oldFont = (HFONT)this->pDC->SelectObject(hFont);

	this->pDC->DrawText(personalProfile->GetNickname().c_str(), &nicknameRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	this->pDC->SelectObject(oldFont);
	DeleteObject(hFont);

	// 4. 상태 메시지 텍스트를 그린다.
	fontRect.SetRect(stateMessageRect.left, 0, stateMessageRect.right, stateMessageRect.Height() / 2);

	logFont = FindFontInRect(this->pDC, &fontRect, "맑은 고딕", 12);

	hFont = CreateFontIndirect(&logFont);
	oldFont = (HFONT)this->pDC->SelectObject(hFont);

	this->pDC->DrawText(personalProfile->GetStateMessage().c_str(), &stateMessageRect, DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);

	this->pDC->SelectObject(oldFont);
	DeleteObject(hFont);

	// 5. 추가옵션 도형을 그린다.
	if (profileRect.PtInRect(point) == TRUE) {
		hBrush = CreateSolidBrush(RGB(0, 0, 0));
		oldBrush = (HBRUSH)this->pDC->SelectObject(hBrush);

		// Horizontal Additional Option
		one_third = additionalOptionRect.Width() / 3;
		quarter = additionalOptionRect.Width() / 4;

		itemRect.SetRect(additionalOptionRect.left, additionalOptionRect.CenterPoint().y - quarter / 2, additionalOptionRect.left + quarter, additionalOptionRect.CenterPoint().y + quarter / 2);
		this->pDC->Ellipse(&itemRect);

		itemRect.SetRect(additionalOptionRect.CenterPoint().x - quarter / 2, itemRect.top, additionalOptionRect.CenterPoint().x - quarter / 2 + quarter, itemRect.bottom);
		this->pDC->Ellipse(&itemRect);

		itemRect.SetRect(additionalOptionRect.right - quarter, itemRect.top, additionalOptionRect.right, itemRect.bottom);
		this->pDC->Ellipse(&itemRect);

		this->pDC->SelectObject(oldBrush);
		DeleteObject(hBrush);

		this->pDC->SetTextColor(oldTextColor);
		this->pDC->SetBkColor(oldColor);
	}
	// </그린다>
	// ============================================================================================================================================

	this->y += profileRect.Height();
}

void DrawingGenerator::Visit(FriendProfile* friendProfile) {
	CRect clientRect;
	CRect profileRect;
	CRect profileAreaRect;
	CRect stateMessageAreaRect;

	CRect friendImageRect;
	CRect stateRect;
	CRect nicknameRect;
	CRect stateMessageRect;
	CRect lastChatDateRect;
	CRect lastChatContentsRect;
	CRect additionalOptionRect;
	CRect itemRect;
	CRect imageRect;
	CRect fontRect;
	CRect unReadRect;

	LONG systemWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	LONG topHeight = systemWidth / 22;
	LONG scrollCurrent = 0;
	LONG margin;
	LONG unReadCountLeft;
	LONG unReadCountWidth;
	LONG unReadCountHeight;
	LONG one_third;
	LONG quarter;

	CDC memoryDC;

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	Gdiplus::Bitmap* image;
	Gdiplus::Status imageStatus;

	CBitmap* pBitmap;

	BITMAP bitmap;
	HBITMAP hBitmap = 0;
	HBITMAP oldBitmap;

	Date today;

	string unReadString;
	string formattingDateTime;
	string itString;
	string printingString;
	string todayString;
	string yesterdayString;
	string fileName;
	wstring fileName_w;

	HPEN hPen;
	HPEN oldPen;

	HBRUSH hBrush;
	HBRUSH oldBrush;

	HFONT hFont;
	HFONT oldFont;

	LOGFONT logFont;

	COLORREF backgroundColor;
	COLORREF textColor;
	COLORREF oldColor;
	COLORREF oldTextColor;

	CPoint point;
	CPoint downPoint;

	GetCursorPos(&point);
	this->pCurrentWnd->ScreenToClient(&point);
	// ============================================================================================================================================
	// 1. <친구 사용자의 영역들을 구한다.>
	/*1. 사용자 이미지, 2. 상태, 3. 별명, 4. 상태 메시지, 5. 마지막 대화 일자, 6. 마지막 대화 내용, 7. 추가 옵션*/
	// 1. 화면 범위를 구한다.
	this->pCurrentWnd->GetClientRect(&clientRect);

	profileRect.SetRect(0, this->y, clientRect.Width(), this->y + (topHeight / 8 * 7));

	profileAreaRect = profileRect;
	profileAreaRect.right = profileAreaRect.Height();

	stateMessageAreaRect = profileRect;
	stateMessageAreaRect.left = profileAreaRect.right;

	margin = stateMessageAreaRect.Height() / 8;

	// 2. 친구 사용자 이미지 영역을 구한다.
	// 사용자 이미지 x = 전체너비 / 2 - 전체너비 / 4, y = 전체높이 / 5, width = 전체너비 / 2, height = 전체높이 / 5 * 2
	itemRect.SetRect(profileAreaRect.Width() / 2 - profileAreaRect.Width() / 4, profileRect.top + profileAreaRect.Height() / 5,
		profileAreaRect.Width() / 2 + profileAreaRect.Width() / 4, profileRect.top + profileAreaRect.Height() / 5 * 3);

	friendImageRect = itemRect;

	// 3. 상태 영역을 구한다.
	itemRect.SetRect(itemRect.left + itemRect.Width() - itemRect.Width() / 2, itemRect.top + itemRect.Height() - itemRect.Height() / 2,
		itemRect.right, itemRect.bottom);

	stateRect = itemRect;

	// 4. 별명 영역을 구한다.
	itemRect.SetRect(0, profileAreaRect.top + profileAreaRect.Height() / 5 * 3, profileAreaRect.Width(), profileAreaRect.top + profileAreaRect.Height() / 5 * 4);

	nicknameRect = itemRect;

	// 5. 상태 메세지 영역을 구한다.
	itemRect = stateMessageAreaRect;
	itemRect.right = stateMessageAreaRect.left + stateMessageAreaRect.Width() / 4 * 3 - margin;
	itemRect.bottom = stateMessageAreaRect.top + stateMessageAreaRect.Height() / 2;

	stateMessageRect = itemRect;
	
	// 6. 마지막 대화 일자 영역을 구한다.
	itemRect.SetRect(itemRect.right, itemRect.top, stateMessageAreaRect.right - margin * 2, itemRect.bottom - margin / 2);

	lastChatDateRect = itemRect;

	// 7. 마지막 대화 내용 영역을 구한다.
	unReadCountWidth = margin * 3;
	unReadCountHeight = stateMessageAreaRect.bottom - (lastChatDateRect.bottom + margin);
	unReadCountHeight = unReadCountHeight - unReadCountHeight / 4;

	unReadString = friendProfile->GetUnreadCount();
	if (unReadString.length() <= 1) {
		unReadCountLeft = stateMessageAreaRect.right - margin - unReadCountHeight;
	}
	else if (unReadString.length() <= 2) {
		unReadCountLeft = stateMessageAreaRect.right - margin - unReadCountWidth;
	}
	else if (unReadString.length() <= 3) {
		unReadCountLeft = stateMessageAreaRect.right - margin - unReadCountWidth - unReadCountWidth / 2;
	}
	else if (unReadString.length() >= 4) {
		unReadCountLeft = stateMessageAreaRect.right - margin - unReadCountWidth * 2;
		unReadString = "999+";
	}

	itemRect.SetRect(stateMessageAreaRect.left, lastChatDateRect.bottom + margin, unReadCountLeft, stateMessageAreaRect.bottom);
	
	lastChatContentsRect = itemRect;

	// 8. 읽지 않은 개수 영역을 구한다.
	itemRect.SetRect(itemRect.right, itemRect.top, stateMessageAreaRect.right - margin, itemRect.bottom);
	itemRect.DeflateRect(0, itemRect.Height() / 8);

	unReadRect = itemRect;

	// 9. 추가 옵션 영역을 구한다.
	stateMessageAreaRect.DeflateRect(margin, margin);

	imageRect.SetRect(0, 0, profileRect.Height(), profileRect.Height());

	itemRect.SetRect(stateMessageAreaRect.right - imageRect.Width(), profileRect.top + profileRect.Height() / 2 - imageRect.Height() / 2,
		stateMessageAreaRect.right, profileRect.top + profileRect.Height() / 2 - imageRect.Height() / 2 + imageRect.Height());
	itemRect.DeflateRect(imageRect.Width() / 5 * 3 / 2, imageRect.Height() / 5 * 3 / 2);

	additionalOptionRect = itemRect;
	// </친구 사용자의 영역들을 구한다.>
	// ============================================================================================================================================

	// ============================================================================================================================================
	// 2. <그릴 준비를 한다.>
	downPoint = CPoint(((ItemSubject*)this->pCurrentWnd)->GetSubjectState()->GetSelectedXPoint(),
		((ItemSubject*)this->pCurrentWnd)->GetSubjectState()->GetSelectedYPoint());

	backgroundColor = this->backgroundColor;
	textColor = this->textColor;
	if (profileRect.PtInRect(point) == TRUE || profileRect.PtInRect(downPoint) == TRUE) {
		stateMessageRect.right = additionalOptionRect.left;
		lastChatContentsRect.right = additionalOptionRect.left;

		backgroundColor = this->selectedBackgroundColor;
	}

	oldColor = this->pDC->SetBkColor(backgroundColor);
	oldTextColor = this->pDC->SetTextColor(textColor);

	// </그릴 준비를 한다.>
	// ============================================================================================================================================

	// ============================================================================================================================================
	// 3. <그린다.>
	this->pDC->FillSolidRect(&profileRect, backgroundColor);
	// 1. 친구 사용자 이미지를 그린다.
	fileName = friendProfile->GetAttachmentImageUrl();

	fileName_w.assign(fileName.begin(), fileName.end());

	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	image = Gdiplus::Bitmap::FromFile(fileName_w.c_str());
	imageStatus = image->GetLastStatus();
	if (imageStatus != Gdiplus::Status::Ok) {
		fileName = "Resource\\Images\\DefaultPersonalProfile.png";
		fileName_w.assign(fileName.begin(), fileName.end());
		image = Gdiplus::Bitmap::FromFile(fileName_w.c_str());
	}

	image->GetHBITMAP(Color::White, &hBitmap);

	pBitmap = CBitmap::FromHandle(hBitmap);

	pBitmap->GetBitmap(&bitmap);
	memoryDC.CreateCompatibleDC(this->pDC);

	oldBitmap = (HBITMAP)memoryDC.SelectObject(*pBitmap);

	this->pDC->StretchBlt(friendImageRect.left, friendImageRect.top, friendImageRect.Width(), friendImageRect.Height(), &memoryDC, 0, 0,
		bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

	memoryDC.SelectObject(oldBitmap);
	DeleteObject(hBitmap);

	delete image;
	GdiplusShutdown(gdiplusToken);

	// 2. 상태 도형을 그린다.
	hBrush = CreateSolidBrush(RGB(127, 127, 127));
	oldBrush = (HBRUSH)this->pDC->SelectObject(hBrush);

	this->pDC->Ellipse(stateRect);

	this->pDC->SelectObject(oldBrush);
	DeleteObject(hBrush);

	// 3. 별명 텍스트를 그린다.
	fontRect.SetRect(nicknameRect.left, nicknameRect.top, nicknameRect.right, nicknameRect.bottom);

	logFont = FindFontInRect(this->pDC, &fontRect, "맑은 고딕", 12);

	hFont = CreateFontIndirect(&logFont);
	oldFont = (HFONT)this->pDC->SelectObject(hFont);

	this->pDC->DrawText(friendProfile->GetNickname().c_str(), &nicknameRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	this->pDC->SelectObject(oldFont);
	DeleteObject(hFont);

	// 4. 상태 메시지 텍스트를 그린다.
	fontRect.SetRect(stateMessageRect.left, 0, stateMessageRect.right, stateMessageRect.Height() / 2);

	logFont = FindFontInRect(this->pDC, &fontRect, "맑은 고딕", 12);

	hFont = CreateFontIndirect(&logFont);
	oldFont = (HFONT)this->pDC->SelectObject(hFont);

	this->pDC->DrawText(friendProfile->GetStateMessage().c_str(), &stateMessageRect, DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);

	this->pDC->SelectObject(oldFont);
	DeleteObject(hFont);

	// 5. 마지막 대화 일자 텍스트를 그린다.
	if (profileRect.PtInRect(point) != TRUE) {
		fontRect.SetRect(lastChatDateRect.left, 0, lastChatDateRect.right, lastChatDateRect.Height() / 2);

		logFont = FindFontInRect(this->pDC, &fontRect, "맑은 고딕", 12);

		hFont = CreateFontIndirect(&logFont);
		oldFont = (HFONT)this->pDC->SelectObject(hFont);

		// 1. 일자를 읽는다.
		formattingDateTime = friendProfile->GetLastUpdateAt();
		itString = formattingDateTime.substr(0, 8);

		// 2. 오늘 일자를 읽는다.
		today = Date::Today();
		todayString = (char*)today;
		yesterdayString = (char*)today.Yesterday();

		// 3. 일자가 같으면 시간으로 출력 문자열을 만든다.
		if (itString == todayString) {
			itString = Time((char*)formattingDateTime.substr(8, formattingDateTime.length() - 8).c_str()).GetConvertTimeKoreanString();
			printingString = itString;
		}
		// 4. 일자가 하루 전이면 "어제"로 출력 문자열을 만든다.
		else if (itString == yesterdayString) {
			printingString = "어제";
		}
		// 5. 아니면 년-월-일로 출력 문자열을 만든다.
		else {
			printingString = Date((char*)itString.c_str()).GetConvertDateFormatString('-');
		}

		this->pDC->DrawText(printingString.c_str(), &lastChatDateRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);

		this->pDC->SelectObject(oldFont);
		DeleteObject(hFont);
	}
	// 6. 마지막 대화 내용 텍스트를 그린다.
	fontRect.SetRect(lastChatContentsRect.left, 0, lastChatContentsRect.right, lastChatContentsRect.Height() / 2);

	logFont = FindFontInRect(this->pDC, &fontRect, "맑은 고딕", 12);

	hFont = CreateFontIndirect(&logFont);
	oldFont = (HFONT)this->pDC->SelectObject(hFont);

	this->pDC->DrawText(friendProfile->GetLastMessage().c_str(), &lastChatContentsRect, DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);

	this->pDC->SelectObject(oldFont);
	DeleteObject(hFont);

	// 7. 읽지 않은 개수를 그린다.
	if (unReadString != "0" && profileRect.PtInRect(point) != TRUE) {
		oldColor = this->pDC->SetBkColor(RGB(255, 0, 0));
		oldTextColor = this->pDC->SetTextColor(RGB(255, 255, 255));

		hPen = CreatePen(PS_DEFAULT, 2, RGB(255, 255, 255));
		oldPen = (HPEN)this->pDC->SelectObject(hPen);

		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		oldBrush = (HBRUSH)this->pDC->SelectObject(hBrush);

		this->pDC->Rectangle(&unReadRect);

		this->pDC->SelectObject(oldBrush);
		DeleteObject(hBrush);


		fontRect.SetRect(unReadRect.left, 0, unReadRect.right, unReadRect.Height() / 4 * 3);

		logFont = FindFontInRect(this->pDC, &fontRect, "맑은 고딕", 12);
		logFont.lfWeight = FW_BOLD;

		hFont = CreateFontIndirect(&logFont);
		oldFont = (HFONT)this->pDC->SelectObject(hFont);

		this->pDC->DrawText(unReadString.c_str(), &unReadRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		this->pDC->SelectObject(oldFont);
		DeleteObject(hFont);

		this->pDC->SelectObject(oldBrush);
		DeleteObject(hBrush);

		this->pDC->SelectObject(oldPen);
		DeleteObject(hPen);

		this->pDC->SetBkColor(oldColor);
		this->pDC->SetTextColor(oldTextColor);
	}

	// 8. 추가 옵션 도형을 그린다.
	if (profileRect.PtInRect(point) == TRUE) {
		hBrush = CreateSolidBrush(RGB(0, 0, 0));
		oldBrush = (HBRUSH)this->pDC->SelectObject(hBrush);

		// Horizontal Additional Option
		one_third = additionalOptionRect.Width() / 3;
		quarter = additionalOptionRect.Width() / 4;

		itemRect.SetRect(additionalOptionRect.left, additionalOptionRect.CenterPoint().y - quarter / 2, additionalOptionRect.left + quarter, additionalOptionRect.CenterPoint().y + quarter / 2);
		this->pDC->Ellipse(&itemRect);

		itemRect.SetRect(additionalOptionRect.CenterPoint().x - quarter / 2, itemRect.top, additionalOptionRect.CenterPoint().x - quarter / 2 + quarter, itemRect.bottom);
		this->pDC->Ellipse(&itemRect);

		itemRect.SetRect(additionalOptionRect.right - quarter, itemRect.top, additionalOptionRect.right, itemRect.bottom);
		this->pDC->Ellipse(&itemRect);

		this->pDC->SelectObject(oldBrush);
		DeleteObject(hBrush);

		this->pDC->SetTextColor(oldTextColor);
		this->pDC->SetBkColor(oldColor);
	}
	
	// </그린다.>
	// ============================================================================================================================================

	this->y += profileRect.Height();
}

void DrawingGenerator::Visit(ChatProfile* chatProfile) {
	chatProfile->GetChatProfileState()->Accept(this);
}

void DrawingGenerator::Visit(SystemChatProfileState* systemChatProfileState) {
	CRect clientRect;
	CRect chatItemRect;
	CRect basicBalloonRect;
	CRect contentsRect;

	LOGFONT logFontNickname;
	LOGFONT logFontContents;

	HFONT hFont;
	HFONT oldFont;

	COLORREF bkColor = RGB(255, 255, 255);
	COLORREF oldColor;
	COLORREF oldTextColor;

	TEXTMETRIC metric;

	string originalSystemMessage;
	string systemMessage;
	string command;
	string writer;
	string sentAt;
	string dateString;

	LONG otherAccountImage = GetSystemMetrics(SM_CXVIRTUALSCREEN) / 22;
	LONG sideMargin = otherAccountImage / 3;
	LONG pointedWidth = sideMargin / 2;
	LONG textHeight;
	LONG i = 0;

	Date date;

	size_t strOffset;
	size_t strIndex;

	SubjectState* subjectState;

	this->pCurrentWnd->GetClientRect(&clientRect);

	subjectState = dynamic_cast<ItemSubject*>(this->pCurrentWnd)->GetSubjectState();//

	ZeroMemory(&logFontNickname, sizeof(LOGFONT));
	ZeroMemory(&logFontContents, sizeof(LOGFONT));

	logFontNickname.lfHeight = -MulDiv(10, this->pDC->GetDeviceCaps(LOGPIXELSY), 72);
	strcpy_s(logFontNickname.lfFaceName, subjectState->GetLogFontFaceName().c_str());

	logFontContents.lfHeight = subjectState->GetLogFontHeight(); // 9포인트
	strcpy_s(logFontContents.lfFaceName, subjectState->GetLogFontFaceName().c_str());

	hFont = CreateFontIndirect(&logFontNickname);
	oldFont = (HFONT)this->pDC->SelectObject(hFont);

	this->pDC->GetTextMetrics(&metric);
	textHeight = metric.tmHeight;
	// ============================================================================================================================================
	// 1. <영역들을 구한다.>
	/*1. 말풍선, 2. 대화 내용*/
	chatItemRect.SetRect(sideMargin, this->y - textHeight * 2, clientRect.Width() - sideMargin, this->y);

	basicBalloonRect.SetRect(chatItemRect.left, chatItemRect.top + pointedWidth / 4, chatItemRect.right, chatItemRect.bottom - pointedWidth / 4);

	contentsRect.SetRect(chatItemRect.left, chatItemRect.top + pointedWidth / 4, chatItemRect.right, chatItemRect.bottom - pointedWidth / 4);

	contentsRect.DeflateRect(pointedWidth / 4, pointedWidth / 4);

	originalSystemMessage = systemChatProfileState->GetCurrentMessage();

	// 1. 명령어를 구한다.
	strIndex = originalSystemMessage.find(' ');

	command = originalSystemMessage.substr(0, strIndex);

	strOffset = strIndex + 1;

	// 2. 작성자를 구한다.
	writer = systemChatProfileState->GetPersonalName();

	// 3. 시스템 메세지를 만든다.
	systemMessage = writer;
	if (command == "DATE") {
		sentAt = systemChatProfileState->GetSentAt();

		dateString = sentAt.substr(0, 8);
		date = Date((char*)dateString.c_str());

		systemMessage = "-------------------------------------------------------------------------------------- " + date.GetConvertDateKoreanString() +
			" --------------------------------------------------------------------------------------";

		bkColor = this->backgroundColor;
	}
	else if (command == "NOTICE") {
		systemMessage = "NOTICE Message Error!!";
	}
	else if (command == "CONNECT") {
		systemMessage += " 님이 접속하였습니다.";
	}
	else if (command == "AWAY") {
		systemMessage += " 님이 접속을 종료하였습니다.";
	}
	else if (command == "OUT") {
		systemMessage += " 님이 방에서 나갔습니다.";
	}
	else if (command == "KICK") {
		systemMessage += " 님이 방에서 쫓겨났습니다.";
	}
	else if (command == "REMOVE") {
		systemMessage += " 님이 삭제했습니다.";
	}

	// ============================================================================================================================================
	
	// ============================================================================================================================================
	// 2. <그릴 준비를 한다.>
	

	// ============================================================================================================================================
	
	// ============================================================================================================================================
	// 3. <그린다.>
	this->pDC->SelectObject(GetStockObject(bkColor));
	this->pDC->SelectObject(GetStockObject(DC_PEN));
	this->pDC->SetDCPenColor(bkColor);

	this->pDC->SelectObject(GetStockObject(DC_BRUSH));
	this->pDC->SetDCBrushColor(bkColor);

	// System (type == 1) = BasicBalloon
	this->pDC->Rectangle(&basicBalloonRect);

	oldColor = this->pDC->SetBkColor(bkColor);
	oldTextColor = this->pDC->SetTextColor(this->textColor);

	this->pDC->DrawText(systemMessage.c_str(), &contentsRect, DT_CENTER | DT_VCENTER);

	this->pDC->SetTextColor(oldTextColor);
	this->pDC->SetBkColor(oldColor);

	this->pDC->SelectObject(oldFont);
	DeleteObject(hFont);

	// ============================================================================================================================================

	this->y -= chatItemRect.Height();
}

void DrawingGenerator::Visit(OneChatProfileState* oneChatProfileState) {
	CRect clientRect;
	CRect chatItemRect;
	CRect itemRect;
	CRect imageRect;
	CRect hostNameRect;
	CRect basicBalloonRect;
	CRect triangleRect;
	CRect contentsRect;
	CRect dateRect;

	CPoint startPos;
	CPoint triangle[3];

	LOGFONT logFontNickname;
	LOGFONT logFontContents;
	HFONT hFont;
	HFONT oldFont;

	COLORREF oldColor;
	COLORREF oldTextColor;

	TEXTMETRIC metric;

	string wrappingContents;
	string timeString;
	string printingTimeString;
	string fileName;
	wstring fileName_w;

	CDC memoryDC;

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	Gdiplus::Bitmap* image;
	Gdiplus::Status imageStatus;

	CBitmap* pBitmap;

	BITMAP bitmap;
	HBITMAP hBitmap = 0;
	HBITMAP oldBitmap;

	LONG realContentsHeight;
	LONG wrappingContentsLength;
	LONG accountImage = GetSystemMetrics(SM_CXVIRTUALSCREEN) / 22;
	LONG sideMargin = accountImage / 3;
	LONG pointedWidth = sideMargin / 2;
	LONG totalWidth;
	LONG textHeight;
	LONG rowLength;
	LONG longestWidthOfContents;
	LONG balloonWidth;
	LONG hhhWidth;
	LONG hhhHeight;
	LONG hhhhWidth;
	LONG hhhhHeight;
	LONG i = 0;

	SubjectState* subjectState;
	TextExtent* textExtent;

	subjectState = dynamic_cast<ItemSubject*>(this->pCurrentWnd)->GetSubjectState();//
	textExtent = subjectState->textExtent;

	this->pCurrentWnd->GetClientRect(&clientRect);

	ZeroMemory(&logFontNickname, sizeof(LOGFONT));
	ZeroMemory(&logFontContents, sizeof(LOGFONT));

	logFontNickname.lfHeight = -MulDiv(10, this->pDC->GetDeviceCaps(LOGPIXELSY), 72);
	strcpy_s(logFontNickname.lfFaceName, subjectState->GetLogFontFaceName().c_str());

	logFontContents.lfHeight = subjectState->GetLogFontHeight(); // 9포인트
	strcpy_s(logFontContents.lfFaceName, subjectState->GetLogFontFaceName().c_str());

	hFont = CreateFontIndirect(&logFontNickname);
	oldFont = (HFONT)this->pDC->SelectObject(hFont);

	this->pDC->GetTextMetrics(&metric);
	textHeight = metric.tmHeight;

	this->pDC->SelectObject(oldFont);
	DeleteObject(hFont);
	// ============================================================================================================================================
	// 1. <영역들을 구한다.>
	/*1. 성명, 2. 이미지 URL, 3. 대화 내용, 4. 시간*/
	totalWidth = clientRect.Width() - sideMargin * 2 - pointedWidth * 3 - accountImage * 2;
	textExtent->WrappingContents(oneChatProfileState->GetCurrentMessage(), totalWidth, &wrappingContents, &wrappingContentsLength, &longestWidthOfContents);

	rowLength = DEFAULT_CHAT_ROWLENGTH + wrappingContentsLength + 1;
	realContentsHeight = (wrappingContentsLength + 1) * textHeight;

	chatItemRect.SetRect(sideMargin, this->y - rowLength * textHeight, clientRect.Width() - sideMargin, this->y);
	balloonWidth = chatItemRect.Width() - (accountImage * 2);

	// 1. 사용자 아이콘 영역을 설정한다.
	itemRect.SetRect(chatItemRect.right - accountImage, chatItemRect.top + pointedWidth, chatItemRect.right, chatItemRect.top + pointedWidth + accountImage);
	imageRect = itemRect;
	imageRect.DeflateRect(pointedWidth, pointedWidth);

	// 2. 작성자 영역을 설정한다.
	itemRect.left = itemRect.left - (pointedWidth + accountImage * 2);
	itemRect.right = itemRect.right - pointedWidth - accountImage;
	itemRect.bottom = itemRect.top + itemRect.Height() / 2;
	hostNameRect = itemRect;

	// 3. 말풍선 영역을 설정한다.
	itemRect.left = itemRect.right - (longestWidthOfContents + pointedWidth);
	itemRect.top = itemRect.bottom;
	itemRect.bottom = chatItemRect.bottom - pointedWidth;

	basicBalloonRect = itemRect;

	startPos.SetPoint(basicBalloonRect.left, basicBalloonRect.top);

	hhhWidth = basicBalloonRect.Width() / 8;
	hhhHeight = basicBalloonRect.Height() / 8;
	hhhhWidth = basicBalloonRect.Width() / 16;
	hhhhHeight = basicBalloonRect.Height() / 16;

	// 1. 왼쪽 여백 너비 = GetSystemMetrics(SM_CXVIRTUALSCREEN) / 22 / 3
	// 2. 뾰족한 너비 = 여백 너비 / 2

	// One
	triangleRect.SetRect(basicBalloonRect.Width(), hhhhHeight, basicBalloonRect.Width() + pointedWidth, hhhhHeight + pointedWidth / 2);
	triangleRect.OffsetRect(startPos);

	triangle[0].SetPoint(triangleRect.right, triangleRect.top);
	triangle[1].SetPoint(triangleRect.left, triangleRect.bottom);
	triangle[2].SetPoint(triangleRect.left, triangleRect.top);

	// 4. 대화내용 영역을 설정한다.
	contentsRect = itemRect;
	contentsRect.DeflateRect(pointedWidth / 2, pointedWidth / 2);
	contentsRect.OffsetRect(0, contentsRect.Height() / 2 - realContentsHeight / 2); // 가운데로

	// 5. 시간 영역을 설정한다.
	itemRect.SetRect(chatItemRect.left, chatItemRect.bottom - hostNameRect.Height() + pointedWidth / 2, itemRect.left - pointedWidth, chatItemRect.bottom + pointedWidth / 2);
	dateRect = itemRect;
	
	// ============================================================================================================================================

	// ============================================================================================================================================
	// 2. <그릴 준비를 한다.>


	// ============================================================================================================================================

	// ============================================================================================================================================
	// 3. <그린다.>

	// 1. 사용자 아이콘을 그린다.
	fileName = oneChatProfileState->GetAttachmentImageUrl();

	fileName_w.assign(fileName.begin(), fileName.end());

	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	image = Gdiplus::Bitmap::FromFile(fileName_w.c_str());
	imageStatus = image->GetLastStatus();
	if (imageStatus != Gdiplus::Status::Ok) {
		fileName = "Resource\\Images\\DefaultPersonalProfile.png";
		fileName_w.assign(fileName.begin(), fileName.end());
		image = Gdiplus::Bitmap::FromFile(fileName_w.c_str());
	}

	image->GetHBITMAP(Color::White, &hBitmap);

	pBitmap = CBitmap::FromHandle(hBitmap);

	pBitmap->GetBitmap(&bitmap);
	memoryDC.CreateCompatibleDC(this->pDC);

	oldBitmap = (HBITMAP)memoryDC.SelectObject(*pBitmap);

	this->pDC->StretchBlt(imageRect.left, imageRect.top, imageRect.Width(), imageRect.Height(), &memoryDC, 0, 0,
		bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

	memoryDC.SelectObject(oldBitmap);
	DeleteObject(hBitmap);

	delete image;
	GdiplusShutdown(gdiplusToken);

	// 2. 작성자 텍스트를 그린다.
	hFont = CreateFontIndirect(&logFontNickname);
	oldFont = (HFONT)this->pDC->SelectObject(hFont);

	this->pDC->DrawText(oneChatProfileState->GetPersonalName().c_str(), &hostNameRect, DT_RIGHT | DT_VCENTER);

	this->pDC->SelectObject(oldFont);
	DeleteObject(hFont);

	// 3. 말풍선 도형을 그린다.
	this->pDC->SelectObject(GetStockObject(this->selectedBackgroundColor));
	this->pDC->SelectObject(GetStockObject(DC_PEN));
	this->pDC->SetDCPenColor(this->selectedBackgroundColor);

	this->pDC->SelectObject(GetStockObject(DC_BRUSH));
	this->pDC->SetDCBrushColor(this->selectedBackgroundColor);

	this->pDC->Rectangle(&basicBalloonRect);
	this->pDC->Polygon(triangle, 3);

	// 4. 대화내용 텍스트를 그린다.
	hFont = CreateFontIndirect(&logFontContents);
	oldFont = (HFONT)this->pDC->SelectObject(hFont);

	oldColor = this->pDC->SetBkColor(this->selectedBackgroundColor);
	oldTextColor = this->pDC->SetTextColor(this->textColor);

	this->pDC->DrawText(wrappingContents.c_str(), &contentsRect, DT_VCENTER);

	this->pDC->SetTextColor(oldTextColor);
	this->pDC->SetBkColor(oldColor);

	this->pDC->SelectObject(oldFont);
	DeleteObject(hFont);

	// 5. 시간 텍스트를 그린다.
	hFont = CreateFontIndirect(&logFontContents);
	oldFont = (HFONT)this->pDC->SelectObject(hFont);

	timeString = oneChatProfileState->GetSentAt();
	timeString = timeString.substr(8, timeString.length() - 8);
	if (timeString.substr(0, 2) < "12") {
		printingTimeString = "오전 " + timeString.substr(0, 2) + ":" + timeString.substr(2, 2);
	}
	else {
		printingTimeString = "오후 " + timeString.substr(0, 2) + ":" + timeString.substr(2, 2);
	}

	this->pDC->DrawText(printingTimeString.c_str(), &dateRect, DT_RIGHT | DT_VCENTER);

	this->pDC->SelectObject(oldFont);
	DeleteObject(hFont);

	// ============================================================================================================================================

	this->y -= chatItemRect.Height();
}

void DrawingGenerator::Visit(OtherChatProfileState* otherChatProfileState) {
	CRect clientRect;
	CRect chatItemRect;
	CRect itemRect;
	CRect imageRect;
	CRect otherUserNameRect;
	CRect basicBalloonRect;
	CRect triangleRect;
	CRect contentsRect;
	CRect dateRect;

	CPoint startPos;
	CPoint triangle[3];

	LOGFONT logFontNickname;
	LOGFONT logFontContents;
	HFONT hFont;
	HFONT oldFont;

	COLORREF oldColor;
	COLORREF oldTextColor;

	TEXTMETRIC metric;

	string wrappingContents;
	string timeString;
	string printingTimeString;
	string fileName;
	wstring fileName_w;

	CDC memoryDC;

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	Gdiplus::Bitmap* image;
	Gdiplus::Status imageStatus;

	CBitmap* pBitmap;

	BITMAP bitmap;
	HBITMAP hBitmap = 0;
	HBITMAP oldBitmap;

	LONG realContentsHeight;
	LONG wrappingContentsLength;
	LONG otherAccountImage = GetSystemMetrics(SM_CXVIRTUALSCREEN) / 22;
	LONG sideMargin = otherAccountImage / 3;
	LONG pointedWidth = sideMargin / 2;
	LONG totalWidth;
	LONG textHeight;
	LONG rowLength;
	LONG longestWidthOfContents;
	LONG balloonWidth;
	LONG hhhWidth;
	LONG hhhHeight;
	LONG hhhhWidth;
	LONG hhhhHeight;
	LONG i = 0;

	SubjectState* subjectState;
	TextExtent* textExtent;

	subjectState = dynamic_cast<ItemSubject*>(this->pCurrentWnd)->GetSubjectState();//
	textExtent = subjectState->textExtent;

	this->pCurrentWnd->GetClientRect(&clientRect);

	ZeroMemory(&logFontNickname, sizeof(LOGFONT));
	ZeroMemory(&logFontContents, sizeof(LOGFONT));

	logFontNickname.lfHeight = -MulDiv(10, this->pDC->GetDeviceCaps(LOGPIXELSY), 72);
	strcpy_s(logFontNickname.lfFaceName, subjectState->GetLogFontFaceName().c_str());

	logFontContents.lfHeight = subjectState->GetLogFontHeight(); // 9포인트
	strcpy_s(logFontContents.lfFaceName, subjectState->GetLogFontFaceName().c_str());

	hFont = CreateFontIndirect(&logFontNickname);
	oldFont = (HFONT)this->pDC->SelectObject(hFont);

	this->pDC->GetTextMetrics(&metric);
	textHeight = metric.tmHeight;

	this->pDC->SelectObject(oldFont);
	DeleteObject(hFont);
	// ============================================================================================================================================
	// 1. <영역들을 구한다.>
	/*1. 성명, 2. 이미지 URL, 3. 대화 내용, 4. 시간*/
	totalWidth = clientRect.Width() - sideMargin * 2 - pointedWidth * 3 - otherAccountImage * 2;
	textExtent->WrappingContents(otherChatProfileState->GetCurrentMessage(), totalWidth, &wrappingContents, &wrappingContentsLength, &longestWidthOfContents);

	rowLength = DEFAULT_CHAT_ROWLENGTH + wrappingContentsLength + 1;
	realContentsHeight = (wrappingContentsLength + 1) * textHeight;

	chatItemRect.SetRect(sideMargin, this->y - rowLength * textHeight, clientRect.Width() - sideMargin, this->y);
	balloonWidth = chatItemRect.Width() - (otherAccountImage * 2);

	// 1. 사용자 아이콘 영역을 설정한다.
	itemRect.SetRect(chatItemRect.left, chatItemRect.top + pointedWidth, chatItemRect.left + otherAccountImage, chatItemRect.top + pointedWidth + otherAccountImage);
	imageRect = itemRect;
	imageRect.DeflateRect(pointedWidth, pointedWidth);

	// 2. 작성자 영역을 설정한다.
	itemRect.left = itemRect.right + pointedWidth;
	itemRect.right = itemRect.left + (pointedWidth + otherAccountImage * 2);
	itemRect.bottom = itemRect.top + itemRect.Height() / 2;
	otherUserNameRect = itemRect;

	// 3. 말풍선 영역을 설정한다.
	itemRect.left = chatItemRect.left + otherAccountImage + pointedWidth;
	itemRect.top = itemRect.bottom;
	itemRect.right = itemRect.left + (longestWidthOfContents + pointedWidth);
	itemRect.bottom = chatItemRect.bottom - pointedWidth;

	basicBalloonRect = itemRect;

	startPos.SetPoint(basicBalloonRect.left, basicBalloonRect.top);

	hhhWidth = basicBalloonRect.Width() / 8;
	hhhHeight = basicBalloonRect.Height() / 8;
	hhhhWidth = basicBalloonRect.Width() / 16;
	hhhhHeight = basicBalloonRect.Height() / 16;

	// 1. 왼쪽 여백 너비 = GetSystemMetrics(SM_CXVIRTUALSCREEN) / 22 / 3
	// 2. 뾰족한 너비 = 여백 너비 / 2

	// Other
	triangleRect.SetRect(-pointedWidth, hhhhHeight, 0, hhhhHeight + pointedWidth / 2);
	triangleRect.OffsetRect(startPos);

	triangle[0].SetPoint(triangleRect.left, triangleRect.top);
	triangle[1].SetPoint(triangleRect.right, triangleRect.bottom);
	triangle[2].SetPoint(triangleRect.right, triangleRect.top);

	// 4. 대화내용 영역을 설정한다.
	contentsRect = itemRect;
	contentsRect.DeflateRect(pointedWidth / 2, pointedWidth / 2);
	contentsRect.OffsetRect(0, contentsRect.Height() / 2 - realContentsHeight / 2); // 가운데로

	// 5. 시간 영역을 설정한다.
	itemRect.SetRect(itemRect.right + pointedWidth, chatItemRect.bottom - otherUserNameRect.Height() + pointedWidth / 2, chatItemRect.right, chatItemRect.bottom + pointedWidth / 2);
	dateRect = itemRect;

	// ============================================================================================================================================

	// ============================================================================================================================================
	// 2. <그릴 준비를 한다.>


	// ============================================================================================================================================

	// ============================================================================================================================================
	// 3. <그린다.>

	// 1. 사용자 아이콘을 그린다.
	fileName = otherChatProfileState->GetAttachmentImageUrl();

	fileName_w.assign(fileName.begin(), fileName.end());

	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	image = Gdiplus::Bitmap::FromFile(fileName_w.c_str());
	imageStatus = image->GetLastStatus();
	if (imageStatus != Gdiplus::Status::Ok) {
		fileName = "Resource\\Images\\DefaultPersonalProfile.png";
		fileName_w.assign(fileName.begin(), fileName.end());
		image = Gdiplus::Bitmap::FromFile(fileName_w.c_str());
	}

	image->GetHBITMAP(Color::White, &hBitmap);

	pBitmap = CBitmap::FromHandle(hBitmap);

	pBitmap->GetBitmap(&bitmap);
	memoryDC.CreateCompatibleDC(this->pDC);

	oldBitmap = (HBITMAP)memoryDC.SelectObject(*pBitmap);

	this->pDC->StretchBlt(imageRect.left, imageRect.top, imageRect.Width(), imageRect.Height(), &memoryDC, 0, 0,
		bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

	memoryDC.SelectObject(oldBitmap);
	DeleteObject(hBitmap);

	delete image;
	GdiplusShutdown(gdiplusToken);

	// 2. 작성자 텍스트를 그린다.
	hFont = CreateFontIndirect(&logFontNickname);
	oldFont = (HFONT)this->pDC->SelectObject(hFont);

	this->pDC->DrawText(otherChatProfileState->GetPersonalName().c_str(), &otherUserNameRect, DT_LEFT | DT_VCENTER);

	this->pDC->SelectObject(oldFont);
	DeleteObject(hFont);

	// 3. 말풍선 도형을 그린다.
	this->pDC->SelectObject(GetStockObject(this->selectedBackgroundColor));
	this->pDC->SelectObject(GetStockObject(DC_PEN));
	this->pDC->SetDCPenColor(this->selectedBackgroundColor);

	this->pDC->SelectObject(GetStockObject(DC_BRUSH));
	this->pDC->SetDCBrushColor(this->selectedBackgroundColor);

	this->pDC->Rectangle(&basicBalloonRect);
	this->pDC->Polygon(triangle, 3);

	// 4. 대화내용 텍스트를 그린다.
	hFont = CreateFontIndirect(&logFontContents);
	oldFont = (HFONT)this->pDC->SelectObject(hFont);

	oldColor = this->pDC->SetBkColor(this->selectedBackgroundColor);
	oldTextColor = this->pDC->SetTextColor(this->textColor);

	this->pDC->DrawText(wrappingContents.c_str(), &contentsRect, DT_VCENTER);

	this->pDC->SetTextColor(oldTextColor);
	this->pDC->SetBkColor(oldColor);

	this->pDC->SelectObject(oldFont);
	DeleteObject(hFont);

	// 5. 시간 텍스트를 그린다.
	hFont = CreateFontIndirect(&logFontContents);
	oldFont = (HFONT)this->pDC->SelectObject(hFont);

	timeString = otherChatProfileState->GetSentAt();
	timeString = timeString.substr(8, timeString.length() - 8);
	if (timeString.substr(0, 2) < "12") {
		printingTimeString = "오전 ";
	}
	else {
		printingTimeString = "오후 ";
	}
	printingTimeString += timeString.substr(0, 2) + ":" + timeString.substr(2, 2);

	this->pDC->DrawText(printingTimeString.c_str(), &dateRect, DT_LEFT | DT_VCENTER);

	this->pDC->SelectObject(oldFont);
	DeleteObject(hFont);

	// ============================================================================================================================================

	this->y -= chatItemRect.Height();
}

void DrawingGenerator::Visit(Bodys* bodys) {
	Profile* chatProfile;

	CRect clientRect;

	Long i = 0;

	if (bodys->GetBodysState() != BodysState::FRIEND && bodys->GetBodysState() != BodysState::COMMENT) {
		this->pCurrentWnd->GetClientRect(&clientRect);
		this->pDC->SetStretchBltMode(HALFTONE);
		this->pDC->FillSolidRect(&clientRect, this->backgroundColor);
	}

	while (i < bodys->GetLength()) {
		chatProfile = bodys->GetAt(i);

		chatProfile->Accept(this);

		i++;
	}
}