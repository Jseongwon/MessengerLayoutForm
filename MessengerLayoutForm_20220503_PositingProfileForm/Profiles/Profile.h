// Profile.h
#ifndef _PROFILE_H
#define _PROFILE_H
#include <string>
typedef signed long int Long;
using namespace std;

namespace parkcom {
	class DrawingGenerator;
	class Kategori;
	class Profile {
	public:
		Profile();
		virtual ~Profile() = 0;

		virtual void Accept(DrawingGenerator* drawingGenerator) {  }
		virtual Profile* Clone() { return 0; }

		virtual Long Add(Profile* profile) { return -1; }
		virtual Long Remove(Profile* index) { return -1; }
		virtual Long Change(Long positionOfProfile, Long positionOfDesired) { return -1; }
		virtual Long Select(Long current) { return -1; }
		virtual Profile* GetAt(Long index) { return 0; }

		virtual Long Move(Long index) { return -1; }

		virtual void SetState(int stateType) {  }

		virtual Long GetCapacity() const { return 0; }
		virtual Long GetLength() const { return 0; }
		virtual Long GetCurrent() const { return -1; }

		virtual Kategori* GetKategori() { return 0; }
		virtual string GetTitle() { return string("Error"); }
		virtual string GetCommentCount() { return string("Error"); }
		virtual string GetWriter() { return string("Error"); }
		virtual string GetWritedAt() { return string("Error"); }
		virtual string GetViews() { return string("Error"); }

		virtual string GetAccountName() { return string("Error"); }
		virtual string GetPassword() { return string("Error"); }
		virtual string GetPersonalName() { return string("Error"); }
		virtual string GetNickname() { return string("Error"); }
		virtual string GetAttachmentImageUrl() { return string("Error"); }
		virtual string GetStateMessage() { return string("Error"); }
		virtual Long GetAddedLength() { return 0; }

		virtual string GetAddedAt() { return string("Error"); }
		virtual string GetRoomID() { return string("Error"); }
		virtual string GetLastChatMember() { return string("Error"); }
		virtual string GetLastChatLogID() { return string("Error"); }
		virtual string GetMessageType() { return string("Error"); }
		virtual string GetLastMessage() { return string("Error"); }
		virtual string GetLastUpdateAt() { return string("Error"); }
		virtual string GetUnreadCount() { return string("Error"); }

		virtual string GetCurrentMessage() { return string("Error"); }
		virtual string SentAt() { return string("Error"); }

		virtual int GetBodysState() { return 0; }
		virtual void Repair(int state) {  }
	};
}

#endif // _PROFILE_H