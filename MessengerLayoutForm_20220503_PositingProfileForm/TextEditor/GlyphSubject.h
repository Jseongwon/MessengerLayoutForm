#ifndef _GLYPHSUBJECT_H
#define _GLYPHSUBJECT_H

#include "../Utilities/Array.h"

typedef signed long int Long;
class GlyphObserver;

class GlyphSubject {
public:
	GlyphSubject(Long capacity = 256);
	GlyphSubject(const GlyphSubject& source);
	virtual ~GlyphSubject();
	GlyphSubject& operator=(const GlyphSubject& source);

	virtual Long AttachObserver(GlyphObserver *glyphObserver);
	virtual Long DetachObserver(GlyphObserver *glyphObserver);
	virtual void Notify();
	GlyphObserver* GetAt(Long index);

	Long GetCapacity() const;
	Long GetLength() const;
private:
	Array<GlyphObserver*> glyphObservers;
	Long capacity;
	Long length;
};

inline Long GlyphSubject::GetCapacity() const {
	return this->capacity;
}

inline Long GlyphSubject::GetLength() const {
	return this->length;
}

int CompareObserverLinks(void *one, void *other);

#endif //_GLYPHSUBJECT_H