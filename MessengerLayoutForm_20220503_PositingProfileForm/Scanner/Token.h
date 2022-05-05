// Token.h
#ifndef _TOKEN_H
#define _TOKEN_H
#include <string>
using namespace std;

namespace parkcom {
	class Token {
	public:
		Token(string contents = "");
		Token(const Token& source);
		~Token();
		Token& operator=(const Token& source);
		operator const string();

		bool IsDAT();

	private:
		string contents;
	};
}

#endif // _TOKEN_H