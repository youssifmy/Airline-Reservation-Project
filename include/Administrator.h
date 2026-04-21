#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "User.h"
#include <string>
using namespace std;

class Administrator : public User {
public:
    Administrator(int id, const string& username, const string& password)
    : User(id, username, password, "Administrator") {}

    void displayMenu() override;
    void performAction(int choice) override;

    void manageUsers();
    void manageFlights();
    void manageAircraft();
    void viewAllReservations();
    void generateReports();
    void manageCrew();
    void assignCrewToFlight();
};

#endif