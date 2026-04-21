#ifndef BOOKINGAGENT_H
#define BOOKINGAGENT_H
#include "User.h"
#include <string>
using namespace std;
class BookingAgent : public User {
    public:
        BookingAgent(int id , const string&username , const string& password):
            User(id, username, password, "BookingAgent") {}


        //Functions from USER class    

        void displayMenu() override;
        void performAction(int choice) override;


        //this class functions 
        
        void searchFlights();
        void createReservation();
        void processPayment();
        void checkInPassenger();
        void viewReservations();

};

#endif