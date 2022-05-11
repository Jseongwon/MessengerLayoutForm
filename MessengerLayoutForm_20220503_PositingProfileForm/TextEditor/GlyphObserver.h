#ifndef _GLYPHOBSERVER_H
#define _GLYPHOBSERVER_H

class GlyphObserver {
public:
	GlyphObserver();
	GlyphObserver(const GlyphObserver& source);
	virtual ~GlyphObserver() = 0;
	GlyphObserver& operator=(const GlyphObserver& source);

	virtual void Update() = 0;
};

#endif //_GLYPHOBSERVER_H