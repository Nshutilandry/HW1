#ifndef HW1_STATION_H
#define HW1_STATION_H

#include <string>

struct Station {
    std::string name;
    double elevation_ft;
};

const Station* find_station(const Station* stations, int count, const std::string& name);

#endif
