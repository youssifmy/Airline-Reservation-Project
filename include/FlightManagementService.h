#ifndef FLIGHTMANAGEMENTSERVICE_H
#define FLIGHTMANAGEMENTSERVICE_H

#include "json.hpp"
#include <string>
#include <vector>

using json = nlohmann::json;
using namespace std;

struct FlightInfo {
    string flightNumber;
    string origin;
    string destination;
    string departureTime;
    string arrivalTime;
    int totalSeats;
    int availableSeats;
};

class FlightManagementService {
public:
    
    static vector<FlightInfo> getAllFlights();
    
    
    static bool addFlight(const string& flightNumber, const string& origin, 
    const string& destination, const string& departureTime,const string& arrivalTime, 
    int totalSeats, int availableSeats);
    
    
    static bool updateFlight(const string& flightNumber, const string& origin,
    const string& destination, const string& departureTime,const string& arrivalTime);
    
    
    static bool deleteFlight(const string& flightNumber);
    
    
    static json* getFlightDetails(const string& flightNumber);
};

#endif
