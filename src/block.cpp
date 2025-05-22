#include "block.h"

Block::Block() {
	cellSize = 30;
	rotationState = 0;
	colors = getCellColors();
	rowOffset = 0;
	columnOffset = 0;
}

void Block::draw(int offsetX, int offsetY) {
	std::vector<Position> tiles = getCellPostitions();
	for (Position item : tiles) {
		DrawRectangle(item.column * cellSize + offsetX, item.row * cellSize + offsetY, cellSize - 1, cellSize - 1, colors[id]);
	}
}

void Block::move(int rows, int columns) {
	rowOffset += rows;
	columnOffset += columns;
}

std::vector<Position> Block::getCellPostitions() {
	std::vector<Position> tiles = cells[rotationState];										// Add current tile positions to vector
	std::vector<Position> movedTiles;														// New vector for moved values
	for (Position item : tiles) {
		Position newPos = Position(item.row + rowOffset, item.column + columnOffset);		// Create new position with moved coordinates
		movedTiles.push_back(newPos);														// Add new position to new vector
	}
	return movedTiles;																		// Return new vector
}

void Block::rotate() {
	rotationState++;
	if (rotationState == (int)cells.size()) {
		rotationState = 0;
	}
}

void Block::undoRotation() {
	rotationState--;
	if (rotationState == -1) {
		rotationState = cells.size() - 1;
	}
}
