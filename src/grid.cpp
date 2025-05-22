/*
Grid uses an array to represent the state of each tile on the board. 0 is used to represent an empty tile. 1-7 are used to represent
the different colors/tetrominoes. The current active piece is not represented by a number in the array.
*/

#include "grid.h"
#include <iostream>
#include "colors.h"

// Grid constructor
Grid::Grid() {		
	numRows = 20;
	numCols = 10;
	cellSize = 30;
	initialize();
	colors = getCellColors();		// Load color vector
}

// Set each tile to 0
void Grid::initialize() {
	for (int row = 0; row < numRows; row++) {
		for (int column = 0; column < numCols; column++) {
			grid[row][column] = 0;
		}
	}
}

// Check tile status in terminal
void Grid::print() {
	for (int row = 0; row < numRows; row++) {
		for (int column = 0; column < numCols; column++) {
			std::cout << grid[row][column] << " ";
		}
		std::cout << std::endl;
	}
}

// Draw grid to Raylib window
void Grid::draw() {
	for (int row = 0; row < numRows; row++) {
		for (int column = 0; column < numCols; column++) {
			int cellValue = grid[row][column];
			DrawRectangle(column * cellSize+11, row * cellSize+11, cellSize-1, cellSize-1, colors[cellValue]);	// Draw colored tiles with grid lines in between
		}
	} 
}

bool Grid::isCellOutside(int row, int column) {
	if (row >= 0 && row < numRows && column >= 0 && column < numCols) {
		return false;
	}
	return true;
}

bool Grid::isCellEmpty(int row, int column)
{
	if (grid[row][column] == 0) {
		return true;
	}
	return false;
}

int Grid::clearFullRows()
{
	int completed = 0;
	for (int row = numRows - 1; row >= 0; row--) {
		if (isRowFull(row)) {
			clearRow(row);
			completed++;
		}
		else if (completed > 0) {
			moveRowDown(row, completed);
		}
	}
	return completed;
}

bool Grid::isRowFull(int row)
{
	for (int column = 0; column < numCols; column++) {
		if (grid[row][column] == 0) {
			return false;
		}
	}
	return true;
}

void Grid::clearRow(int row) {
	for (int column = 0; column < numCols; column++) {
		grid[row][column] = 0;
	}
}

void Grid::moveRowDown(int row, int numRows) {
	for (int column = 0; column < numCols; column++) {
		grid[row + numRows][column] = grid[row][column];
		grid[row][column] = 0;
	}
}
