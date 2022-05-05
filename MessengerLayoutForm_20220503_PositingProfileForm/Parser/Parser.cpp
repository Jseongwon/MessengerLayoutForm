// Parser.cpp
/*
���ϸ�Ī : Parser.cpp
��    �� : �ļ� Ŭ������ �����Ѵ�.
�� �� �� : ������
�ۼ����� : 2022.03.31
����!
�������� ����� ������ ������ �� �ӽ� �������� �������� �ʰ�, �ٷ� Scanȣ��� �Ųٷ� �����͵��� ���Ե�.
L-Value�� ó�� ������ �����ݷ��� ���� ������ ó������ ó���Ѵ�. �׷��⿡ �����͵��� ������ �������� ù��° Scan �����͸� �����Ѵ�.
*/
#include "Parser.h"
#include "../Profiles/PostingProfile.h"
#include "../Profiles/PostingHeaderProfile.h"
#include "../Profiles/PostingBodyProfile.h"
#include "../Profiles/PostingCommentProfile.h"
#include "../Profiles/UserProfile.h"
#include "../Profiles/PersonalProfile.h"
#include "../Profiles/FriendProfile.h"
#include "../Profiles/ChatProfile.h"
#include "../Scanner/Scanner.h"
using namespace parkcom;

Parser::Parser() {

}

Parser::~Parser() {

}

PostingProfile* Parser::ParseByPostingProfile(Scanner* scanner) {
	PostingProfile* postingProfile;

	string kategori = scanner->Scan();
	string title = scanner->Scan();
	string commentCount = scanner->Scan();
	string writer = scanner->Scan();
	string writedAt = scanner->Scan();
	string views = scanner->Scan();

	postingProfile = PostingProfile::Builder().Kategori(kategori)
		->Title(title)
		->CommentCount(commentCount)
		->Writer(writer)
		->WritedAt(writedAt)
		->Views(views)->Build();

	return postingProfile;
}

PostingProfile* Parser::ParseByPostingProfile(Scanner* scanner, int scanningIndex) {
	PostingProfile* postingProfile;
	string(*postingProfileTokens);
	Long postingProfileTokenCount;

	scanner->Scan(scanningIndex, &postingProfileTokens, &postingProfileTokenCount);

	postingProfile = PostingProfile::Builder().Kategori(postingProfileTokens[0])
		->Title(postingProfileTokens[1])
		->CommentCount(postingProfileTokens[2])
		->Writer(postingProfileTokens[3])
		->WritedAt(postingProfileTokens[4])
		->Views(postingProfileTokens[5])->Build();

	if (postingProfileTokens != 0) {
		delete[] postingProfileTokens;
	}

	return postingProfile;
}

PostingHeaderProfile* Parser::ParseByPostingHeaderProfile(Scanner* scanner) {
	PostingHeaderProfile* postingHeaderProfile;

	string kategori = scanner->Scan();
	string title = scanner->Scan();
	string attachmentImageUrl = scanner->Scan();
	string writer = scanner->Scan();
	string writerGrade = scanner->Scan();
	string writedAt = scanner->Scan();
	string views = scanner->Scan();

	postingHeaderProfile = PostingHeaderProfile::Builder().Kategori(kategori)
		->Title(title)
		->AttachmentImageUrl(attachmentImageUrl)
		->Writer(writer)
		->WriterGrade(writerGrade)
		->WritedAt(writedAt)
		->Views(views)->Build();

	return postingHeaderProfile;
}

PostingBodyProfile* Parser::ParseByPostingBodyProfile(Scanner* scanner) {
	PostingBodyProfile* postingBodyProfile;
	postingBodyProfile = new PostingBodyProfile(scanner->Scan());
	return postingBodyProfile;
}

PostingCommentProfile* Parser::ParseByPostingCommentProfile(Scanner* scanner) {
	PostingCommentProfile* postingCommentProfile;

	string attachmentImageUrl = scanner->Scan();
	string writer = scanner->Scan();
	string comment = scanner->Scan();
	string writedAt = scanner->Scan();

	postingCommentProfile = PostingCommentProfile::Builder().AttachmentImageUrl(attachmentImageUrl)
		->Writer(writer)
		->Comment(comment)
		->WritedAt(writedAt)->Build();

	return postingCommentProfile;
}

