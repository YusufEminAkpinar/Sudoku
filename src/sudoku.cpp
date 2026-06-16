#include "sudoku.h"
#include <iostream>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <ostream>
#include <thread>
#include <chrono>

bool SudokuGenerator::isValid(int row, int col, int val) {
	// Check for row
	auto r = grid[row];
	auto f = std::find(r.begin(), r.end(), val);
	if ((f != r.end()) && (std::distance(r.begin(), f) != col )) {
		return false; 
	}

	// Check for column
	for (int i = 0; i < SIZE; ++i) {
		if (i != row) {
			int c = grid[i][col];
			if (c == val) {
				return false;
			}
		}
	}

	// At the 3x3 subgrid
	int subgridStartX = row - row%3;
	int subgridStartY = col - col%3;

	for (int x = 0; x < 3; ++x) {
		for (int y = 0; y < 3; ++y) {
			int posX = subgridStartX + x;
			int posY = subgridStartY + y;
			if ((posX != row) && (posY != col) && (grid[posX][posY] == val)) {
				return false;
			}
		}
	}
	return true;
};

std::vector<int> SudokuGenerator::validOptions(int row, int col) {
	std::vector<int> v;
	for (int i = 1; i < SIZE+1; ++i) {
		if (isValid(row, col, i))
			v.push_back(i);
	}
	return v;
}


std::vector<int> SudokuGenerator::toTwoD(int oneD) {
	return {oneD/SIZE, oneD - SIZE * (oneD/SIZE)};
}

int SudokuGenerator::toOneD(int x, int y) {
	return x*SIZE + y;
}

// Generates a random solved sudoku from empty grid
bool SudokuGenerator::fillGrid(bool anim, int square, bool fake) {

	if (square == SIZE*SIZE) {
		// Look if there is any zero
		for (int i = 0; i < SIZE; ++i) {
			for (int j = 0; j < SIZE; ++j) {
				if (this->grid[i][j] == 0) {
					return fillGrid(anim, toOneD(i, j), fake);
				}
			}
		}
		return true;
	}


	auto zero = toTwoD(square);
	int r = zero[0];
	int c = zero[1];

	if (grid[r][c] != 0) {
        return fillGrid(anim, square + 1, fake);
    }

	auto shuffled = validOptions(r, c);
	if (shuffled.size() > 1)
		std::shuffle(shuffled.begin(), shuffled.end(), g);

	if (anim) printGridDebug();
	// Check for valid positions
	for (auto val: shuffled) {
		if (isValid(r, c, val)) {
			grid[r][c] = val;
			if (fillGrid(anim, square + 1, fake))
				return true;

			// Backtrack, set to 0
			grid[r][c] = 0;
		}
	}

	return false;
}

void SudokuGenerator::printGrid() {
	int t = 0;
	
	for (auto r: grid) {
		
		if(t%3 == 0) {
			std::cout << "-------------------\n";
		} else {
			std::cout << "|- - -|- - -|- - -|\n";
		}
		for (auto c: r) {
			std::cout << '|' << c;
		}
		std::cout << '|' << std::endl;
		t++;
	}
	std::cout << "-------------------\n";
}

/*
 * Generate too fast, you can't see anything, but can be turned into animation
 * using sleeps,
 */
void SudokuGenerator::printGridDebug() {
	int t = 0;
	for (auto r: grid) { if(t%3 == 0) {
			std::cout << "-------------------\n";
		} else {
			std::cout << "|- - -|- - -|- - -|\n";
		}
		for (auto c: r) {
			std::cout << '|' << c;
		}
		std::cout << '|' << std::endl;
		t++;
	}
	std::cout << "-------------------\n";
	for (int i = 0; i < SIZE*2+1; ++i) {
		std::cout << "\033[A"; 
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(100));

}

void SudokuGenerator::setGrid(int x, int y, int val) {
	this->grid[x][y] = val;
}

void SudokuGenerator::setGrid(Grid grid) {
	this->grid = grid;
}

void SudokuGenerator::setGrid(int sq, int val) {
	auto z = toTwoD(sq);
	int r = z[0];
	int c = z[1];
	this->grid[r][c] = val;
}

int SudokuGenerator::numOfValid(int square) {
	auto zero = toTwoD(square);
	int r = zero[0];
	int c = zero[1];
	
	auto valids = validOptions(r, c);
	int num = valids.size();
	// std::cout << "Valid options calculated: " << num << ' ' << valids[0] << '\n';

	// Look if valid option results in valid sudoku.
	SudokuGenerator fakeSudoku;
	fakeSudoku.setGrid(this->grid);
	// std::cout << "Fake sudoku generated and grid is set.\n";
	for (auto v : valids) {
		fakeSudoku.setGrid(r, c, v);
		bool isSolvable = fakeSudoku.fillGrid(false, square+1, true);
		if (!isSolvable) {
			// std::cout << "Solving this sudoku with " << v << " is impossible.\n";
			num--;
		}
	}

	return num;
}


void SudokuGenerator::generatePuzzle() {
	fillGrid();
	// Choose random square
	// std::uniform_int_distribution<int> int_dist(0, SIZE*SIZE-1);
	// int rand = int_dist(g);
	std::vector<int> shuff(SIZE*SIZE);
	std::iota(shuff.begin(), shuff.end(), 0);

	std::shuffle(shuff.begin(), shuff.end(), g);
	std::cout << '\n';
	
	// Look for number of shuffalid options, if 1 delete it, else choose another one.
	for (auto c : shuff) {
		// std::cout << "Trying for " << c << std::endl;
		int n = numOfValid(c);
		if (n == 1) {
			// std::cout << "There is only 1 option." << std::endl;
			this->setGrid(c, 0);
		}
	}

}


