// DocumentProfileCompileMode.h
#ifndef _DOCUMENTPROFILECOMPILEMODE_H
#define _DOCUMENTPROFILECOMPILEMODE_H
#include "ProfileCompileMode.h"

namespace parkcom {
	class DocumentProfileCompileMode : public ProfileCompileMode {
	public:
		DocumentProfileCompileMode(ProfileCompiler* profileCompiler = 0);
		virtual ~DocumentProfileCompileMode();

		virtual void Compile();
	};

}

#endif // _DOCUMENTPROFILECOMPILEMODE_H