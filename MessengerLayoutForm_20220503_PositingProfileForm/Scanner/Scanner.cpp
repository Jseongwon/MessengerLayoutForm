// Scanner.cpp
/*
파일명칭 : Scanner.cpp
기    능 : 스캐너 클래스를 정의한다.
작 성 자 : 정성원
작성일자 : 2022.02.17

디스크파일 형식
테이블 길이 : [Table Length]
필드 길이 : (Field Length)
예) [30](15)aaaaaaaaaaaa(15)bbbbbbbbbbbb
*/
#include "Scanner.h"
#include <fstream>
using namespace parkcom;

Scanner::Scanner(Long capacity)
	: tokenTable(capacity) {
	this->capacity = capacity;
	this->length = 0;
	this->current = -1;
}

Scanner::Scanner(const Scanner& source)
	: tokenTable(source.tokenTable) {
	this->capacity = source.capacity;
	this->length = source.length;
	this->current = source.current;
}

Scanner::~Scanner() {

}

Scanner& Scanner::operator=(const Scanner& source) {
	this->tokenTable = source.tokenTable;
	this->capacity = source.capacity;
	this->length = source.length;
	this->current = source.current;

	return *this;
}

Long Scanner::Read(string pathFileName, int textMode) {
	ifstream fileStream;

	ListToken listToken;

	string rowString;
	string contentsInParentheses;
	string contentsString;

	size_t parenthesesBegin;
	size_t parenthesesEnd;
	size_t strOffset = 0;
	size_t strTotalLength = 0;
	size_t strCurrentLength = 0;
	size_t fileLength;

	char row[2560];

	this->tokenTable.Clear();
	this->tokenTable.Ready(this->capacity);
	this->length = 0;
	this->current = -1;

	fileStream.open(pathFileName);
	if (fileStream.good()) {
		fileStream.seekg(0, ios::end);
		fileLength = fileStream.tellg();
		fileStream.seekg(0, ios::beg);

		while (!fileStream.eof() && fileLength > 0) {
			// 1. 줄을 읽는다.
			fileStream.getline(row, sizeof(row));

			rowString = row;

			if (textMode == ListToken::LENGTH) {
				// 2. 줄의 총 길이를 구한다.
				parenthesesBegin = rowString.find('[');
				parenthesesEnd = rowString.find(']', parenthesesBegin);

				contentsInParentheses = rowString.substr(parenthesesBegin + 1, parenthesesEnd - (parenthesesBegin + 1));

				strTotalLength = stoi(contentsInParentheses);

				// 3. 전체 문자열을 구한다.
				strOffset = parenthesesEnd + 1;
			}
			strCurrentLength = rowString.length() - strOffset;

			// 현재 읽은 줄의 길이를 구한다.
			contentsString = rowString.substr(strOffset, strCurrentLength);

			// 줄의 총 길이보다 작은동안 반복한다.
			while (strCurrentLength < strTotalLength) {
				// 개행문자를 추가한다.
				contentsString += '\n';

				// 줄을 읽는다.
				fileStream.getline(row, sizeof(row));
				contentsString += row;

				// 현재 읽은 줄의 길이를 구한다.
				strCurrentLength = contentsString.length();
			}

			//listToken.Repair(textMode);
			listToken = ListToken(contentsString, textMode);

			// 2. 토큰들을 만든다.
			if (this->length < this->capacity) {
				this->tokenTable.Store(this->length, listToken);
			}
			else {
				this->tokenTable.AppendFromRear(listToken);
				this->capacity++;
			}
			this->length++;
		}
		this->current = 0;
	}
	fileStream.close();

	return this->length;
}

Token& Scanner::Scan() const {
	if (const_cast<Scanner*>(this)->tokenTable.GetAt(this->current).IsNext() != true) {
		const_cast<Scanner*>(this)->current++;
	}
	Token& token = const_cast<Scanner*>(this)->tokenTable.GetAt(this->current).Scan();

	return token;
}

void Scanner::Scan(Long index, string*(*strTokens), Long* count) {
	Long i = 0;

	ListToken& listToken = this->tokenTable.GetAt(index);

	*strTokens = new string[listToken.GetLength()];
	*count = 0;
	while (i < listToken.GetLength()) {
		(*strTokens)[i] = listToken.GetAt(i);
		(*count)++;

		i++;
	}
}

#if 0
int main(int argc, char* argv[]) {
	Scanner scanner;

	string printing;

	Long i = 0;
	Long j;
	bool isTokenListScaning;
	bool isTokenScanning;

	scanner.Read("C:\\Users\\jeong\\AppData\\Local\\Parkcom\\ParkcomMessenger\\Profiles\\alice@hotmail.com\\PersonalProfile.txt", ListToken::LENGTH);
	isTokenListScaning = scanner.IsTokenScan(i, 0);
	while (isTokenListScaning == true) {
		j = 0;
		isTokenScanning = scanner.IsTokenScan(i, j);
		while (isTokenScanning == true) {
			printing = scanner.Scan();

			printf("%s\n", printing.c_str());

			j++;
			isTokenScanning = scanner.IsTokenScan(i, j);
		}
		i++;
		isTokenListScaning = scanner.IsTokenScan(i, 0);
	}

	return 0;
}
#endif