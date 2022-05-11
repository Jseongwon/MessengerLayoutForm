// ProfileDirector.h
#ifndef _PROFILEDIRECTOR_H
#define _PROFILEDIRECTOR_H
#include <string>
typedef signed long int Long;
using namespace std;

class CWnd;
namespace parkcom {
	class PersonalProfile;
	class ProfileDirector {
	public:
		ProfileDirector(CWnd* pCurrentWnd = 0);
		~ProfileDirector();

		void ChangedProfileLength(Long profileLength);
		void ChangedDocumentRowLength(Long documentRowLength);
		void ChangedBaseName(char(*baseName));
		void ChangedBaseIndex(Long baseIndex);
		void ChangedScrollInfo(int nSBCode, Long minimum, Long maximum, Long lineLength, Long pageLength, Long position, bool bRedraw = true);
		void ChangedScrollSize(Long totalWidth, Long totalHeight, bool bRedraw = true);
		void ChangedScrollCurrent(int nSBCode, Long scrollCurrent, bool bRedraw = true);

		string GetBaseName();
		Long GetProfileLength();
		Long GetDocumentRowLength();
		Long GetBaseIndex();
		
		bool IsSpecialPosting();
		void SpecialPosting(bool isSpecialPosting);

	protected:
		CWnd* pCurrentWnd;
	};
}

#endif // _PROFILEDIRECTOR_H