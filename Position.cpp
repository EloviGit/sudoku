#include "Position.h"

std::string Position::toString() {
	return "(" + std::to_string(row) + ", " + std::to_string(col) + ")";
}

std::string Positions::toString() {
	std::stringstream s;
	for (int i = 0; i < 9; i++) {
		s << positions[i].toString() << "; ";
	}
	return s.str();
}

Position Positions::get(int i) {
	return positions[i];
}

void Positions::set(int i, int r, int c){
	positions[i].row = r;
	positions[i].col = c;
}

Block::Block(int r, int c) {
	brow = (int)(r/3);
	bcol = (int)(c/3);
	int count = 0;
	for (int srow = 0; srow < 3; srow++) {
		for (int scol = 0; scol < 3; scol++) {
			set(count, brow * 3 + srow, bcol * 3 + scol);
			count++;
		}
	}
}

Row::Row(int rr) {
	rrow = rr;
	for (int col = 0; col < 9; col++) {
		set(col, rrow, col);
	}
}

Column::Column(int cc) {
	ccol = cc;
	for (int row = 0; row < 9; row++) {
		set(row, row, ccol);
	}
}