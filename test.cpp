#include "common.h"
#include "classes.h"
#include "Sudoku.h"
#include "data.h"

void test_choice() {
	std::cout << "TESTING CHOICE" << std::endl;
	Choice c, d;
	std::cout << "c: " << c.isUnique() << ";" << "d: " << d.isUnique() << std::endl;
	c.set(9);
	d.eliminate(8);
	d.eliminate(7);
	std::cout << "c: " << c.has(8) << ", " << c.has(9) << ";" << "d: " << d.has(8) << ", " << d.has(9) << std::endl;
	std::cout << "c: " << c.isUnique() << ";" << "d: " << d.isUnique() << std::endl;
}

void test_position() {
	std::cout << "TESTING POSITION" << std::endl;
	Position p1(1, 2), p2, p3(4, 5), p4(7, 8);
	std::cout << p1.toString() << std::endl << p2.toString() << std::endl << p3.toString() << std::endl << p4.toString() << std::endl;
	Block b1(p1), b2(0, 3), b3(p2);
	Row r1(p2), r2(p3), r3(6);
	Column c1(p3), c2(p4), c3(3);
	std::cout << b1.toString() << std::endl << b2.toString() << std::endl << b3.toString() << std::endl;
	std::cout << r1.toString() << std::endl << r2.toString() << std::endl << r3.toString() << std::endl;
	std::cout << c1.toString() << std::endl << c2.toString() << std::endl << c3.toString() << std::endl;
}

void test_sudoku_sub(int inputdata[9][9]) {
	Sudoku sudoku(inputdata);
	if (sudoku.isValid()) {
		std::cout << "BEFORE:" << std::endl;
		std::cout << sudoku.toString(2);
		int round = sudoku.solve();
		std::cout << "AFTER:" << std::endl;
		if (round > 0) {
			std::cout << sudoku.toString();
			std::cout << "ITERATION ROUNDS: " << round << std::endl;
		}
		else {
			std::cout << sudoku.toString();
			std::cout << "THIS SUDOKU IS INVALID!" << std::endl;
		}
	}
	else {
		std::cout << sudoku.toString();
		std::cout << "THIS SUDOKU IS INVALID!" << std::endl;
	}

	std::cout << "EVENT LOG:" << std::endl;
	sudoku.printLog();
}

void test_sudoku() {
	std::cout << "TESTING SUDOKU" << std::endl;

//	test_sudoku_sub(INPUTDATA(0));
//	test_sudoku_sub(INPUTDATA(1));
//	test_sudoku_sub(INPUTDATA(2));
//	test_sudoku_sub(INPUTDATA(3));
//	test_sudoku_sub(INPUTDATA(4));
//	test_sudoku_sub(INPUTDATA(5));
//	test_sudoku_sub(INPUTDATA(6));
//	test_sudoku_sub(INPUTDATA(7));
//	test_sudoku_sub(INPUTDATA(8));
//	test_sudoku_sub(INPUTDATA(9));
//	test_sudoku_sub(INPUTDATA(10));
	test_sudoku_sub(INPUTDATA(13));

	std::cout << "SUDOKU INSTANCE COUNT: " << dataCount;
}

void test() {
//	test_choice();
//	test_position();
	test_sudoku();
}
