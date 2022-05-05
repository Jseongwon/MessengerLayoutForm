// SubMenuCard.cpp
/*
파일명칭 : SubMenuCard.cpp
기    능 : 하위 메뉴 카드 클래스를 만든다.
작 성 자 : 정성원
작성일자 : 2022.03.18
*/
#include "SubMenuCard.h"
#include "../Utilities/UtilityFunction.h"
#include "../Generator/Generator.h"
#include <GdiPlus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace parkcom;
using namespace Gdiplus;

SubMenuCard::SubMenuCard() {
	this->buttonName = NORMAL;
}

SubMenuCard::SubMenuCard(string name, string buttonName)
	: name(name), buttonName(buttonName) {
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	Gdiplus::Bitmap* image;

	BITMAP bitmap;
	HBITMAP hBitmap = 0;

	CBitmap* pBitmap;

	wstring filePathName_w;

	// 1. 필터
	filePathName_w = L"C:\\Users\\jeong\\source\\repos\\MessengerLayoutForm_20220316_DrawingGenerator\\MessengerLayoutForm_20220316_DrawingGenerator\\"
		"Resource\\Images\\Common\\Filter64x64.png";
	
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	image = Gdiplus::Bitmap::FromFile(filePathName_w.c_str());

	image->GetHBITMAP(Color::White, &hBitmap);

	pBitmap = CBitmap::FromHandle(hBitmap);

	pBitmap->GetBitmap(&bitmap);
	bitmap.bmBits = (BYTE*)calloc(bitmap.bmHeight * bitmap.bmWidthBytes, sizeof(BYTE));
	pBitmap->GetBitmapBits(bitmap.bmHeight * bitmap.bmWidthBytes, bitmap.bmBits);
	if (bitmap.bmBits != 0) {
		this->filterImage.CreateBitmapIndirect(&bitmap);
		delete bitmap.bmBits;
	}

	DeleteObject(hBitmap);

	delete image;
	GdiplusShutdown(gdiplusToken);
	// 2. 설정
	filePathName_w = L"C:\\Users\\jeong\\source\\repos\\MessengerLayoutForm_20220316_DrawingGenerator\\MessengerLayoutForm_20220316_DrawingGenerator\\"
		"Resource\\Images\\Common\\Setting64x64.png";

	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	image = Gdiplus::Bitmap::FromFile(filePathName_w.c_str());

	image->GetHBITMAP(Color::White, &hBitmap);

	pBitmap = CBitmap::FromHandle(hBitmap);

	pBitmap->GetBitmap(&bitmap);
	bitmap.bmBits = (BYTE*)calloc(bitmap.bmHeight * bitmap.bmWidthBytes, sizeof(BYTE));
	pBitmap->GetBitmapBits(bitmap.bmHeight * bitmap.bmWidthBytes, bitmap.bmBits);
	if (bitmap.bmBits != 0) {
		this->settingImage.CreateBitmapIndirect(&bitmap);
		delete bitmap.bmBits;
	}

	DeleteObject(hBitmap);

	delete image;
	GdiplusShutdown(gdiplusToken);

	this->buttonState = NORMAL;
}

SubMenuCard::SubMenuCard(const SubMenuCard& source)
	: name(source.name), buttonName(source.buttonName) {
	BITMAP bitmap;

	const_cast<SubMenuCard&>(source).filterImage.GetBitmap(&bitmap);
	bitmap.bmBits = (BYTE*)calloc(bitmap.bmHeight * bitmap.bmWidthBytes, sizeof(BYTE));
	const_cast<SubMenuCard&>(source).filterImage.GetBitmapBits(bitmap.bmHeight * bitmap.bmWidthBytes, bitmap.bmBits);
	if (bitmap.bmBits != 0) {
		this->filterImage.CreateBitmapIndirect(&bitmap);
		delete bitmap.bmBits;
	}

	const_cast<SubMenuCard&>(source).settingImage.GetBitmap(&bitmap);
	bitmap.bmBits = (BYTE*)calloc(bitmap.bmHeight * bitmap.bmWidthBytes, sizeof(BYTE));
	const_cast<SubMenuCard&>(source).settingImage.GetBitmapBits(bitmap.bmHeight * bitmap.bmWidthBytes, bitmap.bmBits);
	if (bitmap.bmBits != 0) {
		this->settingImage.CreateBitmapIndirect(&bitmap);
		delete bitmap.bmBits;
	}

	this->buttonState = source.buttonState;
}

SubMenuCard::~SubMenuCard() {
	this->filterImage.DeleteObject();
	this->settingImage.DeleteObject();
}

SubMenuCard& SubMenuCard::operator=(const SubMenuCard& source) {
	BITMAP bitmap;

	this->name = source.name;
	this->buttonName = source.buttonName;

	this->filterImage.DeleteObject();
	const_cast<SubMenuCard&>(source).filterImage.GetBitmap(&bitmap);
	bitmap.bmBits = (BYTE*)calloc(bitmap.bmHeight * bitmap.bmWidthBytes, sizeof(BYTE));
	const_cast<SubMenuCard&>(source).filterImage.GetBitmapBits(bitmap.bmHeight * bitmap.bmWidthBytes, bitmap.bmBits);
	if (bitmap.bmBits != 0) {
		this->filterImage.CreateBitmapIndirect(&bitmap);
		delete bitmap.bmBits;
	}

	this->settingImage.DeleteObject();
	const_cast<SubMenuCard&>(source).settingImage.GetBitmap(&bitmap);
	bitmap.bmBits = (BYTE*)calloc(bitmap.bmHeight * bitmap.bmWidthBytes, sizeof(BYTE));
	const_cast<SubMenuCard&>(source).settingImage.GetBitmapBits(bitmap.bmHeight * bitmap.bmWidthBytes, bitmap.bmBits);
	if (bitmap.bmBits != 0) {
		this->settingImage.CreateBitmapIndirect(&bitmap);
		delete bitmap.bmBits;
	}

	this->buttonState = source.buttonState;

	return *this;
}

