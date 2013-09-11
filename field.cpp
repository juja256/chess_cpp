#include "field.h"

void Field::Setup() {
	for (u_int i=0; i<8; i++) {
		PUT_FIGURE(1, i, Pawn, Colors.White);
		PUT_FIGURE(6, i, Pawn, Colors.Black);
		//f[1][i] = Cell(new Pawn(i, 1, Colors.White));
		//f[6][i] = Cell(new Pawn(i, 1, Colors.Black));
	}
	PUT_FIGURE(0, 1, Rock, Colors.White);
	PUT_FIGURE(0, 2, Knight, Colors.White);
	//...
}