// Scroll.h
#ifndef _SCROLLS_H
#define _SCROLLS_H
typedef signed long int Long;

// Scroll
class Scroll {
public:
	enum { VERTICAL = 0, HORIZONTAL = 1 };

public:
	Scroll();
	Scroll(Long minimum, Long maximum, Long lineLength, Long pageLength, Long position);
	Scroll(const Scroll& source);
	virtual ~Scroll() = 0;
	Scroll& operator =(const Scroll& source);
	Long First();
	Long PreviousLine();
	Long NextLine();
	Long PreviousPage();
	Long NextPage();
	Long PreviousOneFifth();
	Long NextOneFifth();
	Long Last();
	Long Move(Long amount);
	virtual Scroll* Clone() { return 0; }

	Long GetMinimum() const;
	Long GetMaximum() const;
	Long GetLineLength() const;
	Long GetPageLength() const;
	Long GetPosition() const;

protected:
	Long minimum;
	Long maximum;
	Long lineLength;
	Long pageLength;
	Long position;
};

inline Long Scroll::GetMinimum() const {
	return this->minimum;
}
inline Long Scroll::GetMaximum() const {
	return this->maximum;
}
inline Long Scroll::GetLineLength() const {
	return this->lineLength;
}
inline Long Scroll::GetPageLength() const {
	return this->pageLength;
}
inline Long Scroll::GetPosition() const {
	return this->position;
}

// ScrollBuilder
class ScrollBuilder {
public:
	ScrollBuilder();
	ScrollBuilder(int scrollState, Long minimum, Long maximum, Long lineLength, Long pageLength, Long position);
	ScrollBuilder(const ScrollBuilder& source);
	~ScrollBuilder();
	ScrollBuilder& operator=(const ScrollBuilder& source);

	Scroll* Build();

	int GetScrollState() const;

private:
	int scrollState;
	Long minimum;
	Long maximum;
	Long lineLength;
	Long pageLength;
	Long position;
};

inline int ScrollBuilder::GetScrollState() const {
	return this->scrollState;
}

// HorizontalScroll
class HorizontalScroll : public Scroll {
public:
	HorizontalScroll();
	HorizontalScroll(Long minimum, Long maximum, Long lineLength, Long pageLength, Long position);
	HorizontalScroll(const HorizontalScroll& source);
	virtual ~HorizontalScroll();
	HorizontalScroll& operator =(const HorizontalScroll& source);
	virtual Scroll* Clone();
};

// VerticalScroll
class VerticalScroll : public Scroll {
public:
	VerticalScroll();
	VerticalScroll(Long minimum, Long maximum, Long lineLength, Long pageLength, Long position);
	VerticalScroll(const VerticalScroll& source);
	virtual ~VerticalScroll();
	VerticalScroll& operator =(const VerticalScroll& source);
	virtual Scroll* Clone();
};

#endif // _SCROLLS_H