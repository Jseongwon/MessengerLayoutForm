// PostingProfileCompileMode.h
#ifndef _POSTINGPROFILECOMPILEMODE_H
#define _POSTINGPROFILECOMPILEMODE_H
#include "ProfileCompileMode.h"

namespace parkcom {
	class PostingProfileCompileMode : public ProfileCompileMode {
	public:
		PostingProfileCompileMode(ProfileCompiler* profileCompiler);
		virtual ~PostingProfileCompileMode();

		virtual void Compile();
	};
}

#endif // _POSTINGPROFILECOMPILEMODE_H