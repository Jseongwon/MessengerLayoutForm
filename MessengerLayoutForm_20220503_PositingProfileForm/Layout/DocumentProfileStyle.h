// DocumentProfileStyle.h
#ifndef _DOCUMENTPROFILESTYLE_H
#define _DOCUMENTPROFILESTYLE_H
#include "ProfileStyle.h"

namespace parkcom {
	class DocumentProfileStyle : public ProfileStyle {
	public:
		DocumentProfileStyle(CWnd* pCurrentWnd = 0);
		virtual ~DocumentProfileStyle();

		virtual void OnDraw(CDC* pDC);

		virtual void SpecialPosting(bool isSpecialPosting);
		virtual void SetDocumentRowLength(LONG documentRowLength);

		virtual bool IsSpecialPosting();
		virtual LONG GetDocumentRowLength();
		virtual bool IsDrawing();

	private:
		LONG documentRowLength;

		bool isSpecialPosting;
	};
	inline void DocumentProfileStyle::SetDocumentRowLength(LONG documentRowLength) {
		this->documentRowLength = documentRowLength;
	}
	inline void DocumentProfileStyle::SpecialPosting(bool isSpecialPosting) {
		this->isSpecialPosting = isSpecialPosting;
	}

	inline LONG DocumentProfileStyle::GetDocumentRowLength() {
		return this->documentRowLength;
	}
	inline bool DocumentProfileStyle::IsSpecialPosting() {
		return this->isSpecialPosting;
	}
	inline bool DocumentProfileStyle::IsDrawing() {
		return this->onIsDrawing;
	}
}

#endif // _DOCUMENTPROFILESTYLE_H