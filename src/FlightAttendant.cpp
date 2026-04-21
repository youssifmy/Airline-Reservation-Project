#include "../include/FlightAttendant.h"
#include "../include/json.hpp"
#include <iostream>
#include <iomanip>

using namespace std;
using json = nlohmann::json;

extern json attendantsData;

void FlightAttendant::displayAttendantDetails() const {
    cout << "\n=== Flight Attendant Details ===" << endl;
    cout << "Attendant ID: " << attendantId << endl;
    cout << "Name: " << name << endl;
    cout << "Certification: " << certification << endl;
    cout << "Service Years: " << yearsOfService << " years" << endl;
    cout << "Status: " << status << endl;
}

void FlightAttendant::displayAllAttendants() {
    if (attendantsData.empty()) {
        cout << "\nNo flight attendants in the system." << endl;
        return;
    }

    cout << "\n========== All Flight Attendants ==========\n" << endl;
    cout << left << setw(15) << "Attendant ID" 
         << setw(25) << "Name" 
         << setw(20) << "Certification"
         << setw(12) << "Service"
         << setw(15) << "Status" << endl;
    cout << string(87, '-') << endl;

    for (const auto& attendant : attendantsData) {
        cout << left << setw(15) << attendant["attendantId"].get<string>()
             << setw(25) << attendant["name"].get<string>()
             << setw(20) << attendant["certification"].get<string>()
             << setw(12) << (to_string(attendant["yearsOfService"].get<int>()) + " yrs")
             << setw(15) << attendant["status"].get<string>() << endl;
    }
    cout << "\nTotal Attendants: " << attendantsData.size() << endl;
}
