#ifndef FLIGHT_H
#define FLIGHT_H

#include <string>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

class Flight{
    private:
        string flightNumber;
        string origin;
        string destination;
        string departureTime;
        string arrivalTime;
        string aircraftId;
        int totalSeats;
        int availableSeats;
        string status;
        string assignedPilotId;
        string assignedAttendantId;

    public:
        Flight(const string& flightNumber, const string& origin, const string& destination, 
            const string& departureTime, const string& arrivalTime, const string& aircraftId, 
            int totalSeats, int availableSeats, const string& status)
            : flightNumber(flightNumber), origin(origin), destination(destination),
              departureTime(departureTime), arrivalTime(arrivalTime), aircraftId(aircraftId),
              totalSeats(totalSeats), availableSeats(availableSeats), status(status) {}

    
        // Getters
        string getFlightNumber() const {
            return flightNumber;
        }

        string getOrigin() const {
            return origin;
        }

        string getDestination() const {
            return destination;
        }

        string getDepartureTime() const {
            return departureTime;
        }

        string getArrivalTime() const {
            return arrivalTime;
        }

        string getAircraftId() const {
            return aircraftId;
        }

        int getTotalSeats() const {
            return totalSeats;
        }

        int getAvailableSeats() const {
            return availableSeats;
        }

        string getStatus() const {
            return status;
        }

        // Setters
        void setStatus(const string& newStatus){
            status = newStatus;
        }

        void setArrivalTime(const string& newArrivalTime){
            arrivalTime = newArrivalTime;
        }

        void setDepartureTime(const string& newDepartureTime){
            departureTime = newDepartureTime;
        }

        //class functions
        
        bool bookSeat();
        void cancelSeat();
        void displayFlightInfo() const;
        
        // Static Functions
        static void displayFlight(const json& flight);
        static void displayAllFlights(const json& flightsData);
        static void searchByDestination(const json& flightsData, const string& destination);
        static void searchByOrigin(const json& flightsData, const string& origin);
        static void searchAvailableFlights(const json& flightsData);
};

#endif
