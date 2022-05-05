// Bodys.h
#ifndef _BODYS_H
#define _BODYS_H
#include "Profiles.h"

namespace parkcom {
	class BodysState;
	class Bodys : public Profiles { // 친구에 대한 정보
	public:
		Bodys(Long capacity = 8);
		Bodys(const Bodys& source);
		virtual ~Bodys();
		Bodys& operator=(const Bodys& source);

		virtual void Accept(DrawingGenerator* drawingGenerator);
		virtual Profile* Clone();

		virtual int GetBodysState();
		virtual void Repair(int bodysState);

	private:
		BodysState* bodysState;
	};
}

#endif // _BODYS_H