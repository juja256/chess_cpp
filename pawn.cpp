#include "figures.h"

Pawn::Pawn(u_int x_, u_int y_, Colors c) : base(x_, y_, c) {}

int Pawn::Step(u_int x_, u_int y_) {
	int len = abs(y_ - this.y);
	if ( (len <= 2) && (len>0) ) {
		this.y = y_;
		return STEP_SUCCES;
	}
	return IMPOSSIBLE_STEP;
}

int Pawn::Capture(Figure& f) {
	if (f.color != this.color) {
		if (this.color == Colors.White) 
			if ( (abs(f.x - this.x) == 1) && (f.y - this.y == 1) ) {
				this.x = f.x;
				this.y = f.y;
				f.captured = true;
				return STEP_SUCCES;
			}
			else
				return IMPOSSIBLE_STEP;
		else {
			if ( (abs(f.x - this.x) == 1) && (f.y - this.y == -1) ) {
				this.x = f.x;
				this.y = f.y;
				f.captured = true;
				return STEP_SUCCES;
			}
			else 
				return IMPOSSIBLE_STEP;
		}
	}
	return IMPOSSIBLE_STEP;
}