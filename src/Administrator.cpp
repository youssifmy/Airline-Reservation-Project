#include "../include/Administrator.h"
#include "../include/Flight.h"
#include "../include/Pilot.h"
#include "../include/FlightAttendant.h"
#include "../include/UserManagementService.h"
#include "../include/FlightManagementService.h"
#include "../include/ReservationService.h"
#include "../include/ReportService.h"
#include "../include/json.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
using json = nlohmann::json;

//External declarations for main
extern json flightsData;
extern json reservationsData;
extern json usersData;
extern json pilotsData;
extern json attendantsData;
extern bool saveJSON(const string& filename, const json& data);
extern json* findFlight(const string& flightNumber);

void Administrator::displayMenu() {
    cout << "---------- Administrator Menu ----------" << endl;
    cout << "1. Manage Users" << endl;
    cout << "2. Manage Flights" << endl;
    cout << "3. Manage Aircraft" << endl;
    cout << "4. Manage Crew" << endl;
    cout << "5. View All Reservations" << endl;
    cout << "6. Generate Reports" << endl;
    cout << "0. Logout" << endl;
    cout << "Enter your choice: ";
}

void Administrator::performAction(int choice) {
    switch (choice) {
        case 1:
            manageUsers();
            break;
        case 2:
            manageFlights();
            break;
        case 3:
            manageAircraft();
            break;
        case 4:
            manageCrew();
            break;
        case 5:
            viewAllReservations();
            break;
        case 6:
            generateReports();
            break;
        case 0:
            cout << "Logging out..."<< endl;
            break;
        default:
            cout << "Invalid choice" << endl;
    }
}

void Administrator::manageUsers() {
    cout << "\n===== User Management =====\n" << endl;
    cout << "1. View All Users" << endl;
    cout << "2. Add New User" << endl;
    cout << "3. Delete User" << endl;
    cout << "0. Back to Main Menu" << endl;
    cout << "\nEnter your choice: ";
    
    int choice;
    cin >> choice;
    
    switch(choice) {
        case 1: {
            
        vector<UserInfo> users = UserManagementService::getAllUsers();
            
        cout << "\n===== All Users (" << users.size() << " total) =====\n" << endl;
            
        //Roles
        cout << "ADMINISTRATORS:" << endl;
        cout << string(60, '-') << endl;
        for (const auto& user : users) {
        if (user.role == "Administrator") {
        cout << "ID: " << user.id << " | Username: " << user.username << endl;
        }
            }
            
        cout << "\nBOOKING AGENTS:" << endl;
        cout << string(60, '-') << endl;
        for (const auto& user : users) {
        if (user.role == "BookingAgent") {
            cout << "ID: " << user.id << " | Username: " << user.username << endl;
         }
        }
            
        cout << "\nPASSENGERS:" << endl;
        cout << string(60, '-') << endl;
        for (const auto& user : users) {
            if (user.role == "Passenger") {
            cout << "ID: " << user.id << " | Username: " << user.username << " | Points: " << user.loyaltyPoints << endl;
        }
            }
            break;
        }
        
        case 2: {
            
            cout << "\n----- Add New User -----\n" << endl;
            cout << "1. Passenger" << endl;
            cout << "2. Booking Agent" << endl;
            cout << "3. Administrator" << endl;
            cout << "Enter choice: ";
            
            int typeChoice;
            cin >> typeChoice;
            
            if (typeChoice < 1 || typeChoice > 3) {
                cout << "Invalid choice!" << endl;
                return;
            }
            
            cout << "Enter username: ";
            string newUsername;
            cin >> newUsername;
            
            cout << "Enter password: ";
            string newPassword;
            cin >> newPassword;
            
            cout << "Enter email: ";
            string email;
            cin >> email;
            
            string role = (typeChoice == 1) ? "Passenger" : (typeChoice == 2) ? 
            "BookingAgent" : "Administrator";
            
            UserManagementService::addUser(newUsername, newPassword, role, email);
            break;
        }
        
        case 3: {
        //Delete USer case
        cout << "\n----- Delete User -----\n" << endl;
        cout << "Enter user ID to delete: ";
        int userId;
        cin >> userId;
            
        if (userId == id) {
        cout << "\nError: You cannot delete your own account!" << endl;
        return;}
            
        cout << "Confirm deletion? (y/n): ";
        char confirm;
        cin >> confirm;
            
        if (confirm == 'y' || confirm == 'Y') {
        UserManagementService::deleteUser(userId);
        } else {
            cout << "Deletion cancelled." << endl;
        }
            break;
        }
        
        case 0:
            cout << "Returning to main menu..." << endl;
            break;
            
        default:
            cout << "Invalid choice!" << endl;
    }
}

