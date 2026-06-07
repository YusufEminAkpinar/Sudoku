#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>

constexpr int SIZE = 9;

using Grid = std::vector<std::vector<int>>;



class SudokuGenerator {
private:
	Grid grid;
	Grid solved;
	bool isValid(int, int, int);
	std::vector<int> toTwoD(int oneD);
	std::vector<int> validOptions(int, int);
	void printGridDebug();
	// std::vector<int> digits{1, 2, 3, 4, 5, 6, 7, 8, 9};
	
public:
	SudokuGenerator() {
		grid = Grid(SIZE, std::vector<int>(SIZE, 0));
	};
	SudokuGenerator(SudokuGenerator &&) = default;
	SudokuGenerator(const SudokuGenerator &) = default;
	SudokuGenerator &operator=(SudokuGenerator &&) = default;
	SudokuGenerator &operator=(const SudokuGenerator &) = default;
	~SudokuGenerator() = default;
	Grid getGrid() { return grid; }
	void setGrid(int x, int y, int val);
	bool fillGrid(int square);
	void printGrid();

};

#endif // SUDOKU_H
