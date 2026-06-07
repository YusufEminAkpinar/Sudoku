#include "sudoku.h"

int main (int argc, char *argv[]) {
	(void) argc;
	(void) argv;

	SudokuGenerator s;
	Grid g = s.getGrid();

	s.fillGrid(0);

	s.printGrid();

	return 0;
}

