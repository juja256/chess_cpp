#ifndef CHESS_H
#define CHESS_H

#include <sstream>

enum figures { pawn, rook, knight, bishop, queen, king };
enum colors { white, black };
using namespace std;

class chess {
	stringstream& os;
	
	class field {
		struct figure {
			figures fig;
			colors col;
			bool locked;

			figure(figures, colors);
			string name();
		};

		colors turn;
		stringstream& os;
		struct cell{
			colors c;
			figure* f;
		} map[8][8];

	public:
		field(stringstream&);
		colors get_turn();
		void change_turn();
		int move(int, int, int, int);
		void render();
	} *f;

public:
	chess(stringstream& os);
    void start();
	int move(string, colors);
	void render();
};

#endif