void Administrator::manageFlights() {
    cout << "\n----- Flight Management -----\n" << endl;
    cout << "1. Add New Flight" << endl;
    cout << "2. Update Existing Flight" << endl;
    cout << "3. Delete Flight" << endl;
    cout << "4. View Flight Details" << endl;
    cout << "5. View All Flights" << endl;
    cout << "0. Back to Main Menu" << endl;
    cout << "\nEnter your choice: ";
    
    int choice;
    cin >> choice;
    
    switch(choice) {    // new flight switch
        case 1: {
        
            cout << "\n===== Add New Flight =====\n" << endl;
            
            cout << "Enter flight number (EX: AA101): ";
            string flightNumber;
            cin >> flightNumber;
            
            // Checking if already there
            if (findFlight(flightNumber) != nullptr) {
                cout << "\nError: Flight " << flightNumber << " already exists!" << endl;
                return;
            }
            
            cout << "Enter origin city: ";
            string origin;
            cin.ignore();
            getline(cin, origin);
            
            cout << "Enter destination city: ";
            string destination;
            getline(cin, destination);
            
            cout << "Enter departure time (e.g., 08:00): ";
            string departureTime;
            getline(cin, departureTime);
            
            cout << "Enter arrival time (e.g., 14:30): ";
            string arrivalTime;
            getline(cin, arrivalTime);
            
            cout << "Enter total seats: ";
            int totalSeats;
            cin >> totalSeats;
            
            cout << "Enter available seats: ";
            int availableSeats;
            cin >> availableSeats;
            
            cout << "Enter aircraft type (EX: Boeing 737): ";
            string aircraftType;
            cin.ignore();
            getline(cin, aircraftType);
            
            cout << "Enter status (Operational/Maintenance/Cancelled): ";
            string status;
            getline(cin, status);
            
            // Create new flight
            json newFlight = {
                {"flightNumber", flightNumber},
                {"origin", origin},
                {"destination", destination},
                {"departureTime", departureTime},
                {"arrivalTime", arrivalTime},
                {"totalSeats", totalSeats},
                {"availableSeats", availableSeats},
                {"aircraftType", aircraftType},
                {"status", status},
                {"createdBy", username}
            };
            
            flightsData.push_back(newFlight);
            saveJSON("data/flights.json", flightsData);
            
            cout << "\n" << string(40, '=') << endl;
            cout << "   FLIGHT ADDED SUCCESSFULLY" << endl;
            cout << string(40, '=') << endl;
            cout << "Flight Number: " << flightNumber << endl;
            cout << "Route: " << origin << " to " << destination << endl;
            cout << "Time: " << departureTime << " - " << arrivalTime << endl;
            cout << string(40, '=') << endl;
            break;
        }
        
        case 2: { //Update Existing Flight
            
            cout << "\n===== Update Flight =====\n" << endl;
            
            cout << "Enter flight number to update: ";
            string flightNumber;
            cin >> flightNumber;
            
            json* flight = findFlight(flightNumber);
            
            if (flight == nullptr) {
                cout << "\nError: Flight not found!" << endl;
                return;
            }
            
            cout << "\n--- Current Flight Details ---" << endl;
            cout << "Flight: " << (*flight)["flightNumber"] << endl;
            cout << "Route: " << (*flight)["origin"] << " → " << (*flight)["destination"] << endl;
            cout << "Departure: " << (*flight)["departureTime"] << endl;
            cout << "Arrival: " << (*flight)["arrivalTime"] << endl;
            cout << "Total Seats: " << (*flight)["totalSeats"] << endl;
            cout << "Available: " << (*flight)["availableSeats"] << endl;
            cout << "Aircraft: " << (*flight)["aircraftType"] << endl;
            cout << "Status: " << (*flight)["status"] << endl;
            
            cout << "\nWhat do u want to update?" << endl;
            cout << "1. Departure Time" << endl;
            cout << "2. Arrival Time" << endl;
            cout << "3. Available Seats" << endl;
            cout << "4. Aircraft Type" << endl;
            cout << "5. Status" << endl;
            cout << "0. Cancel" << endl;
            cout << "\nEnter choice: ";
            
            int updateChoice;
            cin >> updateChoice;
            
            switch(updateChoice) {
                case 1: {
                cout << "Enter new departure time: ";
                string newTime;
                cin.ignore();
                getline(cin, newTime);
                (*flight)["departureTime"] = newTime;
                cout << "Departure time updated to " << newTime << endl;
                break;
                }
                case 2: {
                cout << "Enter new arrival time: ";
                string newTime;
                cin.ignore();
                getline(cin, newTime);
                (*flight)["arrivalTime"] = newTime;
                cout << "Arrival time updated to " << newTime << endl;
                break;
                }
                case 3: {
                 cout << "Enter new available seats: ";
                int newSeats;
                cin >> newSeats;
                (*flight)["availableSeats"] = newSeats;
                cout << "Available seats updated to " << newSeats << endl;
                break;
                }
                case 4: {
                cout << "Enter new aircraft type: ";
                string newAircraft;
                cin.ignore();
                getline(cin, newAircraft);
                (*flight)["aircraftType"] = newAircraft;
                cout << "Aircraft type updated to " << newAircraft << endl;
                    break;
                }
                case 5: {
                cout << "Enter new status (Operational/Maintenance/Cancelled): ";
                string newStatus;
                cin.ignore();
                getline(cin, newStatus);
                    (*flight)["status"] = newStatus;
                cout << "Status updated to " << newStatus << endl;
                break;
                }
                case 0:
                    cout << "Update cancelled." << endl;
                    return;
                default:
                    cout << "Invalid choice!" << endl;
                    return;
            }
            
            (*flight)["lastModifiedBy"] = username;
            saveJSON("data/flights.json", flightsData);
            
            cout << "\nFlight updated successfully!" << endl;
            break;
        }
        
        case 3: {   // Delete Flight
            
            cout << "\n---- Delete Flight ----\n" << endl;
            
            cout << "Enter flight number to delete: ";
            string flightNumber;
            cin >> flightNumber;
            
            json* flight = findFlight(flightNumber);
            
            if (flight == nullptr) {
                cout << "\nError: Flight not found!" << endl;
                return;
            }
            
            // if active 
            int activeReservations = 0;
            for (const auto& res : reservationsData) {
                if (res["flightNumber"] == flightNumber && 
                    (res["status"] == "Confirmed" || res["status"] == "Checked-In")) {
                    activeReservations++;
                }
            }
            
            if (activeReservations > 0) {
                cout << "\nWarning: This flight has " << activeReservations << " active reservations!" << endl;
                cout << "Are you sure you want to delete it? (y/n): ";
                char confirm;
                cin >> confirm;
                
                if (confirm != 'y' && confirm != 'Y') {
                    cout << "Deletion cancelled." << endl;
                    return;
                }
            }
            
            cout << "\nFlight Details:" << endl;
            cout << "Flight: " << (*flight)["flightNumber"] << endl;
            cout << "Route: " << (*flight)["origin"] << " to " << (*flight)["destination"] << endl;
            
            cout << "\nConfirm deletion? (y/n): ";
            char finalConfirm;
            cin >> finalConfirm;
            
            if (finalConfirm != 'y' && finalConfirm != 'Y') {
                cout << "Deletion cancelled." << endl;
                return;
            }
            
            //Remove flight from the array
            for (size_t i = 0; i < flightsData.size(); i++) {
                if (flightsData[i]["flightNumber"] == flightNumber) {
                    flightsData.erase(flightsData.begin() + i);
                    break;
                }
            }
            
            saveJSON("data/flights.json", flightsData);
            
            cout << "\nFlight " << flightNumber << " deleted successfully!" << endl;
            break;
        }
        
        case 4: {
            //Flight Details
            cout << "\n---- Flight Details ----\n" << endl;
            
            cout << "Enter flight number: ";
            string flightNumber;
            cin >> flightNumber;
            
            json* flight = findFlight(flightNumber);
            
            if (flight == nullptr) {
                cout << "\nError: Flight not found!" << endl;
                return;
            }
            
            cout << "\n" << string(50, '=') << endl;
            cout << "        FLIGHT DETAILS" << endl;
            cout << string(50, '=') << endl;
            cout << "Flight Number: " << (*flight)["flightNumber"] << endl;
            cout << "Origin: " << (*flight)["origin"] << endl;
            cout << "Destination: " << (*flight)["destination"] << endl;
            cout << "Departure Time: " << (*flight)["departureTime"] << endl;
            cout << "Arrival Time: " << (*flight)["arrivalTime"] << endl;
            cout << "Total Seats: " << (*flight)["totalSeats"] << endl;
            cout << "Available Seats: " << (*flight)["availableSeats"] << endl;
            cout << "Booked Seats: " << ((*flight)["totalSeats"].get<int>() - (*flight)["availableSeats"].get<int>()) << endl;
            cout << "Aircraft Type: " << (*flight)["aircraftType"] << endl;
            cout << "Status: " << (*flight)["status"] << endl;
            
            if (flight->contains("createdBy")) {
                cout << "Created By: " << (*flight)["createdBy"] << endl;
            }
            if (flight->contains("lastModifiedBy")) {
                cout << "Last Modified By: " << (*flight)["lastModifiedBy"] << endl;
            }
            
            //counters for reservations
            int totalReservations = 0;
            int confirmedReservations = 0;
            int checkedInReservations = 0;
            int cancelledReservations = 0;
            
            for (const auto& res : reservationsData) {
                if (res["flightNumber"] == flightNumber) {
                totalReservations++;
                string status = res["status"];
                if (status == "Confirmed") confirmedReservations++;
                else if (status == "Checked-In") checkedInReservations++;
                else if (status == "Cancelled") cancelledReservations++;
                }
            }
            
            cout << "\nReservation Statistics:" << endl;
            cout << "Total Reservations: " << totalReservations << endl;
            cout << "  - Confirmed: " << confirmedReservations << endl;
            cout << "  - Checked-In: " << checkedInReservations << endl;
            cout << "  - Cancelled: " << cancelledReservations << endl;
            cout << string(50, '=') << endl;
            break;
        }
        
        case 5: {
            // View All Flights
            cout << "\n---- All Flights ----\n" << endl;
            Flight::displayAllFlights(flightsData);
            break;
        }
        
        case 0:
            cout << "Returning to main menu..." << endl;
            break;
            
        default:
            cout << "Invalid choice!" << endl;
    }
}

