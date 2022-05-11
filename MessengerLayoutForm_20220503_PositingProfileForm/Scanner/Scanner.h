// Scanner.h
#ifndef _SCANNER_H
#define _SCANNER_H
#include "ListToken.h"

namespace parkcom {
	class Scanner {
	public:
		Scanner(Long capacity = 8);
		Scanner(const Scanner& source);
		~Scanner();
		Scanner& operator=(const Scanner& source);

		Long Read(string pathFileName, int scanMode);

		Token& Scan() const;
		// 입력 : 위치, 출력 : 줄(행)의 토큰들, 개수
		void Scan(Long index, string*(*strTokens), Long* count);

		bool IsTokenScan(Long rowCurrent, Long tokenIndex);
		bool IsNext() const;
		bool IsEOF() const;

		Long GetCapacity();
		Long GetLength();
		Long GetCurrent();

	protected:
		Array<ListToken> tokenTable;
		Long capacity;
		Long length;
		Long current;
	};

	inline Long Scanner::GetCapacity() {
		return this->capacity;
	}
	inline Long Scanner::GetLength() {
		return this->length;
	}
	inline Long Scanner::GetCurrent() {
		return this->current;
	}

	inline bool Scanner::IsTokenScan(Long rowCurrent, Long tokenIndex) {
		return this->tokenTable.GetAt(rowCurrent).IsTokenScan(tokenIndex) && this->current >= 0;
	}
	inline bool Scanner::IsNext() const {
		return this->current < this->length && this->current >= 0;
	}
	inline bool Scanner::IsEOF() const {
		return this->current >= this->length || this->current < 0;
	}
}

#endif // _SCANNER_H