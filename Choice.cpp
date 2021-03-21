#include "Choice.h"

Choice::Choice(int number) {
	if (number == 10) {
		mask = 0;
	} else if (number != 0) {
		mask = (1 << (number - 1));
	}
}

int Choice::isUnique() {
	int digit = 0;
	int value = 0;
	int temp = mask;
	while (temp) {
		digit += temp & 1;
		temp >>= 1;
		if (digit > 1) break;
		value++;
	}
	if (digit == 1) {
		return value;
	}
	else {
		return -1;
	}
}

bool Choice::has(int number) {
	return (mask & (1 << (number - 1)));
}

void Choice::set(int number) {
	mask = (1 << (number - 1));
}

bool Choice::eliminate(int number) {
	if (has(number)) {
		mask ^= (1 << (number - 1));
		return true;
	}
	else {
		return false;
	}
}

int Choice::getMask() {
	return mask;
}

Choice Choice::operator|(Choice other) {
	Choice newChoice(0);
	newChoice.mask = mask | other.mask;
	return newChoice;
}