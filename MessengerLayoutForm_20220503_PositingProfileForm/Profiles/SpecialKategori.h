// SpecialKategori.h
#ifndef _SPECIALKATEGORI_H
#define _SPECIALKATEGORI_H
#include "Kategori.h"

namespace parkcom {
	class SpecialKategori : public Kategori {
	public:
		SpecialKategori();
		SpecialKategori(string name);
		SpecialKategori(const SpecialKategori& source);
		virtual ~SpecialKategori();
		SpecialKategori& operator=(const SpecialKategori& source);

		virtual Kategori* Clone();
	};
}

#endif // _SPECIALKATEGORI_H