#include "../include/ReportService.h"
#include <algorithm>
#include <map>
#include <string>
#include <vector>
using namespace std;

// External declarations
extern json flightsData;
extern json reservationsData;

ReportStats ReportService::generateStatistics() {
    ReportStats stats;
    stats.totalFlights = flightsData.size();
    stats.totalReservations = reservationsData.size();
    stats.totalRevenue = 0;
    stats.confirmedReservations = 0;
    stats.cancelledReservations = 0;
    
    // Analyze reservations
    for (const auto& res : reservationsData) {
        string status = res["status"];
        int price = res["totalPrice"];
        string flightNumber = res["flightNumber"];
        
        stats.totalRevenue += price;
        
        if (status == "Confirmed" || status == "Checked-In") {
            stats.confirmedReservations++;
        } else if (status == "Cancelled") {
            stats.cancelledReservations++;
        }
        
        // Track bookings per flight
        stats.flightBookings[flightNumber]++;
        stats.revenueByFlight[flightNumber] += price;
    }
    
    return stats;
}

map<string, int> ReportService::getReservationsByStatus() {
    map<string, int> statusCount;
    
    for (const auto& res : reservationsData) {
        string status = res["status"];
        statusCount[status]++;
    }
    
    return statusCount;
}

map<string, int> ReportService::getRevenueByFlight() {
    map<string, int> revenue;
    
    for (const auto& res : reservationsData) {
        string flightNumber = res["flightNumber"];
        int price = res["totalPrice"];
        revenue[flightNumber] += price;
    }
    
    return revenue;
}

vector<pair<string, int>> ReportService::getTopFlights(int limit) {
    map<string, int> bookings;
    
    for (const auto& res : reservationsData) {
        string flightNumber = res["flightNumber"];
        bookings[flightNumber]++;
    }
    
    vector<pair<string, int>> result(bookings.begin(), bookings.end());
    
    sort(result.begin(), result.end(), 
         [](const pair<string, int>& a, const pair<string, int>& b) {
             return a.second > b.second;
         });
    
    if (result.size() > (size_t)limit) {
        result.resize(limit);
    }
    
    return result;
}
