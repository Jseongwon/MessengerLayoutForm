// Profiles.h
#ifndef _PROFILES_H
#define _PROFILES_H
#include "../Utilities/Array.h"
#include "Profile.h"

namespace parkcom {
	class Profiles : public Profile {
	public:
		Profiles(Long capacity = 8);
		Profiles(const Profiles& source);
		virtual ~Profiles() = 0;
		Profiles& operator=(const Profiles& source);

		virtual Long Add(Profile* profile);
		virtual Long Remove(Profile* index);
		virtual Long Change(Long positionOfProfile, Long positionOfDesired);
		virtual Long Select(Long current);
		virtual Profile* GetAt(Long index);

		virtual Long Move(Long index);

		virtual Long GetCapacity() const;
		virtual Long GetLength() const;
		virtual Long GetCurrent() const;

	protected:
		Array<Profile*> profiles;
		Long capacity;
		Long length;
		Long current;
	};

	inline Long Profiles::Select(Long current) {
		this->current = current;
		return this->current;
	}

	inline Long Profiles::GetCapacity() const {
		return this->capacity;
	}
	inline Long Profiles::GetLength() const {
		return this->length;
	}
	inline Long Profiles::GetCurrent() const {
		return this->current;
	}
}

int CompareProfileLinksInProfiles(void* one, void* other);

#endif // _PROFILES_H