void Administrator::manageAircraft() {
    cout << "\n===== Aircraft Management =====\n" << endl;
    cout << "1. View All Aircraft Types" << endl;
    cout << "0. Back to Main Menu" << endl;
    cout << "\nEnter your choice: ";
    
    int choice;
    cin >> choice;
    
    if (choice == 1) { //switch for types of aircrafts
        cout << "\n----- All Aircraft Types -----\n" << endl;
        set<string> aircraftTypes;
        for (const auto& flight : flightsData) {
            aircraftTypes.insert(flight["aircraftType"]);
        }
        
        if (aircraftTypes.empty()) {
            cout << "No aircraft types found." << endl;
            return;
        }
        
        cout << "Total types: " << aircraftTypes.size() << endl << string(40, '-') << endl;
        for (const auto& type : aircraftTypes) {
            int count = 0;
            for (const auto& f : flightsData) {
                if (f["aircraftType"] == type) count++;
            }
            cout << type << ": " << count << " flight(s)" << endl;
        }
    } else if (choice == 0) {
        cout << "Returning to main menu..." << endl;
    } else {
        cout << "Invalid choice!" << endl;
    }
}

void Administrator::viewAllReservations() {
    cout << "\n===== All Reservations =====\n" << endl;
    
    if (reservationsData.empty()) {
        cout << "No reservations in the system." << endl;
        return;
    }
    
    cout << "Total reservations: " << reservationsData.size() << endl << string(60, '-') << endl;
    
    for (const auto& res : reservationsData) {
        cout << "ID: " << res["reservationId"] 
             << " | Passenger: " << res["passengerId"]
             << " | Flight: " << res["flightNumber"]
             << " | Seat: " << res["seatNumber"]
             << " | Status: " << res["status"]
             << " | $" << res["totalPrice"] << endl;
    }
}