void SubMenuCard::Accept(Generator* generator) {
	generator->Visit(this);
}

void SubMenuCard::Repair(int imageType, bool isHover) {
	CBitmap* targetImage = 0;

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	Gdiplus::Bitmap* image;

	BITMAP bitmap;
	HBITMAP hBitmap = 0;

	CBitmap* pBitmap;

	wstring path;
	wstring fileName;
	wstring filePathName_w;

	size_t strIndex;
	size_t strOffset;

	// 1. 타깃 이미지를 구한다.
	if (imageType == SubMenuCard::FILTER) {
		targetImage = &this->filterImage;
		filePathName_w = L"C:\\Users\\jeong\\source\\repos\\MessengerLayoutForm_20220316_DrawingGenerator\\MessengerLayoutForm_20220316_DrawingGenerator\\"
			"Resource\\Images\\Common\\Filter64x64.png";
	}
	else if(imageType == SubMenuCard::SETTING) {
		targetImage = &this->settingImage;
		filePathName_w = L"C:\\Users\\jeong\\source\\repos\\MessengerLayoutForm_20220316_DrawingGenerator\\MessengerLayoutForm_20220316_DrawingGenerator\\"
			"Resource\\Images\\Common\\Setting64x64.png";
	}

	// 2. 마우스가 위에 있으면 선택된 파일명으로 수정한다.
	if (isHover == true) {
		strIndex = filePathName_w.rfind('\\');

		strOffset = strIndex + 1;

		path = filePathName_w.substr(0, strIndex);
		fileName = filePathName_w.substr(strOffset, filePathName_w.length() - strOffset);

		filePathName_w = path + L"\\Selected" + fileName;
	}

	// 3. 타깃 이미지를 변경한다.
	targetImage->DeleteObject();

	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	image = Gdiplus::Bitmap::FromFile(filePathName_w.c_str());

	image->GetHBITMAP(Color::White, &hBitmap);

	pBitmap = CBitmap::FromHandle(hBitmap);

	pBitmap->GetBitmap(&bitmap);
	bitmap.bmBits = (BYTE*)calloc(bitmap.bmHeight * bitmap.bmWidthBytes, sizeof(BYTE));
	pBitmap->GetBitmapBits(bitmap.bmHeight * bitmap.bmWidthBytes, bitmap.bmBits);
	if (bitmap.bmBits != 0) {
		targetImage->CreateBitmapIndirect(&bitmap);
		delete bitmap.bmBits;
	}

	DeleteObject(hBitmap);

	delete image;
	GdiplusShutdown(gdiplusToken);
}

void SubMenuCard::Repair(string imageType, bool isHover) {
	CBitmap* targetImage = 0;

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	Gdiplus::Bitmap* image;

	BITMAP bitmap;
	HBITMAP hBitmap = 0;

	CBitmap* pBitmap;

	wstring path;
	wstring fileName;
	wstring filePathName_w;

	size_t strIndex;
	size_t strOffset;

	// 1. 타깃 이미지를 구한다.
	if (imageType == "Filter") {
		targetImage = &this->filterImage;
		filePathName_w = L"C:\\Users\\jeong\\source\\repos\\MessengerLayoutForm_20220316_DrawingGenerator\\MessengerLayoutForm_20220316_DrawingGenerator\\"
			"Resource\\Images\\Common\\Filter64x64.png";
	}
	else if (imageType == "Setting") {
		targetImage = &this->settingImage;
		filePathName_w = L"C:\\Users\\jeong\\source\\repos\\MessengerLayoutForm_20220316_DrawingGenerator\\MessengerLayoutForm_20220316_DrawingGenerator\\"
			"Resource\\Images\\Common\\Setting64x64.png";
	}

	// 2. 마우스가 위에 있으면 선택된 파일명으로 수정한다.
	if (isHover == true) {
		strIndex = filePathName_w.rfind('\\');

		strOffset = strIndex + 1;

		path = filePathName_w.substr(0, strIndex);
		fileName = filePathName_w.substr(strOffset, filePathName_w.length() - strOffset);

		filePathName_w = path + L"\\Selected" + fileName;
	}

	// 3. 타깃 이미지를 변경한다.
	targetImage->DeleteObject();

	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	image = Gdiplus::Bitmap::FromFile(filePathName_w.c_str());

	image->GetHBITMAP(Color::White, &hBitmap);

	pBitmap = CBitmap::FromHandle(hBitmap);

	pBitmap->GetBitmap(&bitmap);
	bitmap.bmBits = (BYTE*)calloc(bitmap.bmHeight * bitmap.bmWidthBytes, sizeof(BYTE));
	pBitmap->GetBitmapBits(bitmap.bmHeight * bitmap.bmWidthBytes, bitmap.bmBits);
	if (bitmap.bmBits != 0) {
		targetImage->CreateBitmapIndirect(&bitmap);
		delete bitmap.bmBits;
	}
	
	DeleteObject(hBitmap);

	delete image;
	GdiplusShutdown(gdiplusToken);
}