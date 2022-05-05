// MessengerLayoutApp.cpp
/*
파일명칭 : MessengerLayoutApp.cpp
기    능 : 메신저 레이아웃 앱 클래스를 만든다.
작성일자 : 2021.10.18
*/
#include "MessengerLayoutApp.h"
#include "MessengerLayoutForm.h"
#include <afxdisp.h>

MessengerLayoutApp messengerLayoutApp;

BOOL MessengerLayoutApp::InitInstance() {
	CWinApp::InitInstance();

	MessengerLayoutForm* mainFrameForm = new MessengerLayoutForm;
	this->m_pMainWnd = mainFrameForm;

	SetRegistryKey("Messenger_Layout");
	LoadStdProfileSettings(8);

	mainFrameForm->Create(NULL, "Messenger_Layout", 13565952UL);
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CoInitialize(NULL);
	AfxEnableControlContainer();
	mainFrameForm->ShowWindow(SW_SHOW);
	mainFrameForm->UpdateWindow();

	return TRUE;
}