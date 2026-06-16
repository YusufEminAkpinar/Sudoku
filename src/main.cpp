#include "sudoku.h"
#include <iostream>

int main (int argc, char *argv[]) {
	(void) argc;
	(void) argv;

	SudokuGenerator s;
	Grid g = s.getGrid();

	s.fillGrid();

	s.printGrid();

	s.generatePuzzle();
	std::cout << "\n\n\n\n" << std::endl;
	s.printGrid();

	return 0;
}

