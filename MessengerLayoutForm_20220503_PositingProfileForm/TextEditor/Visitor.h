#ifndef _VISITOR_H
#define _VISITOR_H

class Note;
class Line;
class Character;
class Book;

class Visitor {
public:
	Visitor();
	virtual ~Visitor() = 0;

	virtual void Visit(Note* note) {  }
	virtual void Visit(Line* line) {  }
	virtual void Visit(Character* character) {  }
	virtual void Visit(Book* book) {  } //Not implement
};

#endif //_VISITOR_H