#include "figures.h"

Rock::Rock(u_int x_, u_int y_, Colors c) : base(x_, y_, c) {}

int Rock::Step(u_int x_, u_int y_) {
	if ( ( (abs(this.x - x_) < 8) && (this.y == y_) ) ||
		( (abs(this.y - y_) < 8) && (this.x == x_) ) ) {
		this.x = x_;
		this.y = y_;
		return STEP_SUCCES;
	}
	return IMPOSSIBLE_STEP;
}

int Rock::Capture(Figure& f) {
	if (f.color != this.color) {
		int step = Step(f.x, f.y);
		if (step == STEP_SUCCES) {
			f.captured = true;
		}
		return step;
	}
	return IMPOSSIBLE_STEP;
}