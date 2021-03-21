#pragma once
#include "common.h"

enum EventType {
	ELIMINATE_ROW = 0,	// because cell (i, j) is filled with k, cells of row i eliminate choice k
	ELIMINATE_COL,		// because cell (i, j) is filled with k, cells of col j eliminate choice k
	ELIMINATE_BLK,		// because cell (i, j) is filled with k, cells of block (brow, bcol) eliminate choice k
	FILL_CEL,			// because cell (i, j) has unique choice k, it is filled with k
	FILL_ROW,			// because cell (i, j) is the unique position for choice k in row i, it is filled with k
	FILL_COL,			// because cell (i, j) is the unique position for choice k in row i, it is filled with k
	FILL_BLK,			// because cell (i, j) is the unique position for choice k in block(brow, bcol), it is filled with k
	INVALID_ROW_LOSS,	// because in row i, k cannot be placed anywhere, this sudoku is invalid.
	INVALID_ROW_REPEAT, // because in row i, k is filled at least twice, this sudoku is invalid.
	INVALID_COL_LOSS,	// because in col j, k cannot be placed anywhere, this sudoku is invalid.
	INVALID_COL_REPEAT, // because in col j, k is filled at least twice, this sudoku is invalid.
	INVALID_BLK_LOSS,	// because in block (brow, bcol), k is filled at least twice, this sudoku is invalid.
	INVALID_BLK_REPEAT = 12, // because in block (brow, bcol), k cannot be placed anywhere, this sudoku is invalid.
};

class Event {
	EventType type;
	int i;
	int j;
	int k;
	int brow;
	int bcol;
public:
	Event(EventType _type, int _i, int _j, int _k) : i(_i), j(_j), k(_k) {
		type = _type;
	}

	Event(EventType _type, int _i, int _j, int _k, int _brow, int _bcol) : Event(_type, _i, _j, _k) {
		brow = _brow;
		bcol = _bcol;
	}

	std::string toString();
};

class EventLogger
{
	std::queue<Event*> events;
	std::stringstream s;

	void flush();
public:
	void addEvent(EventType _type, int _i, int _j, int _k) {
		events.push(new Event(_type, _i, _j, _k));
	}

	void addEvent(EventType _type, int _i, int _j, int _k, int _brow, int _bcol) {
		events.push(new Event(_type, _i, _j, _k, _brow, _bcol));
	}

	std::string toString() {
		flush();
		return s.str();
	}
};

