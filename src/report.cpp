#include "report.h"

#include <iomanip>
#include <iostream>

#include "analysis.h"
#include "grid.h"

void print_report(const Station* stations, const double* temps, int rows, int cols) {
	if (stations == nullptr || temps == nullptr || rows <= 0 || cols <= 0) {
		std::cout << "No data.\n";
		return;
	}

	std::cout << std::left << std::setw(20) << "Station"
			  << std::right << std::setw(14) << "Elevation (ft)";
	for (int day = 0; day < cols; ++day) {
		std::cout << std::setw(10) << ("Day " + std::to_string(day + 1));
	}
	std::cout << std::setw(10) << "Average" << '\n';

	std::cout << std::fixed << std::setprecision(1);
	for (int station = 0; station < rows; ++station) {
		std::cout << std::left << std::setw(20) << stations[station].name
				  << std::right << std::setw(14) << stations[station].elevation_ft;
		for (int day = 0; day < cols; ++day) {
			std::cout << std::setw(10) << temps[grid_index(station, day, cols)];
		}

		double average = 0.0;
		if (station_average(temps, rows, cols, station, average)) {
			std::cout << std::setw(10) << average;
		} else {
			std::cout << std::setw(10) << "N/A";
		}
		std::cout << '\n';
	}

	int hot_row = 0;
	int hot_col = 0;
	if (find_hottest(temps, rows, cols, hot_row, hot_col)) {
		std::cout << "Hottest reading: "
				  << temps[grid_index(hot_row, hot_col, cols)]
				  << " at " << stations[hot_row].name
				  << " on day " << hot_col + 1 << '\n';
	}
}
