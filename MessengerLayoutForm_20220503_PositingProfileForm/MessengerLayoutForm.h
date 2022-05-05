// MessengerLayoutForm.h
#ifndef _MESSENGERLAYOUTFORM_H
#define _MESSENGERLAYOUTFORM_H
#include <afxwin.h>

class MenuListForm;
class SubMenuForm;
class CardListForm;
class ProfileForm;
class MessengerLayoutForm : public CFrameWnd {
public:
	MenuListForm* menuListForm;
	SubMenuForm* subMenuForm;
	CardListForm* cardListForm;
	ProfileForm* profileForm;
	
public:
	MessengerLayoutForm();

	TCHAR* GetHostName() const;

protected:
	afx_msg virtual int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg void OnKillFocus(CWnd *pCWnd);

	DECLARE_MESSAGE_MAP()

private:
	TCHAR hostName[128];
};

inline TCHAR* MessengerLayoutForm::GetHostName() const {
	return const_cast<TCHAR*>(this->hostName);
}

#endif // _MESSENGERLAYOUTFORM_H