void Administrator::generateReports() {
    cout << "\n===== Generate Reports =====\n" << endl;
    cout << "1. System Statistics" << endl;
    cout << "0. Back to Main Menu" << endl;
    cout << "\nEnter your choice: ";
    
    int choice;
    cin >> choice;
    
    if (choice == 1) {
        auto stats = ReportService::generateStatistics();
        
        cout << "\n" << string(60, '=') << endl;
        cout << "           SYSTEM STATISTICS" << endl;
        cout << string(60, '=') << endl;
        
        cout << "\n[OVERVIEW]" << endl;
        cout << "Flights: " << stats.totalFlights << endl;
        cout << "Reservations: " << stats.totalReservations << endl;
        cout << "  - Confirmed: " << stats.confirmedReservations << endl;
        cout << "  - Cancelled: " << stats.cancelledReservations << endl;
        
        cout << "\n[REVENUE]" << endl;
        cout << "Total: $" << stats.totalRevenue << endl;
        
        cout << "\n[TOP FLIGHTS]" << endl;
        auto topFlights = ReportService::getTopFlights(5);
        for (const auto& [flight, bookings] : topFlights) {
            cout << flight << ": " << bookings << " bookings" << endl;
        }
        
        cout << string(60, '=') << endl;
    } else if (choice == 0) {
        cout << "Returning to main menu..." << endl;
    } else {
        cout << "Invalid choice!" << endl;
    }
}

