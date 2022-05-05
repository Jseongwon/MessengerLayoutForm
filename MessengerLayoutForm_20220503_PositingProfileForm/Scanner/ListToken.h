// ListToken.h
#ifndef _LISTTOKEN_H
#define _LISTTOKEN_H
#include "../Utilities/Array.h"
#include "Token.h"

namespace parkcom {
	class TextMode;
	class ListToken {
		friend class DefaultTextMode;
		friend class LengthTextMode;

	public:
		enum { COMPILATIONERROR = -1, DEFAULT = 0, LENGTH = 1 };
	public:
		ListToken(Long capacity = 8);
		ListToken(string tokens, int textMode, Long capacity = 8);
		ListToken(const ListToken& source);
		~ListToken();
		ListToken& operator=(const ListToken& source);
		operator string();

		Long Scanning(string tokens);
		void Repair(int textMode);
		void Repair(string textMode);
		
		Token& Scan() const;
		Token& GetAt(Long index) const;
		Long GetCapacity() const;
		Long GetLength() const;
		Long GetCurrent() const;

		TextMode* GetTextMode() const;

		bool IsTokenScan(Long current);
		bool IsNext() const;
		bool IsEOF() const;

	private:
		Array<Token> tokens;
		Long capacity;
		Long length;
		Long current;

		TextMode* textMode;
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
	inline TextMode* ListToken::GetTextMode() const {
		return const_cast<TextMode*>(this->textMode);
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