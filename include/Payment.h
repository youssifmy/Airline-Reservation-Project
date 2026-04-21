#ifndef PAYMENT_H
#define PAYMENT_H
#include <string>
using namespace std;
class Payment {
    private:
    int paymentId;
    int reservationId;
    double amount;
    string paymentDate;
    string paymentMethod;
    string transactionStatus;
    public:
    Payment(int paymentId, int reservationId, double amount, const string& paymentDate,
         const string& paymentMethod, const string& transactionStatus)
         : paymentId(paymentId), reservationId(reservationId), amount(amount),
           paymentDate(paymentDate), paymentMethod(paymentMethod),
           transactionStatus(transactionStatus) {}


        
    //getters
    int getPaymentId() const {
        return paymentId;
    }

    int getReservationId() const {
        return reservationId;
    }

    double getAmount() const {
        return amount;
    }

    string getPaymentDate() const {
        return paymentDate;
    }

    string getPaymentMethod() const {
        return paymentMethod;
    }

    string getTransactionStatus() const {
        return transactionStatus;
    }

    //setters

    void setTransactionStatus(const string& newStatus) {
        transactionStatus = newStatus;
    }

    //class functions
    void displayPaymentInfo() const;
    bool processPayment();
    void refundPayment();
    
        


};
#endif