#ifndef PAYMENTSERVICE_H
#define PAYMENTSERVICE_H

#include "json.hpp"
#include <string>
#include <vector>

using json = nlohmann::json;
using namespace std;

class PaymentService {
public:
    
    static vector<json*> findUnpaidReservations();
    
    
    static bool processPayment(
        json& reservation,
        const string& paymentMethod,
        const string& processedBy = ""
    );
    
    
    static void displayPaymentConfirmation(const json& reservation, const string& paymentMethod);
};

#endif
