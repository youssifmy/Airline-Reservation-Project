#include "../include/FlightManagementService.h"
#include <iostream>

// External declarations
extern json flightsData;
extern json* findFlight(const string& flightNumber);
extern bool saveJSON(const string& filename, const json& data);

vector<FlightInfo> FlightManagementService::getAllFlights() {
    vector<FlightInfo> result;
    
    for (const auto& flight : flightsData) {
        FlightInfo info;
        info.flightNumber = flight["flightNumber"];
        info.origin = flight["origin"];
        info.destination = flight["destination"];
        info.departureTime = flight["departureTime"];
        info.arrivalTime = flight["arrivalTime"];
        info.totalSeats = flight["totalSeats"];
        info.availableSeats = flight["availableSeats"];
        result.push_back(info);
    }
    
    return result;
}

bool FlightManagementService::addFlight(const string& flightNumber, const string& origin,const string& destination, const string& departureTime,
const string& arrivalTime, int totalSeats, int availableSeats) 
{
    //checking for validation
    if (findFlight(flightNumber) != nullptr) {
        cout << "\nError: Flight " << flightNumber << " already exists!" << endl;
        return false;
    }
    
    if (totalSeats < 0 || availableSeats < 0 || availableSeats > totalSeats) {
        cout << "\nError: Invalid seat numbers!" << endl;
        return false;
    }
    
    //Create new flight
    json newFlight = {
        {"flightNumber", flightNumber},
        {"origin", origin},
        {"destination", destination},
        {"departureTime", departureTime},
        {"arrivalTime", arrivalTime},
        {"totalSeats", totalSeats},
        {"availableSeats", availableSeats},
        {"status", "Scheduled"}
    };
    
    flightsData.push_back(newFlight);
    
    bool saved = saveJSON("data/flights.json", flightsData);
    
    if (saved) {
        cout << "\n✓ Flight added successfully!" << endl;
        cout << "Flight Number: " << flightNumber << endl;
        cout << "Route: " << origin << " → " << destination << endl;
    }
    
    return saved;
}

bool FlightManagementService::updateFlight(const string& flightNumber, const string& origin,const string& destination, const string& departureTime,
const string& arrivalTime) 
{
    json* flight = findFlight(flightNumber);
    if (flight == nullptr) {
        cout << "\nError: Flight not found!" << endl;
        return false;
    }
    
    if (!origin.empty()) (*flight)["origin"] = origin;
    if (!destination.empty()) (*flight)["destination"] = destination;
    if (!departureTime.empty()) (*flight)["departureTime"] = departureTime;
    if (!arrivalTime.empty()) (*flight)["arrivalTime"] = arrivalTime;
    
    bool saved = saveJSON("data/flights.json", flightsData);
    
    if (saved) {
        cout << "\n✓ Flight updated successfully!" << endl;
    }
    
    return saved;
}

bool FlightManagementService::deleteFlight(const string& flightNumber) {
    auto it = flightsData.begin(); // it iterator 3shan hansa akeed 
    bool found = false;

//------------------------------------------    
    
    for (; it != flightsData.end(); ++it) {
        if ((*it)["flightNumber"] == flightNumber) {
        found = true;
            break;
        }
    }
    
    if (!found) {
        cout << "\nError: Flight not found!" << endl;
        return false;
    }
    
    flightsData.erase(it);
    
    bool saved = saveJSON("data/flights.json", flightsData);
    
    if (saved) {
        cout << "\n Flight deleted successfully!" << endl;
    }
    
    return saved;
}

json* FlightManagementService::getFlightDetails(const string& flightNumber) {
    return findFlight(flightNumber);
}
