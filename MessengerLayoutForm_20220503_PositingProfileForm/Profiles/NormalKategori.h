// NormalKategori.h
#ifndef _NORMALKATEGORI_H
#define _NORMALKATEGORI_H
#include "Kategori.h"

namespace parkcom {
	class NormalKategori : public Kategori {
	public:
		NormalKategori();
		NormalKategori(string name);
		NormalKategori(const NormalKategori& source);
		virtual ~NormalKategori();
		NormalKategori& operator=(const NormalKategori& source);

		virtual void Accept(DrawingGenerator* drawingGenerator);
		virtual Kategori* Clone();
	};
}

#endif // _NORMALKATEGORI_H