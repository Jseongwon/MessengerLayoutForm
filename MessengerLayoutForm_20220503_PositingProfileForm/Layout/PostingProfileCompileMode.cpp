// PostingProfileCompileMode.cpp
/*
파일명칭 : PostingProfileCompileMode.cpp
기    능 : 컴파일모드 클래스를 정의한다.
작 성 자 : 정성원
작성일자 : 2022.03.24
*/
#include "PostingProfileCompileMode.h"
#include "ProfileCompiler.h"
#include "../Scanner/Scanner.h"
#include "../Parser/Parser.h"
#include "../Generator/DrawingGenerator.h"
#include "../Profiles/PostingProfile.h"
#include "../Profiles/Kategori.h"
#include "../Profiles/BodysState.h"
#include "../Profiles/ProfileFactory.h"
#include "../Profiles/ProfileDirector.h"
#include "../Observers/ItemSubject.h"
#include "../Observers/ItemObservers.h"
#include "../Observers/Scrolls.h"
#define PARKCOM_PATH "C:\\Users\\jeong\\AppData\\Local\\Parkcom\\ParkcomMessenger\\Profiles"
using namespace parkcom;

PostingProfileCompileMode::PostingProfileCompileMode(ProfileCompiler* profileCompiler)
	: ProfileCompileMode(profileCompiler) {
}

PostingProfileCompileMode::~PostingProfileCompileMode() {

}

