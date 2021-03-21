#include "Cell.h"
#include "common.h"

void Cell::fill(int number) {
	filled = true;
	value = number;
	choice.set(number);
}

bool Cell::isFilled() { return filled; }

int Cell::getValue() { return value; }

Position Cell::getPosition() { return position; }

std::string Cell::toString() {
	if (filled) {
		return "  " + std::to_string(value) + "  ";
	}
	else {
		std::stringstream s;
		s << " " << std::oct << std::setw(3) << std::setfill('0') << choice.getMask() << " ";
		return s.str();
	}
}