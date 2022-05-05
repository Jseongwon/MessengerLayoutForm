// DrawingGenerator.h
#ifndef _DRAWINGGENERATOR_H
#define _DRAWINGGENERATOR_H
#include <afxwin.h>
#include "Generator.h"

namespace parkcom {
	class DrawingGenerator : public Generator {
	public:
		DrawingGenerator();
		DrawingGenerator(CWnd* pCurrentWnd, CDC* pDC, COLORREF backgroundColor, COLORREF selectedBackgroundColor = RGB(255, 255, 255),
			COLORREF textColor = RGB(0, 0, 0), COLORREF selectedTextColor = RGB(0, 0, 0));
		DrawingGenerator(const DrawingGenerator& source);
		virtual ~DrawingGenerator();
		DrawingGenerator& operator=(const DrawingGenerator& source);

		virtual void SetPosition(int x, int y);

		virtual Long GetYPosition() const;

		virtual void Visit(MenuCard* menuCard);
		virtual void Visit(SubMenuCard* subMenuCard);

		virtual void Visit(PostingProfile* postingProfile);
		virtual void Visit(PostingHeaderProfile* postingHeaderProfile);
		virtual void Visit(PostingBodyProfile* postingBodyProfile);
		virtual void Visit(PostingCommentProfile* postingCommentProfile);

		virtual void Visit(NormalKategori* normalKategori);
		virtual void Visit(SpecialKategori* specialKategori);

		virtual void Visit(PersonalProfile* personalProfile);
		virtual void Visit(FriendProfile* friendProfile);

		virtual void Visit(ChatProfile* chatProfile);
		virtual void Visit(SystemChatProfileState* systemChatProfileState);
		virtual void Visit(OneChatProfileState* oneChatProfileState);
		virtual void Visit(OtherChatProfileState* otherChatProfileState);

		virtual void Visit(Bodys* friendBodys);

	private:
		CWnd* pCurrentWnd;
		CDC* pDC;

		COLORREF backgroundColor;
		COLORREF selectedBackgroundColor;
		COLORREF textColor;
		COLORREF selectedTextColor;

		Long x;
		Long y;
		Long width;
		Long height;
	};

	inline void DrawingGenerator::SetPosition(int x, int y) {
		this->x = x;
		this->y = y;
	}

	inline Long DrawingGenerator::GetYPosition() const {
		return this->y;
	}
}

#endif // _DRAWINGGENERATOR_H