void PostingProfileCompileMode::Compile() {
	Profile* postingProfile;
	Profile* postingBodys;

	ProfileFactory profileFactory;

	ProfileDirector profileDirector(this->profileCompiler->pCurrentWnd);

	CRect clientRect;
	CRect postingProfileRect;
	CRect iRect;

	Scanner scanner;
	Parser parser;

	string prevBaseName;
	string currentBaseName;
	string accountName;
	string path = PARKCOM_PATH;

	Long changedScrollMax = 0;
	Long scrollCurrent = 0;
	Long systemWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	Long topHeight = systemWidth / 22;
	Long itemHeight;
	Long index;
	Long foundIndex;
	Long prevPostingProfileLength;
	Long totalPostingProfileCount;
	Long specialPostingProfileCount;
	Long normalPostingProfileCount;
	Long i = 0;

	bool onIsReSizedTheScroll = false;

	Subject* subject;
	ItemScrollController* itemScrollController;

	Scroll* verticalScroll;

	CPoint downPoint;

	downPoint = CPoint(((ItemSubject*)this->profileCompiler->pCurrentWnd)->GetSubjectState()->GetSelectedXPoint(),
		((ItemSubject*)this->profileCompiler->pCurrentWnd)->GetSubjectState()->GetSelectedYPoint());

	// 1. 영역들을 구한다.
	this->profileCompiler->pCurrentWnd->GetClientRect(&clientRect);

	itemHeight = topHeight / 3;

	postingProfileRect.SetRect(clientRect.left, 0, clientRect.left + clientRect.Width(), itemHeight);

	// 2. 스크롤 정보를 읽는다.
	subject = dynamic_cast<Subject*>(this->profileCompiler->pCurrentWnd);
	index = subject->Find(Observer::SCROLL);
	if (index >= 0) {
		itemScrollController = (ItemScrollController*)subject->GetAt(index);
		verticalScroll = itemScrollController->GetVerticalScroll();

		scrollCurrent = verticalScroll->GetPosition();
	}
	this->profileCompiler->drawingGenerator->SetPosition(0, -scrollCurrent);

	iRect = postingProfileRect;

	iRect.MoveToY(-scrollCurrent);

	postingBodys = profileFactory.CreateBodys();
	postingBodys->Repair(BodysState::POSTING);

	// 3. 게시글에 대한 정보를 준비한다.
	// ============================================================================================================================================
	// 1. 경로를 구한다.
	path += "\\PostingProfiles";

	// 2. 스캐너로 게시글의 정보를 읽는다.
	scanner.Read((path + "\\PostingProfileIndex.txt").c_str(), ListToken::LENGTH);

	// 3. 게시글의 총 개수와 중요한 게시글 개수, 일반 게시글 개수를 구한다.
	totalPostingProfileCount = atoi((string(scanner.Scan()).c_str()));
	specialPostingProfileCount = atoi((string(scanner.Scan()).c_str()));
	normalPostingProfileCount = atoi((string(scanner.Scan()).c_str()));

	prevPostingProfileLength = profileDirector.GetProfileLength();
	if (totalPostingProfileCount != prevPostingProfileLength) {
		onIsReSizedTheScroll = true;
	}

	profileDirector.ChangedProfileLength(totalPostingProfileCount);

	// 4. 해당 영역에 있는 특별한 게시글 카드들을 그린다.
	// ============================================================================================================================================
	// 1. 스캐너로 특별한 게시글의 정보를 읽는다.
	scanner.Read((path + "\\SpecialPostingProfiles.txt").c_str(), ListToken::LENGTH);

	//  2. 화면 영역 안에 게시글 카드 영역 위치를 찾는다.
	while (iRect.top < clientRect.top && iRect.bottom > clientRect.bottom) {
		i++;
		// 2.1. 영역의 아래로 이동한다.
		iRect.MoveToY(iRect.bottom);
	}
	foundIndex = i;

	this->profileCompiler->drawingGenerator->SetPosition(0, iRect.top);

	prevBaseName = profileDirector.GetBaseName();

	//  2. 화면 영역 안에 중요한 게시글 카드 영역이 있을 동안 반복한다.
	while ((iRect.top >= clientRect.top || iRect.bottom <= clientRect.bottom) && i < specialPostingProfileCount) {
		//  2.1. 게시글 이력을 만든다.
		postingProfile = parser.ParseByPostingProfile(&scanner, i);
		postingProfile->Repair(Kategori::SPECIAL);

		currentBaseName = postingProfile->GetTitle();
		if (iRect.PtInRect(downPoint) && currentBaseName != prevBaseName) {
			profileDirector.ChangedBaseName((char*)currentBaseName.c_str());
			profileDirector.ChangedBaseIndex(i + 1);
			profileDirector.SpecialPosting(true);
		}

		postingBodys->Add(postingProfile);

		i++;

		//  2.2. 게시글 카드 영역을 구한다.
		iRect.MoveToY(iRect.bottom);
	}

	// 5. 해당 영역에 있는 일반의 게시글 카드들을 그린다.
	// ============================================================================================================================================
	// 1. 스캐너로 특별한 게시글의 정보를 읽는다.
	scanner.Read((path + "\\NormalPostingProfiles.txt").c_str(), ListToken::LENGTH);

	//  2. 화면 영역 안에 일반 게시글 카드 영역이 있을 동안 반복한다.
	i = 0;
	while ((iRect.top >= clientRect.top || iRect.bottom <= clientRect.bottom) && i < normalPostingProfileCount) {
		//  2.1. 게시글 이력을 만든다.
		postingProfile = parser.ParseByPostingProfile(&scanner, i);
		// postingProfile->Repair(Kategori::NORMAL); 기본값이 NormalKategori

		currentBaseName = postingProfile->GetTitle();
		if (iRect.PtInRect(downPoint) && currentBaseName != prevBaseName) {
			profileDirector.ChangedBaseName((char*)currentBaseName.c_str());
			profileDirector.ChangedBaseIndex(i + 1);
			profileDirector.SpecialPosting(false);
		}

		postingBodys->Add(postingProfile);

		i++;

		//  2.2. 게시글 카드 영역을 구한다.
		iRect.MoveToY(iRect.bottom);
	}

	if (onIsReSizedTheScroll == true) {
		changedScrollMax = postingProfileRect.Height() * totalPostingProfileCount;

		profileDirector.ChangedScrollSize(clientRect.Width(), changedScrollMax);
	}

	postingBodys->Accept(this->profileCompiler->drawingGenerator);

	if (postingBodys != 0) {
		delete postingBodys;
	}
}