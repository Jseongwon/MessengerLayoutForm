// CardListStyle.cpp
/*
���ϸ�Ī : CardListStyle.cpp
��    �� : ī������ ��Ÿ�� Ŭ������ �����.
�� �� �� : ������
�ۼ����� : 2022.04.28
*/
#include "CardListStyle.h"
using namespace parkcom;

CardListStyle::CardListStyle(CWnd* pCurrentWnd) {
	this->pCurrentWnd = pCurrentWnd;
	this->onIsDrawing = true;
}

CardListStyle::~CardListStyle() {

}