// UtilityFunction.cpp
/*
파일명칭 : UtilityFunction.cpp
작성일자 : 2021.12.09
기    능 : 유용한 함수들을 정의한다.
*/
#include "UtilityFunction.h"
#include <algorithm>
#define HUE_DEGREE 512

LOGFONT FindFontInRect(CDC* printerDC, CRect rect, CString faceName, LONG pointSize) {
	HFONT hFont;
	HFONT oldFont;

	LOGFONT itLogFont;
	LOGFONT findLogFont;

	LONG height;
	LONG sign = 1;

	BOOL isReduced = FALSE;

	TEXTMETRIC metric;

	// 1. 현재 DC에 입력받은 폰트를 설정한다.
	// + 폰트의 크기를 구한다. 일반크기 = -((논리크기 * 72) / GetDeviceCaps(pDC, LOGPIXELSY)), 논리크기 = -((일반크기 * GetDeviceCaps(pDC, LOGPIXELSY)) / 72)
	ZeroMemory(&itLogFont, sizeof(LOGFONT));

	if (pointSize < 0) {
		sign = -1;
		pointSize *= -1;
	}

	itLogFont.lfHeight = -MulDiv(pointSize * sign, printerDC->GetDeviceCaps(LOGPIXELSY), 72);
	strcpy_s(itLogFont.lfFaceName, (LPCTSTR)faceName);

	hFont = CreateFontIndirect(&itLogFont);
	oldFont = (HFONT)printerDC->SelectObject(hFont);

	// 2. 높이를 측정한다.
	printerDC->GetTextMetrics(&metric);
	height = metric.tmHeight;

	// 3. 사각영역의 높이보다 측정된 높이가 클 동안 반복한다.
	while (height > rect.Height() && pointSize > 0) {
		// 3.1. 포인트 크기를 줄인다.
		pointSize--;

		// 3.2. 현재 DC에 입력받은 폰트를 설정한다.
		printerDC->SelectObject(oldFont);
		DeleteObject(hFont);

		itLogFont.lfHeight = -MulDiv(pointSize * sign, printerDC->GetDeviceCaps(LOGPIXELSY), 72);
		hFont = CreateFontIndirect(&itLogFont);
		oldFont = (HFONT)printerDC->SelectObject(hFont);

		// 3.3. 높이를 측정한다.
		isReduced = TRUE;
		printerDC->GetTextMetrics(&metric);
		height = metric.tmHeight;
	}

	// 4. 사각영역의 높이보다 측정된 높이가 작고 포인트 크기를 줄인적이 없는동안 반복한다.
	while (height < rect.Height() && pointSize > 0 && isReduced != TRUE) {
		// 4.1. 포인트 크기를 늘린다.
		pointSize++;

		// 4.2. 현재 DC에 입력받은 폰트를 설정한다.
		printerDC->SelectObject(oldFont);
		DeleteObject(hFont);

		itLogFont.lfHeight = -MulDiv(pointSize * sign, printerDC->GetDeviceCaps(LOGPIXELSY), 72);
		hFont = CreateFontIndirect(&itLogFont);
		oldFont = (HFONT)printerDC->SelectObject(hFont);

		// 3.3. 높이를 측정한다.
		printerDC->GetTextMetrics(&metric);
		height = metric.tmHeight;
	}

	// 4. 폰트를 구한다.(폰트 초기값 현재 폰트)
	findLogFont = itLogFont;

	printerDC->SelectObject(oldFont);
	DeleteObject(hFont);

	// 5. 찾은 폰트를 출력한다.
	return findLogFont;
}

