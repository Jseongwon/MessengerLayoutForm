// UserProfileCompileMode.h
#ifndef _USERPROFILECOMPILEMODE_H
#define _USERPROFILECOMPILEMODE_H
#include "ProfileCompileMode.h"

namespace parkcom {
	class UserProfileCompileMode : public ProfileCompileMode {
	public:
		UserProfileCompileMode(ProfileCompiler* profileCompiler = 0);
		virtual ~UserProfileCompileMode();

		virtual void Compile();
	};

}

#endif // _USERPROFILECOMPILEMODE_H