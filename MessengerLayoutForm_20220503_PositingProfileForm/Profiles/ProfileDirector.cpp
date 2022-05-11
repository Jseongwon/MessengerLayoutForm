// ProfileDirector.cpp
/*
파일명칭 : ProfileDirector.cpp
기    능 : 중재자 패턴을 이용한 이력 관리자 클래스를 정의한다.
작 성 자 : 정성원
작성일자 : 2022.03.31
*/
#include "ProfileDirector.h"
#include "PersonalProfile.h"
#include "../MessengerLayoutForm.h"
#include "../Layout/CardListForm.h"
#include "../Layout/ProfileForm.h"
#include "../Observers/ItemObservers.h"
#include "../Observers/Scrolls.h"
using namespace parkcom;

ProfileDirector::ProfileDirector(CWnd* pCurrentWnd) {
	this->pCurrentWnd = pCurrentWnd;
}

ProfileDirector::~ProfileDirector() {

}

void ProfileDirector::ChangedProfileLength(Long profileLength) {
	if (dynamic_cast<CardListForm*>(this->pCurrentWnd)) {
		dynamic_cast<CardListForm*>(this->pCurrentWnd)->m_CardLength = profileLength;
	}
	else if (dynamic_cast<ProfileForm*>(this->pCurrentWnd)) {
		dynamic_cast<ProfileForm*>(this->pCurrentWnd)->m_ProfileLength = profileLength;
	}
}

void ProfileDirector::ChangedDocumentRowLength(Long documentRowLength) {
	ProfileForm* profileForm;

	if (dynamic_cast<ProfileForm*>(this->pCurrentWnd)) {
		profileForm = dynamic_cast<ProfileForm*>(this->pCurrentWnd);
		profileForm->profileStyle->SetDocumentRowLength(documentRowLength);
	}
}

void ProfileDirector::ChangedBaseName(char(*baseName)) {
	MessengerLayoutForm* messengerLayoutForm;
	CardListForm* cardListForm;
	ProfileForm* profileForm;

	Subject* subject;
	SubjectState* subjectState;

	ItemScrollController* itemScrollController;

	CString fileNameLineNumberString;

	Long index;

	CRect chatProfileRect;
	if (dynamic_cast<CardListForm*>(this->pCurrentWnd)) {
		cardListForm = dynamic_cast<CardListForm*>(this->pCurrentWnd);
		messengerLayoutForm = dynamic_cast<MessengerLayoutForm*>(cardListForm->pParentWnd);
		profileForm = dynamic_cast<ProfileForm*>(messengerLayoutForm->profileForm);
		strcpy_s(profileForm->baseName, BASENAME_LENGTH, baseName);
		profileForm->m_ProfileLength = 0;

		profileForm->GetClientRect(&chatProfileRect);
		subjectState = profileForm->GetSubjectState();
		subjectState->SetScrollSize(chatProfileRect.Width(), chatProfileRect.Height() - 5);

		subject = dynamic_cast<Subject*>(profileForm);
		index = subject->Find(Observer::SCROLL);
		if (index < 0) {
			fileNameLineNumberString.Format("%s(%d): error: ", __FILE__, __LINE__ + 1);
			AfxMessageBox(fileNameLineNumberString + "스크롤 컨트롤러를 찾지 못했습니다.\n", MB_OK);
		}
		itemScrollController = (ItemScrollController*)subject->GetAt(index);

		itemScrollController->GetVerticalScroll()->First();
		itemScrollController->GetHorizontalScroll()->First();

		profileForm->Notify();
		profileForm->Invalidate();
	}
	else if (dynamic_cast<ProfileForm*>(this->pCurrentWnd)) {
		profileForm = dynamic_cast<ProfileForm*>(this->pCurrentWnd);
		strcpy_s(profileForm->baseName, BASENAME_LENGTH, baseName);
		profileForm->m_ProfileLength = 0;

		profileForm->GetClientRect(&chatProfileRect);
		subjectState = profileForm->GetSubjectState();
		subjectState->SetScrollSize(chatProfileRect.Width(), chatProfileRect.Height() - 5);

		subject = dynamic_cast<Subject*>(profileForm);
		index = subject->Find(Observer::SCROLL);
		if (index < 0) {
			fileNameLineNumberString.Format("%s(%d): error: ", __FILE__, __LINE__ + 1);
			AfxMessageBox(fileNameLineNumberString + "스크롤 컨트롤러를 찾지 못했습니다.\n", MB_OK);
		}
		itemScrollController = (ItemScrollController*)subject->GetAt(index);

		itemScrollController->GetVerticalScroll()->First();
		itemScrollController->GetHorizontalScroll()->First();

		profileForm->Notify();
		profileForm->Invalidate();
	}
}

