#include "../include/Administrator.h"
#include "../include/BookingAgent.h"
#include "../include/Passenger.h"
#include "../include/Flight.h"
#include "../include/json.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
using json = nlohmann::json;

json usersData;
json flightsData;
json reservationsData;
json pilotsData;
json attendantsData;

json loadJSON(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return json::array();
    }
    
    json data;
    try {
        file >> data;
    } catch (json::parse_error& e) {
        cerr << "JSON parse error in " << filename << ": " << e.what() << endl;
        return json::array();
    }
    
    file.close();
    return data;
}

void loadAllData() {
    cout << "Loading data from files..." << endl;
    usersData = loadJSON("data/users.json");
    flightsData = loadJSON("data/flights.json");
    reservationsData = loadJSON("data/reservations.json");
    pilotsData = loadJSON("data/pilots.json");
    attendantsData = loadJSON("data/attendants.json");
    
    cout << " Loaded " << usersData.size() << " users" << endl;
    cout << " Loaded " << flightsData.size() << " flights" << endl;
    cout << " Loaded " << reservationsData.size() << " reservations" << endl;
    cout << " Loaded " << pilotsData.size() << " pilots" << endl;
    cout << " Loaded " << attendantsData.size() << " flight attendants" << endl;
    cout << endl;
}

bool saveJSON(const string& filename, const json& data) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << " for writing" << endl;
        return false;
    }
    
    try {
        file << data.dump(4);
    } catch (exception& e) {
        cerr << "Error writing to " << filename << ": " << e.what() << endl;
        return false;
    }
    
    file.close();
    return true;
}

void saveAllData() {
    saveJSON("data/users.json", usersData);
    saveJSON("data/flights.json", flightsData);
    saveJSON("data/reservations.json", reservationsData);
}

json* findFlight(const string& flightNumber) {
    for (auto& flight : flightsData) {
        if (flight["flightNumber"] == flightNumber) {
            return &flight;
        }
    }
    return nullptr;
}

int getNextReservationId() {
    int maxId = 1000;
    for (const auto& res : reservationsData) {
        int id = res["reservationId"];
        if (id > maxId) {
            maxId = id;
        }
    }
    return maxId + 1;
}

json* findReservation(int reservationId) {
    for (auto& res : reservationsData) {
        if (res["reservationId"] == reservationId) {
            return &res;
        }
    }
    return nullptr;
}

void displayFlight(const json& flight) {
    cout << "Flight: " << flight["flightNumber"] << " | "
         << flight["origin"] << " → " << flight["destination"] << endl;
    cout << "Departure: " << flight["departureTime"] << " | "
         << "Arrival: " << flight["arrivalTime"] << endl;
    cout << "Seats Available: " << flight["availableSeats"] << "/" << flight["totalSeats"]
         << " | Status: " << flight["status"] << endl;
    cout << "Aircraft: " << flight["aircraftId"] << endl;
    cout << "----------------------------------------" << endl;
}

void displayAllFlights() {
    if (flightsData.empty()) {
        cout << "\nNo flights available at the moment.\n" << endl;
        return;
    }
    
    cout << "\n========== AVAILABLE FLIGHTS ==========\n" << endl;
    for (const auto& flight : flightsData) {
        displayFlight(flight);
    }
}

void searchFlightsByDestination(const string& destination) {
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

void searchFlightsByOrigin(const string& origin) {
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

void searchAvailableFlights() {
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

void showWelcome() {
    cout << "\n";
    cout << "========================================" << endl;
    cout << "   AIRLINE RESERVATION SYSTEM" << endl;
    cout << "   Welcome to Oufa Airlines" << endl;
    cout << "========================================" << endl;
    cout << "\n";
}

User* authenticateUser(const string& username, const string& password) {
    for (const auto& user : usersData) {
        string jsonUsername = user["username"];
        string jsonPassword = user["password"];
        if (jsonUsername == username && jsonPassword == password) {
            int id = user["id"];
            string role = user["role"];
            
            cout << "\n Login successful! Welcome " << username << ".\n" << endl;
            if (role == "Administrator") {
                return new Administrator(id, username, password);
            }
            else if (role == "BookingAgent") {
                return new BookingAgent(id, username, password);
            }
            else if (role == "Passenger") {
                int loyaltyPoints = user.value("loyaltyPoints", 0);
                string frequentFlyerNumber = user.value("frequentFlyerNumber", "");
                return new Passenger(id, username, password, loyaltyPoints, frequentFlyerNumber);
            }
        }
    }
    return nullptr;
}

int main() {
    showWelcome();
    loadAllData();
    
    string username, password;
    User* currentUser = nullptr;
    while (true) {
        cout << "========================================" << endl;
        cout << "           LOGIN MENU" << endl;
        cout << "========================================" << endl;
        cout << "1. Login" << endl;
        cout << "2. Exit" << endl;
        cout << "========================================" << endl;
        cout << "Enter your choice: ";
        
        int loginChoice;
        cin >> loginChoice;
        
        if (loginChoice == 2) {
            cout << "\nThank you for using Oufa Airlines!" << endl;
            cout << "Have a great day!\n" << endl;
            break;
        }
        
        if (loginChoice == 1) {
            cout << "\n--- LOGIN ---" << endl;
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;
            currentUser = authenticateUser(username, password);
            
            if (currentUser != nullptr) {
                int choice;
                do {
                    cout << "\n";
                    currentUser->displayMenu();
                    cin >> choice;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "Invalid input! Please enter a number." << endl;
                        continue;
                    }
                    
                    cout << "\n";
                    currentUser->performAction(choice);
                } while (choice != 0);
                delete currentUser;
                currentUser = nullptr;
                
                cout << "\n Logged out successfully!\n" << endl;
                
            } else {
                cout << "\n Login failed! Invalid username or password." << endl;
                cout << "Please try again.\n" << endl;
            }
            
        } else {
            cout << "\nInvalid choice! Please try again.\n" << endl;
        }
    }
    
    return 0;
}
