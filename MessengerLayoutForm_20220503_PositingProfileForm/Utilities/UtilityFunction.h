// UtilityFunction.h
#ifndef _UTILITYFUNCTION_H
#define _UTILITYFUNCTION_H
#include <afxwin.h>
#include <string>
using namespace std;

#define MIN_VALUE(a, b) ((a < b) ? a : b)
#define MAX_VALUE(a, b) ((a > b) ? a : b)

#define RGB_MIN(r, g, b) MIN_VALUE(r, MIN_VALUE(g, b))
#define RGB_MAX(r, g, b) MAX_VALUE(r, MAX_VALUE(g, b))

#define GETR(red) (red & 0x0000ff)
#define GETG(green) ((green & 0x00ff00) >> 8)
#define GETB(blue) ((blue & 0xff0000) >> 16)

LOGFONT FindFontInRect(CDC* printerDC, CRect rect, CString faceName, LONG pointSize);
COLORREF GetLightColor(COLORREF rgb, LONG lightness);

void RGBToHSV(COLORREF rgb, int& hue, DOUBLE& saturation, DOUBLE& dValueOrBrightness);
COLORREF HSVToRGB(int hue, DOUBLE saturation, DOUBLE dValueOrBrightness);
void ChangeBitmapColor(CBitmap* changingBitmap, COLORREF selectedColor, COLORREF changingColor);
void ChangeAlphaBlending(CBitmap* changingBitmap, COLORREF selectedColor);
CString IntToString(LONG integer, BOOL isCurrency = FALSE);

wstring StringToWideString(string text);
string WideStringToString(wstring wText);

#endif // _UTILITYFUNCTION_H