#include "../include/BookingAgent.h"
#include "../include/Flight.h"
#include "../include/FlightService.h"
#include "../include/ReservationService.h"
#include "../include/CheckInService.h"
#include "../include/PaymentService.h"
#include "../include/json.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;
using json = nlohmann::json;

// declaretions for main

//the data variables used for json files
extern json flightsData;
extern json reservationsData;
extern json usersData;
extern bool saveJSON(const string& filename, const json& data);
extern json* findFlight(const string& flightNumber);
extern json* findReservation(int reservationId);
extern int getNextReservationId();

void BookingAgent::displayMenu() {
    cout << "---------- Booking Agent Menu ----------"<< endl;
    cout << "1. Search Flights "<< endl;
    cout << "2. Create Reservation" << endl;
    cout << "3. Process Payment" << endl;
    cout << "4. Check-In Passenger" << endl;
    cout << "5. View Reservations" << endl;
    cout << "0. Logout" << endl;
    cout << "Enter your choice: ";
}

void BookingAgent::performAction(int choice) {
    switch (choice) {
        case 1:
            searchFlights();
            break;
        case 2:
            createReservation();
            break;
        case 3:
            processPayment();
            break;
        case 4:
            checkInPassenger();
            break;
        case 5:
            viewReservations();
            break;
        case 0:
            cout << "Logging out..." << endl;
            break;
        default:
            cout << "Invalid choice " << endl;
    }
}

void BookingAgent::searchFlights() {
    
    FlightService::searchFlights(flightsData);
}

void BookingAgent::createReservation() {
    cout << "\n===== Create Reservation for Passenger =====\n" << endl;
    
    cout << "Enter passenger username: ";
    string passengerUsername;
    cin >> passengerUsername;
    
    json* passengerData = nullptr;
    for (auto& user : usersData) {
        if (user["username"] == passengerUsername && user["role"] == "Passenger") {
        passengerData = &user;
        break;
        }
    }
    
    if (passengerData == nullptr) {
        cout << "\nPassenger not found!" << endl;
        return;
    }
    
    cout << "\nPassenger found: " << (*passengerData)["username"] << endl;
    cout << "Passenger ID: " << (*passengerData)["id"] << endl;

    cout << "\n========== Available Flights ==========" << endl;
    Flight::searchAvailableFlights(flightsData);

    cout << "\nEnter flight number to book: ";
    string flightNumber;
    cin >> flightNumber;
    
    json* flight = findFlight(flightNumber);
    if (flight == nullptr) {
        cout << "\nFlight not found!" << endl;
        return;
    }
    
    if ((*flight)["availableSeats"] <= 0) {
        cout << "\nNo seats available on this flight!" << endl;
        return;
    }
    
    //flight details
    cout << "\n--- Flight Details ---" << endl;
    cout << "Flight: " << (*flight)["flightNumber"] << endl;
    cout << "From: " << (*flight)["origin"] << " To: " << (*flight)["destination"] << endl;
    cout << "Available Seats: " << (*flight)["availableSeats"] << endl;
    
    
    cout << "\nEnter seat number (EX: 12A): ";
    string seatNumber;
    cin >> seatNumber;
    

    int estimatedPrice = ReservationService::calculatePrice();
    cout << "\nEstimated Total Price: $" << estimatedPrice << endl;
    
    //Confirm booking
    char confirm;
    cout << "\nConfirm booking? (y/n): ";
    cin >> confirm;
    
    if (confirm != 'y' && confirm != 'Y') {
        cout << "Booking cancelled." << endl;
        return;
    }
    
    
    bool success = ReservationService::createReservation(
        (*passengerData)["id"],
        flightNumber,
        seatNumber,
        username,  // agent who booked it
        id         // agent ID
    );
    
    if (!success) {
        cout << "\nReservation creation failed!" << endl;
    }
}

void BookingAgent::processPayment() {
    cout << "\n===== Process Payment =====\n" << endl;
    
    
    vector<json*> unpaidReservations = PaymentService::findUnpaidReservations();
    
    if (unpaidReservations.empty()) {
        cout << "No unpaid reservations found." << endl;
        return;
    }
    
    cout << "Unpaid Reservations:" << endl;
    cout << "--------------------" << endl;
    
    for (size_t i = 0; i < unpaidReservations.size(); i++) {
        json& res = *unpaidReservations[i];
        cout << (i + 1) << ". Reservation ID: " << res["reservationId"] << endl;
        cout << "   Passenger ID: " << res["passengerId"] << endl;
        cout << "   Flight: " << res["flightNumber"] << endl;
        cout << "   Amount: $" << res["totalPrice"] << endl;
        cout << "   Status: " << res["paymentStatus"] << endl;
        cout << endl;
    }
    
    int choice;
    cout << "Enter reservation number to process payment (0 to cancel): ";
    cin >> choice;
    
    if (choice == 0) {
        cout << "payment cancelled." << endl;
        return;
    }
    
    if (choice < 1 || choice > static_cast<int>(unpaidReservations.size())) {
        cout << "Invalid selection." << endl;
        return;
    }
    
    json& selectedReservation = *unpaidReservations[choice - 1];
    
    
    cout << "\nProcessing payment of $" << selectedReservation["totalPrice"] << "..." << endl;
    cout << "Enter payment method (Credit/Debit/Cash): ";
    string paymentMethod;
    cin >> paymentMethod;
    
    
    bool success = PaymentService::processPayment(selectedReservation, paymentMethod, username);
    
    if (success) {
        PaymentService::displayPaymentConfirmation(selectedReservation, paymentMethod);
    } else {
        cout << "\nPayment processing failed!" << endl;
    }
}

