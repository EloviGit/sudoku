#pragma once
#include "classes.h"
#include "Cell.h"
#include "EventLogger.h"
class Sudoku
{
	int data[9][9] = { 0 };
	Cell cells[9][9] = {
	{Cell(0, 0), Cell(0, 1), Cell(0, 2), Cell(0, 3), Cell(0, 4), Cell(0, 5), Cell(0, 6), Cell(0, 7), Cell(0, 8)},
	{Cell(1, 0), Cell(1, 1), Cell(1, 2), Cell(1, 3), Cell(1, 4), Cell(1, 5), Cell(1, 6), Cell(1, 7), Cell(1, 8)}, 
	{Cell(2, 0), Cell(2, 1), Cell(2, 2), Cell(2, 3), Cell(2, 4), Cell(2, 5), Cell(2, 6), Cell(2, 7), Cell(2, 8)},
	{Cell(3, 0), Cell(3, 1), Cell(3, 2), Cell(3, 3), Cell(3, 4), Cell(3, 5), Cell(3, 6), Cell(3, 7), Cell(3, 8)}, 
	{Cell(4, 0), Cell(4, 1), Cell(4, 2), Cell(4, 3), Cell(4, 4), Cell(4, 5), Cell(4, 6), Cell(4, 7), Cell(4, 8)}, 
	{Cell(5, 0), Cell(5, 1), Cell(5, 2), Cell(5, 3), Cell(5, 4), Cell(5, 5), Cell(5, 6), Cell(5, 7), Cell(5, 8)}, 
	{Cell(6, 0), Cell(6, 1), Cell(6, 2), Cell(6, 3), Cell(6, 4), Cell(6, 5), Cell(6, 6), Cell(6, 7), Cell(6, 8)}, 
	{Cell(7, 0), Cell(7, 1), Cell(7, 2), Cell(7, 3), Cell(7, 4), Cell(7, 5), Cell(7, 6), Cell(7, 7), Cell(7, 8)}, 
	{Cell(8, 0), Cell(8, 1), Cell(8, 2), Cell(8, 3), Cell(8, 4), Cell(8, 5), Cell(8, 6), Cell(8, 7), Cell(8, 8)}};
	EventLogger logger;
	bool loggerOpened;
public:
	Sudoku(int inputdata[9][9], bool openEventLogger = false);

	Cell* fetch(Position p);

	int solve();

	/*
	* trivial solve, return true if made any progress;
	* if a cell is filled, other cells of its row, col, and block should eliminate the choice
	* if a cell has unique choice, it should be filled immediately
	*/
	bool trivialSolve();

	/*
	* second solve, with more complicated logic, return true if made any progress;
	* if in a row a cell is the unique position of some choice, then it should be filled immediately
	* the same for col, blocks
	*/
	bool secondSolve();

	/*
	* third solve, with even more complicated logic, return true if made any progress;
	* think of the intersection of a row and a block:
	*	if some choice only show up in this area while not others in this row, then there must be one here, so other cells in this block should eliminate this choice
	*	if some choice only show up in this area while not others in this block, then there must be one here, so other cells in this row should eliminate this choice
	* the same for intersections of cols and blocks.
	*/
	bool thirdSolve();

	std::string toString(int mode = 1);

	bool isValid();

	void printLog();
};

