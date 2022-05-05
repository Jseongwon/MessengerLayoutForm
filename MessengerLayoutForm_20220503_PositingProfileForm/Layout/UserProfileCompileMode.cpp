// UserProfileCompileMode.cpp
/*
파일명칭 : UserProfileCompileMode.cpp
기    능 : 컴파일모드 클래스를 정의한다.
작 성 자 : 정성원
작성일자 : 2022.04.28
*/
#include "UserProfileCompileMode.h"
#include "ProfileCompiler.h"
#include "../Scanner/Scanner.h"
#include "../Parser/Parser.h"
#include "../Generator/DrawingGenerator.h"
#include "../Profiles/PersonalProfile.h"
#include "../Profiles/FriendProfile.h"
#include "../Profiles/BodysState.h"
#include "../Profiles/ProfileFactory.h"
#include "../Profiles/ProfileDirector.h"
#include "../Observers/ItemSubject.h"
#include "../Observers/ItemObservers.h"
#include "../Observers/Scrolls.h"
#define PARKCOM_PATH "C:\\Users\\jeong\\AppData\\Local\\Parkcom\\ParkcomMessenger\\Profiles"
using namespace parkcom;

UserProfileCompileMode::UserProfileCompileMode(ProfileCompiler* profileCompiler)
	: ProfileCompileMode(profileCompiler) {
}

UserProfileCompileMode::~UserProfileCompileMode() {

}

void UserProfileCompileMode::Compile() {
	Profile* personalProfile = NULL;
	Profile* friendProfile;
	Profile* friendBodys;

	ProfileFactory profileFactory;

	ProfileDirector profileDirector(this->profileCompiler->pCurrentWnd);

	CRect clientRect;
	CRect personalProfileRect;
	CRect friendProfileRect;
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
	Long index;
	Long yPos;
	Long prevIndex;
	Long prevFriendProfileLength;
	Long currentFriendProfileLength;
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

	personalProfileRect.SetRect(0, 0, clientRect.Width(), topHeight);
	friendProfileRect.SetRect(0, 0, clientRect.Width(), topHeight / 8 * 7);
	iRect = personalProfileRect;

	// 2. 스크롤 정보를 읽는다.
	subject = dynamic_cast<Subject*>(this->profileCompiler->pCurrentWnd);
	index = subject->Find(Observer::SCROLL);
	if (index >= 0) {
		itemScrollController = (ItemScrollController*)subject->GetAt(index);
		verticalScroll = itemScrollController->GetVerticalScroll();

		scrollCurrent = verticalScroll->GetPosition();
	}
	this->profileCompiler->drawingGenerator->SetPosition(0, -scrollCurrent);
	iRect.MoveToY(-scrollCurrent);

	// 3. 사용자에 대한 정보를 준비한다.
	// ============================================================================================================================================
	//  1. 현재 접속한 사용자 계정 명을 읽는다.
	scanner.Read((path + "\\LoginInfo.txt").c_str(), ListToken::DEFAULT);
	accountName = scanner.Scan();

	//  2. 경로를 구한다.
	path += "\\" + accountName;

	//  3. 스캐너로 사용자 정보를 읽는다.
	scanner.Read((path + "\\PersonalProfile.txt").c_str(), ListToken::LENGTH);

	//  4. 개인 이력을 만든다.
	personalProfile = parser.ParseByPersonalProfile(&scanner);

	prevFriendProfileLength = profileDirector.GetProfileLength();
	currentFriendProfileLength = personalProfile->GetAddedLength();

	if (currentFriendProfileLength != prevFriendProfileLength) {
		onIsReSizedTheScroll = true;
	}

	profileDirector.ChangedProfileLength(currentFriendProfileLength);

	// 4. 해당 영역에 있는 개인 카드를 그린다.
	// ============================================================================================================================================
	// 1. 사용자 카드가 해당 영역에 있으면
	if (clientRect.top <= iRect.top || clientRect.bottom >= iRect.bottom) {
		// 1.1. 사용자 카드를 그릴 좌표를 정한다.
		this->profileCompiler->drawingGenerator->SetPosition(0, iRect.top);
		// 1.2. 사용자 카드를 그린다.
		personalProfile->Accept(this->profileCompiler->drawingGenerator);
	}

	if (personalProfile != NULL) {
		delete personalProfile;
	}

	// 5. 해당 영역에 있는 친구 카드들을 그린다.
	// ============================================================================================================================================
	//  1. 스캐너로 친구이력 정보를 읽는다.
	scanner.Read((path + "\\FriendProfiles.txt").c_str(), ListToken::LENGTH);

	yPos = iRect.bottom;
	iRect = friendProfileRect;
	iRect.MoveToY(yPos);

	friendBodys = profileFactory.CreateBodys();
	friendBodys->Repair(BodysState::FRIEND);

	prevBaseName = profileDirector.GetBaseName();

	//  2. 화면 영역 안에 친구 카드 영역 위치를 찾는다.
	while (iRect.top < clientRect.top && iRect.bottom > clientRect.bottom) {
		i++;
		// 2.1. 영역의 아래로 이동한다.
		iRect.MoveToY(iRect.bottom);
	}
	prevIndex = i;

	this->profileCompiler->drawingGenerator->SetPosition(0, iRect.top);

	//  2. 화면 영역 안에 친구 카드 영역이 있을 동안 반복한다.
	while ((iRect.top >= clientRect.top || iRect.bottom <= clientRect.bottom) && i < currentFriendProfileLength) {
		//  2.1. 친구 이력을 만든다.
		friendProfile = parser.ParseByFriendProfile(&scanner);

		currentBaseName = friendProfile->GetAccountName();
		if (iRect.PtInRect(downPoint) && currentBaseName != prevBaseName) {
			profileDirector.ChangedBaseName((char*)currentBaseName.c_str());
		}

		friendBodys->Add(friendProfile);

		i++;

		//  2.2. 친구 카드 영역을 구한다.
		iRect.MoveToY(iRect.bottom);
	}

	if (onIsReSizedTheScroll == true) {
		changedScrollMax = personalProfileRect.Height() + friendProfileRect.Height() * currentFriendProfileLength;

		profileDirector.ChangedScrollSize(clientRect.Width(), changedScrollMax);
	}

	friendBodys->Move(prevIndex);
	friendBodys->Accept(this->profileCompiler->drawingGenerator);

	if (friendBodys != 0) {
		delete friendBodys;
	}
}