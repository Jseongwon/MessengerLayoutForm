#include "GlyphSubject.h"
#include "CaretController.h"

GlyphSubject::GlyphSubject(Long capacity)
	: glyphObservers(capacity) {
	this->capacity = capacity;
	this->length = 0;
}

GlyphSubject::GlyphSubject(const GlyphSubject& source)
	: glyphObservers(source.glyphObservers) {
	GlyphObserver *glyphObserver;
	Long i = 0;
	while (i < source.length) {
		glyphObserver = (const_cast<GlyphSubject&>(source)).glyphObservers[i];
		if (dynamic_cast<CaretController*>(glyphObserver)) {
			glyphObserver = new CaretController(*(dynamic_cast<CaretController*>(glyphObserver)));
		}
		this->glyphObservers.Modify(i, glyphObserver);
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
}

GlyphSubject::~GlyphSubject() {
	Long i = 0;
	while (i < this->length) {
		delete this->glyphObservers[i];
		i++;
	}
}

GlyphSubject& GlyphSubject::operator=(const GlyphSubject& source) {
	Long i = 0;
	while (i < this->length) {
		delete this->glyphObservers[i];
		i++;
	}
	GlyphObserver* glyphObserver;
	this->glyphObservers = source.glyphObservers;
	this->capacity = source.capacity;
	i = 0;
	while (i < source.length) {
		glyphObserver = (const_cast<GlyphSubject&>(source)).glyphObservers.GetAt(i);
		if (dynamic_cast<CaretController*>(glyphObserver)) {
			glyphObserver = new CaretController(*(dynamic_cast<CaretController*>(glyphObserver)));
		}
		this->glyphObservers.Modify(i, glyphObserver);
		i++;
	}
	this->length = source.length;

	return *this;
}

Long GlyphSubject::AttachObserver(GlyphObserver *glyphObserver) {
	Long index;
	if (this->length < this->capacity) {
		index = this->glyphObservers.Store(this->length, glyphObserver);
	}
	else {
		index = this->glyphObservers.AppendFromRear(glyphObserver);
		this->capacity++;
	}
	this->length++;

	return index;
}

Long GlyphSubject::DetachObserver(GlyphObserver *glyphObserver) {
	Long index = this->glyphObservers.LinearSearchUnique(glyphObserver, CompareObserverLinks);
	if (index >= 0) {
		index = this->glyphObservers.Delete(index);
		this->capacity--;
		this->length--;
	}

	return index;
}

void GlyphSubject::Notify() {
	Long i = 0;
	while (i < this->length) {
		this->glyphObservers.GetAt(i)->Update();
		i++;
	}
}

GlyphObserver* GlyphSubject::GetAt(Long index) {
	return this->glyphObservers.GetAt(index);
}

int CompareObserverLinks(void *one, void *other) {
	GlyphObserver* *one_ = static_cast<GlyphObserver**>(one);
	int ret;

	if (*one_ < other) {
		ret = -1;
	}
	else if (*one_ == other) {
		ret = 0;
	}
	else if (*one_ > other) {
		ret = 1;
	}

	return ret;
}