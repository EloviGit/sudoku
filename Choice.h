#pragma once
#include "common.h"
#define ALL_CHOICE 511
class Choice
{
	int mask=ALL_CHOICE;

public:

	Choice(int number = 0);

	/*
	* whether the choice is unique;
	* if it is, return the choice;
	* else, return -1;
	*/
	int isUnique();

	/*
	* whether the choice is available;
	*/
	bool has(int number);

	/*
	* set the choice into the value
	*/
	void set(int number);

	/*
	* eliminate a choice; if eliminated, return true;
	*/
	bool eliminate(int number);

	int getMask();

	/*
	* merge the choices
	*/
	Choice operator|(Choice other);
};

