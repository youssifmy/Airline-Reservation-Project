#include "../include/CheckInService.h"
#include <iostream>


extern json reservationsData;
extern bool saveJSON(const string& filename, const json& data);
extern json* findReservation(int reservationId);

bool CheckInService::checkInByReservationId(int reservationId, const string& checkedInBy) {
    json* reservation = findReservation(reservationId);
    
    if (reservation == nullptr) {
        cout << "\nReservation not found!" << endl;
        return false;
    }
    
    
    if ((*reservation)["status"] == "Checked-In") {
        cout << "\nPassenger is already checked in!" << endl;
        return false;
    }
    
    if ((*reservation)["status"] == "Cancelled") {
        cout << "\nThis reservation has been cancelled!" << endl;
        return false;
    }
    
    (*reservation)["status"] = "Checked-In";
    
    if (!checkedInBy.empty()) {
        (*reservation)["checkedInBy"] = checkedInBy;
    }

    saveJSON("data/reservations.json", reservationsData);
    
    return true;
}

void CheckInService::displayBoardingPass(const json& reservation, const string& passengerName) {
    cout << "\n" << string(50, '=') << endl;
    cout << "    BOARDING PASS" << endl;
    cout << string(50, '=') << endl;
    
    if (!passengerName.empty()) {
        cout << "Passenger: " << passengerName << endl;
    } else {
        cout << "Passenger ID: " << reservation["passengerId"] << endl;
    }
    
    cout << "Flight Number: " << reservation["flightNumber"] << endl;
    cout << "Seat Number: " << reservation["seatNumber"] << endl;
    cout << "Booking Date: " << reservation["bookingDate"] << endl;
    cout << "Status: CHECKED-IN" << endl;
    
    if (reservation.contains("checkedInBy")) {
        cout << "Checked in by: " << reservation["checkedInBy"] << endl;
    }
    
    cout << string(50, '=') << endl;
    cout << "\nPlease arrive at the gate before departure." << endl;
    cout << "Have a Good flight!" << endl;
    cout << string(50, '=') << endl;
}
