// ProfileCompiler.cpp
/*
���ϸ�Ī : ProfileCompiler.cpp
��    �� : �����ϸ�� Ŭ������ �����Ѵ�.
�� �� �� : ������
�ۼ����� : 2022.03.24
*/
#include "ProfileCompiler.h"
#include <afxwin.h>
#include "PostingProfileCompileMode.h"
#include "UserProfileCompileMode.h"
#include "ChatProfileCompileMode.h"
#include "DocumentProfileCompileMode.h"
using namespace parkcom;

ProfileCompiler::ProfileCompiler() {
	this->pCurrentWnd = 0;
	this->drawingGenerator = 0;
	this->profileCompileMode = 0;
}

ProfileCompiler::ProfileCompiler(CWnd* pCurrentWnd, DrawingGenerator* drawingGenerator) {
	this->pCurrentWnd = pCurrentWnd;
	this->drawingGenerator = drawingGenerator;
	this->profileCompileMode = 0;
}

ProfileCompiler::ProfileCompiler(const ProfileCompiler& source) {
	this->pCurrentWnd = source.pCurrentWnd;
	this->drawingGenerator = source.drawingGenerator;
	this->profileCompileMode = 0;
	if (dynamic_cast<PostingProfileCompileMode*>(source.profileCompileMode)) {
		this->profileCompileMode = new PostingProfileCompileMode(this);
	}
	else if (dynamic_cast<UserProfileCompileMode*>(source.profileCompileMode)) {
		this->profileCompileMode = new UserProfileCompileMode(this);
	}
	else if (dynamic_cast<ChatProfileCompileMode*>(source.profileCompileMode)) {
		this->profileCompileMode = new ChatProfileCompileMode(this);
	}
	else if (dynamic_cast<DocumentProfileCompileMode*>(source.profileCompileMode)) {
		this->profileCompileMode = new DocumentProfileCompileMode(this);
	}
}

ProfileCompiler::~ProfileCompiler() {
	if (this->profileCompileMode != 0) {
		delete this->profileCompileMode;
		this->profileCompileMode = 0;
	}
}

ProfileCompiler& ProfileCompiler::operator=(const ProfileCompiler& source) {
	this->pCurrentWnd = source.pCurrentWnd;
	this->drawingGenerator = source.drawingGenerator;
	if (this->profileCompileMode != 0) {
		delete this->profileCompileMode;
	}
	this->profileCompileMode = 0;
	if (dynamic_cast<PostingProfileCompileMode*>(source.profileCompileMode)) {
		this->profileCompileMode = new PostingProfileCompileMode(this);
	}
	else if (dynamic_cast<UserProfileCompileMode*>(source.profileCompileMode)) {
		this->profileCompileMode = new UserProfileCompileMode(this);
	}
	else if (dynamic_cast<ChatProfileCompileMode*>(source.profileCompileMode)) {
		this->profileCompileMode = new ChatProfileCompileMode(this);
	}
	else if (dynamic_cast<DocumentProfileCompileMode*>(source.profileCompileMode)) {
		this->profileCompileMode = new DocumentProfileCompileMode(this);
	}

	return *this;
}

void ProfileCompiler::Compile() {
	CString fileNameLineNumberString;
	if (this->profileCompileMode == 0) {
		fileNameLineNumberString.Format("%s(%d): error: ", __FILE__, __LINE__ + 1);
		AfxMessageBox(fileNameLineNumberString + "�̷� �����Ϸ��� ���°� �������� �ʾҽ��ϴ�.\n", MB_OK);
	}
	this->profileCompileMode->Compile();
}

void ProfileCompiler::Repair(int profileCompileMode) {
	if (this->profileCompileMode != 0) {
		delete this->profileCompileMode;
		this->profileCompileMode = 0;
	}
	if (profileCompileMode == ProfileCompileMode::POSTINGPROFILE) {
		this->profileCompileMode = new PostingProfileCompileMode(this);
	}
	else if (profileCompileMode == ProfileCompileMode::USERPROFILE) {
		this->profileCompileMode = new UserProfileCompileMode(this);
	}
	else if (profileCompileMode == ProfileCompileMode::CHATPROFILE) {
		this->profileCompileMode = new ChatProfileCompileMode(this);
	}
	else if (profileCompileMode == ProfileCompileMode::DOCUMENTPROFILE) {
		this->profileCompileMode = new DocumentProfileCompileMode(this);
	}
}