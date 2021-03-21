#include "Sudoku.h"

Sudoku::Sudoku(int inputdata[9][9], bool openEventLogger) {
	for (int row = 0; row < 9; row++)
		for (int col = 0; col < 9; col++) {
			data[row][col] = inputdata[row][col];
			if (inputdata[row][col] != 0)
				cells[row][col].fill(inputdata[row][col]);
		}
	loggerOpened = openEventLogger;
}

Cell* Sudoku::fetch(Position p) {
	return &cells[p.getrow()][p.getcol()];
}

int Sudoku::solve() {
	int count;
	for (count = 0; count < 10000; count++) {
		bool progress = false;
		progress = progress || trivialSolve();
		progress = progress || secondSolve();
		progress = progress || thirdSolve();
		if (!isValid()) return -1;
		if (!progress) break;
	}
	return count;
}

bool Sudoku::trivialSolve() {
	bool progress = false;
	bool event_eliminate_row = false, event_eliminate_col = false, event_eliminate_blk = false;
	for (int row = 0; row < 9; row ++)
		for (int col = 0; col < 9; col++){
			if (cells[row][col].isFilled()) {
				Cell* cell = &cells[row][col];
				if (!cell->trivial_solve_eliminate_done) {
					int value = cell->getValue();
					Row r(cell->getPosition());
					Column c(cell->getPosition());
					Block b(cell->getPosition());
					if (loggerOpened) {
						logger.addEvent(ELIMINATE_ROW, row, col, value);
						logger.addEvent(ELIMINATE_COL, row, col, value);
						logger.addEvent(ELIMINATE_BLK, row, col, value, b.brow, b.bcol);
						cell->trivial_solve_eliminate_done = true;
					}
					for (int i = 0; i < 9; i++) {
						Cell* rcell = fetch(r.get(i)), * ccell = fetch(c.get(i)), * bcell = fetch(b.get(i));
						if (!rcell->isFilled() && rcell->choice.has(value)) {
							progress = true;
							rcell->choice.eliminate(value);
						}
						if (!ccell->isFilled() && ccell->choice.has(value)) {
							progress = true;
							ccell->choice.eliminate(value);
						}
						if (!bcell->isFilled() && bcell->choice.has(value)) {
							progress = true;
							bcell->choice.eliminate(value);
						}
				}
				}
			}
			else {
				int value = cells[row][col].choice.isUnique();
				if (value > 0) {
					if (loggerOpened) {
						logger.addEvent(FILL_CEL, row, col, value);
					}
					cells[row][col].fill(value);
					progress = true;
				}
			}
		}
	return progress;
}

bool Sudoku::secondSolve() {
	bool progress = false;
	for (int row = 0; row < 9; row++) {
		for (int number = 1; number <= 9; number++) {
			int count = 0, index = 0;
			Row r(row);
			for (int i = 0; i < 9 && count <= 1; i++) {
				Cell* cell = fetch(r.get(i));
				if (cell->isFilled() && cell->getValue() == number) {
					count = 2;
				} else if (cell->choice.has(number)) {
					count++;
					index = i;
				}
			}
			if (count == 1) {
				Cell* cell = fetch(r.get(index));
				cell->fill(number);
				progress = true;
				if (loggerOpened) {
					logger.addEvent(FILL_ROW, cell->getPosition().getrow(), cell->getPosition().getcol(), number);
				}
			}
		}
	}

	for (int col = 0; col < 9; col++) {
		for (int number = 1; number <= 9; number++) {
			int count = 0, index = 0;
			Column c(col);
			for (int i = 0; i < 9 && count <= 1; i++) {
				Cell* cell = fetch(c.get(i));
				if (cell->isFilled() && cell->getValue() == number) {
					count = 2;
				} else if (cell->choice.has(number)){
					count ++;
					index = i;
				}
			}
			if (count == 1) {
				Cell* cell = fetch(c.get(index));
				cell->fill(number);
				progress = true;
				if (loggerOpened) {
					logger.addEvent(FILL_COL, cell->getPosition().getrow(), cell->getPosition().getcol(), number);
				}
			}
		}
	}

	for (int brow = 0; brow < 3; brow++) {
		for (int bcol = 0; bcol < 3; bcol++) {
			for (int number = 1; number <= 9; number++) {
				int count = 0, index = 0;
				Block b(3 * brow, 3 * bcol);
				for (int i = 0; i < 9 && count <= 1; i++) {
					Cell* cell = fetch(b.get(i));
					if (cell->isFilled() && cell->getValue() == number) {
						count = 2;
					} else if (cell->choice.has(number)) {
						count++;
						index = i;
					}
				}
				if (count == 1) {
					Cell* cell = fetch(b.get(index));
					cell->fill(number);
					progress = true;
					if (loggerOpened) {
						logger.addEvent(FILL_BLK, cell->getPosition().getrow(), cell->getPosition().getcol(), number, b.brow, b.bcol);
					}
				}
			}
		}
	}

	return progress;
}

