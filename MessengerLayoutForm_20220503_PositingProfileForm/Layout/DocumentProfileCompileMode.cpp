// DocumentProfileCompileMode.cpp
/*
���ϸ�Ī : DocumentProfileCompileMode.cpp
��    �� : ���� �����ϸ�� Ŭ������ �����Ѵ�.
�� �� �� : ������
�ۼ����� : 2022.05.03
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
#define DEFAULT_FACENAME "���� ���"
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

	string(*chatProfileInfos) = 0;		// ��ȭ �̷��� �ʵ� �����

	UserProfile*(*userProfiles) = 0;	// ��ȭ�� �������� �̷�

	Date date;

	Long systemWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	Long imageWidth = systemWidth / 22;
	Long sideMargin = imageWidth / 3;
	Long pageSideMargin = sideMargin * 2;
	Long pointedWidth = sideMargin / 2;
	Long textHeight;
	Long index;
	Long baseIndex;						// �Խñ��� ����� ����, ����� ��ġ
	Long changedScrollMax = 0;
	Long scrollMax = 0;
	Long scrollPage = 0;
	Long scrollCurrent = 0;
	Long currentMax;
	Long totalWidth;					// ��ȭ������ ��ȭ������ �׷��� ������ �ʺ�
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
	������ ����ϱ�

	���̾ƿ�
	====================================================================================================================================================================
	(PostingHeaderProfile)
	ī�װ�	����
	�ۼ���		�ۼ���	�ۼ��� ���	1:1 ä��
	�̹���		����/�ð�	��ȸ ��ȸ��																															�߰��޴�
	--------------------------------------------------------------------------------------------------------------------------------------------------------------------
	(PostingBodyProfile)
	����





	--------------------------------------------------------------------------------------------------------------------------------------------------------------------
	��� �ޱ�

	--------------------------------------------------------------------------------------------------------------------------------------------------------------------
	(CommentProfile)
	�޸� ��۵�
	====================================================================================================================================================================
	*/

	ZeroMemory(&nicknameFont, sizeof(LOGFONT));
	ZeroMemory(&contentsFont, sizeof(LOGFONT));

	pDC = this->profileCompiler->pCurrentWnd->GetDC();

	// 1. �������� ���Ѵ�.
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

	// 2. ��ũ�� ������ �д´�.
	subject = dynamic_cast<Subject*>(this->profileCompiler->pCurrentWnd);
	index = subject->Find(Observer::SCROLL);
	if (index < 0) {
		fileNameLineNumberString.Format("%s(%d): error: ", __FILE__, __LINE__ + 1);
		AfxMessageBox(fileNameLineNumberString + "��ũ�� ��Ʈ�ѷ��� ã�� ���߽��ϴ�.\n", MB_OK);
	}
	itemScrollController = (ItemScrollController*)subject->GetAt(index);
	verticalScroll = itemScrollController->GetVerticalScroll();

	scrollMax = verticalScroll->GetMaximum();
	scrollPage = verticalScroll->GetPageLength();
	scrollCurrent = verticalScroll->GetPosition();

	// + ���� ȭ�� ������ �о�´�.
	prevClientRect = ((ItemState*)subject->GetSubjectState())->GetPrevRect();
	// ȭ�� ũ�Ⱑ �޶��� ��� ���� ��ġ�� ������ ��ġ�� �����Ѵ�.
	if (clientRect.Height() != prevClientRect.Height()) {
		scrollCurrent = scrollMax - scrollPage;
	}

	// + ȭ�� ������ ��ũ�� ��ġ�� �̵���Ų��.
	clientRect.MoveToY(-scrollCurrent);

	totalWidth = clientRect.Width() - pageSideMargin * 2;
	// 3. �Խñ� �̷¿� ���� ������ �غ��Ѵ�.
	// ============================================================================================================================================
	// 1. ���� ���õ� �Խñ��� ����� ��ġ�� �д´�. BaseIndex
	titleName = profileDirector.GetBaseName().c_str();
	baseIndex = profileDirector.GetBaseIndex();
	onIsSpecialPosting = profileDirector.IsSpecialPosting();

	baseIndexString.Format("%05d", baseIndex);

	// 2. ��θ� �����.
	if (onIsSpecialPosting == true) {
		path += "\\SpecialPostingProfile";
	}
	else {
		path += "\\NormalPostingProfile";
	}

	// 2. ȭ�� ���� �ȿ� ��� ������ ������
	if (clientRect.top < postingHeaderProfileRect.bottom || clientRect.bottom > postingHeaderProfileRect.top) {
		// 1.1. ��ĳ�ʷ� �Խñ� ����� �д´�.
		pathFileName = path + "\\PostingHeaderProfile_" + (LPCTSTR)(baseIndexString + ".txt");
		scanner.Read(pathFileName.c_str(), ListToken::LENGTH);

		// 1.2. �Խñ� ����� ȭ�� �ȿ� ������ �����.
		postingHeaderProfile = parser.ParseByPostingHeaderProfile(&scanner);
	}

	// 3. ȭ�� ���� �ȿ� ���� ������ ������
	if (clientRect.top < postingBodyProfileRect.bottom || clientRect.bottom > postingBodyProfileRect.top) {
		// 3.1. ��ĳ�ʷ� �Խñ� ������ �д´�.
		pathFileName = path + "\\PostingBodyProfile_" + (LPCTSTR)(baseIndexString + ".txt");
		scanner.Read(pathFileName.c_str(), ListToken::LENGTH);

		// + ���� ������ �� �� �� ���� ������ �ٽ� ���ؾ��Ѵ�.

		// 3.2. �Խñ� ������ ȭ�� �ȿ� ������ �����.
		postingBodyProfile = parser.ParseByPostingBodyProfile(&scanner);
	}

	// 4. ȭ�� ���� �ȿ� ��� ������ ������
	if (clientRect.top < postingCommentProfileRect.bottom || clientRect.bottom > postingCommentProfileRect.top) {
		// 4.1. ��ĳ�ʷ� �Խñ� ����� �д´�.
		pathFileName = path + "\\PostingCommentProfile_" + (LPCTSTR)(baseIndexString + ".txt");
		scanner.Read(pathFileName.c_str(), ListToken::LENGTH);

		// 4.2. �Խñ� ����� ȭ�� �ȿ� ������ �����.
		postingCommentProfile = parser.ParseByPostingCommentProfile(&scanner);
	}
	
	// 5. ��� ������ �����찡 ȭ�� �ȿ� ������ �����.
	if (clientRect.top < postingCommentEditRect.bottom || clientRect.bottom > postingCommentEditRect.top) {

	}


	// ============================================================================================================================================

	// 4. �غ�� �Խñ� �̷µ��� �׸���.
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
	// 3. ��ȭ �̷¿� ���� ������ �غ��Ѵ�.
	// ============================================================================================================================================
	//  1. ���� ������ ����� ���� ���� �д´�.
	scanner.Read((path + "\\LoginInfo.txt").c_str(), ListToken::DEFAULT);
	accountName = scanner.Scan();

	//  2. ��θ� ���Ѵ�.
	path += "\\" + accountName;

	// + ���� ���õ� ģ�� �������� �д´�.
	guestAccountName = ((ProfileForm*)this->profileCompiler->pCurrentWnd)->GetBaseName();

	//  3. ��ĳ�ʷ� ��ȭ�� ������ �д´�.
	scanner.Read((path + "\\ChatProfiles\\ChatRoom_" + (LPCTSTR)(guestAccountName + ".txt")).c_str(), ListToken::LENGTH);

	// �����ڵ�
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
	// 1. ��ũ�� ��ġ�� 0�϶� (ó�� �����ϰų� �߰��� ȭ�� ������ �ʿ��� ��), ȭ���� ũ�Ⱑ ����Ǿ��� ��, ��ȭ������ ������ ����Ǿ��� ��
	if ((scrollCurrent == 0 && prevChatProfileCount != chatContentsCount) || clientRect.Height() != prevClientRect.Height()) {
		onIsReSizedTheScroll = true;
	}

	scanner.Read((path + "\\ChatProfiles\\ChatLog_" + (LPCTSTR)(guestAccountName + ".txt")).c_str(), ListToken::LENGTH);

	// 4. �� �Ʒ��������� ȭ�� ���� �ȱ��� �ʿ��� �������� ã�´�.
	// ȭ�� ���� ���ε��� �ݺ��Ѵ�.
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
	������ ã�ƾ� �ϴ���
	1. ó�� ������ �� ȭ�� ���� �ȿ� �ִ� ��ȭ ������ ���ؾ� �Ѵ�.
	2. �߰��� ȭ�� ������ ������, ���ڰ� ��ġ�ϴ� ����, ���ϴ� ������ ��ġ���� �߰��� ȭ�� ������ ���ؾ� �Ѵ�.

	1���� ó���ϱ� ���ؼ��� ó�� ��ȭ ������ �о�鿩 ������ ���ؾ� �Ѵ�. �׷��� �ʱ� ���ǹ��� �����Ѵ�.

	2���� ó���ϱ� ���ؼ��� 1���� ���ǵ��� ��� ��ġ�ϴ� ���ȿ��� �������Ѿ� �Ѵ�.
	��ȭ������ ������ ���� �͵� ���������̴�.
	*/
	// ȭ�� �ٱ��� �������� �ݺ��Ѵ�.
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

	// ȭ�� ���� �ȿ� �������� �ݺ��Ѵ�.
	while (i < chatContentsCount && (iRect.top < clientRect.bottom && iRect.bottom > clientRect.top)) {
		chatProfileCount++;

		changedScrollMax += chatProfileHeight;

		// 1. ��ȭ ������ ���������� ��ȭ�� ������ ������ ã�´�.
		j = 0;
		while (j < userProfileCount && chatProfileInfos[0] != "System" && userProfiles[j]->GetAccountName() != chatProfileInfos[0]) {
			j++;
		}
		// 2. �ý��� �޼����̸� ������ �ý��� �޼������� ã�´�.
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
			AfxMessageBox(fileNameLineNumberString + "��ȭ�濡 �������� �ʴ� �������� ��ȭ �����Դϴ�.\n", MB_OK);
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

		// 1. ��ȭ ������ ���������� ��ȭ�� ������ ������ ã�´�.
		j = 0;
		while (j < userProfileCount && chatProfileInfos[0] != "System" && userProfiles[j]->GetAccountName().compare(chatProfileInfos[0].c_str()) != 0) {
			j++;
		}
		// 2. �ý��� �޼����̸� ������ �ý��� �޼������� ã�´�.
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
			AfxMessageBox(fileNameLineNumberString + "��ȭ�濡 �������� �ʴ� �������� ��ȭ �����Դϴ�.\n", MB_OK);
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

	// =========== ��ȭ ������ �����. ===========

	// ���� ȭ��ũ�Ⱑ ���ϴ� ȭ�� ũ�⿡ ��ĥ���� �ݺ��Ѵ�.
	//  ���ڰ� �������� ȭ��ũ�⸦ �ø���.
	iDesiredSize = changedScrollMax;
	while (i < chatContentsCount && iDesiredSize < desiredSize) {
		chatProfileCount++;

		changedScrollMax += chatProfileHeight;

		// ���� ��ȭ���� ������ ���Ѵ�.
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

		// �ִ� ���̸� ���Ѵ�.
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

	// 1. ��ȭ ������ ���� �ְ�, ���� ���ڿ� ���� ���� / �ִ� ũ�⸦ ���Ѵ�.

	// ������ : ��ȭ������ ���������� ����, ��ũ���� ���� ��ġ�� 0�� ��� ��ȭ ������ ������ �� �� ����.

	// ��ũ�� ������ ����
	// 1. ó���̰�, �ִ� ũ�Ⱑ ȭ�� �������� Ŭ �� / ���ݲ� ���� �ִ� ũ��� �����Ѵ�.
	// 2. ��ũ���� ���� ��ġ�� 0�̰�, �ִ� ũ�Ⱑ ȭ�� �������� Ŭ �� / ���ݲ� ���� �ִ� ũ��� �����Ѵ�.
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
			// 1. ���� ��ġ�� scrollMax - scrollPage���� ���� scrollCurrent�� ���� �Ÿ��� �󸶸�ŭ ������ �ִ��� ���
			// 2. ���� ����� ���� ��ġ�� changedScrollMax - scrollPage���� �Ÿ��� �� ���� ��ġ�̴�.
			scrollPosition = changedScrollMax - scrollPage;
		}

		profileDirector.ChangedProfileLength(chatProfileCount);
		profileDirector.ChangedScrollSize(clientRect.Width(), changedScrollMax, false);
		profileDirector.ChangedScrollInfo(SB_VERT, verticalScroll->GetMinimum(), changedScrollMax - 1, 5, clientRect.Height(), scrollPosition);
	}
	currentMax = scrollMax;
	// 1. ��ũ���� ���� ���
	if (scrollMax < scrollPage && changedScrollMax < scrollPage) {
		drawingYPos = changedScrollMax;
	}
	// 2. ��ũ���� ó�� ���� ���
	else if (scrollMax < scrollPage && changedScrollMax >= scrollPage) {
		currentMax = changedScrollMax;
		scrollCurrent = currentMax - scrollPage;

		drawingYPos = clientRect.Height();
	}
	// 3. ��ũ���� �߰��� ���� ���
	else {
		// 3.1. ��ũ���� ���߿� ��� ��ġ�� ���� ���
		if (scrollCurrent == 0 && scrollMax >= scrollPage) {
			currentMax = changedScrollMax;
			scrollCurrent = currentMax - scrollMax;
			drawingStartBottom += scrollCurrent;
		}

		drawingYPos = clientRect.Height() +
			(drawingStartBottom - (scrollCurrent + scrollPage));
	}
	// �ϴ� �׸��� �湮�� Ŭ������ y��ǥ�� Ŭ���̾�Ʈ�� ���ϴ� + n

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