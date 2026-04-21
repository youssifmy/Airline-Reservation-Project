#include "../include/Flight.h"
#include <iostream>
using namespace std;

bool Flight::bookSeat(){
    if (availableSeats > 0)
    {
        availableSeats--;
        cout << "Seat is Booked Successfully." <<endl << "Our Company Wish you A Safe Flight (^_^)" << endl;
        return true;
    }
    else{
        cout << "We are very Sorry but This AirCraft is Complete!" << endl;
        return false;
    }
};

void Flight::cancelSeat() {
    if(availableSeats < totalSeats){
        availableSeats++;
        cout << "\n Canceling Seat ... \n" << endl;
    }
}

void Flight::displayFlightInfo() const {
    cout << "FlightNumber: " << flightNumber << endl;
    cout << "Flight-Origin: " << origin << endl;
    cout << "Flight-Destination: " << destination << endl;
    cout << "Flight-DepartureTime: " << departureTime << endl;
    cout << "Flight-ArrivalTime: " << arrivalTime << endl;
    cout << "AirCraft-ID: " << aircraftId << endl;
    cout << "Flight-TotalSeats: " << totalSeats << endl;
    cout << "Flight-AvailableSeats: " << availableSeats << endl;
    cout << "Flight-Status: " << status << endl;
}




void Flight::displayFlight(const json& flight) {
    cout << "Flight: " << flight["flightNumber"] << " | "
         << flight["origin"] << " to " << flight["destination"] << endl;
    cout << "Departure: " << flight["departureTime"] << " | "
         << "Arrival: " << flight["arrivalTime"] << endl;
    cout << "Seats Available: " << flight["availableSeats"] << "/" << flight["totalSeats"]
         << " | Status: " << flight["status"] << endl;
    cout << "Aircraft: " << flight["aircraftId"] << endl;
    cout << "----------------------------------------" << endl;
}

void Flight::displayAllFlights(const json& flightsData) {
    if (flightsData.empty()) {
        cout << "\nNo flights available at the moment.\n" << endl;
        return;
    }
    
    cout << "\n========== AVAILABLE FLIGHTS ==========\n" << endl;
    for (const auto& flight : flightsData) {
        displayFlight(flight);
    }
}

void Flight::searchByDestination(const json& flightsData, const string& destination) {
    cout << "\n========== FLIGHTS TO " << destination << " ==========\n" << endl;
    
    bool found = false;
    for (const auto& flight : flightsData) {
    string flightDest = flight["destination"];
    if (flightDest.find(destination) != string::npos || 
        destination.find(flightDest) != string::npos) {
        displayFlight(flight);
        found = true;
        }
    }
    
    if (!found) {
        cout << "No flights found to " << destination << "\n" << endl;
    }
}

void Flight::searchByOrigin(const json& flightsData, const string& origin) {
    cout << "\n========== FLIGHTS FROM " << origin << " ==========\n" << endl;
    
    bool found = false;
    for (const auto& flight : flightsData) {
        string flightOrigin = flight["origin"];
        if (flightOrigin.find(origin) != string::npos || 
            origin.find(flightOrigin) != string::npos) {
            displayFlight(flight);
            found = true;
        }
    }
    
    if (!found) {
        cout << "No flights found from " << origin << "\n" << endl;
    }
}

void Flight::searchAvailableFlights(const json& flightsData) {
    cout << "\n========== FLIGHTS WITH AVAILABLE SEATS ==========\n" << endl;
    
    bool found = false;
    for (const auto& flight : flightsData) {
    int availableSeats = flight["availableSeats"];
    if (availableSeats > 0) {
        displayFlight(flight);
        found = true;
        }
    }
    
    if (!found) {
        cout << "No flights with available seats.\n" << endl;
    }
}