void ProfileDirector::ChangedBaseIndex(Long baseIndex) {
	MessengerLayoutForm* messengerLayoutForm;
	CardListForm* cardListForm;
	ProfileForm* profileForm;

	if (dynamic_cast<CardListForm*>(this->pCurrentWnd)) {
		cardListForm = dynamic_cast<CardListForm*>(this->pCurrentWnd);
		messengerLayoutForm = dynamic_cast<MessengerLayoutForm*>(cardListForm->pParentWnd);
		profileForm = dynamic_cast<ProfileForm*>(messengerLayoutForm->profileForm);
		profileForm->baseIndex = baseIndex;
	}
	else if (dynamic_cast<ProfileForm*>(this->pCurrentWnd)) {
		dynamic_cast<ProfileForm*>(this->pCurrentWnd)->baseIndex = baseIndex;
	}
}

void ProfileDirector::ChangedScrollInfo(int nSBCode, Long minimum, Long maximum, Long lineLength, Long pageLength, Long position, bool bRedraw) {
	Subject* subject;
	
	ScrollBuilder scrollBuilder;

	ItemScrollController* itemScrollController;

	CString fileNameLineNumberString;

	Long index;

	if (dynamic_cast<ItemSubject*>(this->pCurrentWnd)) {
		if (bRedraw == true) {
			// 스크롤 빌더를 만든다.
			if (nSBCode == SB_VERT) {
				scrollBuilder = ScrollBuilder(Scroll::VERTICAL, minimum, maximum, lineLength, pageLength, position);
			}
			else {
				scrollBuilder = ScrollBuilder(Scroll::HORIZONTAL, minimum, maximum, lineLength, pageLength, position);
			}
			
			subject = dynamic_cast<Subject*>(this->pCurrentWnd);
			index = subject->Find(Observer::SCROLL);
			if (index < 0) {
				fileNameLineNumberString.Format("%s(%d): error: ", __FILE__, __LINE__ + 1);
				AfxMessageBox(fileNameLineNumberString + "스크롤 컨트롤러를 찾지 못했습니다.\n", MB_OK);
			}
			itemScrollController = (ItemScrollController*)subject->GetAt(index);
			itemScrollController->ChangedScroll(&scrollBuilder);
			if (bRedraw == true) {
				itemScrollController->Update();
			}
		}
	}
}

void ProfileDirector::ChangedScrollSize(Long totalWidth, Long totalHeight, bool bRedraw) {
	Subject* subject;
	SubjectState* subjectState;

	ItemScrollController* itemScrollController;

	CString fileNameLineNumberString;

	Long index;

	if (dynamic_cast<ItemSubject*>(this->pCurrentWnd)) {
		subjectState = dynamic_cast<ItemSubject*>(this->pCurrentWnd)->GetSubjectState();
		subjectState->SetScrollSize(totalWidth, totalHeight);
		if (bRedraw == true) {
			subject = dynamic_cast<Subject*>(this->pCurrentWnd);
			index = subject->Find(Observer::SCROLL);
			if (index < 0) {
				fileNameLineNumberString.Format("%s(%d): error: ", __FILE__, __LINE__ + 1);
				AfxMessageBox(fileNameLineNumberString + "스크롤 컨트롤러를 찾지 못했습니다.\n", MB_OK);
			}
			itemScrollController = (ItemScrollController*)subject->GetAt(index);
			itemScrollController->Update();
		}
	}
}

