#ifndef AIRCRAFT_H
#define AIRCRAFT_H
#include <string>
using namespace std;

class Aircraft {
    private:
        string aircraftId;
        string model;
        int totalCapacity;
        string maintenanceStatus;
        string lastmaintenanceDate;
        string nextmaintenanceDate;
    public:
    Aircraft(const string&aircraftId , const string& model, int totalCapacity, 
        const string& maintenanceStatus, const string& lastmaintenanceDate, 
        const string& nextmaintenanceDate):aircraftId(aircraftId), model(model), 
        totalCapacity(totalCapacity), maintenanceStatus(maintenanceStatus), 
        lastmaintenanceDate(lastmaintenanceDate), nextmaintenanceDate(nextmaintenanceDate) {}

        //getters
        string getAircraftId() const {
            return aircraftId;
        }

        string getModel() const {
            return model;
        }

        int getTotalCapacity() const {
            return totalCapacity;
        }

        string getMaintenanceStatus() const {
            return maintenanceStatus;
        }

        string getLastmaintenanceDate() const {
            return lastmaintenanceDate;
        }

        string getNextmaintenanceDate() const {
            return nextmaintenanceDate;
        }

        //setters

        void setMaintenanceStatus(const string& newStatus) {
            maintenanceStatus = newStatus;
        }

        void setLastmaintenanceDate(const string& newDate) {
            lastmaintenanceDate = newDate;
        }

        void setNextmaintenanceDate(const string& newDate) {
            nextmaintenanceDate = newDate;
        }

        //Functions

        bool isAvailable() const;

        void displayAircraftInfo() const;


        
        

};


#endif