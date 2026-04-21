#include "../include/Pilot.h"
#include "../include/json.hpp"
#include <iostream>
#include <iomanip>

using namespace std;
using json = nlohmann::json;

extern json pilotsData;

void Pilot::displayPilotDetails() const {
    cout << "\n=== Pilot Details ===" << endl;
    cout << "Pilot ID: " << pilotId << endl;
    cout << "Name: " << name << endl;
    cout << "License: " << licenseNumber << endl;
    cout << "Experience: " << experienceYears << " years" << endl;
    cout << "Status: " << status << endl;
}

void Pilot::displayAllPilots() {
    if (pilotsData.empty()) {
        cout << "\nNo pilots in the system." << endl;
        return;
    }

    cout << "\n========== All Pilots ==========\n" << endl;
    cout << left << setw(12) << "Pilot ID" 
         << setw(25) << "Name" 
         << setw(15) << "License"
         << setw(12) << "Experience"
         << setw(15) << "Status" << endl;
    cout << string(79, '-') << endl;

    for (const auto& pilot : pilotsData) {
        cout << left << setw(12) << pilot["pilotId"].get<string>()
             << setw(25) << pilot["name"].get<string>()
             << setw(15) << pilot["licenseNumber"].get<string>()
             << setw(12) << (to_string(pilot["experienceYears"].get<int>()) + " yrs")
             << setw(15) << pilot["status"].get<string>() << endl;
    }
    cout << "\nTotal Pilots: " << pilotsData.size() << endl;
}
