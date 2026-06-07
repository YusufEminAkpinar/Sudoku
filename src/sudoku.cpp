#include "sudoku.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <iostream>

bool SudokuGenerator::isValid(int row, int col, int val) {
	// Check for row
	auto r = grid[row];
	if (std::find(r.begin(), r.end(), val) != r.end()) {
		return false; }

	// Check for column
	for (int i = 0; i < SIZE; ++i) {
		int c = grid[i][col];
		if (c == val) {
			return false;
		}
	}

	// At the 3x3 subgrid
	int subgridStartX = row - row%3;
	int subgridStartY = col - col%3;

	for (int x = 0; x < 3; ++x) {
		for (int y = 0; y < 3; ++y) {
			int posX = subgridStartX + x;
			int posY = subgridStartY + y;
			if (grid[posX][posY] == val) {
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

// Generates a random solved sudoku from empty grid
bool SudokuGenerator::fillGrid(int square) {

	if (square == SIZE*SIZE) {
		return true;
	}

	auto zero = toTwoD(square);
	int r = zero[0];
	int c = zero[1];

	if (grid[r][c] != 0) {
        return fillGrid(square + 1);
    }

	auto shuffled = validOptions(r, c);
	std::random_device rd;
	std::mt19937 g(rd());
	if (shuffled.size() > 1)
		std::shuffle(shuffled.begin(), shuffled.end(), g);

	printGridDebug();
	// Check for valid positions
	for (auto val: shuffled) {
		if (isValid(r, c, val)) {
			grid[r][c] = val;
			if (fillGrid(square + 1))
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
	for (auto r: grid) {
		for (auto c: r) {
			std::cout << c << '|';
		}
		std::cout << '\n';
		std::cout << "- - - - - - - - -\n";
	}
	for (int i = 0; i < SIZE*2; ++i) {
		std::cout << "\033[A"; 
	}
}

void SudokuGenerator::setGrid(int x, int y, int val) {
	grid[x][y] = val;
}
