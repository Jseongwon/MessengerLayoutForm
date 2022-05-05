// PostingBodyProfile.h
#ifndef _POSTINGBODYPROFILE_H
#define _POSTINGBODYPROFILE_H
#include "Profile.h"

namespace parkcom {
	class PostingBodyProfile : public Profile {
	public:
		PostingBodyProfile();
		PostingBodyProfile(string contents);
		PostingBodyProfile(const PostingBodyProfile& source);
		virtual ~PostingBodyProfile();
		PostingBodyProfile& operator=(const PostingBodyProfile& source);

		virtual void Accept(DrawingGenerator* drawingGenerator);
		virtual Profile* Clone();

		virtual string GetContents();

	private:
		string contents;
	};
	inline string PostingBodyProfile::GetContents() {
		return this->contents;
	}
}

#endif // _POSTINGHEADERPROFILE_H