void Administrator::manageCrew() {
    cout << "\n===== Crew Management =====\n" << endl;
    cout << "1. View All Pilots" << endl;
    cout << "2. View All Flight Attendants" << endl;
    cout << "3. Assign Crew to Flight" << endl;
    cout << "4. View Flight Crew Assignments" << endl;
    cout << "0. Back to Main Menu" << endl;
    cout << "\nEnter your choice: ";
    
    int choice;
    cin >> choice;
    
    switch(choice) {
        case 1:

        Pilot::displayAllPilots();
        break;
            
        case 2:
        FlightAttendant::displayAllAttendants();
        break;
            
        case 3:
        assignCrewToFlight();
        break;
            
        case 4: {
            
            cout << "\n===== Flight Crew Assignments =====\n" << endl;

            if (flightsData.empty()) {
            cout << "No flights in the system." << endl;
            return;
            }
            
            for (const auto& flight : flightsData) {
                cout << "\nFlight: " << flight["flightNumber"] << " (" << flight["origin"] << " to " 
                << flight["destination"] << ")" << endl;
                
                if (flight.contains("assignedPilotId") && !flight["assignedPilotId"].is_null()) {
                cout << "  Pilot: " << flight["assignedPilotId"] << endl;
                } else {
                    cout << "  Pilot: Not Assigned" << endl;
                }
                
                if (flight.contains("assignedAttendantId") && !flight["assignedAttendantId"].is_null()) {
                    cout << "  Flight Attendant: " << flight["assignedAttendantId"] << endl;
                } else {
                    cout << "  Flight Attendant: Not Assigned" << endl;
                }
            }
            break;
        }
        
        case 0:
            cout << "Returning to main menu..." << endl;
            break;
            
        default:
            cout << "Invalid choice!" << endl;
    }
}

