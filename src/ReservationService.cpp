#include "../include/ReservationService.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

extern json flightsData;
extern json reservationsData;
extern json usersData;
extern bool saveJSON(const string& filename, const json& data);
extern json* findFlight(const string& flightNumber);
extern json* findReservation(int reservationId);
extern int getNextReservationId();

bool ReservationService::createReservation(
    int passengerId,
    const string& flightNumber,
    const string& seatNumber,
    const string& bookedBy,
    int agentId
) {
    json* flight = findFlight(flightNumber);
    if (flight == nullptr) {
        cout << "\nError: Flight not found!" << endl;
        return false;
    }
    
    if ((*flight)["availableSeats"] <= 0) {
        cout << "\nNo seats available on this flight!" << endl;
        return false;
    }
    
    int totalPrice = calculatePrice();
    int loyaltyPointsEarned = totalPrice * 0.1;
    
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char dateStr[20];
    sprintf(dateStr, "%04d-%02d-%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday);
    
    int reservationId = getNextReservationId();
    
    json newReservation = {
        {"reservationId", reservationId},
        {"passengerId", passengerId},
        {"flightNumber", flightNumber},
        {"seatNumber", seatNumber},
        {"bookingDate", dateStr},
        {"status", "Confirmed"},
        {"totalPrice", totalPrice},
        {"paymentStatus", "Paid"},
        {"loyaltyPointsEarned", loyaltyPointsEarned}
    };
    
    if (!bookedBy.empty()) {
        newReservation["bookedBy"] = bookedBy;
    }
    if (agentId != -1) {
        newReservation["agentId"] = agentId;
    }
    
    reservationsData.push_back(newReservation);
    
    (*flight)["availableSeats"] = (*flight)["availableSeats"].get<int>() - 1;
    
    
    updatePassengerLoyaltyPoints(passengerId, loyaltyPointsEarned);
    
    saveJSON("data/reservations.json", reservationsData);
    saveJSON("data/flights.json", flightsData);
    saveJSON("data/users.json", usersData);
    

    cout << "\n" << string(50, '=') << endl;
    cout << "   RESERVATION CREATED SUCCESSFULLY" << endl;
    cout << string(50, '=') << endl;
    cout << "Reservation ID: " << reservationId << endl;
    cout << "Passenger ID: " << passengerId << endl;
    cout << "Flight: " << flightNumber << endl;
    cout << "Seat: " << seatNumber << endl;
    cout << "Total: $" << totalPrice << endl;
    cout << "Loyalty Points Earned: " << loyaltyPointsEarned << endl;
    if (!bookedBy.empty()) {
        cout << "Booked by Agent: " << bookedBy << endl;
    }
    cout << string(50, '=') << endl;
    
    return true;
}

int ReservationService::calculatePrice() {
    int basePrice = 500;
    int variablePrice = rand() % 500;
    return basePrice + variablePrice;
}

void ReservationService::updatePassengerLoyaltyPoints(int passengerId, int points) {
    for (auto& user : usersData) {
        if (user["id"] == passengerId && user["role"] == "Passenger") {
            if (user.contains("loyaltyPoints")) {
                user["loyaltyPoints"] = user["loyaltyPoints"].get<int>() + points;
            } else {
                user["loyaltyPoints"] = points;
            }
            break;
        }
    }
}

vector<ReservationInfo> ReservationService::getPassengerReservations(int passengerId) {
    vector<ReservationInfo> result;
    
    for (const auto& res : reservationsData) {
        if (res["passengerId"] == passengerId) {
            ReservationInfo info;
            info.reservationId = res["reservationId"];
            info.flightNumber = res["flightNumber"];
            info.seatNumber = res["seatNumber"];
            info.bookingDate = res["bookingDate"];
            info.status = res["status"];
            info.totalPrice = res["totalPrice"];
            info.isPaid = res.contains("isPaid") ? res["isPaid"].get<bool>() : false;
            result.push_back(info);
        }
    }
    
    return result;
}

vector<json*> ReservationService::getActiveReservations(int passengerId) {
    vector<json*> result;
    
    for (auto& res : reservationsData) {
        if (res["passengerId"] == passengerId) {
            string status = res["status"];
            if (status != "Cancelled") {
                result.push_back(&res);
            }
        }
    }
    
    return result;
}

vector<json*> ReservationService::getConfirmedReservations(int passengerId) {
    vector<json*> result;
    
    for (auto& res : reservationsData) {
        if (res["passengerId"] == passengerId && res["status"] == "Confirmed") {
            result.push_back(&res);
        }
    }
    
    return result;
}

bool ReservationService::changeSeat(int reservationId, int passengerId, const string& newSeat) {
    json* reservation = findReservation(reservationId);
    
    if (reservation == nullptr || (*reservation)["passengerId"] != passengerId) {
        cout << "\nError: Reservation not found or doesn't belong to you!\n" << endl;
        return false;
    }
    
    string status = (*reservation)["status"];
    if (status == "Checked-In") {
        cout << "\nSorry, you cannot change seat after check-in.\n" << endl;
        return false;
    }
    
    if (status == "Cancelled") {
        cout << "\nCannot change seat for a cancelled reservation.\n" << endl;
        return false;
    }
    
    (*reservation)["seatNumber"] = newSeat;

    return saveJSON("data/reservations.json", reservationsData);
}

bool ReservationService::cancelReservation(int reservationId, int passengerId, int& refundAmount, int& loyaltyPointsLost) {
    json* reservation = findReservation(reservationId);
    
    if (reservation == nullptr || (*reservation)["passengerId"] != passengerId) {
        cout << "\nError: Reservation not found or doesn't belong to you!\n" << endl;
        return false;
    }
    
    string status = (*reservation)["status"];
    if (status == "Cancelled") {
        cout << "\nThis reservation is already cancelled.\n" << endl;
        return false;
    }
    
    refundAmount = (*reservation)["totalPrice"];
    loyaltyPointsLost = 0;
    if (reservation->contains("loyaltyPointsEarned")) {
        loyaltyPointsLost = (*reservation)["loyaltyPointsEarned"];
    }
    
    string flightNumber = (*reservation)["flightNumber"];
    json* flight = findFlight(flightNumber);
    if (flight != nullptr) {
        (*flight)["availableSeats"] = (*flight)["availableSeats"].get<int>() + 1;
    }
    

    (*reservation)["status"] = "Cancelled";
    //or
    (*reservation)["paymentStatus"] = "Refunded";
    
    
    bool saved = saveJSON("data/reservations.json", reservationsData) &&
                 saveJSON("data/flights.json", flightsData);
    
    return saved;
}
