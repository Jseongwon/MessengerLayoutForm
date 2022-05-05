// Parser.h
#ifndef _PARSER_H
#define _PARSER_H

namespace parkcom {
	class Scanner;
	class PostingProfile;
	class PostingHeaderProfile;
	class PostingBodyProfile;
	class PostingCommentProfile;
	class UserProfile;
	class PersonalProfile;
	class FriendProfile;
	class ChatProfile;
	class Parser {
	public:
		Parser();
		~Parser();

		PostingProfile* ParseByPostingProfile(Scanner* scanner);
		PostingProfile* ParseByPostingProfile(Scanner* scanner, int scanningIndex);
		PostingHeaderProfile* ParseByPostingHeaderProfile(Scanner* scanner);
		PostingBodyProfile* ParseByPostingBodyProfile(Scanner* scanner);
		PostingCommentProfile* ParseByPostingCommentProfile(Scanner* scanner);
		UserProfile* ParseByUserProfile(Scanner* scanner);
		PersonalProfile* ParseByPersonalProfile(Scanner* scanner);
		FriendProfile* ParseByFriendProfile(Scanner* scanner);
		ChatProfile* ParseByChatProfile(Scanner* scanner, UserProfile* userProfile);
		ChatProfile* ParseByChatProfile(Scanner* scanner, UserProfile* userProfile, int scanningIndex);
	};
}

#endif // _PARSER_H