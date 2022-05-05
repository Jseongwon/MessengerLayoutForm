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

		Long Read(string pathFileName, int textMode);

		Token& Scan() const;
		// �Է� : ��ġ, ��� : ��(��)�� ��ū��, ����
		void Scan(Long index, string*(*strTokens), Long* count);

		bool IsTokenScan(Long rowCurrent, Long tokenIndex);
		bool IsNext() const;
		bool IsEOF() const;

	protected:
		Array<ListToken> tokenTable;
		Long capacity;
		Long length;
		Long current;
	};

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