bool Sudoku::thirdSolve() {
	bool progress = false;
	for (int row = 0; row < 9; row++) {
		for (int bcol = 0; bcol < 3; bcol++) {
			Cell* intersectCells[3] = {&cells[row][3 * bcol], &cells[row][3 * bcol + 1], &cells[row][3 * bcol + 2]};
			Choice intersectionCellsChoice = intersectCells[0]->choice | intersectCells[1]->choice | intersectCells[2]->choice;
			Cell* otherCellsOfTheRow[6];
			Choice otherCellsOfTheRowChoice(10);
			int count = 0;
			int bcol2 = 0;
			while (count < 6) {
				if (bcol2 != bcol) {
					otherCellsOfTheRow[count] = &cells[row][3 * bcol2 + (count % 3)];
					otherCellsOfTheRowChoice = otherCellsOfTheRowChoice | otherCellsOfTheRow[count]->choice;
					if (count % 3 == 2) {
						bcol2++;
					}
					count++;
				}
				else {
					bcol2++;
				}
			}
			Cell* otherCellsOfTheBlock[6];
			Choice otherCellsOfTheBlockChoice(10);
			int brow = (int)(row / 3), srow = row % 3;
			count = 0;
			int srow2 = 0;
			while (count < 6) {
				if (srow2 != srow) {
					otherCellsOfTheBlock[count] = &cells[3 * brow + srow2][3 * bcol + (count % 3)];
					otherCellsOfTheBlockChoice = otherCellsOfTheBlockChoice | otherCellsOfTheBlock[count]->choice;
					if (count % 3 == 2) {
						srow2++;
					}
					count++;
				}
				else {
					srow2++;
				}
			}

			for (int number = 1; number <= 9; number++) {
				if (intersectionCellsChoice.has(number) && !otherCellsOfTheBlockChoice.has(number)) {
					for (int i = 0; i < 6; i++) {
						progress = progress || otherCellsOfTheRow[i]->choice.eliminate(number);
					}
				}

				if (intersectionCellsChoice.has(number) && !otherCellsOfTheRowChoice.has(number)) {
					for (int i = 0; i < 6; i++) {
						progress = progress || otherCellsOfTheBlock[i]->choice.eliminate(number);
					}
				}
			}
		}
	}

	for (int col = 0; col < 9; col++) {
		for (int brow = 0; brow < 3; brow++) {
			Cell* intersectCells[3] = { &cells[3 * brow][col], &cells[3 * brow + 1][col], &cells[3 * brow + 2][col] };
			Choice intersectionCellsChoice = intersectCells[0]->choice | intersectCells[1]->choice | intersectCells[2]->choice;
			Cell* otherCellsOfTheCol[6];
			Choice otherCellsOfTheColChoice(0);
			int count = 0;
			int brow2 = 0;
			while (count < 6) {
				if (brow2 != brow) {
					otherCellsOfTheCol[count] = &cells[3 * brow2 + (count % 3)][col];
					otherCellsOfTheColChoice = otherCellsOfTheColChoice | otherCellsOfTheCol[count]->choice;
					if (count % 3 == 2) {
						brow2++;
					}
					count++;
				}
				else {
					brow2++;
				}
			}

			Cell* otherCellsOfTheBlock[6];
			Choice otherCellsOfTheBlockChoice(0);
			int bcol = (int)(col / 3), scol = col % 3;
			count = 0;
			int scol2 = 0;
			while (count < 6) {
				if (scol2 != scol) {
					otherCellsOfTheBlock[count] = &cells[3 * brow + (count % 3)][3 * bcol + scol2];
					otherCellsOfTheBlockChoice = otherCellsOfTheBlockChoice | otherCellsOfTheBlock[count]->choice;
					if (count % 3 == 2) {
						scol2++;
					}
					count++;
				}
				else {
					scol2++;
				}
			}

			for (int number = 1; number <= 9; number++) {
				if (intersectionCellsChoice.has(number) && !otherCellsOfTheBlockChoice.has(number)) {
					for (int i = 0; i < 6; i++) {
						progress = progress || otherCellsOfTheCol[i]->choice.eliminate(number);
					}
				}

				if (intersectionCellsChoice.has(number) && !otherCellsOfTheColChoice.has(number)) {
					for (int i = 0; i < 6; i++) {
						progress = progress || otherCellsOfTheBlock[i]->choice.eliminate(number);
					}
				}
			}
		}
	}
	return progress;
}

