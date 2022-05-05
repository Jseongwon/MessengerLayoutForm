// UserProfileCompileMode.cpp
/*
���ϸ�Ī : UserProfileCompileMode.cpp
��    �� : �����ϸ�� Ŭ������ �����Ѵ�.
�� �� �� : ������
�ۼ����� : 2022.04.28
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

	// 1. �������� ���Ѵ�.
	this->profileCompiler->pCurrentWnd->GetClientRect(&clientRect);

	personalProfileRect.SetRect(0, 0, clientRect.Width(), topHeight);
	friendProfileRect.SetRect(0, 0, clientRect.Width(), topHeight / 8 * 7);
	iRect = personalProfileRect;

	// 2. ��ũ�� ������ �д´�.
	subject = dynamic_cast<Subject*>(this->profileCompiler->pCurrentWnd);
	index = subject->Find(Observer::SCROLL);
	if (index >= 0) {
		itemScrollController = (ItemScrollController*)subject->GetAt(index);
		verticalScroll = itemScrollController->GetVerticalScroll();

		scrollCurrent = verticalScroll->GetPosition();
	}
	this->profileCompiler->drawingGenerator->SetPosition(0, -scrollCurrent);
	iRect.MoveToY(-scrollCurrent);

	// 3. ����ڿ� ���� ������ �غ��Ѵ�.
	// ============================================================================================================================================
	//  1. ���� ������ ����� ���� ���� �д´�.
	scanner.Read((path + "\\LoginInfo.txt").c_str(), ListToken::DEFAULT);
	accountName = scanner.Scan();

	//  2. ��θ� ���Ѵ�.
	path += "\\" + accountName;

	//  3. ��ĳ�ʷ� ����� ������ �д´�.
	scanner.Read((path + "\\PersonalProfile.txt").c_str(), ListToken::LENGTH);

	//  4. ���� �̷��� �����.
	personalProfile = parser.ParseByPersonalProfile(&scanner);

	prevFriendProfileLength = profileDirector.GetProfileLength();
	currentFriendProfileLength = personalProfile->GetAddedLength();

	if (currentFriendProfileLength != prevFriendProfileLength) {
		onIsReSizedTheScroll = true;
	}

	profileDirector.ChangedProfileLength(currentFriendProfileLength);

	// 4. �ش� ������ �ִ� ���� ī�带 �׸���.
	// ============================================================================================================================================
	// 1. ����� ī�尡 �ش� ������ ������
	if (clientRect.top <= iRect.top || clientRect.bottom >= iRect.bottom) {
		// 1.1. ����� ī�带 �׸� ��ǥ�� ���Ѵ�.
		this->profileCompiler->drawingGenerator->SetPosition(0, iRect.top);
		// 1.2. ����� ī�带 �׸���.
		personalProfile->Accept(this->profileCompiler->drawingGenerator);
	}

	if (personalProfile != NULL) {
		delete personalProfile;
	}

	// 5. �ش� ������ �ִ� ģ�� ī����� �׸���.
	// ============================================================================================================================================
	//  1. ��ĳ�ʷ� ģ���̷� ������ �д´�.
	scanner.Read((path + "\\FriendProfiles.txt").c_str(), ListToken::LENGTH);

	yPos = iRect.bottom;
	iRect = friendProfileRect;
	iRect.MoveToY(yPos);

	friendBodys = profileFactory.CreateBodys();
	friendBodys->Repair(BodysState::FRIEND);

	prevBaseName = profileDirector.GetBaseName();

	//  2. ȭ�� ���� �ȿ� ģ�� ī�� ���� ��ġ�� ã�´�.
	while (iRect.top < clientRect.top && iRect.bottom > clientRect.bottom) {
		i++;
		// 2.1. ������ �Ʒ��� �̵��Ѵ�.
		iRect.MoveToY(iRect.bottom);
	}
	prevIndex = i;

	this->profileCompiler->drawingGenerator->SetPosition(0, iRect.top);

	//  2. ȭ�� ���� �ȿ� ģ�� ī�� ������ ���� ���� �ݺ��Ѵ�.
	while ((iRect.top >= clientRect.top || iRect.bottom <= clientRect.bottom) && i < currentFriendProfileLength) {
		//  2.1. ģ�� �̷��� �����.
		friendProfile = parser.ParseByFriendProfile(&scanner);

		currentBaseName = friendProfile->GetAccountName();
		if (iRect.PtInRect(downPoint) && currentBaseName != prevBaseName) {
			profileDirector.ChangedBaseName((char*)currentBaseName.c_str());
		}

		friendBodys->Add(friendProfile);

		i++;

		//  2.2. ģ�� ī�� ������ ���Ѵ�.
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