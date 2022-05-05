// ProfileFactory.h
#ifndef _PROFILEBUILDER_H
#define _PROFILEBUILDER_H
#include <string>
typedef signed long int Long;
using namespace std;

namespace parkcom {
	class Profile;
	class ProfileFactory {
	public:
		ProfileFactory();
		~ProfileFactory();

		Profile* CreatePostingProfile(string kategori, string title, string commentCount, string writer, string writedAt, string views);
		Profile* CreatePersonalProfile(string accountName, string password, string personalName, string nickname, string attachmentImageUrl, string stateMessage, Long addedLength);
		Profile* CreateFriendProfile(string accountName, string personalName, string nickname, string attachmentImageUrl, string stateMessage, string addedAt, string roomID,
			string lastChatMember, string lastChatLogID, string messageType, string lastMessage, string lastUpdateAt, string unreadCount);
		Profile* CreateChatProfile(string accountName, string personalName, string attachmentImageUrl, string message, string sentAt);
		Profile* CreateBodys();
	};
}

#endif // _PROFILEBUILDER_H