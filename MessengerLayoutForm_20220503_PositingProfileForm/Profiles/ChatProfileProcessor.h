// ChatProfileProcessor.h
#ifndef _CHATPROFILEPROCESSOR_H
#define _CHATPROFILEPROCESSOR_H
typedef signed long int Long;

namespace parkcom {
	class Profile;
	class Scanner;
	class Parser;
	class ChatProfileProcessor {
	public:
		ChatProfileProcessor(Scanner* scanner, Parser* parser);
		~ChatProfileProcessor();

		Profile* MakingChatProfile();

		Long GetTotalChatProfileHeight() const;

	private:
		Long totalChatProfileHeight;
	};
	inline Long ChatProfileProcessor::GetTotalChatProfileHeight() const {
		return this->totalChatProfileHeight;
	}
}

#endif // _CHATPROFILEPROCESSOR_H