// Printer.cpp
/*
파일명칭 : Printer.cpp
기    능 : 프린터 클래스를 정의한다.
작 성 자 : 정성원
작성일자 : 2022.02.17
*/
#include "Printer.h"
#include <fstream>
#include <stdlib.h>
#pragma warning(disable:4996)
using namespace parkcom;

Printer::Printer() {

}

Printer::Printer(const Printer& source) {

}

Printer::~Printer() {

}

Printer& Printer::operator=(const Printer& source) {
	return *this;
}

Long Printer::Printing(string pathFileName, string contents) {
	ofstream fileStream;

	fileStream.open(pathFileName);
	if (fileStream.good()) {
		fileStream.write(contents.c_str(), contents.length());
	}
	fileStream.close();

	return contents.length();
}

string Printer::GetAddedFieldLengthString(string contents) {
	string addedFieldLengthString;
	string bufString;
	char(*buffer);

	buffer = new char[contents.length() + 1];

	bufString = itoa(contents.length(), buffer, 10);

	addedFieldLengthString = "(" + bufString + ")" + contents;
	if (buffer != 0) {
		delete[] buffer;
	}

	return addedFieldLengthString;
}

string Printer::GetAddedTableLengthString(string contents) {
	string addedFieldLengthString;
	string bufString;
	char(*buffer);

	buffer = new char[contents.length() + 1];

	bufString = itoa(contents.length(), buffer, 10);

	addedFieldLengthString = "[" + bufString + "]" + contents;
	if (buffer != 0) {
		delete[] buffer;
	}

	return addedFieldLengthString;
}