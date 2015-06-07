#include "chess.h"
#include <stdlib.h>

chess::field::figure::figure(figures f_, colors c_):fig(f_),col(c_),locked(false){  }

string chess::field::figure::name(){
	string bw;
	switch (col) {
		case white:
			bw = "white";
			break;
		case black:
			bw = "black";
			break;
	}
	switch(fig) {
		case pawn:
			return bw+" pawn";
			break;
		case rook:
			return bw+" rock";
			break;
		case knight:
			return bw+" knight";
			break;
		case bishop:
			return bw+" bishop";
			break;
		case queen:
			return bw+" queen";
			break;
		case king:
			return bw+" king";
			break;
	}
    return "default";
}

chess::field::field(stringstream& os_): turn(white), os(os_) {
	for (int i=0; i<8; i++)
		for (int j=0; j<8; j++) {
			map[i][j].f = NULL;
			map[i][j].c = ((i+j)%2==0) ? black : white; // painting field
			colors cur_color = ((i == 0) || (i == 1)) ? white : black;
			if ((i == 1) || (i == 6)) {
				map[i][j].f = new figure(pawn, cur_color);
			}
			else if ((i == 0) || (i == 7)) {
				if ((j == 0) || (j == 7)) map[i][j].f = new figure(rook, cur_color);
				if ((j == 1) || (j == 6)) map[i][j].f = new figure(knight, cur_color);
				if ((j == 2) || (j == 5)) map[i][j].f = new figure(bishop, cur_color);
				if (j == 3) map[i][j].f = new figure(queen, cur_color);
				if (j == 4) map[i][j].f = new figure(king, cur_color);
			} // setting figures
		}
}

colors chess::field::get_turn() {
	return this->turn;
}

int chess::field::move(int x1, int y1, int x2, int y2) {
	if ( map[x1][y1].f == NULL ) {
        os << "Figure does not exist!\n";
		return -1;
	}
	else {
		if (turn != map[x1][y1].f->col) {
            os << "Don't touch opponent figures!\n";
			return -1;
		}
		else {
			/*switch (map[x1][y1].f->fig) {
				case pawn:
					if (map[x1][y1].f->locked) 
						if (y2) ...
			} checking... if turn is not valid throw this out with 'return -1' */ 

			if (map[x2][y2].f == NULL) {
				map[x2][y2].f = map[x1][y1].f;
				map[x1][y1].f = NULL;
				return 0;
			} // if destination is empy cell

			if (map[x2][y2].f->col == map[x1][y1].f->col) {
                os << "Invalid turn!\n";
				return -1;
			} // if same-color figures

			else {
				delete map[x2][y2].f;
				map[x2][y2].f = map[x1][y1].f;
				map[x1][y1].f = NULL;
				return 0;
			} // capturing figure
		}
		
	}
}

void chess::field::render() {
	for (int i=7; i>=0; i--) {
		for (int j=0; j<8; j++) {
			string cell_col = (map[i][j].c == black) ? "\x1b[40m" : "\x1b[47m";
			os << "|" << cell_col;
			if (map[i][j].f == NULL) os << "  ";
			else {
				string c;
				colors cur_color = map[i][j].f->col;
				switch (cur_color) {
					case black:
						c ="\x1b[34;1m";
						break;
					case white:
						c ="\x1b[35;1m";
						break;
				}
				os << c;
				switch (map[i][j].f->fig) {
					case pawn:
						os <<"P ";
						break;
					case rook:
						os <<"R ";
						break;
					case knight:
						os <<"K ";
						break;
					case bishop:
						os <<"B ";
						break;
					case queen:
						os <<"Q ";
						break;
					case king:
						os <<"K ";
						break;
				}
				os << "\x1b[0m";
			}
			os<<"\x1b[0m";
		}
		os<<"|\x1b[0m"<<i+1<<"\n";
	}
	os<<" a  b  c  d  e  f  g  f  \n";
}

void chess::field::change_turn() {
    if (this->turn == black) this->turn = white;
    else this->turn = black;
}

chess::chess(stringstream& os_):os(os_) {
	f = new field(os);
}

int chess::move(string c, colors player) {
	stringstream ss(c);
	string a,b;
	ss >> a;
	ss >> b;
    if (player != this->f->get_turn()) {
        os << "Not your turn!\n";
		return -1;
	}
	if (a.size()!=2 || b.size()!=2) { 
        os << "Unexpected sequence!\n";
		return -1; 
	}
	else {
		int y1 = (int)a[0] - 97;
		int y2 = (int)b[0] - 97;
		int x1 = (int)a[1] - 49;
		int x2 = (int)b[1] - 49;
		int a = f->move(x1, y1, x2, y2);
		if (a==0) {
			f->change_turn();
			return 0;
		}
		else {
            os << "Try again.\n";
			return -1;
		}
	}
}

void chess::render() {
	f->render();
}

void chess::start() {
	os<<"Hello! \nChess The game. \nPurple turns firstly. \nMove example: a1 a3\n";
	f->render();
}
