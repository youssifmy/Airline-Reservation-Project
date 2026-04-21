#include "../include/Aircraft.h"
#include <iostream>
using namespace std;

bool Aircraft::isAvailable() const {
    return maintenanceStatus == "Ready To Fly";
}

void Aircraft::displayAircraftInfo() const {
    cout << "Aircraft ID: " << aircraftId << endl;
    cout << "Model: " << model << endl;
    cout << "Total Capacity: " << totalCapacity << "Seats" << endl;
    cout << "Maintenance Status: " << maintenanceStatus << endl;
    cout << "Last Maintenance Date: " << lastmaintenanceDate << endl;
    cout << "Next Maintenance Date: " << nextmaintenanceDate << endl;
}