#include "../include/Passenger.h"
#include "../include/Flight.h"
#include "../include/Reservation.h"
#include "../include/Payment.h"
#include "../include/FlightService.h"
#include "../include/ReservationService.h"
#include "../include/CheckInService.h"
#include "../include/json.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;
using json = nlohmann::json;


extern json flightsData;
extern json reservationsData;
extern void saveAllData();
extern bool saveJSON(const string& filename, const json& data);
extern json* findFlight(const string& flightNumber);
extern json* findReservation(int reservationId);
extern int getNextReservationId();

void Passenger::displayMenu(){
    cout <<"----------Passenger Menu----------" << endl;
    cout << "1. Search Flights" << endl;
    cout << "2. Book Flight" << endl;
    cout << "3. View My Reservations" << endl;
    cout << "4. Select Seat" << endl;
    cout << "5. Online Check-In" << endl;
    cout << "6. Cancel Reservation" << endl;
    cout << "0. Logout" << endl;
    cout << "Enter your choice: ";

}

void Passenger::performAction(int choice){
    switch (choice)
    {
    case 1:
        searchFlights();
        break;
    case 2:
        bookFlight();
        break;
    case 3:
        viewMyReservations();
        break;
    case 4:
        selectSeat();
        break;
    case 5:
        onlineCheckIn();
        break;
    case 6:
        cancelReservation();
        break;
    case 0:
        cout <<"Logging Out..." << endl;
        break;

    
    
    
    default:
        cout << "Invalid Choice" << endl;
        break;
    }

}

void Passenger::searchFlights() {
    FlightService::searchFlights(flightsData);
}

void Passenger::bookFlight() {
    cout << "\n========== BOOK A FLIGHT ==========\n" << endl;
    
    Flight::searchAvailableFlights(flightsData);   //show the flights
    
    cout << "\nEnter flight number to book (or 0 to cancel): ";
    string flightNumber;
    cin >> flightNumber;
    
    if (flightNumber == "0") {
        cout << "Booking cancelled.\n" << endl;
        return;
    }
    
    cout << "Enter seat number (Ex: 12A, 8C): ";
    string seatNumber;
    cin >> seatNumber;
    
    
    int estimatedPrice = ReservationService::calculatePrice();
    cout << "\nEstimated Price: $" << estimatedPrice << endl;
    
    cout << "\nConfirm booking? (1=Yes, 0=No): ";
    int confirm;
    cin >> confirm;
    
    if (confirm != 1) {
        cout << "Booking cancelled.\n" << endl;
        return;
    }
    
    bool success = ReservationService::createReservation(getId(), flightNumber, seatNumber);
    
    if (success) {
        addLoyaltyPoints(estimatedPrice * 0.1);
        cout << "\nYour e-ticket has been sent to your email.\n" << endl;
    }
}

void Passenger::viewMyReservations() {
    cout << "\n========== MY RESERVATIONS ==========\n" << endl;
    

    vector<ReservationInfo> reservations = ReservationService::getPassengerReservations(getId());
    
    if (reservations.empty()) {
        cout << "You have no reservations yet." << endl;
        cout << "Book your first flight to start your journey!\n" << endl;
    } else {
        for (const auto& res : reservations) {
            cout << "Reservation ID: " << res.reservationId << endl;
            cout << "Flight: " << res.flightNumber << endl;
            cout << "Seat: " << res.seatNumber << endl;
            cout << "Booking Date: " << res.bookingDate << endl;
            cout << "Status: " << res.status << endl;
            cout << "Price: $" << res.totalPrice << endl;
            cout << "Payment: " << (res.isPaid ? "Paid" : "Pending") << endl;
            cout << "----------------------------------------" << endl;
        }
    }
    
    cout << "\nYour Loyalty Points: " << getLoyaltyPoints() << endl;
    cout << "Frequent Flyer Number: " << getFrequentFlyerNumber() << "\n" << endl;
}

void Passenger::selectSeat() {
    cout << "\n========== SELECT/CHANGE SEAT ==========\n" << endl;
    
    vector<json*> activeReservations = ReservationService::getActiveReservations(getId());
    
    if (activeReservations.empty()) {
        cout << "You have no active reservations." << endl;
        cout << "Please book a flight first.\n" << endl;
        return;
    }
    
    cout << "Your Active Reservations:\n" << endl;
    for (const auto& res : activeReservations) {
        cout << "Reservation ID: " << (*res)["reservationId"] << endl;
        cout << "Flight: " << (*res)["flightNumber"] << endl;
        cout << "Current Seat: " << (*res)["seatNumber"] << endl;
        cout << "Status: " << (*res)["status"] << endl;
        cout << "----------------------------------------" << endl;
    }
    
    cout << "\nEnter Reservation ID to change seat (or 0 to cancel): ";
    int resId;
    cin >> resId;
    
    if (resId == 0) {
        cout << "Operation cancelled.\n" << endl;
        return;
    }
    
    cout << "Enter new seat number: ";
    string newSeat;
    cin >> newSeat;
    
    cout << "\nConfirm seat change? (1=Yes, 0=No): ";
    int confirm;
    cin >> confirm;
    
    if (confirm != 1) {
        cout << "Seat change cancelled.\n" << endl;
        return;
    }
    
    bool success = ReservationService::changeSeat(resId, getId(), newSeat);
    
    if (success) {
        cout << "\n Seat changed successfully!" << endl;
        cout << "Your new seat: " << newSeat << endl;
        cout << "Updated e-ticket has been sent to your email.\n" << endl;
    }
}

