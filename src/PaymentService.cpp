#include "../include/PaymentService.h"
#include <iostream>

extern json reservationsData;
extern bool saveJSON(const string& filename, const json& data);

vector<json*> PaymentService::findUnpaidReservations() {
    vector<json*> unpaidReservations;
    
    for (auto& reservation : reservationsData) {
        if (reservation["paymentStatus"] == "Pending" || 
            reservation["paymentStatus"] == "Unpaid") {
            unpaidReservations.push_back(&reservation);
        }
    }
    
    return unpaidReservations;
}

bool PaymentService::processPayment(
    json& reservation,
    const string& paymentMethod,
    const string& processedBy
) {
    reservation["paymentStatus"] = "Paid";
    reservation["paymentMethod"] = paymentMethod;
    
    if (!processedBy.empty()) {
        reservation["processedBy"] = processedBy;
    }
    
bool success = saveJSON("data/reservations.json", reservationsData);
    
    return success;
}

void PaymentService::displayPaymentConfirmation(const json& reservation, const string& paymentMethod) {
    cout << "\n" << string(40, '=') << endl;
    cout << "   PAYMENT PROCESSED SUCCESSFULLY" << endl;
    cout << string(40, '=') << endl;
    cout << "Reservation ID: " << reservation["reservationId"] << endl;
    cout << "Amount Paid: $" << reservation["totalPrice"] << endl;
    cout << "Method: " << paymentMethod << endl;
    
    if (reservation.contains("processedBy")) {
        cout << "Processed by: " << reservation["processedBy"] << endl;
    }
    
    cout << string(40, '=') << endl;
}
