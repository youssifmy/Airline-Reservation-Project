#ifndef CHECKINSERVICE_H
#define CHECKINSERVICE_H

#include "json.hpp"
#include <string>

using json = nlohmann::json;
using namespace std;

class CheckInService {
public:
    
    static bool checkInByReservationId(int reservationId, const string& checkedInBy = "");
    
    static void displayBoardingPass(const json& reservation, const string& passengerName = "");
};

#endif
