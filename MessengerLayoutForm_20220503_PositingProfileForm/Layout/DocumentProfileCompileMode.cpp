// DocumentProfileCompileMode.cpp
/*
파일명칭 : DocumentProfileCompileMode.cpp
기    능 : 문서 컴파일모드 클래스를 정의한다.
작 성 자 : 정성원
작성일자 : 2022.05.03
*/
#include "DocumentProfileCompileMode.h"
#include "ProfileCompiler.h"
#include "../Scanner/Scanner.h"
#include "../Parser/Parser.h"
#include "../Generator/DrawingGenerator.h"
#include "../Layout/ProfileForm.h"


//#include "../Profiles/"
#include "../Profiles/PostingHeaderProfile.h"
#include "../Profiles/PostingBodyProfile.h"
#include "../Profiles/PostingCommentProfile.h"

#include "../Profiles/ChatProfile.h"
#include "../Profiles/UserProfile.h"
#include "../Profiles/BodysState.h"


#include "../Profiles/ProfileFactory.h"
#include "../Profiles/ProfileDirector.h"
#include "../Observers/ItemSubject.h"
#include "../Observers/ItemObservers.h"
#include "../Observers/TextExtent.h"
#include "../Observers/Scrolls.h"
#include "../Utilities/Date.h"
#define PARKCOM_POSTING_PATH "C:\\Users\\jeong\\AppData\\Local\\Parkcom\\ParkcomMessenger\\Profiles\\PostingProfiles"
#define DEFAULT_POSTING_ROWLENGTH	7
#define DEFAULT_COMMENT_ROWLENGTH	5
#define DEFAULT_EDITOR_ROWLENGTH	5
#define DEFAULT_FACENAME "맑은 고딕"
using namespace parkcom;

DocumentProfileCompileMode::DocumentProfileCompileMode(ProfileCompiler* profileCompiler)
	: ProfileCompileMode(profileCompiler) {
}

DocumentProfileCompileMode::~DocumentProfileCompileMode() {

}

