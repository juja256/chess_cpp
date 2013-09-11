#include "field.h"

Cell::Cell() : f(0), empty(true) {}

Cell::Cell(Figure* f_) : f(f_), empty(false) {}

bool Cell::isEmpty() { return empty; }

int Cell::Remove() {
	if (f==0) return EMPTY_CELL;
	delete f;
	return 0;
}