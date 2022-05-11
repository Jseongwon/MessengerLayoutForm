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
		virtual void SetDocumentRowLength(LONG documentRowLength);

		virtual bool IsSpecialPosting();
		virtual LONG GetDocumentRowLength();
		virtual bool IsDrawing();

	private:
		LONG documentRowLength;

		bool isSpecialPosting;
		bool onIsDrawing;
	};
	inline void PostingProfileStyle::SetDocumentRowLength(LONG documentRowLength) {
		this->documentRowLength = documentRowLength;
	}
	inline void PostingProfileStyle::SpecialPosting(bool isSpecialPosting) {
		this->isSpecialPosting = isSpecialPosting;
	}

	inline LONG PostingProfileStyle::GetDocumentRowLength() {
		return this->documentRowLength;
	}
	inline bool PostingProfileStyle::IsSpecialPosting() {
		return this->isSpecialPosting;
	}
	inline bool PostingProfileStyle::IsDrawing() {
		return this->onIsDrawing;
	}
}

#endif // _POSTINGPROFILESTYLE_H