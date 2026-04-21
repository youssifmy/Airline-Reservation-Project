#ifndef REPORTSERVICE_H
#define REPORTSERVICE_H

#include "json.hpp"
#include <string>
#include <map>

using json = nlohmann::json;
using namespace std;

struct ReportStats {
    int totalFlights;
    int totalReservations;
    int totalRevenue;
    int confirmedReservations;
    int cancelledReservations;
    map<string, int> flightBookings;
    map<string, int> revenueByFlight;
};

class ReportService {
public:
    
    static ReportStats generateStatistics();
    static map<string, int> getReservationsByStatus();
    static map<string, int> getRevenueByFlight();
    static vector<pair<string, int>> getTopFlights(int limit = 5);
};

#endif
