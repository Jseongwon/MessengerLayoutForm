// PostingProfileStyle.h
#ifndef _POSTINGPROFILESTYLE_H
#define _POSTINGPROFILESTYLE_H
#include "ProfileStyle.h"

namespace parkcom {
	class PostingProfileStyle : public ProfileStyle {
	public:
		PostingProfileStyle(CWnd* pCurrentWnd = 0);
		virtual ~PostingProfileStyle();

		virtual void OnDraw(CDC* pDC);

		virtual void SpecialPosting(bool isSpecialPosting);
		virtual bool IsSpecialPosting();

	private:
		bool isSpecialPosting;
	};
	inline void PostingProfileStyle::SpecialPosting(bool isSpecialPosting) {
		this->isSpecialPosting = isSpecialPosting;
	}
	inline bool PostingProfileStyle::IsSpecialPosting() {
		return this->isSpecialPosting;
	}
}

#endif // _POSTINGPROFILESTYLE_H