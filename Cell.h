#pragma once
#include "common.h"
#include "classes.h"
class Cell
{
	Position position;
	bool filled = false;
	int value = 0;

public:
	Choice choice;
	bool trivial_solve_eliminate_done = false;

	Cell(int row = 0, int col = 0, int number = 0) : position(row, col), choice(number) {
		if (number != 0) {
			filled = true;
			value = number;
		}
	}

	void fill(int number);

	bool isFilled();

	int getValue();

	Position getPosition();

	std::string toString();
};