void RGBToHSV(COLORREF rgb, int& hue, DOUBLE& saturation, DOUBLE& dValueOrBrightness) {
	int Red = rgb & 0x0000ff;
	int Green = (rgb & 0x00ff00) >> 8;
	int Blue = (rgb & 0xff0000) >> 16;

	int cMin = RGB_MIN(Red, Green, Blue);
	int cMax = RGB_MAX(Red, Green, Blue);
	int delta = cMax - cMin;

	hue = 0;
	saturation = 0;
	dValueOrBrightness = cMax;
	if (cMax > 0 && cMax != cMin) {
		// OpenCV
		if (cMax == Red) {
			hue = (60 * (Green - Blue) / delta);
		}
		else if (cMax == Green) {
			hue = (60 * (Blue - Red) / delta) + 120;
		}
		else if (cMax == Blue) {
			hue = (60 * (Red - Green) / delta) + 240;
		}
		saturation = delta / dValueOrBrightness;

		dValueOrBrightness /= dValueOrBrightness;
	}
	if (hue < 0) hue += 360;
}

COLORREF HSVToRGB(int hue, DOUBLE saturation, DOUBLE dValueOrBrightness) {
	int red, green, blue;

	DOUBLE h_Red, h_Green, h_Blue;
	DOUBLE s_Red, s_Green, s_Blue;
	DOUBLE i = ((hue % 60) / 60.00) * 255;

	// Hue
	// Red
	if ((hue >= 0 && hue <= 60) || (hue >= 300 && hue <= 360)) {
		h_Red = 255;
	}
	else if (hue > 60 && hue < 120) {
		h_Red = 255 - i;
	}
	else if (hue > 240 && hue < 300) {
		h_Red = i;
	}
	else {
		h_Red = 0;
	}
	// Green
	if (hue >= 60 && hue <= 180) {
		h_Green = 255;
	}
	else if (hue > 180 && hue < 240) {
		h_Green = 255 - i;
	}
	else if (hue > 0 && hue < 60) {
		h_Green = i;
	}
	else {
		h_Green = 0;
	}
	// Blue
	if (hue >= 180 && hue <= 300) {
		h_Blue = 255;
	}
	else if (hue > 300 && hue < 360) {
		h_Blue = 255 - i;
	}
	else if (hue > 120 && hue < 180) {
		h_Blue = i;
	}
	else {
		h_Blue = 0;
	}

	// Saturation
	s_Red = h_Red + (255 - h_Red) * (1.00 - saturation);
	s_Green = h_Green + (255 - h_Green) * (1.00 - saturation);
	s_Blue = h_Blue + (255 - h_Blue) * (1.00 - saturation);

	// ValueOrBrightness
	red = (int)((s_Red + 0.5) * dValueOrBrightness);
	green = (int)((s_Green + 0.5) * dValueOrBrightness);
	blue = (int)((s_Blue + 0.5) * dValueOrBrightness);

	return RGB(red, green, blue);
}

COLORREF GetLightColor(COLORREF rgb, LONG lightness) {
	int red = rgb & 0x0000ff;
	int green = (rgb & 0x00ff00) >> 8;// (Byte)((((Word)rgb) & 0x00ff00) >> 8);
	int blue = (rgb & 0xff0000) >> 16;
	
	int hue;
	DOUBLE saturation, value;

	RGBToHSV(rgb, hue, saturation, value);

	saturation -= lightness / 100.00;
	if (lightness > 255)
		saturation = 255;
	if (lightness < 0)
		saturation = 0;

	return HSVToRGB(hue, saturation, value);
}