void Administrator::assignCrewToFlight() {
    cout << "\n===== Assign Crew to Flight =====\n" << endl;
    
    
    cout << "Enter Flight Number: ";
    string flightNumber;
    cin >> flightNumber;
    
    json* flight = findFlight(flightNumber);
    if (!flight) {
        cout << "\nFlight not found!" << endl;
        return;
    }
    
    cout << "\nFlight: " << (*flight)["flightNumber"] << endl;
    cout << "Route: " << (*flight)["origin"] << " to " << (*flight)["destination"] << endl;
    cout << "Departure: " << (*flight)["departureTime"] << endl;
    
    
    cout << "\nSelect information to update:" << endl;
    cout << "1. Pilot" << endl;
    cout << "2. Flight Attendant" << endl;
    cout << "3. Both" << endl;
    cout << "0. Cancel" << endl;
    cout << "\nEnter choice: ";
    
    int updateChoice;
    cin >> updateChoice;
    
    if (updateChoice == 0) {
        cout << "Crew assignment cancelled." << endl;
        return;
    }
    
    
    if (updateChoice == 1 || updateChoice == 3) {
        cout << "\n--- Available Pilots ---" << endl;
        int pilotIndex = 1;
        for (const auto& pilot : pilotsData) {
            if (pilot["status"] == "Available") {
                cout << pilotIndex++ << ". " << pilot["pilotId"] << " - " 
                     << pilot["name"] << " (" << pilot["experienceYears"] 
                     << " years exp)" << endl;
            }
        }
        
        if (pilotIndex == 1) {
            cout << "No available pilots." << endl;
        } else {
            cout << "\nSelect Pilot by ID: ";
            string pilotId;
            cin >> pilotId;
            
            
            bool found = false;
            for (const auto& pilot : pilotsData) {
                if (pilot["pilotId"] == pilotId) {
                found = true;
                (*flight)["assignedPilotId"] = pilotId;
                cout << "Pilot " << pilotId << " assigned to Flight " << flightNumber << endl;
                    break;
                }
            }
            
            if (!found) {
                cout << "Invalid Pilot ID!" << endl;
            }
        }
    }
    
    
    if (updateChoice == 2 || updateChoice == 3) {
        cout << "\n--- Available Flight Attendants ---" << endl;
        int attendantIndex = 1;
        for (const auto& attendant : attendantsData) {
            if (attendant["status"] == "Available") {
                cout << attendantIndex++ << ". " << attendant["attendantId"] << " - " 
                     << attendant["name"] << " (" << attendant["certification"] 
                     << ")" << endl;
            }
        }
        
        if (attendantIndex == 1) {
            cout << "No available flight attendants." << endl;
        } else {
            cout << "\nSelect Flight Attendant by ID: ";
            string attendantId;
            cin >> attendantId;
            
            
            bool found = false;
            for (const auto& attendant : attendantsData) {
            if (attendant["attendantId"] == attendantId) {
                found = true;
                (*flight)["assignedAttendantId"] = attendantId;
                cout << "Flight Attendant " << attendantId << " assigned to Flight " 
                    << flightNumber << endl;
                    break;
                }
            }
            
            if (!found) {
                cout << "Invalid Attendant ID!" << endl;
            }
        }
    }
    
    // Save changes
    saveJSON("data/flights.json", flightsData);
    cout << "\nCrew assigned successfully to Flight " << flightNumber << "!" << endl;
}
