#include "station.h"

const Station* find_station(const Station* stations, int count, const std::string& name) {
	for (int index = 0; index < count; ++index) {
		if (stations[index].name == name) {
			return &stations[index];
		}
	}

	return nullptr;
}
