#ifndef RESERVATIONSERVICE_H
#define RESERVATIONSERVICE_H

#include "json.hpp"
#include <string>
#include <vector>

using json = nlohmann::json;
using namespace std;

struct ReservationInfo {
    int reservationId;
    string flightNumber;
    string seatNumber;
    string bookingDate;
    string status;
    int totalPrice;
    bool isPaid;
};

class ReservationService {
public:
    
    static bool createReservation(
        int passengerId,
        const string& flightNumber,
        const string& seatNumber,
        const string& bookedBy = "",
        int agentId = -1
    );
    
    
    static int calculatePrice();
    static void updatePassengerLoyaltyPoints(int passengerId, int points);
    
    static vector<ReservationInfo> getPassengerReservations(int passengerId);
    
    static vector<json*> getActiveReservations(int passengerId);
    static vector<json*> getConfirmedReservations(int passengerId);
    static bool changeSeat(int reservationId, int passengerId, const string& newSeat);
    
    static bool cancelReservation(int reservationId, int passengerId, int& refundAmount, int& loyaltyPointsLost);
};

#endif
