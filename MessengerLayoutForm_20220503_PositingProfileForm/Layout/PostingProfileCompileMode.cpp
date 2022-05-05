// PostingProfileCompileMode.cpp
/*
���ϸ�Ī : PostingProfileCompileMode.cpp
��    �� : �����ϸ�� Ŭ������ �����Ѵ�.
�� �� �� : ������
�ۼ����� : 2022.03.24
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

	// 1. �������� ���Ѵ�.
	this->profileCompiler->pCurrentWnd->GetClientRect(&clientRect);

	itemHeight = topHeight / 3;

	postingProfileRect.SetRect(clientRect.left, 0, clientRect.left + clientRect.Width(), itemHeight);

	// 2. ��ũ�� ������ �д´�.
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

	// 3. �Խñۿ� ���� ������ �غ��Ѵ�.
	// ============================================================================================================================================
	// 1. ��θ� ���Ѵ�.
	path += "\\PostingProfiles";

	// 2. ��ĳ�ʷ� �Խñ��� ������ �д´�.
	scanner.Read((path + "\\PostingProfileIndex.txt").c_str(), ListToken::LENGTH);

	// 3. �Խñ��� �� ������ �߿��� �Խñ� ����, �Ϲ� �Խñ� ������ ���Ѵ�.
	totalPostingProfileCount = atoi((string(scanner.Scan()).c_str()));
	specialPostingProfileCount = atoi((string(scanner.Scan()).c_str()));
	normalPostingProfileCount = atoi((string(scanner.Scan()).c_str()));

	prevPostingProfileLength = profileDirector.GetProfileLength();
	if (totalPostingProfileCount != prevPostingProfileLength) {
		onIsReSizedTheScroll = true;
	}

	profileDirector.ChangedProfileLength(totalPostingProfileCount);

	// 4. �ش� ������ �ִ� Ư���� �Խñ� ī����� �׸���.
	// ============================================================================================================================================
	// 1. ��ĳ�ʷ� Ư���� �Խñ��� ������ �д´�.
	scanner.Read((path + "\\SpecialPostingProfiles.txt").c_str(), ListToken::LENGTH);

	//  2. ȭ�� ���� �ȿ� �Խñ� ī�� ���� ��ġ�� ã�´�.
	while (iRect.top < clientRect.top && iRect.bottom > clientRect.bottom) {
		i++;
		// 2.1. ������ �Ʒ��� �̵��Ѵ�.
		iRect.MoveToY(iRect.bottom);
	}
	foundIndex = i;

	this->profileCompiler->drawingGenerator->SetPosition(0, iRect.top);

	prevBaseName = profileDirector.GetBaseName();

	//  2. ȭ�� ���� �ȿ� �߿��� �Խñ� ī�� ������ ���� ���� �ݺ��Ѵ�.
	while ((iRect.top >= clientRect.top || iRect.bottom <= clientRect.bottom) && i < specialPostingProfileCount) {
		//  2.1. �Խñ� �̷��� �����.
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

		//  2.2. �Խñ� ī�� ������ ���Ѵ�.
		iRect.MoveToY(iRect.bottom);
	}

	// 5. �ش� ������ �ִ� �Ϲ��� �Խñ� ī����� �׸���.
	// ============================================================================================================================================
	// 1. ��ĳ�ʷ� Ư���� �Խñ��� ������ �д´�.
	scanner.Read((path + "\\NormalPostingProfiles.txt").c_str(), ListToken::LENGTH);

	//  2. ȭ�� ���� �ȿ� �Ϲ� �Խñ� ī�� ������ ���� ���� �ݺ��Ѵ�.
	i = 0;
	while ((iRect.top >= clientRect.top || iRect.bottom <= clientRect.bottom) && i < normalPostingProfileCount) {
		//  2.1. �Խñ� �̷��� �����.
		postingProfile = parser.ParseByPostingProfile(&scanner, i);
		// postingProfile->Repair(Kategori::NORMAL); �⺻���� NormalKategori

		currentBaseName = postingProfile->GetTitle();
		if (iRect.PtInRect(downPoint) && currentBaseName != prevBaseName) {
			profileDirector.ChangedBaseName((char*)currentBaseName.c_str());
			profileDirector.ChangedBaseIndex(i + 1);
			profileDirector.SpecialPosting(false);
		}

		postingBodys->Add(postingProfile);

		i++;

		//  2.2. �Խñ� ī�� ������ ���Ѵ�.
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