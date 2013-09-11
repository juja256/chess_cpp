#ifndef FIELD_H
#define FIELD_H

#define EMPTY_CELL -1
#define PUT_FIGURE(x, y, name, color) (f[(x)][(y)] = Cell(new (name)( (y), (x), (color) )))

#include "common.h"
#include "figures.h"

class Cell {
	private:
		bool empty;
		Figure* f;
	public:
		Cell();
		Cell(Figure*);
		bool isEmpty();
		int Remove();
};

class Field {
	private:
		Cell f[8][8];
		void Setup();
	public:
		Field();
		int Move(u_int, u_int, u_int, u_int);
};

#endif