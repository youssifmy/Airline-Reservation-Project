#include "../include/Payment.h"
#include <iostream>
using namespace std;

void Payment::displayPaymentInfo() const {
    cout <<"Payment-ID: " << paymentId << endl;
    cout <<"Reservation-ID: " << reservationId << endl;
    cout <<"Amount: " << amount << endl;
    cout <<"Payment-Date: " << paymentDate << endl;
    cout <<"Payment-Method: " << paymentMethod << endl;
    cout <<"Transaction-Status: " << transactionStatus << endl;

}

bool Payment::processPayment(){
    if(transactionStatus == "Completed"){
        cout << "Payment already processed" << endl;
        return false;
    }else{
        cout << "Processing payment..." << endl;
        setTransactionStatus("Completed");
        cout << "Payment of $" << amount << " processed successfully!" << endl;
        return true;
    }

};

void Payment::refundPayment(){
    if (transactionStatus == "Completed")
    {
        setTransactionStatus("Refunded");
        cout << "Refund processed successfully!" << endl;
        cout << "$" << amount << " will be returned to your " << paymentMethod << "." << endl;
    }else if(transactionStatus == "Refunded"){
        cout << "Transaction Already Refunded" << endl;
    } else {
    cout << "Cannot process refund - payment was not completed." << endl;
    cout << "Current status: " << transactionStatus << endl;
}
  

    

}