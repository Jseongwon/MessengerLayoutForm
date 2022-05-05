// ProfileCompileMode.h
#ifndef _PROFILECOMPILEMODE_H
#define _PROFILECOMPILEMODE_H

namespace parkcom {
	class ProfileCompiler;
	class ProfileCompileMode {
	public:
		enum { POSTINGPROFILE = 0, USERPROFILE = 1, CHATPROFILE = 2, DOCUMENTPROFILE = 3 };
	public:
		ProfileCompileMode(ProfileCompiler* profileCompiler = 0);
		virtual ~ProfileCompileMode() = 0;

		virtual void Compile() = 0;

	protected:
		ProfileCompiler* profileCompiler;
	};
}

#endif // _PROFILECOMPILEMODE_H