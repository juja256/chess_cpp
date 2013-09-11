#include "figures.h"

Figure::Figure(u_int x_, u_int y_, Colors c_) : x(x_), y(y_), color(c_), captured(false) {}

Figure::~Figure() {}

int Figure::get_x() { return x; }

int Figure::get_y() { return y; }

bool Figure::isCaptured() { return captured; }