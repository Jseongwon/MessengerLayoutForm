// ProfileStyle.cpp
/*
���ϸ�Ī : ProfileStyle.cpp
��    �� : �̷� �������� ��Ÿ�� Ŭ������ �����.
�� �� �� : ������
�ۼ����� : 2022.04.28
*/
#include "ProfileStyle.h"
using namespace parkcom;

ProfileStyle::ProfileStyle(CWnd* pCurrentWnd) {
	this->pCurrentWnd = pCurrentWnd;
	this->onIsDrawing = true;
}

ProfileStyle::~ProfileStyle() {

}