void ChangeBitmapColor(CBitmap* changingBitmap, COLORREF selectedColor, COLORREF changingColor) {
	int selectedRed = selectedColor & 0x0000ff;
	int selectedGreen = (selectedColor & 0x00ff00) >> 8;// (Byte)((((Word)selectedColor) & 0x00ff00) >> 8);
	int selectedBlue = (selectedColor & 0xff0000) >> 16;

	int changingRed = changingColor & 0x0000ff;
	int changingGreen = (changingColor & 0x00ff00) >> 8;// (Byte)((((Word)changingColor) & 0x00ff00) >> 8);
	int changingBlue = (changingColor & 0xff0000) >> 16;// (Byte)((changingColor & 0xff0000) >> 16);

	int currentRed;
	int currentGreen;
	int currentBlue;

	int j;
	int i = 0;

	void* bitmapBits;

	BYTE* pColumn;

	BITMAP bitmap;

	changingBitmap->GetBitmap(&bitmap);

	bitmapBits = (BYTE*)calloc(bitmap.bmHeight * bitmap.bmWidthBytes, sizeof(BYTE));// new BYTE[bitmap.bmHeight * bitmap.bmWidthBytes];

	changingBitmap->GetBitmapBits(bitmap.bmHeight * bitmap.bmWidthBytes, bitmapBits);

	while (i < bitmap.bmHeight) {
		pColumn = ((BYTE*)bitmapBits) + i * bitmap.bmWidthBytes;

		j = 0;
		while (j < bitmap.bmWidth) {
			currentRed = *pColumn;
			currentGreen = *(pColumn + 1);
			currentBlue = *(pColumn + 2);
			if (currentRed == selectedRed && currentGreen == selectedGreen && currentBlue == selectedBlue) {
				*pColumn = changingBlue;		// Blue
				*(pColumn + 1) = changingGreen;	// Green
				*(pColumn + 2) = changingRed;	// Red
			}

			pColumn += 4;

			j++;
		}

		i++;
	}

	changingBitmap->SetBitmapBits(bitmap.bmHeight * bitmap.bmWidthBytes, bitmapBits);

	if (bitmapBits != 0) {
		delete bitmapBits;
	}
}

void ChangeAlphaBlending(CBitmap* changingBitmap, COLORREF selectedColor) {
	int selectedRed = selectedColor & 0x0000ff;
	int selectedGreen = (selectedColor & 0x00ff00) >> 8;// (Byte)((((Word)selectedColor) & 0x00ff00) >> 8);
	int selectedBlue = (selectedColor & 0xff0000) >> 16;

	int currentRed;
	int currentGreen;
	int currentBlue;

	int j;
	int i = 0;

	void* bitmapBits;

	BYTE* pColumn;

	BITMAP bitmap;

	changingBitmap->GetBitmap(&bitmap);

	bitmapBits = (BYTE*)calloc(bitmap.bmHeight * bitmap.bmWidthBytes, sizeof(BYTE));// new BYTE[bitmap.bmHeight * bitmap.bmWidthBytes];

	changingBitmap->GetBitmapBits(bitmap.bmHeight * bitmap.bmWidthBytes, bitmapBits);

	while (i < bitmap.bmHeight) {
		pColumn = ((BYTE*)bitmapBits) + i * bitmap.bmWidthBytes;

		j = 0;
		while (j < bitmap.bmWidth) {
			currentRed = *pColumn;
			currentGreen = *(pColumn + 1);
			currentBlue = *(pColumn + 2);
			if (currentRed == selectedRed && currentGreen == selectedGreen && currentBlue == selectedBlue) {
				*(pColumn + 3) = 0;		// Alpha Blending
			}

			pColumn += 4;

			j++;
		}

		i++;
	}

	changingBitmap->SetBitmapBits(bitmap.bmHeight * bitmap.bmWidthBytes, bitmapBits);

	if (bitmapBits != 0) {
		delete bitmapBits;
	}
}

CString IntToString(LONG integer, BOOL isCurrency) {
	CString ret;
	CString text;

	BOOL isFirst = TRUE;

	LONG remainder;
	LONG i = integer;

	while (i > 1000) {
		if (isFirst != TRUE && isCurrency == TRUE) {
			ret = "," + ret;
		}

		remainder = i % 1000;
		text.Format("%03d", remainder);

		ret = text + ret;

		isFirst = FALSE;
		i /= 1000;
	}
	if (i > 0 || integer == 0) {
		if (isFirst != TRUE && isCurrency == TRUE) {
			ret = "," + ret;
		}
		remainder = i % 1000;
		text.Format("%d", remainder);

		ret = text + ret;
	}

	return ret;
}

wstring StringToWideString(string text) {
	wstring wText;
	wText.assign(text.begin(), text.end());
	return wText;
}

string WideStringToString(wstring wText) {
	string text;
	text.assign(wText.begin(), wText.end());
	return text;
}