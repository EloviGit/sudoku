#pragma once
#include "common.h"

class Position
{
	int row = 0;
	int col = 0;
	friend class Positions;

public:
	/*
	* A position of the table
	*/
	Position(int r = 0, int c = 0) : row(r), col(c) {}

	int getrow() { return row; }
	int getcol() { return col; }

	/*
	* to print the position
	*/
	std::string toString();
};

class Positions
{
public:
	Position positions[9];
	std::string toString();
	Position get(int i);
protected:
	void set(int i, int r, int c);
};

class Block : public Positions
{
	/*
	* A block of 9 positions
	*/
public:
	int brow = 0;
	int bcol = 0;
	Block(int r = 0, int c = 0);
	Block(Position p) : Block(p.getrow(), p.getcol()) {}
};

class Row : public Positions
{
	/*
	* A row of 9 positions
	*/
	int rrow = 0;
public:
	Row(int rr = 0);
	Row(Position p) : Row(p.getrow()) {}
};

class Column : public Positions
{
	/*
	* A column of 9 positions
	*/
	int ccol = 0;
public:
	Column(int cc = 0);
	Column(Position p) : Column(p.getcol()) {}
};
