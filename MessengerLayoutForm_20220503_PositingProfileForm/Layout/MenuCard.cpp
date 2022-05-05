// MenuCard.cpp
/*
파일명칭 : MenuCard.cpp
기    능 : 메뉴 이미지 카드 클래스를 정의한다.
작 성 자 : 정성원
작성일자 : 2022.02.23
*/
#include "MenuCard.h"
#include "NormalState.h"
#include "HoverState.h"
#include "DownState.h"
#include "../Utilities/UtilityFunction.h"
#include "../Generator/Generator.h"
#include <GdiPlus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace parkcom;
using namespace Gdiplus;

MenuCard::MenuCard() {

}

MenuCard::MenuCard(string fileName, string name, int cardState)
	: fileName(fileName), name(name) {
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	Gdiplus::Bitmap* image;

	BITMAP bitmap;
	HBITMAP hBitmap = 0;

	CBitmap* pBitmap;

	wstring filePathName_w;

	switch (cardState) {
	case 0:
		this->cardState = new NormalState;
		break;

	case 1:
		this->cardState = new DownState;
		break;

	case 2:
		this->cardState = new HoverState;
		break;

	default:
		this->cardState = 0;
		break;
	}

	filePathName_w.assign(fileName.begin(), fileName.end());

	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	image = Gdiplus::Bitmap::FromFile(filePathName_w.c_str());

	image->GetHBITMAP(Color::White, &hBitmap);

	pBitmap = CBitmap::FromHandle(hBitmap);

	pBitmap->GetBitmap(&bitmap);
	bitmap.bmBits = (BYTE*)calloc(bitmap.bmHeight * bitmap.bmWidthBytes, sizeof(BYTE));
	pBitmap->GetBitmapBits(bitmap.bmHeight * bitmap.bmWidthBytes, bitmap.bmBits);
	if (bitmap.bmBits != 0) {
		this->image.CreateBitmapIndirect(&bitmap);
		delete bitmap.bmBits;
	}

	DeleteObject(hBitmap);

	delete image;
	GdiplusShutdown(gdiplusToken);
}

MenuCard::MenuCard(const MenuCard& source)
	: fileName(source.fileName), name(source.name) {
	BITMAP bitmap;

	if (dynamic_cast<NormalState*>(source.cardState)) {
		this->cardState = new NormalState;
	}
	else if (dynamic_cast<DownState*>(source.cardState)) {
		this->cardState = new DownState;
	}
	else if (dynamic_cast<HoverState*>(source.cardState)) {
		this->cardState = new HoverState;
	}

	const_cast<MenuCard&>(source).image.GetBitmap(&bitmap);
	bitmap.bmBits = (BYTE*)calloc(bitmap.bmHeight * bitmap.bmWidthBytes, sizeof(BYTE));
	const_cast<MenuCard&>(source).image.GetBitmapBits(bitmap.bmHeight * bitmap.bmWidthBytes, bitmap.bmBits);
	if (bitmap.bmBits != 0) {
		this->image.CreateBitmapIndirect(&bitmap);
		delete bitmap.bmBits;
	}
}

MenuCard::~MenuCard() {
	this->image.DeleteObject();
	if (this->cardState != 0) {
		delete this->cardState;
	}
}

MenuCard& MenuCard::operator=(const MenuCard& source) {
	BITMAP bitmap;

	this->fileName = source.fileName;
	this->name = source.name;
	
	if (this->cardState != 0) {
		delete this->cardState;
		this->cardState = 0;
	}
	if (dynamic_cast<NormalState*>(source.cardState)) {
		this->cardState = new NormalState;
	}
	else if (dynamic_cast<DownState*>(source.cardState)) {
		this->cardState = new DownState;
	}
	else if (dynamic_cast<HoverState*>(source.cardState)) {
		this->cardState = new HoverState;
	}

	this->image.DeleteObject();
	const_cast<MenuCard&>(source).image.GetBitmap(&bitmap);
	bitmap.bmBits = (BYTE*)calloc(bitmap.bmHeight * bitmap.bmWidthBytes, sizeof(BYTE));
	const_cast<MenuCard&>(source).image.GetBitmapBits(bitmap.bmHeight * bitmap.bmWidthBytes, bitmap.bmBits);
	if (bitmap.bmBits != 0) {
		this->image.CreateBitmapIndirect(&bitmap);
		delete bitmap.bmBits;
	}

	return *this;
}

void MenuCard::Accept(Generator* generator) {
	generator->Visit(this);
}

