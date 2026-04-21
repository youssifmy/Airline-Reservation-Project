#ifndef PASSENGER_H
#define PASSENGER_H

#include "User.h"
#include <string>
using namespace std;

class Passenger : public User {
private:
    int loyaltyPoints;
    string frequentFlyerNumber;
    
public:
    
    Passenger(int id, const string& username, const string& password, 
    int loyaltyPoints = 0, const string& frequentFlyerNumber = "")
    : User(id, username, password, "Passenger"), loyaltyPoints(loyaltyPoints), 
    frequentFlyerNumber(frequentFlyerNumber) {}
    
    //functions from user class
    void displayMenu() override;
    void performAction(int choice) override;


    
    // Getters

    int getLoyaltyPoints() const { 
        return loyaltyPoints; 
    }
    
    string getFrequentFlyerNumber() const { 
        return frequentFlyerNumber; 
    }
    
    // Setters

    void addLoyaltyPoints(int points) { 
        loyaltyPoints += points; 
    }
    
    void setFrequentFlyerNumber(const string& number) { 
        frequentFlyerNumber = number; 
    }
    
    //Passenger specific functions
    void searchFlights();
    void bookFlight();
    void viewMyReservations();
    void selectSeat();
    void onlineCheckIn();
    void cancelReservation();
};

#endif