void BookingAgent::checkInPassenger() {
    cout << "\n===== Check-In Passenger =====\n" << endl;
    
    cout << "Enter reservation ID: ";
    int reservationId;
    cin >> reservationId;
    
    json* reservation = findReservation(reservationId);
    
    if (reservation == nullptr) {
        cout << "\nReservation not found!" << endl;
        return;
    }
    
    //before the check-in
    cout << "\n--- Reservation Details ---" << endl;
    cout << "Reservation ID: " << (*reservation)["reservationId"] << endl;
    cout << "Passenger ID: " << (*reservation)["passengerId"] << endl;
    cout << "Flight: " << (*reservation)["flightNumber"] << endl;
    cout << "Seat: " << (*reservation)["seatNumber"] << endl;
    cout << "Current Status: " << (*reservation)["status"] << endl;
    
    char confirm;
    cout << "\nConfirm check-in? (y/n): ";
    cin >> confirm;
    
    if (confirm != 'y' && confirm != 'Y') {
        cout << "Check-in cancelled." << endl;
        return;
    }
    
    bool success = CheckInService::checkInByReservationId(reservationId, username);
    
    if (success) {
        CheckInService::displayBoardingPass(*reservation);
        cout << "\nCheck-in completed successfully!" << endl;
    }
}

void BookingAgent::viewReservations() {
    cout << "\n===== View Reservations =====\n" << endl;
    
    cout << "1. View All Reservations" << endl;
    cout << "2. View My Bookings (created by me)" << endl;
    cout << "3. Search by Reservation ID" << endl;
    cout << "0. Back to Main Menu" << endl;
    cout << "\nEnter your choice: ";
    
    int choice;
    cin >> choice;
    
    switch(choice) {
        case 1: {
         cout << "\n========== All Reservations ==========" << endl;
            if (reservationsData.empty()) {
                cout << "No reservations found." << endl;
                return;
            }
            
            cout << "Total: " << reservationsData.size() << " reservations" << endl << string(50, '-') << endl;
            for (const auto& res : reservationsData) {
                cout << "ID:" << res["reservationId"] << " | Pass:" << res["passengerId"] 
                     << " | Flight:" << res["flightNumber"] << " | Seat:" << res["seatNumber"]
                     << " | " << res["status"] << " | $" << res["totalPrice"] << endl;
            }
            break;
        }
        
        case 2: {  // reservation by the agent
            
            cout << "\n========== My Bookings ==========" << endl;
            int count = 0;
            
            for (const auto& res : reservationsData) {
                if (res.contains("agentId") && res["agentId"] == id) {
                    count++;
                    cout << "ID:" << res["reservationId"] << " | Pass:" << res["passengerId"] 
                         << " | Flight:" << res["flightNumber"] << " | " << res["status"] 
                         << " | $" << res["totalPrice"] << endl;
                }
            }
            
            if (count == 0) {
                cout << "You haven't created any bookings yet." << endl;
            } else {
                cout << string(50, '-') << endl << "Total: " << count << " bookings" << endl;
            }
            break;
        }
        
        case 3: {
            
            cout << "\nEnter Reservation ID: ";
            int resId;
            cin >> resId;
            
            json* res = findReservation(resId);
            
            if (res == nullptr) {
                cout << "\nReservation not found!" << endl;
                return;
            }
            
            cout << "\n========== Reservation Details ==========" << endl;
            cout << "ID: " << (*res)["reservationId"] << endl;
            cout << "Passenger ID: " << (*res)["passengerId"] << endl;
            cout << "Flight: " << (*res)["flightNumber"] << endl;
            cout << "Seat: " << (*res)["seatNumber"] << endl;
            cout << "Date: " << (*res)["bookingDate"] << endl;
            cout << "Status: " << (*res)["status"] << endl;
            cout << "Payment Status: " << (*res)["paymentStatus"] << endl;
            cout << "Total Price: $" << (*res)["totalPrice"] << endl;
            if (res->contains("bookedBy")) {
                cout << "Booked by: " << (*res)["bookedBy"] << endl;
            }
            if (res->contains("checkedInBy")) {
                cout << "Checked in by: " << (*res)["checkedInBy"] << endl;
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