void Passenger::onlineCheckIn() {
    cout << "\n===== Online Check-In =====\n" << endl;
    
    vector<json*> eligibleReservations = ReservationService::getConfirmedReservations(getId());
    
    if (eligibleReservations.empty()) {
        cout << "You have no confirmed reservations available for check-in." << endl;
        return;
    }
    
    cout << "Your Confirmed Reservations:" << endl;
    cout << "----------------------------" << endl;
    for (size_t i = 0; i < eligibleReservations.size(); i++) {
        json& res = *eligibleReservations[i];
        cout << (i + 1) << ". Reservation ID: " << res["reservationId"] << endl;
        cout << "   Flight Number: " << res["flightNumber"] << endl;
        cout << "   Seat: " << res["seatNumber"] << endl;
        cout << "   Date: " << res["bookingDate"] << endl;
        cout << endl;
    }
    
    int choice;
    cout << "Enter the number of the reservation to check-in (0 to cancel): ";
    cin >> choice;
    
    if (choice == 0 || choice < 1 || choice > static_cast<int>(eligibleReservations.size())) {
        cout << "Check-in cancelled." << endl;
        return;
    }
    
    json& selectedReservation = *eligibleReservations[choice - 1];

    cout << "\nConfirm check-in for Flight " << selectedReservation["flightNumber"] << "? (y/n): ";
    char confirm;
    cin >> confirm;
    
    if (confirm != 'y' && confirm != 'Y') {
        cout << "Check-in cancelled." << endl;
        return;
    }
    
    bool success = CheckInService::checkInByReservationId(selectedReservation["reservationId"]);
    
    if (success) {
        CheckInService::displayBoardingPass(selectedReservation, username);
        cout << "\nCheck-in completed successfully!" << endl;
    }
}

void Passenger::cancelReservation() {
    cout << "\n===== Cancel Reservation =====\n" << endl;
    
    vector<json*> activeReservations = ReservationService::getActiveReservations(getId());
    
    if (activeReservations.empty()) {
        cout << "You have no active reservations to cancel." << endl;
        return;
    }
    
    cout << "Your Active Reservations:" << endl;
    cout << "-------------------------" << endl;
    for (size_t i = 0; i < activeReservations.size(); i++) {
        json& res = *activeReservations[i];
        cout << (i + 1) << ". Reservation ID: " << res["reservationId"] << endl;
        cout << "   Flight Number: " << res["flightNumber"] << endl;
        cout << "   Seat: " << res["seatNumber"] << endl;
        cout << "   Status: " << res["status"] << endl;
        cout << "   Total Price: $" << res["totalPrice"] << endl;
        cout << endl;
    }
    
    int choice;
    cout << "Enter the number of the reservation to cancel (0 to go back): ";
    cin >> choice;
    
    if (choice == 0 || choice < 1 || choice > static_cast<int>(activeReservations.size())) {
        cout << "Cancellation cancelled." << endl;
        return;
    }
    
    json& selectedReservation = *activeReservations[choice - 1];
    int resId = selectedReservation["reservationId"];
    int totalPrice = selectedReservation["totalPrice"];
    
    cout << "\n===== Cancellation Details =====" << endl;
    cout << "Reservation ID: " << resId << endl;
    cout << "Flight Number: " << selectedReservation["flightNumber"] << endl;
    cout << "Seat Number: " << selectedReservation["seatNumber"] << endl;
    cout << "Refund Amount: $" << totalPrice << endl;
    cout << "================================\n" << endl;
    
    char confirm;
    cout << "Are you sure you want to cancel this reservation? (y/n): ";
    cin >> confirm;
    
    if (confirm != 'y' && confirm != 'Y') {
        cout << "Cancellation cancelled." << endl;
        return;
    }

    int refundAmount = 0;
    int loyaltyPointsLost = 0;
    bool success = ReservationService::cancelReservation(resId, getId(), refundAmount, loyaltyPointsLost);
    
    if (success) {
        loyaltyPoints = max(0, loyaltyPoints - loyaltyPointsLost);

        cout << "\n" << string(50, '=') << endl;
        cout << "   RESERVATION CANCELLED SUCCESSFULLY" << endl;
        cout << string(50, '=') << endl;
        cout << "Refund of $" << refundAmount << " will be processed." << endl;
        if (loyaltyPointsLost > 0) {
            cout << "Loyalty points deducted: " << loyaltyPointsLost << endl;
            cout << "Current loyalty points: " << loyaltyPoints << endl;
        }
        cout << "Please allow 5-7 business days for the refund." << endl;
        cout << string(50, '=') << endl;
        cout << "\nCancellation completed successfully!" << endl;
    }
}
