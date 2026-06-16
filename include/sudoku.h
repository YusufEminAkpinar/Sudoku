#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>
#include <random>
#include <iostream>

constexpr int SIZE = 9;

using Grid = std::vector<std::vector<int>>;


class SudokuGenerator {
private:
	Grid grid;
	Grid solved;
	bool isValid(int, int, int);
	std::vector<int> toTwoD(int oneD);
	int toOneD(int x, int y);
	std::vector<int> validOptions(int, int);
	void printGridDebug();
	int numOfValid(int square);
	std::random_device rd;
	std::mt19937 g;
	
public:
	SudokuGenerator() :
	rd(),
	g(rd())
	{
		grid = Grid(SIZE, std::vector<int>(SIZE, 0));
	};

	// SudokuGenerator(SudokuGenerator &&) = default;
	// SudokuGenerator(const SudokuGenerator &) = default;
	// SudokuGenerator &operator=(SudokuGenerator &&) = default;
	// SudokuGenerator &operator=(const SudokuGenerator &) = default;
	~SudokuGenerator() = default;
	Grid getGrid() { return grid; }
	void setGrid(Grid grid);
	void setGrid(int x, int y, int val);
	void setGrid(int sq, int val);
	bool fillGrid(bool anim=false, int square=0, bool fake=false);
	void printGrid();
	void generatePuzzle();

	void test() {
		for (int i = 0; i < SIZE; ++i) {
			for (int j = 0; j < SIZE; ++j) {
				auto x = toOneD(i, j);
				std::cout << x << '\n';
			}
		}
	};
};

#endif // SUDOKU_H
