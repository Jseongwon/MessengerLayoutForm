// ListToken.h
#ifndef _LISTTOKEN_H
#define _LISTTOKEN_H
#include "../Utilities/Array.h"
#include "Token.h"

namespace parkcom {
	class ScanMode;
	class ListToken {
		friend class DefaultScanMode;
		friend class LengthScanMode;

	public:
		enum { COMPILATIONERROR = -1, DEFAULT = 0, LENGTH = 1 };
	public:
		ListToken(Long capacity = 8);
		ListToken(string tokens, int scanMode, Long capacity = 8);
		ListToken(const ListToken& source);
		~ListToken();
		ListToken& operator=(const ListToken& source);
		operator string();

		Long Scanning(string tokens);
		void Repair(int scanMode);
		void Repair(string scanMode);
		
		Token& Scan() const;
		Token& GetAt(Long index) const;
		Long GetCapacity() const;
		Long GetLength() const;
		Long GetCurrent() const;

		ScanMode* GetScanMode() const;

		bool IsTokenScan(Long current);
		bool IsNext() const;
		bool IsEOF() const;

	private:
		Array<Token> tokens;
		Long capacity;
		Long length;
		Long current;

		ScanMode* scanMode;
	};

	inline Token& ListToken::GetAt(Long index) const {
		return const_cast<Token&>(const_cast<ListToken*>(this)->tokens.GetAt(index));
	}
	inline Long ListToken::GetCapacity() const {
		return this->capacity;
	}
	inline Long ListToken::GetLength() const {
		return this->length;
	}
	inline Long ListToken::GetCurrent() const {
		return this->current;
	}
	inline ScanMode* ListToken::GetScanMode() const {
		return const_cast<ScanMode*>(this->scanMode);
	}

	inline bool ListToken::IsTokenScan(Long current) {
		return current < this->length && this->current >= 0;
	}
	inline bool ListToken::IsNext() const {
		return this->current < this->length && this->current >= 0;
	}
	inline bool ListToken::IsEOF() const {
		return this->current >= this->length || this->current < 0;
	}
}

#endif // _LISTTOKEN_H