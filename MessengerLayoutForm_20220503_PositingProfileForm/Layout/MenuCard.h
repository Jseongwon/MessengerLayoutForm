// MenuCard.h
#ifndef _MENUCARD_H
#define _MENUCARD_H
#include <afxwin.h>
#include <string>
#include "CardState.h"
using namespace std;

namespace parkcom {
	class Generator;
	class MenuCard {
	public:
		MenuCard();
		MenuCard(string fileName, string name, int imageState = 0);
		MenuCard(const MenuCard& source);
		~MenuCard();
		MenuCard& operator=(const MenuCard& source);
		
		void Accept(Generator* generator);

		void Repair(int cardState);
		void Repair(string cardState);

		string& GetFileName() const;
		string& GetName() const;
		CBitmap& GetImage() const;
		CardState* GetCardState() const;

	private:
		string fileName;
		string name;
		CBitmap image;

		CardState* cardState;
	};

	inline string& MenuCard::GetFileName() const {
		return const_cast<string&>(this->fileName);
	}
	inline string& MenuCard::GetName() const {
		return const_cast<string&>(this->name);
	}
	inline CBitmap& MenuCard::GetImage() const {
		return const_cast<CBitmap&>(this->image);
	}
	inline CardState* MenuCard::GetCardState() const {
		return dynamic_cast<CardState*>(this->cardState);
	}
}

#endif // _MENUCARD_H