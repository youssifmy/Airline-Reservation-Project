#ifndef USER_H
#define USER_H

#include <string>
#include<iostream>
using namespace std;

class User {
protected:
    int id;
    string username;
    string password;
    string role;

public:
    // Constructor
    User(int id, const string& username, const string& password, const string& role)
        : id(id), username(username), password(password), role(role) {}
    
    
    virtual ~User() {}
    
    // Getters
    int getId() const {
        return id;
    }
    
    string getUsername() const {
        return username;
    }
    
    string getPassword() const {
        return password;
    }
    
    string getRole() const {
        return role;
    }
    
    // Setters 
    void setUsername(const string& newUsername) {
        username = newUsername;
    }
    
    void setPassword(const string& newPassword) {
        password = newPassword;
    }

    //class functions
    
    
    virtual void displayMenu() = 0;
    virtual void performAction(int choice) = 0;
};

#endif