UserProfile* Parser::ParseByUserProfile(Scanner* scanner) {
	UserProfile* userProfile;

	string accountName = scanner->Scan();
	string personalName = scanner->Scan();
	string nickname = scanner->Scan();
	string attachmentImageUrl = scanner->Scan();

	userProfile = UserProfile::Builder().AccountName(accountName)
		->PersonalName(personalName)
		->Nickname(nickname)
		->AttachmentImageUrl(attachmentImageUrl)->Build();

	return userProfile;
}

PersonalProfile* Parser::ParseByPersonalProfile(Scanner* scanner) {
	PersonalProfile* personalProfile;

	string accountName = scanner->Scan();
	string password = scanner->Scan();
	string personalName = scanner->Scan();
	string nickname = scanner->Scan();
	string attachmentImageUrl = scanner->Scan();
	string stateMessage = scanner->Scan();
	Long addedLength = atoi(((string)scanner->Scan()).c_str());

	personalProfile = PersonalProfile::Builder().AccountName(accountName)
		->Password(password)
		->PersonalName(personalName)
		->Nickname(nickname)
		->AttachmentImageUrl(attachmentImageUrl)
		->StateMessage(stateMessage)
		->AddedLength(addedLength)->Build();

	return personalProfile;
}

FriendProfile* Parser::ParseByFriendProfile(Scanner* scanner) {
	FriendProfile* friendProfile;

	string accountName = scanner->Scan();
	string personalName = scanner->Scan();
	string nickname = scanner->Scan();
	string attachmentImageUrl = scanner->Scan();
	string stateMessage = scanner->Scan();
	string addedAt = scanner->Scan();
	string roomID = scanner->Scan();
	string lastChatMember = scanner->Scan(); 
	string lastChatLogID = scanner->Scan();
	string messageType = scanner->Scan();
	string lastMessage = scanner->Scan();
	string lastUpdateAt = scanner->Scan();
	string unreadCount = scanner->Scan();

	friendProfile = FriendProfile::Builder().AccountName(accountName)
		->PersonalName(personalName)
		->Nickname(nickname)
		->AttachmentImageUrl(attachmentImageUrl)
		->StateMessage(stateMessage)
		->AddedAt(addedAt)
		->RoomID(roomID)
		->LastChatMember(lastChatMember)
		->LastChatLogID(lastChatLogID)
		->MessageType(messageType)
		->LastMessage(lastMessage)
		->LastUpdateAt(lastUpdateAt)
		->UnreadCount(unreadCount)->Build();

	return friendProfile;
}

ChatProfile* Parser::ParseByChatProfile(Scanner* scanner, UserProfile* userProfile) {
	ChatProfile* chatProfile;

	string accountName = scanner->Scan();
	string message = scanner->Scan();
	string sentAt = scanner->Scan();

	chatProfile = ChatProfile::Builder(userProfile->GetPersonalName(), userProfile->GetAttachmentImageUrl()).AccountName(accountName)
		->Message(message)
		->SentAt(sentAt)->Build();

	return chatProfile;
}

ChatProfile* Parser::ParseByChatProfile(Scanner* scanner, UserProfile* userProfile, int scanningIndex) {
	ChatProfile* chatProfile;
	string(*chatProfileTokens);
	Long chatProfileTokenCount;

	scanner->Scan(scanningIndex, &chatProfileTokens, &chatProfileTokenCount);

	chatProfile = ChatProfile::Builder(userProfile->GetPersonalName(), userProfile->GetAttachmentImageUrl()).AccountName(chatProfileTokens[0])
		->Message(chatProfileTokens[1])
		->SentAt(chatProfileTokens[2])->Build();

	if (chatProfileTokens != 0) {
		delete[] chatProfileTokens;
	}

	return chatProfile;
}