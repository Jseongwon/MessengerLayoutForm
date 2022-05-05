// Kategori.h
#ifndef _KATEGORI_H
#define _KATEGORI_H
#include <string>
using namespace std;

namespace parkcom {
	class DrawingGenerator;
	class Kategori {
	public:
		enum { NORMAL = 0, SPECIAL = 1 };
	public:
		Kategori();
		Kategori(string name);
		Kategori(const Kategori& source);
		virtual ~Kategori() = 0;
		Kategori& operator=(const Kategori& source);

		string& GetName() const;

		virtual void Accept(DrawingGenerator* drawingGenerator) = 0;
		virtual Kategori* Clone() = 0;

	protected:
		string name;
	};
	inline string& Kategori::GetName() const {
		return const_cast<string&>(this->name);
	}
}

#endif // _KATEGORI_H