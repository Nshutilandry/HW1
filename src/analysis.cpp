#include "analysis.h"

#include "grid.h"

bool station_average(const double* temps, int rows, int cols, int station, double& average) {
	if (!in_bounds(station, 0, rows, cols)) {
		return false;
	}

	double total = 0.0;
	for (int day = 0; day < cols; ++day) {
		total += temps[grid_index(station, day, cols)];
	}

	average = total / cols;
	return true;
}

bool day_average(const double* temps, int rows, int cols, int day, double& average) {
	if (!in_bounds(0, day, rows, cols)) {
		return false;
	}

	double total = 0.0;
	for (int station = 0; station < rows; ++station) {
		total += temps[grid_index(station, day, cols)];
	}

	average = total / rows;
	return true;
}

bool find_hottest(const double* temps, int rows, int cols, int& hot_row, int& hot_col) {
	if (rows <= 0 || cols <= 0) {
		return false;
	}

	int hottest_row = 0;
	int hottest_col = 0;
	double hottest = temps[grid_index(0, 0, cols)];

	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < cols; ++col) {
			const double reading = temps[grid_index(row, col, cols)];
			if (reading > hottest) {
				hottest = reading;
				hottest_row = row;
				hottest_col = col;
			}
		}
	}

	hot_row = hottest_row;
	hot_col = hottest_col;
	return true;
}

int count_above(const double* temps, int rows, int cols, double threshold) {
	int count = 0;
	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < cols; ++col) {
			if (temps[grid_index(row, col, cols)] > threshold) {
				++count;
			}
		}
	}

	return count;
}
