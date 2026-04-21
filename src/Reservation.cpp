#include"../include/Reservation.h"
#include<iostream>
using namespace std;

void Reservation::cancelReservation(){
    if(status != "Cancelled"){
        setStatus("Cancelled");
        cout << "... Reservation cancelled successfully " << endl;
    }else{
        cout << "Reservation is Already cancelled" << endl;
    }
}


void Reservation::displayReservationInfo() const{
    cout << "========== RESERVATION DETAILS =========="<< endl;
    cout << "Reservation-ID: " << reservationId << endl;
    cout << "Passenger-ID: " << passengerId << endl;
    cout << "Flight-Number: " << flightNumber << endl;
    cout << "SeatNumber: " << seatNumber << endl;
    cout << "BookingDate: " << bookingDate << endl;
    cout << "Status: " << status << endl;
    cout << "TotalPrice: " << totalPrice << endl;
    cout << "IsPaid: " << isPaid << endl;
    cout << "=========================================" << endl;

}