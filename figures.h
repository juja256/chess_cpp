#ifndef FIGURES_H
#define FIGURES_H

#define STEP_SUCCES 0
#define IMPOSSIBLE_STEP -1

#include "common.h"
#include "field.h"

class Figure {
	protected:
		u_int x,y;
		bool captured;
		Colors color;
		Field* field;
	public:
		Figure(u_int x_, u_int y_, Colors c_);
		virtual ~Figure();
		int get_x();
		int get_y();
		bool isCaptured();
		virtual int Step(u_int, u_int) =0;
		virtual int Capture(Figure& f) =0; 
};

class Pawn : public Figure {
	public:
		Pawn(u_int x_, u_int y_, Colors c);
		int Step(u_int x_, u_int y_);
		int Capture(Figure& f);
};

//Hell yeah!!1 Rock_n_Roll
class Rock : public Figure {
	public:
		Rock(u_int x_, u_int y_, Colors c);
		int Step(u_int x_, u_int y_);
		int Capture(Figure& f);
};

class Knight : public Figure {
	public:
		Knight(u_int x_, u_int y_, Colors c);
		int Step(u_int x_, u_int y_);
		int Capture(Figure& f);
};

class Bishop : public Figure {
	public:
		Bishop(u_int x_, u_int y_, Colors c);
		int Step(u_int x_, u_int y_);
		int Capture(Figure& f);
};

#endif