std::string Sudoku::toString(int mode) {
	std::stringstream s;
	switch (mode)
	{
	case 0:
		s << "+---------------+---------------+---------------+";
		s << std::endl;
		for (int row = 0; row < 9; row++) {
			s << "|";
			for (int col = 0; col < 9; col++) {
				s << cells[row][col].toString();
				if (col % 3 == 2) {
					s << "|";
				}
			}
			s << std::endl;
			if (row % 3 == 2) {
				s << "+---------------+---------------+---------------+";
				s << std::endl;
			}
		}
		break;
	default:
		s << "ERROR STRING MODE";
		break;
	}
	return s.str();
}

bool Sudoku::isValid() {
	for (int row = 0; row < 9; row++) {
		Row r(row);
		for (int number = 1; number <= 9; number++) {
			bool exists = false;
			int count = 0;
			for (int i = 0; i < 9 && count <= 1; i++) {
				Cell* cell = fetch(r.get(i));
				if (cell->isFilled()) {
					if (cell->getValue() == number) {
						exists = true;
						count++;
					}
				}
				else {
					if (cell->choice.has(number)) {
						exists = true;
					}
				}
			}
			if (count > 1 || (count == 0 && !exists)) {
				if (loggerOpened) {
					if (count > 1) {
						logger.addEvent(INVALID_ROW_REPEAT, row, 0, number);
					}
					else {
						logger.addEvent(INVALID_ROW_LOSS, row, 0, number);
					}
				}
				return false;
			}
		}
	}

	for (int col = 0; col < 9; col++) {
		Column c(col);
		for (int number = 1; number <= 9; number++) {
			bool exists = false;
			int count = 0;
			for (int i = 0; i < 9 && count <= 1; i++) {
				Cell* cell = fetch(c.get(i));
				if (cell->isFilled()) {
					if (cell->getValue() == number) {
						exists = true;
						count++;
					}
				}
				else {
					if (cell->choice.has(number)) {
						exists = true;
					}
				}
			}
			if (count > 1 || (count == 0 && !exists)) {
				if (loggerOpened) {
					if (count > 1) {
						logger.addEvent(INVALID_COL_REPEAT, 0, col, number);
					}
					else {
						logger.addEvent(INVALID_COL_LOSS, 0, col, number);
					}
				}
				return false;
			}
		}
	}

	for (int brow = 0; brow < 3; brow++) {
		for (int bcol = 0; bcol < 3; bcol++)
		{
			Block b(3 * brow, 3 * bcol);
			for (int number = 1; number <= 9; number++) {
				bool exists = false;
				int count = 0;
				for (int i = 0; i < 9 && count <= 1; i++) {
					Cell* cell = fetch(b.get(i));
					if (cell->isFilled()) {
						if (cell->getValue() == number) {
							exists = true;
							count++;
						}
					}
					else {
						if (cell->choice.has(number)) {
							exists = true;
						}
					}
				}
				if (count > 1 || (count == 0 && !exists)) {
					if (loggerOpened) {
						if (count > 1) {
							logger.addEvent(INVALID_BLK_REPEAT, 0, 0, number, b.brow, b.bcol);
						}
						else {
							logger.addEvent(INVALID_BLK_LOSS, 0, 0, number, b.brow, b.bcol);
						}
					}
					return false;
				}
			}
		}
	}


	return true;
}

void Sudoku::printLog() {
	std::cout << logger.toString();
}