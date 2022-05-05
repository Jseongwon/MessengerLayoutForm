// DrawingCard.h
#ifndef _DRAWINGCARD_H
#define _DRAWINGCARD_H

namespace parkcom {
	class MenuImageCard;
	class DrawingCard {
	public:
		DrawingCard();
		~DrawingCard();

		void Visit(MenuImageCard* menuImageCard);
	};
}

#endif // _DRAWINGCARD_H