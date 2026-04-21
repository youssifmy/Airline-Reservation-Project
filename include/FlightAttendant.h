#ifndef FLIGHTATTENDANT_H
#define FLIGHTATTENDANT_H

#include <string>
using namespace std;

class FlightAttendant {
private:
    string attendantId;
    string name;
    string certification;
    int yearsOfService;
    string status; 

public:
    FlightAttendant(const string& attendantId, const string& name, 
                    const string& certification, int yearsOfService,
                    const string& status = "Available")
        : attendantId(attendantId), name(name), certification(certification),
          yearsOfService(yearsOfService), status(status) {}

    // Getters
    string getAttendantId() const {
        return attendantId;
    }

    string getName() const {
        return name;
    }

    string getCertification() const {
        return certification;
    }

    int getYearsOfService() const {
        return yearsOfService;
    }

    string getStatus() const {
        return status;
    }

    // Setters
    void setStatus(const string& newStatus) {
        status = newStatus;
    }

    void setYearsOfService(int years) {
        yearsOfService = years;
    }

    
    void displayAttendantDetails() const;
    
    
    static void displayAllAttendants();
};

#endif