void ProfileDirector::ChangedScrollCurrent(int nSBCode, Long scrollCurrent, bool bRedraw) {
	Subject* subject;

	ItemScrollController* itemScrollController;

	CString fileNameLineNumberString;

	Long index;

	if (dynamic_cast<ItemSubject*>(this->pCurrentWnd)) {
		subject = dynamic_cast<Subject*>(this->pCurrentWnd);
		index = subject->Find(Observer::SCROLL);
		if (index < 0) {
			fileNameLineNumberString.Format("%s(%d): error: ", __FILE__, __LINE__ + 1);
			AfxMessageBox(fileNameLineNumberString + "스크롤 컨트롤러를 찾지 못했습니다.\n", MB_OK);
		}
		itemScrollController = (ItemScrollController*)subject->GetAt(index);
		if (nSBCode == SB_VERT) {
			itemScrollController->GetVerticalScroll()->Move(scrollCurrent);
		}
		else if (nSBCode == SB_HORZ) {
			itemScrollController->GetHorizontalScroll()->Move(scrollCurrent);
		}
		if (bRedraw == true) {
			itemScrollController->Update();
		}
	}
}

string ProfileDirector::GetBaseName() {
	string baseName;
	MessengerLayoutForm* messengerLayoutForm;
	CardListForm* cardListForm;
	ProfileForm* profileForm;

	if (dynamic_cast<CardListForm*>(this->pCurrentWnd)) {
		cardListForm = dynamic_cast<CardListForm*>(this->pCurrentWnd);
		messengerLayoutForm = dynamic_cast<MessengerLayoutForm*>(cardListForm->pParentWnd);
		profileForm = dynamic_cast<ProfileForm*>(messengerLayoutForm->profileForm);
		baseName = (LPCTSTR)profileForm->GetBaseName();
	}
	else if (dynamic_cast<ProfileForm*>(this->pCurrentWnd)) {
		profileForm = dynamic_cast<ProfileForm*>(this->pCurrentWnd);
		baseName = (LPCTSTR)profileForm->GetBaseName();
	}
	return baseName;
}

Long ProfileDirector::GetProfileLength() {
	Long profileLength = 0;
	if (dynamic_cast<CardListForm*>(this->pCurrentWnd)) {
		profileLength = dynamic_cast<CardListForm*>(this->pCurrentWnd)->m_CardLength;
	}
	else if (dynamic_cast<ProfileForm*>(this->pCurrentWnd)) {
		profileLength = dynamic_cast<ProfileForm*>(this->pCurrentWnd)->m_ProfileLength;
	}
	return profileLength;
}

Long ProfileDirector::GetDocumentRowLength() {
	Long documentRowLength = 0;
	if (dynamic_cast<ProfileForm*>(this->pCurrentWnd)) {
		documentRowLength = dynamic_cast<ProfileForm*>(this->pCurrentWnd)->profileStyle->GetDocumentRowLength();
	}
	return documentRowLength;
}

Long ProfileDirector::GetBaseIndex() {
	Long profileIndex;
	if (dynamic_cast<ProfileForm*>(this->pCurrentWnd)) {
		profileIndex = dynamic_cast<ProfileForm*>(this->pCurrentWnd)->baseIndex;
	}
	return profileIndex;
}

bool ProfileDirector::IsSpecialPosting() {
	bool onIsSpecialPosting = false;
	if (dynamic_cast<ProfileForm*>(this->pCurrentWnd)) {
		onIsSpecialPosting = dynamic_cast<ProfileForm*>(this->pCurrentWnd)->profileStyle->IsSpecialPosting();
	}
	return onIsSpecialPosting;
}

void ProfileDirector::SpecialPosting(bool isSpecialPosting) {
	MessengerLayoutForm* messengerLayoutForm;
	CardListForm* cardListForm;
	ProfileForm* profileForm;

	if (dynamic_cast<CardListForm*>(this->pCurrentWnd)) {
		cardListForm = dynamic_cast<CardListForm*>(this->pCurrentWnd);
		messengerLayoutForm = dynamic_cast<MessengerLayoutForm*>(cardListForm->pParentWnd);
		profileForm = dynamic_cast<ProfileForm*>(messengerLayoutForm->profileForm);
		profileForm->profileStyle->SpecialPosting(isSpecialPosting);
	}
	else if (dynamic_cast<ProfileForm*>(this->pCurrentWnd)) {
		dynamic_cast<ProfileForm*>(this->pCurrentWnd)->profileStyle->SpecialPosting(isSpecialPosting);
	}
}