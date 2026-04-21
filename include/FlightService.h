#ifndef FLIGHTSERVICE_H
#define FLIGHTSERVICE_H

#include "json.hpp"
#include <string>

using json = nlohmann::json;
using namespace std;

class FlightService {
public:
    
    static void searchFlights(const json& flightsData);
};

#endif
