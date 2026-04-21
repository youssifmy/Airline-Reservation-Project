#ifndef USERMANAGEMENTSERVICE_H
#define USERMANAGEMENTSERVICE_H

#include "json.hpp"
#include <string>
#include <vector>

using json = nlohmann::json;
using namespace std;

struct UserInfo {
    int id;
    string username;
    string role;
    string email;
    int loyaltyPoints;
};

class UserManagementService {
public:
    
    static vector<UserInfo> getAllUsers();
    
    
    static bool addUser(const string& username, const string& password, const string& role, const string& email);
    
    static bool deleteUser(int userId);

    static bool updateUser(int userId, const string& email, const string& role);
    
    static int getNextUserId();
};

#endif
