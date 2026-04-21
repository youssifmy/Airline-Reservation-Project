#ifndef PILOT_H
#define PILOT_H

#include <string>
using namespace std;

class Pilot {
private:
    string pilotId;
    string name;
    string licenseNumber;
    int experienceYears;
    string status; 

public:
    Pilot(const string& pilotId, const string& name, const string& licenseNumber,
    int experienceYears, const string& status = "Available")
    : pilotId(pilotId), name(name), licenseNumber(licenseNumber),experienceYears(experienceYears), status(status) {}

    // Getters
    string getPilotId() const {
        return pilotId;
    }

    string getName() const {
        return name;
    }

    string getLicenseNumber() const {
        return licenseNumber;
    }

    int getExperienceYears() const {
        return experienceYears;
    }

    string getStatus() const {
        return status;
    }

    // Setters
    void setStatus(const string& newStatus) {
        status = newStatus;
    }

    void setExperienceYears(int years) {
        experienceYears = years;
    }

    
    void displayPilotDetails() const;
    
    
    static void displayAllPilots();
};

#endif
