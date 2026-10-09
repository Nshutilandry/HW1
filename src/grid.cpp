#include "grid.h"

int grid_index(int row, int col, int cols) {
	return row * cols + col;
}

bool in_bounds(int row, int col, int rows, int cols) {
	return row >= 0 && row < rows && col >= 0 && col < cols;
}
