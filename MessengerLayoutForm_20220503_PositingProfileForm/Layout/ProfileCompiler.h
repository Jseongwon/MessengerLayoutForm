// ProfileCompiler.h
#ifndef _PROFILECOMPILER_H
#define _PROFILECOMPILER_H

class CWnd;
namespace parkcom {
	class DrawingGenerator;
	class ProfileCompileMode;
	class ProfileCompiler {
		friend class PostingProfileCompileMode;
		friend class UserProfileCompileMode;
		friend class ChatProfileCompileMode;
		friend class DocumentProfileCompileMode;
	public:
		ProfileCompiler();
		ProfileCompiler(CWnd* pCurrentWnd, DrawingGenerator* drawingGenerator);
		ProfileCompiler(const ProfileCompiler& source);
		~ProfileCompiler();
		ProfileCompiler& operator=(const ProfileCompiler& source);

		void Compile();

		void Repair(int profileCompileMode);

	private:
		CWnd* pCurrentWnd;
		DrawingGenerator* drawingGenerator;
		ProfileCompileMode* profileCompileMode;
	};
}

#endif // _PROFILECOMPILER_H