// SubMenuCard.h
#ifndef _SUBMENUCARD_H
#define _SUBMENUCARD_H
#include <afxwin.h>
#include <string>
using namespace std;

namespace parkcom {
	class Generator;
	class SubMenuCard {
	public:
		enum { FILTER = 0, SETTING = 1, BUTTON = 2 };
		enum ButtonState { NORMAL = 0, DOWN = 1, HOVER = 2 };

	public:
		SubMenuCard();
		SubMenuCard(string name, string buttonName);
		SubMenuCard(const SubMenuCard& source);
		~SubMenuCard();
		SubMenuCard& operator=(const SubMenuCard& source);

		void Accept(Generator* generator);

		void Repair(int imageType, bool isHover = true);
		void Repair(string imageType, bool isHover = true);

		void SetButtonState(int buttonState);

		string& GetName() const;
		string& GetButtonName() const;
		int GetButtonState() const;
		CBitmap& GetFilterImage() const;
		CBitmap& GetSettingImage() const;

	private:
		string name;
		string buttonName;
		int buttonState;

		CBitmap filterImage;
		CBitmap settingImage;
	};

	inline void SubMenuCard::SetButtonState(int buttonState) {
		this->buttonState = buttonState;
	}

	inline string& SubMenuCard::GetName() const {
		return const_cast<string&>(this->name);
	}
	inline string& SubMenuCard::GetButtonName() const {
		return const_cast<string&>(this->buttonName);
	}
	inline int SubMenuCard::GetButtonState() const {
		return this->buttonState;
	}
	inline CBitmap& SubMenuCard::GetFilterImage() const {
		return const_cast<CBitmap&>(this->filterImage);
	}
	inline CBitmap& SubMenuCard::GetSettingImage() const {
		return const_cast<CBitmap&>(this->settingImage);
	}
}

#endif // _SUBMENUCARD_H