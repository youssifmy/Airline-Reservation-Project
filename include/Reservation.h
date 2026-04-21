#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>
using namespace std;

class Reservation {
    private:
        int reservationId;
        int passengerId;
        string flightNumber;
        string seatNumber;
        string bookingDate;
        string status;
        double totalPrice;
        bool isPaid;

    public:
        Reservation(int reservationId, int passengerId, const string& flightNumber,
             const string& seatNumber, const string& bookingDate, const string& status, 
             double totalPrice, bool isPaid): reservationId(reservationId), 
             passengerId(passengerId), flightNumber(flightNumber), 
              seatNumber(seatNumber), bookingDate(bookingDate), status(status), 
              totalPrice(totalPrice), isPaid(isPaid) {}

        //getters
        int getReservationId() const {
            return reservationId;
        }

        int getPassengerId() const {
            return passengerId;
        }

        string getFlightNumber() const {
            return flightNumber;
        }

        string getSeatNumber() const {
            return seatNumber;
        }

        string getBookingDate() const {
            return bookingDate;
        }

        string getStatus() const {
            return status;
        }

        double getTotalPrice() const {
            return totalPrice;
        }

        bool getIsPaid() const {
            return isPaid;
        }

        //setters

        void setStatus(const string& newStatus) {
            status = newStatus;
        }

        void setIsPaid(bool paymentStatus) {
            isPaid = paymentStatus;
        }

        void setSeatNumber(const string& newSeatNumber) {
            seatNumber = newSeatNumber;
        }

        //class functions

        void displayReservationInfo() const;

        void cancelReservation();

};

#endif
