// ChatProfileCompileMode.h
#ifndef _CHATPROFILECOMPILEMODE_H
#define _CHATPROFILECOMPILEMODE_H
#include "ProfileCompileMode.h"

namespace parkcom {
	class ChatProfileCompileMode : public ProfileCompileMode {
	public:
		ChatProfileCompileMode(ProfileCompiler* profileCompiler = 0);
		virtual ~ChatProfileCompileMode();

		virtual void Compile();
	};

}

#endif // _CHATPROFILECOMPILEMODE_H