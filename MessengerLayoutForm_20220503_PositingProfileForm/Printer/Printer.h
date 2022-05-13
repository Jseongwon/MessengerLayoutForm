// Printer.h
#ifndef _PRINTER_H
#define _PRINTER_H
#include <string>
using namespace std;
typedef signed long int Long;

namespace parkcom {
	class Printer {
	public:
		Printer();
		Printer(const Printer& source);
		~Printer();
		Printer& operator=(const Printer& source);

		Long Printing(string pathFileName, string contents);
		string GetAddedFieldLengthString(string contents);
		string GetAddedTableLengthString(string contents);
	};
}

#endif // _PRINTER_H