void DocumentProfileCompileMode::Compile() {
	PostingHeaderProfile* postingHeaderProfile = 0;
	PostingBodyProfile* postingBodyProfile = 0;
	PostingCommentProfile* postingCommentProfile = 0;

	ProfileFactory profileFactory;
	ProfileDirector profileDirector(this->profileCompiler->pCurrentWnd);

	CDC* pDC;

	CRect prevClientRect;
	CRect clientRect;
	CRect postingHeaderProfileRect;
	CRect postingBodyProfileRect;
	CRect postingCommentProfileRect;
	CRect postingCommentEditRect;
	CRect iRect;

	LOGFONT nicknameFont;
	LOGFONT contentsFont;

	HFONT hFont;
	HFONT oldFont;

	TEXTMETRIC metric;

	Scanner scanner;
	Parser parser;

	CString fileNameLineNumberString;
	CString titleName;
	CString baseIndexString;

	string systemMessageTarget;
	string prevDate;
	string currentDate;
	string accountName;
	string path = PARKCOM_POSTING_PATH;
	string fileName;
	string pathFileName;

	string(*chatProfileInfos) = 0;		// 대화 이력의 필드 내용들

	UserProfile*(*userProfiles) = 0;	// 대화방 참가자의 이력

	Date date;

	Long systemWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	Long imageWidth = systemWidth / 22;
	Long sideMargin = imageWidth / 3;
	Long pageSideMargin = sideMargin * 2;
	Long pointedWidth = sideMargin / 2;
	Long textHeight;
	Long index;
	Long baseIndex;						// 게시글의 헤더와 본문, 댓글의 위치
	Long changedScrollMax = 0;
	Long scrollMax = 0;
	Long scrollPage = 0;
	Long scrollCurrent = 0;
	Long currentMax;
	Long totalWidth;					// 대화내역의 대화내용이 그려질 영역의 너비
	Long i = 0;
	Long j;

	size_t strOffset;
	size_t strIndex;

	bool onIsReSizedTheScroll = false;
	bool onIsSpecialPosting;

	Subject* subject;
	TextExtent* textExtent;
	ItemScrollController* itemScrollController;
	Scroll* verticalScroll;
	/*
	본문만 출력하기

	레이아웃
	====================================================================================================================================================================
	(PostingHeaderProfile)
	카테고리	제목
	작성자		작성자	작성자 등급	1:1 채팅
	이미지		일자/시간	조회 조회수																															추가메뉴
	--------------------------------------------------------------------------------------------------------------------------------------------------------------------
	(PostingBodyProfile)
	본문





	--------------------------------------------------------------------------------------------------------------------------------------------------------------------
	댓글 달기

	--------------------------------------------------------------------------------------------------------------------------------------------------------------------
	(CommentProfile)
	달린 댓글들
	====================================================================================================================================================================
	*/

	ZeroMemory(&nicknameFont, sizeof(LOGFONT));
	ZeroMemory(&contentsFont, sizeof(LOGFONT));

	pDC = this->profileCompiler->pCurrentWnd->GetDC();

	// 1. 영역들을 구한다.
	this->profileCompiler->pCurrentWnd->GetClientRect(&clientRect);

	nicknameFont.lfHeight = -MulDiv(10, pDC->GetDeviceCaps(LOGPIXELSY), 72);
	strcpy_s(nicknameFont.lfFaceName, DEFAULT_FACENAME);

	contentsFont.lfHeight = -MulDiv(9, pDC->GetDeviceCaps(LOGPIXELSY), 72);
	strcpy_s(contentsFont.lfFaceName, DEFAULT_FACENAME);

	hFont = CreateFontIndirect(&nicknameFont);
	oldFont = (HFONT)pDC->SelectObject(hFont);

	pDC->GetTextMetrics(&metric);

	this->profileCompiler->pCurrentWnd->ReleaseDC(pDC);

	textHeight = metric.tmHeight;

	postingHeaderProfileRect.SetRect(pageSideMargin, pageSideMargin, clientRect.Width() - pageSideMargin, imageWidth * 2);

	postingBodyProfileRect.SetRect(pageSideMargin, postingHeaderProfileRect.top + pageSideMargin * 2,
		clientRect.Width() - pageSideMargin, (postingHeaderProfileRect.top + pageSideMargin * 2) + DEFAULT_POSTING_ROWLENGTH * textHeight);

	postingCommentProfileRect.SetRect(pageSideMargin, postingBodyProfileRect.top + pageSideMargin * 2,
		clientRect.Width() - pageSideMargin, (postingBodyProfileRect.top + pageSideMargin * 2) + DEFAULT_EDITOR_ROWLENGTH * textHeight);

	postingCommentEditRect.SetRect(pageSideMargin, postingCommentProfileRect.top + pageSideMargin * 2,
		clientRect.Width() - pageSideMargin, (postingCommentProfileRect.top + pageSideMargin * 2) + DEFAULT_EDITOR_ROWLENGTH * textHeight);

	// 2. 스크롤 정보를 읽는다.
	subject = dynamic_cast<Subject*>(this->profileCompiler->pCurrentWnd);
	index = subject->Find(Observer::SCROLL);
	if (index < 0) {
		fileNameLineNumberString.Format("%s(%d): error: ", __FILE__, __LINE__ + 1);
		AfxMessageBox(fileNameLineNumberString + "스크롤 컨트롤러를 찾지 못했습니다.\n", MB_OK);
	}
	itemScrollController = (ItemScrollController*)subject->GetAt(index);
	verticalScroll = itemScrollController->GetVerticalScroll();

	scrollMax = verticalScroll->GetMaximum();
	scrollPage = verticalScroll->GetPageLength();
	scrollCurrent = verticalScroll->GetPosition();

	// + 이전 화면 영역을 읽어온다.
	prevClientRect = ((ItemState*)subject->GetSubjectState())->GetPrevRect();
	// 화면 크기가 달라질 경우 현재 위치를 마지막 위치로 조정한다.
	if (clientRect.Height() != prevClientRect.Height()) {
		scrollCurrent = scrollMax - scrollPage;
	}

	// + 화면 영역을 스크롤 위치로 이동시킨다.
	clientRect.MoveToY(-scrollCurrent);

	totalWidth = clientRect.Width() - pageSideMargin * 2;
	// 3. 게시글 이력에 대한 정보를 준비한다.
	// ============================================================================================================================================
	// 1. 현재 선택된 게시글의 제목과 위치를 읽는다. BaseIndex
	titleName = profileDirector.GetBaseName().c_str();
	baseIndex = profileDirector.GetBaseIndex();
	onIsSpecialPosting = profileDirector.IsSpecialPosting();

	baseIndexString.Format("%05d", baseIndex);

	// 2. 경로를 만든다.
	if (onIsSpecialPosting == true) {
		path += "\\SpecialPostingProfile";
	}
	else {
		path += "\\NormalPostingProfile";
	}

	// 2. 화면 영역 안에 헤더 영역이 있으면
	if (clientRect.top < postingHeaderProfileRect.bottom || clientRect.bottom > postingHeaderProfileRect.top) {
		// 1.1. 스캐너로 게시글 헤더를 읽는다.
		pathFileName = path + "\\PostingHeaderProfile_" + (LPCTSTR)(baseIndexString + ".txt");
		scanner.Read(pathFileName.c_str(), ListToken::LENGTH);

		// 1.2. 게시글 헤더가 화면 안에 있으면 만든다.
		postingHeaderProfile = parser.ParseByPostingHeaderProfile(&scanner);
	}

	// 3. 화면 영역 안에 본문 영역이 있으면
	if (clientRect.top < postingBodyProfileRect.bottom || clientRect.bottom > postingBodyProfileRect.top) {
		// 3.1. 스캐너로 게시글 본문을 읽는다.
		pathFileName = path + "\\PostingBodyProfile_" + (LPCTSTR)(baseIndexString + ".txt");
		scanner.Read(pathFileName.c_str(), ListToken::LENGTH);

		// + 본문 내용의 줄 수 를 세서 영역을 다시 구해야한다.

		// 3.2. 게시글 본문이 화면 안에 있으면 만든다.
		postingBodyProfile = parser.ParseByPostingBodyProfile(&scanner);
	}

	// 4. 화면 영역 안에 댓글 영역이 있으면
	if (clientRect.top < postingCommentProfileRect.bottom || clientRect.bottom > postingCommentProfileRect.top) {
		// 4.1. 스캐너로 게시글 댓글을 읽는다.
		pathFileName = path + "\\PostingCommentProfile_" + (LPCTSTR)(baseIndexString + ".txt");
		scanner.Read(pathFileName.c_str(), ListToken::LENGTH);

		// 4.2. 게시글 댓글이 화면 안에 있으면 만든다.
		postingCommentProfile = parser.ParseByPostingCommentProfile(&scanner);
	}
	
	// 5. 댓글 편집기 윈도우가 화면 안에 있으면 만든다.
	if (clientRect.top < postingCommentEditRect.bottom || clientRect.bottom > postingCommentEditRect.top) {

	}


	// ============================================================================================================================================

	// 4. 준비된 게시글 이력들을 그린다.
	// ============================================================================================================================================
	if (postingHeaderProfile != 0) {
		postingHeaderProfile->Accept(this->profileCompiler->drawingGenerator);
		delete postingHeaderProfile;
	}

	if (postingBodyProfile != 0) {
		postingBodyProfile->Accept(this->profileCompiler->drawingGenerator);
		delete postingBodyProfile;
	}

	if (postingCommentProfile != 0) {
		postingCommentProfile->Accept(this->profileCompiler->drawingGenerator);
		delete postingCommentProfile;
	}

	// ============================================================================================================================================
#if 0
	// 3. 대화 이력에 대한 정보를 준비한다.
	// ============================================================================================================================================
	//  1. 현재 접속한 사용자 계정 명을 읽는다.
	scanner.Read((path + "\\LoginInfo.txt").c_str(), ListToken::DEFAULT);
	accountName = scanner.Scan();

	//  2. 경로를 구한다.
	path += "\\" + accountName;

	// + 현재 선택된 친구 계정명을 읽는다.
	guestAccountName = ((ProfileForm*)this->profileCompiler->pCurrentWnd)->GetBaseName();

	//  3. 스캐너로 대화방 정보를 읽는다.
	scanner.Read((path + "\\ChatProfiles\\ChatRoom_" + (LPCTSTR)(guestAccountName + ".txt")).c_str(), ListToken::LENGTH);

	// 참가자들
	if (!scanner.IsEOF()) {
		userProfileCount = atoi((string(scanner.Scan())).c_str());
	}
	if (userProfileCount > 0) {
		userProfiles = new UserProfile*[userProfileCount];
	}

	while (i < userProfileCount) {
		parser.Parse(&scanner, &userProfileBuilder);

		userProfiles[i] = static_cast<UserProfile*>(userProfileBuilder.Build());

		i++;
	}

	prevChatProfileCount = ((ProfileForm*)this->profileCompiler->pCurrentWnd)->GetProfileLength();
	if (!scanner.IsEOF()) {
		chatContentsCount = atoi((string(scanner.Scan())).c_str());
	}
	// 1. 스크롤 위치가 0일때 (처음 시작하거나 추가로 화면 영역이 필요할 때), 화면의 크기가 변경되었을 때, 대화내역의 개수가 변경되었을 때
	if ((scrollCurrent == 0 && prevChatProfileCount != chatContentsCount) || clientRect.Height() != prevClientRect.Height()) {
		onIsReSizedTheScroll = true;
	}

	scanner.Read((path + "\\ChatProfiles\\ChatLog_" + (LPCTSTR)(guestAccountName + ".txt")).c_str(), ListToken::LENGTH);

	// 4. 맨 아래에서부터 화면 영역 안까지 필요한 정보들을 찾는다.
	// 화면 영역 밖인동안 반복한다.
	textExtent = subject->GetSubjectState()->textExtent;

	chatBodys = profileFactory.CreateBodys();
	chatBodys->Repair(BodysState::CHAT);

	i = 0;
	if (chatContentsCount > 0) {
		scanner.Scan(i, &chatProfileInfos, &chatProfileInfoCount);

		currentDate = chatProfileInfos[2];
		currentDate = currentDate.substr(0, 8);

		prevDate = currentDate;

		contentsRowLength = textExtent->GetContentsRowLength(chatProfileInfos[1], totalWidth);
		chatRowLength = contentsRowLength + DEFAULT_CHAT_ROWLENGTH;

		chatProfileHeight = textHeight * chatRowLength;

		iRect.SetRect(0, scrollBottom - textHeight * chatRowLength, clientRect.Width(), scrollBottom);

		i++;
	}
	/*
	무엇을 찾아야 하는지
	1. 처음 시작할 때 화면 영역 안에 있는 대화 내역만 구해야 한다.
	2. 추가로 화면 영역의 위까지, 일자가 일치하는 동안, 원하는 영역의 위치까지 추가될 화면 영역을 구해야 한다.

	1번을 처리하기 위해서는 처음 대화 내역을 읽어들여 영역을 구해야 한다. 그래야 초기 조건문을 만족한다.

	2번을 처리하기 위해서는 1번의 조건들이 모두 일치하는 동안에만 누적시켜야 한다.
	대화내역의 개수를 세는 것도 마찬가지이다.
	*/
	// 화면 바깥에 있을동안 반복한다.
	while (i < chatContentsCount && iRect.top >= clientRect.bottom) {
		chatProfileCount++;

		changedScrollMax += chatProfileHeight;

		if (chatProfileInfos != 0) {
			delete[] chatProfileInfos;
		}
		scanner.Scan(i, &chatProfileInfos, &chatProfileInfoCount);

		if (chatProfileInfos[0] != "System") {
			contentsRowLength = textExtent->GetContentsRowLength(chatProfileInfos[1], totalWidth);
			chatRowLength = contentsRowLength + DEFAULT_CHAT_ROWLENGTH;

			chatProfileHeight = textHeight * chatRowLength;
		}
		else {
			chatProfileHeight = textHeight * 2;
		}
		iRect.bottom = iRect.top;
		iRect.SetRect(0, iRect.bottom - chatProfileHeight, clientRect.Width(), iRect.bottom);

		i++;
	}

	if (iRect.bottom > clientRect.top) {
		drawingStartBottom = iRect.bottom;
	}

	// 화면 영역 안에 있을동안 반복한다.
	while (i < chatContentsCount && (iRect.top < clientRect.bottom && iRect.bottom > clientRect.top)) {
		chatProfileCount++;

		changedScrollMax += chatProfileHeight;

		// 1. 대화 내역의 계정명으로 대화방 참가자 정보를 찾는다.
		j = 0;
		while (j < userProfileCount && chatProfileInfos[0] != "System" && userProfiles[j]->GetAccountName() != chatProfileInfos[0]) {
			j++;
		}
		// 2. 시스템 메세지이면 누구의 시스템 메세지인지 찾는다.
		if (chatProfileInfos[0] == "System") {
			strIndex = chatProfileInfos[1].find(' ');
			strOffset = strIndex + 1;

			systemMessageTarget = chatProfileInfos[1].substr(strOffset, chatProfileInfos[1].length() - strOffset);

			j = 0;
		}
		while (j < userProfileCount && chatProfileInfos[0] == "System" && userProfiles[j]->GetAccountName() != systemMessageTarget) {
			j++;
		}
		if (j >= userProfileCount && userProfiles[j]->GetAccountName().compare(chatProfileInfos[0].c_str()) != 0) {
			fileNameLineNumberString.Format("%s(%d): error: ", __FILE__, __LINE__ + 1);
			AfxMessageBox(fileNameLineNumberString + "대화방에 존재하지 않는 참가자의 대화 내역입니다.\n", MB_OK);
		}
		chatProfileBuilder = ChatProfileBuilder(userProfiles[j]->GetPersonalName(), userProfiles[j]->GetAttachmentImageUrl());

		parser.Parse(&scanner, i - 1, &chatProfileBuilder);

		chatProfile = chatProfileBuilder.Build();

		if (chatProfile->GetAccountName() == "System") {
			chatProfile->SetState(ChatProfile::SYSTEM);
		}
		else if (chatProfile->GetAccountName() == userProfiles[0]->GetAccountName()) {
			chatProfile->SetState(ChatProfile::ONE);
		}
		else {
			chatProfile->SetState(ChatProfile::OTHER);
		}

		chatBodys->Add(chatProfile);

		if (chatProfileInfos != 0) {
			delete[] chatProfileInfos;
		}
		scanner.Scan(i, &chatProfileInfos, &chatProfileInfoCount);

		if (chatProfileInfos[0] != "System") {
			contentsRowLength = textExtent->GetContentsRowLength(chatProfileInfos[1], totalWidth);
			chatRowLength = contentsRowLength + DEFAULT_CHAT_ROWLENGTH;

			chatProfileHeight = textHeight * chatRowLength;
		}
		else {
			chatProfileHeight = textHeight * 2;
		}

		iRect.bottom = iRect.top;
		iRect.SetRect(0, iRect.bottom - chatProfileHeight, clientRect.Width(), iRect.bottom);

		i++;
	}
	if (i == chatContentsCount && (iRect.top < clientRect.bottom && iRect.bottom > clientRect.top)) {
		chatProfileCount++;

		changedScrollMax += chatProfileHeight;

		// 1. 대화 내역의 계정명으로 대화방 참가자 정보를 찾는다.
		j = 0;
		while (j < userProfileCount && chatProfileInfos[0] != "System" && userProfiles[j]->GetAccountName().compare(chatProfileInfos[0].c_str()) != 0) {
			j++;
		}
		// 2. 시스템 메세지이면 누구의 시스템 메세지인지 찾는다.
		if (chatProfileInfos[0] == "System") {
			strIndex = chatProfileInfos[1].find(' ');
			strOffset = strIndex + 1;

			systemMessageTarget = chatProfileInfos[1].substr(strOffset, chatProfileInfos[1].length() - strOffset);

			j = 0;
		}
		while (j < userProfileCount && chatProfileInfos[0] == "System" && userProfiles[j]->GetAccountName() != systemMessageTarget) {
			j++;
		}
		if (j >= userProfileCount && userProfiles[j]->GetAccountName().compare(chatProfileInfos[0].c_str()) != 0) {
			fileNameLineNumberString.Format("%s(%d): error: ", __FILE__, __LINE__ + 1);
			AfxMessageBox(fileNameLineNumberString + "대화방에 존재하지 않는 참가자의 대화 내역입니다.\n", MB_OK);
		}
		chatProfileBuilder = ChatProfileBuilder(userProfiles[j]->GetPersonalName(), userProfiles[j]->GetAttachmentImageUrl());

		parser.Parse(&scanner, i - 1, &chatProfileBuilder);

		chatProfile = chatProfileBuilder.Build();

		if (chatProfile->GetAccountName() == "System") {
			chatProfile->SetState(ChatProfile::SYSTEM);
		}
		else if (chatProfile->GetAccountName() == userProfiles[0]->GetAccountName()) {
			chatProfile->SetState(ChatProfile::ONE);
		}
		else {
			chatProfile->SetState(ChatProfile::OTHER);
		}

		chatBodys->Add(chatProfile);
	}

	// =========== 대화 내역을 만든다. ===========

	// 현재 화면크기가 원하는 화면 크기에 미칠동안 반복한다.
	//  일자가 같은동안 화면크기를 늘린다.
	iDesiredSize = changedScrollMax;
	while (i < chatContentsCount && iDesiredSize < desiredSize) {
		chatProfileCount++;

		changedScrollMax += chatProfileHeight;

		// 현재 대화내역 정보를 구한다.
		if (chatProfileInfos != 0) {
			delete[] chatProfileInfos;
		}
		scanner.Scan(i, &chatProfileInfos, &chatProfileInfoCount);

		if (chatProfileInfos[0] != "System") {
			contentsRowLength = textExtent->GetContentsRowLength(chatProfileInfos[1], totalWidth);
			chatRowLength = contentsRowLength + DEFAULT_CHAT_ROWLENGTH;

			chatProfileHeight = textHeight * chatRowLength;
		}
		else {
			chatProfileHeight = textHeight * 2;
		}

		// 최대 높이를 구한다.
		iDesiredSize = changedScrollMax;

		i++;
	}
	if (i == chatContentsCount && chatProfileCount < chatContentsCount && iDesiredSize < desiredSize) {
		chatProfileCount++;

		changedScrollMax += chatProfileHeight;
	}

	if (chatProfileInfos != 0) {
		delete[] chatProfileInfos;
	}

	// 1. 대화 내역이 남아 있고, 현재 일자와 같을 동안 / 최대 크기를 구한다.

	// 문제점 : 대화내역의 변동사항이 없고, 스크롤의 현재 위치가 0일 경우 대화 내역의 개수로 알 수 있음.

	// 스크롤 정보를 갱신
	// 1. 처음이고, 최대 크기가 화면 영역보다 클 때 / 지금껏 구한 최대 크기로 변경한다.
	// 2. 스크롤의 현재 위치가 0이고, 최대 크기가 화면 영역보다 클 때 / 지금껏 구한 최대 크기로 변경한다.
	if (onIsReSizedTheScroll == true) {
		scrollPosition = changedScrollMax - scrollMax;
		if (changedScrollMax == 0) {
			changedScrollMax = scrollPage - 5;
			scrollPosition = 0;
		}
		else if (scrollMax < scrollPage) {
			scrollPosition = changedScrollMax - scrollPage;
		}
		else if (clientRect.Height() != prevClientRect.Height()) {
			// 1. 시작 위치인 scrollMax - scrollPage에서 현재 scrollCurrent를 빼서 거리가 얼마만큼 떨어져 있는지 계산
			// 2. 이후 변경될 시작 위치인 changedScrollMax - scrollPage에서 거리를 뺀 값이 위치이다.
			scrollPosition = changedScrollMax - scrollPage;
		}

		profileDirector.ChangedProfileLength(chatProfileCount);
		profileDirector.ChangedScrollSize(clientRect.Width(), changedScrollMax, false);
		profileDirector.ChangedScrollInfo(SB_VERT, verticalScroll->GetMinimum(), changedScrollMax - 1, 5, clientRect.Height(), scrollPosition);
	}
	currentMax = scrollMax;
	// 1. 스크롤이 없을 경우
	if (scrollMax < scrollPage && changedScrollMax < scrollPage) {
		drawingYPos = changedScrollMax;
	}
	// 2. 스크롤이 처음 생길 경우
	else if (scrollMax < scrollPage && changedScrollMax >= scrollPage) {
		currentMax = changedScrollMax;
		scrollCurrent = currentMax - scrollPage;

		drawingYPos = clientRect.Height();
	}
	// 3. 스크롤이 중간에 있을 경우
	else {
		// 3.1. 스크롤이 도중에 상단 위치에 있을 경우
		if (scrollCurrent == 0 && scrollMax >= scrollPage) {
			currentMax = changedScrollMax;
			scrollCurrent = currentMax - scrollMax;
			drawingStartBottom += scrollCurrent;
		}

		drawingYPos = clientRect.Height() +
			(drawingStartBottom - (scrollCurrent + scrollPage));
	}
	// 일단 그리기 방문자 클래스의 y좌표는 클라이언트의 최하단 + n

	this->profileCompiler->drawingGenerator->SetPosition(0, drawingYPos);

	chatBodys->Accept(this->profileCompiler->drawingGenerator);

	i = 0;
	while (i < userProfileCount) {
		delete userProfiles[i];

		i++;
	}

	if (userProfiles != 0) {
		delete[] userProfiles;
	}
	if (chatBodys != 0) {
		delete chatBodys;
	}

	
#endif
}

#if 0
#include <stdio.h>
#pragma warning(disable:4996)

int main(int argc, char* argv[]) {
	printf("%04d", -1);

	return 0;
}

#endif