void MenuCard::Repair(int cardState) {
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	Gdiplus::Bitmap* image;

	BITMAP bitmap;
	HBITMAP hBitmap = 0;

	CBitmap* pBitmap;

	string path;
	string fileName;
	string filePathName;
	wstring filePathName_w;

	size_t strIndex;
	size_t strOffset;

	bool isTheSame = false;

	strIndex = this->fileName.rfind('\\');

	strOffset = strIndex + 1;

	path = this->fileName.substr(0, strIndex);
	fileName = this->fileName.substr(strOffset, this->fileName.length() - strOffset);

	if (*this->cardState == cardState) {
		isTheSame = true;
	}

	if (this->cardState != 0 && isTheSame != true) {
		delete this->cardState;
		this->cardState = 0;
	}

	if (cardState == CardState::NORMAL && isTheSame != true) {
		this->cardState = new NormalState;
		filePathName = this->fileName;
	}
	else if (cardState == CardState::DOWN && isTheSame != true) {
		this->cardState = new DownState;
		filePathName = path + "\\Down" + fileName;
	}
	else if (cardState == CardState::HOVER && isTheSame != true) {
		this->cardState = new HoverState;
		filePathName = path + "\\Hover" + fileName;
	}

	if (filePathName != "" && isTheSame != true) {
		this->image.DeleteObject();

		filePathName_w.assign(filePathName.begin(), filePathName.end());

		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

		image = Gdiplus::Bitmap::FromFile(filePathName_w.c_str());

		image->GetHBITMAP(Color::White, &hBitmap);

		pBitmap = CBitmap::FromHandle(hBitmap);

		pBitmap->GetBitmap(&bitmap);
		bitmap.bmBits = (BYTE*)calloc(bitmap.bmHeight * bitmap.bmWidthBytes, sizeof(BYTE));
		pBitmap->GetBitmapBits(bitmap.bmHeight * bitmap.bmWidthBytes, bitmap.bmBits);
		if (bitmap.bmBits != 0) {
			this->image.CreateBitmapIndirect(&bitmap);
			delete bitmap.bmBits;
		}

		DeleteObject(hBitmap);

		delete image;
		GdiplusShutdown(gdiplusToken);
	}
}

void MenuCard::Repair(string cardState) {
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	Gdiplus::Bitmap* image;

	BITMAP bitmap;
	HBITMAP hBitmap = 0;

	CBitmap* pBitmap;

	string path;
	string fileName;
	string filePathName;
	wstring filePathName_w;

	size_t strIndex;
	size_t strOffset;

	bool isTheSame = false;;

	strIndex = this->fileName.rfind('\\');

	strOffset = strIndex + 1;

	path = this->fileName.substr(0, strIndex);
	fileName = this->fileName.substr(strOffset, this->fileName.length() - strOffset);

	if (*this->cardState == (char*)cardState.c_str()) {
		isTheSame = true;
	}

	if (this->cardState != 0 && isTheSame != true) {
		delete this->cardState;
		this->cardState = 0;
	}

	if (cardState == "Normal" && isTheSame != true) {
		this->cardState = new NormalState;
		filePathName = this->fileName;
	}
	else if (cardState == "Down" && isTheSame != true) {
		this->cardState = new DownState;
		filePathName = path + "\\Down" + fileName;
	}
	else if (cardState == "Hover" && isTheSame != true) {
		this->cardState = new HoverState;
		filePathName = path + "\\Hover" + fileName;
	}

	if (fileName != "" && isTheSame != true) {
		this->image.DeleteObject();

		filePathName_w.assign(filePathName.begin(), filePathName.end());

		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

		image = Gdiplus::Bitmap::FromFile(filePathName_w.c_str());

		image->GetHBITMAP(Color::White, &hBitmap);

		pBitmap = CBitmap::FromHandle(hBitmap);

		pBitmap->GetBitmap(&bitmap);
		bitmap.bmBits = (BYTE*)calloc(bitmap.bmHeight * bitmap.bmWidthBytes, sizeof(BYTE));
		pBitmap->GetBitmapBits(bitmap.bmHeight * bitmap.bmWidthBytes, bitmap.bmBits);
		if (bitmap.bmBits != 0) {
			this->image.CreateBitmapIndirect(&bitmap);
			delete bitmap.bmBits;
		}

		DeleteObject(hBitmap);

		delete image;
		GdiplusShutdown(gdiplusToken);
	}
}