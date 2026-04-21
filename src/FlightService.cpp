#include "../include/FlightService.h"
#include "../include/Flight.h"
#include <iostream>
#include <string>

using namespace std;

void FlightService::searchFlights(const json& flightsData) {
    cout << "\n========== FLIGHT SEARCH ==========\n" << endl;
    cout << "1. View All Flights" << endl;
    cout << "2. Search by Destination" << endl;
    cout << "3. Search by Origin" << endl;
    cout << "4. View Flights with Available Seats" << endl;
    cout << "0. Back to Main Menu" << endl;
    cout << "===================================\n" << endl;
    cout << "Enter your choice: ";
    
    int searchChoice;
    cin >> searchChoice;
    
switch (searchChoice) {
    case 1:
        Flight::displayAllFlights(flightsData);
        break;
            
    case 2: {
        cout << "\nEnter destination city: ";
        string destination;
        cin.ignore();
        getline(cin, destination);
        Flight::searchByDestination(flightsData, destination);
        break;
        }
        
    case 3: {
        cout << "\nEnter origin city: ";
        string origin;
        cin.ignore();
        getline(cin, origin);
        Flight::searchByOrigin(flightsData, origin);
        break;
        }
        
    case 4:
        Flight::searchAvailableFlights(flightsData);
        break;
            
    case 0:
            cout << "\nReturning to main menu...\n" << endl;
        break;
            
        default:
            cout << "\nInvalid choice!\n" << endl;
    }
}
