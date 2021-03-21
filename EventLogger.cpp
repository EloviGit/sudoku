#include "EventLogger.h"

std::string Event::toString() {
	char buf[100];
	switch (type)
	{
	case ELIMINATE_ROW:
		sprintf_s(buf, "because cell (%d, %d) is filled with %d, cells of row %d eliminate choice %d.", i, j, k, i, k); break;
	case ELIMINATE_COL:
		sprintf_s(buf, "because cell (%d, %d) is filled with %d, cells of col %d eliminate choice %d.", i, j, k, j, k); break;
	case ELIMINATE_BLK:
		sprintf_s(buf, "because cell (%d, %d) is filled with %d, cells of block (%d, %d) eliminate choice %d.", i, j, k, brow, bcol, k); break;
	case FILL_CEL:
		sprintf_s(buf, "because cell (%d, %d) has unique choice %d, it is filled with %d.", i, j, k, k); break;
	case FILL_ROW:
		sprintf_s(buf, "because cell (%d, %d) is the unique position for choice %d in row %d, it is filled with %d.", i, j, k, i, k); break;
	case FILL_COL:
		sprintf_s(buf, "because cell (%d, %d) is the unique position for choice %d in col %d, it is filled with %d.", i, j, k, j, k); break;
	case FILL_BLK:
		sprintf_s(buf, "because cell (%d, %d) is the unique position for choice %d in block (%d, %d), it is filled with %d.", i, j, k, brow, bcol, k); break;
	case INVALID_ROW_LOSS:
		sprintf_s(buf, "because in row %d, %d cannot be anywhere, this sudoku is invalid.", i, k); break;
	case INVALID_ROW_REPEAT:
		sprintf_s(buf, "because in row %d, %d is filled at least twice, this sudoku is invalid.", i, k); break;
	case INVALID_COL_LOSS:
		sprintf_s(buf, "because in col %d, %d cannot be anywhere, this sudoku is invalid.", j, k); break;
	case INVALID_COL_REPEAT:
		sprintf_s(buf, "because in col %d, %d is filled at least twice, this sudoku is invalid.", j, k); break;
	case INVALID_BLK_LOSS:
		sprintf_s(buf, "because in block(%d, %d), %d cannot be filled anywhere, this sudoku is invalid.", brow, bcol, k); break;
	case INVALID_BLK_REPEAT:
		sprintf_s(buf, "because in block(%d, %d), %d is filled at least twice, this sudoku is invalid.", brow, bcol, k); break;
	default:
		break;
	}
	return buf;
}

void EventLogger::flush() {
	while (!events.empty()) {
		Event* event = events.front();
		events.pop();
		s << event->toString() << std::endl;
		delete event;
	}
}

