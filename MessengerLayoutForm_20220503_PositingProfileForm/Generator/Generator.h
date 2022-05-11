// Generator.h
#ifndef _GENERATOR_H
#define _GENERATOR_H
typedef signed long int Long;

namespace parkcom {
	class MenuCard;
	class SubMenuCard;
	class PostingProfile;
	class PostingHeaderProfile;
	class PostingBodyProfile;
	class PostingCommentProfile;
	class PersonalProfile;
	class FriendProfile;
	class ChatProfile;
	class SystemChatProfileState;
	class OneChatProfileState;
	class OtherChatProfileState;
	class Bodys;
	class ChatBodys;
	class Generator {
	public:
		Generator();
		virtual ~Generator() = 0;

		virtual void SetPosition(int x, int y) {  }

		virtual Long GetYPosition() const { return 0; }

		virtual void Visit(MenuCard* menuCard) {  }
		virtual void Visit(SubMenuCard* subMenuCard) {  }
		
		virtual void Visit(PostingProfile* postingProfile) {  }
		virtual void Visit(PostingHeaderProfile* postingHeaderProfile) {  }
		virtual void Visit(PostingBodyProfile* postingBodyProfile) {  }
		virtual void Visit(PostingCommentProfile* postingCommentProfile) {  }

		virtual void Visit(PersonalProfile* personalProfile) {  }
		virtual void Visit(FriendProfile* friebdProfile) {  }

		virtual void Visit(ChatProfile* chatProfile) {  }
		virtual void Visit(SystemChatProfileState* systemChatProfileState) {  }
		virtual void Visit(OneChatProfileState* oneChatProfileState) {  }
		virtual void Visit(OtherChatProfileState* otherChatProfileState) {  }

		virtual void Visit(Bodys* friendBodys) {  }
	};
}

#endif // _GENERATOR_H